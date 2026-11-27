#ifndef GUARD_CONSTANTS_HOENN_EVENTS_H
#define GUARD_CONSTANTS_HOENN_EVENTS_H

// Hoenn & Seek 2.0: who owns which event flags and vars.
//
// 2.0 adds a lot of events (starter scenes, hidden events, legendary chains),
// so instead of one long list that every part appends to, the 2.0 flag and var
// ranges (constants/hoenn_layout.h) are split into one block per build phase.
// A part defines its flags inside its phase's block, in its own section of
// this file, as BLOCK_START + n:
//
//     // Part 22a: Absol, the storm wanderer (Route 120)
//     #define FLAG_HOENN_ABSOL_WOKEN   (HOENN_FLAGS_E_HOENN + 0x00) // cliff scene seen; roaming
//     #define FLAG_HOENN_ABSOL_CAUGHT  (HOENN_FLAGS_E_HOENN + 0x01)
//
// Rules:
// - Every name starts with FLAG_HOENN_ / VAR_HOENN_, so gen_hoenn_ids.py
//   leaves it alone.
// - Use the next free number in the block and keep each part's flags together.
// - If a block fills up, take the next one from HOENN_FLAGS_SPARE / the spare
//   vars and say so in a comment. Never move a block: numbers are saved.
// - src/hoenn_flags.c checks at build time that the blocks don't overlap.
// - Daily flags reset every morning with HnS's; weekly flags reset once a week.
//   Use them for "once a day" / "once a week" events instead of a counter.
// - Hidden items placed by 2.0 events (bg_event "hidden_item") need a flag
//   below 0x20E9, so they take theirs from HOENN_EVENT_HIDDEN_ITEMS_START.
//
// Block sizes are estimates from claude/hns-2.0-plan.md, with room to spare.
// Phase letters and part numbers follow claude/hns-2.0-roadmap.md.

#include "constants/hoenn_layout.h"

// ---- Flag blocks (0x2040-0x22FF) -----------------------------------------
//                                                   start   size  phase
#define HOENN_FLAGS_A_FOUNDATIONS   (HOENN_EVENT_BLOCKS_START + 0x000) //  16  A: weekday, caps, followers (parts 1-4)
#define HOENN_FLAGS_B_WEATHER_HINTS (HOENN_EVENT_BLOCKS_START + 0x010) //  32  B: weather, hint engine, forecasts (5-7)
#define HOENN_FLAGS_C_BUILDINGS     (HOENN_EVENT_BLOCKS_START + 0x030) //  64  C: opened buildings: gifts, trades (8-11)
#define HOENN_FLAGS_C_WORLD         (HOENN_EVENT_BLOCKS_START + 0x070) //  32  C: secret base sites, sea route, art (12-14)
#define HOENN_FLAGS_D_STARTERS      (HOENN_EVENT_BLOCKS_START + 0x090) //  48  D: starter events (15-17)
#define HOENN_FLAGS_D_SPECIES       (HOENN_EVENT_BLOCKS_START + 0x0C0) //  32  D: species events (18-19)
#define HOENN_FLAGS_E_HOENN         (HOENN_EVENT_BLOCKS_START + 0x0E0) // 128  E: Hoenn hidden events (20-26)
#define HOENN_FLAGS_E_JOHTO_KANTO   (HOENN_EVENT_BLOCKS_START + 0x160) //  96  E: Johto/Kanto hidden events, Unown Cipher (27-32)
#define HOENN_FLAGS_F_LEGENDARIES   (HOENN_EVENT_BLOCKS_START + 0x1C0) // 128  F: legendary clues, keys, cameos (34-37)
#define HOENN_FLAGS_G_FINISH        (HOENN_EVENT_BLOCKS_START + 0x240) //  16  G: sweep and fixes (38-40)
#define HOENN_FLAGS_SPARE           (HOENN_EVENT_BLOCKS_START + 0x250) // 112  overflow for any phase
#define HOENN_FLAGS_BLOCKS_END      HOENN_DAILY_FLAGS_START            // first flag after the blocks

// ---- Var blocks (0x7080-0x70FF) ------------------------------------------
#define HOENN_VARS_A_FOUNDATIONS    (HOENN_EVENT_VARS_START + 0x00) //   8  A (weekday offset, ...)
#define HOENN_VARS_B_WEATHER_HINTS  (HOENN_EVENT_VARS_START + 0x08) //   8  B (hint toggle, ...)
#define HOENN_VARS_C_WORLD          (HOENN_EVENT_VARS_START + 0x10) //   8  C
#define HOENN_VARS_D_EVENTS         (HOENN_EVENT_VARS_START + 0x18) //  16  D (multi-visit counters, chase stages)
#define HOENN_VARS_E_EVENTS         (HOENN_EVENT_VARS_START + 0x28) //  40  E (Cipher fragments, quest stages)
#define HOENN_VARS_F_LEGENDARIES    (HOENN_EVENT_VARS_START + 0x50) //  24  F (clue counts, journal pages)
#define HOENN_VARS_G_FINISH         (HOENN_EVENT_VARS_START + 0x68) //   8  G
#define HOENN_VARS_SPARE            (HOENN_EVENT_VARS_START + 0x70) //  16  overflow
#define HOENN_VARS_BLOCKS_END       (HOENN_EVENT_VARS_START + HOENN_EVENT_VARS_COUNT)

// ==========================================================================
// Each part adds its section below, in roadmap order.
// ==========================================================================

// ---- Part 2: script helpers (src/hoenn_time.c) ----------------------------
// The weekday the game shows is the RTC's weekday plus this offset (0-6), so
// the player can line the game's week up with the real one without moving
// the day counter (that would run the daily resets and grow berries). Set it
// only through HoennSetWeekday(), which also keeps the week from rolling over.
#define VAR_HOENN_WEEKDAY_OFFSET  (HOENN_VARS_A_FOUNDATIONS + 0x00)
// The week the weekly flags were last reset in, plus one (0 = not seen yet:
// the next time check only records the week). See HoennUpdatePerWeek().
#define VAR_HOENN_WEEK_SEEN       (HOENN_VARS_A_FOUNDATIONS + 0x01)

// Weekdays as specialvar VAR_RESULT, GetDayOfWeek returns them. Scripts can't
// use enum Weekday, so these mirror it (src/hoenn_time.c checks they match).
#define HOENN_SUNDAY    0
#define HOENN_MONDAY    1
#define HOENN_TUESDAY   2
#define HOENN_WEDNESDAY 3
#define HOENN_THURSDAY  4
#define HOENN_FRIDAY    5
#define HOENN_SATURDAY  6
#define HOENN_WEEKDAY_COUNT 7 // also MULTI_DAYS_OF_WEEK's EXIT choice

// The day a new week starts on (weekly flags reset when it begins).
// Sunday, like the PokéGear calendar and the WEEKDAY_* order.
#define HOENN_WEEK_STARTS_ON      HOENN_SUNDAY

// Weather cycles are 4 days long (Emerald's weatherCycleStage, 0-3). Part 5
// gives each cycle route an offset; a route's "special weather" day is the one
// where (stage + offset) % 4 == HOENN_SPECIAL_WEATHER_STAGE. Stage 2 is Route
// 119's thunderstorm day in Emerald's own cycle, so offset 0 matches it.
#define HOENN_SPECIAL_WEATHER_STAGE 2

// ---- Part 3: HGSS's weekday content (data/scripts/hoenn_weekday.inc) -------
// Mt. Moon's Clefairy dance only on Monday nights. The eight Clefairy objects
// use this flag (they used FLAG_NIGHT_POKEMON); the map's OnTransition clears
// it on Monday nights and sets it otherwise.
#define FLAG_HOENN_HIDE_CLEFAIRY_DANCE  (HOENN_FLAGS_A_FOUNDATIONS + 0x00)
// Union Cave's Lapras comes back every Friday. Set when it's caught or knocked
// out; weekly, so it clears when the next week starts (Sunday).
#define FLAG_HOENN_WEEKLY_LAPRAS_MET    (HOENN_WEEKLY_FLAGS_START + 0x00)

// gettimeofday's times of day (enum TimeOfDay), for scripts:
// morning 0, day 1, evening 2, night 3.
#define HOENN_TIME_MORNING 0
#define HOENN_TIME_DAY   1
#define HOENN_TIME_EVENING 2
#define HOENN_TIME_NIGHT 3

