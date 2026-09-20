Route110_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Route110_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route110_OnFrame
	.byte 0

Route110_OnResume:
	special UpdateCyclingRoadState
	end

Route110_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	call_if_eq VAR_CYCLING_CHALLENGE_STATE, 1, Route110_EventScript_SaveCyclingMusic
	end

Route110_EventScript_SaveCyclingMusic::
	savebgm MUS_CYCLING
	return

Route110_OnFrame:
	map_script_2 VAR_CYCLING_CHALLENGE_STATE, 1, Route110_EventScript_BeginCylcingRoadChallenge
	.2byte 0

Route110_EventScript_BeginCylcingRoadChallenge::
	special Special_BeginCyclingRoadChallenge
	setvar VAR_CYCLING_CHALLENGE_STATE, 2
	return

Route110_EventScript_AquaGrunt1::
	lock
	faceplayer
	msgbox Route110_Text_WeCantTalkAboutAquaActivities, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route110_EventScript_AquaGrunt2::
	lock
	faceplayer
	msgbox Route110_Text_KickUpARuckus, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route110_EventScript_AquaGrunt3::
	lock
	faceplayer
	msgbox Route110_Text_MyFirstJobInAqua, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route110_EventScript_AquaGrunt4::
	lock
	faceplayer
	msgbox Route110_Text_AquaActionsBringSmiles, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route110_EventScript_Boy1::
	msgbox Route110_Text_RideBikeAtFullSpeed, MSGBOX_NPC
	end

Route110_EventScript_CyclingGirl1::
	msgbox Route110_Text_HairStreamsBehindMe, MSGBOX_NPC
	end

Route110_EventScript_CyclingGuy1::
	msgbox Route110_Text_YouGotBikeFromRydel, MSGBOX_NPC
	end

Route110_EventScript_OldMan::
	msgbox Route110_Text_TwoRoads, MSGBOX_NPC
	end

Route110_EventScript_OldWoman::
	msgbox Route110_Text_WalkOnTheLowRoad, MSGBOX_NPC
	end

Route110_EventScript_CyclingGuy2::
	msgbox Route110_Text_BikeTechniques, MSGBOX_NPC
	end

Route110_EventScript_Boy2::
	msgbox Route110_Text_WhichShouldIChoose, MSGBOX_NPC
	end

Route110_EventScript_SlateportCitySign::
	msgbox Route110_Text_SlateportCitySign, MSGBOX_SIGN
	end

Route110_EventScript_CyclingRoadSign::
	msgbox Route110_Text_CyclingRoadSign, MSGBOX_SIGN
	end

Route110_EventScript_VandalizedSign::
	msgbox Route110_Text_AquaWasHere, MSGBOX_SIGN
	end

Route110_EventScript_Route103Sign::
	msgbox Route110_Text_Route103Sign, MSGBOX_SIGN
	end

Route110_EventScript_SeasideParkingSign::
	msgbox Route110_Text_SeasideParkingSign, MSGBOX_SIGN
	end

Route110_EventScript_MauvilleCitySign::
	msgbox Route110_Text_MauvilleCitySign, MSGBOX_SIGN
	end

Route110_EventScript_TrainerTipsPrlzSleep::
	msgbox Route110_Text_TrainerTipsPrlzSleep, MSGBOX_SIGN
	end

Route110_EventScript_TrainerTipsRegisterItems::
	msgbox Route110_Text_TrainerTipsRegisterItems, MSGBOX_SIGN
	end

Route110_EventScript_TrickHouseSign::
	msgbox Route110_Text_TrickHouseSign, MSGBOX_SIGN
	end

Route110_EventScript_CyclingRoadResultsSign::
	lockall
	specialvar VAR_RESULT, GetRecordedCyclingRoadResults
	goto_if_eq VAR_RESULT, FALSE, Route110_EventScript_NoRecordSet
	msgbox Route110_Text_BestRecord, MSGBOX_DEFAULT
	releaseall
	end

Route110_EventScript_NoRecordSet::
	msgbox Route110_Text_ThereIsNoRecord, MSGBOX_DEFAULT
	releaseall
	end

