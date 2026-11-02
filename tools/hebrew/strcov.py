#!/usr/bin/env python3
"""String coverage: which translated C strings the tours put on screen, read from a string-report build.

Usage:
  HNS_STRCOV=LOGDIR <any hns.py-based driver> ...   every hns.Emu session appends what it saw to LOGDIR
  hns.py tour STRREP.gba OUTDIR --strings LOGDIR    the same for hns.py tours
  strcov.py index  [--tree T] [--elf E] [--rom R] --out INDEX.json
                                                    every translated C string and where it lies in the ROM
  strcov.py report --index INDEX.json --logs LOGDIR [--logs LOGDIR2 ...] --json OUT.json [--md OUT.md]
                                                    map the logged ROM addresses to source strings: OUT.json
                                                    holds one record per translated string, OUT_meta.json the
                                                    per-file table, sessions and unmatched ROM text
  strcov.py runall RUNLIST.json --rom STRREP.gba --out OUTROOT --logs LOGROOT [--jobs N] [--only RE]
                                                    run driver jobs in parallel, each with HNS_STRCOV set

The string-report build is `make hns RTL_STRING_REPORT=1` (pokehns-strrep.gba, built in
build/hns-strrep). It keeps every ROM address (0x08000000-0x09FFFFFF) that reaches a string copy,
expansion or text printer in an open-addressed set in EWRAM (src/string_util.c, '#if RTL_STRING_REPORT'):

  u32 gRtlStringSet[2048]   0 = empty slot, else the address; linear probing
  u32 gRtlStringCount       entries in the set; the game refuses inserts at 3/4 full (1536)
  u32 gRtlStringLost        inserts refused because the set was full (since boot)
  u32 gRtlStringClear       set to 1 by the harness after a read: the next insert empties the set first
  u32 gRtlStringTotal       new entries since boot (a drop means the game reset and RAM was cleared)

The hook (install()) reads the set after every screenshot, before every savestate load (which
restores EWRAM), before the session closes, and between frame commands once it holds more than
DRAIN entries, then sets gRtlStringCount = 0 and gRtlStringClear = 1. Each poll appends one JSON line to LOGDIR/<session>.jsonl:
  {"tour": NAME, "shot": LABEL, "new": ["08ABCDEF", ...], "count": n, "lost": d, "reset": bool}

Mapping (index): the translated strings are the C strings audit.py extracts from src/ (and include/)
that hold Hebrew. Each is encoded with the tree's own tools/preproc and charmap.txt and located in
the ROM inside the sections of the object files that compile it (linker map + the build's .d files),
narrowed to the named symbol when audit.py's key names one that the ELF has. A copy found inside a
longer located string (a suffix) is dropped. An address maps to every located copy that contains it,
so a printer resuming mid-string counts for that string.
"""
import argparse
import bisect
import glob
import json
import os
import re
import subprocess
import sys
import tempfile
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
EMU_DIR = os.path.join(HERE, 'emu')

SLOTS = 2048
DRAIN = 1024                  # entries that trigger a read between frame commands
CHECK_FRAMES = 240            # frames between those checks
SYMS = ('gRtlStringSet', 'gRtlStringCount', 'gRtlStringLost', 'gRtlStringClear', 'gRtlStringTotal')
EOS = 0xFF


# ---------------------------------------------------------------------------- live hook

