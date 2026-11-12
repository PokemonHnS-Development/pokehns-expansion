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
  רמה (level), נקודות ניסיון (EXP; the full spelling ניסיון, as FireRed now writes it). Hebrew uses the
  definite article and prefixes on these normally: `הפוקימון שלך`, `לפוקדקס`, `במרכז הפוקימון`.
- Upper-case English names (NEW BARK TOWN, PROF. ELM) are just names: Hebrew has no case.
  `PROF. ELM` = `פרופ' אלם` (abbreviation with a geresh), unless the glossary says otherwise.
- Generic place words are translated, proper parts transliterated: `העיירה ניו בארק`,
  `העיר ויולט`, `דרך 29` (glossary `mapsec` rows are authoritative).
- Hoenn places have `place` rows (`העיר ראסטבורו`); dialogue uses the proper part with the prefix
  attached (`בראסטבורו`), as for Johto. A common English word after MT. is translated (`הר המוקד`).
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
| Prefix before Latin or digits | a maqaf: `ב-20`, `ה-2`, `ל-PC` | One to three prefix letters (ו ה ב כ ל מ ש) before Latin letters or digits always take the hyphen. Before a placeholder write the prefix bare, `ל{PLAYER}`, `ב{STR_VAR_1}`: the engine adds the hyphen when the name or number comes out in Latin letters or digits and leaves a Hebrew name joined (`ל-GOLD`, `לגולד`; DECISIONS.md Q149). Keep a written hyphen (`ב-{STR_VAR_1}`) only where the placeholder is always a number |
| Digits | normal reading order: `דרך 32`, `500¥`, `10:30` | The renderer handles direction. **Never reverse digits** (FireRed did; we do not) |
| Currency | keep `¥` where the English has it, in the same position relative to the number | |
| ♂ ♀ … ! ? . , : ; ( ) | as in English | Punctuation goes at the logical end of the Hebrew sentence |

## 5. Control codes and structure (hard rules, checked by `tools/hebrew/drift.py`)

- Preserve every `{...}` token byte for byte and **in the same order** as the English string:
  `{PLAYER}`, `{RIVAL}`, `{STR_VAR_1..3}`, `{B_*}`, `{COLOR ...}`, `{PAUSE ...}`, `{PLAY_SE ...}`,
  `{PKMN}`, `{POKE}`, `{LV}`, `{KUN}`, etc. One exception: the battle text buffers `{B_BUFF1}`,
  `{B_BUFF2}` and `{B_BUFF3}` are each filled from their own buffer, so they may swap places with
  each other; every other placeholder keeps its place. If Hebrew word order needs another
  placeholder elsewhere in the sentence, rephrase so the order stays the same; if that is
  impossible, report the string instead of reordering.
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
  them is the one allowed token change besides the battle buffers' swap. `drift.py`
  (`DROPPABLE_TOKENS`, `REORDERABLE_TOKENS`, `same_tokens`) defines this rule, and `units.py` and
  `checkunits.py` use the same one. A translated string that keeps one of them gets a `GLYPHPAIR`
  warning from `drift.py`; `{POKEBLOCK}` is `פוקיבלוק` (glossary `TERM_POKEBLOCK`).
- Do not translate: braille text (`.braille`), the R+START debug menu (`src/debug.c`, and `data/scripts/debug.inc` except `Debug_Text_ArianaDefeat` and `Debug_Text_Grunt23Defeat`, which the Rocket Hideout story battle uses), Latin literals
  compared by code (the "SampleCode" check, Walda's phrase, the Odd Egg name list), and anything
  in an `#if 0` / unused block. The battle debug menu (`src/battle_debug.c`, opened with SELECT in any battle) is translated and uses the glossary's terms.
- Easy Chat words (`src/data/easy_chat/easy_chat_group_*.h`) are Hebrew. A word is at most 72 px
  and 12 bytes, like the widest English word. A word the game compares with the player's phrase
  (the Odd Egg passwords, the questionnaire's Mystery Gift phrase and the Berry Master's wife's
  phrases in `src/easy_chat.c`) prints a text no other enabled word prints. Other words share a
  text where Hebrew has one word for several English ones (I and I AM אני, NOT and DON'T לא); each
  such text is listed in `SHARED_TEXTS` of `tools/hebrew/tests/test_easy_chat.py`. Trainers speak in
  these words, so they take the spoken forms (אני, הוא, לא), not the formal present (הנני, הינו).
  Glossary names and terms keep their glossary form; the Odd Egg hint windows
  (`src/data/help_window.h`) quote the password words exactly. After changing a word, run
  `tools/hebrew/gen_ec_order.py` (the Hebrew order of the group lists) and
  `tools/hebrew/gen_ec_letters.py` (the ABC keyboard's lists, which a species or move rename also
  changes); `tools/hebrew/tests/test_easy_chat.py` checks the rest.

## 6. Length and width (checked by `tools/hebrew/audit.py`)

- Hebrew is one byte per letter. Byte limits are hard (overflow corrupts memory or fails the build):
  species 12 (10 preferred), move 16, ability 16, item 19 (plural 21), type 8, trainer name 10,
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
