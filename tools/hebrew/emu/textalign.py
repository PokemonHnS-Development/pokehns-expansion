#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Pixel alignment check: a Hebrew screenshot against the English one of the same moment.

    textalign.py pair EN.png HE.png [--out DIR] [--tol 2] [--json]
    textalign.py tours EN_DIR HE_DIR OUT [--only RE] [--tol 2] [--jobs N]

`pair` checks one pair (exit 1 if a window is not OK or IN-PLACE); `tours` pairs every PNG of
two tour runs by its path (TOUR/SHOT.png; the release tours are deterministic, so a shot shows
the same moment in both builds) and writes OUT/report.json (every window and line),
OUT/summary.txt (counts, then each class's windows grouped by tour and place), OUT/windows.txt
(every window that is not OK) and OUT/crops/ (an English | Hebrew crop pair, 3x, per window that
is not OK; IN-PLACE ones too).

How it works (pixels only, nothing from the ROM; emu/README.md, "Text alignment"):

1. Text is where the two shots differ. Differing pixels up to 3 columns and 1 row apart are
   grouped into seeds: a word or a line of text, never two lines.
2. A seed's paper is the most common colour the two shots share in its box and a 2-px ring
   around it; its ink colours are its differing pixels whose counterpart in the other shot is
   paper. A seed with more than 6 ink colours is not text (a sprite), and one whose paper is
   under half of the shared pixels is text over art: UNKNOWN.
3. The window is the paper rectangle grown from the seed a column, then a row, at a time while
   the new line holds, in both shots, paper, that shot's ink colours, or static pixels (the
   same in both shots: a sprite cursor, a rounded corner) with at least 30% paper. It stops at
   the frame's inner edge, so a margin is measured against the visible box (the overworld
   message box mirrors around 208 px because its frame pads only the left side). Each shot's
   rectangle is then widened alone, for a menu sized to its longer text. A side that is not a
   solid edge, or that lies on the screen border (a box cut by the screen), is "soft": no
   margin is measured against it. Paper filling the whole screen holds several invisible
   windows and is soft all round.
4. A line is a band of rows holding text in either shot: 8-connected ink groups shorter than
   16 px that differ somewhere between the shots, plus static groups within 4 px of them (a
   Latin letter an in-place line draws where English does). Icons, frames and numbers drawn in
   the same place in both builds do not count.
5. Each line is checked:
   - mirror: Hebrew right margin against English left margin;
   - mirror-right: Hebrew left margin against English right margin (a right-aligned column);
   - centre: an English line within 8 px of centred stays as far off centre, either way;
   - in place: Hebrew keeps English's left or right margin, as WINDOW_RTL_IN_PLACE and
     WINDOW_RTL_LTR windows do by design;
   - edge: Hebrew ink on the window's outermost column where English keeps a gap at both ends
     (at Hebrew's start a 0 against English's 1 is the shadow, not an edge), or Hebrew ink in
     the screen's text colours on a band English leaves empty, cut at both sides of the window
     (text drawn past its window, seen through a gap), or on a patch of paper too small to be
     a window (under 12x8 px) with 12 px or more of it, twice English's;
   - rows: the line's top and bottom ink rows against English's; the scripts differ by up to
     3 px at either end, so a line counts as moved when both ends move the same way by more;
   - cursor: a menu triangle that starts the English line must end the Hebrew one, pointing
     left; one that stays in place pointing right while the window's text is mirrored is not
     mirrored.
   A line whose two extents differ in width by a factor over 4 shows something else in one
   shot (a name the English build draws blank) and is not compared.
6. A window's class is its worst line: EDGE, MIRROR-MISMATCH (also a window where some lines
   are mirrored and others keep English's start, or an unmirrored cursor), CENTRE-OFF,
   ROW-SHIFT, UNKNOWN (no paper, a soft side under a line that keeps no anchor on the solid
   side, or no line with ink in both shots), IN-PLACE (every compared line keeps English's
   anchor: by design for the screens docs/hebrew_translation.md lists, reported so that a
   reviewer can check them against that list) or OK.