class StringReporter(object):
    """Reads and empties the string set of a live hns.Emu; appends what is new to a JSONL log."""

    def __init__(self, emu, logdir, tour=None):
        self.emu = emu
        elf = emu.elf
        try:
            self.addr = {n: elf.sym(n) for n in SYMS}
        except Exception as e:  # hns.HnsError: not a string-report build
            raise RuntimeError('%s is not an RTL_STRING_REPORT build (%s); build it with '
                               'make hns RTL_STRING_REPORT=1' % (elf.path, e))
        self.tour = tour or os.path.basename(emu.outdir.rstrip('/'))
        os.makedirs(logdir, exist_ok=True)
        tag = re.sub(r'[^A-Za-z0-9_.-]+', '_', os.path.relpath(emu.outdir, os.path.dirname(logdir)))[-90:]
        tag = tag.lstrip('._') or 'session'
        self.path = os.path.join(logdir, '%s.%d.%d.jsonl' % (tag, os.getpid(), int(time.time() * 1000) % 10 ** 9))
        self.seen = set()
        self.last_lost = 0
        self.last_total = 0
        self.lost = 0
        self.resets = 0
        self.polls = 0
        self.busy = False
        self.frames_since = 0
        self._write({'session': self.tour, 'outdir': emu.outdir, 'rom': emu.rom, 'slots': SLOTS})

    def _write(self, rec):
        with open(self.path, 'a', encoding='utf-8') as fh:
            fh.write(json.dumps(rec, ensure_ascii=False) + '\n')

    def poll(self, label, only_if_over=0):
        if self.busy:
            return
        self.busy = True
        try:
            e, a = self.emu, self.addr
            count = e.r32(a['gRtlStringCount'])
            if only_if_over and count <= only_if_over:
                return
            total = e.r32(a['gRtlStringTotal'])
            lost = e.r32(a['gRtlStringLost'])
            reset = total < self.last_total or lost < self.last_lost
            if reset:
                self.resets += 1
                self.last_lost = 0
            dlost = lost - self.last_lost
            self.last_lost, self.last_total = lost, total
            self.lost += dlost
            new = []
            if count:
                raw = e.read(a['gRtlStringSet'], SLOTS * 4)
                if e.log and e.log[-1].startswith('MEM '):
                    e.log.pop()                       # keep run.log readable
                for i in range(0, len(raw), 4):
                    v = raw[i] | raw[i + 1] << 8 | raw[i + 2] << 16 | raw[i + 3] << 24
                    if v and v not in self.seen:
                        self.seen.add(v)
                        new.append(v)
                e.w32(a['gRtlStringCount'], 0)
                e.w32(a['gRtlStringClear'], 1)
            self.polls += 1
            if new or dlost or reset:
                self._write({'tour': self.tour, 'shot': label, 'new': ['%08X' % v for v in sorted(new)],
                             'count': count, 'lost': dlost, 'reset': reset})
        finally:
            self.busy = False


def install(emu, logdir, tour=None):
    """Poll after every emu.shot, before emu.close, and between frame commands when the set fills."""
    rep = StringReporter(emu, logdir, tour)
    shot, close, frames, tap = emu.shot, emu.close, emu.frames, emu.tap
    state = {'last': '_boot'}

    def shot_and_poll(name):
        path = shot(name)
        state['last'] = name
        rep.poll(name)
        return path

    def check(n):
        rep.frames_since += n
        if rep.frames_since >= CHECK_FRAMES:
            rep.frames_since = 0
            rep.poll('after:' + state['last'], only_if_over=DRAIN)

    def frames_and_check(n, keys='-'):
        check(int(n))
        return frames(n, keys)

    def tap_and_check(keys, idle=20):
        check(3 + int(idle))
        return tap(keys, idle)

    def poll_and_close():
        try:
            if emu.p.poll() is None:
                rep.poll('after:' + state['last'])
        except Exception as ex:                  # runner gone: what was not read is lost
            rep._write({'tour': rep.tour, 'shot': '_close', 'error': str(ex)[:200]})
        rep._write({'end': True, 'polls': rep.polls, 'lost': rep.lost, 'resets': rep.resets,
                    'distinct': len(rep.seen)})
        return close()

    send = emu.send

    def send_and_poll(line):
        # a savestate load restores EWRAM: read what the set holds before it is overwritten
        if line.startswith(('sl ', 'reset')) and not rep.busy:
            rep.poll('before:' + line.split()[0] + ':' + state['last'])
        return send(line)

    emu.shot, emu.close, emu.frames, emu.tap = shot_and_poll, poll_and_close, frames_and_check, tap_and_check
    emu.send = send_and_poll
    emu.strcov = rep
    return rep


# ---------------------------------------------------------------------------- index

def _key_symbol(key):
    """audit.py key 'src/x.c:gText_Foo' / 'src/x.c:gItemsInfo[ITEM_X].name' -> leading identifier."""
    rest = key.split(':', 1)[1] if ':' in key else ''
    m = re.match(r'^([A-Za-z_]\w*)', rest)
    if not m or re.match(r'^L\d+$', m.group(1)):
        return None
    return m.group(1)


def translated_entries(tree):
    import audit
    hebrew = audit.HEBREW_RE
    out = []
    for e in audit.extract_tree(tree, only=['src']):
        if e.source in ('c', 'json', 'party') and e.text:
            out.append(e)
    out += macro_if_entries(tree)
    inc = os.path.join(tree, 'include')
    for dp, dn, fn in os.walk(inc):
        dn.sort()
        for f in sorted(fn):
            if f.endswith(('.h', '.c')):
                p = os.path.join(dp, f)
                out += [e for e in audit.extract_c(p, os.path.relpath(p, tree)) if e.text]
    for e in out:
        e.note = 'he' if hebrew.search(e.text) else 'en'
    return out


