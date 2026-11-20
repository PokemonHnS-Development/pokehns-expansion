BattleFrontier_BattleFactoryLobby_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleFactoryLobby_OnFrame_hns
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleFactoryLobby_OnWarp_hns
	.byte 0

BattleFrontier_BattleFactoryLobby_OnWarp_hns:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleFactoryLobby_EventScript_TurnPlayerNorth_hns
	.2byte 0

BattleFrontier_BattleFactoryLobby_EventScript_TurnPlayerNorth_hns::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleFactoryLobby_OnFrame_hns:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattleFactoryLobby_EventScript_GetChallengeStatus_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleFactoryLobby_EventScript_QuitWithoutSaving_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleFactoryLobby_EventScript_ResumeChallenge_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattleFactoryLobby_EventScript_WonChallenge_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattleFactoryLobby_EventScript_LostChallenge_hns
	.2byte 0

BattleFrontier_BattleFactoryLobby_EventScript_GetChallengeStatus_hns::
	frontier_getstatus
	end

BattleFrontier_BattleFactoryLobby_EventScript_QuitWithoutSaving_hns::
	lockall
	msgbox BattleFrontier_BattleFactoryLobby_Text_DidntSaveBeforeQuitting_hns, MSGBOX_DEFAULT
	closemessage
	factory_setswapped
	factory_set FACTORY_DATA_WIN_STREAK_SWAPS, 0
	factory_set FACTORY_DATA_WIN_STREAK, 0
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_WonChallenge_hns::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleFactoryLobby_EventScript_DefeatedFactoryHead_hns
	msgbox BattleFrontier_BattleFactoryLobby_Text_CongratsSevenWins_hns, MSGBOX_DEFAULT
	waitmessage
	goto BattleFrontier_BattleFactoryLobby_EventScript_GiveBattlePoints_hns

BattleFrontier_BattleFactoryLobby_EventScript_DefeatedFactoryHead_hns::
	msgbox BattleFrontier_BattleFactoryLobby_Text_CongratsForDefeatingHead_hns, MSGBOX_DEFAULT
	waitmessage
BattleFrontier_BattleFactoryLobby_EventScript_GiveBattlePoints_hns::
	msgbox BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints_hns, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleFactoryLobby_Text_ExchangeMonsAndSave_hns
	waitmessage
	frontier_checkairshow
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
	factory_save 0
	playse SE_SAVE
	waitse
	goto BattleFrontier_BattleFactoryLobby_EventScript_AskRecordBattle_hns
	end

BattleFrontier_BattleFactoryLobby_EventScript_LostChallenge_hns::
	lockall
	message BattleFrontier_BattleFactoryLobby_Text_ReturnMons_hnsSaveResults_hns
	waitmessage
	frontier_checkairshow
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, FALSE
	factory_save 0
	playse SE_SAVE
	waitse

BattleFrontier_BattleFactoryLobby_EventScript_AskRecordBattle_hns::
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle_hns
	message BattleFrontier_BattleFactoryLobby_Text_RecordLastMatch_hns
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle_hns
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_RecordBattle_hns
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle_hns

BattleFrontier_BattleFactoryLobby_EventScript_RecordBattle_hns::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleFactoryLobby_EventScript_EndRecordBattle_hns::
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit_hns, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_ResumeChallenge_hns::
	lockall
	message BattleFrontier_BattleFactoryLobby_Text_WaitingForYouToResume_hns
	waitmessage
	factory_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	setvar VAR_0x8006, 2
	goto BattleFrontier_BattleFactoryLobby_EventScript_EnterChallenge_hns

BattleFrontier_BattleFactoryLobby_EventScript_SinglesAttendant_hns::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	goto BattleFrontier_BattleFactoryLobby_EventScript_Attendant_hns
	end

BattleFrontier_BattleFactoryLobby_EventScript_DoublesAttendant_hns::
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_FACTORY
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES
	goto BattleFrontier_BattleFactoryLobby_EventScript_Attendant_hns
	end

