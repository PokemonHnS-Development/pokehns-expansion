#!/usr/bin/env python3
"""Generate src/data/easy_chat/easy_chat_words_by_letter_rtl.h: the lists of the Easy Chat alphabet
keyboard by Hebrew letter.

  gen_ec_letters.py [--tree TREE] [--check]      TREE defaults to HNS_TREE; the header is rewritten there

The alphabet keyboard of the Easy Chat screen opens a list of every word that starts with the
chosen letter. Upstream files the words under their English initial (A-Z and Others, in
src/data/easy_chat/easy_chat_words_by_letter.h). Under TEXT_RTL, src/easy_chat.c includes this
header instead: 23 lists, Others and then the 22 letters alef to tav, which the Hebrew keyboard
shows.

The words are exactly the entries of the English lists (the unused Japanese lists left out), so
the keyboard offers the same words, each still checked for being unlocked. A species that is in
both Pokemon groups stays one DOUBLE_SPECIES_NAME pair. Each entry is filed by the first character
of the text the game prints for it: the word text of its group file, the species name
(.speciesName in src/data/pokemon/species_info/) or the move name (.name in src/data/moves_info.h).
A final form counts as its base letter; an entry whose text does not start with a Hebrew letter
goes to Others. Each list is sorted like the group lists (gen_ec_order.py): by gen_dex_alpha.py's
key, then by the text and the entry.

The header has no Hebrew text, only word constants. The same file serves the engine branch
(he/renderer, English texts), where the TEXT_RTL keyboard then files each English word under the
initial of its Hebrew text, as the Pokedex A-Z order there follows the Hebrew names. After a word,
species or move name changes on he/main, run this again and pick the regenerated header onto
he/renderer.

The screen copies a list into a buffer of EC_MAX_WORDS_IN_GROUP words (struct
EasyChatScreenWordData, include/easy_chat.h); the header ends with a STATIC_ASSERT that the
longest list fits, so a word move that overflows it fails the build.

--check writes nothing. It regenerates the header in memory and compares it with the file: exit 0
when they are equal, exit 1 when the file is missing or stale (each list that differs is named).
"""
import argparse, os, re, sys

import paths
from gen_dex_alpha import ORDER, FINAL, key as hebrew_key

HEADER = os.path.join('src', 'data', 'easy_chat', 'easy_chat_words_by_letter_rtl.h')
ENGLISH = os.path.join('src', 'data', 'easy_chat', 'easy_chat_words_by_letter.h')
SPECIES_DIR = os.path.join('src', 'data', 'pokemon', 'species_info')
MOVES = os.path.join('src', 'data', 'moves_info.h')
SPECIES_CONSTANTS = os.path.join('include', 'constants', 'species.h')

# The list names, Others and then the letters in alphabetical order (the CHAR_HEB_* names).
LETTER_NAMES = ['Alef', 'Bet', 'Gimel', 'Dalet', 'He', 'Vav', 'Zayin', 'Het', 'Tet', 'Yod', 'Kaf',
                'Lamed', 'Mem', 'Nun', 'Samekh', 'Ayin', 'Pe', 'Tsadi', 'Qof', 'Resh', 'Shin', 'Tav']
LISTS = ['Others'] + LETTER_NAMES
assert len(LETTER_NAMES) == len(ORDER)

ENGLISH_LIST = re.compile(r'const u16 gEasyChatWordsByLetter_(Others|[A-Z])\[\] = \{\n(.*?)\};', re.S)
TOKEN = re.compile(r'DOUBLE_SPECIES_NAME|EC_\w+\(\w+\)|EC_WORD_\w+')
WORD = re.compile(r'\[EC_INDEX\((EC_WORD_\w+)\)\]\s*=\s*\{\s*\.text\s*=\s*COMPOUND_STRING\("((?:[^"\\]|\\.)*)"\)')
SPECIES_NAME = re.compile(r'\.speciesName\s*=\s*_\("((?:[^"\\]|\\.)*)"\)')
MOVE_NAME = re.compile(r'\.name\s*=\s*COMPOUND_STRING\("((?:[^"\\]|\\.)*)"\)')
ENTRY_KEY = re.compile(r'^\s*\[(SPECIES_\w+|MOVE_\w+)\]\s*=\s*(\w+\()?', re.M)


class GenError(Exception):
    pass


def unescape(s):
    return re.sub(r'\\(.)', r'\1', s)


def read(tree, rel):
    with open(os.path.join(tree, rel), encoding='utf-8') as f:
        return f.read()


