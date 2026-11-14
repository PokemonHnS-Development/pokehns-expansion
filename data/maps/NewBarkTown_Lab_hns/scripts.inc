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
	.string "{PLAYER}!\p"
	.string "מה אתה עושה כאן?\p"
	.string "העוזר שלי עדיין מחכה לך\n"
	.string "בעיר ויולט!$"

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
	.string "עדיף לא לגעת!$"

NewBarkTown_Lab_Text_ElmIntro:
	.string "אלם: {PLAYER}! הנה אתה!\p"
	.string "רציתי לבקש ממך טובה.\p"
	.string "אני עורך עכשיו מחקר פוקימונים חדש.\n"
	.string "תהיתי אם תוכל לעזור לי בו, {PLAYER}.\p"
	.string "העניין הוא…\p"
	.string "אני כותב מאמר שאני\n"
	.string "רוצה להציג בכנס.\p"
	.string "אבל יש כמה דברים שאני\n"
	.string "עדיין לא ממש מבין.\p"
	.string "אז ככה!\p"
	.string "הייתי רוצה שתגדל\n"
	.string "פוקימון שתפסתי לא מזמן.$"

NewBarkTown_Lab_Text_ElmAccepted:
	.string "תודה, {PLAYER}!\n"
	.string "זו עזרה ענקית!$"

NewBarkTown_Lab_Text_ElmRefused:
	.string "אבל… בבקשה, אני צריך\n"
	.string "את העזרה שלך!$"

NewBarkTown_Lab_Text_ElmResearchAmbitions:
	.string "כשאפרסם את התגליות שלי,\n"
	.string "אני בטוח שנעמיק\p"
	.string "עוד יותר בתעלומות הרבות\n"
	.string "של הפוקימונים.\p"
	.string "אפשר לסמוך על זה!$"

NewBarkTown_Lab_Text_ElmGotAnEmail:
	.string "אה, היי! קיבלתי אימייל!\p"
	.string "… … … … … … … …\n"
	.string "הממ… אה-הא…\p"
	.string "אוקיי…$"

NewBarkTown_Lab_Text_ElmMissionFromMrPokemon:
	.string "היי, תקשיב.\p"
	.string "יש לי מכר שקוראים לו\n"
	.string "מר פוקימון.\p"
	.string "הוא כל הזמן מוצא דברים מוזרים\n"
	.string "ומתלהב מהתגליות שלו.\p"
	.string "בכל אופן, הרגע קיבלתי ממנו אימייל\n"
	.string "שאומר שהפעם זה אמיתי.\p"
	.string "זה מסקרן, אבל אנחנו עסוקים\n"
	.string "במחקר הפוקימונים שלנו…\p"
	.string "רגע!\n"
	.string "יש לי רעיון!\p"
	.string "{PLAYER}, תוכל ללכת\n"
	.string "במקומנו?$"

NewBarkTown_Lab_Text_ElmChooseAPokemon:
	.string "אני רוצה שתגדל את אחד\n"
	.string "הפוקימונים שבפוכדורים האלה.\p"
	.string "אתה תהיה השותף הראשון\n"
	.string "של הפוקימון הזה, {PLAYER}!\p"
	.string "קדימה. תבחר אחד!$"

NewBarkTown_Lab_Text_ElmWhereGoing:
	.string "אלם: רגע!\n"
	.string "לאן אתה הולך?$"

NewBarkTown_Lab_Text_ChooseCyndaquil:
	.string "אלם: תיקח את {STR_VAR_1},\n"
	.string "פוקימון {STR_VAR_2}?$"

NewBarkTown_Lab_Text_ChooseTotodile:
	.string "אלם: אתה רוצה את {STR_VAR_1},\n"
	.string "פוקימון {STR_VAR_2}?$"

NewBarkTown_Lab_Text_ChooseChikorita:
	.string "אלם: אז אתה אוהב את {STR_VAR_1},\n"
	.string "פוקימון {STR_VAR_2}?$"

NewBarkTown_Lab_Text_DidntChooseStarter:
	.string "אלם: תחשוב על זה היטב.\p"
	.string "השותף שלך חשוב.$"

NewBarkTown_Lab_Text_ChoseStarter:
	.string "אלם: גם אני חושב שזה\n"
	.string "פוקימון נהדר!$"

NewBarkTown_Lab_Text_ReceivedStarter:
	.string "{PLAYER} קיבל את {STR_VAR_1}!$"

