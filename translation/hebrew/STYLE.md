# Heart & Soul Hebrew: translation style guide

Every translator follows this file, `glossary.csv` and `transliteration_rules.md`.
Where they disagree, the glossary wins for names and this file wins for everything else.

## 1. Source and voice

- Translate from the **English** in the upstream source tree (`HNS_UPSTREAM`, see
  `tools/hebrew/README.md`). The Spanish and
  French forks are only a cross-check for an ambiguous line, never a source.
- Voice: natural, modern, friendly Hebrew, the way the FireRed fork reads
  (`data/maps/*/text.inc` in the Hebrew FireRed fork). Short sentences. Spoken register for
  NPCs, neutral register for UI. No nikud. No slang that will date.
- Keep each character's voice: a gruff sailor, a child, a rival who sneers, a professor who
  lectures. Keep jokes as jokes; a pun that cannot survive gets a Hebrew joke of similar weight.
- Do not add or drop information. Hints, prices, directions, numbers and conditions must survive.

## 2. Gender (settled, do not reopen)

- **Every Pokémon is grammatically masculine**: `התעלף`, `פראי`, `ברח`, `{STR_VAR_1} גדל!`.
- **The player is addressed in the masculine singular** (`אתה`, `תרצה`, `קיבלת` is gender-neutral
  and fine). Where a line can be rephrased naturally to avoid second-person gender (imperative,
  plural, impersonal: `אפשר ל…`, `כדאי ל…`), prefer that. Never use slash forms such as `קיבל/ה`.
- NPCs keep their own gender: a woman speaking of herself uses the feminine (`אני מאמנת`).
  Check the English and the map's object graphics name (e.g. `OBJ_EVENT_GFX_LASS`, `WOMAN`, `GIRL`,
  `BEAUTY`, `TWIN`, `NURSE`, `MOM`) in the same map's `map.json` when the English hides it.
- Trainer classes in battle intros: use the class's own gender (`מאמנת קשוחה` for a female
  Cooltrainer if the glossary row says so).

## 3. Names and fixed terms

- Every proper noun and game term comes from `glossary.csv` (`proposed_hebrew` column). Never invent
  a spelling. If a name is missing from the glossary, leave the English name in place and add it to
  your report; do not guess.
- Fixed terms (glossary kind `term`): פוקימון / פוקימונים, מאמן, פוקדקס, פוקיבול, מרכז פוקימון,
  מכון (gym), מחשב (PC), מהלך (move), יכולת, אופי, סוג (type), נ”ח (HP), נ”כ (PP), מ”מ (TM), מ”נ (HM),
  רמה (level), נקודות נסיון (EXP). Hebrew uses the definite article and prefixes on these normally:
  `הפוקימון שלך`, `לפוקדקס`, `במרכז הפוקימון`.
- Upper-case English names (NEW BARK TOWN, PROF. ELM) are just names: Hebrew has no case.
  `PROF. ELM` = `פרופ' אלם` (abbreviation with a geresh), unless the glossary says otherwise.
- Generic place words are translated, proper parts transliterated: `העיירה ניו בארק`,
  `העיר ויולט`, `דרך 29` (glossary `mapsec` rows are authoritative).
- Move names in running dialogue are bare, as in FireRed: `להשתמש בגלישה`, `להשתמש במאבק`.
  In dialogue, quote with `”…”` only where the English quotes the word: a menu option to pick
  (`לבחור ב”מנוחה”`) or a name being explained (`התקצר ל”מנוחה”`). Descriptions and menus
  (move, item and Pokédex descriptions, the challenge menu) quote a move cited inside a
  sentence: `מהלכי טעינה כמו ”קרן על”`.

## 4. Characters you may use

Only characters in `charmap.txt`. In particular:

| Want | Write | Notes |
| --- | --- | --- |
| Hebrew letters | א–ת, finals ך ם ן ף ץ | Final forms at word end, always |
| Geresh | `'` (ASCII apostrophe) | `צ'`, `ג'`, `פרופ'`. In a `.string "..."` it needs no escape |
| Gershayim | `”` (U+201D) | `נ”ח`, `מ”מ`. There is no straight `"` in the charmap; in C strings `"` ends the literal |
| Quotation marks | `”…”` on both sides | FireRed's convention |
| Ellipsis | `…` (one character) | Not three periods |
| Dash | `-` | Also for maqaf: `ה-פוקדקס` only where FireRed does it; normally just attach the prefix |
| Digits | normal reading order: `דרך 32`, `500¥`, `10:30` | The renderer handles direction. **Never reverse digits** (FireRed did; we do not) |
| Currency | keep `¥` where the English has it, in the same position relative to the number | |
| ♂ ♀ … ! ? . , : ; ( ) | as in English | Punctuation goes at the logical end of the Hebrew sentence |

## 5. Control codes and structure (hard rules, checked by `tools/hebrew/drift.py`)

- Preserve every `{...}` token byte for byte and **in the same order** as the English string:
  `{PLAYER}`, `{RIVAL}`, `{STR_VAR_1..3}`, `{B_*}`, `{COLOR ...}`, `{PAUSE ...}`, `{PLAY_SE ...}`,
  `{PKMN}`, `{POKE}`, `{LV}`, `{KUN}`, etc. If Hebrew word order needs a placeholder elsewhere in the
  sentence, rephrase so the order stays the same; if that is impossible, report the string instead
  of reordering.
