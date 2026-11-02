#!/usr/bin/env python3
"""Review helpers for the r10 travel tours (r10travel.py writes OUT/TOUR/texts.jsonl, notes.jsonl
and, on the clip build, clip.json).

  r10review.py texts HE_OUT[,HE_OUT2...] EN_OUT[,EN_OUT2...] REPORT_DIR
      Pairs the Hebrew and English messages of every tour by what was being done (the `ctx` of
      each screenshot: sign / npc / furniture and its script label), then writes
        REPORT_DIR/messages.json   [{tour, ctx, he: [...], en: [...], shots: [...]}]
        REPORT_DIR/latin.txt       Latin words left in Hebrew messages (save-file names aside)
        REPORT_DIR/glossary.txt    an English message names a glossary row (place, person,
                                   item, trainer class ...) but the Hebrew message lacks that
                                   row's Hebrew (a lead to look at, not a verdict)
        REPORT_DIR/clips.txt       every glyph the clip build drew outside its window
        REPORT_DIR/notes.txt       unreachable signs / NPCs, failures
  r10review.py strips HE_OUT[,..] EN_OUT[,..] OUTPREFIX REGEX X0,Y0,X1,Y1 [PER_SHEET] [SCALE]
      The same crop of every matching shot (REGEX on 'tour/shot') from both runs, Hebrew left,
      English right, PER_SHEET rows per sheet (OUTPREFIX_NN.png, OUTPREFIX_index.txt).
  r10review.py pairs HE_TOURDIR EN_TOURDIR OUT_DIR [--scale S] [--match RE]
      Hebrew | English side by side, one PNG per shot name both runs have.
"""
import csv
import glob
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
GLOSSARY = os.path.normpath(os.path.join(HERE, "..", "..", "..", "..", "..", "translation", "hebrew", "glossary.csv"))
NAME_KINDS = ("mapsec", "place", "name", "speaker", "item", "trainer_class", "trainer_name", "decoration",
              "berry", "species", "move", "trade_name")
HEB = re.compile(r"[א-ת]")
SAVE_NAMES = {"NAME_GOLD", "NAME_SILVER"}      # the ladder saves' player and rival names (Latin in the save)


def tours_in(dirs):
    out = {}
    for d in dirs.split(","):
        for t in sorted(glob.glob(os.path.join(d, "*", "texts.jsonl"))):
            out[os.path.basename(os.path.dirname(t))] = os.path.dirname(t)
    return out


def load_msgs(tdir):
    """{ctx: [distinct messages in order]} and {ctx: [shot names]}."""
    msgs, shots = {}, {}
    for line in open(os.path.join(tdir, "texts.jsonl"), encoding="utf-8"):
        r = json.loads(line)
        if "text" not in r:
            continue
        ctx = r.get("ctx", "")
        lst = msgs.setdefault(ctx, [])
        if not lst or lst[-1] != r["text"]:
            lst.append(r["text"])
        shots.setdefault(ctx, []).append(r["shot"])
    return msgs, shots


def strip_codes(t):
    t = t.replace("’", "'")
    return re.sub(r"\{[^}]*\}", " ", t).replace("\\n", " ").replace("\\l", " ").replace("\\p", " ").rstrip("$")


def glossary_rows():
    rows = []
    for r in csv.DictReader(open(GLOSSARY, encoding="utf-8")):
        if r["kind"] not in NAME_KINDS or not r["proposed_hebrew"] or not r["english"]:
            continue
        en = re.sub(r"\{PKMN\}", "POKéMON", r["english"]).strip()
        en = re.sub(r"\s*\(.*\)$", "", en)
        if len(en) < 4 or not re.search(r"[A-Za-z]", en) or r["constant"] in SAVE_NAMES:
            continue
        rows.append((r["kind"], r["constant"], en, r["proposed_hebrew"]))
    return rows


def heb_core(h):
    """The words of a Hebrew name that must show up (prefix letters and the generic
    'city/town/route' words aside): the longest word, without a leading ה/ב/ל/מ/ו/ש/כ."""
    words = [w for w in re.split(r"[\s\-]+", h) if HEB.search(w)]
    generic = {"העיר", "העיירה", "דרך", "האי", "מערת", "מערה", "הר"}
    words = [w for w in words if w not in generic] or words
    if not words:
        return None
    w = max(words, key=len)
    return w.lstrip("'\"")


