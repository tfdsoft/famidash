#!/usr/bin/env python3

import sys
import pathlib
import itertools

famistudioHelpRegex = "FamiStudio (.+) Command-Line Usage"

instSizeRegex = "Info: Instruments size : (.+) bytes\\."
songSizeRegex = "Info: Song '(.+)' size: (.+) bytes\\."
totalSizeRegex = "Info: Total assembly file size: (.+) bytes\\."
youMustSetRegex = "Info: ([^\n]+, you must set [^\n]+\\.)"
actualOptionRegex = "set (FAMISTUDIO_[^ \n=]+ = [^ \n.]+)"

songNameRegex = 'Song[^\n]+Name="([^"]+)'

exportStemPrefix = "music"

dpcmFileNameRegex = f'{exportStemPrefix}_(.+)_bank(.+).dmc'

finalSongInListName = "max"

asmMusicDataName = fr'music_data_famidash_{exportStemPrefix}'
asmAmountOfSongsRegex = fr'({asmMusicDataName}:.*?\n\t\.byte )(\d+)'
asmDpcmSongHeaderMatchRegex = lambda dpcmAlignerName : r'(?m:^; \d+ : ' + dpcmAlignerName + r'.*?$\n(?:^\t\.word @song\d+.*?$\n){5}^\t.word \d+,\d+.*?$\n)'
asmDpcmSongHeaderIdxRegex = lambda dpcmAlignerName : r'(?m:^; \d+ : ' + dpcmAlignerName + r'.*?$\n(?:^\t\.word @song(\d+).*?$\n){5}^\t.word \d+,\d+.*?$\n)'
asmDpcmSongMatchRegex = lambda x : r'(?ms:(^@song' + x + r'\S*:.*?)(?=^@song(?!' + x + r')))' #BUG: currently doesn't match if the dpcm song is the last

datBankSegPrefix = "DAT_BANK_"
dmcBankMetaUnused = 63  # a special dmc bank for shit to go unused
lastDatBank = 0x33

musicFolder = pathlib.Path(sys.path[0]).resolve()
tmpFolder = (musicFolder.parent / "TMP").resolve()

# Because itertools is old af sometimes
def batched(iterable, n, *, strict=False):
    # batched('ABCDEFG', 3) → ABC DEF G
    if n < 1:
        raise ValueError('n must be at least one')
    iterator = iter(iterable)
    while batch := tuple(itertools.islice(iterator, n)):
        if strict and len(batch) != n:
            raise ValueError('batched(): incomplete batch')
        yield batch

# Local version of FamiStudio function
# Source code @ https://github.com/BleuBleu/FamiStudio/blob/master/FamiStudio/Source/Utils/Utils.cs
# Function name: Utils.MakeNiceAsmName
# Make sure to keep this updated
def makeNiceAsmName(name : str, allowDash : bool = False) -> str:
    niceName = ""
    for c in name:
        if (c.isalnum()):
            niceName += c.lower();
        elif (c.isspace() and niceName[-1] != '_'):
            niceName += '_'
        elif (c == '-'):
            niceName += '-' if allowDash else '_'
        elif (c == '_'):
            niceName += c
    return niceName

def convertTextToMenuFormat(name : str | None) -> str | None:
    if name == None:
        return None
    niceName = ""
    for c in name:
        if (c.isalpha() and c.isupper()) or (c.isdigit()):
            niceName += c
        elif (c.isspace()):
            niceName += "$"
        else:
            print(f"Warning: illegal character '{c}' detected in sound text string '{name}'. Will be omitted.")
    return niceName

def processNSFTrackAuthorMetadata(author : str | dict) -> str:
    if isinstance(author, str):
        return author
    if author == None:
        print(f"Warning: NSF author metadata not specified")
        return "[NOT SPECIFIED]"
    if not isinstance(author, dict):
        print(f"Warning: NSF author metadata '{author}' is neither a string nor a dictionary")
        return "[ERROR]"
    if 'original' in author.keys() and 'cover' in author.keys():
        return f"Original by {author['original']}, covered by {author['cover']}"
    print(f"Warning: Invalid NSF author metadata structure '{author}'")
    return "[ERROR]"

