import os
import sys
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(HERE), 'emu'))
import hns  # noqa: E402

SYMS = {
    'gMenuCallback': 0x03006138,
    'HandleStartMenuInput': 0x0821A2AD,
    'StartMenuBagCallback': 0x082195E1,
    'Task_ShowStartMenu': 0x082196CD,
    'sNumStartMenuActions': 0x0203B8C6,
    'sCurrentStartMenuActions': 0x0203B8C8,
    'sStartMenuCursorPos': 0x0203B8C5,
}
NORMAL_MENU = [0, 1, 2, 3, 4, 5, 6, 7]     # POKEDEX POKEMON BAG POKENAV PLAYER SAVE OPTION EXIT


class FakeGame(hns.Emu):
    """The start menu as the game keeps it in RAM (src/start_menu.c): gMenuCallback, the
    Task_ShowStartMenu task and its data[0], the cursor. START on a controllable field draws
    the menu OPEN_FRAMES later; DOWN moves the cursor only while the menu reads input.
    REOPEN_IN draws it again after that many frames, the way the game does on the way back
    from a screen opened from the menu."""
    OPEN_FRAMES = 12

    def __init__(self, callback, task=None, ctl=True, cursor=1, reopen_in=None):
        self.callback, self.task, self.ctl, self.cursor = callback, task, ctl, cursor
        self.now, self.opens_at, self.keys = 0, None, []
        if reopen_in is not None:
            self.opens_at = reopen_in

    def sym(self, name):
        return SYMS[name]

    def cb2_name(self):
        return 'CB2_Overworld'

    def tasks(self):
        return [(0, SYMS['Task_ShowStartMenu'], 'Task_ShowStartMenu')] if self.task is not None else []

    def task_data(self, name):
        if name == 'Task_ShowStartMenu' and self.task is not None:
            return [[self.task] + [0] * 15]
        return []

    def r32(self, addr):
        self.assertAddr(addr, 'gMenuCallback')
        return self.callback

    def r8(self, addr):
        if addr == SYMS['sNumStartMenuActions']:
            return len(NORMAL_MENU)
        self.assertAddr(addr, 'sStartMenuCursorPos')
        return self.cursor

    def read(self, addr, n):
        self.assertAddr(addr, 'sCurrentStartMenuActions')
        return bytes(NORMAL_MENU[:n])

    def assertAddr(self, addr, name):
        if addr != SYMS[name]:
            raise AssertionError('read of %08X, expected %s' % (addr, name))

    def controllable(self):
        return self.ctl

    def ready(self):
        return self.callback == SYMS['HandleStartMenuInput'] and self.task == 1

    def frames(self, n, keys='-'):
        for _ in range(n):
            self.now += 1
            if self.opens_at is not None and self.now >= self.opens_at:
                self.callback, self.task, self.ctl, self.opens_at = SYMS['HandleStartMenuInput'], 1, False, None

    def tap(self, keys, idle=20):
        self.keys.append(keys)
        if keys == 'START' and self.ctl and self.task is None:
            self.ctl, self.opens_at = False, self.now + self.OPEN_FRAMES
        elif keys == 'DOWN' and self.ready():
            self.cursor = (self.cursor + 1) % len(NORMAL_MENU)
        self.frames(3 + idle)


class StartMenuReadyTest(unittest.TestCase):
    def test_the_callback_alone_is_not_an_open_menu(self):
        handler = SYMS['HandleStartMenuInput']
        self.assertFalse(FakeGame(handler).start_menu_ready())            # closed: the stale pointer
        self.assertFalse(FakeGame(handler, task=0).start_menu_ready())    # task not yet reading input
        self.assertTrue(FakeGame(handler, task=1, ctl=False).start_menu_ready())
        self.assertFalse(FakeGame(SYMS['StartMenuBagCallback'], task=1, ctl=False).start_menu_ready())
        self.assertFalse(FakeGame(0, task=1, ctl=False).start_menu_ready())


class StartMenuCursorTest(unittest.TestCase):
    def test_a_closed_menu_with_a_stale_callback_is_opened(self):
        g = FakeGame(SYMS['HandleStartMenuInput'], cursor=1)
        g.start_menu_cursor('BAG')
        self.assertEqual(g.keys.count('START'), 1)
        self.assertEqual(g.cursor, 2)
        self.assertEqual(g.keys[-1], 'A')

    def test_an_open_menu_is_used_as_it_is(self):
        g = FakeGame(SYMS['HandleStartMenuInput'], task=1, ctl=False, cursor=1)
        g.start_menu_cursor('PLAYER')
        self.assertNotIn('START', g.keys)
        self.assertEqual(g.cursor, 4)
        self.assertEqual(g.keys, ['DOWN', 'DOWN', 'DOWN', 'A'])

    def test_a_menu_the_game_is_drawing_again_is_waited_for(self):
        g = FakeGame(SYMS['StartMenuBagCallback'], ctl=False, cursor=2, reopen_in=30)
        g.start_menu_cursor('BAG', press=False)
        self.assertEqual(g.keys, [])
        self.assertTrue(g.ready())
        self.assertGreaterEqual(g.now, 30)

    def test_the_first_menu_of_a_run_opens_as_before(self):
        g = FakeGame(0, cursor=0)
        g.start_menu_cursor('POKEDEX', press=False)
        self.assertEqual(g.keys, ['START'])
        self.assertTrue(g.ready())

    def test_no_menu_and_no_control_is_an_error(self):
        g = FakeGame(0, ctl=False)
        with self.assertRaises(hns.HnsError):
            g.open_start_menu(maxframes=40)
        self.assertEqual(g.keys, [])


if __name__ == '__main__':
    unittest.main()
