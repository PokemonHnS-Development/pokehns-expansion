import glob
import json
import os
import shutil
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from fixtures import DATA, TOOLS  # noqa: E402

FIXTURE = os.path.join(DATA, 'make_chunks')
INC = 'data/maps/TestTown/scripts.inc'
SPECIES = 'src/data/pokemon/species_info/gen_1_families.h'


def make_chunks(out, size):
    """Runs make_chunks.py BX on tests/data/make_chunks; returns (stdout, {chunk file name: content})."""
    env = dict(os.environ, HNS_BASELINE=os.path.join(FIXTURE, 'baseline'), HNS_DATA=os.path.join(FIXTURE, 'data'),
               HNS_GLOSSARY=os.path.join(FIXTURE, 'translation', 'glossary.csv'))
    run = subprocess.run([sys.executable, os.path.join(TOOLS, 'make_chunks.py'), 'BX', '--out', out,
                          '--size', str(size)], capture_output=True, text=True, env=env)
    if run.returncode:
        raise AssertionError(run.stderr)
    chunks = {}
    for path in sorted(glob.glob(os.path.join(out, 'BX', '*.json'))):
        with open(path, encoding='utf-8') as f:
            chunks[os.path.basename(path)] = json.load(f)
    return run.stdout, chunks


class MakeChunksTest(unittest.TestCase):
    """make_chunks.py BX on a baseline with a map script, a species file and an Easy Chat file."""

    @classmethod
    def setUpClass(cls):
        cls.dir = tempfile.mkdtemp(prefix='hns_chunks_test_')
        cls.out2, cls.chunks2 = make_chunks(os.path.join(cls.dir, 'size2'), 2)
        cls.out5, cls.chunks5 = make_chunks(os.path.join(cls.dir, 'size5'), 5)

    @classmethod
    def tearDownClass(cls):
        shutil.rmtree(cls.dir, ignore_errors=True)

    def test_names_file(self):
        names = self.chunks2['BX_names.json']
        self.assertEqual([(u['file'], u['field'], u['en'], u['he'], u['fixed']) for u in names],
                         [(SPECIES, 'speciesName', 'PIKACHU', "פיקאצ'ו", 'species SPECIES_PIKACHU')])
        numbered = [u['id'] for name, c in self.chunks2.items() if name != 'BX_names.json' for u in c['units']]
        self.assertNotIn(names[0]['id'], numbered)
        self.assertEqual(self.out2.strip(), 'BX: 2 files, 6 units (1 names pre-filled), 3 chunks')

    def test_chunks(self):
        chunks = [c for name, c in sorted(self.chunks2.items()) if name != 'BX_names.json']
        self.assertEqual([c['chunk'] for c in chunks], ['BX_01', 'BX_02', 'BX_03'])
        self.assertEqual([[u['key'] for u in c['units']] for c in chunks], [
            ['TestTown_Text_Frontier', 'TestTown_Text_Hello'], ['TestTown_Text_Pass', 'TestTown_Text_Bye'],
            ['SPECIES_PIKACHU.description']])
        for c in chunks:
            self.assertEqual(c['files'], sorted({u['file'] for u in c['units']}))
            self.assertTrue(all(u['he'] == '' and not u.get('fixed') for u in c['units']))
        # The Easy Chat words stay English: no unit, no file.
        every = [u['file'] for c in self.chunks2.values() for u in (c['units'] if isinstance(c, dict) else c)]
        self.assertFalse([f for f in every if f.startswith('src/data/easy_chat/')])
        # A new file starts a new chunk once the current one is 70% full: 4 of 5 here.
        self.assertEqual([[u['file'] for u in c['units']] for name, c in sorted(self.chunks5.items())
                          if name != 'BX_names.json'], [[INC] * 4, [SPECIES]])

    def test_glossary_names_in_a_chunk(self):
        names = {c['chunk']: c['names'] for name, c in self.chunks2.items() if name != 'BX_names.json'}
        # FRONTIER PASS, and not the PASS inside it; a capitalised PASS on its own; lowercase "pass" is
        # an English word, not the item.
        self.assertEqual(names, {'BX_01': {'FRONTIER PASS': 'כרטיס חזית הקרב'},
                                 'BX_02': {'PASS': 'כרטיס רכבת'},
                                 'BX_03': {}})


if __name__ == '__main__':
    unittest.main()
