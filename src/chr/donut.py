#!/usr/bin/env python3
# "Donut", NES CHR codec,
# Copyright (C) 2018  Johnathan Roatch
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Version History:
# 2019-02-15: Swapped the M and L bits, for conceptual consistency.
#             Also rearranged branches for speed.
# 2019-02-07: Removed "Duplicate" block type, and moved
#             Uncompressed block to below 0xc0 to make room
#             for block handling commands in the 0xc0~0xff space
# 2018-10-19: Fixed StopIteration leaking from generators.
#             Added partial block compression.
#             Removed ProgressBar.
#             (next to go will be that FileIterContextHack thing)
# 2018-09-29: XORing onto the block buffer has been removed.
# 2018-08-13: Changed the format of raw blocks to not be reversed.
# 2018-04-30: Initial release.

import functools
from pathlib import Path

"""
The coded block starts with a 1 or 2 byte header,
followed by at most 8 pb8 packets.

Block header:
LMlmbbBR
|||||||+-- Rotate plane bits (135° reflection)
||||000--- All planes: 0x00
||||010--- L planes: 0x00, M planes:  pb8
||||100--- L planes:  pb8, M planes: 0x00
||||110--- All planes: pb8
||||001--- In another header byte, For each bit starting from MSB
||||         0: 0x00 plane
||||         1: pb8 plane
||||011--- In another header byte, Decode only 1 pb8 plane and
||||       duplicate it for each bit starting from MSB
||||         0: 0x00 plane
||||         1: duplicated plane
||||       If extra header byte = 0x00, no pb8 plane is decoded.
||||1x1--- Reserved for Uncompressed block bit pattern
|||+------ M planes predict from 0xff
||+------- L planes predict from 0xff
|+-------- M = M XOR L
+--------- L = M XOR L
00101010-- Uncompressed block of 64 bytes (bit pattern is ascii '*' )

Header >= 0xc0 are Reserved, and currently results in a error.
"""

def pb8_pack_plane(plane, top_value=0x00):
    """pack a 8 byte plane into a pb8 packet.

    The pb8 packet has a 1 byte header.
    for each bit in header:
        0: Duplicate the previous byte. The first previous byte is 0x00
        1: Take a new byte from the data stream.

    This variant encodes the tile upside down
    """
    cplane = bytearray(1)
    flags = 0
    prev_byte = top_value
    for byte in plane[7::-1]:
        flags = flags << 1
        if byte != prev_byte:
            flags = flags | 1
            cplane.append(byte)
        prev_byte = byte
    cplane[0] = flags
    return bytes(cplane)

def pb8_unpack_plane(cplane, top_value=0x00):
    cplane_iter = iter(cplane)
    plane = bytearray(8)
    flags = next(cplane_iter)
    cur_byte = top_value
    for i in range(7,-1,-1):
        flags = flags << 1
        if flags & 0x0100:
            cur_byte = next(cplane_iter)
        plane[i] = cur_byte
    return bytes(plane)

@functools.lru_cache(maxsize=None, typed=False)
def flip_plane_bits_45(plane):
    return bytes(sum(((plane[x] >> (7-y))&0b1) << (7-x) for x in range(8)) for y in range(8))

@functools.lru_cache(maxsize=None, typed=False)
def flip_plane_bits_135(plane):
    return bytes(sum(((plane[x] >> y)&0b1) << x for x in range(8)) for y in range(8))

