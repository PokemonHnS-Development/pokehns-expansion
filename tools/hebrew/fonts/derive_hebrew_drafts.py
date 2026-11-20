#!/usr/bin/env python3
"""Derive DRAFT Hebrew glyphs for the nine expansion Latin fonts from the FireRed fork's glyphs.

Nothing here writes into the game tree. Output goes to OUTDIR (default $HNS_WORK/font_drafts):

  <font>_hebrew_draft.png   256x32 strip in the target font's own PNG format and palette;
                            cells 0..26 hold א..ת then ן ם ץ ף ך (FireRed's order 0x01..0x1B
                            minus one). Paste each cell into whichever code the charmap picks.
  <font>_hebrew_widths.txt  proposed width-table entries, same order.
  compare_<font>.png        Latin reference glyphs + the draft Hebrew, 4x, baseline marked.
  mock_lines.png            one Hebrew line per font, laid out by the mirrored-blit rule.

Every glyph here is a starting point for a human to edit, not a final design. The designs that
shipped are in hebrew_glyph_designs.txt; tools/hebrew/data/font_drafts/ keeps the widths files
that textwidth.py's --hebrew-widths draft reads.

  derive_hebrew_drafts.py [--hns TREE] [--frlg FRLG_TREE] [--out OUTDIR] [--no-stretch]

TREE (default HNS_TREE) gives each target font's PNG format; FRLG_TREE (default
../pokefirered-heb next to this repository) is the FireRed fork whose Hebrew glyphs are the
source. Needs Pillow.
"""

import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import inspect_fonts as F  # noqa: E402

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import paths  # noqa: E402

HEB = 'אבגדהוזחטיכלמנסעפצקרשתןםץףך'
FRLG_CODES = list(range(0x01, 0x1C))   # pokefirered-heb charmap.txt:2-28

# Target geometry per font. height = rows the game blits (gCurGlyph.height in src/text.c
# DecompressGlyph_*); box = rows the upstream PNG paints with index 3; baseline = lowest
# foreground row of 'A' (measured with inspect_fonts.py metrics).
GEOM = {
    'normal':         dict(height=15, box=(0, 14), baseline=11, source='W6', stretch=True),
    'narrow':         dict(height=15, box=(0, 14), baseline=11, source='W5', stretch=True),
    'narrower':       dict(height=15, box=(0, 14), baseline=11, source='W5', stretch=True, drop=1),
    'short':          dict(height=14, box=(0, 13), baseline=10, source='W6'),
    'short_narrow':   dict(height=14, box=(0, 13), baseline=10, source='W5'),
    'short_narrower': dict(height=14, box=(0, 13), baseline=10, source='W5', drop=1),
    'small':          dict(height=13, box=(1, 12), baseline=10, source='W5'),
    'small_narrow':   dict(height=12, box=(1, 12), baseline=10, source='W5'),
    'small_narrower': dict(height=15, box=(1, 12), baseline=10, source='W5', drop=1),
}

LATIN_REF = [0xBB, 0xC7, 0xD1, 0xD5, 0xDB, 0xE0, 0xE4, 0xA1, 0xA9]   # A M W a g l p 0 8


def fg_only(rows):
    return [[v if v in F.INK else 0 for v in r] for r in rows]


def col(rows, x):
    return [r[x] for r in rows]


def diff(a, b):
    return sum(1 for p, q in zip(a, b) if (p in F.INK) != (q in F.INK) or (p in F.INK and p != q))


def stretch_one_row(rows, lo=5, hi=9, centre=7):
    """Insert a copy of the body row that duplicates most cleanly (a straight vertical run)."""
    best = min(range(lo, hi + 1), key=lambda r: (diff(rows[r], rows[r - 1]), abs(r - centre)))
    out = [list(r) for r in rows[:best + 1]] + [list(rows[best])] + [list(r) for r in rows[best + 1:]]
    return out[:16], best


def drop_one_column(rows):
    """Remove the interior foreground column most like its left neighbour (how upstream built
    about 70% of its narrow Latin glyphs; see notes/fonts.md)."""
    span = F.fg_columns(rows)
    if span is None or span[1] - span[0] < 4:
        return rows, None
    lo, hi = span[0] + 1, span[1] - 1
    centre = (span[0] + span[1]) / 2
    best = min(range(lo, hi + 1), key=lambda x: (diff(col(rows, x), col(rows, x - 1)), abs(x - centre)))
    return [r[:best] + r[best + 1:] + [F.BG] for r in rows], best


