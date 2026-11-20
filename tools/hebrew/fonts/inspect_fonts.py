#!/usr/bin/env python3
"""Read and write glyph cells in the GBA Latin font PNGs (pokeemerald-expansion and pokefirered).

Library use:

    import inspect_fonts as F
    font = F.FontPng.load('graphics/fonts/latin_normal.png')
    g = font.glyph(0xBB)                 # 'A' -> 16 rows of 16 palette indices
    print(F.ascii(g))
    font.set_glyph(0x50, g)              # copy it into an unused cell
    font.save('/tmp/latin_normal.png')   # same bit depth, PLTE, tRNS and ancillary chunks

Layouts
  'latin'       pokeemerald / expansion / FRLG normal-male-female: 256 px wide, one glyph per
                16x16 cell, 16 cells per row, glyph id = row*16 + col. gbagfx writes the four
                8x8 tiles of a cell as TL, TR, BL, BR (tools/gbagfx/font.c ConvertToLatinFont),
                and the game reads glyph id at u16 offset 0x20*id (64 bytes).
  'frlg_small'  pokefirered latin_small.png: the game reads 8x16 glyphs, 32 bytes each
                (sFontSmallLatinGlyphs + 0x10*id), but gbagfx still packs the PNG as 16x16
                cells. So cell k holds glyph 2k as TL (top) + TR (bottom) and glyph 2k+1 as
                BL (top) + BR (bottom).

Palette indices are what the game sees: gbagfx reduces every PNG index modulo 4
(tools/gbagfx/convert_png.c ConvertBitDepth), then src/text.c GenerateFontHalfRowLookupTable maps
0 -> background, 1 -> foreground, 2 -> shadow, 3 -> accent (accent == background colour in every
expansion FontInfo, so 3 is the white 'box' that renders as background).

CLI:
  inspect_fonts.py info PNG...
  inspect_fonts.py dump PNG CODE [--layout L]
  inspect_fonts.py metrics PNG [--codes 0x01-0x1B] [--layout L]
  inspect_fonts.py sheet PNG OUT.png [--codes ...] [--zoom 4] [--layout L] [--charmap charmap.txt]
                         [--widths fonts.c:TableName]
  inspect_fonts.py extract PNG OUTDIR [--codes ...] [--zoom 4] [--layout L] [--prefix name]
  inspect_fonts.py verify-latfont PNG LATFONT
  inspect_fonts.py widths C_FILE [TableName]
"""

import argparse
import os
import re
import struct
import sys
import zlib

BG, FG, SHADOW, BOX = 0, 1, 2, 3
INK = (FG, SHADOW)

# Display colours for renders (the gbagfx font palette, tools/gbagfx/font.c gFontPalette).
DISPLAY_PALETTE = [(0x90, 0xC8, 0xFF), (0x38, 0x38, 0x38), (0xD8, 0xD8, 0xD8), (0xFF, 0xFF, 0xFF)]

PNG_SIG = b'\x89PNG\r\n\x1a\n'

# ASCII labels for Hebrew letters (PIL's default bitmap font cannot draw Hebrew).
HEBREW_NAMES = dict(zip(
    'אבגדהוזחטיכלמנסעפצקרשתןםץףך',
    ['alef', 'bet', 'gimel', 'dalet', 'he', 'vav', 'zayin', 'het', 'tet', 'yod', 'kaf', 'lamed',
     'mem', 'nun', 'samekh', 'ayin', 'pe', 'tsadi', 'qof', 'resh', 'shin', 'tav',
     'nun.f', 'mem.f', 'tsadi.f', 'pe.f', 'kaf.f']))


# ---------------------------------------------------------------- PNG I/O (indexed only)

def _chunks(data):
    i = 8
    while i < len(data):
        (ln,) = struct.unpack('>I', data[i:i + 4])
        typ = data[i + 4:i + 8]
        yield typ, data[i + 8:i + 8 + ln]
        i += 12 + ln


def _chunk(typ, body):
    return struct.pack('>I', len(body)) + typ + body + struct.pack('>I', zlib.crc32(typ + body) & 0xFFFFFFFF)


