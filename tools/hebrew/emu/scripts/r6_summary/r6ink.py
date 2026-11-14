#!/usr/bin/env python3
"""Ink extents of the text in every window the sweep shows, per screenshot and line, so that the
outliers of a right-aligned (or centred) column can be listed instead of read one by one.

    r6ink.py WHERE.json RUNDIR OUT.json

For each kind in WHERE.json (r6review.py) and each shot, the dark pixels (sum of RGB < 160) in the
window's lines give (minX, maxX). The report lists, per kind and line, the distribution of the
right edge (Hebrew text is right-aligned) and the shots whose ink leaves the window or whose right
edge differs from the column's usual one.
"""
import collections
import json
import os
import sys

from PIL import Image

# kind -> (x0, x1, [(y0, y1, ink colour) per line]); window edges from the templates, the ink
# colours sampled from the shots (text colour, not shadow or frame)
BLACK, GREY = (0, 0, 0), (99, 99, 99)
WIN = {
    "move_desc_sum": (80, 240, [(120, 136, BLACK), (136, 152, BLACK)]),
    "move_desc_rel": (8, 136, [(72, 88, GREY), (88, 104, GREY)]),
    "ability": (88, 232, [(72, 88, GREY), (88, 104, BLACK)]),
    "item": (80, 160, [(32, 48, BLACK)]),
}


def ink(im, x0, x1, y0, y1, col):
    px = im.load()
    xs = [x for y in range(y0, y1) for x in range(max(x0 - 8, 0), min(x1 + 8, 240)) if px[x, y][:3] == col]
    return (min(xs), max(xs)) if xs else None


def main():
    where, run, out = sys.argv[1:4]
    W = json.load(open(where))
    rep = {}
    for kind, (x0, x1, lines) in WIN.items():
        rows = []
        for ident, shots in W[kind].items():
            path = shots[0][0]
            f = os.path.join(run, path + ".png")
            if not os.path.exists(f):
                continue
            im = Image.open(f).convert("RGB")
            ext = [ink(im, x0, x1, a, b, c) for a, b, c in lines]
            rows.append(dict(id=int(ident), shot=path, ext=ext))
        stats = []
        for li in range(len(lines)):
            right = collections.Counter(r["ext"][li][1] for r in rows if r["ext"][li])
            left = collections.Counter(r["ext"][li][0] for r in rows if r["ext"][li])
            stats.append(dict(line=li, right=right.most_common(6), left_min=min(left) if left else None,
                              right_max=max(right) if right else None))
        rep[kind] = dict(n=len(rows), stats=stats, rows=rows)
        print("%-14s %4d shots" % (kind, len(rows)))
        for s in stats:
            print("   line %d right edges %s  leftmost ink %s  rightmost ink %s" % (
                s["line"], s["right"], s["left_min"], s["right_max"]))
    json.dump(rep, open(out, "w"), indent=0)


if __name__ == "__main__":
    main()
