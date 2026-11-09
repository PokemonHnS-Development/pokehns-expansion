#!/usr/bin/env python3
"""Build the Hebrew versions of the coreui graphics.

Every file is rebuilt from the English release PNG (gfx.BASE_REF), so the script can be re-run.
Only pixel indices change; the PNG chunks (IHDR fields, PLTE, tRNS, ...) are written back as read.

    python3 make_coreui.py [--only SUBSTR] [--dry]
"""

import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import heb                      # noqa: E402
from draw import (draw, fill_from_column, fill_rect, ink_points, place, replace_in_rect, text,  # noqa: E402
                  DIRS_RDB, DIRS_8)
from gfx import load, BASE_REF, TREE, Canvas, tiles_to_sprite, sprite_to_tiles, gather_tiles, scatter_tiles  # noqa: E402
import gpaths  # noqa: E402

WARN = []
JOBS = []


def job(path):
    def deco(fn):
        JOBS.append((path, fn))
        return fn
    return deco


def warn(msg):
    WARN.append(msg)
    print('WARN', msg)


def check_inside(bm, x, y, allowed, label):
    for j, row in enumerate(bm):
        for i, ch in enumerate(row):
            if ch == '#' and not allowed(x + i, y + j):
                warn('%s: ink at (%d,%d) outside the allowed area' % (label, x + i, y + j))
                return


# ------------------------------------------------------------------ bold glyphs for the HP labels
# The HP labels use a bold 4/5-row alphabet (2-px left stems). These are drawn for this label only.
BOLD = {
    4: {'ח': ['####', '##.#', '##.#', '##.#'],
        'נ': ['##.', '.##', '.##', '###'],
        '”': ['#.#', '#.#', '...', '...']},
    5: {'ח': ['####', '##.#', '##.#', '##.#', '##.#'],
        'נ': ['##.', '.##', '.##', '.##', '###'],
        '”': ['#.#', '#.#', '...', '...', '...']},
}


def bold_word(word, rows, gap=1):
    gl = [BOLD[rows][ch] for ch in reversed(word)]
    out = [''] * rows
    for k, g in enumerate(gl):
        if k:
            out = [r + '.' * gap for r in out]
        out = [out[y] + g[y] for y in range(rows)]
    return out


# ------------------------------------------------------------------ HP bars
def hp_label(p, gen4):
    # Label background: columns 9..22 rows 1..6 (hns) / 9..23 (gen4). Clear the English, keep the frame.
    if gen4:
        fill_from_column(p, 10, 22, 2, 5, 9)
        bm = bold_word('נ”ח', 4)
        x = place(bm, 10, 22)
        draw(p, bm, x, 2, 8)
    else:
        fill_from_column(p, 10, 22, 2, 5, 9)
        bm = bold_word('נ”ח', 4)
        x = place(bm, 10, 21)
        grad = {2: 7, 3: 7, 4: 8, 5: 9}           # the English HP's per-row gradient
        draw(p, bm, x, 2, lambda px, py, r: grad[py])


@job('graphics/battle_interface/hns/hpbar.png')
def _(p):
    hp_label(p, gen4=False)


@job('graphics/battle_interface/gen4/hpbar.png')
def _(p):
    hp_label(p, gen4=True)


# ------------------------------------------------------------------ status tags
TAGS_BATTLE = ['רעל', 'שיתוק', 'שינה', 'קפוא', 'כוויה', 'קור']      # PSN PAR SLP FRZ BRN FRB
TAGS_GEN4 = ['רעל', 'שיתוק', 'שינה', 'קפוא', 'כוויה', 'כוויה']      # PSN PAR SLP FRZ BRN BRN
TAGS_ICONS = ['רעל', 'שיתוק', 'שינה', 'קפוא', 'כוויה', None, 'מעולף', 'קור']  # ... PkRS FNT FRB
TEXT = 2

# T6N: T6 with 3-px ayin and mem (ayin: two arms joining into a tail at the bottom left; mem: the
# kinked top and a base open at the bottom left, as the game's small-font mem). In T6 מעולף is 19 px and
# covers the FNT pill's edge columns; with these it is 17 px.
heb.SETS['T6N'] = dict(heb.SETS['T6'], **{
    'ע': ['...', '#.#', '#.#', '#.#', '#.#', '.##', '##.', '...'],
    'מ': ['...', '#..', '.##', '#.#', '#.#', '#.#', '.##', '...'],
})
# Per-icon (glyph set, left x) for status_icons.png. FNT מעולף sits at x7-23 (final pe 7-9,
# lamed 11-13, vav 15, ayin 17-19, mem 21-23), so x6 and x24-25 stay tag-coloured as in the
# English; the lamed's ascender lands on the top row (tag-coloured at x8-23) and the pe's stem
# on the bottom row at x9.
ICONS_OVERRIDES = {6: ('T6N', 7)}


