@ Hoenn & Seek 2.0 (part 2): debug menu → Utilities → "H&S time & weather…".
@
@ Lets a tester jump to any weekday, hour, week or weather stage, so weekly
@ and weather events can be checked without waiting for the real clock. The
@ C side is in src/hoenn_time.c (HoennDebug*); it works with the real clock
@ and the fake RTC option alike. The emulator harness does the same through
@ memory (tools/hoenn/emu/pt.py: set_weekday, set_hour, next_week,
@ set_weather_stage, clock).
@
@ The status box shows the weekday, time, weekday offset, week number and the
@ weather stage, and whether today is the special-weather day here.
@ Time changes reload the map where you stand, so day/night objects and map
@ scripts see the new time; the weather stage changes the weather on the spot.

HoennDebug_EventScript_TimeWeather::
	lockall
	@ Daily and weekly resets only run once the clock is set (New Bark's wall
	@ clock does it at the start of a game; debug saves skip that scene).
	goto_if_set FLAG_SYS_CLOCK_SET, HoennDebug_EventScript_TimeWeatherMenu
	msgbox HoennDebug_Text_ClockNotSet, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennDebug_EventScript_TimeWeatherMenu
	special HoennDebugStartClock
HoennDebug_EventScript_TimeWeatherMenu:
	special HoennDebugBufferStatus
	message gStringVar4
	waitmessage
	dynmultichoice 17, 0, FALSE, 5, 0, DYN_MULTICHOICE_CB_NONE, HoennDebug_Text_SetWeekday, HoennDebug_Text_SetHour, HoennDebug_Text_NextWeek, HoennDebug_Text_WeatherStage, HoennDebug_Text_Exit
	switch VAR_RESULT
	case 0, HoennDebug_EventScript_PickWeekday
	case 1, HoennDebug_EventScript_PickHour
	case 2, HoennDebug_EventScript_NextWeek
	case 3, HoennDebug_EventScript_WeatherStage
	closemessage
	releaseall
	end

HoennDebug_EventScript_PickWeekday:
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	goto_if_gt VAR_RESULT, HOENN_SATURDAY, HoennDebug_EventScript_TimeWeatherMenu @ EXIT or B
	copyvar VAR_0x8004, VAR_RESULT
	special HoennDebugSetWeekday
	goto HoennDebug_EventScript_Reload

HoennDebug_EventScript_PickHour:
	dynmultichoice 21, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, HoennDebug_Text_Hour00, HoennDebug_Text_Hour01, HoennDebug_Text_Hour02, HoennDebug_Text_Hour03, HoennDebug_Text_Hour04, HoennDebug_Text_Hour05, HoennDebug_Text_Hour06, HoennDebug_Text_Hour07, HoennDebug_Text_Hour08, HoennDebug_Text_Hour09, HoennDebug_Text_Hour10, HoennDebug_Text_Hour11, HoennDebug_Text_Hour12, HoennDebug_Text_Hour13, HoennDebug_Text_Hour14, HoennDebug_Text_Hour15, HoennDebug_Text_Hour16, HoennDebug_Text_Hour17, HoennDebug_Text_Hour18, HoennDebug_Text_Hour19, HoennDebug_Text_Hour20, HoennDebug_Text_Hour21, HoennDebug_Text_Hour22, HoennDebug_Text_Hour23
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, HoennDebug_EventScript_TimeWeatherMenu
	copyvar VAR_0x8004, VAR_RESULT
	special HoennDebugSetHour
	goto HoennDebug_EventScript_Reload

HoennDebug_EventScript_NextWeek:
	special HoennDebugNextWeek
	goto HoennDebug_EventScript_Reload

HoennDebug_EventScript_WeatherStage:
	special HoennDebugAdvanceWeatherStage
	doweather
	goto HoennDebug_EventScript_TimeWeatherMenu

@ Reload the map in place. The time check on arrival runs the daily and weekly
@ resets if the change crossed a day or a week.
HoennDebug_EventScript_Reload:
	closemessage
	special HoennDebugReloadMap
	waitstate
	releaseall
	end

HoennDebug_Text_ClockNotSet:
	.string "The clock was never set, so daily and\n"
	.string "weekly resets don't run. Start it?$"

HoennDebug_Text_SetWeekday:
	.string "SET WEEKDAY$"
HoennDebug_Text_SetHour:
	.string "SET HOUR$"
HoennDebug_Text_NextWeek:
	.string "NEXT WEEK$"
HoennDebug_Text_WeatherStage:
	.string "WEATHER +1$"
HoennDebug_Text_Exit:
	.string "EXIT$"
HoennDebug_Text_Hour00:
	.string "00:00$"
HoennDebug_Text_Hour01:
	.string "01:00$"
HoennDebug_Text_Hour02:
	.string "02:00$"
HoennDebug_Text_Hour03:
	.string "03:00$"
HoennDebug_Text_Hour04:
	.string "04:00$"
HoennDebug_Text_Hour05:
	.string "05:00$"
HoennDebug_Text_Hour06:
	.string "06:00$"
HoennDebug_Text_Hour07:
	.string "07:00$"
HoennDebug_Text_Hour08:
	.string "08:00$"
HoennDebug_Text_Hour09:
	.string "09:00$"
HoennDebug_Text_Hour10:
	.string "10:00$"
HoennDebug_Text_Hour11:
	.string "11:00$"
HoennDebug_Text_Hour12:
	.string "12:00$"
HoennDebug_Text_Hour13:
	.string "13:00$"
HoennDebug_Text_Hour14:
	.string "14:00$"
HoennDebug_Text_Hour15:
	.string "15:00$"
HoennDebug_Text_Hour16:
	.string "16:00$"
HoennDebug_Text_Hour17:
	.string "17:00$"
HoennDebug_Text_Hour18:
	.string "18:00$"
HoennDebug_Text_Hour19:
	.string "19:00$"
HoennDebug_Text_Hour20:
	.string "20:00$"
HoennDebug_Text_Hour21:
	.string "21:00$"
HoennDebug_Text_Hour22:
	.string "22:00$"
HoennDebug_Text_Hour23:
	.string "23:00$"
