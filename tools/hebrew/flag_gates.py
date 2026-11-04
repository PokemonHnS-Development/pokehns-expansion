#!/usr/bin/env python3
"""Take script labels that the build cannot show out of the live list of live_labels.json.

  flag_gates.py [--write | --check] [--elf ELF] [--tree TREE] [--labels FILE] [--inventory FILE]

The inventory builder decides liveness from a static reference graph that ignores flags and
ignores whether a file is assembled. This last step moves three kinds of label from `live` to
their own key, each with a reason:

  flag_off   * match-call contacts whose header .flag (src/pokenav_match_call_data.c, the IS_HNS
               branch) is defined as 0 in include/constants/flags_hns.h. FlagGet(0) is FALSE, so
               the contact is never enabled and none of its calls can ring.
             * TV show text: the labels of data/text/tv.inc that only src/tv.c's sTV*TextGroup
               tables name. Those tables are read only by the DoTVShow* functions, which only the
               specials DoTVShow and DoTVShowInSearchOfTrainers reach, and each show special sits
               in a label of data/scripts/tv.inc that the script reaches only through the lines
               below `goto_if_unset FLAG_SYS_TV_START` (followed jump by jump, not by line
               order), with FLAG_SYS_TV_START defined as 0.
  not_built  labels with no symbol in the ELF given with --elf: not assembled into this build.
             Without --elf the not_built lists already in the file are kept as they are.

There is no general rule that a flag defined as 0 makes its target dead: FlagGet stays FALSE, so a
FLAG_HIDE_* flag defined as 0 keeps its object visible (the Lilycove contest reporter, whose
interview lines in tv.inc stay live). Each rule checks the code shape it relies on and stops
with exit status 2 if the shape has changed, instead of guessing.

A label moved earlier whose rule no longer holds goes back to the end of `live`. In
inventory.json, the entries of the changed files get `strings_live` and `strings` recounted and
`strings_flag_off` / `strings_not_built` added.

  --write   rewrite the two files
  --check   exit 1 if either file would change (the default prints the changes only)
Defaults: TREE = HNS_TREE, FILE = tools/hebrew/data/live_labels.json and inventory.json.
Standard library only.
"""
import argparse
import json
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import paths  # noqa: E402

FLAGS_H = 'include/constants/flags_hns.h'
MATCH_CALL_C = 'src/pokenav_match_call_data.c'
MATCH_CALL_INC = 'data/text/match_call.inc'
TV_C = 'src/tv.c'
TV_TEXT = 'data/text/tv.inc'
TV_SCRIPT = 'data/scripts/tv.inc'
TV_GATE = 'goto_if_unset FLAG_SYS_TV_START,'
TV_SPECIALS = ('DoTVShow', 'DoPokeNews', 'DoTVShowInSearchOfTrainers')

REASON_MATCH_CALL = ('match-call contact whose header flag is defined as 0 in %s: FlagGet(0) is FALSE, '
                     'so the contact is never enabled' % FLAGS_H)
REASON_TV = ('TV show text: every show runs after `goto_if_unset FLAG_SYS_TV_START` in %s, and '
             'FLAG_SYS_TV_START is defined as 0' % TV_SCRIPT)
REASON_NOT_BUILT = 'no symbol in the build\'s ELF: not assembled into this build'

LABEL_RE = re.compile(r'^([A-Za-z_]\w*)::?', re.M)


class ShapeError(Exception):
    """The source no longer has the shape a rule relies on."""


def read(tree, rel):
    with open(os.path.join(tree, rel), encoding='utf-8') as f:
        return f.read()


