#!/usr/bin/env python3
"""Translation units: extract player-visible strings into JSON, and write translations back.

Translators never edit source files. They get a JSON chunk of units, fill in "he", and this tool
writes the Hebrew back into the tree, refusing anything that would change more than the string.

  units.py extract FILE... [--all-labels] > units.json      one unit per string
  units.py apply UNITS.json [UNITS.json ...] [--dry-run] [--overwrite-hebrew]
                                                              write "he" back into the tree
  units.py status FILE...                                     how many units are translated

A unit:
  {"id": "data/maps/X/scripts.inc::Label",  or  "src/foo.c@123#0"
   "file": ..., "kind": "script" | "c",
   "key":  "Label" or "ITEM_POTION.description" or the C variable name,
   "field": "description" | "speciesName" | ... (C only, the struct field it fills),
   "live": true/false, "en": "...", "he": "", "context": {...}}

Script text: the label's joined .string text, with \\n \\l \\p and the trailing $ kept exactly as in
the source. Writing back splits it into one .string line per \\n, \\l or \\p, like the English.
C text: the literal content (adjacent literals joined). Writing back keeps the macro and splits
after each \\n onto its own line when the English did.

apply refuses a unit whose tree string no longer matches its "en": English that changed, or Hebrew
that differs from its "he" (a later fix that an old chunk would undo). --overwrite-hebrew replaces
such Hebrew anyway.

The tree is HNS_TREE (this repository) unless --tree is given.
"""
import argparse, csv, json, os, re, sys

import paths
from drift import DROPPABLE_TOKENS, same_tokens  # the CI gate's token rule

TREE = paths.TREE
UPSTREAM = paths.UPSTREAM
LIVE_LABELS = paths.LIVE_LABELS
C_STRINGS = paths.C_STRINGS
GLOSSARY = paths.GLOSSARY

TOKEN_RE = re.compile(r'\{[^}]*\}')
HEBREW_RE = re.compile(r'[\u0590-\u05FF]')

# ---------------------------------------------------------------------------------------------
# Script files


LABEL_RE = re.compile(r'^([A-Za-z0-9_]+)::?\s*(@.*)?$')
STRING_RE = re.compile(r'^(\s*)\.string\s+"((?:[^"\\]|\\.)*)"\s*(@.*)?$')


def parse_script(text):
    """Yields text blocks: (label, first_line_index, last_line_index, indent, joined_text)."""
    lines = text.split('\n')
    label = None
    blocks = []
    i = 0
    seen = {}
    while i < len(lines):
        m = LABEL_RE.match(lines[i].strip())
        if m:
            label = m.group(1)
            i += 1
            continue
        m = STRING_RE.match(lines[i])
        if m:
            start = i
            indent = m.group(1)
            parts = []
            while i < len(lines):
                m2 = STRING_RE.match(lines[i])
                if not m2:
                    break
                parts.append(m2.group(2))
                i += 1
            key = label or '<nolabel>'
            n = seen.get(key, 0)
            seen[key] = n + 1
            if n:
                key = '%s#%d' % (key, n + 1)
            blocks.append((key, start, i - 1, indent, ''.join(parts)))
            continue
        i += 1
    return lines, blocks


def split_script_text(text):
    """Splits joined text after each \\n, \\l, \\p into .string payloads."""
    out, cur, i = [], '', 0
    while i < len(text):
        if text[i] == '\\' and i + 1 < len(text):
            cur += text[i:i + 2]
            if text[i + 1] in 'nlp':
                out.append(cur)
                cur = ''
            i += 2
            continue
        cur += text[i]
        i += 1
    if cur:
        out.append(cur)
    return out


