# Hebrew translation tools

Python 3 tools for translating Heart & Soul into Hebrew and checking the result. They use only the
standard library, except `fontcells.py` (Pillow). The tools that read an ELF (`rom_sweep.py`, the
harness in `emu/`) need devkitARM (`DEVKITARM`, default `/opt/devkitpro/devkitARM`). Every tool
runs from any working directory. The style guide and glossary are in `translation/hebrew/`.

## Locations

`paths.py` resolves every location. You can override each one with an environment variable.
`python3 tools/hebrew/paths.py` prints the values in use.

| Variable | What | Default |
| --- | --- | --- |
| `HNS_TREE` | Hebrew source tree | this repository |
| `HNS_BASELINE` | engine baseline: the Hebrew engine with English strings (drift and chunk source) | `../pokehns-heb-engine`, if it exists |
| `HNS_UPSTREAM` | upstream English tree | `../pokehns-en`, if it exists |
| `HNS_FONTS_TREE` | tree whose `src/fonts.c` and `charmap.txt` set the glyph widths | `HNS_TREE` |
| `HNS_DATA` | data the tools read | `tools/hebrew/data` |
| `HNS_GLOSSARY` | glossary (`glossary_sources.csv` sits next to it) | `translation/hebrew/glossary.csv` |
| `HNS_WORK` | scratch and output folder | `build/hebrew` |
| `HNS_UNITS` | translation unit chunks | `$HNS_WORK/units` |
| `HNS_ROM`, `HNS_EN_ROM` | Hebrew and English ROMs (each `.elf` sits next to its ROM) | `$HNS_TREE/pokehns.gba`, `$HNS_UPSTREAM/pokehns.gba` |
| `HNS_SAVES` | save-ladder folder (`ladder1_newgame.sav` ... `ladder6_postgame.sav`) | none: the saves are not in the repository |
| `HNS_RUNNER` | the `hnsrun` binary | `tools/hebrew/emu/hnsrun` |

## Workflow

1. **Extract.** `units.py extract FILE...` prints the player-visible strings of the given files
   as JSON units. `units.py status FILE...` counts how many of them are already in Hebrew.
2. **Chunk.** `make_chunks.py B10 [B20 ...|all] [--out DIR]` cuts each named inventory batch
   (`data/inventory.json`) into chunk files in `$HNS_UNITS/<batch>/` (or `DIR/<batch>/`). It extracts the units from
   `HNS_BASELINE` and fills in names from the glossary.
3. **Translate.** Fill each unit's `"he"` by following `translation/hebrew/STYLE.md` and the
   glossary. `merge_he.py CHUNK.json TRANSLATIONS.json` merges an `{id: hebrew}` file into a chunk.
4. **Check.** `checkunits.py CHUNK.json...` checks tokens, terminators, escapes, the charset,
   digits, leftover Latin, width and lines. `wrap.py TEXT` re-wraps a string to its budget.
   `textwidth.py TEXT` measures a string.
5. **Apply.** `units.py apply CHUNK.json... [--dry-run]` writes the Hebrew into `HNS_TREE`.
   It refuses a string that changed since the chunk was made, and a string that already holds
   different Hebrew (an old chunk would undo a later fix) unless `--overwrite-hebrew` is given.
   `apply_names.py` writes trainer and map-section names. Run `gen_dex_alpha.py` after the species
   names change, and `gen_ec_order.py` and `gen_ec_letters.py` after an Easy Chat word, species or
   move name changes.
6. **Drift.** `drift.py FILE...` checks that a translated file differs from `HNS_BASELINE` only
   inside its strings.
7. **Audit.** `audit.py [PATH...] [--baseline "$HNS_UPSTREAM"]` runs a static layout audit of
   every string. For the glossary, `namecheck.py --all` checks bytes, the charset, final letters
   and duplicates, and `glossary_widths.py` reports names wider than their budget.
   `plurals.py` checks that every item a player can hold more than one of has a Hebrew plural
   (an `item_plural` row, and its `pluralName` in `src/data/items.h` when it differs).
8. **Build.** `make hns`, or `make hns RTL_CLIP_REPORT=1` for the clip-report build
   (`pokehns-clip.gba`).
9. **Harness.** `rom_sweep.py` lists English text left in the built ROM. The screen tours, the
   label sweep and the map walk run in the headless emulator (`emu/README.md`). `cliptour.py`
   decodes the clip log, and `pairsheets.py` makes side-by-side screenshot sheets.

## Tools

| Tool | What it does |
| --- | --- |
| `apply_names.py` | writes glossary names into the `.party` files and `region_map_sections.json` |
| `audit.py` | static width/lines/buffer/bytes/charset audit of every player-visible string |
| `checkunits.py` | validates translated chunks before they are applied |
| `cliptour.py` | reads the RTL clip log of a clip build between harness steps (`hns.py tour --clip`) |
| `drift.py` | checks that a translated file changed only inside its strings |
| `fontcells.py` | shows, per Latin font, whether each glyph cell is blank and how wide it is (`fontcells.py TREE [HEX...]`) |
| `gen_dex_alpha.py` | regenerates the Hebrew alphabetical Pokédex order from the glossary; `--check` exits 1 when the header is stale (CI) |
| `gen_ec_order.py` | regenerates the Hebrew order of the Easy Chat group lists (`src/data/easy_chat/easy_chat_order_rtl.h`) from the word texts; `--check` exits 1 when it is stale (CI, and `tests/test_easy_chat.py`) |
| `gen_ec_letters.py` | regenerates the Easy Chat ABC keyboard's lists by Hebrew letter (`src/data/easy_chat/easy_chat_words_by_letter_rtl.h`) from the word, species and move texts; `--check` exits 1 when it is stale (CI). The header holds only word constants and is picked onto `he/renderer` with the engine |
| `glossary_widths.py` | glossary names wider than their screen budget and than the English name |
| `make_chunks.py` | cuts inventory batches into translation chunks |
| `merge_he.py` | merges `{id: hebrew}` translations into a chunk |
| `namecheck.py` | validates glossary rows: bytes, charset, final letters, duplicates |
| `pairsheets.py` | side-by-side review sheets of two screenshot runs |
| `paths.py` | the locations above |
| `plurals.py` | every stackable item has a Hebrew plural row that `src/data/items.h` prints (DECISIONS.md Q125) |
| `rom_sweep.py` | finds English strings that are still in a built Hebrew ROM |
| `strcov.py` | string coverage: maps the logs of the string-report build (`make hns RTL_STRING_REPORT=1`) to the translated C strings and lists the ones no tour has shown |
| `strchars.py` | counts the non-ASCII characters and `{TOKENS}` used in string literals (`[TREE]`, default `HNS_TREE`) |
| `textwidth.py` | pixel width model of the RTL renderer (CLI and library) |
| `translit_stats.py` | statistics on FireRed transliteration choices, for `transliteration_rules.md` |
| `units.py` | extracts strings into units and writes translations back |
| `wrap.py` | wraps a Hebrew string to a kind's pixel budget |

`emu/` holds the headless mGBA harness (see `emu/README.md`). `data/` holds what the tools read
at run time: `budgets.json` (pixel budgets per string kind), `live_labels.json` and
`c_strings.json` (which script labels and C literals the H&S build uses), `inventory.json` (files
and batches) and `font_drafts/` (draft Hebrew widths for `--hebrew-widths draft`).

Tests: `python3 -m unittest discover -s tools/hebrew/tests`. The test for the English ROM runs only
when `HNS_EN_ROM` exists.
