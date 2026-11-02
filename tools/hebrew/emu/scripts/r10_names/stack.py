#!/usr/bin/env python3
"""Stack images vertically (review sheets).   stack.py OUT.png IMG..."""
import sys
from PIL import Image
ims = [Image.open(p).convert('RGB') for p in sys.argv[2:]]
w = max(i.size[0] for i in ims)
h = sum(i.size[1] + 6 for i in ims)
out = Image.new('RGB', (w, h), (255, 0, 255))
y = 0
for i in ims:
    out.paste(i, (0, y))
    y += i.size[1] + 6
out.save(sys.argv[1])
