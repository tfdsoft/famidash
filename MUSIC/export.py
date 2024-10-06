#!/usr/bin/env python3

import sys

famistudioHelpRegex = "FamiStudio (.+) Command-Line Usage"

instSizeRegex = "Info: Instruments size : (.+) bytes\\."
songSizeRegex = "Info: Song '(.+)' size: (.+) bytes\\."
totalSizeRegex = "Info: Total assembly file size: (.+) bytes\\."
youMustSetRegex = "Info: ([^\n]+, you must set [^\n]+\\.)"

songNameRegex = 'Song[^\n]+Name="([^"]+)' # Song[anything but newline]Name="[anything but "]"
songFolderNameRegex = 'Song[^\n]+Folder="([^"]+)'

dpcmFileNameRegex = 'music_(.+)_bank(.+).dmc'

dpcmAlignerName = "dpcm"
usedFolderName = "Used in the game"

musicFolder = sys.path[0]
tmpFolder = musicFolder + "/../TMP/"

if __name__ == "__main__":
    import os, sys, glob, filecmp
    import re
    import argparse
    import subprocess
    import binpacking
    parser = argparse.ArgumentParser()
    parser.add_argument('fsPath', metavar='famistudioPath', help='Path to FamiStudio.dll from FamiStudio 4.2.1')
    args = parser.parse_args()
    
    modulePath = musicFolder+"/MODULES/music_master.fms"
    
    fsPath = args.fsPath
    
    if not(os.path.exists(fsPath) or os.path.exists(fsPath + "/FamiStudio.dll")):
        print(f"{fsPath} is not a valid path to FamiStudio.dll or a directory with it.")
        exit(1)
        
    if os.path.isdir(fsPath) and os.path.exists(fsPath + "/FamiStudio.dll"):
        fsPath += "/FamiStudio.dll"
    
    # Check FamiStudio version
    print("\n==== Checking FamiStudio version...")
    proc = subprocess.run(['dotnet', fsPath, '-help'], capture_output=True)
    fsVer = re.findall(famistudioHelpRegex, proc.stdout.decode())[0]
    fsVer = [int(x) for x in fsVer.split(".")]
    fsVer = fsVer[0]*1000_000 + fsVer[1]*1000 + fsVer[2]
    if (fsVer < 400_200_1):
        print("FamiStudio version is less than 4.2.1, please update")
        exit(1)

    # Get FamiStudio text file
    print("\n==== Exporting a FamiStudio text file for processing...")
    fsTxtPath = tmpFolder + "/music_fs.txt"

    proc = subprocess.run(['dotnet', fsPath, modulePath, 'famistudio-txt-export', fsTxtPath], capture_output=True)
    fsTxtFile = open(fsTxtPath)
    fsTxt = "\n".join(fsTxtFile.readlines())
    os.remove(fsTxtPath)

    songNames = re.findall(songNameRegex, fsTxt)
    folderNames = re.findall(songFolderNameRegex, fsTxt)

    if len(songNames) == 0:
        LookupError("Amount of valid songs in the FS txt file is 0.")
        exit(2)
    
    if not(dpcmAlignerName in songNames):
        LookupError("DPCM aligner not found in FS txt file.")
        exit(2)
    elif not(usedFolderName in folderNames):
        LookupError(f"None of the songs are in the folder \"{usedFolderName}\".")
        exit(2)

    dpcmidx = songNames.index(dpcmAlignerName)
    neededSongs = [i for i in range(len(songNames)) if folderNames[i] == usedFolderName]
    neededSongsCommaSep = ",".join([str(i) for i in neededSongs])

    # Get instrument and song sizes
    print("\n==== Getting sizes of songs and instruments...")
    tmpAsmPath = tmpFolder + "music_all.s"
    tmpAsmPrefix = tmpFolder + "music_all"

    proc = subprocess.run(['dotnet', fsPath, modulePath, 'famistudio-asm-export', tmpAsmPath, '-famistudio-asm-format:ca65', '-famistudio-asm-force-dpcm-bankswitch', f'-export-songs:{neededSongsCommaSep},{dpcmidx}'], capture_output=True)
    os.remove(tmpAsmPath)

    for i in glob.glob(f"{tmpAsmPrefix}*.dmc"):
        os.remove(i)
    
    cmdOutput = proc.stdout.decode()
    
    # Get size of all instruments
    instsize = re.findall(instSizeRegex, cmdOutput)
    if (len(instsize) != 1):
        LookupError("Instrument size not correctly present in the text.")
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
    dpcmFiles = []
    optionsToSet = []

    print("\n==== Running export processes of each music data bank...")

    for i in range(len(bins)):
        idxs = ",".join([str(j[0]) for j in bins[i]])

        exportPrefix = tmpFolder+f"music_{i+1}_tmp"
        # exportPrefix = f"{musicFolder}/EXPORTS/music_{i+1}"
        exportPath = f"{exportPrefix}.s"

        proc = subprocess.run(['dotnet', fsPath, modulePath, 'famistudio-asm-export', exportPath, '-famistudio-asm-format:ca65', '-famistudio-asm-generate-list', f'-export-songs:{dpcmidx},{idxs}'], capture_output=True)
        output = proc.stdout.decode()

        print(f"== Info on bank {i}:")
        print("\t" + re.search(totalSizeRegex, output).group())
        
        dpcmFiles += glob.glob(f"{exportPrefix}*.dmc")
        optionsToSet += re.findall(youMustSetRegex, output)

    # Check the DPCM files for being identical
    dpcmExportPrefix = tmpFolder+f"music_tmp"
    # dpcmExportPrefix = f"{musicFolder}/EXPORTS/music"

    print("\n==== Checking if the DPCM files are identical...")
    for i in range(len(dpcmFiles)):
        dpcmFiles[i] = (
            dpcmFiles[i],
            re.findall(dpcmFileNameRegex, os.path.basename(dpcmFiles[i]))[0]
        )

    dpcmError = False
    dpcmBanks = list(set([i[1][1] for i in dpcmFiles]))
    for bank in dpcmBanks:
        bankDpcmError = False
        dpcmFilesOfBank = list(set(i for i in dpcmFiles if i[1][1] == bank))
        for file in dpcmFilesOfBank:
            if not(filecmp.cmp(file[0], dpcmFilesOfBank[0][0], shallow=False)):
                print(f"DPCM Data Bank {file[1][1]} of music data bank {file[1][0]} differs from that of music data bank 0.")
                bankDpcmError = True
                dpcmError = True
        if not bankDpcmError:
            os.rename(dpcmFilesOfBank[0][0], f"{dpcmExportPrefix}_bank{bank}.dmc")
            dpcmFilesOfBank.pop(0)
        for i in dpcmFilesOfBank:
            os.remove(i[0])

    if dpcmError:
        ValueError("DPCM files were not identical. Please check the dpcm aligner for containing all samples.")
        exit(4)    
    
    # Export bank lengths table
    print("\n==== Bank lengths table:")
    print(f"\t.byte {', '.join([str(len(i)) for i in bins[:-1]])}, $FF ;last bank is marked with an FF to always stop bank picking")

    # Print which options to set
    print("\n==== Don't forget to set these options in the sound driver:")
    print("\n".join(list(set(optionsToSet))))

    print("\n==== Please launch parse_fs_files.py now.")