.set PLAYER_STARTER_SPECIES,  VAR_TEMP_2

NewBarkTown_Lab_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NewBarkTown_Lab_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, NewBarkTown_Lab_OnFrame
	.byte 0

NewBarkTown_Lab_OnTransition::
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 6, NewBarkTown_Lab_EventScript_ElmAtComputer
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 2, NewBarkTown_Lab_EventScript_ElmAtComputer
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 3, NewBarkTown_Lab_EventScript_ElmAtComputer
	end
	
NewBarkTown_Lab_OnFrame::
	map_script_2 VAR_NEWBARKTOWN_LABSTATE, 4, NewBarkTown_Lab_EventScript_PoliceEpisode
	.2byte 0

NewBarkTown_Lab_EventScript_ElmAtComputer::
	setobjectxyperm LOCALID_ELM, 3, 2
	setobjectmovementtype LOCALID_ELM, MOVEMENT_TYPE_FACE_UP
	end

NewBarkTown_Lab_EventScript_TriggerStartLabLeft::	
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_WalkRight
	waitmovement 0
	goto NewBarkTown_Lab_EventScript_TriggerStartLab
	end

NewBarkTown_Lab_EventScript_TriggerStartLabRight::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_WalkLeft
	waitmovement 0
	goto NewBarkTown_Lab_EventScript_TriggerStartLab
	end

NewBarkTown_Lab_EventScript_TriggerStartLab::
	lock
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_LabMovement_WalkToElm
	waitmovement 0
	goto NewBarkTown_Lab_EventScript_ElmIntro
	end

NewBarkTown_EventScript_Aide1::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_AideAlwaysBusy, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Aide2::
	lock
	faceplayer
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_EventScript_Aide2Testimony
	msgbox NewBarkTown_Lab_Text_AideSave, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_EventScript_Aide2Testimony::
	msgbox NewBarkTown_Lab_Text_AideTheftTestimony, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_Elm::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_NEWBARKTOWN_LAB_AIDE, NewBarkTown_Lab_EventScript_ElmAideIsWaiting
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 7, NewBarkTown_Lab_EventScript_ElmMasterBall
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 8, NewBarkTown_Lab_EventScript_ElmKimono
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 9, NewBarkTown_Lab_EventScript_ElmLeague
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 10, NewBarkTown_Lab_EventScript_ElmSSTicket

	goto_if_unset FLAG_RECEIVED_TOGEPI_EGG, NewBarkTown_Lab_EventScript_Elm_AfterEggCheck
	goto_if_set FLAG_SHOWN_ELM_TOGEPI, NewBarkTown_Lab_EventScript_Elm_CallMe
	call_if_unset FLAG_SHOWN_ELM_TOGEPI, NewBarkTown_Lab_EventScript_Elm_Check_Togepi
NewBarkTown_Lab_EventScript_Elm_AfterEggCheck:
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 1, NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 5, NewBarkTown_Lab_EventScript_ElmState5

	goto_if_ge VAR_NEWBARKTOWN_LABSTATE, 6, NewBarkTown_Lab_EventScript_ElmState5
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 2, CopNewBarkTown_Lab_EventScript_ElmState2
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 3, CopNewBarkTown_Lab_EventScript_ElmState2
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_MrPokemon
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_ElmChoosePokemon
	end

NewBarkTown_Lab_EventScript_ElmAideIsWaiting::
	msgbox NewBarkTown_Lab_Text_ElmAideIsWaiting, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_Text_ElmAideIsWaiting:
	.string "¡{PLAYER}!\p"
	.string "¿Qué haces aquí?\p"
	.string "Mi ayudante aún te espera\n"
	.string "¡En CIUDAD MALVA!$"

NewBarkTown_Lab_EventScript_ElmIntro::
	msgbox NewBarkTown_Lab_Text_ElmIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
	end

NewBarkTown_Lab_EventScript_ElmRefused::
	msgbox NewBarkTown_Lab_Text_ElmRefused, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ElmAccepted
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_ElmRefused
	end

NewBarkTown_Lab_EventScript_ElmAccepted::
	msgbox NewBarkTown_Lab_Text_ElmAccepted, MSGBOX_DEFAULT
	msgbox NewBarkTown_Lab_Text_ElmResearchAmbitions, MSGBOX_DEFAULT
	delay 30
	playse SE_PC_LOGIN
	waitse
	playse SE_PIN
	applymovement LOCALID_ELM, Common_Movement_QuestionMark
	delay 55
	waitmovement LOCALID_ELM
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmail
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Left
	waitmovement 0
	waitmovement 0
	msgbox NewBarkTown_Lab_Text_ElmGotAnEmail, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ReturnFromEmail
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_Look_Up
	waitmovement 0
	delay 30
	msgbox NewBarkTown_Lab_Text_ElmMissionFromMrPokemon, MSGBOX_DEFAULT
	goto NewBarkTown_Lab_EventScript_ElmChoosePokemon
	end

NewBarkTown_Lab_EventScript_ElmChoosePokemon::
	msgbox NewBarkTown_Lab_Text_ElmChooseAPokemon, MSGBOX_DEFAULT
	closemessage
	setvar VAR_NEWBARKTOWN_LABSTATE, 1
	release
	end

