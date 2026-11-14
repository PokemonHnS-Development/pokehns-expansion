GoldenrodCity_RadioTower_5F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GoldenrodCity_RadioTower_5F_OnLoad
	.byte 0

GoldenrodCity_RadioTower_5F_OnLoad::
	call_if_eq VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_RadioTower_5F_MapScript_HidePetrel
	end

GoldenrodCity_RadioTower_5F_MapScript_HidePetrel::
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	return


@=======[OFFICE]==============================================================================================================================

GoldenrodCity_RadioTower_5F_EventScript_Petrel::
	lock
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 10, GoldenrodCity_RadioTower_5F_EventScript_Director
	goto_if_eq VAR_FACING, DIR_SOUTH, GoldenrodCity_RadioTower_5F_EventScript_PetrelNorth
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirector1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DIRECTOR_OFFICE, GoldenrodCity_RadioTower_5F_Movement_Spin
	waitmovement 0
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	removeobject LOCALID_DIRECTOR_OFFICE
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	addobject LOCALID_PETREL_OFFICE
	applymovement LOCALID_PETREL_OFFICE, GoldenrodCity_RadioTower_5F_Movement_Spin2
	waitmovement 0
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirector2, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PETREL_2_HNS, GoldenrodCity_RadioTower_5F_Text_FakeDirectorWin
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	setvar VAR_GOLDENROD_CITY_STATE, 7
	clearflag FLAG_HIDE_GOLDENROD_UNDERGROUND_KIMONO
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_PetrelNorth::
	end

GoldenrodCity_RadioTower_5F_EventScript_Petrel2::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_Director::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_Movement_Spin:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_4
	face_up
	delay_4
	face_left
	delay_4
	face_down
	delay_4
	face_right
	delay_2
	face_up
	delay_2
	face_left
	delay_2
	face_down
	step_end


GoldenrodCity_RadioTower_5F_Movement_Spin2:
	face_right
	delay_2
	face_up
	delay_2
	face_left
	delay_2
	face_down
	step_end


GoldenrodCity_RadioTower_5F_Text_FakeDirector1:
	.string "א-אתה! באת להציל אותי?$"

GoldenrodCity_RadioTower_5F_Text_FakeDirector2:
	.string "זה מה שציפית לו?\p"
	.string "טעות! אני מתחזה!\p"
	.string "העמדתי פנים שאני האמיתי, כדי\n"
	.string "להתכונן להשתלטות שלנו.\p"
	.string "רוצה לדעת איפה החבאנו את\n"
	.string "מנהל התחנה האמיתי?\p"
	.string "בטח, אני אגיד לך. אבל רק אם\n"
	.string "תנצח אותי!$"

GoldenrodCity_RadioTower_5F_Text_FakeDirectorWin:
	.string "טוב, טוב. אגיד לך איפה הוא.$"

GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter:
	.string "הבוס החביא את מנהל התחנה\n"
	.string "במחסן התת-קרקעי.\p"
	.string "הוא נמצא בקצה הרחוק של המעבר\n"
	.string "התת-קרקעי.\p"
	.string "אני בחור נחמד, אז הנה מפתח המרתף,\n"
	.string "כדי שתגיע למחסן התת-קרקעי.\p"
	.string "אבל אני בספק שתגיע כל כך רחוק.$"

GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter2:
	.string "הבוס החביא את מנהל התחנה\n"
	.string "במחסן התת-קרקעי.\p"
	.string "הוא נמצא בקצה הרחוק של המעבר\n"
	.string "התת-קרקעי.\p"
	.string "אפשר להשתמש במפתח המרתף\n"
	.string "כדי להגיע למחסן התת-קרקעי.\p"
	.string "אבל אני בספק שתגיע כל כך רחוק.$"

@=======[STUDIO]==============================================================================================================================

GoldenrodCity_RadioTower_5F_EventScript_Ben::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_Ben, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodRaidoTower4_EventScript_ARIANA::
	trainerbattle_single TRAINER_ARIANA_2_HNS GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Seen, GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Beaten
	msgbox GoldenrodCity_RadioTower_5F_Text_ExecutiveF1After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_RadioTower_5F_EventScript_Archer::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_RocketBossSeen, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ARCHER_HNS, GoldenrodCity_RadioTower_5F_Text_RocketBossBeaten
	msgbox GoldenrodCity_RadioTower_5F_Text_RocketBossAfter, MSGBOX_DEFAULT
	delay 55
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_GOLDENROD_ROCKETS
	playse SE_EXIT
	setvar VAR_GOLDENROD_CITY_STATE, 10
	removeobject LOCALID_GOLDENROD_ARCHER
	removeobject LOCALID_GOLDENROD_ARIANA
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	removeobject LOCALID_PETREL_OFFICE
	addobject LOCALID_DIRECTOR_STUDIO
	playbgm MUS_HG_GOLDENROD, TRUE
	delay 120
	fadescreen FADE_FROM_BLACK
	goto_if_eq VAR_FACING, DIR_SOUTH, GoldenrodCity_RadioTower_5F_EventScript_WingTop
	goto_if_eq VAR_FACING, DIR_WEST, GoldenrodCity_RadioTower_5F_EventScript_WingMid
	goto_if_eq VAR_FACING, DIR_NORTH, GoldenrodCity_RadioTower_5F_EventScript_WingBot
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_WingTop::
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerTop
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorThanks, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_LUGIA_OR_HOOH, 1,  GoldenrodCity_RadioTower_5F_EventScript_GiveTidalWing
	call_if_eq VAR_LUGIA_OR_HOOH, 2, GoldenrodCity_RadioTower_5F_EventScript_GiveClearWing
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_LeaveTop
	waitmovement 0
	goto GoldenrodCity_RadioTower_5F_Fakeout
	end

