#!/usr/bin/env python3
"""Read the RTL clip log of a clip build between tour steps: which glyphs fell outside their window.

Usage:
  hns.py tour CLIP.gba OUTDIR --clip            every tour, clip report per screenshot (the hook below)
  cliptour.py run SCRIPT OUTDIR [--rom CLIP.gba] [--elf E] [--save S] [--charmap F]
                                                 one hns.py script, clip report after each shot/snap
  cliptour.py decode --elf E --log HEX --count N [--mem ADDR=HEX ...] [--rom R]
                                                 decode a log dump offline (tests, post-mortem)

The clip build is `make hns RTL_CLIP_REPORT=1` (pokehns-clip.gba; Makefile:36-41 on he/renderer).
It records every glyph drawn, or partly drawn, outside its window in a 16-entry ring
(src/text.c '#if RTL_CLIP_REPORT', he/renderer):

  struct RtlClipRecord { const u8 *str; u8 windowId, fontId, x, currentX, windowWidth, glyphWidth;
                         s16 physX; }   = 12 bytes, little endian ('<IBBBBBBh')
  EWRAM_DATA struct RtlClipRecord gRtlClipLog[16];  EWRAM_DATA u32 gRtlClipCount;

Record i lives in gRtlClipLog[i % 16]. str is printerTemplate.currentChar when the glyph is blitted;
RenderText has already stepped past the glyph byte (src/text.c:1908 currentChar++, 2202
PrintGlyphRtl), so the clipped glyph is the byte before str (F9 xx counts as one glyph). The report
decodes the whole string around str with the charmap and marks that glyph with ⟦ ⟧.
UNVERIFIED: the decoding is tested on synthetic logs only (tests/test_cliptour.py).

Each report line: sequence number, window, font, x/currentX, physX and glyph width against the window
width, the nearest symbol of str (ROM string label, or gStringVar4+off etc.) and the decoded text.
Per tour the records are written to OUTDIR/<tour>/clip.json as {"shots": {NAME: [records]}, "lost": n}.
"""
import argparse
import json
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import textwidth as tw  # noqa: E402

EMU_DIR = os.path.join(HERE, 'emu')
REC = struct.Struct('<IBBBBBBh')
RING = 16
FIELDS = ('str', 'windowId', 'fontId', 'x', 'currentX', 'windowWidth', 'glyphWidth', 'physX')
MARK_L, MARK_R = '⟦', '⟧'
BACK, FWD = 240, 240          # bytes read around str to find the string's start and end


def parse_records(log, count, since=0):
    """Records with sequence numbers since..count-1 still in the ring, oldest first.
    Returns (records, lost) where lost counts records overwritten before they were read."""
    since = max(0, min(since, count))
    first = max(since, count - RING)
    out = []
    for seq in range(first, count):
        vals = REC.unpack_from(log, (seq % RING) * REC.size)
        rec = dict(zip(FIELDS, vals))
        rec['seq'] = seq
        out.append(rec)
    return out, first - since


def string_bounds(window, base, addr, floor=None):
    """(start, end) addresses of the 0xFF-terminated string that contains addr - 1, from a
    memory window that starts at address base. end is the address of the FF (or window end).
    FLOOR (the start of the symbol that holds addr) bounds the backward search."""
    i = addr - base
    j = i - 1
    stop = max(0, (floor - base) if floor is not None else 0)
    while j > stop and window[j - 1] != tw.EOS:
        j -= 1
    k = max(i - 1, 0)
    while k < len(window) and window[k] != tw.EOS:
        k += 1
    return base + max(j, 0), base + k