def _paeth(a, b, c):
    p = a + b - c
    pa, pb, pc = abs(p - a), abs(p - b), abs(p - c)
    if pa <= pb and pa <= pc:
        return a
    return b if pb <= pc else c


def _unfilter(raw, width, height, bit_depth):
    bpp = max(1, bit_depth // 8)                       # bytes per pixel for filtering (indexed)
    stride = (width * bit_depth + 7) // 8
    out = bytearray(stride * height)
    prev = bytearray(stride)
    pos = 0
    for y in range(height):
        ftype = raw[pos]
        line = bytearray(raw[pos + 1:pos + 1 + stride])
        pos += 1 + stride
        for x in range(stride):
            a = line[x - bpp] if x >= bpp else 0
            b = prev[x]
            c = prev[x - bpp] if x >= bpp else 0
            if ftype == 1:
                line[x] = (line[x] + a) & 0xFF
            elif ftype == 2:
                line[x] = (line[x] + b) & 0xFF
            elif ftype == 3:
                line[x] = (line[x] + ((a + b) >> 1)) & 0xFF
            elif ftype == 4:
                line[x] = (line[x] + _paeth(a, b, c)) & 0xFF
        out[y * stride:(y + 1) * stride] = line
        prev = line
    return out, stride


def _unpack(rows, width, height, bit_depth, stride):
    px = bytearray(width * height)
    per = 8 // bit_depth if bit_depth < 8 else 1
    mask = (1 << bit_depth) - 1
    for y in range(height):
        base = y * stride
        for x in range(width):
            if bit_depth == 8:
                px[y * width + x] = rows[base + x]
            else:
                byte = rows[base + x // per]
                shift = 8 - bit_depth * (x % per + 1)
                px[y * width + x] = (byte >> shift) & mask
    return px


def _pack(px, width, height, bit_depth):
    stride = (width * bit_depth + 7) // 8
    raw = bytearray()
    per = 8 // bit_depth if bit_depth < 8 else 1
    for y in range(height):
        raw.append(0)
        line = bytearray(stride)
        for x in range(width):
            v = px[y * width + x]
            if v >> bit_depth:
                raise ValueError('index %d does not fit %d-bit PNG at (%d,%d)' % (v, bit_depth, x, y))
            if bit_depth == 8:
                line[x] = v
            else:
                line[x // per] |= v << (8 - bit_depth * (x % per + 1))
        raw += line
    return bytes(raw)


class FontPng:
    """An indexed font PNG kept as raw palette indices, with its non-pixel chunks preserved."""

    def __init__(self, path, width, height, bit_depth, pixels, chunks_before, chunks_after, layout):
        self.path = path
        self.width = width
        self.height = height
        self.bit_depth = bit_depth
        self.pixels = pixels                 # bytearray, width*height palette indices
        self._before = chunks_before         # [(type, body)] between IHDR and IDAT
        self._after = chunks_after           # [(type, body)] between IDAT and IEND
        self.layout = layout

    # -- load / save
    @classmethod
    def load(cls, path, layout=None):
        data = open(path, 'rb').read()
        if data[:8] != PNG_SIG:
            raise ValueError('%s: not a PNG' % path)
        before, after, idat = [], [], b''
        ihdr = None
        seen_idat = False
        for typ, body in _chunks(data):
            if typ == b'IHDR':
                ihdr = body
            elif typ == b'IDAT':
                idat += body
                seen_idat = True
            elif typ == b'IEND':
                break
            else:
                (after if seen_idat else before).append((typ, body))
        width, height, bit_depth, color_type, _comp, _filt, interlace = struct.unpack('>IIBBBBB', ihdr)
        if color_type != 3:
            raise ValueError('%s: colour type %d, expected 3 (indexed)' % (path, color_type))
        if interlace:
            raise ValueError('%s: interlaced PNGs are not supported' % path)
        rows, stride = _unfilter(zlib.decompress(idat), width, height, bit_depth)
        px = _unpack(rows, width, height, bit_depth, stride)
        if layout is None:
            layout = guess_layout(path, width, height)
        return cls(path, width, height, bit_depth, px, before, after, layout)

    def save(self, path=None, bit_depth=None):
        """Write the PNG back with the same chunks; only IHDR's bit depth (optional) and IDAT change."""
        path = path or self.path
        bd = bit_depth or self.bit_depth
        out = bytearray(PNG_SIG)
        out += _chunk(b'IHDR', struct.pack('>IIBBBBB', self.width, self.height, bd, 3, 0, 0, 0))
        for typ, body in self._before:
            out += _chunk(typ, body)
        out += _chunk(b'IDAT', zlib.compress(_pack(self.pixels, self.width, self.height, bd), 9))
        for typ, body in self._after:
            out += _chunk(typ, body)
        out += _chunk(b'IEND', b'')
        with open(path, 'wb') as fh:
            fh.write(out)

    # -- palette
    @property
    def palette(self):
        for typ, body in self._before:
            if typ == b'PLTE':
                return [tuple(body[i:i + 3]) for i in range(0, len(body), 3)]
        return []

    @property
    def transparency(self):
        for typ, body in self._before:
            if typ == b'tRNS':
                return list(body)
        return None

    def index_counts(self):
        counts = {}
        for v in self.pixels:
            counts[v] = counts.get(v, 0) + 1
        return dict(sorted(counts.items()))

    # -- pixels
    def get(self, x, y):
        return self.pixels[y * self.width + x]

    def put(self, x, y, v):
        self.pixels[y * self.width + x] = v

    def _rect(self, x0, y0, w, h):
        return [[self.get(x0 + x, y0 + y) for x in range(w)] for y in range(h)]

    def _put_rect(self, x0, y0, rows):
        for y, row in enumerate(rows):
            for x, v in enumerate(row):
                self.put(x0 + x, y0 + y, v)

    # -- glyphs
    @property
    def num_glyphs(self):
        cells = (self.width // 16) * (self.height // 16)
        return cells * 2 if self.layout == 'frlg_small' else cells

    @property
    def glyph_size(self):
        return (8, 16) if self.layout == 'frlg_small' else (16, 16)

    def cell_origin(self, code):
        """Top-left pixel of the 16x16 cell that holds `code` (latin layout)."""
        return (code % 16) * 16, (code // 16) * 16

    def glyph(self, code):
        """Return the glyph as a list of rows of palette indices (16x16, or 8x16 for frlg_small)."""
        if self.layout == 'frlg_small':
            cell = code >> 1
            cx, cy = (cell % 16) * 16, (cell // 16) * 16
            ty = cy + (8 if code & 1 else 0)
            return self._rect(cx, ty, 8, 8) + self._rect(cx + 8, ty, 8, 8)
        x, y = self.cell_origin(code)
        return self._rect(x, y, 16, 16)

    def set_glyph(self, code, rows):
        if self.layout == 'frlg_small':
            if len(rows) != 16 or any(len(r) != 8 for r in rows):
                raise ValueError('frlg_small glyphs are 8x16')
            cell = code >> 1
            cx, cy = (cell % 16) * 16, (cell // 16) * 16
            ty = cy + (8 if code & 1 else 0)
            self._put_rect(cx, ty, rows[:8])
            self._put_rect(cx + 8, ty, rows[8:])
            return
        if len(rows) > 16 or any(len(r) > 16 for r in rows):
            raise ValueError('latin glyphs are at most 16x16')
        x, y = self.cell_origin(code)
        self._put_rect(x, y, rows)

    # -- latfont
    def to_latfont(self):
        """Bytes exactly as gbagfx `png -> latfont` would write them (indices reduced mod 4)."""
        if self.width != 256 or self.height % 16:
            raise ValueError('latin fonts are 256 px wide and a multiple of 16 tall')
        out = bytearray()
        for row in range(self.height // 16):
            for col in range(16):
                for tile in range(4):
                    px0 = col * 16 + (tile & 1) * 8
                    for i in range(8):
                        py = row * 16 + (tile >> 1) * 8 + i
                        b0 = b1 = 0
                        for k in range(4):
                            b0 |= (self.get(px0 + k, py) & 3) << (6 - 2 * k)
                            b1 |= (self.get(px0 + 4 + k, py) & 3) << (6 - 2 * k)
                        # gbagfx swaps the two bytes of each 8-pixel row (font.c ConvertToLatinFont)
                        out += bytes((b1, b0))
        return bytes(out)


def guess_layout(path, width, height):
    name = os.path.basename(path)
    if 'pokefirered' in os.path.abspath(path) and name == 'latin_small.png':
        return 'frlg_small'
    return 'latin'


# ---------------------------------------------------------------- glyph helpers

def normalize(rows):
    """Reduce indices mod 4, as gbagfx does when it builds the .latfont."""
    return [[v & 3 for v in r] for r in rows]


def ink_columns(rows, ink=INK):
    cols = [x for x in range(len(rows[0])) if any(r[x] in ink for r in rows)]
    return (cols[0], cols[-1]) if cols else None


def ink_rows(rows, ink=INK):
    ys = [y for y, r in enumerate(rows) if any(v in ink for v in r)]
    return (ys[0], ys[-1]) if ys else None


def fg_rows(rows):
    return ink_rows(rows, ink=(FG,))


def fg_columns(rows):
    return ink_columns(rows, ink=(FG,))


def box_extent(rows):
    """Bounding box (x0, y0, x1, y1) of every non-background pixel, i.e. the white 'box' plus ink."""
    xs = [x for x in range(len(rows[0])) if any(r[x] != BG for r in rows)]
    ys = [y for y, r in enumerate(rows) if any(v != BG for v in r)]
    if not xs:
        return None
    return xs[0], ys[0], xs[-1], ys[-1]


def is_blank(rows):
    return ink_rows(rows) is None


def ascii(rows, chars='.#o_'):
    """Text picture: '.' bg, '#' fg, 'o' shadow, '_' box; anything >=4 prints as its hex digit."""
    out = []
    for r in rows:
        out.append(''.join(chars[v] if v < 4 else '%x' % v for v in r))
    return '\n'.join(out)


def from_ascii(text, chars='.#o_'):
    return [[chars.index(c) for c in line] for line in text.strip('\n').splitlines()]


def mirror(rows):
    return [list(reversed(r)) for r in rows]


def shift(rows, dx=0, dy=0, fill=BG):
    h, w = len(rows), len(rows[0])
    out = [[fill] * w for _ in range(h)]
    for y in range(h):
        for x in range(w):
            sx, sy = x - dx, y - dy
            if 0 <= sx < w and 0 <= sy < h:
                out[y][x] = rows[sy][sx]
    return out


def pad(rows, w=16, h=16, fill=BG):
    out = [list(r) + [fill] * (w - len(r)) for r in rows]
    return out + [[fill] * w for _ in range(h - len(out))]


def drop_column(rows, x):
    """Remove column x and pad on the right: the narrow-font derivation primitive."""
    return [r[:x] + r[x + 1:] + [r[-1] if r[-1] == BG else BG] for r in rows]


def render(rows, zoom=4, palette=DISPLAY_PALETTE, grid=False, width_marker=None):
    """PIL image of one glyph. width_marker draws a red tick under the advance width."""
    from PIL import Image, ImageDraw
    h, w = len(rows), len(rows[0])
    extra = 3 * zoom if width_marker is not None else 0
    im = Image.new('RGB', (w * zoom, h * zoom + extra), (40, 40, 40))
    px = im.load()
    for y in range(h):
        for x in range(w):
            v = rows[y][x]
            col = palette[v] if v < len(palette) else (255, 0, 255)
            for dy in range(zoom):
                for dx in range(zoom):
                    px[x * zoom + dx, y * zoom + dy] = col
    d = ImageDraw.Draw(im)
    if grid:
        for x in range(0, w * zoom, zoom * 8):
            d.line([(x, 0), (x, h * zoom)], fill=(255, 0, 0))
    if width_marker is not None:
        d.rectangle([0, h * zoom + zoom, width_marker * zoom - 1, h * zoom + 2 * zoom - 1], fill=(220, 40, 40))
    return im


def contact_sheet(items, zoom=4, cols=16, label_height=12, title=None):
    """items: [(label, rows, width_or_None)]. Returns a PIL image."""
    from PIL import Image, ImageDraw
    if not items:
        raise ValueError('nothing to draw')
    tiles = [(lab, render(rows, zoom, width_marker=w)) for lab, rows, w in items]
    tw = max(t.width for _, t in tiles) + 4
    th = max(t.height for _, t in tiles) + label_height + 4
    rows_n = (len(tiles) + cols - 1) // cols
    top = 16 if title else 0
    sheet = Image.new('RGB', (cols * tw, rows_n * th + top), (255, 255, 255))
    d = ImageDraw.Draw(sheet)
    if title:
        d.text((2, 2), title, fill=(0, 0, 0))
    for i, (lab, t) in enumerate(tiles):
        x, y = (i % cols) * tw, (i // cols) * th + top
        d.text((x + 2, y + 1), lab, fill=(0, 0, 0))
        sheet.paste(t, (x + 2, y + label_height))
    return sheet


# ---------------------------------------------------------------- tables

def parse_width_tables(c_path):
    """{TableName: [widths]} for every `... u8 <Name>LatinGlyphWidths[] = { ... };` in a C file."""
    src = open(c_path, encoding='utf-8').read()
    tables = {}
    for m in re.finditer(r'u8\s+([gs]Font\w*?LatinGlyphWidths)\s*\[\s*\]\s*=\s*\{(.*?)\};', src, re.S):
        body = re.sub(r'/\*.*?\*/', '', m.group(2), flags=re.S)
        body = re.sub(r'//[^\n]*', '', body)
        tables[m.group(1)] = [int(v, 0) for v in re.findall(r'0x[0-9A-Fa-f]+|\d+', body)]
    return tables


def parse_charmap(path):
    """{glyph id: [names]} for single-byte entries and F9-prefixed extra symbols (id | 0x100)."""
    names = {}
    for line in open(path, encoding='utf-8'):
        line = line.split('@')[0].rstrip()
        m = re.match(r"^('(?:\\.|[^'])+'|\w+)\s*=\s*((?:[0-9A-Fa-f]{2}\s*)+)$", line)
        if not m:
            continue
        name, codes = m.group(1), m.group(2).split()
        if len(codes) == 1:
            gid = int(codes[0], 16)
        elif len(codes) == 2 and codes[0].upper() == 'F9':
            gid = 0x100 | int(codes[1], 16)
        else:
            continue
        names.setdefault(gid, []).append(name.strip("'"))
    return names


def parse_codes(spec, limit):
    if not spec:
        return list(range(limit))
    out = []
    for part in spec.split(','):
        if '-' in part:
            a, b = part.split('-')
            out += list(range(int(a, 0), int(b, 0) + 1))
        else:
            out.append(int(part, 0))
    return out


# ---------------------------------------------------------------- CLI

def _load_widths(spec):
    if not spec:
        return None
    path, _, name = spec.partition(':')
    tables = parse_width_tables(path)
    if not name:
        raise SystemExit('give --widths FILE:TableName; tables: %s' % ', '.join(tables))
    return tables[name]


def cmd_info(a):
    for p in a.png:
        f = FontPng.load(p, a.layout)
        print('%s: %dx%d, %d-bit indexed, layout %s, %d glyphs of %dx%d' % (
            p, f.width, f.height, f.bit_depth, f.layout, f.num_glyphs, *f.glyph_size))
        print('  palette:', f.palette, ' tRNS:', f.transparency)
        print('  index counts:', f.index_counts())


def cmd_dump(a):
    f = FontPng.load(a.png, a.layout)
    print(ascii(f.glyph(int(a.code, 0))))


def cmd_metrics(a):
    f = FontPng.load(a.png, a.layout)
    widths = _load_widths(a.widths)
    names = parse_charmap(a.charmap) if a.charmap else {}
    print('code  name        ink_x    ink_y    fg_y     box(x0,y0,x1,y1)  width')
    for c in parse_codes(a.codes, f.num_glyphs):
        g = f.glyph(c)
        print('0x%03X %-10s  %-8s %-8s %-8s %-17s %s' % (
            c, ' '.join(names.get(c, []))[:10], ink_columns(g), ink_rows(g), fg_rows(g),
            box_extent(g), widths[c] if widths and c < len(widths) else ''))


def cmd_sheet(a):
    f = FontPng.load(a.png, a.layout)
    widths = _load_widths(a.widths)
    names = parse_charmap(a.charmap) if a.charmap else {}
    items = []
    for c in parse_codes(a.codes, f.num_glyphs):
        lab = '%02X' % c
        if names.get(c):
            n = names[c][0]
            if n in HEBREW_NAMES:
                lab += ' ' + HEBREW_NAMES[n]
            elif len(n) <= 2 and n.isascii():
                lab += ' ' + n
        g = f.glyph(c)
        items.append((lab, normalize(g) if a.normalize else g, widths[c] if widths and c < len(widths) else None))
    contact_sheet(items, zoom=a.zoom, cols=a.cols, title=a.title or os.path.basename(a.png)).save(a.out)
    print('wrote', a.out)


def cmd_extract(a):
    f = FontPng.load(a.png, a.layout)
    widths = _load_widths(a.widths)
    os.makedirs(a.outdir, exist_ok=True)
    prefix = a.prefix or os.path.splitext(os.path.basename(a.png))[0]
    names = parse_charmap(a.charmap) if a.charmap else {}
    for c in parse_codes(a.codes, f.num_glyphs):
        g = normalize(f.glyph(c)) if a.normalize else f.glyph(c)
        n = names.get(c, [''])[0]
        n = HEBREW_NAMES.get(n, n if re.fullmatch(r'\w+', n or '-') else '')
        fname = '%s_%03X%s.png' % (prefix, c, '_' + n if n else '')
        render(g, a.zoom, width_marker=widths[c] if widths else None).save(os.path.join(a.outdir, fname))
    print('wrote glyphs to', a.outdir)


def cmd_verify(a):
    f = FontPng.load(a.png, a.layout)
    mine = f.to_latfont()
    theirs = open(a.latfont, 'rb').read()
    same = mine == theirs
    print('%s -> %d bytes; %s %d bytes; %s' % (a.png, len(mine), a.latfont, len(theirs),
                                             'IDENTICAL' if same else 'DIFFERENT'))
    if not same:
        diff = next(i for i in range(min(len(mine), len(theirs))) if mine[i] != theirs[i])
        print('first difference at byte 0x%X (glyph 0x%X)' % (diff, diff // 64))
        sys.exit(1)


def cmd_widths(a):
    for name, t in parse_width_tables(a.cfile).items():
        if a.table and name != a.table:
            continue
        print(name, len(t))
        for r in range(0, len(t), 16):
            print('  %03X: %s' % (r, ' '.join('%2d' % v for v in t[r:r + 16])))


def main(argv=None):
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument('--layout', choices=['latin', 'frlg_small'], default=None)
    sub = p.add_subparsers(dest='cmd', required=True)
    s = sub.add_parser('info'); s.add_argument('png', nargs='+'); s.set_defaults(fn=cmd_info)
    s = sub.add_parser('dump'); s.add_argument('png'); s.add_argument('code'); s.set_defaults(fn=cmd_dump)
    for name, fn in (('metrics', cmd_metrics), ('sheet', cmd_sheet), ('extract', cmd_extract)):
        s = sub.add_parser(name)
        s.add_argument('png')
        if name == 'sheet':
            s.add_argument('out')
        if name == 'extract':
            s.add_argument('outdir')
            s.add_argument('--prefix')
        s.add_argument('--codes')
        s.add_argument('--widths', help='C_FILE:TableName')
        s.add_argument('--charmap')
        s.add_argument('--zoom', type=int, default=4)
        s.add_argument('--cols', type=int, default=16)
        s.add_argument('--title')
        s.add_argument('--normalize', action='store_true',
                       help='reduce indices mod 4 first, i.e. show what the ROM draws (raw >=4 shows magenta)')
        s.set_defaults(fn=fn)
    s = sub.add_parser('verify-latfont'); s.add_argument('png'); s.add_argument('latfont'); s.set_defaults(fn=cmd_verify)
    s = sub.add_parser('widths'); s.add_argument('cfile'); s.add_argument('table', nargs='?'); s.set_defaults(fn=cmd_widths)
    a = p.parse_args(argv)
    a.fn(a)


if __name__ == '__main__':
    main()
