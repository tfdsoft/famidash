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

if __name__ == "__main__":
    import glob
    parseAllIncFiles()
    for filename in glob.glob(sys.path[0]+"/EXPORTS/music_*.s"):
        print ("file: " + filename)
        prefix = filename[len(sys.path[0]+"/EXPORTS/music_"):-2]
        print(prefix)