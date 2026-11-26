// Hoenn & Seek 2.0 (part 2): weekday, weekly reset and weather-cycle helpers.
//
// Most 2.0 events are tied to a time, a weekday or the weather ("Lapras on
// Fridays", "Absol on Route 120's storm day"), so these are the building blocks
// every later part uses. Nothing here adds content on its own.
//
// THE WEEKDAY
//   The GBA clock has no idea what day it really is: the game counts days from
//   when the clock was set, and day 0 is a Saturday (gGen3Epoch, src/datetime.c).
//   So HnS's "Monday" is usually not the real Monday. Instead of moving the day
//   counter (which would run the daily resets and grow every berry), the save
//   keeps a weekday offset, VAR_HOENN_WEEKDAY_OFFSET (0-6), and GetDayOfWeek()
//   in src/rtc.c adds it through HoennAdjustWeekday(). Everything that asks for
//   the weekday (scripts, the PokéGear radio) sees the same day.
//   Part 3 adds the places a player sets it (the new-game clock scene and the
//   New Bark wall clock); both go through HoennSetWeekday(). The title
//   screen's reset-clock screen only re-records the week (see below).
//
// THE WEEK
//   Weekly flags (HOENN_WEEKLY_FLAGS_START-END, part 1) reset when a new week
//   starts, on HOENN_WEEK_STARTS_ON (Sunday). HoennUpdatePerWeek() runs with
//   HnS's daily update (DoTimeBasedEvents, src/clock.c) and works the same way
//   as HnS's daily flags: it remembers the week it last saw, resets when the
//   week number goes up, and just re-records it if the clock went backwards.
//   Changing the weekday offset is not a new week (HoennSetWeekday re-records
//   the week), so a player can't reset weekly events by fiddling with the day.
//
// THE WEATHER CYCLE
//   Emerald steps Routes 119 and 123 through a 4-day weather cycle
//   (gSaveBlock1Ptr->weatherCycleStage, advanced once a day). Part 5 puts most
//   routes on cycles of their own, each with one "special weather" day in four.
//   Events ask HoennIsSpecialWeatherDay() instead of reading the stage.
//   Part 5: 78 routes are on cycles (data/hoenn/weather_cycles.json). A map's
//   special day is the day (stage + its offset) % 4 == 2; that day the map
//   starts in its special weather (HoennCycleMapWeather, hooked where the map
//   header's weather is applied) and its weather zones are skipped
//   (HoennCycleIgnoresWeatherZones). Routes 119 and 123 keep Emerald's cycles.

#include "global.h"
#include "clock.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_weather.h"
#include "hoenn_flags.h"
#include "wild_encounter.h"
#include "hoenn_time.h"
#include "overworld.h"
#include "rtc.h"
#include "string_util.h"
#include "strings.h"
#include "constants/hoenn_events.h"
#include "constants/weather.h"
#include "constants/characters.h"
#include "constants/map_groups.h"
#include "fieldmap.h"

#if IS_HNS

// Emerald's cycle length (WEATHER_CYCLE_LENGTH is private to field_weather_effect.c).
#define HOENN_WEATHER_CYCLE_LENGTH 4

STATIC_ASSERT(HOENN_TIME_NIGHT == TIME_NIGHT, HoennTimeNightMatches);

// Scripts compare GetDayOfWeek's result with HOENN_SUNDAY..HOENN_SATURDAY.
STATIC_ASSERT(HOENN_SUNDAY == WEEKDAY_SUN && HOENN_SATURDAY == WEEKDAY_SAT
           && WEEKDAY_COUNT == 7, HoennWeekdayConstantsMatchEnum);
