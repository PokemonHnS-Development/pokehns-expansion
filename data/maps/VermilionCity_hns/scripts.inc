VermilionCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VermilionCity_MapScript_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

VermilionCity_MapScript_OnTransition::
	setflag FLAG_VISITED_VERMILION_CITY
	goto_if_eq VAR_SUICUNE_ENCOUNTERS, 3, VermilionCity_EventScript_SetSuicuneScene
	setflag FLAG_HIDE_VERMILION_EUSINE_SUICUNE
	callnative SetTimeBasedEncounters
	end

VermilionCity_EventScript_SetSuicuneScene::
	clearflag FLAG_HIDE_VERMILION_EUSINE_SUICUNE
	callnative SetTimeBasedEncounters
	end

VermilionCity_EventScript_OldSeaMap::
	finditem ITEM_OLD_SEA_MAP
	end

VermilionCity_TriggerSuicuneNorth_Left::
	lock
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_WalkRight1
	waitmovement 0
	goto VermilionCity_TriggerSuicuneNorth_Merge
VermilionCity_TriggerSuicuneNorth_Mid::
	lock
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_WalkRight1
	waitmovement 0
	goto VermilionCity_TriggerSuicuneNorth_Merge
VermilionCity_TriggerSuicuneNorth_Right::
	lock
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	goto VermilionCity_TriggerSuicuneNorth_Merge
VermilionCity_TriggerSuicuneNorth_Merge::
	applymovement OBJ_EVENT_ID_PLAYER, VermilionCity_Movement_NorthSuicune_PlayerWalkDown
	waitmovement 0
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement2 LOCALID_VERMILION_SUICUNE, VermilionCity_Movement_Suicune1
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_PLAYER, VermilionCity_Movement_NorthSuicune_PlayerWalkDown
	delay 60
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	applymovement2 LOCALID_VERMILION_EUSINE, VermilionCity_Movement_EusineWalkToRail
	waitmovement LOCALID_VERMILION_EUSINE
	waitmovement OBJ_EVENT_ID_PLAYER
	goto VermilionCity_EventScript_SuicuneEpisode

VermilionCity_Movement_NorthSuicune_PlayerWalkDown:
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

VermilionCity_TriggerSuicuneTop::
	lock
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement2 LOCALID_VERMILION_SUICUNE, VermilionCity_Movement_Suicune1
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_PLAYER, VermilionCity_Movement_PlayerWalkToRailTop
	delay 60
	applymovement2 LOCALID_VERMILION_EUSINE, VermilionCity_Movement_EusineWalkToRail
	waitmovement LOCALID_VERMILION_EUSINE
	waitmovement OBJ_EVENT_ID_PLAYER
	goto VermilionCity_EventScript_SuicuneEpisode
VermilionCity_TriggerSuicuneMid::
	lock
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement2 LOCALID_VERMILION_SUICUNE, VermilionCity_Movement_Suicune1
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_PLAYER, VermilionCity_Movement_PlayerWalkToRailMid
	delay 60
	applymovement2 LOCALID_VERMILION_EUSINE, VermilionCity_Movement_EusineWalkToRail
	waitmovement LOCALID_VERMILION_EUSINE
	waitmovement OBJ_EVENT_ID_PLAYER
	goto VermilionCity_EventScript_SuicuneEpisode
VermilionCity_TriggerSuicuneBot::
	lock
	playse SE_PIN
	applymovement2 OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement2 LOCALID_VERMILION_SUICUNE, VermilionCity_Movement_Suicune1
	waitmovement 0
	applymovement2 OBJ_EVENT_ID_PLAYER, VermilionCity_Movement_PlayerWalkToRailBot
	waitmovement 0
	applymovement2 LOCALID_VERMILION_EUSINE, VermilionCity_Movement_EusineWalkToRail
	waitmovement LOCALID_VERMILION_EUSINE
	waitmovement OBJ_EVENT_ID_PLAYER
	goto VermilionCity_EventScript_SuicuneEpisode

