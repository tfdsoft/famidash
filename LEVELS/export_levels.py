# No shebang as it's not supposed to run on its own

# install binpacking
import importlib.util
import subprocess
import sys
spec = importlib.util.find_spec('binpacking')
if spec is None:
    subprocess.check_call([sys.executable, '-m', 'pip', 'install', 'binpacking'])

import argparse
import csv
import pathlib
import itertools
import math
import binpacking
import huffmunch
import json
import hashlib
from collections.abc import Iterable

own_path = pathlib.Path(sys.path[0]).resolve()

def chunks(lst, n):
	"""Yield successive n-sized chunks from lst."""
	for i in range(0, len(lst), n):
		yield lst[i:i + n]

def vertical_rle_with_single_tile(lines):
	# vertical rle compression
	column_tiles = list(itertools.chain.from_iterable(zip(*list(lines))))
	rle_data = []
	current_run = int(column_tiles[0])
	run_length = 1
	for strtile in column_tiles[1:]:
		tile = int(strtile)
		if (tile == -1):
			tile = 0
		if current_run == tile and (
			(current_run == 0x7F and run_length < 0x7F) or	# For meta sequence
			(current_run != 0x7F and run_length < 0x80)):
			run_length += 1
		else:
			# if its a single tile thats less than 0x80, then we add just one byte
			if run_length == 1 and current_run < 0x80:
				rle_data += [0x80 | current_run]
			else:
				# if its more than one byte in the run, then take the length of bytes to write
				# and subtract one since we can't ever have a run of 0 bytes
				rle_data += [run_length - 1, current_run]
			current_run = tile
			run_length = 1
	return rle_data

def get_split_point_in_rle_data(data : Iterable[int], split_point : int):
	lastptr = 0
	ptr = 0
	while ptr <= split_point:
		lastptr = ptr
		if data[ptr] < 0x80:
			ptr += 1
		else:
			ptr += 2
	return lastptr

def split_rle_data_into_huffmunch_banks(data : Iterable[int], compressed_bank_size : int, first_meta_ptr : int):
	out_data = []
	met_ptr = first_meta_ptr
	while len(data) != 0:
		# make a bet about the compression rate
		bet = 30 # %, pretty unsafe bet, but life is all about taking risks
		while True:
			bet_size = compressed_bank_size / (bet / 100)
			# split the bank at the bet size
			if bet_size >= len(data):
				bet_data = data
				og_size = len(data)
			else:
				bet_data = data[0:get_split_point_in_rle_data(data, bet_size - 2)] + [0x7F, 0x7F, met_ptr] # Meta seq
				og_size = get_split_point_in_rle_data(data, bet_size - 2)
			huff_data = huffmunch.compress_single(bet_data)
			print(f"\tBet: {100-bet}%, Real size: {len(bet_data)} -> {len(huff_data)}, Real compression: {100-(len(huff_data) / len(bet_data) * 100) : .4}%")
			if (len(huff_data) <= compressed_bank_size):
				break
			bet += 5 # %
		out_data.append(huff_data)
		data = data[og_size:]
		met_ptr += 1
	return out_data
	

