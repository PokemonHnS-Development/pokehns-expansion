#!/usr/bin/env python3
"""Static layout audit of every player-visible string in a Heart & Soul tree.

Usage:
  audit.py [--tree DIR] [--baseline EN_TREE] [--json OUT.json] [--report OUT.txt] [PATH ...]

  --tree DIR          tree to audit (default HNS_TREE, this repository). Works on the
                      English tree too: there every finding is an English baseline finding.
  --baseline EN_TREE  audit EN_TREE the same way and suppress a finding on a translated string when
                      the English string with the same key already overflows the same check by the
                      same amount or more (e.g. --baseline "$HNS_UPSTREAM")
  --fonts-tree DIR    src/fonts.c and charmap.txt to measure with (default HNS_FONTS_TREE)
  --charmap FILE      charmap override (default <fonts-tree>/charmap.txt, which has the Hebrew slots)
  --fill max|avg      placeholder glyphs: widest (default) or average Hebrew glyph
  --subst NAME=SPEC   override a worst-case placeholder (textwidth.py grammar), e.g. STR_VAR_1=W3
  --json OUT          machine-readable findings ('-' = stdout)
  --report OUT        readable report (default: stdout). Its folder is created if missing, and stdout
                      then gets only the report's '== ' summary lines
  --strict            warnings count as errors for the exit status
  --fail-on-english   errors on untranslated (English) strings also fail the run
  --max-report N      list at most N findings per section in the readable report (default 400)
  PATH ...            limit the audit to these files/directories (relative to --tree)

What is checked (budgets from data/budgets.json, runtime buffer sizes from the engine source):
  WIDTH       a line is wider than its budget in px (prompt lines, ending in \\l or \\p, get 8 px
              less for the down arrow); names with a fit chain are judged in the narrowest font
              and get a FIT warning when only the narrower fonts fit
  LINES       more rows on one page than the window has (\\n adds a row, \\l scrolls, \\p clears)
  BUFFER      bytes after worst-case expansion overflow a runtime buffer: gStringVar4 999 (field
              messages), gDisplayedStringBattle 424 (battle), 422 (trainer lose/win text)
  BYTES       a name is longer than its compile-time field (species 12, move 16, item 19, ...)
  TERMINATOR  a .string block does not end in $
  CHARSET     a character or {CONSTANT} the charmap cannot encode
Each finding is tagged lang=he (string holds Hebrew) or lang=en (untranslated). English findings are
reported in their own section and do not fail the run (see --fail-on-english).

Classification (kind): data/**/*.inc text = overworld_dialogue, except labels used as lose/victory
text by trainerbattle macros (battle_trainer_text), data/text/match_call*.inc (phone_call_text) and
the label patterns in LABEL_RULES (e.g. frontier tutor move descriptions, a 96x48 window). Script
blocks under #if/#ifdef take the branch the H&S build compiles (CPP_DEFINES);
src/battle_message.c = battle_message (UI strings by name, short pieces = fragment); items.h,
moves_info.h, abilities.h, contest_moves.h, species_info/*.h, types_info.h, MAPSEC_* tables,
region_map_sections.json and *.party Name: lines by field. Everything else is 'unclassified'
(CHARSET only). Nothing here was checked on screen; budgets marked UNVERIFIED in budgets.md stay so.

Exit status: 1 if any error remains (lang=he, not suppressed), else 0.
"""
import argparse
import bisect
import fnmatch
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import textwidth as tw  # noqa: E402
from textwidth import read_text  # noqa: E402
import paths  # noqa: E402

TREE = paths.TREE
BUDGETS = paths.BUDGETS
HEBREW_RE = re.compile('[א-ת]')

# ---------------------------------------------------------------------------- kinds

Check = tuple  # (where, fonts(list), px_warn, px_err, prompt_px, lines)


def _chain(spec):
    """'FONT_NARROW->NARROWER' -> ['FONT_NARROW', 'FONT_NARROWER']; 'A / B' keeps A."""
    spec = spec.split('/')[0].strip()
    out = []
    for p in spec.split('->'):
        p = re.sub(r'\(.*?\)', '', p).strip()
        if p and not p.startswith('FONT_'):
            p = 'FONT_' + p
        if p:
            out.append(p)
    return out


def _px(v):
    if isinstance(v, (int, float)):
        return int(v)
    m = re.match(r'\s*(\d+)', str(v or ''))
    return int(m.group(1)) if m else None


