#!/usr/bin/env python3
"""Redraw the type and contest-category plates (graphics/types/*.png) with Hebrew names.

Each plate is a 32x16 4bpp indexed PNG. The English name is FONT_SMALL glyph art: foreground
index 15, shadow index 14, on the plate's own background index, in rows 4-11 (the same rows a
16x16 font cell uses). This script clears those text pixels, then stamps Hebrew glyphs taken
from graphics/fonts/latin_small.png (font index 1 -> 15, 2 -> 14; 0 and 3 stay background),
advancing by gFontSmallLatinGlyphWidths, laid out right to left, centred like the English.
A word too wide for the plate in FONT_SMALL (NARROW_PLATES) takes its glyphs from
latin_small_narrower.png and gFontSmallNarrowerLatinGlyphWidths instead, with the hyphen cut
to two columns of ink.
Only pixel indices change; the PLTE and every other chunk are written back unchanged.

Usage: make_types.py [--write]
Without --write it draws into $HNS_WORK/graphics/types/dry_*.png; with --write it writes
graphics/types/*.png in HNS_TREE. Either way it writes the previews to $HNS_WORK/graphics/types.
"""
import os
import shutil
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import gpaths  # noqa: E402
import inspect_fonts as F  # noqa: E402
from PIL import Image, ImageDraw  # noqa: E402

REPO = gpaths.TREE
OUT = gpaths.out('types')
FONT = 'latin_small'
WIDTHS = 'gFontSmallLatinGlyphWidths'

HEB = 'אבגדהוזחטיכלמנסעפצקרשת'
CODES = {c: 0x3A + i for i, c in enumerate(HEB)}
CODES.update({'ך': 0x50, 'ם': 0x5E, 'ן': 0x5F, 'ף': 0x60, 'ץ': 0x61})
HYPHEN = 0xAE
CODES['-'] = HYPHEN

# Plates whose word is wider than the plate's 30 px of ink in FONT_SMALL (על-חושי is 36 px):
# drawn in FONT_SMALL_NARROWER glyphs, with the hyphen kept to its first SHORT_HYPHEN columns
# (two of ink, one of shadow), which is also its advance.
NARROW_PLATES = {'psychic'}
NARROW_FONT = 'latin_small_narrower'
NARROW_WIDTHS = 'gFontSmallNarrowerLatinGlyphWidths'
SHORT_HYPHEN = 3

# file -> (English on the plate, Hebrew)
PLATES = {
    'normal': ('NORMAL', 'רגיל'),
    'fight': ('FIGHT', 'קרב'),
    'flying': ('FLYING', 'תעופה'),
    'poison': ('POISON', 'רעל'),
    'ground': ('GROUND', 'אדמה'),
    'rock': ('ROCK', 'סלע'),
    'bug': ('BUG', 'חרק'),
    'ghost': ('GHOST', 'רפאים'),
    'steel': ('STEEL', 'פלדה'),
    'fire': ('FIRE', 'אש'),
    'water': ('WATER', 'מים'),
    'grass': ('GRASS', 'עשב'),
    'electric': ('ELECTR', 'חשמל'),
    'psychic': ('PSYCHC', 'על-חושי'),
    'ice': ('ICE', 'קרח'),
    'dragon': ('DRAGON', 'דרקון'),
    'dark': ('DARK', 'אפל'),
    'fairy': ('FAIRY', 'פיה'),
    'stellar': ('STELLR', 'כוכבי'),
    'contest_cool': ('COOL', 'מגניב'),
    'contest_beauty': ('BEAUTY', 'יופי'),
    'contest_cute': ('CUTE', 'חמוד'),
    'contest_smart': ('SMART', 'חכם'),
    'contest_tough': ('TOUGH', 'קשוח'),
}
UNCHANGED = {
    'mystery': '??? (language-neutral, glossary TYPE_MYSTERY keeps ???)',
    'none': '??? (the English plate for TYPE_NONE also shows ???)',
}

