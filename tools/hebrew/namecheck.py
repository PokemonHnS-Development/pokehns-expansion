#!/usr/bin/env python3
"""Validate glossary rows: encodable characters, byte limits per kind, duplicates within a kind, and
(with --all) two glossary rows with the same kind and constant (DUPKEY), where one would hide the other.

Usage:
  namecheck.py FILE.csv [FILE.csv ...]   check these chunk files (column proposed_hebrew)
  namecheck.py --all                     check glossary.csv merged with every glossary_done/*.csv
  namecheck.py [--all|FILE...] [--fr-sync] [--translit] [--dupes] [--warnings]
                                         also print consistency warnings (WARN lines); they never
                                         change the exit status. Without --all or files they run
                                         on the merged glossary. --warnings = all three.

Byte length is the encoded length in the game charmap: one byte per Hebrew letter, space, digit or
punctuation mark; {TOKENS} count as their charmap expansion (e.g. {PKMN} = 2).

The warnings (allowlist: tools/hebrew/data/namecheck_allow.json, one reason per entry):
  --fr-sync   a name that differs from the FireRed Hebrew tree (HNS_FIRERED) as it is now, beyond
              spacing and hyphens: FireRed keeps fixing its names, and H&S inherited many of them.
              An allowlist entry pins both names, so it fires again when either side changes.
  --translit  a transliterated name (species, trainers, nicknames) that breaks a rule of
              translation/hebrew/transliteration_rules.md, e.g. an English X without קס. The entry
              pins the Hebrew.
  --dupes     one English person name spelled two ways in the person-name kinds.
An allowlist entry that no longer matches anything is reported as STALE.
"""
import csv, glob, json, os, re, sys

import paths

ROOT = paths.TRANSLATION
CHARMAP = os.path.join(paths.FONTS_TREE, 'charmap.txt')
ALLOW = os.path.join(paths.DATA, 'namecheck_allow.json')

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


# --- consistency warnings -------------------------------------------------------------------

# FireRed Hebrew name tables: (file, constant prefix, glossary kind).
FR_TABLES = [
    ('src/data/text/species_names.h', 'SPECIES_', 'species'),
    ('src/data/text/move_names.h', 'MOVE_', 'move'),
    ('src/data/text/trainer_class_names.h', 'TRAINER_CLASS_', 'trainer_class'),
    ('src/data/text/nature_names.h', 'NATURE_', 'nature'),
    ('src/data/text/abilities.h', 'ABILITY_', 'ability'),
    ('src/battle_main.c', 'TYPE_', 'type'),
]


def _read(path):
    with open(path, encoding='utf-8') as fh:
        return fh.read()


def firered_names(tree):
    """{(kind, constant): Hebrew name} from a FireRed Hebrew tree; missing files are skipped."""
    out = {}
    for rel, prefix, kind in FR_TABLES:
        path = os.path.join(tree, rel)
        if not os.path.exists(path):
            continue
        text = _read(path)
        for m in re.finditer(r'\[(%s[A-Z0-9_]+)\]\s*=\s*_\("((?:[^"\\]|\\.)*)"\)' % prefix, text):
            out[(kind, m.group(1))] = _fr_display(m.group(2))
    path = os.path.join(tree, 'src/data/items.json')
    if os.path.exists(path):
        items = json.loads(_read(path))
        for it in (items['items'] if isinstance(items, dict) else items):
            c = it.get('itemId') or it.get('id')
            if c and it.get('english'):
                out[('item', c)] = _fr_display(it['english'])
    path = os.path.join(tree, 'src/data/region_map/region_map_sections.json')
    if os.path.exists(path):
        for sec in json.loads(_read(path)).get('map_sections', []):
            if sec.get('hebrew_name'):
                out[('mapsec', sec['map_section'])] = _fr_display(sec['hebrew_name'])
    return out


def _bare(s):
    """A name without spaces and hyphens: FireRed squeezes them out to fit its byte limits."""
    return re.sub(r'[\s\-]', '', s or '')


def _fr_display(s):
    """A FireRed source string as the game shows it: FireRed writes digit runs reversed (its
    right-to-left renderer flips them back) and pads some names with $."""
    return re.sub(r'[0-9]+', lambda m: m.group(0)[::-1], s).rstrip('$')


def fr_sync(rows, fr, allow, used):
    out = []
    for r in rows:
        key = (r['kind'], r['constant'])
        hs = (r.get('proposed_hebrew') or '').strip()
        if key not in fr or not hs or _bare(fr[key]) == _bare(hs):
            continue
        name = '%s:%s' % key
        entry = allow.get(name)
        if entry and entry.get('hs') == hs and entry.get('firered') == fr[key]:
            used.add(('fr_sync', name))
            continue
        out.append('WARN FRSYNC %s %s: H&S "%s", FireRed now "%s"' % (r['kind'], r['constant'], hs, fr[key]))
    return out


TRANSLIT_KINDS = {'species', 'trainer_name', 'frontier_trainer', 'tent_trainer', 'hill_trainer',
                  'contest_trainer', 'contest_nickname', 'trade_nickname', 'trade_ot', 'trade_name', 'name'}
