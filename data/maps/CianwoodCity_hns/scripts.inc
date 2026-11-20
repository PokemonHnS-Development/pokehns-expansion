CianwoodCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CianwoodCity_EventScript_CityEnter
	map_script MAP_SCRIPT_ON_FRAME_TABLE, CianwoodCity_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, CianwoodCity_EventScript_InitializeSuicune
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

CianwoodCity_RemoveEusine::
	setflag FLAG_HIDE_CIANWOOD_EUSINE
	end

CianwoodCity_OnFrame::
	map_script_2 VAR_GETFLY, 1, CianwoodCity_EventScript_Flytrigger
	.2byte 0

CianwoodCity_EventScript_CityEnter::
	setflag FLAG_VISITED_CIANWOOD_CITY
	callnative SetTimeBasedEncounters
	goto_if_ge VAR_OLIVINE_CITY_STATE, 5, OlivineCity_MapScript_ClearWeather
	end

CianwoodCity_EventScript_InitializeSuicune::
	goto_if_ge VAR_SUICUNE_ENCOUNTERS, 2, CianwoodCity_EventScript_InitializeNothing
	clearflag FLAG_HIDE_CIANWOOD_SUICUNE
	setflag FLAG_HIDE_CIANWOOD_EUSINE
	setvar VAR_TEMP_0, 1
	end

CianwoodCity_EventScript_InitializeNothing::
	setvar VAR_TEMP_0, 1
	end

CianwoodCity_EventScript_Flytrigger::
	lock
	playse SE_PIN
	applymovement LOCALID_CIANWOOD_CHUCKSWIFE, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_CIANWOOD_CHUCKSWIFE
	applymovement LOCALID_CIANWOOD_CHUCKSWIFE, CianwoodCity_Movement_ChucksWife
	waitmovement 0
	msgbox CianwoodCity_Text_ChucksWifeGiveHM, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLY
	msgbox CianwoodCity_Text_ChucksWifeFlySpeech, MSGBOX_DEFAULT
	closemessage
	setvar VAR_GETFLY, 2
	goto_if_eq VAR_TRIGGER_ELM_ROCKET_CALL, 1, Mahoganytown_EventScript_RocketTrigger
	release
	end

CianwoodCity_Movement_ChucksWife:
	walk_left
	walk_left
	walk_up
	walk_left
	face_up
	step_end

CianwoodCity_EventScript_Test::
	lock
	random 2
	call_if_eq VAR_RESULT, 1, EventScript_RockSmashHeartscale
	release
	end

CianwoodCity_EventScript_ChucksWife::
	lock
	faceplayer
	checkitem ITEM_HM_FLY
	goto_if_eq VAR_RESULT, TRUE, CianwoodCity_EventScript_ChucksWifeAlreadyHasFly
	msgbox CianwoodCity_Text_ChucksWifeEasierToFly, MSGBOX_DEFAULT
	goto_if_set FLAG_BADGE05_GET, CianwoodCity_EventScript_ChucksWifeGiveFly
	msgbox CianwoodCity_Text_ChucksWifeBeatChuck, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_EventScript_ChucksWifeGiveFly::
	msgbox CianwoodCity_Text_ChucksWifeGiveHM, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLY
	msgbox CianwoodCity_Text_ChucksWifeFlySpeech, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_EventScript_ChucksWifeAlreadyHasFly::
	msgbox CianwoodCity_Text_ChucksWifeChubby, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_ChucksWifeEasierToFly:
	.string "חצית את הים כדי להגיע לכאן?\p"
	.string "זה בטח היה קשה.\p"
	.string "היה הרבה יותר קל אם\n"
	.string "הפוקימונים שלך היו יודעים תעופה…$"

CianwoodCity_Text_ChucksWifeBeatChuck:
	.string "אבל אי אפשר להשתמש בתעופה\n"
	.string "בלי תג המכון של העיר הזאת.\p"
	.string "אם תנצח את מנהיג המכון כאן,\n"
	.string "בוא אליי.\p"
	.string "תהיה לי מתנה נחמדה בשבילך.$"

CianwoodCity_Text_ChucksWifeGiveHM:
	.string "זה תג המכון של סיאנווד!\p"
	.string "אז כדאי שתיקח את המ”נ הזה.$"

CianwoodCity_Text_ChucksWifeFlySpeech:
	.string "כדאי ללמד את הפוקימון שלך תעופה.\p"
	.string "כך אפשר לעוף מיד\n"
	.string "לכל מקום שכבר ביקרת בו.$"

CianwoodCity_Text_ChucksWifeChubby:
	.string "בעלי הפסיד לך, אז הוא צריך\n"
	.string "להתאמן יותר קשה.\p"
	.string "וזה טוב, כי הוא התחיל\n"
	.string "להשמין קצת.$"

CianwoodCity_EventScript_Youngster::
	lock
	faceplayer
	msgbox CianwoodCity_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_Youngster:
	.string "עם תעופה אפשר לחזור\n"
	.string "לאוליבין ברגע.$"

CianwoodCity_EventScript_PokefanM::
	lock
	faceplayer
	msgbox CianwoodCity_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_PokefanM:
	.string "את הסלעים בצפון העיר\n"
	.string "אפשר לנפץ.\p"
	.string "אולי הם מסתירים משהו.\p"
	.string "הפוקימונים שלך יכולים לשבור\n"
	.string "אותם בעזרת ניפוץ סלע.$"

CianwoodCity_EventScript_Lass::
	lock
	faceplayer
	msgbox CianwoodCity_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_Lass:
	.string "צ'אק, מנהיג המכון, עורך קרבות\n"
	.string "אימון עם פוקימוני הקרב שלו.$"

