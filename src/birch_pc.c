#include "global.h"
#include "event_data.h"
#include "field_message_box.h"
#include "pokedex.h"
#include "strings.h"

bool16 ScriptGetPokedexInfo(void)
{
    if (gSpecialVar_0x8004 == 0) // is national dex not present?
    {
        gSpecialVar_0x8005 = GetRegionalPokedexCount(FLAG_GET_SEEN);
        gSpecialVar_0x8006 = GetRegionalPokedexCount(FLAG_GET_CAUGHT);
    }
    else
    {
        gSpecialVar_0x8005 = GetNationalPokedexCount(FLAG_GET_SEEN);
        gSpecialVar_0x8006 = GetNationalPokedexCount(FLAG_GET_CAUGHT);
    }

    return IsNationalPokedexEnabled();
}

#define BIRCH_DEX_STRINGS 21

static const u8 *const sBirchDexRatingTexts[BIRCH_DEX_STRINGS] =
{
    gBirchDexRatingText_LessThan10,
    gBirchDexRatingText_LessThan20,
    gBirchDexRatingText_LessThan30,
    gBirchDexRatingText_LessThan40,
    gBirchDexRatingText_LessThan50,
    gBirchDexRatingText_LessThan60,
    gBirchDexRatingText_LessThan70,
    gBirchDexRatingText_LessThan80,
    gBirchDexRatingText_LessThan90,
    gBirchDexRatingText_LessThan100,
    gBirchDexRatingText_LessThan110,
    gBirchDexRatingText_LessThan120,
    gBirchDexRatingText_LessThan130,
    gBirchDexRatingText_LessThan140,
    gBirchDexRatingText_LessThan150,
    gBirchDexRatingText_LessThan160,
    gBirchDexRatingText_LessThan170,
    gBirchDexRatingText_LessThan180,
    gBirchDexRatingText_LessThan190,
    gBirchDexRatingText_LessThan200,
    gBirchDexRatingText_DexCompleted,
};

#if IS_HNS

const u8 *GetPokedexRatingText(u32 count)
{
    u32 i, j, k;
    // doesNotCountForRegionalPokedex
    u16 maxDex = REGIONAL_DEX_COUNT - 1;
    for (i = 0; i < REGIONAL_DEX_COUNT - 1; i++)
    {
        j = RegionalToNationalOrder(i + 1);
        k = NationalPokedexNumToSpecies(j);
        if (gSpeciesInfo[k].dexNotRequired || (gSpeciesInfo[k].isMythical && !gSpeciesInfo[k].dexForceRequired))
        {
            if (GetSetPokedexFlag(j, FLAG_GET_CAUGHT))
                count--;
            maxDex--;
        }
    }

    if (count >= maxDex)
    {
        gSpecialVar_Result = TRUE;
        return gJohtoDexRatingText_Complete;
    }

    gSpecialVar_Result = FALSE;

    if (count < 10)
        return gJohtoDexRatingText_LessThan10;

    if (count < 20)
        return gJohtoDexRatingText_LessThan20;

    if (count < 35)
        return gJohtoDexRatingText_LessThan35;

    if (count < 50)
        return gJohtoDexRatingText_LessThan50;

    if (count < 65)
        return gJohtoDexRatingText_LessThan65;

    if (count < 80)
        return gJohtoDexRatingText_LessThan80;

    if (count < 95)
        return gJohtoDexRatingText_LessThan95;

    if (count < 110)
        return gJohtoDexRatingText_LessThan110;

    if (count < 125)
        return gJohtoDexRatingText_LessThan125;

    if (count < 140)
        return gJohtoDexRatingText_LessThan140;

    if (count < 155)
        return gJohtoDexRatingText_LessThan155;

    if (count < 170)
        return gJohtoDexRatingText_LessThan170;

    if (count < 185)
        return gJohtoDexRatingText_LessThan185;

    if (count < 200)
        return gJohtoDexRatingText_LessThan200;

    if (count < 215)
        return gJohtoDexRatingText_LessThan215;

    if (count < 230)
        return gJohtoDexRatingText_LessThan230;

    if (count < 245)
        return gJohtoDexRatingText_LessThan245;

    if (count < 260)
        return gJohtoDexRatingText_LessThan260;

    if (count < 275)
        return gJohtoDexRatingText_LessThan275;

    return gJohtoDexRatingText_LessThanMaxDex;
}

const u8 *GetNationalPokedexRatingText(u32 count)
{
    u32 i, j, k;
    // doesNotCountForObtainablePokedex
    u16 maxDex = OBTAINABLE_DEX_COUNT - 1;
    for (i = 1; i < OBTAINABLE_DEX_COUNT - 1; i++)
    {
        j = ObtainableToNationalOrder(i + 1);
        k = NationalPokedexNumToSpecies(j);
        if (gSpeciesInfo[k].dexNotRequired || (gSpeciesInfo[k].isMythical && !gSpeciesInfo[k].dexForceRequired))
        {
            if (GetSetPokedexFlag(j, FLAG_GET_CAUGHT))
                count--;
            maxDex--;
        }
    }

    if (count >= maxDex)
    {
        gSpecialVar_Result = TRUE;
        return gNationalDexRatingText_Complete;
    }

    gSpecialVar_Result = FALSE;

    if (count < 100)
        return gNationalDexRatingText_LessThan100;

    if (count < 150)
        return gNationalDexRatingText_LessThan150;

    if (count < 200)
        return gNationalDexRatingText_LessThan200;

    if (count < 250)
        return gNationalDexRatingText_LessThan250;

    if (count < 300)
        return gNationalDexRatingText_LessThan300;

    if (count < 350)
        return gNationalDexRatingText_LessThan350;

    if (count < 400)
        return gNationalDexRatingText_LessThan400;

    if (count < 435)
        return gNationalDexRatingText_LessThan435;

    if (count < 465)
        return gNationalDexRatingText_LessThan465;

    if (count < 475)
        return gNationalDexRatingText_LessThan475;

    return gNationalDexRatingText_LessThanMaxDex;
}

