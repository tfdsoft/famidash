#!/usr/bin/env python3

import sys, argparse, pathlib, re

cfgCommentRemoveRegex = [re.compile(r'(?m:^(.*?)(#.*?)$)'), r'\0']
cfgPartsRegex = re.compile(r'(?ms:^(?P<name>\w+) \{$(?P<data>.*?)^\})')
cfgLineRegex = re.compile(r'(?P<name>\w+):\s*(?P<data>(?:\s*(?:\w+)\s*=\s*(?:\S+?)\s*(?:,|))+);')
cfgDataRegex = re.compile(r'(?:(\w+)\s*=\s*(\S+?)(?:\s*,|\s+))')

dbgLineRegex = r'(?ms:^(?P<name>\w+)[\t ](?P<data>(?:\w+=(?:"[^"]*?"|[^,\n]+)(?:,|$))+))'
specDbgLineRegex = lambda x : re.compile(r'(?ms:^(?P<name>' + x + r')[\t ](?P<data>(?:\w+=(?:"[^"]*?"|[^,\n]+)(?:,|$))+))')
dbgDataRegex = re.compile(r'(?:(?P<id>\w+)=(?:"(?P<str>[^"]*?)"|(?P<misc>[^,\n]+))(?:,|$))')

def readDbgFile (filename : pathlib.Path, check : str = None) -> dict:
	outdict = {}
	text = filename.read_text()

	if check == None:
		lineRgx = re.compile(dbgLineRegex)
	else:
		lineRgx = re.compile(specDbgLineRegex(check))

	for line in re.finditer(lineRgx, text):
		if line['name'] not in outdict.keys():
			outdict[line['name']] = list()

		lineData = {}
		for data in re.finditer(dbgDataRegex, line['data']):
			lineData[data['id']] = data[data.lastgroup]
		outdict[line['name']].append(lineData)
	return outdict

def readCfgFile (filename : pathlib.Path) -> dict:
	outdict = {}
	text = filename.read_text()

	text = re.sub(*cfgCommentRemoveRegex, text)

	for i in re.finditer(cfgPartsRegex, text):
		part = {}
		
		for line in re.finditer(cfgLineRegex, i['data']):
			lineData = {}
			for statement in re.finditer(cfgDataRegex, line['data']):
				lineData[statement[1]] = statement[2]
			part[line['name']] = lineData

		outdict[i['name']] = part

	return outdict

ownPath = pathlib.Path(sys.path[0]).resolve()

parser = argparse.ArgumentParser()
filepathArgGroup = parser.add_mutually_exclusive_group()
filepathArgGroup.add_argument("subfolder", help="Subfolder of BUILD/ to get the famidash.dbg file from, the default is main", nargs="?", default="main")
filepathArgGroup.add_argument("-f", "--file", help="Specify a path of the new famidash.dbg file, the default is BUILD/[subfolder]/famidash.dbg", type=pathlib.Path)
parser.add_argument("-d", "--only-diff", "--diff-only", help="Only show the differences between the .dbg files", action="store_false", default=True)
parser.add_argument("-m", "--markdown-mode", "--md", help="Enable markdown code quotes around individual entries", action="store_true")
parser.add_argument("-e", "--entry-type", help="The type of entries to include", default="bank", choices=["scope", "seg", "bank"])
parser.add_argument("-c", "--compare", help="Compare the current BUILD/famidash.dbg file to an older version of the famidash.dbg file", type=pathlib.Path)
parser.add_argument("-s", "--sort", help="Sorting options", default="declaration", choices=
					["declaration", "d", "alphabetical", "a", "size-increasing", "si", "size-decreasing", "sd"])
args = parser.parse_args()

if args.file:
	filepath = args.file