NewBarkTown_Lab_EventScript_TriggerReturnPlayer::
	lock
	msgbox NewBarkTown_Lab_Text_ElmWhereGoing, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_ReturnPlayer
	waitmovement 0
	release
	end

NewBarkTown_Lab_EventScript_ShouldntTouch::
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
	closemessage
	release
	end


NewBarkTown_Lab_EventScript_ChikoritaBall::
	lock
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_ShouldntTouch
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_ChikoritaBall_Choice
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
	release
	closemessage
	end

NewBarkTown_Lab_EventScript_ChikoritaBall_Choice::
	@callnative DisableStaticRandomizer
	setvar VAR_STARTER_MON, 0
	setvar PLAYER_STARTER_SPECIES, SPECIES_CHIKORITA
	showmonpic PLAYER_STARTER_SPECIES, 10, 3
	playmoncry PLAYER_STARTER_SPECIES, CRY_MODE_NORMAL
	bufferspeciesname STR_VAR_1, PLAYER_STARTER_SPECIES
	buffermoncategory STR_VAR_2, PLAYER_STARTER_SPECIES
	msgbox NewBarkTown_Lab_Text_ChooseChikorita, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ChoseStarter
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_DeclinedStarter
	end

NewBarkTown_Lab_EventScript_CyndaquilBall::
	lock
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_ShouldntTouch
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_CyndaquilBall_Choice
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_CyndaquilBall_Choice::
	@callnative DisableStaticRandomizer
	setvar VAR_STARTER_MON, 1
	setvar PLAYER_STARTER_SPECIES, SPECIES_CYNDAQUIL
	showmonpic PLAYER_STARTER_SPECIES, 10, 3
	playmoncry PLAYER_STARTER_SPECIES, CRY_MODE_NORMAL
	bufferspeciesname STR_VAR_1, PLAYER_STARTER_SPECIES
	buffermoncategory STR_VAR_2, PLAYER_STARTER_SPECIES
	msgbox NewBarkTown_Lab_Text_ChooseCyndaquil, MSGBOX_YESNO	
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ChoseStarter
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_DeclinedStarter
	end

NewBarkTown_Lab_EventScript_TotodileBall::
	lock
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_ShouldntTouch
	goto_if_eq VAR_NEWBARKTOWN_LABSTATE, 1, NewBarkTown_Lab_EventScript_TotodileBall_Choice
	msgbox NewBarkTown_Lab_Text_ShouldntTouch, MSGBOX_DEFAULT
	release
	closemessage
	end

NewBarkTown_Lab_EventScript_TotodileBall_Choice::
	@callnative DisableStaticRandomizer
	setvar VAR_STARTER_MON, 2
	setvar PLAYER_STARTER_SPECIES, SPECIES_TOTODILE
	showmonpic PLAYER_STARTER_SPECIES, 10, 3
	playmoncry PLAYER_STARTER_SPECIES, CRY_MODE_NORMAL
	bufferspeciesname STR_VAR_1, PLAYER_STARTER_SPECIES
	buffermoncategory STR_VAR_2, PLAYER_STARTER_SPECIES
	msgbox NewBarkTown_Lab_Text_ChooseTotodile, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_ChoseStarter
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_DeclinedStarter
	end

NewBarkTown_Lab_EventScript_DeclinedStarter::
	hidemonpic
	msgbox NewBarkTown_Lab_Text_DidntChooseStarter, MSGBOX_DEFAULT
	closemessage
	@callnative EnableStaticRandomizer
	release
	end

NewBarkTown_Lab_EventScript_ChoseStarter::
	@callnative EnableStaticRandomizer
	hidemonpic
	removeobject VAR_LAST_TALKED
	msgbox NewBarkTown_Lab_Text_ChoseStarter, MSGBOX_DEFAULT
	call_if_eq VAR_STARTER_MON, 0, NewBarkTown_Lab_EventScript_GiveStarter_Chikorita
	call_if_eq VAR_STARTER_MON, 1, NewBarkTown_Lab_EventScript_GiveStarter_Cyndaquil
	call_if_eq VAR_STARTER_MON, 2, NewBarkTown_Lab_EventScript_GiveStarter_Totodile
	setflag FLAG_SYS_POKEMON_GET
	playfanfare MUS_OBTAIN_ITEM
	bufferspeciesname STR_VAR_1, PLAYER_STARTER_SPECIES
	message NewBarkTown_Lab_Text_ReceivedStarter
	waitfanfare
	specialvar VAR_RESULT, IsNuzlockeNicknamingActive
	goto_if_eq VAR_RESULT, TRUE, NewBarkTown_Lab_EventScript_ChoseStarter_NicknameStarter_Nuzlocke
	msgbox NewBarkTown_Lab_Text_Nickname, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_NicknameStarter
	callnative UpdateFollowingPokemon
	release
	end

NewBarkTown_Lab_EventScript_GiveStarter_Chikorita::
	call_if_unset FLAG_SHINY_STARTER_1, NewBarkTown_Lab_EventScript_GiveStarter_NotShiny
	call_if_set FLAG_SHINY_STARTER_1, NewBarkTown_Lab_EventScript_GiveStarter_Shiny
	return