Route110_EventScript_ChallengeGuy::
	lock
	faceplayer
	specialvar VAR_RESULT, GetPlayerAvatarBike
	goto_if_eq VAR_RESULT, 1, Route110_EventScript_PlayerRidingAcroBike
	goto_if_eq VAR_CYCLING_CHALLENGE_STATE, 0, Route110_EventScript_PlayerNotRidingBike
	msgbox Route110_Text_AlwaysAimHigher, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_PlayerNotRidingBike::
	msgbox Route110_Text_RatedForNumberOfCollisions, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_PlayerRidingAcroBike::
	msgbox Route110_Text_AcroBikesDoNotQualify, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_Edward::
	trainerbattle_single TRAINER_EDWARD, Route110_Text_EdwardIntro, Route110_Text_EdwardDefeated
	msgbox Route110_Text_EdwardPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Jaclyn::
	trainerbattle_single TRAINER_JACLYN, Route110_Text_JaclynIntro, Route110_Text_JaclynDefeated
	msgbox Route110_Text_JaclynPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Edwin::
	trainerbattle_single TRAINER_EDWIN_1, Route110_Text_EdwinIntro, Route110_Text_EdwinDefeated, Route110_EventScript_EdwinRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route110_EventScript_EdwinRematch
	msgbox Route110_Text_EdwinPostBattle, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_EdwinRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route110_Text_EdwinRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_EDWIN_1
	release
	end

Route110_EventScript_EdwinRematch::
	trainerbattle_rematch TRAINER_EDWIN_1, Route110_Text_EdwinRematchIntro, Route110_Text_EdwinRematchDefeated
	msgbox Route110_Text_EdwinRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Dale::
	trainerbattle_single TRAINER_DALE, Route110_Text_DaleIntro, Route110_Text_DaleDefeated
	msgbox Route110_Text_DalePostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Jacob::
	trainerbattle_single TRAINER_JACOB, Route110_Text_JacobIntro, Route110_Text_JacobDefeated
	msgbox Route110_Text_JacobPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Anthony::
	trainerbattle_single TRAINER_ANTHONY, Route110_Text_AnthonyIntro, Route110_Text_AnthonyDefeated
	msgbox Route110_Text_AnthonyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Benjamin::
	trainerbattle_single TRAINER_BENJAMIN_1, Route110_Text_BenjaminIntro, Route110_Text_BenjaminDefeated, Route110_EventScript_BenjaminRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route110_EventScript_BenjaminRematch
	msgbox Route110_Text_BenjaminPostBattle, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_BenjaminRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route110_Text_BenjaminRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_BENJAMIN_1
	release
	end

Route110_EventScript_BenjaminRematch::
	trainerbattle_rematch TRAINER_BENJAMIN_1, Route110_Text_BenjaminRematchIntro, Route110_Text_BenjaminRematchDefeated
	msgbox Route110_Text_BenjaminRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Jasmine::
	trainerbattle_single TRAINER_JASMINE, Route110_Text_JasmineIntro, Route110_Text_JasmineDefeated
	msgbox Route110_Text_JasminePostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Abigail::
	trainerbattle_single TRAINER_ABIGAIL_1, Route110_Text_AbigailIntro, Route110_Text_AbigailDefeated, Route110_EventScript_AbigailRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route110_EventScript_AbigailRematch
	msgbox Route110_Text_AbigailPostBattle, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_AbigailRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route110_Text_AbigailRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ABIGAIL_1
	release
	end

Route110_EventScript_AbigailRematch::
	trainerbattle_rematch TRAINER_ABIGAIL_1, Route110_Text_AbigailRematchIntro, Route110_Text_AbigailRematchDefeated
	msgbox Route110_Text_AbigailRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Isabel::
	trainerbattle_single TRAINER_ISABEL_1, Route110_Text_IsabelIntro, Route110_Text_IsabelDefeated, Route110_EventScript_IsabelRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route110_EventScript_IsabelRematch
	msgbox Route110_Text_IsabelPostBattle, MSGBOX_DEFAULT
	release
	end

Route110_EventScript_IsabelRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route110_Text_IsabelRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ISABEL_1
	release
	end