VermilionCity_EventScript_SuicuneEpisode::
	playmoncry SPECIES_SUICUNE, CRY_MODE_NORMAL
	applymovement2 LOCALID_VERMILION_SUICUNE, VermilionCity_Movement_SuicuneLeave
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	playse SE_LEDGE
	delay 30
	waitmovement 0
	msgbox VermilionCity_Text_Eusine, MSGBOX_DEFAULT
	turnobject LOCALID_VERMILION_EUSINE, DIR_SOUTH
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox VermilionCity_Text_Eusine2, MSGBOX_DEFAULT
	closemessage
	applymovement2 LOCALID_VERMILION_EUSINE, VermilionCity_Movement_EusineLeave
	waitmovement 0
	removeobject LOCALID_VERMILION_EUSINE
	removeobject LOCALID_VERMILION_SUICUNE
	setflag FLAG_HIDE_VERMILION_EUSINE_SUICUNE

	setvar VAR_SUICUNE_ENCOUNTERS, 4
	clearflag FLAG_HIDE_ROUTE14_SUICUNE
	release
	end

VermilionCity_EventScript_Teacher::
	msgbox VermilionCity_Text_Teacher, MSGBOX_NPC
	end

VermilionCity_EventScript_Oldman::
	msgbox VermilionCity_Text_MachopOwner, MSGBOX_NPC
	end

VermilionCity_EventScript_Machop::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MACHOP, CRY_MODE_NORMAL
	msgbox VermilionCity_Text_Machop1, MSGBOX_DEFAULT
	waitmoncry
	msgbox VermilionCity_Text_Machop2, MSGBOX_DEFAULT
	release
	end

VermilionCity_EventScript_Nerd::
	msgbox VermilionCity_Text_SuperNerd, MSGBOX_NPC
	end

VermilionCity_EventScript_Snorlax::
	lock
	special CheckRadioStation
	goto_if_eq VAR_RESULT, TRUE, VermilionCity_EventScript_SnorlaxWakeUp
	@goto_if_set FLAG_KANTO_RADIO_GOT, VermilionCity_EventScript_SnorlaxWakeUp
	msgbox VermilionCity_Text_SnorlaxSleeping, MSGBOX_DEFAULT
	closemessage
	release
	end

VermilionCity_EventScript_SnorlaxWakeUp::
    playbgm MUS_HG_RADIO_POKE_FLUTE, FALSE
    msgbox VermilionCity_Text_RadioNearSnorlax, MSGBOX_DEFAULT
    playmoncry SPECIES_SNORLAX, CRY_MODE_ENCOUNTER
    delay 40
    waitmoncry
    setwildbattle SPECIES_SNORLAX, 50
    dowildbattle
    specialvar VAR_RESULT, GetBattleOutcome
    goto_if_eq VAR_RESULT, B_OUTCOME_RAN, VermilionCity_EventScript_SnorlaxRan
    fadescreenswapbuffers FADE_TO_BLACK
    removeobject LOCALID_VERMILION_SNORLAX
    removeobject 8
    removeobject 9
    removeobject 10
    removeobject 11
    setflag FLAG_HIDE_VERMILION_SNORLAX
    fadescreenswapbuffers FADE_FROM_BLACK
    setflag FLAG_INDIGOJUNCTION_HIDE_KANTO_GUARD
    fadedefaultbgm
    release
    end

VermilionCity_EventScript_SnorlaxRan::
    fadedefaultbgm
    release
    end

VermilionCity_EventScript_BadgeGuy::
	lock
	faceplayer
	goto_if_set FLAG_GOT_VERMILION_HP_UP, VermilionCity_EventScript_BadgeGuyAfter
	goto_if_ge VAR_NUM_BADGES, 16, VermilionCity_EventScript_BadgeGuyAll
	goto_if_ge VAR_NUM_BADGES, 12, VermilionCity_EventScript_BadgeGuyMost
	goto_if_ge VAR_NUM_BADGES, 9, VermilionCity_EventScript_BadgeGuySome
	msgbox VermilionCity_Text_BadgeGuy_Trainer, MSGBOX_DEFAULT
	closemessage
	release
	end
VermilionCity_EventScript_BadgeGuySome::
	msgbox VermilionCity_Text_BadgeGuy_SomeBadges, MSGBOX_DEFAULT
	closemessage
	release
	end
VermilionCity_EventScript_BadgeGuyMost::
	msgbox VermilionCity_Text_BadgeGuy_MostBadges, MSGBOX_DEFAULT
	closemessage
	release
	end
