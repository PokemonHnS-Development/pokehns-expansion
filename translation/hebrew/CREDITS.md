# Credits for the Hebrew translation

This file says where the parts of the Hebrew build that were not made for it come from. Counts
were measured on the tree of `he/main` `a5d6c1a101` (2026-11-12); the commands are given so that
they can be measured again.

## The game

The Hebrew build is a translation of **Pokémon Heart & Soul 2.0.6**,
[PokemonHnS-Development/pokehns-expansion](https://github.com/PokemonHnS-Development/pokehns-expansion),
tag `Release-v2.0.6` (`167aa6d537`). Heart & Soul is built on resetes12's Modern Emerald, RHH's
[pokeemerald-expansion](https://github.com/rh-hideout/pokeemerald-expansion) and pret's
[pokeemerald](https://github.com/pret/pokeemerald) (the repository's `README.md`, which names
expansion 1.15.1; `include/constants/expansion.h` says 1.15.2). Apart from the
Hebrew text, glyphs and art labels, the right-to-left drawing, the tools in `tools/hebrew/` and the
fixes listed at the end, the game is theirs; their contributors are credited in the repository's
`README.md` and `CREDITS.md`.

## The FireRed Hebrew translation

[ofir286/pokefirered-heb](https://github.com/ofir286/pokefirered-heb) is ofir286's Hebrew
translation of Pokémon FireRed and LeafGreen, a fork of pret's pokefirered. The comparisons below
use its `master` at `4325a4f01` (2025-05-30). Pull request
[#2](https://github.com/ofir286/pokefirered-heb/pull/2) to it, by the maintainer of this
translation, is open and not merged (head `df2ee712e`); where something comes only from that pull
request, this file says so.

### Letter shapes

The Hebrew glyphs are drawn from `tools/hebrew/fonts/hebrew_glyph_designs.txt`, whose header
records the origin. They were added in `6fa10945bb`; their drafts were derived from FireRed's fonts
by `tools/hebrew/fonts/derive_hebrew_drafts.py`.

| Font (`graphics/fonts/`) | Letter set | Where the letters come from |
| --- | --- | --- |
| `latin_short.png` | `W6_7` | FireRed `graphics/fonts/latin_normal.png`, cells `0x01`-`0x1B`, with the ink moved to column 0; 25 of the 27 letters are pixel for pixel FireRed's, and ן and ף end one row higher |
| `latin_normal.png` | `W6_8` | `W6_7` with one body row added |
| `latin_small.png` | `W5_7` | FireRed `graphics/fonts/latin_small.png`; all 27 letters are pixel for pixel FireRed's |
| `latin_narrow.png` | `W5_8` | `W5_7` with one body row added |
| `latin_short_narrow.png` | `W5_7S` | `W5_7`, ל with an ascender |
| `latin_small_narrow.png` | `W5_7SN` | `W5_7`, the final letters shortened |
| `latin_narrower.png`, `latin_short_narrower.png`, `latin_small_narrower.png` | `W4_8`, `W4_7S`, `W4_7` | drawn for this translation |

- The level glyph רמה of the normal and short fonts is FireRed's (its `{LV_2}` glyph, cell `0x105`
  of `latin_normal.png`, drawn in `1d2e4edb8`) with one pixel added to the left leg of ה, plus
  the shadow: 13 px (`6fa10945bb`). The other seven fonts use a compact 12 px form made for this
  translation.
- FireRed's Hebrew font work is in its commits `60ea5108f` (2023-12-12, the alphabet in
  `latin_normal.png`), `f756bcc31` (2023-12-14, `latin_small.png`), `1d2e4edb8` (2023-12-18, רמה
  for Lv), `14c630eb2` (2025-05-04) and `23c3a599f` (2025-05-05), all by ofir286. Pull request #2
  changes no font file.
- The left cursor ◀ is the mirror of the game's own ▶.

### Names

`translation/hebrew/glossary.csv` has a `firered_hebrew` column, FireRed's name for the same
constant or English name, filled in 2,001 rows.

- 1,915 rows have the status `inherited`: their name is FireRed's. 1,814 of them print FireRed's
  spelling exactly. Of the other 101, 68 hold digits, which FireRed stores reversed and this build
  stores in reading order; 32 are berries, all named פרי here (`DECISIONS.md` K6); and EXEGGUTOR
  is one letter shorter, to fit the Pokédex list. By kind: 502 species, 308 moves, 305 items, 271
  Pokédex categories, 193 trainer names, 137 trainer classes, 72 abilities, 48 map sections, 37
  terms, 25 natures, 15 types, 1 speaker and 1 place.
- Of the 1,915 inherited names, 1,526 occur in ofir286's `master` and 388 only in pull request #2
  (261 species, 93 moves, 33 items and 1 term). The species table of `master` names the 151
  species of Gen 1, and the pull request adds the other 235 (`6086bad15`); `master` names some of
  those only in its text, for example in a Pokédex entry. One name, SWEET KISS, is written
  differently in both.
- 13 `proposed` rows also print FireRed's name, and the `notes` of many others name the FireRed
  form or pattern they follow (for example `FR canon`, `FR's TM/HM pattern`, a `pokefirered-heb`
  path).
- `translation/hebrew/transliteration_rules.md` is derived from FireRed's names, and
  `translation/hebrew/DECISIONS.md` Q140 follows the naming conventions settled in pull request #2.

### Easy Chat words

775 of the 999 Easy Chat words (`src/data/easy_chat/easy_chat_group_*.h`) print the same text as
the same word in ofir286's `master`, where the words were translated in `e7381e35e` and
`3cfe577f6` (2025-02-09); pull request #2 changes four of them (`f5d0c2116`). Of the 482 words
translated last, 354 took FireRed's word (`DECISIONS.md` Q135). The group names TIME and MISC. are
FireRed's, זמן and שונות.

### Wording

`translation/hebrew/STYLE.md` takes FireRed's dialogue as the model for the voice. Where both games
have the same line, some lines read as FireRed's do: 127 distinct string literals of four or more
Hebrew words (a dialogue line or a whole short text each) are identical to a literal in
ofir286's `master`.

### Further back

ofir286's README credits the Hebrew translation of Pokémon Red and Blue,
[Nog-Frog/pokered](https://github.com/Nog-Frog/pokered), for early translation work that was
"inspired by (and in some cases taken from)" it. Names that reached FireRed from there reach this
translation through FireRed.

## Licence and permission

- ofir286/pokefirered-heb has no licence file: GitHub reports no licence for it, and its README
  grants none (checked on 2026-11-12). GitHub reports no licence for Nog-Frog/pokered either, nor
  for Heart & Soul, pokeemerald-expansion and pret's decompilations.
- Permission from ofir286 to use the letter shapes, names and words listed above in this
  translation is not recorded anywhere in this repository. This file credits the work; it does not
  claim a licence to it.
- If permission is refused, the `W6` and `W5` letter sets and the 13 px רמה can be redrawn, as the
  `W4` sets were, and the inherited names, the Easy Chat words and the identical lines written
  again.

## Fixes from other translations and pull requests

Six fixes to the English game came with this translation; each fixes a bug that someone else
found or fixed first:

- `560f5e8bdb` (the map-name pop-up tinted by the time of day) is the change of SkeletonKey36's
  pull request [#24](https://github.com/PokemonHnS-Development/pokehns-expansion/pull/24), and the
  fix their pull request 78 made on the 1.x line
  ([PokemonHnS-Development/pokemonHnS](https://github.com/PokemonHnS-Development/pokemonHnS)).
- `1a0a649f68` (the PokéGear TOUGH label in yellow) and `8852402949` (the condition search results'
  header) were found in Si-Gon's Spanish translation,
  [#37](https://github.com/PokemonHnS-Development/pokehns-expansion/pull/37); the palette lines of
  `1a0a649f68` are the same as there.
- `f96cb7a4f9` (the wild victory music) and `d5447bdd85` (the Pokédex area view at night) fix bugs
  that Exclsior's pull request 20 and SkeletonKey36's pull request 104 fixed on the 1.x line.
- `d40d894676` (a press skipping a short page at instant text speed) fixes, with a different
  change, the bug of ericmaddox's pull request
  [#35](https://github.com/PokemonHnS-Development/pokehns-expansion/pull/35), which was closed.

## Measuring again

From the repository root, with ofir286's repository cloned next to it as `../pokefirered-heb`
(remote `origin`) and pull request #2 fetched with
`git -C ../pokefirered-heb fetch origin pull/2/head:refs/remotes/pr2/head`:

- The letters: compare each `@glyph` block of the designs file with the foreground pixels of the
  same letter's cell in FireRed's PNG, both trimmed to their ink. A pixel is foreground when its
  palette index modulo 4 is 1, as gbagfx converts the PNG (FireRed's ב has one pixel of index 5).
  `tools/hebrew/fonts/inspect_fonts.py` reads FireRed's `latin_small.png` with
  `--layout frlg_small`.
- The names: for each `inherited` row, look for its `firered_hebrew` text in
  `git -C ../pokefirered-heb grep -h -I -e . origin/master -- src data include`, then in the same
  output for `pr2/head` (the pull request's head, `df2ee712e`). Count a match only as a word: no
  Hebrew letter or geresh glued on either side, except a one-letter prefix of the name itself
  (בקבר חול). The matches that are not a whole string literal were checked by hand. A plain
  substring search counts 1,539 in `master`; 13 of them are parts of other words or names, such
  as פורט inside ספורט, וינגול inside ווינגול and נומל in the berry תות נומל.
- The Easy Chat words: pair each `EC_INDEX` entry of a group file with the entry at the same
  position in FireRed's group array and compare their texts. The two lists hold the same words in
  the same order, except FRONTIER and EMERALD, Emerald's last words of two groups, which FireRed
  does not have.
