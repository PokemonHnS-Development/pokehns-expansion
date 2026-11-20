#!/usr/bin/env python3
"""Render GBA text-mode tilemaps (.bin, u16 entries) with a tileset PNG, to see where label tiles land."""

import os
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from gfx import load, TREE, GIT, BASE_REF  # noqa: E402


def read_bin(path, ref=None, repo=None):
    if ref is None:
        data = open(os.path.join(repo or TREE, path), 'rb').read()
    else:
        data = subprocess.run(['git', '-C', repo or GIT, 'show', '%s:%s' % (ref, path)], capture_output=True, check=True).stdout
    return list(struct.unpack('<%dH' % (len(data) // 2), data))


def entries(tm, width=32):
    for i, e in enumerate(tm):
        yield i % width, i // width, e & 0x3FF, bool(e & 0x400), bool(e & 0x800), e >> 12


def tile_pixels(png, idx, base=0):
    t = idx - base
    tw = png.width // 8
    if t < 0 or t >= tw * (png.height // 8):
        return None
    tx, ty = (t % tw) * 8, (t // tw) * 8
    return [[png.get(tx + x, ty + y) for x in range(8)] for y in range(8)]


def render(tm, png, width=32, base=0, zoom=2, pal_rows=None, mark_tiles=None):
    """Screen image. Colours come from the PNG palette row (pal bits)*16 + low nibble when the PNG has
    256 colours, else from the PNG palette directly. Tiles outside the sheet draw dark grey."""
    from PIL import Image, ImageDraw
    height = (len(tm) + width - 1) // width
    im = Image.new('RGB', (width * 8, height * 8), (30, 30, 30))
    px = im.load()
    pal = png.palette
    for cx, cy, t, hf, vf, p in entries(tm, width):
        pix = tile_pixels(png, t, base)
        if pix is None:
            continue
        for y in range(8):
            for x in range(8):
                v = pix[7 - y if vf else y][7 - x if hf else x]
                if len(pal) > 16 and (v & 15) == v and pal_rows is not False:
                    c = pal[min(len(pal) - 1, p * 16 + v)] if p * 16 + v < len(pal) else pal[v]
                else:
                    c = pal[v] if v < len(pal) else (255, 0, 255)
                if (v & 15) == 0:
                    c = (30, 30, 30)
                px[cx * 8 + x, cy * 8 + y] = c
    im = im.resize((im.width * zoom, im.height * zoom), Image.NEAREST)
    if mark_tiles:
        d = ImageDraw.Draw(im)
        for cx, cy, t, hf, vf, p in entries(tm, width):
            if t - base in mark_tiles:
                d.rectangle([cx * 8 * zoom, cy * 8 * zoom, (cx + 1) * 8 * zoom - 1, (cy + 1) * 8 * zoom - 1], outline=(255, 0, 255))
    return im


def placements(tm, tiles, width=32, base=0):
    """{tile: [(cx, cy, hflip, vflip, pal)]} for the given sheet tile numbers."""
    out = {}
    for cx, cy, t, hf, vf, p in entries(tm, width):
        if t - base in tiles:
            out.setdefault(t - base, []).append((cx, cy, hf, vf, p))
    return out
