"""Shared helpers for the Hebrew Pokédex graphics: word placement, tile write-back with
allocation of free tiles, PNG checks and RGB previews.

Builds on pdx.py (index-space canvases over tilesets) and heb.py (Hebrew words harvested from
the game's font PNGs).
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import heb  # noqa: E402
import inspect_fonts as F  # noqa: E402
from pdx import (BgCanvas, SpriteCanvas, english_png, english_bytes, tilemap,  # noqa: E402,F401
                 pack_tilemap, read_jasc, REPO)
import gpaths  # noqa: E402
from PIL import Image, ImageDraw  # noqa: E402

HG = 'graphics/pokedex/hgss/'
from pdx import OUT  # noqa: E402


# ---------------------------------------------------------------- words

def word(font, text):
    return heb.word(font, text)


def ink_x(bm):
    xs = [x for y in range(bm.h) for x in range(bm.w) if bm.px[y][x] == 1]
    return min(xs), max(xs)


def ink_y(bm):
    ys = [y for y in range(bm.h) for x in range(bm.w) if bm.px[y][x] == 1]
    return min(ys), max(ys)


def extent(bm, style):
    """Visible horizontal extent (relative to bitmap col 0) of a word drawn in `style`."""
    if style[0] == 'outline':
        a, b = ink_x(bm)
        return a - 1, b + 1
    if style[0] == 'ink':
        return ink_x(bm)
    return 0, bm.w - 1      # ink + shadow


def place(c, text, font, style, x0, x1, top, align='center', dx=0):
    """Draw `text` so that its visible extent sits inside [x0, x1] (screen x of canvas c).

    top: canvas y of the font cell's row 0. align: 'center', 'right' or 'left'.
    Returns (left, right) of the visible extent."""
    bm = word(font, text)
    a, b = extent(bm, style)
    w = b - a + 1
    if w > x1 - x0 + 1:
        raise ValueError('%r (%s) is %d px, box %d..%d holds %d' % (text, font, w, x0, x1, x1 - x0 + 1))
    if align == 'right':
        left = x1 - w + 1
    elif align == 'left':
        left = x0
    else:
        left = x0 + (x1 - x0 + 1 - w) // 2
    left += dx
    draw(c, bm, left - a, top, style)
    return left, left + w - 1


def draw(c, bm, ox, oy, style):
    """Stamp bitmap bm with its col 0 / cell row 0 at canvas (ox, oy)."""
    kind = style[0]
    pts = [(ox + x, oy + y, bm.px[y][x]) for y in range(bm.h) for x in range(bm.w) if bm.px[y][x]]
    inside = lambda x, y: 0 <= x < c.w and 0 <= y < c.h
    if kind == 'shadow':
        _, ink, sh = style
        for x, y, v in pts:
            if inside(x, y):
                c.want[y][x] = ink if v == 1 else sh
    elif kind == 'ink':
        _, ink = style
        for x, y, v in pts:
            if v == 1 and inside(x, y):
                c.want[y][x] = ink
    elif kind == 'outline':
        _, fill, outl = style[:3]
        rows = style[3] if len(style) > 3 else None     # optional (ymin, ymax) clip for the ring
        ink = {(x, y) for x, y, v in pts if v == 1}
        ring = set()
        for x, y in ink:
            for ddy in (-1, 0, 1):
                for ddx in (-1, 0, 1):
                    q = (x + ddx, y + ddy)
                    if q not in ink:
                        ring.add(q)
        for x, y in ring:
            if inside(x, y) and (rows is None or rows[0] <= y <= rows[1]):
                c.want[y][x] = outl
        for x, y in ink:
            if inside(x, y):
                c.want[y][x] = fill
    else:
        raise ValueError(kind)


def fill(c, x0, y0, x1, y1, v):
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            c.want[y][x] = v(x, y) if callable(v) else v


def recolor(c, x0, y0, x1, y1, mapping):
    """Replace indices inside a rectangle (e.g. erase text colours to the background)."""
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            v = c.want[y][x]
            if v in mapping:
                c.want[y][x] = mapping[v]


# ---------------------------------------------------------------- write-back

def _tile_xy(ts, t):
    tw = ts.width // 8
    return (t % tw) * 8, (t // tw) * 8


def tile_block(ts, t):
    ox, oy = _tile_xy(ts, t)
    return tuple(tuple(ts.get(ox + x, oy + y) for x in range(8)) for y in range(8))


def write_back(ts, canvases, free=(), allow_alloc=(), protect=(0,), dry=False):
    """Write every canvas's wanted pixels into ts.

    BG canvases are handled per tile: for each tile id, the wanted 8x8 contents (in tile
    orientation) of every position that uses it are grouped. One group keeps the tile (the group
    whose content equals the current tile if there is one, else the largest); the other groups
    get a tile from `free` and their tilemap entries are repointed -- only in canvases whose name
    is in `allow_alloc`, else it is an error. Tiles in `protect` must not change.
    Sprite canvases write straight through (conflicts are errors).
    Returns a log of allocations."""
    free = list(free)
    log = []
    bgs = [c for c in canvases if isinstance(c, BgCanvas)]
    sprites = [c for c in canvases if not isinstance(c, BgCanvas)]

    groups = {}       # tile -> {content: [(canvas, tx, ty)]}
    for c in bgs:
        for ty in range(c.h // 8):
            for tx in range(c.mw):
                e = c.entry(tx, ty)
                t = e & 0x3FF
                if t >= c.ntiles:
                    continue
                hf, vf = e & 0x400, e & 0x800
                blk = []
                for y in range(8):
                    row = []
                    for x in range(8):
                        sx = 7 - x if hf else x
                        sy = 7 - y if vf else y
                        row.append(c.want[ty * 8 + sy][tx * 8 + sx])
                    blk.append(tuple(row))
                groups.setdefault(t, {}).setdefault(tuple(blk), []).append((c, tx, ty))

    new_content = {}
    for t, g in sorted(groups.items()):
        cur = tile_block(ts, t)
        if len(g) == 1:
            content = next(iter(g))
            if content != cur:
                if t in protect:
                    raise RuntimeError('protected tile %d would change (%s)' % (t, [(c.name, x, y) for c, x, y in g[content]][:4]))
                new_content[t] = content
            continue
        keep = cur if cur in g else max(g, key=lambda k: len(g[k]))
        if keep != cur:
            if t in protect:
                raise RuntimeError('protected tile %d would change' % t)
            new_content[t] = keep
        for content, users in g.items():
            if content == keep:
                continue
            bad = [u for u in users if u[0].name not in allow_alloc]
            if bad:
                raise RuntimeError('tile %d is shared with different wanted content; users %s vs kept %s' % (
                    t, [(c.name, x, y) for c, x, y in users][:6], [(c.name, x, y) for c, x, y in g[keep]][:6]))
            if not free:
                raise RuntimeError('out of free tiles for tile %d' % t)
            nt = free.pop(0)
            new_content[nt] = content
            for c, tx, ty in users:
                i = ty * c.mw + tx
                old = c.entries[i]
                c.entries[i] = (old & ~0x3FF) | nt     # keep palette and flip bits: content is in tile orientation
            log.append((t, nt, [(c.name, tx, ty) for c, tx, ty in users]))

    if dry:
        return log
    for t, content in new_content.items():
        ox, oy = _tile_xy(ts, t)
        for y in range(8):
            for x in range(8):
                ts.put(ox + x, oy + y, content[y][x])

    put = {}
    for c in sprites:
        for y in range(c.h):
            for x in range(c.w):
                if c.want[y][x] != c.orig[y][x]:
                    p = c.where(x, y)
                    if p in put and put[p] != c.want[y][x]:
                        raise RuntimeError('sprite conflict at %s' % (p,))
                    put[p] = c.want[y][x]
    for (px, py), v in put.items():
        ts.put(px, py, v)
    return log


def verify(canvases, ts):
    bad = []
    for c in canvases:
        for y in range(c.h):
            for x in range(c.w):
                if c.read(x, y, ts) != c.want[y][x]:
                    bad.append((c.name, x, y, c.read(x, y, ts), c.want[y][x]))
    return bad


def check_png(path, ref):
    """Same size, bit depth, and byte-identical non-IDAT chunks (PLTE, tRNS, ...) as ref."""
    new = F.FontPng.load(path)
    problems = []
    if (new.width, new.height, new.bit_depth) != (ref.width, ref.height, ref.bit_depth):
        problems.append('size/depth %s vs %s' % ((new.width, new.height, new.bit_depth),
                                                 (ref.width, ref.height, ref.bit_depth)))
    if new._before != ref._before or new._after != ref._after:
        problems.append('non-IDAT chunks differ')
    extra = set(new.pixels) - set(ref.pixels)
    if extra:
        problems.append('indices the English file never used: %s' % sorted(extra))
    if new.bit_depth == 4 or max(new.pixels) < 16:
        pass
    return problems


# ---------------------------------------------------------------- previews

GREY = (72, 72, 72)


def rgb_bg(c, pal, ts=None, base=None):
    """RGB image of a BG canvas (index 0 = transparent over `base` or grey)."""
    im = base.copy() if base else Image.new('RGB', (c.w, c.h), GREY)
    px = im.load()
    for y in range(min(c.h, im.size[1])):
        for x in range(min(c.w, im.size[0])):
            v = c.read(x, y, ts) if ts is not None else c.want[y][x]
            if not v:
                continue
            bank = c.entry(x // 8, y // 8) >> 12
            i = bank * 16 + v
            px[x, y] = tuple(pal[i][:3]) if i < len(pal) else (255, 0, 255)
    return im


def rgb_grid(grid, pal, base=None, at=(0, 0)):
    h, w = len(grid), len(grid[0])
    im = base.copy() if base else Image.new('RGB', (w, h), GREY)
    px = im.load()
    for y in range(h):
        for x in range(w):
            v = grid[y][x]
            X, Y = at[0] + x, at[1] + y
            if v and 0 <= X < im.size[0] and 0 <= Y < im.size[1]:
                px[X, Y] = tuple(pal[v][:3])
    return im


def png_rgb(f, pal=None):
    pal = pal or f.palette
    im = Image.new('RGB', (f.width, f.height))
    im.putdata([GREY if v == 0 else (tuple(pal[v][:3]) if v < len(pal) else (255, 0, 255)) for v in f.pixels])
    return im


def zoom(im, z):
    return im.resize((im.size[0] * z, im.size[1] * z), Image.NEAREST)


def pair(a, b, z=4, gap=12, labels=('English', 'Hebrew'), title=None):
    a, b = zoom(a, z), zoom(b, z)
    top = 16 if title else 0
    h = max(a.size[1], b.size[1])
    out = Image.new('RGB', (a.size[0] + b.size[0] + gap, h + 14 + top), (255, 255, 255))
    d = ImageDraw.Draw(out)
    if title:
        d.text((2, 1), title, fill=(0, 0, 0))
    d.text((2, top + 1), labels[0], fill=(0, 0, 0))
    d.text((a.size[0] + gap + 2, top + 1), labels[1], fill=(0, 0, 0))
    out.paste(a, (0, top + 14))
    out.paste(b, (a.size[0] + gap, top + 14))
    return out


def stack(images, gap=10, titles=None, bg=(255, 255, 255)):
    w = max(i.size[0] for i in images)
    th = 14 if titles else 0
    h = sum(i.size[1] + gap + th for i in images)
    out = Image.new('RGB', (w, h), bg)
    d = ImageDraw.Draw(out)
    y = 0
    for k, i in enumerate(images):
        if titles:
            d.text((2, y + 1), titles[k], fill=(0, 0, 0))
            y += th
        out.paste(i, (0, y))
        y += i.size[1] + gap
    return out