// ---- Part 7: hint lines, rumors, forecasts (src/hoenn_hints.c) -------------
// Flips on every talk to a hint NPC: 0 = their own script next, 1 = their extra
// line next. One var for all of them, so there are no per-NPC flags (2.0-plan 2c).
#define VAR_HOENN_HINT_TOGGLE     (HOENN_VARS_B_WEATHER_HINTS + 0x00)

// ---- Parts 8a-11: opened buildings (data/hoenn/buildings.json) -------------
// Olivine lighthouse keeper's wife: one find from the shore a day (part 8b).
#define FLAG_HOENN_DAILY_KEEPER_GIFT  (HOENN_DAILY_FLAGS_START + 0x00)
// Celadon florist: one berry a day, by weekday (part 10).
#define FLAG_HOENN_DAILY_FLORIST_GIFT (HOENN_DAILY_FLAGS_START + 0x01)

// ---- Part 12: legendary sites reopened (data/hoenn/base_spots.json) --------
// May's PokéGear call once your secret base is at one of the sites.
#define FLAG_HOENN_CALL_SITES         (HOENN_FLAGS_C_WORLD + 0x00)

// ---- Part 13a: Johto/Kanto secret bases (data/hoenn/base_spots.json) -------
// Brendan's PokéGear call once your secret base is in Johto or Kanto.
#define FLAG_HOENN_CALL_JK_BASE       (HOENN_FLAGS_C_WORLD + 0x01)

// ---- Part 14: the Tidal Strait (data/hoenn/strait.json) --------------------
// The great whirlpool at the strait's Johto end is gone (Oak gave the TIDAL
// TICKET; the west half's OnTransition also sets it if the ticket is in the bag).
#define FLAG_HOENN_STRAIT_OPEN        (HOENN_FLAGS_C_WORLD + 0x02)
// You reached the strait's Hoenn half (May's PokéGear call).
#define FLAG_HOENN_CROSSED_STRAIT     (HOENN_FLAGS_C_WORLD + 0x03)
#define FLAG_HOENN_CALL_STRAIT        (HOENN_FLAGS_C_WORLD + 0x04)

// ---- Part 15a: Johto starters A (data/scripts/hoenn_starters.inc) ----------
// Each Johto starter's scene plays one of three versions by VAR_STARTER_MON:
// your own species is watch-only, the rival's is wild, the unclaimed one is the
// Pokémon Birch sent Elm that got loose (it joins you). All need
// FLAG_HOENN_BEAT_BM. The HIDE flags are decided on every arrival.
// Chikorita: the hidden meadow behind Route 46's cave, mornings and daytime.
#define FLAG_HOENN_CHIKORITA_SCENE      (HOENN_FLAGS_D_STARTERS + 0x00) // first sighting played
#define FLAG_HOENN_CHIKORITA_DONE       (HOENN_FLAGS_D_STARTERS + 0x01) // caught or joined you
#define FLAG_HOENN_HIDE_MEADOW_FAMILY   (HOENN_FLAGS_D_STARTERS + 0x02) // the Meganium and one Chikorita
#define FLAG_HOENN_HIDE_MEADOW_CHIKORITA (HOENN_FLAGS_D_STARTERS + 0x03) // the Chikorita that can stay
// Cyndaquil: Burned Tower B1F, at night.
#define FLAG_HOENN_CYNDAQUIL_SCENE      (HOENN_FLAGS_D_STARTERS + 0x04)
#define FLAG_HOENN_CYNDAQUIL_DONE       (HOENN_FLAGS_D_STARTERS + 0x05)
#define FLAG_HOENN_HIDE_BT_FAMILY       (HOENN_FLAGS_D_STARTERS + 0x06) // the Typhlosion and one Cyndaquil
#define FLAG_HOENN_HIDE_BT_CYNDAQUIL    (HOENN_FLAGS_D_STARTERS + 0x07) // the Cyndaquil that can stay
// Brendan's PokéGear call once Birch's runaway is with you.
#define FLAG_HOENN_CALL_STARTER_FOUND   (HOENN_FLAGS_D_STARTERS + 0x08)

// ---- Part 15b: Johto starters B -------------------------------------------
// Totodile: the Lake of Rage's south cove, any time but night.
#define FLAG_HOENN_TOTODILE_SCENE       (HOENN_FLAGS_D_STARTERS + 0x09)
#define FLAG_HOENN_TOTODILE_DONE        (HOENN_FLAGS_D_STARTERS + 0x0A)
#define FLAG_HOENN_HIDE_LAKE_FAMILY     (HOENN_FLAGS_D_STARTERS + 0x0B) // the Feraligatr and one Totodile
#define FLAG_HOENN_HIDE_LAKE_TOTODILE   (HOENN_FLAGS_D_STARTERS + 0x0C) // the Totodile that can stay

// ---- Part 16: Kanto starters A (data/scripts/hoenn_kanto_starters.inc) ------
// Bulbasaur: the hidden garden behind Bill's house (Route25_Garden_hoenn), mornings.
#define FLAG_HOENN_BULBASAUR_SCENE      (HOENN_FLAGS_D_STARTERS + 0x0D) // the ceremony played
#define FLAG_HOENN_BULBASAUR_DONE       (HOENN_FLAGS_D_STARTERS + 0x0E) // it joined you
#define FLAG_HOENN_HIDE_GARDEN_FAMILY   (HOENN_FLAGS_D_STARTERS + 0x0F) // the Venusaur and three Bulbasaur
#define FLAG_HOENN_HIDE_GARDEN_YOUNG    (HOENN_FLAGS_D_STARTERS + 0x10) // the three that evolve in the ceremony
#define FLAG_HOENN_HIDE_GARDEN_IVYSAUR  (HOENN_FLAGS_D_STARTERS + 0x11) // ...and the Ivysaur they became
#define FLAG_HOENN_HIDE_GARDEN_BULBASAUR (HOENN_FLAGS_D_STARTERS + 0x12) // the one that hid
// Charmander: waiting in the rain at the foot of Nugget Bridge (Route 24), evenings and nights.
#define FLAG_HOENN_CHARMANDER_DONE      (HOENN_FLAGS_D_STARTERS + 0x13) // it joined you
#define FLAG_HOENN_HIDE_CHARMANDER      (HOENN_FLAGS_D_STARTERS + 0x14)
#define FLAG_HOENN_CHARMANDER_TRAINER_BEATEN (HOENN_FLAGS_D_STARTERS + 0x15) // its old trainer, outside the Cerulean Gym
#define FLAG_HOENN_HIDE_CHARMANDER_TRAINER   (HOENN_FLAGS_D_STARTERS + 0x16)
// May's PokéGear call once a Kanto starter from these events is with you.
#define FLAG_HOENN_CALL_KANTO_STARTER   (HOENN_FLAGS_D_STARTERS + 0x17)
// 0 = waiting at the bridge, 1 = you're rushing it to the Cerulean Pokémon
// Center (its frame script plays the scene), 2 = it chose you.
#define VAR_HOENN_CHARMANDER_STATE      (HOENN_VARS_D_EVENTS + 0x00)

// ---- Part 17: Kanto starters B (data/scripts/hoenn_kanto_starters.inc) ------
// Squirtle: the Squirtle Squad. By day they play by Route 6's pond and dig
// pitfalls; one drops you into their hideout (Route6_Hideout_hoenn). At night
// they put out a house fire in Vermilion, and the leader (sunglasses) joins you.
#define FLAG_HOENN_SQUIRTLE_DONE        (HOENN_FLAGS_D_STARTERS + 0x18) // the leader joined you
#define FLAG_HOENN_HIDE_SQUAD_ROUTE6    (HOENN_FLAGS_D_STARTERS + 0x19) // three Squirtle by the pond
#define FLAG_HOENN_HIDE_SQUAD_LEADER    (HOENN_FLAGS_D_STARTERS + 0x1A) // ...and their leader, until the hideout
#define FLAG_HOENN_HIDE_SQUAD_VERMILION (HOENN_FLAGS_D_STARTERS + 0x1B) // the Squad at the burning house
#define FLAG_HOENN_SQUIRTLE_FIRE_OUT    (HOENN_FLAGS_D_STARTERS + 0x1C) // the fire scene played
// 0 = not met, 1 = you fell into the hideout (its frame script plays the
// scene), 2 = met them (Vermilion's fire waits for night), 3 = the leader joined.
#define VAR_HOENN_SQUIRTLE_STATE        (HOENN_VARS_D_EVENTS + 0x01)