STATIC_ASSERT(HOENN_SPECIAL_WEATHER_STAGE < HOENN_WEATHER_CYCLE_LENGTH, HoennSpecialStageInCycle);
// The emulator harness (tools/hoenn/emu/pt.py) pokes these at fixed offsets.
STATIC_ASSERT(offsetof(struct SaveBlock1, weatherCycleStage) == 0x33, HoennHarnessWeatherStageOffset);
STATIC_ASSERT(offsetof(struct SaveBlock1, weather) == 0x32, HoennHarnessWeatherOffset);
STATIC_ASSERT(offsetof(struct SaveBlock2, localTimeOffset) == 0x98, HoennHarnessTimeOffsetOffset);

// ---- Weekday ----------------------------------------------------------------

static u32 WeekdayOffset(void)
{
    return VarGet(VAR_HOENN_WEEKDAY_OFFSET) % WEEKDAY_COUNT;
}

// Called by GetDayOfWeek() with the RTC's own weekday.
u32 HoennAdjustWeekday(u32 rtcWeekday)
{
    return (rtcWeekday + WeekdayOffset()) % WEEKDAY_COUNT;
}

// The weekday (with the offset) of a local day count. Day 0 is the epoch's
// Saturday; ConvertTimeToDateTime treats negative day counts as day 0.
static u32 WeekdayOfLocalDay(s32 localDays)
{
    if (localDays < 0)
        localDays = 0;
    return (WEEKDAY_SAT + localDays + WeekdayOffset()) % WEEKDAY_COUNT;
}

// Days since the start of the week (0 on HOENN_WEEK_STARTS_ON).
static u32 DayInWeek(s32 localDays)
{
    return (WeekdayOfLocalDay(localDays) + WEEKDAY_COUNT - HOENN_WEEK_STARTS_ON) % WEEKDAY_COUNT;
}

// Which week a local day count falls in: 0 for the first (partial) week, then
// up by one every time the week starts over.
static u32 WeekOfLocalDay(s32 localDays)
{
    if (localDays < 0)
        localDays = 0;
    // Day 0 is DayInWeek(0) days into week 0, so count from that week's start.
    return (localDays + DayInWeek(0)) / WEEKDAY_COUNT;
}

// Runs from DoTimeBasedEvents() with the local day count, right after HnS's
// daily update. Stores week + 1 so that 0 means "nothing recorded yet" (a new
// game, or a 1.0 save that just got its 2.0 vars cleared).
void HoennUpdatePerWeek(s32 localDays)
{
    u16 *seen = GetVarPointer(VAR_HOENN_WEEK_SEEN);
    u16 week = WeekOfLocalDay(localDays) + 1;

    if (*seen != 0 && week > *seen)
        HoennClearWeeklyFlags();
    // A smaller week means the clock was set back: record it without a reset,
    // like HnS does for VAR_DAYS.
    *seen = week;
}

// Makes today the given weekday (WEEKDAY_*), without starting a new week.
void HoennSetWeekday(u32 weekday)
{
    s32 days;

    RtcCalcLocalTime();
    days = gLocalTime.days;
    // Let a week that already ended reset first, so changing the day can't
    // swallow a reset that was due.
    HoennUpdatePerWeek(days);
    // Offset that turns the RTC's weekday for today into the wanted one.
    VarSet(VAR_HOENN_WEEKDAY_OFFSET, 0);
    VarSet(VAR_HOENN_WEEKDAY_OFFSET, (weekday % WEEKDAY_COUNT + WEEKDAY_COUNT - WeekdayOfLocalDay(days)) % WEEKDAY_COUNT);
    // The week number moves with the offset; record the new one so the next
    // time check doesn't count it as a new week.
    VarSet(VAR_HOENN_WEEK_SEEN, WeekOfLocalDay(days) + 1);
}

// Part 3: the title screen's reset-clock screen (src/reset_rtc_screen.c) just
// set a new time. HnS records the new day count there without running the
// daily reset (VarSet(VAR_DAYS, ...)), so a reset clock never hands out a free
// new day. Do the same for the week: record it, don't reset the weekly flags.
// The weekday offset stays, so the weekday moves with the day count.
// (That screen only opens after a Mystery Event enables it, as in Emerald, so
// it has no weekday row of its own; the New Bark wall clock changes the day.)
void HoennRecordWeekAfterClockReset(void)
{
    VarSet(VAR_HOENN_WEEK_SEEN, WeekOfLocalDay(gLocalTime.days) + 1);
}

