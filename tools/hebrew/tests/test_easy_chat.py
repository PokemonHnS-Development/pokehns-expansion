"""The Easy Chat word lists against the Odd Egg interview: its passwords and its hint windows."""
import os
import re
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import paths  # noqa: E402

TREE = paths.TREE
ENTRY = re.compile(r'\[EC_INDEX\(EC_WORD_(\w+)\)\]\s*=\s*\{\s*\.text\s*=\s*COMPOUND_STRING\("((?:[^"\\]|\\.)*)"\)'
                   r'\s*,\s*\.alphabeticalOrder\s*=\s*EC_INDEX\(EC_WORD_(\w+)\)\s*,\s*\.enabled\s*=\s*(\w+)')
HINT_WINDOWS = ['HELP_DAYCARE1_WINDOW', 'HELP_DAYCARE2_WINDOW', 'HELP_DAYCARE3_WINDOW', 'HELP_DAYCARE4_WINDOW']


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


def passwords():
    """sInterviewPasswords in src/easy_chat.c: one list of four words per egg."""
    text = read(os.path.join('src', 'easy_chat.c'))
    block = text[text.index('sInterviewPasswords'):]
    block = block[block.index('{') + 1:block.index('};')]
    return [re.findall(r'EC_WORD_(\w+)', row) for row in re.findall(r'\{([^}]*)\}', block)]


def hint_lines(window):
    """The description lines of one help window in src/data/help_window.h."""
    text = read(os.path.join('src', 'data', 'help_window.h'))
    block = text[text.index('[%s]' % window):]
    desc = block[block.index('.desc'):block.index('.headerFont')]
    joined = ''.join(re.findall(r'"((?:[^"\\]|\\.)*)"', desc))
    return joined.split('\\n')


class OddEgg(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.words = {w: (t, e) for entries in groups().values() for w, t, o, e in entries}
        cls.passwords = passwords()

    def test_passwords_are_eleven_rows_of_four_words(self):
        self.assertEqual(len(self.passwords), 11)
        for row in self.passwords:
            self.assertEqual(len(row), 4, row)

    def test_every_password_word_prints_a_text_no_other_word_prints(self):
        enabled = [(w, t) for w, (t, e) in self.words.items() if e]
        for word in sorted({w for row in self.passwords for w in row}):
            text = self.words[word][0]
            others = [w for w, t in enabled if t == text and w != word]
            self.assertEqual(others, [], '%s prints %s, as %s do' % (word, text, others))

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
