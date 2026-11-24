#ifndef GUARD_CONSTANTS_HOENN_LAYOUT_H
#define GUARD_CONSTANTS_HOENN_LAYOUT_H

// Hoenn & Seek: where Hoenn's own flags/vars live (SaveBlock3) and how trainer
// flags are found. IDs are assigned by tools/hoenn/gen_hoenn_ids.py, which
// hardcodes these same numbers. Keep them in sync.
//
// Flag 0x1800-0x1BFF  Hoenn story/item/hidden-item flags (hidden-item flags
//                     come first: their offset from FLAG_HIDDEN_ITEMS_START is
//                     stored in 13 bits, so they must stay below 0x20E9)
// Flag 0x1C00-0x1FFF  Hoenn trainer "defeated" flags (trainer ID - HOENN_TRAINERS_START)
// Var  0x7000-0x707F  Hoenn vars
#define HOENN_FLAGS_START           0x1800
#define HOENN_TRAINER_FLAGS_START   0x1C00
#define HOENN_FLAGS_END             0x1FFF
#define HOENN_FLAGS_BYTES           ((HOENN_FLAGS_END - HOENN_FLAGS_START + 1) / 8)
#define HOENN_VARS_START            0x7000
#define HOENN_VARS_COUNT            0x80

#define IS_HOENN_FLAG(id) ((id) >= HOENN_FLAGS_START && (id) <= HOENN_FLAGS_END)
#define IS_HOENN_VAR(id)  ((id) >= HOENN_VARS_START && (id) < HOENN_VARS_START + HOENN_VARS_COUNT)

// The flag that records whether a trainer has been beaten.
#if IS_HNS && defined(HOENN_TRAINERS_START)
#define TRAINER_FLAG_ID(trainerId) ((u32)(trainerId) >= HOENN_TRAINERS_START && (u32)(trainerId) < TRAINERS_COUNT_HNS \
                                    ? HOENN_TRAINER_FLAGS_START + (trainerId) - HOENN_TRAINERS_START \
                                    : TRAINER_FLAGS_START + (trainerId))
#else
#define TRAINER_FLAG_ID(trainerId) (TRAINER_FLAGS_START + (trainerId))
#endif

#endif // GUARD_CONSTANTS_HOENN_LAYOUT_H