// ---- Part 18: species events A (data/scripts/hoenn_species.inc) ------------
// Route 102, mornings: a Swampert watches two Mudkip practice in the pond, then
// they dive just before a sudden shower (watch-only). Not on the route's rain day.
#define FLAG_HOENN_HIDE_POND_FAMILY     (HOENN_FLAGS_D_SPECIES + 0x00) // Swampert and two Mudkip
#define FLAG_HOENN_POND_SEEN            (HOENN_FLAGS_D_SPECIES + 0x01) // the dive played once
// Route 102, mornings: a Gardevoir guards a Ralts near Petalburg. Walk up (no
// running, no bike) with a max-friendship lead on three mornings; on the third
// the Ralts joins you (hidden ability Telepathy). Rush in and they teleport away.
#define FLAG_HOENN_HIDE_RALTS           (HOENN_FLAGS_D_SPECIES + 0x02) // Gardevoir and the Ralts
#define FLAG_HOENN_RALTS_DONE           (HOENN_FLAGS_D_SPECIES + 0x03) // it joined you
// Mt. Mortar B1F, mornings: Kiyo spars with a wild Machamp. Watch the match and
// he gives you a Black Belt (once).
#define FLAG_HOENN_HIDE_KIYO_MACHAMP    (HOENN_FLAGS_D_SPECIES + 0x04)
#define FLAG_HOENN_KIYO_BLACK_BELT      (HOENN_FLAGS_D_SPECIES + 0x05)
// National Park, Tue/Thu/Sat evenings: a Scizor ends the Scyther duel in the
// back field and flicks a Quick Claw over the trees (once).
#define FLAG_HOENN_HIDE_SCIZOR          (HOENN_FLAGS_D_SPECIES + 0x06)
#define FLAG_HOENN_SCIZOR_QUICK_CLAW    (HOENN_FLAGS_D_SPECIES + 0x07)
// PokéGear event calls (src/hoenn_species.c).
#define FLAG_HOENN_CALL_POND            (HOENN_FLAGS_D_SPECIES + 0x08) // Brendan
#define FLAG_HOENN_CALL_RALTS           (HOENN_FLAGS_D_SPECIES + 0x09) // Wally
#define FLAG_HOENN_CALL_KIYO            (HOENN_FLAGS_D_SPECIES + 0x0A) // Brendan
#define FLAG_HOENN_CALL_SCIZOR          (HOENN_FLAGS_D_SPECIES + 0x0B) // May
// Once a day each: the scene played (or the Ralts visit counted, or they teleported away).
#define FLAG_HOENN_DAILY_POND           (HOENN_DAILY_FLAGS_START + 0x02)
#define FLAG_HOENN_DAILY_RALTS          (HOENN_DAILY_FLAGS_START + 0x03) // visited today
#define FLAG_HOENN_DAILY_RALTS_GONE     (HOENN_DAILY_FLAGS_START + 0x04) // ...and you rushed: gone till tomorrow
#define FLAG_HOENN_DAILY_KIYO_MATCH     (HOENN_DAILY_FLAGS_START + 0x05)
#define FLAG_HOENN_DAILY_SCIZOR         (HOENN_DAILY_FLAGS_START + 0x06)
// Mornings the Ralts has seen you come calmly with a Pokémon that loves you (0-3).
#define VAR_HOENN_RALTS_MORNINGS        (HOENN_VARS_D_EVENTS + 0x02)

// ---- Part 19: species events B (data/scripts/hoenn_species.inc) ------------
// Gengar: at night your shadow grins in Lavender, stops on Route 8, laughs in the
// Underground Path entrance, and jumps out at Lavender's Radio Tower (joins you).
#define FLAG_HOENN_GENGAR_DONE          (HOENN_FLAGS_D_SPECIES + 0x10) // it joined you
#define FLAG_HOENN_HIDE_GENGAR          (HOENN_FLAGS_D_SPECIES + 0x11) // its object in the Radio Tower
// 0 = not met, 1 = it grinned in Lavender, 2 = it stopped on Route 8,
// 3 = it laughed in the Underground Path entrance, 4 = it joined you.
#define VAR_HOENN_GENGAR_STATE          (HOENN_VARS_D_EVENTS + 0x03)
// Slowking: the sage in Slowpoke Well B2F asks one riddle per weekday; each
// riddle solved (once) teaches the next line of the Lugia prophecy (7 lines).
#define FLAG_HOENN_SLOWKING_RIDDLE_SUN  (HOENN_FLAGS_D_SPECIES + 0x12) // + weekday (HOENN_SUNDAY...), 7 flags
#define FLAG_HOENN_SLOWKING_PROPHECY    (HOENN_FLAGS_D_SPECIES + 0x19) // all seven lines heard
#define FLAG_HOENN_CALL_GENGAR          (HOENN_FLAGS_D_SPECIES + 0x1A) // Brendan
#define FLAG_HOENN_CALL_PROPHECY        (HOENN_FLAGS_D_SPECIES + 0x1B) // May
#define FLAG_HOENN_DAILY_SLOWKING       (HOENN_DAILY_FLAGS_START + 0x07) // one answer a day
#define VAR_HOENN_SLOWKING_LINES        (HOENN_VARS_D_EVENTS + 0x04) // lines taught (0-7)

// ---- Part 20: Route 113 and Petalburg Woods (data/scripts/hoenn_hidden.inc) ----
// Munchlax: asleep in a gap in Route 113's southern trees, in front of a hidden
// grotto. The glassblower's GLASS FLUTE wakes it, and it joins you.
#define FLAG_HOENN_MUNCHLAX_DONE        (HOENN_FLAGS_E_HOENN + 0x00) // it joined you (also its object flag)
#define FLAG_HOENN_ITEM_GROTTO_1        (HOENN_FLAGS_E_HOENN + 0x01) // the grotto's item balls
#define FLAG_HOENN_ITEM_GROTTO_2        (HOENN_FLAGS_E_HOENN + 0x02)
#define FLAG_HOENN_ITEM_GROTTO_3        (HOENN_FLAGS_E_HOENN + 0x03)
// Spinda: dances in the falling ash on Route 113 on weekday mornings, once a week.
#define FLAG_HOENN_HIDE_SPINDA          (HOENN_FLAGS_E_HOENN + 0x04)
#define FLAG_HOENN_WEEKLY_SPINDA        (HOENN_WEEKLY_FLAGS_START + 0x01) // danced (and battled) this week
#define FLAG_HOENN_SPINDA_MET           (HOENN_FLAGS_E_HOENN + 0x05) // for the rumor
// Slaking: dozes across a side path in Petalburg Woods; it only gets up at noon.
#define FLAG_HOENN_SLAKING_DONE         (HOENN_FLAGS_E_HOENN + 0x06) // caught
#define FLAG_HOENN_HIDE_SLAKING         (HOENN_FLAGS_E_HOENN + 0x07)
#define FLAG_HOENN_DAILY_SLAKING        (HOENN_DAILY_FLAGS_START + 0x08) // battled today: the path is open
#define FLAG_HOENN_ITEM_CLEARING_1      (HOENN_FLAGS_E_HOENN + 0x08) // the clearing's item balls
#define FLAG_HOENN_ITEM_CLEARING_2      (HOENN_FLAGS_E_HOENN + 0x09)
#define FLAG_HOENN_ITEM_CLEARING_3      (HOENN_FLAGS_E_HOENN + 0x0A)
#define FLAG_HOENN_CALL_MUNCHLAX        (HOENN_FLAGS_E_HOENN + 0x0B) // Brendan
#define FLAG_HOENN_CALL_SLAKING         (HOENN_FLAGS_E_HOENN + 0x0C) // May
#define FLAG_HOENN_GOT_GLASS_FLUTE      (HOENN_FLAGS_E_HOENN + 0x0D)

