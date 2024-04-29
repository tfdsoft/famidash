import sys

def readDbgFile (filename : str) -> dict:
	file = open(sys.path[0]+"/"+filename+".dbg")

	outdict = {}

	while (True):
		line = file.readline()
		# print(line)
		if not line:
			break
		if line.startswith("scope"):
			line = line.split(",")
			if [i[6:-1] for i in line if i.startswith("name")][0]:
				outdict[[i[6:-1] for i in line if i.startswith("name")][0]] = [int(i[5:]) for i in line if i.startswith("size")][0]
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
if ("--only-diff" in sys.argv):
	showall = 0

quote = ""
if ("--md" in sys.argv):
	quote = "`"

# print("start")
old = readDbgFile("TMP/famidash")
new = readDbgFile("BUILD/famidash")

maxsize = max([len(i[0]) for i in old.items() if (showall or (i[1] - new[i[0]] != 0))])

diff = 0

for i in old.items():
	newsize = new[i[0]]
	thisdiff = (i[1] - newsize)
	if (thisdiff != 0 or showall) :
		padding = " " * (maxsize - len(i[0]))
		signpadding = " " if thisdiff > 0 else ""
		print(f"{quote}{i[0]}:{padding} {i[1]}\t→ {newsize}" + ((f"\t - diff: {signpadding}{thisdiff}") if thisdiff != 0 else "") + quote)
	diff += thisdiff

print("\nTotal size reduction: "+str(diff)+" bytes")