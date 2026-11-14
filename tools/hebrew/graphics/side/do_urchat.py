from kit import *
P = 'graphics/union_room_chat/background.png'
f = load_head(P)
# Help bar: dark plates (15) with 6-row light letters (14), one plate row above the letters and one
# below (the bottom one replaces the bar's rule 13). Button caps A, B, SELECT, START stay English.
# Plates are redrawn at the Hebrew width, keeping the English plate's left edge next to its cap
# (A, B, the end of SELECT, START), and the space they leave goes back to the
# bar's blue (1) with the rule (13) on the bottom row.
PLATES = [  # (x0, x1, y0, anchor, Hebrew, English)
    (24, 34, 8, 'left', 'בחר', 'OK'),
    (54, 74, 8, 'left', 'חזרה', 'BACK'),
    (5, 36, 16, 'left', 'החלף', 'SWITCH'),   # next to the end of the SELECT cap it belongs to
    (63, 83, 16, 'left', 'שלח', 'SEND'),
]
for x0, x1, y0, anchor, t, en in PLATES:
    draw.fill(f, x0, y0, x1, y0 + 6, 1)
    draw.fill(f, x0, y0 + 7, x1, y0 + 7, 13)
    m = lay(t, 'M6', 1, asc=1, desc=1)        # final pe's descender takes the plate's bottom row
    w = width(m) + 2
    px0 = x0 if anchor == 'left' else x1 - w + 1
    draw.fill(f, px0, y0, px0 + w - 1, y0 + 7, 15)
    draw.paint(f, m, px0 + 1, y0, 14)
    print(en, t, 'plate', px0, px0 + w - 1)
print(save_and_pair(f, P, 6))

P2 = 'graphics/union_room_chat/r_button_labels.png'
g = load_head(P2)
# Frames 0..2: "A<->a" case toggles (a Latin case switch: kept). Frame 3 (y 48..63): "REGISTER",
# 7-row light letters (14) on a dark plate (15) x 0..31, rows 51..59.
draw.fill(g, 1, 52, 30, 58, 15)
m = lay('רשום', 'W4_7', 2, asc=0, desc=0)
draw.paint(g, m, draw.place_center(m, 1, 30), 52, 14)
print('REGISTER', width(m))
print(save_and_pair(g, P2, 8))