def cblock_cost(cblock):
    l = len(cblock)
    if (l < 1):
        return 0
    block_header = cblock[0]
    l -= 1
    if (block_header >= 0xc0):
        return 0
    if (block_header == 0x2a):
        return (len(cblock)*8192 + 1269)*256 + block_header
    cycles = 1281
    if (block_header & 0xc0):
        cycles += 640
    if (block_header & 0x20):
        cycles += 4
    if (block_header & 0x10):
        cycles += 4
    if (block_header & 0x02):
        if (l < 1):
            return 0
        plane_def = cblock[1]
        l -= 1
        cycles += 5
        decode_only_1_pb8_plane = ((block_header & 0x04) and (plane_def != 0x00))
    else:
        plane_def = [0x00,0x55,0xaa,0xff][(block_header>>2) & 0x03]
        decode_only_1_pb8_plane = False
    pb8_count = bin(plane_def).count("1")
    if (block_header & 0x01):
        cycles += pb8_count * 614
    else:
        cycles += pb8_count * 75
    if decode_only_1_pb8_plane:
        l -= 1
        cycles += pb8_count
        cycles += (l * 6 * pb8_count)
    else:
        l -= pb8_count
        cycles += l * 6
    return (len(cblock)*8192 + cycles)*256 + block_header

