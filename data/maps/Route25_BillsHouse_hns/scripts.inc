Route25_BillsHouse_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route25_BillsHouse_hns_OnTransition
	.byte 0

Route25_BillsHouse_hns_OnTransition::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	end

Route25_BillsHouse_hns_EventScript_TeleporterTest::
	lockall
	dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, Route25_BillsHouse_hns_Text_Slowking, Route25_BillsHouse_hns_Text_Pikachu, Route25_BillsHouse_hns_Text_Clefairy, Route25_BillsHouse_hns_Text_Cancel
	switch VAR_RESULT
	case 0, Route25_BillsHouse_hns_PickSlowking
	case 1, Route25_BillsHouse_hns_PickPikachu
	case 2, Route25_BillsHouse_hns_PickClefairy
	case 3, Route25_BillsHouse_hns_EndChoice
	case 127, Route25_BillsHouse_hns_EndChoice
	end

Route25_BillsHouse_hns_PickSlowking::
	setvar VAR_0x8004, SPECIES_SLOWKING
	setvar VAR_TEMP_0, SPECIES_SLOWKING
	goto Route25_BillsHouse_hns_CheckParty
	end

Route25_BillsHouse_hns_PickPikachu::
	setvar VAR_0x8004, SPECIES_PIKACHU
	setvar VAR_TEMP_0, SPECIES_PIKACHU
	goto Route25_BillsHouse_hns_CheckParty
	end

Route25_BillsHouse_hns_PickClefairy::
	setvar VAR_0x8004, SPECIES_CLEFAIRY
	setvar VAR_TEMP_0, SPECIES_CLEFAIRY
	goto Route25_BillsHouse_hns_CheckParty
	end

Route25_BillsHouse_hns_EndChoice::
	releaseall
	end

Route25_BillsHouse_hns_CheckParty::
	special CheckPartyForSpecies
	goto_if_eq VAR_RESULT, FALSE, Route25_BillsHouse_hns_NoPokemon
	goto Route25_BillsHouse_hns_CutsceneSetup
	end

Route25_BillsHouse_hns_NoPokemon::
	msgbox Route25_BillsHouse_hns_Text_NotInParty
	releaseall
	end


Route25_BillsHouse_SetPlayerMale::
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_GOLD_NORMAL_HNS
	return

Route25_BillsHouse_SetPlayerFemale::
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_KRIS_NORMAL_HNS
	return

Route25_BillsHouse_hns_CutsceneSetup::
	fadescreen FADE_TO_BLACK
	clearflag FLAG_TEMP_1
	copyvar VAR_OBJ_GFX_ID_0, VAR_TEMP_0
	addvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_MON_BASE
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Route25_BillsHouse_SetPlayerMale
	call_if_eq VAR_RESULT, FEMALE, Route25_BillsHouse_SetPlayerFemale
	addobject LOCALID_BILLS_GRANDPA_PLAYER
	addobject LOCALID_BILLS_GRANDPA_OLD_MON
	applymovement OBJ_EVENT_ID_PLAYER, Route25_BillsHouse_Movement_HidePlayer
	hidefollower
	turnobject LOCALID_BILLS_GRANDPA, DIR_NORTH
	special SpawnCameraObject
	applymovement OBJ_EVENT_ID_CAMERA, Route25_BillsHouse_Movement_CameraPanUp
	waitmovement 0
	delay 60
	fadescreen FADE_FROM_BLACK

Route25_BillsHouse_hns_CutsceneBeforeTeleport::
	delay 60
	opendoor 10, 3
	waitdooranim
	playmoncry VAR_TEMP_0, CRY_MODE_NORMAL
	waitmoncry 
	applymovement LOCALID_BILLS_GRANDPA_OLD_MON, Common_Movement_WalkUp1
	waitmovement 0
	turnobject LOCALID_BILLS_GRANDPA_OLD_MON, DIR_SOUTH
	applymovement LOCALID_BILLS_GRANDPA_PLAYER, Common_Movement_WalkRight1
	waitmovement 0
	turnobject LOCALID_BILLS_GRANDPA_PLAYER, DIR_NORTH
	playse SE_CONTEST_CURTAIN_FALL
	closedoor 10, 3
	delay 10
	removeobject LOCALID_BILLS_GRANDPA_OLD_MON
	waitdooranim

