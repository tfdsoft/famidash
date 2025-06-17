# No shebang as it's not supposed to run on its own

# install binpacking and pyjson5
install_list = []

import importlib.util
import subprocess
import sys
spec = importlib.util.find_spec('binpacking')
if spec is None:
	install_list.append('binpacking')

spec = importlib.util.find_spec('pyjson5')
if spec is None:
	install_list.append('pyjson5')

if len(install_list):
    subprocess.check_call([sys.executable, '-m', 'pip', 'install', *install_list])

import argparse
import csv
import pathlib
import itertools
import math
import binpacking
import pyjson5
import aart_lz
import json
import hashlib
from collections.abc import Iterable

own_path = pathlib.Path(sys.path[0]).resolve()

def chunks(lst, n):
	"""Yield successive n-sized chunks from lst."""
	for i in range(0, len(lst), n):
		yield lst[i:i + n]

def getPropFormatted(i, prop, prefix = None, validPrefixVals = None, globalPrefix = "") -> str:
		if prefix and i[prop] in validPrefixVals:
			return f"{globalPrefix}{prefix}{i[prop]}"
		else:
			return f"{globalPrefix}{i[prop]}"

def vertical_rle_with_single_tile(lines):
	# vertical rle compression
	column_tiles = list(itertools.chain.from_iterable(zip(*list(lines)))) + [0x100]
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
		if data[ptr] >= 0x80:
			ptr += 1
		else:
			ptr += 2
	return lastptr

def split_rle_data_into_compressed_banks(data : Iterable[int], first_meta_ptr : int, compressed_banks_sizes : list[int]):
	out_data = []
	meta_ptr = first_meta_ptr
	idx = 0
	while len(data) != 0:
		compressed_bank_size = compressed_banks_sizes[min(len(compressed_banks_sizes)-1, idx)]
		print(f"\tPart {len(out_data)}:")
		# LET'S GO GAMBLING!!!
		# make a bet about the compression rate
		bet = 30 # %, pretty unsafe bet, but life is all about taking risks
		while True:
			bet_size = compressed_bank_size / (bet / 100)
			# split the bank at the bet size
			if bet_size >= len(data):
				bet_data = data
				og_size = len(data)
				bet = min(math.floor((compressed_bank_size / og_size) * 100), 100)
			else:
				bet_data = data[0:get_split_point_in_rle_data(data, bet_size - 3)] + [0x7F, 0x7F, meta_ptr] # Meta seq
				og_size = get_split_point_in_rle_data(data, bet_size - 3)
			print(f"\t\tBet: {100-bet}%, Real size: {len(bet_data)} -> ", end = "", flush = True)
			compressed_data = aart_lz.compress(bet_data)
			print(f"{len(compressed_data)}, Real compression: {100-(len(compressed_data) / len(bet_data) * 100) : .4}%")
			if (len(compressed_data) <= compressed_bank_size):
				break
			# AW DANGIT
			bet += 1 # %
		out_data.append(compressed_data)
		data = data[og_size:]
		meta_ptr += 1
	return out_data
	

