@ Hoenn & Seek 2.0 part 3: HGSS's weekday content, now that the game knows
@ the real weekday (src/hoenn_time.c, part 2).
@
@ The Weekday siblings. In HnS they ran a "guess my favorite day" riddle and
@ gave their gift for the right guess, any day. Like HGSS, they now give it only
@ on their own day, and on any other day they tell you which day that is.
@ Each sibling's script sets VAR_0x8004 to their day and calls
@ specialvar VAR_RESULT, HoennIsItWeekday (TRUE on their day; their day's name
@ goes into STR_VAR_1 either way), then shows one of the texts below.

HoennSeek_Text_SiblingItsMyDay::
	.string "And look, it's {STR_VAR_1}!\n"
	.string "You came on my day!$"

HoennSeek_Text_SiblingComeBack::
	.string "Come and see me on a {STR_VAR_1},\n"
	.string "and I'll have a present for you!$"

@ ---- Setting the day ----------------------------------------------------------
@ The game's own week starts on whatever day the clock was first set, so the
@ player tells it the real day here. HoennSetWeekdayFromChoice shifts the
@ weekday offset (VAR_HOENN_WEEKDAY_OFFSET) without moving the day counter, so
@ daily and weekly resets don't fire (src/hoenn_time.c).

@ After HnS's opening scene sets the stopped clock in your New Bark room
@ (NewBarkTown_PlayersHouse_2F_hns, both triggers). The player has to pick a
@ day; EXIT just asks again.
HoennSeek_EventScript_AskWeekdayAtStart::
	msgbox HoennSeek_Text_CalendarWhatDay, MSGBOX_DEFAULT
HoennSeek_EventScript_AskWeekdayAtStart_Menu:
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, TRUE
	goto_if_ge VAR_RESULT, HOENN_WEEKDAY_COUNT, HoennSeek_EventScript_AskWeekdayAtStart_Menu
	special HoennSetWeekdayFromChoice
	special HoennBufferWeekdayName
	msgbox HoennSeek_Text_CalendarSet, MSGBOX_DEFAULT
	closemessage
	return

@ The wall clock in your New Bark room, any time after the opening (the bg
@ event's script, swapped in map.json). First the calendar: it names today and
@ offers to change the day. Then HnS's clock view, as before (R there resets
@ the time). The clock view must come last: Special_ViewWallClock returns
@ straight to the map (CB2_ReturnToField), which ends the script.
HoennSeek_EventScript_NewBarkWallClock::
	lockall
	goto_if_unset FLAG_SET_WALL_CLOCK, LittlerootTown_BrendansHouse_2F_EventScript_WallClock
	special HoennBufferWeekdayName
	msgbox HoennSeek_Text_CalendarChangeDay, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_NewBarkWallClock_View
	msgbox HoennSeek_Text_CalendarWhatDay, MSGBOX_DEFAULT
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	special HoennSetWeekdayFromChoice
	special HoennBufferWeekdayName
	msgbox HoennSeek_Text_CalendarSet, MSGBOX_DEFAULT
HoennSeek_EventScript_NewBarkWallClock_View:
	msgbox PlayersHouse_2F_Text_ClockChange, MSGBOX_DEFAULT
	incrementgamestat GAME_STAT_CHECKED_CLOCK
	fadescreen FADE_TO_BLACK
	special Special_ViewWallClock
	waitstate
	releaseall
	end

HoennSeek_Text_CalendarWhatDay:
	.string "There's a calendar next to the clock.\n"
	.string "What day is it today?$"

HoennSeek_Text_CalendarSet:
	.string "It's {STR_VAR_1}.\n"
	.string "The calendar is set!$"

HoennSeek_Text_CalendarChangeDay:
	.string "The calendar says it's {STR_VAR_1}.\n"
	.string "Change the day?$"

@ ---- Mt. Moon's Clefairy dance: Monday nights ------------------------------
@ HnS showed the eight Clefairy every night (FLAG_NIGHT_POKEMON). Like HGSS,
@ they now dance only on Monday nights. Their objects use
@ FLAG_HOENN_HIDE_CLEFAIRY_DANCE, decided here each time you arrive, so
@ nightfall while you're standing there shows them on your next visit.
HoennSeek_MtMoon_Outside_OnTransition::
	setflag FLAG_HOENN_HIDE_CLEFAIRY_DANCE
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_MtMoon_Outside_OnTransition_End
	setvar VAR_0x8004, HOENN_MONDAY
	specialvar VAR_RESULT, HoennIsItWeekday
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_MtMoon_Outside_OnTransition_End
	clearflag FLAG_HOENN_HIDE_CLEFAIRY_DANCE
HoennSeek_MtMoon_Outside_OnTransition_End:
	end

@ ---- Union Cave's Lapras: every Friday -------------------------------------
@ HnS brought the Lapras back after each Hall of Fame. Like HGSS, it now waits
@ in Union Cave B2F every Friday, once a week (FLAG_HOENN_WEEKLY_LAPRAS_MET,
@ set when it's caught or knocked out). Its own hide flag is decided here, so
@ the Hall of Fame and Violet City resets no longer matter.
HoennSeek_UnionCave_B2F_OnTransition::
	setflag FLAG_HIDE_UNION_CAVE_LAPRAS
	goto_if_set FLAG_HOENN_WEEKLY_LAPRAS_MET, HoennSeek_UnionCave_B2F_OnTransition_End
	setvar VAR_0x8004, HOENN_FRIDAY
	specialvar VAR_RESULT, HoennIsItWeekday
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_UnionCave_B2F_OnTransition_End
	clearflag FLAG_HIDE_UNION_CAVE_LAPRAS
HoennSeek_UnionCave_B2F_OnTransition_End:
	end