Tolerance (--tol, default 2 px): on the 71 release tours of 1.0 the Hebrew right margin minus
the English left margin of the mirrored lines is 0 on 6,026 lines, -1 on 683, +1 on 206, -2 on
1,100 (1,008 of them the battle healthboxes' names, sprites placed 2 px off the mirror) and +2
on 242, then drops to 86 lines at -3 and 46 at +3 of all paired lines. A glyph's shadow falls
a column right of its ink, so Hebrew's outer column at the start is the shadow where
English's is the ink: one pixel of the difference is the font, the other is slack.
"""
import argparse
import json
import os
import re
import struct
import sys
import zlib
from collections import Counter

PNG_SIG = b'\x89PNG\r\n\x1a\n'

TOL = 2            # px, margins (see the docstring)
ROW_TOL = 3        # px, top and bottom rows of a line (see classify_line)
JOIN_X = 3         # px, differing pixels this far apart in a row (a word space) are one seed
RING = 2           # px, ring around a seed that gives its paper
PAPER_SHARE = 0.5  # the paper's share of the ring's shared pixels
SOLID = 0.6        # share of non-paper pixels that makes a window side a solid edge
MAX_INK_COLOURS = 6  # a seed with more ink colours than this in a shot is not text
STATIC_SHARE = 0.3   # paper share a column or row needs to grow over static pixels
MIN_W, MIN_H = 12, 8  # px, a smaller paper rectangle is not a text window (a sprite's label)
FRAGMENT_MIN = 12   # px of Hebrew ink that make a small gap's ink a finding
MIN_GLYPH_H = 6     # px, the shortest line of text (FONT_SMALL's letters and shadow)
WIDTH_FACTOR = 4    # a line this many times wider in one shot shows something else there
MAX_GLYPH_H = 16    # px, a moving group of ink this tall or taller is an icon, not a glyph
JOIN_STATIC = 4     # px, a static group this close to a line's text belongs to the line
CENTRE_SLACK = 8    # px, |left - right| margin of an English line that may be centred
CURSOR_ZONE = 12    # px, how far into a window a menu cursor stands

CLASSES = ('EDGE', 'MIRROR-MISMATCH', 'CENTRE-OFF', 'ROW-SHIFT', 'UNKNOWN', 'IN-PLACE', 'OK')
RANK = {c: i for i, c in enumerate(CLASSES)}
MIRRORED = {'mirror', 'mirror-right', 'centre'}
IN_PLACE = {'in-place', 'in-place-right'}
UNCHECKED = ('SAME', 'EN-ONLY', 'HE-ONLY', 'UNPAIRED')


# --------------------------------------------------------------------------- PNG

class Shot(object):
    """A screenshot: width, height and rows of 0xRRGGBB ints."""

    def __init__(self, w, h, rows, path=None):
        self.w, self.h, self.rows, self.path = w, h, rows, path


def _paeth(a, b, c):
    p = a + b - c
    pa, pb, pc = abs(p - a), abs(p - b), abs(p - c)
    if pa <= pb and pa <= pc:
        return a
    return b if pb <= pc else c


def read_png(path):
    """Decode a non-interlaced PNG (grey, RGB, palette, grey+alpha, RGBA; 8-bit, or 1/2/4-bit
    grey and palette) into a Shot. Alpha is ignored: screenshots are opaque."""
    with open(path, 'rb') as fh:
        data = fh.read()
    if data[:8] != PNG_SIG:
        raise ValueError('%s: not a PNG' % path)
    i, idat, plte = 8, [], None
    w = h = depth = ctype = interlace = None
    while i < len(data):
        n = struct.unpack('>I', data[i:i + 4])[0]
        t, c = data[i + 4:i + 8], data[i + 8:i + 8 + n]
        i += 12 + n
        if t == b'IHDR':
            w, h, depth, ctype, _, _, interlace = struct.unpack('>IIBBBBB', c)
        elif t == b'PLTE':
            plte = [(c[k] << 16) | (c[k + 1] << 8) | c[k + 2] for k in range(0, len(c) - 2, 3)]
        elif t == b'IDAT':
            idat.append(c)
        elif t == b'IEND':
            break
    if w is None:
        raise ValueError('%s: no IHDR' % path)
    if interlace:
        raise ValueError('%s: interlaced PNG' % path)
    chans = {0: 1, 2: 3, 3: 1, 4: 2, 6: 4}.get(ctype)
    if chans is None or (depth != 8 and not (ctype in (0, 3) and depth in (1, 2, 4))):
        raise ValueError('%s: unsupported PNG (colour type %s, depth %s)' % (path, ctype, depth))
    bits = chans * depth
    stride, bpp = (w * bits + 7) // 8, max(1, bits // 8)
    raw = zlib.decompress(b''.join(idat))
    prev = bytearray(stride)
    rows = []
    for y in range(h):
        off = y * (stride + 1)
        f = raw[off]
        line = bytearray(raw[off + 1:off + 1 + stride])
        if f == 1:
            for x in range(bpp, stride):
                line[x] = (line[x] + line[x - bpp]) & 255
        elif f == 2:
            for x in range(stride):
                line[x] = (line[x] + prev[x]) & 255
        elif f == 3:
            for x in range(stride):
                a = line[x - bpp] if x >= bpp else 0
                line[x] = (line[x] + ((a + prev[x]) >> 1)) & 255
        elif f == 4:
            for x in range(stride):
                a = line[x - bpp] if x >= bpp else 0
                c = prev[x - bpp] if x >= bpp else 0
                line[x] = (line[x] + _paeth(a, prev[x], c)) & 255
        elif f != 0:
            raise ValueError('%s: bad PNG filter %d' % (path, f))
        prev = line
        if ctype == 2:
            row = [(r << 16) | (g << 8) | b for r, g, b in zip(line[0::3], line[1::3], line[2::3])]
        elif ctype == 6:
            row = [(r << 16) | (g << 8) | b for r, g, b in zip(line[0::4], line[1::4], line[2::4])]
        elif ctype == 4:
            row = [v * 0x010101 for v in line[0::2]]
        else:
            if depth == 8:
                vals = list(line)
            else:
                per, mask = 8 // depth, (1 << depth) - 1
                vals = [(line[x // per] >> (8 - depth * (x % per + 1))) & mask for x in range(w)]
            if ctype == 3:
                row = [plte[v] for v in vals]
            else:
                scale = 255 // ((1 << depth) - 1)
                row = [(v * scale) * 0x010101 for v in vals]
        rows.append(row[:w])
    return Shot(w, h, rows, path)


def write_png(path, rows):
    """Write rows of 0xRRGGBB ints as an 8-bit RGB PNG."""
    h, w = len(rows), len(rows[0])
    raw = bytearray()
    for r in rows:
        raw.append(0)
        for v in r:
            raw += bytes(((v >> 16) & 255, (v >> 8) & 255, v & 255))

    def chunk(t, c):
        return struct.pack('>I', len(c)) + t + c + struct.pack('>I', zlib.crc32(t + c) & 0xffffffff)
    with open(path, 'wb') as f:
        f.write(PNG_SIG + chunk(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 2, 0, 0, 0)) +
                chunk(b'IDAT', zlib.compress(bytes(raw), 6)) + chunk(b'IEND', b''))


# --------------------------------------------------------------------------- seeds

def diff_mask(en, he):
    """Per row, the x of every pixel that differs (None for an identical row)."""
    out = []
    for y in range(en.h):
        a, b = en.rows[y], he.rows[y]
        out.append(None if a == b else [x for x in range(en.w) if a[x] != b[x]])
    return out


def _bands(rows_with_ink, gap=0):
    """Runs of consecutive numbers (a run may skip GAP missing numbers)."""
    out, start, prev = [], None, None
    for y in rows_with_ink:
        if start is None:
            start = prev = y
        elif y <= prev + 1 + gap:
            prev = y
        else:
            out.append((start, prev))
            start = prev = y
    if start is not None:
        out.append((start, prev))
    return out


def seeds(en, diff):
    """Groups of differing pixels: pixels at most JOIN_X columns and one row apart are one
    group, so a group is a word or a line of text and two lines stay apart. Returns a list of
    (x0, y0, x1, y1, pixels) with inclusive bounds."""
    pts = set()
    for y, xs in enumerate(diff):
        if xs:
            pts.update((x, y) for x in xs)
    seen, out = set(), []
    for start in sorted(pts, key=lambda p: (p[1], p[0])):
        if start in seen:
            continue
        seen.add(start)
        stack, pix = [start], []
        while stack:
            cx, cy = stack.pop()
            pix.append((cx, cy))
            for dy in (-1, 0, 1):
                for dx in range(-JOIN_X, JOIN_X + 1):
                    n = (cx + dx, cy + dy)
                    if n in pts and n not in seen:
                        seen.add(n)
                        stack.append(n)
        xs = [p[0] for p in pix]
        ys = [p[1] for p in pix]
        out.append((min(xs), min(ys), max(xs), max(ys), pix))
    return out


def ring_paper(en, he, x0, y0, x1, y1):
    """The paper under a seed: the most common colour both shots share inside the seed's box
    and a RING-px ring around it, and its share of those shared pixels. Between the strokes of
    a line of text the shared pixels are the paper; the ring adds the margin around it."""
    cnt, n = Counter(), 0
    for y in range(max(0, y0 - RING), min(en.h, y1 + RING + 1)):
        a, b = en.rows[y], he.rows[y]
        for x in range(max(0, x0 - RING), min(en.w, x1 + RING + 1)):
            if a[x] == b[x]:
                cnt[a[x]] += 1
                n += 1
    if not n:
        return None, 0.0
    colour, k = cnt.most_common(1)[0]
    return colour, k / float(n)


# --------------------------------------------------------------------------- windows

class Window(object):
    """A paper rectangle. RECT is the rectangle both shots share; RECTS gives each shot's own,
    which is wider in the shot whose menu is sized to longer text."""

    def __init__(self, rect, paper):
        self.rect, self.paper = rect, paper
        self.rects = {'en': rect, 'he': rect}
        self.seeds = []
        self.soft = []
        self.inks = (set(), set())
        self.cls, self.notes, self.lines = 'OK', [], []


def _line_ok(en, he, inks, paper, pts):
    """Can the pixels PTS (one column or row) be inside the window? In each shot every pixel
    must be paper, one of that shot's ink colours, or static (the same in both shots, such as a
    sprite cursor or an icon). Each shot needs one paper pixel, and when static pixels are
    present the paper must be STATIC_SHARE of the line: a frame line is all static, no paper."""
    ie, ih = inks
    pe = ph = st = 0
    for (x, y) in pts:
        a, b = en.rows[y][x], he.rows[y][x]
        if a == b:
            # the same pixel in both shots: paper, or static (a frame line drawn in the text's
            # colour is static too; text rarely puts the same pixel in the same place)
            if a == paper:
                pe += 1
                ph += 1
            else:
                st += 1
            continue
        if a == paper:
            pe += 1
        elif a not in ie:
            return False
        if b == paper:
            ph += 1
        elif b not in ih:
            return False
    if not pe or not ph:
        return False
    if st and min(pe, ph) < STATIC_SHARE * len(pts):
        return False
    return True


def grow(en, he, inks, paper, box):
    """The paper rectangle around BOX: columns first (over the rows the box has), then rows
    (over the columns found), repeated until nothing changes. The rounded corners of a frame are
    static pixels, so they do not stop a long column or row."""
    x0, y0, x1, y1 = box
    w, h = en.w, en.h
    for _ in range(4):
        before = (x0, y0, x1, y1)
        ya, yb = y0, y1
        while x0 > 0 and _line_ok(en, he, inks, paper, [(x0 - 1, y) for y in range(ya, yb + 1)]):
            x0 -= 1
        while x1 < w - 1 and _line_ok(en, he, inks, paper, [(x1 + 1, y) for y in range(ya, yb + 1)]):
            x1 += 1
        xa, xb = x0, x1
        while y0 > 0 and _line_ok(en, he, inks, paper, [(x, y0 - 1) for x in range(xa, xb + 1)]):
            y0 -= 1
        while y1 < h - 1 and _line_ok(en, he, inks, paper, [(x, y1 + 1) for x in range(xa, xb + 1)]):
            y1 += 1
        if (x0, y0, x1, y1) == before:
            break
    # a seed that started on two papers (a cursor on the frame's margin beside a striped row)
    # keeps only the columns and rows that hold this paper
    def has_paper(pts):
        return any(en.rows[y][x] == paper for (x, y) in pts) and any(he.rows[y][x] == paper for (x, y) in pts)
    ya, yb = y0, y1
    while x1 > x0 and not has_paper([(x0, y) for y in range(ya, yb + 1)]):
        x0 += 1
    while x1 > x0 and not has_paper([(x1, y) for y in range(ya, yb + 1)]):
        x1 -= 1
    xa, xb = x0, x1
    while y1 > y0 and not has_paper([(x, y0) for x in range(xa, xb + 1)]):
        y0 += 1
    while y1 > y0 and not has_paper([(x, y1) for x in range(xa, xb + 1)]):
        y1 -= 1
    return x0, y0, x1, y1


def _line_ok_one(shot, paper, pts):
    """Can PTS widen a window in one shot? Its paper must be STATIC_SHARE of the line, whatever
    the rest is (text that is longer in this shot, a cursor), so that a frame, a scroll bar or a
    neighbouring box stops it."""
    p = sum(1 for (x, y) in pts if shot.rows[y][x] == paper)
    return p > 0 and p >= STATIC_SHARE * len(pts)


def widen(shot, paper, rect):
    """RECT widened to the left and right over this shot alone: a menu sized to its text is
    wider in the build whose text is longer, so its frame stands further out in that shot."""
    x0, y0, x1, y1 = rect
    while x0 > 0 and _line_ok_one(shot, paper, [(x0 - 1, y) for y in range(y0, y1 + 1)]):
        x0 -= 1
    while x1 < shot.w - 1 and _line_ok_one(shot, paper, [(x1 + 1, y) for y in range(y0, y1 + 1)]):
        x1 += 1
    return x0, y0, x1, y1


def soft_sides(shot, paper, rect):
    """The sides of RECT whose outside line is not a solid edge (fewer than SOLID of its pixels
    differ from the paper), or that lie on the screen border while the opposite side does not:
    a box cut by the screen goes on past it. A band across the whole width (a title bar) has
    the screen for its frame; paper that fills the whole screen is the background of several
    windows whose edges cannot be seen, so all its sides are soft."""
    x0, y0, x1, y1 = rect
    out = []
    full_w, full_h = x0 == 0 and x1 == shot.w - 1, y0 == 0 and y1 == shot.h - 1
    if full_w and full_h:
        return ['left', 'right', 'top', 'bottom']
    if x0 == 0 and not full_w:
        out.append('left')
    if x1 == shot.w - 1 and not full_w:
        out.append('right')
    if y0 == 0 and not full_h:
        out.append('top')
    if y1 == shot.h - 1 and not full_h:
        out.append('bottom')

    def share(vals):
        vals = list(vals)
        return sum(1 for v in vals if v != paper) / float(len(vals)) if vals else 1.0
    if x0 > 0 and share(shot.rows[y][x0 - 1] for y in range(y0, y1 + 1)) < SOLID:
        out.append('left')
    if x1 < shot.w - 1 and share(shot.rows[y][x1 + 1] for y in range(y0, y1 + 1)) < SOLID:
        out.append('right')
    if y0 > 0 and share(shot.rows[y0 - 1][x] for x in range(x0, x1 + 1)) < SOLID:
        out.append('top')
    if y1 < shot.h - 1 and share(shot.rows[y1 + 1][x] for x in range(x0, x1 + 1)) < SOLID:
        out.append('bottom')
    return out


def find_windows(en, he, diff=None):
    """Windows (paper rectangles holding differing ink) and UNKNOWN text regions."""
    if diff is None:
        diff = diff_mask(en, he)
    found = []
    for (x0, y0, x1, y1, pix) in seeds(en, diff):
        paper, share = ring_paper(en, he, x0, y0, x1, y1)
        ink_e, ink_h = set(), set()
        for (x, y) in pix:
            a, b = en.rows[y][x], he.rows[y][x]
            if b == paper and a != paper:
                ink_e.add(a)
            elif a == paper and b != paper:
                ink_h.add(b)
        textlike = (len(ink_e) <= MAX_INK_COLOURS and len(ink_h) <= MAX_INK_COLOURS and
                    (ink_e or ink_h))
        found.append({'box': (x0, y0, x1, y1), 'paper': paper, 'share': share, 'pix': len(pix),
                      'ink': (ink_e, ink_h), 'textlike': bool(textlike)})
    # one ink set per paper colour and shot, from every text-like seed on that paper
    inks = {}
    for s in found:
        if s['textlike'] and s['share'] >= PAPER_SHARE:
            e, h = inks.setdefault(s['paper'], (set(), set()))
            e |= s['ink'][0]
            h |= s['ink'][1]
    windows, unknown, other = [], [], []
    for s in found:
        if not s['textlike']:
            other.append(s)
            continue
        if s['share'] < PAPER_SHARE:
            unknown.append(s)
            continue
        home = [w for w in windows if w.paper == s['paper'] and _contains(w.rect, s['box'])]
        if home:
            home[0].seeds.append(s)
            continue
        ie, ih = inks[s['paper']]
        ie, ih = ie - {s['paper']}, ih - {s['paper']}
        rect = grow(en, he, (ie, ih), s['paper'], s['box'])
        for w in windows:
            if w.paper == s['paper'] and w.rect == rect:
                w.seeds.append(s)
                break
        else:
            w = Window(rect, s['paper'])
            w.seeds.append(s)
            w.inks = (ie, ih)
            windows.append(w)
    for w in windows:
        w.rects = {'en': widen(en, w.paper, w.rect), 'he': widen(he, w.paper, w.rect)}
    # windows on the same paper that overlap by half of the smaller one, or that have the same
    # columns and overlap or touch (the lines of one box, grown from different seeds, can stop
    # a few rows apart), in either shot, are one window
    keep = list(windows)
    merged = True
    while merged:
        merged = False
        for i in range(len(keep)):
            for j in range(i + 1, len(keep)):
                p, q = keep[i], keep[j]
                if p.paper == q.paper and any(_overlap(p.rects[k], q.rects[k]) >= 0.5 or
                                              _stacked(p.rects[k], q.rects[k]) for k in ('en', 'he')):
                    p.rect = _union(p.rect, q.rect)
                    p.rects = {k: _union(p.rects[k], q.rects[k]) for k in ('en', 'he')}
                    p.seeds.extend(q.seeds)
                    p.inks = (p.inks[0] | q.inks[0], p.inks[1] | q.inks[1])
                    del keep[j]
                    merged = True
                    break
            if merged:
                break
    small = [w for w in keep if w.rect[2] - w.rect[0] + 1 < MIN_W or w.rect[3] - w.rect[1] + 1 < MIN_H]
    keep = [w for w in keep if w not in small]
    for w in keep:
        w.soft = sorted(set(soft_sides(en, w.paper, w.rects['en'])) | set(soft_sides(he, w.paper, w.rects['he'])))
    keep.sort(key=lambda w: (w.rect[1], w.rect[0]))
    # text-like ink with no paper: one region per cluster of nearby seeds, unless it lies in a
    # window found from other seeds (a glyph over an icon)
    boxes = [list(s['box']) for s in unknown
             if not any(_contains(w.rect, s['box']) for w in keep)]
    merged = True
    while merged:
        merged = False
        for i in range(len(boxes)):
            for j in range(i + 1, len(boxes)):
                a, b = boxes[i], boxes[j]
                if a[0] <= b[2] + 4 and b[0] <= a[2] + 4 and a[1] <= b[3] + 4 and b[1] <= a[3] + 4:
                    boxes[i] = [min(a[0], b[0]), min(a[1], b[1]), max(a[2], b[2]), max(a[3], b[3])]
                    del boxes[j]
                    merged = True
                    break
            if merged:
                break
    regions = []
    for bx in boxes:
        if bx[2] - bx[0] + 1 < MIN_W or bx[3] - bx[1] + 1 < MIN_GLYPH_H:
            continue        # a bar, a gender sign or a dot of a sprite, not a line of text
        paper, share = ring_paper(en, he, *bx)
        regions.append({'box': tuple(bx), 'share': share})
    return keep, regions, other, small


def _contains(a, b):
    return a[0] <= b[0] and a[1] <= b[1] and a[2] >= b[2] and a[3] >= b[3]


def _union(a, b):
    return (min(a[0], b[0]), min(a[1], b[1]), max(a[2], b[2]), max(a[3], b[3]))


def _stacked(a, b):
    """Same columns (within 2 px) and overlapping or touching rows."""
    return abs(a[0] - b[0]) <= 2 and abs(a[2] - b[2]) <= 2 and a[1] <= b[3] + 1 and b[1] <= a[3] + 1


def _overlap(a, b):
    """Intersection area over the smaller rectangle's area."""
    ix = min(a[2], b[2]) - max(a[0], b[0]) + 1
    iy = min(a[3], b[3]) - max(a[1], b[1]) + 1
    if ix <= 0 or iy <= 0:
        return 0.0
    area = lambda r: (r[2] - r[0] + 1) * (r[3] - r[1] + 1)
    return ix * iy / float(min(area(a), area(b)))


