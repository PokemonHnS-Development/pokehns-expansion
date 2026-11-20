BattleFrontier_ScottsHouse_hns_MapScripts::
	.byte 0

BattleFrontier_ScottsHouse_EventScript_Scott_hns::
	lock
	faceplayer
	goto_if_set FLAG_TEMP_4, BattleFrontier_ScottsHouse_EventScript_GivenBerry_hns
	goto_if_set FLAG_TEMP_3, BattleFrontier_ScottsHouse_EventScript_GivenShield_hns
	goto_if_set FLAG_TEMP_2, BattleFrontier_ScottsHouse_EventScript_GivenBattlePoints_hns
	goto BattleFrontier_ScottsHouse_EventScript_CheckGiveItems_hns
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveItems_hns::
	goto_if_unset FLAG_SCOTT_GIVES_BATTLE_POINTS, BattleFrontier_ScottsHouse_EventScript_WelcomeToFrontier_hns
	goto_if_unset FLAG_COLLECTED_ALL_SILVER_SYMBOLS, BattleFrontier_ScottsHouse_EventScript_CheckSilverSymbols_hns
	goto_if_unset FLAG_COLLECTED_ALL_GOLD_SYMBOLS, BattleFrontier_ScottsHouse_EventScript_CheckGoldSymbols_hns
	goto BattleFrontier_ScottsHouse_EventScript_CheckGiveShield_hns
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveShield_hns::
	goto_if_unset FLAG_RECEIVED_SILVER_SHIELD, BattleFrontier_ScottsHouse_EventScript_CheckGiveSilverShield_hns
	goto_if_unset FLAG_RECEIVED_GOLD_SHIELD, BattleFrontier_ScottsHouse_EventScript_CheckGiveGoldShield_hns
	goto BattleFrontier_ScottsHouse_EventScript_RandomComment_hns
	end

BattleFrontier_ScottsHouse_EventScript_CheckSilverSymbols_hns::
	goto_if_unset FLAG_SYS_TOWER_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield_hns
	goto_if_unset FLAG_SYS_DOME_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield_hns
	goto_if_unset FLAG_SYS_PALACE_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield_hns
	goto_if_unset FLAG_SYS_ARENA_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield_hns
	goto_if_unset FLAG_SYS_FACTORY_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield_hns
	goto_if_unset FLAG_SYS_PIKE_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield_hns
	goto_if_unset FLAG_SYS_PYRAMID_SILVER, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield_hns
	msgbox BattleFrontier_ScottsHouse_Text_YouveCollectedAllSilverSymbols_hns, MSGBOX_DEFAULT
	giveitem ITEM_LANSAT_BERRY
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_BerryPocketFull_hns
	setflag FLAG_COLLECTED_ALL_SILVER_SYMBOLS
	setflag FLAG_TEMP_4
	release
	end

BattleFrontier_ScottsHouse_EventScript_CheckGoldSymbols_hns::
	goto_if_unset FLAG_SYS_TOWER_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield_hns
	goto_if_unset FLAG_SYS_DOME_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield_hns
	goto_if_unset FLAG_SYS_PALACE_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield_hns
	goto_if_unset FLAG_SYS_ARENA_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield_hns
	goto_if_unset FLAG_SYS_FACTORY_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield_hns
	goto_if_unset FLAG_SYS_PIKE_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield_hns
	goto_if_unset FLAG_SYS_PYRAMID_GOLD, BattleFrontier_ScottsHouse_EventScript_CheckGiveShield_hns
	msgbox BattleFrontier_ScottsHouse_Text_YouveCollectedAllGoldSymbols_hns, MSGBOX_DEFAULT
	giveitem ITEM_STARF_BERRY
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_BerryPocketFull_hns
	setflag FLAG_COLLECTED_ALL_GOLD_SYMBOLS
	setflag FLAG_TEMP_4
	release
	end

BattleFrontier_ScottsHouse_EventScript_BerryPocketFull_hns::
	msgbox BattleFrontier_ScottsHouse_Text_BerryPocketStuffed_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_GivenBerry_hns::
	msgbox BattleFrontier_ScottsHouse_Text_SoGladIBroughtYouHere_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_RandomComment_hns::
	random 3
	goto_if_eq VAR_RESULT, 1, BattleFrontier_ScottsHouse_EventScript_FrontierBrainComment_hns
	goto_if_eq VAR_RESULT, 2, BattleFrontier_ScottsHouse_EventScript_ArtisanCaveComment_hns
	msgbox BattleFrontier_ScottsHouse_Text_WhyIGoSeekingTrainers_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_FrontierBrainComment_hns::
	msgbox BattleFrontier_ScottsHouse_Text_HaveYouMetFrontierBrain_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_ArtisanCaveComment_hns::
	msgbox BattleFrontier_ScottsHouse_Text_MayFindWildMonsInFrontier_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveSilverShield_hns::
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_50
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ge VAR_RESULT, 50, BattleFrontier_ScottsHouse_EventScript_GiveSilverShield_hns
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_OPEN
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ge VAR_RESULT, 50, BattleFrontier_ScottsHouse_EventScript_GiveSilverShield_hns
	goto BattleFrontier_ScottsHouse_EventScript_RandomComment_hns
	end

