import os
import subprocess
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import textwidth as tw  # noqa: E402
import wrap  # noqa: E402
from fixtures import TempTree, TOOLS  # noqa: E402

W5 = 'אבגדה'          # 5 glyphs x 7 px = 35 px in the fixture's FONT_NORMAL


class WrapTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.tmp = TempTree(kind='fonts')
        cls.tree = cls.tmp.__enter__()
        cls.m = tw.TextModel(cls.tree, symtree=None, hebrew_widths='table', reference_tree=None)

    @classmethod
    def tearDownClass(cls):
        cls.tmp.__exit__(None, None, None)

    def wrapper(self, px=110, prompt=102, lines=2, scroll=True):
        return wrap.Wrapper(self.m, wrap.Budget([('FONT_NORMAL', px, prompt)], lines, scroll))

    def test_refill_moves_breaks_only(self):
        # each word 35 px, word + space + word = 73, three words = 111 (> 110): two words a line
        src = '\\n'.join([W5] * 3) + '\\n' + ' '.join([W5] * 3) + '$'
        out, detail, problems = self.wrapper().wrap(src)
        self.assertEqual(out, '%s %s\\n%s %s\\l%s %s$' % ((W5,) * 6))
        self.assertEqual(problems, [])
        self.assertEqual(wrap.canonical(out), wrap.canonical(src))
        self.assertEqual([l['width'] for l in detail[0]], [73, 73, 73])
        self.assertEqual([l['prompt'] for l in detail[0]], [False, True, False])

    def test_pages_stay(self):
        src = '%s %s %s\\p%s$' % ((W5,) * 4)
        out, _, _ = self.wrapper().wrap(src)
        self.assertEqual(out, '%s %s\\n%s\\p%s$' % ((W5,) * 4))

    def test_prompt_budget_on_last_line_before_p(self):
        # 3 words in one line = 111 px: fits neither; 2 words = 73 fits 75 but the line before \\p
        # gets the prompt budget (75 - 8 = 67), so the second word moves down
        w = wrap.Wrapper(self.m, wrap.Budget([('FONT_NORMAL', 75, 67)], 2, True))
        out, detail, problems = w.wrap('%s %s\\p%s$' % ((W5,) * 3))
        self.assertEqual(out, '%s\\n%s\\p%s$' % ((W5,) * 3))
        self.assertEqual(problems, [])

    def test_placeholder_is_worst_case(self):
        out, detail, _ = self.wrapper(px=200, prompt=192).wrap('{PLAYER} %s %s %s$' % ((W5,) * 3))
        self.assertEqual(detail[0][0]['width'], 7 * 8 + 3 + 35 + 3 + 35 + 3 + 35)
        self.assertNotIn('\\n', out)

    def test_no_scroll_too_many_lines(self):
        out, _, problems = self.wrapper(scroll=False, prompt=110).wrap(' '.join([W5] * 7))
        self.assertEqual(out.count('\\n'), 3)
        self.assertNotIn('\\l', out)
        self.assertTrue(any('reword' in p for p in problems))

    def test_word_too_wide(self):
        _, _, problems = self.wrapper(px=30, prompt=22).wrap(W5 + '$')
        self.assertTrue(problems)

    def test_idempotent_and_keeps_codes(self):
        src = '{COLOR RED}%s %s {FONT_NARROW}%s %s %s$' % ((W5,) * 5)
        once, _, _ = self.wrapper().wrap(src)
        twice, _, _ = self.wrapper().wrap(once)
        self.assertEqual(once, twice)
        self.assertIn('{COLOR RED}', once)
        self.assertIn('{FONT_NARROW}', once)

    def test_kind_budget(self):
        b = wrap.budget_for_kind('move_description')
        self.assertEqual(b.lines, 2)
        self.assertFalse(b.scroll)
        self.assertIn(('FONT_NARROW', 128, 128), b.checks)
        d = wrap.budget_for_kind('overworld_dialogue')
        self.assertEqual((d.checks, d.lines, d.scroll), ([('FONT_NORMAL', 208, 200)], 2, True))

    def test_cli(self):
        out = subprocess.run([sys.executable, os.path.join(TOOLS, 'wrap.py'), '--fonts-tree', self.tree,
                              '--px', '110', ' '.join([W5] * 4) + '$'], capture_output=True, text=True)
        self.assertEqual(out.returncode, 0, out.stderr)
        self.assertEqual(out.stdout.splitlines()[0], '%s %s\\n%s %s$' % ((W5,) * 4))


if __name__ == '__main__':
    unittest.main()
