#include "global.h"
#include "string_util.h"
#include "text.h"
#include "strings.h"
#include "union_room_chat.h"
#include "event_data.h"

EWRAM_DATA u8 gStringVar1[0x100] = {0};
EWRAM_DATA u8 gStringVar2[0x100] = {0};
EWRAM_DATA u8 gStringVar3[0x100] = {0};
EWRAM_DATA u8 gStringVar4[0x3E8] = {0};
EWRAM_DATA static u8 sUnknownStringVar[16] = {0};

#if RTL_STRING_REPORT
// Read back by the harness (tools/hebrew/strcov.py): every ROM address that reached a string copy,
// an expansion or a text printer, once each, in an open-addressed set (0 = empty slot). Inserts are
// refused at 3/4 full and counted in gRtlStringLost. The harness empties the set after each read by
// setting gRtlStringCount to 0 and gRtlStringClear to 1; the next insert then clears the slots.
#define RTL_STRING_SLOTS 2048
EWRAM_DATA u32 gRtlStringSet[RTL_STRING_SLOTS] = {0};
EWRAM_DATA u32 gRtlStringCount = 0;
EWRAM_DATA u32 gRtlStringLost = 0;
EWRAM_DATA u32 gRtlStringClear = 0;
EWRAM_DATA u32 gRtlStringTotal = 0;

// RAM copies of ROM data that hold strings (facility floors in the heap, contest opponents and hall
// winners): a string read from such a copy is recorded at its ROM address, if the copy still holds
// the ROM bytes (the block may have been freed and reused, or the save's copy changed, since).
#define RTL_STRING_RAM_MAPS 16
struct RtlStringRamMap
{
    const u8 *ram;
    const u8 *rom;
    u32 size;
};
EWRAM_DATA static struct RtlStringRamMap sRtlStringRamMaps[RTL_STRING_RAM_MAPS] = {0};
EWRAM_DATA static u32 sRtlStringRamMapNext = 0;

void RtlStringMapRam(const void *ram, const void *rom, u32 size)
{
    u32 i;

    for (i = 0; i < RTL_STRING_RAM_MAPS; i++)
    {
        if (sRtlStringRamMaps[i].ram == ram)
            break;
    }
    if (i == RTL_STRING_RAM_MAPS)
    {
        i = sRtlStringRamMapNext;
        sRtlStringRamMapNext = (sRtlStringRamMapNext + 1) % RTL_STRING_RAM_MAPS;
    }
    sRtlStringRamMaps[i].ram = ram;
    sRtlStringRamMaps[i].rom = rom;
    sRtlStringRamMaps[i].size = size;
}

static u32 RtlStringRomAddress(u32 addr)
{
    u32 i, n;

    for (i = 0; i < RTL_STRING_RAM_MAPS; i++)
    {
        const struct RtlStringRamMap *map = &sRtlStringRamMaps[i];
        if (map->size && addr >= (u32)map->ram && addr < (u32)map->ram + map->size)
        {
            const u8 *ram = (const u8 *)addr;
            const u8 *rom = map->rom + (addr - (u32)map->ram);
            for (n = 0; n < 0x100; n++)
            {
                if (ram[n] != rom[n])
                    return 0;
                if (ram[n] == EOS)
                    break;
            }
            return (u32)rom;
        }
    }
    return 0;
}

void RtlStringReport(const u8 *str)
{
    u32 addr = (u32)str;
    u32 i, slot;

    if (addr >= 0x02000000 && addr < 0x04000000)
        addr = RtlStringRomAddress(addr);
    if (addr < 0x08000000 || addr >= 0x0A000000)
        return;
    if (gRtlStringClear)
    {
        for (i = 0; i < RTL_STRING_SLOTS; i++)
            gRtlStringSet[i] = 0;
        gRtlStringCount = 0;
        gRtlStringClear = 0;
    }
    slot = (addr * 2654435761u) >> 21;
    for (i = 0; i < RTL_STRING_SLOTS; i++)
    {
        if (gRtlStringSet[slot] == addr)
            return;
        if (gRtlStringSet[slot] == 0)
            break;
        slot = (slot + 1) & (RTL_STRING_SLOTS - 1);
    }
    if (gRtlStringCount >= RTL_STRING_SLOTS / 4 * 3)
    {
        gRtlStringLost++;
        return;
    }
    gRtlStringSet[slot] = addr;
    gRtlStringCount++;
    gRtlStringTotal++;
}
#endif

