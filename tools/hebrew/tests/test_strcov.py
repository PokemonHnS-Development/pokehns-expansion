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
             'text': 'D', 'copies': [[0x08100020, 0x08100024]], 'how': 'object'},
            {'id': 4, 'lang': 'he', 'file': 'src/b.c', 'line': 5, 'symbol': 'src/b.c:L5', 'kind': 'k',
             'text': 'F', 'copies': [], 'how': 'object', 'compiled': False},
            {'id': 5, 'lang': 'he', 'file': 'src/b.c', 'line': 6, 'symbol': 'src/b.c:sG', 'kind': 'k',
             'text': 'G', 'copies': [], 'how': 'ram_data'}],
            'orphans': [{'addr': 0x08100030, 'end': 0x08100038, 'object': 'src/b.o', 'text': 'E'},
                        {'addr': 0x08100000, 'end': 0x08100008, 'object': 'src/a.o', 'text': 'A'}]}

    def test_mid_string_pointer_counts_and_terminator_does_not(self):
        logs = [('logs/job1/s.jsonl', {'session': 't', 'outdir': '/o/t'}),
                ('logs/job1/s.jsonl', {'tour': 't', 'shot': 'x', 'new': ['08100004', '08100018', '08100021', '08100031']})]
        out, ses, unmapped, unm, orph = strcov.make_report(self.index(), logs)
        st = {o['id']: o['status'] for o in out}
        self.assertEqual(st, {0: 'seen', 1: 'unseen', 2: 'not_located', 4: 'compiled_out', 5: 'hook_blind'})
        self.assertEqual(out[0]['first_seen'], {'job': 'job1', 'session': 's.jsonl', 'outdir': '/o/t',
                                                'tour': 't', 'shot': 'x', 'addr': '08100004'})
        self.assertEqual(sorted(unmapped), [0x08100018])      # the FF of B: nothing drawn
        self.assertTrue(orph[0]['seen'])
        self.assertTrue(orph[1]['seen'])                      # a mapped address is tested as well
        self.assertNotIn(3, st)                               # English strings are not reported

    def test_by_file(self):
        out, _, _, _, _ = strcov.make_report(self.index(), [])
        files = {f['file']: f for f in strcov.by_file(out)}
        self.assertEqual(files['src/a.c']['unseen'], 2)
        self.assertEqual(files['src/b.c']['not_located'], 1)
        self.assertEqual(files['src/b.c']['compiled_out'], 1)
        self.assertEqual(files['src/b.c']['hook_blind'], 1)


class SharedCopyTest(unittest.TestCase):
    def test_seen_only_through_a_shared_copy_is_marked(self):
        idx = {'records': [
            {'id': 0, 'lang': 'he', 'file': 'src/a.c', 'line': 1, 'symbol': 'src/a.c:L1', 'kind': 'k', 'text': 'A',
             'copies': [[0x08100000, 0x08100004]], 'how': 'object', 'shares_copy_with': [1]},
            {'id': 1, 'lang': 'he', 'file': 'src/a.c', 'line': 2, 'symbol': 'src/a.c:L2', 'kind': 'k', 'text': 'A',
             'copies': [[0x08100000, 0x08100004], [0x08100010, 0x08100014]], 'how': 'object',
             'shares_copy_with': [0]}]}
        logs = [('logs/j/s.jsonl', {'tour': 't', 'shot': 'x', 'new': ['08100000']})]
        out, _, _, _, _ = strcov.make_report(idx, logs)
        self.assertEqual([o['seen_shared_only'] for o in out], [True, True])
        logs.append(('logs/j/s.jsonl', {'tour': 't', 'shot': 'y', 'new': ['08100011']}))
        out, _, _, _, _ = strcov.make_report(idx, logs)
        self.assertEqual([o['seen_shared_only'] for o in out], [True, False])
        self.assertEqual(strcov.by_file(out)[0]['seen_shared_only'], 1)


