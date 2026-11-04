SinjohRuins_House1_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SinjohRuins_Lab_OnFrame
	map_script 	MAP_SCRIPT_ON_TRANSITION, SinjohRuins_Lab_OnTransition
	.byte 0

SinjohRuins_Lab_OnTransition::
	call_if_eq VAR_SINJOH_STORYLINE, 7, SinjohRuins_Lab_SetupFinalPlateScene
	end

SinjohRuins_Lab_OnFrame::
	map_script_2 VAR_SINJOH_STORYLINE, 7, SinjohRuins_Lab_FinalPlateScene
	.2byte 0

@==========================Intro Cutscene SCRIPTS================================================================================

SinjohRuins_Lab_EventScript_TriggerIntroTop::
	lock
	playse SE_PIN
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene1, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_PLAYER, Common_Movement_WalkDown1
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenMeetPlayer
	waitmovement 0
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	goto SinjohRuins_Lab_EventScript_TriggerIntro

SinjohRuins_Lab_EventScript_TriggerIntroMid::
	lock
	playse SE_PIN
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene1, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenMeetPlayer
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	goto SinjohRuins_Lab_EventScript_TriggerIntro

SinjohRuins_Lab_EventScript_TriggerIntroBot::
	lock
	playse SE_PIN
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene1, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_PLAYER, Common_Movement_WalkUp1
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenMeetPlayer
	waitmovement 0
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	goto SinjohRuins_Lab_EventScript_TriggerIntro

SinjohRuins_Lab_EventScript_TriggerIntro::
	turnobject LOCALID_PLAYER, DIR_EAST
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene2, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenSitsDown
	delay 10
	applymovement LOCALID_PLAYER, SinjohRuins_Lab_Movement_PlayerGoesToTable
	delay 40
	applymovement2 LOCALID_NEWSINJOH_LAB_LINGUIST, SinjohRuins_Lab_Movement_LinguistWalkDown
	waitmovement 0
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	waitmovement LOCALID_NEWSINJOH_LAB_LINGUIST
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene3, MSGBOX_DEFAULT
	closemessage
	delay 10
	applymovement2 LOCALID_NEWSINJOH_LAB_LINGUIST, Common_Movement_WalkInPlaceDown
	waitmovement 0
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene4, MSGBOX_DEFAULT
	closemessage
	delay 10
	applymovement LOCALID_NEWSINJOH_LAB_LINGUIST, SinjohRuins_Lab_Movement_LinguistWalkUp
	applymovement2 LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_WalkInPlaceRight
	waitmovement 0
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene5, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, SinjohRuins_Lab_EventScript_IntroChoseYes
SinjohRuins_Lab_EventScript_IntroChoice::
	msgbox SinjohRuins_Lab_Text_StevenIntroCutsceneRefused, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, SinjohRuins_Lab_EventScript_IntroChoseYes
	goto SinjohRuins_Lab_EventScript_IntroChoice

SinjohRuins_Lab_EventScript_IntroChoseYes::
	msgbox SinjohRuins_Lab_Text_StevenIntroCutscene6, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SINJOH_STORYLINE, 6
	setvar VAR_NOBLE_SNEASLER, 1
	setvar VAR_NOBLE_OVERQWIL, 1
	setvar VAR_NOBLE_WYRDEER, 1
	setvar VAR_NOBLE_ARCANINE, 1
	setvar VAR_NOBLE_URSALUNA, 1
	setvar VAR_NOBLE_KLEAVOR, 1
	setvar VAR_NOBLE_ELECTRODE, 1
	setvar VAR_NOBLE_TYPHLOSION, 1
	release
	end

SinjohRuins_Lab_Movement_StevenMeetPlayer:
	walk_up
	walk_up
	walk_up
	face_left
	step_end

SinjohRuins_Lab_Movement_StevenSitsDown:
	walk_down
	walk_down
	walk_down
	face_right
	step_end

SinjohRuins_Lab_Movement_PlayerGoesToTable:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_right
	face_left
	step_end

SinjohRuins_Lab_Movement_LinguistWalkDown:
	walk_down
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	face_down
	step_end

SinjohRuins_Lab_Movement_LinguistWalkUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	step_end


SinjohRuins_Lab_Text_StevenIntroCutscene1:
   	.string "סטיבן: הממ?$"

