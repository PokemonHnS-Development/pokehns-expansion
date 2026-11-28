#!/usr/bin/env python3
"""Hoenn & Seek (2.0 part 12b): render a map layout to a PNG offline, for art mockups.

    render_layout.py LAYOUT_ID out.png [--secondary gTileset_X] [--pal N=file.pal ...]
                     [--bin map.bin] [--scale 2]

Reads data/layouts/layouts.json and the tileset definitions in src/data/tilesets/
(headers.h, graphics.h, metatiles.h, plus any hoenn_*.h there) to find each
tileset's tiles (the .png next to the .4bpp), palettes (.pal, JASC) and metatiles.
--secondary swaps the layout's secondary tileset; --pal N=file replaces palette N
(0-15) with a JASC .pal file, so a palette can be tried before it goes in the ROM.
Only the two metatile layers are drawn (no objects, no animations, no day/night
tint), which is enough to judge colours and shapes.
"""
import argparse, glob, json, os, re, struct
from PIL import Image

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..")
P = lambda *a: os.path.join(ROOT, *a)


def tileset_sources():
    text = ""
    for f in ["graphics.h", "metatiles.h", "headers.h"] + sorted(os.path.basename(x) for x in glob.glob(P("src/data/tilesets/hoenn_*.h"))):
        text += open(P("src/data/tilesets", f)).read() + "\n"
    text += open(P("src/graphics.c")).read()  # gTileset_General's tiles and palettes live here
    incbin = dict(re.findall(r"(g\w+)\[\]\s*=\s*INCBIN_U\d+\(\"([^\"]+)\"\)", text))
    pals = {}
    for m in re.finditer(r"(gTilesetPalettes_\w+)\[\]\[16\]\s*=\s*\{(.*?)\};", text, re.S):
        pals[m.group(1)] = re.findall(r"\"([^\"]+)\"", m.group(2))
    sets = {}
    for m in re.finditer(r"const struct Tileset (gTileset_\w+)\s*=\s*\{(.*?)\};", text, re.S):
        body = dict(re.findall(r"\.(\w+)\s*=\s*(\w+)", m.group(2)))
        sets[m.group(1)] = {"tiles": incbin.get(body.get("tiles")), "pals": pals.get(body.get("palettes"), []),
                            "metatiles": incbin.get(body.get("metatiles")), "secondary": body.get("isSecondary") == "TRUE"}
    return sets


def read_pal(path):
    path = re.sub(r"\.gbapal$", ".pal", path)
    lines = open(P(path)).read().split("\n")[3:19]
    return [tuple(int(c) for c in l.split()[:3]) for l in lines if l.strip()]


def read_tiles(path):
    png = re.sub(r"\.4bpp(\.\w+)*$", ".png", path)
    im = Image.open(P(png))
    w, h = im.size
    px = im.load()
    tiles = []
    for ty in range(h // 8):
        for tx in range(w // 8):
            tiles.append([[px[tx * 8 + x, ty * 8 + y] & 15 for x in range(8)] for y in range(8)])
    return tiles


def render(layout_id, out, secondary=None, pal_over=(), bin_path=None, scale=2):
    lay = next(l for l in json.load(open(P("data/layouts/layouts.json")))["layouts"] if l.get("id") == layout_id)
    sets = tileset_sources()
    prim, sec = sets[lay["primary_tileset"]], sets[secondary or lay["secondary_tileset"]]
    hns = lay.get("layout_version") != "emerald"
    nprim_tiles, nprim_pals, nprim_mt = (640, 7, 640) if hns else (512, 6, 512)
    tiles = read_tiles(prim["tiles"])[:nprim_tiles]
    tiles += [[[0] * 8 for _ in range(8)]] * (nprim_tiles - len(tiles))
    tiles += read_tiles(sec["tiles"])
    pals = [read_pal(f) for f in prim["pals"][:nprim_pals]] + [read_pal(f) for f in sec["pals"][nprim_pals:]]
    pals += [[(0, 0, 0)] * 16] * (16 - len(pals))
    for over in pal_over:
        n, f = over.split("=", 1)
        pals[int(n)] = read_pal(f)
    def mts(path):
        d = open(P(path), "rb").read()
        return struct.unpack("<%dH" % (len(d) // 2), d)
    pm, sm = mts(prim["metatiles"]), mts(sec["metatiles"])
    data = open(P(bin_path or lay["blockdata_filepath"]), "rb").read()
    blocks = struct.unpack("<%dH" % (len(data) // 2), data)
    W, H = lay["width"], lay["height"]
    img = Image.new("RGB", (W * 16, H * 16), pals[0][0])
    px = img.load()
    for by in range(H):
        for bx in range(W):
            mid = blocks[by * W + bx] & 0x3FF
            ents = pm[mid * 8:mid * 8 + 8] if mid < nprim_mt else sm[(mid - nprim_mt) * 8:(mid - nprim_mt) * 8 + 8]
            for layer in range(2):
                for i in range(4):
                    if layer * 4 + i >= len(ents): continue
                    e = ents[layer * 4 + i]
                    t, hf, vf, pal = e & 0x3FF, (e >> 10) & 1, (e >> 11) & 1, e >> 12
                    if t >= len(tiles): continue
                    tile = tiles[t]
                    for y in range(8):
                        for x in range(8):
                            c = tile[7 - y if vf else y][7 - x if hf else x]
                            if c == 0 and layer: continue
                            if c == 0: c = 0
                            px[bx * 16 + (i % 2) * 8 + x, by * 16 + (i // 2) * 8 + y] = pals[pal][c] if c or not layer else px[0, 0]
    if scale != 1:
        img = img.resize((img.width * scale, img.height * scale), Image.NEAREST)
    img.save(out)


if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("layout"); ap.add_argument("out")
    ap.add_argument("--secondary"); ap.add_argument("--pal", action="append", default=[])
    ap.add_argument("--bin"); ap.add_argument("--scale", type=int, default=2)
    a = ap.parse_args()
    render(a.layout, a.out, a.secondary, a.pal, a.bin, a.scale)
