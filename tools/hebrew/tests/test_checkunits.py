import json
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import checkunits  # noqa: E402
import drift  # noqa: E402
import paths  # noqa: E402
import textwidth as tw  # noqa: E402
from fixtures import CHARMAP, TempTree, token_cases  # noqa: E402

SCRIPT = 'data/maps/TestTown/scripts.inc'
LONG = 'א' * 29          # 203 px in the fixture's FONT_NORMAL: over a prompt line's 200, under 208


def unit(he, en='', kind='script', file=SCRIPT, **kw):
    u = {'id': 'test', 'file': file, 'kind': kind, 'key': 'TestTown_Text_X', 'en': en, 'he': he}
    u.update(kw)
    return u


def kinds(found):
    return [x.split()[0] for x in found]


class CheckUnitsTest(unittest.TestCase):
    """checkunits.check with the fixture fonts (Hebrew letters 7 px in FONT_NORMAL) and charmap."""

    @classmethod
    def setUpClass(cls):
        cls.tmp = TempTree()
        tree = cls.tmp.__enter__()
        cls.saved = checkunits._MODEL, checkunits.CHARMAP, checkunits.CHARS
        checkunits._MODEL = tw.TextModel(tree, symtree=tree, hebrew_widths='table', reference_tree=None)
        checkunits.CHARMAP = CHARMAP
        checkunits.CHARS = checkunits.load_charmap()

    @classmethod
    def tearDownClass(cls):
        checkunits._MODEL, checkunits.CHARMAP, checkunits.CHARS = cls.saved
        cls.tmp.__exit__(None, None, None)

    def test_clean_unit(self):
        self.assertEqual(checkunits.check(unit('שלום {PLAYER}!\\nמה שלומך?$', 'Hello {PLAYER}!\\nHow are you?$')),
                         ([], []))

    def test_token_rule_is_drifts(self):
        for en, he, same, why in token_cases():
            errs, _ = checkunits.check(unit(he, en))
            t_en = [t for t in drift.TOKEN_RE.findall(en) if t not in drift.DROPPABLE_TOKENS]
            t_he = [t for t in drift.TOKEN_RE.findall(he) if t not in drift.DROPPABLE_TOKENS]
            self.assertEqual('TOKENS' in kinds(errs), not drift.same_tokens(t_en, t_he), why)
            self.assertEqual('TOKENS' in kinds(errs), not same, why)

    def test_digits(self):
        self.assertEqual(checkunits.check(unit('דרך 23$', 'Route 32$')), (["DIGITS reversed ['32'] -> ['23']"], []))
        self.assertEqual(checkunits.check(unit('דרך 32 ו-23$', 'Route 23 and 32$')), ([], []))
        errs, warns = checkunits.check(unit('דרך$', 'Route 32$'))
        self.assertEqual((errs, kinds(warns)), ([], ['DIGITS']))

    def test_c_escapes(self):
        c = dict(kind='c', file='src/strings.c')
        self.assertIn('ESCAPE bare double quote (use ”)', checkunits.check(unit('שלום "חבר"', 'Hi "pal"', **c))[0])
        self.assertIn('ESCAPE \\t', checkunits.check(unit('שלום\\tחבר', 'Hi pal', **c))[0])
        self.assertEqual(checkunits.check(unit('שלום ”חבר”\\nלך', 'Hi "pal"\\ngo', **c)), ([], []))

    def test_budgets_are_budgets_json(self):
        with open(paths.BUDGETS, encoding='utf-8') as f:
            budgets = json.load(f)['kinds']
        cases = [
            ('overworld_dialogue', dict(kind='script', file=SCRIPT)),
            ('battle_message', dict(kind='c', file='src/battle_message.c', key='STRINGID_X')),
            ('item_description', dict(kind='c', file='src/data/items.h', field='description')),
            ('item_description', dict(kind='c', file='src/data/items.h', field=None, key='sFullHealDesc')),
            ('relearner_move_description', dict(kind='c', file='src/data/moves_info.h', field='description')),
            ('dex_ability', dict(kind='c', file='src/data/abilities.h', field='description')),
            ('dex_entry', dict(kind='c', file='src/data/pokemon/species_info/gen_1_families.h',
                               field='description')),
        ]
        for name, kw in cases:
            b = budgets[name]
            font, px, lines, prompt_px = checkunits.budget_for(unit('', **kw))
            self.assertEqual((font, px, lines), (b['font'], b['max_px_per_line'], b['max_lines']), name)
            self.assertEqual(prompt_px, b.get('prompt_line_px', px), name)
            # A line that ends in a prompt arrow is held to prompt_line_px; any other line to the full width.
            if 'prompt_line_px' in b:
                end = '$' if kw['kind'] == 'script' else ''
                errs, _ = checkunits.check(unit(LONG + '\\pב' + end, 'A\\pB' + end, **kw))
                self.assertEqual(errs, ['WIDTH page 1 line 1: 203 px > %d' % b['prompt_line_px']], name)
                errs, _ = checkunits.check(unit(LONG + '\\nב' + end, 'A\\nB' + end, **kw))
                self.assertEqual(errs, [], name)
        self.assertIsNone(checkunits.budget_for(unit('', kind='c', file='src/strings.c')))


if __name__ == '__main__':
    unittest.main()
