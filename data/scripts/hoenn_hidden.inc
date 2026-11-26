@ Hoenn & Seek 2.0 (parts 20+): hidden events, Hoenn (hoenn-docs/2.0-plan.md
@ section 7). Code in src/hoenn_hidden.c, flags in hoenn_events.h.
@
@ Part 20: Route 113 and Petalburg Woods.
@ - Munchlax (Route 113): asleep at (14,14), in front of a gap in the southern
@   trees that hides a grotto (Route113_Grotto_hoenn). The glassblower makes a
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

@ The gap behind the Munchlax (14,16) and the grotto's way out (bottom row).
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
	.string "A MUNCHLAX is fast asleep in front\n"
	.string "of a gap in the trees, snoring.\p"
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

@ ==========================================================================
@ Part 21: Routes 119 and 114
@ ==========================================================================

@ ---- Tropius's orchard (Route119_Orchard_hoenn) -------------------------
@ The hidden way in is the tree trunk at Route 119 (26,21), below the
@ Fortree sign (its collision is cleared in composed_maps.json).

HoennSeek_EventScript_EnterOrchard::
	warpsilent MAP_ROUTE119_ORCHARD_HOENN, 7, 12
	waitstate
	end

HoennSeek_EventScript_LeaveOrchard::
	warpsilent MAP_ROUTE119, 26, 22
	waitstate
	end

@ Tropius stands in the orchard on mornings until it's caught; once battled
@ it's gone for the rest of the day.
HoennSeek_EventScript_OrchardOnTransition::
	setflag FLAG_HOENN_HIDE_TROPIUS
	goto_if_set FLAG_HOENN_TROPIUS_DONE, HoennSeek_EventScript_HiddenEnd21
	goto_if_set FLAG_HOENN_DAILY_TROPIUS, HoennSeek_EventScript_HiddenEnd21
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_MORNING, HoennSeek_EventScript_HiddenEnd21
	clearflag FLAG_HOENN_HIDE_TROPIUS
HoennSeek_EventScript_HiddenEnd21:
	end

HoennSeek_EventScript_Tropius::
	lock
	faceplayer
	msgbox HoennSeek_Text_TropiusShakes, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, HoennSeek_Movement_TropiusShake
	waitmovement 0
	playmoncry SPECIES_TROPIUS, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_TropiusBattle, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setflag FLAG_HOENN_TROPIUS_MET
	setflag FLAG_HOENN_DAILY_TROPIUS
	setvar VAR_0x8004, SPECIES_TROPIUS
	special HoennSetupScaledWildBattle
	setvar VAR_0x8005, MOVE_NONE
	setvar VAR_0x8006, FALSE
	setvar VAR_0x8007, ITEM_SITRUS_BERRY
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, HOENN_TUNE_HIDDEN_ABILITY
	special HoennTuneWildMonSlot
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	setflag FLAG_HOENN_HIDE_TROPIUS
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_TropiusCaught
	msgbox HoennSeek_Text_TropiusFliesOff, MSGBOX_DEFAULT
	closemessage
	removeobject VAR_LAST_TALKED
	release
	end

HoennSeek_EventScript_TropiusCaught:
	setflag FLAG_HOENN_TROPIUS_DONE
	removeobject VAR_LAST_TALKED
	msgbox HoennSeek_Text_TropiusCaught, MSGBOX_DEFAULT
	release
	end

HoennSeek_Movement_TropiusShake:
	face_left
	delay_4
	face_right
	delay_4
	face_down
	jump_in_place_down
	step_end

