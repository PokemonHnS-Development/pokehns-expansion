#!/usr/bin/env python3
"""Check that every item a player can hold more than one of has a Hebrew plural (DECISIONS.md Q125).

The count lines (toss, deposit, withdraw, obtained N, the Pokédex 'N <item> בתיק') take the item name
from CopyItemNameHandlePlural (src/item.c). An item without a pluralName gets an 's' in English and
keeps its singular in the Hebrew build, which is wrong after a count. So every stackable item needs
a glossary item_plural row, and src/data/items.h needs its pluralName whenever that row differs from
the singular (a row equal to the singular is a mass noun or an uninflected name: the fallback
prints it).

Stackable: an item outside the key-item and TM/HM pockets with no importance. TM and HM names are an
abbreviation (מ”מ, מ”נ) plus a number, which Hebrew does not inflect.

Usage: plurals.py [--tree DIR] [--glossary CSV]      exit status 1 on any problem
"""
import argparse
import csv
import os
import re
import sys

import paths

ENTRY_RE = re.compile(r'^    \[(ITEM_[A-Z0-9_]+)\]\s*=[^\n]*\n    \{\n(.*?)^    \},', re.M | re.S)
NAME_RE = re.compile(r'\.name = ITEM_NAME\("([^"]*)"\)')
PLURAL_RE = re.compile(r'\.pluralName = ITEM_PLURAL_NAME\("([^"]*)"\)')
POCKET_RE = re.compile(r'\.pocket = (\w+)')
IMPORTANCE_RE = re.compile(r'\.importance = ([^,\n]+),')
NOT_STACKABLE_POCKETS = {'POCKET_KEY_ITEMS', 'POCKET_TM_HM'}


def parse_items(text):
    """const -> dict(name, plural, pocket, importance) for each entry of gItemsInfo (first one wins)."""
    items = {}
    for m in ENTRY_RE.finditer(text):
        const, body = m.group(1), m.group(2)
        if const in items:
            continue
        name, pocket, imp = NAME_RE.search(body), POCKET_RE.search(body), IMPORTANCE_RE.search(body)
        plurals = PLURAL_RE.findall(body)
        items[const] = dict(name=name.group(1) if name else None, plural=plurals[-1] if plurals else None,
                            pocket=pocket.group(1) if pocket else None,
                            importance=imp.group(1).strip() if imp else '0')
    return items


def stackable(item):
    return item['pocket'] not in NOT_STACKABLE_POCKETS and item['importance'] == '0'


def check(items, rows):
    """items: parse_items() result; rows: const -> proposed_hebrew of the item_plural rows."""
    problems = []
    for const, it in items.items():
        if const == 'ITEM_NONE' or it['name'] is None:
            continue
        shown = it['plural'] or it['name']
        if const not in rows:
            if stackable(it):
                problems.append('MISSING %s (%s): no item_plural row' % (const, it['name']))
            continue
        if rows[const] != shown:
            problems.append('MISMATCH %s: glossary %r, items.h prints %r' % (const, rows[const], shown))
    return problems


def load_rows(path):
    return {r['constant']: (r.get('proposed_hebrew') or '').strip()
            for r in csv.DictReader(open(path, encoding='utf-8')) if r['kind'] == 'item_plural'}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--tree', default=paths.TREE)
    ap.add_argument('--glossary', default=paths.GLOSSARY)
    a = ap.parse_args()
    items = parse_items(open(os.path.join(a.tree, 'src', 'data', 'items.h'), encoding='utf-8').read())
    problems = check(items, load_rows(a.glossary))
    print('\n'.join(problems))
    print('items %d, stackable %d, problems %d' % (len(items), sum(stackable(i) for i in items.values()),
                                                   len(problems)))
    sys.exit(1 if problems else 0)


if __name__ == '__main__':
    main()