def script_speakers(path):
    """label -> sorted graphics ids of the objects whose script shows it (best effort)."""
    mapdir = os.path.dirname(path)
    mj = os.path.join(mapdir, 'map.json')
    if not os.path.exists(mj):
        return {}
    try:
        data = json.load(open(mj, encoding='utf-8'))
    except Exception:
        return {}
    script_gfx = {}
    for ev in data.get('object_events', []) or []:
        s = ev.get('script')
        if s and s != '0x0':
            script_gfx.setdefault(s, set()).add(ev.get('graphics_id', '?'))
    if not script_gfx:
        return {}
    text = open(path, encoding='utf-8').read()
    lines = text.split('\n')
    cur = None
    refs = {}
    for line in lines:
        m = LABEL_RE.match(line.strip())
        if m:
            cur = m.group(1)
            continue
        if cur in script_gfx:
            for tok in re.findall(r'[A-Za-z0-9_]+_Text_[A-Za-z0-9_]+', line):
                refs.setdefault(tok, set()).update(script_gfx[cur])
    return {k: sorted(v) for k, v in refs.items()}


def load_live_labels():
    p = LIVE_LABELS
    return json.load(open(p)) if os.path.exists(p) else {}


def extract_script(path, rel, all_labels):
    text = open(path, encoding='utf-8').read()
    lines, blocks = parse_script(text)
    live = load_live_labels().get(rel)
    live_set = set(live['live']) | set(live.get('debug_only', [])) if live else None
    speakers = script_speakers(path)
    units = []
    for key, start, end, indent, joined in blocks:
        base = key.split('#')[0]
        if not re.search(r'[A-Za-z\u05d0-\u05ea]', TOKEN_RE.sub('', joined)):
            continue
        is_live = live_set is None or base in live_set
        if not is_live and not all_labels:
            continue
        ctx = {'line': start + 1, 'map': os.path.basename(os.path.dirname(rel))}
        if base in speakers:
            ctx['speaker_gfx'] = speakers[base]
        units.append({'id': '%s::%s' % (rel, key), 'file': rel, 'kind': 'script', 'key': key,
                      'live': is_live, 'en': joined, 'he': '', 'context': ctx})
    return units


def stale(u, tree_text, overwrite_hebrew):
    """Why unit u must not replace tree_text, the string now in the tree, or None."""
    if tree_text == u['en']:
        return None
    if not HEBREW_RE.search(tree_text):
        return 'changed in the tree since extraction'
    if tree_text != u['he'] and not overwrite_hebrew:
        return 'already holds different Hebrew in the tree (--overwrite-hebrew replaces it)'
    return None


def apply_script(path, rel, units, dry, overwrite_hebrew=False):
    text = open(path, encoding='utf-8').read()
    lines, blocks = parse_script(text)
    by_key = {u['key']: u for u in units}
    # Replace from the bottom so line numbers stay valid.
    changed = 0
    for key, start, end, indent, joined in reversed(blocks):
        u = by_key.get(key)
        if not u or not u.get('he'):
            continue
        why = stale(u, joined, overwrite_hebrew)
        if why:
            raise SystemExit('%s: %s %s' % (rel, key, why))
        check_unit(u)
        payloads = split_script_text(u['he'])
        new = ['%s.string "%s"' % (indent, p) for p in payloads]
        lines[start:end + 1] = new
        changed += 1
    if not dry:
        open(path, 'w', encoding='utf-8').write('\n'.join(lines))
    return changed


# ---------------------------------------------------------------------------------------------
# C files

C_MACROS = r'(?:_|__|COMPOUND_STRING|COMPOUND_STRING_SIZE_LIMIT|ITEM_NAME|ITEM_PLURAL_NAME)'
C_LIT_RE = re.compile(r'"((?:[^"\\]|\\.)*)"')
C_CALL_RE = re.compile(r'\b(' + C_MACROS + r')\((\s*)((?:"(?:[^"\\]|\\.)*"\s*)+)(,[^)]*)?\)', re.S)
DESIGNATOR_RE = re.compile(r'\[\s*([A-Z][A-Z0-9_]+)\s*\]\s*=')
FIELD_RE = re.compile(r'\.([A-Za-z0-9_]+)\s*=\s*$')
VAR_RE = re.compile(r'(?:const\s+)?u8\s+([A-Za-z0-9_]+)\s*\[[^\]]*\]\s*=\s*$')


