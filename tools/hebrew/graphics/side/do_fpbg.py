from kit import *
P = 'graphics/frontier_pass/bg.png'
f = load_head(P)
# Header "FRONTIER PASS": 13-row white (1) letters with 2-px stems on blue 14, no shadow;
# tiles 16..30 / 32..46 = x 0..119, rows 8..23. Hebrew in wide bold letters, centred on the English.
draw.replace(f, 0, 9, 119, 23, {1: 14})
# 11-row body on rows 10..20, the size of the BATTLE FRONTIER header (map_screen.png).
m = lay('כרטיס החזית', 'B11w', 2, asc=0, desc=0, space=6)
x = draw.place_center(m, 4, 118)
draw.paint(f, m, x, 10, 1)
print('FRONTIER PASS', width(m), x)
# CANCEL button (cancel.bin / cancel_highlighted.bin): 9-row letters, ink 4 (edge 3) on 1,
# highlighted ink 13 (edge 12); text area x 13..71 of the 9x2-tile strip, rows 3..11.
for rows, inks, ink in [([[0x39, 0x3a, 0x8c, 0x8d, 0x8e, 0x8f, 0xac, 0xad, 0xae], [0x49, 0x4a, 0x9c, 0x9d, 0x9e, 0x9f, 0xbc, 0xbd, 0xbe]], (3, 4), 4),
                        ([[0x3, 0x4, 0xcc, 0xcd, 0xce, 0xcf, 0xec, 0xed, 0xee], [0xa, 0xb, 0xdc, 0xdd, 0xde, 0xdf, 0xfc, 0xfd, 0xfe]], (12, 13), 13)]:
    s = TileStrip(f, rows)
    draw.replace(s, 13, 2, 71, 12, {v: 1 for v in inks})
    m = lay('ביטול', 'B9m', 2, asc=1, desc=0)
    x = draw.place_center(m, 13, 63)
    draw.paint(s, m, x, 2, ink)
    s.put_back()
    print('CANCEL', width(m), x)
from fpcard import card
card(f, 184)
# A second copy of the card at y 64..119 (tiles that no tilemap of the screen references) gets
# the same labels, so a future use shows Hebrew too.
card(f, 64)
print(save_and_pair(f, P, 3))
