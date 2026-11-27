#!/usr/bin/env python3
"""Hoenn & Seek (2.0 part 15a): small new maps painted from an existing layout's blocks.

Reads data/hoenn/composed_maps.json and writes data/layouts/<Map>/map.bin and
border.bin for each map in "maps", then applies "patches" to existing layouts.

A map starts empty and runs its "ops" in order; each op paints a rectangle with
blocks copied (metatile, collision and elevation) from the map's "source" layout:

  {"at": [x, y, w, h], "from": [sx, sy]}                  copy the w x h blocks at sx,sy
  {"at": [x, y, w, h], "from": [sx, sy], "tile": [pw, ph]} repeat the pw x ph patch at sx,sy
                                                           across the rectangle, anchored at x,y
  {"cells": [[x, y], ...], "from": [sx, sy]}               copy one block to each cell
  {"grid": ["..TT..", ...], "at": [x, y], "legend": {"T": {"from": [sx, sy], "tile": [2, 2]}}}
      paint by hand: each character is a legend entry (" " and "." leave the cell as it is);
      an entry with "tile" repeats that patch anchored at the map's (0,0), so "from" is the
      patch block that lands on even (x, y); an entry with "metatile": "0x1e6" keeps the
      collision and elevation of its "from" block but draws that metatile instead (for
      a piece no layout uses yet, 2.0 part 30a)
Any op or legend entry may take "src": LAYOUT_X to copy from another layout with the same
primary tileset; its blocks must be primary metatiles, or that layout must also share the
secondary tileset (checked).

Keeping the rows' and columns' parity between source and destination keeps 2x2
patterns (trees, checkered grass) lined up. "border" is the 2x2 border's top-left
block in the source, or "source" for the source layout's own border (2.0 part 28:
the Ruins' black border has no 2x2 block of its own in the map). Every cell must be painted.

A patch changes blocks of an existing layout in place:
  {"layout": L, "cells": [[x, y], ...], "from": [sx, sy]}  copies the layout's own block
                                                           at sx,sy (which no patch may change)
  {"layout": L, "clear_collision": [[x, y], ...]}          makes those blocks passable
                                                           (opens a fake door, for example)
  {"layout": L, "grid": [...], "at": [x, y], "legend": {...}}  paints by hand, like a map's
                                                           grid op; legend blocks come from the
                                                           layout itself (cells no patch paints)
                                                           or from "src"
Re-runs give the same files. Check the result with tools/hoenn/render_layout.py.
"""
import json, os, struct

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..")
P = lambda *a: os.path.join(ROOT, *a)
COLLISION = 0x0C00
PRIMARY_METATILES = 640  # NUM_METATILES_IN_PRIMARY (HnS layouts)


def layouts():
    return {l["id"]: l for l in json.load(open(P("data/layouts/layouts.json")))["layouts"] if "id" in l}


def with_metatile(entry, block):
    """A legend entry's block, with its "metatile" drawn instead if it names one."""
    if "metatile" not in entry:
        return block
    return (block & ~0x3FF) | int(entry["metatile"], 16)


def read_blocks(lay):
    d = open(P(lay["blockdata_filepath"]), "rb").read()
    return list(struct.unpack("<%dH" % (len(d) // 2), d))


def write_blocks(lay, blocks):
    open(P(lay["blockdata_filepath"]), "wb").write(struct.pack("<%dH" % len(blocks), *blocks))


def build(name, m, lays):
    src = lays[m["source"]]
    sb, sw = read_blocks(src), src["width"]
    lay = lays[m["layout"]]
    w, h = lay["width"], lay["height"]
    out = [None] * (w * h)
    get = lambda sx, sy: sb[sy * sw + sx]

    def getter(op):
        if "src" not in op:
            return get
        other = lays[op["src"]]
        assert other["primary_tileset"] == lay["primary_tileset"], (name, op)
        ob, ow = read_blocks(other), other["width"]
        same_sec = other["secondary_tileset"] == lay["secondary_tileset"]

        def g(sx, sy):
            b = ob[sy * ow + sx]
            assert same_sec or (b & 0x3FF) < PRIMARY_METATILES, (name, op["src"], sx, sy, "secondary metatile")
            return b
        return g

    for op in m["ops"]:
        if "grid" in op:
            x0, y0 = op["at"]
            for j, row in enumerate(op["grid"]):
                for i, ch in enumerate(row):
                    if ch in " .":
                        continue
                    e = op["legend"][ch]
                    x, y = x0 + i, y0 + j
                    assert x < w and y < h, (name, "grid outside the map", x, y)
                    pw, ph = e.get("tile", [1, 1])
                    sx, sy = e["from"]
                    out[y * w + x] = with_metatile(e, getter(e)(sx + x % pw, sy + y % ph))
            continue
        g = getter(op)
        sx, sy = op["from"]
        if "cells" in op:
            for x, y in op["cells"]:
                out[y * w + x] = g(sx, sy)
            continue
        x0, y0, rw, rh = op["at"]
        pw, ph = op.get("tile", [rw, rh])
        assert x0 + rw <= w and y0 + rh <= h, (name, op)
        for j in range(rh):
            for i in range(rw):
                out[(y0 + j) * w + x0 + i] = g(sx + i % pw, sy + j % ph)
    missing = [(i % w, i // w) for i, b in enumerate(out) if b is None]
    assert not missing, (name, "unpainted cells", missing[:8])
    write_blocks(lay, out)
    if m["border"] == "source":
        border = list(struct.unpack("<4H", open(P(src["border_filepath"]), "rb").read()))
    else:
        bx, by = m["border"]
        border = [get(bx, by), get(bx + 1, by), get(bx, by + 1), get(bx + 1, by + 1)]
    open(P(lay["border_filepath"]), "wb").write(struct.pack("<4H", *border))
    print(f"{name}: {w}x{h}")


def patch(p, lays):
    lay = lays[p["layout"]]
    b = read_blocks(lay)
    w = lay["width"]
    if "cells" in p:
        sx, sy = p["from"]
        assert [sx, sy] not in p["cells"], p
        for x, y in p["cells"]:
            b[y * w + x] = b[sy * w + sx]
    if "grid" in p:
        x0, y0 = p["at"]
        painted = {(x0 + i, y0 + j) for j, row in enumerate(p["grid"]) for i, ch in enumerate(row) if ch not in " ."}
        before = list(b)
        for j, row in enumerate(p["grid"]):
            for i, ch in enumerate(row):
                if ch in " .":
                    continue
                e = p["legend"][ch]
                x, y = x0 + i, y0 + j
                pw, ph = e.get("tile", [1, 1])
                sx, sy = e["from"][0] + x % pw, e["from"][1] + y % ph
                if "src" in e:
                    other = lays[e["src"]]
                    assert other["primary_tileset"] == lay["primary_tileset"], (p["layout"], e)
                    blk = read_blocks(other)[sy * other["width"] + sx]
                    assert other["secondary_tileset"] == lay["secondary_tileset"] or (blk & 0x3FF) < PRIMARY_METATILES, (p["layout"], e)
                else:
                    assert (sx, sy) not in painted, (p["layout"], "legend block inside the patch", sx, sy)
                    blk = before[sy * w + sx]
                b[y * w + x] = with_metatile(e, blk)
    for x, y in p.get("clear_collision", []):
        b[y * w + x] &= ~COLLISION
    write_blocks(lay, b)


def main():
    cfg = json.load(open(P("data/hoenn/composed_maps.json")))
    lays = layouts()
    for name, m in cfg["maps"].items():
        build(name, m, lays)
    for p in cfg["patches"]:
        patch(p, lays)


if __name__ == "__main__":
    main()
