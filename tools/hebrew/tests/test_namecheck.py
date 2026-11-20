import os
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import namecheck  # noqa: E402
from fixtures import CHARMAP, DATA, TOOLS  # noqa: E402


def row(kind, constant, hebrew, english='', status='proposed'):
    return {'kind': kind, 'constant': constant, 'english': english or constant, 'proposed_hebrew': hebrew,
            'status': status}


def write(root, rel, text):
    path = os.path.join(root, rel)
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, 'w', encoding='utf-8') as fh:
        fh.write(text)


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

    def test_firered_names(self):
        with tempfile.TemporaryDirectory() as fr:
            write(fr, 'src/data/text/move_names.h',
                  '[MOVE_NONE] = _("-$$$$$$"),\n[MOVE_SONIC_BOOM] = _("בוםעל-קולי"),\n')
            write(fr, 'src/data/region_map/region_map_sections.json',
                  '{"map_sections": [{"map_section": "MAPSEC_ROUTE_12", "hebrew_name": "דרך 21"}]}')
            # FireRed pads with $ and writes digit runs reversed; both are undone. Missing files are skipped.
            self.assertEqual(namecheck.firered_names(fr), {
                ('move', 'MOVE_NONE'): '-', ('move', 'MOVE_SONIC_BOOM'): 'בוםעל-קולי',
                ('mapsec', 'MAPSEC_ROUTE_12'): 'דרך 12'})

    def test_fr_sync(self):
        fr = {('move', 'MOVE_SONIC_BOOM'): 'בוםעל-קולי', ('move', 'MOVE_PAY_DAY'): 'גשם מטבע',
              ('type', 'TYPE_GHOST'): 'רפאים'}
        rows = [row('move', 'MOVE_SONIC_BOOM', 'בום על-קולי'),      # differs only in spacing
                row('move', 'MOVE_PAY_DAY', 'לוטו'),
                row('type', 'TYPE_GHOST', 'רוח'),
                row('species', 'MOVE_PAY_DAY', 'לוטו')]              # another kind: not compared
        allow = {'type:TYPE_GHOST': {'hs': 'רוח', 'firered': 'רפאים', 'why': 'kept'}}
        used = set()
        self.assertEqual(namecheck.fr_sync(rows, fr, allow, used),
                         ['WARN FRSYNC move MOVE_PAY_DAY: H&S "לוטו", FireRed now "גשם מטבע"'])
        self.assertEqual(used, {('fr_sync', 'type:TYPE_GHOST')})
        # The entry pins FireRed's name: a later FireRed change warns again.
        fr[('type', 'TYPE_GHOST')] = 'רוח רפאים'
        self.assertEqual(len(namecheck.fr_sync(rows, fr, allow, set())), 2)

    def test_translit(self):
        rows = [row('species', 'SPECIES_X1', 'אקזגוטור', 'EXEGGUTOR'),    # X as קז: fine
                row('species', 'SPECIES_X2', 'אגוטור', 'EXEGGUTOR'),       # X lost
                row('species', 'SPECIES_X3', 'זרניאס', 'XERNEAS'),          # an initial X is /z/
                row('frontier_trainer', 'FT_MITCH', "מיץ'", 'MITCH'),      # final tsadi + geresh
                row('trade_ot', 'OT_KOBE', 'KOBE', 'KOBE'),
                row('trade_ot', 'OT_ROMAN', 'ROMAN', 'ROMAN', status='inherited'),   # not linted
                row('move', 'MOVE_X', 'ABC', 'X')]                                     # not a name kind
        allow = {'trade_ot:OT_KOBE': {'hebrew': 'KOBE', 'why': 'unreachable'}}
        used = set()
        self.assertEqual(namecheck.translit(rows, allow, used), [
            'WARN TRANSLIT species SPECIES_X2: EXEGGUTOR -> אגוטור (X without קס/קז/כס/גז)'])
        self.assertEqual(used, {('translit', 'trade_ot:OT_KOBE')})

    def test_same_name(self):
        rows = [row('trainer_name', 'TRNAME_LTSURGE', "סמל סרג'", 'LTSURGE'),
                row('frontier_trainer', 'FT_LTSURGE', "סרג'", 'LTSURGE'),
                row('trainer_name', 'TRNAME_ANN', 'אן', 'ANN'),
                row('hill_trainer', 'HT_ANN', 'אן', 'Ann'),
                row('species', 'SPECIES_ANN', 'אנה', 'ANN')]                 # not a person kind
        self.assertEqual(namecheck.same_name(rows, {}, set()),
                         ["WARN SAMENAME LTSURGE: סמל סרג' / סרג' (frontier_trainer, trainer_name)"])
        allow = {'LTSURGE': {'spellings': ["סרג'", "סמל סרג'"], 'why': 'short field'}}
        self.assertEqual(namecheck.same_name(rows, allow, set()), [])

    def test_warnings_report_stale_entries(self):
        allow = {'translit': {'trade_ot:OT_GONE': {'hebrew': 'X', 'why': 'gone'}}, 'dupes': {}}
        out, allowed = namecheck.warnings([], {'translit', 'dupes'}, allow)
        self.assertEqual(out, ['WARN STALE translit trade_ot:OT_GONE: allowlisted but no longer matches'])
        self.assertEqual(allowed, 0)
        out, _ = namecheck.warnings([], {'fr_sync'}, {}, fr=None)
        self.assertEqual(out, ['WARN FRSYNC skipped: no FireRed tree (set HNS_FIRERED)'])

    def test_committed_allowlist_is_well_formed(self):
        allow = namecheck.load_allow()
        for check, fields in (('fr_sync', {'hs', 'firered', 'why'}), ('translit', {'hebrew', 'why'}),
                              ('dupes', {'spellings', 'why'})):
            for key, entry in allow[check].items():
                self.assertEqual(set(entry), fields, key)
                self.assertTrue(entry['why'], key)


if __name__ == '__main__':
    unittest.main()