NewBarkTown_Lab_EventScript_GiveStarter_Cyndaquil::
	call_if_unset FLAG_SHINY_STARTER_2, NewBarkTown_Lab_EventScript_GiveStarter_NotShiny
	call_if_set FLAG_SHINY_STARTER_2, NewBarkTown_Lab_EventScript_GiveStarter_Shiny
	return

NewBarkTown_Lab_EventScript_GiveStarter_Totodile::
	call_if_unset FLAG_SHINY_STARTER_3, NewBarkTown_Lab_EventScript_GiveStarter_NotShiny
	call_if_set FLAG_SHINY_STARTER_3, NewBarkTown_Lab_EventScript_GiveStarter_Shiny
	return

NewBarkTown_Lab_EventScript_GiveStarter_NotShiny::
	givemon PLAYER_STARTER_SPECIES, 5, ITEM_NONE, BALL_POKE, NATURE_RANDOM, NUM_ABILITY_PERSONALITY, MON_GENDER_RANDOM, 0, 0, 0, 0, 0, 0, USE_RANDOM_IVS, USE_RANDOM_IVS, USE_RANDOM_IVS, USE_RANDOM_IVS, USE_RANDOM_IVS, USE_RANDOM_IVS, MOVE_DEFAULT, MOVE_DEFAULT, MOVE_DEFAULT, MOVE_DEFAULT, SHINY_MODE_NEVER
	return

NewBarkTown_Lab_EventScript_GiveStarter_Shiny::
	givemon PLAYER_STARTER_SPECIES, 5, ITEM_NONE, BALL_POKE, NATURE_RANDOM, NUM_ABILITY_PERSONALITY, MON_GENDER_RANDOM, 0, 0, 0, 0, 0, 0, USE_RANDOM_IVS, USE_RANDOM_IVS, USE_RANDOM_IVS, USE_RANDOM_IVS, USE_RANDOM_IVS, USE_RANDOM_IVS, MOVE_DEFAULT, MOVE_DEFAULT, MOVE_DEFAULT, MOVE_DEFAULT, SHINY_MODE_ALWAYS	
	return

NewBarkTown_Lab_EventScript_NicknameStarter::
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	release
	end

NewBarkTown_Lab_EventScript_ChoseStarter_NicknameStarter_Nuzlocke::
	message NewBarkTown_Lab_Text_Nickname
	waitmessage
	setvar VAR_0x8004, 0
	call Common_EventScript_NameReceivedPartyMon
	release
	end

NewBarkTown_Lab_EventScript_MrPokemon::
	setvar VAR_NEWBARKTOWN_LABSTATE, 2
	setvar VAR_NEWBARK_TOWN_STATE, 3
	msgbox NewBarkTown_Lab_Text_ElmDirections1_Register, MSGBOX_DEFAULT
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox NewBarkTown_Lab_Text_RegisteredElm, MSGBOX_DEFAULT
	waitfanfare
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_EAST, NewBarkTown_Lab_EventScript_MrPokemonMovementSafe
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_CheckEmailSlow
	waitmovement 0
	clearflag FLAG_RECEIVED_FIRST_BALLS
	clearflag FLAG_RECEIVED_FIRST_POTION
	setvar VAR_NEWBARK_TOWN_STATE, 3
	setflag FLAG_ENABLE_CONDITION
	release
	end

NewBarkTown_Lab_EventScript_MrPokemonMovementSafe::
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_GotoComputerSafe
	waitmovement 0
	clearflag FLAG_RECEIVED_FIRST_BALLS
	clearflag FLAG_RECEIVED_FIRST_POTION
	setvar VAR_NEWBARK_TOWN_STATE, 3
	release
	end

CopNewBarkTown_Lab_EventScript_ElmState2::
	msgbox NewBarkTown_Lab_Text_ElmDirections1, MSGBOX_DEFAULT
	msgbox NewBarkTown_Lab_Text_ElmDirections2, MSGBOX_DEFAULT
	applymovement LOCALID_ELM, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_HealingMachine1::
	lock
	goto_if_set FLAG_SYS_POKEMON_GET, NewBarkTown_Lab_EventScript_HealingMachine2
	msgbox LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_HealingMachine2::
	call Common_EventScript_OutOfCenterPartyHeal
	release
	end



NewBarkTown_Lab_EventScript_TriggerAideGivePotion::
	lock
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox NewBarkTown_Lab_Text_AideGivePotion, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_POTION
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FIRST_POTION
	setvar VAR_NEWBARKTOWN_LABSTATE, 3
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	release
	end

NewBarkTown_Lab_EventScript_HideCyndaquil::
	setflag FLAG_HIDE_CYNDAQUILBALL
	return
NewBarkTown_Lab_EventScript_HideTotodile::
	setflag FLAG_HIDE_TOTODILEBALL
	return
NewBarkTown_Lab_EventScript_HideChikorita::
	setflag FLAG_HIDE_CHIKORITABALL
	return