def status_tags(p, words, tag_x0, tag_x1, text_x0, text_x1, colour_x, overrides=None):
    """tag_x0..tag_x1: the tag's widest span (rows 2-5); text_x0..text_x1: where the English text sits.
    overrides: {tag index: (glyph set, left x)} for words that are not placed automatically."""
    overrides = overrides or {}
    for k, word in enumerate(words):
        y0 = 8 * k
        tag = p.get(colour_x, y0 + 3)
        orig = {(x, y): p.get(x, y) for x in range(p.width) for y in range(y0, y0 + 8)}

        def interior(x, y, orig=orig, tag=tag):
            v = orig.get((x, y))
            if v == tag:
                return True
            return v == TEXT and text_x0 <= x <= text_x1 and y0 + 1 <= y <= y0 + 6
        if word is None:
            continue
        for y in range(y0 + 1, y0 + 7):
            for x in range(text_x0, text_x1 + 1):
                if p.get(x, y) == TEXT:
                    p.put(x, y, tag)
        setname, x = overrides.get(k, ('T6', None))
        bm = text(word, setname)

        def outside(x, bm=bm, interior=interior):
            return [(px, py) for px, py, _ in ink_points(bm, x, y0) if not interior(px, py)]
        if x is None:
            # A word as wide as the tag (שיתוק) cannot avoid every rounded corner: take the position
            # that loses the fewest ink pixels (ties: the right one, so qof keeps its descender and
            # shin loses the top pixel of its right arm), and never paint over the tag's outline.
            xc = place(bm, tag_x0 + 1, tag_x1 - 1)
            x = min((xc, xc + 1, xc - 1), key=lambda cx: (len(outside(cx)), -cx))
        lost = outside(x)
        if lost:
            warn('tag %d %s: %d ink pixel(s) on the tag outline left out: %s' % (k, word, len(lost), lost))
        for px, py, _ in ink_points(bm, x, y0):
            if interior(px, py):
                p.put(px, py, TEXT)


for _n in ('', '2', '3', '4'):
    JOBS.append(('graphics/battle_interface/hns/status%s.png' % _n,
                 lambda p: status_tags(p, TAGS_BATTLE, 0, 19, 3, 17, 0)))
    JOBS.append(('graphics/battle_interface/gen4/status%s.png' % _n,
                 lambda p: status_tags(p, TAGS_GEN4, 0, 19, 3, 17, 0)))


@job('graphics/interface/status_icons.png')
def _(p):
    status_tags(p, TAGS_ICONS, 6, 25, 7, 24, 6, ICONS_OVERRIDES)


# ------------------------------------------------------------------ shared helpers (second batch)
def lo(v):
    return v & 15


def clear_where(c, x0, x1, y0, y1, pred, bg):
    """Set every pixel in the rect for which pred(v) holds to bg (index or f(x, y))."""
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            if pred(c.get(x, y)):
                c.put(x, y, bg(x, y) if callable(bg) else bg)


def bold(bm):
    """Embolden a bitmap: every ink pixel also inks the pixel to its right (width + 1)."""
    out = []
    for r in bm:
        r2 = r + '.'
        out.append(''.join('#' if r2[i] == '#' or (i and r2[i - 1] == '#') else '.' for i in range(len(r2))))
    return out


def word(w, setname, gap=1, bolden=False, space=None):
    """Like heb.layout, but each glyph may be emboldened before the line is joined."""
    if not bolden:
        return heb.layout(w, setname, gap=gap, space=space)
    h = len(next(iter(heb.SETS[setname].values())))
    glyphs = []
    for ch in reversed(w):
        if ch == ' ':
            glyphs.append(['.' * (space if space is not None else 3)] * h)
        else:
            glyphs.append(bold(heb.glyph(setname, ch)))
    out = [''] * h
    for k, g in enumerate(glyphs):
        if k:
            out = [r + '.' * gap for r in out]
        out = [out[y] + g[y] for y in range(h)]
    return out


