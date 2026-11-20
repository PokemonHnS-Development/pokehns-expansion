BattleFrontier_BattleDomeLobby_hns_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleDomeLobby_OnResume_hns
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleDomeLobby_OnFrame_hns
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleDomeLobby_OnWarp_hns
	.byte 0

BattleFrontier_BattleDomeLobby_OnResume_hns:
	dome_initresultstree
	end

BattleFrontier_BattleDomeLobby_OnWarp_hns:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleDomeLobby_EventScript_TurnPlayerNorth_hns
	.2byte 0

BattleFrontier_BattleDomeLobby_EventScript_TurnPlayerNorth_hns::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleDomeLobby_OnFrame_hns:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattleDomeLobby_EventScript_GetChallengeStatus_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleDomeLobby_EventScript_QuitWithoutSaving_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleDomeLobby_EventScript_ResumeChallenge_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattleDomeLobby_EventScript_WonChallenge_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattleDomeLobby_EventScript_LostChallenge_hns
	.2byte 0

BattleFrontier_BattleDomeLobby_EventScript_GetChallengeStatus_hns::
	frontier_getstatus
	end

BattleFrontier_BattleDomeLobby_EventScript_QuitWithoutSaving_hns::
	lockall
	msgbox BattleFrontier_BattleDomeLobby_Text_DidntSaveBeforeQuitting_hns, MSGBOX_DEFAULT
	closemessage
	dome_set DOME_DATA_WIN_STREAK, 0
	dome_set DOME_DATA_WIN_STREAK_ACTIVE, FALSE
	dome_set DOME_DATA_ATTEMPTED_CHALLENGE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleDomeLobby_EventScript_WonChallenge_hns::
	call BattleFrontier_EventScript_IncrementWinStreak
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleDomeLobby_EventScript_DefeatedAce_hns
	msgbox BattleFrontier_BattleDomeLobby_Text_CongratsForWinningTourney_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_GiveBattlePoints_hns

BattleFrontier_BattleDomeLobby_EventScript_DefeatedAce_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_CongratsDefeatedTucker_hns, MSGBOX_DEFAULT
BattleFrontier_BattleDomeLobby_EventScript_GiveBattlePoints_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_AwardTheseBattlePoints_hns, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleDomeLobby_Text_RecordWillBeSaved_hns
	waitmessage
	special LoadPlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	frontier_checkairshow
	dome_set DOME_DATA_ATTEMPTED_CHALLENGE, TRUE
	dome_set DOME_DATA_HAS_WON_CHALLENGE, TRUE
	dome_set DOME_DATA_WIN_STREAK_ACTIVE, TRUE
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	goto BattleFrontier_BattleDomeLobby_EventScript_AskRecordBattle_hns

BattleFrontier_BattleDomeLobby_EventScript_LostChallenge_hns::
	lockall
	msgbox BattleFrontier_BattleDomeLobby_Text_ThankYouForPlaying_hns, MSGBOX_DEFAULT
	message BattleFrontier_BattleDomeLobby_Text_RecordWillBeSaved_hns
	waitmessage
	special LoadPlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	frontier_checkairshow
	dome_set DOME_DATA_WIN_STREAK_ACTIVE, FALSE
	dome_set DOME_DATA_ATTEMPTED_CHALLENGE, TRUE
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattleDomeLobby_EventScript_AskRecordBattle_hns::
	dome_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleDomeLobby_EventScript_EndChallenge_hns
	message BattleFrontier_BattleDomeLobby_Text_RecordLastMatch_hns
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleDomeLobby_EventScript_EndChallenge_hns
	case 0, BattleFrontier_BattleDomeLobby_EventScript_RecordBattle_hns
	case MULTI_B_PRESSED, BattleFrontier_BattleDomeLobby_EventScript_EndChallenge_hns

