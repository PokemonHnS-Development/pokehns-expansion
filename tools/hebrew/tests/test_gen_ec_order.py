import os
import shutil
import subprocess
import sys
import tempfile
import unittest

TOOL = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'gen_ec_order.py')


def group(name, words):
    body = ''.join('    [EC_INDEX(EC_WORD_%s)] =\n    {\n        .text = COMPOUND_STRING("%s"),\n'
                   '        .alphabeticalOrder = EC_INDEX(EC_WORD_%s),\n        .enabled = TRUE,\n    },\n'
                   % (w, t, w) for w, t in words)
    return ('const u8 gEasyChatWord_Old[] = _("OLD");\n\n'
            'const struct EasyChatWordInfo gEasyChatGroup_%s[] = {\n%s};\n' % (name, body))


class GenEcOrder(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.mkdtemp()
        self.folder = os.path.join(self.tmp, 'src', 'data', 'easy_chat')
        os.makedirs(self.folder)
        # index order: ZEBRA, APPLE, MANGO; Hebrew order: APPLE (א), MANGO (מ), ZEBRA (ת, final ף as פ)
        self.write('trendy_saying', 'TrendySaying', [('ZEBRA', 'תף'), ('APPLE', "אג'"), ('MANGO', 'מפ')])
        with open(os.path.join(self.folder, 'easy_chat_group_move_1.h'), 'w', encoding='utf-8') as f:
            f.write('const u16 gEasyChatGroup_Move1[] = {\n    MOVE_POUND,\n};\n')

    def tearDown(self):
        shutil.rmtree(self.tmp)

    def write(self, file_name, array, words):
        with open(os.path.join(self.folder, 'easy_chat_group_%s.h' % file_name), 'w', encoding='utf-8') as f:
            f.write(group(array, words))

    def run_tool(self, *args):
        return subprocess.run([sys.executable, TOOL, '--tree', self.tmp] + list(args), capture_output=True, text=True)

    def header(self):
        with open(os.path.join(self.folder, 'easy_chat_order_rtl.h'), encoding='utf-8') as f:
            return f.read()

    def test_writes_the_hebrew_order_and_the_group_table(self):
        r = self.run_tool()
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        text = self.header()
        self.assertIn('static const u16 sEasyChatRtlOrder_TrendySaying[] = {\n    EC_INDEX(EC_WORD_APPLE),\n'
                      '    EC_INDEX(EC_WORD_MANGO),\n    EC_INDEX(EC_WORD_ZEBRA),\n};', text)
        self.assertIn('[EC_GROUP_TRENDY_SAYING] = sEasyChatRtlOrder_TrendySaying,', text)
        self.assertNotIn('Move1', text)

    def test_check_passes_when_current_and_fails_when_a_word_changes(self):
        self.run_tool()
        r = self.run_tool('--check')
        self.assertEqual(r.returncode, 0, r.stdout + r.stderr)
        self.write('trendy_saying', 'TrendySaying', [('ZEBRA', 'בב'), ('APPLE', "אג'"), ('MANGO', 'מפ')])
        r = self.run_tool('--check')
        self.assertEqual(r.returncode, 1, r.stdout)
        self.assertIn('TrendySaying: order differs', r.stdout)

    def test_check_fails_when_the_header_is_missing(self):
        r = self.run_tool('--check')
        self.assertEqual(r.returncode, 1)
        self.assertIn('missing', r.stdout)


if __name__ == '__main__':
    unittest.main()