def decode_clip(read, addr, charmap, floor=None):
    """Decoded string around a clip record's str, with the clipped glyph marked.
    read(addr, n) -> bytes; FLOOR = start of the symbol holding addr, if known.
    Returns dict(start, glyph, text)."""
    lo = max(addr - BACK, 0)
    window = read(lo, BACK + FWD if addr >= BACK else addr + FWD)
    start, end = string_bounds(window, lo, addr, floor if floor is not None and floor < addr else None)
    g = addr - 1
    if g - 1 >= start and window[g - 1 - lo] == tw.EXTRA_SYMBOL:
        g -= 1
    before = bytes(window[start - lo:g - lo])
    glyph = bytes(window[g - lo:addr - lo])
    after = bytes(window[addr - lo:end - lo + 1])
    text = charmap.decode(before, stop_at_eos=False) + MARK_L + charmap.decode(glyph, stop_at_eos=False) + \
        MARK_R + charmap.decode(after)
    return {'start': start, 'glyph': charmap.decode(glyph, stop_at_eos=False), 'text': text}


def symbol_floor(where, addr):
    """Start address of the symbol named by an Elf.where() string ('name+0x1C'), when addr lies
    inside it; None when it is past the symbol's end or unknown."""
    import re
    if not where or where == '?' or 'past end' in where:
        return None
    m = re.search(r'\+0x([0-9A-Fa-f]+)$', where)
    return addr - int(m.group(1), 16) if m else addr


def describe(rec, where=None, decoded=None):
    side = 'left' if rec['physX'] < 0 else 'right'
    out = '#%d win %d font %s x %d currentX %d: glyph %d px at physX %d, window %d px (%s edge)' % (
        rec['seq'], rec['windowId'], tw.FONT_NAMES.get(rec['fontId'], rec['fontId']), rec['x'],
        rec['currentX'], rec['glyphWidth'], rec['physX'], rec['windowWidth'], side)
    if where:
        out += ' @ %08X %s' % (rec['str'], where)
    if decoded:
        out += '\n      ' + decoded['text'][:200]
    return out


class ClipReporter(object):
    """Reads gRtlClipLog/gRtlClipCount from a live hns.Emu and keeps what is new since the last poll."""

    def __init__(self, emu, charmap=None, outdir=None, echo=True):
        self.emu = emu
        elf = emu.elf
        try:
            self.log_addr = elf.sym('gRtlClipLog')
            self.count_addr = elf.sym('gRtlClipCount')
        except Exception as e:  # hns.HnsError: not a clip build
            raise RuntimeError('%s is not an RTL_CLIP_REPORT build (%s); build it with '
                               'make hns RTL_CLIP_REPORT=1' % (elf.path, e))
        if charmap is None:
            cand = os.path.join(os.path.dirname(os.path.abspath(elf.path)), 'charmap.txt')
            charmap = cand if os.path.exists(cand) else os.path.join(tw.FONTS_TREE, 'charmap.txt')
        self.charmap = tw.Charmap(charmap) if isinstance(charmap, str) else charmap
        self.outdir = outdir
        self.echo = echo
        self.seen = 0
        self.lost = 0
        self.shots = {}

    def poll(self, label):
        count = self.emu.r32(self.count_addr)
        if count < self.seen:              # the game reset (or the log was cleared): start over
            self.seen = 0
        if count == self.seen:
            self.shots[label] = []
            self._save()
            return []
        log = self.emu.read(self.log_addr, REC.size * RING)
        recs, lost = parse_records(log, count, self.seen)
        self.lost += lost
        self.seen = count
        out = []
        for r in recs:
            where = self.emu.elf.where(r['str'])
            try:
                d = decode_clip(self.emu.read, r['str'], self.charmap, symbol_floor(where, r['str']))
            except Exception as e:      # unreadable address: keep the raw record
                d = {'start': None, 'glyph': None, 'text': '<cannot read: %s>' % e}
            r = dict(r, where=where,
                     string_symbol=self.emu.elf.where(d['start']) if d.get('start') else None,
                     glyph=d['glyph'], text=d['text'])
            out.append(r)
        self.shots[label] = out
        if self.echo:
            print('clip %s: %d glyph(s) outside their window%s' % (label, len(out),
                  (' (%d lost: ring overflowed)' % lost) if lost else ''))
            for r in out:
                print('   ' + describe(r, r['where'], r))
        self._save()
        return out

    def total(self):
        return sum(len(v) for v in self.shots.values())

    def _save(self):
        if not self.outdir:
            return
        recs = {k: [dict(r, str='%08X' % r['str']) for r in v] for k, v in self.shots.items()}
        with open(os.path.join(self.outdir, 'clip.json'), 'w', encoding='utf-8') as fh:
            json.dump({'shots': recs, 'lost': self.lost, 'total': self.total()}, fh, ensure_ascii=False, indent=1)