def processMetadata(metadata : dict) -> dict:
    songlist = [i for i in metadata['songs'] if 'fmsSongName' in i.keys()] # filter out commented out songs

    # Get song names
    songNameList = ['song_' + makeNiceAsmName(i.get('fmsSongName'), False) for i in songlist]
    vsSongNameList = ['song_' + makeNiceAsmName(i.get('fmsSongName'), False) for i in songlist if i.get('vsSystemEnabled') == True]

    # Optimize text usage
    upperTextList = [i.get('upperText') for i in songlist]
    lowerTextList = [i.get('lowerText') for i in songlist]
    totalTextList = [i for i in upperTextList + lowerTextList if i]
    totalTextSet = tuple(sorted(set(totalTextList), key=lambda x : totalTextList.index(x)))

    # Get indices, convert to displayable format
    upperIdxList = [totalTextSet.index(i) if i else None for i in upperTextList]
    lowerIdxList = [totalTextSet.index(i) if i else None for i in lowerTextList]
    processedTextList = tuple(map(convertTextToMenuFormat, totalTextSet))

    # Convert to C
    outputStringsList = [f'const char musicSoundTextString{i:02X}[{len(s):2}] = "{s}";' for i, s in enumerate(processedTextList)]
    upperArrayList = [f'\tmusicSoundTextString{i:02X},' if i != None else '\tNULL,' for i in upperIdxList]
    upperSizeArrayList = [f'\tsizeof(musicSoundTextString{i:02X}),' if i != None else '\t0,' for i in upperIdxList]
    lowerArrayList = [f'\tmusicSoundTextString{i:02X},' if i != None else '\tNULL,' for i in lowerIdxList]
    lowerSizeArrayList = [f'\tsizeof(musicSoundTextString{i:02X}),' if i != None else '\t0,' for i in lowerIdxList]

    if args.outputFolder.name == 'lvlset_Z':        

        #ORIGINAL ARTISTS 1+2

        # Optimize text usage
        upperOrigArtistTextList = [i.get('upperOrigArtistText') for i in songlist]
        lowerOrigArtistTextList = [i.get('lowerOrigArtistText') for i in songlist]
        totalOrigArtistTextList = [i for i in upperOrigArtistTextList + lowerOrigArtistTextList if i]
        totalOrigArtistTextSet = tuple(sorted(set(totalOrigArtistTextList), key=lambda x : totalOrigArtistTextList.index(x)))

        CoveringArtist1TextList = [i.get('CoveringArtist1Text') for i in songlist]
        CoveringArtist2TextList = [i.get('CoveringArtist2Text') for i in songlist]
        CoveringArtist3TextList = [i.get('CoveringArtist3Text') for i in songlist]
        CoveringArtist4TextList = [i.get('CoveringArtist4Text') for i in songlist]

        totalCoveringArtistTextList = [i for i in CoveringArtist4TextList + CoveringArtist3TextList + CoveringArtist2TextList + CoveringArtist1TextList if i]
        totalCoveringArtistTextSet = tuple(sorted(set(totalCoveringArtistTextList), key=lambda x : totalCoveringArtistTextList.index(x)))

        # Get indices, convert to displayable format
        upperOrigArtistIdxList = [totalOrigArtistTextSet.index(i) if i else None for i in upperOrigArtistTextList]
        lowerOrigArtistIdxList = [totalOrigArtistTextSet.index(i) if i else None for i in lowerOrigArtistTextList]
        processedOrigArtistTextList = tuple(map(convertTextToMenuFormat, totalOrigArtistTextSet))

        CoveringArtist1IdxList = [totalCoveringArtistTextSet.index(i) if i else None for i in CoveringArtist1TextList]
        CoveringArtist2IdxList = [totalCoveringArtistTextSet.index(i) if i else None for i in CoveringArtist2TextList]
        CoveringArtist3IdxList = [totalCoveringArtistTextSet.index(i) if i else None for i in CoveringArtist3TextList]
        CoveringArtist4IdxList = [totalCoveringArtistTextSet.index(i) if i else None for i in CoveringArtist4TextList]
        processedCoveringArtistTextList = tuple(map(convertTextToMenuFormat, totalCoveringArtistTextSet))


        # Convert to C
        outputOrigArtistStringsList = [f'const char musicSoundOrigArtistTextString{i:02X}[{len(s):2}] = "{s}";' for i, s in enumerate(processedOrigArtistTextList)]
        upperOrigArtistArrayList = [f'\tmusicSoundOrigArtistTextString{i:02X},' if i != None else '\tNULL,' for i in upperOrigArtistIdxList]
        upperOrigArtistSizeArrayList = [f'\tsizeof(musicSoundOrigArtistTextString{i:02X}),' if i != None else '\t0,' for i in upperOrigArtistIdxList]
        lowerOrigArtistArrayList = [f'\tmusicSoundOrigArtistTextString{i:02X},' if i != None else '\tNULL,' for i in lowerOrigArtistIdxList]
        lowerOrigArtistSizeArrayList = [f'\tsizeof(musicSoundOrigArtistTextString{i:02X}),' if i != None else '\t0,' for i in lowerOrigArtistIdxList]

        outputCoveringArtistStringsList = [f'const char musicSoundCoveringArtistTextString{i:02X}[{len(s):2}] = "{s}";' for i, s in enumerate(processedCoveringArtistTextList)]
        CoveringArtist1ArrayList = [f'\tmusicSoundCoveringArtistTextString{i:02X},' if i != None else '\tNULL,' for i in CoveringArtist1IdxList]
        CoveringArtist1SizeArrayList = [f'\tsizeof(musicSoundCoveringArtistTextString{i:02X}),' if i != None else '\t0,' for i in CoveringArtist1IdxList]
        CoveringArtist2ArrayList = [f'\tmusicSoundCoveringArtistTextString{i:02X},' if i != None else '\tNULL,' for i in CoveringArtist2IdxList]
        CoveringArtist2SizeArrayList = [f'\tsizeof(musicSoundCoveringArtistTextString{i:02X}),' if i != None else '\t0,' for i in CoveringArtist2IdxList]
        CoveringArtist3ArrayList = [f'\tmusicSoundCoveringArtistTextString{i:02X},' if i != None else '\tNULL,' for i in CoveringArtist3IdxList]
        CoveringArtist3SizeArrayList = [f'\tsizeof(musicSoundCoveringArtistTextString{i:02X}),' if i != None else '\t0,' for i in CoveringArtist3IdxList]
        CoveringArtist4ArrayList = [f'\tmusicSoundCoveringArtistTextString{i:02X},' if i != None else '\tNULL,' for i in CoveringArtist4IdxList]
        CoveringArtist4SizeArrayList = [f'\tsizeof(musicSoundCoveringArtistTextString{i:02X}),' if i != None else '\t0,' for i in CoveringArtist4IdxList]

        #COVERING ARTISTS 1+2

        # Optimize text usage


        # Get indices, convert to displayable format

        # Convert to C

        #COVERING ARTISTS 3+4

        # Optimize text usage
