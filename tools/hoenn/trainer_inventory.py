#!/usr/bin/env python3
"""Inventory of Hoenn trainers placed on kept maps.

    tools/hoenn/trainer_inventory.py [--json OUT]

For every object on a kept Hoenn map whose script starts a trainer battle,
prints map, object position, trainer constant, class, level range, whether it's
a double battle and whether it's in a gym. Also lists trainers in
trainers_hoenn.party that no kept map uses (rematch tiers, story trainers).
"""
import json, os, re, sys
from collections import Counter

ROOT = os.path.join(os.path.dirname(__file__), "..", "..")

def party_info():
    info, cur = {}, None
    for line in open(os.path.join(ROOT, "src/data/trainers_hoenn.party")):
        m = re.match(r"=== (TRAINER_\w+) ===", line)
        if m:
            cur = m.group(1); info[cur] = {"class": "", "levels": [], "double": False}
            continue
        if not cur:
            continue
        if line.startswith("Class:"):
            info[cur]["class"] = line.split(":", 1)[1].strip()
        elif line.startswith("Double Battle:"):
            info[cur]["double"] = "Yes" in line
        elif line.startswith("Level:"):
            info[cur]["levels"].append(int(line.split(":")[1]))
    return info

def labels(text):
    out, cur = {}, None
    for line in text.splitlines():
        m = re.match(r"^(\w+)::?\s*$", line)
        if m:
            cur = m.group(1); out[cur] = []
        elif cur:
            out[cur].append(line)
    return out

def main():
    kept = json.load(open(os.path.join(ROOT, "data/hoenn/maps.json")))["items"]
    party = party_info()
    rows, used = [], set()
    for m in sorted(kept):
        mp = os.path.join(ROOT, "data/maps", m)
        d = json.load(open(os.path.join(mp, "map.json")))
        sp = os.path.join(mp, "scripts.inc")
        labs = labels(open(sp).read()) if os.path.exists(sp) else {}
        for idx, o in enumerate(d.get("object_events", [])):
            body = "\n".join(labs.get(o.get("script", ""), [])[:3])
            t = re.search(r"trainerbattle_(\w+)\s+(TRAINER_\w+)(?:,\s*(TRAINER_\w+))?", body)
            if not t:
                continue
            kind, tr, tr2 = t.group(1), t.group(2), t.group(3)
            for x in (tr, tr2):
                if x: used.add(x)
            p = party.get(tr, {})
            lv = p.get("levels") or [0]
            rows.append({
                "map": m, "x": o["x"], "y": o["y"], "local_id": o.get("local_id", ""),
                "script": o["script"], "trainer": tr, "trainer2": tr2, "kind": kind,
                "class": p.get("class", "?"), "lv": f"{min(lv)}-{max(lv)}",
                "double": p.get("double", False) or kind.startswith("double") or bool(tr2),
                "gym": "_Gym" in m, "trainer_type": o.get("trainer_type"),
                "sight": o.get("trainer_sight_or_berry_tree_id"),
            })
    if "--json" in sys.argv:
        json.dump(rows, open(sys.argv[sys.argv.index("--json") + 1], "w"), indent=1)
    for r in rows:
        print(f"{r['map']:34} {r['x']:3},{r['y']:<3} {r['trainer']:28} {r['class']:16} {r['lv']:6} {'D' if r['double'] else ' '}{'G' if r['gym'] else ' '} {r['kind']}")
    unused = [t for t in party if t not in used]
    print(f"-- {len(rows)} placed objects, {len(used)} trainer IDs used, {len(unused)} unused in party file", file=sys.stderr)
    print("-- classes (non-gym):", Counter(r["class"] for r in rows if not r["gym"]).most_common(), file=sys.stderr)
    print("-- unused:", " ".join(unused), file=sys.stderr)

if __name__ == "__main__":
    main()