SinjohRuins_Lab_Text_StevenIntroCutscene2:
	.string "סטיבן: {PLAYER}!\p"
	.string "הייתי מזהה את העיניים האלה בכל מקום.\p"
	.string "מה מביא אותך כל כך רחוק צפונה?\p"
	.string "…………\p"
	.string "אני מבין, נערות הקימונו של סינג'ו החדשה\n"
	.string "שלחו אותך לעזור לחקירה שלנו.\p"
	.string "אם כך, אעדכן אותך בכל הפרטים.$"

SinjohRuins_Lab_Text_StevenIntroCutscene3:
	.string "סטיבן: כששמעתי לראשונה על החורבות\n"
	.string "האלה, הייתי חייב לראות אותן בעצמי.\p"
	.string "הרכבתי צוות מחברת דבון\n"
	.string "ויצאנו למשלחת מחקר.\p"
	.string "מי יודע מה עוד נגלה כאן מתחת לאדמה.\p"
	.string "כבר למדנו לא מעט.$"

SinjohRuins_Lab_Text_StevenIntroCutscene4:
	.string "בלשנית: עוד לא הצלחתי לתרגם\n"
	.string "במלואן את הכתובות שסביב החורבות,\p"
	.string "אבל כבר פענחתי כמה דברים.\p"
	.string "יש 17 לוחות משונים.\p"
	.string "הם קשורים איכשהו לחורבות,\n"
	.string "אבל עד עכשיו מצאנו רק 1.\p"
	.string "אומרים שאת השאר שומרים\n"
	.string "פוקימונים ומאמנים בעלי כוח אדיר.$"

SinjohRuins_Lab_Text_StevenIntroCutscene5:
	.string "סטיבן: זה הסיפור, {PLAYER}.\p"
	.string "לצערי, הפוקימונים האציליים ששומרים\n"
	.string "על שאר הלוחות חזקים מדי לצוות שלי.\p"
	.string "ואני צריך להישאר כאן\n"
	.string "כדי לפקח על המחקר.\p"
	.string "אבל אני חושב שזה בהישג ידך.\n"
	.string "תעזור לנו?$"

SinjohRuins_Lab_Text_StevenIntroCutscene6:
	.string "מצוין.\p"
	.string "לפי הכתובות, הלוחות בידי פוקימונים\n"
	.string "אציליים ומאמנים חזקים ברחבי סינג'ו.\p"
	.string "אתקשר לפוקיגיר שלך\n"
	.string "אם נגלה משהו חדש.\p"
	.string "תודה, {PLAYER}.$"

SinjohRuins_Lab_Text_StevenIntroCutsceneRefused:
	.string "אתה בטוח?\p"
	.string "מי יודע מה עוד נגלה כאן מתחת לאדמה.\p"
	.string "אולי תשקול שוב?$"

@==========================Final plate Cutscene SCRIPTS================================================================================

SinjohRuins_Lab_SetupFinalPlateScene::
	setobjectxyperm LOCALID_SINJOHRUINS_LAB_STEVEN, 4, 7
	setobjectmovementtype LOCALID_SINJOHRUINS_LAB_STEVEN, MOVEMENT_TYPE_FACE_RIGHT
	setobjectxyperm LOCALID_NEWSINJOH_LAB_LINGUIST, 5, 7
	setobjectmovementtype LOCALID_NEWSINJOH_LAB_LINGUIST, MOVEMENT_TYPE_FACE_LEFT
	return

SinjohRuins_Lab_FinalPlateScene::
	lock
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkUp1
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SINJOHRUINS_LAB_STEVEN
	turnobject LOCALID_SINJOHRUINS_LAB_STEVEN, DIR_SOUTH
	delay 30
	applymovement LOCALID_SINJOHRUINS_LAB_STEVEN, Common_Movement_WalkDown1
	turnobject LOCALID_NEWSINJOH_LAB_LINGUIST, DIR_SOUTH
	delay 30
	msgbox SinjohRuins_Lab_Text_FinalPlateScene1, MSGBOX_DEFAULT
	closemessage
	dofieldeffectsparkle 3, 8, 0
	waitfieldeffect FLDEFF_SPARKLE
	setvar VAR_RESULT, 3
	playfanfare MUS_AWAKEN_LEGEND
	playse SE_ORB
	special DoOrbEffect
	delay 200
	special FadeOutOrbEffect
	waitstate
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 40  @ num shakes
	setvar VAR_0x8007, 3  @ shake delay
	special ShakeCamera
	waitstate
	msgbox SinjohRuins_Lab_Text_FinalPlateScene2, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, SinjohRuins_Lab_Movement_PlayerLeaveLab
	applymovement LOCALID_SINJOHRUINS_LAB_STEVEN, SinjohRuins_Lab_Movement_StevenLeaveLab
	waitmovement 0
	waitmovement 0
	setvar VAR_SINJOH_STORYLINE, 8
	warp MAP_SINJOH_RUINS_HNS, 0
	waitstate
	end

