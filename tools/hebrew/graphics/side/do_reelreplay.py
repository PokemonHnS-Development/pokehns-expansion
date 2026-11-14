from kit import *
from check import check


def verify(P):
    """The written file keeps the English size, depth, palette and other chunks, and uses no
    palette index the English file did not use."""
    e, h = load_head(P), load(P)
    used = lambda im: {im.get(x, y) for y in range(im.height) for x in range(im.width)}
    assert check(P)[0] and e.palette == h.palette and used(h) <= used(e), P
    print('checked', P)


P = 'graphics/slot_machine/reel_symbols/7.png'
f = load_head(P)
# The REPLAY reel symbol (one 32x32 sprite): 5-row white (3) letters on rows 13..17 with a dark
# shadow (15) right, below and down-right, on the grey (1) band of rows 12..18, x 3..28.
# Hebrew: חוזר, the word and the 5-row letters of the pay table (do_slotmenu.py), centred on the band;
# the four letters take 2-px gaps so the word spans the band as the six English letters do.
draw.replace(f, 4, 13, 28, 18, {3: 1, 15: 1})
m = lay('חוזר', 'M5', 2, asc=0, desc=0)
x = draw.place_center(m, 4, 28 - 1)
draw.paint(f, m, x, 13, 3, shadow=15, clip=(4, 13, 28, 18))
print('REPLAY', 'חוזר', width(m) + 1, x)
print(save_and_pair(f, P, 10))
verify(P)
