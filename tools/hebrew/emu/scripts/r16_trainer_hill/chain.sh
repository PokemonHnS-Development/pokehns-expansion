#!/bin/bash
# chain.sh ROM OUTROOT [normal|vue|all] [--clip]: the Trainer Hill steps of round 16 on one ROM, in order,
# each from the savestate the previous one left (hill16.py run ... --from A --to B). One emulator at a time.
#
# Environment: HNS_SRC (the ROM's tree), HNS_RUNNER, DEVKITARM, HNS_SAVES (saves_all: ladder6_postgame.sav),
# HNS_SAVES_SCREENS (saves_screens: r7/r7_hill_base.sav), HNS_MAX_FRAMES (frame cap per step),
# HNS_STRCOV (string-report ROM only). Logs: OUTROOT/logs/STEP.log. The chain stops at the first failed step.
#
# Normal (r2 steps, from ladder6_postgame.sav): h00 base, h02 entry (Normal tag match), h03 1F, h04 2F,
#   h05 3F, h06 4F, h07 roof.
# Variety, Unique, Expert (r7 steps, from saves_screens r7_hill_base.sav): r7_00_counter (hc), then per
#   mode the entry and 1F-4F and the roof: v0-v5, u0-u5, x0-x5; each mode starts from the previous
#   mode's roof state.
HERE="$(cd "$(dirname "$0")" && pwd)"
S="$HERE/.."
ROM=$1; OUT=$2; WHICH=${3:-all}; CLIP=$4
mkdir -p "$OUT/logs"
step() {   # SCRIPT FROMARG TO
  local scr=$1 frm=$2 to=$3 name
  name=$(basename "$scr" .txt)
  echo "=== $name ($frm -> $to)"
  python3 "$HERE/hill16.py" run "$ROM" "$scr" "$OUT" $frm ${to:+--to $to} $CLIP > "$OUT/logs/$name.log" 2>&1
  grep -E "^(battle2 .*over|ERROR|exit|clip total)" "$OUT/logs/$name.log"
  grep -q "^exit 0" "$OUT/logs/$name.log"
}
if [ "$WHICH" = normal ] || [ "$WHICH" = all ]; then
  H=$S/r2_hill_tents
  step $H/h00_base.txt "--save $HNS_SAVES/ladder6_postgame.sav" h00 &&
  step $H/h02_entry.txt "--from h00" h02 &&
  step $H/h03_1f.txt "--from h02" h03 &&
  step $H/h04_2f.txt "--from h03" h04 &&
  step $H/h05_3f.txt "--from h04" h05 &&
  step $H/h06_4f.txt "--from h05" h06 &&
  step $H/h07_roof.txt "--from h06" h07 || echo "normal chain stopped"
fi
if [ "$WHICH" = vue ] || [ "$WHICH" = all ]; then
  R=$S/r7_hill
  prev=""
  step $R/r7_00_counter.txt "--save $HNS_SAVES_SCREENS/r7/r7_hill_base.sav" hc || { echo "vue chain stopped"; exit 1; }
  prev=hc
  for m in v u x; do
    for s in 0_entry 1_1f 2_2f 3_3f 4_4f 5_roof; do
      st=$m${s%%_*}
      step $R/r7_$m$s.txt "--from $prev" $st || { echo "vue chain stopped at $st"; exit 1; }
      prev=$st
    done
  done
fi
