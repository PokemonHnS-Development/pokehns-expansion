from kit import *
from check import check


def verify(P):
    """The written file keeps the English size, depth, palette and other chunks, and uses no
    palette index the English file did not use."""
    e, h = load_head(P), load(P)
    used = lambda im: {im.get(x, y) for y in range(im.height) for x in range(im.width)}
    assert check(P)[0] and e.palette == h.palette and used(h) <= used(e), P
    print('checked', P)


# Big outlined words of the minigames: the "go" sprite after the Berry Blender countdown, the
# 3-2-1 countdown's closing word of the wireless minigames (both sheets), and the Pokémon Jump
# bonus banners.
#
# The English words are drawn in 3-4 px strokes with an outline, far heavier than any font
# design, so the Hebrew letters are built here from rectangles: the shapes of the font's stroke
# designs (W4_7: the top bar of ד ה ק ר, the detached left leg of ה and ק, the notch and the
# open bottom-left corner of מ, the inward hook of ט, the protruding bottom bar of ב) drawn with
# the English stroke widths. Each glyph is a list of rows, '#' = fill; the outline and colours
# are added per sprite from the English art.
#
# Words: "go" is קדימה!, the Easy Chat word for GO AHEAD. The bonuses are the
# game's own words: EXCELLENT is מצוין as in the Pokémon Jump records ("”מצוין” ברצף") and the
# Easy Chat word, GOOD טוב and GREAT נהדר and NICE נחמד as the Easy Chat words.


# Letters whose diagonal does not come out of rectangles, drawn by hand at the size they are used
# (body rows, stem width): tsadi's right arm bends in to meet the left arm's slant at mid-height,
# as in W4_7, and the stem comes back out to the right edge below it.
HAND = {
    ('צ', 12, 4): ['####...####',
                   '####...####',
                   '.####..####',
                   '..####.###.',
                   '...######..',
                   '....######.',
                   '......#####',
                   '.......####',
                   '.......####',
                   '###########',
                   '###########',
                   '###########'],
}


