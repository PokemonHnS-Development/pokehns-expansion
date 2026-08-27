#include "global.h"
#include "ui_screenshots.h"
#include "strings.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "field_weather.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "item.h"
#include "item_menu.h"
#include "item_menu_icons.h"
#include "list_menu.h"
#include "item_icon.h"
#include "item_use.h"
#include "international_string_util.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "palette.h"
#include "party_menu.h"
#include "scanline_effect.h"
#include "script.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text_window.h"
#include "overworld.h"
#include "event_data.h"
#include "constants/items.h"
#include "constants/field_weather.h"
#include "constants/songs.h"
#include "constants/rgb.h"
#include "constants/event_objects.h"
#include "comfy_anim.h"
#include "random.h"

/*
 * 
 */
 
//==========DEFINES==========//
struct ScreenshotsResources
{
    MainCallback savedCallback;     // determines callback to run when we exit. e.g. where do we want to go after closing the menu
    u8 gfxLoadState;
    u16 playerIconSpriteId;
    u16 nameplateSpriteId[2];
    u16 cursorIconSpriteId;
    u16 selectedSeaSectionId;
};

enum WindowIds
{
    WINDOW_1,
};

//==========EWRAM==========//
static EWRAM_DATA struct ScreenshotsResources *sScreenshotsDataPtr = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;
static EWRAM_DATA u8 *sBg2TilemapBuffer = NULL;

//==========STATIC=DEFINES==========//
static void Screenshots_RunSetup(void);
static bool8 Screenshots_DoGfxSetup(void);
static bool8 Screenshots_InitBgs(void);
static void Screenshots_FadeAndBail(void);
static bool8 Screenshots_LoadGraphics(void);
static void Screenshots_InitWindows(void);
static void PrintToWindow(u16 seaSectionId);
static void Task_ScreenshotsWaitFadeIn(u8 taskId);
static void Task_ScreenshotsMain(u8 taskId);

//==========CONST=DATA==========//
static const struct BgTemplate sScreenshotsBgTemplates[] =
{
    {
        .bg = 0,    // windows, etc
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .priority = 1
    }, 
    {
        .bg = 1,    // this bg loads the UI tilemap
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .priority = 0,
        .paletteMode = 1,
    },
    {
        .bg = 2,    // this bg loads the UI tilemap
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .priority = 1
    }
};

static const struct WindowTemplate sScreenshotsWindowTemplates[] = 
{
    [WINDOW_1] = 
    {
        .bg = 0,            // which bg to print text on
        .tilemapLeft = 20,   // position from left (per 8 pixels)
        .tilemapTop = 17,    // position from top (per 8 pixels)
        .width = 10,        // width (per 8 pixels)
        .height = 3,        // height (per 8 pixels)
        .paletteNum = 15,   // palette index to use for text
        .baseBlock = 1,     // tile start in VRAM
    },
    DUMMY_WIN_TEMPLATE
};


static const u32 sAlolaMapScreenshotsTiles[] = INCBIN_U32("graphics/ui_screenshots/hnsAlolaMap_tiles.8bpp.smol");
static const u32 sAlolaMapScreenshotsTilemap[] = INCBIN_U32("graphics/ui_screenshots/hnsAlolaMap_tiles.bin.smolTM");
static const u16 sAlolaMapScreenshotsPalette[] = INCBIN_U16("graphics/ui_screenshots/hnsAlolaMap_tiles.gbapal");


struct Screenshot {
	const u32 *screenshotTiles;
	const u32 *screenshotTilemap;
	const u16 *screenshotPalette;
};

static const struct Screenshot sScreenshotData[] = {
	[SCREENSHOT_ALOLA_MAP] = {
		.screenshotTiles = sAlolaMapScreenshotsTiles,
		.screenshotTilemap = sAlolaMapScreenshotsTilemap,
		.screenshotPalette = sAlolaMapScreenshotsPalette,
	},
};


enum Colors
{
    FONT_BLACK,
    FONT_WHITE,
    FONT_RED,
    FONT_BLUE,
};
static const u8 sScreenshotsWindowFontColors[][3] = 
{
    [FONT_BLACK]  = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_DARK_GRAY,  TEXT_COLOR_LIGHT_GRAY},
    [FONT_WHITE]  = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_WHITE,  TEXT_COLOR_DARK_GRAY},
    [FONT_RED]   = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_RED,        TEXT_COLOR_LIGHT_GRAY},
    [FONT_BLUE]  = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_BLUE,       TEXT_COLOR_LIGHT_GRAY},
};

//==========FUNCTIONS==========//
// UI loader template
// void Task_OpenScreenshotsFromStartScreenshots(u8 taskId)
// {
//     s16 *data = gTasks[taskId].data;
//     if (!gPaletteFade.active)
//     {
//         CleanupOverworldWindowsAndTilemaps();
//         Screenshots_Init(CB2_ReturnToFullScreenStartMenu);
//         DestroyTask(taskId);
//     }
// }

void OpenScreenshotsFromScript(void)
{
	CleanupOverworldWindowsAndTilemaps();
	Screenshots_Init(CB2_ReturnToFieldContinueScript);
}

