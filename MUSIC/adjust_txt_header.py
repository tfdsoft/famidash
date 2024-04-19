import sys

DnFTheader = "# Dn-FamiTracker text export 0."
OGFTheader = "# FamiTracker text export 0.4.2\n"

if __name__ == "__main__":
    import glob
    for filename in glob.glob(sys.path[0]+"/INTERMEDIATES/*.txt"):
        file = open(filename, "rb")
        print(f"Opened file {filename}, ", end="")
        header = file.readline()
        if (header.decode("utf-8").startswith(DnFTheader)):
            print("header is from Dn-FT, reading the rest of file... ", end="")
            restOfFile = file.read()
            file.close()
            print("done, writing new file... ", end="")
            with open(filename, "wb") as file:
                file.write(OGFTheader.encode("utf-8"))
                file.write(restOfFile)
            print("done!", flush=True)
        else:
            print("header is not from Dn-FT, skipping...")
            file.close()