def cmd_texts(he_dirs, en_dirs, rep):
    os.makedirs(rep, exist_ok=True)
    he, en = tours_in(he_dirs), tours_in(en_dirs)
    rows = glossary_rows()
    out, latin, gl = [], {}, []
    for tour in sorted(he):
        hm, hs = load_msgs(he[tour])
        em, es = load_msgs(en[tour]) if tour in en else ({}, {})
        for ctx in hm:
            he_list = hm[ctx]
            en_list = em.get(ctx, [])
            out.append(dict(tour=tour, ctx=ctx, he=he_list, en=en_list, shots=hs[ctx][:40]))
            for t in he_list:
                for w in re.findall(r"[A-Za-z][A-Za-z.'\-]+", strip_codes(t)):
                    latin.setdefault(w, []).append("%s | %s" % (tour, ctx))
            hj = " ".join(strip_codes(t) for t in he_list)
            ej = " ".join(strip_codes(t) for t in en_list)
            words = set(re.findall(r"[A-Za-zé']+", ej))
            wl = {w.lower() for w in words}
            for kind, const, ename, hname in rows:
                first = (re.findall(r"[A-Za-zé']+", ename) or [""])[0]
                if (first not in words) and not (ename.upper() != ename and first.lower() in wl):
                    continue
                if not re.search(r"(?<![A-Za-z])%s(?![A-Za-z])" % re.escape(ename), ej, 0 if ename.upper() == ename else re.I):
                    continue
                core = heb_core(hname)
                if core and core not in hj and hname not in hj:
                    gl.append("%s | %s | %s %s = %s | HE: %s | EN: %s" % (tour, ctx, kind, ename, hname,
                                                                        hj[:300], ej[:300]))
    json.dump(out, open(os.path.join(rep, "messages.json"), "w", encoding="utf-8"), ensure_ascii=False, indent=1)
    with open(os.path.join(rep, "latin.txt"), "w", encoding="utf-8") as fh:
        for w, where in sorted(latin.items(), key=lambda kv: -len(kv[1])):
            fh.write("%-20s %4d  %s\n" % (w, len(where), "; ".join(sorted(set(where))[:6])))
    with open(os.path.join(rep, "glossary.txt"), "w", encoding="utf-8") as fh:
        fh.write("\n".join(sorted(set(gl))) + "\n")
    clips = []
    notes = []
    for tour in sorted(he):
        cj = os.path.join(he[tour], "clip.json")
        if os.path.exists(cj):
            c = json.load(open(cj))
            for shot, recs in c.get("shots", {}).items():
                for r in recs:
                    clips.append("%s | %s | %s" % (tour, shot, json.dumps(r, ensure_ascii=False)))
        nj = os.path.join(he[tour], "notes.jsonl")
        if os.path.exists(nj):
            for line in open(nj, encoding="utf-8"):
                notes.append("%s | %s" % (tour, line.strip()))
    open(os.path.join(rep, "clips.txt"), "w", encoding="utf-8").write("\n".join(clips) + "\n")
    open(os.path.join(rep, "notes.txt"), "w", encoding="utf-8").write("\n".join(notes) + "\n")
    print("%d contexts, %d Latin words, %d glossary leads, %d clip records, %d notes"
          % (len(out), len(latin), len(set(gl)), len(clips), len(notes)))


def cmd_pairs(hdir, edir, outdir, scale=2, match=None):
    from PIL import Image
    os.makedirs(outdir, exist_ok=True)
    n = 0
    for p in sorted(glob.glob(os.path.join(hdir, "*.png"))):
        name = os.path.basename(p)
        if name.startswith(("_", "ct0")) or (match and not re.search(match, name)):
            continue
        q = os.path.join(edir, name)
        if not os.path.exists(q):
            continue
        a = Image.open(p).convert("RGB").resize((240 * scale, 160 * scale), Image.NEAREST)
        b = Image.open(q).convert("RGB").resize((240 * scale, 160 * scale), Image.NEAREST)
        im = Image.new("RGB", (480 * scale + 4, 160 * scale), (255, 0, 255))
        im.paste(a, (0, 0))
        im.paste(b, (240 * scale + 4, 0))
        im.save(os.path.join(outdir, name))
        n += 1
    print("%d pair(s) in %s" % (n, outdir))


