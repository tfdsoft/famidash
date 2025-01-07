#!/usr/bin/env python

DnFTheader = "# Dn-FamiTracker text export 0."
OGFTheader = "# FamiTracker text export 0.4.2\n"

DPCMReleaseRegex = b"(?:[^:\n]+ :){5} ==="
DPCMEffectsRegex = b"(?:[^:\n]+ :){5} ... .. .((?:(?: ...)*(?: L..)+)*)\r\n"
DelayedReleaseRegex = b" L"

if __name__ == "__main__":
    import re, sys, glob # todo: refactor with pathlib and non-binary reading mode
    for filename in glob.glob(sys.path[0]+"/INTERMEDIATES/*.txt"):
        file = open(filename, "rb")
        print(f"Opened file {filename}, ", end="")
        header = file.readline()
        if (header.decode("utf-8").startswith(DnFTheader)):
            print("header is from Dn-FT, reading the rest of file... ", end="", flush=True)
            restOfFile = file.read()
            file.close()
            print("done, regexing the file... ", end="", flush=True)
            restOfFile = re.sub(DPCMReleaseRegex, lambda x: x.group()[:-3]+b"---", restOfFile)
            restOfFile = re.sub(DPCMEffectsRegex, 
                lambda x: 
                    restOfFile[x.span()[0]:x.span(1)[0]] + 
                    re.sub(DelayedReleaseRegex, b" S", x.groups()[0]) + 
                    restOfFile[x.span(1)[1]:x.span()[1]],
                restOfFile)
            print("done, writing the new file... ", end="", flush=True)
            with open(filename, "wb") as file:
                file.write(OGFTheader.encode("utf-8"))
                file.write(restOfFile)
            print("done!", flush=True)
        else:
            print("header is not from Dn-FT, skipping...")
            file.close()