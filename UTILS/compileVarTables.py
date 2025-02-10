#!/usr/bin/env python

import pathlib, re, math, itertools

optionalFlagRegex = \
	"(?:" + "|".join(
		f"{marker}[ \t]*=[ \t]*(?P<{name}>{data})" if data else f"(?P<{name}>{marker})"
		for marker, name, data in [
			("sz", "size", r".*"),
			("pw", "power", r"-?\d+"),
			("tbl", "table", None),
			("uninum", "unifiedNumber", None),
			("be", "bigEndian", None),
			("ef", "exactFramerate", None)
	]) + ")"
optionalFlagsRegex = f"(?:{optionalFlagRegex}[ \t]+)*"

lineParseRegex = re.compile(r'^[\t ]*(?!#|$)' + 
	'|'.join(f'(?:{expr})' for expr in [
		r'(?P<type>(?:int)|(?:fxp\w+))[\t ]+' + 
			optionalFlagsRegex +
			r'?\[(?P<flags>\w*)\][\t ]+(?P<name>\w+)[\t ]+' +
			r'(?:{(?s:(?P<mltLnValue>.*?))}.*|(?P<value>.*))',
		
		r'(?P<segCmd>segment)[\t ]+(?P<segVal>\w+)'
	]) + '$', re.MULTILINE)		# matches each command

fxpRegex = re.compile(r'^fxp(?P<fracBits>\d+)')	# matches fxp type, gets the amount of bits

filterRegex = re.compile(r'#.*?$|\\\n', re.MULTILINE)	# removes comments and converts line breaks into one line

parseNum = lambda x : float(x) if "." in x else int(x, base=0)

getByte = lambda x, y : (x >> (y * 8)) & 0xFF

def bytesEqual(arr, idx : int) -> bool:
	tmp = [getByte(i, idx) for i in arr]
	return max(tmp) == min(tmp)

NTSC_FRAMERATE = (236250000 / 11) / 4 / 89341.5
PAL_FRAMERATE = (26601712.5) / 5 / 106392

NTSC_FRAMERATE_APPROX = 60
# defines PAL rate as the same ratio as real PAL / NTSC, but assuming that NTSC is 60Hz
PAL_FRAMERATE_APPROX = (26601712.5) / 5 / 106392 * (60 / ((236250000 / 11) / 4 / 89341.5))

def generateCNumArray(num : int|float, source : dict, maxNum : int = None) -> list:
	if not maxNum:
		maxNum = num

	if source['exactFramerate']:
		ntsc = NTSC_FRAMERATE
		pal = PAL_FRAMERATE
	else:
		ntsc = NTSC_FRAMERATE_APPROX
		pal = PAL_FRAMERATE_APPROX

	if re.match(fxpRegex, source['type']):
		num *= 2 ** int(re.match(fxpRegex, source['type'])['fracBits'])	# Convert to fixed point
		maxNum *= 2 ** int(re.match(fxpRegex, source['type'])['fracBits'])

	if source['power'] == None or parseNum(source['power']) == 0:
		ntscVal = palVal = num
		maxVal = maxNum
	else:
		ntscVal = num * ntsc ** int(source['power'])
		palVal = num * pal ** int(source['power'])
		if int(source['power']) < 0:	# Division
			maxVal = maxNum * pal ** int(source['power'])	# Maximum result of division
		elif int(source['power']) > 0:	# Multiplication
			maxVal = maxNum * ntsc ** int(source['power'])	# Maximum result of division

	if maxNum == 0:
		return [[0, 0], [0, 0]]

	if source['size']:
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

def generateOptimizedNumArray(source : dict, flags : dict, value) -> tuple:
	comment = None
	argument = "table_idx"
	maxVal = None

	if type(source['value']) in [list]:
		maxVal = max(map(parseNum, source['value']), key=abs)

	if flags['g'] and not (flags['m'] or flags['r']):
		value = generateCNumArray(parseNum(value), source, maxVal)
		numTable = value[0]
		comment = "// Depends on gravity"
		argument = "gravity"
	elif flags['m'] and not (flags['r'] or flags['g']):
		values = [parseNum(i) for i in value]
		values = [generateCNumArray(i, source, maxVal) for i in values]
		numTable = (values[0][0][0], values[1][0][0])
		comment = "// Depends on mini"
		argument = "mini"
	elif flags['r'] and not (flags['g'] or flags['m']):
		value = generateCNumArray(parseNum(value), source, maxVal)
		numTable = (value[0][0], value[1][0])
		comment = "// Depends on framerate"
		argument = "framerate"
	elif flags['m']:
		values = [parseNum(i) for i in value]
		values = [generateCNumArray(i, source, maxVal) for i in values]
		numTable = (*values[0][0], *values[1][0], *values[0][1], *values[1][1])
	else:
		value = generateCNumArray(parseNum(source['value']), source, maxVal)
		numTable = (*value[0], *value[0], *value[1], *value[1])

	return (numTable, comment, argument)