static const u8 *const sWeekdayNames[WEEKDAY_COUNT] = {
    gText_Sunday, gText_Monday, gText_Tuesday, gText_Wednesday,
    gText_Thursday, gText_Friday, gText_Saturday,
};

// special HoennBufferWeekdayName: today's name ("MONDAY") in STR_VAR_1.
void HoennBufferWeekdayName(void)
{
    StringCopy(gStringVar1, sWeekdayNames[GetDayOfWeek()]);
}

// Part 3: today's short name ("MON ") at dest, for the start-menu clock.
// Returns the end of the string, so the time can be written right after it.
u8 *HoennWriteWeekdayAbbrev(u8 *dest)
{
    dest = StringCopyN(dest, sWeekdayNames[GetDayOfWeek()], 3);
    *dest++ = CHAR_SPACE;
    *dest = EOS;
    return dest;
}

// specialvar VAR_RESULT, HoennIsItWeekday (part 3)
// VAR_0x8004 = HOENN_SUNDAY..HOENN_SATURDAY. Puts that day's name in STR_VAR_1
// and returns TRUE if today is that day. Made for HGSS-style "only on my day"
// NPCs, such as the Weekday siblings, so their text can name the day either way.
bool16 HoennIsItWeekday(void)
{
    u32 day = gSpecialVar_0x8004 % WEEKDAY_COUNT;
    StringCopy(gStringVar1, sWeekdayNames[day]);
    return GetDayOfWeek() == day;
}

// special HoennSetWeekdayFromChoice (part 3): the player answered "What day is
// it?" (MULTI_DAYS_OF_WEEK, VAR_RESULT = 0-6). Anything else (EXIT or B)
// leaves the day alone. Used by New Bark's wall clock.
void HoennSetWeekdayFromChoice(void)
{
    if (gSpecialVar_Result < WEEKDAY_COUNT)
        HoennSetWeekday(gSpecialVar_Result);
}

// ---- Weather cycle ------------------------------------------------------------

// specialvar VAR_RESULT, HoennGetWeatherCycleStage: today's stage, 0-3.
u16 HoennGetWeatherCycleStage(void)
{
    return gSaveBlock1Ptr->weatherCycleStage;
}

// The maps with a weather cycle (part 5): generated from
// data/hoenn/weather_cycles.json by tools/hoenn/gen_hoenn_weather.py.
//   weather: the special-day weather (WEATHER_RAIN, ...). For Emerald's two
//            cycle routes it's their cycle (WEATHER_ROUTE119_CYCLE), which
//            field_weather_effect.c translates per stage in their weather zones.
//   offset:  days added to weatherCycleStage, so groups of routes have their
//            special day on different days.
//   emerald: Routes 119 and 123. Their map headers and zones already run
//            Emerald's cycle, so HoennCycleMapWeather leaves them alone; they're
//            here so events can ask about their special day.
// Any other map in the table shows its header weather three days in four and
// its special weather on the fourth, everywhere on the map.
static const struct {
    u16 map;    // MAP_* (num | group << 8)
    u8 weather;
    u8 offset;
    bool8 emerald;
} sWeatherCycleMaps[] = {
#include "data/hoenn_weather_cycles.h"
};

static s32 FindWeatherCycleMap(u16 mapGroup, u16 mapNum)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sWeatherCycleMaps); i++)
        if (sWeatherCycleMaps[i].map == (mapNum | (mapGroup << 8)))
            return i;
    return -1;
}

