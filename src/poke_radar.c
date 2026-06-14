#include "global.h"
#include "task.h"
#include "event_object_movement.h"
#include "item_use.h"
#include "event_scripts.h"
#include "event_data.h"
#include "script.h"
#include "event_object_lock.h"
#include "field_specials.h"
#include "graphics.h"
#include "item_icon.h"
#include "item_menu_icons.h"
#include "item.h"
#include "item_menu.h"
#include "field_effect.h"
#include "field_weather.h"
#include "script_movement.h"
#include "battle.h"
#include "battle_setup.h"
#include "random.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "fieldmap.h"
#include "field_camera.h"
#include "poke_radar.h"
#include "pokemon_icon.h"
#include "pokedex.h"
#include "dexnav.h"
#include "decompress.h"
#include "palette.h"
#include "menu.h"
#include "string_util.h"
#include "overworld.h"
#include "tv.h"
#include "malloc.h"
#include "field_screen_effect.h"
#include "gym_leader_rematch.h"
#include "sound.h"
#include "constants/event_object_movement.h"
#include "constants/event_objects.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/songs.h"
#include "constants/script_commands.h"
#include "constants/trainer_types.h"
#include "constants/field_effects.h"
#include "constants/wild_encounter.h"
#include "wild_encounter.h"
#include "rtc.h"

// Documentation for the Poke Radar cannot be found anywhere. yet.

enum PokeRadarEncounterTableIndices {
    LAND_START = 0,
    LAND_END = LAND_START + 11,
    LAND_COUNT,
    WATER_START = 0,
    WATER_END = WATER_START + 11,
    WATER_COUNT,
    OLDROD_START = 0,
    OLDROD_END = OLDROD_START + 1,
    OLDROD_COUNT,
    GOODROD_START = OLDROD_END + 1,
    GOODROD_END = GOODROD_START + 2,
    GOODROD_COUNT = GOODROD_END - OLDROD_END,
    SUPERROD_START = GOODROD_END + 1,
    SUPERROD_END = SUPERROD_START + 4,
    SUPERROD_COUNT = SUPERROD_END - GOODROD_END,
    ROCKS_START = 0,
    ROCKS_END = ROCKS_START + 4,
    ROCKS_COUNT,
    HEADBUTT_START = 0,
    HEADBUTT_END = HEADBUTT_START + 4,
    HEADBUTT_COUNT
};

enum PokeRadarEncounterType {
    ENCOUNTER_LAND,
    ENCOUNTER_WATER,
    ENCOUNTER_OLDROD,
    ENCOUNTER_GOODROD,
    ENCOUNTER_SUPERROD,
    ENCOUNTER_ROCKS,
    ENCOUNTER_HEADBUTT,
    ENCOUNTER_COUNT
};

struct PokeRadarEncounterInfo
{
    bool8 seen;
    bool8 caught;
    s16 xCoord;
    s16 yCoord;
    u16 species;
};

struct PokeRadarEncounterTypeInfo
{
    u8 numEncounters;
    bool8 allEncounterTypeCaught;
    struct PokeRadarEncounterInfo encountersInfo[12];
};

struct PokeRadarStruct
{
    bool8 allRouteCaught;
    u8 numValidEncounterTypes;
    u8 validEncounterTypes[ENCOUNTER_COUNT];
    struct PokeRadarEncounterTypeInfo encounterTypesInfo[ENCOUNTER_COUNT];
};

struct EncounterCoords { u16 species; u8 x; u8 y; };

static const struct EncounterCoords route31EncounterCoords[] =
{
    {SPECIES_NONE, 10, 16},
    {SPECIES_LEDYBA, 10, 16},
    {SPECIES_BELLSPROUT, 27, 7},
    {SPECIES_CATERPIE, 10, 16},
    {SPECIES_MAREEP, 54, 18},
    {SPECIES_WEEDLE, 10, 16},
    {SPECIES_PICHU, 20, 7},
    {SPECIES_SPINARAK, 39, 15},
    {SPECIES_POLIWAG, 10, 5},
    {SPECIES_HOOTHOOT, 45, 24},
    {SPECIES_ZUBAT, 56, 11},
    {SPECIES_GASTLY, 39, 7},
};

// static declarations
static EWRAM_DATA struct PokeRadarStruct *sPokeRadar = NULL;

static const struct OamData sCapturedAllOam =
{
    .y = 0,
    .affineMode = 1,
    .objMode = 0,
    .mosaic = 0,
    .bpp = 0,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 0, //Highest
    .paletteNum = 12,
    .affineParam = 0,
};

static const struct SpriteTemplate sCaptureAllMonsSpriteTemplate =
{
    .tileTag = CAPTURED_ALL_TAG,
    .paletteTag = 0xFFFF,
    .oam = &sCapturedAllOam,
};

static const u16 sCapturedAllMonsPal[] = INCBIN_U16("graphics/dexnav/cursor.gbapal");
static const u32 sCapturedAllMonsTiles[] = INCBIN_U32("graphics/dexnav/captured_all.4bpp.smol");  //uses selection cursor pal
static const u32 sOwnedIconGfx[] = INCBIN_U32("graphics/dexnav/owned_icon.4bpp.smol");
static const u16 sSizeScreenSilhouette_Pal[] = INCBIN_U16("graphics/pokedex/size_silhouette.gbapal");
static const struct CompressedSpriteSheet sCapturedAllPokemonSpriteSheet = {sCapturedAllMonsTiles, (8 * 8) / 2, CAPTURED_ALL_TAG};
static const struct CompressedSpriteSheet sOwnedIconSpriteSheet = {sOwnedIconGfx, (8 * 8) / 2, OWNED_ICON_TAG};

struct PokeRadarEncounterTypeSprite
{
    const u16 tag;
    const u32 *pic;
    const u16 *pal;
};

