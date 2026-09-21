BattleFrontier_BattlePyramidLobby_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidLobby_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleDomeLobby_OnWarp
	.byte 0

@ Unused. Pyramid uses Dome's OnWarp (presumably by mistake). Their effects are identical
BattleFrontier_BattlePyramidLobby_OnWarp:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePyramidLobby_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattlePyramidLobby_EventScript_TurnPlayerNorth:
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePyramidLobby_OnFrame:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattlePyramidLobby_EventScript_GetChallengeStatus
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramidLobby_EventScript_QuitWithoutSaving
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidLobby_EventScript_ResumeChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattlePyramidLobby_EventScript_WonChallenge
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePyramidLobby_EventScript_LostChallenge
	.2byte 0

BattleFrontier_BattlePyramidLobby_EventScript_GetChallengeStatus::
	frontier_getstatus
	end

BattleFrontier_BattlePyramidLobby_EventScript_QuitWithoutSaving::
	lockall
	message BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag
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

BattleFrontier_BattlePyramidLobby_EventScript_WonChallenge::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_DefeatedKing
	msgbox BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_GiveBattlePoints

BattleFrontier_BattlePyramidLobby_EventScript_DefeatedKing::
	msgbox BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_GiveBattlePoints::
	special DoBattlePyramidMonsHaveHeldItem
	call_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_StoreHeldItemsInPyramidBag
	clearflag FLAG_STORING_ITEMS_IN_PYRAMID_BAG
	frontier_checkairshow
	special LoadPlayerParty
	pyramid_clearhelditems
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	message BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept
	waitmessage
	playse SE_EXP_MAX
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait
	waitmessage
	pyramid_setprize
	pyramid_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_LostChallenge::
	frontier_checkairshow
	special LoadPlayerParty
	pyramid_clearhelditems
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	lockall
	message BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	message BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait
	waitmessage
	pyramid_set PYRAMID_DATA_WIN_STREAK_ACTIVE, FALSE
	pyramid_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_ResumeChallenge::
	goto BattleFrontier_BattlePyramidLobby_EventScript_EnterChallenge

BattleFrontier_BattlePyramidLobby_EventScript_Attendant::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PYRAMID
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattlePyramidLobby_Text_WelcomeToBattlePyramid, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_AskTakeChallenge::
	message BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_ExplainChallenge
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_TryEnterChallenge::
	message BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge
	msgbox BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge
	case YES, BattleFrontier_BattlePyramidLobby_EventScript_SaveBeforeChallenge
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_SaveBeforeChallenge::
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
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_CancelChallengeSaveFailed
BattleFrontier_BattlePyramidLobby_EventScript_EnterChallenge::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid, MSGBOX_DEFAULT
	closemessage
	call BattleFrontier_BattlePyramidLobby_EventScript_WalkToPanelAndReceiveBag
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_RESULT, 0
	special HealPlayerParty
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR, 1, 1
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExplainChallenge::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_AskTakeChallenge

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMons::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLvOpen

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLv50::
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_NotEnoughValidMonsLvOpen::
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsEnd, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_CancelChallengeSaveFailed::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge

BattleFrontier_BattlePyramidLobby_EventScript_LoadPartyAndCancelChallenge::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattlePyramidLobby_EventScript_CancelChallenge::
	msgbox BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_EndCancelChallenge::
	release
	end

BattleFrontier_BattlePyramidLobby_EventScript_HintGiver::
	lockall
	applymovement LOCALID_PYRAMID_LOBBY_HINT_GIVER, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait, MSGBOX_DEFAULT
	call BattleFrontier_BattlePyramidLobby_EventScript_GiveHint
	msgbox BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot, MSGBOX_DEFAULT
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_GiveHint::
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLv50
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLvOpen
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePyramidLobby_EventScript_NoHint
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_NoHint
	return

