from kit import *
P = 'graphics/battle_frontier/tourney_buttons.png'
f = load_head(P)
# Four 32x16 buttons: CANCEL selected (y 0) / unselected (y 16), EXIT selected (y 64) /
# unselected (y 80). English: 7-row, 4-px letters, ink 4 with a shadow (9 on fill 6 when selected,
# 8 on fill 2 when not) inside x 4..27, rows 5..11; row 4 and 12 are the button's inner rule.
# Hebrew: 6-row letters on rows 6..11 so lamed's ascender (row 5) stays off the rule.
for y0, t, fill, sh in [(0, 'ביטול', 6, 9), (16, 'ביטול', 2, 8), (64, 'יציאה', 6, 9), (80, 'יציאה', 2, 8)]:
    draw.fill(f, 4, y0 + 5, 27, y0 + 11, fill)
    m = fit(t, 'M6', 24, gaps=((2, 1), (1, 1)), asc=1, desc=0)
    x = draw.place_center(m, 4, 26)
    draw.paint(f, m, x, y0 + 5, 4, shadow=sh, clip=(4, y0 + 5, 27, y0 + 11))
    print(t, width(m) + 1, x)
print(save_and_pair(f, P, 8))
