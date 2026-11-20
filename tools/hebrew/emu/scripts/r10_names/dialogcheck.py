#!/usr/bin/env python3
"""Second dialogue pass for round-10 names: multi-word item / move / map-section / ability /
decoration / trainer-class names matched case-insensitively in the English string of a key, and
looked for in the Hebrew string of the same key (prefix letters, the article and a changed last
letter of each word allowed).   dialogcheck.py OUT.txt"""
import csv
import os
import re
import sys
from collections import defaultdict

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, '..', '..', '..'))
import paths  # noqa: E402
import audit  # noqa: E402

KINDS = ('item', 'move', 'mapsec', 'ability', 'decoration', 'trainer_class', 'place', 'term')
rows = [r for r in csv.DictReader(open(paths.GLOSSARY, encoding='utf-8'))]
names = []
for i, r in enumerate(rows, 2):
    en = r['english'].replace('POKé', 'POKE').replace('Poké', 'Poke')
    if r['kind'] in KINDS and r['proposed_hebrew'] and len(en.split()) >= 2 and '{' not in en:
        names.append((r['kind'], en, r['proposed_hebrew'], i))
names.sort(key=lambda x: -len(x[1]))
he = {e.key: e for e in audit.extract_tree(paths.TREE)}
en = {e.key: e for e in audit.extract_tree(paths.BASELINE)}
SKIP = {'item_name', 'item_plural', 'move_name', 'ability_name', 'type_name', 'map_name', 'trainer_name',
        'species_name', 'category', 'type_generic', 'item_description', 'move_description', 'dex_entry',
        'ability_description', 'contest_effect_description'}
strip = lambda s: re.sub(r'(^|[\s”(\-])[הבלמשוכ]{0,2}(?=[א-ת])', r'\1', s)
first = defaultdict(list)
for n in names:
    first[n[1].split()[0].upper()].append(n)
out = []
for key, ee in en.items():
    h = he.get(key)
    if not h or ee.kind in SKIP or not re.search('[א-ת]', h.text):
        continue
    if any(x in ee.file for x in ('debug', 'easy_chat')):
        continue
    et = re.sub(r'\\[nlp]', ' ', ee.text).replace('POKé', 'POKE').replace('Poké', 'Poke')
    ht = strip(re.sub(r'\\[nlp]', ' ', h.text))
    toks = set(w.upper().strip('.,!?:;') for w in et.split())
    used = []
    cands = sorted({c for t in toks for c in first.get(t, [])}, key=lambda x: -len(x[1]))
    for kind, n, hn, gl in cands:
        if any(n.upper() in u.upper() for u in used):
            continue
        if not re.search(r'(?<![A-Za-z])' + re.escape(n) + r'(?![A-Za-z])', et, re.I):
            continue
        used.append(n)
        core = strip(hn)
        words = core.split()
        loose = r'\s+'.join(re.escape(w[:-1]) + r'\S{0,3}' if len(w) > 2 else re.escape(w) for w in words)
        if core in ht or re.search(loose, ht):
            continue
        out.append('%s:%s %s %r -> %r (glossary.csv:%d)\n   EN %s\n   HE %s' % (h.file, h.line, kind, n, hn, gl, ee.text[:220], h.text[:220]))
open(sys.argv[1], 'w', encoding='utf-8').write('\n'.join(out) + '\n')
print(len(out))