@ Shouldnt occur
BattleFrontier_BattlePyramidLobby_EventScript_NoHint::
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLv50::
	msgbox BattleFrontier_BattlePyramidLobby_Text_Aah, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK_ACTIVE_50
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLv50Streak
	setvar VAR_RESULT, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLv50Streak::
	pyramid_get PYRAMID_DATA_WIN_STREAK_50
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintLvOpen::
	msgbox BattleFrontier_BattlePyramidLobby_Text_Aah, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK_ACTIVE_OPEN
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLvOpenStreak
	setvar VAR_RESULT, 0
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_GiveHintGetLvOpenStreak::
	pyramid_get PYRAMID_DATA_WIN_STREAK_OPEN
	goto BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment
	return

BattleFrontier_BattlePyramidLobby_EventScript_DoHintComment::
	copyvar VAR_0x8004, VAR_RESULT
	special GetBattlePyramidHint
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_HintParalysis
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_HintPoison
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_HintBurn
	case 3, BattleFrontier_BattlePyramidLobby_EventScript_HintPPWaste
	case 4, BattleFrontier_BattlePyramidLobby_EventScript_HintLevitate
	case 5, BattleFrontier_BattlePyramidLobby_EventScript_HintTrapAbility
	case 6, BattleFrontier_BattlePyramidLobby_EventScript_HintIce
	case 7, BattleFrontier_BattlePyramidLobby_EventScript_HintExplosion
	case 8, BattleFrontier_BattlePyramidLobby_EventScript_HintPsychic
	case 9, BattleFrontier_BattlePyramidLobby_EventScript_HintRock
	case 10, BattleFrontier_BattlePyramidLobby_EventScript_HintFighting
	case 11, BattleFrontier_BattlePyramidLobby_EventScript_HintWeather
	case 12, BattleFrontier_BattlePyramidLobby_EventScript_HintBug
	case 13, BattleFrontier_BattlePyramidLobby_EventScript_HintDark
	case 14, BattleFrontier_BattlePyramidLobby_EventScript_HintWater
	case 15, BattleFrontier_BattlePyramidLobby_EventScript_HintGhost
	case 16, BattleFrontier_BattlePyramidLobby_EventScript_HintSteel
	case 17, BattleFrontier_BattlePyramidLobby_EventScript_HintFlyingDragon
	case 18, BattleFrontier_BattlePyramidLobby_EventScript_HintStoneEvolve
	case 19, BattleFrontier_BattlePyramidLobby_EventScript_HintNormal
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintParalysis::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintParalysis, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPoison::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPoison, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintBurn::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintBurn, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPPWaste::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPPWaste, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintLevitate::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintLevitate, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintTrapAbility::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintIce::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintIce, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintExplosion::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintExplosion, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintPsychic::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintPsychic, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintRock::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintRock, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintFighting::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintFighting, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintWeather::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintWeather, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintBug::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintBug, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintDark::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintDark, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintWater::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintWater, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintGhost::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintGhost, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintSteel::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintSteel, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintFlyingDragon::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintStoneEvolve::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_HintNormal::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HintNormal, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePyramidLobby_EventScript_ShowResults::
	lockall
	frontier_results FRONTIER_FACILITY_PYRAMID
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePyramidLobby_EventScript_WalkToPanelAndReceiveBag::
	applymovement LOCALID_PYRAMID_LOBBY_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel
	waitmovement 0
	msgbox BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping, MSGBOX_DEFAULT
	pyramid_get PYRAMID_DATA_WIN_STREAK
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_ReceiveNewBattleBag
	msgbox BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReceiveBattleBag

BattleFrontier_BattlePyramidLobby_EventScript_ReceiveNewBattleBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag, MSGBOX_DEFAULT
BattleFrontier_BattlePyramidLobby_EventScript_ReceiveBattleBag::
	message BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag
	waitmessage
	playse SE_EXP_MAX
	waitse
	msgbox BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PYRAMID_LOBBY_ATTENDANT, BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside
	waitmovement 0
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel
	waitmovement 0
	return

BattleFrontier_BattlePyramidLobby_Movement_AttendantWalkToPanel:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_down
	step_end

BattleFrontier_BattlePyramidLobby_Movement_PlayerWalkToPanel:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePyramidLobby_Movement_AttendantMoveAside:
	walk_right
	face_left
	step_end