BattleFrontier_BattleFactoryLobby_EventScript_Attendant_hns::
	special SavePlayerParty
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForSingleBattle_hns
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForDoubleBattle_hns
BattleFrontier_BattleFactoryLobby_EventScript_AskTakeChallenge_hns::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_TakeSinglesChallenge_hns
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_TakeDoublesChallenge_hns
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge_hns
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_ExplainChallenge_hns
	case 2, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge_hns

BattleFrontier_BattleFactoryLobby_EventScript_TryEnterChallenge_hns::
	message BattleFrontier_BattleFactoryLobby_Text_WhichLevelMode_hns
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge_hns
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleFactoryLobby_Text_OkayToSaveBeforeChallenge_hns, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge_hns
	case YES, BattleFrontier_BattleFactoryLobby_EventScript_SaveBeforeChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge_hns

BattleFrontier_BattleFactoryLobby_EventScript_SaveBeforeChallenge_hns::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	factory_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	factory_set FACTORY_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge_hnsSaveFailed_hns
	setvar VAR_0x8006, 0
BattleFrontier_BattleFactoryLobby_EventScript_EnterChallenge_hns::
	special SavePlayerParty
	msgbox BattleFrontier_BattleFactoryLobby_Text_StepThisWay_hns, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_TalkedToSinglesAttendant_hns
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_TalkedToDoublesAttendant_hns
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleFactoryLobby_Movement_AttendantEnterDoor_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattleFactoryLobby_Movement_PlayerEnterDoor_hns
	waitmovement 0
	warp MAP_BATTLE_FRONTIER_BATTLE_FACTORY_PRE_BATTLE_ROOM_HNS, 8, 13
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattleFactoryLobby_EventScript_TalkedToSinglesAttendant_hns::
	setvar VAR_LAST_TALKED, LOCALID_FACTORY_ATTENDANT_SINGLES
	return

BattleFrontier_BattleFactoryLobby_EventScript_TalkedToDoublesAttendant_hns::
	setvar VAR_LAST_TALKED, LOCALID_FACTORY_ATTENDANT_DOUBLES
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainChallenge_hns::
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES, BattleFrontier_BattleFactoryLobby_EventScript_ExplainSinglesChallenge_hns
	call_if_eq VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_DOUBLES, BattleFrontier_BattleFactoryLobby_EventScript_ExplainDoublesChallenge_hns
	goto BattleFrontier_BattleFactoryLobby_EventScript_AskTakeChallenge_hns

BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge_hnsSaveFailed_hns::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge_hns

BattleFrontier_BattleFactoryLobby_EventScript_LoadPartyAndCancelChallenge_hns::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattleFactoryLobby_EventScript_CancelChallenge_hns::
	msgbox BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleFactoryLobby_Movement_AttendantEnterDoor_hns:
	walk_up
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleFactoryLobby_Movement_PlayerEnterDoor_hns:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForSingleBattle_hns::
	msgbox BattleFrontier_BattleFactoryLobby_Text_WelcomeForSingleBattle_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_WelcomeForDoubleBattle_hns::
	msgbox BattleFrontier_BattleFactoryLobby_Text_WelcomeForDoubleBattle_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_TakeSinglesChallenge_hns::
	message BattleFrontier_BattleFactoryLobby_Text_TakeSinglesChallenge_hns
	return

BattleFrontier_BattleFactoryLobby_EventScript_TakeDoublesChallenge_hns::
	message BattleFrontier_BattleFactoryLobby_Text_TakeDoublesChallenge_hns
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainSinglesChallenge_hns::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSinglesChallenge_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_ExplainDoublesChallenge_hns::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainDoublesChallenge_hns, MSGBOX_DEFAULT
	return