NewBarkTown_Lab_EventScript_PoliceEpisode::
	lock
	setmetatile 7, 1, METATILE_R26_21_Broken_Window, TRUE
	call_if_eq VAR_STARTER_MON, 0 NewBarkTown_Lab_EventScript_HideCyndaquil
	call_if_eq VAR_STARTER_MON, 1 NewBarkTown_Lab_EventScript_HideTotodile
	call_if_eq VAR_STARTER_MON, 2 NewBarkTown_Lab_EventScript_HideChikorita
	applymovement OBJ_EVENT_ID_PLAYER, NeBarkTownLab_Movement_PlayerWalkToCop
	waitmovement 0
	setflag FLAG_HIDE_LAB_POLICEMAN
	turnobject LOCALID_COP DIR_WEST
	msgbox NewBarkTown_Lab_Text_Officer1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceYes
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceNo
	end

NewBarkTown_Lab_EventScript_PoliceNo::
	msgbox NewBarkTown_Lab_Text_OfficerNo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, NewBarkTown_Lab_EventScript_PoliceYes
	goto_if_eq VAR_RESULT, NO, NewBarkTown_Lab_EventScript_PoliceNo
	end

NewBarkTown_Lab_EventScript_PoliceYes::
	closemessage
	special NameRival
	waitstate
	msgbox NewBarkTown_Lab_Text_Officer2_1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, NewBarkTown_Lab_EventScript_PoliceYes
	msgbox NewBarkTown_Lab_Text_Officer2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_COP, NewBarkTown_Lab_Movement_CopLeaves
	waitmovement 0
	removeobject LOCALID_COP

	@ setobjectxyperm LOCALID_COP, 25, 4
	applymovement OBJ_EVENT_ID_PLAYER, NewBarkTown_Lab_Movement_PlayerStepsToElm
	waitmovement 0
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft1, MSGBOX_DEFAULT
	playfanfare MUS_LEVEL_UP
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft2, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepBack
	waitmovement 0
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft3, MSGBOX_DEFAULT
	delay 20
	closemessage
	applymovement LOCALID_ELM, NewBarkTown_Lab_Movement_ElmStepForward
	waitmovement 0
	msgbox NewBarkTown_Lab_Text_ElmAfterTheft4, MSGBOX_DEFAULT
	closemessage
	setvar VAR_NEWBARKTOWN_LABSTATE, 5
	setvar VAR_NEWBARK_TOWN_STATE, 4
	setflag FLAG_HIDE_MOMS_FRIEND
	clearflag FLAG_HIDE_MOMS_FRIEND2
	setflag FLAG_ADVENTURE_STARTED
	setflag FLAG_START_NUZLOCKE
	setflag FLAG_EXP_SHARE_ENABLED
	removeitem ITEM_MYSTERY_EGG
	release
	end

NewBarkTown_Lab_EventScript_ElmState5::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_ElmStudyingEgg, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ELM Common_Movement_FaceOriginalDirection
	release
	end
	
NewBarkTown_Lab_EventScript_ElmMasterBall::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall1, MSGBOX_DEFAULT
	giveitem ITEM_MASTER_BALL
	msgbox NewBarkTown_Lab_Text_ElmGiveMasterBall2, MSGBOX_DEFAULT
	closemessage
	delay 20
	playse SE_PIN
	applymovement LOCALID_ELM, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ELM
	msgbox NewBarkTown_Lab_Text_KimonoGirls, MSGBOX_DEFAULT
	closemessage
	setvar VAR_NEWBARKTOWN_LABSTATE, 8
	setvar VAR_ECRUTEAK_CITY_THEATER, 4
	setflag FLAG_HIDE_ECRUTEAK_SILVER
	setflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_NPCS
	clearflag FLAG_HIDE_ECRUTEAK_CITY_THEATER_KIMONOS
	release
	end

NewBarkTown_Lab_EventScript_ElmKimono::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_KimonoWaiting, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_ElmLeague::
	lock
	faceplayer
	msgbox NewBarkTown_Lab_Text_League, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_ElmSSTicket::
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket1, MSGBOX_DEFAULT
	giveitem ITEM_SS_TICKET
	msgbox NewBarkTown_Lab_Text_ElmGiveTicket2, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_SSAQUA_1F_GRANDPA
	setvar VAR_NEWBARKTOWN_LABSTATE, 11
	clearflag FLAG_HIDE_OLIVINE_PORT_OAK
	release
	end

NewBarkTown_Lab_EventScript_TriggerAideGiveBalls::
	lock
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1WalkToPlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox NewBarkTown_Lab_Text_AideGiveBalls, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_POKE_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FIRST_BALLS
	setvar VAR_NEWBARKTOWN_LABSTATE, 6
	applymovement LOCALID_AIDE1, NewBarkTown_Lab_Movement_Aide1LeavePlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	release
	end

