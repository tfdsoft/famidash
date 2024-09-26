#!/usr/bin/env python3
# export command: dotnet path/FamiStudio.dll famidash/MUSIC/MODULES/music_master.fms famistudio-asm-export /tmp/tmp.s -famistudio-asm-format:ca65 -export-songs:find them yourself 

instsizeregex = "Info: Instruments size : (.+) bytes\\."
songsizeregex = "Info: Song '(.+)' size: (.+) bytes\\."

songnameregex = 'Song[^\n]+Name="([^"]+)' # Song[anything but newline]Name="[anything but "]"
nameregex = 'Name="[^"]+"'
dpcmalignername = "dpcm"

cmd_output = """Put the output of the export command above here"""

fs_txt_path = "/tmp/tmp.txt"

if __name__ == "__main__":
    import binpacking, re, os
    instsize = re.findall(instsizeregex, cmd_output)
    if (len(instsize) != 1):
        LookupError("Instrument size not correctly present in the text.")
        exit(3)
    instsize = int(instsize[0])
    songsizestrings = re.findall(songsizeregex, cmd_output)
    print(songsizestrings)
    songsizes = [(i[0], int(i[1])) for i in songsizestrings if i[0] != dpcmalignername]
    bins = binpacking.to_constant_volume(songsizes, 8192-instsize, 1)
    for i in range(len(bins)):
        print(f"== Bank {i}:")
        print("\t- Songs: "+", ".join([j[0] for j in bins[i]]))
        print("\t- Total approx. size:", sum([j[1] for j in bins[i]]), "bytes")

    if os.path.exists(fs_txt_path):
        fs_txt = open(fs_txt_path)

        names = re.findall(songnameregex, "\n".join(fs_txt.readlines()))
        if len(names) == 0:
            LookupError("Amount of valid songs in the FS txt file is 0.")
            exit(1)
        
        if not(dpcmalignername in names):
            LookupError("DPCM aligner not found in FS txt file.")
            exit(2)

        dpcmidx = names.index(dpcmalignername)
        
        print("List of commands to run (adjust with your path):")

        for i in range(len(bins)):
            idxs = ",".join([str(names.index(j[0])) for j in bins[i]])
            print(f"dotnet path/FamiStudio.dll famidash/MUSIC/MODULES/music_master.fms famistudio-asm-export famidash/MUSIC/EXPORTS/music_{i+1}.s -famistudio-asm-format:ca65 -famistudio-asm-generate-list -export-songs:{dpcmidx},{idxs}")

        print("Bank lengths table:")
        print(f"\t.byte{', '.join([len(i) for i in bins[:-1]])}, $FF ;last bank is marked with an FF to always stop bank picking")