BattleFrontier_BattleDomeLobby_EventScript_RecordBattle_hns::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleDomeLobby_EventScript_EndChallenge_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_HopeToSeeYouAgain_hns, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleDomeLobby_EventScript_ResumeChallenge_hns::
	lockall
	msgbox BattleFrontier_BattleDomeLobby_Text_WeveBeenWaitingForYou_hns, MSGBOX_DEFAULT
	message BattleFrontier_BattleDomeLobby_Text_OkayToSaveBeforeChallenge_hns2_hns
	waitmessage
	dome_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto BattleFrontier_BattleDomeLobby_EventScript_EnterChallenge_hns

BattleFrontier_BattleDomeLobby_EventScript_SinglesAttendant_hns::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_DOME
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto BattleFrontier_BattleDomeLobby_EventScript_AttendantWelcome_hns
	end

BattleFrontier_BattleDomeLobby_EventScript_DoublesAttendant_hns::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_DOME
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto BattleFrontier_BattleDomeLobby_EventScript_AttendantWelcome_hns
	end

BattleFrontier_BattleDomeLobby_EventScript_AttendantWelcome_hns::
	special SavePlayerParty
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleDomeLobby_EventScript_WelcomeSingles_hns
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleDomeLobby_EventScript_WelcomeDoubles_hns
BattleFrontier_BattleDomeLobby_EventScript_AskTakeChallenge_hns::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleDomeLobby_EventScript_TakeSinglesChallenge_hns
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleDomeLobby_EventScript_TakeDoublesChallenge_hns
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleDomeLobby_EventScript_TryEnterChallenge_hns
	case 1, BattleFrontier_BattleDomeLobby_EventScript_ExplainChallenge_hns
	case 2, BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge_hns

BattleFrontier_BattleDomeLobby_EventScript_TryEnterChallenge_hns::
	message BattleFrontier_BattleDomeLobby_Text_WhichLevelMode_hns
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge_hns
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMons_hns
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleDomeLobby_Text_SelectThreeMons_hns, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleDomeLobby_EventScript_LoadPartyCancelChallenge_hns
	msgbox BattleFrontier_BattleDomeLobby_Text_OkayToSaveBeforeChallenge_hns, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleDomeLobby_EventScript_LoadPartyCancelChallenge_hns
	case YES, BattleFrontier_BattleDomeLobby_EventScript_SaveBeforeChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattleDomeLobby_EventScript_LoadPartyCancelChallenge_hns

BattleFrontier_BattleDomeLobby_EventScript_SaveBeforeChallenge_hns::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	dome_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge_hnsSaveFailed_hns
	dome_inittrainers
BattleFrontier_BattleDomeLobby_EventScript_EnterChallenge_hns::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	dome_settrainers
	msgbox BattleFrontier_BattleDomeLobby_Text_ShowYouToBattleDome_hns, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_BattleDomeLobby_EventScript_WalkToDoor_hns
	special HealPlayerParty
	warp MAP_BATTLE_FRONTIER_BATTLE_DOME_CORRIDOR_HNS, 23, 6
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattleDomeLobby_EventScript_ExplainChallenge_hns::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleDomeLobby_EventScript_ExplainSinglesChallenge_hns
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleDomeLobby_EventScript_ExplainDoublesChallenge_hns
	goto BattleFrontier_BattleDomeLobby_EventScript_AskTakeChallenge_hns

BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMons_hns::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMons_hnsLv50_hns
	case FRONTIER_LVL_OPEN, BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMons_hnsLvOpen_hns

BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMons_hnsLv50_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_NotEnoughValidMonsLv50_hns, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattleDomeLobby_Text_NotEnoughValidMonsEnd_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_EndCancelChallenge_hns

BattleFrontier_BattleDomeLobby_EventScript_NotEnoughValidMons_hnsLvOpen_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_NotEnoughValidMonsLvOpen_hns, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattleDomeLobby_Text_NotEnoughValidMonsEnd_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_EndCancelChallenge_hns

BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge_hnsSaveFailed_hns::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge_hns

BattleFrontier_BattleDomeLobby_EventScript_LoadPartyCancelChallenge_hns::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattleDomeLobby_EventScript_CancelChallenge_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_HopeToSeeYouAgain_hns, MSGBOX_DEFAULT
BattleFrontier_BattleDomeLobby_EventScript_EndCancelChallenge_hns::
	release
	end

