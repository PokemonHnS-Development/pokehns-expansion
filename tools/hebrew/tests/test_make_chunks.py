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


def run_make_chunks(out, size, *args, data=os.path.join(FIXTURE, 'data')):
    """Runs make_chunks.py ARGS (default BX) on tests/data/make_chunks; returns the finished process."""
    env = dict(os.environ, HNS_BASELINE=os.path.join(FIXTURE, 'baseline'), HNS_DATA=data,
               HNS_GLOSSARY=os.path.join(FIXTURE, 'translation', 'glossary.csv'))
    run = subprocess.run([sys.executable, '-B', os.path.join(TOOLS, 'make_chunks.py')] + list(args or ['BX']) +
                         ['--out', out, '--size', str(size)], capture_output=True, text=True, env=env)
    if run.returncode:
        raise AssertionError(run.stderr)
    return run


def read_chunks(out, batch='BX'):
    chunks = {}
    for path in sorted(glob.glob(os.path.join(out, batch, '*.json'))):
        with open(path, encoding='utf-8') as f:
            chunks[os.path.basename(path)] = json.load(f)
    return chunks


def make_chunks(out, size):
    """Runs make_chunks.py BX on tests/data/make_chunks; returns (stdout, {chunk file name: content})."""
    return run_make_chunks(out, size).stdout, read_chunks(out)


def plant(out, rel, text='{"units": []}'):
    path = os.path.join(out, rel)
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w', encoding='utf-8') as f:
        f.write(text)


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



class OldChunksTest(unittest.TestCase):
    """A run rewrites each batch it names: the batch's chunk files from an earlier run go first, as
    the sweep reads every file in the folder. Nothing else is removed."""

    def setUp(self):
        self.dir = tempfile.mkdtemp(prefix='hns_chunks_old_')
        self.out = os.path.join(self.dir, 'units')

    def tearDown(self):
        shutil.rmtree(self.dir, ignore_errors=True)

    def files(self):
        return sorted(os.path.relpath(os.path.join(dp, f), self.out)
                      for dp, dn, fn in os.walk(self.out) for f in fn)

    def test_a_stale_chunk_file_is_removed(self):
        _, fresh = make_chunks(os.path.join(self.dir, 'fresh'), 2)
        # An earlier run cut BX into more chunks and a supplement; other files are not its own.
        for rel in ('BX/BX_04.json', 'BX/BX_s01.json', 'BX/BX_snames.json', 'BX/BX_01.json'):
            plant(self.out, rel)
        for rel in ('BX/notes.txt', 'BX/CHUNK.json', 'BX/BX_04.json.bak', 'BX/BX_01_old.json',
                    'BX/BY_01.json', 'BY/BY_01.json', 'top.json'):
            plant(self.out, rel, '"keep"')
        run = run_make_chunks(self.out, 2)
        self.assertEqual(self.files(), ['BX/BX_01.json', 'BX/BX_01_old.json', 'BX/BX_02.json', 'BX/BX_03.json',
                                        'BX/BX_04.json.bak', 'BX/BX_names.json', 'BX/BY_01.json', 'BX/CHUNK.json',
                                        'BX/notes.txt', 'BY/BY_01.json', 'top.json'])
        self.assertEqual({k: v for k, v in read_chunks(self.out).items() if k in fresh}, fresh)
        self.assertIn('BX: removed 3 chunk file(s) of an earlier run that this run does not write: '
                      'BX_04.json, BX_s01.json, BX_snames.json', run.stdout)
        for rel in ('BX/notes.txt', 'BX/CHUNK.json', 'BY/BY_01.json'):
            with open(os.path.join(self.out, rel), encoding='utf-8') as f:
                self.assertEqual(f.read(), '"keep"')

    def test_a_rerun_reports_nothing_removed(self):
        first = run_make_chunks(self.out, 2).stdout
        second = run_make_chunks(self.out, 2).stdout
        self.assertEqual(second, first)
        self.assertNotIn('removed', second)

    def test_supplement_removes_nothing(self):
        run_make_chunks(self.out, 2)
        plant(self.out, 'BX/BX_09.json')
        before = self.files()
        run_make_chunks(self.out, 2, 'BX', '--supplement')
        self.assertEqual(self.files(), before)          # every unit is in a file already: nothing new

    def test_all_warns_about_a_batch_the_inventory_has_no_longer(self):
        data = os.path.join(self.dir, 'data')
        os.makedirs(data)
        with open(os.path.join(FIXTURE, 'data', 'inventory.json'), encoding='utf-8') as f:
            inv = [i for i in json.load(f) if i['batch'] == 'BX']
        with open(os.path.join(data, 'inventory.json'), 'w', encoding='utf-8') as f:
            json.dump(inv, f)
        plant(self.out, 'BZ/BZ_01.json')
        plant(self.out, 'misc/notes.json')
        run = run_make_chunks(self.out, 2, 'all', data=data)
        self.assertIn('%s holds chunk files of BZ' % os.path.join(self.out, 'BZ'), run.stderr)
        self.assertNotIn('misc', run.stderr)
        self.assertIn('BZ/BZ_01.json', self.files())   # a warning only


if __name__ == '__main__':
    unittest.main()
