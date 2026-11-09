CianwoodGym_hns_MapScripts::
	.byte 0


CianwoodGym_EventScript_Statue::
	lock
	goto_if_set FLAG_DEFEATED_CIANWOOD_GYM, CianwoodGym_EventScript_Statue2
	msgbox CianwoodGym_Text_GymStatue, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_EventScript_Statue2::
	msgbox CianwoodGym_Text_GymStatueCertified, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_Text_GymStatue:
	.string "מכון הפוקימון של העיר סיאנווד$"

CianwoodGym_Text_GymStatueCertified:
	.string "מכון הפוקימון של העיר סיאנווד\p"
	.string "המאמנים המוסמכים של צ'אק:\n"
	.string "{PLAYER}$"

CianwoodGym_EventScript_Chuck::
	lock
	faceplayer
	goto_if_unset FLAG_HIDE_DOJO_CHUCK, CianwoodGym_EventScript_ChuckAtDojo
	goto_if_set FLAG_VISITED_VERMILION_CITY, CianwoodGym_EventScript_ChuckGotoDojo
	goto_if_set FLAG_DEFEATED_CIANWOOD_GYM, CianwoodGym_EventScript_Chuck_Defeated
	msgbox CianwoodGym_Text_ChuckIntro1, MSGBOX_DEFAULT
	applymovement LOCALID_CIANWOOD_CHUCK, CianwoodGym_Movement_ChuckLeft
	waitmovement 0
	message CianwoodGym_Text_ChuckIntro2
	applymovement LOCALID_CIANWOOD_CHUCK_ROCK_LEFT, Movement_SmashRock
	playse SE_M_ROCK_THROW
	waitmovement 0

	delay 20

	applymovement LOCALID_CIANWOOD_CHUCK, CianwoodGym_Movement_ChuckRight
	waitmovement 0
	applymovement LOCALID_CIANWOOD_CHUCK_ROCK_RIGHT, Movement_SmashRock
	playse SE_M_ROCK_THROW
	waitmovement 0
	waitmessage
	turnobject LOCALID_CIANWOOD_CHUCK, DIR_SOUTH
	msgbox CianwoodGym_Text_ChuckIntro3, MSGBOX_DEFAULT
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, CianwoodGym_EventScript_OlivineCheckMahog
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM, CianwoodGym_EventScript_MahogCheckOlivine
	goto CianwoodGym_EventScript_Chuck_Battle1

CianwoodGym_EventScript_ChuckVictory::
	message CianwoodGym_Text_GetStormBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox CianwoodGym_Text_ChuckBadgeSpeech, MSGBOX_DEFAULT
	setflag FLAG_BADGE05_GET
	setflag FLAG_DEFEATED_CIANWOOD_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 5
	call Common_EventScript_SetGymTrainers_hns
	giveitem ITEM_TM_FOCUS_PUNCH
	msgbox CianwoodGym_Text_ChuckTMSpeech, MSGBOX_DEFAULT
	setvar VAR_GETFLY, 1
	setrespawn HEAL_LOCATION_CIANWOOD_CITY_HNS
    call_if_eq VAR_NUM_BADGES, 7, MahoganyTown_Gym_EventScript_SetupElmRocketCall
	closemessage
	release
	end

CianwoodGym_EventScript_ChuckGotoDojo::
	msgbox CianwoodGym_Text_ChuckGotoDojo, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_DOJO_CHUCK
	release
	end

CianwoodGym_Text_ChuckGotoDojo:
	.string "וואהאהאהא {PLAYER}!\n"
	.string "אני באמצע האימון שלי!\p"
	.string "אם אתה רוצה עוד קרב, בוא\n"
	.string "לדוג'ו הלחימה בסאפרון!$"

CianwoodGym_EventScript_ChuckAtDojo::
	msgbox CianwoodGym_Text_ChuckAtDojo, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_Text_ChuckAtDojo:
	.string "נתראה בדוג'ו!\n"
	.string "וואהאהאהאהאהא$"

CianwoodGym_EventScript_OlivineCheckMahog::
	goto_if_set FLAG_DEFEATED_MAHOGANY_TOWN_GYM, CianwoodGym_EventScript_Chuck_Battle3
	goto CianwoodGym_EventScript_Chuck_Battle2

CianwoodGym_EventScript_MahogCheckOlivine::
	goto_if_set FLAG_DEFEATED_OLIVINE_CITY_GYM, CianwoodGym_EventScript_Chuck_Battle3
	goto CianwoodGym_EventScript_Chuck_Battle2
	
CianwoodGym_EventScript_Chuck_Battle1::
	trainerbattle_no_intro TRAINER_CHUCK_1_HNS, CianwoodGym_Text_ChuckIntro2
	goto CianwoodGym_EventScript_ChuckVictory

CianwoodGym_EventScript_Chuck_Battle2::
	trainerbattle_no_intro TRAINER_CHUCK_1_2_HNS, CianwoodGym_Text_ChuckIntro2
	goto CianwoodGym_EventScript_ChuckVictory

CianwoodGym_EventScript_Chuck_Battle3::
	trainerbattle_no_intro TRAINER_CHUCK_1_3_HNS, CianwoodGym_Text_ChuckIntro2
	goto CianwoodGym_EventScript_ChuckVictory

CianwoodGym_EventScript_Chuck_Defeated::
	msgbox CianwoodGym_Text_ChuckAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_Movement_ChuckLeft:
	jump_in_place_left
	step_end

CianwoodGym_Movement_ChuckRight:
	jump_in_place_right
	step_end

