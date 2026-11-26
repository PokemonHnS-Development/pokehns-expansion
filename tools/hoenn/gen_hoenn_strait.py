#!/usr/bin/env python3
"""Hoenn & Seek (2.0 part 14): the Tidal Strait's two map layouts.

Reads data/hoenn/strait.json and writes data/layouts/<Map>/map.bin and border.bin for
each half of the strait, then opens the Route 41 rocks at "route41_gap".

Each row is one line of the map: '~' is the half's water metatile, a letter is a 2x2
stamp copied (metatile, collision and elevation) from the source layout at the given
top-left tile, and '.' is a cell a stamp already covers. The west half copies Route 41's
blocks (Johto tiles), the east half Route 105's (Hoenn tiles), so each half joins its
neighbour seamlessly through a normal map connection; the seam between the halves is a
warp (see the maps' scripts.inc). Re-runs give the same files.
"""
import json, os, struct

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..")
P = lambda *a: os.path.join(ROOT, *a)


def layouts():
    return {l["id"]: l for l in json.load(open(P("data/layouts/layouts.json")))["layouts"] if "id" in l}


def read_blocks(lay):
    d = open(P(lay["blockdata_filepath"]), "rb").read()
    return list(struct.unpack("<%dH" % (len(d) // 2), d))


def build(name, m, lays):
    src = lays[m["source"]]
    sb, sw = read_blocks(src), src["width"]
    rows = m["rows"]
    w, h = len(rows[0]), len(rows)
    assert all(len(r) == w for r in rows), name
    water = int(m["water"], 0)
    out = [water] * (w * h)
    for y, row in enumerate(rows):
        for x, ch in enumerate(row):
            if ch in "~.":
                continue
            fx, fy = m["stamps"][ch]
            for j in (0, 1):
                for i in (0, 1):
                    assert rows[y + j][x + i] == (ch if i == j == 0 else "."), (name, x, y)
                    out[(y + j) * w + x + i] = sb[(fy + j) * sw + fx + i]
    lay = lays[m["layout"]]
    assert (lay["width"], lay["height"]) == (w, h), (name, w, h)
    open(P(lay["blockdata_filepath"]), "wb").write(struct.pack("<%dH" % len(out), *out))
    open(P(lay["border_filepath"]), "wb").write(struct.pack("<4H", *[int(m["border"], 0)] * 4))
    print(f"{name}: {w}x{h}")


def open_gap(gap, lays):
    lay = lays[gap["layout"]]
    b = read_blocks(lay)
    for x, y in gap["tiles"]:
        b[y * lay["width"] + x] = int(gap["water"], 0)
    open(P(lay["blockdata_filepath"]), "wb").write(struct.pack("<%dH" % len(b), *b))


def main():
    cfg = json.load(open(P("data/hoenn/strait.json")))
    lays = layouts()
    for name, m in cfg["maps"].items():
        build(name, m, lays)
    open_gap(cfg["route41_gap"], lays)


if __name__ == "__main__":
    main()
