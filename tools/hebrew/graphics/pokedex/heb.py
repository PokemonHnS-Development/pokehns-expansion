"""Hebrew word bitmaps harvested from the game's font PNGs (graphics/fonts/latin_*.png).

word(font, text) -> Bitmap with .w, .h (16) and .px[y][x] in {0: none, 1: ink, 2: shadow}.
Letters are laid out right to left (the first letter at the right), advancing by the font's
glyph width table in src/fonts.c, exactly as the text renderer spaces them.
"""
import os, re, sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import gpaths
import inspect_fonts as F

ROOT = gpaths.TREE
HEB = 'אבגדהוזחטיכלמנסעפצקרשת'
CODES = {c: 0x3A + i for i, c in enumerate(HEB)}
CODES.update({'ך': 0x50, 'ם': 0x5E, 'ן': 0x5F, 'ף': 0x60, 'ץ': 0x61})

TABLES = {
    'small': 'gFontSmallLatinGlyphWidths', 'small_narrow': 'gFontSmallNarrowLatinGlyphWidths',
    'small_narrower': 'gFontSmallNarrowerLatinGlyphWidths', 'normal': 'gFontNormalLatinGlyphWidths',
    'narrow': 'gFontNarrowLatinGlyphWidths', 'narrower': 'gFontNarrowerLatinGlyphWidths',
    'short': 'gFontShortLatinGlyphWidths', 'short_narrow': 'gFontShortNarrowLatinGlyphWidths',
    'short_narrower': 'gFontShortNarrowerLatinGlyphWidths',
}

def _charmap():
    cm = {}
    for line in open(os.path.join(ROOT, 'charmap.txt'), encoding='utf-8'):
        m = re.match(r"^'(.)'\s*=\s*([0-9A-Fa-f]{2})\s*$", line.strip())
        if m:
            cm.setdefault(m.group(1), int(m.group(2), 16))
    return cm

_CM = None
def code(ch):
    global _CM
    if ch in CODES:
        return CODES[ch]
    if _CM is None:
        _CM = _charmap()
    special = {'”': 0xB2, "'": 0xB4, ' ': 0x00, '-': 0xAE}
    if ch in special:
        return special[ch]
    return _CM[ch]

_widths = {}
def widths(font):
    if font not in _widths:
        src = open(os.path.join(ROOT, 'src/fonts.c')).read()
        m = re.search(TABLES[font] + r'\[\]\s*=\s*\{(.*?)\};', src, re.S)
        _widths[font] = [int(v, 0) for v in re.findall(r'0x[0-9A-Fa-f]+|\d+', m.group(1))]
    return _widths[font]

_fonts = {}
def fontpng(font):
    if font not in _fonts:
        _fonts[font] = F.FontPng.load(os.path.join(ROOT, 'graphics/fonts/latin_%s.png' % font))
    return _fonts[font]

class Bitmap:
    def __init__(self, w, h):
        self.w, self.h = w, h
        self.px = [[0] * w for _ in range(h)]
    def ink_bbox(self, kinds=(1, 2)):
        xs = [x for x in range(self.w) for y in range(self.h) if self.px[y][x] in kinds]
        ys = [y for y in range(self.h) for x in range(self.w) if self.px[y][x] in kinds]
        if not xs:
            return None
        return min(xs), min(ys), max(xs), max(ys)
    def ascii(self):
        return '\n'.join(''.join('.#+'[v] for v in r) for r in self.px)

def glyph(font, ch):
    g = fontpng(font).glyph(code(ch))
    return [[{1: 1, 2: 2}.get(v & 3, 0) for v in row] for row in g]

def word(font, text, spacing=0, rtl=True):
    """Lay out `text`; Hebrew letters right to left. Digits/Latin are not expected here."""
    wt = widths(font)
    adv = [wt[code(c)] + (spacing if i < len(text) - 1 else 0) for i, c in enumerate(text)]
    total = sum(adv)
    bm = Bitmap(total + 16, 16)
    x = total if rtl else 0
    for c, a in zip(text, adv):
        if rtl:
            x -= a
        g = glyph(font, c)
        for y in range(16):
            for gx in range(16):
                v = g[y][gx]
                if v and x + gx < bm.w:
                    # ink wins over shadow where glyphs overlap
                    if v == 1 or bm.px[y][x + gx] == 0:
                        bm.px[y][x + gx] = v
        if not rtl:
            x += a
    # trim to ink box width (keep rows)
    bb = bm.ink_bbox()
    out = Bitmap(bb[2] - bb[0] + 1, 16)
    for y in range(16):
        out.px[y] = bm.px[y][bb[0]:bb[2] + 1]
    out.advance = total
    return out

if __name__ == '__main__':
    font = sys.argv[1]
    for t in sys.argv[2:]:
        b = word(font, t)
        print(t, 'ink+shadow width', b.w, 'bbox', b.ink_bbox())
        print(b.ascii())