IFARG_RE = re.compile(r'\b(_|COMPOUND_STRING|COMPOUND_STRING_SIZE_LIMIT|ITEM_NAME|ITEM_PLURAL_NAME)\(\s*\n(\s*#\s*if)')


def macro_if_entries(tree):
    """Strings audit.py does not extract: a string macro whose argument is an #if/#else block
    (COMPOUND_STRING(\n#if X\n "a"),\n#else\n "b"),\n#endif). One entry per branch."""
    import audit
    from textwidth import read_text
    out = []
    for dp, dn, fn in os.walk(os.path.join(tree, 'src')):
        dn.sort()
        for f in sorted(fn):
            if not f.endswith(('.c', '.h')):
                continue
            path = os.path.join(dp, f)
            src = read_text(path)
            if not IFARG_RE.search(src):
                continue
            rel = os.path.relpath(path, tree)
            lines = src.split('\n')
            for m in IFARG_RE.finditer(src):
                ln = src.count('\n', 0, m.start(2)) + 1            # 1-based line of the #if
                branch, lits, first, k = 0, [], None, ln
                before = src[max(0, m.start() - 200):m.start()]
                fm = re.search(r'\.(\w+)\s*=\s*$', before)
                dm = list(re.finditer(r'\[\s*([A-Za-z_]\w*)\s*\]\s*=', src[max(0, m.start() - 3000):m.start()]))
                base = '%s:%s%s' % (rel, ('[%s]' % dm[-1].group(1)) if dm else 'L%d' % ln,
                                    ('.' + fm.group(1)) if fm else '')
                while k < len(lines):
                    line = lines[k - 1] if k > ln else lines[ln - 1]
                    t = line.strip()
                    if k > ln and re.match(r'#\s*(else|elif)', t) or re.match(r'#\s*endif', t):
                        if lits:
                            out.append(audit.Entry(rel, first, '%s#if%d' % (base, branch), 'unclassified',
                                                   ''.join(lits), source='c', note='if-branch'))
                        lits, first = [], None
                        branch += 1
                        if re.match(r'#\s*endif', t):
                            break
                    elif not t.startswith('#'):
                        for lit in audit.C_LIT_RE.findall(t):
                            lits.append(lit)
                            first = first or k
                    k += 1
    return out


def macro_of(tree, e, _cache={}):
    """'__' when the literal has no terminator (the __() macro), else '_'."""
    if e.source != 'c':
        return '_'
    lines = _cache.get(e.file)
    if lines is None:
        from textwidth import read_text
        lines = _cache[e.file] = read_text(os.path.join(tree, e.file)).split('\n')
    line = lines[e.line - 1] if 0 < e.line <= len(lines) else ''
    return '__' if re.search(r'(?<![A-Za-z0-9_])__\(', line) and not re.search(r'(?<![A-Za-z0-9_])_\(', line) else '_'


def encode_all(tree, texts):
    """Encode source-form strings with tools/preproc (exactly as the build does). Returns a list of
    bytes or None (the string does not encode)."""
    preproc = os.path.join(tree, 'tools', 'preproc', 'preproc')
    charmap = os.path.join(tree, 'charmap.txt')
    out = [None] * len(texts)

    def run(idx):
        with tempfile.NamedTemporaryFile('w', suffix='.c', delete=False, encoding='utf-8') as fh:
            for i in idx:
                fh.write('S%d __("%s")\n' % (i, texts[i]))
            name = fh.name
        try:
            r = subprocess.run([preproc, name, charmap], capture_output=True)
        finally:
            os.unlink(name)
        if r.returncode != 0:
            return False
        for line in r.stdout.decode('latin-1').split('\n'):
            m = re.match(r"^S(\d+) \{ ((?:0x[0-9A-F]{2}, )*)\s*\}", line)
            if m:
                out[int(m.group(1))] = bytes(int(x, 16) for x in re.findall(r'0x([0-9A-F]{2})', m.group(2)))
        return True

    def chunk(idx):
        if not idx:
            return
        if run(idx):
            return
        if len(idx) == 1:
            return
        h = len(idx) // 2
        chunk(idx[:h])
        chunk(idx[h:])

    ids = list(range(len(texts)))
    for s in range(0, len(ids), 2000):
        chunk(ids[s:s + 2000])
    return out