// Today's stage of a map's own cycle, or -1 if the map has no weather cycle.
static s32 MapCycleStage(u16 mapGroup, u16 mapNum)
{
    s32 i = FindWeatherCycleMap(mapGroup, mapNum);

    if (i < 0)
        return -1;
    return (gSaveBlock1Ptr->weatherCycleStage + sWeatherCycleMaps[i].offset) % HOENN_WEATHER_CYCLE_LENGTH;
}

// TRUE if today is the special-weather day of that map's cycle (the storm day,
// the heavy rain day...). FALSE for maps without a cycle.
bool32 HoennIsSpecialWeatherDay(u16 mapGroup, u16 mapNum)
{
    return MapCycleStage(mapGroup, mapNum) == HOENN_SPECIAL_WEATHER_STAGE;
}

// Hook in SetSavedWeatherFromCurrMapHeader (src/field_weather_effect.c): the
// weather a map starts with. On a cycle map's special day it's the special
// weather; otherwise the header's own.
u8 HoennCycleMapWeather(u8 headerWeather)
{
    s32 i = FindWeatherCycleMap(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum);

    if (i < 0 || sWeatherCycleMaps[i].emerald || !HoennIsSpecialWeatherDay(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum))
        return headerWeather;
    return sWeatherCycleMaps[i].weather;
}

// Hook in DoCoordEventWeather (src/coord_event_weather.c): TRUE skips a weather
// zone. On a cycle map's special day the special weather covers the whole map
// (Route 120's sunny and rain patches would otherwise turn the storm off).
bool32 HoennCycleIgnoresWeatherZones(void)
{
    s32 i = FindWeatherCycleMap(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum);

    return i >= 0 && !sWeatherCycleMaps[i].emerald
        && HoennIsSpecialWeatherDay(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum);
}

// Hook in GetCurrentMapWildMonHeaderId (src/wild_encounter.c), part 6a. The
// weather tables (data/hoenn/wild_encounters_weather.json) are extra headers
// for the same map, after every normal one. On the map's special day the first
// later header for the map is used; any other day, or with no weather table,
// the normal one.
u16 HoennWeatherWildHeader(u16 headerId)
{
    u32 i;
    const struct WildPokemonHeader *base = &gWildMonHeaders[headerId];

    if (!HoennIsSpecialWeatherDay(base->mapGroup, base->mapNum))
        return headerId;
    for (i = headerId + 1; gWildMonHeaders[i].mapGroup != MAP_GROUP(MAP_UNDEFINED); i++)
        if (gWildMonHeaders[i].mapGroup == base->mapGroup && gWildMonHeaders[i].mapNum == base->mapNum)
            return i;
    return headerId;
}

// specialvar VAR_RESULT, HoennIsSpecialWeatherHere: the map the player is on.
u16 HoennIsSpecialWeatherHere(void)
{
    return HoennIsSpecialWeatherDay(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum);
}

// setvar VAR_0x8004, MAP_ROUTE120
// specialvar VAR_RESULT, HoennIsSpecialWeatherOn
// For forecasts and hints about another map. MAP_* constants are num | group << 8.
u16 HoennIsSpecialWeatherOn(void)
{
    return HoennIsSpecialWeatherDay(gSpecialVar_0x8004 >> 8, gSpecialVar_0x8004 & 0xFF);
}

// ---- Debug menu ---------------------------------------------------------------
// Utilities → "H&S time & weather…" runs HoennDebug_EventScript_TimeWeather
// (data/scripts/hoenn_debug.inc), which calls these. They work with the real
// clock and with the fake RTC option alike.

