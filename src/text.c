#include "global.h"
#include "battle.h"
#include "blit.h"
#include "dynamic_placeholder_text_util.h"
#include "event_data.h"
#include "field_name_box.h"
#include "fonts.h"
#include "m4a.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "palette.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "text.h"
#include "window.h"
#include "constants/songs.h"
#include "constants/speaker_names.h"

static u16 RenderText(struct TextPrinter *);
static u32 RenderFont(struct TextPrinter *);
static u16 FontFunc_Small(struct TextPrinter *);
static u16 FontFunc_Normal(struct TextPrinter *);
static u16 FontFunc_Short(struct TextPrinter *);
static u16 FontFunc_ShortCopy1(struct TextPrinter *);
static u16 FontFunc_ShortCopy2(struct TextPrinter *);
static u16 FontFunc_ShortCopy3(struct TextPrinter *);
static u16 FontFunc_Narrow(struct TextPrinter *);
static u16 FontFunc_SmallNarrow(struct TextPrinter *);
static u16 FontFunc_Narrower(struct TextPrinter *);
static u16 FontFunc_SmallNarrower(struct TextPrinter *);
static u16 FontFunc_ShortNarrow(struct TextPrinter *);
static u16 FontFunc_ShortNarrower(struct TextPrinter *);
static void DecompressGlyph_Small(u16, bool32);
static void DecompressGlyph_Normal(u16, bool32);
static void DecompressGlyph_Short(u16, bool32);
static void DecompressGlyph_Narrow(u16, bool32);
static void DecompressGlyph_SmallNarrow(u16, bool32);
static void DecompressGlyph_Bold(u16);
static void DecompressGlyph_Narrower(u16, bool32);
static void DecompressGlyph_SmallNarrower(u16, bool32);
static void DecompressGlyph_ShortNarrow(u16, bool32);
static void DecompressGlyph_ShortNarrower(u16, bool32);
static u32 GetGlyphWidth_Small(u16, bool32);
static u32 GetGlyphWidth_Normal(u16, bool32);
static u32 GetGlyphWidth_Short(u16, bool32);
static u32 GetGlyphWidth_Narrow(u16, bool32);
static u32 GetGlyphWidth_SmallNarrow(u16, bool32);
static u32 GetGlyphWidth_Narrower(u16, bool32);
static u32 GetGlyphWidth_SmallNarrower(u16, bool32);
static u32 GetGlyphWidth_ShortNarrow(u16, bool32);
static u32 GetGlyphWidth_ShortNarrower(u16, bool32);
static struct TextPrinter *AllocateTextPrinter(void);
static u32 GetNumTextPrinters(void);
static void FreeFinishedTextPrinters(void);
static void SpriteCB_TextCursor(struct Sprite *sprite);
#if TEXT_RTL
static EWRAM_DATA u8 sRtlVisualBuffer[160] = {0};
static bool32 RtlReorderToVisual(const u8 *str, u8 *dest, u32 destSize, union TextColor color);
#endif

static EWRAM_DATA struct TextPrinter *sFirstTextPrinter = NULL;

static EWRAM_DATA u16 sFontHalfRowLookupTable[0x100];
static EWRAM_DATA union TextColor sLastTextColor;

EWRAM_DATA const struct FontInfo *gFonts = NULL;
EWRAM_DATA bool8 gDisableTextPrinters = 0;
EWRAM_DATA TextFlags gTextFlags = {0};
IWRAM_DATA struct TextGlyph gCurGlyph = {0};

static const u8 sDownArrowTiles[] = INCBIN_U8("graphics/fonts/down_arrow.4bpp");
static const u8 sDarkDownArrowTiles[] = INCBIN_U8("graphics/fonts/down_arrow_alt.4bpp");
static const u8 sUnusedFRLGBlankedDownArrow[] = INCBIN_U8("graphics/fonts/unused_frlg_blanked_down_arrow.4bpp");
static const u8 sUnusedFRLGDownArrow[] = INCBIN_U8("graphics/fonts/unused_frlg_down_arrow.4bpp");
static const u8 sDownArrowYCoords[] = { 0, 1, 2, 1 };

static const struct GlyphWidthFunc sGlyphWidthFuncs[] =
{
    { FONT_SMALL,          GetGlyphWidth_Small },
    { FONT_NORMAL,         GetGlyphWidth_Normal },
    { FONT_SHORT,          GetGlyphWidth_Short },
    { FONT_SHORT_COPY_1,   GetGlyphWidth_Short },
    { FONT_SHORT_COPY_2,   GetGlyphWidth_Short },
    { FONT_SHORT_COPY_3,   GetGlyphWidth_Short },
    { FONT_BRAILLE,        GetGlyphWidth_Braille },
    { FONT_NARROW,         GetGlyphWidth_Narrow },
    { FONT_SMALL_NARROW,   GetGlyphWidth_SmallNarrow },
    { FONT_NARROWER,       GetGlyphWidth_Narrower },
    { FONT_SMALL_NARROWER, GetGlyphWidth_SmallNarrower },
    { FONT_SHORT_NARROW,   GetGlyphWidth_ShortNarrow },
    { FONT_SHORT_NARROWER, GetGlyphWidth_ShortNarrower },
};

struct
{
    u16 tileOffset;
    u8 width;
    u8 height;
} static const sKeypadIcons[] =
{
    [CHAR_A_BUTTON]       = { 0x00,  8, 12 },
    [CHAR_B_BUTTON]       = { 0x01,  8, 12 },
    [CHAR_L_BUTTON]       = { 0x02, 16, 12 },
    [CHAR_R_BUTTON]       = { 0x04, 16, 12 },
    [CHAR_START_BUTTON]   = { 0x06, 24, 12 },
    [CHAR_SELECT_BUTTON]  = { 0x09, 24, 12 },
    [CHAR_DPAD_UP]        = { 0x0C,  8, 12 },
    [CHAR_DPAD_DOWN]      = { 0x0D,  8, 12 },
    [CHAR_DPAD_LEFT]      = { 0x0E,  8, 12 },
    [CHAR_DPAD_RIGHT]     = { 0x0F,  8, 12 },
    [CHAR_DPAD_UPDOWN]    = { 0x20,  8, 12 },
    [CHAR_DPAD_LEFTRIGHT] = { 0x21,  8, 12 },
    [CHAR_DPAD_NONE]      = { 0x22,  8, 12 }
};

static const u8 sKeypadIconTiles[] = INCBIN_U8("graphics/fonts/keypad_icons.4bpp");

static const struct FontInfo sFontInfos[] =
{
    [FONT_SMALL] = {
        .fontFunction = FontFunc_Small,
        .maxLetterWidth = 5,
        .maxLetterHeight = 12,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .color.foreground = 2,
        .color.background = 1,
        .color.accent = 1,
        .color.shadow = 3,
    },
    [FONT_NORMAL] = {
        .fontFunction = FontFunc_Normal,
        .maxLetterWidth = 6,
        .maxLetterHeight = 16,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .color.foreground = 2,
        .color.background = 1,
        .color.accent = 1,
        .color.shadow = 3,
    },
    [FONT_SHORT] = {
        .fontFunction = FontFunc_Short,
        .maxLetterWidth = 6,
        .maxLetterHeight = 14,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .color.foreground = 2,
        .color.background = 1,
        .color.accent = 1,
        .color.shadow = 3,
    },
    [FONT_SHORT_COPY_1] = {
        .fontFunction = FontFunc_ShortCopy1,
        .maxLetterWidth = 6,
        .maxLetterHeight =  14,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .color.foreground = 2,
        .color.background = 1,
        .color.accent = 1,
        .color.shadow = 3,
    },
    [FONT_SHORT_COPY_2] = {
        .fontFunction = FontFunc_ShortCopy2,
        .maxLetterWidth = 6,
        .maxLetterHeight =  14,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .color.foreground = 2,
        .color.background = 1,
        .color.accent = 1,
        .color.shadow = 3,
    },
    [FONT_SHORT_COPY_3] = {
        .fontFunction = FontFunc_ShortCopy3,
        .maxLetterWidth = 6,
        .maxLetterHeight =  14,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .color.foreground = 2,
        .color.background = 1,
        .color.accent = 1,
        .color.shadow = 3,
    },
    [FONT_BRAILLE] = {
        .fontFunction = FontFunc_Braille,
        .maxLetterWidth = 8,
        .maxLetterHeight = 16,
        .letterSpacing = 0,
        .lineSpacing = 8,
        .color.foreground = 2,
        .color.background = 1,
        .color.accent = 1,
        .color.shadow = 3,
    },
    [FONT_NARROW] = {
        .fontFunction = FontFunc_Narrow,
        .maxLetterWidth = 5,
        .maxLetterHeight = 16,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .color.foreground = 2,
        .color.background = 1,
        .color.accent = 1,
        .color.shadow = 3,
    },
    [FONT_SMALL_NARROW] = {
        .fontFunction = FontFunc_SmallNarrow,
        .maxLetterWidth = 5,
        .maxLetterHeight = 8,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .color.foreground = 2,
        .color.background = 1,
        .color.accent = 1,
        .color.shadow = 3,
    },
    [FONT_BOLD] = {
        .fontFunction = NULL,
        .maxLetterWidth = 8,
        .maxLetterHeight = 8,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .color.foreground = 1,
        .color.background = 2,
        .color.accent = 2,
        .color.shadow = 15,
    },
    [FONT_NARROWER] = {
        .fontFunction = FontFunc_Narrower,
        .maxLetterWidth = 5,
        .maxLetterHeight = 16,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .color.foreground = 2,
        .color.background = 1,
        .color.accent = 1,
        .color.shadow = 3,
    },
    [FONT_SMALL_NARROWER] = {
        .fontFunction = FontFunc_SmallNarrower,
        .maxLetterWidth = 5,
        .maxLetterHeight = 8,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .color.foreground = 2,
        .color.background = 1,
        .color.accent = 1,
        .color.shadow = 3,
    },
    [FONT_SHORT_NARROW] = {
        .fontFunction = FontFunc_ShortNarrow,
        .maxLetterWidth = 5,
        .maxLetterHeight = 14,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .color.foreground = 2,
        .color.background = 1,
        .color.accent = 1,
        .color.shadow = 3,
    },
    [FONT_SHORT_NARROWER] = {
        .fontFunction = FontFunc_ShortNarrower,
        .maxLetterWidth = 5,
        .maxLetterHeight = 14,
        .letterSpacing = 0,
        .lineSpacing = 0,
        .color.foreground = 2,
        .color.background = 1,
        .color.accent = 1,
        .color.shadow = 3,
    },
};

static const u8 sMenuCursorDimensions[][2] =
{
    [FONT_SMALL]          = { 8,  12 },
    [FONT_NORMAL]         = { 8,  15 },
    [FONT_SHORT]          = { 8,  14 },
    [FONT_SHORT_COPY_1]   = { 8,  14 },
    [FONT_SHORT_COPY_2]   = { 8,  14 },
    [FONT_SHORT_COPY_3]   = { 8,  14 },
    [FONT_BRAILLE]        = { 8,  16 },
    [FONT_NARROW]         = { 8,  15 },
    [FONT_SMALL_NARROW]   = { 8,   8 },
    [FONT_BOLD]           = {},
    [FONT_NARROWER]       = { 8,  15 },
    [FONT_SMALL_NARROWER] = { 8,   8 },
    [FONT_SHORT_NARROW]   = { 8,  14 },
    [FONT_SHORT_NARROWER] = { 8,  14 },
};

// these three arrays are most for readability, ie instead of returning a magic number 8
static const u8 sTextSpeedFrameDelays[] =
{
    [OPTIONS_TEXT_SPEED_SLOW]    = 8,
    [OPTIONS_TEXT_SPEED_MID]     = 4,
    [OPTIONS_TEXT_SPEED_FAST]    = 1,
    [OPTIONS_TEXT_SPEED_INSTANT] = 1,
};

static const u8 sTextSpeedModifiers[] =
{
    [OPTIONS_TEXT_SPEED_SLOW]    = TEXT_SPEED_SLOW_MODIFIER,
    [OPTIONS_TEXT_SPEED_MID]     = TEXT_SPEED_MEDIUM_MODIFIER,
    [OPTIONS_TEXT_SPEED_FAST]    = TEXT_SPEED_FAST_MODIFIER,
    [OPTIONS_TEXT_SPEED_INSTANT] = TEXT_SPEED_INSTANT_MODIFIER,
};

static const u8 sTextScrollSpeeds[] =
{
    [OPTIONS_TEXT_SPEED_SLOW]    = 1,
    [OPTIONS_TEXT_SPEED_MID]     = 2,
    [OPTIONS_TEXT_SPEED_FAST]    = 4,
    [OPTIONS_TEXT_SPEED_INSTANT] = 6,
};

static const u16 sFontBoldJapaneseGlyphs[] = INCBIN_U16("graphics/fonts/bold.hwjpnfont");

static void SetFontsPointer(const struct FontInfo *fonts)
{
    gFonts = fonts;
}

u32 GetPlayerTextSpeed(void)
{
    if (gTextFlags.forceMidTextSpeed)
        return OPTIONS_TEXT_SPEED_MID;

    if (gSaveBlock2Ptr->optionsTextSpeed > OPTIONS_TEXT_SPEED_INSTANT)
        gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_FAST;

    if (FlagGet(FLAG_TEXT_SPEED_INSTANT) || TEXT_SPEED_INSTANT)
        return OPTIONS_TEXT_SPEED_INSTANT;

    return gSaveBlock2Ptr->optionsTextSpeed;
}

u32 GetPlayerTextSpeedDelay(void)
{
    return sTextSpeedFrameDelays[GetPlayerTextSpeed()];
}

u32 GetPlayerTextSpeedModifier(void)
{
    return sTextSpeedModifiers[GetPlayerTextSpeed()];
}

u32 GetPlayerTextScrollSpeed(void)
{
    return sTextScrollSpeeds[GetPlayerTextSpeed()];
}

bool32 IsPlayerTextSpeedInstant(void)
{
    return GetPlayerTextSpeed() == OPTIONS_TEXT_SPEED_INSTANT;
}

void DeactivateAllTextPrinters(void)
{
    struct TextPrinter *currentPrinter = sFirstTextPrinter;
    while (currentPrinter != NULL)
    {
        currentPrinter->isInUse = FALSE;
        currentPrinter = currentPrinter->nextPrinter;
    }

    FreeFinishedTextPrinters();
}

u16 AddTextPrinterParameterized(u8 windowId, u8 fontId, const u8 *str, u8 x, u8 y, u8 speed, void (*callback)(struct TextPrinterTemplate *, u16))
{
    struct TextPrinterTemplate printerTemplate;

    printerTemplate.currentChar = str;
    printerTemplate.type = WINDOW_TEXT_PRINTER;
    printerTemplate.windowId = windowId;
    printerTemplate.fontId = fontId;
    printerTemplate.x = x;
    printerTemplate.y = y;
    printerTemplate.currentX = x;
    printerTemplate.currentY = y;
    printerTemplate.letterSpacing = gFonts[fontId].letterSpacing;
    printerTemplate.lineSpacing = gFonts[fontId].lineSpacing;
    printerTemplate.color = gFonts[fontId].color;
    return AddTextPrinter(&printerTemplate, speed, callback);
}

u16 AddSpriteTextPrinterParametrerized(u8 spriteId, u8 fontId, const u8 *str, u8 x, u8 y, u8 speed, void (*callback)(struct TextPrinterTemplate *, u16))
{
    struct TextPrinterTemplate printerTemplate;

    printerTemplate.currentChar = str;
    printerTemplate.type = SPRITE_TEXT_PRINTER;
    printerTemplate.spriteId = spriteId;
    printerTemplate.fontId = fontId;
    printerTemplate.x = x;
    printerTemplate.y = y;
    printerTemplate.currentX = x;
    printerTemplate.currentY = y;
    printerTemplate.letterSpacing = gFonts[fontId].letterSpacing;
    printerTemplate.lineSpacing = gFonts[fontId].lineSpacing;
    printerTemplate.color = gFonts[fontId].color;
    return AddTextPrinter(&printerTemplate, speed, callback);
}

void AddSpriteTextPrinterParameterized3(u8 spriteId, u8 fontId, u8 left, u8 top, const u8 *color, s8 speed, const u8 *str)
{
    struct TextPrinterTemplate printer;

    printer.currentChar = str;
    printer.type = SPRITE_TEXT_PRINTER;
    printer.spriteId = spriteId;
    printer.fontId = fontId;
    printer.x = left;
    printer.y = top;
    printer.currentX = printer.x;
    printer.currentY = printer.y;
    printer.letterSpacing = GetFontAttribute(fontId, FONTATTR_LETTER_SPACING);
    printer.lineSpacing = GetFontAttribute(fontId, FONTATTR_LINE_SPACING);
    printer.color.background = color[0];
    printer.color.foreground = color[1];
    printer.color.shadow = color[2];
    printer.color.accent = color[0];

    AddTextPrinter(&printer, speed, NULL);
}

void AddSpriteTextPrinterParameterized4(u8 spriteId, u8 fontId, u8 left, u8 top, u8 letterSpacing, u8 lineSpacing, const u8 *color, s8 speed, const u8 *str)
{
    struct TextPrinterTemplate printer;

    printer.currentChar = str;
    printer.type = SPRITE_TEXT_PRINTER;
    printer.spriteId = spriteId;
    printer.fontId = fontId;
    printer.x = left;
    printer.y = top;
    printer.currentX = printer.x;
    printer.currentY = printer.y;
    printer.letterSpacing = letterSpacing;
    printer.lineSpacing = lineSpacing;
    printer.color.background = color[0];
    printer.color.foreground = color[1];
    printer.color.shadow = color[2];
    printer.color.accent = color[0];

    AddTextPrinter(&printer, speed, NULL);
}

