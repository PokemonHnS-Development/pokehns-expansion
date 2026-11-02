import json
import os
import shutil
import sys
import tempfile
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))
import strcov  # noqa: E402

TREE = os.path.dirname(os.path.dirname(os.path.dirname(HERE)))
PREPROC = os.path.join(TREE, 'tools', 'preproc', 'preproc')


class FakeElf(object):
    def __init__(self):
        self.byname = {n: [(0x02030000 + 4 * i, 4, 'OBJECT', 'GLOBAL')] for i, n in enumerate(strcov.SYMS)}
        self.byname['gRtlStringSet'] = [(0x02040000, strcov.SLOTS * 4, 'OBJECT', 'GLOBAL')]
        self.path = 'fake.elf'

    def sym(self, name):
        return self.byname[name][0][0]


class FakeEmu(object):
    """Just enough of hns.Emu: memory, shot, close, frames, tap."""

    def __init__(self, outdir):
        self.elf = FakeElf()
        self.outdir = outdir
        self.rom = 'fake.gba'
        self.log = []
        self.mem = {}
        self.shots = []
        self.closed = False

        class P(object):
            def poll(self):
                return None
        self.p = P()

    def r32(self, a):
        return self.mem.get(a, 0)

    def w32(self, a, v):
        self.mem[a] = v

    def read(self, a, n):
        out = bytearray(n)
        for i in range(0, n, 4):
            v = self.mem.get(a + i, 0)
            out[i:i + 4] = v.to_bytes(4, 'little')
        return bytes(out)

    def shot(self, name):
        self.shots.append(name)
        return name

    def close(self):
        self.closed = True
        return 0

    def frames(self, n, keys='-'):
        pass

    def tap(self, keys, idle=20):
        pass

    def send(self, line):
        self.sent = getattr(self, 'sent', []) + [line]

    def game_insert(self, addr):
        """What RtlStringReport does (src/string_util.c), minus the hash: any free slot will do."""
        e = self.elf
        if self.mem.get(e.sym('gRtlStringClear')):
            for i in range(strcov.SLOTS):
                self.mem.pop(e.sym('gRtlStringSet') + 4 * i, None)
            self.mem[e.sym('gRtlStringCount')] = 0
            self.mem[e.sym('gRtlStringClear')] = 0
        base = e.sym('gRtlStringSet')
        free = None
        for i in range(strcov.SLOTS):
            v = self.mem.get(base + 4 * i, 0)
            if v == addr:
                return
            if v == 0 and free is None:
                free = i
        self.mem[base + 4 * free] = addr
        for n in ('gRtlStringCount', 'gRtlStringTotal'):
            self.mem[e.sym(n)] = self.mem.get(e.sym(n), 0) + 1


class HookTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.mkdtemp()

    def tearDown(self):
        shutil.rmtree(self.tmp)

    def test_poll_logs_new_addresses_once_and_empties_the_set(self):
        emu = FakeEmu(os.path.join(self.tmp, 'out', 'tour_a'))
        rep = strcov.install(emu, os.path.join(self.tmp, 'logs'))
        emu.game_insert(0x08100000)
        emu.game_insert(0x08100010)
        emu.shot('s1')
        self.assertEqual(emu.r32(emu.elf.sym('gRtlStringCount')), 0)
        self.assertEqual(emu.r32(emu.elf.sym('gRtlStringClear')), 1)
        emu.game_insert(0x08100010)            # seen before: logged once only
        emu.game_insert(0x08100020)
        emu.shot('s2')
        emu.close()
        self.assertTrue(emu.closed)
        recs = [r for _, r in strcov.read_logs([os.path.join(self.tmp, 'logs')])]
        polls = [r for r in recs if 'new' in r]
        self.assertEqual([p['shot'] for p in polls], ['s1', 's2'])
        self.assertEqual(polls[0]['new'], ['08100000', '08100010'])
        self.assertEqual(polls[1]['new'], ['08100020'])
        self.assertEqual(recs[-1]['distinct'], 3)
        self.assertEqual(rep.lost, 0)

    def test_savestate_load_is_preceded_by_a_poll(self):
        emu = FakeEmu(os.path.join(self.tmp, 'out', 'tour_c'))
        strcov.install(emu, os.path.join(self.tmp, 'logs'))
        emu.game_insert(0x08100040)
        emu.send('sl state.ss')
        polls = [r for _, r in strcov.read_logs([os.path.join(self.tmp, 'logs')]) if 'new' in r]
        self.assertEqual(polls[0]['shot'], 'before:sl:_boot')
        self.assertEqual(polls[0]['new'], ['08100040'])
        self.assertEqual(emu.sent, ['sl state.ss'])

    def test_session_file_is_not_hidden(self):
        emu = FakeEmu(os.path.join(self.tmp, 'out', 'tour_b'))
        rep = strcov.install(emu, os.path.join(self.tmp, 'logs'))
        self.assertFalse(os.path.basename(rep.path).startswith('.'))


