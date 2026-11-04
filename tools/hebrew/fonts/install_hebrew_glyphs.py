#!/usr/bin/env python3
"""Install the Hebrew letters, the left-pointing triangle and the level glyph into the nine
expansion Latin fonts, and write their widths into src/fonts.c.

Source of truth: hebrew_glyph_designs.txt next to this script. It holds foreground pixels only
('#' = index 1), one block per glyph, rows 2..14 of the 16x16 cell. Everything else is computed
so the nine fonts stay consistent:

  shadow   index 2 on every non-foreground pixel to the right of, below, or below-right of a
           foreground pixel. 63 of the 78 Latin glyphs 0xA1-0xEE of latin_normal.png follow this
           rule exactly; the rest are hand touch-ups of it.
  advance  last foreground column + 2: ink starts at column 0 and the last column holds no
           foreground (it carries the shadow), as Latin 'A' (fg 0-4, shadow 5, width 6) does.
           WIDTH_OVERRIDES below lists the letters whose width table entry is set by hand.
  box      index 3 (renders as background) on every other pixel inside the advance, on the rows
           the font's own Latin glyphs paint, so the PNG shows the advance.

Cells written (charmap.txt / include/constants/characters.h):
  0x3A-0x4F  א..ת      0x50 ך   0x5E ם   0x5F ן   0x60 ף   0x61 ץ
  0x87       ◀  the mirror of ▶ (0xEF) inside ▶'s advance, shadow recomputed so it falls to the
                right like every other glyph's; same advance as ▶
  0x34       רמה level glyph (CHAR_LV), and 0x105 (F9 05, CHAR_LV_2): same pixels and width

usage:
  install_hebrew_glyphs.py TREE                 write the 9 PNGs and src/fonts.c in TREE
  install_hebrew_glyphs.py TREE --check         compare TREE with what would be written
  install_hebrew_glyphs.py TREE --sheet OUT.png contact sheet of the result (needs Pillow)
  install_hebrew_glyphs.py TREE --mock OUT.png --text 'שלום Lv5' [--font normal] [--width 208]
"""

import argparse
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import inspect_fonts as F  # noqa: E402

HERE = os.path.dirname(os.path.abspath(__file__))
DESIGNS = os.path.join(HERE, 'hebrew_glyph_designs.txt')
TOP = 2          # first cell row stored in the designs file

LETTERS = 'אבגדהוזחטיכלמנסעפצקרשתךםןףץ'
CODES = list(range(0x3A, 0x51)) + [0x5E, 0x5F, 0x60, 0x61]
CODE_OF = dict(zip(LETTERS, CODES))
TRI_RIGHT, TRI_LEFT = 0xEF, 0x87
LV, LV_2 = 0x34, 0x105

# name: (width table, letter set, level set, box rows, rows the game blits)
# Blit heights: gCurGlyph.height in each DecompressGlyph_* (src/text.c).
FONTS = {
    'normal':         ('gFontNormalLatinGlyphWidths',        'W6_8', 'LV_B11', (0, 14), 15),
    'short':          ('gFontShortLatinGlyphWidths',         'W6_7', 'LV_B10', (0, 13), 14),
    'narrow':         ('gFontNarrowLatinGlyphWidths',        'W5_8', 'LVC_B11', (0, 14), 15),
    'narrower':       ('gFontNarrowerLatinGlyphWidths',      'W4_8', 'LVC_B11', (0, 14), 15),
    'short_narrow':   ('gFontShortNarrowLatinGlyphWidths',   'W5_7S', 'LVC_B10', (0, 13), 14),
    'short_narrower': ('gFontShortNarrowerLatinGlyphWidths', 'W4_7S', 'LVC_B10', (0, 13), 14),
    'small':          ('gFontSmallLatinGlyphWidths',         'W5_7', 'LVC_B10', (1, 12), 13),
    'small_narrow':   ('gFontSmallNarrowLatinGlyphWidths',   'W5_7SN', 'LVC_B10', (1, 12), 12),
    'small_narrower': ('gFontSmallNarrowerLatinGlyphWidths', 'W4_7', 'LVC_B10', (1, 12), 15),
}