def cmd_strips(he_dirs, en_dirs, outprefix, regex, box, per_sheet=8, scale=2):
    """Crop BOX (x0,y0,x1,y1 in GBA pixels) from every shot whose 'tour/shot' matches REGEX in both
    runs and stack Hebrew | English rows, PER_SHEET rows per sheet: OUTPREFIX_NN.png (+ .txt index)."""
    from PIL import Image, ImageDraw
    he, en = tours_in(he_dirs), tours_in(en_dirs)
    x0, y0, x1, y1 = box
    w, h = (x1 - x0) * scale, (y1 - y0) * scale
    rows = []
    for tour in sorted(he):
        if tour not in en:
            continue
        for p in sorted(glob.glob(os.path.join(he[tour], "*.png"))):
            name = os.path.basename(p)[:-4]
            if name.startswith(("_", "ct0")) or not re.search(regex, tour + "/" + name):
                continue
            q = os.path.join(en[tour], name + ".png")
            if os.path.exists(q):
                rows.append((tour, name, p, q))
    os.makedirs(os.path.dirname(os.path.abspath(outprefix)), exist_ok=True)
    k = 0
    for i in range(0, len(rows), per_sheet):
        chunk = rows[i:i + per_sheet]
        sheet = Image.new("RGB", (2 * w + 6, len(chunk) * (h + 12)), (60, 0, 60))
        d = ImageDraw.Draw(sheet)
        for j, (tour, name, p, q) in enumerate(chunk):
            y = j * (h + 12)
            d.text((2, y), "%d %s/%s" % (i + j, tour, name), fill=(255, 255, 0))
            for col, src in enumerate((p, q)):
                im = Image.open(src).convert("RGB").crop((x0, y0, x1, y1)).resize((w, h), Image.NEAREST)
                sheet.paste(im, (col * (w + 6), y + 12))
        k += 1
        sheet.save("%s_%02d.png" % (outprefix, k))
    with open(outprefix + "_index.txt", "w") as fh:
        for i, (tour, name, p, q) in enumerate(rows):
            fh.write("%d %s %s\n" % (i, p, q))
    print("%d rows in %d sheet(s): %s_NN.png" % (len(rows), k, outprefix))


def main():
    a = sys.argv[1:]
    if not a:
        print(__doc__)
        return 2
    if a[0] == "texts":
        cmd_texts(a[1], a[2], a[3])
    elif a[0] == "mixed":
        for x in mixed_shots(a[1]):
            print(x)
    elif a[0] == "strips":
        box = tuple(int(v) for v in a[5].split(","))
        per = int(a[6]) if len(a) > 6 else 8
        sc = int(a[7]) if len(a) > 7 else 2
        cmd_strips(a[1], a[2], a[3], a[4], box, per, sc)
    elif a[0] == "pairs":
        scale = int(a[a.index("--scale") + 1]) if "--scale" in a else 2
        match = a[a.index("--match") + 1] if "--match" in a else None
        cmd_pairs(a[1], a[2], a[3], scale, match)
    return 0




def mixed_shots(he_dirs, pattern=r"[0-9A-Za-z¥₽$%()\"”“'’…:;]"):
    """'tour/shot' of every Hebrew message page whose text holds digits, Latin letters or
    punctuation that RTL drawing reorders (one shot per distinct message per context)."""
    out = []
    rx = re.compile(pattern)
    for tour, tdir in sorted(tours_in(he_dirs).items()):
        seen = set()
        for line in open(os.path.join(tdir, "texts.jsonl"), encoding="utf-8"):
            r = json.loads(line)
            if "text" not in r or r.get("battle"):
                continue
            body = strip_codes(r["text"])
            key = (r.get("ctx"), r["text"])
            if rx.search(body) and HEB.search(body):
                out.append("%s/%s" % (tour, r["shot"]))
                seen.add(key)
    return out


if __name__ == "__main__":
    sys.exit(main())