BattleFrontier_ScottsHouse_EventScript_GiveSilverShield_hns::
	msgbox BattleFrontier_ScottsHouse_Text_Beat50TrainersInARow_hns, MSGBOX_DEFAULT
	givedecoration DECOR_SILVER_SHIELD
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_NoRoomForShield_hns
	setflag FLAG_RECEIVED_SILVER_SHIELD
	setflag FLAG_TEMP_3
	goto BattleFrontier_ScottsHouse_EventScript_GivenShield_hns
	end

BattleFrontier_ScottsHouse_EventScript_NoRoomForShield_hns::
	msgbox BattleFrontier_ScottsHouse_Text_ComeBackForThisLater_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_GivenShield_hns::
	msgbox BattleFrontier_ScottsHouse_Text_ExpectingToHearEvenGreaterThings_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_CheckGiveGoldShield_hns::
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_50
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ge VAR_RESULT, 100, BattleFrontier_ScottsHouse_EventScript_GiveGoldShield_hns
	frontier_set FRONTIER_DATA_LVL_MODE, FRONTIER_LVL_OPEN
	tower_get TOWER_DATA_WIN_STREAK
	goto_if_ge VAR_RESULT, 100, BattleFrontier_ScottsHouse_EventScript_GiveGoldShield_hns
	goto BattleFrontier_ScottsHouse_EventScript_RandomComment_hns
	end

BattleFrontier_ScottsHouse_EventScript_GiveGoldShield_hns::
	msgbox BattleFrontier_ScottsHouse_Text_Beat100TrainersInARow_hns, MSGBOX_DEFAULT
	givedecoration DECOR_GOLD_SHIELD
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_ScottsHouse_EventScript_NoRoomForShield_hns
	setflag FLAG_RECEIVED_GOLD_SHIELD
	setflag FLAG_TEMP_3
	goto BattleFrontier_ScottsHouse_EventScript_GivenShield_hns
	end

BattleFrontier_ScottsHouse_EventScript_GivenBattlePoints_hns::
	msgbox BattleFrontier_ScottsHouse_Text_ExpectingGreatThings_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ScottsHouse_EventScript_WelcomeToFrontier_hns::
	msgbox BattleFrontier_ScottsHouse_Text_WelcomeToBattleFrontier_hns, MSGBOX_DEFAULT
	closemessage
	delay 30
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_ScottsHouse_EventScript_Scott_hnsFaceAwayNorth_hns
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_ScottsHouse_EventScript_Scott_hnsFaceAwaySouth_hns
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_ScottsHouse_EventScript_Scott_hnsFaceAwayEast_hns
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_ScottsHouse_EventScript_Scott_hnsFaceAwayWest_hns
	msgbox BattleFrontier_ScottsHouse_Text_HowMuchEffortItTookToMakeReal_hns, MSGBOX_DEFAULT
	applymovement LOCALID_SCOTTS_HOUSE_SCOTT, Common_Movement_FacePlayer
	waitmovement 0
	msgbox BattleFrontier_ScottsHouse_Text_HaveThisAsMementoOfOurPathsCrossing_hns, MSGBOX_DEFAULT
	goto_if_eq VAR_SCOTT_STATE, 13, BattleFrontier_ScottsHouse_EventScript_Give4BattlePoints_hns
	goto_if_ge VAR_SCOTT_STATE, 9, BattleFrontier_ScottsHouse_EventScript_Give3BattlePoints_hns
	goto_if_ge VAR_SCOTT_STATE, 6, BattleFrontier_ScottsHouse_EventScript_Give2BattlePoints_hns
	goto BattleFrontier_ScottsHouse_EventScript_Give1BattlePoint_hns
	end

BattleFrontier_ScottsHouse_EventScript_Give4BattlePoints_hns::
	buffernumberstring STR_VAR_1, 4
	setvar VAR_0x8004, 4
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints_hns
	end

BattleFrontier_ScottsHouse_EventScript_Give3BattlePoints_hns::
	buffernumberstring STR_VAR_1, 3
	setvar VAR_0x8004, 3
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints_hns
	end