def generateCTable(source : dict, numTable : tuple, argument : str, comment : str, size : int, name : str, unifiedNumber : bool, standalone : bool = True) -> str:
	if (size == 8):
		return (comment + '\n' if comment else '') + f'const uint8_t {name}[] = {{{", ".join(f"0x{i:02X}" for i in numTable)}}};' + (f'\n#define {name}({argument}) {name}[{argument}]' if standalone else '')
	elif (size >= 16 and size <= 32):
		if not unifiedNumber:
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
				outString.append(f'#define {name}({argument}) {generateCArgumentDefine(source, numTable, suffixes, argument)}')
			else:
				outString.append(f'#define {name}({argument}) (lohi_arr{size}_load({name}, {argument}))')

			return "\n".join(outString)

		else:
			fmt = lambda x : f'0x{x:04X}' if size == 16 else f'0x{x:08X}'

			if source['bigEndian']:
				inv = lambda x : ((getByte(x, 0) << 8) | getByte(x, 1)) if size == 16 else ((getByte(x, 0) << 24) | (getByte(x, 1) << 16) | (getByte(x, 2) << 8) | getByte(x, 3))
			else:
				inv = lambda x : x

			return (comment + '\n' if comment else '') + \
				('// These tables have been generated in big-endian.\n// Use the corresponding macros to fetch data.\n' if source['bigEndian'] and standalone else '') + \
				f'const uint{size}_t {name}[] = {{{", ".join(fmt(inv(i)) for i in numTable)}}};' + \
				(f'\n#define {name}({argument}) {name}[{argument}]' if standalone else '')
	print(f"Table integer size {size} is invalid! Full table: {numTable}, happened with {source}")

	return f""


def processCTableCommand(source : dict) -> str:
	if source['mltLnValue']:
		source['value'] = source['mltLnValue']

	source['value'] = str(source['value']).strip().split()
	if len(source['value']) == 1:
		source['value'] = source['value'][0]

	flags = {
		'g': 'g' in source['flags'],
		'm': 'm' in source['flags'],
		'r': not (source['power'] == None or int(source['power']) == 0)
	}

	size_override = -1 if source['size'] == None else int(source['size'])

	if source['table']:
		if flags['m']:
			values = tuple(zip(source['value'][:len(source['value']) // 2], source['value'][len(source['value']) // 2:]))
		else:
			values = source['value']
		numTable, comment, argument = zip(*map(lambda x : generateOptimizedNumArray(source, flags, x), values))
		comment = comment[0]
		argument = argument[0]
		# Maybe make this eventually a flag?
		numTable = tuple(zip(*numTable))
	else:
		numTable, comment, argument = generateOptimizedNumArray(source, flags, source['value'])

	if source['table'] and not source['unifiedNumber']:
		print("Warning: Tables without uninum are currently unsupported")
		comment += "\n// Table initially specified without uninum, currently unsupported"
		source['unifiedNumber'] = "uninum"

	if source['table']:
		maxVal = max(map(max, numTable))
	else:
		maxVal = max(numTable)

	size = math.ceil(math.ceil(max(math.log2(maxVal), size_override)) / 8) * 8

	if source['unifiedNumber']:
		if size < 8:
			size = 8
		elif 9 < size < 16:
			size = 16
		elif 17 < size < 32:
			size = 32
		elif size > 32:
			print(f"Size {size} > 32 and therefore is unsupported with the uninum argument.")
			return f"// You took a shit the size of {size} bits. It was one unified piece of shit."


	if source['table']:
		match(argument):
			case "gravity":
				flags = "gG"
			case "mini":
				flags = "mM"
			case "framerate":
				flags = ("50", "60")
			case _:
				flags = (f"{f}_{m}{g}" for f,m,g in itertools.product(("50", "60"), "mM", "gG"))

		names = tuple(f"{source['name']}_{combo}" for combo in flags)

		output = []

		if source['bigEndian']:
			output.append("// These tables have been generated in big-endian.")
			output.append("// Use the corresponding macros to fetch data.")

		for	idx, name in enumerate(names):
			output.append(generateCTable(source, numTable[idx], "idx", None, size, name, source['unifiedNumber'] != None, False))

		# Next, generate the table of tables
		output.append("")

		if comment:
			output.append(comment)

		output.append(f"const uint{size}_t * const {source['name']}[] = {{{', '.join(names)}}};")
		output.append(f"#define {source['name']}({argument}) {source['name']}[{argument} & 0x7F]")

		return "\n".join(output)

	else:
		return generateCTable(source, numTable, argument, comment, size, source['name'], source['unifiedNumber'] != None)
	
	
def processCommand(source : dict) -> str:
	if source['type']:
		return processCTableCommand(source)
	elif source['segCmd']:
		return f'#pragma rodata-name("{source["segVal"]}")'

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

		text = realFilename.read_text()
		text = re.sub(filterRegex, '', text)

		for line in re.finditer(lineParseRegex, text):
			outString.append(processCommand(line.groupdict()))

		outFilename.write_text("\n\n".join(outString))