void AddSpriteTextPrinterParameterized6(u8 spriteId, u8 fontId, u8 left, u8 top, u8 letterSpacing, u8 lineSpacing, const union TextColor color, s8 speed, const u8 *str)
{
    struct TextPrinterTemplate printer;

    printer.currentChar = str;
    printer.type = SPRITE_TEXT_PRINTER;
    printer.spriteId = spriteId;
    printer.fontId = fontId;
    printer.x = left;
    printer.y = top;
    printer.currentX = printer.x;
    printer.currentY = printer.y;
    printer.letterSpacing = letterSpacing;
    printer.lineSpacing = lineSpacing;
    printer.color = color;

    AddTextPrinter(&printer, speed, NULL);
}

bool32 AddTextPrinter(struct TextPrinterTemplate *printerTemplate, u8 speed, void (*callback)(struct TextPrinterTemplate *, u16))
{
    if (!gFonts)
        return FALSE;

    struct TextPrinter sTempTextPrinter = {0};

    sTempTextPrinter.active = TRUE;
    sTempTextPrinter.state = RENDER_STATE_HANDLE_CHAR;
    sTempTextPrinter.printerTemplate = *printerTemplate;
    sTempTextPrinter.callback = callback;
    sTempTextPrinter.textSpeed = speed;

#if TEXT_RTL
    if (printerTemplate->type == WINDOW_TEXT_PRINTER)
    {
        sTempTextPrinter.rtlMode = GetWindowRtlMode(printerTemplate->windowId);
        sTempTextPrinter.rtlAxis = GetWindowRtlMirrorWidth(printerTemplate->windowId);
        sTempTextPrinter.rtlNeedAxis = TRUE;
    }
    // Sprite text (the healthbox) keeps its English position: reorder the string into visual order
    // and print it left to right. Only immediate printers can do this, since the reordered copy
    // lives in one shared buffer.
    else if ((speed == 0 || speed == TEXT_SKIP_DRAW)
     && RtlReorderToVisual(printerTemplate->currentChar, sRtlVisualBuffer, sizeof(sRtlVisualBuffer), printerTemplate->color))
    {
        sTempTextPrinter.printerTemplate.currentChar = sRtlVisualBuffer;
        sTempTextPrinter.rtlVisualOrder = TRUE;
    }
#endif

    if (printerTemplate->type == SPRITE_TEXT_PRINTER)
    {
        sTempTextPrinter.printerTemplate.firstSprite = printerTemplate->spriteId;
        sTempTextPrinter.printerTemplate.firstSpriteInRow = printerTemplate->spriteId;
    }


    GenerateFontHalfRowLookupTable(printerTemplate->color);
    if (speed != TEXT_SKIP_DRAW && speed != 0)
    {
        --sTempTextPrinter.textSpeed;
        sTempTextPrinter.isInUse = TRUE;
        struct TextPrinter *printer = AllocateTextPrinter();
        if (printer != NULL)
        {
            *printer = sTempTextPrinter;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        sTempTextPrinter.textSpeed = 0;

        // Render all text (up to limit) at once
        for (u32 j = 0; j < 0x400; ++j)
        {
            if (RenderFont(&sTempTextPrinter) == RENDER_FINISH)
                break;
        }

        // All the text is rendered but don't draw it yet.
        if (speed != TEXT_SKIP_DRAW)
        {
            switch (sTempTextPrinter.printerTemplate.type)
            {
            case WINDOW_TEXT_PRINTER:
                CopyWindowToVram(sTempTextPrinter.printerTemplate.windowId, COPYWIN_GFX);
                break;
            case SPRITE_TEXT_PRINTER:
                break;
            }
        }
    }
    gDisableTextPrinters = FALSE;
    return TRUE;
}

void RunTextPrinters(void)
{
    bool32 isInstantText = IsPlayerTextSpeedInstant();
    u32 textRepeats = GetPlayerTextSpeedModifier();

    if (gDisableTextPrinters)
        return;

    u32 numPrinters = GetNumTextPrinters();

    struct TextPrinter *currentPrinter = sFirstTextPrinter;

    do
    {
        u32 numEmpty = 0;
        while (currentPrinter != NULL)
        {
            if (currentPrinter->active)
            {
                for (u32 repeat = 0; repeat < textRepeats || isInstantText; repeat++)
                {
                    u32 renderState = RenderFont(currentPrinter);
                    switch (renderState)
                    {
                    case RENDER_PRINT:
                        switch (currentPrinter->printerTemplate.type)
                        {
                        case WINDOW_TEXT_PRINTER:
                            CopyWindowToVram(currentPrinter->printerTemplate.windowId, COPYWIN_GFX);
                            break;
                        case SPRITE_TEXT_PRINTER:
                            break;
                        }
                        break;
                    case RENDER_UPDATE:
                        if (currentPrinter->callback != NULL)
                            currentPrinter->callback(&currentPrinter->printerTemplate, renderState);
                        isInstantText = FALSE;
                        break;
                    case RENDER_FINISH:
                        currentPrinter->active = FALSE;
                        currentPrinter->isInUse = FALSE;
                        isInstantText = FALSE;
                        break;
                    }

                    if (!currentPrinter->active)
                        break;
                }
            }
            else
            {
                numEmpty++;
            }
            currentPrinter = currentPrinter->nextPrinter;
        }

        if (numEmpty == numPrinters)
        {
            FreeFinishedTextPrinters();
            return;
        }
    } while (isInstantText);
    FreeFinishedTextPrinters();
}

bool32 IsTextPrinterActiveOnWindow(u32 windowId)
{
    struct TextPrinter *currentPrinter = sFirstTextPrinter;

    while (currentPrinter != NULL)
    {
        if (currentPrinter->printerTemplate.type == WINDOW_TEXT_PRINTER
         && currentPrinter->printerTemplate.windowId == windowId)
        {
            return currentPrinter->active;
        }
        currentPrinter = currentPrinter->nextPrinter;
    }

    return FALSE;
}

bool32 IsTextPrinterActiveOnSprite(u32 spriteId)
{
    struct TextPrinter *currentPrinter = sFirstTextPrinter;

    while (currentPrinter != NULL)
    {
        if (currentPrinter->printerTemplate.type == SPRITE_TEXT_PRINTER
         && currentPrinter->printerTemplate.firstSprite == spriteId)
        {
            return currentPrinter->active;
        }
        currentPrinter = currentPrinter->nextPrinter;
    }

    return FALSE;
}

static u32 RenderFont(struct TextPrinter *textPrinter)
{
    u32 ret;
    u16 (*fontFunction)(struct TextPrinter *x) = gFonts[textPrinter->printerTemplate.fontId].fontFunction;

    do
    {
        ret = fontFunction(textPrinter);
    } while (ret == RENDER_REPEAT);

    return ret;
}

void GenerateFontHalfRowLookupTable(union TextColor color)
{
    if (color.asU32 == sLastTextColor.asU32)
    {
        return;
    }

    sLastTextColor = color;

    u8 quarterRows[16] = {
        color.background << 4 | color.background,
        color.foreground << 4 | color.background,
        color.shadow << 4     | color.background,
        color.accent << 4     | color.background,
        color.background << 4 | color.foreground,
        color.foreground << 4 | color.foreground,
        color.shadow << 4     | color.foreground,
        color.accent << 4     | color.foreground,
        color.background << 4 | color.shadow,
        color.foreground << 4 | color.shadow,
        color.shadow << 4     | color.shadow,
        color.accent << 4     | color.shadow,
        color.background << 4 | color.accent,
        color.foreground << 4 | color.accent,
        color.shadow << 4     | color.accent,
        color.accent << 4     | color.accent,
    };

    u8 *current = (u8 *)sFontHalfRowLookupTable;

    for (u32 i = 0; i < 16; i++)
    {
        for (u32 j = 0; j < 16; j++)
        {
            *(current++) = quarterRows[i];
            *(current++) = quarterRows[j];
        }
    }
}

union TextColor SaveTextColors(void)
{
    return sLastTextColor;
}

void RestoreTextColors(union TextColor color)
{
    GenerateFontHalfRowLookupTable(color);
}

void DecompressGlyphTile(const void *src_, void *dest_)
{
    u32 temp;
    const u16 *src = src_;
    u32 *dest = dest_;

    temp = *(src++);
    *(dest++) = (sFontHalfRowLookupTable[temp & 0xFF] << 16) | (sFontHalfRowLookupTable[temp >> 8]);

    temp = *(src++);
    *(dest++) = (sFontHalfRowLookupTable[temp & 0xFF] << 16) | (sFontHalfRowLookupTable[temp >> 8]);

    temp = *(src++);
    *(dest++) = (sFontHalfRowLookupTable[temp & 0xFF] << 16) | (sFontHalfRowLookupTable[temp >> 8]);

    temp = *(src++);
    *(dest++) = (sFontHalfRowLookupTable[temp & 0xFF] << 16) | (sFontHalfRowLookupTable[temp >> 8]);

    temp = *(src++);
    *(dest++) = (sFontHalfRowLookupTable[temp & 0xFF] << 16) | (sFontHalfRowLookupTable[temp >> 8]);

    temp = *(src++);
    *(dest++) = (sFontHalfRowLookupTable[temp & 0xFF] << 16) | (sFontHalfRowLookupTable[temp >> 8]);

    temp = *(src++);
    *(dest++) = (sFontHalfRowLookupTable[temp & 0xFF] << 16) | (sFontHalfRowLookupTable[temp >> 8]);

    temp = *(src++);
    *(dest++) = (sFontHalfRowLookupTable[temp & 0xFF] << 16) | (sFontHalfRowLookupTable[temp >> 8]);
}

static u8 UNUSED GetLastTextColor(enum TextColorType colorType)
{
    switch (colorType)
    {
    case TEXT_COLOR_TYPE_FOREGROUND:
        return sLastTextColor.foreground;
    case TEXT_COLOR_TYPE_HIGHLIGHT:
    case TEXT_COLOR_TYPE_BACKGROUND:
        return sLastTextColor.background;
    case TEXT_COLOR_TYPE_SHADOW:
        return sLastTextColor.shadow;
    case TEXT_COLOR_TYPE_ACCENT:
        return sLastTextColor.accent;
    default:
        return TEXT_COLOR_TRANSPARENT;
    }
}

static u32 OffsetCurrGlyph(u32 shiftWidth)
{
    u32 newWidth = gCurGlyph.width - shiftWidth;

    if (gCurGlyph.width <= 8)
    {
        for (u32 i = 0; i < 8; i++)
        {
            gCurGlyph.gfxBufferTop[i] = gCurGlyph.gfxBufferTop[i] >> (4 * shiftWidth);
            gCurGlyph.gfxBufferBottom[i] = gCurGlyph.gfxBufferBottom[i] >> (4 * shiftWidth);
        }
    }
    else
    {
        //  Do cursed u64 handling of double wide glyphs
        for (u32 i = 0; i < 8; i++)
        {
            u64 tempVal = gCurGlyph.gfxBufferTop[8 + i];
            u64 topVal = (tempVal << 32) | gCurGlyph.gfxBufferTop[i];
            tempVal = gCurGlyph.gfxBufferBottom[8 + i];
            u64 bottomVal = (tempVal << 32) | gCurGlyph.gfxBufferBottom[i];
            topVal = topVal >> (4 * shiftWidth);
            bottomVal = bottomVal >> (4 * shiftWidth);

            gCurGlyph.gfxBufferTop[i] = topVal & 0xFFFFFFFF;
            gCurGlyph.gfxBufferTop[8 + i] = topVal >> 32;

            gCurGlyph.gfxBufferBottom[i] = bottomVal & 0xFFFFFFFF;
            gCurGlyph.gfxBufferBottom[8 + i] = bottomVal >> 32;
        }
    }

    gCurGlyph.width = newWidth;
    return newWidth;
}

inline static void GLYPH_COPY(u8 *windowTiles, u32 widthOffset, u32 x0, u32 y0, u32 *glyphPixels, s32 width, s32 height)
{
    if (width <= 0)
        return;

    u32 widthMask = (1 << (width * 4)) - 1;

    u32 shift0 = (x0 % 8) * 4, shift8 = 32 - shift0;

    u32 *alignedWindowTilesX = (u32 *)(windowTiles + ((x0 / 8) * TILE_SIZE_4BPP));

    u32 y1 = y0 + height;
    for (u32 y = y0; y < y1; y++)
    {
        u32 pixels = *glyphPixels++ & widthMask;

        u32 mask = pixels;
        mask = mask | (mask >> 2);
        mask = mask | (mask >> 1);
        mask = mask & 0x11111111;
        mask = mask * 0xF;

        u32 pixels0 = pixels << shift0, pixels8 = pixels >> shift8;
        u32 mask0 = mask << shift0, mask8 = mask >> shift8;

        u32 *alignedWindowTiles = (u32 *)((u8 *)alignedWindowTilesX + ((y / 8) * widthOffset) + ((y % 8) * 4));

        alignedWindowTiles[0] = (alignedWindowTiles[0] & ~mask0) | pixels0;
        alignedWindowTiles[8] = (alignedWindowTiles[8] & ~mask8) | pixels8;
    }
}

u32 CopyGlyphToVRAM(struct TextPrinter *textPrinter)
{
    u32 *glyphPixels;
    u32 currX, currY, widthOffset;
    s32 glyphWidth, glyphHeight;

    struct Window *window;
    struct WindowTemplate *template;
    u8 *destTiles;

    struct Sprite *sprite;

    bool32 wasCutOff = FALSE;

    currX = textPrinter->printerTemplate.currentX;
    currY = textPrinter->printerTemplate.currentY;
    glyphPixels = gCurGlyph.gfxBufferTop;

    switch (textPrinter->printerTemplate.type)
    {
    case WINDOW_TEXT_PRINTER:
        window = &gWindows[textPrinter->printerTemplate.windowId];
        template = &window->window;

        if ((glyphWidth = (template->width * 8) - textPrinter->printerTemplate.currentX) > gCurGlyph.width)
            glyphWidth = gCurGlyph.width;

        if ((glyphHeight = (template->height * 8) - textPrinter->printerTemplate.currentY) > gCurGlyph.height)
            glyphHeight = gCurGlyph.height;
        destTiles = window->tileData;
        widthOffset = template->width * 32;
        break;
    case SPRITE_TEXT_PRINTER:
        sprite = &gSprites[textPrinter->printerTemplate.spriteId];
        destTiles = (void*)(OBJ_VRAM0) + sprite->oam.tileNum * TILE_SIZE_4BPP;

        if ((glyphWidth = GetSpriteWidth(sprite) - textPrinter->printerTemplate.currentX) > gCurGlyph.width)
            glyphWidth = gCurGlyph.width;
        else
            wasCutOff = TRUE;

        if ((glyphHeight = GetSpriteHeight(sprite) - textPrinter->printerTemplate.currentY) > gCurGlyph.height)
            glyphHeight = gCurGlyph.height;

        widthOffset = GetSpriteWidth(sprite) * 4;
        break;
    default:
        errorf("Illegal printer type");
        return 0;
    }

    if (glyphWidth < 9)
    {
        if (glyphHeight < 9)
        {
            GLYPH_COPY(destTiles, widthOffset, currX, currY, glyphPixels, glyphWidth, glyphHeight);
        }
        else
        {
            GLYPH_COPY(destTiles, widthOffset, currX, currY, glyphPixels, glyphWidth, 8);
            GLYPH_COPY(destTiles, widthOffset, currX, currY + 8, glyphPixels + 16, glyphWidth, glyphHeight - 8);
        }
    }
    else
    {
        if (glyphHeight < 9)
        {
            GLYPH_COPY(destTiles, widthOffset, currX, currY, glyphPixels, 8, glyphHeight);
            GLYPH_COPY(destTiles, widthOffset, currX + 8, currY, glyphPixels + 8, glyphWidth - 8, glyphHeight);
        }
        else
        {
            GLYPH_COPY(destTiles, widthOffset, currX, currY, glyphPixels, 8, 8);
            GLYPH_COPY(destTiles, widthOffset, currX + 8, currY, glyphPixels + 8, glyphWidth - 8, 8);
            GLYPH_COPY(destTiles, widthOffset, currX, currY + 8, glyphPixels + 16, 8, glyphHeight - 8);
            GLYPH_COPY(destTiles, widthOffset, currX + 8, currY + 8, glyphPixels + 24, glyphWidth - 8, glyphHeight - 8);
        }
    }

    //  Handle Y cutoff
    if (textPrinter->printerTemplate.type == SPRITE_TEXT_PRINTER
     && glyphHeight != gCurGlyph.height)
    {
        sprite = &gSprites[gSprites[textPrinter->printerTemplate.spriteId].data[2]];
        destTiles = (void*)(OBJ_VRAM0) + sprite->oam.tileNum * TILE_SIZE_4BPP;

        u32 newHeight = gCurGlyph.height - glyphHeight;

        u32 leftHalf[16];
        u32 rightHalf[16];

        if (gCurGlyph.width > 8)
        {
            for (u32 i = 0; i < 8; i++)
            {
                leftHalf[i] = gCurGlyph.gfxBufferTop[i];
                leftHalf[8 + i] = gCurGlyph.gfxBufferBottom[i];
                rightHalf[i] = gCurGlyph.gfxBufferTop[8 + i];
                rightHalf[8 + i] = gCurGlyph.gfxBufferBottom[8 + i];
            }

            for (u32 i = 0; i < newHeight; i++)
            {
                leftHalf[i] = leftHalf[glyphHeight + i];
                rightHalf[i] = rightHalf[glyphHeight + i];
            }
        }
        else
        {
            for (u32 i = 0; i < 8; i++)
            {
                leftHalf[i] = gCurGlyph.gfxBufferTop[i];
                leftHalf[8 + i] = gCurGlyph.gfxBufferBottom[i];
            }

            for (u32 i = 0; i < newHeight; i++)
                leftHalf[i] = leftHalf[glyphHeight + i];
        }

        glyphHeight = newHeight;

        if (glyphWidth < 9)
        {
            if (glyphHeight < 9)
            {
                GLYPH_COPY(destTiles, widthOffset, currX, 0, leftHalf, glyphWidth, glyphHeight);
            }
            else
            {
                GLYPH_COPY(destTiles, widthOffset, currX, 0, leftHalf, glyphWidth, 8);
                GLYPH_COPY(destTiles, widthOffset, currX, 8, &leftHalf[8], glyphWidth, glyphHeight - 8);
            }
        }
        else
        {
            if (glyphHeight < 9)
            {
                GLYPH_COPY(destTiles, widthOffset, currX, 0, leftHalf, 8, glyphHeight);
                GLYPH_COPY(destTiles, widthOffset, currX + 8, 0, rightHalf, glyphWidth - 8, glyphHeight);
            }
            else
            {
                GLYPH_COPY(destTiles, widthOffset, currX, 0, leftHalf, 8, 8);
                GLYPH_COPY(destTiles, widthOffset, currX + 8, 0, rightHalf, glyphWidth - 8, 8);
                GLYPH_COPY(destTiles, widthOffset, currX, 8, &leftHalf[8], 8, glyphHeight - 8);
                GLYPH_COPY(destTiles, widthOffset, currX + 8, 8, &rightHalf[8], glyphWidth - 8, glyphHeight - 8);
            }
        }
    }

    if (wasCutOff)
        return glyphWidth;

    return 0;
}

#if TEXT_RTL
// Right-to-left rendering.
//
// A window printer keeps upstream's logical pen: x, currentX, {CLEAR_TO}, {SKIP} and every layout
// computed from GetStringWidth mean exactly what they mean in English. Only the blit is mirrored,
// around an axis: a glyph at logical x, w pixels wide, is drawn at axis - x - w.
//
// - WINDOW_RTL_MIRROR (the default): the axis is the window's mirror width, so the whole window
//   comes out as the mirror image of its English layout. The window primitives in window.c
//   (fills, bitmap blits) mirror around the same axis, so cursors, icons and arrows move with the
//   text. A string that fits in English fits mirrored.
// - WINDOW_RTL_IN_PLACE: each segment of a line (up to a newline or a code that moves the pen,
//   such as {CLEAR_TO}) is mirrored inside its own English extent, so columns stay where the
//   English put them and only the reading order flips. For windows laid over fixed art.
// - WINDOW_RTL_LTR: untouched.
//
// A run of Latin letters or digits, with the punctuation between them, is measured when it starts
// and drawn left to right as one block at the run's mirrored position, so "32", "10:30" and "PP"
// are stored and read in their normal order. A {JPN}...{ENG} span (a name from a Japanese game)
// is placed as one such run too, in the Japanese font (RtlBeginJapanese).
//
// Sprite printers (the healthbox) print immediately; they reorder the string into visual order and
// print it left to right, which keeps their English position.

enum
{
    RTL_CLASS_NEUTRAL,    // Spaces and punctuation take the direction of their surroundings
    RTL_CLASS_RTL,        // Hebrew letters, and the Hebrew level glyph
    RTL_CLASS_LTR,        // Latin letters and Latin-only symbols
    RTL_CLASS_DIGIT,
    RTL_CLASS_NUM_PREFIX, // Starts a run when a digit follows: currency, plus, minus
    RTL_CLASS_NUM_SUFFIX, // Stays in a run when a digit precedes it: percent
    RTL_CLASS_CONTROL,    // Control bytes always end a run
};

static const u8 sRtlCharClass[0x100] =
{
    [CHAR_A_GRAVE ... CHAR_SUPER_ER]                = RTL_CLASS_LTR,
    [CHAR_PLUS]                                     = RTL_CLASS_NUM_PREFIX,
    [CHAR_LV]                                       = RTL_CLASS_RTL,
    [CHAR_HEB_ALEF ... CHAR_HEB_FINAL_KAF]          = RTL_CLASS_RTL,
    [CHAR_PK ... CHAR_I_ACUTE]                      = RTL_CLASS_LTR,
    [CHAR_PERCENT]                                  = RTL_CLASS_NUM_SUFFIX,
    [CHAR_HEB_FINAL_MEM ... CHAR_HEB_FINAL_TSADI]   = RTL_CLASS_RTL,
    [CHAR_a_CIRCUMFLEX]                             = RTL_CLASS_LTR,
    [CHAR_i_ACUTE]                                  = RTL_CLASS_LTR,
    [CHAR_SUPER_E]                                  = RTL_CLASS_LTR,
    [CHAR_SUPER_RE]                                 = RTL_CLASS_LTR,
    [CHAR_0 ... CHAR_9]                             = RTL_CLASS_DIGIT,
    [CHAR_HYPHEN]                                   = RTL_CLASS_NUM_PREFIX,
    [CHAR_CURRENCY]                                 = RTL_CLASS_NUM_PREFIX,
    [CHAR_A ... CHAR_z]                             = RTL_CLASS_LTR,
    [CHAR_A_DIAERESIS ... CHAR_u_DIAERESIS]         = RTL_CLASS_LTR,
    [CHAR_DYNAMIC ... EOS]                          = RTL_CLASS_CONTROL,
};

#define RTL_MAX_RUN_GLYPHS 127

#if RTL_CLIP_REPORT
// Read back by the harness between screens: every glyph that was drawn, or partly drawn, outside
// its window, with enough context to find the string and the printer that placed it.
struct RtlClipRecord
{
    const u8 *str;
    u8 windowId;
    u8 fontId;
    u8 x;
    u8 currentX;
    u8 windowWidth;
    u8 glyphWidth;
    s16 physX;
};
EWRAM_DATA struct RtlClipRecord gRtlClipLog[16] = {0};
EWRAM_DATA u32 gRtlClipCount = 0;

static void RtlReportClip(struct TextPrinter *textPrinter, s32 physX, u32 windowWidth)
{
    struct RtlClipRecord *record = &gRtlClipLog[gRtlClipCount % ARRAY_COUNT(gRtlClipLog)];
    gRtlClipCount++;
    record->str = textPrinter->printerTemplate.currentChar;
    record->windowId = textPrinter->printerTemplate.windowId;
    record->fontId = textPrinter->printerTemplate.fontId;
    record->x = textPrinter->printerTemplate.x;
    record->currentX = textPrinter->printerTemplate.currentX;
    record->windowWidth = windowWidth;
    record->glyphWidth = gCurGlyph.width;
    record->physX = physX;
}
#else
#define RtlReportClip(textPrinter, physX, windowWidth)
#endif

// Whether this printer's glyphs are placed right to left.
static bool32 RtlIsActive(const struct TextPrinter *textPrinter)
{
    return textPrinter->printerTemplate.type == WINDOW_TEXT_PRINTER
        && !textPrinter->japanese
        && !textPrinter->rtlVisualOrder
        && textPrinter->rtlMode != WINDOW_RTL_LTR
        && !textPrinter->rtlSegmentLtr;
}

static u32 RtlWindowWidth(const struct TextPrinter *textPrinter)
{
    return gWindows[textPrinter->printerTemplate.windowId].window.width * 8;
}

static u32 RtlClassAt(const u8 *str, u32 *length)
{
    if (str[0] == CHAR_EXTRA_SYMBOL)
    {
        *length = 2;
        switch (str[1])
        {
        case CHAR_LV_2:
            return RTL_CLASS_RTL;
        case CHAR_PP:
        case CHAR_ID:
            return RTL_CLASS_LTR;
        case CHAR_NO:
            // Not part of its number's run, so it stands on the number's right and is read
            // first, where Unicode puts it in right-to-left text: "01№" like the dex's "006№".
            return RTL_CLASS_NEUTRAL;
        default:
            return RTL_CLASS_NEUTRAL;
        }
    }
    *length = 1;
    return sRtlCharClass[str[0]];
}

// Whether a run of left-to-right text starts at str. afterRtl: the glyph before it is a Hebrew
// letter. A hyphen there is the Hebrew prefix hyphen ("ב-20", "by 20"), which stays with the
// letter before it, not a minus sign, so the number starts its own run after it.
static bool32 RtlStartsRun(const u8 *str, bool32 afterRtl)
{
    u32 length, nextLength;
    u32 class;

    if (str[0] == CHAR_KEYPAD_ICON)
        return TRUE;
    class = RtlClassAt(str, &length);
    if (class == RTL_CLASS_LTR || class == RTL_CLASS_DIGIT)
        return TRUE;
    if (afterRtl && str[0] == CHAR_HYPHEN)
        return FALSE;
    return class == RTL_CLASS_NUM_PREFIX && RtlClassAt(str + length, &nextLength) == RTL_CLASS_DIGIT;
}

// The one-letter Hebrew words that are written joined to the next word: ו "and", ה "the",
// ב "in", כ "as", ל "to", מ "from", ש "that".
static bool32 RtlIsPrefixLetter(u32 c)
{
    switch (c)
    {
    case CHAR_HEB_VAV:
    case CHAR_HEB_HE:
    case CHAR_HEB_BET:
    case CHAR_HEB_KAF:
    case CHAR_HEB_LAMED:
    case CHAR_HEB_MEM:
    case CHAR_HEB_SHIN:
        return TRUE;
    }
    return FALSE;
}

#define RTL_MAX_PREFIX_LETTERS 3

// A Hebrew prefix is joined to Latin letters and digits with a maqaf ("ל-PC", "ב-20") and to
// Hebrew directly, and the static text is written so. A placeholder is filled in only when the
// text is expanded, so the expanders ask this after each one, to write "ל-GOLD" but "לגולד":
// TRUE when the template has a prefix right before the placeholder (one to three prefix letters
// after a space, punctuation, a control code or the start of the template) and the placeholder's
// text, after any control codes, starts with a Latin letter or a digit. template: the string being
// expanded; placeholder: the placeholder's first byte in it; expansion: what the placeholder gave,
// EOS-terminated.
bool32 RtlNeedsPrefixMaqaf(const u8 *template, const u8 *placeholder, const u8 *expansion)
{
    u32 length, class;
    u32 letters = 0; // Prefix letters since the last word boundary; above the limit inside a word
    const u8 *str;

    while (*expansion == EXT_CTRL_CODE_BEGIN)
        expansion += 1 + GetExtCtrlCodeLength(expansion[1]);
    class = RtlClassAt(expansion, &length);
    if (class != RTL_CLASS_LTR && class != RTL_CLASS_DIGIT)
        return FALSE;

    for (str = template; str < placeholder; str += length)
    {
        switch (*str)
        {
        case EXT_CTRL_CODE_BEGIN:
            length = 1 + GetExtCtrlCodeLength(str[1]);
            letters = 0;
            continue;
        case PLACEHOLDER_BEGIN:
        case CHAR_DYNAMIC:
        case CHAR_KEYPAD_ICON:
            length = 2;
            letters = RTL_MAX_PREFIX_LETTERS + 1;
            continue;
        }
        class = RtlClassAt(str, &length);
        if (RtlIsPrefixLetter(*str))
            letters = (letters < RTL_MAX_PREFIX_LETTERS) ? letters + 1 : RTL_MAX_PREFIX_LETTERS + 1;
        else if (class == RTL_CLASS_RTL || class == RTL_CLASS_LTR || class == RTL_CLASS_DIGIT)
            letters = RTL_MAX_PREFIX_LETTERS + 1;
        else
            letters = 0;
    }
    return str == placeholder && letters != 0 && letters <= RTL_MAX_PREFIX_LETTERS;
}

// Length of a control code at str that can sit inside a run because it draws nothing and does not
// move the pen (colours, pauses, sounds, and placeholder bytes a window printer skips), or 0 for
// any code that ends a run.
static u32 RtlRunTransparentCodeLength(const u8 *str)
{
    if (str[0] == PLACEHOLDER_BEGIN)
        return 2;
    if (str[0] != EXT_CTRL_CODE_BEGIN)
        return 0;
    switch (str[1])
    {
    case EXT_CTRL_CODE_COLOR:
    case EXT_CTRL_CODE_HIGHLIGHT:
    case EXT_CTRL_CODE_SHADOW:
    case EXT_CTRL_CODE_PALETTE:
    case EXT_CTRL_CODE_ACCENT:
    case EXT_CTRL_CODE_BACKGROUND:
    case EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW:
    case EXT_CTRL_CODE_TEXT_COLORS:
    case EXT_CTRL_CODE_PAUSE:
    case EXT_CTRL_CODE_PAUSE_UNTIL_PRESS:
    case EXT_CTRL_CODE_WAIT_SE:
    case EXT_CTRL_CODE_PLAY_BGM:
    case EXT_CTRL_CODE_PLAY_SE:
    case EXT_CTRL_CODE_PAUSE_MUSIC:
    case EXT_CTRL_CODE_RESUME_MUSIC:
        return 1 + GetExtCtrlCodeLength(str[1]);
    default:
        return 0;
    }
}

static u32 (*GetFontWidthFunc(u8 fontId))(u16, bool32);

// The pen advance PrintGlyph will make for this glyph in this font.
static u32 RtlGlyphAdvance(const struct TextPrinter *textPrinter, u32 fontId, u16 glyphId)
{
    u32 (*widthFunc)(u16, bool32);

    if (textPrinter->minLetterSpacing)
        return textPrinter->minLetterSpacing;
    widthFunc = GetFontWidthFunc(fontId);
    if (widthFunc == NULL)
        return 0;
    return widthFunc(glyphId, FALSE);
}

// Measures the run that starts at str: everything up to the last Latin letter or digit before the
// next Hebrew letter or control code. Neutrals after that stay right-to-left. A button icon counts
// as a Latin letter, so "[L]/[R]" keeps its order, and a closing bracket whose opening bracket is
// in the run stays in it, so "AUTORUN (SURF)" keeps its brackets.
static void RtlBeginRun(struct TextPrinter *textPrinter, const u8 *str)
{
    u32 width = 0, glyphs = 0, runWidth = 0, runGlyphs = 0;
    u32 prevClass = RTL_CLASS_NEUTRAL;
    u32 openBrackets = 0;

    while (glyphs < RTL_MAX_RUN_GLYPHS)
    {
        u32 length, class, nextLength;
        bool32 strong;

        if (*str == EXT_CTRL_CODE_BEGIN || *str == PLACEHOLDER_BEGIN)
        {
            u32 codeLength = RtlRunTransparentCodeLength(str);
            if (codeLength == 0)
                break;
            str += codeLength;
            continue;
        }

        if (*str == CHAR_KEYPAD_ICON)
        {
            width += GetKeypadIconWidth(str[1]) + textPrinter->printerTemplate.letterSpacing;
            glyphs++;
            runWidth = width;
            runGlyphs = glyphs;
            prevClass = RTL_CLASS_LTR;
            str += 2;
            continue;
        }

        class = RtlClassAt(str, &length);
        if (class == RTL_CLASS_RTL || (class == RTL_CLASS_CONTROL && *str != CHAR_EXTRA_SYMBOL))
            break;

        width += RtlGlyphAdvance(textPrinter, textPrinter->fontId, length == 2 ? (str[1] | 0x100) : str[0]);
        glyphs++;

        strong = class == RTL_CLASS_LTR
              || class == RTL_CLASS_DIGIT
              || (class == RTL_CLASS_NUM_PREFIX && RtlClassAt(str + length, &nextLength) == RTL_CLASS_DIGIT)
              || (class == RTL_CLASS_NUM_SUFFIX && prevClass == RTL_CLASS_DIGIT);
        if (length == 1 && *str == CHAR_LEFT_PAREN)
        {
            openBrackets++;
        }
        else if (length == 1 && *str == CHAR_RIGHT_PAREN && openBrackets != 0)
        {
            openBrackets--;
            strong = TRUE;
        }
        if (strong)
        {
            runWidth = width;
            runGlyphs = glyphs;
        }
        prevClass = class;
        str += length;
    }

    textPrinter->rtlRunStart = textPrinter->printerTemplate.currentX;
    textPrinter->rtlRunWidth = min(runWidth, 255);
    textPrinter->rtlRunGlyphs = runGlyphs;
}

// Scans the Japanese glyphs from str up to {ENG} or a code that ends a run, and returns where they
// stop. *width is their width, each advancing the pen as PrintGlyph advances it in the Japanese
// font. Their bytes are kana, whatever the same bytes are in the Latin font.
static const u8 *RtlScanJapanese(const struct TextPrinter *textPrinter, u32 fontId, const u8 *str, u32 *width)
{
    *width = 0;
    while (TRUE)
    {
        u16 glyphId;

        if (str[0] == EXT_CTRL_CODE_BEGIN && str[1] == EXT_CTRL_CODE_ESCAPE)
        {
            glyphId = str[2] | 0x100;
            str += 3;
        }
        else if (*str == EXT_CTRL_CODE_BEGIN || *str == PLACEHOLDER_BEGIN)
        {
            u32 codeLength = RtlRunTransparentCodeLength(str);
            if (codeLength == 0)
                break;
            str += codeLength;
            continue;
        }
        else if (*str == CHAR_EXTRA_SYMBOL)
        {
            glyphId = str[1] | 0x100;
            str += 2;
        }
        else if (sRtlCharClass[*str] == RTL_CLASS_CONTROL)
        {
            break;
        }
        else
        {
            glyphId = *str++;
        }

        if (textPrinter->minLetterSpacing)
            *width += textPrinter->minLetterSpacing;
        else
            *width += GetGlyphWidth(glyphId, TRUE, fontId) + textPrinter->printerTemplate.letterSpacing;
    }
    return str;
}

// The width of the Japanese glyphs from str (RtlScanJapanese).
static NOINLINE u32 RtlJapaneseWidth(const struct TextPrinter *textPrinter, u32 fontId, const u8 *str)
{
    u32 width;

    RtlScanJapanese(textPrinter, fontId, str, &width);
    return width;
}

// Where the Japanese glyphs from str stop (RtlScanJapanese).
static NOINLINE const u8 *RtlJapaneseEnd(const struct TextPrinter *textPrinter, u32 fontId, const u8 *str)
{
    u32 width;

    return RtlScanJapanese(textPrinter, fontId, str, &width);
}

// In-place mode: the width of the segment that starts at str, up to a newline, the end, or a code
// that moves the pen, and whether it holds any Hebrew. Codes that only change colour, font, pace or
// sound do not end it. Inlined into both callers, so RtlPrepareGlyph, which runs for every glyph,
// keeps it inline.
static ALWAYS_INLINE u32 RtlMeasureSegment(const struct TextPrinter *textPrinter, const u8 *str, bool32 *hasRtl)
{
    u32 width = 0;
    u32 fontId = textPrinter->fontId;
    u32 length;

    *hasRtl = FALSE;

    while (TRUE)
    {
        switch (*str)
        {
        case EOS:
        case CHAR_NEWLINE:
        case CHAR_PROMPT_SCROLL:
        case CHAR_PROMPT_CLEAR:
        case PLACEHOLDER_BEGIN:
        case CHAR_DYNAMIC:
            return width;
        case CHAR_KEYPAD_ICON:
            width += GetKeypadIconWidth(str[1]);
            str += 2;
            continue;
        case CHAR_EXTRA_SYMBOL:
            if (RtlClassAt(str, &length) == RTL_CLASS_RTL)
                *hasRtl = TRUE;
            width += RtlGlyphAdvance(textPrinter, fontId, str[1] | 0x100);
            str += 2;
            continue;
        case EXT_CTRL_CODE_BEGIN:
            switch (str[1])
            {
            case EXT_CTRL_CODE_SHIFT_RIGHT:
            case EXT_CTRL_CODE_SHIFT_DOWN:
            case EXT_CTRL_CODE_FILL_WINDOW:
            case EXT_CTRL_CODE_CLEAR:
            case EXT_CTRL_CODE_SKIP:
            case EXT_CTRL_CODE_CLEAR_TO:
            case EXT_CTRL_CODE_MIN_LETTER_SPACING:
                return width;
            case EXT_CTRL_CODE_ESCAPE:
                width += RtlGlyphAdvance(textPrinter, fontId, str[2] | 0x100);
                str += 3;
                continue;
            case EXT_CTRL_CODE_FONT:
                fontId = str[2];
                break;
            case EXT_CTRL_CODE_SPEAKER:
                str += 1;
                break;
            case EXT_CTRL_CODE_JPN:
                width += RtlJapaneseWidth(textPrinter, fontId, str + 2);
                str = RtlJapaneseEnd(textPrinter, fontId, str + 2);
                continue;
            }
            str += 1 + GetExtCtrlCodeLength(str[1]);
            continue;
        default:
            if (sRtlCharClass[*str] == RTL_CLASS_RTL)
                *hasRtl = TRUE;
            width += RtlGlyphAdvance(textPrinter, fontId, *str);
            str++;
            continue;
        }
    }
}

// Called for every printable glyph before it is decompressed. Places the in-place axis when a
// segment starts, starts a run when one begins here, and gives a neutral in right-to-left context
// its mirrored partner.
static void RtlPrepareGlyph(struct TextPrinter *textPrinter, const u8 *glyphStart, u16 *currChar)
{
    u32 length;
    bool32 afterRtl = textPrinter->rtlAfterRtl;

    textPrinter->rtlAfterRtl = RtlClassAt(glyphStart, &length) == RTL_CLASS_RTL;

    if (textPrinter->rtlNeedAxis)
    {
        textPrinter->rtlNeedAxis = FALSE;
        textPrinter->rtlSegmentLtr = FALSE;
        if (textPrinter->rtlMode == WINDOW_RTL_IN_PLACE)
        {
            // A segment with no Hebrew (a number, an untranslated name) keeps the English layout:
            // screens such as the party menu overlap separate prints that only line up in it.
            bool32 hasRtl;
            u32 width = RtlMeasureSegment(textPrinter, glyphStart, &hasRtl);
            textPrinter->rtlAxis = 2 * textPrinter->printerTemplate.currentX + width;
            textPrinter->rtlSegmentLtr = !hasRtl;
        }
    }

    if (!RtlIsActive(textPrinter))
        return;

    if (textPrinter->rtlRunGlyphs != 0)
        return;

    if (RtlStartsRun(glyphStart, afterRtl))
    {
        RtlBeginRun(textPrinter, glyphStart);
        if (textPrinter->rtlRunGlyphs != 0)
            return;
    }

    switch (*currChar)
    {
    case CHAR_LEFT_PAREN:     *currChar = CHAR_RIGHT_PAREN;          break;
    case CHAR_RIGHT_PAREN:    *currChar = CHAR_LEFT_PAREN;           break;
    case CHAR_LESS_THAN:      *currChar = CHAR_GREATER_THAN;         break;
    case CHAR_GREATER_THAN:   *currChar = CHAR_LESS_THAN;            break;
    case CHAR_BLACK_TRIANGLE: *currChar = CHAR_BLACK_TRIANGLE_LEFT;  break;
    }
}

// A segment starts after any code that moves the pen; in-place mode measures it again.
static void RtlNewSegment(struct TextPrinter *textPrinter)
{
    textPrinter->rtlNeedAxis = TRUE;
    textPrinter->rtlRunGlyphs = 0;
    textPrinter->rtlAfterRtl = FALSE;
}

// Physical x of a glyph (or of a cleared span) that starts at logical x and is width wide.
static s32 RtlPhysicalX(const struct TextPrinter *textPrinter, u32 x, u32 width, bool32 inRun)
{
    s32 axis = textPrinter->rtlAxis;

    if (inRun)
        return axis - textPrinter->rtlRunStart - textPrinter->rtlRunWidth + ((s32)x - textPrinter->rtlRunStart);
    return axis - (s32)x - (s32)width;
}

// {JPN}, before the printer switches to the Japanese font. Japanese glyphs print through PrintGlyph,
// left to right from the pen, as in English. In a right-to-left window the pen moves here to the
// mirrored place of the whole span, and RtlEndJapanese moves it back to the logical place after
// it, so the span reads as one left-to-right run. rtlRunStart and rtlRunWidth keep the span's
// logical x and width, and rtlRunGlyphs is 1 while the pen is moved; a code that starts a new
// segment (a newline) clears it, and then {ENG} leaves the pen where it is.
static NOINLINE void RtlBeginJapanese(struct TextPrinter *textPrinter)
{
    u32 x = textPrinter->printerTemplate.currentX;
    u32 width;
    s32 physX;

    if (textPrinter->japanese || textPrinter->rtlRunGlyphs != 0)
        return;
    if (textPrinter->rtlNeedAxis)
    {
        // The span starts a segment: place the axis as RtlPrepareGlyph does, measuring from the
        // {JPN} code.
        textPrinter->rtlNeedAxis = FALSE;
        textPrinter->rtlSegmentLtr = FALSE;
        if (textPrinter->rtlMode == WINDOW_RTL_IN_PLACE)
        {
            bool32 hasRtl;
            width = RtlMeasureSegment(textPrinter, textPrinter->printerTemplate.currentChar - 2, &hasRtl);
            textPrinter->rtlAxis = 2 * x + width;
            textPrinter->rtlSegmentLtr = !hasRtl;
        }
    }
    if (!RtlIsActive(textPrinter))
        return;

    width = RtlJapaneseWidth(textPrinter, textPrinter->fontId, textPrinter->printerTemplate.currentChar);
    physX = RtlPhysicalX(textPrinter, x, width, FALSE);
    textPrinter->rtlRunStart = x;
    textPrinter->rtlRunWidth = min(width, 255);
    textPrinter->rtlRunGlyphs = 1;
    textPrinter->printerTemplate.currentX = physX < 0 ? 0 : physX;
}

// {ENG}, while the printer is still in the Japanese font: the pen goes back to its logical place
// after the span that RtlBeginJapanese moved.
static NOINLINE void RtlEndJapanese(struct TextPrinter *textPrinter)
{
    if (!textPrinter->japanese || textPrinter->rtlRunGlyphs == 0)
        return;
    textPrinter->printerTemplate.currentX = textPrinter->rtlRunStart + textPrinter->rtlRunWidth;
    textPrinter->rtlRunGlyphs = 0;
    textPrinter->rtlAfterRtl = FALSE;
}

static void RtlFillSpan(struct TextPrinter *textPrinter, s32 physX, s32 width)
{
    struct Window *window = &gWindows[textPrinter->printerTemplate.windowId];
    struct Bitmap pixels;

    if (physX < 0)
    {
        width += physX;
        physX = 0;
    }
    if (width <= 0 || sLastTextColor.background == TEXT_COLOR_TRANSPARENT)
        return;
    pixels.pixels = window->tileData;
    pixels.width = window->window.width << 3;
    pixels.height = window->window.height << 3;
    FillBitmapRect4Bit(&pixels, physX, textPrinter->printerTemplate.currentY, width, gCurGlyph.height, sLastTextColor.background);
}

// Blits gCurGlyph at a physical x, clipping it at the window's left edge.
static void RtlBlitGlyph(struct TextPrinter *textPrinter, s32 physX)
{
    u32 windowWidth = RtlWindowWidth(textPrinter);
    u32 logicalX = textPrinter->printerTemplate.currentX;

    if (physX < 0)
    {
        RtlReportClip(textPrinter, physX, windowWidth);
        if (-physX >= gCurGlyph.width)
            return;
        OffsetCurrGlyph(-physX);
        physX = 0;
    }
    else if (physX + gCurGlyph.width > windowWidth)
    {
        RtlReportClip(textPrinter, physX, windowWidth);
    }
    textPrinter->printerTemplate.currentX = physX;
    CopyGlyphToVRAM(textPrinter);
    textPrinter->printerTemplate.currentX = logicalX;
}

// PrintGlyph for a right-to-left window printer. The logical pen advances exactly as upstream's.
static void PrintGlyphRtl(struct TextPrinter *textPrinter)
{
    u32 logicalX = textPrinter->printerTemplate.currentX;
    u32 glyphWidth = gCurGlyph.width;
    bool32 inRun = textPrinter->rtlRunGlyphs != 0;
    s32 physX = RtlPhysicalX(textPrinter, logicalX, glyphWidth, inRun);

    RtlBlitGlyph(textPrinter, physX);

    if (textPrinter->minLetterSpacing)
    {
        s32 pad = (s32)textPrinter->minLetterSpacing - (s32)glyphWidth;
        if (pad > 0)
            RtlFillSpan(textPrinter, inRun ? physX + (s32)glyphWidth : physX - pad, pad);
        textPrinter->printerTemplate.currentX = logicalX + textPrinter->minLetterSpacing;
    }
    else
    {
        textPrinter->printerTemplate.currentX = logicalX + glyphWidth;
    }

    if (inRun)
        textPrinter->rtlRunGlyphs--;
}

// x to pass to a window primitive for something drawn at the pen that is width wide (the down
// arrow, a keypad icon). Mirrored windows mirror inside the primitive, so they get the logical x;
// in-place windows are mirrored here around the segment's axis.
static u32 RtlPenObjectX(const struct TextPrinter *textPrinter, u32 width)
{
    s32 x;

    if (!RtlIsActive(textPrinter) || textPrinter->rtlMode != WINDOW_RTL_IN_PLACE)
        return textPrinter->printerTemplate.currentX;
    x = RtlPhysicalX(textPrinter, textPrinter->printerTemplate.currentX, width, FALSE);
    return x < 0 ? 0 : x;
}

// x to pass to a window primitive for the down arrow. The arrow's tile is blank in its first column,
// which English puts against the text; drawn unflipped on the left of right-to-left text, that column
// faces away, and the arrow's ink would touch a last glyph inked in its own first column (a colon).
// One pixel further from the pen keeps the English column of space.
static u32 RtlDownArrowX(const struct TextPrinter *textPrinter)
{
    u32 x = RtlPenObjectX(textPrinter, 8);

    if (!RtlIsActive(textPrinter))
        return x;
    if (textPrinter->rtlMode == WINDOW_RTL_MIRROR)
        return x + 1; // logical: the primitive mirrors it, and clips only the blank column at the edge
    return x > 0 ? x - 1 : 0;
}

// x to pass to DrawKeypadIcon for the button icon at glyphStart, which is width wide. The icon is
// placed like a glyph: it sets the in-place axis when it starts a segment, it can start a run, and
// inside a run it keeps its left-to-right place.
static u32 RtlKeypadIconX(struct TextPrinter *textPrinter, const u8 *glyphStart, u32 width)
{
    u16 unusedChar = 0;
    s32 x;

    RtlPrepareGlyph(textPrinter, glyphStart, &unusedChar);
    if (!RtlIsActive(textPrinter) || textPrinter->rtlRunGlyphs == 0)
        return RtlPenObjectX(textPrinter, width);
    x = RtlPhysicalX(textPrinter, textPrinter->printerTemplate.currentX, width, TRUE);
    textPrinter->rtlRunGlyphs--;
    // The window primitive mirrors a mirrored window's x again.
    if (textPrinter->rtlMode == WINDOW_RTL_MIRROR)
        return WindowRtlX(textPrinter->printerTemplate.windowId, x, width);
    return x < 0 ? 0 : x;
}

// Applies a colour code at str (EXT_CTRL_CODE_BEGIN) to color and returns its length, or returns 0
// for any other code.
static u32 RtlApplyColorCode(const u8 *str, union TextColor *color)
{
    switch (str[1])
    {
    case EXT_CTRL_CODE_COLOR:
        color->foreground = str[2];
        return 3;
    case EXT_CTRL_CODE_HIGHLIGHT:
        color->background = color->accent = str[2];
        return 3;
    case EXT_CTRL_CODE_SHADOW:
        color->shadow = str[2];
        return 3;
    case EXT_CTRL_CODE_ACCENT:
        color->accent = str[2];
        return 3;
    case EXT_CTRL_CODE_BACKGROUND:
        color->background = str[2];
        return 3;
    case EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW:
        color->foreground = str[2];
        color->background = color->accent = str[3];
        color->shadow = str[4];
        return 5;
    case EXT_CTRL_CODE_TEXT_COLORS:
        color->foreground = str[2];
        color->shadow = str[3];
        color->accent = str[4];
        return 5;
    default:
        return 0;
    }
}

// Sprite printers: reorders str into visual order in dest, so that printing it left to right
// reads right to left while the line keeps its English position. Colour codes travel with the
// glyphs they colour (the healthbox's gender symbol). Returns FALSE (and leaves dest unused) when
// str holds no Hebrew, or control codes other than colours and line breaks.
static bool32 RtlReorderToVisual(const u8 *str, u8 *dest, u32 destSize, union TextColor color)
{
    struct { const u8 *start; u8 length; union TextColor color; } units[64];
    union TextColor emitted = color, scan = color;
    bool32 hasRtl = FALSE;
    u32 out = 0;

    for (const u8 *s = str; *s != EOS; s++)
    {
        if (*s == EXT_CTRL_CODE_BEGIN)
        {
            u32 length = RtlApplyColorCode(s, &scan);
            if (length == 0)
                return FALSE;
            s += length - 1;
            continue;
        }
        if (*s == PLACEHOLDER_BEGIN || *s == CHAR_KEYPAD_ICON
         || *s == CHAR_PROMPT_SCROLL || *s == CHAR_PROMPT_CLEAR || *s == CHAR_DYNAMIC)
            return FALSE;
        if (*s == CHAR_EXTRA_SYMBOL)
        {
            s++;
            if (*s == CHAR_LV_2)
                hasRtl = TRUE;
        }
        else if (sRtlCharClass[*s] == RTL_CLASS_RTL)
        {
            hasRtl = TRUE;
        }
    }
    if (!hasRtl)
        return FALSE;

    while (TRUE)
    {
        u32 numUnits = 0;

        while (*str != EOS && *str != CHAR_NEWLINE && numUnits < ARRAY_COUNT(units))
        {
            u32 length;
            if (*str == EXT_CTRL_CODE_BEGIN)
            {
                str += RtlApplyColorCode(str, &color);
                continue;
            }
            units[numUnits].start = str;
            units[numUnits].color = color;
            if (RtlStartsRun(str, numUnits > 0 && RtlClassAt(units[numUnits - 1].start, &length) == RTL_CLASS_RTL))
            {
                // The run ends at its last strong character, as in RtlBeginRun. Colour codes end
                // a unit here, so each unit has one colour.
                const u8 *s = str, *end = str;
                u32 prevClass = RTL_CLASS_NEUTRAL;
                while (*s != EOS && *s != CHAR_NEWLINE && *s != EXT_CTRL_CODE_BEGIN)
                {
                    u32 nextLength, class = RtlClassAt(s, &length);
                    if (class == RTL_CLASS_RTL)
                        break;
                    if (class == RTL_CLASS_LTR || class == RTL_CLASS_DIGIT
                     || (class == RTL_CLASS_NUM_PREFIX && RtlClassAt(s + length, &nextLength) == RTL_CLASS_DIGIT)
                     || (class == RTL_CLASS_NUM_SUFFIX && prevClass == RTL_CLASS_DIGIT))
                        end = s + length;
                    prevClass = class;
                    s += length;
                }
                length = end - str;
            }
            else
            {
                RtlClassAt(str, &length);
            }
            units[numUnits++].length = length;
            str += length;
        }

        while (numUnits > 0)
        {
            u32 i;
            numUnits--;
            if (out + units[numUnits].length + 10 > destSize)
                return FALSE;
            if (units[numUnits].color.asU32 != emitted.asU32)
            {
                emitted = units[numUnits].color;
                dest[out++] = EXT_CTRL_CODE_BEGIN;
                dest[out++] = EXT_CTRL_CODE_TEXT_COLORS;
                dest[out++] = emitted.foreground;
                dest[out++] = emitted.shadow;
                dest[out++] = emitted.accent;
                dest[out++] = EXT_CTRL_CODE_BEGIN;
                dest[out++] = EXT_CTRL_CODE_BACKGROUND;
                dest[out++] = emitted.background;
            }
            for (i = 0; i < units[numUnits].length; i++)
            {
                u8 c = units[numUnits].start[i];
                if (units[numUnits].length == 1)
                {
                    if (c == CHAR_LEFT_PAREN)          c = CHAR_RIGHT_PAREN;
                    else if (c == CHAR_RIGHT_PAREN)    c = CHAR_LEFT_PAREN;
                    else if (c == CHAR_LESS_THAN)      c = CHAR_GREATER_THAN;
                    else if (c == CHAR_GREATER_THAN)   c = CHAR_LESS_THAN;
                }
                dest[out++] = c;
            }
        }

        if (*str == CHAR_NEWLINE)
        {
            dest[out++] = CHAR_NEWLINE;
            str++;
            continue;
        }
        if (*str != EOS)
            return FALSE; // More units on one line than this can hold
        dest[out] = EOS;
        return TRUE;
    }
}

#endif // TEXT_RTL


#define nextX data[1]
#define nextY data[2]

static void PrintGlyph(struct TextPrinter *textPrinter)
{
    u32 cutOffAmount = CopyGlyphToVRAM(textPrinter);

    //  Handle switching to next sprite here
    if (textPrinter->printerTemplate.type == SPRITE_TEXT_PRINTER
     && cutOffAmount > 0
     && gSprites[textPrinter->printerTemplate.spriteId].nextX != SPRITE_NONE)
    {
        //  Set the data to the next sprite
        textPrinter->printerTemplate.spriteId = gSprites[textPrinter->printerTemplate.spriteId].nextX;
        textPrinter->printerTemplate.currentX = 0;

        //  Copy the remaining part of the glyph to the sprite
        //  Offset the current glyph
        u32 newWidth = OffsetCurrGlyph(cutOffAmount);
        CopyGlyphToVRAM(textPrinter);

        //  Set the print offset for the next glyph
        textPrinter->printerTemplate.currentX = newWidth;

    }
    else
    {
        if (textPrinter->minLetterSpacing)
        {
            textPrinter->printerTemplate.currentX += gCurGlyph.width;
            u32 width = textPrinter->minLetterSpacing - gCurGlyph.width;
            if (width > 0)
            {
                ClearTextSpan(textPrinter, width);
                textPrinter->printerTemplate.currentX += width;
            }
        }
        else
        {
            if (textPrinter->japanese)
                textPrinter->printerTemplate.currentX += (gCurGlyph.width + textPrinter->printerTemplate.letterSpacing);
            else
                textPrinter->printerTemplate.currentX += gCurGlyph.width;
        }
    }
}

void ClearTextSpan(struct TextPrinter *textPrinter, u32 width)
{
    struct Window *window;
    struct Bitmap pixels_data;
    struct TextGlyph *glyph;
    u8 *glyphHeight;

#if TEXT_RTL
    // A mirrored window clears the mirrored span. In-place windows keep the gaps between their
    // segments where the English has them.
    if (RtlIsActive(textPrinter) && textPrinter->rtlMode == WINDOW_RTL_MIRROR)
    {
        RtlFillSpan(textPrinter, RtlPhysicalX(textPrinter, textPrinter->printerTemplate.currentX, width, FALSE), width);
        return;
    }
#endif
    if (sLastTextColor.background != TEXT_COLOR_TRANSPARENT)
    {
        window = &gWindows[textPrinter->printerTemplate.windowId];
        pixels_data.pixels = window->tileData;
        pixels_data.width = window->window.width << 3;
        pixels_data.height = window->window.height << 3;

        glyph = &gCurGlyph;
        glyphHeight = &glyph->height;

        FillBitmapRect4Bit(
            &pixels_data,
            textPrinter->printerTemplate.currentX,
            textPrinter->printerTemplate.currentY,
            width,
            *glyphHeight,
            sLastTextColor.background);
    }
}

static u16 FontFunc_Small(struct TextPrinter *textPrinter)
{
    if (textPrinter->hasFontIdBeenSet == FALSE)
    {
        textPrinter->fontId = FONT_SMALL;
        textPrinter->hasFontIdBeenSet = TRUE;
    }
    return RenderText(textPrinter);
}

static u16 FontFunc_Normal(struct TextPrinter *textPrinter)
{
    if (textPrinter->hasFontIdBeenSet == FALSE)
    {
        textPrinter->fontId = FONT_NORMAL;
        textPrinter->hasFontIdBeenSet = TRUE;
    }
    return RenderText(textPrinter);
}

static u16 FontFunc_Short(struct TextPrinter *textPrinter)
{
    if (textPrinter->hasFontIdBeenSet == FALSE)
    {
        textPrinter->fontId = FONT_SHORT;
        textPrinter->hasFontIdBeenSet = TRUE;
    }
    return RenderText(textPrinter);
}

static u16 FontFunc_ShortCopy1(struct TextPrinter *textPrinter)
{
    if (textPrinter->hasFontIdBeenSet == FALSE)
    {
        textPrinter->fontId = FONT_SHORT_COPY_1;
        textPrinter->hasFontIdBeenSet = TRUE;
    }
    return RenderText(textPrinter);
}

static u16 FontFunc_ShortCopy2(struct TextPrinter *textPrinter)
{
    if (textPrinter->hasFontIdBeenSet == FALSE)
    {
        textPrinter->fontId = FONT_SHORT_COPY_2;
        textPrinter->hasFontIdBeenSet = TRUE;
    }
    return RenderText(textPrinter);
}

static u16 FontFunc_ShortCopy3(struct TextPrinter *textPrinter)
{
    if (textPrinter->hasFontIdBeenSet == FALSE)
    {
        textPrinter->fontId = FONT_SHORT_COPY_3;
        textPrinter->hasFontIdBeenSet = TRUE;
    }
    return RenderText(textPrinter);
}

static u16 FontFunc_Narrow(struct TextPrinter *textPrinter)
{
    if (textPrinter->hasFontIdBeenSet == FALSE)
    {
        textPrinter->fontId = FONT_NARROW;
        textPrinter->hasFontIdBeenSet = TRUE;
    }
    return RenderText(textPrinter);
}

static u16 FontFunc_SmallNarrow(struct TextPrinter *textPrinter)
{
    if (textPrinter->hasFontIdBeenSet == FALSE)
    {
        textPrinter->fontId = FONT_SMALL_NARROW;
        textPrinter->hasFontIdBeenSet = TRUE;
    }
    return RenderText(textPrinter);
}

static u16 FontFunc_Narrower(struct TextPrinter *textPrinter)
{
    if (textPrinter->hasFontIdBeenSet == FALSE)
    {
        textPrinter->fontId = FONT_NARROWER;
        textPrinter->hasFontIdBeenSet = TRUE;
    }
    return RenderText(textPrinter);
}

static u16 FontFunc_SmallNarrower(struct TextPrinter *textPrinter)
{
    if (textPrinter->hasFontIdBeenSet == FALSE)
    {
        textPrinter->fontId = FONT_SMALL_NARROWER;
        textPrinter->hasFontIdBeenSet = TRUE;
    }
    return RenderText(textPrinter);
}

static u16 FontFunc_ShortNarrow(struct TextPrinter *textPrinter)
{
    if (textPrinter->hasFontIdBeenSet == FALSE)
    {
        textPrinter->fontId = FONT_SHORT_NARROW;
        textPrinter->hasFontIdBeenSet = TRUE;
    }
    return RenderText(textPrinter);
}

static u16 FontFunc_ShortNarrower(struct TextPrinter *textPrinter)
{
    if (textPrinter->hasFontIdBeenSet == FALSE)
    {
        textPrinter->fontId = FONT_SHORT_NARROWER;
        textPrinter->hasFontIdBeenSet = TRUE;
    }
    return RenderText(textPrinter);
}

void TextPrinterInitDownArrowCounters(struct TextPrinter *textPrinter)
{
    if (gTextFlags.autoScroll == 1)
    {
        textPrinter->autoScrollDelay = 0;
    }
    else
    {
        textPrinter->downArrowYPosIdx = 0;
        textPrinter->utilityCounter = 0;
    }
}

#if TEXT_RTL
#define DOWN_ARROW_X(textPrinter) RtlDownArrowX(textPrinter)
#else
#define DOWN_ARROW_X(textPrinter) ((textPrinter)->printerTemplate.currentX)
#endif

void TextPrinterDrawDownArrow(struct TextPrinter *textPrinter)
{
    const u8 *arrowTiles;

    if (gTextFlags.autoScroll == 0)
    {
        if (textPrinter->utilityCounter != 0)
        {
            textPrinter->utilityCounter--;
        }
        else
        {
            FillWindowPixelRect(
                textPrinter->printerTemplate.windowId,
                textPrinter->printerTemplate.color.background << 4 | textPrinter->printerTemplate.color.background,
                DOWN_ARROW_X(textPrinter),
                textPrinter->printerTemplate.currentY,
                8,
                16);

            switch (gTextFlags.useAlternateDownArrow)
            {
            case FALSE:
            default:
                arrowTiles = sDownArrowTiles;
                break;
            case TRUE:
                arrowTiles = sDarkDownArrowTiles;
                break;
            }

            BlitBitmapRectToWindow(
                textPrinter->printerTemplate.windowId,
                arrowTiles,
                0,
                sDownArrowYCoords[textPrinter->downArrowYPosIdx],
                8,
                16,
                DOWN_ARROW_X(textPrinter),
                textPrinter->printerTemplate.currentY,
                8,
                16);
            CopyWindowToVram(textPrinter->printerTemplate.windowId, COPYWIN_GFX);

            textPrinter->utilityCounter = 8 * GetPlayerTextSpeedModifier();
            textPrinter->downArrowYPosIdx++;
        }
    }
}

void TextPrinterClearDownArrow(struct TextPrinter *textPrinter)
{
    FillWindowPixelRect(
        textPrinter->printerTemplate.windowId,
        textPrinter->printerTemplate.color.background << 4 | textPrinter->printerTemplate.color.background,
        DOWN_ARROW_X(textPrinter),
        textPrinter->printerTemplate.currentY,
        8,
        16);
    CopyWindowToVram(textPrinter->printerTemplate.windowId, COPYWIN_GFX);
}

bool32 TextPrinterWaitAutoMode(struct TextPrinter *textPrinter)
{
    if (textPrinter->autoScrollDelay == NUM_FRAMES_AUTO_SCROLL_DELAY)
    {
        textPrinter->autoScrollDelay = 0;
        return TRUE;
    }
    else
    {
        textPrinter->autoScrollDelay++;
        return FALSE;
    }
}

// At instant speed RenderFont runs up to TEXT_SPEED_INSTANT_MODIFIER times a frame, so a prompt
// reached right after the press that ended the one before it would take that same press. A prompt
// ignores A/B for the calls that can still follow in that frame: all but the call that took the
// press and the call that reached the prompt.
#define INSTANT_TEXT_PROMPT_DELAY (TEXT_SPEED_INSTANT_MODIFIER - 2)
STATIC_ASSERT(INSTANT_TEXT_PROMPT_DELAY >= 0, InstantTextPromptDelayIsNotNegative);

static void DelayPromptPressAtInstantSpeed(struct TextPrinter *textPrinter)
{
    if (IsPlayerTextSpeedInstant())
        textPrinter->delayCounter = INSTANT_TEXT_PROMPT_DELAY;
}

void SetResultWithButtonPress(struct TextPrinter *textPrinter, bool32 *result)
{
    if (textPrinter->delayCounter != 0 && IsPlayerTextSpeedInstant())
    {
        textPrinter->delayCounter--;
    }
    else if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        *result = TRUE;
        PlaySE(SE_SELECT);
    }
}