static const u8 sDigits[] = __("0123456789ABCDEF");

static const s32 sPowersOfTen[] =
{
             1,
            10,
           100,
          1000,
         10000,
        100000,
       1000000,
      10000000,
     100000000,
    1000000000,
};

u8 *StringCopy_Nickname(u8 *dest, const u8 *src)
{
#if RTL_STRING_REPORT
    RtlStringReport(src);
#endif
    u8 i;
    u32 limit = POKEMON_NAME_LENGTH;

    for (i = 0; i < limit; i++)
    {
        dest[i] = src[i];

        if (dest[i] == EOS)
            return &dest[i];
    }

    dest[i] = EOS;
    return &dest[i];
}

u8 *StringGet_Nickname(u8 *str)
{
    u32 i;
    u32 limit = POKEMON_NAME_LENGTH;

    for (i = 0; i < limit; i++)
        if (str[i] == EOS)
            return &str[i];

    str[i] = EOS;
    return &str[i];
}

u8 *StringCopy_PlayerName(u8 *dest, const u8 *src)
{
#if RTL_STRING_REPORT
    RtlStringReport(src);
#endif
    s32 i;
    s32 limit = PLAYER_NAME_LENGTH;

    for (i = 0; i < limit; i++)
    {
        dest[i] = src[i];

        if (dest[i] == EOS)
            return &dest[i];
    }

    dest[i] = EOS;
    return &dest[i];
}