FG, SH = 15, 14
TEXT_ROWS = range(3, 14)        # rows that may hold glyph ink (ascender row 3 .. descender row 13)
CLEAR_ROWS = range(4, 12)       # rows the English text occupies


def plate_bg(p):
    row = [p.get(x, 3) for x in range(p.width)]
    return max(set(row), key=row.count)


def compose(word, font, widths):
    """Return (columns, rows) grid of font indices for `word`, first letter at the right."""
    glyphs = [(font.glyph(CODES[c]), widths[CODES[c]]) for c in reversed(word)]
    total = sum(w for _, w in glyphs)
    grid = [[0] * total for _ in range(16)]
    x = 0
    for g, w in glyphs:
        for y in range(16):
            for gx in range(w):
                v = g[y][gx]
                if v in (1, 2):
                    grid[y][x + gx] = v
        x += w
    return grid


def ink_bbox(grid):
    cols = [x for x in range(len(grid[0])) if any(grid[y][x] for y in range(16))]
    rows = [y for y in range(16) if any(grid[y])]
    return min(cols), max(cols), min(rows), max(rows)


def redraw(path, word, font, widths):
    p = F.FontPng.load(path, layout='latin')
    bg = plate_bg(p)
    # 1. the text band holds only bg, FG and SH; clear FG/SH there
    for y in CLEAR_ROWS:
        for x in range(p.width):
            v = p.get(x, y)
            assert v in (bg, FG, SH), (path, x, y, v)
            p.put(x, y, bg)
    for y in (3, 12):
        assert all(p.get(x, y) == bg for x in range(p.width)), (path, y)
    # 2. stamp the Hebrew word, centred on the ink bounding box like the English
    grid = compose(word, font, widths)
    x0, x1, y0, y1 = ink_bbox(grid)
    bw = x1 - x0 + 1
    left = (p.width - bw + 1) // 2
    assert 1 <= left and left + bw <= p.width - 1, (path, word, bw)
    assert y0 >= 3 and y1 <= 13, (path, word, y0, y1)
    for y in TEXT_ROWS:
        for gx in range(x0, x1 + 1):
            v = grid[y][gx]
            if not v:
                continue
            x = left + gx - x0
            assert p.get(x, y) == bg, (path, x, y)   # never overwrite the border
            p.put(x, y, FG if v == 1 else SH)
    return p, bw, left


class ShortHyphenFont:
    """A font whose hyphen keeps only its first SHORT_HYPHEN columns."""

    def __init__(self, font):
        self.font = font

    def glyph(self, code):
        g = self.font.glyph(code)
        if code != HYPHEN:
            return g
        return [[v if x < SHORT_HYPHEN else 0 for x, v in enumerate(row)] for row in g]


def fonts():
    """(font, widths) per plate kind: 'small' for every plate, 'narrow' for NARROW_PLATES."""
    tables = F.parse_width_tables(os.path.join(REPO, 'src/fonts.c'))
    small = (F.FontPng.load(os.path.join(REPO, 'graphics/fonts/%s.png' % FONT)), tables[WIDTHS])
    nwidths = list(tables[NARROW_WIDTHS])
    nwidths[HYPHEN] = SHORT_HYPHEN
    narrow = (ShortHyphenFont(F.FontPng.load(os.path.join(REPO, 'graphics/fonts/%s.png' % NARROW_FONT))), nwidths)
    return {'small': small, 'narrow': narrow}


def to_image(p, zoom=4):
    pal = p.palette
    im = Image.new('RGB', (p.width, p.height))
    im.putdata([pal[v] for v in p.pixels])
    return im.resize((p.width * zoom, p.height * zoom), Image.NEAREST)


def chunks_of(path):
    data = open(path, 'rb').read()
    return [(t, b) for t, b in F._chunks(data) if t not in (b'IDAT',)]