bool32 TextPrinterWaitWithDownArrow(struct TextPrinter *textPrinter)
{
    bool32 result = FALSE;
    if (gTextFlags.autoScroll != 0 || AUTO_SCROLL_TEXT)
    {
        result = TextPrinterWaitAutoMode(textPrinter);

        if (AUTO_SCROLL_TEXT)
            SetResultWithButtonPress(textPrinter, &result);
    }
    else
    {
        TextPrinterDrawDownArrow(textPrinter);
        SetResultWithButtonPress(textPrinter, &result);
    }
    return result;
}

bool32 TextPrinterWait(struct TextPrinter *textPrinter)
{
    bool32 result = FALSE;
    if (gTextFlags.autoScroll != 0 || AUTO_SCROLL_TEXT)
    {
        result = TextPrinterWaitAutoMode(textPrinter);

        if (AUTO_SCROLL_TEXT)
            SetResultWithButtonPress(textPrinter, &result);
    }
    else
    {
        SetResultWithButtonPress(textPrinter, &result);
    }
    return result;
}

void DrawDownArrow(u8 windowId, u16 x, u16 y, u8 bgColor, bool32 drawArrow, u8 *counter, u8 *yCoordIndex)
{
    const u8 *arrowTiles;

    if (*counter != 0)
    {
        --*counter;
    }
    else
    {
        FillWindowPixelRect(windowId, (bgColor << 4) | bgColor, x, y, 0x8, 0x10);
        if (drawArrow == 0)
        {
            switch (gTextFlags.useAlternateDownArrow)
            {
            case FALSE:
            default:
                arrowTiles = sDownArrowTiles;
                break;
            case TRUE:
                arrowTiles = sDarkDownArrowTiles;
                break;
            }

            BlitBitmapRectToWindow(windowId, arrowTiles, 0, sDownArrowYCoords[*yCoordIndex & 3], 8, 16, x, y - 2, 8, 16);
            CopyWindowToVram(windowId, COPYWIN_GFX);
            *counter = 8 * GetPlayerTextSpeedModifier();
            ++*yCoordIndex;
        }
    }
}