BattleFrontier_BattleDomeLobby_EventScript_WalkToDoor_hns::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleDomeLobby_EventScript_SinglesAttendant_hnsWalkToDoor_hns
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleDomeLobby_EventScript_DoublesAttendant_hnsWalkToDoor_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattleDomeLobby_Movement_WalkToDoor_hns
	waitmovement 0
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleDomeLobby_EventScript_OpenSinglesDoor_hns
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleDomeLobby_EventScript_OpenDoublesDoor_hns
	waitdooranim
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleDomeLobby_EventScript_SinglesAttendant_hnsEnterDoor_hns
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleDomeLobby_EventScript_DoublesAttendant_hnsEnterDoor_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattleDomeLobby_Movement_PlayerEnterDoor_hns
	waitmovement 0
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleDomeLobby_EventScript_CloseSinglesDoor_hns
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleDomeLobby_EventScript_CloseDoublesDoor_hns
	waitdooranim
	return

BattleFrontier_BattleDomeLobby_EventScript_SinglesAttendant_hnsWalkToDoor_hns::
	applymovement LOCALID_DOME_ATTENDANT_SINGLES, BattleFrontier_BattleDomeLobby_Movement_WalkToDoor_hns
	return

BattleFrontier_BattleDomeLobby_EventScript_DoublesAttendant_hnsWalkToDoor_hns::
	applymovement LOCALID_DOME_ATTENDANT_DOUBLES, BattleFrontier_BattleDomeLobby_Movement_WalkToDoor_hns
	return

BattleFrontier_BattleDomeLobby_EventScript_SinglesAttendant_hnsEnterDoor_hns::
	applymovement LOCALID_DOME_ATTENDANT_SINGLES, BattleFrontier_BattleDomeLobby_Movement_AttendantEnterDoor_hns
	return

BattleFrontier_BattleDomeLobby_EventScript_DoublesAttendant_hnsEnterDoor_hns::
	applymovement LOCALID_DOME_ATTENDANT_DOUBLES, BattleFrontier_BattleDomeLobby_Movement_AttendantEnterDoor_hns
	return

BattleFrontier_BattleDomeLobby_EventScript_WelcomeSingles_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_WelcomeSingleBattle_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomeLobby_EventScript_WelcomeDoubles_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_WelcomeDoubleBattle_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomeLobby_EventScript_TakeSinglesChallenge_hns::
	message BattleFrontier_BattleDomeLobby_Text_TakeSinglesChallenge_hns
	return

BattleFrontier_BattleDomeLobby_EventScript_TakeDoublesChallenge_hns::
	message BattleFrontier_BattleDomeLobby_Text_TakeDoublesChallenge_hns
	return

BattleFrontier_BattleDomeLobby_EventScript_ExplainSinglesChallenge_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_ExplainSinglesChallenge_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomeLobby_EventScript_ExplainDoublesChallenge_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_ExplainDoublesChallenge_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattleDomeLobby_EventScript_OpenSinglesDoor_hns::
	opendoor 5, 4
	return

BattleFrontier_BattleDomeLobby_EventScript_OpenDoublesDoor_hns::
	opendoor 17, 4
	return

BattleFrontier_BattleDomeLobby_EventScript_CloseSinglesDoor_hns::
	closedoor 5, 4
	return

BattleFrontier_BattleDomeLobby_EventScript_CloseDoublesDoor_hns::
	closedoor 17, 4
	return

BattleFrontier_BattleDomeLobby_Movement_WalkToDoor_hns:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattleDomeLobby_Movement_AttendantEnterDoor_hns:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleDomeLobby_Movement_PlayerEnterDoor_hns:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleDomeLobby_EventScript_ShowSinglesResults_hns::
	lockall
	frontier_results FRONTIER_FACILITY_DOME, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleDomeLobby_EventScript_ShowDoublesResults_hns::
	lockall
	frontier_results FRONTIER_FACILITY_DOME, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleDomeLobby_EventScript_ShowPrevTourneyTree_hns::
	dome_get DOME_DATA_PREV_TOURNEY_TYPE
	call_if_eq VAR_RESULT, 0, BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsSinglesLv50_hns
	call_if_eq VAR_RESULT, 1, BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsDoublesLv50_hns
	call_if_eq VAR_RESULT, 2, BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsSinglesLvOpen_hns
	call_if_eq VAR_RESULT, 3, BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsDoublesLvOpen_hns
	fadescreen FADE_TO_BLACK
	dome_showprevtourneytree
	waitstate
	end

BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsSinglesLv50_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsSinglesLv50_hns, MSGBOX_SIGN
	return

BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsDoublesLv50_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsDoublesLv50_hns, MSGBOX_SIGN
	return

BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsSinglesLvOpen_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsSinglesLvOpen_hns, MSGBOX_SIGN
	return

BattleFrontier_BattleDomeLobby_EventScript_PrevTourneyResultsDoublesLvOpen_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsDoublesLvOpen_hns, MSGBOX_SIGN
	return

BattleFrontier_BattleDomeLobby_EventScript_Man_hnsiac_hns::
	dome_getwinnersname
	msgbox BattleFrontier_BattleDomeLobby_Text_LastWinnerWasTough_hns, MSGBOX_NPC
	end

BattleFrontier_BattleDomeLobby_EventScript_Lass_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_WinnersGainReputation_hns, MSGBOX_NPC
	end

BattleFrontier_BattleDomeLobby_EventScript_FatMan_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_TrashedInFirstRound_hns, MSGBOX_NPC
	end

BattleFrontier_BattleDomeLobby_EventScript_Man_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_NeedToCheckOpponentCarefully_hns, MSGBOX_NPC
	end

@ A few OutsideWest event scripts are inserted here instead, two of which are unused
BattleFrontier_OutsideWest_EventScript_Man3_hns::
	msgbox BattleFrontier_OutsideWest_Text_LongDreamedAboutBattleFrontier_hns, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_BattleDomeSign2_hns::
	msgbox BattleFrontier_OutsideWest_Text_BattleDomeSign2_hns, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnderConstructionSign_hns::
	msgbox BattleFrontier_OutsideWest_Text_QuestionMarkUnderConstruction_hns, MSGBOX_NPC
	end

BattleFrontier_BattleDomeLobby_EventScript_RulesBoard_hns::
	lockall
	msgbox BattleFrontier_BattleDomeLobby_Text_RulesAreListed_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattleDomeLobby_EventScript_ReadRulesBoard_hns::
	message BattleFrontier_BattleDomeLobby_Text_ReadWhichHeading_hns
	waitmessage
	multichoice 17, 4, MULTI_BATTLE_DOME_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleDomeLobby_EventScript_RulesMatchup_hns
	case 1, BattleFrontier_BattleDomeLobby_EventScript_RulesTourneyTree_hns
	case 2, BattleFrontier_BattleDomeLobby_EventScript_RulesDoubleKO_hns
	case 3, BattleFrontier_BattleDomeLobby_EventScript_ExitRules_hns
	case MULTI_B_PRESSED, BattleFrontier_BattleDomeLobby_EventScript_ExitRules_hns
	end

BattleFrontier_BattleDomeLobby_EventScript_RulesMatchup_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_ExplainMatchupRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattleDomeLobby_EventScript_RulesTourneyTree_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_ExplainTourneyTree_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattleDomeLobby_EventScript_RulesDoubleKO_hns::
	msgbox BattleFrontier_BattleDomeLobby_Text_ExplainDoubleKORules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleDomeLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattleDomeLobby_EventScript_ExitRules_hns::
	releaseall
	end

BattleFrontier_BattleDomeLobby_Text_WelcomeSingleBattle_hns:
	.string "כאן האסטרטגיות של המאמנים\n"
	.string "עומדות למבחן!\p"
	.string "ברוכים הבאים לכיפת הקרב!\p"
	.string "אני המדריך שלך\n"
	.string "לטורניר הקרב היחיד.$"

