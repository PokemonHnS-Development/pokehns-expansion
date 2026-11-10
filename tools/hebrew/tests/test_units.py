import contextlib
import io
import json
import os
import shutil
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import drift  # noqa: E402
import units  # noqa: E402
from fixtures import TOOLS, copy_data, token_cases  # noqa: E402

INC = 'data/maps/TestTown/scripts.inc'
ITEMS = 'src/data/items.h'
HELLO_HE = 'שלום {PLAYER}\\nמה שלומך?$'
DESC_HE = 'משקם את הנ”ח\\nשל פוקימון\\nב-20 נקודות.'


class UnitsTest(unittest.TestCase):
    """units.py on a copy of tests/data/units: a map script and an items.h entry."""

    def setUp(self):
        self.dir = tempfile.mkdtemp(prefix='hns_units_test_')
        self.tree = copy_data('units', os.path.join(self.dir, 'tree'))
        # No liveness data: every label and literal counts as live unless a test says otherwise.
        self.saved = units.LIVE_LABELS, units.C_STRINGS
        units.LIVE_LABELS = units.C_STRINGS = os.path.join(self.dir, 'absent.json')

    def tearDown(self):
        units.LIVE_LABELS, units.C_STRINGS = self.saved
        shutil.rmtree(self.dir, ignore_errors=True)

    def read(self, rel):
        with open(os.path.join(self.tree, rel), encoding='utf-8') as f:
            return f.read()

    def write(self, rel, text):
        with open(os.path.join(self.tree, rel), 'w', encoding='utf-8') as f:
            f.write(text)

    def chunk(self, us, name='chunk.json'):
        path = os.path.join(self.dir, name)
        with open(path, 'w', encoding='utf-8') as f:
            json.dump({'units': us}, f, ensure_ascii=False)
        return path

    def apply(self, chunk):
        with contextlib.redirect_stdout(io.StringIO()):       # units.apply prints a line per file
            return units.apply([chunk], self.tree, False)

    def unit(self, rel, key):
        return next(u for u in units.extract([rel], self.tree, True) if u['key'] == key)

    def test_script_round_trip(self):
        before = self.read(INC)
        u = self.unit(INC, 'TestTown_Text_Hello')
        self.assertEqual(u['en'], 'Hello {PLAYER}\\nHow are you?$')
        u['he'] = HELLO_HE
        self.assertEqual(self.apply(self.chunk([u])), 1)
        # Two .string lines with the English indent; every other line byte for byte the same.
        self.assertEqual(self.read(INC), before.replace(
            '\t.string "Hello {PLAYER}\\n"\n\t.string "How are you?$"',
            '\t.string "שלום {PLAYER}\\n"\n\t.string "מה שלומך?$"'))
        self.assertEqual(self.unit(INC, 'TestTown_Text_Hello')['en'], HELLO_HE)
        self.assertEqual(drift.split_inc(self.read(INC))[0], drift.split_inc(before)[0])

    def test_c_round_trip(self):
        before = self.read(ITEMS)
        us = units.extract([ITEMS], self.tree, True)
        self.assertEqual([(u['key'], u['macro'], u['en']) for u in us], [
            ('ITEM_POTION.name', 'ITEM_NAME', 'POTION'),
            ('ITEM_POTION.description', 'COMPOUND_STRING', 'Restores the HP of\\na Pokémon by\\n20 points.')])
        us[0]['he'], us[1]['he'] = 'שיקוי', DESC_HE
        self.assertEqual(self.apply(self.chunk(us)), 2)
        # The macros stay; the description keeps one literal per line, split after each \n.
        self.assertEqual(self.read(ITEMS), before.replace('ITEM_NAME("POTION")', 'ITEM_NAME("שיקוי")').replace(
            '"Restores the HP of\\n"\n            "a Pokémon by\\n"\n            "20 points."',
            '"משקם את הנ”ח\\n"\n            "של פוקימון\\n"\n            "ב-20 נקודות."'))
        self.assertEqual([u['en'] for u in units.extract([ITEMS], self.tree, True)], ['שיקוי', DESC_HE])

    def test_token_rule_is_drifts(self):
        for en, he, same, why in token_cases():
            u = {'id': 'case', 'kind': 'script', 'en': en, 'he': he}
            if same:
                units.check_unit(u)
            else:
                with self.assertRaises(SystemExit, msg=why) as cm:
                    units.check_unit(u)
                self.assertTrue(str(cm.exception).startswith('TOKENS'), why)

    def test_english_changed_after_extraction(self):
        u = self.unit(INC, 'TestTown_Text_Bye')
        u['he'] = 'להתראות!$'
        self.write(INC, self.read(INC).replace('Bye for now!', 'Bye for good!'))
        before = self.read(INC)
        with self.assertRaises(SystemExit) as cm:
            self.apply(self.chunk([u]))
        self.assertIn('TestTown_Text_Bye changed in the tree since extraction', str(cm.exception))
        self.assertEqual(self.read(INC), before)

    def test_live_labels(self):
        live = os.path.join(self.dir, 'live_labels.json')
        with open(live, 'w', encoding='utf-8') as f:
            json.dump({INC: {'live': ['TestTown_Text_Hello'], 'debug_only': [], 'dead': [],
                             'flag_off': ['TestTown_Text_Bye']}}, f)
        units.LIVE_LABELS = live
        self.assertEqual([u['key'] for u in units.extract([INC], self.tree, False)], ['TestTown_Text_Hello'])
        self.assertEqual([(u['key'], u['live']) for u in units.extract([INC], self.tree, True)],
                         [('TestTown_Text_Hello', True), ('TestTown_Text_Bye', False)])

    def test_different_hebrew_is_not_overwritten(self):
        old = self.unit(INC, 'TestTown_Text_Hello')
        old['he'] = HELLO_HE
        stale_chunk = self.chunk([old])
        self.apply(stale_chunk)
        self.apply(stale_chunk)          # the same Hebrew again: allowed
        fixed = self.read(INC).replace('מה שלומך?', 'מה נשמע?')    # a later fix in the tree
        self.write(INC, fixed)
        cmd = [sys.executable, os.path.join(TOOLS, 'units.py'), 'apply', stale_chunk, '--tree', self.tree]
        out = subprocess.run(cmd, capture_output=True, text=True)
        self.assertEqual(out.returncode, 1)
        self.assertIn('TestTown_Text_Hello already holds different Hebrew', out.stderr)
        self.assertEqual(self.read(INC), fixed)
        out = subprocess.run(cmd + ['--overwrite-hebrew'], capture_output=True, text=True)
        self.assertEqual(out.returncode, 0, out.stderr)
        self.assertIn('"מה שלומך?$"', self.read(INC))