static u16 RenderText(struct TextPrinter *textPrinter)
{
    u16 currChar;
    s32 width;
    s32 widthHelper;
#if TEXT_RTL
    const u8 *glyphStart = NULL;
#endif

    switch (textPrinter->state)
    {
    case RENDER_STATE_HANDLE_CHAR:
        if ((JOY_HELD(A_BUTTON | B_BUTTON) && textPrinter->hasPrintBeenSpedUp) || IsPlayerTextSpeedInstant())
            textPrinter->delayCounter = 0;

        if (textPrinter->delayCounter && textPrinter->textSpeed)
        {
            textPrinter->delayCounter--;
            if (gTextFlags.canABSpeedUpPrint && (JOY_NEW(A_BUTTON | B_BUTTON)))
            {
                textPrinter->hasPrintBeenSpedUp = TRUE;
                textPrinter->delayCounter = 0;
            }
            return RENDER_UPDATE;
        }

        if (!(gBattleTypeFlags & BATTLE_TYPE_RECORDED) && gTextFlags.autoScroll)
            textPrinter->delayCounter = 3;
        else
            textPrinter->delayCounter = textPrinter->textSpeed;

#if TEXT_RTL
        glyphStart = textPrinter->printerTemplate.currentChar;
#endif
        currChar = *textPrinter->printerTemplate.currentChar;
        textPrinter->printerTemplate.currentChar++;

        switch (currChar)
        {
        case CHAR_NEWLINE:
#if TEXT_RTL
            RtlNewSegment(textPrinter);
#endif
            textPrinter->printerTemplate.currentX = textPrinter->printerTemplate.x;
            textPrinter->printerTemplate.currentY += (gFonts[textPrinter->printerTemplate.fontId].maxLetterHeight + textPrinter->printerTemplate.lineSpacing);
            if (textPrinter->printerTemplate.type == SPRITE_TEXT_PRINTER)
            {
                struct Sprite *sprite = &gSprites[textPrinter->printerTemplate.spriteId];
                textPrinter->printerTemplate.spriteId = textPrinter->printerTemplate.firstSpriteInRow;
                if (textPrinter->printerTemplate.currentY  >= GetSpriteHeight(sprite)
                 && gSprites[textPrinter->printerTemplate.spriteId].nextY != SPRITE_NONE)
                {
                    textPrinter->printerTemplate.currentY = textPrinter->printerTemplate.currentY - GetSpriteHeight(sprite);
                    textPrinter->printerTemplate.spriteId = gSprites[textPrinter->printerTemplate.firstSpriteInRow].nextY;
                    textPrinter->printerTemplate.firstSpriteInRow = textPrinter->printerTemplate.spriteId;
                }
            }
            return RENDER_REPEAT;
        case PLACEHOLDER_BEGIN:
            textPrinter->printerTemplate.currentChar++;
            return RENDER_REPEAT;
        case EXT_CTRL_CODE_BEGIN:
            currChar = *textPrinter->printerTemplate.currentChar;
            textPrinter->printerTemplate.currentChar++;
            switch (currChar)
            {
            case EXT_CTRL_CODE_BACKGROUND:
                textPrinter->printerTemplate.color.background = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                GenerateFontHalfRowLookupTable(textPrinter->printerTemplate.color);
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_COLOR:
                textPrinter->printerTemplate.color.foreground = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                GenerateFontHalfRowLookupTable(textPrinter->printerTemplate.color);
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_SHADOW:
                textPrinter->printerTemplate.color.shadow = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                GenerateFontHalfRowLookupTable(textPrinter->printerTemplate.color);
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_ACCENT:
                textPrinter->printerTemplate.color.accent = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                GenerateFontHalfRowLookupTable(textPrinter->printerTemplate.color);
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_HIGHLIGHT:
                textPrinter->printerTemplate.color.background = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.color.accent = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                GenerateFontHalfRowLookupTable(textPrinter->printerTemplate.color);
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW:
                textPrinter->printerTemplate.color.foreground = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                textPrinter->printerTemplate.color.background = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.color.accent = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                textPrinter->printerTemplate.color.shadow = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                GenerateFontHalfRowLookupTable(textPrinter->printerTemplate.color);
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_TEXT_COLORS:
                textPrinter->printerTemplate.color.foreground = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                textPrinter->printerTemplate.color.shadow = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                textPrinter->printerTemplate.color.accent = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                GenerateFontHalfRowLookupTable(textPrinter->printerTemplate.color);
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_PALETTE:
                textPrinter->printerTemplate.currentChar++;
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_FONT:
                textPrinter->fontId = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_RESET_FONT:
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_PAUSE:
                textPrinter->delayCounter = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                textPrinter->state = RENDER_STATE_PAUSE;
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_PAUSE_UNTIL_PRESS:
                textPrinter->state = RENDER_STATE_WAIT;
                DelayPromptPressAtInstantSpeed(textPrinter);
                if (gTextFlags.autoScroll)
                    textPrinter->autoScrollDelay = 0;
                return RENDER_UPDATE;
            case EXT_CTRL_CODE_WAIT_SE:
                textPrinter->state = RENDER_STATE_WAIT_SE;
                return RENDER_UPDATE;
            case EXT_CTRL_CODE_PLAY_BGM:
                currChar = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                currChar |= *textPrinter->printerTemplate.currentChar << 8;
                textPrinter->printerTemplate.currentChar++;
                PlayBGM(currChar);
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_ESCAPE:
                currChar = *textPrinter->printerTemplate.currentChar | 0x100;
                textPrinter->printerTemplate.currentChar++;
                break;
            case EXT_CTRL_CODE_PLAY_SE:
                currChar = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                currChar |= (*textPrinter->printerTemplate.currentChar << 8);
                textPrinter->printerTemplate.currentChar++;
                PlaySE(currChar);
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_SHIFT_RIGHT:
#if TEXT_RTL
                RtlNewSegment(textPrinter);
#endif
                textPrinter->printerTemplate.currentX = textPrinter->printerTemplate.x + *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_SHIFT_DOWN:
#if TEXT_RTL
                RtlNewSegment(textPrinter);
#endif
                textPrinter->printerTemplate.currentY = textPrinter->printerTemplate.y + *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_FILL_WINDOW:
#if TEXT_RTL
                RtlNewSegment(textPrinter);
#endif
                if (textPrinter->printerTemplate.type == WINDOW_TEXT_PRINTER)
                {
                    FillWindowPixelBuffer(textPrinter->printerTemplate.windowId, PIXEL_FILL(textPrinter->printerTemplate.color.background));
                    textPrinter->printerTemplate.currentX = textPrinter->printerTemplate.x;
                    textPrinter->printerTemplate.currentY = textPrinter->printerTemplate.y;
                }
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_PAUSE_MUSIC:
                m4aMPlayStop(&gMPlayInfo_BGM);
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_RESUME_MUSIC:
                m4aMPlayContinue(&gMPlayInfo_BGM);
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_CLEAR:
#if TEXT_RTL
                RtlNewSegment(textPrinter);
#endif
                width = *textPrinter->printerTemplate.currentChar;
                textPrinter->printerTemplate.currentChar++;
                if (width > 0)
                {
                    ClearTextSpan(textPrinter, width);
                    textPrinter->printerTemplate.currentX += width;
                    return RENDER_PRINT;
                }
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_SKIP:
#if TEXT_RTL
                RtlNewSegment(textPrinter);
#endif
                textPrinter->printerTemplate.currentX = *textPrinter->printerTemplate.currentChar + textPrinter->printerTemplate.x;
                textPrinter->printerTemplate.currentChar++;
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_CLEAR_TO:
#if TEXT_RTL
                RtlNewSegment(textPrinter);
#endif
                {
                    widthHelper = *textPrinter->printerTemplate.currentChar;
                    widthHelper += textPrinter->printerTemplate.x;
                    textPrinter->printerTemplate.currentChar++;
                    width = widthHelper - textPrinter->printerTemplate.currentX;
                    if (width > 0)
                    {
                        ClearTextSpan(textPrinter, width);
                        textPrinter->printerTemplate.currentX += width;
                        return RENDER_PRINT;
                    }
                }
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_MIN_LETTER_SPACING:
#if TEXT_RTL
                RtlNewSegment(textPrinter);
#endif
                textPrinter->minLetterSpacing = *textPrinter->printerTemplate.currentChar++;
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_JPN:
#if TEXT_RTL
                RtlBeginJapanese(textPrinter);
#endif
                textPrinter->japanese = TRUE;
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_ENG:
#if TEXT_RTL
                RtlEndJapanese(textPrinter);
#endif
                textPrinter->japanese = FALSE;
                return RENDER_REPEAT;
            case EXT_CTRL_CODE_SPEAKER:
                {
                    enum SpeakerNames name = *textPrinter->printerTemplate.currentChar++;
                    TrySpawnAndShowNamebox(gSpeakerNamesTable[name], NAME_BOX_BASE_TILE_NUM);

                    return RENDER_REPEAT;
                }
            }
            break;
        case CHAR_PROMPT_CLEAR:
            textPrinter->state = RENDER_STATE_CLEAR;
            DelayPromptPressAtInstantSpeed(textPrinter);
            TextPrinterInitDownArrowCounters(textPrinter);
            return RENDER_UPDATE;
        case CHAR_PROMPT_SCROLL:
            textPrinter->state = RENDER_STATE_SCROLL_START;
            DelayPromptPressAtInstantSpeed(textPrinter);
            TextPrinterInitDownArrowCounters(textPrinter);
            return RENDER_UPDATE;
        case CHAR_EXTRA_SYMBOL:
            currChar = *textPrinter->printerTemplate.currentChar | 0x100;
            textPrinter->printerTemplate.currentChar++;
            break;
        case CHAR_KEYPAD_ICON:
            if (textPrinter->printerTemplate.type == WINDOW_TEXT_PRINTER)
            {
                currChar = *textPrinter->printerTemplate.currentChar++;
#if TEXT_RTL
                gCurGlyph.width = DrawKeypadIcon(textPrinter->printerTemplate.windowId, currChar, RtlKeypadIconX(textPrinter, glyphStart, GetKeypadIconWidth(currChar)), textPrinter->printerTemplate.currentY);
#else
                gCurGlyph.width = DrawKeypadIcon(textPrinter->printerTemplate.windowId, currChar, textPrinter->printerTemplate.currentX, textPrinter->printerTemplate.currentY);
#endif
                textPrinter->printerTemplate.currentX += gCurGlyph.width + textPrinter->printerTemplate.letterSpacing;
                return RENDER_PRINT;
            }
            else
            {
                //  Loop over how many 8 px wide glyphs the icon needs
                u32 keypadIconId = *textPrinter->printerTemplate.currentChar++;
                u32 numTiles = sKeypadIcons[keypadIconId].width / 8;
                for (u32 i = 0; i < numTiles; i++)
                {
                    //  Fill the current glyph part
                    for (u32 j = 0; j < 8; j++)
                    {
                        gCurGlyph.gfxBufferTop[j] = ((u32 *)(sKeypadIconTiles + ((i + sKeypadIcons[keypadIconId].tileOffset) * 0x20)))[j];
                        gCurGlyph.gfxBufferBottom[j] = ((u32 *)(sKeypadIconTiles + ((i + 16 + sKeypadIcons[keypadIconId].tileOffset) * 0x20)))[j];
                    }
                    gCurGlyph.width = 8;
                    PrintGlyph(textPrinter);
                }
                return RENDER_PRINT;
            }
        case EOS:
            textPrinter->isInUse = FALSE;
            return RENDER_FINISH;
        }

#if TEXT_RTL
        RtlPrepareGlyph(textPrinter, glyphStart, &currChar);
#endif
        switch (textPrinter->fontId)
        {
        case FONT_SMALL:
            DecompressGlyph_Small(currChar, textPrinter->japanese);
            break;
        case FONT_NORMAL:
            DecompressGlyph_Normal(currChar, textPrinter->japanese);
            break;
        case FONT_SHORT:
        case FONT_SHORT_COPY_1:
        case FONT_SHORT_COPY_2:
        case FONT_SHORT_COPY_3:
            DecompressGlyph_Short(currChar, textPrinter->japanese);
            break;
        case FONT_NARROW:
            DecompressGlyph_Narrow(currChar, textPrinter->japanese);
            break;
        case FONT_SMALL_NARROW:
            DecompressGlyph_SmallNarrow(currChar, textPrinter->japanese);
            break;
        case FONT_NARROWER:
            DecompressGlyph_Narrower(currChar, textPrinter->japanese);
            break;
        case FONT_SMALL_NARROWER:
            DecompressGlyph_SmallNarrower(currChar, textPrinter->japanese);
            break;
        case FONT_SHORT_NARROW:
            DecompressGlyph_ShortNarrow(currChar, textPrinter->japanese);
            break;
        case FONT_SHORT_NARROWER:
            DecompressGlyph_ShortNarrower(currChar, textPrinter->japanese);
            break;
        case FONT_BRAILLE:
            break;
        }

#if TEXT_RTL
        if (RtlIsActive(textPrinter))
        {
            PrintGlyphRtl(textPrinter);
            return RENDER_PRINT;
        }
#endif
        PrintGlyph(textPrinter);

        return RENDER_PRINT;
    case RENDER_STATE_WAIT:
        if (TextPrinterWait(textPrinter))
            textPrinter->state = RENDER_STATE_HANDLE_CHAR;
        return RENDER_UPDATE;
    case RENDER_STATE_CLEAR:
        if (textPrinter->printerTemplate.type == WINDOW_TEXT_PRINTER && TextPrinterWaitWithDownArrow(textPrinter))
        {
            FillWindowPixelBuffer(textPrinter->printerTemplate.windowId, PIXEL_FILL(textPrinter->printerTemplate.color.background));
            textPrinter->printerTemplate.currentX = textPrinter->printerTemplate.x;
            textPrinter->printerTemplate.currentY = textPrinter->printerTemplate.y;
#if TEXT_RTL
            RtlNewSegment(textPrinter);
#endif
            textPrinter->state = RENDER_STATE_HANDLE_CHAR;
        }
        return RENDER_UPDATE;
    case RENDER_STATE_SCROLL_START:
        if (TextPrinterWaitWithDownArrow(textPrinter))
        {
            textPrinter->utilityCounter = 0;
            TextPrinterClearDownArrow(textPrinter);
            textPrinter->scrollDistance = gFonts[textPrinter->printerTemplate.fontId].maxLetterHeight + textPrinter->printerTemplate.lineSpacing;
            textPrinter->printerTemplate.currentX = textPrinter->printerTemplate.x;
#if TEXT_RTL
            RtlNewSegment(textPrinter);
#endif
            textPrinter->state = RENDER_STATE_SCROLL;
        }
        return RENDER_UPDATE;
    case RENDER_STATE_SCROLL:
        if (textPrinter->scrollDistance)
        {
            u32 scrollSpeed = GetPlayerTextScrollSpeed();
            u32 speedModifier = GetPlayerTextSpeedModifier();

            if (textPrinter->utilityCounter != 0)
            {
                textPrinter->utilityCounter--;
                return RENDER_UPDATE;
            }

            if (textPrinter->scrollDistance < scrollSpeed)
            {
                ScrollWindow(textPrinter->printerTemplate.windowId, 0, textPrinter->scrollDistance, PIXEL_FILL(textPrinter->printerTemplate.color.background));
                textPrinter->scrollDistance = 0;
            }
            else
            {
                ScrollWindow(textPrinter->printerTemplate.windowId, 0, scrollSpeed, PIXEL_FILL(textPrinter->printerTemplate.color.background));
                textPrinter->scrollDistance -= scrollSpeed;
            }

            if (speedModifier > 1)
                textPrinter->utilityCounter = speedModifier;
            else
                textPrinter->utilityCounter = 0;

            CopyWindowToVram(textPrinter->printerTemplate.windowId, COPYWIN_GFX);
        }
        else
        {
            textPrinter->state = RENDER_STATE_HANDLE_CHAR;
        }
        return RENDER_UPDATE;
    case RENDER_STATE_WAIT_SE:
        if (!IsSEPlaying())
            textPrinter->state = RENDER_STATE_HANDLE_CHAR;
        return RENDER_UPDATE;
    case RENDER_STATE_PAUSE:
        if (textPrinter->delayCounter != 0)
            textPrinter->delayCounter--;
        else
            textPrinter->state = RENDER_STATE_HANDLE_CHAR;
        return RENDER_UPDATE;
    }

    textPrinter->isInUse = FALSE;
    return RENDER_FINISH;
}

