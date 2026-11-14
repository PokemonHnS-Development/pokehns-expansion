#!/usr/bin/env python3
"""Static width/line pass over the strings the summary / relearner sweep shows, with the RTL width
model (tools/hebrew/textwidth.py), against the windows they are printed in:

  move name        summary rows, FONT_NORMAL fit chain, window 72 px (pokemon_summary_screen.c:4413)
                   relearner list, FONT_NORMAL narrowed to 68 px (menu_specialized.c:174-195)
  move desc        summary, FONT_NORMAL at x 6 in 160 px, 2 lines (pokemon_summary_screen.c:4560)
                   relearner, FONT_NARROW at x 0 in 128 px, 2 lines (menu_specialized.c:815)
  contest desc     summary, FONT_NORMAL at x 6 in 160 px (:4541); relearner FONT_NARROW 128 px (:851)
  ability          INFO page window 144 px, name FONT_NORMAL at x 0, description at x 0, 1 line
  item             SKILLS held item, fit chain to 72 px (80 - 8), centred at 72 + 6 (:4164)
  nature           memo, FONT_NORMAL in 144 px

    r6static.py DATA.json OUT.json [--tree T]
"""
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(HERE, "..", "..", ".."))    # tools/hebrew
import textwidth as tw  # noqa: E402

CHAIN = {"FONT_NORMAL": "FONT_NARROW", "FONT_NARROW": "FONT_NARROWER", "FONT_NARROWER": None}


def fit(m, s, font, px):
    while True:
        w = m.width(s, font)
        nxt = CHAIN.get(font)
        if w <= px or nxt is None:
            return font, w
        font = nxt


def main():
    data_path, out = sys.argv[1:3]
    tree = sys.argv[sys.argv.index("--tree") + 1] if "--tree" in sys.argv else None
    m = tw.TextModel(tree=tree) if tree else tw.TextModel()
    d = json.load(open(data_path))
    rows = []

    def add(kind, ident, text, font, budget, x=0, maxlines=1, chain=False):
        if text is None:
            return
        if chain:
            f, w = fit(m, text, font, budget)
            lines = [w]
        else:
            f = font
            lines = [l.width for l in m.lines(text, font, x)]
            w = max(lines or [0])
        over = (w + x) - budget if not chain else w - budget
        rows.append(dict(kind=kind, id=ident, text=text, font=f, width=w, x=x, budget=budget,
                         lines=len(lines), maxlines=maxlines, over=over,
                         bad=over > 0 or len(lines) > maxlines))

    seen = set()
    for mv in d["moves"][1:]:
        add("move_name_summary", mv["id"], mv["name"], "FONT_NORMAL", 72, chain=True)
        add("move_name_relearner", mv["id"], mv["name"], "FONT_NORMAL", 68, chain=True)
        if mv["desc"] not in seen:
            seen.add(mv["desc"])
            add("move_desc_summary", mv["id"], mv["desc"], "FONT_NORMAL", 160, x=6, maxlines=2)
            add("move_desc_relearner", mv["id"], mv["desc"], "FONT_NARROW", 128, x=0, maxlines=2)
    for ce in d["contest_effects"]:
        add("contest_desc_summary", ce["id"], ce["desc"], "FONT_NORMAL", 160, x=6, maxlines=2)
        add("contest_desc_relearner", ce["id"], ce["desc"], "FONT_NARROW", 128, x=0, maxlines=2)
    for ab in d["abilities"]:
        add("ability_name", ab["id"], ab["name"], "FONT_NORMAL", 144)
        add("ability_desc", ab["id"], ab["desc"], "FONT_NORMAL", 144)
    for it in d["items"]:
        if it["name"] and not it["name"].startswith("????"):
            add("item_held", it["id"], it["name"], "FONT_NORMAL", 72, chain=True)
    for n in d["natures"]:
        add("nature", n["id"], n["name"], "FONT_NORMAL", 144)
    json.dump(rows, open(out, "w"), ensure_ascii=False, indent=0)
    bad = [r for r in rows if r["bad"]]
    by = {}
    for r in rows:
        by.setdefault(r["kind"], [0, 0, -999])
        by[r["kind"]][0] += 1
        by[r["kind"]][1] += r["bad"]
        by[r["kind"]][2] = max(by[r["kind"]][2], r["over"])
    for k, (n, b, mo) in by.items():
        print("%-24s %4d strings, %3d over budget/lines, max over %+d px" % (k, n, b, mo))
    for r in bad[:80]:
        print("  %-22s %4d %-14s w=%3d x=%d budget=%d lines=%d/%d  %s" % (
            r["kind"], r["id"], r["font"], r["width"], r["x"], r["budget"], r["lines"], r["maxlines"], r["text"]))


if __name__ == "__main__":
    main()
