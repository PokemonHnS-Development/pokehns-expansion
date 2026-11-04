"""Hebrew lettering for the Pokegear graphics.

Every font here comes from the game's own Hebrew glyphs (graphics/fonts/latin_*.png cells
0x3A-0x4F, 0x50, 0x5E-0x61) so one pixel style runs through the ROM:

  GEAR    latin_short shapes (5-6 px wide, 7-row body, 2-row ascender for lamed, 2-row
          descenders), drawn with the Pokegear alphabet's 1-px drop shadow (right, down, diagonal).
  HALO    the same latin_short shapes, drawn dark with a 1-px light halo (condition graph labels).
  BOLD    latin_short shapes with every stroke doubled (each pixel also paints x+1, each row twice),
          for the bold Pokegear title bar.
  TINY    latin_small shapes with one body row removed (4 px wide, 6-row body), no shadow, for the
          4x6 legend lettering (radio TUNING button, region-map legend).

Masks are lists of strings ('#' ink, '.' empty); `top` is the first row relative to the baseline
(baseline row = 0, body rows are -6..0 for a 7-row body).
"""
import os
import sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.dirname(HERE))
import gpaths  # noqa: E402
from harvest import harvest  # noqa: E402

FONTDIR = os.path.join(gpaths.TREE, 'graphics', 'fonts') + os.sep
SHORT = harvest(FONTDIR + 'latin_short.png', 10)
SMALL = harvest(FONTDIR + 'latin_small.png', 10)


def _drop_body_row(rows, top):
    """Remove one row from the 7-row body (rows -6..0): the middle-most row that repeats its neighbour."""
    body = [i for i in range(len(rows)) if -6 <= top + i <= 0]
    cands = [i for i in body[1:-1] if rows[i] == rows[i - 1] or rows[i] == rows[i + 1]]
    if not cands:
        cands = body[1:-1]
    mid = (body[0] + body[-1]) / 2.0
    i = min(cands, key=lambda k: (abs(k - mid), k))
    return rows[:i] + rows[i + 1:], top + 1


def _tiny():
    out = {}
    for ch, (rows, top) in SMALL.items():
        r, t = _drop_body_row(rows, top)
        out[ch] = (r, t)
    return out


TINY = _tiny()
# The small-font qof has a 1-row tail; keep a 2-row tail in TINY so it reads as qof, not he.
TINY['ק'] = (['####', '...#', '...#', '#.#.', '#.#.', '#...', '#...'], -5)
TINY['ן'] = (['#.', '.#', '.#', '.#', '.#', '.#', '.#', '.#'], -5)


def _bold():
    out = {}
    for ch, (rows, top) in SHORT.items():
        w = len(rows[0]) + 1
        new = []
        for r in rows:
            line = ['.'] * w
            for x, c in enumerate(r):
                if c == '#':
                    line[x] = line[x + 1] = '#'
            new.append(''.join(line))
            new.append(''.join(line))
        out[ch] = (new, top * 2 - 1)   # 7-row body -> 14 rows, baseline stays the last body row
    return out


NORMAL = harvest(FONTDIR + 'latin_normal.png', 11)


def _add_body_row(rows, top, body_top=-7):
    """Add one row to an 8-row body (rows body_top..0): repeat the middle-most row that already
    repeats a neighbour (a straight stem), so the letter grows without changing its shape.
    Letters that do not span the whole body (yod) keep their size and stay hung from the top."""
    body = [i for i in range(len(rows)) if body_top <= top + i <= 0]
    if top + body[0] != body_top or top + body[-1] != 0:
        return rows, top - 1      # not full height (yod): keep its size, hang it from the new top
    cands = [i for i in body[1:-1] if rows[i] == rows[i - 1] or rows[i] == rows[i + 1]] or body[1:-1]
    mid = (body[0] + body[-1]) / 2.0
    i = min(cands, key=lambda k: (abs(k - mid), k))
    return rows[:i + 1] + rows[i:], top - 1


def _tall():
    out = {}
    for ch, (rows, top) in NORMAL.items():
        out[ch] = _add_body_row(rows, top)
    return out


