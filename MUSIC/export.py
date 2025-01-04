#!/usr/bin/env python3

import sys
import pathlib

famistudioHelpRegex = "FamiStudio (.+) Command-Line Usage"

instSizeRegex = "Info: Instruments size : (.+) bytes\\."
songSizeRegex = "Info: Song '(.+)' size: (.+) bytes\\."
totalSizeRegex = "Info: Total assembly file size: (.+) bytes\\."
youMustSetRegex = "Info: ([^\n]+, you must set [^\n]+\\.)"
actualOptionRegex = "set (FAMISTUDIO_[^ \n=]+ = [^ \n.]+)"

songNameRegex = 'Song[^\n]+Name="([^"]+)'
songFolderNameRegex = 'Song[^\n]+Folder="([^"]+)'

dpcmFileNameRegex = 'music_(.+)_bank(.+).dmc'

dpcmAlignerName = "dpcm"
usedFolderNames = ["Official music used in the game", "Custom music used in the game"]

musicFolder = pathlib.Path(sys.path[0]).resolve()
tmpFolder = (musicFolder.parent / "TMP").resolve()

if __name__ == "__main__":
    # install binpacking
    import importlib.util
    import subprocess
    import sys
    spec = importlib.util.find_spec('binpacking')
    if spec is None:
        subprocess.check_call([sys.executable, '-m', 'pip', 'install', 'binpacking'])

    import os, filecmp
    import re
    import argparse
    import binpacking
    
    def checkErr(proc : subprocess.CompletedProcess):
        if (proc.returncode != 0):
            print(f"AN ERROR HAS OCCURED WITHIN A SUBPROCESS!\n======\nstdout dump:\n===\n{proc.stdout.decode()}\n===\nstderr dump:\n===\n{proc.stderr.decode()}\n===")
            proc.check_returncode() # exits
    
    envPath = os.environ.get('PATH', "")
    if (os.name == 'posix'):
        envPath = envPath.split(":")
    elif (os.name == 'nt'):
        envPath = envPath.split(";")
    else:
        print (f"YO KIND OF OPERATING SYSTEM ('{os.name}') AIN'T SUPPORTED")
        exit(1)
    
    def findInPATH(executable : str):
        for prefix in envPath:
            if (pathlib.Path(prefix) / executable).is_file():
                return f"{prefix}/{executable}"
        return None
    
    parser = argparse.ArgumentParser()
    if (findInPATH("FamiStudio.dll")):
        parser.add_argument('fsPath', metavar='famistudioPath', help='Path to FamiStudio.dll from FamiStudio 4.3.0', nargs='?', default=findInPATH("FamiStudio.dll"), type=pathlib.Path)
    else:
        parser.add_argument('fsPath', metavar='famistudioPath', help='Path to FamiStudio.dll from FamiStudio 4.3.0', type=pathlib.Path)
    parser.add_argument('-t', '--test-export', action='store_true', help='Exports the music to the TMP folder instead of MUSIC/EXPORTS.')
    args = parser.parse_args()
    
    modulePath = musicFolder / "MODULES" / "music_master.fms"
    
    fsPath = pathlib.Path(args.fsPath)
    
    if not(fsPath.is_file() or (fsPath / "FamiStudio.dll").is_file()):
        print(f"{fsPath} is not a valid path to FamiStudio.dll or a directory with it.")
        exit(1)
        
    if fsPath.is_dir() and (fsPath / "FamiStudio.dll").is_file():
        fsPath /= "FamiStudio.dll"
    
    # Check FamiStudio version
    print("\n==== Checking FamiStudio version...")
    proc = subprocess.run(['dotnet', fsPath, '-help'], capture_output=True)
    checkErr(proc)
    fsVer = re.findall(famistudioHelpRegex, proc.stdout.decode())[0]
    fsVer = [int(x) for x in fsVer.split(".")]
    fsVer = fsVer[0]*1000_000 + fsVer[1]*1000 + fsVer[2]
    if (fsVer < 400_300_0):
        print("FamiStudio version is less than 4.3.0, please update")
        exit(1)

    # Get FamiStudio text file
    print("\n==== Exporting a FamiStudio text file for processing...")
    fsTxtPath = tmpFolder / "music_fs.txt"

    proc = subprocess.run(['dotnet', fsPath, modulePath, 'famistudio-txt-export', fsTxtPath], capture_output=True)
    checkErr(proc)
    if fsTxtPath.is_file():
        fsTxt = fsTxtPath.read_text()
        fsTxtPath.unlink(missing_ok = True)
    else:
        print("Somehow the famistudio-txt-export process didn't create a valid text file.")
        exit(2)

    songNames = re.findall(songNameRegex, fsTxt)
    folderNames = re.findall(songFolderNameRegex, fsTxt)
    neededSongs = [i for i in range(len(songNames)) if folderNames[i] in usedFolderNames]

    if len(songNames) == 0:
        print("Amount of valid songs in the FS txt file is 0.")
        exit(2)
    
    if not(dpcmAlignerName in songNames):
        print("DPCM aligner not found in FS txt file.")
        exit(2)
    elif len(neededSongs) == 0:
        print(f"None of the songs are in the folders \"{usedFolderNames}\".")
        exit(2)

    dpcmidx = songNames.index(dpcmAlignerName)
    neededSongsCommaSep = ",".join([str(i) for i in neededSongs])

    # Get instrument and song sizes
    print("\n==== Getting sizes of songs and instruments...")
    tmpAsmPath = tmpFolder / "music_all.s"

    proc = subprocess.run(['dotnet', fsPath, modulePath, 'famistudio-asm-export', tmpAsmPath, '-famistudio-asm-format:ca65', '-famistudio-asm-force-dpcm-bankswitch', f'-export-songs:{neededSongsCommaSep},{dpcmidx}'], capture_output=True)
    tmpAsmPath.unlink(missing_ok = True)
    checkErr(proc)

    for i in tmpFolder.glob(f"music_all*.dmc"):
        i.unlink(missing_ok = True)
    
    cmdOutput = proc.stdout.decode()
    
    # Get size of all instruments
    instsize = re.findall(instSizeRegex, cmdOutput)
    if (len(instsize) != 1):
        print("Instrument size not correctly present in the FamiStudio command output.")
        exit(3)
    instsize = int(instsize[0])
    print(f"== Total maximum size of data in a bank is {8192 - instsize} bytes")

    # Get song sizes in bytes
    songsizestrings = re.findall(songSizeRegex, cmdOutput)
    songsizes = [(songNames.index(i[0]), i[0], int(i[1])) for i in songsizestrings if i[0] != dpcmAlignerName]
    bins = binpacking.to_constant_volume(songsizes, 8192-instsize, 2)
    for i in range(len(bins)):
        print(f"== Bank {i}:")
        print("\t- Songs: "+", ".join([j[1] for j in bins[i]]))
        print("\t- Total approx. size:", sum([j[2] for j in bins[i]]), "bytes")

    # Export the music_X.s files
    if (args.test_export):
        exportPath = tmpFolder
    else:
        exportPath = musicFolder / "EXPORTS"
    
    dpcmFiles = []
    optionsToSet = []

    print("\n==== Running export processes of each music data bank...")

    for i in range(len(bins)):
        idxs = ",".join([str(j[0]) for j in bins[i]])

        asmExportName = f"music_{i+1}"
        asmExportPath = exportPath / f"{asmExportName}.s"

        proc = subprocess.run(['dotnet', fsPath, modulePath, 'famistudio-asm-export', asmExportPath, '-famistudio-asm-format:ca65', '-famistudio-asm-generate-list', f'-export-songs:{dpcmidx},{idxs}'], capture_output=True)
        output = proc.stdout.decode()
        checkErr(proc)

        print(f"== Info on bank {i}:")
        print("\t" + re.search(totalSizeRegex, output).group())
        
        dpcmFiles += exportPath.glob(f"{asmExportName}*.dmc")
        optionsToSet += re.findall(youMustSetRegex, output)

    # Check the DPCM files for being identical
    dpcmExportPath = exportPath
    dpcmExportStemPrefix = "music"

    print("\n==== Checking if the DPCM files are identical...")
    
    dpcmFiles = [(i, re.findall(dpcmFileNameRegex, i.name)[0]) for i in dpcmFiles]
    dpcmError = False
    dpcmBanks = list(set([i[1][1] for i in dpcmFiles]))
    for bank in dpcmBanks:
        bankDpcmError = False
        dpcmFilesOfBank = list(set(filter(lambda x : x[1][1] == bank, dpcmFiles)))
        for file in dpcmFilesOfBank:
            if not(filecmp.cmp(file[0], dpcmFilesOfBank[0][0], shallow=False)):
                print(f"DPCM Data Bank {file[1][1]} of music data bank {file[1][0]} differs from that of music data bank 0.")
                bankDpcmError = True
                dpcmError = True
        if not bankDpcmError:
            (dpcmExportPath / f"{dpcmExportStemPrefix}_bank{bank}.dmc").unlink(missing_ok = True)
            dpcmFilesOfBank[0][0].rename(dpcmExportPath / f"{dpcmExportStemPrefix}_bank{bank}.dmc")
            dpcmFilesOfBank.pop(0)
        [i[0].unlink(missing_ok = True) for i in dpcmFilesOfBank]

    if dpcmError:
        ValueError("DPCM files were not identical. Please check the dpcm aligner for containing all samples.")
        exit(4)    
    
    # Export bank lengths table
    bank_table_data = [
        ".if .not(useConstInitPtr)",
        "music_data_locations_lo:",
        f"\t.byte " + ", ".join([f"<music_data_famidash_music{i+1}" for i in range(len(bins))]),
        "music_data_locations_hi:",
        f"\t.byte " + ",".join([f">music_data_famidash_music{i+1}" for i in range(len(bins))]),
        ".endif",
        "",
        "music_counts:",
        f"\t.byte {', '.join([str(len(i)) for i in bins[:-1]])}, $FF ;last bank is marked with an FF to always stop bank picking"
        ]
    (exportPath / "musicPlayRoutines.s").write_text("\n".join(bank_table_data))

    # Print which options to set
    print("\n==== Don't forget to set these options in the sound driver:")
    print("\n".join(re.findall(actualOptionRegex, "\n".join(list(set(optionsToSet))))))

    if not args.test_export:
        print("\n==== Please launch parse_fs_files.py now.")
    else:
        print("\n==== Everything seems to have gone alright, you can run it for real now.")
        [i.unlink(missing_ok = True) for i in dpcmExportPath.glob(f"{dpcmExportStemPrefix}*.s")]
        [i.unlink(missing_ok = True) for i in dpcmExportPath.glob(f"{dpcmExportStemPrefix}*.dmc")]
        [i.unlink(missing_ok = True) for i in dpcmExportPath.glob(f"{dpcmExportStemPrefix}*songlist.inc")]