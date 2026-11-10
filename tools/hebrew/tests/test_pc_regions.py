"""The harness's CRASH check: which PC regions count as running code (hns.pc_is_sane and hnsrun.c's
pcIsSane), and how a PC in the ROM's wait-state mirrors is named (hns.Elf.where, sweep.crash_detail).
The game runs every script command that requests effects from the mirror at 0x0A (the script
command table stores those as address + ROM_SIZE), so those regions must pass."""
import os
import re
import shutil
import subprocess
import sys
import tempfile
import types
import unittest

HERE = os.path.dirname(os.path.abspath(__file__))
EMU = os.path.join(os.path.dirname(HERE), 'emu')
sys.path.insert(0, EMU)
import hns  # noqa: E402
import sweep  # noqa: E402

SANE = [0x000001F8, 0x02012345, 0x03007C98, 0x080E8ECC, 0x09FFFFFE,
        0x0A0E8ECC, 0x0A202259, 0x0B000000, 0x0C000001, 0x0DFFFFFF]
INSANE = [0x01000000, 0x04000000, 0x05000200, 0x06017FF4, 0x07000000, 0x0E000004, 0x0F000000,
          0x10000000, 0x5BD05BD4, 0xFFFFFFFF]


def fake_elf():
    elf = hns.Elf.__new__(hns.Elf)
    elf.path, elf._sorted, elf._ranges = 'fake.elf', None, None
    elf.byname = {'FillBitmapRect4Bit': [(0x080E8E2D, 194, 'FUNC', 'GLOBAL')],
                  'ScrCmd_multichoice': [(0x08202259, 88, 'FUNC', 'GLOBAL')],
                  'sLastRomObject': [(0x09F00000, 0x10, 'OBJECT', 'LOCAL')],
                  'gMain': [(0x03005BD0, 0x43C, 'OBJECT', 'GLOBAL')]}
    return elf


class PcIsSaneTest(unittest.TestCase):
    def test_code_regions(self):
        for pc in SANE:
            self.assertTrue(hns.pc_is_sane(pc), '%08X' % pc)
        for pc in INSANE:
            self.assertFalse(hns.pc_is_sane(pc), '%08X' % pc)

    def test_the_sweep_fault_is_a_crash(self):
        # sweep.py --fault crash must put the PC where the check stops the run.
        self.assertFalse(hns.pc_is_sane(sweep.FAULT_PC))


class SweepFaultTest(unittest.TestCase):
    """sweep.py --fault crash writes a loop that masks IRQs into VRAM and points gMain.callback2 at
    it, so the PC stays outside the code regions until hnsrun's next 60-frame check."""

    def test_crash_writes_an_irq_off_loop_and_jumps_there(self):
        sw = types.SimpleNamespace(faults={'L': 'crash'}, gmain=0x03005BD0)
        self.assertEqual(sweep.Sweeper._fault(sw, 'L'),
                         ['w32 06017FF0 E321F09F', 'w32 06017FF4 EAFFFFFE', 'w32 03005BD4 06017FF0'])
        self.assertEqual(sweep.Sweeper._fault(sw, 'other'), [])

    def test_the_loop(self):
        msr, branch = sweep.FAULT_CODE
        self.assertEqual(msr & 0xFFFFFF00, 0xE321F000)     # msr cpsr_c, #imm
        self.assertEqual(msr & 0xFF, 0x9F)                 # System mode 0x1F, I bit 0x80 (IRQs masked), ARM
        self.assertEqual(branch, 0xEAFFFFFE)               # b .
        self.assertEqual(sweep.FAULT_PC & 3, 0)            # ARM: callback2 is called with bx
        for pc in range(sweep.FAULT_PC, sweep.FAULT_PC + 4 * len(sweep.FAULT_CODE) + 8, 4):
            self.assertFalse(hns.pc_is_sane(pc), '%08X' % pc)