def map_sections(mapfile):
    """[(start, end, object)] of every input section in ROM (0x08000000-0x09FFFFFF), from the linker map."""
    rx = re.compile(r'^ (\.\S+)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+\.o)\s*$')
    rx2 = re.compile(r'^\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+\.o)\s*$')
    out, pend = [], None
    for line in open(mapfile, errors='replace'):
        m = rx.match(line)
        if m:
            a, n, obj = int(m.group(2), 16), int(m.group(3), 16), m.group(4)
        elif pend is not None and rx2.match(line):
            m = rx2.match(line)
            a, n, obj = int(m.group(1), 16), int(m.group(2), 16), m.group(3)
        else:
            m = None
        pend = line if re.match(r'^ \.\S+\s*$', line) else None
        if m and n and 0x08000000 <= a < 0x0A000000:
            out.append((a, a + n, obj))
    out.sort()
    return out


def dep_map(objdir):
    """header (tree-relative) -> set of object basenames whose .d lists it; each .c -> its own object."""
    deps = {}
    for d in glob.glob(os.path.join(objdir, 'src', '**', '*.d'), recursive=True):
        obj = os.path.splitext(os.path.relpath(d, objdir))[0] + '.o'      # src/item.o
        with open(d, errors='replace') as fh:
            text = fh.read()
        first = text.split('\n\n', 1)[0].replace('\\\n', ' ')
        for tok in first.split(':', 1)[1].split() if ':' in first else ():
            deps.setdefault(tok, set()).add(obj)
        deps.setdefault(obj[:-2] + '.c', set()).add(obj)
    return deps


def _texty(t):
    """Decoded bytes that read as Hebrew text, not graphics or code that happens to hold the bytes."""
    if '{0x' in t:
        return False
    body = re.sub(r'\{[A-Z_0-9 ]+\}', '', t).replace('$', '')
    hs = re.findall('[א-ת]', body)
    n = len(body.replace(' ', ''))
    return len(hs) >= 4 and len(set(hs)) >= 3 and n and len(hs) / n >= 0.75 and not re.search(r'(.)\1\1', body)