SinjohRuins_Lab_Text_FinalPlateScene1:
	.string "סטיבן: {PLAYER}!\p"
	.string "נראה לי שאני יודע מה יקרה\n"
	.string "כשנאחד את כל 17 הלוחות.\p"
	.string "אני מרגיש…\n"
	.string "…………$"

SinjohRuins_Lab_Text_FinalPlateScene2:
	.string "סטיבן: אני חייב לראות את זה בעצמי!\p"
	.string "החוצה, {PLAYER}!$"

SinjohRuins_Lab_Movement_PlayerLeaveLab:
	walk_fast_down
	walk_fast_down
	walk_in_place_fast_down
	step_end

SinjohRuins_Lab_Movement_StevenLeaveLab:
	walk_fast_down
	walk_fast_down
	walk_in_place_fast_down
	step_end

@==========================NPC SCRIPTS================================================================================

SinjohRuins_Lab_EventScript_Steven::
	lock
	faceplayer
	buffernumberstring STR_VAR_1, VAR_PLATECOUNTER
	goto_if_ge VAR_PLATECOUNTER, 17, SinjohRuins_Lab_EventScript_StevenAfterAllPlates
	goto_if_ge VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_StevenAfter15Plates
	goto_if_ge VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_StevenAfter12Plates
	goto_if_ge VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_StevenAfter9Plates
	goto_if_ge VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_StevenAfter6Plates
	goto_if_ge VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_StevenAfter3Plates
	msgbox SinjohRuins_Lab_Text_StevenFindPlates, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter3Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates3, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter6Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates3, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter9Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates9, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter12Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates9, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfter15Plates::
	msgbox SinjohRuins_Lab_Text_StevenFindPlates9, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_EventScript_StevenAfterAllPlates::
	msgbox SinjohRuins_Lab_Text_StevenAfterAll, MSGBOX_AUTOCLOSE
	release
	end

SinjohRuins_Lab_Text_StevenFindPlates:
	.string "סטיבן: אה, {PLAYER}.\p"
	.string "{STR_VAR_1} לוחות עד עכשיו.\n"
	.string "לא רע בכלל.\p"
	.string "אני חייב להודות,\n"
	.string "אני סקרן לדעת מה יקרה כשכולם ייאספו.\p"
	.string "ובכן, בוא נראה מה תמצא.$"

SinjohRuins_Lab_Text_StevenFindPlates3:
	.string "סטיבן: אה, {PLAYER}.\p"
	.string "{STR_VAR_1} לוחות עד עכשיו.\n"
	.string "לא רע בכלל.\p"
	.string "כבר בדקת את החדר ההוא?\n"
	.string "הכול מאוד מסתורי.$"

SinjohRuins_Lab_Text_StevenFindPlates9:
	.string "סטיבן: אה, {PLAYER}.\p"
	.string "{STR_VAR_1} לוחות עד עכשיו.\n"
	.string "התקדמות יפה מאוד.\p"
	.string "החדרים שנפתחו דומים להפליא\n"
	.string "לסדרת חדרים באזור הואן.\p"
	.string "בכל אחד מהחדרים ההם שכן גם\n"
	.string "פוקימון אגדי.\p"
	.string "אבל בהואן נתגלו עד היום רק 3.\p"
	.string "וכאן יש לפחות 6.\p"
	.string "מי יודע מה עוד נגלה.$"

SinjohRuins_Lab_Text_StevenAfterAll:
	.string "סטיבן: {PLAYER}!\p"
	.string "המשלחת הזאת הייתה\n"
	.string "חוויה של פעם בחיים.\p"
	.string "מאז ששמעתי על החורבות האלה,\n"
	.string "הייתה לי תחושה.\p"
	.string "חשבתי שנגלה משהו מדהים.\p"
	.string "והתחזיות שלי בדרך כלל מתגשמות.\p"
	.string "תודה על כל העזרה, אלוף.\p"
	.string "לאן תמשיך מכאן?\p"
	.string "אני מקווה שניפגש שוב איפשהו.$"

