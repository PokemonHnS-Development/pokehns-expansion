#!/usr/bin/env python3
"""Find player-visible strings in a built Hebrew ROM that are still English.

Usage:
  rom_sweep.py [HE.gba] [--elf HE.elf] [--en EN.gba] [--en-elf EN.elf] [options]

  HE.gba            ROM to sweep (default HNS_ROM, pokehns.gba in HNS_TREE);
                    its .elf and .map are taken from next to it unless --elf is given
  --en EN.gba       English reference ROM (default HNS_EN_ROM, pokehns.gba in HNS_UPSTREAM)
  --charmap FILE    charmap used to decode (default <HE tree>/charmap.txt, else HNS_FONTS_TREE's)
  --src TREE        source tree searched for the decoded text (default: the tree of HE.gba)
  --min-words N     a run must hold at least N Latin words of 2+ letters (default 2, at least 1).
                    The default skips one-word strings (a menu item, a name, CANCEL) and strings
                    with no two such words in a row (MOM: Wait, {PLAYER}!); 1 reports them too,
                    besides every run of the default (step 2)
  --include-debug   also report strings of the R+START debug menu (src/debug.o)
  --all             also list Latin strings that are not in the English ROM (new or changed text)
  --json OUT        machine-readable output ('-' = stdout)
  --limit N         readable report lists at most N strings (default 300; JSON always has all)

Validation: `rom_sweep.py "$HNS_EN_ROM"` sweeps the English ROM against
itself, so every English text run is reported; `tests/test_rom_sweep.py` checks known strings and
the run time (< 60 s).

How it works:
  1. ROM ranges = the allocated, non-executable ROM sections of the ELF (script_data, .rodata);
     .text (code) is skipped. Inside them, input sections of sound, graphics, tileset, font and map
     layout objects (from the linker map, SKIP_OBJ) and OBJECT symbols whose names say graphics or
     sound (SKIP_SYM) are blanked.
  2. Candidates: two runs of 2+ Latin letter bytes separated by space/newline/prompt bytes
     (one C regex over the whole ROM). With --min-words 1, a run of 2+ Latin letter bytes is
     then a candidate too, in a 0xFF-delimited segment that has no two-word candidate, so a
     one-word string is checked and no run of the default moves. Each candidate is widened to its
     0xFF-terminated run; the start is pulled forward to the enclosing symbol (asm labels and C
     objects carry sizes in the ELF), past alignment padding and past any byte the charmap cannot
     decode.
  3. The run is decoded with the charmap and kept when it holds >= N Latin words, no undecodable
     bytes and mostly text characters.
  4. A Hebrew-ROM run is reported when the same bytes are a text run of the English ROM.
  5. Location: nearest symbol (arm-none-eabi-nm -n -S), object file (linker map), and the source
     file:line whose string literal contains the longest plain fragment of the decoded text.
Exit status: 0 when nothing is reported, 1 when English strings remain, 2 on usage errors.
"""
import argparse
import bisect
import json
import os
import re
import subprocess
import sys
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import textwidth as tw  # noqa: E402
import paths  # noqa: E402

HE_ROM = paths.ROM
EN_ROM = paths.EN_ROM
DEVKITARM = os.environ.get('DEVKITARM', '/opt/devkitpro/devkitARM')
NM = os.path.join(DEVKITARM, 'bin', 'arm-none-eabi-nm')
READELF = os.path.join(DEVKITARM, 'bin', 'arm-none-eabi-readelf')
ROM_BASE = 0x08000000

# Input objects whose ROM data holds no text (the linker map names them).
SKIP_OBJ = re.compile(r'(^|/)(sound/|data/sound_data\.o|src/graphics\.o|src/tilesets\.o|src/tileset_anims\.o'
                      r'|src/surfable\.o|src/fonts\.o|data/multiboot_|src/bard_music\.o|data/maps\.o'
                      r'|data/map_events\.o|data/battle_anim_scripts\.o|src/event_object_movement\.o'
                      r'|src/field_effect\.o|src/battle_transition\.o|src/m4a)')
DEBUG_OBJ = re.compile(r'(^|/)src/debug\.o$')
# OBJECT symbols that are graphics/sound blobs even inside objects that also hold text.
SKIP_SYM = re.compile(r'Gfx|Tiles|Tilemap|Palette|Pal(s|_|\d|$)|Pic(s|_|\d|$)|Icon|Image|Sprite|Anim|Footprint'
                      r'|Font|Glyph|Song|Voice|Cry|Cries|Blockdata|Metatile|Border|Bitmap|Bg([A-Z_\d]|$)'
                      r'|^(gMon|gObjectEventPic|gBattleAnim)')
