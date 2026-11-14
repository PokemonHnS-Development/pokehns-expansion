#!/usr/bin/env python3
"""Side-by-side review sheets: reference run | candidate run, same screenshot names.

  pairsheets.py REF_DIR CAND_DIR OUT_DIR [--per 6] [--scale 2]

Writes OUT_DIR/<tour>_<NN>.png (each row: reference left, candidate right, 2x by default) and
OUT_DIR/index.json mapping each sheet to the screenshot names on it, in order.
"""
import argparse, json, os, struct, sys, zlib


def readpng(p):
    d = open(p, 'rb').read(); i = 8; idat = b''; w = h = 0
    while i < len(d):
        n = struct.unpack('>I', d[i:i + 4])[0]; t = d[i + 4:i + 8]; c = d[i + 8:i + 8 + n]
        if t == b'IHDR': w, h = struct.unpack('>II', c[:8])
        if t == b'IDAT': idat += c
        i += 12 + n
    raw = zlib.decompress(idat); stride = w * 3
    return w, h, [raw[y * (stride + 1) + 1:(y + 1) * (stride + 1)] for y in range(h)]


def writepng(path, w, h, rows):
    raw = b''.join(b'\0' + bytes(r) for r in rows)
    ch = lambda t, c: struct.pack('>I', len(c)) + t + c + struct.pack('>I', zlib.crc32(t + c) & 0xffffffff)
    open(path, 'wb').write(b'\x89PNG\r\n\x1a\n' + ch(b'IHDR', struct.pack('>IIBBBBB', w, h, 8, 2, 0, 0, 0)) +
                           ch(b'IDAT', zlib.compress(raw, 6)) + ch(b'IEND', b''))


def scale_rows(rows, s):
    out = []
    for r in rows:
        line = bytearray()
        for x in range(0, len(r), 3):
            line += r[x:x + 3] * s
        for _ in range(s):
            out.append(line)
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('ref'); ap.add_argument('cand'); ap.add_argument('out')
    ap.add_argument('--per', type=int, default=6)
    ap.add_argument('--scale', type=int, default=2)
    a = ap.parse_args()
    os.makedirs(a.out, exist_ok=True)
    index = {}
    gap = 4
    for tour in sorted(os.listdir(a.cand)):
        cdir = os.path.join(a.cand, tour)
        if not os.path.isdir(cdir) or tour.startswith('_'):
            continue
        shots = sorted(f for f in os.listdir(cdir) if f.endswith('.png') and f.startswith(tour.split('_')[0]))
        if not shots:
            shots = sorted(f for f in os.listdir(cdir) if f.endswith('.png'))
        for k in range(0, len(shots), a.per):
            group = shots[k:k + a.per]
            W = 240 * a.scale * 2 + gap
            rows_out = []
            for name in group:
                rp = os.path.join(a.ref, tour, name)
                cw, chh, crows = readpng(os.path.join(cdir, name))
                if os.path.exists(rp):
                    rw, rh, rrows = readpng(rp)
                else:
                    rrows = [bytes(240 * 3)] * 160
                L = scale_rows(rrows, a.scale); R = scale_rows(crows, a.scale)
                for y in range(len(L)):
                    rows_out.append(bytes(L[y]) + b'\xff\x00\xff' * gap + bytes(R[y]))
                for _ in range(gap):
                    rows_out.append(b'\xff\x00\xff' * W)
            sheet = '%s_%02d.png' % (tour, k // a.per + 1)
            writepng(os.path.join(a.out, sheet), W, len(rows_out), rows_out)
            index[sheet] = group
    json.dump(index, open(os.path.join(a.out, 'index.json'), 'w'), indent=1)
    print('%d sheets' % len(index))


if __name__ == '__main__':
    main()
