CianwoodPokecenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CianwoodPokecenter_OnTransition
	.byte 0

CianwoodPokecenter_OnTransition::
	setrespawn HEAL_LOCATION_CIANWOOD_CITY_HNS
	end

CianwoodPokemoncenter_EventScript_Fisher::
	lock
	faceplayer
	goto_if_set FLAG_TEMP_1, CianwoodPokemoncenter_EventScript_FisherNormal
	checkfieldmove FIELD_MOVE_SURF
	goto_if_eq VAR_RESULT, PARTY_SIZE, CianwoodPokemoncenter_EventScript_FisherGiveTentacool
CianwoodPokemoncenter_EventScript_FisherNormal::
	msgbox CianwoodPokemoncenter_Text_Fisher1, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodPokemoncenter_EventScript_FisherGiveTentacool::
	msgbox CianwoodPokemoncenter_Text_Fisher2, MSGBOX_DEFAULT
	@HnS gift pokemon setup
	@callnative DisableStaticRandomizer
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TENTACOOL
	bufferspeciesname STR_VAR_1, SPECIES_TENTACOOL
	givemon SPECIES_TENTACOOL, 25
	call Common_EventScript_GiftMon
	setflag FLAG_TEMP_1
	@callnative EnableStaticRandomizer
	closemessage
	release
	end

CianwoodPokemoncenter_Text_Fisher1:
	.string "מבין פוקימוני המים, טנטקול\n"
	.string "הכי טוב בהפרש של מייל ימי!$"

CianwoodPokemoncenter_Text_Fisher2:
	.string "נראה שחסר לך\n"
	.string "פוקימון מים.\p"
	.string "הנה, קח אותו, יש לי הרבה כאלה.$"

CianwoodPokecenter_EventScript_Lass::
	lock
	faceplayer
	msgbox CianwoodCity_Text_PokecenterLass, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_PokecenterLass:
	.string "פגשת את הפוקימאניאק?\p"
	.string "הוא תמיד מתרברב בפוקימונים\n"
	.string "הנדירים שלו.$"


CianwoodGym_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_CIANWOOD_GYM, CianwoodGym_EventScript_GymGuideAfter
	msgbox CianwoodCity_Text_GymGuide, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodGym_EventScript_GymGuideAfter::
	msgbox CianwoodCity_Text_GymGuideWin, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_GymGuide:
	.string "מאמני מכון הפוקימון כאן\n"
	.string "הם בריונים מאצ'ואים.\p"
	.string "אם אשאר כאן, הם עלולים\n"
	.string "לבוא אחריי.\p"
	.string "הנה עצה: מנהיג המכון\n"
	.string "משתמש בסוג קרב.\p"
	.string "אז כדאי לבלבל אותו עם\n"
	.string "פוקימונים מסוג על-חושי.\p"
	.string "כדאי לחסל את הפוקימונים שלו\n"
	.string "לפני שינצלו את הכוח הפיזי שלהם.\p"
	.string "והסלעים באמצע המכון?\p"
	.string "אם לא מזיזים אותם נכון,\n"
	.string "אי אפשר להגיע למנהיג המכון.\p"
	.string "אם נתקעת, כדאי לצאת החוצה.$"

CianwoodCity_Text_GymGuideWin:
	.string "{PLAYER}! ניצחת!\n"
	.string "ידעתי את זה רק מלהסתכל עליך!$"

CianwoodPokecenter_EventScript_Nerd::
	lock
	faceplayer
	msgbox CianwoodCity_Text_PokecenterSuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodCity_Text_PokecenterSuperNerd:
	.string "אני אוהב להשוויץ בפוקימונים\n"
	.string "שגידלתי.\p"
	.string "גם אתה, לא?\p"
	.string "אני הולך להשתתף בהמון קרבות\n"
	.string "ולהשוויץ בפוקימונים שלי!$"
