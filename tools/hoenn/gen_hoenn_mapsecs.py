#!/usr/bin/env python3
"""Give Hoenn's map sections real values in the HnS build.

    python3 tools/hoenn/gen_hoenn_mapsecs.py

In HnS, src/data/region_map/region_map_sections.json lists HnS's own sections
in "hns_map_sections" (values 1..N); every other section is generated as
`= 0`, so all Hoenn maps reported section 0 (wrong name, wrong region).

This appends the sections used by kept Hoenn maps (data/hoenn/maps.json) to
the end of "hns_map_sections" and marks them "in_hns" in "map_sections", so
HnS's own values don't move. Appended sections sit after JOHTO_MAPSEC_END, so
GetRegionForSectionId() returns REGION_HOENN for them. Idempotent.
"""
import json, os
ROOT = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))
P = os.path.join(ROOT, "src/data/region_map/region_map_sections.json")

def main():
    d = json.load(open(P))
    kept = json.load(open(os.path.join(ROOT, "data/hoenn/maps.json")))["items"]
    used = {json.load(open(os.path.join(ROOT, f"data/maps/{m}/map.json")))["region_map_section"] for m in kept}
    hns_ids = {s["id"] for s in d["hns_map_sections"]}
    by_id = {s["id"]: s for s in d["map_sections"]}
    added = []
    for s in d["map_sections"]:                     # keep Emerald's order
        if s["id"] in used and s["id"] not in hns_ids:
            s["in_hns"] = True
            entry = {k: v for k, v in s.items() if k != "in_hns"}
            entry["hoenn"] = True
            d["hns_map_sections"].append(entry)
            added.append(s["id"])
    missing = sorted(u for u in used if u not in by_id and u not in hns_ids)
    if missing:
        raise SystemExit(f"unknown sections: {missing}")
    total = len(d["hns_map_sections"])
    if total + 1 > 255:
        raise SystemExit(f"too many map sections for u8: {total}")
    with open(P, "w") as f:
        json.dump(d, f, indent=2, ensure_ascii=False)
        f.write("\n")
    print(f"appended {len(added)} Hoenn sections; HnS sections now {total} (MAPSEC_NONE = {total + 1})")

if __name__ == "__main__":
    main()