#undef nextX
#undef nextY

static u32 UNUSED GetStringWidthFixedWidthFont(const u8 *str, u8 fontId, u8 letterSpacing)
{
    int i;
    u8 width;
    int temp;
    int temp2;
    u8 line;
    int strPos;
    u8 lineWidths[8];
    const u8 *strLocal;

    for (i = 0; i < (int)ARRAY_COUNT(lineWidths); i++)
        lineWidths[i] = 0;

    width = 0;
    line = 0;
    strLocal = str;
    strPos = 0;

    do
    {
        temp = strLocal[strPos++];
        switch (temp)
        {
        case CHAR_NEWLINE:
        case EOS:
            lineWidths[line] = width;
            width = 0;
            line++;
            break;
        case EXT_CTRL_CODE_BEGIN:
            temp2 = strLocal[strPos++];
            switch (temp2)
            {
            case EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW:
            case EXT_CTRL_CODE_TEXT_COLORS:
                ++strPos;
            case EXT_CTRL_CODE_PLAY_BGM:
            case EXT_CTRL_CODE_PLAY_SE:
                ++strPos;
            case EXT_CTRL_CODE_BACKGROUND:
            case EXT_CTRL_CODE_COLOR:
            case EXT_CTRL_CODE_SHADOW:
            case EXT_CTRL_CODE_ACCENT:
            case EXT_CTRL_CODE_HIGHLIGHT:
            case EXT_CTRL_CODE_PALETTE:
            case EXT_CTRL_CODE_FONT:
            case EXT_CTRL_CODE_PAUSE:
            case EXT_CTRL_CODE_ESCAPE:
            case EXT_CTRL_CODE_SHIFT_RIGHT:
            case EXT_CTRL_CODE_SHIFT_DOWN:
            case EXT_CTRL_CODE_CLEAR:
            case EXT_CTRL_CODE_SKIP:
            case EXT_CTRL_CODE_CLEAR_TO:
            case EXT_CTRL_CODE_MIN_LETTER_SPACING:
            case EXT_CTRL_CODE_SPEAKER:
                ++strPos;
                break;
            case EXT_CTRL_CODE_RESET_FONT:
            case EXT_CTRL_CODE_PAUSE_UNTIL_PRESS:
            case EXT_CTRL_CODE_WAIT_SE:
            case EXT_CTRL_CODE_FILL_WINDOW:
            case EXT_CTRL_CODE_JPN:
            case EXT_CTRL_CODE_ENG:
            default:
                break;
            }
            break;
        case CHAR_DYNAMIC:
        case PLACEHOLDER_BEGIN:
            ++strPos;
            break;
        case CHAR_PROMPT_SCROLL:
        case CHAR_PROMPT_CLEAR:
            break;
        case CHAR_KEYPAD_ICON:
        case CHAR_EXTRA_SYMBOL:
            ++strPos;
        default:
            ++width;
            break;
        }
    } while (temp != EOS);

    for (width = 0, strPos = 0; strPos < 8; ++strPos)
    {
        if (width < lineWidths[strPos])
            width = lineWidths[strPos];
    }

    return (u8)(GetFontAttribute(fontId, FONTATTR_MAX_LETTER_WIDTH) + letterSpacing) * width;
}