def export_bg(folder: pathlib.PurePath, levels: Iterable[dict], include_path : pathlib.Path) -> tuple:
	# data for all levels, each gets a tuple, they are then binpacked
	level_data = []
	# data for split level parts
	level_chunk_data = []
	# also include the output length of levels in tiles:
	level_widths = []

	total_rle_size = 0
	total_final_size = 0

	# load compressed level cache, if it exists
	if ((include_path / "level_data_cache.json").is_file()):
		with open((include_path / "level_data_cache.json")) as file:
			size_cache = json.load(file)
	else:
		size_cache = {}

	cached_data_subfolder = (include_path / "EXPORTS").resolve()
	if not cached_data_subfolder.is_dir():
		cached_data_subfolder.mkdir(parents=True)

	for metadata in levels:
		level = metadata['level']
		lines = []
		with open(folder / f"{level}_.csv") as f:
			lines = list(csv.reader(f))
		level_widths.append(math.ceil(len(lines[0]) * 16 / 100))	# the width of the level in tiles
		rle_data = vertical_rle_with_single_tile(lines)
		cached_data_path = (include_path / "EXPORTS" / f"{level}.lz.bin")
		if (level in size_cache):
			level_cache = size_cache[level]
		else:
			level_cache = {}
		def sha256(data : bytes) -> str:
			return hashlib.sha256(data).hexdigest()
		if (
			# Check existence of cache
			level in size_cache and
			cached_data_path.is_file() and
			# Check that the cache is valid against the RLE data
			"rle_size" in level_cache.keys() and
			int(level_cache.get("rle_size")) == len(rle_data) and
			level_cache.get("rle_hash") == sha256(bytes(rle_data)) and
			# Check that the cache is valid against the compressed data
			"lz_size" in level_cache.keys() and
			int(level_cache.get("lz_size")) == cached_data_path.stat().st_size
		):
			lz_data = cached_data_path.read_bytes()
			if (level_cache.get("lz_hash") == sha256(lz_data)):
				print(f'Loading cached level: {level}; ', end = "", flush = True)
			else:
				print(f'Loading level: {level}; ', end = "", flush = True)
				lz_data = aart_lz.compress(rle_data)
				cached_data_path.write_bytes(lz_data)
				level_cache = {}
		else:
			print(f'Loading level: {level}; ', end = "", flush = True)
			lz_data = aart_lz.compress(rle_data)
			cached_data_path.write_bytes(lz_data)
			level_cache = {}
		header = [
			metadata['songID'],
			f"{metadata['startingGameMode']}",
			f"{metadata['startingSpeed']}",
			f"{int(bool(metadata.get('parallaxDisable')))}",
			f"_{metadata['decoType']}",
			getPropFormatted(metadata, 'spikeSet', 'SPIKES', ('A', 'B', 'C'), "_"),
			getPropFormatted(metadata, 'blockSet', 'BLOCKS', ('A', 'B', 'C', 'D'), "_"),
			getPropFormatted(metadata, 'sawSet', 'SAWBLADES', ('A',), "_"),
			f"${metadata['startingBackgroundColor']:02X}",
			f"${metadata['startingGroundColor']:02X}",
			str(len(lines)),
		]
		maxHeaderStrLen = max(map(len, header))
		headerDataDesc = [
			"Song ID", "Starting game mode", "Starting speed", "Disable parallax",
			"Deco type", "Spike set", "Block set", "Sawblade set",
			"Starting background color", "Starting ground color", "Level height"]
		header = [f"{i} ;{'_'*(maxHeaderStrLen-len(i)+3)} {headerDataDesc[idx]}" for idx, i in enumerate(header)]
		total_rle_size += len(header) + len(rle_data)
		if (len(lz_data) >= 8192 - len(header)):
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
				all([int(
						path.is_file() and
						level_cache["split_huff_sizes"][id] == path.stat().st_size and
						level_cache["split_huff_hashes"][id] == sha256(path.read_bytes())
					) for id, path in (
						[(j, cached_data_path.with_suffix(f".{j}.bin")) for j in range(level_cache["split_count"])]
					)])
			):
				split_files = [cached_data_path.with_suffix(f".{i}.bin") for i in range(level_cache["split_count"])]
				split_data = [i.read_bytes() for i in split_files]
			
			else:
				print("compressing in parts:")

				split_data = split_rle_data_into_compressed_banks(rle_data, len(level_chunk_data), [8192-len(header), 8192])
				split_files = [cached_data_path.with_suffix(f".{i}.bin") for i in range(len(split_data))]

				[path.write_bytes(data) for path, data in zip(split_files, split_data)]
			
			continued_data = split_data[1:]

			level_data.append((level, len(header)+len(split_data[0]), header, split_files[0]))

			level_chunk_data += zip([level] * len(continued_data), [len(i) for i in continued_data], split_files[1:])

			print(f"Total RLE size: {len(rle_data)}; Split into:")

			total_final_size += len(header)
			for idx, dat in enumerate(split_data):
				print(f"\tPart {idx}, RLE+LZ size: {len(dat)}")
				total_final_size += len(dat)
			
			size_cache[level] = {
				"rle_size": len(rle_data), "lz_size": len(lz_data),
				"rle_hash": hashlib.sha256(bytes(rle_data)).hexdigest(),
				"lz_hash" : hashlib.sha256(bytes(lz_data)).hexdigest(),
				"split_count": len(split_data),
				"split_huff_hashes": 
					[hashlib.sha256(bytes(i)).hexdigest() for i in split_data],
				"split_huff_sizes":
					[len(i) for i in split_data]
			}
		else:
			level_data.append((level, len(header)+len(lz_data), header, cached_data_path))

			print(f"RLE size: {len(rle_data)}; RLE+LZ size: {len(lz_data)}; compression rate: {100-(len(lz_data) / len(rle_data) * 100) : .4}%")

			total_final_size += len(header)+len(lz_data)

			size_cache[level] = {
				"rle_size": len(rle_data), "lz_size": len(lz_data),
				"rle_hash": hashlib.sha256(bytes(rle_data)).hexdigest(),
				"lz_hash" : hashlib.sha256(bytes(lz_data)).hexdigest()
			}
	


	print("")
	print("============ TOTAL LEVEL COMPRESSION STATS ============")
	print(f"Total RLE (+ header) size:    {total_rle_size}")
	print(f"Total RLE+LZ (+ header) size: {total_final_size}")
	print(f"Bytes shaved off:             {total_rle_size - total_final_size}")
	print(f"Effective compression rate:  {100-(total_final_size / total_rle_size * 100) : .6}%")
	print("============ TOTAL LEVEL COMPRESSION STATS ============")
	print("")

	all_level_data = level_data + [(f"{l_id}_{i}", l_len, None, l_file) for i, (l_id, l_len, l_file) in enumerate(level_chunk_data)]

	banked_level_data = []

	for (id, length, hdr, cached_data_path) in all_level_data:
		out_str = []
		out_str.append(f"\t.export level_data_{id}")
		out_str.append(f"\tlevel_data_{id}:")
		if (hdr != None):
			out_str.append("\t; Header")
			out_str += [f"\t\t.byte {i}" for i in hdr]
		out_str.append("\t; Level data")
		out_str.append(f'\t\t.incbin "{cached_data_path.relative_to(include_path).as_posix()}" ; Size: {length}')
		out_str.append("")
		
		banked_level_data.append((length, "\n".join(out_str), f"level_data_{id}", "level", []))

	# if the export is successful, write cache
	(include_path / "level_data_cache.json").write_text(json.dumps(size_cache))

	level_chunk_list = [f"{l_id}_{i}" for i, (l_id, __, __) in enumerate(level_chunk_data)]

	return (banked_level_data, level_widths, level_chunk_list)
		
