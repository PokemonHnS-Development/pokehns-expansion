import json
import os
import shutil
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from fixtures import TOOLS  # noqa: E402

SCRIPT = os.path.join(TOOLS, 'release', 'make_testing_md.py')
COMMIT = '0123456789abcdef0123456789abcdef01234567'
OTHER = 'fedcba9876543210fedcba9876543210fedcba98'
CORES = ('vbam', 'vba_next', 'gpsp', 'mednafen_gba', 'skyemu')
ROMNAME = 'pokehns-he-2.0.6-test.gba'
NOTES = {
    'release': 'test', 'upstream_version': '2.0.6', 'branch': 'he/main', 'toolchain': 'devkitARM',
    'static_checks': '0 failures', 'visual_review': 'every changed frame looked at',
    'crosscore_notes': 'All cores agree.',
    'map_walk': {'held_reason': 'a scripted sequence', 'hebrew_only_held': [], 'hebrew_only_reason': ''},
    'known_issues_intro': '', 'known_issues': ['none'], 'not_tested': ['real hardware'],
}


class VisualFindingsTest(unittest.TestCase):
    """A candidate folder whose every other input passes, so only visual_findings.json decides."""

    def setUp(self):
        self.dir = tempfile.mkdtemp(prefix='hns_testing_md_')
        rom = {'size': 33554432, 'sha1': '0' * 40, 'crc32': '00000000'}
        self.write('rc/build_info.json', json.dumps({'commit': COMMIT, 'ref': COMMIT[:10], 'pokehns.gba': rom,
                                                     'pokehns-clip.gba': rom}))
        self.write('rc/gbafix.log', 'gbafix: header already valid\n')
        self.write('rc/make_check.log', '')
        self.write('rc/tests/tours/tour_report.json', json.dumps({'tours': {'menu': {'status': 'OK', 'shots': 2}}}))
        self.write('rc/tests/tours_clip/tour_report.json',
                   json.dumps({'tours': {'menu': {'status': 'OK', 'clipped': 0}}}))
        self.write('rc/tests/sweep/sweep.json', json.dumps({'summary': {'OK': 3, 'SKIP': 0}}))
        self.write('rc/tests/selfcheck.log', 'all checks passed\n')
        self.write('rc/tests/mapwalk/mapwalk.json', json.dumps([{'map': 'MAP_A', 'status': 'OK'}]))
        self.write('rc/tests/crosscore.txt', 'shot' + ''.join('%14s' % c for c in CORES) + '\n'
                   + 'boot' + ''.join('%14d' % 0 for _ in CORES) + '\n')
        self.write('rc/tests/ladder_ladder1_newgame.log', 'continue\nexit 0\n')
        self.write('rc/tests/ladder/ladder1_newgame/a.png', '')
        self.write('en_mapwalk.json', json.dumps([{'map': 'MAP_A', 'status': 'OK'}]))
        self.notes(NOTES)

    def tearDown(self):
        shutil.rmtree(self.dir, ignore_errors=True)

    def path(self, rel):
        return os.path.join(self.dir, rel)

    def write(self, rel, text):
        os.makedirs(os.path.dirname(self.path(rel)), exist_ok=True)
        with open(self.path(rel), 'w', encoding='utf-8') as f:
            f.write(text)

    def notes(self, notes):
        self.write('notes.json', json.dumps(notes))

    def run_md(self, findings=None):
        """Runs make_testing_md.py with FINDINGS (JSON data, or a str written as is) as
        visual_findings.json; None leaves the file out."""
        if findings is not None:
            self.write('rc/visual_findings.json', findings if isinstance(findings, str) else json.dumps(findings))
        return subprocess.run([sys.executable, SCRIPT, self.path('rc'), ROMNAME, self.path('TESTING.md'),
                               '--notes', self.path('notes.json')], capture_output=True, text=True,
                              env=dict(os.environ, HNS_EN_MAPWALK=self.path('en_mapwalk.json')))

    def report(self):
        with open(self.path('TESTING.md'), encoding='utf-8') as f:
            return f.read()

    def assertRefused(self, out, *words):
        self.assertEqual(out.returncode, 1, out.stdout + out.stderr)
        self.assertNotIn('Traceback', out.stderr)
        self.assertIn('visual_findings.json', out.stderr)
        for w in words:
            self.assertIn(w, out.stderr)
        self.assertFalse(os.path.exists(self.path('TESTING.md')))

    def test_no_file_no_row(self):
        out = self.run_md()
        self.assertEqual(out.returncode, 0, out.stderr)
        self.assertNotIn('| Visual review |', self.report())

    def test_this_candidates_review_gives_the_row(self):
        for findings in ([], [{'shot': 'menu_pc_boot_02', 'outcome': 'intended'}]):
            out = self.run_md({'commit': COMMIT, 'findings': findings})
            self.assertEqual(out.returncode, 0, out.stderr)
            self.assertIn('| Visual review |', self.report())
            self.assertIn(NOTES['visual_review'], self.report())
            os.remove(self.path('TESTING.md'))

    def test_bare_list_is_refused(self):
        # the format of every candidate before this check: a list with no commit
        self.assertRefused(self.run_md([{'shot': 'battle_catch_dexpage', 'kind': 'numbers'}]), 'earlier candidate')

    def test_other_commit_is_refused(self):
        self.assertRefused(self.run_md({'commit': OTHER, 'findings': []}), OTHER, COMMIT, 'earlier candidate')
        self.assertRefused(self.run_md({'commit': COMMIT[:10], 'findings': []}), COMMIT)

    def test_malformed_file_is_refused(self):
        for findings in ('{"commit": ', '', {'findings': []}, {'commit': COMMIT}, {'commit': 1, 'findings': []},
                         {'commit': COMMIT, 'findings': {}}, {'commit': COMMIT, 'findings': ['menu_01']},
                         {'commit': COMMIT, 'findings': [], 'reviewed': 12}, 'null'):
            with self.subTest(findings=findings):
                self.assertRefused(self.run_md(findings))

    def test_review_without_notes_text_is_refused(self):
        self.notes(dict(NOTES, visual_review=''))
        self.assertRefused(self.run_md({'commit': COMMIT, 'findings': []}), 'visual_review')


if __name__ == '__main__':
    unittest.main()
