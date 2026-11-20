"""Paint Hebrew masks into indexed images (FontPng from inspect_fonts)."""
import heb

FONT_SHADOW = [(1, 0), (0, 1), (1, 1)]


def size(mask):
    return len(mask[0]), len(mask)


def ink_cells(mask, x, y):
    return {(x + i, y + j) for j, r in enumerate(mask) for i, c in enumerate(r) if c == '#'}


def paint(f, mask, x, y, ink, shadow=None, shadow_offsets=FONT_SHADOW, outline=None,
          outline_diag=None, clip=None, only_on=None):
    """ink: palette index, or callable(px, py, row_in_mask) -> index.
    shadow: index (or callable) put at shadow_offsets of ink pixels that are not ink.
    outline: index for 4-neighbours of ink; outline_diag for pixels touching ink only diagonally.
    clip: (x0, y0, x1, y1) inclusive bounds; only_on: set of indices that may be overwritten by
    shadow/outline (None = anything)."""
    cells = ink_cells(mask, x, y)

    def ok(px, py):
        if clip and not (clip[0] <= px <= clip[2] and clip[1] <= py <= clip[3]):
            return False
        return 0 <= px < f.width and 0 <= py < f.height

    def put(px, py, v):
        if ok(px, py):
            f.put(px, py, v(px, py) if callable(v) else v)

    if outline is not None or outline_diag is not None:
        for (cx, cy) in cells:
            for dx in (-1, 0, 1):
                for dy in (-1, 0, 1):
                    p = (cx + dx, cy + dy)
                    if p in cells or not ok(*p):
                        continue
                    orth = any((p[0] + ax, p[1] + ay) in cells for ax, ay in ((1, 0), (-1, 0), (0, 1), (0, -1)))
                    if orth and outline is not None:
                        put(p[0], p[1], outline)
                    elif not orth and outline_diag is not None:
                        put(p[0], p[1], outline_diag)
    if shadow is not None:
        for (cx, cy) in cells:
            for dx, dy in shadow_offsets:
                p = (cx + dx, cy + dy)
                if p in cells or not ok(*p):
                    continue
                if only_on is not None and f.get(*p) not in only_on:
                    continue
                put(p[0], p[1], shadow)
    for (cx, cy) in cells:
        if ok(cx, cy):
            if callable(ink):
                f.put(cx, cy, ink(cx, cy, cy - y))
            else:
                f.put(cx, cy, ink)
    return cells


def fill(f, x0, y0, x1, y1, v):
    """Fill inclusive rect with index v, or callable(x, y) -> index."""
    for yy in range(y0, y1 + 1):
        for xx in range(x0, x1 + 1):
            f.put(xx, yy, v(xx, yy) if callable(v) else v)


def replace(f, x0, y0, x1, y1, mapping):
    """Inside the inclusive rect, replace indices by mapping {old: new}."""
    for yy in range(y0, y1 + 1):
        for xx in range(x0, x1 + 1):
            v = f.get(xx, yy)
            if v in mapping:
                f.put(xx, yy, mapping[v])


def text(t, setname=None, gap=1, space=3, glyph_fn=None):
    return heb.layout(t, setname, gap=gap, space=space, glyph_fn=glyph_fn)


def place_center(mask, x0, x1):
    """Left x so the mask is centered in [x0, x1] (inclusive)."""
    w = len(mask[0])
    return x0 + (x1 - x0 + 1 - w) // 2


def place_right(mask, xr):
    return xr - len(mask[0]) + 1


def crop_rows(mask):
    """Return (first_row, last_row) that hold ink."""
    ys = [i for i, r in enumerate(mask) if '#' in r]
    return ys[0], ys[-1]


def inpaint(f, x0, y0, x1, y1, remove, prefer_vertical=True):
    """Inside the inclusive rect, treat pixels whose index is in `remove` as unknown and fill each
    with the index of the nearest known pixel (multi-source BFS, vertical steps first)."""
    from collections import deque
    unknown = {(x, y) for y in range(y0, y1 + 1) for x in range(x0, x1 + 1) if f.get(x, y) in remove}
    q = deque()
    for (x, y) in unknown:
        pass
    known_val = {}
    steps = [(0, 1), (0, -1), (1, 0), (-1, 0)] if prefer_vertical else [(1, 0), (-1, 0), (0, 1), (0, -1)]
    # seed: known pixels adjacent to unknown ones
    for (x, y) in unknown:
        for dx, dy in steps:
            p = (x + dx, y + dy)
            if p not in unknown and 0 <= p[0] < f.width and 0 <= p[1] < f.height:
                q.append((p, f.get(*p)))
    seen = set()
    while q:
        (p, v) = q.popleft()
        for dx, dy in steps:
            n = (p[0] + dx, p[1] + dy)
            if n in unknown and n not in seen:
                seen.add(n)
                known_val[n] = v
                q.append((n, v))
    for (x, y), v in known_val.items():
        f.put(x, y, v)
    return len(unknown)


def bbox_of(f, x0, y0, x1, y1, vals):
    xs, ys = [], []
    for y in range(y0, y1 + 1):
        for x in range(x0, x1 + 1):
            if f.get(x, y) in vals:
                xs.append(x); ys.append(y)
    return min(xs), min(ys), max(xs), max(ys)
