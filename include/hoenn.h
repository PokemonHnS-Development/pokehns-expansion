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

#endif // GUARD_HOENN_H
