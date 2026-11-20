#!/usr/bin/env python3
"""Write glossary names into the two non-C name sources: trainer names in the .party files and map
section names in region_map_sections.json (the hns_map_sections list only, the one the hns build
uses). C name fields go through make_chunks.py / units.py instead.

  apply_names.py [--tree TREE] [--dry-run]
"""
import argparse, csv, json, os, re

import paths

GLOSSARY = paths.GLOSSARY
TREE = paths.TREE
PARTY_FILES = ['src/data/trainers_hns.party', 'src/data/battle_partners.party']


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--tree', default=TREE)
    ap.add_argument('--dry-run', action='store_true')
    a = ap.parse_args()
    rows = list(csv.DictReader(open(GLOSSARY, encoding='utf-8')))
    names = {r['english']: r['proposed_hebrew'] for r in rows if r['kind'] == 'trainer_name' and r['proposed_hebrew']}
    mapsecs = {r['constant']: r['proposed_hebrew'] for r in rows if r['kind'] == 'mapsec' and r['proposed_hebrew']}

    for rel in PARTY_FILES:
        path = os.path.join(a.tree, rel)
        if not os.path.exists(path):
            continue
        lines = open(path, encoding='utf-8').read().split('\n')
        n = missing = 0
        for i, line in enumerate(lines):
            m = re.match(r'^Name:\s*(.*?)\s*$', line)
            if m and m.group(1):
                he = names.get(m.group(1))
                if he:
                    lines[i] = 'Name: ' + he
                    n += 1
                elif not re.search(r'[֐-׿]', m.group(1)):
                    missing += 1
        if not a.dry_run:
            open(path, 'w', encoding='utf-8').write('\n'.join(lines))
        print('%s: %d names, %d without a glossary row' % (rel, n, missing))

    path = os.path.join(a.tree, 'src/data/region_map/region_map_sections.json')
    lines = open(path, encoding='utf-8').read().split('\n')
    in_hns = False
    cur_id = None
    n = 0
    for i, line in enumerate(lines):
        if '"hns_map_sections"' in line:
            in_hns = True
        elif re.match(r'^\s*"map_sections"', line):
            in_hns = False
        m = re.search(r'"id":\s*"(MAPSEC_[A-Z0-9_]+)"', line)
        if m:
            cur_id = m.group(1)
        m = re.match(r'^(\s*"name":\s*")(.*)(",?\s*)$', line)
        if m and in_hns and cur_id in mapsecs:
            lines[i] = m.group(1) + mapsecs[cur_id] + m.group(3)
            n += 1
            cur_id = None
    if not a.dry_run:
        open(path, 'w', encoding='utf-8').write('\n'.join(lines))
    json.loads('\n'.join(lines))  # still valid JSON
    print('region_map_sections.json: %d hns map names' % n)


if __name__ == '__main__':
    main()
