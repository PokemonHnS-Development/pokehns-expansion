#!/usr/bin/env python3
"""Draw Hebrew into the Pokegear (graphics/pokenav) PNGs of HNS_TREE.

Idempotent: every run starts from the English file of the 2.0.6 release, erases the English lettering
(only the label's own palette indices inside the label's box), draws the Hebrew with the
label's own indices, writes the PNG back through inspect_fonts.FontPng (same IHDR, PLTE, tRNS),
verifies size/depth/palette, and renders English | Hebrew previews into
$HNS_WORK/graphics/pokegear.

    python3 heb_pokegear.py            # all files
    python3 heb_pokegear.py options    # only jobs whose path contains 'options'
"""
import os
import struct
import subprocess
import sys
import tempfile
from collections import Counter

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.dirname(HERE))
import gpaths                                 # noqa: E402
import pgfx                                   # noqa: E402
import hebfont as H                           # noqa: E402
from PIL import Image, ImageDraw              # noqa: E402

REPO = gpaths.TREE
OUT = gpaths.out('pokegear')
# The two Spanish forks whose redrawn condition graph shows what lies under the English labels:
# es/master and sigon as fetched on 2026-10-05. Only condition/graph.png needs them.
FORK_REFS = {'es/master': '268113861f', 'sigon': '098f8e4906'}


# ----------------------------------------------------------------------------- canvases

