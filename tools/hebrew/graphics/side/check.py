"""Verify an edited PNG against its English version: size, depth, colour type, palette, tRNS."""
import sys, subprocess, struct, zlib, os
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import gpaths
WT = gpaths.TREE
def chunks(data):
    i = 8; out = []
    while i < len(data):
        ln, = struct.unpack('>I', data[i:i+4]); typ = data[i+4:i+8]
        out.append((typ, data[i+8:i+8+ln])); i += 12 + ln
    return out
def info(data):
    c = chunks(data)
    ihdr = dict(c)[b'IHDR']
    w, h, bd, ct, _, _, il = struct.unpack('>IIBBBBB', ihdr)
    other = [(t, b) for t, b in c if t not in (b'IHDR', b'IDAT', b'IEND')]
    return (w, h, bd, ct, il), other
def check(path):
    new = open(os.path.join(WT, path), 'rb').read()
    old = gpaths.english(path)
    a, ao = info(old); b, bo = info(new)
    ok = a == b and ao == bo
    return ok, a, b, [t for t, _ in ao], [t for t, _ in bo]
if __name__ == '__main__':
    bad = 0
    for p in sys.argv[1:]:
        ok, a, b, ac, bc = check(p)
        print('%-55s %s  %s %s' % (p, 'OK ' if ok else 'BAD', b, bc if ok else (a, ac)))
        bad += not ok
    sys.exit(bad)
