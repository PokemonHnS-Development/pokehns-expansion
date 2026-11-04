#!/usr/bin/env python3
"""Validate glossary rows: encodable characters, byte limits per kind, duplicates within a kind, and
(with --all) two glossary rows with the same kind and constant (DUPKEY), where one would hide the other.

Usage:
  namecheck.py FILE.csv [FILE.csv ...]   check these chunk files (column proposed_hebrew)
  namecheck.py --all                     check glossary.csv merged with every glossary_done/*.csv

Byte length is the encoded length in the game charmap: one byte per Hebrew letter, space, digit or
punctuation mark; {TOKENS} count as their charmap expansion (e.g. {PKMN} = 2).
"""
import csv, glob, os, re, sys

import paths

ROOT = paths.TRANSLATION
CHARMAP = os.path.join(paths.FONTS_TREE, 'charmap.txt')

LIMITS = {
    'species': 12, 'move': 16, 'ability': 16, 'item': 19, 'item_plural': 21, 'type': 8,
    'trainer_name': 10, 'trainer_class': 12, 'berry': 6, 'mapsec': 19, 'category': 12,
    'nature': 12, 'type_generic': 30, 'term': 30, 'speaker': 16,
}
# Kinds whose names must be unique (two different things must not share a Hebrew name).
UNIQUE = {'move', 'ability', 'item', 'type', 'nature', 'berry', 'trainer_class'}


def load_charmap():
    single, tokens = {}, {}
    for line in open(CHARMAP, encoding='utf-8'):
        line = line.split('@')[0].rstrip()
        m = re.match(r"^'(.+)'\s*=\s*([0-9A-Fa-f ]+)$", line)
        if m:
            ch = m.group(1).replace("\\'", "'")
            single[ch] = len(m.group(2).split())
            continue
        m = re.match(r'^([A-Z_0-9]+)\s*=\s*([0-9A-Fa-f ]+)$', line)
        if m:
            tokens[m.group(1)] = len(m.group(2).split())
    return single, tokens


SINGLE, TOKENS = load_charmap()


def encoded_length(s):
    n, i, bad = 0, 0, []
    while i < len(s):
        if s[i] == '{':
            j = s.find('}', i)
            name = s[i + 1:j].split()[0]
            n += TOKENS.get(name, 2)
            i = j + 1
            continue
        if s[i] in SINGLE:
            n += SINGLE[s[i]]
        else:
            bad.append(s[i])
        i += 1
    return n, bad


def check_rows(rows, label):
    problems = []
    for r in rows:
        heb = (r.get('proposed_hebrew') or '').strip()
        kind = r['kind']
        if not heb:
            problems.append('%s %s %s: empty' % (label, kind, r['constant']))
            continue
        n, bad = encoded_length(heb)
        if bad:
            problems.append('%s %s %s: unencodable %r in %s' % (label, kind, r['constant'], ''.join(bad), heb))
        lim = LIMITS.get(kind)
        if lim and n > lim:
            problems.append('%s %s %s: %d bytes > %d: %s' % (label, kind, r['constant'], n, lim, heb))
        # Word-final פ is a /p/ sound and stays non-final (FireRed's rule); acronyms with ” are exempt.
        if re.search(r'(?<!”)[כמנצ](?=[\s\-.,!?…]|$)', heb):
            problems.append('%s %s %s: non-final letter at word end: %s' % (label, kind, r['constant'], heb))
        if re.search(r'[ךםןףץ](?=[א-ת])', heb):
            problems.append('%s %s %s: final letter inside a word: %s' % (label, kind, r['constant'], heb))
    return problems


def duplicates(rows):
    seen, out = {}, []
    for r in rows:
        if r['kind'] not in UNIQUE:
            continue
        heb = (r.get('proposed_hebrew') or '').strip()
        if not heb:
            continue
        key = (r['kind'], heb)
        if key in seen and seen[key]['english'] != r['english']:
            out.append('DUP %s "%s": %s / %s' % (r['kind'], heb, seen[key]['constant'], r['constant']))
        seen.setdefault(key, r)
    return out


def main():
    args = sys.argv[1:]
    if args == ['--all']:
        rows, dupkeys = {}, []
        for r in csv.DictReader(open(paths.GLOSSARY, encoding='utf-8')):
            key = (r['kind'], r['constant'])
            if key in rows:
                dupkeys.append('DUPKEY %s %s: "%s" and "%s" share a key; only the last is checked'
                               % (key + (rows[key]['english'], r['english'])))
            rows[key] = r
        for f in sorted(glob.glob(os.path.join(ROOT, 'glossary_done', '*.csv'))):
            for r in csv.DictReader(open(f, encoding='utf-8')):
                rows[(r['kind'], r['constant'])] = r
        rows = list(rows.values())
        probs = dupkeys + check_rows([r for r in rows if r.get('proposed_hebrew')], 'glossary')
        probs += duplicates(rows)
        todo = [r for r in rows if not (r.get('proposed_hebrew') or '').strip()]
        print('\n'.join(probs))
        print('rows %d, still empty %d, problems %d' % (len(rows), len(todo), len(probs)))
        sys.exit(1 if probs else 0)
    allp = []
    for f in args:
        rows = list(csv.DictReader(open(f, encoding='utf-8')))
        allp += check_rows(rows, os.path.basename(f)) + duplicates(rows)
    print('\n'.join(allp) if allp else 'ok')
    sys.exit(1 if allp else 0)


if __name__ == '__main__':
    main()