@ The fruit tree: nothing until Tropius has been met, then one berry each
@ morning (the plan's "each morning"; 21r).
HoennSeek_EventScript_OrchardTree::
	lock
	goto_if_unset FLAG_HOENN_TROPIUS_MET, HoennSeek_EventScript_OrchardTreeHigh
	goto_if_set FLAG_HOENN_DAILY_ORCHARD_BERRY, HoennSeek_EventScript_OrchardTreeBare
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_MORNING, HoennSeek_EventScript_OrchardTreeLater
	specialvar VAR_0x8004, HoennOrchardBerry
	msgbox HoennSeek_Text_OrchardTreeFruit, MSGBOX_DEFAULT
	giveitem VAR_0x8004
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_HOENN_DAILY_ORCHARD_BERRY
	release
	end

HoennSeek_EventScript_OrchardTreeHigh:
	msgbox HoennSeek_Text_OrchardTreeHigh, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_OrchardTreeBare:
	msgbox HoennSeek_Text_OrchardTreeBare, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_OrchardTreeLater:
	msgbox HoennSeek_Text_OrchardTreeLater, MSGBOX_DEFAULT
	release
	end

@ ---- Feebas in the mirror pool (Route 119 pond, (11-12, 67-68)) ---------
@ Evenings and nights, with the OLD ROD, once a day. Always female, knows
@ Mirror Coat; the first one you catch holds a Prism Scale (it keeps
@ holding one until you do).
HoennSeek_EventScript_MirrorPool::
	lock
	msgbox HoennSeek_Text_MirrorPool, MSGBOX_DEFAULT
	goto_if_set FLAG_HOENN_DAILY_FEEBAS, HoennSeek_EventScript_MirrorPoolStill
	gettimeofday
	goto_if_lt VAR_0x8000, HOENN_TIME_EVENING, HoennSeek_EventScript_MirrorPoolDay
	msgbox HoennSeek_Text_MirrorPoolShimmer, MSGBOX_DEFAULT
	checkitem ITEM_OLD_ROD
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_MirrorPoolNoRod
	msgbox HoennSeek_Text_MirrorPoolCast, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_MirrorPoolEnd
	msgbox HoennSeek_Text_MirrorPoolBite, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HOENN_DAILY_FEEBAS
	@ Lv 19, not the scaled 60-70: it's the shabby fish nobody looks at
	@ twice (Bryan, 21r).
	setwildbattle SPECIES_FEEBAS, 19
	setvar VAR_0x8005, MOVE_MIRROR_COAT
	setvar VAR_0x8006, FALSE
	setvar VAR_0x8007, ITEM_NONE
	call_if_unset FLAG_HOENN_FEEBAS_PRISM_GIVEN, HoennSeek_EventScript_FeebasPrismScale
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, HOENN_TUNE_FEMALE
	special HoennTuneWildMonSlot
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_MirrorPoolEnd
	setflag FLAG_HOENN_FEEBAS_PRISM_GIVEN
HoennSeek_EventScript_MirrorPoolEnd:
	release
	end

HoennSeek_EventScript_FeebasPrismScale:
	setvar VAR_0x8007, ITEM_PRISM_SCALE
	return

HoennSeek_EventScript_MirrorPoolStill:
	msgbox HoennSeek_Text_MirrorPoolStill, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_MirrorPoolDay:
	msgbox HoennSeek_Text_MirrorPoolDay, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_MirrorPoolNoRod:
	msgbox HoennSeek_Text_MirrorPoolNoRod, MSGBOX_DEFAULT
	release
	end

@ ---- Zangoose vs. Seviper (Route 114's lake island) ---------------------
@ Sunday evenings and nights, once a week: a wild double against both.
@ Zangoose has Toxic Boost and a Toxic Orb, Seviper knows Shed Tail.
HoennSeek_EventScript_Route114OnTransition::
	setflag FLAG_HOENN_HIDE_FEUD
	goto_if_set FLAG_HOENN_WEEKLY_FEUD, HoennSeek_EventScript_FeudReturn
	specialvar VAR_RESULT, GetDayOfWeek
	goto_if_ne VAR_RESULT, HOENN_SUNDAY, HoennSeek_EventScript_FeudReturn
	gettimeofday
	goto_if_lt VAR_0x8000, HOENN_TIME_EVENING, HoennSeek_EventScript_FeudReturn
	clearflag FLAG_HOENN_HIDE_FEUD
	setvar VAR_TEMP_4, 1
HoennSeek_EventScript_FeudReturn:
	return

HoennSeek_EventScript_FeudApproach::
HoennSeek_EventScript_Feud::
	lockall
	setvar VAR_TEMP_4, 0
	msgbox HoennSeek_Text_FeudFighting, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HOENN_ZANGOOSE, HoennSeek_Movement_FeudLunge
	applymovement LOCALID_HOENN_SEVIPER, HoennSeek_Movement_FeudLunge
	waitmovement 0
	playmoncry SPECIES_SEVIPER, CRY_MODE_ENCOUNTER
	waitmoncry
	applymovement LOCALID_HOENN_ZANGOOSE, Common_Movement_FacePlayer
	applymovement LOCALID_HOENN_SEVIPER, Common_Movement_FacePlayer
	waitmovement 0
	playmoncry SPECIES_ZANGOOSE, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_FeudTurn, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setflag FLAG_HOENN_WEEKLY_FEUD
	setflag FLAG_HOENN_FEUD_MET
	@ setwildbattle with two species makes dowildbattle start a double;
	@ HoennSetupScaledWildDouble then remakes both at the scaled level.
	setwildbattle SPECIES_ZANGOOSE, 1, ITEM_NONE, SPECIES_SEVIPER, 1, ITEM_NONE
	setvar VAR_0x8004, SPECIES_ZANGOOSE
	setvar VAR_0x8005, SPECIES_SEVIPER
	special HoennSetupScaledWildDouble
	setvar VAR_0x8005, MOVE_NONE
	setvar VAR_0x8006, FALSE
	setvar VAR_0x8007, ITEM_TOXIC_ORB
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, HOENN_TUNE_HIDDEN_ABILITY
	special HoennTuneWildMonSlot
	setvar VAR_0x8005, MOVE_SHED_TAIL
	setvar VAR_0x8007, ITEM_NONE
	setvar VAR_0x8008, 1
	setvar VAR_0x8009, 0
	special HoennTuneWildMonSlot
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	@ back to single wild battles for every later script
	setwildbattle SPECIES_ZANGOOSE, 1
	msgbox HoennSeek_Text_FeudAfter, MSGBOX_DEFAULT
	closemessage
	removeobject LOCALID_HOENN_ZANGOOSE
	removeobject LOCALID_HOENN_SEVIPER
	setflag FLAG_HOENN_HIDE_FEUD
	releaseall
	end

HoennSeek_Movement_FeudLunge:
	jump_in_place_down
	delay_8
	jump_in_place_down
	step_end

@ ---- Part 21's calls ----------------------------------------------------
HoennSeek_EventScript_CallTropius::
	setflag FLAG_HOENN_CALL_TROPIUS
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallTropius
	goto HoennSeek_EventScript_CallEnd

HoennSeek_EventScript_CallFeebas::
	setflag FLAG_HOENN_CALL_FEEBAS
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallFeebas
	goto HoennSeek_EventScript_CallEnd

HoennSeek_EventScript_CallFeud::
	setflag FLAG_HOENN_CALL_FEUD
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallFeud
	goto HoennSeek_EventScript_CallEnd

@ ---- Part 21 texts ------------------------------------------------------
HoennSeek_Text_TropiusShakes:
	.string "A TROPIUS is shaking fruit off its\n"
	.string "neck for the morning!$"

HoennSeek_Text_TropiusBattle:
	.string "It stamps its feet. It wants you\n"
	.string "out of its orchard!$"

HoennSeek_Text_TropiusFliesOff:
	.string "TROPIUS flapped its leaves and flew\n"
	.string "off over the treetops…\p"
	.string "It left a few fruit behind on the\n"
	.string "big tree.$"

HoennSeek_Text_TropiusCaught:
	.string "The big tree is still heavy with\n"
	.string "the fruit TROPIUS was tending.$"

HoennSeek_Text_OrchardTreeHigh:
	.string "Fruit hangs from the top of the\n"
	.string "tree, far out of reach.\p"
	.string "Something tall must feed here\n"
	.string "in the mornings.$"

HoennSeek_Text_OrchardTreeFruit:
	.string "A piece of fruit has dropped from\n"
	.string "the tree TROPIUS planted!$"

HoennSeek_Text_OrchardTreeBare:
	.string "Nothing else has fallen today.\n"
	.string "Come back tomorrow.$"

HoennSeek_Text_OrchardTreeLater:
	.string "The fruit is still up in the\n"
	.string "branches. It falls in the morning,\p"
	.string "when the first sun warms it.$"

HoennSeek_Text_MirrorPool:
	.string "The pond is perfectly still,\n"
	.string "like a mirror.$"

HoennSeek_Text_MirrorPoolDay:
	.string "It only reflects the sky right now.\n"
	.string "Nothing seems to live in it.$"

HoennSeek_Text_MirrorPoolStill:
	.string "Nothing has stirred in it since\n"
	.string "earlier today.$"

HoennSeek_Text_MirrorPoolShimmer:
	.string "In the dim light, one spot of the\n"
	.string "water is shimmering…$"

HoennSeek_Text_MirrorPoolNoRod:
	.string "Something might bite if you had\n"
	.string "even an old fishing rod.$"

HoennSeek_Text_MirrorPoolCast:
	.string "Cast the OLD ROD into the\n"
	.string "shimmering spot?$"

HoennSeek_Text_MirrorPoolBite:
	.string "{PLAYER} cast the OLD ROD…\p"
	.string "…  …  …\p"
	.string "Oh! Something shy took the bait!$"

HoennSeek_Text_FeudFighting:
	.string "A ZANGOOSE and a SEVIPER are locked\n"
	.string "in a furious fight!$"

HoennSeek_Text_FeudTurn:
	.string "They noticed you…\n"
	.string "and both turn on you at once!$"

HoennSeek_Text_FeudAfter:
	.string "The rivals slipped off into the\n"
	.string "dark. Same island next Sunday?$"

HoennSeek_Text_CallTropius:
	.string "{PLAYER}! It's BRENDAN!\p"
	.string "The WEATHER INSTITUTE on ROUTE 119\n"
	.string "called Dad this morning.\p"
	.string "From their roof they saw a TROPIUS\n"
	.string "in the jungle, and you with it!\p"
	.string "Dad's been looking for that orchard\n"
	.string "for years. How did you find it?$"

HoennSeek_Text_CallFeebas:
	.string "Hi, {PLAYER}! It's MAY!\p"
	.string "The contest crowd in LILYCOVE says\n"
	.string "someone fished a FEEBAS out of a\l"
	.string "pond on ROUTE 119. That was you!\p"
	.string "Raise its beauty and it becomes\n"
	.string "MILOTIC, the contest star.\p"
	.string "Show it off on stage sometime!$"

HoennSeek_Text_CallFeud:
	.string "{PLAYER}! It's BRENDAN!\p"
	.string "MAXIE's researchers watch ROUTE 114\n"
	.string "from the METEOR FALLS side.\p"
	.string "They told Dad a ZANGOOSE and a\n"
	.string "SEVIPER fight on the lake island\l"
	.string "every Sunday night.\p"
	.string "And you jumped right into the\n"
	.string "middle of their fight!\p"
	.string "Those two have hated each other\n"
	.string "for as long as anyone remembers.$"

@ ==========================================================================
@ Part 22a: Absol, the storm wanderer (Route 120)
@ On Route 120's storm day (its weather cycle), in the evening or at night,
@ an ABSOL stands on the ridge between the route's two paths, (15,50). The
@ first step onto row 52 on either side plays the scene: it looks at you,
@ lightning, and it's gone. From then on it roams Route 120's grass on storm
@ evenings and nights (src/hoenn_roamer.c): it flees like Raikou and Entei,
@ and keeps its HP and status between battles. Knocked out, it's back on the
@ ridge the next storm night, and the same scene revives the same ABSOL.
@ Caught: the ridge stays empty. It knows Earthquake, Eruption, Extreme Speed
@ and Future Sight and holds a Razor Claw (plan section 9).
@ ==========================================================================

@ Called from Route 120's OnTransition: shows the ABSOL on the ridge and arms
@ the trigger row (VAR_TEMP_4) when it isn't roaming or caught.
HoennSeek_EventScript_Route120OnTransition::
	setflag FLAG_HOENN_HIDE_ABSOL_CLIFF
	specialvar VAR_RESULT, HoennAbsolIsOut
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_HiddenReturn
	specialvar VAR_RESULT, HoennAbsolState
	goto_if_eq VAR_RESULT, HOENN_ABSOL_ROAMING, HoennSeek_EventScript_HiddenReturn
	goto_if_eq VAR_RESULT, HOENN_ABSOL_CAUGHT, HoennSeek_EventScript_HiddenReturn
	clearflag FLAG_HOENN_HIDE_ABSOL_CLIFF
	setvar VAR_TEMP_4, 1
	return

HoennSeek_EventScript_AbsolCliff::
	lockall
	setvar VAR_TEMP_4, 0
	getplayerxy VAR_0x8008, VAR_0x8009
	call_if_lt VAR_0x8008, 15, HoennSeek_EventScript_AbsolLookLeft
	call_if_gt VAR_0x8008, 15, HoennSeek_EventScript_AbsolLookRight
	playmoncry SPECIES_ABSOL, CRY_MODE_ENCOUNTER
	specialvar VAR_RESULT, HoennAbsolState
	call_if_eq VAR_RESULT, HOENN_ABSOL_DOWN, HoennSeek_EventScript_AbsolAgainText
	call_if_ne VAR_RESULT, HOENN_ABSOL_DOWN, HoennSeek_EventScript_AbsolFirstText
	waitmoncry
	closemessage
	delay 20
	playse SE_THUNDER
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_HOENN_ABSOL_CLIFF
	setflag FLAG_HOENN_HIDE_ABSOL_CLIFF
	specialvar VAR_RESULT, HoennWakeAbsol
	setflag FLAG_HOENN_ABSOL_WOKEN
	delay 8
	fadescreen FADE_FROM_WHITE
	msgbox HoennSeek_Text_AbsolGone, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_AbsolLookLeft:
	applymovement LOCALID_HOENN_ABSOL_CLIFF, Common_Movement_FaceLeft
	waitmovement 0
	return

HoennSeek_EventScript_AbsolLookRight:
	applymovement LOCALID_HOENN_ABSOL_CLIFF, Common_Movement_FaceRight
	waitmovement 0
	return

HoennSeek_EventScript_AbsolFirstText:
	msgbox HoennSeek_Text_AbsolOnRidge, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_AbsolAgainText:
	msgbox HoennSeek_Text_AbsolBack, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_CallAbsol::
	setflag FLAG_HOENN_CALL_ABSOL
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallAbsol
	goto HoennSeek_EventScript_CallEnd

@ ---- Part 22a texts ------------------------------------------------------
HoennSeek_Text_AbsolOnRidge:
	.string "A white POKéMON stands on the\n"
	.string "ridge, its horn to the storm…\p"
	.string "It's looking straight at you.$"

HoennSeek_Text_AbsolBack:
	.string "The white POKéMON is back on the\n"
	.string "ridge, rested and watching you.$"

HoennSeek_Text_AbsolGone:
	.string "…When the flash cleared, the\n"
	.string "ridge was empty.\p"
	.string "Something white is moving in\n"
	.string "the tall grass of ROUTE 120.$"

HoennSeek_Text_CallAbsol:
	.string "{PLAYER}? It's MAY!\p"
	.string "WINONA flew home to FORTREE in\n"
	.string "that storm, and she told Dad what\l"
	.string "she saw from up there.\p"
	.string "A white ABSOL on the ridge over\n"
	.string "ROUTE 120, staring at someone…\p"
	.string "That was you, wasn't it?\p"
	.string "They say ABSOL show up when\n"
	.string "disaster's near. Or a big storm!\p"
	.string "It runs from everybody. You'll\n"
	.string "need a way to stop it escaping.\p"
	.string "Good luck out there! Bye!$"

@ ==========================================================================
@ Part 22b: Wailord's strait (Route 131) and Chimecho's chimes (Mt. Pyre)
@ WAILORD: a huge WAILORD sleeps wedged in a one-tile strait at Route 131's
@ bottom edge, (17,38) (the rock beside it moved down a row in
@ composed_maps.json). It only wakes on Saturday mornings, when a WAILMER
@ leads your party (it's listening for its young). Its battle is scaled; it
@ knows Steam Eruption (its spout) and has a perfect HP IV. Whatever happens,
@ it dives under and the strait stays open: (17,39) leads to an atoll
@ (Route131_Atoll_hoenn) with pearls, a Star Piece, hidden Heart Scales and
@ a Luvdisc lagoon. Until it's caught, it sleeps in that lagoon and wakes
@ the same way, once a week.
@ CHIMECHO: on Mt. Pyre's summit at night, chimes ring from the top-left
@ graves. Three rings of trigger tiles on the only way there (VAR_TEMP_4,
@ BFS distances 16, 9 and 4 from the graves) make them louder; the last one
@ brings CHIMECHO out of the fog. Scaled battle, Relic Song, Cleanse Tag.
@ Once a night until it's caught.
@ ==========================================================================

@ ---- Wailord ---------------------------------------------------------------
HoennSeek_EventScript_EnterAtoll::
	warp MAP_ROUTE131_ATOLL_HOENN, 13, 1
	waitstate
	end

HoennSeek_EventScript_LeaveAtoll::
	warp MAP_ROUTE131, 17, 38
	waitstate
	end

@ In the lagoon from its first battle until it's caught, except the rest of
@ a week in which it was battled.
HoennSeek_EventScript_AtollOnTransition::
	setflag FLAG_HOENN_HIDE_WAILORD_ATOLL
	goto_if_set FLAG_HOENN_WAILORD_CAUGHT, HoennSeek_EventScript_HiddenEnd22b
	goto_if_set FLAG_HOENN_WEEKLY_WAILORD, HoennSeek_EventScript_HiddenEnd22b
	clearflag FLAG_HOENN_HIDE_WAILORD_ATOLL
HoennSeek_EventScript_HiddenEnd22b:
	end

@ The same script runs in the strait and, once it has moved, in the lagoon.
HoennSeek_EventScript_Wailord::
	lock
	goto_if_set FLAG_HOENN_WAILORD_MOVED, HoennSeek_EventScript_WailordInLagoon
	msgbox HoennSeek_Text_WailordAsleep, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_WailordTryWake

HoennSeek_EventScript_WailordInLagoon:
	msgbox HoennSeek_Text_WailordLagoon, MSGBOX_DEFAULT
HoennSeek_EventScript_WailordTryWake:
	setvar VAR_0x8004, HOENN_SATURDAY
	specialvar VAR_RESULT, HoennIsItWeekday
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_WailordSleeps
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_MORNING, HoennSeek_EventScript_WailordSleeps
	setvar VAR_0x8004, SPECIES_WAILMER
	specialvar VAR_RESULT, HoennLeadIsSpecies
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_WailordSleeps
	playmoncry SPECIES_WAILMER, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_WailmerCalls, MSGBOX_DEFAULT
	waitmoncry
	playmoncry SPECIES_WAILORD, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_WailordWakes, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setvar VAR_0x800A, FALSE
	goto_if_set FLAG_HOENN_WAILORD_MOVED, HoennSeek_EventScript_WailordBattle
	setvar VAR_0x800A, TRUE @ it was in the strait
HoennSeek_EventScript_WailordBattle:
	setflag FLAG_HOENN_WAILORD_MOVED
	setflag FLAG_HOENN_WEEKLY_WAILORD
	setvar VAR_0x8004, SPECIES_WAILORD
	special HoennSetupScaledWildBattle
	setvar VAR_0x8005, MOVE_STEAM_ERUPTION
	setvar VAR_0x8006, HOENN_TUNE_IV_HP
	setvar VAR_0x8007, ITEM_NONE
	special HoennTuneWildMon
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_WailordCaught
	removeobject VAR_LAST_TALKED
	goto_if_eq VAR_0x800A, FALSE, HoennSeek_EventScript_WailordDivesLagoon
	msgbox HoennSeek_Text_WailordDives, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_WailordDivesLagoon:
	msgbox HoennSeek_Text_WailordDivesLagoon, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_WailordCaught:
	setflag FLAG_HOENN_WAILORD_CAUGHT
	removeobject VAR_LAST_TALKED
	goto_if_eq VAR_0x800A, FALSE, HoennSeek_EventScript_WailordEnd
	msgbox HoennSeek_Text_WailordCaught, MSGBOX_DEFAULT
HoennSeek_EventScript_WailordEnd:
	release
	end

HoennSeek_EventScript_WailordSleeps:
	msgbox HoennSeek_Text_WailordListening, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_CallWailord::
	setflag FLAG_HOENN_CALL_WAILORD
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallWailord
	goto HoennSeek_EventScript_CallEnd

@ ---- Chimecho --------------------------------------------------------------
@ Called from Mt. Pyre summit's OnTransition.
HoennSeek_EventScript_PyreSummitOnTransition::
	setflag FLAG_HOENN_HIDE_CHIMECHO
	goto_if_set FLAG_HOENN_CHIMECHO_CAUGHT, HoennSeek_EventScript_HiddenReturn
	goto_if_set FLAG_HOENN_DAILY_CHIMECHO, HoennSeek_EventScript_HiddenReturn
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_HiddenReturn
	setvar VAR_TEMP_4, 1
	return

HoennSeek_EventScript_ChimesFaint::
	lockall
	setvar VAR_TEMP_4, 2
	playse SE_M_HEAL_BELL
	msgbox HoennSeek_Text_ChimesFaint, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_ChimesLouder::
	lockall
	setvar VAR_TEMP_4, 3
	playse SE_M_HEAL_BELL
	delay 12
	playse SE_M_HEAL_BELL
	msgbox HoennSeek_Text_ChimesLouder, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_ChimechoAppears::
	lockall
	setvar VAR_TEMP_4, 4
	applymovement LOCALID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	playmoncry SPECIES_CHIMECHO, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_ChimesHere, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	clearflag FLAG_HOENN_HIDE_CHIMECHO
	addobject LOCALID_HOENN_CHIMECHO
	applymovement LOCALID_HOENN_CHIMECHO, HoennSeek_Movement_ChimechoDrift
	waitmovement 0
	playmoncry SPECIES_CHIMECHO, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_ChimechoBattle, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setflag FLAG_HOENN_CHIMECHO_MET
	setflag FLAG_HOENN_DAILY_CHIMECHO
	setvar VAR_0x8004, SPECIES_CHIMECHO
	special HoennSetupScaledWildBattle
	setvar VAR_0x8005, MOVE_RELIC_SONG
	setvar VAR_0x8006, FALSE
	setvar VAR_0x8007, ITEM_CLEANSE_TAG
	special HoennTuneWildMon
	dowildbattle
	removeobject LOCALID_HOENN_CHIMECHO
	setflag FLAG_HOENN_HIDE_CHIMECHO
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_ChimechoCaught
	msgbox HoennSeek_Text_ChimechoDrifts, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_ChimechoCaught:
	setflag FLAG_HOENN_CHIMECHO_CAUGHT
	msgbox HoennSeek_Text_ChimechoCaught, MSGBOX_DEFAULT
	releaseall
	end

@ From the graves at (8,4) to two steps from the player at (11,5).
HoennSeek_Movement_ChimechoDrift:
	walk_slow_down
	walk_slow_right
	step_end

HoennSeek_EventScript_CallChimecho::
	setflag FLAG_HOENN_CALL_CHIMECHO
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallChimecho
	goto HoennSeek_EventScript_CallEnd

@ ---- Part 22b texts ------------------------------------------------------
HoennSeek_Text_WailordAsleep:
	.string "A huge WAILORD is asleep in the\n"
	.string "gap, wedged between the rocks.\p"
	.string "Each breath it takes sounds like\n"
	.string "the tide going out.$"

HoennSeek_Text_WailordLagoon:
	.string "The WAILORD is asleep, floating\n"
	.string "in the middle of the lagoon.$"

HoennSeek_Text_WailordListening:
	.string "It doesn't stir. Even asleep,\n"
	.string "it seems to be listening for\l"
	.string "something out in the sea…$"

HoennSeek_Text_WailmerCalls:
	.string "Your WAILMER calls out across\n"
	.string "the water!$"

HoennSeek_Text_WailordWakes:
	.string "The WAILORD's eye opens!\p"
	.string "It blasts a spout of steam high\n"
	.string "into the morning air!$"

HoennSeek_Text_WailordDives:
	.string "The WAILORD dove under and\n"
	.string "swam off through the gap.\p"
	.string "The strait it was blocking\n"
	.string "is open now!$"

HoennSeek_Text_WailordDivesLagoon:
	.string "The WAILORD dove deep into the\n"
	.string "lagoon. It'll be back to sleep\l"
	.string "here before long.$"

HoennSeek_Text_WailordCaught:
	.string "With the WAILORD gone, the\n"
	.string "strait it was blocking is open!$"

HoennSeek_Text_CallWailord:
	.string "{PLAYER}! It's BRENDAN!\p"
	.string "CAPT. STERN's crew was charting\n"
	.string "the sea by PACIFIDLOG this week.\p"
	.string "They saw a WAILORD as big as\n"
	.string "their boat go under, right by\l"
	.string "ROUTE 131. Dad says it was you!\p"
	.string "They say there's an atoll past\n"
	.string "that strait nobody's charted.\p"
	.string "Dad wants a full report, so look\n"
	.string "around for me, okay?$"

HoennSeek_Text_ChimesFaint:
	.string "Somewhere in the fog, a chime\n"
	.string "rings… then another.\p"
	.string "But there's no wind tonight.$"

HoennSeek_Text_ChimesLouder:
	.string "The chimes are louder here,\n"
	.string "ringing from between the graves.$"

HoennSeek_Text_ChimesHere:
	.string "The chimes ring all around you!$"

HoennSeek_Text_ChimechoBattle:
	.string "A CHIMECHO drifted out of the\n"
	.string "fog, singing an old, old song!$"

HoennSeek_Text_ChimechoDrifts:
	.string "The CHIMECHO drifted back into\n"
	.string "the fog. The chimes fell silent.$"

HoennSeek_Text_ChimechoCaught:
	.string "The summit is quiet now. Only\n"
	.string "the wind moves between the graves.$"

HoennSeek_Text_CallChimecho:
	.string "Hi, {PLAYER}! It's MAY.\p"
	.string "Mom went up to MT. PYRE last\n"
	.string "night to tend our family's grave.\p"
	.string "She heard wind chimes on the\n"
	.string "summit, with no wind at all!\p"
	.string "The old lady up there told her\n"
	.string "someone followed the sound into\l"
	.string "the graves… That was you, right?\p"
	.string "Mom says it was a CHIMECHO\n"
	.string "singing to the spirits there.$"

@ ==========================================================================
@ Part 23: Meteor Falls (Altaria's chorus, Bagon's leap, Metagross)
@ CHORUS: a cave mouth at the top right of Meteor Falls 1F (27,3) leads up
@ to a clifftop (MeteorFalls_Clifftop_hoenn). On Saturday mornings an
@ ALTARIA sings there with four SWABLU, once a week. A line of boulders
@ (row 10) hides you: stand behind one (row 11) to watch, step into a gap
@ and the flock scatters until next week. Watch-only, like HGSS's Clefairy
@ dance; each watch leaves a Pretty Feather.
@ SHINY ALTARIA: once you've watched the chorus to the end, a later chorus
@ offers to play the GLASS FLUTE if your lead is a SWABLU or ALTARIA. A
@ shiny ALTARIA glides down to sing along and battles you: scaled, Perish
@ Song (the chorus). Knocked out, it's back the next Saturday.
@ BAGON: on the ledge above the pool in B1F_2R, mornings, once a day until
@ caught. Surfing up the pool (row 7, where the ledge is in full view)
@ plays its leap into the water; land on the ledge to battle it: scaled, Dragon Ascent (its dream of flight),
@ holding a Dragon Scale.
@ METAGROSS: two METANG hover over a meteorite fragment in Steven's cave
@ at night, once a week. Coming up the path past them (15-16,12) they
@ fuse into a METAGROSS, which leaves (watch-only). Comet Shard the first
@ time, Star Piece after that.
@ ==========================================================================

@ ---- Altaria's chorus ----------------------------------------------------
HoennSeek_EventScript_LeaveClifftop::
	warp MAP_METEOR_FALLS_1F_1R, 27, 4
	waitstate
	end

HoennSeek_EventScript_ClifftopOnTransition::
	setflag FLAG_HOENN_HIDE_CHORUS
	setflag FLAG_HOENN_HIDE_SHINY_ALTARIA
	goto_if_set FLAG_HOENN_WEEKLY_CHORUS, HoennSeek_EventScript_HiddenEnd23
	setvar VAR_0x8004, HOENN_SATURDAY
	specialvar VAR_RESULT, HoennIsItWeekday
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_HiddenEnd23
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_MORNING, HoennSeek_EventScript_HiddenEnd23
	clearflag FLAG_HOENN_HIDE_CHORUS
	setvar VAR_TEMP_1, 1
HoennSeek_EventScript_HiddenEnd23:
	end

@ ON_FRAME, the first frame on the clifftop while the chorus is there.
HoennSeek_EventScript_ChorusIntro::
	lockall
	setvar VAR_TEMP_1, 2
	msgbox HoennSeek_Text_ChorusIntro, MSGBOX_DEFAULT
	releaseall
	end

@ The chorus's objects can't be reached before they leave.
HoennSeek_EventScript_ChorusMon::
	end

@ Row 10's gaps between the boulders.
HoennSeek_EventScript_ChorusScatter::
	lockall
	setvar VAR_TEMP_1, 3
	playse SE_PIN
	applymovement LOCALID_HOENN_CHORUS_ALTARIA, Common_Movement_ExclamationMark
	applymovement LOCALID_HOENN_CHORUS_SWABLU_1, Common_Movement_ExclamationMark
	applymovement LOCALID_HOENN_CHORUS_SWABLU_2, Common_Movement_ExclamationMark
	applymovement LOCALID_HOENN_CHORUS_SWABLU_3, Common_Movement_ExclamationMark
	applymovement LOCALID_HOENN_CHORUS_SWABLU_4, Common_Movement_ExclamationMark
	waitmovement 0
	call HoennSeek_EventScript_ChorusFliesOff
	msgbox HoennSeek_Text_ChorusScattered, MSGBOX_DEFAULT
	releaseall
	end

@ Row 11, right behind a boulder.
HoennSeek_EventScript_ChorusWatch::
	lockall
	setvar VAR_TEMP_1, 3
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	msgbox HoennSeek_Text_ChorusHide, MSGBOX_DEFAULT
	closemessage
	call HoennSeek_EventScript_ChorusCircle
	playmoncry SPECIES_ALTARIA, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_ChorusSings, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	call HoennSeek_EventScript_ChorusCircle
	goto_if_unset FLAG_HOENN_CHORUS_WATCHED, HoennSeek_EventScript_ChorusEnds
	goto_if_set FLAG_HOENN_SHINY_ALTARIA_DONE, HoennSeek_EventScript_ChorusEnds
	checkitem ITEM_GLASS_FLUTE
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_ChorusEnds
	setvar VAR_0x8004, SPECIES_SWABLU
	specialvar VAR_RESULT, HoennLeadIsSpecies
	goto_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_ChorusFlute
	setvar VAR_0x8004, SPECIES_ALTARIA
	specialvar VAR_RESULT, HoennLeadIsSpecies
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_ChorusEnds
HoennSeek_EventScript_ChorusFlute:
	msgbox HoennSeek_Text_ChorusHumming, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_ChorusEnds
	playse SE_GLASS_FLUTE
	msgbox HoennSeek_Text_ChorusFlute, MSGBOX_DEFAULT
	waitse
	closemessage
	clearflag FLAG_HOENN_HIDE_SHINY_ALTARIA
	addobject LOCALID_HOENN_SHINY_ALTARIA
	applymovement LOCALID_HOENN_SHINY_ALTARIA, HoennSeek_Movement_ShinyAltariaGlides
	waitmovement 0
	playmoncry SPECIES_ALTARIA, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_ShinyAltaria, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setvar VAR_0x8004, SPECIES_ALTARIA
	special HoennSetupScaledWildBattle
	setvar VAR_0x8005, MOVE_PERISH_SONG
	setvar VAR_0x8006, FALSE
	setvar VAR_0x8007, ITEM_NONE
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, HOENN_TUNE_SHINY
	special HoennTuneWildMonSlot
	dowildbattle
	removeobject LOCALID_HOENN_SHINY_ALTARIA
	setflag FLAG_HOENN_HIDE_SHINY_ALTARIA
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_ChorusEnds
	setflag FLAG_HOENN_SHINY_ALTARIA_DONE
HoennSeek_EventScript_ChorusEnds:
	call HoennSeek_EventScript_ChorusFliesOff
	setflag FLAG_HOENN_CHORUS_WATCHED
	msgbox HoennSeek_Text_ChorusEnds, MSGBOX_DEFAULT
	giveitem ITEM_PRETTY_FEATHER
	releaseall
	end

@ The SWABLU fly two laps around the singing ALTARIA.
HoennSeek_EventScript_ChorusCircle:
	applymovement LOCALID_HOENN_CHORUS_SWABLU_1, HoennSeek_Movement_SwabluLapA
	applymovement LOCALID_HOENN_CHORUS_SWABLU_2, HoennSeek_Movement_SwabluLapB
	applymovement LOCALID_HOENN_CHORUS_SWABLU_3, HoennSeek_Movement_SwabluLapC
	applymovement LOCALID_HOENN_CHORUS_SWABLU_4, HoennSeek_Movement_SwabluLapD
	applymovement LOCALID_HOENN_CHORUS_ALTARIA, HoennSeek_Movement_AltariaSings
	waitmovement 0
	return

HoennSeek_EventScript_ChorusFliesOff:
	playse SE_M_FLY
	applymovement LOCALID_HOENN_CHORUS_ALTARIA, HoennSeek_Movement_ChorusFliesOff
	applymovement LOCALID_HOENN_CHORUS_SWABLU_1, HoennSeek_Movement_ChorusFliesOff
	applymovement LOCALID_HOENN_CHORUS_SWABLU_2, HoennSeek_Movement_ChorusFliesOff
	applymovement LOCALID_HOENN_CHORUS_SWABLU_3, HoennSeek_Movement_ChorusFliesOff
	applymovement LOCALID_HOENN_CHORUS_SWABLU_4, HoennSeek_Movement_ChorusFliesOff
	waitmovement 0
	removeobject LOCALID_HOENN_CHORUS_ALTARIA
	removeobject LOCALID_HOENN_CHORUS_SWABLU_1
	removeobject LOCALID_HOENN_CHORUS_SWABLU_2
	removeobject LOCALID_HOENN_CHORUS_SWABLU_3
	removeobject LOCALID_HOENN_CHORUS_SWABLU_4
	setflag FLAG_HOENN_HIDE_CHORUS
	setflag FLAG_HOENN_WEEKLY_CHORUS
	return

@ Each SWABLU loops through the three tiles next to its own, away from the
@ others, and lands where it started.
HoennSeek_Movement_SwabluLapA: @ (6,7)
	walk_up
	walk_left
	walk_down
	walk_right
	face_right
	step_end

HoennSeek_Movement_SwabluLapB: @ (10,7)
	walk_up
	walk_right
	walk_down
	walk_left
	face_left
	step_end

HoennSeek_Movement_SwabluLapC: @ (5,9)
	walk_left
	walk_up
	walk_right
	walk_down
	face_right
	step_end

HoennSeek_Movement_SwabluLapD: @ (11,9)
	walk_right
	walk_up
	walk_left
	walk_down
	face_left
	step_end

HoennSeek_Movement_AltariaSings:
	jump_in_place_down
	delay_8
	jump_in_place_down
	delay_8
	face_down
	step_end

HoennSeek_Movement_ChorusFliesOff:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

@ From the right edge of the stage (12,7) to the middle (9,7).
HoennSeek_Movement_ShinyAltariaGlides:
	walk_slow_left
	walk_slow_left
	walk_slow_left
	face_down
	step_end

HoennSeek_EventScript_CallChorus::
	setflag FLAG_HOENN_CALL_CHORUS
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallChorus
	goto HoennSeek_EventScript_CallEnd

@ ---- Bagon ----------------------------------------------------------------
HoennSeek_EventScript_BagonOnTransition::
	setflag FLAG_HOENN_HIDE_BAGON
	goto_if_set FLAG_HOENN_BAGON_CAUGHT, HoennSeek_EventScript_HiddenEnd23
	goto_if_set FLAG_HOENN_DAILY_BAGON, HoennSeek_EventScript_HiddenEnd23
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_MORNING, HoennSeek_EventScript_HiddenEnd23
	clearflag FLAG_HOENN_HIDE_BAGON
	setvar VAR_TEMP_1, 1
	end

@ Row 7 of the pool, the first row from which the whole ledge is on screen.
HoennSeek_EventScript_BagonLeaps::
	lockall
	setvar VAR_TEMP_1, 2
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	applymovement LOCALID_HOENN_BAGON, HoennSeek_Movement_BagonWindUp
	waitmovement 0
	playmoncry SPECIES_BAGON, CRY_MODE_NORMAL
	applymovement LOCALID_HOENN_BAGON, HoennSeek_Movement_BagonLeap
	waitmovement 0
	waitmoncry
	playse SE_M_DIVE
	msgbox HoennSeek_Text_BagonLeaps, MSGBOX_DEFAULT
	closemessage
	setobjectxy LOCALID_HOENN_BAGON, 6, 4
	applymovement LOCALID_HOENN_BAGON, HoennSeek_Movement_BagonClimbsBack
	waitmovement 0
	msgbox HoennSeek_Text_BagonClimbs, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_Bagon::
	lock
	faceplayer
	playmoncry SPECIES_BAGON, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_BagonBattle, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setflag FLAG_HOENN_BAGON_MET
	setflag FLAG_HOENN_DAILY_BAGON
	setvar VAR_0x8004, SPECIES_BAGON
	special HoennSetupScaledWildBattle
	setvar VAR_0x8005, MOVE_DRAGON_ASCENT
	setvar VAR_0x8006, FALSE
	setvar VAR_0x8007, ITEM_DRAGON_SCALE
	special HoennTuneWildMon
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	removeobject VAR_LAST_TALKED
	setflag FLAG_HOENN_HIDE_BAGON
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_BagonCaught
	msgbox HoennSeek_Text_BagonLeaves, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_BagonCaught:
	setflag FLAG_HOENN_BAGON_CAUGHT
	release
	end

HoennSeek_Movement_BagonWindUp:
	jump_in_place_down
	jump_in_place_down
	delay_8
	step_end

@ Off the ledge (6,4) into the pool (6,5), out of sight under the water.
HoennSeek_Movement_BagonLeap:
	jump_down
	set_invisible
	step_end

HoennSeek_Movement_BagonClimbsBack:
	delay_16
	set_visible
	jump_in_place_down
	face_down
	step_end

HoennSeek_EventScript_CallBagon::
	setflag FLAG_HOENN_CALL_BAGON
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallBagon
	goto HoennSeek_EventScript_CallEnd

@ ---- Metagross -------------------------------------------------------------
HoennSeek_EventScript_StevensCaveOnTransition::
	setflag FLAG_HOENN_HIDE_METANG
	setflag FLAG_HOENN_HIDE_METAGROSS
	goto_if_set FLAG_HOENN_WEEKLY_METAGROSS, HoennSeek_EventScript_HiddenEnd23
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_HiddenEnd23
	clearflag FLAG_HOENN_HIDE_METANG
	setvar VAR_TEMP_1, 1
	end

@ They're gone before you can get next to them.
HoennSeek_EventScript_Metang::
	end

@ (15,12) and (16,12): every way up the cave passes one of them.
HoennSeek_EventScript_MetangFuse::
	lockall
	setvar VAR_TEMP_1, 2
	applymovement LOCALID_PLAYER, Common_Movement_FaceLeft
	waitmovement 0
	msgbox HoennSeek_Text_MetangHover, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HOENN_METANG_1, HoennSeek_Movement_MetangRight
	applymovement LOCALID_HOENN_METANG_2, HoennSeek_Movement_MetangLeft
	waitmovement 0
	playse SE_M_REFLECT
	fadescreen FADE_TO_WHITE
	removeobject LOCALID_HOENN_METANG_1
	removeobject LOCALID_HOENN_METANG_2
	clearflag FLAG_HOENN_HIDE_METAGROSS
	addobject LOCALID_HOENN_METAGROSS
	delay 30
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_METAGROSS, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_MetagrossFused, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	applymovement LOCALID_HOENN_METAGROSS, HoennSeek_Movement_MetagrossLeaves
	waitmovement 0
	removeobject LOCALID_HOENN_METAGROSS
	setflag FLAG_HOENN_HIDE_METAGROSS
	setflag FLAG_HOENN_HIDE_METANG
	setflag FLAG_HOENN_WEEKLY_METAGROSS
	msgbox HoennSeek_Text_MetagrossGone, MSGBOX_DEFAULT
	goto_if_set FLAG_HOENN_METAGROSS_SEEN, HoennSeek_EventScript_MetagrossStarPiece
	setflag FLAG_HOENN_METAGROSS_SEEN
	giveitem ITEM_COMET_SHARD
	releaseall
	end

HoennSeek_EventScript_MetagrossStarPiece:
	giveitem ITEM_STAR_PIECE
	releaseall
	end

HoennSeek_Movement_MetangRight:
	walk_slow_right
	step_end

HoennSeek_Movement_MetangLeft:
	walk_slow_left
	step_end

@ From (11,9) up into the dark at (11,7).
HoennSeek_Movement_MetagrossLeaves:
	face_right
	delay_16
	walk_slow_up
	walk_slow_up
	step_end

HoennSeek_EventScript_CallMetagross::
	setflag FLAG_HOENN_CALL_METAGROSS
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallMetagross
	goto HoennSeek_EventScript_CallEnd

@ ---- Part 23 texts ---------------------------------------------------------
HoennSeek_Text_ChorusIntro:
	.string "A song is drifting over the\n"
	.string "boulders up ahead…\p"
	.string "Better stay out of sight behind\n"
	.string "them, or the singers might fly!$"

HoennSeek_Text_ChorusHide:
	.string "{PLAYER} crouched behind the\n"
	.string "boulder and peeked over it.$"

HoennSeek_Text_ChorusSings:
	.string "An ALTARIA is singing, and the\n"
	.string "SWABLU circle it, humming along!$"

HoennSeek_Text_ChorusHumming:
	.string "Your POKéMON is humming along\n"
	.string "with the chorus, very quietly…\p"
	.string "Play the GLASS FLUTE with them?$"

HoennSeek_Text_ChorusFlute:
	.string "{PLAYER} played the GLASS FLUTE.\p"
	.string "The flute and the song blend\n"
	.string "together into one melody!$"

HoennSeek_Text_ShinyAltaria:
	.string "An ALTARIA with golden wings\n"
	.string "glided down to sing along!\p"
	.string "It noticed {PLAYER}!$"

HoennSeek_Text_ChorusEnds:
	.string "The song ended, and the flock\n"
	.string "flew off over the falls.\p"
	.string "A soft feather drifted down by\n"
	.string "the boulder.$"

HoennSeek_Text_ChorusScattered:
	.string "The SWABLU scattered, and the\n"
	.string "whole flock flew off!\p"
	.string "They won't sing here again\n"
	.string "until next SATURDAY morning.$"

HoennSeek_Text_BagonLeaps:
	.string "A BAGON leapt off the ledge,\n"
	.string "flapping its stubby arms…\p"
	.string "SPLASH! Straight into the pool.$"

HoennSeek_Text_BagonClimbs:
	.string "It climbed back onto the ledge,\n"
	.string "dripping wet, to try again.$"

HoennSeek_Text_BagonBattle:
	.string "The BAGON wants to show you how\n"
	.string "high it can fly!$"

HoennSeek_Text_BagonLeaves:
	.string "The BAGON dove into the pool and\n"
	.string "swam off. It'll be back to leap\l"
	.string "again tomorrow morning.$"

HoennSeek_Text_MetangHover:
	.string "Two METANG are hovering over a\n"
	.string "glowing rock, humming together…$"

HoennSeek_Text_MetagrossFused:
	.string "In a flash of light, the two\n"
	.string "METANG fused into a METAGROSS!$"

HoennSeek_Text_MetagrossGone:
	.string "The METAGROSS lumbered off into\n"
	.string "the dark.\p"
	.string "Something is glinting where the\n"
	.string "rock was glowing…$"

HoennSeek_Text_CallChorus:
	.string "Hi, {PLAYER}! It's MAY.\p"
	.string "Dad saw WINONA at the LEAGUE\n"
	.string "today. She keeps ALTARIA, so\l"
	.string "she hears about every flock.\p"
	.string "She said someone watched the\n"
	.string "chorus above METEOR FALLS\l"
	.string "without scaring a single one!\p"
	.string "Dad laughed and said that had\n"
	.string "to be you. Was it?$"

HoennSeek_Text_CallBagon:
	.string "{PLAYER}! It's BRENDAN!\p"
	.string "MAXIE's researchers were at\n"
	.string "METEOR FALLS with Dad's team.\p"
	.string "They saw a BAGON leap off a\n"
	.string "ledge, climb back up and then\l"
	.string "battle someone. Dad says that\l"
	.string "was you!\p"
	.string "BAGON dream of flying, you know.\n"
	.string "Maybe it wanted to show you!$"

HoennSeek_Text_CallMetagross:
	.string "{PLAYER}! It's BRENDAN!\p"
	.string "PROF. COZMO called Dad from\n"
	.string "METEOR FALLS. He was up all\l"
	.string "night in STEVEN's cave.\p"
	.string "He was charting how the\n"
	.string "meteorite pieces glow, when\l"
	.string "two METANG fused right in\l"
	.string "front of him. You saw it too!\p"
	.string "Dad's never even seen that\n"
	.string "happen. Lucky!$"
