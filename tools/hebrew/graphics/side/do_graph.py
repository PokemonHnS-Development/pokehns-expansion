from gfx import *
# The Pokéblock feeding screen shows the same condition panel, at the same screen place
# (tiles 12..27 x 0..17), as the PokéNav condition screen. Copy the Pokégear group's Hebrew panel
# (graphics/pokenav/condition/graph.png, its own tilemap) cell by cell into this tileset, so the
# two screens show identical labels.
P = 'graphics/pokeblock/use_screen/graph.png'
A = 'graphics/pokenav/condition/graph.png'
tmA = read_bin('graphics/pokenav/condition/graph.bin')
tmB = read_bin('graphics/pokeblock/use_screen/graph.bin')
aE, aH, bE = load_head(A), load(A), load_head(P)
f = load_head(P)

def cell(img, e, off):
    t = (e & 0x3FF) - off
    tp = tile_px(img, t)
    if e & 0x400: tp = [r[::-1] for r in tp]
    if e & 0x800: tp = tp[::-1]
    return tp

def put_tile(img, t, px):
    tw = img.width // 8
    tx, ty = (t % tw) * 8, (t // tw) * 8
    for y in range(8):
        for x in range(8):
            img.put(tx + x, ty + y, px[y][x])

written, conflicts, skipped = {}, [], []
for cy in range(0, 18):
    for cx in range(12, 28):
        ea, eb = tmA[cy * 32 + cx], tmB[cy * 32 + cx]
        if cell(aE, ea, 0) != cell(bE, eb, 640):
            skipped.append((cx, cy)); continue
        want = cell(aH, ea, 0)
        if eb & 0x800: want = want[::-1]
        if eb & 0x400: want = [r[::-1] for r in want]
        t = (eb & 0x3FF) - 640
        if t in written and written[t] != want:
            conflicts.append((cx, cy, t)); continue
        written[t] = want
for t, px in written.items():
    put_tile(f, t, px)
print('cells skipped (English differs):', skipped)
print('conflicts:', conflicts)
f.save(gpaths.write_target(P))
# verify: the composed panel equals the Pokégear Hebrew panel
bad = [(cx, cy) for cy in range(18) for cx in range(12, 28)
       if cell(f, tmB[cy * 32 + cx], 640) != cell(aH, tmA[cy * 32 + cx], 0) and (cx, cy) not in skipped]
print('mismatching cells:', bad)
side_by_side([compose(bE, tmB, 32, 640, 3), compose(f, tmB, 32, 640, 3)], ['EN', 'HE']).save(OUT + '/pokeblock__use_screen__graph_screen_pair.png')
print(pair(P, 4))
