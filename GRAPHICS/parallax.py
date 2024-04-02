#!/usr/bin/env python3
#
# Bitmap to multi-console CHR converter using Pillow
# (with PB8 instead of PackBits)
#
# Copyright 2014-2015 Damian Yerrick
# Copying and distribution of this file, with or without
# modification, are permitted in any medium without royalty
# provided the copyright notice and this notice are preserved.
# This file is offered as-is, without any warranty.

from PIL import Image
from time import sleep
import array

# python 2/3 cross compatibility fixes
try:
    xrange
except NameError:
    xrange = range
try:
    raw_input
except NameError:
    raw_input = input
try:
    next
except NameError:
    next = lambda x: x.next()

def formatTilePlanar(tile, planemap, hflip=False, little=False):
    """Turn a tile into bitplanes.

Planemap opcodes:
10 -- bit 1 then bit 0 of each tile
0,1 -- planar interleaved by rows
0;1 -- planar interlaved by planes
0,1;2,3 -- SNES/PCE format

"""
    hflip = 7 if hflip else 0
    if (tile.size != (8, 8)):
        return None
    pixels = list(tile.getdata())
    pixelrows = [pixels[i:i + 8] for i in xrange(0, 64, 8)]
    if hflip:
        for row in pixelrows:
            row.reverse()
    out = bytearray()

    planemap = [[[int(c) for c in row]
                 for row in plane.split(',')]
                for plane in planemap.split(';')]
    # format: [tile-plane number][plane-within-row number][bit number]

    # we have five (!) nested loops
    # outermost: separate planes
    # within separate planes: pixel rows
    # within pixel rows: row planes
    # within row planes: pixels
    # within pixels: bits
    for plane in planemap:
        for pxrow in pixelrows:
            for rowplane in plane:
                rowbits = 1
                thisrow = bytearray()
                for px in pxrow:
                    for bitnum in rowplane:
                        rowbits = (rowbits << 1) | ((px >> bitnum) & 1)
                        if rowbits >= 0x100:
                            thisrow.append(rowbits & 0xFF)
                            rowbits = 1
                if little: thisrow.reverse()
                out.extend(thisrow)
    return out

def pilbmp2chr(im, tileWidth=8, tileHeight=8,
               formatTile=lambda im: formatTilePlanar(im, "0;1")):
    """Convert a bitmap image into a list of byte strings representing tiles."""
    im.load()
    (w, h) = im.size
    outdata = []
    for mt_y in range(0, h, tileHeight):
        for mt_x in range(0, w, tileWidth):
            metatile = im.crop((mt_x, mt_y,
                                mt_x + tileWidth, mt_y + tileHeight))
            for tile_y in range(0, tileHeight, 8):
                for tile_x in range(0, tileWidth, 8):
                    tile = metatile.crop((tile_x, tile_y,
                                          tile_x + 8, tile_y + 8))
                    data = formatTile(tile)
                    outdata.append(data)
    return outdata

def parallaxify():
    # due to absolute laziness, this loads parallax.bmp in the same folder
    # and generates 32 horizontally scrolled versions of the background
    import os
    curpath = os.path.abspath(os.path.dirname(__file__))
    with open(f"{curpath}/parallax.bmp", "rb") as fin:
        orig_img = Image.open(fin)
        im = orig_img.copy()
        im = im.resize((128, 32))
        
        with open(f"{curpath}/parallax/parallax_0.chr", "wb") as fout:
            outdata = b''.join(pilbmp2chr(orig_img))
            fout.write(outdata)
        for i in range(0, 144):
            # shift the main image over by i pixels
            shifted = orig_img.crop((144 - i, 0, (144+48) - i, 72))
            # shifted.save(f"{curpath}/temp/test{i}.png")
            top_region = shifted.crop((0, 0, 48, 32))
            mid_region = shifted.crop((0, 32, 48, 64))
            bot1_region = shifted.crop((0, 64, 24, 72))
            bot2_region = shifted.crop((24, 64, 48, 72))
            im.paste(0, (0,0,128,32))
            im.paste(top_region, (0, 0, 48, 32))
            im.paste(mid_region, (48, 0, 96, 32))
            im.paste(bot1_region, (96, 0, 120, 8))
            im.paste(bot2_region, (96, 8, 120, 16))
            
            with open(f"{curpath}/parallax/parallax_{i}.chr", "wb") as fout:
                outdata = b''.join(pilbmp2chr(im))
                fout.write(outdata)


if __name__ == "__main__":
    parallaxify()
