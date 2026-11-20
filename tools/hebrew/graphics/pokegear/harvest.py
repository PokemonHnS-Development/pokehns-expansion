"""Harvest Hebrew foreground masks from the game fonts (cells 0x3A-0x4F, 0x50, 0x5E-0x61)."""
import os
import sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import gpaths  # noqa: E402,F401  (puts tools/hebrew/fonts on the path)
import inspect_fonts as F

LETTERS = 'אבגדהוזחטיכלמנסעפצקרשת'
CODES = {ch: 0x3A + i for i, ch in enumerate(LETTERS)}
CODES.update({'ך': 0x50, 'ם': 0x5E, 'ן': 0x5F, 'ף': 0x60, 'ץ': 0x61})

def harvest(font_png, baseline):
    """{letter: (rows, top)} where rows are strings of '#'/'.' cropped to fg columns; top = first row - baseline."""
    f = F.FontPng.load(font_png)
    out = {}
    for ch, c in CODES.items():
        g = F.normalize(f.glyph(c))
        ys = [y for y in range(16) if any(v == 1 for v in g[y])]
        xs = [x for x in range(16) if any(g[y][x] == 1 for y in range(16))]
        rows = [''.join('#' if g[y][x] == 1 else '.' for x in range(0, xs[-1] + 1)) for y in range(ys[0], ys[-1] + 1)]
        out[ch] = (rows, ys[0] - baseline)
    return out

if __name__ == '__main__':
    for name, base in (('latin_short', 10), ('latin_normal', 11)):
        h = harvest('graphics/fonts/%s.png' % name, base)
        print(name)
        for ch in 'אבגדהוזחטיכךלמםנןסעפףצץקרשת':
            rows, top = h[ch]
            print(ch, top, rows)