static const struct PokeRadarEncounterTypeSprite sEncounterTypeSprites[] = {
    [ENCOUNTER_LAND]     = {ENCOUNTER_TYPE_TAG, gFieldEffectObjectPic_TallGrass,      gFieldEffectObjectPalette1},
    [ENCOUNTER_WATER]    = {ENCOUNTER_TYPE_TAG, gFieldEffectObjectPic_Ripple,         gFieldEffectObjectPalette1},
    [ENCOUNTER_OLDROD]   = {ENCOUNTER_TYPE_TAG, gItemIcon_OldRod,                     gItemIconPalette_OldRod},
    [ENCOUNTER_GOODROD]  = {ENCOUNTER_TYPE_TAG, gItemIcon_GoodRod,                    gItemIconPalette_GoodRod},
    [ENCOUNTER_SUPERROD] = {ENCOUNTER_TYPE_TAG, gItemIcon_SuperRod,                   gItemIconPalette_SuperRod},
    [ENCOUNTER_ROCKS]    = {ENCOUNTER_TYPE_TAG, gObjectEventPic_BreakableRock_hns,    gObjectEventPal_Npc1_hns},
    [ENCOUNTER_HEADBUTT] = {ENCOUNTER_TYPE_TAG, gObjectEventPic_HeadbuttableTree_hns, gObjectEventPal_HeadbuttableTree_hns},
};

static const struct OamData sEncounterTypeOam =
{
    .y = 0,
    .affineMode = 0,
    .objMode = 0,
    .bpp = 0,
    .mosaic = 0,
    .shape = SPRITE_SHAPE(16x16),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(16x16),
    .tileNum = 0,
    .priority = 0, //Highest
    .paletteNum = 13,
    .affineParam = 0,
};

static const struct SpriteTemplate sEncounterTypeSpriteTemplate =
{
    .tileTag = ENCOUNTER_TYPE_TAG,
    .paletteTag = ENCOUNTER_TYPE_TAG,
    .affineAnims = gDummySpriteAffineAnimTable,
    .anims = gDummySpriteAnimTable,
    .oam = &sEncounterTypeOam,
    .callback = SpriteCallbackDummy
};

static const u8 *const sText_EncounterTypeLabel[] = {
    [ENCOUNTER_LAND]        = COMPOUND_STRING("LAND"),
    [ENCOUNTER_WATER]       = COMPOUND_STRING("WATER"),
    [ENCOUNTER_OLDROD]      = COMPOUND_STRING(" OLD ROD"),
    [ENCOUNTER_GOODROD]     = COMPOUND_STRING(" GOOD ROD"),
    [ENCOUNTER_SUPERROD]    = COMPOUND_STRING(" SUPER ROD"),
    [ENCOUNTER_ROCKS]       = COMPOUND_STRING("ROCK SMASH"),
    [ENCOUNTER_HEADBUTT]    = COMPOUND_STRING("HEADBUTT")
};

static const u8 *const sText_PokeRadarClearWindow = COMPOUND_STRING("                                 ");
static const u8 *const sText_PokeRadarEncounterTypeDisplay = COMPOUND_STRING("{DPAD_UPDOWN}       {STR_VAR_1}");
static const u8 *const sText_PokeRadarSpeciesDisplay = COMPOUND_STRING("{DPAD_LEFTRIGHT}        {STR_VAR_2}");
static const u8 *const sText_PokeRadarConfirm = COMPOUND_STRING("\n{A_BUTTON} CONFIRM");
static const u8 *const sText_PokeRadarCancel = COMPOUND_STRING("\n{B_BUTTON} CANCEL");
static const u8 *sPokeRadar_Text_FlashRequired = COMPOUND_STRING("It's too dark for the POKé RADAR!\nTime for a FLASH of genius?{PAUSE_UNTIL_PRESS}$");

static void Task_PokeRadar(u8 taskId);
static bool32 PokeRadar_Init(struct Task *task);
static bool32 PokeRadar_GetRadarOut(struct Task *task);
static bool32 PokeRadar_InitDisplay(struct Task *task);
static bool32 PokeRadar_Display(struct Task *task);
static bool32 PokeRadar_Cancel(struct Task *task);
static bool32 PokeRadar_Confirm(struct Task *task);
static bool32 PokeRadar_Bail(struct Task *task);

static void GatherMapEncounterInfo(struct Task *task);
static u32 CreateCapturedAllSprite(struct Task *task, s16 x, s16 y);
static u32 CreateEncounterTypeSprite(struct Task *task, u8 encounterType, s16 x, s16 y);
static bool8 IsObjectEventOnScreen(struct ObjectEvent *objectEvent);

enum
{
    POKE_RADAR_INIT,
    POKE_RADAR_GET_RADAR_OUT,
    POKE_RADAR_INIT_DISPLAY,
    POKE_RADAR_DISPLAY,
    POKE_RADAR_CONFIRM,
    POKE_RADAR_CANCEL,
    POKE_RADAR_BAIL
};

static bool32 (*const sPokeRadarStateFuncs[])(struct Task *) =
{
    [POKE_RADAR_INIT]                  = PokeRadar_Init,
    [POKE_RADAR_GET_RADAR_OUT]         = PokeRadar_GetRadarOut,
    [POKE_RADAR_INIT_DISPLAY]          = PokeRadar_InitDisplay,
    [POKE_RADAR_DISPLAY]               = PokeRadar_Display,
    [POKE_RADAR_CONFIRM]               = PokeRadar_Confirm,
    [POKE_RADAR_CANCEL]                = PokeRadar_Cancel,
    [POKE_RADAR_BAIL]                  = PokeRadar_Bail,
};


