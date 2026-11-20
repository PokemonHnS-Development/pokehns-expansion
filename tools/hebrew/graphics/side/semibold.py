"""Semi-bold sets: double only the right-most vertical stem of each letter (the main Hebrew stroke)."""
import heb

def stem_cols(rows):
    w = len(rows[0])
    out = []
    for x in range(w):
        col = [r[x] for r in rows]
        if any(col[y] == '#' and col[y + 1] == '#' for y in range(len(col) - 1)):
            out.append(x)
    return out

def semibold(rows, which='right'):
    cols = stem_cols(rows)
    if not cols:
        return rows
    if which == 'right':
        dbl = {cols[-1]}
    elif which == 'all':
        dbl = set(cols)
    else:
        dbl = set(which)
    out = [''] * len(rows)
    for x in range(len(rows[0])):
        for i in range(len(rows)):
            out[i] += rows[i][x] * (2 if x in dbl else 1)
    return out

def derive_sb(base, new_h, name, overrides=None):
    meta = heb.META[base]
    out = {}
    for ch, g in heb.SETS[base].items():
        r = heb.trim(heb.resize_body(g, meta['top'], meta['h'], new_h))
        out[ch] = semibold(r)
    for ch, g in (overrides or {}).items():
        out[ch] = g
    heb.SETS[name] = out
    heb.META[name] = {'top': meta['top'], 'h': new_h}
    return out

for h in (5, 6, 7, 8, 9, 10, 11, 12, 13):
    derive_sb('W4_8', h, 'S%d' % h)
