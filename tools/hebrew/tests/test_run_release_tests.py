import json
import os
import shutil
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from fixtures import TOOLS  # noqa: E402

SCRIPT = os.path.join(TOOLS, 'release', 'run_release_tests.sh')
LADDER = ['ladder1_newgame', 'ladder2_badge1', 'ladder3_ecruteak', 'ladder4_league', 'ladder5_kanto',
          'ladder6_postgame']


@unittest.skipUnless(shutil.which('bash'), 'needs bash')
class CheckInputsTest(unittest.TestCase):
    """run_release_tests.sh --check lists every missing input before it runs anything. These tests
    look only at its lines about tour saves and unit batches; the other inputs are missing here."""

    def setUp(self):
        self.dir = tempfile.mkdtemp(prefix='hns_release_check_')
        for rel in ('rc', 'units', 'saves'):
            os.makedirs(self.path(rel))
        self.write('emu/tours/a.txt', '# a tour\n\nstart saves/base_a.sav\nscreenshot\n')
        self.write('emu/tours/b.txt', 'start saves/ladder1_newgame.sav   # a ladder save\n')
        self.write('emu/tours/c.txt', 'start save:x\n')
        self.write('emu/tours/d.txt', 'start empty\nstart saves/not_first.sav\n')
        self.write('emu/tours/e.txt', 'start saves/r3/base.sav\n')
        self.write('emu/tours/_include.txt', 'start saves/include_only.sav\n')
        self.write('emu/tours/old/f.txt', 'start saves/subfolder_only.sav\n')
        for n in LADDER + ['r3/base']:
            self.write('saves/%s.sav' % n, '')
        self.write('data/inventory.json', json.dumps([{'file': 'a.c', 'batch': 'B01'}, {'file': 'b.c', 'batch': 'B02'},
                                                      {'file': 'c.c', 'batch': 'B01'}, {'file': 'd.c'}]))
        self.write('units/B01/B01_01.json', '{}')

    def tearDown(self):
        shutil.rmtree(self.dir, ignore_errors=True)

    def path(self, rel):
        return os.path.join(self.dir, rel)

    def write(self, rel, text):
        os.makedirs(os.path.dirname(self.path(rel)), exist_ok=True)
        with open(self.path(rel), 'w', encoding='utf-8') as f:
            f.write(text)

    def check(self, **env):
        base = {'HNS_EMU': self.path('emu'), 'HNS_SAVES': self.path('saves'), 'HNS_UNITS': self.path('units'),
                'HNS_DATA': self.path('data'), 'HNS_RELEASE_WORKTREE': self.path('none/worktree'),
                'HNS_RUNNER': self.path('none/hnsrun'), 'HNS_EN_ROM': self.path('none/en.gba'),
                'HNS_CORES': self.path('none'), 'HNS_MGBA_CORE': self.path('none/mgba.dylib'),
                'HNS_WORK': self.path('work'), 'DEVKITARM': self.path('none')}
        base.update(env)
        out = subprocess.run(['bash', SCRIPT, '--check', self.path('rc')], capture_output=True, text=True,
                             env=dict(os.environ, **base))
        self.assertEqual(out.returncode, 2, out.stderr)
        return [l for l in out.stderr.splitlines() if 'HNS_SAVES' in l or 'batch' in l or 'unit chunks' in l]

    def test_tour_saves_and_batches(self):
        # Only the first command of a tour counts, '_' files and subfolders are not tours, and a
        # ladder save is reported once, as part of the ladder.
        self.assertEqual(self.check(), [
            'run_release_tests.sh: missing %s (a screen tour starts from it, HNS_SAVES)' % self.path('saves/base_a.sav'),
            'run_release_tests.sh: no folder %s for batch B02 of %s (python3 tools/hebrew/make_chunks.py all)'
            % (self.path('units/B02'), self.path('data/inventory.json'))])
        os.remove(self.path('saves/ladder1_newgame.sav'))
        self.write('saves/base_a.sav', '')
        os.makedirs(self.path('units/B02'))
        self.assertEqual(self.check(), [
            'run_release_tests.sh: missing %s (the save ladder, HNS_SAVES)' % self.path('saves/ladder1_newgame.sav')])

    def test_no_units_or_inventory(self):
        self.assertEqual(self.check(HNS_DATA=self.path('none')),
                         ['run_release_tests.sh: missing %s (a screen tour starts from it, HNS_SAVES)'
                          % self.path('saves/base_a.sav'),
                          'run_release_tests.sh: cannot read the batches of %s (HNS_DATA)'
                          % self.path('none/inventory.json')])
        shutil.rmtree(self.path('units/B01'))
        lines = self.check()
        self.assertEqual(lines[-1], 'run_release_tests.sh: no unit chunks in %s (python3 tools/hebrew/make_chunks.py '
                                    'all; or set HNS_UNITS)' % self.path('units'))


if __name__ == '__main__':
    unittest.main()
