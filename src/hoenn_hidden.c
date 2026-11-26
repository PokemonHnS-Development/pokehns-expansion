// Hoenn & Seek 2.0 (parts 20+): hidden events, Hoenn (plan section 7). The scenes
// are scripts (data/scripts/hoenn_hidden.inc); this file holds what scripts
// can't do on their own.
//
// - special HoennTuneWildMon: every event Pokémon has something special (plan
//   section 9): a move it can't normally learn, perfect IVs or a held item. Run it
//   after HoennSetupScaledWildBattle (which creates gEnemyParty[0]) and before
//   dowildbattle.
// - special HoennTuneWildMonSlot / HoennSetupScaledWildDouble: the same for
//   wild doubles and female or hidden-ability Pokémon (part 21).
// - specialvar VAR_RESULT, HoennOrchardBerry: the orchard tree's daily berry.
// - HoennHiddenDueCall(): the PokéGear event calls these events add. It runs from
//   HoennSpeciesDueCall() (src/hoenn_species.c), after the species calls.
#include "global.h"
#include "event_data.h"
#include "move.h"
#include "ow_synchronize.h"
#include "pokemon.h"
#include "random.h"
#include "script_pokemon_util.h"
#include "hoenn.h"

#if IS_HNS
#include "constants/hoenn_custom.h"
#include "constants/hoenn_events.h"
#include "constants/hoenn_phone.h"

// Tunes one wild Pokémon in gEnemyParty (HoennTuneWildMon: slot 0, no extras).
//   VAR_0x8005 = a move to teach (MOVE_NONE: none). It replaces the last move,
//                unless the Pokémon already knows it or has an empty slot.
//   VAR_0x8006 = TRUE: all six IVs become 31; HOENN_TUNE_IV_HP (2): only HP's
//                (part 22b's Wailord).
//   VAR_0x8007 = held item (ITEM_NONE: keep whatever it rolled).
// HoennTuneWildMonSlot also reads:
//   VAR_0x8008 = the party slot (1 = the second Pokémon of a wild double).
//   VAR_0x8009 = HOENN_TUNE_* bits: FEMALE re-rolls the Pokémon as a female
//                (same species and level; done first, so it keeps the rest),
//                HIDDEN_ABILITY gives it its hidden ability, SHINY makes it
//                shiny (part 23's Altaria).
static void TuneWildMon(u32 slot, u32 extras)
{
    struct Pokemon *mon = &gEnemyParty[slot];
    u16 move = VarGet(VAR_0x8005);
    u16 item = VarGet(VAR_0x8007);
    u32 i;

    if (extras & HOENN_TUNE_FEMALE)
    {
        u16 species = GetMonData(mon, MON_DATA_SPECIES);
        u8 level = GetMonData(mon, MON_DATA_LEVEL);
        u32 personality = GetMonPersonality(species, MON_FEMALE,
            GetSynchronizedNature(STATIC_WILDMON_ORIGIN, species), RANDOM_UNOWN_LETTER);
        CreateMonWithIVs(mon, species, level, personality, OTID_STRUCT_PLAYER_ID, USE_RANDOM_IVS);
        GiveMonInitialMoveset(mon);
    }
    if (extras & HOENN_TUNE_HIDDEN_ABILITY)
    {
        u8 abilityNum = 2;
        SetMonData(mon, MON_DATA_ABILITY_NUM, &abilityNum);
    }
    if (extras & HOENN_TUNE_SHINY)
    {
        bool32 isShiny = TRUE;
        SetMonData(mon, MON_DATA_IS_SHINY, &isShiny);
    }
    if (move != MOVE_NONE)
    {
        bool32 known = FALSE;
        u32 moveSlot = MAX_MON_MOVES - 1;
        for (i = MAX_MON_MOVES; i-- > 0;)
        {
            u16 cur = GetMonData(mon, MON_DATA_MOVE1 + i);
            if (cur == move)
                known = TRUE;
            else if (cur == MOVE_NONE)
                moveSlot = i; // ends on the first empty slot
        }
        if (!known)
        {
            u8 pp = GetMovePP(move);
            SetMonData(mon, MON_DATA_MOVE1 + moveSlot, &move);
            SetMonData(mon, MON_DATA_PP1 + moveSlot, &pp);
        }
    }
    if (VarGet(VAR_0x8006))
    {
        u8 iv = MAX_PER_STAT_IVS;
        u32 stats = VarGet(VAR_0x8006) == HOENN_TUNE_IV_HP ? 1 : NUM_STATS;
        for (i = 0; i < stats; i++)
            SetMonData(mon, MON_DATA_HP_IV + i, &iv);
        CalculateMonStats(mon);
    }
    if (item != ITEM_NONE)
        SetMonData(mon, MON_DATA_HELD_ITEM, &item);
}

