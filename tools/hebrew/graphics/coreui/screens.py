#!/usr/bin/env python3
"""English | Hebrew renders of the tilemaps that place coreui label tiles (summary pages, berry tag,
PC storage panels), so the labels can be judged where the game puts them. Writes screens.png."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from PIL import Image
from gfx import load, BASE_REF, OUT, labelled_row
from tmap import read_bin, render

VIEWS = [   # (tileset, tilemap, width in tiles, tile base, crop in tiles or None, label)
    ('graphics/summary_screen/hns/tiles.png', 'graphics/summary_screen/page_info.bin', 32, 0, (10, 2, 30, 15), 'summary info'),
    ('graphics/summary_screen/hns/tiles.png', 'graphics/summary_screen/page_info_egg.bin', 32, 0, (10, 7, 30, 10), 'summary egg'),
    ('graphics/summary_screen/hns/tiles.png', 'graphics/summary_screen/page_skills.bin', 32, 0, (10, 2, 30, 20), 'summary skills'),
    ('graphics/summary_screen/hns/tiles.png', 'graphics/summary_screen/page_battle_moves.bin', 32, 0, (0, 2, 30, 16), 'summary moves'),
    ('graphics/bag/check_berry.png', 'graphics/bag/berry_tag.bin', 32, 0, (2, 10, 30, 14), 'berry tag'),
    ('graphics/pokemon_storage/menu.png', 'graphics/pokemon_storage/pkmn_data.bin', 8, 0x100, None, 'PC pkmn data'),
    ('graphics/pokemon_storage/menu.png', 'graphics/pokemon_storage/party_menu.bin', 12, 0x100, (0, 16, 12, 22), 'PC party panel'),
    ('graphics/pokemon_storage/menu.png', 'graphics/pokemon_storage/close_box_button.bin', 9, 0x100, None, 'PC close box'),
]

def main(zoom=3):
    rows = []
    for png, tm, w, base, crop, label in VIEWS:
        ims = []
        for ref in (BASE_REF, None):
            im = render(read_bin(tm, BASE_REF), load(png, ref), width=w, base=base, zoom=zoom,
                        pal_rows=False if base else None)
            if crop:
                x0, y0, x1, y1 = crop
                im = im.crop((x0 * 8 * zoom, y0 * 8 * zoom, x1 * 8 * zoom, y1 * 8 * zoom))
            ims.append(im)
        rows.append(labelled_row(ims, ['%s (English)' % label, 'Hebrew']))
    W = max(r.width for r in rows)
    out = Image.new('RGB', (W, sum(r.height for r in rows)), (40, 40, 40))
    y = 0
    for r in rows:
        out.paste(r, (0, y)); y += r.height
    out.save(os.path.join(OUT, 'screens.png'))
    print('screens', out.size)

if __name__ == '__main__':
    main()
