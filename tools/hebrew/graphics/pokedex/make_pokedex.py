#!/usr/bin/env python3
"""Hebrew versions of the HGSS-style Pokédex graphics (graphics/pokedex/hgss/*.png).

Every file is rebuilt from its English original (the 2.0.6 release, gpaths.EN_REF), so the
script is idempotent. Without --write it only builds, verifies and renders previews into
$HNS_WORK/graphics/pokedex/; with --write it also writes the PNGs (and the two start-menu
tilemaps, see job_menu_list) into HNS_TREE.

    python3 make_pokedex.py [--write] [job ...]
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from dexlib import *  # noqa: F401,F403
import dexlib as D

WRITE = '--write' in sys.argv
ONLY = [a for a in sys.argv[1:] if not a.startswith('--')]
PREV = D.OUT                              # previews go straight into the group folder
TMP = os.path.join(D.OUT, 'tmp')          # files as they would be written (dry run)
os.makedirs(TMP, exist_ok=True)

RESULTS = []          # (file, problems)
SHEET = []            # (title, image) for the contact sheet


def pal(name):
    return D.read_jasc(os.path.join(D.REPO, D.HG + name))


def save_png(rel, ts, ref):
    dst = D.gpaths.write_target(rel) if WRITE else os.path.join(D.REPO, rel)
    tmp = os.path.join(TMP, os.path.basename(rel))
    ts.save(tmp)
    probs = D.check_png(tmp, ref)
    targets = [tmp]
    if WRITE and not probs:
        ts.save(dst)
        probs = D.check_png(dst, ref)
        targets.append(dst)
    for t in targets:                       # what is on disk is exactly what was verified
        back = D.F.FontPng.load(t)
        if list(back.pixels) != list(ts.pixels):
            probs.append('re-read pixels differ: ' + t)
    # raw tileset pair (English | Hebrew), 4x, in the PNG's own palette
    D.pair(D.png_rgb(ref), D.png_rgb(D.F.FontPng.load(tmp)), 4,
           title=rel + ' (raw PNG, own palette)').save(
        os.path.join(PREV, os.path.basename(rel).replace('.png', '_raw_pair.png')))
    RESULTS.append((rel, probs))
    return probs


def save_tilemap(rel, canvas, orig_entries):
    if canvas.entries == list(orig_entries):
        return False
    data = D.pack_tilemap(canvas.entries)
    probs = []
    if len(data) != len(D.english_bytes(rel)):
        probs.append('size changed')
    open(os.path.join(TMP, os.path.basename(rel)), 'wb').write(data)
    if WRITE and not probs:
        open(D.gpaths.write_target(rel), 'wb').write(data)
    n = sum(1 for a, b in zip(canvas.entries, orig_entries) if a != b)
    RESULTS.append((rel, probs or ['(%d entries repointed)' % n]))
    return True


def bg_canvases(ts, names):
    out = []
    for n in names:
        out.append(D.BgCanvas(n, ts, D.tilemap(D.english_bytes(D.HG + n))))
    return out


def finish(rel, ts_new, ref, canvases, free=(), allow_alloc=(), protect=(0,)):
    log = D.write_back(ts_new, canvases, free, allow_alloc, protect)
    bad = D.verify(canvases, ts_new)
    if bad:
        raise RuntimeError('%s: verify failed at %s' % (rel, bad[:10]))
    probs = save_png(rel, ts_new, ref)
    return log, probs


# =====================================================================================
# Page tabs: tileset_menu1/2/3.png
# =====================================================================================
#
# The tab bar is the top 16 px of each info-page tilemap. English labels are 2-px bold letters
# with a 1-px outline: inactive fill 6 / outline 9, active fill 1 / outline 15, on bar index 7.
# Hebrew: FONT_NARROW glyphs (1-px strokes, 8 rows tall like the English); bold 2-px Hebrew does
# not fit (EVO/CRY/SIZE would need 91 px of the 85 available). Each label must stay inside the screen columns whose tiles are private to
# the screens that show it in that state (see notes): INFO x16-47, AREA x56-87, STATS x88-127,
# EVO/CRY/SIZE x136-222 with CRY and SIZE inside x160-222.

TABS = {'INFO': 'מידע', 'AREA': 'אזור', 'STATS': 'נתונים', 'EVO': 'התפתחות', 'CRY': 'קול', 'SIZE': 'גודל'}
TAB_FONT = 'narrow'
TAB_TOP = -1               # font cell row 4 (top of a letter body) -> bar row 3, as the English
TAB_CLEAR = [(16, 47), (56, 127), (136, 222)]
TAB_BOXES = {'INFO': (16, 47), 'AREA': (56, 87), 'STATS': (88, 127)}
# Inactive: pink ink with a dark-red drop shadow (an outline around 1-px strokes reads darker and
# thinner than the English 2-px pink letters). Active: white with a black outline, as English.
TAB_STYLE = {False: ('shadow', 6, 9), True: ('outline', 1, 15, (1, 12))}
TAB_SCREENS = {
    'tileset_menu1.png': [('tilemap_info_screen.bin', 'INFO'), ('tilemap_stats_screen.bin', 'STATS'),
                          ('SelectBar.bin', 'AREA')],
    'tileset_menu2.png': [('tilemap_evo_screen_PE.bin', 'EVO'), ('tilemap_forms_screen.bin', 'EVO')],
    'tileset_menu3.png': [('tilemap_cry_screen.bin', 'CRY'), ('tilemap_size_screen.bin', 'SIZE')],
}


def tab_layout():
    """Screen x of each label's visible (outlined) extent."""
    pos = {}
    for k, (x0, x1) in TAB_BOXES.items():
        bm = D.word(TAB_FONT, TABS[k])
        a, b = D.ink_x(bm)
        w = b - a + 3
        left = x0 + (x1 - x0 + 1 - w) // 2
        pos[k] = (left, left + w - 1)
    # EVO / CRY / SIZE: spread evenly over 136..222
    names = ['EVO', 'CRY', 'SIZE']
    ws = []
    for k in names:
        a, b = D.ink_x(D.word(TAB_FONT, TABS[k]))
        ws.append(b - a + 3)
    # Like the English: EVO starts right after the separator tile (x136), SIZE ends 3 px
    # before the arrow (x220); the two gaps share what is left.
    x0, x1 = 136, 220
    free = (x1 - x0 + 1) - sum(ws)
    gap = free // 2
    x = x0
    for k, w in zip(names, ws):
        pos[k] = (x, x + w - 1)
        x += w + gap
    assert pos['CRY'][0] >= 160 and pos['SIZE'][1] <= 220 and pos['EVO'][1] < pos['CRY'][0]
    return pos