SinjohRuins_Lab_EventScript_Geologist::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SinjohRuins_Lab_EventScript_GeologistAfterEvent
	goto_if_ge VAR_SINJOH_STORYLINE, 9, SinjohRuins_Lab_EventScript_GeologistDuringEvent
	msgbox SinjohRuins_Lab_Text_Geologist MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_GeologistDuringEvent::
	msgbox SinjohRuins_Lab_Text_GeologistDuring, MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_GeologistAfterEvent::
	msgbox SinjohRuins_Lab_Text_GeologistAfter, MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Geologist:
    .string "מכ”ם חודר קרקע מראה\n"
    .string "6 חדרים תת-קרקעיים בעמק הזה.\p"
    .string "5 מהם נראים קרובים יותר לפני השטח,\n"
    .string "ו-1 קבור עמוק עוד יותר.$"
SinjohRuins_Lab_Text_GeologistDuring:
	.string "כל הזמן הזה כיוונתי את הציוד שלי\n"
	.string "למטה כדי לצלם את מה שמתחת לאדמה.\p"
	.string "כשברור שהייתי צריך לכוון אותו למעלה!$"
SinjohRuins_Lab_Text_GeologistAfter:
	.string "הלוחות האלה היו קשורים\n"
	.string "לפוקימון החזק ביותר??\p"
	.string "הלוואי שהיה לי עוד זמן לחקור אותם.$"

SinjohRuins_Lab_EventScript_Linguist::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SinjohRuins_Lab_EventScript_LinguistAfterEvent
	goto_if_ge VAR_SINJOH_STORYLINE, 9, SinjohRuins_Lab_EventScript_LinguistDuringEvent
	msgbox SinjohRuins_Lab_Text_Linguist MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_LinguistDuringEvent::
	msgbox SinjohRuins_Lab_Text_LinguistDuring, MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_LinguistAfterEvent::
	msgbox SinjohRuins_Lab_Text_LinguistAfter, MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Linguist:
    .string "אוף…\n"
    .string "יש כל כך הרבה כתובות לתרגם…\p"
    .string "אין לנו שום דבר כזה באזור הואן.$"
SinjohRuins_Lab_Text_LinguistDuring:
    .string "תאר לעצמך כמה הופתעתי\n"
    .string "כשתרגמתי את הכתובת!\p"
    .string "בדקתי אותה שלוש וארבע פעמים\n"
    .string "לפני שסיפרתי לסטיבן!\p"
    .string "כלומר, באמת, אל הפוקימונים?\p"
    .string "זה לא ייאמן.$"
SinjohRuins_Lab_Text_LinguistAfter:
    .string "המשלחת הזאת הייתה תענוג, {PLAYER}.\p"
    .string "תודה שדאגת לכל עבודת השטח.$"

SinjohRuins_Lab_EventScript_Archaeologist::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SinjohRuins_Lab_EventScript_ArchaeologistAfterEvent
	goto_if_ge VAR_SINJOH_STORYLINE, 9, SinjohRuins_Lab_EventScript_ArchaeologistDuringEvent
	msgbox SinjohRuins_Lab_Text_Archaeologist MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_ArchaeologistDuringEvent::
	msgbox SinjohRuins_Lab_Text_ArchaeologistDuring, MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_ArchaeologistAfterEvent::
	msgbox SinjohRuins_Lab_Text_ArchaeologistAfter, MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Archaeologist:
	.string "קיומה של ציוויליזציה באזור הזה משנה\n"
	.string "את כל ההבנה שלנו את ההיסטוריה.\p"
	.string "רבים מהחפצים שמצאנו\n"
	.string "בני יותר מאלף שנה.\p"
	.string "תיארוך הפחמן תואם לממצאים\n"
	.string "שנמצאו באזור סינו.\p"
	.string "אבל החליל שמצאת…\n"
	.string "הוא נראה עתיק הרבה יותר.$"
SinjohRuins_Lab_Text_ArchaeologistDuring:
	.string "הלוחות האלה… הקשר לאזור סינו…\n"
	.string "החליל ההוא… הכול מתחיל להתחבר.$"
