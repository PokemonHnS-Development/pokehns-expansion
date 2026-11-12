# Hebrew translation guide (Heart & Soul)

Everything here is about the Hebrew branches of this fork (`he/*`). None of it applies to upstream
Heart & Soul. The tools named here live in `tools/hebrew/` (see its `README.md`); the glossary,
the style guide and the transliteration rules live in `translation/hebrew/`.

## How Hebrew is stored

`charmap.txt` maps the alphabet onto bytes that no Latin character uses, so leftover English
(`POKéMON`, whose `é` is `0x1B`) keeps rendering:

| Letters | Bytes |
| --- | --- |
| א ב ג ד ה ו ז ח ט י כ ל מ נ ס ע פ צ ק ר ש ת | `0x3A`–`0x4F`, in alphabetical order |
| ך | `0x50` |
| ם ן ף ץ | `0x5E`–`0x61` |
| ◀ (the right-to-left menu cursor) | `0x87` |

`include/constants/characters.h` names them (`CHAR_HEB_ALEF` … `CHAR_HEB_FINAL_TSADI`,
`IS_HEBREW_CHAR`). The geresh is the ASCII apostrophe (byte `0xB4`, as in FireRed), the
gershayim is `”` (`0xB2`). There is no straight double quote.

**Write Hebrew in logical order, and write numbers the way you read them.** Unlike the FireRed
fork, digits are never reversed: the renderer draws Latin and digit runs left to right.

## How right-to-left works

All of it is in `src/text.c` (the `#if TEXT_RTL` block, switched on in `include/config/text.h`)
and `src/window.c`.

**The logical pen is upstream's.** A window printer's `x`, `currentX`, `{CLEAR_TO}`, `{SKIP}` and
every layout computed with `GetStringWidth` mean what they mean in English. Only the blit is
mirrored: a glyph at logical `x`, `w` pixels wide, lands at `axis - x - w`. So a string that fits
in English fits in Hebrew, and no call site needs an "RTL anchor".

**Runs.** When a printer meets a Latin letter or a digit (or a currency sign, plus or minus
before a digit), it measures the run up to the last Latin letter or digit before the next Hebrew
letter or pen-moving code, and draws the run left to right as one block at its mirrored place.
Neutrals between two run characters belong to the run; neutrals after it take the paragraph's
direction. Colour codes, pauses, sounds and leftover placeholder bytes do not end a run. The
numero sign `{NO}` is a neutral, not part of its number's run, so it stands right of the number
and is read first, as Unicode places it: `01№`, `006№` (DECISIONS.md Q148).

**The prefix maqaf.** A Hebrew prefix is joined to Latin letters and digits with a hyphen and to
Hebrew directly (`ב-20`, `לגולד`). For a name or number filled in at run time, the three
placeholder expanders (`StringExpandPlaceholders`, `BattleStringExpandPlaceholders`,
`DynamicPlaceholderTextUtil_ExpandPlaceholders`) ask `RtlNeedsPrefixMaqaf`: when the template
has one to three of ו ה ב כ ל מ ש right before the placeholder, after a space, punctuation, a
code or the start, and the placeholder's text starts with a Latin letter or a digit or is a name
from a Japanese game (`{JPN}`), a hyphen is put before it (`ל-GOLD`; DECISIONS.md Q149). The
renderer already keeps a hyphen right after a Hebrew letter with that letter.

**Mirrored glyphs.** Outside a run, `( ) < >` swap with their partners and the menu cursor `▶`
becomes `◀`. Arrow characters are left alone: they show physical directions.

**Windows have modes** (`include/window.h`):

| Mode | What it does | Used for |
| --- | --- | --- |
| `WINDOW_RTL_MIRROR` (default) | Glyphs and the window primitives (`FillWindowPixelRect`, `BlitBitmapRectToWindow`, the 8-bit variants, `FillWindowTilesByRow`) mirror around the window's mirror width, so cursors and icons move with the text | Dialogue, lists, menus, plain boxes |
| `WINDOW_RTL_IN_PLACE` | Each text segment (up to a newline or a pen-moving code) reads right to left inside the extent it has in English; fills and blits stay. A segment with no Hebrew keeps the English layout | Text in fixed boxes on art, next to sprites or tilemap cursors, or prints that only line up in English (party slots, battle menus, the level-up banner, healthbox scratch windows, the ability pop-up, the bag pocket title, the PC box title) |
| `WINDOW_RTL_LTR` | Untouched | |

