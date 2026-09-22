BattleFrontier_BattlePalaceLobby_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePalaceLobby_OnFrame_hns
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePalaceLobby_OnWarp_hns
	.byte 0

BattleFrontier_BattlePalaceLobby_OnWarp_hns:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePalaceLobby_EventScript_TurnPlayerNorth_hns
	.2byte 0

BattleFrontier_BattlePalaceLobby_EventScript_TurnPlayerNorth_hns::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePalaceLobby_OnFrame_hns:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattlePalaceLobby_EventScript_GetChallengeStatus_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePalaceLobby_EventScript_QuitWithoutSaving_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePalaceLobby_EventScript_ResumeChallenge_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattlePalaceLobby_EventScript_WonChallenge_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePalaceLobby_EventScript_LostChallenge_hns
	.2byte 0

BattleFrontier_BattlePalaceLobby_EventScript_GetChallengeStatus_hns::
	frontier_getstatus
	end

BattleFrontier_BattlePalaceLobby_EventScript_QuitWithoutSaving_hns::
	lockall
	msgbox BattleFrontier_BattlePalaceLobby_Text_FailedToSaveBeforeEndingChallenge_hns, MSGBOX_DEFAULT
	closemessage
	palace_set PALACE_DATA_WIN_STREAK, 0
	palace_set PALACE_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_WonChallenge_hns::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePalaceLobby_EventScript_DefeatedMaven_hns
	msgbox BattleFrontier_BattlePalaceLobby_Text_FirmTrueBondsFor7WinStreak_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_GiveBattlePoints_hns

BattleFrontier_BattlePalaceLobby_EventScript_DefeatedMaven_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ToDefeatMavenAnd7Trainers_hns, MSGBOX_DEFAULT
BattleFrontier_BattlePalaceLobby_EventScript_GiveBattlePoints_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_PresentYouWithBattlePoints_hns, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattlePalaceLobby_Text_FeatWillBeRecorded_hns
	waitmessage
	call BattleFrontier_BattlePalaceLobby_EventScript_SaveAfterChallenge_hns
	msgbox BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified_hns, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_LostChallenge_hns::
	lockall
	message BattleFrontier_BattlePalaceLobby_Text_ResultsWillBeRecorded_hns
	waitmessage
	palace_set PALACE_DATA_WIN_STREAK_ACTIVE, FALSE
	call BattleFrontier_BattlePalaceLobby_EventScript_SaveAfterChallenge_hns
	msgbox BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified_hns, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_SaveAfterChallenge_hns::
	frontier_checkairshow
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	palace_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge_hns
	message BattleFrontier_BattlePalaceLobby_Text_LikeToRecordMatch_hns
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge_hns
	case 0, BattleFrontier_BattlePalaceLobby_EventScript_RecordMatch_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge_hns

BattleFrontier_BattlePalaceLobby_EventScript_RecordMatch_hns::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattlePalaceLobby_EventScript_EndSaveAfterChallenge_hns::
	return

BattleFrontier_BattlePalaceLobby_EventScript_ResumeChallenge_hns::
	lockall
	msgbox BattleFrontier_BattlePalaceLobby_Text_WeHaveBeenWaiting_hns, MSGBOX_DEFAULT
	message BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge_hns
	waitmessage
	palace_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto BattleFrontier_BattlePalaceLobby_EventScript_EnterChallenge_hns

BattleFrontier_BattlePalaceLobby_EventScript_SinglesAttendant_hns::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PALACE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto BattleFrontier_BattlePalaceLobby_EventScript_Attendant_hns
	end

BattleFrontier_BattlePalaceLobby_EventScript_DoublesAttendant_hns::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PALACE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto BattleFrontier_BattlePalaceLobby_EventScript_Attendant_hns
	end

