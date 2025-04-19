#!/usr/bin/env python3

import pathlib
import sys
import re

own_path = pathlib.Path(sys.path[0]).resolve()

metadataPath = own_path / "metadata"

metadataFileRegex = "lvlset_(.+)_metadata.json5"
metadataFileGlob = "lvlset_*_metadata.json5"
metadataFile = lambda lvlset: metadataPath / f"lvlset_{lvlset}_metadata.json5"
outputFolder = lambda lvlset: own_path / "include" / f"lvlset_{lvlset}"
csvFolder = own_path / "LEVEL DATA"
innerScript = own_path / "export_levels.py"

availableLevelSets = {re.findall(metadataFileRegex, i.name)[0] for i in (metadataPath).glob(metadataFileGlob)}

verbose = False

if __name__ == "__main__":
	import argparse
	import subprocess
	import os
	from collections.abc import Iterable

	envPath = os.environ.get('PATH', "")
	if (os.name == 'posix'):
		envPath = envPath.split(":")
	elif (os.name == 'nt'):
		envPath = envPath.split(";")
	else:
		print (f"YO KIND OF OPERATING SYSTEM ('{os.name}') AIN'T SUPPORTED")
		exit(1)

	def checkErr(proc : subprocess.CompletedProcess):
		if (proc.returncode != 0):
			print(f"AN ERROR HAS OCCURED WITHIN A SUBPROCESS!\n======\nstdout dump:\n===\n{proc.stdout.decode()}\n===\nstderr dump:\n===\n{proc.stderr.decode()}\n===")
			proc.check_returncode() # exits
	
	def findInPATH(executable : str | dict | Iterable, possibleEnvPaths: str | Iterable | None = None):
		localEnvPath = envPath
		if isinstance(executable, str) or isinstance(executable, dict):
			executable = [executable]
		if possibleEnvPaths:
			if isinstance(possibleEnvPaths, str):
				localEnvPath = [possibleEnvPaths] + localEnvPath
			else:
				localEnvPath = list(possibleEnvPaths) + localEnvPath	
		for prefix in localEnvPath:
			for spec in executable:
				if isinstance(spec, dict):
					crit = spec['criterion']
					spec = spec['name']
				else:
					crit = lambda x: True
				if verbose:
					print(f"Checking {prefix}/{spec}")
				if (pathlib.Path(prefix) / spec).is_file() and crit((pathlib.Path(prefix) / spec).resolve()):
					return (pathlib.Path(prefix) / spec).resolve()
		return None

	parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)
	parser.add_argument('-f', '--csvFolder', type=pathlib.Path, required=False,
					default=csvFolder,
					help='Path to folder with csv files')
	parser.add_argument('-m', '--metadata', type=pathlib.Path, required=False,
					default=None,
					help='Custom path to json5 file with level metadata specifications')
	parser.add_argument('-o', '--outputFolder', type=pathlib.Path, required=False,
					default=None,
					help='Custom output folder for the include files')
	parser.add_argument('-l', '--levelSet', choices=availableLevelSets, required=False,
					default=None,
					help='Set of levels to export')
	parser.add_argument('-v', '--verbose', action='store_true',
		help='Increase verbosity of wrapper script')
	args = parser.parse_args()

	verbose = args.verbose

	levelSet = args.levelSet
	while levelSet not in availableLevelSets.union({"exit"}):
		levelSet = input(f"Please select the level set to export [{', '.join(sorted(availableLevelSets))}, exit to exit]: ")
	if levelSet == "exit":
		exit(0)

	metaFile = metadataFile(levelSet) if not args.metadata else args.metadata
	outFolder = outputFolder(levelSet) if not args.outputFolder else args.outputFolder

	print("Running export script...")
	cmd = [
		sys.executable, innerScript,
		'--csvFolder', args.csvFolder,
		'--metadata', metaFile,
		'--outputFolder', outFolder]
	if verbose:
		print(f"Command: {' '.join(map(str, cmd))}")
	proc = subprocess.run(cmd)