Route110_EventScript_IsabelRematch::
	trainerbattle_rematch TRAINER_ISABEL_1, Route110_Text_IsabelRematchIntro, Route110_Text_IsabelRematchDefeated
	msgbox Route110_Text_IsabelRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Timmy::
	trainerbattle_single TRAINER_TIMMY, Route110_Text_TimmyIntro, Route110_Text_TimmyDefeated
	msgbox Route110_Text_TimmyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Unused::
	end

Route110_EventScript_Kaleb::
	trainerbattle_single TRAINER_KALEB, Route110_Text_KalebIntro, Route110_Text_KalebDefeated
	msgbox Route110_Text_KalebPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Joseph::
	trainerbattle_single TRAINER_JOSEPH, Route110_Text_JosephIntro, Route110_Text_JosephDefeated
	msgbox Route110_Text_JosephPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_Alyssa::
	trainerbattle_single TRAINER_ALYSSA, Route110_Text_AlyssaIntro, Route110_Text_AlyssaDefeated
	msgbox Route110_Text_AlyssaPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_EventScript_CyclingChallengeEnd::
	lockall
	applymovement LOCALID_CHALLENGE_BIKER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	call Route110_EventScript_CyclingChallengeResults
	releaseall
	end

Route110_EventScript_CyclingChallengeResults::
	special FinishCyclingRoadChallenge
	msgbox Route110_Text_CyclingChallengeResultSummary, MSGBOX_DEFAULT
	switch VAR_RESULT
	case 10, Route110_EventScript_ChallengeReactionBest
	case 9, Route110_EventScript_ChallengeReactionGood
	case 8, Route110_EventScript_ChallengeReactionGood
	case 7, Route110_EventScript_ChallengeReactionGood
	case 6, Route110_EventScript_ChallengeReactionOk
	case 5, Route110_EventScript_ChallengeReactionOk
	case 4, Route110_EventScript_ChallengeReactionOk
	case 3, Route110_EventScript_ChallengeReactionBad
	case 2, Route110_EventScript_ChallengeReactionBad
	case 1, Route110_EventScript_ChallengeReactionBad
	case 0, Route110_EventScript_ChallengeReactionWorst
	end

Route110_EventScript_ChallengeReactionBest::
	msgbox Route110_Text_ChallengeReactionBest, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route110_EventScript_ChallengeReactionGood::
	msgbox Route110_Text_ChallengeReactionGood, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route110_EventScript_ChallengeReactionOk::
	msgbox Route110_Text_ChallengeReactionOk, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route110_EventScript_ChallengeReactionBad::
	msgbox Route110_Text_ChallengeReactionBad, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route110_EventScript_ChallengeReactionWorst::
	msgbox Route110_Text_ChallengeReactionWorst, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route110_EventScript_EndChallenge::
	setvar VAR_CYCLING_CHALLENGE_STATE, 3
	savebgm MUS_DUMMY
	fadedefaultbgm
	return

Route110_EventScript_RivalTrigger1::
	setvar VAR_0x8008, 1
	goto Route110_EventScript_RivalScene
	end

Route110_EventScript_RivalTrigger2::
	setvar VAR_0x8008, 2
	goto Route110_EventScript_RivalScene
	end

Route110_EventScript_RivalTrigger3::
	setvar VAR_0x8008, 3
	goto Route110_EventScript_RivalScene
	end

Route110_EventScript_RivalScene::
	lockall
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Route110_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, Route110_EventScript_PlayBrendanMusic
	applymovement LOCALID_ROUTE110_RIVAL, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_ROUTE110_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_ROUTE110_RIVAL, Common_Movement_Delay48
	waitmovement 0
	delay 30
	call_if_eq VAR_0x8008, 1, Route110_EventScript_RivalApproachPlayer1
	call_if_eq VAR_0x8008, 2, Route110_EventScript_RivalApproachPlayer2
	call_if_eq VAR_0x8008, 3, Route110_EventScript_RivalApproachPlayer3
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Route110_EventScript_MayBattle
	goto_if_eq VAR_RESULT, FEMALE, Route110_EventScript_BrendanBattle
	releaseall
	end

Route110_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

Route110_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

