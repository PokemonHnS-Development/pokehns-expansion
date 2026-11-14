BattleFrontier_ReceptionGate_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_ReceptionGate_OnFrame_hns
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_ReceptionGate_OnTransition_hns
	.byte 0

BattleFrontier_ReceptionGate_OnTransition_hns:
	setflag FLAG_LANDMARK_BATTLE_FRONTIER
	end

BattleFrontier_ReceptionGate_OnFrame_hns:
	map_script_2 VAR_HAS_ENTERED_BATTLE_FRONTIER, 0, BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering_hns
	.2byte 0

BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering_hns::
	lockall
	setvar VAR_HAS_ENTERED_BATTLE_FRONTIER, 1
	playse SE_PIN
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_FRONTIER_RECEPTION_GREETER
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_Delay48
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter_hns
	waitmovement 0
	goto BattleFrontier_ReceptionGate_EventScript_ScottScene_hns
	end

BattleFrontier_ReceptionGate_EventScript_ScottScene_hns::
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier_hns, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IssueFrontierPass_hns, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass_hns
	waitfanfare
	waitmessage
	msgbox BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass_hns, MSGBOX_DEFAULT
	setflag FLAG_SYS_FRONTIER_PASS
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier_hns, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_ExclamationMark
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, Common_Movement_ExclamationMark
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_PLAYER
	msgbox BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, BattleFrontier_ReceptionGate_Movement_GreeterFaceScott_hns
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott_hns
	applymovement LOCALID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerFaceScott_hns
	applymovement LOCALID_FRONTIER_RECEPTION_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottEnter_hns
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottExit_hns
	waitmovement 0
	removeobject LOCALID_FRONTIER_RECEPTION_SCOTT
	releaseall
	end

BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter_hns:
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_PlayerFaceScott_hns:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

@ Unused
BattleFrontier_ReceptionGate_Movement_WalkDown_hns:
	walk_down
	walk_down
	step_end

BattleFrontier_ReceptionGate_Movement_ScottEnter_hns:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_ScottExit_hns:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_ReceptionGate_Movement_GreeterFaceScott_hns:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott_hns:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

BattleFrontier_ReceptionGate_EventScript_Greeter_hns::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier_hns, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FacilityGuide_hns::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFacilities_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich2_hns
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BF_RECEPTIONIST
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_BattleTower_hns
	case 1, BattleFrontier_ReceptionGate_EventScript_BattleDome_hns
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePalace_hns
	case 3, BattleFrontier_ReceptionGate_EventScript_BattleArena_hns
	case 4, BattleFrontier_ReceptionGate_EventScript_BattleFactory_hns
	case 5, BattleFrontier_ReceptionGate_EventScript_BattlePike_hns
	case 6, BattleFrontier_ReceptionGate_EventScript_BattlePyramid_hns
	case 7, BattleFrontier_ReceptionGate_EventScript_RankingHall_hns
	case 8, BattleFrontier_ReceptionGate_EventScript_ExchangeCorner_hns
	case 9, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide_hns
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide_hns
	end

BattleFrontier_ReceptionGate_EventScript_BattleTower_hns::
	msgbox BattleFrontier_ReceptionGate_Text_BattleTowerInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_BattleDome_hns::
	msgbox BattleFrontier_ReceptionGate_Text_BattleDomeInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_BattlePalace_hns::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePalaceInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_BattleArena_hns::
	msgbox BattleFrontier_ReceptionGate_Text_BattleArenaInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_BattleFactory_hns::
	msgbox BattleFrontier_ReceptionGate_Text_BattleFactoryInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_BattlePike_hns::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePikeInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_BattlePyramid_hns::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePyramidInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_RankingHall_hns::
	msgbox BattleFrontier_ReceptionGate_Text_RankingHallInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_ExchangeCorner_hns::
	msgbox BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide_hns::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_RulesGuide_hns::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout_hns::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhat_hns
	waitmessage
	multichoice 15, 0, MULTI_FRONTIER_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_LevelMode_hns
	case 1, BattleFrontier_ReceptionGate_EventScript_Level50_hns
	case 2, BattleFrontier_ReceptionGate_EventScript_OpenLevel_hns
	case 3, BattleFrontier_ReceptionGate_EventScript_MonEntry_hns
	case 4, BattleFrontier_ReceptionGate_EventScript_HoldItems_hns
	case 5, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide_hns
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide_hns
	end

BattleFrontier_ReceptionGate_EventScript_LevelMode_hns::
	msgbox BattleFrontier_ReceptionGate_Text_LevelModeInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_Level50_hns::
	msgbox BattleFrontier_ReceptionGate_Text_Level50Info_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_OpenLevel_hns::
	msgbox BattleFrontier_ReceptionGate_Text_OpenLevelInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_MonEntry_hns::
	msgbox BattleFrontier_ReceptionGate_Text_MonEntryInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_HoldItems_hns::
	msgbox BattleFrontier_ReceptionGate_Text_HoldItemsInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide_hns::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FrontierPassGuide_hns::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout_hns::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich1_hns
	waitmessage
	multichoice 16, 4, MULTI_FRONTIER_PASS_INFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_Symbols_hns
	case 1, BattleFrontier_ReceptionGate_EventScript_RecordBattle_hns
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePoints_hns
	case 3, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide_hns
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide_hns
	end