# --------------------------------------------------------------------------- lines

def ink_components(shot, other, paper, xa, xb, ya, yb):
    """The text of SHOT in the box: its 8-connected groups of non-paper pixels no taller than a
    glyph that move (at least one pixel differs from OTHER), plus the static groups (the same
    in both shots) that stand within JOIN_STATIC columns of one of them on the same rows, such
    as a Latin letter or a digit an in-place line draws where English does. Static groups
    elsewhere (icons, frame corners, numbers drawn in the same place) are not text."""
    seen, moving, static = set(), [], []
    rows = shot.rows
    for y in range(ya, yb + 1):
        for x in range(xa, xb + 1):
            if rows[y][x] == paper or (x, y) in seen:
                continue
            seen.add((x, y))
            stack, comp, moves = [(x, y)], [], False
            while stack:
                cx, cy = stack.pop()
                comp.append((cx, cy))
                if rows[cy][cx] != other.rows[cy][cx]:
                    moves = True
                for nx in (cx - 1, cx, cx + 1):
                    for ny in (cy - 1, cy, cy + 1):
                        if xa <= nx <= xb and ya <= ny <= yb and (nx, ny) not in seen and rows[ny][nx] != paper:
                            seen.add((nx, ny))
                            stack.append((nx, ny))
            ys = [p[1] for p in comp]
            if max(ys) - min(ys) >= MAX_GLYPH_H:
                continue
            (moving if moves else static).append(comp)

    def box(c):
        xs = [p[0] for p in c]
        ys = [p[1] for p in c]
        return min(xs), max(xs), min(ys), max(ys)
    out = list(moving)
    boxes = [box(c) for c in out]
    # a static group on the box's border is a frame corner or a neighbour's edge, never text
    pending = [(c, b) for c, b in ((c, box(c)) for c in static)
               if b[0] > xa and b[1] < xb and b[2] > ya and b[3] < yb]
    grew = True
    while grew and pending:
        grew = False
        for item in list(pending):
            c, (ax, bx, ay, by) = item
            for (cx0, cx1, cy0, cy1) in boxes:
                if ay <= cy1 and cy0 <= by and ax <= cx1 + JOIN_STATIC and cx0 <= bx + JOIN_STATIC:
                    out.append(c)
                    boxes.append((ax, bx, ay, by))
                    pending.remove(item)
                    grew = True
                    break
    return out


