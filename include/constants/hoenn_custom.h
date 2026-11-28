#ifndef GUARD_CONSTANTS_HOENN_CUSTOM_H
#define GUARD_CONSTANTS_HOENN_CUSTOM_H

// Hoenn & Seek 1.0: hand-defined flags and vars (not generated). They live in the
// reserved tail of the Hoenn ranges in constants/hoenn_layout.h, which
// tools/hoenn/gen_hoenn_ids.py never assigns.
//
// This block is nearly full (flags 0x37-0x3F and vars 0x03-0x0F are free).
// Keep those for 1.x fixes. **New 2.0 content takes its flags and vars from
// constants/hoenn_events.h**, which has a block per build phase.
#include "constants/hoenn_layout.h"

// Trainer card stamps (part 9 adds the UI and gym hooks). Wallace's stamp is
// the Hoenn League win; it opens Mt. Silver (ReceptionGate_hns).
#define FLAG_HOENN_STAMP_GYM_1       (HOENN_CUSTOM_FLAGS_START + 0x00)
#define FLAG_HOENN_STAMP_GYM_2       (HOENN_CUSTOM_FLAGS_START + 0x01)
#define FLAG_HOENN_STAMP_GYM_3       (HOENN_CUSTOM_FLAGS_START + 0x02)
#define FLAG_HOENN_STAMP_GYM_4       (HOENN_CUSTOM_FLAGS_START + 0x03)
#define FLAG_HOENN_STAMP_GYM_5       (HOENN_CUSTOM_FLAGS_START + 0x04)
#define FLAG_HOENN_STAMP_GYM_6       (HOENN_CUSTOM_FLAGS_START + 0x05)
#define FLAG_HOENN_STAMP_GYM_7       (HOENN_CUSTOM_FLAGS_START + 0x06)
#define FLAG_HOENN_STAMP_GYM_8       (HOENN_CUSTOM_FLAGS_START + 0x07)
#define FLAG_HOENN_STAMP_WALLACE     (HOENN_CUSTOM_FLAGS_START + 0x08)

// Ferry (part 8)
#define FLAG_HOENN_SILVER_GATE_OPEN  (HOENN_CUSTOM_FLAGS_START + 0x11) // the gate guard has stepped aside
#define FLAG_HOENN_MET_MIND_READER   (HOENN_CUSTOM_FLAGS_START + 0x12) // Mossdeep guru introduced himself (part 14a)