def export_spr(folder: pathlib.PurePath, levels: Iterable[dict], globalOffsetSettings: Iterable[dict]):
	all_data = []
	overflows = []

	def getDictFromOffsetSettings(offsetSettings : Iterable[dict], alreadyExistingDict: dict = {}):
		outDict = alreadyExistingDict.copy()
		# Recompile global offset settings into a single dict (faster)
		for setting in offsetSettings:
			offset = setting.get('offset', None)
			if not offset:
				offsetX = setting.get('offsetX', 0)
				offsetY = setting.get('offsetY', 0)
				offset = [offsetX, offsetY]
			if all([i == 0 for i in offset]):
				print(f"No offset data specified in setting {setting}.")
				continue

			if 'coordinates' in setting.keys():
				coordinates = tuple(setting['coordinates'])
				if not isinstance(coordinates, Iterable):
					print (f"Coordinates invalid in setting {setting}")
					continue

				if len(coordinates) == 2 and all([isinstance(i, int) for i in coordinates]):
					coordinates = [coordinates]

				for coordinate in coordinates:
					if not isinstance(coordinate, Iterable) or len(coordinate) != 2:
						print (f"Coordinates [{coordinate}] invalid in setting {setting}")
						continue

					coordinate = tuple(coordinate)

					if coordinate not in outDict.keys() or setting.get('override'):
						outDict[coordinate] = [offset, setting.get('override', False)]
					else:	# add up
						outDict[coordinate] = [[outDict[coordinate][0][i] + offset[i] for i in range(2)], False]
			elif 'objectID' in setting.keys():
				objIDs = setting['objectID']
				if isinstance(objIDs, int):
					objIDs = [objIDs]					

				for obj in objIDs:
					if obj not in outDict.keys() or setting.get('override'):
						outDict[obj] = offset
					else:	# add up
						outDict[obj] = [outDict[obj][i] + offset[i] for i in range(2)]
		return outDict

	globalOffsetSettingDict = getDictFromOffsetSettings(globalOffsetSettings)

	for num, metadata in enumerate(levels):
		level = metadata['level']
		localOffsetSettings = getDictFromOffsetSettings(metadata.get('objectOffsets', []), globalOffsetSettingDict)
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

					offsetA = localOffsetSettings.get(obj_id, [0, 0])
					offsetB, offBOverride = localOffsetSettings.get((i, j), [[0, 0], False])

					if offBOverride:
						x += offsetB[0]
						y += offsetB[1]
					else:
						x += offsetA[0] + offsetB[0]
						y += offsetA[1] + offsetB[1]
					
					level_data.append(
						[x & 0xFF, (x >> 8) & 0xFF,
						 y & 0xFF, (y >> 8) & 0xFF,
						 obj_id])
			
		if overflowStart > 0:
			overflows.append([level, overflowStart, -1])

		level_data.append([0xff]) # add terminator byte
		all_data.append((level, len(level_data) * 5 - 4, level_data, num))
		print(f"Sprite data for {level} is {len(level_data) * 5 - 4} bytes long")

	banked_data = []
	for (id, length, data, num) in all_data:
		out_str = []
		out_str.append(f"sprite_data_{id}:")
		for sprite in data:
			out_str.append(f"  .byte {','.join([f'${x:02x}' for x in sprite])}")
		banked_data.append((length, "\n".join(out_str), f"sprite_data_{id}", "sprite", [num, ]))

	if (len(overflows) > 0):
		print("SPRITE LIMIT OVERFLOWS HAPPENED IN SPRITE DATA:", file=sys.stderr)
		for i in overflows:
			print(f"\tLevel {i[0]} at x={i[1]}..{i[2] if i[2] > 0 else 'the end'}", file=sys.stderr)
	
	return (banked_data, None)
	
