import os
import subprocess
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import namecheck  # noqa: E402
from fixtures import CHARMAP, DATA, TOOLS  # noqa: E402


def row(kind, constant, hebrew, english=''):
    return {'kind': kind, 'constant': constant, 'english': english or constant, 'proposed_hebrew': hebrew}


class NameCheckTest(unittest.TestCase):
    """namecheck.py with the fixture charmap."""

    @classmethod
    def setUpClass(cls):
        cls.saved = namecheck.CHARMAP, namecheck.SINGLE, namecheck.TOKENS
        namecheck.CHARMAP = CHARMAP
        namecheck.SINGLE, namecheck.TOKENS = namecheck.load_charmap()

    @classmethod
    def tearDownClass(cls):
        namecheck.CHARMAP, namecheck.SINGLE, namecheck.TOKENS = cls.saved

    def test_encoded_length(self):
        self.assertEqual(namecheck.encoded_length('{PKMN}'), (2, []))
        self.assertEqual(namecheck.encoded_length('א'), (1, []))
        self.assertEqual(namecheck.encoded_length('מס\' {PLAYER}'), (6, []))
        self.assertEqual(namecheck.encoded_length('5€'), (1, ['€']))

    def test_check_rows(self):
        rows = [
            row('species', 'SPECIES_TWELVE', 'אבגדהוזחטיכא'),          # 12 letters: the limit
            row('species', 'SPECIES_THIRTEEN', 'אבגדהוזחטיכלא'),       # 13
            row('item', 'ITEM_OPEN_MEM', 'שלומ'),
            row('item', 'ITEM_FINAL_INSIDE', 'שםלו'),
            row('species', 'SPECIES_PRIMEAPE', 'פריימיפ'),             # final פ stays non-final
            row('item', 'ITEM_PP_UP', 'הגדלת נ”כ'),                  # acronym
            row('item', 'ITEM_EURO', 'מטבע €'),
        ]
        self.assertEqual(namecheck.check_rows(rows, 'g'), [
            'g species SPECIES_THIRTEEN: 13 bytes > 12: אבגדהוזחטיכלא',
            'g item ITEM_OPEN_MEM: non-final letter at word end: שלומ',
            'g item ITEM_FINAL_INSIDE: final letter inside a word: שםלו',
            "g item ITEM_EURO: unencodable '€' in מטבע €",
        ])

    def test_duplicates(self):
        self.assertEqual(namecheck.duplicates([row('move', 'MOVE_A', 'מכה', 'HIT'), row('move', 'MOVE_B', 'מכה', 'SLAP')]),
                         ['DUP move "מכה": MOVE_A / MOVE_B'])
        # Species may share a Hebrew name (forms), and one English name may have two constants.
        self.assertEqual(namecheck.duplicates([row('species', 'SPECIES_A', 'פיקאצ\'ו', 'PIKACHU'),
                                               row('species', 'SPECIES_B', 'פיקאצ\'ו', 'PIKACHU_COSPLAY')]), [])
        self.assertEqual(namecheck.duplicates([row('item', 'ITEM_A', 'כרטיס', 'PASS'),
                                               row('item', 'ITEM_B', 'כרטיס', 'PASS')]), [])

    def test_all_reports_a_hidden_row(self):
        env = dict(os.environ, HNS_GLOSSARY=os.path.join(DATA, 'namecheck', 'glossary.csv'),
                   HNS_FONTS_TREE=os.path.dirname(CHARMAP))
        out = subprocess.run([sys.executable, os.path.join(TOOLS, 'namecheck.py'), '--all'],
                             capture_output=True, text=True, env=env)
        self.assertEqual(out.returncode, 1, out.stderr)
        self.assertEqual(out.stdout.splitlines(), [
            'DUPKEY trainer_name TRNAME_: "???" and "{B_RIVAL_NAME}" share a key; only the last is checked',
            'rows 2, still empty 0, problems 1'])


if __name__ == '__main__':
    unittest.main()
