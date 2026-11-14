#!/bin/bash
# Rebuild the save ladder (rungs 2-6) on the English 2.0.6 ROM and validate every rung.
#   scripts/make_ladder.sh [WORKDIR]     (default: $HNS_WORK/ladder_run)
# Needs HNS_SAVES (the ladder folder: ladder1_newgame.sav is read from it, rungs 2-6 are written
# to it) and the English ROM (HNS_EN_ROM, default pokehns.gba in HNS_UPSTREAM, ELF next to it).
# Rungs 2, 3 and 4 start from ladder 1 (new game, bedroom); 5 starts from 4 and 6 from 5, so the
# real Hall of Fame records made in 4 and 6 are carried forward. Each rung is a battery save made
# in-game inside a Pokemon Center. Deterministic: the same ROM gives byte-identical saves.
# Look at WORKDIR/v*/ screenshots after a run (leave the Center, walk, Pokedex, party, bag, card).
set -euo pipefail
EMU="$(cd "$(dirname "$0")/.." && pwd)"
PATHS="$EMU/../paths.py"
SAVES="$(python3 "$PATHS" SAVES)" || { echo "make_ladder.sh: set HNS_SAVES" >&2; exit 1; }
ROM="$(python3 "$PATHS" EN_ROM)" || { echo "make_ladder.sh: set HNS_EN_ROM" >&2; exit 1; }
WORK="${1:-$(python3 "$PATHS" WORK)/ladder_run}"
cd "$EMU"
mkdir -p "$WORK"
run() { echo "== $*"; python3 ladder.py --rom "$ROM" run "$@" > "$WORK/$(basename "$2").log" 2>&1 || { tail -20 "$WORK/$(basename "$2").log"; exit 1; }; }
run scripts/ladder2_badge1.txt   "$WORK/l2" --save "$SAVES/ladder1_newgame.sav" --save-out "$SAVES/ladder2_badge1.sav"
run scripts/ladder3_ecruteak.txt "$WORK/l3" --save "$SAVES/ladder1_newgame.sav" --save-out "$SAVES/ladder3_ecruteak.sav"
run scripts/ladder4_league.txt   "$WORK/l4" --save "$SAVES/ladder1_newgame.sav" --save-out "$SAVES/ladder4_league.sav"
run scripts/ladder5_kanto.txt    "$WORK/l5" --save "$SAVES/ladder4_league.sav"  --save-out "$SAVES/ladder5_kanto.sav"
run scripts/ladder6_postgame.txt "$WORK/l6" --save "$SAVES/ladder5_kanto.sav"   --save-out "$SAVES/ladder6_postgame.sav"
for s in ladder2_badge1 ladder3_ecruteak ladder4_league ladder5_kanto ladder6_postgame; do
    run scripts/ladder_validate.txt "$WORK/v_$s" --save "$SAVES/$s.sav"
    grep -h "leavecenter\|walk \|startmenu" "$WORK/v_$s.log" | sed "s/^/   $s: /"
done
md5 -q "$SAVES"/ladder[2-6]_*.sav 2>/dev/null || md5sum "$SAVES"/ladder[2-6]_*.sav
