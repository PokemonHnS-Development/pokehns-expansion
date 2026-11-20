"""The Easy Chat word lists: no Latin, only the listed shared texts, the Hebrew order of the group
lists, a text of its own for every word the game compares, fixed phrases that fit their window, and
the Odd Egg interview's passwords and hint windows."""
import os
import re
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import gen_ec_letters  # noqa: E402
import gen_ec_order  # noqa: E402
import paths  # noqa: E402
import textwidth  # noqa: E402

TREE = paths.TREE
ENTRY = re.compile(r'\[EC_INDEX\(EC_WORD_(\w+)\)\]\s*=\s*\{\s*\.text\s*=\s*COMPOUND_STRING\("((?:[^"\\]|\\.)*)"\)'
                   r'\s*,\s*\.alphabeticalOrder\s*=\s*EC_INDEX\(EC_WORD_(\w+)\)\s*,\s*\.enabled\s*=\s*(\w+)')
HINT_WINDOWS = ['HELP_DAYCARE1_WINDOW', 'HELP_DAYCARE2_WINDOW', 'HELP_DAYCARE3_WINDOW', 'HELP_DAYCARE4_WINDOW']
# The phrases src/easy_chat.c compares word by word with the player's: the Odd Egg passwords, the
# questionnaire's Mystery Gift phrase and the Berry Master's wife's phrases.
COMPARED = ['sInterviewPasswords', 'sMysteryGiftPhrase', 'sBerryMasterWifePhrases']
# Fixed phrases the game builds from word lists: six-word speeches of the Frontier, tent, Trainer Hill
# and Pike trainers and the record-mix defaults, and the nine-word in-game trade mails and Kenya's mail.
SPEECH_FILES = [os.path.join('src', 'data', 'battle_frontier', 'battle_frontier_trainers.h'),
                os.path.join('src', 'data', 'battle_frontier', 'battle_tent.h'),
                os.path.join('src', 'data', 'battle_frontier', 'trainer_hill.h'),
                os.path.join('src', 'battle_pike.c'), os.path.join('src', 'battle_tower.c')]
MAIL_FILES = [os.path.join('src', 'data', 'trade.h'), os.path.join('src', 'scrcmd.c')]
TOKEN = r'(?:EC_WORD_\w+|EC_EMPTY_WORD|EC_POKEMON(?:_NATIONAL)?\(\w+\)|EC_MOVE2?\(\w+\))'
PHRASE = re.compile(r'\{\s*(' + TOKEN + r'(?:\s*,\s*' + TOKEN + r')+)\s*,?\s*\}')
# src/frontier_util.c FrontierSpeechToString: three words a line, two a line above this width
SPEECH_SWITCH_PX = 204
# Texts that several enabled words print on purpose, where Hebrew has one word for several English
# ones. Either word prints the same phrase, and no compared word is among them. Any other shared
# text fails, and so does a row that no longer matches the lists.
SHARED_TEXTS = {
    'אחר': {'OTHER', 'ELSE'},
    'אני': {'I', 'I_AM'},
    'אתה': {'YOU', 'YOU_RE'},
    'הוא': {'HE', 'IS'},
    'היי': {'HI', 'HEY'},
    'הם': {'THEY', 'ARE'},
    'זה': {'THIS', 'THAT_S', 'IT'},
    'טוב': {'GOOD', 'WELL'},
    'לא': {'NOT', 'NO', 'DON_T', 'AREN_T'},
    'מנצח': {'WINS', 'WINNER'},
}


def read(rel):
    with open(os.path.join(TREE, rel), encoding='utf-8') as f:
        return f.read()


def groups():
    """{group: [(word, text, alphabeticalOrder word, enabled)]} for the groups that hold text."""
    out = {}
    folder = os.path.join(TREE, 'src', 'data', 'easy_chat')
    for name in sorted(os.listdir(folder)):
        m = re.match(r'easy_chat_group_(\w+)\.h$', name)
        if m:
            entries = [(w, t, o, e == 'TRUE') for w, t, o, e in ENTRY.findall(read(os.path.join('src', 'data', 'easy_chat', name)))]
            if entries:
                out[m.group(1)] = entries
    return out


def table_rows(name):
    """The rows of a word table in src/easy_chat.c: the EC_WORD_ names of each {...} row."""
    text = read(os.path.join('src', 'easy_chat.c'))
    block = text[text.index(name + '['):]
    block = block[block.index('{') + 1:block.index('};')]
    rows = re.findall(r'\{([^}]*)\}', block) or [block]
    return [re.findall(r'EC_WORD_(\w+)', row) for row in rows]


def passwords():
    """sInterviewPasswords in src/easy_chat.c: one list of four words per egg."""
    return table_rows('sInterviewPasswords')


def hint_lines(window):
    """The description lines of one help window in src/data/help_window.h."""
    text = read(os.path.join('src', 'data', 'help_window.h'))
    block = text[text.index('[%s]' % window):]
    desc = block[block.index('.desc'):block.index('.headerFont')]
    joined = ''.join(re.findall(r'"((?:[^"\\]|\\.)*)"', desc))
    return joined.split('\\n')


