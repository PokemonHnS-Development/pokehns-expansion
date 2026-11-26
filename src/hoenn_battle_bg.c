// Hoenn & Seek 2.0 (part 13b): battle backgrounds of their own for Hoenn places.
//
// Part 20a of 1.0 gave Hoenn maps battle environments from HnS's art (Route 111 and
// Mt. Pyre got the mountain, Route 113 the snowy mountain). This adds three
// backgrounds made for Hoenn: the desert, the ash fields and Mt. Pyre's graves.
//
// THE ART
//   tools/hoenn/gen_hoenn_battle_art.py builds each one from an HnS modern background
//   (recoloured palettes, dunes and gravestones drawn in, the palm trees cleared) into
//   graphics/battle_environment/hoenn_*/, from the "art" section of
//   data/hoenn/battle_environments.json, and writes the tables included below.
//
// WHERE IT SHOWS
//   Only the graphics change, never the environment: a battle on Mt. Pyre is still a
//   MOUNTAIN battle for Secret Power, Nature Power and Camouflage. A background shows
//   when the map is listed and the battle's environment is the one listed for it, so
//   surfing, the gym leaders' stadium and every other override keep their own art.
//   It replaces HnS's modern backgrounds only (the default); with classic backgrounds
//   chosen in the options, the listed environments show their classic art as before.
//
// THE DESERT
//   Route 111 is one map with grass at both ends and the desert in the middle, and
//   part 20a's map default (MOUNTAIN) skips the tile checks. HoennMapEnvironment()
//   gives its sand tiles the SAND environment back, which is also right for Secret
//   Power and Nature Power there; the desert background then replaces SAND's beach.
#include "global.h"
#include "hoenn_battle_bg.h"
#include "constants/battle.h"
#include "constants/maps.h"
#include "metatile_behavior.h"

#if IS_HNS

struct HoennBattleBg
{
    const u32 *tileset;
    const u32 *tilemap;
    const u32 *entryTileset;
    const u32 *entryTilemap;
    const u16 *palettes[3]; // day, morning/evening, night (battle_bg.c's time-of-day order)
};

struct HoennBattleBgMap
{
    u16 mapId;
    u8 environment;
    u8 background;
    u8 time; // HOENN_BATTLE_BG_ANY_TIME or a fixed palette (0-2)
};

#define HOENN_BATTLE_BG_ANY_TIME 0xFF

#include "data/graphics/hoenn_battle_environment.h"
#include "data/hoenn_battle_art.h"

static u16 CurrentMapId(void)
{
    return (gSaveBlock1Ptr->location.mapGroup << 8) | gSaveBlock1Ptr->location.mapNum;
}

static const struct HoennBattleBgMap *FindBackground(u32 environment)
{
    u32 i;
    u16 mapId = CurrentMapId();

    for (i = 0; i < ARRAY_COUNT(sHoennBattleBgMaps); i++)
    {
        if (sHoennBattleBgMaps[i].mapId == mapId && sHoennBattleBgMaps[i].environment == environment)
            return &sHoennBattleBgMaps[i];
    }
    return NULL;
}

s32 HoennMapEnvironment(s32 mapDefault, u16 tileBehavior)
{
    u32 i;
    u16 mapId = CurrentMapId();

    if (mapDefault < 0 || !MetatileBehavior_IsSandOrDeepSand(tileBehavior))
        return mapDefault;
    for (i = 0; i < ARRAY_COUNT(sHoennSandMaps); i++)
    {
        if (sHoennSandMaps[i] == mapId)
            return BATTLE_ENVIRONMENT_SAND;
    }
    return mapDefault;
}

void HoennBattleBackground(u32 environment, u32 timeOfDay, const void **tileset, const void **tilemap, const void **palette)
{
    const struct HoennBattleBgMap *map = FindBackground(environment);
    const struct HoennBattleBg *bg;

    if (map == NULL)
        return;
    bg = &sHoennBattleBgs[map->background];
    if (map->time != HOENN_BATTLE_BG_ANY_TIME)
        timeOfDay = map->time;
    *tileset = bg->tileset;
    *tilemap = bg->tilemap;
    *palette = bg->palettes[timeOfDay < 3 ? timeOfDay : 0];
}

void HoennBattleBackgroundEntry(u32 environment, const void **tileset, const void **tilemap)
{
    const struct HoennBattleBgMap *map = FindBackground(environment);

    if (map == NULL)
        return;
    *tileset = sHoennBattleBgs[map->background].entryTileset;
    *tilemap = sHoennBattleBgs[map->background].entryTilemap;
}

#endif // IS_HNS
