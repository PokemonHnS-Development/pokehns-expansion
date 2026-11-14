PewterCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PewterCity_EventScript_CityEnter
	.byte 0

PewterCity_EventScript_CityEnter::
	setflag FLAG_VISITED_PEWTER_CITY
	end

PewterCity_EventScript_CooltrainerF::
	msgbox PewterCity_Text_CooltrainerF, MSGBOX_NPC
	end

PewterCity_EventScript_BugCatcher::
	msgbox PewterCity_Text_BugCatcher, MSGBOX_NPC
	end

PewterCity_EventScript_Gramps::
	lock
	faceplayer
	goto_if_eq VAR_LUGIA_OR_HOOH, 1, PewterCity_EventScript_GrampsRainbowWing
	goto_if_eq VAR_LUGIA_OR_HOOH, 2, PewterCity_EventScript_GrampsSilverWing
	end

PewterCity_EventScript_GrampsRainbowWing::
	checkitem ITEM_RAINBOW_WING
	goto_if_eq VAR_RESULT, TRUE, PewterCity_EventScript_GrampsDone
	msgbox PewterCity_Text_Gramps, MSGBOX_DEFAULT
	setvar VAR_COMPLETED_HO_OH, 4
	giveitem ITEM_RAINBOW_WING
	setflag FLAG_HIDE_TINTOWER_GUARD
	closemessage
	release
	end

PewterCity_EventScript_GrampsSilverWing::
	checkitem ITEM_SILVER_WING
	goto_if_eq VAR_RESULT, TRUE, PewterCity_EventScript_GrampsDone
	msgbox PewterCity_Text_Gramps, MSGBOX_DEFAULT
	setvar VAR_COMPLETED_LUGIA, 4
	giveitem ITEM_SILVER_WING
	setflag FLAG_HIDE_WHIRL_ISLANDS_TENTACRUEL
	closemessage
	release
	end

PewterCity_EventScript_GrampsDone::
	msgbox PewterCity_Text_Gramps_GotSilverWing, MSGBOX_DEFAULT
	closemessage
	release
	end

PewterCity_EventScript_Bugcatcher::
	msgbox PewterCity_Text_BugCatcher, MSGBOX_NPC
	end

PewterCity_EventScript_Cooltrainer::
	msgbox PewterCity_Text_CooltrainerF, MSGBOX_NPC
	end

PewterCity_Text_CooltrainerF:
	.string "כבר ביקרת במכון פיוטר?\p"
	.string "מנהיג המכון משתמש\n"
	.string "בפוקימונים מסוג סלע.$"

PewterCity_Text_BugCatcher:
	.string "בלילה, קלפרי יוצאים לשחק\n"
	.string "בהר הירח.\p"
	.string "אבל לא בכל לילה.$"

PewterCity_Text_Gramps:
	.string "אה, הגעת עד לכאן מג'וטו?\p"
	.string "זה מעורר זיכרונות. כשהייתי צעיר,\n"
	.string "נסעתי לג'וטו להתאמן.\p"
	.string "אתה כל כך מזכיר לי את עצמי\n"
	.string "כשהייתי בחור צעיר.\p"
	.string "הנה. אני רוצה לתת לך את הפריט הזה\n"
	.string "שמצאתי בג'וטו.$"

PewterCity_Text_Gramps_GotSilverWing:
	.string "לנסוע למקומות חדשים ולא מוכרים\n"
	.string "ולפגוש אנשים חדשים…\p"
	.string "אלה התענוגות שבמסעות.$"

PewterCity_EventScript_CitySign::
	msgbox PewterCity_Text_Sign, MSGBOX_NPC
	end

PewterCity_EventScript_GymSign::
	msgbox PewterCity_Text_GymSign, MSGBOX_NPC
	end

PewterCity_EventScript_MuseumSign::
	msgbox PewterCity_Text_MuseumSign, MSGBOX_NPC
	end

PewterCity_EventScript_MtMoonSign::
	msgbox PewterCity_Text_MtMoonGiftShopSign, MSGBOX_NPC
	end

PewterCity_EventScript_WelcomeSign::
	msgbox PewterCity_Text_WelcomeSign, MSGBOX_NPC
	end

PewterCity_Text_Sign:
	.string "העיר פיוטר\n"
	.string "עיר אפורה כסלע$"

PewterCity_Text_GymSign:
	.string "מכון הפוקימון של העיר פיוטר\n"
	.string "מנהיג: ברוק\p"
	.string "מאמן הפוקימונים הקשוח כסלע$"

PewterCity_Text_MuseumSign:
	.string "יש כאן הודעה…\p"
	.string "מוזיאון המדע של פיוטר סגור\n"
	.string "לשיפוצים…$"

PewterCity_Text_MtMoonGiftShopSign:
	.string "יש כאן הודעה…\p"
	.string "חנות המזכרות של הר הירח נפתחה!$"

PewterCity_Text_WelcomeSign:
	.string "ברוכים הבאים לעיר פיוטר!$"