class SpriteCanvas:
    """Sprite frames of sw x sh cut row-major from the PNG and shown left to right."""

    def __init__(self, f, sw, sh, nframes=None):
        self.f, self.sw, self.sh = f, sw, sh
        fr = pgfx.strips(f, sw, sh)
        self.frames = fr[:nframes] if nframes else fr
        self.width, self.height = sw * len(self.frames), sh

    def _xy(self, X, Y):
        if not (0 <= X < self.width and 0 <= Y < self.height):
            return None
        x0, y0 = self.frames[X // self.sw]
        return x0 + X % self.sw, y0 + Y

    def get(self, X, Y):
        p = self._xy(X, Y)
        return None if p is None else self.f.get(*p)

    def put(self, X, Y, v):
        p = self._xy(X, Y)
        if p is None:
            raise ValueError('pixel (%d,%d) outside canvas' % (X, Y))
        self.f.put(p[0], p[1], v)


class PlainCanvas:
    def __init__(self, f):
        self.f, self.width, self.height = f, f.width, f.height

    def get(self, X, Y):
        if 0 <= X < self.width and 0 <= Y < self.height:
            return self.f.get(X, Y)
        return None

    def put(self, X, Y, v):
        self.f.put(X, Y, v)


class TilemapCanvas:
    """Screen pixels of a BG tilemap region; each (col,row) must map to a tile used nowhere else."""

    def __init__(self, f, ents, map_w, c0, r0, cols, rows):
        self.f, self.ents, self.map_w = f, ents, map_w
        self.c0, self.r0 = c0, r0
        self.width, self.height = cols * 8, rows * 8
        self.ntx = f.width // 8

    def _xy(self, X, Y):
        if not (0 <= X < self.width and 0 <= Y < self.height):
            return None
        e = self.ents[(self.r0 + Y // 8) * self.map_w + self.c0 + X // 8]
        if e & 0xC00:
            raise ValueError('flipped tile in text area')
        t = e & 0x3FF
        return (t % self.ntx) * 8 + X % 8, (t // self.ntx) * 8 + Y % 8

    def get(self, X, Y):
        p = self._xy(X, Y)
        return None if p is None else self.f.get(*p)

    def put(self, X, Y, v):
        p = self._xy(X, Y)
        self.f.put(p[0], p[1], v)


class RibbonCanvas:
    """city_zoom_text: 64 sprite tiles read in order as one 8-px-high ribbon (tile t at
    ((t % 8) * 8, (t // 8) * 8) in the PNG). The legend shows it through a 12-tile window."""

    def __init__(self, f):
        self.f, self.width, self.height = f, 64 * 8, 8

    def _xy(self, X, Y):
        if not (0 <= X < self.width and 0 <= Y < self.height):
            return None
        t = X // 8
        return (t % 8) * 8 + X % 8, (t // 8) * 8 + Y

    def get(self, X, Y):
        p = self._xy(X, Y)
        return None if p is None else self.f.get(*p)

    def put(self, X, Y, v):
        p = self._xy(X, Y)
        if p is None:
            raise ValueError('pixel (%d,%d) outside ribbon' % (X, Y))
        self.f.put(p[0], p[1], v)


def read_map(path):
    data = open(path, 'rb').read()
    return list(struct.unpack('<%dH' % (len(data) // 2), data))


# ----------------------------------------------------------------------------- erase / draw

def erase(cv, box, text_idx, keep=None):
    """Inside box (x0,y0,x1,y1 inclusive) replace pixels whose index is in text_idx with that row's
    most common other index (the background, or a border row's own colour)."""
    x0, y0, x1, y1 = box
    for y in range(y0, y1 + 1):
        others = Counter(cv.get(x, y) for x in range(x0, x1 + 1)
                         if cv.get(x, y) not in text_idx and (keep is None or (x, y) not in keep))
        if not others:
            raise ValueError('row %d of %s is all text' % (y, box))
        bg = others.most_common(1)[0][0]
        for x in range(x0, x1 + 1):
            if cv.get(x, y) in text_idx and (keep is None or (x, y) not in keep):
                cv.put(x, y, bg)


def place(text, font, baseline, x_left=None, x_center=None, x_right=None, space=4, gap=1):
    """Absolute ink pixels for `text` (set right to left) at the given horizontal anchor."""
    ink, w = H.layout(text, font, space=space, gap=gap)
    if x_left is not None:
        dx = x_left
    elif x_right is not None:
        dx = x_right - w + 1
    else:
        dx = int(round(x_center - (w - 1) / 2.0))
    return {(x + dx, y + baseline) for (x, y) in ink}


def paint(cv, pixels, idx, only_over=None):
    for (x, y) in pixels:
        if only_over is not None and cv.get(x, y) not in only_over:
            continue
        cv.put(x, y, idx)


def draw_shadowed(cv, ink, fg, shadow, bg_ok):
    """Pokegear alphabet: ink in fg, 1-px drop shadow (right, down, diagonal) over background only."""
    for p in ink:
        if cv.get(*p) is None:
            raise ValueError('ink outside canvas at %s' % (p,))
    paint(cv, ink, fg)
    paint(cv, H.drop_shadow(ink), shadow, only_over=bg_ok)


def check_inside(ink, box):
    x0, y0, x1, y1 = box
    bad = [p for p in ink if not (x0 <= p[0] <= x1 and y0 <= p[1] <= y1)]
    if bad:
        raise ValueError('text leaves its box %s: %s' % (box, sorted(bad)[:6]))


# ----------------------------------------------------------------------------- terms

T = {
    'MAP': 'מפה',
    'CALL': 'טלפון',
    'RADIO': 'רדיו',
    'CONDITION': 'כושר',
    'RIBBONS': 'סרטים',
    'SWITCH OFF': 'כיבוי',
    'PARTY PKMN': 'הצוות',
    'SEARCH': 'חיפוש',
    'CANCEL': 'ביטול',
    'MAIN MENU': 'תפריט ראשי',
    'COOL': 'מגניבות',
    'BEAUTY': 'יופי',
    'CUTE': 'חמידות',
    'SMART': 'חוכמה',
    'TOUGH': 'קשיחות',
    'TUNING': 'כוונון',
    'POKéMON GEAR': 'פוקיגיר',
    'POKéMON CENTER': 'מרכז פוקימון',
    'POKé MART': 'חנות פוקימון',
    'POKéMON GYM': 'מכון פוקימון',
    'BATTLE TENT': 'אוהל קרב',
    'POKéMON CONTEST': 'תחרות פוקימון',
    'CANCEL (condition plate)': 'חזרה',
}


# ----------------------------------------------------------------------------- jobs

def job_option(f, english, has_icon):
    """Menu buttons: four 32x16 sprite frames side by side (128x16). Interior rows 2-13."""
    cv = SpriteCanvas(f, 32, 16)
    x_text = 15 if has_icon else 4
    erase(cv, (x_text, 0, 127, 15), {1, 2})
    bg = Counter(cv.get(x, 8) for x in range(x_text, 128)).most_common(1)[0][0]
    ink = place(T[english], H.GEAR, baseline=10, x_left=16 if has_icon else 8)
    check_inside(ink, (x_text, 2, 115, 12))   # x<=115: stays on screen when the button is not selected
    draw_shadowed(cv, ink, 1, 2, bg_ok={bg})
    return cv


def job_main_header(f, english):
    """Main left header: two 64x32 frames side by side; bar interior x 0-85, rows 2-21."""
    cv = SpriteCanvas(f, 64, 32)
    erase(cv, (0, 2, 85, 21), {1, 2})
    ink = place(T[english], H.GEAR, baseline=14, x_center=42.5)
    check_inside(ink, (2, 3, 83, 19))
    draw_shadowed(cv, ink, 1, 2, bg_ok={cv.get(40, 4)})
    return cv


def job_sub_header(f, english):
    """Submenu left header: only frames 0-1 (32x16 each) are shown; bar interior x 0-61, rows 2-13."""
    cv = SpriteCanvas(f, 32, 16, nframes=2)
    erase(cv, (0, 0, 61, 15), {1, 2})     # rows 14-15 too: the PKMN ligature runs into the border
    ink = place(T[english], H.GEAR, baseline=10, x_center=31)
    check_inside(ink, (1, 2, 60, 12))
    draw_shadowed(cv, ink, 1, 2, bg_ok={cv.get(30, 3)})
    return cv


def job_graph(f):
    """Condition graph labels: dark strokes (1), light halo (4), pale corners (f) on the panel."""
    cv = PlainCanvas(f)
    labels = [
        # english, erase box, anchor, baseline, which side the colour disc is on
        ('COOL', (55, 1, 82, 9), dict(x_center=68), 8),
        ('TOUGH', (13, 24, 46, 32), dict(x_right=44), 29),
        ('BEAUTY', (89, 24, 122, 32), dict(x_left=91), 31),
        ('SMART', (19, 84, 53, 92), dict(x_center=36), 91),
        ('CUTE', (83, 84, 109, 92), dict(x_center=96), 91),
    ]
    for eng, box, anchor, base in labels:
        x0, y0, x1, y1 = box
        restore_label_background(cv, box)
        ink = place(T[eng], H.GEAR, baseline=base, **anchor)
        near, corner = H.halo(ink)
        for p in ink | near | corner:
            if cv.get(*p) is None:
                raise ValueError('%s label leaves the graph' % eng)
        paint(cv, corner, 0xF, only_over={3, 6, 7, 8, 9, 0xA, 0xB, 0xC, 0xD, 0xE})
        paint(cv, near, 4)
        paint(cv, ink, 1)
    return cv


def job_condition_cancel(f):
    """Condition screen CANCEL plate (32x16 sprite): black 2-3 px letters (f) on the plate (2),
    5 rows (5-9) between the plate's bars, x 4-22. Hebrew in the 3x5 MICRO letters."""
    cv = PlainCanvas(f)
    erase(cv, (4, 5, 22, 9), {0xF})
    ink = place(T['CANCEL (condition plate)'], H.MICRO, baseline=9, x_center=13)
    check_inside(ink, (4, 5, 22, 9))
    paint(cv, ink, 0xF)
    return cv


RADIO_MAP = 'graphics/pokenav/hns/radio/ui_map.bin'


def job_radio(f):
    """Radio screen (BG tilemap ui_map.bin, 32 wide). Two labels:
    - "RADIO" title beside the radio icon: embossed 1-px strokes (3) with a drop shadow (6) on the
      panel (4), 9-row body at screen y 25-33, x 53-84; map cols 6-10 rows 3-4 (tiles 0x18-0x1f,
      0x23-0x2a, each used once). The panel's right border (x 86-87) also uses 3/6: not touched.
    - "TUNING" on the dial button: black (6) on light grey (a), rows 1-6 of map row 5, between the
      orange arrows; tiles 0x2f-0x34 (cols 20-25, each used once)."""
    ents = read_map(os.path.join(REPO, RADIO_MAP))
    # RADIO: canvas = screen x 48-87, y 24-39
    cv = TilemapCanvas(f, ents, 32, 6, 3, 5, 2)
    box = (1, 1, 37, 10)                     # screen x 49-85, y 25-34
    eng = [(x, y) for y in range(box[1], box[3] + 1) for x in range(box[0], box[2] + 1)
           if cv.get(x, y) == 3]
    cx = (min(x for x, _ in eng) + max(x for x, _ in eng)) / 2.0
    erase(cv, box, {3, 6})
    ink = place(T['RADIO'], H.TALL, baseline=9, x_center=cx, gap=2)
    check_inside(ink, (1, 1, 36, 9))
    draw_shadowed(cv, ink, 3, 6, bg_ok={4})
    # TUNING: canvas = screen x 160-207, y 40-47 (button light area runs x 152-215, arrows at
    # 157-159 and 208-210, so the button centre is x 183.5 = canvas 23.5)
    cv2 = TilemapCanvas(f, ents, 32, 20, 5, 6, 1)
    erase(cv2, (0, 0, 47, 7), {6})
    ink = place(T['TUNING'], H.TINY1, baseline=6, x_center=23.5)
    check_inside(ink, (1, 1, 46, 7))
    paint(cv2, ink, 6)
    return cv


LEGEND = [  # window start tile, English, palette index of its square and letters
    (0, 'POKéMON CENTER', 3), (12, 'POKé MART', 5), (24, 'POKéMON GYM', 0xF),
    (36, 'BATTLE TENT', 2), (48, 'POKéMON CONTEST', 4)]


def job_city_zoom(f):
    """Region-map legend. Three 32x8 sprites side by side show tiles k..k+11 of the ribbon and
    pause at k = 0, 12, 24, 36, 48 (pokenav_region_map.c SpriteCB_CityZoomText), so each entry
    owns one 96-px window. English: 6x6 square at x 7-12, letters from x 14, rows 1-6.
    Hebrew mirrors it: square at x 83-88, text right-aligned to x 81, body rows 1-6 (TINY1;
    lamed's ascender uses row 0, qof's and final nun's tails row 7)."""
    cv = RibbonCanvas(f)
    for k, eng, idx in LEGEND:
        x0 = k * 8
        for y in range(8):
            for x in range(96):
                cv.put(x0 + x, y, 0)
        for y in range(1, 7):
            for x in range(83, 89):
                cv.put(x0 + x, y, idx)
        ink = place(T[eng], H.TINY1, baseline=6, x_right=x0 + 81)
        check_inside(ink, (x0 + 2, 0, x0 + 81, 7))
        paint(cv, ink, idx)
    for X in range(60 * 8, 64 * 8):           # tail of the ribbon stays blank
        for y in range(8):
            assert cv.get(X, y) == 0
    return cv


FORK_GRAPHS = {}


def fork_graph(branch):
    """graph.png as redrawn by a translation fork (its own labels sit elsewhere, so where it erased
    the English it shows the artist's reconstruction of the disc, edge or panel underneath)."""
    if branch not in FORK_GRAPHS:
        data = subprocess.run(['git', '-C', gpaths.GIT, 'show',
                               FORK_REFS[branch] + ':graphics/pokenav/condition/graph.png'],
                              check=True, capture_output=True).stdout
        tmp = tempfile.NamedTemporaryFile(suffix='.png', delete=False)
        tmp.write(data)
        tmp.close()
        FORK_GRAPHS[branch] = pgfx.load(tmp.name)
        os.unlink(tmp.name)
    return FORK_GRAPHS[branch]


def restore_label_background(cv, box):
    """Remove an English graph label (indices 1, 4, f inside its box). Each pixel takes the value
    both forks (es, sigon) agree on when neither has its own label there; otherwise the one fork
    that is clear; otherwise the colour found by walking down/up to the first non-label pixel."""
    x0, y0, x1, y1 = box
    lab = {1, 4, 0xF}
    forks = [fork_graph('es/master'), fork_graph('sigon')]
    todo = [(x, y) for y in range(y0, y1 + 1) for x in range(x0, x1 + 1) if cv.get(x, y) in lab]
    snap = {(x, y): cv.get(x, y) for y in range(y0 - 4, y1 + 5) for x in range(x0 - 4, x1 + 5)}
    for (x, y) in todo:
        votes = [g.get(x, y) for g in forks if g.get(x, y) not in lab]
        if votes:
            cv.put(x, y, Counter(votes).most_common(1)[0][0])
            continue
        col = 3
        for dy in (1, -1, 2, -2, 3, -3, 4, -4):
            v = snap.get((x, y + dy))
            if v is not None and v not in lab:
                col = v
                break
        cv.put(x, y, col)


# ----------------------------------------------------------------------------- driver

def git_original(path):
    data = gpaths.english(path)
    tmp = tempfile.NamedTemporaryFile(suffix='.png', delete=False)
    tmp.write(data)
    tmp.close()
    f = pgfx.load(tmp.name)
    os.unlink(tmp.name)
    return f


def verify(path, orig, written):
    new = pgfx.load(written)
    assert (new.width, new.height, new.bit_depth) == (orig.width, orig.height, orig.bit_depth), path
    assert new._before == orig._before and new._after == orig._after, path + ': PLTE/tRNS changed'
    raw = open(written, 'rb').read()
    assert raw[25] == 3, path + ': colour type changed'
    used = set(new.pixels)
    assert max(used) < (1 << new.bit_depth) and max(used) < 16, path
    changed = sum(1 for a, b in zip(orig.pixels, new.pixels) if a != b)
    return changed


def preview_pair(name, img_en, img_he, zoom=4):
    a = img_en.resize((img_en.width * zoom, img_en.height * zoom), Image.NEAREST)
    b = img_he.resize((img_he.width * zoom, img_he.height * zoom), Image.NEAREST)
    pad = 12
    im = Image.new('RGB', (a.width + b.width + pad * 3, max(a.height, b.height) + 26), (255, 255, 255))
    d = ImageDraw.Draw(im)
    d.text((pad, 2), name + '   (English | Hebrew, %dx)' % zoom, fill=(0, 0, 0))
    im.paste(a, (pad, 18))
    im.paste(b, (a.width + pad * 2, 18))
    return im


def canvas_image(f, kind):
    """1x RGB of what the player sees for this file."""
    if kind[0] == 'sprite':
        _, sw, sh, n = kind
        return pgfx.compose(f, sw, sh, 1).crop((0, 0, sw * (n or len(pgfx.strips(f, sw, sh))), sh))
    if kind[0] == 'ribbon':
        cv = RibbonCanvas(f)
        im = Image.new('RGB', (96, 5 * 10 - 2), (90, 90, 110))
        pal = f.palette
        for n, (k, _, _) in enumerate(LEGEND):
            for y in range(8):
                for x in range(96):
                    im.putpixel((x, n * 10 + y), pal[cv.get(k * 8 + x, y)])
        return im
    if kind[0] == 'tilemap':
        _, binpath, mw, crop = kind
        im, _ = pgfx.render_tilemap(f, os.path.join(REPO, binpath), mw, None, 1)
        return im.crop(crop)
    return pgfx.to_image(f, 1)


JOBS = []


def job(path, kind, fn):
    JOBS.append((path, kind, fn))


OPTIONS = [('options/condition.png', 'CONDITION', True), ('options/ribbons.png', 'RIBBONS', True),
           ('options/switch_off.png', 'SWITCH OFF', True), ('options/party.png', 'PARTY PKMN', True),
           ('options/search.png', 'SEARCH', True), ('options/cancel.png', 'CANCEL', True),
           ('options/cool.png', 'COOL', False), ('options/beauty.png', 'BEAUTY', False),
           ('options/cute.png', 'CUTE', False), ('options/smart.png', 'SMART', False),
           ('options/tough.png', 'TOUGH', False),
           ('hns/options/hoenn_map.png', 'MAP', True), ('hns/options/match_call.png', 'CALL', True),
           ('hns/options/radio.png', 'RADIO', True)]
for p, e, icon in OPTIONS:
    job('graphics/pokenav/' + p, ('sprite', 32, 16, None), lambda f, e=e, icon=icon: job_option(f, e, icon))

for p, e in [('left_headers/main_menu.png', 'MAIN MENU'), ('left_headers/condition.png', 'CONDITION'),
             ('left_headers/ribbons.png', 'RIBBONS'), ('hns/left_headers/match_call.png', 'CALL')]:
    job('graphics/pokenav/' + p, ('sprite', 64, 32, None), lambda f, e=e: job_main_header(f, e))

for p, e in [('left_headers/party.png', 'PARTY PKMN'), ('left_headers/search.png', 'SEARCH'),
             ('left_headers/cool.png', 'COOL'), ('left_headers/beauty.png', 'BEAUTY'),
             ('left_headers/cute.png', 'CUTE'), ('left_headers/smart.png', 'SMART'),
             ('left_headers/tough.png', 'TOUGH')]:
    job('graphics/pokenav/' + p, ('sprite', 32, 16, 2), lambda f, e=e: job_sub_header(f, e))

job('graphics/pokenav/condition/graph.png', ('tilemap', 'graphics/pokenav/condition/graph.bin', 32,
                                             (96, 0, 216, 144)), job_graph)


job('graphics/pokenav/condition/cancel.png', ('plain',), job_condition_cancel)
job('graphics/pokenav/hns/radio/ui_tiles.png', ('tilemap', RADIO_MAP, 32, (16, 8, 240, 56)), job_radio)
job('graphics/pokenav/region_map/city_zoom_text.png', ('ribbon',), job_city_zoom)


def main(filters):
    os.makedirs(OUT, exist_ok=True)
    report = []
    for path, kind, fn in JOBS:
        if filters and not any(s in path for s in filters):
            continue
        orig = git_original(path)
        work = git_original(path)
        fn(work)
        dst = gpaths.write_target(path)
        work.save(dst)
        n = verify(path, orig, dst)
        name = path.replace('graphics/pokenav/', '')
        pair = preview_pair(name, canvas_image(orig, kind), canvas_image(work, kind))
        pair.save(os.path.join(OUT, 'pv_' + name.replace('/', '__')))
        report.append((path, n))
        print('%-50s %5d px changed' % (path, n))
    return report


if __name__ == '__main__':
    main(sys.argv[1:])