Route110_EventScript_MayBattle::
	msgbox Route110_Text_MayLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route110_EventScript_MayBattleTreecko
	case 1, Route110_EventScript_MayBattleTorchic
	case 2, Route110_EventScript_MayBattleMudkip
	end

Route110_EventScript_MayBattleTreecko::
	trainerbattle_no_intro TRAINER_MAY_ROUTE_110_TREECKO, Route110_Text_MayDefeated
	goto Route110_EventScript_MayDefeated
	end

Route110_EventScript_MayBattleTorchic::
	trainerbattle_no_intro TRAINER_MAY_ROUTE_110_TORCHIC, Route110_Text_MayDefeated
	goto Route110_EventScript_MayDefeated
	end

Route110_EventScript_MayBattleMudkip::
	trainerbattle_no_intro TRAINER_MAY_ROUTE_110_MUDKIP, Route110_Text_MayDefeated
	goto Route110_EventScript_MayDefeated
	end

Route110_EventScript_MayDefeated::
	msgbox Route110_Text_MayTakeThis, MSGBOX_DEFAULT
	call Route110_EventScript_GiveItemfinder
	msgbox Route110_Text_MayExplainItemfinder, MSGBOX_DEFAULT
	goto Route110_EventScript_RivalExit
	end

Route110_EventScript_BrendanBattle::
	msgbox Route110_Text_BrendanLetsBattle, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Route110_EventScript_BrendanBattleTreecko
	case 1, Route110_EventScript_BrendanBattleTorchic
	case 2, Route110_EventScript_BrendanBattleMudkip
	end

Route110_EventScript_BrendanBattleTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_110_TREECKO, Route110_Text_BrendanDefeated
	goto Route110_EventScript_BrendanDefeated
	end

Route110_EventScript_BrendanBattleTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_110_TORCHIC, Route110_Text_BrendanDefeated
	goto Route110_EventScript_BrendanDefeated
	end

Route110_EventScript_BrendanBattleMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_110_MUDKIP, Route110_Text_BrendanDefeated
	goto Route110_EventScript_BrendanDefeated
	end

Route110_EventScript_BrendanDefeated::
	msgbox Route110_Text_BrendanTakeThis, MSGBOX_DEFAULT
	call Route110_EventScript_GiveItemfinder
	msgbox Route110_Text_BrendanExplainItemfinder, MSGBOX_DEFAULT
	goto Route110_EventScript_RivalExit
	end

Route110_EventScript_GiveItemfinder::
	giveitem ITEM_DOWSING_MACHINE
	return

Route110_EventScript_RivalExit::
	closemessage
	call_if_eq VAR_0x8008, 1, Route110_EventScript_MoveRival1
	call_if_eq VAR_0x8008, 2, Route110_EventScript_MoveRival2
	call_if_eq VAR_0x8008, 3, Route110_EventScript_MoveRival3
	setobjectmovementtype LOCALID_ROUTE110_RIVAL, MOVEMENT_TYPE_FACE_RIGHT
	setobjectmovementtype LOCALID_ROUTE110_RIVAL_ON_BIKE, MOVEMENT_TYPE_FACE_RIGHT
	removeobject LOCALID_ROUTE110_RIVAL
	addobject LOCALID_ROUTE110_RIVAL_ON_BIKE
	delay 45
	call_if_eq VAR_0x8008, 1, Route110_EventScript_RivalExit1
	call_if_eq VAR_0x8008, 2, Route110_EventScript_RivalExit2
	call_if_eq VAR_0x8008, 3, Route110_EventScript_RivalExit3
	removeobject LOCALID_ROUTE110_RIVAL_ON_BIKE
	setvar VAR_ROUTE110_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

Route110_EventScript_RivalApproachPlayer1::
	applymovement LOCALID_ROUTE110_RIVAL, Route110_Movement_RivalApproachPlayer1
	waitmovement 0
	return

Route110_EventScript_RivalApproachPlayer2::
	applymovement LOCALID_ROUTE110_RIVAL, Route110_Movement_RivalApproachPlayer2
	waitmovement 0
	return

Route110_EventScript_RivalApproachPlayer3::
	applymovement LOCALID_ROUTE110_RIVAL, Route110_Movement_RivalApproachPlayer3
	waitmovement 0
	return