#        upperOrigArtistTextList = [i.get('upperOrigArtistText') for i in songlist]
#        lowerOrigArtistTextList = [i.get('lowerOrigArtistText') for i in songlist]
#        totalOrigArtistTextList = [i for i in upperOrigArtistTextList + lowerOrigArtistTextList if i]
#        totalOrigArtistTextSet = tuple(sorted(set(totalOrigArtistTextList), key=lambda x : totalOrigArtistTextList.index(x)))

        # Get indices, convert to displayable format
#        upperOrigArtistIdxList = [totalOrigArtistTextSet.index(i) if i else None for i in upperOrigArtistTextList]
#        lowerOrigArtistIdxList = [totalOrigArtistTextSet.index(i) if i else None for i in lowerOrigArtistTextList]
#        processedOrigArtistTextList = tuple(map(convertTextToMenuFormat, totalOrigArtistTextSet))

        # Convert to C
#        outputOrigArtistStringsList = [f'const char musicSoundOrigArtistTextString{i:02X}[{len(s):2}] = "{s}";' for i, s in enumerate(processedOrigArtistTextList)]
#        upperOrigArtistArrayList = [f'\tmusicSoundOrigArtistTextString{i:02X},' if i != None else '\tNULL,' for i in upperOrigArtistIdxList]
#        upperOrigArtistSizeArrayList = [f'\tsizeof(musicSoundOrigArtistTextString{i:02X}),' if i != None else '\t0,' for i in upperOrigArtistIdxList]
#        lowerOrigArtistArrayList = [f'\tmusicSoundOrigArtistTextString{i:02X},' if i != None else '\tNULL,' for i in lowerOrigArtistIdxList]
#        lowerOrigArtistSizeArrayList = [f'\tsizeof(musicSoundOrigArtistTextString{i:02X}),' if i != None else '\t0,' for i in lowerOrigArtistIdxList]



    else:
        upperOrigArtistTextList = 0
        lowerOrigArtistTextList = 0
        totalOrigArtistTextList = 0
        totalOrigArtistTextSet = 0

        # Get indices, convert to displayable format
        upperOrigArtistIdxList = 0
        lowerOrigArtistIdxList = 0
        processedOrigArtistTextList = 0

        # Convert to C
        outputOrigArtistStringsList = 0
        upperOrigArtistArrayList = 0
        upperOrigArtistSizeArrayList = 0
        lowerOrigArtistArrayList = 0
        lowerOrigArtistSizeArrayList = 0
        
        CoveringArtist1TextList = 0
        CoveringArtist2TextList = 0
        CoveringArtist3TextList = 0
        CoveringArtist4TextList = 0
        totalCoveringArtistTextList = 0
        totalCoveringArtistTextSet = 0

        CoveringArtist1IdxList = 0
        CoveringArtist2IdxList = 0
        CoveringArtist3IdxList = 0
        CoveringArtist4IdxList = 0

        outputCoveringArtistStringsList = 0
        CoveringArtist1ArrayList = 0
        CoveringArtist1SizeArrayList = 0
        CoveringArtist2ArrayList = 0
        CoveringArtist2SizeArrayList = 0
        CoveringArtist3ArrayList = 0
        CoveringArtist3SizeArrayList = 0
        CoveringArtist4ArrayList = 0
        CoveringArtist4SizeArrayList = 0
        
        processedCoveringArtistTextList = 0


    # Get SFX names
    sfxTextList = [i['text'] for i in metadata['SFX'] if 'text' in i.keys() and i['text']]
    sfxTextSet = tuple(sorted(set(sfxTextList), key=lambda x : sfxTextList.index(x)))
    sfxIdxList = [sfxTextSet.index(i) for i in sfxTextList]
    processedSfxTextList = tuple(map(convertTextToMenuFormat, sfxTextSet))

    # Convert to C
    sfxOutputStringsList = [f'const char sfxSoundTextString{i:02X}[{len(s):2}] = "{s}";' for i, s in enumerate(processedSfxTextList)]
    sfxArrayList = [f'\tsfxSoundTextString{i:02X},' if i != None else '\tNULL,' for i in sfxIdxList]
    sfxSizeArrayList = [f'\tsizeof(sfxSoundTextString{i:02X}),' if i != None else '\t0,' for i in sfxIdxList]

    # Get PCM data
    pcmlist = [i for i in metadata['PCM'] if set(['segment', 'path', 'sampleRateNTSC', 'sampleRatePAL']).issubset(set(i.keys()))]
    bankIncludesList = [f"\t.byte <.bank(pcmData{i})" for i in range(len(pcmlist))]
    sampleRateNTSCList = [f"\t.byte {i['sampleRateNTSC']}" for i in pcmlist]
    sampleRatePALList = [f"\t.byte {i['sampleRatePAL']}" for i in pcmlist]
    pcmHeaderList = ['', '; PCM includes']
    for idx, i in enumerate(pcmlist):
        pcmHeaderList += [f'.segment "{i["segment"]}"', f'\tpcmData{idx}:', f'\t\t.incbin "{i["path"]}"']

    # Get NSF metadata
    nsfMetaList = [i.get('nsfData') for i in (songlist + metadata['SFX'] + metadata['PCM']) if 'nsfData' in i.keys()]
    # For now, don't warn people of missing NSF metadata, but do warn about incomplete data
    trackLabelList = [i.get('trackLabel') for i in nsfMetaList]
    trackAuthorList = [processNSFTrackAuthorMetadata(i.get('trackAuthor')) for i in nsfMetaList]
    loopList = [i.get('looped') == True for i in nsfMetaList] # do not warn, assume false if not present
    defTime = -1 & 0xFFFFFFFF # default time
    durationFadeList = [defTime if i else 0 for i in loopList] # either 0 for None, or -1 for default
    durationNTSCList = [i['durationNTSC'] * (2 if loopList[idx] else 1) if 'durationNTSC' in i.keys() else defTime for idx, i in enumerate(nsfMetaList)]
    durationPALList = [i['durationPAL'] * (2 if loopList[idx] else 1) if 'durationPAL' in i.keys() else defTime  for idx, i in enumerate(nsfMetaList)]

    return {
        'filteredSongList': songlist,
        'soundTextData': {
            'songNames': songNameList,
            'vsSongNames': vsSongNameList,
            'soundTextStrings': outputStringsList,
            'upperPtrs': upperArrayList,
            'upperSizes': upperSizeArrayList,
            'lowerPtrs': lowerArrayList,
            'lowerSizes': lowerSizeArrayList,
            'upperOrigArtistPtrs': upperOrigArtistArrayList,
            'upperOrigArtistSizes': upperOrigArtistSizeArrayList,
            'lowerOrigArtistPtrs': lowerOrigArtistArrayList,
            'lowerOrigArtistSizes': lowerOrigArtistSizeArrayList,
            'origartistTextStrings': outputOrigArtistStringsList,
            'CoveringArtist1Ptrs': CoveringArtist1ArrayList,
            'CoveringArtist1Sizes': CoveringArtist1SizeArrayList,
            'CoveringArtist2Ptrs': CoveringArtist2ArrayList,
            'CoveringArtist2Sizes': CoveringArtist2SizeArrayList,
            'CoveringArtist3Ptrs': CoveringArtist3ArrayList,
            'CoveringArtist3Sizes': CoveringArtist3SizeArrayList,
            'CoveringArtist4Ptrs': CoveringArtist4ArrayList,
            'CoveringArtist4Sizes': CoveringArtist4SizeArrayList,
            'coveringartistTextStrings': outputCoveringArtistStringsList,
            'sfxSoundTextStrings': sfxOutputStringsList,
            'sfxPtrs': sfxArrayList,
            'sfxSizes': sfxSizeArrayList,
        },
        'nsfMetadata': {
            'trackLabelList': trackLabelList,
            'trackAuthorList': trackAuthorList,
            'durationNTSCList': durationNTSCList,
            'durationPALList': durationPALList,
            'durationFadeList': durationFadeList
        },
        'pcmMetadata': {
            'bankTable': bankIncludesList,
            'sampleRateNTSC': sampleRateNTSCList,
            'sampleRatePAL': sampleRatePALList,
            'headerData': pcmHeaderList
        },
    'dpcmAlignerName': metadata['dpcmAligner']
}


