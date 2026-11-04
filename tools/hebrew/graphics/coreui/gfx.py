#!/usr/bin/env python3
"""Shared helpers for the coreui graphics translation: load indexed PNGs (from the tree or a git ref),
render them with their own palette, make English | Hebrew preview pairs and contact sheets."""

import os
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import gpaths  # noqa: E402
import inspect_fonts as F  # noqa: E402

TREE = gpaths.TREE
GIT = gpaths.GIT
OUT = gpaths.out('coreui')
BASE_REF = gpaths.EN_REF   # 2.0.6 release: the English the forks started from

_tmp = tempfile.mkdtemp(prefix='coreui_')


def load(path, ref=None, repo=None):
    """Load an indexed PNG from the tree (ref=None) or from `git show ref:path` in the repository."""
    if ref is None:
        return F.FontPng.load(os.path.join(repo or TREE, path), layout='latin')
    data = subprocess.run(['git', '-C', repo or GIT, 'show', '%s:%s' % (ref, path)], capture_output=True, check=True).stdout
    tmp = os.path.join(_tmp, '%s_%s' % (ref.replace('/', '_'), path.replace('/', '_')))
    with open(tmp, 'wb') as fh:
        fh.write(data)
    return F.FontPng.load(tmp, layout='latin')


def try_load(path, ref, repo=None):
    try:
        return load(path, ref, repo)
    except subprocess.CalledProcessError:
        return None


def render(png, zoom=4, grid=0, low_nibble_pal=None):
    """PIL image of the PNG in its own palette. grid=8 draws a faint tile grid."""
    from PIL import Image, ImageDraw
    pal = png.palette
    w, h = png.width, png.height
    im = Image.new('RGB', (w, h))
    px = im.load()
    for y in range(h):
        for x in range(w):
            v = png.get(x, y)
            if low_nibble_pal is not None:
                c = low_nibble_pal[v & 15]
            else:
                c = pal[v] if v < len(pal) else (255, 0, 255)
            px[x, y] = c
    im = im.resize((w * zoom, h * zoom), Image.NEAREST)
    if grid:
        d = ImageDraw.Draw(im)
        for x in range(0, w * zoom, grid * zoom):
            d.line([(x, 0), (x, h * zoom)], fill=(255, 0, 255))
        for y in range(0, h * zoom, grid * zoom):
            d.line([(0, y), (w * zoom, y)], fill=(255, 0, 255))
    return im


def labelled_row(images, labels, gap=12, bg=(40, 40, 40)):
    from PIL import Image, ImageDraw
    th = 14
    w = sum(i.width for i in images) + gap * (len(images) + 1)
    h = max(i.height for i in images) + th + gap * 2
    out = Image.new('RGB', (w, h), bg)
    d = ImageDraw.Draw(out)
    x = gap
    for im, lab in zip(images, labels):
        d.text((x, gap // 2), lab, fill=(255, 255, 255))
        out.paste(im, (x, gap + th))
        x += im.width + gap
    return out


def pair(path, zoom=4, grid=0, extra_refs=()):
    """English (release) | Hebrew (working tree) image, optionally with other refs between them."""
    imgs, labs = [render(load(path, BASE_REF), zoom, grid)], ['English']
    for ref, repo, lab in extra_refs:
        p = try_load(path, ref, repo)
        if p is not None:
            imgs.append(render(p, zoom, grid))
            labs.append(lab)
    imgs.append(render(load(path), zoom, grid))
    labs.append('Hebrew')
    return labelled_row(imgs, labs)


def check_same(path):
    """Assert size, bit depth, palette and non-pixel chunks match the release version."""
    a, b = load(path, BASE_REF), load(path)
    assert (a.width, a.height, a.bit_depth) == (b.width, b.height, b.bit_depth), path
    assert a._before == b._before and a._after == b._after, path + ': chunks differ'
    raw = open(os.path.join(TREE, path), 'rb').read()
    import struct
    ihdr = raw[16:29]
    assert struct.unpack('>IIBBBBB', ihdr)[3] == 3, 'colour type'
    changed = sum(1 for i in range(len(a.pixels)) if a.pixels[i] != b.pixels[i])
    return changed


def tiles_to_sprite(png, first_tile, wt, ht):
    """2D list of pixels for a 1D-mapped sprite of wt x ht tiles starting at first_tile."""
    tw = png.width // 8
    out = [[0] * (wt * 8) for _ in range(ht * 8)]
    for i in range(wt * ht):
        t = first_tile + i
        sx, sy = (t % tw) * 8, (t // tw) * 8
        dx, dy = (i % wt) * 8, (i // wt) * 8
        for y in range(8):
            for x in range(8):
                out[dy + y][dx + x] = png.get(sx + x, sy + y)
    return out


def sprite_to_tiles(png, first_tile, wt, ht, pix):
    tw = png.width // 8
    for i in range(wt * ht):
        t = first_tile + i
        sx, sy = (t % tw) * 8, (t // tw) * 8
        dx, dy = (i % wt) * 8, (i // wt) * 8
        for y in range(8):
            for x in range(8):
                png.put(sx + x, sy + y, pix[dy + y][dx + x])


class Canvas:
    """Pixel rows with get/put, so the drawing code works on sprites as on PNGs."""
    def __init__(self, rows):
        self.rows = rows
        self.height = len(rows)
        self.width = len(rows[0])

    def get(self, x, y):
        return self.rows[y][x]

    def put(self, x, y, v):
        self.rows[y][x] = v


def gather_tiles(png, tile_rows):
    """Canvas of 8x8 tiles laid out as `tile_rows` (a list of rows of tile numbers in the sheet)."""
    tw = png.width // 8
    rows = []
    for trow in tile_rows:
        band = [[] for _ in range(8)]
        for t in trow:
            sx, sy = (t % tw) * 8, (t // tw) * 8
            for y in range(8):
                band[y] += [png.get(sx + x, sy + y) for x in range(8)]
        rows += band
    return Canvas(rows)


def scatter_tiles(png, tile_rows, canvas):
    """Write a canvas made by gather_tiles back into the sheet."""
    tw = png.width // 8
    for j, trow in enumerate(tile_rows):
        for i, t in enumerate(trow):
            sx, sy = (t % tw) * 8, (t // tw) * 8
            for y in range(8):
                for x in range(8):
                    png.put(sx + x, sy + y, canvas.get(i * 8 + x, j * 8 + y))
