import io
import json
import os
import shutil
import struct
import sys
import tempfile
import unittest
from contextlib import redirect_stdout, redirect_stderr

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import flag_gates  # noqa: E402
import paths  # noqa: E402

FLAGS_H = '''#define FLAG_ENABLE_A                0
#define FLAG_ENABLE_B                0x247
#define FLAG_REGISTERED_C            FLAG_ENABLE_A
#define FLAG_HIDE_REPORTER           0
#define FLAG_SYS_TV_START            0 // the TV never starts
#define FLAG_EXTENDED                (HNS_EXTENDED_CONTENT_START + 9)
'''

MATCH_CALL_C = '''#define ALWAYS_AVAILABLE 0xFFFF
#define NO_FLAG_TO_SET   0xFFFF

#if IS_HNS
static const match_call_text_data_t sATextScripts[] = {
    { MatchCall_Text_A1, ALWAYS_AVAILABLE, NO_FLAG_TO_SET },
    { MatchCall_Text_Shared, FLAG_ENABLE_A, NO_FLAG_TO_SET },
    { NULL, ALWAYS_AVAILABLE, NO_FLAG_TO_SET }
};
static const struct MatchCallStructNPC sAMatchCallHeader = {
    .flag = FLAG_ENABLE_A,
    .textData = sATextScripts
};
static const match_call_text_data_t sBTextScripts[] = {
    { MatchCall_Text_B1, ALWAYS_AVAILABLE, NO_FLAG_TO_SET },
    { MatchCall_Text_Shared, ALWAYS_AVAILABLE, NO_FLAG_TO_SET },
};
static const struct MatchCallStructTrainer sBMatchCallHeader = {
    .flag = FLAG_ENABLE_B,
    .textData = sBTextScripts
};
static const match_call_text_data_t sMomTextScripts[] = {
    { MatchCall_Text_Mom1, ALWAYS_AVAILABLE, NO_FLAG_TO_SET },
};
static const struct MatchCallStructNPC sMomMatchCallHeader = {
    .flag = ALWAYS_AVAILABLE,
    .textData = sMomTextScripts
};
static const match_call_text_data_t sCTextScripts[] = {
    { MatchCall_Text_C1, ALWAYS_AVAILABLE, NO_FLAG_TO_SET },
    { MatchCall_Text_Called, ALWAYS_AVAILABLE, NO_FLAG_TO_SET },
};
static const struct MatchCallStructNPC sCMatchCallHeader = {
    .flag = FLAG_REGISTERED_C,
    .textData = sCTextScripts
};
#else
static const match_call_text_data_t sEmeraldTextScripts[] = {
    { MatchCall_Text_B1, FLAG_ENABLE_A, NO_FLAG_TO_SET },
};
#endif
'''

MATCH_CALL_INC = ''.join('MatchCall_Text_%s::\n\t.string "Hello.$"\n\n' % n
                         for n in ('A1', 'Shared', 'B1', 'Mom1', 'C1', 'Called'))

TV_SCRIPT = '''EventScript_TV::
\tlockall
\tgoto_if_unset FLAG_SYS_TV_START, EventScript_NoShow
\tgoto EventScript_TryDoTVShow
\tend

EventScript_NoShow::
\treleaseall
\tend

EventScript_TryDoTVShow::
\tspecial DoTVShow
\treleaseall
\tend
'''

TV_TEXT = '''TV_Text_Show1::
\t.string "Show one.$"

TV_Text_Show2::
\t.string "Show two.$"

Lobby_Text_Reporter::
\t.string "May I ask you something?$"

TV_Text_Rerun::
\t.string "Here is that show again.$"

TV_Text_Unused::
\t.string "Nobody shows this.$"
'''

TV_C = '''// TV_Text_Unused is named only in this comment
static const u8 *const sTVShowTextGroup[] = {
    TV_Text_Show1,
    TV_Text_Show2,
    TV_Text_Rerun,
};

static void DoTVShowOne(void)
{
    ShowFieldMessage(sTVShowTextGroup[gSpecialVar_Result]);
}

void DoTVShow(void)
{
    DoTVShowOne();
}
'''