Set a mode with `SetWindowRtlMode(windowId, mode)` right after the window is created (it resets
on `InitWindows`, `AddWindow`, `RemoveWindow` and `FreeAllWindowBuffers`). A window whose box art
is narrower than the window mirrors around a smaller axis: `SetWindowRtlMirrorWidth(id, px)`.
The overworld dialogue box uses 208 px (26 tiles), because its frame pads only the left side;
the Pokédex windows use the visible 240 px of their 256-px windows.

**Sprite text** (the healthbox) is printed immediately, so the string is reordered into visual
order and printed left to right in its English position.

## Other engine changes

- `IsStringJapanese` does not count Hebrew letters as kana.
- Battle text puts "wild"/"opposing" after the name (`TEXT_NAME_SUFFIX_IN_BATTLE`), so the
  prefix strings hold the definite `" הפראי"` and `" היריב"`. The ability pop-up drops the English
  possessive, and the Pokédex category puts פוקימון first. The switch is defined as `TEXT_RTL`
  (`include/config/text.h`), so a build with `TEXT_RTL` FALSE keeps upstream's English prefixes.
- The speaker name box sits at the right end of the dialogue box.
- The start-menu clock is one 24-hour string.
- Grid menus swap LEFT and RIGHT in mirrored windows.
- The Pokédex name search groups the Hebrew alphabet three letters at a time; the list falls
  back to the narrower font when a name is wider than its column; the A–Z order is generated from
  the Hebrew names (`gen_dex_alpha.py`).
- The Easy Chat group lists follow the Hebrew order of the words, generated from the word texts
  (`gen_ec_order.py`, `src/data/easy_chat/easy_chat_order_rtl.h`). The ABC keyboard shows the
  Hebrew letters, each opening the words, species and moves whose Hebrew text starts with it
  (`gen_ec_letters.py`, `src/data/easy_chat/easy_chat_words_by_letter_rtl.h`). The keyboard and
  the word list are mirrored inside the frame drawn behind them, the cursors stand right of their
  word and point left, and the YES/NO box sits over the footer's OK option at the left end.