SinjohRuins_Lab_Text_ArchaeologistAfter:
	.string "אי אפשר להפריז בערך ההיסטורי של\n"
	.string "מה שעזרת לנו לחשוף כאן, {PLAYER}.\p"
	.string "באמת, תודה.$"

SinjohRuins_Lab_EventScript_Growlithe_Hisui::
    lock
	faceplayer
	playmoncry SPECIES_GROWLITHE, 0
	msgbox SinjohRuins_Lab_Text_Growlithe_Cry, MSGBOX_DEFAULT
	waitmoncry
    closemessage
	release
	end

SinjohRuins_Lab_Text_Growlithe_Cry:
    .string "גראו אאו!!$"

SinjohRuins_Lab_EventScript_GrowlithePokeball::
    msgbox SinjohRuins_Lab_Text_GrowlitheBall MSGBOX_SIGN
	end

SinjohRuins_Lab_Text_GrowlitheBall:
    .string "נראה שזה הפוקיבול של גראולית'…\n"
    .string "עדיף לא לגעת בו.$"

SinjohRuins_Lab_EventScript_Biologist::
	goto_if_ge VAR_SINJOH_STORYLINE, 13, SinjohRuins_Lab_EventScript_BiologistAfterEvent
	goto_if_ge VAR_SINJOH_STORYLINE, 9, SinjohRuins_Lab_EventScript_BiologistDuringEvent
	msgbox SinjohRuins_Lab_Text_Biologist MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_BiologistDuringEvent::
	msgbox SinjohRuins_Lab_Text_BiologistDuring, MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_BiologistAfterEvent::
	msgbox SinjohRuins_Lab_Text_BiologistAfter, MSGBOX_NPC
	end

SinjohRuins_Lab_Text_Biologist:
    .string "איזה פרט נפלא!\p"
    .string "זן הגראולית' הזה שונה מכל\n"
    .string "מה שנמצא בשאר העולם.\p"
    .string "ניתוח דנ”א מגלה שיש לו אב קדמון\n"
    .string "משותף עם גראולית' מאזורים אחרים.\p"
    .string "ועם זאת, המזג והסוג שלו שונים מאוד.\p"
    .string "תיאורים של גראולית' ברשומות\n"
    .string "עתיקות של סינו נראים תואמים.\p"
    .string "אולי הזן הזה שכן פעם בשטח גדול בהרבה,\n"
    .string "שנמשך צפונה דרך סינו העתיקה.$"
SinjohRuins_Lab_Text_BiologistDuring:
	.string "אם היצור שבראש המדרגות האלה\n"
	.string "הוא באמת האל של כל הפוקימונים,\p"
	.string "האם זה אומר שהוא\n"
	.string "האב הקדמון המשותף הראשון?$"
SinjohRuins_Lab_Text_BiologistAfter:
	.string "במשלחת הזאת אספתי המון נתונים על\n"
	.string "צורות אזוריות ועל אבולוציה מתפצלת.\p"
	.string "תודה לך, {PLAYER}.$"

SinjohRuins_Lab_EventScript_Hiker::
	goto_if_ge VAR_SINJOH_STORYLINE, 9, SinjohRuins_Lab_EventScript_HikerDuringAfter
	msgbox SinjohRuins_Lab_Text_Hiker MSGBOX_NPC
	end
SinjohRuins_Lab_EventScript_HikerDuringAfter::
	msgbox SinjohRuins_Lab_Text_HikerDuringAfter, MSGBOX_NPC
	end
SinjohRuins_Lab_Text_Hiker:
   	.string "עשר שנים אני מטייל בשממות האלה.\p"
   	.string "לא, בעצם עשרים שנה.\p"
   	.string "עד שיום אחד מצאתי את עמודי האבן\n"
   	.string "הגדולים ואת המקדש המאיים ההוא.\p"
   	.string "אלה חורבות סינג'ו.\n"
   	.string "ככה לפחות שמעתי.\p"
   	.string "אז עוד לא ידעתי על העיירה.\p"
   	.string "כל מה שעשיתי היה לספר לכמה חברים.\n"
   	.string "אבל שמועות עוברות מהר.\p"
   	.string "לא חשבתי שזה ימשוך\n"
   	.string "כל כך הרבה תשומת לב לאזור.\p"
   	.string "זה גורם לי להרגיש קצת מוזר.\n"
   	.string "אתה יודע?$"
