import sys

def readFile (file : str) -> list:
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

if __name__ == "__main__":
    output = readFile("music_songlist")
    output += readFile("sfx_sfxlist")

    outfile = open(sys.path[0]+"/EXPORTS/musicDefines.h", "w")
    outfile.write("\n".join(output))
    outfile.close()