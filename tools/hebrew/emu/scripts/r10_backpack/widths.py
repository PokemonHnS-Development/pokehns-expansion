#!/usr/bin/env python3
"""widths.py ITEMS_JSON TREE OUT.json : pixel widths of each item's name (FONT_NARROW, the bag list),
plural, and description lines (FONT_NORMAL), with textwidth.py's model of the RTL renderer."""
import json
import os
import sys
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.normpath(os.path.join(HERE, "..", "..", "..")))
import textwidth as tw  # noqa: E402

items, tree, out = sys.argv[1:4]
m = tw.TextModel(tree=tree, symtree=tree)
res = []
for it in json.load(open(items)):
    def w(s, font):
        try:
            return m.width(s.rstrip("$"), font)
        except Exception as e:  # noqa: BLE001
            return str(e)
    r = dict(id=it["id"], const=it["const"], pocket=it["pocket"], name=it["name"],
             name_narrow=w(it["name"] or "", "FONT_NARROW"), name_normal=w(it["name"] or "", "FONT_NORMAL"))
    d = (it["desc"] or "").rstrip("$")
    lines = d.split("\n")
    r["desc_lines"] = len(lines)
    r["desc_w"] = [w(l, "FONT_NORMAL") for l in lines]
    res.append(r)
json.dump(res, open(out, "w"), ensure_ascii=False, indent=0)