#define tStep                   data[0] // State Function index for sPokeRadarStateFuncs
#define tFrameCounter           data[1] // Can be used to delay logic by a number of frames
#define tValidEncounterTypeIdx  data[2] // Currently Selected Encounter Type. Specifically, index of sPokeRadar->validEncounterTypes to retrieve a valid index for for sPokeRadar->encounterTypesInfo
#define tEncounterIdx           data[3] // Currently Selected Encounter. Specifically, index of sPokeRadar->encounterTypesInfo[].encountersInfo
#define tMonIconSpriteId        data[4] // Sprite ID for the Poke Radar Mon Icon
#define tEncounterTypeSpriteId  data[5] // Sprite ID for the Encounter Type Sprite
#define tCaughtSpriteId         data[6] // Sprite ID for the "Caught" Icon for the currently displayed Mon Icon
#define tCaughtAllTypeSpriteId  data[7] // Sprite ID for the "Caught" Icon for the currently displayed Encounter Type
#define tCaughtAllRouteSpriteId data[8] // Sprite ID for the "Caught" Icon for the current Route
#define tFlashLevel             data[9] // The Flash Level to return to when done with the Poke Radar


// Entry Point - Sets the central looping function
void OpenPokeRadar(void)
{
    u8 taskId = CreateTask(Task_PokeRadar, 0xFF);
    gTasks[taskId].func = Task_PokeRadar;
}

// Our only true "Task" function, called every frame at low (0xFF) priority
// Uses "tStep" and "sPokeRadarStateFuncs" to call the Function for the current State - unless we need to wait for a sound effect
static void Task_PokeRadar(u8 taskId)
{
    if (!IsSEPlaying())
        sPokeRadarStateFuncs[gTasks[taskId].tStep](&gTasks[taskId]);
}

// Allocates and Initializes PokeRadar data structures
// If current map requires Flash and it hasn't been used, bails PokeRadar outright 
// If Flash has been used, animates the Flash Level to 0 so PokeRadar UI Sprites can render
// tStep = 0 aka sPokeRadarStateFuncs[0]
static bool32 PokeRadar_Init(struct Task *task)
{
    for (u8 i = 0; i < 16; i++)
        gTasks[FindTaskIdByFunc(Task_PokeRadar)].data[i] = 0;

    sPokeRadar = AllocZeroed(sizeof(struct PokeRadarStruct));
    GatherMapEncounterInfo(task);    

    LockPlayerFieldControls();
    gPlayerAvatar.preventStep = TRUE;
    
    task->tFlashLevel = GetFlashLevel();
    if (task->tFlashLevel > 1)
    {
        PlaySE(SE_FAILURE);
        task->tStep = POKE_RADAR_BAIL;
        return FALSE;
    }
    else if (task->tFlashLevel == 1)
    {
        PlaySE(SE_M_REFLECT);
        AnimateFlash(0);
    }

    task->tStep = POKE_RADAR_GET_RADAR_OUT;
    return TRUE;
}