void HoennTuneWildMon(void)
{
    TuneWildMon(0, 0);
}

void HoennTuneWildMonSlot(void)
{
    TuneWildMon(VarGet(VAR_0x8008) ? 1 : 0, VarGet(VAR_0x8009));
}

// A wild double at the scaled level (like HoennSetupScaledWildBattle):
// VAR_0x8004 and VAR_0x8005 are the two species. The script must run
// `setwildbattle A, 1, ITEM_NONE, B, 1, ITEM_NONE` first: that's what makes
// dowildbattle start a double (scrcmd.c keeps that choice in a static), and
// a single `setwildbattle` afterwards puts it back.
void HoennSetupScaledWildDouble(void)
{
    u8 level = HoennGymAceLevel() - HOENN_SCALED_WILD_GAP;
    CreateScriptedDoubleWildMon(VarGet(VAR_0x8004), level, ITEM_NONE, VarGet(VAR_0x8005), level, ITEM_NONE);
}

// The orchard's fruit tree (part 21): one berry a day, put in VAR_RESULT.
// With the orchard's Tropius leading your party it only drops the rare ones.
static const u16 sOrchardBerries[] = {
    ITEM_LUM_BERRY, ITEM_SITRUS_BERRY, // common: 2 of 3 drops without Tropius
    ITEM_LIECHI_BERRY, ITEM_GANLON_BERRY, ITEM_SALAC_BERRY, ITEM_PETAYA_BERRY,
    ITEM_APICOT_BERRY, ITEM_LANSAT_BERRY, ITEM_STARF_BERRY,
};
#define ORCHARD_COMMON 2

u16 HoennOrchardBerry(void)
{
    u32 rare = ARRAY_COUNT(sOrchardBerries) - ORCHARD_COMMON;
    u32 lead;
    for (lead = 0; lead < PARTY_SIZE; lead++)
        if (GetMonData(&gPlayerParty[lead], MON_DATA_SPECIES) != SPECIES_NONE
         && !GetMonData(&gPlayerParty[lead], MON_DATA_IS_EGG))
            break;
    if (lead < PARTY_SIZE && GetMonData(&gPlayerParty[lead], MON_DATA_SPECIES) == SPECIES_TROPIUS)
        return sOrchardBerries[ORCHARD_COMMON + Random() % rare];
    if (Random() % 3 != 0)
        return sOrchardBerries[Random() % ORCHARD_COMMON];
    return sOrchardBerries[ORCHARD_COMMON + Random() % rare];
}

