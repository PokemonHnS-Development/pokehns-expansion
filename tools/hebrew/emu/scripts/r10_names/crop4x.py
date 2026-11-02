#!/usr/bin/env python3
"""Crop a region of one or more screenshots and scale it (default 4x, NEAREST), stacked.

    crop4x.py OUT.png X0,Y0,X1,Y1 [SCALE] PNG...
"""
import sys
from PIL import Image

out, box = sys.argv[1], [int(v) for v in sys.argv[2].split(',')]
args = sys.argv[3:]
scale = 4
if args and args[0].isdigit():
    scale = int(args[0])
    args = args[1:]
ims = [Image.open(p).convert('RGB').crop(box) for p in args]
w, h = box[2] - box[0], box[3] - box[1]
res = Image.new('RGB', (w * scale, (h * scale + 4) * len(ims)), (255, 0, 255))
for i, im in enumerate(ims):
    res.paste(im.resize((w * scale, h * scale), Image.NEAREST), (0, i * (h * scale + 4)))
res.save(out)
