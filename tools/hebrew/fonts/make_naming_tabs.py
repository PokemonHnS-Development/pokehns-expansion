#!/usr/bin/env python3
"""Draw the Hebrew build's naming-screen page tabs.

    python3 make_naming_tabs.py TREE        # writes TREE/graphics/naming_screen/page_swap_{hebrew,latin}.png
    python3 make_naming_tabs.py TREE --show # also prints them as ASCII art

The tabs are 40x8 indexed PNGs in the format of page_swap_upper.png: the label sits in the first
24 columns (the sprite shows 3 tiles), ink is index 1, the shadow (right, below and below-right of
every ink pixel, as in the fonts) and the background are the tab's colour pair in buttons.pal
(6/7 blue, 8/9 orange, 10/11 green), and columns 24-39 are index 0.

- page_swap_hebrew.png: "עברית" in blue, for the Hebrew page (the first page, blue keyboard).
  The letters are the W4_7 set of hebrew_glyph_designs.txt (small_narrower's 4-column letters,
  7 body rows), the same size as the 4x7 capitals of "UPPER".
- page_swap_latin.png: "ABC" in orange, for the Latin capitals page (the second page, orange
  keyboard). The capitals are drawn in the style of "UPPER".
"""
import argparse
import os
import re

from PIL import Image

HERE = os.path.dirname(os.path.abspath(__file__))
DESIGNS = os.path.join(HERE, "hebrew_glyph_designs.txt")

LATIN = {
    "A": [".##.", "#..#", "#..#", "#..#", "####", "#..#", "#..#"],
    "B": ["###.", "#..#", "#..#", "###.", "#..#", "#..#", "###."],
    "C": [".##.", "#..#", "#...", "#...", "#...", "#..#", ".##."],
}


def load_hebrew(set_name):
    """Glyph -> list of 7 rows (body rows 4-10 of the design cell), trimmed to the ink width."""
    glyphs, cur, name = {}, None, None
    for line in open(DESIGNS, encoding="utf8"):
        line = line.rstrip("\n")
        if line.startswith("@set"):
            cur, name = line.split()[1], None
        elif line.startswith("@glyph"):
            name = line.split()[1]
            if cur == set_name:
                glyphs[name] = []
        elif cur == set_name and name and re.match(r"^[#.]+\s+\d+", line):
            pixels, row = line.split()[:2]
            if 4 <= int(row) <= 10:
                glyphs[name].append(pixels)
    out = {}
    for ch, rows in glyphs.items():
        width = max((r.rfind("#") + 1 for r in rows), default=0)
        out[ch] = [r[:width] for r in rows]
    return out


def draw(glyph_rows, start, shadow, background):
    """Glyphs (already in visual order) placed left to right from column start."""
    ink = set()
    x = start
    for rows in glyph_rows:
        width = len(rows[0])
        for y, row in enumerate(rows):
            for dx, c in enumerate(row):
                if c == "#":
                    ink.add((x + dx, y))
        x += width + 1  # one column for the shadow, as in "UPPER"
    img = Image.new("P", (40, 8), 0)
    ref = Image.open(TEMPLATE)
    img.putpalette(ref.getpalette())
    px = img.load()
    for yy in range(8):
        for xx in range(24):
            px[xx, yy] = background
    for (xx, yy) in ink:
        for sx, sy in ((1, 0), (0, 1), (1, 1)):
            p = (xx + sx, yy + sy)
            if p not in ink and p[0] < 24 and p[1] < 8:
                px[p] = shadow
    for (xx, yy) in ink:
        if xx < 24:
            px[xx, yy] = 1
    return img, x - 1


def show(img):
    px = img.load()
    for y in range(8):
        print("".join({1: "#", 0: " "}.get(px[x, y], "o" if px[x, y] in (6, 8, 10) else ".")
                      for x in range(24)))


if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("tree")
    ap.add_argument("--show", action="store_true")
    a = ap.parse_args()
    gfx = os.path.join(a.tree, "graphics", "naming_screen")
    TEMPLATE = os.path.join(gfx, "page_swap_upper.png")

    heb = load_hebrew("W4_7")
    word = "עברית"
    visual = [heb[c] for c in reversed(word)]
    hebrew, end = draw(visual, 1, 6, 7)
    assert end <= 24, end
    hebrew.save(os.path.join(gfx, "page_swap_hebrew.png"))

    latin, end = draw([LATIN[c] for c in "ABC"], 5, 8, 9)
    assert end <= 24, end
    latin.save(os.path.join(gfx, "page_swap_latin.png"))

    if a.show:
        show(hebrew)
        print()
        show(latin)