# Advances set by hand where the computed one (last ink column + 2) is too tight. Only the width
# table changes; the glyph and its white box stay as computed.
#   normal ן: at 3 px it touches the next letter.
WIDTH_OVERRIDES = {('normal', 'ן'): 4}


# ---------------------------------------------------------------- designs

def parse_designs(path=DESIGNS):
    """{set: {name: [16 rows of 16 0/1 values]}}. '@alias NEW OLD' starts NEW as a copy of OLD;
    glyphs that follow it replace OLD's."""
    sets, cur, rows, y = {}, None, None, 0
    for raw in open(path, encoding='utf-8'):
        line = raw.rstrip('\n')
        if line.startswith('@set '):
            cur = sets.setdefault(line.split()[1], {})
            rows = None
        elif line.startswith('@alias '):
            _, new, old = line.split()[:3]
            sets[new] = {k: [list(r) for r in v] for k, v in sets[old].items()}
            cur, rows = sets[new], None
        elif line.startswith('@glyph '):
            rows = [[0] * 16 for _ in range(16)]
            cur[line.split()[1]] = rows
            y = TOP
        elif line[:1] in ('.', '#') and rows is not None:
            for x, c in enumerate(line.split()[0]):
                if c == '#':
                    rows[y][x] = 1
            y += 1
    return sets


# ---------------------------------------------------------------- glyph building

def shade(fg):
    """fg (0/1 rows) -> rows of 0 bg / 1 fg / 2 shadow."""
    h, w = len(fg), len(fg[0])
    out = [[1 if fg[y][x] else 0 for x in range(w)] for y in range(h)]
    for y in range(h):
        for x in range(w):
            if fg[y][x]:
                for dx, dy in ((1, 0), (0, 1), (1, 1)):
                    if x + dx < w and y + dy < h and out[y + dy][x + dx] == 0:
                        out[y + dy][x + dx] = 2
    return out


def fg_cols(fg):
    cols = [x for x in range(16) if any(r[x] for r in fg)]
    return (cols[0], cols[-1]) if cols else None


def advance(fg):
    return fg_cols(fg)[1] + 2


def boxed(ink, width, box):
    return [[v if v else (F.BOX if x < width and box[0] <= y <= box[1] else F.BG)
             for x, v in enumerate(r)] for y, r in enumerate(ink)]


def build_letter(fg, box):
    span = fg_cols(fg)
    if span[0] != 0:
        raise ValueError('ink must start at column 0')
    w = advance(fg)
    if w > 8:
        raise ValueError('wider than 8 px')
    return boxed(shade(fg), w, box), w


def build_left_triangle(font, widths, box):
    """◀: mirror ▶'s foreground inside ▶'s own advance, then shade it like every other glyph."""
    w = widths[TRI_RIGHT]
    src = F.normalize(font.glyph(TRI_RIGHT))
    fg = [[1 if (x < w and src[y][w - 1 - x] == F.FG) else 0 for x in range(16)] for y in range(16)]
    ink = shade(fg)
    if fg_cols(fg)[1] >= w - 1:
        raise ValueError('mirrored triangle leaves no column for its shadow')
    rows = [y for y in range(16) if any(src[y][x] != F.BG for x in range(w))]
    return boxed(ink, w, (rows[0], rows[-1])), w


# ---------------------------------------------------------------- fonts.c

def table_span(src, name):
    m = re.search(r'const u8 %s\[\] = \{\n(.*?)\n\};' % re.escape(name), src, re.S)
    if not m:
        raise KeyError(name)
    return m.start(1), m.end(1)


def read_table(src, name):
    a, b = table_span(src, name)
    return [int(v) for v in re.findall(r'\d+', src[a:b])]