NewBarkTown_Lab_Text_Nickname:
	.string "לתת כינוי\n"
	.string "ל{STR_VAR_1} שלך?$"

NewBarkTown_Lab_Text_ElmDirections1:
	.string "מר פוקימון גר קצת אחרי צ'ריגרוב,\n"
	.string "העיר הבאה בדרך.\p"
	.string "הדרך לשם כמעט ישרה,\n"
	.string "כך שאי אפשר לפספס.\p"
	.string "אבל ליתר ביטחון, יש לך את המספר שלי.\n"
	.string "תתקשר אליי אם יקרה משהו!$"

NewBarkTown_Lab_Text_ElmDirections1_Register:
	.string "מר פוקימון גר קצת אחרי צ'ריגרוב,\n"
	.string "העיר הבאה בדרך.\p"
	.string "הדרך לשם כמעט ישרה,\n"
	.string "כך שאי אפשר לפספס.\p"
	.string "אבל ליתר ביטחון, הנה מספר הטלפון שלי.\n"
	.string "תתקשר אליי אם יקרה משהו!$"

NewBarkTown_Lab_Text_RegisteredElm:
	.string "רשמת את פרופ' אלם\n"
	.string "בפוקיגיר.$"


NewBarkTown_Lab_Text_ElmLetYourMonBattle:
	.string "If a wild POKéMON appears,\n"
	.string "let your POKéMON battle it!$"

NewBarkTown_Lab_Text_ElmDirections2:
	.string "אם יופיע פוקימון פראי,\n"
	.string "תן לפוקימון שלך להילחם בו!\p"
	.string "אם הפוקימון שלך נפגע, כדאי לרפא אותו\n"
	.string "במכונה שמימיני או במרכז הפוקימון.\p"
	.string "אני סומך עליך!$"

NewBarkTown_Lab_Text_GotElmsNumber:
	.string "{PLAYER} got ELM's phone\n"
	.string "number.$"

NewBarkTown_Lab_Text_ElmDescribesMrPokemon:
	.string "MR. POKéMON goes everywhere and\n"
	.string "finds rarities.\p"
	.string "Too bad they're just rare and\n"
	.string "not very useful…$"

NewBarkTown_Lab_Text_ElmPokeBall:
	.string "It contains a POKéMON caught\n"
	.string "by PROF.ELM.$"

@THEFT================================================================================

NewBarkTown_Lab_Text_ElmAfterTheft1:
	.string "אלם: {PLAYER}, זה נורא…\p"
	.string "אה, נכון, מה הייתה התגלית\n"
	.string "הגדולה של מר פוקימון?$"

NewBarkTown_Lab_Text_ElmAfterTheft2:
	.string "{PLAYER} מסר את הביצה המסתורית\n"
	.string "לפרופ' אלם.$"

NewBarkTown_Lab_Text_ElmAfterTheft3:
	.string "אלם: זה?$"

NewBarkTown_Lab_Text_ElmAfterTheft4:
	.string "אבל… זו ביצת פוקימון?\p"
	.string "אם כן, זו תגלית\n"
	.string "גדולה!\p"
	.string "אלם: מה?!?\p"
	.string "פרופ' אוק נתן לך פוקדקס?\p"
	.string "{PLAYER}, זה נכון?\n"
	.string "ז-זה מדהים!\p"
	.string "הוא מצטיין בזיהוי הפוטנציאל\n"
	.string "של אנשים כמאמנים.\p"
	.string "וואו, {PLAYER}. אולי יש לך\n"
	.string "את מה שצריך כדי להפוך לאלוף.\p"
	.string "נראה שאתה גם מסתדר\n"
	.string "מצוין עם פוקימונים.\p"
	.string "כדאי לך לקחת על עצמך\n"
	.string "את אתגר מכוני הפוקימון.\p"
	.string "המכון הקרוב ביותר נמצא\n"
	.string "בעיר ויולט.\p"
	.string "…{PLAYER}. הדרך לאליפות\n"
	.string "תהיה ארוכה.\p"
	.string "לפני שאתה יוצא, תקפיד\n"
	.string "לדבר עם אמא שלך.$"

NewBarkTown_Lab_Text_ElmStudyingEgg:
	.string "אלם: אל תוותר!\n"
	.string "אתקשר אם אגלה משהו על הביצה הזאת!$"