def cursors_in(shot, paper, xa, xb, ya, yb):
    """The filled menu triangles in the box: one-colour 4-connected groups 3-8 px wide and 5-11
    px tall, every column one unbroken run centred on the same row, whose heights fall
    (pointing right) or rise (pointing left) by 1-3 px a column. Returns [(x0, x1, y0, y1,
    'right'|'left')]."""
    seen = set()
    out = []
    rows = shot.rows
    for y in range(ya, yb + 1):
        for x in range(xa, xb + 1):
            v = rows[y][x]
            if v == paper or (x, y) in seen:
                continue
            stack, comp = [(x, y)], []
            seen.add((x, y))
            while stack:
                cx, cy = stack.pop()
                comp.append((cx, cy))
                for nx, ny in ((cx + 1, cy), (cx - 1, cy), (cx, cy + 1), (cx, cy - 1)):
                    if xa <= nx <= xb and ya <= ny <= yb and (nx, ny) not in seen and rows[ny][nx] == v:
                        seen.add((nx, ny))
                        stack.append((nx, ny))
            if len(comp) > 60:
                continue
            xs = [p[0] for p in comp]
            ys = [p[1] for p in comp]
            if not (3 <= max(xs) - min(xs) + 1 <= 8 and 5 <= max(ys) - min(ys) + 1 <= 11):
                continue
            cols = {}
            for (cx, cy) in comp:
                cols.setdefault(cx, []).append(cy)
            heights, mids, ok = [], [], True
            for cx in range(min(xs), max(xs) + 1):
                c = cols.get(cx)
                if not c or max(c) - min(c) + 1 != len(c):
                    ok = False
                    break
                heights.append(len(c))
                mids.append((max(c) + min(c)) / 2.0)
            if not ok or max(mids) - min(mids) > 1:
                continue
            steps = [heights[i + 1] - heights[i] for i in range(len(heights) - 1)]
            if all(-3 <= d <= -1 for d in steps) and heights[0] >= 5:
                out.append((min(xs), max(xs), min(ys), max(ys), 'right'))
            elif all(1 <= d <= 3 for d in steps) and heights[-1] >= 5:
                out.append((min(xs), max(xs), min(ys), max(ys), 'left'))
    return out