def install(emu, outdir=None, charmap=None, echo=True):
    """Hook for hns.py: after every emu.shot (snap and shot both end there), report the clips the
    game logged since the previous screenshot under that screenshot's name. Returns the reporter;
    emu.clip is set to it."""
    rep = ClipReporter(emu, charmap, outdir, echo)
    if emu.r32(rep.count_addr):
        rep.poll('_before_first_shot')
    shot = emu.shot

    def shot_and_report(name):
        path = shot(name)
        rep.poll(name)
        return path

    emu.shot = shot_and_report
    emu.clip = rep
    return rep


# ---------------------------------------------------------------------------- CLI

def _load_hns():
    sys.path.insert(0, EMU_DIR)
    import hns  # noqa: E402
    return hns


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='cmd')
    p = sub.add_parser('run')
    p.add_argument('script')
    p.add_argument('outdir')
    p.add_argument('--rom')
    p.add_argument('--elf')
    p.add_argument('--save')
    p.add_argument('--charmap')
    p = sub.add_parser('decode')
    p.add_argument('--elf', required=True)
    p.add_argument('--log', required=True, help='hex bytes of gRtlClipLog (192 bytes)')
    p.add_argument('--count', type=int, required=True)
    p.add_argument('--since', type=int, default=0)
    p.add_argument('--mem', action='append', default=[], help='ADDR=HEX: memory the strings live in')
    p.add_argument('--rom', help='ROM image, so 08xxxxxx strings can be read')
    p.add_argument('--charmap')
    a = ap.parse_args(argv)
    if a.cmd == 'run':
        hns = _load_hns()
        rom = a.rom or hns.DEFAULT_ROM
        # boot a copy (OUTDIR/cur.sav) so an in-game save never writes into the ladder
        emu = hns.Emu(rom, a.elf, a.outdir, hns.prepare_save(a.save, a.outdir, False))
        rep = install(emu, a.outdir, a.charmap)
        try:
            emu.run_script(a.script)
        finally:
            emu.close()
        print('clip total: %d glyph(s), %d lost' % (rep.total(), rep.lost))
        return 1 if rep.total() else 0
    if a.cmd == 'decode':
        hns = _load_hns()
        elf = hns.Elf(a.elf)
        mem = MemImage(a.rom)
        for m in a.mem:
            addr, hexdata = m.split('=', 1)
            mem.add(int(addr, 16), bytes.fromhex(hexdata))
        cm = tw.Charmap(a.charmap or os.path.join(os.path.dirname(os.path.abspath(a.elf)), 'charmap.txt'))
        recs, lost = parse_records(bytes.fromhex(a.log), a.count, a.since)
        for r in recs:
            where = elf.where(r['str'])
            d = decode_clip(mem.read, r['str'], cm, symbol_floor(where, r['str']))
            print(describe(r, where, d))
        if lost:
            print('%d record(s) lost' % lost)
        return 1 if recs else 0
    ap.print_usage()
    return 2


class MemImage(object):
    """read(addr, n) over a ROM file plus added memory blocks (a later add() overrides an earlier
    one where they overlap); unknown bytes read as 0xFF."""

    def __init__(self, rom=None):
        self.blocks = []
        if rom:
            with open(rom, 'rb') as fh:
                self.blocks.append((0x08000000, fh.read()))

    def add(self, addr, data):
        self.blocks.insert(0, (addr, bytes(data)))

    def read(self, addr, n):
        out = bytearray(b'\xff' * n)
        for base, data in reversed(self.blocks):          # the block added last wins
            lo, hi = max(addr, base), min(addr + n, base + len(data))
            if lo < hi:
                out[lo - addr:hi - addr] = data[lo - base:hi - base]
        return bytes(out)


if __name__ == '__main__':
    sys.exit(main())
