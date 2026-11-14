#!/usr/bin/env python3
"""Hebrew | English screenshot pairs for review (PIL, NEAREST).

    pairs.py pair HE_DIR EN_DIR OUT_DIR [SCALE] [REGEX]
        one image per shot name present in HE_DIR: Hebrew left, English right (magenta when the
        English shot is missing), at SCALE (default 4)
    pairs.py sheet HE_DIR EN_DIR OUT_PREFIX [SCALE] [REGEX] [PER]
        the same pairs stacked PER (default 4) to an image with the shot name above each pair:
        OUT_PREFIX_01.png, _02 ...
    pairs.py crop IMAGE X0 Y0 X1 Y1 OUT [SCALE]
        a GBA-pixel region of one screenshot at SCALE (default 4)
"""
import os
import re
import sys
from PIL import Image, ImageDraw


def _pair(he, en, name, scale):
    a = Image.open(os.path.join(he, name)).convert("RGB")
    pe = os.path.join(en, name)
    b = Image.open(pe).convert("RGB") if os.path.exists(pe) else Image.new("RGB", a.size, (255, 0, 255))
    w, h = a.size
    im = Image.new("RGB", (2 * w * scale + 8, h * scale), (255, 255, 255))
    im.paste(a.resize((w * scale, h * scale), Image.NEAREST), (0, 0))
    im.paste(b.resize((w * scale, h * scale), Image.NEAREST), (w * scale + 8, 0))
    return im


def _names(he, rx):
    rx = re.compile(rx) if rx else None
    return [f for f in sorted(os.listdir(he))
            if f.endswith(".png") and not f.startswith("ct0") and (not rx or rx.search(f))]


def main(argv):
    cmd = argv[1]
    if cmd == "pair":
        he, en, out = argv[2:5]
        scale = int(argv[5]) if len(argv) > 5 else 4
        os.makedirs(out, exist_ok=True)
        names = _names(he, argv[6] if len(argv) > 6 else None)
        for f in names:
            _pair(he, en, f, scale).save(os.path.join(out, f))
        print("%d pairs -> %s" % (len(names), out))
    elif cmd == "sheet":
        he, en, out = argv[2:5]
        scale = int(argv[5]) if len(argv) > 5 else 2
        names = _names(he, argv[6] if len(argv) > 6 else None)
        per = int(argv[7]) if len(argv) > 7 else 4
        os.makedirs(os.path.dirname(out) or ".", exist_ok=True)
        k = 0
        for i in range(0, len(names), per):
            chunk = names[i:i + per]
            ims = [_pair(he, en, f, scale) for f in chunk]
            W = max(im.size[0] for im in ims)
            H = sum(im.size[1] + 14 for im in ims)
            sheet = Image.new("RGB", (W, H), (255, 255, 255))
            d = ImageDraw.Draw(sheet)
            y = 0
            for f, im in zip(chunk, ims):
                d.text((2, y), f, fill=(200, 0, 0))
                sheet.paste(im, (0, y + 14))
                y += im.size[1] + 14
            k += 1
            sheet.save("%s_%02d.png" % (out, k))
        print("%d pairs in %d sheet(s) -> %s_NN.png" % (len(names), k, out))
    elif cmd == "strip":
        # strip HE_DIRS EN_DIRS OUT_PREFIX Y0 Y1 [SCALE] [REGEX] [PER]: the rows Y0..Y1 (the message box)
        # of every pair, PER (default 16) to an image; HE_DIRS / EN_DIRS are comma lists (same order)
        hes, ens, out = argv[2].split(","), argv[3].split(","), argv[4]
        y0, y1 = int(argv[5]), int(argv[6])
        scale = int(argv[7]) if len(argv) > 7 else 2
        rx = argv[8] if len(argv) > 8 else None
        per = int(argv[9]) if len(argv) > 9 else 16
        items = [(he, en, f) for he, en in zip(hes, ens) for f in _names(he, rx)]
        os.makedirs(os.path.dirname(out) or ".", exist_ok=True)
        k = 0
        for i in range(0, len(items), per):
            chunk = items[i:i + per]
            rows = []
            for he, en, f in chunk:
                im = _pair(he, en, f, 1)
                w = im.size[0]
                a = im.crop((0, y0, w, y1))
                rows.append((os.path.basename(he) + "/" + f, a.resize((a.size[0] * scale, a.size[1] * scale), Image.NEAREST)))
            W = max(r[1].size[0] for r in rows)
            H = sum(r[1].size[1] + 12 for r in rows)
            sheet = Image.new("RGB", (W, H), (255, 255, 255))
            d = ImageDraw.Draw(sheet)
            y = 0
            for name, r in rows:
                d.text((2, y), name, fill=(200, 0, 0))
                sheet.paste(r, (0, y + 12))
                y += r.size[1] + 12
            k += 1
            sheet.save("%s_%02d.png" % (out, k))
        print("%d strips in %d sheet(s) -> %s_NN.png" % (len(items), k, out))
    elif cmd == "crop":
        img, x0, y0, x1, y1, out = argv[2], int(argv[3]), int(argv[4]), int(argv[5]), int(argv[6]), argv[7]
        scale = int(argv[8]) if len(argv) > 8 else 4
        im = Image.open(img).convert("RGB").crop((x0, y0, x1, y1))
        im.resize((im.size[0] * scale, im.size[1] * scale), Image.NEAREST).save(out)
        print("crop -> %s" % out)
    else:
        raise SystemExit(__doc__)


if __name__ == "__main__":
    main(sys.argv)
