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
	goto_if_set FLAG_HOENN_GOT_SINGING_SAND, HoennSeek_EventScript_GlassWorkerSand @ part 24b
HoennSeek_EventScript_GlassWorkerFlute::
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
	call HoennSeek_EventScript_Route113VibravaOnTransition @ part 24b
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
@ dance; each watch leaves a STAR PIECE where the ALTARIA sang (22r, Bryan).
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
	giveitem ITEM_STAR_PIECE
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
	.string "Something glittered on the grass\n"
	.string "where the ALTARIA had sung.$"

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

@ ==========================================================================
@ Part 24a: Flygon's desert song A (Route 111, Fallarbor, Desert Underpass)
@ ROUTE 111, EVENINGS: a TRAPINCH sits out in the desert east of the Mirage
@ Tower (26,58). Coming within four tiles of it (a ring of VAR_TEMP_4
@ triggers) plays the hum: the TRAPINCH pops up, scurries north leaving
@ footprints (the camera follows it) and burrows into a sand hollow at the
@ desert's north edge (29-31, 35-36, painted by composed_maps.json). Once a
@ day until you have the SINGING SAND. Reading the hollow afterwards says
@ the sand drains away underground.
@ FALLARBOR (hint lines, data/hoenn/npc_hints.json): the town's old gentleman
@ remembers the sand draining into the FOSSIL MANIAC's tunnel, and COZMO
@ explains where it goes: the DESERT UNDERPASS.
@ DESERT UNDERPASS, any time, after the hum: a VIBRAVA fans the sand in the
@ nook at the sandy east end (104,4). Entering the nook (row 7) plays the
@ hum; talking starts the battle: scaled, Boomburst (the desert's song),
@ and it can't be caught. Knocked out, it leaves the SINGING SAND (a new key
@ item) and flies off up a crack in the ceiling (part 24b: it circles
@ Route 113's ash). Run, and it stays.
@ ==========================================================================

HoennSeek_EventScript_HiddenEnd24a:
	return

@ ---- Route 111: the hum and the TRAPINCH ----------------------------------
HoennSeek_EventScript_DesertSongOnTransition::
	setflag FLAG_HOENN_HIDE_DESERT_TRAPINCH
	setvar VAR_TEMP_4, 0
	goto_if_set FLAG_HOENN_GOT_SINGING_SAND, HoennSeek_EventScript_HiddenEnd24a
	goto_if_set FLAG_HOENN_DAILY_DESERT_SONG, HoennSeek_EventScript_HiddenEnd24a
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_EVENING, HoennSeek_EventScript_HiddenEnd24a
	clearflag FLAG_HOENN_HIDE_DESERT_TRAPINCH
	setvar VAR_TEMP_4, 1
	return

@ A trigger tile four steps from the TRAPINCH.
HoennSeek_EventScript_DesertSong::
	lockall
	setvar VAR_TEMP_4, 2
	msgbox HoennSeek_Text_DesertHum, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HOENN_DESERT_TRAPINCH, HoennSeek_Movement_TrapinchPopsUp
	waitmovement 0
	playmoncry SPECIES_TRAPINCH, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_TrapinchListens, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	@ Its path runs straight up column 26 (see TrapinchToHollow), and the
	@ ring's north trigger (26,54) sits on it: from there the TRAPINCH would
	@ walk right through you, so step aside first (24r).
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_eq VAR_0x8004, 26, HoennSeek_EventScript_DesertStepAside
	@ Pan to the TRAPINCH, then follow it (the camera takes the same steps).
	setvar VAR_0x8008, 26
	setvar VAR_0x8009, 58
	call HoennSeek_EventScript_StarterPanTo
	applymovement LOCALID_HOENN_DESERT_TRAPINCH, HoennSeek_Movement_TrapinchToHollow
	applymovement OBJ_EVENT_ID_CAMERA, HoennSeek_Movement_TrapinchToHollow
	waitmovement OBJ_EVENT_ID_CAMERA
	waitmovement LOCALID_HOENN_DESERT_TRAPINCH
	@ It burrows into the hollow at (30,35).
	applymovement LOCALID_HOENN_DESERT_TRAPINCH, HoennSeek_Movement_TrapinchBurrows
	waitmovement 0
	@ A puff of sand where it dug in (FLDEFF_SAND_HOLE, DexNav's, loops
	@ forever and never ends: don't use it here).
	setfieldeffectargument 0, 37
	setfieldeffectargument 1, 42
	setfieldeffectargument 2, 0
	setfieldeffectargument 3, 1
	dofieldeffect FLDEFF_DUST
	playse SE_M_DIG
	removeobject LOCALID_HOENN_DESERT_TRAPINCH
	delay 16
	dofieldeffect FLDEFF_DUST
	delay 30
	setflag FLAG_HOENN_HIDE_DESERT_TRAPINCH
	msgbox HoennSeek_Text_TrapinchBurrowed, MSGBOX_DEFAULT
	closemessage
	@ Back to the player, quickly: the hollow can be 30 tiles away.
	setvar VAR_0x8004, 30
	setvar VAR_0x8005, 35
	call HoennSeek_EventScript_DesertCameraBack
	setflag FLAG_HOENN_DESERT_SONG_HEARD
	setflag FLAG_HOENN_DAILY_DESERT_SONG
	releaseall
	end

@ Only (26,54) and (26,62) of the ring are in column 26, and the path goes
@ north, so only the north one is in the way. (25,54) is open sand.
HoennSeek_EventScript_DesertStepAside:
	goto_if_ne VAR_0x8005, 54, HoennSeek_EventScript_HiddenEnd24a
	applymovement LOCALID_PLAYER, HoennSeek_Movement_DesertStepAside
	waitmovement 0
	return

@ Walks the camera from VAR_0x8004/0x8005 back to the player's tile, saved
@ by StarterPanTo in VAR_0x800A/0x800B (x first), then removes it. Like
@ hoenn_starters.inc's StarterPanBack, but four times as fast.
HoennSeek_EventScript_DesertCameraBack:
	goto_if_eq VAR_0x8004, VAR_0x800A, HoennSeek_EventScript_DesertCameraBackY
	goto_if_lt VAR_0x8004, VAR_0x800A, HoennSeek_EventScript_DesertCameraRight
	applymovement OBJ_EVENT_ID_CAMERA, HoennSeek_Movement_CameraFastLeft
	waitmovement 0
	subvar VAR_0x8004, 1
	goto HoennSeek_EventScript_DesertCameraBack
HoennSeek_EventScript_DesertCameraRight:
	applymovement OBJ_EVENT_ID_CAMERA, HoennSeek_Movement_CameraFastRight
	waitmovement 0
	addvar VAR_0x8004, 1
	goto HoennSeek_EventScript_DesertCameraBack
HoennSeek_EventScript_DesertCameraBackY:
	goto_if_eq VAR_0x8005, VAR_0x800B, HoennSeek_EventScript_DesertCameraDone
	goto_if_lt VAR_0x8005, VAR_0x800B, HoennSeek_EventScript_DesertCameraDown
	applymovement OBJ_EVENT_ID_CAMERA, HoennSeek_Movement_CameraFastUp
	waitmovement 0
	subvar VAR_0x8005, 1
	goto HoennSeek_EventScript_DesertCameraBackY
HoennSeek_EventScript_DesertCameraDown:
	applymovement OBJ_EVENT_ID_CAMERA, HoennSeek_Movement_CameraFastDown
	waitmovement 0
	addvar VAR_0x8005, 1
	goto HoennSeek_EventScript_DesertCameraBackY
HoennSeek_EventScript_DesertCameraDone:
	special RemoveCameraObject
	setvar VAR_0x8007, 0
	return

@ Talking to it before the hum starts it too (the triggers are a ring).
HoennSeek_EventScript_DesertTrapinch::
	goto_if_eq VAR_TEMP_4, 1, HoennSeek_EventScript_DesertSong
	end

@ The sand hollow at the desert's north edge (bg events on all six tiles).
HoennSeek_EventScript_DesertHollow::
	goto_if_set FLAG_HOENN_GOT_SINGING_SAND, HoennSeek_EventScript_DesertHollowQuiet
	goto_if_set FLAG_HOENN_DESERT_SONG_HEARD, HoennSeek_EventScript_DesertHollowTracks
	msgbox HoennSeek_Text_DesertHollow, MSGBOX_SIGN
	end
HoennSeek_EventScript_DesertHollowTracks:
	msgbox HoennSeek_Text_DesertHollowTracks, MSGBOX_SIGN
	end
HoennSeek_EventScript_DesertHollowQuiet:
	msgbox HoennSeek_Text_DesertHollowQuiet, MSGBOX_SIGN
	end

HoennSeek_Movement_TrapinchPopsUp:
	jump_in_place_down
	face_up
	step_end

@ (26,58) to the hollow (30,35), around the rocks: the path a BFS over the
@ map's walkable tiles found (no objects on it).
HoennSeek_Movement_TrapinchToHollow:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	step_end

HoennSeek_Movement_DesertStepAside:
	walk_left
	face_down
	step_end

HoennSeek_Movement_TrapinchBurrows:
	face_down
	jump_in_place_down
	jump_in_place_down
	step_end

HoennSeek_Movement_CameraFastLeft:
	walk_faster_left
	step_end
HoennSeek_Movement_CameraFastRight:
	walk_faster_right
	step_end
HoennSeek_Movement_CameraFastUp:
	walk_faster_up
	step_end
HoennSeek_Movement_CameraFastDown:
	walk_faster_down
	step_end

@ ---- Desert Underpass: the VIBRAVA ------------------------------------------
HoennSeek_EventScript_UnderpassOnTransition::
	setflag FLAG_HOENN_HIDE_UNDERPASS_VIBRAVA
	setvar VAR_TEMP_1, 0
	goto_if_unset FLAG_HOENN_DESERT_SONG_HEARD, HoennSeek_EventScript_HiddenEnd24a
	goto_if_set FLAG_HOENN_GOT_SINGING_SAND, HoennSeek_EventScript_HiddenEnd24a
	clearflag FLAG_HOENN_HIDE_UNDERPASS_VIBRAVA
	setvar VAR_TEMP_1, 1
	return

@ Row 7, the only way into the nook: (104,4) is in view from both tiles.
HoennSeek_EventScript_UnderpassHum::
	lockall
	setvar VAR_TEMP_1, 2
	applymovement LOCALID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	msgbox HoennSeek_Text_UnderpassHum, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HOENN_UNDERPASS_VIBRAVA, HoennSeek_Movement_VibravaNotices
	waitmovement 0
	playmoncry SPECIES_VIBRAVA, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_UnderpassVibrava, MSGBOX_DEFAULT
	waitmoncry
	releaseall
	end

HoennSeek_EventScript_UnderpassVibrava::
	lock
	faceplayer
	setvar VAR_TEMP_1, 2
	playmoncry SPECIES_VIBRAVA, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_VibravaBattle, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setflag FLAG_NO_WILD_CATCHING
	setvar VAR_0x8004, SPECIES_VIBRAVA
	special HoennSetupScaledWildBattle
	setvar VAR_0x8005, MOVE_BOOMBURST
	setvar VAR_0x8006, FALSE
	setvar VAR_0x8007, ITEM_NONE
	special HoennTuneWildMon
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	clearflag FLAG_NO_WILD_CATCHING
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_WON, HoennSeek_EventScript_VibravaStays
	msgbox HoennSeek_Text_VibravaDrops, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HOENN_UNDERPASS_VIBRAVA, HoennSeek_Movement_VibravaFliesOff
	waitmovement 0
	removeobject LOCALID_HOENN_UNDERPASS_VIBRAVA
	setflag FLAG_HOENN_HIDE_UNDERPASS_VIBRAVA
	giveitem ITEM_SINGING_SAND
	setflag FLAG_HOENN_GOT_SINGING_SAND
	msgbox HoennSeek_Text_SingingSandHums, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_VibravaStays:
	msgbox HoennSeek_Text_VibravaStays, MSGBOX_DEFAULT
	release
	end

HoennSeek_Movement_VibravaNotices:
	jump_in_place_down
	jump_in_place_down
	step_end

@ Up and away through a crack in the ceiling.
HoennSeek_Movement_VibravaFliesOff:
	face_up
	jump_in_place_up
	walk_faster_up
	set_invisible
	step_end

@ ---- Call -------------------------------------------------------------------
HoennSeek_EventScript_CallSingingSand::
	setflag FLAG_HOENN_CALL_SINGING_SAND
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallSingingSand
	goto HoennSeek_EventScript_CallEnd

@ ---- Texts -----------------------------------------------------------------
HoennSeek_Text_DesertHum:
	.string "A low hum drifts over the dunes,\n"
	.string "rising and falling like a song…$"

HoennSeek_Text_TrapinchListens:
	.string "A TRAPINCH popped up out of the\n"
	.string "sand! It's listening to the hum…$"

HoennSeek_Text_TrapinchBurrowed:
	.string "The TRAPINCH dug into a hollow\n"
	.string "at the edge of the desert.\p"
	.string "The hum faded away with it.$"

HoennSeek_Text_DesertHollow:
	.string "A hollow in the sand. Fine grains\n"
	.string "trickle down into it and vanish.$"

HoennSeek_Text_DesertHollowTracks:
	.string "TRAPINCH tracks lead into the\n"
	.string "hollow and stop.\p"
	.string "Fine sand trickles down into it\n"
	.string "and vanishes somewhere below.\p"
	.string "A faint hum seems to rise from\n"
	.string "deep underground…$"

HoennSeek_Text_DesertHollowQuiet:
	.string "Fine sand trickles down into the\n"
	.string "hollow. All is quiet below.$"

HoennSeek_Text_UnderpassHum:
	.string "A soft hum echoes through the\n"
	.string "tunnel. Fine sand is pouring\l"
	.string "down from a crack overhead…$"

HoennSeek_Text_UnderpassVibrava:
	.string "A VIBRAVA is fanning the falling\n"
	.string "sand with its wings!\p"
	.string "The humming is coming from it!$"

HoennSeek_Text_VibravaBattle:
	.string "The VIBRAVA's wings buzz louder\n"
	.string "and louder!$"

HoennSeek_Text_VibravaDrops:
	.string "The VIBRAVA shook its wings.\n"
	.string "Glittering sand spilled out!\p"
	.string "It flew off up the crack in the\n"
	.string "ceiling, toward the desert above.$"

HoennSeek_Text_SingingSandHums:
	.string "The SINGING SAND hums softly\n"
	.string "whenever it trickles.$"

HoennSeek_Text_VibravaStays:
	.string "The VIBRAVA went back to fanning\n"
	.string "the sand, humming to itself.$"

HoennSeek_Text_CallSingingSand:
	.string "{PLAYER}! It's BRENDAN!\p"
	.string "The FOSSIL MANIAC on ROUTE 114\n"
	.string "just called Dad. He sends Dad\l"
	.string "every fossil he digs up.\p"
	.string "He says something was humming\n"
	.string "in his tunnel for days. Then\l"
	.string "came a battle, and silence!\p"
	.string "He saw you come out with a\n"
	.string "pouch of sand that sings.\p"
	.string "Dad says VIBRAVA hum like that\n"
	.string "to call their flock. Wonder\l"
	.string "where it went!$"

@ ==========================================================================
@ Part 24b: Flygon's desert song B (plan section 7, steps 4-6)
@ ROUTE 113, evenings, once you have the SINGING SAND: the Vibrava from the
@   Desert Underpass flits over the ash outside the Glass Workshop (40,6).
@   Talking to it: it circles, its hum and the sand's answer each other, and
@   it flies off over the workshop roof. Watch-only.
@ GLASSBLOWER: with the sand (and the Vibrava seen) he fuses it into the SAND
@   CHIME. Before the Vibrava, he says the sand is too fine to melt alone and
@   that VIBRAVA come by at sunset. His glass flute offer comes after.
@ LAVARIDGE: the hot-springs granny's hint line ("ring it in the desert at
@   sunset"), from the hint engine.
@ SAND CHIME (key item, used from the bag; src/item_use.c): on Route 111's
@   desert in the evening it raises the MIRAGE TOWER until midnight
@   (FLAG_HOENN_DAILY_MIRAGE_TOWER, read by SetMirageTowerVisibility through
@   HoennMirageTowerRung). Anywhere else, at another hour, or once the tower
@   has crumbled, it just rings.
@ MIRAGE TOWER 4F: a FLYGON guards Emerald's two fossils. A scaled battle
@   (Boomburst, Soft Sand), catchable; knocked out, it's back the next time you
@   come up to 4F; ran from, it stays. Once it's caught the fossils can be
@   taken, and taking one collapses the tower for good (Emerald's scene). A
@   DRAGON FANG lies in the corner. May calls once you've caught it.
@ ==========================================================================

HoennSeek_EventScript_HiddenEnd24b:
	return

@ ---- Route 113 ------------------------------------------------------------
HoennSeek_EventScript_Route113VibravaOnTransition::
	setflag FLAG_HOENN_HIDE_ROUTE113_VIBRAVA
	goto_if_unset FLAG_HOENN_GOT_SINGING_SAND, HoennSeek_EventScript_HiddenEnd24b
	goto_if_set FLAG_HOENN_ROUTE113_VIBRAVA_SEEN, HoennSeek_EventScript_HiddenEnd24b
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_EVENING, HoennSeek_EventScript_HiddenEnd24b
	clearflag FLAG_HOENN_HIDE_ROUTE113_VIBRAVA
	return

HoennSeek_EventScript_Route113Vibrava::
	lock
	faceplayer
	playmoncry SPECIES_VIBRAVA, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_Route113VibravaHums, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	applymovement LOCALID_HOENN_ROUTE113_VIBRAVA, HoennSeek_Movement_VibravaCircles
	waitmovement 0
	msgbox HoennSeek_Text_Route113SandAnswers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HOENN_ROUTE113_VIBRAVA, HoennSeek_Movement_VibravaOverRoof
	waitmovement 0
	removeobject LOCALID_HOENN_ROUTE113_VIBRAVA
	setflag FLAG_HOENN_HIDE_ROUTE113_VIBRAVA
	setflag FLAG_HOENN_ROUTE113_VIBRAVA_SEEN
	msgbox HoennSeek_Text_Route113VibravaGone, MSGBOX_DEFAULT
	release
	end

@ A spin in the falling ash, then a hop.
HoennSeek_Movement_VibravaCircles:
	face_up
	delay_4
	face_right
	delay_4
	face_down
	delay_4
	face_left
	delay_4
	face_up
	delay_4
	face_right
	delay_4
	face_down
	delay_4
	face_left
	delay_4
	jump_in_place_down
	step_end

@ Up over the workshop roof to the north, and out of sight.
HoennSeek_Movement_VibravaOverRoof:
	face_up
	jump_in_place_up
	walk_faster_up
	walk_faster_up
	walk_faster_up
	set_invisible
	step_end

@ ---- The glassblower --------------------------------------------------------
HoennSeek_EventScript_GlassWorkerSand:
	goto_if_set FLAG_HOENN_GOT_SAND_CHIME, HoennSeek_EventScript_GlassWorkerFlute
	lock
	faceplayer
	goto_if_set FLAG_HOENN_ROUTE113_VIBRAVA_SEEN, HoennSeek_EventScript_GlassChimeFuse
	msgbox HoennSeek_Text_GlassSandTooFine, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_GlassChimeFuse:
	msgbox HoennSeek_Text_GlassChimeOffer, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	playse SE_M_FLAMETHROWER
	waitse
	delay 30
	fadescreen FADE_FROM_BLACK
	removeitem ITEM_SINGING_SAND
	giveitem ITEM_SAND_CHIME
	setflag FLAG_HOENN_GOT_SAND_CHIME
	msgbox HoennSeek_Text_GlassChimeGiven, MSGBOX_DEFAULT
	release
	end

@ ---- The Sand Chime (from the bag) ----------------------------------------
HoennSeek_EventScript_RingSandChime::
	lockall
	playse SE_M_HEAL_BELL
	msgbox HoennSeek_Text_ChimeRings, MSGBOX_DEFAULT
	waitse
	specialvar VAR_RESULT, HoennSandChimePlace
	goto_if_eq VAR_RESULT, HOENN_CHIME_ELSEWHERE, HoennSeek_EventScript_ChimeFades
	goto_if_ne VAR_MIRAGE_TOWER_STATE, 0, HoennSeek_EventScript_ChimeTowerGone
	goto_if_set FLAG_HOENN_DAILY_MIRAGE_TOWER, HoennSeek_EventScript_ChimeTowerStands
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_EVENING, HoennSeek_EventScript_ChimeNotSunset
	goto_if_eq VAR_RESULT, HOENN_CHIME_ON_TOWER, HoennSeek_EventScript_ChimeStepBack
	msgbox HoennSeek_Text_ChimeDunesAnswer, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_HOENN_DAILY_MIRAGE_TOWER
	setflag FLAG_HOENN_MIRAGE_RAISED
	@ Reload Route 111 where you stand: its OnTransition now picks the
	@ tower layout (SetMirageTowerVisibility) and starts the shimmer.
	getplayerxy VAR_0x8004, VAR_0x8005
	fadescreen FADE_TO_WHITE
	warpsilent MAP_ROUTE111, VAR_0x8004, VAR_0x8005
	waitstate
	releaseall
	end

HoennSeek_EventScript_ChimeFades:
	msgbox HoennSeek_Text_ChimeFades, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_ChimeTowerGone:
	msgbox HoennSeek_Text_ChimeTowerGone, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_ChimeTowerStands:
	msgbox HoennSeek_Text_ChimeTowerStands, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_ChimeNotSunset:
	msgbox HoennSeek_Text_ChimeNotSunset, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_ChimeStepBack:
	msgbox HoennSeek_Text_ChimeStepBack, MSGBOX_DEFAULT
	releaseall
	end

@ ---- Mirage Tower 4F -------------------------------------------------------
HoennSeek_EventScript_MirageTopOnTransition:
	setflag FLAG_HOENN_HIDE_MIRAGE_FLYGON
	goto_if_set FLAG_HOENN_CAUGHT_FLYGON, HoennSeek_EventScript_MirageTopEnd
	clearflag FLAG_HOENN_HIDE_MIRAGE_FLYGON
HoennSeek_EventScript_MirageTopEnd:
	end

HoennSeek_EventScript_MirageFlygon::
	lock
	faceplayer
	playmoncry SPECIES_FLYGON, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_FlygonSings, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setvar VAR_0x8004, SPECIES_FLYGON
	special HoennSetupScaledWildBattle
	setvar VAR_0x8005, MOVE_BOOMBURST
	setvar VAR_0x8006, FALSE
	setvar VAR_0x8007, ITEM_SOFT_SAND
	special HoennTuneWildMon
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_FlygonCaught
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, HoennSeek_EventScript_FlygonFades
	msgbox HoennSeek_Text_FlygonStays, MSGBOX_DEFAULT
	release
	end

@ Knocked out: it fades like a mirage; it's back the next time you come up.
HoennSeek_EventScript_FlygonFades:
	removeobject LOCALID_HOENN_MIRAGE_FLYGON
	setflag FLAG_HOENN_HIDE_MIRAGE_FLYGON
	msgbox HoennSeek_Text_FlygonFades, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_FlygonCaught:
	removeobject LOCALID_HOENN_MIRAGE_FLYGON
	setflag FLAG_HOENN_HIDE_MIRAGE_FLYGON
	setflag FLAG_HOENN_CAUGHT_FLYGON
	msgbox HoennSeek_Text_FlygonCaught, MSGBOX_DEFAULT
	release
	end

@ The fossils run Emerald's scripts once the Flygon is caught (taking one
@ brings the tower down for good). Until then, it stands guard.
HoennSeek_EventScript_MirageRootFossil::
	goto_if_set FLAG_HOENN_CAUGHT_FLYGON, MirageTower_4F_EventScript_RootFossil
	goto HoennSeek_EventScript_MirageFossilGuarded

HoennSeek_EventScript_MirageClawFossil::
	goto_if_set FLAG_HOENN_CAUGHT_FLYGON, MirageTower_4F_EventScript_ClawFossil
HoennSeek_EventScript_MirageFossilGuarded:
	lock
	msgbox HoennSeek_Text_FossilGuarded, MSGBOX_DEFAULT
	release
	end

@ ---- Call -------------------------------------------------------------------
HoennSeek_EventScript_CallFlygon::
	setflag FLAG_HOENN_CALL_FLYGON
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallFlygon
	goto HoennSeek_EventScript_CallEnd

@ ---- Texts -----------------------------------------------------------------
HoennSeek_Text_Route113VibravaHums:
	.string "It's the VIBRAVA from the DESERT\n"
	.string "UNDERPASS! It's humming softly.$"

HoennSeek_Text_Route113SandAnswers:
	.string "The SINGING SAND in your BAG\n"
	.string "hums back, in the same tune!\p"
	.string "The VIBRAVA looks up at the\n"
	.string "GLASS WORKSHOP's chimney…$"

HoennSeek_Text_Route113VibravaGone:
	.string "The VIBRAVA flew off over the\n"
	.string "roof of the GLASS WORKSHOP.$"

HoennSeek_Text_GlassSandTooFine:
	.string "What's that humming? Sand?\n"
	.string "Let me see… My, it sings!\p"
	.string "Glass from sand like this would\n"
	.string "ring like a bell. But it's far\l"
	.string "too fine to melt on its own.\p"
	.string "A VIBRAVA's wingbeat packs fine\n"
	.string "sand together, they say.\p"
	.string "They come by in the evenings to\n"
	.string "hum in the falling ash. If one\l"
	.string "answers your sand, come back!$"

HoennSeek_Text_GlassChimeOffer:
	.string "A VIBRAVA was humming outside\n"
	.string "my door at sunset! Did you see?\p"
	.string "Its wings packed your sand just\n"
	.string "right. Leave it to me!$"

HoennSeek_Text_GlassChimeGiven:
	.string "A SAND CHIME! Listen to it\n"
	.string "ring. It's the desert's own song.\p"
	.string "The old folks at LAVARIDGE's\n"
	.string "hot springs know desert songs.\p"
	.string "Ask them what a chime like that\n"
	.string "is for!$"

HoennSeek_Text_ChimeRings:
	.string "{PLAYER} rang the SAND CHIME.\n"
	.string "A clear, humming note rings out.$"

HoennSeek_Text_ChimeFades:
	.string "The note fades away. Nothing\n"
	.string "seems to answer it here.$"

HoennSeek_Text_ChimeTowerGone:
	.string "The sand hums back faintly, but\n"
	.string "nothing rises from the dunes\l"
	.string "any more.$"

HoennSeek_Text_ChimeTowerStands:
	.string "The MIRAGE TOWER shimmers in\n"
	.string "the haze, humming along.$"

HoennSeek_Text_ChimeNotSunset:
	.string "The sand stirs, then settles.\p"
	.string "It seems to be waiting for the\n"
	.string "sun to set.$"

HoennSeek_Text_ChimeStepBack:
	.string "The sand shifts under your feet!\p"
	.string "Something wants to rise right\n"
	.string "here. Better step back first.$"

HoennSeek_Text_ChimeDunesAnswer:
	.string "The dunes answer with a deep hum!\p"
	.string "Something is rising out of the\n"
	.string "haze of the sandstorm…$"

HoennSeek_Text_FlygonSings:
	.string "A FLYGON! Its wings hum the same\n"
	.string "song as the SAND CHIME!$"

HoennSeek_Text_FlygonStays:
	.string "The FLYGON settled back in front\n"
	.string "of the FOSSILS, still humming.$"

HoennSeek_Text_FlygonFades:
	.string "The FLYGON flickered like a\n"
	.string "mirage and was gone.\p"
	.string "It might come back if you climb\n"
	.string "up here again.$"

HoennSeek_Text_FlygonCaught:
	.string "The hum around the tower has\n"
	.string "gone quiet…$"

HoennSeek_Text_FossilGuarded:
	.string "The FLYGON hums a warning. It's\n"
	.string "guarding this FOSSIL.$"

HoennSeek_Text_CallFlygon:
	.string "{PLAYER}? It's MAY!\p"
	.string "One of PROF. BIRCH's aides was\n"
	.string "charting the ROUTE 111 desert.\p"
	.string "At sunset, a tower rose right\n"
	.string "out of the sandstorm, she says!\p"
	.string "She saw someone climb it, and\n"
	.string "come down with a FLYGON.\p"
	.string "The PROFESSOR told me it had to\n"
	.string "be you. A mirage tower! I'm so\l"
	.string "jealous! Bye!$"

@ =============================================================================
@ Part 25a: Night dive A (Underwater Route 124)
@ At night a CHINCHOU's light waits in the north-west basin. src/hoenn_lights.c
@ moves it from stop to stop as you swim close (the route is generated from
@ data/hoenn/light_paths.json); stray too far and the lights scatter back to the
@ start. The light leads to the bottom of the south-east basin, slips into a
@ crack there, and the crack stays open from then on (ON_LOAD redraws it). Going
@ down needs a CHINCHOU or LANTURN in the party to light the way. The trench
@ below (Route124_Trench_hoenn) is filled in by part 25b.
@ =============================================================================
HoennSeek_EventScript_UW124OnLoad::
	call_if_set FLAG_HOENN_TRENCH_FOUND, HoennSeek_EventScript_OpenTrenchCrack
	end

@ The basin's bottom edge (44-45, 39) becomes Underwater Route 134's opening
@ pieces, with its light shimmer on the floor above (44, 38), the trigger tile.
HoennSeek_EventScript_OpenTrenchCrack::
	setmetatile 44, 39, 0x22C, TRUE
	setmetatile 45, 39, 0x22D, TRUE
	setmetatile 44, 38, 0x224, FALSE
	return

HoennSeek_EventScript_UW124OnTransition::
	setflag FLAG_HOENN_HIDE_DIVE_LIGHT
	goto_if_set FLAG_HOENN_TRENCH_FOUND, HoennSeek_EventScript_ArmTrenchCrack
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_HiddenEnd25a
	clearflag FLAG_HOENN_HIDE_DIVE_LIGHT
	end

HoennSeek_EventScript_ArmTrenchCrack:
	setvar VAR_TEMP_3, 1
	end

HoennSeek_EventScript_HiddenEnd25a:
	end

HoennSeek_EventScript_DiveLight::
	lock
	playmoncry SPECIES_CHINCHOU, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_DiveLightBlinks, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ Started by src/hoenn_lights.c for any light path (VAR_0x8005 = the light).
HoennSeek_EventScript_LightsScatter::
	lockall
	playse SE_M_DETECT
	msgbox HoennSeek_Text_LightsScatter, MSGBOX_DEFAULT
	releaseall
	end

@ The light's last stop is (44, 37), just above the crack.
HoennSeek_EventScript_DiveLightsEnd::
	lockall
	playmoncry SPECIES_CHINCHOU, CRY_MODE_NORMAL
	applymovement LOCALID_HOENN_DIVE_LIGHT, HoennSeek_Movement_LightIntoCrack
	waitmovement 0
	waitmoncry
	msgbox HoennSeek_Text_LightSlipsDown, MSGBOX_DEFAULT
	closemessage
	removeobject LOCALID_HOENN_DIVE_LIGHT
	setflag FLAG_HOENN_HIDE_DIVE_LIGHT
	setflag FLAG_HOENN_TRENCH_FOUND
	call HoennSeek_EventScript_OpenTrenchCrack
	special DrawWholeMapView
	playse SE_M_BUBBLE
	waitse
	msgbox HoennSeek_Text_CrackGlows, MSGBOX_DEFAULT
	setvar VAR_TEMP_3, 1
	releaseall
	end

HoennSeek_Movement_LightIntoCrack:
	walk_slow_down
	step_end

@ Coord trigger on (44, 38) once the crack is open (VAR_TEMP_3 = 1).
HoennSeek_EventScript_TrenchCrack::
	lockall
	checkspecies SPECIES_LANTURN
	goto_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_TrenchCrackLit
	checkspecies SPECIES_CHINCHOU
	goto_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_TrenchCrackLit
	msgbox HoennSeek_Text_CrackTooDark, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	releaseall
	end

HoennSeek_EventScript_TrenchCrackLit:
	msgbox HoennSeek_Text_CrackLit, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_TrenchCrackStay
	closemessage
	playse SE_M_DIVE
	setflag FLAG_HOENN_TRENCH_ENTERED
	warp MAP_ROUTE124_TRENCH_HOENN, 13, 18
	waitstate
	releaseall
	end

HoennSeek_EventScript_TrenchCrackStay:
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp
	waitmovement 0
	releaseall
	end

@ Coord trigger on the trench's way out (13, 19).
HoennSeek_EventScript_TrenchExit::
	lockall
	playse SE_M_DIVE
	warp MAP_UNDERWATER_ROUTE124, 44, 37
	waitstate
	releaseall
	end

@ ---- Call -------------------------------------------------------------------
HoennSeek_EventScript_CallTrench::
	setflag FLAG_HOENN_CALL_TRENCH
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallTrench
	goto HoennSeek_EventScript_CallEnd

@ ---- Texts -----------------------------------------------------------------
HoennSeek_Text_DiveLightBlinks:
	.string "The CHINCHOU's lights blink on and\n"
	.string "off, on and off…\p"
	.string "It seems to want you to follow it.$"

HoennSeek_Text_LightsScatter:
	.string "The light you were following\n"
	.string "flickered out…\p"
	.string "Far back the way you came, a faint\n"
	.string "glow lights up again.$"

HoennSeek_Text_LightSlipsDown:
	.string "The CHINCHOU slipped down into a\n"
	.string "crack in the seabed!$"

HoennSeek_Text_CrackGlows:
	.string "Light glows up out of the crack.\p"
	.string "There's a deep trench down there!$"

HoennSeek_Text_CrackTooDark:
	.string "The crack drops away into water\n"
	.string "as black as ink.\p"
	.string "A POKéMON that glows might light\n"
	.string "the way down…$"

HoennSeek_Text_CrackLit:
	.string "Your glowing POKéMON lights up the\n"
	.string "crack. It's wide enough to swim\l"
	.string "down!\p"
	.string "Dive down into the trench?$"

HoennSeek_Text_CallTrench:
	.string "Hey, {PLAYER}! It's BRENDAN.\p"
	.string "A diver from MOSSDEEP dropped by\n"
	.string "the lab to see PROF. BIRCH.\p"
	.string "She was night diving off ROUTE 124\n"
	.string "and saw a trainer follow CHINCHOU\l"
	.string "lights right down into the seabed!\p"
	.string "Dad says nobody but you would\n"
	.string "try that. What's down there?\p"
	.string "Tell me next time, okay? Later!$"

@ =============================================================================
@ Part 25b: Night dive B (Route124_Trench_hoenn)
@ A guardian waits at the bottom of the trench (17,14), a different one by
@ weekday: HUNTAIL Mon/Wed/Fri, GOREBYSS Tue/Thu/Sat, RELICANTH Sun. Each is a
@ scaled wild battle with its hidden ability and perfect IVs; run and it
@ stays, knock it out and it's gone until its next day. A pearl bed of three
@ CLAMPERL in the west basin gives a pearl each, once a week. Once all three
@ guardians are caught, the mound's old cavern door (13-15, 8-9) opens and
@ leads into its hollow (12-15, 1-3), where the DEEP SEA TOOTH and DEEP SEA
@ SCALE lie; the hollow's glimmer (14,3) takes you back out.
@ =============================================================================
HoennSeek_EventScript_TrenchOnLoad::
	call_if_set FLAG_HOENN_TRENCH_DOOR_OPEN, HoennSeek_EventScript_OpenTrenchDoor
	end

@ The door is Underwater Route 128's Seafloor Cavern door (part 25a's
@ composed map filled it in), and the hollow gets its glimmer back.
HoennSeek_EventScript_OpenTrenchDoor::
	setmetatile 13, 8, 0x265, TRUE
	setmetatile 14, 8, 0x266, TRUE
	setmetatile 15, 8, 0x267, TRUE
	setmetatile 13, 9, 0x26D, TRUE
	setmetatile 14, 9, 0x26E, FALSE
	setmetatile 15, 9, 0x26F, TRUE
	setmetatile 14, 3, 0x2B8, FALSE
	return

HoennSeek_EventScript_TrenchOnTransition::
	setflag FLAG_HOENN_HIDE_HUNTAIL
	setflag FLAG_HOENN_HIDE_GOREBYSS
	setflag FLAG_HOENN_HIDE_RELICANTH
	call_if_set FLAG_HOENN_TRENCH_DOOR_OPEN, HoennSeek_EventScript_ArmTrenchDoor
	goto_if_set FLAG_HOENN_DAILY_TRENCH_GUARDIAN, HoennSeek_EventScript_HiddenEnd25a
	specialvar VAR_RESULT, GetDayOfWeek
	switch VAR_RESULT
	case HOENN_SUNDAY, HoennSeek_EventScript_TrenchShowRelicanth
	case HOENN_TUESDAY, HoennSeek_EventScript_TrenchShowGorebyss
	case HOENN_THURSDAY, HoennSeek_EventScript_TrenchShowGorebyss
	case HOENN_SATURDAY, HoennSeek_EventScript_TrenchShowGorebyss
	goto_if_set FLAG_HOENN_CAUGHT_HUNTAIL, HoennSeek_EventScript_HiddenEnd25a
	clearflag FLAG_HOENN_HIDE_HUNTAIL
	end

HoennSeek_EventScript_TrenchShowGorebyss:
	goto_if_set FLAG_HOENN_CAUGHT_GOREBYSS, HoennSeek_EventScript_HiddenEnd25a
	clearflag FLAG_HOENN_HIDE_GOREBYSS
	end

HoennSeek_EventScript_TrenchShowRelicanth:
	goto_if_set FLAG_HOENN_CAUGHT_RELICANTH, HoennSeek_EventScript_HiddenEnd25a
	clearflag FLAG_HOENN_HIDE_RELICANTH
	end

HoennSeek_EventScript_ArmTrenchDoor:
	setvar VAR_TEMP_2, 1
	return

@ ---- Guardians -------------------------------------------------------------
@ Flag commands take no vars, so each guardian has its own tail.
HoennSeek_EventScript_TrenchHuntail::
	lock
	setvar VAR_0x8004, SPECIES_HUNTAIL
	setvar VAR_0x8005, MOVE_SUCKER_PUNCH
	setvar VAR_0x8007, ITEM_BIG_PEARL
	call HoennSeek_EventScript_TrenchGuardianBattle
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_TrenchGuardianEnd
	removeobject LOCALID_HOENN_TRENCH_HUNTAIL
	setflag FLAG_HOENN_HIDE_HUNTAIL
	goto_if_ne VAR_0x8000, B_OUTCOME_CAUGHT, HoennSeek_EventScript_TrenchGuardianSinks
	setflag FLAG_HOENN_CAUGHT_HUNTAIL
	goto HoennSeek_EventScript_TrenchGuardianCaught

HoennSeek_EventScript_TrenchGorebyss::
	lock
	setvar VAR_0x8004, SPECIES_GOREBYSS
	setvar VAR_0x8005, MOVE_SHELL_SMASH
	setvar VAR_0x8007, ITEM_HEART_SCALE
	call HoennSeek_EventScript_TrenchGuardianBattle
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_TrenchGuardianEnd
	removeobject LOCALID_HOENN_TRENCH_GOREBYSS
	setflag FLAG_HOENN_HIDE_GOREBYSS
	goto_if_ne VAR_0x8000, B_OUTCOME_CAUGHT, HoennSeek_EventScript_TrenchGuardianSinks
	setflag FLAG_HOENN_CAUGHT_GOREBYSS
	goto HoennSeek_EventScript_TrenchGuardianCaught

HoennSeek_EventScript_TrenchRelicanth::
	lock
	setvar VAR_0x8004, SPECIES_RELICANTH
	setvar VAR_0x8005, MOVE_HEAD_SMASH
	setvar VAR_0x8007, ITEM_STAR_PIECE
	call HoennSeek_EventScript_TrenchGuardianBattle
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_TrenchGuardianEnd
	removeobject LOCALID_HOENN_TRENCH_RELICANTH
	setflag FLAG_HOENN_HIDE_RELICANTH
	goto_if_ne VAR_0x8000, B_OUTCOME_CAUGHT, HoennSeek_EventScript_TrenchGuardianSinks
	setflag FLAG_HOENN_CAUGHT_RELICANTH
	goto HoennSeek_EventScript_TrenchGuardianCaught

@ VAR_0x8004 species, 0x8005 its move, 0x8007 its held item (always set: a
@ wild HUNTAIL/GOREBYSS with no item can roll the DEEP SEA TOOTH/SCALE, the
@ hollow's reward, at the start of the battle). Returns VAR_RESULT FALSE if the player
@ ran (it stays), else TRUE with the battle outcome in VAR_0x8000.
HoennSeek_EventScript_TrenchGuardianBattle:
	playmoncry VAR_0x8004, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_TrenchGuardian, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setflag FLAG_HOENN_TRENCH_GUARDIAN_MET
	special HoennSetupScaledWildBattle
	setvar VAR_0x8006, TRUE
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, HOENN_TUNE_HIDDEN_ABILITY
	special HoennTuneWildMonSlot
	dowildbattle
	specialvar VAR_0x8000, GetBattleOutcome
	setvar VAR_RESULT, FALSE
	goto_if_eq VAR_0x8000, B_OUTCOME_RAN, HoennSeek_EventScript_HiddenReturn
	goto_if_eq VAR_0x8000, B_OUTCOME_PLAYER_TELEPORTED, HoennSeek_EventScript_HiddenReturn
	setflag FLAG_HOENN_DAILY_TRENCH_GUARDIAN
	setvar VAR_RESULT, TRUE
	return

HoennSeek_EventScript_TrenchGuardianSinks:
	msgbox HoennSeek_Text_TrenchGuardianSinks, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_TrenchGuardianCaught:
	goto_if_unset FLAG_HOENN_CAUGHT_HUNTAIL, HoennSeek_EventScript_TrenchGuardianEnd
	goto_if_unset FLAG_HOENN_CAUGHT_GOREBYSS, HoennSeek_EventScript_TrenchGuardianEnd
	goto_if_unset FLAG_HOENN_CAUGHT_RELICANTH, HoennSeek_EventScript_TrenchGuardianEnd
	@ The last of the three: the mound's door opens.
	playse SE_M_EARTHQUAKE
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ number of shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	setflag FLAG_HOENN_TRENCH_DOOR_OPEN
	call HoennSeek_EventScript_OpenTrenchDoor
	special DrawWholeMapView
	setvar VAR_TEMP_2, 1
	msgbox HoennSeek_Text_TrenchDoorOpens, MSGBOX_DEFAULT
HoennSeek_EventScript_TrenchGuardianEnd:
	release
	end

@ ---- The door and the hollow -------------------------------------------------
HoennSeek_EventScript_TrenchDoor::
	lockall
	playse SE_M_DIVE
	warp MAP_ROUTE124_TRENCH_HOENN, 13, 2
	waitstate
	releaseall
	end

HoennSeek_EventScript_TrenchHollowExit::
	lockall
	playse SE_M_DIVE
	warp MAP_ROUTE124_TRENCH_HOENN, 14, 10
	waitstate
	releaseall
	end

@ ---- Pearl bed ----------------------------------------------------------------
HoennSeek_EventScript_PearlBed1::
	lock
	playmoncry SPECIES_CLAMPERL, CRY_MODE_NORMAL
	goto_if_set FLAG_HOENN_WEEKLY_PEARL_1, HoennSeek_EventScript_PearlBedShut
	call HoennSeek_EventScript_PearlBedOpens
	giveitem ITEM_BIG_PEARL
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_PearlBedFull
	setflag FLAG_HOENN_WEEKLY_PEARL_1
	release
	end

HoennSeek_EventScript_PearlBed2::
	lock
	playmoncry SPECIES_CLAMPERL, CRY_MODE_NORMAL
	goto_if_set FLAG_HOENN_WEEKLY_PEARL_2, HoennSeek_EventScript_PearlBedShut
	call HoennSeek_EventScript_PearlBedOpens
	giveitem ITEM_BIG_PEARL
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_PearlBedFull
	setflag FLAG_HOENN_WEEKLY_PEARL_2
	release
	end

HoennSeek_EventScript_PearlBed3::
	lock
	playmoncry SPECIES_CLAMPERL, CRY_MODE_NORMAL
	goto_if_set FLAG_HOENN_WEEKLY_PEARL_3, HoennSeek_EventScript_PearlBedShut
	call HoennSeek_EventScript_PearlBedOpens
	giveitem ITEM_PEARL_STRING
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_PearlBedFull
	setflag FLAG_HOENN_WEEKLY_PEARL_3
	release
	end

HoennSeek_EventScript_PearlBedOpens:
	msgbox HoennSeek_Text_PearlBedOpens, MSGBOX_DEFAULT
	waitmoncry
	return

HoennSeek_EventScript_PearlBedShut:
	msgbox HoennSeek_Text_PearlBedShut, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_PearlBedFull:
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
	release
	end

@ ---- Call -------------------------------------------------------------------
HoennSeek_EventScript_CallTrenchDoor::
	setflag FLAG_HOENN_CALL_TRENCH_DOOR
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallTrenchDoor
	goto HoennSeek_EventScript_CallEnd

@ ---- Texts -----------------------------------------------------------------
HoennSeek_Text_TrenchGuardian:
	.string "Something huge stirs at the\n"
	.string "bottom of the trench!$"

HoennSeek_Text_TrenchGuardianSinks:
	.string "It sank back into the dark.\p"
	.string "Something else may be waiting\n"
	.string "here tomorrow…$"

HoennSeek_Text_TrenchDoorOpens:
	.string "The seabed rumbled…\p"
	.string "A dark doorway has opened in the\n"
	.string "face of the mound!$"

HoennSeek_Text_PearlBedOpens:
	.string "The CLAMPERL opened its shell.\n"
	.string "There's a pearl inside!$"

HoennSeek_Text_PearlBedShut:
	.string "The CLAMPERL is keeping its shell\n"
	.string "shut tight.\p"
	.string "A new pearl takes a week to grow.$"

HoennSeek_Text_CallTrenchDoor:
	.string "{PLAYER}! It's MAY!\p"
	.string "That diver from MOSSDEEP came by\n"
	.string "the lab again. She talks to PROF.\l"
	.string "BIRCH about everything she sees!\p"
	.string "She says the big POKéMON in the\n"
	.string "ROUTE 124 trench are all gone,\l"
	.string "and the seabed shook last night.\p"
	.string "You caught all three, didn't you?\n"
	.string "Brendan owes me a lunch. Bye!$"

@ =============================================================================
@ Part 26a: Ice chamber A (ShoalCave_LowTideIceRoom, ShoalCave_IceChamber_hoenn)
@ At low tide a ladder hole opens in the ice room's floor (16,21), in the strip
@ of ice in its south-east corner; at high tide sea ice plugs it. The tide is
@ Emerald's FLAG_SYS_SHOAL_TIDE (set = high), which UpdateShoalTideFlag only
@ changes when you walk in from Route 125, so it can't turn while you're inside.
@ The hole leads down into the frozen chamber: a sliding-ice hall (a puzzle,
@ 12 moves at best; every slide can get back to the ladder), and through the
@ one gap in its ice wall (10,13-15), the inner chamber. There a GLALIE waits
@ on the frozen pool by day (any time but night): a scaled wild battle with
@ perfect IVs and Head Smash. Run and it stays; knock it out and it's back
@ tomorrow; caught, it's gone. Part 26b brings the chamber's night.
@ =============================================================================

@ ---- The ice room's hole ------------------------------------------------------
@ The layout keeps plain ice at (16,21), so the hole only exists while this
@ draws it. The warp there (warp 1) only fires on the ladder's MB_LADDER.
HoennSeek_EventScript_IceRoomOnLoad::
	goto_if_set FLAG_SYS_SHOAL_TIDE, HoennSeek_EventScript_IceRoomHolePlugged
	setmetatile 16, 21, 0x38B, FALSE
	end

HoennSeek_EventScript_IceRoomHolePlugged:
	setmetatile 16, 21, 0x37D, TRUE
	end

@ Its sign: only the plug at high tide has something to say.
HoennSeek_EventScript_IceRoomHole::
	goto_if_unset FLAG_SYS_SHOAL_TIDE, HoennSeek_EventScript_IceRoomHoleEnd
	msgbox HoennSeek_Text_IceRoomPlug, MSGBOX_SIGN
HoennSeek_EventScript_IceRoomHoleEnd:
	end

@ ---- The chamber -------------------------------------------------------------
HoennSeek_EventScript_IceChamberOnTransition::
	setflag FLAG_HOENN_ICE_CHAMBER_FOUND
	setflag FLAG_HOENN_HIDE_ICE_GLALIE
	setflag FLAG_HOENN_HIDE_ICE_FROSLASS
	setvar VAR_TEMP_4, 0
	gettimeofday
	goto_if_eq VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_IceChamberNight
	goto_if_set FLAG_HOENN_CAUGHT_ICE_GLALIE, HoennSeek_EventScript_IceChamberEnd
	goto_if_set FLAG_HOENN_DAILY_ICE_GLALIE, HoennSeek_EventScript_IceChamberEnd
	clearflag FLAG_HOENN_HIDE_ICE_GLALIE
HoennSeek_EventScript_IceChamberEnd:
	end

@ Part 26b: at night the Froslass waits in the first pillar (the object's
@ template spot, 11,6), and the frame script shows her once on arrival.
HoennSeek_EventScript_IceChamberNight:
	goto_if_set FLAG_HOENN_CAUGHT_ICE_FROSLASS, HoennSeek_EventScript_IceChamberEnd
	goto_if_set FLAG_HOENN_DAILY_ICE_FROSLASS, HoennSeek_EventScript_IceChamberEnd
	clearflag FLAG_HOENN_HIDE_ICE_FROSLASS
	setvar VAR_TEMP_4, 1
	setvar VAR_TEMP_5, 1
	end

HoennSeek_EventScript_IceGlalie::
	lock
	playmoncry SPECIES_GLALIE, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_IceGlalie, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setflag FLAG_HOENN_ICE_GLALIE_MET
	setvar VAR_0x8004, SPECIES_GLALIE
	special HoennSetupScaledWildBattle
	setvar VAR_0x8005, MOVE_HEAD_SMASH
	setvar VAR_0x8006, TRUE
	setvar VAR_0x8007, ITEM_NONE
	special HoennTuneWildMon
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, HoennSeek_EventScript_IceGlalieStays
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, HoennSeek_EventScript_IceGlalieStays
	setflag FLAG_HOENN_DAILY_ICE_GLALIE
	removeobject LOCALID_HOENN_ICE_GLALIE
	setflag FLAG_HOENN_HIDE_ICE_GLALIE
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_IceGlalieCaught
	msgbox HoennSeek_Text_IceGlalieGone, MSGBOX_DEFAULT
	release
	end

HoennSeek_EventScript_IceGlalieCaught:
	setflag FLAG_HOENN_CAUGHT_ICE_GLALIE
HoennSeek_EventScript_IceGlalieStays:
	release
	end

@ ---- Part 26b: the Froslass's pillar chase -----------------------------------
@ The chamber's ice rocks are its pillars. At night a FROSLASS's reflection
@ shows in one of them (her object, standing on the rock: the rocks have no top
@ layer, so she's drawn over them). Touch that pillar and she flickers out and
@ into the next one, and the camera shows you where; touch any other pillar
@ while she's in the ice and a freezing gust blows you back to the ladder,
@ which starts the chase over. Getting to each pillar is the sliding puzzle:
@ (6,9) and (12,9) can only be touched from the tile below them.
@ VAR_TEMP_4: 0 no chase, 1-5 the pillar she's in, 6 she has stepped out.
@ Pillars, in order: (11,6), (6,9), (15,4), (12,9) in the hall, then (15,20)
@ in the inner chamber's south-east corner, where she steps out.
HoennSeek_EventScript_IceFroslassIntro::
	lockall
	setvar VAR_TEMP_5, 2
	delay 30
	msgbox HoennSeek_Text_IceFroslassIntro, MSGBOX_DEFAULT
	closemessage
	@ The first pillar is at the bottom edge of the screen from the ladder,
	@ under the message box, so the camera goes to show it.
	setvar VAR_0x8008, 11
	setvar VAR_0x8009, 6
	call HoennSeek_EventScript_StarterPanTo
	playse SE_M_HAZE
	applymovement LOCALID_HOENN_ICE_FROSLASS, HoennSeek_Movement_IceFroslassFlicker
	waitmovement 0
	msgbox HoennSeek_Text_IceFroslassIntro2, MSGBOX_DEFAULT
	closemessage
	call HoennSeek_EventScript_StarterPanBack
	releaseall
	end

HoennSeek_EventScript_IceFroslass::
	lock
	goto_if_ge VAR_TEMP_4, 5, HoennSeek_EventScript_IceFroslassStepOut
	playse SE_M_HAZE
	applymovement LOCALID_HOENN_ICE_FROSLASS, HoennSeek_Movement_IceFroslassFlicker
	waitmovement 0
	removeobject LOCALID_HOENN_ICE_FROSLASS
	addvar VAR_TEMP_4, 1
	call_if_eq VAR_TEMP_4, 2, HoennSeek_EventScript_IceFroslassTo2
	call_if_eq VAR_TEMP_4, 3, HoennSeek_EventScript_IceFroslassTo3
	call_if_eq VAR_TEMP_4, 4, HoennSeek_EventScript_IceFroslassTo4
	call_if_eq VAR_TEMP_4, 5, HoennSeek_EventScript_IceFroslassTo5
	msgbox HoennSeek_Text_IceFroslassSlips, MSGBOX_DEFAULT
	closemessage
	@ Show the pillar she went to, then come back.
	call HoennSeek_EventScript_StarterPanTo
	@ removeobject set her flag; clear it, or she isn't respawned once the
	@ camera leaves her pillar and comes back.
	clearflag FLAG_HOENN_HIDE_ICE_FROSLASS
	addobject LOCALID_HOENN_ICE_FROSLASS
	playse SE_M_HAZE
	applymovement LOCALID_HOENN_ICE_FROSLASS, HoennSeek_Movement_IceFroslassFlicker
	waitmovement 0
	delay 30
	call HoennSeek_EventScript_StarterPanBack
	release
	end

@ Each sets her object's spot and the camera's target (VAR_0x8008/0x8009).
HoennSeek_EventScript_IceFroslassTo2:
	setobjectxyperm LOCALID_HOENN_ICE_FROSLASS, 6, 9
	setvar VAR_0x8008, 6
	setvar VAR_0x8009, 9
	return
HoennSeek_EventScript_IceFroslassTo3:
	setobjectxyperm LOCALID_HOENN_ICE_FROSLASS, 15, 4
	setvar VAR_0x8008, 15
	setvar VAR_0x8009, 4
	return
HoennSeek_EventScript_IceFroslassTo4:
	setobjectxyperm LOCALID_HOENN_ICE_FROSLASS, 12, 9
	setvar VAR_0x8008, 12
	setvar VAR_0x8009, 9
	return
HoennSeek_EventScript_IceFroslassTo5:
	setobjectxyperm LOCALID_HOENN_ICE_FROSLASS, 15, 20
	setvar VAR_0x8008, 15
	setvar VAR_0x8009, 20
	return

@ The last pillar: she steps out and fights. If you ran, she's still there
@ (stage 6) and talking to her fights again.
HoennSeek_EventScript_IceFroslassStepOut:
	goto_if_eq VAR_TEMP_4, 6, HoennSeek_EventScript_IceFroslassBattle
	setvar VAR_TEMP_4, 6
	setflag FLAG_HOENN_ICE_FROSLASS_MET
	playmoncry SPECIES_FROSLASS, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_IceFroslassOut, MSGBOX_DEFAULT
	waitmoncry
	closemessage
HoennSeek_EventScript_IceFroslassBattle:
	setvar VAR_0x8004, SPECIES_FROSLASS
	special HoennSetupScaledWildBattle
	setvar VAR_0x8005, MOVE_SPIRIT_SHACKLE
	setvar VAR_0x8006, TRUE
	setvar VAR_0x8007, ITEM_NONE
	special HoennTuneWildMon
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, HoennSeek_EventScript_IceFroslassStays
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, HoennSeek_EventScript_IceFroslassStays
	setflag FLAG_HOENN_DAILY_ICE_FROSLASS
	removeobject LOCALID_HOENN_ICE_FROSLASS
	setflag FLAG_HOENN_HIDE_ICE_FROSLASS
	setvar VAR_TEMP_4, 0
	call_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_IceFroslassCaught
	call_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, HoennSeek_EventScript_IceFroslassGone
	goto_if_set FLAG_HOENN_GOT_FROST_FEATHER, HoennSeek_EventScript_IceFroslassStays
	@ Behind her, the pillar's ice holds Articuno's feather.
	msgbox HoennSeek_Text_IceFeatherGlint, MSGBOX_DEFAULT
	giveitem ITEM_FROST_FEATHER
	setflag FLAG_HOENN_GOT_FROST_FEATHER
	msgbox HoennSeek_Text_IceFeatherGot, MSGBOX_DEFAULT
HoennSeek_EventScript_IceFroslassStays:
	release
	end

HoennSeek_EventScript_IceFroslassCaught:
	setflag FLAG_HOENN_CAUGHT_ICE_FROSLASS
	return

HoennSeek_EventScript_IceFroslassGone:
	msgbox HoennSeek_Text_IceFroslassGone, MSGBOX_DEFAULT
	return

@ Every ice rock in the chamber (bg events). While she's in the ice, the
@ wrong one blows you back to the ladder; the right one is her object, which
@ the game finds first.
HoennSeek_EventScript_IcePillar::
	goto_if_eq VAR_TEMP_4, 0, HoennSeek_EventScript_IcePillarEnd
	goto_if_eq VAR_TEMP_4, 6, HoennSeek_EventScript_IcePillarEnd
	lockall
	playse SE_M_ICY_WIND
	msgbox HoennSeek_Text_IceGust, MSGBOX_DEFAULT
	closemessage
	warpwhitefade MAP_SHOAL_CAVE_ICE_CHAMBER_HOENN, 0
	waitstate
	releaseall
HoennSeek_EventScript_IcePillarEnd:
	end

HoennSeek_Movement_IceFroslassFlicker:
	set_invisible
	delay_4
	set_visible
	delay_4
	set_invisible
	delay_4
	set_visible
	delay_8
	step_end

@ ---- Call -------------------------------------------------------------------
HoennSeek_EventScript_CallIceGlalie::
	setflag FLAG_HOENN_CALL_ICE_GLALIE
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallIceGlalie
	goto HoennSeek_EventScript_CallEnd

HoennSeek_EventScript_CallFrostFeather::
	setflag FLAG_HOENN_CALL_FROST_FEATHER
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallFrostFeather
	goto HoennSeek_EventScript_CallEnd

@ ---- Texts -----------------------------------------------------------------
HoennSeek_Text_IceRoomPlug:
	.string "A lump of sea ice plugs a hole in\n"
	.string "the floor.\p"
	.string "Seawater sloshes somewhere\n"
	.string "underneath it.\p"
	.string "Maybe it drains away when the\n"
	.string "tide goes out…$"

HoennSeek_Text_IceGlalie:
	.string "A GLALIE sits frozen in the ice.\n"
	.string "Its eyes snap open!$"

HoennSeek_Text_IceGlalieGone:
	.string "The GLALIE rolled away into the\n"
	.string "ice and was gone.\p"
	.string "It might be back tomorrow…$"

HoennSeek_Text_CallIceGlalie:
	.string "{PLAYER}! It's BRENDAN.\p"
	.string "The old man who makes SHELL BELLS\n"
	.string "in SHOAL CAVE came by the lab.\l"
	.string "He trades shells with the PROF.\p"
	.string "He saw you climb down through the\n"
	.string "ice at low tide, then heard a\l"
	.string "GLALIE roar from under the floor!\p"
	.string "He says it's sat down there since\n"
	.string "before he was born. Bet it hit\l"
	.string "hard! Talk later!$"

HoennSeek_Text_IceFroslassIntro:
	.string "A chill runs down your back.\n"
	.string "Something moved in the ice…$"

HoennSeek_Text_IceFroslassIntro2:
	.string "A FROSLASS's pale face looks out\n"
	.string "from inside a pillar of ice!$"

HoennSeek_Text_IceFroslassSlips:
	.string "The FROSLASS's reflection slipped\n"
	.string "away through the ice!$"

HoennSeek_Text_IceGust:
	.string "Wrong pillar! A freezing gust\n"
	.string "howls out of the ice!$"

HoennSeek_Text_IceFroslassOut:
	.string "The FROSLASS stepped out of\n"
	.string "the ice!$"

HoennSeek_Text_IceFroslassGone:
	.string "The FROSLASS melted back into the\n"
	.string "ice and was gone.\p"
	.string "She might walk the ice again\n"
	.string "tomorrow night…$"

HoennSeek_Text_IceFeatherGlint:
	.string "Something glints deep in the\n"
	.string "pillar where she stood…\p"
	.string "A long blue feather, frozen into\n"
	.string "the ice! It slides out cleanly.$"

HoennSeek_Text_IceFeatherGot:
	.string "It's as cold as the ice it was in,\n"
	.string "but it doesn't melt at all.$"

HoennSeek_Text_CallFrostFeather:
	.string "Hi, {PLAYER}! It's MAY.\p"
	.string "The SHELL BELL man from SHOAL\n"
	.string "CAVE was at the lab again.\p"
	.string "He says you went down to the ice\n"
	.string "at night and came back with a\l"
	.string "blue feather that won't melt!\p"
	.string "The PROF thinks it's ARTICUNO's.\n"
	.string "It flew over our sea years ago.\p"
	.string "BILL in CERULEAN collects stories\n"
	.string "about the legendary birds.\l"
	.string "He'd love to hear about this!\p"
	.string "Keep it safe, okay? Bye!$"
