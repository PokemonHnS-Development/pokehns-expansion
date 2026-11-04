#!/usr/bin/env python3
"""Drift check: a translated file must differ from English only inside player-visible strings.

For each file (path relative to the repo root) it compares the translation tree with the English
reference tree and reports:
  STRUCTURE  anything outside string contents changed (script commands, labels, C code, JSON keys,
             non-text literals such as INCBIN paths)
  TOKENS     a string's {PLACEHOLDER}/{CONTROL} sequence differs from English (order matters, except
             among the battle buffers {B_BUFF1}..{B_BUFF3})
  TERMINATOR a text block gained or lost its '$'
  PAGES      the number of \\p page breaks changed (warning only)
  CHARSET    a character that the charmap cannot encode
  SHRUNK     the file is much smaller than English (truncation guard)
  LATIN      a translated string still holds a Latin word (warning; ignores tokens and known terms)
  UNTRANSLATED a string identical to English that contains English words (warning)

Usage: drift.py [--en EN_ROOT] [--tree TREE_ROOT] [--strict] [--quiet] FILE...
EN_ROOT defaults to HNS_BASELINE, TREE_ROOT to HNS_TREE (tools/hebrew/paths.py).
The last line is always 'drift: N files, F FAIL, W with warnings only', also with --quiet.
Exit status is 1 if any error (not warning) was found.
"""
import argparse, json, os, re, sys

import paths

EN_ROOT = paths.BASELINE  # engine baseline: English strings, Hebrew engine
TREE_ROOT = paths.TREE

TOKEN_RE = re.compile(r'\{[^}]*\}')
# Latin glyph-pair tokens that Hebrew text may replace with the Hebrew word (POKé, PKMN, the IDNo pair).
DROPPABLE_TOKENS = {'{POKE}', '{PKMN}', '{POKEBLOCK}', '{ID}', '{NO}'}
# Battle text buffers, each expanded from its own buffer, so Hebrew word order may move them
# relative to each other; every other token keeps the English order.
REORDERABLE_TOKENS = {'{B_BUFF1}', '{B_BUFF2}', '{B_BUFF3}'}


def same_tokens(t_en, t_tr):
    """t_tr has the tokens of t_en in the same order, except that the battle buffers may trade
    places with each other (never with another token)."""
    def slots(ts):
        return ['{B_BUFF}' if t in REORDERABLE_TOKENS else t for t in ts]

    def free(ts):
        return sorted(t for t in ts if t in REORDERABLE_TOKENS)

    return slots(t_en) == slots(t_tr) and free(t_en) == free(t_tr)


LATIN_WORD_RE = re.compile(r'[A-Za-z][A-Za-z]+')
# Latin that may legitimately stay in Hebrew text.
LATIN_OK = {
    'PP', 'HP', 'TM', 'HM', 'Lv', 'LV', 'OK', 'ID', 'No', 'PC', 'TV', 'CD', 'GBA', 'EXP', 'IV', 'IVs',
    'EV', 'EVs', 'BP', 'GTS', 'HnS', 'DS', 'Wi', 'Fi', 'vs', 'VS', 'KO', 'SP', 'ATK', 'DEF', 'SPD',
    'SPATK', 'SPDEF', 'STAB', 'UFO', 'DNA', 'XD', 'RNG', 'GO', 'ONLINE',
    # Button names, acronyms the glossary keeps in Latin (GS BALL, RKS SYSTEM), the NES console and
    # the game title HEART & SOUL.
    'START', 'SELECT', 'GS', 'RKS', 'NES', 'HEART', 'SOUL', 'Heart', 'Soul',
    # The emulator save type as its menus print it (Flash 1Mb/128K), the same name for the memory,
    # and ROM, on the flash-not-detected screen.
    'Flash', 'Mb', 'ROM',
}


def load_charmap(root):
    chars = set()
    path = os.path.join(root, 'charmap.txt')
    for line in open(path, encoding='utf-8'):
        m = re.match(r"^'(.+)'\s*=", line)
        if m:
            ch = m.group(1)
            if ch == "\\'":
                ch = "'"
            chars.add(ch)
    return chars


def split_inc(text):
    """Returns (skeleton, blocks): blocks maps label -> joined string content (in order)."""
    skeleton, blocks, order = [], {}, []
    label = None
    in_text = False
    for line in text.split('\n'):
        stripped = line.strip()
        m = re.match(r'^([A-Za-z0-9_]+)::?\s*$', stripped)
        if m:
            label = m.group(1)
            in_text = False
            skeleton.append(stripped)
            continue
        m = re.match(r'^\.string\s+"((?:[^"\\]|\\.)*)"\s*(@.*)?$', stripped)
        if m:
            key = label or '<nolabel>'
            if not in_text:
                skeleton.append('.string <text>')
                n = 1
                base = key
                while key in blocks:
                    n += 1
                    key = '%s#%d' % (base, n)
                blocks[key] = ''
                order.append(key)
                in_text = True
                current = key
            blocks[current] += m.group(1)
            continue
        in_text = False if stripped else in_text
        if stripped:
            skeleton.append(re.sub(r'\s+', ' ', stripped))
    return skeleton, [(k, blocks[k]) for k in order]