static u32 (*GetFontWidthFunc(u8 fontId))(u16, bool32)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sGlyphWidthFuncs); ++i)
    {
        if (fontId == sGlyphWidthFuncs[i].fontId)
            return sGlyphWidthFuncs[i].func;
    }

    return NULL;
}

s32 GetGlyphWidth(u16 glyphId, bool32 isJapanese, u8 fontId)
{
    u32 (*func)(u16 fontId, bool32 isJapanese);

    func = GetFontWidthFunc(fontId);
    if (func == NULL)
        return 0;
    return func(glyphId, isJapanese);
}

s32 GetStringWidth(u8 fontId, const u8 *str, s16 letterSpacing)
{
    bool32 isJapanese;
    int minGlyphWidth;
    u32 (*func)(u16 fontId, bool32 isJapanese);
    int localLetterSpacing;
    u32 lineWidth;
    const u8 *bufferPointer;
    int glyphWidth;
    s32 width;

    isJapanese = 0;
    minGlyphWidth = 0;

    func = GetFontWidthFunc(fontId);
    if (func == NULL)
        return 0;

    if (letterSpacing == -1)
        localLetterSpacing = GetFontAttribute(fontId, FONTATTR_LETTER_SPACING);
    else
        localLetterSpacing = letterSpacing;

    width = 0;
    lineWidth = 0;
    bufferPointer = 0;

    while (*str != EOS)
    {
        switch (*str)
        {
        case CHAR_NEWLINE:
            if (lineWidth > width)
                width = lineWidth;
            lineWidth = 0;
            break;
        case PLACEHOLDER_BEGIN:
            switch (*++str)
            {
            case PLACEHOLDER_ID_STRING_VAR_1:
                bufferPointer = gStringVar1;
                break;
            case PLACEHOLDER_ID_STRING_VAR_2:
                bufferPointer = gStringVar2;
                break;
            case PLACEHOLDER_ID_STRING_VAR_3:
                bufferPointer = gStringVar3;
                break;
            default:
                return 0;
            }
        case CHAR_DYNAMIC:
            if (bufferPointer == NULL)
                bufferPointer = DynamicPlaceholderTextUtil_GetPlaceholderPtr(*++str);
            while (*bufferPointer != EOS)
            {
                glyphWidth = func(*bufferPointer++, isJapanese);
                if (minGlyphWidth > 0)
                {
                    if (glyphWidth < minGlyphWidth)
                        glyphWidth = minGlyphWidth;
                    lineWidth += glyphWidth;
                }
                else
                {
                    lineWidth += glyphWidth;
                    if (isJapanese && str[1] != EOS)
                        lineWidth += localLetterSpacing;
                }
            }
            bufferPointer = 0;
            break;
        case EXT_CTRL_CODE_BEGIN:
            switch (*++str)
            {
            case EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW:
            case EXT_CTRL_CODE_TEXT_COLORS:
                ++str;
            case EXT_CTRL_CODE_PLAY_BGM:
            case EXT_CTRL_CODE_PLAY_SE:
                ++str;
            case EXT_CTRL_CODE_BACKGROUND:
            case EXT_CTRL_CODE_COLOR:
            case EXT_CTRL_CODE_SHADOW:
            case EXT_CTRL_CODE_ACCENT:
            case EXT_CTRL_CODE_HIGHLIGHT:
            case EXT_CTRL_CODE_PALETTE:
            case EXT_CTRL_CODE_PAUSE:
            case EXT_CTRL_CODE_ESCAPE:
            case EXT_CTRL_CODE_SHIFT_RIGHT:
            case EXT_CTRL_CODE_SHIFT_DOWN:
            case EXT_CTRL_CODE_SPEAKER:
                ++str;
                break;
            case EXT_CTRL_CODE_FONT:
                func = GetFontWidthFunc(*++str);
                if (func == NULL)
                    return 0;
                if (letterSpacing == -1)
                    localLetterSpacing = GetFontAttribute(*str, FONTATTR_LETTER_SPACING);
                break;
            case EXT_CTRL_CODE_CLEAR:
                glyphWidth = *++str;
                lineWidth += glyphWidth;
                break;
            case EXT_CTRL_CODE_SKIP:
                lineWidth = *++str;
                break;
            case EXT_CTRL_CODE_CLEAR_TO:
                if (*++str > lineWidth)
                    lineWidth = *str;
                break;
            case EXT_CTRL_CODE_MIN_LETTER_SPACING:
                minGlyphWidth = *++str;
                break;
            case EXT_CTRL_CODE_JPN:
                isJapanese = 1;
                break;
            case EXT_CTRL_CODE_ENG:
                isJapanese = 0;
                break;
            case EXT_CTRL_CODE_RESET_FONT:
            case EXT_CTRL_CODE_PAUSE_UNTIL_PRESS:
            case EXT_CTRL_CODE_WAIT_SE:
            case EXT_CTRL_CODE_FILL_WINDOW:
            default:
                break;
            }
            break;
        case CHAR_KEYPAD_ICON:
        case CHAR_EXTRA_SYMBOL:
            if (*str == CHAR_EXTRA_SYMBOL)
                glyphWidth = func(*++str | 0x100, isJapanese);
            else
                glyphWidth = GetKeypadIconWidth(*++str);

            if (minGlyphWidth > 0)
            {
                if (glyphWidth < minGlyphWidth)
                    glyphWidth = minGlyphWidth;
                lineWidth += glyphWidth;
            }
            else
            {
                lineWidth += glyphWidth;
                if (isJapanese && str[1] != EOS)
                    lineWidth += localLetterSpacing;
            }
            break;
        case CHAR_PROMPT_SCROLL:
        case CHAR_PROMPT_CLEAR:
            break;
        default:
            glyphWidth = func(*str, isJapanese);
            if (minGlyphWidth > 0)
            {
                if (glyphWidth < minGlyphWidth)
                    glyphWidth = minGlyphWidth;
                lineWidth += glyphWidth;
            }
            else
            {
                lineWidth += glyphWidth;
                if (isJapanese && str[1] != EOS)
                    lineWidth += localLetterSpacing;
            }
            break;
        }
        ++str;
    }

    if (lineWidth > width)
        return lineWidth;
    return width;
}

