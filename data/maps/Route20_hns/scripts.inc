Route20_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route20_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route20_EventScript_ShellBell::
	finditem ITEM_SHELL_BELL
	end

Route20_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route20_EventScript_Nicole::
	trainerbattle_single TRAINER_NICOLE_HNS, Route20_Text_SwimmerfNicoleSeen, Route20_Text_SwimmerfNicoleBeaten, Route20_EventScript_RegisterNicole
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route20_EventScript_RematchNicole
	msgbox Route20_Text_SwimmerfNicoleAfterBattle, MSGBOX_AUTOCLOSE
	end

Route20_EventScript_RegisterNicole::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route20_Text_NicoleRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_NICOLE_HNS
	release
	end

Route20_EventScript_RematchNicole::
	trainerbattle_rematch TRAINER_NICOLE_HNS, Route20_Text_NicoleRematchIntro, Route20_Text_NicoleRematchDefeat
	msgbox Route20_Text_NicolePostRematch, MSGBOX_AUTOCLOSE
	goto_if_defeated TRAINER_NICOLE_2_HNS, Route20_EventScript_RematchNicoleTryGiveItem
	end

Route20_EventScript_RematchNicoleTryGiveItem::
	checkitem ITEM_HEART_SCALE
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NoOp
	giveitem ITEM_HEART_SCALE
	closemessage
	end

Route20_EventScript_Lori::
	trainerbattle_single TRAINER_LORI_HNS, Route20_Text_SwimmerfLoriSeen, Route20_Text_SwimmerfLoriBeaten
	msgbox Route20_Text_SwimmerfLoriAfterBattle, MSGBOX_AUTOCLOSE
	end	

Route20_EventScript_Cameron::
	trainerbattle_single TRAINER_CAMERON_HNS, Route20_Text_SwimmermCameronSeen, Route20_Text_SwimmermCameronBeaten
	msgbox Route20_Text_SwimmermCameronAfterBattle, MSGBOX_AUTOCLOSE
	end	

Route20_EventScript_SeafoamSign::
	msgbox Route20_Text_SeafoamSign, MSGBOX_SIGN
	end

Route20_EventScript_GymSign::
	msgbox Route20_Text_CinnabarIsland_GymUnusedSign, MSGBOX_SIGN
	end

Route20_EventScript_Seel::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SEEL, CRY_MODE_NORMAL
	msgbox Route20_Text_Seel, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route20_EventScript_Dewgong::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DEWGONG, CRY_MODE_NORMAL
	msgbox Route20_Text_Dewgong, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route20_EventScript_Dennis::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MAGIKARP, CRY_MODE_NORMAL
	msgbox Route20_Text_Dennis, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route20_EventScript_Headlocker::
	lock
	faceplayer
	msgbox Route20_Text_Headlocker, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_ROUTE20_HEADLOCKER, DIR_SOUTH
	release
	end

Route20_Text_Dennis:
	.string "דניס: שאאאאאאאא!$"

Route20_Text_Headlocker:
	.string "יש פוקימון נדיר בדרך הזאת.\p"
	.string "ולפעמים הוא מחזיק\n"
	.string "פריט התפתחות נדיר.\p"
	.string "זה נדיר בריבוע!\p"
	.string "אני חייב להשלים את הפוקדקס שלי,\n"
	.string "אז אני דג פה כבר שעות!$"

Route20_Text_Seel:
	.string "סיל: סיל סיל!$"

Route20_Text_Dewgong:
	.string "דיוגונג: גוווונג!$"

Route20_Text_SeafoamSign:
	.string "איי הקצף$"

Route20_Text_NicoleRegister:
	.string "הפוקימון שלך שוחה מהר!\n"
	.string "אני חייבת את המספר שלך!$"

Route20_Text_NicoleRematchIntro:
	.string "כל השחייה הזאת חיזקה\n"
	.string "את הפוקימונים שלי! בוא נילחם!$"

Route20_Text_NicoleRematchDefeat:
	.string "שוב נסחפתי…$"

Route20_Text_NicolePostRematch:
	.string "ניצחון או הפסד, אני נכנסת לכושר\n"
	.string "וגם הפוקימונים שלי!$"

Route20_Text_SwimmerfNicoleSeen:
	.string "במים אני מרגישה הרבה יותר קלה.$"

Route20_Text_SwimmerfNicoleBeaten:
	.string "אוי, לא!$"

Route20_Text_SwimmerfNicoleAfterBattle:
	.string "שחייה מפעילה את כל הגוף.\p"
	.string "זה ממש בריא.$"

Route20_Text_SwimmerfLoriSeen:
	.string "איזה אוסף מרשים של תגי מכון.\n"
	.string "כדאי שנילחם!$"

Route20_Text_SwimmerfLoriBeaten:
	.string "לא!$"

Route20_Text_SwimmerfLoriAfterBattle:
	.string "גלישה היא כבר לא\n"
	.string "מהלך המ”נ היחיד שמשתמשים בו במים.$"

Route20_Text_SwimmermCameronSeen:
	.string "כנראה שאי אפשר לשחות\n"
	.string "כל הדרך עד ג'וטו.$"

Route20_Text_SwimmermCameronBeaten:
	.string "איייה!$"

Route20_Text_SwimmermCameronAfterBattle:
	.string "חוץ מהים, אני יכול לשחות גם\n"
	.string "באגמים ובנהרות.$"

Route20_Text_CinnabarIsland_GymUnusedSign:
	.string "מה כתוב על השלט הזה?\p"
	.string "מנהיג מכון סיננבר: בליין$"

