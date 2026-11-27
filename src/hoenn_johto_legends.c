// Hoenn & Seek 2.0 part 35b (lane A): Ho-Oh, Raikou and Entei, Celebi.
//
// HnS already has all four: Raikou and Entei roam Johto, Ho-Oh waits on the
// Tin Tower roof once VAR_COMPLETED_HO_OH is 4 (after the Hall of Fame, or the
// Pewter grandpa's Rainbow Wing), and the GS BALL calls Celebi at the Ilex
// Forest shrine (VAR_AZALEA_TOWN_STATE 9). Part 35b keeps every story moment
// and makes the last step, from "it's there" to "you can battle it", longer
// (plan section 4: sighting, three clues, a key, the encounter):
//
// - Raikou / Entei: HoennJohtoBeastBattleEnded() (called from the roamer
//   battle hook in src/hoenn_roamer.c) notes each beast you've met and caught.
//   Once one is caught, EUSINE (Celadon Pokémon Center) sends his tracking
//   notes to OAK's POKéMON TALK, and the show's intro says where the other one
//   is right now (HoennRadioEusineReport, hooked into src/pokenav_radio.c).
// - Ho-Oh: on the roof only at dawn (TIME_MORNING), once the Ruins of Alph
//   Ho-Oh panel is solved, all three beasts have met you (Raikou and Entei in
//   battle, Suicune at the end of its chase) and the CLEAR BELL is in the bag
//   (HoennHoOhClue). The Tin Tower 1F sage names the first missing clue, and
//   gives the CLEAR BELL to a Lugia-route player who shows the Rainbow Wing.
//   The first dawn everything is ready, a rainbow crosses Ecruteak (cameo).
// - Celebi: the shrine takes the GS BALL only once three forest offerings are
//   in its dishes. Plant a berry in the old soil at Ilex Forest, Viridian
//   Forest and Petalburg Woods; the next day (a daily flag has reset) each has
//   grown, and you take its glowing berry (HoennForestSoilState and friends).
//
// Scripts and texts: data/scripts/hoenn_johto_legends.inc.
#include "global.h"
#include "event_data.h"
#include "hoenn.h"

#if IS_HNS
#include "battle.h"
#include "item.h"
#include "overworld.h"
#include "pokedex.h"
#include "pokemon.h"
#include "region_map.h"
#include "roamer.h"
#include "rtc.h"
#include "string_util.h"
#include "constants/battle.h"
#include "constants/characters.h"
#include "constants/hoenn_events.h"
#include "constants/items.h"
#include "constants/species.h"

// ------------------------------------------------------------------ beasts

void HoennJohtoBeastBattleEnded(u32 roamerIndex)
{
    u16 species = gSaveBlock1Ptr->roamer[roamerIndex].species;
    bool32 caught = (gBattleOutcome == B_OUTCOME_CAUGHT);

    if (species == SPECIES_RAIKOU)
    {
        FlagSet(FLAG_HOENN_MET_RAIKOU);
        if (caught)
            FlagSet(FLAG_HOENN_CAUGHT_RAIKOU);
    }
    else if (species == SPECIES_ENTEI)
    {
        FlagSet(FLAG_HOENN_MET_ENTEI);
        if (caught)
            FlagSet(FLAG_HOENN_CAUGHT_ENTEI);
    }
}

// The roaming beast Eusine tracks: the one you haven't caught, if it's out
// there (active, with HP left). SPECIES_NONE if there's nothing to report.
static u16 TrackedBeast(u32 *slot)
{
    u16 species;
    u32 i;

    if (FlagGet(FLAG_HOENN_CAUGHT_RAIKOU) == FlagGet(FLAG_HOENN_CAUGHT_ENTEI))
        return SPECIES_NONE; // neither caught yet (no trail to read), or both
    species = FlagGet(FLAG_HOENN_CAUGHT_RAIKOU) ? SPECIES_ENTEI : SPECIES_RAIKOU;
    for (i = 0; i < ROAMER_COUNT; i++)
    {
        struct Roamer *roamer = &gSaveBlock1Ptr->roamer[i];
        if (roamer->active && roamer->species == species && roamer->hp != 0)
        {
            *slot = i;
            return species;
        }
    }
    return SPECIES_NONE;
}

// specialvar: what EUSINE says. 0 = no beast caught yet, 1 = one caught and
// the other still out there (he gives his notes), 2 = nothing left to track.
u16 HoennEusineState(void)
{
    u32 slot;

    if (!FlagGet(FLAG_HOENN_CAUGHT_RAIKOU) && !FlagGet(FLAG_HOENN_CAUGHT_ENTEI))
        return 0;
    if (TrackedBeast(&slot) != SPECIES_NONE)
    {
        StringCopy(gStringVar1, GetSpeciesName(gSaveBlock1Ptr->roamer[slot].species));
        return 1;
    }
    return 2;
}

