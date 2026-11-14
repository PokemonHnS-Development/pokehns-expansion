import inspect
import json
import os
import shutil
import struct
import sys
import tempfile
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))
sys.path.insert(0, HERE)
import cliptour as ct  # noqa: E402
import textwidth as tw  # noqa: E402
from fixtures import CHARMAP  # noqa: E402

CM = tw.Charmap(CHARMAP)
LOG, COUNT = 0x02030000, 0x020300C0
VAR4 = 0x0203B8D8
ROMSTR = 0x08100000


def enc(text):
    m = tw.TextModel.__new__(tw.TextModel)
    m.charmap, m.subst, m.warnings, m.fill = CM, {}, [], 'max'
    return bytes(m.encode(text))


def rec(str_addr, win=0, font=1, x=0, cur=0, ww=216, gw=7, phys=-3):
    return struct.pack('<IBBBBBBh', str_addr, win, font, x, cur, ww, gw, phys)


class FakeElf(object):
    path = '/nonexistent/pokehns-clip.elf'
    SYMS = [(LOG, 192, 'gRtlClipLog'), (COUNT, 4, 'gRtlClipCount'), (VAR4, 1000, 'gStringVar4'),
            (ROMSTR, 0x20, 'Test_Text_Sign')]

    def __init__(self, clip=True):
        self.clip = clip

    def sym(self, name):
        for a, s, n in self.SYMS:
            if n == name and (self.clip or not n.startswith('gRtlClip')):
                return a
        raise KeyError(name)

    def where(self, addr):
        best = max((s for s in self.SYMS if s[0] <= addr), default=None)
        if best is None:
            return '?'
        off = addr - best[0]
        tag = ' (past end)' if off >= best[1] else ''
        return ('%s+0x%X%s' % (best[2], off, tag)) if off else best[2] + tag


class FakeEmu(object):
    def __init__(self, clip=True):
        self.elf = FakeElf(clip)
        self.mem = ct.MemImage()
        self.mem.add(LOG, b'\x00' * 192)
        self.mem.add(COUNT, b'\x00' * 4)
        self.shots = []

    def set_log(self, count, records):
        log = bytearray(192)
        for seq, r in records.items():
            log[(seq % 16) * 12:(seq % 16) * 12 + 12] = r
        self.mem.add(LOG, bytes(log))
        self.mem.add(COUNT, struct.pack('<I', count))

    def read(self, addr, n):
        return self.mem.read(addr, n)

    def r32(self, addr):
        return struct.unpack('<I', self.mem.read(addr, 4))[0]

    def shot(self, name):
        self.shots.append(name)
        return name + '.png'


class ParseTest(unittest.TestCase):
    def test_ring(self):
        log = b''.join(rec(0x08000000 + i) for i in range(16))
        recs, lost = ct.parse_records(log, 3)
        self.assertEqual([r['seq'] for r in recs], [0, 1, 2])
        self.assertEqual(recs[1]['str'], 0x08000001)
        self.assertEqual(lost, 0)
        recs, lost = ct.parse_records(log, 20, since=2)
        self.assertEqual([r['seq'] for r in recs], list(range(4, 20)))
        self.assertEqual(lost, 2)
        self.assertEqual(recs[0]['str'], 0x08000004)           # seq 4 sits in slot 4
        recs, lost = ct.parse_records(log, 5, since=5)
        self.assertEqual((recs, lost), ([], 0))
        r = ct.parse_records(rec(1, 2, 7, 4, 100, 96, 6, 93) + bytes(180), 1)[0][0]
        self.assertEqual((r['windowId'], r['fontId'], r['x'], r['currentX'], r['windowWidth'], r['glyphWidth'],
                          r['physX']), (2, 7, 4, 100, 96, 6, 93))

    def test_decode_marks_glyph_before_str(self):
        mem = ct.MemImage()
        data = b'\x55\xff' + enc('שלום GOLD!$') + b'\x55' * 8
        mem.add(VAR4 - 2, data)
        d = ct.decode_clip(mem.read, VAR4 + 3, CM)
        self.assertEqual(d['text'], 'של⟦ו⟧ם GOLD!$')
        self.assertEqual(d['start'], VAR4)
        self.assertEqual(d['glyph'], 'ו')

    def test_decode_extra_symbol_and_floor(self):
        mem = ct.MemImage()
        mem.add(ROMSTR - 4, b'\x00\x00\x00\x00' + enc('{UP_ARROW_2}AB$'))
        d = ct.decode_clip(mem.read, ROMSTR + 2, CM, floor=ROMSTR)
        self.assertEqual(d['text'], '⟦{UP_ARROW_2}⟧AB$')
        d = ct.decode_clip(mem.read, ROMSTR + 2, CM)                  # no floor: padding spaces show
        self.assertTrue(d['text'].endswith('⟦{UP_ARROW_2}⟧AB$'))
        self.assertEqual(ct.symbol_floor('Test_Text_Sign+0x2', ROMSTR + 2), ROMSTR)
        self.assertIsNone(ct.symbol_floor('gFoo+0x40 (past end)', ROMSTR))


class HookTest(unittest.TestCase):
    def setUp(self):
        self.out = tempfile.mkdtemp(prefix='hns_clip_test_')

    def tearDown(self):
        shutil.rmtree(self.out, ignore_errors=True)

    def test_install_reports_per_shot(self):
        emu = FakeEmu()
        emu.mem.add(VAR4, enc('שלום GOLD!$'))
        emu.mem.add(ROMSTR, enc('Sign text here$'))
        rep = ct.install(emu, self.out, CM, echo=False)
        emu.shot('title')
        self.assertEqual(rep.shots['title'], [])
        emu.set_log(2, {0: rec(VAR4 + 3), 1: rec(ROMSTR + 4, win=3, font=7, phys=94, ww=96, gw=6)})
        self.assertEqual(emu.shot('bag'), 'bag.png')
        got = rep.shots['bag']
        self.assertEqual([r['where'] for r in got], ['gStringVar4+0x3', 'Test_Text_Sign+0x4'])
        self.assertEqual(got[1]['text'], 'Sig⟦n⟧ text here$')
        emu.shot('bag2')
        self.assertEqual(rep.shots['bag2'], [])
        emu.set_log(22, {s: rec(ROMSTR + 1 + (s % 4)) for s in range(6, 22)})
        emu.shot('party')
        self.assertEqual(len(rep.shots['party']), 16)
        self.assertEqual(rep.lost, 4)
        with open(os.path.join(self.out, 'clip.json'), encoding='utf-8') as fh:
            saved = json.load(fh)
        self.assertEqual(saved['total'], 18)
        self.assertEqual(saved['shots']['bag'][0]['str'], '%08X' % (VAR4 + 3))
        self.assertIn('glyph', ct.describe(got[0], got[0]['where'], got[0]))

    def test_not_a_clip_build(self):
        with self.assertRaises(RuntimeError):
            ct.install(FakeEmu(clip=False), None, CM, echo=False)


class HnsIntegrationTest(unittest.TestCase):
    def test_tour_has_clip_option(self):
        sys.path.insert(0, ct.EMU_DIR)
        import hns
        self.assertIn('clip', inspect.signature(hns.run_tours).parameters)
        with self.assertRaises(hns.HnsError):
            hns.clip_hook(FakeEmu(clip=False), None)
        emu = FakeEmu()
        hns.clip_hook(emu, None)
        self.assertEqual(hns.clip_count(emu), 0)


if __name__ == '__main__':
    unittest.main()
