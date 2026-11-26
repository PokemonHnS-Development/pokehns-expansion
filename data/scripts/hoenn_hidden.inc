@ Hoenn & Seek 2.0 (parts 20+): hidden events, Hoenn (hoenn-docs/2.0-plan.md
@ section 7). Code in src/hoenn_hidden.c, flags in hoenn_events.h.
@
@ Part 20: Route 113 and Petalburg Woods.
@ - Munchlax (Route 113): asleep in a gap in the southern trees at (14,15), in
@   front of a hidden grotto (Route113_Grotto_hoenn). The glassblower makes a
@   GLASS FLUTE from 500 ash; playing it wakes the Munchlax, which joins you.
@ - Spinda (Route 113, mornings, once a week): it
@   dances in the falling ash in the pocket by the sign at (58,4). Walking up
@   plays the dance, then it challenges you.
@ - Slaking (Petalburg Woods): dozes across the notch at (26,7). It only gets
@   up at noon (12:00-12:59); then it battles you, once a day. Behind it, a
@   clearing with a MACHO BRACE.
@ Every event Pokémon has something special (plan section 9): Munchlax knows
@ Slack Off and holds Leftovers, Spinda knows Revelation Dance, Slaking has
@ perfect IVs and Slack Off.

@ ==========================================================================
@ The glassblower (Route 113 Glass Workshop; his object script is swapped).
@ Once you have the SOOT SACK and have brought ash once, he offers the GLASS
@ FLUTE (500 ash) before his usual list. Everything else is Emerald's script.
@ ==========================================================================

	.set GLASS_FLUTE_PRICE, 500

HoennSeek_EventScript_GlassWorker::
	goto_if_set FLAG_HOENN_GOT_GLASS_FLUTE, Route113_GlassWorkshop_EventScript_GlassWorker
	goto_if_ne VAR_GLASS_WORKSHOP_STATE, 2, Route113_GlassWorkshop_EventScript_GlassWorker
	checkitem ITEM_SOOT_SACK
	goto_if_eq VAR_RESULT, FALSE, Route113_GlassWorkshop_EventScript_GlassWorker
	lock
	faceplayer
	msgbox HoennSeek_Text_GlassFluteOffer, MSGBOX_DEFAULT
	goto_if_lt VAR_ASH_GATHER_COUNT, GLASS_FLUTE_PRICE, HoennSeek_EventScript_GlassFluteNotYet
	buffernumberstring STR_VAR_1, VAR_ASH_GATHER_COUNT
	msgbox HoennSeek_Text_GlassFluteTrade, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route113_GlassWorkshop_EventScript_CheckCollectedAsh
	giveitem ITEM_GLASS_FLUTE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	subvar VAR_ASH_GATHER_COUNT, GLASS_FLUTE_PRICE
	setflag FLAG_HOENN_GOT_GLASS_FLUTE
	msgbox HoennSeek_Text_GlassFluteGiven, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_GlassFluteNotYet:
	msgbox HoennSeek_Text_GlassFluteNotYet, MSGBOX_DEFAULT
	goto Route113_GlassWorkshop_EventScript_CheckCollectedAsh

@ ==========================================================================
@ Munchlax and the grotto (Route 113)
@ ==========================================================================

HoennSeek_EventScript_Munchlax::
	lock
	playmoncry SPECIES_MUNCHLAX, CRY_MODE_WEAK
	msgbox HoennSeek_Text_MunchlaxAsleep, MSGBOX_DEFAULT
	waitmoncry
	checkitem ITEM_GLASS_FLUTE
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_MunchlaxRelease
	msgbox HoennSeek_Text_MunchlaxPlayFlute, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_MunchlaxRelease
	playfanfare MUS_RG_POKE_FLUTE
	msgbox HoennSeek_Text_MunchlaxFlute, MSGBOX_DEFAULT
	waitfanfare
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, HoennSeek_Movement_MunchlaxWakes
	waitmovement 0
	playmoncry SPECIES_MUNCHLAX, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_MunchlaxAwake, MSGBOX_DEFAULT
	waitmoncry
	bufferspeciesname STR_VAR_1, SPECIES_MUNCHLAX
	givemon SPECIES_MUNCHLAX, 42, item=ITEM_LEFTOVERS, move1=MOVE_SLACK_OFF, move2=MOVE_BODY_SLAM, move3=MOVE_CRUNCH, move4=MOVE_CURSE
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, HoennSeek_EventScript_MunchlaxNoRoom
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_MUNCHLAX
	setflag FLAG_HOENN_MUNCHLAX_DONE
	call Common_EventScript_GiftMon
	removeobject VAR_LAST_TALKED
	msgbox HoennSeek_Text_MunchlaxJoined, MSGBOX_DEFAULT
HoennSeek_EventScript_MunchlaxRelease:
	release
	end