s32 GetStringLineWidth(u8 fontId, const u8 *str, s16 letterSpacing, u32 lineNum, u32 strSize)
{
    u32 strWidth = 0, strLen, currLine;
    u8 strCopy[strSize];

    for (currLine = 1; currLine <= lineNum; currLine++)
    {
        strWidth = GetStringWidth(fontId, str, letterSpacing);
        strLen = StringLineLength(str);
        memset(strCopy, EOS, strSize);
        if (currLine == lineNum && strLen != 0)
        {
            StringCopyN(strCopy, str, strLen);
            strWidth = GetStringWidth(fontId, strCopy, letterSpacing);
            strLen = StringLineLength(strCopy);
            StringAppend(strCopy, gText_EmptyString3);
        }
        str += strLen + 1;
    }
    return strWidth;
}

u8 RenderTextHandleBold(u8 *pixels, u8 fontId, u8 *str)
{
    u8 *strLocal;
    int strPos;
    int temp;
    int temp2;

    union TextColor savedTextColors = SaveTextColors();

    union TextColor textColor = {
        .background = TEXT_COLOR_TRANSPARENT,
        .foreground = TEXT_COLOR_WHITE,
        .shadow = TEXT_COLOR_LIGHT_GRAY,
        .accent = TEXT_COLOR_TRANSPARENT,
    };

    GenerateFontHalfRowLookupTable(textColor);
    strLocal = str;
    strPos = 0;

    do
    {
        temp = strLocal[strPos++];
        switch (temp)
        {
        case EXT_CTRL_CODE_BEGIN:
            temp2 = strLocal[strPos++];
            switch (temp2)
            {
            case EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW:
                textColor.foreground = strLocal[strPos++];
                textColor.background = textColor.accent = strLocal[strPos++];
                textColor.shadow = strLocal[strPos++];
                GenerateFontHalfRowLookupTable(textColor);
                continue;
            case EXT_CTRL_CODE_TEXT_COLORS:
                textColor.foreground = strLocal[strPos++];
                textColor.shadow = strLocal[strPos++];
                textColor.accent = strLocal[strPos++];
                GenerateFontHalfRowLookupTable(textColor);
                continue;
            case EXT_CTRL_CODE_BACKGROUND:
                textColor.background = strLocal[strPos++];
                GenerateFontHalfRowLookupTable(textColor);
                continue;
            case EXT_CTRL_CODE_COLOR:
                textColor.foreground = strLocal[strPos++];
                GenerateFontHalfRowLookupTable(textColor);
                continue;
            case EXT_CTRL_CODE_SHADOW:
                textColor.shadow = strLocal[strPos++];
                GenerateFontHalfRowLookupTable(textColor);
                continue;
            case EXT_CTRL_CODE_ACCENT:
                textColor.accent = strLocal[strPos++];
                GenerateFontHalfRowLookupTable(textColor);
                continue;
            case EXT_CTRL_CODE_HIGHLIGHT:
                textColor.background = textColor.accent = strLocal[strPos++];
                GenerateFontHalfRowLookupTable(textColor);
                continue;
            case EXT_CTRL_CODE_FONT:
                fontId = strLocal[strPos++];
                break;
            case EXT_CTRL_CODE_PLAY_BGM:
            case EXT_CTRL_CODE_PLAY_SE:
                ++strPos;
            case EXT_CTRL_CODE_PALETTE:
            case EXT_CTRL_CODE_PAUSE:
            case EXT_CTRL_CODE_ESCAPE:
            case EXT_CTRL_CODE_SHIFT_RIGHT:
            case EXT_CTRL_CODE_SHIFT_DOWN:
            case EXT_CTRL_CODE_CLEAR:
            case EXT_CTRL_CODE_SKIP:
            case EXT_CTRL_CODE_CLEAR_TO:
            case EXT_CTRL_CODE_MIN_LETTER_SPACING:
            case EXT_CTRL_CODE_SPEAKER:
                ++strPos;
                break;
            case EXT_CTRL_CODE_RESET_FONT:
            case EXT_CTRL_CODE_PAUSE_UNTIL_PRESS:
            case EXT_CTRL_CODE_WAIT_SE:
            case EXT_CTRL_CODE_FILL_WINDOW:
            case EXT_CTRL_CODE_JPN:
            case EXT_CTRL_CODE_ENG:
            default:
                continue;
            }
            break;
        case CHAR_DYNAMIC:
        case CHAR_KEYPAD_ICON:
        case CHAR_EXTRA_SYMBOL:
        case PLACEHOLDER_BEGIN:
            ++strPos;
            break;
        case CHAR_PROMPT_SCROLL:
        case CHAR_PROMPT_CLEAR:
        case CHAR_NEWLINE:
        case EOS:
            break;
        default:
            switch (fontId)
            {
            case FONT_BOLD:
                DecompressGlyph_Bold(temp);
                break;
            case FONT_NORMAL:
            default:
                DecompressGlyph_Normal(temp, TRUE);
                break;
            }
            CpuCopy32(gCurGlyph.gfxBufferTop, pixels, 0x20);
            CpuCopy32(gCurGlyph.gfxBufferBottom, pixels + 0x20, 0x20);
            pixels += 0x40;
            break;
        }
    }
    while (temp != EOS);

    RestoreTextColors(savedTextColors);
    return 1;
}

u8 DrawKeypadIcon(u8 windowId, u8 keypadIconId, u16 x, u16 y)
{
    BlitBitmapRectToWindow(
        windowId,
        sKeypadIconTiles + (sKeypadIcons[keypadIconId].tileOffset * 0x20),
        0,
        0,
        0x80,
        0x80,
        x,
        y,
        sKeypadIcons[keypadIconId].width,
        sKeypadIcons[keypadIconId].height);
    return sKeypadIcons[keypadIconId].width;
}

u8 GetKeypadIconTileOffset(u8 keypadIconId)
{
    return sKeypadIcons[keypadIconId].tileOffset;
}

u8 GetKeypadIconWidth(u8 keypadIconId)
{
    return sKeypadIcons[keypadIconId].width;
}

u8 GetKeypadIconHeight(u8 keypadIconId)
{
    return sKeypadIcons[keypadIconId].height;
}

void SetDefaultFontsPointer(void)
{
    SetFontsPointer(sFontInfos);
}

u8 GetFontAttribute(u8 fontId, u8 attributeId)
{
    int result = 0;
    switch (attributeId)
    {
    case FONTATTR_MAX_LETTER_WIDTH:
        result = sFontInfos[fontId].maxLetterWidth;
        break;
    case FONTATTR_MAX_LETTER_HEIGHT:
        result = sFontInfos[fontId].maxLetterHeight;
        break;
    case FONTATTR_LETTER_SPACING:
        result = sFontInfos[fontId].letterSpacing;
        break;
    case FONTATTR_LINE_SPACING:
        result = sFontInfos[fontId].lineSpacing;
        break;
    case FONTATTR_COLOR_ACCENT:
        result = sFontInfos[fontId].color.accent;
        break;
    case FONTATTR_COLOR_FOREGROUND:
        result = sFontInfos[fontId].color.foreground;
        break;
    case FONTATTR_COLOR_BACKGROUND:
        result = sFontInfos[fontId].color.background;
        break;
    case FONTATTR_COLOR_SHADOW:
        result = sFontInfos[fontId].color.shadow;
        break;
    }
    return result;
}

u8 GetMenuCursorDimensionByFont(u8 fontId, u8 whichDimension)
{
    return sMenuCursorDimensions[fontId][whichDimension];
}

static void DecompressGlyph_Small(u16 glyphId, bool32 isJapanese)
{
    const u16 *glyphs;

    if (isJapanese == 1)
    {
        glyphs = gFontSmallJapaneseGlyphs + (0x100 * (glyphId >> 0x4)) + (0x8 * (glyphId & 0xF));
        DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
        DecompressGlyphTile(glyphs + 0x80, gCurGlyph.gfxBufferBottom);
        gCurGlyph.width = 8;
        gCurGlyph.height = 12;
    }
    else
    {
        glyphs = gFontSmallLatinGlyphs + (0x20 * glyphId);
        gCurGlyph.width = gFontSmallLatinGlyphWidths[glyphId];

        if (gCurGlyph.width <= 8)
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
        }
        else
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x8, gCurGlyph.gfxBufferTop + 8);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
            DecompressGlyphTile(glyphs + 0x18, gCurGlyph.gfxBufferBottom + 8);
        }

        gCurGlyph.height = 13;
    }
}

static u32 GetGlyphWidth_Small(u16 glyphId, bool32 isJapanese)
{
    if (isJapanese == TRUE)
        return 8;
    else
        return gFontSmallLatinGlyphWidths[glyphId];
}

static void DecompressGlyph_Narrow(u16 glyphId, bool32 isJapanese)
{
    const u16 *glyphs;

    if (isJapanese == TRUE)
    {
        glyphs = gFontNormalJapaneseGlyphs + (0x100 * (glyphId >> 0x4)) + (0x8 * (glyphId % 0x10));
        DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
        DecompressGlyphTile(glyphs + 0x80, gCurGlyph.gfxBufferBottom);
        gCurGlyph.width = 8;
        gCurGlyph.height = 15;
    }
    else
    {
        glyphs = gFontNarrowLatinGlyphs + (0x20 * glyphId);
        gCurGlyph.width = gFontNarrowLatinGlyphWidths[glyphId];

        if (gCurGlyph.width <= 8)
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
        }
        else
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x8, gCurGlyph.gfxBufferTop + 8);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
            DecompressGlyphTile(glyphs + 0x18, gCurGlyph.gfxBufferBottom + 8);
        }

        gCurGlyph.height = 15;
    }
}

static u32 GetGlyphWidth_Narrow(u16 glyphId, bool32 isJapanese)
{
    if (isJapanese == TRUE)
        return 8;
    else
        return gFontNarrowLatinGlyphWidths[glyphId];
}

static void DecompressGlyph_SmallNarrow(u16 glyphId, bool32 isJapanese)
{
    const u16 *glyphs;

    if (isJapanese == TRUE)
    {
        glyphs = gFontSmallJapaneseGlyphs + (0x100 * (glyphId >> 0x4)) + (0x8 * (glyphId & 0xF));
        DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
        DecompressGlyphTile(glyphs + 0x80, gCurGlyph.gfxBufferBottom);
        gCurGlyph.width = 8;
        gCurGlyph.height = 12;
    }
    else
    {
        glyphs = gFontSmallNarrowLatinGlyphs + (0x20 * glyphId);
        gCurGlyph.width = gFontSmallNarrowLatinGlyphWidths[glyphId];

        if (gCurGlyph.width <= 8)
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
        }
        else
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x8, gCurGlyph.gfxBufferTop + 8);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
            DecompressGlyphTile(glyphs + 0x18, gCurGlyph.gfxBufferBottom + 8);
        }

        gCurGlyph.height = 12;
    }
}

static u32 GetGlyphWidth_SmallNarrow(u16 glyphId, bool32 isJapanese)
{
    if (isJapanese == TRUE)
        return 8;
    else
        return gFontSmallNarrowLatinGlyphWidths[glyphId];
}

static void DecompressGlyph_Short(u16 glyphId, bool32 isJapanese)
{
    const u16 *glyphs;

    if (isJapanese == TRUE)
    {
        glyphs = gFontShortJapaneseGlyphs + (0x100 * (glyphId >> 0x3)) + (0x10 * (glyphId & 0x7));
        DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
        DecompressGlyphTile(glyphs + 0x8, gCurGlyph.gfxBufferTop + 8);
        DecompressGlyphTile(glyphs + 0x80, gCurGlyph.gfxBufferBottom);    // gCurGlyph + 0x20
        DecompressGlyphTile(glyphs + 0x88, gCurGlyph.gfxBufferBottom + 8);    // gCurGlyph + 0x60
        gCurGlyph.width = gFontShortJapaneseGlyphWidths[glyphId];
        gCurGlyph.height = 14;
    }
    else
    {
        glyphs = gFontShortLatinGlyphs + (0x20 * glyphId);
        gCurGlyph.width = gFontShortLatinGlyphWidths[glyphId];

        if (gCurGlyph.width <= 8)
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
        }
        else
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x8, gCurGlyph.gfxBufferTop + 8);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
            DecompressGlyphTile(glyphs + 0x18, gCurGlyph.gfxBufferBottom + 8);
        }

        gCurGlyph.height = 14;
    }
}

