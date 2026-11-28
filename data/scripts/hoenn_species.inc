@ Hoenn & Seek 2.0 (part 18): species events A. Design: hoenn-docs/2.0-plan.md
@ section 6 (and section 5 for the Mudkip pond). Flags and vars: part 18's
@ section of include/constants/hoenn_events.h. Calls: src/hoenn_species.c.
@
@ None of these Pokémon can be caught except the Ralts, which joins you. Each
@ scene is decided on arrival by a one-line OnTransition `call` in the map's own
@ script, which shows the objects and arms the trigger tiles (VAR_TEMP_*).

HoennSeek_EventScript_SpeciesReturn::
	return

@ ==========================================================================
@ Route 102, mornings: the Mudkip pond and the Ralts. Route 102 had no map
@ scripts; its OnTransition is HoennSeek_EventScript_Route102OnTransition.
@ ==========================================================================

HoennSeek_EventScript_Route102OnTransition::
	setflag FLAG_HOENN_HIDE_POND_FAMILY
	setflag FLAG_HOENN_HIDE_RALTS
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_MORNING, HoennSeek_EventScript_SpeciesEnd
	call HoennSeek_EventScript_PondSetup
	call HoennSeek_EventScript_RaltsSetup
HoennSeek_EventScript_SpeciesEnd::
	end

@ The Swampert family is out on mornings they haven't dived yet, except on the
@ route's rain day (they stay under while it pours; 17r-d took Route 102 out of
@ the weather cycles, so the check only matters if it goes back in). Trigger tiles: row 8,
@ x 35-47, the way to the pond bank and the grass beside it.
HoennSeek_EventScript_PondSetup:
	goto_if_set FLAG_HOENN_DAILY_POND, HoennSeek_EventScript_SpeciesReturn
	specialvar VAR_RESULT, HoennIsSpecialWeatherHere
	goto_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_SpeciesReturn
	clearflag FLAG_HOENN_HIDE_POND_FAMILY
	setvar VAR_TEMP_2, 1
	return

HoennSeek_EventScript_PondScene::
	lockall
	setvar VAR_TEMP_2, 0
	setflag FLAG_HOENN_DAILY_POND
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	waitmovement 0
	msgbox HoennSeek_Text_PondPractice, MSGBOX_DEFAULT
	closemessage
	@ Practice: each Mudkip shoots a jet, the Swampert nods.
	playse SE_M_BUBBLE
	applymovement LOCALID_HOENN_POND_MUDKIP_1, HoennSeek_Movement_PondHop
	waitmovement 0
	playse SE_M_BUBBLE
	applymovement LOCALID_HOENN_POND_MUDKIP_2, HoennSeek_Movement_PondHop
	waitmovement 0
	playmoncry SPECIES_MUDKIP, CRY_MODE_NORMAL
	applymovement LOCALID_HOENN_POND_MUDKIP_1, HoennSeek_Movement_PondHop
	applymovement LOCALID_HOENN_POND_MUDKIP_2, HoennSeek_Movement_PondHop
	waitmovement 0
	waitmoncry
	@ The Swampert's fin feels the weather turn.
	playse SE_PIN
	applymovement LOCALID_HOENN_POND_SWAMPERT, Common_Movement_ExclamationMark
	waitmovement 0
	playmoncry SPECIES_SWAMPERT, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_PondFin, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	applymovement LOCALID_HOENN_POND_SWAMPERT, HoennSeek_Movement_PondSwampertIn
	applymovement LOCALID_HOENN_POND_MUDKIP_1, HoennSeek_Movement_PondMudkip1In
	applymovement LOCALID_HOENN_POND_MUDKIP_2, HoennSeek_Movement_PondMudkip2In
	waitmovement 0
	playse SE_M_DIVE
	removeobject LOCALID_HOENN_POND_MUDKIP_1
	removeobject LOCALID_HOENN_POND_MUDKIP_2
	delay 10
	removeobject LOCALID_HOENN_POND_SWAMPERT
	delay 40
	@ The shower they felt coming.
	playse SE_M_RAIN_DANCE
	setweather WEATHER_RAIN
	doweather
	delay 60
	msgbox HoennSeek_Text_PondRain, MSGBOX_DEFAULT
	setflag FLAG_HOENN_POND_SEEN
	releaseall
	end

@ Only reachable from the water's edge after the scene starts; kept simple.
HoennSeek_EventScript_PondSwampert::
	lock
	playmoncry SPECIES_SWAMPERT, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_PondSwampertTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_PondMudkip::
	lock
	playmoncry SPECIES_MUDKIP, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_PondMudkipTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ The Gardevoir and its Ralts stand on the open patch beside the tall grass
@ near Petalburg (where Wally caught his Ralts in Emerald; in the grass itself
@ they were hard to see), mornings, until the Ralts has joined you. Rush
@ in and they're gone until tomorrow. Trigger tiles: every open tile two steps
@ from them, so you can't get closer without crossing one.
HoennSeek_EventScript_RaltsSetup:
	goto_if_set FLAG_HOENN_RALTS_DONE, HoennSeek_EventScript_SpeciesReturn
	goto_if_set FLAG_HOENN_DAILY_RALTS_GONE, HoennSeek_EventScript_SpeciesReturn
	clearflag FLAG_HOENN_HIDE_RALTS
	goto_if_set FLAG_HOENN_DAILY_RALTS, HoennSeek_EventScript_SpeciesReturn
	setvar VAR_TEMP_1, 1
	return

HoennSeek_EventScript_RaltsApproach::
	@ Before lockall: locking stops the player, which clears the running flag.
	specialvar VAR_RESULT, HoennPlayerIsRushing
	lockall
	setvar VAR_TEMP_1, 0
	goto_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_RaltsTeleport
	goto_if_ge VAR_HOENN_RALTS_MORNINGS, 3, HoennSeek_EventScript_RaltsComes
	applymovement LOCALID_HOENN_GARDEVOIR, HoennSeek_Movement_FacePlayer
	waitmovement 0
	playmoncry SPECIES_GARDEVOIR, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_GardevoirReads, MSGBOX_DEFAULT
	waitmoncry
	@ It reads your lead: only a Pokémon that loves you with all its heart will do.
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	goto_if_ne VAR_RESULT, FRIENDSHIP_MAX, HoennSeek_EventScript_RaltsNotYet
	setflag FLAG_HOENN_DAILY_RALTS
	addvar VAR_HOENN_RALTS_MORNINGS, 1
	goto_if_ge VAR_HOENN_RALTS_MORNINGS, 3, HoennSeek_EventScript_RaltsComes
	bufferleadmonspeciesname STR_VAR_1
	applymovement LOCALID_HOENN_RALTS, HoennSeek_Movement_FacePlayer
	waitmovement 0
	playmoncry SPECIES_RALTS, CRY_MODE_NORMAL
	call_if_eq VAR_HOENN_RALTS_MORNINGS, 1, HoennSeek_EventScript_RaltsMorning1
	call_if_eq VAR_HOENN_RALTS_MORNINGS, 2, HoennSeek_EventScript_RaltsMorning2
	waitmoncry
	releaseall
	end
HoennSeek_EventScript_RaltsMorning1:
	msgbox HoennSeek_Text_RaltsMorning1, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_RaltsMorning2:
	applymovement LOCALID_HOENN_RALTS, HoennSeek_Movement_RaltsPeek
	waitmovement 0
	msgbox HoennSeek_Text_RaltsMorning2, MSGBOX_DEFAULT
	return

