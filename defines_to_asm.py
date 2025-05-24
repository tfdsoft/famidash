#!/usr/bin/env python

import pathlib, re

# basic splitter into control and comment blocks
basicSplit = re.compile(r'^(?P<padding>[\t ]*)(?:(?P<ctrl>#.*?)|(?P<noCtrl>))[\t ]*(?:\/\/(?P<comment>.*))?$', re.MULTILINE)
# process control statements
ifdefStatementMatch = re.compile(r'#ifdef[\t ]+(?P<id>\w+)')
condStatementMatch = re.compile(r'#(?P<ctrl>if|elif)[\t ]+(?P<stat>.*)')
ctrlStatementMatch = re.compile(r'#(?P<ctrl>else|endif)')
macroMatch = re.compile(r'#define[\t ]+(?P<id>\w+)\((?P<params>[\w,]+)\)[\t ]+(?P<stat>.*)[\t ]*')
defineMatch = re.compile(r'#define[\t ]+(?P<id>\w+)(?:[\t ]+(?P<stat>.*)|)[\t ]*')
# separates between (approximately) expressions and non-expressions
expressionSplit = re.compile(
	"(?:" + "|".join((
		r'(?:0[Xx](?P<hex>[\dA-Fa-f]+))',	# hex numerals
		# r'(?:0?[Oo](?P<oct>[0-7]+))',		# oct numerals (C26 or smth)
		r'(?:0(?P<oct>[0-7]+))',			# oct numerals
		r'(?:0[Bb](?P<bin>[01]+))',			# bin numerals
		r'(?:(?P<dec>\d+))',				# dec numerals
		r'(?P<mod>%)',						# mod operator, requires modification to insert into ca65
		r'(?P<neq>!=)',						# neq operator, same as above,
		r'(?P<eqp>==)',						# eq operator, same as above,
		r'(?P<opt><<|>>|=|>|<|>=|<=|&&|\|\|)',	# multi-symbol operators
		r'(?P<opr>[~*\/&^+\-|!])',				# single-symbol operators
		r'(?P<brc>[()])',						# braces, who knows how they get modified later
		r'(?P<chr>\'(?:[^\'\\]|\\.)*\')',		# character literals (treating like strings just in case)
		# r'(?P<str>"(?:[^"\\]|\\.)*")',		# string literals
		# cancelled because not valid expressions in both use cases
		r'(?P<tkn>\w+)',						# symbols
		r'(?P<pad>[\t ]+)',						# space
	)) + ")"
)
expressionMatch = re.compile(r'(?:' + expressionSplit.pattern + ')+')

def portExprToAsm(expr : str):
	outString = ""
	for i in re.finditer(expressionSplit, expr):
		kind = i.lastgroup
		val = i.group(kind)
		if kind in {"dec", "opt", "opr", "brc", "pad", "chr", "str"}:	# no-mod tokens
			outString += val
		elif kind in {"hex", "bin", "tkn"}:	# re-prefixed tokens
			outString += {"hex" : "$", "bin" : "%", "tkn": "_"}[kind]
			outString += val
		elif kind == "oct":
			# octal numerals are not supported in ca65,
			# so convert them to decimal
			outString += str(int(val, base=8))
		elif kind in {"mod", "neq", "eqp"}:
			# those tokens exist but with different symbols,
			# so replace them
			outString += {"mod" : " .mod ", "neq" : "<>", "eqp" : "="}[kind]

	return outString

def convertCFileToS(filename : pathlib.Path, outfile):
	fileText = filename.read_text()
	outText = ""
	for token in re.finditer(basicSplit, fileText):
		di = token.groupdict()

		outString = ""

		if (di['padding'] != None):
			outString += di['padding']

		if (di['ctrl'] != None):
			stat = di['ctrl']
			if re.match(ifdefStatementMatch, stat):
				match = re.match(ifdefStatementMatch, stat).groupdict()
				outString += f".ifdef _{match['id']}"
			elif re.match(condStatementMatch, stat):
				match = re.match(condStatementMatch, stat).groupdict()
				if re.match(expressionMatch, match['stat']) != None:
					outString += {"if" : ".if", "elif" : ".elseif"}[match['ctrl']]
					outString += f" {portExprToAsm(match['stat'])}"
				else:
					print(f"Line '{stat}' has a condition but the expression was deemed invalid")
			elif re.match(ctrlStatementMatch, stat):
				match = re.match(ctrlStatementMatch, stat).groupdict()
				outString += f".{match['ctrl']}"
			elif re.match(macroMatch, stat):
				match = re.match(macroMatch, stat).groupdict()
				outString += f"; MACRO: _{match['id']}({match['params']}) = {match['stat']}"
			elif re.match(defineMatch, stat):
				match = re.match(defineMatch, stat).groupdict()
				if match['stat'] == None:
					outString += f"_{match['id']} = 1"
				elif re.match(expressionMatch, match['stat']) != None:
					outString += f"_{match['id']} = {portExprToAsm(match['stat'])}"
				else:
					outString += f".define _{match['id']} {match['stat']}"
			else:
				outString += f"; NP : {di['ctrl']}"

		if (di['comment'] != None):
			if (len(outString)):
				outString += " "
			outString += f";{di['comment']}"

		outString += "\n"

		outText += outString
	outfile.write(outText)

getStringForFile = lambda name : "\n".join(["; " + ("="*23) + "+" + ("-"*len(name)) + "+", f"; Start of contents from |{name}|", "; " + ("="*23) + "+" + ("-"*len(name)) + "+", "", ""])

if __name__ == "__main__":
	import sys, argparse
	parser = argparse.ArgumentParser()
	parser.add_argument("output", type=pathlib.Path)
	parser.add_argument("input", nargs=argparse.REMAINDER)
	args = parser.parse_args()

	ownPath = pathlib.Path(sys.path[0]).resolve()
	outfile = open(ownPath / args.output.with_suffix(".s"), "w")
	for filename in args.input:
		outfile.write(getStringForFile(filename))
		realFilename = ownPath / filename
		convertCFileToS(realFilename, outfile)