def write_table(src, name, updates):
    """Replace entries in place, keeping each number right-aligned in its original column."""
    a, b = table_span(src, name)
    body = src[a:b]
    toks = list(re.finditer(r'(\s*)(\d+)', body))
    if len(toks) != 512:
        raise ValueError('%s: %d entries' % (name, len(toks)))
    out, pos = [], 0
    for i, m in enumerate(toks):
        out.append(body[pos:m.start()])
        lead, num = m.group(1), m.group(2)
        if i in updates and int(num) != updates[i]:
            new = str(updates[i])
            cut = lead.rfind('\n') + 1
            prefix, spaces = lead[:cut], lead[cut:]
            n = len(spaces) + len(num) - len(new)
            lead = prefix + ' ' * max(n, 0 if (prefix or i == 0) else 1)
            num = new
        out.append(lead + num)
        pos = m.end()
    out.append(body[pos:])
    return src[:a] + ''.join(out) + src[b:]


# ---------------------------------------------------------------- main work

def plan(tree, designs):
    """{font: (FontPng with new cells, {code: width})}."""
    src = open(os.path.join(tree, 'src/fonts.c'), encoding='utf-8').read()
    result = {}
    for name, (table, letter_set, lv_set, box, height) in FONTS.items():
        font = F.FontPng.load(os.path.join(tree, 'graphics/fonts/latin_%s.png' % name))
        widths = read_table(src, table)
        new = {}
        for ch, code in CODE_OF.items():
            fg = designs[letter_set][ch]
            rows, w = build_letter(fg, box)
            low = max(y for y in range(16) if any(fg[y]))
            if low >= height:
                raise ValueError('%s %s: foreground on row %d, the game blits %d rows' % (name, ch, low, height))
            font.set_glyph(code, rows)
            new[code] = WIDTH_OVERRIDES.get((name, ch), w)
        rows, w = build_left_triangle(font, widths, box)
        font.set_glyph(TRI_LEFT, rows)
        new[TRI_LEFT] = w
        lv = designs[lv_set]['רמה']
        w = advance(lv)
        rows = boxed(shade(lv), w, box)
        for code in (LV, LV_2):
            font.set_glyph(code, rows)
            new[code] = w
        result[name] = (font, new)
    return result, src


def apply(tree, result, src):
    for name, (font, new) in result.items():
        font.save(os.path.join(tree, 'graphics/fonts/latin_%s.png' % name))
        src = write_table(src, FONTS[name][0], new)
    with open(os.path.join(tree, 'src/fonts.c'), 'w', encoding='utf-8') as fh:
        fh.write(src)


def check(tree, result, src):
    ok = True
    for name, (font, new) in result.items():
        cur = F.FontPng.load(os.path.join(tree, 'graphics/fonts/latin_%s.png' % name))
        if bytes(cur.pixels) != bytes(font.pixels):
            print('DIFFERS: latin_%s.png' % name)
            ok = False
        widths = read_table(src, FONTS[name][0])
        bad = {hex(c): (widths[c], w) for c, w in new.items() if widths[c] != w}
        if bad:
            print('DIFFERS: %s %s' % (FONTS[name][0], bad))
            ok = False
    print('OK: tree matches the designs' if ok else 'tree does NOT match the designs')
    return ok


# ---------------------------------------------------------------- previews

def glyph_and_width(result, font, code):
    f, new = result[font]
    return f.glyph(code), new.get(code)


def sheet(result, tree, out, zoom=4):
    from PIL import Image, ImageDraw
    src = open(os.path.join(tree, 'src/fonts.c'), encoding='utf-8').read()
    tiles = []
    for name, (font, new) in result.items():
        widths = read_table(src, FONTS[name][0])
        items = [('%02X' % c, font.glyph(c), widths[c]) for c in (0xBB, 0xC7, 0xD5, 0xDB, 0xA1)]
        items += [('%02X' % c, font.glyph(c), new[c]) for c in CODES + [TRI_LEFT]]
        items += [('EF', font.glyph(TRI_RIGHT), widths[TRI_RIGHT])]
        items += [('LV', font.glyph(LV), new[LV])]
        tiles.append((name, F.contact_sheet(items, zoom=zoom, cols=35, title=name)))
    img = Image.new('RGB', (max(t.width for _, t in tiles), sum(t.height for _, t in tiles)), 'white')
    y = 0
    for _, t in tiles:
        img.paste(t, (0, y))
        y += t.height
    img.save(out)