def build_index(tree, elf_path, rom_path, map_path, objdir):
    sys.path.insert(0, EMU_DIR)
    import hns
    elf = hns.Elf(elf_path)
    rom = open(rom_path, 'rb').read()
    entries = translated_entries(tree)
    macros = [macro_of(tree, e) for e in entries]
    enc = encode_all(tree, [e.text for e in entries])
    sections = map_sections(map_path)
    deps = dep_map(objdir)
    by_obj = {}
    for a, b, obj in sections:
        rel = os.path.relpath(obj, objdir) if obj.startswith(objdir) else obj
        rel = re.sub(r'^build/[^/]+/', '', rel)
        by_obj.setdefault(rel, []).append((a, b))
    c_objs = [o for o in by_obj if o.startswith('src/')]

    def regions_for(e):
        if e.source == 'c':
            objs = deps.get(e.file, set())
            return [r for o in sorted(objs) for r in by_obj.get(o, [])], sorted(objs)
        return [r for o in c_objs for r in by_obj[o]], ['(all C objects)']

    def find_all(needle, regions, limit=400):
        hits = []
        for a, b in regions:
            lo, hi = a - 0x08000000, b - 0x08000000
            i = rom.find(needle, lo, hi)
            while i >= 0 and len(hits) < limit:
                hits.append(0x08000000 + i)
                i = rom.find(needle, i + 1, hi)
        return hits

    recs = []
    for i, e in enumerate(entries):
        b = enc[i]
        rec = {'id': i, 'file': e.file, 'line': e.line, 'symbol': e.key, 'kind': e.kind, 'lang': e.note,
               'text': e.text, 'bytes': len(b) if b is not None else None, 'copies': [], 'how': None}
        recs.append(rec)
        if not b:
            rec['how'] = 'not encodable' if b is None else 'empty'
            continue
        regions, objs = regions_for(e)
        rec['objects'] = objs
        needle = b if macros[i] == '__' else b + bytes([EOS])
        hits = []
        # the symbol audit.py names, when the string lies inside it (a char array, or a struct with
        # an inline array); a table of pointers holds the string elsewhere in the object
        sym = _key_symbol(e.key)
        if sym and sym in elf.byname:
            symr = [(val, val + size) for val, size, typ, bind in elf.byname[sym]
                    if size and any(a <= val < bb for a, bb in regions)]
            hits = find_all(needle, symr) if symr else []
            if hits:
                rec['how'] = 'symbol'
        if not hits:
            hits = find_all(needle, regions)
            rec['how'] = 'object' if e.source == 'c' else 'global'
        if not hits and macros[i] != '__':
            hits = find_all(b, regions)                 # a size-limited array that dropped its terminator
            if hits:
                rec['how'] += '+noterm'
        rec['copies'] = [[h, h + len(b)] for h in hits]

    # drop copies that lie inside a longer located copy (a suffix of another string)
    spans = sorted((c[0], c[1], r['id']) for r in recs for c in r['copies'])
    starts = [s[0] for s in spans]
    for r in recs:
        keep = []
        for s, t in r['copies']:
            j = bisect.bisect_right(starts, s) - 1
            inside = False
            k = j
            while k >= 0 and spans[k][0] > s - 512:
                s2, t2, rid = spans[k]
                if rid != r['id'] and s2 <= s and t <= t2 and (t2 - s2) > (t - s):
                    inside = True
                    break
                k -= 1
            if not inside:
                keep.append([s, t])
            else:
                r.setdefault('suffix_copies', []).append([s, t])
        r['copies'] = keep
    # a copy found at a named symbol's own address belongs to that string only
    claimed = {}
    for r in recs:
        if r['how'] and r['how'].startswith('symbol'):
            for s, t in r['copies']:
                claimed[s] = r['id']
    for r in recs:
        if r['how'] and r['how'].startswith('symbol'):
            continue
        mine = [c for c in r['copies'] if claimed.get(c[0], r['id']) == r['id']]
        if mine and len(mine) < len(r['copies']):
            r['claimed_elsewhere'] = [c for c in r['copies'] if c not in mine]
            r['copies'] = mine
    # identical text in the same object(s): the copies cannot be told apart
    groups = {}
    for r in recs:
        for s, t in r['copies']:
            groups.setdefault(s, []).append(r['id'])
    for r in recs:
        shared = sorted({j for s, t in r['copies'] for j in groups[s] if j != r['id']})
        if shared:
            r['shares_copy_with'] = shared
    # Hebrew text in the C objects that no extracted string accounts for (strings the extractor
    # misses): every FF-terminated run with two or more Hebrew letters whose terminator ends no
    # located copy
    import textwidth as tw
    cm = tw.Charmap(os.path.join(tree, 'charmap.txt'))
    heb = set(cm.hebrew_bytes)
    ends = {t for r in recs for c in r['copies'] for t in (c[1],)}
    ends |= {t for r in recs for c in r.get('suffix_copies', []) for t in (c[1],)}
    orphans = []
    for obj in c_objs:
        for a, bb in by_obj[obj]:
            lo, hi = a - 0x08000000, bb - 0x08000000
            prev = lo
            i = rom.find(bytes([EOS]), lo, hi)
            while i >= 0:
                seg = rom[prev:i]
                if sum(1 for x in seg if x in heb) >= 4 and (0x08000000 + i) not in ends:
                    text = cm.decode(seg + bytes([EOS]))
                    m = re.search('[א-ת]', text)
                    text = text[m.start():] if m else text
                    if _texty(text):
                        orphans.append({'addr': 0x08000000 + prev, 'end': 0x08000000 + i, 'object': obj,
                                        'text': text})
                prev = i + 1
                i = rom.find(bytes([EOS]), i + 1, hi)
    return {'tree': os.path.abspath(tree), 'elf': os.path.abspath(elf_path), 'rom': os.path.abspath(rom_path),
            'records': recs, 'orphans': orphans}


# ---------------------------------------------------------------------------- report

def read_logs(logdirs):
    """[(session file, record)] of every poll line, sessions in name order."""
    out = []
    for d in logdirs:
        found = [os.path.join(dp, f) for dp, dn, fn in os.walk(d) for f in fn if f.endswith('.jsonl')]
        for p in sorted(found):
            with open(p, encoding='utf-8') as fh:
                for line in fh:
                    line = line.strip()
                    if line:
                        try:
                            out.append((p, json.loads(line)))
                        except ValueError:
                            pass
    return out


def classify_unmapped(elf, addr):
    obj = elf.objfile(addr) or ''
    obj = re.sub(r'^build/[^/]+/', '', obj)
    if obj.startswith('data/'):
        return 'script/data object (%s)' % obj
    if obj.startswith('src/'):
        return 'C object, not a located translated string (%s)' % obj
    if not obj:
        return 'no C object in the linker map (data/ scripts and other assembled data)'
    return 'other (%s)' % obj


