#!/usr/bin/env python3
"""Compare crosscore frame dumps between cores, after reducing every pixel to RGB555, the GBA's own
15-bit colour. Cores hand frames over as RGB565 or XRGB8888 and each widens the 15 bits its own
way (on the same frame, VBA-Next sets the low bit of the 6-bit green where mGBA leaves it clear),
so only the 15 bits are compared.

  ccdiff.py REF_DIR DIR... -> per shot: differing pixel count against REF_DIR, and PNGs of each

Exit status 0 when the table was printed, 2 for wrong arguments; -h or --help prints this text.
"""
import os, struct, sys, zlib

USAGE = 'usage: ccdiff.py REF_DIR DIR...   (--help for details)'

def load(path):
    d = open(path, 'rb').read()
    w, h = struct.unpack('<II', d[:8]); px = d[8:]
    out = []
    for i in range(w * h):
        b, g, r = px[i * 4], px[i * 4 + 1], px[i * 4 + 2]
        out.append(((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3))
    return w, h, out

def png(path, w, h, pix555):
    rows = []
    for y in range(h):
        row = bytearray([0])
        for x in range(w):
            v = pix555[y * w + x]
            row += bytes([((v >> 10) & 31) << 3, ((v >> 5) & 31) << 3, (v & 31) << 3])
        rows.append(bytes(row))
    def chunk(t, data):
        c = t + data
        return struct.pack('>I', len(data)) + c + struct.pack('>I', zlib.crc32(c) & 0xffffffff)
    open(path, 'wb').write(b'\x89PNG\r\n\x1a\n' + chunk(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 2, 0, 0, 0))
                          + chunk(b'IDAT', zlib.compress(b''.join(rows), 9)) + chunk(b'IEND', b''))

if sys.argv[1:2] in (['-h'], ['--help']):
    print(__doc__.strip())
    sys.exit(0)
if len(sys.argv) < 3:
    print(USAGE, file=sys.stderr)
    sys.exit(2)
for d in sys.argv[1:]:
    if not os.path.isdir(d):
        print('ccdiff.py: %s is not a directory' % d, file=sys.stderr)
        print(USAGE, file=sys.stderr)
        sys.exit(2)
ref = sys.argv[1]
for d in [ref] + sys.argv[2:]:
    for f in sorted(os.listdir(d)):
        if f.endswith('.raw'):
            w, h, p = load(os.path.join(d, f)); png(os.path.join(d, f[:-4] + '.png'), w, h, p)
shots = sorted(f for f in os.listdir(ref) if f.endswith('.raw'))
print('%-10s' % 'shot' + ''.join('%14s' % os.path.basename(d.rstrip('/')) for d in sys.argv[2:]))
for s in shots:
    w, h, a = load(os.path.join(ref, s))
    cells = []
    for d in sys.argv[2:]:
        p = os.path.join(d, s)
        if not os.path.exists(p):
            cells.append('missing'); continue
        w2, h2, b = load(p)
        cells.append('size %dx%d' % (w2, h2) if (w2, h2) != (w, h) else str(sum(1 for x, y in zip(a, b) if x != y)))
    print('%-10s' % s[:-4] + ''.join('%14s' % c for c in cells))
