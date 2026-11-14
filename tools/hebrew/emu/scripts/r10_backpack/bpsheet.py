#!/usr/bin/env python3
"""bpsheet.py: contact sheets for the r10 backpack review (PIL, NEAREST).

    bpsheet.py sheet OUT.png SCALE COLS PNG...            tiles with the file name under each
    bpsheet.py pairs OUT.png SCALE COLS HEDIR ENDIR NAME...  Hebrew | English side by side per NAME
                                                         (NAME = shot name without .png)
    bpsheet.py crop OUT.png SCALE X0,Y0,X1,Y1 COLS HEDIR ENDIR NAME...
                                                         the same crop of each pair, stacked
"""
import os
import sys
from PIL import Image, ImageDraw


def _tile(ims, labels, cols, out, pad=4, lab=10):
    w = max(i.width for i in ims)
    h = max(i.height for i in ims)
    rows = (len(ims) + cols - 1) // cols
    s = Image.new("RGB", (cols * (w + pad), rows * (h + pad + lab)), (40, 40, 40))
    d = ImageDraw.Draw(s)
    for k, (im, t) in enumerate(zip(ims, labels)):
        x, y = (k % cols) * (w + pad), (k // cols) * (h + pad + lab)
        s.paste(im, (x, y))
        d.text((x + 2, y + h), t[:int(w / 6)], fill=(255, 255, 0))
    s.save(out)


def main():
    cmd = sys.argv[1]
    if cmd == "sheet":
        out, sc, cols = sys.argv[2], int(sys.argv[3]), int(sys.argv[4])
        ims, labs = [], []
        for p in sys.argv[5:]:
            im = Image.open(p).convert("RGB")
            ims.append(im.resize((im.width * sc, im.height * sc), Image.NEAREST))
            labs.append(os.path.basename(p)[:-4])
        _tile(ims, labs, cols, out)
    elif cmd in ("pairs", "crop"):
        if cmd == "pairs":
            out, sc, cols, he, en = sys.argv[2], int(sys.argv[3]), int(sys.argv[4]), sys.argv[5], sys.argv[6]
            box, names = None, sys.argv[7:]
        else:
            out, sc = sys.argv[2], int(sys.argv[3])
            box = tuple(int(v) for v in sys.argv[4].split(","))
            cols, he, en, names = int(sys.argv[5]), sys.argv[6], sys.argv[7], sys.argv[8:]
        ims, labs = [], []
        for n in names:
            a = Image.open(os.path.join(he, n + ".png")).convert("RGB")
            pe = os.path.join(en, n + ".png")
            b = Image.open(pe).convert("RGB") if os.path.exists(pe) else Image.new("RGB", a.size, (255, 0, 255))
            if box:
                a, b = a.crop(box), b.crop(box)
            pair = Image.new("RGB", (a.width * 2 + 2, a.height), (255, 0, 255))
            pair.paste(a, (0, 0))
            pair.paste(b, (a.width + 2, 0))
            ims.append(pair.resize((pair.width * sc, pair.height * sc), Image.NEAREST))
            labs.append(n)
        _tile(ims, labs, cols, out)


if __name__ == "__main__":
    main()