static u32 GetGlyphWidth_Short(u16 glyphId, bool32 isJapanese)
{
    if (isJapanese == TRUE)
        return gFontShortJapaneseGlyphWidths[glyphId];
    else
        return gFontShortLatinGlyphWidths[glyphId];
}

static void DecompressGlyph_Normal(u16 glyphId, bool32 isJapanese)
{
    const u16 *glyphs;

    if (isJapanese == TRUE)
    {
        glyphs = gFontNormalJapaneseGlyphs + (0x100 * (glyphId >> 0x4)) + (0x8 * (glyphId % 0x10));
        DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
        DecompressGlyphTile(glyphs + 0x80, gCurGlyph.gfxBufferBottom);
        gCurGlyph.width = 8;
        gCurGlyph.height = 15;
    }
    else
    {
        glyphs = gFontNormalLatinGlyphs + (0x20 * glyphId);
        gCurGlyph.width = gFontNormalLatinGlyphWidths[glyphId];

        if (gCurGlyph.width <= 8)
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
        }
        else
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x8, gCurGlyph.gfxBufferTop + 8);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
            DecompressGlyphTile(glyphs + 0x18, gCurGlyph.gfxBufferBottom + 8);
        }

        gCurGlyph.height = 15;
    }
}

static u32 GetGlyphWidth_Normal(u16 glyphId, bool32 isJapanese)
{
    if (isJapanese == TRUE)
        return 8;
    else
        return gFontNormalLatinGlyphWidths[glyphId];
}

static void DecompressGlyph_Bold(u16 glyphId)
{
    const u16 *glyphs;

    glyphs = sFontBoldJapaneseGlyphs + (0x100 * (glyphId >> 4)) + (0x8 * (glyphId & 0xF));
    DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
    DecompressGlyphTile(glyphs + 0x80, gCurGlyph.gfxBufferBottom);
    gCurGlyph.width = 8;
    gCurGlyph.height = 12;
}

static void DecompressGlyph_Narrower(u16 glyphId, bool32 isJapanese)
{
    const u16 *glyphs;

    if (isJapanese == TRUE)
    {
        glyphs = gFontNormalJapaneseGlyphs + (0x100 * (glyphId >> 0x4)) + (0x8 * (glyphId % 0x10));
        DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
        DecompressGlyphTile(glyphs + 0x80, gCurGlyph.gfxBufferBottom);
        gCurGlyph.width = 8;
        gCurGlyph.height = 15;
    }
    else
    {
        glyphs = gFontNarrowerLatinGlyphs + (0x20 * glyphId);
        gCurGlyph.width = gFontNarrowerLatinGlyphWidths[glyphId];

        if (gCurGlyph.width <= 8)
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
        }
        else
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x8, gCurGlyph.gfxBufferTop + 8);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
            DecompressGlyphTile(glyphs + 0x18, gCurGlyph.gfxBufferBottom + 8);
        }

        gCurGlyph.height = 15;
    }
}

static u32 GetGlyphWidth_Narrower(u16 glyphId, bool32 isJapanese)
{
    if (isJapanese == TRUE)
        return 8;
    else
        return gFontNarrowerLatinGlyphWidths[glyphId];
}

static void DecompressGlyph_SmallNarrower(u16 glyphId, bool32 isJapanese)
{
    const u16 *glyphs;

    if (isJapanese == TRUE)
    {
        glyphs = gFontSmallJapaneseGlyphs + (0x100 * (glyphId >> 0x4)) + (0x8 * (glyphId % 0x10));
        DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
        DecompressGlyphTile(glyphs + 0x80, gCurGlyph.gfxBufferBottom);
        gCurGlyph.width = 8;
        gCurGlyph.height = 15;
    }
    else
    {
        glyphs = gFontSmallNarrowerLatinGlyphs + (0x20 * glyphId);
        gCurGlyph.width = gFontSmallNarrowerLatinGlyphWidths[glyphId];

        if (gCurGlyph.width <= 8)
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
        }
        else
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x8, gCurGlyph.gfxBufferTop + 8);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
            DecompressGlyphTile(glyphs + 0x18, gCurGlyph.gfxBufferBottom + 8);
        }

        gCurGlyph.height = 15;
    }
}

static u32 GetGlyphWidth_SmallNarrower(u16 glyphId, bool32 isJapanese)
{
    if (isJapanese == TRUE)
        return 8;
    else
        return gFontSmallNarrowerLatinGlyphWidths[glyphId];
}

static void DecompressGlyph_ShortNarrow(u16 glyphId, bool32 isJapanese)
{
    const u16 *glyphs;

    if (isJapanese == TRUE)
    {
        glyphs = gFontShortJapaneseGlyphs + (0x100 * (glyphId >> 0x3)) + (0x10 * (glyphId & 0x7));
        DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
        DecompressGlyphTile(glyphs + 0x8, gCurGlyph.gfxBufferTop + 8);
        DecompressGlyphTile(glyphs + 0x80, gCurGlyph.gfxBufferBottom);    // gCurGlyph + 0x20
        DecompressGlyphTile(glyphs + 0x88, gCurGlyph.gfxBufferBottom + 8);    // gCurGlyph + 0x60
        gCurGlyph.width = gFontShortJapaneseGlyphWidths[glyphId];
        gCurGlyph.height = 14;
    }
    else
    {
        glyphs = gFontShortNarrowLatinGlyphs + (0x20 * glyphId);
        gCurGlyph.width = gFontShortNarrowLatinGlyphWidths[glyphId];

        if (gCurGlyph.width <= 8)
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
        }
        else
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x8, gCurGlyph.gfxBufferTop + 8);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
            DecompressGlyphTile(glyphs + 0x18, gCurGlyph.gfxBufferBottom + 8);
        }

        gCurGlyph.height = 14;
    }
}

static u32 GetGlyphWidth_ShortNarrow(u16 glyphId, bool32 isJapanese)
{
    if (isJapanese == TRUE)
        return gFontShortJapaneseGlyphWidths[glyphId];
    else
        return gFontShortNarrowLatinGlyphWidths[glyphId];
}

static void DecompressGlyph_ShortNarrower(u16 glyphId, bool32 isJapanese)
{
    const u16 *glyphs;

    if (isJapanese == TRUE)
    {
        glyphs = gFontShortJapaneseGlyphs + (0x100 * (glyphId >> 0x3)) + (0x10 * (glyphId & 0x7));
        DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
        DecompressGlyphTile(glyphs + 0x8, gCurGlyph.gfxBufferTop + 8);
        DecompressGlyphTile(glyphs + 0x80, gCurGlyph.gfxBufferBottom);    // gCurGlyph + 0x20
        DecompressGlyphTile(glyphs + 0x88, gCurGlyph.gfxBufferBottom + 8);    // gCurGlyph + 0x60
        gCurGlyph.width = gFontShortJapaneseGlyphWidths[glyphId];
        gCurGlyph.height = 14;
    }
    else
    {
        glyphs = gFontShortNarrowerLatinGlyphs + (0x20 * glyphId);
        gCurGlyph.width = gFontShortNarrowerLatinGlyphWidths[glyphId];

        if (gCurGlyph.width <= 8)
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
        }
        else
        {
            DecompressGlyphTile(glyphs, gCurGlyph.gfxBufferTop);
            DecompressGlyphTile(glyphs + 0x8, gCurGlyph.gfxBufferTop + 8);
            DecompressGlyphTile(glyphs + 0x10, gCurGlyph.gfxBufferBottom);
            DecompressGlyphTile(glyphs + 0x18, gCurGlyph.gfxBufferBottom + 8);
        }

        gCurGlyph.height = 14;
    }
}

static u32 GetGlyphWidth_ShortNarrower(u16 glyphId, bool32 isJapanese)
{
    if (isJapanese == TRUE)
        return gFontShortJapaneseGlyphWidths[glyphId];
    else
        return gFontShortNarrowerLatinGlyphWidths[glyphId];
}

static const s8 sNarrowerFontIds[] =
{
    [FONT_SMALL] = FONT_SMALL_NARROW,
    [FONT_NORMAL] = FONT_NARROW,
    [FONT_SHORT] = FONT_SHORT_NARROW,
    [FONT_SHORT_COPY_1] = FONT_SHORT_NARROW,
    [FONT_SHORT_COPY_2] = FONT_SHORT_NARROW,
    [FONT_SHORT_COPY_3] = FONT_SHORT_NARROW,
    [FONT_BRAILLE] = -1,
    [FONT_NARROW] = FONT_NARROWER,
    [FONT_SMALL_NARROW] = FONT_SMALL_NARROWER,
    [FONT_BOLD] = -1,
    [FONT_NARROWER] = -1,
    [FONT_SMALL_NARROWER] = -1,
    [FONT_SHORT_NARROW] = FONT_SHORT_NARROWER,
    [FONT_SHORT_NARROWER] = -1,
};

// If the narrowest font ID doesn't fit the text, we still return that
// ID because clipping is better than crashing.
u32 GetFontIdToFit(const u8 *string, u32 fontId, u32 letterSpacing, u32 widthPx)
{
    for (;;)
    {
        s32 narrowerFontId = sNarrowerFontIds[fontId];
        if (narrowerFontId == -1)
            return fontId;
        if (GetStringWidth(fontId, string, letterSpacing) <= widthPx)
            return fontId;
        fontId = narrowerFontId;
    }
}

#if TEXT_RTL
// Drops glyphs from the end of a name until the whole string fits in widthPx in fontId. The name
// runs from str to nameEnd; what follows it (a gender symbol and its colour codes) is kept. Some
// Hebrew letters are wider than the Latin letters an English name slot was sized for, so ten of
// them do not fit even in the narrowest font GetFontIdToFit falls back to.
void FitNameToWidth(u8 *str, u8 *nameEnd, u32 fontId, u32 widthPx)
{
    while (nameEnd > str && GetStringWidth(fontId, str, 0) > (s32)widthPx)
    {
        u8 *cut = nameEnd - 1;

        if (cut > str && cut[-1] == CHAR_EXTRA_SYMBOL)
            cut--;
        StringCopy(cut, nameEnd);
        nameEnd = cut;
    }
}

#endif
u8 *PrependFontIdToFit(u8 *start, u8 *end, u32 fontId, u32 width)
{
    u32 fitFontId = GetFontIdToFit(start, fontId, 0, width);

    if (fitFontId == fontId)
        return end;

    memmove(&start[3], &start[0], end - start);
    start[0] = EXT_CTRL_CODE_BEGIN;
    start[1] = EXT_CTRL_CODE_FONT;
    start[2] = fitFontId;
    end[3] = EOS;
    return end + 3;
}

u8 *WrapFontIdToFit(u8 *start, u8 *end, u32 fontId, u32 width)
{

    u32 fitFontId = GetFontIdToFit(start, fontId, 0, width);
    if (fitFontId != fontId)
    {
        memmove(&start[3], &start[0], end - start);
        start[0] = EXT_CTRL_CODE_BEGIN;
        start[1] = EXT_CTRL_CODE_FONT;
        start[2] = fitFontId;
        end[3] = EXT_CTRL_CODE_BEGIN;
        end[4] = EXT_CTRL_CODE_FONT;
        end[5] = fontId;
        end[6] = EOS;
        return end + 6;
    }
    else
    {
        return end;
    }
}

static struct TextPrinter *AllocateTextPrinter(void)
{
    struct TextPrinter *printer = Alloc(sizeof(struct TextPrinter));

    if (printer == NULL)
    {
        errorf("Failed to allocate text printer");
        return NULL;
    }

    if (sFirstTextPrinter == NULL)
    {
        sFirstTextPrinter = printer;
    }
    else
    {
        struct TextPrinter *currentPrinter = sFirstTextPrinter;
        while (currentPrinter->nextPrinter != NULL)
            currentPrinter = currentPrinter->nextPrinter;

        currentPrinter->nextPrinter = printer;
    }

    return printer;
}

static u32 GetNumTextPrinters(void)
{
    u32 numPrinters = 0;
    struct TextPrinter *currentPrinter = sFirstTextPrinter;
    while (currentPrinter != NULL)
    {
        currentPrinter = currentPrinter->nextPrinter;
        numPrinters++;
    }
    return numPrinters;
}

static void FreeFinishedTextPrinters(void)
{
    //  Clear out printers from the front
    while (sFirstTextPrinter != NULL)
    {
        if (!sFirstTextPrinter->isInUse)
        {
            struct TextPrinter *printer = sFirstTextPrinter;
            sFirstTextPrinter = sFirstTextPrinter->nextPrinter;
            Free(printer);
        }
        else
        {
            break;
        }
    }

    if (sFirstTextPrinter == NULL)
        return;

    //  Clear out printers in the "middle"
    struct TextPrinter *prevPrinter = sFirstTextPrinter;
    struct TextPrinter *currentPrinter = sFirstTextPrinter->nextPrinter;

    while (currentPrinter != NULL)
    {
        if (!currentPrinter->isInUse)
        {
            prevPrinter->nextPrinter = currentPrinter->nextPrinter;
            Free(currentPrinter);
            currentPrinter = prevPrinter->nextPrinter;
        }
        else
        {
            prevPrinter = currentPrinter;
            currentPrinter = currentPrinter->nextPrinter;
        }
    }
}

// FRLG

#define TAG_CURSOR 0x8000

extern const struct OamData gOamData_AffineOff_ObjNormal_16x16;

static const u8 sDoubleArrowTiles1[]       = INCBIN_U8("graphics/fonts/down_arrow_3.4bpp");
static const u8 sDoubleArrowTiles2[]       = INCBIN_U8("graphics/fonts/down_arrow_4.4bpp");

static const struct SpriteSheet sSpriteSheets_TextCursor[] =
{
    {sDoubleArrowTiles1, sizeof(sDoubleArrowTiles1), TAG_CURSOR},
    {sDoubleArrowTiles2, sizeof(sDoubleArrowTiles2), TAG_CURSOR},
    {NULL}
};

static const struct SpritePalette sSpritePalettes_TextCursor[] =
{
    {gStandardMenuPalette, TAG_CURSOR},
    {NULL}
};

static const struct SpriteTemplate sSpriteTemplate_TextCursor =
{
    .tileTag = TAG_CURSOR,
    .paletteTag = TAG_CURSOR,
    .oam = &gOamData_AffineOff_ObjNormal_16x16,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_TextCursor,
};

#define sDelay data[0]
#define sState data[1]

static void SpriteCB_TextCursor(struct Sprite *sprite)
{
    if (sprite->sDelay)
    {
        sprite->sDelay--;
    }
    else
    {
        sprite->sDelay = 8;
        switch (sprite->sState)
        {
        case 0:
            sprite->y2 = 0;
            break;
        case 1:
            sprite->y2 = 1;
            break;
        case 2:
            sprite->y2 = 2;
            break;
        case 3:
            sprite->y2 = 1;
            sprite->sState = 0;
            return;
        }
        sprite->sState++;
    }
}

u8 CreateTextCursorSprite(u8 sheetId, u16 x, u16 y, u8 priority, u8 subpriority)
{
    u8 spriteId;
    LoadSpriteSheet(&sSpriteSheets_TextCursor[sheetId & 1]);
    LoadSpritePalette(&sSpritePalettes_TextCursor[0]);
    spriteId = CreateSprite(&sSpriteTemplate_TextCursor, x + 3, y + 4, subpriority);
    gSprites[spriteId].oam.priority = (priority & 3);
    gSprites[spriteId].oam.matrixNum = 0;
    gSprites[spriteId].sDelay = 8;
    return spriteId;
}

void DestroyTextCursorSprite(u8 spriteId)
{
    DestroySprite(&gSprites[spriteId]);
    FreeSpriteTilesByTag(TAG_CURSOR);
    FreeSpritePaletteByTag(TAG_CURSOR);
}

#undef sDelay
#undef sState

// End FRLG

void DeactivateSingleTextPrinter(u32 id, enum TextPrinterType type)
{
    struct TextPrinter *currentPrinter = sFirstTextPrinter;
    bool32 foundPrinter = FALSE;
    //  This loop cannot exit early because a single window/sprite group can have multiple printers attached to it
    while (currentPrinter != NULL)
    {
        switch (type)
        {
        case WINDOW_TEXT_PRINTER:
            if (currentPrinter->printerTemplate.type == WINDOW_TEXT_PRINTER && currentPrinter->printerTemplate.windowId == id)
            {
                currentPrinter->isInUse = FALSE;
                currentPrinter = NULL;
                foundPrinter = TRUE;
            }
            else
            {
                currentPrinter = currentPrinter->nextPrinter;
            }
            break;
        case SPRITE_TEXT_PRINTER:
            if (currentPrinter->printerTemplate.type == SPRITE_TEXT_PRINTER && currentPrinter->printerTemplate.firstSprite == id)
            {
                currentPrinter->isInUse = FALSE;
                currentPrinter = NULL;
                foundPrinter = TRUE;
            }
            else
            {
                currentPrinter = currentPrinter->nextPrinter;
            }
            break;
        }
    }

    if (foundPrinter)
        FreeFinishedTextPrinters();
}
