#!/usr/bin/env python3
"""EN | HE review sheets of the species-name tours (tours/r16b_species_names), NEAREST-scaled crops.

    sheets16.py EN_RUN HE_RUN OUT_DIR [--popups EN_POP HE_POP]

EN_RUN / HE_RUN are `names16.py tour` output folders (one sub-folder per tour). Every row is one pair:
English left, Hebrew right, the same screenshot or crop of it. Writes OUT_DIR/<sheet>.png and
OUT_DIR/index.json / index.md (sheet -> loads -> species constants, string ids, both names).

Sheets:
  ld_NN     two loads of six species: party menu, the summary name block of slots 0-2 and 3-5
            (portrait panel crop), the wild battle's first page (appeared line, foe healthbox), the
            send-out line, the action menu (both healthboxes); 12 pairs
  wide_N    a load of the widest names: party, summary name blocks, PC DEPOSIT panel of every slot,
            the action menu of the battle with each name on both sides; 11 pairs
  abil_N    RANDOM ABILITIES loads: the summary INFO ability window of every slot, then the battle
            pages with the pop-ups
  popups    the battle-sweep pop-up stand-in (bsweep.py --popups): foe and player side
"""
import argparse
import json
import os

from PIL import Image, ImageDraw

HERE = os.path.dirname(os.path.abspath(__file__))
TOURS = os.path.join(HERE, "..", "..", "tours", "r16b_species_names")
S = 2
GAP = 8
LABEL_H = 12
SUM_CROP = (0, 88, 80, 148)          # summary portrait panel: nickname, /species, gender, level
PC_CROP = (0, 80, 80, 160)           # PC panel: nickname, /species, gender and level, item
MSG_CROP = (0, 112, 240, 160)        # battle message box


def load(path, crop=None):
    if not os.path.exists(path):
        return None
    im = Image.open(path).convert("RGB")
    return im.crop(crop) if crop else im


def strip(paths, crop):
    ims = [load(p, crop) for p in paths]
    w, h = crop[2] - crop[0], crop[3] - crop[1]
    out = Image.new("RGB", (w * len(paths) + 2 * (len(paths) - 1), h), (255, 0, 255))
    for i, im in enumerate(ims):
        if im is not None:
            out.paste(im, (i * (w + 2), 0))
    return out