NewBarkTown_Lab_EventScript_Elm_Check_WhereIsEgg::
	msgbox NewBarkTown_Lab_Text_ElmWaitingEggHatch, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_EventScript_Elm_Check_Togepi::
	checkspecies SPECIES_TOGEPI
	goto_if_eq VAR_RESULT, TRUE, NewBarkTown_Lab_EventScript_Elm_Togepi_Seen
	checkspecies SPECIES_TOGETIC
	goto_if_eq VAR_RESULT, TRUE, NewBarkTown_Lab_EventScript_Elm_Togepi_Seen
	checkspecies SPECIES_TOGEKISS
	goto_if_eq VAR_RESULT, TRUE, NewBarkTown_Lab_EventScript_Elm_Togepi_Seen
	return

NewBarkTown_Lab_EventScript_Elm_Togepi_Seen::
	msgbox NewBarkTown_Lab_Text_ShowTogepi1, MSGBOX_DEFAULT
	waitmessage
	msgbox NewBarkTown_Lab_Text_ShowTogepi2, MSGBOX_DEFAULT
	waitmessage
	msgbox NewBarkTown_Lab_Text_ShowTogepi3, MSGBOX_DEFAULT
	waitmessage
	msgbox NewBarkTown_Lab_Text_ElmGiveEverstone1, MSGBOX_DEFAULT
	waitmessage
	giveitem ITEM_EVERSTONE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox NewBarkTown_Lab_Text_ElmGiveEverstone2, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_SHOWN_ELM_TOGEPI
	release
	end

NewBarkTown_Lab_EventScript_Elm_CallMe::
	msgbox NewBarkTown_Lab_Text_Elm_CallMe, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_Lab_Movement_WalkRight:
	walk_right
	step_end

NewBarkTown_Lab_Movement_WalkLeft:
	walk_left
	step_end

NewBarkTown_LabMovement_WalkToElm:
	walk_up
	walk_up
	walk_up
	step_end

NewBarkTown_Lab_Movement_ReturnPlayer:
	walk_up
	step_end

NewBarkTown_Lab_Movement_CheckEmail:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	step_end

NewBarkTown_Lab_Movement_CheckEmailSlow:
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

NewBarkTown_Lab_Movement_GotoComputerSafe:
	walk_up
	walk_left
	walk_left
	walk_left
	face_up
	step_end

NewBarkTown_Lab_Movement_ReturnFromEmail:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	face_down
	step_end

NewBarkTown_Lab_Movement_Look_Left:
	face_left
	step_end

NewBarkTown_Lab_Movement_Look_Up:
	face_up
	step_end


NewBarkTown_Lab_Movement_Aide1WalkToPlayer:
	walk_down
	walk_down
	walk_right
	walk_right
	step_end

NewBarkTown_Lab_Movement_Aide1LeavePlayer:
	walk_left
	walk_left
	walk_up
	walk_up
	face_down
	step_end

NeBarkTownLab_Movement_PlayerWalkToCop:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_left
	walk_fast_up
	face_right
	step_end

NewBarkTown_Lab_Movement_CopLeaves:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

NewBarkTown_Lab_Movement_PlayerStepsToElm:
	walk_right
	face_up
	step_end

NewBarkTown_Lab_Movement_ElmStepBack:
	lock_facing_direction
	walk_fast_up
	unlock_facing_direction
	step_end

NewBarkTown_Lab_Movement_ElmStepForward:
	walk_fast_down
	step_end

NewBarkTown_Lab_Text_ShouldntTouch:
	.string "¡Mejor no tocarlo!$"

NewBarkTown_Lab_Text_ElmIntro:
	.string "ELM: {PLAYER}! ¡Aquí estás!\p"
	.string "Necesitaba pedirte un favor.\p"
	.string "Estoy haciendo nuevas\n"
	.string "investigaciones POKéMON. Me\l"
	.string "preguntaba si podrías\l"
	.string "ayudarme, {PLAYER}.\p"
	.string "Verás...\p"
	.string "Estoy escribiendo un artículo\n"
	.string "para presentarlo en un congreso.\p"
	.string "Pero hay algunas cosas que\n"
	.string "aún no entiendo del todo.\p"
	.string "¡Entonces!\p"
	.string "Me gustaría que entrenes a un\n"
	.string "POKéMON que atrapé hace poco.$"

NewBarkTown_Lab_Text_ElmAccepted:
	.string "¡Gracias, {PLAYER}!\n"
	.string "¡Eres de gran ayuda!$"

NewBarkTown_Lab_Text_ElmRefused:
	.string "Pero... ¡Por favor, necesito\n"
	.string "tu ayuda!$"

NewBarkTown_Lab_Text_ElmResearchAmbitions:
	.string "Cuando anuncie mis hallazgos,\n"
	.string "seguro profundizaremos más\p"
	.string "en los muchos misterios de\n"
	.string "POKéMON planta.\p"
	.string "¡Puedes contar con ello!$"

NewBarkTown_Lab_Text_ElmGotAnEmail:
	.string "¡Oh, mira! ¡Recibí un e-mail!\p"
	.string "... ... ... ... ... ... ... ...\n"
	.string "Hm... Ajá...\p"
	.string "Está bien...$"

