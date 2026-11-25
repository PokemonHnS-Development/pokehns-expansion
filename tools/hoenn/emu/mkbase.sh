#!/bin/bash
# mkbase.sh ROM OUT.ss  (run from the harness directory)
# New game -> debug "Set Party" (Lapras leads; the six know every overworld move)
# -> all badges -> HM-received/Headbutt/Running Shoes flags -> debug menu open.
set -e
ROM=$1; OUT=$2; HERE=$(cd "$(dirname "$0")" && pwd)
ELF=${ROM%.gba}.elf
{ cat "$HERE/new_game_to_debug_menu.txt"; echo "press DOWN 4"; echo "wait 10"; echo "press DOWN 4"; echo "wait 10"; echo "press A 4"; echo "wait 30"; for i in $(seq 9); do echo "press DOWN 4"; echo "wait 8"; done; echo "press A 4"; echo "wait 120"; echo "savestate _mb.ss"; } | timeout 300 ./harness "$ROM" >/dev/null
{ echo "loadstate _mb.ss"; echo "press R+START 6"; echo "wait 40"; for i in $(seq 7); do echo "press DOWN 4"; echo "wait 8"; done; echo "press A 4"; echo "wait 30"; for i in $(seq 10); do echo "press DOWN 4"; echo "wait 8"; done; echo "press A 4"; echo "wait 60"; for i in 1 2 3; do echo "press B 4"; echo "wait 25"; done; echo "savestate _mb2.ss"; } | timeout 200 ./harness "$ROM" >/dev/null
# SaveBlock1 flags: offsetof(struct SaveBlock1, flags) = 0x198C (2.0.6). HnS flags 0x1F5-0x1F9 (HMs), 0x1FD (shoes), 0x200 (Headbutt).
SB1=$(arm-none-eabi-nm "$ELF" | awk '$3=="gSaveBlock1Ptr"{print $1}')
P=$({ echo "loadstate _mb2.ss"; echo "r32 $SB1"; } | ./harness "$ROM" | awk -F': ' '/:/{print $2}')
F=$(python3 -c "print(hex(int('$P',16)+0x198C)[2:])")
B=$({ echo "loadstate _mb2.ss"; for o in 3e 3f 40; do echo "r8 $(python3 -c "print(hex(0x$F+0x$o)[2:])")"; done; } | ./harness "$ROM" | awk -F': ' '/:/{print $2}' | tr '\n' ' ')
python3 - "$F" "$OUT" $B > _mb.txt <<'PY'
import sys
f=int(sys.argv[1],16); cur=[int(x,16) for x in sys.argv[3:6]]
c=["loadstate _mb2.ss"]
for (off,bits),v in zip(((0x3E,0xE0),(0x3F,0x23),(0x40,0x01)),cur):
    c.append(f"w8 {f+off:x} {v|bits}")
c+=["wait 10","press R+START 6","wait 40",f"savestate {sys.argv[2]}"]
print("\n".join(c))
PY
timeout 100 ./harness "$ROM" < _mb.txt >/dev/null
