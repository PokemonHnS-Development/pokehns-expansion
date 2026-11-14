BattleFrontier_OutsideWest_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideWest_OnTransition_hns
	.byte 0

BattleFrontier_OutsideWest_OnTransition_hns:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	end

BattleFrontier_OutsideWest_EventScript_EventScript_Sailor_hns::
	lock
	faceplayer
	msgbox FarawayIsland_Entrance_Text_SailorReturn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_AsYouLike_hns
	msgbox EventTicket_Text_SailHome, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	clearflag FLAG_SAFE_FOLLOWER_MOVEMENT
	hideobjectat LOCALID_BATTLE_FRONTIER_SAILOR_HNS, MAP_BATTLE_FRONTIER_OUTSIDE_WEST_HNS
	setvar VAR_0x8004, LOCALID_FARAWAY_BATTLE_FRONTIER_HNS_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	warpsilent MAP_OLIVINE_CITY_PORT_INSIDE_HNS, 8, 16
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_AsYouLike_hns::
	msgbox EventTicket_Text_AsYouLike, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_BattleDomeSign_hns::
	msgbox BattleFrontier_OutsideWest_Text_BattleDomeSign_hns, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattleFactorySign_hns::
	msgbox BattleFrontier_OutsideWest_Text_BattleFactorySign_hns, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattlePikeSign_hns::
	msgbox BattleFrontier_OutsideWest_Text_BattlePikeSign_hns, MSGBOX_SIGN
	end

@ Unused. Of note, Battle Tower is in the East section in the final release
BattleFrontier_OutsideWest_EventScript_UnusedNPC1_hns::
	msgbox BattleFrontier_OutsideWest_Text_ThisIsBattleTower_hns, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC2_hns::
	msgbox BattleFrontier_OutsideWest_Text_CantFindBattleTower_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Boy1_hns::
	msgbox BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Fisherman2_hns::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere_hns
	waitmessage
	applymovement LOCALID_FRONTIER_FISHERMAN_2, Common_Movement_FaceAwayPlayer
	waitmovement 0
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_Man1_hns::
	msgbox BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Maniac1_hns::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk_hns
	end

BattleFrontier_OutsideWest_EventScript_Maniac2_hns::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk_hns
	end

BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk_hns::
	applymovement LOCALID_FRONTIER_MANIAC_1, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons_hns, MSGBOX_DEFAULT
	applymovement LOCALID_FRONTIER_MANIAC_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons_hns, MSGBOX_DEFAULT
	closemessage
	delay 25
	applymovement LOCALID_FRONTIER_MANIAC_1, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_FRONTIER_MANIAC_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_Camper_hns::
	lock
	faceplayer
	delay 20
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_Camper_hnsFaceFactory_hns
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_Camper_hnsAlreadyFacingFactory_hns
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_Camper_hnsFaceFactory_hns
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_Camper_hnsFaceFactory_hns
	msgbox BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Camper_hnsFaceFactory_hns::
	applymovement LOCALID_FRONTIER_CAMPER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_Camper_hnsAlreadyFacingFactory_hns::
	return

BattleFrontier_OutsideWest_EventScript_Girl_hns::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper_hns
	waitmessage
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_Girl_hnsShudderNorth_hns
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_Girl_hnsShudderSouth_hns
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_Girl_hnsShudderWest_hns
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_Girl_hnsShudderEast_hns
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_Girl_hnsShudderNorth_hns::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderNorth_hns
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_Girl_hnsShudderSouth_hns::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderSouth_hns
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_Girl_hnsShudderWest_hns::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderWest_hns
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_Girl_hnsShudderEast_hns::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderEast_hns
	waitmovement 0
	return

BattleFrontier_OutsideWest_Movement_GirlShudderNorth_hns:
	walk_in_place_faster_down
	walk_in_place_faster_down
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderSouth_hns:
	walk_in_place_faster_up
	walk_in_place_faster_up
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderWest_hns:
	walk_in_place_faster_right
	walk_in_place_faster_right
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderEast_hns:
	walk_in_place_faster_left
	walk_in_place_faster_left
	step_end

BattleFrontier_OutsideWest_EventScript_Woman2_hns::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors_hns, MSGBOX_DEFAULT
	random 2
	goto_if_eq VAR_RESULT, 1, BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors_hns
	goto BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors_hns
	end

BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors_hns::
	msgbox BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors_hns::
	msgbox BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Fisherman1_hns::
	msgbox BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling_hns, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC3_hns::
	msgbox BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Gentleman_hns::
	msgbox BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Lass_hns::
	msgbox BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_ExpertM_hns::
	msgbox BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man2_hns::
	msgbox BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman1_hns::
	msgbox BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan1_hns::
	msgbox BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan2_hns::
	msgbox BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman3_hns::
	lock
	msgbox BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Boy2_hns::
	lock
	msgbox BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_OldMan_hns::
	msgbox BattleFrontier_OutsideWest_Text_DomeAceIsMine_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man4_hns::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_MAN_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_PokefanF_hns::
	msgbox BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Text_BattleDomeSign_hns:
	.string "זוהי כיפת הקרב!\n"
	.string "הדרך שלכם להפוך לכוכב-על בלתי מנוצח!$"

BattleFrontier_OutsideWest_Text_BattleFactorySign_hns:
	.string "זהו מפעל הקרב!\n"
	.string "חפשו את הפוקימונים החזקים ביותר!$"

BattleFrontier_OutsideWest_Text_BattlePikeSign_hns:
	.string "זהו שביל הקרב!\n"
	.string "בחרו אחת משלוש דרכים!$"

BattleFrontier_OutsideWest_Text_ThisIsBattleTower_hns:
	.string "This is the BATTLE TOWER.\p"
	.string "TRAINERS bring their best-raised\n"
	.string "POKéMON for elimination-style matches.$"

BattleFrontier_OutsideWest_Text_MayISeeYourTicket_hns:
	.string "Hello, are you here for the ferry?\n"
	.string "May I see your TICKET?$"

BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard_hns:
	.string "{PLAYER} doesn't have the TICKET…\p"
	.string "I'm terribly sorry.\p"
	.string "You must have a TICKET to board\n"
	.string "the ferry.$"

BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo_hns:
	.string "{PLAYER} flashed the TICKET.\p"
	.string "Perfect! That's all you need!\p"
	.string "And where would you like to go?$"

BattleFrontier_OutsideWest_Text_SlateportItIs_hns:
	.string "SLATEPORT CITY it is, then!$"

BattleFrontier_OutsideWest_Text_LilycoveItIs_hns:
	.string "LILYCOVE CITY it is, then!$"

BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime_hns:
	.string "Please sail with us another time!$"

BattleFrontier_OutsideWest_Text_PleaseBoardFerry_hns:
	.string "Please board the ferry and wait for\n"
	.string "departure.$"

BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo_hns:
	.string "Then, where would you like to go?$"

BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends_hns:
	.string "אני הכי טוב מכל החברים שלי.\n"
	.string "אבל כאן… לא הייתי שווה כלום!$"

BattleFrontier_OutsideWest_Text_CantFindBattleTower_hns:
	.string "I want to go to the BATTLE TOWER,\n"
	.string "but I can't find it even though I have\l"
	.string "a map of the BATTLE FRONTIER.\p"
	.string "This place is just too big!$"

BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere_hns:
	.string "רציתי להתמודד באתגר ברגע\n"
	.string "שהגעתי לכאן.\p"
	.string "אבל בדרך, קיבלתי מחלת ים…\n"
	.string "אוווורפ…$"

BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere_hns:
	.string "זה לא שכל אחד יכול לבוא לכאן,\n"
	.string "אתה יודע?\p"
	.string "רק מאמנים שהוכרו כקשוחים\n"
	.string "מובאים לכאן.\p"
	.string "בגלל זה הרבה מאמנים בכלל לא\n"
	.string "יודעים על חזית הקרב.$"

BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons_hns:
	.string "היי, אחי…\p"
	.string "אתה בטוח שאפשר להתמודד באתגרים\n"
	.string "גם אם אין לנו פוקימונים?$"

BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons_hns:
	.string "אה…\n"
	.string "בטח יהיה בסדר.\p"
	.string "אני חושב…\p"
	.string "אבל זוכר את הבחור הגדול והמפחיד?\n"
	.string "הוא אמר: ”אשאיל לכם פוקימונים!”$"

BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons_hns:
	.string "זה מפעל הקרב.\n"
	.string "אפשר לשכור שם פוקימונים חזקים.\p"
	.string "אבל זה גורם לי לתהות.\n"
	.string "מי מגדל את הפוקימונים השכורים?$"

BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper_hns:
	.string "אני מפחדת להיכנס לשביל הקרב\n"
	.string "בגלל סוויפר…\p"
	.string "א-אבל באתי עד לכאן, אז אנסה\n"
	.string "לכבוש הכול! …צמרמורת…$"

BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors_hns:
	.string "קדימה, נשחק אבן, נייר ומספריים!\n"
	.string "אחת, שתיים, שלוש!\p"
	.string "… … … … … …$"

BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge_hns:
	.string "יש! ניצחתי!\n"
	.string "אתמודד באתגר שביל הקרב!$"

BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge_hns:
	.string "אוי, לא…\n"
	.string "הפסדתי.\p"
	.string "כנראה שהמזל לא לצידי היום.\n"
	.string "אדחה את אתגר שביל הקרב למחר.$"

BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling_hns:
	.string "נראה לי שאני היחיד כאן שמסיבה\n"
	.string "לא ידועה מעדיף דיג על פני קרבות.\p"
	.string "מה? אי אפשר לתפוס כאן כלום?\n"
	.string "איזו אכזבה…$"

BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol_hns:
	.string "היום אמשיך להילחם, ויהי מה,\n"
	.string "עד שאשיג סמל.$"

BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome_hns:
	.string "הו? אתה בדרך לאתגר את\n"
	.string "כיפת הקרב?\p"
	.string "אני מאחל לך הרבה מזל.\p"
	.string "הבה נתקדם שנינו מניצחון לניצחון\n"
	.string "וניפגש באתגרים.$"

BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa_hns:
	.string "Grandpa, over here!\n"
	.string "The BATTLE DOME is here!\l"
	.string "Go get 'em, Grandpa!$"

BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe_hns:
	.string "אה, אז זאת כיפת הקרב?\n"
	.string "לא אתן לג'נטלמנים לנצח אותי!\p"
	.string "אבל איפה הכניסה?$"

BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo_hns:
	.string "לפני לא הרבה זמן, לא היה כאן\n"
	.string "כלום.\p"
	.string "אבל תראה את המקום עכשיו! מדהים!\n"
	.string "אביא את אמא שלי לראות את זה.$"

BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier_hns:
	.string "סוף סוף הגעתי לחזית הקרב!\p"
	.string "אני בטוחה שאמשוך תשומת לב\n"
	.string "בזכות המראה והכישורים שלי!$"

BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople_hns:
	.string "נשנוש, נשנוש…\p"
	.string "נראה שהכיכר הזאת מלאה\n"
	.string "באנשים קשוחים.\p"
	.string "נשנוש, נשנוש…$"

BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike_hns:
	.string "קראנץ', נשנוש…\p"
	.string "לפני זמן מה, פגשתי בחורה מבוגרת ממני\n"
	.string "בשביל הקרב.\p"
	.string "היו לה עיניים מפחידות,\n"
	.string "ממש רעות ועצבניות.\p"
	.string "קראנץ', נשנוש…\p"
	.string "היא התעצבנה נורא: ”תפסיק כבר\n"
	.string "לאכול!” ואז היא הרביצה לי.\p"
	.string "זאת הייתה חוויה מפחידה, מסמרת\n"
	.string "שיער, ללא ספק.\p"
	.string "קראנץ', נשנוש…$"

BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet_hns:
	.string "מה? אתה שומע את עצמך?\n"
	.string "זה כלום!\p"
	.string "הרי בפעם האחרונה שעודדתי אותו,\n"
	.string "המבטים שלנו נפגשו ועפו ניצוצות!$"

BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering_hns:
	.string "מהההההה?!\n"
	.string "פפף!\p"
	.string "זה קרה רק כי במקרה\n"
	.string "ישבתי לידך!\p"
	.string "אס הכיפה הסתכל לכיוון שלנו רק\n"
	.string "כי העידוד שלי היה כל כך רועש!$"

BattleFrontier_OutsideWest_Text_DomeAceIsMine_hns:
	.string "אוי, שקט!\n"
	.string "תורידו את הרעש!\p"
	.string "אוהדים הפכפכים כמוכם צריכים\n"
	.string "להסתפק בעידוד של איזה מנהיג מכון!\p"
	.string "אס הכיפה שלי!\n"
	.string "האליל היחיד שלי!$"

BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers_hns:
	.string "האנשים שמתקוטטים שם…\p"
	.string "קשה להאמין, אבל פעם הם היו\n"
	.string "מאמנים, ומאמנים טובים.\p"
	.string "הם היו קשוחים להפליא,\n"
	.string "וגם מפורסמים.\p"
	.string "אבל מאמן מסוים מחץ אותם\n"
	.string "בטורניר אחד.\p"
	.string "הם הובסו כל כך, שהם\n"
	.string "התאהבו במאמן הזה.\p"
	.string "עכשיו הם סתם מעריצים שלו.\p"
	.string "כל יום הם הולכים לעודד את\n"
	.string "האליל שלהם בכיפת הקרב.$"

BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier_hns:
	.string "שמועה אומרת שמישהו ראה פוקימון עם\n"
	.string "זנב ארוך במיוחד, אי שם בחזית הקרב.\p"
	.string "הוא בטח מקסים. אני בטוח בזה…\p"
	.string "אה, האתגרים יכולים לחכות. אני חייב\n"
	.string "למצוא את היצור המקסים הזה!$"

