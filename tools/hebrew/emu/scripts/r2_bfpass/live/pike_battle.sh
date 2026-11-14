#!/bin/bash
# pike_battle.sh SESSION TYPE PREFIX: like pike_room.sh for a battle room: drive the intro to
# the battle, win it (bwin), drive the text after it.
S=$1; T=$2; P=$3
../hns-tools/scratch/screens/r2_battle_frontier_pass_bp_and_remaining_facilities/tools/s $S <<EOT
waitctl 600
py: sb2 = emu.sb2(); emu.w8(sb2 + 0xE10, (emu.r8(sb2 + 0xE10) & 0x80) | ($T << 3) | 1); print("hint", hex(emu.r8(sb2 + 0xE10)))
go UP 6
py: emu.frames(8, "UP"); emu.wait_until(lambda: emu.r8(emu.sb1() + 9) != 67 or emu.wants_key(), 900, "the room", step=2); print("in room", emu.location())
drivex ${P}_in battle 30 9000
fastbattles off
bwin ${P}_b
drivex ${P}_after free 30 9000
loc
EOT