- The healthbox drops the level glyph when glyph and digits do not fit (level 100).
- Lists sorted by name (the bag's A–Z sort, the move relearner) use `StringCompareAlphabetical`:
  final letters sort with their ordinary forms, and a name sorts before the longer names that
  start with it.

## Fonts

All nine Latin fonts carry the Hebrew letters, the left cursor `◀` and a Hebrew level glyph
(`רמה`, replacing `Lv` at `0x34` and `0x105`). Widths are in the tables in `src/fonts.c`; the
advance is the table value, nothing else. `tools/hebrew/textwidth.py` reads those tables.

## Budgets

Measure, do not count characters. The most common budgets (all from
`tools/hebrew/data/budgets.json`, which `audit.py` and `wrap.py` read):

| Kind | Font | Width | Lines |
| --- | --- | --- | --- |
| Overworld dialogue and signs | normal | 208 px (200 on a line that ends in `\l` or `\p`) | 2 |
| Battle text | normal | 208 px | 2 |
| Item description | normal | 102 px | 3 |
| Move description (summary) | normal | 152 px | 2 |
| Ability description | small | 139 px | 1 |
| Pokédex entry | normal | 224 px | 3 |

Hard byte limits: species 12, move 16, ability 16, item 19, type 8, trainer name 10, trainer
class 12, berry 6, map name 19; an expanded message under 999 bytes (`gStringVar4`), a battle
message under 424.

## Tools and the workflow

| Tool | What it does |
| --- | --- |
| `units.py` | Extracts every live string into JSON units and writes translations back, refusing any change outside the string |
| `make_chunks.py` | Cuts batches into chunks, pre-fills names from the glossary |
| `checkunits.py` | Validates a chunk: tokens, `$`, escapes, charset, digits, widths, lines |
| `drift.py` | Compares a translated file with the English baseline: only strings may differ |
| `namecheck.py`, `glossary_widths.py` | Glossary byte limits, final letters, duplicates, on-screen widths |
| `apply_names.py` | Writes trainer and map-section names (`.party`, JSON) |
| `textwidth.py`, `audit.py`, `wrap.py` | The width model, a whole-tree budget audit, a re-wrapper |
| `rom_sweep.py` | Finds English left in a built ROM |
| `status_report.py` | Writes `translation/hebrew/STATUS.md`; `--sweep` marks the files the dialogue sweep rendered |
| `flag_gates.py` | Takes the labels behind flags defined as 0, and the labels that are not built, out of the live list |
| `gen_dex_alpha.py` | Regenerates the Pokédex A–Z order |
| `gen_ec_order.py` | Regenerates the Hebrew order of the Easy Chat group lists |
| `gen_ec_letters.py` | Regenerates the Easy Chat ABC keyboard's lists by Hebrew letter |
| `emu/` | Headless mGBA harness, the save ladder, the screen tours (`hns.py tour`), the dialogue sweep (`sweep.py`), the map walk (`mapwalk.py`) and the libretro frontend for other cores (`crosscore.c`) |
| `check_tests.py` | Compares a `make check` log with the tests upstream already fails (`data/known_test_failures.txt`) |
| `check_chunked.py` | Runs the `make check` suite one test-name prefix at a time, so that it fits the memory of a CI runner; a test in `data/crashing_tests.txt` runs alone |
| `testmsgs/` | Rebuilds the battle tests' Hebrew message table (below) |
| `release/` | Builds a release candidate from one commit, runs every harness test on the files that ship and writes its `TESTING.md` (`tools/hebrew/release/README.md`; the screenshot review is in `REVIEW.md` there) |

## Tests

Upstream 2.0.6 does not pass its own suite (about 1,900 tests fail on the English build), so the
Hebrew build is held to "no test fails that passes upstream". The battle tests expect English
messages; `test/test_runner_battle.c` swaps each expected message for the Hebrew the game prints,
from `test/hebrew_battle_messages.h` (see `tools/hebrew/testmsgs/README.md`). The text-width tests
in `test/text.c` run on the Hebrew names; their English-only lists of names known to overflow do
not apply.

CI (`.github/workflows/hebrew.yml`) builds the ROM and the clip-report ROM on every push to `he/*`,
runs the drift check against `he/renderer`, the layout audit, the glossary checks, the checks that
the generated Pokédex A–Z order, Easy Chat lists and live-label list are up to date, the tool tests
and `make check`. It never uploads a ROM.

## What is left / what this cannot see

Each build's `TESTING.md` lists what was tested on that exact ROM and what was not. In short:

- **Not seen by a person.** Every check is automated: screen tours, the clip report, the dialogue
  sweep, the map walk, the save ladder, cross-core frames, `make check`, and a review of the tour
  screenshots against English. Nobody has played from a new game to the first badge, and nothing
  ran on real hardware.
- **Screens the release tours do not reach.** The Battle Frontier facilities, contests from start
  to finish, the Trainer Hill, the Battle Tents, mail, the credits and the Hall of Fame were seen in
  the review rounds' own tours (`tools/hebrew/emu/tours/<round>/`), which each release does not run
  again. The link screens were seen with the partner faked in memory; a real link with a second
  GBA was never tried.
- **Proposed names.** Pokémon from Gen 4 on and many NPCs are transliterations with status
  `proposed` in the glossary; they have not been checked against an official Hebrew source, and no
  native speaker has read the text on screen.
- **Style calls.** Every open question from the review of the first release candidate is decided in
  `translation/hebrew/DECISIONS.md`: for example the trainer ID label `מס'` (K2), פוקיגיר for POKéGEAR
  (K3), move names without quotation marks in dialogue (Q2), 'מזל טוב' for "Congratulations" (Q6) and the
  apprentices' English name column (Q50). The summary's PP label is נ”כ.
- **Easy Chat.** All 999 Easy Chat words are Hebrew: 517 from the first translation and 482 from
  FireRed's words and the glossary (the other 9 entries of the lists are punctuation). Where
  Hebrew has one word for several English ones, they print the same text (I and I AM אני, NOT
  and DON'T לא); the words the game compares (the Odd Egg passwords, the Mystery Gift phrase)
  each have a text of their own. Trainer phrases put the words in English order, one word after
  another. The ABC keyboard shows the 22
  Hebrew letters and files every word, species and move under the first letter of its Hebrew text
  (`DECISIONS.md` Q135).
- **Kept in English on purpose:** the overworld debug menu (`src/debug.c`, `data/scripts/debug.inc`;
  DECISIONS.md Q120; the battle debug menu is Hebrew, Q118), the names of people, teams and games in the
  credits, and the Odd Egg name list (the game compares it with the player's name).
- **Graphics.** The PNGs in `graphics/` are the source of truth; the scripts that drew the Hebrew
  labels are in `tools/hebrew/graphics/` (its README says which script drew which file, and which
  files were changed by hand afterwards).
- **Female address.** The player is addressed in the masculine.
