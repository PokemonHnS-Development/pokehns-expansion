#!/bin/bash
# One-time setup for a new session: build the headless mGBA harness and a working
# folder next to the repo, then a debug ROM and a fresh Hoenn save.
#   tools/hoenn/emu/setup.sh [HARNESS_DIR]     (default: ~/emu)
# Afterwards: cd ~/emu, and use pt.py (see playtest/README.md).
set -e
REPO=$(cd "$(dirname "$0")/../../.." && pwd)
DIR=${1:-$HOME/emu}
mkdir -p "$DIR/pt"
if ! [ -x "$DIR/harness" ]; then
  dpkg -s libmgba-dev >/dev/null 2>&1 || sudo apt-get install -y libmgba-dev libpng-dev
  gcc -O2 -o "$DIR/harness" "$REPO/tools/hoenn/emu/harness.c" -lmgba -lpng
fi
cd "$REPO"
[ -f pokehns.gba ] || make hns -j"$(nproc)"
cp pokehns.gba "$DIR/pt.gba"; cp pokehns.elf "$DIR/pt.elf"
cd "$DIR"
"$REPO/tools/hoenn/emu/mkbase.sh" pt.gba pt/base.ss
python3 - <<PY
import sys; sys.path.insert(0, "$REPO/tools/hoenn/emu")
from pt import *; from pt_sections import *
e = Emu("pt.gba", "pt.elf"); log = []
s = s0_arrival(e, "pt/base.ss", log); s = s1_birch(e, s, log)
print("ready:", s, "(Hoenn save after Oak's ticket, the ferry and Birch's Mudkip)")
PY