- Keep `$` exactly where the English has it (end of each text block). Never touch labels, script
  commands, `msgbox`/`goto`/flags, C code, `#if` lines, or non-text string literals (file paths,
  INCBIN, asm).
- Line breaks: `\n` = next line, `\l` = scroll one line, `\p` = new page. You may move `\n`/`\l` to
  re-wrap Hebrew, and add or remove `\p` only when a page would otherwise not fit; keep the number of
  pages close to the English. Battle strings without any manual break in English are auto-wrapped:
  keep them without breaks.
- `{POKE}` / `{PKMN}` render the Latin "POKé"/"PKMN" glyph pairs. In Hebrew text replace them with the
  Hebrew word (`פוקי`, `פוקימון`). `drift.py` ignores these glyph-pair tokens (`{POKE}`, `{PKMN}`,
  `{POKEBLOCK}`, the `{ID}{NO}` pair and the `{PK}` of the Easy Chat word `{PK}RS`), so dropping
  them is the one allowed token change.
- Do not translate: braille text (`.braille`), the R+START debug menu (`src/debug.c`, and `data/scripts/debug.inc` except `Debug_Text_ArianaDefeat` and `Debug_Text_Grunt23Defeat`, which the Rocket Hideout story battle uses), easy-chat/mail
  word lists unless your batch says so, Latin literals compared by code (the "SampleCode"
  check, Walda's phrase, the Odd Egg name list), and anything in an `#if 0` / unused block. The battle debug menu (`src/battle_debug.c`, opened with SELECT in any battle) is translated and uses the glossary's terms.

## 6. Length and width (checked by `tools/hebrew/audit.py`)

- Hebrew is one byte per letter. Byte limits are hard (overflow corrupts memory or fails the build):
  species 12 (10 preferred), move 16, ability 16, item 20 (plural 22), type 8, trainer name 10,
  trainer class 12, berry 6, map name 19 (region map) / 20 (pop-up), Pokédex category 12.
- Pixel budgets per kind are in `tools/hebrew/data/budgets.json`. The most common ones: dialogue 208 px per line
  (200 on a line ending in `\p` or `\l`), 2 lines per page; battle text 208 px, 2 lines; item
  description 102 px x 3 lines; move description 2 lines (summary 152 px, relearner 128 px);
  ability description 1 line, 139 px; Pokédex entry 3 lines x 224 px.
- As a rough guide, a 208 px dialogue line holds about 30–34 Hebrew letters in the normal font.
  Budget runtime substitutions at their worst case: `{PLAYER}`/`{RIVAL}` 7 letters, a species
  name 12, a nickname 12, an item name 20, a move name 16.
- Whole-buffer limits: an expanded message must stay under 999 bytes (`gStringVar4`); a battle
  message under 424 bytes after expansion.

## 7. Battle text grammar

- Name prefixes: `{B_ATK_NAME_WITH_PREFIX}` expands to the Pokémon name with a prefix string
  (wild/foe). The prefixes are translated in `src/battle_message.c` (`sText_WildPkmnPrefix` and
  friends). Hebrew puts the adjective after the noun, so they are suffixes, and they are definite
  (` הפראי`, ` היריב`, see §9): a name is definite, so its adjective takes ה in every position, after `את` too. A literal "wild" written in a string follows the English article: `{B_BUFF1} הפראי ברח!` for "The wild X fled!", but `פראי` in the encounter intros ("a wild X", "Wild X appeared!").
- Verbs agree in the masculine: `{B_DEF_NAME_WITH_PREFIX} התעלף!`, `… נפגע!`.

## 8. Process for a batch

1. Read this file, the glossary rows you need, and `tools/hebrew/data/budgets.json` for your string kinds.
2. Translate whole files, one at a time, editing the file in place in the translation tree.
3. Run `python3 tools/hebrew/drift.py <files>` and fix every error.
4. Re-read your Hebrew once against the English, line by line, for meaning, gender, names and
   numbers.
5. Report: files done, strings translated, anything left in English and why, every name you needed
   that the glossary lacked, and every judgment call.

## 9. Strings that the engine changes depend on (exact values)

| String | Hebrew | Why |
| --- | --- | --- |
| `sText_WildPkmnPrefix`, `sText_WildPkmnPrefixLower` (`src/battle_message.c`) | `" הפראי"` (leading space) | The engine appends it after the nickname. Definite like the English "The wild" (`פידג'י הפראי`) in every position, as is the literal in `STRINGID_WILDPKMNFLED`; only the encounter intros, which print the bare name for "a wild X", say `פראי` (FireRed's ` פראי` followed its article-less "Wild ") |
| `sText_FoePkmnPrefix`, `sText_FoePkmnPrefixLower` | `" היריב"` (leading space) | Same, definite like the English "The opposing" (`פידג'י היריב`) |
| `sText_FoePkmnPrefix2/3/4`, `sText_AllyPkmnPrefix/2/3` | `יריב` / `ידיד` (no space) | Stand-alone words; check how each is used before translating |
| `gText_DexSearchAlphaABC` … `gText_DexSearchAlphaYZ` (`src/strings.c`) | `אבג`, `דהו`, `זחט`, `יכל`, `מנס`, `עפצ`, `קרש`, `ת`, `A-Z` (in that order: ABC, DEF, GHI, JKL, MNO, PQR, STU, VWX, YZ) | The Pokédex name search now groups Hebrew letters that way |
| `sText_AM`, `sText_PM` (`src/start_menu.c`) | leave as is | The start-menu clock is now 24-hour and no longer prints them |
