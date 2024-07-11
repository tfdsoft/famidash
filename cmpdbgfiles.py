import sys, argparse

def readDbgFile (filename : str, check : str) -> dict:
	file = open(sys.path[0]+"/"+filename+".dbg")

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

parser = argparse.ArgumentParser()
parser.add_argument("-d", "--only-diff", "--diff-only", help="Only show the differences between the .dbg files", action="store_false", default=True)
parser.add_argument("-m", "--markdown-mode", "--md", help="Enable markdown code quotes around individual entries", action="store_true")
parser.add_argument("-e", "--entry-type", help="The type of entries to include", default="scope", choices=["scope", "seg"])
parser.add_argument("-u", "--update", help="Include new or removed entries between .dbg files", action="store_true")
args = parser.parse_args()

showall = args.only_diff

quote = "`" if args.markdown_mode else ""

check = args.entry_type

showNewOrRemoved = args.update

# print("start")
old = readDbgFile("TMP/famidash", check)
new = readDbgFile("BUILD/famidash", check)

if (showNewOrRemoved):
	for i in old.items():
		if i[0] not in new.keys():
			new[i[0]] = 0
	for i in new.items():
		if i[0] not in old.keys():
			old[i[0]] = 0

maxstrsize = [len(i[0]) for i in old.items() if (showall or (i[1] - new[i[0]] != 0))]
if (len(maxstrsize) == 0):
	print("No entries found, exiting")
	exit(0)
maxstrsize = max(maxstrsize)
maxoldnumsize = max([len(str(i[1])) for i in old.items() if (showall or (i[1] - new[i[0]] != 0))])
maxnewnumsize = max([len(str(i[1])) for i in old.items() if (showall or (i[1] - new[i[0]] != 0))])

diff = 0

for i in old.items():
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