BattleFrontier_BattlePyramidLobby_Movement_PlayerStepOnPanel:
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePyramidLobby_EventScript_StoreHeldItemsInPyramidBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake, MSGBOX_DEFAULT
	setflag FLAG_STORING_ITEMS_IN_PYRAMID_BAG
	special TryStoreHeldItemsInPyramidBag
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidLobby_EventScript_HeldItemsStoredInPyramidBag
	message BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_HeldItemsStoredInPyramidBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag, MSGBOX_DEFAULT
	return

@ When exiting Battle Pyramid with a full pyramid bag and held items the player must select to keep/toss party held items and make room for any kept items by tossing from the pyramid bag
BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep::
	multichoice 17, 6, MULTI_FRONTIER_ITEM_CHOOSE, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromBag
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromParty
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems
	end

BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromBag::
	special ChooseItemsToTossFromPyramidBag
	waitstate
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_PickItemsFromParty::
	special BattlePyramidChooseMonHeldItems
	waitstate
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExitPickItems::
	special DoBattlePyramidMonsHaveHeldItem
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePyramidLobby_EventScript_PartyStillHasHeldItems
	return

BattleFrontier_BattlePyramidLobby_EventScript_PartyStillHasHeldItems::
	msgbox BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem, MSGBOX_DEFAULT
	message BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep
	waitmessage
	goto BattleFrontier_BattlePyramidLobby_EventScript_PickItemsToKeep
	end

BattleFrontier_BattlePyramidLobby_EventScript_Woman::
	msgbox BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning, MSGBOX_NPC
	end

BattleFrontier_BattlePyramidLobby_EventScript_FatMan::
	msgbox BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems, MSGBOX_NPC
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesBoard::
	lockall
	msgbox BattleFrontier_BattlePyramidLobby_Text_RulesAreListed, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard::
	message BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading
	waitmessage
	multichoice 15, 2, MULTI_BATTLE_PYRAMID_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePyramidLobby_EventScript_RulesPokemon
	case 1, BattleFrontier_BattlePyramidLobby_EventScript_RulesTrainers
	case 2, BattleFrontier_BattlePyramidLobby_EventScript_RulesMaze
	case 3, BattleFrontier_BattlePyramidLobby_EventScript_RulesBag
	case 4, BattleFrontier_BattlePyramidLobby_EventScript_ExitRules
	case MULTI_B_PRESSED, BattleFrontier_BattlePyramidLobby_EventScript_ExitRules
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesPokemon::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesTrainers::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesMaze::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_RulesBag::
	msgbox BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePyramidLobby_EventScript_ReadRulesBoard
	end

BattleFrontier_BattlePyramidLobby_EventScript_ExitRules::
	releaseall
	end

BattleFrontier_BattlePyramidLobby_Text_WelcomeToBattlePyramid:
	.string "Donde el valor de los ENTRENADORES\n"
	.string "ENTRENADORES es puesto a prueba!\p"
	.string "¡Bienvenido a la PIRÁMIDE BATALLA!\p"
	.string "Soy tu guía para\n"
	.string "la Búsqueda de Batalla.$"

BattleFrontier_BattlePyramidLobby_Text_EmbarkOnChallenge:
	.string "¿Tienes el valor de iniciar el\n"
	.string "desafío de la Búsqueda de Batalla?$"

BattleFrontier_BattlePyramidLobby_Text_AwaitFutureChallenge:
	.string "¡Esperamos tu desafío en el futuro!$"

BattleFrontier_BattlePyramidLobby_Text_ExplainBattlePyramid:
	.string "La Búsqueda de Batalla es un evento\n"
	.string "donde deberás explorar la\l"
	.string "PIRÁMIDE e intentar llegar arriba.\p"
	.string "En la PIRÁMIDE hay siete pisos de\n"
	.string "laberintos, llenos no solo de\l"
	.string "ENTRENADORES y POKéMON salvajes.\p"
	.string "Debes entrar con tres POKéMON,\n"
	.string "ninguno puede llevar un objeto.\p"
	.string "Al subir, se te dará una\n"
	.string "Bolsa de Batalla para objetos.\p"
	.string "Si fallas el desafío, cualquier\n"
	.string "objeto en la bolsa desaparecerá.\p"
	.string "Si quieres interrumpir tu\n"
	.string "reto, debes elegir “DESCANSAR”\l"
	.string "y guarda la partida.\p"
	.string "Si no guardas antes de interrumpir,\n"
	.string "quedarás descalificado.$"

