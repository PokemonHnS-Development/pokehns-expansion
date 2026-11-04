import json
import os
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import audit  # noqa: E402
from fixtures import TempTree, TOOLS  # noqa: E402


def run_audit(tree, *extra):
    out = subprocess.run([sys.executable, os.path.join(TOOLS, 'audit.py'), '--tree', tree, '--fonts-tree', tree,
                          '--hebrew-widths', 'table', '--json', '-'] + list(extra),
                         capture_output=True, text=True)
    return out.returncode, json.loads(out.stdout), out.stderr


def by_key(findings):
    out = {}
    for f in findings:
        out.setdefault(f['key'].split(':', 1)[1], []).append(f)
    return out


class CppTest(unittest.TestCase):
    def test_eval(self):
        self.assertTrue(audit.cpp_eval('IS_HNS'))
        self.assertFalse(audit.cpp_eval('IS_FRLG'))
        self.assertTrue(audit.cpp_eval('IS_FRLG || IS_HNS'))
        self.assertFalse(audit.cpp_eval('!IS_HNS'))
        self.assertTrue(audit.cpp_eval('defined(BUGFIX) && I_COMBINE_BAG_POCKETS == TRUE'))
        self.assertFalse(audit.cpp_eval('SOMETHING_UNKNOWN'))

    def test_state(self):
        c = audit.CppState()
        seen = []
        for line in ['#if IS_FRLG', 'a', '#elif IS_HNS', 'b', '#else', 'c', '#endif', 'd',
                     '#ifndef BUGFIX', 'e', '#else', 'f', '#endif']:
            if line.startswith('#'):
                c.feed(line)
            elif c.compiled():
                seen.append(line)
        self.assertEqual(seen, ['b', 'd', 'f'])


class AuditTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.he_tmp, cls.en_tmp = TempTree(hebrew=True), TempTree(hebrew=False)
        cls.he, cls.en = cls.he_tmp.__enter__(), cls.en_tmp.__enter__()

    @classmethod
    def tearDownClass(cls):
        cls.he_tmp.__exit__(None, None, None)
        cls.en_tmp.__exit__(None, None, None)

    def test_hebrew_findings(self):
        rc, d, err = run_audit(self.he)
        self.assertEqual(rc, 1, err)
        f = by_key(d['findings'])
        codes = {k: sorted({x['code'] for x in v}) for k, v in f.items()}
        self.assertEqual(codes.get('TestTown_Text_TooWide'), ['WIDTH'])
        self.assertEqual(codes.get('TestTown_Text_ThreeRows'), ['LINES'])
        self.assertIn('TERMINATOR', codes.get('TestTown_Text_NoTerminator', []))
        self.assertNotIn('TestTown_Text_Conditional', codes)            # #ifdef branch not glued to #else
        self.assertNotIn('TestTown_Text_Fine', codes)
        self.assertIn('BYTES', codes.get('gItemsInfo[ITEM_LONGNAME].name', []))
        wide = f['TestTown_Text_TooWide'][0]
        self.assertEqual((wide['value'], wide['limit'], wide['lang']), (36 * 8 + 5 * 3, 208, 'he'))
        # English text in the Hebrew tree is reported apart and does not fail the run by itself
        en = by_key(d['english_findings'])
        self.assertIn('TestTown_Text_StillEnglish', en)
        kinds = d['meta']['strings_by_kind']
        self.assertEqual(kinds.get('battle_trainer_text'), 1)
        self.assertEqual(kinds.get('item_description'), 1)

    def test_english_tree_is_baseline_only(self):
        rc, d, err = run_audit(self.en)
        self.assertEqual(rc, 0, err)
        self.assertEqual(d['findings'], [])
        en = by_key(d['english_findings'])
        self.assertIn('TestTown_Text_TooWide', en)

    def test_baseline_suppresses_inherited_overflow(self):
        rc, d, err = run_audit(self.he, '--baseline', self.en)
        f = by_key(d['findings'])
        sup = by_key(d['suppressed'])
        self.assertIn('TestTown_Text_Baseline', sup)                    # he over 25 <= en over 41
        self.assertNotIn('TestTown_Text_Baseline', f)
        self.assertIn('TestTown_Text_TooWide', f)                       # he over 95 > en over 59
        self.assertEqual(sup['TestTown_Text_Baseline'][0]['baseline_over'], 41)

    def test_readable_report(self):
        out = subprocess.run([sys.executable, os.path.join(TOOLS, 'audit.py'), '--tree', self.he, '--fonts-tree',
                              self.he, '--hebrew-widths', 'table'], capture_output=True, text=True)
        self.assertIn('== translated strings:', out.stdout)
        self.assertIn('TestTown_Text_TooWide', out.stdout)
        self.assertEqual(out.returncode, 1)

    def test_report_file(self):
        with tempfile.TemporaryDirectory(prefix='hns_audit_report_') as d:
            report = os.path.join(d, 'not', 'yet', 'audit.txt')
            out = subprocess.run([sys.executable, os.path.join(TOOLS, 'audit.py'), '--tree', self.he, '--fonts-tree',
                                  self.he, '--hebrew-widths', 'table', '--report', report],
                                 capture_output=True, text=True)
            self.assertEqual(out.returncode, 1, out.stderr)
            with open(report, encoding='utf-8') as f:
                text = f.read()
        # The folder was created; the file has the whole report, stdout only its summary lines.
        self.assertIn('TestTown_Text_TooWide', text)
        summary = [l for l in text.splitlines() if l.startswith('== ')]
        self.assertEqual(len(summary), 2)
        self.assertEqual(out.stdout.splitlines(), summary)


if __name__ == '__main__':
    unittest.main()
