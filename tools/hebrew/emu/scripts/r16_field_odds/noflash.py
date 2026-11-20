#!/usr/bin/env python3
"""noflash.py ROM OUTDIR: write OUTDIR/<rom name> (a copy of ROM whose IdentifyFlash returns 1: movs r0,#1;
bx lr) and link the ELF (and the linker map, if any) next to it, so CheckForFlashMemory finds no flash
chip at boot and the game shows CB2_FlashNotDetectedScreen (src/main.c:105-119), the screen a player
with a wrong emulator save type or a cart without flash sees. Every symbol keeps its address.
Run tours/r16_field_odds/fo_flash.txt on the copy (odds16.py tour COPY OUT --only '^fo_flash$')."""
import os
import shutil
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(os.path.dirname(HERE)))
import hns  # noqa: E402

PATCH = bytes([0x01, 0x20, 0x70, 0x47])


def main():
    rom, out = os.path.abspath(sys.argv[1]), os.path.abspath(sys.argv[2])
    os.makedirs(out, exist_ok=True)
    base = os.path.splitext(rom)[0]
    elf = hns.Elf(base + ".elf")
    addr = elf.sym("IdentifyFlash") & ~1
    dst = os.path.join(out, os.path.basename(rom))
    shutil.copyfile(rom, dst)
    with open(dst, "r+b") as fh:
        fh.seek(addr - 0x08000000)
        fh.write(PATCH)
    for ext in (".elf", ".map"):
        src, lnk = base + ext, os.path.splitext(dst)[0] + ext
        if os.path.exists(src):
            if os.path.lexists(lnk):
                os.remove(lnk)
            os.symlink(src, lnk)
    sib = os.path.join(os.path.dirname(rom), "pokehns.elf")
    if os.path.exists(sib) and os.path.basename(rom) != "pokehns.gba":
        for ext in (".elf", ".map"):
            src, lnk = os.path.join(os.path.dirname(rom), "pokehns" + ext), os.path.join(out, "pokehns" + ext)
            if os.path.exists(src) and not os.path.lexists(lnk):
                os.symlink(src, lnk)
    print("noflash: %s (IdentifyFlash at %08X)" % (dst, addr))


if __name__ == "__main__":
    main()