def job_tabs():
    pos = tab_layout()
    for tsn, screens in TAB_SCREENS.items():
        rel = D.HG + tsn
        ref = D.english_png(rel)
        ts = D.english_png(rel)
        cans = bg_canvases(ts, [s for s, _ in screens])
        for c, (_, active) in zip(cans, screens):
            for x0, x1 in TAB_CLEAR:
                D.fill(c, x0, 1, x1, 12, 7)
            for k, (l, r) in pos.items():
                # same ink position in both states, so a label does not move when it is selected
                bm = D.word(TAB_FONT, TABS[k])
                D.draw(c, bm, l + 1 - D.ink_x(bm)[0], TAB_TOP, TAB_STYLE[k == active])
        finish(rel, ts, ref, cans)
        # previews: the tab bar of every screen, English | Hebrew, and the whole screens
        p = pal('palette_default.pal')
        old = bg_canvases(ref, [s for s, _ in screens])
        a = D.stack([D.rgb_bg(o, p).crop((0, 0, 240, 16)) for o in old], gap=2)
        b = D.stack([D.rgb_bg(c, p, ts).crop((0, 0, 240, 16)) for c in cans], gap=2)
        im = D.pair(a, b, 4, title=tsn + ': tab bar of ' + ', '.join(s for s, _ in screens))
        im.save(os.path.join(PREV, tsn.replace('.png', '_pair.png')))
        full = D.pair(D.stack([D.rgb_bg(o, p).crop((0, 0, 240, 160)) for o in old], gap=4),
                      D.stack([D.rgb_bg(c, p, ts).crop((0, 0, 240, 160)) for c in cans], gap=4), 2,
                      title=tsn + ' screens (2x)')
        full.save(os.path.join(PREV, tsn.replace('.png', '_screens.png')))
        SHEET.append((tsn, D.pair(a, b, 2)))


