import io
import os
import queue
import sys
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(HERE), 'emu'))
import hns  # noqa: E402


class FakeProc(object):
    def __init__(self, text):
        self.stdout = io.StringIO(text)
        self.sent = []

        class In(object):
            def write(s, line):
                self.sent.append(line)

            def flush(s):
                pass
        self.stdin = In()

    def poll(self):
        return None


def bare_emu(proc, max_frames=0):
    emu = hns.Emu.__new__(hns.Emu)
    emu.p, emu.q = proc, queue.Queue()
    emu.max_frames, emu.frames_asked = max_frames, 0
    return emu


def drain(q):
    out = []
    while True:
        line = q.get_nowait()
        if line is None:
            return out
        out.append(line)


class CommandFramesTest(unittest.TestCase):
    def test_frame_commands(self):
        self.assertEqual(hns.command_frames('60 -'), 60)
        self.assertEqual(hns.command_frames('12 UP'), 12)
        self.assertEqual(hns.command_frames('tap A'), 23)
        self.assertEqual(hns.command_frames('tap A 4'), 7)
        self.assertEqual(hns.command_frames('wait32 03005BD4 08000001 600 A'), 600)
        for line in ('r32 03005BD4', 'read 02000000 4', 'shot x', 'pc', 'quit', 'w8 02000000 1'):
            self.assertEqual(hns.command_frames(line), 0, line)


class FrameLimitTest(unittest.TestCase):
    def test_a_command_past_the_limit_ends_the_tour(self):
        p = FakeProc('')
        emu = bare_emu(p, max_frames=100)
        emu.send('60 -')
        emu.send('r32 03005BD4')
        with self.assertRaises(hns.TourTimeout):
            emu.send('tap A 40')
        emu.send('pc')                                   # no frames: still allowed (the end-of-tour shot)
        self.assertEqual(p.sent, ['60 -\n', 'r32 03005BD4\n', 'pc\n'])
        self.assertEqual(emu.frames_asked, 60)

    def test_answers_with_the_frame_count_reset_the_sum(self):
        p = FakeProc('WAIT ok 03005BD4 after 12 @112\n')
        emu = bare_emu(p, max_frames=1000)
        emu.log, emu.echo = hns.RunLog(), False
        emu.send('100 -')
        emu.send('wait32 03005BD4 08000001 600')          # charged 600 until it answers
        self.assertEqual(emu.frames_asked, 700)
        emu._reader()
        emu.expect(r'^WAIT ')
        self.assertEqual(emu.frames_asked, 112)
        emu.send('wait32 03005BD4 08000001 800')          # 112 + 800 fits

    def test_no_limit_by_default(self):
        emu = bare_emu(FakeProc(''))
        emu.send('100000 -')
        self.assertEqual(emu.frames_asked, 0)


class ReaderTest(unittest.TestCase):
    def test_a_run_of_log_lines_is_cut(self):
        lines = ['R32 0 = 1'] + ['LOG[GBA/4] @808 Illegal opcode: e710b710'] * 2500 + ['PC 5BD05BD4 @1685']
        emu = bare_emu(FakeProc('\n'.join(lines) + '\n'))
        emu._reader()
        out = drain(emu.q)
        self.assertEqual(len(out), 1 + hns.Emu.LOG_RUN_MAX + 1 + 1)
        self.assertEqual(out[0], 'R32 0 = 1')
        self.assertEqual(out[-2], 'LOG ... %d more log lines in a row dropped (invalid code)'
                         % (2500 - hns.Emu.LOG_RUN_MAX))
        self.assertEqual(out[-1], 'PC 5BD05BD4 @1685')

    def test_invalid_code_ends_the_tour_as_a_crash(self):
        lines = ['LOG[GBA Memory/1] @808 Jumped to invalid address: 5BD05BD4'] * 1500 + ['PC 5BD05BD4 @1685']
        emu = bare_emu(FakeProc('\n'.join(lines) + '\n'))
        emu.log, emu.echo = hns.RunLog(), False
        emu._reader()
        with self.assertRaises(hns.HnsError) as cm:
            emu.expect(r'^PC ')
        self.assertTrue(str(cm.exception).startswith('CRASH'))

    def test_a_long_run_of_game_prints_is_not_a_crash(self):
        lines = ['LOG[GBA Debug/1] @9 print'] * 1500 + ['PC 08000000 @9']
        emu = bare_emu(FakeProc('\n'.join(lines) + '\n'))
        emu.log, emu.echo = hns.RunLog(), False
        emu._reader()
        self.assertEqual(emu.expect(r'^PC (\w+)').group(1), '08000000')
        self.assertEqual(emu.log[-2], 'LOG ... 500 more log lines in a row dropped')

    def test_short_runs_are_kept(self):
        lines = ['LOG[GBA Debug/1] @1 a', 'R32 0 = 1', 'LOG[GBA Debug/1] @2 b']
        emu = bare_emu(FakeProc('\n'.join(lines) + '\n'))
        emu._reader()
        self.assertEqual(drain(emu.q), lines)


if __name__ == '__main__':
    unittest.main()