static const u8 sText_RadioEusine[] = _("MARY: A tip from EUSINE!");
static const u8 sText_RadioWasTracked[] = _("was tracked near ");

// Hook in the intro of OAK's POKéMON TALK (src/pokenav_radio.c). Writes up to
// three lines (one static, two into line1/line2, each a 40-byte buffer) and
// returns how many.
u32 HoennRadioEusineReport(const u8 **lines, u8 *line1, u8 *line2)
{
    u8 mapGroup, mapNum;
    u32 slot;
    u16 species;
    u8 *end;

    if (!FlagGet(FLAG_HOENN_EUSINE_NOTES))
        return 0;
    species = TrackedBeast(&slot);
    if (species == SPECIES_NONE)
        return 0;
    GetRoamerLocation(slot, &mapGroup, &mapNum);
    if (mapGroup == 0 && mapNum == 0)
        return 0; // not placed since the game was loaded: it moves on the next map change

    // "ENTEI's trail" / "was tracked near ROUTE 37."
    end = StringCopy(line1, GetSpeciesName(species));
    StringCopy(end, COMPOUND_STRING("'s fresh trail"));
    end = StringCopy(line2, sText_RadioWasTracked);
    end = GetMapName(end, Overworld_GetMapHeaderByGroupAndId(mapGroup, mapNum)->regionMapSectionId, 0);
    *end++ = CHAR_PERIOD;
    *end = EOS;
    lines[0] = sText_RadioEusine;
    lines[1] = line1;
    lines[2] = line2;
    return 3;
}

// ------------------------------------------------------------------ Ho-Oh

// specialvar: the first clue still missing for Ho-Oh (HOENN_HOOH_*), checked
// in the order the Tin Tower sage gives them. HOENN_HOOH_READY when all hold.
u16 HoennHoOhClue(void)
{
    if (!CheckBagHasItem(ITEM_CLEAR_BELL, 1))
        return HOENN_HOOH_NEEDS_BELL;
    if (!FlagGet(FLAG_COMPLETED_HOOH_PUZZLE))
        return HOENN_HOOH_NEEDS_PUZZLE;
    if (!FlagGet(FLAG_HOENN_MET_RAIKOU) || !FlagGet(FLAG_HOENN_MET_ENTEI)
     || VarGet(VAR_SUICUNE_ENCOUNTERS) < 8)
        return HOENN_HOOH_NEEDS_BEASTS;
    if (GetTimeOfDay() != TIME_MORNING)
        return HOENN_HOOH_NEEDS_DAWN;
    return HOENN_HOOH_READY;
}

// ------------------------------------------------------------------ Celebi

// The three soil spots: VAR_0x8004 = HOENN_SOIL_ILEX / _VIRIDIAN / _PETALBURG.
// Flag commands can't take a computed flag, so the scripts go through these.
static u32 SoilSpot(void)
{
    return gSpecialVar_0x8004 < HOENN_SOIL_COUNT ? gSpecialVar_0x8004 : 0;
}

// specialvar: HOENN_SOIL_EMPTY, _GROWING (planted today), _GROWN, _TAKEN.
u16 HoennForestSoilState(void)
{
    u32 spot = SoilSpot();

    if (FlagGet(FLAG_HOENN_FOREST_OFFERING_ILEX + spot))
        return HOENN_SOIL_TAKEN;
    if (!FlagGet(FLAG_HOENN_FOREST_PLANTED_ILEX + spot))
        return HOENN_SOIL_EMPTY;
    // Planting sets a daily flag; once the day has turned it's clear again.
    if (FlagGet(FLAG_HOENN_DAILY_SOIL_ILEX + spot))
        return HOENN_SOIL_GROWING;
    return HOENN_SOIL_GROWN;
}

void HoennForestSoilPlant(void)
{
    u32 spot = SoilSpot();

    FlagSet(FLAG_HOENN_FOREST_PLANTED_ILEX + spot);
    FlagSet(FLAG_HOENN_DAILY_SOIL_ILEX + spot);
}

void HoennForestSoilTake(void)
{
    FlagSet(FLAG_HOENN_FOREST_OFFERING_ILEX + SoilSpot());
}

// specialvar: how many of the three offerings you carry (0-3).
u16 HoennForestOfferings(void)
{
    u32 i, count = 0;

    for (i = 0; i < HOENN_SOIL_COUNT; i++)
        if (FlagGet(FLAG_HOENN_FOREST_OFFERING_ILEX + i))
            count++;
    return count;
}

#endif // IS_HNS