BattleFrontier_BattleDomeLobby_Text_TakeSinglesChallenge_hns:
	.string "רוצה להתמודד\n"
	.string "בטורניר הקרב היחיד?$"

BattleFrontier_BattleDomeLobby_Text_HopeToSeeYouAgain_hns:
	.string "נשמח לראות אותך שוב.$"

BattleFrontier_BattleDomeLobby_Text_ExplainSinglesChallenge_hns:
	.string "טורניר הקרב היחיד הוא בדיוק מה\n"
	.string "שהשם אומר: טורניר של קרבות יחידים.\p"
	.string "כל המאמנים המשתתפים חייבים\n"
	.string "לרשום שלושה פוקימונים כל אחד.\p"
	.string "בכל קרב, אחד משלושת\n"
	.string "הפוקימונים חייב להישאר בעתודה.\p"
	.string "שני הפוקימונים האחרים יכולים\n"
	.string "להילחם אחד בכל פעם.\p"
	.string "את שני הפוקימונים שיילחמו בוחרים\n"
	.string "אחרי שבוחנים את שלישיית היריב.\p"
	.string "כדי לזכות בטורניר צריך\n"
	.string "לנצח ארבעה מאמנים.\p"
	.string "הזוכה בטורניר מקבל\n"
	.string "נקודות קרב.\p"
	.string "כדי להפסיק את הטורניר באמצע,\n"
	.string "יש לשמור את המשחק.\p"
	.string "הפסקה בלי שמירה מראש\n"
	.string "תוביל לפסילה.$"

BattleFrontier_BattleDomeLobby_Text_OkayToSaveBeforeChallenge_hns:
	.string "לפני שאוביל אותך לכיפת הקרב,\n"
	.string "עליי לשמור את הנתונים. זה בסדר?$"

BattleFrontier_BattleDomeLobby_Text_WhichLevelMode_hns:
	.string "בטורניר יש שתי רמות אתגר: רמה 50\n"
	.string "ורמה פתוחה. מה הבחירה שלך?$"

BattleFrontier_BattleDomeLobby_Text_SelectThreeMons_hns:
	.string "עכשיו יש לבחור את שלושת\n"
	.string "הפוקימונים שברצונך לרשום.$"

BattleFrontier_BattleDomeLobby_Text_NotEnoughValidMonsLvOpen_hns:
	.string "סליחה!\p"
	.string "אין לך שלושה פוקימונים כשירים.\p"
	.string "בנוסף, הפוקימונים חייבים להחזיק\n"
	.string "פריטים מסוגים שונים.\p"
	.string "ביצים{STR_VAR_1}.$"

BattleFrontier_BattleDomeLobby_Text_NotEnoughValidMonsEnd_hns:
	.string "אפשר לחזור אליי כשהכול יהיה מוכן.$"

BattleFrontier_BattleDomeLobby_Text_NotEnoughValidMonsLv50_hns:
	.string "סליחה!\p"
	.string "אין לך שלושה פוקימונים כשירים.\p"
	.string "כדי להשתתף צריך שלושה פוקימונים\n"
	.string "שונים ברמה 50 ומטה.\p"
	.string "הם גם חייבים להחזיק\n"
	.string "פריטים מסוגים שונים.\p"
	.string "ביצים{STR_VAR_1}.$"

BattleFrontier_BattleDomeLobby_Text_ShowYouToBattleDome_hns:
	.string "עכשיו אוביל אותך\n"
	.string "לכיפת הקרב.$"

BattleFrontier_BattleDomeLobby_Text_DidntSaveBeforeQuitting_hns:
	.string "סליחה!\p"
	.string "בפעם הקודמת יצאת מהאתגר\n"
	.string "בלי לשמור.\p"
	.string "לכן האתגר שלך עד כה\n"
	.string "נפסל. מצטער!$"

BattleFrontier_BattleDomeLobby_Text_CongratsForWinningTourney_hns:
	.string "מזל טוב על הזכייה\n"
	.string "בטורניר הקרב!$"