def make_report(index, logs, elf_path=None):
    recs = index['records']
    spans = sorted((c[0], c[1], r['id']) for r in recs for c in r['copies'])
    starts = [s[0] for s in spans]
    maxlen = max([t - s for s, t, _ in spans] or [1])
    seen = {}
    unmapped = {}
    sessions = {}
    for path, rec in logs:
        ses = sessions.setdefault(path, {'tour': None, 'polls': 0, 'lost': 0, 'resets': 0, 'end': False,
                                         'outdir': None, 'distinct': 0})
        if 'session' in rec:
            ses['tour'], ses['outdir'] = rec['session'], rec.get('outdir')
            continue
        if rec.get('end'):
            ses['end'] = True
            ses['polls'], ses['distinct'] = rec.get('polls', 0), rec.get('distinct', 0)
            continue
        ses['lost'] += rec.get('lost', 0) or 0
        ses['max_count'] = max(ses.get('max_count', 0), rec.get('count', 0) or 0)
        ses['resets'] += 1 if rec.get('reset') else 0
        for h in rec.get('new', ()):
            a = int(h, 16)
            j = bisect.bisect_right(starts, a) - 1
            hit = False
            while j >= 0 and spans[j][0] > a - maxlen:
                s, t, rid = spans[j]
                if s <= a < t:
                    hit = True
                    if rid not in seen:
                        seen[rid] = {'tour': rec.get('tour'), 'shot': rec.get('shot'),
                                     'session': os.path.basename(path), 'addr': h}
                j -= 1
            if not hit:
                unmapped.setdefault(a, {'tour': rec.get('tour'), 'shot': rec.get('shot')})
    orph = sorted((o['addr'], o['end'], k) for k, o in enumerate(index.get('orphans', [])))
    ostarts = [o[0] for o in orph]
    orphan_seen = {}
    for a, where in list(unmapped.items()):
        j = bisect.bisect_right(ostarts, a) - 1
        if j >= 0 and orph[j][0] <= a < orph[j][1]:
            orphan_seen.setdefault(orph[j][2], where)
            del unmapped[a]
    out = []
    for r in recs:
        if r['lang'] != 'he':
            continue
        status = 'seen' if r['id'] in seen else ('unseen' if r['copies'] else 'not_located')
        o = {'id': r['id'], 'file': r['file'], 'line': r['line'], 'symbol': r['symbol'], 'kind': r['kind'],
             'text': r['text'], 'seen': r['id'] in seen, 'status': status,
             'first_seen': ({'tour': seen[r['id']]['tour'], 'shot': seen[r['id']]['shot']}
                            if r['id'] in seen else None),
             'rom': ['%08X' % c[0] for c in r['copies']], 'located_by': r['how']}
        if r.get('shares_copy_with'):
            o['shares_copy_with'] = r['shares_copy_with']
        out.append(o)
    unm = {}
    if elf_path and unmapped:
        sys.path.insert(0, EMU_DIR)
        import hns
        elf = hns.Elf(elf_path)
        for a in unmapped:
            k = classify_unmapped(elf, a)
            k = re.sub(r' \(.*\)$', '', k)
            unm[k] = unm.get(k, 0) + 1
    orphans = [dict(o, addr='%08X' % o['addr'], end='%08X' % o['end'], seen=k in orphan_seen,
                    first_seen=orphan_seen.get(k)) for k, o in enumerate(index.get('orphans', []))]
    return out, sessions, unmapped, unm, orphans


def by_file(out):
    files = {}
    for o in out:
        f = files.setdefault(o['file'], {'file': o['file'], 'strings': 0, 'seen': 0, 'unseen': 0, 'not_located': 0})
        f['strings'] += 1
        f[o['status']] += 1
    return sorted(files.values(), key=lambda f: (-f['strings'], f['file']))