VermilionCity_EventScript_BadgeGuyAll::
	msgbox VermilionCity_Text_BadgeGuy_AllBadges, MSGBOX_DEFAULT
	giveitem ITEM_HP_UP
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_VERMILION_HP_UP
	closemessage
	release
	end
VermilionCity_EventScript_BadgeGuyAfter::
	msgbox VermilionCity_Text_BadgeGuy_BattleEdge, MSGBOX_DEFAULT
	closemessage
	release
	end


VermilionCity_Movement_Suicune1:
	jump_in_place_left
	jump_in_place_left
	jump_in_place_left
	step_end

VermilionCity_Movement_PlayerWalkToRailTop: @goal tile = 51, 28
	walk_right
	walk_right
	walk_up
	walk_up
	walk_right
	step_end
VermilionCity_Movement_PlayerWalkToRailMid:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_right
	step_end
VermilionCity_Movement_PlayerWalkToRailBot:
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	step_end

VermilionCity_Movement_EusineWalkToRail:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_right
	step_end

VermilionCity_Movement_SuicuneLeave:
	jump_in_place_left
	jump_2_right
	jump_2_right
	jump_2_right
	step_end

VermilionCity_Movement_EusineLeave:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

VermilionCity_Text_Eusine:
	.string "יוסין: זה היה כל כך קרוב! חשבתי\n"
	.string "שאוכל ללכוד אותו במארב כאן.\p"
	.string "אבל לרוץ על המים זה מעבר\n"
	.string "ליכולת שלי.\p"
	.string "ובכל זאת, אני מתחיל לזהות\n"
	.string "דפוס.\p"
	.string "סואיקון מעדיף מים!\p"
	.string "זה אומר ש…$"

VermilionCity_Text_Eusine2:
	.string "סליחה, {PLAYER}, אני חייב ללכת!$"

VermilionCity_Text_Teacher:
	.string "נמל ורמיליון הוא שער הים\n"
	.string "של קאנטו.\p"
	.string "אוניות פאר מכל העולם\n"
	.string "עוגנות כאן.$"

VermilionCity_Text_MachopOwner:
	.string "הפוקימון שלי מכין את הקרקע\n"
	.string "לבנייה.\p"
	.string "אבל אין לי כסף להתחיל את\n"
	.string "הפרויקט…$"

VermilionCity_Text_Machop1:
	.string "מאצ'ופ: גואוה גוגוגוה!$"

VermilionCity_Text_Machop2:
	.string "מאצ'ופ נוהם תוך כדי שהוא\n"
	.string "רוקע ומשטח את הקרקע.$"

VermilionCity_Text_SuperNerd:
	.string "יש שמונה מכונים בקאנטו.\p"
	.string "הבניין הגדול הזה הוא\n"
	.string "מכון הפוקימון של ורמיליון.$"

VermilionCity_Text_SnorlaxSleeping:
	.string "סנורלקס נוחר בשלווה…$"

VermilionCity_Text_RadioNearSnorlax:
	.string "הפוקיגיר הונח ליד\n"
	.string "סנורלקס הישן…\p"
	.string "…\p"
	.string "סנורלקס התעורר!$"

VermilionCity_Text_BadgeGuy_Trainer:
	.string "מאמנים מיומנים מתאספים בקאנטו.\p"
	.string "מנהיגי המכונים חזקים במיוחד.\p"
	.string "לא יהיה קל לנצח אותם.$"

VermilionCity_Text_BadgeGuy_SomeBadges:
	.string "התחלת לאסוף את תגי המכונים\n"
	.string "של קאנטו?\p"
	.string "נכון שהמאמנים כאן\n"
	.string "קשוחים?$"

VermilionCity_Text_BadgeGuy_MostBadges:
	.string "נראה לי שבקרוב תסיים לכבוש\n"
	.string "את המכונים של קאנטו.\p"
	.string "תגיד לי אם תשיג את כל שמונת\n"
	.string "התגים.$"

VermilionCity_Text_BadgeGuy_AllBadges:
	.string "מזל טוב!\p"
	.string "השגת את כל תגי המכונים של קאנטו.\p"
	.string "יש לי פרס בשביל המאמצים שלך.$"

