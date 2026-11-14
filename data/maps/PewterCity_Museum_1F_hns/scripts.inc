PewterCity_Museum_1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RuinsOfAlph_Lab_OnTransition
	.byte 0

PewterCity_Museum_1F_EventScript_RootFossil::
	finditem ITEM_ROOT_FOSSIL
	setflag FLAG_HIDE_PEWTER_ROOT_FOSSIL
	removeobject LOCALID_MUSEUM_ROOTFOSSIL
	end

PewterCity_Museum_1F_EventScript_ClawFossil::
	finditem ITEM_CLAW_FOSSIL
	setflag FLAG_HIDE_PEWTER_CLAW_FOSSIL
	removeobject LOCALID_MUSEUM_CLAWFOSSIL
	end

PewterCity_Museum_1F_EventScript_Receptionist::
	msgbox PewterCity_Museum_1F_Text_Recptionist, MSGBOX_NPC
	end

PewterCity_Museum_1F_EventScript_FossilWoman::
	goto_if_set FLAG_HIDE_PEWTER_CLAW_FOSSIL, PewterCity_Museum_1F_EventScript_FossilWoman2
	goto_if_set FLAG_HIDE_PEWTER_ROOT_FOSSIL, PewterCity_Museum_1F_EventScript_FossilWoman2
	goto_if_ge VAR_TEMP_2, 1, PewterCity_Museum_1F_EventScript_FossilWoman2
	msgbox PewterCity_Museum_1F_Text_FossilWoman, MSGBOX_NPC
	setvar VAR_TEMP_2, 1
	end

PewterCity_Museum_1F_EventScript_FossilWoman2::
	msgbox PewterCity_Museum_1F_Text_FossilWomanAfter, MSGBOX_NPC
	end

PewterCity_Museum_1F_EventScript_Oldman::
	msgbox PewterCity_Museum_1F_Text_Oldman, MSGBOX_NPC
	end

PewterCity_Museum_1F_EventScript_Bones::
	msgbox PewterCity_Museum_1F_Text_Bones, MSGBOX_SIGN
	end

PewterCity_Museum_1F_Text_Recptionist:
	.string "ברוכים הבאים!\p"
	.string "רק לידיעתך, כל המוצגים הגדולים\n"
	.string "נלקחו להצגה במוזיאונים אחרים.\p"
	.string "לכן כרגע, הכניסה היא\n"
	.string "ללא תשלום!\p"
	.string "בבקשה, אפשר להיכנס.$"

PewterCity_Museum_1F_Text_FossilWoman:
	.string "אתה בטח מאמן חזק.\p"
	.string "אין לנו הרבה שימוש במאובנים\n"
	.string "שעל הדלפק שם.\p"
	.string "איש מוזר עם שיער כסוף\n"
	.string "השאיר פה המון כאלה.\p"
	.string "אם תרצה, אפשר לקחת אותם.$"

PewterCity_Museum_1F_Text_FossilWomanAfter:
	.string "לעתים קרובות אנחנו חולקים מחקרים\n"
	.string "עם החוקרים של חורבות אלף.\p"
	.string "אנחנו אפילו חולקים איתם מאובנים\n"
	.string "דרך המחשב!$"

PewterCity_Museum_1F_Text_Oldman:
	.string "אני צריך להיות אסיר תודה על\n"
	.string "החיים הארוכים שלי.\p"
	.string "מעולם לא חשבתי שאזכה\n"
	.string "לראות עצמות של דרקון!$"

PewterCity_Museum_1F_Text_Bones:
	.string "עצמות של פוקימון דרקון\n"
	.string "קדום.$"