class Lists(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.groups = groups()

    def test_only_the_listed_texts_are_shared(self):
        by_text = {}
        for group, entries in self.groups.items():
            for word, text, order, enabled in entries:
                if enabled:
                    by_text.setdefault(text, set()).add(word)
        shared = {t: ws for t, ws in by_text.items() if len(ws) > 1}
        for text, words in sorted(shared.items()):
            self.assertEqual(words, SHARED_TEXTS.get(text), '%s print %s' % (', '.join(sorted(words)), text))
        for text in SHARED_TEXTS:
            self.assertIn(text, shared, 'SHARED_TEXTS lists %s, which one word prints at most' % text)

    def test_every_compared_word_prints_a_text_no_other_word_prints(self):
        # The game tells these words apart by their ID, so the player must be able to tell them
        # apart by their text.
        words = {w: (t, e) for entries in self.groups.values() for w, t, o, e in entries}
        enabled = [(w, t) for w, (t, e) in words.items() if e]
        compared = sorted({w for name in COMPARED for row in table_rows(name) for w in row})
        self.assertGreater(len(compared), 38)
        for word in compared:
            text = words[word][0]
            others = [w for w, t in enabled if t == text and w != word]
            self.assertEqual(others, [], '%s prints %s, as %s do' % (word, text, others))

    def test_no_latin_letters_in_the_words(self):
        for group, entries in self.groups.items():
            for word, text, order, enabled in entries:
                self.assertIsNone(re.search('[A-Za-z]', text), '%s: %s' % (word, text))

    def test_hebrew_order_header_is_current(self):
        # src/easy_chat.c lists a group in this order under TEXT_RTL; gen_ec_order.py writes it.
        current, fresh = read(gen_ec_order.HEADER), gen_ec_order.render(TREE)
        if current != fresh:
            old, new = gen_ec_order.blocks(current), gen_ec_order.blocks(fresh)
            stale = sorted(g for g in set(old) | set(new) if old.get(g) != new.get(g)) or ['the comment or table']
            self.fail('%s is stale (%s); run tools/hebrew/gen_ec_order.py' % (gen_ec_order.HEADER, ', '.join(stale)))


def fixed_phrases(rel, n):
    """The brace lists of exactly N word tokens in a source file."""
    out = []
    for m in PHRASE.finditer(read(rel)):
        tokens = [t.strip() for t in m.group(1).split(',')]
        if len(tokens) == n:
            out.append(tokens)
    return out


def mail_lines():
    """(words per line, widest line in px) of the mail layout the game uses (src/mail.c): the
    'Tall' layouts in the 26-tile text window, text from wordsXPos of the layout."""
    text = read(os.path.join('src', 'mail.c'))
    lines = text[text.index('sLineLayouts_Tall[]'):]
    lines = [int(x) for x in re.findall(r'numEasyChatWords = (\d+)', lines[:lines.index('};')])]
    layouts = text[text.index('sMailLayouts_Tall[]'):]
    x = max(int(v) for v in re.findall(r'wordsXPos = (\d+)', layouts[:layouts.index('\n};')]))
    window = text[text.index('sWindowTemplates[]'):]
    width = int(re.search(r'\.width = (\d+)', window).group(1)) * 8
    return lines, width - x


class FixedPhrases(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        tree = TREE
        cls.words = gen_ec_letters.word_texts(tree)
        cls.species = gen_ec_letters.species_names(tree)
        cls.moves = gen_ec_letters.table_names(gen_ec_letters.read(tree, gen_ec_letters.MOVES),
                                               gen_ec_letters.MOVE_NAME)
        cls.model = textwidth.TextModel(tree=paths.FONTS_TREE)

    def lines(self, tokens, per_line):
        out, i = [], 0
        for n in per_line:
            texts = [gen_ec_letters.text_of(t, self.words, self.species, self.moves)
                     for t in tokens[i:i + n] if t != 'EC_EMPTY_WORD']
            out.append(' '.join(texts))
            i += n
        return out

    def test_speeches_keep_three_words_a_line(self):
        count = 0
        for rel in SPEECH_FILES:
            for tokens in fixed_phrases(rel, 6):
                count += 1
                for line in self.lines(tokens, [3, 3]):
                    self.assertLessEqual(self.model.width(line), SPEECH_SWITCH_PX, '%s: %s' % (rel, line))
        self.assertGreater(count, 1400)

    def test_mails_fit_their_window(self):
        per_line, px = mail_lines()
        self.assertEqual(sum(per_line), 9)
        count = 0
        for rel in MAIL_FILES:
            for tokens in fixed_phrases(rel, 9):
                count += 1
                for line in self.lines(tokens, per_line):
                    self.assertLessEqual(self.model.width(line), px, '%s: %s' % (rel, line))
        self.assertGreaterEqual(count, 5)


class OddEgg(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.words = {w: (t, e) for entries in groups().values() for w, t, o, e in entries}
        cls.passwords = passwords()

    def test_passwords_are_eleven_rows_of_four_words(self):
        self.assertEqual(len(self.passwords), 11)
        for row in self.passwords:
            self.assertEqual(len(row), 4, row)

    def test_each_hint_quotes_the_password_word_of_its_egg(self):
        # The four windows give the four words of the first seven eggs: window k, line i quotes
        # word k of password i.
        for k, window in enumerate(HINT_WINDOWS):
            lines = hint_lines(window)
            self.assertEqual(len(lines), 7, window)
            for i, line in enumerate(lines):
                quoted = re.findall(r'”([^”]*)”', line)
                want = self.words[self.passwords[i][k]][0]
                self.assertEqual(quoted, [want], '%s line %d: %s' % (window, i + 1, line))

    def test_hints_have_no_latin_letters(self):
        for window in HINT_WINDOWS:
            for line in hint_lines(window):
                self.assertIsNone(re.search('[A-Za-z]', line), '%s: %s' % (window, line))


if __name__ == '__main__':
    unittest.main()
