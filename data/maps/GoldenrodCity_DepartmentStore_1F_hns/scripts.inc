GoldenrodCity_DepartmentStore_1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, GoldenrodDeptElevator_OnFrame
	.byte 0

GoldenrodDeptStore1_EventScript_Receptionist::
	lock
	faceplayer
	msgbox GoldenrodDeptStor1_Text_Receptionist, MSGBOX_DEFAULT
	closemessage
	release
	end
GoldenrodDeptStore1_EventScript_Gentleman::
	lock
	faceplayer
	msgbox GoldenrodDeptStore1_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
	end
GoldenrodDeptStore1_EventScript_PokefanF::
	lock
	faceplayer
	msgbox GoldenrodDeptStore1_Text_PokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end
GoldenrodDeptStore1_EventScript_BugCatcher::
	lock
	faceplayer
	msgbox GoldenrodDeptStore1_Text_BugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodDeptStore1_EventScript_Directory::
	lock
	msgbox GoldenrodDeptStore1_Text_Directory, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodDeptStor1_Text_Receptionist:
    .string "ברוכים הבאים לכלבו של גולדנרוד.$"

GoldenrodDeptStore1_Text_Gentleman:
    .string "בכלבו יש מבחר לא רע.\p"
    .string "אבל יש פריטים שאפשר לקבל רק\n"
    .string "כפרסים במשחקייה.$"

GoldenrodDeptStore1_Text_PokefanF:
    .string "אני להוטה לעשות קניות גם היום!$"

GoldenrodDeptStore1_Text_BugCatcher:
    .string "אמא שלי טובה בציד מציאות.\p"
    .string "היא תמיד קונה דברים במחירים\n"
    .string "נמוכים יותר.$"

GoldenrodDeptStore1_Text_Directory:
    .string "ק1: דלפק שירות\n"
    .string "אתה נמצא כאן.\p"
    .string "ק2: שוק המאמנים\p"
    .string "ק3: ציוד קרב\p"
    .string "ק4: ארון התרופות\p"
    .string "ק5: פינת המ”מ\p"
    .string "ק6: כיכר השלווה\p"
    .string "קומת גג: תצפית$"