SinjohRuins_Lab_Text_HikerDuringAfter:
   	.string "אל תספר לאף אחד, {PLAYER},\p"
   	.string "אבל ראיתי את המקדש שבפסגת ההר\n"
   	.string "כבר כשגיליתי את המקום הזה.\p"
   	.string "שמרתי את זה לעצמי.\p"
   	.string "כבר פטפטתי מספיק על החורבות האלה.\p"
   	.string "נראה שלפחות הכול הסתדר בסוף.$"

@ENVIRONMENT
SinjohRuins_Lab_EventScript_Notes1::
	msgbox SinjohRuins_Lab_Text_Note1 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes2::
	msgbox SinjohRuins_Lab_Text_Note2 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes3::
	msgbox SinjohRuins_Lab_Text_Note3 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes4::
	msgbox SinjohRuins_Lab_Text_Note4 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes5::
	msgbox SinjohRuins_Lab_Text_Note5 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes6::
	msgbox SinjohRuins_Lab_Text_Note6 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes7::
	msgbox SinjohRuins_Lab_Text_Note7 MSGBOX_SIGN
	end
SinjohRuins_Lab_EventScript_Notes8::
	msgbox SinjohRuins_Lab_Text_Note8 MSGBOX_SIGN
	end

SinjohRuins_Lab_Text_Note1:
    .string "יומן מחקר 1, מיום 3 במאי 1975\p"
    .string "הגענו לאתר החורבות.\p"
    .string "אפשר להרגיש את הקור העז של\n"
    .string "הר הכסף כל הדרך עד לכאן למטה…\p"
    .string "בקרוב צוות החפירה הראשי\n"
    .string "יעבור דרך ההר…\p"
    .string "אני מת לראות מה מחכה לנו מתחת לרגליים!$"

SinjohRuins_Lab_Text_Note2:
    .string "יומן מחקר 2, מיום 10 במאי 1975\p"
    .string "שבוע של חפירות לא הניב שום תוצאה.\p"
    .string "הקרח כאן עבה באופן בלתי אפשרי,\n"
    .string "והסלע פשוט שובר לנו את הציוד לגמרי.\p"
    .string "אפילו מאצ'אמפ לא הצליח\n"
    .string "להשאיר בו שריטה.\p"
    .string "מה זה המקום הזה?\p"
    .string "אנחנו חייבים לגלות.$"

SinjohRuins_Lab_Text_Note3:
    .string "יומן מחקר 3, מיום 14 במאי 1975\p"
    .string "לא מתקדמים בחיים אם\n"
    .string "עומדים בצד ולא עושים כלום.\p"
    .string "אני רק פועל.\p"
    .string "אבל היה לי רעיון איך\n"
    .string "נוכל לפרוץ דרך הקרח.\p"
    .string "או ליתר דיוק, להמיס אותו.\p"
    .string "אנחנו צריכים פוקימונים מסוג אש,\n"
    .string "והרבה מהם.\p"
    .string "אבל איך נביא אותם לכאן\n"
    .string "כל הדרך מסינו?$"

SinjohRuins_Lab_Text_Note4:
    .string "יומן מחקר 4, מיום 21 במאי 1975\p"
    .string "היינו עסוקים.\p"
    .string "הרעיון שלי עבד והעביר אותנו דרך הקרח.\n"
    .string "רק שלא הבאנו את פוקימוני האש מהבית.\p"
    .string "הבוס התעקש שנשיג אותם כאן.\p"
    .string "מצאנו מעיין חם ליד כפר סמוך…\p"
    .string "ולקחנו את מה שהיינו צריכים…\p"
    .string "אני לא גאה בזה.\n"
    .string "אבל לפעמים ההתקדמות דורשת קורבנות.\p"
    .string "אז הקרח נעלם.\p"
    .string "יש 6 חדרים, ומקדש חתום במרכז.\p"
    .string "לפי הארכיטקטורה, אולי המבנה הראשי\n"
    .string "שייך לעמי סלסטיקה הקדומים…\p"
    .string "אבותינו.\n"
    .string "לפני שעברו צפונה.\p"
    .string "הבוס רוצה שהמקדש\n"
    .string "ייפתח כמה שיותר מהר…$"

