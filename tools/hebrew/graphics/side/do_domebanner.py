from kit import *
from check import check
P = 'data/tilesets/secondary/battle_dome/tiles.png'
f = load_head(P)
# BATTLE FRONTIER on the banner along the Battle Dome battle room's top wall. The banner repeats
# every 7 metatiles: emblem (258), the panel's end piece (259), text tiles 260..269 over 276..285,
# end piece 259 again. Only the text tiles change; no map places them outside the banner.
# English: 7-row white (5) letters with 1-px strokes on the panel blue 10, rows 4..10 of the
# 80x16 text strip, each letter's left stem lit by 11 on its left.
# Hebrew חזית הקרב (MAPSEC_BATTLE_FRONTIER, as the Frontier Pass map header) in the installed font's
# 7-row W5_7 letters, centred; qof's descender takes rows 11..12.
s = TileStrip(f, [list(range(260, 270)), list(range(276, 286))])
draw.replace(s, 0, 2, 79, 13, {5: 10, 11: 10})
GAP, SPACE = 2, 5
vis = list(reversed('חזית הקרב'))
glyphs = [None if ch == ' ' else glyph_rows('W5_7', ch, 0, 2) for ch in vis]
w = sum(SPACE if g is None else len(g[0]) for g in glyphs) + GAP * sum(
    1 for a, b in zip(glyphs, glyphs[1:]) if a is not None and b is not None)
x = (80 - w) // 2
for k, g in enumerate(glyphs):
    if g is None:
        x += SPACE
        continue
    draw.paint(s, g, x, 4, 5)
    # The light on the left: left of each row's first ink pixel when it is part of a stem.
    for r, row in enumerate(g):
        i = row.find('#')
        if i < 0:
            continue
        stem = any(0 <= rr < len(g) and g[rr][i] == '#' for rr in (r - 1, r + 1))
        if stem and s.get(x + i - 1, 4 + r) == 10:
            s.put(x + i - 1, 4 + r, 11)
    x += len(g[0]) + (GAP if k + 1 < len(glyphs) and glyphs[k + 1] is not None else 0)
s.put_back()
print('BATTLE FRONTIER w', w)
print(save_and_pair(f, P, 6, region=(0, 128, 128, 16)))
# Pixel rules: same PNG apart from IDAT, no index the English file lacks, only the text tiles changed.
e = load_head(P)
ok = check(P)[0] and e.palette == f.palette and not set(f.pixels) - set(e.pixels)
moved = {(y // 8) * 16 + x // 8 for y in range(e.height) for x in range(e.width) if e.get(x, y) != f.get(x, y)}
allowed = set(range(260, 270)) | set(range(276, 286))
print(P, 'OK' if ok and moved <= allowed else 'BAD', sorted(moved))
assert ok and moved <= allowed