BattleFrontier_BattlePalaceLobby_EventScript_Attendant_hns::
	palace_get PALACE_DATA_PRIZE
	goto_if_ne VAR_RESULT, ITEM_NONE, BattleFrontier_BattlePalaceLobby_EventScript_WonChallenge_hns
	special SavePlayerParty
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForSingleBattle_hns
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForDoubleBattle_hns
BattleFrontier_BattlePalaceLobby_EventScript_AskTakeChallenge_hns::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_AskTakeSingleBattleChallenge_hns
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_AskTakeDoubleBattleChallenge_hns
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePalaceLobby_EventScript_TryEnterChallenge_hns
	case 1, BattleFrontier_BattlePalaceLobby_EventScript_ExplainChallenge_hns
	case 2, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge_hns

BattleFrontier_BattlePalaceLobby_EventScript_TryEnterChallenge_hns::
	message BattleFrontier_BattlePalaceLobby_Text_WhichChallenge_hns
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge_hns
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMons_hns
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePalaceLobby_Text_NowSelectThreeMons_hns, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge_hns
	msgbox BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge_hns2_hns, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge_hns
	case YES, BattleFrontier_BattlePalaceLobby_EventScript_SaveBeforeChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge_hns

BattleFrontier_BattlePalaceLobby_EventScript_SaveBeforeChallenge_hns::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	palace_init
	palace_set PALACE_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge_hnsSaveFailed_hns
BattleFrontier_BattlePalaceLobby_EventScript_EnterChallenge_hns::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePalaceLobby_Text_FollowMe_hns, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_BattlePalaceLobby_EventScript_WalkToDoor_hns
	warp MAP_BATTLE_FRONTIER_BATTLE_PALACE_CORRIDOR_HNS, 8, 13
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattlePalaceLobby_EventScript_ExplainChallenge_hns::
	goto_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_ExplainDoublesChallenge_hns
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainSingleBattleChallenge_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_AskTakeChallenge_hns

BattleFrontier_BattlePalaceLobby_EventScript_ExplainDoublesChallenge_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainDoubleBattleChallenge_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_AskTakeChallenge_hns

BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMons_hns::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMons_hnsLv50_hns
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMons_hnsLvOpen_hns

BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMons_hnsLv50_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLv50_hns, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsEnd_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_EndCancelChallenge_hns

BattleFrontier_BattlePalaceLobby_EventScript_NotEnoughValidMons_hnsLvOpen_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLvOpen_hns, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsEnd_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_EndCancelChallenge_hns

BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge_hnsSaveFailed_hns::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge_hns

BattleFrontier_BattlePalaceLobby_EventScript_LoadPartyAndCancelChallenge_hns::
	special LoadPlayerParty
	callnative LoadPlayerParty
BattleFrontier_BattlePalaceLobby_EventScript_CancelChallenge_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified_hns, MSGBOX_DEFAULT
BattleFrontier_BattlePalaceLobby_EventScript_EndCancelChallenge_hns::
	release
	end

BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForSingleBattle_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_WelcomeForSingleBattle_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceLobby_EventScript_WelcomeForDoubleBattle_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_WelcomeForDoubleBattle_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePalaceLobby_EventScript_AskTakeSingleBattleChallenge_hns::
	message BattleFrontier_BattlePalaceLobby_Text_TakeSingleBattleChallenge_hns
	return

BattleFrontier_BattlePalaceLobby_EventScript_AskTakeDoubleBattleChallenge_hns::
	message BattleFrontier_BattlePalaceLobby_Text_TakeDoubleBattleChallenge_hns
	return

BattleFrontier_BattlePalaceLobby_EventScript_WalkToDoor_hns::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_TalkedToSinglesAttendant_hns
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_TalkedToDoublesAttendant_hns
	applymovement VAR_LAST_TALKED, BattleFrontier_BattlePalaceLobby_Movement_WalkToDoor_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceLobby_Movement_WalkToDoor_hns
	waitmovement 0
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_OpenSinglesHallDoor_hns
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_OpenDoublesHallDoor_hns
	waitdooranim
	applymovement VAR_LAST_TALKED, BattleFrontier_BattlePalaceLobby_Movement_AttendantEnterDoor_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePalaceLobby_Movement_PlayerEnterDoor_hns
	waitmovement 0
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattlePalaceLobby_EventScript_CloseSinglesHallDoor_hns
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattlePalaceLobby_EventScript_CloseDoublesHallDoor_hns
	waitdooranim
	return