def cursor_in(shot, paper, xa, xb, ya, yb):
    """The largest menu triangle of cursors_in, as (x0, x1, 'right'|'left'), or None."""
    found = cursors_in(shot, paper, xa, xb, ya, yb)
    if not found:
        return None
    c = max(found, key=lambda t: (t[1] - t[0] + 1) * (t[3] - t[2] + 1))
    return c[0], c[1], c[4]


def fixed_cursors(en, he, w):
    """English menu cursors (pointing right, at most CURSOR_ZONE px into the window) that the
    Hebrew shot shows in the same place, still pointing right: a cursor that was not mirrored
    with its window. Arrows elsewhere (a pocket title's next arrow) are not menu cursors."""
    r_e, r_h = w.rects['en'], w.rects['he']
    ce = cursors_in(en, w.paper, r_e[0], r_e[2], w.rect[1], w.rect[3])
    ch = cursors_in(he, w.paper, r_h[0], r_h[2], w.rect[1], w.rect[3])
    return [c for c in ce if c[4] == 'right' and c in ch and c[0] - r_e[0] <= CURSOR_ZONE]


def _mode(vals):
    """The most common value (the smallest of a tie), or None."""
    if not vals:
        return None
    c = Counter(vals)
    top = max(c.values())
    return min(v for v in c if c[v] == top)


def measure_lines(en, he, w):
    """Pass 1: the window's lines with their extents, margins, rows and cursors. A line is
    a band of rows holding text: the groups of ink that move between the shots and are no
    taller than a glyph (an icon beside two lines of text would join them into one band)."""
    y0, y1 = w.rect[1], w.rect[3]
    P = w.paper
    comps = {}
    for name, s, o in (('en', en, he), ('he', he, en)):
        r = w.rects[name]
        comps[name] = ink_components(s, o, P, r[0], r[2], y0, y1)
    rows = set()
    for c in comps['en'] + comps['he']:
        rows.update(p[1] for p in c)
    lines = []
    for (ya, yb) in _bands(sorted(rows)):
        ln = {'rows': [ya, yb]}
        pix = {}
        for name in ('en', 'he'):
            pix[name] = [p for c in comps[name] if ya <= c[0][1] <= yb for p in c]
        for name in ('en', 'he'):
            if pix[name]:
                xs = [p[0] for p in pix[name]]
                ys = [p[1] for p in pix[name]]
                rx0, rx1 = w.rects[name][0], w.rects[name][2]
                ln[name] = [min(xs), max(xs)]
                ln[name + '_margins'] = [min(xs) - rx0, rx1 - max(xs)]
                ln[name + '_rows'] = [min(ys), max(ys)]
                cols = set((en if name == 'en' else he).rows[y][x] for (x, y) in pix[name])
                ln[name + '_colours'] = len(cols)
                ln.setdefault('_cols', {})[name] = cols
        if not pix['he']:
            ln['status'] = 'EN-ONLY'
        elif not pix['en']:
            ln['status'] = 'HE-ONLY'
        else:
            ln['mirror_delta'] = ln['he_margins'][1] - ln['en_margins'][0]
            ce = cursor_in(en, P, w.rects['en'][0], w.rects['en'][2], ya, yb)
            ch = cursor_in(he, P, w.rects['he'][0], w.rects['he'][2], ya, yb)
            ln['cursor'] = [list(ce) if ce else None, list(ch) if ch else None]
        lines.append(ln)
    return lines


