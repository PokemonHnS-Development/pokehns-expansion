#ifndef GUARD_HOENN_H
#define GUARD_HOENN_H

// Hoenn & Seek: runtime "is this Hoenn?" helpers for the HnS build.
#include "constants/region_map_sections.h"
#include "constants/hoenn_mapsecs.h"

#if IS_HNS
// True for the map sections of the Hoenn maps added by Hoenn & Seek.
// Unlike GetRegionForSectionId() == REGION_HOENN, this is false for HnS's own
// out-of-range sections (its Battle Frontier, Trainer Hill, event islands...).
static inline bool32 IsHoennMapSec(u32 mapSecId)
{
    static const mapsec_u16_t sShared[] = { HOENN_SHARED_MAPSECS };
    u32 i;
    if (mapSecId >= HOENN_MAPSEC_FIRST && mapSecId <= HOENN_MAPSEC_LAST)
        return TRUE;
    for (i = 0; i < ARRAY_COUNT(sShared); i++)
        if (sShared[i] == mapSecId)
            return TRUE;
    return FALSE;
}
#else
static inline bool32 IsHoennMapSec(u32 mapSecId) { (void)mapSecId; return FALSE; }
#endif

// Trainer card stamps and gym level scaling (src/hoenn_scaling.c, part 9).
#define HOENN_GYM_COUNT 8
struct Trainer;
#if IS_HNS
u32 HoennCountStamps(void);
u32 HoennGymAceLevel(void);
u8 HoennScaleTrainerMonLevel(const struct Trainer *trainer, u8 level);
void HoennSetupScaledWildBattle(void);
u16 HoennGetStampCount(void);
u16 HoennBufferFollower(void);
void HoennPushStoneList(void);
u16 HoennStoneFromIndex(void);
void HoennPushIVList(void);
u16 HoennCheckIV(void);
u16 HoennMaxIV(void);
void HoennPushAbilityList(void);
u16 HoennCountOtherAbilities(void);
void HoennBufferAbilitySlot(void);
void HoennSetAbilitySlot(void);
// PokéGear (src/hoenn_phone.c, part 16d)
bool32 HoennTryEventCall(void);
bool32 HoennIsCallableSpecialSlot(u32 rematchIdx);
bool32 HoennSpecialCallerAnswers(s32 rematchIdx);
const u8 *HoennPhoneCallText(u16 trainerId, bool32 *newRematchRequest);
#define HOENN_TRAINER_MON_LEVEL(trainer, level) HoennScaleTrainerMonLevel(trainer, level)
#else
#define HOENN_TRAINER_MON_LEVEL(trainer, level) (level)
#endif

#endif // GUARD_HOENN_H
