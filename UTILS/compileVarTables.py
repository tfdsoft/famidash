#!/usr/bin/env python

import pathlib, re, math

optionalFlagRegex = \
	"(?:" + "|".join(
		f"{marker}[ \t]*=[ \t]*(?P<{name}>{data})" for marker, name, data in [
			("sz", "size", r".*"),
			("pw", "power", r"-?\d+")
	]) + ")"
optionalFlagsRegex = f"(?:{optionalFlagRegex}[ \t]+)*"

lineParseRegex = re.compile(r'^[\t ]*(?!#|$)(?P<type>\w+)[\t ]+' + optionalFlagsRegex + r'?\[(?P<flags>\w*)\][\t ]+(?P<name>\w+)[\t ]+(?P<value>.*)$', re.MULTILINE)
fxpRegex = re.compile(r'^fxp(?P<fracBits>\d+)')

parseNum = lambda x : float(x) if "." in x else int(x, base=0)

getByte = lambda x, y : (x >> (y * 8)) & 0xFF

def bytesEqual(arr, idx : int) -> bool:
	tmp = [getByte(i, idx) for i in arr]
	return max(tmp) == min(tmp)

NTSC_FRAMERATE = (236250000 / 11) / 4 / 89341.5
PAL_FRAMERATE = (26601712.5) / 5 / 106392

def generateCNumArray(num : int|float, source : dict, maxNum : int = None) -> list:
	if not maxNum:
		maxNum = num

	if re.match(fxpRegex, source['type']):
		num *= 2 ** int(re.match(fxpRegex, source['type'])['fracBits'])	# Convert to fixed point
		maxNum *= 2 ** int(re.match(fxpRegex, source['type'])['fracBits'])

	if source['power'] == None or int(source['power']) == 0:
		ntscVal = palVal = num
		maxVal = maxNum
	else:
		ntscVal = num * NTSC_FRAMERATE ** int(source['power'])
		palVal = num * PAL_FRAMERATE ** int(source['power'])
		if int(source['power']) < 0:	# Division
			maxVal = maxNum * PAL_FRAMERATE ** int(source['power'])		# Maximum result of division
		elif int(source['power']) > 0:	# Multiplication
			maxVal = maxNum * NTSC_FRAMERATE ** int(source['power'])	# Maximum result of division

	if source['size'] != None:
		maxVal = 2 ** int(source['size'])
	else:
		bitCount = math.ceil(math.ceil(math.log2(abs(maxVal))+(1 if 'g' in source['flags'] else 0)) / 8) * 8
		maxVal = 2 ** bitCount

	if (num < 0):
		ntscVal = maxVal - abs(ntscVal)
		palVal = maxVal - abs(palVal)


	return [
		[
			round(palVal),
			round((maxVal - palVal) if 'g' in source['flags'] else palVal),
		],
		[
			round(ntscVal),
			round((maxVal - ntscVal) if 'g' in source['flags'] else ntscVal),
		]
	]

def generateCArrayLine(source : dict, numTable : tuple[int], byteIdx : int, suffix : str | None) -> str:
	if suffix == None:
		suffix = ""
	else:
		suffix = f"_{suffix}"

	if bytesEqual(numTable, byteIdx):
		return f"#define {source['name']}{suffix} 0x{getByte(numTable[0], byteIdx):02X}"
	else:
		return f"const uint8_t {source['name']}{suffix}[] = {{{', '.join(f'0x{getByte(i, byteIdx):02X}' for i in numTable)}}};"

