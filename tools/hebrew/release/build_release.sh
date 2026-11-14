#!/bin/bash
# Clean release build of one commit in its own worktree, plus the clip-report build of the same commit.
#
#   build_release.sh COMMIT OUTDIR           build COMMIT and copy the release files to OUTDIR
#   build_release.sh --check COMMIT OUTDIR   check the inputs only; change nothing
#   build_release.sh --help
#
# OUTDIR gets pokehns.gba/.elf/.map, pokehns-clip.gba/.elf/.map, build.log, build_clip.log, gbafix.log
# and build_info.json (the commit, and size, SHA-1 and CRC32 of both ROMs).
#
# Environment (an empty variable counts as unset):
#   HNS_RELEASE_WORKTREE  the worktree the release is built in. A worktree already there is
#                         removed first (git worktree remove --force), so nothing else may live
#                         there.                        default: ../pokehns-release next to the repository
#   HNS_JOBS              make -j                      default: 12
#   DEVKITPRO, DEVKITARM  the toolchain                default: /opt/devkitpro, $DEVKITPRO/devkitARM
#   CPATH, LIBRARY_PATH   headers and libraries of the host tools (libpng)
#                                                      default: /opt/homebrew/include, /opt/homebrew/lib
set -euo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO="$(cd "$HERE/../../.." && pwd)"
USAGE="usage: build_release.sh [--check] COMMIT OUTDIR   (--help for details)"

help() { awk 'NR > 1 && /^#/ { sub(/^# ?/, ""); print; next } NR > 1 { exit }' "$0"; }
die() { echo "build_release.sh: $*" >&2; exit 2; }

CHECK=0
case "${1:-}" in
  -h|--help) help; exit 0 ;;
  --check) CHECK=1; shift ;;
esac
[ $# -eq 2 ] || { echo "$USAGE" >&2; exit 2; }
COMMIT=$1; OUT=$2
case "$OUT" in /*) ;; *) OUT="$PWD/$OUT" ;; esac

WT="${HNS_RELEASE_WORKTREE:-$(dirname "$REPO")/pokehns-release}"
case "$WT" in /*) ;; *) WT="$PWD/$WT" ;; esac
JOBS="${HNS_JOBS:-12}"
export DEVKITPRO="${DEVKITPRO:-/opt/devkitpro}"
export DEVKITARM="${DEVKITARM:-$DEVKITPRO/devkitARM}"
export CPATH="${CPATH:-/opt/homebrew/include}"
export LIBRARY_PATH="${LIBRARY_PATH:-/opt/homebrew/lib}"

# -- inputs, before anything is changed
for t in git make python3; do command -v "$t" >/dev/null || die "$t is not on PATH"; done
git -C "$REPO" rev-parse --git-dir >/dev/null 2>&1 || die "$REPO is not a git repository"
SHA="$(git -C "$REPO" rev-parse --verify --quiet "$COMMIT^{commit}")" || die "$COMMIT is not a commit of $REPO"
[ -x "$DEVKITARM/bin/arm-none-eabi-gcc" ] || die "no $DEVKITARM/bin/arm-none-eabi-gcc: install devkitARM or set DEVKITPRO/DEVKITARM"
case "$JOBS" in ''|*[!0-9]*) die "HNS_JOBS=$JOBS is not a number" ;; esac
[ "$WT" != "$REPO" ] || die "HNS_RELEASE_WORKTREE is this repository; point it at a separate folder"
WT_STATE="absent: it will be created"
if [ -e "$WT" ]; then
  [ -d "$WT" ] || die "HNS_RELEASE_WORKTREE=$WT is not a directory"
  WT_REAL="$(cd "$WT" && pwd -P)"
  WTS="$(git -C "$REPO" worktree list --porcelain)"
  grep -qxF -e "worktree $WT" -e "worktree $WT_REAL" <<< "$WTS" \
    || die "HNS_RELEASE_WORKTREE=$WT exists and is not a worktree of $REPO; move it or point HNS_RELEASE_WORKTREE elsewhere"
  WT_STATE="a worktree at $(git -C "$WT" rev-parse --short HEAD 2>/dev/null || echo '?'): it will be removed and re-created"
fi
[ ! -e "$OUT" ] || [ -d "$OUT" ] || die "OUTDIR $OUT exists and is not a directory"

if [ $CHECK = 1 ]; then
  echo "commit     $SHA ($COMMIT)"
  echo "worktree   $WT ($WT_STATE)"
  echo "output     $OUT"
  echo "toolchain  $("$DEVKITARM/bin/arm-none-eabi-gcc" --version | head -1), make -j$JOBS"
  echo "inputs OK"
  exit 0
fi

mkdir -p "$OUT"
if [ -d "$WT" ]; then git -C "$REPO" worktree remove --force "$WT"; fi
git -C "$REPO" worktree add --detach "$WT" "$COMMIT"
cd "$WT"
test -z "$(git status --porcelain)" || { echo "worktree not clean"; exit 1; }
make clean >/dev/null 2>&1 || true
make hns -j"$JOBS" > "$OUT/build.log" 2>&1
cp pokehns.gba "$OUT/pokehns.gba"; cp pokehns.elf "$OUT/pokehns.elf"; cp pokehns.map "$OUT/pokehns.map"
# The build runs gbafix; running it again on a copy must not change a byte.
cp pokehns.gba "$OUT/gbafix_check.gba"; tools/gbafix/gbafix "$OUT/gbafix_check.gba" > "$OUT/gbafix.log" 2>&1
cmp -s pokehns.gba "$OUT/gbafix_check.gba" && echo "gbafix: header already valid" >> "$OUT/gbafix.log" || echo "gbafix: HEADER CHANGED" >> "$OUT/gbafix.log"
rm -f "$OUT/gbafix_check.gba"
make hns RTL_CLIP_REPORT=1 -j"$JOBS" > "$OUT/build_clip.log" 2>&1
cp pokehns-clip.gba pokehns-clip.elf pokehns-clip.map "$OUT/" 2>/dev/null || cp build/hns-clip/*.gba "$OUT/"
python3 - "$OUT" "$COMMIT" "$(git rev-parse HEAD)" <<'PY'
import hashlib, zlib, os, sys, json
out, ref, sha = sys.argv[1:4]
info = {'commit': sha, 'ref': ref}
for f in ('pokehns.gba', 'pokehns-clip.gba'):
    p = os.path.join(out, f)
    if os.path.exists(p):
        b = open(p, 'rb').read()
        info[f] = {'size': len(b), 'sha1': hashlib.sha1(b).hexdigest(), 'crc32': '%08X' % (zlib.crc32(b) & 0xffffffff)}
json.dump(info, open(os.path.join(out, 'build_info.json'), 'w'), indent=1)
print(json.dumps(info, indent=1))
PY
tail -1 "$OUT/gbafix.log"
