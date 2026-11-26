#!/usr/bin/env python3
"""Hoenn & Seek (2.0 part 13a): secret base entrances drawn into Johto/Kanto tilesets.

Reads data/hoenn/base_entrances.json. Emerald's entrance metatiles (the cave indents, the
tree with vines, the shrub) live in Emerald's tilesets, which Johto and Kanto maps don't
load, and HnS's 640-entry primary tilesets are full. So each "host" (a Johto/Kanto
secondary tileset with room) gets two new metatiles appended to it, a closed entrance and
its open state, drawn over one of the host's own metatiles (a tree trunk, a rock face):

  * "kinds" hold the art: 16 rows of 16 characters for the closed and the open metatile.
    '.' keeps the base metatile's pixel; the letters are colour roles, matched against the
    palette of the layer that is painted (the top layer where it is opaque, else the bottom
    one): K darkest, D second darkest, M third darkest, H lightest, G and L the palette
    colours closest to a vine green and a light vine green. A kind can hold several
    "styles" (mockups); "style" picks the one that is built.
  * new 8x8 tiles go into blank tiles of the host's tiles.png that no metatile uses,
    taken from the end of the sheet; the metatile entries pointing at them drop their
    flips (the tile is stored the way it is drawn);
  * attributes: the base metatile's layer type with the kind's behavior
    (MB_SECRET_BASE_SPOT_* closed and *_OPEN, so Secret Power and the entrance script
    accept it).

Metatile IDs are host-local (secondary metatile n is ID 640 + n), so one ID means
different art in different hosts. secret_base.c looks entrances up by ID in one table
(sSecretBaseEntranceMetatiles, closed -> open and open -> closed), so the generator checks
that no closed ID of one host is an open ID of another (or of Emerald's own rows) and pads
a host by one blank metatile when they would clash.

Writes include/constants/hoenn_base_entrances.h: METATILE_HOENN_BASE_<HOST>[_OPEN] and
HOENN_SECRET_BASE_ENTRANCE_METATILES (rows appended to sSecretBaseEntranceMetatiles).
data/hoenn/base_entrance_slots.json records what was added to each host (metatile count
before, tiles used), so a re-run first takes it back out: re-runs give the same result.
Run tools/hoenn/gen_hoenn_base_spots.py afterwards (spots use these metatiles).
"""
import json, os, re, struct, sys
from PIL import Image

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..")
P = lambda *a: os.path.join(ROOT, *a)
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import render_layout as R  # tileset sources, palettes, tile sheets

NUM_PRIMARY = 640          # HnS primary tilesets: 640 tiles, 640 metatiles, 7 palettes
NUM_PRIMARY_PALS = 7
MAX_SECONDARY = 1024 - NUM_PRIMARY
EMERALD_ROWS = [(0x026, 0x036), (0x027, 0x037), (0x1A0, 0x1A1), (0x1A8, 0x1A9), (0x1B0, 0x1B1),
                (0x208, 0x210), (0x271, 0x278)]  # sSecretBaseEntranceMetatiles before ours
SLOTS = "data/hoenn/base_entrance_slots.json"
HEADER = "include/constants/hoenn_base_entrances.h"
VINE, LIGHT_VINE = (72, 136, 56), (136, 192, 88)


def load(path):
    return json.load(open(P(path)))


def behaviors():
    names = re.findall(r"^\s*(MB_\w+),", open(P("include/constants/metatile_behaviors.h")).read(), re.M)
    return {n: i for i, n in enumerate(names)}


def tileset_dir(name):
    return f"data/tilesets/secondary/{name}"


def read_sheet(path):
    im = Image.open(P(path))
    assert im.mode == "P", path
    return im


def sheet_tile(im, i):
    w = im.size[0] // 8
    tx, ty = i % w, i // w
    return [[im.getpixel((tx * 8 + x, ty * 8 + y)) & 15 for x in range(8)] for y in range(8)]


def put_tile(im, i, tile):
    w = im.size[0] // 8
    tx, ty = i % w, i // w
    for y in range(8):
        for x in range(8):
            im.putpixel((tx * 8 + x, ty * 8 + y), tile[y][x])


