from gfx import *
import draw, heb
P = 'graphics/contest/applause.png'
f = load_head(P)
# English text: rows 7-13, index 5 on 4, x 8..49 (inside the frame).
draw.replace(f, 6, 7, 51, 13, {5: 4})
m = draw.text('תשואות', 'W5_7')
top, bot = draw.crop_rows(m)
m = m[top:bot + 1]
x = draw.place_center(m, 7, 50)
draw.paint(f, m, x, 7, 5)
f.save(gpaths.write_target(P))
print(pair(P, 6))