BattleFrontier_BattlePalaceLobby_EventScript_TalkedToSinglesAttendant_hns::
	setvar VAR_LAST_TALKED, LOCALID_PALACE_ATTENDANT_SINGLES
	return

BattleFrontier_BattlePalaceLobby_EventScript_TalkedToDoublesAttendant_hns::
	setvar VAR_LAST_TALKED, LOCALID_PALACE_ATTENDANT_DOUBLES
	return

BattleFrontier_BattlePalaceLobby_EventScript_OpenSinglesHallDoor_hns::
	opendoor 5, 4
	return

BattleFrontier_BattlePalaceLobby_EventScript_OpenDoublesHallDoor_hns::
	opendoor 19, 4
	return

BattleFrontier_BattlePalaceLobby_EventScript_CloseSinglesHallDoor_hns::
	closedoor 5, 4
	return

BattleFrontier_BattlePalaceLobby_EventScript_CloseDoublesHallDoor_hns::
	closedoor 19, 4
	return

BattleFrontier_BattlePalaceLobby_Movement_WalkToDoor_hns:
	walk_up
	step_end

BattleFrontier_BattlePalaceLobby_Movement_AttendantEnterDoor_hns:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePalaceLobby_Movement_PlayerEnterDoor_hns:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePalaceLobby_EventScript_ShowSinglesResults_hns::
	lockall
	frontier_results FRONTIER_FACILITY_PALACE, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_ShowDoublesResults_hns::
	lockall
	frontier_results FRONTIER_FACILITY_PALACE, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePalaceLobby_EventScript_BlackBelt_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_LadyCanTellWhatMonsThink_hns, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_Man_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_NatureAndMovesKeyHere_hns, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_Beauty_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_MonDocileButTransforms_hns, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_Maniac_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_WhatNatureFavorsChippingAway_hns, MSGBOX_NPC
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesBoard_hns::
	lockall
	msgbox BattleFrontier_BattlePalaceLobby_Text_RulesAreListed_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard_hns::
	message BattleFrontier_BattlePalaceLobby_Text_ReadWhichHeading_hns
	waitmessage
	multichoice 16, 0, MULTI_BATTLE_PALACE_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePalaceLobby_EventScript_RulesBasics_hns
	case 1, BattleFrontier_BattlePalaceLobby_EventScript_RulesNature_hns
	case 2, BattleFrontier_BattlePalaceLobby_EventScript_RulesMoves_hns
	case 3, BattleFrontier_BattlePalaceLobby_EventScript_RulesUnderpowered_hns
	case 4, BattleFrontier_BattlePalaceLobby_EventScript_RulesWhenInDanger_hns
	case 5, BattleFrontier_BattlePalaceLobby_EventScript_ExitRules_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePalaceLobby_EventScript_ExitRules_hns
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesBasics_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesBasics_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesNature_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesNature_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesMoves_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesMoves_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesUnderpowered_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesUnderpowered_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePalaceLobby_EventScript_RulesWhenInDanger_hns::
	msgbox BattleFrontier_BattlePalaceLobby_Text_ExplainRulesWhenInDanger_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePalaceLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePalaceLobby_EventScript_ExitRules_hns::
	releaseall
	end

BattleFrontier_BattlePalaceLobby_Text_WelcomeForSingleBattle_hns:
	.string "Donde el corazón de los ENTRENADORES\n"
	.string "se pone a prueba.\p"
	.string "Bienvenidos al PALACIO BATALLA.\p"
	.string "Acepto retos en las SALAS DE\n"
	.string "BATALLA INDIVIDUAL.$"

BattleFrontier_BattlePalaceLobby_Text_TakeSingleBattleChallenge_hns:
	.string "¿Quieres aceptar el reto de la\n"
	.string "SALA DE BATALLA INDIVIDUAL?$"

