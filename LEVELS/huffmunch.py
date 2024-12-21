import subprocess
import pathlib
import os, sys

huffmunch_own_path = pathlib.Path(sys.path[0]).resolve()
huffmunch_tmp_path = huffmunch_own_path.parent / "TMP"

if (os.name == "nt"):
	huffmunchExecutable = "huffmunch.exe"
elif (os.name == "posix"):
	huffmunchExecutable = "huffmunch"

def compress_multiple(data : list[list[int]], bank_count : int = 1, bank_size : int = 65536) -> bytearray:
	ptr = 0
	fileBase = huffmunch_tmp_path / "huff_tmp"
	with open(f"{fileBase}.bin", "wb") as file:
		for i in data:
			file.write(bytes(i))
	with open(f"{fileBase}.lst", "w") as file:
		file.write(f"{bank_count} {bank_size}{os.linesep}")
		for idx in range(len(data)):
			file.write(f"{ptr} {ptr+len(data[idx])-1} {fileBase}.bin{os.linesep}")
			ptr += len(data[idx])
	process = subprocess.run([huffmunch_own_path / "huffmunch" / "bin" / huffmunchExecutable, "-L", f"{fileBase}.lst", f"{fileBase}.hfm"], capture_output=True)
	if (process.returncode != 0):
		print(process.stdout)
		print(process.stderr)
		return 0
	with open(f"{fileBase}.hfm", "rb") as file:
		output = file.read()
	for ext in ["bin", "lst"]:
		os.remove(f"{fileBase}.{ext}")
	return output

def compress_single(data : list[int]) -> bytearray:
	fileBase = huffmunch_tmp_path / "huff_tmp"
	with open(f"{fileBase}.bin", "wb") as file:
		file.write(bytes(data))
	process = subprocess.run([huffmunch_own_path / "huffmunch" / "bin" / huffmunchExecutable, "-B", f"{fileBase}.bin", f"{fileBase}.hfm"], capture_output=True)
	if (process.returncode != 0):
		print(process.stdout)
		print(process.stderr)
		return 0
	with open(f"{fileBase}.hfm", "rb") as file:
		output = file.read()
	for ext in ["bin", "hfm"]:
		os.remove(f"{fileBase}.{ext}")
	return output

def estimate_compressed_size_multiple(data : list[list[int]], bank_count : int = 1, bank_size : int = 65536) -> int:
	ptr = 0
	fileBase = huffmunch_tmp_path / "huff_tmp"
	with open(f"{fileBase}.bin", "wb") as file:
		for i in data:
			file.write(bytes(i))
	with open(f"{fileBase}.lst", "w") as file:
		file.write(f"{bank_count} {bank_size}{os.linesep}")
		for idx in range(len(data)):
			file.write(f"{ptr} {ptr+len(data[idx])-1} {fileBase}.bin{os.linesep}")
			ptr += len(data[idx])
	process = subprocess.run([huffmunch_own_path / "huffmunch" / "bin" / huffmunchExecutable, "-L", f"{fileBase}.lst", f"{fileBase}.hfm"], capture_output=True)
	if (process.returncode != 0):
		print(process.stdout)
		print(process.stderr)
		return 0
	output = pathlib.Path(f"{fileBase}0000.hfm").stat().st_size
	for ext in [".bin", ".lst", ".hfm", "0000.hfm"]:
		os.remove(f"{fileBase}{ext}")
	return output

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