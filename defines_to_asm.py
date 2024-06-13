def convertCFileToS(filename : str, outfilename : str):
	infile = open(filename, "r")
	outfile = open(outfilename, "w")
	while (True):
		line = infile.readline()
		split = line.split()
		# print(line)
		if not line:
			break
		if len(split) == 0:
			outfile.write("\n")
		elif split[0] == "#define":
			if len(split) >= 3 and (" ".join(split[2:])).isnumeric():
				outfile.write(f"{split[1]} = " + " ".join(split[2:]) + "\n")
			else:
				split[0] = ".define"
				outfile.write(" ".join(split) + "\n")
		elif split[0].startswith("//"):
			split[0] = ";" + split[0][2:]
			outfile.write(" ".join(split) + "\n")
		else:
			outfile.write(";" + " ".join(split) + "\n")
	infile.close()
	outfile.close()

if __name__ == "__main__":
	import sys
	convertCFileToS(sys.path[0]+"/BUILD_FLAGS.h", sys.path[0]+"/TMP/BUILD_FLAGS.s")