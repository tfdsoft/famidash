import sys

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

showall = 1
if ("--only-diff" in sys.argv or "--diff-only" in sys.argv or "-d" in sys.argv):
	showall = 0

quote = ""
if ("--md" in sys.argv or "-m" in sys.argv):
	quote = "`"

check = "scope"
if ("--scope" in sys.argv):
	check = "scope"
if ("--seg" in sys.argv or "-s" in sys.argv):
	check = "seg"

# print("start")
old = readDbgFile("TMP/famidash", check)
new = readDbgFile("BUILD/famidash", check)

maxstrsize = [len(i[0]) for i in old.items() if (showall or (i[1] - new[i[0]] != 0))]
if (len(maxstrsize) == 0):
	print("No entries found, exiting")
	exit(0)
maxstrsize = max(maxstrsize)
maxnumsize = max([len(str(i[1])) for i in old.items() if (showall or (i[1] - new[i[0]] != 0))])

diff = 0

for i in old.items():
	newsize = new[i[0]]
	thisdiff = (i[1] - newsize)
	if (thisdiff != 0 or showall) :
		padding = " " * (maxstrsize - len(i[0]))
		signpadding = " " if thisdiff > 0 else ""
		numpadding = " " * (maxnumsize - len(str(i[1])))
		print(f"{quote}{i[0]}:{padding} {i[1]}{numpadding} → {newsize}" + ((f"{numpadding} - diff: {signpadding}{thisdiff}") if thisdiff != 0 else "") + quote)
	diff += thisdiff

print("\nTotal size reduction: "+str(diff)+" bytes")