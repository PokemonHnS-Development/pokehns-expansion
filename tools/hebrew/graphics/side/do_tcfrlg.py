from kit import *
P = 'graphics/trainer_card/frlg/tiles.png'
f = load_head(P)
# Header: the game puts the TRAINER tiles (x 64..127, rows 24..39) left of the CARD tiles
# (x 64..95, rows 40..55): right to left that reads "כרטיס מאמן" with כרטיס in the CARD slot.
# English: 9-row yellow letters (8, inner bars 9) with 2-px stems on blue 10; no shadow.
draw.replace(f, 64, 27, 127, 37, {8: 10, 9: 10})
m = lay('מאמן', 'S9', 2, asc=0, desc=2)                  # final nun's descender on rows 37..38
draw.paint(f, m, draw.place_right(m, 118), 28, 8)     # ends where TRAINER ended (word gap kept)
print('TRAINER', width(m))
draw.replace(f, 64, 43, 95, 53, {8: 10, 9: 10})
m = lay('כרטיס', 'S9', 2, asc=0, desc=0)
draw.paint(f, m, 64, 44, 8)                           # starts where CARD started
print('CARD', width(m))
# BADGES: 5-row white (14) letters on 15, x 96..127, rows 42..46.
draw.replace(f, 96, 41, 127, 47, {14: 15})
m = lay('תגים', 'S5', 2, asc=0, desc=0)
draw.paint(f, m, 99, 42, 14)
print('BADGES', width(m))
# Back: "TRAINER:" in 6-row orange (5) letters on yellow 13, x 0..55, rows 72..77 (row 79 = rule).
draw.replace(f, 0, 72, 55, 77, {5: 13})
m = lay('מאמן', 'S5', 2, asc=0, desc=2)    # 5-row body so final nun's descender ends above the rule
x = draw.place_right(m, 52)
draw.paint(f, m, x, 72, 5)
for y in (74, 76):                                    # the colon at the word's logical end (left)
    f.put(x - 3, y, 5)
print('TRAINER:', width(m) + 3)
print(save_and_pair(f, P, 4))
