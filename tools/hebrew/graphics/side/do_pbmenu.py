from kit import *
P = 'graphics/pokeblock/menu.png'
f = load_head(P)
heb.derive('W4_8', 9, False, name='N9')
# FEEL: 9-row letters with 1-px strokes, ink 9, shadow 11 right/below/diagonal, on 3; the label's
# tiles are x 16..39, y 24..39 (one tilemap reference each). Kept left-aligned as the English.
draw.replace(f, 16, 26, 39, 38, {9: 3, 11: 3})
m = fit('תחושה', 'N9', 24, asc=0, desc=0)
draw.paint(f, m, 16, 28, 9, shadow=11, clip=(16, 24, 39, 39))
print('FEEL', width(m) + 1)
print(save_and_pair(f, P, 6))