def main():
    write = '--write' in sys.argv
    font_sets = fonts()
    os.makedirs(OUT, exist_ok=True)
    orig_dir = os.path.join(OUT, 'english')
    os.makedirs(orig_dir, exist_ok=True)
    rows = []
    for name, (en, he) in PLATES.items():
        path = os.path.join(REPO, 'graphics/types/%s.png' % name)
        orig = os.path.join(orig_dir, '%s.png' % name)
        # the English original from the release, not whatever is on disk
        with open(orig, 'wb') as fh:
            fh.write(gpaths.english('graphics/types/%s.png' % name))
        font, widths = font_sets['narrow' if name in NARROW_PLATES else 'small']
        p, bw, left = redraw(orig, he, font, widths)
        dest = path if write else os.path.join(OUT, 'dry_%s.png' % name)
        p.save(dest)
        # verify: same IHDR, same non-IDAT chunks, same size
        a, b = chunks_of(orig), chunks_of(dest)
        assert a == b, (name, 'chunks differ')
        e = F.FontPng.load(orig, layout='latin')
        h = F.FontPng.load(dest, layout='latin')
        assert (e.width, e.height, e.bit_depth, e.palette) == (h.width, h.height, h.bit_depth, h.palette)
        changed = [(x, y) for y in range(16) for x in range(32) if e.get(x, y) != h.get(x, y)]
        assert all(3 <= y <= 13 for _, y in changed), name
        new_idx = set(h.pixels) - set(e.pixels)
        assert not new_idx, (name, new_idx)
        pair = Image.new('RGB', (32 * 4 * 2 + 8, 16 * 4), (40, 40, 40))
        pair.paste(to_image(e), (0, 0))
        pair.paste(to_image(h), (32 * 4 + 8, 0))
        pair.save(os.path.join(OUT, '%s_pair.png' % name))
        rows.append((name, en, he, pair, bw, left))
        print('%-15s %-7s %-6s width %2d left %2d changed %3d px' % (name, en, he[::-1], bw, left, len(changed)))
    for name in UNCHANGED:
        e = F.FontPng.load(os.path.join(REPO, 'graphics/types/%s.png' % name), layout='latin')
        pair = Image.new('RGB', (32 * 4 * 2 + 8, 16 * 4), (40, 40, 40))
        pair.paste(to_image(e), (0, 0))
        pair.paste(to_image(e), (32 * 4 + 8, 0))
        pair.save(os.path.join(OUT, '%s_pair.png' % name))
        rows.append((name, '???', '??? (unchanged)', pair, 0, 0))
    # contact sheet: 2 columns of pairs with labels
    cols = 2
    cw, ch = 32 * 4 * 2 + 8, 16 * 4
    lab = 110
    n = len(rows)
    nr = (n + cols - 1) // cols
    sheet = Image.new('RGB', (cols * (cw + lab + 16), nr * (ch + 10) + 10), (24, 24, 24))
    d = ImageDraw.Draw(sheet)
    for i, (name, en, he, pair, _, _) in enumerate(rows):
        cx = (i % cols) * (cw + lab + 16) + 8
        cy = (i // cols) * (ch + 10) + 10
        d.text((cx, cy + 20), '%s\n%s' % (name, en), fill=(220, 220, 220))
        sheet.paste(pair, (cx + lab, cy))
    sheet.save(os.path.join(OUT, 'contact_sheet.png'))
    # 1x strip as the game shows it, and a 2x one
    strip = Image.new('RGB', (len(rows) * 34, 18), (24, 24, 24))
    for i, (name, *_r) in enumerate(rows):
        src = os.path.join(REPO, 'graphics/types/%s.png' % name) if write else os.path.join(OUT, 'dry_%s.png' % name)
        if not os.path.exists(src):
            src = os.path.join(REPO, 'graphics/types/%s.png' % name)
        strip.paste(to_image(F.FontPng.load(src, layout='latin'), 1), (i * 34 + 1, 1))
    strip.resize((strip.width * 2, strip.height * 2), Image.NEAREST).save(os.path.join(OUT, 'strip_2x.png'))


if __name__ == '__main__':
    main()