TEXT_MACROS = {'_', '__', 'COMPOUND_STRING', 'COMPOUND_STRING_SIZE_LIMIT', 'ITEM_NAME', 'ITEM_PLURAL_NAME'}
C_TOKEN_RE = re.compile(r'''
    (?P<comment>//[^\n]*|/\*.*?\*/)
  | (?P<directive>^[ \t]*\#[^\n]*(?:\\\n[^\n]*)*)
  | (?P<string>"(?:[^"\\\n]|\\.)*")
  | (?P<char>'(?:[^'\\\n]|\\.)*')
  | (?P<ident>[A-Za-z_][A-Za-z0-9_]*)
  | (?P<number>\.?[0-9][0-9A-Za-z_.]*)
  | (?P<space>[ \t\r\f\v]+|\n)
  | (?P<punct>.)
''', re.S | re.M | re.X)
C_LIT_RE = re.compile(r'"((?:[^"\\]|\\.)*)"')


def split_c(text):
    """Skeleton = the C tokens with comments dropped and each run of adjacent string literals inside
    a text macro (_(), COMPOUND_STRING(), ...) replaced by <text>; directives are tokens, so a
    description whose literals are split by #if/#else/#endif keeps its structure. Returns
    (skeleton, [(key, joined literal run)])."""
    skeleton, strings = [], []
    text_depths = []          # paren depths at which a text macro's argument list is open
    depth = 0
    pp_stack = []             # (depth, text_depths) saved at #if, restored at #else/#elif
    pending_macro = False
    run = None
    for m in C_TOKEN_RE.finditer(text):
        kind, tok = m.lastgroup, m.group()
        if kind in ('space', 'comment'):
            continue
        if kind == 'string':
            if text_depths and text_depths[-1] == depth:
                if run is None:
                    run = []
                    skeleton.append('<text>')
                run.append(C_LIT_RE.match(tok).group(1))
                continue
            skeleton.append(tok)
            continue
        if run is not None:
            strings.append(('#%d' % len(strings), ''.join(run)))
            run = None
        if kind == 'directive':
            d = re.sub(r'\s+', ' ', tok.strip())
            # A macro whose value is player-visible text: #define BINDING_TURNS "4 or 5"
            dm = re.match(r'(#\s*define\s+\w+\s+)("(?:[^"\\]|\\.)*")\s*$', d)
            if dm:
                strings.append(('#%d' % len(strings), C_LIT_RE.match(dm.group(2)).group(1)))
                d = dm.group(1) + '<text>'
            skeleton.append(d)
            word = re.match(r'#\s*(\w+)', d)
            word = word.group(1) if word else ''
            if word in ('if', 'ifdef', 'ifndef'):
                pp_stack.append((depth, list(text_depths)))
            elif word in ('elif', 'else') and pp_stack:
                depth, text_depths = pp_stack[-1][0], list(pp_stack[-1][1])
            elif word == 'endif' and pp_stack:
                pp_stack.pop()
            continue
        skeleton.append(tok)
        if kind == 'ident':
            pending_macro = tok in TEXT_MACROS
            continue
        if tok == '(':
            depth += 1
            if pending_macro:
                text_depths.append(depth)
        elif tok == ')':
            if text_depths and text_depths[-1] == depth:
                text_depths.pop()
            depth -= 1
        pending_macro = False
    if run is not None:
        strings.append(('#%d' % len(strings), ''.join(run)))
    return skeleton, strings


def split_json(text):
    data = json.loads(text)
    strings = []

    def walk(node, path):
        if isinstance(node, dict):
            return {k: walk(v, path + [k]) for k, v in node.items()}
        if isinstance(node, list):
            return [walk(v, path + [str(i)]) for i, v in enumerate(node)]
        if isinstance(node, str) and re.search(r'[A-Za-z֐-׿]', node) and ' ' in node or (
                isinstance(node, str) and path and path[-1] in TEXT_KEYS):
            strings.append(('/'.join(path), node))
            return '<text>'
        return node

    skel = walk(data, [])
    return [json.dumps(skel, sort_keys=True)], strings


TEXT_KEYS = {'name', 'description', 'pluralName', 'hebrew_name', 'text', 'title', 'desc', 'mapsec_name'}


def split_file(path, text):
    if path.endswith('.inc') or path.endswith('.s'):
        return split_inc(text)
    if path.endswith('.c') or path.endswith('.h'):
        return split_c(text)
    if path.endswith('.json'):
        return split_json(text)
    return text.split('\n'), []


