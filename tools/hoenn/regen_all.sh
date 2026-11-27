#!/usr/bin/env bash
# Hoenn & Seek (lane setup, Nov 27): re-run every Hoenn generator, in the order
# their inputs and outputs need.
#
# Why: two builders now work in parallel (hoenn-docs/lanes/README.md). When a
# merge of `hoenn` into your branch conflicts in a generated file (a map.json's
# objects, hoenn_hints.inc, hoenn_flags.h, a composed layout, ...), don't
# resolve it by hand: take hoenn's side of the generated file, keep both sides
# of the hand-written inputs (the JSON files in data/hoenn/, the scripts), then
# run this script and rebuild. Every generator is deterministic and idempotent,
# so on a clean tree this script changes nothing (`--check` proves it).
#
# The order (each line's notes are in CLAUDE.md):
#   lists → mapsecs → wild tables (+ item upgrades) → weather cycles → weather
#   tables → strait → base entrances → base spots → composed maps → trainers →
#   IDs → gyms, new-game state → battle backgrounds and art → overworld
#   Pokémon → trainer followers → buildings → hints → light paths → Unown tiles.
#
# Usage: tools/hoenn/regen_all.sh           run everything
#        tools/hoenn/regen_all.sh --check   run, then fail if the tree changed
#                                           (run it on a clean tree)
set -euo pipefail
cd "$(dirname "$0")/../.."

GENERATORS=(
    gen_hoenn_lists          # data/hoenn/{maps,layouts}.json from exclude.json
    gen_hoenn_mapsecs        # Hoenn map sections
    gen_hoenn_wild           # Hoenn wild tables, item-ball upgrades
    gen_hoenn_weather        # weather-cycle routes
    gen_hoenn_weather_wild   # special-weather wild tables (after wild + weather)
    gen_hoenn_strait         # Tidal Strait maps, Route 41 rocks
    gen_hoenn_base_entrances # Johto/Kanto base entrance metatiles (before spots)
    gen_hoenn_base_spots     # secret base spots, chamber-bases
    gen_hoenn_composed_maps  # maps and patches painted from other layouts
    gen_hoenn_trainers       # trainer curation (before gen_hoenn_ids)
    gen_hoenn_ids            # Hoenn flag/var/trainer IDs
    gen_hoenn_gyms           # gym trainer table (after IDs)
    gen_hoenn_newgame        # new-game flags and overrides (after IDs)
    gen_hoenn_battle_bgs     # battle environments per map
    gen_hoenn_battle_art     # battle background art
    gen_hoenn_ow_mons        # overworld Pokémon (after map objects change)
    gen_hoenn_followers      # trainer followers (after trainers + ow mons)
    gen_hoenn_buildings      # opened buildings (before hints)
    gen_hoenn_hints          # hint NPC wrappers (after everything that moves objects)
    gen_hoenn_lights         # follow-the-lights paths (after layouts and objects)
    gen_hoenn_unown_tiles    # Unown Cipher braille + glow tiles (part 27a)
)

# What changed, by content: `git status` also lists the battle-art .pal files
# whenever they're rewritten (stored with LF, checked out as CRLF by
# .gitattributes), even when nothing in them changed, so ask `git diff`.
tree_changes() {
    { git diff --name-only 2>/dev/null; git diff --cached --name-only; git ls-files --others --exclude-standard; } | sort -u
}

check=0
[[ "${1:-}" == "--check" ]] && check=1
if (( check )) && [[ -n "$(tree_changes)" ]]; then
    echo "regen_all.sh --check needs a clean tree (commit or stash first)" >&2
    exit 1
fi

for g in "${GENERATORS[@]}"; do
    echo "== $g"
    python3 "tools/hoenn/$g.py"
done

# Two generators rewrite files that come out byte-different but identical in
# content: gen_hoenn_base_entrances.py and gen_hoenn_battle_art.py re-encode
# their PNGs (same pixels and palette, other zlib settings), and .pal files can
# differ only in line endings. Put those back so a re-run shows no noise.
python3 - <<'PY'
import io, os, subprocess
from PIL import Image
changed = subprocess.check_output(["git", "diff", "--name-only"], text=True, stderr=subprocess.DEVNULL).split()
for f in changed:
    if not os.path.isfile(f):  # deleted in the working tree: not ours to judge
        continue
    try:
        old = subprocess.check_output(["git", "show", "HEAD:" + f])
    except subprocess.CalledProcessError:
        continue
    new = open(f, "rb").read()
    same = False
    if f.endswith(".png"):
        a, b = Image.open(io.BytesIO(old)), Image.open(io.BytesIO(new))
        same = (a.mode, a.size, a.getpalette(), a.tobytes()) == (b.mode, b.size, b.getpalette(), b.tobytes())
    elif f.endswith(".pal"):
        same = old.replace(b"\r\n", b"\n") == new.replace(b"\r\n", b"\n")
    if same:
        subprocess.check_call(["git", "checkout", "-q", "--", f])
PY

if (( check )); then
    if [[ -n "$(tree_changes)" ]]; then
        echo "regen_all.sh --check: the generators changed these files:" >&2
        tree_changes >&2
        exit 1
    fi
    echo "regen_all.sh --check: no changes"
fi