CianwoodCity_EventScript_SuicuneTrigger::
	lock
	hidefollower 1
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement LOCALID_CIANWOOD_SUICUNE, CianwoodCity_Movement_Suicune1
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0
	waitmoncry
	playse SE_PIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement LOCALID_CIANWOOD_SUICUNE, CianwoodCity_Movement_Suicune2
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_SOUTH
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	waitmoncry
	applymovement LOCALID_CIANWOOD_SUICUNE, CianwoodCity_Movement_Suicune3
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	waitmovement 0
	delay 30
	playbgm MUS_HG_EUSINE, FALSE
	clearflag FLAG_HIDE_CIANWOOD_EUSINE
	addobject LOCALID_CIANWOOD_EUSINE
	applymovement LOCALID_CIANWOOD_EUSINE, CianwoodCity_Movement_Eusine1
	waitmovement 0
	delay 55
	applymovement LOCALID_CIANWOOD_EUSINE, CianwoodCity_Movement_Eusine2
	waitmovement 0 
	msgbox CianwoodCity_Text_EusineSuicune, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_EUSINE_HNS, CianwoodCity_Text_EusineBeaten
	playbgm MUS_HG_EUSINE, FALSE
	msgbox CianwoodCity_Text_EusineAfter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CIANWOOD_EUSINE, CianwoodCity_Movement_Eusine3
	waitmovement 0
	setflag FLAG_HIDE_CIANWOOD_EUSINE
	setflag FLAG_HIDE_CIANWOOD_SUICUNE
	removeobject LOCALID_CIANWOOD_SUICUNE
	removeobject LOCALID_CIANWOOD_EUSINE
	setvar VAR_SUICUNE_ENCOUNTERS, 2
	setvar VAR_CIANWOOD_CITY_STATE, 2
	fadedefaultbgm
	call_if_set FLAG_HIDE_ROUTE42_SUICUNE, CianwoodCity_EventScript_DoneJohtoSuicune
	release
	end

CianwoodCity_EventScript_DoneJohtoSuicune::
	setvar VAR_SUICUNE_ENCOUNTERS, 3
	return

CianwoodCity_Movement_Suicune1:
	jump_in_place_right_left
	jump_in_place_right_left
	face_down
	step_end

CianwoodCity_Movement_Suicune2:
	jump_down
	jump_2_down
	jump_right
	face_up
	step_end

CianwoodCity_Movement_Suicune3:
	jump_2_down
	jump_2_right
	jump_2_right
	jump_2_right
	jump_2_right
	jump_2_right
	step_end

CianwoodCity_Movement_Eusine1:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	face_right
	step_end

CianwoodCity_Movement_Eusine2:
	face_up
	walk_up
	walk_up
	step_end

CianwoodCity_Movement_Eusine3:
	face_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

CianwoodCity_Text_EusineSuicune:
	.string "יוסין: היי, {PLAYER}.\p"
	.string "זה לא היה סואיקון עכשיו?\p"
	.string "רק הצצתי לרגע, אבל נדמה לי\n"
	.string "שראיתי את סואיקון רץ על הגלים.\p"
	.string "סואיקון יפהפה ומרשים.\p"
	.string "והוא דוהר בין ערים ודרכים\n"
	.string "במהירות פשוט מדהימה.\p"
	.string "זה נפלא…\p"
	.string "אני רוצה לראות את סואיקון מקרוב…\p"
	.string "החלטתי.\p"
	.string "אילחם בך כמאמן כדי\n"
	.string "לזכות בכבוד של סואיקון!\p"
	.string "קדימה, {PLAYER}. בוא נילחם עכשיו!$"

CianwoodCity_Text_EusineBeaten:
	.string "קשה לי להודות בזה, אבל ניצחת.$"

CianwoodCity_Text_EusineAfter:
	.string "אתה מדהים, {PLAYER}!\p"
	.string "אין פלא שפוקימונים נמשכים אליך.\p"
	.string "עכשיו אני מבין.\p"
	.string "אני אמשיך לחפש את סואיקון.\p"
	.string "אני בטוח שעוד ניפגש.\p"
	.string "להתראות!$"

CianwoodCity_EventScript_CitySign::
	lock
	msgbox CianwoodCity_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

CianwoodCity_Text_Sign:
	.string "העיר סיאנווד\p"
	.string "נמל מוקף במים סוערים$"

CianwoodCity_EventScript_GymSign::
	lock
	msgbox CianwoodCity_Text_GymSign, MSGBOX_SIGN
	closemessage
	release
	end

CianwoodCity_Text_GymSign:
	.string "מכון הפוקימון של העיר סיאנווד\p"
	.string "מנהיג: צ'אק\p"
	.string "האגרופים השואגים שלו\n"
	.string "מדברים בשבילו$"

CianwoodCity_EventScript_Pharmacy::
	lock
	msgbox CianwoodCity_Text_PharmacySign, MSGBOX_SIGN
	closemessage
	release
	end

CianwoodCity_Text_PharmacySign:
	.string "500 שנות מסורת\p"
	.string "בית המרקחת של העיר סיאנווד\p"
	.string "נשמח לענות על שאלותיכם\n"
	.string "בענייני תרופות$"

CianwoodCity_EventScript_CaveSign::
	lock
	msgbox CianwoodCity_Text_Safari, MSGBOX_SIGN
	closemessage
	release
	end

CianwoodCity_EventScript_Engineer::
	lock
	faceplayer
	msgbox CianwoodCity_Text_Engineer, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_Safari:
	.string "מערת הצוק\n"
	.string "הדרך לאזור הספארי.$"

CianwoodCity_Text_Engineer:
	.string "השביל הזה בבנייה. אנחנו עובדים\n"
	.string "על פתיחת אזור הספארי החדש!$"