def classify_line(ln, w, tol, en_start, he_start, text_colours=None):
    """Pass 2: the anchors one line keeps and its status. EN_START and HE_START are the window's
    most common English left margin and Hebrew right margin (the lines' start); TEXT_COLOURS are
    the colours of the Hebrew text that has an English counterpart on this screen."""
    softl, softr = 'left' in w.soft, 'right' in w.soft
    if 'en' not in ln:
        # Hebrew text on a band where English has nothing, cut at both sides of the window: text
        # past its window, seen through a gap between two frames. Only ink in the colours of the
        # screen's Hebrew text counts (a sprite caught in another frame of its animation is not
        # text), and only at both sides (a line English draws blank, such as a name the English
        # build cannot draw, often ends at one side).
        hl, hr = ln['he_margins']
        cols = ln.get('_cols', {}).get('he', set())
        if hl <= 0 and hr <= 0 and not softl and not softr and _texty(cols, text_colours):
            ln['status'] = 'EDGE'
        return
    (el, er), (hl, hr) = ln['en_margins'], ln['he_margins']
    ew, hw = ln['en'][1] - ln['en'][0] + 1, ln['he'][1] - ln['he'][0] + 1
    if max(ew, hw) > WIDTH_FACTOR * min(ew, hw):
        # one shot shows something else here (a name the other build cannot draw, a page
        # caught at another moment): nothing to compare
        ln['status'] = 'UNPAIRED'
        return
    anchors = []
    if not softl and not softr:
        if abs(hr - el) <= tol:
            anchors.append('mirror')
        elif (en_start is not None and el != en_start and abs(hr - en_start) <= tol
              and hr == he_start):
            # English starts this line elsewhere than its other lines (a name it draws blank)
            # while Hebrew starts it with the others: the window's start is mirrored
            anchors.append('mirror')
        if abs(hl - er) <= tol:
            anchors.append('mirror-right')
    # centred: English nearly centred (a centring routine's rounding and a trailing space
    # can leave it a few px off) and Hebrew off centre by the same amount or its mirror
    en_centred = not softl and not softr and abs(el - er) <= CENTRE_SLACK
    if en_centred and min(abs((hl - hr) - (el - er)), abs((hl - hr) + (el - er))) <= 2 * tol:
        anchors.append('centre')
    if not softl and abs(hl - el) <= tol:
        anchors.append('in-place')
    if not softr and abs(hr - er) <= tol:
        anchors.append('in-place-right')
    ln['anchors'] = anchors
    # edge: Hebrew ink on a window's outermost column where English keeps a gap at both ends.
    # A mirrored line's start is the shadow column in Hebrew and the ink in English, so a
    # Hebrew 0 at the right against an English 1 at the left is the mirror, not an edge.
    if not softl and not softr and min(el, er) >= 1 and (hl <= 0 or (hr <= 0 and el >= 2)):
        st = 'EDGE'
    elif set(anchors) & MIRRORED:
        st = 'OK'
    elif anchors:
        st = 'IN-PLACE'
    elif softl or softr:
        st = 'UNKNOWN'
    elif abs(el - er) <= tol and min(el, er) > tol:
        st = 'CENTRE-OFF'
    else:
        st = 'MIRROR-MISMATCH'
    # rows: the scripts differ by up to 3 px at the top (Latin capitals and accents against
    # Hebrew bodies, the lamed) and at the bottom (descenders of both, Hebrew finals), but a line
    # drawn at the same y never moves both ends the same way by more than that
    dt = ln['he_rows'][0] - ln['en_rows'][0]
    db = ln['he_rows'][1] - ln['en_rows'][1]
    if st in ('OK', 'IN-PLACE') and ((dt > ROW_TOL and db > ROW_TOL) or (dt < -ROW_TOL and db < -ROW_TOL)):
        st = 'ROW-SHIFT'
    ln['status'] = st


def _texty(cols, text_colours):
    """Ink in at most MAX_INK_COLOURS colours, at least half of them colours of the screen's
    Hebrew text (a window's shadow may differ from the other windows'; a sprite's colours are
    not text colours)."""
    return (bool(cols) and len(cols) <= MAX_INK_COLOURS and
            2 * len(cols & (text_colours or set())) >= len(cols))


def paired_colours(line_lists):
    """The colours of the Hebrew ink of every line that has English ink too."""
    out = set()
    for lines in line_lists:
        for ln in lines:
            if 'en' in ln and 'he' in ln:
                out |= ln.get('_cols', {}).get('he', set())
    return out


def analyse_window(en, he, w, tol=TOL, lines=None, text_colours=None):
    """Lines, margins and the class of one window (sets w.lines, w.cls, w.notes). LINES may be
    measure_lines' result, TEXT_COLOURS the screen's paired Hebrew text colours."""
    if lines is None:
        lines = measure_lines(en, he, w)
    if text_colours is None:
        text_colours = paired_colours([lines])
    both = [ln for ln in lines if 'en' in ln and 'he' in ln]
    en_start = _mode([ln['en_margins'][0] for ln in both])
    he_start = _mode([ln['he_margins'][1] for ln in both])
    for ln in lines:
        if 'he' in ln:
            classify_line(ln, w, tol, en_start, he_start, text_colours)
    w.lines = lines
    notes = []
    checked = [ln for ln in lines if ln['status'] not in UNCHECKED]
    if not checked:
        cls = 'UNKNOWN'
        notes.append('no line to compare: %s' % (', '.join(sorted(set(ln['status'] for ln in lines))) or 'no ink'))
    else:
        cls = min((ln['status'] for ln in checked), key=lambda s: RANK[s])
        for ln in checked:
            if 'en' not in ln:
                notes.append('line %d: Hebrew ink on a band English leaves empty is cut at both sides'
                             % (lines.index(ln) + 1))
        only_m = [ln for ln in checked if set(ln.get('anchors', ())) & MIRRORED
                  and not set(ln['anchors']) & IN_PLACE]
        only_i = [ln for ln in checked if set(ln.get('anchors', ())) & IN_PLACE
                  and not set(ln['anchors']) & MIRRORED]
        if only_m and only_i and RANK[cls] > RANK['MIRROR-MISMATCH']:
            cls = 'MIRROR-MISMATCH'
            notes.append('lines %s keep the English start while lines %s are mirrored' % (
                ','.join(str(lines.index(ln) + 1) for ln in only_i),
                ','.join(str(lines.index(ln) + 1) for ln in only_m)))
        elif only_i and not only_m and cls == 'OK':
            cls = 'IN-PLACE'
        if cls != 'IN-PLACE' and 'left' not in w.soft and 'right' not in w.soft:
            for ln in checked:
                ce, ch = ln.get('cursor', (None, None))
                # a cursor that starts the English line (a second column's cursor stands
                # inside the line in both builds)
                if not (ce and ch and ce[2] == 'right' and ce[0] <= ln['en'][0] + 1):
                    continue
                if ch[2] == 'right':
                    notes.append('line %d: the Hebrew cursor points right, as in English' % (lines.index(ln) + 1))
                elif ch[1] < ln['he'][1] - 1:
                    notes.append('line %d: the Hebrew cursor does not end its line' % (lines.index(ln) + 1))
                else:
                    continue
                if RANK[cls] > RANK['MIRROR-MISMATCH']:
                    cls = 'MIRROR-MISMATCH'
    if checked and cls != 'IN-PLACE' and any(set(ln.get('anchors', ())) & MIRRORED for ln in checked):
        for c in fixed_cursors(en, he, w):
            notes.append('the cursor at (%d,%d) points right in the same place as in English, '
                         'while the window\'s text is mirrored' % (c[0], c[2]))
            if RANK[cls] > RANK['MIRROR-MISMATCH']:
                cls = 'MIRROR-MISMATCH'
    soft = [s for s in w.soft if s in ('left', 'right')]
    if soft:
        notes.append('%s side not a frame (open art or the screen edge): only margins against the '
                     'other side are measured' % '/'.join(soft))
    w.cls, w.notes = cls, notes
    return w