BattleFrontier_BattlePyramidLobby_Text_WhichLevelMode:
	.string "La PIRÁMIDE ofrece dos rutas,\n"
	.string "Nivel 50 y Nivel Abierto.\l"
	.string "¿En cuál entrarás?$"

BattleFrontier_BattlePyramidLobby_Text_SelectThreeMons:
	.string "Muy bien. Ahora, elige los tres\n"
	.string "POKéMON que quieres que te acompañen.$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLvOpen:
	.string "¡Un pequeño problema, aventurero!\p"
	.string "Parece que no tienes los tres\n"
	.string "POKéMON aptos para el desafío.\p"
	.string "Recuerda también quitarles todos\n"
	.string "los objetos a tus POKéMON.\p"
	.string "HUEVOS{STR_VAR_1}.$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsLv50:
	.string "¡Un pequeño problema, aventurero!\p"
	.string "Parece que no tienes los tres\n"
	.string "POKéMON aptos para el desafío.\p"
	.string "Los tres POKéMON deben ser distintos\n"
	.string "y ninguno puede superar el nivel 50.\p"
	.string "Recuerda también quitarles todos\n"
	.string "los objetos a tus POKéMON.\p"
	.string "HUEVOS{STR_VAR_1}.$"

BattleFrontier_BattlePyramidLobby_Text_NotEnoughValidMonsEnd:
	.string "Cuando estés listo, por favor\n"
	.string "habla conmigo.$"

BattleFrontier_BattlePyramidLobby_Text_OkayToSaveBeforeChallenge:
	.string "Antes de entrar a la PIRÁMIDE BATALLA,\n"
	.string "debes guardar la partida. ¿Está bien?$"

BattleFrontier_BattlePyramidLobby_Text_ShowYouIntoPyramid:
	.string "Muy bien. Ahora te mostraré la\n"
	.string "PIRÁMIDE BATALLA.$"

BattleFrontier_BattlePyramidLobby_Text_WeWillHoldBagForSafekeeping:
	.string "Guardaremos tu MOCHILA por seguridad,\n"
	.string "{PLAYER}, mientras exploras.$"

BattleFrontier_BattlePyramidLobby_Text_PleaseTakePreviousBattleBag:
	.string "A cambio, toma esta MOCHILA BATALLA,\n"
	.string "la misma que usaste antes.$"

BattleFrontier_BattlePyramidLobby_Text_PleaseTakeThisBattleBag:
	.string "A cambio, por favor toma esta\n"
	.string "MOCHILA BATALLA.$"

BattleFrontier_BattlePyramidLobby_Text_ExchangedBagForBattleBag:
	.string "{PLAYER} cambió la MOCHILA por la\n"
	.string "MOCHILA BATALLA.$"

BattleFrontier_BattlePyramidLobby_Text_StepOnFloorPanel:
	.string "Cuando pises este panel del suelo,\n"
	.string "serás transportado a un piso superior\l"
	.string "piso de la PIRÁMIDE.\p"
	.string "¡Espero que tu\n"
	.string "misión sea segura!$"

BattleFrontier_BattlePyramidLobby_Text_DidntSaveBeforeQuittingTakeBag:
	.string "¡Un gran problema, explorador!\p"
	.string "No guardaste antes de salir.\n"
	.string "tu desafío la última vez.\p"
	.string "Por eso, tu desafío ha sido\n"
	.string "descalificado, lo siento mucho.\p"
	.string "Aquí tienes la BOLSA que\n"
	.string "estábamos guardando.\p"
	.string "{PLAYER} recuperó la BOLSA.$"

BattleFrontier_BattlePyramidLobby_Text_YouveConqueredPyramid:
	.string "¡Qué alegría verte de vuelta!\p"
	.string "¡Conquistaste la PIRÁMIDE!\n"
	.string "¡Qué espléndido!$"