def decompress_single_block(cblock, allow_partial=False):
    cblock_iter = iter(cblock)
    block = bytearray(64)
    bytes_processed = 0
    try:
        block_header = next(cblock_iter)
        bytes_processed += 1
    except StopIteration:
        return (None, 0)
    if block_header >= 0xc0:
        raise ValueError("Block Header >= 0xc0 (currently reserved)", bytes_processed)
    if block_header == 0x2a:
        for i in range(64):
            try:
                block[i] = next(cblock_iter)
                bytes_processed += 1
            except StopIteration:
                if not allow_partial:
                    raise ValueError("Unexpected end at raw block bytes", bytes_processed)
                else:
                    break
    else:
        plane = bytearray(8)
        if block_header & 0x02:
            try:
                plane_def = next(cblock_iter)
                bytes_processed += 1
            except StopIteration:
                if not allow_partial:
                    raise ValueError("Unexpected end at zero plane flags", bytes_processed)
                else:
                    plane_def = 0x00
            decode_only_1_pb8_plane = ((block_header & 0x04) and (plane_def != 0x00));
        else:
            plane_def = [0x00,0x55,0xaa,0xff][(block_header>>2) & 0x03]
            decode_only_1_pb8_plane = False;
        is_M_plane = False
        if decode_only_1_pb8_plane:
            single_pb8_buf = bytearray()
            try:
                pb8_flags = next(cblock_iter)
                bytes_processed += 1
            except StopIteration:
                if not allow_partial:
                    raise ValueError("Unexpected end at pb8 flags of plane {}".format(block_offset//8), bytes_processed)
                else:
                    pb8_flags = 0x00
                    plane_def = 0x00
            single_pb8_buf.append(pb8_flags)
            for i in range(bin(pb8_flags).count("1")):
                try:
                    cur_byte = next(cblock_iter)
                    bytes_processed += 1
                except StopIteration:
                    if not allow_partial:
                        raise ValueError("Unexpected end at pb8 byte -{} of plane {}".format(i+1, block_offset//8), bytes_processed)
                    else:
                        pb8_flags = 0x00
                        plane_def = 0x00
                single_pb8_buf.append(cur_byte)
        for block_offset in range(0,64,8):
            cur_byte = 0x00
            if block_header & 0x10 and is_M_plane:
                cur_byte = 0xff
            if block_header & 0x20 and not is_M_plane:
                cur_byte = 0xff
            plane[0:8] = [cur_byte]*8
            if plane_def & 0x80:
                if decode_only_1_pb8_plane:
                    cblock_iter = iter(single_pb8_buf)
                try:
                    pb8_flags = next(cblock_iter)
                    if not decode_only_1_pb8_plane:
                        bytes_processed += 1
                except StopIteration:
                    if not allow_partial:
                        raise ValueError("Unexpected end at pb8 flags of plane {}".format(block_offset//8), bytes_processed)
                    else:
                        pb8_flags = 0x00
                        plane_def = 0x00
                for i in range(7,-1,-1):
                    pb8_flags = pb8_flags << 1
                    if pb8_flags & 0x0100:
                        try:
                            cur_byte = next(cblock_iter)
                            if not decode_only_1_pb8_plane:
                                bytes_processed += 1
                        except StopIteration:
                            if not allow_partial:
                                raise ValueError("Unexpected end at pb8 byte -{} of plane {}".format(i+1, block_offset//8), bytes_processed)
                            else:
                                pb8_flags = 0x00
                                plane_def = 0x00
                    plane[i] = cur_byte
                if block_header & 0x01:
                    plane[0:8] = (sum(((plane[x] >> y)&0b1) << x for x in range(8)) for y in range(8))
            block[block_offset:block_offset+8] = plane
            if is_M_plane:
                for i in range(8):
                    plane[i] = block[block_offset + i - 8] ^ block[block_offset + i]
                if block_header & 0x80:
                    block[block_offset-8:block_offset] = plane
                if block_header & 0x40:
                    block[block_offset:block_offset+8] = plane
            plane_def = (plane_def << 1) & 0xff
            is_M_plane = not is_M_plane
    return (bytes(block), bytes_processed)

def fill_dont_care_bits(plane, dont_care_mask=b'\xff'*8, top_value=0x00, xor_bg=b'\x00'*8):
    if dont_care_mask == b'\xff'*8:
        return plane
    result_plane = bytearray(8)
    backwards_smudge_plane = bytearray(8)
    cur_byte = top_value
    for i in range(8):
        mask = dont_care_mask[i]
        cur_byte = (plane[i] & mask) | (cur_byte & ~mask)
        backwards_smudge_plane[i] = (cur_byte & mask) | ((cur_byte ^ xor_bg[i]) & ~mask)
    prev_byte = top_value
    for i in range(7,-1,-1):
        new_byte = plane[i]
        mask = dont_care_mask[i]
        if new_byte & mask == prev_byte & mask:
            cur_byte = (new_byte & mask) | (prev_byte & ~mask)
        else:
            cur_byte = (new_byte & mask) | (backwards_smudge_plane[i] & ~mask)
        result_plane[i] = (cur_byte & mask) | ((cur_byte ^ xor_bg[i]) & ~mask)
        prev_byte = cur_byte
    return bytes(result_plane)

def compress_single_block(block, dont_care_mask=b'\xff'*64, use_bit_flip=True):
    if len(block) != 64 or len(dont_care_mask) != 64:
        raise ValueError("input block and \"dont care mask\" must be 64 bytes.")
    cblock_choices = [b'\x2a' + block]
    for t in range(24):
        attempt_type = ((t & 0x1e) << 3) | (t & 0x01)
        if not use_bit_flip and attempt_type & 0x01:
            continue
        cblock = [b'']
        plane_def = 0
        for plane_l, plane_m, mask_l, mask_m in ((block[i+0:i+8], block[i+8:i+16], dont_care_mask[i+0:i+8], dont_care_mask[i+8:i+16]) for i in range(0,64,16)):
            plane_def = plane_def << 2
            if attempt_type & 0x01:
                plane_l, plane_m = flip_plane_bits_135(plane_l), flip_plane_bits_135(plane_m)
            top_value_l = 0xff if attempt_type & 0x20 else 0x00
            top_value_m = 0xff if attempt_type & 0x10 else 0x00
            if mask_l != b'\xff'*8 or mask_m != b'\xff'*8:
                if attempt_type & 0x01:
                    mask_l, mask_m = flip_plane_bits_135(mask_l), flip_plane_bits_135(mask_m)
                plane_l = fill_dont_care_bits(plane_l, mask_l, top_value_l)
                plane_m = fill_dont_care_bits(plane_m, mask_m, top_value_m)
                if attempt_type & 0x80:
                    plane_l = fill_dont_care_bits(plane_l, mask_l, top_value_l, plane_m)
                if attempt_type & 0x40:
                    plane_m = fill_dont_care_bits(plane_m, mask_m, top_value_m, plane_l)
            if attempt_type & 0xc0 != 0x00:
                plane_xor = bytes(l^m for l , m in zip(plane_l, plane_m))
                if attempt_type & 0x80:
                    plane_l = plane_xor
                if attempt_type & 0x40:
                    plane_m = plane_xor
            cplane_l = pb8_pack_plane(plane_l, top_value_l)
            if cplane_l != b'\x00':
                cblock.append(cplane_l)
                plane_def = plane_def | 2
            cplane_m = pb8_pack_plane(plane_m, top_value_m)
            if cplane_m != b'\x00':
                cblock.append(cplane_m)
                plane_def = plane_def | 1
        short_planes_type = next((i for i, t in enumerate([0x00,0x55,0xaa,0xff]) if plane_def == t), -1)
        if short_planes_type < 0:
            attempt_type |= 0x02
            cblock[0] = bytes([attempt_type, plane_def])
        else:
            attempt_type |= (short_planes_type << 2)
            cblock[0] = bytes([attempt_type])
        cblock_result = b''.join(cblock)
        if dont_care_mask == b'\xff'*64:
            assert block == decompress_single_block(cblock_result)[0]
        else:
            assert bytes(i&m for i, m in zip(block, dont_care_mask)) == bytes(i&m for i, m in zip(decompress_single_block(cblock_result)[0], dont_care_mask))
        cblock_choices.append(cblock_result)
    result = min(cblock_choices, key=cblock_cost)
    return result

def get_blocks_from_compressed_bytes(cblock_iter, number_of_blocks=float("inf"), allow_partial=False):
    cblock_iter = iter(cblock_iter)
    total_bytes_processed = 0
    total_blocks = 0
    while total_blocks < number_of_blocks:
        try:
            block, bytes_processed = decompress_single_block(cblock_iter, allow_partial)
        except ValueError as error:
            raise ValueError("At byte {}, for block {}: {}".format(total_bytes_processed + error.args[1], total_blocks, error.args[0])) from error
        if block is None:
            break
        total_bytes_processed += bytes_processed
        yield block
        total_blocks += 1

def get_cblocks_from_bytes(block_iter, number_of_blocks=float("inf"), use_bit_flip=True, allow_partial=False):
    block_iter = iter(block_iter)
    total_blocks = 0
    while total_blocks < number_of_blocks:
        block = bytes(i for _, i in zip(range(64), block_iter))
        block_len = len(block)
        if block_len == 0:
            break
        if block_len < 64:
            if not allow_partial:
                raise ValueError("Last block is less than 64 bytes.")
            else:
                block = block + b'\x00'*(64-block_len)
                block_mask = b'\xff'*block_len + b'\x00'*(64-block_len)
        else:
            block_mask = b'\xff'*64
        yield compress_single_block(block, block_mask, use_bit_flip)
        total_blocks += 1

def compress(data, use_bit_flip=True, allow_partial=False):
    return b''.join(get_cblocks_from_bytes(data, use_bit_flip=use_bit_flip, allow_partial=allow_partial))

def decompress(data, allow_partial=False):
    return b''.join(get_blocks_from_compressed_bytes(data, allow_partial=allow_partial))

import sys
import os
import itertools

class FileIterContextHack():
    def __init__(self, fn, mode, ask_file_overwrite=True):
        if fn == '-':
            if mode == 'rb':
                self.fd = sys.stdin.buffer
                self.file_name = "<stdin>"
            elif mode == 'wb' or mode == 'xb':
                self.fd = sys.stdout.buffer
                self.file_name = "<stdout>"
            self.file_size = 0
            self.exit_needs_closed = False
        else:
            self.file_name = fn
            if mode not in {'rb', 'wb', 'xb'}:
                raise ValueError("File mode must be binary.")
            try:
                self.fd = open(self.file_name, mode)
            except FileExistsError as error:
                if ask_file_overwrite:
                    print("{0} already exists; do you wish to overwrite (y/N) ? ".format(self.file_name), end='', file=sys.stderr)
                    overwrite_answer = input()
                else:
                    raise error
                if overwrite_answer[0:1].lower() == 'y':
                    self.fd = open(self.file_name, 'wb')
                else:
                    print("    not overwritten", file=sys.stderr)
                    sys.exit()
            self.file_size = os.stat(self.fd.fileno()).st_size
            self.exit_needs_closed = True
        self.read_iter = itertools.chain.from_iterable(
            iter(lambda: self.fd.read1(8192), b'')
        ) if mode == "rb" else None
        self.bytes_transfered = 0
    def __enter__(self):
        return self
    def __exit__(self, *args):
        if self.exit_needs_closed:
            self.fd.close()
    def __iter__(self):
        return self
    def __next__(self):
        byte = next(self.read_iter)
        self.bytes_transfered += 1
        return byte
    def __len__(self):
        return self.file_size
    def read(self, size=-1):
        bytes = self.fd.read(size)
        self.bytes_transfered += len(bytes)
        return bytes
    def write(self, b):
        number_written = self.fd.write(b)
        self.bytes_transfered += number_written
        return number_written

def main(argv=None):
    import sys
    import argparse

    parser = argparse.ArgumentParser(description='Donut NES Codec', usage='%(prog)s [options] [-d] input [-o] output')
    parser.add_argument('--version', action='version', version='%(prog)s 1.7.1')
    parser.add_argument('input', metavar='files', help='Path to the folder with the input files')
    parser.add_argument('output', metavar='FILE', help='Path to the output folder')
    parser.add_argument('-d', '--decompress', help='decompress the input files', action='store_true')
    parser.add_argument('-f', '--force',  help='overwrite output without prompting', action='store_true')
    parser.add_argument('-q', '--quiet', help='suppress messages and completion stats', action="store_true")
    parser.add_argument('--no-bit-flip', help="don't encode plane flipping", action="store_true")
    options = parser.parse_args(argv)

    if not options.output and len(options.input) > 1:
        options.output = options.input.pop()
    if '-' not in options.input and not sys.stdin.isatty():
        options.input.append('-')
    if options.output is None and not sys.stdout.isatty():
        options.output = '-'
    if not options.input or not options.output:
        if not options.quiet:
            parser.print_usage(file=sys.stderr)
        sys.exit(1)

    output_file_mode = 'wb' if options.force else 'xb'
    ask_for_overwrite = not options.quiet and sys.stdin.isatty()
    indir = Path(options.input)
    outdir = Path(options.output)
    outdir.mkdir(parents=True, exist_ok=True)
    for fn in indir.glob("*"):
        with FileIterContextHack(outdir.joinpath(fn.stem + '.bin'), output_file_mode, ask_for_overwrite) as output_file:
            total_input_bytes = 0
            total_output_bytes = 0
            with FileIterContextHack(fn, 'rb') as input_file:
                if options.decompress:
                    page = []
                    for block in get_blocks_from_compressed_bytes(input_file):
                        page.append(block)
                        if len(page) >= 128:
                            output_file.write(b''.join(page))
                            page.clear()
                    if len(page) > 0:
                        output_file.write(b''.join(page))
                        page.clear()
                else:
                    page = []
                    for block in get_cblocks_from_bytes(input_file, use_bit_flip=(not options.no_bit_flip), allow_partial=True):
                        page.append(block)
                        if len(page) >= 128:
                            output_file.write(b''.join(page))
                            page.clear()
                    if len(page) > 0:
                        output_file.write(b''.join(page))
                        page.clear()
                if not options.quiet:
                    r = input_file.bytes_transfered
                    w = output_file.bytes_transfered - total_output_bytes
                    try:
                        ratio = 1 - (r / w) if options.decompress else 1 - (w / r)
                    except ZeroDivisionError:
                        if r == w:
                            ratio = 0
                        else:
                            ratio = float('NaN')
                    output_file.write(b'\xff')
                    print("{} :{:>6.1%} ({} => {} bytes, {})".format(input_file.file_name, ratio, r, w, output_file.file_name), file=sys.stderr)
                    total_input_bytes += r
                    total_output_bytes += w
            if not options.quiet and len(options.input) > 1:
                r = total_input_bytes
                w = total_output_bytes
                ratio = 1-(r / w) if options.decompress else 1-(w / r)
                print("<total> :{:>6.1%} ({} => {} bytes, {})".format(ratio, r, w, output_file.file_name), file=sys.stderr)

if __name__ == "__main__":
    main()