HoennSeek_EventScript_RaltsNotYet:
	msgbox HoennSeek_Text_RaltsNotYet, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_RaltsTeleport:
	setflag FLAG_HOENN_DAILY_RALTS
	setflag FLAG_HOENN_DAILY_RALTS_GONE
	playse SE_PIN
	applymovement LOCALID_HOENN_GARDEVOIR, Common_Movement_ExclamationMark
	waitmovement 0
	playmoncry SPECIES_GARDEVOIR, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_GardevoirStartled, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	playse SE_M_TELEPORT
	applymovement LOCALID_HOENN_GARDEVOIR, HoennSeek_Movement_Spin
	applymovement LOCALID_HOENN_RALTS, HoennSeek_Movement_Spin
	waitmovement 0
	removeobject LOCALID_HOENN_RALTS
	removeobject LOCALID_HOENN_GARDEVOIR
	delay 30
	msgbox HoennSeek_Text_RaltsGone, MSGBOX_DEFAULT
	releaseall
	end

@ Third morning (or any later visit, if there was no room for it then).
HoennSeek_EventScript_RaltsComes:
	applymovement LOCALID_HOENN_RALTS, HoennSeek_Movement_FacePlayer
	waitmovement 0
	playmoncry SPECIES_RALTS, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_RaltsComes, MSGBOX_DEFAULT
	waitmoncry
HoennSeek_EventScript_RaltsJoin:
	bufferspeciesname STR_VAR_1, SPECIES_RALTS
	@ The only Ralts in the game, with its hidden ability, Telepathy.
	givemon SPECIES_RALTS, 5, abilityNum=2
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, HoennSeek_EventScript_RaltsNoRoom
	setflag FLAG_HOENN_RALTS_DONE
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_RALTS
	copyvar VAR_0x8005, VAR_RESULT
	playse SE_M_TELEPORT
	applymovement LOCALID_HOENN_RALTS, HoennSeek_Movement_Spin
	waitmovement 0
	removeobject LOCALID_HOENN_RALTS
	msgbox HoennSeek_Text_RaltsTeleportsToYou, MSGBOX_DEFAULT
	copyvar VAR_RESULT, VAR_0x8005
	call Common_EventScript_GiftMon
	@ Its guardian is at peace now.
	applymovement LOCALID_HOENN_GARDEVOIR, HoennSeek_Movement_FacePlayer
	waitmovement 0
	playmoncry SPECIES_GARDEVOIR, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_GardevoirFarewell, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	playse SE_M_TELEPORT
	applymovement LOCALID_HOENN_GARDEVOIR, HoennSeek_Movement_Spin
	waitmovement 0
	removeobject LOCALID_HOENN_GARDEVOIR
	releaseall
	end

HoennSeek_EventScript_RaltsNoRoom:
	msgbox HoennSeek_Text_RaltsNoRoom, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_Gardevoir::
	lock
	playmoncry SPECIES_GARDEVOIR, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_GardevoirTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_Ralts::
	lockall
	goto_if_ge VAR_HOENN_RALTS_MORNINGS, 3, HoennSeek_EventScript_RaltsJoin
	playmoncry SPECIES_RALTS, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_RaltsTalk, MSGBOX_DEFAULT
	waitmoncry
	releaseall
	end

@ ==========================================================================
@ Mt. Mortar B1F, mornings: Kiyo spars with a wild Machamp. Hook: one `call`
@ in MtMortar_B1F_OnTransition. Trigger tiles: row 11, x 37-39, the only way
@ into the pocket where Kiyo trains.
@ ==========================================================================

HoennSeek_EventScript_MtMortarOnTransition::
	setflag FLAG_HOENN_HIDE_KIYO_MACHAMP
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_MORNING, HoennSeek_EventScript_SpeciesReturn
	goto_if_set FLAG_HOENN_DAILY_KIYO_MATCH, HoennSeek_EventScript_SpeciesReturn
	clearflag FLAG_HOENN_HIDE_KIYO_MACHAMP
	setvar VAR_TEMP_5, 1
	return

HoennSeek_EventScript_KiyoMatch::
	lockall
	setvar VAR_TEMP_5, 0
	setflag FLAG_HOENN_DAILY_KIYO_MATCH
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
	applymovement LOCALID_HOENN_KIYO, Common_Movement_FaceDown
	waitmovement 0
	msgbox HoennSeek_Text_KiyoSpar, MSGBOX_DEFAULT
	closemessage
	@ Round 1: Kiyo lunges.
	applymovement LOCALID_HOENN_KIYO, HoennSeek_Movement_LungeDown
	waitmovement 0
	playse SE_M_COMET_PUNCH
	applymovement LOCALID_HOENN_KIYO_MACHAMP, HoennSeek_Movement_JumpUp
	waitmovement 0
	applymovement LOCALID_HOENN_KIYO, HoennSeek_Movement_BackUp
	waitmovement 0
	@ Round 2: the Machamp answers.
	playmoncry SPECIES_MACHAMP, CRY_MODE_NORMAL
	applymovement LOCALID_HOENN_KIYO_MACHAMP, HoennSeek_Movement_LungeUp
	waitmovement 0
	playse SE_M_MEGA_KICK
	applymovement LOCALID_HOENN_KIYO, HoennSeek_Movement_JumpDown
	waitmovement 0
	applymovement LOCALID_HOENN_KIYO_MACHAMP, HoennSeek_Movement_BackDown
	waitmovement 0
	waitmoncry
	@ Round 3: both at once.
	applymovement LOCALID_HOENN_KIYO, HoennSeek_Movement_LungeDown
	applymovement LOCALID_HOENN_KIYO_MACHAMP, HoennSeek_Movement_LungeUpHalf
	waitmovement 0
	playse SE_M_VITAL_THROW
	applymovement LOCALID_HOENN_KIYO, HoennSeek_Movement_JumpDown
	applymovement LOCALID_HOENN_KIYO_MACHAMP, HoennSeek_Movement_JumpUp
	waitmovement 0
	msgbox HoennSeek_Text_KiyoClash, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HOENN_KIYO, HoennSeek_Movement_BackUp
	waitmovement 0
	@ A bow, and the Machamp heads back up the mountain.
	playmoncry SPECIES_MACHAMP, CRY_MODE_NORMAL
	applymovement LOCALID_HOENN_KIYO_MACHAMP, HoennSeek_Movement_Bow
	applymovement LOCALID_HOENN_KIYO, HoennSeek_Movement_Bow
	waitmovement 0
	waitmoncry
	applymovement LOCALID_HOENN_KIYO_MACHAMP, HoennSeek_Movement_MachampLeaves
	waitmovement 0
	removeobject LOCALID_HOENN_KIYO_MACHAMP
	applymovement LOCALID_HOENN_KIYO, HoennSeek_Movement_FacePlayer
	waitmovement 0
	goto_if_set FLAG_HOENN_KIYO_BLACK_BELT, HoennSeek_EventScript_KiyoMatchAgain
	msgbox HoennSeek_Text_KiyoWatched, MSGBOX_DEFAULT
	giveitem ITEM_BLACK_BELT
	goto_if_eq VAR_RESULT, FALSE, HoennSeek_EventScript_KiyoBagFull
	setflag FLAG_HOENN_KIYO_BLACK_BELT
	msgbox HoennSeek_Text_KiyoBelt, MSGBOX_DEFAULT
	releaseall
	end
HoennSeek_EventScript_KiyoBagFull:
	msgbox HoennSeek_Text_KiyoBagFull, MSGBOX_DEFAULT
	releaseall
	end