def ink_cols(c, x0, x1, y0, y1, pred):
    return [x for x in range(x0, x1 + 1) if any(pred(c.get(x, y)) for y in range(y0, y1 + 1))]


def clusters(cols, min_gap=5):
    out = []
    for x in cols:
        if out and x - out[-1][1] < min_gap:
            out[-1][1] = x
        else:
            out.append([x, x])
    return out


def centre_x(bm, centre):
    """Left x that puts the bitmap's ink centre on `centre` (may be .5)."""
    return int(round(centre - (heb.width(bm) - 1) / 2.0))


# ------------------------------------------------------------------ bag: HM tag on TM/HM icons
@job('graphics/bag/hm.png')
def _(p):
    # "HM": white (15) 1-px strokes, shadow 11 right/below, body rows 5-9, on index 1.
    clear_where(p, 0, 15, 3, 12, lambda v: v in (15, 11), 1)
    # Letters get the English shadow (right, below, below-right); the gershayim only a right
    # shadow, since a shadow row under its two dots reads as a cup at this size.
    x = 1
    for ch in reversed('מ”נ'):
        g = heb.glyph('C5', ch)
        draw(p, g, x, 4, 15, shadow=11, dirs=((1, 0),) if ch == '”' else DIRS_RDB)
        x += heb.width(g) + 2                  # C5 row 1 = body top -> image row 5


# ------------------------------------------------------------------ shop: MONEY label
@job('graphics/shop/money.png')
def _(p):
    # Yellow letters (rows 4-5: 14, 6-7: 12, 8: 13) on a dark plate (6) that is the 8-way outline
    # of the letters; light grey (2) anti-alias dots in some concave corners. Rebuild from scratch.
    fill_rect(p, 0, 31, 2, 11, 0)
    bm = word('כסף', 'C5')
    x = centre_x(bm, 16.5)
    grad = {4: 14, 5: 14, 6: 12, 7: 12, 8: 13, 9: 13, 3: 14}
    draw(p, bm, x, 3, lambda px, py, r: grad[py], outline=6)


# ------------------------------------------------------------------ markings menu: OK / CANCEL sprites
MARK_SPRITES = {9: 'אישור', 17: 'ביטול'}      # first tile of each 32x16 sprite (4x2 tiles, 1D)


@job('graphics/interface/mon_markings_menu.png')
def _(p):
    for first, w in MARK_SPRITES.items():
        c = Canvas(tiles_to_sprite(p, first, 4, 2))
        clear_where(c, 0, 31, 0, 15, lambda v: v in (2, 5), 1)
        bm = word(w, 'W5_8')
        # W5_8 design row 2 = body top; English body rows 3-11 -> Hebrew body rows 4-11.
        draw(c, bm, 0, 2, 2, shadow=5)
        sprite_to_tiles(p, first, 4, 2, c.rows)


# ------------------------------------------------------------------ berry tag: flavour names
FLAVOURS = ['חריף', 'יבש', 'מתוק', 'מר', 'חמוץ']    # SPICY DRY SWEET BITTER SOUR


@job('graphics/bag/check_berry.png')
def _(p):
    tiles = [list(range(39, 64))]          # one 200x8 strip, laid out on screen row 12
    c = gather_tiles(p, tiles)
    words = clusters(ink_cols(c, 0, c.width - 1, 0, 7, lambda v: v == 11))
    assert len(words) == 5, words
    clear_where(c, 0, c.width - 1, 0, 7, lambda v: v in (11, 8), 3)
    for (a, b), w in zip(words, FLAVOURS):
        bm = word(w, 'C7W')
        draw(c, bm, centre_x(bm, (a + b) / 2.0), -1, 11, shadow=8)   # body rows 0-6 like the English
    scatter_tiles(p, tiles, c)


# ------------------------------------------------------------------ healthbox: EXP label
NUN4 = ['.#.', '..#', '..#', '###']
GERSH4 = ['#.#', '#.#', '...', '...']


@job('graphics/battle_interface/hns/healthbox_singles_player.png')
def _(p):
    # "EXP": 3-row letters, row 34 colour 4, rows 35-36 colour 9, on 6, cols 18-28.
    clear_where(p, 16, 31, 34, 36, lambda v: v in (4, 9), 6)
    # Rows 34-37 (the English uses 34-36): 3 rows cannot carry a Hebrew letter. The letters are
    # the bold 4-row ones of the HP label just above (hpbar.png), so the two labels match.
    bm = bold_word('נ”נ', 4)
    draw(p, bm, centre_x(bm, 23), 34, 9)