def c_record_live(rec):
    """Whether a C_STRINGS record is in one of the inventory's two builds of the English tree
    (release and std): the build's preprocessor keeps its line (pp_*) and the build's ROM holds
    its longest plain run (rom_*). None in either field means not decided (a run too short to
    search for; a record from before pp_* was recorded) and does not rule the build out."""
    return any(rec.get('pp_' + b) is not False and rec.get('rom_' + b) is not False for b in ('release', 'std'))


def c_live_index(rel):
    """{c_key: live} for the C literals of REL that C_STRINGS records.

    C_STRINGS records each literal by its line in the English tree (UPSTREAM), and lines differ in
    this tree (Hebrew wraps differently, TEXT_RTL adds plural names). So each record is found in the
    English file by line and text, and keyed by what the literal initialises there (c_key); the
    tree's literals are looked up by the same key. Without the English file every literal of REL
    counts as live."""
    try:
        lits = json.load(open(C_STRINGS)).get(rel)
    except Exception:
        return {}
    if not lits:
        return {}
    live = {}
    for l in lits:
        live[(l['line'], l['text'])] = c_record_live(l)
    text = None
    if UPSTREAM:
        try:
            text = open(os.path.join(UPSTREAM, rel), encoding='utf-8').read()
        except OSError:
            pass
    if text is None:
        print('units: %s is not in the English tree %s; every literal of it counts as live'
              % (rel, UPSTREAM or '(none: HNS_UPSTREAM is unset and ../pokehns-en is missing)'), file=sys.stderr)
        return {}
    idx, seen = {}, {}
    rtl = rtl_only_lines(text)
    for m, line_no, joined, desig, field, var in c_literals(text):
        key = c_key(m, desig, field, var, seen, line_no in rtl)
        if (line_no, joined) in live:
            idx[key] = live[(line_no, joined)]
    return idx


def c_key(m, desig, field, var, seen, rtl_only=False):
    """A C literal's key that does not depend on its line: the variable it initialises, or else the
    designator and field, and its macro, plus n, its place among the file's literals with the same.
    SEEN counts the keys of the literals before it; call this for every literal of c_literals, in
    order. A variable's name places it, so its key leaves out the designator, which c_literals takes
    from up to 4000 characters back and which can then differ between the trees. RTL_ONLY marks a
    literal of a branch only a TEXT_RTL build compiles (rtl_only_lines): the English file has no
    such literal, so it gets a key of its own and does not move the place of the literals after it."""
    base = (None if var else desig, field, var, m.group(1)) + (('rtl',) if rtl_only else ())
    n = seen.get(base, 0)
    seen[base] = n + 1
    return base + (n,)


PP_RE = re.compile(r'^[ \t]*#[ \t]*(if|ifdef|ifndef|elif|else|endif)\b(.*)$')


def rtl_only_lines(text):
    """The line numbers (1-based) inside a branch that only a TEXT_RTL build compiles: the first
    branch of `#if TEXT_RTL` (or `#if TEXT_RTL && ...`) and the later branches of `#if !TEXT_RTL`."""
    out, stack = set(), []         # per open #if: [kind, branch]; kind 'rtl', 'not_rtl' or None
    for i, line in enumerate(text.split('\n'), 1):
        m = PP_RE.match(line)
        if m:
            d, cond = m.group(1), m.group(2).strip()
            if d in ('if', 'ifdef', 'ifndef'):
                kind = None
                if d == 'if' and re.match(r'TEXT_RTL\b(?!\s*==\s*0)', cond):
                    kind = 'rtl'
                elif d == 'if' and re.match(r'!\s*TEXT_RTL\b', cond):
                    kind = 'not_rtl'
                stack.append([kind, 0])
            elif d in ('elif', 'else') and stack:
                stack[-1][1] += 1
            elif d == 'endif' and stack:
                stack.pop()
            continue
        if any((k == 'rtl' and b == 0) or (k == 'not_rtl' and b > 0) for k, b in stack):
            out.add(i)
    return out