#define FLAG_HOENN_SCOPE_BROKEN      (HOENN_CUSTOM_FLAGS_START + 0x13) // Route 120 tester's prototype broke (part 14)
// Gyms and League (part 13b)
#define FLAG_HOENN_COZMO_GAVE_METEORITE  (HOENN_CUSTOM_FLAGS_START + 0x14)
#define FLAG_HOENN_METEORITE_DELIVERED   (HOENN_CUSTOM_FLAGS_START + 0x15) // opens Tate & Liza
#define FLAG_HOENN_WINONA_BACK           (HOENN_CUSTOM_FLAGS_START + 0x16) // also hides her Route 119 object
#define FLAG_HOENN_WINONA_GYM_HIDDEN     (HOENN_CUSTOM_FLAGS_START + 0x17) // set by Fortree Gym OnTransition
// Teams Aqua/Magma, Norman's call, Brendan & May (part 16a)
#define FLAG_HOENN_AQUA_QUEST            (HOENN_CUSTOM_FLAGS_START + 0x18)
#define FLAG_HOENN_AQUA_DONE             (HOENN_CUSTOM_FLAGS_START + 0x19)
#define FLAG_HOENN_MAGMA_QUEST           (HOENN_CUSTOM_FLAGS_START + 0x1A)
#define FLAG_HOENN_TORKOAL_FOUND         (HOENN_CUSTOM_FLAGS_START + 0x1B) // also the Fiery Path Torkoal's object flag
#define FLAG_HOENN_MAGMA_REPORT          (HOENN_CUSTOM_FLAGS_START + 0x1C)
#define FLAG_HOENN_MAGMA_DONE            (HOENN_CUSTOM_FLAGS_START + 0x1D)
#define FLAG_HOENN_TEAMS_DOUBLE_WON      (HOENN_CUSTOM_FLAGS_START + 0x1E)
#define FLAG_HOENN_HIDE_SUMMIT_LEADERS   (HOENN_CUSTOM_FLAGS_START + 0x1F) // set at new game
#define FLAG_HOENN_BM_BACK_CALLED        (HOENN_CUSTOM_FLAGS_START + 0x20)
#define FLAG_HOENN_HIDE_BM_OUTSIDE       (HOENN_CUSTOM_FLAGS_START + 0x21) // set at new game
#define FLAG_HOENN_HIDE_BM_HOME          (HOENN_CUSTOM_FLAGS_START + 0x22) // set at new game
#define FLAG_HOENN_BEAT_BM               (HOENN_CUSTOM_FLAGS_START + 0x23) // opens Mt. Silver
#define FLAG_HOENN_BM_EGGS               (HOENN_CUSTOM_FLAGS_START + 0x24)
// Arrival gifts (part 16b)
#define FLAG_HOENN_RECEIVED_MUDKIP       (HOENN_CUSTOM_FLAGS_START + 0x25) // also hides Birch's aide at the Slateport harbor
#define FLAG_HOENN_HIDE_LAB_WALLY        (HOENN_CUSTOM_FLAGS_START + 0x26) // Wally leaves the lab after you talk to him
// PokéGear calls (part 16d)
#define FLAG_HOENN_BM_PHONE              (HOENN_CUSTOM_FLAGS_START + 0x27) // Birch gave you Brendan's and May's numbers
#define FLAG_HOENN_WALLY_PHONE           (HOENN_CUSTOM_FLAGS_START + 0x28) // registered after his Victory Road battle
#define FLAG_HOENN_JOHTO_STARTERS_READY  (HOENN_CUSTOM_FLAGS_START + 0x29) // unused since 2.0 part 15a (Elm no longer gives starters)
#define FLAG_HOENN_CALL_BADGE1           (HOENN_CUSTOM_FLAGS_START + 0x2A) // event calls done (src/hoenn_phone.c);
#define FLAG_HOENN_CALL_BADGE4           (HOENN_CUSTOM_FLAGS_START + 0x2B) // they also gate Brendan's and May's
#define FLAG_HOENN_CALL_BADGE8           (HOENN_CUSTOM_FLAGS_START + 0x2C) // phone lines when you call them
#define FLAG_HOENN_CALL_ELM              (HOENN_CUSTOM_FLAGS_START + 0x2D)
#define FLAG_HOENN_CALL_TEAMS            (HOENN_CUSTOM_FLAGS_START + 0x2E)
#define FLAG_HOENN_CALL_RED              (HOENN_CUSTOM_FLAGS_START + 0x2F)
// Contests and Safari (part 17)
#define FLAG_HOENN_IN_SAFARI_ZONE        (HOENN_CUSTOM_FLAGS_START + 0x30) // you entered from Route 121 (src: safari_zone.inc exit hook)
#define FLAG_HOENN_CALL_CONTEST          (HOENN_CUSTOM_FLAGS_START + 0x31) // May's call after your first contest win
#define FLAG_HOENN_LILYCOVE_CONTEST      (HOENN_CUSTOM_FLAGS_START + 0x32) // in Lilycove's contest lobby: contests return there (part 17)
#define FLAG_HOENN_MET_CONTEST_TWIN      (HOENN_CUSTOM_FLAGS_START + 0x33) // Lilycove's receptionist told you about her twin
#define FLAG_HOENN_CALL_BASE             (HOENN_CUSTOM_FLAGS_START + 0x34) // Brendan's call after your first secret base (part 18)
#define HOENN_CUSTOM_FLAGS_END       (HOENN_CUSTOM_FLAGS_START + 0x3F)

// 1.x fix (found in 2.0 part 26a): HnS defines Emerald's two Shoal Cave system
// flags as 0, so FlagSet did nothing and the cave was stuck at low tide (and the
// Shoal Salt and Shells never came back). Give them real Hoenn flags. The
// tide flag is set (high tide) by UpdateShoalTideFlag when you walk in from
// Route 125; the item flag by SetShoalItemFlag at each new day (src/clock.c).
#define FLAG_HOENN_SHOAL_TIDE        (HOENN_CUSTOM_FLAGS_START + 0x35)
#define FLAG_HOENN_SHOAL_ITEM        (HOENN_CUSTOM_FLAGS_START + 0x36)
#include "constants/global.h"
#if IS_HNS && !defined(HOENN_NO_REMAP)
#undef FLAG_SYS_SHOAL_TIDE
#define FLAG_SYS_SHOAL_TIDE          FLAG_HOENN_SHOAL_TIDE
#undef FLAG_SYS_SHOAL_ITEM
#define FLAG_SYS_SHOAL_ITEM          FLAG_HOENN_SHOAL_ITEM
#endif

// Fake fights (part 14): one "already happened" flag each, numbered by
// tools/hoenn/gen_hoenn_trainers.py. They borrow the top of the Hoenn trainer
// flag block, which real Hoenn trainers (TRAINER_FLAG_ID) never reach.
#define HOENN_FAKE_FLAGS_START       0x1F00
#define HOENN_FAKE_FLAGS_COUNT       0x100

// Vars (0x7070-0x707F)
#define VAR_HOENN_NEWS               (HOENN_CUSTOM_VARS_START + 0x00) // next HOENN TV news item (part 14)
#define VAR_HOENN_E4_STATE           (HOENN_CUSTOM_VARS_START + 0x01) // Hoenn Elite Four progress (VAR_ELITE_4_STATE is HnS's)
#define VAR_HOENN_AIDE_STATE         (HOENN_CUSTOM_VARS_START + 0x02) // 0: Birch's aide greets you at the Slateport harbor (part 16b)

#endif // GUARD_CONSTANTS_HOENN_CUSTOM_H
