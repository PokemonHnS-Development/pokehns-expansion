#!/usr/bin/env python3
"""Map every string of the sweep to the screenshots that show it, and write review-sheet specs
(r6sheet.py) for the groups worth a 4x look: mixed runs (digits, Latin, punctuation), the widest
strings per window, all contest effects, all natures and mint memos.

    r6review.py TOURDIR DATA_HE.json DATA_EN.json STATIC_HE.json HEDIR ENDIR OUTDIR

Writes OUTDIR/where.json ({kind: {id: [shot paths]}}) and OUTDIR/spec_*.json.
"""
import json
import os
import re
import sys

# screen crops (x0, y0, x1, y1): src/pokemon_summary_screen.c window templates, src/menu_specialized.c:111-160
CROP = {
    "sum_rows": (80, 24, 240, 112),       # move rows (type badge, name, PP) incl. header
    "sum_desc": (0, 112, 240, 160),       # power/acc or appeal/jam + description
    "sum_moves": (0, 24, 240, 160),
    "info_ability": (80, 64, 240, 112),
    "info_memo": (80, 104, 240, 160),
    "info_all": (80, 24, 240, 160),
    "skills_item": (80, 24, 240, 56),
    "skills_all": (80, 24, 240, 160),
    "rel_all": (0, 0, 240, 160),
}


def mixed(s):
    t = s.rstrip("$").replace("\\n", " ")
    t = re.sub(r"\{[^}]*\}", "", t)
    return bool(re.search(r"[A-Za-z0-9()%/+\-:]", t))


