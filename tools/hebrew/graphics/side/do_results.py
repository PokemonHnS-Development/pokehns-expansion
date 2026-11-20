from kit import *
P = 'graphics/contest/results_screen/tiles.png'
f = load_head(P)
# Title-bar words, 5x2 tiles (CONTEST 6x2). English: 11-row letters, 2-px stems, ink base+1,
# shadow base+9 right/below/diagonal, background base+8, base = 16 * palette row of the slot.
# The game lays them left to right as [rank][RANK][category][CONTEST] or [LINK][category][CONTEST],
# so a right-to-left reader gets "תחרות <category> דרגת <rank>" / "תחרות <category> מקושרת".
SLOTS = [  # (x0, y0, x1, y1, base, Hebrew, English)
    (16, 0, 55, 15, 0, 'מקושרת', 'LINK'),
    (80, 0, 119, 15, 0, 'מאסטר', 'MASTER'),
    (0, 16, 39, 31, 0, 'בסיס', 'NORMAL'),
    (40, 16, 79, 31, 0, 'סופר', 'SUPER'),
    (80, 16, 119, 31, 0, 'היפר', 'HYPER'),
    (88, 48, 127, 63, 0, 'דרגת', 'RANK'),
    (0, 96, 39, 111, 0, 'מגניבות', 'COOL'),
    (40, 96, 79, 111, 16, 'יופי', 'BEAUTY'),
    (80, 96, 119, 111, 32, 'חמידות', 'CUTE'),
    (0, 112, 39, 127, 48, 'חוכמה', 'SMART'),
    (40, 112, 79, 127, 64, 'קשיחות', 'TOUGH'),
    (80, 112, 127, 127, 0, 'תחרות', 'CONTEST'),
]
for x0, y0, x1, y1, b, t, en in SLOTS:
    draw.fill(f, x0, y0, x1, y1, b + 8)
    m = fit(t, 'S11', x1 - x0 + 1 - 2, asc=1, desc=2)
    x = x0 if en == 'LINK' else draw.place_center(m, x0, x1 - 1)  # LINK: keep the gap toward the category
    draw.paint(f, m, x, y0 + 1, b + 1, shadow=b + 9, clip=(x0, y0, x1, y1))
    print(en, t, width(m) + 1)
print(save_and_pair(f, P, 4))
