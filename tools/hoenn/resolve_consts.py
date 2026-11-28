#!/usr/bin/env python3
"""Resolve C constants as the HnS build sees them (uses the real compiler).
    resolve_consts.py NAME [NAME ...]   -> prints NAME=VALUE (or NAME=UNDEF)
Imported by other tools/hoenn scripts via resolve(names)."""
import os, re, subprocess, sys, tempfile
ROOT = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))

def resolve(names, extra_defines=("POKEMON_HNS",)):
    names = sorted(set(names))
    src = ['#include "global.h"', '#include "constants/flags.h"', '#include "constants/vars.h"',
           '#include "constants/opponents.h"', '#include "constants/items.h"']
    for i, n in enumerate(names):
        src += [f"#ifdef {n}", f"const int hoenn_c_{i} = ({n});", "#else", f"const int hoenn_c_{i} = -0x7fffffff;", "#endif"]
    with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False) as f:
        f.write("\n".join(src) + "\n"); path = f.name
    cmd = ["arm-none-eabi-gcc", "-mthumb", "-mcpu=arm7tdmi", "-mabi=apcs-gnu", "-std=gnu17", "-S", "-O0",
           "-iquote", "include", "-DMODERN=1", "-DTESTING=0", "-o", "-", path] + [f"-D{d}" for d in extra_defines]
    out = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True)
    os.unlink(path)
    if out.returncode:
        sys.exit(out.stderr[-3000:])
    vals = {}
    for m in re.finditer(r"^hoenn_c_(\d+):\s*\n\s*\.(word|space)\s+(-?\d+)", out.stdout, re.M):
        v = int(m.group(3)) if m.group(2) == "word" else 0
        vals[names[int(m.group(1))]] = None if v == -0x7fffffff else v
    return vals

if __name__ == "__main__":
    for k, v in resolve(sys.argv[1:]).items():
        print(f"{k}={'UNDEF' if v is None else hex(v)}")
