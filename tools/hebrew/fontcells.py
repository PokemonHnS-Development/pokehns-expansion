#!/usr/bin/env python3
"""Report, for each Latin font, whether a glyph cell is blank and its width from src/fonts.c.

Usage: fontcells.py <repo> [hex bytes...]
Palette index -> 2bpp value: 0 background, 1 foreground, 2 shadow, 3 accent
(src/text.c GenerateFontHalfRowLookupTable). A cell is "blank" when it has no
foreground or shadow pixel; "acc" counts accent-only pixels (the box Latin glyphs
fill behind themselves).
"""
import re, sys
from PIL import Image

FONTS = [
    ('normal', 'latin_normal.png', 'gFontNormalLatinGlyphWidths'),
    ('short', 'latin_short.png', 'gFontShortLatinGlyphWidths'),
    ('small', 'latin_small.png', 'gFontSmallLatinGlyphWidths'),
    ('narrow', 'latin_narrow.png', 'gFontNarrowLatinGlyphWidths'),
    ('narrower', 'latin_narrower.png', 'gFontNarrowerLatinGlyphWidths'),
    ('short_narrow', 'latin_short_narrow.png', 'gFontShortNarrowLatinGlyphWidths'),
    ('short_narrower', 'latin_short_narrower.png', 'gFontShortNarrowerLatinGlyphWidths'),
    ('small_narrow', 'latin_small_narrow.png', 'gFontSmallNarrowLatinGlyphWidths'),
    ('small_narrower', 'latin_small_narrower.png', 'gFontSmallNarrowerLatinGlyphWidths'),
]

def widths(repo):
    src = open(f'{repo}/src/fonts.c', encoding='utf-8').read()
    out = {}
    for m in re.finditer(r'const u8 (\w+LatinGlyphWidths)\[\] = \{(.*?)\};', src, re.S):
        out[m.group(1)] = [int(v) for v in re.findall(r'\d+', m.group(2))]
    return out

def cell_ink(im, c):
    x0, y0 = (c % 16) * 16, (c // 16) * 16
    px = [im.getpixel((x0 + x, y0 + y)) for y in range(16) for x in range(16)]
    return sum(1 for v in px if v in (1, 2)), sum(1 for v in px if v == 3)

def main():
    repo = sys.argv[1]
    codes = [int(h, 16) for h in sys.argv[2:]] or list(range(0x100))
    w = widths(repo)
    ims = {n: Image.open(f'{repo}/graphics/fonts/{p}') for n, p, _ in FONTS}
    print('code ' + ' '.join(f'{n:>14}' for n, _, _ in FONTS))
    for c in codes:
        cols = []
        for n, _, t in FONTS:
            ink, acc = cell_ink(ims[n], c)
            tag = ('blank' if ink == 0 else 'INK%d' % ink) + ('+acc' if acc and not ink else '')
            cols.append(f"{tag}/w{w[t][c]}".rjust(14))
        print(f'0x{c:02X} ' + ' '.join(cols))

if __name__ == '__main__':
    main()