# ------------------------------------------------------------------ battle: move info window (L / R / START)
def move_info(p, top):
    clear_where(p, 3, 28, top - 1, top + 12, lambda v: v == 5, 13)
    for k, w in enumerate(('פרטי', 'מהלך')):
        bm = word(w, 'C5')
        draw(p, bm, centre_x(bm, 15.5), top - 1 + 6 * k, 5)


@job('graphics/battle_interface/move_info_window_l.png')
def _(p):
    move_info(p, 11)


@job('graphics/battle_interface/move_info_window_r.png')
def _(p):
    move_info(p, 11)


@job('graphics/battle_interface/move_info_window_start.png')
def _(p):
    move_info(p, 13)


# ------------------------------------------------------------------ party menu: HP labels, ORDER
def party_hp(p, x0, y0):
    """x0, y0: top-left of the label interior (5 text rows), 13 columns wide."""
    clear_where(p, x0, x0 + 12, y0, y0 + 4, lambda v: v in (0x3e, 0x3f), 0x3d)
    bm = bold_word('נ”ח', 5)
    draw(p, bm, x0, y0, lambda px, py, r: 0x3e if py - y0 < 2 else 0x3f)


@job('graphics/party_menu/hns/bg.png')
def _(p):
    party_hp(p, 34, 49)
    party_hp(p, 26, 58)
    # ORDER (SEL cap is kept): colour 0x15 on 0x13, rows 66-70, cols 42-60.
    clear_where(p, 41, 61, 65, 70, lambda v: v == 0x15, 0x13)
    bm = word('סדר', 'C5')
    draw(p, bm, centre_x(bm, 51), 65, 0x15)


# ------------------------------------------------------------------ menu_info: type plates and labels
HEB_CODES = {ch: 0x3A + i for i, ch in enumerate('אבגדהוזחטיכלמנסעפצקרשת')}
HEB_CODES.update({'ך': 0x50, 'ם': 0x5E, 'ן': 0x5F, 'ף': 0x60, 'ץ': 0x61})
HEB_CODES['-'] = 0xAE
_SMALL = {}
SMALL_FONTS = {     # FONT_SMALL, and FONT_SMALL_NARROWER for a word too wide for its plate
    False: ('latin_small', 'gFontSmallLatinGlyphWidths'),
    True: ('latin_small_narrower', 'gFontSmallNarrowerLatinGlyphWidths'),
}


def small_font(narrower=False):
    if narrower not in _SMALL:
        import inspect_fonts as F
        png, table = SMALL_FONTS[narrower]
        _SMALL[narrower] = (F.FontPng.load(os.path.join(TREE, 'graphics/fonts/%s.png' % png)),
                            F.parse_width_tables(os.path.join(TREE, 'src/fonts.c'))[table])
    return _SMALL[narrower]


def small_word(w, narrower=False):
    """16-row grid of font indices (1 ink, 2 shadow) for `w` in FONT_SMALL (or FONT_SMALL_NARROWER),
    first letter at the right. The same composition graphics/types/*.png uses, so the plates match
    the summary type icons."""
    font, widths = small_font(narrower)
    glyphs = [(font.glyph(HEB_CODES[ch]), widths[HEB_CODES[ch]]) for ch in reversed(w)]
    grid = [[0] * sum(gw for _, gw in glyphs) for _ in range(16)]
    x = 0
    for g, gw in glyphs:
        for y in range(16):
            for gx in range(gw):
                if g[y][gx] in (1, 2):
                    grid[y][x + gx] = g[y][gx]
        x += gw
    cols = [i for i in range(len(grid[0])) if any(grid[y][i] for y in range(16))]
    return [r[cols[0]:cols[-1] + 1] for r in grid]


MENU_PLATES = {     # sMenuInfoIcons offsets (src/menu.c), glossary type names
    0x20: 'רגיל', 0x24: 'אש', 0x28: 'מים', 0x2C: 'עשב', 0x40: 'חשמל', 0x44: 'סלע', 0x48: 'אדמה',
    0x4C: 'קרח', 0x60: 'תעופה', 0x64: 'קרב', 0x68: 'רפאים', 0x6C: 'חרק', 0x80: 'רעל', 0x84: 'על-חושי',
    0x88: 'פלדה', 0x8C: 'אפל', 0xA0: 'דרקון', 0x04: 'פיה',
}
NARROWER_PLATES = {0x84}    # על-חושי: 36 px in FONT_SMALL runs off the 32 px plate; 31 px in FONT_SMALL_NARROWER fits
MENU_LABELS = {0xA8: 'סוג', 0xC0: 'עוצמה', 0xC8: 'דיוק', 0xE0: 'נ”כ', 0xE8: 'השפעה'}


