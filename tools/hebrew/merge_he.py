#!/usr/bin/env python3
"""Merge translations into a chunk: merge_he.py CHUNK.json TRANSLATIONS.json

TRANSLATIONS.json is {"<unit id>": "<hebrew>", ...}. Units marked "fixed" are never overwritten.
Prints how many units were filled and which ids were not found.
"""
import json, sys
chunk_path, tr_path = sys.argv[1], sys.argv[2]
doc = json.load(open(chunk_path, encoding='utf-8'))
tr = json.load(open(tr_path, encoding='utf-8'))
units = doc['units'] if isinstance(doc, dict) else doc
ids = {u['id']: u for u in units}
n = 0
for k, v in tr.items():
    u = ids.get(k)
    if u is None:
        print('unknown id', k)
        continue
    if u.get('fixed'):
        continue
    u['he'] = v
    n += 1
json.dump(doc, open(chunk_path, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print('filled %d of %d units' % (n, sum(1 for u in units if not u.get('fixed'))))
