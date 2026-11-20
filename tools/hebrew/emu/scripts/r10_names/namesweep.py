#!/usr/bin/env python3
"""Round 10, names of things that are not Pokémon: a static sweep of every name table against the
glossary rows, and of each name against itself across tables and dialogue.

    namesweep.py OUT_DIR

Reads HNS_TREE (Hebrew), HNS_BASELINE (the Hebrew engine with English strings, same structure)
and the glossary (paths.py). Writes OUT_DIR/namesweep.json and OUT_DIR/namesweep.txt.

Checks:
  T  table vs row: a name in a source table differs from its glossary row (by constant, or by
     English name for trainer names), or is Latin while its row is Hebrew
  L  Latin left in a name table (no Hebrew letter) with no row: listed apart, not a finding
  X  the same English name has two Hebrew names across the tables (trainer names in the party file,
     the Frontier, Tent, Hill, contest and trade tables; berry stem vs berry item; species vs doll)
  D  dialogue: an English string names a thing in upper case (item, move, map section, trainer
     class, ability, decoration) and the Hebrew string of the same key does not contain the row's
     Hebrew name (allowing one-letter prefixes and the definite article); candidates only
"""
import csv
import json
import os
import re
import sys
from collections import defaultdict

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, '..', '..', '..'))            # tools/hebrew
import paths  # noqa: E402
import audit  # noqa: E402

HE_TREE = paths.TREE
EN_TREE = paths.BASELINE
HEB = re.compile('[א-ת]')

MACRO = re.compile(r'\b(?:__|_|COMPOUND_STRING|ITEM_NAME|ITEM_PLURAL_NAME)\(\s*((?:"(?:[^"\\\n]|\\.)*"\s*)+)\)')
LIT = re.compile(r'"((?:[^"\\\n]|\\.)*)"')
DESIG = re.compile(r'^\s*\[\s*([A-Z_][A-Z0-9_]*)(?:\s*-\s*[A-Z_0-9]+)?\s*\]\s*=')
FIELD = re.compile(r'^\s*\.(\w+)\s*=\s*')


def read(tree, rel):
    with open(os.path.join(tree, rel), encoding='utf-8') as f:
        return f.read()


def table_fields(tree, rel, fields):
    """{(designator, field): (text, line)} for designated initialisers whose .field is a string."""
    out = {}
    cur = None
    src = audit.blank_c_comments(read(tree, rel))
    for ln, line in enumerate(src.split('\n'), 1):
        m = DESIG.match(line)
        if m:
            cur = m.group(1)
        m = FIELD.match(line)
        if m and m.group(1) in fields and cur:
            mm = MACRO.search(line)
            if mm:
                out[(cur, m.group(1))] = (''.join(LIT.findall(mm.group(1))), ln)
    return out


def trainer_classes(tree):
    out = {}
    src = read(tree, 'src/battle_main.c')
    for ln, line in enumerate(src.split('\n'), 1):
        m = re.match(r'^\s*\[(TRAINER_CLASS_\w+)\]\s*=\s*\{\s*_\("((?:[^"\\]|\\.)*)"\)', line)
        if m:
            out[(m.group(1), 'name')] = (m.group(2), ln)
    return out


def speaker_names(tree):
    out = {}
    for ln, line in enumerate(read(tree, 'src/data/speaker_names.h').split('\n'), 1):
        m = re.match(r'^\s*\[(SP_NAME_\w+)\]\s*=\s*COMPOUND_STRING\("((?:[^"\\]|\\.)*)"\)', line)
        if m:
            out[(m.group(1), 'name')] = (m.group(2), ln)
    return out


def party_names(tree, rel):
    out = {}
    cur = None
    for ln, line in enumerate(read(tree, rel).split('\n'), 1):
        m = re.match(r'^===\s*(\w+)\s*===', line)
        if m:
            cur = m.group(1)
        m = re.match(r'^Name:\s*(.*?)\s*$', line)
        if m and cur:
            out[(cur, 'name')] = (m.group(1), ln)
    return out


def mapsec_names(tree):
    data = json.loads(read(tree, 'src/data/region_map/region_map_sections.json'))
    raw = read(tree, 'src/data/region_map/region_map_sections.json').split('\n')
    out = {}
    for it in data.get('hns_map_sections', []):
        needle = '"id": "%s"' % it['id']
        ln = next((k + 1 for k, l in enumerate(raw) if needle in l and k > 1700), 0)
        out[(it['id'], 'name')] = (it.get('name', ''), ln)
    return out


def ordinal_literals(tree, rel, field_rx):
    """[(field, text, line)] for every '.field = _("...")' in file order (structure-identical trees)."""
    out = []
    for ln, line in enumerate(read(tree, rel).split('\n'), 1):
        m = re.match(r'^\s*\.(\w+)\s*=\s*_\("((?:[^"\\]|\\.)*)"\)', line)
        if m and re.match(field_rx, m.group(1)):
            out.append((m.group(1), m.group(2), ln))
    return out


