#!/usr/bin/env python3
"""EN | HE review sheets of the dex_text track: 2 columns x 4 rows of screenshot pairs, NEAREST 2x,
a Latin label above each pair (shot name and the string ids the strrep run logged at that shot).

    dexsheets.py PLAN.json OUT_DIR [--per 8] [--cols 2] [--scale 2]

PLAN.json: {"GROUP": [{"name": SHOT, "en": PNG or null, "he": PNG, "label": TEXT, "ids": [..],
             "info": {...}}, ...], ...}. GROUP names the sheets (GROUP_NN.png), e.g. dexA_g4
(part A: Gen 4, Gen 5, shared_dex_text.h, EVO page) or dexB_g6 (part B: Gen 6-9).
Writes OUT_DIR/GROUP_NN.png and OUT_DIR/sheet_index.json: sheet -> [{slot, name, en, he, ids, info}].
A missing EN shot leaves a grey panel.
"""
import argparse
import json
import os

from PIL import Image, ImageDraw

LABEL_H = 12
GAP = 4
COL_GAP = 16


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("plan")
    ap.add_argument("out")
    ap.add_argument("--per", type=int, default=8)
    ap.add_argument("--cols", type=int, default=2)
    ap.add_argument("--scale", type=int, default=2)
    a = ap.parse_args()
    plan = json.load(open(a.plan, encoding="utf-8"))
    os.makedirs(a.out, exist_ok=True)
    w, h = 240 * a.scale, 160 * a.scale
    pw = 2 * w + GAP
    index = {}
    for group, items in plan.items():
        for k in range(0, len(items), a.per):
            chunk = items[k:k + a.per]
            rows = (len(chunk) + a.cols - 1) // a.cols
            W = a.cols * pw + (a.cols - 1) * COL_GAP
            H = rows * (LABEL_H + h + GAP)
            sheet = Image.new("RGB", (W, H), "white")
            d = ImageDraw.Draw(sheet)
            recs = []
            for i, it in enumerate(chunk):
                x0 = (i % a.cols) * (pw + COL_GAP)
                y0 = (i // a.cols) * (LABEL_H + h + GAP)
                d.text((x0 + 2, y0), "%d  %s" % (i + 1, it.get("label", it["name"]))[:150], fill="black")
                for j, key in enumerate(("en", "he")):
                    p = it.get(key)
                    x = x0 + j * (w + GAP)
                    if p and os.path.exists(p):
                        im = Image.open(p).convert("RGB").resize((w, h), Image.NEAREST)
                        sheet.paste(im, (x, y0 + LABEL_H))
                    else:
                        d.rectangle((x, y0 + LABEL_H, x + w - 1, y0 + LABEL_H + h - 1), fill=(200, 200, 200))
                        d.text((x + 8, y0 + LABEL_H + 8), "no %s shot" % key.upper(), fill="black")
                recs.append({"slot": i + 1, "row": i // a.cols + 1, "col": i % a.cols + 1, "name": it["name"],
                             "en": it.get("en"), "he": it.get("he"), "ids": it.get("ids", []),
                             "info": it.get("info", {})})
            name = "%s_%02d.png" % (group, k // a.per + 1)
            sheet.save(os.path.join(a.out, name))
            index[name] = recs
    with open(os.path.join(a.out, "sheet_index.json"), "w", encoding="utf-8") as fh:
        json.dump(index, fh, ensure_ascii=False, indent=1)
    print("%d sheets in %s" % (len(index), a.out))


if __name__ == "__main__":
    main()