def write_md(path, res, notes=None, max_text=70):
    out = res['strings']
    n = len(out)
    st = {k: sum(1 for o in out if o['status'] == k) for k in ('seen', 'unseen', 'not_located')}
    loc = st['seen'] + st['unseen']
    L = ['# Translated C strings drawn by the tours', '']
    L.append('| | strings |')
    L.append('| --- | ---: |')
    L.append('| translated C strings (src/, include/) | %d |' % n)
    L.append('| located in the ROM | %d |' % loc)
    L.append('| seen (copied, expanded or printed during a tour) | %d (%.1f%% of located) |' % (
        st['seen'], 100.0 * st['seen'] / max(loc, 1)))
    L.append('| unseen | %d |' % st['unseen'])
    L.append('| not located in the ROM (compiled out, unused, or not encodable) | %d |' % st['not_located'])
    L.append('| ROM addresses logged that map to no translated C string | %d |' % res.get('unmapped_pointers', 0))
    L.append('')
    ses = res.get('sessions', {})
    if ses:
        L.append('Harness: %d emulator sessions, %d polls, largest set fill %d of %d usable slots, '
                 '%d inserts refused (set full), %d EWRAM restores or resets seen between polls, '
                 '%d sessions without a closing poll.' % (
                     len(ses), sum(v.get('polls', 0) for v in ses.values()),
                     max([v.get('max_count', 0) for v in ses.values()] or [0]), SLOTS * 3 // 4,
                     sum(v.get('lost', 0) for v in ses.values()), sum(v.get('resets', 0) for v in ses.values()),
                     sum(1 for v in ses.values() if not v.get('end'))))
        L.append('')
    if notes:
        L += [open(notes, encoding='utf-8').read().rstrip(), '']
    kinds = {}
    for o in out:
        k = kinds.setdefault(o['kind'], [0, 0, 0])
        k[0] += 1
        k[1] += o['status'] == 'seen'
        k[2] += o['status'] == 'unseen'
    L += ['## By kind (audit.py classification)', '', '| kind | strings | seen | unseen |', '| --- | ---: | ---: | ---: |']
    for k, v in sorted(kinds.items(), key=lambda kv: -kv[1][0]):
        L.append('| %s | %d | %d | %d |' % (k, v[0], v[1], v[2]))
    L += ['', '## By file', '', '| file | strings | seen | unseen | not located |', '| --- | ---: | ---: | ---: | ---: |']
    for f in res['by_file']:
        L.append('| %s | %d | %d | %d | %d |' % (f['file'], f['strings'], f['seen'], f['unseen'], f['not_located']))

    def clean(t):
        t = t.replace('|', '\\|').replace('\n', ' ').replace('\\n', ' / ').replace('\\l', ' / ').replace('\\p', ' // ')
        return t if len(t) <= max_text else t[:max_text] + '…'
    orph = res.get('unmatched_rom_text') or []
    if orph:
        L += ['', '## Hebrew text in C objects that no extracted string accounts for', '',
              'Heuristic scan (FF-terminated runs that read as Hebrew, see strcov.py _texty); some rows are '
              'graphics or code bytes that happen to decode as letters. Not counted in the totals above.', '',
              '| address | object | seen | text |', '| --- | --- | --- | --- |']
        for o in orph:
            L.append('| %s | %s | %s | %s |' % (o['addr'], o['object'], 'yes' if o['seen'] else 'no', clean(o['text'])))
    for status, title in (('unseen', 'Unseen strings (located in the ROM, never logged)'),
                          ('not_located', 'Strings not located in the ROM')):
        L += ['', '## ' + title, '']
        cur = None
        for o in sorted((o for o in out if o['status'] == status), key=lambda o: (o['file'], o['line'])):
            if o['file'] != cur:
                cur = o['file']
                L += ['', '### ' + cur, '', '| line | key | text |', '| ---: | --- | --- |']
            key = o['symbol'].split(':', 1)[1] if ':' in o['symbol'] else o['symbol']
            L.append('| %d | %s | %s |' % (o['line'], clean(key)[:60], clean(o['text'])))
    with open(path, 'w', encoding='utf-8') as fh:
        fh.write('\n'.join(L) + '\n')


# ---------------------------------------------------------------------------- batch runner

def run_all(runlist, rom, outroot, logroot, jobs, only=None):
    """Run every job of RUNLIST (JSON list of {name, cmd, env, timeout}) with HNS_STRCOV set.
    cmd/env values may hold {ROM}, {OUT} (OUTROOT/name), {EMU} (tools/hebrew/emu) and $VARS."""
    import concurrent.futures
    import shlex
    jobs_list = json.load(open(runlist, encoding='utf-8'))
    if only:
        jobs_list = [j for j in jobs_list if re.search(only, j['name'])]
    os.makedirs(outroot, exist_ok=True)
    status_path = os.path.join(outroot, 'runall.json')
    try:
        status = json.load(open(status_path))
    except (OSError, ValueError):
        status = {}

    def fill(v, out):
        v = v.replace('{ROM}', os.path.abspath(rom)).replace('{OUT}', out).replace('{EMU}', EMU_DIR)
        return os.path.expandvars(v)

    def one(job):
        out = os.path.join(os.path.abspath(outroot), job['name'])
        os.makedirs(out, exist_ok=True)
        env = dict(os.environ)
        for k, v in job.get('env', {}).items():
            env[k] = fill(v, out)
        env['HNS_STRCOV'] = os.path.join(os.path.abspath(logroot), job['name'])
        env.setdefault('HNS_WORK', os.path.join(out, 'work'))
        cmd = [fill(c, out) for c in job['cmd']]
        t0 = time.time()
        with open(os.path.join(out, 'run.out'), 'w') as log:
            log.write('$ ' + ' '.join(shlex.quote(c) for c in cmd) + '\n')
            log.flush()
            try:
                r = subprocess.run(cmd, cwd=out, env=env, stdout=log, stderr=subprocess.STDOUT,
                                   timeout=job.get('timeout', 3600))
                rc, timed_out = r.returncode, False
            except subprocess.TimeoutExpired:
                rc, timed_out = None, True
        try:
            tail = open(os.path.join(out, 'run.out'), errors='replace').read().splitlines()[-6:]
        except OSError:
            tail = []
        return job['name'], {'rc': rc, 'timeout': timed_out, 'secs': round(time.time() - t0, 1), 'tail': tail}

    with concurrent.futures.ThreadPoolExecutor(max_workers=jobs) as ex:
        for name, res in ex.map(one, jobs_list):
            status[name] = res
            print('%-34s rc=%s%s %7.1fs  %s' % (name, res['rc'], ' TIMEOUT' if res['timeout'] else '',
                                                res['secs'], (res['tail'] or [''])[-1][:110]))
            sys.stdout.flush()
            with open(status_path, 'w') as fh:
                json.dump(status, fh, indent=1)
    return 0