NewBarkTown_Lab_Text_ElmAideHasEgg:
	.string "ELM: {PLAYER}? Didn't you meet\n"
	.string "my assistant?\p"
	.string "He should have met you with\n"
	.string "the EGG at VIOLET CITY's\p"
	.string "POKéMON CENTER.\p"
	.string "You must have just missed him.\n"
	.string "Try to catch him there.$"

NewBarkTown_Lab_Text_ElmWaitingEggHatch:
	.string "אלם: היי, הביצה הזאת\n"
	.string "השתנתה בכלל?$"

NewBarkTown_Lab_Text_ElmThoughtEggHatched:
	.string "{PLAYER}? I thought the EGG\n"
	.string "hatched.\p"
	.string "Where is the POKéMON?$"

NewBarkTown_Lab_Text_ShowTogepi1:
	.string "אלם: {PLAYER}, אתה נראה נהדר!$"

NewBarkTown_Lab_Text_ShowTogepi2:
	.string "מה? הפוקימון הזה!?!$"

NewBarkTown_Lab_Text_ShowTogepi3:
	.string "הביצה בקעה! אז פוקימונים\n"
	.string "נולדים מביצים…\p"
	.string "לא, אולי לא כל הפוקימונים.\p"
	.string "וואו, יש עוד\n"
	.string "הרבה מחקר לעשות.$"

NewBarkTown_Lab_Text_ElmGiveEverstone1:
	.string "תודה, {PLAYER}! אתה עוזר לנו\n"
	.string "לפענח את תעלומות הפוקימונים!\p"
	.string "אני רוצה שתקבל את זה\n"
	.string "כאות הוקרה מאיתנו.$"

NewBarkTown_Lab_Text_ElmGiveEverstone2:
	.string "זו אבן נצח.\p"
	.string "יש פוקימונים שמתפתחים\n"
	.string "כשהם מגיעים לרמה מסוימת.\p"
	.string "פוקימון שמחזיק אבן נצח\n"
	.string "לא יתפתח.\p"
	.string "כדאי לתת אותה לפוקימון שאתה\n"
	.string "לא רוצה שיתפתח.$"

NewBarkTown_Lab_Text_ElmCallYou:
	.string "ELM: {PLAYER}, I'll call you if\n"
	.string "anything comes up.$"

NewBarkTown_Lab_Text_AideAfterTheft:
	.string "…sigh… That stolen POKéMON.\p"
	.string "I wonder how it's doing.\p"
	.string "They say a POKéMON raised by a\n"
	.string "bad person turns bad itself.$"

NewBarkTown_Lab_Text_ElmGiveMasterBall1:
	.string "אלם: היי, {PLAYER}!\p"
	.string "בזכותך, המחקר שלי\n"
	.string "מתקדם מצוין!\p"
	.string "קח את זה\n"
	.string "כאות הוקרה ממני.$"

NewBarkTown_Lab_Text_ElmGiveMasterBall2:
	.string "המאסטר בול הוא הכי טוב!\p"
	.string "זה הכדור האולטימטיבי!\n"
	.string "הוא יתפוס כל פוקימון בלי לפספס.\p"
	.string "נותנים אותו רק לחוקרי\n"
	.string "פוקימונים מוסמכים.\p"
	.string "אני חושב שאתה תנצל אותו\n"
	.string "הרבה יותר טוב ממני, {PLAYER}!$"

NewBarkTown_Lab_Text_KimonoGirls:
	.string "דרך אגב… קבוצה של נערות קימונו\n"
	.string "יפהפיות חיפשה אותך.\p"
	.string "הן אמרו לי שהן מחכות לך\n"
	.string "בתיאטרון המחול של אקרוטיק.\p"
	.string "אני יודע שעברת הרבה מאז\n"
	.string "שהביצה ההיא סיבכה אותך בכל זה…\p"
	.string "אני מקווה שתמשיך עד הסוף.$"

NewBarkTown_Lab_Text_KimonoWaiting:
	.string "פרופ' אלם: נערות הקימונו מחכות לך\n"
	.string "בתיאטרון המחול של אקרוטיק.$"

