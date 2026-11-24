// Hoenn & Seek (part 9): trainer card stamps and gym level scaling.
//
// Hoenn gyms can be done in any order, so their teams scale with how many
// stamps the player already has. The leader's strongest Pokémon is set to
// HOENN_GYM_ACE_MIN at 0 stamps and HOENN_GYM_ACE_MAX at 7 (the eighth gym);
// the rest of the team keeps Emerald's level gaps below it. Gym trainers
// top out HOENN_GYM_TRAINER_GAP levels below the leader.
#include "global.h"
#include "data.h"
#include "event_data.h"
#include "hoenn.h"
#include "constants/opponents.h"

#if IS_HNS

#include "data/hoenn_gym_trainers.h"

#define HOENN_GYM_ACE_MIN       68
#define HOENN_GYM_ACE_MAX       78
#define HOENN_GYM_TRAINER_GAP   4

enum { GYM_ROLE_NONE, GYM_ROLE_TRAINER, GYM_ROLE_LEADER };

u32 HoennCountStamps(void)
{
    u32 i, count = 0;

    for (i = 0; i < HOENN_GYM_COUNT; i++)
        if (FlagGet(FLAG_HOENN_STAMP_GYM_1 + i))
            count++;
    return count;
}

u32 HoennGymAceLevel(void)
{
    u32 stamps = HoennCountStamps();

    if (stamps > HOENN_GYM_COUNT - 1)
        stamps = HOENN_GYM_COUNT - 1;
    return HOENN_GYM_ACE_MIN + (stamps * (HOENN_GYM_ACE_MAX - HOENN_GYM_ACE_MIN) + (HOENN_GYM_COUNT - 1) / 2) / (HOENN_GYM_COUNT - 1);
}

static u32 GetGymRole(const struct Trainer *trainer)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sHoennGymLeaders); i++)
        if (GetTrainerStructFromId(sHoennGymLeaders[i]) == trainer)
            return GYM_ROLE_LEADER;
    for (i = 0; i < ARRAY_COUNT(sHoennGymTrainers); i++)
        if (GetTrainerStructFromId(sHoennGymTrainers[i]) == trainer)
            return GYM_ROLE_TRAINER;
    return GYM_ROLE_NONE;
}

u8 HoennScaleTrainerMonLevel(const struct Trainer *trainer, u8 level)
{
    u32 role, i, count, maxLevel = 0;
    s32 ace, scaled;

    role = GetGymRole(trainer);
    if (role == GYM_ROLE_NONE)
        return level;

    count = trainer->poolSize ? trainer->poolSize : trainer->partySize;
    for (i = 0; i < count; i++)
        if (trainer->party[i].lvl > maxLevel)
            maxLevel = trainer->party[i].lvl;

    ace = HoennGymAceLevel();
    if (role == GYM_ROLE_TRAINER)
        ace -= HOENN_GYM_TRAINER_GAP;
    scaled = ace - (s32)(maxLevel - level);
    if (scaled < 1)
        scaled = 1;
    if (scaled > MAX_LEVEL)
        scaled = MAX_LEVEL;
    return scaled;
}

#endif // IS_HNS

#if IS_HNS
#include "script_pokemon_util.h"

#define HOENN_SCALED_WILD_GAP   8

// Special: set up a scripted wild battle against VAR_0x8004's species at the
// stamp curve minus HOENN_SCALED_WILD_GAP (Lv 60 -> 70). Used for the Route 120
// bridge Kecleon (part 11).
void HoennSetupScaledWildBattle(void)
{
    CreateScriptedWildMon(VarGet(VAR_0x8004), HoennGymAceLevel() - HOENN_SCALED_WILD_GAP, ITEM_NONE);
}
#endif
