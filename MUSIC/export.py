#!/usr/bin/env python3

import sys
import pathlib
import itertools

famistudioHelpRegex = r"FamiStudio (?P<version>.+) Command-Line Usage"

instSizeRegex = "Info: Instruments size : (?P<instSize>.+) bytes\\."
songSizeRegex = "Info: Song '(?P<songName>.+)' size: (?P<songSize>.+) bytes\\."
totalSizeRegex = "Info: Total assembly file size: (?P<totalSize>.+) bytes\\."
youMustSetRegex = "Info: ([^\n]+, you must set [^\n]+\\.)"
actualOptionRegex = "set (FAMISTUDIO_[^ \n=]+ = [^ \n.]+)"

fsTxtIndentRegex = r'^(?P<indent>\t*)'
fsTxtLineRegex = r'^(?P<indent>\t*)(?P<type>\S+)\s+(?P<properties>.*)$'
fsTxtPropRegex = r'(?:(\S+)="([^"]*)"\s*)'

exportStemPrefix = "music"

dpcmFileNameRegex = f'{exportStemPrefix}_(?P<musicBank>.+)_bank(?P<dpcmBank>.+).dmc'

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

def pairwise(iterable):
    iterator = iter(iterable)
    a = next(iterator, None)

    for b in iterator:
        yield a, b
        a = b

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
            print(f"Warning: illegal character '{c}' detected in sound test string '{name}'. Will be omitted.")
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
    outputStringsList = [f'const char musicSoundTestString{i:02X}[{len(s):2}] = "{s}";' for i, s in enumerate(processedTextList)]
    upperArrayList = [f'\tmusicSoundTestString{i:02X},' if i != None else '\tNULL,' for i in upperIdxList]
    upperSizeArrayList = [f'\tsizeof(musicSoundTestString{i:02X}),' if i != None else '\t0,' for i in upperIdxList]
    lowerArrayList = [f'\tmusicSoundTestString{i:02X},' if i != None else '\tNULL,' for i in lowerIdxList]
    lowerSizeArrayList = [f'\tsizeof(musicSoundTestString{i:02X}),' if i != None else '\t0,' for i in lowerIdxList]

    OrigArtistTextList = [i.get('originalArtist') for i in songlist]
    totalOrigArtistTextList = [i for i in OrigArtistTextList if i]
    totalOrigArtistTextSet = tuple(sorted(set(totalOrigArtistTextList), key=lambda x : totalOrigArtistTextList.index(x)))

    # Get indices, convert to displayable format
    OrigArtistIdxList = [totalOrigArtistTextSet.index(i) if i else None for i in OrigArtistTextList]
    processedOrigArtistTextList = tuple(map(convertTextToMenuFormat, totalOrigArtistTextSet))

    # Convert to C
    outputOrigArtistStringsList = [f'const char musicSoundOrigArtistTestString{i:02X}[{len(s):2}] = "{s}";' for i, s in enumerate(processedOrigArtistTextList)]
    OrigArtistArrayList = [f'\tmusicSoundOrigArtistTestString{i:02X},' if i != None else '\tNULL,' for i in OrigArtistIdxList]
    OrigArtistSizeArrayList = [f'\tsizeof(musicSoundOrigArtistTestString{i:02X}),' if i != None else '\t0,' for i in OrigArtistIdxList]



    # Get SFX names
    sfxTextList = [i['text'] for i in metadata['SFX'] if 'text' in i.keys() and i['text']]
    sfxTextSet = tuple(sorted(set(sfxTextList), key=lambda x : sfxTextList.index(x)))
    sfxIdxList = [sfxTextSet.index(i) for i in sfxTextList]
    processedSfxTextList = tuple(map(convertTextToMenuFormat, sfxTextSet))

    # Convert to C
    sfxOutputStringsList = [f'const char sfxSoundTestString{i:02X}[{len(s):2}] = "{s}";' for i, s in enumerate(processedSfxTextList)]
    sfxArrayList = [f'\tsfxSoundTestString{i:02X},' if i != None else '\tNULL,' for i in sfxIdxList]
    sfxSizeArrayList = [f'\tsizeof(sfxSoundTestString{i:02X}),' if i != None else '\t0,' for i in sfxIdxList]

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
        'soundTestData': {
            'songNames': songNameList,
            'vsSongNames': vsSongNameList,
            'soundTestStrings': outputStringsList,
            'origartistTestStrings': outputOrigArtistStringsList,
            'upperPtrs': upperArrayList,
            'upperSizes': upperSizeArrayList,
            'lowerPtrs': lowerArrayList,
            'lowerSizes': lowerSizeArrayList,
            'OrigArtistPtrs': OrigArtistArrayList,
            'OrigArtistSizes': OrigArtistSizeArrayList,


            'sfxSoundTestStrings': sfxOutputStringsList,
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


def parseFSTextFile(file : pathlib.Path | list[str], indent = 0, indentArr = None):
    output = []
    if isinstance(file, pathlib.Path):
        filedata = list(file.open())
    else:
        filedata = file.copy()
    if not indentArr:
        indentArr = [len(re.match(fsTxtIndentRegex, line)['indent']) for line in filedata]
    indentIdxs = [idx for idx, ind in enumerate(indentArr) if ind == indent]
    indentIdxs.append(len(indentArr))
    for lineStart, lineEnd in pairwise(indentIdxs):
        data = re.match(fsTxtLineRegex, filedata[lineStart]).groupdict()

        linetype = data['type']
        properties = re.findall(fsTxtPropRegex, data['properties'])
        lineobj = {"__type": linetype, **dict(properties)}
        
        if lineStart < lineEnd - 1:
            # Recursion
            lineobj['__subordinates'] = parseFSTextFile(filedata[lineStart+1:lineEnd], indent+1, indentArr[lineStart+1:lineEnd])
        output.append(lineobj)
    return output
        
def tidyUpFSTextData(data : list, uppermostLevel = True):
    objtypes = set()
    for obj in data:
        objtypes.add(obj['__type'])
        if '__subordinates' in obj.keys():
            # Recurse to tidy up shit
            subordinates = tidyUpFSTextData(obj['__subordinates'], False)
            # Get types of subordinates
            subtypes = {i['__type'] for i in subordinates}
            subtypes = {i : [] for i in subtypes}
            # Remove old subordinates
            obj.pop('__subordinates')
            obj.update(subtypes)
            # Sort subordinates per category
            for i in subordinates:
                type = i.pop('__type')
                obj[type].append(i)
    if not uppermostLevel:
        return data
    else:
        return {objtype : [obj for obj in data if obj.pop('__type') == objtype] for objtype in objtypes}


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
    fsVer = re.search(famistudioHelpRegex, proc.stdout.decode())['version']
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
        fsTxtData = parseFSTextFile(fsTxtPath)
        fsTxtData = tidyUpFSTextData(fsTxtData)
        # Assume there's only one project that got exported
        fsTxtData = fsTxtData['Project'][0]
        fsTxtPath.unlink(missing_ok = True)
    else:
        print("Somehow the famistudio-txt-export process didn't create a valid text file.")
        exit(2)
    
    dpcmAlignerName = processed_metadata['dpcmAlignerName']

    songNames = [song['Name'] for song in fsTxtData['Song']]
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
    instsize = re.search(instSizeRegex, cmdOutput)
    if (not instsize):
        print("Instrument size not correctly present in the FamiStudio command output.")
        exit(3)
    instsize = int(instsize['instSize'])
    print(f"== Total maximum size of data in a bank is {8192 - (instsize / 5 * 3)} bytes")

    # Get song sizes in bytes
    songsizestrings = re.finditer(songSizeRegex, cmdOutput)
    songsizes = [[
            songNames.index(match['songName']),
            match['songName'],
            int(match['songSize'])
        ] for match in songsizestrings if match['songName'] != dpcmAlignerName]
    SONG_IDX_IDX = 0
    SONG_NAME_IDX = 1
    SONG_SIZE_IDX = 2
    bins = binpacking.to_constant_volume(songsizes, 8192-(instsize / 5 * 3), SONG_SIZE_IDX)
    for idx, bank in enumerate(bins):
        print(f"== Bank {idx}:")
        print("\t- Songs: "+", ".join([j[SONG_NAME_IDX] for j in bank]))
        print("\t- Total approx. size:", sum([j[SONG_SIZE_IDX] for j in bank]), "bytes")

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
    
    dpcmFiles = [{
        "path": i,
        **re.search(dpcmFileNameRegex, i.name).groupdict()
    } for i in dpcmFiles]
    dpcmError = False
    dpcmBanks = list(set([i['dpcmBank'] for i in dpcmFiles]))
    for bank in dpcmBanks:
        bankDpcmError = False
        dpcmFilesOfBank = [file for file in dpcmFiles if file['dpcmBank'] == bank]
        for file in dpcmFilesOfBank:
            if not(filecmp.cmp(file['path'], dpcmFilesOfBank[0]['path'], shallow=False)):
                print(f"DPCM Data Bank {file['dpcmBank']} of music data bank {file['musicBank']} differs from that of music data bank 0.")
                bankDpcmError = True
                dpcmError = True
        if not bankDpcmError:
            (exportPath / f"{exportStemPrefix}_bank{bank}.dmc").unlink(missing_ok = True)
            dpcmFilesOfBank[0]['path'].rename(exportPath / f"{exportStemPrefix}_bank{bank}.dmc")
            dpcmFilesOfBank.pop(0)
        [i['path'].unlink(missing_ok = True) for i in dpcmFilesOfBank]

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

    print(f"== {exportStemPrefix}_soundTestTables.h")
    processed_soundtest_metadata = processed_metadata['soundTestData']
    soundTestTextData = [
        '// Generated by export.py using data in metadata.json',
        '',
        '#if !__VS_SYSTEM',
        '',
        *processed_soundtest_metadata['soundTestStrings'],
        '', '',
        'const char* const xbgmtextsUpper[] = {',
        *processed_soundtest_metadata['upperPtrs'],
        '};',
        '',
        'const uint8_t xbgmtextsUpperSize[] = {',
        *processed_soundtest_metadata['upperSizes'],
        '};',
        '', '',
        'const char* const xbgmtextsLower[] = {',
        *processed_soundtest_metadata['lowerPtrs'],
        '};',
        '',
        'const uint8_t xbgmtextsLowerSize[] = {',
        *processed_soundtest_metadata['lowerSizes'],
        '};',
        '',
        *processed_soundtest_metadata['origartistTestStrings'],
        '', '',
        'const char* const xbgmtextsOrigArtist[] = {',
        *processed_soundtest_metadata['OrigArtistPtrs'],
        '};',
        '', '',
        'const uint8_t xbgmtextsOrigArtistSize[] = {',
        *processed_soundtest_metadata['OrigArtistSizes'],
        '};',
        '', '',
        '#else',
        '',        
        'const char* const xbgmtextsUpper[] = {};',
        'const uint8_t xbgmtextsUpperSize[] = {};',
        'const char* const xbgmtextsLower[] = {};',
        'const uint8_t xbgmtextsLowerSize[] = {};',
        'const char* const xbgmtextsOrigArtist[] = {};',
        'const uint8_t xbgmtextsOrigArtistSize[] = {};',
        '',
        '#endif',
        '', '', '',
        'CODE_BANK_PUSH("RODATA")',
        '',
        '#if !__VS_SYSTEM',
        '',
        'const uint8_t xbgmlookuptable[] = {',
        *[f"\t{i}," for i in processed_soundtest_metadata['songNames']],
        '};', '', '#else', '',
        'const uint8_t xbgmlookuptable[] = {',
        *[f"\t{i}," for i in processed_soundtest_metadata['vsSongNames']],
        '};', '', '#endif', '', 
        'CODE_BANK_POP()',
        ''
    ]
    (exportPath / f"{exportStemPrefix}_soundTestTables.h").write_text("\n".join(soundTestTextData))

    print(f"== sfx_soundTestTables.h")
    soundTestSfxTextData = [
        '// Generated by export.py using data in metadata.json',
        '',
        '#if !__VS_SYSTEM',
        '',
        *processed_soundtest_metadata['sfxSoundTestStrings'],
        '', '',
        'const char* const sfxtexts[] = {',
        *processed_soundtest_metadata['sfxPtrs'],
        '};',
        '',
        'const uint8_t sfxtextSizes[] = {',
        *processed_soundtest_metadata['sfxSizes'],
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
    (exportPath / "sfx_soundTestTables.h").write_text("\n".join(soundTestSfxTextData))

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