BattleFrontier_BattlePyramidLobby_Text_MonHoldingItemCannotTake:
	.string "Ah, hay un pequeño problema.\p"
	.string "Al menos un POKéMON lleva\n"
	.string "un objeto.\p"
	.string "Lamento decir que los objetos de la\n"
	.string "PIRÁMIDE no pueden retirarse.$"

BattleFrontier_BattlePyramidLobby_Text_HeldItemsMovedToBag:
	.string "Los objetos de tus POKéMON irán a la\n"
	.string "BOLSA DE COMBATE, {PLAYER}.$"

BattleFrontier_BattlePyramidLobby_Text_BagCannotHoldPickItemsToKeep:
	.string "La BOLSA DE COMBATE no tiene espacio\n"
	.string "para todo, lo lamento.\p"
	.string "Elige qué objetos dejarás en la\n"
	.string "BOLSA y cuáles con tus POKéMON.$"

BattleFrontier_BattlePyramidLobby_Text_LeastOneMonHoldingItem:
	.string "Al menos un POKéMON todavía\n"
	.string "lleva un objeto.$"

BattleFrontier_BattlePyramidLobby_Text_PickItemsToKeep:
	.string "Elige qué objetos dejarás en la\n"
	.string "BOLSA y cuáles con tus POKéMON.$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ReturnedEverythingMonsHeld:
	.string "{PLAYER} recuperó todo lo que\n"
	.string "llevaban los POKéMON.$"

BattleFrontier_BattlePyramidLobby_Text_UsedBattleBagWillBeKept:
	.string "La BATTLE BAG que usaste quedará\n"
	.string "lista para tu próximo desafío.\p"
	.string "{PLAYER} devolvió la BATTLE BAG\n"
	.string "para recuperar su BAG.$"

BattleFrontier_BattlePyramidLobby_Text_RecordResultsWait:
	.string "Debo registrar tus resultados.\n"
	.string "Please wait.$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ForConqueringPyramidTakeThis:
	.string "Como recuerdo por conquistar la\n"
	.string "BATTLE PYRAMID, toma esto.$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_ReceivedPrizeItem:
	.string "{PLAYER} recibió el premio\n"
	.string "{STR_VAR_1}.$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_BagIsFull:
	.string "…Ah…\n"
	.string "Tu BAG parece estar llena.\p"
	.string "Vuelve cuando hayas organizado\n"
	.string "el contenido de tu MOCHILA.$"

BattleFrontier_BattlePyramidLobby_Text_DisappointingHereIsBag:
	.string "Qué decepcionante para ti...\p"
	.string "Aquí tienes la BOLSA que\n"
	.string "estábamos guardando.\p"
	.string "{PLAYER} recuperó la BOLSA.$"

BattleFrontier_BattlePyramidLobby_Text_LookForwardToNextChallenge:
	.string "¡Esperamos con ansias tu\n"
	.string "próximo desafío!$"

@ Unused
BattleFrontier_BattlePyramidLobby_Text_HereIsPrize:
	.string "Hemos estado esperando\n"
	.string "¡tu llegada!\p"
	.string "Aquí tienes tu premio por vencer\n"
	.string "la PIRÁMIDE.$"

BattleFrontier_BattlePyramidLobby_Text_TellYouWhatMisfortunesAwait:
	.string "Bienvenido...\p"
	.string "Me dará gusto decirte qué\n"
	.string "desgracias hay en la PIRÁMIDE...$"

BattleFrontier_BattlePyramidLobby_Text_Aah:
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "… … … … … …\n"
	.string "¡Aah!$"

BattleFrontier_BattlePyramidLobby_Text_HintParalysis:
	.string "Veo una lluvia de chispas...\p"
	.string "...Y en él, veo a tu POKéMON\n"
	.string "luchando contra la parálisis...$"

BattleFrontier_BattlePyramidLobby_Text_HintPoison:
	.string "Veo veneno...\p"
	.string "...Y veo a tu POKéMON sufriendo\n"
	.string "por los efectos del veneno...$"

BattleFrontier_BattlePyramidLobby_Text_HintBurn:
	.string "Veo llamas rojas brillantes...\p"
	.string "...Y veo a tu POKéMON sufriendo\n"
	.string "por quemaduras...$"