def binpack_and_write_data(bg_exp_data : tuple, spr_exp_data : tuple, include_path : pathlib.Path):
	# Binpack all the data
	banked_data = binpacking.to_constant_volume(bg_exp_data[0] + spr_exp_data[0], 8192, 0)
	lvl_file = ["", ";;; Generated by export_levels.py", ""]
	spr_data = []
	for i, bank in enumerate(banked_data):
		real_sum_size = sum(list(zip(*bank))[0])
		print(f"Bank DAT_BANK_{i:02X}: {real_sum_size}/8192 bytes")
		if (any([i[3] == "level" for i in bank])):
			lvl_file.append("")
			lvl_file.append(f'.segment "DAT_BANK_{i:02X}"\t; Total bank size: {real_sum_size} bytes')
		for size, data, label, data_type, metadata in bank:
			print(f"\t{label}: {size}")
			if (data_type == "level"):
				lvl_file.append(data)
			elif (data_type == "sprite"):
				spr_data.append((metadata[0], i, data))
	
	# Write the level data
	(include_path / "all_level_data.s").write_text("\n".join(lvl_file))

	# Pack the sprite data
	spr_file = ["", ";;; Generated by export_levels.py", ""]
	spr_data.sort()
	for id, bank, data in spr_data:
		spr_file += ["", f'.segment "DAT_BANK_{bank:02X}"', data]
	# Write the sprite data
	(include_path / "all_sprite_data.s").write_text("\n".join(spr_file))

def generate_menutext(filteredMetadata : dict, include_path : pathlib.Path):
	upperTextList = [i.get('upperText') for i in filteredMetadata]
	lowerTextList = [i.get('lowerText') for i in filteredMetadata]
	totalTextList = [i for i in upperTextList + lowerTextList if i]
	totalTextSet = tuple(sorted(set(totalTextList), key=lambda x : totalTextList.index(x)))

	# Get indices, convert to displayable format
	upperIdxList = [totalTextSet.index(i) if i else None for i in upperTextList]
	lowerIdxList = [totalTextSet.index(i) if i else None for i in lowerTextList]

	# Convert to C
	outputStringsList = [f'const char levelText{i:02X}[{len(s):2}] = "{s}";' for i, s in enumerate(totalTextSet)]
	upperArrayList = [f'\tlevelText{i:02X},' if i != None else '\tNULL,' for i in upperIdxList]
	upperSizeArrayList = [f'\tsizeof(levelText{i:02X}),' if i != None else '\t0,' for i in upperIdxList]
	lowerArrayList = [f'\tlevelText{i:02X},' if i != None else '\tNULL,' for i in lowerIdxList]
	lowerSizeArrayList = [f'\tsizeof(levelText{i:02X}),' if i != None else '\t0,' for i in lowerIdxList]

	(include_path / 'menutext.h').write_text("\n".join([
		'',
		'// Exported by export_levels.py',
		'',
		*outputStringsList,
		'', '',
		'const char* const levelTextsUpper[] = {',
		*upperArrayList,
		'};',
		'',
		'const uint8_t levelTextsUpperSize[] = {',
		*upperSizeArrayList,
		'};',
		'', '',
		'const char* const levelTextsLower[] = {',
		*lowerArrayList,
		'};',
		'',
		'const uint8_t levelTextsLowerSize[] = {',
		*lowerSizeArrayList,
		'};',
		''
		]))

