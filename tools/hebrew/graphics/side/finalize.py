"""Verify every edited file of the side group and write the 4x English | Hebrew pairs + contact sheet."""
import subprocess
from gfx import *
from check import check
from PIL import Image, ImageDraw
FILES = [
    'graphics/contest/applause.png', 'graphics/contest/nextturn.png', 'graphics/contest/interface.png',
    'graphics/contest/results_screen/tiles.png',
    'graphics/pokeblock/menu.png', 'graphics/pokeblock/use_screen/graph.png',
    'graphics/pokeblock/use_screen/updown.png', 'graphics/pokeblock/use_screen/condition.png',
    'graphics/roulette/credit.png',
    'graphics/slot_machine/menu.png', 'graphics/slot_machine/digital_display.png',
    'graphics/trainer_card/tiles.png', 'graphics/trainer_card/frlg/tiles.png',
    'graphics/frontier_pass/bg.png', 'graphics/frontier_pass/map_and_card.png', 'graphics/frontier_pass/map_screen.png',
    'graphics/battle_frontier/tourney_buttons.png',
    'graphics/easy_chat/button_window.png', 'graphics/easy_chat/mode.png',
    'graphics/union_room_chat/background.png', 'graphics/union_room_chat/r_button_labels.png',
]
bad = 0
pairs = []
for p in FILES:
    ok, a, b, ac, bc = check(p)
    e, h = load_head(p), load(p)
    ie = {e.get(x, y) for y in range(e.height) for x in range(e.width)}
    ih = {h.get(x, y) for y in range(h.height) for x in range(h.width)}
    changed = sum(e.get(x, y) != h.get(x, y) for y in range(e.height) for x in range(e.width))
    new = sorted(ih - ie)
    pal_same = e.palette == h.palette
    status = 'OK' if ok and pal_same and not new and changed else 'CHECK'
    bad += status != 'OK'
    print('%-50s %s size=%dx%d depth=%d palette_same=%s new_indices=%s changed_px=%d' % (p, status, b[0], b[1], b[2], pal_same, new, changed))
    pairs.append((p, pair(p, 4)))
# contact sheet: every pair scaled to fit 640 px wide, two columns
thumbs = []
for p, path in pairs:
    im = Image.open(path)
    s = min(1.0, 640 / im.width, 520 / im.height)
    im = im.resize((int(im.width * s), int(im.height * s)), Image.NEAREST)
    lab = Image.new('RGB', (im.width, im.height + 14), (255, 255, 255))
    lab.paste(im, (0, 14)); ImageDraw.Draw(lab).text((2, 1), p.replace('graphics/', ''), fill=(0, 0, 160))
    thumbs.append(lab)
cols = 2; colw = 650
rows = [thumbs[i:i + cols] for i in range(0, len(thumbs), cols)]
H = sum(max(t.height for t in r) + 8 for r in rows)
sheet = Image.new('RGB', (colw * cols, H), (255, 255, 255)); y = 0
for r in rows:
    for i, t in enumerate(r):
        sheet.paste(t, (i * colw, y))
    y += max(t.height for t in r) + 8
sheet.save(OUT + '/contact_sheet.png')
print('contact sheet', sheet.size, 'bad', bad)
