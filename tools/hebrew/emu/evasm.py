#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Assemble a Heart & Soul event script (the real `data/` script language) for RAM and
run it in the live game.

    evasm.py asm SCRIPT.inc [--addr HEX]     assemble, print the bytes and the symbols used

A script file is the body of an event script, written exactly like a map's scripts.inc:

    setflag FLAG_BADGE01_GET
    givemon SPECIES_CYNDAQUIL, 14, move1=MOVE_EMBER
    additem ITEM_POTION, 5
    special EnableNationalPokedex
    end

It is assembled with the SOURCE TREE's own macros and constants, through the same pipeline
the Makefile uses for data/*.s (preproc | cpp | preproc -ie | as; Makefile:538), then
linked at a RAM address with the built ELF as a symbol table (ld -R), so `callnative X`,
`special X` (SPECIAL_X is a global absolute symbol made by data/specials.inc) and every
SCR_OP_/FLAG_/VAR_/ITEM_/SPECIES_/MOVE_ constant resolve exactly as in the ROM.

Nothing is written into the source tree: the host tools (preproc, mapjson, jsonproc) are
built from its sources into SCRATCH/bin, and the headers `make` would generate
(map_groups.h, layouts.h, map_event_ids.h, heal_locations.h, region_map_sections.h) are
generated into SCRATCH/trees/<one folder per source tree>/gen from COPIES of the map JSON.
SCRATCH is HNS_EVASM_SCRATCH, default $HNS_WORK/evasm. The source tree is the one next to
the ELF (HNS_SRC overrides it).

Running (Emu.run_event in hns.py): the bytes go into gRfuAPIBuffer, the wireless adapter's
work area (src/link_rfu_2.c:80), which nothing touches unless a wireless link is started
(rfu_initializeAPI, src/link_rfu_2.c:331). Then the global script context is pointed at
them exactly as ScriptContext_SetupScript does (src/script.c:281-289): mode BYTECODE,
scriptPtr, stackDepth 0, field controls locked, status CONTEXT_RUNNING. CB1_Overworld runs
it on the next frame. Scripts may use waitstate, warps, specials, givemon, etc.
"""
import hashlib
import os
import re
import shutil
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))
import paths  # noqa: E402

SRC = os.environ.get("HNS_SRC") or paths.TREE
SCRATCH = os.environ.get("HNS_EVASM_SCRATCH") or os.path.join(paths.WORK, "evasm")
DEVKITARM = os.environ.get("DEVKITARM", "/opt/devkitpro/devkitARM")
BIN = os.path.join(DEVKITARM, "bin")
CPP = shutil.which("arm-none-eabi-cpp") or os.path.join(BIN, "arm-none-eabi-cpp")
AS = os.path.join(BIN, "arm-none-eabi-as")
LD = os.path.join(BIN, "arm-none-eabi-ld")
OBJCOPY = os.path.join(BIN, "arm-none-eabi-objcopy")
NM = os.path.join(BIN, "arm-none-eabi-nm")

RAM_BUFFER = "gRfuAPIBuffer"
# CPPFLAGS for `make hns` (Makefile:168, GAME_VERSION POKEMON_HNS) and ASFLAGS (Makefile:157)
CPPFLAGS = ["-Wno-trigraphs", "-DMODERN=1", "-DTESTING=0", "-DPOKEMON_HNS", "-std=gnu17"]
ASFLAGS = ["-mcpu=arm7tdmi", "-march=armv4t", "-meabi=5", "--defsym", "MODERN=1",
           "--defsym", "POKEMON_HNS=1"]


class EvasmError(Exception):
    pass


def _run(argv, **kw):
    p = subprocess.run(argv, capture_output=True, text=True, **kw)
    if p.returncode:
        raise EvasmError("%s failed (%d):\n%s%s" % (os.path.basename(argv[0]), p.returncode,
                                                     p.stdout[-3000:], p.stderr[-3000:]))
    return p.stdout


def _tool(name, sources, extra=()):
    out = os.path.join(SCRATCH, "bin", name)
    if not os.path.exists(out):
        os.makedirs(os.path.dirname(out), exist_ok=True)
        _run(["c++", "-std=c++17", "-O2"] + list(extra) + sources + ["-o", out])
    return out


def prepare(src=SRC):
    """Build the host tools and generate the headers `make` would, once per source tree.
    Returns the gen include dir."""
    src = os.path.abspath(src)
    # one folder per tree, so a run on another tree never picks up this tree's headers
    tree = os.path.join(SCRATCH, "trees", hashlib.sha1(src.encode()).hexdigest()[:12])
    gen = os.path.join(tree, "gen")
    stamp = os.path.join(gen, ".stamp")
    if os.path.exists(stamp):
        return os.path.join(gen, "include")
    t = os.path.join(src, "tools")
    preproc = _tool("preproc", [os.path.join(t, "preproc", f) for f in os.listdir(os.path.join(t, "preproc"))
                               if f.endswith(".cpp")])
    mapjson = _tool("mapjson", [os.path.join(t, "mapjson", "mapjson.cpp"), os.path.join(t, "mapjson", "json11.cpp")])
    jsonproc = _tool("jsonproc", [os.path.join(t, "jsonproc", "jsonproc.cpp")], ["-I", os.path.join(t, "jsonproc")])
    del preproc
    consts = os.path.join(gen, "include", "constants")
    os.makedirs(consts, exist_ok=True)
    # mapjson writes map_group_count.h next to <map_groups.json>/../../src/data, so it
    # only ever sees copies of the JSON.
    jdir = os.path.join(tree, "json")
    if os.path.exists(jdir):
        shutil.rmtree(jdir)
    shutil.copytree(os.path.join(src, "data", "maps"), os.path.join(jdir, "data", "maps"),
                    ignore=lambda d, names: [n for n in names if not (n.endswith(".json") or
                                                                      os.path.isdir(os.path.join(d, n)))])
    os.makedirs(os.path.join(jdir, "src", "data"), exist_ok=True)
    maps = sorted(os.path.join(jdir, "data", "maps", d, "map.json")
                  for d in os.listdir(os.path.join(jdir, "data", "maps"))
                  if os.path.exists(os.path.join(jdir, "data", "maps", d, "map.json")))
    asmout = os.path.join(gen, "asm")
    os.makedirs(asmout, exist_ok=True)
    # mapjson `groups` works relative to the cwd: it reads tools/mapjson/required_map_defines.json
    # and rewrites src/data/heal_locations.json, so it runs on copies in the scratch dir.
    os.makedirs(os.path.join(jdir, "tools", "mapjson"), exist_ok=True)
    shutil.copyfile(os.path.join(t, "mapjson", "required_map_defines.json"),
                    os.path.join(jdir, "tools", "mapjson", "required_map_defines.json"))
    heal = os.path.join(jdir, "src", "data", "heal_locations.json")
    shutil.copyfile(os.path.join(src, "src", "data", "heal_locations.json"), heal)
    _run([mapjson, "groups", "hns", os.path.join(jdir, "data", "maps", "map_groups.json")] + maps + [asmout, consts], cwd=jdir)
    _run([mapjson, "layouts", "hns", os.path.join(src, "data", "layouts", "layouts.json"), asmout, consts], cwd=src)
    _run([mapjson, "event_constants", "emerald"] + maps + [os.path.join(consts, "map_event_ids.h")], cwd=src)
    rm = os.path.join(src, "src", "data", "region_map")
    _run([jsonproc, os.path.join(rm, "region_map_sections.json"),
          os.path.join(rm, "region_map_sections.constants.json.txt"), os.path.join(consts, "region_map_sections.h")])
    _run([jsonproc, heal,
          os.path.join(src, "src", "data", "heal_locations.constants.json.txt"), os.path.join(consts, "heal_locations.h")])
    open(stamp, "w").write(src + "\n")
    return os.path.join(gen, "include")


def preamble(src=SRC):
    """The #include/.include block at the top of data/event_scripts.s, verbatim, so the
    script sees exactly the constants and macros the ROM's own scripts see."""
    out = []
    for line in open(os.path.join(src, "data", "event_scripts.s"), encoding="utf-8"):
        out.append(line)
        if "constants/constants.inc" in line:
            return "".join(out)
    raise EvasmError("data/event_scripts.s: preamble end (constants/constants.inc) not found")


def assemble(body, addr, elf, src=SRC, name="event", incdirs=()):
    """Assemble BODY (event script text) to run at ADDR. Returns (bytes, symbols) where
    symbols maps the script's own labels to addresses. INCDIRS are searched by
    `#include "file.inc"` (cpp), so a script can include shared story steps."""
    geninc = prepare(src)
    deps = []                     # every .inc an #include could reach (cache key only)
    for d in incdirs:
        for fn in sorted(os.listdir(d)):
            if fn.endswith(".inc"):
                deps.append(fn + open(os.path.join(d, fn), encoding="utf-8").read())
    key = hashlib.sha1(("%s\n%08X\n%s\n%s\n%s" % (src, addr, os.path.getmtime(elf), body, "\n".join(deps))).encode()).hexdigest()[:16]
    work = os.path.join(SCRATCH, "build", "%s_%s" % (re.sub(r"\W", "_", name), key))
    binf = os.path.join(work, "out.bin")
    if not os.path.exists(binf):
        os.makedirs(work, exist_ok=True)
        s = os.path.join(work, "event.s")
        with open(s, "w", encoding="utf-8") as f:
            f.write(preamble(src))
            f.write("\n\t.section .data\n\t.align 2\n\t.global EvasmEntry\nEvasmEntry:\n")
            f.write(body)
            f.write("\n")
        preproc = os.path.join(SCRATCH, "bin", "preproc")
        charmap = os.path.join(src, "charmap.txt")
        cppargs = [CPP, "-iquote", os.path.join(src, "include"), "-iquote", geninc,
                   "-iquote", os.path.join(geninc, "constants"), "-I", os.path.join(src, "include")] + \
            sum([["-I", d] for d in incdirs], []) + CPPFLAGS + ["-"]
        p1 = subprocess.run([preproc, s, charmap], capture_output=True, cwd=src)
        if p1.returncode:
            raise EvasmError("preproc: " + p1.stderr.decode(errors="replace"))
        p2 = subprocess.run(cppargs, input=p1.stdout, capture_output=True, cwd=src)
        if p2.returncode:
            raise EvasmError("cpp: " + p2.stderr.decode(errors="replace")[-3000:])
        p3 = subprocess.run([preproc, "-ie", s, charmap], input=p2.stdout, capture_output=True, cwd=src)
        if p3.returncode:
            raise EvasmError("preproc -ie: " + p3.stderr.decode(errors="replace")[-3000:])
        pp = os.path.join(work, "event.pp.s")
        open(pp, "wb").write(p3.stdout)
        obj = os.path.join(work, "event.o")
        _run([AS] + ASFLAGS + ["-I", src, "-o", obj, pp], cwd=src)
        ld = os.path.join(work, "ram.ld")
        open(ld, "w").write("SECTIONS { . = 0x%08X; .data : { *(.data) } "
                            "/DISCARD/ : { *(.text) *(.bss) *(.ARM.attributes) *(.comment) } }\n" % addr)
        lelf = os.path.join(work, "event.elf")
        _run([LD, "-T", ld, "-R", elf, "-o", lelf, obj])
        _run([OBJCOPY, "-O", "binary", "-j", ".data", lelf, binf])
        syms = {}
        objsyms = _run([NM, obj])
        mine = {l.split()[-1] for l in objsyms.splitlines() if len(l.split()) == 3 and l.split()[1] in "dDtT"}
        for l in _run([NM, lelf]).splitlines():
            f = l.split()
            if len(f) == 3 and f[2] in mine:
                syms[f[2]] = int(f[0], 16)
        open(os.path.join(work, "syms.txt"), "w").write("".join("%s %08X\n" % kv for kv in sorted(syms.items())))
    data = open(binf, "rb").read()
    syms = {}
    for l in open(os.path.join(work, "syms.txt")):
        n, v = l.split()
        syms[n] = int(v, 16)
    return data, syms


def main():
    import argparse
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=["asm"])
    ap.add_argument("script")
    ap.add_argument("--addr", default=None)
    ap.add_argument("--elf", default=os.environ.get("HNS_ELF") or os.path.splitext(paths.ROM)[0] + ".elf")
    a = ap.parse_args()
    sys.path.insert(0, HERE)
    import hns
    elf = hns.Elf(a.elf)
    addr = int(a.addr, 16) if a.addr else elf.sym(RAM_BUFFER)
    data, syms = assemble(open(a.script, encoding="utf-8").read(), addr, a.elf, src=hns.src_dir(elf),
                          name=os.path.basename(a.script))
    print("%d bytes at %08X (buffer %s is %d bytes)" % (len(data), addr, RAM_BUFFER, elf.size(RAM_BUFFER)))
    for n, v in sorted(syms.items(), key=lambda kv: kv[1]):
        print("  %08X %s" % (v, n))
    for i in range(0, len(data), 16):
        print("  %08X: %s" % (addr + i, data[i:i + 16].hex(" ")))


if __name__ == "__main__":
    main()
