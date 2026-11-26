#!/usr/bin/env python3
"""Hoenn & Seek (2.0 part 13b): battle backgrounds of their own for Hoenn places.

    gen_hoenn_battle_art.py              write the art, the C tables and the headers
    gen_hoenn_battle_art.py --mock DIR   only draw every style of every background to DIR

Reads the "art" section of data/hoenn/battle_environments.json. Each background starts
from one of HnS's modern battle backgrounds (graphics/battle_environment/<base>/: a 512x256
scene in tiles.png + map.bin, the entry strip in anim_tiles.png + anim_map.bin, and a day
palette with optional morning/night ones), then:

  * "palettes": colour overrides per palette file ("palette", "palette_morning",
    "palette_night"), as {"index": [r, g, b]}; index 0-47 covers the three battle
    palettes (the scene uses its tile's palette, the entry strip the third one).
    A base without a morning/night file falls back to its day palette before overriding.
  * "copies": tile blocks moved inside the scene, [from_col, from_row, to_col, to_row, w, h]
    on the 64x32 tile grid (used to clear the beach's palm trees off the desert);
  * "ridges": skylines (dunes) drawn as smooth curves through "points", filled down to
    "to" with the "fill" colour, a "rim" colour on top and "shade" on the falling slopes;
  * "stamps": small pictures drawn into the scene at pixel positions, from "sprites"
    (rows of characters: '.' keeps the pixel, a hex digit is a colour index of the
    palette the tile already uses).

A background can hold several "styles" (mockups); "style" picks the one that is built.
The scene is re-tiled afterwards (identical and mirrored tiles shared), so stamps cost
only the tiles they touch. Output goes to graphics/battle_environment/hoenn_<name>/,
src/data/graphics/hoenn_battle_environment.h (INCBINs) and src/data/hoenn_battle_art.h
(the background table and the map table read by src/hoenn_battle_bg.c).
"""
import json, os, shutil, struct, sys
from PIL import Image

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..")
P = lambda *a: os.path.join(ROOT, *a)
GFX = "graphics/battle_environment"
PAL_FILES = ["palette", "palette_morning", "palette_night"]
COLS, ROWS = 64, 32  # the scene is two 32x32 screen blocks side by side


def read_pal(path):
    lines = open(P(path)).read().split("\n")
    n = int(lines[2])
    return [tuple(int(c) for c in l.split()[:3]) for l in lines[3:3 + n]]


def write_pal(path, cols):
    with open(P(path), "w") as f:
        f.write("JASC-PAL\n0100\n%d\n" % len(cols))
        for c in cols:
            f.write("%d %d %d\n" % c)