def load_glossary():
    rows = list(csv.DictReader(open(paths.GLOSSARY, encoding='utf-8')))
    by_const = {}
    by_en = defaultdict(list)
    for i, r in enumerate(rows, 2):
        r['_line'] = i
        by_const[(r['kind'], r['constant'])] = r
        by_en[(r['kind'], r['english'])].append(r)
    return rows, by_const, by_en


def norm(s):
    return s.replace('{PKMN}', 'פוקימון').strip()


def main():
    out_dir = sys.argv[1]
    os.makedirs(out_dir, exist_ok=True)
    rows, by_const, by_en = load_glossary()
    findings, latin_no_row, inventory = [], [], defaultdict(dict)

    def add(code, kind, const, rel, ln, en, he, row, msg):
        findings.append({'code': code, 'kind': kind, 'constant': const, 'file': rel, 'line': ln,
                         'english': en, 'hebrew': he,
                         'glossary': (row or {}).get('proposed_hebrew'),
                         'glossary_line': (row or {}).get('_line'), 'msg': msg})

    TABLES = [
        ('item', 'src/data/items.h', ('name',), lambda t: table_fields(t, 'src/data/items.h', ('name', 'pluralName'))),
        ('move', 'src/data/moves_info.h', ('name',), lambda t: table_fields(t, 'src/data/moves_info.h', ('name',))),
        ('ability', 'src/data/abilities.h', ('name',), lambda t: table_fields(t, 'src/data/abilities.h', ('name',))),
        ('nature', 'src/pokemon.c', ('name',), lambda t: {k: v for k, v in table_fields(t, 'src/pokemon.c', ('name',)).items() if k[0].startswith('NATURE_')}),
        ('type', 'src/data/types_info.h', ('name', 'generic'), lambda t: table_fields(t, 'src/data/types_info.h', ('name', 'generic'))),
        ('decoration', 'src/data/decoration/header.h', ('name',), lambda t: table_fields(t, 'src/data/decoration/header.h', ('name',))),
        ('berry', 'src/berry.c', ('name',), lambda t: table_fields(t, 'src/berry.c', ('name',))),
        ('trainer_class', 'src/battle_main.c', ('name',), trainer_classes),
        ('mapsec', 'src/data/region_map/region_map_sections.json', ('name',), mapsec_names),
        ('speaker', 'src/data/speaker_names.h', ('name',), speaker_names),
    ]
    for kind, rel, _f, fn in TABLES:
        he, en = fn(HE_TREE), fn(EN_TREE)
        for (const, field), (htext, ln) in sorted(he.items(), key=lambda kv: kv[1][1]):
            etext = en.get((const, field), ('', 0))[0]
            gkind = kind
            if kind == 'item' and field == 'pluralName':
                gkind = 'item_plural'
            if kind == 'type' and field == 'generic':
                gkind = 'type_generic'
            row = by_const.get((gkind, const))
            inventory[gkind][const] = {'he': htext, 'en': etext, 'file': rel, 'line': ln}
            if row is None:
                if not HEB.search(htext) and re.search('[A-Za-z]', htext):
                    latin_no_row.append({'kind': gkind, 'constant': const, 'file': rel, 'line': ln, 'text': htext, 'english': etext})
                continue
            g = norm(row['proposed_hebrew'])
            if norm(htext) != g:
                code = 'T-LATIN' if (not HEB.search(htext) and HEB.search(g)) else 'T'
                add(code, gkind, const, rel, ln, etext, htext, row, 'source differs from glossary row')

    # trainer names: party files, keyed by English name
    for rel in ('src/data/trainers_hns.party', 'src/data/battle_partners.party'):
        he, en = party_names(HE_TREE, rel), party_names(EN_TREE, rel)
        for (tid, _), (htext, ln) in he.items():
            etext = en.get((tid, 'name'), ('', 0))[0]
            inventory['trainer_name'][tid] = {'he': htext, 'en': etext, 'file': rel, 'line': ln}
            cands = by_en.get(('trainer_name', etext), [])
            if not cands:
                if not HEB.search(htext) and re.search('[A-Za-z]', htext):
                    latin_no_row.append({'kind': 'trainer_name', 'constant': tid, 'file': rel, 'line': ln, 'text': htext, 'english': etext})
                continue
            if all(norm(c['proposed_hebrew']) != norm(htext) for c in cands):
                add('T-LATIN' if not HEB.search(htext) else 'T', 'trainer_name', tid, rel, ln, etext, htext, cands[0],
                    'party name differs from the trainer_name row')

    # ordinal tables: frontier, tent, hill, contest, trade (pair EN/HE by position)
    ORD = [
        ('frontier_trainer', 'src/data/battle_frontier/battle_frontier_trainers.h', r'^trainerName$'),
        ('tent_trainer', 'src/data/battle_frontier/battle_tent.h', r'^trainerName$'),
        ('hill_trainer', 'src/data/battle_frontier/trainer_hill.h', r'^name$'),
        ('contest', 'src/data/contest_opponents.h', r'^(monName|trainerName)$'),
        ('trade', 'src/data/trade.h', r'^(nickname|otName)$'),
    ]
    for kind, rel, frx in ORD:
        he, en = ordinal_literals(HE_TREE, rel, frx), ordinal_literals(EN_TREE, rel, frx)
        if len(he) != len(en):
            add('STRUCT', kind, '-', rel, 0, len(en), len(he), None, 'literal counts differ')
            continue
        for (fld, htext, ln), (_f2, etext, _l2) in zip(he, en):
            kinds = {'contest': ('contest_nickname', 'contest_trainer') if fld == 'monName' else ('contest_trainer', 'contest_nickname'),
                     'trade': ('trade_nickname', 'trade_ot', 'trade_name')}.get(kind, (kind,))
            kinds = tuple(kinds) + ('trainer_name',)
            inventory[kind]['%s:%d' % (rel, ln)] = {'he': htext, 'en': etext, 'file': rel, 'line': ln}
            cands = [c for k in kinds for c in by_en.get((k, etext), [])]
            if not cands:
                if not HEB.search(htext) and re.search('[A-Za-z]', htext):
                    latin_no_row.append({'kind': kind, 'constant': fld, 'file': rel, 'line': ln, 'text': htext, 'english': etext})
                continue
            own = [c for c in cands if c['kind'] != 'trainer_name']
            ref = own or cands
            if all(norm(c['proposed_hebrew']) != norm(htext) for c in ref):
                add('T-LATIN' if not HEB.search(htext) and any(HEB.search(c['proposed_hebrew']) for c in ref) else 'T',
                    kind, fld, rel, ln, etext, htext, ref[0], 'differs from its row')
            # cross-check with the plain trainer_name row of the same English name
            tn = by_en.get(('trainer_name', etext), [])
            if own and tn and all(norm(c['proposed_hebrew']) != norm(tn[0]['proposed_hebrew']) for c in own):
                add('X', kind, fld, rel, ln, etext, htext, tn[0],
                    'same English name as a trainer_name row with another Hebrew spelling (%s row says %s)'
                    % (own[0]['kind'], own[0]['proposed_hebrew']))

    # X: same English across glossary kinds of names of people, different Hebrew
    people = ('trainer_name', 'frontier_trainer', 'tent_trainer', 'hill_trainer', 'contest_trainer',
              'trade_ot', 'trade_name', 'name', 'speaker')
    by_en_people = defaultdict(set)
    for r in rows:
        if r['kind'] in people and r['proposed_hebrew']:
            by_en_people[r['english'].upper()].add((r['proposed_hebrew'], r['kind'], r['constant'], r['_line']))
    cross_people = []
    for en, s in sorted(by_en_people.items()):
        if len({x[0] for x in s}) > 1:
            cross_people.append({'english': en, 'variants': sorted(s)})

    # berry stem vs berry item name
    berry_x = []
    for (k, const), r in by_const.items():
        if k != 'berry':
            continue
        item = by_const.get(('item', const))
        if item and r['proposed_hebrew'] not in item['proposed_hebrew']:
            berry_x.append({'constant': const, 'berry': r['proposed_hebrew'], 'item': item['proposed_hebrew']})

    # dolls / cushions / posters named after a species: the species row should be inside
    species_en = {r['english'].upper(): r['proposed_hebrew'] for r in rows if r['kind'] == 'species'}
    doll_x = []
    for const, v in inventory['decoration'].items():
        m = re.match(r'^(.*?) (DOLL|CUSHION|POSTER|MAT)$', v['en'] or '')
        if not m:
            continue
        sp = m.group(1).upper().replace('POKé', 'POKé')
        he_sp = species_en.get(sp)
        if he_sp and he_sp not in v['he']:
            doll_x.append({'constant': const, 'english': v['en'], 'hebrew': v['he'], 'species_row': he_sp,
                           'file': v['file'], 'line': v['line']})

    # D: dialogue candidates
    NAMEKINDS = ('item', 'move', 'mapsec', 'trainer_class', 'ability', 'decoration')
    names = []
    for r in rows:
        if r['kind'] in NAMEKINDS and r['english'] and r['proposed_hebrew'] and len(r['english']) >= 4:
            en = r['english']
            if en.upper() != en or not re.search('[A-Z]', en):
                continue
            names.append((r['kind'], en, r['proposed_hebrew'], r['_line']))
    names.sort(key=lambda x: -len(x[1]))
    first_word = defaultdict(list)
    for n in names:
        fw = re.match(r"[A-Zé][A-Zé'.\-]*", n[1])
        if fw:
            first_word[fw.group(0)].append(n)
    he_entries = {e.key: e for e in audit.extract_tree(HE_TREE)}
    en_entries = {e.key: e for e in audit.extract_tree(EN_TREE)}
    SKIP_KINDS = {'item_name', 'item_plural', 'move_name', 'ability_name', 'type_name', 'map_name',
                  'trainer_name', 'species_name', 'category', 'type_generic'}
    dialog = []
    stripdef = lambda s: re.sub(r'(^|\s)ה(?=[א-ת])', r'\1', s)
    for key, ee in en_entries.items():
        he = he_entries.get(key)
        if not he or ee.kind in SKIP_KINDS or not HEB.search(he.text):
            continue
        if '/debug.c' in ee.file or 'debug.inc' in ee.file or 'easy_chat' in ee.file:
            continue
        etext = ee.text.replace('\\n', ' ').replace('\\l', ' ').replace('\\p', ' ')
        htext = he.text.replace('\\n', ' ').replace('\\l', ' ').replace('\\p', ' ')
        hflat = stripdef(htext)
        used = []
        toks = set(re.findall(r"[A-Zé][A-Zé'.\-]*", etext))
        cands = []
        for t in toks:
            cands += first_word.get(t, [])
        cands.sort(key=lambda x: -len(x[1]))
        for kind, en, hname, gl in cands:
            if any(en in u for u in used):
                continue
            if not re.search(r'(?<![A-Za-z])' + re.escape(en) + r'(?![A-Za-z])', etext):
                continue
            used.append(en)
            core = stripdef(hname)
            if hname in htext or core in hflat:
                continue
            # allow construct-state / plural changes on the last letter of the first word
            words = core.split()
            loose = r'\s'.join(re.escape(w[:-1]) + r'\S{0,3}' if len(w) > 2 else re.escape(w) for w in words)
            if re.search(loose, hflat):
                continue
            dialog.append({'key': key, 'file': he.file, 'line': he.line, 'kind': kind, 'english_name': en,
                           'glossary': hname, 'glossary_line': gl, 'en': ee.text[:200], 'he': he.text[:200]})

    res = {'findings': findings, 'latin_no_row': latin_no_row, 'cross_people': cross_people,
           'berry_vs_item': berry_x, 'doll_vs_species': doll_x, 'dialogue_candidates': dialog,
           'counts': {k: len(v) for k, v in inventory.items()}}
    json.dump(res, open(os.path.join(out_dir, 'namesweep.json'), 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    json.dump(inventory, open(os.path.join(out_dir, 'name_inventory.json'), 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
    with open(os.path.join(out_dir, 'namesweep.txt'), 'w', encoding='utf-8') as f:
        f.write('counts %s\n' % json.dumps(res['counts']))
        f.write('\n== T: table vs glossary (%d)\n' % len(findings))
        for x in findings:
            f.write('%s %s %s %s:%s en=%r he=%r glossary=%r (glossary.csv:%s) %s\n' % (
                x['code'], x['kind'], x['constant'], x['file'], x['line'], x['english'], x['hebrew'],
                x['glossary'], x['glossary_line'], x['msg']))
        f.write('\n== Latin names without a glossary row (%d, not findings)\n' % len(latin_no_row))
        for x in latin_no_row:
            f.write('%s %s %s:%s %r\n' % (x['kind'], x['constant'], x['file'], x['line'], x['text']))
        f.write('\n== X: same English person name, several Hebrew rows (%d)\n' % len(cross_people))
        for x in cross_people:
            f.write('%s: %s\n' % (x['english'], ' | '.join('%s (%s %s :%s)' % v for v in x['variants'])))
        f.write('\n== berry stem not inside the berry item name (%d)\n' % len(berry_x))
        for x in berry_x:
            f.write('%s\n' % json.dumps(x, ensure_ascii=False))
        f.write('\n== decoration named after a species without the species row (%d)\n' % len(doll_x))
        for x in doll_x:
            f.write('%s\n' % json.dumps(x, ensure_ascii=False))
        f.write('\n== D: dialogue candidates (%d)\n' % len(dialog))
        for x in dialog:
            f.write('%s:%s %s %r -> %r (glossary.csv:%s)\n   EN %s\n   HE %s\n' % (
                x['file'], x['line'], x['kind'], x['english_name'], x['glossary'], x['glossary_line'], x['en'], x['he']))
    print('T %d, latin-no-row %d, X people %d, berry %d, doll %d, dialogue %d' % (
        len(findings), len(latin_no_row), len(cross_people), len(berry_x), len(doll_x), len(dialog)))


if __name__ == '__main__':
    main()