// Completely Fills out sPokeRadar
static void GatherMapEncounterInfo(struct Task *task)
{
    sPokeRadar->numValidEncounterTypes = 0;
    sPokeRadar->allRouteCaught = TRUE;

    u16 headerId = GetCurrentMapWildMonHeaderId();

    #ifndef NDEBUG
        MgbaPrintf(MGBA_LOG_DEBUG, "POKE RADAR TRIGGERED. MapGroup: %d MapNum: %d HeaderId: %d", gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum, headerId);
    #endif

    for (u8 encounterType = 0; encounterType < ENCOUNTER_COUNT; encounterType++)
    {
        enum TimeOfDay timeOfDay = 0;
        const struct WildPokemonInfo *monsInfo = NULL;
        struct PokeRadarEncounterTypeInfo *encounterTypeInfo = &(sPokeRadar->encounterTypesInfo[encounterType]);
        encounterTypeInfo->numEncounters = 0;
        encounterTypeInfo->allEncounterTypeCaught = TRUE;
        u8 currentIdx, lastIdx;

        // For each PokeRadar "encounter type", retrieve the WildEncounter encounter table for the current time,
        //   and prepare the first and last indices of the encounter table that map to that "encounter type".
        // This currently only matters for fishing, which is one table grouped by rod used.
        switch (encounterType)
        {
        case ENCOUNTER_LAND:
            timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_LAND);
            monsInfo = gWildMonHeaders[headerId].encounterTypes[timeOfDay].landMonsInfo;
            currentIdx = LAND_START;
            lastIdx = LAND_END;
            break;
        case ENCOUNTER_WATER:
            timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_WATER);
            monsInfo = gWildMonHeaders[headerId].encounterTypes[timeOfDay].waterMonsInfo;
            currentIdx = WATER_START;
            lastIdx = WATER_END;
            break;
        case ENCOUNTER_OLDROD:
            timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_FISHING);
            monsInfo = gWildMonHeaders[headerId].encounterTypes[timeOfDay].fishingMonsInfo;
            currentIdx = OLDROD_START;
            lastIdx = OLDROD_END;
            break;
        case ENCOUNTER_GOODROD:
            timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_FISHING);
            monsInfo = gWildMonHeaders[headerId].encounterTypes[timeOfDay].fishingMonsInfo;
            currentIdx = GOODROD_START;
            lastIdx = GOODROD_END;
            break;
        case ENCOUNTER_SUPERROD:
            timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_FISHING);
            monsInfo = gWildMonHeaders[headerId].encounterTypes[timeOfDay].fishingMonsInfo;
            currentIdx = SUPERROD_START;
            lastIdx = SUPERROD_END;
            break;
        case ENCOUNTER_ROCKS:
            timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_ROCKS);
            monsInfo = gWildMonHeaders[headerId].encounterTypes[timeOfDay].rockSmashMonsInfo;
            currentIdx = ROCKS_START;
            lastIdx = ROCKS_END;
            break;
        case ENCOUNTER_HEADBUTT:
            timeOfDay = GetTimeOfDayForEncounters(headerId, WILD_AREA_ROCKS);
            monsInfo = gWildMonHeaders[headerId].encounterTypes[timeOfDay].rockSmashMonsInfo;
            currentIdx = HEADBUTT_START;
            lastIdx = HEADBUTT_END;
            break;
        default:
            lastIdx = 0;
            currentIdx = 0;
            break;
        }

        #ifndef NDEBUG
            MgbaPrintf(MGBA_LOG_DEBUG, "Encounter Type: %d, Time of Day: %d, starting Index: %d, ending Index: %d", encounterType, timeOfDay, currentIdx, lastIdx);
        #endif

        if (monsInfo != NULL)
        {
            // Building up an array of "valid" indices for easier iteration
            // (These could technically include "invalid" indices if a map only had Good or Super Rod encounters)
            sPokeRadar->validEncounterTypes[sPokeRadar->numValidEncounterTypes++] = encounterType;

            for (; currentIdx <= lastIdx; currentIdx++)
            {
                bool8 newSpecies = TRUE;
                u16 species = monsInfo->wildPokemon[currentIdx].species;

                if (species == 0 || species > NUM_SPECIES)
                    break;

                for (u8 dupeCheckIdx = 0; dupeCheckIdx < encounterTypeInfo->numEncounters && newSpecies == TRUE; dupeCheckIdx++)
                {
                    if (encounterTypeInfo->encountersInfo[dupeCheckIdx].species == species)
                        newSpecies = FALSE;
                }

                if (newSpecies)
                {
                    // TODO - Prepare Coordinates for all encounters for all maps
                    encounterTypeInfo->encountersInfo[encounterTypeInfo->numEncounters].species = species;

                    encounterTypeInfo->encountersInfo[encounterTypeInfo->numEncounters].xCoord = route31EncounterCoords[0].x;
                    encounterTypeInfo->encountersInfo[encounterTypeInfo->numEncounters].yCoord = route31EncounterCoords[0].y;
                    for (u8 i = 1; i < 12; i++)
                    {
                        if (species == route31EncounterCoords[i].species)
                        {
                            encounterTypeInfo->encountersInfo[encounterTypeInfo->numEncounters].xCoord = route31EncounterCoords[i].x;
                            encounterTypeInfo->encountersInfo[encounterTypeInfo->numEncounters].yCoord = route31EncounterCoords[i].y;
                        }
                    }
                    
                    encounterTypeInfo->encountersInfo[encounterTypeInfo->numEncounters].seen = GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_SEEN);
                    encounterTypeInfo->encountersInfo[encounterTypeInfo->numEncounters].caught = GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_CAUGHT);

                    if (encounterTypeInfo->allEncounterTypeCaught && !encounterTypeInfo->encountersInfo[encounterTypeInfo->numEncounters].caught)
                    {
                        encounterTypeInfo->allEncounterTypeCaught = FALSE;
                        if (sPokeRadar->allRouteCaught)
                            sPokeRadar->allRouteCaught = FALSE;
                    }

                    encounterTypeInfo->numEncounters++;

                    #ifndef NDEBUG
                        switch (encounterType)
                        {
                        case ENCOUNTER_LAND:
                            MgbaPrintf(MGBA_LOG_DEBUG, "Species ID %d found for Land Encounters", species);
                            break;
                        case ENCOUNTER_WATER:
                            MgbaPrintf(MGBA_LOG_DEBUG, "Species ID %d found for Water Encounters", species);
                            break;
                        case ENCOUNTER_OLDROD:
                            MgbaPrintf(MGBA_LOG_DEBUG, "Species ID %d found for Old Rod Encounters", species);
                            break;
                        case ENCOUNTER_GOODROD:
                            MgbaPrintf(MGBA_LOG_DEBUG, "Species ID %d found for Good Rod Encounters", species);
                            break;
                        case ENCOUNTER_SUPERROD:
                            MgbaPrintf(MGBA_LOG_DEBUG, "Species ID %d found for Super Rod Encounters", species);
                            break;
                        case ENCOUNTER_ROCKS:
                            MgbaPrintf(MGBA_LOG_DEBUG, "Species ID %d found for Rock Smash Encounters", species);
                            break;
                        case ENCOUNTER_HEADBUTT:
                            MgbaPrintf(MGBA_LOG_DEBUG, "Species ID %d found for Headbutt Encounters", species);
                            break;
                        default:
                            MgbaPrintf(MGBA_LOG_WARN, "???");
                            break;
                        }
                    #endif
                }
            }
        }

        #ifndef NDEBUG
            MgbaPrintf(MGBA_LOG_DEBUG, "%d Encounters found for Encounter Type %d", encounterTypeInfo->numEncounters, encounterType);
        #endif
    }
}

// Animates the Player into the Field Move pose
// tStep = 1 aka sPokeRadarStateFuncs[1]
static bool32 PokeRadar_GetRadarOut(struct Task *task)
{
    struct ObjectEvent *playerObjEvent = &gObjectEvents[gPlayerAvatar.objectEventId];

    ObjectEventClearHeldMovementIfActive(playerObjEvent);
    playerObjEvent->enableAnim = TRUE;
    HideFollowerForFieldEffect();
    SetPlayerAvatarFieldMove();
    ObjectEventSetHeldMovement(playerObjEvent, MOVEMENT_ACTION_START_ANIM_IN_DIRECTION);
    PlaySE(SE_POKENAV_ON);
    task->tStep = POKE_RADAR_INIT_DISPLAY;
    return FALSE;
}

#define encounterTypeIdx sPokeRadar->validEncounterTypes[task->tValidEncounterTypeIdx] // translates continuous "Valid" Indices to non-continuous "actual" indices

// icon/global x = 16 to 226  (GetWindowAttribute(0, WINDOW_TILEMAP_LEFT) + 2) * 8
// icon/global y = 120 to 144 (GetWindowAttribute(0, WINDOW_TILEMAP_TOP) * 8) + 2