def generate_level_list(filteredMetadata : dict, include_path : pathlib.Path):

	# Accessed from multiple places in diff banks, so it's in fixed
	starsList = [f"\t{i['stars']},\t// {i['level']}" for i in filteredMetadata]

	# variables that will be in the menu bank
	difficultiesList = [f"\t{i['difficulty']},\t// {i['level']}" for i in filteredMetadata]
	# colors list would be here IF IT WAS UPDATED
	# currently it overflows into iconBank
	# those 2 happen to get accessed from exclusively diff banks

	(include_path / 'levellist.h').write_text("\n".join([
			'',
			'// Exported by export_levels.py',
			'',
			'#define EASY 0',
			'#define NORMAL 1',
			'#define HARD 2',
			'#define HARDER 3',
			'#define INSANE 4',
			'#define DEMON 5',
			'#define AUTO 6',
			'',
			'const uint8_t difficulty_list[] = {',
			*difficultiesList,
			'};',
			'',
			'const uint8_t stars_list[] = {',
			*starsList,
			'};',
			''
		]
		))

def generate_level_table(levels, bg_exp_data, include_path):

	mid_widths_enabled = max(bg_exp_data[1]) >= 0x100
	hi_widths_enabled = max(bg_exp_data[1]) >= 0x10000
	
	level_list_lo = '\n'.join(
		[f"\t.byte .lobyte(level_data_{x})" for x in levels])
	sprite_list_lo = '\n'.join(
		[f"\t.byte .lobyte(sprite_data_{x})" for x in levels])
	
	level_list_hi = '\n'.join(
		[f"\t.byte .hibyte(level_data_{x})" for x in levels])
	sprite_list_hi = '\n'.join(
		[f"\t.byte .hibyte(sprite_data_{x})" for x in levels])
	
	level_list_bank = '\n'.join(
		[f"\t.byte .lobyte(.bank(level_data_{x}))" for x in levels])
	sprite_list_bank = '\n'.join(
		[f"\t.byte .lobyte(.bank(sprite_data_{x}))" for x in levels])
	
	level_chunk_list_lo = '\n'.join(
		[f"\t.byte .lobyte(level_data_{x})" for x in bg_exp_data[2]])
	level_chunk_list_hi = '\n'.join(
		[f"\t.byte .hibyte(level_data_{x})" for x in bg_exp_data[2]])
	level_chunk_list_bank = '\n'.join(
		[f"\t.byte .lobyte(.bank(level_data_{x}))" for x in bg_exp_data[2]])

	level_lengths_lo = "\n".join(
		[f"\t.byte .lobyte(${bg_exp_data[1][x]:06X})\t\t; {levels[x]}" 
			for x in range(len(levels))])
	level_lengths_md = "\n".join(
		[f"\t.byte .hibyte(${bg_exp_data[1][x]:06X})\t\t; {levels[x]}"
			for x in range(len(levels))])
	level_lengths_hi = "\n".join(
		[f"\t.byte .bankbyte(${bg_exp_data[1][x]:06X})\t\t; {levels[x]}"
			for x in range(len(levels))])
	
	(include_path / "all_level_table.s").write_text("\n".join([
		'',
		';;; Generated by export_levels.py',
		'',
		'.global _level_list_lo, _level_list_hi, _level_list_bank, _sprite_list_lo, _sprite_list_hi, _sprite_list_bank, _level_chunk_list_lo, _level_chunk_list_hi, _level_chunk_list_bank',
		'.segment "RODATA_2"', '',

		'_level_list_lo:',		level_list_lo,		'',	
		'_level_list_hi:',		level_list_hi,		'',	
		'_level_list_bank:',	level_list_bank,	'',	

		'_level_chunk_list_lo:',	level_chunk_list_lo,	'',	
		'_level_chunk_list_hi:',	level_chunk_list_hi,	'',	
		'_level_chunk_list_bank:',	level_chunk_list_bank,	'',	

		'_sprite_list_lo:',		sprite_list_lo,		'',	
		'_sprite_list_hi:',		sprite_list_hi,		'',	
		'_sprite_list_bank:',	sprite_list_bank,	'',	

		f'.define MID_LEVEL_LENGTHS_ENABLED {"1" if mid_widths_enabled else "0"}',
		f'.define HIGH_LEVEL_LENGTHS_ENABLED {"1" if hi_widths_enabled else "0"}',
		'',

		'_level_lengths_lo:',	level_lengths_lo,	'',

		'.if MID_LEVEL_LENGTHS_ENABLED',	'',
		'_level_lengths_md:',	level_lengths_md,	'',

		'.if HIGH_LEVEL_LENGTHS_ENABLED',	'',
		'_level_lengths_hi:',	level_lengths_hi,	'',

		'.endif',	'.endif',	''
	]))

