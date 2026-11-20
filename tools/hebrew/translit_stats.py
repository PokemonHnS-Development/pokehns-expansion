#!/usr/bin/env python3
"""Count how the FireRed fork renders a few English spellings in Hebrew, from glossary.csv.
Evidence for translation/hebrew/transliteration_rules.md. Usage: python3 translit_stats.py [regex]"""
import collections, csv, re, sys

import paths

rows = list(csv.DictReader(open(paths.GLOSSARY, encoding='utf-8')))
pairs, seen = [], set()
for r in rows:
    if r['kind'] in ('species', 'trainer_name') and r['status'] == 'inherited' \
            and r['english'] not in seen and not re.search(r'-[AGHP]$', r['english']):
        seen.add(r['english'])
        pairs.append((r['kind'], r['english'], r['firered_hebrew']))

c = collections.Counter()
for kind, e, h in pairs:
    if (e.startswith('W') and e[1:2] in 'AEIOUY') or e.startswith('WH'):
        c['initial W -> ' + ('וו' if h.startswith('וו') else 'ו')] += 1
    if re.search(r'(?<=[AEIOURL])V(?=[AEIOUY])', e):
        c['mid V -> ' + ('ב' if 'ב' in h[1:] else ('וו' if 'וו' in h[1:] else 'ו'))] += 1
    if re.search(r'P$', e):
        c['final /p/ -> ' + h[-1]] += 1
    if re.search(r'(F|FF|PH)$', e):
        c['final /f/ -> ' + h[-1]] += 1
    if re.search(r'CH$', e):
        c['final ch -> ' + h[-2:]] += 1
    if re.search(r'M$', e):
        c['final m -> ' + h[-1]] += 1
    if re.search(r'N$', e):
        c['final n -> ' + h[-1]] += 1
    if re.search(r'(CK|K|C)$', e):
        c['final k -> ' + h[-1]] += 1
    if kind == 'species' and re.search(r'^[^AEIOU]+A[^AEIOUY]', e):
        c['first-syllable a -> ' + ('א' if re.match(r"^[^אוי]+'?א", h) else 'no letter')] += 1
for k, v in sorted(c.items()):
    print(f'{v:4d}  {k}')
print(f'({len(pairs)} distinct inherited species and trainer names)')
if len(sys.argv) > 1:
    pat = re.compile(sys.argv[1])
    for kind, e, h in pairs:
        if pat.search(e):
            print(f'{e}={h}')