BattleFrontier_BattlePyramidLobby_Text_HintPPWaste:
	.string "Siento la tremenda presión de\n"
	.string "una ira no correspondida...\p"
	.string "Es una maldición...\p"
	.string "...Y veo a tu POKéMON sin\n"
	.string "Puntos de Poder y sin recursos\l"
	.string "pero usar LUCHA…$"

BattleFrontier_BattlePyramidLobby_Text_HintLevitate:
	.string "Veo POKéMON volando muy alto…\p"
	.string "…Y veo a tu POKéMON frustrado\n"
	.string "por ataques TIPO TIERRA inútiles…$"

BattleFrontier_BattlePyramidLobby_Text_HintTrapAbility:
	.string "Siento una energía tremenda subir\n"
	.string "desde el suelo…\p"
	.string "…Y veo a tu POKéMON incapaz de\n"
	.string "escapar de ese poder…$"

BattleFrontier_BattlePyramidLobby_Text_HintIce:
	.string "Veo POKéMON TIPO HIELO…\p"
	.string "…Y veo a tu POKéMON luchando\n"
	.string "contra los efectos del hielo…$"

BattleFrontier_BattlePyramidLobby_Text_HintExplosion:
	.string "Veo una ráfaga de ataques peligrosos\n"
	.string "el usuario…\p"
	.string "…Y veo a tu POKéMON caer\n"
	.string "ante ellos…$"

BattleFrontier_BattlePyramidLobby_Text_HintPsychic:
	.string "Veo POKéMON tipo PSÍQUICO…\p"
	.string "…Y veo a tu POKéMON sufriendo\n"
	.string "por ataques PSÍQUICOS…$"

BattleFrontier_BattlePyramidLobby_Text_HintRock:
	.string "Veo POKéMON tipo ROCA…\p"
	.string "...Y veo a tu POKéMON sufriendo\n"
	.string "por ataques ROCA…$"

BattleFrontier_BattlePyramidLobby_Text_HintFighting:
	.string "Veo POKéMON tipo LUCHA…\p"
	.string "…Y veo a tu POKéMON golpeado\n"
	.string "por ataques de LUCHA…$"

BattleFrontier_BattlePyramidLobby_Text_HintWeather:
	.string "DANZA LUVIA… DÍA SOLEADO…\n"
	.string "TORMENTA DE ARENA... GRANIZO...\p"
	.string "Veo POKéMON que se hacen fuertes\n"
	.string "con el clima...\p"
	.string "...Y veo a tus POKéMON confundidos\n"
	.string "por distintos tipos de ataques...$"

BattleFrontier_BattlePyramidLobby_Text_HintBug:
	.string "Veo POKéMON tipo BICHOS...\p"
	.string "...Y veo a tu POKéMON sufriendo\n"
	.string "ante diversos tipos de ataques...$"

BattleFrontier_BattlePyramidLobby_Text_HintDark:
	.string "Veo POKéMON tipo SIN DIESTRO...\p"
	.string "...Y veo a tu POKéMON sufriendo\n"
	.string "ante ataques tipo SIN DIESTRO...$"

BattleFrontier_BattlePyramidLobby_Text_HintWater:
	.string "Veo POKéMON tipo AGUA...\p"
	.string "...Y veo a tu POKéMON sufriendo\n"
	.string "ante ataques tipo AGUA...$"

BattleFrontier_BattlePyramidLobby_Text_HintGhost:
	.string "Veo POKéMON tipo FANTASMA...\p"
	.string "...Y veo a tu POKéMON sufriendo\n"
	.string "de los ataques tipo FANTASMA…$"

BattleFrontier_BattlePyramidLobby_Text_HintSteel:
	.string "Veo POKéMON tipo ACERO…\p"
	.string "...Y veo a tu POKéMON sufriendo\n"
	.string "de ataques muy poderosos…$"

BattleFrontier_BattlePyramidLobby_Text_HintFlyingDragon:
	.string "Veo POKéMON voladores…\p"
	.string "...Y veo a tu POKéMON sufriendo\n"
	.string "de ataques muy poderosos…$"

