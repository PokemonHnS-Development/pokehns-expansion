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
#define HOENN_SCALED_WILD_GAP 8 // scripted wild battles: gym-ace level - 8 (60-70, 77 after Wallace)
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
// Party checks (2.0 part 2)
u16 HoennLeadIsSpecies(void);
u16 HoennFindPartySpecies(void);
// PokéGear (src/hoenn_phone.c, part 16d)
bool32 HoennTryEventCall(void);
u16 HoennSpeciesDueCall(void);
u16 HoennHiddenDueCall(void);
void HoennTuneWildMon(void);
void HoennTuneWildMonSlot(void);
void HoennSetupScaledWildDouble(void);
u16 HoennOrchardBerry(void);
bool8 HoennPlayerIsRushing(void);
bool32 HoennIsCallableSpecialSlot(u32 rematchIdx);
bool32 HoennSpecialCallerAnswers(s32 rematchIdx);
const u8 *HoennPhoneCallText(u16 trainerId, bool32 *newRematchRequest);
#define HOENN_TRAINER_MON_LEVEL(trainer, level) HoennScaleTrainerMonLevel(trainer, level)
#else
#define HOENN_TRAINER_MON_LEVEL(trainer, level) (level)
#endif

#endif // GUARD_HOENN_H
