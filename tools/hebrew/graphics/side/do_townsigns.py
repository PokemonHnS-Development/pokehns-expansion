from kit import *
import os
# The words on the town buildings of the map tilesets: the Poké Mart sign MART -> חנות, the
# Pokémon Center sign P.C -> מרכז (P.C abbreviates POKéMON CENTER, מרכז פוקימון), and the gym
# plaque and gym stand GYM -> מכון. On every map that loads one of these tilesets, the tiles changed
# here appear only in these signs' metatiles.
#
# Letters: the narrow T6 set of coreui/coreui_mini_designs.txt (the battle status tags), with the
# body cut to the signs' 5 or 3 rows. The side parser skips one-column rows, so vav and final nun
# (one-pixel strokes, final nun one row longer) are given here.
T6 = heb._parse(os.path.join(gpaths.HERE, 'coreui', 'coreui_mini_designs.txt'))[0]['T6']
T6['ו'] = ['.'] + ['#'] * 6 + ['.']
T6['ן'] = ['.'] + ['#'] * 7


def cut(g, body):
    """Keep the ascender row, the listed T6 body rows (0..5) and the descender row."""
    return heb.trim([g[0]] + [g[1 + i] for i in body] + [g[7]])


# 5-row body: a body row that repeats its upper neighbour goes, as C5 is cut from C6.
heb.SETS['T5'] = {ch: heb.trim(heb.resize_body(g, 1, 6, 5)) for ch, g in T6.items()}
heb.META['T5'] = {'top': 1, 'h': 5}
# 3-row body: the first, second and last T6 body rows. Mem is drawn here: a box closed at the top
# and on the right, its top-left corner cut and its base open at the bottom left, the shape of the
# game's small-font mem. The 3-px narrow mem no longer reads as a mem at this height, and the
# font's W4_7 mem cut to 3 rows (M3) is an X with a foot that reads as alef.
heb.SETS['T3'] = {'מ': ['....', '.###', '#..#', '#.##', '....'], 'כ': cut(T6['כ'], (0, 1, 5)),
                  'ו': cut(T6['ו'], (0, 1, 5)), 'ן': cut(T6['ן'], (0, 1, 5))}
heb.META['T3'] = {'top': 1, 'h': 3}
# The gym stand's narrower 3-row set: kaf two columns wide (T6 nun's shape cut to 3 rows), so the
# word leaves a column of background beside the stand's frame on both sides, as the English does.
heb.SETS['T3s'] = dict(heb.SETS['T3'], **{'כ': ['..', '##', '.#', '##', '..']})
heb.META['T3s'] = heb.META['T3']


def spaced(text, setname, wide=('נו',)):
    """Right-to-left layout with 1-px gaps, 2 px between the neighbours named in `wide`: vav
    beside nun would close into a box at this size."""
    vis = list(reversed(text))
    out = glyph_rows(setname, vis[0], 0, 0)
    for left, ch in zip(vis, vis[1:]):
        gap = 2 if ch + left in wide or left + ch in wide else 1
        out = [a + '.' * gap + b for a, b in zip(out, glyph_rows(setname, ch, 0, 0))]
    return out


JOHTO = ['johto_general_hns', 'johto_north_east_hns', 'johto_north_west_hns', 'johto_south_hns',
         'kanto_general_hns']
CHANGED = {}   # path -> tiles this script may change


def tiles_png(ts):
    return 'data/tilesets/primary/%s/tiles.png' % ts


def row_inks(s, rows, x0, x1, skip):
    """For each row, the index the English letters use most (anti-alias shades lose)."""
    out = {}
    for y in rows:
        c = {}
        for x in range(x0, x1 + 1):
            v = s.get(x, y)
            if v not in skip:
                c[v] = c.get(v, 0) + 1
        out[y] = max(c, key=c.get)
    return out


def sign5(f, tiles, word, bg, keep_bottom_line):
    """MART / P.C on the Johto buildings: two tiles, 5-row letters on rows 2..6 in the English
    rows' gradient (one index per row), drop shadow 2 below and below-right; row 7 is the sign's
    light bottom line on the MART sign and plain background on the P.C sign."""
    s = TileStrip(f, [tiles])
    inks = row_inks(s, range(2, 7), 0, 15, {bg, 2, 10})   # 10: the MART letters' corner shade
    draw.fill(s, 0, 2, 15, 6 if keep_bottom_line else 7, bg)
    m = spaced(word, 'T5')
    x = 15 - width(m)          # right-aligned; the shadow takes x 15
    draw.paint(s, m, x, 2, lambda px, py, r: inks[py], shadow=2, shadow_offsets=[(0, 1), (1, 1)],
               clip=(0, 2, 15, 7), only_on={bg})
    s.put_back()
    print(word, 'w', width(m), 'x', x, 'inks', inks)


