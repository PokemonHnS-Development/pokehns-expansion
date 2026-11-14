#!/usr/bin/env python3
"""Hebrew | English pairs of the same screenshot, NEAREST-scaled, optionally cropped.

    r6pair.py OUT.png HEDIR ENDIR NAME[,NAME...] [--scale 4] [--crop x0,y0,x1,y1] [--cols 1]

NAME is a path under the tour run folders (TOUR/SHOT, without .png). Each row is HE left, EN right.
"""
import argparse
import os

from PIL import Image, ImageDraw


def main():
    p = argparse.ArgumentParser()
    p.add_argument("out")
    p.add_argument("he")
    p.add_argument("en")
    p.add_argument("names")
    p.add_argument("--scale", type=int, default=4)
    p.add_argument("--crop")
    p.add_argument("--cols", type=int, default=1)
    a = p.parse_args()
    names = a.names.split(",")
    crop = tuple(int(v) for v in a.crop.split(",")) if a.crop else (0, 0, 240, 160)
    w, h = (crop[2] - crop[0]) * a.scale, (crop[3] - crop[1]) * a.scale
    pw = 2 * w + 6
    rows = (len(names) + a.cols - 1) // a.cols
    W = Image.new("RGB", (a.cols * pw + (a.cols - 1) * 12, rows * (h + 4)), "white")
    for i, n in enumerate(names):
        x0, y0 = (i % a.cols) * (pw + 12), (i // a.cols) * (h + 4)
        for k, d in enumerate((a.he, a.en)):
            f = os.path.join(d, n + ".png")
            if not os.path.exists(f):
                ImageDraw.Draw(W).text((x0 + k * (w + 6) + 4, y0 + 4), "missing " + n, fill="red")
                continue
            im = Image.open(f).convert("RGB").crop(crop).resize((w, h), Image.NEAREST)
            W.paste(im, (x0 + k * (w + 6), y0))
    W.save(a.out)
    print(a.out, W.size)


if __name__ == "__main__":
    main()
