#!/usr/bin/env python3
"""Hoenn & Seek 2.0 part 27a: Unown Cipher tiles for the Ruins of Alph.

Adds two sets of metatiles to the Ruins of Alph's secondary tileset
(data/tilesets/secondary/ruins_of_alph_writing_hns, shared by the puzzle
chambers, the four Words rooms and the Sinjoh Ruins):

- BRAILLE cells (all 26 letters) on the dark floor strip under the Words rooms'
  north wall (metatile 0x2E3). Each cell is 2 x 3 raised dots, 2 x 2 pixels
  each, at x 4-5 / 10-11 and y 4-5 / 8-9 / 12-13 of the 16 x 16 block, so dot
  row 1 sits in the block's top tiles and rows 2-3 in its bottom tiles. The
  four tiles of a cell only depend on the dots they hold, so the 26 cells need
  just 8 new tiles. The Rosetta line in Words Room 1 (part 27a) puts a braille
  cell straight above each Unown letter.
- GLOWING Unown letters for the night words (TOWER MOON ICE WHIRL MORTAR UNION
  FOAM): copies of the floor's letter blocks (0x310-0x32E) whose dark ink
  (colour 1) is redrawn in colour 14 and drawn with palette 10. Palettes 8 and
  10 are the same except colours 14-15, and no block that uses palette 10 draws
  colour 14 (checked below), so colour 14 of palette 10 becomes the glow.

Everything goes in fixed, empty slots (tiles from GLOW/BRAILLE_TILE_START,
metatiles from BRAILLE_METATILE_START), so re-running rewrites the same slots.
Writes src/data/hoenn_unown_tiles.h (letter -> metatile tables for
src/hoenn_cipher.c).

    tools/hoenn/gen_hoenn_unown_tiles.py [--mock out.png]
"""
import argparse, os, struct, sys
from PIL import Image

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..")
TS = os.path.join(ROOT, "data/tilesets/secondary/ruins_of_alph_writing_hns")
OUT_H = os.path.join(ROOT, "src/data/hoenn_unown_tiles.h")

SECONDARY_TILE_BASE = 640      # HnS primary tilesets hold 640 tiles
SECONDARY_METATILE_BASE = 0x280
FIRST_FREE_TILE = 318          # tiles.png slots 318-383 were blank before part 27a
FIRST_FREE_METATILE = 0x352    # metatiles after 0x350 were empty before part 27a

BRAILLE_METATILE_START = 0x360 # 26 cells, A-Z
GLOW_METATILE_START = 0x380    # the night words' letters, alphabetical
STRIP = 0x2E3                  # the dark floor strip under the north wall
INK, GLOW_INK = 1, 14
GLOW_PALETTE = 10
GLOW_RGB = (136, 232, 248)     # pale cyan: stands out on the olive floor at night
DOT_SHAPE = [[8, 2, None],     # 8 (240,240,216) and 2 (224,216,160): the lit bump
             [2, 2, 1],        # 1 (80,80,104): its shadow
             [None, 1, 1]]

WORDS = ["TOWER", "MOON", "ICE", "WHIRL", "MORTAR", "UNION", "FOAM"]  # Sun..Sat

# Standard braille (Hoenn's is the same alphabet): dots 1-3 left column top to
# bottom, 4-6 right column.
BRAILLE = {
    "A": "1", "B": "12", "C": "14", "D": "145", "E": "15", "F": "124",
    "G": "1245", "H": "125", "I": "24", "J": "245", "K": "13", "L": "123",
    "M": "134", "N": "1345", "O": "135", "P": "1234", "Q": "12345",
    "R": "1235", "S": "234", "T": "2345", "U": "136", "V": "1236",
    "W": "2456", "X": "1346", "Y": "13456", "Z": "1356",
}