// ---- Part 21: Routes 119 and 114 (data/scripts/hoenn_hidden.inc) ----
// HoennTuneWildMonSlot's VAR_0x8009 bits (src/hoenn_hidden.c).
#define HOENN_TUNE_FEMALE          1
#define HOENN_TUNE_HIDDEN_ABILITY  2
// Tropius: mornings in a hidden orchard behind Route 119's trees (Route119_Orchard_hoenn).
#define FLAG_HOENN_TROPIUS_DONE         (HOENN_FLAGS_E_HOENN + 0x0E) // caught
#define FLAG_HOENN_HIDE_TROPIUS         (HOENN_FLAGS_E_HOENN + 0x0F)
#define FLAG_HOENN_TROPIUS_MET          (HOENN_FLAGS_E_HOENN + 0x10) // battled once: the fruit tree drops berries
#define FLAG_HOENN_DAILY_TROPIUS        (HOENN_DAILY_FLAGS_START + 0x09) // battled today
#define FLAG_HOENN_DAILY_ORCHARD_BERRY  (HOENN_DAILY_FLAGS_START + 0x0A)
// Feebas: the mirror pool on upper Route 119, evenings and nights, Old Rod, once a day.
#define FLAG_HOENN_DAILY_FEEBAS         (HOENN_DAILY_FLAGS_START + 0x0B)
#define FLAG_HOENN_FEEBAS_PRISM_GIVEN   (HOENN_FLAGS_E_HOENN + 0x11) // the first one caught came with a Prism Scale
// Zangoose vs. Seviper: Route 114's lake island, Sunday evenings and nights, once a week.
#define FLAG_HOENN_HIDE_FEUD          (HOENN_FLAGS_E_HOENN + 0x12)
#define FLAG_HOENN_WEEKLY_FEUD        (HOENN_WEEKLY_FLAGS_START + 0x02)
#define FLAG_HOENN_FEUD_MET           (HOENN_FLAGS_E_HOENN + 0x13)
#define FLAG_HOENN_CALL_TROPIUS         (HOENN_FLAGS_E_HOENN + 0x14) // Brendan
#define FLAG_HOENN_CALL_FEEBAS          (HOENN_FLAGS_E_HOENN + 0x15) // May
#define FLAG_HOENN_CALL_FEUD          (HOENN_FLAGS_E_HOENN + 0x16) // Brendan

// ---- Part 22a: Absol, the storm wanderer (src/hoenn_roamer.c, data/scripts/hoenn_hidden.inc) ----
// On Route 120's storm day, evenings and nights, Absol stands on the ridge above
// the route; seeing it starts it roaming Route 120 (storm evenings/nights only).
#define FLAG_HOENN_ABSOL_WOKEN          (HOENN_FLAGS_E_HOENN + 0x17) // the cliff scene played once: it roams
#define FLAG_HOENN_ABSOL_CAUGHT         (HOENN_FLAGS_E_HOENN + 0x18)
#define FLAG_HOENN_HIDE_ABSOL_CLIFF     (HOENN_FLAGS_E_HOENN + 0x19) // decided on every arrival
#define FLAG_HOENN_CALL_ABSOL           (HOENN_FLAGS_E_HOENN + 0x1A) // May
// specialvar VAR_RESULT, HoennAbsolState
#define HOENN_ABSOL_ASLEEP  0 // never woken (or this game's data is gone): the cliff scene creates it
#define HOENN_ABSOL_ROAMING 1
#define HOENN_ABSOL_DOWN    2 // knocked out: the cliff scene brings the same one back
#define HOENN_ABSOL_CAUGHT  3

// ---- Part 22b: Wailord's strait and atoll, Chimecho's chimes (data/scripts/hoenn_hidden.inc) ----
// HoennTuneWildMon's VAR_0x8006 value for "only the HP IV becomes 31" (TRUE = all six).
#define HOENN_TUNE_IV_HP  2
// Wailord sleeps in a one-tile strait at Route 131's bottom edge (17,38); a Wailmer lead
// wakes it on Saturday mornings. After its first battle the strait leads to an atoll
// (Route131_Atoll_hoenn), where it sleeps in the lagoon until it's caught.
#define FLAG_HOENN_WAILORD_MOVED        (HOENN_FLAGS_E_HOENN + 0x1B) // battled once: the strait is open (its Route 131 object flag)
#define FLAG_HOENN_WAILORD_CAUGHT       (HOENN_FLAGS_E_HOENN + 0x1C)
#define FLAG_HOENN_HIDE_WAILORD_ATOLL   (HOENN_FLAGS_E_HOENN + 0x1D) // decided on every arrival
#define FLAG_HOENN_WEEKLY_WAILORD       (HOENN_WEEKLY_FLAGS_START + 0x03) // battled this week
#define FLAG_HOENN_ITEM_ATOLL_1         (HOENN_FLAGS_E_HOENN + 0x1E) // the atoll's item balls
#define FLAG_HOENN_ITEM_ATOLL_2         (HOENN_FLAGS_E_HOENN + 0x1F)
#define FLAG_HOENN_ITEM_ATOLL_3         (HOENN_FLAGS_E_HOENN + 0x20)
#define FLAG_HOENN_HIDDEN_ATOLL_1       (HOENN_EVENT_HIDDEN_ITEMS_START + 0x00) // the atoll's hidden Heart Scales
#define FLAG_HOENN_HIDDEN_ATOLL_2       (HOENN_EVENT_HIDDEN_ITEMS_START + 0x01)
#define FLAG_HOENN_HIDDEN_ATOLL_3       (HOENN_EVENT_HIDDEN_ITEMS_START + 0x02)
#define FLAG_HOENN_CALL_WAILORD         (HOENN_FLAGS_E_HOENN + 0x21) // Brendan
// Chimecho: Mt. Pyre's summit at night, hidden in the top-left graves (8,4); rings of
// VAR_TEMP_4 triggers on the way make the chimes louder. Once a night until caught.
#define FLAG_HOENN_CHIMECHO_CAUGHT      (HOENN_FLAGS_E_HOENN + 0x22)
#define FLAG_HOENN_HIDE_CHIMECHO        (HOENN_FLAGS_E_HOENN + 0x23) // set on every arrival
#define FLAG_HOENN_CHIMECHO_MET         (HOENN_FLAGS_E_HOENN + 0x24) // battled once (rumor, call)
#define FLAG_HOENN_DAILY_CHIMECHO       (HOENN_DAILY_FLAGS_START + 0x0C)
#define FLAG_HOENN_CALL_CHIMECHO        (HOENN_FLAGS_E_HOENN + 0x25) // May

// ---- Part 23: Meteor Falls (data/scripts/hoenn_hidden.inc) ----
// HoennTuneWildMonSlot bit: the Pokémon becomes shiny (the chorus's Altaria).
#define HOENN_TUNE_SHINY  4
// Altaria's chorus: a clifftop above Meteor Falls (MeteorFalls_Clifftop_hoenn,
// through a cave mouth at 1F_1R (27,3)). Saturday mornings, once a week: watch
// from behind the boulders, or step out and the flock scatters until next week.
#define FLAG_HOENN_HIDE_CHORUS          (HOENN_FLAGS_E_HOENN + 0x26) // decided on every arrival
#define FLAG_HOENN_CHORUS_WATCHED       (HOENN_FLAGS_E_HOENN + 0x27) // watched once to the end (rumor, call, shiny add-on)
#define FLAG_HOENN_HIDE_SHINY_ALTARIA   (HOENN_FLAGS_E_HOENN + 0x28) // set on every arrival
#define FLAG_HOENN_SHINY_ALTARIA_DONE   (HOENN_FLAGS_E_HOENN + 0x29) // caught
#define FLAG_HOENN_WEEKLY_CHORUS        (HOENN_WEEKLY_FLAGS_START + 0x04) // watched or scattered this week
#define FLAG_HOENN_CALL_CHORUS          (HOENN_FLAGS_E_HOENN + 0x2A) // May
// Bagon's leap: Meteor Falls B1F_2R's top ledge, mornings, once a day until caught.
#define FLAG_HOENN_BAGON_CAUGHT         (HOENN_FLAGS_E_HOENN + 0x2B)
#define FLAG_HOENN_HIDE_BAGON           (HOENN_FLAGS_E_HOENN + 0x2C) // decided on every arrival
#define FLAG_HOENN_BAGON_MET            (HOENN_FLAGS_E_HOENN + 0x2D) // battled once (rumor, call)
#define FLAG_HOENN_DAILY_BAGON          (HOENN_DAILY_FLAGS_START + 0x0D)
#define FLAG_HOENN_CALL_BAGON           (HOENN_FLAGS_E_HOENN + 0x2E) // Brendan
// Metagross (watch-only): two Metang fuse in Steven's cave at night, once a week.
#define FLAG_HOENN_HIDE_METANG          (HOENN_FLAGS_E_HOENN + 0x2F) // decided on every arrival
#define FLAG_HOENN_HIDE_METAGROSS       (HOENN_FLAGS_E_HOENN + 0x30) // set on every arrival
#define FLAG_HOENN_METAGROSS_SEEN       (HOENN_FLAGS_E_HOENN + 0x31) // watched once (Comet Shard the first time; rumor, call)
#define FLAG_HOENN_WEEKLY_METAGROSS     (HOENN_WEEKLY_FLAGS_START + 0x05)
#define FLAG_HOENN_CALL_METAGROSS       (HOENN_FLAGS_E_HOENN + 0x32) // Brendan

