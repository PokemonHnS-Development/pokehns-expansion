GoldenrodCity_DepartmentStore_7F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GoldenrodCity_DepartmentStore_7F_OnTransition
	.byte 0

GoldenrodCity_DepartmentStore_7F_OnTransition:
	call_if_set FLAG_DAY_POKEMON, GoldenrodCity_DepartmentStore_7F_EventScript_SetNight
	call_if_unset FLAG_DAY_POKEMON, GoldenrodCity_DepartmentStore_7F_EventScript_SetDay
	end

GoldenrodCity_DepartmentStore_7F_EventScript_SetNight::
	setmaplayoutindex LAYOUT_GOLDENROD_CITY_DEPARTMENT_STORE_7FNIGHT_HNS
	return

GoldenrodCity_DepartmentStore_7F_EventScript_SetDay::
	setmaplayoutindex LAYOUT_GOLDENROD_CITY_DEPARTMENT_STORE_7F_HNS
	return


GoldenrodDeptStore7_EventScript_PokefanF::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofPokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofPokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_Twin::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofTwin, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_Nerd::
	lock
	msgbox GoldenrodDeptStore_Text_RoofSuperNerdOhWow, MSGBOX_DEFAULT
	closemessage
	PLAYSE SE_PIN
	applymovement LOCALID_GOLDENROD_ROOF_NERD, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_GOLDENROD_ROOF_NERD
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofSuperNerdQuitBotheringMe, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_GOLDENROD_ROOF_NERD, DIR_SOUTH
	release
	end

GoldenrodDeptStore7_EventScript_Teacher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofTeacher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore7_EventScript_Bugcatcher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore_Text_RoofBugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore_Text_RoofPokefanF:
    .string "אוף, אני עייפה.\p"
    .string "לפעמים אני עולה לגג כדי לנוח\n"
    .string "קצת מהקניות.$"

GoldenrodDeptStore_Text_RoofFisher:
    .string "Pardon? Who says an adult can't get\n"
    .string "into this?\p"
    .string "I'm going to be back every day to\n"
    .string "collect all the dolls!$"

GoldenrodDeptStore_Text_RoofTwin:
    .string "They have bargain sales here every\n"
    .string "so often.$"

GoldenrodDeptStore_Text_RoofSuperNerdOhWow:
    .string "אוי, וואו!$"

GoldenrodDeptStore_Text_RoofSuperNerdQuitBotheringMe:
    .string "אולי תפסיק להציק לי?$"

GoldenrodDeptStore_Text_RoofPokefanM:
    .string "יש משהו שאני ממש רוצה,\n"
    .string "אבל אין לי מספיק כסף…\p"
    .string "אולי אמכור את הפירות\n"
    .string "שאספתי…$"

GoldenrodDeptStore_Text_RoofTeacher:
    .string "Oh, everything is so cheap!\p"
    .string "I bought so much, my PACK's crammed!$"

GoldenrodDeptStore_Text_RoofBugCatcher:
    .string "הפוקימונים שלי תמיד חוטפים שיתוק\n"
    .string "או הרעלה ברגעים הקריטיים…\p"
    .string "אז באתי לקנות ריפוי מלא.\p"
    .string "מעניין אם נשאר עוד?$"
