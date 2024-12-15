import subprocess
import pathlib
import os, sys

huffmunch_own_path = pathlib.Path(sys.path[0]).resolve()
huffmunch_tmp_path = huffmunch_own_path.parent / "TMP"

if (os.name == "nt"):
	huffmunchExecutable = "huffmunch.exe"
elif (os.name == "posix"):
	huffmunchExecutable = "huffmunch"

def estimate_compressed_size(data : list[int]) -> int:
	fileBase = huffmunch_tmp_path / "huff_tmp"
	with open(f"{fileBase}.bin", "wb") as file:
		file.write(bytes(data))
	process = subprocess.run([huffmunch_own_path / "huffmunch" / "bin" / huffmunchExecutable, "-B", f"{fileBase}.bin", f"{fileBase}.hfm"], capture_output=True)
	if (process.returncode != 0):
		return 0
	output = pathlib.Path(f"{fileBase}.hfm").stat().st_size
	for ext in ["bin", "hfm"]:
		os.remove(f"{fileBase}.{ext}")
	return output