BattleFrontier_BattlePalaceLobby_Text_ExplainSingleBattleChallenge_hns:
	.string "En el PALACIO BATALLA hay\n"
	.string "varios auditorios de BATALLAS\l"
	.string "llamados SALAS DE BATALLA INDIV.\p"
	.string "Las BATALLAS INDIVIDUALES son\n"
	.string "como siempre, salvo un detalle clave\l"
	.string "regla que debe obedecerse.\p"
	.string "Los ENTRENADORES solo pueden cambiar\n"
	.string "sus POKéMON.\p"
	.string "De lo contrario, tienen prohibido\n"
	.string "dar órdenes a sus POKéMON.\p"
	.string "Los POKéMON actuarán según su\n"
	.string "naturaleza y lucharán por su cuenta.\p"
	.string "Debes confiar en tus POKéMON\n"
	.string "y vigilarlos.\p"
	.string "Si logras el honor de ganar el\n"
	.string "siete ENTRENADORES seguidos,\l"
	.string "reto, te daremos Puntos de Batalla.\p"
	.string "Si quieres interrumpir tu\n"
	.string "desafío, debes guardar la partida.\p"
	.string "Si no guardas antes de interrumpir,\n"
	.string "quedarás descalificado.$"

BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified_hns:
	.string "Cuando hayas fortalecido tu corazón\n"
	.string "y a tus POKéMON, debes volver.$"

BattleFrontier_BattlePalaceLobby_Text_WhichChallenge_hns:
	.string "Hay dos BATTLE HALLS,\n"
	.string "Nivel 50 y Nivel Abierto.\l"
	.string "¿Cuál desafío eliges?$"

BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLv50_hns:
	.string "Suspiro...\p"
	.string "No tienes los tres POKéMON\n"
	.string "necesarios para el desafío.\p"
	.string "Para entrar, debes traer tres\n"
	.string "tipos distintos de POKéMON.\p"
	.string "Estos POKéMON deben ser todos de\n"
	.string "Nivel 50 o inferior.\p"
	.string "Tampoco deben llevar puestos\n"
	.string "el mismo tipo de objetos.\p"
	.string "HUEVOS{STR_VAR_1}.$"

BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsEnd_hns:
	.string "Vuelve cuando hayas hecho\n"
	.string "tus preparativos.$"

BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLvOpen_hns:
	.string "Suspiro...\p"
	.string "No tienes los tres POKéMON\n"
	.string "necesarios para el desafío.\p"
	.string "Para entrar, debes traer tres\n"
	.string "tipos distintos de POKéMON.\p"
	.string "Tampoco deben llevar puestos\n"
	.string "el mismo tipo de objetos.\p"
	.string "HUEVOS{STR_VAR_1}.$"

BattleFrontier_BattlePalaceLobby_Text_NowSelectThreeMons_hns:
	.string "Bien. Ahora, debes elegir a tus\n"
	.string "tres POKéMON.$"

BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge_hns2_hns:
	.string "Debo guardar antes de llevarte al\n"
	.string "BATTLE HALL. ¿Está bien?$"

BattleFrontier_BattlePalaceLobby_Text_FollowMe_hns:
	.string "Bien.\n"
	.string "Ahora, sígueme.$"

BattleFrontier_BattlePalaceLobby_Text_ResultsWillBeRecorded_hns:
	.string "Me siento honrado de haber visto\n"
	.string "las hazañas de tus POKéMON.\p"
	.string "Los resultados se registrarán.\n"
	.string "Te pido que esperes un momento.$"

BattleFrontier_BattlePalaceLobby_Text_FirmTrueBondsFor7WinStreak_hns:
	.string "Para lograr 7 victorias seguidas...\p"
	.string "Los vínculos que unen tu corazón\n"
	.string "con tu POKéMON parecen fuertes.$"

BattleFrontier_BattlePalaceLobby_Text_FeatWillBeRecorded_hns:
	.string "Tu hazaña será registrada.\n"
	.string "Te pido que esperes un momento.$"

@ Unused
BattleFrontier_BattlePalaceLobby_Text_BattlePointsFor7WinStreak_hns:
	.string "Por tu racha de 7 victorias,\n"
	.string "te damos Puntos de Batalla.$"

BattleFrontier_BattlePalaceLobby_Text_NoSpaceForPrize_hns:
	.string "Parece que no tienes espacio para\n"
	.string "nuestro premio.\p"
	.string "Vuelve cuando hayas organizado\n"
	.string "tu MOCHILA.$"

