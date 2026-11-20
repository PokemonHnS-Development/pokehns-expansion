from kit import *
P = 'graphics/roulette/credit.png'
f = load_head(P)
# English "CREDIT": 7-row letters with 2-px stems on rows 8-14, colour 13 (rows 8-9), 15 (10-13),
# 14 (row 14); dark shadow 1 to the right and down-right; window interior is index 0, x 8..55.
# Hebrew: semi-bold 7-row letters from the 5-column strokes (main stem 2 px), same gradient and shadow.
draw.fill(f, 8, 8, 55, 15, 0)
m = lay('מטבעות', 'S7m', 2, asc=0, desc=0)
x = draw.place_center(m, 8, 55)
grad = lambda px, py, r: 13 if r <= 1 else (15 if r <= 5 else 14)
draw.paint(f, m, x, 8, grad, shadow=1, shadow_offsets=[(1, 0), (1, 1)], clip=(8, 8, 55, 15))
print('CREDIT', width(m))
print(save_and_pair(f, P, 8))
