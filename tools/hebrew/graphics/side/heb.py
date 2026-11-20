"""Hebrew pixel glyphs for the side-content graphics.

Sources (one pixel style everywhere):
  * tools/hebrew/fonts/hebrew_glyph_designs.txt: the strokes installed in graphics/fonts/latin_*.png
    (W6_7, W6_8, W5_7, W5_8, W4_7, W4_8, LV_*).
  * side_designs.txt (this folder): hand-made variants for labels whose letter height or weight
    differs from the fonts (5/6-row minis, 2-px-stem bold letters), drawn from the same shapes.

A glyph is a list of equal-length strings, '#' = ink. Every glyph of a set has the same rows; the
set records which row is the top of the letter body ('top') and the body height ('h').
Text is laid out right to left: the first character of the string ends up at the right.
"""
import os
HERE = os.path.dirname(os.path.abspath(__file__))
FONT_DESIGNS = os.path.join(os.path.dirname(os.path.dirname(HERE)), 'fonts', 'hebrew_glyph_designs.txt')
SIDE_DESIGNS = os.path.join(HERE, 'side_designs.txt')
FINALS = {'כ': 'ך', 'מ': 'ם', 'נ': 'ן', 'פ': 'ף', 'צ': 'ץ'}


def _parse(path):
    sets, meta, aliases = {}, {}, {}
    cur = glyph = None
    for line in open(path, encoding='utf-8'):
        line = line.rstrip('\n')
        if not line.strip() or (line.startswith('#') and (len(line) < 2 or line[1] not in '.#')):
            continue
        if line.startswith('@set '):
            parts = line.split()
            cur = sets.setdefault(parts[1], {})
            m = {}
            for p in parts[2:]:
                k, _, v = p.partition('=')
                m[k] = int(v)
            meta[parts[1]] = m
            glyph = None
            continue
        if line.startswith('@alias '):
            p = line.split(); aliases[p[1]] = p[2]; cur = None; continue
        if line.startswith('@glyph '):
            glyph = None if cur is None else cur.setdefault(line.split()[1], [])
            continue
        if line.startswith('@'):
            glyph = None; continue
        if glyph is not None:
            glyph.append(line.split()[0])
    return sets, meta


SETS, META = _parse(FONT_DESIGNS)
for name in SETS:  # font designs: rows 2..14, body starts at row 4 (index 2)
    META[name] = {'top': 2, 'h': 8 if name.endswith('_8') else 7}
if os.path.exists(SIDE_DESIGNS):
    s, m = _parse(SIDE_DESIGNS)
    SETS.update(s); META.update(m)


def trim(rows):
    w = max(len(r) for r in rows)
    rows = [r.ljust(w, '.') for r in rows]
    cols = [x for x in range(w) if any(r[x] == '#' for r in rows)]
    if not cols:
        return ['' for _ in rows]
    return [r[cols[0]:cols[-1] + 1] for r in rows]


def glyph(setname, ch):
    return trim(SETS[setname][ch])


def bold(rows):
    """Double every column that holds a vertical stroke (two ink pixels stacked)."""
    w = len(rows[0])
    out = [''] * len(rows)
    for x in range(w):
        col = [r[x] for r in rows]
        stem = any(col[y] == '#' and col[y + 1] == '#' for y in range(len(col) - 1))
        for i in range(len(rows)):
            out[i] += rows[i][x] * (2 if stem else 1)
    return out