u8 *StringCopy(u8 *dest, const u8 *src)
{
#if RTL_STRING_REPORT
    RtlStringReport(src);
#endif
    while (*src != EOS)
    {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = EOS;
    return dest;
}

u8 *StringAppend(u8 *dest, const u8 *src)
{
    while (*dest != EOS)
        dest++;

    return StringCopy(dest, src);
}

u8 *StringCopyN(u8 *dest, const u8 *src, u8 n)
{
#if RTL_STRING_REPORT
    RtlStringReport(src);
#endif
    u32 i;

    for (i = 0; i < n; i++)
        dest[i] = src[i];

    return &dest[n];
}

u8 *StringAppendN(u8 *dest, const u8 *src, u8 n)
{
    while (*dest != EOS)
        dest++;

    return StringCopyN(dest, src, n);
}

u16 StringLength(const u8 *str)
{
    u16 length = 0;

    while (str[length] != EOS)
        length++;

    return length;
}

u16 StringLineLength(const u8 *str)
{
    u16 i = 0, length = 0;

    while (str[length] != EOS)
    {
        switch (str[length])
        {
        case CHAR_PROMPT_SCROLL:
        case CHAR_PROMPT_CLEAR:
        case CHAR_NEWLINE:
            return length;
        default:
            i++;
            length++;
            break;
        }
    }

    return length;
}

s32 StringCompare(const u8 *str1, const u8 *str2)
{
    while (*str1 == *str2)
    {
        if (*str1 == EOS)
            return 0;
        str1++;
        str2++;
    }

    return *str1 - *str2;
}

#if TEXT_RTL
static u8 HebrewBaseLetter(u8 c)
{
    switch (c)
    {
    case CHAR_HEB_FINAL_KAF:   return CHAR_HEB_KAF;
    case CHAR_HEB_FINAL_MEM:   return CHAR_HEB_MEM;
    case CHAR_HEB_FINAL_NUN:   return CHAR_HEB_NUN;
    case CHAR_HEB_FINAL_PE:    return CHAR_HEB_PE;
    case CHAR_HEB_FINAL_TSADI: return CHAR_HEB_TSADI;
    default:                   return c;
    }
}
#endif

// Order for lists sorted by name. Hebrew final letters sort with their ordinary forms, and a
// name sorts before the longer names that start with it.
s32 StringCompareAlphabetical(const u8 *str1, const u8 *str2)
{
#if TEXT_RTL
    const u8 *a = str1, *b = str2;

    while (HebrewBaseLetter(*a) == HebrewBaseLetter(*b))
    {
        if (*a == EOS)
            return StringCompare(str1, str2);
        a++;
        b++;
    }

    if (*a == EOS)
        return -1;
    if (*b == EOS)
        return 1;
    return HebrewBaseLetter(*a) - HebrewBaseLetter(*b);
#else
    return StringCompare(str1, str2);
#endif
}

s32 StringCompareN(const u8 *str1, const u8 *str2, u32 n)
{
    while (*str1 == *str2)
    {
        if (*str1 == EOS)
            return 0;
        str1++;
        str2++;
        if (--n == 0)
            return 0;
    }

    return *str1 - *str2;
}

bool8 IsStringLengthAtLeast(const u8 *str, s32 n)
{
    u32 i;

    for (i = 0; i < n; i++)
        if (str[i] && str[i] != EOS)
            return TRUE;

    return FALSE;
}

u8 *ConvertIntToDecimalStringN(u8 *dest, s32 value, enum StringConvertMode mode, u8 n)
{
    enum { WAITING_FOR_NONZERO_DIGIT, WRITING_DIGITS, WRITING_SPACES } state;
    s32 powerOfTen;
    s32 largestPowerOfTen = sPowersOfTen[n - 1];

    state = WAITING_FOR_NONZERO_DIGIT;

    if (mode == STR_CONV_MODE_RIGHT_ALIGN)
        state = WRITING_SPACES;

    if (mode == STR_CONV_MODE_LEADING_ZEROS)
        state = WRITING_DIGITS;

    for (powerOfTen = largestPowerOfTen; powerOfTen > 0; powerOfTen /= 10)
    {
        u8 c;
        u16 digit = value / powerOfTen;
        s32 temp = value - (powerOfTen * digit);

        if (state == WRITING_DIGITS)
        {
            u8 *out = dest++;

            if (digit <= 9)
                c = sDigits[digit];
            else
                c = CHAR_QUESTION_MARK;

            *out = c;
        }
        else if (digit != 0 || powerOfTen == 1)
        {
            u8 *out;
            state = WRITING_DIGITS;
            out = dest++;

            if (digit <= 9)
                c = sDigits[digit];
            else
                c = CHAR_QUESTION_MARK;

            *out = c;
        }
        else if (state == WRITING_SPACES)
        {
            *dest++ = CHAR_SPACER;
        }

        value = temp;
    }

    *dest = EOS;
    return dest;
}

u8 *ConvertUIntToDecimalStringN(u8 *dest, u32 value, enum StringConvertMode mode, u8 n)
{
    enum { WAITING_FOR_NONZERO_DIGIT, WRITING_DIGITS, WRITING_SPACES } state;
    s32 powerOfTen;
    s32 largestPowerOfTen = sPowersOfTen[n - 1];

    state = WAITING_FOR_NONZERO_DIGIT;

    if (mode == STR_CONV_MODE_RIGHT_ALIGN)
        state = WRITING_SPACES;

    if (mode == STR_CONV_MODE_LEADING_ZEROS)
        state = WRITING_DIGITS;

    for (powerOfTen = largestPowerOfTen; powerOfTen > 0; powerOfTen /= 10)
    {
        u8 c;
        u16 digit = value / powerOfTen;
        u32 temp = value - (powerOfTen * digit);

        if (state == WRITING_DIGITS)
        {
            u8 *out = dest++;

            if (digit <= 9)
                c = sDigits[digit];
            else
                c = CHAR_QUESTION_MARK;

            *out = c;
        }
        else if (digit != 0 || powerOfTen == 1)
        {
            u8 *out;
            state = WRITING_DIGITS;
            out = dest++;

            if (digit <= 9)
                c = sDigits[digit];
            else
                c = CHAR_QUESTION_MARK;

            *out = c;
        }
        else if (state == WRITING_SPACES)
        {
            *dest++ = CHAR_SPACER;
        }

        value = temp;
    }

    *dest = EOS;
    return dest;
}

u8 *ConvertIntToHexStringN(u8 *dest, s32 value, enum StringConvertMode mode, u8 n)
{
    enum { WAITING_FOR_NONZERO_DIGIT, WRITING_DIGITS, WRITING_SPACES } state;
    u32 i;
    s32 powerOfSixteen;
    s32 largestPowerOfSixteen = 1;

    for (i = 1; i < n; i++)
        largestPowerOfSixteen *= 16;

    state = WAITING_FOR_NONZERO_DIGIT;

    if (mode == STR_CONV_MODE_RIGHT_ALIGN)
        state = WRITING_SPACES;

    if (mode == STR_CONV_MODE_LEADING_ZEROS)
        state = WRITING_DIGITS;

    for (powerOfSixteen = largestPowerOfSixteen; powerOfSixteen > 0; powerOfSixteen /= 16)
    {
        u8 c;
        u32 digit = value / powerOfSixteen;
        s32 temp = value % powerOfSixteen;

        if (state == WRITING_DIGITS)
        {
            u8 *out = dest++;

            if (digit <= 0xF)
                c = sDigits[digit];
            else
                c = CHAR_QUESTION_MARK;

            *out = c;
        }
        else if (digit != 0 || powerOfSixteen == 1)
        {
            u8 *out;
            state = WRITING_DIGITS;
            out = dest++;

            if (digit <= 0xF)
                c = sDigits[digit];
            else
                c = CHAR_QUESTION_MARK;

            *out = c;
        }
        else if (state == WRITING_SPACES)
        {
            *dest++ = CHAR_SPACER;
        }

        value = temp;
    }

    *dest = EOS;
    return dest;
}

u8 *StringExpandPlaceholders(u8 *dest, const u8 *src)
{
#if RTL_STRING_REPORT
    RtlStringReport(src);
#endif
    for (;;)
    {
        u8 c = *src++;
        u8 placeholderId;
        const u8 *expandedString;

        switch (c)
        {
        case PLACEHOLDER_BEGIN:
            placeholderId = *src++;
            expandedString = GetExpandedPlaceholder(placeholderId);
            dest = StringExpandPlaceholders(dest, expandedString);
            break;
        case EXT_CTRL_CODE_BEGIN:
            *dest++ = c;
            c = *src++;
            *dest++ = c;

            switch (c)
            {
            case EXT_CTRL_CODE_RESET_FONT:
            case EXT_CTRL_CODE_PAUSE_UNTIL_PRESS:
            case EXT_CTRL_CODE_FILL_WINDOW:
            case EXT_CTRL_CODE_JPN:
            case EXT_CTRL_CODE_ENG:
            case EXT_CTRL_CODE_PAUSE_MUSIC:
            case EXT_CTRL_CODE_RESUME_MUSIC:
                break;
            case EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW:
            case EXT_CTRL_CODE_TEXT_COLORS:
                *dest++ = *src++;
            case EXT_CTRL_CODE_PLAY_BGM:
                *dest++ = *src++;
            default:
                *dest++ = *src++;
            }
            break;
        case EOS:
            *dest = EOS;
            return dest;
        case CHAR_PROMPT_SCROLL:
        case CHAR_PROMPT_CLEAR:
        case CHAR_NEWLINE:
        default:
            *dest++ = c;
        }
    }
}

u8 *StringBraille(u8 *dest, const u8 *src)
{
#if RTL_STRING_REPORT
    RtlStringReport(src);
#endif
    const u8 setBrailleFont[] = {
        EXT_CTRL_CODE_BEGIN,
        EXT_CTRL_CODE_FONT,
        FONT_BRAILLE,
        EOS
    };
    const u8 gotoLine2[] = {
        CHAR_NEWLINE,
        EXT_CTRL_CODE_BEGIN,
        EXT_CTRL_CODE_SHIFT_DOWN,
        2,
        EOS
    };

    dest = StringCopy(dest, setBrailleFont);

    for (;;)
    {
        u8 c = *src++;

        switch (c)
        {
        case EOS:
            *dest = c;
            return dest;
        case CHAR_NEWLINE:
            dest = StringCopy(dest, gotoLine2);
            break;
        default:
            *dest++ = c;
            *dest++ = c + NUM_BRAILLE_CHARS;
            break;
        }
    }
}

static const u8 *ExpandPlaceholder_UnknownStringVar(void)
{
    return sUnknownStringVar;
}

static const u8 *ExpandPlaceholder_PlayerName(void)
{
    return gSaveBlock2Ptr->playerName;
}

static const u8 *ExpandPlaceholder_StringVar1(void)
{
    return gStringVar1;
}

static const u8 *ExpandPlaceholder_StringVar2(void)
{
    return gStringVar2;
}

static const u8 *ExpandPlaceholder_StringVar3(void)
{
    return gStringVar3;
}

static const u8 *ExpandPlaceholder_KunChan(void)
{
    if (gSaveBlock2Ptr->playerGender == MALE)
        return gText_ExpandedPlaceholder_Kun;
    else
        return gText_ExpandedPlaceholder_Chan;
}

static const u8 *ExpandPlaceholder_RivalName(void)
{
#if IS_FRLG
    if (gSaveBlock1Ptr->rivalName[0] != EOS)
        return gSaveBlock1Ptr->rivalName;
#elif IS_HNS
    if (gSaveBlock2Ptr->rivalName[0] != EOS)
        return gSaveBlock2Ptr->rivalName;
#endif

    if (gSaveBlock2Ptr->playerGender == MALE)
        return (IS_FRLG ? gText_ExpandedPlaceholder_Green : gText_ExpandedPlaceholder_May);
    else
        return (IS_FRLG ? gText_ExpandedPlaceholder_Red : gText_ExpandedPlaceholder_Brendan);
}

static const u8 *ExpandPlaceholder_Version(void)
{
    return gText_ExpandedPlaceholder_Emerald;
}

static const u8 *ExpandPlaceholder_Aqua(void)
{
    return gText_ExpandedPlaceholder_Aqua;
}

static const u8 *ExpandPlaceholder_Magma(void)
{
    return gText_ExpandedPlaceholder_Magma;
}

static const u8 *ExpandPlaceholder_Archie(void)
{
    return gText_ExpandedPlaceholder_Archie;
}

static const u8 *ExpandPlaceholder_Maxie(void)
{
    return gText_ExpandedPlaceholder_Maxie;
}

static const u8 *ExpandPlaceholder_Kyogre(void)
{
    return gText_ExpandedPlaceholder_Kyogre;
}

static const u8 *ExpandPlaceholder_Groudon(void)
{
    return gText_ExpandedPlaceholder_Groudon;
}

static const u8 *ExpandPlaceholder_Region(void)
{
    if (IS_HNS)
        return FlagGet(FLAG_VISITED_KANTO) ? gText_JohtoKanto : gText_Johto;
    else if (IS_FRLG)
        return gText_Kanto;
    else
        return gText_Hoenn;
}

const u8 *GetExpandedPlaceholder(u32 id)
{
    typedef const u8 *(*ExpandPlaceholderFunc)(void);

    static const ExpandPlaceholderFunc funcs[] =
    {
        [PLACEHOLDER_ID_UNKNOWN]      = ExpandPlaceholder_UnknownStringVar,
        [PLACEHOLDER_ID_PLAYER]       = ExpandPlaceholder_PlayerName,
        [PLACEHOLDER_ID_STRING_VAR_1] = ExpandPlaceholder_StringVar1,
        [PLACEHOLDER_ID_STRING_VAR_2] = ExpandPlaceholder_StringVar2,
        [PLACEHOLDER_ID_STRING_VAR_3] = ExpandPlaceholder_StringVar3,
        [PLACEHOLDER_ID_KUN]          = ExpandPlaceholder_KunChan,
        [PLACEHOLDER_ID_RIVAL]        = ExpandPlaceholder_RivalName,
        [PLACEHOLDER_ID_VERSION]      = ExpandPlaceholder_Version,
        [PLACEHOLDER_ID_AQUA]         = ExpandPlaceholder_Aqua,
        [PLACEHOLDER_ID_MAGMA]        = ExpandPlaceholder_Magma,
        [PLACEHOLDER_ID_ARCHIE]       = ExpandPlaceholder_Archie,
        [PLACEHOLDER_ID_MAXIE]        = ExpandPlaceholder_Maxie,
        [PLACEHOLDER_ID_KYOGRE]       = ExpandPlaceholder_Kyogre,
        [PLACEHOLDER_ID_GROUDON]      = ExpandPlaceholder_Groudon,
        [PLACEHOLDER_ID_REGION]       = ExpandPlaceholder_Region,
    };

    if (id >= ARRAY_COUNT(funcs))
        return gText_ExpandedPlaceholder_Empty;
    else
        return funcs[id]();
}

u8 *StringFill(u8 *dest, u8 c, u16 n)
{
    u32 i;

    for (i = 0; i < n; i++)
        *dest++ = c;

    *dest = EOS;
    return dest;
}

u8 *StringCopyPadded(u8 *dest, const u8 *src, u8 c, u16 n)
{
#if RTL_STRING_REPORT
    RtlStringReport(src);
#endif
    while (*src != EOS)
    {
        *dest++ = *src++;

        if (n)
            n--;
    }

    n--;

    while (n != (u16)-1)
    {
        *dest++ = c;
        n--;
    }

    *dest = EOS;
    return dest;
}

u8 *StringFillWithTerminator(u8 *dest, u16 n)
{
    return StringFill(dest, EOS, n);
}

u8 *StringCopyN_Multibyte(u8 *dest, u8 *src, u32 n)
{
#if RTL_STRING_REPORT
    RtlStringReport(src);
#endif
    u32 i;

    for (i = n - 1; i != (u32)-1; i--)
    {
        if (*src == EOS)
        {
            break;
        }
        else
        {
            *dest++ = *src++;
            if (*(src - 1) == CHAR_EXTRA_SYMBOL)
                *dest++ = *src++;
        }
    }

    *dest = EOS;
    return dest;
}

u32 StringLength_Multibyte(const u8 *str)
{
    u32 length = 0;

    while (*str != EOS)
    {
        if (*str == CHAR_EXTRA_SYMBOL)
            str++;
        str++;
        length++;
    }

    return length;
}

u8 *WriteColorChangeControlCode(u8 *dest, enum TextColorType colorType, u8 color)
{
    *dest = EXT_CTRL_CODE_BEGIN;
    dest++;

    switch (colorType)
    {
    case TEXT_COLOR_TYPE_FOREGROUND:
        *dest = EXT_CTRL_CODE_COLOR;
        dest++;
        break;
    case TEXT_COLOR_TYPE_SHADOW:
        *dest = EXT_CTRL_CODE_SHADOW;
        dest++;
        break;
    case TEXT_COLOR_TYPE_HIGHLIGHT:
        *dest = EXT_CTRL_CODE_HIGHLIGHT;
        dest++;
        break;
    case TEXT_COLOR_TYPE_ACCENT:
        *dest = EXT_CTRL_CODE_ACCENT;
        dest++;
        break;
    case TEXT_COLOR_TYPE_BACKGROUND:
        *dest = EXT_CTRL_CODE_BACKGROUND;
        dest++;
        break;
    }

    *dest = color;
    dest++;
    *dest = EOS;
    return dest;
}

bool32 IsStringJapanese(u8 *str)
{
    while (*str != EOS)
    {
        // Hebrew letters sit below JAPANESE_CHAR_END too, but they are not kana.
        if (*str <= JAPANESE_CHAR_END && !IS_HEBREW_CHAR(*str))
            if (*str != CHAR_SPACE)
                return TRUE;
        str++;
    }

    return FALSE;
}

bool32 IsStringNJapanese(u8 *str, s32 n)
{
    s32 i;

    for (i = 0; *str != EOS && i < n; i++)
    {
        if (*str <= JAPANESE_CHAR_END && !IS_HEBREW_CHAR(*str))
            if (*str != CHAR_SPACE)
                return TRUE;
        str++;
    }

    return FALSE;
}

u8 GetExtCtrlCodeLength(u8 code)
{
    static const u8 lengths[] =
    {
        [0]                                    = 1,
        [EXT_CTRL_CODE_COLOR]                  = 2,
        [EXT_CTRL_CODE_HIGHLIGHT]              = 2,
        [EXT_CTRL_CODE_SHADOW]                 = 2,
        [EXT_CTRL_CODE_COLOR_HIGHLIGHT_SHADOW] = 4,
        [EXT_CTRL_CODE_PALETTE]                = 2,
        [EXT_CTRL_CODE_FONT]                   = 2,
        [EXT_CTRL_CODE_RESET_FONT]             = 1,
        [EXT_CTRL_CODE_PAUSE]                  = 2,
        [EXT_CTRL_CODE_PAUSE_UNTIL_PRESS]      = 1,
        [EXT_CTRL_CODE_WAIT_SE]                = 1,
        [EXT_CTRL_CODE_PLAY_BGM]               = 3,
        [EXT_CTRL_CODE_ESCAPE]                 = 2,
        [EXT_CTRL_CODE_SHIFT_RIGHT]            = 2,
        [EXT_CTRL_CODE_SHIFT_DOWN]             = 2,
        [EXT_CTRL_CODE_FILL_WINDOW]            = 1,
        [EXT_CTRL_CODE_PLAY_SE]                = 3,
        [EXT_CTRL_CODE_CLEAR]                  = 2,
        [EXT_CTRL_CODE_SKIP]                   = 2,
        [EXT_CTRL_CODE_CLEAR_TO]               = 2,
        [EXT_CTRL_CODE_MIN_LETTER_SPACING]     = 2,
        [EXT_CTRL_CODE_JPN]                    = 1,
        [EXT_CTRL_CODE_ENG]                    = 1,
        [EXT_CTRL_CODE_PAUSE_MUSIC]            = 1,
        [EXT_CTRL_CODE_RESUME_MUSIC]           = 1,
        [EXT_CTRL_CODE_SPEAKER]                = 1,
        [EXT_CTRL_CODE_ACCENT]                 = 2,
        [EXT_CTRL_CODE_BACKGROUND]             = 2,
        [EXT_CTRL_CODE_TEXT_COLORS]            = 4,
    };

    u8 length = 0;
    if (code < ARRAY_COUNT(lengths))
        length = lengths[code];
    return length;
}

static const u8 *SkipExtCtrlCode(const u8 *s)
{
    while (*s == EXT_CTRL_CODE_BEGIN)
    {
        s++;
        s += GetExtCtrlCodeLength(*s);
    }

    return s;
}

s32 StringCompareWithoutExtCtrlCodes(const u8 *str1, const u8 *str2)
{
    s32 retVal = 0;

    while (1)
    {
        str1 = SkipExtCtrlCode(str1);
        str2 = SkipExtCtrlCode(str2);

        if (*str1 > *str2)
            break;

        if (*str1 < *str2)
        {
            retVal = -1;
            if (*str2 == EOS)
                retVal = 1;
        }

        if (*str1 == EOS)
            return retVal;

        str1++;
        str2++;
    }

    retVal = 1;

    if (*str1 == EOS)
        retVal = -1;

    return retVal;
}

void ConvertInternationalString(u8 *s, enum Language language)
{
    if (language == LANGUAGE_JAPANESE)
    {
        u32 i;

        StripExtCtrlCodes(s);
        i = StringLength(s);
        s[i++] = EXT_CTRL_CODE_BEGIN;
        s[i++] = EXT_CTRL_CODE_ENG;
        s[i++] = EOS;

        i--;

        while (i != -1)
        {
            s[i + 2] = s[i];
            i--;
        }

        s[0] = EXT_CTRL_CODE_BEGIN;
        s[1] = EXT_CTRL_CODE_JPN;
    }
}

void StripExtCtrlCodes(u8 *str)
{
    u16 srcIndex = 0;
    u16 destIndex = 0;
    while (str[srcIndex] != EOS)
    {
        if (str[srcIndex] == EXT_CTRL_CODE_BEGIN)
        {
            srcIndex++;
            srcIndex += GetExtCtrlCodeLength(str[srcIndex]);
        }
        else
        {
            str[destIndex++] = str[srcIndex++];
        }
    }
    str[destIndex] = EOS;
}

u8 *StringCopyUppercase(u8 *dest, const u8 *src)
{
#if RTL_STRING_REPORT
    RtlStringReport(src);
#endif
    while (*src != EOS)
    {
        if (*src >= CHAR_a && *src <= CHAR_z)
            *dest = gCaseToggleTable[*src];
        else
            *dest = *src;
        dest++;
        src++;
    }

    *dest = EOS;
    return dest;
}

bool32 DoesStringProperlyTerminate(const u8 *str, u32 last)
{
    for (u32 i = 0; i < last; i++)
    {
        if (str[i] == EOS)
            return TRUE;
    }

    return FALSE;
}

#if RTL_STRING_REPORT
// Linked with --wrap (Makefile): every call from another file to these printers in text.c comes
// here first.
bool32 __real_AddTextPrinter(struct TextPrinterTemplate *printerTemplate, u8 speed, void (*callback)(struct TextPrinterTemplate *, u16));
u16 __real_AddTextPrinterParameterized(u8 windowId, u8 fontId, const u8 *str, u8 x, u8 y, u8 speed, void (*callback)(struct TextPrinterTemplate *, u16));
u16 __real_AddSpriteTextPrinterParametrerized(u8 spriteId, u8 fontId, const u8 *str, u8 x, u8 y, u8 speed, void (*callback)(struct TextPrinterTemplate *, u16));
void __real_AddSpriteTextPrinterParameterized3(u8 spriteId, u8 fontId, u8 left, u8 top, const u8 *color, s8 speed, const u8 *str);
void __real_AddSpriteTextPrinterParameterized4(u8 spriteId, u8 fontId, u8 left, u8 top, u8 letterSpacing, u8 lineSpacing, const u8 *color, s8 speed, const u8 *str);
void __real_AddSpriteTextPrinterParameterized6(u8 spriteId, u8 fontId, u8 left, u8 top, u8 letterSpacing, u8 lineSpacing, const union TextColor color, s8 speed, const u8 *str);
u8 __real_RenderTextHandleBold(u8 *pixels, u8 fontId, u8 *str);

bool32 __wrap_AddTextPrinter(struct TextPrinterTemplate *printerTemplate, u8 speed, void (*callback)(struct TextPrinterTemplate *, u16))
{
    RtlStringReport(printerTemplate->currentChar);
    return __real_AddTextPrinter(printerTemplate, speed, callback);
}

u16 __wrap_AddTextPrinterParameterized(u8 windowId, u8 fontId, const u8 *str, u8 x, u8 y, u8 speed, void (*callback)(struct TextPrinterTemplate *, u16))
{
    RtlStringReport(str);
    return __real_AddTextPrinterParameterized(windowId, fontId, str, x, y, speed, callback);
}

u16 __wrap_AddSpriteTextPrinterParametrerized(u8 spriteId, u8 fontId, const u8 *str, u8 x, u8 y, u8 speed, void (*callback)(struct TextPrinterTemplate *, u16))
{
    RtlStringReport(str);
    return __real_AddSpriteTextPrinterParametrerized(spriteId, fontId, str, x, y, speed, callback);
}

void __wrap_AddSpriteTextPrinterParameterized3(u8 spriteId, u8 fontId, u8 left, u8 top, const u8 *color, s8 speed, const u8 *str)
{
    RtlStringReport(str);
    __real_AddSpriteTextPrinterParameterized3(spriteId, fontId, left, top, color, speed, str);
}

void __wrap_AddSpriteTextPrinterParameterized4(u8 spriteId, u8 fontId, u8 left, u8 top, u8 letterSpacing, u8 lineSpacing, const u8 *color, s8 speed, const u8 *str)
{
    RtlStringReport(str);
    __real_AddSpriteTextPrinterParameterized4(spriteId, fontId, left, top, letterSpacing, lineSpacing, color, speed, str);
}

void __wrap_AddSpriteTextPrinterParameterized6(u8 spriteId, u8 fontId, u8 left, u8 top, u8 letterSpacing, u8 lineSpacing, const union TextColor color, s8 speed, const u8 *str)
{
    RtlStringReport(str);
    __real_AddSpriteTextPrinterParameterized6(spriteId, fontId, left, top, letterSpacing, lineSpacing, color, speed, str);
}

u8 __wrap_RenderTextHandleBold(u8 *pixels, u8 fontId, u8 *str)
{
    RtlStringReport(str);
    return __real_RenderTextHandleBold(pixels, fontId, str);
}
#endif
