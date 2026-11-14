import contextlib
import io
import json
import os
import shutil
import sys
import tempfile
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(HERE), 'emu'))
import sweep  # noqa: E402


def unit(label, he=None, live=True):
    u = {'key': label, 'kind': 'script', 'file': 'data/maps/Town/scripts.inc', 'en': 'Hello.', 'live': live}
    if he is not None:
        u['he'] = he
    return u


class SelectLabelsTest(unittest.TestCase):
    """sweep.py list/run --translated keeps the units that hold a Hebrew text. Units fresh from
    make_chunks.py hold none, so the option would select nothing without a word: it stops instead
    and points at --hebrew-only, which reads the Hebrew of the ROM."""

    def setUp(self):
        self.dir = tempfile.mkdtemp(prefix='hns_sweep_select_')

    def tearDown(self):
        shutil.rmtree(self.dir, ignore_errors=True)

    def units(self, items):
        os.makedirs(os.path.join(self.dir, 'B01'))
        with open(os.path.join(self.dir, 'B01', 'B01_01.json'), 'w', encoding='utf-8') as fh:
            json.dump({'units': items}, fh, ensure_ascii=False)

    def run_list(self, *args):
        out, err = io.StringIO(), io.StringIO()
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
            try:
                rc = sweep.main(['list', '--units', self.dir] + list(args))
            except SystemExit as e:
                rc = e.code
        return rc, out.getvalue().splitlines(), err.getvalue()

    def test_translated_without_hebrew_units_exits_2(self):
        self.units([unit('Town_Text_A'), unit('Town_Text_B', he='')])
        rc, out, err = self.run_list('--translated')
        self.assertEqual(rc, 2)
        self.assertEqual(out, [])
        self.assertIn('no unit has Hebrew; use --hebrew-only', err)

    def test_translated_explicit_labels_without_hebrew_units_exits_2(self):
        self.units([unit('Town_Text_A')])
        rc, _, err = self.run_list('--translated', '--label', 'Town_Text_A')
        self.assertEqual(rc, 2)
        self.assertIn('no unit has Hebrew; use --hebrew-only', err)

    def test_translated_keeps_hebrew_units(self):
        self.units([unit('Town_Text_A'), unit('Town_Text_B', he='שלום.')])
        rc, out, err = self.run_list('--translated')
        self.assertEqual((rc, err), (0, ''))
        self.assertEqual(out, ['Town_Text_B\tdata/maps/Town/scripts.inc'])

    def test_translated_filter_that_matches_nothing_is_not_an_error(self):
        # Hebrew units exist; the other filters leave none of them: an empty selection, exit 0.
        self.units([unit('Town_Text_A'), unit('Town_Text_B', he='שלום.')])
        rc, out, err = self.run_list('--translated', '--match', 'Text_A$')
        self.assertEqual((rc, out, err), (0, [], ''))

    def test_without_translated_untranslated_units_are_listed(self):
        self.units([unit('Town_Text_A'), unit('Town_Text_B')])
        rc, out, err = self.run_list()
        self.assertEqual((rc, err), (0, ''))
        self.assertEqual([l.split('\t')[0] for l in out], ['Town_Text_A', 'Town_Text_B'])


if __name__ == '__main__':
    unittest.main()