# --------------------------------------------------------------------------- pair

def analyse_pair(en, he, tol=TOL):
    """Check one pair. Returns {'windows': [...], 'unknown': [...], 'other': n}."""
    if (en.w, en.h) != (he.w, he.h):
        raise ValueError('sizes differ: %dx%d and %dx%d' % (en.w, en.h, he.w, he.h))
    if all(a == b for a, b in zip(en.rows, he.rows)):
        return {'windows': [], 'unknown': [], 'other': 0, 'identical': True}
    windows, unknown, other, small = find_windows(en, he)
    measured = [measure_lines(en, he, w) for w in windows]
    text_colours = paired_colours(measured)
    out = []
    for w, lines in zip(windows, measured):
        analyse_window(en, he, w, tol, lines, text_colours)
        for ln in lines:
            ln.pop('_cols', None)
        rec = {'rect': list(w.rects['he']), 'paper': '%06X' % w.paper, 'class': w.cls,
               'notes': w.notes, 'soft': w.soft, 'lines': w.lines}
        if w.rects['en'] != w.rects['he']:
            rec['rect_en'] = list(w.rects['en'])
        out.append(rec)
    # a paper rectangle too small to be a window (a gap between two frames) that shows more
    # Hebrew ink than English: text drawn past its window, seen through the gap
    for w in small:
        ne, nh, cols = fragment_ink(en, he, w)
        if nh >= FRAGMENT_MIN and nh >= 2 * ne and _texty(cols, text_colours):
            out.append({'rect': list(w.rect), 'paper': '%06X' % w.paper, 'class': 'EDGE',
                        'notes': ['%d px of Hebrew ink, %d of English, in a %dx%d gap outside every window'
                                  % (nh, ne, w.rect[2] - w.rect[0] + 1, w.rect[3] - w.rect[1] + 1)],
                        'soft': [], 'lines': []})
    unk = []
    for s in unknown:
        unk.append({'rect': list(s['box']), 'class': 'UNKNOWN', 'paper_share': round(s['share'], 2),
                    'notes': ['no paper: text over art (paper share %.2f)' % s['share']]})
    return {'windows': out, 'unknown': unk, 'other': len(other)}


def fragment_ink(en, he, w):
    """Differing non-paper pixels inside a small rectangle, per shot, and the Hebrew ones'
    colours."""
    x0, y0, x1, y1 = w.rect
    P = w.paper
    ne = nh = 0
    cols = set()
    for y in range(y0, y1 + 1):
        a, b = en.rows[y], he.rows[y]
        for x in range(x0, x1 + 1):
            if a[x] != b[x]:
                ne += a[x] != P
                if b[x] != P:
                    nh += 1
                    cols.add(b[x])
    return ne, nh, cols


# --------------------------------------------------------------------------- crops

MAGENTA, RED, GREY = 0xFF00FF, 0xFF2020, 0x404040


def crop_pair(en, he, rect, path, scale=3, pad=6, marks=(), rect_en=None):
    """EN crop | HE crop around the window (+PAD px), SCALEx, each shot's window outlined in
    magenta just outside it and each marked band (ya, yb) flagged in red at the crop's left."""
    rects = (rect_en or rect, rect)
    cx0 = max(0, min(r[0] for r in rects) - pad)
    cy0 = max(0, min(r[1] for r in rects) - pad)
    cx1 = min(en.w - 1, max(r[2] for r in rects) + pad)
    cy1 = min(en.h - 1, max(r[3] for r in rects) + pad)
    cw, chh = cx1 - cx0 + 1, cy1 - cy0 + 1
    gap = 4
    W = (cw * scale) * 2 + gap
    out = [[GREY] * W for _ in range(chh * scale)]
    for k, (s, (x0, y0, x1, y1)) in enumerate(zip((en, he), rects)):
        ox = k * (cw * scale + gap)
        for y in range(chh):
            src = s.rows[cy0 + y]
            for x in range(cw):
                v = src[cx0 + x]
                for dy in range(scale):
                    row = out[y * scale + dy]
                    for dx in range(scale):
                        row[ox + x * scale + dx] = v
        L, R = (x0 - cx0) * scale - 1, (x1 - cx0 + 1) * scale
        T, B = (y0 - cy0) * scale - 1, (y1 - cy0 + 1) * scale
        for yy in range(max(0, T), min(chh * scale, B + 1)):
            for xx in (L, R):
                if 0 <= xx < cw * scale:
                    out[yy][ox + xx] = MAGENTA
        for xx in range(max(0, L), min(cw * scale, R + 1)):
            for yy in (T, B):
                if 0 <= yy < chh * scale:
                    out[yy][ox + xx] = MAGENTA
        for (ya, yb) in marks:
            for yy in range((ya - cy0) * scale, (yb - cy0 + 1) * scale):
                for xx in range(0, min(2, cw * scale)):
                    if 0 <= yy < chh * scale:
                        out[yy][ox + xx] = RED
    write_png(path, out)


# --------------------------------------------------------------------------- CLI

def _flag_marks(win):
    return [tuple(ln['rows']) for ln in win.get('lines', [])
            if ln.get('status') not in ('OK', 'IN-PLACE') + UNCHECKED]


def write_crops(en, he, res, outdir, stem, include_inplace=True):
    os.makedirs(outdir, exist_ok=True)
    k = 0
    for win in res['windows'] + res['unknown']:
        if win['class'] == 'OK' or (win['class'] == 'IN-PLACE' and not include_inplace):
            continue
        k += 1
        name = '%s__w%d_%s.png' % (stem, k, win['class'])
        crop_pair(en, he, win['rect'], os.path.join(outdir, name), marks=_flag_marks(win),
                  rect_en=win.get('rect_en'))
        win['crop'] = name