@ Unused
BattleFrontier_BattleDomeLobby_Text_HereIsYourPrize_hns:
	.string "Here is your prize for your Battle\n"
	.string "Tournament victory.$"

@ Used by Verdanturf Tent
BattleFrontier_BattleDomeLobby_Text_ReceivedPrize_hns:
	.string "{PLAYER} received the prize\n"
	.string "{STR_VAR_1}.$"

@ Unused
BattleFrontier_BattleDomeLobby_Text_BagFullMakeRoom_hns:
	.string "Oh, your BAG appears to be full.\p"
	.string "Please make room in your BAG, then come\n"
	.string "see me.$"

BattleFrontier_BattleDomeLobby_Text_ThankYouForPlaying_hns:
	.string "תודה על ההשתתפות!$"

BattleFrontier_BattleDomeLobby_Text_RecordWillBeSaved_hns:
	.string "התוצאות שלך יישמרו.\n"
	.string "נא להמתין.$"

BattleFrontier_BattleDomeLobby_Text_WeveBeenWaitingForYou_hns:
	.string "חיכינו לך!$"

BattleFrontier_BattleDomeLobby_Text_OkayToSaveBeforeChallenge_hns2_hns:
	.string "לפני שאוביל אותך לכיפת הקרב,\n"
	.string "עליי לשמור את הנתונים. זה בסדר?$"

BattleFrontier_BattleDomeLobby_Text_WelcomeDoubleBattle_hns:
	.string "כאן האסטרטגיות של המאמנים\n"
	.string "עומדות למבחן!\p"
	.string "ברוכים הבאים לכיפת הקרב!\p"
	.string "אני המדריך שלך\n"
	.string "לטורניר הקרב הכפול.$"

BattleFrontier_BattleDomeLobby_Text_TakeDoublesChallenge_hns:
	.string "רוצה להתמודד\n"
	.string "בטורניר הקרב הכפול?$"

BattleFrontier_BattleDomeLobby_Text_ExplainDoublesChallenge_hns:
	.string "טורניר הקרב הכפול הוא בדיוק מה\n"
	.string "שהשם אומר: טורניר של קרבות כפולים.\p"
	.string "כל המאמנים המשתתפים חייבים\n"
	.string "לרשום שלושה פוקימונים כל אחד.\p"
	.string "בכל קרב, אחד משלושת\n"
	.string "הפוקימונים חייב להישאר בעתודה.\p"
	.string "שני הפוקימונים הנותרים חייבים\n"
	.string "להשתתף בקרב כפול.\p"
	.string "את שני הפוקימונים שיילחמו בוחרים\n"
	.string "אחרי שבוחנים את שלישיית היריב.\p"
	.string "כדי לזכות בטורניר צריך\n"
	.string "לנצח ארבעה מאמנים.\p"
	.string "הזוכה בטורניר מקבל\n"
	.string "נקודות קרב.\p"
	.string "כדי להפסיק את הטורניר באמצע,\n"
	.string "יש לשמור את המשחק.\p"
	.string "הפסקה בלי שמירה מראש\n"
	.string "תוביל לפסילה.$"

BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsSinglesLv50_hns:
	.string "אלה התוצאות של טורניר הקרב היחיד\n"
	.string "האחרון ברמה 50.$"

BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsDoublesLv50_hns:
	.string "אלה התוצאות של טורניר הקרב הכפול\n"
	.string "האחרון ברמה 50.$"

BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsSinglesLvOpen_hns:
	.string "אלה התוצאות של טורניר הקרב היחיד\n"
	.string "האחרון ברמה הפתוחה.$"

BattleFrontier_BattleDomeLobby_Text_PrevTourneyResultsDoublesLvOpen_hns:
	.string "אלה התוצאות של טורניר הקרב הכפול\n"
	.string "האחרון ברמה הפתוחה.$"

BattleFrontier_BattleDomeLobby_Text_LastWinnerWasTough_hns:
	.string "Did you see it?\n"
	.string "The last Battle Tournament?\p"
	.string "The winner, {STR_VAR_1}, was seriously\n"
	.string "tough.\p"
	.string "You should check out the results\n"
	.string "on the monitor beside the PC.$"

