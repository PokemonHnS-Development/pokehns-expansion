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