def roles(pal):
    """Palette index for each colour role (index 0 is transparent and never used)."""
    lum = lambda c: 0.3 * c[0] + 0.59 * c[1] + 0.11 * c[2]
    idx = sorted(range(1, 16), key=lambda i: (lum(pal[i]), i))
    near = lambda rgb: min(range(1, 16), key=lambda i: sum((a - b) ** 2 for a, b in zip(pal[i], rgb)))
    return {"K": idx[0], "D": idx[1], "M": idx[2], "H": idx[-1], "G": near(VINE), "L": near(LIGHT_VINE)}


class Host:
    def __init__(self, h, sets):
        self.name = h["tileset"]
        self.dir = tileset_dir(self.name)
        prim, sec = sets[h["primary"]], sets[h["secondary"]]
        self.prim_tiles = R.read_tiles(prim["tiles"])[:NUM_PRIMARY]
        self.pals = [R.read_pal(f) for f in prim["pals"][:NUM_PRIMARY_PALS]] + \
                    [R.read_pal(f) for f in sec["pals"][NUM_PRIMARY_PALS:]]
        d = open(P(prim["metatiles"]), "rb").read()
        self.prim_mt = list(struct.unpack("<%dH" % (len(d) // 2), d))
        self.prim_attr = open(P(re.sub(r"metatiles\.bin$", "metatile_attributes.bin", prim["metatiles"])), "rb").read()
        self.sheet = read_sheet(f"{self.dir}/tiles.png")
        d = open(P(f"{self.dir}/metatiles.bin"), "rb").read()
        self.mt = list(struct.unpack("<%dH" % (len(d) // 2), d))
        self.attr = bytearray(open(P(f"{self.dir}/metatile_attributes.bin"), "rb").read())

    def undo(self, slot):
        """Take a previous run's metatiles and tiles back out."""
        if not slot:
            return
        n = slot["metatiles_before"]
        self.mt, self.attr = self.mt[:n * 8], self.attr[:n * 2]
        for t in slot["tiles"]:
            put_tile(self.sheet, t, [[0] * 8 for _ in range(8)])

    def count(self):
        return len(self.mt) // 8

    def entries(self, mid):
        return list(self.prim_mt[mid * 8:mid * 8 + 8]) if mid < NUM_PRIMARY else \
               list(self.mt[(mid - NUM_PRIMARY) * 8:(mid - NUM_PRIMARY) * 8 + 8])

    def layer_attr(self, mid):
        a = self.prim_attr if mid < NUM_PRIMARY else self.attr
        i = mid if mid < NUM_PRIMARY else mid - NUM_PRIMARY
        return struct.unpack_from("<H", a, i * 2)[0] & 0xF000

    def tile(self, t):
        return self.prim_tiles[t] if t < NUM_PRIMARY else sheet_tile(self.sheet, t - NUM_PRIMARY)

    def free_tiles(self):
        """Blank sheet tiles no metatile refers to, last first."""
        used = {e & 0x3FF for e in self.mt}
        total = self.sheet.size[0] // 8 * (self.sheet.size[1] // 8)
        return [i for i in range(total - 1, -1, -1)
                if NUM_PRIMARY + i not in used and not any(any(r) for r in sheet_tile(self.sheet, i))]

    def paint(self, base_mid, art, free, used_tiles):
        """The base metatile's 8 entries with the art painted in; new tiles go into free."""
        ents = self.entries(base_mid)
        layers = []  # [layer][quadrant] -> 8x8 pixel rows as drawn (flips applied)
        for e in ents:
            t, hf, vf = e & 0x3FF, (e >> 10) & 1, (e >> 11) & 1
            src = self.tile(t)
            layers.append([[src[7 - y if vf else y][7 - x if hf else x] for x in range(8)] for y in range(8)])
        changed = set()
        for y, row in enumerate(art):
            assert len(row) == 16, row
            for x, ch in enumerate(row):
                if ch == ".":
                    continue
                q = (y // 8) * 2 + x // 8
                layer = 1 if layers[4 + q][y % 8][x % 8] else 0
                k = layer * 4 + q
                layers[k][y % 8][x % 8] = roles(self.pals[ents[k] >> 12])[ch]
                changed.add(k)
        for k in sorted(changed):
            t = free.pop(0)
            used_tiles.append(t)
            put_tile(self.sheet, t, layers[k])
            ents[k] = (ents[k] & 0xF000) | (NUM_PRIMARY + t)  # same palette, no flips
        return ents

    def append(self, ents, attr):
        assert self.count() < MAX_SECONDARY, self.name
        self.mt += ents
        self.attr += struct.pack("<H", attr)
        return NUM_PRIMARY + self.count() - 1

    def save(self):
        self.sheet.save(P(f"{self.dir}/tiles.png"))
        open(P(f"{self.dir}/metatiles.bin"), "wb").write(struct.pack("<%dH" % len(self.mt), *self.mt))
        open(P(f"{self.dir}/metatile_attributes.bin"), "wb").write(bytes(self.attr))


def main():
    cfg = load("data/hoenn/base_entrances.json")
    mb = behaviors()
    sets = R.tileset_sources()
    slots = load(SLOTS) if os.path.exists(P(SLOTS)) else {}
    new_slots, rows, defines = {}, [], []
    closed_ids = {c for c, _ in EMERALD_ROWS}
    open_ids = {o for _, o in EMERALD_ROWS}

    for h in cfg["hosts"]:
        host = Host(h, sets)
        host.undo(slots.get(host.name))
        before = host.count()
        kind = cfg["kinds"][h["kind"]]
        style = kind["styles"][h.get("style", kind["style"])]
        base = int(h["base_metatile"], 0)
        layer = host.layer_attr(base)
        free, used = host.free_tiles(), []
        closed_ents = host.paint(base, style["closed"], free, used)
        open_ents = host.paint(base, style["open"], free, used)

        # Pad until this host's pair clashes with no other row (see the header comment).
        while True:
            c, o = NUM_PRIMARY + host.count(), NUM_PRIMARY + host.count() + 1
            if c not in open_ids and o not in closed_ids and c not in closed_ids and o not in open_ids:
                break
            host.append([0] * 8, 0)
        c = host.append(closed_ents, layer | mb[kind["behavior"]])
        o = host.append(open_ents, layer | mb[kind["behavior"] + "_OPEN"])
        closed_ids.add(c)
        open_ids.add(o)
        host.save()

        const = f"METATILE_HOENN_BASE_{h['name']}"
        defines.append(f"#define {const:40s} 0x{c:03X}  // {host.name}: {h['kind']} over 0x{base:03X}")
        defines.append(f"#define {const + '_OPEN':40s} 0x{o:03X}")
        rows.append(f"    {{.closedMetatileId = {const}, .openMetatileId = {const}_OPEN}}, \\")
        new_slots[host.name] = {"metatiles_before": before, "tiles": sorted(used)}
        print(f"{host.name}: {h['kind']} 0x{c:03X}/0x{o:03X}, tiles {sorted(used)}")

    with open(P(SLOTS), "w") as f:
        json.dump(new_slots, f, indent=2)
        f.write("\n")
    with open(P(HEADER), "w") as f:
        f.write("// Generated by tools/hoenn/gen_hoenn_base_entrances.py from data/hoenn/base_entrances.json.\n")
        f.write("// Secret base entrances in Johto/Kanto tilesets (2.0 part 13a). Each ID is local to its\n")
        f.write("// host secondary tileset (named in the comment).\n")
        f.write("#ifndef GUARD_CONSTANTS_HOENN_BASE_ENTRANCES_H\n#define GUARD_CONSTANTS_HOENN_BASE_ENTRANCES_H\n\n")
        f.write("\n".join(defines) + "\n\n")
        f.write("// Rows appended to sSecretBaseEntranceMetatiles (src/secret_base.c).\n")
        f.write("#define HOENN_SECRET_BASE_ENTRANCE_METATILES \\\n" + "\n".join(rows) + "\n\n#endif\n")


if __name__ == "__main__":
    main()
