// Hoenn & Seek (part 13): script specials for Hoenn dialogue and gifts.
#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "hoenn.h"
#include "item.h"
#include "list_menu.h"
#include "malloc.h"
#include "pokemon.h"
#include "script_menu.h"
#include "string_util.h"
#include "constants/hold_effects.h"
#include "constants/items.h"

#if IS_HNS

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

// Steven's stone collection (Mossdeep): every stone that isn't a key item,
// in three menus. VAR_0x8004 picks the menu.
enum { STONES_EVOLUTION, STONES_MEGA, STONES_OTHER };

static const u16 sEvolutionStones[] = {
    ITEM_FIRE_STONE, ITEM_WATER_STONE, ITEM_THUNDER_STONE, ITEM_LEAF_STONE,
    ITEM_ICE_STONE, ITEM_MOON_STONE, ITEM_SUN_STONE, ITEM_SHINY_STONE,
    ITEM_DUSK_STONE, ITEM_DAWN_STONE, ITEM_OVAL_STONE,
};

static const u16 sOtherStones[] = {
    ITEM_EVERSTONE, ITEM_HARD_STONE, ITEM_FLOAT_STONE, ITEM_ODD_KEYSTONE,
};

static bool32 IsMegaStone(u32 item)
{
    return GetItemHoldEffect(item) == HOLD_EFFECT_MEGA_STONE
        && GetItemPocket(item) != POCKET_KEY_ITEMS;
}

// Returns the index-th stone of a menu, or ITEM_NONE past its end.
static u32 GetStone(u32 menu, u32 index)
{
    u32 item;

    switch (menu)
    {
    case STONES_EVOLUTION:
        return index < ARRAY_COUNT(sEvolutionStones) ? sEvolutionStones[index] : ITEM_NONE;
    case STONES_OTHER:
        return index < ARRAY_COUNT(sOtherStones) ? sOtherStones[index] : ITEM_NONE;
    default:
        for (item = ITEM_NONE + 1; item < ITEMS_COUNT; item++)
        {
            if (IsMegaStone(item) && index-- == 0)
                return item;
        }
        return ITEM_NONE;
    }
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

#endif // IS_HNS