TEXT_SYM = re.compile(r'Text|String|Name|Desc|Msg|Message', re.I)
GFX_SYM = re.compile(r'Gfx|Tiles|Tilemap|Palette|Pal(s|_|\d|$)')

LETTER = rb'[\xBB-\xEE]'                       # A-Z, a-z in the charmap (charmap.txt 0xBB-0xEE)
CAND_RE = re.compile(LETTER + rb'{2,}[\x00\xFE\xFA\xFB]+' + LETTER + rb'{2,}')
CAND_RE_ONE_WORD = re.compile(LETTER + rb'{2,}')
WORD_RE = re.compile(r'[A-Za-z]{2,}')
TEXTCH_RE = re.compile(r'[A-Za-z0-9 .,!?\'"…:;\-/()&+%$#*=éÉ♂♀“”‘’~\[\]]')
PLAIN_SPLIT = re.compile(r'\\[nlp]|\{[^}]*\}|\$')


# ---------------------------------------------------------------------------- ELF / map

def rom_sections(elf):
    out = subprocess.run([READELF, '-SW', elf], capture_output=True, text=True, check=True).stdout
    secs = []
    for line in out.splitlines():
        m = re.match(r'^\s*\[\s*\d+\]\s+(\S+)\s+(\S+)\s+([0-9a-f]{8})\s+([0-9a-f]+)\s+([0-9a-f]+)\s+\S+\s+(\S*)', line)
        if not m:
            continue
        name, typ, addr, off, size, flags = m.group(1), m.group(2), int(m.group(3), 16), int(m.group(4), 16), \
            int(m.group(5), 16), m.group(6)
        if typ == 'PROGBITS' and 'A' in flags and ROM_BASE <= addr < 0x0A000000:
            secs.append({'name': name, 'addr': addr, 'size': size, 'exec': 'X' in flags})
    return secs


def map_objects(mapfile):
    """[(start, end, section, object)] of every ROM input section in the linker map."""
    out = []
    if not mapfile or not os.path.exists(mapfile):
        return out
    rx1 = re.compile(r'^ (\S+)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+)\s*$')
    rx2 = re.compile(r'^\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+\.o)\s*$')
    pend = None
    for line in open(mapfile, errors='replace'):
        m = rx1.match(line)
        if m:
            sec, a, n, obj = m.group(1), int(m.group(2), 16), int(m.group(3), 16), m.group(4)
        else:
            m = rx2.match(line) if pend else None
            if not m:
                pend = line.strip() if re.match(r'^ \S+\s*$', line) else None
                continue
            sec, a, n, obj = pend, int(m.group(1), 16), int(m.group(2), 16), m.group(3)
        pend = None
        if a >= ROM_BASE and n and obj.endswith('.o'):
            out.append((a, a + n, sec, obj))
    out.sort()
    return out


class Symbols(object):
    """ROM symbols from `nm -n -S`, or from a list of (addr, size, kind, name) (tests)."""

    def __init__(self, elf=None, table=None):
        self.addr, self.size, self.name, self.kind = [], [], [], []
        if table is not None:
            for a, s, k, n in sorted(table):
                self.addr.append(a)
                self.size.append(s)
                self.kind.append(k)
                self.name.append(n)
            return
        out = subprocess.run([NM, '-n', '-S', '--defined-only', elf], capture_output=True, text=True,
                             check=True).stdout
        for line in out.splitlines():
            f = line.split()
            if len(f) == 4:
                a, s, k, n = int(f[0], 16), int(f[1], 16), f[2], f[3]
            elif len(f) == 3:
                a, s, k, n = int(f[0], 16), 0, f[1], f[2]
            else:
                continue
            if a < ROM_BASE or a >= 0x0A000000 or n.startswith('$') or n.startswith('.'):
                continue
            self.addr.append(a & ~1 if k in 'Tt' else a)
            self.size.append(s)
            self.name.append(n)
            self.kind.append(k)

    def at_or_before(self, addr):
        return bisect.bisect_right(self.addr, addr) - 1

    def where(self, addr):
        i = self.at_or_before(addr)
        if i < 0:
            return '?'
        off = addr - self.addr[i]
        past = ' (past end)' if self.size[i] and off >= self.size[i] else ''
        return ('%s+0x%X%s' % (self.name[i], off, past)) if off else self.name[i]


# ---------------------------------------------------------------------------- extraction