def letter_metatile(c):
    """The floor's own (dark) Unown letter block, as HnS draws the Words rooms."""
    for start, row in ((0x310, "ABCDEFG"), (0x318, "HIJKLMN"), (0x320, "OPQRSTU"), (0x328, "VWXYZ!?")):
        if c in row:
            return start + row.index(c)
    raise KeyError(c)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--mock", help="also draw every new block to this PNG (4x)")
    a = ap.parse_args()

    im = Image.open(os.path.join(TS, "tiles.png"))
    px = im.load()
    tiles_w = im.size[0] // 8

    def get_tile(n):
        n -= SECONDARY_TILE_BASE
        tx, ty = n % tiles_w, n // tiles_w
        return [[px[tx * 8 + x, ty * 8 + y] & 15 for x in range(8)] for y in range(8)]

    def put_tile(n, t):
        n -= SECONDARY_TILE_BASE
        tx, ty = n % tiles_w, n // tiles_w
        for y in range(8):
            for x in range(8):
                px[tx * 8 + x, ty * 8 + y] = t[y][x]

    raw = open(os.path.join(TS, "metatiles.bin"), "rb").read()
    mt = list(struct.unpack("<%dH" % (len(raw) // 2), raw))
    raw = open(os.path.join(TS, "metatile_attributes.bin"), "rb").read()
    attrs = list(struct.unpack("<%dH" % (len(raw) // 2), raw))

    def entries(mid):
        i = (mid - SECONDARY_METATILE_BASE) * 8
        return mt[i:i + 8]

    def set_metatile(mid, ents, attr):
        i = mid - SECONDARY_METATILE_BASE
        mt[i * 8:i * 8 + 8] = ents
        attrs[i] = attr

    # Slots must be free (or hold what an earlier run wrote): nothing that was
    # there before part 27a may sit at or after the first free slot.
    n_slots = (im.size[0] // 8) * (im.size[1] // 8)
    for m in range(FIRST_FREE_METATILE, SECONDARY_METATILE_BASE + len(attrs)):
        if m >= BRAILLE_METATILE_START:
            continue
        if any(entries(m)):
            sys.exit("metatile 0x%X is in use; move BRAILLE_METATILE_START" % m)

    # Palette 10 must not draw colour 14 anywhere, or the glow would show up there.
    for m in range(SECONDARY_METATILE_BASE, BRAILLE_METATILE_START):
        for e in entries(m):
            if e and e >> 12 == GLOW_PALETTE and (e & 0x3FF) >= SECONDARY_TILE_BASE:
                if any(GLOW_INK in row for row in get_tile(e & 0x3FF)):
                    sys.exit("metatile 0x%X draws colour %d with palette %d" % (m, GLOW_INK, GLOW_PALETTE))

    next_tile = [SECONDARY_TILE_BASE + FIRST_FREE_TILE]

    def new_tile(t):
        n = next_tile[0]
        if n - SECONDARY_TILE_BASE >= n_slots:
            sys.exit("out of tile slots")
        put_tile(n, t)
        next_tile[0] += 1
        return n

    # ---- Braille ----------------------------------------------------------
    strip = entries(STRIP)
    tl, tr, bl, br = (e & 0x3FF for e in strip[:4])
    pal = strip[0] >> 12

    def with_dots(base, dots):
        t = [row[:] for row in get_tile(base)]
        for (x, y) in dots:
            # A raised bump: lit from the top left, shadow to the bottom right.
            for dy, row in enumerate(DOT_SHAPE):
                for dx, v in enumerate(row):
                    if v is not None and y + dy < 8 and x + dx < 8:
                        t[y + dy][x + dx] = v
        return t

    cache = {}

    def tile_for(base, dots):
        key = (base, tuple(sorted(dots)))
        if not dots:
            return base
        if key not in cache:
            cache[key] = new_tile(with_dots(base, dots))
        return cache[key]

    # Dot positions inside each 8x8 tile: column x 4 (left tile) or 2 (right
    # tile); row y 4 (top tile) or 0 / 4 (bottom tile).
    braille_ids = {}
    for i, c in enumerate("ABCDEFGHIJKLMNOPQRSTUVWXYZ"):
        d = BRAILLE[c]
        t_tl = tile_for(tl, [(4, 4)] if "1" in d else [])
        t_tr = tile_for(tr, [(2, 4)] if "4" in d else [])
        t_bl = tile_for(bl, [(4, y) for n, y in (("2", 0), ("3", 4)) if n in d])
        t_br = tile_for(br, [(2, y) for n, y in (("5", 0), ("6", 4)) if n in d])
        mid = BRAILLE_METATILE_START + i
        set_metatile(mid, [t | (pal << 12) for t in (t_tl, t_tr, t_bl, t_br)] + list(strip[4:]), attrs[STRIP - SECONDARY_METATILE_BASE])
        braille_ids[c] = mid

    # ---- Glowing letters --------------------------------------------------
    glow_letters = sorted(set("".join(WORDS)))
    glow_ids = {}
    gcache = {}
    for i, c in enumerate(glow_letters):
        src = letter_metatile(c)
        ents = []
        for e in entries(src)[:4]:
            t = e & 0x3FF
            tile = get_tile(t)
            if any(INK in row for row in tile):
                if t not in gcache:
                    gcache[t] = new_tile([[GLOW_INK if v == INK else v for v in row] for row in tile])
                t = gcache[t]
            ents.append(t | (e & 0x0C00) | (GLOW_PALETTE << 12))
        mid = GLOW_METATILE_START + i
        set_metatile(mid, ents + list(entries(src)[4:]), attrs[src - SECONDARY_METATILE_BASE])
        glow_ids[c] = mid

    im.save(os.path.join(TS, "tiles.png"))
    open(os.path.join(TS, "metatiles.bin"), "wb").write(struct.pack("<%dH" % len(mt), *mt))
    open(os.path.join(TS, "metatile_attributes.bin"), "wb").write(struct.pack("<%dH" % len(attrs), *attrs))

    # Palette 10, colour 14 = the glow.
    pal_path = os.path.join(TS, "palettes", "%02d.pal" % GLOW_PALETTE)
    text = open(pal_path, newline="").read()
    eol = "\r\n" if "\r\n" in text else "\n"
    lines = text.split(eol)
    lines[3 + GLOW_INK] = "%d %d %d" % GLOW_RGB
    open(pal_path, "w", newline="").write(eol.join(lines))

    with open(OUT_H, "w") as f:
        f.write("// Generated by tools/hoenn/gen_hoenn_unown_tiles.py (Hoenn & Seek 2.0 part 27a). Do not edit.\n")
        f.write("// Metatiles in gTileset_RuinsOfAlphWriting_Hns, indexed by letter (A = 0).\n\n")
        f.write("// Braille cells on the dark strip under the Words rooms' north wall.\n")
        f.write("static const u16 sHoennUnownBraille[26] = {\n")
        for c in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
            f.write("    0x%03X, // %s\n" % (braille_ids[c], c))
        f.write("};\n\n")
        f.write("// Glowing letters (0 = none: only the night words' letters glow).\n")
        f.write("static const u16 sHoennUnownGlow[26] = {\n")
        for c in "ABCDEFGHIJKLMNOPQRSTUVWXYZ":
            f.write("    0x%03X, // %s\n" % (glow_ids.get(c, 0), c))
        f.write("};\n")
    print("tiles %d-%d, braille 0x%X-0x%X, glow 0x%X-0x%X" % (
        SECONDARY_TILE_BASE + FIRST_FREE_TILE, next_tile[0] - 1, BRAILLE_METATILE_START,
        BRAILLE_METATILE_START + 25, GLOW_METATILE_START, GLOW_METATILE_START + len(glow_letters) - 1))

    if a.mock:
        sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
        from render_layout import read_pal
        pals = {p: read_pal("data/tilesets/secondary/ruins_of_alph_writing_hns/palettes/%02d.pal" % p) for p in range(7, 13)}
        ids = [braille_ids[c] for c in sorted(braille_ids)] + [glow_ids[c] for c in glow_letters]
        out = Image.new("RGB", (16 * 13, 16 * ((len(ids) + 12) // 13)))
        op = out.load()
        for k, mid in enumerate(ids):
            ox, oy = (k % 13) * 16, (k // 13) * 16
            for q, e in enumerate(entries(mid)[:4]):
                t, hf, vf, p = e & 0x3FF, (e >> 10) & 1, (e >> 11) & 1, e >> 12
                tile = get_tile(t)
                for y in range(8):
                    for x in range(8):
                        v = tile[7 - y if vf else y][7 - x if hf else x]
                        op[ox + (q % 2) * 8 + x, oy + (q // 2) * 8 + y] = pals[p][v]
        out.resize((out.width * 4, out.height * 4), Image.NEAREST).save(a.mock)


if __name__ == "__main__":
    main()