def build_kinds(budgets_path=BUDGETS):
    b = json.loads(read_text(budgets_path))
    K, X = b['kinds'], b['cross_screen']

    def from_kind(name, lines=None, where=None, px=None):
        k = K[name]
        fonts = [f for f in (k.get('fit_chain') or [k['font']]) if 'measure' not in f]
        warn = px or k['max_px_per_line']
        err = px or k.get('hard_px') or warn
        nlines = lines if lines is not None else (k['max_lines'] if isinstance(k['max_lines'], int) else 1)
        return (where or name, fonts, warn, err, k.get('prompt_line_px'), nlines)

    def from_cross(name, lines=None):
        out = []
        for e in X[name]:
            px = _px(e.get('px'))
            if px is None:
                continue
            out.append((e['where'], _chain(e['font']), px, px, None, lines or e.get('lines') or 1))
        return out

    kinds = {
        'overworld_dialogue': {'checks': [from_kind('overworld_dialogue')], 'buffer': ('gStringVar4', 999), 'inc': True},
        'phone_call_text': {'checks': [from_kind('phone_call_text')], 'buffer': ('gStringVar4', 999), 'inc': True},
        'battle_message': {'checks': [from_kind('battle_message')], 'buffer': ('gDisplayedStringBattle', 424),
                           'battle': True},
        'battle_trainer_text': {'checks': [from_kind('battle_message', where='battle_message (trainer text)')],
                                'buffer': ('gDisplayedStringBattle (lose/win text)', 422), 'battle': True,
                                'all_nbsp': True, 'inc': True},
        'battle_action_prompt': {'checks': [from_kind('battle_action_prompt')]},
        'battle_action_menu': {'checks': [from_kind('battle_action_menu', px=96, where='battle_action_menu (96 px window, columns at CLEAR_TO 56)')]},
        'battle_pp_label': {'checks': [from_kind('battle_pp_label')]},
        'battle_move_type_label': {'checks': [from_kind('battle_move_type', px=25, where='battle_move_type label')]},
        'battle_switch_prompt': {'checks': [from_kind('battle_switch_prompt')]},
        'battle_yes_no': {'checks': [from_kind('battle_yes_no')]},
        'item_description': {'checks': [from_kind('item_description')]},
        'move_description': {'checks': from_cross('move_description')},
        'contest_effect_description': {'checks': from_cross('contest_effect_description')},
        'ability_description': {'checks': [c for c in from_cross('ability') if 'description' in c[0]]},
        # budgets.json says 3 lines (navigation window at y=144); English ships 4-line entries for
        # 1231 species, and 93 + 4*16 = 157 < 160. UNVERIFIED on screen.
        'dex_entry': {'checks': [from_kind('dex_entry', lines=4)]},
        'species_name': {'checks': from_cross('species_name'), 'bytes': 12},
        'move_name': {'checks': from_cross('move_name'), 'bytes': 16},
        'item_name': {'checks': from_cross('item_name'), 'bytes': 19},
        'item_plural': {'checks': [], 'bytes': 21},
        'ability_name': {'checks': [c for c in from_cross('ability') if 'name' in c[0]], 'bytes': 16},
        'category': {'checks': [], 'bytes': 12},
        'type_name': {'checks': [('battle_move_type (type name)', ['FONT_NARROW', 'FONT_NARROWER'], 39, 39, None, 1)],
                      'bytes': 8},
        'type_generic': {'checks': [], 'bytes': 16},
        'map_name': {'checks': from_cross('map_name'), 'bytes': 19},
        'trainer_name': {'checks': [], 'bytes': 10},
        'keyboard_row': {'checks': [], 'exact_bytes': 8},
        # src/field_specials.c:3242-3249 12x6-tile window, 3316-3324 FONT_NORMAL at x=0, y=1
        'frontier_tutor_description': {'checks': [('frontier tutor window 96x48', ['FONT_NORMAL'], 96, 96, None, 3)],
                                       'inc': True},
        'fragment': {'checks': []},
        'unclassified': {'checks': []},
    }
    return kinds


# ---------------------------------------------------------------------------- extraction

class Entry(object):
    __slots__ = ('file', 'line', 'key', 'kind', 'text', 'terminated', 'source', 'note')

    def __init__(self, file, line, key, kind, text, terminated=None, source='inc', note=''):
        self.file, self.line, self.key, self.kind, self.text = file, line, key, kind, text
        self.terminated, self.source, self.note = terminated, source, note


