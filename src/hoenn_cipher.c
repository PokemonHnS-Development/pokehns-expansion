// Hoenn & Seek 2.0 parts 27-28: the Unown Cipher at the Ruins of Alph (plan
// section 8). The scenes are scripts (data/scripts/hoenn_cipher.inc); this file
// draws the Words rooms' new floor lines and answers the scripts' questions.
//
// Part 27a:
// - The cipher OPENS once all four panels (Kabuto, Omanyte, Aerodactyl, Ho-Oh)
//   are solved and you've been to Hoenn (any Hoenn town's visited flag, or the
//   Tidal Strait crossed).
// - Then Words Room 1 shows a Rosetta line: Hoenn braille cells on the dark
//   strip under the north wall (row 2) and, under each cell, the same letter in
//   Unown (row 3): AT NIGHT WE SPEAK. Reading the braille sets
//   FLAG_HOENN_CIPHER_ROSETTA (you can read Unown from then on).
// - With the Rosetta read, at night (HnS's TIME_NIGHT), Words Rooms 2-4 show a
//   glowing word on row 3 that changes by weekday. Each word names a place for
//   part 27b's glyph sites: Sun TOWER, Mon MOON, Tue ICE, Wed WHIRL, Thu MORTAR,
//   Fri UNION, Sat FOAM. FLAG_HOENN_CIPHER_WORD_SUN + weekday records it.
// The braille and glowing-letter blocks come from
// tools/hoenn/gen_hoenn_unown_tiles.py (src/data/hoenn_unown_tiles.h).
#include "global.h"
#include "event_data.h"
#include "fieldmap.h"
#include "rtc.h"
#include "string_util.h"
#include "constants/characters.h"
#include "constants/rtc.h"
#include "hoenn.h"

#if IS_HNS
#include "constants/hoenn_custom.h"
#include "constants/hoenn_events.h"
#include "constants/hoenn_phone.h"
#include "data/hoenn_unown_tiles.h"

// The floor's own Unown letter blocks (gTileset_RuinsOfAlphWriting_Hns): four
// rows of seven, A-G, H-N, O-U, V-Z ! ?, each row starting on a multiple of 8.
#define UNOWN_LETTER_METATILE(i) (0x310 + ((i) / 7) * 8 + (i) % 7)

#define WORDS_ROOM_FIRST_X 2   // the floor's first column (x 1 is its shaded edge)
#define WORDS_ROOM_WIDTH   17  // x 2-18
#define ROSETTA_BRAILLE_Y  2
#define ROSETTA_UNOWN_Y    3
#define NIGHT_WORD_Y       3   // Rooms 2-4: the free row above the inscription

static const u8 sRosetta[] = _("AT NIGHT WE SPEAK");

static const u8 sWordTower[]  = _("TOWER");
static const u8 sWordMoon[]   = _("MOON");
static const u8 sWordIce[]    = _("ICE");
static const u8 sWordWhirl[]  = _("WHIRL");
static const u8 sWordMortar[] = _("MORTAR");
static const u8 sWordUnion[]  = _("UNION");
static const u8 sWordFoam[]   = _("FOAM");

// Indexed by GetDayOfWeek() (HOENN_SUNDAY = 0).
static const u8 *const sNightWords[] = {
    sWordTower, sWordMoon, sWordIce, sWordWhirl, sWordMortar, sWordUnion, sWordFoam,
};

static const u16 sHoennVisitedFlags[] = {
    FLAG_VISITED_LITTLEROOT_TOWN, FLAG_VISITED_OLDALE_TOWN, FLAG_VISITED_DEWFORD_TOWN,
    FLAG_VISITED_LAVARIDGE_TOWN, FLAG_VISITED_FALLARBOR_TOWN, FLAG_VISITED_VERDANTURF_TOWN,
    FLAG_VISITED_PACIFIDLOG_TOWN, FLAG_VISITED_PETALBURG_CITY, FLAG_VISITED_SLATEPORT_CITY,
    FLAG_VISITED_MAUVILLE_CITY, FLAG_VISITED_RUSTBORO_CITY, FLAG_VISITED_FORTREE_CITY,
    FLAG_VISITED_LILYCOVE_CITY, FLAG_VISITED_MOSSDEEP_CITY, FLAG_VISITED_SOOTOPOLIS_CITY,
    FLAG_VISITED_EVER_GRANDE_CITY, FLAG_HOENN_CROSSED_STRAIT,
};

// A-Z -> 0-25; anything else (the space) -> -1.
static s32 LetterIndex(u8 c)
{
    if (c >= CHAR_A && c <= CHAR_Z)
        return c - CHAR_A;
    return -1;
}

static void SetFloorBlock(s32 x, s32 y, u16 metatile)
{
    MapGridSetMetatileIdAt(x + MAP_OFFSET, y + MAP_OFFSET, metatile);
}

static bool32 IsNightNow(void)
{
    return GetTimeOfDay() == TIME_NIGHT;
}

