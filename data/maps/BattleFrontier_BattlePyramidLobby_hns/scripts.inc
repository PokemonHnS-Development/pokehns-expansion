BattleFrontier_BattlePyramidLobby_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidLobby_OnFrame_hns
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleDomeLobby_OnWarp
	.byte 0

@ Unused. Pyramid uses Dome's OnWarp (presumably by mistake). Their effects are identical
BattleFrontier_BattlePyramidLobby_OnWarp_hns:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePyramidLobby_EventScript_TurnPlayerNorth_hns
	.2byte 0

BattleFrontier_BattlePyramidLobby_EventScript_TurnPlayerNorth_hns:
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePyramidLobby_OnFrame_hns:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattlePyramidLobby_EventScript_GetChallengeStatus_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramidLobby_EventScript_QuitWithoutSaving_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidLobby_EventScript_ResumeChallenge_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattlePyramidLobby_EventScript_WonChallenge_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePyramidLobby_EventScript_LostChallenge_hns
	.2byte 0

BattleFrontier_BattlePyramidLobby_EventScript_GetChallengeStatus_hns::
	frontier_getstatus
	end

BattleFrontier_BattlePyramidLobby_EventScript_QuitWithoutSaving_hns::
	lockall
	message BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag_hns
	waitmessage
	playse SE_EXP_MAX
	waitse
	closemessage
	pyramid_set PYRAMID_DATA_WIN_STREAK, 0
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_WonChallenge_hns::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_DefeatedKing_hns
	msgbox BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_GiveBattlePoints_hns

BattleFrontier_BattlePyramidLobby_EventScript_DefeatedKing_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing_hns, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_GiveBattlePoints_hns::
	special DoBattlePyramidMonsHaveHeldItem
	call_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_StoreHeldItemsInPyramidBag_hns
	clearflag FLAG_STORING_ITEMS_IN_PYRAMID_BAG
	frontier_checkairshow
	special LoadPlayerParty
	pyramid_clearhelditems
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	message BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept_hns
	waitmessage
	playse SE_EXP_MAX
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints_hns, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait_hns
	waitmessage
	pyramid_setprize
	pyramid_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge_hns, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_LostChallenge_hns::
	frontier_checkairshow
	special LoadPlayerParty
	pyramid_clearhelditems
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	lockall
	message BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag_hns
	waitmessage
	playse SE_EXP_MAX
	waitse
	message BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait_hns
	waitmessage
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, FALSE
	pyramid_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge_hns, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_ResumeChallenge_hns::
	goto BattleFrontier_BattlePyramidLobby_EventScript_EnterChallenge_hns

BattleFrontier_BattlePyramidLobby_EventScript_Attendant_hns::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PYRAMID
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattlePyramidLobby_Text_WelcomeToBattlePyramid_hns, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_AskTakeChallenge_hns::
	message BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge_hns
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge_hns
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_ExplainChallenge_hns
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge_hns

BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge_hns::
	message BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode_hns
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge_hns
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons_hns
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons_hns, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge_hns
	msgbox BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge_hns, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge_hns
	case YES, BattleFrontier_BattlePyramidLobby_EventScript_SaveBeforeChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge_hns

BattleFrontier_BattlePyramidLobby_EventScript_SaveBeforeChallenge_hns::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	pyramid_init
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	pyramid_seedfloor
	pyramid_settrainers
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge_hnsSaveFailed_hns
BattleFrontier_BattlePyramidLobby_EventScript_EnterChallenge_hns::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid_hns, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_BattlePyramidLobby_EventScript_WalkToPanelAndReceiveBag_hns
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_RESULT, 0
	special HealPlayerParty
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR_HNS, 1, 1
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExplainChallenge_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_AskTakeChallenge_hns

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons_hns::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons_hnsLv50_hns
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons_hnsLvOpen_hns

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons_hnsLv50_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50_hns, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsEnd_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge_hns

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons_hnsLvOpen_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen_hns, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsEnd_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge_hns

BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge_hnsSaveFailed_hns::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge_hns

BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge_hns::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge_hns, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge_hns::
	release
	end

