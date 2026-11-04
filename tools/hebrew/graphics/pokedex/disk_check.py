"""Independent check of the written files: PIL-read size/mode/palette vs the English release,
IHDR bit depth and colour type, PNG == dry-run output byte for byte, tilemaps == dry-run output,
and the number of changed pixels / entries per file. Run it after make_pokedex.py --write; the
files checked are those under graphics/pokedex/hgss in HNS_TREE that differ from the release."""
import io, os, struct, subprocess, sys
from PIL import Image
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import gpaths
REPO = gpaths.TREE
TMP = os.path.join(gpaths.out('pokedex'), 'tmp')
HG = 'graphics/pokedex/hgss/'

def head(rel):
    return gpaths.english(rel)

def ihdr(data):
    w, h, depth, ctype = struct.unpack('>IIBB', data[16:26])
    return w, h, depth, ctype

changed = []
for name in sorted(os.listdir(os.path.join(REPO, HG))):
    rel = HG + name
    if not name.endswith(('.png', '.bin')):
        continue
    try:
        if open(os.path.join(REPO, rel), 'rb').read() != head(rel):
            changed.append(rel)
    except subprocess.CalledProcessError:
        pass
ok = True
for rel in changed:
    new = open(os.path.join(REPO, rel), 'rb').read()
    old = head(rel)
    tmp = open(os.path.join(TMP, os.path.basename(rel)), 'rb').read()
    same_tmp = new == tmp
    if rel.endswith('.png'):
        a, b = Image.open(io.BytesIO(old)), Image.open(io.BytesIO(new))
        res = dict(size=a.size == b.size, mode=a.mode == b.mode, palette=a.getpalette() == b.getpalette(),
                   ihdr=ihdr(old) == ihdr(new), tmp=same_tmp)
        diff = sum(1 for p, q in zip(a.getdata(), b.getdata()) if p != q)
        print('%-58s %s ihdr=%s changed_px=%d' % (rel, ' '.join('%s=%s' % kv for kv in res.items()), ihdr(new), diff))
    else:
        n = len(old) // 2
        eo, en = struct.unpack('<%dH' % n, old), struct.unpack('<%dH' % n, new)
        d = [(i % 32, i // 32, eo[i], en[i]) for i in range(n) if eo[i] != en[i]]
        res = dict(size=len(old) == len(new), tmp=same_tmp)
        print('%-58s %s entries_changed=%d %s' % (rel, ' '.join('%s=%s' % kv for kv in res.items()), len(d), d))
    ok &= all(res.values())
print('ALL OK' if ok else 'PROBLEMS')