BattleFrontier_OutsideWest_Text_LongDreamedAboutBattleFrontier_hns:
	.string "חזית הקרב…\n"
	.string "כבר מזמן חלמתי על מקום כזה.$"

@ Functionally unused
BattleFrontier_OutsideWest_Text_BattleDomeSign2_hns:
	.string "The BATTLE DOME\n"
	.string "Become the Unbeatable Superstar!$"

@ Functionally unused
BattleFrontier_OutsideWest_Text_QuestionMarkUnderConstruction_hns:
	.string "The ??????\n"
	.string "Under Construction!$"

BattleFrontier_BattleDomeLobby_Text_WinnersGainReputation_hns:
	.string "מאמן שזוכה בטורנירים ברצף\n"
	.string "בכיפת הקרב צובר מוניטין של כוכב.\p"
	.string "המוניטין הזה מושך מאמנים\n"
	.string "קשוחים אל כיפת הקרב.\p"
	.string "כוכב-על אמיתי הוא מאמן\n"
	.string "שממשיך לזכות בטורנירים.$"

BattleFrontier_BattleDomeLobby_Text_TrashedInFirstRound_hns:
	.string "נתקלתי באחד המועמדים הבולטים לזכייה\n"
	.string "כבר בסיבוב הראשון.\p"
	.string "ברור שהוא ריסק אותי…$"

BattleFrontier_BattleDomeLobby_Text_NeedToCheckOpponentCarefully_hns:
	.string "הייתי מנצח אם הייתי משאיר\n"
	.string "את הפוקימון הזה בעתודה.\p"
	.string "צריך לבדוק היטב את פוקימוני היריב\n"
	.string "לפני שבוחרים את הפוקימונים שיילחמו.$"

BattleFrontier_BattleDomeLobby_Text_CongratsDefeatedTucker_hns:
	.string "מזל טוב!\p"
	.string "ניצחת את אס הכיפה וזכית\n"
	.string "בטורניר הקרב!$"

BattleFrontier_BattleDomeLobby_Text_AwardTheseBattlePoints_hns:
	.string "כהוקרה על האסטרטגיה היפהפייה שלך,\n"
	.string "אנו מעניקים לך את נקודות הקרב האלה!$"

BattleFrontier_BattleDomeLobby_Text_RecordLastMatch_hns:
	.string "להקליט בכרטיס חזית הקרב את\n"
	.string "הקרב האחרון שלך בכיפת הקרב?$"

BattleFrontier_BattleDomeLobby_Text_RulesAreListed_hns:
	.string "כאן כתובים החוקים\n"
	.string "של טורניר הקרב.$"

BattleFrontier_BattleDomeLobby_Text_ReadWhichHeading_hns:
	.string "איזה סעיף ברצונך לקרוא?$"

BattleFrontier_BattleDomeLobby_Text_ExplainMatchupRules_hns:
	.string "השיבוצים בטורניר נקבעים לפי\n"
	.string "חוזק הפוקימונים של המאמנים.\p"
	.string "כך מאמנים חזקים לא נפגשים\n"
	.string "זה מול זה כבר בהתחלה.$"

BattleFrontier_BattleDomeLobby_Text_ExplainTourneyTree_hns:
	.string "כל מדריך בחדר ההמתנה יכול להציג\n"
	.string "את טבלת הטורניר, שאנו מכנים ”העץ”.\p"
	.string "עץ הטורניר מציג\n"
	.string "כמה סוגים של נתונים.\p"
	.string "בין הנתונים: תוצאות הטורניר הקודם,\n"
	.string "הפוקימונים וסגנונות הקרב של המאמנים.$"

BattleFrontier_BattleDomeLobby_Text_ExplainDoubleKORules_hns:
	.string "אם בקרב בטורניר הפוקימונים הנלחמים\n"
	.string "מתעלפים בו-זמנית, זה נוקאאוט כפול.\p"
	.string "במקרה כזה, השופטים יבחנו את\n"
	.string "הקרב ויכריזו על המנצח.$"
