"""Small helpers for the Pokegear graphics: load indexed PNGs, render them with their own palette."""
import os
import sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import gpaths  # noqa: E402,F401  (puts tools/hebrew/fonts on the path)
import inspect_fonts as F
from PIL import Image, ImageDraw

def load(path):
    return F.FontPng.load(path, 'latin')

def to_image(f, zoom=4, grid=0):
    pal = f.palette
    im = Image.new('RGB', (f.width, f.height))
    px = im.load()
    for y in range(f.height):
        for x in range(f.width):
            v = f.get(x, y)
            px[x, y] = pal[v] if v < len(pal) else (255, 0, 255)
    im = im.resize((f.width * zoom, f.height * zoom), Image.NEAREST)
    if grid:
        d = ImageDraw.Draw(im)
        for x in range(0, f.width * zoom, grid * zoom):
            d.line([(x, 0), (x, f.height * zoom)], fill=(255, 0, 255))
        for y in range(0, f.height * zoom, grid * zoom):
            d.line([(0, y), (f.width * zoom, y)], fill=(255, 0, 255))
    return im

def pair(a, b, zoom=4, label=None, grid=0):
    ia, ib = to_image(a, zoom, grid), to_image(b, zoom, grid)
    top = 14 if label else 0
    im = Image.new('RGB', (ia.width + ib.width + 12, max(ia.height, ib.height) + top), (255, 255, 255))
    im.paste(ia, (0, top)); im.paste(ib, (ia.width + 12, top))
    if label:
        ImageDraw.Draw(im).text((2, 1), label, fill=(0, 0, 0))
    return im

def strips(f, sw, sh):
    """Cut the image into consecutive sw x sh sprite frames (row-major in the PNG) and lay them left to right."""
    from copy import deepcopy
    frames = []
    for y in range(0, f.height, sh):
        for x in range(0, f.width, sw):
            frames.append((x, y))
    return frames

def compose(f, sw, sh, zoom=4):
    """Displayed layout: frames side by side."""
    fr = strips(f, sw, sh)
    full = to_image(f, 1)
    out = Image.new('RGB', (sw * len(fr), sh))
    for i, (x, y) in enumerate(fr):
        out.paste(full.crop((x, y, x + sw, y + sh)), (i * sw, 0))
    return out.resize((out.width * zoom, out.height * zoom), Image.NEAREST)

def read_jasc(path):
    lines = open(path).read().split()
    n = int(lines[2])
    vals = list(map(int, lines[3:3 + 3 * n]))
    return [tuple(vals[i:i + 3]) for i in range(0, 3 * n, 3)]

def render_tilemap(f, binpath, width_tiles, pal=None, zoom=3, base_tile=0, pal_offset=0, mark_tiles=None):
    """Render a GBA text-BG tilemap using f's tiles (8x8, row-major). pal: list of RGB (all banks) or None."""
    import struct
    data = open(binpath, 'rb').read()
    ents = struct.unpack('<%dH' % (len(data) // 2), data)
    ntx = f.width // 8
    ntiles = ntx * (f.height // 8)
    h = (len(ents) + width_tiles - 1) // width_tiles
    im = Image.new('RGB', (width_tiles * 8, h * 8), (40, 0, 40))
    px = im.load()
    for i, e in enumerate(ents):
        t = (e & 0x3FF) - base_tile
        hf, vf, pb = (e >> 10) & 1, (e >> 11) & 1, (e >> 12) - pal_offset
        tx, ty = i % width_tiles, i // width_tiles
        if t < 0 or t >= ntiles:
            continue
        sx, sy = (t % ntx) * 8, (t // ntx) * 8
        for y in range(8):
            for x in range(8):
                xx = 7 - x if hf else x
                yy = 7 - y if vf else y
                v = f.get(sx + xx, sy + yy)
                if pal is not None:
                    idx = pb * 16 + v
                    c = pal[idx] if 0 <= idx < len(pal) else (255, 0, 255)
                else:
                    c = f.palette[v]
                px[tx * 8 + x, ty * 8 + y] = c
    return im.resize((im.width * zoom, im.height * zoom), Image.NEAREST), ents

def tile_usage(binpath):
    import struct
    data = open(binpath, 'rb').read()
    ents = struct.unpack('<%dH' % (len(data) // 2), data)
    use = {}
    for i, e in enumerate(ents):
        use.setdefault(e & 0x3FF, []).append((i, (e >> 10) & 3, e >> 12))
    return use
