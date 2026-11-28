#!/usr/bin/env python3
"""Story audit for a set of Hoenn maps: what can lock the player or fire a cutscene.
    story_audit.py PREFIX [PREFIX...]   (map-name prefixes, e.g. LittlerootTown Route101)
For each matching kept map it prints coord triggers and frame triggers (with the var
value that fires them), objects hidden by flags, and the values each var is set to
anywhere in the kept Hoenn scripts, so a post-Emerald value can be picked."""
import json, os, re, sys, collections

ROOT = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", ".."))
def rd(p):
    with open(os.path.join(ROOT, p)) as f:
        return f.read()

maps = json.loads(rd("data/hoenn/maps.json"))["items"]
sel = [m for m in maps if any(m.startswith(p) for p in sys.argv[1:])]

# all setvar/addvar values across kept Hoenn scripts
setvals = collections.defaultdict(set)
for m in maps:
    p = f"data/maps/{m}/scripts.inc"
    if os.path.exists(os.path.join(ROOT, p)):
        for v, n in re.findall(r"setvar (VAR_\w+), (\w+)", rd(p)):
            setvals[v].add(n)
        for v in re.findall(r"addvar (VAR_\w+)", rd(p)):
            setvals[v].add("+")
for p in ("data/scripts",):
    for f in os.listdir(os.path.join(ROOT, p)):
        if f.endswith(".inc") and "hns" not in f and "frlg" not in f:
            for v, n in re.findall(r"setvar (VAR_\w+), (\w+)", rd(f"{p}/{f}")):
                setvals[v].add(n)

seen_vars = set()
for m in sel:
    j = json.loads(rd(f"data/maps/{m}/map.json"))
    s = rd(f"data/maps/{m}/scripts.inc") if os.path.exists(os.path.join(ROOT, f"data/maps/{m}/scripts.inc")) else ""
    lines = []
    for c in j.get("coord_events") or []:
        if c.get("type") == "trigger" and c.get("var") and c["var"] != "0":
            lines.append(f"  trigger ({c['x']},{c['y']}) {c['var']}=={c['var_value']} -> {c['script']}")
            seen_vars.add(c["var"])
    for v, val, scr in re.findall(r"map_script_2 (VAR_\w+), (\w+), (\w+)", s):
        lines.append(f"  frame {v}=={val} -> {scr}")
        seen_vars.add(v)
    for o in j.get("object_events") or []:
        f = o.get("flag", "0")
        if f not in ("0", 0, "", None) and not f.startswith(("FLAG_ITEM_", "FLAG_HIDDEN_ITEM")):
            lines.append(f"  obj {o.get('local_id') or ''} {o['graphics_id'].replace('OBJ_EVENT_GFX_','')} ({o['x']},{o['y']}) hide={f} script={o.get('script')}")
    for v in set(re.findall(r"(VAR_\w+)", s)):
        if not v.startswith(("VAR_TEMP", "VAR_0x8", "VAR_RESULT", "VAR_FACING", "VAR_LAST")):
            seen_vars.add(v)
    if lines:
        print(m); print("\n".join(lines))
print("\nVARS (values set anywhere in kept Hoenn scripts):")
for v in sorted(seen_vars):
    print(f"  {v}: {sorted(setvals.get(v, []), key=lambda x: (len(x), x))}")