VermilionCity_Text_BadgeGuy_BattleEdge:
	.string "מגוון של סוגי פוקימונים אמור\n"
	.string "לתת לך יתרון בקרב.\p"
	.string "אני בטוח שתגי המכונים של קאנטו\n"
	.string "יעזרו לך.$"

VermilionCity_EventScript_CitySign::
	msgbox VermilionCity_Text_Sign, MSGBOX_SIGN
	end
VermilionCity_EventScript_GymSign::
	msgbox VermilionCity_Text_GymSign, MSGBOX_SIGN
	end
VermilionCity_EventScript_FanClubSign::
	msgbox VermilionCity_Text_FanClubSign, MSGBOX_SIGN
	end
VermilionCity_EventScript_DiglettsCaveSign::
	msgbox VermilionCity_Text_DiglettsCaveSign, MSGBOX_SIGN
	end

VermilionCity_Text_Sign:
	.string "העיר ורמיליון\p"
	.string "נמל השקיעות המופלאות$"

VermilionCity_Text_GymSign:
	.string "העיר ורמיליון\n"
	.string "מכון הפוקימון\p"
	.string "מנהיג: סמל סרג'\p"
	.string "האמריקאי החשמלי$"

VermilionCity_Text_FanClubSign:
	.string "מועדון מעריצי הפוקימונים\p"
	.string "כל מעריצי הפוקימונים מוזמנים!$"

VermilionCity_Text_DiglettsCaveSign:
	.string "מערת דיגלט$"

VermilionCity_Text_PortSign:
	.string "VERMILION PORT\n"
	.string "ENTRANCE$"

VermilionCity_EventScript_TriggerStevenLeft::
	lock
	playse SE_PIN
	applymovement2 LOCALID_PLAYER, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_PLAYER
	applymovement2 LOCALID_VERMILIONCITY_STEVEN, Common_Movement_WalkLeft1
	waitmovement 0
	call VermilionCity_EventScript_LatiChoice
	applymovement2 LOCALID_VERMILIONCITY_STEVEN, Common_Movement_WalkRight1
	waitmovement 0
	applymovement2 LOCALID_VERMILIONCITY_STEVEN, VermilionCity_Movement_StevenWalkToPlayer
	waitmovement 0
	applymovement2 LOCALID_VERMILIONCITY_STEVEN, Common_Movement_WalkDown1
	waitmovement 0
	setvar VAR_VERMILION_CITY_STEVEN, 1
	removeobject LOCALID_VERMILIONCITY_STEVEN
	release
	end

VermilionCity_EventScript_TriggerStevenMiddle::
	lock
	playse SE_PIN
	applymovement2 LOCALID_PLAYER, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_PLAYER
	call VermilionCity_EventScript_LatiChoice
	applymovement2 LOCALID_VERMILIONCITY_STEVEN, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement2 LOCALID_VERMILIONCITY_STEVEN, VermilionCity_Movement_StevenWalkToPlayer
	waitmovement 0
	applymovement2 LOCALID_VERMILIONCITY_STEVEN, Common_Movement_WalkDown1
	waitmovement 0
	setvar VAR_VERMILION_CITY_STEVEN, 1
	removeobject LOCALID_VERMILIONCITY_STEVEN
	release
	end
 
VermilionCity_EventScript_TriggerStevenRight::
	lock
	playse SE_PIN
	applymovement2 LOCALID_PLAYER, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_PLAYER
	applymovement2 LOCALID_VERMILIONCITY_STEVEN, Common_Movement_WalkRight1
	waitmovement 0
	call VermilionCity_EventScript_LatiChoice
	applymovement2 LOCALID_VERMILIONCITY_STEVEN, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement2 LOCALID_VERMILIONCITY_STEVEN, VermilionCity_Movement_StevenWalkToPlayer
	waitmovement 0
	applymovement2 LOCALID_VERMILIONCITY_STEVEN, Common_Movement_WalkDown1
	waitmovement 0
	setvar VAR_VERMILION_CITY_STEVEN, 1
	removeobject LOCALID_VERMILIONCITY_STEVEN
	release
	end


