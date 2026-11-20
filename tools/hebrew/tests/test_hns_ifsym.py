import contextlib
import io
import os
import sys
import tempfile
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(HERE), 'emu'))
import hns  # noqa: E402


class FakeElf(object):
    def __init__(self, names):
        self.byname = {n: [(0x08000001, 4, 'FUNC', 'LOCAL')] for n in names}


class EchoEmu(hns.Emu):
    """Only what run_script needs for echo and include lines: no runner process."""

    def __init__(self, names):
        self.elf = FakeElf(names)

    def sync(self):
        return 0


def run(script, names, extra=None):
    with tempfile.TemporaryDirectory() as d:
        for name, text in dict(extra or {}, main=script).items():
            with open(os.path.join(d, name + '.txt'), 'w', encoding='utf-8') as f:
                f.write(text)
        out = io.StringIO()
        with contextlib.redirect_stdout(out):
            EchoEmu(names).run_script(os.path.join(d, 'main.txt'))
        return out.getvalue().split()


class IfsymTest(unittest.TestCase):
    SCRIPT = ('echo a\n'
              'ifsym Task_HandleStopLearningMoveYesNoInput   # only in a build with the yes/no\n'
              'echo b\n'
              'include part.txt\n'
              'endif\n'
              'echo d\n')

    def test_the_block_runs_when_the_elf_defines_the_symbol(self):
        self.assertEqual(run(self.SCRIPT, ['Task_HandleStopLearningMoveYesNoInput'], {'part': 'echo c\n'}),
                         ['a', 'b', 'c', 'd'])

    def test_the_block_is_skipped_includes_too_when_it_does_not(self):
        self.assertEqual(run(self.SCRIPT, [], {'part': 'echo c\n'}), ['a', 'd'])

    def test_blocks_nest(self):
        script = 'ifsym A\necho a\nifsym B\necho b\nendif\necho c\nendif\necho d\n'
        self.assertEqual(run(script, ['A']), ['a', 'c', 'd'])
        self.assertEqual(run(script, ['B']), ['d'])

    def test_an_unbalanced_block_is_an_error(self):
        with self.assertRaises(hns.HnsError):
            run('ifsym A\necho a\n', ['A'])
        with self.assertRaises(hns.HnsError):
            run('echo a\nendif\n', [])

    def test_render_refuses_it(self):
        self.assertIn('ifsym', hns.EXTENSIONS)
        self.assertIn('endif', hns.EXTENSIONS)


if __name__ == '__main__':
    unittest.main()