BattleFrontier_ScottsHouse_EventScript_Give2BattlePoints_hns::
	buffernumberstring STR_VAR_1, 2
	setvar VAR_0x8004, 2
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints_hns
	end

BattleFrontier_ScottsHouse_EventScript_Give1BattlePoint_hns::
	buffernumberstring STR_VAR_1, 1
	setvar VAR_0x8004, 1
	goto BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints_hns
	end

BattleFrontier_ScottsHouse_EventScript_GiveBattlePoints_hns::
	special GiveFrontierBattlePoints
	msgbox BattleFrontier_ScottsHouse_Text_ObtainedXBattlePoints_hns, MSGBOX_GETPOINTS
	msgbox BattleFrontier_ScottsHouse_Text_ExplainBattlePoints_hns, MSGBOX_DEFAULT
	setflag FLAG_SCOTT_GIVES_BATTLE_POINTS
	setflag FLAG_TEMP_2
	release
	end

BattleFrontier_ScottsHouse_EventScript_Scott_hnsFaceAwayNorth_hns::
	applymovement LOCALID_SCOTTS_HOUSE_SCOTT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

BattleFrontier_ScottsHouse_EventScript_Scott_hnsFaceAwaySouth_hns::
	applymovement LOCALID_SCOTTS_HOUSE_SCOTT, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

BattleFrontier_ScottsHouse_EventScript_Scott_hnsFaceAwayEast_hns::
	applymovement LOCALID_SCOTTS_HOUSE_SCOTT, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

BattleFrontier_ScottsHouse_EventScript_Scott_hnsFaceAwayWest_hns::
	applymovement LOCALID_SCOTTS_HOUSE_SCOTT, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

BattleFrontier_ScottsHouse_Text_WelcomeToBattleFrontier_hns:
	.string "סקוט: שלום, וברוך הבא!\n"
	.string "הה-הה… סליחה על הצפיפות.\p"
	.string "בכל אופן, {PLAYER}{KUN}, הרשה לי לברך\n"
	.string "אותך רשמית: ברוך הבא לחזית הקרב.\p"
	.string "זה החלום שלי שהתגשם.\p"
	.string "לקח לי שנים על גבי שנים, אבל סוף סוף\n"
	.string "החלום שלי קרם עור וגידים.$"

BattleFrontier_ScottsHouse_Text_HowMuchEffortItTookToMakeReal_hns:
	.string "כשאני חושב על זה,\n"
	.string "זה היה מסע ארוך להחריד…\p"
	.string "יצאתי מהבית לבד,\n"
	.string "למסע בחיפוש אחר מאמנים חזקים.\p"
	.string "אף אחד לא יכול לדמיין כמה מאמץ\n"
	.string "וזמן נדרשו כדי להפוך את זה למציאות.$"

BattleFrontier_ScottsHouse_Text_HaveThisAsMementoOfOurPathsCrossing_hns:
	.string "אבל כל זה כבר מאחוריי.\n"
	.string "אין טעם להתעכב על זה!\p"
	.string "כל מה שאני רוצה הוא שתיהנה\n"
	.string "כאן מקרבות כאוות נפשך.\p"
	.string "{PLAYER}{KUN}, אני רוצה לתת לך את זה למזכרת\n"
	.string "מכל הפעמים שדרכינו הצטלבו במסעותינו.$"

BattleFrontier_ScottsHouse_Text_ObtainedXBattlePoints_hns:
	.string "{PLAYER} השיג\n"
	.string "נקודות קרב: {STR_VAR_1}.$"

BattleFrontier_ScottsHouse_Text_ExplainBattlePoints_hns:
	.string "סקוט: אפשר לבדוק את נקודות\n"
	.string "הקרב שלך בכרטיס חזית הקרב.\p"
	.string "ככל שתצליח יותר כאן בחזית הקרב,\n"
	.string "כך תאסוף יותר נקודות קרב.\p"
	.string "אפשר להשתמש בנקודות הקרב איך שתרצה,\n"
	.string "למשל להמיר אותן בפריטים.$"

BattleFrontier_ScottsHouse_Text_ExpectingGreatThings_hns:
	.string "אני מצפה ממך לדברים גדולים!$"

BattleFrontier_ScottsHouse_Text_WhyIGoSeekingTrainers_hns:
	.string "סקוט: כל מאמן הוא עולם ומלואו.\n"
	.string "לכל אחד יש חיים משלו.\p"
	.string "אבל כשהם בקרב, לא משנה מי הם.\p"
	.string "כולם אותו דבר!\p"
	.string "אני אוהב את הטוהר של הקרב,\n"
	.string "שבו כולם שווים.\p"
	.string "לכן אני הולך לכל מקום ומחפש מאמנים\n"
	.string "שלוקחים קרבות ברצינות, ומזמין אותם לכאן.$"