#define textCenterX GetWindowAttribute(0, WINDOW_WIDTH) * 4 // x-coordinate for text on the right half of the UI
#define iconLeftX GetWindowAttribute(0, WINDOW_WIDTH) + 8 // approximate x-coordinate for sprites on the left half of the UI
#define iconCenterX GetWindowAttribute(0, WINDOW_WIDTH) * 5 + 8 // approximate x-coordinate for sprites on the right half of the UI
#define iconTopY GetWindowAttribute(0, WINDOW_TILEMAP_TOP) * 8 + 8 // approximate y-coordinate for sprites on the upper line of the UI

// Draws the initial state of the PokeRadar UI
// tStep = 2 aka sPokeRadarStateFuncs[2]
static bool32 PokeRadar_InitDisplay(struct Task *task)
{
    LoadMessageBoxAndFrameGfx(0, TRUE);
    ScriptUnfreezeObjectEvents();

    struct PokeRadarEncounterTypeInfo *encounterTypeInfo = &(sPokeRadar->encounterTypesInfo[encounterTypeIdx]);
    u16 species = encounterTypeInfo->encountersInfo[task->tEncounterIdx].species;
    bool8 seen = encounterTypeInfo->encountersInfo[task->tEncounterIdx].seen;
    bool8 caught = encounterTypeInfo->encountersInfo[task->tEncounterIdx].caught;
    u16 displaySpecies = seen ? species : SPECIES_NONE;

    StringCopy(gStringVar1, sText_EncounterTypeLabel[encounterTypeIdx]);
    StringCopy(gStringVar2, GetSpeciesName(displaySpecies)); // TODO - Decide if alternative display text is preferred
    StringExpandPlaceholders(gStringVar3, sText_PokeRadarEncounterTypeDisplay);
    StringExpandPlaceholders(gStringVar4, sText_PokeRadarSpeciesDisplay);

    AddTextPrinterParameterized(0, FONT_NORMAL, gStringVar3, 0, 0, 0, NULL);
    AddTextPrinterParameterized(0, FONT_NORMAL, gStringVar4, textCenterX, 0, 0, NULL);
    AddTextPrinterParameterized(0, FONT_NORMAL, sText_PokeRadarConfirm, 0, 0, 0, NULL);
    AddTextPrinterParameterized(0, FONT_NORMAL, sText_PokeRadarCancel, textCenterX, 0, 0, NULL);

    // If player hasn't "seen" this species before, load an all-black palette with the species' tag in place of its intended palette
    if (!seen)
        LoadSpritePaletteWithTag(sSizeScreenSilhouette_Pal, gMonIconPaletteTable[gSpeciesInfo[SanitizeSpeciesId(species)].iconPalIndex].tag);
    else
        LoadMonIconPalette(species);

    task->tMonIconSpriteId = CreateMonIconNoPersonality(species, SpriteCB_MonIcon, iconCenterX, iconTopY - 4, 0);
    gSprites[task->tMonIconSpriteId].oam.priority = 0; // ensure Mon Icon is drawn above text box

    if (caught)
        task->tCaughtSpriteId = CreateCapturedAllSprite(task, iconLeftX, iconTopY);

    if (encounterTypeInfo->allEncounterTypeCaught)
        task->tCaughtAllTypeSpriteId = CreateCapturedAllSprite(task, iconCenterX, iconTopY);
    
    if (sPokeRadar->allRouteCaught)
        task->tCaughtAllRouteSpriteId = CreateCapturedAllSprite(task, iconLeftX - 15, iconTopY + 15);

    task->tEncounterTypeSpriteId = CreateEncounterTypeSprite(task, encounterTypeIdx, iconLeftX, iconTopY);

    task->tStep = POKE_RADAR_DISPLAY;
    task->tFrameCounter = 1;

    SetDynamicWarpWithCoords(0, gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum, WARP_ID_NONE, gSaveBlock1Ptr->pos.x, gSaveBlock1Ptr->pos.y);
    FlagSet(FLAG_HIDE_MAP_NAME_POPUP);

    return TRUE;
}

