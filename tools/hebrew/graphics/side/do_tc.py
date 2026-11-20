from kit import *
P = 'graphics/trainer_card/tiles.png'
f = load_head(P)
# BADGES: 6-row letters with 2-px stems, ink 1 on the plain band 10, x 48..89, rows 1..6.
# Hebrew: semi-bold 6-row letters (main stem 2 px), left-aligned like the English.
draw.replace(f, 48, 0, 89, 7, {1: 10, 11: 10})   # 11: a stray stripe pixel inside the label
m = lay('תגים', 'S6', 2, asc=0, desc=0)
draw.paint(f, m, 49, 1, 1)
# The English label sits on a plain patch that ends where the band's stripes (11 on rows 1, 2, 5, 6)
# start at x 90; extend the stripes left to 2 px after the shorter Hebrew word.
for x in range(49 + width(m) + 2, 91):
    for y in (1, 2, 5, 6):
        f.put(x, y, 11)
print('BADGES', width(m))
# TRAINER CARD: 6-row black (15) letters on the blue tab 13 (rows 67..76 free, x 0..91).
# Hebrew: semi-bold 7-row letters on rows 68..74 (taller than the English so the Hebrew stays
# legible), final nun's descender on rows 75..76.
draw.replace(f, 0, 67, 91, 76, {15: 13, 8: 13})
m = lay('כרטיס מאמן', 'S7', 2, asc=0, desc=2, space=5)
x = draw.place_center(m, 1, 90)
draw.paint(f, m, x, 68, 15)
print('TRAINER CARD', width(m), x)
print(save_and_pair(f, P, 4))
