"""Screen composites (English | Hebrew) for files whose tiles are laid out by a tilemap."""
from gfx import *
from fpview import compose_pal, screen
from PIL import Image

def stack(ims, path):
    W = max(i.width for i in ims); H = sum(i.height for i in ims)
    o = Image.new('RGB', (W, H), (255, 255, 255)); y = 0
    for i in ims:
        o.paste(i, (0, y)); y += i.height
    o.save(path)

def tc():
    tm = read_bin('graphics/trainer_card/front.bin')
    e, h = load_head('graphics/trainer_card/tiles.png'), load('graphics/trainer_card/tiles.png')
    side_by_side([compose(e, tm, 30, 0, 3), compose(h, tm, 30, 0, 3)], ['EN', 'HE']).save(OUT + '/trainer_card__front_screen_pair.png')
    e, h = load_head('graphics/trainer_card/frlg/tiles.png'), load('graphics/trainer_card/frlg/tiles.png')
    ims = []
    for n in ['front', 'back']:
        tm = read_bin('graphics/trainer_card/frlg/%s.bin' % n)
        ims.append(side_by_side([compose(e, tm, 30, 0, 3), compose(h, tm, 30, 0, 3)], ['EN ' + n, 'HE ' + n]))
    stack(ims, OUT + '/trainer_card__frlg__screen_pair.png')

def fp():
    e = load_head('graphics/frontier_pass/bg.png'); h = load('graphics/frontier_pass/bg.png')
    ims = [screen(e).resize((720, 480), 0), screen(h).resize((720, 480), 0),
           screen(h, 'cancel_highlighted').crop((150, 0, 240, 24)).resize((360, 96), 0)]
    side_by_side(ims, ['EN', 'HE', 'HE cancel highlighted']).save(OUT + '/frontier_pass__bg_screen_pair.png')

if __name__ == '__main__':
    tc(); fp()
