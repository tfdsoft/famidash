#!/usr/bin/env python3

import sys, argparse, pathlib

def readDbgFile (filename : str, check : str) -> dict:
	file = open(sys.path[0]+"/"+filename)

	outdict = {}

	while (True):
		line = file.readline()
		# print(line)
		if not line:
			break
		if line.startswith(check):
			line = line.split(",")
			if [i[6:-1] for i in line if i.startswith("name")][0]:
				outdict[[i[6:-1] for i in line if i.startswith("name")][0]] = [int(i[5:], 0) for i in line if i.startswith("size")][0]
				# names += [i[6:-1] for i in line if i.startswith("name")]
				# sizes += [int(i[5:]) for i in line if i.startswith("size")]
			# if (len(line) >= 2 ):
				# output.append("#define "+line[0]+" "+line[2])
			# else: 
	# for i in outdict.items():
		# print(i)
	file.close()
	return outdict

def parseCfgLine (line : str) -> tuple:
	name = ""
	args = {}
	line = line.split()
	if len(line) == 0:
		return ()
	idx = 0
	for i in line:
		if i.startswith("#"):
			return ()
		elif i.endswith(":"):
			name = i.strip()[:-1]
			break
		idx += 1
	line = " ".join(line[idx+1:])
	line = line[:line.rfind(";")]
	for i in line.split(","):
		sub = i.split()
		if (len(sub) == 3):
			if sub[1] == "=":
				args[sub[0]] = sub[2]
		elif (len(sub) == 2):
			if sub[0][-1] == "=":
				args[sub[0][:-1]] = sub[2]
			elif sub[2][0] == "=":
				args[sub[0]] = sub[2][1:]
			else:
				raise ValueError (f"What the hell happened here? String:\n{i}")
		elif (len(sub) == 1):
			args[:i.index("=")] = args[i.index("=")+1:]
	return (name, args)


def readCfgFile (filename : str, check : str, part : str) -> dict:
	file = open(sys.path[0]+"/"+filename)

	outdict = {}

	state = 0

	lines = []

	while (True):
		line = file.readline()
		if not line:
			return {}
		if state == 0:
			if line.startswith(part):
				line = line.split()
				if line[1] == "{":
					state = 1
		elif state == 1:
			if "}" in line:
				break
			lines.append(line)
	for i in lines:
		data = parseCfgLine(i)
		if len(data) == 0:
			continue
		if check in data[1].keys():
			outdict[data[0]] = data[1][check]
	
	return outdict

parser = argparse.ArgumentParser()
parser.add_argument("-d", "--only-diff", "--diff-only", help="Only show the differences between the .dbg files", action="store_false", default=True)
parser.add_argument("-m", "--markdown-mode", "--md", help="Enable markdown code quotes around individual entries", action="store_true")
parser.add_argument("-e", "--entry-type", help="The type of entries to include", default="scope", choices=["scope", "seg", "bank"])
parser.add_argument("-c", "--compare", help="Compare the current BUILD/famidash.dbg file to an older version of the famidash.dbg file")
parser.add_argument("-s", "--sort", help="Sorting options", default="declaration", choices=
					["declaration", "d", "alphabetical", "a", "size-increasing", "si", "size-decreasing", "sd"])
args = parser.parse_args()

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
	old = readDbgFile(args.compare, check)
new = readDbgFile("BUILD/famidash.dbg", check)

if compare:
	for i in old.items():
		if i[0] not in new.keys():
			new[i[0]] = 0
	for i in new.items():
		if i[0] not in old.keys():
			old[i[0]] = 0

if args.entry_type == "bank":
	cfg = readCfgFile("CONFIG/mmc3.cfg", "load", "SEGMENTS")
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