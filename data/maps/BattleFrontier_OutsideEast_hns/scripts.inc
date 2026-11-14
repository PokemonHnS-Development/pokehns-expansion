BattleFrontier_OutsideEast_hns_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_OutsideEast_OnResume_hns
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideEast_OnTransition_hns
	.byte 0

BattleFrontier_OutsideEast_OnResume_hns:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo_hns
	end

BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo_hns::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

BattleFrontier_OutsideEast_OnTransition_hns:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	call_if_unset FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_ShowSudowoodo_hns
	end

BattleFrontier_OutsideEast_EventScript_ShowSudowoodo_hns::
	clearflag FLAG_HIDE_BATTLE_FRONTIER_SUDOWOODO
	return

BattleFrontier_OutsideEast_EventScript_BattleTowerSign_hns::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerSign_hns, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign_hns::
	msgbox BattleFrontier_OutsideEast_Text_BattlePalaceSign_hns, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattleArenaSign_hns::
	msgbox BattleFrontier_OutsideEast_Text_BattleArenaSign_hns, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign_hns::
	msgbox BattleFrontier_OutsideEast_Text_BattlePyramidSign_hns, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_NinjaBoy_hns::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man1_hns::
	msgbox BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Hiker_hns::
	msgbox BattleFrontier_OutsideEast_Text_PyramidTooHarsh_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_HexManiac_hns::
	msgbox BattleFrontier_OutsideEast_Text_ThriveInDarkness_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt1_hns::
	msgbox BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Cook_hns::
	lock
	msgbox BattleFrontier_OutsideEast_Text_BelieveInYouBuddy_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Zigzagoon_hns::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant_hns, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_OutsideEast_EventScript_RichBoy_hns::
	msgbox BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_ExpertF_hns::
	msgbox BattleFrontier_OutsideEast_Text_OnceBeatGymLeader_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_TriathleteF_hns::
	msgbox BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Twin_hns::
	msgbox BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man2_hns::
	lock
	msgbox BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_TriathleteM_hns::
	msgbox BattleFrontier_OutsideEast_Text_DidScottBringYouHere_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Sudowoodo_hns::
	lock
	faceplayer
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_FRONTIER_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake_hns
	waitmovement 0
	release
	end

BattleFrontier_OutsideEast_EventScript_WaterSudowoodo_hns::
	lock
	faceplayer
	special DoWateringBerryTreeAnim
	waitstate
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_FRONTIER_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake_hns
	waitmovement 0
	msgbox gText_Sudowoodo_Attacked, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SUDOWOODO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_FRONTIER_SUDOWOODO
	setwildbattle SPECIES_SUDOWOODO, 40
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo_hns
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo_hns
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo_hns
	setflag FLAG_DEFEATED_SUDOWOODO
	release
	end

BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo_hns::
	setflag FLAG_DEFEATED_SUDOWOODO
	goto Common_EventScript_RemoveStaticPokemon
	end

BattleFrontier_OutsideEast_Movement_SudowoodoShake_hns:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	step_end

BattleFrontier_OutsideEast_EventScript_Maniac1_hns::
	msgbox BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Girl_hns::
	msgbox BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_PsychicM_hns::
	msgbox BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man3_hns::
	msgbox BattleFrontier_OutsideEast_Text_GotWipedOut_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman1_hns::
	msgbox BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman2_hns::
	msgbox BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt2_hns::
	msgbox BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Maniac2_hns::
	lock
	msgbox BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Woman3_hns::
	lock
	msgbox BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RankingHallSign_hns::
	msgbox BattleFrontier_OutsideEast_Text_RankingHallSign_hns, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_ExchangeCornerSign_hns::
	msgbox BattleFrontier_OutsideEast_Text_ExchangeCornerSign_hns, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_Gentleman_hns::
	msgbox BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_OldWoman_hns::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_OldWoman_hnsSudowoodoGone_hns
	msgbox BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_OldWoman_hnsSudowoodoGone_hns::
	msgbox BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Camper_hns::
	msgbox BattleFrontier_OutsideEast_Text_StickyMonWithLongTail_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Text_BattleTowerSign_hns:
	.string "זהו מגדל הקרב!\n"
	.string "המשיכו ברצף הניצחונות כמאמן\l"
	.string "הקשוח ביותר!$"

BattleFrontier_OutsideEast_Text_BattlePalaceSign_hns:
	.string "זהו ארמון הקרב!\n"
	.string "אל תורידו עיניים מקרבות הפוקימונים!$"