def main():
    tourdir, dh, de, st, he, en, out = sys.argv[1:8]
    ix = json.load(open(os.path.join(tourdir, "index.json")))
    H, E = json.load(open(dh)), json.load(open(de))
    S = json.load(open(st))
    where = {k: {} for k in ("move_sum", "move_rel", "move_desc_sum", "move_desc_rel", "contest_sum",
                             "contest_rel", "ability", "item", "nature", "mint")}

    def add(k, i, path, crop):
        where[k].setdefault(str(i), []).append((path, crop))

    for f in ix["full"]:
        t, tag = f["tour"], f["tag"]
        add("ability", f["aid"], "%s/%s_info" % (t, tag), "info_ability")
        add("item", f["item"], "%s/%s_skills" % (t, tag), "skills_item")
        add("nature", f["nature"], "%s/%s_info" % (t, tag), "info_memo")
        for r, m in enumerate(f["moves"]):
            add("move_sum", m, "%s/%s_bm_%d" % (t, tag, r + 1), "sum_rows")
            add("move_desc_sum", m, "%s/%s_bm_%d" % (t, tag, r + 1), "sum_desc")
            if os.path.exists(os.path.join(he, t, "%s_cm_%d.png" % (tag, r + 1))):
                add("contest_sum", H["moves"][m]["contestEffect"], "%s/%s_cm_%d" % (t, tag, r + 1), "sum_desc")
    for f in ix["items"]:
        add("item", f["item"], "%s/%s_skills" % (f["tour"], f["tag"]), "skills_item")
        if f["mint"] is not None:
            add("mint", f["nature"], "%s/%s_info" % (f["tour"], f["tag"]), "info_memo")
    for r in ix["relearner"]:
        for i, m in enumerate(r["moves"]):
            # row 0's windows are drawn before relpoke; the walk back up redraws them (PREFIX_top)
            p = "%s/%s_%03d" % (r["tour"], r["prefix"], i) if i else "%s/%s_top" % (r["tour"], r["prefix"])
            if r["mode"] == "battle":
                add("move_rel", m, p, "rel_all")
                add("move_desc_rel", m, p, "rel_all")
            else:
                add("contest_rel", H["moves"][m]["contestEffect"], p, "rel_all")
    json.dump(where, open(os.path.join(out, "where.json"), "w"), indent=0)

    def entry(label, k, i, n=1):
        res = []
        for path, crop in where[k].get(str(i), [])[:n]:
            res.append(dict(label=label, he=os.path.join(he, path + ".png"), en=os.path.join(en, path + ".png"),
                            crop=list(CROP[crop])))
        return res

    specs = {}
    # moves: names and descriptions with mixed runs; widest
    mm = [m for m in H["moves"][1:848] if mixed(m["name"])]
    specs["moves_mixed_name"] = sum((entry("move %d %s" % (m["id"], E["moves"][m["id"]]["name"]), "move_sum", m["id"])
                                     for m in mm), [])
    seen, md = set(), []
    for m in H["moves"][1:848]:
        if m["desc"] not in seen and mixed(m["desc"]):
            seen.add(m["desc"])
            md.append(m)
    specs["moves_mixed_desc_sum"] = sum((entry("move %d %s" % (m["id"], E["moves"][m["id"]]["name"]), "move_desc_sum", m["id"])
                                         for m in md), [])
    specs["moves_mixed_desc_rel"] = sum((entry("move %d %s" % (m["id"], E["moves"][m["id"]]["name"]), "move_desc_rel", m["id"])
                                         for m in md), [])
    wide = {}
    for r in S:
        wide.setdefault(r["kind"], []).append(r)
    for k in wide:
        wide[k].sort(key=lambda r: -r["over"])
    specs["wide_move_desc_sum"] = sum((entry("move %d over %+d" % (r["id"], r["over"]), "move_desc_sum", r["id"])
                                       for r in wide["move_desc_summary"][:16]), [])
    specs["wide_move_desc_rel"] = sum((entry("move %d over %+d" % (r["id"], r["over"]), "move_desc_rel", r["id"])
                                       for r in wide["move_desc_relearner"][:16]), [])
    specs["wide_move_name"] = sum((entry("move %d over %+d" % (r["id"], r["over"]), "move_sum", r["id"])
                                   for r in [r for r in wide["move_name_summary"] if r["id"] < 848][:16]), [])
    specs["wide_move_name_rel"] = sum((entry("move %d over %+d" % (r["id"], r["over"]), "move_rel", r["id"])
                                       for r in [r for r in wide["move_name_relearner"] if r["id"] < 848][:16]), [])
    specs["contest_sum"] = sum((entry("effect %d" % c, "contest_sum", c) for c in range(48)), [])
    specs["contest_rel"] = sum((entry("effect %d" % c, "contest_rel", c) for c in range(48)), [])
    ab = [a for a in H["abilities"][1:] if mixed(a["name"]) or mixed(a["desc"])]
    specs["abilities_mixed"] = sum((entry("ability %d %s" % (a["id"], E["abilities"][a["id"]]["name"]), "ability", a["id"])
                                    for a in ab), [])
    specs["wide_ability_desc"] = sum((entry("ability %d over %+d" % (r["id"], r["over"]), "ability", r["id"])
                                      for r in wide["ability_desc"][:16]), [])
    it = [i for i in H["items"] if i["name"] and not i["name"].startswith("????") and mixed(i["name"])]
    specs["items_mixed"] = sum((entry("item %d %s" % (i["id"], E["items"][i["id"]]["name"]), "item", i["id"])
                                for i in it), [])
    specs["wide_item"] = sum((entry("item %d over %+d" % (r["id"], r["over"]), "item", r["id"])
                              for r in wide["item_held"][:24]), [])
    specs["natures"] = sum((entry("nature %d %s" % (n, E["natures"][n]["name"]), "nature", n) for n in range(25)), [])
    specs["mint"] = sum((entry("mint for nature %d" % n, "mint", n) for n in range(25)), [])
    for k, v in specs.items():
        json.dump(v, open(os.path.join(out, "spec_%s.json" % k), "w"), ensure_ascii=False, indent=0)
        print("%-24s %4d crops" % (k, len(v)))
    # coverage
    cov = {}
    for k in ("move_sum", "move_rel", "ability", "item", "nature", "mint", "contest_sum", "contest_rel"):
        cov[k] = len(where[k])
    print("coverage (distinct ids with a shot):", cov)


if __name__ == "__main__":
    main()
