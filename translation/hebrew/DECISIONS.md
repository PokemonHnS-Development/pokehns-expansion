# Translation decisions

Each entry is one open question from the review of the first release candidate: the six known issues listed in TESTING.md (K1–K6) and the reviewers' style and consistency questions (Q). For each one the analysis, the options with how each would be done and its risk, and the option chosen and why. "No change" means the current text was kept on purpose.

| ID | Question | Choice | Result |
|---|---|---|---|
| [K1](#k1) | Battle text after את: the wild/opposing suffix is indefinite (טירניטר פראי), so lines such as Intimidate read … | C. Make all four suffix strings definite (" הפראי"/" היריב") and the l… | changed |
| [K2](#k2) | The trainer ID label is the Latin glyph pair {ID}{NO} (IDNo) on the summary and trainer card, a style decision… | B. Hebrew short form "מס' " | changed |
| [K3](#k3) | POKéGEAR is written in Latin letters in dialogue and menus, consistently; the glossary has no Hebrew form. | B. פוקיגיר everywhere text is drawn | changed |
| [K4](#k4) | Naming screen: switching to the Hebrew page keeps the cursor column, so the cursor does not start on א. | A. Mirror the column when the swap crosses between the RTL page and an… | changed |
| [K5](#k5) | Cosmetic: the fainted tag fills its pill edge to edge; the descender of ק in a summary nickname touches the fr… | B. Fix each at its source, under TEXT_RTL or in Hebrew assets | changed |
| [K6](#k6) | Berry names come from the FireRed fork and mix the words גרגר, פרי, פירות and תות, as FireRed does; CHESTO is … | B. Unify to פרי / פירות, and fix the CHESTO and IAPAPA stems | changed |
| [Q2](#q2) | STRUGGLE in prose is written without quotation marks ('להשתמש במאבק'), following B30_01. | (a) Bare in dialogue, as now. Write the rule into STYLE.md §3, scoped … | changed |
| [Q5](#q5) | Brandon's nickname 'the chief' is rendered as 'הבוס', used the same way in both the attendant's and Brandon's … | (a) Keep 'הבוס' | no change |
| [Q6](#q6) | Frontier lobbies here and in B33/B34 say 'ברכות!' for 'Congratulations!', while the rest of the game mostly us… | A: 'מזל טוב' for every 'Congratulations', the HoF screen included; kee… | changed |
| [Q8](#q8) | The '{STR_VAR_1}-using {STR_VAR_2}' pattern (a move, then a species) has to keep the token order, so it is tra… | (a) Keep as the house wording | no change |
| [Q9](#q9) | The apprentices' mentor ({STR_VAR_3} in the Mon messages) is another player's name and may be female. | (a) Keep the masculine | no change |
| [Q11](#q11) | Sound words are a style call: crying 'סניף…' / 'היק…' (taken from the FireRed fork), cough 'כחח', and the coll… | (a) Keep the other spellings and make the cough 'כחח' everywhere | changed |
| [Q12](#q12) | Term for 'tag team': the glossary has no row for it, and each chunk uses a different word. | A: 'צוות זוגי' for 'tag team' ('הצוות'/'הצוותים' on a second mention);… | changed |
| [Q15](#q15) | Intro word order differs by speaker: 'אני {STR_VAR_1}, נערת קרב!' / 'אני {STR_VAR_1}, מאמן על!' versus 'אני נע… | (a) Keep | no change |
| [Q17](#q17) | Tag team: this chunk and B34_04 use 'צמד', while B35_01, B35_02 and B35_04 use 'צוות' or 'צוות זוגי' for the s… | A: Replace the 8 'צמד' lines with 'צוות זוגי' (on a second mention, 'ה… | changed |
| [Q18](#q18) | BATTLE PIKE is 'שביל הקרב' everywhere (strings.c gText_BattlePike, B09, B34), but the glossary class PIKE QUEE… | A: 'מלכת השביל' (now applied) | no change |
| [Q23](#q23) | MIMI (OutsideEast ConquerLeagueAndFrontier) and ZIGG (BelieveInYouBuddy, a Zigzagoon nickname) are not in the … | A: add NAME_MIMI = מימי and NAME_ZIGG = זיג, then apply them | changed |
| [Q24](#q24) | Battle Frontier facility names (מגדל/כיפת/ארמון/זירת/מפעל/שביל/פירמידת הקרב), היכל הדירוג, מוחות החזית, סלון ה… | A: Add term rows in the tree's existing forms | changed |
| [Q27](#q27) | Lounge3 ObtainedBattlePoints keeps 'השיג' to match B34_04. | A: 'השיג' for Battle Points; change ScottsHouse_hns:238 | changed |
| [Q29](#q29) | None of the Battle Frontier facility and event names are in glossary.csv: מגדל/כיפת/ארמון/זירת/מפעל/שביל/פירמי… | A: Add term rows (definite form as the headword, with a note on the co… | changed |
| [Q33](#q33) | FRONTIER BRAIN, FRONTIER PASS, BATTLE TOWER, BATTLE TENT, Battle Points, BERRY POCKET and Gold/Silver Symbols … | A: Add rows (english as the game writes it) and keep 'מוחות החזית' | changed |
| [Q37](#q37) | VerdanturfTown GentleMonsScaryIfAngry uses 'נעימה' for the speaker's sister to keep the GENTLE nature (נעים) l… | (a) Keep 'נעימה' | no change |
| [Q38](#q38) | The apprentice 'underling' (Guitarist) is rendered 'העוזר שלך', and 'mentor' and 'master' stay as the loanword… | (a) Accept as is | no change |
| [Q40](#q40) | 'I need to tap your mind again' is translated אני שוב צריכה את המוח שלך. | (a) Copy the :821 wording exactly into :1561 and :1848 | changed |
| [Q41](#q41) | 'Snivel/Sniff' is rendered סניף across B36_01 and this chunk. | (a) Keep 'סניף' | no change |
| [Q43](#q43) | ThanksNoHeldItem14 and ThanksHeldItem14 translate the odd English line 'Wouldn't it be too cool?' literally (ז… | (a) 'זה לא ייראה מגניב מדי?' | changed |
| [Q44](#q44) | Two live strings still show Emerald town names in Latin letters: VerdanturfTown_BattleTentLobby_Text_RulesAreL… | A: Use the H&S tent names in the two live strings | changed |
| [Q48](#q48) | 'crucial rule' is 'כלל מכריע' here and in the Palace lobby. | (a) 'כלל חשוב אחד' in all 3 | changed |
| [Q49](#q49) | For the Sailor rap I used the slang 'אחי' (bro) for the rhyme. | (a) Accept the register and spell it 'אולה' at :921 and :1897 | changed |
| [Q50](#q50) | Apprentice names (src/data/battle_frontier/apprentice.h): GAME_LANGUAGE is LANGUAGE_ENGLISH (include/constants… | A: revert the 7 foreign-column cells to their upstream values | changed |
| [Q52](#q52) | #112 'בלי להשתמש במהלך' vs 'בלי להשתמש באף מהלך' (clearer that no move at all was used): the longer form measu… | (c) 'בלי אף מהלך' | changed |
| [Q54](#q54) | Cross-chunk consistency: B37_s01 still has about 101 frontier trainer names in English. | A: nothing more to do | no change |
| [Q56](#q56) | Judgment calls the references do not settle: JORDAN ג'ורדן rather than the Israeli name ירדן; JORDYN ג'ורדין; … | B: JORDAN becomes ירדן; JORDYN and the others stay | changed |
| [Q57](#q57) | 68 frontier and tent trainer names in this chunk are still in Latin letters (TRISTON, FERRIS, ALIVIA, GRETEL, … | A: nothing more to do | no change |
| [Q59](#q59) | Not changed but worth a human ear: Tucker's 'לא נעים לך?' for 'Aren't you embarrassed?' (the alternative is 'ל… | (a) Keep both | no change |
| [Q60](#q60) | Twelve Trainer Hill trainer names are not in glossary.csv, so they stay in English as STYLE §3 says: SABINE, D… | A: nothing more to do | no change |
| [Q62](#q62) | 'Tag team' is translated inconsistently across chunks: צוות (B35_01), צוות זוגי (B35_02 and this chunk's Roof … | A: Adopt 'צוות זוגי' / 'שותף לצוות' / 'קרב צוות' project-wide (the Q12… | changed |
| [Q66](#q66) | JOHN DOE (trainer_hill.h@3480#170) is still in English. | A: keep ג'ון דו | no change |
| [Q67](#q67) | BREYDEN (#156), LUCIANA (#177) and GAVITE (#233) are Trainer Hill trainer names with no glossary row. | B: גאווייט | changed |
| [Q74](#q74) | If you want these names in Hebrew, these are my proposed glossary rows (trainer_name, 10-byte limit from u8 na… | A: keep the Trainer Tower names in Latin | no change |
| [Q75](#q75) | Policy clash between parallel reviewers in this run. | A: keep the applied rule: rows for reachable facilities, Trainer Tower… | no change |
| [Q78](#q78) | To clear those warnings, add these as glossary rows. | A: keep the remaining Trainer Tower names in Latin | no change |
| [Q79](#q79) | Decision for you: should the pair names (KAT & KIPP, GEB&MEGAN) be translated only once both halves have gloss… | A: keep the pairs in Latin, with GEB recorded as hard g (גב) for any f… | no change |
| [Q81](#q81) | Trainer Tower names AXE & REN (twice), CAMDEN, ZACKERY and MIKAELA are not in glossary.csv, so they stay in En… | A: keep them in Latin | no change |
| [Q83](#q83) | Alola_Akala_Totem_sign_Text_0 keeps the line break after אנרגיה, copying the English's own awkward break and m… | (a) Move the \n: 'מהטוטם נובעת\nאנרגיה חזקה…' in all 4 | changed |
| [Q84](#q84) | The hiking claim is worded differently on different islands: Akala's hiker says הטיולים הכי טובים and Ula'ula'… | (a) Ula'ula = 'באי אולאולה הטיולים הכי טובים!\p', and delete line 364 … | changed |
| [Q85](#q85) | Game Boy Advance: I followed FireRed's NPC wording, 'גיים בוי אדוונס'. | (a) 'גיים בוי אדוונס' everywhere, with a glossary term row | changed |
| [Q86](#q86) | HAU'OLI CITY (SamsonOak_Trigger_Beginning_Text_4) and ELIO (House5_Mom) are not in the glossary, so they stay … | A: העיר האואולי, and ELIO = אליו | changed |
| [Q89](#q89) | Samson's line about the real MELEMELE ISLAND (Trigger_Beginning_Text_4) adds 'שבאלולה' to tell it apart from t… | (a) Keep 'האי מלמלה שבאלולה' | no change |
| [Q93](#q93) | "demake" is translated as גרסת רטרו. | (a) Keep 'גרסת רטרו' | no change |
| [Q95](#q95) | Hiker battle intro "You must be tough to handle this rough terrain!" is kept impersonal (צריך להיות קשוח...), … | (c) Keep the impersonal wording | no change |
| [Q101](#q101) | The GREETINGS menu item (sText_Greetings) is 'ברכות', and sText_ShowTrainerCardMale quotes it ('בתור ”ברכות”'). | A: Keep 'ברכות' in all three | no change |
| [Q106](#q106) | Several names are missing from glossary.csv, so they stay in English as STYLE §3 requires: BRINEY ('קפטן BRINE… | B: BRINEY everywhere it appears in Hebrew, plus the existing MAXIE row… | changed |
| [Q111](#q111) | Several sibling strings in src/battle_debug.c are in no unit chunk, so they stay in English inside the Hebrew … | A. Translate the 14 labels with the glossary and in-game forms | changed |
| [Q112](#q112) | This chunk abbreviates AI as ב”מ (בינה מלאכותית), but the main-list item 'AI' stays Latin, so 'AI' sits next t… | A. Use ב”מ at :326 | changed |
| [Q118](#q118) | STYLE.md section 5 says not to translate debug-menu strings, but it names only src/debug.c. | A. Keep the battle debug menu in Hebrew and finish it | changed |
| [Q120](#q120) | STYLE.md excludes src/debug.c, but the overworld debug menu is on in this build (DEBUG_OVERWORLD_MENU TRUE, R+… | A. Keep both menus on and keep src/debug.c and debug.inc in English, b… | changed |
| [Q122](#q122) | The glossary has no row for TRICK MASTER. | A: Add term rows TRICK MASTER = 'אמן התעלולים' and TRICK HOUSE = 'בית … | changed |
| [Q123](#q123) | The opponent send-out and about-to-send battle lines use the masculine 'שלח'/'עומד' for every trainer, so Karen and the female leaders read… | A. Reword so the verb agrees with the Pokémon: 'הפוקימון של X, Y, יוצא לקרב!' | changed |
| [Q124](#q124) | The line for an opponent using an item, '{X} השתמש ב{ITEM}!', uses the masculine verb for every trainer, so Rocket Admin Ariana reads… | A. No verb: '{X}: שימוש ב{ITEM}!' | changed |
| [Q125](#q125) | Lines that put a count before an item name print the singular for every item without a Hebrew plural name ('זרקת 3 שיקוי.', 'לזרוק כמה נוצת שרירים?')… | A. A Hebrew plural for every stackable item, with the Pyramid bag and the put-away lines following | changed |
| [Q126](#q126) | The NORMAL contest rank has three names in one contest ('דרגה רגילה', 'בדרגת רגיל', 'דרגת בסיס'), and the MC's 'בדרגת רגיל' is not Hebrew. | A. 'נורמל', a rank name like סופר / היפר / מאסטר, wherever the rank is named | changed |
| [Q127](#q127) | The withdraw lines with a trainer or partner as the subject use the masculine 'החזיר' for every trainer, so women and pairs read as masc… | A. Reword so the verb agrees with the Pokémon: 'הפוקימון של X, Y, חוזר!' | changed |
| [Q128](#q128) | Summary screen: a geresh or quote mark in the portrait nickname (ג'ימי, טיפלוז'ן) touches the bottom of the portrait box. | D. Lowered copies of the four quote marks, used only by that window | changed |
| [Q129](#q129) | EXEGGUTOR-A is אקזגיוטר-א, without the ק of its base form אקזגקיוטר, because the base plus -א was measured at 56 px against the 50 px Pokédex list column. | B. The full form אקזגקיוטר-א, with the TEXT_RTL fits, a Pokédex CRY page fit and one PC panel fallback | changed |
| [Q130](#q130) | The battle intro attaches מ to the trainer class, and 'ממלכת השביל', 'מאס הכיפה', 'משומר פוקימון' read as other words. | A. 'קיבלת אתגר מאת' before the class | changed |
| [Q131](#q131) | The battle debug menu shows three stat-up hold effects as 'העלאת X' and six as 'X +', and its 'switching to' label leaves a gap before the Pokémon it names. | A. 'X +' for all nine, and the 68 px label 'עובר לפוקימון ' | changed |
| [Q132](#q132) | The link battle lines for the other player or the link partner sending out or withdrawing a Pokémon, and running, use the masculine verb whatever character that player chose. | A. Reword so the verb agrees with the Pokémon, as Q123 and Q127 did | changed |
| [Q133](#q133) | Five Pokédex terms have Hebrew names with no official source: HISUI היסואי, MT. CORONET הר הנזר, Ultra Wormhole חור תולעת אולטרה, TEAM PLASMA צוות פלזמה, ROSE רוז. | A. Keep all five | no change |
| [Q134](#q134) | 'psychic power' in Pokédex prose is כוח פסיכי in most entries and כוח על-חושי in nine. | A. כוח פסיכי and its forms in every entry; על-חושי stays in Kadabra's 'extrasensory' and in the move names that have it | changed |
| [Q135](#q135) | 482 of the 999 Easy Chat words were still English, so trainer phrases mixed the two directions, and three Odd Egg hints named words the list no longer has. | a. Translate every word, a text of its own for every word the game compares and shared texts only where Hebrew has one word, Hebrew order for the group lists, hints that quote the list words, a Hebrew ABC keyboard and the screen mirrored inside its frames | changed |
| [Q137](#q137) | In the Gen 4 battle interface the frostbite tag is a copy of the burn tag and reads כויה, as in English. | B. Redraw it as קור, the word of the H&S sheets | changed |

## K1

**Question.** Battle text after את: the wild/opposing suffix is indefinite (טירניטר פראי), so lines such as Intimidate read 'את התקפת טירניטר פראי'. The definite form (הפראי / היריב) would touch 77 strings; it is a style decision left open.

*Source:* TESTING.md known issue

**Analysis.** Still open in the current tree (he/main @95c35506a0). I checked every claim. Most hold, but the edit list is missing one string.

CORRECTION:
- STRINGID_WILDPKMNFLED (src/battle_message.c:395) is "{PLAY_SE SE_FLEE}{B_BUFF1} פראי ברח!". It carries a literal indefinite פראי after a plain nickname buffer: PREPARE_MON_NICK_BUFFER at src/battle_main.c:5795, printed by BattleScript_WildMonFled in data/battle_scripts_1.s:4333-4334.
- The English (pokehns-heb-engine src/battle_message.c:395) is "The wild {B_BUFF1} fled!", which is definite. FireRed's identical "{B_BUFF1} פראי ברח!" (pokefirered-heb src/battle_message.c:326) mirrored FireRed's article-less "Wild {B_BUFF1} fled!".
- With option C, every other battle line would say "X הפראי" and only the flee line would say "X פראי". So "none of the 489 strings needs rewording" is wrong by one, and C needs a fifth edit.
- No other English string pairs a definite "the wild/the opposing" with a bare name placeholder. A grep of src, data/*.s and data/text finds only :395. Lines :91-96 ("a wild X", "Wild X appeared!") and the overworld match-call/apprentice "{STR_VAR_3} פראי" lines are indefinite in English and stay as they are.

VERIFIED:
- Suffix strings and switch:
  - src/battle_message.c:133-136 are " פראי", " יריב", " פראי", " יריב".
  - The English (:133-136) is "The wild ", "The opposing ", "the wild ", "the opposing ".
  - TEXT_NAME_SUFFIX_IN_BATTLE is TRUE (include/config/text.h:28).
- Code paths:
  - Placeholder expansion: HANDLE_NICKNAME_WITH_SUFFIX (:2927-2948), used at :3273-3290 and :3737-3746.
  - B_TXT_26 (:3456-3472).
  - B_BUFF_MON_NICK_WITH_PREFIX(_LOWER) (:3853-3879).
- Buffer users:
  - Trace, the only LOWER user: battle_util.c:3130.
  - Beat Up: battle_script_commands.c:3654.
  - Wish: battle_end_turn.c:270.
  - PreventsSwitching: pokemon.c:8357/8366.
  - Also: exp at battle_script_commands.c:4349/4403 (player side, so never suffixed) and Instruct at :14393 (it fills BUFF1, but STRINGID_USEDINSTRUCTEDMOVE :670 does not print it). Neither changes the result.
- Placeholder counts: 78 PREFIX2 and 411 PREFIX.
- Grammatical positions:
  - 16 direct objects after את: :220 230 233 238 287 293 322 598 608 611 681 748 769 788 838 862.
  - 3 construct possessors after את: :352 יכולת, :377 התקפת (Intimidate), :670 הוראת.
  - Joined prepositions: ב 6, ל 29, מ 10, ש 1, all combined.
  - No string has a literal ה before a name placeholder, and no Hebrew letter follows one directly.
- The rc3 finding (hns-tools/release/rc3/visual_findings.json, shot battle_effects_intro_05) confirms the Intimidate line "את התקפת טירניטר פראי".
- FireRed precedent:
  - FireRed has the same error. 5 strings put "את {X_NAME_WITH_PREFIX}" before the indefinite suffix (pokefirered-heb src/battle_message.c:84-105).
  - Its indefinite form was faithful to its own article-less English, so it is precedent only for an English source without the article. H&S's English source has it.
- Widths (textwidth, FONT_NORMAL):
  - " פראי" 26 -> " הפראי" 33.
  - " יריב" 22 -> " היריב" 29.
  - The worst-case name with suffix goes from 110 to 117 px (TextModel with symtree on the edited copy).
  - :395 goes from 137 to 144 of 208 px.
- Audit: I applied all five edits to a scratch copy and ran audit.py --tree <copy> src/battle_message.c, with the sym: lookup reading the new suffix. Result: 0 findings, the same as the current tree.
  - Control run: --subst B_ATK_NAME_WITH_PREFIX2=W40 produces 18 WIDTH errors, so the substitution path does take effect.
- Tests:
  - test/hebrew_battle_messages.h and testmsgs composed.json/table.json do not contain the suffix. Their היריב comes from team strings ("הקבוצה של היריב").
  - No test or tour expects the wild-flee message.
  - The standalone sText_FoePkmnPrefix2/3/4 "יריב" (B_*_PREFIX1/2/3) are referenced by no string and are out of scope.

| Option | How | Risk |
|---|---|---|
| A. Keep the indefinite " פראי"/" יריב" (status quo, the FireRed form) | Close K1 as accepted style. | No cost, but it leaves 19 ungrammatical את lines (Intimidate is shown in battle_effects). The Imposter line :629 changes meaning, and subject lines read as "A wild X used…" against a definite English source. |
| B. Make only the Lower pair definite (:135-136) | Two edits that cover the 78 PREFIX2 placeholders and Trace. | Fixes את, but one battler becomes "X פראי" in one line and "X הפראי" in the next. The split follows English capitalization, not Hebrew grammar (for example "אבל {X2} לא יכול…" against "{X} לא יכול…"). |
| C. Make all four suffix strings definite (" הפראי"/" היריב") and the literal in STRINGID_WILDPKMNFLED :395 ("{B_BUFF1} הפראי ברח!") | Five Hebrew-only literal edits in src/battle_message.c, plus doc updates. No code, label, flag or script change. | +7 px and +1 byte per name. Measured: 0 audit findings, the widest line at 117 px, :395 at 144/208, and no test expectation changes. It departs deliberately from FireRed, whose source had no article. |
| C without :395 (the decision as submitted) | Only the four suffix strings. | Every wild-flee message (BattleScript_WildMonFled) keeps the indefinite "X פראי ברח!" right after the battle called the same Pokémon "X הפראי". It is inconsistent and does not match the English "The wild X fled!". |
| D. Foe suffix " של היריב" (possessive) instead of " היריב" | Mirrors the team strings ("הקבוצה של היריב"). | Produces a double של in 31 של-contexts ("ההתקפה של פידג'י של היריב") and a clumsy construct ("התקפת פידג'י של היריב"). It costs about +16 px more, and wild battles have no parallel form. Worse than the apposition היריב. |
| E. Reword the 19 את strings, or add a per-position suffix in the engine | Rewrite the strings around the indefinite form, or add a new placeholder or flag in BattleStringExpandPlaceholders. | Many rewrites or a code change. Either leaves the subject lines, :629 and :395 inconsistent, and the engine variant gains nothing over C, since the definite form is correct in every position. |

**Chosen:** C, completed: make all four suffix strings definite (" הפראי" for wild, " היריב" for opposing), and change the literal in STRINGID_WILDPKMNFLED (:395) to "{B_BUFF1} הפראי ברח!". The encounter intros (:91-96) stay indefinite.. The definite form is correct Hebrew in every position the placeholders take: subject, את object, construct possessor, joined and separate prepositions, and relative clause. With a name, the adjective must take ה. It fixes all 19 את lines and the Imposter meaning in one place.

It also translates H&S faithfully, since the English says "The wild / the opposing" in both the capitalized and lower-case variants and "The wild X fled!". FireRed's indefinite form mirrored FireRed's article-less "Wild/Foe", so it is not a precedent here.

The :395 edit is required for completeness. Without it, the one message that ends many wild battles would revert to the indefinite form right after the battle used the definite one. The first-mention intros keep "פראי", as the English "a wild X" / "Wild X appeared!" does.

The risk is minimal: 5 string literals and no code, label, flag or script change. All 5 are audited on a scratch copy with 0 findings and at least 91 px to spare on the widest line, and no test expectation changes. Option B splits one battler into two forms. Option D ("של היריב") stacks של.

*Changed:* `docs/hebrew_translation.md`, `src/battle_message.c`, `translation/hebrew/STYLE.md`

*Glossary:* `TERM_BATTLE_SUFFIX_WILD`, `TERM_BATTLE_SUFFIX_OPPOSING`, `TERM_WILD_ENCOUNTER`

## K2

**Question.** The trainer ID label is the Latin glyph pair {ID}{NO} (IDNo) on the summary and trainer card, a style decision left open.

*Source:* TESTING.md known issue

**Analysis.** Confirmed in the current tree (he/main 95c35506a0), and only the summary screen is still affected. The trainer card is already Hebrew: src/strings.c:756 gText_TrainerCardIDNo = "מס' זיהוי ". The Hall of Fame is also Hebrew: gText_IDNumber, strings.c:133. src/strings.c:157 gText_IDNumber2 = "{ID}{NO}" has three uses, src/pokemon_summary_screen.c:3848 (PrintMonOTID) and :4015/:4017 (PrintEggOTID), and no other source references it. The renderer classes {ID}/{NO} as strong LTR (src/text.c:1105-1108). That is why PrintEggOTID has a TEXT_RTL block at :4011-4019 that prints the marks before the label. The ID window PSS_DATA_WINDOW_INFO_ID is 7 tiles = 56 px (:640-652), right-aligned with GetStringRightAlignXOffset(...,56). Widths in FONT_NORMAL, re-measured: "{ID}{NO}23773" 48, "מס' 23773" 50, "מס' 00000" 50, "מס' ?????" 50, "ת.ז. 23773" 51, "זיהוי 23773" 54, "מס' זיהוי 23773" 74 (too wide). The OTID is always printed as 5 digits with leading zeros, so 50 px is the maximum. FireRed gives no precedent for this string: pokefirered-heb src/strings.c:157 also keeps "{ID}{NO}" but nothing there references it. Its trainer card uses "מס' זיהוי " (:855) and its Hall of Fame uses "מספר מזהה" (:113). Out of scope: gText_NumberClear01 (the dex-number numero sign), which is shared with both dex files.

| Option | How | Risk |
|---|---|---|
| A. Keep {ID}{NO} | No change; record it as a deliberate glyph. | None technically. It stays the last Latin label on the summary info page, and it differs from "מס' זיהוי" on the trainer card and in the Hall of Fame. |
| B. Hebrew short form "מס' " | gText_IDNumber2 = "מס' " (50 px with 5 digits or marks; fits 56). Under TEXT_RTL, PrintEggOTID returns to label-then-marks. With a Hebrew label, the trailing neutral marks are drawn to its left, where a hatched Pokémon's digits sit. | Low: one string, plus removing a 9-line #if/#else/#endif block. It is the same abbreviation the trainer card and Hall of Fame use. |
| C. "ת.ז. " | gText_IDNumber2 = "ת.ז. " (51 px), plus the same PrintEggOTID change. | Fits, but ת.ז. is a citizen's identity card, the wrong register for a trainer number, and appears nowhere else in the game. |
| D. "זיהוי " | gText_IDNumber2 = "זיהוי " (54 px), plus the same PrintEggOTID change. | Only 2 px to spare, and "identification 23773" reads less naturally as a number label than מס'. |
| E. Redraw the ID/NO glyphs as Hebrew art | Redraw glyphs 0x107/0x108 in every font and reclass them as RTL in RtlClassAt. | High: {NO} is also the numero sign in dex numbers, bag TM/berry rows, DexNav and berry tags, so all of those would change. |

**Chosen:** B. To a Hebrew player, "מס'" next to a number is the natural label. It is the abbreviation the trainer card and Hall of Fame already use ("מס' זיהוי"), and it fits the 56 px slot with 6 px to spare. It changes one string and removes a workaround instead of adding code. FireRed has no competing precedent because it never uses this string.

*Changed:* `src/strings.c`

*Glossary:* `TERM_ID_NO_SHORT`

## K3

**Question.** POKéGEAR is written in Latin letters in dialogue and menus, consistently; the glossary has no Hebrew form.

*Source:* TESTING.md known issue

**Analysis.** Partly resolved since TESTING.md was written, and now inconsistent. The start menu says פוקיגיר: src/strings.c:1030 gText_MenuPokenav (IS_HNS branch). The glossary already has name,NAME_POKÉGEAR,...,פוקיגיר,proposed (glossary.csv:6472). Dialogue still says POKéGEAR. A scan of data/src/include for lines with Hebrew letters and Latin POKéGEAR/POKéNAV finds 25 lines. The 17 HnS dialogue lines are listed in the edits; each old substring occurs exactly once on its stated line. Two more are Pokégear menu descriptions (src/pokenav_menu_handler_gfx.c:351-352). Two are Battle Pike mentions that upstream HnS English left as POKéNAV (BattleFrontier_BattlePikeLobby_hns:418, used at :251; src/data/script_menu.h:720 MultichoiceList_BattlePikeRules, used by MULTI_BATTLE_PIKE_RULES at Pike lobby _hns:241). The Pike is reachable through BattleFrontier_OutsideWest_hns/map.json:629. The remaining four are out of scope. event_scripts.s:1550 is the #else (Emerald) branch. match_call.inc:2623/2699/2841 (Wally6, Scott7, MrStone1) are compiled into the HnS match-call table, but their enable flags FLAG_ENABLE_NORMAN/WALLY/SCOTT_MATCH_CALL are set only in Emerald maps (Route104:377, MauvilleCity:457, SlateportCity:75), so they cannot be reached. src/strings.c:560 gText_MenuOptionPokenav (IS_HNS) is still Latin "POKéGEAR". It is drawn by CreateStartMenuForPokenavTutorial (script_menu.c:1205). The Latin lines left in HnS maps are unreferenced: RadioTower1F_Text_GotRadio, GoldenrodCity_Text_CooltrainerF2_GotCard and RuinsOfAlph_Lab IMadePokenav/WowThatsAPokenav/DevelopNewPokenavFeature. Precedent: the tree writes the sister terms in Hebrew, פוקדקס and פוקיבול. STYLE.md §4 says to attach prefixes rather than hyphenate, and §5 says the {POKE} token is written פוקי. Hebrew גיר is also the everyday word for a gearbox, so the reading is natural.

| Option | How | Risk |
|---|---|---|
| A. Latin everywhere | Revert gText_MenuPokenav to "POKéGEAR" and treat the name as a brand. | Keeps Latin inside 17 Hebrew sentences with hyphenated prefixes (ב-, ה-, ל-), unlike פוקדקס and פוקיבול. |
| B. פוקיגיר everywhere text is drawn | Replace POKéGEAR with פוקיגיר in the 17 dialogue lines, the 2 menu descriptions and gText_MenuOptionPokenav, with prefixes attached directly. Also write פוקיגיר in the 2 HnS Battle Pike lines, because the player carries a Pokégear, not a PokéNav. Keep the header logo art. | Low. Every line gets narrower: by 21 px where a hyphenated prefix is dropped, by 15 px elsewhere. No tokens, labels or logic change. |
| C. פוקגיר (by analogy with פוקדקס) | The same edits with פוקגיר. | Contradicts the glossary row and the start menu, which already ship פוקיגיר. The rules give POKé as פוקי (פוקיבול); פוקדקס is FireRed's exception. |
| D. A descriptive Hebrew noun | Translate the meaning instead of the name. | Loses the device's name, lengthens lines, and has no precedent. |

**Chosen:** B. It matches what the player already sees in the start menu and the glossary, and the house style for POKé names. It removes hyphenated Latin from 21 strings, and every line gets narrower. The header art stays as a logo, the way the POKéDEX logo was kept.

*Changed:* `data/event_scripts.s`, `data/maps/BattleFrontier_BattlePikeLobby_hns/scripts.inc`, `data/maps/CherrygroveCity_hns/scripts.inc`, `data/maps/GoldenrodCity_DepartmentStore_2F_hns/scripts.inc`, `data/maps/GoldenrodCity_RadioTower_1F_hns/scripts.inc`, `data/maps/NewBarkTown_Lab_hns/scripts.inc`, `data/maps/NewBarkTown_PlayersHouse_1F_hns/scripts.inc`, `data/maps/NewBarkTown_hns/scripts.inc`, `data/maps/OlivineCity_hns/scripts.inc`, `data/maps/Route27_hns/scripts.inc`, `data/maps/Route39_hns/scripts.inc`, `data/maps/SinjohRuins_House1_hns/scripts.inc`, `data/maps/VermilionCity_hns/scripts.inc`, `src/data/script_menu.h`, `src/pokenav_menu_handler_gfx.c`, `src/strings.c`

*Glossary:* `NAME_POKÉGEAR`

## K4

**Question.** Naming screen: switching to the Hebrew page keeps the cursor column, so the cursor does not start on א.

*Source:* TESTING.md known issue

**Analysis.** Confirmed still open. src/naming_screen.c:835-866 MainState_WaitPageSwap has no TEXT_RTL handling. It keeps cursorX, clamps it to the new page's column count, and handles the button column separately (onLastColumn). The page order is KBPAGE_SYMBOLS=0, LETTERS_UPPER=1, LETTERS_LOWER=2 (:92-96), and currentPage++ mod 3 cycles UPPER -> LOWER -> SYMBOLS -> UPPER. In the Hebrew build KEYBOARD_HEBREW is KEYBOARD_LETTERS_UPPER and KEYBOARD_LATIN is LETTERS_LOWER (:348-349). The Hebrew page is laid out right to left with א in column 7 (sHebrewKeyboardChars :356-361; mirrored x positions sHebrewColumnXPos :364). The Latin page has A in column 0 (:319-324), and the symbols page has 6 columns (sPageColumnCounts :332-336). The cursor starts on א only when the screen opens (CreateCursorSprite :1217-1219), and every template starts on KBPAGE_LETTERS_UPPER (:2583-2638; also :547). So a full SELECT cycle runs א(col 7) -> Latin '.'(7) -> symbols col 5 (clamped, an empty key) -> Hebrew col 5 = ג, which matches the rc3 battle_catch_naming_typed result.

| Option | How | Risk |
|---|---|---|
| A. Mirror the column when the swap crosses between the RTL page and an LTR page | Remember the old keyboard id. After currentPage++, if exactly one of old/new is KEYBOARD_HEBREW and the cursor is not on the button column, set cursorX = KBCOL_COUNT-1-cursorX, then apply the existing clamp. The cycle becomes א(7) -> A(0) -> 0(0) -> א(7), and matching keys line up (ב 6 <-> B 1; Hebrew '.' 0 <-> Latin '.' 7). | Low: about 6 lines under #if TEXT_RTL in one function. English is untouched; the row and the button column are kept. |
| B. Reset to the page's first key on every swap | Under TEXT_RTL, set (7,0) on the Hebrew page and (0,0) on the others unless onLastColumn. | Low code risk, but it discards the row and departs further from stock behaviour. |
| C. Leave it and document | No change. | Cycling pages lands on ג or an empty key, and the tour types the wrong letters. |

**Chosen:** A. It is the mirror image of the stock rule: column n means the n-th key from the reading start on every page. A full cycle returns to א, and the change is small and confined to TEXT_RTL.

## K5

**Question.** Cosmetic: the fainted tag fills its pill edge to edge; the descender of ק in a summary nickname touches the frame; the unknown height and weight placeholders show the unit before the question marks; the Pokédex list stat panel keeps the English left-to-right layout (the labels are Hebrew).

*Source:* TESTING.md known issue

**Analysis.** All four items are still open. (1) Fainted tag. In graphics/interface/status_icons.png, icon 6 (rows 48-55) מעולף has ink from x6 (final pe, rows 50-51) to x24, while the pill interior is x6-25. The left end therefore looks notched. FireRed's untranslated FNT (pokefirered-heb graphics/summary_screen/status_ailment_icons.png rows 48-55) keeps x6-8 and x24-25 clear. The tag is generated by hns-tools/scratch/graphics/coreui/tools/make_coreui.py status_tags() (TAGS_ICONS, job status_icons.png). Icon 1 שיתוק also inks x25 (rows 10-13), but the issue does not name it. Moving it left would drop the qof descender's bottom pixel on the corner at (7,15), so it is left as is. (2) Summary nickname. PSS_LABEL_WINDOW_PORTRAIT_NICKNAME (src/pokemon_summary_screen.c:603-611: L1 T12 W9 H2, base 413) prints at y=1 (:3543; egg :3559), so the glyph origin is y97. Normal-font Hebrew has its body on rows 4-11, the ל ascender at row 2, and descenders to row 13 with the shadow on row 14 (hns-tools/notes/fonts_done.md). The ק ך ן ף ץ descenders therefore land at y109-110 and the shadow at y111. y is u8 and already 1. The BG0 char base is 0 and BG1-3 use char base 2 (sBgTemplates :354-386). Of the 32 window templates, the largest end is MOVE_DESCRIPTION 617+80=697, and PROMPT_RELEARN sits at 800, so tiles 697-799 are free. No BG0 window uses tile row 11, columns 1-9. The window is cleared with PIXEL_FILL(0) (:3479), so an extra row is transparent. (3) Unknown height and weight. src/strings.c:49-52 holds "{CLEAR_TO 0x0C}??'??”", "???.? m", "????.? lbs" and "???.? kg". '?', '.', ''' and '”' are neutral (sRtlCharClass, text.c:1024-1042), and only m/kg/lbs start an LTR run (RtlStartsRun :1120, RtlBeginRun :1186). The measurements go to window 0 through pokedex.c PrintInfoScreenText, called from pokedex_plus_hgss.c:4729, and that window is mirrored, not in place. Each neutral is therefore drawn at axis-x-w and the unit lands at the far left: "m ?.???", "”??'??". The renderer keeps the logical pen, so {CLEAR_TO} keeps its English meaning (text.c:993-996). Known metric values render "0.5 m". (4) Dex list stat panel. Since df3596f377, stat_bars.png has the Hebrew labels right-aligned at x0-18 with their shadows. CreateStatBar draws the bars from STAT_BAR_X_OFFSET 19, scaled to end at x48 (pokedex_plus_hgss.c:3716-3779). There are 15 WritePixel x terms, and the raw width is capped at 39 (:3838-3839), so the drawn width is at most 30. The panel reads left to right while the dex stats page is mirrored.

| Option | How | Risk |
|---|---|---|
| A. Accept all four as cosmetic | Keep TESTING.md as is. | None, but four visible blemishes stay on common screens. |
| B. Fix each at its source, under TEXT_RTL or in Hebrew assets | (1) Redraw מעולף 2 px narrower (3-px ayin/mem) at x7-23. (2) Move the nickname window up one tile row (height 3) at a free baseBlock and print 2 px higher. (3) Reorder the placeholders' neutrals so the unit forms the run at the right end. (4) Mirror the stat panel: labels flush right, bars growing leftwards. | Low to moderate: one generator override, about 10 lines of summary code, 4 strings, and a graphic plus about 8 lines in CreateStatBar. All are isolated from English, save data and logic. |
| C. Minimal partial fixes | (2) print at y=0 only (1 px; one white row stays on the frame), (4) keep the LTR panel, (1) and (3) as in B. | Least code, but item 2 is only half fixed and item 4 stays inconsistent with the stats page. |

**Chosen:** B. Each fix is local and reversible, and sits in Hebrew-only assets or behind TEXT_RTL. Each makes its screen match the English layout and its Hebrew neighbours: the pill margins match FNT, the unknown measures match the known "0.5 m", and the panel matches the mirrored stats page. The nickname fix uses free VRAM instead of fighting the u8 y. The PAR tag change is dropped from the plan: it is outside the issue and only swaps a shin pixel for a qof descender pixel.

*Changed:* `src/strings.c`

*Glossary:* `TERM_STATUS_FAINTED_TAG`

## K6

**Question.** Berry names come from the FireRed fork and mix the words גרגר, פרי, פירות and תות, as FireRed does; CHESTO is צ'סטרו there too.

*Source:* TESTING.md known issue

**Analysis.** Confirmed still open in src/data/items.h. Of the 68 berry .name heads (10913-12157), 36 use פרי, 22 תות, 6 פירות and 4 גרגר. Of the plural heads, 42 use פירות, 22 תותי and 4 גרגרי. The 6 פירות items use a plural as the singular name (for example 10995-10996). ITEM_UNUSED_BERRY_1 (16318) is also "פירות סיטרוס". Everything else already says פרי: gText_Var1Berry "פרי {STR_VAR_1}" (strings.c:855), gText_Berry (:1261), battle sText_BerrySuffix (battle_message.c:183), TERM_BERRY = פרי (glossary.csv:5535, which logs FireRed's mix) and the dialogue (כיס הפירות). CHESTO is צ'סטרו at items.h:10935-10936, berry.c:90 (stem, 6-byte limit) and strings.c:1292 gText_Moon. Glossary :4701 already calls this a FireRed slip and asks to fix the item and stem together. A stem mismatch check of berry.c against items.h finds one more case. IAPAPA's tag stem is יאפאפה (berry.c:389), shortened because יאיפאפה is 7 bytes, but the item is "תות יאיפאפה". Glossary :4548/:4714 says the dropped second yod is silent and asks to align the item if it is renamed. Singular dialogue with an item word: Route14_hns:401 "מתות קואלות" (English: the QUALOT BERRY). IcePath_B3F_hns:154/163 "מפירות אספר" (the ASPEAR BERRY). Route39_Barn_hns:154/160/175 "פירות אורן" (an ORAN BERRY, checked against pokehns-heb-engine). The plurals at Route39_Barn :144/:172 and Route35_hns:164 are correct and stay. challenge_menu.c:382/383/451 "פירות סיטרוס" is a plural topic heading and generic statements, so it stays. A scan finds no other old heads in Hebrew text outside items.h.

| Option | How | Risk |
|---|---|---|
| A. Keep FireRed's mixed heads (canon) | No change; document. | Four nouns for one item class in one pocket. פירות as a singular is ungrammatical, and תות means strawberry. |
| B. Unify to פרי / פירות, and fix the CHESTO and IAPAPA stems | Every .name becomes "פרי <stem>" and every .pluralName "פירות <stem>" (32 items plus the unused duplicate). Chesto becomes צ'סטו in items.h, berry.c and gText_Moon. The IAPAPA item takes the tag's stem, יאפאפה. The 6 singular dialogue lines follow. | Low. Labels, constants and berry data do not change. This deliberately overrides FireRed item names (rules §0), justified by FireRed contradicting itself (logged in §7). |
| C. Unify to גרגר / גרגרי | Use the botanical word in all 68 items. | Contradicts the code-built strings, battle suffix, glossary term and dialogue, which all say פרי/פירות; also wider and 36 more edits. |

**Chosen:** B. פרי/פירות is the majority head (36 items). It is what the code, battle text, dialogue and TERM_BERRY already use, it is correct Hebrew in both numbers, and it is the narrowest singular head. CHESTO and IAPAPA are fixed in the same pass because those items are being renamed anyway, and the glossary itself asks for both. After the change the bag name matches the berry tag and the berry-crush and blender names built from the stem.

*Changed:* `data/maps/IcePath_B3F_hns/scripts.inc`, `data/maps/Route14_hns/scripts.inc`, `data/maps/Route39_Barn_hns/scripts.inc`, `src/berry.c`, `src/data/items.h`, `src/strings.c`

*Glossary:* `TERM_BERRY`, `ITEM_CHESTO_BERRY`, `ITEM_CHERI_BERRY`, `ITEM_CHERI_BERRY`, `ITEM_CHESTO_BERRY`, `ITEM_CHESTO_BERRY`, `ITEM_PECHA_BERRY`, `ITEM_PECHA_BERRY`, `ITEM_RAWST_BERRY`, `ITEM_RAWST_BERRY`, `ITEM_ASPEAR_BERRY`, `ITEM_LEPPA_BERRY`, `ITEM_ORAN_BERRY`, `ITEM_PERSIM_BERRY`, `ITEM_LUM_BERRY`, `ITEM_SITRUS_BERRY`, `ITEM_FIGY_BERRY`, `ITEM_FIGY_BERRY`, `ITEM_WIKI_BERRY`, `ITEM_WIKI_BERRY`, `ITEM_MAGO_BERRY`, `ITEM_MAGO_BERRY`, `ITEM_AGUAV_BERRY`, `ITEM_AGUAV_BERRY`, `ITEM_IAPAPA_BERRY`, `ITEM_IAPAPA_BERRY`, `ITEM_RAZZ_BERRY`, `ITEM_RAZZ_BERRY`, `ITEM_BLUK_BERRY`, `ITEM_BLUK_BERRY`, `ITEM_NANAB_BERRY`, `ITEM_NANAB_BERRY`, `ITEM_WEPEAR_BERRY`, `ITEM_WEPEAR_BERRY`, `ITEM_PINAP_BERRY`, `ITEM_PINAP_BERRY`, `ITEM_POMEG_BERRY`, `ITEM_POMEG_BERRY`, `ITEM_KELPSY_BERRY`, `ITEM_KELPSY_BERRY`, `ITEM_QUALOT_BERRY`, `ITEM_QUALOT_BERRY`, `ITEM_HONDEW_BERRY`, `ITEM_HONDEW_BERRY`, `ITEM_GREPA_BERRY`, `ITEM_GREPA_BERRY`, `ITEM_TAMATO_BERRY`, `ITEM_TAMATO_BERRY`, `ITEM_CORNN_BERRY`, `ITEM_CORNN_BERRY`, `ITEM_MAGOST_BERRY`, `ITEM_MAGOST_BERRY`, `ITEM_RABUTA_BERRY`, `ITEM_RABUTA_BERRY`, `ITEM_NOMEL_BERRY`, `ITEM_NOMEL_BERRY`, `ITEM_SPELON_BERRY`, `ITEM_SPELON_BERRY`, `ITEM_PAMTRE_BERRY`, `ITEM_PAMTRE_BERRY`

## Q2

**Question.** STRUGGLE in prose is written without quotation marks ('להשתמש במאבק'), following B30_01. Should move names in running dialogue get ”…” to set them apart from the common noun (here מאבק = 'a struggle')? STYLE.md does not settle this

*Source:* reviewer question (chunk B34_03)

**Analysis.** Settled in practice for dialogue, but STYLE.md does not say so, and the proposed bullet as drafted would contradict the C description strings. Dialogue: move names are bare. HintPPWaste_hns has '…ונאלצים להשתמש במאבק…' (BattleFrontier_BattlePyramidLobby_hns/scripts.inc:737, 185 px; English :748 'but to use STRUGGLE…'). Falkner's TM line is now bare: 'המ”מ הזה מכיל את מנוחת כנף.' (VioletCity_Gym_hns/scripts.inc:87). A scan of every ”…” in data/ against the glossary move names finds only two quoted moves in map scripts, and the English quotes both: Route31_hns:171 'התקצר ל”מנוחה”' (English :172 'shortened to 'Rest,''), where the word itself is being explained, and BattlePyramidLobby_hns:558 'ב”מנוחה”' (English :560 'select “REST”'), a menu option. NewBarkTown_Lab_hns:972 '”שמירה”' is the SAVE option, not a move. FireRed writes moves bare in dialogue: CeruleanCity_House1/text.inc:47 'גלישה', OneIsland_KindleRoad:42 'להשתמש בגלישה', SSAnne_3F_Corridor:3 'בחיתוך'. Correction: system and description text does the opposite. At least 36 C strings quote a move name that the English writes in capitals without quotes: src/challenge_menu.c:378 '”גיליוטינה”', :418 'מהלכי טעינה כמו ”קרן על”', :645, :1018-1019; src/data/moves_info.h:111 and :20643 '”הגנה”'; 25 Z-crystal and terrain-item descriptions in src/data/items.h (7937-8206, 9356-9518); and 3 Pokédex entries. A bullet that says 'quote only where the English quotes the word', with no scope, would tell a later batch to strip those quotes or to quote inconsistently. The bullet must say which kind of text it covers.

| Option | How | Risk |
|---|---|---|
| (a) Bare in dialogue, as now. Write the rule into STYLE.md §3, scoped to dialogue, and record that descriptions and menus keep their quotes | No game text changes. Add one bullet to STYLE.md §3. | None. Context makes מאבק read as the move. The bullet only records what the tree already does. |
| (a') Same rule, but the bullet is unscoped ('quote only where the English quotes') | No game text changes. Add the bullet as first drafted. | It contradicts the 36+ quoted move names in the C descriptions and invites churn or drift in later batches |
| (b) Always quote move names | Add ”…” around every move name in dialogue (hundreds of lines) | Large churn, goes against FireRed, and adds width |
| (c) Add the classifier, FireRed-style: 'במהלך מאבק' | Change line 737 to '…להשתמש במהלך מאבק…' | 214 px, over the 208 limit, and 'במהלך' also reads as 'during' |

**Chosen:** (a). Bare move names in dialogue match the FireRed canon and the whole tree, and cost nothing. The classifier option overflows and is ambiguous. Scoping the bullet keeps STYLE.md consistent with the description and menu strings, which already quote a move cited in a sentence (Hebrew has no capitals to mark the name there).

*Changed:* `translation/hebrew/STYLE.md`

## Q5

**Question.** Brandon's nickname 'the chief' is rendered as 'הבוס', used the same way in both the attendant's and Brandon's lines. 'הצ'יף' and 'המפקד' are alternatives. This is a style call.

*Source:* reviewer question (chunk B34_04)

**Analysis.** Brandon's nickname 'the chief' is 'הבוס' in all three places in the live map: BattleFrontier_BattlePyramidTop_hns/scripts.inc:234 'הבוס שלנו' and :238 'מהבוס שלנו' (the attendant, English :235/:240), and :259 'רוב האנשים קוראים לי הבוס!' (Brandon, English :260). It is consistent. The _hns chain is the live one: BattlePyramidFloor_hns:102 warps to MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_TOP_HNS. The non-hns copy of the map (scripts.inc:235/240/260) is still English and is reached only from the non-hns floor.

| Option | How | Risk |
|---|---|---|
| (a) Keep 'הבוס' | No change | None |
| (b) 'הצ'יף' | Replace in 3 lines | A loanword few Hebrew speakers use |
| (c) 'המפקד' | Replace in 3 lines | Sounds military, which is wrong for a jovial explorer |

**Chosen:** (a). 'הבוס' is how Hebrew speakers naturally say an informal 'the chief', and the attendant and Brandon already use it the same way.

## Q6

**Question.** Frontier lobbies here and in B33/B34 say 'ברכות!' for 'Congratulations!', while the rest of the game mostly uses 'מזל טוב!'. I kept 'ברכות!' to match the other Frontier lobbies; a project-wide choice may be wanted.

*Source:* reviewer question (chunk B34_04)

**Analysis.** Checked against the current tree (HEAD bb8db5c703; commits landed during this review but touched none of these lines). The engine has 52 live units whose English says 'Congratulations'. Their Hebrew:
- 'מזל טוב' in 34.
- bare 'ברכות' in 9.
- 'ברכותיי' in 4.
- 5 use another fitting phrase ('כל הכבוד', 'אנו מברכים אותך').
The 9 bare-'ברכות' units are all live staff or tent lines: BattleDomeLobby_hns:517 and :639, BattleFactoryLobby_hns:384 and :447, BattleTowerLobby_hns:948 and :1337, BattleDomePreBattleRoom_hns:367 and :375, and data/text/battle_tent.inc:309 (Slateport tent). The Frontier is already mixed: BattleDomeBattleRoom_hns has 8 'מזל טוב' (936-1176).
The Hall of Fame string src/strings.c:128 gText_LeagueChamp 'אלוף הליגה!\nברכות!' is printed in FONT_NORMAL in the dialogue frame (hall_of_fame.c:729, hall_of_fame_frlg.c:648) and is copied from FireRed (pokefirered-heb src/strings.c:109). H&S has already moved off FireRed's 'ברכות!' in two places: the evolution message (src/battle_message.c:1418; FireRed :1279) and the easy-chat word CONGRATS (easy_chat_group_greetings.h:58).
The 4 'ברכותיי' units are formal speakers: PikeLobby_hns:380, PikeRoomFinal_hns:38, TowerBattleRoom_hns:548 (Anabel), and PokemonLeague_HallOfFame_Frlg:58/:68 (Oak, one unit).

| Option | How | Risk |
|---|---|---|
| A: 'מזל טוב' for every 'Congratulations', the HoF screen included; keep 'ברכותיי' as a formal speaker's voice | Swap 'ברכות' for 'מזל טוב' in the 9 units and in gText_LeagueChamp, and add a glossary term row. | Low: 10 one-word swaps, the widest line 166 px. The HoF screen departs from FireRed, as the evolution message already does. |
| B: 'ברכות!' everywhere | Rewrite the 34 'מזל טוב' units. | High: 34+ edits, and a bare 'ברכות!' as an exclamation is stiff, unnatural Hebrew. |
| C: Leave it mixed as register (staff 'ברכות', everyone else 'מזל טוב') | No edits. | The Dome MC says 'מזל טוב' and the Dome lobby says 'ברכות' for the same event, and the reviewer's question stays open. |

**Chosen:** A. 'מזל טוב' is the natural Hebrew exclamation. It is already the majority (34 to 9), including the Frontier's own Dome battle room, the easy-chat word and the evolution message. 'ברכותיי' stays as character voice (Anabel, the Pike staff, Oak), as STYLE §1 asks. After the HoF change, a bare 'ברכות' never means 'Congratulations' anywhere in the game, which also settles Q101.

*Changed:* `data/maps/BattleFrontier_BattleDomeLobby_hns/scripts.inc`, `data/maps/BattleFrontier_BattleDomePreBattleRoom_hns/scripts.inc`, `data/maps/BattleFrontier_BattleFactoryLobby_hns/scripts.inc`, `data/maps/BattleFrontier_BattleTowerLobby_hns/scripts.inc`, `data/text/battle_tent.inc`, `src/strings.c`

*Glossary:* `TERM_CONGRATULATIONS`

## Q8

**Question.** The '{STR_VAR_1}-using {STR_VAR_2}' pattern (a move, then a species) has to keep the token order, so it is translated as 'אחד שמשתמש ב{STR_VAR_1} - {STR_VAR_2}' throughout. That is correct but stiff. Is it the house wording, or do you want another construction for every chunk?

*Source:* reviewer question (chunk B35_01)

**Analysis.** The live text is in data/maps/BattleFrontier_BattleTowerMultiPartnerRoom/scripts.inc: include/strings.h:985 and :1099 declare the non-_hns labels, and the _hns copies of these texts are not referenced from C. The English has 30 '-using' occurrences. The Hebrew uses 'ב{STR_VAR_1} - {STR_VAR_2}' on 31 lines (:397 … :1756). The lead-in varies naturally: 'אחד שמשתמש' / 'ועוד אחד שמשתמש' (for example :476-477, :480-481). STYLE §5 and drift.py's TOKENS check (order matters) require the move before the species. Width correction: 190 px is the model's default (both tokens at the W12 fill). With STR_VAR_1 filled at W16 the line measures 218 px, but that fill is not a real move. The widest Hebrew move in the glossary is 'להבת נשמה מצלצלת' (96 px) and the widest species is 'מיאוסקראדה' (60 px), which gives a real worst case of 178 px. That is under both 208 and the 200 limit of the '.\p' lines (:481 etc.).

| Option | How | Risk |
|---|---|---|
| (a) Keep as the house wording | No change | Slightly formal, but clear |
| (b) 'אחד עם {STR_VAR_1}: {STR_VAR_2}' | Rewrite 30 units | 218 px at the default fill, over budget, and vaguer |
| (c) 'מומחה {STR_VAR_1}: {STR_VAR_2}' | Rewrite 30 units | Changes the meaning (an 'expert' rather than one that uses the move) |
| (d) '{STR_VAR_2} עם {STR_VAR_1}' | Swap the tokens | Breaks STYLE §5 token order, and drift.py fails |

**Chosen:** (a). It is the only natural construction that keeps the required token order and fits with real names. It is already used consistently across all the units.

## Q9

**Question.** The apprentices' mentor ({STR_VAR_3} in the Mon messages) is another player's name and may be female. Most units avoid gender with 'בעצת / בהמלצת', but Apprentice10Mon1 says 'המנטור שלי, {STR_VAR_3}, המליץ' in the masculine. I left it because the player is masculine by default. Should mentor references be gender-neutral everywhere?

*Source:* reviewer question (chunk B35_01)

**Analysis.** {STR_VAR_3} in the Mon1 lines is the apprentice record's playerName (src/battle_tower.c:1461). For the player's own former apprentice, that is the player's name (src/apprentice.c:1174 StringCopy(apprentices[0].playerName, gSaveBlock2Ptr->playerName)). The record stores no gender (include/global.h:430-444). Without record mixing the mentor is always the player, who is masculine by the settled rule (STYLE §2), and apprentice.inc already calls the player 'המנטור שלי' (:1324, :1614; 10 uses of מנטור, e.g. :407 'אתה המנטור שלי'). Only Apprentice10Mon1 is gendered ('המנטור שלי, {STR_VAR_3},\nהמליץ על הצוות הזה:', MultiPartnerRoom:579-580). The other Mon1 lines use בעצת / בהמלצת / לפי.

| Option | How | Risk |
|---|---|---|
| (a) Keep the masculine | No change | A female mentor from a record-mixed save reads as masculine, the same as everywhere the player is addressed |
| (b) 'בהמלצת המנטור שלי, {STR_VAR_3},' | Rewrap 579-582 | The noun is still masculine, so little is gained |
| (c) Drop 'mentor': 'בהמלצת {STR_VAR_3}' | Rewrap | Drops this apprentice's 'my mentor' voice |

**Chosen:** (a). In practice the mentor is the player, and the player is masculine by a decision that is not to be reopened. Hebrew has no neutral noun for 'mentor', and dropping the word loses information.

## Q11

**Question.** Sound words are a style call: crying 'סניף…' / 'היק…' (taken from the FireRed fork), cough 'כחח', and the colloquial 'מחשבן' for 'calculating'. Please confirm or give house spellings.

*Source:* reviewer question (chunk B35_01)

**Analysis.** The coughing apprentice (apprentice.inc suffix 13, the same character as MultiPartnerRoom Apprentice14: 'אה, סליחה, אני מצונן' there, 'יש לי הצטננות' at apprentice.inc:1972) coughs 'כחח' in the MultiPartnerRoom (:687, :690, :709). In data/text/apprentice.inc the same English 'Cough!' is 'כח!' at :58 and :59 (gText_ApprenticeChallenge13, English :54-55) and twice at :544 (WhichLevelMode13, English :575), and 'אחח!' at :1983 (MoveThanks13, English :2093 'Cough!'). That is 5 occurrences, and 'כח' also reads as the old spelling of כוח. The 'Gahack! Gaah!' at :1971 ('אחח! קח-קח!', English :2082) is a different, hacking cough and stays. Neither FireRed nor the rest of the tree has another cough spelling. The other sound words are consistent: סניף (FireRed PokemonTower_1F/text.inc:18), היק, יבבה. 'מחשבן' (MultiPartnerRoom:596) is the standard colloquial word for a calculating person. Width correction: the widest result is :59 at 203/208 px, with STR_VAR_2 at the W12 default fill. STR_VAR_2 there is really the apprentice's number (ConvertIntToDecimalStringN, src/apprentice.c:131), so the real width is far lower. No move appears in these lines.

| Option | How | Risk |
|---|---|---|
| (a) Keep the other spellings and make the cough 'כחח' everywhere | Edit 4 lines in apprentice.inc (5 occurrences) | None. Widths: :58 170, :59 203 (worst-case fill), :544 57, :1983 174 px, all within 208 |
| (b) Leave the mix | No change | One character coughs 3 different ways, and 'כח' misreads as 'power' |

**Chosen:** (a). The same character gets one cough spelling, the 'כח' misreading goes away, and every line still fits.

*Changed:* `data/text/apprentice.inc`

## Q12

**Question.** Term for 'tag team': the glossary has no row for it, and each chunk uses a different word. B35_01 (same file, lines 339-1049) uses plain 'צוות'. This chunk uses 'צוות זוגי' (about 20 units), and B37_03 does too. B35_03 and B34_04 use 'צמד'. Players will see these in the same Battle Tower room, so a glossary decision is needed. 'צמד' is the most natural, but this chunk already uses 'הצמד' for 'twosome' (PsychicMMon1) and 'צמד הפוקימונים' for 'POKéMON pair' (SchoolKidFMon2Ask). 'Tag partner' is 'שותף לצוות' here.

*Source:* reviewer question (chunk B35_02)

**Analysis.** Verified against the current tree. 58 live units contain English 'tag team', 'tag-team', 'tag partner' or 'tag battle(s)'. Their Hebrew:
- 'צוות זוגי' in 21 units, e.g. BattleTowerMultiPartnerRoom:1082, 1103, 1144 and TrainerHill_Roof_hns:76, :107.
- bare 'צוות' for 'tag team' in 16 units, all in BattleTowerMultiPartnerRoom between 379 and 1060 (B35_01). This counts the rhyme at 647.
- 'צמד' in 7 units (8 lines; Q17).
- 'שותף/שותפה/שותפים לצוות' for 'tag partner' in 8 units (562, 705, 756, 799, 998, 1111, 1232, 1547).
- 'קרבות צוות' for 'tag battles' in 3 units (TrainerHill_Entrance_hns:300 and :307, MultiPartnerRoom:616), consistent with TAG MATCH 'קרב צוות' (src/strings.c:572-575, trainer_hill.c:373).
Bare 'צוות' is ambiguous in this room. The same NPCs call their Pokémon line-up a צוות: 372 'הרכבתי צוות', 422, 448, 529, 554, 695, 746. For example, Apprentice2 says 'הרכבתי צוות' and then 'בוא נקים צוות!'.
'זוגי' appears nowhere else in data/ or src/, so it does not clash with 'קרב כפול' (DOUBLE). FireRed has no tag-team term; it uses 'צמד מאמנים' once (LavenderTown_Mart/text.inc:14).

| Option | How | Risk |
|---|---|---|
| A: 'צוות זוגי' for 'tag team' ('הצוות'/'הצוותים' on a second mention); 'שותף/שותפה לצוות' for 'tag partner'; 'קרב צוות' for TAG MATCH | Change the 15 bare-צוות units here and the 7 'צמד' units (Q17). | Low. 23 short insertions; the widest new line is 185 px. 'צוות זוגי' is a coined term, a little formal for chatty NPCs. |
| B: 'צמד' everywhere | Rewrite the 21 'צוות זוגי' units and the 15 bare-צוות units, and move the Pokémon-pair uses (1646, 1693) to 'זוג'. | About 38 edits. 'שותף לצמד' for 'tag partner' is awkward, and it breaks the 'צוות' family with TAG MATCH 'קרב צוות'. |
| C: Bare 'צוות' everywhere | Strip 'זוגי' from 21 units and replace 'צמד' in 7. | Keeps the ambiguity with the Pokémon-team 'צוות' inside the same NPC's two messages. |

**Chosen:** A. It is unambiguous next to the Pokémon-team 'צוות' and is already the largest group (21 units, including the Trainer Hill owner). It belongs to one family with 'קרב צוות' (TAG MATCH and tag battles) and 'שותף לצוות' (tag partner), and needs the fewest edits of the unambiguous options. Apprentice12Mon2Ask:647 'בניצחון של צוות, בלי לדאוג!' stays: it rhymes (לחגוג/לדאוג), 'ניצחון של צוות' is idiomatic, and STYLE §1 says to keep jokes. The 'team up' lines without 'tag' in English keep plain 'צוות': 353, 387, 456, 510, 1167, 1273, 1280, 1399, 1420, 1610, 1619, 1660.

*Changed:* `data/maps/BattleFrontier_BattleTowerMultiPartnerRoom/scripts.inc`

*Glossary:* `TERM_TAG_TEAM`, `TERM_TAG_PARTNER`, `TERM_TAG_MATCH`

## Q15

**Question.** Intro word order differs by speaker: 'אני {STR_VAR_1}, נערת קרב!' / 'אני {STR_VAR_1}, מאמן על!' versus 'אני נער הנינג'ה {STR_VAR_1}!'. Both are correct, so I left it. Should the chunk use one order?

*Source:* reviewer question (chunk B35_02)

**Analysis.** In MultiPartnerRoom, 4 intros put the name first where the English puts the class first: BattleGirlIntro :1114 'אני {STR_VAR_1}, נערת קרב!' (English 'I'm BATTLE GIRL {STR_VAR_1}!'), ParasolLadyIntro :1344, CoolTrainerMIntro :1517 'אני {STR_VAR_1}, מאמן על!', CoolTrainerFIntro :1538 'אני {STR_VAR_1}, מאמנת על!'. The English itself mixes the two orders: LassIntro :754 'I'm {STR_VAR_1}, and I'm a LASS!' vs :796 'I'm HIKER {STR_VAR_1}!'. Name-first keeps the glossary class forms intact (glossary.csv:4811 נערת קרב, :4812 גברת שמשייה, :4773 מאמן על). With one token, the order of the tokens is unaffected. Each intro belongs to a different trainer and is seen on its own.

| Option | How | Risk |
|---|---|---|
| (a) Keep | No change | None |
| (b) Class first: 'אני נערת הקרב {STR_VAR_1}!', 'אני מאמן העל {STR_VAR_1}!' | Edit 4 lines | Bends the glossary forms into the construct state and gains nothing visible |

**Chosen:** (a). Both orders are natural, the English mixes them too, and the current lines quote the glossary class forms exactly.

## Q17

**Question.** Tag team: this chunk and B34_04 use 'צמד', while B35_01, B35_02 and B35_04 use 'צוות' or 'צוות זוגי' for the same partner-room concept. A batch-wide term would help.

*Source:* reviewer question (chunk B35_03)

**Analysis.** This is the same decision as Q12 ('צוות זוגי'). These are the 'צמד' lines still in the current tree for 'tag team', all live:
- BattleTowerLobby_hns:1241 'שבעה צמדים' and :1243 'הצמדים' (ExplainMultisChallenge_hns).
- BattleTowerLobby_hns:1372 'ליצור צמד' (ExplainSalonRules_hns).
- BattleTowerMultiPartnerRoom:1716, :1758, :1766, :1778.
- BattleTowerMultiPartnerRoom_hns:285 'לצמד שלך' (QuitLookingForPartner_hns).
Two other 'צמד' uses translate a Pokémon pair, not a tag team, and stay: MultiPartnerRoom:1646 'הצמד שגידלתי' ('twosome') and :1693 'צמד הפוקימונים' ('POKéMON pair'). After the change, 1693-1694 reads 'צמד הפוקימונים שלי… השותפה שלך בצוות זוגי', with the two concepts kept apart.

| Option | How | Risk |
|---|---|---|
| A: Replace the 8 'צמד' lines with 'צוות זוגי' (on a second mention, 'הצוותים' / 'הצוות הזוגי'), with the verb 'להקים' as in the salon lines | 8 substring edits, listed below. | Low; every line is measured and within budget (widest 185 px on a \p line, budget 200). |
| B: Keep 'צמד' in these chunks | No edits. | The Tower Lobby rules and four salon trainers would use a different word from the 38 other tag-team units in the same building. |

**Chosen:** A. It implements the Q12 term. The Lobby's rule text is where a player first meets the concept, so it must use the term the salon trainers then repeat.
One correction to the earlier proposal: line 1372 uses 'להקים צוות זוגי', not 'ליצור צוות זוגי'. 'להקים צוות' is the standard collocation, and it is the verb the salon trainers use (534, 822, 930, 953, 1060). Width 185 px on a \p line (budget 200).
Second mentions take plain 'הצוותים', as the English goes from 'tag teams' to 'teams'. Agreement is masculine throughout: 'שבעה צוותים זוגיים', 'כל שבעת הצוותים'.

*Changed:* `data/maps/BattleFrontier_BattleTowerLobby_hns/scripts.inc`, `data/maps/BattleFrontier_BattleTowerMultiPartnerRoom/scripts.inc`, `data/maps/BattleFrontier_BattleTowerMultiPartnerRoom_hns/scripts.inc`

## Q18

**Question.** BATTLE PIKE is 'שביל הקרב' everywhere (strings.c gText_BattlePike, B09, B34), but the glossary class PIKE QUEEN is 'מלכת הרומח' (pike as a weapon). Should the facility and its Brain match?

*Source:* reviewer question (chunk B35_03)

**Analysis.** Already applied in the current tree. Commits landed during this review, 3d72a5d77a, ba90a43b56, 01f4f6db62 and 27d8ed0664, replaced every 'מלכת הרומח' with 'מלכת השביל':
- src/battle_main.c:372 and :461;
- BattleFrontier_Lounge2/scripts.inc:219, :223, :231;
- BattlePikeLobby_hns:382;
- BattlePikeRoomNormal_hns:756.
Commit bb8db5c703 set proposed_hebrew to 'מלכת השביל' in glossary.csv:4831 (TRAINER_CLASS_PIKE_QUEEN) and :4917 (_HNS). 'מלכת הרומח' now has 0 hits in data/ and src/, and namecheck.py reports nothing for these rows.
The English is covered: the live Lounge2 labels (called from src/field_specials.c:2238-2240) and the two _hns Pike labels. The Lounge2_hns English copies and the non-_hns Pike maps are not built.
One leftover: both rows' notes still say 'PIKE = רומח as done MOVE_GLACIAL_LANCE…; debatable…', which now contradicts their Hebrew. The earlier code plan also had a corrupted character in 'שביל הקרב' (an Arabic letter in place of ר).

| Option | How | Risk |
|---|---|---|
| A: 'מלכת השביל' (now applied) | Nothing left in the text. Rewrite the two glossary notes only. | None. 10 bytes (limit 12), 59 px, the same as before; dialogue widths are unchanged. |
| B: Revert to 'מלכת הרומח' | Undo the 7 string edits and the 2 rows. | Restores a mistranslation (pike as a weapon) and the only Brain title that does not echo its facility. |
| C: 'מלכת הצינור' (Japanese 'Tube') | Change the class and also rename the facility in 12+ units and the symbol strings. | Large churn against the established 'שביל הקרב'. |

**Chosen:** A. It matches the facility name players see ('שביל הקרב', 'לבחור אחד משלושה שבילים לקרב!', src/strings.c:786, :905) and the pattern of the other six Brains (אס הכיפה, ראש המפעל, גבירת הזירה, אשף הארמון, מלך הפירמידה, עלמת הסלון). It fixes the weapon reading at the same byte and pixel cost.

## Q23

**Question.** MIMI (OutsideEast ConquerLeagueAndFrontier) and ZIGG (BelieveInYouBuddy, a Zigzagoon nickname) are not in the glossary, so they stay in Latin under STYLE section 3. Proposed: מימי and זיג.

*Source:* reviewer question (chunk B35_04)

**Analysis.** Still open at HEAD bb8db5c703. The Hebrew lines are data/maps/BattleFrontier_OutsideEast_hns/scripts.inc:268 'אני… אני אשאל את MIMI מהבית ליד', :298 'ZIGG!' and :300 'אם תנצח, ZIGG הקטן שלי, אכין לך'. The English is pokehns-heb-engine, same file, :270, :301 and :303. The map is live: STATUS.md:72 lists it as 27/27 seen on screen. glossary.csv has no MIMI or ZIGG row; the only MIMI hits are the MIMIKYU species rows. ZIGG is the owner's nickname for the Zigzagoon in the next text box (ZigzagoonLooksVacant, 'זיגזגון בוהה בחלל…'). ZIGZAGOON is זיגזגון, inherited from FireRed (glossary.csv:437). Apart from these 3 lines, MIMI and ZIGG appear only in the untranslated vanilla map data/maps/BattleFrontier_OutsideEast/scripts.inc. I applied the 3 edits to a scratch copy and ran drift.py against the engine baseline: the file is 'ok', and the LATIN warnings for MIMI and ZIGG are gone.

| Option | How | Risk |
|---|---|---|
| A: add NAME_MIMI = מימי and NAME_ZIGG = זיג, then apply them | Add two proposed 'name' rows and edit the 3 lines. MIMI: i = י (rules §3). ZIGG: the ZIG chunk of זיגזגון (rules §6), with the doubled g written once (rules §2). Widths in FONT_NORMAL: 160 px at :268, 17 px at :298 and 145 px at :300; each line ends in \n, so the budget is 208. | None. These are dialogue strings, and no token, label or page break changes. |
| B: keep the Latin names | No change. | Latin stays inside Hebrew lines on a live map, and the pet name appears twice. |
| C: write the species name זיגזגון instead of ZIGG | Replace ZIGG with זיגזגון. | The owner's pet name is lost, and the species name is repeated from the next text box. |

**Chosen:** A. Both are natural Hebrew renderings. מימי is a common name, and זיג is how a Hebrew speaker would shorten זיגזגון, so the link to the Pokémon the player sees next survives. The spellings follow the transliteration rules and the ZIGZAGOON family, and they remove Latin from a live map. The cost is 3 string edits and 2 rows.

*Changed:* `data/maps/BattleFrontier_OutsideEast_hns/scripts.inc`

*Glossary:* `NAME_MIMI`, `NAME_ZIGG`

## Q24

**Question.** Battle Frontier facility names (מגדל/כיפת/ארמון/זירת/מפעל/שביל/פירמידת הקרב), היכל הדירוג, מוחות החזית, סלון הקרב, חדר קרב מרובה, מסע הקרב and מורה היסודות (ELEMENTAL TUTOR) have no glossary rows. They are used consistently across B34-B36, except one B36_01 unit that has 'ראשי חזית הקרב' for FRONTIER BRAINS. Add them to the glossary?

*Source:* reviewer question (chunk B35_04)

**Analysis.** Each English term was mapped to its Hebrew across all live units. Every one has a single form that matches the engine strings:
- BATTLE TOWER 54/54 'מגדל הקרב', DOME 21/21 'כיפת הקרב', PALACE 13/13 'ארמון הקרב', ARENA 15/15 'זירת הקרב', FACTORY 11/11 'מפעל הקרב', PIKE 12/12 'שביל הקרב', PYRAMID 15/15 'פירמידת הקרב' (src/strings.c:779-787).
- RANKING HALL 4/4 'היכל הדירוג' (:617).
- EXCHANGE SERVICE 5/5 'שירות ההמרה' (:618); two of the units wrap it as 'פינת שירות\n ההמרה'. The corner is 'פינת שירות ההמרה'.
- BATTLE SALON 4/4 'סלון הקרב'.
- MULTI BATTLE ROOM in 7 units: 'חדר קרב מרובה' in 5, plural 'חדרי קרב מרובה' in 3.
- ELEMENTAL TUTOR 1/1 'מורה היסודות' (Lounge7_hns).
- FRONTIER BRAINS 8/8 'מוחות החזית'; the B36_01 variant 'ראשי חזית הקרב' no longer exists.
None of these has a glossary row (checked by constant). The related rows that exist are MAPSEC_BATTLE_FRONTIER (glossary.csv:4941) and TERM_FRONTIER_PASS (:6038).
These terms are written in upper case in the game text, so upper-case english fields match the case-sensitive names matcher in make_chunks.py.

| Option | How | Risk |
|---|---|---|
| A: Add term rows in the tree's existing forms | Append the rows below; no text edits. | None. The rows only lock what is already uniform. |
| B: Leave them out of the glossary | Nothing. | Later chunks get no names map for these terms and may invent variants, as B36_01 once did. |

**Chosen:** A. Every form is already uniform and matches the engine strings, so locking them protects later work at no cost. The event names (Battle Quest and the others) are in Q29 and FRONTIER BRAINS is in Q33, so no row is added twice.

*Glossary:* `TERM_BATTLE_TOWER`, `TERM_BATTLE_DOME`, `TERM_BATTLE_PALACE`, `TERM_BATTLE_ARENA`, `TERM_BATTLE_FACTORY`, `TERM_BATTLE_PIKE`, `TERM_BATTLE_PYRAMID`, `TERM_RANKING_HALL`, `TERM_EXCHANGE_SERVICE_CORNER`, `TERM_EXCHANGE_SERVICE`, `TERM_BATTLE_SALON`, `TERM_MULTI_BATTLE_ROOM`, `TERM_ELEMENTAL_TUTOR`

## Q27

**Question.** Lounge3 ObtainedBattlePoints keeps 'השיג' to match B34_04. ScottsHouse (B36_01) uses 'קיבל'. Pick one for '{PLAYER} obtained … Battle Points'.

*Source:* reviewer question (chunk B35_04)

**Analysis.** The four '{PLAYER} obtained N Battle Points' strings in the current tree:
- BattleFrontier_Text_ObtainedXBattlePoints (BattleTowerLobby/scripts.inc:1358) uses 'השיג'. This is the shared string: the facility lobbies' streak awards, NewBarkTown_hns:176, and 32 call sites in SaffronCity_FightingDojoVIP_hns (rematch rewards, e.g. after Falkner: 'givebp 10').
- Its _hns copy (BattleTowerLobby_hns:1345) uses 'השיג'.
- Lounge3_hns:432 uses 'השיג'.
- ScottsHouse_hns:238 is the only one with 'קיבל'.
The TV line tv.inc gTVWhatsNo1InHoennTodayText07 also says 'השיג'. Item and badge receipts use 'קיבל' (46 '{PLAYER} קיבל' lines in the tree, as FireRed does). The second-person tent line 'קיבלת {STR_VAR_1} נקודות קרב!' (battle_tent.inc:464) is a different sentence and is not affected.

| Option | How | Risk |
|---|---|---|
| A: 'השיג' for Battle Points; change ScottsHouse_hns:238 | 1 edit. | Minimal. For a gift from Scott, 'השיג' is a little less exact than 'קיבל', but the shared string already says 'השיג' for gifts (Dojo rewards, the New Bark NPC). |
| B: 'קיבל' everywhere, like item receipts | 3 edits: BattleTowerLobby:1358, BattleTowerLobby_hns:1345 and Lounge3_hns:432; tv.inc stays 'השיג' as narrative. | Also low (one-word swaps, same 161 px), but it changes the string players see most often to fit one line, and it gives up the idiomatic points collocation. |

**Chosen:** A. 'להשיג נקודות' is idiomatic Hebrew for points. The shared string, seen after every Frontier streak and Dojo rematch, already uses it, and 3 of the 4 receipt lines already agree. One edit makes all four match.

*Changed:* `data/maps/BattleFrontier_ScottsHouse_hns/scripts.inc`

## Q29

**Question.** None of the Battle Frontier facility and event names are in glossary.csv: מגדל/כיפת/ארמון/זירת/מפעל/שביל/פירמידת הקרב, היכל הדירוג, החלפת הקרב, בחירת הקרב, מסע הקרב, טורניר הנוקאאוט. They are used the same way in every chunk, but should they be added as glossary rows so they are locked?

*Source:* reviewer question (chunk B35_05)

**Analysis.** The facility names are covered by Q24. Event names in live units:
- Battle Choice: 17/17 'בחירת הקרב'.
- Battle Quest: 9/9 'מסע הקרב'.
- Battle Tournament: 15 'טורניר הקרב', plus 2 plurals 'טורנירי הקרב' (tv.inc).
- Battle Swap: 8 units with 'החלפת הקרב' and 11 with 'החלפת קרב'. Every indefinite one is grammar, not drift. It is either a construct before יחיד/כפול ('טורניר החלפת קרב יחיד' in FactoryLobby_hns and Lounge3) or an indefinite event ('באירוע החלפת קרב', 'אירועי החלפת קרב' in battle_tent.inc and FactoryLobby). This matches the results titles 'תוצאות החלפת קרב יחיד/כפול' (src/strings.c:974-975).
- Set KO Tourney: 14 'טורניר הנוקאאוט', plus the referee's callout 'שופט: טורניר נוקאאוט!' (ArenaBattleRoom and ArenaBattleRoom_hns SetKOTourneyBegin).
- BATTLE HALL (Palace halls): 'אולם הקרב' in 7 units, 'אולמות הקרב' in 6, and indefinite or split forms in 4 ('אולמות קרב', 'לאולמות\n הקרב'). The results titles use 'אולם קרב' (src/strings.c:970-971).
None of these has a glossary row.
Case matters for the rows: the game writes 'Battle Swap' (37), 'Battle Choice' (38), 'Battle Quest' (17), 'Set KO Tourney' (22), 'Battle Tournament' (20; also 'BATTLE Tournament' 18) and 'BATTLE HALL(S)'. make_chunks.py names_in() matches case-sensitively, so the earlier all-caps english fields ('BATTLE SWAP' and the others) and 'BATTLE HALL (Battle Palace)' would never fire.

| Option | How | Risk |
|---|---|---|
| A: Add term rows (definite form as the headword, with a note on the construct form), with english in the game's own spelling | Append the rows below; no text edits. | None. |
| B: Also force the definite 'החלפת הקרב' in the 11 construct units | Rewrite 11 units. | Produces ungrammatical Hebrew ('טורניר החלפת הקרב יחיד') and breaks the match with the results titles. |

**Chosen:** A. Once Hebrew construct grammar is taken into account, the tree is already consistent. Locking the headword form, with a note that 'החלפת קרב' / 'בחירת קרב' / 'מסע קרב' / 'אולם קרב' are the construct forms (before יחיד/כפול, after אירוע/טורניר, and in the results titles), prevents drift without touching correct text.

*Glossary:* `TERM_BATTLE_SWAP`, `TERM_BATTLE_CHOICE`, `TERM_BATTLE_QUEST`, `TERM_SET_KO_TOURNEY`, `TERM_BATTLE_TOURNAMENT`, `TERM_BATTLE_HALL`

## Q33

**Question.** FRONTIER BRAIN, FRONTIER PASS, BATTLE TOWER, BATTLE TENT, Battle Points, BERRY POCKET and Gold/Silver Symbols have no glossary rows. I followed what the tree already uses (מוחות החזית, כרטיס חזית הקרב, מגדל הקרב, אוהל הקרב, נקודות קרב, כיס הפירות, סמלי זהב/כסף). Should these become glossary rows? Is 'מוחות החזית' the final term, or should Scott's 'handpicked FRONTIER BRAINS' read more like titled leaders?

*Source:* reviewer question (chunk B36_01)

**Analysis.** Current tree, live units:
- FRONTIER BRAINS: 8/8 'מוחות החזית'. Lounge2 has 6 in quotes ('מכנה ”מוחות החזית”'). ScottsHouse_hns:264 has 'ממוחות החזית' and :266 'בחרתי את מוחות החזית בקפידה'. The B36_01 variant is gone. The game always writes the plural, 'FRONTIER BRAINS' (18 English occurrences).
- FRONTIER PASS: 40/40 'כרטיס חזית הקרב'; the row already exists (TERM_FRONTIER_PASS, glossary.csv:6038).
- BATTLE TOWER: row added in Q24.
- BATTLE TENT: 16 units 'אוהל הקרב', plus 3 plural 'אוהלי הקרב'.
- Battle Points: 42 units. 23 use only 'נקודות קרב', 14 only 'נקודות הקרב', 5 both. Every definite use is where Hebrew needs the article ('את נקודות הקרב האלה', 'בנקודות הקרב', 'לוקח את כל נקודות הקרב').
- BERRY POCKET: 'כיס הפירות' (ScottsHouse_hns:313). The bag tab itself is 'פירות' (src/strings.c:222).
- Gold/Silver Symbols: the game only writes the plural, 'Gold Symbols' / 'Silver Symbols' (once each, plus lower-case 'gold/silver symbols'). The Hebrew is 'סמלי זהב' / 'סמלי כסף' (tv.inc:1204-1205) and definite 'סמלי הזהב' / 'סמלי הכסף' (ScottsHouse_hns:298, :284), matching the 'סמל' of the per-facility symbols (src/strings.c:884-891).
None except FRONTIER PASS has a row. Because names_in() in make_chunks.py rejects a hit followed by a letter, a singular english 'Gold Symbol' would never match 'Gold Symbols'. The rows therefore use the plural the game writes.

| Option | How | Risk |
|---|---|---|
| A: Add rows (english as the game writes it) and keep 'מוחות החזית' | Append the rows below; no text edits. | None. |
| B: Re-title FRONTIER BRAINS as leaders ('ראשי החזית' or 'מנהיגי החזית') | Rewrite 8 units and add the row. | 'ראשי' clashes with the class 'ראש המפעל' (FACTORY HEAD), and 'מנהיג' is the glossary's GYM LEADER (TERM_GYM_LEADER, glossary.csv:5520). 8 edits for no gain. |

**Chosen:** A. 'מוחות החזית' is a faithful rendering of the coined English title, reads naturally in Scott's line, and does not collide with ראש המפעל or מנהיג. Every other term already has one form. FRONTIER PASS is already in the glossary and is not added again.

*Glossary:* `TERM_FRONTIER_BRAINS`, `TERM_BATTLE_TENT`, `TERM_BATTLE_POINTS`, `TERM_BERRY_POCKET`, `TERM_GOLD_SYMBOLS`, `TERM_SILVER_SYMBOLS`

## Q37

**Question.** VerdanturfTown GentleMonsScaryIfAngry uses 'נעימה' for the speaker's sister to keep the GENTLE nature (נעים) link. 'עדינה' would be more natural for a person but loses the link. Keep 'נעימה'?

*Source:* reviewer question (chunk B36_01)

**Analysis.** VerdanturfTown_BattleTentLobby_hns GentleMonsScaryIfAngry (label :340, text :341-344) has 'אחותי הגדולה בדרך כלל נעימה' (:341) and 'בטח גם פוקימון נעים' (:343). (Line correction: the text is at :341/:343, not :342/:344.) GENTLE is 'נעים' (glossary.csv:4654) and MILD is 'עדין' (glossary.csv:4649), both FireRed matches.

| Option | How | Risk |
|---|---|---|
| (a) Keep 'נעימה' | No change | None. 'בדרך כלל נעימה' is natural for a person |
| (b) 'עדינה' | Edit :341 and :343 | Points at the MILD nature (עדין), so the hint becomes wrong |

**Chosen:** (a). The line exists to hint at GENTLE. 'עדינה' would hint at a different nature.

## Q38

**Question.** The apprentice 'underling' (Guitarist) is rendered 'העוזר שלך', and 'mentor' and 'master' stay as the loanwords 'מנטור' / 'מאסטר' (consistent with B35_01). Confirm this register is acceptable.

*Source:* reviewer question (chunk B36_01)

**Analysis.** Three English words map to three Hebrew words, consistently, in data/text/apprentice.inc: mentor→מנטור (10 Hebrew, 11 English), master→מאסטר (25/24, including the Spanish speaker's 'המאסטרו' at :922), teacher→מורה (9/8), apprentice→חניך. 'underling' (Guitarist, English :529/:535) is 'העוזר שלך' at :499 and :505. מאסטר is also the tree's word for the dragon masters (DragonsDen_Shrine_hns:402 'המאסטר לאנס', BlackthornCity_hns:206).

| Option | How | Risk |
|---|---|---|
| (a) Accept as is | No change | None |
| (b) underling = 'הכפוף שלך' / 'המשרת שלך' | Edit 2 lines | Bureaucratic or servile, which breaks the rocker's playful voice |
| (c) underling = 'החניך שלך' | Edit 2 lines | Flattens the character's word into the system term |

**Chosen:** (a). It is consistent, keeps the English distinctions, and fits each character's voice.

## Q40

**Question.** 'I need to tap your mind again' is translated אני שוב צריכה את המוח שלך. It is a calque, and I kept it only because B36_01 (WhatHeldItem6) uses the same phrase. Should the whole batch switch to something more idiomatic, such as אני שוב צריכה את הראש שלך?

*Source:* reviewer question (chunk B36_02)

**Analysis.** The premise has changed. Apprentice 6's identical English line 'I need to tap your mind again today.' now has two Hebrew renderings. WhatHeldItem6 :821 has 'היום שוב אני צריכה להיעזר בראש שלך.' (idiomatic). WhichMon6 :1561 ('…\n') and WhichMove6 :1848 ('…\p', a one-line page) still have the calque 'אני שוב צריכה את המוח שלך היום.'. The :821 wording measures 180 px.

| Option | How | Risk |
|---|---|---|
| (a) Copy the :821 wording exactly into :1561 and :1848 | 2 edits, 180 px (limit 208 at :1561, 200 at :1848) | None |
| (b) 'אני שוב צריכה להתייעץ איתך היום.' in all 3 | 3 edits, 159 px | Loses the 'tap your mind' color, and it is one more edit |
| (c) Keep the calque | No change | One character's catchphrase is worded two ways, one of them a calque |

**Chosen:** (a). The character gets one catchphrase, reused word for word in its idiomatic form, with the fewest edits.

*Changed:* `data/text/apprentice.inc`

## Q41

**Question.** 'Snivel/Sniff' is rendered סניף across B36_01 and this chunk. In Hebrew סניף also means a branch (of a bank or store). Keep it, or use a different crying sound such as אפצ'-סניף or *משיכת אף*?

*Source:* reviewer question (chunk B36_02)

**Analysis.** Count correction: 'סניף' appears 22 times in the tree, but only 18 are the crying sound. Sniff/Snivel: apprentice.inc 10 lines (:4, :71, :83, :103, :1455, :1467, :1739, :1753, :2031, :2046), MultiPartnerRoom:342/:352, GoldenrodCity_Gym_hns:142/:145, SaffronCity_FightingDojoVIP_hns:748, tv.inc:2766/:2852/:2868. The other 4 mean 'branch': NewSinjoh_hns:172 'לפתוח סניף', and battle_tent.inc:9/:137/:245 'סניף FALLARBOR!' etc., which sit in the #else (non-HnS) branch and so are not built. As a sound, it always stands alone, with '…' or '!'. It is FireRed canon (pokefirered-heb PokemonTower_1F/text.inc:18 'סניף!').

| Option | How | Risk |
|---|---|---|
| (a) Keep 'סניף' | No change | None in context |
| (b) 'אפצ'-סניף' | Replace 18 times | That is a sneeze, not crying |
| (c) '*משיכת אף*' | Replace 18 times | A stage direction, which the game never uses |

**Chosen:** (a). It is FireRed canon, consistent across the tree, and never ambiguous where it stands as an interjection. The one live 'branch' use (NewSinjoh) is clear from its verb.

## Q43

**Question.** ThanksNoHeldItem14 and ThanksHeldItem14 translate the odd English line 'Wouldn't it be too cool?' literally (זה לא יהיה מגניב מדי?). It probably means the shy speaker is worried about looking too showy. Is the literal version acceptable, or should it read something like זה לא ייראה יותר מדי מתרברב?

*Source:* reviewer question (chunk B36_02)

**Analysis.** Apprentice 14 is the shy ruin explorer (PleaseTeach14: 'אתה גורם לי להרגיש נבוך', apprentice.inc:559; 'ממש מביך אותי', :561; English :590-593 'You're making me all self-conscious'). In ThanksNoHeldItem14 :1120 and ThanksHeldItem14 :1128, 'Wouldn't it be too cool?' (English :1184/:1193) is 'זה לא יהיה מגניב מדי?'. The joke is that he worries his choice will make him look too flashy. 'ייראה מגניב' is already used in the tree (GoldenrodCity_UndergroundTunnel_hns:334 'אדאג שהוא ייראה מגניב!').

| Option | How | Risk |
|---|---|---|
| (a) 'זה לא ייראה מגניב מדי?' | Edit 2 lines, 112 px (limit 200; the lines end in \p) | None |
| (b) 'זה לא ייראה יותר מדי מתרברב?' | Edit 2 lines, 148 px | Changes the meaning to 'boastful' |
| (c) Keep the literal version | No change | Reads oddly, and the self-consciousness is lost |

**Chosen:** (a). One verb change keeps the English 'too cool' joke and adds the worry about how it looks, which fits the shy character. The spelling matches the tree's existing 'ייראה מגניב'.

*Changed:* `data/text/apprentice.inc`

## Q44

**Question.** Two live strings still show Emerald town names in Latin letters: VerdanturfTown_BattleTentLobby_Text_RulesAreListed (VERDANTURF) and SlateportCity_BattleTentLobby_Text_ExplainMonRules (SLATEPORT). The H&S scripts call both. Upstream never renamed them, and FALLARBOR/VERDANTURF/SLATEPORT have no glossary rows, so I left the English as STYLE §3 requires. Should these use the H&S names ('אוהל הקרב של הארמון' / 'אוהל הקרב של המפעל') instead? That would also need a decision for the #else-only units that carry the same names.

*Source:* reviewer question (chunk B36_03)

**Analysis.** The premise is confirmed in the current tree:
- VerdanturfTown_BattleTentLobby_hns/scripts.inc:277 calls VerdanturfTown_BattleTentLobby_Text_RulesAreListed.
- SlateportCity_BattleTentLobby_hns/scripts.inc:277 calls SlateportCity_BattleTentLobby_Text_ExplainMonRules.
- live_labels.json marks both as live.
They still carry Latin: data/text/battle_tent.inc:461 'אוהל הקרב של VERDANTURF.$', and :383-384 'כל הפוקימונים של אוהל הקרב' / 'של SLATEPORT הם שכורים.'. Upstream never gave these two an IS_HNS branch; the engine has a plain 'The VERDANTURF BATTLE TENT' and 'The POKéMON of the SLATEPORT BATTLE TENT'.
The same file's IS_HNS branches already name the tents: 'באוהל הקרב של הזירה' (:23, English 'ARENA BATTLE TENT'), 'באוהל הקרב של הארמון' (:151, 'PALACE BATTLE TENT') and 'באוהל הקרב של המפעל' (:257, 'FACTORY BATTLE TENT').
The other Latin town names in this file (:9, :25, :137, :145, :153, :245, :259) are in #else branches that H&S does not build.

| Option | How | Risk |
|---|---|---|
| A: Use the H&S tent names in the two live strings | battle_tent.inc:461 VERDANTURF becomes 'הארמון'. Lines 383-384 become 'כל הפוקימונים באוהל הקרב' / 'של המפעל הם שכורים.', which avoids a double 'של'. | Low: widths 127, 105 and 107 px, Hebrew text only, no #if lines or labels touched. |
| B: Keep the Latin per STYLE §3 | No edits. | Players read 'VERDANTURF' and 'SLATEPORT', towns that do not exist in H&S, right after the tent intro called these tents 'הארמון' and 'המפעל'. |

**Chosen:** A. The names come from the same file's H&S branches, so nothing is invented and STYLE §3 holds. It removes two Latin words players actually see, and it matches the tent intros. The #else-only units are not built (IS_HNS is set) and stay as they are.

*Changed:* `data/text/battle_tent.inc`

*Glossary:* `TERM_ARENA_BATTLE_TENT`, `TERM_PALACE_BATTLE_TENT`, `TERM_FACTORY_BATTLE_TENT`

## Q48

**Question.** 'crucial rule' is 'כלל מכריע' here and in the Palace lobby. 'כלל חשוב אחד' reads more naturally. If you change it, change both places.

*Source:* reviewer question (chunk B36_03)

**Analysis.** 'one crucial rule' appears 3 times as 'כלל מכריע אחד' ('decisive', which is slightly off), and there are no other occurrences in data/ or src/: BattleFrontier_BattlePalaceLobby_hns/scripts.inc:396 and :556 (the Single and Double explanations), and data/text/battle_tent.inc:155 ('יש כלל מכריע אחד…', after the #endif, so it is shared). All three lines end in \p (limit 200).

| Option | How | Risk |
|---|---|---|
| (a) 'כלל חשוב אחד' in all 3 | 3 edits: 146 px (was 151) and 159 px (was 164) | None |
| (b) 'כלל קריטי אחד' | 3 edits, 147 px | A loanword. Natural, but less neutral in register |
| (c) Keep 'מכריע' | No change | Slightly wrong meaning |

**Chosen:** (a). It is the most natural Hebrew, keeps the meaning, is narrower, and keeps the three copies consistent.

*Changed:* `data/maps/BattleFrontier_BattlePalaceLobby_hns/scripts.inc`, `data/text/battle_tent.inc`

## Q49

**Question.** For the Sailor rap I used the slang 'אחי' (bro) for the rhyme. For the Hiker I kept the Spanish transliterations 'אולה, בואנו', 'סי', 'אדיוס'. Are these acceptable for the register?

*Source:* reviewer question (chunk B36_03)

**Analysis.** The register is fine. 'אחי' is used by the Sailor (apprentice.inc:450, :2282) and the Guitarist (:494, :503), and elsewhere in the tree (BlackthornCity_hns, Route29_hns, LilycoveCity_ContestLobby_hns, among others). The Spanish words come from the English itself ('Hola!' :976, 'Si, bueno!' :990, 'Hola, {PLAYER}{KUN}, bueno!' :2006, 'Hola, bueno!' :2355, 'Adios!' ×7), so STYLE §1 'keep each character's voice' applies. There is one spelling split for 'Hola': 'הולה' at :921 and :1897, but 'אולה' at :2233. 'הולה' is already the tree's word for hula (EcruteakCity_Theater_hns:110 'ריקוד הולה'), and transliteration_rules §2 drops a silent initial h ('HUGH יו').

| Option | How | Risk |
|---|---|---|
| (a) Accept the register and spell it 'אולה' at :921 and :1897 | 2 edits (158 px at :1897, unchanged) | None |
| (b) Spell it 'הולה' at :2233 | 1 edit | Collides with 'hula' and goes against the silent-h rule |
| (c) Translate the Spanish to Hebrew | Rewrite about 10 lines | Erases the character's voice |

**Chosen:** (a). It keeps the voice, and the single spelling matches both the rules and how Hebrew speakers write the greeting.

*Changed:* `data/text/apprentice.inc`

## Q50

**Question.** Apprentice names (src/data/battle_frontier/apprentice.h): GAME_LANGUAGE is LANGUAGE_ENGLISH (include/constants/global.h:82), and GetApprenticeNameInLanguage returns name[1], the English column (src/apprentice.c:1240-1259). So the names a Hebrew player sees are the English-column ones: DALLAS, TYRESE, ARTURO here, and ALANN, LIONEL, SONNY, LAYLA, MACY, AMIRA, KALI, ANNIE, DILLEN, LAMONT and DANTE in other chunks. None of these is in the glossary, so they display in Latin. Meanwhile the French and German slots (BRUNO, ANDY, DAVID, BRIAN, LOLA, FRANK) were turned into Hebrew only because they happened to match a glossary name, even though those slots are effectively never shown. Should the 16 English-column apprentice names get glossary rows and be transliterated, with the other language columns left alone?

*Source:* reviewer question (chunk B36_04)

**Analysis.** The main part is done. The English column, name[1], of all 16 apprentices (src/data/battle_frontier/apprentice.h:300-420) is Hebrew, from the NAME_ALANN … NAME_ARTURO rows (glossary.csv:6388 onward) plus TRNAME_FRANK פרנק.
What is left are 7 cells in the other-language columns. They became Hebrew only because they matched glossary names: :324 name[5] לולה, :380 name[2] ברונו, :388 name[2] and name[4] פרנק, :404 name[2] אנדי and name[4] דוד, :420 name[4] בריאן. The other 57 cells in those columns are upstream Latin (STATUS.md:536: '57 | 0 | translated (57 kept in Latin…)').
GetApprenticeNameInLanguage (src/apprentice.c:1240-1259) picks the column by language. The player's own apprentice uses GAME_LANGUAGE = LANGUAGE_ENGLISH (include/constants/global.h:82; src/apprentice.c:1052). Records and their Pokémon use the stored language (src/frontier_util.c:3270-3274, src/pokemon.c:3591-3593). So a non-English column appears only for an apprentice record mixed in from a French, Italian, German or Spanish game.
I checked the 5 edits in a scratch copy. After them, every one of the 16 lines differs from upstream only in name[1]. units.extract counts 64 Latin units (it counted 57 before), and drift.py reports 'ok'.
Correction to the earlier code plan: tools/hebrew/status_report.py fills in 'seen on screen' only when it gets --sweep (status_report.py:59-62, 89-92). Run without it, it would downgrade the 491 'seen on screen' rows to 'translated'. Do not regenerate STATUS.md that way.

| Option | How | Risk |
|---|---|---|
| A: revert the 7 foreign-column cells to their upstream values | Restore LOLA, BRUNO, FRANK (twice), ANDY, DAVID and BRIAN. The file then has one rule with no exceptions: the English column is Hebrew and the other columns are upstream, which is exactly what the KEPT_LATIN reason (status_report.py:27) says. Update STATUS.md:536 from 57 to 64 by hand. | None for players, because a Hebrew game's own data never shows these cells. A future name-fill pass over apprentice.h could make them Hebrew again; the KEPT_LATIN reason documents the rule against that. |
| B: leave them as they are | No change. | Harmless. But the foreign columns stay an arbitrary mix picked by glossary coincidence, and the KEPT_LATIN reason is only partly true. |
| C: transliterate all 64 foreign-column cells | Add about 50 proposed rows and apply them. | A lot of work and more unchecked proposed names, for text that practically no player sees. |

**Chosen:** A. This is the smallest change that leaves the file under one rule that matches the code. Nothing a player normally sees changes, and it removes translations that came from accidental matches rather than decisions.

*Changed:* `src/data/battle_frontier/apprentice.h`, `translation/hebrew/STATUS.md`

## Q52

**Question.** #112 'בלי להשתמש במהלך' vs 'בלי להשתמש באף מהלך' (clearer that no move at all was used): the longer form measures 204 px against the English's 184 px at realistic worst case. Both fit the 208 px window, so this is a style call.

*Source:* reviewer question (chunk B36_04)

**Analysis.** src/battle_dome.c:1005 DOME_TEXT_WON_NO_MOVES is 'ניצחון ל{STR_VAR_1} בלי להשתמש במהלך!' (English '{STR_VAR_1} won without using a move!'). :1001 is 'ניצחון ל{STR_VAR_1} עם {STR_VAR_2}!', and :1006 (CHAMP_NO_MOVES, English 'won outright with no moves!') is '{STR_VAR_1} זוכה באליפות בלי אף מהלך!'. The string prints in WIN_MATCH_WIN_TEXT: 26 tiles = 208 px wide (battle_dome.c:429-433), at x=0 (:4791-4808). It is chosen at :4624 when the winning move is MOVE_NONE and the match was not forfeited. STR_VAR_1 is a trainer name of at most 7 letters (the widest Hebrew frontier trainer name is 41 px). Widths at W7: current 187, 'באף מהלך' 204, 'בלי אף מהלך' 153.

| Option | How | Risk |
|---|---|---|
| (a) Keep 'בלי להשתמש במהלך' | No change | Less clear that no move at all was used |
| (b) 'בלי להשתמש באף מהלך' | 1 edit, 204/208 | A 4 px margin at the worst case |
| (c) 'בלי אף מהלך' | 1 edit, 153/208 | None. It is the exact negation of the :1001 'עם {STR_VAR_2}' frame |

**Chosen:** (c). It is the clearest ('not a single move'), matches the champion line at :1006 word for word, mirrors the 'won with MOVE' line, and leaves a wide margin.

*Changed:* `src/battle_dome.c`

## Q54

**Question.** Cross-chunk consistency: B37_s01 still has about 101 frontier trainer names in English. Some names in this chunk also appear in other files that are still in English: TRISTAN and ROBERTO (src/trader.c, B30_06); GABRIEL, CHELSEA, TRENTON, BRADEN, SHANIA, BRENNAN, EMANUEL and JARRETT (src/trainer_tower_sets.c, B38); KELSEY and CAITLIN (contest_opponents.h, B26_02); MIRANDA (trainer_hill.h, B37_03). Should those use the spellings chosen here?

*Source:* reviewer question (chunk B37_01))

**Analysis.** Already resolved. Every file named in the question uses the Battle Frontier spellings:
- src/trader.c:20-23: טריסטן, פיליפ, דניס, רוברטו.
- src/data/contest_opponents.h:313 קלסי and :777 קייטלין. They have their own contest_trainer rows (glossary.csv:6055 and :6084 at HEAD bb8db5c703; the glossary lost 5 rows during this review).
- src/data/battle_frontier/trainer_hill.h:788 מירנדה, the same as FRONTIER_TRAINER_247_MIRANDA (glossary.csv:5778).
- src/trainer_tower_sets.c already has גבריאל, צ'לסי, טרנטון, בריידן, שאנייה, ברנן, עמנואל, ג'ארט and לורנצו, one occurrence each.
The trader names and the Trainer Hill MIRANDA have no row of their own. They match the existing rows for the same English name: FRONTIER_TRAINER_65_TRISTAN (:5596), FRONTIER_TRAINER_152_ROBERTO (:5683), TENT_TRAINER_40_DENNIS (:6268) and NAME_PHILIP (:6470).
Correction: the trader buffer is playerNames[NUM_TRADER_ITEMS][11] (include/global.h:880), so the limit is 10 letters, not 7. All four names have 6 letters or fewer.

| Option | How | Risk |
|---|---|---|
| A: nothing more to do | Leave the tree and the glossary as they are. | None. |
| B: add rows keyed to the trader and Trainer Hill constants | Add TRADER_* and HILL_TRAINER_7_MIRANDA rows that repeat the existing Hebrew. | Duplicate rows with no visible effect, and one more place to update if a spelling changes. |

**Chosen:** A. The question is settled: every listed name already uses the Battle Frontier spelling. Matching rows by English name is the convention the Battle Tent and Trainer Hill passes already used.

## Q56

**Question.** Judgment calls the references do not settle: JORDAN ג'ורדן rather than the Israeli name ירדן; JORDYN ג'ורדין; XANDER זנדר (by sound) rather than קסנדר; XAVIER קסבייר (the familiar Israeli form, as in X-Men); JAZMIN ג'זמין, kept distinct from both YAZMIN יסמין and the gym leader JASMINE ג'סמין; HUNTER הנטר (to avoid looking like the Pokémon); GUNNAR גונאר; SHANIA שאנייה; CIERRA סיירה; JULIAN ג'וליאן (English) next to JULIANA יוליאנה (byte-forced).

*Source:* reviewer question (chunk B37_01))

**Analysis.** XANDER is settled: קסנדר in the glossary (glossary.csv:5662) and in the tree.
JORDAN is still ג'ורדן: src/data/battle_frontier/battle_frontier_trainers.h:928 (FACILITY_CLASS_EXPERT_M) and glossary.csv:5646. That row was :5651 when the decision was drafted; the HEAD bb8db5c703 glossary commit removed 5 rows above it.
The proposed-names review that was just applied (hns-tools/scratch/names_check/result.json) kept ג'ורדן. Its reason is 'Michael Jordan ג'ורדן', which is about the surname.
For given names, transliteration_rules §5 gives a name with a familiar Hebrew form that form. FireRed does this for full biblical names: SAMUEL שמואל (pokefirered-heb src/data/trainers.h:3919), AARON אהרן (:3199), JOSHUA יהושע (:3419), ISAAC יצחק (:2079), and also ETHAN איתן, JONAH יונה, BENJAMIN בנימין. The project's own proposed rows do the same: MICHAEL מיכאל, JOEL יואל, NATHAN נתן, DANIEL דניאל, GABRIEL גבריאל, MIRIAM מרים, REBECCA רבקה, EZRA עזרא, ABRAHAM אברהם.
FireRed is not fully consistent: SIMON סיימון, JEREMY ג'רמי and JESSE ג'סי were transliterated, so this is a judgment call. JORDAN is the standard English form of ירדן, a common Israeli unisex name, so it fits a male Expert.
The other calls stand:
- JORDYN ג'ורדין (:1112, a Beauty; glossary.csv:5669) keeps its own spelling. The project keeps different English spellings distinct, as with JAZMIN, YAZMIN and JASMINE.
- XAVIER קסבייר is the familiar Israeli form.
- HUNTER הנטר avoids the Pokémon HAUNTER האנטר.
- GUNNAR גונאר, SHANIA שאנייה and CIERRA סיירה stay as proposed.
- JULIAN ג'וליאן stays. ג'וליאנה would be 8 bytes, over trainerName[PLAYER_NAME_LENGTH + 1] (include/battle_frontier.h:11; PLAYER_NAME_LENGTH is 7), and יוליאנה follows FireRed's JULIA יוליה.

| Option | How | Risk |
|---|---|---|
| A: keep ג'ורדן | No change. This is what the names_check review chose. | It goes against §5 as the project applies it to its own new given names (MICHAEL מיכאל, JOEL יואל, NATHAN נתן). Hebrew players see an anglicised form of a common Israeli name. |
| B: JORDAN becomes ירדן; JORDYN and the others stay | Edit battle_frontier_trainers.h:928 and the glossary row at glossary.csv:5646. The new name is 4 bytes, within the 7-byte limit. | Minimal: one name string, with no save data or logic involved. It overrides the names_check 'keep' verdict, so the reason is written into the row's notes. |
| C: both JORDAN and JORDYN become ירדן | Also edit :1112 and glossary.csv:5669. | Two Frontier trainers share one name, and the practice of keeping distinct English spellings distinct is lost. |

**Chosen:** B. ירדן is the natural Hebrew form of this given name. It follows §5 the way FireRed treats SAMUEL, AARON and ISAAC, and the way this project treats MICHAEL, JOEL and NATHAN. The names_check reason rests on the surname Jordan, not the given name. JORDYN is a deliberate modern respelling and keeps its own form, as JASMINE, JAZMIN and YAZMIN do.

*Changed:* `src/data/battle_frontier/battle_frontier_trainers.h`, `translation/hebrew/glossary.csv`

## Q57

**Question.** 68 frontier and tent trainer names in this chunk are still in Latin letters (TRISTON, FERRIS, ALIVIA, GRETEL, and the Slateport, Verdanturf and Fallarbor tent trainers from MALACHI to KIANNA). None of them has a row in glossary.csv, so per STYLE §3 they were not guessed. Sibling chunk B37_01 follows the same convention. Should glossary rows be added (trainer names have a 10-byte limit) so that checkunits' NOHEBREW warnings can be cleared?

*Source:* reviewer question (chunk B37_02)

**Analysis.** Already resolved. I checked src/data/battle_frontier/battle_tent.h by script against the engine baseline:
- All 90 trainerName fields are Hebrew; none is Latin.
- 86 have tent_trainer rows, for example TENT_TRAINER_1_MALACHI מלאכי (glossary.csv:6233) and TENT_TRAINER_34_CAITLYN קייטלין (:6263). Every one matches its row.
- The other 4 reuse existing rows: KELSIE קלסי (:530), REBECCA רבקה (:634), MARKUS מרקוס (:1661) and RONALD רונלד (:1685).
- The longest name has 7 letters (רודולפו, :562), within trainerName[PLAYER_NAME_LENGTH + 1] (include/battle_frontier.h:11).
The four Frontier names the question lists (TRISTON, FERRIS, ALIVIA, GRETEL) are Hebrew too.

| Option | How | Risk |
|---|---|---|
| A: nothing more to do | No change. | None. |
| B: re-review the 86 proposed tent spellings | A reviewer pass over the tent_trainer rows. | This belongs to the general check of proposed names, which has just run (names_check), not to this issue. |

**Chosen:** A. Proposed rows were added and applied within the 7-letter limit, and existing spellings were reused, which is what the triage asked for.

## Q59

**Question.** Not changed but worth a human ear: Tucker's 'לא נעים לך?' for 'Aren't you embarrassed?' (the alternative is 'לא מביך אותך?'), and Noland's 'כבר סיימת?' for 'You're finished already?' (the alternative is 'כבר נגמר לך הכוח?').

*Source:* reviewer question (chunk B37_02)

**Analysis.** Tucker, src/frontier_util.c:150-151: 'אהאהאהא! לא נעים לך?\nכולם מסתכלים!' (English 'Ahahaha! Aren't you embarrassed?\nEveryone's watching!'). Noland, :236-237: 'היי, היי, היי!\nכבר סיימת?' (English 'Hey, hey, hey!\nYou're finished already?').

| Option | How | Risk |
|---|---|---|
| (a) Keep both | No change | None |
| (b) Tucker 'לא מביך אותך?', Noland 'כבר נגמר לך הכוח?' | 2 edits | 'לא מביך אותך' is stiffer, and 'נגמר לך הכוח' adds information that is not in the English |

**Chosen:** (a). 'לא נעים לך?' is the idiomatic Hebrew for being embarrassed in front of others, and 'כבר סיימת?' says exactly what the English says.

## Q60

**Question.** Twelve Trainer Hill trainer names are not in glossary.csv, so they stay in English as STYLE §3 says: SABINE, DAICHI, MIRANDA, TANNER, LENORA, MARLIN, LILIAN, REGINALD, MARTINA, FELICIA, CORNELIA, ABRAHAM (src/data/battle_frontier/trainer_hill.h). They need glossary rows. B37_04, B37_05 and B37_s02 have the same gap.

*Source:* reviewer question (chunk B37_03)

**Analysis.** Already resolved. Correction to the count: src/data/battle_frontier/trainer_hill.h has 64 Latin-source names (`.name = _("…")`), not 63, and all 64 are Hebrew. The 4 Japanese e-Reader dummies (`__("…")`) are unchanged.
I checked by script against the engine baseline. 56 names have hill_trainer rows and all match, for example SABINE סבין (glossary.csv:6318), DAICHI דאיצ'י (:6320), TANNER טנר (:6321), LENORA לנורה (:6322), REGINALD רג'ינלד (:6325), CORNELIA קורנליה (:6330), and ABRAHAM אברהם (:6332 and :6361, the familiar Hebrew form under §5). These line numbers are at HEAD bb8db5c703.
The other 8 (MIRANDA, PRESTON, CLARISSA, HENRY, DEAN, ALICE, VERONICA, ALFRED) reuse existing rows with the same English name; this is consistent. The longest name has 8 letters (קריסטינה), within name[TRAINER_NAME_LENGTH + 1] (include/trainer_hill.h:8; TRAINER_NAME_LENGTH is 10).

| Option | How | Risk |
|---|---|---|
| A: nothing more to do | No change. | None. |
| B: add duplicate hill rows for the 8 reused names | Add HILL_TRAINER_7_MIRANDA and the others. | Duplication with no visible effect. |

**Chosen:** A. The rows exist, the tree matches them, and every name fits the 10-byte field.

## Q62

**Question.** 'Tag team' is translated inconsistently across chunks: צוות (B35_01), צוות זוגי (B35_02 and this chunk's Roof owner), צמד (B35_03). The menu term TAG MATCH = קרב צוות. The glossary needs one term.

*Source:* reviewer question (chunk B37_03)

**Analysis.** This is the same decision as Q12. This chunk (B37_03) already follows it: TrainerHill_Roof_hns:76 'אתה רוצה להקים איתי צוות זוגי!' and :107 'צוות זוגי!' (both live). TrainerHill_Entrance_hns:300 and :307 render 'tag battles' as 'קרבות צוות', which is consistent with TAG MATCH 'קרב צוות'. The inconsistency the reviewer saw is in other chunks: the 15 bare-צוות units in Q12 and the 8 'צמד' lines in Q17.

| Option | How | Risk |
|---|---|---|
| A: Adopt 'צוות זוגי' / 'שותף לצוות' / 'קרב צוות' project-wide (the Q12 and Q17 edits) | No edits of its own. The Q12 and Q17 edit lists cover every remaining unit, so each edit is applied once. | None beyond Q12 and Q17. |
| B: Change the Trainer Hill lines to another term | Edit TrainerHill_Roof_hns:76 and :107. | Pointless churn on lines that already use the majority term. |

**Chosen:** A. The Trainer Hill owner's lines already use the chosen term. Repeating the Q12 and Q17 edits under this id would apply them twice.

## Q66

**Question.** JOHN DOE (trainer_hill.h@3480#170) is still in English. The glossary has no 'JOHN DOE' row. The chunk's 'names' map lists JOHN = ג'ון, but that comes from TRNAME_JOHN, a different trainer inherited from FireRed. Spelling DOE would mean inventing a transliteration, which STYLE.md section 3 forbids. Should this stay in English, become ג'ון דו (I'd need a glossary row for DOE), or become a Hebrew placeholder name such as פלוני אלמוני (too long for the 10-byte name field, so it would need shortening)?

*Source:* reviewer question (chunk B37_04)

**Analysis.** Already resolved. src/data/battle_frontier/trainer_hill.h:3480 is ג'ון דו, and the HILL_TRAINER_26_JOHN_DOE row (glossary.csv:6336 at HEAD bb8db5c703) records it. JOHN is FireRed's ג'ון, and DOE /doʊ/ is דו. The name is 7 bytes, within name[TRAINER_NAME_LENGTH + 1] (include/trainer_hill.h:8). The names_check review that was just applied also kept it. ג'ון דו is how Hebrew subtitles and the press write the placeholder name.

| Option | How | Risk |
|---|---|---|
| A: keep ג'ון דו | No change. | None. |
| B: פלוני | Replace it with the Hebrew placeholder word. | On its own, פלוני reads oddly as a name, and the full idiom פלוני אלמוני is 12 bytes, over the limit. |
| C: the English JOHN DOE | Revert. | Latin in a reachable facility. |

**Chosen:** A. The name is applied, recognisable to Hebrew readers, within the limit, and built from the canonical JOHN.

## Q67

**Question.** BREYDEN (#156), LUCIANA (#177) and GAVITE (#233) are Trainer Hill trainer names with no glossary row. Following STYLE.md section 3, I left them in English, as the sibling chunks B37_01, B37_02 and B37_03 do for other unknown names. If they should be in Hebrew, someone needs to add glossary rows first (BREYDEN also appears in B37_05).

*Source:* reviewer question (chunk B37_04)

**Analysis.** The rows exist and are applied:
- BREYDEN בריידן at trainer_hill.h:3202 and :7678 (glossary.csv:6334 and :6363 at HEAD bb8db5c703).
- LUCIANA לוסיאנה at :3609 (glossary.csv:6337).
- GAVITE גאבייט at :4732 (glossary.csv:6343; it was :6348 before the glossary commit).
GAVITE has a real problem: גאבייט is letter for letter the species GABITE (src/data/pokemon/species_info/gen_4_families.h:4338; glossary.csv:657). In English the two names differ by one letter; in Hebrew they are identical, so a player who knows the Pokémon reads the trainer as 'Gabite'.
The row's notes are also cut off mid-word ('… 6 chars. FLAG: sam'). The full text in hns-tools/scratch/gaps/names2.json raises exactly this collision and suggests גאווייט. The names_check review that was just applied kept גאבייט, but it saw only the truncated note, and its reason does not mention the collision.

| Option | How | Risk |
|---|---|---|
| A: keep גאבייט | Only repair the truncated note. | A trainer has exactly the spelling of a dragon Pokémon, which looks like a bug to Hebrew players. |
| B: גאווייט | Medial v is written וו, as in the glossary's GAVIN גאווין (rules §2: ב unless the family uses וו). -ITE stays ייט (FR DRAGONITE דרגונייט). 7 bytes, within TRAINER_NAME_LENGTH 10. Rewrite the note in full. | It drops the ב chunk shared with HILL_TRAINER_67_GAV גאב (glossary.csv:6373). The two are separate trainers, so the cost is cosmetic. The spelling still differs from גאבייט by one letter, so any GABITE pun survives, as in English. |
| C: גאוויט (triage) | Use a single י in the final syllable. | It reads GAV-eet and ignores the -ITE = ייט precedent. |

**Chosen:** B. It makes the /v/ sound unambiguous and ends the exact clash with a species name, while keeping the one-letter resemblance the English has. The cost is one string and one row, and it closes the flag that the truncated note hid from the names_check review. BREYDEN and LUCIANA need nothing more.

*Changed:* `src/data/battle_frontier/trainer_hill.h`, `translation/hebrew/glossary.csv`

## Q74

**Question.** If you want these names in Hebrew, these are my proposed glossary rows (trainer_name, 10-byte limit from u8 name[11] in include/trainer_tower.h:8). JOS & ANNE ג'וס ואן (ANNE=אן as in FireRed's ELI & ANNE). EMY & ALEK אמי ואלק. JO & HALEY ג'ו והיילי (JO=ג'ו as in JO&ZOE; HAYLEE/HAYLIE are היילי in B37_01; 10 bytes, at the limit). GABRIEL גבריאל and CHELSEA צ'לסי, the spellings B37_01 already uses. NICOLAS ניקולס. RIC & RENE ריק ורנה (RICK=ריק; RENE is the female half of a Crush Kin pair). JEN & KIRA ג'ן וקירה. ISAC & MAG אייזק ומג (MEG=מג). Every one is 10 bytes or less and 25 to 42 px in FONT_NORMAL.

*Source:* reviewer question (chunk B38_01)

**Analysis.** These names (JOS & ANNE, EMY & ALEK, JO & HALEY, NICOLAS, RIC & RENE, JEN & KIRA, ISAC & MAG) are in src/trainer_tower_sets.c, which Heart & Soul cannot reach. I re-checked the evidence at HEAD:
- The data is read only by src/trainer_tower.c:453 (gTrainerTowerFloors).
- The only scripts that start it are in the FRLG Sevii maps (TrainerTower_*_Frlg, SevenIsland_*_Frlg, data/scripts/trainer_tower.inc).
- The Seagallop ferry to Seven Island (src/seagallop.c:76) is offered only from the *_Frlg harbor maps.
- No *_hns map.json or scripts.inc references MAP_SEVEN_ISLAND* or MAP_TRAINER_TOWER*.
- Re-run: a breadth-first search over warps, connections and MAP_ constants in the scripts, from all 560 *_hns maps, reaches 1013 maps and none of them.
The project already records this as deliberate: tools/hebrew/status_report.py:36 lists the file under KEPT_LATIN, and STATUS.md:608 reads '36 kept in Latin: Trainer Tower data, which Heart & Soul cannot reach'. The file has 42 Latin name fields, 18 Hebrew ones (filled from existing rows) and two placeholders.
For the record, if the tower is ever wired up, the spellings would be the triage's: ג'וס ואן, אמי ואלק, ג'ו והיילי (10 bytes, at the name[11] limit; include/trainer_tower.h:8), ניקולס, ריק ורנה, ג'ן וקירה and יצחק ומג (ISAC as FireRed's ISAAC, trainers.h:2079).

| Option | How | Risk |
|---|---|---|
| A: keep the Trainer Tower names in Latin | No change. The KEPT_LATIN entry and the STATUS.md line already document it. | None for players, because the content is unreachable. |
| B: add 7 pair and single rows and apply them | Add trainer_name rows in the 'X וY' form and edit 14 name fields. | Low technical risk, but it adds unchecked proposed names that no player will see. |

**Chosen:** A. No player benefits, and it matches the documented decision for unreachable content.

## Q75

**Question.** Policy clash between parallel reviewers in this run. The B37_01 reviewer transliterated 134 frontier trainer names that have no glossary row, including CHELSEA=צ'לסי and GABRIEL=גבריאל. The B37_02 reviewer and this chunk kept such names in English. Other chunks still have the same kind of English names: B37_s01, B37_02, B38_s01 (COLE, JAC, MILY, JORDY), B38_02 (TRENTON, BRENNAN, LORENZO) and B38_03 (AXE & REN). One rule should be picked for all of them. The cleanest way is to add glossary rows and fill the names with apply_names.py.

*Source:* reviewer question (chunk B38_01)

**Analysis.** The policy was chosen and applied: reachable facilities got proposed rows and Hebrew names.
- Battle Frontier: 320 frontier_trainer rows, and battle_frontier_trainers.h has no Latin names left.
- Battle Tent: 86 tent_trainer rows; battle_tent.h is 90 of 90 Hebrew (checked by script).
- Trainer Hill: 56 hill_trainer rows; trainer_hill.h has 64 of 64 Hebrew (checked by script).
Trainer Tower (src/trainer_tower_sets.c) is the only exception. It is unreachable: the re-run map search from the 560 *_hns maps reaches 1013 maps and no Seven Island or Trainer Tower map (details in Q74). It is in KEPT_LATIN (tools/hebrew/status_report.py:36). The triage's note still holds: C name fields are applied by re-cutting chunks (make_chunks.py/units.py), not by apply_names.py, which handles only the .party files and region_map_sections.json (apply_names.py:2-4).

| Option | How | Risk |
|---|---|---|
| A: keep the applied rule: rows for reachable facilities, Trainer Tower stays Latin | No change. | None. |
| B: extend the rule to Trainer Tower | Add about 25 rows and apply them to 42 fields. | Work and review load for content no player sees. |

**Chosen:** A. The clash is settled for everything a player can reach, and the one exception is documented in the tooling and in STATUS.md.

## Q78

**Question.** To clear those warnings, add these as glossary rows. Proposed spellings, following transliteration_rules.md: טרנטון, קמרין, נטליה, קתלין, בריידן, אליסון, אלברטו, קט & קיפ, גב&מייגן, פריסילה, שרלוט (French ch = ש, as MICHELLE = מישל), שנאייה, ברנן, עמנואל (familiar Hebrew form, as SAMUEL = שמואל), ג'רט, לורנזו. All are within the 10-byte name[11] limit. Once the rows exist, the same merge step will fill them in.

*Source:* reviewer question (chunk B38_02)

**Analysis.** Every name in this question that is still Latin is a Trainer Tower name in src/trainer_tower_sets.c: CAMRYN, NATALIA, KATHLEEN, ALLYSON, ALBERTO, PRISCILLA, CHARLOTTE, KAT & KIPP and GEB&MEGAN. That file is unreachable and deliberately kept in Latin (Q74; status_report.py:36; STATUS.md:608).
The names that already had rows are Hebrew there with the glossary spellings, which won over the chunk's proposals: טרנטון, שאנייה, ברנן, עמנואל, ג'ארט, לורנצו and בריידן (one occurrence each).
CAMRYN קמרין (TENT_TRAINER_25_CAMRYN, glossary.csv:6255) and NATALIA נטליה (CONTEST_OPPONENT_NATALIA_TRAINERNAME, :6135) now exist elsewhere and could be reused if the tower is ever done. Pairs would use the 'X וY' form, for example קט וקיפ and גב ומייגן (KIPP קיפ and MEGAN מייגן exist).

| Option | How | Risk |
|---|---|---|
| A: keep the remaining Trainer Tower names in Latin | No change. | None for players. |
| B: add rows for KATHLEEN קתלין, ALLYSON אליסון, ALBERTO אלברטו, PRISCILLA פריסילה, CHARLOTTE שרלוט and the two pairs, then apply them | About 7 rows and 9 field edits. | More unchecked proposed names for content no player sees. |

**Chosen:** A. Same reason as Q74: the content is unreachable, the exception is documented, and the glossary spellings were already used where they existed.

## Q79

**Question.** Decision for you: should the pair names (KAT & KIPP, GEB&MEGAN) be translated only once both halves have glossary rows? KIPP (קיפ) and MEGAN (מייגן) are in the glossary, but KAT and GEB are not, and translating only half would mix Hebrew and Latin in one name. I left both pairs fully in English. GEB is also unclear: hard g (גב) or soft g (ג'ב)?

*Source:* reviewer question (chunk B38_02)

**Analysis.** The pair-assembly part is settled. The glossary stores each pair as its own row (TRNAME_AMYMAY AMY&MAY = איימי ומיי, glossary.csv:5419), so a pair is never put together from halves.
KAT & KIPP, GEB&MEGAN and KATI & GEB are all Trainer Tower names in src/trainer_tower_sets.c, two fields each, which is unreachable and kept in Latin (Q74). So the GEB question does not affect the ROM.
For the record: GEB has a hard g. The Egyptian god Geb is written גב in Hebrew, and rules §2 say to go by sound. But a bare גב is also the everyday word 'back' and reads /gav/; that is why HILL_TRAINER_67_GAV added an א (גאב, glossary.csv:6373). A future pass should weigh this.

| Option | How | Risk |
|---|---|---|
| A: keep the pairs in Latin, with GEB recorded as hard g (גב) for any future pass | No change. | None. |
| B: add 'GEB&MEGAN' = גב ומייגן and 'KATI & GEB' = קייטי וגב now | 2 rows and 4 field edits. | The content is invisible, and this adds proposed names to review. |

**Chosen:** A. The content is unreachable, so the spelling has no effect on players. The hard-g answer and the גב homograph caveat are recorded for later.

## Q81

**Question.** Trainer Tower names AXE & REN (twice), CAMDEN, ZACKERY and MIKAELA are not in glossary.csv, so they stay in English per STYLE.md section 3. checkunits flags each one with a NOHEBREW warning. They need trainer_name glossary rows; ZACKERY and MIKAELA have a double-transliteration risk, so please decide the spellings. The other B38 chunks also leave unlisted names like these in English.

*Source:* reviewer question (chunk B38_03)

**Analysis.** AXE & REN (2 fields), CAMDEN, ZACKERY and MIKAELA are still Latin in src/trainer_tower_sets.c. They are Trainer Tower names, and the tower is unreachable and deliberately kept in Latin (Q74; status_report.py:36; STATUS.md:608). For a future pass, the spellings would be:
- AXE & REN: אקס ורן.
- CAMDEN: קמדן.
- ZACKERY: זכריה, its familiar Hebrew form under §5 (Zachary comes from Zechariah), the way FireRed made ISAAC יצחק. The alternative is זאקרי.
- MIKAELA: מיכאלה, in line with TRNAME_MICHAEL מיכאל (glossary.csv:5294).

| Option | How | Risk |
|---|---|---|
| A: keep them in Latin | No change. | None for players. |
| B: add the 4 rows and apply them | 4 trainer_name rows and 5 field edits. | Unchecked proposed names for content no player sees. |

**Chosen:** A. Same as Q74. The spellings are recorded so that a later pass does not have to decide them again.

## Q83

**Question.** Alola_Akala_Totem_sign_Text_0 keeps the line break after אנרגיה, copying the English's own awkward break and matching B38_04 and B38_05. A cleaner split would be מהטוטם נובעת\nאנרגיה חזקה…, but it should change in all three islands together.

*Source:* reviewer question (chunk B38_03)

**Analysis.** The totem sign has 4 identical copies: AkalaIsle_hns/scripts.inc:528-529, MelemeleIsle_hns:773-774, PoniIsle_hns:406-407, UlaUla_Forest_hns:358-359. Each breaks 'מהטוטם נובעת אנרגיה\nחזקה…\p', which separates the noun from its adjective. That copies the English break ('a strong\n energy'), which works in English but not in Hebrew.

| Option | How | Risk |
|---|---|---|
| (a) Move the \n: 'מהטוטם נובעת\nאנרגיה חזקה…' in all 4 | 8 one-line edits: 69/208 and 66/200 px | None. STYLE §5 allows moving \n, and the pages are unchanged |
| (b) One line: 'מהטוטם נובעת אנרגיה חזקה…\p' | Merge the lines (deletes a line in each file), 138 px | Drops a line from the English layout, and a line deletion is riskier to apply |
| (c) Keep | No change | An awkward orphaned adjective |

**Chosen:** (a). The noun and adjective stay together, both lines fit easily, and the 4 copies stay identical.

*Changed:* `data/maps/AkalaIsle_hns/scripts.inc`, `data/maps/MelemeleIsle_hns/scripts.inc`, `data/maps/PoniIsle_hns/scripts.inc`, `data/maps/UlaUla_Forest_hns/scripts.inc`

## Q84

**Question.** The hiking claim is worded differently on different islands: Akala's hiker says הטיולים הכי טובים and Ula'ula's (B38_05) says יש את מסלולי ההליכה הכי טובים. Both are fine; aligning them is a style call.

*Source:* reviewer question (chunk B38_03)

**Analysis.** The English line is the same on both islands. AkalaIsle_hns:559 is 'באי אקאלה הטיולים הכי טובים!\n' (English 'AKALA ISLE has the best hiking!\n'). UlaulaIsle_hns:363-364 is 'באי אולאולה יש את מסלולי הטיול\nהכי טובים!\p', which spreads a one-line English page (English :362 'ULA'ULA ISLE has the best hiking!\p') over two lines. Elsewhere the islanders' rivalry joke uses a single frame: Akala's swimmers say 'באי אקאלה החופים הכי טובים!' / 'באי אולאולה החופים הכי טובים!' (AkalaIsle_hns:594, :605). Implementation correction: the line-364 edit as written (old '.string "הכי טובים!\p"' → '') would leave a tab-only line inside the unit. drift.py's split_inc tolerates that, but units.py parse_script (units.py:46-70) stops a block at the first non-.string line. The label would then split into two units (…Text_2 and …Text_2#2), which breaks extract/status pairing against the English. The whole line, including its newline, must be removed.

| Option | How | Risk |
|---|---|---|
| (a) Ula'ula = 'באי אולאולה הטיולים הכי טובים!\p', and delete line 364 entirely | Rewrite :363 and remove :364 (line and newline). 151/200 px, one line like the English | Low. The page count is unchanged (one \p), and the token list is empty |
| (a') Same wording, no line deletion: ':363 באי אולאולה הטיולים\n', ':364 הכי טובים!\p' | 2 in-place edits | Keeps an extra line the English does not have, and breaks a short sentence across two lines |
| (b) Make Akala match Ula'ula's longer wording | Rewrap AkalaIsle_hns:559 | Longer, and breaks the parallel with the swimmers' lines |
| (c) Keep both | No change | The repeated-boast joke is weakened |

**Chosen:** (a). It restores the identical rival boast and the English one-line page, with a shorter line. The deletion is safe as long as no blank line is left behind.

*Changed:* `data/maps/UlaulaIsle_hns/scripts.inc`

## Q85

**Question.** Game Boy Advance: I followed FireRed's NPC wording, 'גיים בוי אדוונס'. B39_03 (sText_EnsureGBAConnectionMatches) keeps the Latin 'Game Boy Advance' in system text. Should NPC dialogue use the Hebrew and system text the Latin, or should one form be used everywhere?

*Source:* reviewer question (chunk B38_04)

**Analysis.** The tree is split. Hebrew 'גיים בוי אדוונס' is at Melemele_House_6_hns/scripts.inc:25 and :28. Latin is at src/berry_fix_program.c:45 ('ה-Game Boy Advance שלך תואם לתמונה.') and :55 ('ה-Game Boy Advance.'), and at src/strings.c:951 (gJPText_SelectConnectWithGBA, inside an already-translated quote: ”תקשורת עם\nGame Boy Advance”). FireRed's canon is Hebrew (pokefirered-heb CeladonCity_Condominiums_RoofRoom/text.inc:5 'שבתוך הגיים בוי אדוונס שלך!'), and FireRed also transliterates the brand 'גיים פריק' (strings.c:974). The glossary has no row. Both windows are 28 tiles = 224 px (berry_fix_program.c:96 WIN_MSG_BODY; mystery_gift_menu.c:120), and the Hebrew is narrower: 164 vs 192 px, 78 vs 106 px and 77 vs 99 px. The remaining Latin mention in a map, BattleTowerLobby_hns:1269 (ExplainLinkMultisChallenge_hns), is in tools/hebrew/data/live_labels.json's 'dead' list. The Latin kept on the berry-fix screen is the cartridge titles (Ruby/Sapphire, Emerald), which STATUS.md:531 records as deliberate.

| Option | How | Risk |
|---|---|---|
| (a) 'גיים בוי אדוונס' everywhere, with a glossary term row | 3 edits plus 1 glossary row | None. Everything is narrower than the Latin |
| (b) Hebrew in dialogue, Latin in system screens | No edit, but document it | The same device has two names, and the e-Reader quote mixes scripts |
| (c) Latin everywhere | Edit Melemele_House_6 | Goes against FireRed and is less readable in NPC speech |

**Chosen:** (a). It follows FireRed, uses one name throughout, and reads more naturally for Hebrew players. The prefix attaches directly, per STYLE §4.

*Changed:* `src/berry_fix_program.c`, `src/strings.c`

*Glossary:* `TERM_GAME_BOY_ADVANCE`

## Q86

**Question.** HAU'OLI CITY (SamsonOak_Trigger_Beginning_Text_4) and ELIO (House5_Mom) are not in the glossary, so they stay in Latin. Suggested rows: 'העיר האואולי' and 'אליו'. Note that 'אליו' also reads as the word 'to him', so an alternative such as 'אֶליוֹ' without nikud needs a decision.

*Source:* reviewer question (chunk B38_04)

**Analysis.** Still open.
- data/maps/MelemeleIsle_hns/scripts.inc:723 reads 'היא דומה באופן מוזר לעיר HAU'OLI'. The English is :724, 'HAU'OLI CITY in ALOLA'.
- data/maps/Melemele_House_5_hns/scripts.inc:46 reads 'עם הבן שלי, ELIO.' (English :46).
Both maps are live; STATUS.md:235 and :239 list them as seen on screen. Neither name has a row, and no other string in data/ or src/ uses them.
ULA'ULA ISLE is האי אולאולה (glossary.csv:4950), which writes the Hawaiian glottal stop ' as א, not a geresh. HAU follows rules §3 (/aʊ/ = או). So HAU'OLI = ה + או + א + ולי = האואולי, and CITY = העיר X (rules §5).
ELIO by the rules is אליו: initial e = א, and -io = יו as in Hebrew מריו and אנטוניו. It is a homograph of 'to him', but a name set off by a comma after 'הבן שלי' at the end of the sentence reads clearly as a name.
I applied both edits to a scratch copy and ran drift.py: ok, and the LATIN warnings for HAU'OLI and ELIO are gone.

| Option | How | Risk |
|---|---|---|
| A: העיר האואולי, and ELIO = אליו | Add PLACE_HAUOLI_CITY and NAME_ELIO and apply both. Widths: 162 px at :723 (the line ends in \n, budget 208) and 81 px at :46 (it ends in \p, budget 200). | None technically. אליו is ambiguous for a moment, but the apposition resolves it. |
| B: העיר האואולי, and ELIO = אליאו | The same, but spell the name with an extra א to avoid the homograph. | A nonstandard spelling; Hebrew writes -io names with יו. |
| C: keep both in Latin | No change. | Latin inside Hebrew on live maps. |

**Chosen:** A. האואולי follows the ULA'ULA precedent for the glottal stop and the rules for /aʊ/. אליו is the standard Hebrew spelling of Elio, and the comma after 'הבן שלי' makes it read as a name.

*Changed:* `data/maps/MelemeleIsle_hns/scripts.inc`, `data/maps/Melemele_House_5_hns/scripts.inc`

*Glossary:* `PLACE_HAUOLI_CITY`, `NAME_ELIO`

## Q89

**Question.** Samson's line about the real MELEMELE ISLAND (Trigger_Beginning_Text_4) adds 'שבאלולה' to tell it apart from this game's MELEMELE ISLE, because both are 'האי מלמלה' in Hebrew. Is this clarifying addition acceptable?

*Source:* reviewer question (chunk B38_04)

**Analysis.** MelemeleIsle_hns/scripts.inc:725-726 is 'כל האי הזה מזכיר לי את\nהאי מלמלה שבאלולה…$' (English 'This whole island reminds me of MELEMELE\nISLAND…$'). The player is standing on MAPSEC MELEMELE ISLE = 'האי מלמלה' (glossary.csv:4948), so without the addition Samson would say the island reminds him of itself. The sentence before already uses the same frame, 'לעיר HAU'OLI\nשבאלולה' (:723-724, English 'HAU'OLI CITY in\nALOLA'), so 'שבאלולה' is parallel and adds no new facts. The Latin HAU'OLI on :723 is a separate issue (Q86) and is not touched here.

| Option | How | Risk |
|---|---|---|
| (a) Keep 'האי מלמלה שבאלולה' | No change | None |
| (b) 'האי מלמלה האמיתי' | Edit :726 | Implies that this island is fake |
| (c) Drop the addition | Edit :726 | Nonsensical in Hebrew: the island reminds him of itself |

**Chosen:** (a). It restores the ISLE/ISLAND distinction that the shared Hebrew mapsec name erases, and it echoes the sentence before it.

## Q93

**Question.** "demake" is translated as גרסת רטרו. Is that acceptable, or is a different term preferred?

*Source:* reviewer question (chunk B38_05)

**Analysis.** 'demake' appears in UlaUla_House_hns/scripts.inc:187 and UlaulaIsle_hns:323 as 'אני עובד על גרסת רטרו מלאה של\nהאזור, שנקראת אולטרה אקליפס.' (English 'I'm working on a full demake of the'). The developer office (CeladonCity_Apartments_2F_hns, CeladonMansion2F_Text_Phant 'I love DEMAKES!') also says DEMAKES. That file's text is dead: the room has no objects, triggers or signs (its map.json lists none) and none of its 16 labels is referenced outside the file, so it is outside this decision. If upstream adds the NPCs later, they should use the same term.

| Option | How | Risk |
|---|---|---|
| (a) Keep 'גרסת רטרו' | No change | None |
| (b) Loanword 'דימייק' | Edit 2 lines | Only ROM-hack insiders know it |
| (c) 'גרסה בסגנון GBA' | Edit 2 lines | Longer, and adds Latin |

**Chosen:** (a). Hebrew has no established term, and 'retro version' is clear to every player and keeps the meaning.

## Q95

**Question.** Hiker battle intro "You must be tough to handle this rough terrain!" is kept impersonal (צריך להיות קשוח...), reading it as a requirement. The other reading is a deduction about the player (אתה בטח קשוח אם...). Which one is intended?

*Source:* reviewer question (chunk B38_05)

**Analysis.** Hiker battle intro, UlaulaIsle_hns/scripts.inc:355-356: 'צריך להיות קשוח כדי להתמודד\nעם השטח הקשה הזה!' (English :356 'You must be tough to handle this\nrough terrain!'). Correction: the decision read the English as a deduction about the player and cited Akala_Cave_hns:109 as precedent. The Akala English is a different construction: 'You must be tough IF you made it all the way up here!' (English Akala_Cave_hns:109). The 'if' clause forces the deduction, so 'אתה בטח קשוח אם הצלחת…' is right there. 'You must be X to Y', with a bare infinitive, is the requirement idiom ('you must be 18 to enter'): the hiker is boasting about the terrain, and that implicitly challenges the player. The current impersonal Hebrew says exactly that. STYLE §2 says that where a line can be rephrased naturally to avoid second-person gender (impersonal 'צריך…'), that wording is preferred. The current line is already that rephrasing, it is natural, and it fits (153 px would also have fit, so width is not the issue).

| Option | How | Risk |
|---|---|---|
| (a) Deduction: 'אתה בטח קשוח אם אתה מתמודד\nעם השטח הקשה הזה!' | Edit :355 only, 153/208 | Picks the less likely reading of 'must be X to Y', and adds masculine second person where STYLE §2 prefers impersonal wording |
| (b) Neutral maxim: 'רק קשוחים מסתדרים\nבשטח הקשה הזה!' | Rewrite 2 lines | Rephrases more than needed; the current line already is neutral |
| (c) Keep the impersonal wording | No change | None. It follows the English requirement reading and STYLE §2 |

**Chosen:** (c). The English infinitive construction states a requirement. The Akala Cave line differs ('if you made it'), so it is not a precedent. The current impersonal Hebrew is faithful and natural, and it is the gender-neutral wording STYLE §2 asks for. Changing it would only add a second-person masculine.

## Q101

**Question.** The GREETINGS menu item (sText_Greetings) is 'ברכות', and sText_ShowTrainerCardMale quotes it ('בתור ”ברכות”'). I kept it because the easy-chat group GREETINGS already uses 'ברכות' (src/data/easy_chat/easy_chat_groups.h:57). On its own, though, 'ברכות' reads as 'congratulations' (gText_LeagueChamp uses it that way, src/strings.c:128). 'היכרות' or 'ברכת שלום' would say 'swap trainer cards to say hello' more clearly. Should the menu item, this dialogue line and the easy-chat group name all change together?

*Source:* reviewer question (chunk B39_02)

**Analysis.** Confirmed in the current tree:
- the Union Room menu item src/data/union_room.h:541 sText_Greetings is 'ברכות';
- the male quote :259 is 'בטח! בתור ”ברכות”,\nהנה כרטיס המאמן שלי.';
- the easy-chat group name src/data/easy_chat/easy_chat_groups.h:57 is 'ברכות'.
FireRed precedent: gEasyChatGroupName_Greetings = 'ברכות' (pokefirered-heb src/strings.c:1193). FireRed left its Union Room strings in English (src/union_room_message.c:256, :513), so there is no other precedent.
The tree already uses 'ברכות' to mean greetings in data/text/cable_club.inc:395 and data/scripts/cable_club_frlg.inc:1623 ('להחליף ברכות'). The easy-chat group holds hello, thank-you and congrats words, so 'היכרות' would be wrong for it.
The 'congratulations' reading came only from gText_LeagueChamp (src/strings.c:128), which Q6 changes to 'מזל טוב!'. After Q6, the only bare 'ברכות' left are greetings, plus 'וברכות' meaning blessings in two Pokédex entries.

| Option | How | Risk |
|---|---|---|
| A: Keep 'ברכות' in all three | No text edits; add a glossary row to lock the term. | None. After Q6, a bare 'ברכות' is used only for greetings. |
| B: Change all three to 'היכרות' | Edit union_room.h:541 and :259, and easy_chat_groups.h:57. | Wrong for the easy-chat group, which is a word category (hello, thanks, congrats), not an introduction. It also breaks the FireRed group name. |
| C: Change only the Union Room item and its quote to 'היכרות' | Edit union_room.h:541 ('היכרות') and :259 ('בתור ”היכרות”'). | Splits one English term into two Hebrew words. The female line ('כדי להציג את עצמי') already carries the 'introduction' sense. |

**Chosen:** A. It matches FireRed's group name and the tree's existing 'להחליף ברכות'. In a menu next to 'קרב' and 'צ'אט' it reads as 'greetings', and Q6 removes the only competing reading. Zero edits, zero risk.

*Glossary:* `TERM_GREETINGS`

## Q106

**Question.** Several names are missing from glossary.csv, so they stay in English as STYLE §3 requires: BRINEY ('קפטן BRINEY'), PETALBURG ('במכון של PETALBURG'), RUSTBORO ('בעיר RUSTBORO') and MAXIE (the 'MAXIE:' speaker prefix, twice). They need glossary rows; MAXIE is the most visible because it is a speaker name.

*Source:* reviewer question (chunk B39_03; merged, checkunits: 116 units, 0 errors))

**Analysis.** BRINEY is live. data/text/event_ticket_2.inc:35 ('קפטן BRINEY יכול להיות'; English 'CAPT. BRINEY can be so maddeningly') is FarawayIsland_Entrance_Text_SailorReturn. It is shown from BattleFrontier_OutsideWest_hns/scripts.inc:13 and FarawayIsland_Entrance_hns/scripts.inc:22, both seen on screen (STATUS.md:73, :145).
The same Latin name is in 3 more Hebrew strings: data/text/match_call.inc:2339 and :2460 ('מר BRINEY'), and src/landmark.c:22 ('הבקתה של מר BRINEY'). There is no BRINEY row.
MAXIE has a row, NAME_MAXIE = מקסי (glossary.csv:6462 at HEAD bb8db5c703), and src/strings.c:16 uses it. Two speaker prefixes in data/maps/MossdeepCity_SpaceCenter_2F/scripts.inc, :464 and :478, still read 'MAXIE:', while STEVEN in the same file (:484) is already סטיבן.
PETALBURG and RUSTBORO are in 15 Hebrew strings: match_call.inc (12), Mossdeep 2F:490, landmark.c:21 and mystery_event_msg.c:3. All of them are vanilla Hoenn content, and other Hoenn names (DEWFORD, SLATEPORT, VERDANTURF) stay Latin consistently.
Correction to the earlier option C: NAME_MAY מיי (:6464) and NAME_BRENDAN ברנדן (:6463) already exist. Yet match_call.inc still has 31 Hebrew lines with Latin 'MAY:' or 'BRENDAN:' prefixes, including the two text boxes edited here (:2338, :2459). That is a separate follow-up.
Reachability: the map search I re-ran from the 560 *_hns maps reaches MAP_MOSSDEEP_CITY_SPACE_CENTER_2F, MAP_MOSSDEEP_CITY and MAP_ROUTE104_MR_BRINEYS_HOUSE. The route is the warp at (39,55) in BattleFrontier_OutsideWest_hns/map.json to vanilla MAP_ARTISAN_CAVE_B1F, which exits to vanilla MAP_BATTLE_FRONTIER_OUTSIDE_WEST. So vanilla Hoenn is reachable in the map graph, though this is not verified on screen and may be gated by flags or tiles.
I applied the 6 edits to a scratch copy and ran drift.py: all 4 files are ok, and the BRINEY and MAXIE LATIN warnings are gone.

| Option | How | Risk |
|---|---|---|
| A: BRINEY only, in the one string confirmed on screen | Add NAME_BRINEY = ברייני and edit event_ticket_2.inc:35. | The same name stays Latin in 3 other Hebrew strings. |
| B: BRINEY everywhere it appears in Hebrew, plus the existing MAXIE row; PETALBURG and RUSTBORO stay Latin | Add NAME_BRINEY = ברייני (BRY-nee: i /aɪ/ = יי, final y = י, rules §3) and make 4 edits. Replace 'MAXIE:' with 'מקסי:' at Mossdeep 2F :464 and :478. Widths: 102 px (:35), 141 px (:2339 and :2460, which end in \p; budget 200), 159 px (:464) and 62 px (:478); the landmark is 95 px, shorter than the Latin it replaces. | None. Only name strings and speaker prefixes change. |
| C: B plus a full Hoenn-names pass | Add rows for PETALBURG פטלבורג, RUSTBORO רסטבורו, DEWFORD, SLATEPORT, VERDANTURF, PEEKO, STONE and others, apply them in about 25 strings, and apply the existing NAME_MAY and NAME_BRENDAN rows to the 31 match_call.inc speaker prefixes. | A larger set of new proposed names for vanilla Emerald content whose reachability in Heart & Soul is unverified. |

**Chosen:** B. Once a row exists, STYLE §3 has the glossary win everywhere, so BRINEY should not be Hebrew in one string and Latin in three. The MAXIE row already exists, so applying it costs two edits and matches STEVEN in the same file and strings.c:16. That vanilla Hoenn is reachable in the map graph makes these edits more worthwhile, not less. Leaving the Hoenn city names in Latin keeps 15 strings consistent until a Hoenn-names pass is decided. The 31 MAY:/BRENDAN: prefixes are outside this question and belong to that pass.

*Changed:* `data/maps/MossdeepCity_SpaceCenter_2F/scripts.inc`, `data/text/event_ticket_2.inc`, `data/text/match_call.inc`, `src/landmark.c`

*Glossary:* `NAME_BRINEY`

## Q111

**Question.** Several sibling strings in src/battle_debug.c are in no unit chunk, so they stay in English inside the Hebrew menus: main list 'Moves', 'PP', 'Types', 'Stats', 'AI'; Stats list 'Speed'; Status1 list 'Sleep', 'Burn'; Volatiles 'Rage', 'Root', 'Yawn'; Side Status 'Mist', 'Swamp'; AI flags 'Risky', 'Stall'. Should they be added to a chunk? Suggested Hebrew: מהלכים, נ”כ, סוגים, נתונים, מהירות, שינה, כוויה, ערפל (Mist per the glossary). The Hebrew for Rage/Root/Yawn would come from the glossary move rows, which were not looked up here.

*Source:* reviewer question (chunk B39_04)

**Analysis.** The analysis is confirmed. All 14 strings are still Latin, and each old substring occurs exactly once at its line: :315 Moves, :318 PP, :319 Types, :320 Stats, :340 Speed, :347 Sleep, :349 Burn, :364 Rage, :383 Root, :384 Yawn, :413 Mist, :420 Swamp, :429 Risky, :438 Stall.

The windows:
- Main list: 9 tiles wide (:522-531) with item_X 8, so 64 px.
- Secondary lists: 20 tiles (:533-542), so 152 px.
- Both use fontId 1, FONT_NORMAL.

The sources check out:
- TERM_MOVE מהלך (glossary.csv:5511), TERM_PP נ”כ (:5508, U+201D) and TERM_TYPE סוג (:5514).
- 'נתונים' as stats: battle_debug.c:321 'דרגות נתונים', battle_z_move.c:98, battle_message.c:208 and :332, and FireRed's move descriptions. The glossary has no TERM_STAT row yet.
- gText_Speed מהירות (strings.c:1079); gText_Sleep שינה and gText_Burn כוויה (battle_message.c:1441 and :1443).
- MOVE_RAGE זעם (:2402), MOVE_INGRAIN השתרשות (:2578), MOVE_YAWN פיהוק (:2584), MOVE_MIST ערפל (:2357).
- STRINGID_SWAMPENVELOPEDSIDE 'ביצה טובענית' (battle_message.c:829). TERM_EGG is ביצה (:5500), so a bare ביצה would read as Egg.
- AI_FLAG_RISKY 'behave more recklessly' and AI_FLAG_STALL 'stalls battle' (include/constants/battle_ai.h:12 and :23). ABILITY_STALL השהיה (:3338) means 'moves last', which is something else.

Widths (FONT_NORMAL):
- Main list: 36, 16, 25 and 28 px, all within 64.
- Secondary lists: 33, 21, 22, 19, 44, 26, 26, 64, 65 and 48 px, all within 152. The AI-flag list already holds a 115 px label.

All edits apply on a scratch copy, and drift.py reports ok.

| Option | How | Risk |
|---|---|---|
| A. Translate the 14 labels with the glossary and in-game forms | The 14 edits below. The AI flags become noun phrases like their neighbours ('ניסיון לחסל', 'בדיקת כדאיות', 'הקרבה עצמית'): 'לקיחת סיכונים' and 'משיכת זמן'. | Low. Text only, with no tokens, and every label fits and encodes. |
| B. As A, but use the ability name 'השהיה' for Stall | Change :438 to 'השהיה'. | It misleads. השהיה is ABILITY_STALL ('moves last'), not the AI's stalling strategy. |
| C. Leave them in English | No change. | The lists stay mixed. This is consistent only if Q118 reverted the file, and it did not. |

**Chosen:** A. Q118 keeps the menu in Hebrew. Every label comes from a glossary row or a string players already see in battle, except the two AI flags. For those, the wording follows what the flag actually does rather than borrowing an ability name. 'ביצה טובענית' copies the battle message and avoids the clash with Egg. TERM_STAT is added so that 'נתון/נתונים' (used in FireRed and across this tree) is recorded.

*Changed:* `src/battle_debug.c`

*Glossary:* `TERM_STAT`

## Q112

**Question.** This chunk abbreviates AI as ב”מ (בינה מלאכותית), but the main-list item 'AI' stays Latin, so 'AI' sits next to 'מידע ב”מ' and 'קבוצת ב”מ'. Use ב”מ everywhere, or keep Latin 'AI' throughout? This is a debug menu for developers.

*Source:* reviewer question (chunk B39_04)

**Analysis.** The analysis is confirmed. src/battle_debug.c:326 is exactly {COMPOUND_STRING("AI"), LIST_ITEM_AI}. The three rows under it use ב”מ: :327 'ב”מ נק'/נזק', :328 'מידע ב”מ' and :329 'קבוצת ב”מ'. Their gershayim is U+201D (checked by code point), as STYLE §4 requires. Elsewhere in the tree, ב” occurs only before quotation marks (BattlePyramidLobby:558, GoldenrodDeptStore_3F:36), never as an abbreviation. Widths in FONT_NORMAL against the 64 px main list: 'ב”מ' 20 px, 'בינה מלאכותית' 70 px (too wide). The glossary has no TERM_AI row yet.

| Option | How | Risk |
|---|---|---|
| A. Use ב”מ at :326 | COMPOUND_STRING("AI") → COMPOUND_STRING("ב”מ"), and add a TERM_AI row to the glossary. | Low. One label of 20 px. The three rows under it give the abbreviation its context. |
| B. Latin 'AI' everywhere | Revert :327-329 to forms such as 'מידע AI'. | Medium. It puts LTR runs inside RTL labels and undoes reviewed text, against Q118. |
| C. Spell it out | 'בינה מלאכותית'. | At 70 px it overflows the 64 px window. |

**Chosen:** A. It matches the three ב”מ rows already in the same list, fits easily, and follows Q118's decision to keep the menu in Hebrew. B adds bidi risk and C does not fit.

*Changed:* `src/battle_debug.c`

*Glossary:* `TERM_AI`

## Q118

**Question.** STYLE.md section 5 says not to translate debug-menu strings, but it names only src/debug.c. This chunk is src/battle_debug.c, and the batch translated it. Please confirm the battle debug screen is meant to be in Hebrew.

*Source:* reviewer question (chunk B39_05)

**Analysis.** Checked against the current tree (he/main at 95c35506a0). The analysis holds, with three corrections.

The tree has src/battle_debug.c in Hebrew. It was translated in four commits: 7db86f2f06 (10-12), 57b2a35e4a (10-15), bd09c987a2 (10-18) and 5b1870b7b5 (10-18). 229 of its 251 literals are Hebrew. A scan of every literal outside comments finds exactly 22 with Latin words:
- 15 in the lists: :315 Moves, :318 PP, :319 Types, :320 Stats, :326 AI, :340 Speed, :347 Sleep, :349 Burn, :364 Rage, :383 Root, :384 Yawn, :413 Mist, :420 Swamp, :429 Risky, :438 Stall. These are Q111 and Q112.
- :1440 sTextAll "All", printed at :1481 (Moves) and :1528 (Stat Stages).
- Six hold-effect names: :2196 Repel, :2212 Leek, :2253 Plate, :2257 Drive, :2258 Gems, :2275 Seeds.
The only other Latin is the Z in :2278 "גביש Z". It is deliberate, as in the glossary's פוריגון-Z.

The tools still contradict the tree in three places:
- tools/hebrew/make_chunks.py:26-28: SKIP_FILES contains 'src/battle_debug.c' ("Left in English on purpose ... the debug menus").
- tools/hebrew/status_report.py:21: battle_debug.c is in BLOCKED.
- tools/hebrew/rom_sweep.py:63 (correction: the original analysis missed this one): DEBUG_OBJ = r'(^|/)src/(battle_)?debug\.o$' leaves battle_debug.o out of the default release sweep. Its docstring at :13 says the same.
STYLE.md:77 names only src/debug.c.

Players can reach the screen:
- include/config/debug.h:11 sets DEBUG_BATTLE_MENU TRUE.
- src/battle_controller_player.c:398 opens the menu on SELECT during action selection. The last-used-ball button is R (include/config/battle.h:361).
- inventory.json records 215/215 of the file's literals in the release ROM.

The screen prints game data that is already Hebrew: moves (:1474), abilities (:1487), items (:1492), types (:1501) and stat names (:1509; correction, the analysis said :1507).

Sibling forks (correction): the French fork (fr/fr/main) does not touch battle_debug.c. The ES tag es-2.0.6-v1 translated about 12 of its strings; es/master has none.

Widths, measured with textwidth (which says the RTL renderer ignores the list's lettersSpacing):
- Main list, 64 px: new labels are 16-36 px; the widest existing label is 59.
- Secondary list, 152 px: new labels are up to 65 px.
- Hold-effect columns, FONT_SMALL, 75 px: new labels are up to 41 px; the widest existing is 72.
All strings encode with charmap.txt.

On a scratch copy, all 22 edits applied, and drift.py reported 'ok src/battle_debug.c'.

| Option | How | Risk |
|---|---|---|
| A. Keep the battle debug menu in Hebrew and finish it | Apply Q111's 14 labels and Q112's 'AI', plus the 7 literals below. Then align every tool and STYLE with the tree: remove battle_debug.c from make_chunks SKIP_FILES, from status_report BLOCKED and from rom_sweep's DEBUG_OBJ, and add one sentence to STYLE §5. | Low. Text and tool-config edits only, and every label fits its window. With rom_sweep changed, the default release sweep will cover battle_debug.o and catch any Latin that comes back. |
| B. Revert the file to English, as the SKIP_FILES comment says | Restore src/battle_debug.c from the parent of 7db86f2f06 (equal to pokehns-heb-engine). | Medium. It throws away four reviewed, width-checked commits. A screen that opens with one button would show English labels next to Hebrew move, item, ability and type names. |
| C. Turn off DEBUG_BATTLE_MENU for the Hebrew release | Set include/config/debug.h:11 to DISABLED_ON_RELEASE. | An engine and config change. The Hebrew release would no longer match English 2.0.6 or the ES and French forks. It is a product decision outside translation scope; see Q120. |

**Chosen:** A. The menu opens with a single button in every battle and shows Hebrew game data whatever its labels say, so Hebrew labels are what a player should see. The work is about 90% done and already reviewed against the glossary. The remaining 22 edits are one-word labels taken from the glossary or in-game strings:
- הכול: the full spelling, used 107 times in the tree against 4 for הכל.
- דוחה: ITEM_REPEL, glossary.csv:3663.
- מקל: ITEM_LEEK, :3988.
- לוח: the PLATE chunk, :3799.
- כונן: the DRIVE chunk, :3816.
- אבני חן: the GEM chunk, :3935, in the plural like the English.
- זרעי שטח: SEED זרע, :4046-4049, plus terrain שטח, :4101, the same word as the sibling 'מאריך שטח' at :2274.

The one change to the earlier decision: rom_sweep.py also treats battle_debug.o as an English debug menu, so it gets the same fix. Otherwise the release sweep would keep skipping a file we now ship in Hebrew. The STYLE sentence is reworded slightly ('is translated and uses the glossary's terms').

*Changed:* `src/battle_debug.c`, `tools/hebrew/make_chunks.py`, `tools/hebrew/rom_sweep.py`, `translation/hebrew/STYLE.md`

## Q120

**Question.** STYLE.md excludes src/debug.c, but the overworld debug menu is on in this build (DEBUG_OVERWORLD_MENU TRUE, R+START; notes/harness.md section 6). notes/inventory.md says only 4 debug.c literals are compiled out of the release ROM, so the debug.c text is in the release ROM. If players can reach the menu, does the 'keep English' rule still stand, or should DEBUG_OVERWORLD_MENU be turned off for the Hebrew release? That is an engine and config decision, not a translation one.

*Source:* reviewer question (chunk B40_01)

**Analysis.** The core facts hold. Two supporting claims needed correction.

The R+START menu is in the release ROM:
- include/config/debug.h:5 sets DEBUG_OVERWORLD_MENU TRUE, and src/field_control_avatar.c:165 and :278 open it.
- debug.h is identical in Release-v2.0.6, es-2.0.6-v1, es/master and fr/fr/main.
- data/event_scripts.s:1061 includes data/scripts/debug.inc unconditionally.
- src/debug.c is byte-identical to pokehns-heb-engine (cmp).
- data/scripts/debug.inc has 0 Hebrew lines (counted with Python; a plain grep for [א-ת] gives false hits on é and ×). Commit 1332b08bf1, titled 'Translate data/scripts/debug.inc into Hebrew', only rewrapped English lines.
- STATUS.md:486 shows debug.inc as '74 | 0 | blocked (debug menu, English by design)'. Its 74 units are 2 live plus 72 debug_only (live_labels.json).

The real gap: live_labels.json lists Debug_Text_ArianaDefeat (debug.inc:288-289) and Debug_Text_Grunt23Defeat (:291-292) as live. The story battle at data/maps/RocketHideout_B2F_hns/scripts.inc:305 uses them (multi_2_vs_2 ... PARTNER_LANCE_HNS). No other map uses a Debug_ label. The copies at :342 and :345 (Lance3, Clair3) are reached only from the debug menu.

Speakers and widths:
- Ariana's lines address the player in the masculine singular (scripts.inc:252-274: אתה, לך, תתכונן).
- Grunt 23 is male (trainers_hns.party:2539-2543, 'Pic: Rocket Grunt M Hns').
- Widths in FONT_NORMAL: 'עוד תשמע ממני!' 76 px and 'אני לא מקבל את זה!' 95 px, each one line.
- drift.py on the edited scratch copy reports 'ok data/scripts/debug.inc'.

Corrections:
(1) Upstream history. The config was not a single switch. It went DISABLED_ON_RELEASE (b18de9d182, 2025-07-07), then FALSE (3b889fd542), DISABLED_ON_RELEASE (c49b1509d9 'Revert last for debug'), FALSE (b2366daa11) and TRUE (fc9ba4908e, 2026-08-22). That is four toggles in August 2026, so the intent is unclear. TRUE has shipped in Release-v2.0.2 through v2.0.6.
(2) Sibling forks. The French fork does not touch any debug file. The ES tag es-2.0.6-v1 translated almost all of debug.inc (159 of 168 .string lines, including '¡Aún no has visto mi final!' and '¡No aceptaré esto!'), but only 13 lines of src/debug.c, so its R+START menu labels stay English. The claim that the community HNS_modern ReleaseM2 notes tell players to use the menu could not be checked in this workspace.

Minor: in debug.inc the label Debug_EventScript_DoLanceMultiBattle is at :275 and its multi_2_vs_2 at :276. src/debug.c:581 'Lance Multi' runs Debug_EventScript_Lance_Multi (:265).

| Option | How | Risk |
|---|---|---|
| A. Keep both menus on and keep src/debug.c and debug.inc in English, but translate the two story lines | Translate debug.inc:289 and :292, and make STYLE §5 name the R+START menu with its two exceptions. In status_report.py, move debug.inc from BLOCKED to KEPT_LATIN so the row reflects the 2 translated live strings. | Low. Two .string edits with labels and '$' kept, and no engine change. Behaviour matches English 2.0.6 and both forks. |
| B. Turn the debug menus off for the Hebrew release | Set include/config/debug.h:5 and :11 to DISABLED_ON_RELEASE (include/constants/global.h:13-16). Plain make builds keep the menus; make RELEASE=1 (Makefile:63-75, :179-180) drops them. | Medium. An engine and behaviour change outside translation scope that departs from English 2.0.6 and both forks. The two Rocket Hideout lines would still need translating, because debug.inc stays assembled. |
| C. Translate src/debug.c and all of debug.inc | About 188 C literals and 74 script units. | High cost for a developer tool, with no glossary for flags, vars, EV/IV or SaveBlock text, and a large new surface for width checks. ES translated debug.inc but left its debug.c labels mostly English, so its menu mixes languages. That is not a model to copy. |

**Chosen:** A. A is the only option that stays inside translation scope and keeps the Hebrew release's behaviour identical to English 2.0.6. The two defeat lines are reached in the main story, so they must be Hebrew whatever is decided about the menus.

'עוד תשמע ממני!' is the natural Hebrew for 'you haven't seen the last of me' and addresses the player in the masculine, as Ariana's other lines do. It also says nothing about the speaker's gender, which matters because the party file marks Ariana as Male even though her script lines are feminine. 'אני לא מקבל את זה!' fits the male grunt.

The ES precedent for debug.inc (correction 2) does not change the choice. Translating the menu's result messages while its labels in src/debug.c stay English would mix languages inside one tool. If the user wants the menus hidden, B with DISABLED_ON_RELEASE is the least invasive way, but that is a product decision, not a translation fix.

*Changed:* `data/scripts/debug.inc`, `translation/hebrew/STYLE.md`

## Q122

**Question.** The glossary has no row for TRICK MASTER. This chunk uses 'אמן התעלולים' in all eight secret codes. Other Trick House strings, still untranslated in other chunks ('The TRICK MASTER!', 'Don't look for me. TRICK MASTER', and others), need the same rendering, so a glossary row (or TRICK HOUSE = בית התעלולים) should be added to keep them consistent.

*Source:* reviewer question (chunk B40_02)

**Analysis.** Current tree: all 8 live secret-code units use 'אמן התעלולים'. These are Route110_TrickHousePuzzle1-8 *_Text_WroteSecretCodeLockOpened: Puzzle1:42, Puzzle2:105, Puzzle3:307, Puzzle4:33, Puzzle5:901, Puzzle6:48, Puzzle7:320, Puzzle8:33. The landmark already reads 'בית התעלולים' (src/landmark.c:28).
The remaining English TRICK MASTER/HOUSE lines are all dead according to tools/hebrew/data/live_labels.json:
- Route110 (TrickHouseSign; file not built);
- TrickHouseEntrance TheyCallMeTrickMaster, ComeToChallengeTrickHouse, LeavingOnJourneyNote, MechadollWhichTent;
- the Puzzle trainer intros and post-battle lines;
- trainers.inc Route124_Text_JennyPostRematch.
Related rows already use 'תעלול': MOVE_TRICK 'תעלול' (glossary.csv:2574) and MOVE_TRICK_ROOM 'חדר תעלולים' (:2736). Neither TRICK MASTER nor TRICK HOUSE has a row.

| Option | How | Risk |
|---|---|---|
| A: Add term rows TRICK MASTER = 'אמן התעלולים' and TRICK HOUSE = 'בית התעלולים' | Append the 2 rows; no text edits. | None. |
| B: Also translate the dead English lines now | Translate unreachable units. | Effort spent on text no player can reach; a row is enough to keep any future translation consistent. |

**Chosen:** A. It locks the two forms the tree already uses (8 codes and the landmark), in the MOVE_TRICK 'תעלול' family. Priority is low because the remaining English cannot be reached in H&S.

*Glossary:* `TERM_TRICK_MASTER`, `TERM_TRICK_HOUSE`

## Q123

**Question.** The shared battle lines that say a trainer sends out a Pokémon use the masculine verb for every trainer: 'רביעיית עלית קארן שלח את אמבריאון!', 'מנהיג קלייר עומד לשלוח את לפרס.'. Karen, Whitney, Jasmine, Clair, Misty, Erika, Sabrina and Janine speak of themselves in the feminine in their own text, so the battle box contradicts them. For Karen the verb also disagrees with the feminine head noun רביעייה.

*Source:* screen review, round 6 (gym leaders and Elite Four); left open in round 5 because it needs a decision.

**Analysis.** The strings are src/battle_message.c sText_Trainer1SentOutPkmn, sText_Trainer1SentOutTwoPkmn, sText_Trainer1SentOutPkmn2, sText_TwoTrainersSentPkmn, sText_Trainer2SentOutPkmn and STRINGID_ENEMYABOUTTOSWITCHPKMN. Every opponent trainer prints them, men, women and pairs (Twins, couples) alike. The English 'sent out' and 'is about to send out' carry no gender or number.
- The trainer data cannot pick a form: src/data/trainers_hns.party marks 630 of its 651 trainers 'Gender: Male', all eight women above included, and changing it would change trainer data.
- A class noun does not settle it either: TRAINER_CLASS_LEADER and TRAINER_CLASS_LEADER_HNS 'מנהיג' are shared by men and women (glossary.csv:4800, :4898), and TRAINER_CLASS_ELITE_FOUR_HNS 'רביעיית עלית' (:4910) is a feminine noun for Will, Koga and Bruno too.
- STYLE §2 keeps NPCs in their own gender and prefers a rewording that avoids gender where one reads naturally. The Pokémon is masculine by the settled rule.
- The English strings have no manual line break, so the battle text breaks them automatically (src/line_break.c BreakStringAutomatic); STYLE §5 says to keep them without breaks.

| Option | How | Risk |
|---|---|---|
| A. Reword so the Pokémon is the subject | 'הפוקימון של {X}, {Y}, יוצא לקרב!' for the send-out lines, 'הפוקימונים של {X}, {Y} ו{Z}, יוצאים לקרב!' for two Pokémon, and 'הפוקימון הבא של {X} יהיה {Y}.' for the about-to-send line. Token order unchanged; no manual breaks, as in English. | Low. Six strings; one form for every trainer, pairs included. The line is longer and wraps to two lines more often. |
| B. Feminine variants chosen in code | Under TEXT_RTL, pick a feminine string from a table of female trainer pics or ids. | Medium. A hand-kept table of every female pic, plural forms for pairs, and the Frontier and link trainers on top; a masculine class noun before a feminine verb ('מנהיג קלייר שלחה') still clashes. |
| C. Keep and list as a known issue | No change. | Every gym leader and Elite Four battle with a woman shows the clash. |

**Chosen:** A. It removes the clash for every trainer without trainer data or a table to maintain, and the wording is ordinary Hebrew narration. The other lines with a trainer as the subject keep the masculine for now: withdrew (sText_Trainer1WithdrewPkmn, sText_Trainer2WithdrewPkmn) and used an item (STRINGID_TRAINER1USEDITEM). They need their own neutral wording and were not part of this review. The partner lines name only male partners in H&S (src/data/battle_partners.party), and the link lines name real players.

*Changed:* `src/battle_message.c`

## Q124

**Question.** The battle line for an opponent trainer using an item, STRINGID_TRAINER1USEDITEM '{B_ATK_TRAINER_NAME_WITH_CLASS}\nהשתמש ב{B_LAST_ITEM}!', has the masculine verb for every trainer. On the Radio Tower 5F it reads 'מנהל רוקט אריאנה / השתמש בשיחזור מלא!' while Ariana speaks of herself in the feminine on the same screens ('עכשיו אני חזקה יותר'). Q123 left this line masculine 'for now'.

*Source:* screen review, round 6 (Johto story battles), confirmed on screen by a second reviewer; follow-up to Q123.

**Analysis.** The string is src/battle_message.c:509. The English, 'X used ITEM!', carries no gender and has no manual line break.
- Every AI trainer that carries battle items prints it. 100 entries in src/data/trainers_hns.party have an 'Items:' line. At least 25 of them are women: Whitney, Jasmine, Clair, Misty, Erika, Sabrina, Janine, Karen and Ariana, with their rematch and post-game entries.
- As in Q123, the trainer data cannot pick a form: both Ariana entries are 'Gender: Male' in the party file (:10892, :10927), like the female leaders.
- The class noun 'מנהל רוקט' before her name is a separate question. TRAINER_CLASS_ROCKET_ADMIN_HNS (glossary.csv:4926, reviewed) is shared by Archer, Proton, Petrel and Ariana, so it cannot take one gender (the Q123 analysis). A female class would change trainer data, which is out of scope. It stays masculine, in this line and in her intro and defeat lines.
- STYLE §2 keeps NPCs in their own gender and prefers a rewording that avoids gender where one reads naturally.

| Option | How | Risk |
|---|---|---|
| A. No verb | '{B_ATK_TRAINER_NAME_WITH_CLASS}: שימוש ב{B_LAST_ITEM}!'. Token order unchanged; no manual break, as in English, so the battle text breaks it automatically. | Low. One string, one form for every trainer. It reads as a terse battle report rather than a sentence. |
| B. Feminine variant chosen in code | Under TEXT_RTL, pick 'השתמשה' from a table of female trainer pics. | Medium. A hand-kept table, as rejected in Q123; 'מנהל רוקט אריאנה השתמשה' still clashes with the masculine class noun. |
| C. Keep and list as a known issue | No change. | Every female leader, Karen and Ariana who uses an item shows the clash. |

**Chosen:** A. It removes the masculine verb for every trainer without trainer data or a table, in the same spirit as Q123. The masculine class noun before Ariana's name is unchanged (shared class, see above). The withdrew lines (sText_Trainer1WithdrewPkmn, sText_Trainer2WithdrewPkmn) are still masculine; they were not part of this review.

*Changed:* `src/battle_message.c`

## Q125

**Question.** Lines that put a count before an item name print the singular for every item that has no Hebrew plural name: 'לזרוק כמה\nנוצת שרירים?', 'האם לזרוק 3\nשיקוי?', 'זרקת 999\nדינוזאור מאובן.', 'משכת 999\nאבן מפתח מוזרה.'. CopyItemNameHandlePlural (src/item.c:196) prints an item's plural name when it has one. Otherwise the English build adds 's' and, under TEXT_RTL, the Hebrew build keeps the singular. Before this change only the 183 items whose English has a pluralName, plus POKé BALL and SPORT BALL, had a Hebrew plural.

*Source:* screen review, round 7 (listed as known in round 6).

**Analysis.** These are the lines a player can see that print an item name after a count, or that ask for the plural on purpose (quantity 2, for 'how many'):
- The bag (src/item_menu.c): TOSS asks how many (:1984, gText_TossHowManyVar1s), confirms with the count (:1998, gText_ConfirmTossItems) and reports it (:2042, gText_ThrewAwayVar2Var1s). In the PC's DEPOSIT mode the bag asks how many (:2467, sText_DepositHowManyVar1) and reports the deposit (:2515, sText_DepositedVar2Var1s).
- PC item storage (src/player_pc.c): withdraw how many (:1335), toss how many (:1349), withdrew (:1399), the toss confirmation (:1422) and threw away (:1439).
- The Battle Pyramid bag (src/battle_pyramid_bag.c BagAction_Toss, AskConfirmToss, TossItem) prints the same three toss strings. It took the name from CopyItemName, so the singular followed the count in both languages ('Threw away 99\nMAX ELIXIR.' in English).
- Scripts. bufferitemnameplural (src/scrcmd.c:2909) is used only in data/scripts/obtain_item.inc (:15, :162, :182, :195, :296). It feeds 'obtained N' (gText_ObtainedTheItems), 'found N' (gText_PlayerFoundItems, gText_PlayerFoundTMHMs) and the put-away lines after them (gText_PutItemInPocket, gText_PlayerPutItemInBag). The put-away lines get the plural name without a count. Two reachable H&S scripts give an item in a count: the aide's 5 POKé BALLs (NewBarkTown_Lab_hns:500) and the 30 SPORT BALLs (Gate_NationalPark_hns:31, :50). No H&S item ball (movement_range_x) has a quantity above 1, and no hidden item does either (map.json quantity) apart from coins, which print gText_FoundXCoins.
- Berry trees (src/berry.c:2231, data/scripts/berry_tree.inc:69, :73): 'GOLD קטף\n5 פירות אורן.' and the full-pocket line. Every berry already has a plural (K6).
- Not reachable in H&S:
  - the Pokédex evolution condition 'N <item> בתיק' (src/pokedex_plus_hgss.c:7297). It uses a count above 1 only for GHOLDENGO's 999 GIMMIGHOUL COINs, and GIMMIGHOUL is in no H&S encounter, party or map. SHEDINJA's 1 POKé BALL takes the singular.
  - apricorn trees (src/apricorn_tree.c; APRICORN_TREE_COUNT is 0, include/constants/apricorn_tree.h:88).
  - Pokémon Jump (src/pokemon_jump.c:3336), a link minigame.
- Already worded so the count does not govern the name:
  - Kurt's balls ('{PLAYER} קיבל {STR_VAR_2}\nיחידות של {STR_VAR_1}!', AzaleaTown_KurtsHouse_hns:308, with bufferitemname);
  - hidden items in a count (gText_FoundXItems 'מצא N פריטים מסוג X');
  - the mart: 'X? ורצית N?' (src/strings.c gText_Var1AndYouWantedVar2) and 'X?\nכמה ברצונך למכור?' (gText_HowManyToSell), both with CopyItemName;
  - the Premier Ball bonus ('N כדורי פרמייר').
- The items. 525 stackable items had no Hebrew plural: every item outside the key-item and TM/HM pockets that has no importance. TMs are stackable too (I_REUSABLE_TMS is FALSE), but a TM's name is the abbreviation מ”מ plus a number, which Hebrew does not inflect ('2 מ”מ 01').
- Widths. The bag's description window is 14 tiles (112 px), the PC's message window 13 tiles (104 px) and the Pyramid's 14 tiles. In all three strings the name has a line to itself. The bag and the PC wrap a name wider than the window minus 16 px (WrapFontIdToFit); the Pyramid does not wrap. The widest plural is 'דינוזאורים מאובנים' (89 px, 18 bytes), so every plural fits on one line in every window. The widest counts are 999 in the bag and the PC (MAX_BAG_ITEM_CAPACITY, MAX_PC_ITEM_CAPACITY) and 99 in the Pyramid.

| Option | How | Risk |
|---|---|---|
| A. A Hebrew plural for every stackable item | Add item_plural rows for the 525 items. Where the plural differs from the singular (338 items), add a pluralName under #if TEXT_RTL in src/data/items.h, as for the two balls. A row equal to the singular needs no pluralName, because the fallback prints the singular. The Pyramid bag's count lines ask for the plural under TEXT_RTL, as the main bag does. A check (tools/hebrew/plurals.py, run by the unit tests) fails when a stackable item has no row or items.h prints something else. | The change is mostly data: 525 rows and 338 three-line blocks. drift.py reports STRUCTURE for items.h and battle_pyramid_bag.c until the same blocks, with English placeholders, are on he/renderer. Without a row, an item added later would print the singular, but the check catches it. |
| B. Reword the count lines so the number does not govern the name | For example '{STR_VAR_1}:\nכמה לזרוק?' and 'לזרוק {STR_VAR_2} יח'\n{STR_VAR_1}?'. The token order (count, then name) must stay. 'יחידות' fails at a count of 1 ('1 יחידות'), which the bag and PC print for a single item. | Small: about ten strings, with every item, caller and later item covered. But the lines read like a receipt in a game that otherwise says 'קיבלת 5 פוקיבולים!'. The 187 reviewed plurals still feed these strings, so each wording must read with both forms. |
| C. A for what scripts hand out in counts, B for the bag, the PC and the Pyramid | The two script gifts already have plurals; reword the seven bag and PC strings. | Medium. The same kind of line comes in two styles ('קיבלת 5 פוקיבולים!' but 'זרקת 3 יח' פוקיבולים.'), and the B lines read like a receipt. |

**Chosen:** A. It follows the English, where every stackable item has a plural (a pluralName or an added 's'), and the engine already supports it. The lines read as ordinary Hebrew: 'לזרוק כמה\nשיקויים?', 'האם לזרוק 999\nפוקיבולים?', 'משכת 999\nאבני מפתח מוזרות.'. No reviewed wording changes except the three lines below.

The plurals follow the reviewed rows:
- the head noun in the plural (שיקויים, נוגדנים, החייאות, לימונדות);
- a construct plural for a compound name (כדורי ריפוי, אבני אש, שיקויי על, נוצות בריאות, לוחות להבה, אבני חן אש, שברי טרה מים);
- the adjective in the plural where it agrees (כדורים מעולים, אבנים נוצצות, פנינים גדולות, גולות אדומות, אבני חן פסיכיות).

The singular is kept for:
- mass nouns, as honey, mulch and mail are (ברזל, סידן, אבץ, קטורת, צוף, נענע, חלב מומו, סודה פופ, פחם, אבק כוכבים, מלח מערות, נחושת/כסף/זהב עתיק);
- names that are already plural (מים טריים, מים מיסטיים);
- the X items (as X ACCURACY);
- the 128 Mega Stone, Z-Crystal and Augurite names;
- two unused placeholders.

A counter is used where the plain plural changes the meaning, as REMEDIES מנות מרפא did: ETHER מנות אתר (אתרים reads as websites) and REPEL תרסיסי דוחה (דוחים reads as 'disgusting'). ULTRA BALL and MASTER BALL take בולים, like פוקיבולים.

The put-away lines dropped 'את'. 'את' marks a definite object. A singular item name is read as a name ('שם את שיקוי'), but a plural name is an indefinite noun, and 'GOLD שם את פוקיבולים' is not Hebrew. Without 'את' the line reads correctly for both: 'GOLD שם פוקיבולים\nבכיס כדורי פוקי.' and 'GOLD שם שיקוי\nבכיס תרופות.'. The same applies to gText_PlayerPutItemInBag (Pyramid item balls) and to the berry tree's full-pocket line ('אי אפשר היה לקחת פירות סיטרוס.').

*Changed:* `src/data/items.h`, `src/battle_pyramid_bag.c`, `data/text/obtain_item.inc`, `data/scripts/berry_tree.inc`, `tools/hebrew/plurals.py`, `tools/hebrew/tests/test_plurals.py`

*Glossary:* 525 `item_plural` rows (notes end in Q125)

## Q126

**Question.** One NORMAL-rank contest calls its rank three different things. The lobby rank menu says 'דרגה רגילה', the MC says 'מנחה: שלום! בדרגת רגיל,' and the results title says 'דרגת בסיס'. The MC line joins the construct noun דרגת to the bare masculine adjective רגיל, which is not Hebrew. סופר, היפר and מאסטר read correctly in the same slot because they are names. Two rewordings of the MC line were rejected: 'הדרגה: {STR_VAR_3}.' puts the feminine noun next to the masculine רגיל, and 'בדרגת ”{STR_VAR_3}”,' quotes a name, which STYLE §3 does not do.

*Source:* screen review, round 9 (contest opponents and COOL ranks), confirmed by two reviewers. Rounds 5 (R6) and 6 (C4) proposed rewordings of the MC line, and neither was merged.

**Analysis.** These are the places that name the NORMAL rank (English 'NORMAL', 'NORMAL RANK', 'Normal Rank'):
- gText_Normal (src/strings.c) reaches two lines through gStdStrings[STDSTRING_NORMAL]. One is the MC's line (data/scripts/contest_hall.inc ContestHall_Text_GettingStartedParticipantsAsFollows, 'בדרגת {STR_VAR_3},'). The other is the BRAVO TRAINER TV show (src/tv.c CopyContestRankToStringVar; data/text/tv.inc gTVBravoTrainerText00, 'מתהדר בדרגת {STR_VAR_3}'). No H&S map runs EventScript_TV, so the show is not seen in H&S. Both lines put the rank after the construct דרגת, so the rank has to be a name.
- The lobby rank menu (MultichoiceList_ContestRank, src/data/script_menu.h) says 'דרגה רגילה'.
- The lobby painting caption (sContestRankNames, src/contest_painting.c) says 'בדרגה רגילה'.
- The ribbon description (gRibbonDescriptionPart2_NormalRank, src/data/text/ribbon_descriptions.h) says 'מנצח בדרגה רגילה!'.
- The receptionist's rank explanation (LilycoveCity_ContestLobby_Text_ExplainContestRanks, contest_hall.inc) says 'רגילה, סופר, היפר ומאסטר' and 'בדרגה הרגילה' twice.
- The results title graphic (graphics/contest/results_screen/tiles.png) says 'דרגת בסיס'. The game builds the title from tiles as [rank][RANK][category][CONTEST], so the rank word follows the construct דרגת there too. The graphics notes chose בסיס because that construct needs a noun.

gText_Normal has one other user, and it is not the contest rank. The FRLG Game Corner photo printer's tint menu (sMultichoiceList_TrainerCardIconTint, MULTI_TRAINER_CARD_ICON_TINT) uses it for the plain print. The menu's only script, data/scripts/trainer_card_frlg.inc:14, is assembled only when IS_FRLG (data/event_scripts.s:605), but the list is in the ROM. VerdanturfTown_ContestHall_Text_NormalRankStage is unused and still in English.

The English and the Japanese (ノーマル, スーパー, ハイパー, マスター) name all four ranks the same way. SUPER, HYPER and MASTER are transliterated everywhere in the tree (סופר, היפר, מאסטר). No glossary row covered any rank.

| Option | How | Risk |
|---|---|---|
| A. 'נורמל', a rank name like the other three | Set gText_Normal to 'נורמל', so the MC and TV lines read 'בדרגת נורמל'. The menu, the painting caption, the ribbon description and the rank explanation say 'דרגת נורמל' / 'בדרגת נורמל'. The results title is redrawn as 'דרגת נורמל' in the title's own S11 letters. The tint menu keeps 'רגיל' with its own string under TEXT_RTL. Add glossary rows for the four ranks. | Low. Six strings, one graphic and a TEXT_RTL entry in a data table, with no script or layout change. Every new string is narrower than its MASTER sibling. drift.py reports STRUCTURE for src/data/script_menu.h until the same entry, with an English placeholder, is on he/renderer. |
| B. 'בסיס' everywhere, the title graphic's word | Set gText_Normal to 'בסיס' and the strings to 'דרגת בסיס'. The graphic does not change. | Low effort. But it makes the first rank the only translated name of the four, and בסיס ('base', 'basic') says something the English NORMAL does not. |
| C. Reword the lines so an adjective fits | For example 'הדרגה: {STR_VAR_3}.', or quotation marks. | Rejected twice already: the gender clash with רגיל, and quoting a name breaks STYLE §3. The TV line would need the same treatment. |

**Chosen:** A. It treats the four ranks alike, as the English and the Japanese do. Every rank string then has one form, דרגת + name, that is grammatical for all four ranks: 'דרגת נורמל', 'בדרגת נורמל', 'מנצח בדרגת נורמל!', 'תחרות מגניבות בדרגת נורמל'. The word רגיל keeps its meaning wherever it is not the contest rank: TYPE_NORMAL, ordinary use and the photo printer's plain print.

*Changed:* `src/strings.c`, `src/data/script_menu.h`, `src/contest_painting.c`, `src/data/text/ribbon_descriptions.h`, `data/scripts/contest_hall.inc`, `graphics/contest/results_screen/tiles.png`

*Glossary:* `TERM_CONTEST_RANK_NORMAL`, `TERM_CONTEST_RANK_SUPER`, `TERM_CONTEST_RANK_HYPER`, `TERM_CONTEST_RANK_MASTER`

## Q127

**Question.** The battle lines that say a trainer withdraws a Pokémon use the masculine 'החזיר' for every trainer: 'מטיילת ארין החזיר / את רפידאש!', 'מאמן על רינה החזיר / את סטארמי!', 'תאומים לאה ופיה החזיר / את דרגונייר!', and in a Battle Tower multi battle the second opponent and the lobby partner, 'גברת שמשייה יוליאנה החזיר / את קלידול!' and 'עלמה סיביל החזיר / את היטמונטופ!'. Q123 and Q124 left these lines masculine because they were not part of those reviews. The Hebrew also breaks the line by hand where the English has no break.

*Source:* screen review, round 11 (trainer withdraw, finding 1: the Twins pair with a singular verb), the open lines of Q123 and Q124, and round 13 (a woman as the Tower lobby partner).

**Analysis.** The strings are src/battle_message.c sText_Trainer1WithdrewPkmn, sText_Trainer2WithdrewPkmn, sText_InGamePartnerWithdrewPkmn1 and sText_InGamePartnerWithdrewPkmn2, which BufferStringBattle picks for STRINGID_RETURNMON by the battler's side and position. Every AI trainer that switches prints them: field trainers of both genders, a pair in a one-trainer double battle (Twins, couples), both opponents of a multi battle (the Rocket Hideout B2F battle; Battle Tower multis) and the in-game partner (Lance; a Tower lobby partner, who may be a woman, so Q123's 'only male partners' no longer holds once the Frontier partners are counted).
- The English 'X withdrew Y!' carries no gender or number and has no manual line break.
- As in Q123, the trainer data cannot pick a form (630 of the 651 trainers in src/data/trainers_hns.party are 'Gender: Male', the women included), a class noun is shared by men and women, and a table of female trainers would also have to cover the Frontier trainers and partners.
- A search of battle_message.c for {B_TRAINER1_NAME_WITH_CLASS}, {B_TRAINER2_NAME_WITH_CLASS}, {B_PARTNER_NAME_WITH_CLASS} and {B_ATK_TRAINER_NAME_WITH_CLASS}, and for the bare name tokens ({B_TRAINER1_NAME}, {B_TRAINER2_NAME}, {B_ATK_TRAINER_NAME}, {B_PARTNER_NAME}), followed by a verb finds no other line that reaches the screen: the send-out lines follow Q123 and the item line Q124. sText_Trainer1Fled ('{B_TRAINER1_NAME_WITH_CLASS} ברח!') is defined but never referenced, so the compiler drops it (no symbol in pokehns.elf) and it is left as it is.
- The link lines (sText_LinkTrainer1WithdrewPkmn, sText_LinkPartnerWithdrewPkmn1 and their siblings) name real players, as Q123 noted, and keep their wording.
- The move WITHDRAW is 'נסיגה' (glossary MOVE_WITHDRAW), so the verb 'נסוג' would read as the move.

| Option | How | Risk |
|---|---|---|
| A. Reword so the Pokémon is the subject, as Q123 did | 'הפוקימון של {X}, {Y}, חוזר!' for all four strings, the partner lines with {B_PLAYER_MON1_NAME} / {B_PLAYER_MON2_NAME} in place of {B_BUFF1}. Token order unchanged; no manual break, as in English, so the battle text breaks the line automatically. The present 'חוזר' pairs with the send-out line that follows it, '… יוצא לקרב!'. | Low. Four strings, one form for every trainer and partner, pairs included. The line is longer than before; the battle text keeps it on one line when it fits and wraps it to a second when it does not. |
| B. Feminine variants chosen in code | Under TEXT_RTL, pick 'החזירה' / 'החזירו' from a table of female trainer pics and pair classes. | Medium. The hand-kept table rejected in Q123 and Q124, with the Frontier trainers and partners on top; 'מאמן על רינה החזירה' would still clash with the masculine class noun. |
| C. Keep and list as a known issue | No change. | Every woman, pair and woman partner who switches shows the clash. |

**Chosen:** A. It closes the withdraw lines Q123 and Q124 left open, with the wording of the send-out lines, and no trainer data or table. With it no line of src/battle_message.c that reaches the screen gives an opponent or partner trainer a gendered verb; the link lines are the exception noted above, and the player is masculine by STYLE §2. A class noun before a trainer's name keeps the gender the trainer data gives it: Ariana's shared 'מנהל רוקט' (Q124) and the other classes shared by men and women are trainer data, which is out of scope.

*Changed:* `src/battle_message.c`

## Q128

**Question.** On the summary screen, a geresh in the portrait nickname (ג'ימי, and species names used as nicknames such as טיפלוז'ן, פיקאצ'ו and צ'אנסי) is drawn on y 96, directly under the portrait box's last row, y 95. The 1.0 release notes list it as a known issue, a side effect of K5.

*Source:* K5 review ('Review of the changed screens' below); round 5 rejected a fix that moved the name; retried in round 14.

**Analysis.** The name prints at PORTRAIT_NICKNAME_Y = 7 in a window whose top is y 88, so glyph row 0 is y 95. Hebrew letters have their body on rows 4-11, the ל ascender on row 2, and descenders to row 13 with the shadow on row 14. The frame under the name on the move pages is y 109. The four quote marks a name can hold, “ ” ‘ ’ (0xB1-0xB4; ’ is also the geresh, CHAR_SGL_QUOTE_RIGHT, on the Hebrew keyboard), are the only glyphs whose foreground starts on row 1, in all three fonts this window can use (FONT_NORMAL and its GetFontIdToFit fallbacks FONT_NARROW and FONT_NARROWER). Round 5 showed that no y clears both the box and the frame (13 free rows, 14 needed), and that a page-dependent y makes the name jump.

| Option | How | Risk |
|---|---|---|
| A. Keep it as a known issue | No change. | The geresh stays against the box. |
| B. Lower or shorten the marks in the fonts | Redraw 0xB1-0xB4 one row lower, or one row shorter, in latin_normal/narrow/narrower.png. | Changes every apostrophe, geresh and quote mark in every text in those fonts, including dialogue and the Easy Chat words, which are out of scope. Lowering only the geresh would put it below the gershayim (נ”ח). |
| C. A per-window y offset in the renderer for glyphs above the x-height | New window state in src/text.c. | An engine change, with its own drift and review, for one window. |
| D. Lowered copies used only by this window | Write the four marks one row lower, at the same widths, into the blank extra-symbol cells F9 19-1C of the three fonts (and their width tables in src/fonts.c). Under TEXT_RTL, PrintNotEggInfo prints a copy of the nickname with the four marks replaced by those cells. | Low. Nothing else uses the cells, so no other text changes. The cells are neutral to the renderer like the marks (RtlClassAt), so the reading order is the same. A Japanese-language nickname is left as it is. drift.py reports STRUCTURE for src/pokemon_summary_screen.c and src/fonts.c until the same changes are on he/renderer. |

**Chosen:** D. The marks keep their shape and are 1 row below the box. The name's baseline and its lowest rows do not move, so what the forget-move frame shows is unchanged, as round 5 required. In the 71 regression tours, 15 shots differ, each only in the 3 x 6 px of a geresh. They are the Typhlosion, ג'ימי and Chansey summary pages.

*Changed:* `src/pokemon_summary_screen.c`, `src/fonts.c`, `graphics/fonts/latin_normal.png`, `graphics/fonts/latin_narrow.png`, `graphics/fonts/latin_narrower.png`, `tools/hebrew/release/notes.json`

## Q129

**Question.** EXEGGUTOR-A is אקזגיוטר-א, without the ק of the base form אקזגקיוטר (SPECIES_EXEGGUTOR, FireRed's spelling). Every other Alolan form is its base name plus -א (סנדסלאש-א, ניינטיילס-א, מארוואק-א), and the Pokédex shows the two spellings side by side on EXEGGCUTE's EVOLUTION page. The ק was dropped because the base plus -א is 56 px against the 50 px Pokédex list column. The 1.0 release notes list it as a known issue.

*Source:* 1.0 known issue (tools/hebrew/release/notes.json), retried in round 14.

**Analysis.** אקזגקיוטר-א is 11 letters (the species limit is 12 bytes) and measures 61 px in FONT_NORMAL, 56 in FONT_NARROW and 49 in FONT_NARROWER (tools/hebrew/textwidth.py). It would be the widest species name by 1 to 3 px: the widest today is MEOWSCARADA מיאוסקראדה, 60 / 53 / 46. The 56 px figure is the FONT_NARROW width. The list itself does not stop there: under TEXT_RTL, src/pokedex_plus_hgss.c CreateMonName prints with GetFontIdToFit(name, FONT_NARROW, 0, 50), which falls back to FONT_NARROWER at 49 px. That fit dates from a1c5d26885. The audit's budget file was written later but still called the column "no fit" (tools/hebrew/data/budgets.json, and the dex entry of tools/hebrew/glossary_widths.py). Every window that draws the name, with the width it allows:

| Window | Code | Full form |
|---|---|---|
| Pokédex list | CreateMonName, FONT_NARROW fitted to 50 | FONT_NARROWER, 49 px |
| Pokédex INFO banner | PrintInfoScreenTextWhite, FONT_NORMAL inside x 119-237 | 61 px |
| Pokédex STATS | FONT_SMALL up to 55, else FONT_SMALL_NARROWER | 49 px |
| Pokédex EVOLUTION | FONT_SMALL, the method text after it | fits on both pages |
| Summary | nickname line fitted to 63, species line to 58 | 61 px normal; 56 px narrow |
| Party menu | FONT_SMALL fitted to 50, then FitNameToWidth | FONT_SMALL_NARROWER, 49 px, nothing cut |
| Healthbox, Gen 3 and Gen 4 UI | name and gender sign fitted to 55, then FitNameToWidth | FONT_SMALL_NARROWER, 53 px with ♂, nothing cut |
| Ability pop-up | the battler's name on the pop-up's first line | 56 px, inside the pop-up |
| Naming screen title | WrapFontIdToFit(name, FONT_NORMAL, 64) | 61 px |
| Pokédex CRY page | FONT_NORMAL with no fit in the x 81-142 gap between the mon box and the VU meter | 61 px would touch the box at x 80; under TEXT_RTL the name is fitted to 60 px, so it falls back to FONT_NARROW, 56 px |
| PC panel, nickname line | FONT_NORMAL fitted to 66 | 61 px |
| PC panel, species line | '/' + name in the font fitted to the nickname (English code) | 62 px after no nickname; 67 px after a short one, which would start at x 5, 1 px inside the 6 px margin the 78 px mirror axis keeps |
| Contest | FONT_NARROW fitted to 50 | FONT_NARROWER, 49 px (not seen on screen) |
| Messages | dialogue and battle boxes | fits |

| Option | How | Risk |
|---|---|---|
| A. Keep אקזגיוטר-א | No change. | The only regional form that is not its base plus the suffix, shown next to the base form in the Pokédex. |
| B. The full form, with the TEXT_RTL fits | The glossary row first, then the species name. On the Pokédex CRY page, under TEXT_RTL, the name is fitted to the 60 px that keep a 1 px gap to the mon box. In the PC panel, under TEXT_RTL, the species line keeps the nickname's font unless the line is wider than the 66 px the mirrored panel leaves; then it falls back to a narrower font. Correct the dex list entry of budgets.json and glossary_widths.py to the fit the code has. | Low. The name is drawn in a narrower font in the list, the party, the healthbox, STATS and the summary species line, as long names already are. The CRY page and PC fallbacks fire for no other species: every other name is 60 px or less in FONT_NORMAL, and every other '/' + name is 66 px or less in FONT_SHORT. drift.py reports STRUCTURE for src/pokemon_storage_system.c and src/pokedex_plus_hgss.c until the same block is on he/renderer. |
| C. Shorten the base another way | For example drop the י (אקזגקוטר-א, 53 px in FONT_NARROW). | It still differs from the base form, and it loses the /ju/ that the base and the row 184 note keep. |

**Chosen:** B. The Alolan form follows the same rule as the other -א forms, and the Pokédex shows one base spelling on both entries. Every window in the table except the contest was seen on screen before and after (tours scripts/r14_fix_b/tours/r14b_exeggutor_menus, r14b_exeggutor_battle and r14b_dex_cry). The first review found the CRY page touching the box, which the fit then fixed.

*Changed:* `src/data/pokemon/species_info/gen_1_families.h`, `src/pokedex_plus_hgss.c`, `src/pokemon_storage_system.c`, `tools/hebrew/data/budgets.json`, `tools/hebrew/glossary_widths.py`, `tools/hebrew/release/notes.json`

*Glossary:* `SPECIES_EXEGGUTOR_ALOLA`

## Q130

**Question.** The battle intro 'קיבלת אתגר\nמ{B_TRAINER1_NAME_WITH_CLASS}!' attaches the prefix מ to the trainer class, and for some classes the joined word reads as another word: 'ממלכת השביל לוסי!' (PIKE QUEEN: 'kingdom of the Pike'), 'מאס הכיפה טאקר!' (DOME ACE: the verb מאס), 'משומר פוקימון קורנליה!' (PKMN RANGER: 'preserved'), more weakly 'מילד עשיר', 'מצעיר', 'ממנהל רוקט'.

*Source:* screen review, round 16 (Frontier Brain intros; Trainer Hill Rangers), confirmed by the refute pass.

**Analysis.** The strings are src/battle_message.c sText_Trainer1WantsToBattle and sText_TwoTrainersWantToBattle, which every field, Frontier, Trainer Hill and Tower trainer prints when the battle starts; the Frontier Brains take their class from GetFrontierBrainTrainerClass, so the brain lines are the ones in play. STYLE §4 attaches a prefix by default; no decision covered a prefix that changes the word. The link templates name only the player ('קיבלת אתגר מ{B_LINK_OPPONENT1_NAME}!') and are not affected by a class.

| Option | How | Risk |
|---|---|---|
| A. 'מאת' before the class | 'קיבלת אתגר\nמאת {B_TRAINER1_NAME_WITH_CLASS}!\p' and 'קיבלת אתגר\nמאת {B_TRAINER1_NAME_WITH_CLASS}\lומאת {B_TRAINER2_NAME_WITH_CLASS}!\p'. Token order and breaks unchanged. | Low. The class is never joined to a letter. Worst case (a 12-letter class and a 10-letter name, the widest glyph): 185 px +8 arrow on one trainer's line, 181 and 188 px on the two-trainer lines, inside 200 px (tools/hebrew/textwidth.py). |
| B. Rename the classes that collide | Change PIKE QUEEN, DOME ACE, PKMN RANGER and the others. | Trainer-class names are glossary terms used in many lines; a rename for one template is out of proportion, and a new class could collide again. |
| C. Keep | No change. | The intros of three Frontier Brains and the Rangers read as other words. |

**Chosen:** A. Seen on screen on the rc17 clip build and the fixed clip build: the Pike Queen and Dome Ace intros, the Trainer Hill Rangers (one trainer and a pair), Youngster Mikey, the Twins, the gym leader and the Rocket Hideout multi battle ('מאת מנהל רוקט אריאנה / ומאת רוקט גראנט!'), with 0 clip records.

*Changed:* `src/battle_message.c`

## Q131

**Question.** The battle debug menu shows the stat-up hold effects in two forms: six as 'X +' ('התקפה +', 'מהירות +', "התק' מ' +", 'קריטיות +', 'נתון מקרי +', 'התחמקות +') and three as 'העלאת X' ('העלאת הגנה', "העלאת הגנ' מ'", 'העלאת חברות'). On the AI points page, the label 'מחליף אל' stands about 19 px away from the Pokémon it names.

*Source:* the string-coverage round (round 16), the battle debug menu; a question for the owner in HANDOFF section 8.2. Q118 keeps this menu in Hebrew and says to finish it.

**Analysis.** The names are src/battle_debug.c sHoldEffectNames. English 2.0.6 uses one form for all nine, 'X Up'.
- The info page prints a name in FONT_SMALL in a 75 px column per battler (x = 83 + battler × 75). The AI party page copies only the first 7 bytes of the name (StringCopyN(..., 7)) and prints them in FONT_SMALL_NARROW in a 41 px column, so Defense Up and Sp. Def Up both print 'העלאת ה' there, and Friendship Up prints 'העלאת ח'.
- "הגנ' מ'" is the tree's own short Sp. Def (gText_SpDef4 in src/strings.c), next to "התק' מ'" (gText_SpAtk4), which Sp. Attack Up already uses.
- The AI points page prints the label at x 74 and the species at the fixed x 74 + 68. The English 'Switching to ' is exactly 68 px, so English has one space between the two. Under TEXT_RTL the window is mirrored, and 'מחליף אל ' (49 px) leaves a hole of 19 px.
- Labels measured in FONT_NORMAL with the trailing space (tools/hebrew/textwidth.py): 'עובר לפוקימון ' 68 px, 'יחליף לפוקימון ' 71, 'מחליף לפוקימון ' 75, 'החלפה לפוקימון ' 79, 'מחליף אל פוקימון ' 85. A label over 68 px runs into the species.

| Option | How | Risk |
|---|---|---|
| A. 'X +' for all nine, and a 68 px label | 'הגנה +', "הגנ' מ' +" and 'חברות +' for the three; 'עובר לפוקימון ' for the label. Text only. | Low. The three are shorter: 32, 45 and 37 px in FONT_SMALL, against 54, 67 and 59. The widest of the nine stays 50 px. Their 7-byte copies, 'הגנה +', "הגנ' מ'" and 'חברות +', differ from each other and measure 30, 30 and 35 px of the 41 px column. |
| B. 'העלאת X' for all nine | Reword the six 'X +' rows. | It undoes six reviewed rows, "העלאת הגנ' מ'" is 67 px, and the 7-byte copies still read the same. |
| C. Place the species after the label in code | Under TEXT_RTL, x = 74 + GetStringWidth(label). | An engine change in a file drift.py checks: STRUCTURE until he/renderer has the same block. Not needed when a natural label is exactly 68 px. |
| D. Keep | No change. | The family stays mixed, and the gap stays. |

**Chosen:** A. One form, as in English, the one most rows already had and the shortest, and the 7-byte party page now tells Defense, Sp. Def and Friendship apart. The label puts the species one space after it, as in English.

*Changed:* `src/battle_debug.c`

## Q132

**Question.** In a link battle, the lines for the other player or the link partner sending out or withdrawing a Pokémon read '{X} שלח את {Y}!' and '{X} החזיר את {Y}!', with the masculine verb whatever character that player chose. The line for a link opponent who runs, '{X} ברח!', has the same fault. The 1.0 release notes listed the send-out and withdraw lines as a known issue.

*Source:* 1.0 known issue (tools/hebrew/release/notes.json); the link lines that Q123 and Q127 left as they were.

**Analysis.** The strings are src/battle_message.c sText_LinkTrainerSentOutPkmn, sText_LinkTrainer2SentOutPkmn2, sText_LinkTrainerSentOutTwoPkmn, sText_TwoLinkTrainersSentOutPkmn, sText_LinkTrainerSentOutPkmn2, sText_LinkTrainerMultiSentOutPkmn, sText_LinkPartnerSentOutPkmn1GoPkmn, sText_LinkPartnerSentOutPkmn2GoPkmn, sText_LinkPartnerSentOutPkmn1, sText_LinkPartnerSentOutPkmn2, sText_LinkPartnerWithdrewPkmn1, sText_LinkPartnerWithdrewPkmn2, sText_LinkTrainer1WithdrewPkmn and sText_LinkTrainer2WithdrewPkmn, and sText_WildFled, which prints when the link opponent runs.
- Q123 and Q127 kept these lines because they name real players. That is not a reason to keep a gendered verb: the other player may have chosen the girl, and the wording of those two decisions reads the same for both.
- The English lines carry no gender and have no manual line break. The Hebrew lines for two Pokémon and the partner's lines with 'צא' broke the line by hand.
- sText_TwoWildFled 'ברחו' is the past plural, which has one form for both genders, so it stays.
- Widths (tools/hebrew/textwidth.py, worst case a 7-letter player name and a 12-letter Pokémon name): 255 px for one Pokémon sent out, 365 px for two and for the partner's line with 'צא', 229 px for a withdraw, 513 px for the two-player line (two sentences), 175 px for the fled line. The battle text wraps each at 200 px a line and pages it; the trainer lines of Q123 already reach 473 px.

| Option | How | Risk |
|---|---|---|
| A. Reword so the Pokémon is the subject, as Q123 and Q127 did | 'הפוקימון של {X}, {Y}, יוצא לקרב!', 'הפוקימונים של {X}, {Y} ו{Z}, יוצאים לקרב!' and 'הפוקימון של {X}, {Y}, חוזר!'; the partner's line keeps 'צא, {Y}!' after its send-out; the fled line becomes 'הקרב הסתיים בבריחה של {X}!'. Token order unchanged; no manual breaks, as in English. | Low. Fifteen strings, text only, one form for every player. |
| B. Pick the verb by the other player's gender in code | Under TEXT_RTL, read the gender the link sends (gLinkPlayers) and print 'שלחה' / 'החזירה'. | Medium. Engine code for screens only a real link shows, two forms of every line, and no second GBA to check it with. |
| C. Keep as a known issue | No change. | Every link battle against a girl shows the clash. |

**Chosen:** A. The link lines get the wording the trainer lines already have, with no code. With it, no line of src/battle_message.c that names a link player gives that player a gendered verb. The known issue is removed from the release notes. The player stays masculine by STYLE §2.

*Changed:* `src/battle_message.c`, `tools/hebrew/release/notes.json`

## Q133

**Question.** Round 17 gave Hebrew names to five terms that Pokédex entries printed in Latin: HISUI היסואי, MT. CORONET הר הנזר, Ultra Wormhole חור תולעת אולטרה, TEAM PLASMA צוות פלזמה and ROSE רוז. No official Hebrew source exists for them, and the handoff asked the owner to confirm them.

*Source:* HANDOFF section 8.2, questions for the owner from the Pokédex rounds (16b and 17); glossary rows PLACE_MT_CORONET, NAME_HISUI, PLACE_ULTRA_WORMHOLE, TERM_TEAM_PLASMA and NAME_ROSE.

**Analysis.** The terms appear in src/data/pokemon/species_info: gen_2_families.h:542 (MT. CORONET), gen_5_families.h:822 and :4699, gen_6_families.h:5283 and gen_7_families.h:249 (HISUI), gen_7_families.h:6574, :6640 and :7528 (Ultra Wormhole), shared_dex_text.h:61 (TEAM PLASMA) and gen_8_families.h:7134 (ROSE). How the glossary renders their neighbours:

| Family | Rows | Rule |
|---|---|---|
| Mountains | MAPSEC_MT_MOON הר הירח (inherited from FireRed), MAPSEC_MT_MORTAR הר המכתש, MAPSEC_MT_SILVER הר הכסף | MT. = הר; an English common word is translated by its meaning. FireRed also has MT. EMBER הר אמבר, transliterated. |
| Regions | KANTO קאנטו, JOHTO ג'וטו, GALAR גלאר, SINNOH סינו, PALDEA פלדייה | transliterated; prose says 'אזור X' |
| Teams | TERM_TEAM_ROCKET צוות רוקט (inherited), TEAM AQUA צוות אקווה, TEAM MAGMA צוות מגמה | TEAM = צוות + the name |
| People | the NAME_* rows | transliterated, never translated |
| Ultra | TERM_ULTRA_BEASTS חיות אולטרה, ITEM_ULTRA_BALL אולטרה בול | Ultra = אולטרה; definite 'X האולטרה' |

- היסואי is transliterated like every region; the א marks the break between the two vowels, as in PLACE_HAUOLI_CITY האואולי, and without it היסוי reads 'hisoy'. It matches the -ה ending of the Hisuian forms.
- 'coronet' is a common English word (נזר), so הר הנזר follows H&S's own mountains. The transliterated הר קורונט is FireRed's minority MT. EMBER pattern; it would also make the entry's last row 113 px instead of 106.
- חור תולעת is the standard Hebrew physics term; Ultra and the definite form follow חיות האולטרה. The three uses follow the English article: definite at :6574 and :6640, indefinite at :7528.
- צוות פלזמה follows the three inherited teams; פלזמה is the Hebrew word, as in DEXCAT_PLASMA and MOVE_PLASMA_FISTS.
- רוז is a person's name, transliterated like every NAME_* row (s as /z/ = ז).
- No official Hebrew source was found: the Pokémon Israel site (pokemon-il.co.il) refused the request (HTTP 403), and the Hebrew dub's terms were not checked.

| Option | How | Risk |
|---|---|---|
| A. Keep all five | No change. | None found; the rows stay 'proposed' until a native speaker or an official source confirms them. |
| B. Transliterate MT. CORONET as הר קורונט | Change the glossary row and gen_2_families.h:542. | It follows the minority pattern, and the row is 7 px wider. |
| C. Leave the five in Latin | Revert round 17. | Latin words inside Hebrew prose, which round 17 removed. |

**Chosen:** A. Each term follows the rule of its family in the glossary. The rows stay 'proposed', as no official source or native reading confirms them.

## Q134

**Question.** The English 'psychic power(s)', 'psychic energy' and 'psychic abilities' have two renderings in Pokédex prose: כוח פסיכי in most entries and כוח על-חושי in nine.

*Source:* HANDOFF section 8.2, questions for the owner from the Pokédex rounds (16b and 17).

**Analysis.** Every English 'psychic power', 'energy' or 'ability' in the tree, paired with its Hebrew:

| Where | Count | Rendering |
|---|---|---|
| Pokédex entries | 35 | פסיכי in 26; על-חושי in 9 (11 rows): Alolan Raichu, Golduck, Kadabra, Alakazam, Delphox, Espurr, female Meowstic, Pa'u Oricorio, Bruxish |
| Move descriptions | 3 (Freezing Glare, Eerie Spell, Psyshield Bash) | פסיכי |
| Dialogue | 10 lines (the Saffron gyms and the fighting dojo) | פסיכי |

- על-חושי stays in Kadabra's 'extrasensory powers' (תפיסה על-חושית) and in the move names that already have it: PSYBEAM קרן על-חוש, PSYWAVE על-חוש, PSYSHOCK הלם על-חושי, PSYSTRIKE מכת על-חוש, ESPER WING כנף על-חושית and PSYBLADE להב על-חוש. Move names are not changed here. Other PSY- names already use פסיכי (PSYCHO CUT חיתוך פסיכי, PSYSHIELD BASH מכת מגן פסיכי), and the move EXTRASENSORY is חוש נוסף.
- The type name is פסיכי. It is not changed here: TYPE_PSYCHIC is an inherited glossary row, and the type labels are drawn in the art (graphics/types/psychic.png). FireRed's own prose is mixed, and FireRed has since renamed its type to על-חושי.
- The English ties the prose to the type in the same scenes (in Sabrina's gym, Sabrina's 'psychic powers' and the guide's 'PSYCHIC-type POKéMON').
- כוחות פסיכיים is ordinary spoken Hebrew for a medium's powers (STYLE §1).
- Widths (tools/hebrew/textwidth.py, FONT_NORMAL): each of the eleven rows becomes 13 px narrower; the widest is 195 px of the 224 px line. Doing the opposite would also push two פסיכי rows over the line: Gothitelle to 228 px and Rellor to 227 px.

| Option | How | Risk |
|---|---|---|
| A. פסיכי in prose | אנרגיה פסיכית, כוחות פסיכיים, כוח פסיכי, כוחו הפסיכי, ביכולות הפסיכיות in the eleven rows; a glossary term row. | Low. Eleven rows, each narrower; no row count changes. |
| B. על-חושי in prose | Change 27 Pokédex rows, 10 dialogue lines and 3 move descriptions. | Two Pokédex rows over 224 px, and the prose no longer matches the type name. |
| C. Keep the mix | No change. | The same English reads two ways. |

**Chosen:** A. It is the form 39 of the 48 strings already had, the word of the type, and the smallest change. על-חושי stays in Kadabra's 'extrasensory' and in the move names that already have it.

*Changed:* `src/data/pokemon/species_info/gen_1_families.h`, `src/data/pokemon/species_info/gen_6_families.h`, `src/data/pokemon/species_info/gen_7_families.h`

*Glossary:* `TERM_PSYCHIC_POWER`

## Q135

**Question.** About half of the Easy Chat words were still English: 482 of the 999 words of the 18 word lists, plus the group names TIME and MISC. Frontier, Tent and Trainer Hill trainers speak in Easy Chat phrases, so many of their lines mixed the two directions ('לבחור YOU CAN / להאמין NOT TO'). The 1.0 release notes listed this as the first known issue and left open whether Easy Chat is translated in full or kept English.

*Source:* 1.0 known issue (tools/hebrew/release/notes.json); HANDOFF section 8.2; the round-16 Trainer Hill review (trainer_hill-002) and the Easy Chat cursor, keyboard and YES/NO findings of the same round (contests_menus-002, -r01, -r02).

**Analysis.**
- The English words were exactly the short ones: every word of 1 to 5 letters was English and every word of 6 or more was Hebrew. The species and move groups already print the Hebrew name tables.
- FireRed translated its whole list (997 words) and kept its English letter index. 481 of the 482 English words have a FireRed word; EMERALD has none.
- A trainer phrase is six words joined with spaces in the English word order, three to a line. The RTL renderer draws a run of Latin letters left to right as one block, so a mixed line reads in two directions, and a ! or ? after a Latin word lands at the wrong end.
- The Odd Egg interview compares four words with eleven passwords (src/easy_chat.c sInterviewPasswords). Its four Day Care hint windows gave the English word in parentheses, and three named words the list no longer has: the cries LALALA and OI, OI, OI, and the actions STORES and ANGERS. The Tyrogue hint's type word קרב (FIGHTING) was also the text of BATTLE, so a player could pick the wrong one.
- English never shows two words with the same text. Hebrew has one word for several English ones (a pronoun and the pronoun with 'is', IT, THIS and IT'S, NOT and NO): with FireRed's words as they are, 141 words would share one of 64 texts. FireRed ships with 82 shared texts. The game tells words apart by their ID only where it compares a phrase word by word with fixed words (src/easy_chat.c): the Odd Egg passwords, the questionnaire's Mystery Gift phrase LINK TOGETHER WITH ALL, which an H&S mart reaches, and the Berry Master's wife's phrases, which it does not.
- A group list is shown in the order of the .alphabeticalOrder fields of its group file, the English alphabetical order. The ABC keyboard (src/data/easy_chat/easy_chat_words_by_letter.h) files every word, species and move under the English initial of its English spelling.
- Widths: the widest English word is 72 px and 12 bytes; a fixed phrase switches to two words a line above 204 px.

| Option | How | Risk |
|---|---|---|
| a. Translate every word | FireRed's word first, the glossary for names and terms, our own where FireRed's misreads or another word already prints it. A text of its own for every compared word; other words share a text only where Hebrew has one word. Hebrew order for the group lists. | Word-by-word Hebrew in the English word order is rough, as in FireRed. Text and display order only: word IDs and which words are unlocked do not change. |
| b. Revert the lists to English | 517 words back to English. | Species and move names stay Hebrew, so phrases stay mixed, and lines of English words still put ! and ? at the wrong end. |
| c. Leave the lists mixed | No change. | The known issue and the broken Odd Egg hints stay. |

**Chosen:** a.
- The 482 words: FireRed's word for 354, the glossary for 30 (the types and abilities of the status group, TYPE סוג, BERRY, BIKE, PC, MONEY, RADIO, RIVAL, EGG, BAG, RUBY אודם, EMERALD ברקת, POKéNAV and the token words {POKEBLOCK} פוקיבלוק and {PK}RS פוקרוס), and our own for 98. POKéNAV is פוקינאב, a new glossary row by the house form POKé = פוקי. Disabled version words take FireRed's colours and metals (RED אדום, GREEN ירוק, GOLD זהב), as SILVER כסף already did. TIME and MISC. are זמן and שונות, FireRed's group names.
- A text of its own for every word the game compares: the 38 Odd Egg password words, LINK, TOGETHER, WITH and ALL, and the Berry Master's wife's words each print a text no other enabled word prints. Other words share a text where Hebrew has one word for several English ones, as FireRed does. A first pass kept every text apart, as English does; that put the formal present into the words trainers speak most (I AM הנני, IS הינו, YOU'RE הינך, ARE הינם, THAT'S הרי זה, in 434 of the 1,359 distinct trainer phrases), against the spoken register of STYLE section 1, and its pairs still differed by one letter (HE'S הנו and IS הינו, HEY הי and HI היי). Ten texts are shared, each listed in SHARED_TEXTS of tools/hebrew/tests/test_easy_chat.py: I and I AM אני, YOU and YOU'RE אתה, HE and IS הוא, THEY and ARE הם, THIS, THAT'S and IT זה, NOT, NO, DON'T and AREN'T לא, GOOD and WELL טוב, OTHER and ELSE אחר, HI and HEY היי, WINS and WINNER מנצח. Either word prints the same phrase; a group list shows both (five pairs share a list: I and I AM, YOU and YOU'RE, NOT and DON'T, GOOD and WELL, HI and HEY), and an ABC list offers one entry per text. The rarely spoken HE'S הנו, SHE IS הינה, THEY'RE הנם, WE'RE אנו, IT'S זהו and ISN'T אינו keep the first pass's texts, so the lists show fewer equal entries. A and AN are אחד and אחת.
- Words read in the phrases that use them: DON'T is לא, not אל, which forbids only before a future verb while the Easy Chat verbs are infinitives (לא לוותר); NO is לא, not לא!, which put a ! into all 31 of its phrases; THAT זאת (the pronoun; ההוא is "that one"); LOOK תראה (the verb in 17 of 22 phrases); LEFT השאיר (the verb in 4 of 5); RIGHT ממש (5 of its 15 phrases say right now or right away, 3 end in the tag right?, 6 mean "correct", 1 is the direction); NONE אף אחד (the pronoun, not the type row's ללא); OWN אישי; RULE שולט; WILL עומד and WON'T לא עומד (spoken; עתיד is formal and reads as "future" before a noun). LIKE stays כמו: the verb is 27 of its 49 uses and the preposition 22, and אוהב would turn the preposition into nonsense. Words changed so that their text is not a password word's or a move's: BATTLE דו-קרב (קרב is FIGHTING, a password word), MATCH UP התאמה, CONCEDE להודות בהפסד, SURRENDER להיכנע and FRONTIER החזית (their old texts are the moves SUBMISSION and FACADE); SHOULD אמור, SIMPLE בסיסי, FOREVER לתמיד and OPPONENT מתחרה, changed in the first pass, read well and stay. The battle group is קרבות, so no group bears the name of the type word ”קרב” that the Tyrogue hint quotes.
- Two words print the name of a move of the move lists, with glossary names on both sides: FLYING and FLY תעופה, BLAZE and EMBER להבה. They stay as the glossary gives them.
- Every word is at most 72 px and 12 bytes (the widest, להודות בהפסד, is 71 px); no fixed phrase of the Frontier, Tent, Trainer Hill or Pike trainers or the record-mix defaults passes 204 px (1,493 phrases, widest line 136 px), and the in-game trade mails and Kenya's mail fit their window, two words a line in 178 px (widest line 80 px).
- The four hint windows follow the English sentences in Hebrew only and quote the list word with ”…”: היכולת של פיצ'ו היא ”סטטי”, טיירוג הוא מסוג ”קרב”, אלקיד אומר ”הי, הי, הי”, אלקיד ”מאחסן” מטען חשמלי. The passwords do not change.
- Under TEXT_RTL the group lists take their order from src/data/easy_chat/easy_chat_order_rtl.h, which tools/hebrew/gen_ec_order.py generates from the word texts in Hebrew alphabetical order; the group files keep the English fields, so they differ from the English baseline only in their texts. tools/hebrew/tests/test_easy_chat.py checks no Latin, the listed shared texts, a text of its own for every compared word, the fixed phrase widths, the generated order and the hint quotes.
- The keyboard and the screen layout, in engine code under TEXT_RTL (the #else branch is upstream's):
  - The ABC keyboard shows the 22 letters and אחר right to left in the English grid: א to ו and אחר, ז to ל, מ to ק, ר to ת. The four keys after ת are blank, map to אחר and are skipped by the cursor. Each key opens a list of src/data/easy_chat/easy_chat_words_by_letter_rtl.h, which tools/hebrew/gen_ec_letters.py generates: the entries of the English lists, each under the first letter of the text it prints (the word, species or move name). Entries that print one text are one entry, as upstream's DOUBLE_SPECIES_NAME pairs are: the 67 species pairs stay pairs; FLYING and FLY, MONEY and SILVER, BLAZE, FLAME and EMBER, and the words of each of the ten shared texts become one entry each; the English pair PSYCHIC is filed apart, the type פסיכי under פ and the move אשליה under א.
  - The longest list, מ, has 239 entries (298 if the unused Japanese lists and both halves of each species pair are counted). That is under EC_MAX_WORDS_IN_GROUP (270), so no constant changes: struct EasyChatScreenWordData, the screen's heap buffer, which is not saved, keeps its 15,268 bytes. The generated header asserts both limits at build time.
  - The lower window mirrors around the frame drawn behind it, the keyboard frame (inside x 16-184) for the group names and the letters and the list frame for the words, so both columns of group names show. The cursor box, the word-select cursor and the phrase and footer cursor stand at the mirrored x, the triangles point left, and LEFT and RIGHT move the way the mirrored columns run.
  - The YES/NO box of the confirm, exit and delete-all prompts sits over the footer's OK option at the left end, tiles 2-6 instead of 22-26 on every frame: the mirror of English's place, one tile nearer the screen edge, because אישור is twice as wide as OK and the exact mirror left its last letter showing (and, on the interview frame beside the two people, put the box in the middle of the footer). On the win and loss screens it covers no word of the phrase.
  - The mode tab's alphabet frame reads מצב over א-ת (graphics/easy_chat/mode.png), the short form of the Pokédex's מצב א' עד ת'; the engine branch keeps the English file.
  - The phrase and footer cursor was not in the round-16 findings: it stood at the English x, at the far end of the row from the first word, and on the footer it marked OK when DEL. ALL was selected.
  - The header holds only word constants and the engine commits have no Hebrew text, so they are picked onto he/renderer; there the English words are filed under the initials of their Hebrew texts. After a word, species or move rename, run gen_ec_order.py and gen_ec_letters.py (CI runs both with --check) and pick the regenerated headers onto he/renderer.
- Seen on the clip build with 0 clip records: the four hint windows, the interview with its keyboards and the status, voices, feelings and actions lists, Pichu's password giving the egg, the Battle Tower feelings man's start, win and loss screens and the first Trainer Hill floor's trainer lines; then, with the keyboard and layout change, every key of the Hebrew keyboard and every one of its 23 lists, the cursors in every column, and every screen type whose script an H&S map or the party menu reaches opened with no crash and the same heap buffer: the Day Care interview, mail written from the bag, the feelings man's three, the contest and Battle Tower interviews, the apprentice's win speech and the mart questionnaire. The quiz, Bard, trendy-phrase, fan-club and profile screens belong to Emerald scripts H&S cannot reach. After the shared texts and the word fixes: the people, endings, speech, misc, hobbies, conditions, battle and actions lists, the group keyboard with קרבות, the mode tab with א-ת, eight Frontier and tent intros, eight win and loss speeches, a Battle Tower battle's two speeches, two Trainer Hill lines, the feelings man's default start phrase and Kenya's mail read from the party, all in the new words; the box over OK with no letter beside it in all 39 YES/NO prompts of the tours; all 11 Odd Egg answers still giving their egg.

*Changed:* `src/data/easy_chat/easy_chat_group_*.h` (18 files), `src/data/easy_chat/easy_chat_groups.h`, `graphics/easy_chat/mode.png`, `src/data/easy_chat/easy_chat_order_rtl.h`, `src/data/easy_chat/easy_chat_words_by_letter_rtl.h`, `src/easy_chat.c`, `src/text_input_strings.c`, `include/strings.h`, `src/data/help_window.h`, `tools/hebrew/gen_ec_order.py`, `tools/hebrew/gen_ec_letters.py`, `tools/hebrew/tests/test_easy_chat.py`, `tools/hebrew/drift.py`, `tools/hebrew/status_report.py`, `tools/hebrew/make_chunks.py`, `tools/hebrew/release/notes.json`, `.github/workflows/hebrew.yml`

*Glossary:* `TERM_POKENAV`

## Q137

**Question.** In the Gen 4 battle interface, the frostbite tag is a copy of the burn tag, so a frostbitten Pokémon shows a blue pill reading כויה. English 2.0.6 has the same copy (BRN). The handoff asked the owner whether to redraw it or list it in the release notes.

*Source:* HANDOFF section 8.2, a question for the owner found in the cross-check against the Spanish translation.

**Analysis.** graphics/battle_interface/gen4/status.png, status2.png, status3.png and status4.png (one per battler) are 24 x 48 sheets of six 8-px rows: PSN, PRZ, SLP, FRZ, BRN, FRB (src/battle_interface.c). In all four, row 5 (FRB) is the same as row 4 (BRN), as in the English sheets. The H&S sheets (graphics/battle_interface/hns/) have קור in row 5.
- Frostbite is off in H&S: B_USE_FROSTBITE is FALSE (include/config/battle.h), so MOVE_EFFECT_FREEZE_OR_FROSTBITE means freeze. Only the debug menus can set it (the battle debug menu, and Inflict Status1 in the R+START menu), and only the Gen 4 interface option (UseGen4BattleUI) draws these sheets. Frostbite draws these tiles in the freeze colour (PAL_STATUS_FRZ).
- The H&S rows FRZ and FRB differ only inside x 3-17, and the Gen 4 FRZ row equals the H&S FRZ row there, so the H&S glyph fits the Gen 4 pill unchanged.

| Option | How | Risk |
|---|---|---|
| A. List it in the release notes | No change. | A note about a debug-only screen tells a player nothing they can act on. |
| B. Redraw row 5 with the H&S glyph | In each sheet, a pixel of the pill is glyph where the H&S sheet's row 5 has its קור glyph, and the sheet's own body index (76 + battler) elsewhere. Frame, background, the other rows and the palette stay. | Low. 30 pixels per sheet; art only. |
| C. The same with the H&S body index (60 + battler) | As B. | The same tiles in game, but 135 changed pixels per sheet. |
| D. Point frostbite at the freeze tiles in code | Change src/battle_interface.c. | An engine change, and the tag would read קפוא, not קור. |

**Chosen:** B. Pure art with no behaviour change, the word the H&S sheets already use, and the smallest diff.

*Changed:* `graphics/battle_interface/gen4/status.png`, `graphics/battle_interface/gen4/status2.png`, `graphics/battle_interface/gen4/status3.png`, `graphics/battle_interface/gen4/status4.png`

## Proposed names

The 1,851 glossary names with status "proposed" (Gen 4+ Pokémon, NPCs, places, trainer classes) were checked against the transliteration rules, the official English pronunciation and consistency with related names, and every proposed change was then argued against by a second reviewer. 23 changes survived. The table gives the result in the tree; the full reasons are in the glossary notes.

| Name | English | Was | Proposed | Now | Why |
|---|---|---|---|---|---|
| `CONTEST_OPPONENT_HEATH_NICKNAME` | HEROSS | הרוס | הירוס | הירוס | Hebrew readers read the current spelling הרוס as the ordinary word harus, 'ruined/wrecked'. |
| `FRONTIER_TRAINER_220_LEON` | LEON | לאון | ליאון | ליאון | The usual English pronunciation of LEON is LEE-on, and rules §3 write e /i/ before a vowel as י (VAPOREON ופוריאון, CHARMELEON צ'רמיליון, GEODUDE ג'יאודוד). |
| `FRONTIER_TRAINER_32_MARCO` | MARCO | מארקו | מרקו | מרקו | MARCO is MAR-koh, the same sound as FR canon TRAINER_HIKER_MARCOS מרקוס (pokefirered-heb trainers.h:1805-1809) minus the -s. |
| `NAME_DOUBLE_JAW_(CATEGORY,_SPECIES_FERALIGATR_MEGA)` | Double Jaw (category, SPECIES_FERALIGATR_MEGA) | לסת | לסת כפולה | לסת כפולה | The row is cut off after its first word: לסת alone just means 'jaw'. |
| `NAME_ETERNAL_FLOWER` | ETERNAL FLOWER | הפרח | הפרח הנצחי | הפרח הנצחי | The row is cut off after its first word: הפרח alone means 'the flower'. |
| `NAME_GIGANTAMAX` | GIGANTAMAX | ג'ימקס | ג'ייגנטמקס | ג'ימקס | kept: the game uses one word for both Gigantamax and G-Max, ג'ימקס, in over 80 move names, move descriptions and battle lines, where the long form does not fit |
| `NAME_GLACIA` | GLACIA | גלסיה | גלייסיה | גלייסיה | Glacia is said GLAY-see-uh: /eɪ/ = יי (§3: GRACE גרייס, RATICATE רטיקייט). |
| `NAME_GIGANTAMAX_(TERM)` | Gigantamax (term) | גיגנטמקס | ג'ייגנטמקס | ג'ימקס | unified with NAME_GIGANTAMAX on ג'ימקס (was גיגנטמקס, which reads like the Hebrew word גיגנטי) |
| `NAME_HIGH_KING_(CATEGORY)` | High King (category) | מלך | מלך עליון | מלך עליון | The row is cut off after its first word: מלך alone means 'king'. |
| `NAME_MEGA_EVOLUTION` | MEGA EVOLUTION | התפתחות | התפתחות מגה | התפתחות מגה | The row is cut off after its first word: התפתחות alone means just 'evolution'. |
| `NAME_MEGA_SOL_CANNON` | MEGA SOL CANNON | תותח | תותח שמש מגה | תותח שמש מגה | The row is cut off after its first word: תותח alone means 'cannon'. |
| `NAME_MEGA_STONE` | MEGA STONE | אבן | אבן מגה | אבן מגה | The row is cut off after its first word: אבן alone means 'stone'. |
| `NAME_THE_ROYAL_PINK_PRINCESS_(DIANCIE_MEGA_EPITHET)` | the Royal Pink Princess (Diancie Mega epithet) | הנסיכה | הנסיכה הוורודה המלכותית | הנסיכה הוורודה המלכותית | The row is cut off after its first word: הנסיכה alone means 'the princess'. |
| `NAME_THE_BLOOD-SOAKED_CRESCENT_(SALAMENCE_MEGA_EPITHET)` | the blood-soaked crescent (Salamence Mega epithet) | הסהר | הסהר הספוג בדם | הסהר הספוג בדם | The row is cut off after its first word: הסהר alone means 'the crescent'. |
| `SPECIES_ANNIHILAPE` | ANNIHILAPE | אנייהיליפ | אנייאליפ | אנייאליפ | Annihilape is said like 'annihilate' (/əˈnaɪəleɪt/): uh-NYE-uh-layp. |
| `SPECIES_EXEGGUTOR_ALOLA` | EXEGGUTOR-A | אקזגוטר-א | אקזגיוטר-א | אקזגקיוטר-א | Pronunciation: EXEGGUTOR is said eg-ZEG-yoo-ter, and the row 184 note says the same. Later given the full base form (Q129). |
| `SPECIES_KRICKETUNE` | KRICKETUNE | קריקטיון | קריקטון | קריקטון | The binding pronunciation is TPC's English, which is US English: KRIK-eh-toon, with /tuːn/ (no y-glide after t). |
| `SPECIES_PAWMI` | PAWMI | פאומי | פומי | פומי | PAW-mee: medial aw /ɔː/ before a consonant is written ו everywhere in FireRed: CRAWDAUNT קרודונט (species_names.h:329), DAWN דון (trainers.h:1269), SHAWN שון (trainers.h:2889). |
| `SPECIES_PAWMO` | PAWMO | פאומו | פומו | פומו | PAW-moh. |
| `SPECIES_PAWMOT` | PAWMOT | פאומוט | פומוט | פומוט | PAW-mot (the batch reason said 'PAW-met'; corrected here). |
| `SPECIES_ZACIAN_HERO` | ZACIAN | זאסיאן | זאשיאן | זאשיאן | TPCi gave PokeBeach the official pronunciation 'ZAH-shee-ən' (https://x.com/pokebeach/status/1163887152452628480), and Marriland's 'ZAH-shee-in' agrees. |
| `TRAINER_CLASS_PIKE_QUEEN` | PIKE QUEEN | מלכת הרומח | מלכת השביל | מלכת השביל | PIKE = שביל, as in the facility name BATTLE PIKE שביל הקרב; רומח (a spear) read as a weapon |
| `TRAINER_CLASS_PIKE_QUEEN_HNS` | PIKE QUEEN | מלכת הרומח | מלכת השביל | מלכת השביל | Same as row 4831 TRAINER_CLASS_PIKE_QUEEN, and it must stay identical to it. |

Eight more rows had kept only the first word of a multi-word Hebrew name (for example הסהר for הסהר הספוג בדם); they were completed from the text that uses them.

## Review of the changed screens

Every screen these decisions changed was reviewed on the release candidate (60 tour frames, 119 dialogue labels on 336 pages), and each finding was then checked by a second reviewer who tried to refute it. 8 findings were confirmed and 8 refuted.

| Finding | Handling |
|---|---|
| The narrowed mem of the fainted tag had no base and read as ח | Redrawn with the base open at the bottom left, as the game's small-font mem; the ayin got a tail |
| Stat changes read "התקפה בחדות ירד!", with the adverb in the English slot | The intensity words follow the verb in all eleven stat change strings: "התקפה ירד בחדות!" |
| The Pike Queen glossary notes still argued for רומח | Rewritten for מלכת השביל |
| A blank line was left inside a Hiker text (Q84) | Removed |
| MIMI: "להיות חברה שלי" reads first as "my girlfriend" | "להיות ידידה שלי" |
| The nickname tour still typed with the old cursor rule (K4) | The tour was updated; the ROM was right |
| A geresh in a summary nickname touches the portrait box (a side effect of K5) | Listed as a known issue; fixed later (Q128) |
| A page ending in a colon draws it against the continue arrow | Listed as a known issue |