BattleFrontier_BattlePalaceLobby_Text_WeHaveBeenWaiting_hns:
	.string "Te estábamos esperando...$"

BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge_hns:
	.string "Debo guardar antes de llevarte al\n"
	.string "BATTLE HALL. ¿Está bien?$"

BattleFrontier_BattlePalaceLobby_Text_FailedToSaveBeforeEndingChallenge_hns:
	.string "Suspiro...\p"
	.string "No guardaste antes de terminar\n"
	.string "tu desafío la última vez.\p"
	.string "Como resultado, tu desafío ha sido\n"
	.string "descalificado. Es lamentable.$"

@ Unused
BattleFrontier_BattlePalaceLobby_Text_ReceivedPrize_hns:
	.string "{PLAYER} recibió el premio\n"
	.string "{STR_VAR_1}.$"

BattleFrontier_BattlePalaceLobby_Text_LadyCanTellWhatMonsThink_hns:
	.string "Para alguien fuerte como yo,\n"
	.string "los POKéMON fuertes son los mejores.\p"
	.string "¡Atacar es la mejor defensa!\n"
	.string "¡Un ataque constante es lo máximo!\p"
	.string "Pero de eso no es de lo que quería\n"
	.string "hablar.\p"
	.string "De vez en cuando, una chica muy linda\n"
	.string "pasa por aquí.\p"
	.string "Dice que ella puede saber qué\n"
	.string "Los POKéMON están pensando.\p"
	.string "No sé mucho sobre esa parte,\n"
	.string "pero ella es muy linda.\p"
	.string "¿Eh?\n"
	.string "¿Por qué me miras así?$"

BattleFrontier_BattlePalaceLobby_Text_NatureAndMovesKeyHere_hns:
	.string "Hmm...\p"
	.string "Parece que la naturaleza del POKéMON\n"
	.string "y los movimientos que ha\l"
	.string "aprendido son la clave aquí.\p"
	.string "Para ser precisos, es qué tan bien\n"
	.string "encajan los movimientos con la\l"
	.string "naturaleza del POKéMON.\p"
	.string "Si tu POKéMON tiene problemas y\n"
	.string "no puede dar todo su potencial,\l"
	.string "deberías examinar qué tan bien\l"
	.string "sus movimientos van con su naturaleza.$"

BattleFrontier_BattlePalaceLobby_Text_MonDocileButTransforms_hns:
	.string "Mi POKéMON suele ser muy dócil.\p"
	.string "Pero cuando está en el BATTLE HALL,\n"
	.string "¡a veces parece transformarse\l"
	.string "en algo malvado!\p"
	.string "Se vuelve totalmente intimidante.\n"
	.string "Es hasta impactante.$"

BattleFrontier_BattlePalaceLobby_Text_WhatNatureFavorsChippingAway_hns:
	.string "Me pregunto qué naturaleza tendría\n"
	.string "un POKéMON que prefiera debilitar\l"
	.string "al rival y desgastarlo lentamente.\p"
	.string "Me sorprendería que fuera LAX.\p"
	.string "Pero no, eso no puede estar bien.$"

BattleFrontier_BattlePalaceLobby_Text_WelcomeForDoubleBattle_hns:
	.string "Donde el corazón de los ENTRENADORES\n"
	.string "se pone a prueba.\p"
	.string "Bienvenidos al PALACIO BATALLA.\p"
	.string "Acepto retos de DOBLE\n"
	.string "BATALLA INDIVIDUAL.$"

BattleFrontier_BattlePalaceLobby_Text_TakeDoubleBattleChallenge_hns:
	.string "¿Quieres aceptar el reto de la\n"
	.string "¿el reto del SALÓN DE BATALLA DOBLE?$"

