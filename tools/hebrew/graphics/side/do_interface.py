from kit import *
P = 'graphics/contest/interface.png'
f = load_head(P)
# Category boxes: 9-row letters (2-px stems) in ink 77, shadow (box palette's dark) right/below/
# diagonal, on the box fill; border index 78 untouched. Box interior = x0+1..x0+38, y0+1..y0+14.
BOXES = [  # (x0, y0, fill, shadow, Hebrew, English)
    (0, 32, 65, 66, 'מגניבות', 'COOL'),
    (40, 32, 68, 69, 'יופי', 'BEAUTY'),
    (80, 32, 71, 72, 'חמידות', 'CUTE'),
    (80, 48, 73, 74, 'חוכמה', 'SMART'),
    (80, 64, 75, 76, 'קשיחות', 'TOUGH'),
]
for x0, y0, fill, sh, t, en in BOXES:
    draw.fill(f, x0 + 1, y0 + 1, x0 + 38, y0 + 14, fill)
    m = fit(t, 'S9', 36, asc=1, desc=2)
    x = draw.place_center(m, x0 + 1, x0 + 37)
    draw.paint(f, m, x, y0 + 2, 77, shadow=sh, clip=(x0 + 1, y0 + 1, x0 + 38, y0 + 14))
    print(en, t, width(m) + 1)
# APPEAL / JAM tags: 5-row letters, ink 42, no shadow, tags x 72..103.
for y0, bg, t, en in [(8, 33, 'רושם', 'APPEAL'), (16, 44, 'הפרעה', 'JAM')]:
    draw.replace(f, 72, y0 + 1, 103, y0 + 7, {42: bg})
    m = lay(t, 'M5', 1, asc=0, desc=0)
    x = draw.place_center(m, 72, 103)
    draw.paint(f, m, x, y0 + 2, 42)
    print(en, t, width(m))
# APPLAUSE: 7-row letters on the yellow strip x 56..95, rows 80..86, no shadow.
ink, bg = f.get(56, 81), f.get(56, 80)
draw.replace(f, 56, 80, 95, 87, {ink: bg})
m = lay('תשואות', 'W5_7', 1, asc=0, desc=0)
x = draw.place_center(m, 56, 95)
draw.paint(f, m, x, 80, ink)
print('APPLAUSE', ink, bg, width(m))
print(save_and_pair(f, P, 4))