def export_bg(folder: pathlib.PurePath, levels: Iterable[str]) -> tuple:
	# data for all levels, each gets a tuple, they are then binpacked
	level_data = []
	# data for split level parts
	meta_level_data = []
	# also include the output length of levels in tiles:
	level_widths = []

	# load compressed level cache, if it exists
	if ((own_path / "level_data_cache.json").exists()):
		with open((own_path / "level_data_cache.json")) as file:
			size_cache = json.load(file)
	else:
		size_cache = {}
	for level in levels:
		
		lines = []
		with open(folder / f"{level}_.csv") as f:
			lines = list(csv.reader(f))
		level_widths.append(math.ceil(len(lines[0]) * 16 / 100))	# the width of the level in tiles
		rle_data = vertical_rle_with_single_tile(lines)
		cached_data_path = (own_path / "EXPORTS" / f"{level}.hfm.bin")
		if (level in size_cache):
			level_cache = size_cache[level]
		else:
			level_cache = {}
		def sha256(data : bytes) -> str:
			return hashlib.sha256(data).hexdigest()
		if (
			# Check existence of cache
			level in size_cache and
			cached_data_path.exists() and
			cached_data_path.is_file() and
			# Check that the cache is valid against the RLE data
			int(level_cache.get("rle_size")) == len(rle_data) and
			level_cache.get("rle_hash") == sha256(bytes(rle_data)) and
			# Check that the cache is valid against the huffmunch data
			int(level_cache.get("huff_size")) == cached_data_path.stat().st_size
		):
			huff_data = cached_data_path.read_bytes()
			if (level_cache.get("huff_hash") == sha256(huff_data)):
				cached_str = "cached level"
			else:
				huff_data = huffmunch.compress_single(rle_data)
				cached_str = "level"
				cached_data_path.write_bytes(huff_data)
		else:
			huff_data = huffmunch.compress_single(rle_data)
			cached_str = "level"
			cached_data_path.write_bytes(huff_data)
		header = [
			f"{level}_song_number",
			f"{level}_game_mode",
			f"{level}_speed",
			f"{level}_no_parallax",
			f"{level}_bg_color",
			f"{level}_grnd_color",
			f"{len(lines)}\t; height of {level}",
		]
		if (len(huff_data) >= 8192 - 7):
			if (
				# Check existence of split cache
				level in size_cache and
				"split_count" in level_cache and
				"split_huff_hashes" in level_cache and
				"split_huff_sizes" in level_cache and
				# Check the consistency of the split count
				len(level_cache["split_huff_hashes"]) == level_cache["split_count"] and
				len(level_cache["split_huff_sizes"]) == level_cache["split_count"] and
				# Check validity of all split cached data
				min(
					[int(
						path.exists() and path.is_file() and
						level_cache["split_huff_sizes"][id] == path.stat().st_size and
						level_cache["split_huff_hashes"][id] == sha256(path.read_bytes())
					) for id, path in (
						[(j, cached_data_path.with_suffix(f".{j}.bin")) for j in range(level_cache["split_count"])]
					)
					]) == 1
			):
				split_files = [cached_data_path.with_suffix(f".{i}.bin") for i in range(level_cache["split_count"])]
				split_data = [i.read_bytes() for i in split_files]
			else:
				split_data = split_rle_data_into_huffmunch_banks(rle_data, 8192, len(meta_level_data))
				split_files = [cached_data_path.with_suffix(f".{i}.bin") for i in range(len(split_data))]
				[path.write_bytes(data) for path, data in zip(split_files, split_data)]
			continued_data = split_data[1:]

			level_data.append((level, len(header)+len(split_data[0]), header, split_files[0]))
			meta_level_data += zip([level] * len(continued_data), [len(i) for i in continued_data], split_files[1:])
			print(f"loading {cached_str}: {level} total rle size: {len(rle_data)}, split into:")
			for idx, dat in enumerate(split_data):
				print(f"\tpart {idx}, rle + huffmunch size: {len(dat)}")
			size_cache[level] = {
				"rle_size": len(rle_data), "huff_size": len(huff_data),
				"rle_hash": hashlib.sha256(bytes(rle_data)).hexdigest(),
				"huff_hash" : hashlib.sha256(bytes(huff_data)).hexdigest(),
				"split_count": len(split_data),
				"split_huff_hashes": 
					[hashlib.sha256(bytes(i)).hexdigest() for i in split_data],
				"split_huff_sizes":
					[len(i) for i in split_data]
			}
		else:
			level_data.append((level, len(header)+len(huff_data), header, cached_data_path))
			#includes non-compressed data, as every bank will be compressed together
			print(f"loading {cached_str}: {level} rle size: {len(rle_data)} rle+huffmunch size: {len(huff_data)} compression rate: {100-(len(huff_data) / len(rle_data) * 100) : .4}%")
			size_cache[level] = {
				"rle_size": len(rle_data), "huff_size": len(huff_data),
				"rle_hash": hashlib.sha256(bytes(rle_data)).hexdigest(),
				"huff_hash" : hashlib.sha256(bytes(huff_data)).hexdigest()
			}
	all_level_data = level_data + [(f"{l_id}_{i}", l_len, None, l_file) for i, (l_id, l_len, l_file) in enumerate(meta_level_data)]
	banked_level_data = binpacking.to_constant_volume(all_level_data, 8192, 1)

	out_str = ["", ";;; Generated by export_levels.py", ""]

	for (i, bank) in enumerate(banked_level_data, 1):
		real_sum_size = sum([length for (id, length, hdr, cached_data_path) in bank])
		print(f"\t- LVL_BANK_{i:02X}, size {real_sum_size:04}/8192:")
		out_str.append(f'.segment "LVL_BANK_{i:02X}" ; Size: {real_sum_size}')
		for (id, length, hdr, cached_data_path) in bank:
			print(f"\t\t- ({length:4} bytes) {id}")
			out_str.append(f"\t.export level_data_{id}")
			out_str.append(f"\tlevel_data_{id}:")
			if (hdr != None):
				out_str.append("\t; Header")
				out_str += [f"\t\t.byte {i}" for i in hdr]
			out_str.append("\t; Level data")
			out_str.append(f'\t\t.incbin "{cached_data_path.relative_to(own_path)}" ; Size: {length}')
			out_str.append("")
		out_str.append("")

	(own_path / "all_level_data.s").write_text("\n".join(out_str))

	# if the export is successful, write cache
	(own_path / "level_data_cache.json").write_text(json.dumps(size_cache))

	exit()
	return (level_widths, )#current_bank, remaining_bytes)
		