NewBarkTown_Lab_Text_ElmMissionFromMrPokemon:
	.string "Oye, escucha.\p"
	.string "Tengo un conocido llamado\n"
	.string "SR. POKéMON.\p"
	.string "Siempre halla cosas raras y\n"
	.string "delira con sus descubrimientos.\p"
	.string "En fin, acabo de recibir un e-mail\n"
	.string "de él diciendo que esta\l"
	.string "vez es real.\p"
	.string "Es intrigante, pero estamos\n"
	.string "ocupados con la investigación...\p"
	.string "¡Espera!\n"
	.string "¡Ya sé!\p"
	.string "{PLAYER}, ¿puedes ir en mi\n"
	.string "lugar?$"

NewBarkTown_Lab_Text_ElmChooseAPokemon:
	.string "Quiero que críes a uno de los\n"
	.string "POKéMON de estas BALLS.\p"
	.string "¡Serás el primer compañero\n"
	.string "de ese POKéMON, {PLAYER}!\p"
	.string "¡Anda, elige uno!$"

NewBarkTown_Lab_Text_ElmWhereGoing:
	.string "ELM: ¡Espera! ¿A dónde\n"
	.string "vas?$"

NewBarkTown_Lab_Text_ChooseCyndaquil:
	.string "ELM: ¿Te llevarás a {STR_VAR_1},\n"
	.string "el POKéMON {STR_VAR_2}?$"

NewBarkTown_Lab_Text_ChooseTotodile:
	.string "ELM: ¿Quieres a {STR_VAR_1},\n"
	.string "el POKéMON {STR_VAR_2}?$"

NewBarkTown_Lab_Text_ChooseChikorita:
	.string "ELM: Así que te gusta {STR_VAR_1},\n"
	.string "el POKéMON {STR_VAR_2}?$"

NewBarkTown_Lab_Text_DidntChooseStarter:
	.string "ELM: Piénsalo con cuidado.\p"
	.string "Tu compañero es importante.$"

NewBarkTown_Lab_Text_ChoseStarter:
	.string "ELM: ¡Yo creo que ese POKéMON\n"
	.string "también es genial!$"

NewBarkTown_Lab_Text_ReceivedStarter:
	.string "{PLAYER} recibió {STR_VAR_1}!$"

NewBarkTown_Lab_Text_Nickname:
	.string "¿Quieres ponerle un apodo a\n"
	.string "tu {STR_VAR_1}?$"

NewBarkTown_Lab_Text_ElmDirections1:
	.string "MR. POKéMON vive un poco\n"
	.string "más allá de CIUDAD CEREZO, la\l"
	.string "siguiente ciudad.\p"
	.string "Es casi una ruta directa,\n"
	.string "así que no te perderás.\p"
	.string "Pero por si acaso, tienes mi\n"
	.string "número de teléfono. ¡Llámame si\l"
	.string "pasa cualquier cosa!$"

NewBarkTown_Lab_Text_ElmDirections1_Register:
	.string "MR. POKéMON vive un poco\n"
	.string "más allá de CIUDAD CEREZO, la\l"
	.string "siguiente ciudad.\p"
	.string "Es casi una ruta directa,\n"
	.string "así que no te perderás.\p"
	.string "Pero por si acaso, aquí tienes mi\n"
	.string "número de teléfono. ¡Llámame si\l"
	.string "pasa cualquier cosa!$"

NewBarkTown_Lab_Text_RegisteredElm:
	.string "Registro del PROF.ELM\n"
	.string "en el POKéGEAR.$"


NewBarkTown_Lab_Text_ElmLetYourMonBattle:
	.string "Si aparece un POKéMON salvaje,\n"
	.string "¡deja que tu POKéMON luche!$"

NewBarkTown_Lab_Text_ElmDirections2:
	.string "Si aparece un POKéMON salvaje,\n"
	.string "¡deja que tu POKéMON luche!\p"
	.string "Si tu POKéMON está herido,\n"
	.string "cúralo con la máquina a mi\l"
	.string "derecha o en el POKéCENTER.\p"
	.string "¡Cuento contigo!$"

NewBarkTown_Lab_Text_GotElmsNumber:
	.string "{PLAYER} obtuvo el número de\n"
	.string "teléfono de ELM.$"

NewBarkTown_Lab_Text_ElmDescribesMrPokemon:
	.string "MR. POKéMON viaja por doquier y\n"
	.string "encuentra rarezas.\p"
	.string "Lástima que solo sean raras y\n"
	.string "no muy útiles...$"

NewBarkTown_Lab_Text_ElmPokeBall:
	.string "Contiene un POKéMON capturado\n"
	.string "por el PROF.ELM.$"

@THEFT================================================================================

NewBarkTown_Lab_Text_ElmAfterTheft1:
	.string "ELM: {PLAYER}, esto es terrible...\p"
	.string "Oh, sí, ¿cuál fue el gran\n"
	.string "descubrimiento del SR. POKéMON?$"

NewBarkTown_Lab_Text_ElmAfterTheft2:
	.string "{PLAYER} le entregó el HUEVO MISTERIO\n"
	.string "al PROF.ELM.$"

NewBarkTown_Lab_Text_ElmAfterTheft3:
	.string "ELM: ¿Esto?$"

