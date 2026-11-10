#!/usr/bin/env python3
"""Extract player-visible English strings from the Heart & Soul tree and decide
which of them the hns build can reach.

Read-only on the source tree and the built ROMs. Writes scratch JSON only.

Method
- Script text (.inc/.s under data/): one "string" = one label whose block holds
  at least one `.string`/`.braille` line with an ASCII letter outside {...}.
  Reachability is label-level: roots are script-region labels whose address
  occurs as an aligned 32-bit word anywhere in the release ROM outside the
  event_scripts.o script_data section (C code literal pools, C data tables,
  maps.o headers, map_events.o events), plus unaligned words inside the other
  script_data sections (battle scripts etc.). From the roots we follow every
  identifier that names a label, plus fall-through to the next label when a
  block does not end in end/return/goto/step_end/text/table terminator.
- C text (src/**/*.c, src/**/*.h): one "string" = one _( ), __( ),
  COMPOUND_STRING( ), COMPOUND_STRING_SIZE_LIMIT( ), ITEM_NAME( ),
  ITEM_PLURAL_NAME( ) invocation whose literal has an ASCII letter outside
  {...}. Liveness, per build (release and std): the build's preprocessor keeps
  the literal's line (cpp_lines.py: pp_release, pp_std), and the longest plain
  run (>= 6 chars) of the literal, encoded with charmap.txt, is found in that
  build's ROM outside the script region (rom_release, rom_std; None when no run
  is long enough to search for).
"""
import json, os, re, struct, subprocess, sys, glob, bisect
import numpy as np

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import invconfig as C  # noqa: E402
import cpp_lines  # noqa: E402

SRC = C.SRC
OUT = C.OUT
NM = C.NM
GCC = C.GCC
BUILDS = C.BUILDS

# ---------------------------------------------------------------- charmap
def load_charmap():
    cm = {}
    for line in open(f'{SRC}/charmap.txt', encoding='utf-8'):
        line = line.split('@', 1)[0] if not line.startswith("'@'") else line
        m = re.match(r"^'(\\.|[^'\\]|\\'')'\s*=\s*([0-9A-Fa-f ]+)", line)
        if m:
            ch = m.group(1)
            ch = {"\\'": "'", '\\n': '\n', '\\l': '\x01', '\\p': '\x02'}.get(ch, ch)
            if ch not in cm:
                cm[ch] = bytes(int(x, 16) for x in m.group(2).split())
    return cm
CHARMAP = load_charmap()

def plain_runs(s):
    """Split a game string into plain-text runs (no {..}, no escapes, no $)."""
    s = re.sub(r'\{[^}]*\}', '\0', s)
    s = re.sub(r'\\[nlp]', '\0', s)
    s = s.replace('$', '\0')
    return [r for r in s.split('\0') if r]

def encode(run):
    out = b''
    for ch in run:
        if ch == '\\':
            continue
        b = CHARMAP.get(ch)
        if b is None:
            return None
        out += b
    return out

def has_letters(s):
    s2 = re.sub(r'\{[^}]*\}', '', s)
    s2 = re.sub(r'\\[nlp]', ' ', s2)
    return re.search(r'[A-Za-z]', s2) is not None

def visible(s):
    s2 = re.sub(r'\{[^}]*\}', '', s)
    s2 = re.sub(r'\\[nlp]', ' ', s2).replace('$', '')
    return s2

# ---------------------------------------------------------------- builds
def load_build(name):
    gba, elf, mp = BUILDS[name]
    rom = open(gba, 'rb').read()
    syms = {}
    types = {}
    addr_to = {}
    out = subprocess.run([NM, elf], capture_output=True, text=True).stdout
    for l in out.splitlines():
        p = l.split()
        if len(p) == 3:
            a = int(p[0], 16)
            syms.setdefault(p[2], a)
            types.setdefault(p[2], p[1])
            addr_to.setdefault(a, []).append(p[2])
    sd = []
    for l in open(mp):
        m = re.match(r'^ script_data\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+)', l)
        if m:
            sd.append((int(m.group(1), 16), int(m.group(2), 16), m.group(3)))
    ev = [x for x in sd if x[2].endswith('event_scripts.o')][0]
    return dict(rom=rom, syms=syms, types=types, addr_to=addr_to, script_sections=sd, ev=(ev[0], ev[0] + ev[1]))