BattleFrontier_ReceptionGate_EventScript_Symbols_hns::
	msgbox BattleFrontier_ReceptionGate_Text_SymbolsInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_RecordBattle_hns::
	msgbox BattleFrontier_ReceptionGate_Text_RecordedBattleInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_BattlePoints_hns::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePointsInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide_hns::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay_hns:
	.string "זו הפעם הראשונה שלך כאן?\n"
	.string "בבקשה, מכאן!$"

BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier_hns:
	.string "קו החזית של קרבות הפוקימונים!\n"
	.string "ברוכים הבאים לחזית הקרב!$"

BattleFrontier_ReceptionGate_Text_IssueFrontierPass_hns:
	.string "למבקרים בפעם הראשונה אנחנו מנפיקים\n"
	.string "את כרטיס חזית הקרב.\p"
	.string "הוא משמש בכל המתקנים\n"
	.string "של חזית הקרב.\p"
	.string "הנה, בבקשה!$"

BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass_hns:
	.string "{PLAYER} קיבל\n"
	.string "את כרטיס חזית הקרב.$"

BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass_hns:
	.string "{PLAYER} צירף את כרטיס המאמן\n"
	.string "לכרטיס חזית הקרב.$"

BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier_hns:
	.string "אנחנו מקווים שתיהנה מכל מה\n"
	.string "שחזית הקרב מציעה!$"

BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame_hns:
	.string "???: תראו מי כאן, {PLAYER}{KUN}!\n"
	.string "הגעת עד לכאן!$"

BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay_hns:
	.string "מדריכה: אה! מר סקוט!\n"
	.string "יום טוב לך, אדוני!$"

BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere_hns:
	.string "סקוט: כל כך טוב לראות אותך כאן,\n"
	.string "באמת!\p"
	.string "אני מקווה שתסייר בכל מקום\n"
	.string "בלי למהר.\p"
	.string "וכמובן, אני מקווה שתחווה גם\n"
	.string "את המהות הטהורה של הקרב.\p"
	.string "גם המגורים שלי נמצאים כאן, אז\n"
	.string "תקפוץ לבקר אם יהיה לך זמן.$"

BattleFrontier_ReceptionGate_Text_YourGuideToFacilities_hns:
	.string "אני המדריכה שלך למתקנים השונים\n"
	.string "כאן בחזית הקרב.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich2_hns:
	.string "על איזה מקום לספר לך?$"

BattleFrontier_ReceptionGate_Text_BattleTowerInfo_hns:
	.string "זהו המגדל הענק שנחשב\n"
	.string "לסמל של חזית הקרב.\p"
	.string "במגדל יש ארבעה סוגי חדרי קרב:\n"
	.string "יחיד, כפול, מרובה ומרובה בקישור.$"

BattleFrontier_ReceptionGate_Text_BattleDomeInfo_hns:
	.string "כיפת הקרב היא הבניין הגדול\n"
	.string "בצורת ביצה ענקית.\p"
	.string "במתקן הזה נערכים אירועים\n"
	.string "שנקראים טורנירי קרב.\p"
	.string "טורנירי הקרב מוצעים בשני מסלולים:\n"
	.string "לקרבות יחידים ולקרבות כפולים.$"

BattleFrontier_ReceptionGate_Text_BattlePalaceInfo_hns:
	.string "ארמון הקרב הוא הבניין האדום\n"
	.string "בצד הימני של חזית הקרב.\p"
	.string "יש בו שני סוגים של אולמות קרב:\n"
	.string "לקרבות יחידים ולקרבות כפולים.$"

BattleFrontier_ReceptionGate_Text_BattleArenaInfo_hns:
	.string "זירת הקרב היא הבניין דמוי הדוג'ו\n"
	.string "שמימין למרכז חזית הקרב.\p"
	.string "בזירת הקרב נערך אירוע\n"
	.string "שנקרא טורניר הנוקאאוט.$"

BattleFrontier_ReceptionGate_Text_BattleFactoryInfo_hns:
	.string "מפעל הקרב הוא הבניין הגדול\n"
	.string "הקרוב ביותר אלינו.\p"
	.string "שם נערך אירוע שנקרא\n"
	.string "החלפת הקרב.\p"
	.string "אירוע החלפת הקרב מוצע בשני מסלולים:\n"
	.string "לקרבות יחידים ולקרבות כפולים.$"

BattleFrontier_ReceptionGate_Text_BattlePikeInfo_hns:
	.string "שביל הקרב הוא הבניין בצורת פוקימון\n"
	.string "שמשמאל למרכז חזית הקרב.\p"
	.string "שם נערך אירוע שנקרא\n"
	.string "בחירת הקרב.$"

