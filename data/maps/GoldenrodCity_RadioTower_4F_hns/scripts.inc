GoldenrodCity_RadioTower_4F_hns_MapScripts::
	.byte 0

GoldenrodCity_RadioTower_4F4_EventScript_Sign1::
	lock
	msgbox GoldenrodCity_RadioTower_4F4_Text_Studio2Sign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_EventScript_Sign2::
	lock
	msgbox GoldenrodCity_RadioTower_4F4_Text_ProductionSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodRaidoTower4_EventScript_Grunt28::
	trainerbattle_single TRAINER_GRUNT_28_HNS, GoldenrodCity_RadioTower_4F4_Text_GruntF4Seen, GoldenrodCity_RadioTower_4F4_Text_GruntF4Beaten
	msgbox GoldenrodCity_RadioTower_4F4_Text_GruntF4After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower4_EventScript_Grunt9::
	trainerbattle_single TRAINER_GRUNT_9_HNS, GoldenrodCity_RadioTower_4F4_Text_GruntM10Seen, GoldenrodCity_RadioTower_4F4_Text_GruntM10Beaten
	msgbox GoldenrodCity_RadioTower_4F4_Text_GruntM10After, MSGBOX_AUTOCLOSE
	end

GoldenrodRaidoTower4_EventScript_Proton::
	trainerbattle_single TRAINER_PROTON_2_HNS, GoldenrodCity_RadioTower_4F4_Text_Proton_Seen, GoldenrodCity_RadioTower_4F4_Text_Proton_Beaten
	msgbox GoldenrodCity_RadioTower_4F4_Text_Proton_After, MSGBOX_AUTOCLOSE
	end


GoldenrodCity_RadioTower_4F4_EventScript_Fisher::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_4F4_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_EventScript_Scientist::
	trainerbattle_single TRAINER_RICH_HNS, GoldenrodCity_RadioTower_4F4_Text_ScientistRichSeen, GoldenrodCity_RadioTower_4F4_Text_ScientistRichBeaten
	msgbox GoldenrodCity_RadioTower_4F4_Text_ScientistRichAfter, MSGBOX_AUTOCLOSE
	end


GoldenrodCity_RadioTower_4F4_EventScript_Mary::
	lock
	faceplayer
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_RadioTower_4F4_EventScript_Mary2
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 7, GoldenrodCity_RadioTower_4F4_EventScript_Mary2
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 8, GoldenrodCity_RadioTower_4F4_EventScript_Mary2
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 9, GoldenrodCity_RadioTower_4F4_EventScript_Mary2
	goto_if_unset FLAG_GOT_MARY_BRIGHT_POWDER, GoldenrodCity_RadioTower_4F4_EventScript_Mary3
	msgbox GoldenrodCity_RadioTower_4F4_Text_DJMaryAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_EventScript_Mary2::
	msgbox GoldenrodCity_RadioTower_4F4_Text_DJMary, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_EventScript_Mary3::
	msgbox GoldenrodCity_RadioTower_4F4_Text_DJMaryCleared, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_BRIGHT_POWDER
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox GoldenrodCity_RadioTower_4F4_Text_DJMaryPinkBow, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_GOT_MARY_BRIGHT_POWDER
	closemessage
	release
	end

GoldenrodCity_RadioTower_4F4_EventScript_Meowth::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MEOWTH, CRY_MODE_NORMAL
	msgbox GoldenrodCity_RadioTower_4F4_Text_Meowth, MSGBOX_DEFAULT
	waitmoncry
	release
	end


GoldenrodCity_RadioTower_4F4_Text_Proton_Seen:
	.string "פרוטון: רגע אחד!\p"
	.string "אתה לא זה שהפריע לנו\n"
	.string "בבאר סלופוק?\p"
	.string "אני מבין… אתה עושה את כל זה כדי\n"
	.string "להכעיס אותי. כדאי לך להיזהר!\p"
	.string "אבל אם זה מה שאתה רוצה, אראה לך\n"
	.string "את מלוא הזעם של מנהל בצוות רוקט!$"