LOBBY = '''Lobby_EventScript_Reporter::
\tmsgbox Lobby_Text_Reporter, MSGBOX_DEFAULT
\tend

Lobby_EventScript_Fan::
\tmsgbox TV_Text_Rerun, MSGBOX_DEFAULT
\tend
'''

OTHER = '''Other_EventScript_Phone::
\tmsgbox MatchCall_Text_Called, MSGBOX_DEFAULT
\tend
'''

LIVE_LABELS = {
    'data/text/match_call.inc': {'live': ['MatchCall_Text_A1', 'MatchCall_Text_Shared', 'MatchCall_Text_B1',
                                          'MatchCall_Text_Mom1', 'MatchCall_Text_C1', 'MatchCall_Text_Called'],
                                 'debug_only': [], 'dead': []},
    'data/text/tv.inc': {'live': ['TV_Text_Show1', 'TV_Text_Show2', 'Lobby_Text_Reporter', 'TV_Text_Rerun'],
                         'debug_only': [], 'dead': ['TV_Text_Unused']},
    'data/maps/Kanto_Frlg/scripts.inc': {'live': ['Kanto_Text_Built', 'Kanto_Text_NotBuilt'],
                                         'debug_only': [], 'dead': []},
}

INVENTORY = [
    {'file': 'data/text/match_call.inc', 'strings': 6, 'strings_live': 6, 'chars_live': 60},
    {'file': 'data/text/tv.inc', 'strings': 4, 'strings_live': 4, 'chars_live': 40},
    {'file': 'data/maps/Kanto_Frlg/scripts.inc', 'strings': 2, 'strings_live': 2, 'chars_live': 20},
    {'file': 'src/strings.c', 'strings': 9, 'strings_live': 9, 'chars_live': 90},
]