// specialvar VAR_RESULT, HoennCipherIsOpen
bool8 HoennCipherIsOpen(void)
{
    u32 i;

    if (!FlagGet(FLAG_COMPLETED_KABUTO_PUZZLE) || !FlagGet(FLAG_COMPLETED_OMANYTE_PUZZLE)
     || !FlagGet(FLAG_COMPLETED_AERODACTYL_PUZZLE) || !FlagGet(FLAG_COMPLETED_HOOH_PUZZLE))
        return FALSE;
    for (i = 0; i < ARRAY_COUNT(sHoennVisitedFlags); i++)
        if (FlagGet(sHoennVisitedFlags[i]))
            return TRUE;
    return FALSE;
}

// Whether tonight's word shows: the cipher is open, the Rosetta was read and
// it's night.
static bool32 NightWordShows(void)
{
    return HoennCipherIsOpen() && FlagGet(FLAG_HOENN_CIPHER_ROSETTA) && IsNightNow();
}

// special HoennCipherDrawRoom (VAR_0x8004 = Words room 1-4), from each room's
// ON_LOAD: draws the Rosetta line (room 1) or tonight's word (rooms 2-4).
void HoennCipherDrawRoom(void)
{
    u32 i, len;

    if (!HoennCipherIsOpen())
        return;

    if (gSpecialVar_0x8004 == 1)
    {
        for (i = 0; sRosetta[i] != EOS; i++)
        {
            s32 letter = LetterIndex(sRosetta[i]);
            if (letter < 0)
                continue;
            SetFloorBlock(WORDS_ROOM_FIRST_X + i, ROSETTA_BRAILLE_Y, sHoennUnownBraille[letter]);
            SetFloorBlock(WORDS_ROOM_FIRST_X + i, ROSETTA_UNOWN_Y, UNOWN_LETTER_METATILE(letter));
        }
        return;
    }

    if (!NightWordShows())
        return;
    {
        const u8 *word = sNightWords[GetDayOfWeek() % ARRAY_COUNT(sNightWords)];
        s32 x0;

        len = StringLength(word);
        x0 = WORDS_ROOM_FIRST_X + (WORDS_ROOM_WIDTH - len) / 2;
        for (i = 0; i < len; i++)
        {
            s32 letter = LetterIndex(word[i]);
            if (letter >= 0 && sHoennUnownGlow[letter] != 0)
                SetFloorBlock(x0 + i, NIGHT_WORD_Y, sHoennUnownGlow[letter]);
        }
    }
}

// specialvar VAR_RESULT, HoennCipherTonightWord: HOENN_CIPHER_NO_WORD if no
// word shows now, else HOENN_CIPHER_NEW_WORD / HOENN_CIPHER_SEEN_WORD (this
// weekday's word was already noted). The word goes in STR_VAR_1.
u16 HoennCipherTonightWord(void)
{
    u32 day;

    if (!NightWordShows())
        return HOENN_CIPHER_NO_WORD;
    day = GetDayOfWeek() % ARRAY_COUNT(sNightWords);
    StringCopy(gStringVar1, sNightWords[day]);
    return FlagGet(FLAG_HOENN_CIPHER_WORD_SUN + day) ? HOENN_CIPHER_SEEN_WORD : HOENN_CIPHER_NEW_WORD;
}

// special HoennCipherNoteWord: records tonight's weekday word as seen (flag
// commands can't take a computed flag).
void HoennCipherNoteWord(void)
{
    if (NightWordShows())
        FlagSet(FLAG_HOENN_CIPHER_WORD_SUN + GetDayOfWeek() % ARRAY_COUNT(sNightWords));
}

// specialvar VAR_RESULT, HoennCipherWordCount: how many of the seven words were
// noted. STR_VAR_1 gets the count, STR_VAR_2 the words in weekday order
// ("MOON, ICE"), for the lab researcher. The text box doesn't wrap, so a new
// line starts after every third word: six words ("TOWER, MOON, ICE, WHIRL,
// MORTAR, UNION") ran far past the box's edge on one line (review, Nov 27).
#define CIPHER_WORDS_PER_LINE 3
u16 HoennCipherWordCount(void)
{
    u32 i, count = 0;
    u8 *end = gStringVar2;

    *end = EOS;
    for (i = 0; i < ARRAY_COUNT(sNightWords); i++)
    {
        if (!FlagGet(FLAG_HOENN_CIPHER_WORD_SUN + i))
            continue;
        if (count != 0)
        {
            *end++ = CHAR_COMMA;
            // The researcher's text puts the list on its own line, so the
            // next one scrolls up (\l).
            *end++ = (count % CIPHER_WORDS_PER_LINE == 0) ? CHAR_PROMPT_SCROLL : CHAR_SPACE;
        }
        end = StringCopy(end, sNightWords[i]);
        count++;
    }
    ConvertIntToDecimalStringN(gStringVar1, count, STR_CONV_MODE_LEFT_ALIGN, 1);
    return count;
}

// Brendan's call: the lab phoned Birch about the braille. Due once the cipher
// is open, until you've been told (by the call or the lab) or read the wall.
u16 HoennCipherDueCall(void)
{
    if (!FlagGet(FLAG_HOENN_CALL_CIPHER) && !FlagGet(FLAG_HOENN_CIPHER_ASKED)
     && !FlagGet(FLAG_HOENN_CIPHER_ROSETTA) && HoennCipherIsOpen())
        return HOENN_CALL_CIPHER;
    return HOENN_CALL_NONE;
}

#endif // IS_HNS