SinjohRuins_Lab_Text_Note5:
    .string "יומן מחקר 5, מיום 2 ביוני 1975\p"
    .string "הצלחנו לפתוח אותו…\p"
    .string "חשבתי שאהיה מאושר…\p"
    .string "אבל איבדנו אנשים טובים\n"
    .string "בפיצוץ האנרגיה שפרץ מהמקדש.\p"
    .string "שלא לדבר על הפוקימונים שעזרו\n"
    .string "לנו לפתוח אותו. יהי זכרם ברוך…\p"
    .string "……………\p"
    .string "בכל מקרה.\p"
    .string "המקדש פתוח,\n"
    .string "אבל נשארנו רק עם עוד שאלות.\p"
    .string "אין בפנים שום פוקימון אגדי.\n"
    .string "שום אוצר.\p"
    .string "האספקה שלנו מתחילה להיגמר,\n"
    .string "ואין לנו שום תוצאות למרות כל המאמצים…$"

SinjohRuins_Lab_Text_Note6:
  	.string "יומן מחקר 6, מיום 10 ביוני 1975\p"
  	.string "המשלחת הסתיימה.\n"
  	.string "שאר האנשים אורזים.\p"
  	.string "אבל אני לא יכול.\p"
  	.string "אני לא יכול לנטוש את המשימה.\n"
  	.string "לא אחרי מה שאיבדנו.\p"
  	.string "אני נשאר כאן.$"

SinjohRuins_Lab_Text_Note7:
  	.string "יומן מחקר 7, מיום 10 בספטמבר 1975\p"
  	.string "עברו חודשים מאז שהגענו לכאן.\n"
  	.string "מאז שאני הגעתי לכאן.\p"
  	.string "שאר האנשים הלכו.\p"
  	.string "עכשיו נשארנו רק אני והפוקימונים\n"
  	.string "שתפסנו כדי שיעזרו לנו בעבודה.\p"
  	.string "אני מאמן אותם כדי שיהיו חזקים יותר.\p"
  	.string "את הטיפלוז'ן שלי, יותר מכולם.\p"
  	.string "אנחנו חייבים לגלות מה יש מתחת למקדש.$"

SinjohRuins_Lab_Text_Note8:
  	.string "יומן מחקר 8, מיום 15 בספטמבר 1975\p"
  	.string "כישלון.\p"
  	.string "……………\p"
  	.string "הפוקימונים שלי…\p"
  	.string "יחד, כל 6 הפוקימונים שלי הצליחו\n"
  	.string "לפרוץ דרך קיר מזויף במקדש.\p"
  	.string "אבל הוא חיכה לנו…\p"
  	.string "משהו כמו טיטאן ענק…\p"
  	.string "האנרגיה ששחרר הייתה בדיוק\n"
  	.string "כמו מה שקרה בפעם הקודמת.\p"
  	.string "כולם הושמדו…\p"
  	.string "והכי גרוע, החיה ההיא\n"
  	.string "אטמה את הקיר מחדש.\p"
  	.string "אני לא יכול לחזור הביתה.\n"
  	.string "הם כבר לא יזהו אותי…\p"
  	.string "המקום הזה שינה אותי…\p"
  	.string "אני הולך לדבר עם תושבי הכפר.\p"
  	.string "הם לא יודעים מה עשיתי.\p"
  	.string "מאחר שהאנשים האחרים עזבו מזמן,\n"
  	.string "הם יחשבו שאני סתם מטייל שהלך לאיבוד.\p"
  	.string "לא נשאר לי שום מקום מלבד כאן.$"

SinjohRuins_EventScript_DisplayCase::
    lock
	msgbox SinjohRuins_DisplayCase_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_DisplayCase_Text:
    .string "זו תיבת תצוגה מסודרת בקפידה,\n"
    .string "מלאה בדגימות ובממצאים!$"

SinjohRuins_EventScript_WallSign::
    lock
	msgbox SinjohRuins_WallSign_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_WallSign_Text:
   .string "Xray and printing lab.$"


SinjohRuins_EventScript_Artifact::
   lock
   msgbox SinjohRuins_Artifact_Text MSGBOX_DEFAULT
   release
   end

SinjohRuins_Artifact_Text:
   .string "זה חפץ עתיק שנמצא בתוך החורבות!$"


@==========================Unified other map SCRIPTS================================================================================

SinjohRuins_Lab_EventScript_NoOp::
	release
	end

