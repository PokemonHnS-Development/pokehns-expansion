#!/bin/bash
# Every harness test on the exact release files of one release candidate.
#
#   run_release_tests.sh RCDIR           run every test; logs and output in RCDIR/tests
#   run_release_tests.sh --check RCDIR   check the inputs only; run nothing
#   run_release_tests.sh --help
#
# RCDIR comes from build_release.sh (pokehns.gba/.elf, pokehns-clip.gba/.elf, build_info.json).
# The harness reads the source tree next to the ROM (the ELF, data/maps), so the tests run on the
# copies in the release worktree, which must be byte-identical to the files in RCDIR. Steps: screen
# tours, clip-report tours, dialogue sweep, harness self-check, save ladder, map walk, cross-core
# frames, ROM sweep. A failing step does not stop the later ones: read the logs. macOS only (the
# libretro cores are .dylib files). The cross-core step builds its libretro frontend from
# $HNS_EMU/crosscore.c with cc into RCDIR/tests/bin on every run, so its table always comes from
# that source.
#
# Environment (an empty variable counts as unset; tools/hebrew/paths.py resolves the ones it knows):
#   HNS_RELEASE_WORKTREE  the worktree build_release.sh built in   default: ../pokehns-release
#   HNS_EMU               the harness                              default: tools/hebrew/emu
#   HNS_SAVES             the save ladder, ladder1_newgame.sav ... ladder6_postgame.sav   no default
#   HNS_RUNNER            the hnsrun binary (emu/README.md)        default: tools/hebrew/emu/hnsrun
#   HNS_UNITS             unit chunks the sweep takes its labels from (make_chunks.py all)
#                                                                  default: $HNS_WORK/units
#   HNS_EN_ROM            English ROM for the ROM sweep, its .elf next to it
#                                                                  default: ../pokehns-en/pokehns.gba
#   HNS_CORES             vbam, vba_next, gpsp, mednafen_gba and skyemu _libretro.dylib
#                                                                  default: $HNS_WORK/cores
#   HNS_MGBA_CORE         RetroArch's mGBA core
#                         default: ~/Library/Application Support/RetroArch/cores/mgba_libretro.dylib
#   HNS_WORK              scratch folder (paths.py)                default: build/hebrew
#   DEVKITARM             arm-none-eabi-readelf/nm for the ELF     default: /opt/devkitpro/devkitARM
set -uo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TOOLS="$(dirname "$HERE")"
USAGE="usage: run_release_tests.sh [--check] RCDIR   (--help for details)"

help() { awk 'NR > 1 && /^#/ { sub(/^# ?/, ""); print; next } NR > 1 { exit }' "$0"; }

CHECK=0
case "${1:-}" in
  -h|--help) help; exit 0 ;;
  --check) CHECK=1; shift ;;
