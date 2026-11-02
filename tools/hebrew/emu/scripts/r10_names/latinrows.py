#!/usr/bin/env python3
"""Latin runs left inside Hebrew strings, split into those that match a glossary row's English
(a finding when the string is reachable) and those with no row (listed, not findings).
    latinrows.py OUT.txt"""
import csv
import os
import re
import sys
from collections import defaultdict

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, '..', '..', '..'))
import paths  # noqa: E402
import audit  # noqa: E402

rows = list(csv.DictReader(open(paths.GLOSSARY, encoding='utf-8')))
gl = defaultdict(list)
for i, r in enumerate(rows, 2):
    if r['kind'] in ('species', 'category') or not r['proposed_hebrew']:
        continue
    if re.search('[א-ת]', r['proposed_hebrew']):
        gl[r['english'].upper().replace('POKé', 'POKE')].append((r['kind'], r['constant'], r['proposed_hebrew'], i))
withrow, norow = [], defaultdict(list)
for e in audit.extract_tree(paths.TREE):
    if not re.search('[א-ת]', e.text) or 'debug' in e.file or 'easy_chat' in e.file:
        continue
    t = re.sub(r'\{[^}]*\}', ' ', e.text)
    t = re.sub(r'\\[nlp]', ' ', t)
    for run in re.findall(r"[A-Za-zé][A-Za-zé'.\-]*(?:\s+[A-Za-zé][A-Za-zé'.\-]*)*", t):
        key = run.upper().replace('POKé', 'POKE').strip(".'-")
        if key in gl:
            withrow.append('%s:%s %s -> %s\n   %s' % (e.file, e.line, run, gl[key][:2], e.text[:200]))
        else:
            norow[run].append('%s:%s' % (e.file, e.line))
with open(sys.argv[1], 'w', encoding='utf-8') as f:
    f.write('== Latin with a glossary row (%d)\n' % len(withrow))
    f.write('\n'.join(withrow) + '\n')
    f.write('\n== Latin without a row (%d distinct)\n' % len(norow))
    for k, v in sorted(norow.items(), key=lambda kv: -len(kv[1])):
        f.write('%-30s %3d  %s\n' % (k, len(v), ' '.join(v[:4])))
print(len(withrow), len(norow))