NewBarkTown_Lab_Text_ElmAfterTheft4:
	.string "Pero... ¿es un HUEVO POKéMON?\p"
	.string "¡Si lo es, es un gran\n"
	.string "descubrimiento!\p"
	.string "ELM: ¡¿Qué?!?\p"
	.string "¿El PROF.OAK te dio una POKéDEX?\p"
	.string "{PLAYER}, ¿es eso cierto?\n"
	.string "¡E-eso es increíble!\p"
	.string "Es magnífico viendo el\n"
	.string "potencial de los entrenadores.\p"
	.string "Vaya, {PLAYER}. Puede que tengas\n"
	.string "lo necesario para ser CAMPEÓN.\p"
	.string "Parece que te llevas\n"
	.string "muy bien con los POKéMON también.\p"
	.string "Deberías aceptar el desafío\n"
	.string "de los GIMNASIOS.\p"
	.string "El GIMNASIO más cercano sería el\n"
	.string "uno en CIUDAD MALVA.\p"
	.string "...{PLAYER}. El camino hacia el\n"
	.string "campeonato será muy largo.\p"
	.string "Antes de irte, asegúrate\n"
	.string "de hablar con tu mamá.$"

NewBarkTown_Lab_Text_ElmStudyingEgg:
	.string "ELM: ¡No te rindas!\n"
	.string "¡Te llamaré si descubro algo\l"
	.string "sobre ese HUEVO!$"

NewBarkTown_Lab_Text_ElmAideHasEgg:
	.string "ELM: {PLAYER}, ¿no conociste\n"
	.string "a mi asistente?\p"
	.string "Debió encontrarte con el\n"
	.string "HUEVO en CIUDAD MALVA.\p"
	.string "CENTRO POKéMON.\p"
	.string "Debes haberlo perdido por poco.\n"
	.string "Intenta atraparlo allí.$"

NewBarkTown_Lab_Text_ElmWaitingEggHatch:
	.string "ELM: Oye, ¿ese HUEVO ha cambiado\n"
	.string "algo?$"

NewBarkTown_Lab_Text_ElmThoughtEggHatched:
	.string "{PLAYER}? Pensé que el HUEVO\n"
	.string "había nacido.\p"
	.string "¿Dónde está el POKéMON?$"

NewBarkTown_Lab_Text_ShowTogepi1:
	.string "ELM: {PLAYER}, ¡te ves genial!$"

NewBarkTown_Lab_Text_ShowTogepi2:
	.string "¿Qué? ¡¿Ese POKéMON?!?$"

NewBarkTown_Lab_Text_ShowTogepi3:
	.string "¡El HUEVO nació! Así que los\n"
	.string "POKéMON nacen de HUEVOS...\p"
	.string "No, tal vez no todos los POKéMON\n"
	.string "que eres.\p"
	.string "Vaya, aún queda mucha\n"
	.string "investigación por hacer.$"

NewBarkTown_Lab_Text_ElmGiveEverstone1:
	.string "¡Gracias, {PLAYER}! Nos ayudas a\n"
	.string "resolver misterios POKéMON!\p"
	.string "Quiero que tengas esto como\n"
	.string "muestra de nuestro agradecimiento.$"

NewBarkTown_Lab_Text_ElmGiveEverstone2:
	.string "Es una PIEDRA ETERNA.\p"
	.string "Algunas especies de POKéMON\n"
	.string "cuando alcancen ciertos niveles.\p"
	.string "Un POKéMON con la PIEDRA ETERNA\n"
	.string "no evolucionará.\p"
	.string "Dáselo a un POKéMON que no\n"
	.string "quieras evolucionar.$"

NewBarkTown_Lab_Text_ElmCallYou:
	.string "ELM: {PLAYER}, te llamaré si\n"
	.string "surge cualquier novedad.$"

NewBarkTown_Lab_Text_AideAfterTheft:
	.string "...Suspiro... Ese POKéMON robado.\p"
	.string "Me pregunto cómo estará.\p"
	.string "Dicen que un POKéMON criado por\n"
	.string "alguien malo, se vuelve malo.$"

NewBarkTown_Lab_Text_ElmGiveMasterBall1:
	.string "ELM: ¡Hola, {PLAYER}!\p"
	.string "¡Gracias a ti, mi investigación\n"
	.string "va genial!\p"
	.string "Toma esto como muestra de mi\n"
	.string "aprecio.$"

NewBarkTown_Lab_Text_ElmGiveMasterBall2:
	.string "¡La MASTER BALL es la mejor!\p"
	.string "¡Es la BALL definitiva! Podrá\n"
	.string "atrapar cualquier POKéMON.\p"
	.string "Solo se entrega a reconocidos\n"
	.string "investigadores POKéMON.\p"
	.string "Creo que puedes darle un mejor\n"
	.string "uso que yo, {PLAYER}!$"

NewBarkTown_Lab_Text_KimonoGirls:
	.string "Por cierto...\n"
	.string "Un grupo de bellas CHICAS\l"
	.string "KIMONO te estaban buscando.\p"
	.string "Me dijeron que están\n"
	.string "esperándote en el\l" 
	.string "TEATRO DE DANZA DE CIUDAD IRIS.\p"
	.string "Sé que has pasado por muchas\n"
	.string "cosas desde que ese HUEVO te\l"
	.string "involucró en todo esto...\p"
	.string "Espero que lo logres superar.$"