class StructClaimTest(unittest.TestCase):
    def test_layout_from_single_copy_records(self):
        pairs = [(1, 64), (5, 240), (9, 416), (2, 999)]           # element size 44, field at 20; one outlier
        self.assertEqual(strcov.struct_layout(pairs)[:2], (44, 20))
        self.assertEqual(strcov.struct_layout(pairs)[2], 0.75)

    def test_name_and_plural_with_the_same_text_get_their_own_pointer(self):
        base, esize = 0x08200000, 16                            # element: u32 x; name ptr +4; plural ptr +8
        rom = bytearray(0x300010)
        name_a, name_b, plural_b = 0x08100000, 0x08100010, 0x08100020
        for idx, (n, pl) in ((1, (name_a, name_a)), (2, (name_b, plural_b))):
            o = base + idx * esize - 0x08000000
            rom[o + 4:o + 8] = n.to_bytes(4, 'little')
            rom[o + 8:o + 12] = pl.to_bytes(4, 'little')
        for idx in range(3, 8):                                 # more single-copy names for the layout
            o = base + idx * esize - 0x08000000
            rom[o + 4:o + 8] = (0x08100100 + 16 * idx).to_bytes(4, 'little')

        class Elf(object):
            byname = {'gItemsInfo': [(base, 8 * esize, 'OBJECT', 'GLOBAL')]}

            def sym(self, n):
                return base

            def size(self, n):
                return 8 * esize

        def rec(i, item, field, copies):
            return {'id': i, 'file': 'src/data/items.h', 'symbol': 'src/data/items.h:gItemsInfo[%s].%s' % (item, field),
                    'copies': copies}
        recs = [rec(0, 'ITEM_B', 'name', [[name_b, name_b + 4], [plural_b, plural_b + 4]]),
                rec(1, 'ITEM_B', 'pluralName', [[name_b, name_b + 4], [plural_b, plural_b + 4]]),
                rec(2, 'ITEM_A', 'name', [[name_a, name_a + 4]])]
        recs += [rec(10 + k, 'ITEM_%d' % k, 'name', [[0x08100100 + 16 * k, 0x08100104 + 16 * k]]) for k in range(3, 8)]
        consts = dict({'ITEM_A': 1, 'ITEM_B': 2}, **{'ITEM_%d' % k: k for k in range(3, 8)})
        real = strcov.resolve_constants
        strcov.resolve_constants = lambda tree, names, dka: {n: consts[n] for n in names if n in consts}
        try:
            claims, layout = strcov.struct_claims(recs, Elf(), bytes(rom), '.', '')
        finally:
            strcov.resolve_constants = real
        self.assertEqual(layout['gItemsInfo.name']['kind'], 'pointer')
        self.assertEqual((layout['gItemsInfo.name']['element_size'], layout['gItemsInfo.name']['offset']), (16, 4))
        self.assertEqual(claims[name_b], {0})
        self.assertEqual(claims[name_a], {2})
        self.assertNotIn(plural_b, claims)                      # too few plurals to measure the field: not used
        self.assertIsNone(layout['gItemsInfo.pluralName'])


class MapRamTest(unittest.TestCase):
    def test_same_ram_reuses_its_slot_else_the_oldest(self):
        emu = FakeEmu('/tmp/x')
        emu.elf.byname['sRtlStringRamMaps'] = [(0x02050000, 2 * strcov.RAM_MAP_SIZE, 'OBJECT', 'LOCAL')]
        emu.elf.byname['sRtlStringRamMapNext'] = [(0x02050100, 4, 'OBJECT', 'LOCAL')]
        emu.elf.size = lambda n: emu.elf.byname[n][0][1]
        self.assertTrue(strcov.map_ram(emu, 0x02001000, 0x08300000, 24))
        self.assertTrue(strcov.map_ram(emu, 0x02002000, 0x08300100, 24))
        self.assertTrue(strcov.map_ram(emu, 0x02001000, 0x08300200, 24))      # same RAM: slot 0 again
        self.assertEqual([emu.r32(0x02050000 + 4 * k) for k in range(6)],
                         [0x02001000, 0x08300200, 24, 0x02002000, 0x08300100, 24])
        self.assertTrue(strcov.map_ram(emu, 0x02003000, 0x08300300, 8))       # new RAM: the oldest slot (0)
        self.assertEqual(emu.r32(0x02050000), 0x02003000)

    def test_not_a_string_report_build(self):
        self.assertFalse(strcov.map_ram(FakeEmu('/tmp/x'), 0x02001000, 0x08300000, 24))


class PrefixTest(unittest.TestCase):
    def entry(self, src, line, text):
        import audit
        starts = [0] + [m.end() for m in __import__('re').finditer('\n', src)]
        return strcov.continues_after(src, starts, audit.Entry('src/x.h', line, 'k', 'k', text, source='c'))

    def test_macro_and_if_continue_a_string(self):
        src = '.d = COMPOUND_STRING(\n    "a\\n"\n    "b "BINDING_TURNS" c"),\n'
        self.assertTrue(self.entry(src, 1, 'a\\nb '))
        src = '.d = COMPOUND_STRING(\n    "a\\n"\n#if X\n    "b"),\n#endif\n'
        self.assertTrue(self.entry(src, 1, 'a\\n'))

    def test_complete_string_does_not(self):
        src = 'static const u8 sText_SpaceIs[] = _(" x"); // c\n'
        self.assertFalse(self.entry(src, 1, ' x'))
        src = '.d = COMPOUND_STRING(\n    "a"\n    /* c */ "b"),\n'
        self.assertFalse(self.entry(src, 1, 'ab'))


@unittest.skipUnless(os.path.exists(PREPROC), 'tools/preproc is not built')
class EncodeTest(unittest.TestCase):
    def test_preproc_encoding_and_bad_string(self):
        enc = strcov.encode_all(TREE, ['AB', '{NOT_A_CONSTANT}', ''])
        self.assertEqual(enc[0], bytes([0xBB, 0xBC]))
        self.assertIsNone(enc[1])
        self.assertEqual(enc[2], b'')


if __name__ == '__main__':
    unittest.main()
