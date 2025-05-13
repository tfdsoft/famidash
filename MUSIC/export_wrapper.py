#!/usr/bin/env python3

import pathlib
import sys
import re

famistudioHelpRegex = "FamiStudio (.+) Command-Line Usage"

own_path = pathlib.Path(sys.path[0]).resolve()
metadataPath = own_path / "METADATA"

metadataFileRegex = "lvlset_(.+)_metadata.json5"
metadataFileGlob = "lvlset_*_metadata.json5"
metadataFile = lambda lvlset: metadataPath / f"lvlset_{lvlset}_metadata.json5"
outputFolder = lambda lvlset: own_path / "EXPORTS" / f"lvlset_{lvlset}"
innerScript = own_path / "export.py"

availableLevelSets = {re.findall(metadataFileRegex, i.name)[0] for i in (metadataPath).glob(metadataFileGlob)}

tmpFolder = (own_path.parent / "TMP").resolve()

verbose = False

if __name__ == "__main__":
	import argparse
	import subprocess
	import time
	import os
	import textwrap
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

	def getFSVer(text):
		fsVer = [int(x) for x in text.split(".")]
		fsVer = fsVer[0]*1000_000 + fsVer[1]*1000 + fsVer[2]
		return fsVer

	def getFSFromFlatpak(flatpak):
		proc = subprocess.run([flatpak, '--version'], capture_output=True)
		if (proc.returncode == 0):
			# Search for org.famistudio.FamiStudio >= 4.3.0
			flatpakAppName = 'org.famistudio.FamiStudio'
			flatpakList = subprocess.run(['flatpak', 'list', '--columns=application,version'], capture_output=True)
			if (proc.returncode == 0 and len(flatpakList.stdout.decode())):
				# Split the data
				flatpakList = [i.split() for i in flatpakList.stdout.decode().splitlines()]
				flatpakFSList = list(filter(lambda x : len(x) == 2 and x[0] == 'org.famistudio.FamiStudio' and getFSVer(x[1]) >= 400_300_0, flatpakList))
				if verbose:
					print(f'List of FamiStudio >= 4.3.0 from flatpak instance at "{flatpak}":')
					print(flatpakFSList)
				return flatpakFSList

		return []

	def getFSCmdFromStem(filename : pathlib.PurePath | None):
		if not filename:
			return None

		if filename.name == "FamiStudio.dll":
			return ['dotnet', filename]
		elif filename.name == "famistudio":
			return [filename]
		elif filename.name == "flatpak":
			if len(getFSFromFlatpak(filename)) > 0:
				return [filename, 'run', 'org.famistudio.FamiStudio']
			else:
				print("flatpak has been specified, but it does not have org.famistudio.FamiStudio >= 4.3.0")
				return None
		else:
			print(f"The filename provided \"{filename.name}\" is invalid.")
			return None

	def checkFSVersion(executable):
		if verbose:
			print(f'Checking version of "{executable}"... ', end='', flush=True)
		cmd = getFSCmdFromStem(executable)
		proc = subprocess.run([*cmd, '-help'], capture_output=True)
		if proc.returncode != 0:
			if verbose:
				print(f'Executable invalid')
			return False
		fsVerStr = re.findall(famistudioHelpRegex, proc.stdout.decode())[0]
		fsVer = [int(x) for x in fsVerStr.split(".")]
		fsVer = fsVer[0]*1000_000 + fsVer[1]*1000 + fsVer[2]
		if (fsVer < 400_300_0):
			if verbose:
				print(f'Found valid executable but its version {fsVerStr} < 4.3.0')
			return False
		if verbose:
			print(f'Found valid executable version {fsVerStr}')
		return True

	famistudioExecutables = [{"name": "FamiStudio.dll", "criterion": checkFSVersion}]
	possibleFamiStudioEnvPaths = []
	if (os.name == 'posix'):
		# Possible e.g. AUR installation
		famistudioExecutables.append({"name": "famistudio", "criterion": checkFSVersion})
		# Possible flatpak installation
		# Currently disabled due to flatpak famistudio not passing arguments
		# famistudioExecutables.append({"name": "flatpak", "criterion": checkFSVersion}) # already includes flatpak checks
	elif (os.name == 'nt'):
		possibleFamiStudioEnvPaths = [
		f"{os.environ.get(i)}\\FamiStudio" for i in 
			["ProgramFiles", "ProgramFilesW6432", "ProgramFiles(x86)"]
			if i in os.environ.keys()]

	parser = argparse.ArgumentParser(formatter_class=argparse.RawTextHelpFormatter)
	parser.add_argument('-t', '--test', action='store_true',
		help='Export to a temporary folder instead of EXPORTS/')
	fsPathGroup = parser.add_mutually_exclusive_group()
	fsPathGroup.add_argument('-f', '--famistudioPath', type=pathlib.Path,
		help=textwrap.dedent('''\
			Path to FamiStudio executable''' + ('''
				(FamiStudio.dll, famistudio or flatpak on Linux)'''
					if os.name == 'posix' else '''
				(FamiStudio.dll on Windows)'''
					if os.name == 'nt' else '')
					+ ('''
				Not necessary if the executable is in PATH'''
				# or if FamiStudio is installed via flatpak'''
					if os.name == 'posix' else '''
				Not necessary if the executable is in PATH
				or in one of the Program Files\\FamiStudio folders'''
					if os.name == 'nt' else '')))
	fsPathGroup.add_argument('-c', '--famistudioCommand', nargs='+',
		help=textwrap.dedent('''\
			Command to execute FamiStudio
				(Useful if -f is not flexible enough
				or additional arguments are needed)'''))
	levelSetArgs = parser.add_mutually_exclusive_group()
	levelSetArgs.add_argument('-l', '--levelSet', choices=availableLevelSets, required=False,
					default=None,
					help='Set of levels to export')
	levelSetArgs.add_argument('-a', '--exportAll', action='store_true', required=False,
					default=False,
					help='Export all level sets')
	parser.add_argument('-v', '--verbose', action='store_true',
		help='Increase verbosity of wrapper script')
	args = parser.parse_args()


	def getFamiStudio():
		# Order of precedence:
		# 1. User-specified command / path
		# 2. Executable found in PATH
		# 3. Flatpak version
		if args.famistudioCommand:
			return args.famistudioCommand

		if args.famistudioPath:
			if (args.famistudioPath.is_file()):
				return getFSCmdFromStem(args.famistudioPath)
			
			if (args.famistudioPath.is_dir()):
				return getFSCmdFromStem(
					findInPATH(famistudioExecutables, [args.famistudioPath] + possibleFamiStudioEnvPaths)
				)
		
		return getFSCmdFromStem(
			findInPATH(famistudioExecutables, possibleFamiStudioEnvPaths)
		)

	fsCmd = getFamiStudio()

	if fsCmd == None:
		parser.print_help()
		print("")
		print("No FamiStudio instances found.")
		exit(1)

	verbose = args.verbose

	if args.exportAll:
		levelSet = "all"
	else:
		levelSet = args.levelSet
		while levelSet not in availableLevelSets.union({"exit", "all"}):
			levelSet = input(f"Please select the level set to export [{', '.join(sorted(availableLevelSets))}, 'exit' to exit, 'all' to build them all]: ")
		if levelSet == "exit":
			exit(0)

	if levelSet == "all":
		levelSetsToExport = availableLevelSets
	else:
		levelSetsToExport = [levelSet]

	for levelSet in levelSetsToExport:

		metaFile = metadataFile(levelSet)

		# Get output folder
		if args.test:
			# Create new temp folder
			foldername = f"music_export_{os.getpid():x}_{time.time_ns():x}"
			if verbose:
				print(f"Creating temporary folder TMP/{foldername}")
			outFolder = tmpFolder / foldername
			outFolder.mkdir()
		else:
			outFolder = outputFolder(levelSet)

		print(f"Running export script for level set {levelSet}...")
		cmd = [sys.executable, innerScript, '-f', *fsCmd, '-m', metaFile, '-o', outFolder]
		if verbose:
			print(f"Command: {' '.join(map(str, cmd))}")
		proc = subprocess.run(cmd)

		if args.test:
			if proc.returncode == 0:
				print(f"Export successful, deleting temporary folder {outFolder}")
				for i in outFolder.rglob('*'):
					i.unlink()
				outFolder.rmdir()
			elif proc.returncode == 1:
				print(f"Export failed before even doing anything, deleting temporary folder {outFolder}")
				for i in outFolder.rglob('*'):
					i.unlink()
				outFolder.rmdir()
			else:
				print(f"Export failed, please check temporary folder {outFolder}")
