import sys

def readIncFile (file : str) -> list:
    file = open(sys.path[0]+"/EXPORTS/"+file+".inc")
    output = []

    while (True):
        line = file.readline()
        line = line.split()
        if (len(line) >= 2 and line[1] == "="):
            output.append("#define "+line[0]+" "+line[2])
        else: 
            file.close()
            return output
        
def parseAllIncFiles() :
    output = readIncFile("music_songlist")
    output += readIncFile("sfx_sfxlist")

    outfile = open(sys.path[0]+"/EXPORTS/musicDefines.h", "w")
    outfile.write("\n".join(output))
    outfile.close()

import io
def incrIncFile(inFile : io.TextIOWrapper, outFileC : io.TextIOWrapper, outFileAsm : io.TextIOWrapper, initialCount : int) -> int:
    outputC = []
    outputAsm = []
    count = initialCount

    while (True):
        line = inFile.readline()
        line = line.split()
        if (len(line) >= 2 and line[1] == "=" and (line[0][:len("song_")] == "song_" or line[0][:len("sfx_")] == "sfx_")):
            if (line[0][len("song_"):] not in ["dpcm", "max"]):
                outputC.append(f"#define {line[0]} {count}")
                outputAsm.append(f"{line[0]} = {count}")
                count += 1
            elif (line[0][len("song_"):] == "dpcm"):
                print(f"DPCM aligner detected at count {count}")
        else: 
            outFileC.write("\n".join(outputC))
            outFileC.write("\n")
            if (outFileAsm != 0):
                outFileAsm.write("\n".join(outputAsm))
                outFileAsm.write("\n")
            return count

if __name__ == "__main__":
    import glob, os
    outfileC = open(sys.path[0]+"/EXPORTS/musicDefines.h", "w")
    outfileAsm = open(sys.path[0]+"/EXPORTS/music_songlist.inc", "w")
    count = 0
    for filename in glob.glob(sys.path[0]+"/EXPORTS/music_*_songlist.inc"):
        print ("file: " + filename)
        count = incrIncFile(open(filename), outfileC, outfileAsm, count)
        # os.remove(filename)
    outfileC.write(f"#define song_max {count}")
    outfileC.write("\n")
    outfileC.write("\n".join(readIncFile("sfx_sfxlist")))
    outfileC.close()
    outfileAsm.write(f"song_max = {count}")
    outfileAsm.close()

    # parseAllIncFiles()
    for filename in glob.glob(sys.path[0]+"/EXPORTS/music_*.s"):
        print ("file: " + filename)
        prefix = filename[len(sys.path[0]+"/EXPORTS/music_"):-2]
        print(prefix)