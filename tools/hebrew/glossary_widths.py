#!/usr/bin/env python3
"""Glossary names wider than their on-screen budget AND wider than the English (fallback fonts
counted where the game fits text to a width). Prints one row per problem; exit 1 if any.

  glossary_widths.py [--csv OUT.csv]
"""
import argparse, csv, sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import textwidth as T
import paths

GLOSSARY = paths.GLOSSARY
B = {
    'species': [('party_nickname', 'FONT_SMALL', 50, 'FONT_SMALL_NARROWER'), ('dex_species_name', 'FONT_NARROW', 50, 'FONT_NARROWER'),
                ('healthbox_name', 'FONT_SMALL', 48, 'FONT_SMALL_NARROWER'), ('summary', 'FONT_NORMAL', 63, None)],
    'move': [('battle_move_name', 'FONT_NARROW', 64, 'FONT_NARROWER'), ('summary_move_name', 'FONT_NORMAL', 70, None)],
    'item': [('bag_item_name', 'FONT_NARROW', 88, None), ('shop_item_name', 'FONT_NARROW', 84, None)],
    'ability': [('ability_popup', 'FONT_SMALL', 76, 'FONT_SMALL_NARROWER'), ('summary_ability', 'FONT_NORMAL', 144, None)],
    'mapsec': [('map_name_popup', 'FONT_NARROW', 80, None), ('region_map', 'FONT_NORMAL', 96, None)],
    'category': [('dex_category', 'FONT_NORMAL', 117, None)],
}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--csv')
    a = ap.parse_args()
    m = T.TextModel(tree=paths.FONTS_TREE)

    def fit(text, font, fb, px):
        w = m.width(text, font)
        return w if w <= px or not fb else m.width(text, fb)

    out = []
    for r in csv.DictReader(open(GLOSSARY, encoding='utf-8')):
        k, he, en = r['kind'], r['proposed_hebrew'], r['english']
        for name, font, px, fb in B.get(k, []):
            if not he:
                continue
            wh, we = fit(he, font, fb, px), fit(en, font, fb, px)
            if wh > px and wh > we:
                out.append({'kind': k, 'constant': r['constant'], 'english': en, 'hebrew': he, 'budget': name,
                            'font': font, 'px': px, 'hebrew_px': wh, 'english_px': we})
    for o in out:
        print('%(kind)s %(constant)s %(hebrew)s: %(hebrew_px)d px > %(px)d (%(budget)s, English %(english_px)d)' % o)
    if a.csv:
        w = csv.DictWriter(open(a.csv, 'w', encoding='utf-8', newline=''), fieldnames=list(out[0].keys()) if out else ['kind'])
        w.writeheader(); w.writerows(out)
    print('%d over budget' % len(out))
    sys.exit(1 if out else 0)


if __name__ == '__main__':
    main()