def left_align(rows):
    """FireRed placed its glyphs for a renderer that advanced by the *previous* glyph's width
    plus a +1 kern after letters that start at column 0 (pokefirered-heb src/text.c:854-887).
    Under the mirrored-blit design each glyph owns exactly [x, x+w), so the gap has to live
    inside the glyph: start the ink at column 0 (column 1 for the 1-2 column letters ו י ן,
    like Latin 'i'/'l') and keep one clear column at the right."""
    span = F.ink_columns(rows)
    fspan = F.fg_columns(rows)
    if span is None:
        return rows
    want = 1 if fspan and fspan[1] - fspan[0] <= 1 else 0
    return F.shift(rows, dx=want - span[0])


def fit_height(rows, height, baseline):
    """Drop the first row under the baseline until the foreground fits the blitted height.
    A clipped bottom shadow row is left alone: upstream's own g/p/y lose it in small_narrow."""
    while F.fg_rows(rows) and F.fg_rows(rows)[1] >= height:
        r = baseline + 1
        rows = rows[:r] + rows[r + 1:] + [[F.BG] * len(rows[0])]
    return rows


def width_rule(rows):
    """Advance = last ink column + 1, and at least one clear column after the last fg pixel.
    expansion ignores letterSpacing for Latin printers (src/text.c:1010), so the gap must be
    inside the advance."""
    ink, fg = F.ink_columns(rows), F.fg_columns(rows)
    if ink is None:
        return 3
    return max(ink[1] + 1, fg[1] + 2)


def rebuild_box(rows, width, box):
    out = []
    for y, r in enumerate(rows):
        line = []
        for x, v in enumerate(r):
            if v in F.INK:
                line.append(v)
            elif x < width and box[0] <= y <= box[1]:
                line.append(F.BOX)
            else:
                line.append(F.BG)
        out.append(line)
    return out


def load_sources(frlg_root):
    normal = F.FontPng.load(os.path.join(frlg_root, 'graphics/fonts/latin_normal.png'), 'latin')
    small = F.FontPng.load(os.path.join(frlg_root, 'graphics/fonts/latin_small.png'), 'frlg_small')
    w6 = [fg_only(F.normalize(normal.glyph(c))) for c in FRLG_CODES]
    w5 = [fg_only(F.pad(F.normalize(small.glyph(c)))) for c in FRLG_CODES]
    return {'W6': w6, 'W5': w5}


def derive(font, sources, stretch=True):
    g = GEOM[font]
    out, notes = [], []
    for i, src in enumerate(sources[g['source']]):
        rows = [list(r) for r in src]
        # FireRed baseline is row 10 in both source fonts.
        if g['baseline'] == 11:
            if stretch and g.get('stretch'):
                rows, r = stretch_one_row(rows)
                notes.append('dup row %d' % r)
            else:
                rows = F.shift(rows, dy=1)
                notes.append('shift +1')
        else:
            notes.append('')
        if g.get('drop'):
            rows, x = drop_one_column(rows)
            if x is not None:
                notes[-1] += ' drop col %d' % x
        if F.fg_rows(rows)[1] >= g['height']:
            rows = fit_height(rows, g['height'], g['baseline'])
            notes[-1] += ' descender shortened to fit height %d' % g['height']
        elif F.ink_rows(rows)[1] >= g['height']:
            notes[-1] += ' bottom shadow row clipped by height %d (as upstream g/p/y)' % g['height']
        rows = left_align(rows)
        w = width_rule(rows)
        out.append((rebuild_box(rows, w, g['box']), w))
    return out, notes


def strip_png(target_png, glyphs, path):
    t = F.FontPng.load(target_png)
    strip = F.FontPng(path, 256, 32, t.bit_depth, bytearray(256 * 32), t._before, t._after, 'latin')
    for i, (rows, w) in enumerate(glyphs):
        strip.set_glyph(i, rows)
    strip.save(path)


