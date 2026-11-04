#!/usr/bin/env python3
"""Pixel operations used by make_coreui.py: erase English text, draw Hebrew bitmaps."""

import heb

DIRS_RDB = ((1, 0), (0, 1), (1, 1))          # shadow right, below, below-right (the fonts' rule)
DIRS_RB = ((1, 0), (0, 1))
DIRS_8 = tuple((dx, dy) for dy in (-1, 0, 1) for dx in (-1, 0, 1) if dx or dy)


def fill_from_column(c, x0, x1, y0, y1, src_x):
    """Rebuild a horizontally uniform background: every column of the rect copies column src_x."""
    col = [c.get(src_x, y) for y in range(y0, y1 + 1)]
    for x in range(x0, x1 + 1):
        for i, y in enumerate(range(y0, y1 + 1)):
            c.put(x, y, col[i])


def fill_rect(c, x0, x1, y0, y1, v):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            c.put(x, y, v(x, y) if callable(v) else v)


def replace_in_rect(c, x0, x1, y0, y1, mapping):
    """Swap palette indices inside a rect (e.g. text colours -> background)."""
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            v = c.get(x, y)
            if v in mapping:
                c.put(x, y, mapping[v](x, y) if callable(mapping[v]) else mapping[v])


def ink_points(bm, x, y):
    for j, row in enumerate(bm):
        for i, ch in enumerate(row):
            if ch == '#':
                yield x + i, y + j, j


def draw(c, bm, x, y, fg, shadow=None, dirs=DIRS_RDB, outline=None, outline_dirs=DIRS_8, clip=None):
    """Draw bitmap rows at (x, y). fg: index or f(x, y, row) -> index. shadow/outline: index or f(x, y).
    clip: (x0, x1, y0, y1) inclusive; pixels outside are not touched."""
    pts = list(ink_points(bm, x, y))
    ink = {(px, py) for px, py, _ in pts}

    def ok(px, py):
        if not (0 <= px < c.width and 0 <= py < c.height):
            return False
        if clip and not (clip[0] <= px <= clip[1] and clip[2] <= py <= clip[3]):
            return False
        return True

    def val(v, px, py):
        return v(px, py) if callable(v) else v

    if outline is not None:
        for px, py, _ in pts:
            for dx, dy in outline_dirs:
                q = (px + dx, py + dy)
                if q not in ink and ok(*q):
                    c.put(q[0], q[1], val(outline, *q))
    if shadow is not None:
        for px, py, _ in pts:
            for dx, dy in dirs:
                q = (px + dx, py + dy)
                if q not in ink and ok(*q):
                    c.put(q[0], q[1], val(shadow, *q))
    for px, py, row in pts:
        if ok(px, py):
            c.put(px, py, fg(px, py, row) if callable(fg) else fg)


def place(bm, box_x0, box_x1, align='center'):
    """Left x for a bitmap inside [box_x0, box_x1] (inclusive)."""
    w = heb.width(bm)
    if align == 'left':
        return box_x0
    if align == 'right':
        return box_x1 - w + 1
    return box_x0 + (box_x1 - box_x0 + 1 - w) // 2


def text(word, setname, gap=1, **kw):
    return heb.layout(word, setname, gap=gap, **kw)