JOBS = {'tabs': job_tabs}


# =====================================================================================
# Interface sprites: tileset_interface_hns.png (1D sprite sheet, 32 px wide)
# =====================================================================================
#
# Frames (sprite tile numbers, src/pokedex_plus_hgss.c sSpriteAnim_*): SELECT cap 32, SEARCH 40,
# START cap 48, MENU 56 (32x16 each; the four are never created by the HGSS list code, see notes),
# SEEN 64 and OWN 96 (64x32), JOHTO 160 and NATIONAL 168 (32x16, with an underline).
# Text colours: SEEN/OWN/JOHTO/NATIONAL ink 15, shadow 4 on transparent 0 (FONT_SMALL style);
# SEARCH/MENU ink 1 (white), shadow 15.

IFACE = 'tileset_interface_hns.png'
IFACE_FONT = 'small_narrower'   # 4-px letters like the English SEEN/OWN; keeps OWN clear of the red rule
IFACE_NEW = {}


def job_interface():
    rel = D.HG + IFACE
    ref = D.english_png(rel)
    ts = D.english_png(rel)
    S = lambda name, t0, w, h: D.SpriteCanvas(name, ts, t0, w, h)
    seen, own = S('seen', 64, 64, 32), S('own', 96, 64, 32)
    johto, national = S('johto', 160, 32, 16), S('national', 168, 32, 16)
    search, menu = S('search', 40, 32, 16), S('menu', 56, 32, 16)
    # SEEN / OWN: label right-aligned to the English right edge (x 39 incl. shadow), so the gap to
    # the digit sprites (x >= 43) stays as in English; letter body on rows 6-12 as in English.
    for c, text in ((seen, 'נראו'), (own, 'נתפסו')):
        D.fill(c, 0, 0, 63, 31, 0)
        D.place(c, text, IFACE_FONT, ('shadow', 15, 4), 0, 39, 2, align='right')
    # JOHTO / NATIONAL headings: text rows 0-11 redrawn, underline rows 12-13 kept. Right edge at
    # x 23 = screen 211, the same column as the SEEN/OWN labels' right edge.
    for c, text in ((johto, "ג'וטו"), (national, 'לאומי')):
        D.fill(c, 0, 0, 31, 11, 0)
        D.place(c, text, IFACE_FONT, ('shadow', 15, 4), 0, 23, 0, align='right')
    # SEARCH / MENU (unused frames; drawn for consistency with the BG labels)
    for c, text in ((search, 'חיפוש'), (menu, 'תפריט')):
        D.fill(c, 0, 0, 31, 15, 0)
        D.place(c, text, 'narrow', ('shadow', 1, 15), 0, 31, -1, align='center')
    cans = [seen, own, johto, national, search, menu]
    finish(rel, ts, ref, cans)
    IFACE_NEW['ts'] = ts
    p = pal('palette_default.pal')
    rows = []
    for c in cans:
        a = D.rgb_grid(c.orig, p)
        b = D.rgb_grid(c.want, p)
        rows.append(D.pair(a, b, 4, title='frame %s' % c.name))
    D.stack(rows, gap=6).save(os.path.join(PREV, IFACE.replace('.png', '_pair.png')))
    SHEET.append((IFACE, D.pair(D.stack([D.rgb_grid(c.orig, p) for c in cans], gap=2),
                                D.stack([D.rgb_grid(c.want, p) for c in cans], gap=2), 2)))


JOBS['interface'] = job_interface

# =====================================================================================
# List screen and START menu: tileset_menu_list.png (+ the two start-menu tilemaps)
# =====================================================================================
#
# List screen (BG1 tilemap_list_screen.bin): MENU / SEARCH under the START / SELECT button caps,
# ink 15 shadow 4 on white 1, with the grey rule (index 4) on row 152 running through the text.
# START menu (BG0 tilemap_start_menu.bin, tilemap_start_menu_search_results.bin): one item per
# 16-px row inside a white box (x134-245), ink 15 shadow 3 on 1. The POKéDEX logo and the
# START / SELECT caps are kept.

