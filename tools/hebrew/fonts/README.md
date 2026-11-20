# Hebrew glyphs in the nine Latin fonts

The Hebrew letters live in the nine expansion Latin fonts (`graphics/fonts/latin_*.png`), with
their widths in `src/fonts.c`. They are not drawn by hand in the PNGs: the designs file holds the
strokes, and the installer computes everything else and writes the PNGs and width tables.

| File | What |
| --- | --- |
| `hebrew_glyph_designs.txt` | the source of truth: the foreground pixels of every Hebrew glyph, one set per letter shape (its header says which set is which) |
| `install_hebrew_glyphs.py TREE` | writes the 27 letters, ◀ and the level glyph רמה into the nine PNGs and width tables of TREE. `--check` compares TREE with the designs and exits 1 on a difference; `--sheet OUT.png` and `--mock OUT.png --text '...'` draw previews (Pillow) |
| `inspect_fonts.py` | library and CLI that read and write glyph cells in a GBA font PNG and keep its bit depth, palette and ancillary chunks (`info`, `dump`, `metrics`, `sheet`, `extract`, `verify-latfont`, `widths`) |
| `make_naming_tabs.py TREE` | draws the naming screen's page tabs `graphics/naming_screen/page_swap_hebrew.png` (עברית) and `page_swap_latin.png` (ABC), Pillow |
| `derive_hebrew_drafts.py` | derives draft glyphs from the FireRed Hebrew fork (`--frlg`, default `../pokefirered-heb`) into `$HNS_WORK/font_drafts`. These drafts were the starting point of the designs; `tools/hebrew/data/font_drafts/` keeps their width files for `textwidth.py --hebrew-widths draft` |

Installing, `--check` and the text commands of `inspect_fonts.py` need only the standard library
(they run on Python 3.9). Anything that draws a picture needs Pillow: the installer's previews,
`inspect_fonts.py sheet` and `extract`, `make_naming_tabs.py` and `derive_hebrew_drafts.py`.

## How a glyph is built

- The designs file stores foreground pixels only (`#` = palette index 1), rows 2 to 14 of the
  16x16 cell, with the ink starting at column 0.
- The installer adds the shadow (index 2) to the right of, below and below-right of every
  foreground pixel, as the Latin glyphs have it.
- The width is the last foreground column + 2: the last column holds only shadow, so the mirrored
  blit leaves letters 1 px apart. `WIDTH_OVERRIDES` in the installer lists the exceptions set by
  hand (normal ן is 4, not 3, because at 3 it touches the next letter).
- The white box (index 3, drawn as background) fills the advance on the rows the font's own Latin
  glyphs paint.
- Cells (`charmap.txt`, `include/constants/characters.h`): 0x3A-0x4F א..ת, 0x50 ך, 0x5E ם,
  0x5F ן, 0x60 ף, 0x61 ץ, 0x87 ◀ (▶ mirrored inside ▶'s advance, so its shadow falls right),
  0x34 and 0x105 רמה (the level glyph, same pixels and width in both cells).

| Font | Letter set | Level set |
| --- | --- | --- |
| normal | W6_8 | LV_B11 |
| short | W6_7 | LV_B10 |
| narrow | W5_8 | LVC_B11 |
| narrower | W4_8 | LVC_B11 |
| short_narrow | W5_7S | LVC_B10 |
| short_narrower | W4_7S | LVC_B10 |
| small | W5_7 | LVC_B10 |
| small_narrow | W5_7SN | LVC_B10 |
| small_narrower | W4_7 | LVC_B10 |

W6 is FireRed's normal Hebrew and W5 its small Hebrew, with the ink moved to column 0; `_8` adds
one body row (rows 4-11, baseline 11); the W4 sets were drawn by hand. The `S` sets give ל its
ascender on rows 2-3 so it keeps its height when a string falls back to a narrower font, and
`W5_7SN` shortens the finals to small_narrow's 12-row blit. Normal and short use the 13 px
FireRed רמה; the other seven use a compact 12 px form.

Decisions behind these choices:

- **Normal is stretched, not shifted.** FireRed's 7-row letters shifted down looked like small
  text next to the 9-row digits and capitals; with one body row added, Hebrew stands one row below
  the capitals, FireRed's own ratio.
- **ן and ף end on the same row as the other finals** in normal and short, so the game's blit keeps
  their bottom shadow.

## Changing a glyph

1. Edit the glyph's block in `hebrew_glyph_designs.txt` (or `WIDTH_OVERRIDES` for a width).
2. `python3 tools/hebrew/fonts/install_hebrew_glyphs.py .` from the repository root writes the
   nine PNGs and `src/fonts.c`.
3. `python3 tools/hebrew/fonts/install_hebrew_glyphs.py . --check` must print
   `OK: tree matches the designs`.
4. Re-measure the strings in the changed font (`tools/hebrew/audit.py`) and look at the screens
   that use it: a width change moves every line that holds the letter.

Re-running the installer on an unchanged tree rewrites the nine PNGs and `src/fonts.c`
byte-identically, and `make_naming_tabs.py` does the same for the two tabs.