SinjohRuins_Lab_Text_PlayFlute:
	.string "חליל התכלת מגיב.\n"
	.string "לנגן בחליל?$"

SinjohRuins_Lab_Text_DropedItem:
	.string "{STR_VAR_1} האצילי הפיל פריט…$"

SinjohRuins_Lab_Text_StevenName:
	.string "סטיבן$"

SinjohRuins_Lab_EventScript_3Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall3Plates
	waitmessage
	delay 30
	return
SinjohRuins_Lab_EventScript_6Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall6Plates
	waitmessage
	delay 30
	return
SinjohRuins_Lab_EventScript_9Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall9Plates
	waitmessage
	delay 30
	return
SinjohRuins_Lab_EventScript_12Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall12Plates
	waitmessage
	delay 30
	return
SinjohRuins_Lab_EventScript_15Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall15Plates
	waitmessage
	delay 30
	return
SinjohRuins_Lab_EventScript_16Plates::
	setspeaker SinjohRuins_Lab_Text_StevenName
	pokenavcall SinjohRuins_Lab_Text_StevenCall16Plates
	waitmessage
	delay 30
	setvar VAR_SINJOH_STORYLINE, 7
	return

SinjohRuins_Lab_Text_StevenCall3Plates:
	.string "סטיבן: {PLAYER}.\p"
	.string "הרגשנו עכשיו רעד אדמה בחורבות.\p"
	.string "כולם בסדר, אין מה לדאוג.\p"
	.string "זה די מסקרן. אחד החדרים\n"
	.string "התת-קרקעיים מתחת לחורבות נפתח.\p"
	.string "הסימנים שבפנים מזכירים לי\n"
	.string "משהו מהואן.\p"
	.string "כדאי לבוא להציץ כשיתאפשר.$"

SinjohRuins_Lab_Text_StevenCall6Plates:
	.string "סטיבן: {PLAYER}.\p"
	.string "איך מתקדם החיפוש?\p"
	.string "היה כאן עוד רעד.\n"
	.string "הפעם נפתח חדר שני.\p"
	.string "ביקשתי מהגיאולוג שלנו להכין את\n"
	.string "המכשירים למקרה שזה יקרה שוב.\p"
	.string "ככל שאנחנו חופרים עמוק יותר…\n"
	.string "כך אנחנו מוצאים יותר שאלות.$"

SinjohRuins_Lab_Text_StevenCall9Plates:
	.string "סטיבן: {PLAYER}.\p"
	.string "עוד רעד כאן בחורבות.\p"
	.string "הנתונים מציירים תמונה מסקרנת.\p"
	.string "זו בכלל לא הייתה רעידת אדמה.\p"
	.string "סוג של אנרגיה הצטבר מתחת\n"
	.string "לאדמה וסדק את הסלע מבפנים.\p"
	.string "מה יכול לגרום לזה…\n"
	.string "אני באמת לא יודע.$"

SinjohRuins_Lab_Text_StevenCall12Plates:
	.string "סטיבן: {PLAYER}.\p"
	.string "עוד רעד.\n"
	.string "עוד חדר שנפתח.\p"
	.string "אנחנו עדיין לא מבינים את\n"
	.string "הדפוס שמאחורי התזמון.\p"
	.string "תגיד, {PLAYER}… אתה לא עושה\n"
	.string "משהו שגורם לכל זה, נכון?\p"
	.string "לא, זה לא ייתכן.$"

SinjohRuins_Lab_Text_StevenCall15Plates:
	.string "סטיבן: {PLAYER}.\p"
	.string "מצאת עכשיו עוד לוח?\p"
	.string "…………\p"
	.string "ברור.\p"
	.string "הפוקימונים האגדיים שבחורבות האלה…\n"
	.string "הם מגיבים אליך, נכון?\p"
	.string "כאילו הם רוצים שימצאו אותם.\p"
	.string "התחזיות שלי בדרך כלל מתגשמות.\n"
	.string "הייתי צריך לדעת שאין טעם לפקפק בך.$"

SinjohRuins_Lab_Text_StevenCall16Plates:
	.string "סטיבן: {PLAYER}.\p"
	.string "אנחנו קרובים מאוד עכשיו.\n"
	.string "אני מרגיש את זה.\p"
	.string "…………\p"
	.string "כדאי שתבוא לראות את זה בעצמך.$"