#else

// This shows your Hoenn Pokédex rating and not your National Dex.
const u8 *GetPokedexRatingText(u32 count)
{
    u32 i, j, k;
    u16 maxDex = REGIONAL_DEX_COUNT - 1;
    // doesNotCountForRegionalPokedex
    for (i = 0; i < REGIONAL_DEX_COUNT; i++)
    {
        j = RegionalToNationalOrder(i + 1);
        k = NationalPokedexNumToSpecies(j);
        if (gSpeciesInfo[k].dexNotRequired || (gSpeciesInfo[k].isMythical && !gSpeciesInfo[k].dexForceRequired))
        {
            if (GetSetPokedexFlag(j, FLAG_GET_CAUGHT))
                count--;
            maxDex--;
        }
    }

    u32 idx = (count * (BIRCH_DEX_STRINGS - 1)) / maxDex;

    gSpecialVar_Result = idx == (BIRCH_DEX_STRINGS - 1);

    return sBirchDexRatingTexts[idx];
}

#endif // IS_HNS

void ShowPokedexRatingMessage(void)
{
    ShowFieldMessage(GetPokedexRatingText(gSpecialVar_0x8004));
}

// FRLG
extern const u8 PokedexRating_Text_LessThan10[];
extern const u8 PokedexRating_Text_LessThan20[];
extern const u8 PokedexRating_Text_LessThan30[];
extern const u8 PokedexRating_Text_LessThan40[];
extern const u8 PokedexRating_Text_LessThan50[];
extern const u8 PokedexRating_Text_LessThan60[];
extern const u8 PokedexRating_Text_LessThan70[];
extern const u8 PokedexRating_Text_LessThan80[];
extern const u8 PokedexRating_Text_LessThan90[];
extern const u8 PokedexRating_Text_LessThan100[];
extern const u8 PokedexRating_Text_LessThan110[];
extern const u8 PokedexRating_Text_LessThan120[];
extern const u8 PokedexRating_Text_LessThan130[];
extern const u8 PokedexRating_Text_LessThan140[];
extern const u8 PokedexRating_Text_LessThan150[];
extern const u8 PokedexRating_Text_Complete[];

u16 GetFrlgPokedexCount(void)
{
    if (gSpecialVar_0x8004 == 0)
    {
        gSpecialVar_0x8005 = GetKantoPokedexCount(FLAG_GET_SEEN);
        gSpecialVar_0x8006 = GetKantoPokedexCount(FLAG_GET_CAUGHT);
    }
    else
    {
        gSpecialVar_0x8005 = GetNationalPokedexCount(FLAG_GET_SEEN);
        gSpecialVar_0x8006 = GetNationalPokedexCount(FLAG_GET_CAUGHT);
    }
    return IsNationalPokedexEnabled();
}

static const u8 *GetProfOaksRatingMessageByCount(u16 count)
{
    gSpecialVar_Result = FALSE;

    if (count > 0 && GetSetPokedexFlag(NATIONAL_DEX_MEW, FLAG_GET_CAUGHT))
        count--;

    if (count < 10)
        return PokedexRating_Text_LessThan10;

    if (count < 20)
        return PokedexRating_Text_LessThan20;

    if (count < 30)
        return PokedexRating_Text_LessThan30;

    if (count < 40)
        return PokedexRating_Text_LessThan40;

    if (count < 50)
        return PokedexRating_Text_LessThan50;

    if (count < 60)
        return PokedexRating_Text_LessThan60;

    if (count < 70)
        return PokedexRating_Text_LessThan70;

    if (count < 80)
        return PokedexRating_Text_LessThan80;

    if (count < 90)
        return PokedexRating_Text_LessThan90;

    if (count < 100)
        return PokedexRating_Text_LessThan100;

    if (count < 110)
        return PokedexRating_Text_LessThan110;

    if (count < 120)
        return PokedexRating_Text_LessThan120;

    if (count < 130)
        return PokedexRating_Text_LessThan130;

    if (count < 140)
        return PokedexRating_Text_LessThan140;

    if (count < KANTO_DEX_COUNT - 1)
        return PokedexRating_Text_LessThan150;

    gSpecialVar_Result = TRUE;
    return PokedexRating_Text_Complete;
}

void GetProfOaksRatingMessage(void)
{
    ShowFieldMessage(GetProfOaksRatingMessageByCount(gSpecialVar_0x8004));
}