VermilionCity_EventScript_LatiChoice::
	applymovement2 LOCALID_VERMILIONCITY_STEVEN, VermilionCity_Movement_StevenWalkToPlayer
	waitmovement LOCALID_VERMILIONCITY_STEVEN
	msgbox VermilionCity_Text_StevenIntro, MSGBOX_DEFAULT
	multichoice 20, 8, MULTI_TV_LATI, TRUE
	@goto_if_eq VAR_RESULT, MULTI_B_PRESSED, VermilionCity_EventScript_LatiCancel
	copyvar VAR_0x8004, VAR_RESULT
	copyvar VAR_ROAMER_POKEMON_HNS, VAR_RESULT
	special InitKantoRoamers
	setflag FLAG_LATIOS_OR_LATIAS_ROAMING
	msgbox VermilionCity_Text_StevenOutro, MSGBOX_DEFAULT
	closemessage
	return

VermilionCity_Movement_StevenWalkToPlayer:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_down
	step_end

VermilionCity_Text_StevenIntro:
	.string "היי! קוראים לי סטיבן.\n"
	.string "אני האלוף מאזור הואן.\p"
	.string "נפגשנו… פעם?\p"
	.string "זה לא ייתכן. כל המאמנים שנלחמתי\n"
	.string "בהם נראים די אותו דבר, בכל מקרה.\p"
	.string "במיוחד אלה שנתנו לי\n"
	.string "קרבות קשים.\p"
	.string "אני בקאנטו לרגל עסקים. לאחרונה\n"
	.string "פוקימונים רבים מהואן נדדו לאזור הזה.\p"
	.string "הזרם הזה עלול לשבש את\n"
	.string "המערכת האקולוגית הטבעית כאן.\p"
	.string "אז בעזרת החברה שלי, אני מקים\n"
	.string "בית גידול מיוחד.\p"
	.string "הוא ימשוך אליו את המינים\n"
	.string "הפולשניים ביותר ויחזיק אותם שם.\p"
	.string "כדאי לפקוח עיניים ולתפוס\n"
	.string "כל פוקימון מהואן שרואים.\p"
	.string "כמה מאמנים אפילו דיווחו על אחד\n"
	.string "שדואה בשמיים כמו מטוס סילון…\p"
	.string "מה היה הצבע שלו, בעצם?$"

VermilionCity_Text_StevenOutro:
	.string "אה, נכון.\p"
	.string "אני חייב ללכת.\n"
	.string "שדרכינו יצטלבו שוב.$"

VermilionCity_EventScript_TriggerSamson::
	lock
	clearflag FLAG_HIDE_VERMILION_CITY_SAMSON
	addobject LOCALID_VERMILION_CITY_SAMSON
	playse SE_BANG
	applymovement LOCALID_VERMILION_CITY_SAMSON, VermilionCity_Movement_SamsonEnter
	applymovement LOCALID_PLAYER, VermilionCity_Movement_PlayerSlideback
	waitmovement LOCALID_VERMILION_CITY_SAMSON
	waitmovement LOCALID_PLAYER
	msgbox VermilionCity_Text_Samson, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_VERMILION_CITY_SAMSON, VermilionCity_Movement_SamsonLeave
	waitmovement LOCALID_VERMILION_CITY_SAMSON
	removeobject LOCALID_VERMILION_CITY_SAMSON
	setflag FLAG_HIDE_VERMILION_CITY_SAMSON
	setvar VAR_VERMILION_CITY_SAMSON, 2
	release
	end

VermilionCity_Movement_PlayerSlideback:
	lock_facing_direction
	walk_fast_down
	walk_fast_down
	unlock_facing_direction
	step_end

VermilionCity_Movement_SamsonEnter:
	walk_fast_down
	walk_fast_down
	step_end

VermilionCity_Movement_SamsonLeave:
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

VermilionCity_Text_Samson:
	.string "וואו!\p"
	.string "סליחה, ילד, אני ממהר!\p"
	.string "המעבורת בדרך 13 תצא בקרוב\n"
	.string "לאיים, ואני חייב להיות עליה!\p"
	.string "פוו… פוו…\p"
	.string "רצתי כל הדרך לכאן\n"
	.string "מהר הירח.\p"
	.string "רואה את הקישוט הקטן הזה?\p"
	.string "השגתי את המזכרת המוזרה הזאת\n"
	.string "בחנות המזכרות.\p"
	.string "זה הכרטיס שלי לאיים.\p"
	.string "טוב, להתראות!$"