// ---- Part 24a: Flygon's desert song A (data/scripts/hoenn_hidden.inc) ----
// Route 111, evenings: a hum over the desert, and a Trapinch that scurries off
// into a sand hollow at the desert's north edge (30,35). Fallarbor's old-timers
// say the sand drains into the Fossil Maniac's tunnel; in the Desert
// Underpass's sandy east end a Vibrava fans the sand. Beat it (it can't be
// caught) and it leaves the Singing Sand. Part 24b continues the chain.
#define FLAG_HOENN_DESERT_SONG_HEARD    (HOENN_FLAGS_E_HOENN + 0x33) // the Route 111 Trapinch scene played once
#define FLAG_HOENN_HIDE_DESERT_TRAPINCH (HOENN_FLAGS_E_HOENN + 0x34) // decided on every arrival
#define FLAG_HOENN_DAILY_DESERT_SONG    (HOENN_DAILY_FLAGS_START + 0x0E) // the scene played today
#define FLAG_HOENN_HIDE_UNDERPASS_VIBRAVA (HOENN_FLAGS_E_HOENN + 0x35) // decided on every arrival
#define FLAG_HOENN_GOT_SINGING_SAND     (HOENN_FLAGS_E_HOENN + 0x36) // beat the Vibrava (the Singing Sand)
#define FLAG_HOENN_CALL_SINGING_SAND    (HOENN_FLAGS_E_HOENN + 0x37) // Brendan

// ---- Part 24b: Flygon's desert song B (data/scripts/hoenn_hidden.inc) ----
// Route 113, evenings: the Vibrava circles the ash outside the Glass Workshop
// and its hum answers the Singing Sand. The glassblower then fuses the sand
// into the SAND CHIME. Lavaridge's hot-springs granny: "ring it in the desert
// at sunset". Ringing it on Route 111's desert in the evening raises the
// Mirage Tower for the rest of the day (src/hoenn_hidden.c,
// HoennMirageTowerRung; it never shows by chance any more). A Flygon waits at
// the top, in front of Emerald's two fossils; once it's caught, taking a
// fossil collapses the tower for good, as in Emerald.
#define FLAG_HOENN_HIDE_ROUTE113_VIBRAVA (HOENN_FLAGS_E_HOENN + 0x38) // decided on every arrival
#define FLAG_HOENN_ROUTE113_VIBRAVA_SEEN (HOENN_FLAGS_E_HOENN + 0x39) // the Route 113 scene played
#define FLAG_HOENN_GOT_SAND_CHIME       (HOENN_FLAGS_E_HOENN + 0x3A)
#define FLAG_HOENN_MIRAGE_RAISED        (HOENN_FLAGS_E_HOENN + 0x3B) // the chime raised the tower at least once
#define FLAG_HOENN_HIDE_MIRAGE_FLYGON   (HOENN_FLAGS_E_HOENN + 0x3C) // decided on every arrival at 4F
#define FLAG_HOENN_CAUGHT_FLYGON        (HOENN_FLAGS_E_HOENN + 0x3D)
#define FLAG_HOENN_ITEM_MIRAGE_DRAGON_FANG (HOENN_FLAGS_E_HOENN + 0x3E) // item ball on 4F
#define FLAG_HOENN_CALL_FLYGON          (HOENN_FLAGS_E_HOENN + 0x3F) // May
#define FLAG_HOENN_DAILY_MIRAGE_TOWER   (HOENN_DAILY_FLAGS_START + 0x0F) // rung today: the tower stands until midnight
// specialvar VAR_RESULT, HoennSandChimePlace
#define HOENN_CHIME_ELSEWHERE 0
#define HOENN_CHIME_DESERT    1
#define HOENN_CHIME_ON_TOWER  2 // standing where the tower would rise

// ---- Part 25a: Night dive A (src/hoenn_lights.c, data/scripts/hoenn_hidden.inc) ----
// Underwater Route 124, nights: a Chinchou's light waits in the north-west
// basin. Swim close and it drifts on to the next spot; stray too far and the
// lights scatter back to the start (follow-the-lights, data/hoenn/light_paths.json).
// It leads to the bottom of the south-east basin and slips into a crack, which
// stays open from then on. Going down needs a Chinchou or Lanturn in the party
// to light the way. The trench below is part 25b's.
#define FLAG_HOENN_HIDE_DIVE_LIGHT      (HOENN_FLAGS_E_HOENN + 0x40) // decided on every arrival
#define FLAG_HOENN_TRENCH_FOUND         (HOENN_FLAGS_E_HOENN + 0x41) // the lights led you to the crack
#define FLAG_HOENN_TRENCH_ENTERED       (HOENN_FLAGS_E_HOENN + 0x42) // swam down into the trench once
#define FLAG_HOENN_CALL_TRENCH          (HOENN_FLAGS_E_HOENN + 0x43) // Brendan

// ---- Part 25b: Night dive B (data/scripts/hoenn_hidden.inc) ----
// The trench under Underwater Route 124. A guardian waits at the bottom of the
// trench, a different one by weekday: Huntail Mon/Wed/Fri, Gorebyss Tue/Thu/Sat,
// Relicanth Sun (hidden ability, perfect IVs). A pearl bed of three Clamperl
// gives two Big Pearls and a Pearl String, each once a week. Once all three
// guardians are caught, the mound's old cavern door opens onto its hollow,
// where the Deep Sea Tooth and Deep Sea Scale lie.
#define FLAG_HOENN_HIDE_HUNTAIL         (HOENN_FLAGS_E_HOENN + 0x44) // decided on every arrival
#define FLAG_HOENN_HIDE_GOREBYSS        (HOENN_FLAGS_E_HOENN + 0x45) // decided on every arrival
#define FLAG_HOENN_HIDE_RELICANTH       (HOENN_FLAGS_E_HOENN + 0x46) // decided on every arrival
#define FLAG_HOENN_CAUGHT_HUNTAIL       (HOENN_FLAGS_E_HOENN + 0x47)
#define FLAG_HOENN_CAUGHT_GOREBYSS      (HOENN_FLAGS_E_HOENN + 0x48)
#define FLAG_HOENN_CAUGHT_RELICANTH     (HOENN_FLAGS_E_HOENN + 0x49)
#define FLAG_HOENN_TRENCH_GUARDIAN_MET  (HOENN_FLAGS_E_HOENN + 0x4A) // battled a guardian once
#define FLAG_HOENN_TRENCH_DOOR_OPEN     (HOENN_FLAGS_E_HOENN + 0x4B) // all three caught
#define FLAG_HOENN_ITEM_DEEP_SEA_TOOTH  (HOENN_FLAGS_E_HOENN + 0x4C) // item ball in the hollow
#define FLAG_HOENN_ITEM_DEEP_SEA_SCALE  (HOENN_FLAGS_E_HOENN + 0x4D) // item ball in the hollow
#define FLAG_HOENN_CALL_TRENCH_DOOR     (HOENN_FLAGS_E_HOENN + 0x4E) // May
#define FLAG_HOENN_DAILY_TRENCH_GUARDIAN (HOENN_DAILY_FLAGS_START + 0x10) // knocked out (or caught) today
#define FLAG_HOENN_WEEKLY_PEARL_1       (HOENN_WEEKLY_FLAGS_START + 0x06) // Big Pearl
#define FLAG_HOENN_WEEKLY_PEARL_2       (HOENN_WEEKLY_FLAGS_START + 0x07) // Big Pearl
#define FLAG_HOENN_WEEKLY_PEARL_3       (HOENN_WEEKLY_FLAGS_START + 0x08) // Pearl String


// ---- Part 26a: Ice chamber A (data/scripts/hoenn_hidden.inc) ----
// Shoal Cave's ice room, low tide: a ladder hole in the ice (16,21) leads down
// into ShoalCave_IceChamber_hoenn. At high tide sea ice plugs the hole (the
// tide is Emerald's FLAG_SYS_SHOAL_TIDE, set when you walk in from Route 125).
// The chamber's hall is a sliding-ice puzzle; through the one gap in its ice
// wall (10,13) lies the inner chamber, where a GLALIE waits by day (any time
// but night): scaled, perfect IVs, Head Smash. Run and it stays; knock it out
// and it's back tomorrow; caught, it's gone for good. Part 26b brings the
// night (Froslass) and Articuno's feather.
#define FLAG_HOENN_ICE_CHAMBER_FOUND    (HOENN_FLAGS_E_HOENN + 0x4F) // climbed down into the chamber once
#define FLAG_HOENN_HIDE_ICE_GLALIE      (HOENN_FLAGS_E_HOENN + 0x50) // decided on every arrival
#define FLAG_HOENN_CAUGHT_ICE_GLALIE    (HOENN_FLAGS_E_HOENN + 0x51)
#define FLAG_HOENN_ICE_GLALIE_MET       (HOENN_FLAGS_E_HOENN + 0x52) // battled once (call)
#define FLAG_HOENN_CALL_ICE_GLALIE      (HOENN_FLAGS_E_HOENN + 0x53) // Brendan
#define FLAG_HOENN_DAILY_ICE_GLALIE     (HOENN_DAILY_FLAGS_START + 0x11) // knocked out (or caught) today

