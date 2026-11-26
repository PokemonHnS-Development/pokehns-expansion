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
	@ Route 119's Old Rod level (43-44), not the scaled 60-70: it's the
	@ shabby fish nobody looks at twice (Bryan's review, 21r).
	setwildbattle SPECIES_FEEBAS, 44
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