EN_ITEMS = """const struct Item gItemsInfo[] =
{
    [ITEM_POTION] =
    {
        .name = ITEM_NAME("POTION"),
        .description = COMPOUND_STRING(
            "Restores the HP of\\n"
            "a Pokémon."),
    },

    [ITEM_ICY_ROCK] =
    {
        .name = ITEM_NAME("ICY ROCK"),
    #if B_HAIL
        .description = COMPOUND_STRING("Extends Hail."),
    #else
        .description = COMPOUND_STRING("Extends Snow."),
    #endif
    },
};

static const u8 *const sNames[] =
{
    COMPOUND_STRING("FIRST"),
    COMPOUND_STRING("SECOND"),
    COMPOUND_STRING("THIRD"),
};
"""

# The same file translated: a TEXT_RTL plural name and a shorter description move every later
# literal up or down, the dead Hail branch keeps its English, and the dead SECOND stays English.
HE_ITEMS = """const struct Item gItemsInfo[] =
{
    [ITEM_POTION] =
    {
        .name = ITEM_NAME("שיקוי"),
    #if TEXT_RTL
        .pluralName = ITEM_PLURAL_NAME("שיקויים"),
    #endif
        .description = COMPOUND_STRING("משקם נ”ח."),
    },

    [ITEM_ICY_ROCK] =
    {
        .name = ITEM_NAME("סלע קרח"),
    #if B_HAIL
        .description = COMPOUND_STRING("Extends Hail."),
    #else
        .description = COMPOUND_STRING("מאריך שלג."),
    #endif
    },
};

static const u8 *const sNames[] =
{
    COMPOUND_STRING("ראשון"),
    COMPOUND_STRING("SECOND"),
    COMPOUND_STRING("שלישי"),
};
"""