// ---- Part 26b: Ice chamber B (data/scripts/hoenn_hidden.inc) ----
// The chamber at night: a FROSLASS's reflection shows in one of its ice
// pillars (the ice rocks). Touch that pillar and she slips into the next one,
// across the hall and into the inner chamber; touch any other pillar while she
// is in the ice and a gust blows you back up to the ladder (the chase starts
// over). At the fifth pillar she steps out: scaled, perfect IVs, Spirit
// Shackle. Run and she stays; knocked out, she's back tomorrow night; caught,
// gone. After her first battle the pillar she left gives up ARTICUNO's
// FROST FEATHER. Bonuses: a DAWN STONE behind the inner chamber's outcrop and
// a NEVERMELTICE frozen into the hall's north-west wall (hidden).
#define FLAG_HOENN_HIDE_ICE_FROSLASS    (HOENN_FLAGS_E_HOENN + 0x54) // decided on every arrival
#define FLAG_HOENN_CAUGHT_ICE_FROSLASS  (HOENN_FLAGS_E_HOENN + 0x55)
#define FLAG_HOENN_ICE_FROSLASS_MET     (HOENN_FLAGS_E_HOENN + 0x56) // she stepped out of the last pillar once
#define FLAG_HOENN_GOT_FROST_FEATHER    (HOENN_FLAGS_E_HOENN + 0x57)
#define FLAG_HOENN_ITEM_ICE_DAWN_STONE  (HOENN_FLAGS_E_HOENN + 0x58) // item ball behind the outcrop
#define FLAG_HOENN_CALL_FROST_FEATHER   (HOENN_FLAGS_E_HOENN + 0x59) // May
#define FLAG_HOENN_DAILY_ICE_FROSLASS   (HOENN_DAILY_FLAGS_START + 0x12) // knocked out (or caught) today
#define FLAG_HOENN_HIDDEN_ICE_NEVERMELTICE (HOENN_EVENT_HIDDEN_ITEMS_START + 0x03)
// The chase's stage lives in VAR_TEMP_4 (0 = no chase, 1-5 = the pillar she's
// in, 6 = she stepped out), so leaving the map starts it over.

// ==== Two builder lanes (since Nov 27) =====================================
// Two builders now add parts in parallel (hoenn-docs/lanes/README.md), so the
// rest of phases E and F is split into one range per lane inside the blocks
// above. A lane defines its flags and vars ONLY from its own ranges, in its own
// section below (lane A's directly under its header, lane B's at the end of
// the file), so the two never edit the same lines. src/hoenn_flags.c checks at
// build time that the ranges sit inside their blocks and don't overlap.
// Out of room? Take flags from HOENN_FLAGS_SPARE (vars: HOENN_VARS_SPARE) and
// write the claim in your lane file. 27a was started before the split and
// uses lane A's ranges from their start.

// ---- Lane A: parts 27a-28, 31a, 32, 34b, 35b, 37 (hoenn-docs/lanes/lane-a.md) ----
#define HOENN_LANE_A_FLAGS_E        (HOENN_FLAGS_E_JOHTO_KANTO + 0x00)     // 0x21A0, 48 flags
#define HOENN_LANE_A_FLAGS_E_COUNT  0x30
#define HOENN_LANE_A_FLAGS_F        (HOENN_FLAGS_F_LEGENDARIES + 0x00)     // 0x2200, 64 flags
#define HOENN_LANE_A_FLAGS_F_COUNT  0x40
#define HOENN_LANE_A_DAILY          (HOENN_DAILY_FLAGS_START + 0x13)       // 21 daily flags
#define HOENN_LANE_A_DAILY_COUNT    21
#define HOENN_LANE_A_WEEKLY         (HOENN_WEEKLY_FLAGS_START + 0x09)      // 26 weekly flags
#define HOENN_LANE_A_WEEKLY_COUNT   26
#define HOENN_LANE_A_HIDDEN         (HOENN_EVENT_HIDDEN_ITEMS_START + 0x04) // 28 hidden-item flags
#define HOENN_LANE_A_HIDDEN_COUNT   28
#define HOENN_LANE_A_VARS_E         (HOENN_VARS_E_EVENTS + 0x00)           // 20 vars
#define HOENN_LANE_A_VARS_E_COUNT   20
#define HOENN_LANE_A_VARS_F         (HOENN_VARS_F_LEGENDARIES + 0x00)      // 12 vars
#define HOENN_LANE_A_VARS_F_COUNT   12
// Lane A's part sections go here, each "// ---- Part NN: ... ----" like the
// ones above, numbered from its range's start:
//     #define FLAG_HOENN_X   (HOENN_LANE_A_FLAGS_E + 0x00)

// ---- Part 27a: Unown Cipher A (lane A, built before the split) (data/scripts/hoenn_cipher.inc, src/hoenn_cipher.c) ----
// Once all four Ruins of Alph panels are solved and you've been to Hoenn, a
// Rosetta line shows in Words Room 1: Unown letters under Hoenn braille cells
// (AT NIGHT WE SPEAK). Reading the braille teaches you the Unown letters. From
// then on, at night, Words Rooms 2-4 show a glowing word that changes by
// weekday; the lab researcher keeps count. Brendan's call sends you to the lab.
#define FLAG_HOENN_CIPHER_ASKED         (HOENN_LANE_A_FLAGS_E + 0x00) // the lab researcher asked for help
#define FLAG_HOENN_CIPHER_ROSETTA       (HOENN_LANE_A_FLAGS_E + 0x01) // read the braille: you can read Unown
#define FLAG_HOENN_CIPHER_WORD_SUN      (HOENN_LANE_A_FLAGS_E + 0x02) // + HOENN_SUNDAY..HOENN_SATURDAY (0x02-0x08):
                                                                           // that weekday's night word was seen
#define FLAG_HOENN_CIPHER_ALL_WORDS     (HOENN_LANE_A_FLAGS_E + 0x09) // the lab heard all seven (part 27b starts here)
#define FLAG_HOENN_CALL_CIPHER          (HOENN_LANE_A_FLAGS_E + 0x0A) // Brendan: the lab phoned Birch
// Words Rooms 2-4 use VAR_TEMP_1 for the night word's first-sight message.
// specialvar VAR_RESULT, HoennCipherTonightWord answers:
#define HOENN_CIPHER_NO_WORD   0 // no word shows now (not night, or the Rosetta isn't read)
#define HOENN_CIPHER_NEW_WORD  1 // tonight's word, not noted yet
#define HOENN_CIPHER_SEEN_WORD 2 // tonight's word, already noted

// ---- Part 27b: Unown Cipher B, the glyph sites (data/scripts/hoenn_lane_a.inc, src/hoenn_lane_a.c) ----
// Each night word names a place. Once you've seen a weekday's word, its place
// shows a ring of Unown at night spelling the word, in a quiet corner. Talk to
// the ring: one letter comes out to battle, and once it's caught or knocked
// out the ring is gone and a TABLET FRAGMENT carved with that letter lies on
// the floor. The seven letters spell ANCIENT (part 28 reads the tablet).
#define FLAG_HOENN_CIPHER_FRAGMENT_SUN  (HOENN_LANE_A_FLAGS_E + 0x0B) // + HOENN_SUNDAY..HOENN_SATURDAY (0x0B-0x11):
                                                                       // that place's fragment was found
#define FLAG_HOENN_CIPHER_HIDE_RING     (HOENN_LANE_A_FLAGS_E + 0x12) // the ring objects' flag (every site map decides it on arrival)
#define FLAG_HOENN_CIPHER_SHOWED_LAB    (HOENN_LANE_A_FLAGS_E + 0x13) // the lab researcher has seen a fragment
#define FLAG_HOENN_CALL_CIPHER_FRAGMENT (HOENN_LANE_A_FLAGS_E + 0x14) // May: the lab phoned Birch about the fragment
#define FLAG_HOENN_CIPHER_TABLET        (HOENN_LANE_A_FLAGS_E + 0x15) // the lab put all seven together (part 28 starts here)

