from gfx import *
import draw, heb
P = 'graphics/pokeblock/use_screen/updown.png'
f = load_head(P)
# Two 32x16 frames: "UP" (fill 1, outline 2) and "DOWN" (fill 1, outline 3); letters with 2-px
# strokes both ways and a 1-px outline all round, as the English. Transparent = 0.
draw.fill(f, 0, 0, 31, 31, 0)
up = heb.word('עלה', 'C9', gap=2, asc=2, desc=0)
dn = heb.word('ירד', 'C9', gap=2, asc=0, desc=0)
x = draw.place_center(up, 0, 31)
draw.paint(f, up, x, 2, 1, outline=2, outline_diag=2)     # body rows 4-12
x = draw.place_center(dn, 0, 31)
draw.paint(f, dn, x, 19, 1, outline=3, outline_diag=3)    # body rows 19-27 (English 20-27)
f.save(gpaths.write_target(P))
print(len(up[0]), len(dn[0]), pair(P, 8))
