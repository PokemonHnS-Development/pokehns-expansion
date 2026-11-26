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

// The day a new week starts on (weekly flags reset when it begins).
// Sunday, like the PokéGear calendar and the WEEKDAY_* order.
#define HOENN_WEEK_STARTS_ON      HOENN_SUNDAY

// Weather cycles are 4 days long (Emerald's weatherCycleStage, 0-3). Part 5
// gives each cycle route an offset; a route's "special weather" day is the one
// where (stage + offset) % 4 == HOENN_SPECIAL_WEATHER_STAGE. Stage 2 is Route
// 119's thunderstorm day in Emerald's own cycle, so offset 0 matches it.
#define HOENN_SPECIAL_WEATHER_STAGE 2

#endif // GUARD_CONSTANTS_HOENN_EVENTS_H