Route110_EventScript_RivalExit1::
	applymovement LOCALID_ROUTE110_RIVAL_ON_BIKE, Route110_Movement_RivalExit1
	waitmovement 0
	return

Route110_EventScript_RivalExit2::
	applymovement LOCALID_ROUTE110_RIVAL_ON_BIKE, Route110_Movement_RivalExit2
	waitmovement 0
	return

Route110_EventScript_RivalExit3::
	applymovement LOCALID_ROUTE110_RIVAL_ON_BIKE, Route110_Movement_RivalExit3
	waitmovement 0
	return

Route110_EventScript_MoveRival1::
	setobjectxyperm LOCALID_ROUTE110_RIVAL_ON_BIKE, 33, 55
	return

Route110_EventScript_MoveRival2::
	setobjectxyperm LOCALID_ROUTE110_RIVAL_ON_BIKE, 34, 55
	return

Route110_EventScript_MoveRival3::
	setobjectxyperm LOCALID_ROUTE110_RIVAL_ON_BIKE, 35, 55
	return

Route110_Movement_RivalApproachPlayer1:
	walk_down
	walk_left
	walk_in_place_faster_down
	step_end

Route110_Movement_RivalApproachPlayer2:
	walk_down
	step_end

Route110_Movement_RivalApproachPlayer3:
	walk_down
	walk_right
	walk_in_place_faster_down
	step_end

Route110_Movement_RivalExit1:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route110_Movement_RivalExit2:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_down
	step_end

Route110_Movement_RivalExit3:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route110_EventScript_BirchScene1::
	lockall
	setvar VAR_0x8008, 1
	goto Route110_EventScript_BirchScene

Route110_EventScript_BirchScene2::
	lockall
	setvar VAR_0x8008, 2
	goto Route110_EventScript_BirchScene

Route110_EventScript_BirchScene3::
	lockall
	setvar VAR_0x8008, 3
	goto Route110_EventScript_BirchScene

Route110_EventScript_BirchScene4::
	lockall
	setvar VAR_0x8008, 4
	goto Route110_EventScript_BirchScene

Route110_EventScript_BirchScene::
	addobject LOCALID_ROUTE110_BIRCH
	applymovement LOCALID_ROUTE110_BIRCH, Route110_Movement_BirchEntrance
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_ROUTE110_BIRCH, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_ROUTE110_BIRCH, Common_Movement_Delay48
	waitmovement 0
	call_if_eq VAR_0x8008, 1, Route110_EventScript_BirchApproachPlayer1
	call_if_eq VAR_0x8008, 2, Route110_EventScript_BirchApproachPlayer2
	call_if_eq VAR_0x8008, 3, Route110_EventScript_BirchApproachPlayer3
	call_if_eq VAR_0x8008, 4, Route110_EventScript_BirchApproachPlayer4
	msgbox Route110_Text_ImagineSeeingYouHere, MSGBOX_DEFAULT
	closemessage
	delay 20
	applymovement LOCALID_ROUTE110_BIRCH, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 10
	applymovement LOCALID_ROUTE110_BIRCH, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	delay 20
	applymovement LOCALID_ROUTE110_BIRCH, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	msgbox Route110_Text_HeardYouInstallMatchCall, MSGBOX_DEFAULT
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox Route110_Text_RegisteredBirchInPokenav, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
	msgbox Route110_Text_KeepAnEyeOutForRival, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_0x8008, 1, Route110_EventScript_BirchExit1
	call_if_eq VAR_0x8008, 2, Route110_EventScript_BirchExit2
	call_if_eq VAR_0x8008, 3, Route110_EventScript_BirchExit3
	call_if_eq VAR_0x8008, 4, Route110_EventScript_BirchExit4
	removeobject LOCALID_ROUTE110_BIRCH
	setvar VAR_REGISTER_BIRCH_STATE, 2
	releaseall
	end

Route110_EventScript_BirchApproachPlayer1::
	applymovement LOCALID_ROUTE110_BIRCH, Route110_Movement_BirchApproachPlayer1
	waitmovement 0
	return