// ---- Part 31a: the Sneasel thief (data/scripts/hoenn_lane_a.inc) ----
// Ice Path B2F at night, once all four B1F boulders have dropped onto it: an
// item ball on the ice is snatched by a Sneasel as you reach it, then another
// shows farther across the ice, three times; then it's cornered in the
// north-west nook. Its stash comes with the first battle.
#define FLAG_HOENN_HIDE_SNEASEL_BALL_1  (HOENN_LANE_A_FLAGS_E + 0x20) // the three snatched balls' object flags
#define FLAG_HOENN_HIDE_SNEASEL_BALL_2  (HOENN_LANE_A_FLAGS_E + 0x21) //   (decided on every arrival)
#define FLAG_HOENN_HIDE_SNEASEL_BALL_3  (HOENN_LANE_A_FLAGS_E + 0x22)
#define FLAG_HOENN_HIDE_ICE_SNEASEL     (HOENN_LANE_A_FLAGS_E + 0x23) // the Sneasel's object flag
#define FLAG_HOENN_SNEASEL_STASH        (HOENN_LANE_A_FLAGS_E + 0x24) // fought it once and got its stash: no more chase, it waits in the nook
#define FLAG_HOENN_CAUGHT_ICE_SNEASEL   (HOENN_LANE_A_FLAGS_E + 0x25)
#define FLAG_HOENN_CALL_SNEASEL         (HOENN_LANE_A_FLAGS_E + 0x26) // Brendan: Clair's gym report
#define FLAG_HOENN_DAILY_ICE_SNEASEL    (HOENN_LANE_A_DAILY + 0x00)   // knocked out: back next night

// ---- Lane B: parts 31b, 34a, 29, 30a, 30b, 33, 36, 35a (hoenn-docs/lanes/lane-b.md) ----
// (Kept below lane A's sections, so its additions land at the end of the file.)
#define HOENN_LANE_B_FLAGS_E        (HOENN_FLAGS_E_JOHTO_KANTO + 0x30)     // 0x21D0, 48 flags
#define HOENN_LANE_B_FLAGS_E_COUNT  0x30
#define HOENN_LANE_B_FLAGS_F        (HOENN_FLAGS_F_LEGENDARIES + 0x40)     // 0x2240, 64 flags
#define HOENN_LANE_B_FLAGS_F_COUNT  0x40
#define HOENN_LANE_B_DAILY          (HOENN_DAILY_FLAGS_START + 0x28)       // 20 daily flags
#define HOENN_LANE_B_DAILY_COUNT    20
#define HOENN_LANE_B_WEEKLY         (HOENN_WEEKLY_FLAGS_START + 0x23)      // 26 weekly flags
#define HOENN_LANE_B_WEEKLY_COUNT   26
#define HOENN_LANE_B_HIDDEN         (HOENN_EVENT_HIDDEN_ITEMS_START + 0x20) // 28 hidden-item flags
#define HOENN_LANE_B_HIDDEN_COUNT   28
#define HOENN_LANE_B_VARS_E         (HOENN_VARS_E_EVENTS + 0x14)           // 20 vars
#define HOENN_LANE_B_VARS_E_COUNT   20
#define HOENN_LANE_B_VARS_F         (HOENN_VARS_F_LEGENDARIES + 0x0C)      // 12 vars
#define HOENN_LANE_B_VARS_F_COUNT   12
// Lane B's part sections go here, at the end of the file:
//     #define FLAG_HOENN_Y   (HOENN_LANE_B_FLAGS_E + 0x00)

// ---- Part 31b: Teddiursa's honey trail (data/scripts/hoenn_lane_b.inc) ----
// A beekeeper's house at the top of Route 45 gives one HONEY a day. Spread on
// the old pine in the pond meadow, it brings two Teddiursa the next morning;
// after HOENN_HONEY_MORNINGS_NEEDED watched mornings their mother comes
// instead, and on a later night she climbs the meadow's east cliff and leads
// you to the moon hollow (Route45_MoonHollow_hoenn), one of Jirachi's three
// wishing spots (lane A's part 37 reads FLAG_HOENN_MOON_HOLLOW_FOUND).
#define FLAG_HOENN_HONEY_ON_TREE        (HOENN_LANE_B_FLAGS_E + 0x00) // HONEY is on the pine
#define FLAG_HOENN_HIDE_HONEY_TEDDI     (HOENN_LANE_B_FLAGS_E + 0x01) // object flag: the two Teddiursa at the pine
#define FLAG_HOENN_HIDE_HONEY_URSARING  (HOENN_LANE_B_FLAGS_E + 0x02) // object flag: the Ursaring at the pine
#define FLAG_HOENN_HIDE_HOLLOW_BEARS    (HOENN_LANE_B_FLAGS_E + 0x03) // object flag: the bears in the hollow
#define FLAG_HOENN_MOON_HOLLOW_FOUND    (HOENN_LANE_B_FLAGS_E + 0x04) // followed the Ursaring up (Jirachi's spot)
#define FLAG_HOENN_CALL_MOON_HOLLOW     (HOENN_LANE_B_FLAGS_E + 0x05) // Brendan's call about it
#define FLAG_HOENN_DAILY_BEEKEEPER_HONEY (HOENN_LANE_B_DAILY + 0x00)  // today's jar from the beekeeper
#define FLAG_HOENN_DAILY_HONEY_SPREAD    (HOENN_LANE_B_DAILY + 0x01)  // HONEY went on the pine today (visitors come on a later morning)
#define VAR_HOENN_HONEY_STAGE           (HOENN_LANE_B_VARS_E + 0x00)  // HOENN_HONEY_STAGE_*
#define VAR_HOENN_HONEY_MORNINGS        (HOENN_LANE_B_VARS_E + 0x01)  // honey mornings watched (stops counting at the goal)
#define HOENN_HONEY_STAGE_CUBS          0 // the Teddiursa come for the honey
#define HOENN_HONEY_STAGE_NIGHT         1 // the mother came one morning: she waits at the pine at night
#define HOENN_HONEY_STAGE_HOLLOW        2 // the hollow is found; the bears sit there at night
#define HOENN_HONEY_MORNINGS_NEEDED     3 // watched mornings before the mother comes
// The hollow uses VAR_TEMP_1 for its first-visit scene (an ON_FRAME entry).

// ---- Part 34a: the three birds (data/scripts/hoenn_lane_b.inc, src/hoenn_lane_b.c) ----
// Bill (Goldenrod) tracks Articuno, Zapdos and Moltres. Each bird has a
// feather (key item): the FROST FEATHER (part 26b, Shoal Cave), the THUNDER
// FEATHER (the Power Plant manager on Route 10's thunderstorm day) and the
// FLAME FEATHER (dropped into Route 113's ash by Moltres's flyover). Carrying a
// bird's feather to its roost (Seafoam B1F, the Power Plant's back yard, Mt.
// Silver's Moltres room) calls the bird down; it waits there until you battle
// it. Caught = gone for good; knocked out = back another day; ran = it stays.
// The flags below come in Articuno, Zapdos, Moltres order (HOENN_BIRD_*), so
// src/hoenn_lane_b.c can add the bird's index to the first one.
#define HOENN_BIRD_ARTICUNO             0
#define HOENN_BIRD_ZAPDOS               1
#define HOENN_BIRD_MOLTRES              2
#define HOENN_BIRD_COUNT                3
#define FLAG_HOENN_HIDE_ARTICUNO        (HOENN_LANE_B_FLAGS_F + 0x00) // object flags (replace HnS's FLAG_HIDE_*, which are 0)
#define FLAG_HOENN_HIDE_ZAPDOS          (HOENN_LANE_B_FLAGS_F + 0x01)
#define FLAG_HOENN_HIDE_MOLTRES         (HOENN_LANE_B_FLAGS_F + 0x02)
#define FLAG_HOENN_ARTICUNO_LANDED      (HOENN_LANE_B_FLAGS_F + 0x03) // the feather called it down: it waits at its roost
#define FLAG_HOENN_ZAPDOS_LANDED        (HOENN_LANE_B_FLAGS_F + 0x04)
#define FLAG_HOENN_MOLTRES_LANDED       (HOENN_LANE_B_FLAGS_F + 0x05)
#define FLAG_HOENN_CAUGHT_ARTICUNO      (HOENN_LANE_B_FLAGS_F + 0x06)
#define FLAG_HOENN_CAUGHT_ZAPDOS        (HOENN_LANE_B_FLAGS_F + 0x07)
#define FLAG_HOENN_CAUGHT_MOLTRES       (HOENN_LANE_B_FLAGS_F + 0x08)
#define FLAG_HOENN_GOT_THUNDER_FEATHER  (HOENN_LANE_B_FLAGS_F + 0x09)
#define FLAG_HOENN_GOT_FLAME_FEATHER    (HOENN_LANE_B_FLAGS_F + 0x0A)
#define FLAG_HOENN_MOLTRES_CAMEO        (HOENN_LANE_B_FLAGS_F + 0x0B) // saw Moltres fly over Route 113
#define FLAG_HOENN_HIDE_FLAME_FEATHER   (HOENN_LANE_B_FLAGS_F + 0x0C) // object flag: the feather in Route 113's ash
#define FLAG_HOENN_HIDE_ROUTE113_MOLTRES (HOENN_LANE_B_FLAGS_F + 0x0D) // object flag: Moltres in the flyover
#define FLAG_HOENN_BILL_BIRDS           (HOENN_LANE_B_FLAGS_F + 0x0E) // Bill told you he's tracking the birds
#define FLAG_HOENN_CALL_BIRDS           (HOENN_LANE_B_FLAGS_F + 0x0F) // May: Bill heard a bird came down
#define FLAG_HOENN_DAILY_ARTICUNO_GONE  (HOENN_LANE_B_DAILY + 0x02)   // knocked out today: back tomorrow
#define FLAG_HOENN_DAILY_ZAPDOS_GONE    (HOENN_LANE_B_DAILY + 0x03)
#define FLAG_HOENN_DAILY_MOLTRES_GONE   (HOENN_LANE_B_DAILY + 0x04)
// specialvar VAR_RESULT, HoennBirdRoostState (VAR_0x8009 = HOENN_BIRD_*):
#define HOENN_ROOST_EMPTY    0 // nothing happens (caught, gone today, or no feather)
#define HOENN_ROOST_CALL     1 // the feather can call it: arm the roost's triggers
#define HOENN_ROOST_WAITING  2 // it already landed: it's shown
// Route 113 uses VAR_TEMP_6 for the flyover's triggers; the roosts use VAR_TEMP_6 too.


