from kit import *
P = 'graphics/slot_machine/digital_display.png'
f = load_head(P)
# Dot-matrix sprites: every lit dot is a 2x2 block of index 1 on the grey 0, on a 3-px grid
# (x = 1 + 3i, i = 0..20; rows on a per-sprite origin). Hebrew letters are drawn one dot per
# glyph pixel. Sources: the font strokes (M5 = W4_7 at 5 rows, W5_8, N9 = W4_8 at 9 rows,
# D6 = W5_8 at 6 rows) plus three 5-row letters drawn for the TIME line.
heb.derive('W5_8', 6, False, name='D6')
heb.derive('W5_8', 7, False, name='D7')
FIVE = {  # 5-row letters for "גלגל" (lamed's ascender inside the 5 rows)
    'ג': ['.##.', '...#', '..##', '.#.#', '#..#'],
    'ל': ['#...', '###.', '...#', '..#.', '.#..'],
}

def dot(x, y, v=1):
    assert 0 <= x <= 62 and 0 <= y, (x, y)
    for dy in (0, 1):
        for dx in (0, 1):
            f.put(x + dx, y + dy, v)

def clear(y0, y1, x0=0, x1=63):
    draw.fill(f, x0, y0, x1, y1, 0)

def put_mask(m, col0, gy0, v=1):
    for j, r in enumerate(m):
        for i, c in enumerate(r):
            if c == '#':
                dot(1 + 3 * (col0 + i), gy0 + 3 * j, v)

def center_col(m, c0, c1):
    """Leftmost grid column so the mask is centred on grid columns c0..c1."""
    return c0 + (c1 - c0 + 1 - len(m[0])) // 2

def word(t, setname, asc, desc, gap=1, glyphs=None, sb=False):
    """Right-to-left dot word; sb doubles each letter's main (right-most) stem, as the English
    STOP / WIN / LOSE / BIG / REG letters have 2-dot stems."""
    if glyphs or sb:
        src = glyphs or {c: glyph_rows(setname, c, asc, desc) for c in t}
        pieces = [semibold.semibold(src[c]) if sb else src[c] for c in reversed(t)]
        rows = [''] * len(pieces[0])
        for k, p in enumerate(pieces):
            rows = [rows[y] + p[y] + ('.' * gap if k < len(pieces) - 1 else '') for y in range(len(rows))]
        return rows
    return lay(t, setname, gap, asc=asc, desc=desc)

# Whole-word sprites (64 px wide, the PNG strip is the screen layout).
# TIME (y 48..63, rows 49 + 3j, 5 rows): REEL and TIME stack (REEL on top), so the pair reads
# "זמן / גלגל" = REEL TIME.
clear(48, 63)
m = word('גלגל', None, 0, 0, glyphs=FIVE)
put_mask(m, center_col(m, 0, 20), 49)
# INSERT (y 64..79, rows 65 + 3j): "הכנס"
clear(64, 79)
m = word('הכנס', 'M5', 0, 0)
put_mask(m, center_col(m, 0, 20), 65)
# WIN (y 96..119, rows 96 + 3j, 8 rows): "זכית"
clear(96, 119)
m = word('זכית', 'W4_8', 0, 0, sb=True)
put_mask(m, center_col(m, 0, 20), 96)
# LOSE (y 128..159, rows 131 + 3j, 9 rows): "הפסד"
clear(128, 159)
m = word('הפסד', 'N9', 0, 0)            # 2-dot stems would need 23 of the 21 columns
put_mask(m, center_col(m, 0, 20), 131)

# Letter sprites: each English letter is its own sprite, placed left to right, so the Hebrew
# letters go in visual order (the word's last letter in the leftmost slot).
def slots(y0, y1, gy0, spec, setname, asc, desc, sb=False):
    """spec: list of (x0, x1, letter) per slot; the letter is centred on the slot's grid columns."""
    clear(y0, y1)
    for x0, x1, ch in spec:
        cols = [i for i in range(21) if 1 + 3 * i >= x0 and 1 + 3 * i + 1 <= x1]
        g = word(ch, setname, asc, desc, sb=sb)
        if len(g[0]) > len(cols):
            g = word(ch, setname, asc, desc)
        put_mask(g, center_col(g, cols[0], cols[-1]), gy0)
# STOP: four 16-px slots S T O P -> "עצור" (visual ר ו צ ע)
slots(80, 95, 81, [(0, 15, 'ר'), (16, 31, 'ו'), (32, 47, 'צ'), (48, 63, 'ע')], 'M5', 0, 0, sb=True)
# BONUS: slots B 16, O 8, N 16, U 8, S 16 px -> "בונוס" (visual ס ו נ ו ב; the vavs take the 8-px slots)
slots(160, 175, 161, [(0, 15, 'ס'), (16, 23, 'ו'), (24, 39, 'נ'), (40, 47, 'ו'), (48, 63, 'ב')], 'M5', 0, 0)
# BIG: slots B 24, I 16, G 24 px -> "ענק"; REG: R 24, E 16, G 24 -> "קטן". 6-row body + 2-row
# descender on the 8 dot rows 176 + 3j (the English used rows 179..197).
slots(176, 199, 176, [(0, 23, 'ק'), (24, 39, 'נ'), (40, 63, 'ע')], 'D6', 0, 2, sb=True)
slots(200, 223, 200, [(0, 23, 'ן'), (24, 39, 'ט'), (40, 63, 'ק')], 'D6', 0, 2, sb=True)

# REEL (y 0..47): a crown of dots over a lit block (rows 16..46, columns 1..19) with the word
# cut out as unlit dots on rows 22..40. Hebrew "זמן" cut out of the same block; final nun's
# descender runs into the block's lit bottom rows.
for j in range(7):
    for i in range(2, 19):
        dot(1 + 3 * i, 22 + 3 * j, 1)
m = word('זמן', 'D7', 0, 2)
put_mask(m, center_col(m, 2, 18), 22, 0)
f.save(gpaths.write_target(P))

# previews: each sprite at its screen arrangement
ims, labs = [], []
for name, y0, h in [('REEL', 0, 48), ('TIME', 48, 16), ('INSERT', 64, 16), ('STOP', 80, 16), ('WIN', 96, 24),
                    ('LOSE', 128, 32), ('BONUS', 160, 16), ('BIG', 176, 24), ('REG', 200, 24)]:
    e = load_head(P)
    ims.append(side_by_side([render(e, 4, region=(0, y0, 64, h)), render(f, 4, region=(0, y0, 64, h))], [name, '']))
from PIL import Image
W = max(i.width for i in ims); H = sum(i.height for i in ims)
o = Image.new('RGB', (W, H), (255, 255, 255)); y = 0
for i in ims:
    o.paste(i, (0, y)); y += i.height
o.save(OUT + '/slot_machine__digital_display_words_pair.png')
print(pair(P, 3))
