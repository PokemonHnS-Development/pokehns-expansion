import os
import re
import shutil
import subprocess
import sys
import tempfile
import unittest

HERE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TOOL = os.path.join(HERE, 'gen_ec_letters.py')
sys.path.insert(0, HERE)
import gen_ec_letters  # noqa: E402
import paths  # noqa: E402

ENGLISH = '''#include "easy_chat.h"

#define DOUBLE_SPECIES_NAME EC_EMPTY_WORD, 2,

const u16 gEasyChatWordsByLetter_Others[] = {
    EC_WORD_EXCL,
};

const u16 gEasyChatWordsByLetter_A[] = {
    DOUBLE_SPECIES_NAME
    EC_POKEMON(ABRA),
    EC_POKEMON_NATIONAL(ABRA),
    EC_WORD_APPLE,
};

const u16 gEasyChatWordsByLetter_F[] = {
    EC_MOVE(FLY),
    EC_WORD_FLYING,
};

const u16 gEasyChatWordsByLetter_P[] = {
    DOUBLE_SPECIES_NAME
    EC_WORD_PSYCHIC,
    EC_MOVE(PSYCHIC),
};

const u16 gEasyChatWordsByLetter_U[] = {
    EC_POKEMON_NATIONAL(UNOWN),
};

const u16 gEasyChatWordsByLetter_UnusedJapaneseHi[] = {
    EC_WORD_UNUSED,
};
'''

GROUP = '''const struct EasyChatWordInfo gEasyChatGroup_Misc[] = {
    [EC_INDEX(EC_WORD_EXCL)] =
    {
        .text = COMPOUND_STRING("!"),
    },
    [EC_INDEX(EC_WORD_APPLE)] =
    {
        .text = COMPOUND_STRING("%s"),
    },
    [EC_INDEX(EC_WORD_FLYING)] =
    {
        .text = COMPOUND_STRING("תעופה"),
    },
    [EC_INDEX(EC_WORD_PSYCHIC)] =
    {
        .text = COMPOUND_STRING("פסיכי"),
    },
};
'''

SPECIES = '''#define UNOWN_INFO(letter)    \\
    {                             \\
        .speciesName = _("אנון"), \\
    }

const struct SpeciesInfo gSpeciesInfoGen1[] =
{
    [SPECIES_ABRA_REAL] =
    {
        .speciesName = _("אברה"),
    },
    [SPECIES_UNOWN] = UNOWN_INFO(A),
};
'''

MOVES = '''const struct MoveInfo gMovesInfo[] =
{
    [MOVE_FLY] =
    {
        .name = COMPOUND_STRING("תעופה"),
    },
    [MOVE_PSYCHIC] =
    {
        .name = COMPOUND_STRING("אשליה"),
    },
};
'''


class GenEcLetters(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.mkdtemp()
        self.write('src/data/easy_chat/easy_chat_words_by_letter.h', ENGLISH)
        self.write_group('בננה')
        self.write('src/data/pokemon/species_info/gen_1_families.h', SPECIES)
        self.write('src/data/moves_info.h', MOVES)
        self.write('include/constants/species.h', '#define SPECIES_ABRA SPECIES_ABRA_REAL\n')

    def tearDown(self):
        shutil.rmtree(self.tmp)

    def write(self, rel, text):
        path = os.path.join(self.tmp, rel)
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, 'w', encoding='utf-8') as f:
            f.write(text)

    def write_group(self, apple):
        self.write('src/data/easy_chat/easy_chat_group_misc.h', GROUP % apple)

    def run_tool(self, *args):
        return subprocess.run([sys.executable, TOOL, '--tree', self.tmp] + list(args), capture_output=True, text=True)

    def header(self):
        with open(os.path.join(self.tmp, gen_ec_letters.HEADER), encoding='utf-8') as f:
            return f.read()

    def lists(self):
        tokens = re.compile(r'DOUBLE_SPECIES_NAME|EC_EMPTY_WORD, \d+|EC_\w+\(\w+\)|EC_WORD_\w+')
        return {k: ' '.join(tokens.findall(v)) for k, v in gen_ec_letters.blocks(self.header()).items()}

    def test_files_each_entry_under_the_initial_of_its_text(self):
        r = self.run_tool()
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        lists = self.lists()
        self.assertEqual(lists['Others'], 'EC_WORD_EXCL')
        # the species pair stays one entry (its name through the SPECIES_ABRA alias); UNOWN's name
        # comes from its macro; the English pair PSYCHIC prints two texts, so the move (an alef
        # word) and the word (a pe word) are filed apart
        self.assertEqual(lists['Alef'], 'DOUBLE_SPECIES_NAME EC_POKEMON(ABRA) EC_POKEMON_NATIONAL(ABRA) '
                                        'EC_POKEMON_NATIONAL(UNOWN) EC_MOVE(PSYCHIC)')
        self.assertEqual(lists['Bet'], 'EC_WORD_APPLE')
        self.assertEqual(lists['Pe'], 'EC_WORD_PSYCHIC')
        self.assertEqual(len(gen_ec_letters.blocks(self.header())), 23)
        self.assertNotIn('UNUSED', self.header())

    def test_entries_with_the_same_text_are_one_item_word_first(self):
        self.run_tool()
        self.assertEqual(self.lists()['Tav'], 'DOUBLE_SPECIES_NAME EC_WORD_FLYING EC_MOVE(FLY)')

    def test_table_and_size_checks(self):
        self.run_tool()
        text = self.header()
        self.assertEqual(text.count('.words = sEasyChatWordsByLetterRtl_'), 23)
        self.assertIn('STATIC_ASSERT(3 <= EC_MAX_WORDS_IN_GROUP, EasyChatWordsByLetterRtlFit);', text)
        self.assertIn('STATIC_ASSERT(23 <= EC_NUM_ALPHABET_GROUPS, EasyChatWordsByLetterRtlCount);', text)
        self.assertFalse(re.search(r'[^\x00-\x7f]', text), 'the header must hold no Hebrew text')

    def test_check_passes_when_current_and_fails_when_a_word_changes(self):
        self.run_tool()
        r = self.run_tool('--check')
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        self.write_group('גזר')
        r = self.run_tool('--check')
        self.assertEqual(r.returncode, 1, r.stdout)
        self.assertIn('Bet: list differs', r.stdout)
        self.assertIn('Gimel: list differs', r.stdout)

    def test_check_fails_when_the_header_is_missing(self):
        r = self.run_tool('--check')
        self.assertEqual(r.returncode, 1)
        self.assertIn('missing', r.stdout)

    def test_a_missing_name_is_an_error(self):
        self.write('src/data/moves_info.h', MOVES.replace('MOVE_FLY', 'MOVE_SURF'))
        r = self.run_tool()
        self.assertEqual(r.returncode, 2)
        self.assertIn('no text for EC_MOVE(FLY)', r.stdout)


class RealTree(unittest.TestCase):
    """The tree's header keeps every entry of the English lists exactly once."""

    def test_same_entries_as_the_english_lists(self):
        def entries(text):
            return sorted(re.findall(r'EC_\w+\(\w+\)|EC_WORD_\w+', text))
        rtl = os.path.join(paths.TREE, gen_ec_letters.HEADER)
        if not os.path.exists(rtl):
            self.skipTest('no %s in this tree' % gen_ec_letters.HEADER)
        with open(rtl, encoding='utf-8') as f:
            got = entries(''.join(gen_ec_letters.blocks(f.read()).values()))
        english = [t for e in gen_ec_letters.english_entries(paths.TREE) for t in e]
        self.assertEqual(got, sorted(english))


if __name__ == '__main__':
    unittest.main()
