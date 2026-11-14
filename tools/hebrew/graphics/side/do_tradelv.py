from kit import *
from check import check
P = 'graphics/trade/menu.png'
f = load_head(P)
# The trade menu's Pokémon box (menu_mon_box.bin) has the level label on its top edge, over the
# level digits: tile 130 in column 4, and in column 5 the tile trade.c picks by gender, 131 (none),
# 132 (male) or 133 (female). English "Lv.": 3-row letters, ink 15 on the box colour 4, rows 5..7
# of tile 130, with the dot in column 0 of 131..133; the gender symbols take columns 2..6.
# The font's level mark רמה (LVC_B10 in hebrew_glyph_designs.txt, the narrowest) is 11 px wide, and
# the label has 9 (tile 130 and column 0 of 131..133, column 1 kept clear of the symbol). So the
# label is רמ', the abbreviation the Union Room trade board prints for the same LV. header
# (union_room.h), with the mark's own resh and mem and a 1-px geresh as the narrower fonts draw it.
# 5-row letters on rows 3..7, as tall as the mark, bottom-aligned with the gender symbols.
INK, BOX, TOP = 15, 4, 3
mark = [r for r in heb.SETS['LVC_B10']['רמה'] if '#' in r]
MEM = [r[4:7] for r in mark]
RESH = [r[8:11] for r in mark]
GERESH = ['#', '#', '.', '.', '.']
m = [g + '.' + mm + '.' + rr for g, mm, rr in zip(GERESH, MEM, RESH)]
s = TileStrip(f, [[130, 131]])
draw.replace(s, 0, 2, 15, 7, {INK: BOX})
draw.paint(s, m, 0, TOP, INK)
s.put_back()
# Column 0 of the male and female tiles is the same as tile 131's.
tw = f.width // 8
for t in (132, 133):
    for y in range(8):
        f.put((t % tw) * 8, (t // tw) * 8 + y, f.get((131 % tw) * 8, (131 // tw) * 8 + y))
print("LV. רמ'", width(m))
print(save_and_pair(f, P, 6, region=(136, 24, 48, 8)))

e, g = load_head(P), load(P)
ok, a, b, ac, bc = check(P)
used = lambda im: {im.get(x, y) for y in range(im.height) for x in range(im.width)}
moved = {(x, y) for y in range(g.height) for x in range(g.width) if g.get(x, y) != e.get(x, y)}
tiles = {(x // 8) + (y // 8) * tw for x, y in moved}
assert ok and g.palette == e.palette and used(g) <= used(e) and tiles <= {130, 131, 132, 133}, (ok, tiles)
print('pixel rules OK: size, depth, palette and chunks as English; indices', sorted(used(g)),
      '; changed tiles', sorted(tiles), len(moved), 'px')