MENU_ITEMS = {
    'tilemap_start_menu.bin': ['חזרה לרשימה', 'ראש הרשימה', 'סוף הרשימה', 'סגירת הפוקדקס'],
    'tilemap_start_menu_search_results.bin': ['חזרה לרשימה', 'ראש הרשימה', 'סוף הרשימה',
                                              'חזרה לפוקדקס', 'סגירת הפוקדקס'],
}
MENU_FONT = 'narrower'     # 4-px letters, like the English menu font
LIST_FONT = 'narrow'
MENU_ALIGN = os.environ.get('MENU_ALIGN', 'left')
MENU_X = (144, 223)        # English text starts at x144; the box interior is x134-233
LIST_LABELS = [('תפריט', 115, 140), ('חיפוש', 150, 181)]   # under START (x116-139), SELECT (x152-175)
LIST_FREE_TILES = [119] + list(range(196, 208))     # referenced by no tilemap


def job_menu_list():
    rel = D.HG + 'tileset_menu_list.png'
    ref = D.english_png(rel)
    ts = D.english_png(rel)
    names = ['tilemap_list_screen.bin', 'tilemap_list_screen_underlay.bin',
             'tilemap_start_menu.bin', 'tilemap_start_menu_search_results.bin']
    cans = bg_canvases(ts, names)
    orig_entries = {c.name: list(c.entries) for c in cans}
    lst = cans[0]
    # --- list screen labels
    D.fill(lst, 112, 150, 181, 159, lambda x, y: 4 if y == 152 else 1)
    for text, x0, x1 in LIST_LABELS:
        mid = (x0 + x1) // 2
        bm = D.word(LIST_FONT, text)
        half = bm.w // 2
        D.place(lst, text, LIST_FONT, ('shadow', 15, 4), mid - half - 2, mid - half + bm.w + 1, 147)
    # --- start menus
    for c in cans[2:]:
        for k, text in enumerate(MENU_ITEMS[c.name]):
            y0 = 8 + 16 * k
            D.recolor(c, 136, y0, 231, y0 + 15, {15: 1, 3: 1, 5: 1})   # 5: a few shadow pixels
            # font cell row 4 -> y0+3 (English ink rows y0+3 .. y0+11, shadow y0+12); the narrow
            # glyphs are 8 rows, aligned to the English baseline
            D.place(c, text, MENU_FONT, ('shadow', 15, 3), MENU_X[0], MENU_X[1], y0, align=MENU_ALIGN)
    log, probs = finish(rel, ts, ref, cans, free=LIST_FREE_TILES,
                        allow_alloc=('tilemap_start_menu.bin', 'tilemap_start_menu_search_results.bin'))
    for t, nt, users in log:
        print('  tile %d split: %d <- %s' % (t, nt, users))
    for c in cans:
        save_tilemap(D.HG + c.name, c, orig_entries[c.name])
    # --- previews
    p = pal('palette_default.pal')
    pr = pal('palette_search_results.pal')
    old = bg_canvases(ref, names)
    IFACE_OLD = D.english_png(D.HG + IFACE)
    def list_screen(cs, t, iface):
        base = D.rgb_bg(cs[1], p, t)
        im = D.rgb_bg(cs[0], p, t, base=base)
        if iface is not None:
            im = draw_list_sprites(im, iface, p)
        return im.crop((0, 0, 240, 160))
    a = list_screen(old, ref, IFACE_OLD)
    b = list_screen(cans, ts, IFACE_NEW.get('ts'))
    D.pair(a, b, 4, title='list screen (BG + interface sprites)').save(os.path.join(PREV, 'tileset_menu_list_pair.png'))
    sm = []
    for i, pp in ((2, p), (3, pr)):
        sm.append(D.pair(D.rgb_bg(old[i], pp, ref).crop((120, 0, 256, 96)),
                         D.rgb_bg(cans[i], pp, ts).crop((120, 0, 256, 96)), 4, title=names[i]))
    D.stack(sm).save(os.path.join(PREV, 'tileset_menu_list_startmenu_pair.png'))
    SHEET.append(('list screen', D.pair(a, b, 2)))
    SHEET.append(('start menus', D.pair(D.stack([D.rgb_bg(old[i], pp, ref).crop((120, 0, 256, 96)) for i, pp in ((2, p), (3, pr))], gap=2),
                                        D.stack([D.rgb_bg(cans[i], pp, ts).crop((120, 0, 256, 96)) for i, pp in ((2, p), (3, pr))], gap=2), 2)))