# (rule, test on the upper-case English and the Hebrew); rules from transliteration_rules.md.
TRANSLIT_RULES = [
    ('final P as ף (P is a non-final פ)', lambda e, h: re.search(r'P\b', e) and re.search(r'ף(\s|$|-)', h)),
    ('final K as ך (K is ק)', lambda e, h: re.search(r'K\b', e) and re.search(r'ך(\s|$|-)', h)),
    ('X without קס/קז/כס/גז', lambda e, h: 'X' in e and not re.search(r'קס|קז|כס|גז', h)
     and not (e.startswith('X') and h.startswith('ז'))),          # an initial X is /z/
    ('SH without ש', lambda e, h: 'SH' in e and 'ש' not in h),
    ('Z without ז/צ', lambda e, h: 'Z' in e and not re.search(r'[זצץ]', h)),
    ("J without ג'/ז'/י", lambda e, h: 'J' in e and not re.search(r"ג'|ז'|^י|ה", h)),
    ("CH without צ'/ק/כ/ש", lambda e, h: 'CH' in e and not re.search(r"[צץ]'|ק|כ|ש", h)),
    ('TH without ת/ט/ד/ס/ז', lambda e, h: 'TH' in e and not re.search(r'ת|ט|ד|ס|ז', h)),
    ('initial vowel without א/ע/י', lambda e, h: re.match(r'[AEIOU]', e) and not re.match(r'[אעי]', h)
     and not e.startswith(('EU', 'U'))),
    ('initial V/W without ו', lambda e, h: re.match(r'[VW]', e) and not re.match(r'ו', h)),
    ('final -Y without י/ה', lambda e, h: re.search(r'[^AEOU]Y$', e) and not re.search(r'[יה]$', h)),
    ('Latin letters left', lambda e, h: re.search(r'[A-Za-z]', h)),
]


def translit(rows, allow, used):
    out = []
    for r in rows:
        if r['kind'] not in TRANSLIT_KINDS or r.get('status') != 'proposed':
            continue
        e, h = r['english'].upper(), (r.get('proposed_hebrew') or '').strip()
        hits = [name for name, test in TRANSLIT_RULES if h and test(e, h)]
        if not hits:
            continue
        key = '%s:%s' % (r['kind'], r['constant'])
        entry = allow.get(key)
        if entry and entry.get('hebrew') == h:
            used.add(('translit', key))
            continue
        out.append('WARN TRANSLIT %s %s: %s -> %s (%s)' % (r['kind'], r['constant'], r['english'], h, '; '.join(hits)))
    return out


PERSON_KINDS = {'trainer_name', 'frontier_trainer', 'tent_trainer', 'hill_trainer', 'contest_trainer',
                'trade_ot', 'trade_name', 'name'}


def same_name(rows, allow, used):
    spell, kinds = {}, {}
    for r in rows:
        e, h = r['english'].upper().strip(), (r.get('proposed_hebrew') or '').strip()
        if r['kind'] in PERSON_KINDS and re.search(r'[A-Z]', e) and re.search(r'[א-ת]', h):
            spell.setdefault(e, set()).add(h)
            kinds.setdefault(e, set()).add(r['kind'])
    out = []
    for e in sorted(spell):
        if len(spell[e]) < 2:
            continue
        entry = allow.get(e)
        if entry and sorted(entry.get('spellings', [])) == sorted(spell[e]):
            used.add(('dupes', e))
            continue
        out.append('WARN SAMENAME %s: %s (%s)' % (e, ' / '.join(sorted(spell[e])), ', '.join(sorted(kinds[e]))))
    return out


def load_allow(path=None):
    path = path or ALLOW
    if not os.path.exists(path):
        return {}
    return json.loads(_read(path))


def warnings(rows, which, allow, fr=None):
    """WARN lines for the checks in WHICH ('fr_sync', 'translit', 'dupes'), then STALE entries."""
    used, out = set(), []
    if 'fr_sync' in which:
        if fr is None:
            out.append('WARN FRSYNC skipped: no FireRed tree (set HNS_FIRERED)')
        else:
            out += fr_sync(rows, fr, allow.get('fr_sync', {}), used)
    if 'translit' in which:
        out += translit(rows, allow.get('translit', {}), used)
    if 'dupes' in which:
        out += same_name(rows, allow.get('dupes', {}), used)
    for check in sorted(which):
        if check == 'fr_sync' and fr is None:
            continue
        for key in sorted(allow.get(check, {})):
            if (check, key) not in used:
                out.append('WARN STALE %s %s: allowlisted but no longer matches' % (check, key))
    return out, len(used)


WARN_FLAGS = {'--fr-sync': ['fr_sync'], '--translit': ['translit'], '--dupes': ['dupes'],
              '--warnings': ['fr_sync', 'translit', 'dupes']}


def merged_glossary():
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
    return list(rows.values()), dupkeys


def print_warnings(rows, which):
    if not which:
        return
    tree = paths.FIRERED
    fr = firered_names(tree) if 'fr_sync' in which and tree and os.path.isdir(tree) else None
    out, allowed = warnings(rows, which, load_allow(), fr)
    if out:
        print('\n'.join(out))
    print('warnings %d, allowlisted %d' % (len(out), allowed))


def main():
    args, which = [], set()
    for a in sys.argv[1:]:
        if a in WARN_FLAGS:
            which.update(WARN_FLAGS[a])
        else:
            args.append(a)
    if args == ['--all']:
        rows, dupkeys = merged_glossary()
        probs = dupkeys + check_rows([r for r in rows if r.get('proposed_hebrew')], 'glossary')
        probs += duplicates(rows)
        todo = [r for r in rows if not (r.get('proposed_hebrew') or '').strip()]
        print('\n'.join(probs))
        print('rows %d, still empty %d, problems %d' % (len(rows), len(todo), len(probs)))
        print_warnings(rows, which)
        sys.exit(1 if probs else 0)
    if not args and which:
        print_warnings(merged_glossary()[0], which)
        sys.exit(0)
    allp, allrows = [], []
    for f in args:
        rows = list(csv.DictReader(open(f, encoding='utf-8')))
        allrows += rows
        allp += check_rows(rows, os.path.basename(f)) + duplicates(rows)
    print('\n'.join(allp) if allp else 'ok')
    print_warnings(allrows, which)
    sys.exit(1 if allp else 0)


if __name__ == '__main__':
    main()