STRING_LINE_RE = re.compile(r'^\s*\.(string|braille)\s+"((?:[^"\\]|\\.)*)"\s*(?:@.*)?$')
LABEL_RE = re.compile(r'^([A-Za-z_][A-Za-z0-9_]*)::?\s*(?:@.*)?$')
# lose/victory text argument positions per trainerbattle macro (asm/macros/event.inc:812-886)
TRAINERBATTLE_ARGS = {
    'trainerbattle_single': (2,), 'trainerbattle_double': (2,), 'trainerbattle_rematch': (2,),
    'trainerbattle_rematch_double': (2,), 'trainerbattle_no_intro': (1,), 'trainerbattle_earlyrival': (2, 3),
    'trainerbattle': (4, 9, 11),
}


def scan_trainer_text_labels(paths):
    labels = set()
    rx = re.compile(r'^\s*(trainerbattle\w*)\s+(.*?)\s*(?:@.*)?$')
    for p in paths:
        try:
            text = read_text(p)
        except (UnicodeDecodeError, OSError):
            continue
        for line in text.split('\n'):
            m = rx.match(line)
            if not m or m.group(1) not in TRAINERBATTLE_ARGS:
                continue
            args = [a.strip() for a in m.group(2).split(',')]
            for k in TRAINERBATTLE_ARGS[m.group(1)]:
                if k < len(args) and re.match(r'^[A-Za-z_]\w*$', args[k]) and args[k] not in ('NULL', 'FALSE', 'TRUE'):
                    labels.add(args[k])
    return labels


# Script text that is not drawn in the dialogue box: (file regex, label regex, kind).
LABEL_RULES = [
    (r'^data/maps/BattleFrontier_Lounge7(_hns)?/', r'^BattleFrontier_Lounge7_Text_\w+Desc(_hns)?$',
     'frontier_tutor_description'),
]

# Preprocessor symbols as the H&S build sees them (include/constants/global.h:75-76 POKEMON_HNS,
# include/config/general.h:43,49, include/config/randomizer.h:4, include/config/item.h:55).
# Script blocks under #if take the branch the H&S build takes; unknown symbols are 0, as in cpp.
CPP_DEFINES = {'IS_HNS': 1, 'IS_FRLG': 0, 'BUGFIX': 1, 'UBFIX': 1, 'RANDOMIZER_AVAILABLE': 1,
               'I_COMBINE_BAG_POCKETS': 1, 'TRUE': 1, 'FALSE': 0}


def cpp_eval(expr, defines=CPP_DEFINES):
    """Value of a simple #if expression (identifiers, defined(), !, &&, ||, ==, !=, parentheses)."""
    expr = re.sub(r'(//|/\*|@).*$', '', expr).strip()
    expr = re.sub(r'\bdefined\s*\(\s*(\w+)\s*\)|\bdefined\s+(\w+)',
                  lambda m: '1' if (m.group(1) or m.group(2)) in defines else '0', expr)
    expr = re.sub(r'[A-Za-z_]\w*', lambda m: str(defines.get(m.group(0), 0)), expr)
    expr = expr.replace('&&', ' and ').replace('||', ' or ')
    expr = re.sub(r'!(?!=)', ' not ', expr)
    if not re.match(r'^[\d\s()=!<>andortn]*$', expr):
        return False
    try:
        return bool(eval(expr, {'__builtins__': {}}, {}))
    except Exception:
        return False


class CppState(object):
    """Tracks #if/#ifdef/#elif/#else/#endif; compiled() says whether the current line is compiled."""

    def __init__(self, defines=CPP_DEFINES):
        self.defines, self.stack = defines, []        # per level: [this_branch_on, a_branch_was_taken]

    def feed(self, s):
        """Consumes a directive line (stripped); returns True when S was a conditional directive."""
        m = re.match(r'^#\s*(ifdef|ifndef|if|elif|else|endif)\b\s*(.*)$', s)
        if not m:
            return False
        d, arg = m.group(1), re.sub(r'\s*(@|//|/\*).*$', '', m.group(2)).strip()
        if d in ('if', 'ifdef', 'ifndef'):
            if d == 'if':
                on = cpp_eval(arg, self.defines)
            else:
                on = (arg.split()[0] in self.defines if arg else False) == (d == 'ifdef')
            self.stack.append([on, on])
        elif d == 'elif' and self.stack:
            top = self.stack[-1]
            top[0] = (not top[1]) and cpp_eval(arg, self.defines)
            top[1] = top[1] or top[0]
        elif d == 'else' and self.stack:
            top = self.stack[-1]
            top[0] = not top[1]
            top[1] = True
        elif d == 'endif' and self.stack:
            self.stack.pop()
        return True

    def compiled(self):
        return all(s[0] for s in self.stack)