# TALL: latin_normal shapes grown to a 9-row body (rows -8..0), for the radio screen's 9-row
# embossed "RADIO" title.
TALL = _tall()

# TINY1: TINY with final nun's tail cut to one row, for 8-px-high strips whose English body
# already fills rows 1-6 (radio TUNING button, region-map legend sprites).
TINY1 = dict(TINY)
TINY1['ן'] = (['#.', '.#', '.#', '.#', '.#', '.#', '.#'], -5)

# MICRO: 3x5 letters for the condition screen's CANCEL plate (English is 2-3 px x 5 rows).
# Drawn from the latin_small shapes: het closed on both legs, he with its left leg detached,
# resh with the rounded top-right corner, zayin as head bar over a stem.
MICRO = {
    'ח': (['###', '#.#', '#.#', '#.#', '#.#'], -4),
    'ה': (['###', '..#', '#.#', '#.#', '#.#'], -4),
    'ר': (['##.', '..#', '..#', '..#', '..#'], -4),
    'ז': (['###', '.#.', '.#.', '.#.', '.#.'], -4),
}

BOLD = _bold()
# Doubling merges qof's leg into its body; keep a one-pixel gap between them.
BOLD['ק'] = (['######', '######', '....##', '....##', '....##', '....##', '...##.', '...##.',
              '##.##.', '##.##.', '##.##.', '##.##.', '##.##.', '##.##.', '##....', '##....', '##....'], -13)
GEAR = SHORT


def layout(text, font, space=4, gap=1):
    """Ink pixels of `text` set right to left: returns (set of (x, y)), width).
    x runs 0..width-1 left to right; y is relative to the baseline (0 = last body row)."""
    items = []
    for ch in text:
        if ch == ' ':
            items.append(None)
        else:
            items.append(font[ch])
    widths = [space if it is None else len(it[0][0]) for it in items]
    total = sum(widths) + gap * sum(1 for i in range(len(items) - 1)
                                    if items[i] is not None and items[i + 1] is not None)
    ink = set()
    cur = total  # right edge (exclusive)
    for i, it in enumerate(items):
        w = widths[i]
        if it is not None:
            rows, top = it
            x0 = cur - w
            for yy, r in enumerate(rows):
                for xx, c in enumerate(r):
                    if c == '#':
                        ink.add((x0 + xx, top + yy))
        cur -= w
        if it is not None and i + 1 < len(items) and items[i + 1] is not None:
            cur -= gap
    return ink, total


def drop_shadow(ink):
    sh = set()
    for (x, y) in ink:
        for d in ((1, 0), (0, 1), (1, 1)):
            q = (x + d[0], y + d[1])
            if q not in ink:
                sh.add(q)
    return sh


def halo(ink):
    """4-neighbour halo and diagonal-only corners, as the condition graph labels draw it."""
    near, corner = set(), set()
    for (x, y) in ink:
        for d in ((1, 0), (-1, 0), (0, 1), (0, -1)):
            q = (x + d[0], y + d[1])
            if q not in ink:
                near.add(q)
    for (x, y) in ink:
        for d in ((1, 1), (-1, 1), (1, -1), (-1, -1)):
            q = (x + d[0], y + d[1])
            if q not in ink and q not in near:
                corner.add(q)
    return near, corner


def extent(ink):
    ys = [y for _, y in ink]
    xs = [x for x, _ in ink]
    return min(xs), min(ys), max(xs), max(ys)


def show(text, font):
    ink, w = layout(text, font)
    x0, y0, x1, y1 = extent(ink)
    for y in range(y0, y1 + 1):
        print('%3d ' % y + ''.join('#' if (x, y) in ink else '.' for x in range(0, w)))


if __name__ == '__main__':
    for name, f in (('TINY', TINY), ('BOLD', BOLD)):
        print(name)
        for ch in 'אבגדהוזחטיכךלמםנןסעפףצץקרשת':
            rows, top = f[ch]
            print(ch, top, rows)
    show('כוונון', TINY)
    show('מרכז פוקימון', TINY)
    show('פוקיגיר', BOLD)
    show('תפריט ראשי', GEAR)
