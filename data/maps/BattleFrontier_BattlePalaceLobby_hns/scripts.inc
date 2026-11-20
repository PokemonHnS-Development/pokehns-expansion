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
	.string "המקום שבו לבם של המאמנים\n"
	.string "עומד למבחן.\p"
	.string "ברוכים הבאים לארמון הקרב.\p"
	.string "אני מקבל אתגרים לאולמות\n"
	.string "הקרב היחיד.$"

BattleFrontier_BattlePalaceLobby_Text_TakeSingleBattleChallenge_hns:
	.string "האם ברצונך לקבל על עצמך\n"
	.string "את אתגר אולם הקרב היחיד?$"

BattleFrontier_BattlePalaceLobby_Text_ExplainSingleBattleChallenge_hns:
	.string "בארמון הקרב יש כמה אולמות לקרבות\n"
	.string "יחידים, שנקראים אולמות הקרב היחיד.\p"
	.string "הקרבות היחידים מתנהלים כרגיל, מלבד\n"
	.string "כלל חשוב אחד שחובה לציית לו.\p"
	.string "למאמנים מותר רק להכניס\n"
	.string "ולהוציא את הפוקימונים שלהם.\p"
	.string "מלבד זאת, אסור למאמנים\n"
	.string "לתת פקודות לפוקימונים שלהם.\p"
	.string "הפוקימונים יתנהגו לפי האופי\n"
	.string "שלהם ויילחמו בכוחות עצמם.\p"
	.string "עליך לתת אמון בפוקימונים\n"
	.string "שלך ולהשגיח עליהם.\p"
	.string "אם תזכה בכבוד לנצח שבעה מאמנים\n"
	.string "ברצף, נעניק לך נקודות קרב.\p"
	.string "אם ברצונך להפסיק את האתגר באמצע,\n"
	.string "עליך לשמור את המשחק.\p"
	.string "אם לא תשמור לפני ההפסקה, תיפסל.$"

BattleFrontier_BattlePalaceLobby_Text_ReturnWhenFortified_hns:
	.string "כשתחשל את לבך ואת\n"
	.string "הפוקימונים שלך, עליך לשוב.$"

BattleFrontier_BattlePalaceLobby_Text_WhichChallenge_hns:
	.string "יש שני אולמות קרב: רמה 50 ורמה פתוחה.\n"
	.string "באיזה אתגר אתה בוחר?$"

BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLv50_hns:
	.string "אח…\p"
	.string "אין לך את שלושת הפוקימונים\n"
	.string "הדרושים לאתגר.\p"
	.string "כדי להשתתף, עליך להביא שלושה\n"
	.string "פוקימונים ממינים שונים.\p"
	.string "כל הפוקימונים האלה חייבים\n"
	.string "להיות ברמה 50 או פחות.\p"
	.string "בנוסף, אסור שיחזיקו\n"
	.string "פריטים זהים.\p"
	.string "ביצים{STR_VAR_1}.$"

BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsEnd_hns:
	.string "כדאי לחזור כשההכנות\n"
	.string "שלך יושלמו.$"

BattleFrontier_BattlePalaceLobby_Text_NotEnoughValidMonsLvOpen_hns:
	.string "אח…\p"
	.string "אין לך את שלושת הפוקימונים\n"
	.string "הדרושים לאתגר.\p"
	.string "כדי להשתתף, עליך להביא שלושה\n"
	.string "פוקימונים ממינים שונים.\p"
	.string "בנוסף, אסור שיחזיקו\n"
	.string "פריטים זהים.\p"
	.string "ביצים{STR_VAR_1}.$"

BattleFrontier_BattlePalaceLobby_Text_NowSelectThreeMons_hns:
	.string "טוב. עכשיו עליך לבחור\n"
	.string "את שלושת הפוקימונים שלך.$"

BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge_hns2_hns:
	.string "עליי לשמור לפני שאוביל אותך\n"
	.string "לאולם הקרב. זה בסדר?$"

BattleFrontier_BattlePalaceLobby_Text_FollowMe_hns:
	.string "טוב.\n"
	.string "עכשיו, אחריי בבקשה.$"

BattleFrontier_BattlePalaceLobby_Text_ResultsWillBeRecorded_hns:
	.string "זכות היא לי שראיתי\n"
	.string "את מעללי הפוקימונים שלך.\p"
	.string "התוצאות יירשמו.\n"
	.string "עליי לבקש ממך להמתין רגע.$"

BattleFrontier_BattlePalaceLobby_Text_FirmTrueBondsFor7WinStreak_hns:
	.string "להשיג רצף של 7 ניצחונות…\p"
	.string "נראה שהקשר בין לבך לבין\n"
	.string "הפוקימונים שלך איתן ואמיתי.$"