def english_entries(tree):
    """The entries of the English lists in file order: ('EC_WORD_X',) for one entry, a pair of
    tokens for a DOUBLE_SPECIES_NAME pair."""
    text = read(tree, ENGLISH)
    entries = []
    for _, body in ENGLISH_LIST.findall(text):
        tokens = TOKEN.findall(body)
        i = 0
        while i < len(tokens):
            if tokens[i] == 'DOUBLE_SPECIES_NAME':
                entries.append(tuple(tokens[i + 1:i + 3]))
                i += 3
            else:
                entries.append((tokens[i],))
                i += 1
    if not entries:
        raise GenError('no lists in %s' % ENGLISH)
    seen = set()
    for e in entries:
        for t in e:
            if t in seen:
                raise GenError('%s is listed twice in %s' % (t, ENGLISH))
            seen.add(t)
    return entries


def word_texts(tree):
    folder = os.path.join(tree, 'src', 'data', 'easy_chat')
    texts = {}
    for name in sorted(os.listdir(folder)):
        if re.match(r'easy_chat_group_\w+\.h$', name):
            for const, text in WORD.findall(read(tree, os.path.join('src', 'data', 'easy_chat', name))):
                texts[const] = unescape(text)
    return texts


def macro_names(text, field):
    """{macro: name} for the function-like macros whose body sets the field (UNOWN_MISC_INFO)."""
    out = {}
    for m in re.finditer(r'^#define\s+(\w+)\(.*?(?<!\\)\n', text, re.M | re.S):
        n = field.search(m.group(0))
        if n:
            out[m.group(1)] = unescape(n.group(1))
    return out


def table_names(text, field):
    """{SPECIES_X or MOVE_X: name} from a designated-initializer table. An entry's name is the first
    field after its [KEY] =, or the field in the body of the macro it is built with. A key that is
    defined twice with different names is an error."""
    macros = macro_names(text, field)
    keys = list(ENTRY_KEY.finditer(text))
    out = {}
    for i, k in enumerate(keys):
        end = keys[i + 1].start() if i + 1 < len(keys) else len(text)
        name = None
        if k.group(2) and k.group(2)[:-1] in macros:
            name = macros[k.group(2)[:-1]]
        else:
            m = field.search(text, k.end(), end)
            if m:
                name = unescape(m.group(1))
        if name is None:
            continue
        if out.get(k.group(1), name) != name:
            raise GenError('%s has two names: %s, %s' % (k.group(1), out[k.group(1)], name))
        out[k.group(1)] = name
    return out


def species_names(tree):
    """{SPECIES_X: name}, with the aliases of include/constants/species.h (SPECIES_CASTFORM is
    SPECIES_CASTFORM_NORMAL) resolved."""
    out = {}
    folder = os.path.join(tree, SPECIES_DIR)
    for name in sorted(os.listdir(folder)):
        if name.endswith('.h'):
            out.update(table_names(read(tree, os.path.join(SPECIES_DIR, name)), SPECIES_NAME))
    aliases = dict(re.findall(r'^#define\s+(SPECIES_\w+)\s+(SPECIES_\w+)\s*$', read(tree, SPECIES_CONSTANTS), re.M))
    for alias in aliases:
        target = alias
        while target in aliases:
            target = aliases[target]
        if alias not in out and target in out:
            out[alias] = out[target]
    return out


def text_of(token, words, species, moves):
    m = re.match(r'EC_(POKEMON|POKEMON_NATIONAL|MOVE|MOVE2)\((\w+)\)$', token)
    if not m:
        table, name = words, token
    elif m.group(1).startswith('POKEMON'):
        table, name = species, 'SPECIES_' + m.group(2)
    else:
        table, name = moves, 'MOVE_' + m.group(2)
    if name not in table:
        raise GenError('no text for %s (%s)' % (token, name))
    return table[name]


def letter_of(text):
    """The list index: 1-22 for the Hebrew letter the text starts with, 0 (Others) otherwise."""
    ch = FINAL.get(text[:1], text[:1])
    return ORDER.index(ch) + 1 if ch and ch in ORDER else 0


KIND_RANK = {'EC_WORD': 0, 'EC_POKEMON': 1, 'EC_POKEMON_NATIONAL': 2, 'EC_MOVE': 3, 'EC_MOVE2': 4}


def kind(token):
    return token.split('(')[0] if '(' in token else 'EC_WORD'