Route25_BillsHouse_hns_CutsceneTeleport::
	delay 35
	playse SE_PIN
	waitse
	setvar VAR_0x8004, 0
	special AnimateTeleporterHousing
	delay 10
	call Route25_BillsHouse_hns_BeepSE
	call Route25_BillsHouse_hns_BeepSE
	call Route25_BillsHouse_hns_BeepSE
	call Route25_BillsHouse_hns_BeepSE
	call Route25_BillsHouse_hns_BeepSE
	call Route25_BillsHouse_hns_BeepSE
	call Route25_BillsHouse_hns_BeepSE
	setvar VAR_0x8004, 1
	special AnimateTeleporterHousing
	playse SE_WARP_IN
	special AnimateTeleporterCable
	delay 30
	applymovement LOCALID_BILLS_GRANDPA_PLAYER, Route25_BillsHouse_Movement_PlayerMoveLeft
	waitse
	call Route25_BillsHouse_hns_BeepSE
	call Route25_BillsHouse_hns_BeepSE
	call Route25_BillsHouse_hns_BeepSE
	call Route25_BillsHouse_hns_BeepSE
	call Route25_BillsHouse_hns_BeepSE
	special GetRegionalFormSpecies
	copyvar VAR_TEMP_1, VAR_RESULT
	clearflag FLAG_TEMP_2
	copyvar VAR_OBJ_GFX_ID_1, VAR_TEMP_1
	addvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_MON_BASE
	
Route25_BillsHouse_hns_CutsceneAfterTeleport::
	opendoor 3, 3
	delay 10
	addobject LOCALID_BILLS_GRANDPA_NEW_MON
	waitdooranim
	applymovement LOCALID_BILLS_GRANDPA_PLAYER, Route25_BillsHouse_Movement_PlayerSlideDown
	playse SE_LEDGE
	applymovement LOCALID_BILLS_GRANDPA_NEW_MON, Common_Movement_WalkDown1
	waitmovement 0
	waitmovement 0
	@playse SE_PIN
	@applymovement LOCALID_BILLS_GRANDPA_PLAYER, Common_Movement_ExclamationMark
	@delay 60
	playse SE_CONTEST_CURTAIN_FALL
	closedoor 3, 3
	delay 10
	applymovement LOCALID_BILLS_GRANDPA_NEW_MON, Route25_BillsHouse_Movement_MonCelebration
	waitmovement 0
	playmoncry VAR_TEMP_0, CRY_MODE_NORMAL
	waitmoncry
	delay 60

Route25_BillsHouse_hns_CutsceneCleanup::
	fadescreen FADE_TO_BLACK
	applymovement OBJ_EVENT_ID_CAMERA, Route25_BillsHouse_Movement_CameraPanDown
	waitmovement 0
	removeobject LOCALID_BILLS_GRANDPA_NEW_MON
	removeobject LOCALID_BILLS_GRANDPA_OLD_MON
	removeobject LOCALID_BILLS_GRANDPA_PLAYER
	applymovement OBJ_EVENT_ID_PLAYER, Route25_BillsHouse_Movement_ShowPlayer
	waitmovement 0
	turnobject LOCALID_BILLS_GRANDPA, DIR_SOUTH
	callnative UpdateFollowingPokemon
	special RemoveCameraObject
	special ConvertToRegionalForm
	delay 60
	fadescreen FADE_FROM_BLACK
	releaseall
	end

Route25_BillsHouse_Movement_CameraPanUp:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	step_end

Route25_BillsHouse_Movement_CameraPanDown:
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	step_end

Route25_BillsHouse_Movement_PlayerMoveLeft:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	face_up
	step_end

Route25_BillsHouse_Movement_PlayerSlideDown:
	lock_facing_direction
	jump_down
	unlock_facing_direction
	step_end

Route25_BillsHouse_hns_BeepSE::
	playse SE_BALL
	waitse
	delay 20
	return

Route25_BillsHouse_Movement_HidePlayer:
	set_invisible
	step_end

Route25_BillsHouse_Movement_ShowPlayer:
	set_visible
	step_end

Route25_BillsHouse_hns_Text_Slowking:
	.string "SLOWKING$"

Route25_BillsHouse_hns_Text_Pikachu:
	.string "PIKACHU$"

Route25_BillsHouse_hns_Text_Clefairy:
	.string "CLEFAIRY$"

Route25_BillsHouse_hns_Text_Cancel:
	.string "CANCEL$"

Route25_BillsHouse_hns_Text_NotInParty:
	.string "I don't see that POKéMON\n"
	.string "in your party.$"

@VAR_BILLS_GRANDPA

