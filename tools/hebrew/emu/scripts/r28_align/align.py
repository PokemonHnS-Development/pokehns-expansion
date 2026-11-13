#!/usr/bin/env python3
"""Pair the English shots with the Hebrew ones by text page, not by name, and write the English
side under the Hebrew names: align.py EN_DIR HE_DIR OUT_DIR. A shot name is SEGMENT_NN[_TAG]
(r10pg's Shooter) or a plain name (snap). Within a segment the two sequences are cut into runs at
the tagged shots (menu, pick, party, ...); tagged shots pair in order of their tag, and plain pages
of a run pair in order (when the runs differ in length the extra pages stay unpaired).
OUT_DIR/TOUR/<hebrew name>.png is a copy of the English shot; OUT_DIR/pairs.json lists every pair
and every unpaired shot."""
import json
import os
import re
import shutil
import sys

PAT = re.compile(r'^(?P<seg>.+?)_(?P<n>\d\d)(?:_(?P<tag>[a-z][a-z_0-9]*))?$')


def parse(names):
    segs, order = {}, []
    for nm in names:
        m = PAT.match(nm)
        if not m:
            key = ('#', nm)
            segs.setdefault(key, []).append((0, None, nm))
            order.append(key)
            continue
        key = ('s', m.group('seg'))
        if key not in segs:
            order.append(key)
        segs.setdefault(key, []).append((int(m.group('n')), m.group('tag'), nm))
    for k in segs:
        segs[k].sort()
    return segs, order


def runs(seq):
    out, cur = [], []
    for n, tag, nm in seq:
        if tag:
            out.append(('plain', cur))
            out.append((tag, [nm]))
            cur = []
        else:
            cur.append(nm)
    out.append(('plain', cur))
    return out


def pair_seq(he, en):
    pairs, une, unh = [], [], []
    rh, re_ = runs(he), runs(en)
    # align the run lists by their kinds (tags), greedily
    i = j = 0
    while i < len(rh) and j < len(re_):
        kh, lh = rh[i]
        ke, le = re_[j]
        if kh == ke:
            k = min(len(lh), len(le))
            pairs += list(zip(lh[:k], le[:k]))
            unh += lh[k:]
            une += le[k:]
            i += 1
            j += 1
        else:
            # skip the side whose run kind does not appear next on the other side
            nxt_e = [r[0] for r in re_[j:]]
            if kh in nxt_e:
                une += le
                j += 1
            else:
                unh += lh
                i += 1
    for _, l in rh[i:]:
        unh += l
    for _, l in re_[j:]:
        une += l
    return pairs, unh, une


def main():
    en_dir, he_dir, out = sys.argv[1:4]
    report = {}
    for tour in sorted(os.listdir(he_dir)):
        hd, ed = os.path.join(he_dir, tour), os.path.join(en_dir, tour)
        if not os.path.isdir(hd) or not os.path.isdir(ed):
            continue
        hn = sorted(f[:-4] for f in os.listdir(hd) if f.endswith('.png') and not f.startswith('_'))
        en = sorted(f[:-4] for f in os.listdir(ed) if f.endswith('.png') and not f.startswith('_'))
        hs, horder = parse(hn)
        es, _ = parse(en)
        od = os.path.join(out, tour)
        os.makedirs(od, exist_ok=True)
        rep = dict(pairs=[], he_only=[], en_only=[], renamed=0)
        for key in horder:
            p, uh, ue = pair_seq(hs[key], es.get(key, []))
            for h, e in p:
                shutil.copyfile(os.path.join(ed, e + '.png'), os.path.join(od, h + '.png'))
                rep['pairs'].append([h, e])
                rep['renamed'] += h != e
            rep['he_only'] += uh
            rep['en_only'] += ue
        for key in es:
            if key not in hs:
                rep['en_only'] += [x[2] for x in es[key]]
        report[tour] = rep
        print('%-22s %4d pairs (%d renamed), %d Hebrew-only, %d English-only' % (
            tour, len(rep['pairs']), rep['renamed'], len(rep['he_only']), len(rep['en_only'])))
    json.dump(report, open(os.path.join(out, 'pairs.json'), 'w'), indent=1)


if __name__ == '__main__':
    main()
