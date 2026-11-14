#!/usr/bin/env python3
"""List every shop a player can open in H&S: the map objects, signs and triggers whose script
reaches a shop command (pokemart, pokemartdecoration*, special Create*Shop, the Kurt shop) or a
money-box seller (showmoneybox / showcoinsbox / BP box with a sale), following goto/call.

    HNS_SRC=<tree> python3 shops.py [--json OUT.json]

Prints one row per entry point: map, event kind, x, y, script label, what it reaches.
"""
import glob
import json
import os
import re
import sys

SRC = os.environ.get("HNS_SRC") or os.getcwd()

LABEL = re.compile(r"^([A-Za-z_][A-Za-z0-9_]*)::?\s*$")
JUMP = re.compile(r"^\s*(goto|call|goto_if_\w+|call_if_\w+|goto_if|call_if|jump)\b(.*)$")
SHOP = re.compile(r"^\s*(pokemart\s+\S+|pokemartdecoration2?\s+\S+|special\s+Create\w*(?:Shop|Mart)\w*)")
MONEY = re.compile(r"^\s*(showmoneybox|showcoinsbox|special\s+\w*(?:Vending|Prize|Coin|BP)\w*|checkmoney|removemoney)\b")
IDENT = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")


def parse_scripts():
    body = {}
    where = {}
    files = sorted(glob.glob(os.path.join(SRC, "data/maps/*/scripts.inc")))
    files += sorted(glob.glob(os.path.join(SRC, "data/scripts/*.inc")))
    files += [os.path.join(SRC, "data/event_scripts.s")]
    for f in files:
        cur = None
        try:
            lines = open(f, encoding="utf-8").read().splitlines()
        except OSError:
            continue
        for n, line in enumerate(lines, 1):
            m = LABEL.match(line)
            if m:
                cur = m.group(1)
                body.setdefault(cur, [])
                where[cur] = "%s:%d" % (os.path.relpath(f, SRC), n)
                continue
            if cur:
                body[cur].append((line, n))
    return body, where


def reach(body, start, depth=12):
    """(shop commands, money commands, labels visited) reachable from START."""
    seen = set()
    shops, money = [], []
    todo = [start]
    while todo:
        lab = todo.pop()
        if lab in seen or lab not in body:
            continue
        seen.add(lab)
        if len(seen) > 200:
            break
        lines = body[lab]
        for line, n in lines:
            s = line.split("@")[0]
            m = SHOP.match(s)
            if m:
                shops.append((lab, n, m.group(1).strip()))
            m = MONEY.match(s)
            if m:
                money.append((lab, n, m.group(1).strip()))
            j = JUMP.match(s)
            if j:
                for tok in IDENT.findall(j.group(2)):
                    if tok in body:
                        todo.append(tok)
        # fall through into the next label when the body has no end/return/goto
        last = [l for l, _ in lines if l.strip() and not l.strip().startswith("@")]
    return shops, money, seen


def main():
    body, where = parse_scripts()
    rows = []
    for mj in sorted(glob.glob(os.path.join(SRC, "data/maps/*_hns/map.json"))):
        d = json.load(open(mj, encoding="utf-8"))
        mid = d.get("id")
        evs = []
        for o in d.get("object_events", []) or []:
            evs.append(("obj", o.get("x"), o.get("y"), o.get("script"), o.get("graphics_id"), o.get("flag")))
        for b in d.get("bg_events", []) or []:
            if b.get("type") == "sign":
                evs.append(("sign", b.get("x"), b.get("y"), b.get("script"), b.get("player_facing_dir"), None))
        for c in d.get("coord_events", []) or []:
            if c.get("type") == "trigger":
                evs.append(("trig", c.get("x"), c.get("y"), c.get("script"), c.get("var"), c.get("var_value")))
        for kind, x, y, scr, gfx, flag in evs:
            if not scr or scr == "0x0":
                continue
            shops, money, seen = reach(body, scr)
            if shops or money:
                rows.append({
                    "map": mid, "kind": kind, "x": x, "y": y, "script": scr, "gfx": gfx, "flag": flag,
                    "where": where.get(scr), "shops": shops, "money": money,
                })
    out = None
    if "--json" in sys.argv:
        out = sys.argv[sys.argv.index("--json") + 1]
        json.dump(rows, open(out, "w"), ensure_ascii=False, indent=1)
    for r in rows:
        tag = "SHOP" if r["shops"] else "money"
        what = "; ".join(sorted(set(s[2] for s in r["shops"]))) or "; ".join(sorted(set(s[2] for s in r["money"])))
        print("%-5s %-46s %-4s (%s,%s) %-50s %s" % (tag, r["map"], r["kind"], r["x"], r["y"], r["script"], what))


if __name__ == "__main__":
    main()