def extract_inc(path, rel, trainer_labels):
    entries = []
    label, block, block_line, nth = None, None, 0, {}
    lines = read_text(path).split('\n')
    cpp = CppState()

    def flush():
        if block is None:
            return
        kind_ = 'overworld_dialogue'
        if label in trainer_labels:
            kind_ = 'battle_trainer_text'
        elif re.search(r'data/text/match_call', rel):
            kind_ = 'phone_call_text'
        for frx, lrx, k in LABEL_RULES:
            if re.search(frx, rel) and label and re.search(lrx, label):
                kind_ = k
        base = '%s:%s' % (rel, label or '<nolabel>')
        nth[base] = nth.get(base, 0) + 1
        key = base if nth[base] == 1 else '%s#%d' % (base, nth[base])
        text = ''.join(block)
        entries.append(Entry(rel, block_line, key, kind_, text, terminated=text.endswith('$'), source='inc'))

    for ln, raw in enumerate(lines, 1):
        s = raw.strip()
        if s.startswith('#') and cpp.feed(s):
            continue
        if not cpp.compiled():
            continue
        m = STRING_LINE_RE.match(raw)
        if m:
            if m.group(1) == 'braille':
                continue
            if block is None:
                block, block_line = [], ln
            block.append(m.group(2))
            if m.group(2).endswith('$'):
                flush()
                block = None
            continue
        if not s or s.startswith('@'):
            continue
        flush()
        block = None
        m = LABEL_RE.match(s)
        if m:
            label = m.group(1)
    flush()
    return entries


C_MACRO_RE = re.compile(r'\b(__|_|COMPOUND_STRING_SIZE_LIMIT|COMPOUND_STRING|ITEM_NAME|ITEM_PLURAL_NAME)\(\s*((?:"(?:[^"\\\n]|\\.)*"\s*)+)')
C_LIT_RE = re.compile(r'"((?:[^"\\\n]|\\.)*)"')
DESIG_RE = re.compile(r'\[\s*([A-Za-z_][A-Za-z0-9_]*)\s*\]\s*=')
TABLE_RE = re.compile(r'\b([A-Za-z_]\w*)\s*\[[^\]\n]*\]\s*=\s*\{')

BATTLE_UI = {
    'gText_WhatWillPkmnDo': 'battle_action_prompt', 'gText_WhatWillPkmnDo2': 'battle_action_prompt',
    'gText_WhatWillWallyDo': 'battle_action_prompt',
    'gText_BattleMenu': 'battle_action_menu', 'gText_SafariZoneMenu': 'battle_action_menu',
    'gText_SafariZoneMenuFrlg': 'battle_action_menu',
    'gText_MoveInterfacePP': 'battle_pp_label', 'gText_MoveInterfaceType': 'battle_move_type_label',
    'gText_BattleSwitchWhich': 'battle_switch_prompt', 'gText_BattleYesNoChoice': 'battle_yes_no',
}
# (path regex, {field or 'sym:REGEX': kind})
C_RULES = [
    (r'^src/data/items\.h$', {'name': 'item_name', 'pluralName': 'item_plural', 'description': 'item_description',
                              r'sym:^s\w*Desc$': 'item_description'}),
    (r'^src/data/moves_info\.h$', {'name': 'move_name', 'description': 'move_description'}),
    (r'^src/data/abilities\.h$', {'name': 'ability_name', 'description': 'ability_description'}),
    (r'^src/data/contest_moves\.h$', {'description': 'contest_effect_description'}),
    (r'^src/data/pokemon/species_info/.*\.h$', {'speciesName': 'species_name', 'categoryName': 'category',
                                                'description': 'dex_entry', r'sym:^g\w*PokedexText$': 'dex_entry'}),
    (r'^src/data/types_info\.h$', {'name': 'type_name', 'generic': 'type_generic'}),
]


def blank_c_comments(src):
    """Comments -> spaces (newlines kept), so offsets and line numbers stay valid."""
    out, i, n = list(src), 0, len(src)
    while i < n:
        c = src[i]
        if c == '"' or c == "'":
            q, i = c, i + 1
            while i < n and src[i] != q and src[i] != '\n':
                i += 2 if src[i] == '\\' else 1
            i += 1
        elif src.startswith('//', i):
            while i < n and src[i] != '\n':
                out[i] = ' '
                i += 1
        elif src.startswith('/*', i):
            while i < n and not src.startswith('*/', i):
                if src[i] != '\n':
                    out[i] = ' '
                i += 1
            if i < n:
                out[i] = out[i + 1] = ' '
            i += 2
        else:
            i += 1
    return ''.join(out)