if __name__ == "__main__":
    # install binpacking and pyjson5
    install_list = []

    import importlib.util
    import subprocess
    import sys
    spec = importlib.util.find_spec('binpacking')
    if spec is None:
        install_list.append('binpacking')

    spec = importlib.util.find_spec('pyjson5')
    if spec is None:
        install_list.append('pyjson5')

    if len(install_list):
        subprocess.check_call([sys.executable, '-m', 'pip', 'install', *install_list])

    import os, filecmp
    import re
    import argparse
    import binpacking
    import pyjson5
    from collections.abc import Iterable
    
    def checkErr(proc : subprocess.CompletedProcess):
        if (proc.returncode != 0):
            print(f"AN ERROR HAS OCCURED WITHIN A SUBPROCESS!\n======\nstdout dump:\n===\n{proc.stdout.decode()}\n===\nstderr dump:\n===\n{proc.stderr.decode()}\n===")
            proc.check_returncode() # exits
    
    parser = argparse.ArgumentParser()
    parser.add_argument('-f', '--famistudioCommand', required=True, nargs="+",
                help='Command to launch FamiStudio >= 4.3.0')
    parser.add_argument('-m', '--metadata', type=pathlib.Path, required=True,
                help='Path to json5 file with music metadata specifications')
    parser.add_argument('-o', '--outputFolder', type=pathlib.Path, required=True,
                help='Output folder for the include files')
    args = parser.parse_args()
    
    print(args.outputFolder)
    
    if args.outputFolder.name == 'lvlset_Z':
        modulePath = musicFolder / "MODULES" / "the album.fms"
    else:
        modulePath = musicFolder / "MODULES" / "music_master.fms"
    
    metadataPath = args.metadata

    fsCmd = args.famistudioCommand

    # Load metadata file
    print("\n==== Loading metadata...")
    if not(metadataPath.is_file()):
        print("Path to the metadata json5 file is invalid. Please specify a proper file.")
        exit(1)
    with metadataPath.open() as metafile:
        metadata = pyjson5.decode_io(metafile)
    
    # Process metadata
    print("\n==== Processing metadata...")
    processed_metadata = processMetadata(metadata)

    # Check FamiStudio version
    print("\n==== Checking FamiStudio version...")
    proc = subprocess.run([*fsCmd, '-help'], capture_output=True)
    checkErr(proc)
    fsVer = re.findall(famistudioHelpRegex, proc.stdout.decode())[0]
    fsVer = [int(x) for x in fsVer.split(".")]
    fsVer = fsVer[0]*1000_000 + fsVer[1]*1000 + fsVer[2]
    if (fsVer < 400_300_0):
        print("FamiStudio version is less than 4.3.0, please update")
        exit(1)

    # Get FamiStudio text file
    print("\n==== Exporting a FamiStudio text file for processing...")
    fsTxtPath = tmpFolder / "{exportStemPrefix}_fs.txt"

    proc = subprocess.run([*fsCmd, modulePath, 'famistudio-txt-export', fsTxtPath], capture_output=True)
    checkErr(proc)
    if fsTxtPath.is_file():
        fsTxt = fsTxtPath.read_text()
        fsTxtPath.unlink(missing_ok = True)
    else:
        print("Somehow the famistudio-txt-export process didn't create a valid text file.")
        exit(2)
    
    dpcmAlignerName = processed_metadata['dpcmAlignerName']

    songNames = re.findall(songNameRegex, fsTxt)
    neededSongNames = sorted(i['fmsSongName'] for i in processed_metadata['filteredSongList'])
    if any(i not in songNames for i in neededSongNames):
        print('Songs ', ", ".join([f'"{i}"' for i in neededSongNames if i not in songNames]), ' not found in FamiStudio module. Please check the song names', sep="")
        exit(2)
    neededSongs = [songNames.index(i) for i in neededSongNames]

    if len(songNames) == 0:
        print("No valid songs found in FS txt file.")
        exit(2)
    
    if not(dpcmAlignerName in songNames):
        print("DPCM aligner not found in FS txt file.")
        exit(2)

    dpcmidx = songNames.index(dpcmAlignerName)
    neededSongsCommaSep = ",".join([str(i) for i in neededSongs])

    # Get instrument and song sizes
    print("\n==== Getting sizes of songs and instruments...")
    tmpAsmPath = tmpFolder / f"{exportStemPrefix}_all.s"

    proc = subprocess.run([*fsCmd, modulePath, 'famistudio-asm-export', tmpAsmPath, '-famistudio-asm-format:ca65', '-famistudio-asm-force-dpcm-bankswitch', f'-export-songs:{neededSongsCommaSep},{dpcmidx}'], capture_output=True)
    tmpAsmPath.unlink(missing_ok = True)
    checkErr(proc)

    for i in tmpFolder.glob(f"{exportStemPrefix}_all*.dmc"):
        i.unlink(missing_ok = True)
    
    cmdOutput = proc.stdout.decode()
    
    # Get size of all instruments
    instsize = re.findall(instSizeRegex, cmdOutput)
    if (len(instsize) != 1):
        print("Instrument size not correctly present in the FamiStudio command output.")
        exit(3)
    instsize = int(instsize[0])
    print(f"== Total maximum size of data in a bank is {8192 - (instsize / 5 * 3)} bytes")

    # Get song sizes in bytes
    songsizestrings = re.findall(songSizeRegex, cmdOutput)
    songsizes = [(songNames.index(i[0]), i[0], int(i[1])) for i in songsizestrings if i[0] != dpcmAlignerName]
    bins = binpacking.to_constant_volume(songsizes, 8192-(instsize / 5 * 3), 2)
    for i in range(len(bins)):
        print(f"== Bank {i}:")
        print("\t- Songs: "+", ".join([j[1] for j in bins[i]]))
        print("\t- Total approx. size:", sum([j[2] for j in bins[i]]), "bytes")

    # Export the music_X.s files
    exportPath = args.outputFolder
    if not exportPath.is_dir():
        exportPath.mkdir(parents=True)
    
    dpcmFiles = []
    optionsToSet = []
    masterSonglist = []

    print("\n==== Running export processes of each music data bank...")

    for i in range(len(bins)):
        idxs, names, _ = zip(*sorted(bins[i]))
        idxs = ','.join(map(str, idxs))
        names = list(map(makeNiceAsmName, names))

        asmExportStem = f"{exportStemPrefix}_{i}"
        asmExportPath = exportPath / f"{asmExportStem}.s"

        proc = subprocess.run([*fsCmd, modulePath, 'famistudio-asm-export', asmExportPath, '-famistudio-asm-format:ca65', f'-export-songs:{dpcmidx},{idxs}'], capture_output=True)
        output = proc.stdout.decode()
        checkErr(proc)

        print(f"== Info on bank {i}:")
        print("\t" + re.search(totalSizeRegex, output).group())

        # Run the asm file through a few regexes:
        captData = []
        asmExportData = asmExportPath.read_text()
        for capt, og, repl in [
            # Decrement song count
            (None, asmAmountOfSongsRegex, lambda x : f'{x.group(1)}{int(x.group(2)) - 1}'),
            # Make the label unique
            (None, asmMusicDataName, f"{asmMusicDataName}{i}"),
            # Remove DPCM aligner from header
            (asmDpcmSongHeaderIdxRegex(dpcmAlignerName), asmDpcmSongHeaderMatchRegex(dpcmAlignerName), "; The DPCM aligner used to be here\n"),
            # Remove DPCM aligner song data
            (None, lambda : asmDpcmSongMatchRegex(captData[2][0]), "; The DPCM aligner used to be here\n")
        ]:
            if capt != None:
                captData.append(re.findall(capt, asmExportData))
            else:
                captData.append(None)

            if callable(og):
                asmExportData = re.sub(og(), repl, asmExportData)
            else:
                asmExportData = re.sub(og, repl, asmExportData)
        asmExportPath.write_text(asmExportData)

        dpcmFiles += exportPath.glob(f"{asmExportStem}*.dmc")
        optionsToSet += re.findall(youMustSetRegex, output)
        masterSonglist += names

    masterSonglist.append(finalSongInListName)

    # Check the DPCM files for being identical
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
            (exportPath / f"{exportStemPrefix}_bank{bank}.dmc").unlink(missing_ok = True)
            dpcmFilesOfBank[0][0].rename(exportPath / f"{exportStemPrefix}_bank{bank}.dmc")
            dpcmFilesOfBank.pop(0)
        [i[0].unlink(missing_ok = True) for i in dpcmFilesOfBank]

    if dpcmError:
        ValueError("DPCM files were not identical. Please check the dpcm aligner for containing all samples.")
        exit(4)    

    dpcmBanks = sorted(list(map(int, dpcmBanks)))
    
    print("\n==== Exporting miscellaneous files...")
    print("== musicPlayRoutines.s")
    # Export bank lengths table
    bank_table_data = [
        '; Generated by export.py',
        '',
        ".if .not(useConstInitPtr)",
        "music_data_locations_lo:",
        f"\t.byte " + ", ".join([f"<{asmMusicDataName}{i}" for i in range(len(bins))]),
        "music_data_locations_hi:",
        f"\t.byte " + ", ".join([f">{asmMusicDataName}{i}" for i in range(len(bins))]),
        ".endif",
        "",
        "music_counts:",
        f"\t.byte {', '.join([str(len(i)) for i in bins[:-1]])}, $FF ;last bank is marked with an FF to always stop bank picking"
        ]
    (exportPath / "musicPlayRoutines.s").write_text("\n".join(bank_table_data))

    # Export C songlist
    print("== musicDefines.h")
    (exportPath / "musicDefines.h").write_text(
        "\n".join([f"#define song_{id} {i}" for i, id in enumerate(masterSonglist)]))

    # Export asm songlist
    print("== music_songlist.inc")
    (exportPath / "music_songlist.inc").write_text(
        "\n".join([f"song_{id} = {i}" for i, id in enumerate(masterSonglist)]))

    # Export segment assignment
    print("== music_data_header.s")
    lastAfterDatBank = lastDatBank + 1
    firstDmcBank = lastAfterDatBank - len([i for i in dpcmBanks if i != dmcBankMetaUnused])
    firstMusBank = firstDmcBank - len(bins)
    header_data = [
        '; Generated by export.py using data in metadata.json',
        '',
        '; Music data banks',
        f'.segment "{datBankSegPrefix}{firstMusBank:02X}"',
        '\tfirstMusicBankPtr := *',
        f'\t.include "{exportStemPrefix}_0.s"'
    ]
    if (len(bins) > 1):
        header_data += [f'.segment "{datBankSegPrefix}{i+firstMusBank:02X}"\n\t.include "{exportStemPrefix}_{i}.s"' for i in range(1, len(bins))]

    if (len(dpcmBanks)):
        header_data += [
            '',
            '; DMC banks',
            f'.segment "{datBankSegPrefix}{firstDmcBank:02X}"',
            '\tfirstDMCBankPtr := *',
            f'\t.incbin "{exportStemPrefix}_bank{dpcmBanks[0]}.dmc"',
        ]
        header_data += [f'.segment "{datBankSegPrefix}{i+firstDmcBank:02X}"\n\t.incbin "{exportStemPrefix}_bank{bank}.dmc"' for i, bank in enumerate(dpcmBanks[1:], 1) if bank != dmcBankMetaUnused]

    header_data += processed_metadata['pcmMetadata']['headerData']

    header_data += [
        '',
        '; Constants',
        'FIRST_MUSIC_BANK = .bank(firstMusicBankPtr)',
    ]
    if (len(dpcmBanks)):
        header_data.append('FIRST_DMC_BANK = .bank(firstDMCBankPtr)')

    (exportPath / "music_data_header.s").write_text("\n".join(header_data))

    print(f"== {exportStemPrefix}_soundTextTables.h")
    processed_soundtext_metadata = processed_metadata['soundTextData']
    if args.outputFolder.name == 'lvlset_Z':

        soundTextTextData = [
            '// Generated by export.py using data in metadata.json',
            '',
            '#if !__VS_SYSTEM',
            '',
            *processed_soundtext_metadata['soundTextStrings'],
            '', '',
            'const char* const xbgmtextsUpper[] = {',
            *processed_soundtext_metadata['upperPtrs'],
            '};',
            '',
            'const uint8_t xbgmtextsUpperSize[] = {',
            *processed_soundtext_metadata['upperSizes'],
            '};',
            '', '',
            'const char* const xbgmtextsLower[] = {',
            *processed_soundtext_metadata['lowerPtrs'],
            '};',
            '', '',
            'const uint8_t xbgmtextsLowerSize[] = {',
            *processed_soundtext_metadata['lowerSizes'],
            '};',
            '', '',
            *processed_soundtext_metadata['origartistTextStrings'],
            '', '',
            'const char* const xbgmtextsOrigArtistUpper[] = {',
            *processed_soundtext_metadata['upperOrigArtistPtrs'],
            '};',
            '', '',
            'const uint8_t xbgmtextsOrigArtistUpperSize[] = {',
            *processed_soundtext_metadata['upperOrigArtistSizes'],
            '};',
            '', '',
            'const char* const xbgmtextsOrigArtistLower[] = {',
            *processed_soundtext_metadata['lowerOrigArtistPtrs'],
            '};',
            '', '',
            'const uint8_t xbgmtextsOrigArtistLowerSize[] = {',
            *processed_soundtext_metadata['lowerOrigArtistSizes'],
            '};',
            '', '',
            *processed_soundtext_metadata['coveringartistTextStrings'],
            '', '',
            'const char* const xbgmtextsCoveringArtist1[] = {',
            *processed_soundtext_metadata['CoveringArtist1Ptrs'],
            '};',
            '', '',
            'const uint8_t xbgmtextsCoveringArtist1Size[] = {',
            *processed_soundtext_metadata['CoveringArtist1Sizes'],
            '};',
            '', '',
            'const char* const xbgmtextsCoveringArtist2[] = {',
            *processed_soundtext_metadata['CoveringArtist2Ptrs'],
            '};',
            '', '',
            'const uint8_t xbgmtextsCoveringArtist2Size[] = {',
            *processed_soundtext_metadata['CoveringArtist2Sizes'],
            '};',
            '', '',
            'const char* const xbgmtextsCoveringArtist3[] = {',
            *processed_soundtext_metadata['CoveringArtist3Ptrs'],
            '};',
            '', '',
            'const uint8_t xbgmtextsCoveringArtist3Size[] = {',
            *processed_soundtext_metadata['CoveringArtist3Sizes'],
            '};',
            '', '',
            'const char* const xbgmtextsCoveringArtist4[] = {',
            *processed_soundtext_metadata['CoveringArtist4Ptrs'],
            '};',
            '', '',
            'const uint8_t xbgmtextsCoveringArtist4Size[] = {',
            *processed_soundtext_metadata['CoveringArtist4Sizes'],
            '};',
            '', '',
            '#else',
            '',
            'const char* const xbgmtextsUpper[] = {};',
            'const uint8_t xbgmtextsUpperSize[] = {};',
            'const char* const xbgmtextsLower[] = {};',
            'const uint8_t xbgmtextsLowerSize[] = {};',
            'const char* const xbgmtextsOrigArtistUpper[] = {};',
            'const uint8_t xbgmtextsOrigArtistUpperSize[] = {};',
            'const char* const xbgmtextsOrigArtistLower[] = {};',
            'const uint8_t xbgmtextsOrigArtistLowerSize[] = {};',
            'const char* const xbgmtextsCoveringArtist1[] = {};',
            'const uint8_t xbgmtextsCoveringArtist1Size[] = {};',
            'const char* const xbgmtextsCoveringArtist2[] = {};',
            'const uint8_t xbgmtextsCoveringArtist2Size[] = {};',
            'const char* const xbgmtextsCoveringArtist3[] = {};',
            'const uint8_t xbgmtextsCoveringArtist3Size[] = {};',
            'const char* const xbgmtextsCoveringArtist4[] = {};',
            'const uint8_t xbgmtextsCoveringArtist4Size[] = {};',
            '',
            '#endif',
            '', '', '',
            'CODE_BANK_PUSH("RODATA")',
            '',
            '#if !__VS_SYSTEM',
            '',
            'const uint8_t xbgmlookuptable[] = {',
            *[f"\t{i}," for i in processed_soundtext_metadata['songNames']],
            '};', '', '#else', '',
            'const uint8_t xbgmlookuptable[] = {',
            *[f"\t{i}," for i in processed_soundtext_metadata['vsSongNames']],
            '};', '', '#endif', '', 
            'CODE_BANK_POP()',
            ''
        ]
    else:
        soundTextTextData = [
            '// Generated by export.py using data in metadata.json',
            '',
            '#if !__VS_SYSTEM',
            '',
            *processed_soundtext_metadata['soundTextStrings'],
            '', '',
            'const char* const xbgmtextsUpper[] = {',
            *processed_soundtext_metadata['upperPtrs'],
            '};',
            '',
            'const uint8_t xbgmtextsUpperSize[] = {',
            *processed_soundtext_metadata['upperSizes'],
            '};',
            '', '',
            'const char* const xbgmtextsLower[] = {',
            *processed_soundtext_metadata['lowerPtrs'],
            '};',
            '', '',
            'const uint8_t xbgmtextsLowerSize[] = {',
            *processed_soundtext_metadata['lowerSizes'],
            '};',
            '', '',
            '#else',
            '',
            'const char* const xbgmtextsUpper[] = {};',
            'const uint8_t xbgmtextsUpperSize[] = {};',
            'const char* const xbgmtextsLower[] = {};',
            'const uint8_t xbgmtextsLowerSize[] = {};',
            '',
            '#endif',
            '', '', '',
            'CODE_BANK_PUSH("RODATA")',
            '',
            '#if !__VS_SYSTEM',
            '',
            'const uint8_t xbgmlookuptable[] = {',
            *[f"\t{i}," for i in processed_soundtext_metadata['songNames']],
            '};', '', '#else', '',
            'const uint8_t xbgmlookuptable[] = {',
            *[f"\t{i}," for i in processed_soundtext_metadata['vsSongNames']],
            '};', '', '#endif', '', 
            'CODE_BANK_POP()',
            ''
        ]        
    (exportPath / f"{exportStemPrefix}_soundTextTables.h").write_text("\n".join(soundTextTextData))

    print(f"== sfx_soundTextTables.h")
    soundTextSfxTextData = [
        '// Generated by export.py using data in metadata.json',
        '',
        '#if !__VS_SYSTEM',
        '',
        *processed_soundtext_metadata['sfxSoundTextStrings'],
        '', '',
        'const char* const sfxtexts[] = {',
        *processed_soundtext_metadata['sfxPtrs'],
        '};',
        '',
        'const uint8_t sfxtextSizes[] = {',
        *processed_soundtext_metadata['sfxSizes'],
        '};',
        '',
        '#else',
        '',
        'const char* const sfxtexts[] = {};',
        'const uint8_t sfxtextSizes[] = {};',
        '',
        '#endif',
        ''
    ]
    (exportPath / "sfx_soundTextTables.h").write_text("\n".join(soundTextSfxTextData))

    print("== pcm_metadataTables.s")
    pcmMetadataText = [
        '; Generated by export.py using data in metadata.json',
        '',
        'Bank:',
        *processed_metadata['pcmMetadata']['bankTable'],
        '',
        'SampleRate_NTSC:   ; Also applies to Dendy, as it is derived from the CPU speed',
        *processed_metadata['pcmMetadata']['sampleRateNTSC'],
        '',
        'SampleRate_PAL:',
        *processed_metadata['pcmMetadata']['sampleRatePAL'],
        ''
    ]
    (exportPath / "pcm_metadata.s").write_text("\n".join(pcmMetadataText))

    print("== nsf_metadata.s")
    processed_nsf_metadata = processed_metadata['nsfMetadata']
    nsfMetadataText = [
        '; Generated by export.py using data in metadata.json',
        '',
        'RIFFChunkStart "tlbl"',
        *[f'.asciiz "{i}"' for i in processed_nsf_metadata['trackLabelList']],
        '',
        'RIFFChunkStart "taut"',
        *[f'.asciiz "{i}"' for i in processed_nsf_metadata['trackAuthorList']],
        '',
        'RIFFChunkStart "time"',
        '.if REGION = 0',
        *['.dword ' + ", ".join(i) for i in batched(map(str, processed_nsf_metadata['durationNTSCList']), 4)],
        '.else',
        *['.dword ' + ", ".join(i) for i in batched(map(str, processed_nsf_metadata['durationPALList']), 4)],
        '.endif',
        '',
        'RIFFChunkStart "fade"',
        *['.dword ' + ", ".join(i) for i in batched(map(str, processed_nsf_metadata['durationFadeList']), 4)],
        ''
    ]
    (exportPath / "nsf_metadata.s").write_text("\n".join(nsfMetadataText))

    # Print which options to set
    print("\n==== Don't forget to set these options in the sound driver:")
    print("\n".join(re.findall(actualOptionRegex, "\n".join(list(set(optionsToSet))))))

    print("\n==== The export is over, now manually correct stuff as per the contributing guide")