def generate_space_defines(filteredOfficialMetadata, filteredCommunityMetadata, levelSetDefineName, include_path):
	offLevelList = [i['level'] for i in filteredOfficialMetadata]
	commLevelList = [i['level'] for i in filteredCommunityMetadata]
	official_level_count = len(offLevelList)
	community_level_count = len(commLevelList)

	levelDefineList = [f"#define {i} {idx}" for idx, i in enumerate(offLevelList + commLevelList)]

	if isinstance(levelSetDefineName, int) or isinstance(levelSetDefineName, float):
		levelSetDefineName = f"{levelSetDefineName}"
	elif isinstance(levelSetDefineName, str):
		levelSetDefineName = f"'{levelSetDefineName}'"

	(include_path / "level_defines.h").write_text("\n".join([
		'',
		'// Generated by export_levels.py',
		'',
		f"#define LEVELSET {levelSetDefineName}",
		'',
		f'#define OFFICIAL_LEVEL_COUNT {official_level_count}',
		f'#define COMMUNITY_LEVEL_COUNT {community_level_count}',
		'',
		*levelDefineList,
		''
	]))



def print_around_function(stringA, stringB, function, args):
	print(stringA, end="", flush=True)
	function(*args)
	print(stringB, end="", flush=True)

def main():
	parser = argparse.ArgumentParser(prog='export_levels',
					description='RLE encode level csv files and convert them to level data')
	parser.add_argument('-f', '--csvFolder', type=pathlib.Path, required=True,
					help='Path to folder with csv files')
	parser.add_argument('-m', '--metadata', type=pathlib.Path, required=True,
					help='Path to json5 file with level metadata specifications')
	parser.add_argument('-o', '--outputFolder', type=pathlib.Path, required=True,
					help='Output folder for the include files')
	args = parser.parse_args()

	if not args.metadata.is_file():
		print("Path to the metadata json5 file is invalid. Please specify a proper file.")
		exit(1)

	with args.metadata.open() as metafile:
		metadata = pyjson5.decode_io(metafile)

	filterMetadata = lambda __metadata:	tuple(filter(lambda obj: 
			set(['level', 'lowerText', 'decoType', 'spikeSet', 'blockSet', 'sawSet', 'difficulty',
				'stars', 'songID', 'startingGameMode', 'startingSpeed', 'startingBackgroundColor',
				'startingGroundColor']).issubset(obj.keys()), __metadata))

	filteredOfficialMetadata = filterMetadata(metadata['official_levels'])
	filteredCommunityMetadata = filterMetadata(metadata['community_levels'])
	filteredMetadata = filteredOfficialMetadata + filteredCommunityMetadata
	levels = [i['level'] for i in filteredMetadata]

	globalObjectOffsetSettings = metadata['globalObjectOffsets']

	levelSetDefineName = metadata['levelSetDefineName']

	include_path = (args.outputFolder).resolve()
	if not include_path.is_dir():
		include_path.mkdir(parents=True)

	bg_exp_data = export_bg(args.csvFolder, filteredMetadata, include_path)
	spr_exp_data = export_spr(args.csvFolder, filteredMetadata, globalObjectOffsetSettings)
	binpack_and_write_data(bg_exp_data, spr_exp_data, include_path)

	print("")
	print("Exporting includes:")
	print_around_function("\t- Menu text... ", "Done\n", generate_menutext, (filteredMetadata, include_path))
	print_around_function("\t- Level list... ", "Done\n", generate_level_list, (filteredMetadata, include_path))
	print_around_function("\t- Level table... ", "Done\n", generate_level_table, (levels, bg_exp_data, include_path))
	print_around_function("\t- Level defines... ", "Done\n", generate_space_defines, (filteredOfficialMetadata, filteredCommunityMetadata, levelSetDefineName, include_path))


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