BattleFrontier_OutsideEast_Text_BattleArenaSign_hns:
	.string "זוהי זירת הקרב!\n"
	.string "שהקבוצות הקשוחות ביותר יתאספו!$"

BattleFrontier_OutsideEast_Text_BattlePyramidSign_hns:
	.string "זוהי פירמידת הקרב!\n"
	.string "התקדמו במסע הקרב!$"

BattleFrontier_OutsideEast_Text_RankingHallSign_hns:
	.string "היכל הדירוג של חזית הקרב\n"
	.string "כוונו לשיאים חדשים!$"

BattleFrontier_OutsideEast_Text_ExchangeCornerSign_hns:
	.string "פינת שירות ההמרה של נקודות קרב\n"
	.string "המירו את נקודות הקרב שלכם!$"

BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial_hns:
	.string "וואו!\n"
	.string "הוא ענק!\p"
	.string "יש משהו מיוחד במגדל הקרב.\n"
	.string "הוא שונה מכל השאר.$"

BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier_hns:
	.string "השאיפה הגדולה שלי: לכבוש גם את\n"
	.string "חזית הקרב וגם את ליגת הפוקימון.\p"
	.string "ואם החלום שלי יתגשם…\p"
	.string "אני… אני אשאל את מימי מהבית ליד\n"
	.string "אם היא תסכים להיות ידידה שלי!$"

BattleFrontier_OutsideEast_Text_PyramidTooHarsh_hns:
	.string "פירמידת הקרב קשוחה מדי!\n"
	.string "אני פשוט לא מצליח להגיע לפסגה!\p"
	.string "אין לי ברירה אחרת, אז אולי\n"
	.string "אטפס עליה מבחוץ…$"

BattleFrontier_OutsideEast_Text_ThriveInDarkness_hns:
	.string "אני פורחת בחשכה… כן… מה ראוי לי?\n"
	.string "רק פירמידת הקרב, ולא אחרת…\p"
	.string "מה תאמר על שיטוט בחשכה,\n"
	.string "בייאוש מוחלט וגמור?$"

BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam_hns:
	.string "לא ישנתי שבוע שלם, אבל אז\n"
	.string "הרכבתי את הקבוצה האולטימטיבית!\p"
	.string "אין מצב שאני מפסיד, בלי צחוק.\n"
	.string "אנחנו מסתערים על זירת הקרב!$"

BattleFrontier_OutsideEast_Text_DidScottBringYouHere_hns:
	.string "גם אותך סקוט הביא לכאן?\n"
	.string "מה הקטע עם הבחור הזה?\p"
	.string "נשמע שהוא באמת יודע לזהות\n"
	.string "מאמנים מוכשרים, אבל…\p"
	.string "אף פעם לא ראיתי אותו נלחם\n"
	.string "בעצמו.$"

BattleFrontier_OutsideEast_Text_BelieveInYouBuddy_hns:
	.string "זיג!\n"
	.string "אני מאמין בך, חבר קטן!\p"
	.string "אם תנצח, זיג הקטן שלי, אכין לך\n"
	.string "את כל הפינוקים הטעימים שתרצה!$"

BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant_hns:
	.string "זיגזגון בוהה בחלל…$"

BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody_hns:
	.string "אומרים שאני דוחף את האף לכל דבר,\n"
	.string "אבל אני לא יכול להתאפק.\p"
	.string "הכובע שלך עקום!\n"
	.string "אוי לא, זבל על הארץ!\p"
	.string "אופס, כמעט שעת ארוחת ערב!\p"
	.string "אני לא יודע אם אוכל להסתפק\n"
	.string "בצפייה בארמון הקרב…$"

BattleFrontier_OutsideEast_Text_OnceBeatGymLeader_hns:
	.string "אולי אני לא נראית מרשימה עכשיו,\n"
	.string "אבל פעם ניצחתי מנהיג מכון.\p"
	.string "מי יודע, אולי כדאי לי לנסות שוב\n"
	.string "לזכות בתהילה.$"

BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles_hns:
	.string "אני מהירה על האופניים, וזה נכון\n"
	.string "גם לגבי הדרך שבה אני נלחמת.\p"
	.string "אני מנצחת בקרבות\n"
	.string "כהרף עין!$"

BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon_hns:
	.string "אני יותר טובה מאבא שלי\n"
	.string "בפוקימונים.$"

BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy_hns:
	.string "קדימה, מתוקה שלי!\n"
	.string "לכי תאספי כמה ניצחונות בשביל אבא!\p"
	.string "את בדיוק כמו אמא שלך,\n"
	.string "אז את תנצחי את כולם בגדול!$"

BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena_hns:
	.string "לא היה קל להגיע לכאן, אבל שמעתי\n"
	.string "על בחורה מהממת בזירת הקרב.\p"
	.string "ובמקומה, אתה יודע מה מצאתי?\p"
	.string "המון סואן של אמני לחימה מיוזעים,\n"
	.string "מסריחים ופרימיטיביים!$"

BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere_hns:
	.string "לפעמים אני רואה זקן אחד שנראה\n"
	.string "ממש חשוב נכנס לשם.\p"
	.string "יש לו פוקימונים ממש מדהימים.\n"
	.string "אבל הוא נראה ממש נחמד.$"

BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid_hns:
	.string "שמעת עליה?\n"
	.string "על האגדה של פירמידת הקרב?\p"
	.string "כאשר יבוא מאמן בטוח בעצמו\n"
	.string "השולח ידו אל הפסגה המוזהבת,\p"
	.string "יופיע גבר שבגברים.\p"
	.string "לא שמעת על האגדה הזאת?\n"
	.string "טוב, ברור שלא! הרגע המצאתי אותה!\p"
	.string "מה זה אמור להגיד?\n"
	.string "את זה, ידידי, אני לא יכולה לומר!$"

BattleFrontier_OutsideEast_Text_GotWipedOut_hns:
	.string "אוף! אוף, אוף!\n"
	.string "אף פעם לא הפסדתי לפני כן!\p"
	.string "אבל נמחקתי לגמרי, בלי שום\n"
	.string "נקודת אור!\p"
	.string "ואז עוד אומרים לי שאין לי\n"
	.string "שום כישרון?! אוף!$"

BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower_hns:
	.string "הבחור הזה נתקל במאמן קשוח להחריד\n"
	.string "בזמן שהיה באתגר מגדל הקרב.\p"
	.string "תראה אותו עכשיו…\p"
	.string "צריך להיזהר אם תחליט פעם\n"
	.string "ללכת למגדל הקרב.$"

BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll_hns:
	.string "יש!\n"
	.string "סוף סוף יש לי מספיק נקודות קרב!\p"
	.string "נראה לי שאמיר אותן\n"
	.string "בעוד בובת פרווה ענקית!$"

BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere_hns:
	.string "אה, כן, אוקיי!\n"
	.string "אז זה היכל הדירוג!\p"
	.string "הייתי רוצה להיכנס להיסטוריה כאלוף-על\n"
	.string "ושהשם שלי יירשם כאן לדורות.$"

BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou_hns:
	.string "כשאת לצידי, אני יכול לעשות הכול.$"

BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome_hns:
	.string "אוו, יקירי, אתה כל כך נפלא!\p"
	.string "אוו, אני פשוט לא יכולה לחכות יותר!\p"
	.string "בוא נלך לחדר קרב מרובה\n"
	.string "ברגע זה!\p"
	.string "אם נתאחד בסלון הקרב, כוח האהבה\n"
	.string "שלנו יגבר על כל מי שנפגוש.\p"
	.string "הרי לפנינו, יקירי, הכול ייפול\n"
	.string "כמו אבני דומינו!$"

BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers_hns:
	.string "חזית הקרב לא מיועדת רק\n"
	.string "למאמנים קשוחים.\p"
	.string "נראה שהוזמנו לכאן אנשים רבים\n"
	.string "בעלי יכולות מיוחדות.\p"
	.string "האיש ההוא, סקוט…\p"
	.string "ייתכן שהוא בנה את המקום הזה\n"
	.string "למען מטרה גדולה יותר…$"

BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle_hns:
	.string "Excuse me, young one.\n"
	.string "Have you good eyesight?\p"
	.string "There is an odd tree past here, and to\n"
	.string "my tired eyes it seems to wiggle.$"

BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere_hns:
	.string "Excuse me, young one.\n"
	.string "Have you a good memory?\p"
	.string "I have this feeling there once was\n"
	.string "an odd tree past here.$"

BattleFrontier_OutsideEast_Text_StickyMonWithLongTail_hns:
	.string "I…\n"
	.string "I saw it!\p"
	.string "There was a sticky sort of a POKéMON\n"
	.string "with a long tail up ahead!\p"
	.string "It was hiding under a boulder, and\n"
	.string "it kept staring at me!$"