def classify_c(rel, macro, field, sym, desig, text):
    if macro == '__':
        return 'keyboard_row' if rel == 'src/naming_screen.c' else 'unclassified'
    if desig and desig.startswith('MAPSEC_'):
        return 'map_name'
    for rx, table in C_RULES:
        if re.search(rx, rel):
            if field and field in table:
                return table[field]
            for k, v in table.items():
                if k.startswith('sym:') and sym and re.search(k[4:], sym):
                    return v
            return 'unclassified'
    if rel == 'src/battle_message.c':
        if sym in BATTLE_UI:
            return BATTLE_UI[sym]
        if desig and desig.startswith('STRINGID_'):
            return 'battle_message'
        body = re.sub(r'\{[^}]*\}', '', text)
        if ' ' in body.strip() and (re.search(r'[.!?…]\s*$', body) or re.search(r'\\[npl]', text)):
            return 'battle_message'
        return 'fragment'
    return 'unclassified'


def extract_c(path, rel):
    src = read_text(path)
    clean = blank_c_comments(src)
    line_starts = [0] + [m.end() for m in re.finditer(r'\n', clean)]
    desigs = [(m.start(), m.group(1)) for m in DESIG_RE.finditer(clean)]
    dpos = [d[0] for d in desigs]
    tables = [(m.start(), m.group(1)) for m in TABLE_RE.finditer(clean)]
    tpos = [t[0] for t in tables]
    entries, nth = [], {}
    for m in C_MACRO_RE.finditer(clean):
        s = m.start()
        text = ''.join(C_LIT_RE.findall(m.group(2)))
        before = clean[max(0, s - 200):s]
        fm = re.search(r'\.(\w+)\s*=\s*$', before)
        field = fm.group(1) if fm else None
        sm = re.search(r'\b([A-Za-z_]\w*)\s*\[[^\]\n]*\]\s*=\s*$', before)
        sym = sm.group(1) if sm else None
        desig = None
        di = bisect.bisect_left(dpos, s) - 1
        ti = bisect.bisect_left(tpos, s) - 1
        if di >= 0 and not sym:
            if ti < 0 or desigs[di][0] > tables[ti][0]:
                desig = desigs[di][1]
        table = tables[ti][1] if ti >= 0 and desig else None
        parts = [p for p in ((table + '[' + desig + ']') if table and desig else desig, sym,
                             ('.' + field) if field else None) if p]
        base = '%s:%s' % (rel, ''.join(parts) if parts else 'L%d' % (bisect.bisect_right(line_starts, s)))
        nth[base] = nth.get(base, 0) + 1
        key = base if nth[base] == 1 else '%s#%d' % (base, nth[base])
        kind = classify_c(rel, m.group(1), field, sym, desig, text)
        line = bisect.bisect_right(line_starts, s)
        entries.append(Entry(rel, line, key, kind, text, source='c'))
    return entries


def extract_mapsec_json(path, rel):
    data = json.loads(read_text(path))
    raw = read_text(path).split('\n')
    entries = []
    for listname, items in data.items():
        if not isinstance(items, list):
            continue
        for i, it in enumerate(items):
            if isinstance(it, dict) and isinstance(it.get('name'), str):
                needle = '"name": %s' % json.dumps(it['name'], ensure_ascii=False)
                line = next((k + 1 for k, l in enumerate(raw) if needle in l), 0)
                entries.append(Entry(rel, line, '%s:%s/%s' % (rel, listname, it.get('id', i)), 'map_name',
                                     it['name'], source='json'))
    return entries


def extract_party(path, rel):
    entries, trainer = [], None
    for ln, line in enumerate(read_text(path).split('\n'), 1):
        m = re.match(r'^===\s*(\w+)\s*===', line)
        if m:
            trainer = m.group(1)
            continue
        m = re.match(r'^Name:\s*(.*?)\s*$', line)
        if m and trainer:
            entries.append(Entry(rel, ln, '%s:%s' % (rel, trainer), 'trainer_name', m.group(1), source='party'))
    return entries


def walk_tree(tree, only=None):
    """Yields (abs path, rel path) of every file the audit reads, limited to ONLY (rel paths/globs)."""
    roots = [('data', ('.inc', '.s')), ('src', ('.c', '.h', '.json', '.party'))]
    for top, exts in roots:
        for dp, dn, fn in os.walk(os.path.join(tree, top)):
            dn.sort()
            for f in sorted(fn):
                if not f.endswith(exts):
                    continue
                if f.endswith('.json') and f != 'region_map_sections.json':
                    continue
                p = os.path.join(dp, f)
                rel = os.path.relpath(p, tree)
                if only and not any(rel == o or rel.startswith(o.rstrip('/') + '/') or fnmatch.fnmatch(rel, o)
                                    for o in only):
                    continue
                yield p, rel


