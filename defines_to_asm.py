#!/usr/bin/env python

def convertCFileToS(filename : str, outfilename : str):
	infile = open(filename, "r")
	outfile = open(outfilename, "w")
	for line in infile:
		split = line.split()
		# print(line)
		if len(split) == 0:
			outfile.write("\n")
		elif split[0] == "#define":
			split[1] = "_" + split[1]
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
	import sys, argparse, pathlib
	parser = argparse.ArgumentParser()
	parser.add_argument("input", nargs=argparse.REMAINDER)
	args = parser.parse_args()

	ownPath = pathlib.PurePath(sys.path[0])
	for filename in args.input:
		realFilename = ownPath / filename
		outFilename = ownPath / "TMP" / (realFilename.stem+".s")
		convertCFileToS(realFilename, outFilename)