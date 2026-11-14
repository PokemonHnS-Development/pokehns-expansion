from kit import *
from fpview import compose_pal
from check import check


def verify(P):
    """The written file keeps the English size, depth, palette and other chunks, and uses no
    palette index the English file did not use."""
    e, h = load_head(P), load(P)
    used = lambda im: {im.get(x, y) for y in range(im.height) for x in range(im.width)}
    assert check(P)[0] and e.palette == h.palette and used(h) <= used(e), P
    print('checked', P)


# Voltorb Flip board: the NOTES label over the memo panel and the COINS: label of the coin counter.
# Both are 9-row white (1) letters with 1-px strokes and a dark shadow (15 on the board, 2 on the
# coin sprite) to the right, below and down-right. Hebrew uses the game's own words: the memo is
# סימונים (the Game Corner's "על הסימונים" / "מצב סימונים") and the coins are מטבעות as in the coins box
# ("מטבעות: ..."), with the colon after the word, so at its left end.

# NOTES: tiles 0x0B..0x0F (letter tops) and 0x19..0x1D (bottoms) are drawn once each, at screen
# columns 22..26, rows 1..2; the underline below (0x20..0x22) stays. The strip is those ten tiles.
P = 'graphics/voltorb_flip/gameboard.png'
f = load_head(P)
s = TileStrip(f, [[0x0B, 0x0C, 0x0D, 0x0E, 0x0F], [0x19, 0x1A, 0x1B, 0x1C, 0x1D]])
draw.replace(s, 0, 0, 39, 15, {1: 9, 15: 9})
m = lay('סימונים', 'N9', 2, asc=0, desc=0)
x = draw.place_center(m, 0, 39 - 1)
draw.paint(s, m, x, 4, 1, shadow=15, clip=(0, 0, 39, 15))
s.put_back()
print('NOTES', 'סימונים', width(m) + 1, x)
print(save_and_pair(f, P, 6))
verify(P)
tm = read_bin('graphics/voltorb_flip/gameboard.bin')
a, b = compose_pal(load_head(P), tm, 32), compose_pal(f, tm, 32)
side_by_side([a.resize((a.width * 3, a.height * 3), 0), b.resize((b.width * 3, b.height * 3), 0)],
             ['EN board', 'HE board']).save(OUT + '/voltorb_flip__gameboard_screen_pair.png')

# COINS: a 32x16 sprite; letters on rows 0..8, shadow row 9, the underline on rows 12..13 stays.
P = 'graphics/voltorb_flip/coins.png'
f = load_head(P)
draw.replace(f, 0, 0, 31, 10, {1: 0, 2: 0})
m = fit('מטבעות:', 'N9', 32, asc=0, desc=0)
x = draw.place_center(m, 0, 31 - 1)
draw.paint(f, m, x, 0, 1, shadow=2, clip=(0, 0, 31, 10))
print('COINS:', 'מטבעות:', width(m) + 1, x)
print(save_and_pair(f, P, 10))
verify(P)