def read_tiles(path):
    im = Image.open(P(path))
    w, h = im.size
    px = im.load()
    return [[[px[tx * 8 + x, ty * 8 + y] & 15 for x in range(8)] for y in range(8)]
            for ty in range(h // 8) for tx in range(w // 8)]


def read_map(path):
    d = open(P(path), "rb").read()
    return list(struct.unpack("<%dH" % (len(d) // 2), d))


def cell(col, row):
    """Map entry index of scene cell (col, row): two 32x32 blocks, left then right."""
    return (col // 32) * 1024 + row * 32 + col % 32


class Scene:
    """The background as 64x32 cells, each an 8x8 pixel grid (flips applied) + palette."""

    def __init__(self, base):
        tiles = read_tiles(f"{GFX}/{base}/tiles.png")
        ents = read_map(f"{GFX}/{base}/map.bin")
        assert len(ents) == COLS * ROWS, base
        self.cells = {}
        for row in range(ROWS):
            for col in range(COLS):
                e = ents[cell(col, row)]
                t, hf, vf = tiles[e & 0x3FF], (e >> 10) & 1, (e >> 11) & 1
                px = [[t[7 - y if vf else y][7 - x if hf else x] for x in range(8)] for y in range(8)]
                self.cells[col, row] = [px, e >> 12]

    def copy(self, fc, fr, tc, tr, w, h):
        src = {(c, r): [[row[:] for row in self.cells[fc + c, fr + r][0]], self.cells[fc + c, fr + r][1]]
               for c in range(w) for r in range(h)}
        for (c, r), v in src.items():
            self.cells[tc + c, tr + r] = v

    def stamp(self, sprite, x0, y0):
        for y, line in enumerate(sprite):
            for x, ch in enumerate(line):
                if ch == ".":
                    continue
                X, Y = x0 + x, y0 + y
                self.cells[X // 8, Y // 8][0][Y % 8][X % 8] = int(ch, 16)

    def ridge(self, r):
        """A skyline (dunes, hills) through r["points"], filled down to y = r["to"]."""
        import math
        pts = r["points"]
        for x in range(COLS * 8):
            i = max(k for k in range(len(pts) - 1) if pts[k][0] <= x) if x < pts[-1][0] else len(pts) - 2
            (x0, y0), (x1, y1) = pts[i], pts[i + 1]
            t = (1 - math.cos(math.pi * (x - x0) / (x1 - x0))) / 2  # smooth between points
            top = round(y0 + (y1 - y0) * t)
            falling = y1 > y0
            for y in range(top, r["to"]):
                c = self.cells[x // 8, y // 8]
                if c[1] != 2:
                    continue
                ch = r["rim"] if y == top else (r["shade"] if falling and y - top < 3 else r["fill"])
                c[0][y % 8][x % 8] = int(ch, 16)

    def image(self, pal):
        im = Image.new("RGB", (COLS * 8, ROWS * 8))
        px = im.load()
        for (col, row), (p, pn) in self.cells.items():
            for y in range(8):
                for x in range(8):
                    i = (pn - 2) * 16 + p[y][x]
                    px[col * 8 + x, row * 8 + y] = pal[i] if 0 <= i < len(pal) else (0, 0, 0)
        return im

    def retile(self):
        """Tiles (deduplicated, mirrors shared) and map entries. Tile 0 stays blank."""
        tiles, index, ents = [[[0] * 8 for _ in range(8)]], {}, [0] * (COLS * ROWS)
        index[tuple(map(tuple, tiles[0]))] = (0, 0, 0)
        for (col, row), (p, pn) in sorted(self.cells.items(), key=lambda kv: (kv[0][1], kv[0][0])):
            hit = None
            for hf in (0, 1):
                for vf in (0, 1):
                    key = tuple(tuple(p[7 - y if vf else y][7 - x if hf else x] for x in range(8)) for y in range(8))
                    if key in index and hit is None:
                        hit = (index[key][0], hf, vf)
            if hit is None:
                index[tuple(map(tuple, p))] = (len(tiles), 0, 0)
                hit = (len(tiles), 0, 0)
                tiles.append(p)
            t, hf, vf = hit
            ents[cell(col, row)] = t | hf << 10 | vf << 11 | pn << 12
        assert len(tiles) <= 512, len(tiles)  # BG_CHAR_ADDR(2) holds 512 tiles before the screen blocks
        return tiles, ents


def palettes(base, over):
    """The three palettes of a background with its overrides applied."""
    out = {}
    day = read_pal(f"{GFX}/{base}/palette.pal")
    for f in PAL_FILES:
        path = f"{GFX}/{base}/{f}.pal"
        pal = read_pal(path) if os.path.exists(P(path)) else list(day)
        pal = pal + [(0, 0, 0)] * (48 - len(pal))
        for i, rgb in over.get(f, {}).items():
            pal[int(i)] = tuple(rgb)
        out[f] = pal
    return out


def build(name, bg, sprites, style_name):
    style = bg["styles"][style_name]
    base = style.get("base", bg["base"])
    scene = Scene(base)
    for c in style.get("copies", []):
        scene.copy(*c)
    for r in style.get("ridges", []):
        scene.ridge(r)
    for s in style.get("stamps", []):
        scene.stamp(sprites[s["sprite"]], *s["at"])
    return scene, palettes(base, style.get("palettes", {})), base


def save_sheet(path, tiles, pal):
    w = 16
    h = (len(tiles) + w - 1) // w
    im = Image.new("P", (w * 8, h * 8))
    im.putpalette([v for c in pal[:16] for v in c] + [0] * (768 - 48))
    for i, t in enumerate(tiles):
        for y in range(8):
            for x in range(8):
                im.putpixel(((i % w) * 8 + x, (i // w) * 8 + y), t[y][x])
    im.save(P(path))


def camel(name):
    return "".join(w.capitalize() for w in name.split("_"))


def mock(outdir):
    cfg = json.load(open(P("data/hoenn/battle_environments.json")))["art"]
    os.makedirs(outdir, exist_ok=True)
    for name, bg in cfg["backgrounds"].items():
        shots = []
        for style_name in bg["styles"]:
            scene, pals, _ = build(name, bg, cfg["sprites"], style_name)
            for f in PAL_FILES:
                # Two 240x112 views (the area above the text box): the left edge and the far half.
                im = scene.image(pals[f])
                shots.append(im.crop((0, 0, 240, 112)))
                shots.append(im.crop((272, 0, 512, 112)))
        grid = Image.new("RGB", (480, 112 * len(shots) // 2), "white")
        for i, s in enumerate(shots):
            grid.paste(s, ((i % 2) * 240, (i // 2) * 112))
        grid.resize((grid.width * 2, grid.height * 2), Image.NEAREST).save(os.path.join(outdir, f"{name}.png"))
        print(name, "->", os.path.join(outdir, f"{name}.png"), "styles:", list(bg["styles"]))


def main():
    if len(sys.argv) > 2 and sys.argv[1] == "--mock":
        return mock(sys.argv[2])
    cfg = json.load(open(P("data/hoenn/battle_environments.json")))
    art = cfg["art"]
    incbins, table, ids = [], [], {}
    for n, (name, bg) in enumerate(art["backgrounds"].items()):
        scene, pals, base = build(name, bg, art["sprites"], bg["style"])
        tiles, ents = scene.retile()
        out = f"{GFX}/hoenn_{name}"
        os.makedirs(P(out), exist_ok=True)
        save_sheet(f"{out}/tiles.png", tiles, pals["palette"])
        open(P(f"{out}/map.bin"), "wb").write(struct.pack("<%dH" % len(ents), *ents))
        for f in PAL_FILES:
            write_pal(f"{out}/{f}.pal", pals[f])
        for f in ["anim_tiles.png", "anim_map.bin"]:
            shutil.copyfile(P(f"{GFX}/{base}/{f}"), P(f"{out}/{f}"))
        c = "Hoenn" + camel(name)
        incbins += [
            f'const u32 gBattleEnvironmentTiles_{c}[] = INCBIN_U32("{out}/tiles.4bpp.smol");',
            f'const u32 gBattleEnvironmentTilemap_{c}[] = INCBIN_U32("{out}/map.bin.smolTM");',
            f'const u32 gBattleEnvironmentAnimTiles_{c}[] = INCBIN_U32("{out}/anim_tiles.4bpp.smol");',
            f'const u32 gBattleEnvironmentAnimTilemap_{c}[] = INCBIN_U32("{out}/anim_map.bin.smolTM");',
            f'const u16 gBattleEnvironmentPalette_{c}[] = INCBIN_U16("{out}/palette.gbapal");',
            f'const u16 gBattleEnvironmentPalette_{c}Morning[] = INCBIN_U16("{out}/palette_morning.gbapal");',
            f'const u16 gBattleEnvironmentPalette_{c}Night[] = INCBIN_U16("{out}/palette_night.gbapal");',
        ]
        table.append(f"    [HOENN_BATTLE_BG_{name.upper()}] = {{gBattleEnvironmentTiles_{c}, gBattleEnvironmentTilemap_{c}, "
                     f"gBattleEnvironmentAnimTiles_{c}, gBattleEnvironmentAnimTilemap_{c}, "
                     f"{{gBattleEnvironmentPalette_{c}, gBattleEnvironmentPalette_{c}Morning, gBattleEnvironmentPalette_{c}Night}}}},")
        ids[name] = n
        print(f"{name}: style {bg['style']}, {len(tiles)} tiles")

    import gen_hoenn_battle_bgs as B  # map constants and rule lookup, shared with part 20a's generator
    kept = json.load(open(P("data/hoenn/maps.json")))["items"]
    rows = []
    for rule in art["maps"]:
        for name in sorted(kept):
            if name == rule["map"] or (rule["map"].endswith("_") and name.startswith(rule["map"])):
                m = json.load(open(P("data/maps", name, "map.json")))
                time = rule.get("time", "HOENN_BATTLE_BG_ANY_TIME")
                rows.append(f"    {{{m['id']}, BATTLE_ENVIRONMENT_{rule['environment']}, "
                            f"HOENN_BATTLE_BG_{rule['background'].upper()}, {time}}},")

    with open(P("src/data/graphics/hoenn_battle_environment.h"), "w") as f:
        f.write("// Generated by tools/hoenn/gen_hoenn_battle_art.py (2.0 part 13b). Included by src/hoenn_battle_bg.c.\n")
        f.write("\n".join(incbins) + "\n")
    with open(P("src/data/hoenn_battle_art.h"), "w") as f:
        f.write("// Generated by tools/hoenn/gen_hoenn_battle_art.py from data/hoenn/battle_environments.json\n")
        f.write("// (2.0 part 13b). Included by src/hoenn_battle_bg.c.\n\n")
        f.write("enum {\n" + "".join(f"    HOENN_BATTLE_BG_{k.upper()},\n" for k in ids) + "};\n\n")
        f.write("static const struct HoennBattleBg sHoennBattleBgs[] = {\n" + "\n".join(table) + "\n};\n\n")
        f.write("// {map, environment it replaces, background, time of day it always uses}\n")
        f.write("static const struct HoennBattleBgMap sHoennBattleBgMaps[] = {\n" + "\n".join(rows) + "\n};\n\n")
        sand = [json.load(open(P("data/maps", n, "map.json")))["id"] for n in art.get("sand_maps", [])]
        f.write("// Maps where sand tiles give the sand environment despite the map's own default.\n")
        f.write("static const u16 sHoennSandMaps[] = {" + ", ".join(sand) + "};\n")


if __name__ == "__main__":
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    main()