def draw_list_sprites(im, iface, p):
    """Interface sprites as CreateInterfaceSprites places them on the main list page (national
    dex enabled): JOHTO/NATIONAL headings, SEEN/OWN labels and sample counts."""
    def spr(t0, w, h, cx, cy):
        c = D.SpriteCanvas('s', iface, t0, w, h)
        return D.rgb_grid(c.orig, p, base=im, at=(cx - w // 2, cy - h // 2))
    X, YO = 204, 13
    im = spr(160, 32, 16, X, 40 - YO - 6)
    im = spr(64, 64, 32, X, 45 - YO + 6)
    im = spr(96, 64, 32, X, 55 - YO + 7)
    im = spr(168, 32, 16, X, 73 - YO - 6)
    im = spr(64, 64, 32, X, 78 - YO + 6)
    im = spr(96, 64, 32, X, 88 - YO + 6)
    x1 = X + 15 + 14
    for y, num in ((45, 123), (55, 45), (78, 456), (88, 78)):
        digits = str(num)
        for k, ch in enumerate(reversed(digits)):
            im = spr(176 + 2 * int(ch), 8, 16, x1 - 7 * k, y - YO)
    return im


JOBS['menu_list'] = job_menu_list


# =====================================================================================
# Search screen: tileset_menu_search.png
# =====================================================================================
#
# FONT_SMALL-style lettering in pills: top bar ink 3 / shadow 9 on green 8; left column ink 3 /
# shadow 11 on orange 10; OK pill ink 3 / shadow 9 on green 8. Highlighting is a palette swap
# (SetSearchRectHighlight), so each label exists once. The big MODE/ORDER/NAME/... buttons and
# the black POKéDEX title in the upper part of the PNG are referenced by no tilemap and by no
# code (only tiles 2, 10, 11, 13 are written by DrawOrEraseSearchParameterBox), so they stay.

SEARCH_FONT = 'small'
TOP = [('חיפוש', 4), ('החלפה', 52), ('ביטול', 100)]          # SEARCH, SHIFT, CANCEL (pill x0)
LEFT = {'tilemap_search_screen_national.bin': ['שם', 'צבע', 'סוג', 'סדר', 'מצב', 'אישור'],
        'tilemap_search_screen_hoenn.bin': ['שם', 'צבע', 'סוג', 'סדר', 'אישור']}
LEFT_EN = {'tilemap_search_screen_national.bin': ['NAME', 'COLOR', 'TYPE', 'ORDER', 'MODE', 'OK'],
           'tilemap_search_screen_hoenn.bin': ['NAME', 'COLOR', 'TYPE', 'ORDER', 'OK']}
SEARCH_PROTECT = (0, 2, 10, 11, 13)


def job_search():
    rel = D.HG + 'tileset_menu_search.png'
    ref = D.english_png(rel)
    ts = D.english_png(rel)
    names = ['tilemap_search_screen_national.bin', 'tilemap_search_screen_hoenn.bin']
    cans = bg_canvases(ts, names)
    for c in cans:
        for text, x0 in TOP:
            D.recolor(c, x0, 2, x0 + 31, 12, {3: 8, 9: 8})
            D.place(c, text, SEARCH_FONT, ('shadow', 3, 9), x0 + 1, x0 + 30, 0)
        for k, (text, en) in enumerate(zip(LEFT[c.name], LEFT_EN[c.name])):
            top = 16 + 16 * k
            if en == 'OK':
                bgc, sh = 8, 9
            else:
                bgc, sh = 10, 11
            D.recolor(c, 4, top + 3, 35, top + 12, {3: bgc, sh: bgc})
            D.place(c, text, SEARCH_FONT, ('shadow', 3, sh), 5, 34, top)
    finish(rel, ts, ref, cans, protect=SEARCH_PROTECT)
    p = pal('palette_search_menu.pal')
    old = bg_canvases(ref, names)
    a = D.stack([D.rgb_bg(o, p, ref).crop((0, 0, 136, 112)) for o in old], gap=4)
    b = D.stack([D.rgb_bg(c, p, ts).crop((0, 0, 136, 112)) for c in cans], gap=4)
    D.pair(a, b, 4, title='search screen (national, hoenn), labels area').save(os.path.join(PREV, 'tileset_menu_search_pair.png'))
    D.pair(D.stack([D.rgb_bg(o, p, ref).crop((0, 0, 240, 160)) for o in old], gap=4),
           D.stack([D.rgb_bg(c, p, ts).crop((0, 0, 240, 160)) for c in cans], gap=4), 2,
           title='search screens (2x)').save(os.path.join(PREV, 'tileset_menu_search_screens.png'))
    SHEET.append(('search screen', D.pair(a, b, 2)))


JOBS['search'] = job_search


# =====================================================================================
# Stat bars: stat_bars.png -- SUPERSEDED, do not write
# =====================================================================================
#
# The tree's stat_bars.png no longer comes from this job. It holds the stats page's Hebrew
# abbreviations (נ”ח, הת', הגנ', ת”מ, הג”מ, מהי', FONT_SMALL_NARROWER) right-aligned at x30-48,
# and under TEXT_RTL CreateStatBar draws the bars leftwards from x29 (x 30-w .. 29, the mirror of
# the old x19 .. 18+w about the box). That file was made by hand: the earlier label column x0-18
# shifted right by 30 px, x0-29 cleared to index 0. The job below still renders the old English
# x0-9 layout and its two-letter candidate for reference only; --stat-bars-hebrew no longer writes.
#
# A 64x64 4bpp sprite; labels sit in x0-9 of six 10-row bands, ink 14 / shadow 15, because
# CreateStatBar draws the bars from x 10 (STAT_BAR_X_OFFSET) on band rows 3-7. Ten pixels hold
# two 4-px FONT_SMALL_NARROWER letters and no gershayim, so נ”ח cannot be written and the special
# stats have no readable two-letter form.

STAT_CANDIDATE = ['נח', 'הת', 'הג', 'תמ', 'גמ', 'מה']      # HP AT DE SA SD SP


def job_stat_bars():
    rel = D.HG + 'stat_bars.png'
    ref = D.english_png(rel)
    ts = D.english_png(rel)
    c = D.SpriteCanvas('stat_bars', ts, 0, 64, 64)
    for i, text in enumerate(STAT_CANDIDATE):
        D.fill(c, 0, 10 * i, 9, 10 * i + 9, 0)
        D.place(c, text, 'small_narrower', ('shadow', 14, 15), 0, 9, 10 * i - 2, align='right')
    # preview with sample bars drawn the way CreateStatBar does
    def with_bars(grid):
        g = [row[:] for row in grid]
        for i, w in enumerate((30, 25, 20, 35, 15, 28)):
            y = 10 * i + 3
            for x in range(w):
                for yy in range(5):
                    g[y + yy][10 + x] = 1 if yy in (0, 4) or x in (0, w - 1) else 2
        return g
    p = [(232, 232, 232), (255, 255, 255), (16, 200, 200)] + [(255, 0, 255)] * 11 + [(0, 0, 0), (173, 173, 173)]
    D.pair(D.rgb_grid(with_bars(c.orig), p), D.rgb_grid(with_bars(c.want), p), 4,
           labels=('English (kept)', 'Hebrew candidate, NOT applied'),
           title='stat_bars.png with sample bars').save(os.path.join(PREV, 'stat_bars_candidate_pair.png'))
    # Superseded (see above): writing would replace the tree's labels and break the RTL bar layout.
    RESULTS.append((rel, ['superseded: candidate rendered only, never written']))


JOBS['stat_bars'] = job_stat_bars


if __name__ == '__main__':
    for name, fn in JOBS.items():
        if not ONLY or name in ONLY:
            fn()
    if SHEET and not ONLY:
        D.stack([im for _, im in SHEET], gap=12, titles=[t for t, _ in SHEET]).save(
            os.path.join(PREV, 'contact_sheet.png'))
    for rel, probs in RESULTS:
        print('%-60s %s' % (rel, 'OK' if not probs else probs))
    print('written' if WRITE else 'dry run (previews only)')
