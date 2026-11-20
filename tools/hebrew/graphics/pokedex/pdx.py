"""Index-space canvases over GBA tilesets, with write-back and verification.

A Canvas is what one consumer (a BG tilemap, or a sprite's 1D tile layout) shows, in palette
indices. Edits change `want`; write-back puts each changed pixel into the tileset pixel it comes
from (honouring flips); verify() re-renders every canvas from the new tileset and demands that
it equals `want` everywhere, so a tile shared with another place cannot change unnoticed.
"""
import os
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import gpaths  # noqa: E402
import inspect_fonts as F  # noqa: E402

REPO = gpaths.TREE
OUT = gpaths.out('pokedex')
ENGLISH = os.path.join(OUT, 'english')


def english_png(rel):
    """The English original of a repo file (from the release), saved under OUT/english/, loaded."""
    dst = os.path.join(ENGLISH, rel)
    os.makedirs(os.path.dirname(dst), exist_ok=True)
    with open(dst, 'wb') as fh:
        fh.write(gpaths.english(rel))
    return F.FontPng.load(dst)


def english_bytes(rel):
    return gpaths.english(rel)


def read_jasc(path):
    lines = open(path).read().split('\n')
    n = int(lines[2])
    return [tuple(int(v) for v in lines[3 + i].split()) for i in range(n)]


def tilemap(data):
    return list(struct.unpack('<%dH' % (len(data) // 2), data))


def pack_tilemap(entries):
    return struct.pack('<%dH' % len(entries), *entries)


class Canvas:
    """Base: subclasses define size and where(x, y) -> (png_x, png_y) or None."""
    name = '?'

    def init(self, ts, w, h):
        self.ts = ts
        self.w, self.h = w, h
        self.orig = [[self.read(x, y) for x in range(w)] for y in range(h)]
        self.want = [row[:] for row in self.orig]
        self.edit_rects = []

    def read(self, x, y, ts=None):
        ts = ts or self.ts
        p = self.where(x, y)
        return None if p is None else ts.get(*p)

    # -- edits
    def fill(self, x0, y0, x1, y1, v):
        """Fill the inclusive rectangle with index v (or v(x, y) if callable)."""
        self.edit_rects.append((x0, y0, x1, y1))
        for y in range(y0, y1 + 1):
            for x in range(x0, x1 + 1):
                self.want[y][x] = v(x, y) if callable(v) else v

    def draw(self, bm, x0, y0, style):
        """Stamp a heb.Bitmap with its cell origin at (x0, y0).

        style = ('shadow', ink, shadow) or ('outline', fill, outline)."""
        kind = style[0]
        pts = []
        for y in range(bm.h):
            for x in range(bm.w):
                v = bm.px[y][x]
                if v:
                    pts.append((x0 + x, y0 + y, v))
        pts = [(x, y, v) for x, y, v in pts if 0 <= x < self.w and 0 <= y < self.h]
        if kind == 'shadow':
            _, ink, sh = style
            for x, y, v in pts:
                self.want[y][x] = ink if v == 1 else sh
        elif kind == 'outline':
            _, fill, outl = style
            ink = {(x, y) for x, y, v in pts if v == 1}
            ring = set()
            for x, y in ink:
                for dy in (-1, 0, 1):
                    for dx in (-1, 0, 1):
                        q = (x + dx, y + dy)
                        if q not in ink:
                            ring.add(q)
            for x, y in ring:
                if 0 <= x < self.w and 0 <= y < self.h:
                    self.want[y][x] = outl
            for x, y in ink:
                self.want[y][x] = fill
        else:
            raise ValueError(kind)

    def changed(self):
        return [(x, y) for y in range(self.h) for x in range(self.w) if self.want[y][x] != self.orig[y][x]]


class BgCanvas(Canvas):
    def __init__(self, name, ts, entries, width=32, rows=None):
        self.name = name
        self.entries = list(entries)
        self.mw = width
        rows = rows or (len(self.entries) + width - 1) // width
        self.tw = ts.width // 8
        self.ntiles = self.tw * (ts.height // 8)
        self.init(ts, width * 8, rows * 8)

    def entry(self, tx, ty):
        i = ty * self.mw + tx
        return self.entries[i] if i < len(self.entries) else 0

    def where(self, x, y):
        e = self.entry(x // 8, y // 8)
        t = e & 0x3FF
        if t >= self.ntiles:
            return None
        px, py = x % 8, y % 8
        if e & 0x400:
            px = 7 - px
        if e & 0x800:
            py = 7 - py
        return (t % self.tw) * 8 + px, (t // self.tw) * 8 + py


class SpriteCanvas(Canvas):
    """A sprite of w x h pixels whose tiles start at tile0 in a sheet, 1D mapping."""
    def __init__(self, name, ts, tile0, w, h):
        self.name = name
        self.tile0 = tile0
        self.sw, self.sh = w, h
        self.tw = ts.width // 8
        self.init(ts, w, h)

    def where(self, x, y):
        k = (y // 8) * (self.sw // 8) + x // 8
        t = self.tile0 + k
        return (t % self.tw) * 8 + x % 8, (t // self.tw) * 8 + y % 8


def write_back(ts, canvases):
    """Put every wanted change into the tileset. Returns {png (x, y): value}; raises on conflicts."""
    put = {}
    conflicts = []
    for c in canvases:
        for x, y in c.changed():
            p = c.where(x, y)
            if p is None:
                conflicts.append((c.name, x, y, 'no tile'))
                continue
            v = c.want[y][x]
            if p in put and put[p][0] != v:
                conflicts.append((c.name, x, y, 'png %s wants %d, %s wants %d' % (p, v, put[p][1], put[p][0])))
            put[p] = (v, '%s@%d,%d' % (c.name, x, y))
    if conflicts:
        raise RuntimeError('write-back conflicts:\n' + '\n'.join(map(str, conflicts[:40])))
    for (px, py), (v, _) in put.items():
        ts.put(px, py, v)
    return put


def verify(canvases, ts):
    """Every canvas, re-read from ts (and its current entries), must equal its `want`."""
    bad = []
    for c in canvases:
        for y in range(c.h):
            for x in range(c.w):
                if c.read(x, y, ts) != c.want[y][x]:
                    bad.append((c.name, x, y, c.read(x, y, ts), c.want[y][x]))
    return bad


def check_png(path, ref):
    """Same size, depth, colour type, and byte-identical non-IDAT chunks as `ref` (a FontPng)."""
    new = F.FontPng.load(path)
    problems = []
    if (new.width, new.height, new.bit_depth) != (ref.width, ref.height, ref.bit_depth):
        problems.append('size/depth %s vs %s' % ((new.width, new.height, new.bit_depth),
                                                 (ref.width, ref.height, ref.bit_depth)))
    if new._before != ref._before or new._after != ref._after:
        problems.append('ancillary chunks differ')
    used_new = set(new.pixels)
    used_old = set(ref.pixels)
    if not used_new <= used_old:
        problems.append('new palette indices %s' % sorted(used_new - used_old))
    return problems
