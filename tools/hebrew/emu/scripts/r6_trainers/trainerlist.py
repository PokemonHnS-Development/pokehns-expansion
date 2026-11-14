#!/usr/bin/env python3
"""trainerlist.py SRC OUT.json: the field trainers of data/maps/*_hns/map.json.

An object is taken when its trainer_type is not TRAINER_TYPE_NONE and the first command of its
script is trainerbattle_single or trainerbattle_double. The BattlePyramidSquare* maps are left
out (BattlePyramid_TrainerBattle_hns). Labels are looked up in every data/maps/*/scripts.inc and
data/scripts/*.inc, because a few objects share a script with another map (Route26North uses
Route26_EventScript_*, SSAqua_1F uses SSAqua_B1F_EventScript_Jeff).

Each row: map dir, MAP_ constant, local id, x, y, movement type, sight, hide flag, script, kind
(single/double/rematch), trainer constant(s), intro/defeat/extra labels, class, Hebrew name,
gender, party species, the Gym flag (gym junior), and the region used to split the tours."""
import glob
import json
import os
import re
import sys

def labels(SRC):
    """label -> (file, line, body). A label defined in several files (a FRLG map and its H&S copy)
    resolves to the *_hns map's file, then data/scripts, then the rest."""
    out = {}
    files = sorted(glob.glob(os.path.join(SRC, "data/maps/*/scripts.inc"))) + sorted(glob.glob(os.path.join(SRC, "data/scripts/*.inc")))
    rank = lambda f: 0 if "_hns/" in f else 1 if "/data/scripts/" in f else 2
    for p in files:
        lines = open(p, encoding="utf-8").read().split("\n")
        for i, l in enumerate(lines):
            m = re.match(r"^([A-Za-z0-9_]+)::?\s*$", l)
            if m:
                body = []
                for k in range(i + 1, min(i + 40, len(lines))):
                    s = lines[k].strip()
                    if re.match(r"^[A-Za-z0-9_]+::?\s*$", lines[k]):
                        break
                    if s and not s.startswith("@") and not s.startswith("//"):
                        body.append(s)
                old = out.get(m.group(1))
                if old is None or rank(p) < old[3]:
                    out[m.group(1)] = (os.path.relpath(p, SRC), i + 1, body, rank(p))
    return {k: v[:3] for k, v in out.items()}


def parties(SRC):
    out = {}
    cur = None
    for l in open(os.path.join(SRC, "src/data/trainers_hns.party"), encoding="utf-8"):
        l = l.rstrip("\n")
        m = re.match(r"^=== (TRAINER_\w+) ===", l)
        if m:
            cur = out.setdefault(m.group(1), dict(mons=[]))
            expect_mon = True
            continue
        if cur is None:
            continue
        for k in ("Name", "Class", "Gender", "Double Battle", "Pic"):
            if l.startswith(k + ": "):
                cur[k] = l[len(k) + 2:].strip()
                break
        else:
            if l and ":" not in l and not l.startswith("-") and not l.startswith("/"):
                sp = re.split(r"\s*[@(]", l)[0].strip()
                if sp:
                    cur["mons"].append(sp)
    return out


def region(mapdir):
    n = mapdir
    if re.search(r"_Gym_hns$", n) or n.startswith("ViridianCity_Gym") or "Gym" in n.split("_")[1:2]:
        return "gym_juniors"
    if re.search(r"(Akala|Melemele|Ulaula|Poni|Alola|Sinjoh|Mystri)", n):
        return "sinjoh_alola"
    m = re.match(r"Route(\d+)", n)
    if m:
        return "johto_routes" if 29 <= int(m.group(1)) <= 46 or int(m.group(1)) >= 47 else "kanto_routes"
    kanto = ("Viridian", "Pewter", "Cerulean", "Vermilion", "Lavender", "Celadon", "Fuchsia", "Saffron",
             "Cinnabar", "Pallet", "MtMoon", "RockTunnel", "DiglettsCave", "SeafoamIslands", "VictoryRoad",
             "PowerPlant", "CeruleanCave", "SilphCo", "PokemonTower", "SafariZone", "MtSilver", "Indigo",
             "SeviiIsland", "OneIsland", "TwoIsland", "ThreeIsland", "FourIsland", "FiveIsland",
             "SixIsland", "SevenIsland", "Kanto")
    if n.startswith(kanto):
        return "kanto_routes"
    return "johto_routes"


def build(SRC):
    lab = labels(SRC)
    par = parties(SRC)
    rows = []
    for p in sorted(glob.glob(os.path.join(SRC, "data/maps/*_hns/map.json"))):
        mapdir = os.path.basename(os.path.dirname(p))
        if mapdir.startswith("BattlePyramidSquare"):
            continue
        m = json.load(open(p, encoding="utf-8"))
        for i, o in enumerate(m.get("object_events", [])):
            if o.get("type", "object") != "object":
                continue
            if o.get("trainer_type", "TRAINER_TYPE_NONE") in ("TRAINER_TYPE_NONE", 0, "0"):
                continue
            s = o["script"]
            if s not in lab:
                continue
            f, line, body = lab[s]
            if not body or not body[0].startswith(("trainerbattle_single", "trainerbattle_double")):
                continue
            first = body[0]
            cmd, args = first.split(None, 1)
            args = [a.strip() for a in re.split(r"[,\s]+", args.strip()) if a.strip()]
            row = dict(map=mapdir, mapc=m["id"], local=i + 1, x=o["x"], y=o["y"],
                       move=o["movement_type"], sight=int(o["trainer_sight_or_berry_tree_id"] or 0),
                       flag=o["flag"], script=s, file=f, line=line, cmd=cmd, args=args,
                       trainer=args[0], region=region(mapdir), body=body[1:8])
            if cmd == "trainerbattle_double":
                row["kind"] = "double"
                row["intro"], row["defeat"], row["notenough"] = args[1], args[2], args[3]
                row["extra"] = args[4] if len(args) > 4 else None
            else:
                row["kind"] = "single"
                row["intro"], row["defeat"] = args[1], args[2]
                row["extra"] = args[3] if len(args) > 3 else None
            # rematch: the script that follows the battle (trainerbattle_rematch inside the label
            # body or inside the extra script)
            rm = [b for b in body if b.startswith("trainerbattle_rematch")]
            for b in body:
                g = re.match(r"goto_if_eq VAR_RESULT, TRUE, (\w+)", b)
                if g and g.group(1) in lab:
                    rm += [(g.group(1), x) for x in lab[g.group(1)][2] if x.startswith("trainerbattle_rematch")]
            row["rematch"] = rm[0] if rm else None
            row["register"] = bool(row["extra"] and row["extra"] in lab and
                                   any("register_matchcall" in x for x in lab[row["extra"]][2]))
            pt = par.get(row["trainer"], {})
            row["class"] = pt.get("Class")
            row["name"] = pt.get("Name")
            row["gender"] = pt.get("Gender")
            row["mons"] = pt.get("mons", [])
            row["gym"] = "_Gym_hns" in mapdir or "Gym" in mapdir
            if row["gym"]:
                row["region"] = "gym_juniors"
            rows.append(row)
    return rows


def main(SRC, OUT):
    rows = build(SRC)
    json.dump(rows, open(OUT, "w", encoding="utf-8"), ensure_ascii=False, indent=1)
    from collections import Counter
    print(len(rows), Counter(r["kind"] for r in rows), Counter(r["region"] for r in rows),
          "gym", sum(r["gym"] for r in rows), "maps", len(set(r["map"] for r in rows)),
          "classes", len(set(r["class"] for r in rows)))


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
