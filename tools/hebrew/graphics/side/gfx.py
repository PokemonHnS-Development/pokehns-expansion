"""Helpers for the side-content graphics group: load indexed PNGs, render, compare."""
import os, sys, subprocess, tempfile
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import gpaths
import inspect_fonts as F
from PIL import Image, ImageDraw

WT = gpaths.TREE                 # read and written: the Hebrew tree
OUT = gpaths.out('side')         # previews

def load(path):
    return F.FontPng.load(path if path.startswith('/') else os.path.join(WT, path), 'latin')

def load_rev(rev, path, repo=gpaths.GIT):
    data = subprocess.run(['git', '-C', repo, 'show', '%s:%s' % (rev, path)], capture_output=True, check=True).stdout
    fd, tmp = tempfile.mkstemp(suffix='.png'); os.write(fd, data); os.close(fd)
    f = F.FontPng.load(tmp, 'latin'); os.unlink(tmp); return f

def render(f, zoom=4, grid=0, pal=None, region=None):
    pal = pal or f.palette
    x0, y0, w, h = region or (0, 0, f.width, f.height)
    im = Image.new('RGB', (w, h))
    px = im.load()
    for y in range(h):
        for x in range(w):
            v = f.get(x0 + x, y0 + y)
            px[x, y] = pal[v] if v < len(pal) else (255, 0, 255)
    im = im.resize((w * zoom, h * zoom), Image.NEAREST)
    if grid:
        d = ImageDraw.Draw(im)
        for gx in range(0, w * zoom, grid * zoom):
            d.line([(gx, 0), (gx, h * zoom)], fill=(255, 0, 0))
        for gy in range(0, h * zoom, grid * zoom):
            d.line([(0, gy), (w * zoom, gy)], fill=(255, 0, 0))
    return im

def side_by_side(ims, labels=None, gap=8, bg=(255, 255, 255)):
    labels = labels or [''] * len(ims)
    top = 14
    W = sum(i.width for i in ims) + gap * (len(ims) + 1)
    H = max(i.height for i in ims) + top + gap
    out = Image.new('RGB', (W, H), bg)
    d = ImageDraw.Draw(out)
    x = gap
    for im, lab in zip(ims, labels):
        d.text((x, 1), lab, fill=(0, 0, 0))
        out.paste(im, (x, top))
        x += im.width + gap
    return out

def dump(f, x0=0, y0=0, w=None, h=None, legend=True):
    w = w or f.width - x0; h = h or f.height - y0
    vals = sorted({f.get(x0 + x, y0 + y) for y in range(h) for x in range(w)})
    digs = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
    if max(vals) < len(digs):
        m = {v: digs[v] for v in vals}
    else:
        m = {v: digs[i] for i, v in enumerate(vals)}
        print('legend:', ' '.join('%s=%d' % (m[v], v) for v in vals))
    print('    ' + ''.join(str((x0 + x) % 10) for x in range(w)))
    for y in range(h):
        print('%3d ' % (y0 + y) + ''.join(m[f.get(x0 + x, y0 + y)] for x in range(w)))

import struct
def read_bin(path):
    p = path if path.startswith('/') else os.path.join(WT, path)
    d = open(p, 'rb').read()
    return list(struct.unpack('<%dH' % (len(d) // 2), d))

def tile_px(f, t):
    tw = f.width // 8
    tx, ty = (t % tw) * 8, (t // tw) * 8
    return [[f.get(tx + x, ty + y) for x in range(8)] for y in range(8)]

def compose(f, tm, width=32, offset=0, zoom=3, pal=None):
    """Render a tilemap (list of u16 entries) using the tiles of f."""
    pal = pal or f.palette
    n = len(tm); h = (n + width - 1) // width
    ntiles = (f.width // 8) * (f.height // 8)
    im = Image.new('RGB', (width * 8, h * 8), (40, 0, 40))
    px = im.load()
    for i, e in enumerate(tm):
        t = (e & 0x3FF) - offset
        if t < 0 or t >= ntiles:
            continue
        hf, vf = e & 0x400, e & 0x800
        tp = tile_px(f, t)
        X, Y = (i % width) * 8, (i // width) * 8
        for y in range(8):
            for x in range(8):
                sx = 7 - x if hf else x
                sy = 7 - y if vf else y
                v = tp[sy][sx]
                px[X + x, Y + y] = pal[v] if v < len(pal) else (255, 0, 255)
    return im.resize((im.width * zoom, im.height * zoom), Image.NEAREST)

def refs(tm, offset=0):
    from collections import Counter
    return Counter((e & 0x3FF) - offset for e in tm)

def load_head(path):
    """The English original of PATH (the 2.0.6 release)."""
    return load_rev(gpaths.EN_REF, path)

def pair(path, zoom=4, grid=0, region=None):
    """Write the English | Hebrew 4x preview for a graphics path into OUT."""
    e = load_head(path); h = load(path)
    out = side_by_side([render(e, zoom, grid, region=region), render(h, zoom, grid, region=region)], ['English', 'Hebrew'])
    name = path.replace('graphics/', '').replace('/', '__').replace('.png', '') + ('_crop' if region else '') + '_pair.png'
    out.save(os.path.join(OUT, name))
    return os.path.join(OUT, name)
