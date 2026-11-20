from kit import *
from fpcard import card
P = 'graphics/frontier_pass/map_and_card.png'
f = load_head(P)
# The same mini trainer card as bg.png (same indices), at x 32..127, y 56..111.
card(f, 56, 32)
# A cut-out of the card's right part (IDNo, Poké Ball, badges) at x 0..31, y 8..47: IDNo is
# 4-row ink 31 / shadow 30 on stripes 26/27, rows 8..11.
erase_rows(f, 0, 8, 31, 11, {30, 31}, 31)
m = lay("מס' זיהוי", 'M4', 1, asc=0, desc=0, space=3)
draw.paint(f, m, 0, 8, 31, shadow=30, shadow_offsets=[(1, 0)], clip=(0, 8, 31, 11))
print('IDNo fragment', width(m))
print(save_and_pair(f, P, 4))