def strip_c(text):
    """C source with comments and string/char literals blanked (line breaks kept)."""
    def blank(m):
        return re.sub(r'[^\n]', ' ', m.group(0))
    return re.sub(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', blank, text, flags=re.S)


def strip_script(text):
    """Assembler script with comments and string literals blanked."""
    text = strip_c(text)
    return re.sub(r'@[^\n]*', '', text)


def identifiers(rel, text):
    """The identifiers a file names outside its comments, string literals and (C) extern
    declarations: a declaration names a symbol without using it."""
    if rel.endswith(('.c', '.h')):
        code = re.sub(r'^\s*extern\b[^;]*;', '', strip_c(text), flags=re.M)
    else:
        code = strip_script(text)
    return set(re.findall(r'[A-Za-z_]\w*', code))


# ---------------------------------------------------------------------------- flags

def flag_values(tree):
    """{FLAG_NAME: int or None} from the #defines of the H&S flags header (None = not a plain
    number or an alias of one)."""
    raw = {}
    for line in read(tree, FLAGS_H).split('\n'):
        m = re.match(r'\s*#define\s+(FLAG_\w+)\s+(.*?)\s*(//.*|/\*.*)?$', line)
        if m:
            raw[m.group(1)] = m.group(2).strip()

    def value(name, seen=()):
        v = raw.get(name)
        if v is None or name in seen:
            return None
        v = v.strip('()').strip()
        if re.fullmatch(r'0[xX][0-9a-fA-F]+|\d+', v):
            return int(v, 0)
        if re.fullmatch(r'FLAG_\w+', v):
            return value(v, seen + (name,))
        return None
    return {n: value(n) for n in raw}


def is_zero(flag, flags, local_defines):
    if re.fullmatch(r'0[xX][0-9a-fA-F]+|\d+', flag):
        return int(flag, 0) == 0
    if flag in local_defines:
        return is_zero(local_defines[flag], flags, {})
    return flags.get(flag) == 0


# ---------------------------------------------------------------------------- match calls

def hns_branch(text):
    """The text of the `#if IS_HNS` block that holds the H&S match-call tables, up to its #else."""
    lines = text.split('\n')
    for i, line in enumerate(lines):
        if re.match(r'\s*#\s*if\s+IS_HNS\b', line):
            depth, body = 0, []
            for line2 in lines[i + 1:]:
                if re.match(r'\s*#\s*if', line2):
                    depth += 1
                elif re.match(r'\s*#\s*endif', line2):
                    if depth == 0:
                        break
                    depth -= 1
                elif re.match(r'\s*#\s*(else|elif)', line2) and depth == 0:
                    break
                body.append(line2)
            block = '\n'.join(body)
            if 'match_call_text_data_t' in block:
                return block
    raise ShapeError('%s: no `#if IS_HNS` block with match_call_text_data_t tables' % MATCH_CALL_C)


def match_call_off(tree, flags):
    """Labels of match_call.inc whose every match-call table belongs only to contacts whose header
    flag is 0. Returns (labels, {table: [headers]} of the gated tables)."""
    text = read(tree, MATCH_CALL_C)
    local = dict(re.findall(r'^\s*#define\s+(\w+)\s+(0[xX][0-9a-fA-F]+|\d+)\b', text, re.M))
    block = strip_c(hns_branch(text))
    tables = {}
    for m in re.finditer(r'match_call_text_data_t\s+(\w+)\s*\[\s*\]\s*=\s*\{(.*?)\};', block, re.S):
        tables[m.group(1)] = re.findall(r'\{\s*(MatchCall_Text_\w+)\s*,', m.group(2))
    headers = {}
    for m in re.finditer(r'struct\s+MatchCall\w+\s+(\w+)\s*=\s*\{(.*?)\};', block, re.S):
        body = m.group(2)
        flag = re.search(r'\.flag\s*=\s*(\w+)', body)
        data = re.search(r'\.textData\s*=\s*(\w+)', body)
        if data:
            if not flag:
                raise ShapeError('%s: header %s has .textData but no .flag' % (MATCH_CALL_C, m.group(1)))
            headers[m.group(1)] = (flag.group(1), data.group(1))
    if not tables or not headers:
        raise ShapeError('%s: found %d text tables and %d headers' % (MATCH_CALL_C, len(tables), len(headers)))
    users = {}
    for h, (flag, table) in headers.items():
        if table not in tables:
            raise ShapeError('%s: header %s names an unknown table %s' % (MATCH_CALL_C, h, table))
        users.setdefault(table, []).append((h, flag))
    gated = {t: [h for h, _ in us] for t, us in users.items()
             if all(is_zero(flag, flags, local) for _, flag in us)}
    in_gated, in_open = set(), set()
    for t, labels in tables.items():
        (in_gated if t in gated else in_open).update(labels)
    return in_gated - in_open, gated


# ---------------------------------------------------------------------------- TV

def top_level_owners(text, token_re):
    """{token: {names of the top-level C definitions whose text holds it}}."""
    owners = {}
    depth, name = 0, None
    for line in strip_c(text).split('\n'):
        if depth == 0 and not line.lstrip().startswith('#'):
            m = re.match(r'^(?:static\s+)?(?:const\s+)?[\w\s\*]+?\b(\w+)\s*(?:\[[^\]]*\])*\s*(?:=|\()', line)
            if m:
                name = m.group(1)
        depth += line.count('{') - line.count('}')
        for tok in set(re.findall(token_re, line)):
            owners.setdefault(tok, set()).add(name)
    return owners


def script_files(tree):
    out = []
    for root, dirs, files in os.walk(os.path.join(tree, 'data')):
        dirs.sort()
        for f in sorted(files):
            if f.endswith(('.inc', '.s')):
                out.append(os.path.relpath(os.path.join(root, f), tree))
    return out


def c_files(tree):
    out = []
    for top in ('src', 'include'):
        for root, dirs, files in os.walk(os.path.join(tree, top)):
            dirs.sort()
            for f in sorted(files):
                if f.endswith(('.c', '.h')):
                    out.append(os.path.relpath(os.path.join(root, f), tree))
    return out


def gated_labels(script, gate):
    """(gated, owner) for the lines of a script file and the index of its gate line.

    owner[i] is the label line i belongs to (None above the first label). gated holds the labels
    that run only after the gate: reached from the lines below the gate in the gate's own label,
    and not from the lines up to the gate (its own target included), from a label that the lines
    below the gate do not reach, or from anything those reach. A label is reached by a line that
    names it, and by the label above it when that label's last line is not end, return or goto."""
    lines = strip_script('\n'.join(script)).split('\n')
    owner, starts, current = [], [], None
    for i, line in enumerate(lines):
        m = LABEL_RE.match(line)
        if m:
            current = m.group(1)
            starts.append((i, current))
        owner.append(current)
    if owner[gate] is None:
        raise ShapeError('%s:%d: the gate line is above the first label' % (TV_SCRIPT, gate + 1))
    names = {n for _, n in starts}
    bounds = {n: (i + 1, starts[k + 1][0] if k + 1 < len(starts) else len(lines))
              for k, (i, n) in enumerate(starts)}
    following = {n: starts[k + 1][1] for k, (_, n) in enumerate(starts[:-1])}

    def refs(first, end):
        return {t for line in lines[first:end] for t in re.findall(r'[A-Za-z_]\w*', line) if t in names}

    def falls_through(n):
        first, end = bounds[n]
        body = [line.split() for line in lines[first:end] if line.strip()]
        return n in following and not (body and body[-1][0] in ('end', 'return', 'goto'))

    home = owner[gate]
    first, end = bounds[home]
    before = refs(first, gate + 1)

    def reach(roots):
        seen, todo = set(), list(roots)
        while todo:
            n = todo.pop()
            if n in seen:
                continue
            seen.add(n)
            if n == home:
                todo += before          # entering the gate's label runs the gate again
                continue
            todo += refs(*bounds[n])
            if falls_through(n):
                todo.append(following[n])
        return seen

    after = refs(gate + 1, end) | ({following[home]} if falls_through(home) else set())
    below = reach(after)
    open_ = reach(before | (names - below - {home}))
    return below - open_ - {home}, owner


def tv_off(tree, flags, texts, tokens):
    """Labels of tv.inc that only the TV show tables of tv.c name, after checking the gate.
    texts: {rel: text} of every script and C file; tokens: {rel: set of its identifiers}."""
    if flags.get('FLAG_SYS_TV_START') != 0:
        raise ShapeError('FLAG_SYS_TV_START is not defined as 0 in %s' % FLAGS_H)
    script = texts[TV_SCRIPT].split('\n')
    gate = next((i for i, l in enumerate(script) if l.strip().startswith(TV_GATE)), None)
    if gate is None:
        raise ShapeError('%s: no `%s` line' % (TV_SCRIPT, TV_GATE))
    gated, owner = gated_labels(script, gate)
    special_re = re.compile(r'^\s*special\s+(%s)\b' % '|'.join(TV_SPECIALS))
    for rel, text in texts.items():
        if not rel.endswith(('.inc', '.s')):
            continue
        for i, line in enumerate(text.split('\n')):
            if not special_re.match(line):
                continue
            if rel == TV_SCRIPT and (owner[i] in gated or (owner[i] == owner[gate] and i > gate)):
                continue
            raise ShapeError('%s:%d runs a TV show special outside the FLAG_SYS_TV_START gate (%s:%d)'
                             % (rel, i + 1, TV_SCRIPT, gate + 1))
    # the labels that run only after the gate (the show scripts) must not be entered from anywhere else
    for rel, toks in sorted(tokens.items()):
        hit = sorted(gated & toks) if rel != TV_SCRIPT else []
        if hit:
            raise ShapeError('%s names %s, a TV script behind the gate in %s' % (rel, hit[0], TV_SCRIPT))
    tvc = texts[TV_C]
    labels = LABEL_RE.findall(texts[TV_TEXT])
    owners = top_level_owners(tvc, r'\b[A-Za-z_]\w*\b')
    groups = top_level_owners(tvc, r'\bsTV\w*TextGroup\b')
    shows = top_level_owners(tvc, r'\bDoTVShow\w*\b')
    for g, users in groups.items():
        bad = sorted(u for u in users - {g} if not (u or '').startswith(('DoTVShow', 'sTV')))
        if bad:
            raise ShapeError('%s: %s is read outside the DoTVShow* functions, by %s' % (TV_C, g, ', '.join(bad)))
    for f, users in shows.items():
        bad = sorted(u for u in users - {f} if not (u or '').startswith('DoTVShow'))
        if bad:
            raise ShapeError('%s: %s is called outside the TV shows, by %s' % (TV_C, f, ', '.join(bad)))
    off = set()
    for L in labels:
        where = owners.get(L)
        if not where or not all(re.fullmatch(r'sTV\w*TextGroup', w or '') for w in where):
            continue
        if any(L in toks for rel, toks in tokens.items() if rel not in (TV_C, TV_TEXT)):
            continue
        off.add(L)
    return off


# ---------------------------------------------------------------------------- ELF

def elf_symbols(path):
    """Names of the NOTYPE, OBJECT and FUNC symbols of a 32-bit little-endian ELF."""
    with open(path, 'rb') as f:
        data = f.read()
    if data[:4] != b'\x7fELF' or data[4] != 1 or data[5] != 1:
        raise SystemExit('%s: not a 32-bit little-endian ELF' % path)
    shoff, = struct.unpack_from('<I', data, 0x20)
    shentsize, shnum = struct.unpack_from('<HH', data, 0x2E)
    sections = [struct.unpack_from('<IIIIIIIIII', data, shoff + i * shentsize) for i in range(shnum)]
    names = set()
    for sh in sections:
        if sh[1] != 2:                                  # SHT_SYMTAB
            continue
        off, size, link, entsize = sh[4], sh[5], sh[6], sh[9]
        stroff = sections[link][4]
        for i in range(size // entsize):
            st_name, _, _, st_info, _, _ = struct.unpack_from('<IIIBBH', data, off + i * entsize)
            if (st_info & 0xF) not in (0, 1, 2) or not st_name:
                continue
            end = data.index(b'\0', stroff + st_name)
            n = data[stroff + st_name:end].decode('latin-1')
            if n and n[0] not in '$.':
                names.add(n)
    return names


# ---------------------------------------------------------------------------- apply

def move(entry, key, reason, labels):
    """Move LABELS from entry['live'] to entry[key]; labels in entry[key] that are not in LABELS go
    back to the end of live. Returns True if the entry changed."""
    before = json.dumps(entry, sort_keys=True)
    live = entry.get('live', [])
    old = entry.get(key, [])
    back = [L for L in old if L not in labels]
    keep = [L for L in old if L in labels]
    moved = [L for L in live if L in labels]
    entry['live'] = [L for L in live if L not in labels] + back
    entry.pop(key, None)
    entry.pop(key + '_reason', None)
    if keep or moved:
        entry[key] = keep + moved
        entry[key + '_reason'] = reason
    return json.dumps(entry, sort_keys=True) != before


def ordered(entry):
    order = ['live', 'debug_only', 'dead', 'flag_off', 'flag_off_reason', 'not_built', 'not_built_reason']
    return {k: entry[k] for k in order + sorted(set(entry) - set(order)) if k in entry}


def recount(item, entry):
    live, dbg = len(entry.get('live', [])), len(entry.get('debug_only', []))
    item['strings_live'] = live
    item['strings'] = live if live else dbg
    for key in ('flag_off', 'not_built'):
        n = len(entry.get(key, []))
        if n:
            item['strings_' + key] = n
        else:
            item.pop('strings_' + key, None)


def gate(labels_doc, tree, elf=None):
    """Apply the rules to the parsed live_labels.json in place; return the files changed."""
    flags = flag_values(tree)
    texts = {}
    for rel in script_files(tree) + c_files(tree):
        try:
            texts[rel] = read(tree, rel)
        except UnicodeDecodeError:
            texts[rel] = open(os.path.join(tree, rel), encoding='utf-8', errors='replace').read()
    tokens = {rel: identifiers(rel, t) for rel, t in texts.items()}
    changed = []
    mc, _ = match_call_off(tree, flags)
    mc_inc = set(LABEL_RE.findall(texts.get(MATCH_CALL_INC, '')))
    # a label any other file names stays live (the IS_HNS tables are the only roots counted)
    mc = {L for L in mc & mc_inc
          if not any(L in toks for rel, toks in tokens.items() if rel not in (MATCH_CALL_C, MATCH_CALL_INC))}
    off = {MATCH_CALL_INC: mc, TV_TEXT: tv_off(tree, flags, texts, tokens)}
    for rel, entry in labels_doc.items():
        if rel in off or entry.get('flag_off'):
            if move(entry, 'flag_off', REASON_MATCH_CALL if rel == MATCH_CALL_INC else REASON_TV,
                    off.get(rel, set())):
                changed.append(rel)
    if elf:
        syms = elf_symbols(elf)
        for rel, entry in labels_doc.items():
            missing = {L for L in entry.get('live', []) + entry.get('not_built', []) if L not in syms}
            if move(entry, 'not_built', REASON_NOT_BUILT, missing) and rel not in changed:
                changed.append(rel)
    for rel in list(labels_doc):
        labels_doc[rel] = ordered(labels_doc[rel])
    return changed


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split('\n\n')[0])
    mode = ap.add_mutually_exclusive_group()
    mode.add_argument('--write', action='store_true', help='rewrite live_labels.json and inventory.json')
    mode.add_argument('--check', action='store_true', help='exit 1 if a file would change')
    ap.add_argument('--elf', help='the build\'s ELF; live labels with no symbol in it become not_built')
    ap.add_argument('--tree', default=paths.TREE, help='source tree (default HNS_TREE)')
    ap.add_argument('--labels', default=paths.LIVE_LABELS, help='live_labels.json to filter')
    ap.add_argument('--inventory', default=paths.INVENTORY, help='inventory.json to recount')
    a = ap.parse_args(argv)
    with open(a.labels, encoding='utf-8') as f:
        labels_text = f.read()
    with open(a.inventory, encoding='utf-8') as f:
        inv_text = f.read()
    doc = json.loads(labels_text)
    inv = json.loads(inv_text)
    try:
        changed = gate(doc, a.tree, a.elf)
    except ShapeError as e:
        sys.stderr.write('flag_gates: %s\n' % e)
        return 2
    by_file = {item['file']: item for item in inv}
    for rel, entry in doc.items():
        if rel in by_file and (rel in changed or entry.get('flag_off') or entry.get('not_built')):
            recount(by_file[rel], entry)
    new_labels = json.dumps(doc, indent=0)
    new_inv = json.dumps(inv, indent=1, ensure_ascii=False)
    diff = [p for p, old, new in ((a.labels, labels_text, new_labels), (a.inventory, inv_text, new_inv)) if old != new]
    for rel in changed:
        e = doc[rel]
        print('%-55s live %4d  flag_off %4d  not_built %4d' % (rel, len(e.get('live', [])),
                                                                 len(e.get('flag_off', [])), len(e.get('not_built', []))))
    tot = {k: sum(len(e.get(k, [])) for e in doc.values()) for k in ('live', 'flag_off', 'not_built')}
    print('total: live %(live)d, flag_off %(flag_off)d, not_built %(not_built)d' % tot)
    if a.write:
        for p, text in ((a.labels, new_labels), (a.inventory, new_inv)):
            if p in diff:
                with open(p, 'w', encoding='utf-8') as f:
                    f.write(text)
        print('wrote %s' % (', '.join(diff) if diff else 'nothing (no change)'))
        return 0
    if diff:
        print('would change: %s' % ', '.join(diff))
        return 1 if a.check else 0
    print('no change')
    return 0


if __name__ == '__main__':
    sys.exit(main())
