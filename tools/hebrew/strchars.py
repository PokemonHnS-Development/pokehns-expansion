#!/usr/bin/env python3
"""Count the non-ASCII characters and {TOKENS} that appear inside string literals.

Scans data/ src/ include/ for "..." literals (C, .inc/.s, .pory, .json) and
whole lines of .party files, then maps each non-ASCII character to its byte
through the Latin section of charmap.txt. Prints per-character counts with
example locations, so a charmap slot can be checked for real use.

  strchars.py [TREE]        TREE defaults to HNS_TREE
"""
import os, re, sys, collections

import paths

repo = sys.argv[1] if len(sys.argv) > 1 else paths.TREE
LATIN_END = 163  # last line of the Latin section in charmap.txt

charmap = {}
tokens = {}
for i, line in enumerate(open(f'{repo}/charmap.txt', encoding='utf-8'), 1):
    m = re.match(r"^'(.+?)'\s*=\s*([0-9A-Fa-f ]+)", line)
    if m and i <= LATIN_END:
        ch = m.group(1).replace("\\'", "'")
        charmap.setdefault(ch, m.group(2).split()[0].upper())
    m = re.match(r"^([A-Z_0-9]+)\s*=\s*([0-9A-Fa-f ]+)", line)
    if m:
        tokens.setdefault(m.group(1), m.group(2).strip().upper())

lit = re.compile(r'"((?:[^"\\\n]|\\.)*)"')
count = collections.Counter()
where = collections.defaultdict(list)
tokcount = collections.Counter()
tokwhere = collections.defaultdict(list)
exts = ('.inc', '.s', '.c', '.h', '.json', '.pory', '.party', '.txt')
for top in ('data', 'src', 'include'):
    for dp, dn, fn in os.walk(f'{repo}/{top}'):
        for f in fn:
            if not f.endswith(exts):
                continue
            p = os.path.join(dp, f)
            rel = os.path.relpath(p, repo)
            try:
                text = open(p, encoding='utf-8').read()
            except UnicodeDecodeError:
                continue
            for ln, line in enumerate(text.split('\n'), 1):
                if f.endswith('.party'):
                    if line.lstrip().startswith(('/*', '//', '*')):
                        continue
                    pieces = [line]
                else:
                    pieces = lit.findall(line)
                for s in pieces:
                    for ch in s:
                        if ord(ch) > 0x7E:
                            count[ch] += 1
                            if len(where[ch]) < 4:
                                where[ch].append(f'{rel}:{ln}')
                    for t in re.findall(r'\{([A-Z_0-9]+)\}', s):
                        tokcount[t] += 1
                        if len(tokwhere[t]) < 3:
                            tokwhere[t].append(f'{rel}:{ln}')

print('== non-ASCII characters in string literals ==')
for ch, n in sorted(count.items(), key=lambda kv: (charmap.get(kv[0], 'ZZ'), kv[0])):
    print(f"U+{ord(ch):04X} {ch!r:6} byte={charmap.get(ch, '--'):3} n={n:6}  e.g. {', '.join(where[ch])}")
print('== {TOKENS} used in literals whose first charmap byte is < 0xF8 (args of PLAY_BGM etc. included) ==')
for t, n in sorted(tokcount.items()):
    v = tokens.get(t, '')
    if v and len(v.split()) <= 5 and int(v.split()[0], 16) < 0xF8:
        print(f'{t:16} = {v:15} n={n:6}  e.g. {", ".join(tokwhere[t])}')