BattleFrontier_BattlePyramidLobby_Text_HintStoneEvolve:
	.string "Veo a los que han evolucionado por\n"
	.string "el poder de las piedras…\p"
	.string "También siento fuego, agua,\n"
	.string "y electricidad…\p"
	.string "...Y veo a tu POKéMON sufriendo\n"
	.string "de esos tres poderes…$"

BattleFrontier_BattlePyramidLobby_Text_HintNormal:
	.string "Veo POKéMON tipo NORMAL…\p"
	.string "...Y veo a tu POKéMON sufriendo\n"
	.string "de ataques muy poderosos…$"

BattleFrontier_BattlePyramidLobby_Text_BelieveMyFortunesOrNot:
	.string "Si crees en mis predicciones\n"
	.string "o no, la decisión es tuya…\p"
	.string "El futuro puede cambiar siempre…\n"
	.string "Deseo que tengas un viaje seguro…$"

BattleFrontier_BattlePyramidLobby_Text_TrainersNoticeRunning:
	.string "¿Sabías esto?\p"
	.string "Si corres, los ENTRENADORES pueden\n"
	.string "notarlo y venir a luchar contigo.\p"
	.string "Así que, para evitar ENTRENADORES,\n"
	.string "no los mires, mejor escabullirte\l"
	.string "con cuidado y en silencio.$"

BattleFrontier_BattlePyramidLobby_Text_LostLotOfItems:
	.string "¡Awaaaaaaarrrrgh!\p"
	.string "Tenía muchos objetos, ¡pero los\n"
	.string "perdí todos al ser derrotado!\p"
	.string "¡Awaaaaaaarrrrgh!$"

BattleFrontier_BattlePyramidLobby_Text_YouveDefeatedPyramidKing:
	.string "¡Bienvenido de nuevo!\n"
	.string "¡Hiciste lo impensable!\p"
	.string "Derrotaste al REY DE LA PIRÁMIDE\n"
	.string "¡y conquistó la PIRÁMIDE BATALLA!$"

BattleFrontier_BattlePyramidLobby_Text_GiveYouTheseBattlePoints:
	.string "¡Joven explorador!\n"
	.string "En honor a tu gran valentía,\l"
	.string "¡te damos estos Puntos de Combate!$"

BattleFrontier_BattlePyramidLobby_Text_RulesAreListed:
	.string "Las reglas de Battle Quest se listan.$"

BattleFrontier_BattlePyramidLobby_Text_ReadWhichHeading:
	.string "¿Qué sección quieres leer?$"

BattleFrontier_BattlePyramidLobby_Text_ExplainMonRules:
	.string "Cuando la PIRÁMIDE es conquistada,\n"
	.string "los POKéMON salvajes que aparecen\l"
	.string "son reemplazados por otros tipos.\p"
	.string "Explora y aprende qué tipos son\n"
	.string "de POKéMON salvajes que hallarás.$"

BattleFrontier_BattlePyramidLobby_Text_ExplainTrainerRules:
	.string "Hay ENTRENADORES esperándote\n"
	.string "dentro de la PIRÁMIDE.\p"
	.string "En cada piso, hay hasta\n"
	.string "ocho ENTRENADORES.\p"
	.string "Al vencer a un ENTRENADOR, recibirás\n"
	.string "una pista útil para tu aventura.$"

BattleFrontier_BattlePyramidLobby_Text_ExplainMazeRules:
	.string "Los laberintos de la PIRÁMIDE cambian\n"
	.string "cada vez que entras en ella.\p"
	.string "Los laberintos están mal iluminados.\n"
	.string "Debes avanzar con precaución.\p"
	.string "La luz brilla más cuando\n"
	.string "vence a un POKéMON o ENTRENADOR.$"

BattleFrontier_BattlePyramidLobby_Text_ExplainBagRules:
	.string "La BATTLE BAG sirve como tu MOCHILA\n"
	.string "mientras estés en la PIRÁMIDE.\p"
	.string "Hay dos BATTLE BAG separadas--\n"
	.string "una para el Nivel 50 y otra para\l"
	.string "las aventuras de Nivel Abierto.\p"
	.string "Cada una puede llevar hasta 99\n"
	.string "objetos de diez tipos distintos.\p"
	.string "El contenido de la BATTLE BAG se\n"
	.string "perderá si fallas en tu misión.$"