def build(tree):
    """[(list name, [(entries, text)] sorted)] for Others and the 22 letters. Entries that print the
    same text are one item, plain words first, then the two Pokemon groups, then the two move
    groups, each in the order of the English file."""
    words, species = word_texts(tree), species_names(tree)
    moves = table_names(read(tree, MOVES), MOVE_NAME)
    tokens = [t for entry in english_entries(tree) for t in entry]
    by_text = {}
    for pos, t in enumerate(tokens):
        by_text.setdefault(text_of(t, words, species, moves), []).append((KIND_RANK[kind(t)], pos, t))
    lists = [[] for _ in LISTS]
    for text, members in by_text.items():
        lists[letter_of(text)].append((tuple(t for _, _, t in sorted(members)), text))
    for items in lists:
        items.sort(key=lambda et: (hebrew_key(et[1]), et[1], et[0]))
    return list(zip(LISTS, lists))


def render(tree):
    built = build(tree)
    parts = ['// The Easy Chat alphabet keyboard\'s lists by Hebrew letter, used under TEXT_RTL\n'
             '// (src/easy_chat.c): Others, then the letters alef to tav. Generated by\n'
             '// tools/hebrew/gen_ec_letters.py from the word texts and the species and move names;\n'
             '// run it again after changing one of them.\n'
             '//\n'
             '// Entries that print the same text follow EC_EMPTY_WORD and their number\n'
             '// (DOUBLE_SPECIES_NAME for two); the list offers the first of them that is unlocked\n'
             '// (SetUnlockedWordsByAlphabet).\n\n'
             '#define DOUBLE_SPECIES_NAME EC_EMPTY_WORD, 2,\n\n']
    longest = 0
    for name, items in built:
        longest = max(longest, len(items))
        parts.append('static const u16 sEasyChatWordsByLetterRtl_%s[] = {\n' % name)
        for entry, _ in items:
            if len(entry) == 2:
                parts.append('    DOUBLE_SPECIES_NAME\n')
            elif len(entry) > 2:
                parts.append('    EC_EMPTY_WORD, %d,\n' % len(entry))
            parts.extend('    %s,\n' % t for t in entry)
        parts.append('};\n\n')
    parts.append('// The keyboard uses the first %d alphabet groups; the others stay empty.\n'
                 'const struct EasyChatWordsByLetter gEasyChatWordsByLetterPointers[EC_NUM_ALPHABET_GROUPS] = {\n'
                 % len(built))
    for name, _ in built:
        parts.append('    {\n        .words = sEasyChatWordsByLetterRtl_%s,\n'
                     '        .numWords = ARRAY_COUNT(sEasyChatWordsByLetterRtl_%s),\n    },\n' % (name, name))
    parts.append('};\n\n')
    parts.append('// The longest list offers %d words; the screen copies a list into a buffer of\n'
                 '// EC_MAX_WORDS_IN_GROUP words.\n'
                 'STATIC_ASSERT(%d <= EC_MAX_WORDS_IN_GROUP, EasyChatWordsByLetterRtlFit);\n'
                 'STATIC_ASSERT(%d <= EC_NUM_ALPHABET_GROUPS, EasyChatWordsByLetterRtlCount);\n'
                 % (longest, longest, len(built)))
    return ''.join(parts)


def blocks(text):
    return dict(re.findall(r'static const u16 sEasyChatWordsByLetterRtl_(\w+)\[\] = \{\n(.*?)\};', text, re.S))


def summary(tree):
    return ', '.join('%s %d' % (name, len(items)) for name, items in build(tree))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--tree', default=paths.TREE)
    ap.add_argument('--check', action='store_true',
                    help='compare the header with a fresh generation; exit 1 if it is missing or stale')
    ap.add_argument('--summary', action='store_true', help='print the number of entries of each list')
    a = ap.parse_args()
    path = os.path.join(a.tree, HEADER)
    try:
        new = render(a.tree)
        if a.summary:
            print(summary(a.tree))
    except GenError as e:
        print('gen_ec_letters: %s' % e)
        sys.exit(2)
    if a.check:
        if not os.path.exists(path):
            print('gen_ec_letters: %s is missing; run gen_ec_letters.py' % HEADER)
            sys.exit(1)
        with open(path, encoding='utf-8') as f:
            old = f.read()
        if old == new:
            print('gen_ec_letters: %d lists, the header is up to date' % len(blocks(new)))
            return
        ob, nb = blocks(old), blocks(new)
        for g in LISTS:
            if ob.get(g) != nb.get(g):
                print('  %s: list differs' % g)
        if ob == nb:
            print('  the table or the size checks differ')
        print('gen_ec_letters: %s is stale; run gen_ec_letters.py and commit it' % HEADER)
        sys.exit(1)
    with open(path, 'w', encoding='utf-8') as f:
        f.write(new)
    print('wrote %s: %d lists' % (HEADER, len(blocks(new))))


if __name__ == '__main__':
    main()