DEAD = {'Extends Hail.', 'SECOND'}


class CLivenessTest(unittest.TestCase):
    """c_strings.json records a C literal by its line in the English tree; units.py finds it in the
    translated tree by designator, field and place, whatever line it moved to."""

    def setUp(self):
        self.dir = tempfile.mkdtemp(prefix='hns_units_live_')
        self.en = os.path.join(self.dir, 'en')
        self.tree = os.path.join(self.dir, 'tree')
        for root, text in ((self.en, EN_ITEMS), (self.tree, HE_ITEMS)):
            os.makedirs(os.path.join(root, 'src/data'))
            with open(os.path.join(root, ITEMS), 'w', encoding='utf-8') as f:
                f.write(text)
        # The inventory's record of every English literal: line, text and whether a ROM holds it.
        recs = [{'line': line, 'text': text, 'rom_release': text not in DEAD, 'rom_std': text not in DEAD}
                for _, line, text, _, _, _ in units.c_literals(EN_ITEMS)]
        self.c_strings = os.path.join(self.dir, 'c_strings.json')
        with open(self.c_strings, 'w', encoding='utf-8') as f:
            json.dump({ITEMS: recs}, f, ensure_ascii=False)
        self.saved = units.C_STRINGS, units.UPSTREAM
        units.C_STRINGS, units.UPSTREAM = self.c_strings, self.en

    def tearDown(self):
        units.C_STRINGS, units.UPSTREAM = self.saved
        shutil.rmtree(self.dir, ignore_errors=True)

    def live(self, tree):
        return [(u['key'], u['en'], u['live']) for u in units.extract([ITEMS], tree, True)]

    def test_translated_tree_matches_by_designator_and_field(self):
        self.assertEqual(self.live(self.tree), [
            ('ITEM_POTION.name', 'שיקוי', True),
            ('ITEM_POTION.pluralName', 'שיקויים', True),       # not in the English tree: live
            ('ITEM_POTION.description', 'משקם נ”ח.', True),
            ('ITEM_ICY_ROCK.name', 'סלע קרח', True),
            ('ITEM_ICY_ROCK.description', 'Extends Hail.', False),
            ('ITEM_ICY_ROCK.description', 'מאריך שלג.', True),
            ('ITEM_ICY_ROCK', 'ראשון', True),
            ('ITEM_ICY_ROCK', 'SECOND', False),
            ('ITEM_ICY_ROCK', 'שלישי', True)])
        self.assertEqual([u['en'] for u in units.extract([ITEMS], self.tree, False)],
                         ['שיקוי', 'שיקויים', 'משקם נ”ח.', 'סלע קרח', 'מאריך שלג.', 'ראשון', 'שלישי'])

    def test_line_numbers_would_be_wrong_here(self):
        # The plural name moves the list one line down, onto the English lines of other literals:
        # a key by line would mark the live first name dead and the dead SECOND live.
        en_lines = {text: line for _, line, text, _, _, _ in units.c_literals(EN_ITEMS)}
        he_lines = {text: line for _, line, text, _, _, _ in units.c_literals(HE_ITEMS)}
        self.assertEqual(he_lines['ראשון'], en_lines['SECOND'])
        self.assertEqual(he_lines['SECOND'], en_lines['THIRD'])

    def test_english_tree_gives_the_records_verdicts(self):
        self.assertEqual([(text, live) for _, text, live in self.live(self.en)],
                         [(text, text not in DEAD) for _, _, text, _, _, _ in units.c_literals(EN_ITEMS)])

    def test_without_the_english_file_every_literal_is_live(self):
        units.UPSTREAM = os.path.join(self.dir, 'absent')
        err = io.StringIO()
        with contextlib.redirect_stderr(err):
            self.assertTrue(all(live for _, _, live in self.live(self.tree)))
        self.assertIn('%s is not in the English tree' % ITEMS, err.getvalue())


if __name__ == '__main__':
    unittest.main()