# ---------------------------------------------------------------- asm parse
LABEL_RE = re.compile(r'^\s*([A-Za-z_][A-Za-z0-9_]*)::?\s*(?:@.*|//.*)?$')
STR_RE = re.compile(r'^\s*\.(string|braille)\s+"((?:[^"\\]|\\.)*)"')
IDENT_RE = re.compile(r'\b[A-Za-z_][A-Za-z0-9_]*\b')
TERMINATORS = {'end', 'return', 'goto', 'step_end', 'end_trainer_battle'}

def parse_asm(path):
    blocks = []
    cur = dict(label=None, line=1, strings=[], refs=set(), last=None, file=path)
    for i, raw in enumerate(open(path, encoding='utf-8', errors='replace'), 1):
        line = raw.rstrip('\n')
        m = LABEL_RE.match(line)
        if m:
            blocks.append(cur)
            cur = dict(label=m.group(1), line=i, strings=[], refs=set(), last=None, file=path)
            continue
        sm = STR_RE.match(line)
        if sm:
            cur['strings'].append((i, sm.group(1), sm.group(2)))
            cur['last'] = 'string'
            continue
        code = re.sub(r'"(?:[^"\\]|\\.)*"', '', line)
        code = code.split('@', 1)[0].split('//', 1)[0]
        if code.strip().startswith('#') or re.match(r'^\s*\.(include|section|align|balign|global|globl|set|equ|macro|endm|if|ifdef|ifndef|else|endif)\b', code):
            continue
        toks = IDENT_RE.findall(code)
        if not toks:
            continue
        cur['refs'].update(toks[1:] if toks else [])
        if toks:
            cur['refs'].add(toks[0])
        first = toks[0]
        if first in TERMINATORS:
            cur['last'] = 'term'
        elif first in ('byte', '2byte', '4byte') or code.strip().startswith('.'):
            st = code.strip()
            if re.match(r'^\.(byte|2byte|4byte)\s+0\s*$', st):
                cur['last'] = 'term'
            else:
                cur['last'] = 'data'
        else:
            cur['last'] = 'code'
    blocks.append(cur)
    return blocks

def asm_files():
    files = []
    files += sorted(glob.glob(f'{SRC}/data/maps/*/scripts.inc'))
    files += sorted(glob.glob(f'{SRC}/data/scripts/*.inc'))
    files += sorted(glob.glob(f'{SRC}/data/text/*.inc'))
    files += [f'{SRC}/data/event_scripts.s']
    return files

# ---------------------------------------------------------------- C parse
C_MACROS = ['COMPOUND_STRING_SIZE_LIMIT', 'COMPOUND_STRING', 'ITEM_PLURAL_NAME', 'ITEM_NAME', '__', '_']
C_CALL_RE = re.compile(r'(?<![A-Za-z0-9_])(' + '|'.join(re.escape(m) for m in C_MACROS) + r')\s*\(')

def strip_c_comments(text):
    out = []
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == '"' or c == "'":
            q = c; j = i + 1
            while j < n and text[j] != q:
                j += 2 if text[j] == '\\' else 1
            out.append(text[i:j + 1]); i = j + 1
        elif text.startswith('//', i):
            j = text.find('\n', i); j = n if j < 0 else j
            out.append(' ' * (j - i)); i = j
        elif text.startswith('/*', i):
            j = text.find('*/', i + 2); j = n if j < 0 else j + 2
            out.append(re.sub(r'[^\n]', ' ', text[i:j])); i = j
        else:
            out.append(c); i += 1
    return ''.join(out)

