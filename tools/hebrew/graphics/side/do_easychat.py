from kit import *
P = 'graphics/easy_chat/button_window.png'
f = load_head(P)
# Labels: 5-row 1-px letters, light (15) with a grey (12) outline all round on the window blue (5);
# "BUTTON" is grey (12) letters with no outline. The SELECT and B caps stay English.
# Hebrew right-aligned to the English right edge (letters end at x 54).
OUT_LABELS = [  # (erase rect, rows of letters, Hebrew, English)
    ((33, 16, 56, 21), 16, 'מצב', 'MODE'),
    ((23, 29, 56, 35), 30, 'מחיקה', 'DELETE'),
    ((24, 47, 56, 53), 48, 'ביטול', 'CANCEL'),
]
draw.replace(f, 46, 15, 56, 15, {12: 5})        # MODE's top outline beside the SELECT cap's base
for (x0, y0, x1, y1), ty, t, en in OUT_LABELS:
    draw.replace(f, x0, y0, x1, y1, {12: 5, 15: 5})
    m = lay(t, 'M5', 1, asc=1, desc=2)       # qof's descender (מחיקה) runs below the line
    x = draw.place_right(m, 54)
    draw.paint(f, m, x, ty - 1, 15, outline=12, outline_diag=12)
    print(en, t, x, width(m))
# "BUTTON" after the B cap: grey letters, rows 41..45, x 33..54 -> "כפתור" (reads "כפתור B").
draw.replace(f, 32, 40, 56, 46, {12: 5})
m = lay('כפתור', 'M5', 1, asc=0, desc=0)
draw.paint(f, m, 33, 41, 12)
print('BUTTON', width(m))
print(save_and_pair(f, P, 6))

P2 = 'graphics/easy_chat/mode.png'
g = load_head(P2)
# Two buttons (y 11..31 and 43..63) on the light face 14: line 1 is 6-row light (15) letters with
# a grey (12) outline (A-Z / GROUP), line 2 a light plate (15, rows +11..+17) with 5-row grey
# letters (MODE). Hebrew puts the noun first: line 1 "מצב", line 2 "A-Z" / "נושאים" (topics:
# easy-chat words stay English, so the A-Z order is still the Latin alphabet).
AZ = {'A': ['.##.', '#..#', '####', '#..#', '#..#'], '-': ['...', '...', '###', '...', '...'],
      'Z': ['####', '...#', '.##.', '#...', '####']}
def latin(t):
    rows = [''] * 5
    for i, ch in enumerate(t):
        for y in range(5):
            rows[y] += AZ[ch][y] + ('.' if i < len(t) - 1 else '')
    return rows
for top, left, line2 in [(11, 29, latin('A-Z')), (43, 27, lay('נושאים', 'M5', 1, asc=0, desc=0))]:
    # line 1 (rows top+3..top+10) and the plate (rows top+11..top+17)
    draw.replace(g, left, top + 3, 56, top + 10, {12: 14, 15: 14})
    draw.replace(g, 35, top + 11, 56, top + 17, {12: 14, 13: 14, 15: 14})
    m = lay('מצב', 'M6', 1, asc=0, desc=0)
    draw.paint(g, m, draw.place_right(m, 54), top + 4, 15, outline=12, outline_diag=12)
    w = width(line2) + 3
    draw.fill(g, 57 - w, top + 11, 56, top + 17, 15)
    draw.paint(g, line2, 57 - w + 2, top + 12, 12)
    print('line2 plate', 57 - w, 56)
print(save_and_pair(g, P2, 6))