// This is our main initialization function if you want to call the menu from elsewhere
void Screenshots_Init(MainCallback callback)
{
    if ((sScreenshotsDataPtr = AllocZeroed(sizeof(struct ScreenshotsResources))) == NULL)
    {
        SetMainCallback2(callback);
        return;
    }
    
    // initialize stuff
    sScreenshotsDataPtr->gfxLoadState = 0;
    sScreenshotsDataPtr->savedCallback = callback;
    
    SetMainCallback2(Screenshots_RunSetup);
}

static void Screenshots_RunSetup(void)
{
    while (1)
    {
        if (Screenshots_DoGfxSetup() == TRUE)
            break;
    }
}

static void Screenshots_MainCB(void)
{
    RunTasks();
    AdvanceComfyAnimations();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void Screenshots_VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static bool8 Screenshots_DoGfxSetup(void)
{
    u8 taskId;
    switch (gMain.state)
    {
    case 0:
        DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000)
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        ResetVramOamAndBgCntRegs();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP); 
        gMain.state++;
        break;
    case 2:
        if (Screenshots_InitBgs())
        {
            sScreenshotsDataPtr->gfxLoadState = 0;
            gMain.state++;
        }
        else
        {
            Screenshots_FadeAndBail();
            return TRUE;
        }
        break;
    case 3:
        if (Screenshots_LoadGraphics() == TRUE)
            gMain.state++;
        break;
    case 4:
        Screenshots_InitWindows();
        gMain.state++;
        break;
    case 5:
        taskId = CreateTask(Task_ScreenshotsWaitFadeIn, 0);
        BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
        gMain.state++;
        break;
    case 6:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    default:
        SetVBlankCallback(Screenshots_VBlankCB);
        SetMainCallback2(Screenshots_MainCB);
        return TRUE;
    }
    return FALSE;
}

#define try_free(ptr) ({        \
    void ** ptr__ = (void **)&(ptr);   \
    if (*ptr__ != NULL)                \
        Free(*ptr__);                  \
})

static void Screenshots_FreeResources(void)
{
    try_free(sScreenshotsDataPtr);
    try_free(sBg1TilemapBuffer);
    try_free(sBg2TilemapBuffer);
    ReleaseComfyAnims();
    FreeAllWindowBuffers();
}


static void Task_ScreenshotsWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sScreenshotsDataPtr->savedCallback);
        Screenshots_FreeResources();
        DestroyTask(taskId);
    }
}

static void Screenshots_FadeAndBail(void)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_ScreenshotsWaitFadeAndBail, 0);
    SetVBlankCallback(Screenshots_VBlankCB);
    SetMainCallback2(Screenshots_MainCB);
}

static bool8 Screenshots_InitBgs(void)
{
    ResetAllBgsCoordinates();
    sBg1TilemapBuffer = Alloc(0x800);
    if (sBg1TilemapBuffer == NULL)
        return FALSE;
    memset(sBg1TilemapBuffer, 0, 0x800);

    sBg2TilemapBuffer = Alloc(0x800);
    if (sBg2TilemapBuffer == NULL)
        return FALSE;
    memset(sBg2TilemapBuffer, 0, 0x800);

    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sScreenshotsBgTemplates, NELEMS(sScreenshotsBgTemplates));
    SetBgTilemapBuffer(1, sBg1TilemapBuffer);
    SetBgTilemapBuffer(2, sBg2TilemapBuffer);
    ScheduleBgCopyTilemapToVram(1);
    //ScheduleBgCopyTilemapToVram(2);
    ShowBg(1);
    return TRUE;
}

static bool8 Screenshots_LoadGraphics(void)
{
    switch (sScreenshotsDataPtr->gfxLoadState)
    {
    case 0:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(1, sScreenshotData[gSpecialVar_0x8000].screenshotTiles, 0, 0, 0);
        sScreenshotsDataPtr->gfxLoadState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            DecompressDataWithHeaderWram(sScreenshotData[gSpecialVar_0x8000].screenshotTilemap, sBg1TilemapBuffer);
            sScreenshotsDataPtr->gfxLoadState++;
        }
        break;
    case 2:
        LoadPalette(sScreenshotData[gSpecialVar_0x8000].screenshotPalette, 0, PLTT_SIZE_8BPP);
        sScreenshotsDataPtr->gfxLoadState++;
        break;
    default:
        sScreenshotsDataPtr->gfxLoadState = 0;
        return TRUE;
    }
    return FALSE;
}

static void Screenshots_InitWindows(void)
{

}


static void PrintToWindow(u16 seaSectionId)
{

}

static void Task_ScreenshotsWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_ScreenshotsMain;
}

static void Task_ScreenshotsTurnOff(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        SetMainCallback2(sScreenshotsDataPtr->savedCallback);
        Screenshots_FreeResources();
        DestroyTask(taskId);
    }
}

/* This is the meat of the UI. This is where you wait for player inputs and can branch to other tasks accordingly */
static void Task_ScreenshotsMain(u8 taskId)
{
    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_PC_OFF);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_ScreenshotsTurnOff;
    }
}


