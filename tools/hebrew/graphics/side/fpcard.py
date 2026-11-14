from kit import *

# Mini trainer card (bg.bin cells, tiles x 0..95, y 184..239). Labels: 3-row tab text, 4-row
# black (31) labels with a grey (30) shadow on the right, on the card's two-tone stripes.
def card(f, oy, ox=0):
    # tab "TRAINER CARD": 3-row letters; no Hebrew is readable at 3 rows, so the tab keeps the English.
    # IDNo, NAME, MONEY, POKéDEX, TIME: erase ink/shadow, restoring each row's stripe colour
    for (x0, y0, x1, y1, ref, t) in [(54, oy + 7, 89, oy + 11, 90, "מס' זיהוי"), (10, oy + 16, 25, oy + 19, 5, 'שם'),
                                      (10, oy + 26, 45, oy + 29, 5, 'כסף'), (10, oy + 31, 45, oy + 34, 5, 'פוקדקס'),
                                      (10, oy + 36, 45, oy + 39, 5, 'זמן')]:
        x0, x1, ref = x0 + ox, x1 + ox, ref + ox
        erase_rows(f, x0, y0, x1, y1, {30, 31}, ref)
        m = lay(t, 'M4', 1, asc=0, desc=1, space=3)   # final nun: 1 descender row (the stripe below)
        top = y0 + 1 if t.startswith('מס') else y0
        draw.paint(f, m, x0, top, 31, shadow=30, shadow_offsets=[(1, 0)])
        print(t, width(m))