BattleFrontier_BattlePyramidLobby_EventScript_HintGiver_hns::
	lockall
	applymovement LOCALID_PYRAMID_LOBBY_HINT_GIVER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait_hns, MSGBOX_DEFAULT
	call BattleFrontier_BattlePyramidLobby_EventScript_GiveHint_hns
	msgbox BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot_hns, MSGBOX_DEFAULT
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_GiveHint_hns::
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePyramidLobby_EventScript_GiveHint_hnsLv50_hns
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePyramidLobby_EventScript_GiveHint_hnsLvOpen_hns
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePyramidLobby_EventScript_NoHint_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_NoHint_hns
	return

@ Shouldnt occur
BattleFrontier_BattlePyramidLobby_EventScript_NoHint_hns::
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHint_hnsLv50_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_Aah_hns, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK_ACTIVE_50
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidLobby_EventScript_GiveHint_hnsGetLv50Streak_hns
	setvar VAR_RESULT, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment_hns
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHint_hnsGetLv50Streak_hns::
	pyramid_get PYRAMID_DATA_WIN_STREAK_50
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment_hns
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHint_hnsLvOpen_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_Aah_hns, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK_ACTIVE_OPEN
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidLobby_EventScript_GiveHint_hnsGetLvOpenStreak_hns
	setvar VAR_RESULT, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment_hns
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHint_hnsGetLvOpenStreak_hns::
	pyramid_get PYRAMID_DATA_WIN_STREAK_OPEN
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment_hns
	return

BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment_hns::
	copyvar VAR_0x8004, VAR_RESULT
	special GetBattlePyramidHint
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_HintParalysis_hns
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_HintPoison_hns
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_HintBurn_hns
	case 3, BattleFrontier_BattlePyramidLobby_EventScript_HintPPWaste_hns
	case 4, BattleFrontier_BattlePyramidLobby_EventScript_HintLevitate_hns
	case 5, BattleFrontier_BattlePyramidLobby_EventScript_HintTrapAbility_hns
	case 6, BattleFrontier_BattlePyramidLobby_EventScript_HintIce_hns
	case 7, BattleFrontier_BattlePyramidLobby_EventScript_HintExplosion_hns
	case 8, BattleFrontier_BattlePyramidLobby_EventScript_HintPsychic_hns
	case 9, BattleFrontier_BattlePyramidLobby_EventScript_HintRock_hns
	case 10, BattleFrontier_BattlePyramidLobby_EventScript_HintFighting_hns
	case 11, BattleFrontier_BattlePyramidLobby_EventScript_HintWeather_hns
	case 12, BattleFrontier_BattlePyramidLobby_EventScript_HintBug_hns
	case 13, BattleFrontier_BattlePyramidLobby_EventScript_HintDark_hns
	case 14, BattleFrontier_BattlePyramidLobby_EventScript_HintWater_hns
	case 15, BattleFrontier_BattlePyramidLobby_EventScript_HintGhost_hns
	case 16, BattleFrontier_BattlePyramidLobby_EventScript_HintSteel_hns
	case 17, BattleFrontier_BattlePyramidLobby_EventScript_HintFlyingDragon_hns
	case 18, BattleFrontier_BattlePyramidLobby_EventScript_HintStoneEvolve_hns
	case 19, BattleFrontier_BattlePyramidLobby_EventScript_HintNormal_hns
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintParalysis_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintParalysis_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPoison_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPoison_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintBurn_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintBurn_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPPWaste_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPPWaste_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintLevitate_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintLevitate_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintTrapAbility_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintIce_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintIce_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintExplosion_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintExplosion_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPsychic_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPsychic_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintRock_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintRock_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintFighting_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintFighting_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintWeather_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintWeather_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintBug_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintBug_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintDark_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintDark_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintWater_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintWater_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintGhost_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintGhost_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintSteel_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintSteel_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintFlyingDragon_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintStoneEvolve_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintNormal_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintNormal_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_ShowResults_hns::
	lockall
	frontier_results FRONTIER_FACILITY_PYRAMID
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_WalkToPanelAndReceiveBag_hns::
	applymovement LOCALID_PYRAMID_LOBBY_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel_hns
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping_hns, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_ReceiveNewBattleBag_hns
	msgbox BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReceiveBattleBag_hns

BattleFrontier_BattlePyramidLobby_EventScript_ReceiveNewBattleBag_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag_hns, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_ReceiveBattleBag_hns::
	message BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag_hns
	waitmessage
	playse SE_EXP_MAX
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PYRAMID_LOBBY_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside_hns
	waitmovement 0
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel_hns
	waitmovement 0
	return

BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel_hns:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_down
	step_end

BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel_hns:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside_hns:
	walk_right
	face_left
	step_end

BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel_hns:
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePyramidLobby_EventScript_StoreHeldItemsInPyramidBag_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake_hns, MSGBOX_DEFAULT
	setflag FLAG_STORING_ITEMS_IN_PYRAMID_BAG
	special TryStoreHeldItemsInPyramidBag
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_HeldItemsStoredInPyramidBag_hns
	message BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep_hns
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep_hns
	end

BattleFrontier_BattlePyramidLobby_EventScript_HeldItemsStoredInPyramidBag_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag_hns, MSGBOX_DEFAULT
	return

@ When exiting Battle Pyramid with a full pyramid bag and held items the player must select to keep/toss party held items and make room for any kept items by tossing from the pyramid bag
BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep_hns::
	multichoice 17, 6, MULTI_FRONTIER_ITEM_CHOOSE, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromBag_hns
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromParty_hns
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems_hns
	end

BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromBag_hns::
	special ChooseItemsToTossFromPyramidBag
	waitstate
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep_hns
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep_hns
	end

BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromParty_hns::
	special BattlePyramidChooseMonHeldItems
	waitstate
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep_hns
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep_hns
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems_hns::
	special DoBattlePyramidMonsHaveHeldItem
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_PartyStillHasHeldItems_hns
	return

BattleFrontier_BattlePyramidLobby_EventScript_PartyStillHasHeldItems_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem_hns, MSGBOX_DEFAULT
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep_hns
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep_hns
	end

BattleFrontier_BattlePyramidLobby_EventScript_Woman_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning_hns, MSGBOX_NPC
	end

BattleFrontier_BattlePyramidLobby_EventScript_FatMan_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems_hns, MSGBOX_NPC
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesBoard_hns::
	lockall
	msgbox BattleFrontier_BattlePyramidLobby_Text_RulesAreListed_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard_hns::
	message BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading_hns
	waitmessage
	multichoice 15, 2, MULTI_BATTLE_PYRAMID_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_RulesPokemon_hns
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_RulesTrainers_hns
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_RulesMaze_hns
	case 3, BattleFrontier_BattlePyramidLobby_EventScript_RulesBag_hns
	case 4, BattleFrontier_BattlePyramidLobby_EventScript_ExitRules_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_ExitRules_hns
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesPokemon_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesTrainers_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesMaze_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesBag_hns::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExitRules_hns::
	releaseall
	end

BattleFrontier_BattlePyramidLobby_Text_WelcomeToBattlePyramid_hns:
	.string "המקום שבו אומץ המאמנים\n"
	.string "עומד למבחן!\p"
	.string "ברוכים הבאים לפירמידת הקרב!\p"
	.string "אני המדריך שלך\n"
	.string "במסע הקרב.$"

BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge_hns:
	.string "יש לך את האומץ לצאת\n"
	.string "לאתגר מסע הקרב?$"

BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge_hns:
	.string "נחכה לאתגר שלך בעתיד!$"

BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid_hns:
	.string "מסע הקרב הוא אירוע קרבות שבו חוקרים\n"
	.string "את הפירמידה ומנסים להגיע לפסגה.\p"
	.string "בפירמידה שבע קומות של מבוכים, ובכולן\n"
	.string "גם מאמנים מיומנים וגם פוקימונים פראיים.\p"
	.string "יש להיכנס עם שלושה פוקימונים,\n"
	.string "שאף אחד מהם לא מחזיק פריט.\p"
	.string "במהלך העלייה יינתן לך\n"
	.string "תיק הקרב לאחסון פריטים.\p"
	.string "במקרה של כישלון באתגר, כל פריט\n"
	.string "שנמצא בתיק הקרב ייעלם.\p"
	.string "כדי להפסיק את האתגר באמצע, יש לבחור\n"
	.string "ב”מנוחה” ולשמור את המשחק.\p"
	.string "אם לא שומרים לפני ההפסקה,\n"
	.string "נפסלים מהאתגר.$"

BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode_hns:
	.string "בפירמידה יש שני מסלולים: רמה 50\n"
	.string "ורמה פתוחה. לאיזה מהם תרצה להיכנס?$"

BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons_hns:
	.string "טוב מאוד. עכשיו יש לבחור\n"
	.string "את שלושת הפוקימונים שילוו אותך.$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen_hns:
	.string "בעיה קטנה, הרפתקן!\p"
	.string "נראה שאין לך שלושה פוקימונים\n"
	.string "כשירים לאתגר.\p"
	.string "בנוסף, יש לזכור לקחת\n"
	.string "את כל הפריטים מהפוקימונים שלך.\p"
	.string "ביצים{STR_VAR_1}.$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50_hns:
	.string "בעיה קטנה, הרפתקן!\p"
	.string "נראה שאין לך שלושה פוקימונים\n"
	.string "כשירים לאתגר.\p"
	.string "שלושת הפוקימונים צריכים להיות שונים,\n"
	.string "וכל אחד מהם ברמה 50 לכל היותר.\p"
	.string "בנוסף, יש לזכור לקחת\n"
	.string "את כל הפריטים מהפוקימונים שלך.\p"
	.string "ביצים{STR_VAR_1}.$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsEnd_hns:
	.string "כשהכול יהיה מוכן,\n"
	.string "אפשר לפנות אליי.$"

BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge_hns:
	.string "לפני הכניסה לפירמידת הקרב\n"
	.string "יש לשמור את המשחק. זה בסדר?$"

BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid_hns:
	.string "טוב מאוד. עכשיו אוביל אותך\n"
	.string "אל פירמידת הקרב.$"

BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping_hns:
	.string "נשמור לך את התיק בבטחה,\n"
	.string "{PLAYER}, במהלך המסע.$"

BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag_hns:
	.string "בתמורה, הנה תיק הקרב,\n"
	.string "זה שהשתמשת בו בפעם הקודמת.$"

BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag_hns:
	.string "בתמורה, הנה לך\n"
	.string "תיק הקרב.$"

BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag_hns:
	.string "{PLAYER} החליף את התיק\n"
	.string "בתיק הקרב.$"

BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel_hns:
	.string "כשדורכים על משטח הרצפה הזה,\n"
	.string "מועברים לקומה גבוהה יותר בפירמידה.\p"
	.string "אני מקווה למענך\n"
	.string "שהמסע שלך יעבור בשלום!$"

BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag_hns:
	.string "בעיה רצינית, חוקר!\p"
	.string "בפעם הקודמת לא שמרת לפני\n"
	.string "שסיימת את האתגר.\p"
	.string "לכן, לצערי, האתגר שלך נפסל.\p"
	.string "הנה התיק ששמרנו בשבילך.\p"
	.string "{PLAYER} קיבל את התיק בחזרה.$"

BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid_hns:
	.string "איזה יופי שחזרת!\p"
	.string "כבשת את הפירמידה!\n"
	.string "נפלא!$"

BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake_hns:
	.string "אה, בעיה קטנה.\p"
	.string "לפחות פוקימון אחד מחזיק פריט.\p"
	.string "לצערי, אי אפשר להוציא מכאן\n"
	.string "פריטים שהושגו בפירמידה.$"

BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag_hns:
	.string "כל הפריטים שהפוקימונים שלך מחזיקים\n"
	.string "יועברו לתיק הקרב שלך, {PLAYER}.$"

BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep_hns:
	.string "לצערי, תיק הקרב לא יכול\n"
	.string "להכיל את כל הפריטים שלך.\p"
	.string "יש לבחור אילו פריטים יישארו\n"
	.string "בתיק הקרב ואצל הפוקימונים.$"

BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem_hns:
	.string "לפחות פוקימון אחד עדיין מחזיק פריט.$"

BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep_hns:
	.string "יש לבחור אילו פריטים יישארו\n"
	.string "בתיק הקרב ואצל הפוקימונים.$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ReturnedEverythingMonsHeld_hns:
	.string "{PLAYER} returned everything that\n"
	.string "the POKéMON held.$"

BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept_hns:
	.string "תיק הקרב שהשתמשת בו יישמר\n"
	.string "לקראת האתגר הבא שלך.\p"
	.string "{PLAYER} מסר את תיק הקרב\n"
	.string "וקיבל בחזרה את התיק.$"

BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait_hns:
	.string "עליי לרשום את התוצאות שלך.\n"
	.string "נא להמתין.$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ForConqueringPyramidTakeThis_hns:
	.string "As a memento for conquering\n"
	.string "the BATTLE PYRAMID, please take this.$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ReceivedPrizeItem_hns:
	.string "{PLAYER} received the prize\n"
	.string "{STR_VAR_1}.$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_BagIsFull_hns:
	.string "…Ah…\n"
	.string "Your BAG appears to be filled.\p"
	.string "Please return after you've organized\n"
	.string "your BAG's contents.$"

BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag_hns:
	.string "איזו אכזבה…\p"
	.string "הנה התיק ששמרנו בשבילך.\p"
	.string "{PLAYER} קיבל את התיק בחזרה.$"

BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge_hns:
	.string "נשמח לראות אותך\n"
	.string "באתגר הבא!$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_HereIsPrize_hns:
	.string "We have been looking forward to\n"
	.string "your arrival!\p"
	.string "Here is your prize for conquering\n"
	.string "the PYRAMID.$"

BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait_hns:
	.string "ברוכים הבאים…\p"
	.string "אשמח לספר לך אילו צרות\n"
	.string "מחכות לך בפירמידה…$"

BattleFrontier_BattlePyramidLobby_Text_Aah_hns:
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "… … … … … …\n"
	.string "אהה!$"

BattleFrontier_BattlePyramidLobby_Text_HintParalysis_hns:
	.string "אני רואה מטר של ניצוצות…\p"
	.string "…ובתוכו אני רואה את הפוקימונים שלך\n"
	.string "נאבקים בשיתוק…$"

BattleFrontier_BattlePyramidLobby_Text_HintPoison_hns:
	.string "אני רואה רעל…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "סובלים מהשפעות הרעל…$"

BattleFrontier_BattlePyramidLobby_Text_HintBurn_hns:
	.string "אני רואה להבות אדומות בוהקות…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "סובלים מכוויות…$"

BattleFrontier_BattlePyramidLobby_Text_HintPPWaste_hns:
	.string "אני חשה לחץ עצום של\n"
	.string "זעם שלא בא על סיפוקו…\p"
	.string "זוהי קללה…\p"
	.string "…ואני רואה את הפוקימונים שלך מרוקנים\n"
	.string "מנקודות כוח, ונאלצים להשתמש במאבק…$"

BattleFrontier_BattlePyramidLobby_Text_HintLevitate_hns:
	.string "אני רואה פוקימונים מרחפים גבוה באוויר…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "מתוסכלים ממהלכי אדמה חסרי השפעה…$"

BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility_hns:
	.string "אני חשה אנרגיה אדירה שעולה\n"
	.string "מהאדמה שמתחת…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "לא מצליחים להימלט מאחיזת הכוח…$"

BattleFrontier_BattlePyramidLobby_Text_HintIce_hns:
	.string "אני רואה פוקימונים מסוג קרח…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "נאבקים בהשפעות המקפיאות של הקרח…$"

BattleFrontier_BattlePyramidLobby_Text_HintExplosion_hns:
	.string "אני רואה שטף של מהלכים שמסכנים\n"
	.string "את המשתמש בהם…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "נופלים מולם…$"

BattleFrontier_BattlePyramidLobby_Text_HintPsychic_hns:
	.string "אני רואה פוקימונים מסוג על-חושי…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "מתייסרים ממהלכים מסוג על-חושי…$"

BattleFrontier_BattlePyramidLobby_Text_HintRock_hns:
	.string "אני רואה פוקימונים מסוג סלע…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "סובלים ממהלכים מסוג סלע…$"

BattleFrontier_BattlePyramidLobby_Text_HintFighting_hns:
	.string "אני רואה פוקימונים מסוג קרב…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "מוכים במהלכים מסוג קרב…$"

BattleFrontier_BattlePyramidLobby_Text_HintWeather_hns:
	.string "ריקוד גשם… יום שמשי…\n"
	.string "סופת חול… ברד…\p"
	.string "אני רואה פוקימונים שמתחזקים\n"
	.string "בזכות מזג האוויר…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "מבולבלים מסוגים שונים של מהלכים…$"

BattleFrontier_BattlePyramidLobby_Text_HintBug_hns:
	.string "אני רואה פוקימונים מסוג חרק…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "סובלים מסוגים שונים של התקפות…$"

BattleFrontier_BattlePyramidLobby_Text_HintDark_hns:
	.string "אני רואה פוקימונים מסוג אפל…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "סובלים ממהלכים מסוג אפל…$"