HoennSeek_EventScript_KiyoMatchAgain:
	msgbox HoennSeek_Text_KiyoAgain, MSGBOX_DEFAULT
	releaseall
	end

HoennSeek_EventScript_KiyoMachamp::
	lock
	playmoncry SPECIES_MACHAMP, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_KiyoMachampTalk, MSGBOX_DEFAULT
	waitmoncry
	release
	end

@ ==========================================================================
@ National Park, Tuesday/Thursday/Saturday evenings: the Scyther behind the
@ trees in the north-east corner (HnS's two overworld Scyther, a patch you
@ can't walk into) duel, and a Scizor ends it. Hook: one `call` in
@ NationalPark_Normal_OnTransition. Trigger tiles: row 2, x 26-29, the strip
@ at the top of the park (past the cut tree, or up from x 29) that looks across at the patch.
@ ==========================================================================

HoennSeek_EventScript_NationalParkOnTransition::
	setflag FLAG_HOENN_HIDE_SCIZOR
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_EVENING, HoennSeek_EventScript_SpeciesReturn
	goto_if_set FLAG_HOENN_DAILY_SCIZOR, HoennSeek_EventScript_SpeciesReturn
	specialvar VAR_RESULT, GetDayOfWeek
	goto_if_eq VAR_RESULT, HOENN_TUESDAY, HoennSeek_EventScript_ParkArm
	goto_if_eq VAR_RESULT, HOENN_THURSDAY, HoennSeek_EventScript_ParkArm
	goto_if_eq VAR_RESULT, HOENN_SATURDAY, HoennSeek_EventScript_ParkArm
	return
HoennSeek_EventScript_ParkArm:
	setvar VAR_TEMP_5, 1
	return

HoennSeek_EventScript_ParkDuel::
	lockall
	setvar VAR_TEMP_5, 0
	setflag FLAG_HOENN_DAILY_SCIZOR
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
	waitmovement 0
	msgbox HoennSeek_Text_ParkRustle, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8008, 37
	setvar VAR_0x8009, 3
	call HoennSeek_EventScript_StarterPanTo
	@ The duel: they close in and trade blows (their wandering is reset first).
	setobjectxy LOCALID_HOENN_PARK_SCYTHER_1, 36, 3
	setobjectxy LOCALID_HOENN_PARK_SCYTHER_2, 41, 3
	applymovement LOCALID_HOENN_PARK_SCYTHER_1, HoennSeek_Movement_ScytherInRight
	applymovement LOCALID_HOENN_PARK_SCYTHER_2, HoennSeek_Movement_ScytherInLeft
	waitmovement 0
	playmoncry SPECIES_SCYTHER, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_ParkDuel, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	playse SE_M_CUT
	applymovement LOCALID_HOENN_PARK_SCYTHER_1, HoennSeek_Movement_JumpRight
	applymovement LOCALID_HOENN_PARK_SCYTHER_2, HoennSeek_Movement_JumpLeft
	waitmovement 0
	playse SE_M_CUT
	applymovement LOCALID_HOENN_PARK_SCYTHER_2, HoennSeek_Movement_JumpLeft
	applymovement LOCALID_HOENN_PARK_SCYTHER_1, HoennSeek_Movement_JumpRight
	waitmovement 0
	@ The Scizor drops in between them.
	clearflag FLAG_HOENN_HIDE_SCIZOR
	addobject LOCALID_HOENN_PARK_SCIZOR
	playse SE_M_RAZOR_WIND
	applymovement LOCALID_HOENN_PARK_SCIZOR, HoennSeek_Movement_ScizorIn
	waitmovement 0
	playmoncry SPECIES_SCIZOR, CRY_MODE_NORMAL
	applymovement LOCALID_HOENN_PARK_SCIZOR, HoennSeek_Movement_ScizorStrike
	waitmovement 0
	playse SE_M_SWORDS_DANCE
	applymovement LOCALID_HOENN_PARK_SCYTHER_1, HoennSeek_Movement_JumpUpInPlace
	applymovement LOCALID_HOENN_PARK_SCYTHER_2, HoennSeek_Movement_JumpUpInPlace
	waitmovement 0
	waitmoncry
	applymovement LOCALID_HOENN_PARK_SCYTHER_1, HoennSeek_Movement_ScytherFleeLeft
	applymovement LOCALID_HOENN_PARK_SCYTHER_2, HoennSeek_Movement_ScytherFleeRight
	waitmovement 0
	removeobject LOCALID_HOENN_PARK_SCYTHER_1
	removeobject LOCALID_HOENN_PARK_SCYTHER_2
	msgbox HoennSeek_Text_ParkScizor, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HOENN_PARK_SCIZOR, Common_Movement_FaceLeft
	waitmovement 0
	goto_if_set FLAG_HOENN_SCIZOR_QUICK_CLAW, HoennSeek_EventScript_ParkScizorLeaves
	@ Once: it flicks a Quick Claw over the trees to you.
	playse SE_M_RAZOR_WIND
	applymovement LOCALID_HOENN_PARK_SCIZOR, HoennSeek_Movement_JumpLeftInPlace
	waitmovement 0
	msgbox HoennSeek_Text_ParkFlick, MSGBOX_DEFAULT
	giveitem ITEM_QUICK_CLAW
	call_if_eq VAR_RESULT, TRUE, HoennSeek_EventScript_ParkGotClaw
HoennSeek_EventScript_ParkScizorLeaves:
	applymovement LOCALID_HOENN_PARK_SCIZOR, HoennSeek_Movement_ScizorLeaves
	waitmovement 0
	removeobject LOCALID_HOENN_PARK_SCIZOR
	call HoennSeek_EventScript_StarterPanBack
	releaseall
	end
HoennSeek_EventScript_ParkGotClaw:
	setflag FLAG_HOENN_SCIZOR_QUICK_CLAW
	return

HoennSeek_EventScript_ParkScizor::
	lock
	playmoncry SPECIES_SCIZOR, CRY_MODE_NORMAL
	waitmoncry
	release
	end

@ ==========================================================================
@ PokéGear event calls (src/hoenn_species.c says who heard what from whom).
@ HoennSeek_EventScript_PhoneEvent's switch jumps here for part 18's IDs.
@ ==========================================================================

HoennSeek_EventScript_CallPond::
	setflag FLAG_HOENN_CALL_POND
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallPond
	goto HoennSeek_EventScript_CallEnd

HoennSeek_EventScript_CallRalts::
	setflag FLAG_HOENN_CALL_RALTS
	setspeaker HoennSeek_Text_NameWally
	pokenavcall HoennSeek_Text_CallRalts
	goto HoennSeek_EventScript_CallEnd

HoennSeek_EventScript_CallKiyo::
	setflag FLAG_HOENN_CALL_KIYO
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallKiyo
	goto HoennSeek_EventScript_CallEnd

HoennSeek_EventScript_CallScizor::
	setflag FLAG_HOENN_CALL_SCIZOR
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallScizor
	goto HoennSeek_EventScript_CallEnd

@ ==========================================================================
@ Movements
@ ==========================================================================

HoennSeek_Movement_FacePlayer:
	face_player
	step_end

HoennSeek_Movement_PondHop:
	jump_in_place_down
	step_end

HoennSeek_Movement_PondSwampertIn:
	walk_up
	walk_in_place_up
	step_end

HoennSeek_Movement_PondMudkip1In:
	walk_right
	walk_in_place_down
	step_end

HoennSeek_Movement_PondMudkip2In:
	walk_down
	walk_in_place_left
	step_end

HoennSeek_Movement_RaltsPeek:
	walk_in_place_fast_left
	walk_in_place_fast_right
	step_end

HoennSeek_Movement_Spin:
	face_down
	face_left
	face_up
	face_right
	face_down
	face_left
	face_up
	face_right
	set_invisible
	step_end

HoennSeek_Movement_LungeDown:
	walk_fast_down
	step_end

HoennSeek_Movement_LungeUp:
	walk_fast_up
	step_end

HoennSeek_Movement_LungeUpHalf:
	walk_in_place_fast_up
	step_end

HoennSeek_Movement_BackUp:
	lock_facing_direction
	walk_up
	unlock_facing_direction
	step_end

HoennSeek_Movement_BackDown:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

HoennSeek_Movement_JumpUp:
	jump_in_place_up
	step_end

HoennSeek_Movement_JumpDown:
	jump_in_place_down
	step_end

HoennSeek_Movement_Bow:
	delay_16
	walk_in_place_slow_down
	delay_16
	step_end

HoennSeek_Movement_MachampLeaves:
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

HoennSeek_Movement_ScytherInRight:
	walk_fast_right
	walk_in_place_fast_right
	step_end

HoennSeek_Movement_ScytherInLeft:
	walk_fast_left
	walk_in_place_fast_left
	step_end

HoennSeek_Movement_JumpRight:
	jump_in_place_right
	step_end

HoennSeek_Movement_JumpLeft:
	jump_in_place_left
	step_end

HoennSeek_Movement_JumpUpInPlace:
	jump_in_place_up
	step_end

HoennSeek_Movement_JumpLeftInPlace:
	jump_in_place_left
	step_end

HoennSeek_Movement_ScizorIn:
	walk_faster_down
	step_end

HoennSeek_Movement_ScizorStrike:
	walk_in_place_faster_left
	walk_in_place_faster_right
	walk_in_place_faster_left
	walk_in_place_faster_down
	step_end

HoennSeek_Movement_ScytherFleeLeft:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

HoennSeek_Movement_ScytherFleeRight:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

HoennSeek_Movement_ScizorLeaves:
	walk_up
	walk_up
	walk_up
	step_end

@ ==========================================================================
@ Texts
@ ==========================================================================

HoennSeek_Text_PondPractice:
	.string "A SWAMPERT is watching two MUDKIP\n"
	.string "practice in the pond.$"

HoennSeek_Text_PondFin:
	.string "SWAMPERT's fin twitches.\p"
	.string "It looks up at the sky and calls\n"
	.string "to the MUDKIP.$"

HoennSeek_Text_PondRain:
	.string "Rain!\p"
	.string "SWAMPERT felt the shower coming\n"
	.string "before a single cloud showed.$"

HoennSeek_Text_PondSwampertTalk:
	.string "SWAMPERT keeps one eye on the sky\n"
	.string "and one on its MUDKIP.$"

HoennSeek_Text_PondMudkipTalk:
	.string "MUDKIP spits a jet of water and\n"
	.string "looks back at SWAMPERT, proudly.$"

HoennSeek_Text_GardevoirReads:
	.string "GARDEVOIR steps in front of the\n"
	.string "RALTS. Its eyes glow softly.\p"
	.string "It's reading your\n"
	.string "POKéMON's feelings…$"

HoennSeek_Text_RaltsMorning1:
	.string "From behind GARDEVOIR, the RALTS\n"
	.string "peeks out at you.\p"
	.string "It felt how much your\n"
	.string "{STR_VAR_1} loves you.$"

HoennSeek_Text_RaltsMorning2:
	.string "The RALTS takes a step toward you,\n"
	.string "then hurries back.\p"
	.string "GARDEVOIR doesn't stop it this\n"
	.string "time. It almost seems to smile.$"

HoennSeek_Text_RaltsNotYet:
	.string "GARDEVOIR draws the RALTS close and\n"
	.string "shakes its head.\p"
	.string "It seems to be looking for a\n"
	.string "POKéMON that loves its TRAINER\l"
	.string "with all its heart.$"

HoennSeek_Text_GardevoirStartled:
	.string "GARDEVOIR felt you rushing in!$"

HoennSeek_Text_RaltsGone:
	.string "GARDEVOIR teleported away, and\n"
	.string "the RALTS with it.\p"
	.string "Maybe a slower, gentler approach\n"
	.string "would help…$"

HoennSeek_Text_RaltsComes:
	.string "The RALTS's horn glows. It slips\n"
	.string "past GARDEVOIR and looks up at you.\p"
	.string "It wants to come with you!$"

HoennSeek_Text_RaltsTeleportsToYou:
	.string "The RALTS teleported right into\n"
	.string "your arms!$"

HoennSeek_Text_GardevoirFarewell:
	.string "GARDEVOIR bows to you, then looks\n"
	.string "at the RALTS one last time.$"

HoennSeek_Text_RaltsNoRoom:
	.string "The RALTS wants to come with you,\n"
	.string "but you have no room for it.\p"
	.string "GARDEVOIR will keep it safe until\n"
	.string "you come back.$"

HoennSeek_Text_GardevoirTalk:
	.string "GARDEVOIR watches you calmly.$"

HoennSeek_Text_RaltsTalk:
	.string "The RALTS hides behind GARDEVOIR,\n"
	.string "but it doesn't look scared.$"

HoennSeek_Text_KiyoSpar:
	.string "KIYO: Hwaaah!\p"
	.string "The KARATE KING is sparring with a\n"
	.string "wild MACHAMP!$"

HoennSeek_Text_KiyoClash:
	.string "Their fists meet in the middle!$"

HoennSeek_Text_KiyoWatched:
	.string "KIYO: …Hah! You watched the whole\n"
	.string "match without making a sound!\p"
	.string "That MACHAMP comes down from the\n"
	.string "peak every morning. It's never\l"
	.string "once let me win.\p"
	.string "A TRAINER who can watch quietly\n"
	.string "can learn. Take this!$"

HoennSeek_Text_KiyoBelt:
	.string "KIYO: A BLACK BELT powers up\n"
	.string "FIGHTING moves.\p"
	.string "Train hard, and come watch again\n"
	.string "some morning!$"

HoennSeek_Text_KiyoBagFull:
	.string "KIYO: Your BAG is full! Come watch\n"
	.string "another morning, then.$"

HoennSeek_Text_KiyoAgain:
	.string "KIYO: Another draw! One of these\n"
	.string "mornings, MACHAMP will bow first.$"

HoennSeek_Text_KiyoMachampTalk:
	.string "MACHAMP's eyes never leave KIYO.$"

HoennSeek_Text_ParkRustle:
	.string "Something is moving\n"
	.string "behind the trees…$"

HoennSeek_Text_ParkDuel:
	.string "Two SCYTHER are dueling\n"
	.string "in the grass!$"

HoennSeek_Text_ParkScizor:
	.string "A SCIZOR swooped in and beat\n"
	.string "them both in a flash!$"

HoennSeek_Text_ParkFlick:
	.string "SCIZOR flicked something\n"
	.string "over the trees!$"

HoennSeek_Text_NameWally:
	.string "WALLY$"

HoennSeek_Text_CallPond:
	.string "Hey, {PLAYER}! It's BRENDAN.\p"
	.string "One of Dad's aides counts the\n"
	.string "POKéMON on ROUTE 102 every\l"
	.string "morning. He saw you at the pond!\p"
	.string "The SWAMPERT family dove right\n"
	.string "before it rained, right?\p"
	.string "Dad's been trying to see that\n"
	.string "for years. He's so jealous!$"

HoennSeek_Text_CallRalts:
	.string "{PLAYER}? It's WALLY!\p"
	.string "My GARDEVOIR woke me up this\n"
	.string "morning, all happy and glowing.\p"
	.string "It came from the GARDEVOIR family\n"
	.string "on ROUTE 102, you know.\p"
	.string "I think it felt that little\n"
	.string "RALTS choose you!\p"
	.string "Take good care of that RALTS.\n"
	.string "It already trusts you a lot.$"

HoennSeek_Text_CallKiyo:
	.string "{PLAYER}, it's BRENDAN!\p"
	.string "I called CHUCK in CIANWOOD for\n"
	.string "training tips.\p"
	.string "He got a letter from KIYO, the\n"
	.string "KARATE KING, all about you!\p"
	.string "You watched his whole match with\n"
	.string "a wild MACHAMP? I'd never manage\l"
	.string "to keep quiet that long.$"

HoennSeek_Text_CallScizor:
	.string "Hi, {PLAYER}! It's MAY.\p"
	.string "BUGSY was on the radio talking\n"
	.string "about the NATIONAL PARK.\p"
	.string "He said a TRAINER saw the SCIZOR\n"
	.string "that breaks up the SCYTHER duels!\p"
	.string "That was you, wasn't it? It was,\n"
	.string "I just know it!$"

@ ==========================================================================
@ Part 19: the Gengar shadow chase (Lavender Town, nights). Every stage only
@ happens at night, in order (VAR_HOENN_GENGAR_STATE 0-4). Hooks: one `call` in
@ Lavender's and Route 8's OnTransition, and map scripts added to the Underground
@ Path entrance and the Radio Tower (both had none). The stages that play on
@ arrival use ON_FRAME entries on VAR_TEMP_4, which the OnTransition arms.
@ ==========================================================================

@ Arms VAR_TEMP_4 when it's night and the chase is at stage VAR_0x8004.
HoennSeek_EventScript_GengarArm:
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, HoennSeek_EventScript_SpeciesReturn
	goto_if_ne VAR_HOENN_GENGAR_STATE, VAR_0x8004, HoennSeek_EventScript_SpeciesReturn
	setvar VAR_TEMP_4, 1
	return

HoennSeek_EventScript_LavenderOnTransition::
	setvar VAR_0x8004, 0
	goto HoennSeek_EventScript_GengarArm

HoennSeek_LavenderOnFrame::
	map_script_2 VAR_TEMP_4, 1, HoennSeek_EventScript_GengarLavender
	.2byte 0

@ Stage 0 -> 1: your shadow grins.
HoennSeek_EventScript_GengarLavender::
	lockall
	setvar VAR_TEMP_4, 0
	setvar VAR_HOENN_GENGAR_STATE, 1
	delay 30
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_QuestionMark
	waitmovement 0
	msgbox HoennSeek_Text_GengarGrin, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_GENGAR, CRY_MODE_NORMAL
	applymovement OBJ_EVENT_ID_PLAYER, HoennSeek_Movement_ShadowTwitch
	waitmovement 0
	waitmoncry
	msgbox HoennSeek_Text_GengarPointsRoute8, MSGBOX_DEFAULT
	releaseall
	end

@ Stage 1 -> 2: Route 8, the column of tiles east of the tunnel building
@ (x 14, rows 20-23): every way to the Underground Path crosses it.
HoennSeek_EventScript_Route8OnTransition::
	setvar VAR_0x8004, 1
	goto HoennSeek_EventScript_GengarArm

HoennSeek_EventScript_GengarRoute8::
	lockall
	setvar VAR_TEMP_4, 0
	setvar VAR_HOENN_GENGAR_STATE, 2
	msgbox HoennSeek_Text_GengarStops, MSGBOX_DEFAULT
	closemessage
	playmoncry SPECIES_GENGAR, CRY_MODE_NORMAL
	applymovement OBJ_EVENT_ID_PLAYER, HoennSeek_Movement_ShadowTwitch
	waitmovement 0
	waitmoncry
	@ The prank: a cheap item in your BAG "turns into" a joke note, for a moment.
	playse SE_RG_BAG_POCKET
	msgbox HoennSeek_Text_GengarBagJoke, MSGBOX_DEFAULT
	msgbox HoennSeek_Text_GengarPointsTunnel, MSGBOX_DEFAULT
	releaseall
	end

@ Stage 2 -> 3: the Underground Path entrance, on arrival.
@ (The map's own table, Route8_TunnelEntrance_hns_MapScripts, points here.)
HoennSeek_EventScript_TunnelOnTransition::
	setvar VAR_0x8004, 2
	call HoennSeek_EventScript_GengarArm
	end

HoennSeek_TunnelOnFrame::
	map_script_2 VAR_TEMP_4, 1, HoennSeek_EventScript_GengarTunnel
	.2byte 0

HoennSeek_EventScript_GengarTunnel::
	lockall
	setvar VAR_TEMP_4, 0
	setvar VAR_HOENN_GENGAR_STATE, 3
	delay 20
	playmoncry SPECIES_GENGAR, CRY_MODE_ENCOUNTER
	msgbox HoennSeek_Text_GengarEcho, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, HoennSeek_Movement_ShadowTwitch
	waitmovement 0
	msgbox HoennSeek_Text_GengarPointsTower, MSGBOX_DEFAULT
	releaseall
	end

@ Stage 3 -> 4: Lavender's Radio Tower, by the memorial in the corner where
@ the old POKéMON TOWER stood. The Gengar jumps out and joins you (Lv 50, the
@ level of Route 8's night Haunter, knowing Spectral Thief).
@ (The map's own table, LavenderTown_RadioStation_hns_MapScripts, points here.)
HoennSeek_EventScript_RadioTowerOnTransition::
	setflag FLAG_HOENN_HIDE_GENGAR
	setvar VAR_0x8004, 3
	call HoennSeek_EventScript_GengarArm
	end

HoennSeek_RadioTowerOnFrame::
	map_script_2 VAR_TEMP_4, 1, HoennSeek_EventScript_GengarTower
	.2byte 0

HoennSeek_EventScript_GengarTower::
	lockall
	setvar VAR_TEMP_4, 0
	delay 20
	msgbox HoennSeek_Text_GengarMemorial, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, HoennSeek_Movement_ShadowTwitch
	waitmovement 0
	clearflag FLAG_HOENN_HIDE_GENGAR
	addobject LOCALID_HOENN_GENGAR
	playse SE_M_NIGHTMARE
	applymovement LOCALID_HOENN_GENGAR, HoennSeek_Movement_GengarPops
	waitmovement 0
	playmoncry SPECIES_GENGAR, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_GengarJumpsOut, MSGBOX_DEFAULT
	waitmoncry
HoennSeek_EventScript_GengarJoin:
	bufferspeciesname STR_VAR_1, SPECIES_GENGAR
	givemon SPECIES_GENGAR, 50, move1=MOVE_SPECTRAL_THIEF, move2=MOVE_SHADOW_BALL, move3=MOVE_SLUDGE_BOMB, move4=MOVE_HYPNOSIS
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, HoennSeek_EventScript_GengarNoRoom
	setvar VAR_HOENN_GENGAR_STATE, 4
	setflag FLAG_HOENN_GENGAR_DONE
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_GENGAR
	call Common_EventScript_GiftMon
	removeobject LOCALID_HOENN_GENGAR
	msgbox HoennSeek_Text_GengarJoined, MSGBOX_DEFAULT
	releaseall
	end

@ No room: it slips back into your shadow and tries again next time you come in at night.
HoennSeek_EventScript_GengarNoRoom:
	msgbox HoennSeek_Text_GengarNoRoom, MSGBOX_DEFAULT
	closemessage
	removeobject LOCALID_HOENN_GENGAR
	releaseall
	end

HoennSeek_EventScript_Gengar::
	lockall
	goto HoennSeek_EventScript_GengarJoin

@ ==========================================================================
@ Part 19: the Slowking sage (Slowpoke Well B2F). HnS's Slowking gives TM Rain
@ Dance first (its own script, unchanged); after that its object runs this.
@ One riddle per weekday; each one solved (once) teaches the next line of the
@ prophecy. One answer a day. The prophecy is the Lugia chain's clue (parts
@ 34+): three birds, their feathers and the Silver Wing, the Whirl Islands at
@ night, and the lights under the sea that lead to the shrine.
@ ==========================================================================

HoennSeek_EventScript_SlowkingSage::
	goto_if_unset FLAG_ITEM_SLOWPOKE_WELL_RAIN_DANCE, SlowpokeWell_EventScript_Slowking
	lock
	faceplayer
	playmoncry SPECIES_SLOWKING, CRY_MODE_NORMAL
	waitmoncry
	goto_if_set FLAG_HOENN_SLOWKING_PROPHECY, HoennSeek_EventScript_SageDone
	call_if_eq VAR_HOENN_SLOWKING_LINES, 0, HoennSeek_EventScript_SageIntro
	goto_if_set FLAG_HOENN_DAILY_SLOWKING, HoennSeek_EventScript_SageTomorrow
	specialvar VAR_RESULT, GetDayOfWeek
	switch VAR_RESULT
	case HOENN_SUNDAY, HoennSeek_EventScript_RiddleSun
	case HOENN_MONDAY, HoennSeek_EventScript_RiddleMon
	case HOENN_TUESDAY, HoennSeek_EventScript_RiddleTue
	case HOENN_WEDNESDAY, HoennSeek_EventScript_RiddleWed
	case HOENN_THURSDAY, HoennSeek_EventScript_RiddleThu
	case HOENN_FRIDAY, HoennSeek_EventScript_RiddleFri
	case HOENN_SATURDAY, HoennSeek_EventScript_RiddleSat
	release
	end

HoennSeek_EventScript_SageIntro:
	msgbox HoennSeek_Text_SageIntro, MSGBOX_DEFAULT
	return

@ Already answered today (right or wrong), or today's riddle is solved.
HoennSeek_EventScript_SageTomorrow:
	msgbox HoennSeek_Text_SageTomorrow, MSGBOX_DEFAULT
	goto HoennSeek_EventScript_SageOfferRecite
HoennSeek_EventScript_SageSolvedToday:
	msgbox HoennSeek_Text_SageSolvedToday, MSGBOX_DEFAULT
HoennSeek_EventScript_SageOfferRecite:
	goto_if_eq VAR_HOENN_SLOWKING_LINES, 0, HoennSeek_EventScript_SageRelease
	msgbox HoennSeek_Text_SageHearAgain, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_SageRelease
	call HoennSeek_EventScript_SageRecite
HoennSeek_EventScript_SageRelease:
	release
	end

HoennSeek_EventScript_SageDone:
	msgbox HoennSeek_Text_SageDone, MSGBOX_DEFAULT
	msgbox HoennSeek_Text_SageHearAgain, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, HoennSeek_EventScript_SageRelease
	call HoennSeek_EventScript_SageRecite
	release
	end

HoennSeek_EventScript_SageRecite:
	call_if_ge VAR_HOENN_SLOWKING_LINES, 1, HoennSeek_EventScript_SageLine1
	call_if_ge VAR_HOENN_SLOWKING_LINES, 2, HoennSeek_EventScript_SageLine2
	call_if_ge VAR_HOENN_SLOWKING_LINES, 3, HoennSeek_EventScript_SageLine3
	call_if_ge VAR_HOENN_SLOWKING_LINES, 4, HoennSeek_EventScript_SageLine4
	call_if_ge VAR_HOENN_SLOWKING_LINES, 5, HoennSeek_EventScript_SageLine5
	call_if_ge VAR_HOENN_SLOWKING_LINES, 6, HoennSeek_EventScript_SageLine6
	call_if_ge VAR_HOENN_SLOWKING_LINES, 7, HoennSeek_EventScript_SageLine7
	return
HoennSeek_EventScript_SageLine1:
	msgbox HoennSeek_Text_Prophecy1, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_SageLine2:
	msgbox HoennSeek_Text_Prophecy2, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_SageLine3:
	msgbox HoennSeek_Text_Prophecy3, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_SageLine4:
	msgbox HoennSeek_Text_Prophecy4, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_SageLine5:
	msgbox HoennSeek_Text_Prophecy5, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_SageLine6:
	msgbox HoennSeek_Text_Prophecy6, MSGBOX_DEFAULT
	return
HoennSeek_EventScript_SageLine7:
	msgbox HoennSeek_Text_Prophecy7, MSGBOX_DEFAULT
	return

@ Each riddle: skip it if solved, ask, then three answers. VAR_0x8005 is the
@ right answer's index; B leaves without using up the day's answer.
HoennSeek_EventScript_RiddleSun:
	goto_if_set FLAG_HOENN_SLOWKING_RIDDLE_SUN, HoennSeek_EventScript_SageSolvedToday
	msgbox HoennSeek_Text_RiddleSun, MSGBOX_DEFAULT
	dynmultichoice 18, 4, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, HoennSeek_Text_AnsFog, HoennSeek_Text_AnsDarkness, HoennSeek_Text_AnsSmoke
	setvar VAR_0x8005, 1
	call HoennSeek_EventScript_RiddleCheck
	setflag FLAG_HOENN_SLOWKING_RIDDLE_SUN
	goto HoennSeek_EventScript_RiddleSolved
HoennSeek_EventScript_RiddleMon:
	goto_if_set FLAG_HOENN_SLOWKING_RIDDLE_SUN + HOENN_MONDAY, HoennSeek_EventScript_SageSolvedToday
	msgbox HoennSeek_Text_RiddleMon, MSGBOX_DEFAULT
	dynmultichoice 18, 4, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, HoennSeek_Text_AnsCoin, HoennSeek_Text_AnsKite, HoennSeek_Text_AnsSnake
	setvar VAR_0x8005, 0
	call HoennSeek_EventScript_RiddleCheck
	setflag FLAG_HOENN_SLOWKING_RIDDLE_SUN + HOENN_MONDAY
	goto HoennSeek_EventScript_RiddleSolved
HoennSeek_EventScript_RiddleTue:
	goto_if_set FLAG_HOENN_SLOWKING_RIDDLE_SUN + HOENN_TUESDAY, HoennSeek_EventScript_SageSolvedToday
	msgbox HoennSeek_Text_RiddleTue, MSGBOX_DEFAULT
	dynmultichoice 18, 4, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, HoennSeek_Text_AnsWind, HoennSeek_Text_AnsBird, HoennSeek_Text_AnsCloud
	setvar VAR_0x8005, 2
	call HoennSeek_EventScript_RiddleCheck
	setflag FLAG_HOENN_SLOWKING_RIDDLE_SUN + HOENN_TUESDAY
	goto HoennSeek_EventScript_RiddleSolved
HoennSeek_EventScript_RiddleWed:
	goto_if_set FLAG_HOENN_SLOWKING_RIDDLE_SUN + HOENN_WEDNESDAY, HoennSeek_EventScript_SageSolvedToday
	msgbox HoennSeek_Text_RiddleWed, MSGBOX_DEFAULT
	dynmultichoice 18, 4, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, HoennSeek_Text_AnsSponge, HoennSeek_Text_AnsTowel, HoennSeek_Text_AnsFish
	setvar VAR_0x8005, 1
	call HoennSeek_EventScript_RiddleCheck
	setflag FLAG_HOENN_SLOWKING_RIDDLE_SUN + HOENN_WEDNESDAY
	goto HoennSeek_EventScript_RiddleSolved
HoennSeek_EventScript_RiddleThu:
	goto_if_set FLAG_HOENN_SLOWKING_RIDDLE_SUN + HOENN_THURSDAY, HoennSeek_EventScript_SageSolvedToday
	msgbox HoennSeek_Text_RiddleThu, MSGBOX_DEFAULT
	dynmultichoice 18, 4, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, HoennSeek_Text_AnsPiano, HoennSeek_Text_AnsDoor, HoennSeek_Text_AnsMap
	setvar VAR_0x8005, 0
	call HoennSeek_EventScript_RiddleCheck
	setflag FLAG_HOENN_SLOWKING_RIDDLE_SUN + HOENN_THURSDAY
	goto HoennSeek_EventScript_RiddleSolved
HoennSeek_EventScript_RiddleFri:
	goto_if_set FLAG_HOENN_SLOWKING_RIDDLE_SUN + HOENN_FRIDAY, HoennSeek_EventScript_SageSolvedToday
	msgbox HoennSeek_Text_RiddleFri, MSGBOX_DEFAULT
	dynmultichoice 18, 4, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, HoennSeek_Text_AnsNeedle, HoennSeek_Text_AnsPotato, HoennSeek_Text_AnsWhirlpool
	setvar VAR_0x8005, 2
	call HoennSeek_EventScript_RiddleCheck
	setflag FLAG_HOENN_SLOWKING_RIDDLE_SUN + HOENN_FRIDAY
	goto HoennSeek_EventScript_RiddleSolved
HoennSeek_EventScript_RiddleSat:
	goto_if_set FLAG_HOENN_SLOWKING_RIDDLE_SUN + HOENN_SATURDAY, HoennSeek_EventScript_SageSolvedToday
	msgbox HoennSeek_Text_RiddleSat, MSGBOX_DEFAULT
	dynmultichoice 18, 4, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, HoennSeek_Text_AnsBall, HoennSeek_Text_AnsCold, HoennSeek_Text_AnsShadow
	setvar VAR_0x8005, 1
	call HoennSeek_EventScript_RiddleCheck
	setflag FLAG_HOENN_SLOWKING_RIDDLE_SUN + HOENN_SATURDAY
	goto HoennSeek_EventScript_RiddleSolved

@ Returns only on a right answer; otherwise ends the script.
HoennSeek_EventScript_RiddleCheck:
	goto_if_eq VAR_RESULT, MULTI_B_PRESSED, HoennSeek_EventScript_RiddleLater
	setflag FLAG_HOENN_DAILY_SLOWKING
	goto_if_ne VAR_RESULT, VAR_0x8005, HoennSeek_EventScript_RiddleWrong
	return
HoennSeek_EventScript_RiddleLater:
	msgbox HoennSeek_Text_RiddleLater, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_RiddleWrong:
	playmoncry SPECIES_SLOWPOKE, CRY_MODE_NORMAL
	msgbox HoennSeek_Text_RiddleWrong, MSGBOX_DEFAULT
	waitmoncry
	release
	end

HoennSeek_EventScript_RiddleSolved:
	addvar VAR_HOENN_SLOWKING_LINES, 1
	playse SE_M_PSYBEAM
	applymovement LOCALID_WELL_SLOWKING, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox HoennSeek_Text_RiddleRight, MSGBOX_DEFAULT
	call_if_eq VAR_HOENN_SLOWKING_LINES, 1, HoennSeek_EventScript_SageLine1
	call_if_eq VAR_HOENN_SLOWKING_LINES, 2, HoennSeek_EventScript_SageLine2
	call_if_eq VAR_HOENN_SLOWKING_LINES, 3, HoennSeek_EventScript_SageLine3
	call_if_eq VAR_HOENN_SLOWKING_LINES, 4, HoennSeek_EventScript_SageLine4
	call_if_eq VAR_HOENN_SLOWKING_LINES, 5, HoennSeek_EventScript_SageLine5
	call_if_eq VAR_HOENN_SLOWKING_LINES, 6, HoennSeek_EventScript_SageLine6
	call_if_eq VAR_HOENN_SLOWKING_LINES, 7, HoennSeek_EventScript_SageLine7
	goto_if_lt VAR_HOENN_SLOWKING_LINES, 7, HoennSeek_EventScript_SageMore
	setflag FLAG_HOENN_SLOWKING_PROPHECY
	msgbox HoennSeek_Text_SageComplete, MSGBOX_DEFAULT
	release
	end
HoennSeek_EventScript_SageMore:
	msgbox HoennSeek_Text_SageMore, MSGBOX_DEFAULT
	release
	end

@ Part 19's calls.
HoennSeek_EventScript_CallGengar::
	setflag FLAG_HOENN_CALL_GENGAR
	setspeaker HoennSeek_Text_NameBrendan
	pokenavcall HoennSeek_Text_CallGengar
	goto HoennSeek_EventScript_CallEnd

HoennSeek_EventScript_CallProphecy::
	setflag FLAG_HOENN_CALL_PROPHECY
	setspeaker HoennSeek_Text_NameMay
	pokenavcall HoennSeek_Text_CallProphecy
	goto HoennSeek_EventScript_CallEnd

HoennSeek_Movement_ShadowTwitch:
	face_left
	delay_8
	face_right
	delay_8
	face_down
	step_end

HoennSeek_Movement_GengarPops:
	jump_in_place_right
	face_right
	step_end

@ Part 19 texts.
HoennSeek_Text_GengarGrin:
	.string "…Huh?\p"
	.string "Your shadow under the streetlight\n"
	.string "just grinned at you!$"

HoennSeek_Text_GengarPointsRoute8:
	.string "Your shadow stretches out to the\n"
	.string "west, toward ROUTE 8…$"

HoennSeek_Text_GengarStops:
	.string "Your shadow stops dead and points\n"
	.string "at the ground.\p"
	.string "Something giggles from somewhere\n"
	.string "around your feet…$"

HoennSeek_Text_GengarBagJoke:
	.string "Your BAG rustles. You peek inside…\p"
	.string "Your POTION is gone! In its place\n"
	.string "is a note that says “BOO!”\p"
	.string "…You blink, and it's a POTION\n"
	.string "again. Very funny.$"

HoennSeek_Text_GengarPointsTunnel:
	.string "Your shadow stretches toward the\n"
	.string "UNDERGROUND PATH.$"

HoennSeek_Text_GengarEcho:
	.string "A cackle echoes all around\n"
	.string "the entrance!$"

HoennSeek_Text_GengarPointsTower:
	.string "Your shadow points back east,\n"
	.string "toward LAVENDER's RADIO TOWER.$"

HoennSeek_Text_GengarMemorial:
	.string "In the corner, a small plaque\n"
	.string "remembers the old POKéMON TOWER.\p"
	.string "Your shadow stretches toward it,\n"
	.string "then bulges…$"

HoennSeek_Text_GengarJumpsOut:
	.string "A GENGAR jumped out of your shadow!\p"
	.string "It's laughing so hard it can\n"
	.string "barely float.\p"
	.string "It seems to like you. It wants to\n"
	.string "come along!$"

HoennSeek_Text_GengarJoined:
	.string "GENGAR grins from your shadow.\n"
	.string "It's not leaving any time soon.$"

HoennSeek_Text_GengarNoRoom:
	.string "You have no room for it…\p"
	.string "GENGAR slips back into your shadow\n"
	.string "to wait. Come back some night!$"

HoennSeek_Text_SageIntro:
	.string "A voice echoes in your head…\p"
	.string "SLOWKING: Seeker. I know an old\n"
	.string "song, but it does not come cheaply.\p"
	.string "Each day of the week, I ask one\n"
	.string "riddle. Answer it, and I will teach\l"
	.string "you the next line of the song.$"

HoennSeek_Text_SageTomorrow:
	.string "SLOWKING: One answer a day,\n"
	.string "seeker. Come back tomorrow.$"

HoennSeek_Text_SageSolvedToday:
	.string "SLOWKING: You have already solved\n"
	.string "today's riddle. Another day brings\l"
	.string "another riddle.$"

HoennSeek_Text_SageHearAgain:
	.string "Hear the song so far?$"

HoennSeek_Text_SageDone:
	.string "SLOWKING: The song is yours now.\n"
	.string "Carry it to the whirling tides.$"

HoennSeek_Text_RiddleLater:
	.string "SLOWKING: Think on it. The riddle\n"
	.string "will wait.$"

HoennSeek_Text_RiddleWrong:
	.string "SLOWKING yawns enormously.\p"
	.string "SLOWKING: …No. Think on it\n"
	.string "until tomorrow.$"

HoennSeek_Text_RiddleRight:
	.string "SLOWKING: Yes. Listen well…$"

HoennSeek_Text_SageMore:
	.string "SLOWKING: There is more. Come back\n"
	.string "on another day.$"

HoennSeek_Text_SageComplete:
	.string "SLOWKING: That is the whole song.\p"
	.string "The guardian of the sea still\n"
	.string "sleeps. Perhaps you are the one\l"
	.string "who will wake it.$"

HoennSeek_Text_RiddleSun:
	.string "SLOWKING: The more of me there is,\n"
	.string "the less you see. GASTLY love me.\p"
	.string "What am I?$"
HoennSeek_Text_RiddleMon:
	.string "SLOWKING: I have a head and a tail\n"
	.string "but no body. TRAINERS flip me to\l"
	.string "see who goes first. What am I?$"
HoennSeek_Text_RiddleTue:
	.string "SLOWKING: I fly without wings and\n"
	.string "cry without eyes. When I come, the\l"
	.string "SLOWPOKE come out. What am I?$"
HoennSeek_Text_RiddleWed:
	.string "SLOWKING: The more I dry, the\n"
	.string "wetter I get. What am I?$"
HoennSeek_Text_RiddleThu:
	.string "SLOWKING: I have many keys but open\n"
	.string "no locks. The radio plays my songs.\l"
	.string "What am I?$"
HoennSeek_Text_RiddleFri:
	.string "SLOWKING: I have an eye but cannot\n"
	.string "see, and I spin forever above the\l"
	.string "guardian's bed. What am I?$"
HoennSeek_Text_RiddleSat:
	.string "SLOWKING: You can catch me, but\n"
	.string "you can never throw me. What am I?$"

HoennSeek_Text_AnsFog:
	.string "FOG$"
HoennSeek_Text_AnsDarkness:
	.string "DARKNESS$"
HoennSeek_Text_AnsSmoke:
	.string "SMOKE$"
HoennSeek_Text_AnsCoin:
	.string "A COIN$"
HoennSeek_Text_AnsKite:
	.string "A KITE$"
HoennSeek_Text_AnsSnake:
	.string "A SNAKE$"
HoennSeek_Text_AnsWind:
	.string "THE WIND$"
HoennSeek_Text_AnsBird:
	.string "A BIRD$"
HoennSeek_Text_AnsCloud:
	.string "A RAIN CLOUD$"
HoennSeek_Text_AnsSponge:
	.string "A SPONGE$"
HoennSeek_Text_AnsTowel:
	.string "A TOWEL$"
HoennSeek_Text_AnsFish:
	.string "A FISH$"
HoennSeek_Text_AnsPiano:
	.string "A PIANO$"
HoennSeek_Text_AnsDoor:
	.string "A DOOR$"
HoennSeek_Text_AnsMap:
	.string "A MAP$"
HoennSeek_Text_AnsNeedle:
	.string "A NEEDLE$"
HoennSeek_Text_AnsPotato:
	.string "A POTATO$"
HoennSeek_Text_AnsWhirlpool:
	.string "A WHIRLPOOL$"
HoennSeek_Text_AnsBall:
	.string "A POKé BALL$"
HoennSeek_Text_AnsCold:
	.string "A COLD$"
HoennSeek_Text_AnsShadow:
	.string "A SHADOW$"

@ The prophecy (written for Hoenn & Seek, in the spirit of the Lugia legend).
HoennSeek_Text_Prophecy1:
	.string "“When fire, ice and thunder\n"
	.string "quarrel, the sky will burn and\l"
	.string "the sea will rise.”$"
HoennSeek_Text_Prophecy2:
	.string "“The guardian of the sea will wake\n"
	.string "to calm them, but its song alone\l"
	.string "will not be enough.”$"
HoennSeek_Text_Prophecy3:
	.string "“Each titan sheds one feather,\n"
	.string "and each feather holds a piece of\l"
	.string "its power.”$"
HoennSeek_Text_Prophecy4:
	.string "“Gather all three with the wing of\n"
	.string "silver, and the guardian will hear\l"
	.string "the one who carries them.”$"
HoennSeek_Text_Prophecy5:
	.string "“Seek the islands of whirling\n"
	.string "tides when the sun has set.”$"
HoennSeek_Text_Prophecy6:
	.string "“Follow the lights that swim\n"
	.string "beneath the waves to the\l"
	.string "hidden shore.”$"
HoennSeek_Text_Prophecy7:
	.string "“Lay the treasures down there,\n"
	.string "and the song of the sea\l"
	.string "will answer.”$"

HoennSeek_Text_CallGengar:
	.string "{PLAYER}! It's BRENDAN!\p"
	.string "May and I stopped by the SOUL HOUSE\n"
	.string "in LAVENDER, and MR. FUJI told us\l"
	.string "the strangest story.\p"
	.string "A TRAINER's shadow laughed all\n"
	.string "night, then a GENGAR jumped out\l"
	.string "of it at the RADIO TOWER!\p"
	.string "That was you, right? Watch your\n"
	.string "BAG. GENGAR love pranks!$"

HoennSeek_Text_CallProphecy:
	.string "Hi, {PLAYER}! It's MAY.\p"
	.string "I went to see KURT in AZALEA\n"
	.string "about some APRICORN BALLS.\p"
	.string "He says the SLOWKING in the well\n"
	.string "finally sang its whole song for\l"
	.string "someone. Was that you?\p"
	.string "He thinks it's about the guardian\n"
	.string "of the sea. Spooky, right?$"
