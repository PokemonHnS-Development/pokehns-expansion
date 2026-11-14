#!/usr/bin/env python3
"""Hebrew pixel text for the coreui graphics.

Glyph sources (one pixel style everywhere):
  - the font designs in tools/hebrew/fonts/hebrew_glyph_designs.txt (sets W6_7, W5_7, W4_7, ...),
    i.e. exactly the strokes installed in graphics/fonts/latin_*.png;
  - coreui_mini_designs.txt next to this file: 4-, 5- and 6-row letters drawn for labels that are
    shorter than the fonts' 7-row body (HP bar, move-info window, status tags). They follow the
    W4_7 shapes with rows removed.

A glyph is a list of strings, '#' = ink, '.' = none, all rows of one set have the same height
(the set's line box: body plus ascender/descender rows). Text is laid out right to left: the
first letter of the logical string is drawn at the right end.
"""

import os
import re

HERE = os.path.dirname(os.path.abspath(__file__))
FONT_DESIGNS = os.path.join(os.path.dirname(os.path.dirname(HERE)), 'fonts', 'hebrew_glyph_designs.txt')
MINI_DESIGNS = os.path.join(HERE, 'coreui_mini_designs.txt')

FINALS = {'כ': 'ך', 'מ': 'ם', 'נ': 'ן', 'פ': 'ף', 'צ': 'ץ'}


def _parse(path):
    sets, aliases = {}, {}
    cur = None
    glyph = None
    for line in open(path, encoding='utf-8'):
        line = line.rstrip('\n')
        if not line.strip():
            continue
        if re.match(r'^[#.]+(\s+\d+)?\s*$', line):
            if glyph is not None:
                glyph.append(line.split()[0])
            continue
        if line.startswith('#'):
            continue
        if line.startswith('@set '):
            cur = sets.setdefault(line.split()[1], {})
            glyph = None
            continue
        if line.startswith('@alias '):
            parts = line.split()
            aliases[parts[1]] = parts[2]
            cur = None
            continue
        if line.startswith('@glyph '):
            if cur is None:
                glyph = None
                continue
            ch = line.split()[1]
            glyph = cur.setdefault(ch, [])
            continue
        if line.startswith('@'):
            glyph = None
            continue
    return sets, aliases


def load_sets():
    sets, _ = _parse(FONT_DESIGNS)
    if os.path.exists(MINI_DESIGNS):
        mini, _ = _parse(MINI_DESIGNS)
        sets.update(mini)
    return sets


SETS = load_sets()


def trim(rows):
    """Trim empty columns on both sides (keep all rows)."""
    cols = [x for x in range(max(len(r) for r in rows)) if any(x < len(r) and r[x] == '#' for r in rows)]
    if not cols:
        return [''] * len(rows)
    a, b = cols[0], cols[-1]
    return [r.ljust(b + 1, '.')[a:b + 1] for r in rows]


def glyph(setname, ch):
    g = SETS[setname].get(ch)
    if g is None:
        raise KeyError('%s has no glyph %r' % (setname, ch))
    if ch == ' ':
        return g
    return trim(g)


def layout(text, setname, gap=1, space=None, kern=None, rows=None):
    """Bitmap rows ('#'/'.') of `text` laid out right to left.

    gap: blank columns between letters. space: width of ' ' (default 2*gap+1).
    kern: dict {(left_char, right_char): delta} applied between visual neighbours.
    rows: (first, last) row range of the set to keep (crop the line box).
    """
    glyphs = []
    for ch in text:
        if ch == ' ':
            w = space if space is not None else gap * 2 + 1
            glyphs.append((ch, ['.' * w] * len(next(iter(SETS[setname].values())))))
        else:
            glyphs.append((ch, glyph(setname, ch)))
    glyphs.reverse()                     # visual order, left to right
    h = len(glyphs[0][1])
    out = [''] * h
    for i, (ch, g) in enumerate(glyphs):
        if i:
            g_gap = gap
            if ch == ' ' or glyphs[i - 1][0] == ' ':
                g_gap = 0
            if kern:
                g_gap += kern.get((ch, glyphs[i - 1][0]), 0)
            out = [r + '.' * g_gap for r in out]
        out = [out[y] + g[y] for y in range(h)]
    if rows:
        out = out[rows[0]:rows[1] + 1]
    return out


def ink_rows(bm):
    ys = [y for y, r in enumerate(bm) if '#' in r]
    return (ys[0], ys[-1]) if ys else None


def crop_rows(bm):
    r = ink_rows(bm)
    return bm[r[0]:r[1] + 1] if r else bm


def width(bm):
    return len(bm[0]) if bm else 0


def show(bm):
    return '\n'.join(bm)


# ---------------------------------------------------------------- derived sets
GERSHAYIM = {'”': ['#.#', '#.#'], "'": ['#', '#']}


def _derive(src, name, first, last, body_top):
    """Crop rows [first, last] (indices into the 13-row design, row 0 = cell row 2) of every glyph of
    set `src` into a new set; punctuation marks are put on the body's top rows (index body_top)."""
    out = {}
    for ch, rows in SETS[src].items():
        out[ch] = rows[first:last + 1]
    h = last - first + 1
    for ch, marks in GERSHAYIM.items():
        w = len(marks[0])
        rows = ['.' * w] * h
        for i, m in enumerate(marks):
            rows[body_top + i] = m
        out[ch] = rows
    SETS[name] = out


# C7: W4_7 (small_narrower letters, body rows 4-10) with a 1-row ascender and a 1-row descender.
_derive('W4_7', 'C7', 1, 9, 1)
# C7W: the same crop of W5_7 (small font letters, 5 columns).
_derive('W5_7', 'C7W', 1, 9, 1)
# N8: W5_8 (narrow font, body rows 4-11) with 2 ascender and 2 descender rows.
_derive('W5_8', 'N8', 0, 12, 2)
_derive('W6_8', 'N8W', 0, 12, 2)
