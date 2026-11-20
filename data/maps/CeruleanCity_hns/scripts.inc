CeruleanCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeruleanCity_EventScript_CityEnter
	.byte 0

CeruleanCity_EventScript_CityEnter::
	setflag FLAG_VISITED_CERULEAN_CITY
	end

CeruleanCity_EventScript_CooltrainerM1::
	goto_if_set FLAG_RETURNED_MACHINE_PART, CeruleanCity_EventScript_CooltrainerMReturnedPart
	msgbox CeruleanCity_Text_CooltrainerM1, MSGBOX_NPC
	end

CeruleanCity_EventScript_CooltrainerMReturnedPart::
	msgbox CeruleanCity_Text_CooltrainerM2, MSGBOX_NPC
	end

CeruleanCity_EventScript_Boy::
	msgbox CeruleanCity_Text_SuperNerd, MSGBOX_NPC
	end

CeruleanCity_EventScript_Guard::
	msgbox CeruleanCity_Text_ThisIsCeruleanCave, MSGBOX_NPC
	end

CeruleanCity_Text_ThisIsCeruleanCave::
    .string "זו מערת סרוליאן.\p"
    .string "בפנים חיים פוקימונים\n"
    .string "חזקים להחריד.\p"
    .string "רק מאמן מיוחד מאוד\n"
    .string "מורשה להיכנס לשם.\p"
    .string "קודם כול, צריך להיות חזק מספיק כדי\n"
    .string "להיות אלוף ליגת הפוקימון של קאנטו.\p"
    .string "וחוץ מזה, צריך גם\n"
    .string "להגיע להישג גדול.$"

CeruleanCity_Text_CooltrainerM1:
	.string "מפעל החשמל של קאנטו?\p"
	.string "הוא ליד הקצה של דרך 9,\n"
	.string "הדרך שיוצאת מכאן מזרחה.\p"
	.string "נראה לי שקרתה שם\n"
	.string "איזושהי תאונה.$"

CeruleanCity_Text_CooltrainerM2:
	.string "אתה אוסף כל פוקימון שקיים?\p"
	.string "זה בטח אתגר לא קטן,\n"
	.string "אבל זה נשמע גם כיף.$"

CeruleanCity_Text_SuperNerd:
	.string "הכף שבצפון הוא מקום טוב\n"
	.string "לדייטים.\p"
	.string "בנות אוהבות אותו!$"

CeruleanCity_EventScript_Slowbro::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SLOWBRO, CRY_MODE_NORMAL
	msgbox CeruleanCity_Text_Slowbro, MSGBOX_DEFAULT
	waitmoncry
	release
	end

CeruleanCity_Text_Slowbro:
	.string "סלוברו: יארה?$"

CeruleanCity_EventScript_SlowbroWoman::
	msgbox CeruleanCity_Text_CooltrainerF1, MSGBOX_NPC
	turnobject LOCALID_CERULEAN_CITY_WOMAN, DIR_EAST
	msgbox CeruleanCity_Text_CooltrainerF2, MSGBOX_DEFAULT
	delay 20
	playmoncry SPECIES_SLOWBRO, CRY_MODE_NORMAL
	applymovement2 LOCALID_CERULEAN_CITY_SLOWBRO, Common_Movement_QuestionMark
	turnobject LOCALID_CERULEAN_CITY_SLOWBRO DIR_WEST
	delay 30
	turnobject LOCALID_CERULEAN_CITY_SLOWBRO, DIR_EAST
	delay 30
	turnobject LOCALID_CERULEAN_CITY_SLOWBRO, DIR_SOUTH
	delay 70
	msgbox CeruleanCity_Text_CooltrainerF3, MSGBOX_NPC
	end

CeruleanCity_Text_CooltrainerF1:
	.string "אני והסלוברו שלי צמד מדהים!$"

CeruleanCity_Text_CooltrainerF2:
	.string "סלוברו, תראה לי את האנדרלמוסיה שלך!$"

CeruleanCity_Text_CooltrainerF3:
	.string "…$"

CeruleanCity_EventScript_Fisher::
	goto_if_eq VAR_CERULEAN_CITY_STATE, 2, CeruleanCity_EventScript_FisherDuringRocket
	msgbox CeruleanCity_Text_Fisher, MSGBOX_NPC
	end

CeruleanCity_EventScript_FisherDuringRocket::
	msgbox CeruleanCity_Text_Fisher_RocketTip, MSGBOX_NPC
	end

CeruleanCity_Text_Fisher:
	.string "אני מעריץ ענק של מיסטי\n"
	.string "ממכון סרוליאן.$"

CeruleanCity_Text_Fisher_RocketTip:
	.string "ראיתי איזה בחור חשוד הולך\n"
	.string "לכיוון כף סרוליאן.$"

CeruleanCity_EventScript_Youngster::
	msgbox CeruleanCity_Text_Youngster1, MSGBOX_NPC
	end

CeruleanCity_Text_Youngster1:
	.string "במערה שמצפון לעיר יש\n"
	.string "פוקימונים חזקים להחריד.$"

CeruleanCity_Text_Youngster2:
	.string "Ayuh?\p"
	.string "My ITEMFINDER is responding…$"

CeruleanCity_EventScript_Sign::
	msgbox CeruleanCity_Text_Sign, MSGBOX_SIGN
	end

CeruleanCity_EventScript_GymSign::
	msgbox CeruleanCity_Text_GymSign, MSGBOX_SIGN
	end

CeruleanCity_EventScript_BikeShopSign::
	msgbox CeruleanCity_Text_BikeShopSign, MSGBOX_SIGN
	end

CeruleanCity_EventScript_PoliceSign::
	msgbox CeruleanCity_Text_PoliceSign, MSGBOX_SIGN
	end

CeruleanCity_EventScript_CapeSign::
	msgbox CeruleanCity_Text_CapeSign, MSGBOX_SIGN
	end

CeruleanCity_Text_Sign:
	.string "העיר סרוליאן\p"
	.string "אפופה בהילה כחולה ומסתורית$"

CeruleanCity_Text_GymSign:
	.string "מכון הפוקימון של העיר סרוליאן\n"
	.string "מנהיגה: מיסטי\p"
	.string "בת הים הבנית$"

CeruleanCity_Text_BikeShopSign:
	.string "יש כאן הודעה…\p"
	.string "חנות האופניים עברה\n"
	.string "לעיר גולדנרוד בג'וטו…$"

CeruleanCity_Text_PoliceSign:
	.string "יש כאן הודעה…\p"
	.string "בואו נמגר את הגניבות ונהפוך\n"
	.string "את העיר למקום ידידותי ועליז יותר!\p"
	.string "משטרת סרוליאן$"

CeruleanCity_Text_CapeSign:
	.string "כף סרוליאן\n"
	.string "בהמשך הדרך$"

CeruleanCity_Text_LockedDoor:
	.string "It's locked…$"

