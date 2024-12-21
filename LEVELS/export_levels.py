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
		if current_run == tile and run_length < 0x80:
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

def export_bg(folder: pathlib.PurePath, levels: Iterable[str]) -> tuple:
	# data for all levels, each gets a tuple, they are then binpacked
	level_data = []
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
		if level in size_cache and size_cache[level].get("hash") == hashlib.sha256(bytes(rle_data)).hexdigest() and int(size_cache[level].get("rle_size")) == len(rle_data) and "huff_size" in size_cache[level]:
			huff_len = int(size_cache[level]["huff_size"])
			cached_str = "cached level"
		else:
			huff_len = huffmunch.estimate_compressed_size(rle_data)
			cached_str = "level"
		if (huff_len >= 8192 - 7):
			print(f"Level {level} is {huff_len:6} bytes long after compression, which is more than the bank size of 8192 (- 7 required by the header). This is temporarily not supported, and as such the level will be absent.")
			continue
		header = [
			f"{level}_song_number",
			f"{level}_game_mode",
			f"{level}_speed",
			f"{level}_no_parallax",
			f"{level}_bg_color",
			f"{level}_grnd_color",
			f"{len(lines)}\t; {level} height",
		]
		level_data.append((level, len(header)+huff_len, header, rle_data))
		#includes non-compressed data, as every bank will be compressed together
		print(f"loading {cached_str}: {level} rle size: {len(rle_data)} rle+huffmunch size: {huff_len} compression rate: {(huff_len / len(rle_data) * 100) : .4}%")
		size_cache[level] = {"rle_size": len(rle_data), "huff_size": huff_len, "hash": hashlib.sha256(bytes(rle_data)).hexdigest()}
		
	banked_level_data = binpacking.to_constant_volume(level_data, 8192, 1)

	for (i, bank) in enumerate(banked_level_data, 1):
		real_sum_size = sum([length for (id, length, hdr, rle_data) in bank])
		print(f"\t- LVL_BANK_{i:02X}, max size 8192, real sum size {real_sum_size:04}:")
		for (id, length, hdr, rle_data) in bank:
			print(f"\t\t- ({length:4} bytes) {id}")
			# all_data.append((id, length, i+first_bank_num, data))
	
	# TODO: complete the rest lmfao


	# this is legacy code now bitch

	# # now split up the data into banks
	# banked_data = chunks(all_data, 0x2000)
	# print("about to split up the data")

	# current_bank = 1
	# current_level = 0
	# out_str = "\n"
	# # now write the bytes
	# remaining_bytes = 0
	# next_level_offset = 0
	# for bank in banked_data:
	# 	print(f"exporting bank {current_bank}")
	# 	out_str += f'.segment "LVL_BANK_{current_bank:02X}"\n'
	# 	filled_bytes = 0
	# 	while filled_bytes < len(bank):
	# 		print(f"already filled bytes: {filled_bytes}")
	# 		# if we don't have any left over bytes from the previous level, then start the next level
	# 		if remaining_bytes <= 0:
	# 			if remaining_bytes == 0:
	# 				print(f"exporting level {levels[current_level]}")
	# 				out_str += f".export level_data_{levels[current_level]}\n"
	# 				out_str += f"level_data_{levels[current_level]}:\n"
				
	# 			# this is protection from header bank overflows (we go byte by byte)
	# 			out_str += f"  .byte {bank[filled_bytes]}\n"
	# 			remaining_bytes -= 1
	# 			filled_bytes += 1
	# 			if remaining_bytes == -7:
	# 				next_level_offset = filled_bytes + level_lengths[current_level] - 7
	# 				current_level += 1
	# 				remaining_bytes = 0

	# 		else:
	# 			tmp = remaining_bytes
	# 			remaining_bytes = max(0, next_level_offset - 0x2000)
	# 			next_level_offset = tmp
	# 			print(f"spilling to new bank remaining_bytes {remaining_bytes}")


	# 		if remaining_bytes >= 0:
	# 			# chunk the bytes for this level
	# 			for level_data in chunks(bank[filled_bytes:next_level_offset], 0x20):
	# 				out_str += f"  .byte {','.join([f'${x:02x}' for x in level_data])}\n"

	# 			# if the next level ends past this one, then set the remaining bytes for the next bank
	# 			print(f"filled_bytes {filled_bytes} next_level_offset {next_level_offset} remaining_bytes {remaining_bytes}")
	# 			filled_bytes = next_level_offset
	# 			if 0x2000 <= next_level_offset:
	# 				remaining_bytes = next_level_offset - 0x2000
					
	# 	current_bank += 1

# 	with open(own_path.joinpath("all_level_data.s"), 'w') as out:
# 		out.write(f"""
# ;;; Generated by export_levels.py
# {out_str}
# """)

# 	if (remaining_bytes != 0):
# 		current_bank -= 1

	# if the export is successful, write cache
	with open(own_path / "level_data_cache.json", "w") as file:
		json.dump(size_cache, file)

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
		spriteCounts = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
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