def check(path, en_root, tree_root, charmap, strict):
    errors, warnings = [], []
    en_path, tr_path = os.path.join(en_root, path), os.path.join(tree_root, path)
    if not os.path.exists(en_path):
        return ['MISSING_EN %s' % path], []
    raw_tr = open(tr_path, 'rb').read()
    raw_en = open(en_path, 'rb').read()
    try:
        tr = raw_tr.decode('utf-8')
    except UnicodeDecodeError as e:
        return ['UTF8 invalid at byte %d' % e.start], []
    en = raw_en.decode('utf-8', errors='replace')
    if len(raw_en) > 2000 and len(raw_tr) < 0.6 * len(raw_en):
        errors.append('SHRUNK %d -> %d bytes' % (len(raw_en), len(raw_tr)))

    try:
        sk_en, st_en = split_file(path, en)
        sk_tr, st_tr = split_file(path, tr)
    except Exception as e:
        return ['PARSE %s' % e], []

    if sk_en != sk_tr:
        import difflib
        diff = list(difflib.unified_diff(sk_en, sk_tr, 'en', 'he', lineterm='', n=0))
        errors.append('STRUCTURE changed outside strings:\n      ' + '\n      '.join(diff[2:14]))
    if len(st_en) != len(st_tr):
        errors.append('STRUCTURE string count %d -> %d' % (len(st_en), len(st_tr)))
        return errors, warnings

    for (key_en, s_en), (key_tr, s_tr) in zip(st_en, st_tr):
        where = key_tr if path.endswith('.inc') else key_en
        if key_en != key_tr and path.endswith('.inc'):
            errors.append('STRUCTURE label order %s vs %s' % (key_en, key_tr))
            continue
        t_en = [t for t in TOKEN_RE.findall(s_en) if t not in DROPPABLE_TOKENS]
        t_tr = [t for t in TOKEN_RE.findall(s_tr) if t not in DROPPABLE_TOKENS]
        if not same_tokens(t_en, t_tr):
            errors.append('TOKENS %s: %s -> %s' % (where, t_en, t_tr))
        if path.endswith('.inc') and s_en.endswith('$') != s_tr.endswith('$'):
            errors.append('TERMINATOR %s' % where)
        if s_en.count('\\p') != s_tr.count('\\p'):
            warnings.append('PAGES %s: %d -> %d' % (where, s_en.count('\\p'), s_tr.count('\\p')))
        body = TOKEN_RE.sub('', s_tr)
        body = re.sub(r'\\[nlpN]', '', body).replace('\\"', '"').replace("\\'", "'")
        bad = sorted({c for c in body if c not in charmap and c not in '$'})
        if bad and not path.endswith('.json'):
            errors.append('CHARSET %s: %s' % (where, ''.join(bad)))
        has_heb = re.search(r'[֐-׿]', s_tr)
        words = [w for w in LATIN_WORD_RE.findall(TOKEN_RE.sub(' ', s_tr).replace('\\n', ' ').replace('\\p', ' ').replace('\\l', ' '))
                 if w not in LATIN_OK]
        if s_tr == s_en and LATIN_WORD_RE.search(TOKEN_RE.sub('', s_en)):
            warnings.append('UNTRANSLATED %s: %s' % (where, s_en[:70]))
        elif has_heb and words:
            warnings.append('LATIN %s: %s' % (where, ' '.join(words[:6])))
    if strict:
        errors += warnings
        warnings = []
    return errors, warnings


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--en', default=EN_ROOT)
    ap.add_argument('--tree', default=TREE_ROOT)
    ap.add_argument('--strict', action='store_true')
    ap.add_argument('--quiet', action='store_true', help='print only files with problems')
    ap.add_argument('files', nargs='+')
    a = ap.parse_args()
    a.en = a.en or paths.need('BASELINE', 'pass --en')
    charmap = load_charmap(a.tree)
    bad = warned = 0
    for f in a.files:
        f = os.path.relpath(os.path.abspath(f), a.tree) if os.path.isabs(f) else f
        errors, warnings = check(f, a.en, a.tree, charmap, a.strict)
        if errors:
            bad += 1
        elif warnings:
            warned += 1
        if errors or warnings or not a.quiet:
            print('%s %s' % ('FAIL' if errors else 'ok  ', f))
            for e in errors:
                print('   E', e)
            # LATIN warnings are never capped: a capped list hid whole files of them.
            latin = [w for w in warnings if w.startswith('LATIN ')]
            other = [w for w in warnings if not w.startswith('LATIN ')]
            for w in other[:40]:
                print('   w', w)
            if len(other) > 40:
                print('   w ... %d more warnings' % (len(other) - 40))
            for w in latin:
                print('   w', w)
    n = len(a.files)
    print('drift: %d file%s, %d FAIL, %d with warnings only' % (n, '' if n == 1 else 's', bad, warned))
    sys.exit(1 if bad else 0)


if __name__ == '__main__':
    main()