def extract_tree(tree, only=None):
    files = list(walk_tree(tree, only))
    inc_all = [p for p, r in walk_tree(tree) if r.endswith(('.inc', '.s'))]
    trainer_labels = scan_trainer_text_labels(inc_all)
    entries = []
    for p, rel in files:
        try:
            if rel.endswith(('.inc', '.s')):
                entries += extract_inc(p, rel, trainer_labels)
            elif rel.endswith(('.c', '.h')):
                entries += extract_c(p, rel)
            elif rel.endswith('.json'):
                entries += extract_mapsec_json(p, rel)
            elif rel.endswith('.party'):
                entries += extract_party(p, rel)
        except UnicodeDecodeError as e:
            entries.append(Entry(rel, 0, rel + ':<file>', 'unclassified', '', source='file',
                                 note='UTF-8 decode error at byte %d' % e.start))
    return entries


# ---------------------------------------------------------------------------- checks

def finding(e, sev, code, where='', font='', value=None, limit=None, detail='', page=None, row=None):
    over = (value - limit) if isinstance(value, int) and isinstance(limit, int) else None
    return {'sev': sev, 'code': code, 'file': e.file, 'line': e.line, 'key': e.key, 'kind': e.kind,
            'where': where, 'font': font, 'value': value, 'limit': limit, 'over': over, 'page': page, 'row': row,
            'lang': 'he' if HEBREW_RE.search(e.text) else 'en', 'detail': detail, 'text': e.text[:160]}


def _rows_overflow(lines, max_lines):
    """Pages whose row count exceeds max_lines: [(page, rows)]."""
    rows = {}
    for l in lines:
        rows[l.page] = max(rows.get(l.page, 0), l.row)
    return [(p, r) for p, r in sorted(rows.items()) if r > max_lines]


# Z-moves and Max/G-Max moves replace a move only while it is used in battle: they are never in a
# move set, so only the battle move-select box and battle messages can show their names.
BATTLE_ONLY_WHERE = ('battle move select', 'battle messages')
BATTLE_ONLY = set()


def _move_const(key):
    m = re.search(r'\bMOVE_[A-Z0-9_]+', key or '')
    return m.group(0) if m else None


def battle_only_moves(tree):
    path = os.path.join(tree, 'include', 'constants', 'moves.h')
    try:
        text = open(path, encoding='utf-8').read()
    except OSError:
        return set()
    m = re.search(r'FIRST_Z_MOVE\s*=\s*MOVES_COUNT,(.*?)MOVES_COUNT_DYNAMAX', text, re.S)
    return set(re.findall(r'\b(MOVE_[A-Z0-9_]+)\s*(?:=|,)', m.group(1))) if m else set()


def check_entry(model, kinds, e):
    out = []
    if e.note:
        out.append(finding(e, 'error', 'CHARSET', detail=e.note))
        return out
    k = kinds.get(e.kind, kinds['unclassified'])
    errs = []
    battle = k.get('battle')
    units = model.encode(e.text, nbsp=bool(battle), errors=errs)
    if errs:
        out.append(finding(e, 'error', 'CHARSET', detail='; '.join(sorted(set(errs)))))
        return out
    if k.get('inc') or e.source == 'inc':
        if e.terminated is False:
            out.append(finding(e, 'error', 'TERMINATOR', detail='.string block does not end in $'))
    nbytes = model.byte_length(e.text)
    if 'buffer' in k:
        name, cap = k['buffer']
        if nbytes > cap:
            out.append(finding(e, 'error', 'BUFFER', where=name, value=nbytes, limit=cap,
                               detail='bytes after worst-case expansion'))
    if 'bytes' in k or 'exact_bytes' in k:
        plain = _plain_length(model, e.text)
        if 'bytes' in k and plain > k['bytes']:
            out.append(finding(e, 'error', 'BYTES', value=plain, limit=k['bytes'], detail='encoded name length'))
        if 'exact_bytes' in k and plain != k['exact_bytes']:
            out.append(finding(e, 'error', 'BYTES', value=plain, limit=k['exact_bytes'], detail='must be exactly'))
    if not k['checks']:
        return out
    if k.get('all_nbsp'):
        units = [tw.NBSP if u == tw.SPACE else u for u in units]
    for where, fonts, px_warn, px_err, prompt_px, max_lines in k['checks']:
        if e.kind == 'move_name' and not where.startswith(BATTLE_ONLY_WHERE) and _move_const(e.key) in BATTLE_ONLY:
            continue
        try:
            first = fonts[0]
            u = tw.battle_auto_wrap(model, units, first) if battle else units
            lines_first = model.layout(u, first)
            lines_last = model.layout(u, fonts[-1]) if len(fonts) > 1 else lines_first
        except tw.TextError as ex:
            out.append(finding(e, 'error', 'CHARSET', where=where, detail=str(ex)))
            continue
        for p, r in _rows_overflow(lines_first, max_lines):
            out.append(finding(e, 'error', 'LINES', where=where, font=first, value=r, limit=max_lines, page=p,
                               detail='rows on page %d' % p))
        for lf, ll in zip(lines_first, lines_last):
            if lf.prompt and prompt_px:
                cap_warn = cap_err = prompt_px
            else:
                cap_warn, cap_err = px_warn, px_err
            if ll.width > cap_err:
                out.append(finding(e, 'error', 'WIDTH', where=where, font=fonts[-1], value=ll.width, limit=cap_err,
                                   page=lf.page, row=lf.row,
                                   detail='prompt line' if (lf.prompt and prompt_px) else ''))
            elif ll.width > cap_warn:
                out.append(finding(e, 'warning', 'WIDTH', where=where, font=fonts[-1], value=ll.width,
                                   limit=cap_warn, page=lf.page, row=lf.row, detail='over the soft budget'))
            elif len(fonts) > 1 and lf.width > cap_warn:
                out.append(finding(e, 'warning', 'FIT', where=where, font=first, value=lf.width, limit=cap_warn,
                                   page=lf.page, row=lf.row, detail='fits only after narrowing to %s' % fonts[-1]))
    return out


