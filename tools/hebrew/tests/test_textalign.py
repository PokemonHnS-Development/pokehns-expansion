"""textalign.py on synthetic screenshots: a framed window with lines of blocky 'glyphs' drawn the
way the game draws text (ink plus a shadow one pixel right and below), English and Hebrew
placed by hand."""
import contextlib
import io
import json
import os
import shutil
import struct
import sys
import tempfile
import unittest
import zlib

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(HERE), 'emu'))
import textalign as ta  # noqa: E402

BG, FRAME, PAPER, INK, SHADOW = 0x203040, 0x4A425A, 0xFFFFFF, 0x636363, 0xD6D6CE
W, H = 240, 160
BOX = (16, 100, 223, 151)          # the paper of a message box (inclusive)


def blank():
    rows = [[BG] * W for _ in range(H)]
    return ta.Shot(W, H, rows)


def window(shot, box=BOX, paper=PAPER, frame=FRAME):
    x0, y0, x1, y1 = box
    for y in range(y0 - 3, y1 + 4):
        for x in range(x0 - 3, x1 + 4):
            shot.rows[y][x] = frame
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            shot.rows[y][x] = paper


def glyph(shot, x, y, shape, clip=None):
    """Draw one 5x9 glyph at (x, y): SHAPE is 'E' (an English-like letter) or 'H' (a Hebrew-like
    one); each ink pixel gets a shadow pixel to its right and below. CLIP (x0, y0, x1, y1) keeps
    only the pixels inside it."""
    if shape == 'E':
        pix = [(0, r) for r in range(9)] + [(c, 0) for c in range(5)] + [(c, 4) for c in range(4)] + \
              [(c, 8) for c in range(5)]
    else:
        pix = [(c, 0) for c in range(5)] + [(4, r) for r in range(9)] + [(1, r) for r in range(3, 9)]
    ink = set((x + c, y + r) for (c, r) in pix)

    def inside(px, py):
        return clip is None or (clip[0] <= px <= clip[2] and clip[1] <= py <= clip[3])
    for (px, py) in ink:
        for (sx, sy) in ((px + 1, py), (px, py + 1), (px + 1, py + 1)):
            if (sx, sy) not in ink and shot.rows[sy][sx] != INK and inside(sx, sy):
                shot.rows[sy][sx] = SHADOW
    for (px, py) in ink:
        if inside(px, py):
            shot.rows[py][px] = INK


