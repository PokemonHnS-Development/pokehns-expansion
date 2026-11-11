import contextlib
import io
import json
import os
import subprocess
import sys
import time
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import rom_sweep as rs  # noqa: E402
import textwidth as tw  # noqa: E402
from fixtures import CHARMAP, TempTree, TOOLS  # noqa: E402
import paths  # noqa: E402

EN_ROM = paths.EN_ROM or ''
B = 0x08000000
CM = tw.Charmap(CHARMAP)


def enc(text):
    m = tw.TextModel.__new__(tw.TextModel)
    m.charmap, m.subst, m.warnings, m.fill = CM, {}, [], 'max'
    return bytes(m.encode(text))


def synthetic_rom(hello='Hello there, my friend!$'):
    """0x000 .text with a sentence (code: skipped); 0x100 script_data with bytecode then a labelled
    string; 0x200 .rodata struct with an inline name; 0x300 graphics object with a sentence (skipped);
    0x380 an aligned C string after 0xFF + padding."""
    d = bytearray(b'\x55' * 0x400)
    def put(off, data):
        d[off:off + len(data)] = data
    put(0x010, enc('Code is not text here$'))
    put(0x10C, bytes([0x6A, 0x5A, 0x0F, 0x02]))
    put(0x110, enc(hello))
    put(0x200, bytes([0x55, 0x55, 0x00, 0x00]) + enc('BLACK BELT$'))
    put(0x300, enc('Graphics never hold words$'))
    put(0x380, b'\xff\x00\x00\x00' + enc('It is not very effective…$'))
    sections = [{'name': '.text', 'addr': B, 'size': 0x100, 'exec': True},
                {'name': 'script_data', 'addr': B + 0x100, 'size': 0x100, 'exec': False},
                {'name': '.rodata', 'addr': B + 0x200, 'size': 0x200, 'exec': False}]
    objs = [(B + 0x300, B + 0x380, '.rodata', 'src/graphics.o'), (B + 0x200, B + 0x240, '.rodata', 'src/data.o')]
    syms = rs.Symbols(table=[(B + 0x100, 0x10, 'd', 'Test_EventScript'), (B + 0x110, len(enc(hello)), 'd',
                             'Test_Text_Hello'), (B + 0x200, 0x40, 'R', 'gTrainerClasses')])
    return bytes(d), sections, objs, syms


def rom_text(data, sections, objs, syms):
    return rs.RomText(None, 'x.elf', None, CM, data=data, sections=sections, objs=objs, syms=syms).scan()


class SyntheticTest(unittest.TestCase):
    def test_runs(self):
        rt = rom_text(*synthetic_rom())
        got = {r['addr'] - B: r['text'] for r in rt.runs}
        self.assertEqual(got, {0x110: 'Hello there, my friend!$', 0x204: 'BLACK BELT$',
                               0x384: 'It is not very effective…$'})
        self.assertEqual(rt.syms.where(B + 0x110), 'Test_Text_Hello')
        self.assertEqual(rt.obj_at(B + 0x204), 'src/data.o')

    def test_compare_reports_only_shared_english(self):
        en = rom_text(*synthetic_rom())
        he = rom_text(*synthetic_rom(hello='שלום לך, ידידי!$'))
        found, other = rs.compare(he, en, None, all_latin=True)
        self.assertEqual(sorted(r['text'] for r in found), ['BLACK BELT$', 'It is not very effective…$'])
        self.assertEqual(other, [])
        self.assertEqual(found[0]['en_addr'] is not None, True)

    def test_is_text(self):
        rt = rs.RomText(None, 'x.elf', None, CM, data=b'', sections=[], objs=[], syms=rs.Symbols(table=[]))
        self.assertTrue(rt.is_text('{PLAYER} received the\\nPOTION.$'))
        self.assertFalse(rt.is_text('One$'))
        self.assertFalse(rt.is_text('ab cd {0x55}$'))
        self.assertFalse(rt.is_text('ÀÁÂ ÇÈ ab cd ÉÊËÌÎÏÒÓÔ$'))

    def test_source_index(self):
        with TempTree(hebrew=False) as tree:
            idx = rs.SourceIndex(tree, CM)
            loc = idx.locate('This one was not translated, and it is much too long$')
            self.assertEqual(len(loc), 1)
            self.assertTrue(loc[0].startswith('data/maps/TestTown/scripts.inc:'))
            self.assertEqual(idx.locate('Hello {PLAYER}!\\nHow are you?$')[0].split(':')[0],
                             'data/maps/TestTown/scripts.inc')
            # ' and the typographic apostrophe share a byte: either spelling finds the source
            self.assertEqual(rs.normalizer(CM)("don't"), rs.normalizer(CM)('don’t'))

    def test_weather_object_is_swept(self):
        # src/field_weather.o holds the weather names that the Pokédex prints
        data, sections, objs, syms = synthetic_rom()
        objs = objs + [(B + 0x380, B + 0x3A0, '.rodata', 'src/field_weather.o')]
        got = {r['addr'] - B: r['text'] for r in rom_text(data, sections, objs, syms).runs}
        self.assertEqual(got.get(0x384), 'It is not very effective…$')