def compare_sheet(target_png, font, glyphs, path, zoom=4):
    from PIL import ImageDraw
    t = F.FontPng.load(target_png)
    widths = F.parse_width_tables(os.path.join(os.path.dirname(target_png), '../../src/fonts.c'))
    tname = 'gFont%sLatinGlyphWidths' % ''.join(p.capitalize() for p in font.split('_'))
    items = [('%02X' % c, t.glyph(c), widths[tname][c]) for c in LATIN_REF]
    items += [(F.HEBREW_NAMES[HEB[i]], rows, w) for i, (rows, w) in enumerate(glyphs)]
    sheet = F.contact_sheet(items, zoom=zoom, cols=18, title='%s: Latin reference + DRAFT Hebrew '
                            '(red bar = proposed width; green line = Latin baseline row %d)'
                            % (font, GEOM[font]['baseline']))
    d = ImageDraw.Draw(sheet)
    tile_h = 16 * zoom + 3 * zoom + 12 + 4
    for row in range((len(items) + 17) // 18):
        y = 16 + row * tile_h + 12 + (GEOM[font]['baseline'] + 1) * zoom
        d.line([(0, y), (sheet.width, y)], fill=(0, 160, 0))
    sheet.save(path)


def mock_line(glyph_of, text, window_w, height, zoom):
    """Lay out `text` with the chosen design: logical pen left to right, glyph drawn at
    physical x' = W - x - w (no Latin runs in this mock)."""
    from PIL import Image
    canvas = [[F.BOX] * window_w for _ in range(16)]
    x = 1
    for ch in text:
        rows, w = glyph_of(ch)
        px0 = window_w - x - w
        for yy in range(min(height, 16)):
            for xx in range(w):
                v = rows[yy][xx]
                if v in F.INK and 0 <= px0 + xx < window_w:
                    canvas[yy][px0 + xx] = v
        x += w
    return F.render(canvas, zoom)


def overview(hns, out, zoom=5, cw=8):
    """all_fonts_drafts.png: per font, Latin A M W a g then the 27 draft Hebrew glyphs."""
    from PIL import Image, ImageDraw
    fonts = list(GEOM)
    img = Image.new('RGB', (cw * zoom * 32 + 10, len(fonts) * (16 * zoom + 18) + 4), 'white')
    d = ImageDraw.Draw(img)
    for fi, fn in enumerate(fonts):
        heb = F.FontPng.load(os.path.join(out, '%s_hebrew_draft.png' % fn))
        lat = F.FontPng.load(os.path.join(hns, 'graphics/fonts/latin_%s.png' % fn))
        y = fi * (16 * zoom + 18) + 14
        d.text((5, y - 12), fn, fill=(0, 0, 0))
        cells = [lat.glyph(c) for c in (0xBB, 0xC7, 0xD1, 0xD5, 0xDB)] + [heb.glyph(i) for i in range(27)]
        for i, g in enumerate(cells):
            img.paste(F.render([r[:cw] for r in g], zoom), (i * cw * zoom + 5, y))
    img.save(os.path.join(out, 'all_fonts_drafts.png'))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--hns', default=paths.TREE, help='tree whose graphics/fonts set the format (default HNS_TREE)')
    ap.add_argument('--frlg', default=os.path.join(os.path.dirname(paths.REPO), 'pokefirered-heb'),
                    help='the FireRed Hebrew fork (default ../pokefirered-heb next to this repository)')
    ap.add_argument('--out', default=os.path.join(paths.WORK, 'font_drafts'))
    ap.add_argument('--no-stretch', action='store_true', help='shift the tall fonts down 1 row instead')
    a = ap.parse_args()
    os.makedirs(a.out, exist_ok=True)
    sources = load_sources(a.frlg)
    from PIL import Image, ImageDraw
    lines = []
    for font in GEOM:
        target = os.path.join(a.hns, 'graphics/fonts/latin_%s.png' % font)
        glyphs, notes = derive(font, sources, stretch=not a.no_stretch)
        strip_png(target, glyphs, os.path.join(a.out, '%s_hebrew_draft.png' % font))
        with open(os.path.join(a.out, '%s_hebrew_widths.txt' % font), 'w', encoding='utf-8') as fh:
            for ch, (rows, w), n in zip(HEB, glyphs, notes):
                fh.write('%s %-8s %d  %s\n' % (ch, F.HEBREW_NAMES[ch], w, n.strip()))
        compare_sheet(target, font, glyphs, os.path.join(a.out, 'compare_%s.png' % font))
        table = dict(zip(HEB, glyphs))
        lines.append((font, mock_line(lambda ch: table[ch] if ch != ' ' else ([[0] * 16] * 16, 3),
                                      'פוקימון של אש ומים', 120, GEOM[font]['height'], 3)))
    sheet = Image.new('RGB', (max(im.width for _, im in lines) + 130, sum(im.height + 6 for _, im in lines)), 'white')
    d = ImageDraw.Draw(sheet)
    y = 0
    for font, im in lines:
        d.text((2, y + 10), font, fill=(0, 0, 0))
        sheet.paste(im, (128, y))
        y += im.height + 6
    sheet.save(os.path.join(a.out, 'mock_lines.png'))
    overview(a.hns, a.out)
    print('wrote drafts to', os.path.abspath(a.out))


if __name__ == '__main__':
    main()