def encode(text, charmap):
    """Very small encoder for previews: single characters, {LV}, {LV_2}, spaces."""
    rev = {}
    for gid, names in charmap.items():
        for n in names:
            rev.setdefault(n, gid)
    out, i = [], 0
    while i < len(text):
        if text[i] == '{':
            j = text.index('}', i)
            out.append(rev[text[i + 1:j]])
            i = j + 1
            continue
        out.append(rev[text[i]] if text[i] != ' ' else 0)
        i += 1
    return out


def mock(result, tree, fontname, text, window_w, out, zoom=4):
    """1x and zoomed picture of one line laid out like src/text.c TEXT_RTL: each glyph at
    W - x - w, except runs of Latin/digits, which are drawn left to right as one block."""
    from PIL import Image
    src = open(os.path.join(tree, 'src/fonts.c'), encoding='utf-8').read()
    font, new = result[fontname]
    widths = read_table(src, FONTS[fontname][0])
    widths = [new.get(i, w) for i, w in enumerate(widths)]
    cm = F.parse_charmap(os.path.join(tree, 'charmap.txt'))
    codes = encode(text, cm)

    def cls(c):
        if c in CODES:
            return 'R'
        if 0xA1 <= c <= 0xAA:
            return 'D'
        if 0xBB <= c <= 0xEE or c in (LV, LV_2):
            return 'L'
        return 'N'
    canvas = [[F.BOX] * window_w for _ in range(16)]
    x, i = 0, 0
    while i < len(codes):
        if cls(codes[i]) in 'LD':
            j = i
            while j < len(codes) and cls(codes[j]) != 'R':
                j += 1
            while j > i and cls(codes[j - 1]) == 'N':
                j -= 1
            run = codes[i:j]
            rw = sum(widths[c] for c in run)
            px = window_w - x - rw
            for c in run:
                g = font.glyph(c)
                for yy in range(16):
                    for xx in range(widths[c]):
                        if g[yy][xx] in F.INK and 0 <= px + xx < window_w:
                            canvas[yy][px + xx] = g[yy][xx]
                px += widths[c]
            x += rw
            i = j
            continue
        c = codes[i]
        g = font.glyph(c)
        w = widths[c]
        px = window_w - x - w
        for yy in range(16):
            for xx in range(w):
                if g[yy][xx] in F.INK and 0 <= px + xx < window_w:
                    canvas[yy][px + xx] = g[yy][xx]
        x += w
        i += 1
    one = F.render(canvas, 1)
    big = F.render(canvas, zoom)
    img = Image.new('RGB', (big.width, one.height + 4 + big.height), 'white')
    img.paste(one, (0, 0))
    img.paste(big, (0, one.height + 4))
    img.save(out)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('tree')
    ap.add_argument('--designs', default=DESIGNS)
    ap.add_argument('--check', action='store_true')
    ap.add_argument('--sheet')
    ap.add_argument('--mock')
    ap.add_argument('--text', default='')
    ap.add_argument('--font', default='normal')
    ap.add_argument('--width', type=int, default=208)
    a = ap.parse_args()
    designs = parse_designs(a.designs)
    result, src = plan(a.tree, designs)
    if a.check:
        sys.exit(0 if check(a.tree, result, src) else 1)
    if a.sheet:
        sheet(result, a.tree, a.sheet)
        return
    if a.mock:
        mock(result, a.tree, a.font, a.text, a.width, a.mock)
        return
    apply(a.tree, result, src)
    for name, (font, new) in result.items():
        print('%-15s' % name, ' '.join('%s%d' % (ch, new[CODE_OF[ch]]) for ch in LETTERS),
              ' ◀%d  רמה%d' % (new[TRI_LEFT], new[LV]))


if __name__ == '__main__':
    main()
