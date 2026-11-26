#ifndef GUARD_HOENN_TIME_H
#define GUARD_HOENN_TIME_H

// Hoenn & Seek 2.0 (parts 2 and 5): weekday, weekly reset and weather-cycle helpers.
// The code and the reasoning behind it are in src/hoenn_time.c; the vars and
// script constants are in constants/hoenn_events.h (part 2's section).

#if IS_HNS
// Hooks in upstream files (one line each)
u32 HoennAdjustWeekday(u32 rtcWeekday);  // GetDayOfWeek(), src/rtc.c
void HoennUpdatePerWeek(s32 localDays);  // DoTimeBasedEvents(), src/clock.c
void HoennRecordWeekAfterClockReset(void); // reset-clock screen, src/reset_rtc_screen.c
u8 HoennCycleMapWeather(u8 headerWeather);  // SetSavedWeatherFromCurrMapHeader(), src/field_weather_effect.c (part 5)
bool32 HoennCycleIgnoresWeatherZones(void); // DoCoordEventWeather(), src/coord_event_weather.c (part 5)

// For C callers
void HoennSetWeekday(u32 weekday);
bool32 HoennIsSpecialWeatherDay(u16 mapGroup, u16 mapNum);

// Specials (data/specials.inc). GetDayOfWeek itself is also a special.
void HoennBufferWeekdayName(void);
bool16 HoennIsItWeekday(void);
u8 *HoennWriteWeekdayAbbrev(u8 *dest);
void HoennSetWeekdayFromChoice(void);
u16 HoennGetWeatherCycleStage(void);
u16 HoennIsSpecialWeatherHere(void);
u16 HoennIsSpecialWeatherOn(void);

// Debug menu → Utilities → "H&S time & weather…" (data/scripts/hoenn_debug.inc)
void HoennDebugBufferStatus(void);
void HoennDebugStartClock(void);
void HoennDebugSetWeekday(void);
void HoennDebugSetHour(void);
void HoennDebugNextWeek(void);
void HoennDebugAdvanceWeatherStage(void);
void HoennDebugReloadMap(void);
#else
static inline u32 HoennAdjustWeekday(u32 rtcWeekday) { return rtcWeekday; }
static inline void HoennUpdatePerWeek(s32 localDays) { (void)localDays; }
static inline void HoennRecordWeekAfterClockReset(void) { }
static inline u8 HoennCycleMapWeather(u8 headerWeather) { return headerWeather; }
static inline bool32 HoennCycleIgnoresWeatherZones(void) { return FALSE; }
#endif

#endif // GUARD_HOENN_TIME_H