Route25_BillsHouse_EventScript_Gramps::
	lock
	faceplayer
	goto_if_eq VAR_BILLS_GRANDPA, 1, Route25_BillsHouse_EventScript_Gramps_Spinda
	goto_if_eq VAR_BILLS_GRANDPA, 2, Route25_BillsHouse_EventScript_Gramps_Roselia
	goto_if_eq VAR_BILLS_GRANDPA, 3, Route25_BillsHouse_EventScript_Gramps_Lotad
	goto_if_eq VAR_BILLS_GRANDPA, 4, Route25_BillsHouse_EventScript_Gramps_Growlithe
	goto_if_eq VAR_BILLS_GRANDPA, 5, Route25_BillsHouse_EventScript_Gramps_Pichu
	goto_if_eq VAR_BILLS_GRANDPA, 6, Route25_BillsHouse_EventScript_Gramps_ShownAll
	msgbox Route25_BillsHouse_Text_GrandpaIntro, MSGBOX_DEFAULT
	setvar VAR_BILLS_GRANDPA, 1
	goto Route25_BillsHouse_EventScript_Gramps_Spinda

Route25_BillsHouse_EventScript_Gramps_Declined::
	msgbox Route25_BillsHouse_Text_YouDontHaveIt, MSGBOX_DEFAULT
	closemessage
	release
	end

Route25_BillsHouse_EventScript_Gramps_WrongMon::
	msgbox Route25_BillsHouse_Text_WrongPokemon, MSGBOX_DEFAULT
	closemessage
	release
	end

Route25_BillsHouse_EventScript_Gramps_Spinda::
	msgbox Route25_BillsHouse_Text_Spinda, MSGBOX_DEFAULT
	msgbox Route25_BillsHouse_Text_AskToSeeMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Route25_BillsHouse_EventScript_Gramps_Declined
	msgbox Route25_BillsHouse_Text_ExcitedToSee, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	@ Store selected slot in VAR_0x800A
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route25_BillsHouse_EventScript_Gramps_Declined
	@ Get the species of the selected Pokémon
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	@ Check if it's Spinda
	goto_if_ne VAR_RESULT, SPECIES_SPINDA, Route25_BillsHouse_EventScript_Gramps_WrongMon
	bufferspeciesname STR_VAR_1, SPECIES_SPINDA
	setvar VAR_TEMP_0, ITEM_EVERSTONE
	goto Route25_BillsHouse_EventScript_Gramps_Correctmon

Route25_BillsHouse_EventScript_Gramps_Roselia::
	msgbox Route25_BillsHouse_Text_Roselia, MSGBOX_DEFAULT
	msgbox Route25_BillsHouse_Text_AskToSeeMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Route25_BillsHouse_EventScript_Gramps_Declined
	msgbox Route25_BillsHouse_Text_ExcitedToSee, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route25_BillsHouse_EventScript_Gramps_Declined
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, SPECIES_ROSELIA, Route25_BillsHouse_EventScript_Gramps_WrongMon
	bufferspeciesname STR_VAR_1, SPECIES_ROSELIA
	setvar VAR_TEMP_0, ITEM_LEAF_STONE
	goto Route25_BillsHouse_EventScript_Gramps_Correctmon

Route25_BillsHouse_EventScript_Gramps_Lotad::
	msgbox Route25_BillsHouse_Text_Lotad, MSGBOX_DEFAULT
	msgbox Route25_BillsHouse_Text_AskToSeeMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Route25_BillsHouse_EventScript_Gramps_Declined
	msgbox Route25_BillsHouse_Text_ExcitedToSee, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route25_BillsHouse_EventScript_Gramps_Declined
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, SPECIES_LOTAD, Route25_BillsHouse_EventScript_Gramps_WrongMon
	bufferspeciesname STR_VAR_1, SPECIES_LOTAD
	setvar VAR_TEMP_0, ITEM_DEEP_SEA_TOOTH
	goto Route25_BillsHouse_EventScript_Gramps_Correctmon

Route25_BillsHouse_EventScript_Gramps_Growlithe::
	msgbox Route25_BillsHouse_Text_Growlithe, MSGBOX_DEFAULT
	msgbox Route25_BillsHouse_Text_AskToSeeMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Route25_BillsHouse_EventScript_Gramps_Declined
	msgbox Route25_BillsHouse_Text_ExcitedToSee, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route25_BillsHouse_EventScript_Gramps_Declined
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, SPECIES_GROWLITHE, Route25_BillsHouse_EventScript_Gramps_WrongMon
	bufferspeciesname STR_VAR_1, SPECIES_GROWLITHE
	setvar VAR_TEMP_0, ITEM_SUN_STONE
	goto Route25_BillsHouse_EventScript_Gramps_Correctmon

