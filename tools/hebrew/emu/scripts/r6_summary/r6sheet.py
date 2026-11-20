#!/usr/bin/env python3
"""Review sheets of cropped Hebrew | English pairs, many per page, NEAREST-scaled.

    r6sheet.py SPEC.json OUTPREFIX [--scale 3] [--per 8] [--cols 1]

SPEC is a list of {"label": str, "he": png, "en": png, "crop": [x0, y0, x1, y1]}. Writes
OUTPREFIX_NN.png and OUTPREFIX_index.json (sheet -> labels).
"""
import argparse
import json

from PIL import Image, ImageDraw


def main():
    p = argparse.ArgumentParser()
    p.add_argument("spec")
    p.add_argument("out")
    p.add_argument("--scale", type=int, default=3)
    p.add_argument("--per", type=int, default=8)
    p.add_argument("--cols", type=int, default=1)
    a = p.parse_args()
    spec = json.load(open(a.spec))
    index = {}
    for si in range(0, len(spec), a.per):
        part = spec[si:si + a.per]
        cw = max((e["crop"][2] - e["crop"][0]) for e in part) * a.scale
        ch = max((e["crop"][3] - e["crop"][1]) for e in part) * a.scale
        lab = 14
        pw = 2 * cw + 6
        rows = (len(part) + a.cols - 1) // a.cols
        W = Image.new("RGB", (a.cols * pw + (a.cols - 1) * 16, rows * (ch + lab + 6)), "white")
        d = ImageDraw.Draw(W)
        for i, e in enumerate(part):
            x0, y0 = (i % a.cols) * (pw + 16), (i // a.cols) * (ch + lab + 6)
            d.text((x0 + 2, y0), e["label"], fill="black")
            for k, key in enumerate(("he", "en")):
                if not e.get(key):
                    continue
                try:
                    im = Image.open(e[key]).convert("RGB")
                except OSError:
                    d.text((x0 + k * (cw + 6) + 4, y0 + lab + 4), "missing", fill="red")
                    continue
                c = e["crop"]
                im = im.crop(c).resize(((c[2] - c[0]) * a.scale, (c[3] - c[1]) * a.scale), Image.NEAREST)
                W.paste(im, (x0 + k * (cw + 6), y0 + lab))
        name = "%s_%02d.png" % (a.out, si // a.per + 1)
        W.save(name)
        index[name] = [e["label"] for e in part]
    json.dump(index, open(a.out + "_index.json", "w"), ensure_ascii=False, indent=0)
    print("%d sheets -> %s_NN.png" % (len(index), a.out))


if __name__ == "__main__":
    main()