def export_spr(folder: pathlib.PurePath, levels: Iterable[str], level_last_bank : int, level_bytes_filled : int):
	all_data = []
	overflows = []
	for (num, level) in enumerate(levels):
		lines = []
		with open(folder / f"{level}_SP.csv") as f:
			lines = list(csv.reader(f))
		level_data = []
		rows = len(lines)
		columns = len(lines[0])
		rowOffset = 57 - rows
		count1 = 0
		count2 = 0
		spriteCounts = [0] * 16
		overflowStart = -1
		for i in range(0, columns):
			spriteCounts[i & 0x0F] = sum([int(int(lines[j][i]) >= 0) for j in range(0, rows)])
			if overflowStart < 0 and sum(spriteCounts) > 16:
				overflowStart = i - 15
			elif overflowStart >= 0 and sum(spriteCounts) <+ 16:
				overflows.append([level, overflowStart, i])
				overflowStart = -1
			for j in range(0, rows):
				a = str(lines[j][i])
				if (a != "-1"):
					x = i * 16		# x coordinate
					y = (rowOffset + j) * 16		# y coordinate
					obj_id = int(a)	# object id
					
					if obj_id == 0x3E: #right medium post
						x -= 8
					elif obj_id == 0x40: #right long post
						x -= 16

					if int(a) in [10,13,37,82,0x56,253]: # ADJUST HEIGHT FOR BOTTOM PADS
						y += 8
#					if level == "eon" and obj_id == 0x08:
#							x += 4
#					if level == "eon" and obj_id == 0x09:
#							x += 4

					if level == "polargeist" and obj_id == 0x0d:
						y -= 6
					if level == "clutterfunk" and obj_id == 0x10:
						count1 += 1
						if count1 == 2:
							y -= 8
					if level == "clutterfunk" and obj_id == 0xfc:
						count2 += 1
						if count2 == 3:
							y -= 8                     
						elif count2 == 4:
							y -= 8                     
					if int(a) in [0x42,0x43,0x47]:
						y -= 8
					level_data.append(
						[x & 0xFF, (x >> 8) & 0xFF,
						 y & 0xFF, (y >> 8) & 0xFF,
						 obj_id])
			
		if overflowStart > 0:
			overflows.append([level, overflowStart, -1])

		level_data.append([0xff]) # add terminator byte
		all_data.append((num, len(level_data) * 5 - 4, level_data))
		print(f"Sprites data for {level} takes {len(level_data) * 5 - 4} bytes")

	# binpack the data
	first_bank_size = 8192-level_bytes_filled
	first_bank_num = level_last_bank

	levels_that_fit_in_first_bank = list(filter(lambda e : e[1] <= first_bank_size, all_data))
	total_banked_data = []
	if (len(levels_that_fit_in_first_bank) != 0):
		data_for_first_bank = binpacking.to_constant_volume(
			list(filter(lambda e : e[1] <= 8192-level_bytes_filled, all_data)),	# so that no levels too big end up in here
			8192-level_bytes_filled, 1)

		all_data = list(filter(lambda e : e not in data_for_first_bank[0], all_data))
		total_banked_data.append(data_for_first_bank[0])
	else:
		first_bank_num += 1
		first_bank_size = 8192

	data_for_other_banks = binpacking.to_constant_volume(all_data, 8192, 1)
	total_banked_data += data_for_other_banks

	# assign bank numbers to each lvl

	all_data = []

	print("Per-bank sprite data:")
	for (i, bank) in enumerate(total_banked_data):
		real_sum_size = sum([length for (id, length, data) in bank])
		print(f"\t- LVL_BANK_{first_bank_num+i:02X}, max size {(first_bank_size):04}, real sum size {real_sum_size:04}:")
		for (id, length, data) in bank:
			print(f"\t\t- ({length:4} bytes) {levels[id]}")
			all_data.append((id, length, i+first_bank_num, data))

	all_data.sort()

	out_str = ""
	for (id, length, bank, data) in all_data:
		out_str += f'.segment "LVL_BANK_{bank:02X}"\n'
		out_str += f"sprite_data_{levels[id]}:\n"
		for sprite in data:
			out_str += f"  .byte {','.join([f'${x:02x}' for x in sprite])}\n"

	with open(own_path.joinpath("all_sprite_data.s"), 'w') as out:
		out.write(f"""

;;; Generated by export_levels.py

{out_str}
""")
	if (len(overflows) > 0):
		print("SPRITE LIMIT OVERFLOWS HAPPENED IN SPRITE DATA:", file=sys.stderr)
		for i in overflows:
			print(f"\tLevel {i[0]} at x={i[1]}..{i[2] if i[2] > 0 else 'the end'}", file=sys.stderr)
	