BattleFrontier_ScottsHouse_Text_HaveYouMetFrontierBrain_hns:
	.string "סקוט: פגשת כבר מישהו\n"
	.string "ממוחות החזית?\p"
	.string "או אפילו טוב יותר, השגת מהם סמלים?\p"
	.string "בחרתי את מוחות החזית בקפידה,\n"
	.string "בתור המאמנים הקשוחים ביותר שיש.\p"
	.string "אבל אני בטוח שכשיראו כמה\n"
	.string "אתה קשוח, אפילו הם יופתעו!$"

BattleFrontier_ScottsHouse_Text_MayFindWildMonsInFrontier_hns:
	.string "סקוט: אתה לא מתאמן רק לקרבות, נכון?\p"
	.string "נדמה לי שאני זוכר שאתה\n"
	.string "ממלא גם את הפוקדקס.\p"
	.string "אז נחש מה?\p"
	.string "אולי תיתקל בפוקימונים פראיים\n"
	.string "איפשהו בחזית הקרב… פופופו!$"

BattleFrontier_ScottsHouse_Text_YouveCollectedAllSilverSymbols_hns:
	.string "סקוט: אתה נהנה בחזית הקרב?\p"
	.string "…רגע אחד…\n"
	.string "אה!\p"
	.string "כרטיס חזית הקרב שלך!\n"
	.string "אספת את כל סדרת סמלי הכסף!\p"
	.string "זה יותר ממרשים!\n"
	.string "אתה קשוח, בדיוק כמו שחשדתי!\p"
	.string "בדרך כלל לא הייתי עושה דבר כזה,\n"
	.string "אבל זו הזדמנות מיוחדת!\p"
	.string "אני רוצה לתת לך את זה.\n"
	.string "אני בטוח שתשתמש בזה כמו שצריך.$"

BattleFrontier_ScottsHouse_Text_YouveCollectedAllGoldSymbols_hns:
	.string "סקוט: אני מקווה שאתה נהנה\n"
	.string "מכל מה שיש בחזית הקרב.\p"
	.string "…רגע אחד…\n"
	.string "אני לא מאמין למראה עיניי!\p"
	.string "כרטיס חזית הקרב שלך!\n"
	.string "אספת את כל סדרת סמלי הזהב!\p"
	.string "זה יותר מפנומנלי!\n"
	.string "אתה מדהים, בדיוק כמו שחשדתי!\p"
	.string "… … … … … …\p"
	.string "{PLAYER}, אתה חייב לקבל את זה!\p"
	.string "אני חושב שתדע להעריך\n"
	.string "כמה המתנה שלי שווה!$"

BattleFrontier_ScottsHouse_Text_SoGladIBroughtYouHere_hns:
	.string "אני חייב לומר שיש לי כישרון\n"
	.string "לזהות מאמן טוב ממבט ראשון.\p"
	.string "אני כל כך שמח שראיתי את הנולד\n"
	.string "והבאתי אותך לכאן!$"

BattleFrontier_ScottsHouse_Text_BerryPocketStuffed_hns:
	.string "נראה שכיס הפירות שלך\n"
	.string "מלא עד אפס מקום.$"

BattleFrontier_ScottsHouse_Text_Beat50TrainersInARow_hns:
	.string "סקוט: הו, שמעתי עליך!\n"
	.string "על איך ששלטת במגדל הקרב!\p"
	.string "ניצחת מעל 50 מאמנים ברצף?\p"
	.string "זה פנטסטי!\n"
	.string "אני רוצה לתת לך את זה!$"

BattleFrontier_ScottsHouse_Text_Beat100TrainersInARow_hns:
	.string "סקוט: וואו! שמעתי עליך!\n"
	.string "על איך שהכנעת את מגדל הקרב!\p"
	.string "ניצחת מעל 100 מאמנים ברצף?\p"
	.string "זה מרהיב בטירוף!\n"
	.string "אתה חייב לקבל את זה!$"

BattleFrontier_ScottsHouse_Text_ExpectingToHearEvenGreaterThings_hns:
	.string "מעכשיו אצפה לשמוע עליך\n"
	.string "דברים גדולים עוד יותר!$"

BattleFrontier_ScottsHouse_Text_ComeBackForThisLater_hns:
	.string "אופס… אם יש לך יותר מדי חפצים,\n"
	.string "אפשר לחזור לקחת את זה אחר כך.$"