BattleFrontier_BattleFactoryLobby_EventScript_ShowSinglesResults_hns::
	lockall
	frontier_results FRONTIER_FACILITY_FACTORY, FRONTIER_MODE_SINGLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_ShowDoublesResults_hns::
	lockall
	frontier_results FRONTIER_FACILITY_FACTORY, FRONTIER_MODE_DOUBLES
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleFactoryLobby_EventScript_Woman_hns::
	msgbox BattleFrontier_BattleFactoryLobby_Text_NeedKnowledgeOfMonsMoves_hns, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_Camper_hns::
	msgbox BattleFrontier_BattleFactoryLobby_Text_SwappedForWeakMon_hns, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_Picnicker_hns::
	lock
	msgbox BattleFrontier_BattleFactoryLobby_Text_NeedToCheckOpponentsMons_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleFactoryLobby_EventScript_FatMan_hns::
	msgbox BattleFrontier_BattleFactoryLobby_Text_CantFigureOutStaffHints_hns, MSGBOX_NPC
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesBoard_hns::
	lockall
	msgbox BattleFrontier_BattleFactoryLobby_Text_RulesAreListed_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard_hns::
	message BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading_hns
	waitmessage
	multichoice 17, 0, MULTI_BATTLE_FACTORY_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleFactoryLobby_EventScript_RulesBasics_hns
	case 1, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapPartner_hns
	case 2, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNumber_hns
	case 3, BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNotes_hns
	case 4, BattleFrontier_BattleFactoryLobby_EventScript_RulesOpenLv_hns
	case 5, BattleFrontier_BattleFactoryLobby_EventScript_ExitRules_hns
	case MULTI_B_PRESSED, BattleFrontier_BattleFactoryLobby_EventScript_ExitRules_hns
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesBasics_hns::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainBasicRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapPartner_hns::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapPartnerRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNumber_hns::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNumberRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesSwapNotes_hns::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNotesRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattleFactoryLobby_EventScript_RulesOpenLv_hns::
	msgbox BattleFrontier_BattleFactoryLobby_Text_ExplainOpenLvRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleFactoryLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattleFactoryLobby_EventScript_ExitRules_hns::
	releaseall
	end

BattleFrontier_BattleFactoryLobby_Text_WelcomeForSingleBattle_hns:
	.string "כאן האינטליגנציה של המאמנים\n"
	.string "עומדת למבחן!\p"
	.string "ברוכים הבאים למפעל הקרב!\p"
	.string "אני המדריך שלך\n"
	.string "לטורניר החלפת קרב יחיד.$"

BattleFrontier_BattleFactoryLobby_Text_TakeSinglesChallenge_hns:
	.string "רוצה לגשת לאתגר\n"
	.string "החלפת קרב יחיד?$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSinglesChallenge_hns:
	.string "טורניר החלפת קרב יחיד הוא תחרות של\n"
	.string "קרבות יחידים בפוקימונים שכורים בלבד.\p"
	.string "קודם כול, מושאלים לך שלושה\n"
	.string "פוקימונים במיוחד לאירוע הזה.\p"
	.string "עם הפוקימונים השכורים האלה\n"
	.string "יש להילחם בקרב יחיד.\p"
	.string "אחרי ניצחון, מותר להחליף\n"
	.string "אחד מהפוקימונים השכורים שלך.\p"
	.string "חוזרים על הסבב של קרב והחלפה.\n"
	.string "שבעה ניצחונות ברצף מזכים בנקודות קרב.\p"
	.string "כדי להפסיק את האתגר באמצע,\n"
	.string "יש לשמור את המשחק.\p"
	.string "הפסקה בלי שמירה\n"
	.string "תוביל לפסילה מהאתגר.$"

BattleFrontier_BattleFactoryLobby_Text_LookForwardToNextVisit_hns:
	.string "נשמח לראות אותך בביקור הבא.$"

BattleFrontier_BattleFactoryLobby_Text_WhichLevelMode_hns:
	.string "באיזו רמה ברצונך להתמודד?\n"
	.string "רמה 50 או רמה פתוחה?$"

BattleFrontier_BattleFactoryLobby_Text_OkayToSaveBeforeChallenge_hns:
	.string "לפני תחילת האתגר,\n"
	.string "עליי לשמור את המשחק. זה בסדר?$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_WillHoldMonsForSafekeeping_hns:
	.string "Okay, I will hold your POKéMON for\n"
	.string "safekeeping while you compete.$"

BattleFrontier_BattleFactoryLobby_Text_StepThisWay_hns:
	.string "מכאן, בבקשה.$"