def describe(win):
    x0, y0, x1, y1 = win['rect']
    s = '%-15s (%d,%d)-(%d,%d)' % (win['class'], x0, y0, x1, y1)
    bits = list(win.get('notes', []))
    for i, ln in enumerate(win.get('lines', [])):
        if ln.get('status') in ('OK', 'IN-PLACE') + UNCHECKED:
            continue
        if 'en_margins' not in ln:
            bits.append('line %d %s: no English ink, HE L%d R%d rows %d-%d' % (
                i + 1, ln['status'], ln['he_margins'][0], ln['he_margins'][1], ln['he_rows'][0], ln['he_rows'][1]))
            continue
        bits.append('line %d %s: EN L%d R%d rows %d-%d, HE L%d R%d rows %d-%d' % (
            i + 1, ln['status'], ln['en_margins'][0], ln['en_margins'][1], ln['en_rows'][0], ln['en_rows'][1],
            ln['he_margins'][0], ln['he_margins'][1], ln['he_rows'][0], ln['he_rows'][1]))
    if bits:
        s += ': ' + '; '.join(bits)
    return s


def cmd_pair(a):
    en, he = read_png(a.en), read_png(a.he)
    res = analyse_pair(en, he, a.tol)
    if a.out:
        write_crops(en, he, res, a.out, os.path.splitext(os.path.basename(a.he))[0], include_inplace=True)
    if a.json:
        print(json.dumps(res, indent=1))
    else:
        for win in res['windows'] + res['unknown']:
            print(describe(win))
            if a.verbose:
                for i, ln in enumerate(win.get('lines', [])):
                    print('    line %d %s' % (i + 1, json.dumps(ln)))
    return 1 if any(w['class'] not in ('OK', 'IN-PLACE') for w in res['windows'] + res['unknown']) else 0


def _pairs(en_dir, he_dir, only=None):
    out, missing = [], []
    for tour in sorted(os.listdir(he_dir)):
        hd = os.path.join(he_dir, tour)
        if not os.path.isdir(hd) or tour.startswith('_'):
            continue
        if only and not re.search(only, tour):
            continue
        for f in sorted(os.listdir(hd)):
            if not f.endswith('.png') or f.startswith('_'):
                continue
            ep = os.path.join(en_dir, tour, f)
            if os.path.exists(ep):
                out.append((tour, f, ep, os.path.join(hd, f)))
            else:
                missing.append('%s/%s' % (tour, f))
    return out, missing


def _work(job):
    tour, f, ep, hp, tol, crops = job
    en, he = read_png(ep), read_png(hp)
    res = analyse_pair(en, he, tol)
    stem = '%s__%s' % (tour, os.path.splitext(f)[0])
    write_crops(en, he, res, crops, stem)
    return tour, f, res


def cmd_tours(a):
    pairs, missing = _pairs(a.en_dir, a.he_dir, a.only)
    crops = os.path.join(a.out, 'crops')
    os.makedirs(crops, exist_ok=True)
    jobs = [(t, f, ep, hp, a.tol, crops) for (t, f, ep, hp) in pairs]
    if a.jobs > 1:
        import multiprocessing
        with multiprocessing.Pool(a.jobs) as pool:
            results = pool.map(_work, jobs, chunksize=8)
    else:
        results = [_work(j) for j in jobs]
    report = {'en': os.path.abspath(a.en_dir), 'he': os.path.abspath(a.he_dir), 'tol': a.tol,
              'pairs': len(pairs), 'missing_en': missing, 'shots': {}}
    counts, groups, other = Counter(), {}, 0
    listing = []
    for tour, f, res in results:
        report['shots']['%s/%s' % (tour, f)] = res
        other += res.get('other', 0)
        for win in res['windows'] + res['unknown']:
            counts[win['class']] += 1
            if win['class'] == 'OK':
                continue
            text = '%s/%s  %s%s' % (tour, f, describe(win), '  [crops/%s]' % win['crop'] if win.get('crop') else '')
            listing.append((win['class'], text))
            # the same window in several shots of a tour is one group
            groups.setdefault((win['class'], tour, tuple(win['rect'])), []).append((f, win))
    report['counts'] = dict(counts)
    report['other_regions'] = other
    with open(os.path.join(a.out, 'report.json'), 'w') as fh:
        json.dump(report, fh, indent=1, sort_keys=True)
    head = ['textalign: %d pairs (%s vs %s), tolerance %d px' % (len(pairs), a.en_dir, a.he_dir, a.tol),
            'no English shot for %d Hebrew shots%s' % (len(missing), ': ' + ', '.join(missing) if missing else ''),
            'windows per class: ' + ', '.join('%s %d' % (c, counts.get(c, 0)) for c in CLASSES),
            'differing regions that are not text (sprites, a window drawn elsewhere), not checked: %d' % other,
            '']
    out = list(head)
    for c in CLASSES:
        if c == 'OK':
            continue
        sel = sorted((k, v) for k, v in groups.items() if k[0] == c)
        out.append('== %s: %d windows in %d groups (one group = one window of one tour, in N shots)'
                   % (c, counts.get(c, 0), len(sel)))
        for (cls, tour, rect), items in sel:
            f, win = items[0]
            out.append('%3d  %s/%s  %s%s' % (len(items), tour, f, describe(win),
                                              '  [crops/%s]' % win['crop'] if win.get('crop') else ''))
        out.append('')
    with open(os.path.join(a.out, 'summary.txt'), 'w') as fh:
        fh.write('\n'.join(out) + '\n')
    with open(os.path.join(a.out, 'windows.txt'), 'w') as fh:
        for c in CLASSES:
            fh.write(''.join(t + '\n' for cls, t in listing if cls == c))
    print('\n'.join(head[:4]))
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split('\n\n')[0])
    sub = ap.add_subparsers(dest='cmd')
    p = sub.add_parser('pair', help='check one English/Hebrew pair')
    p.add_argument('en')
    p.add_argument('he')
    p.add_argument('--out', help='write crop pairs here (every window that is not OK)')
    p.add_argument('--tol', type=int, default=TOL)
    p.add_argument('--json', action='store_true')
    p.add_argument('-v', '--verbose', action='store_true')
    p = sub.add_parser('tours', help='check every shot of two tour runs')
    p.add_argument('en_dir')
    p.add_argument('he_dir')
    p.add_argument('out')
    p.add_argument('--only', help='regex on tour names')
    p.add_argument('--tol', type=int, default=TOL)
    p.add_argument('--jobs', type=int, default=1)
    a = ap.parse_args(argv)
    if a.cmd == 'pair':
        return cmd_pair(a)
    if a.cmd == 'tours':
        return cmd_tours(a)
    ap.print_help()
    return 2


if __name__ == '__main__':
    sys.exit(main())