BattleFrontier_BattlePalaceLobby_Text_FeatWillBeRecorded_hns:
	.string "ההישג שלך יירשם.\n"
	.string "עליי לבקש ממך להמתין רגע.$"

@ Unused
BattleFrontier_BattlePalaceLobby_Text_BattlePointsFor7WinStreak_hns:
	.string "For the feat of your 7-win streak,\n"
	.string "we present you with Battle Point(s).$"

BattleFrontier_BattlePalaceLobby_Text_NoSpaceForPrize_hns:
	.string "You seem to have no space for\n"
	.string "our prize.\p"
	.string "You should return when you have\n"
	.string "organized your BAG.$"

BattleFrontier_BattlePalaceLobby_Text_WeHaveBeenWaiting_hns:
	.string "חיכינו לך…$"

BattleFrontier_BattlePalaceLobby_Text_MustSaveBeforeChallenge_hns:
	.string "עליי לשמור לפני שאוביל אותך\n"
	.string "לאולם הקרב. זה בסדר?$"

BattleFrontier_BattlePalaceLobby_Text_FailedToSaveBeforeEndingChallenge_hns:
	.string "אח…\p"
	.string "בפעם הקודמת לא שמרת לפני\n"
	.string "שסיימת את האתגר שלך.\p"
	.string "לכן האתגר שלך נפסל.\n"
	.string "זה מצער ביותר.$"

@ Unused
BattleFrontier_BattlePalaceLobby_Text_ReceivedPrize_hns:
	.string "{PLAYER} received the prize\n"
	.string "{STR_VAR_1}.$"

BattleFrontier_BattlePalaceLobby_Text_LadyCanTellWhatMonsThink_hns:
	.string "לבחור קשוח כמוני, פוקימונים\n"
	.string "בעלי אופי קשוח הם הכי טובים.\p"
	.string "ההתקפה היא ההגנה הטובה ביותר!\n"
	.string "התקפה בלתי פוסקת היא השיא!\p"
	.string "אבל לא על זה רציתי לדבר.\p"
	.string "מדי פעם עוברת כאן\n"
	.string "בחורה ממש חמודה.\p"
	.string "היא אומרת שהיא יודעת מה\n"
	.string "פוקימונים חושבים.\p"
	.string "לגבי זה אני לא בטוח,\n"
	.string "אבל היא באמת ממש חמודה.\p"
	.string "מה?\n"
	.string "למה אתה מסתכל עליי ככה?$"

BattleFrontier_BattlePalaceLobby_Text_NatureAndMovesKeyHere_hns:
	.string "הממ…\p"
	.string "נראה שהאופי של הפוקימונים והמהלכים\n"
	.string "שלימדו אותם הם המפתח לקרבות כאן.\p"
	.string "ליתר דיוק, מה שחשוב הוא עד כמה\n"
	.string "המהלכים מתאימים לאופי של הפוקימון.\p"
	.string "אם הפוקימון שלך בצרה ולא מצליח\n"
	.string "לממש את הפוטנציאל שלו,\p"
	.string "אולי כדאי לבדוק עד כמה\n"
	.string "המהלכים שלו מתאימים לאופי שלו.$"

BattleFrontier_BattlePalaceLobby_Text_MonDocileButTransforms_hns:
	.string "הפוקימון שלי בדרך כלל צייתן מאוד.\p"
	.string "אבל כשהוא באולם הקרב, לפעמים נדמה\n"
	.string "שהוא הופך למשהו מרושע!\p"
	.string "הוא נעשה מאיים לגמרי.\n"
	.string "אפילו מזעזע.$"

BattleFrontier_BattlePalaceLobby_Text_WhatNatureFavorsChippingAway_hns:
	.string "מעניין איזה אופי יש לפוקימון שמעדיף\n"
	.string "להחליש את יריביו ולכרסם בהם לאט לאט.\p"
	.string "הייתי מופתע אם זה היה אופי רפוי.\p"
	.string "אבל לא, זה לא יכול להיות נכון.$"

BattleFrontier_BattlePalaceLobby_Text_WelcomeForDoubleBattle_hns:
	.string "המקום שבו לבם של המאמנים\n"
	.string "עומד למבחן.\p"
	.string "ברוכים הבאים לארמון הקרב.\p"
	.string "אני מקבל אתגרים לאולמות\n"
	.string "הקרב הכפול.$"

BattleFrontier_BattlePalaceLobby_Text_TakeDoubleBattleChallenge_hns:
	.string "האם ברצונך לקבל על עצמך\n"
	.string "את אתגר אולם הקרב הכפול?$"

