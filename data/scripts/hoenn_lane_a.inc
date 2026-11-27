@ Hoenn & Seek 2.0, lane A: parts 27b, 28, 31a, 32, 34b, 35b and 37 (Johto, the Unown Cipher, the sea, Lugia, Ho-Oh, the Regis).
@ Lane A's scenes, phone calls and texts go in this file (or a new data/scripts/hoenn_*.inc
@ of its own); the other lane has its own file, so the two never edit the same lines.
@ Rules: hoenn-docs/lanes/README.md. C code: src/hoenn_lane_a.c.

@ ---------------------------------------------------------------- event calls

@ The PokéGear event-call switch (HoennSeek_EventScript_PhoneEvent, hoenn_phone.inc)
@ falls through to lane A's cases, then to lane B's. Add one case per call:
@ 	case HOENN_CALL_X, HoennSeek_EventScript_CallX
HoennSeek_EventScript_PhoneEventLaneA::
	switch VAR_0x8004
	case HOENN_CALL_CIPHER, HoennSeek_EventScript_CallCipher @ part 27a (hoenn_cipher.inc)
	case HOENN_CALL_SNEASEL, HoennSeek_EventScript_CallSneasel @ part 31a
	goto HoennSeek_EventScript_PhoneEventLaneB @ lane B's calls (hoenn_lane_b.inc)

@ ============================================================================
@ Part 31a: the Sneasel thief (Ice Path B2F, nights)
@ Once all four B1F boulders have dropped onto B2F (they shape the ice), at
@ night an item ball sits out on the ice. Reach it and a SNEASEL darts in and
@ snatches it, and another ball shows farther across the ice; three times.
@ After the third it runs into the north-west nook, where talking to it starts
@ the battle (hidden ability Pickpocket, Razor Claw, catchable). The first
@ battle, won or caught, gives its stash; after that it waits in the nook on
@ later nights until caught (knocked out: back the next night).
@ Balls and how to reach them (B2F's sliding ice, from the ladder at (26,6);
@ when a ball vanishes you slide on the way you faced, so each leg starts
@ where that slide ends; every state on the way can still reach a ladder):
@   1 (15,11), from (15,12) facing up:    LLLLDLURU, then slide to (15,5)
@   2 (22,13), from (21,13) facing right: LDDRDR, then slide to (26,13)
@   3 (16,18), from (16,17) facing down:  ULLLLDLURDDDRD, then slide to (16,22)
@   nook: SNEASEL at (9,6), from (8,6) facing right: LUULD
@ Leaving the floor mid-chase starts it over (the OnTransition decides).
@ ============================================================================

@ One `call` at the top of IcePath_B2F's OnTransition.
HoennSeek_EventScript_SneaselArm::
	setflag FLAG_HOENN_HIDE_SNEASEL_BALL_1
	setflag FLAG_HOENN_HIDE_SNEASEL_BALL_2
	setflag FLAG_HOENN_HIDE_SNEASEL_BALL_3
	setflag FLAG_HOENN_HIDE_ICE_SNEASEL
	goto_if_set FLAG_HOENN_CAUGHT_ICE_SNEASEL, HoennSeek_EventScript_SneaselArmDone
	goto_if_set FLAG_HOENN_DAILY_ICE_SNEASEL, HoennSeek_EventScript_SneaselArmDone
	goto_if_set FLAG_HIDE_ICEPATH_B2F_BOULDER1, HoennSeek_EventScript_SneaselArmDone
	goto_if_set FLAG_HIDE_ICEPATH_B2F_BOULDER2, HoennSeek_EventScript_SneaselArmDone
	goto_if_set FLAG_HIDE_ICEPATH_B2F_BOULDER3, HoennSeek_EventScript_SneaselArmDone
	goto_if_set FLAG_HIDE_ICEPATH_B2F_BOULDER4, HoennSeek_EventScript_SneaselArmDone
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_SneaselArmDone
	goto_if_set FLAG_HOENN_SNEASEL_STASH, HoennSeek_EventScript_SneaselArmNook
	clearflag FLAG_HOENN_HIDE_SNEASEL_BALL_1
	setobjectxyperm LOCALID_HOENN_ICE_SNEASEL, 15, 10