// Waits for User Input, then attempts to redraw relevant elements of the PokeRadar UI
// tStep = 3 aka sPokeRadarStateFuncs[3]
static bool32 PokeRadar_Display(struct Task *task)
{
    LockPlayerFieldControls();

    bool8 redraw = FALSE;
    u8 encounterTypePrev = encounterTypeIdx;
    u8 encounterPrev = task->tEncounterIdx;
    struct PokeRadarEncounterTypeInfo *encounterTypeInfo = &(sPokeRadar->encounterTypesInfo[encounterTypePrev]);

    if (task->tFrameCounter == 1)
    {
        SetWarpDestination(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum, WARP_ID_NONE, encounterTypeInfo->encountersInfo[encounterPrev].xCoord, encounterTypeInfo->encountersInfo[encounterPrev].yCoord);
        WarpIntoMap();
        DrawWholeMapView();
        
        for (u8 i = 0; i < 16; i++)
        {
            if (gObjectEvents[i].active)
            {
                MoveObjectEventToMapCoords(&gObjectEvents[i], gObjectEvents[i].currentCoords.x, gObjectEvents[i].currentCoords.y);
            }
        }

        TrySpawnObjectEvents(0, 0);
        task->tFrameCounter++;
    }
    else if (task->tFrameCounter > 1)
    {
        for (u8 i = 0; i < 16; i++)
        {
            if (gObjectEvents[i].active)
            {
                if (i != gPlayerAvatar.objectEventId && !IsObjectEventOnScreen(&gObjectEvents[i]))
                    RemoveObjectEvent(&gObjectEvents[i]);
            }
            TrySpawnObjectEvents(0, 0);
        }
        task->tFrameCounter = 0;
    }
    else if (task->tEncounterTypeSpriteId == 0) // assume that if 0, Encounter Type Sprite doesn't exist
    {
        // Draw the new Encounter Type Sprite with SE, preventing input that could trigger another redraw
        task->tEncounterTypeSpriteId = CreateEncounterTypeSprite(task, encounterTypeIdx, iconLeftX, iconTopY);
        PlaySE(SE_DEX_PAGE);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        #ifndef NDEBUG
            MgbaPrintf(MGBA_LOG_DEBUG, "B Pressed");
        #endif
        task->tStep = POKE_RADAR_CANCEL;
        if (task->tFlashLevel == 1)
        {
            SetFlashLevel(1);
            PlaySE(SE_M_REFLECT);
            ObjectEventSetGraphicsId(&gObjectEvents[gPlayerAvatar.objectEventId], GetPlayerAvatarGraphicsIdByCurrentState());
            ObjectEventForceSetHeldMovement(&gObjectEvents[gPlayerAvatar.objectEventId], GetFaceDirectionMovementAction((&gObjectEvents[gPlayerAvatar.objectEventId])->facingDirection));
            CB2_ReturnToFieldFadeFromBlack();
        }
        else
        {
            PlaySE(SE_POKENAV_OFF);
        }
        return TRUE;
    }
    else if (JOY_NEW(A_BUTTON))
    {
        #ifndef NDEBUG
            MgbaPrintf(MGBA_LOG_DEBUG, "A Pressed");
        #endif
        task->tStep = POKE_RADAR_CONFIRM;
        if (task->tFlashLevel == 1)
        {
            SetFlashLevel(1);
            PlaySE(SE_M_REFLECT);
            ObjectEventSetGraphicsId(&gObjectEvents[gPlayerAvatar.objectEventId], GetPlayerAvatarGraphicsIdByCurrentState());
            ObjectEventForceSetHeldMovement(&gObjectEvents[gPlayerAvatar.objectEventId], GetFaceDirectionMovementAction((&gObjectEvents[gPlayerAvatar.objectEventId])->facingDirection));
            CB2_ReturnToFieldFadeFromBlack();
        }
        else
        {
            // TODO - Pan Camera back over to Player to guide them to the selected OW Mon
            PlaySE(SE_DEX_SEARCH);
        }
        return TRUE;
    }
    else if (JOY_NEW(DPAD_UP) || JOY_HELD(DPAD_UP))
    {
        if (--task->tValidEncounterTypeIdx < 0)
            task->tValidEncounterTypeIdx = sPokeRadar->numValidEncounterTypes - 1;
        if (sPokeRadar->numValidEncounterTypes > 1)
        {
            task->tEncounterIdx = 0;
            redraw = TRUE;
        }
    }
    else if (JOY_NEW(DPAD_DOWN) || JOY_HELD(DPAD_DOWN))
    {
        if (++task->tValidEncounterTypeIdx >= sPokeRadar->numValidEncounterTypes)
            task->tValidEncounterTypeIdx = 0;
        if (sPokeRadar->numValidEncounterTypes > 1)
        {
            task->tEncounterIdx = 0;
            redraw = TRUE;
        }
    }
    else if (JOY_NEW(DPAD_LEFT) || JOY_HELD(DPAD_LEFT))
    {
        if (--task->tEncounterIdx < 0)
            task->tEncounterIdx = encounterTypeInfo->numEncounters - 1;
        if (encounterTypeInfo->numEncounters > 1)
        {
            PlaySE(SE_DEX_SCROLL);
            redraw = TRUE;
        }
    }
    else if (JOY_NEW(DPAD_RIGHT) || JOY_HELD(DPAD_RIGHT))
    {
        if (++task->tEncounterIdx >= encounterTypeInfo->numEncounters)
            task->tEncounterIdx = 0;
        if (encounterTypeInfo->numEncounters > 1)
        {
            PlaySE(SE_DEX_SCROLL);
            redraw = TRUE;
        }
    }

    if (redraw)
    {
        u16 speciesPrev = encounterTypeInfo->encountersInfo[encounterPrev].species;
        bool8 seenPrev = encounterTypeInfo->encountersInfo[encounterPrev].seen;
        u16 displaySpeciesPrev = seenPrev ? speciesPrev : SPECIES_NONE;
        bool8 caughtPrev = encounterTypeInfo->encountersInfo[encounterPrev].caught;
        bool8 caughtAllTypePrev = encounterTypeInfo->allEncounterTypeCaught;
        u8 xPrev = encounterTypeInfo->encountersInfo[encounterPrev].xCoord;
        u8 yPrev = encounterTypeInfo->encountersInfo[encounterPrev].yCoord;

        encounterTypeInfo = &(sPokeRadar->encounterTypesInfo[encounterTypeIdx]);
        
        u16 speciesNext = encounterTypeInfo->encountersInfo[task->tEncounterIdx].species;
        bool8 seenNext = encounterTypeInfo->encountersInfo[task->tEncounterIdx].seen;
        u16 displaySpeciesNext = seenNext ? speciesNext : SPECIES_NONE;
        bool8 caughtNext = encounterTypeInfo->encountersInfo[task->tEncounterIdx].caught;
        bool8 caughtAllTypeNext = encounterTypeInfo->allEncounterTypeCaught;
        u8 xNext = encounterTypeInfo->encountersInfo[task->tEncounterIdx].xCoord;
        u8 yNext = encounterTypeInfo->encountersInfo[task->tEncounterIdx].yCoord;

        #ifndef NDEBUG
            MgbaPrintf(MGBA_LOG_DEBUG, "Previously Drawn - Species Prev: %d, Display Species Prev: %d\nNext to be Drawn - Species Next: %d, Display Species Next: %d", speciesPrev, displaySpeciesPrev, speciesNext, displaySpeciesNext);
        #endif

        if (encounterTypePrev != encounterTypeIdx)
        {
            StringCopy(gStringVar1, sText_EncounterTypeLabel[encounterTypeIdx]);
            StringExpandPlaceholders(gStringVar3, sText_PokeRadarEncounterTypeDisplay);
            AddTextPrinterParameterized(0, FONT_NORMAL, sText_PokeRadarClearWindow, 0, 0, 0, NULL);
            AddTextPrinterParameterized(0, FONT_NORMAL, gStringVar3, 0, 0, 0, NULL);

            // Both Clearing and Drawing the Old and New Sprites is too much for a single frame
            // Only clears current Sprite on this frame, sets up new Sprite to be drawn next frame
            DestroySpriteAndFreeResources(&gSprites[task->tEncounterTypeSpriteId]);
            task->tEncounterTypeSpriteId = 0; // assume that if 0, Encounter Type Sprite doesn't exist
        }

        if (displaySpeciesPrev != displaySpeciesNext)
        {
            StringCopy(gStringVar2, GetSpeciesName(displaySpeciesNext));  // TODO - Decide if alternative display text is preferred
            StringExpandPlaceholders(gStringVar4, sText_PokeRadarSpeciesDisplay);
            AddTextPrinterParameterized(0, FONT_NORMAL, sText_PokeRadarClearWindow, textCenterX, 0, 0, NULL);
            AddTextPrinterParameterized(0, FONT_NORMAL, gStringVar4, textCenterX, 0, 0, NULL);
        }
        
        if (speciesPrev != speciesNext)
        {
            #ifndef NDEBUG
                MgbaPrintf(MGBA_LOG_DEBUG, "Previous Icon Palette Num: %d", gSprites[task->tMonIconSpriteId].oam.paletteNum);
            #endif

            FreeMonIconPalette(speciesPrev);
            FreeAndDestroyMonIconSprite(&gSprites[task->tMonIconSpriteId]);

            // If player hasn't "seen" this species before, load an all-black palette with the species' tag in place of its intended palette
            if (!seenNext)
                LoadSpritePaletteWithTag(sSizeScreenSilhouette_Pal, gMonIconPaletteTable[gSpeciesInfo[SanitizeSpeciesId(speciesNext)].iconPalIndex].tag);
            else
                LoadMonIconPalette(speciesNext);
            
            task->tMonIconSpriteId = CreateMonIconNoPersonality(speciesNext, SpriteCB_MonIcon, iconCenterX, iconTopY - 4, 0);
            gSprites[task->tMonIconSpriteId].oam.priority = 0; // ensure Mon Icon is drawn above text box

            #ifndef NDEBUG
                MgbaPrintf(MGBA_LOG_DEBUG, "Next Icon Palette Num: %d", gSprites[task->tMonIconSpriteId].oam.paletteNum);
            #endif
        }

        if (caughtPrev && !caughtNext)
        {
            DestroySprite(&gSprites[task->tCaughtSpriteId]);
            task->tCaughtSpriteId = 0; // assume that if 0, Caught Sprite doesn't exist
        }
        
        if (caughtNext && !caughtPrev)
            task->tCaughtSpriteId = CreateCapturedAllSprite(task, iconLeftX, iconTopY);

        if (caughtAllTypePrev && !caughtAllTypeNext)
        {
            DestroySprite(&gSprites[task->tCaughtAllTypeSpriteId]);
            task->tCaughtAllTypeSpriteId = 0; // assume that if 0, CaughtAllType Sprite doesn't exist
        }

        if (caughtAllTypeNext && !caughtAllTypePrev)
            task->tCaughtAllTypeSpriteId = CreateCapturedAllSprite(task, iconCenterX, iconTopY);

        if (xPrev != xNext || yPrev != yNext)
        {
            task->tFrameCounter++;
        }

        return FALSE;
    }

    return TRUE;
}