# ---------------------------------------------------------------------------- CLI

def _default(tree, name):
    return os.path.join(tree, name)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='cmd')
    p = sub.add_parser('index')
    p.add_argument('--tree', default=os.path.dirname(os.path.dirname(HERE)))
    p.add_argument('--elf')
    p.add_argument('--rom')
    p.add_argument('--map')
    p.add_argument('--objdir', help='build folder with the .d files (default TREE/build/hns-strrep)')
    p.add_argument('--out', required=True)
    p = sub.add_parser('report')
    p.add_argument('--index', required=True)
    p.add_argument('--logs', action='append', required=True)
    p.add_argument('--json', required=True)
    p.add_argument('--elf')
    p.add_argument('--md', help='markdown report')
    p.add_argument('--notes', help='markdown inserted after the totals (method, tours, caveats)')
    p = sub.add_parser('runall')
    p.add_argument('runlist')
    p.add_argument('--rom', required=True)
    p.add_argument('--out', required=True)
    p.add_argument('--logs', required=True)
    p.add_argument('--jobs', type=int, default=8)
    p.add_argument('--only')
    a = ap.parse_args(argv)
    if a.cmd == 'runall':
        return run_all(a.runlist, a.rom, a.out, a.logs, a.jobs, a.only)
    if a.cmd == 'index':
        tree = os.path.abspath(a.tree)
        rom = a.rom or _default(tree, 'pokehns-strrep.gba')
        elf = a.elf or os.path.splitext(rom)[0] + '.elf'
        mp = a.map or os.path.splitext(rom)[0] + '.map'
        objdir = a.objdir or os.path.join(tree, 'build', 'hns-strrep')
        idx = build_index(tree, elf, rom, mp, objdir)
        with open(a.out, 'w', encoding='utf-8') as fh:
            json.dump(idx, fh, ensure_ascii=False)
        he = [r for r in idx['records'] if r['lang'] == 'he']
        print('%d C strings, %d translated; %d translated located, %d not located' % (
            len(idx['records']), len(he), sum(1 for r in he if r['copies']), sum(1 for r in he if not r['copies'])))
        return 0
    if a.cmd == 'report':
        idx = json.load(open(a.index, encoding='utf-8'))
        out, sessions, unmapped, unm, orphans = make_report(idx, read_logs(a.logs), a.elf or idx.get('elf'))
        res = {'strings': out, 'by_file': by_file(out),
               'sessions': {os.path.relpath(k, os.path.commonpath(a.logs)): v for k, v in sessions.items()},
               'unmapped_pointers': len(unmapped), 'unmapped_kinds': unm,
               'unmatched_rom_text': orphans}
        with open(a.json, 'w', encoding='utf-8') as fh:            # one record per translated string
            json.dump(out, fh, ensure_ascii=False, indent=1)
        meta = os.path.splitext(a.json)[0] + '_meta.json'
        with open(meta, 'w', encoding='utf-8') as fh:
            json.dump({k: v for k, v in res.items() if k != 'strings'}, fh, ensure_ascii=False, indent=1)
        if a.md:
            write_md(a.md, res, a.notes)
        n = len(out)
        s = sum(1 for o in out if o['seen'])
        print('%d translated C strings: %d seen, %d unseen, %d not located; %d sessions, %d unmapped pointers'
              % (n, s, sum(1 for o in out if o['status'] == 'unseen'),
                 sum(1 for o in out if o['status'] == 'not_located'), len(sessions), len(unmapped)))
        return 0
    ap.print_usage()
    return 2


if __name__ == '__main__':
    sys.exit(main())