HoennSeek_EventScript_SneaselArmDone:
	return

HoennSeek_EventScript_SneaselArmNook:
	setobjectxyperm LOCALID_HOENN_ICE_SNEASEL, 9, 6
	clearflag FLAG_HOENN_HIDE_ICE_SNEASEL
	return

@ The balls. Each one: the SNEASEL pops up behind it, grabs it and dashes
@ off; the next ball shows.
HoennSeek_EventScript_SneaselBall1::
	lock
	setobjectxyperm LOCALID_HOENN_ICE_SNEASEL, 15, 10
	setvar VAR_0x8004, LOCALID_HOENN_SNEASEL_BALL_1
	call HoennSeek_EventScript_SneaselSnatch
	applymovement LOCALID_HOENN_ICE_SNEASEL, HoennSeek_Movement_SneaselDashUp
	waitmovement 0
	call HoennSeek_EventScript_SneaselGone
	clearflag FLAG_HOENN_HIDE_SNEASEL_BALL_2
	addobject LOCALID_HOENN_SNEASEL_BALL_2
	setobjectxyperm LOCALID_HOENN_ICE_SNEASEL, 23, 13
	msgbox HoennSeek_Text_SneaselAnother, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_SneaselBall2::
	lock
	setvar VAR_0x8004, LOCALID_HOENN_SNEASEL_BALL_2
	call HoennSeek_EventScript_SneaselSnatch
	applymovement LOCALID_HOENN_ICE_SNEASEL, HoennSeek_Movement_SneaselDashRight
	waitmovement 0
	call HoennSeek_EventScript_SneaselGone
	clearflag FLAG_HOENN_HIDE_SNEASEL_BALL_3
	addobject LOCALID_HOENN_SNEASEL_BALL_3
	setobjectxyperm LOCALID_HOENN_ICE_SNEASEL, 16, 19
	msgbox HoennSeek_Text_SneaselAgain, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_SneaselBall3::
	lock
	setvar VAR_0x8004, LOCALID_HOENN_SNEASEL_BALL_3
	call HoennSeek_EventScript_SneaselSnatch
	applymovement LOCALID_HOENN_ICE_SNEASEL, HoennSeek_Movement_SneaselDashDown
	waitmovement 0
	call HoennSeek_EventScript_SneaselGone
	setobjectxyperm LOCALID_HOENN_ICE_SNEASEL, 9, 6
	clearflag FLAG_HOENN_HIDE_ICE_SNEASEL
	addobject LOCALID_HOENN_ICE_SNEASEL
	msgbox HoennSeek_Text_SneaselToNook, MSGBOX_DEFAULT
	release
	end

