BattleFrontier_BattlePikeLobby_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePikeLobby_OnFrame_hns
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePikeLobby_OnWarp_hns
	.byte 0

BattleFrontier_BattlePikeLobby_OnFrame_hns:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattlePikeLobby_EventScript_GetChallengeStatus_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePikeLobby_EventScript_QuitWithoutSaving_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattlePikeLobby_EventScript_WonChallenge_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePikeLobby_EventScript_LostChallenge_hns
	.2byte 0

BattleFrontier_BattlePikeLobby_OnWarp_hns:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePikeLobby_EventScript_TurnPlayerNorth_hns
	.2byte 0

BattleFrontier_BattlePikeLobby_EventScript_TurnPlayerNorth_hns::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePikeLobby_EventScript_GetChallengeStatus_hns::
	frontier_getstatus
	end

BattleFrontier_BattlePikeLobby_EventScript_QuitWithoutSaving_hns::
	special HealPlayerParty
	pike_resethelditems
	lockall
	msgbox BattleFrontier_BattlePikeLobby_Text_FailedToSaveBeforeQuitting_hns, MSGBOX_DEFAULT
	closemessage
	pike_set PIKE_DATA_WIN_STREAK, 0
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_WonChallenge_hns::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePikeLobby_EventScript_DefeatedQueen_hns
	msgbox BattleFrontier_BattlePikeLobby_Text_PossessLuckInAbundance_hns, MSGBOX_DEFAULT
	waitmessage
	goto BattleFrontier_BattlePikeLobby_EventScript_GiveBattlePoints_hns

BattleFrontier_BattlePikeLobby_EventScript_DefeatedQueen_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_SnatchedVictoryFromQueen_hns, MSGBOX_DEFAULT
	waitmessage
BattleFrontier_BattlePikeLobby_EventScript_GiveBattlePoints_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints_hns, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	frontier_checkairshow
	pike_get PIKE_DATA_TOTAL_STREAKS
	addvar VAR_RESULT, 1
	pike_set PIKE_DATA_TOTAL_STREAKS, VAR_RESULT
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	pike_resethelditems
	message BattleFrontier_BattlePikeLobby_Text_ShallRecordResults_hns
	waitmessage
	pike_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou_hns, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_LostChallenge_hns::
	lockall
	message BattleFrontier_BattlePikeLobby_Text_ChallengeEndedRecordResults_hns
	waitmessage
	frontier_checkairshow
	frontier_set FRONTIER_DATA_BATTLE_NUM, 0
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, FALSE
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	pike_resethelditems
	pike_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou_hns, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_Attendant_hns::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PIKE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattlePikeLobby_Text_WelcomeToBattlePike_hns, MSGBOX_DEFAULT
BattleFrontier_BattlePikeLobby_EventScript_AskTakeChallenge_hns::
	message BattleFrontier_BattlePikeLobby_Text_TakeChallenge_hns
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeLobby_EventScript_TryEnterChallenge_hns
	case 1, BattleFrontier_BattlePikeLobby_EventScript_ExplainChallenge_hns
	case 2, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge_hns

BattleFrontier_BattlePikeLobby_EventScript_TryEnterChallenge_hns::
	message BattleFrontier_BattlePikeLobby_Text_WhichChallengeMode_hns
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge_hns
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons_hns
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePikeLobby_Text_PleaseChooseThreeMons_hns, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge_hns
	msgbox BattleFrontier_BattlePikeLobby_Text_SaveBeforeChallenge_hns, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge_hns
	case YES, BattleFrontier_BattlePikeLobby_EventScript_SaveBeforeChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge_hns

BattleFrontier_BattlePikeLobby_EventScript_SaveBeforeChallenge_hns::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_1, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	pike_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, TRUE
	pike_savehelditems
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	pike_savehelditems
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge_hnsSaveFailed_hns
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePikeLobby_Text_StepThisWay_hns, MSGBOX_DEFAULT
	closemessage
	frontier_settrainers
	call BattleFrontier_BattlePikeLobby_EventScript_WalkToCorridor_hns
	special HealPlayerParty
	call BattleFrontier_BattlePike_EventScript_CloseCurtain_hns
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PIKE_CORRIDOR_HNS, 6, 7
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattlePikeLobby_EventScript_ExplainChallenge_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainBattlePike_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_AskTakeChallenge_hns

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons_hns::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons_hnsLv50_hns
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons_hnsLvOpen_hns

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons_hnsLv50_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLv50_hns, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsEnd_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge_hns

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons_hnsLvOpen_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLvOpen_hns, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsEnd_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge_hns

BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge_hnsSaveFailed_hns::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge_hns

BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge_hns::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou_hns, MSGBOX_DEFAULT
BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge_hns::
	release
	end

