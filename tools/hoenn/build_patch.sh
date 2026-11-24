#!/usr/bin/env bash
# Build Hoenn & Seek (HnS target, release mode) and make a .ups patch
# against an unmodified Pokemon - Emerald Version (U).
#
#   tools/hoenn/build_patch.sh [--debug] [path/to/emerald.gba]
#
# --debug builds without RELEASE=1 (keeps the HnS debug menu, for warping
# during testing). Note: the official HnS 2.0.6 patch is ~397 KB larger than
# our release build and matches a non-release build's size.
# Base ROM defaults to baserom/emerald.gba (git-ignored). Output: dist/
set -euo pipefail
cd "$(dirname "$0")/../.."

MODE=release
if [[ "${1:-}" == "--debug" ]]; then MODE=debug; shift; fi
BASE="${1:-baserom/emerald.gba}"
EMERALD_SHA1="f3ae088181bf583e55daf962a92bb46f4f1d07b7"
NAME="hoenn-and-seek"

if [[ ! -f "$BASE" ]]; then
  echo "error: base ROM not found at '$BASE'." >&2
  echo "Put your own Pokemon - Emerald Version (U) ROM there, or pass its path." >&2
  exit 1
fi
actual=$(sha1sum "$BASE" | cut -d' ' -f1)
if [[ "$actual" != "$EMERALD_SHA1" ]]; then
  echo "error: '$BASE' is not an unmodified Emerald (U) ROM (sha1 $actual)." >&2
  exit 1
fi

if [[ "$MODE" == release ]]; then
  make hns RELEASE=1 -j"$(nproc)"
  ROM=pokehns-release.gba; SUFFIX=""
else
  make hns -j"$(nproc)"
  ROM=pokehns.gba; SUFFIX="-debug"
fi

mkdir -p dist
rev=$(git rev-parse --short HEAD 2>/dev/null || echo unknown)
OUT="dist/${NAME}-${rev}${SUFFIX}.ups"
python3 tools/hoenn/ups.py create "$BASE" "$ROM" "$OUT"
cp "$OUT" "dist/${NAME}-latest${SUFFIX}.ups"
used=$(python3 -c "import sys;b=open(sys.argv[1],'rb').read();print(len(b.rstrip(b'\\xff')))" "$ROM")
echo "ROM:   $ROM  sha1 $(sha1sum "$ROM" | cut -d' ' -f1)"
echo "Used:  $used / 33554432 bytes ($(( (33554432-used)/1024 )) KB free)"
echo "Patch: $OUT"