@unittest.skipUnless(shutil.which('cc'), 'needs a C compiler')
class HnsrunPcIsSaneTest(unittest.TestCase):
    """pcIsSane from hnsrun.c, compiled on its own (the runner itself needs libmgba), accepts
    exactly the regions hns.pc_is_sane accepts."""

    def test_same_regions_as_hns(self):
        with open(os.path.join(EMU, 'hnsrun.c'), encoding='utf-8') as fh:
            src = fh.read()
        m = re.search(r'^static int pcIsSane\(uint32_t pc\) \{\n.*?^\}\n', src, re.M | re.S)
        self.assertIsNotNone(m, 'pcIsSane not found in hnsrun.c')
        d = tempfile.mkdtemp(prefix='hns_pcissane_')
        try:
            c = os.path.join(d, 'pc.c')
            with open(c, 'w') as fh:
                fh.write('#include <stdint.h>\n#include <stdio.h>\n#include <stdlib.h>\n' + m.group(0) +
                         'int main(int argc, char** argv) {\n'
                         '    for (int i = 1; i < argc; i++)\n'
                         '        printf("%d\\n", pcIsSane((uint32_t) strtoul(argv[i], NULL, 16)));\n'
                         '    return 0;\n}\n')
            exe = os.path.join(d, 'pc')
            subprocess.run(['cc', '-O0', '-o', exe, c], check=True, capture_output=True)
            pcs = SANE + INSANE + [r << 24 | 0x123456 for r in range(256)]
            out = subprocess.run([exe] + ['%08X' % pc for pc in pcs], check=True, capture_output=True,
                                 text=True).stdout.split()
            got = [('%08X' % pc, o == '1') for pc, o in zip(pcs, out)]
            self.assertEqual(got[:len(SANE) + len(INSANE)],
                             [('%08X' % pc, True) for pc in SANE] + [('%08X' % pc, False) for pc in INSANE])
            self.assertEqual(got, [('%08X' % pc, hns.pc_is_sane(pc)) for pc in pcs])
        finally:
            shutil.rmtree(d, ignore_errors=True)


class MirrorSymbolTest(unittest.TestCase):
    def test_unmirror(self):
        self.assertEqual(hns.rom_unmirror(0x0A202259), 0x08202259)
        self.assertEqual(hns.rom_unmirror(0x0B000010), 0x09000010)
        self.assertEqual(hns.rom_unmirror(0x0C000000), 0x08000000)
        self.assertEqual(hns.rom_unmirror(0x0DFFFFFE), 0x09FFFFFE)
        for addr in (0x08001234, 0x09FFFFFF, 0x02000000, 0x03007C98, 0x0E000000, 0x000001F8):
            self.assertEqual(hns.rom_unmirror(addr), addr)

    def test_where_names_the_mirrored_rom_address(self):
        elf = fake_elf()
        self.assertEqual(elf.where(0x080E8ECC), 'FillBitmapRect4Bit+0xA0')
        self.assertEqual(elf.where(0x0A0E8ECC), 'FillBitmapRect4Bit+0xA0')
        self.assertEqual(elf.where(0x0A202259), 'ScrCmd_multichoice')
        self.assertEqual(elf.where(0x03005BD4), 'gMain+0x4')

    def test_sweep_crash_detail(self):
        elf = fake_elf()
        self.assertEqual(sweep.crash_detail('CRASH: pc=0A0E8ECC @21720', elf),
                         'CRASH: pc=0A0E8ECC @21720 (FillBitmapRect4Bit+0xA0)')
        self.assertEqual(sweep.crash_detail('CRASH: pc=080E8ECC @60', elf),
                         'CRASH: pc=080E8ECC @60 (FillBitmapRect4Bit+0xA0)')
        for msg in ('CRASH: pc=0E000004 @420', 'CRASH: pc=000001F8 @60',
                    'runner exited while waiting for /^PC /; last lines:'):
            self.assertEqual(sweep.crash_detail(msg, elf), msg)


if __name__ == '__main__':
    unittest.main()