def span(n):
    """Columns from a line's first ink to its last shadow column, for N glyphs."""
    return (n - 1) * 7 + ((n - 1) // 3) * 3 + 5


def line(shot, x, y, n, shape, clip=None):
    """N glyphs from x (7 px apart, 3 more after every third glyph, like a word space)."""
    for i in range(n):
        glyph(shot, x + i * 7 + (i // 3) * 3, y, shape, clip)


def rline(shot, margin, y, n, shape, box=BOX):
    """A line whose last shadow column stands MARGIN px inside the box's right edge."""
    line(shot, box[2] - margin - span(n), y, n, shape)


def triangle(shot, x, y, right=True, colour=INK):
    """A 5-wide, 9-tall filled menu cursor."""
    for c in range(5):
        h = 9 - 2 * c
        cx = x + c if right else x + 4 - c
        for r in range(h):
            shot.rows[y + c + r][cx] = colour


def pair():
    en, he = blank(), blank()
    window(en)
    window(he)
    return en, he


def classes(res):
    return [w['class'] for w in res['windows'] + res['unknown']]


class TextAlignTest(unittest.TestCase):

    def test_mirrored_lines_are_ok(self):
        en, he = pair()
        line(en, BOX[0] + 8, 108, 9, 'E')
        line(en, BOX[0] + 8, 126, 6, 'E')
        # Hebrew ends where English starts, mirrored: the shadow column stands 8 px from the edge
        rline(he, 8, 108, 7, 'H')
        rline(he, 8, 126, 5, 'H')
        res = ta.analyse_pair(en, he)
        self.assertEqual(classes(res), ['OK'])
        lines = res['windows'][0]['lines']
        self.assertEqual([ln['status'] for ln in lines], ['OK', 'OK'])
        self.assertEqual(lines[0]['en_margins'][0], 8)
        self.assertEqual(lines[0]['he_margins'][1], 8)
        self.assertIn('mirror', lines[0]['anchors'])

    def test_margin_off_by_more_than_the_tolerance_is_a_mismatch(self):
        en, he = pair()
        line(en, BOX[0] + 8, 108, 5, 'E')
        rline(he, 17, 108, 8, 'H')                      # 17-px right margin against 8
        res = ta.analyse_pair(en, he)
        self.assertEqual(classes(res), ['MIRROR-MISMATCH'])
        ln = res['windows'][0]['lines'][0]
        self.assertEqual(ln['he_margins'][1] - ln['en_margins'][0], 9)

    def test_tolerance_two_pixels(self):
        en, he = pair()
        line(en, BOX[0] + 8, 108, 9, 'E')
        rline(he, 10, 108, 8, 'H')                      # 10 against 8: within 2 px
        self.assertEqual(classes(ta.analyse_pair(en, he)), ['OK'])
        self.assertEqual(classes(ta.analyse_pair(en, he, tol=1)), ['MIRROR-MISMATCH'])

    def test_english_margin_kept_is_in_place(self):
        en, he = pair()
        line(en, BOX[0] + 8, 108, 9, 'E')
        line(he, BOX[0] + 8, 108, 5, 'H')
        self.assertEqual(classes(ta.analyse_pair(en, he)), ['IN-PLACE'])

    def test_centred_line_stays_centred(self):
        en, he = pair()
        mid = (BOX[0] + BOX[2]) // 2
        line(en, mid - span(9) // 2, 108, 9, 'E')       # centred
        line(he, mid - span(5) // 2, 108, 5, 'H')       # centred, narrower
        res = ta.analyse_pair(en, he)
        self.assertEqual(classes(res), ['OK'])
        self.assertIn('centre', res['windows'][0]['lines'][0]['anchors'])

    def test_centred_line_moved_off_centre(self):
        en, he = pair()
        mid = (BOX[0] + BOX[2]) // 2
        line(en, mid - span(9) // 2, 108, 9, 'E')
        line(he, mid + 20, 108, 5, 'H')                 # off centre, neither mirrored nor in place
        self.assertEqual(classes(ta.analyse_pair(en, he)), ['CENTRE-OFF'])

    def test_ink_on_the_edge(self):
        en, he = pair()
        line(en, BOX[0] + 2, 108, 9, 'E')               # English keeps 2 px at the start
        line(he, BOX[0], 108, 20, 'H')                  # Hebrew ink on the window's first column
        res = ta.analyse_pair(en, he)
        self.assertEqual(classes(res), ['EDGE'])

    def test_mirrored_shadow_on_the_edge_is_not_an_edge(self):
        en, he = pair()
        line(en, BOX[0] + 1, 108, 9, 'E')               # English starts 1 px in
        rline(he, 0, 108, 8, 'H')                       # Hebrew's shadow on the last column
        self.assertEqual(classes(ta.analyse_pair(en, he)), ['OK'])

    def test_row_shift(self):
        en, he = pair()
        line(en, BOX[0] + 8, 108, 9, 'E')
        rline(he, 8, 114, 8, 'H')                       # 6 rows lower
        res = ta.analyse_pair(en, he)
        self.assertEqual(classes(res), ['ROW-SHIFT'])

    def test_small_row_difference_is_not_a_shift(self):
        en, he = pair()
        line(en, BOX[0] + 8, 108, 9, 'E')
        rline(he, 8, 110, 8, 'H')                       # 2 rows: ascender/descender range
        self.assertEqual(classes(ta.analyse_pair(en, he)), ['OK'])

    def test_text_over_art_is_unknown(self):
        en, he = blank(), blank()
        for y in range(90, 150):
            for x in range(10, 230):
                c = 0x30A030 if (x // 2 + y // 2) % 3 else 0x208020
                c = 0x60C060 if (x + 2 * y) % 5 == 0 else c
                en.rows[y][x] = he.rows[y][x] = c
        line(en, 40, 110, 9, 'E')
        line(he, 120, 110, 7, 'H')
        res = ta.analyse_pair(en, he)
        self.assertEqual(set(classes(res)), {'UNKNOWN'})

    def test_cursor_left_unmirrored(self):
        en, he = pair()
        triangle(en, BOX[0] + 3, 108)
        line(en, BOX[0] + 11, 108, 6, 'E')
        rline(he, 11, 108, 6, 'H')
        triangle(he, BOX[2] - 3 - 4, 108, right=True)   # mirrored place, but still pointing right
        res = ta.analyse_pair(en, he)
        self.assertEqual(classes(res), ['MIRROR-MISMATCH'])
        self.assertTrue(any('points right' in n for n in res['windows'][0]['notes']))

    def test_cursor_mirrored(self):
        en, he = pair()
        triangle(en, BOX[0] + 3, 108)
        line(en, BOX[0] + 11, 108, 6, 'E')
        rline(he, 11, 108, 6, 'H')
        triangle(he, BOX[2] - 3 - 4, 108, right=False)
        res = ta.analyse_pair(en, he)
        self.assertEqual(classes(res), ['OK'])
        self.assertEqual(res['windows'][0]['lines'][0]['cursor'][1][2], 'left')

    def test_mixed_window_is_a_mismatch(self):
        en, he = pair()
        line(en, BOX[0] + 8, 108, 9, 'E')
        line(en, BOX[0] + 8, 126, 9, 'E')
        rline(he, 8, 108, 8, 'H')                       # mirrored
        line(he, BOX[0] + 8, 126, 4, 'H')               # left where English starts
        res = ta.analyse_pair(en, he)
        self.assertEqual(classes(res), ['MIRROR-MISMATCH'])
        self.assertTrue(any('keep the English start' in n for n in res['windows'][0]['notes']))

    def test_menu_sized_to_its_text(self):
        en, he = blank(), blank()
        window(en, (20, 20, 100, 60))
        window(he, (20, 20, 80, 60))                    # the Hebrew menu is 20 px narrower
        line(en, 28, 26, 9, 'E')                        # ends 5 px before English's frame
        rline(he, 8, 26, 5, 'H', box=(20, 20, 80, 60))
        res = ta.analyse_pair(en, he)
        self.assertEqual([w['class'] for w in res['windows']], ['OK'])
        w = res['windows'][0]
        self.assertEqual(w['rect'][2], 80)
        self.assertEqual(w['rect_en'][2], 100)

    def test_text_seen_through_a_gap(self):
        en, he = blank(), blank()
        for s in (en, he):
            window(s, (20, 20, 120, 60))
            window(s, (130, 40, 141, 55))               # a 12-px gap between two frames
        line(en, 28, 26, 9, 'E')
        rline(he, 8, 26, 8, 'H', box=(20, 20, 120, 60))
        line(he, 126, 43, 4, 'H', clip=(130, 40, 141, 55))   # Hebrew seen through the gap
        res = ta.analyse_pair(en, he)
        self.assertIn('EDGE', classes(res))
        edge = [w for w in res['windows'] if w['class'] == 'EDGE'][0]
        self.assertEqual(edge['rect'][0], 130)

    def test_identical_shots(self):
        en, he = pair()
        line(en, 30, 108, 5, 'E')
        line(he, 30, 108, 5, 'E')
        res = ta.analyse_pair(en, he)
        self.assertTrue(res.get('identical'))
        self.assertEqual(res['windows'], [])


class PngTest(unittest.TestCase):

    def test_round_trip(self):
        d = tempfile.mkdtemp()
        try:
            rows = [[(x * 7 + y * 3) & 0xFFFFFF for x in range(13)] for y in range(5)]
            p = os.path.join(d, 'a.png')
            ta.write_png(p, rows)
            s = ta.read_png(p)
            self.assertEqual((s.w, s.h), (13, 5))
            self.assertEqual(s.rows, rows)
        finally:
            shutil.rmtree(d)

    def test_filtered_rows(self):
        """Rows stored with the Sub, Up, Average and Paeth filters decode to the same pixels."""
        w, h = 6, 5
        rows = [[(0x10 * x + 0x20 * y) | ((x * y) << 8) | ((x + y) << 16) for x in range(w)] for y in range(h)]
        raw_rows = [bytearray(b for v in r for b in ((v >> 16) & 255, (v >> 8) & 255, v & 255)) for r in rows]
        out = bytearray()
        prev = bytearray(w * 3)
        for y, cur in enumerate(raw_rows):
            f = (y % 4) + 1
            enc = bytearray()
            for i in range(len(cur)):
                a = cur[i - 3] if i >= 3 else 0
                b = prev[i]
                c = prev[i - 3] if i >= 3 else 0
                pred = {1: a, 2: b, 3: (a + b) >> 1, 4: ta._paeth(a, b, c)}[f]
                enc.append((cur[i] - pred) & 255)
            out.append(f)
            out += enc
            prev = cur

        def chunk(t, c):
            return struct.pack('>I', len(c)) + t + c + struct.pack('>I', zlib.crc32(t + c) & 0xffffffff)
        d = tempfile.mkdtemp()
        try:
            p = os.path.join(d, 'f.png')
            with open(p, 'wb') as fh:
                fh.write(ta.PNG_SIG + chunk(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 2, 0, 0, 0)) +
                         chunk(b'IDAT', zlib.compress(bytes(out))) + chunk(b'IEND', b''))
            self.assertEqual(ta.read_png(p).rows, rows)
        finally:
            shutil.rmtree(d)


class ToursTest(unittest.TestCase):

    def test_tours_writes_report_summary_and_crops(self):
        d = tempfile.mkdtemp()
        try:
            for side in ('en', 'he'):
                os.makedirs(os.path.join(d, side, 't1'))
            en, he = pair()
            line(en, BOX[0] + 8, 108, 9, 'E')
            rline(he, 20, 108, 8, 'H')
            ta.write_png(os.path.join(d, 'en', 't1', 's1.png'), en.rows)
            ta.write_png(os.path.join(d, 'he', 't1', 's1.png'), he.rows)
            ta.write_png(os.path.join(d, 'he', 't1', 's2.png'), he.rows)    # no English shot
            out = os.path.join(d, 'out')
            with contextlib.redirect_stdout(io.StringIO()):
                rc = ta.main(['tours', os.path.join(d, 'en'), os.path.join(d, 'he'), out])
            self.assertEqual(rc, 0)
            with open(os.path.join(out, 'report.json')) as fh:
                rep = json.load(fh)
            self.assertEqual(rep['pairs'], 1)
            self.assertEqual(rep['missing_en'], ['t1/s2.png'])
            self.assertEqual(rep['counts'], {'MIRROR-MISMATCH': 1})
            crop = rep['shots']['t1/s1.png']['windows'][0]['crop']
            self.assertTrue(os.path.exists(os.path.join(out, 'crops', crop)))
            with open(os.path.join(out, 'summary.txt')) as fh:
                self.assertIn('== MIRROR-MISMATCH: 1 windows in 1 groups', fh.read())
        finally:
            shutil.rmtree(d)


if __name__ == '__main__':
    unittest.main()
