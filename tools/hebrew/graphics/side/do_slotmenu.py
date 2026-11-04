from kit import *
P = 'graphics/slot_machine/menu.png'
f = load_head(P)
# CREDIT / PAYOUT: 5-row white (3) letters on the dark plates (15), rows 25..29, no shadow.
for x0, x1, t, en in [(1, 30, 'מטבעות', 'CREDIT'), (33, 62, 'זכייה', 'PAYOUT')]:
    draw.replace(f, x0, 25, x1, 29, {3: 15})
    m = lay(t, 'M5', 1, asc=0, desc=0)
    draw.paint(f, m, draw.place_center(m, x0, x1), 25, 3)
    print(en, t, width(m))
# Pay table words (info box): 5-row light (33) letters, shadow 15 right/below, on 46.
# The game lays [BIG][BONUS] / [REG] [BONUS] left to right, so a right-to-left reader gets
# "בונוס ענק" / "בונוס קטן": the adjective slot is right-aligned, BONUS left-aligned.
WORDS = [  # (x0, x1, y_letters, align, Hebrew, English)
    (24, 39, 81, 'right', 'ענק', 'BIG'),
    (40, 63, 81, 'left', 'בונוס', 'BONUS'),
    (24, 39, 89, 'right', 'קטן', 'REG'),
    (72, 103, 81, 'left', 'חוזר', 'REPLAY'),
    (72, 93, 89, 'left', 'כוח', 'POWER'),        # ",3" (x 94..99, the payout) stays
]
for x0, x1, y, al, t, en in WORDS:
    draw.replace(f, x0, y, x1, y + 5, {33: 46, 15: 46})
    m = lay(t, 'M5', 1, asc=1, desc=2)
    w = width(m)
    x = max(x0, x1 - w - 2) if al == 'right' else x0 + 1   # keep a word space before BONUS
    draw.paint(f, m, x, y - 1, 33, shadow=15, clip=(x0, y - 1, x1, y + 6))
    print(en, t, w + 1, x)
# Bottom bar: 7-row white (3) letters with a dark shadow (12) right/below on 10, rows 125..131.
for x0, x1, t, en in [(1, 31, 'מידע', 'INFO.'), (33, 63, 'יציאה', 'QUIT'), (64, 103, 'ביטול', 'CANCEL')]:
    draw.replace(f, x0, 124, x1, 132, {3: 10, 12: 10})
    m = lay(t, 'W4_7', 2, asc=1, desc=0)
    x = draw.place_center(m, x0, x1 - 1)
    draw.paint(f, m, x, 124, 3, shadow=12, clip=(x0, 124, x1, 132))
    print(en, t, width(m) + 1, x)
print(save_and_pair(f, P, 4))
from fpview import compose_pal
for n in ['menu', 'info_box']:
    tm = read_bin('graphics/slot_machine/%s.bin' % n)
    a, b = compose_pal(load_head(P), tm, 32), compose_pal(f, tm, 32)
    side_by_side([a.resize((a.width * 2, a.height * 2), 0), b.resize((b.width * 2, b.height * 2), 0)], ['EN ' + n, 'HE ' + n]).save(OUT + '/slot_machine__%s_screen_pair.png' % n)
