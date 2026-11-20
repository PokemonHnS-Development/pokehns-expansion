from kit import *
from check import check
P = 'graphics/title_screen/hns/press_start.png'
f = load_head(P)
# The title screen's blinking banner: five 32x8 sprites cut from tiles 1..20 (title_screen.c
# CreatePressStartBanner), so PNG row 0 from x 8 is one strip on screen; tiles 21..40 are the
# version banner below it ("v2.0.6", kept). English "PRESS START": letters with 2-px stems, 5 rows
# (2..6) shaded 5, 5, 4, 3, 3 from the top, with a 1-px outline 1 all round, PRESS on x 35..75 and
# START on x 83..124.
# Hebrew: לוחצים START, the game's own wording for it. START keeps its English pixels and moves to
# PRESS's place; לוחצים takes START's, in 5-row letters with doubled stems (W4_7 strokes, as the
# other bold labels), the same shading and outline; lamed's ascender on row 1 keeps its outline
# on row 0.
heb.derive('W4_7', 5, True, name='B5')
# Yod as the 6-row set draws it (3 rows, doubled stem): cut to 5 rows it is a 2-px tick.
heb.SETS['B5']['י'] = heb.SETS['B6']['י'][:7] + ['...'] * 4
SHADE = {0: 5, 1: 5, 2: 5, 3: 4, 4: 3, 5: 3}
start = {(x, y): f.get(x, y) for y in range(8) for x in range(80, 128) if f.get(x, y)}
draw.fill(f, 8, 0, 127, 7, 0)
for (x, y), v in start.items():
    f.put(x - 48, y, v)
m = lay('לוחצים', 'B5', 2, asc=1, desc=0)
x = 124 - width(m)
draw.paint(f, m, x, 1, lambda px, py, r: SHADE[r], outline=1, outline_diag=1)
print('PRESS לוחצים', width(m), 'ink x', x, x + width(m) - 1, '; START x', min(p[0] for p in start) - 48,
      max(p[0] for p in start) - 48)
print(save_and_pair(f, P, 8, region=(0, 0, 128, 16)))

e, g = load_head(P), load(P)
ok, a, b, ac, bc = check(P)
used = lambda im: {im.get(x, y) for y in range(im.height) for x in range(im.width)}
moved = {(x, y) for y in range(g.height) for x in range(g.width) if g.get(x, y) != e.get(x, y)}
assert ok and g.palette == e.palette and used(g) <= used(e), (ok, a, b, ac, bc)
assert all(8 <= x and y < 8 for x, y in moved), 'outside the PRESS START strip'
print('pixel rules OK: size, depth, palette and chunks as English; indices', sorted(used(g)),
      '; changed', len(moved), 'px, all in row 0 from x 8')
