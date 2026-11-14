from kit import *
import importlib.util
from check import check
P = 'graphics/interface/status_icons.png'
# Frame 5 (rows 40..47) is the Pokérus tag the summary screen shows. Its pill is wider than the
# other tags: tag colour 4 on x 5..26 (rows 42..45) and x 6..25 (rows 41 and 46), corners 5.
# English "PkRS": ink 2, x 8..24, rows 41..47.
# Hebrew: פוקרוס in the T6 tag letters of the other Hebrew tags (coreui_mini_designs.txt), ink 2,
# 20 px on x 6..25 so every pixel stays on the tag colour; the qof stops on the last letter row,
# above the pill's bottom row, as in the other tags, and the two letter corners that would touch
# the pill's corner pixels are rounded off.
# The other frames were fixed after make_coreui.py drew them (gpaths.LATER_EDITS), so this script
# starts from the committed file, redraws frame 5 from the English frame and writes the committed
# file itself.
_spec = importlib.util.spec_from_file_location(
    'coreui_heb', os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'coreui', 'heb.py'))
cheb = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(cheb)

TEXT, TAG, Y0, X = 2, 4, 40, 6
e = load_head(P)
f = load(P)
before = [[f.get(x, y) for x in range(f.width)] for y in range(f.height)]
for y in range(Y0, Y0 + 8):
    for x in range(f.width):
        f.put(x, y, e.get(x, y))
draw.replace(f, 0, Y0, f.width - 1, Y0 + 7, {TEXT: TAG})
m = cheb.layout('פוקרוס', 'T6', gap=1)
m[7] = '.' * len(m[7])
for j, r in enumerate(m):
    for i, c in enumerate(r):
        if c == '#':
            assert e.get(X + i, Y0 + j) in (TAG, TEXT), ('off the tag', X + i, Y0 + j)
            f.put(X + i, Y0 + j, TEXT)
# On the pill's corner rows (41 and 46) the word would touch the corner pixels: the samekh's
# top-left and the pe's bottom-right corners are rounded off, so the tag keeps a margin there too.
for x, y in ((X, Y0 + 1), (X + width(m) - 1, Y0 + 6)):
    assert f.get(x, y) == TEXT and e.get(x - 1 if x == X else x + 1, y) == 5
    f.put(x, y, TAG)
print('PKRS פוקרוס', width(m), 'x', X, X + width(m) - 1)
dst = os.path.join(gpaths.TREE, P)
f.save(dst)

g = load(P)
ok, a, b, ac, bc = check(P)
used = lambda im: {im.get(x, y) for y in range(im.height) for x in range(im.width)}
other = [(x, y) for y in range(g.height) for x in range(g.width)
         if not Y0 <= y < Y0 + 8 and g.get(x, y) != before[y][x]]
assert ok and g.palette == e.palette and used(g) <= used(e) and not other, (ok, a, b, ac, bc, other[:5])
print('pixel rules OK: size, depth, palette and chunks as English; indices', sorted(used(g)),
      '; frames other than 5 unchanged')
print(pair(P, 8))
