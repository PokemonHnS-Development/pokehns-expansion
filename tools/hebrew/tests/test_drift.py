import os
import shutil
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import drift  # noqa: E402
from fixtures import CHARMAP, TOOLS, copy_data, token_cases  # noqa: E402

INC = 'data/maps/TestTown/scripts.inc'
ITEMS = 'src/data/items.h'
PARTY = 'src/data/partners.party'


class DriftTest(unittest.TestCase):
    """drift.check on a copy of tests/data/drift: an English tree (en) and its translation (he)."""

    def setUp(self):
        self.dir = copy_data('drift', tempfile.mkdtemp(prefix='hns_drift_test_'))
        self.en, self.he = os.path.join(self.dir, 'en'), os.path.join(self.dir, 'he')
        self.charmap = drift.load_charmap(os.path.dirname(CHARMAP))

    def tearDown(self):
        shutil.rmtree(self.dir, ignore_errors=True)

    def read(self, rel):
        with open(os.path.join(self.he, rel), encoding='utf-8') as f:
            return f.read()

    def write(self, root, rel, text):
        path = os.path.join(root, rel)
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, 'w', encoding='utf-8') as f:
            f.write(text)

    def edit(self, rel, old, new):
        text = self.read(rel)
        self.assertIn(old, text)
        self.write(self.he, rel, text.replace(old, new))

    def check(self, rel, strict=False):
        return drift.check(rel, self.en, self.he, self.charmap, strict)

    def test_only_strings_differ(self):
        for rel in (INC, ITEMS):
            self.assertEqual(self.check(rel), ([], []), rel)

    def test_changed_command(self):
        self.edit(INC, 'MSGBOX_NPC', 'MSGBOX_SIGN')
        errors, _ = self.check(INC)
        self.assertEqual(len(errors), 1, errors)
        self.assertTrue(errors[0].startswith('STRUCTURE changed outside strings'), errors)
        self.assertIn('MSGBOX_SIGN', errors[0])

    def test_tokens_terminator_charset(self):
        rel = 'data/maps/Cases/scripts.inc'
        en, he, expected = [], [], {}
        for i, (s_en, s_he, same, why) in enumerate(token_cases()):
            label = 'Cases_Text_%02d' % i
            en += [label + ':', '\t.string "%s"' % s_en, '']
            he += [label + ':', '\t.string "%s"' % s_he, '']
            if not same:
                expected[label] = {'TOKENS'}
        for label, s_en, s_he, kind in [('Cases_Text_NoEnd', 'Bye!$', 'ביי!', 'TERMINATOR'),
                                        ('Cases_Text_Euro', 'It costs 5 dollars.$', 'זה עולה 5 €.$', 'CHARSET')]:
            en += [label + ':', '\t.string "%s"' % s_en, '']
            he += [label + ':', '\t.string "%s"' % s_he, '']
            expected[label] = {kind}
        self.write(self.en, rel, '\n'.join(en))
        self.write(self.he, rel, '\n'.join(he))
        errors, _ = self.check(rel)
        found = {}
        for e in errors:
            kind, where = e.split()[:2]
            found.setdefault(where.rstrip(':'), set()).add(kind)
        self.assertEqual(found, expected)

    def test_a_kept_glyph_pair_in_a_translated_string(self):
        rel = 'data/maps/Glyphs/scripts.inc'
        cases = [('BALL {POKEBLOCK}$', 'כדור {POKEBLOCK}$', '{POKEBLOCK}'),
                 ('{POKE} BALL, {PKMN}, {ID}{NO}$', 'פוכדור, {PKMN} {ID}{NO}$', '{PKMN} {ID} {NO}'),
                 ('BALL {POKEBLOCK}$', 'כדור פוקיבלוק$', None),       # the Hebrew word replaces it
                 ('{PK}RS$', '{PK}RS$', None)]                        # untranslated: not this check
        en, he = [], []
        for i, (s_en, s_he, _) in enumerate(cases):
            en += ['Glyphs_Text_%d:' % i, '\t.string "%s"' % s_en, '']
            he += ['Glyphs_Text_%d:' % i, '\t.string "%s"' % s_he, '']
        self.write(self.en, rel, '\n'.join(en))
        self.write(self.he, rel, '\n'.join(he))
        errors, warnings = self.check(rel)
        self.assertEqual(errors, [])
        self.assertEqual([w for w in warnings if w.startswith('GLYPHPAIR')],
                         ['GLYPHPAIR Glyphs_Text_%d: %s' % (i, kept) for i, (_, _, kept) in enumerate(cases) if kept])
        # A warning only: --strict makes it an error.
        errors, _ = self.check(rel, strict=True)
        self.assertIn('GLYPHPAIR Glyphs_Text_0: {POKEBLOCK}', errors)

    def test_if_else_inside_a_description(self):
        self.assertEqual(self.check(ITEMS), ([], []))
        # Both branches collapsed into one: the #if/#else/#endif lines are structure.
        self.edit(ITEMS, '        #if I_HEALTH_RECOVERY >= GEN_7\n', '')
        self.edit(ITEMS, '        #else\n            "ב-50 נקודות."),\n        #endif\n', '')
        errors, _ = self.check(ITEMS)
        self.assertTrue(errors and all(e.startswith('STRUCTURE') for e in errors), errors)

    def test_party(self):
        translated = self.read(PARTY)
        self.edit(PARTY, 'Level: 42', 'Level: 43')
        errors, _ = self.check(PARTY)
        self.assertTrue(any(e.startswith('STRUCTURE') and 'Level: 43' in e for e in errors), errors)
        self.write(self.he, PARTY, translated)
        # A translated trainer name is a string, not structure.
        self.assertEqual(self.check(PARTY), ([], []))
        self.edit(PARTY, 'Name: סטיבן', 'Name: סטיבן€')
        errors, _ = self.check(PARTY)
        self.assertEqual(errors, ['CHARSET PARTNER_STEVEN: €'])
        self.write(self.he, PARTY, translated.replace('Name: סטיבן', 'Name: STEVEN'))
        errors, warnings = self.check(PARTY)
        self.assertEqual(errors, [])
        self.assertEqual([w.split()[0] for w in warnings], ['UNTRANSLATED'], warnings)

    def test_command_line(self):
        rel = 'data/maps/Latin/scripts.inc'
        n = 45
        self.write(self.en, rel, ''.join('Latin_Text_%02d:\n\t.string "Hello Bob!$"\n\n' % i for i in range(n)))
        self.write(self.he, rel, ''.join('Latin_Text_%02d:\n\t.string "שלום Bob!$"\n\n' % i for i in range(n)))
        shutil.copy(CHARMAP, os.path.join(self.he, 'charmap.txt'))

        def run(*args):
            return subprocess.run([sys.executable, os.path.join(TOOLS, 'drift.py'), '--en', self.en,
                                   '--tree', self.he] + list(args), capture_output=True, text=True)

        for quiet in ([], ['--quiet']):
            out = run(*quiet + [rel])
            self.assertEqual(out.returncode, 0, out.stderr)
            lines = out.stdout.splitlines()
            # A file with warnings only is listed even with --quiet, and no LATIN warning is cut.
            self.assertEqual(lines[0].split(), ['ok', rel])
            self.assertEqual(len([l for l in lines if l.startswith('   w LATIN Latin_Text_')]), n)
            # The last line counts the files, also with --quiet.
            self.assertEqual(lines[-1], 'drift: 1 file, 0 FAIL, 1 with warnings only')
        self.edit(INC, 'MSGBOX_NPC', 'MSGBOX_SIGN')
        out = run('--quiet', rel, INC, ITEMS)
        self.assertEqual(out.returncode, 1, out.stderr)
        lines = out.stdout.splitlines()
        self.assertEqual([l.split()[0] for l in lines if not l.startswith(' ')], ['ok', 'FAIL', 'drift:'])
        self.assertEqual(lines[-1], 'drift: 3 files, 1 FAIL, 1 with warnings only')


if __name__ == '__main__':
    unittest.main()