HoennSeek_EventScript_MunchlaxNoRoom:
	msgbox HoennSeek_Text_MunchlaxNoRoom, MSGBOX_DEFAULT
	release
	end

@ The gap below the Munchlax (14,16) and the grotto's way out (bottom row).
HoennSeek_EventScript_EnterGrotto::
	warpsilent MAP_ROUTE113_GROTTO_HOENN, 7, 11
	waitstate
	end

HoennSeek_EventScript_LeaveGrotto::
	warpsilent MAP_ROUTE113, 14, 15
	waitstate
	end

HoennSeek_Movement_MunchlaxWakes:
	jump_in_place_down
	face_left
	delay_8
	face_right
	delay_8
	face_down
	step_end

@ ==========================================================================
@ Spinda's dance (Route 113, mornings, once a week)
@ ==========================================================================

@ Called from Route 113's OnTransition: shows the Spinda and arms the ring of
@ trigger tiles around it (VAR_TEMP_4) on a morning it hasn't danced yet.
HoennSeek_EventScript_Route113OnTransition::
	setflag FLAG_HOENN_HIDE_SPINDA
	goto_if_set FLAG_HOENN_WEEKLY_SPINDA, HoennSeek_EventScript_HiddenReturn
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_MORNING, HoennSeek_EventScript_HiddenReturn
	clearflag FLAG_HOENN_HIDE_SPINDA
	setvar VAR_TEMP_4, 1
HoennSeek_EventScript_HiddenReturn:
	return

HoennSeek_EventScript_SpindaApproach::
	lockall
	setvar VAR_TEMP_4, 0
	goto HoennSeek_EventScript_SpindaDance

HoennSeek_EventScript_Spinda::
	lockall
	setvar VAR_TEMP_4, 0
HoennSeek_EventScript_SpindaDance:
	setflag FLAG_HOENN_SPINDA_MET
	msgbox HoennSeek_Text_SpindaDancing, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HOENN_SPINDA, HoennSeek_Movement_SpindaDance
	waitmovement 0
	applymovement LOCALID_HOENN_SPINDA, HoennSeek_Movement_SpindaDance
	waitmovement 0
	playmoncry SPECIES_SPINDA, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_SpindaChallenge, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setflag FLAG_HOENN_WEEKLY_SPINDA
	setvar VAR_0x8004, SPECIES_SPINDA
	special HoennSetupScaledWildBattle
	setvar VAR_0x8005, MOVE_REVELATION_DANCE
	setvar VAR_0x8006, FALSE
	setvar VAR_0x8007, ITEM_NONE
	special HoennTuneWildMon
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_SpindaGone
	msgbox HoennSeek_Text_SpindaLeaves, MSGBOX_DEFAULT
HoennSeek_EventScript_SpindaGone:
	removeobject LOCALID_HOENN_SPINDA
	releaseall
	end

HoennSeek_Movement_SpindaDance:
	face_left
	delay_4
	face_up
	delay_4
	face_right
	delay_4
	face_down
	jump_in_place_down
	walk_in_place_faster_left
	walk_in_place_faster_right
	jump_in_place_down
	step_end

@ ==========================================================================
@ Slaking's nap (Petalburg Woods)
@ ==========================================================================

@ Petalburg Woods' OnTransition: the Slaking lies in the notch unless it was
@ caught, or already battled today.
HoennSeek_EventScript_PetalburgWoodsOnTransition::
	setflag FLAG_HOENN_HIDE_SLAKING
	goto_if_set FLAG_HOENN_SLAKING_DONE, HoennSeek_EventScript_HiddenEnd
	goto_if_set FLAG_HOENN_DAILY_SLAKING, HoennSeek_EventScript_HiddenEnd
	clearflag FLAG_HOENN_HIDE_SLAKING
HoennSeek_EventScript_HiddenEnd:
	end

HoennSeek_EventScript_Slaking::
	lock
	gettime
	goto_if_eq VAR_0x8000, 12, HoennSeek_EventScript_SlakingWakes
	playmoncry SPECIES_SLAKING, CRY_MODE_WEAK
	msgbox HoennSeek_Text_SlakingAsleep, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_SlakingWakes:
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox HoennSeek_Text_SlakingNoon, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	playmoncry SPECIES_SLAKING, CRY_MODE_ENCOUNTER
	waitmoncry
	setflag FLAG_HOENN_DAILY_SLAKING
	setvar VAR_0x8004, SPECIES_SLAKING
	special HoennSetupScaledWildBattle
	setvar VAR_0x8005, MOVE_SLACK_OFF
	setvar VAR_0x8006, TRUE
	setvar VAR_0x8007, ITEM_NONE
	special HoennTuneWildMon
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	setflag FLAG_HOENN_HIDE_SLAKING
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_SlakingCaught
	msgbox HoennSeek_Text_SlakingWandersOff, MSGBOX_DEFAULT
	closemessage
	removeobject VAR_LAST_TALKED
	release
	end