def generateCArgumentDefine(source : dict, numTable : tuple[int], suffixes : tuple[str] | list[str], argument : str) -> str:
	output = [f"__A__ = {argument}", '__asm__("tay")']
	size = len(suffixes) * 8
	suffixes = [f"_{i}" for i in suffixes]
	equalBytes = [bytesEqual(numTable, i) for i in range(size // 8)]
	arg = [r'#%b' if i else r'%v, y' for i in equalBytes]
	val = [f'{source["name"]}{suffix}' for suffix in suffixes]
	if size > 16:
		if size > 24:
			# Load value into sreg+1
			output.append(f'__asm__("ldx {arg[3]}", {val[3]})')
		else:
			# Load zero into sreg+1
			output.append(f'__asm__("ldx #0")')
		output.append(f'__asm__("lda {arg[2]}", {val[2]})')
		output.append(f'__EAX__ <<= 16')

	output.append(f'__asm__("ldx {arg[1]} \\n lda {arg[0]}", {val[1]}, {val[0]})')
	output.append('__EAX__' if size > 16 else '__AX__')
	output = [f'\t{i}' for i in output]
	mlsp = '\\\n'
	output = f'( {mlsp}{f", {mlsp}".join(output)} {mlsp})'
	return output

def generateCTable(source : dict) -> str:
	comment = None
	argument = "table_idx"

	flags = {
		'g': 'g' in source['flags'],
		'm': 'm' in source['flags'],
		'r': not (source['power'] == None or int(source['power']) == 0)
	}

	size_override = -1 if source['size'] == None else int(source['size'])

	if flags['g'] and not (flags['m'] or flags['r']):
		value = generateCNumArray(parseNum(source['value']), source)
		numTable = value[0]
		comment = "// Depends on gravity"
		argument = "gravity"
	elif flags['m'] and not (flags['r'] or flags['g']):
		values = [parseNum(i) for i in source['value'].split()]
		values = [generateCNumArray(i, source, max(values)) for i in values]
		numTable = (values[0][0][0], values[1][0][0])
		comment = "// Depends on mini"
		argument = "mini"
	elif flags['r'] and not (flags['g'] or flags['m']):
		value = generateCNumArray(parseNum(source['value']), source)
		numTable = (value[0][0], value[1][0])
		comment = "// Depends on framerate"
		argument = "framerate"
	elif flags['m']:
		values = [parseNum(i) for i in source['value'].split()]
		values = [generateCNumArray(i, source, max(values)) for i in values]
		numTable = (*values[0][0], *values[1][0], *values[0][1], *values[1][1])
	else:
		value = generateCNumArray(parseNum(source['value']), source)
		numTable = (*value[0], *value[0], *value[1], *value[1])

	size = math.ceil(math.ceil(max(math.log2(max(numTable)), size_override)) / 8) * 8
	
	if (size == 8):
		return (comment + '\n' if comment else '') + f'const uint8_t {source["name"]}[] = {{{", ".join(f"0x{i:02X}" for i in numTable)}}};\n#define {source["name"]}({argument}) {source["name"]}[{argument}]'
	elif (size >= 16 and size <= 32):
		outString = []
		if comment:
			outString.append(comment)

		match(size):
			case 16:
				suffixes = ['lo', 'hi']
			case 24:
				suffixes = ['lo', 'md', 'hi']
			case 32:
				suffixes = ['lo', 'md', 'hi', 'ex']

		for byte, suffix in enumerate(suffixes):
			outString.append(generateCArrayLine(source, numTable, byte, suffix))
		
		if any([bytesEqual(numTable, i) for i in range(size // 8)]):
			outString.append(f'#define {source["name"]}({argument}) {generateCArgumentDefine(source, numTable, suffixes, argument)}')
		else:
			outString.append(f'#define {source["name"]}({argument}) (lohi_arr{size}_load({source["name"]}, {argument}))')

		return "\n".join(outString)
	print(f"Table integer size {size} is invalid! Full table: {numTable}, happened with {source}")

	return f""


if __name__ == "__main__":
	import sys, argparse
	parser = argparse.ArgumentParser()
	parser.add_argument("input", nargs=argparse.REMAINDER)
	args = parser.parse_args()

	rootPath = pathlib.Path(sys.path[0]).parent.resolve()

	for filename in args.input:
		realFilename = rootPath / filename
		outFilename = realFilename.parent / (realFilename.stem+".cmp.h")
		
		outString = ["// This file was generated by compileVarTables.py\n\n"]

		for line in re.finditer(lineParseRegex, realFilename.read_text()):
			outString.append(generateCTable(line.groupdict()))

		outFilename.write_text("\n\n".join(outString))