BattleFrontier_BattlePyramidLobby_Text_HintWater_hns:
	.string "אני רואה פוקימונים מסוג מים…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "סובלים ממהלכים מסוג מים…$"

BattleFrontier_BattlePyramidLobby_Text_HintGhost_hns:
	.string "אני רואה פוקימונים מסוג רפאים…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "סובלים ממהלכים מסוג רפאים…$"

BattleFrontier_BattlePyramidLobby_Text_HintSteel_hns:
	.string "אני רואה פוקימונים מסוג פלדה…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "סובלים ממהלכים עוצמתיים להפליא…$"

BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon_hns:
	.string "אני רואה פוקימונים מעופפים…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "סובלים ממהלכים עוצמתיים להפליא…$"

BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve_hns:
	.string "אני רואה כאלה שהתפתחו\n"
	.string "בזכות כוחן של אבנים…\p"
	.string "אני חשה גם אש, מים\n"
	.string "וחשמל…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "סובלים משלושת הכוחות האלה…$"

BattleFrontier_BattlePyramidLobby_Text_HintNormal_hns:
	.string "אני רואה פוקימונים מסוג רגיל…\p"
	.string "…ואני רואה את הפוקימונים שלך\n"
	.string "סובלים ממהלכים עוצמתיים להפליא…$"

BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot_hns:
	.string "אם להאמין לנבואות שלי או לא,\n"
	.string "הבחירה בידיך…\p"
	.string "את העתיד אפשר לשנות בכל עת…\n"
	.string "אני מאחלת לך דרך צלחה…$"

BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning_hns:
	.string "ידעת?\p"
	.string "אם רצים מהר, מאמנים עלולים לשים לב\n"
	.string "ולבוא אחריך לקרב.\p"
	.string "אז אם רוצים להימנע ממאמנים,\n"
	.string "לא כדאי למשוך את תשומת ליבם.\p"
	.string "עדיף לחמוק על פניהם\n"
	.string "בזהירות ובשקט.$"

BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems_hns:
	.string "אוווווווייייייי!\p"
	.string "היו לי המון פריטים, אבל כשהפסדתי\n"
	.string "הפסדתי את כולם!\p"
	.string "אוווווווייייייי!$"

BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing_hns:
	.string "ברוכים השבים!\n"
	.string "עשית את הבלתי ייאמן!\p"
	.string "ניצחת את מלך הפירמידה\n"
	.string "וכבשת את פירמידת הקרב!$"

BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints_hns:
	.string "חוקר צעיר! כאות הוקרה על האומץ שלך,\n"
	.string "אנו מעניקים לך את נקודות הקרב האלה!$"

BattleFrontier_BattlePyramidLobby_Text_RulesAreListed_hns:
	.string "כאן מפורטים חוקי מסע הקרב.$"

BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading_hns:
	.string "על איזה נושא לקרוא?$"

BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules_hns:
	.string "כשהפירמידה נכבשת, הפוקימונים הפראיים\n"
	.string "שמופיעים בה מתחלפים במינים אחרים.\p"
	.string "כדאי לחקור, להתבונן וללמוד אילו\n"
	.string "מיני פוקימונים פראיים עשויים להופיע.$"

BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules_hns:
	.string "בתוך הפירמידה מאמנים\n"
	.string "אורבים לך.\p"
	.string "בכל קומה יש עד\n"
	.string "שמונה מאמנים.\p"
	.string "על כל ניצחון על מאמן מקבלים\n"
	.string "רמז שימושי להרפתקה.$"

BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules_hns:
	.string "המבוכים בפירמידה משתנים\n"
	.string "בכל פעם שנכנסים אליה.\p"
	.string "המבוכים מוארים בקושי.\n"
	.string "יש להתקדם בזהירות.\p"
	.string "האור מתחזק בכל פעם שמנצחים\n"
	.string "פוקימון פראי או מאמן.$"

BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules_hns:
	.string "בפירמידה, תיק הקרב משמש\n"
	.string "בתור התיק שלך.\p"
	.string "יש שני תיקי קרב נפרדים - אחד להרפתקאות\n"
	.string "ברמה 50 ואחד להרפתקאות ברמה פתוחה.\p"
	.string "כל אחד מהם מכיל עד עשרה סוגי פריטים,\n"
	.string "ועד 99 יחידות מכל סוג.\p"
	.string "התוכן של תיק הקרב אובד\n"
	.string "במקרה של כישלון במסע.$"

