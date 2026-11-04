import os
import shutil
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import gen_dex_alpha  # noqa: E402

TOOL = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'gen_dex_alpha.py')

GLOSSARY = '''kind,constant,english,firered_hebrew,proposed_hebrew,status,notes
species,SPECIES_ABRA,ABRA,,אברה,inherited,
species,SPECIES_BULBASAUR,BULBASAUR,,בולבזאור,inherited,
species,SPECIES_ZUBAT,ZUBAT,,זובאט,inherited,
species,SPECIES_GOLBAT,GOLBAT,,גולבאט,inherited,
'''

ENGLISH = ['ABRA', 'BULBASAUR', 'GOLBAT', 'ZUBAT']


def header(hebrew=None):
    body = ''.join('    NATIONAL_DEX_%s,\n' % e for e in ENGLISH)
    alpha = body if hebrew is None else (
        '#if TEXT_RTL\n    // generated\n' + ''.join('    NATIONAL_DEX_%s,\n' % e for e in hebrew)
        + '#else\n' + body + '#endif\n')
    return ('const u16 gPokedexOrder_Alphabetical[] =\n{\n' + alpha + '};\n\n'
            'const u16 gPokedexOrder_Weight[] =\n{\n    NATIONAL_DEX_ZUBAT,\n};\n')


class Check(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.mkdtemp()
        os.makedirs(os.path.join(self.tmp, 'src', 'data', 'pokemon'))
        self.glossary = os.path.join(self.tmp, 'glossary.csv')
        with open(self.glossary, 'w', encoding='utf-8') as f:
            f.write(GLOSSARY)

    def tearDown(self):
        shutil.rmtree(self.tmp)

    def write(self, text):
        with open(os.path.join(self.tmp, 'src', 'data', 'pokemon', 'pokedex_orders.h'), 'w', encoding='utf-8') as f:
            f.write(text)

    def run_tool(self, *args):
        env = dict(os.environ, HNS_GLOSSARY=self.glossary)
        return subprocess.run([sys.executable, TOOL, '--tree', self.tmp] + list(args),
                              capture_output=True, text=True, env=env)

    def test_up_to_date_header_passes(self):
        self.write(header(['ABRA', 'BULBASAUR', 'GOLBAT', 'ZUBAT']))
        r = self.run_tool('--check')
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        self.assertIn('up to date', r.stdout)

    def test_stale_header_fails_and_names_the_moved_entry(self):
        self.write(header(['ABRA', 'BULBASAUR', 'ZUBAT', 'GOLBAT']))
        r = self.run_tool('--check')
        self.assertEqual(r.returncode, 1, r.stdout + r.stderr)
        self.assertIn('1 entries move', r.stdout)
        self.assertRegex(r.stdout, r'(GOLBAT|ZUBAT) +index')

    def test_header_without_hebrew_list_fails(self):
        self.write(header())
        self.assertEqual(self.run_tool('--check').returncode, 1)

    def test_check_writes_nothing_and_write_makes_check_pass(self):
        stale = header(['ZUBAT', 'ABRA', 'BULBASAUR', 'GOLBAT'])
        self.write(stale)
        self.run_tool('--check')
        with open(os.path.join(self.tmp, 'src', 'data', 'pokemon', 'pokedex_orders.h'), encoding='utf-8') as f:
            self.assertEqual(f.read(), stale)
        self.assertEqual(self.run_tool().returncode, 0)
        self.assertEqual(self.run_tool('--check').returncode, 0)


class Moved(unittest.TestCase):
    def test_entries_that_only_shift_are_not_listed(self):
        old = ['A', 'X', 'B', 'C', 'D']
        new = ['A', 'B', 'C', 'X', 'D']
        self.assertEqual(gen_dex_alpha.moved_entries(old, new), [('X', 1, 3)])

    def test_added_and_removed_entries(self):
        self.assertEqual(gen_dex_alpha.moved_entries(['A', 'B'], ['A', 'C']), [('C', None, 1), ('B', 1, None)])


if __name__ == '__main__':
    unittest.main()
