from gfx import *
from PIL import Image
def compose_pal(f, tm, width, off=0, zoom=3, base=None):
    n = len(tm); h = (n + width - 1) // width
    im = base.copy() if base else Image.new('RGB', (width * 8, h * 8), (40, 0, 40))
    px = im.load(); pal = f.palette
    for i, en in enumerate(tm):
        t = (en & 0x3ff) - off
        if t < 0 or t >= (f.width // 8) * (f.height // 8): continue
        pb = (en >> 12) & 15
        tp = tile_px(f, t)
        X, Y = (i % width) * 8, (i // width) * 8
        for y in range(8):
            for x in range(8):
                sx = 7 - x if en & 0x400 else x; sy = 7 - y if en & 0x800 else y
                v = (tp[sy][sx] & 15) + pb * 16
                px[X + x, Y + y] = pal[v] if v < len(pal) else (255, 0, 255)
    return im
def screen(f, cancel=None):
    tm = list(read_bin('graphics/frontier_pass/bg.bin'))
    if cancel:
        c = read_bin('graphics/frontier_pass/%s.bin' % cancel)
        for j in range(2):
            for i in range(9):
                tm[j * 32 + 21 + i] = c[j * 9 + i]
    return compose_pal(f, tm, 32)
if __name__ == '__main__':
    e = load_head('graphics/frontier_pass/bg.png'); h = load('graphics/frontier_pass/bg.png')
    ims = [screen(e).resize((720, 480), 0), screen(h).resize((720, 480), 0), screen(h, 'cancel_highlighted').crop((150, 0, 240, 24)).resize((360, 96), 0)]
    side_by_side(ims, ['EN', 'HE', 'HE cancel highlighted']).save(OUT + '/frontier_pass__bg_screen_pair.png')