GoldenrodCity_RadioTower_5F_EventScript_WingMid::
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerMid
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorThanks, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_LUGIA_OR_HOOH, 1,  GoldenrodCity_RadioTower_5F_EventScript_GiveTidalWing
	call_if_eq VAR_LUGIA_OR_HOOH, 2, GoldenrodCity_RadioTower_5F_EventScript_GiveClearWing
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_LeaveMid
	waitmovement 0
	goto GoldenrodCity_RadioTower_5F_Fakeout
	end

GoldenrodCity_RadioTower_5F_EventScript_WingBot::
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerBot
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorThanks, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_LUGIA_OR_HOOH, 1,  GoldenrodCity_RadioTower_5F_EventScript_GiveTidalWing
	call_if_eq VAR_LUGIA_OR_HOOH, 2, GoldenrodCity_RadioTower_5F_EventScript_GiveClearWing
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_LeaveBot
	waitmovement 0
	goto GoldenrodCity_RadioTower_5F_Fakeout
	end

GoldenrodCity_RadioTower_5F_EventScript_GiveTidalWing::
	giveitem ITEM_SILVER_WING
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorTidalWingExplanation, MSGBOX_DEFAULT
	closemessage
	release
	return

GoldenrodCity_RadioTower_5F_EventScript_GiveClearWing::
	giveitem ITEM_RAINBOW_WING
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorClearWingExplanation, MSGBOX_DEFAULT
	closemessage
	release
	return

GoldenrodCity_RadioTower_5F_Fakeout::
	playse SE_PIN
	applymovement LOCALID_DIRECTOR_STUDIO, Common_Movement_ExclamationMark
	delay 60
	turnobject LOCALID_DIRECTOR_STUDIO, DIR_WEST
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorLegendary, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_Leave1
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_DIRECTOR_STUDIO, Common_Movement_ExclamationMark
	delay 60
	turnobject LOCALID_DIRECTOR_STUDIO, DIR_SOUTH
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorFakeout, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_Leave2
	waitmovement 0
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR_2
	removeobject LOCALID_DIRECTOR_STUDIO
	setvar VAR_MAHOGANY_TOWN_STATE, 17
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_Trigger_NPCS::
	clearflag FLAG_HIDE_GOLDENROD_NPCS
	setvar VAR_GOLDENROD_CITY_STATE, 11
	end

GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerTop:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_RadioTower_5F_Movement_LeaveTop:
	walk_right
	walk_right
	walk_right
	step_end

GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerMid:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	step_end


GoldenrodCity_RadioTower_5F_Movement_LeaveMid:
	walk_right
	walk_right
	step_end

GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerBot:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_RadioTower_5F_Movement_LeaveBot:
	walk_right
	walk_right
	walk_right
	step_end

GoldenrodCity_RadioTower_5F_Movement_Leave1:
	walk_up
	walk_up
	step_end

GoldenrodCity_RadioTower_5F_Movement_Leave2:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Seen:
	.string "זוכר אותי מהמחבוא\n"
	.string "בעיירה מהגוני?\p"
	.string "הבוס נזף בי, אבל עכשיו\n"
	.string "אני חזקה יותר.\p"
	.string "אז הפסדתי, אבל הפעם לא אפסיד.$"

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Beaten:
	.string "זה לא ייתכן!\p"
	.string "נלחמתי קשה, ובכל זאת הפסדתי…\p"
	.string "אני כל כך מצטערת, ג'ובאני…$"

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1After:
	.string "{PLAYER}, נכון?\p"
	.string "פרחח כמוך לא יעריך את\n"
	.string "גדולתו של צוות רוקט.\p"
	.string "חבל מאוד. אני באמת מעריצה\n"
	.string "את הכוח שלך.$"