def parse_c(path):
    text = strip_c_comments(open(path, encoding='utf-8', errors='replace').read())
    res = []
    for m in C_CALL_RE.finditer(text):
        j = m.end()
        # gather adjacent string literals
        parts = []
        k = j
        while True:
            while k < len(text) and text[k] in ' \t\r\n':
                k += 1
            if k < len(text) and text[k] == '"':
                e = k + 1
                while e < len(text) and text[e] != '"':
                    e += 2 if text[e] == '\\' else 1
                parts.append(text[k + 1:e]); k = e + 1
            else:
                break
        if not parts:
            continue
        s = ''.join(parts)
        line = text.count('\n', 0, m.start()) + 1
        # nearest preceding identifier assignment, for symbol-based liveness
        head = text[max(0, m.start() - 200):m.start()]
        nm = re.findall(r'\b([A-Za-z_][A-Za-z0-9_]*)\s*(?:\[[^\]]*\])*\s*=\s*$', head)
        res.append(dict(line=line, macro=m.group(1), text=s, var=nm[-1] if nm else None))
    return res

def c_files():
    fs = []
    for root, _, names in os.walk(f'{SRC}/src'):
        for nmn in names:
            if nmn.endswith(('.c', '.h')):
                fs.append(os.path.join(root, nmn))
    return sorted(fs)

# ---------------------------------------------------------------- main
SRC_IDENTS = set()
def load_src_idents():
    for f in glob.glob(f'{SRC}/src/**/*.[ch]', recursive=True) + glob.glob(f'{SRC}/include/**/*.h', recursive=True):
        SRC_IDENTS.update(re.findall(r'[A-Za-z_][A-Za-z0-9_]*', open(f, errors='replace').read()))
    for f in glob.glob(f'{SRC}/data/maps/*/map.json'):
        d = json.load(open(f))
        if d.get('game_version') != 'hns':
            continue  # not compiled into the hns build (mapjson process_groups)
        SRC_IDENTS.add(d['name'] + '_MapScripts')
        for k in ('object_events', 'coord_events', 'bg_events'):
            for e in d.get(k) or []:
                if e.get('script'):
                    SRC_IDENTS.add(e['script'])