@ VAR_0x8004: the ball's local ID. The SNEASEL's spot was set by the caller.
HoennSeek_EventScript_SneaselSnatch:
	clearflag FLAG_HOENN_HIDE_ICE_SNEASEL
	addobject LOCALID_HOENN_ICE_SNEASEL
	playmoncry SPECIES_SNEASEL, CRY_MODE_ENCOUNTER
	applymovement LOCALID_HOENN_ICE_SNEASEL, HoennSeek_Movement_SneaselHop
	waitmovement 0
	removeobject VAR_0x8004 @ (also sets the ball's hide flag)
	playse SE_BALL
	waitmoncry
	msgbox HoennSeek_Text_SneaselSnatch, MSGBOX_DEFAULT
	closemessage
	return

HoennSeek_EventScript_SneaselGone:
	removeobject LOCALID_HOENN_ICE_SNEASEL
	setflag FLAG_HOENN_HIDE_ICE_SNEASEL
	return

@ The cornered SNEASEL in the nook.
HoennSeek_EventScript_IceSneasel::
	lock
	faceplayer
	playmoncry SPECIES_SNEASEL, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_SneaselCornered, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setvar VAR_0x8004, SPECIES_SNEASEL
	special HoennSetupScaledWildBattle
	setvar VAR_0x8005, MOVE_NONE
	setvar VAR_0x8006, FALSE
	setvar VAR_0x8007, ITEM_RAZOR_CLAW
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, HOENN_TUNE_HIDDEN_ABILITY
	special HoennTuneWildMonSlot
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, HoennSeek_EventScript_SneaselStays
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, HoennSeek_EventScript_SneaselStays
	call HoennSeek_EventScript_SneaselGone
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_SneaselCaught
	setflag FLAG_HOENN_DAILY_ICE_SNEASEL
	msgbox HoennSeek_Text_SneaselFled, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_SneaselStash

HoennSeek_EventScript_SneaselCaught:
	setflag FLAG_HOENN_CAUGHT_ICE_SNEASEL
HoennSeek_EventScript_SneaselStash:
	goto_if_set FLAG_HOENN_SNEASEL_STASH, HoennSeek_EventScript_SneaselEnd
	setflag FLAG_HOENN_SNEASEL_STASH
	msgbox HoennSeek_Text_SneaselStash, MSGBOX_DEFAULT
	giveitem ITEM_PP_UP, 2
	giveitem ITEM_LUCKY_EGG
	giveitem ITEM_LANSAT_BERRY
	giveitem ITEM_STARF_BERRY
HoennSeek_EventScript_SneaselEnd:
	release
	end

HoennSeek_EventScript_SneaselStays:
	release
	end

HoennSeek_Movement_SneaselHop:
	jump_in_place_down
	step_end

HoennSeek_Movement_SneaselDashUp:
	walk_faster_up
	walk_faster_up
	step_end

HoennSeek_Movement_SneaselDashRight:
	walk_faster_right
	walk_faster_right
	step_end

HoennSeek_Movement_SneaselDashDown:
	walk_faster_down
	walk_faster_down
	step_end

@ Brendan: Norman reads every gym's report to the League, and Clair's says
@ the Ice Path thief was caught.
HoennSeek_EventScript_CallSneasel::
	setflag FLAG_HOENN_CALL_SNEASEL
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallSneasel
	goto HoennSeek_EventScript_CallEnd

HoennSeek_Text_SneaselSnatch:
	.string "A SNEASEL darts out of the dark\n"
	.string "and snatches the item!$"

HoennSeek_Text_SneaselAnother:
	.string "It skated off across the ice!\p"
	.string "Something else glints out on the\n"
	.string "ice, farther away…$"

HoennSeek_Text_SneaselAgain:
	.string "Gone again!\p"
	.string "There's one more glint out on the\n"
	.string "ice. Is it leading you somewhere?$"

HoennSeek_Text_SneaselToNook:
	.string "The SNEASEL skidded off toward the\n"
	.string "cave's far corner…$"

HoennSeek_Text_SneaselCornered:
	.string "The SNEASEL is cornered! It hisses\n"
	.string "and clutches its stolen hoard!$"

HoennSeek_Text_SneaselFled:
	.string "The SNEASEL scrambled off\n"
	.string "across the ice!$"

HoennSeek_Text_SneaselStash:
	.string "It left its hoard behind! Tucked\n"
	.string "into the corner is the SNEASEL's\l"
	.string "stash of stolen things!$"

HoennSeek_Text_CallSneasel:
	.string "{PLAYER}! It's BRENDAN.\p"
	.string "Dad reads every gym's report to\n"
	.string "the LEAGUE, and guess what was\l"
	.string "in CLAIR's from BLACKTHORN?\p"
	.string "The thief of the ICE PATH! Some\n"
	.string "SNEASEL was swiping items right\l"
	.string "off the ice for years.\p"
	.string "And a trainer from out of town\n"
	.string "finally cornered it. That was\l"
	.string "you, wasn't it? Ha! Nice one!$"