class Sheet:
    def __init__(self, name):
        self.name, self.rows = name, []

    def pair(self, label, en, he):
        self.rows.append((label, en, he))

    def save(self, out):
        w = max(max(e.width if e else 0, h.width if h else 0) for _, e, h in self.rows) * S
        H = sum(LABEL_H + max(e.height if e else 0, h.height if h else 0) * S + GAP for _, e, h in self.rows)
        W = Image.new("RGB", (2 * w + GAP, H), "white")
        d = ImageDraw.Draw(W)
        y = 0
        for label, en, he in self.rows:
            d.text((2, y), "EN | HE  " + label, fill=(0, 0, 160))
            y += LABEL_H
            rh = 0
            for k, im in enumerate((en, he)):
                if im is None:
                    d.text((k * (w + GAP) + 4, y + 4), "missing", fill="red")
                    continue
                im2 = im.resize((im.width * S, im.height * S), Image.NEAREST)
                W.paste(im2, (k * (w + GAP), y))
                rh = max(rh, im2.height)
            y += rh + GAP
        W.save(os.path.join(out, self.name + ".png"))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("en")
    ap.add_argument("he")
    ap.add_argument("out")
    ap.add_argument("--popups", nargs=2, default=None)
    a = ap.parse_args()
    os.makedirs(a.out, exist_ok=True)
    T = json.load(open(os.path.join(TOURS, "index.json")))
    TG = json.load(open(os.path.join(TOURS, "species_targets.json"), encoding="utf-8"))
    sp = {s["const"]: s for s in TG["species"] + TG["extra"]}
    index = []

    def P(run, tour, shot):
        return os.path.join(run, tour, shot + ".png")

    def entry(c):
        s = sp.get(c, {})
        return dict(const=c, id=s.get("id"), he=s.get("he"), en=s.get("en"))

    loads = T["loads"]
    for i in range(0, len(loads), 2):
        sh = Sheet("ld_%02d" % (i // 2 + 1))
        rec = dict(sheet=sh.name + ".png", loads=[])
        for L in loads[i:i + 2]:
            t, g, sl = L["tour"], L["tag"], L["slots"]
            sh.pair("%s party: %s" % (g, " ".join(c[8:] for c in sl)), load(P(a.en, t, g + "_party")), load(P(a.he, t, g + "_party")))
            for half in (range(0, 3), range(3, len(sl))):
                ss = list(half)
                if not ss:
                    continue
                sh.pair("%s summary slots %s: %s" % (g, ",".join(map(str, ss)), " ".join(sl[k][8:] for k in ss)),
                        strip([P(a.en, t, "%s_s%d_info" % (g, k)) for k in ss], SUM_CROP),
                        strip([P(a.he, t, "%s_s%d_info" % (g, k)) for k in ss], SUM_CROP))
            sh.pair("%s wild %s appears (foe healthbox)" % (g, L["wild"][8:]), load(P(a.en, t, g + "_bt_01")), load(P(a.he, t, g + "_bt_01")))
            sh.pair("%s send-out line, lead %s" % (g, L["lead"][8:]), load(P(a.en, t, g + "_bt_02"), MSG_CROP), load(P(a.he, t, g + "_bt_02"), MSG_CROP))
            sh.pair("%s action menu: player healthbox %s, foe %s" % (g, L["lead"][8:], L["wild"][8:]),
                    load(P(a.en, t, g + "_bt_action")), load(P(a.he, t, g + "_bt_action")))
            rec["loads"].append(dict(tour=t, tag=g, wild=L["wild"], lead=L["lead"], species=[entry(c) for c in sl]))
        sh.save(a.out)
        index.append(rec)
    for L in T["wide"]:
        t, g, sl = L["tour"], L["tag"], L["slots"]
        sh = Sheet("wide_%s" % g[1:])
        sh.pair("%s party: %s" % (g, " ".join(c[8:] for c in sl)), load(P(a.en, t, g + "_party")), load(P(a.he, t, g + "_party")))
        for half in (range(0, 3), range(3, len(sl))):
            ss = list(half)
            sh.pair("%s summary slots %s" % (g, ",".join(map(str, ss))),
                    strip([P(a.en, t, "%s_s%d_info" % (g, k)) for k in ss], SUM_CROP),
                    strip([P(a.he, t, "%s_s%d_info" % (g, k)) for k in ss], SUM_CROP))
            sh.pair("%s PC DEPOSIT panel slots %s" % (g, ",".join(map(str, ss))),
                    strip([P(a.en, t, "%s_pc_s%d" % (g, k)) for k in ss], PC_CROP),
                    strip([P(a.he, t, "%s_pc_s%d" % (g, k)) for k in ss], PC_CROP))
        for k, c in enumerate(sl):
            tt = "%s_%d_%s" % (g, k, c[len("SPECIES_"):])
            sh.pair("%s battle, %s on both sides" % (g, c[8:]), load(P(a.en, t, tt + "_bt_action")), load(P(a.he, t, tt + "_bt_action")))
        sh.save(a.out)
        index.append(dict(sheet=sh.name + ".png", loads=[dict(tour=t, tag=g, species=[entry(c) for c in sl])]))
    for L in T["abilities"]:
        t, g, sl = L["tour"], L["tag"], L["slots"]
        sh = Sheet("abil_%s" % g[1:])
        for k, (c, ab) in enumerate(sl):
            sh.pair("%s slot %d %s: %s (RANDOM ABILITIES %s)" % (g, k, c[8:], ab, "on" if L["rz"] else "off"),
                    load(P(a.en, t, "%s_s%d_info" % (g, k))), load(P(a.he, t, "%s_s%d_info" % (g, k))))
        for b, (lead, wild) in enumerate(L["battles"], 1):
            k = 1
            while os.path.exists(P(a.he, t, "%s_b%d_bt_%02d" % (g, b, k))) or os.path.exists(P(a.en, t, "%s_b%d_bt_%02d" % (g, b, k))):
                sh.pair("%s battle %d (lead %s, wild %s) page %d" % (g, b, lead[8:], wild[8:], k),
                        load(P(a.en, t, "%s_b%d_bt_%02d" % (g, b, k))), load(P(a.he, t, "%s_b%d_bt_%02d" % (g, b, k))))
                k += 1
        sh.save(a.out)
        index.append(dict(sheet=sh.name + ".png", abilities=[dict(const=c, ability=ab) for c, ab in sl], battles=L["battles"]))
    if a.popups:
        sh = Sheet("popups")
        names = sorted(f[:-4] for f in os.listdir(a.popups[1]) if f.startswith("p") and f.endswith(".png"))
        for n in names:
            sh.pair("pop-up stand-in %s" % n, load(os.path.join(a.popups[0], n + ".png"), (0, 0, 240, 112)),
                    load(os.path.join(a.popups[1], n + ".png"), (0, 0, 240, 112)))
        sh.save(a.out)
        index.append(dict(sheet="popups.png", popups=names))
    json.dump(index, open(os.path.join(a.out, "index.json"), "w"), ensure_ascii=False, indent=1)
    with open(os.path.join(a.out, "index.md"), "w", encoding="utf-8") as f:
        f.write("| sheet | load | species (string id: HE / EN) |\n| --- | --- | --- |\n")
        for r in index:
            for L in r.get("loads", []):
                f.write("| %s | %s | %s |\n" % (r["sheet"], L["tag"], "; ".join(
                    "%s (%s: %s / %s)" % (s["const"][8:], s["id"], s["he"], s["en"]) for s in L["species"])))
            if "abilities" in r:
                f.write("| %s | abilities | %s |\n" % (r["sheet"], "; ".join("%s=%s" % (x["const"][8:], x["ability"]) for x in r["abilities"])))
            if "popups" in r:
                f.write("| %s | pop-ups | %s |\n" % (r["sheet"], ", ".join(r["popups"])))
    print(len(index), "sheets ->", a.out)


if __name__ == "__main__":
    main()