def _plain_length(model, text):
    """Encoded length with placeholders counted as their own bytes (no worst-case expansion)."""
    n = 0
    for u in _raw_units(model, text):
        if u == tw.EOS:
            break
        n += 1
    return n


def _raw_units(model, text):
    saved = model.subst
    model.subst = {}
    try:
        return model.encode(text, errors=[])
    finally:
        model.subst = saved


def audit(tree, model, kinds, only=None):
    entries = extract_tree(tree, only)
    findings = []
    for e in entries:
        findings.extend(check_entry(model, kinds, e))
    return entries, findings


def worst(findings):
    """(key, code, where) -> largest overflow among the findings."""
    out = {}
    for f in findings:
        k = (f['key'], f['code'], f['where'])
        ov = f['over'] if f['over'] is not None else 0
        out[k] = max(out.get(k, -1), ov)
    return out


def apply_baseline(findings, en_findings):
    base = worst(en_findings)
    kept, suppressed = [], []
    for f in findings:
        k = (f['key'], f['code'], f['where'])
        ov = f['over'] if f['over'] is not None else 0
        if f['lang'] == 'he' and k in base and base[k] >= ov:
            g = dict(f)
            g['baseline_over'] = base[k]
            suppressed.append(g)
        else:
            kept.append(f)
    return kept, suppressed


# ---------------------------------------------------------------------------- report

def fmt_finding(f):
    loc = '%s:%d' % (f['file'], f['line'])
    what = f['code']
    if f['value'] is not None:
        what += ' %s > %s' % (f['value'], f['limit']) if f['code'] != 'BYTES' or f['detail'] != 'must be exactly' \
            else ' %s != %s' % (f['value'], f['limit'])
    pos = ''
    if f['page']:
        pos = ' p%d' % f['page'] + (' r%d' % f['row'] if f['row'] else '')
    extra = ' [%s%s]' % (f['where'], (' ' + f['font']) if f['font'] else '') if f['where'] else ''
    det = (' (%s)' % f['detail']) if f['detail'] else ''
    return '%s %-7s %s%s%s%s  %s\n        %s' % ('E' if f['sev'] == 'error' else 'w', f['kind'][:22], what, pos, extra,
                                                  det, loc, f['key'].split(':', 1)[-1] + ': ' + f['text'][:100])