BattleFrontier_BattlePikeLobby_EventScript_ShowResults_hns::
	lockall
	frontier_results FRONTIER_FACILITY_PIKE
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_WalkToCorridor_hns::
	applymovement LOCALID_PIKE_LOBBY_ATTENDANT, BattleFrontier_BattlePikeLobby_Movement_AttendantWalkToCorridor_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePikeLobby_Movement_PlayerWalkToCorridor_hns
	waitmovement 0
	return

BattleFrontier_BattlePikeLobby_Movement_PlayerWalkToCorridor_hns:
	walk_up
BattleFrontier_BattlePikeLobby_Movement_AttendantWalkToCorridor_hns:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePikeLobby_EventScript_Hiker_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_OneRoomAwayFromGoal_hns, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_Twin_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_NeverHadToBattleTrainer_hns, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_Beauty_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_ThinkAbilitiesUsefulHere_hns, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesBoard_hns::
	lockall
	msgbox BattleFrontier_BattlePikeLobby_Text_RulesAreListed_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard_hns::
	message BattleFrontier_BattlePikeLobby_Text_ReadWhichHeading_hns
	waitmessage
	multichoice 16, 4, MULTI_BATTLE_PIKE_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeLobby_EventScript_RulesPokenavBag_hns
	case 1, BattleFrontier_BattlePikeLobby_EventScript_RulesHeldItems_hns
	case 2, BattleFrontier_BattlePikeLobby_EventScript_RulesMonOrder_hns
	case 3, BattleFrontier_BattlePikeLobby_EventScript_ExitRules_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_ExitRules_hns
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesPokenavBag_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainPokenavBagRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesHeldItems_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainHeldItemRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesMonOrder_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainMonOrderRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePikeLobby_EventScript_ExitRules_hns::
	releaseall
	end

BattleFrontier_BattlePike_EventScript_CloseCurtain_hns::
	playse SE_PIKE_CURTAIN_CLOSE
	special CloseBattlePikeCurtain
	waitstate
	waitse
	return

BattleFrontier_BattlePikeLobby_Text_WelcomeToBattlePike_hns:
	.string "המקום שבו מזלם של המאמנים\n"
	.string "עומד למבחן…\p"
	.string "ברוכים הבאים לשביל הקרב…\p"
	.string "אני המדריכה שלך לשביל הקרב…$"

BattleFrontier_BattlePikeLobby_Text_TakeChallenge_hns:
	.string "האם ברצונך לקחת חלק\n"
	.string "באתגר בחירת הקרב?$"

BattleFrontier_BattlePikeLobby_Text_ExplainBattlePike_hns:
	.string "כאן אנו עורכים אירוע שנקרא\n"
	.string "בחירת הקרב.\p"
	.string "החוקים של בחירת הקרב\n"
	.string "פשוטים מאוד…\p"
	.string "יש לבחור אחד משלושה שבילים ולהגיע\n"
	.string "לחדר היעד שבסוף שביל הקרב. זה הכול.\p"
	.string "אולם, מה שיקרה בשביל שנבחר\n"
	.string "תלוי כולו במזלו של המתמודד…\p"
	.string "מי שמגיע ליעד\n"
	.string "מקבל נקודות קרב כפרס.\p"
	.string "כדי לעצור את האתגר באמצע, יש לפנות\n"
	.string "לצוות שלנו בחדרים הגדולים שבדרך.\p"
	.string "עצירה בלי לשמור קודם\n"
	.string "תוביל לפסילה.$"

BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou_hns:
	.string "נשמח לראות אותך\n"
	.string "בהזדמנות אחרת…$"

BattleFrontier_BattlePikeLobby_Text_WhichChallengeMode_hns:
	.string "יש שני מסלולים: רמה 50 ורמה פתוחה.\n"
	.string "באיזה מהם להתמודד?$"

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLv50_hns:
	.string "סליחה, אבל…\p"
	.string "אין לך שלושה פוקימונים\n"
	.string "כשירים לאירוע בחירת הקרב.\p"
	.string "כדי להשתתף צריך שלושה פוקימונים\n"
	.string "שונים ברמה 50 ומטה.\p"
	.string "בנוסף, עליהם להחזיק\n"
	.string "פריטים מסוגים שונים.\p"
	.string "ביצים{STR_VAR_1}.$"

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsEnd_hns:
	.string "אפשר לחזור אליי\n"
	.string "כשההכנות יושלמו…$"

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLvOpen_hns:
	.string "סליחה, אבל…\p"
	.string "אין לך שלושה פוקימונים\n"
	.string "כשירים לאירוע בחירת הקרב.\p"
	.string "כדי להשתתף צריך שלושה\n"
	.string "פוקימונים שונים.\p"
	.string "בנוסף, עליהם להחזיק\n"
	.string "פריטים מסוגים שונים.\p"
	.string "ביצים{STR_VAR_1}.$"

