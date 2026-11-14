from kit import *
from check import check
P = 'data/tilesets/secondary/department_store_hns/tiles.png'
f = load_head(P)
# The floor plates above the department store elevators read digit + F (1F .. 5F, and 6F through
# the building tileset's digit tile 201). Tile 132 is the F; no map places it outside the plates.
# The game's floor names are קומה 1 .. and the directory boards write ק1:, so the F becomes qof:
# right of the digit, read right to left as ק2.
# English F: 2-px strokes on x 1..5, rows 2..6, ink 14 on rows 2..3 and 15 on rows 4..6, a white
# (1) outline on the 8 neighbours, plate background 7 elsewhere; row 0 is the plate's frame.
# Qof: C5's qof (top bar, right stem, leg with one row below the stem) in the digits' 2-px strokes.
QOF = ['#####',
       '...##',
       '##.##',
       '##.##',
       '##...']
s = TileStrip(f, [[132]])
draw.fill(s, 0, 1, 7, 7, 7)
draw.paint(s, QOF, 1, 2, lambda px, py, r: 14 if py <= 3 else 15, outline=1, outline_diag=1,
           clip=(0, 1, 7, 7))
s.put_back()
print(save_and_pair(f, P, 8, region=(0, 48, 128, 32)))
# Pixel rules: same PNG apart from IDAT, no index the English file lacks, only tile 132 changed.
e = load_head(P)
ok = check(P)[0] and e.palette == f.palette and not set(f.pixels) - set(e.pixels)
moved = {(y // 8) * 16 + x // 8 for y in range(e.height) for x in range(e.width) if e.get(x, y) != f.get(x, y)}
print(P, 'OK' if ok and moved == {132} else 'BAD', sorted(moved))
assert ok and moved == {132}
