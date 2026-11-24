#!/usr/bin/env python3
"""Report links from compiled Hoenn maps into maps that are NOT in the HnS build.
Following one of these at runtime would load a NULL map header and crash.

    python3 tools/hoenn/check_links.py [--json OUT]

Checks map.json warps and connections, plus warp-like script commands in each
kept map's scripts.inc. Writes a summary; exit code 0 (informational).
"""
import glob
import json
import os
import re
import sys
from collections import defaultdict

ROOT = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))
WARP_CMDS = r"(?:warp|warpsilent|warpdoor|warphole|warpteleport|warpspinenter|warpwhitefade|warpmossdeepgym|setwarp|setdynamicwarp|setescapewarp|setdivewarp|setholewarp|goto_if_map)"
SPECIAL = {"MAP_DYNAMIC", "MAP_UNDEFINED", "MAP_NONE"}


def main():
    maps = {}
    for p in glob.glob(os.path.join(ROOT, "data/maps/*/map.json")):
        d = json.load(open(p))
        maps[d["name"]] = d
    id2name = {d["id"]: n for n, d in maps.items()}
    kept = set(json.load(open(os.path.join(ROOT, "data/hoenn/maps.json")))["items"])
    groups = json.load(open(os.path.join(ROOT, "data/maps/map_groups.json")))
    grouped = {m for g in groups["group_order"] for m in groups[g]}
    built = kept | {n for n, d in maps.items() if d.get("game_version") == "hns" and n in grouped}

    dangling = defaultdict(set)  # target -> {(source, kind)}
    for src in sorted(kept):
        d = maps[src]
        for w in d.get("warp_events") or []:
            t = w["dest_map"]
            if t not in SPECIAL and id2name.get(t) not in built:
                dangling[t].add((src, "warp"))
        for c in d.get("connections") or []:
            t = c["map"]
            if id2name.get(t) not in built:
                dangling[t].add((src, f"connection {c['direction']}"))
        sp = os.path.join(ROOT, "data/maps", src, "scripts.inc")
        if os.path.exists(sp):
            for m in re.finditer(WARP_CMDS + r"\s+(MAP_[A-Z0-9_]+)", open(sp).read()):
                t = m.group(1)
                if t not in SPECIAL and id2name.get(t) not in built:
                    dangling[t].add((src, "script"))

    out = {t: sorted(f"{s} ({k})" for s, k in v) for t, v in sorted(dangling.items())}
    print(f"built maps: {len(built)} (Hoenn {len(kept)})")
    print(f"targets outside the build reached from Hoenn maps: {len(out)}")
    for t, srcs in out.items():
        print(f"  {t}  <-  {', '.join(srcs[:4])}{' …' if len(srcs) > 4 else ''}")
    if len(sys.argv) == 3 and sys.argv[1] == "--json":
        json.dump(out, open(sys.argv[2], "w"), indent=2)


if __name__ == "__main__":
    main()