def non_rtl_lines(text):
    """The line numbers (1-based) that a TEXT_RTL build never compiles: the later branches of
    `#if TEXT_RTL` and the first branch of `#if !TEXT_RTL`, each with no other condition. The
    Hebrew build defines TEXT_RTL as TRUE (include/config/text.h), so a literal there is never
    shown; such a branch keeps the English line of the English build."""
    out, stack = set(), []         # per open #if: [kind, branch]; kind 'rtl', 'not_rtl' or None
    for i, line in enumerate(text.split('\n'), 1):
        m = PP_RE.match(line)
        if m:
            d, cond = m.group(1), re.sub(r'/[/*].*$', '', m.group(2)).strip()
            if d in ('if', 'ifdef', 'ifndef'):
                kind = None
                if d == 'if' and re.fullmatch(r'\(?\s*TEXT_RTL\s*\)?', cond):
                    kind = 'rtl'
                elif d == 'if' and re.fullmatch(r'!\s*\(?\s*TEXT_RTL\s*\)?', cond):
                    kind = 'not_rtl'
                stack.append([kind, 0])
            elif d in ('elif', 'else') and stack:
                stack[-1][1] += 1
            elif d == 'endif' and stack:
                stack.pop()
            continue
        if any((k == 'rtl' and b > 0) or (k == 'not_rtl' and b == 0) for k, b in stack):
            out.add(i)
    return out


def c_literals(text):
    """Yields (match, line_no, joined_text, designator, field, var)."""
    for m in C_CALL_RE.finditer(text):
        joined = ''.join(C_LIT_RE.findall(m.group(3)))
        line_no = text.count('\n', 0, m.start()) + 1
        before = text[max(0, m.start() - 4000):m.start()]
        desig = None
        for d in DESIGNATOR_RE.finditer(before):
            desig = d.group(1)
        last_line = before.split('\n')[-1]
        fm = FIELD_RE.search(last_line)
        vm = VAR_RE.search(last_line)
        yield m, line_no, joined, desig, fm.group(1) if fm else None, vm.group(1) if vm else None


def extract_c(path, rel, all_labels):
    text = open(path, encoding='utf-8').read()
    live_idx = c_live_index(rel)
    units = []
    n = 0
    seen = {}
    rtl = rtl_only_lines(text)
    not_built = non_rtl_lines(text)
    for m, line_no, joined, desig, field, var in c_literals(text):
        idx = n
        n += 1
        ckey = c_key(m, desig, field, var, seen, line_no in rtl)
        if not re.search(r'[A-Za-z\u05d0-\u05ea]', TOKEN_RE.sub('', joined)):
            continue
        # A literal the Hebrew build never compiles still takes its English place (c_key above).
        is_live = live_idx.get(ckey, True) and line_no not in not_built
        if not is_live and not all_labels:
            continue
        key = var or ('%s.%s' % (desig, field) if desig and field else (desig or field or '?'))
        units.append({'id': '%s@%d#%d' % (rel, line_no, idx), 'file': rel, 'kind': 'c', 'key': key,
                      'field': field, 'macro': m.group(1), 'live': is_live, 'en': joined, 'he': '',
                      'context': {'line': line_no}})
    return units


def c_escape_ok(s):
    # A translation must not contain a bare double quote; backslashes only as \n \l \p \\ \".
    i = 0
    while i < len(s):
        if s[i] == '"':
            return False
        if s[i] == '\\':
            if i + 1 >= len(s) or s[i + 1] not in 'nlp"\\':
                return False
            i += 2
            continue
        i += 1
    return True