BattleFrontier_BattlePalaceLobby_Text_ExplainDoubleBattleChallenge_hns:
	.string "En el PALACIO BATALLA hay\n"
	.string "varios auditorios para BATALLAS DOBLES\l"
	.string "llamados SALONES DE BATALLA DOBLE.\p"
	.string "Las BATALLAS DOBLES se hacen en\n"
	.string "como siempre, salvo un detalle clave\l"
	.string "regla que debe obedecerse.\p"
	.string "Los ENTRENADORES solo pueden cambiar\n"
	.string "sus POKéMON.\p"
	.string "De lo contrario, tienen prohibido\n"
	.string "dar órdenes a sus POKéMON.\p"
	.string "Los POKéMON actuarán según su\n"
	.string "naturaleza y lucharán por su cuenta.\p"
	.string "Debes confiar en tus POKéMON\n"
	.string "y vigilarlos.\p"
	.string "Si logras el honor de ganar el\n"
	.string "siete ENTRENADORES seguidos,\l"
	.string "reto, te daremos Puntos de Batalla.\p"
	.string "Si quieres interrumpir tu\n"
	.string "Antes del reto, guarda la partida.\p"
	.string "Si no guardas antes de interrumpir,\n"
	.string "quedarás descalificado.$"

BattleFrontier_BattlePalaceLobby_Text_ToDefeatMavenAnd7Trainers_hns:
	.string "Para vencer al EXPERTO DEL PALACIO\n"
	.string "y a siete ENTRENADORES seguidos...$"

BattleFrontier_BattlePalaceLobby_Text_PresentYouWithBattlePoints_hns:
	.string "En honor al vínculo que compartes con\n"
	.string "tus POKéMON, te entregamos\l"
	.string "estos Puntos de Batalla.$"

BattleFrontier_BattlePalaceLobby_Text_LikeToRecordMatch_hns:
	.string "¿Quieres grabar tu última\n"
	.string "combate del PALACIO DE BATALLA en tu\l"
	.string "BATALLA en tu PASA FRONTERA?$"

BattleFrontier_BattlePalaceLobby_Text_RulesAreListed_hns:
	.string "Se listan las reglas de SALA BATALLA.$"

BattleFrontier_BattlePalaceLobby_Text_ReadWhichHeading_hns:
	.string "¿Qué apartado quieres leer?$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesBasics_hns:
	.string "Aquí, los POKéMON deben pensar\n"
	.string "y luchar por su cuenta.\p"
	.string "A diferencia de los salvajes, los\n"
	.string "POKéMON que viven con personas\l"
	.string "actúan según su naturaleza.$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesNature_hns:
	.string "Según su naturaleza, un POKéMON\n"
	.string "podría preferir atacar siempre.\p"
	.string "Otro POKéMON podría preferir\n"
	.string "protegerse de cualquier daño.\p"
	.string "Y otro podría disfrutar molestando\n"
	.string "o confundiendo a sus rivales.\p"
	.string "Por su naturaleza, un POKéMON\n"
	.string "tendrá movimientos favoritos que\l"
	.string "sabrá usar mejor.\p"
	.string "También puede haber movimientos que\n"
	.string "le cuesten más trabajo usar.$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesMoves_hns:
	.string "Hay movimientos ofensivos que\n"
	.string "causan daño directo al rival.\p"
	.string "Hay movimientos defensivos que\n"
	.string "sirven para prepararse ante ataques\l"
	.string "o para recuperar PS y más.\p"
	.string "También hay otros movimientos\n"
	.string "extraños que pueden debilitar al rival\l"
	.string "problemas de estado como veneno y \l"
	.string "parálisis.\p"
	.string "El POKéMON considerará usar ataques\n"
	.string "de estas tres categorías.$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesUnderpowered_hns:
	.string "Si no recibe órdenes de su ENTRENADOR,\n"
	.string "un POKéMON podría no ser capaz de\l"
	.string "usar ciertos ataques.\p"
	.string "Un POKéMON no es bueno usando\n"
	.string "ataques que no le gustan.\p"
	.string "Si un POKéMON solo sabe ataques que\n"
	.string "no van con su naturaleza, a menudo\l"
	.string "no alcanzará todo su potencial.$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesWhenInDanger_hns:
	.string "Según su naturaleza, un POKéMON\n"
	.string "puede usar movimientos que no\l"
	.string "van con su naturaleza al sufrir.\p"
	.string "Si un POKéMON actúa extraño\n"
	.string "en un apuro, obsérvalo bien.$"