esac
[ $# -eq 1 ] || { echo "$USAGE" >&2; exit 2; }
command -v python3 >/dev/null || { echo "run_release_tests.sh: python3 is not on PATH" >&2; exit 2; }
RC=$1
[ -d "$RC" ] || { echo "run_release_tests.sh: RCDIR $RC is not a directory" >&2; echo "$USAGE" >&2; exit 2; }
RC="$(cd "$RC" && pwd)"
OUT=$RC/tests

p() { python3 "$TOOLS/paths.py" "$1" 2>/dev/null; }
abs() { case "$1" in /*) printf '%s' "$1" ;; *) printf '%s/%s' "$PWD" "$1" ;; esac; }
REPO="$(p REPO)"; WORK="$(p WORK)"
WT="$(abs "${HNS_RELEASE_WORKTREE:-$(dirname "$REPO")/pokehns-release}")"
EMU="$(abs "${HNS_EMU:-$TOOLS/emu}")"
SAVES="$(p SAVES)" || SAVES=""
RUNNER="$(p RUNNER)" || RUNNER=""
UNITS="$(p UNITS)" || UNITS=""
EN_ROM="$(p EN_ROM)" || EN_ROM=""
CROSSCORE=$OUT/bin/crosscore
C="$(abs "${HNS_CORES:-$WORK/cores}")"
RA="$(abs "${HNS_MGBA_CORE:-$HOME/Library/Application Support/RetroArch/cores/mgba_libretro.dylib}")"
export DEVKITARM="${DEVKITARM:-/opt/devkitpro/devkitARM}"
export HNS_SAVES="$SAVES" HNS_RUNNER="$RUNNER" HNS_UNITS="$UNITS"
# The harness reads the source tree next to the ROM, so it runs the worktree copies, which must be
# byte-identical to the release files.
ROM=$WT/pokehns.gba; CLIP=$WT/pokehns-clip.gba

# -- inputs: every problem is listed, then the script stops before running anything
bad=()
need_file() { [ -f "$1" ] || bad+=("missing $1 ($2)"); }
for f in pokehns.gba pokehns-clip.gba build_info.json; do need_file "$RC/$f" "build_release.sh writes it"; done
if [ -d "$WT" ]; then
  for f in pokehns.gba pokehns.elf pokehns-clip.gba pokehns-clip.elf; do need_file "$WT/$f" "build_release.sh builds it in the worktree"; done
  if [ -f "$ROM" ] && [ -f "$CLIP" ] && [ -f "$RC/pokehns.gba" ] && [ -f "$RC/pokehns-clip.gba" ]; then
    cmp -s "$ROM" "$RC/pokehns.gba" && cmp -s "$CLIP" "$RC/pokehns-clip.gba" || bad+=("worktree ROMs differ from the release files")
  fi
  if [ -f "$RC/build_info.json" ]; then
    want="$(python3 -c 'import json,sys; print(json.load(open(sys.argv[1]))["commit"])' "$RC/build_info.json" 2>/dev/null)"
    have="$(git -C "$WT" rev-parse HEAD 2>/dev/null)"
    [ -n "$want" ] && [ "$want" = "$have" ] || bad+=("the worktree $WT is at ${have:-?}, build_info.json says ${want:-?}")
  fi
else
  bad+=("no release worktree $WT (build_release.sh makes it; HNS_RELEASE_WORKTREE points elsewhere)")
fi
for f in hns.py sweep.py ladder.py mapwalk.py scripts/ladder_validate.txt scripts/ladder_validate_newgame.txt; do
  need_file "$EMU/$f" "the harness, HNS_EMU"
done
if [ -z "$SAVES" ]; then
  bad+=("HNS_SAVES is not set (the save ladder; emu/scripts/make_ladder.sh builds it)")
else
  for n in ladder1_newgame ladder2_badge1 ladder3_ecruteak ladder4_league ladder5_kanto ladder6_postgame; do
    need_file "$SAVES/$n.sav" "the save ladder, HNS_SAVES"
  done
fi
[ -x "$RUNNER" ] || bad+=("no hnsrun at ${RUNNER:-?} (build it from emu/hnsrun.c, emu/README.md; or set HNS_RUNNER)")
ls "$UNITS"/*/*.json >/dev/null 2>&1 || bad+=("no unit chunks in ${UNITS:-?} (python3 tools/hebrew/make_chunks.py all; or set HNS_UNITS)")
[ -x "$DEVKITARM/bin/arm-none-eabi-readelf" ] || bad+=("no $DEVKITARM/bin/arm-none-eabi-readelf (set DEVKITARM)")
if [ -z "$EN_ROM" ]; then
  bad+=("no English ROM (set HNS_EN_ROM, or HNS_UPSTREAM to the English tree)")
else
  need_file "$EN_ROM" "the English ROM, HNS_EN_ROM"; need_file "${EN_ROM%.gba}.elf" "the English ELF, next to HNS_EN_ROM"
fi
need_file "$EMU/crosscore.c" "the cross-core frontend's source, HNS_EMU"
command -v cc >/dev/null || bad+=("no C compiler cc on PATH (the cross-core step builds emu/crosscore.c)")
for core in vbam vba_next gpsp mednafen_gba skyemu; do need_file "$C/${core}_libretro.dylib" "a libretro core, HNS_CORES"; done
need_file "$RA" "RetroArch's mGBA core, HNS_MGBA_CORE"
need_file "$HERE/crosscore_menus.txt" "the cross-core input script"
need_file "$HERE/ccdiff.py" "the cross-core frame diff"
need_file "$TOOLS/rom_sweep.py" "part of tools/hebrew"
if [ ${#bad[@]} -gt 0 ]; then
  for b in "${bad[@]}"; do echo "run_release_tests.sh: $b" >&2; done
  echo "$USAGE" >&2
  exit 2
fi
if [ $CHECK = 1 ]; then
  echo "release    $RC (output in $OUT)"
  echo "worktree   $WT"
  echo "harness    $EMU, runner $RUNNER"
  echo "saves      $SAVES"
  echo "units      $UNITS"
  echo "English    $EN_ROM"
  echo "crosscore  built from $EMU/crosscore.c into $CROSSCORE, cores in $C, mGBA $RA"
  echo "inputs OK"
  exit 0
fi

mkdir -p "$OUT"; cd "$EMU"
echo "== tours";      python3 hns.py --rom "$ROM" tour "$ROM" "$OUT/tours" > "$OUT/tours.log" 2>&1; tail -1 "$OUT/tours.log"
echo "== clip tours"; python3 hns.py --rom "$CLIP" tour "$CLIP" "$OUT/tours_clip" --clip > "$OUT/tours_clip.log" 2>&1; tail -1 "$OUT/tours_clip.log"
echo "== sweep";      python3 sweep.py run "$CLIP" "$OUT/sweep" --save "$SAVES/ladder4_league.sav" --shots clip > "$OUT/sweep.log" 2>&1; grep "totals" "$OUT/sweep.log" | tail -1
echo "== selfcheck";  python3 hns.py --rom "$ROM" selfcheck --save "$SAVES/ladder4_league.sav" > "$OUT/selfcheck.log" 2>&1; tail -1 "$OUT/selfcheck.log"
echo "== ladder"
# Rung 1 is a new game saved in the bedroom (no Center, Pokedex or party yet), so it has its own
# validation script. Each log ends in the script's exit status, which make_testing_md.py checks.
for s in "$SAVES"/ladder*.sav; do
  n=$(basename "$s" .sav); v=scripts/ladder_validate.txt
  [ "$n" = ladder1_newgame ] && v=scripts/ladder_validate_newgame.txt
  python3 ladder.py --rom "$ROM" run "$v" "$OUT/ladder/$n" --save "$s" > "$OUT/ladder_$n.log" 2>&1; rc=$?
  echo "exit $rc" >> "$OUT/ladder_$n.log"
  echo "  $n exit $rc $(ls "$OUT/ladder/$n" 2>/dev/null | grep -c png) shots"
done
echo "== map walk";   python3 mapwalk.py "$ROM" "$SAVES/ladder6_postgame.sav" "$OUT/mapwalk" > "$OUT/mapwalk.log" 2>&1; tail -1 "$OUT/mapwalk.log"
echo "== cross-core"
rm -f "$OUT/crosscore.txt"; mkdir -p "$OUT/bin"
if cc -O2 "$EMU/crosscore.c" -o "$CROSSCORE" > "$OUT/crosscore_build.log" 2>&1; then
  for core in mgba vbam vba_next gpsp mednafen_gba skyemu; do
    dl="$C/${core}_libretro.dylib"; [ $core = mgba ] && dl="$RA"
    d="$OUT/crosscore/$core"; rm -rf "$d"; mkdir -p "$d"; cp "$SAVES/ladder4_league.sav" "$d/save.sav"
    (cd "$d" && "$CROSSCORE" "$dl" "$ROM" "$d" "$d/save.sav" < "$HERE/crosscore_menus.txt" > "$d/log.txt" 2>&1); echo "  $core exit $?"
  done
  (cd "$OUT/crosscore" && python3 "$HERE/ccdiff.py" mgba vbam vba_next gpsp mednafen_gba skyemu) > "$OUT/crosscore.txt" 2>&1; cat "$OUT/crosscore.txt"
else
  echo "  the frontend did not build, so there is no crosscore.txt: $OUT/crosscore_build.log"
fi
echo "== rom sweep";  python3 "$TOOLS/rom_sweep.py" "$ROM" --en "$EN_ROM" > "$OUT/rom_sweep.txt" 2>&1; tail -5 "$OUT/rom_sweep.txt"
echo "done"
