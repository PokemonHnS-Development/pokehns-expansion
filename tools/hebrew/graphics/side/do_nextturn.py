from gfx import *
import draw, heb
P = 'graphics/contest/nextturn.png'
f = load_head(P)
# English "NEXT TURN": rows 2-6, index 15 on 8, x 2..45; tile 6 (x 48-55) receives the turn digit.
draw.replace(f, 0, 2, 47, 6, {15: 8})
m = heb.word('בתור הבא', 'M5', asc=0, desc=0)
x = draw.place_right(m, 44)   # keep a 3 px gap before the digit tile, as the English does
draw.paint(f, m, x, 2, 15)
f.save(gpaths.write_target(P))
print(pair(P, 8))