static u32 CreateCapturedAllSprite(struct Task *task, s16 x, s16 y)
{
    struct CompressedSpriteSheet spriteSheet;

    spriteSheet.data = sCapturedAllMonsTiles;
    spriteSheet.size = 0x200;
    spriteSheet.tag = CAPTURED_ALL_TAG;
    LoadCompressedSpriteSheet(&spriteSheet);

    LoadPalette(sCapturedAllMonsPal, OBJ_PLTT_ID(sCapturedAllOam.paletteNum), PLTT_SIZE_4BPP);

    return CreateSprite(&sCaptureAllMonsSpriteTemplate, x, y, 0);    
}

static u32 CreateEncounterTypeSprite(struct Task *task, u8 encounterType, s16 x, s16 y)
{
    #ifndef NDEBUG
        MgbaPrintf(MGBA_LOG_DEBUG, "Attempting to Draw sprite for Encounter Type %d at coords %d x %d y", encounterType, x, y);
    #endif

    #define etag sEncounterTypeSprites[encounterType].tag
    #define epic sEncounterTypeSprites[encounterType].pic
    #define epal sEncounterTypeSprites[encounterType].pal

    u32 spriteId;
    u32 palNum;
    u16 tileNum;
    struct Sprite *sprite;
    struct SpriteSheet spriteSheet;

    if (encounterType == ENCOUNTER_OLDROD || encounterType == ENCOUNTER_GOODROD || encounterType == ENCOUNTER_SUPERROD)
    {
        if (!AllocItemIconTemporaryBuffers())
        {
            return MAX_SPRITES;
        }
        else
        {
            // Repurposes logic from AddItemIconSprite in item_icon.c
            DecompressDataWithHeaderWram(epic, gItemIconDecompressionBuffer);
            CopyItemIconPicTo4x4Buffer(gItemIconDecompressionBuffer, gItemIcon4x4Buffer);
            spriteSheet.data = gItemIcon4x4Buffer;
            spriteSheet.size = 0x200;
            spriteSheet.tag = etag;
            tileNum = LoadSpriteSheet(&spriteSheet);
            palNum = LoadSpritePaletteWithTag(epal, etag);

            struct SpriteTemplate *spriteTemplate;
            spriteTemplate = Alloc(sizeof(*spriteTemplate));
            CpuCopy16(&gItemIconSpriteTemplate, spriteTemplate, sizeof(*spriteTemplate));
            spriteTemplate->tileTag = etag;
            spriteTemplate->paletteTag = etag;
            
            spriteTemplate->callback = SpriteCallbackDummy;
            spriteTemplate->anims = gDummySpriteAnimTable;
            spriteTemplate->affineAnims = gDummySpriteAffineAnimTable;

            spriteId = CreateSprite(spriteTemplate, x + 5, y + 3, 0);
            sprite = &gSprites[spriteId];
            sprite->oam.priority = 0;
            sprite->oam.tileNum = tileNum;
            sprite->oam.paletteNum = palNum;

            FreeItemIconTemporaryBuffers();
            Free(spriteTemplate);
        }
    }
    else
    {
        spriteSheet.data = epic;
        spriteSheet.size = 0x200;
        spriteSheet.tag = etag;
        tileNum = LoadSpriteSheet(&spriteSheet);
        palNum = LoadSpritePaletteWithTag(epal, etag);
        spriteId = CreateSprite(&sEncounterTypeSpriteTemplate, x, y, 0);
        sprite = &gSprites[spriteId];
        sprite->oam.tileNum = tileNum;
        sprite->oam.paletteNum = palNum;

        if (encounterType == ENCOUNTER_LAND)
            sprite->oam.tileNum += 8;
        else if (encounterType == ENCOUNTER_WATER)
            sprite->oam.tileNum += 4;
    }

    return spriteId;
    #undef etag
    #undef epic
    #undef epal
}