def apply_c(path, rel, units, dry, overwrite_hebrew=False):
    text = open(path, encoding='utf-8').read()
    by_idx = {}
    for u in units:
        if u.get('he'):
            by_idx[int(u['id'].rsplit('#', 1)[1])] = u
    if not by_idx:
        return 0
    out, pos, n, changed = [], 0, 0, 0
    for m, line_no, joined, desig, field, var in c_literals(text):
        idx = n
        n += 1
        u = by_idx.get(idx)
        if not u:
            continue
        why = stale(u, joined, overwrite_hebrew)
        if why:
            raise SystemExit('%s: literal #%d (line %d) %s' % (rel, idx, line_no, why))
        check_unit(u)
        if not c_escape_ok(u['he']):
            raise SystemExit('%s: unit %s has a bare quote or bad escape' % (rel, u['id']))
        seg = m.group(3)
        lits = C_LIT_RE.findall(seg)
        trailing = seg[len(seg.rstrip()):]
        if len(lits) > 1:
            # Keep the English layout: one literal per line, split after each \n.
            nl_indent = re.search(r'\n([ \t]*)"', m.group(2) + seg)
            indent = nl_indent.group(1) if nl_indent else ''
            parts = split_script_text(u['he']) or ['']
            body = ('\n' + indent).join('"%s"' % p for p in parts)
        else:
            body = '"%s"' % u['he']
        new_call = '%s(%s%s%s%s)' % (m.group(1), m.group(2), body, trailing, m.group(4) or '')
        out.append(text[pos:m.start()])
        out.append(new_call)
        pos = m.end()
        changed += 1
    out.append(text[pos:])
    if not dry:
        open(path, 'w', encoding='utf-8').write(''.join(out))
    return changed


# ---------------------------------------------------------------------------------------------
# Checks shared by every unit


def check_unit(u):
    t_en = [t for t in TOKEN_RE.findall(u['en']) if t not in DROPPABLE_TOKENS]
    t_he = [t for t in TOKEN_RE.findall(u['he']) if t not in DROPPABLE_TOKENS]
    if not same_tokens(t_en, t_he):
        raise SystemExit('TOKENS %s: %s -> %s' % (u['id'], t_en, t_he))
    if u['kind'] == 'script' and u['en'].endswith('$') != u['he'].endswith('$'):
        raise SystemExit('TERMINATOR %s' % u['id'])
    if '\n' in u['he'] or '\r' in u['he']:
        raise SystemExit('RAW NEWLINE %s (use \\n)' % u['id'])


# ---------------------------------------------------------------------------------------------


def extract(files, tree, all_labels):
    units = []
    for f in files:
        rel = os.path.relpath(os.path.abspath(f), tree) if os.path.isabs(f) else f
        path = os.path.join(tree, rel)
        if rel.endswith('.inc') or rel.endswith('.s'):
            units += extract_script(path, rel, all_labels)
        elif rel.endswith('.c') or rel.endswith('.h'):
            units += extract_c(path, rel, all_labels)
        else:
            print('skip (unsupported): %s' % rel, file=sys.stderr)
    return units


def apply(unit_files, tree, dry, overwrite_hebrew=False):
    by_file = {}
    for uf in unit_files:
        doc = json.load(open(uf, encoding='utf-8'))
        for u in (doc['units'] if isinstance(doc, dict) else doc):
            by_file.setdefault(u['file'], []).append(u)
    total = 0
    for rel, us in sorted(by_file.items()):
        path = os.path.join(tree, rel)
        if us[0]['kind'] == 'script':
            n = apply_script(path, rel, us, dry, overwrite_hebrew)
        else:
            n = apply_c(path, rel, us, dry, overwrite_hebrew)
        total += n
        print('%s %d unit(s) %s' % ('would write' if dry else 'wrote', n, rel))
    return total


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('cmd', choices=['extract', 'apply', 'status'])
    ap.add_argument('paths', nargs='+')
    ap.add_argument('--tree', default=TREE)
    ap.add_argument('--all-labels', action='store_true', help='include dead labels/literals too')
    ap.add_argument('--dry-run', action='store_true')
    ap.add_argument('--overwrite-hebrew', action='store_true',
                    help='replace a tree string that already holds different Hebrew')
    a = ap.parse_args()
    if a.cmd == 'extract':
        json.dump(extract(a.paths, a.tree, a.all_labels), sys.stdout, ensure_ascii=False, indent=1)
    elif a.cmd == 'apply':
        apply(a.paths, a.tree, a.dry_run, a.overwrite_hebrew)
    else:
        us = extract(a.paths, a.tree, False)
        heb = sum(1 for u in us if re.search(r'[֐-׿]', u['en']))
        print('%d units, %d already Hebrew' % (len(us), heb))


if __name__ == '__main__':
    main()