GoldenrodCity_RadioTower_5F_Text_RocketBossSeen:
	.string "הו? הצלחת להגיע עד לכאן?\p"
	.string "אתה בטח מאמן של ממש.\p"
	.string "אנחנו מתכוונים להשתלט על תחנת\n"
	.string "הרדיו הזאת ולהכריז על שובנו.\p"
	.string "זה אמור להחזיר את הבוס שלנו,\n"
	.string "ג'ובאני, מהאימונים שלו בבדידות.\p"
	.string "אנחנו נחזיר לעצמנו את\n"
	.string "התהילה של פעם…\p"
	.string "לא אתן לך להפריע\n"
	.string "לתוכניות המדוקדקות שלנו!$"

GoldenrodCity_RadioTower_5F_Text_RocketBossBeaten:
	.string "לא! סלח לי, ג'ובאני!$"

GoldenrodCity_RadioTower_5F_Text_RocketBossAfter:
	.string "איך זה ייתכן?\p"
	.string "החלומות שלנו ירדו לטמיון.\p"
	.string "בסופו של דבר, לא עמדתי במשימה.\p"
	.string "כמו שג'ובאני עשה לפניי, גם אני\n"
	.string "אפרק את צוות רוקט כאן, היום.\p"
	.string "היה שלום.$"

GoldenrodCity_RadioTower_5F_Text_DirectorThanks:
	.string "מנהל התחנה: {PLAYER}, תודה לך!\p"
	.string "המעשים האמיצים שלך הצילו\n"
	.string "פוקימונים בכל רחבי הארץ.\p"
	.string "אני יודע שזה לא הרבה, אבל\n"
	.string "זה בשבילך.$"

GoldenrodCity_RadioTower_5F_Text_DirectorClearWingExplanation:
	.string "פעם עמד מגדל ממש כאן,\n"
	.string "בעיר גולדנרוד.\p"
	.string "אבל הוא היה ישן ורעוע.\p"
	.string "אז החלפנו אותו במגדל\n"
	.string "הרדיו שלנו.\p"
	.string "את הנוצה הזאת מצאנו\n"
	.string "בחפירות של הבנייה.\p"
	.string "שמעתי שבעבר חיו בגולדנרוד\n"
	.string "כל מיני פוקימונים.\p"
	.string "אולי…\p"
	.string "לנוצה הזאת יש קשר כלשהו\n"
	.string "למגדל הבדיל שבעיר אקרוטיק…\p"
	.string "טוב, כדאי שאלך ללשכה שלי.$"

GoldenrodCity_RadioTower_5F_Text_DirectorTidalWingExplanation:
	.string "פעם עמד מגדל ממש כאן,\n"
	.string "בעיר גולדנרוד.\p"
	.string "אבל הוא היה ישן ורעוע.\p"
	.string "אז החלפנו אותו במגדל\n"
	.string "הרדיו שלנו.\p"
	.string "את הנוצה הזאת מצאנו\n"
	.string "בחפירות של הבנייה.\p"
	.string "שמעתי שבעבר חיו בגולדנרוד\n"
	.string "כל מיני פוקימונים.\p"
	.string "אולי…\p"
	.string "לנוצה הזאת יש קשר כלשהו\n"
	.string "לאיי המערבולת שליד העיר סיאנווד…\p"
	.string "טוב, כדאי שאלך ללשכה שלי.$"

GoldenrodCity_RadioTower_5F_Text_DirectorLegendary:
	.string "אה!\p"
	.string "זה מזכיר לי…\p"
	.string "הנוצה שנתתי לך… אני חושב שהיא\n"
	.string "קשורה לפוקימון האגדי.\p"
	.string "אבל! הפוקימון האגדי לא יופיע\n"
	.string "רק בזכות הנוצה הזאת…\p"
	.string "כנראה שצריך עוד משהו…\n"
	.string "או משהו כזה.\p"
	.string "מעניין מה זה היה…\p"
	.string "אני לא זוכר.$"

GoldenrodCity_RadioTower_5F_Text_DirectorFakeout:
	.string "ציפית למשהו?\n"
	.string "לזה קוראים הטעייה.\p"
	.string "הפעם אני באמת חייב לחזור\n"
	.string "ללשכה שלי. להתראות!$"

GoldenrodCity_RadioTower_5F_Text_DirectorIntro:
	.string "מנהל התחנה: שלום, {PLAYER}!\p"
	.string "אתה יודע, אני אוהב פוקימונים.\p"
	.string "בניתי את מגדל הרדיו הזה כדי\n"
	.string "לבטא את האהבה שלי לפוקימונים.\p"
	.string "היה נחמד אם אנשים היו נהנים\n"
	.string "מהתוכניות שלנו.$"

GoldenrodCity_RadioTower_5F_Text_Ben:
	.string "בן: יוצא לך להאזין למוזיקה שלנו?$"

GoldenrodCity_RadioTower_5F_Text_DirectorOfficeSign:
	.string "5F DIRECTOR'S   OFFICE$"

GoldenrodCity_RadioTower_5F_Text_Studio1Sign:
	.string "5F STUDIO 1$"