BattleFrontier_BattlePikeLobby_Text_PleaseChooseThreeMons_hns:
	.string "נא לבחור את שלושת הפוקימונים\n"
	.string "שישתתפו באתגר…$"

BattleFrontier_BattlePikeLobby_Text_SaveBeforeChallenge_hns:
	.string "לפני תחילת אתגר בחירת הקרב,\n"
	.string "עליי לשמור את המשחק. זה בסדר?$"

BattleFrontier_BattlePikeLobby_Text_StepThisWay_hns:
	.string "מכאן, בבקשה…$"

BattleFrontier_BattlePikeLobby_Text_ChallengeEndedRecordResults_hns:
	.string "האתגר שלך הסתיים…\p"
	.string "כעת ארשום את התוצאות שלך.\n"
	.string "נא להמתין…$"

BattleFrontier_BattlePikeLobby_Text_PossessLuckInAbundance_hns:
	.string "השלמת את האתגר…\p"
	.string "עליי לומר… נראה שיש לך\n"
	.string "מזל בשפע…$"

BattleFrontier_BattlePikeLobby_Text_ShallRecordResults_hns:
	.string "כעת ארשום את התוצאות שלך.\n"
	.string "נא להמתין…$"

@ Unused
BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints_hns2_hns:
	.string "To commemorate your completion of\n"
	.string "the Battle Choice challenge, we award\l"
	.string "you these Battle Point(s)…$"

@ Unused
BattleFrontier_BattlePikeLobby_Text_ReachedBattlePointLimit_hns:
	.string "You appear to have reached the limit\n"
	.string "for Battle Points…\p"
	.string "Please exchange some Battle Points\n"
	.string "for prizes, then return…$"

BattleFrontier_BattlePikeLobby_Text_FailedToSaveBeforeQuitting_hns:
	.string "סליחה, אבל…\p"
	.string "בפעם הקודמת לא שמרת לפני\n"
	.string "שעזבת את האתגר.\p"
	.string "בגלל זה, האתגר שלך עד כה\n"
	.string "נפסל. אני מצטערת…$"

BattleFrontier_BattlePikeLobby_Text_SnatchedVictoryFromQueen_hns:
	.string "ברכותיי…\p"
	.string "חטפת את הניצחון מידי\n"
	.string "מלכת השביל והשלמת את האירוע…$"

BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints_hns:
	.string "כהוקרה על מזלך המדהים,\n"
	.string "אנו מעניקים לך את נקודות הקרב האלה…$"

BattleFrontier_BattlePikeLobby_Text_OneRoomAwayFromGoal_hns:
	.string "אררג! פספסתי את ההזדמנות!\n"
	.string "הייתי במרחק חדר אחד מהיעד!\p"
	.string "במקום הזה כדאי להיזהר\n"
	.string "מהרעלה, מקיפאון וכדומה.$"

BattleFrontier_BattlePikeLobby_Text_NeverHadToBattleTrainer_hns:
	.string "השלמתי את האתגר כבר 10 פעמים, אבל\n"
	.string "אף פעם לא הייתי צריכה להילחם במאמן.$"

BattleFrontier_BattlePikeLobby_Text_ThinkAbilitiesUsefulHere_hns:
	.string "תקשיב! תקשיב!\p"
	.string "לא נראה לך שהיכולות המיוחדות\n"
	.string "של הפוקימונים יועילו כאן?$"

@ Unused
BattleFrontier_BattlePikeLobby_Text_TrainersWhicheverPathIChoose_hns:
	.string "What is this weird place?\n"
	.string "I can't figure it out at all!\p"
	.string "I've taken the challenge a bunch\n"
	.string "of times, but all I ever do is run into\l"
	.string "TRAINERS whichever path I choose.$"

BattleFrontier_BattlePikeLobby_Text_RulesAreListed_hns:
	.string "כאן מפורטים חוקי בחירת הקרב.$"

BattleFrontier_BattlePikeLobby_Text_ReadWhichHeading_hns:
	.string "איזו כותרת לקרוא?$"

BattleFrontier_BattlePikeLobby_Text_ExplainPokenavBagRules_hns:
	.string "אסור להשתמש בתיק ובפוקיגיר\n"
	.string "במהלך אתגר בחירת הקרב.$"

BattleFrontier_BattlePikeLobby_Text_ExplainHeldItemRules_hns:
	.string "במהלך אתגר בחירת הקרב, כל פרי או\n"
	.string "עשב שפוקימון מחזיק יפעל רק פעם אחת.$"

BattleFrontier_BattlePikeLobby_Text_ExplainMonOrderRules_hns:
	.string "במהלך אתגר בחירת הקרב, אי אפשר\n"
	.string "לשנות את סדר הפוקימונים.\p"
	.string "את הסדר יש לקבוע לפני\n"
	.string "תחילת האתגר.$"