class RomText(object):
    """Text runs of one ROM: {bytes: addr} plus per-run records."""

    def __init__(self, rom, elf=None, mapfile=None, charmap=None, min_words=2, include_debug=False,
                 data=None, sections=None, objs=None, syms=None):
        """DATA/SECTIONS/OBJS/SYMS replace what would be read from ROM/ELF/map (tests)."""
        if min_words < 1:
            raise ValueError('min_words must be at least 1, not %r' % min_words)
        self.rom = rom
        self.elf = elf or (os.path.splitext(rom)[0] + '.elf' if rom else None)
        self.mapfile = mapfile or (os.path.splitext(self.elf)[0] + '.map' if self.elf else None)
        self.charmap = charmap
        self.min_words = min_words
        self.include_debug = include_debug
        if data is None:
            with open(rom, 'rb') as fh:
                data = fh.read()
        self.data = data
        self.sections = sections if sections is not None else rom_sections(self.elf)
        self.syms = syms if syms is not None else Symbols(self.elf)
        self.objs = sorted(objs) if objs is not None else map_objects(self.mapfile)
        self._okeys = [o[0] for o in self.objs]
        self.runs = []          # dicts: addr, len, raw (bytes incl. FF), text
        self.by_bytes = {}
        self.stats = {}

    def obj_at(self, addr):
        i = bisect.bisect_right(self._okeys, addr) - 1
        if i >= 0 and addr < self.objs[i][1]:
            return self.objs[i][3]
        return None

    def build_buffer(self):
        """ROM bytes with code, excluded objects and excluded symbols overwritten by 0xFF."""
        buf = bytearray(b'\xff' * len(self.data))
        scanned = 0
        for s in self.sections:
            if s['exec']:
                continue
            lo, hi = s['addr'] - ROM_BASE, min(s['addr'] - ROM_BASE + s['size'], len(self.data))
            buf[lo:hi] = self.data[lo:hi]
            scanned += hi - lo
        blank = 0
        for a, e, sec, obj in self.objs:
            if SKIP_OBJ.search(obj) or (not self.include_debug and DEBUG_OBJ.search(obj)):
                lo, hi = a - ROM_BASE, min(e - ROM_BASE, len(buf))
                if lo < hi:
                    buf[lo:hi] = b'\xff' * (hi - lo)
                    blank += hi - lo
        sy = self.syms
        for i, n in enumerate(sy.name):
            if sy.size[i] >= 32 and sy.kind[i] in 'rRdD' and SKIP_SYM.search(n) and \
                    (not TEXT_SYM.search(n) or GFX_SYM.search(n)):
                lo, hi = sy.addr[i] - ROM_BASE, min(sy.addr[i] - ROM_BASE + sy.size[i], len(buf))
                if lo < hi:
                    buf[lo:hi] = b'\xff' * (hi - lo)
                    blank += hi - lo
        self.stats.update(scanned_bytes=scanned, blanked_bytes=blank)
        return bytes(buf)

    def run_start(self, buf, seg_start, hit):
        """Where the text that contains HIT begins (>= seg_start)."""
        start = seg_start
        sy = self.syms
        i = sy.at_or_before(ROM_BASE + hit)
        if i >= 0:
            a, s = sy.addr[i] - ROM_BASE, sy.size[i]
            if s == 0 or hit < a + s:
                cand = a
            else:
                cand = a + s
            if cand > start:
                start = cand
        while start < hit and buf[start] == 0x00 and start % 4:
            start += 1                                  # alignment padding after the previous string
        return start

    def trim_prefix(self, buf, start, word):
        """Moves START past struct bytes that precede a string: past the last byte the charmap
        cannot decode, the last non-text character, or the last double space before WORD (where the
        first candidate match starts). Control codes are kept: a string may begin with {PLAYER} etc."""
        dec = self.charmap.decode_char
        cut, k, prev_space = start, start, False
        while k < word:
            b = buf[k]
            if b in (tw.CTRL, tw.PLACEHOLDER, tw.EXTRA_SYMBOL, tw.KEYPAD_ICON, tw.DYNAMIC):
                k += 2 + (tw.CTRL_ARGS.get(buf[k + 1], 0) if b == tw.CTRL and k + 1 < len(buf) else 0)
                prev_space = False
                continue
            if b in (tw.NEWLINE, tw.PROMPT_SCROLL, tw.PROMPT_CLEAR):
                prev_space = False
            elif b not in dec or not TEXTCH_RE.match(dec[b]):
                cut = k + 1
                prev_space = False
            elif b == tw.SPACE:
                if prev_space:
                    cut = k + 1
                prev_space = True
            else:
                prev_space = False
            k += 1
        if cut > start:
            while cut < word and buf[cut] == tw.SPACE:
                cut += 1
        return cut

    def candidates(self, buf):
        """Two-word matches; with min_words 1, then one-word matches. scan() takes the first match of
        each 0xFF-delimited segment, so a segment with a two-word match starts its run where the
        default does, and one-word matches only add segments that have none."""
        for m in CAND_RE.finditer(buf):
            yield m
        if self.min_words == 1:
            for m in CAND_RE_ONE_WORD.finditer(buf):
                yield m

    def scan(self):
        t0 = time.time()
        buf = self.build_buffer()
        seen = set()
        cands = 0
        for m in self.candidates(buf):
            seg_start = buf.rfind(b'\xff', 0, m.start()) + 1
            if seg_start in seen:
                continue
            seen.add(seg_start)
            cands += 1
            end = buf.find(b'\xff', m.end())
            if end < 0:
                continue
            start = self.run_start(buf, seg_start, m.start())
            start = self.trim_prefix(buf, start, m.start())
            raw = bytes(buf[start:end + 1])
            if len(raw) > 2048:
                continue
            text = self.charmap.decode(raw)
            if not self.is_text(text):
                continue
            self.runs.append({'addr': ROM_BASE + start, 'len': len(raw), 'raw': raw, 'text': text})
        self.runs.sort(key=lambda r: r['addr'])
        for rec in self.runs:
            self.by_bytes.setdefault(rec['raw'], rec['addr'])
        self.stats.update(candidates=cands, runs=len(self.runs), secs=round(time.time() - t0, 1))
        return self

    def is_text(self, text):
        if '{0x' in text:
            return False
        plain = PLAIN_SPLIT.sub(' ', text)
        if len(WORD_RE.findall(plain)) < self.min_words:
            return False
        vis = plain.replace(' ', '')
        if not vis:
            return False
        good = len(TEXTCH_RE.findall(vis))
        return good >= 0.9 * len(vis)