HoennSeek_EventScript_SlakingCaught:
	setflag FLAG_HOENN_SLAKING_DONE
	removeobject VAR_LAST_TALKED
	release
	end

@ ==========================================================================
@ Part 20's calls
@ ==========================================================================

HoennSeek_EventScript_CallMunchlax::
	setflag FLAG_HOENN_CALL_MUNCHLAX
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallMunchlax
	goto HoennSeek_EventScript_CallEnd

HoennSeek_EventScript_CallSlaking::
	setflag FLAG_HOENN_CALL_SLAKING
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallSlaking
	goto HoennSeek_EventScript_CallEnd

@ ==========================================================================
@ Part 20 texts
@ ==========================================================================

HoennSeek_Text_GlassFluteOffer:
	.string "Oh, it's you! Look at this. I've\n"
	.string "made something new: a GLASS FLUTE.\p"
	.string "Its note is sweet enough to wake\n"
	.string "a sleeping glutton, I'd say.\p"
	.string "It takes 500 steps' worth of ash\n"
	.string "to make one, though.$"

HoennSeek_Text_GlassFluteNotYet:
	.string "Bring me 500 and it's yours.\n"
	.string "Now, what else can I do for you?$"

HoennSeek_Text_GlassFluteTrade:
	.string "Your SOOT SACK holds {STR_VAR_1} ash.\n"
	.string "Trade 500 for the GLASS FLUTE?$"

HoennSeek_Text_GlassFluteGiven:
	.string "There's a MUNCHLAX asleep in the\n"
	.string "trees west of here. It never wakes\l"
	.string "up, and it's in everybody's way.\p"
	.string "Give it a tune! And if you're out\n"
	.string "on a morning, look for the SPINDA\l"
	.string "that dances in the ash out east.$"

HoennSeek_Text_MunchlaxAsleep:
	.string "A MUNCHLAX is fast asleep in the\n"
	.string "gap between the trees, snoring.\p"
	.string "It's far too sleepy to move. Some\n"
	.string "sweet sound might wake it up…$"

HoennSeek_Text_MunchlaxPlayFlute:
	.string "Play the GLASS FLUTE?$"

HoennSeek_Text_MunchlaxFlute:
	.string "{PLAYER} played the GLASS FLUTE.$"

HoennSeek_Text_MunchlaxAwake:
	.string "MUNCHLAX woke up! It sniffs your\n"
	.string "BAG hungrily, then looks up at you.\p"
	.string "It seems to have decided you're\n"
	.string "where the food is. It wants to come!$"

HoennSeek_Text_MunchlaxJoined:
	.string "There's a path through the trees\n"
	.string "where MUNCHLAX was sleeping.$"

HoennSeek_Text_MunchlaxNoRoom:
	.string "There's no room for MUNCHLAX…\p"
	.string "It yawned and went back to sleep.$"

HoennSeek_Text_SpindaDancing:
	.string "A SPINDA is dancing in the falling\n"
	.string "ash, all alone!$"

HoennSeek_Text_SpindaChallenge:
	.string "It finished its dance with a wobbly\n"
	.string "bow… and it wants to battle!$"

HoennSeek_Text_SpindaLeaves:
	.string "SPINDA wobbled off into the ash.\n"
	.string "It might dance here again next week.$"

HoennSeek_Text_SlakingAsleep:
	.string "A SLAKING is lying across the path,\n"
	.string "dozing. It won't budge at all.$"

HoennSeek_Text_SlakingNoon:
	.string "The sun is right overhead… SLAKING\n"
	.string "yawns, scratches, and gets up!\p"
	.string "It looks annoyed that someone is\n"
	.string "in its way!$"

HoennSeek_Text_SlakingWandersOff:
	.string "SLAKING lumbered off into the\n"
	.string "trees for a nap somewhere else.$"

HoennSeek_Text_CallMunchlax:
	.string "{PLAYER}! It's BRENDAN!\p"
	.string "The glassblower on ROUTE 113 makes\n"
	.string "beakers for Dad's lab.\p"
	.string "He told Dad he made a GLASS FLUTE\n"
	.string "for you, and that sleepy MUNCHLAX\l"
	.string "finally got up!\p"
	.string "I tried to wake it once with a\n"
	.string "whole picnic. It didn't even twitch!$"

HoennSeek_Text_CallSlaking:
	.string "Hi, {PLAYER}! It's MAY.\p"
	.string "Dad says you caught the SLAKING\n"
	.string "in PETALBURG WOODS!\p"
	.string "That spot was his old training\n"
	.string "ground, and he hears about\l"
	.string "everything that goes on there.\p"
	.string "He says it only ever got up at\n"
	.string "noon. He's very jealous!$"