Route110_EventScript_BirchApproachPlayer2::
	applymovement LOCALID_ROUTE110_BIRCH, Route110_Movement_BirchApproachPlayer2
	waitmovement 0
	return

Route110_EventScript_BirchApproachPlayer3::
	applymovement LOCALID_ROUTE110_BIRCH, Route110_Movement_BirchApproachPlayer3
	waitmovement 0
	return

Route110_EventScript_BirchApproachPlayer4::
	applymovement LOCALID_ROUTE110_BIRCH, Route110_Movement_BirchApproachPlayer4
	waitmovement 0
	return

Route110_EventScript_BirchExit1::
	applymovement LOCALID_ROUTE110_BIRCH, Route110_Movement_BirchExit1
	waitmovement 0
	return

Route110_EventScript_BirchExit2::
	applymovement LOCALID_ROUTE110_BIRCH, Route110_Movement_BirchExit2
	waitmovement 0
	return

Route110_EventScript_BirchExit3::
	applymovement LOCALID_ROUTE110_BIRCH, Route110_Movement_BirchExit3
	waitmovement 0
	return

Route110_EventScript_BirchExit4::
	applymovement LOCALID_ROUTE110_BIRCH, Route110_Movement_BirchExit4
	waitmovement 0
	return

Route110_Movement_BirchEntrance:
	walk_down
	walk_down
	walk_down
	step_end

Route110_Movement_BirchApproachPlayer1:
	walk_down
	walk_left
	walk_left
	walk_down
	step_end

Route110_Movement_BirchApproachPlayer2:
	walk_down
	walk_left
	walk_down
	step_end

Route110_Movement_BirchApproachPlayer3:
	walk_down
	walk_down
	step_end

Route110_Movement_BirchApproachPlayer4:
	walk_down
	walk_right
	walk_down
	step_end

Route110_Movement_BirchExit1:
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_up
	step_end

Route110_Movement_BirchExit2:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route110_Movement_BirchExit3:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route110_Movement_BirchExit4:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route110_Text_WeCantTalkAboutAquaActivities:
	.string "Las actividades del EQUIPO AQUA...\n"
	.string "No podemos hablar de eso aún.$"

Route110_Text_KickUpARuckus:
	.string "¡Quiero ir ya a PORT VALIANTE y\n"
	.string "armar un buen escándalo!$"

Route110_Text_MyFirstJobInAqua:
	.string "Es mi primer trabajo desde que me\n"
	.string "uní al EQUIPO AQUA. Da miedo.$"

Route110_Text_AquaActionsBringSmiles:
	.string "¡Las acciones del EQUIPO AQUA\n"
	.string "harán feliz a todo el mundo!$"

Route110_Text_MayLetsBattle:
	.string "MAY: ¡Hola, {PLAYER}{KUN}! ¡Tanto tiempo!\p"
	.string "Mientras buscaba otros POKéMON,\n"
	.string "los míos se hicieron más fuertes.\p"
	.string "So…\n"
	.string "¿Qué tal una pequeña batalla?$"

Route110_Text_MayDefeated:
	.string "¡Cielos!\n"
	.string "¡Eres mejor de lo que esperaba!$"

Route110_Text_MayTakeThis:
	.string "MAY: {PLAYER}{KUN}, has estado ocupado\n"
	.string "entrenando, ¿verdad?\p"
	.string "¡Creo que mereces un premio!\n"
	.string "¡Esto es para ti!$"

Route110_Text_MayExplainItemfinder:
	.string "MAY: Es un BUSCADESOBJ.\p"
	.string "Pruébalo. Si hay un objeto que\n"
	.string "no se ve, emitirá un sonido.\p"
	.string "¡Bien, {PLAYER}{KUN}, nos vemos!\p"
	.string "Sé que suena tonto viniendo de mí,\n"
	.string "pero creo que debes entrenar mucho\l"
	.string "más para la próxima vez.$"

Route110_Text_BrendanLetsBattle:
	.string "BRENDAN: Hola, {PLAYER}.\n"
	.string "Así que aquí estabas.\l"
	.string "¿Cómo va todo?\p"
	.string "¿Has estado criando tus POKéMON?\n"
	.string "Lo revisaré por ti.$"

