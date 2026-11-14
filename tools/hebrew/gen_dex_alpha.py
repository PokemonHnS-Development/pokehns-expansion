#!/usr/bin/env python3
"""Regenerate gPokedexOrder_Alphabetical for Hebrew names (the Pokédex 'A-Z' sort).

  gen_dex_alpha.py [--tree TREE] [--check]      TREE defaults to HNS_TREE; the header is rewritten there

Reads the English array in src/data/pokemon/pokedex_orders.h, looks up each NATIONAL_DEX_X's
Hebrew species name in the glossary (SPECIES_X), sorts by Hebrew alphabetical order (final forms
count as their base letter, geresh and punctuation are ignored, the English name breaks ties), and
writes the result as the TEXT_RTL branch of the array, keeping the English order in the #else.

--check writes nothing. It regenerates the order in memory and compares it with the TEXT_RTL
branch in the header: exit 0 when they are equal, exit 1 when the header is stale (each entry
that moves is printed with its old and new index) or has no TEXT_RTL branch.
"""
import argparse, csv, difflib, re, sys

import paths

ORDER = 'אבגדהוזחטיכלמנסעפצקרשת'
FINAL = {'ך': 'כ', 'ם': 'מ', 'ן': 'נ', 'ף': 'פ', 'ץ': 'צ'}


def key(name):
    k = []
    for ch in name:
        ch = FINAL.get(ch, ch)
        if ch in ORDER:
            k.append(ORDER.index(ch))
        elif ch.isdigit():
            k.append(100 + int(ch))
        elif ch.isalpha():
            k.append(200 + ord(ch.upper()))
    return k


def alphabetical_block(text):
    """The source of the gPokedexOrder_Alphabetical array, which comes before gPokedexOrder_Weight."""
    return text.split('gPokedexOrder_Weight')[0]


def english_body(text):
    block = alphabetical_block(text)
    if '#if TEXT_RTL' in block:
        return re.search(r'#else\n(.*?)#endif\n', block, re.S).group(1)
    return re.search(r'const u16 gPokedexOrder_Alphabetical\[\] =\n\{\n(.*?)\};', text, re.S).group(1)


def hebrew_entries(text):
    """The entries of the header's TEXT_RTL branch, or None when it has none."""
    m = re.search(r'#if TEXT_RTL\n(.*?)#else\n', alphabetical_block(text), re.S)
    return re.findall(r'NATIONAL_DEX_([A-Z0-9_]+)', m.group(1)) if m else None


def glossary_names(glossary):
    names = {}
    for r in csv.DictReader(open(glossary, encoding='utf-8')):
        if r['kind'] == 'species':
            names[r['constant']] = (r['proposed_hebrew'], r['english'])
    return names


def sort_entries(entries, names):
    names = dict(names)
    # Species with forms have no plain constant (SPECIES_BURMY_PLANT_CLOAK); use the first form's name.
    for e in entries:
        if 'SPECIES_' + e not in names:
            forms = sorted(c for c in names if c.startswith('SPECIES_' + e + '_'))
            if forms:
                names['SPECIES_' + e] = names[forms[0]]
    missing = [e for e in entries if 'SPECIES_' + e not in names]
    rows = sorted(entries, key=lambda e: (key(names.get('SPECIES_' + e, ('', e))[0]), names.get('SPECIES_' + e, ('', e))[1]))
    return rows, missing


def moved_entries(old, new):
    """Entries outside the longest run the two orders share, as (entry, old index, new index).

    An entry that only shifts because others moved past it is not listed. An index is None when
    the entry is missing from that list."""
    sm = difflib.SequenceMatcher(None, old, new, autojunk=False)
    kept = set()
    for i, j, n in sm.get_matching_blocks():
        kept.update(old[i:i + n])
    old_at = {e: i for i, e in enumerate(old)}
    new_at = {e: i for i, e in enumerate(new)}
    moved = [e for e in new if e not in kept] + [e for e in old if e not in new_at]
    return [(e, old_at.get(e), new_at.get(e)) for e in moved]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--tree', default=paths.TREE)
    ap.add_argument('--check', action='store_true',
                    help='compare the header with a fresh generation; exit 1 if it is stale')
    a = ap.parse_args()
    path = a.tree + '/src/data/pokemon/pokedex_orders.h'
    text = open(path, encoding='utf-8').read()
    body = english_body(text)
    entries = re.findall(r'NATIONAL_DEX_([A-Z0-9_]+)', body)
    rows, missing = sort_entries(entries, glossary_names(paths.GLOSSARY))
    if missing:
        print('no glossary name for', missing[:20], len(missing))
    if a.check:
        current = hebrew_entries(text)
        if current is None:
            print('gen_dex_alpha: %s has no TEXT_RTL list; run gen_dex_alpha.py' % path)
            sys.exit(1)
        if current == rows:
            print('gen_dex_alpha: %d entries, the TEXT_RTL list is up to date' % len(rows))
            return
        moved = moved_entries(current, rows)
        for e, i, j in moved:
            print('  %-28s index %s -> %s' % (e, '-' if i is None else i, '-' if j is None else j))
        print('gen_dex_alpha: the TEXT_RTL list is stale, %d entries move; run gen_dex_alpha.py and '
              'commit src/data/pokemon/pokedex_orders.h' % len(moved))
        sys.exit(1)
    heb_body = ''.join('    NATIONAL_DEX_%s,\n' % e for e in rows)
    new_block = ('const u16 gPokedexOrder_Alphabetical[] =\n{\n'
                 '#if TEXT_RTL\n    // Hebrew alphabetical order, generated by tools/hebrew/gen_dex_alpha.py from the glossary.\n'
                 + heb_body + '#else\n' + body + '#endif\n};')
    start = text.index('const u16 gPokedexOrder_Alphabetical[] =')
    end = text.index('};', start) + 2
    text = text[:start] + new_block + text[end:]
    open(path, 'w', encoding='utf-8').write(text)
    print('wrote %d entries' % len(rows))


if __name__ == '__main__':
    main()