def menu_plate(p, off, w):
    x0, y0 = (off % 16) * 8, (off // 16) * 8
    corners = [(x0, y0), (x0 + 31, y0), (x0, y0 + 11), (x0 + 31, y0 + 11)]
    assert all(p.get(x, y) == 0 for x, y in corners)
    bg = None
    for y in range(y0, y0 + 12):
        row = [p.get(x, y) for x in range(x0 + 1, x0 + 31)]
        free = [v for v in row if v not in (14, 15)]
        if free:                    # a row fully covered by text keeps the row above's colour
            bg = max(free, key=row.count)
        for x in range(x0, x0 + 32):
            if p.get(x, y) in (14, 15):
                p.put(x, y, bg)
    grid = small_word(w, off in NARROWER_PLATES)
    gw = len(grid[0])
    left = x0 + (32 - gw + 1) // 2
    for cy in range(3, 14):                  # font cell rows 3..13 -> plate rows 1..11
        for gx in range(gw):
            v = grid[cy][gx]
            if v:
                x, y = left + gx, y0 + cy - 2
                assert (x, y) not in corners and x0 <= x < x0 + 32, (w, x, y)
                p.put(x, y, 15 if v == 1 else 14)


def menu_label(p, off, w):
    x0, y0 = (off % 16) * 8, (off // 16) * 8
    fill_rect(p, x0, x0 + 41, y0, y0 + 11, 0)
    for y in range(y0 + 4, y0 + 9):
        a, b = (x0 + 1, x0 + 38) if y in (y0 + 4, y0 + 8) else (x0, x0 + 39)
        fill_rect(p, a, b, y, y, 14)
    bm = word(w, 'C7W')
    draw(p, bm, centre_x(bm, x0 + 19.5), y0 + 2, 15, outline=14,
         clip=(x0, x0 + 41, y0, y0 + 11))


@job('graphics/interface/menu_info.png')
def _(p):
    for off, w in MENU_PLATES.items():
        menu_plate(p, off, w)
    for off, w in MENU_LABELS.items():
        menu_label(p, off, w)


# ------------------------------------------------------------------ PC storage menu
@job('graphics/pokemon_storage/menu.png')
def _(p):
    # PKMN DATA header: 64x16 (tiles 1-8 over 17-24); bold letters, vertical gradient
    # (white 0x0e, peach 0x0a, orange 0x05) with an 8-way outline 0x03, on 0x02.
    tiles = [list(range(1, 9)), list(range(17, 25))]
    c = gather_tiles(p, tiles)
    fill_rect(c, 0, 63, 4, 13, 0x02)
    # FONT_SMALL letters (W5_7), body rows 5-11; emboldened 4-column letters were tried and read
    # worse (vav and final nun turn into bars).
    bm = word('נתוני פוקימון', 'W5_7')
    grad = {4: 0x0e, 5: 0x0e, 6: 0x0e, 7: 0x0e, 8: 0x0a, 9: 0x0a, 10: 0x05, 11: 0x05, 12: 0x05, 13: 0x05}
    draw(c, bm, centre_x(bm, 31.5), 3, lambda px, py, r: grad[py], outline=0x03, clip=(0, 63, 3, 14))
    scatter_tiles(p, tiles, c)

    def button(tiles, x0, x1, y0, y1, fg, sh, bg, w, top, centre):
        c = gather_tiles(p, tiles)
        clear_where(c, x0, x1, y0, y1, lambda v: v in (fg, sh) or (sh is None and v == fg), bg)
        bm = word(w, 'W4_7')
        draw(c, bm, centre_x(bm, centre), top - 2, fg, shadow=sh, clip=(x0, x1, y0, y1))
        check_inside(bm, centre_x(bm, centre), top - 2, lambda x, y: x0 <= x <= x1 and y0 <= y <= y1, w)
        scatter_tiles(p, tiles, c)

    # PARTY POKéMON tab (party panel), white 0x18 / shadow 0x17 on 0x1e, body rows 4-10
    button([[40, 41, 42, 43, 44, 45, 46, 47, 102], [56, 57, 58, 59, 60, 61, 62, 63, 103]],
           4, 67, 3, 12, 0x18, 0x17, 0x1e, 'פוקימוני הקבוצה', 4, 35.5)
    # CANCEL button in the party panel, white 0x18 / shadow 0x17 on 0x16
    button([[73, 74, 75, 105], [89, 90, 91, 106]], 1, 30, 3, 12, 0x18, 0x17, 0x16, 'ביטול', 4, 15)
    # CLOSE BOX: normal (white 0x0e, shadow 0x09) and flashing (0x09, no shadow), on 0x08
    button([[76, 77, 78, 79, 112, 113, 114, 115, 116], [92, 93, 94, 95, 128, 129, 130, 131, 132]],
           4, 67, 4, 12, 0x0e, 0x09, 0x08, 'סגור תיבה', 5, 35.5)
    button([[117, 118, 119, 120, 121, 122, 123, 124, 125], [133, 134, 135, 136, 137, 138, 139, 140, 141]],
           4, 67, 4, 12, 0x09, None, 0x08, 'סגור תיבה', 5, 35.5)


# ------------------------------------------------------------------ summary screen tab labels
# Each label is one row of 8x8 tiles (tile numbers in hns/tiles.png), used only by that label
# (checked against every summary tilemap). Text colour 0x02, shadow 0x06; the background index
# carries the palette row (0x07 orange, 0x27 yellow, 0x37 magenta). The Hebrew starts where the
# English did (x = 2), in the 6-row C6 letters so that lamed's ascender and the final letters'
# descenders fit inside the 8-pixel strip.
SUMMARY_LABELS = [
    (range(128, 136), 'פרופיל', None),        # PROFILE
    (range(144, 153), 'יכולת', None),         # ABILITY
    (range(224, 233), 'הערות מאמן', None),    # TRAINER MEMO
    (range(176, 185), 'מצב', None),           # STATE (egg page)
    (range(137, 144), 'פריט', None),          # ITEM
    (range(153, 160), 'סרטים', None),         # RIBBON
    (range(169, 173), 'נתונים', 31),          # STATS (the START cap starts at x = 33 of this strip)
    (range(185, 192), 'נסיון', None),         # EXP.
    (range(192, 200), 'מהלכים', None),        # MOVES
    (range(202, 208), 'השפעה', None),         # EFFECT
    (range(208, 218), 'תיאור', None),         # DESCRIPTION
]


@job('graphics/summary_screen/hns/tiles.png')
def _(p):
    for trange, w, xmax in SUMMARY_LABELS:
        tiles = [list(trange)]
        c = gather_tiles(p, tiles)
        x1 = (xmax if xmax is not None else c.width - 1)
        for y in range(8):
            for x in range(0, x1 + 1):
                if c.get(x, y) in (0x02, 0x06):
                    # nearest non-text pixel to the left in the same row (backgrounds are flat
                    # where the text sits; x = 0, 1 is always background)
                    xx = x
                    while c.get(xx, y) in (0x02, 0x06):
                        xx -= 1
                    c.put(x, y, c.get(xx, y))
        bm = word(w, 'C6')
        assert 2 + heb.width(bm) <= x1, (w, heb.width(bm))
        draw(c, bm, 2, 0, 0x02, shadow=0x06, clip=(0, x1, 0, 7))
        scatter_tiles(p, tiles, c)
    # small "EXP" beside the experience bar (tiles 96-97): 5-row letters, rows 1-3 0x27, 4-5 0x28
    tiles = [[96, 97]]
    c = gather_tiles(p, tiles)
    clear_where(c, 0, 13, 0, 7, lambda v: v in (0x27, 0x28), 0x2f)
    bm = word('נ”נ', 'C5')
    draw(c, bm, 2, 0, lambda px, py, r: 0x27 if py <= 3 else 0x28)
    scatter_tiles(p, tiles, c)


# ------------------------------------------------------------------ main
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--only', default='')
    ap.add_argument('--dry', action='store_true')
    ap.add_argument('--out', default=TREE, help='tree to write into (default HNS_TREE)')
    a = ap.parse_args()
    for path, fn in JOBS:
        if a.only not in path:
            continue
        p = load(path, BASE_REF)
        fn(p)
        if not a.dry:
            p.save(gpaths.write_target(path, a.out))
        print('done', path)
    if WARN:
        print('%d warnings' % len(WARN))


if __name__ == '__main__':
    main()