def one_word_rom():
    """synthetic_rom() plus the one-word string CANCEL at 0x3C1 and, at 0x3E1, struct bytes that
    decode as letters and symbols (GIªËÌÁÁ) before the two-word string at 0x3E8."""
    data, sections, objs, syms = synthetic_rom()
    d = bytearray(data)
    for off, text in ((0x3C0, 'CANCEL$'), (0x3E0, 'GIªËÌÁÁFar away$')):
        d[off:off + 1 + len(enc(text))] = b'\xff' + enc(text)
    return bytes(d), sections, objs, syms


class MinWordsTest(unittest.TestCase):
    def runs(self, min_words):
        data, sections, objs, syms = one_word_rom()
        rt = rs.RomText(None, 'x.elf', None, CM, min_words=min_words, data=data, sections=sections, objs=objs,
                        syms=syms).scan()
        return rt, {r['addr'] - B: r['text'] for r in rt.runs}

    def test_one_word_runs_with_min_words_1(self):
        # 1 adds the one-word runs and keeps every run of the default, where it starts
        _, two = self.runs(2)
        _, one = self.runs(1)
        self.assertNotIn(0x3C1, two)
        self.assertEqual(two.get(0x3E8), 'Far away$')
        two[0x3C1] = 'CANCEL$'
        self.assertEqual(one, two)

    def test_one_word_english_is_reported(self):
        en, _ = self.runs(1)
        he, _ = self.runs(1)
        found, _ = rs.compare(he, en, None)
        self.assertIn('CANCEL$', [r['text'] for r in found])
        en, _ = self.runs(2)
        he, _ = self.runs(2)
        found, _ = rs.compare(he, en, None)
        self.assertNotIn('CANCEL$', [r['text'] for r in found])

    def test_min_words_below_1_is_refused(self):
        data, sections, objs, syms = one_word_rom()
        for n in (0, -1):
            with self.assertRaises(ValueError):
                rs.RomText(None, 'x.elf', None, CM, min_words=n, data=data, sections=sections, objs=objs, syms=syms)
        err = io.StringIO()
        with contextlib.redirect_stderr(err), self.assertRaises(SystemExit) as cm:
            rs.main(['missing_he.gba', '--en', 'missing_en.gba', '--min-words', '0'])
        self.assertEqual(cm.exception.code, 2)
        self.assertIn('--min-words', err.getvalue())


@unittest.skipUnless(os.path.exists(EN_ROM), 'English reference ROM not built')
class EnglishRomTest(unittest.TestCase):
    def test_english_vs_itself(self):
        t0 = time.time()
        out = subprocess.run([sys.executable, os.path.join(TOOLS, 'rom_sweep.py'), EN_ROM, '--en', EN_ROM,
                              '--json', '-'], capture_output=True, text=True)
        secs = time.time() - t0
        self.assertLess(secs, 60)
        self.assertEqual(out.returncode, 1, out.stderr)
        d = json.loads(out.stdout)
        runs = d['english']
        self.assertGreater(len(runs), 15000)
        by_sym = {r['symbol']: r for r in runs}
        r = by_sym['NewBarkTown_Text_LassState5']
        self.assertTrue(r['text'].startswith('Call your mom on your POKéGEAR'))
        self.assertTrue(any('NewBarkTown_hns/scripts.inc' in s for s in r['source']))
        self.assertIn('gText_RegisteredTrainerinPokeNav', by_sym)
        # the weather names of src/field_weather.o (the Pokédex's evolution page prints them)
        self.assertIn('SUNNY CLOUDS$', [r['text'] for r in runs if (r['object'] or '').endswith('src/field_weather.o')])
        located = sum(1 for r in runs if r['source'])
        self.assertGreater(located / float(len(runs)), 0.98)
        # code and the debug menu are not swept
        self.assertFalse(any((r['object'] or '').endswith('src/debug.o') for r in runs))


if __name__ == '__main__':
    unittest.main()
