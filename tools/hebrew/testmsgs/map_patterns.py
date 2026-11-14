"""For each test that passes in English and fails in Hebrew, map every MESSAGE pattern to the Hebrew the
game printed at the same position, using the English run to find which message each pattern matched."""
import os, sys
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import paths  # noqa: E402
import re, json, glob, collections, os
TREE = paths.TREE
if len(sys.argv) != 4:
    sys.exit('usage: map_patterns.py RUNS.json FAILING_TESTS.txt OUTDIR')
runs = json.load(open(sys.argv[1]))
regs = [l for l in open(sys.argv[2]).read().split('\n') if l]
OUTDIR = sys.argv[3]
regs = [re.sub(r' \d+/\d+$', '', r) for r in regs]

PAT = re.compile(r'^\s*(?:SINGLE_BATTLE_TEST|DOUBLE_BATTLE_TEST|MULTI_BATTLE_TEST|TWO_VS_ONE_BATTLE_TEST|ONE_VS_TWO_BATTLE_TEST|AI_SINGLE_BATTLE_TEST|AI_DOUBLE_BATTLE_TEST|AI_MULTI_BATTLE_TEST|AI_TWO_VS_ONE_BATTLE_TEST|AI_ONE_VS_TWO_BATTLE_TEST|WILD_BATTLE_TEST|TEST)\("((?:[^"\\]|\\.)*)"', re.M)
bodies = {}
for f in glob.glob(TREE + '/test/**/*.c', recursive=True):
    s = open(f, encoding='utf-8', errors='replace').read()
    ms = list(PAT.finditer(s))
    for i, m in enumerate(ms):
        end = ms[i + 1].start() if i + 1 < len(ms) else len(s)
        bodies.setdefault(m.group(1).replace('\\"', '"'), []).append((os.path.relpath(f, TREE), s[m.start():end], s[:m.start()].count('\n') + 1))

def load_charmap(path):
    fwd, rev = {}, {}
    for line in open(path, encoding='utf-8'):
        line = line.split('@')[0].rstrip()
        mm = re.match(r"^'(.+)'\s*=\s*([0-9A-Fa-f]{2})\s*$", line)
        if mm:
            ch = mm.group(1)
            if ch == "\\'": ch = "'"
            b = int(mm.group(2), 16)
            fwd.setdefault(ch, b); rev.setdefault(b, ch)
    return fwd, rev
FWD_EN, _ = load_charmap(os.path.join(paths.UPSTREAM, 'charmap.txt'))
FWD_HE, REV_HE = load_charmap(os.path.join(TREE, 'charmap.txt'))
# The Hebrew source writes these bytes with these characters.
for ch in ("'", '”', ' '):
    if ch in FWD_HE: REV_HE[FWD_HE[ch]] = ch

def norm(hexs):
    """Bytes the matcher compares: \\n \\l \\p count as a space; a trailing \\p is dropped."""
    bs = bytearray(bytes.fromhex(hexs))
    if bs and bs[-1] == 0xFB: bs = bs[:-1]
    return bytes(0 if b in (0xFE, 0xFA, 0xFB) else b for b in bs)

def encode_pattern(p):
    p = p.replace('\\"', '"')
    out = bytearray()
    for ch in p:
        if ch not in FWD_EN: return None
        out.append(FWD_EN[ch])
    return bytes(out)

def to_source(bs):
    out = []
    for b in bs:
        if b in REV_HE: out.append(REV_HE[b].replace('"', '\\"'))
        else: return None
    return ''.join(out)

def ascii_key(name):
    return re.sub(r'[^\x20-\x7e]', '', name)

runs_en = collections.defaultdict(dict); runs_he = collections.defaultdict(dict)
for k, v in runs['en'].items():
    n, p = k.rsplit('||', 1); runs_en[n][int(p)] = v
for k, v in runs['he'].items():
    n, p = k.rsplit('||', 1); runs_he[n][int(p)] = v

out = []; table = {}; conflicts = []
for t in sorted(set(regs)):
    cands = bodies.get(t) or [b for n, bl in bodies.items() if ascii_key(n) == t for b in bl]
    if not cands:
        out.append({'test': t, 'status': 'NO_SOURCE'}); continue
    f, body, line0 = cands[0]
    pats = []
    for m in re.finditer(r'(NOT\s+)?MESSAGE\("((?:[^"\\]|\\.)*)"\)', body):
        pats.append({'pattern': m.group(2), 'negated': bool(m.group(1)), 'line': line0 + body[:m.start()].count('\n')})
    names = [n for n in runs_en if n == t or ascii_key(n) == t]
    rec = {'test': t, 'file': f, 'patterns': []}
    for p in pats:
        hes = collections.Counter(); seen = 0
        pb = encode_pattern(p['pattern'])
        for n in names:
            for prm, ens in runs_en[n].items():
                hs = runs_he.get(n, {}).get(prm)
                if hs is None or len(hs) != len(ens):
                    continue
                for i, em in enumerate(ens):
                    if pb is not None and norm(em) == pb:
                        seen += 1
                        src = to_source(norm(hs[i]))
                        hes[src if src is not None else 'UNDECODABLE:' + hs[i]] += 1
        p['matches'] = seen
        p['hebrew'] = [h for h, _ in hes.most_common()]
        if len(p['hebrew']) == 1:
            prev = table.get(p['pattern'])
            if prev and prev != p['hebrew'][0]:
                conflicts.append((p['pattern'], prev, p['hebrew'][0]))
            table[p['pattern']] = p['hebrew'][0]
        rec['patterns'].append(p)
    out.append(rec)
json.dump(out, open(os.path.join(OUTDIR, 'mapping.json'), 'w'), ensure_ascii=False, indent=1)
json.dump(table, open(os.path.join(OUTDIR, 'table.json'), 'w'), ensure_ascii=False, indent=1)
tot = sum(len(r.get('patterns', [])) for r in out)
one = sum(1 for r in out for p in r.get('patterns', []) if len(p['hebrew']) == 1)
many = sum(1 for r in out for p in r.get('patterns', []) if len(p['hebrew']) > 1)
none_ = [(r['test'], p['pattern'], p['negated']) for r in out for p in r.get('patterns', []) if not p['hebrew']]
print('tests', len(out), 'no source', sum(1 for r in out if r.get('status') == 'NO_SOURCE'))
print('patterns', tot, 'mapped', one, 'ambiguous', many, 'unmatched', len(none_), 'distinct mapped', len(table), 'conflicts', len(conflicts))
print('unmatched negated', sum(1 for x in none_ if x[2]))
for x in none_[:12]: print('  ', x)
for c in conflicts[:5]: print('CONFLICT', c)