// The two-line status box above the menu, e.g.
//   TUESDAY 14:05 (offset +3)
//   Week 1404, weather 2: special
// The last word is "special" or "normal" for today on this map's weather
// cycle, or "no cycle" on a map without one.
void HoennDebugBufferStatus(void)
{
    u8 *s = gStringVar4;

    RtcCalcLocalTime();
    HoennBufferWeekdayName();
    s = StringCopy(s, gStringVar1);
    *s++ = CHAR_SPACE;
    s = ConvertIntToDecimalStringN(s, gLocalTime.hours, STR_CONV_MODE_LEADING_ZEROS, 2);
    *s++ = CHAR_COLON;
    s = ConvertIntToDecimalStringN(s, gLocalTime.minutes, STR_CONV_MODE_LEADING_ZEROS, 2);
    s = StringCopy(s, COMPOUND_STRING(" (offset +"));
    s = ConvertIntToDecimalStringN(s, WeekdayOffset(), STR_CONV_MODE_LEFT_ALIGN, 1);
    s = StringCopy(s, COMPOUND_STRING(")\nWeek "));
    s = ConvertIntToDecimalStringN(s, WeekOfLocalDay(gLocalTime.days), STR_CONV_MODE_LEFT_ALIGN, 5);
    s = StringCopy(s, COMPOUND_STRING(", weather "));
    s = ConvertIntToDecimalStringN(s, HoennGetWeatherCycleStage(), STR_CONV_MODE_LEFT_ALIGN, 1);
    if (MapCycleStage(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum) < 0)
        StringCopy(s, COMPOUND_STRING(": no cycle"));
    else if (HoennIsSpecialWeatherHere())
        StringCopy(s, COMPOUND_STRING(": special"));
    else
        StringCopy(s, COMPOUND_STRING(": normal"));
}

// Starts the time checks on a save that never set the clock (debug saves skip
// New Bark's wall clock scene). Same as setting the wall clock to the current
// time: FLAG_SYS_CLOCK_SET, and today recorded as already seen.
void HoennDebugStartClock(void)
{
    InitTimeBasedEvents();
    RtcCalcLocalTime();
    HoennUpdatePerWeek(gLocalTime.days);
}

// VAR_0x8004 = WEEKDAY_* (the MULTI_DAYS_OF_WEEK choice)
void HoennDebugSetWeekday(void)
{
    HoennSetWeekday(gSpecialVar_0x8004);
}

// VAR_0x8004 = hour (0-23). Same day, minute 0. Going back an hour is fine:
// the daily update only counts whole days.
void HoennDebugSetHour(void)
{
    RtcCalcLocalTime();
    RtcCalcLocalTimeOffset(gLocalTime.days, gSpecialVar_0x8004 % HOURS_PER_DAY, 0, 0);
}

// Jumps to midnight at the start of next week. The next time check then runs
// the daily update for the skipped days and resets the weekly flags, exactly
// as if the days had passed.
void HoennDebugNextWeek(void)
{
    RtcCalcLocalTime();
    RtcCalcLocalTimeOffset(gLocalTime.days + WEEKDAY_COUNT - DayInWeek(gLocalTime.days), 0, 0, 0);
}

// One step through the 4-day cycle without changing the day. On a cycle map
// the weather switches to the cycle's weather for the new stage (the script
// runs doweather), even outside its weather zones, so the change shows at once.
// Elsewhere the weather is left alone.
void HoennDebugAdvanceWeatherStage(void)
{
    s32 i = FindWeatherCycleMap(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum);

    UpdateWeatherPerDay(1);
    if (i >= 0 && sWeatherCycleMaps[i].emerald)
        SetSavedWeather(sWeatherCycleMaps[i].weather);
    else if (i >= 0)
        SetSavedWeather(HoennCycleMapWeather(gMapHeader.weather));
}

// Reloads the current map where the player stands (like warpsilent), so
// day/night objects, weekday objects and map scripts see the new time.
// Follow it with waitstate in the script.
void HoennDebugReloadMap(void)
{
    struct ObjectEvent *player = &gObjectEvents[gPlayerAvatar.objectEventId];

    SetWarpDestination(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum, WARP_ID_NONE,
                       player->currentCoords.x - MAP_OFFSET, player->currentCoords.y - MAP_OFFSET);
    DoDiveWarp();
    ResetInitialPlayerAvatarState();
}

#endif // IS_HNS