CianwoodGym_Text_ChuckIntro1:
	.string "וואהאהאה!\p"
	.string "אז הגעת עד לכאן!\p"
	.string "אני אגיד לך משהו, אני קשוח!\p"
	.string "הפוקימונים שלי ירסקו אבנים\n"
	.string "וישברו עצמות!\p"
	.string "תראה את זה!$"

CianwoodGym_Text_ChuckIntro2:
	.string "צ'אק: אורגגג!\n"
	.string "…\p"
	.string "אואואררררג!$"

CianwoodGym_Text_ChuckIntro3:
	.string "הנה! עכשיו אתה מפחד, נכון?\p"
	.string "מה? זה לא קשור\n"
	.string "לפוקימונים?\p"
	.string "נכון מאוד!\p"
	.string "קדימה. הבה נצא לקרב!$"

CianwoodGym_Text_ChuckLoss:
	.string "Wha? Huh? I lost?\p"
	.string "How about that!\n"
	.string "You're worthy of STORMBADGE!$"

CianwoodGym_Text_GetStormBadge:
	.string "{PLAYER} קיבל את תג סערה.$"

CianwoodGym_Text_ChuckBadgeSpeech:
	.string "עם תג סערה, כל פוקימון עד\n"
	.string "רמה 70 יציית לך, גם אם התקבל בהחלפה.\p"
	.string "הוא גם מאפשר לפוקימונים שלך\n"
	.string "להשתמש בתעופה מחוץ לקרב.\p"
	.string "הנה, קח גם את זה!$"

CianwoodGym_Text_ChuckTMSpeech:
	.string "זו מכת ריכוז.\p"
	.string "היא איטית, אבל גורמת נזק\n"
	.string "עצום. רק שלא יפגעו בך קודם!$"

CianwoodGym_Text_ChuckAfter:
	.string "וואהאהאה! נהניתי להילחם בך!\p"
	.string "אבל הפסד הוא הפסד!\p"
	.string "מעכשיו אני אתאמן\n"
	.string "24 שעות ביממה!$"

CianwoodGym_Text_ChuckRematch:
	.string "WAHAHAH! JOHTO CHAMPION!\p"
	.string "You've come back for more!\p"
	.string "I see your skills have improved!\p"
	.string "Ready to see who's stronger?$"

CianwoodGym_Text_ChuckRematchDefeat:
	.string "Wha? Huh? I lost?\n"
	.string "Again?$"

CianwoodGym_EventScript_Yoshi::
	trainerbattle_single TRAINER_YOSHI_HNS, CianwoodGym_Text_BlackbeltYoshiSeen, CianwoodGym_Text_BlackbeltYoshiBeaten
	msgbox CianwoodGym_Text_BlackbeltYoshiAfter, MSGBOX_AUTOCLOSE
	end

CianwoodGym_Text_BlackbeltYoshiSeen:
	.string "אני והפוקימונים שלי קשורים\n"
	.string "בקשר של חברות.\p"
	.string "הקשר שלנו לעולם לא יישבר!$"

CianwoodGym_Text_BlackbeltYoshiBeaten:
	.string "זה לא יכול להיות אמיתי!$"

CianwoodGym_Text_BlackbeltYoshiAfter:
	.string "נראה שגם לך יש קשר חזק\n"
	.string "עם הפוקימונים שלך!$"

CianwoodGym_EventScript_Lao::
	trainerbattle_single TRAINER_LAO_HNS, CianwoodGym_Text_BlackbeltLaoSeen, CianwoodGym_Text_BlackbeltLaoBeaten
	msgbox CianwoodGym_Text_BlackbeltLaoAfter, MSGBOX_AUTOCLOSE
	end

CianwoodGym_Text_BlackbeltLaoSeen:
	.string "אנחנו, אמני הלחימה,\n"
	.string "לא מפחדים מכלום!$"

CianwoodGym_Text_BlackbeltLaoBeaten:
	.string "זה מזעזע!$"

CianwoodGym_Text_BlackbeltLaoAfter:
	.string "פוקימונים מסוג קרב מפחדים\n"
	.string "מפוקימונים מסוג על-חושי…$"


CianwoodGym_EventScript_Nob::
	trainerbattle_single TRAINER_NOB_HNS, CianwoodGym_Text_BlackbeltNobSeen, CianwoodGym_Text_BlackbeltNobBeaten
	msgbox CianwoodGym_Text_BlackbeltNobAfter, MSGBOX_AUTOCLOSE
	end

CianwoodGym_Text_BlackbeltNobSeen:
	.string "מילים לא שוות כלום.\n"
	.string "שהאגרופים ידברו!$"

CianwoodGym_Text_BlackbeltNobBeaten:
	.string "…$"

CianwoodGym_Text_BlackbeltNobAfter:
	.string "הפסדתי! אין לי מילים!$"

CianwoodGym_EventScript_Lung::
	trainerbattle_single TRAINER_LUNG_HNS, CianwoodGym_Text_BlackbeltLungSeen, CianwoodGym_Text_BlackbeltLungBeaten
	msgbox CianwoodGym_Text_BlackbeltLungAfter, MSGBOX_AUTOCLOSE
	end

CianwoodGym_Text_BlackbeltLungSeen:
	.string "האגרופים הזועמים שלי ינפצו\n"
	.string "את הפוקימונים שלך!$"

CianwoodGym_Text_BlackbeltLungBeaten:
	.string "התנפצתי לרסיסים!$"

CianwoodGym_Text_BlackbeltLungAfter:
	.string "הפוקימונים שלי הפסידו…\n"
	.string "ה… הגאווה שלי התנפצה…$"