else:
	if not pathlib.Path(ownPath / 'BUILD' / args.subfolder).is_dir():
		print("The subfolder argument is invalid. Please specify a subfolder that exists.")
		exit(1)
	if not pathlib.Path(ownPath / 'BUILD' / args.subfolder / 'famidash.dbg').is_file():
		print(f"The subfolder 'BUILD/{args.subfolder}' does not have a famidash.dbg file. Please specify a subfolder that has one.")
		exit(1)
	filepath = ownPath / 'BUILD' / args.subfolder / 'famidash.dbg'

showall = args.only_diff

quote = "`" if args.markdown_mode else ""

sortalg = args.sort

conversion = {"declaration" : "d", "alphabetical" : "a", "size-increasing" : "si", "size-decreasing" : "sd"}
if sortalg in conversion.keys():
	sortalg = conversion[sortalg]

check = args.entry_type
if check == "bank":
	check = "seg"

compare = args.compare != None

# print("start")
if compare:
	oldDbgData = readDbgFile(args.compare, check)
	old = {i['name'] : int(i['size'], base=0) for i in oldDbgData[check]}
newDbgData = readDbgFile(filepath, check)
new = {i['name'] : int(i['size'], base=0) for i in newDbgData[check]}

if compare:
	for i in old.items():
		if i[0] not in new.keys():
			new[i[0]] = 0
	for i in new.items():
		if i[0] not in old.keys():
			old[i[0]] = 0

if args.entry_type == "bank":
	cfgData = readCfgFile(ownPath / "CONFIG" / "mmc3.cfg")
	cfg = {}
	for segment in cfgData['SEGMENTS']:
		cfg[segment] = cfgData['SEGMENTS'][segment]['load']
	if compare:
		older = old.copy()
		old = {}
	newer = new.copy()
	new = {}

	# map segments onto memory areas
	for i in cfg.keys():

		if compare:
			if cfg[i] not in old.keys():
				old[cfg[i]] = 0
			if i not in older.keys():
				older[i] = 0
			old[cfg[i]] += older[i]

		if cfg[i] not in new.keys():
			new[cfg[i]] = 0
		if i not in newer.keys():
			newer[i] = 0
		new[cfg[i]] += newer[i]

if (compare):
	maxstrsize = [len(i[0]) for i in new.items() if (showall or (old[i[0]] - i[1] != 0))]
else:
	maxstrsize = [len(i[0]) for i in new.items()]
if (len(maxstrsize) == 0):
	print("No entries found, exiting")
	exit(0)
maxstrsize = max(maxstrsize)
maxnewnumsize = max([len(str(i[1])) for i in new.items() if (showall or (old[i[0]] - i[1] != 0))])

if compare:
	maxoldnumsize = max([len(str(i[1])) for i in old.items() if (showall or (i[1] - new[i[0]] != 0))])
	diff = 0

	items = list(old.items())
	if sortalg != "d":
		items.sort(key = lambda x : (x[0].strip("_") if sortalg == "a" else x[1]), reverse = sortalg == "sd")

	for i in items:
		newsize = new[i[0]]
		thisdiff = (i[1] - newsize)
		if (thisdiff != 0 or showall) :
			padding = " " * (maxstrsize - len(i[0]))
			signpadding = " " if thisdiff > 0 else ""
			oldnumpadding = " " * (maxoldnumsize - len(str(i[1])))
			newnumpadding = " " * (maxnewnumsize - len(str(newsize)))
			print(f"{quote}{i[0]}:{padding} {i[1]}{oldnumpadding} → {newsize}" + ((f"{newnumpadding} - diff: {signpadding}{thisdiff}") if thisdiff != 0 else "") + quote)
		diff += thisdiff

	print("\nTotal size reduction: "+str(diff)+" bytes")

else:
	items = list(new.items())
	if sortalg != "d":
		items.sort(key = lambda x : (x[0].strip("_") if sortalg == "a" else x[1]), reverse = sortalg == "sd")


	for i in items:
		size = i[1]
		padding = " " * (maxstrsize - len(i[0]))
		print(f"{quote}{i[0]}:{padding} {size}{quote}")