def glyph(ch, H, S, B, D=0, W=None):
    """Fill mask of one letter: body H rows, stems S px, bars B rows, D descender rows (used by
    ק and ן only). Every mask has H + D rows."""
    if (ch, H, S) in HAND:
        rows = HAND[(ch, H, S)]
        return rows + ['.' * len(rows[0])] * D
    w = W or {'י': S + 3, 'ו': S + 2, 'ן': S + 2, '!': S, 'נ': S + 4}.get(ch, 3 * S - 1)
    g = [['.'] * w for _ in range(H + D)]

    def rect(x0, y0, x1, y1):
        for y in range(y0, y1 + 1):
            for x in range(x0, x1 + 1):
                g[y][x] = '#'

    def cut(*pts):
        for x, y in pts:
            g[y][x] = '.'
    leg = B + 3                                    # first row of a detached left leg
    if ch in 'הק':
        rect(0, 0, w - 1, B - 1)
        rect(w - S, 0, w - 1, H - 1)
        rect(0, leg, S - 1, H - 1 + (D if ch == 'ק' else 0))
    elif ch == 'ד':
        p = max(1, w // 5)                         # the bar runs past the stem
        rect(0, 0, w - 1, B - 1)
        rect(w - p - S, 0, w - p - 1, H - 1)
    elif ch == 'ר':
        rect(0, 0, w - 1, B - 1)
        rect(w - S, 0, w - 1, H - 1)
        # rounded corner, unlike ד
        cut((w - 1, 0), (w - 2, 0), (w - 3, 0), (w - 1, 1), (w - 2, 1), (w - 1, 2))
    elif ch == 'ח':
        rect(0, 0, w - 1, B - 1)
        rect(0, 0, S - 1, H - 1)
        rect(w - S, 0, w - 1, H - 1)
    elif ch == 'מ':
        inner = w - 2 * S
        notch, slit = max(1, inner // 3), max(1, inner // 2)
        rect(0, 0, S - 1, H - 1)
        rect(S + notch, 0, w - 1, B - 1)
        rect(0, B - 1, w - 1, B - 1)               # notch above the join of stem and bar
        rect(w - S, 0, w - 1, H - 1)
        rect(S + slit, H - B, w - 1, H - 1)        # open bottom-left corner
    elif ch == 'ט':
        rect(0, 0, S - 1, H - 1)
        rect(w - S, 0, w - 1, H - 1)
        rect(w - S - max(2, S // 2), 0, w - 1, B - 1)   # the hook turns inward
        rect(0, H - B, w - 1, H - 1)
        cut((0, H - 1), (w - 1, H - 1))
    elif ch == 'ב':
        p = max(1, w // 5)
        rect(0, 0, w - p - 1, B - 1)
        rect(w - p - S, 0, w - p - 1, H - 1)
        rect(0, H - B, w - 1, H - 1)
    elif ch == 'נ':
        rect(w - S - 2, 0, w - 1, B - 1)
        rect(w - S, 0, w - 1, H - 1)
        rect(0, H - B, w - 1, H - 1)
    elif ch in 'וןי':
        rect(0, 0, w - 1, B - 1)
        end = {'ו': H - 1, 'ן': H - 1 + D, 'י': H * 9 // 20 - 1}[ch]
        rect(w - S, 0, w - 1, end)
    elif ch == '!':
        rect(0, 0, S - 1, H - B - 4)
        rect(0, H - B, S - 1, H - 1)
    else:
        raise KeyError(ch)
    return [''.join(r) for r in g]


def word(text, H, S, B, D=0, gap=3, widths=None):
    """Right-to-left word mask (the string's first letter at the right)."""
    widths = widths or {}
    out = None
    for ch in reversed(text):
        m = glyph(ch, H, S, B, D, widths.get(ch))
        out = m if out is None else [a + '.' * gap + b for a, b in zip(out, m)]
    return out


def cells(m, x, y):
    return {(x + i, y + j) for j, r in enumerate(m) for i, c in enumerate(r) if c == '#'}


N4 = [(1, 0), (-1, 0), (0, 1), (0, -1)]
N8 = N4 + [(1, 1), (1, -1), (-1, 1), (-1, -1)]


def ring(pts, nb):
    return {(x + dx, y + dy) for x, y in pts for dx, dy in nb} - pts


def corners(fill):
    """Fill pixels open above or below and to the left or right: the rounded corners the English
    letters draw in a darker tone."""
    return {(x, y) for x, y in fill
            if ((x, y - 1) not in fill or (x, y + 1) not in fill)
            and ((x - 1, y) not in fill or (x + 1, y) not in fill)}


class Canvas:
    """A blank w x h image of indices."""
    def __init__(self, w, h, v=0):
        self.width, self.height = w, h
        self.px = [[v] * w for _ in range(h)]

    def get(self, x, y): return self.px[y][x]
    def put(self, x, y, v): self.px[y][x] = v


def outlined(c, fill, ink, inner, outer, inner_nb=N8, outer_nb=N4, aa=None):
    """Paint fill (ink: index or callable(x, y) -> index), an inner outline ring and an outer one;
    aa(x, y) gives the tone of a corner pixel (None: no corner tone)."""
    r1 = ring(fill, inner_nb)
    r2 = ring(fill | r1, outer_nb) if outer is not None else set()
    for pts, v in ((r2, outer), (r1, inner)):
        for x, y in pts:
            assert 0 <= x < c.width and 0 <= y < c.height, ('outside', x, y)
            c.put(x, y, v)
    cor = corners(fill) if aa else set()
    for x, y in fill:
        c.put(x, y, aa(x, y) if (x, y) in cor else (ink(x, y) if callable(ink) else ink))


def blit(dst, src, sx, sy, w, h, dx, dy):
    for y in range(h):
        for x in range(w):
            dst.put(dx + x, dy + y, src.get(sx + x, sy + y))


def preview(name, pairs, zoom):
    ims = []
    for lab, e, h in pairs:
        ims.append(side_by_side([render(e, zoom), render(h, zoom)], ['EN ' + lab, 'HE ' + lab]))
    from PIL import Image
    W = max(i.width for i in ims); Hh = sum(i.height for i in ims)
    o = Image.new('RGB', (W, Hh), (255, 255, 255)); y = 0
    for i in ims:
        o.paste(i, (0, y)); y += i.height
    o.save(OUT + '/' + name)
    return OUT + '/' + name


GO = 'קדימה!'

# --- Berry Blender: one 64x32 sprite. English START: yellow (12) fill rows 5..25 in 3-4 px
# strokes, a black (1) ring around it (8-neighbour) and a white (15) ring around that
# (4-neighbour). The Hebrew word fills the width the same way: 3-px stems and bars, an 18-row body
# (rows 5..22) and qof's leg down to row 26.
P = 'graphics/berry_blender/start.png'
c = Canvas(64, 32)
m = word(GO, 18, 3, 3, D=4, widths={'ק': 9, 'ד': 8, 'מ': 9, 'ה': 9, 'י': 4})
x0 = (64 - width(m)) // 2
outlined(c, cells(m, x0, 5), 12, 1, 15)
f = load_head(P)
blit(f, c, 0, 0, 64, 32, 0, 0)
print('blender', GO, 'fill', width(m), 'at', x0)
f.save(gpaths.write_target(P))
verify(P)
print(preview('berry_blender__start_pair.png', [('start', load_head(P), f)], 8))

# --- Wireless minigame countdown. English START: fill rows in three tones from the top, 3 rows
# of 14, 7 of 12, then 10; corners in 13 / 11 / 9; a dark (8) ring (8-neighbour) and a white (15)
# ring (4-neighbour). Hebrew: 4-px stems, 3-row bars, a 16-row body and qof's leg 4 rows lower,
# the same 20 fill rows as the English.
TONE = [(3, 14, 13), (7, 12, 11), (99, 10, 9)]


def tone(row):
    for n, v, a in TONE:
        if row < n:
            return v, a
        row -= n


def countdown(w, top):
    """The word on a w x 32 canvas, its fill starting at row `top`."""
    cv = Canvas(w, 32)
    m = word(GO, 16, 4, 3, D=4, widths={'מ': 15, 'י': 7, 'ה': 14, 'ק': 14, 'ד': 14})
    x = (w - width(m)) // 2
    outlined(cv, cells(m, x, top), lambda px, py: tone(py - top)[0], 8, 15,
             aa=lambda px, py: tone(py - top)[1])
    return cv, width(m), x


# 321start.png (64 px wide sheet): START is two 64x32 sprites side by side, tiles 48 (left half,
# sheet rows 48..79) and 80 (right half, rows 80..111); the fill starts on sprite row 6.
P = 'graphics/link/321start.png'
f = load_head(P)
cv, w, x = countdown(128, 6)
blit(f, cv, 0, 0, 64, 32, 0, 48)
blit(f, cv, 64, 0, 64, 32, 0, 80)
print('321start', GO, 'fill', w, 'at', x)
f.save(gpaths.write_target(P))
verify(P)
e = load_head(P)
ce, ch = Canvas(128, 32), Canvas(128, 32)
blit(ce, e, 0, 48, 64, 32, 0, 0); blit(ce, e, 0, 80, 64, 32, 64, 0)
blit(ch, f, 0, 48, 64, 32, 0, 0); blit(ch, f, 0, 80, 64, 32, 64, 0)
ce.palette = ch.palette = f.palette
print(preview('link__321start_pair.png', [('sheet', e, f), ('START as shown', ce, ch)], 6))

# 321start_static.png (32 px wide sheet): START is three 32x32 sprites, left to right the frames
# at sheet rows 96, 128 and 160; the fill starts on sprite row 2.
P = 'graphics/link/321start_static.png'
f = load_head(P)
cv, w, x = countdown(96, 2)
for i, y in enumerate((96, 128, 160)):
    blit(f, cv, 32 * i, 0, 32, 32, 0, y)
print('321start_static', GO, 'fill', w, 'at', x)
f.save(gpaths.write_target(P))
verify(P)
e = load_head(P)
ce, ch = Canvas(96, 32), Canvas(96, 32)
for i, y in enumerate((96, 128, 160)):
    blit(ce, e, 0, y, 32, 32, 32 * i, 0); blit(ch, f, 0, y, 32, 32, 32 * i, 0)
ce.palette = ch.palette = f.palette
print(preview('link__321start_static_pair.png', [('sheet', e, f), ('START as shown', ce, ch)], 6))

# --- Pokémon Jump bonus banners: bonuses.png is the tile sheet of a 512x512 background whose four
# 256x256 screens each hold one banner on map rows 0..3 (bonuses.bin; ShowBonus scrolls to screen
# bonusId / 2, bonusId % 2: NICE +50, GOOD +100, GREAT +200, EXCELLENT +500). The text is on map
# rows 1..2 (banner rows 8..23): yellow (10) letters with corners in 9 and a 4-neighbour dark (7)
# ring, 14 fill rows, 4-px stems, on horizontal stripes. The Hebrew word goes on the right and the
# English "+NN" (kept as drawn) moves to its left, the pair centred on the banner. Map rows 0 and 3
# reuse one tile across the banner and are not touched. The only text tile used twice is 0x63 in
# the EXCELLENT banner (map column 14, on row 1 and flipped on row 2): it must stay symmetric top to
# bottom, so the "+500" block is placed with its last "0", which is symmetric, on that column.
P = 'graphics/pokemon_jump/bonuses.png'
BANNERS = [  # (map screen, Hebrew, English, body rows, fixed x of the "+NN" block or None)
    (0, 'נחמד', 'NICE +50', 14, None),
    (2, 'טוב', 'GOOD +100', 14, None),
    (1, 'נהדר', 'GREAT +200', 14, None),
    (3, 'מצוין', 'EXCELLENT +500', 12, 46),     # final nun runs 2 rows below the 12-row body
]
INK = {7, 9, 10}
tm = read_bin('graphics/pokemon_jump/bonuses.bin')
f = load_head(P)
e = load_head(P)
TW = f.width // 8


class Banner:
    """Map rows 0..3 of one screen, columns c0..c1, as a w x 32 image (tile flips applied)."""
    def __init__(self, img, scr):
        self.img, self.base = img, scr * 1024
        cols = [i for i in range(32) if tm[self.base + 32 + i] & 0x3FF]
        self.c0, self.c1 = cols[0], cols[-1]
        self.width, self.height = (self.c1 - self.c0 + 1) * 8, 32
        self.palette = img.palette

    def at(self, x, y):
        en = tm[self.base + (y // 8) * 32 + self.c0 + x // 8]
        t, sx, sy = en & 0x3FF, x % 8, y % 8
        if en & 0x400: sx = 7 - sx
        if en & 0x800: sy = 7 - sy
        return (t % TW) * 8 + sx, (t // TW) * 8 + sy

    def get(self, x, y): return self.img.get(*self.at(x, y))
    def put(self, x, y, v): self.img.put(*self.at(x, y), v)


def runs(b):
    xs = [x for x in range(b.width) if any(b.get(x, y) in INK for y in range(8, 24))]
    out = []
    for x in xs:
        if out and x == out[-1][1] + 1: out[-1][1] = x
        else: out.append([x, x])
    return out


SPACE = 5                                          # background columns between "+NN" and the word
shown = []
for scr, heb_word, en_word, H, fixed in BANNERS:
    src, b = Banner(e, scr), Banner(f, scr)
    rs = runs(src)
    ndig = len(en_word.split('+')[1])
    xp, xb = rs[-1 - ndig][0], rs[-1][1]           # the "+" run to the last digit
    bg = {y: src.get(xp - 1, y) for y in range(8, 24)}
    assert all(v not in INK for v in bg.values())
    xa = rs[0][0]                                  # the English text, with its odd edge tones
    inside = {(x, y) for y in range(8, 24) for x in range(b.width)
              if src.get(x, y) == bg[y] or src.get(x, y) in INK or xa <= x <= xb}
    # the new rows 8..23: background, the "+NN" block, then the word (fill, corners, ring)
    m = word(heb_word, H, 4, 3, D=14 - H)
    blk = xb - xp + 1

    def draw_at(gx):
        cv = Canvas(b.width, 32)
        for y in range(8, 24):
            for x in range(b.width):
                cv.put(x, y, bg[y])
            for x in range(blk):
                cv.put(gx + x, y, src.get(xp + x, y))
        fill = cells(m, gx + blk + SPACE + 1, 9)
        outlined(cv, fill, 10, 7, None, inner_nb=N4, aa=lambda px, py: 9)
        marks = {(x, y) for y in range(8, 24) for x in range(b.width) if cv.get(x, y) != bg[y]}
        return cv, marks
    group = blk + SPACE + width(m) + 2
    row_lo = {y: min(x for x, yy in inside if yy == y) for y in range(8, 24)}
    row_hi = {y: max(x for x, yy in inside if yy == y) for y in range(8, 24)}

    def clearance(marks):
        # columns between the drawing and the banner's rim, at the tightest row
        return min(min(x - row_lo[y], row_hi[y] - x) for x, y in marks)
    fits = [gx for gx in range(b.width - group + 1)
            if (fixed is None or gx == fixed) and draw_at(gx)[1] <= inside]
    assert fits, (en_word, 'does not fit')
    gx = max(fits, key=lambda g: (clearance(draw_at(g)[1]), -abs(g + group / 2 - b.width / 2)))
    cv, marks = draw_at(gx)
    # write back through the tilemap; a tile shown twice must get the same pixels from both places
    got = {}
    for y in range(8, 24):
        for x in range(b.width):
            v = cv.get(x, y) if (x, y) in inside else src.get(x, y)
            k = b.at(x, y)
            assert got.get(k, v) == v, ('tile shown twice disagrees', en_word, x, y)
            got[k] = v
    for k, v in got.items():
        f.put(*k, v)
    print('bonus', en_word, '->', heb_word, 'x', gx, '..', gx + group - 1, 'of', b.width, 'word fill', width(m),
          'clearance', clearance(marks))
    shown.append((en_word, src, Banner(f, scr)))

f.save(gpaths.write_target(P))
verify(P)
print(preview('pokemon_jump__bonuses_banners_pair.png', shown, 5))
print(pair(P, 4))
