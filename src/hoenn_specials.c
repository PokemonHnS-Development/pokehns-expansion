// Hoenn & Seek (part 13): script specials for Hoenn dialogue and gifts.
#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "hoenn.h"
#include "item.h"
#include "list_menu.h"
#include "malloc.h"
#include "pokemon.h"
#include "script.h"
#include "script_menu.h"
#include "string_util.h"
#include "constants/abilities.h"
#include "constants/items.h"
#include "constants/opponents.h"
#include "constants/hoenn_custom.h"

#if IS_HNS

// Fake-fight flags sit above every real Hoenn trainer flag.
STATIC_ASSERT(HOENN_TRAINER_FLAGS_START + TRAINERS_COUNT_HNS - HOENN_TRAINERS_START <= HOENN_FAKE_FLAGS_START, HoennFakeFlagsOverlapTrainers);

// callnative HoennSeek_EndScriptIfSeeing (part 14): a trainer's sight check runs
// the object's script until it reaches an effect, and walks up if it finds one.
// Fake fights that already happened put this first on their talk path, so the
// sight check ends there and the trainer stays put; talking still gets a line.
// Tagged requests_effects=1 in the script, so the sight check runs it.
void HoennSeek_EndScriptIfSeeing(struct ScriptContext *ctx)
{
    Script_RequestEffects(SCREFF_V1);
    // Only the sight check breaks on trainerbattle; the talk check (which skips
    // scripts with no effect) must keep going so talking still works.
    if (Script_IsAnalyzingEffects() && ctx->breakOnTrainerBattle)
        StopScript(ctx);
}

// specialvar VAR_RESULT, HoennGetStampCount: how many Hoenn gym stamps the player has.
u16 HoennGetStampCount(void)
{
    return HoennCountStamps();
}

// specialvar VAR_RESULT, HoennBufferFollower: TRUE if a Pokémon is following
// the player, with its nickname in STR_VAR_1 and its species name in STR_VAR_2.
u16 HoennBufferFollower(void)
{
    struct Pokemon *mon;

    if (GetFollowerObject() == NULL || (mon = GetFirstLiveMon()) == NULL)
        return FALSE;
    GetMonData(mon, MON_DATA_NICKNAME, gStringVar1);
    StringGet_Nickname(gStringVar1);
    StringCopy(gStringVar2, GetSpeciesName(GetMonData(mon, MON_DATA_SPECIES)));
    return TRUE;
}

// Steven's stone collection (Mossdeep): every non-key stone except Mega Stones
// (Hoenn & Seek has no Megas), in two menus. VAR_0x8004 picks the menu.
enum { STONES_EVOLUTION, STONES_OTHER };

static const u16 sEvolutionStones[] = {
    ITEM_FIRE_STONE, ITEM_WATER_STONE, ITEM_THUNDER_STONE, ITEM_LEAF_STONE,
    ITEM_ICE_STONE, ITEM_MOON_STONE, ITEM_SUN_STONE, ITEM_SHINY_STONE,
    ITEM_DUSK_STONE, ITEM_DAWN_STONE, ITEM_OVAL_STONE,
};

static const u16 sOtherStones[] = {
    ITEM_EVERSTONE, ITEM_HARD_STONE, ITEM_FLOAT_STONE, ITEM_ODD_KEYSTONE,
};

// Returns the index-th stone of a menu, or ITEM_NONE past its end.
static u32 GetStone(u32 menu, u32 index)
{
    if (menu == STONES_EVOLUTION)
        return index < ARRAY_COUNT(sEvolutionStones) ? sEvolutionStones[index] : ITEM_NONE;
    return index < ARRAY_COUNT(sOtherStones) ? sOtherStones[index] : ITEM_NONE;
}

// special HoennPushStoneList: fills the dynmultistack list for menu VAR_0x8004.
// Entry ids are list indexes; HoennStoneFromIndex turns one back into an item.
void HoennPushStoneList(void)
{
    u32 i, item;
    struct ListMenuItem entry;

    for (i = 0; (item = GetStone(gSpecialVar_0x8004, i)) != ITEM_NONE; i++)
    {
        u8 *name = Alloc(ITEM_NAME_LENGTH + 1);
        CopyItemName(item, name);
        entry.name = name;
        entry.id = i;
        MultichoiceDynamic_PushElement(entry);
    }
}

// specialvar VAR_RESULT, HoennStoneFromIndex: the item for list index VAR_0x8005
// of menu VAR_0x8004 (ITEM_NONE if out of range).
u16 HoennStoneFromIndex(void)
{
    return GetStone(gSpecialVar_0x8004, gSpecialVar_0x8005);
}

// ---------------------------------------------------------------------------
// The Mossdeep mind reader (part 14a): perfects IVs and changes abilities.
// VAR_0x8004 is the party slot (from ChoosePartyMon) in all of these.

static const u8 sIVStatNames[NUM_STATS][8] = {
    _("HP"), _("ATTACK"), _("DEFENSE"), _("SPEED"), _("SP. ATK"), _("SP. DEF"),
};