def main():
	parser = argparse.ArgumentParser(prog='export_levels',
					description='RLE encode level csv files and convert them to level data')
	parser.add_argument('-f', '--folder')
	parser.add_argument('file', metavar='FILE', type=str, nargs='+',
					help='list of level names to process')
	args = parser.parse_args()
	bg_exp_data = export_bg(pathlib.PurePath(args.folder), args.file)
	export_spr(pathlib.PurePath(args.folder), args.file, bg_exp_data[1], bg_exp_data[2])

	levels = args.file

	mid_widths_enabled = max(bg_exp_data[0]) >= 0x100
	hi_widths_enabled = max(bg_exp_data[0]) >= 0x10000
	
	with open(own_path.joinpath("all_level_table.s"), 'w') as out:
		level_list_lo = '\n'.join(
			[f"  .byte .lobyte(level_data_{x})" for x in levels])
		level_list_hi = '\n'.join(
			[f"  .byte .hibyte(level_data_{x})" for x in levels])
		sprite_list_lo = '\n'.join(
			[f"  .byte .lobyte(sprite_data_{x})" for x in levels])
		sprite_list_hi = '\n'.join(
			[f"  .byte .hibyte(sprite_data_{x})" for x in levels])
		level_list_bank = '\n'.join(
			[f"  .byte .lobyte(.bank(level_data_{x}))" for x in levels])
		sprite_list_bank = '\n'.join(
			[f"  .byte .lobyte(.bank(sprite_data_{x}))" for x in levels])
		level_lengths_lo = "\n".join(
			[f"  .byte .lobyte(${bg_exp_data[0][x]:06X})\t\t; {levels[x]}" 
				for x in range(len(levels))])
		level_lengths_md = "\n".join(
			[f"  .byte .hibyte(${bg_exp_data[0][x]:06X})\t\t; {levels[x]}"
				for x in range(len(levels))])
		level_lengths_hi = "\n".join(
			[f"  .byte .bankbyte(${bg_exp_data[0][x]:06X})\t\t; {levels[x]}"
				for x in range(len(levels))])
		out.write(f"""
;;; Generated by export_levels.py

.global _level_list_lo, _level_list_hi, _level_list_bank, _sprite_list_lo, _sprite_list_hi, _sprite_list_bank
.segment "RODATA_2"

_level_list_lo:
{level_list_lo}

_level_list_hi:
{level_list_hi}

_level_list_bank:
{level_list_bank}

_sprite_list_lo:
{sprite_list_lo}

_sprite_list_hi:
{sprite_list_hi}

_sprite_list_bank:
{sprite_list_bank}

.define MID_LEVEL_LENGTHS_ENABLED {"1" if mid_widths_enabled else "0"}
.define HIGH_LEVEL_LENGTHS_ENABLED {"1" if hi_widths_enabled else "0"}

_level_lengths_lo:
{level_lengths_lo}

.if MID_LEVEL_LENGTHS_ENABLED

_level_lengths_md:
{level_lengths_md}

.if HIGH_LEVEL_LENGTHS_ENABLED

_level_lengths_hi:
{level_lengths_hi}

.endif
.endif
""")


if __name__ == "__main__":
	main()


###
# unused RLE functions for comparison

def horizontal_rle_single(lines):
	all_rows = []
	for row in lines:
		i += 1
		rle_row = []
		current_run = int(row[0])
		total_size += 1
		run_length = 1
		for strtile in row[1:]:
			total_size += 1

			tile = int(strtile)
			if current_run == tile and run_length < 0x80:
				run_length += 1
			else:
				# if its a single tile thats less than 0x80, then we add just one byte
				if run_length == 1 and current_run < 0x80:
					rle_row += [0x80 | current_run]
				else:
					rle_row += [run_length, current_run]
				current_run = tile
				run_length = 1
		all_rows.append(rle_row)

def vertical_rle_no_single(lines):
	# vertical rle compression where its always a 2 byte length + tile id combo
	i = 0
	rle_data2 = []
	for row in zip(*list(lines)):
		i += 1
		current_run = int(row[0])
		run_length = 1
		for strtile in row[1:]:
			tile = int(strtile)
			if current_run == tile and run_length < 0x100:
				run_length += 1
			else:
				# if its a single tile thats less than 0x80, then we add just one byte
				rle_data2 += [run_length, current_run]
				current_run = tile
				run_length = 1
	return rle_data2