GoldenrodCity_RadioTower_4F4_Text_Proton_Beaten:
	.string "פיו…$"

GoldenrodCity_RadioTower_4F4_Text_Proton_After:
	.string "פרוטון: אולי ניצחת הפעם…\p"
	.string "אבל כל מה שעשית זה להגביר\n"
	.string "את הזעם של צוות רוקט.$"

GoldenrodCity_RadioTower_4F4_Text_Fisher:
	.string "הקשבתי לרדיו כשהייתי\n"
	.string "בחורבות.\p"
	.string "שמעתי שם שידור מוזר.$"

GoldenrodCity_RadioTower_4F4_Text_DJMary:
	.string "מרי: למה? למה אני צריכה\n"
	.string "לסבול את כל זה?\p"
	.string "מיאו, תעזור לי!$"

GoldenrodCity_RadioTower_4F4_Text_DJMaryCleared:
	.string "מרי: הו! אתה המושיע הקטן שלי!\p"
	.string "תקבל את זה כאות תודה?$"

GoldenrodCity_RadioTower_4F4_Text_DJMaryPinkBow:
	.string "מרי: זה עוזר להתחמק\n"
	.string "מהתקפות של היריב.$"

GoldenrodCity_RadioTower_4F4_Text_DJMaryAfter:
	.string "מרי: תאזין לי בתוכנית\n"
	.string "”שיחות פוקימון” של פרופ' אוק!$"

GoldenrodCity_RadioTower_4F4_Text_Meowth:
	.string "מיאו: מיאו…$"

GoldenrodCity_RadioTower_4F4_Text_GruntM10Seen:
	.string "אתה מתכנן להציל את מנהל התחנה?\p"
	.string "זה לא יקרה, כי אני הולך\n"
	.string "לנצח אותך!$"

GoldenrodCity_RadioTower_4F4_Text_GruntM10Beaten:
	.string "לא! לא ייאמן!$"

GoldenrodCity_RadioTower_4F4_Text_GruntM10After:
	.string "אני לא מאמין! הפסדתי!$"

GoldenrodCity_RadioTower_4F4_Text_ExecutiveM2Seen:
	.string "Stop! I'm known as the TEAM ROCKET\n"
	.string "fortress!\p"
	.string "You're not taking another step!$"

GoldenrodCity_RadioTower_4F4_Text_ExecutiveM2Beaten:
	.string "The fortress came down!$"

GoldenrodCity_RadioTower_4F4_Text_ExecutiveM2After:
	.string "You've earned my respect, so here's\n"
	.string "some advice.\p"
	.string "It's not too late. You can still turn\n"
	.string "back.$"

GoldenrodCity_RadioTower_4F4_Text_GruntF4Seen:
	.string "אם אני חושבת שפוקימונים חמודים?\p"
	.string "אני אחשוב שהפוקימונים שלי\n"
	.string "חמודים…\p"
	.string "אחרי שהם ינצחו את שלך!$"

GoldenrodCity_RadioTower_4F4_Text_GruntF4Beaten:
	.string "אוי, לא! הם כל כך חסרי תועלת!$"

GoldenrodCity_RadioTower_4F4_Text_GruntF4After:
	.string "אני אוהבת את עצמי היפה!\p"
	.string "למי אכפת מפוקימונים?$"

GoldenrodCity_RadioTower_4F4_Text_ScientistRichSeen:
	.string "מצוין ביותר.\p"
	.string "מגדל הרדיו הזה יגשים את\n"
	.string "התוכנית הגדולה שלנו.$"

GoldenrodCity_RadioTower_4F4_Text_ScientistRichBeaten:
	.string "הממ…\p"
	.string "לכל תוכנית גדולה יש תקלות.$"

GoldenrodCity_RadioTower_4F4_Text_ScientistRichAfter:
	.string "אתה באמת מאמין שתוכל לעצור\n"
	.string "את צוות רוקט?$"

GoldenrodCity_RadioTower_4F4_Text_ProductionSign:
	.string "קומה 4: הפקה$"

GoldenrodCity_RadioTower_4F4_Text_Studio2Sign:
	.string "קומה 4: אולפן 2$"