class ReportTest(unittest.TestCase):
    def index(self):
        return {'records': [
            {'id': 0, 'lang': 'he', 'file': 'src/a.c', 'line': 1, 'symbol': 'src/a.c:gText_A', 'kind': 'k',
             'text': 'A', 'copies': [[0x08100000, 0x08100008]], 'how': 'symbol'},
            {'id': 1, 'lang': 'he', 'file': 'src/a.c', 'line': 2, 'symbol': 'src/a.c:L2', 'kind': 'k',
             'text': 'B', 'copies': [[0x08100010, 0x08100018]], 'how': 'object'},
            {'id': 2, 'lang': 'he', 'file': 'src/b.c', 'line': 3, 'symbol': 'src/b.c:L3', 'kind': 'k',
             'text': 'C', 'copies': [], 'how': 'object'},
            {'id': 3, 'lang': 'en', 'file': 'src/b.c', 'line': 4, 'symbol': 'src/b.c:L4', 'kind': 'k',
             'text': 'D', 'copies': [[0x08100020, 0x08100024]], 'how': 'object'}],
            'orphans': [{'addr': 0x08100030, 'end': 0x08100038, 'object': 'src/b.o', 'text': 'E'}]}

    def test_mid_string_pointer_counts_and_terminator_does_not(self):
        logs = [('s.jsonl', {'session': 't'}),
                ('s.jsonl', {'tour': 't', 'shot': 'x', 'new': ['08100004', '08100018', '08100021', '08100031']})]
        out, ses, unmapped, unm, orph = strcov.make_report(self.index(), logs)
        st = {o['id']: o['status'] for o in out}
        self.assertEqual(st, {0: 'seen', 1: 'unseen', 2: 'not_located'})
        self.assertEqual(out[0]['first_seen'], {'tour': 't', 'shot': 'x'})
        self.assertEqual(sorted(unmapped), [0x08100018])      # the FF of B: nothing drawn
        self.assertTrue(orph[0]['seen'])
        self.assertNotIn(3, st)                               # English strings are not reported

    def test_by_file(self):
        out, _, _, _, _ = strcov.make_report(self.index(), [])
        files = {f['file']: f for f in strcov.by_file(out)}
        self.assertEqual(files['src/a.c']['unseen'], 2)
        self.assertEqual(files['src/b.c']['not_located'], 1)


@unittest.skipUnless(os.path.exists(PREPROC), 'tools/preproc is not built')
class EncodeTest(unittest.TestCase):
    def test_preproc_encoding_and_bad_string(self):
        enc = strcov.encode_all(TREE, ['AB', '{NOT_A_CONSTANT}', ''])
        self.assertEqual(enc[0], bytes([0xBB, 0xBC]))
        self.assertIsNone(enc[1])
        self.assertEqual(enc[2], b'')


if __name__ == '__main__':
    unittest.main()