# ---------------------------------------------------------------------------- source search

class SourceIndex(object):
    """Plain fragments of every string literal in a tree -> [(file, line)]."""
    EXTS = ('.inc', '.s', '.c', '.h', '.json', '.party', '.pory')
    LIT = re.compile(r'"((?:[^"\\\n]|\\.)*)"')

    def __init__(self, tree, charmap=None):
        self.tree = tree
        self.idx = {}
        self.norm = normalizer(charmap)
        if not tree or not os.path.isdir(tree):
            return
        for top in ('data', 'src'):
            for dp, dn, fn in os.walk(os.path.join(tree, top)):
                if '/graphics' in dp or '/sound' in dp:
                    continue
                for f in fn:
                    if not f.endswith(self.EXTS):
                        continue
                    p = os.path.join(dp, f)
                    rel = os.path.relpath(p, tree)
                    try:
                        with open(p, encoding='utf-8') as fh:
                            lines = fh.read().split('\n')
                    except (UnicodeDecodeError, OSError):
                        continue
                    for ln, line in enumerate(lines, 1):
                        if '"' not in line:
                            continue
                        lits = self.LIT.findall(line) if not f.endswith('.party') else [line]
                        for lit in lits:
                            for frag in fragments(self.norm(lit)):
                                self.idx.setdefault(frag, [])
                                if len(self.idx[frag]) < 4:
                                    self.idx[frag].append('%s:%d' % (rel, ln))

    def locate(self, text):
        for frag in sorted(fragments(self.norm(text)), key=len, reverse=True):
            if frag in self.idx:
                return self.idx[frag]
        return []


def normalizer(charmap):
    """Maps every character to the one the charmap decodes its byte to (' and ’ share a byte)."""
    if charmap is None:
        return lambda s: s
    table = {}
    for ch, seq in charmap.chars.items():
        if len(seq) == 1 and seq[0] in charmap.decode_char and len(ch) == 1:
            table[ord(ch)] = charmap.decode_char[seq[0]]
    return lambda s: s.translate(table)


def fragments(s):
    out = []
    for part in PLAIN_SPLIT.split(s):
        part = part.strip()
        if len(part) >= 6 and WORD_RE.search(part):
            out.append(part)
    return out


# ---------------------------------------------------------------------------- main

def default_charmap(rom):
    for c in (os.path.join(os.path.dirname(os.path.abspath(rom)), 'charmap.txt'),
              os.path.join(tw.FONTS_TREE, 'charmap.txt')):
        if os.path.exists(c):
            return c
    raise SystemExit('rom_sweep: no charmap.txt next to %s; pass --charmap' % rom)


