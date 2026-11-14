from kit import *
P = 'graphics/frontier_pass/map_screen.png'
f = load_head(P)
# "BATTLE FRONTIER": screen cells 2..17 of rows 0..1 = tiles 2..15 + 48, 49 (top) and
# 18..31 + 64, 65 (bottom). 13-row white (1) letters with 2-px stems on 14, no shadow.
s = TileStrip(f, [list(range(2, 16)) + [48, 49], list(range(18, 32)) + [64, 65]])
draw.replace(s, 0, 0, 127, 15, {1: 14})
# 11-row body (rows 2..12) so qof's descender fits on rows 13..14 above the tile edge.
m = lay('חזית הקרב', 'B11w', 2, asc=0, desc=2, space=6)
x = draw.place_center(m, 0, 127)
draw.paint(s, m, x, 2, 1)
s.put_back()
print('BATTLE FRONTIER', width(m), x)
print(save_and_pair(f, P, 4))
tm = read_bin('graphics/frontier_pass/map_screen.bin')
side_by_side([compose(load_head(P), tm, 32, 0, 3), compose(f, tm, 32, 0, 3)], ['EN', 'HE']).save(OUT + '/frontier_pass__map_screen_screen_pair.png')