BattleFrontier_BattleFactoryLobby_Text_ReturnMons_hnsSaveResults_hns:
	.string "תודה על ההשתתפות!\p"
	.string "אחזיר לך את הפוקימונים שלך\n"
	.string "תמורת הפוקימונים השכורים שלנו.\p"
	.string "עליי גם לשמור את תוצאות האירוע.\n"
	.string "נא להמתין.$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_ReturnMons_hns:
	.string "I will return your POKéMON in exchange\n"
	.string "for our rental POKéMON.$"

BattleFrontier_BattleFactoryLobby_Text_CongratsSevenWins_hns:
	.string "מזל טוב! ניצחת בשבעה קרבות\n"
	.string "רצופים באתגר החלפת הקרב!$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints_hnsForStreak_hns:
	.string "In recognition of your 7-win streak,\n"
	.string "we award you these Battle Point(s).$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_MaxBattlePoints_hns:
	.string "Oh, oh, oh!\p"
	.string "Your Battle Points are maxed.\p"
	.string "Please come back after using\n"
	.string "some Battle Points.$"

BattleFrontier_BattleFactoryLobby_Text_WaitingForYouToResume_hns:
	.string "חיכינו לך!\p"
	.string "לפני שנמשיך באתגר שלך,\n"
	.string "עליי לשמור את המשחק.$"

BattleFrontier_BattleFactoryLobby_Text_DidntSaveBeforeQuitting_hns:
	.string "צר לי לומר, אבל בפעם הקודמת\n"
	.string "הפסקת לשחק בלי לשמור.\p"
	.string "כתוצאה מכך, נפסלת\n"
	.string "מהאתגר שלך.$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_WellReturnMons_hns:
	.string "We'll return your personal POKéMON.$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_ReceivedPrizeItem_hns:
	.string "{PLAYER} received the prize\n"
	.string "{STR_VAR_1}.$"

BattleFrontier_BattleFactoryLobby_Text_WelcomeForDoubleBattle_hns:
	.string "כאן האינטליגנציה של המאמנים\n"
	.string "עומדת למבחן!\p"
	.string "ברוכים הבאים למפעל הקרב!\p"
	.string "אני המדריך שלך\n"
	.string "לטורניר החלפת קרב כפול.$"

BattleFrontier_BattleFactoryLobby_Text_TakeDoublesChallenge_hns:
	.string "רוצה לגשת לאתגר\n"
	.string "החלפת קרב כפול?$"

BattleFrontier_BattleFactoryLobby_Text_ExplainDoublesChallenge_hns:
	.string "טורניר החלפת קרב כפול הוא תחרות של\n"
	.string "קרבות כפולים בפוקימונים שכורים בלבד.\p"
	.string "קודם כול, מושאלים לך שלושה\n"
	.string "פוקימונים במיוחד לאירוע הזה.\p"
	.string "עם הפוקימונים השכורים האלה\n"
	.string "יש להילחם בקרב כפול.\p"
	.string "אחרי ניצחון, מותר להחליף\n"
	.string "אחד מהפוקימונים השכורים שלך.\p"
	.string "חוזרים על הסבב של קרב והחלפה.\n"
	.string "שבעה ניצחונות ברצף מזכים בנקודות קרב.\p"
	.string "כדי להפסיק את האתגר באמצע,\n"
	.string "יש לשמור את המשחק.\p"
	.string "הפסקה בלי שמירה מראש\n"
	.string "תוביל לפסילה.$"

BattleFrontier_BattleFactoryLobby_Text_CongratsForDefeatingHead_hns:
	.string "מזל טוב על הניצחון על ראש המפעל\n"
	.string "ועל הזכייה בשבעה קרבות ברצף!$"

BattleFrontier_BattleFactoryLobby_Text_AwardBattlePoints_hns:
	.string "כהוקרה על הידע העשיר והשכל החד שלך,\n"
	.string "אנו מעניקים לך את נקודות הקרב האלה.$"

BattleFrontier_BattleFactoryLobby_Text_ExchangeMonsAndSave_hns:
	.string "אחזיר לך את הפוקימונים שלך\n"
	.string "תמורת הפוקימונים השכורים שלנו.\p"
	.string "עליי לשמור את נתוני הקרב,\n"
	.string "אז נא להמתין.$"

BattleFrontier_BattleFactoryLobby_Text_RecordLastMatch_hns:
	.string "להקליט בכרטיס חזית הקרב את\n"
	.string "הקרב האחרון שלך במפעל הקרב?$"