// special HoennPushIVList: one entry per stat, "ATTACK  12", id = stat index
// (HP, Atk, Def, Speed, Sp. Atk, Sp. Def: the MON_DATA_*_IV order).
void HoennPushIVList(void)
{
    struct Pokemon *mon = &gPlayerParty[gSpecialVar_0x8004];
    struct ListMenuItem entry;
    u32 i;

    for (i = 0; i < NUM_STATS; i++)
    {
        u8 *name = Alloc(20);
        u8 *end = StringCopy(name, sIVStatNames[i]);
        *end++ = CHAR_SPACE;
        *end++ = CHAR_SPACE;
        ConvertIntToDecimalStringN(end, GetMonData(mon, MON_DATA_HP_IV + i), STR_CONV_MODE_LEFT_ALIGN, 2);
        entry.name = name;
        entry.id = i;
        MultichoiceDynamic_PushElement(entry);
    }
}

// specialvar VAR_RESULT, HoennCheckIV: TRUE if stat VAR_0x8005's IV is
// already 31. Puts the stat name in STR_VAR_2.
u16 HoennCheckIV(void)
{
    u32 stat = gSpecialVar_0x8005;

    if (stat >= NUM_STATS)
        return TRUE;
    StringCopy(gStringVar2, sIVStatNames[stat]);
    return GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_HP_IV + stat) >= MAX_PER_STAT_IVS;
}

// specialvar VAR_RESULT, HoennMaxIV: raises stat VAR_0x8005's IV to 31.
// FALSE if it was already 31. Puts the stat name in STR_VAR_2.
u16 HoennMaxIV(void)
{
    struct Pokemon *mon = &gPlayerParty[gSpecialVar_0x8004];
    u32 stat = gSpecialVar_0x8005, iv = MAX_PER_STAT_IVS;

    if (stat >= NUM_STATS)
        return FALSE;
    StringCopy(gStringVar2, sIVStatNames[stat]);
    if (GetMonData(mon, MON_DATA_HP_IV + stat) >= MAX_PER_STAT_IVS)
        return FALSE;
    SetMonData(mon, MON_DATA_HP_IV + stat, &iv);
    CalculateMonStats(mon);
    return TRUE;
}

// special HoennPushAbilityList: the species' other abilities (not the current
// one, no blanks or duplicates), id = ability slot (2 = hidden).
void HoennPushAbilityList(void)
{
    struct Pokemon *mon = &gPlayerParty[gSpecialVar_0x8004];
    u32 species = GetMonData(mon, MON_DATA_SPECIES);
    enum Ability current = GetMonAbility(mon);
    struct ListMenuItem entry;
    u32 slot, other;

    for (slot = 0; slot < NUM_ABILITY_SLOTS; slot++)
    {
        enum Ability ability = GetSpeciesAbility(species, slot);
        bool32 seen = FALSE;
        u8 *name;

        if (ability == ABILITY_NONE || ability == current)
            continue;
        for (other = 0; other < slot; other++)
            seen |= (GetSpeciesAbility(species, other) == ability);
        if (seen)
            continue;
        // The menu frees every name when it closes, so push a copy.
        name = Alloc(ABILITY_NAME_LENGTH + 1);
        StringCopy(name, gAbilitiesInfo[ability].name);
        entry.name = name;
        entry.id = slot;
        MultichoiceDynamic_PushElement(entry);
    }
}

// specialvar VAR_RESULT, HoennCountOtherAbilities: how many entries
// HoennPushAbilityList would push (0 = nothing to change to).
u16 HoennCountOtherAbilities(void)
{
    struct Pokemon *mon = &gPlayerParty[gSpecialVar_0x8004];
    u32 species = GetMonData(mon, MON_DATA_SPECIES);
    enum Ability current = GetMonAbility(mon);
    u32 slot, other, count = 0;

    for (slot = 0; slot < NUM_ABILITY_SLOTS; slot++)
    {
        enum Ability ability = GetSpeciesAbility(species, slot);
        bool32 seen = FALSE;

        if (ability == ABILITY_NONE || ability == current)
            continue;
        for (other = 0; other < slot; other++)
            seen |= (GetSpeciesAbility(species, other) == ability);
        if (!seen)
            count++;
    }
    return count;
}

// special HoennBufferAbilitySlot: name of ability slot VAR_0x8005 in STR_VAR_2.
void HoennBufferAbilitySlot(void)
{
    u32 species = GetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_SPECIES);
    StringCopy(gStringVar2, gAbilitiesInfo[GetSpeciesAbility(species, gSpecialVar_0x8005)].name);
}

// special HoennSetAbilitySlot: gives the Pokémon ability slot VAR_0x8005.
void HoennSetAbilitySlot(void)
{
    u32 slot = gSpecialVar_0x8005;
    SetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_ABILITY_NUM, &slot);
}

#endif // IS_HNS
