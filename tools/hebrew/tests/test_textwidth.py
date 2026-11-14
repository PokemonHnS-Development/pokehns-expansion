import json
import os
import subprocess
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import textwidth as tw  # noqa: E402
from fixtures import TempTree, SHIN, TOOLS  # noqa: E402


class TextWidthTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.tmp = TempTree()
        cls.tree = cls.tmp.__enter__()
        cls.m = tw.TextModel(cls.tree, symtree=cls.tree, hebrew_widths='table', reference_tree=None)

    @classmethod
    def tearDownClass(cls):
        cls.tmp.__exit__(None, None, None)

    def test_tables(self):
        t = self.m.fonts.table(tw.font_id('FONT_NORMAL'))
        self.assertEqual(t[0x00], 3)
        self.assertEqual(t[0xBB], 6)                           # 'A'
        self.assertEqual(self.m.fonts.widest_hebrew(1), (SHIN, 8))
        self.assertEqual(self.m.fonts.widest_hebrew(tw.font_id('NARROWER')), (SHIN, 6))

    def test_plain_widths(self):
        self.assertEqual(self.m.width('Hello$'), 30)
        self.assertEqual(self.m.width('שלום עולם$'), 8 + 3 * 7 + 3 + 4 * 7)   # ש is the 8 px glyph
        self.assertEqual(self.m.width('Hello$', 'FONT_NARROW'), 25)

    def test_placeholders_are_worst_case(self):
        self.assertEqual(self.m.width('{PLAYER}$'), 7 * 8)       # 7 x widest glyph
        self.assertEqual(self.m.width('{STR_VAR_1}$'), 12 * 8)
        self.assertEqual(self.m.width('{PLAYER}$', 'FONT_NARROWER'), 7 * 6)
        self.assertEqual(self.m.width('{PLAYER}$', subst={'PLAYER': '"AB"'}), 12)
        self.assertEqual(self.m.byte_length('{PLAYER}!$'), 8)
        # prefix read from the tree's battle_message.c: "The opposing " is the wider prefix
        w = self.m.width('{B_ATK_NAME_WITH_PREFIX}$')
        self.assertEqual(w, 11 * 6 + 2 * 3 + 12 * 8)          # 'The opposing ' + 12-glyph nickname

    def test_font_switch_and_pen_moves(self):
        self.assertEqual(self.m.width('AB{FONT_NARROW}AB$'), 12 + 10)
        self.assertEqual(self.m.width('A{CLEAR_TO 50}B$'), 56)
        self.assertEqual(self.m.width('ABCDEFGHIJ{CLEAR_TO 10}B$'), 66)   # CLEAR_TO never moves back
        self.assertEqual(self.m.width('ABCDEFGHIJ{SKIP 10}B$'), 60)       # SKIP does; extent stays 60
        self.assertEqual(self.m.width('A{CLEAR 4}B$'), 16)

    def test_lines_pages_prompts(self):
        ls = self.m.lines('AB\\nCDE\\lF\\pGH$')
        self.assertEqual([(l.page, l.row, l.width, l.end, l.prompt) for l in ls],
                         [(1, 1, 12, 'n', False), (1, 2, 18, 'l', True), (1, 2, 6, 'p', True), (2, 1, 12, '$', False)])

    def test_encode_decode_roundtrip(self):
        src = 'שלום {PLAYER}!\\nAB 12 {COLOR RED}x\\pé$'
        saved, self.m.subst = self.m.subst, {}          # raw bytes: placeholders unexpanded
        try:
            data = bytes(self.m.encode(src))
            again = self.m.decode(data)
            self.assertEqual(bytes(self.m.encode(again)), data)
        finally:
            self.m.subst = saved
        self.assertTrue(again.startswith('שלום {PLAYER}!\\nAB 12 '))
        self.assertEqual(data[-1], tw.EOS)

    def test_errors(self):
        errs = []
        self.m.encode('A一B$', errors=errs)
        self.assertTrue(any('unencodable' in e for e in errs))
        with self.assertRaises(tw.TextError):
            self.m.encode('{NOT_A_CONSTANT}$')

    def test_battle_auto_wrap(self):
        words = ' '.join(['אבגדה'] * 14) + '$'
        out = tw.battle_auto_wrap(self.m, self.m.encode(words, nbsp=True), 'FONT_NORMAL')
        lines = self.m.layout(out, 'FONT_NORMAL')
        self.assertGreater(len(lines), 1)
        self.assertTrue(all(l.width <= 208 for l in lines))

    def test_cli_json(self):
        out = subprocess.run([sys.executable, os.path.join(TOOLS, 'textwidth.py'), '--tree', self.tree,
                              '--symtree', self.tree, '--hebrew-widths', 'table', '--json', 'AB\\nC$'],
                             capture_output=True, text=True)
        self.assertEqual(out.returncode, 0, out.stderr)
        d = json.loads(out.stdout)
        self.assertEqual([l['width'] for l in d['results'][0]['lines']], [12, 6])


if __name__ == '__main__':
    unittest.main()