def tiny_elf(path, names):
    """A 32-bit little-endian ELF that holds only a symbol table naming NAMES (NOTYPE symbols)."""
    strtab = b'\0' + b''.join(n.encode() + b'\0' for n in names)
    syms = [b'\0' * 16]
    off = 1
    for n in names:
        syms.append(struct.pack('<IIIBBH', off, 0x08000000, 0, 0, 0, 1))
        off += len(n) + 1
    symtab = b''.join(syms)
    shstrtab = b'\0.symtab\0.strtab\0.shstrtab\0'
    body = symtab + strtab + shstrtab
    data_off = 52
    shoff = data_off + len(body)
    sections = [
        (0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
        (1, 2, 0, 0, data_off, len(symtab), 2, 1, 4, 16),
        (9, 3, 0, 0, data_off + len(symtab), len(strtab), 0, 0, 1, 0),
        (17, 3, 0, 0, data_off + len(symtab) + len(strtab), len(shstrtab), 0, 0, 1, 0),
    ]
    header = (b'\x7fELF\x01\x01\x01' + b'\0' * 9
              + struct.pack('<HHIIIIIHHHHHH', 2, 40, 1, 0, 0, shoff, 0, 52, 0, 0, 40, len(sections), 3))
    with open(path, 'wb') as f:
        f.write(header + body + b''.join(struct.pack('<IIIIIIIIII', *s) for s in sections))


class FlagGatesTest(unittest.TestCase):

    def setUp(self):
        self.tree = tempfile.mkdtemp()
        files = {
            'include/constants/flags_hns.h': FLAGS_H,
            'src/pokenav_match_call_data.c': MATCH_CALL_C,
            'data/text/match_call.inc': MATCH_CALL_INC,
            'data/scripts/tv.inc': TV_SCRIPT,
            'data/text/tv.inc': TV_TEXT,
            'src/tv.c': TV_C,
            'include/strings.h': 'extern const u8 TV_Text_Show1[];\nextern const u8 MatchCall_Text_A1[];\n',
            'data/specials.inc': '\tdef_special DoTVShow\n',
            'data/maps/Lobby/scripts.inc': LOBBY,
            'data/scripts/other.inc': OTHER,
        }
        for rel, text in files.items():
            p = os.path.join(self.tree, rel)
            os.makedirs(os.path.dirname(p), exist_ok=True)
            with open(p, 'w', encoding='utf-8') as f:
                f.write(text)
        self.labels = os.path.join(self.tree, 'live_labels.json')
        self.inventory = os.path.join(self.tree, 'inventory.json')
        with open(self.labels, 'w') as f:
            json.dump(LIVE_LABELS, f, indent=0)
        with open(self.inventory, 'w') as f:
            json.dump(INVENTORY, f, indent=1)
        self.elf = os.path.join(self.tree, 'build.elf')
        self.all_labels = [L for e in LIVE_LABELS.values() for L in e['live']]
        # MatchCall_Text_A1 has no symbol either, but its flag rule comes first
        tiny_elf(self.elf, [L for L in self.all_labels if L not in ('Kanto_Text_NotBuilt', 'MatchCall_Text_A1')])

    def tearDown(self):
        shutil.rmtree(self.tree)

    def run_tool(self, *args):
        out, err = io.StringIO(), io.StringIO()
        with redirect_stdout(out), redirect_stderr(err):
            code = flag_gates.main(['--tree', self.tree, '--labels', self.labels,
                                    '--inventory', self.inventory] + list(args))
        return code, out.getvalue() + err.getvalue()

    def load(self):
        with open(self.labels) as f:
            labels = json.load(f)
        with open(self.inventory) as f:
            inv = {i['file']: i for i in json.load(f)}
        return labels, inv

    def test_flag_rules(self):
        self.assertEqual(self.run_tool('--check')[0], 1)
        self.assertEqual(self.run_tool('--write')[0], 0)
        labels, inv = self.load()
        mc = labels['data/text/match_call.inc']
        # A's flag is 0 and C's flag is an alias of it; Shared is also in B's table (flag 0x247),
        # Called is named by another script, Mom is ALWAYS_AVAILABLE
        self.assertEqual(mc['flag_off'], ['MatchCall_Text_A1', 'MatchCall_Text_C1'])
        self.assertEqual(mc['live'], ['MatchCall_Text_Shared', 'MatchCall_Text_B1', 'MatchCall_Text_Mom1',
                                      'MatchCall_Text_Called'])
        tv = labels['data/text/tv.inc']
        # the reporter's line is named by a map script, not by a TV table: it stays live; the rerun
        # is in a TV table but a map script names it too, so it stays live as well
        self.assertEqual(tv['flag_off'], ['TV_Text_Show1', 'TV_Text_Show2'])
        self.assertEqual(tv['live'], ['Lobby_Text_Reporter', 'TV_Text_Rerun'])
        self.assertEqual(tv['dead'], ['TV_Text_Unused'])
        self.assertIn('FLAG_SYS_TV_START', tv['flag_off_reason'])
        self.assertNotIn('not_built', labels['data/maps/Kanto_Frlg/scripts.inc'])
        self.assertEqual((inv['data/text/tv.inc']['strings_live'], inv['data/text/tv.inc']['strings'],
                          inv['data/text/tv.inc']['strings_flag_off']), (2, 2, 2))
        self.assertEqual(inv['src/strings.c'], INVENTORY[3])
        self.assertEqual(self.run_tool('--check')[0], 0)

    def test_not_built(self):
        self.assertEqual(self.run_tool('--write', '--elf', self.elf)[0], 0)
        labels, inv = self.load()
        kanto = labels['data/maps/Kanto_Frlg/scripts.inc']
        self.assertEqual(kanto['live'], ['Kanto_Text_Built'])
        self.assertEqual(kanto['not_built'], ['Kanto_Text_NotBuilt'])
        self.assertEqual(inv['data/maps/Kanto_Frlg/scripts.inc']['strings_not_built'], 1)
        # a flag_off label is not also listed as not_built
        self.assertNotIn('not_built', labels['data/text/match_call.inc'])
        self.assertIn('MatchCall_Text_A1', labels['data/text/match_call.inc']['flag_off'])
        # without --elf the not_built lists stay; with an ELF that has the symbol it goes back
        self.assertEqual(self.run_tool('--check')[0], 0)
        tiny_elf(self.elf, self.all_labels)
        self.assertEqual(self.run_tool('--check', '--elf', self.elf)[0], 1)
        self.run_tool('--write', '--elf', self.elf)
        labels, inv = self.load()
        self.assertEqual(labels['data/maps/Kanto_Frlg/scripts.inc']['live'],
                         ['Kanto_Text_Built', 'Kanto_Text_NotBuilt'])
        self.assertNotIn('strings_not_built', inv['data/maps/Kanto_Frlg/scripts.inc'])

    def test_changed_gate_stops(self):
        with open(os.path.join(self.tree, 'data/maps/Lobby/scripts.inc'), 'a') as f:
            f.write('Lobby_EventScript_Tv::\n\tspecial DoTVShow\n\tend\n')
        code, out = self.run_tool('--check')
        self.assertEqual(code, 2)
        self.assertIn('outside the FLAG_SYS_TV_START gate', out)

    def test_special_reached_before_the_gate_stops(self):
        # each special sits below the gate line, but the script reaches it without passing the gate
        script = 'data/scripts/tv.inc'
        cases = [
            ('the gate\'s own target', script, 'EventScript_NoShow::\n\treleaseall',
             'EventScript_NoShow::\n\tspecial DoTVShow\n\treleaseall', 'outside the FLAG_SYS_TV_START gate'),
            ('a jump above the gate', script, '\tlockall\n',
             '\tlockall\n\tgoto_if_set FLAG_ENABLE_B, EventScript_Early\n',
             'outside the FLAG_SYS_TV_START gate'),
            ('a label that falls through', script, 'EventScript_NoShow::\n\treleaseall\n\tend\n',
             'EventScript_NoShow::\n\treleaseall\n', 'outside the FLAG_SYS_TV_START gate'),
            ('a map script that enters a show', 'data/maps/Lobby/scripts.inc', 'Lobby_EventScript_Reporter::\n',
             'Lobby_EventScript_Reporter::\n\tgoto_if_set FLAG_ENABLE_B, EventScript_TryDoTVShow\n',
             'EventScript_TryDoTVShow, a TV script behind the gate'),
        ]
        for name, rel, old, new, message in cases:
            with self.subTest(name):
                p = os.path.join(self.tree, rel)
                with open(p, encoding='utf-8') as f:
                    before = f.read()
                text = before.replace(old, new, 1)
                if name == 'a jump above the gate':
                    text += '\nEventScript_Early::\n\tspecial DoTVShow\n\tend\n'
                self.assertNotEqual(text, before)
                with open(p, 'w', encoding='utf-8') as f:
                    f.write(text)
                code, out = self.run_tool('--check')
                with open(p, 'w', encoding='utf-8') as f:
                    f.write(before)
                self.assertEqual(code, 2, out)
                self.assertIn(message, out)
        self.assertEqual(self.run_tool('--check')[0], 1)

    def test_tv_flag_set_stops(self):
        p = os.path.join(self.tree, 'include/constants/flags_hns.h')
        with open(p, 'w') as f:
            f.write(FLAGS_H.replace('FLAG_SYS_TV_START            0', 'FLAG_SYS_TV_START            0x860'))
        self.assertEqual(self.run_tool('--check')[0], 2)

    def test_shipped_files_pass_check(self):
        out = io.StringIO()
        with redirect_stdout(out):
            code = flag_gates.main(['--check', '--tree', paths.REPO])
        self.assertEqual(code, 0, out.getvalue())


if __name__ == '__main__':
    unittest.main()