// TODO - Pan Camera back over to Player to guide them to the selected OW Mon
// Currently just falls through to PokeRadar_Cancel
// tStep = 4 aka sPokeRadarStateFuncs[4]
static bool32 PokeRadar_Confirm(struct Task *task)
{
    // gObjectEvents[gPlayerAvatar.objectEventId].trackedByCamera = TRUE;
    // InitCameraUpdateCallback(gPlayerAvatar.spriteId);
    task->tStep = POKE_RADAR_CANCEL;
    return TRUE;
}

// Clears all PokeRadar data and UI elements, returns Player to their original Pose
// tStep = 5 aka sPokeRadarStateFuncs[5]
static bool32 PokeRadar_Cancel(struct Task *task)
{
    SetWarpDestinationToDynamicWarp(0);
    WarpIntoMap();
    DrawWholeMapView();

    for (u8 i = 0; i < 16; i++)
    {
        if (gObjectEvents[i].active)
        {
            MoveObjectEventToMapCoords(&gObjectEvents[i], gObjectEvents[i].currentCoords.x, gObjectEvents[i].currentCoords.y);

            if (i != gPlayerAvatar.objectEventId && !IsObjectEventOnScreen(&gObjectEvents[i]))
                RemoveObjectEvent(&gObjectEvents[i]);
        }
    }

    TrySpawnObjectEvents(0, 0);
    UpdateFollowingPokemon();

    FlagClear(FLAG_HIDE_MAP_NAME_POPUP);

    Free(sPokeRadar);

    FreeMonIconPalettes();
    FreeAndDestroyMonIconSprite(&gSprites[task->tMonIconSpriteId]);

    if (task->tEncounterTypeSpriteId)
        DestroySpriteAndFreeResources(&gSprites[task->tEncounterTypeSpriteId]);

    FreeSpritePaletteByTag(CAPTURED_ALL_TAG);
    FreeSpriteTilesByTag(CAPTURED_ALL_TAG);

    if (task->tCaughtSpriteId) // assume that if 0, Sprite doesn't exist
        DestroySprite(&gSprites[task->tCaughtSpriteId]);

    if (task->tCaughtAllTypeSpriteId) // assume that if 0, Sprite doesn't exist
        DestroySprite(&gSprites[task->tCaughtAllTypeSpriteId]);

    if (task->tCaughtAllRouteSpriteId) // assume that if 0, Sprite doesn't exist
        DestroySprite(&gSprites[task->tCaughtAllRouteSpriteId]);

    ClearDialogWindowAndFrame(0, TRUE);
    
    if (task->tFlashLevel == 1)
    {
        FadeInFromBlack();
    }
    else
    {
        ObjectEventSetGraphicsId(&gObjectEvents[gPlayerAvatar.objectEventId], GetPlayerAvatarGraphicsIdByCurrentState());
        ObjectEventForceSetHeldMovement(&gObjectEvents[gPlayerAvatar.objectEventId], GetFaceDirectionMovementAction((&gObjectEvents[gPlayerAvatar.objectEventId])->facingDirection));
    }
    gPlayerAvatar.preventStep = FALSE;
    UnlockPlayerFieldControls();
    ScriptUnfreezeObjectEvents();

    DestroyTask(FindTaskIdByFunc(Task_PokeRadar));
    return TRUE;
}

static bool32 PokeRadar_Bail(struct Task *task)
{
    Free(sPokeRadar);
    gPlayerAvatar.preventStep = FALSE;
    DisplayItemMessageOnField(FindTaskIdByFunc(Task_PokeRadar), sPokeRadar_Text_FlashRequired, Task_ItemUse_CloseMessageBoxAndReturnToField_PokeRadar);
    return FALSE;
}

bool32 IsPokeRadarEnabled(void)
{
    return (CheckBagHasItem(ITEM_POKE_RADAR, 1));
}

static bool8 IsObjectEventOnScreen(struct ObjectEvent *objectEvent)
{
    s16 x;
    s16 y;

    x = gSaveBlock1Ptr->pos.x + MAP_OFFSET;
    y = gSaveBlock1Ptr->pos.y + MAP_OFFSET;

    if ((  x - 7 <= objectEvent->currentCoords.x
        && x + 7 >= objectEvent->currentCoords.x
        && y - 5 <= objectEvent->currentCoords.y
        && y + 5 >= objectEvent->currentCoords.y) ||
        (  objectEvent->initialCoords.x == gObjectEvents[gPlayerAvatar.objectEventId].currentCoords.x
        && objectEvent->initialCoords.x == gObjectEvents[gPlayerAvatar.objectEventId].currentCoords.x))
        return TRUE;
    return FALSE;
}
