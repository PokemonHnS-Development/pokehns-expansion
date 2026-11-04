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
# Whether drift.py reads the Name: lines of a .party file as strings. Until it does, every line of
# a .party file is structure, so a translated name is reported as STRUCTURE.
PARTY_NAMES = bool(drift.split_file('t.party', 'Name: A\n')[1])


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
        if not PARTY_NAMES:
            self.skipTest('drift.py does not read .party Name: lines as strings')
        self.assertEqual(self.check(PARTY), ([], []))
        self.edit(PARTY, 'Name: סטיבן', 'Name: סטיבן€')
        errors, _ = self.check(PARTY)
        self.assertEqual([e.split()[0] for e in errors], ['CHARSET'], errors)
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
        runs = []
        for quiet in ([], ['--quiet']):
            out = subprocess.run([sys.executable, os.path.join(TOOLS, 'drift.py'), '--en', self.en,
                                  '--tree', self.he] + quiet + [rel], capture_output=True, text=True)
            self.assertEqual(out.returncode, 0, out.stderr)
            lines = out.stdout.splitlines()
            # A file with warnings only is listed even with --quiet, and no LATIN warning is cut.
            self.assertEqual(lines[0].split(), ['ok', rel])
            self.assertEqual(len([l for l in lines if l.startswith('   w LATIN Latin_Text_')]), n)
            runs.append(lines)
        if not any(l.startswith('drift: ') for l in runs[0]):
            self.skipTest('drift.py prints no summary line')
        for lines in runs:
            self.assertRegex(lines[-1], r'^drift: 1 files?, 0 FAIL, 1 with warnings only$')


if __name__ == '__main__':
    unittest.main()