BattleFrontier_ReceptionGate_Text_BattlePyramidInfo_hns:
	.string "פירמידת הקרב היא הפירמידה\n"
	.string "העצומה.\p"
	.string "שם נערך אירוע שנקרא\n"
	.string "מסע הקרב.$"

BattleFrontier_ReceptionGate_Text_RankingHallInfo_hns:
	.string "היכל הדירוג נמצא ליד\n"
	.string "מגדל הקרב.\p"
	.string "שם מוצגים השיאים המדהימים ביותר של\n"
	.string "מאמנים שהתמודדו עם אתגרי חזית הקרב.$"

BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo_hns:
	.string "פינת שירות ההמרה נמצאת ליד\n"
	.string "מגדל הקרב.\p"
	.string "שם אפשר להמיר את נקודות הקרב שצברת\n"
	.string "בחזית הקרב בפרסים נהדרים.$"

BattleFrontier_ReceptionGate_Text_YourGuideToRules_hns:
	.string "אני המדריכה שלך לחוקים הבסיסיים\n"
	.string "המשותפים לאתגרים בכל מתקני חזית הקרב.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhat_hns:
	.string "על מה לספר לך?$"

BattleFrontier_ReceptionGate_Text_LevelModeInfo_hns:
	.string "כל האתגרים במתקני חזית הקרב מוצעים\n"
	.string "בשני מסלולים: רמה 50 ורמה פתוחה.$"

BattleFrontier_ReceptionGate_Text_Level50Info_hns:
	.string "מסלול רמה 50 פתוח לפוקימונים\n"
	.string "עד רמה 50, כולל.\p"
	.string "אבל חשוב לזכור: לאף מאמן יריב\n"
	.string "לא יהיו פוקימונים מתחת לרמה 50.\p"
	.string "זהו מסלול המתחילים לקרבות\n"
	.string "בחזית הקרב.\p"
	.string "בתור התחלה, אנחנו מקווים\n"
	.string "שתתמודד במסלול הזה.$"

BattleFrontier_ReceptionGate_Text_OpenLevelInfo_hns:
	.string "מסלול הרמה הפתוחה לא מגביל את רמות\n"
	.string "הפוקימונים שמשתתפים באתגרים.\p"
	.string "הרמות של היריבים יותאמו\n"
	.string "לרמות של הפוקימונים שלך.\p"
	.string "עם זאת, לאף מאמן יריב לא יהיו\n"
	.string "פוקימונים מתחת לרמה 60.$"

BattleFrontier_ReceptionGate_Text_MonEntryInfo_hns:
	.string "כמעט כל פוקימון יכול להשתתף\n"
	.string "באתגרים בכל המתקנים.\p"
	.string "עם זאת, ביצים ופוקימונים מסוימים\n"
	.string "אינם מורשים.\p"
	.string "מספר הפוקימונים הנדרש לאתגרים\n"
	.string "תלוי במתקן.\p"
	.string "אבל בכל המתקנים, אסור להשתתף\n"
	.string "עם שניים או יותר מאותו פוקימון.$"

BattleFrontier_ReceptionGate_Text_HoldItemsInfo_hns:
	.string "בכניסה לאתגר במתקני חזית הקרב,\n"
	.string "אסור לפוקימונים להחזיק פריטים זהים.\p"
	.string "יש לוודא שכל הפוקימונים שנכנסים\n"
	.string "לאתגר מחזיקים פריטים שונים.$"

BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass_hns:
	.string "אני המדריכה שלך לכרטיס חזית הקרב.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich1_hns:
	.string "על מה לספר לך?$"

BattleFrontier_ReceptionGate_Text_SymbolsInfo_hns:
	.string "בחזית הקרב יש שבעה מתקנים.\p"
	.string "מאמנים שכישוריהם זוכים להכרה עשויים\n"
	.string "לקבל סמלים מכל אחד מהמתקנים.\p"
	.string "כדי לזכות בסמל, ייתכן שיהיה צריך\n"
	.string "לנצח מאמנים אחרים ברצף.\p"
	.string "ייתכן גם שיהיה צריך לנצח\n"
	.string "באירועים שוב ושוב.\p"
	.string "זה בהחלט לא קל לזכות בסמלים.\n"
	.string "אני מאחלת לך המון הצלחה!$"

BattleFrontier_ReceptionGate_Text_RecordedBattleInfo_hns:
	.string "אפשר להקליט קרב אחד\n"
	.string "בכרטיס חזית הקרב שלך.\p"
	.string "אפשר להקליט קרב שניהלת\n"
	.string "עם חבר או עם חברים.\p"
	.string "או קרב בחזית הקרב, חוץ מקרבות\n"
	.string "בשביל הקרב או בפירמידת הקרב.\p"
	.string "בסוף כל קרב אפשר לבחור\n"
	.string "אם להקליט אותו.$"

BattleFrontier_ReceptionGate_Text_BattlePointsInfo_hns:
	.string "נקודות קרב הן פרס למאמנים\n"
	.string "שהצטיינו בקרבות בחזית הקרב.\p"
	.string "אפשר להמיר את נקודות הקרב\n"
	.string "בפרסים בפינת שירות ההמרה.$"