def compare(he, en, index, all_latin=False):
    """Runs of HE whose bytes are also a text run of EN (found), and with all_latin the others."""
    found, other = [], []
    for r in he.runs:
        en_addr = en.by_bytes.get(r['raw'])
        if en_addr is None and not all_latin:
            continue
        rec = {'addr': '%08X' % r['addr'], 'symbol': he.syms.where(r['addr']), 'object': he.obj_at(r['addr']),
               'en_addr': '%08X' % en_addr if en_addr is not None else None,
               'en_symbol': en.syms.where(en_addr) if en_addr is not None else None,
               'bytes': r['len'], 'text': r['text'], 'source': index.locate(r['text']) if index else []}
        (found if en_addr is not None else other).append(rec)
    return found, other


def sweep(he_rom, en_rom, he_elf=None, en_elf=None, charmap=None, src=None, min_words=2,
          include_debug=False, all_latin=False):
    cm = tw.Charmap(charmap or default_charmap(he_rom))
    t0 = time.time()
    he = RomText(he_rom, he_elf, None, cm, min_words, include_debug).scan()
    if os.path.abspath(en_rom) == os.path.abspath(he_rom) and not en_elf:
        en = he
    else:
        en = RomText(en_rom, en_elf, None, cm, min_words, include_debug).scan()
    srcdir = src if src is not None else os.path.dirname(os.path.abspath(he_rom))
    index = SourceIndex(srcdir, cm)
    found, other = compare(he, en, index, all_latin)
    return {'meta': {'rom': os.path.abspath(he_rom), 'elf': he.elf, 'english_rom': os.path.abspath(en_rom),
                     'charmap': cm.path, 'src': srcdir, 'min_words': min_words, 'include_debug': include_debug,
                     'stats': {'rom': he.stats, 'english_rom': en.stats, 'index_fragments': len(index.idx),
                               'secs': round(time.time() - t0, 1)}},
            'english': found, 'latin_not_in_english': other}


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('rom', nargs='?', default=HE_ROM)
    ap.add_argument('--elf')
    ap.add_argument('--en', default=EN_ROM)
    ap.add_argument('--en-elf')
    ap.add_argument('--charmap')
    ap.add_argument('--src')
    ap.add_argument('--min-words', type=int, default=2)
    ap.add_argument('--include-debug', action='store_true')
    ap.add_argument('--all', action='store_true')
    ap.add_argument('--json')
    ap.add_argument('--limit', type=int, default=300)
    a = ap.parse_args(argv)
    if a.min_words < 1:
        ap.error('--min-words must be at least 1, not %d' % a.min_words)
    if not a.en:
        sys.stderr.write('rom_sweep: no English ROM: set HNS_EN_ROM or pass --en\n')
        return 2
    for p in (a.rom, a.en):
        if not os.path.exists(p):
            sys.stderr.write('rom_sweep: %s does not exist\n' % p)
            return 2
    res = sweep(a.rom, a.en, a.elf, a.en_elf, a.charmap, a.src, a.min_words, a.include_debug, a.all)
    if a.json:
        data = json.dumps(res, ensure_ascii=False, indent=1)
        if a.json == '-':
            print(data)
        else:
            with open(a.json, 'w', encoding='utf-8') as f:
                f.write(data + '\n')
    if a.json != '-':
        st = res['meta']['stats']
        print('rom_sweep %s vs %s: %d text runs (%d candidates), %d still English, %.1fs' % (
            res['meta']['rom'], res['meta']['english_rom'], st['rom']['runs'], st['rom']['candidates'],
            len(res['english']), st['secs']))
        for r in res['english'][:a.limit]:
            print('%s %-44s %s\n    %s' % (r['addr'], r['symbol'][:44], ', '.join(r['source'][:2]) or r['object'] or '?',
                                         r['text'][:150]))
        if len(res['english']) > a.limit:
            print('... %d more (see --json)' % (len(res['english']) - a.limit))
        if a.all:
            print('== Latin text not in the English ROM: %d' % len(res['latin_not_in_english']))
            for r in res['latin_not_in_english'][:a.limit]:
                print('%s %-44s %s\n    %s' % (r['addr'], r['symbol'][:44], ', '.join(r['source'][:2]) or '?',
                                             r['text'][:150]))
    return 1 if res['english'] else 0


if __name__ == '__main__':
    sys.exit(main())
