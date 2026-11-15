from kit import *
from check import check
# The evening and night glow of the Poké Mart and Pokémon Center signs: a 16x16 light sprite that
# the map's light object places over the sign at every time of day but TIME_DAY
# (src/event_object_movement.c, UpdateLightSprite), blended over the background. The English glow
# draws the sign's letters again, pixel for pixel over tiles 329/330 (MART) and 327/328 (P C) of
# the Emerald general tileset: its rows 8..12 are the tiles' rows 0..4, x for x. Over the Hebrew
# signs (do_townsigns.py) it would light English letters, so the glow is redrawn from the Hebrew
# tiles with the English glow's own mapping, row by row:
# - a letter pixel of the Hebrew tile takes the glow index that the English row gives most often
#   to the same tile index (an index the English row's letters do not use takes the row's most
#   common letter glow);
# - a background pixel keeps the English glow where the English tile was background too, and
#   takes the row's most common background glow (columns 1..14) where an English letter was;
# - the other rows (the halo above and below, and the frame) stay as drawn.
# The Pokémon Center glow also lights the Melemele Isle sign, whose letters sit two rows lower
# than the glow's in English too.
GEN = 'data/tilesets/primary/general/tiles.png'
LIGHTS = [  # (sprite, the sign's two tiles in the general tileset)
    ('graphics/object_events/pics/misc/mart_light_hns.png', (329, 330)),
    ('graphics/object_events/pics/misc/poke_center_light_hns.png', (327, 328)),
]
BG = {1, 2}           # the signs' white (rows 0..2) and lower (rows 3..4) background
TOP = 8               # the sprite row over the tiles' row 0
te, th = load_head(GEN), load(GEN)


def tile_rows(f, tiles):
    return [tile_px(f, tiles[0])[r] + tile_px(f, tiles[1])[r] for r in range(5)]


def most(counts):
    return max(counts, key=counts.get)


for P, tiles in LIGHTS:
    f = load_head(P)
    e, h = tile_rows(te, tiles), tile_rows(th, tiles)
    for r in range(5):
        y = TOP + r
        glow = [f.get(x, y) for x in range(16)]
        ink, bg = {}, {}
        for x in range(16):
            if e[r][x] in BG:
                if 1 <= x <= 14:
                    bg[glow[x]] = bg.get(glow[x], 0) + 1
            else:
                d = ink.setdefault(e[r][x], {})
                d[glow[x]] = d.get(glow[x], 0) + 1
        every = {}
        for d in ink.values():
            for k, c in d.items():
                every[k] = every.get(k, 0) + c
        for x in range(16):
            v = h[r][x]
            if v in BG:
                f.put(x, y, glow[x] if e[r][x] in BG else most(bg))
            else:
                f.put(x, y, most(ink.get(v, every)))
    f.save(gpaths.write_target(P))
    print(P)
    dump(f, 0, TOP - 1, 16, 7)

# Pixel rules: same PNG apart from IDAT, no index the English file lacks, only rows 8..12 changed.
for P, tiles in LIGHTS:
    ok, a, b, ac, bc = check(P)
    e, h = load_head(P), load(P)
    new = set(h.pixels) - set(e.pixels)
    rows = {y for y in range(e.height) for x in range(e.width) if e.get(x, y) != h.get(x, y)}
    good = ok and e.palette == h.palette and not new and rows <= set(range(TOP, TOP + 5))
    print('%-60s %s new_indices=%s rows_changed=%s' % (P, 'OK' if good else 'BAD', sorted(new), sorted(rows)))
    assert good, P