// Part 20's calls. Each caller says how they heard:
//  - Brendan, the Munchlax: the glassblower on Route 113 makes glassware for
//    Birch's lab, and he told Birch who he made the GLASS FLUTE for.
//  - May, the Slaking: Petalburg Woods was her dad Norman's old training spot,
//    and he still hears about everything that goes on there.
// Part 21's:
//  - Brendan, the Tropius: the Weather Institute on Route 119 spotted it from
//    their roof and told Birch.
//  - May, the Feebas: the contest crowd in Lilycove talks about nothing else
//    (Feebas becomes Milotic, the contest star).
//  - Brendan, Zangoose vs. Seviper: Magma's researchers by Meteor Falls watch
//    the fight every Sunday and told Birch (they measure volcanoes together).
//  - May, Absol (part 22a): WINONA flew home through the storm and saw it from
//    the air; she told Norman, who hears every gym leader's news.
// Part 22b's:
//  - Brendan, the Wailord: Capt. Stern's crew charts the sea near Pacifidlog and
//    saw it go under from their boat; they told Birch, who funds their surveys.
//  - May, the Chimecho: her mom tends a grave on Mt. Pyre and heard the chimes
//    the same night.
// Part 23's:
//  - May, the chorus: Winona keeps Altaria and hears about every flock in Hoenn;
//    she told Norman at the League, who told May.
//  - Brendan, the Bagon: Magma's researchers survey Meteor Falls with Birch and
//    saw it leap at you.
//  - Brendan, the Metagross: Cozmo was charting the meteorite fragments' glow in
//    Steven's cave that night and told Birch.
// Part 24a's:
//  - Brendan, the Singing Sand: the Fossil Maniac sends Birch every fossil he
//    digs up; he heard the Vibrava humming in the Desert Underpass, then a
//    battle, and phoned Birch about it.
u16 HoennHiddenDueCall(void)
{
    if (FlagGet(FLAG_HOENN_MUNCHLAX_DONE) && !FlagGet(FLAG_HOENN_CALL_MUNCHLAX))
        return HOENN_CALL_MUNCHLAX;
    if (FlagGet(FLAG_HOENN_SLAKING_DONE) && !FlagGet(FLAG_HOENN_CALL_SLAKING))
        return HOENN_CALL_SLAKING;
    if (FlagGet(FLAG_HOENN_TROPIUS_MET) && !FlagGet(FLAG_HOENN_CALL_TROPIUS))
        return HOENN_CALL_TROPIUS;
    if (FlagGet(FLAG_HOENN_FEEBAS_PRISM_GIVEN) && !FlagGet(FLAG_HOENN_CALL_FEEBAS))
        return HOENN_CALL_FEEBAS;
    if (FlagGet(FLAG_HOENN_FEUD_MET) && !FlagGet(FLAG_HOENN_CALL_FEUD))
        return HOENN_CALL_FEUD;
    if (FlagGet(FLAG_HOENN_ABSOL_WOKEN) && !FlagGet(FLAG_HOENN_CALL_ABSOL))
        return HOENN_CALL_ABSOL;
    if (FlagGet(FLAG_HOENN_WAILORD_MOVED) && !FlagGet(FLAG_HOENN_CALL_WAILORD))
        return HOENN_CALL_WAILORD;
    if (FlagGet(FLAG_HOENN_CHIMECHO_MET) && !FlagGet(FLAG_HOENN_CALL_CHIMECHO))
        return HOENN_CALL_CHIMECHO;
    if (FlagGet(FLAG_HOENN_CHORUS_WATCHED) && !FlagGet(FLAG_HOENN_CALL_CHORUS))
        return HOENN_CALL_CHORUS;
    if (FlagGet(FLAG_HOENN_BAGON_MET) && !FlagGet(FLAG_HOENN_CALL_BAGON))
        return HOENN_CALL_BAGON;
    if (FlagGet(FLAG_HOENN_METAGROSS_SEEN) && !FlagGet(FLAG_HOENN_CALL_METAGROSS))
        return HOENN_CALL_METAGROSS;
    if (FlagGet(FLAG_HOENN_GOT_SINGING_SAND) && !FlagGet(FLAG_HOENN_CALL_SINGING_SAND))
        return HOENN_CALL_SINGING_SAND;
    return HOENN_CALL_NONE;
}

#endif // IS_HNS