NewBarkTown_Lab_Text_League:
	.string "פרופ' אלם: חה חה חה…\n"
	.string "כל הכבוד!\p"
	.string "הביצה הנדירה ההיא הביאה לך\n"
	.string "הרבה צרות, הא?\p"
	.string "נערות הקימונו אמרו משהו\n"
	.string "עליי?\p"
	.string "אין לי שום קשר לזה.\p"
	.string "אתה קיבלת את ההחלטה\n"
	.string "ועמדת בה.\p"
	.string "אחרי כל מה שעשית, אתה אמור\n"
	.string "להיות מוכן לליגה עכשיו!\p"
	.string "כדאי לך לצאת\n"
	.string "לרמת אינדיגו!\p"
	.string "אתה יודע איך מגיעים לשם?\n"
	.string "ממשיכים בדרך 27 עד דרך 26.\p"
	.string "משם, ישר צפונה!$"


NewBarkTown_Lab_Text_ElmGiveTicket1:
	.string "אלם: {PLAYER}! הנה אתה!\p"
	.string "התקשרתי כי יש לי\n"
	.string "משהו בשבילך.\p"
	.string "רואה? זה כרטיס ס.ס.\p"
	.string "עכשיו תוכל לתפוס פוקימונים\n"
	.string "בקאנטו.$"

NewBarkTown_Lab_Text_ElmGiveTicket2:
	.string "הספינה יוצאת\n"
	.string "מהעיר אוליבין.\p"
	.string "אבל אתה כבר יודע את זה,\n"
	.string "{PLAYER}.\p"
	.string "אחרי הכול, טיילת בכל מקום\n"
	.string "עם הפוקימונים שלך.\p"
	.string "תמסור דרישת שלום לפרופ' אוק\n"
	.string "בקאנטו!$"

NewBarkTown_Lab_Text_LabMonEgg:
	.string "It's the POKéMON EGG being\n"
	.string "studied by PROF.ELM.$"

NewBarkTown_Lab_Text_AideGivePotion:
	.string "{PLAYER}, אני רוצה שתיקח\n"
	.string "את זה לשליחות שלך.$"

NewBarkTown_Lab_Text_AideAlwaysBusy:
	.string "אנחנו רק שלושה, אז\n"
	.string "אנחנו תמיד עסוקים.$"

NewBarkTown_Lab_Text_AideSave:
	.string "לא לשכוח לשמור את המשחק\n"
	.string "באופן קבוע!\p"
	.string "לוחצים על כפתור START,\n"
	.string "ואז בוחרים ב”שמירה”!$"

NewBarkTown_Lab_Text_AideTheftTestimony:
	.string "היה רעש חזק\n"
	.string "בחוץ…\p"
	.string "כשיצאנו לבדוק, התברר שמישהו\n"
	.string "גנב פוקימון.\p"
	.string "לא ייאמן שמישהו\n"
	.string "מסוגל לעשות דבר כזה!\p"
	.string "…אנחה… הפוקימון שנגנב.\p"
	.string "מעניין מה שלומו.\p"
	.string "אומרים שפוקימון שגדל אצל\n"
	.string "אדם רע הופך לרע בעצמו.$"

NewBarkTown_Lab_Text_AideGiveBalls:
	.string "{PLAYER}!\p"
	.string "קח את אלה למסע\n"
	.string "הפוקדקס שלך!$"

NewBarkTown_Lab_Text_AideExplainBalls:
	.string "To add to your POKéDEX, you\n"
	.string "have to catch POKéMON.\p"
	.string "Throw POKé BALLS at wild\n"
	.string "POKéMON to get them.$"

NewBarkTown_Lab_Text_Officer1:
	.string "שמעתי שנגנב כאן\n"
	.string "פוקימון…\p"
	.string "בדיוק קיבלתי קצת\n"
	.string "מידע מפרופ' אלם.\p"
	.string "כנראה מדובר בבחור צעיר\n"
	.string "עם שיער אדום וארוך…\p"
	.string "מה?\p"
	.string "נלחמת במאמן כזה?\p"
	.string "במקרה יצא לך לשמוע\n"
	.string "את השם שלו?$"

NewBarkTown_Lab_Text_Officer2_1:
	.string "אוקיי! אז קוראים לו {RIVAL}?$"

NewBarkTown_Lab_Text_Officer2:
	.string "תודה על העזרה\n"
	.string "בחקירה שלי!$"

NewBarkTown_Lab_Text_OfficerNo:
	.string "בטח שמעת את השם שלו?!$"

NewBarkTown_Lab_Text_Elm_CallMe:
	.string "אה, {PLAYER}!\p"
	.string "איך מתקדם הפוקדקס שלך?\p"
	.string "אני עסוק עכשיו, אבל תתקשר מתישהו\n"
	.string "ואוכל לבדוק את ההתקדמות שלך!$"