Route25_BillsHouse_EventScript_Gramps_Pichu::
	msgbox Route25_BillsHouse_Text_Pichu, MSGBOX_DEFAULT
	msgbox Route25_BillsHouse_Text_AskToSeeMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Route25_BillsHouse_EventScript_Gramps_Declined
	msgbox Route25_BillsHouse_Text_ExcitedToSee, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, Route25_BillsHouse_EventScript_Gramps_Declined
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, SPECIES_PICHU, Route25_BillsHouse_EventScript_Gramps_WrongMon
	bufferspeciesname STR_VAR_1, SPECIES_PICHU
	setvar VAR_TEMP_0, ITEM_DEEP_SEA_SCALE
	goto Route25_BillsHouse_EventScript_Gramps_Correctmon

Route25_BillsHouse_EventScript_Gramps_ShownAll::
	msgbox Route25_BillsHouse_Text_ShownAll, MSGBOX_DEFAULT
	closemessage
	release
	end

Route25_BillsHouse_EventScript_Gramps_Correctmon::
	msgbox Route25_BillsHouse_Text_ShownPokemon, MSGBOX_DEFAULT
	msgbox Route25_BillsHouse_Text_Appreciation, MSGBOX_DEFAULT
	giveitem VAR_TEMP_0
	call_if_eq VAR_TEMP_0, ITEM_LEAF_STONE, Route25_BillsHouse_EventScript_Gramps_ExtraLeafStones
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox Route25_BillsHouse_Text_ComeAgain, MSGBOX_DEFAULT
	addvar VAR_BILLS_GRANDPA, 1
	closemessage
	release
	end

Route25_BillsHouse_EventScript_Gramps_ExtraLeafStones::
	additem VAR_TEMP_0
	additem VAR_TEMP_0
	return

Route25_BillsHouse_Test::
	givemon SPECIES_SPINDA, 10
	givemon SPECIES_LOTAD, 10
	givemon SPECIES_ROSELIA, 10
	givemon SPECIES_GROWLITHE, 10
	givemon SPECIES_PICHU, 10
	end

Route25_BillsHouse_Movement_MonCelebration:
	jump_in_place_down
	jump_in_place_left
	jump_in_place_right
	jump_in_place_down
	step_end

Route25_BillsHouse_Text_GrandpaIntro:
	.string "Hm? You know BILL? He's my\n"
	.string "grandson.\p"
	.string "He's in JOHTO. He does\n"
	.string "something with PCs, so I'm\l"
	.string "housesitting.$"

Route25_BillsHouse_Text_Spinda:
	.string "My grandson BILL told me about\n"
	.string "a POKéMON that is covered in\l"
	.string "a random pattern.$"

Route25_BillsHouse_Text_Roselia:
	.string "Ah, my grandson mentioned a\n"
	.string "green POKéMON that has flowers\l"
	.string "growing from its wrists.$"

Route25_BillsHouse_Text_Lotad:
	.string "Do you know of a water POKéMON\n"
	.string "that has a big lily pad on\l"
	.string "its head?"
	.string "I heard there are some at the\n"
	.string "FUCHSIA SAFARI ZONE.\p"
	.string "I would surely like to see it.$"

Route25_BillsHouse_Text_Growlithe:
	.string "BILL told me about a POKéMON\n"
	.string "that is\l"
	.string "very loyal to its trainer.\p"
	.string "It's supposed to ROAR well.$"

Route25_BillsHouse_Text_Pichu:
	.string "Do you know that hugely popular\n"
	.string "POKéMON?\p"
	.string "The POKéMON that has a yellow\n"
	.string "body and red cheeks.\p"
	.string "I would love to see what it\n"
	.string "looks like before it evolves$"

Route25_BillsHouse_Text_AskToSeeMon:
	.string "If you have that POKéMON, may I\n"
	.string "see it, please?$"

Route25_BillsHouse_Text_ExcitedToSee:
	.string "You will show me? How good of\n"
	.string "you!$"

Route25_BillsHouse_Text_YouDontHaveIt:
	.string "You don't have it?\n"
	.string "That's too bad…$"

Route25_BillsHouse_Text_ShownPokemon:
	.string "Ah, so that is {STR_VAR_1}?\p"
	.string "Isn't it cute! That's so kind\n"
	.string "of you.$"

Route25_BillsHouse_Text_Appreciation:
	.string "Thanks!\p"
	.string "This is a token of my\n"
	.string "appreciation.$"

Route25_BillsHouse_Text_ComeAgain:
	.string "Come visit again sometime.$"

Route25_BillsHouse_Text_ShownAll:
	.string "Thanks for showing me so many\n"
	.string "cute POKéMON.\p"
	.string "I really enjoyed myself. I'm\n"
	.string "glad\l"
	.string "I've lived such a long life.$"

Route25_BillsHouse_Text_WrongPokemon:
	.string "Hm?\p"
	.string "That's not the POKéMON that I\n"
	.string "was told about.$"