Route110_Text_BrendanDefeated:
	.string "Hmm…\n"
	.string "Eres bastante bueno.$"

Route110_Text_BrendanTakeThis:
	.string "BRENDAN: {PLAYER}, has entrenado\n"
	.string "sin que me diera cuenta...\p"
	.string "¡Está bastante bien!\n"
	.string "Toma, ten esto.$"

Route110_Text_BrendanExplainItemfinder:
	.string "BRENDAN: Eso es un ITEMFINDER.\p"
	.string "Úsalo para buscar objetos que\n"
	.string "no son visibles.\p"
	.string "Si detecta algo, emitirá\n"
	.string "un sonido.\p"
	.string "En fin, me voy a buscar nuevos\n"
	.string "POKéMON.$"

Route110_Text_RideBikeAtFullSpeed:
	.string "¿No sería genial usar una BIKE?\n"
	.string "¿a toda velocidad en la RUTA CICLISTA?$"

Route110_Text_HairStreamsBehindMe:
	.string "¿Qué te parece cómo mi cabello\n"
	.string "color cuervo ondea tras de mí?\p"
	.string "Lo dejé crecer solo para eso.$"

Route110_Text_YouGotBikeFromRydel:
	.string "¡Oh, tienes la BICICLETA de RYDEL!\p"
	.string "Oh, es demasiado obvio.\n"
	.string "Dice justo en tu bicicleta...\p"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\n"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\p"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\n"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\p"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\n"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\p"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\n"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\p"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL...\n"
	.string "Ese nombre está en todas partes.\p"
	.string "Deberías usarla por todo el\n"
	.string "lugar... ¡es buena publicidad!$"

Route110_Text_TwoRoads:
	.string "Dos caminos, uno arriba y otro abajo…\p"
	.string "Uno para personas y otro POKéMON.\n"
	.string "Tal vez así sea justo y correcto.$"

Route110_Text_WalkOnTheLowRoad:
	.string "No tengo BICICLETA, así que daré\n"
	.string "un paseo tranquilo por el camino bajo.$"

Route110_Text_BikeTechniques:
	.string "Aprender técnicas hará que usar la\n"
	.string "BICICLETA sea más divertido.\p"
	.string "Hay lugares a los que solo puedes\n"
	.string "llegar usando técnicas de BICICLETA.$"

Route110_Text_WhichShouldIChoose:
	.string "¿Cuál debería elegir?\p"
	.string "Ir directo a MALVILLA por la\n"
	.string "CICLOVÍA, o tomar el camino bajo\l"
	.string "¿y buscar POKéMON?$"

Route110_Text_CyclingChallengeResultSummary:
	.string "Número de choques:\n"
	.string "… … {STR_VAR_1}!\p"
	.string "Tiempo total:\n"
	.string "… … {STR_VAR_2}!$"

Route110_Text_ChallengeReactionBest:
	.string "¡Bravo! ¡Una exhibición espléndida!\p"
	.string "Tu amor por el ciclismo nace desde\n"
	.string "lo más profundo de tu corazón.\l"
	.string "¡Me has conmovido hasta el alma!$"

Route110_Text_ChallengeReactionGood:
	.string "Tu técnica es extraordinaria.\p"
	.string "Te sugiero que aceleres un poco más\n"
	.string "sigues evitando choques.$"

Route110_Text_ChallengeReactionOk:
	.string "Te consideraría una obra en\n"
	.string "progreso.\p"
	.string "Aun así, espero que no olvides el\n"
	.string "puro placer de andar en bici.$"

Route110_Text_ChallengeReactionBad:
	.string "Cielos... Tus dotes al pedalear son\n"
	.string "aterradoras.\p"
	.string "Sin duda, necesitas mucha más\n"
	.string "práctica montando.$"

Route110_Text_ChallengeReactionWorst:
	.string "...Estoy horrorizado...\p"
	.string "Tal vez no sirvas para este\n"
	.string "desafortunado asunto de las bicis.\p"
	.string "Deberías pensar seriamente en\n"
	.string "devolver esa BIKE a RYDEL.$"