def resize_body(rows, top, h, new_h, prefer=None):
    """Change the body height from h to new_h rows by repeating or dropping body rows.
    Rows are chosen from the middle out; `prefer` lists body-row indices to use first."""
    head, body, tail = rows[:top], list(rows[top:top + h]), rows[top + h:]
    order = list(prefer or [])
    mid = (h - 1) / 2.0
    order += [i for i in sorted(range(1, h - 1), key=lambda i: (abs(i - mid), i)) if i not in order]
    if new_h > h:
        reps = {}
        k = 0
        while sum(reps.values()) < new_h - h:
            i = order[k % len(order)]
            reps[i] = reps.get(i, 0) + 1
            k += 1
        nb = []
        for i, r in enumerate(body):
            nb += [r] * (1 + reps.get(i, 0))
        body = nb
    elif new_h < h:
        # drop rows that repeat their upper neighbour first
        drop = []
        cands = [i for i in order if body[i] == body[i - 1]] + [i for i in order if body[i] != body[i - 1]]
        for i in cands:
            if len(drop) == h - new_h:
                break
            drop.append(i)
        body = [r for i, r in enumerate(body) if i not in drop]
    return head + body + tail


def layout(text, setname, gap=1, space=3, glyph_fn=None):
    """Return (mask rows, list of (x0, x1) per char) for text laid out right to left.
    glyph_fn(ch) may supply glyphs (rows of the set's height)."""
    glyph_fn = glyph_fn or (lambda ch: glyph(setname, ch))
    nrows = len(next(iter(SETS[setname].values()))) if glyph_fn is None else None
    pieces = []
    for ch in text:  # logical order
        if ch == ' ':
            pieces.append(None)
        else:
            pieces.append(glyph_fn(ch))
    nrows = max(len(p) for p in pieces if p)
    # visual order: right to left -> reverse
    vis = list(reversed(pieces))
    out = [''] * nrows
    for i, p in enumerate(vis):
        if p is None:
            for y in range(nrows):
                out[y] += '.' * space
        else:
            for y in range(nrows):
                out[y] += p[y] if y < len(p) else '.' * len(p[0])
        if i < len(vis) - 1 and p is not None and vis[i + 1] is not None:
            for y in range(nrows):
                out[y] += '.' * gap
    return out


def show(rows):
    print('\n'.join(r.replace('.', '·') for r in rows))


def derive(base, new_h, do_bold=False, name=None):
    """Make a set from a font design set: body resized to new_h rows (rows repeated or dropped
    from the middle out), optionally emboldened (vertical stems doubled). Hand overrides in
    side_designs.txt under '@set <name>' replace single letters."""
    meta = META[base]
    out = {}
    for ch, g in SETS[base].items():
        r = trim(resize_body(g, meta['top'], meta['h'], new_h))
        if do_bold:
            r = bold(r)
        out[ch] = r
    if name:
        over = SETS.get(name + '_fix', {})
        for ch, g in over.items():
            out[ch] = trim(g)
        SETS[name] = out
        META[name] = {'top': meta['top'], 'h': new_h}
    return out


derive('W4_7', 5, name='M5')
derive('W4_7', 4, name='M4')
derive('W4_7', 6, True, name='B6')
derive('W4_7', 7, True, name='B7')
derive('W4_7', 8, True, name='B8')
derive('W4_7', 9, True, name='B9')
derive('W4_7', 11, True, name='B11')
derive('W4_7', 13, True, name='B13')


def body_glyph(setname, ch, asc=None, desc=None):
    """Glyph rows cut to the body plus at most `asc` rows above and `desc` rows below."""
    g = SETS[setname][ch]
    m = META[setname]
    a = m['top'] if asc is None else min(asc, m['top'])
    rows = g[m['top'] - a: m['top'] + m['h'] + (len(g) if desc is None else desc)]
    return trim(rows) if any('#' in r for r in rows) else rows


def word(t, setname, gap=1, space=3, asc=1, desc=2):
    """Lay out t right to left with every glyph cut to the same asc/body/desc rows."""
    return layout(t, setname, gap=gap, space=space,
                  glyph_fn=lambda ch: _pad(body_glyph(setname, ch, asc, desc), asc, META[setname]['h'], desc, setname, ch))


def _pad(rows, asc, h, desc, setname, ch):
    # body_glyph keeps exactly asc+h+desc rows (trim only touches columns)
    return rows