// ---- Part 29: shifting tunnels (data/scripts/hoenn_lane_b.inc, src/hoenn_lane_b.c) ----
// Onix: every night a fresh hole opens in a different wall of Rock Tunnel B1F
// (one per weekday, sOnixHoles); it leads into the Onix's bore
// (RockTunnel_OnixBore_hoenn), where a shiny Onix rests in its chamber at night.
// Dunsparce: Dark Cave's south side has four burrow holes, one open in each time
// of day (sBurrowHoles). They all drop into the burrow (DarkCave_Burrow_hoenn);
// the first visit in each time of day, a Dunsparce digs one row of the rubble
// out of the passage, and after all four the chamber behind it is open, where a
// Three-Segment Dudunsparce sleeps.
// Tangela: Route 21's islet near Pallet is choked with Tangela vines that only
// relax in the morning, opening the way to a shiny Tangela.
#define FLAG_HOENN_ONIX_CAUGHT          (HOENN_LANE_B_FLAGS_E + 0x06)
#define FLAG_HOENN_HIDE_ONIX            (HOENN_LANE_B_FLAGS_E + 0x07) // object flag, decided on every arrival
#define FLAG_HOENN_ITEM_BORE_IRON_BALL  (HOENN_LANE_B_FLAGS_E + 0x08)
#define FLAG_HOENN_ITEM_BORE_STAR_PIECE (HOENN_LANE_B_FLAGS_E + 0x09)
#define FLAG_HOENN_ITEM_BORE_BIG_NUGGET (HOENN_LANE_B_FLAGS_E + 0x0A)
#define FLAG_HOENN_ONIX_FOUND           (HOENN_LANE_B_FLAGS_E + 0x0B) // reached the bore's chamber (rumor)
#define FLAG_HOENN_BURROW_DUG_MORNING   (HOENN_LANE_B_FLAGS_E + 0x0C) // + HOENN_TIME_*: that time of day's Dunsparce dug
#define FLAG_HOENN_BURROW_DUG_DAY       (HOENN_LANE_B_FLAGS_E + 0x0D)
#define FLAG_HOENN_BURROW_DUG_EVENING   (HOENN_LANE_B_FLAGS_E + 0x0E)
#define FLAG_HOENN_BURROW_DUG_NIGHT     (HOENN_LANE_B_FLAGS_E + 0x0F)
#define FLAG_HOENN_DUDUNSPARCE_CAUGHT   (HOENN_LANE_B_FLAGS_E + 0x10)
#define FLAG_HOENN_HIDE_DUDUNSPARCE     (HOENN_LANE_B_FLAGS_E + 0x11) // object flag, decided on every arrival
#define FLAG_HOENN_HIDE_BURROW_DIGGER   (HOENN_LANE_B_FLAGS_E + 0x12) // object flag, decided on every arrival
#define FLAG_HOENN_TANGELA_CAUGHT       (HOENN_LANE_B_FLAGS_E + 0x13)
#define FLAG_HOENN_HIDE_TANGELA         (HOENN_LANE_B_FLAGS_E + 0x14) // object flag: the shiny one and its vines
#define FLAG_HOENN_TANGELA_SEEN         (HOENN_LANE_B_FLAGS_E + 0x15) // pushed at the vines once (rumor)
#define FLAG_HOENN_CALL_TUNNELS         (HOENN_LANE_B_FLAGS_E + 0x16) // Brendan: the crystal Onix
#define FLAG_HOENN_DAILY_ONIX_GONE      (HOENN_LANE_B_DAILY + 0x05)   // knocked out tonight: back tomorrow night
#define FLAG_HOENN_DAILY_ONIX_RUMBLE    (HOENN_LANE_B_DAILY + 0x06)   // tonight's rumble was felt
#define FLAG_HOENN_DAILY_DUDUNSPARCE_GONE (HOENN_LANE_B_DAILY + 0x07)
#define FLAG_HOENN_DAILY_TANGELA_GONE   (HOENN_LANE_B_DAILY + 0x08)
#define FLAG_HOENN_HIDDEN_BORE_METAL_COAT  (HOENN_LANE_B_HIDDEN + 0x00) // under the Onix's resting spot
#define FLAG_HOENN_HIDDEN_ISLET_MIRACLE_SEED (HOENN_LANE_B_HIDDEN + 0x01) // where the shiny Tangela sat
#define HOENN_ONIX_NO_HOLE      7  // HoennOnixHoleTonight: no hole (it's not night)
#define HOENN_BURROW_DIGS_NEEDED 4 // one per time of day
// Rock Tunnel B1F uses VAR_TEMP_5 for the rumble, the burrow VAR_TEMP_1 for the dig,
// Route 21 VAR_TEMP_1 for the vines' morning.

// ---- Part 30a: the lost Kangaskhan baby (data/scripts/hoenn_lane_b.inc, src/hoenn_lane_b.c) ----
// Evenings in the Fuchsia Safari Zone, a Kangaskhan baby cries on the Beach's
// sand. Talk to it and it follows you like your follower Pokémon (its own
// sprite) until the Safari game ends; walk it to its mother in a hidden nook of
// the Brush (4,15) and she gives you a Lucky Egg. Afterwards the two sit there
// together. Leaving the Safari Zone with the baby sends it back to the Beach.
#define FLAG_HOENN_KANGA_BABY_FOLLOWING (HOENN_LANE_B_FLAGS_E + 0x17) // the baby walks behind you (Safari Zone only)
#define FLAG_HOENN_KANGA_REUNITED       (HOENN_LANE_B_FLAGS_E + 0x18) // brought it home: Lucky Egg given
#define FLAG_HOENN_HIDE_KANGA_BABY      (HOENN_LANE_B_FLAGS_E + 0x19) // object flag: the baby on the Beach, decided on every arrival
#define FLAG_HOENN_HIDE_KANGA_PAIR_BABY (HOENN_LANE_B_FLAGS_E + 0x1A) // object flag: the baby beside its mother in the Brush
#define FLAG_HOENN_CALL_KANGASKHAN      (HOENN_LANE_B_FLAGS_E + 0x1B) // May: the warden told Birch's aide
#define FLAG_HOENN_KANGA_EGG_GIVEN      (HOENN_LANE_B_FLAGS_E + 0x1C) // the mother's LUCKY EGG (later, if the bag was full)
// The Beach and the Brush use VAR_TEMP_1 for the baby's scenes.
#endif // GUARD_CONSTANTS_HOENN_EVENTS_H
