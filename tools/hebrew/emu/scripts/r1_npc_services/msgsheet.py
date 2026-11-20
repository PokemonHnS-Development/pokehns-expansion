#!/usr/bin/env python3
"""msgsheet.py TOUR OUT.png Y0 Y1 NAME|GLOB ...: rows Y0..Y1 of each shot, Hebrew | English, 2x."""
import os, sys, glob
from PIL import Image, ImageDraw
R = os.path.dirname(os.path.abspath(__file__))
t, out, y0, y1 = sys.argv[1], sys.argv[2], int(sys.argv[3]), int(sys.argv[4])
names = []
for a in sys.argv[5:]:
    if "*" in a:
        names += sorted(os.path.basename(p)[:-4] for p in glob.glob(os.path.join(R, "he", t, a + ".png")))
    else:
        names.append(a)
z = 2; W, H = 240 * z, (y1 - y0) * z
c = Image.new("RGB", (2 * W + 8, len(names) * (H + 12)), (60, 0, 60)); d = ImageDraw.Draw(c)
for i, n in enumerate(names):
    y = i * (H + 12); d.text((2, y), n, fill=(255, 255, 0))
    for j, lang in enumerate(("he", "en")):
        p = os.path.join(R, lang, t, n + ".png")
        if os.path.exists(p):
            im = Image.open(p).convert("RGB").crop((0, y0, 240, y1))
            c.paste(im.resize((W, H), Image.NEAREST), (j * (W + 8), y + 11))
c.save(os.path.join(R, "cmp", out)); print(len(names), "rows")