BattleFrontier_BattleFactoryLobby_Text_NeedKnowledgeOfMonsMoves_hns:
	.string "היי!\n"
	.string "כן, אליך אני מדברת!\p"
	.string "נדמה לך שהאירועים פה קלים כי\n"
	.string "לא צריך קבוצת פוקימונים מאומנת?\p"
	.string "לא הייתי בטוחה כל כך\n"
	.string "שהניצחון יבוא בקלות.\p"
	.string "בלי ידע מעמיק על פוקימונים ועל\n"
	.string "המהלכים שלהם, קשה להמשיך לנצח.$"

BattleFrontier_BattleFactoryLobby_Text_SwappedForWeakMon_hns:
	.string "קיבלתי בהחלפה פוקימון חלש…\n"
	.string "חשבתי שכדאי שיהיה לי כזה…\p"
	.string "הם ניגבו איתנו את הרצפה…$"

BattleFrontier_BattleFactoryLobby_Text_NeedToCheckOpponentsMons_hns:
	.string "שום דבר לא הולך לי\n"
	.string "בכלל.\p"
	.string "צריך לבדוק את פוקימוני היריב במהלך\n"
	.string "הקרב כדי לראות אם הם שווים משהו.$"

BattleFrontier_BattleFactoryLobby_Text_CantFigureOutStaffHints_hns:
	.string "שמת לב שהצוות כאן נותן\n"
	.string "כמה רמזים על היריב הבא?\p"
	.string "טוב, אני גבר מבוגר, אבל\n"
	.string "קשה לי לפענח את הרמזים שלהם.$"

@ Unused
BattleFrontier_BattleFactoryLobby_Text_RentalMonsAreVaried_hns:
	.string "Like, I'm really tough, but I get bored\n"
	.string "really easily, so I just kept swapping\l"
	.string "and battling over and over.\p"
	.string "So anyway, when I kept entering\n"
	.string "Battle Swap events, I noticed they\l"
	.string "varied the rental POKéMON.$"

BattleFrontier_BattleFactoryLobby_Text_RulesAreListed_hns:
	.string "כאן כתובים חוקי החלפת הקרב.$"

BattleFrontier_BattleFactoryLobby_Text_ReadWhichHeading_hns:
	.string "איזה סעיף ברצונך לקרוא?$"

BattleFrontier_BattleFactoryLobby_Text_ExplainBasicRules_hns:
	.string "באירוע החלפת קרב אפשר להשתמש\n"
	.string "בשלושה פוקימונים בלבד.\p"
	.string "בין אם שוכרים ובין אם מחליפים, אסור\n"
	.string "שיהיו בקבוצה שניים או יותר מאותו פוקימון.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapPartnerRules_hns:
	.string "אפשר להחליף פוקימונים רק עם\n"
	.string "המאמן שניצחת זה עתה.\p"
	.string "אפשר לקבל בהחלפה רק פוקימונים\n"
	.string "שהמאמן המובס השתמש בהם.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNumberRules_hns:
	.string "אחרי כל ניצחון, אפשר לקבל בהחלפה\n"
	.string "אחד מהפוקימונים של היריב המובס.\p"
	.string "אי אפשר להחליף פוקימונים\n"
	.string "עם המאמן השביעי באירוע.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainSwapNotesRules_hns:
	.string "יש שתי נקודות חשובות שכדאי\n"
	.string "לזכור כשמחליפים פוקימונים.\p"
	.string "ראשית, בזמן החלפה אי אפשר לבדוק את\n"
	.string "הנתונים של הפוקימון שעומדים לקבל.\p"
	.string "שנית, הפוקימונים בקבוצה שלך מסודרים\n"
	.string "ברצף, לפי הסדר שבו שכרת אותם.\p"
	.string "הסדר הזה לא משתנה\n"
	.string "גם כשמבצעים החלפות.$"

BattleFrontier_BattleFactoryLobby_Text_ExplainOpenLvRules_hns:
	.string "ברמה הפתוחה, גם הפוקימונים השכורים וגם\n"
	.string "אלה של המאמנים היריבים הם ברמה 100.$"