hns_map_names = set()
def main():
    load_src_idents()
    for f in glob.glob(f'{SRC}/data/maps/*/map.json'):
        d = json.load(open(f))
        if d.get('game_version') == 'hns':
            hns_map_names.add(d['name'])
    builds = {k: load_build(k) for k in BUILDS}
    # ---------------- asm
    blocks_by_file = {}
    label_index = {}
    for f in asm_files():
        bl = parse_asm(f)
        blocks_by_file[f] = bl
        for b in bl:
            if b['label']:
                label_index.setdefault(b['label'], []).append(b)
    order = []
    for f in asm_files():
        order.extend(blocks_by_file[f])
    # fall-through successor
    succ = {}
    for f, bl in blocks_by_file.items():
        for a, b in zip(bl, bl[1:]):
            if a['label'] and b['label'] and a['last'] in ('code', None) and not a['strings']:
                succ[a['label']] = b['label']
    labels = set(label_index)

    reach_results = {}
    for bname, B in builds.items():
        rom = B['rom']; syms = B['syms']
        ev0, ev1 = B['ev']
        lab_addr = {}
        for L in labels:
            a = syms.get(L)
            if a is not None and ev0 <= a < ev1:
                lab_addr.setdefault(a, []).append(L)
        addrs = np.array(sorted(lab_addr), dtype=np.uint32)
        words = np.frombuffer(rom[:len(rom) // 4 * 4], dtype='<u4')
        idx = np.arange(len(words), dtype=np.int64) * 4 + 0x08000000
        outside = (idx < ev0) | (idx >= ev1)
        hit = np.isin(words, addrs) & outside
        roots = {}
        for pos in np.nonzero(hit)[0]:
            a = int(words[pos])
            for L in lab_addr[a]:
                roots.setdefault(L, []).append(int(pos) * 4 + 0x08000000)
        # unaligned scan inside the other script_data sections
        for (s0, sz, obj) in B['script_sections']:
            # Battle/anim/field-effect bytecode never points into event scripts; an
            # unaligned scan there only yields chance matches, so it is not used.
            continue
            seg = rom[s0 - 0x08000000: s0 - 0x08000000 + sz]
            for off in range(0, max(0, len(seg) - 3)):
                v = struct.unpack_from('<I', seg, off)[0]
                if v in lab_addr:
                    for L in lab_addr[v]:
                        roots.setdefault(L, []).append(s0 + off)
        # attribute each root reference to the containing symbol (for debug-only split)
        all_syms = sorted((a, n) for n, a in syms.items() if 0x08000000 <= a < 0x0A000000)
        sa = [a for a, _ in all_syms]
        def owner(addr):
            i = bisect.bisect_right(sa, addr) - 1
            return all_syms[i][1] if i >= 0 else None
        # Drop coincidental hits: a 32-bit word inside sound/graphics blobs can equal a
        # label address by chance (~1e-5 per word). Keep a reference only when it sits
        # in code, in a map event/script table, or in a data object that is pointer-rich.
        sym_addrs = np.array(sorted(set(sa)), dtype=np.uint32)
        isptr = np.isin(words, sym_addrs)
        BLOB = re.compile(r'^(gMon(Front|Back)Pic_|gMonIcon_|gMon(Shiny)?Palette|Cry_|DirectSoundWaveData_|ProgrammableWaveData|gObjectEventPic_|gObjectEventPal|gOverworldPalette_|gShinyOverworldPalette_|gTrainer(Front|Back)Pic_|gTilesetTiles_|gBattleAnim)')
        def extent(addr):
            i = bisect.bisect_right(sa, addr) - 1
            a = sa[i]
            j = bisect.bisect_right(sa, a)
            return a, (sa[j] if j < len(sa) else 0x0A000000)
        dropped = {}
        def ok(addr):
            o = owner(addr)
            if o is None:
                return False
            t = B['types'].get(o, '?')
            if t in 'Tt':
                return True
            if re.search(r'_(ObjectEvents|MapBGEvents|MapCoordEvents|MapScripts|MapEvents)$', o):
                return True
            if BLOB.search(o):
                dropped.setdefault(o, 0); dropped[o] += 1
                return False
            a, b = extent(addr)
            w0 = (a - 0x08000000 + 3) // 4; w1 = max(w0 + 1, (b - 0x08000000) // 4)
            dens = float(isptr[w0:w1].sum()) / (w1 - w0)
            if dens < 0.01:
                dropped.setdefault(o, 0); dropped[o] += 1
                return False
            return True
        roots = {L: [x for x in xs if ok(x)] for L, xs in roots.items()}
        # Several labels can share one address (e.g. gStdScripts_End and the first map
        # script after it). When C names one of them, only that one is the root.
        by_addr = {}
        for L in roots:
            by_addr.setdefault(syms[L], []).append(L)
        for a, Ls in by_addr.items():
            named = [L for L in Ls if L in SRC_IDENTS]
            if named and len(named) < len(Ls):
                for L in Ls:
                    if L not in named:
                        roots[L] = []
        roots = {L: xs for L, xs in roots.items() if xs}
        B['dropped_roots'] = dropped
        root_owner = {L: sorted(set(owner(x) for x in xs)) for L, xs in roots.items()}
        # binary edges: pointers stored in a label's own bytes (catches macro-internal refs)
        sorted_addrs = sorted(lab_addr)
        bin_edges = {}
        for i, a in enumerate(sorted_addrs):
            end = sorted_addrs[i + 1] if i + 1 < len(sorted_addrs) else ev1
            seg = rom[a - 0x08000000:end - 0x08000000]
            tg = set()
            for off in range(len(seg) - 3):
                v = struct.unpack_from('<I', seg, off)[0]
                if v in lab_addr:
                    tg.update(lab_addr[v])
            if tg:
                # give the bytes only to labels whose own source block has content;
                # an empty marker label (e.g. gStdScripts_End) does not own the
                # next file's first script just because they share an address
                for L in lab_addr[a]:
                    if any(b['refs'] or b['strings'] for b in label_index.get(L, [])):
                        bin_edges[L] = tg
        # traverse
        def traverse(start, parents=None):
            seen = set()
            stack = [(L, ('root', None)) for L in start]
            while stack:
                L, via = stack.pop()
                if L in seen:
                    continue
                seen.add(L)
                if parents is not None:
                    parents[L] = via
                for b in label_index.get(L, []):
                    for r in b['refs']:
                        if r in labels and r not in seen:
                            stack.append((r, ('ref', L)))
                for r in bin_edges.get(L, ()):
                    if r not in seen:
                        stack.append((r, ('bin', L)))
                s = succ.get(L)
                if s and s not in seen:
                    stack.append((s, ('fall', L)))
            return seen
        parents = {}
        reach = traverse(roots.keys(), parents)
        DEBUG_OWNERS = re.compile(r'(?i)debug|sprite_visualizer|Debug_')
        nondebug_roots = [L for L, ow in root_owner.items() if not all(DEBUG_OWNERS.search(o or '') for o in ow)]
        reach_nd = traverse(nondebug_roots)
        def cat(o):
            o = o or ''
            if DEBUG_OWNERS.search(o): return 'debug'
            if o.startswith('GetInteractedMetatileScript'): return 'metatile'
            if re.search(r'_(ObjectEvents|MapBGEvents|MapCoordEvents|MapScripts|MapEvents)$', o) or o in hns_map_names: return 'map'
            return 'code'
        via = {}
        for c in ('map', 'code', 'metatile', 'debug'):
            rs = [L for L, ow in root_owner.items() if any(cat(o) == c for o in ow)]
            for L in traverse(rs):
                via.setdefault(L, set()).add(c)
        # which live maps (by their event/script tables) reach each label
        by_map = {}
        if bname == 'release':
            map_roots = {}
            for L, ow in root_owner.items():
                for o in ow:
                    m = re.match(r'^(.*)_(ObjectEvents|MapBGEvents|MapCoordEvents|MapScripts|MapEvents)$', o or '')
                    if m and m.group(1) in hns_map_names:
                        map_roots.setdefault(m.group(1), []).append(L)
            for M, rs in map_roots.items():
                for L in traverse(rs):
                    by_map.setdefault(L, set()).add(M)
        reach_results[bname] = dict(reach=reach, reach_nd=reach_nd, roots=root_owner, parents=parents, via=via, by_map=by_map)

    asm_out = {}
    for f, bl in blocks_by_file.items():
        rel = os.path.relpath(f, SRC)
        recs = []
        for b in bl:
            if not b['strings']:
                continue
            txt = ''.join(s[2] for s in b['strings'])
            recs.append(dict(
                label=b['label'], line=b['line'], first_string_line=b['strings'][0][0],
                lines=len(b['strings']), braille=any(s[1] == 'braille' for s in b['strings']),
                text=txt, letters=has_letters(txt), chars=len(visible(txt)),
                reach_release=bool(b['label'] and b['label'] in reach_results['release']['reach']),
                reach_release_nodebug=bool(b['label'] and b['label'] in reach_results['release']['reach_nd']),
                reach_std=bool(b['label'] and b['label'] in reach_results['std']['reach']),
                via=sorted(reach_results['release']['via'].get(b['label'], ())),
                maps=sorted(reach_results['release']['by_map'].get(b['label'], ())),
            ))
        asm_out[rel] = recs
    json.dump(asm_out, open(f'{OUT}/asm_strings.json', 'w'), indent=0)
    json.dump({k: {L: v['roots'][L] for L in sorted(v['roots'])} for k, v in reach_results.items()},
              open(f'{OUT}/asm_roots.json', 'w'), indent=0)
    json.dump({k: sorted(v['reach']) for k, v in reach_results.items()}, open(f'{OUT}/asm_reach.json', 'w'))
    json.dump(reach_results['release']['parents'], open(f'{OUT}/asm_parents.json', 'w'))

    # ---------------- C
    c_out = {}
    parsed = {}
    encs = {}
    for f in c_files():
        rel = os.path.relpath(f, SRC)
        recs = parse_c(f)
        for r in recs:
            r['letters'] = has_letters(r['text'])
            r['chars'] = len(visible(r['text']))
            enc = None
            for run in sorted(plain_runs(r['text']), key=len, reverse=True):
                if len(run) >= 6:
                    e = encode(run)
                    if e is not None and len(e) >= 6:
                        enc = e; break
            r['_enc'] = enc
            if enc is not None:
                encs[enc] = None
        if recs:
            parsed[rel] = recs
    for bname in ('release', 'std'):
        B = builds[bname]
        ev0, ev1 = B['ev']
        rom = np.frombuffer(B['rom'], dtype=np.uint8)
        n = len(rom) - 8
        v = np.zeros(n, dtype=np.uint64)
        for k in range(8):
            v |= rom[k:k + n].astype(np.uint64) << np.uint64(8 * k)
        pos = np.arange(n, dtype=np.int64) + 0x08000000
        keep = (pos < ev0) | (pos >= ev1)
        v6 = v & np.uint64(0xFFFFFFFFFFFF)
        keys8 = np.array(sorted({int.from_bytes(e[:8], 'little') for e in encs if len(e) >= 8}), dtype=np.uint64)
        keys6 = np.array(sorted({int.from_bytes(e[:6], 'little') for e in encs}), dtype=np.uint64)
        hit8 = np.nonzero(np.isin(v, keys8) & keep)[0]
        hit6 = np.nonzero(np.isin(v6, keys6) & keep)[0]
        d8, d6 = {}, {}
        for p in hit8: d8.setdefault(int(v[p]), []).append(int(p))
        for p in hit6: d6.setdefault(int(v6[p]), []).append(int(p))
        raw = B['rom']
        found = {}
        for e in encs:
            cands = d8.get(int.from_bytes(e[:8], 'little'), []) if len(e) >= 8 else d6.get(int.from_bytes(e[:6], 'little'), [])
            found[e] = any(raw[p:p + len(e)] == e for p in cands)
        symnames = set(re.sub(r'\.(lto_priv|constprop|isra|part)\.\d+.*$', '', nm) for nm in B['syms'])
        for rel, recs in parsed.items():
            for r in recs:
                r[f'rom_{bname}'] = None if r['_enc'] is None else found[r['_enc']]
                if r['var']:
                    r[f'sym_{bname}'] = r['var'] in symnames
        del v, v6, pos, keep
    # A literal is in a build only if the build's preprocessor keeps its line: the ROM search alone
    # also finds the text of a branch the build leaves out when another line compiles the same run.
    for bname in ('release', 'std'):
        kept = cpp_lines.preprocess(SRC, release=bname == 'release', gcc=GCC, files=set(parsed))
        for rel, recs in parsed.items():
            text = open(f'{SRC}/{rel}', encoding='utf-8', errors='replace').read()
            verdict = cpp_lines.verdicts(text, [r['line'] for r in recs], kept.get(rel))
            for r in recs:
                r[f'pp_{bname}'] = verdict[r['line']]
    c_out = {}
    for rel, recs in parsed.items():
        for r in recs:
            r.pop('_enc', None)
        c_out[rel] = recs
    json.dump(c_out, open(f'{OUT}/c_strings.json', 'w'), indent=0)
    print('asm files', len(asm_out), 'c files', len(c_out))
    for k, v in reach_results.items():
        print(k, 'roots', len(v['roots']), 'reach', len(v['reach']), 'reach_nodebug', len(v['reach_nd']))
        print('  dropped coincidental owners:', builds[k].get('dropped_roots'))

if __name__ == '__main__':
    main()
