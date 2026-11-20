"""Small synthetic trees for the tool tests (written to a temp dir; nothing here touches a real tree).

Fonts tree: tests/fixtures/charmap.txt (a copy of he/fonts charmap.txt) plus a src/fonts.c holding the
nine Latin width tables with round numbers:
  space 3; every other byte 6 (normal, short, small), 5 (narrow, small_narrow, short_narrow),
  4 (narrower, small_narrower, short_narrower); Hebrew letters 7 / 6 / 5, and 'ש' one wider
  (8 / 7 / 6) so the widest glyph is unambiguous.
"""
import json
import os
import shutil
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
TOOLS = os.path.dirname(HERE)
CHARMAP = os.path.join(HERE, 'fixtures', 'charmap.txt')
DATA = os.path.join(HERE, 'data')     # small committed fixture trees, one folder per tool

TABLES = {
    'gFontSmallLatinGlyphWidths': 6, 'gFontNormalLatinGlyphWidths': 6, 'gFontShortLatinGlyphWidths': 6,
    'gFontNarrowLatinGlyphWidths': 5, 'gFontSmallNarrowLatinGlyphWidths': 5, 'gFontShortNarrowLatinGlyphWidths': 5,
    'gFontNarrowerLatinGlyphWidths': 4, 'gFontSmallNarrowerLatinGlyphWidths': 4,
    'gFontShortNarrowerLatinGlyphWidths': 4,
}
HEBREW = list(range(0x3A, 0x51)) + [0x5E, 0x5F, 0x60, 0x61]
SHIN = 0x4E


def width_of(table, b):
    base = TABLES[table]
    if b == 0x00:
        return 3
    if b == SHIN:
        return base + 2
    if b in HEBREW:
        return base + 1
    return base


def write(root, rel, text):
    p = os.path.join(root, rel)
    os.makedirs(os.path.dirname(p), exist_ok=True)
    with open(p, 'w', encoding='utf-8') as f:
        f.write(text)
    return p


def make_fonts_tree(root):
    shutil.copy(CHARMAP, os.path.join(root, 'charmap.txt'))
    parts = []
    for name in TABLES:
        vals = ', '.join(str(width_of(name, b)) for b in range(512))
        parts.append('ALIGNED(4) const u8 %s[] = {\n    %s\n};\n' % (name, vals))
    write(root, 'src/fonts.c', '\n'.join(parts))
    return root


BATTLE_MESSAGE_C = r'''
static const u8 sText_FoePkmnPrefix[] = _("The opposing ");
static const u8 sText_WildPkmnPrefix[] = _("The wild ");
static const u8 sText_FoePkmnPrefixLower[] = _("the opposing ");
static const u8 sText_WildPkmnPrefixLower[] = _("the wild ");
const u8 gText_WhatWillPkmnDo[] = _("What will\n{B_BUFF1} do?");
const u8 *const gBattleStringsTable[] =
{
    [STRINGID_TEST1] = COMPOUND_STRING("{B_ATK_NAME_WITH_PREFIX} used\n{B_CURRENT_MOVE}!"),
    [STRINGID_TEST2] = COMPOUND_STRING("%s"),
};
'''


def make_tree(root, hebrew=True):
    """A tiny game tree. hebrew=False gives the 'English' version of the same keys."""
    make_fonts_tree(root)
    h = hebrew
    write(root, 'src/battle_message.c', BATTLE_MESSAGE_C % (
        'אבגדה אבגדה אבגדה אבגדה אבגדה אבגדה אבגדה\\nאבגדה!' if h else 'Words words words words words\\nwords!'))
    long_line = ('שששששש ' * 6).strip() if h else 'This line is far too long for the dialogue box ok'
    write(root, 'data/maps/TestTown/scripts.inc', '\n'.join([
        'TestTown_EventScript_Npc::',
        '\tmsgbox TestTown_Text_Fine, MSGBOX_NPC',
        '\tend',
        '',
        'TestTown_Text_Fine:',
        '\t.string "%s\\n"' % ('שלום {PLAYER}!' if h else 'Hello {PLAYER}!'),
        '\t.string "%s$"' % ('מה שלומך?' if h else 'How are you?'),
        '',
        'TestTown_Text_TooWide:',
        '\t.string "%s$"' % long_line,
        '',
        'TestTown_Text_ThreeRows:',
        '\t.string "%s\\n"' % ('א' if h else 'A'),
        '\t.string "%s\\n"' % ('ב' if h else 'B'),
        '\t.string "%s$"' % ('ג' if h else 'C'),
        '',
        'TestTown_Text_NoTerminator:',
        '\t.string "%s"' % ('בלי סוף' if h else 'No end'),
        '',
        'TestTown_Text_Conditional:',
        '#ifdef BUGFIX',
        '\t.string "%s\\p"' % ('א' if h else 'A'),
        '#else',
        '\t.string "%s\\p"' % ('ב' if h else 'B'),
        '#endif',
        '\t.string "%s$"' % ('סוף' if h else 'End'),
        '',
        'TestTown_Text_Baseline:',          # he: 28*8+3*3 = 233 (over 17); en: 40*6+3*3 = 249 (over 33)
        '\t.string "%s$"' % (('ששששששש ' * 4).strip() if h else ('WWWWWWWWWW ' * 4).strip()),
        '',
        'TestTown_Text_StillEnglish:',
        '\t.string "This one was not translated, and it is much too long$"',
        '',
    ]) + '\n')
    write(root, 'data/maps/TestTown/trainers.inc', '\n'.join([
        'TestTown_EventScript_Trainer::',
        '\ttrainerbattle_single TRAINER_TEST, TestTown_Text_Intro, TestTown_Text_Defeat',
        '\tend',
        'TestTown_Text_Defeat:',
        '\t.string "%s$"' % ('הפסדתי!' if h else 'I lost!'),
        '',
    ]) + '\n')
    write(root, 'src/data/items.h', '\n'.join([
        'const struct Item gItemsInfo[] =',
        '{',
        '    [ITEM_POTION] =',
        '    {',
        '        .name = ITEM_NAME("%s"),' % ('שיקוי' if h else 'POTION'),
        '        .description = COMPOUND_STRING("%s"),' % (
            'שיקוי שמחזיר\\nעשרים נקודות\\nחיים.' if h else 'Restores the HP\\nof a POKéMON\\nby 20 points.'),
        '    },',
        '    [ITEM_LONGNAME] =',
        '    {',
        '        .name = ITEM_NAME("%s"),' % ('אבגדהוזחטיכלמנסעפצקר' if h else 'ABCDEFGHIJKLMNOPQRST'),
        '    },',
        '};',
    ]) + '\n')
    return root


class TempTree(object):
    def __init__(self, hebrew=True, kind='tree'):
        self.dir = tempfile.mkdtemp(prefix='hns_tools_test_')
        if kind == 'fonts':
            make_fonts_tree(self.dir)
        else:
            make_tree(self.dir, hebrew)

    def __enter__(self):
        return self.dir

    def __exit__(self, *exc):
        shutil.rmtree(self.dir, ignore_errors=True)


def copy_data(name, dest):
    """Copies tests/data/NAME into the folder DEST (created if needed) and returns DEST."""
    shutil.copytree(os.path.join(DATA, name), dest, dirs_exist_ok=True)
    return dest


def token_cases():
    """[(english, hebrew, same, why)]: the token-rule table that drift, units and checkunits share."""
    with open(os.path.join(DATA, 'token_cases.json'), encoding='utf-8') as f:
        return [(c['en'], c['he'], c['same'], c['why']) for c in json.load(f)]