def summarize(findings):
    s = {}
    for f in findings:
        k = '%s %s %s' % (f['sev'], f['code'], f['kind'])
        s[k] = s.get(k, 0) + 1
    return dict(sorted(s.items()))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('paths', nargs='*')
    ap.add_argument('--tree', default=TREE)
    ap.add_argument('--baseline')
    ap.add_argument('--fonts-tree', default=tw.FONTS_TREE)
    ap.add_argument('--charmap')
    ap.add_argument('--budgets', default=BUDGETS)
    ap.add_argument('--fill', choices=('max', 'avg'), default='max')
    ap.add_argument('--subst', action='append')
    ap.add_argument('--hebrew-widths', choices=('auto', 'table', 'draft'), default='auto')
    ap.add_argument('--json')
    ap.add_argument('--report')
    ap.add_argument('--strict', action='store_true')
    ap.add_argument('--fail-on-english', action='store_true')
    ap.add_argument('--max-report', type=int, default=400)
    a = ap.parse_args(argv)

    subst = tw._parse_subst(a.subst)
    model = tw.TextModel(a.fonts_tree, a.charmap, symtree=a.tree, fill=a.fill, subst=subst,
                         hebrew_widths=a.hebrew_widths)
    kinds = build_kinds(a.budgets)
    BATTLE_ONLY.update(battle_only_moves(a.tree))
    entries, findings = audit(a.tree, model, kinds, a.paths or None)
    suppressed = []
    if a.baseline:
        en_model = tw.TextModel(a.fonts_tree, a.charmap, symtree=a.baseline, fill=a.fill, subst=subst,
                                hebrew_widths=a.hebrew_widths)
        _, en_findings = audit(a.baseline, en_model, kinds, a.paths or None)
        findings, suppressed = apply_baseline(findings, en_findings)
    he = [f for f in findings if f['lang'] == 'he']
    en = [f for f in findings if f['lang'] == 'en']
    he_err = [f for f in he if f['sev'] == 'error' or (a.strict and f['sev'] == 'warning')]
    en_err = [f for f in en if f['sev'] == 'error']
    kinds_count = {}
    for e in entries:
        kinds_count[e.kind] = kinds_count.get(e.kind, 0) + 1
    result = {
        'meta': {'tree': a.tree, 'baseline': a.baseline, 'fonts_tree': a.fonts_tree,
                 'charmap': model.charmap.path, 'fill': a.fill, 'budgets': a.budgets,
                 'hebrew_width_source': model.fonts.source, 'paths': a.paths,
                 'strings': len(entries), 'strings_by_kind': dict(sorted(kinds_count.items())),
                 'translated_strings': sum(1 for e in entries if HEBREW_RE.search(e.text))},
        'summary': {'hebrew': summarize(he), 'english': summarize(en), 'suppressed_by_baseline': len(suppressed)},
        'findings': he, 'english_findings': en, 'suppressed': suppressed,
        'warnings': sorted(set(model.warnings)),
    }
    if a.json:
        data = json.dumps(result, ensure_ascii=False, indent=1)
        if a.json == '-':
            print(data)
        else:
            with open(a.json, 'w', encoding='utf-8') as f:
                f.write(data + '\n')
    out = []
    m = result['meta']
    out.append('audit %s: %d strings (%d translated), fonts %s, fill=%s' % (
        m['tree'], m['strings'], m['translated_strings'], m['fonts_tree'], m['fill']))
    out.append('Hebrew widths: ' + '; '.join(sorted(set(model.fonts.source.values()))))
    out.append('== translated strings: %d errors, %d warnings%s' % (
        sum(1 for f in he if f['sev'] == 'error'), sum(1 for f in he if f['sev'] == 'warning'),
        (', %d suppressed by baseline %s' % (len(suppressed), a.baseline)) if a.baseline else ''))
    for k, v in result['summary']['hebrew'].items():
        out.append('   %5d  %s' % (v, k))
    for f in sorted(he, key=lambda f: (f['sev'] != 'error', f['file'], f['line']))[:a.max_report]:
        out.append(fmt_finding(f))
    out.append('== English (untranslated) strings, baseline only: %d errors, %d warnings' % (
        len(en_err), sum(1 for f in en if f['sev'] == 'warning')))
    for k, v in result['summary']['english'].items():
        out.append('   %5d  %s' % (v, k))
    for f in sorted(en, key=lambda f: (f['sev'] != 'error', f['file'], f['line']))[:a.max_report]:
        out.append(fmt_finding(f))
    for w in result['warnings'][:20]:
        out.append('warning: ' + w)
    text = '\n'.join(out) + '\n'
    if a.report:
        os.makedirs(os.path.dirname(os.path.abspath(a.report)), exist_ok=True)
        with open(a.report, 'w', encoding='utf-8') as f:
            f.write(text)
    if a.json != '-':
        # With --report the full text goes to the file and stdout gets its '== ' summary lines.
        sys.stdout.write(''.join(l + '\n' for l in out if l.startswith('== ')) if a.report else text)
    fail = bool(he_err) or (a.fail_on_english and bool(en_err))
    return 1 if fail else 0


if __name__ == '__main__':
    sys.exit(main())