def gym_plaque(f):
    """Wall plaque: tiles 264, 265, 270 over 280, 281, 286. 3-row red (13) letters on white (1),
    interior x 3..19 on rows 5..7; row 8 (white x 5..17) takes final nun's descender. The 12-px
    word sits one column right of centre (x 6..17), so the descender lands on the white row clear
    of the bevel's corner pixel at x 4."""
    s = TileStrip(f, [[264, 265, 270], [280, 281, 286]])
    draw.fill(s, 3, 5, 19, 7, 1)
    m = lay('מכון', 'T3', 1, asc=0, desc=1)
    x = draw.place_center(m, 3, 19) + 1
    cells = draw.paint(s, m, x, 5, 13)
    assert all(3 <= cx <= 19 and (cy <= 7 or 6 <= cx <= 17) for cx, cy in cells)
    s.put_back()
    print('GYM plaque w', width(m), 'x', x)


def gym_stand(f):
    """Stand sign: tiles 366, 367 (stand rows 8..15) over 382, 383 (rows 16..23, the red dash row
    first). 3-row grey letters on 2, interior x 1..13 of rows 3..7; the dark frame (7) is x 0 and
    14. The 11-px word (T3s, the narrow kaf) takes x 2..12, the English letters' columns, with one
    column of background on each side; ink 6, the darkest of the English letters' 4/5/6. Final
    nun's descender ends on row 7, right above the first red dash: that dash pixel becomes
    background, so the stroke does not run into the decoration."""
    s = TileStrip(f, [[366, 367], [382, 383]])
    draw.fill(s, 1, 4, 13, 6, 2)
    m = lay('מכון', 'T3s', 1, asc=0, desc=1)
    x = draw.place_center(m, 1, 13)
    cells = draw.paint(s, m, x, 4, 6)
    assert all(2 <= cx <= 12 and cy <= 7 for cx, cy in cells)
    for cx, cy in cells:
        if cy == 7:
            assert s.get(cx, 8) == 13, ('not a dash pixel under the descender', cx)
            s.put(cx, 8, 2)
    s.put_back()
    print('GYM stand w', width(m), 'x', x)


def emerald_sign(f, tiles, word):
    """The Emerald general tileset's signs: 5-row letters on rows 0..4, ink 13 on white (1) for
    rows 0..2 and ink 14 on 2 for rows 3..4, no shadow; rows 5..7 (the dashes) stay."""
    s = TileStrip(f, [tiles])
    bg = {0: 1, 1: 1, 2: 1, 3: 2, 4: 2}
    ink = {0: 13, 1: 13, 2: 13, 3: 14, 4: 14}
    for y in range(5):
        draw.fill(s, 0, y, 15, y, bg[y])
    m = spaced(word, 'T5')
    x = draw.place_center(m, 0, 15)
    draw.paint(s, m, x, 0, lambda px, py, r: ink[py])
    s.put_back()
    print(word, 'w', width(m), 'x', x)


# The five Johto/Kanto primaries hold the same English sign tiles; one drawing serves them all.
ref = load_head(tiles_png(JOHTO[0]))
SIGN_TILES = [211, 225, 226, 227, 264, 265, 270, 280, 281, 286, 366, 367, 382]
for ts in JOHTO:
    P = tiles_png(ts)
    f = load_head(P)
    assert all(tile_px(f, t) == tile_px(ref, t) for t in SIGN_TILES), ts
    sign5(f, [225, 226], 'חנות', 1, True)
    sign5(f, [211, 227], 'מרכז', 1, False)
    gym_plaque(f)
    gym_stand(f)
    CHANGED[P] = SIGN_TILES
    f.save(gpaths.write_target(P))

# Alola island: the P.C sign only (tiles 257, 258 = the Johto 211, 227).
P = tiles_png('alola_island')
f = load_head(P)
sign5(f, [257, 258], 'מרכז', 1, False)
CHANGED[P] = [257, 258]
f.save(gpaths.write_target(P))

# The snow primary of New Sinjoh: the P.C sign on background 15, top row in 12. Its MART tiles
# (225, 226) are placed by no map.
P = tiles_png('mt_silver_exp_hns')
f = load_head(P)
sign5(f, [211, 227], 'מרכז', 15, False)
CHANGED[P] = [211, 227]
f.save(gpaths.write_target(P))

# Emerald's general tileset: the Pokémon Center and Mart on the Battle Frontier's east side.
P = tiles_png('general')
f = load_head(P)
emerald_sign(f, [327, 328], 'מרכז')
emerald_sign(f, [329, 330], 'חנות')
CHANGED[P] = [327, 328, 329, 330]
f.save(gpaths.write_target(P))

# Pixel rules: same PNG apart from IDAT, no index the English file lacks, changes only inside
# the listed tiles.
from check import check
for P, tiles in CHANGED.items():
    ok, a, b, ac, bc = check(P)
    e, h = load_head(P), load(P)
    used = set(e.pixels)
    tw = e.width // 8
    moved = {(y // 8) * tw + x // 8 for y in range(e.height) for x in range(e.width) if e.get(x, y) != h.get(x, y)}
    new = set(h.pixels) - used
    good = ok and e.palette == h.palette and not new and moved <= set(tiles)
    print('%-50s %s new_indices=%s tiles_changed=%s' % (P, 'OK' if good else 'BAD', sorted(new), sorted(moved)))
    assert good, P
