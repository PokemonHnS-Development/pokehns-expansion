# Hebrew transliteration rules for Heart & Soul names

Derived from the names the FireRed Hebrew fork (`pokefirered-heb`, ofir286's translation; see `CREDITS.md`) already uses, so that new
Heart & Soul names read as if the same hand wrote them. Every example below is a real FireRed name
unless it is marked **(proposed)**.

Sources of the examples:
- species: `pokefirered-heb/src/data/text/species_names.h` (the line number is the name's line in
  that file); Gen 1 from commit `bc846a444` (2023-12-18), Gen 2–3 from commit `6086bad15`
  (2026-09-21, "translate: the remaining 235 species names")
- people: `pokefirered-heb/src/data/trainers.h` (`.trainerName`)
- places: `pokefirered-heb/src/data/region_map/region_map_sections.json` (`hebrew_name`)
- counts: `python3 tools/hebrew/translit_stats.py` (reads `glossary.csv`; 579 distinct
  inherited species and trainer names)

## 0. Where a name comes from, in order

1. **FireRed fork.** For Gen 1–3 species, Kanto places, moves, items, abilities, natures, trainer
   classes. These are `inherited` in `glossary.csv`. FireRed wins any conflict.
2. **Pokémon Israel's Pokédex** (pokemon-il.co.il, "הפוקידע המלא") for Gen 4–9 and anything else it
   covers. Read its `robots.txt` first. If it disallows automated fetching, do not fetch; collect
   the names by hand. Take names only, and log each conflict with FireRed in the glossary.
3. **These rules.** For anything neither source has, such as forms, regional variants and
   H&S-only people and places. Mark the row "proposed" in `notes` for review.

The rules below are what FireRed does. Where FireRed is inconsistent, the section says so and gives
the majority. For a new name, first look for an existing FireRed name that shares the same English
chunk, and copy its Hebrew for that chunk (see §6).

## 1. Storage conventions (how the bytes go into the ROM)

| Thing | Convention | Evidence |
| --- | --- | --- |
| Order | Logical order, as typed. Do not reverse words or strings. | `pokefirered-heb/docs/hebrew_translation.md:18-19` |
| Geresh (צ' ג' ז' ת' ץ') | ASCII `'`. Both `'` and `’` map to byte `B4`, but write `'`. Map `’ ‘ ׳` to `'` on import (`‘` is a different byte, `B3`). | H&S `charmap.txt:91-93`; FR `charmap.txt:113-114`; FR species use `'` 48 times and `’` never |
| Gershayim (מ”מ נ”ח נ”כ) | `”` U+201D, byte `B2`. There is no straight `"`. Map `״` and `"` to `”`. | H&S `charmap.txt:90`; FR doc `docs/hebrew_translation.md:215`; FR `items.json` `ITEM_TM01` = `מ”מ 10` (line 4629) |
| Digits | **Reading order in H&S.** FireRed stored multi-digit literals reversed (`ROUTE 10` = `דרך 01`, `region_map_sections.json:114`; `SEVII ISLE 23` = `אי 32`, line 762), because its renderer draws glyph by glyph. The H&S renderer draws digit runs left to right, so `glossary.csv` un-reverses them (55 items, 13 map sections; see each row's notes). | FR commit `566f05fdc` |
| Latin inside Hebrew | Allowed; stored in normal order (`התקפת X` for X ATTACK). | FR `items.json` `ITEM_X_ATTACK` |
| Symbols | Keep `♂ ♀ . - 2` from the English: `נידורן♀` (:31), `מר. מיים` (:124), `הו-הו` (:252), `פוריגון2` (:235). Drop the English apostrophe: FARFETCH'D = `פארפג'ד` (:85), where the `'` is a geresh. | species_names.h |
| Length | One byte per Hebrew letter, geresh, gershayim or space. Species ≤ 12 bytes (≤ 10 to survive the save/link records that use `VANILLA_POKEMON_NAME_LENGTH`), moves and abilities ≤ 16, items ≤ 20, trainer names ≤ 10, trainer classes ≤ 12, types ≤ 8, berries ≤ 6. | `include/constants/global.h:174-191`, `include/data.h:139`, `include/global.berry.h:4` |

## 2. Consonants

| English | Hebrew | Examples |
| --- | --- | --- |
| ch /tʃ/ | `צ'` | CHARMANDER `צ'רמנדר` (:6), PIKACHU `פיקאצ'ו` (:27), MACHOP `מאצ'ופ` (:68), CHIKORITA `צ'יקוריטה`, TORCHIC `טורצ'יק`, RICHARD `ריצ'רד` |
| ch /tʃ/ at word end | `ץ'` (final form + geresh) | TRAPINCH `טרפינץ'` (:334), BARBOACH `ברבואץ'`, MITCH `מיץ'` (trainers.h:3139), RICH `ריץ'`. 4 of 4 |
| ch /ʃ/ (French) | `ש` | MICHELLE `מישל` (trainers.h:5999) |
| tch | `צ'` / `ץ'`; the t is silent | MITCH `מיץ'`. FARFETCH'D `פארפג'ד` (:85) is an exception: FireRed voiced it to ג' |
| j | `ג'` | JIGGLYPUFF `ג'יגליפאף` (:41), JYNX `ג'ינקס` (:126), JOLTEON `ג'ולטיאון`, NINJASK `נינג'סק`, JIRACHI `ג'ירצ'י`, JACK `ג'ק` |
| g before e/i/y, sounding /dʒ/ | `ג'` | PIDGEY `פידג'י` (:18), GEODUDE `ג'יאודוד` (:76), MAGIKARP `מג'יקארפ` (:131), REGIROCK `רג'ירוק`, GEORGE `ג'ורג'`. Go by sound, not spelling: GENGAR `גנגר` (:96), TOGEPI `טוגפי`, LUGIA `לוגיה`, TANGELA `טנגלה` keep a hard ג |
| dg | `ג'` | PIDGEOT `פידג'יוט`, BRIDGET `ברידג'ט` |
| -sion, zh /ʒ/ | `ז'` | TYPHLOSION `טיפלוז'ן` (:159) |
| th at word end | `ת'` | VENOMOTH `ונומות'` (:51), GROWLITHE `גראולית'` (:60), SLAKOTH `סלקות'`, ANORITH `אנורית'`, RELICANTH `רליקנת'`, BETH `בת'` (trainers.h:5969), KEITH `קית'` (:3119) |
| th elsewhere | `ת` (no geresh) | ETHAN `איתן`, ANTHONY `אנתוני`, MARTHA `מרתה`, BETHANY `בתני`, THOMAS `תומאס`. SCYTHER `סייטר` (:125) uses ט. MEOWTH `מיאו` (:54) drops it, an exception |
| sh | `ש` | SHELLDER `שלדר`, ODDISH `אודיש`, SANDSHREW `סנדשרו`, MARSHTOMP `מרשטומפ` |
| ph | `פ` | TYPHLOSION `טיפלוז'ן`, AMPHAROS `אמפרוס`, PHANPY `פאנפי`, SPHEAL `ספיל` |
| f, ff, ph at word end | `ף` | JIGGLYPUFF `ג'יגליפאף`, BAYLEEF `בייליף` (:155), NUZLEAF `נאזליף`, JEFF `ג'ף`. 7 of 7 |
| p at word end | `פ` (not ף, because ף reads /f/) | MACHOP `מאצ'ופ`, MAGIKARP `מג'יקארפ`, MAREEP `מריפ` (:181), MUDKIP `מדקיפ`, PHILLIP `פיליפ`. 10 of 10 |
| k, ck, hard c | `ק` (never ך, which reads /x/) | ARBOK `ארבוק`, PSYDUCK `פסיידאק` (:56), CATERPIE `קטרפי`, BROCK `ברוק`. Word-final k: 26 of 26 are ק |
| kh | `ק` | KANGASKHAN `קנגסקאן` (:117) |
| soft c (ce/ci/cy) | `ס` | SCIZOR `סייזור`, CYNDAQUIL `סינדקוויל`, CELEBI `סלבי`, VANCE `ואנס`, GRACE `גרייס` |
| qu | `קוו` | SQUIRTLE `סקווירטל` (:9), NIDOQUEEN `נידוקווין`, CYNDAQUIL `סינדקוויל`, RAYQUAZA `רייקוואזה`. /k/ only: MASQUERAIN `מסקריין` |
| x | `קס` | VULPIX `וולפיקס` (:39), ONIX `אוניקס`, XATU `קסאטו` (:180), SNORLAX `סנורלקס`. ex- by sound: EXEGGCUTE `אקזגקיוט` (:104) vs EXPLOUD `אקספלאוד` (:374). The person name ALEX is `אלכס` (trainers.h:1979) |
| z | `ז` | ZUBAT `זובאט`, CHARIZARD `צ'ריזארד`, ELECTABUZZ `אלקטאבאז` |
| s sounding /z/ between vowels | `ז` | BULBASAUR `בלבאזור` (:3), VENUSAUR `וינאזור`, BLASTOISE `בלסטויז`, ROSELIA `רוזליה`, NOSEPASS `נוזפאס`, SNEASEL `סניזל`. Otherwise ס: ZANGOOSE `זנגוס`, LISA `ליסה` |
| final ts | `טס` (no ץ) | RALTS `רלטס` (:394) |
| w at word start | `ו` or `וו`, split 11 to 10. Before o/u the second ו is the vowel: WOOPER `וופר`, WURMPLE `וורמפל`. Before /a/: `וו`, as in WARTORTLE `וורטורטל` (:10), WALREIN `וולריין`, WALTER `וולטר`. Before an i/ei sound: Gen 3 uses one ו, as in WEEZING `ויזינג` (:112), WINGULL `וינגול`, WHISMUR `ויסמר`, WAILMER `ויילמר`; Gen 1 doubled it in WEEDLE `ווידל`, WIGGLYTUFF `וויגליטאף` and WEEPINBELL `וויפינבל`. **Rule for new names:** `וו` before /a/, /o/ or /u/, `ו` before a vowel written with י |
| w inside a word | `וו` | POLIWAG `פוליוואג` (:62), MAROWAK `מארוואק`, SWINUB `סווינאב`, SWAMPERT `סוומפרט`, QWILFISH `קווילפיש`, DWAYNE `דוויין`. EDWARD `אדוארד` and GWEN `גוון` are person names |
| wh | like w; the h is silent | WHISMUR `ויסמר`, WHISCASH `ויסקאש` |
| v at word start | `ו` | VULPIX `וולפיקס`, VENONAT `ונונאט`, VOLTORB `וולטורב` |
| v inside a word | `ב` 11, `וו` 7, `ו` 2. GRAVELER `גרבלר` (:77), LARVITAR `לרביטר`, QUILAVA `קווילבה`, STEVE `סטיב` (trainers.h:1649) vs MISDREAVUS `מיסדריווס` (:202), GARDEVOIR `גרדוואר`, EEVEE `איווי`. **Rule:** `ב`, unless the family already uses `וו` |
| h at word start | `ה`; dropped where silent | HAUNTER `האנטר`, HOOTHOOT `הוטהוט`, HO-OH `הו-הו`; HUGH `יו`, HUEY `יואי` |
| ng | `נג` | NIDOKING `נידוקינג`, WEEZING `ויזינג`, METANG `מטאנג` |
| doubled consonants | one letter | SHELLDER `שלדר`, HOPPIP `הופיפ`, KRABBY `קראבי` |
| -le at word end | `ל` | SQUIRTLE `סקווירטל`, WEEDLE `ווידל`, SHUCKLE `שאקל`, SMEARGLE `סמירגל` |

## 3. Vowels

Hebrew writes some vowels with matres lectionis (א ו י) and leaves the rest out. FireRed's habits:

| English sound | Hebrew | Examples |
| --- | --- | --- |
| o /o/ | `ו`, always | ONIX `אוניקס`, MACHOP `מאצ'ופ`, VOLTORB `וולטורב`, GOLEM `גולם` |
| u /u/, oo | `ו` | ZUBAT `זובאט`, LUGIA `לוגיה`, GLOOM `גלום`, ZIGZAGOON `זיגזגון` |
| u /ju/ | `יו` | CUBONE `קיובון` (:106), EXEGGCUTE `אקזגקיוט` |
| u /ʌ/ | `א` when stressed, often unwritten otherwise | GOLDUCK `גולדאק` (:57), MUK `מאק`, JIGGLYPUFF `ג'יגליפאף`, SHUCKLE `שאקל`; BUTTERFREE `בטרפרי` (:14) and BULBASAUR `בלבאזור` write nothing |
| a /a/ in the first syllable | usually unwritten (72), sometimes `א` (23) | CHARMANDER `צ'רמנדר`, CATERPIE `קטרפי`, SANDSLASH `סנדסלאש` vs MACHOP `מאצ'ופ`, KRABBY `קראבי`. Write `א` when the syllable is stressed and long (MACHAMP `מאצ'אמפ`, MAGIKARP `מג'יקארפ`), or when leaving it out would misread |
| a /a/ later in the word | `א` when stressed | PIKACHU `פיקאצ'ו`, ZUBAT `זובאט`, SANDSLASH `סנדסלאש`, CHARIZARD `צ'ריזארד` |
| i /ɪ/, ee, ea /i/ | `י` | PIKACHU `פיקאצ'ו`, WEEDLE `ווידל`, SEEL `סיל`, SPEAROW `ספירו`, SNEASEL `סניזל` |
| i, y /aɪ/ | `יי` | GRIMER `גריימר` (:90), PSYDUCK `פסיידאק`, SCYTHER `סייטר`, BLAZIKEN `בלייזיקן`, FLYGON `פלייגון`, GLIGAR `גלייגר`, RHYHORN `רייהורן` |
| ai, ay, a_e /eɪ/ | `יי` | BAYLEEF `בייליף`, RAIKOU `רייקו`, WAILMER `ויילמר`, RAYQUAZA `רייקוואזה`, RATICATE `רטיקייט`, BLAINE `בליין` |
| ai /aɪ/ | `אי` | RAICHU `ראיצ'ו` (:28) |
| short e | usually unwritten | SHELLDER `שלדר`, GENGAR `גנגר`, MEDICHAM `מדיצ'ם` |
| e /i/ before a vowel (-eon, -eo) | `י` | VAPOREON `ופוריאון` (:136), JOLTEON `ג'ולטיאון`, CHARMELEON `צ'רמיליון` (:7), GEODUDE `ג'יאודוד` |
| -er, -ar, -or at word end | consonant only | SHELLDER `שלדר`, HAUNTER `האנטר`, GENGAR `גנגר`, SCIZOR `סייזור` (when stressed: ו) |
| silent final e | dropped | ARCANINE `ארקניין` (:61), MACHOKE `מאצ'וק`, CUBONE `קיובון` |
| ow /aʊ/, ou | `או` | GROWLITHE `גראולית'`, DROWZEE `דראוזי`, NOCTOWL `נוקטאול`, HOUNDOUR `האונדור`, GROUDON `גראודון` |
| ow /oʊ/ | `ו`, sometimes `ואו` | SLOWPOKE `סלופוק` (:81), SPEAROW `ספירו` (:23) vs SLOWKING `סלואוקינג` (:201), SWELLOW `סוולואו`, MURKROW `מרקרואו`. FireRed is inconsistent here. Follow the family (SLOWBRO `סלוברו`) |
| oi, oy | `וי` | BLASTOISE `בלסטויז`, CLOYSTER `קלויסטר`, BALTOY `בלטוי` |
| y at word end | `י` | MANKEY `מאנקי`, CHANSEY `צ'נסי`, SKITTY `סקיטי`, JOEY `ג'ואי` (46 names) |
| vowel at word start | `א` for a, e, u (/ʌ/); `או` for o; `אי` for i/ee | ARBOK `ארבוק`, EKANS `אקנס`, UMBREON `אמבריאון`, ONIX `אוניקס`, IGGLYBUFF `איגליבאף`, EEVEE `איווי`. ETHAN `איתן`, EDNA `עדנה` are Hebrew names |

## 4. Final letter forms

Use them at the end of every word, never inside one. FireRed has no exceptions in names. The only
non-final letters at a word's end are abbreviations with gershayim (`מ”מ`, `נ”ח`, `נ”כ`), which keep
the regular form, as Hebrew abbreviations do. The counts:
`ם` 14/14 (GOLEM `גולם`), `ן` 72/72 (PORYGON `פוריגון`), `ף` for /f/ 7/7, `ץ'` for /tʃ/ 4/4.
Two cases do not take a final form: /p/ stays `פ` (MACHOP `מאצ'ופ`), and /k/ stays `ק`, never `ך`.
A final form *inside* a word is the signal that two words were run
together. FireRed did that on purpose, to fit its 64-pixel move cell: COMET PUNCH `אגרוףשביט`
(see the glossary notes on 8 moves, and FR commit `9908ae109`).

## 5. People and places

People:
- Most names are transliterated by the rules above: JOEY `ג'ואי`, CHAD `צ'אד`, BRIDGET `ברידג'ט`,
  SHANNON `שנון`.
- Names with a familiar Hebrew form take that form: SAMUEL `שמואל` (trainers.h:3919), JOSHUA
  `יהושע` (:3419), BENJAMIN `בנימין` (:6029), JONAH `יונה` (:6119), AARON `אהרן` (:3199), DAVID
  `דוד` (:2389), RUTH `רות`. Spanish names sound Spanish: JOSE `חוזה` (:3379), JULIA `יוליה`
  (:1309).
- Ranks and titles are translated: LT. SURGE `סמל סרג'` (:4159). PROF. OAK is `פרופ' אוק` in
  most dialogue strings and `פרופסור אוק` in the rest (FR text corpus, see the `TERM_PROF` row).
- The Rocket grunts' trainer name GRUNT was transliterated as `גראנט`, not translated. It is kept
  as canon.

Places (every FireRed map section):
- The generic word is translated and the proper part is transliterated: TOWN → `העיירה X` (PALLET
  TOWN `העיירה פאלט`, json:6), CITY → `העיר X` (VIRIDIAN CITY `העיר וירידיאן`), ISLAND → `האי X`
  (CINNABAR ISLAND `האי סיננבר`, :78), FOREST → `יער X` (VIRIDIAN FOREST `יער וירידיאן`, :348),
  CAVE → `מערת X` (CERULEAN CAVE `מערת סרוליאן`), MT. → `הר X` (MT. EMBER `הר אמבר`), ROUTE n →
  `דרך n` (ROUTE 1 `דרך 1`), PLATEAU → `רמת X` (`רמת אינדיגו`, :87), CHAMBER → `חדר X`.
- A specific part that is an ordinary English word is translated: MT. MOON `הר הירח` (:357),
  ROCK TUNNEL `מערת האבן` (:456), SEAFOAM ISLANDS `איי הקצף` (:465), TREASURE BEACH `חוף הזהב`
  (:573), POWER PLANT `מפעל החשמל`, VICTORY ROAD `דרך הניצחון`, BERRY FOREST `יער הפירות`.
- Kanto's colour and plant names are treated as proper names and transliterated: VIRIDIAN
  `וירידיאן`, CERULEAN `סרוליאן`, VERMILION `ורמיליון`, LAVENDER `לבנדר`, FUCHSIA `פושיה`, SAFFRON
  `סאפרון`. Johto's town names follow suit, for example VIOLET CITY `העיר ויולט`
  and ILEX FOREST `יער אילקס`.
- A Pokémon or trainer inside a place name keeps its glossary form: DIGLETT'S CAVE `מערת דיגלט`,
  ROCKET HIDEOUT `מחבוא רוקט`.

Worked Johto examples, all **(proposed)**, by the rules above:
NEW BARK TOWN `העיירה ניו בארק`, CHERRYGROVE CITY `העיר צ'ריגרוב`, AZALEA TOWN `העיירה אזיליה`,
GOLDENROD CITY `העיר גולדנרוד`, ECRUTEAK CITY `העיר אקרוטיק`, OLIVINE CITY `העיר אוליבין`,
CIANWOOD CITY `העיר סיאנווד`, MAHOGANY TOWN `העיירה מהגוני`, BLACKTHORN CITY `העיר בלקת'ורן`
(`ת'` because the th is /θ/), JOHTO `ג'וטו`. Ordinary words are translated: LAKE OF RAGE `אגם הזעם`,
ICE PATH `שביל הקרח`, DARK CAVE `המערה החשוכה`, BURNED TOWER `המגדל השרוף`. A reviewer decides.

## 6. Keep families together (the most useful rule)

When a new name shares an English chunk with an existing one, reuse that chunk's Hebrew exactly:
- Eeveelutions: VAPOREON `ופוריאון`, JOLTEON `ג'ולטיאון`, FLAREON `פלייריאון`, ESPEON `אספיאון`,
  UMBREON `אמבריאון`. So LEAFEON is `ליפיאון`, GLACEON is `גלייסיאון`, and SYLVEON is `סילביאון`
  **(proposed)**.
- Prefixes and suffixes: NIDO- `נידו`, HITMON- `היטמון`, POLI- `פולי`, -CHU `צ'ו` (PICHU `פיצ'ו`,
  RAICHU `ראיצ'ו`), -SAUR `זור` (IVYSAUR `אייויזור`, VENUSAUR `וינאזור`), REGI- `רג'י`, SLOW-
  `סלו`/`סלוא`.
- Cross-gen evolutions extend their family: MAGNEMITE/MAGNETON `מגנטון` gives MAGNEZONE `מגנזון`;
  TOGEPI `טוגפי` gives TOGEKISS `טוגקיס`; PORYGON2 `פוריגון2` gives PORYGON-Z `פוריגון-Z`
  **(proposed; check Pokémon Israel first)**.
- Regional forms: H&S builds them as `RATTATA-A`, `MEOWTH-G` and so on, with
  `P_SEPARATE_REGIONAL_FORMS` (`gen_1_families.h:2288-2292`). The glossary proposes the FireRed base
  name plus `-א` (Alola), `-ג` (Galar), `-ה` (Hisui) or `-פ` (Paldea). The suffix letters are a style
  call for review (46 rows).

`tools/hebrew/translit_stats.py <regex>` lists every FireRed name whose English matches the regex,
for example `python3 tools/hebrew/translit_stats.py 'EON$'`.

## 7. Known inconsistencies in FireRed (log them; do not fix silently)

- POKéDEX: `פוקדקס` in menus and most dialogue (42 strings), `פוקידקס` in 12.
- Berries: `גרגר צ'רי` (CHERI BERRY) and `פירות אורן` (ORAN BERRY); BERRY POUCH is `נרתיק פירות`.
- TM CASE: the item is `תיק מ”מ` and the menu is `קופסת מ”מ`.
- COOLTRAINER: was `מאמן על` and `מאמן-על`. FireRed now writes `מאמן-על` in both class rows, and the glossary
  and the game text follow it (`מאמן-על`, `מאמנת-על`, `מאמנת-העל`; DECISIONS.md Q140).
- Pokédex categories: `מקדחה`/`מקדח` (Drill). The Mushroom split (`פטריה`/`פטרייה`) is resolved: the
  category is `פטרייה`, as every other use of the word in the game.
- SAFARI ZONE: the map uses `אזור הספארי` and dialogue uses `איזור ספארי`. EXP: `נסיון` and `ניסיון`
  (the glossary and the game text take `ניסיון` everywhere; DECISIONS.md Q140).
- Initial W, medial V and ow /oʊ/ (§2, §3) vary between the Gen 1 and Gen 2–3 batches, which had
  different authors.
