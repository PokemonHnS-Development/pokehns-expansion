#!/usr/bin/env python3
"""Widest names of each kind in the fonts of the windows that show them (round 10, names).

    widest.py INVENTORY.json OUT.json [N]

INVENTORY.json is namesweep.py's name_inventory.json. Prints and writes the N widest Hebrew names
per (kind, font) with their English, measured with textwidth.py.
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, '..', '..', '..'))
import textwidth as tw  # noqa: E402

FONTS = {
    'item': ['FONT_NARROW', 'FONT_NORMAL', 'FONT_SMALL'],
    'item_plural': ['FONT_NORMAL'],
    'move': ['FONT_NORMAL', 'FONT_NARROW'],
    'ability': ['FONT_NORMAL', 'FONT_SMALL'],
    'nature': ['FONT_NORMAL'],
    'type': ['FONT_NORMAL', 'FONT_NARROW'],
    'decoration': ['FONT_NORMAL', 'FONT_NARROW'],
    'berry': ['FONT_NORMAL'],
    'trainer_class': ['FONT_NORMAL'],
    'trainer_name': ['FONT_NORMAL'],
    'mapsec': ['FONT_NORMAL', 'FONT_NARROW'],
}


def main():
    inv = json.load(open(sys.argv[1], encoding='utf-8'))
    n = int(sys.argv[3]) if len(sys.argv) > 3 else 12
    model = tw.TextModel()
    out = {}
    for kind, fonts in FONTS.items():
        for font in fonts:
            rows = []
            for const, v in inv.get(kind, {}).items():
                if not v['he'] or v['he'] in ('-', '???'):
                    continue
                try:
                    w = model.width(v['he'], font)
                except Exception:
                    continue
                rows.append((w, const, v['he'], v['en']))
            rows.sort(reverse=True)
            out['%s/%s' % (kind, font)] = rows[:n]
            print('== %s %s' % (kind, font))
            for r in rows[:n]:
                print('  %3d %-40s %s | %s' % r)
    json.dump(out, open(sys.argv[2], 'w', encoding='utf-8'), ensure_ascii=False, indent=1)


if __name__ == '__main__':
    main()
