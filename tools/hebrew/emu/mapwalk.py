#!/usr/bin/env python3
"""Crash test: warp into every live map from a save, fight through any battle that starts, read
through any text, and screenshot each map. Reports CRASH (PC out of range, from hnsrun), maps where
the game never gave control back, and the maps visited.

  mapwalk.py ROM SAVE OUTDIR [--only REGEX] [--max N]
"""
import argparse, glob, json, os, re, shutil, sys, time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import hns


def maps(tree):
    out = []
    for mj in sorted(glob.glob(os.path.join(tree, 'data/maps/*_hns/map.json'))):
        d = json.load(open(mj))
        w = d.get('warp_events') or []
        obj = [o for o in (d.get('object_events') or []) if 'x' in o]
        if w:
            out.append((d['id'], w[0]['x'], w[0]['y']))
        elif obj:
            out.append((d['id'], obj[0]['x'], obj[0]['y'] + 1))
    return out


def settle(emu, maxframes=60000):
    """Press through text and battles until the player can move. Returns (ok, note)."""
    battles = 0
    for _ in range(maxframes // 20):
        if emu.controllable():
            return True, 'battles %d' % battles if battles else ''
        cb2 = emu.cb2_name() or ''
        if 'Battle' in cb2:
            battles += 1 if battles == 0 else 0
            emu.tap('A', 8)          # fight with the first move; the post-game team wins quickly
        else:
            # B advances text and answers prompts with No; A would talk to the NPC in front
            # of the player again and reopen the dialogue forever.
            emu.tap('B', 8)
    return False, 'still held at %s' % emu.cb2_name()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('rom'); ap.add_argument('save'); ap.add_argument('outdir')
    ap.add_argument('--only'); ap.add_argument('--max', type=int, default=0)
    a = ap.parse_args()
    os.makedirs(a.outdir, exist_ok=True)
    tree = os.path.dirname(os.path.abspath(a.rom))
    todo = [m for m in maps(tree) if not a.only or re.search(a.only, m[0])]
    if a.max:
        todo = todo[:a.max]
    results = []
    emu = None

    def boot():
        cur = os.path.join(a.outdir, 'cur.sav')
        shutil.copy(a.save, cur)
        e = hns.Emu(a.rom, None, a.outdir, cur, None, False)
        e.run_script(os.path.join(HERE, 'scripts/continue.txt'))
        return e

    t0 = time.time()
    for i, (mid, x, y) in enumerate(todo):
        if emu is None:
            emu = boot()
        rec = {'map': mid}
        try:
            g, n = hns.map_lookup(emu.elf, mid)
            try:
                emu.warp(g, n, x, y)
            except hns.HnsError as e:
                if 'landed at' not in str(e) and 'not in the overworld' not in str(e):
                    raise
                rec['note'] = str(e)
            ok, note = settle(emu)
            loc = emu.location()[0]
            rec.update(status='OK' if ok else 'HELD', detail=note, at='%d.%d' % (loc[0], loc[1]))
            emu.shot('mapwalk_%03d_%s' % (i, mid.lower()))
            if not ok:
                emu.close(); emu = None
        except Exception as e:
            msg = str(e)
            rec.update(status='CRASH' if 'CRASH' in msg or 'crash' in msg.lower() else 'ERROR', detail=msg[:300])
            try:
                emu.close()
            except Exception:
                pass
            emu = None
        results.append(rec)
        if rec['status'] != 'OK':
            print('%-45s %s %s' % (mid, rec['status'], rec.get('detail', '')))
    if emu:
        emu.close()
    json.dump(results, open(os.path.join(a.outdir, 'mapwalk.json'), 'w'), indent=1)
    counts = {}
    for r in results:
        counts[r['status']] = counts.get(r['status'], 0) + 1
    print('%d maps in %.0f s: %s' % (len(results), time.time() - t0, counts))


if __name__ == '__main__':
    main()