BattleFrontier_BattlePalaceLobby_Text_ExplainDoubleBattleChallenge_hns:
	.string "בארמון הקרב יש כמה אולמות לקרבות\n"
	.string "כפולים, שנקראים אולמות הקרב הכפול.\p"
	.string "הקרבות הכפולים מתנהלים כרגיל, מלבד\n"
	.string "כלל חשוב אחד שחובה לציית לו.\p"
	.string "למאמנים מותר רק להכניס\n"
	.string "ולהוציא את הפוקימונים שלהם.\p"
	.string "מלבד זאת, אסור למאמנים\n"
	.string "לתת פקודות לפוקימונים שלהם.\p"
	.string "הפוקימונים יתנהגו לפי האופי\n"
	.string "שלהם ויילחמו בכוחות עצמם.\p"
	.string "עליך לתת אמון בפוקימונים\n"
	.string "שלך ולהשגיח עליהם.\p"
	.string "אם תזכה בכבוד לנצח שבעה מאמנים\n"
	.string "ברצף, נעניק לך נקודות קרב.\p"
	.string "אם ברצונך להפסיק את האתגר באמצע,\n"
	.string "יש לשמור את המשחק.\p"
	.string "אם לא תשמור לפני ההפסקה, תיפסל.$"

BattleFrontier_BattlePalaceLobby_Text_ToDefeatMavenAnd7Trainers_hns:
	.string "להביס את אשף הארמון\n"
	.string "ושבעה מאמנים ברצף…$"

BattleFrontier_BattlePalaceLobby_Text_PresentYouWithBattlePoints_hns:
	.string "לכבוד הקשר בינך לבין הפוקימונים שלך,\n"
	.string "אנו מעניקים לך את נקודות הקרב האלה.$"

BattleFrontier_BattlePalaceLobby_Text_LikeToRecordMatch_hns:
	.string "לשמור בכרטיס חזית הקרב את\n"
	.string "הקרב האחרון שלך בארמון הקרב?$"

BattleFrontier_BattlePalaceLobby_Text_RulesAreListed_hns:
	.string "כאן מפורטים חוקי אולם הקרב.$"

BattleFrontier_BattlePalaceLobby_Text_ReadWhichHeading_hns:
	.string "איזה סעיף ברצונך לקרוא?$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesBasics_hns:
	.string "כאן הפוקימונים נדרשים לחשוב\n"
	.string "ולהילחם בכוחות עצמם.\p"
	.string "בניגוד לפוקימונים בטבע, פוקימונים שחיים\n"
	.string "עם אנשים מתנהגים בהתאם לאופי שלהם.$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesNature_hns:
	.string "בהתאם לאופי שלו, פוקימון עשוי\n"
	.string "להעדיף לתקוף בכל מצב.\p"
	.string "פוקימון אחר עשוי להעדיף להגן\n"
	.string "על עצמו מכל פגיעה.\p"
	.string "ואחר עשוי ליהנות להציק\n"
	.string "ליריביו ולבלבל אותם.\p"
	.string "בגלל האופי שלו, לפוקימון יש\n"
	.string "מהלכים אהובים שהוא טוב בהם.\p"
	.string "הוא גם עלול לא לאהוב מהלכים\n"
	.string "מסוימים שקשה לו להשתמש בהם.$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesMoves_hns:
	.string "יש מהלכי התקפה שגורמים\n"
	.string "נזק ישיר ליריב.\p"
	.string "יש מהלכי הגנה שמשמשים להתכונן להתקפות\n"
	.string "היריב, לרפא נ”ח וכדומה.\p"
	.string "יש גם מהלכים מוזרים משהו שמחלישים\n"
	.string "יריבים בבעיות מצב כמו הרעלה ושיתוק.\p"
	.string "הפוקימונים ישקלו להשתמש\n"
	.string "במהלכים משלוש הקטגוריות האלה.$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesUnderpowered_hns:
	.string "כשהמאמן לא נותן לו פקודות, פוקימון\n"
	.string "עלול לא לנצל היטב מהלכים מסוימים.\p"
	.string "פוקימון לא מיטיב להשתמש\n"
	.string "במהלכים שהוא לא אוהב.\p"
	.string "אם כל המהלכים של פוקימון לא תואמים\n"
	.string "את אופיו, לרוב הוא לא ימצה את יכולתו.$"

BattleFrontier_BattlePalaceLobby_Text_ExplainRulesWhenInDanger_hns:
	.string "בהתאם לאופי שלו, פוקימון בצרה עשוי\n"
	.string "לעבור למהלכים שלא תואמים את אופיו.\p"
	.string "אם פוקימון מתחיל להתנהג מוזר\n"
	.string "בשעת דחק, כדאי לעקוב אחריו היטב.$"

