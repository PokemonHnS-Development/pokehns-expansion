#!/usr/bin/env python3
"""Side-by-side Hebrew | English screenshots at a scale (default 4x, NEAREST).

    pair4x.py HE_DIR EN_DIR OUT_DIR [SCALE] [REGEX]
"""
import os
import re
import sys
from PIL import Image

he, en, out = sys.argv[1:4]
scale = int(sys.argv[4]) if len(sys.argv) > 4 else 4
rx = re.compile(sys.argv[5]) if len(sys.argv) > 5 else None
os.makedirs(out, exist_ok=True)
n = 0
for f in sorted(os.listdir(he)):
    if not f.endswith('.png') or f.startswith('_') or (rx and not rx.search(f)):
        continue
    a = Image.open(os.path.join(he, f)).convert('RGB')
    pe = os.path.join(en, f)
    b = Image.open(pe).convert('RGB') if os.path.exists(pe) else Image.new('RGB', a.size, (255, 0, 255))
    w, h = a.size
    im = Image.new('RGB', (2 * w * scale + 8, h * scale), (255, 255, 255))
    im.paste(a.resize((w * scale, h * scale), Image.NEAREST), (0, 0))
    im.paste(b.resize((w * scale, h * scale), Image.NEAREST), (w * scale + 8, 0))
    im.save(os.path.join(out, f))
    n += 1
print('%d pairs -> %s' % (n, out))
