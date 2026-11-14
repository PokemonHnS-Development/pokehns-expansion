#!/bin/bash
# Re-measure the struct offsets hns.py pokes (OFF / SIZES), for when `hns.py selfcheck`
# reports a size change. Compiles probe/offsets.c against SRC's headers with the build's
# own ABI flags and prints offsetof()/sizeof() values. Never writes into SRC: the generated
# headers the build normally makes (map_groups.h, region_map_sections.h, ...) are rebuilt
# in a scratch dir from copies of the JSON inputs.
#   probe/measure.sh [SRC]        SRC defaults to HNS_TREE; the scratch dir is $HNS_WORK/probe
set -euo pipefail
HERE=$(cd "$(dirname "$0")" && pwd)
PATHS="$HERE/../../paths.py"
SRC=${1:-$(python3 "$PATHS" TREE)}
W=${HNS_SCRATCH:-$(python3 "$PATHS" WORK)/probe}
DEVKITARM=${DEVKITARM:-/opt/devkitpro/devkitARM}
CC=$DEVKITARM/bin/arm-none-eabi-gcc
OBJCOPY=$DEVKITARM/bin/arm-none-eabi-objcopy
mkdir -p "$W/bin" "$W/gen/include/constants" "$W/gen/asm" "$W/json/data/maps" "$W/json/src/data"

# host tools, built from SRC's sources into the scratch dir
[ -x "$W/bin/mapjson" ] || c++ -std=c++17 -O2 "$SRC/tools/mapjson/mapjson.cpp" "$SRC/tools/mapjson/json11.cpp" -o "$W/bin/mapjson"
[ -x "$W/bin/jsonproc" ] || c++ -std=c++17 -O1 -I "$SRC/tools/jsonproc" "$SRC/tools/jsonproc/jsonproc.cpp" -o "$W/bin/jsonproc"

# mapjson writes map_group_count.h to <dir of map_groups.json>/../../src/data, so run it
# on COPIES of the JSON (never on SRC/data/maps directly)
( cd "$SRC/data/maps" && find . -name '*.json' -print0 | cpio -0pdm --quiet "$W/json/data/maps" )
MAPS=$(ls "$W"/json/data/maps/*/map.json)
# mapjson `groups` works relative to the cwd: it reads tools/mapjson/required_map_defines.json and
# rewrites src/data/heal_locations.json, so it runs on copies in the scratch dir
mkdir -p "$W/json/tools/mapjson"
cp "$SRC/tools/mapjson/required_map_defines.json" "$W/json/tools/mapjson/"
cp "$SRC/src/data/heal_locations.json" "$W/json/src/data/"
( cd "$W/json" && "$W/bin/mapjson" groups hns "$W/json/data/maps/map_groups.json" $MAPS "$W/gen/asm" "$W/gen/include/constants" )
( cd "$SRC" && "$W/bin/mapjson" layouts hns "$SRC/data/layouts/layouts.json" "$W/gen/asm" "$W/gen/include/constants" )
"$W/bin/jsonproc" "$SRC/src/data/region_map/region_map_sections.json" \
    "$SRC/src/data/region_map/region_map_sections.constants.json.txt" "$W/gen/include/constants/region_map_sections.h"
"$W/bin/jsonproc" "$W/json/src/data/heal_locations.json" \
    "$SRC/src/data/heal_locations.constants.json.txt" "$W/gen/include/constants/heal_locations.h"

# same flags as the Makefile's CPPFLAGS/CFLAGS for `make hns` (-mabi=apcs-gnu matters:
# it aligns every struct to 4)
( cd "$SRC" && "$CC" -iquote include -iquote "$W/gen/include/constants" -iquote "$W/gen/include" \
    -Wno-trigraphs -DMODERN=1 -DTESTING=0 -DPOKEMON_HNS -std=gnu17 \
    -mthumb -mthumb-interwork -O2 -mabi=apcs-gnu -mtune=arm7tdmi -march=armv4t \
    -c "$HERE/offsets.c" -o "$W/offsets.o" )
"$OBJCOPY" -O binary -j .rodata "$W/offsets.o" "$W/offsets.bin"
python3 - "$HERE/offsets.c" "$W/offsets.bin" <<'PY'
import re, struct, sys
names = re.findall(r'O\("([^"]+)"', open(sys.argv[1]).read())
b = open(sys.argv[2], "rb").read()
for i, n in enumerate(names):          # struct Off { const char *n; u32 v; } -> 8 bytes each
    print("%-28s 0x%X" % (n, struct.unpack_from("<I", b, i * 8 + 4)[0]))
PY
