"""Shared helpers for the side group: glyph sets, kerned layout, fitting, painting."""
from gfx import *
import heb, semibold, draw
heb.derive('W4_7', 3, False, name='M3')
heb.derive('W4_8', 9, False, name='N9')
heb.derive('W4_7', 6, False, name='M6')
heb.derive('W5_8', 9, True, name='B9m')
heb.derive('W6_8', 13, True, name='B13w')
heb.derive('W6_8', 11, True, name='B11w')
semibold.derive_sb('W4_8', 4, 'S4')
semibold.derive_sb('W5_8', 7, 'S7m')

NARROW = set('יון')


def punct(setname, ch, asc, desc):
    """Geresh, gershayim, colon, period and hyphen drawn to the set's body height."""
    h = heb.META[setname]['h']
    n = asc + h + desc
    rows = [['.'] for _ in range(n)]
    tick = 2 if h >= 6 else 1
    if ch in "'’":
        for y in range(tick): rows[asc + y] = ['#']
    elif ch == '”':
        rows = [['.', '.', '.'] for _ in range(n)]
        for y in range(tick): rows[asc + y] = ['#', '.', '#']
    elif ch == ':':
        a, b = asc + (h - 1) // 3, asc + h - 1 - (h - 1) // 3
        if b - a < 2: a, b = asc + max(0, h - 4), asc + h - 1
        rows[a] = ['#']; rows[b] = ['#']
    elif ch == '.':
        rows[asc + h - 1] = ['#']
    elif ch == '-':
        rows = [['.', '.', '.'] for _ in range(n)]
        rows[asc + h // 2] = ['#', '#', '#']
    else:
        raise KeyError(ch)
    return [''.join(r) for r in rows]


def glyph_rows(setname, ch, asc, desc):
    if ch not in heb.SETS[setname]:
        return punct(setname, ch, asc, desc)
    return heb.body_glyph(setname, ch, asc, desc)


def lay(text, setname, gap=2, asc=1, desc=2, ngap=None, space=None):
    """Right-to-left layout with per-pair gaps: `ngap` next to narrow letters (י ו ן)."""
    ngap = gap if ngap is None else ngap
    space = (gap + 2) if space is None else space
    chars = list(text)
    vis = list(reversed(chars))
    pieces = [None if c == ' ' else glyph_rows(setname, c, asc, desc) for c in vis]
    n = len(next(p for p in pieces if p))
    out = [''] * n
    for i, p in enumerate(pieces):
        if p is None:
            out = [r + '.' * space for r in out]
            continue
        out = [out[y] + p[y] for y in range(n)]
        if i < len(pieces) - 1 and pieces[i + 1] is not None:
            g = ngap if (vis[i] in NARROW or vis[i + 1] in NARROW) else gap
            out = [r + '.' * g for r in out]
    return out


def fit(text, setname, maxw, gaps=((2, 2), (2, 1), (1, 1), (1, 0)), extra=1, **kw):
    """First layout whose width + extra (shadow) fits maxw."""
    for g, ng in gaps:
        m = lay(text, setname, g, ngap=ng, **kw)
        if len(m[0]) + extra <= maxw:
            return m
    raise ValueError('%s does not fit %d in %s (%d)' % (text, maxw, setname, len(m[0]) + extra))


def width(m):
    return len(m[0])


def ink_rows(m):
    ys = [i for i, r in enumerate(m) if '#' in r]
    return ys[0], ys[-1]


def clear(f, x0, y0, x1, y1, vals, to):
    draw.replace(f, x0, y0, x1, y1, {v: to for v in vals})


def save_and_pair(f, P, zoom=4, region=None):
    f.save(gpaths.write_target(P))
    return pair(P, zoom, region=region)


class TileStrip:
    """A temporary image made of tiles of `f` (rows of tile numbers), written back with put_back()."""
    def __init__(self, f, rows):
        self.f, self.rows = f, rows
        self.width, self.height = 8 * len(rows[0]), 8 * len(rows)
        self.palette = f.palette
        self.px = [[0] * self.width for _ in range(self.height)]
        tw = f.width // 8
        for j, r in enumerate(rows):
            for i, t in enumerate(r):
                for y in range(8):
                    for x in range(8):
                        self.px[j * 8 + y][i * 8 + x] = f.get((t % tw) * 8 + x, (t // tw) * 8 + y)

    def get(self, x, y): return self.px[y][x]
    def put(self, x, y, v): self.px[y][x] = v

    def put_back(self):
        tw = self.f.width // 8
        for j, r in enumerate(self.rows):
            for i, t in enumerate(r):
                for y in range(8):
                    for x in range(8):
                        self.f.put((t % tw) * 8 + x, (t // tw) * 8 + y, self.px[j * 8 + y][i * 8 + x])


def erase_rows(f, x0, y0, x1, y1, remove, ref_x):
    """Inside the rect, pixels whose index is in `remove` take the colour of column ref_x on the
    same row (for backgrounds made of horizontal stripes)."""
    for y in range(y0, y1 + 1):
        bg = f.get(ref_x, y)
        for x in range(x0, x1 + 1):
            if f.get(x, y) in remove:
                f.put(x, y, bg)