NewBarkTown_Lab_Text_KimonoWaiting:
	.string "PROF.ELM: Las CHICAS\n"
	.string "KIMONO te esperan en el\l"
	.string "TEATRO DE DANZA DE CIUDAD IRIS.$"

NewBarkTown_Lab_Text_League:
	.string "PROF.ELM: Jajaja...\n"
	.string "¡Buen trabajo!\p"
	.string "Ese HUEVO raro te ha traído\n"
	.string "Muchos problemas, ¿eh?\p"
	.string "Las KIMONO GIRLS dijeron algo\n"
	.string "¿sobre mí?\p"
	.string "Yo no tengo nada que ver.\p"
	.string "Tomaste tu decisión y la\n"
	.string "llevaste a cabo.\p"
	.string "Tras hacer tanto, ¡ya deberías\n"
	.string "poder enfrentar la LIGA!\p"
	.string "¡Deberías ir hacia la MESETA\n"
	.string "AÑIL!\p"
	.string "¿Sabes cómo llegar?\n"
	.string "Sigue la RUTA 27 hasta la 26.\p"
	.string "¡Una vez allí, ve hacia el norte!$"


NewBarkTown_Lab_Text_ElmGiveTicket1:
	.string "ELM: {PLAYER}! ¡Aquí estás!\p"
	.string "Llamé porque tengo\n"
	.string "algo para ti.\p"
	.string "¿Ves? Es un S.S.TICKET.\p"
	.string "Ahora puedes capturar POKéMON en\n"
	.string "KANTO.$"

NewBarkTown_Lab_Text_ElmGiveTicket2:
	.string "El barco sale de CIUDAD OLIVO\n"
	.string "CIUDAD MALVA.\p"
	.string "Pero ya sabías eso,\n"
	.string "{PLAYER}.\p"
	.string "después de todo, has viajado\n"
	.string "por doquier con tus POKéMON.\p"
	.string "¡Dale mis saludos al PROF.OAK en\n"
	.string "KANTO!$"

NewBarkTown_Lab_Text_LabMonEgg:
	.string "Es el HUEVO POKéMON que está\n"
	.string "estudiado por el PROF.ELM.$"

NewBarkTown_Lab_Text_AideGivePotion:
	.string "{PLAYER}, quiero que tengas\n"
	.string "esto para tu encargo.$"

NewBarkTown_Lab_Text_AideAlwaysBusy:
	.string "Solo somos tres, así que\n"
	.string "siempre estamos ocupados.$"

NewBarkTown_Lab_Text_AideSave:
	.string "¡No olvides guardar tu partida\n"
	.string "con frecuencia!\p"
	.string "¡Pulsa el botón START y luego\n"
	.string "GUARDA la partida!$"

NewBarkTown_Lab_Text_AideTheftTestimony:
	.string "Se escuchó un ruido fuerte\n"
	.string "afuera...\p"
	.string "Cuando fuimos a mirar,\n"
	.string "alguien robó un POKéMON.\p"
	.string "¡Es increíble que alguien\n"
	.string "haga algo así!\p"
	.string "...Suspiro... Ese POKéMON robado.\p"
	.string "Me pregunto cómo estará.\p"
	.string "Dicen que un POKéMON criado por\n"
	.string "alguien malo, se vuelve malo.$"

NewBarkTown_Lab_Text_AideGiveBalls:
	.string "¡{PLAYER}!\p"
	.string "¡Usa esto en tu misión de la\n"
	.string "POKéDEX!$"

NewBarkTown_Lab_Text_AideExplainBalls:
	.string "Para llenar tu POKéDEX, debes\n"
	.string "atrapar POKéMON.\p"
	.string "Lanza POKé BALLS a POKéMON\n"
	.string "salvajes para atraparlos.$"

NewBarkTown_Lab_Text_Officer1:
	.string "Oí que robaron un POKéMON\n"
	.string "aquí...\p"
	.string "Solo estaba consiguiendo unos\n"
	.string "información del PROF.ELM.\p"
	.string "Al parecer, era un joven\n"
	.string "con el pelo largo y rojo...\p"
	.string "¿Qué?\p"
	.string "¿Luchaste contra un\n"
	.string "entrenador así?\p"
	.string "¿De casualidad sabes\n"
	.string "su nombre?$"

NewBarkTown_Lab_Text_Officer2_1:
	.string "¡OK! ¿Así que {RIVAL} era su nombre?$"

NewBarkTown_Lab_Text_Officer2:
	.string "¡Gracias por ayudar en mi\n"
	.string "investigación!$"

NewBarkTown_Lab_Text_OfficerNo:
	.string "¡Seguro que conseguiste su nombre!$"

NewBarkTown_Lab_Text_Elm_CallMe:
	.string "¡Ah, {PLAYER}!\p"
	.string "¿Cómo va tu POKéDEX?\n"
	.string "Ahora estoy ocupado, pero llámame\l"
	.string "¡y revisaré tu progreso!$"
