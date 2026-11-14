"""Parse the HNSDUMP message logs of the English and Hebrew test runs into per-run message lists."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import paths  # noqa: E402
import re, json, sys, collections

def charmap(path):
    rev = {}
    for line in open(path, encoding='utf-8'):
        line = line.split('@')[0].rstrip()
        m = re.match(r"^'(.+)'\s*=\s*([0-9A-Fa-f]{2})\s*$", line)
        if m:
            ch = m.group(1)
            if ch == "\\'": ch = "'"
            b = int(m.group(2), 16)
            rev.setdefault(b, ch)
    return rev

def decode(hexs, rev):
    bs = bytes.fromhex(hexs)
    out = []
    i = 0
    while i < len(bs):
        b = bs[i]
        if b == 0xFE: out.append('\\n')
        elif b == 0xFA: out.append('\\l')
        elif b == 0xFB: out.append('\\p')
        elif b in rev and b not in (0xFC, 0xFD, 0xF9, 0xF8, 0xF7):
            out.append(rev[b])
        else:
            out.append('{%02X}' % b)
        i += 1
    return ''.join(out)

def parse(log, rev):
    runs = collections.OrderedDict()   # (name, param) -> list of decoded messages (all trials concatenated, in order)
    cur = None; buf = []
    for raw in open(log, 'rb'):
        line = raw.decode('latin-1').strip()
        line = re.sub(r'\x1b\[[0-9;]*m', '', line)
        if line.startswith('MSGT|'):
            _, p, name = line.split('|', 2)
            cur = (name, int(p)); buf = []
        elif line.startswith('MSGH|') and cur:
            buf.append(line[5:])
        elif line.startswith('MSGE|') and cur:
            runs.setdefault(cur, []).append(''.join(buf))
            cur = None
    return runs

if __name__ == '__main__':
    en = parse(sys.argv[1], charmap(os.path.join(paths.UPSTREAM, 'charmap.txt')))
    he = parse(sys.argv[2], charmap(os.path.join(paths.TREE, 'charmap.txt')))
    out = {'en': {'%s||%d' % k: v for k, v in en.items()}, 'he': {'%s||%d' % k: v for k, v in he.items()}}
    json.dump(out, open(sys.argv[3], 'w'), ensure_ascii=False)
    print(len(en), 'english runs,', len(he), 'hebrew runs')
    same = sum(1 for k in en if k in he and len(en[k]) == len(he[k]))
    print('runs with equal message counts:', same, 'of', len(set(en) & set(he)))