Route110_Text_RatedForNumberOfCollisions:
	.string "Esta es la RUTA CICLISTA.\p"
	.string "Si fueras de MALVITA a\n"
	.string "FONSALUD en MACH BIKE, se\l"
	.string "contarían tus colisiones\l"
	.string "y tu tiempo total.$"

Route110_Text_AlwaysAimHigher:
	.string "Sin importar el resultado, espero\n"
	.string "ver más desafíos tuyos.\l"
	.string "¡Apunta siempre más alto!$"

Route110_Text_AcroBikesDoNotQualify:
	.string "En esta RUTA CICLISTA, quienes usan\n"
	.string "MACH BIKES son evaluados por su número\l"
	.string "de colisiones y sus tiempos totales.\p"
	.string "Las ACRO BIKES no califican.\n"
	.string "Giran fácil, así que no es justo.$"

Route110_Text_SlateportCitySign:
	.string "RUTA 110\n"
	.string "{DOWN_ARROW} CIUDAD PORTAL$"

Route110_Text_CyclingRoadSign:
	.string "SEASIDE CYCLING ROAD$"

Route110_Text_AquaWasHere:
	.string "¡El TEAM AQUA estuvo aquí!\p"
	.string "Alguien pintó eso en el cartel,\n"
	.string "pero luego alguien más lo tapó.\p"
	.string "Ahora dice: ¡El TEAM MAGMA\n"
	.string "manda!$"

Route110_Text_Route103Sign:
	.string "RUTA 110\n"
	.string "{LEFT_ARROW} RUTA 103$"

Route110_Text_SeasideParkingSign:
	.string "SEASIDE PARKING$"

Route110_Text_MauvilleCitySign:
	.string "RUTA 110\n"
	.string "{UP_ARROW} CIUDAD MALVA$"

Route110_Text_TrainerTipsPrlzSleep:
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "Puedes dejar al rival indefenso\n"
	.string "si lo paralizas o lo duermes.\p"
	.string "Es una técnica muy importante para\n"
	.string "combates POKéMON.$"

Route110_Text_TrainerTipsRegisterItems:
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "Los objetos de la MOCHILA se pueden\n"
	.string "reorganizar con SELECT.$"

Route110_Text_TrickHouseSign:
	.string "Tres pasos {RIGHT_ARROW} y dos {UP_ARROW}\n"
	.string "para llegar a la TRICK HOUSE.$"

Route110_Text_BestRecord:
	.string "EL MEJOR RÉCORD HASTA HOY...\p"
	.string "Choques: {STR_VAR_1}\p"
	.string "Tiempo: {STR_VAR_2}$"

Route110_Text_ThereIsNoRecord:
	.string "EL MEJOR RÉCORD HASTA HOY...\p"
	.string "Parece que nadie ha aceptado el\n"
	.string "desafío. No hay registros...$"

Route110_Text_ImagineSeeingYouHere:
	.string "PROF. BIRCH: ¡Oh, {PLAYER}{KUN}!\n"
	.string "¡No esperaba verte aquí!\p"
	.string "¿Y dónde estará mi {RIVAL}?$"

Route110_Text_HeardYouInstallMatchCall:
	.string "¡Ah, ya veo!\n"
	.string "Ustedes dos viajan separados.\l"
	.string "Bueno, no hay problema.\p"
	.string "Ah, sí, escuché que tu POKéNAV\n"
	.string "tiene el sistema MATCH CALL.\p"
	.string "Entonces, yo también debería\n"
	.string "registrarte en mi POKéNAV.\p"
	.string "Así, aunque estemos lejos,\n"
	.string "Puedo evaluar tu POKéDEX cuando sea.\p"
	.string "… … … … … …$"

Route110_Text_RegisteredBirchInPokenav:
	.string "Registrado PROF. BIRCH\n"
	.string "en el POKéNAV.$"

Route110_Text_KeepAnEyeOutForRival:
	.string "PROF. BIRCH: {PLAYER}{KUN}…\p"
	.string "Vigila a mi {RIVAL}, por favor.\n"
	.string "… … … … … …\p"
	.string "Bueno, es mejor que me vaya.\n"
	.string "¡Nos vemos, {PLAYER}{KUN}!$"

