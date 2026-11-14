MahoganyTown_House1_hns_MapScripts::
	.byte 0

MahoganyTown_House1_EventScript_BlackBelt::
	msgbox MahoganyRedGyaradosHouse_Text_BlackBelt, MSGBOX_NPC
	end

MahoganyTown_House1_EventScript_Teacher::
	goto_if_lt VAR_GOLDENROD_CITY_STATE, 6, MahoganyTown_House1_EventScript_TeacherBeforeAfter
	goto_if_lt VAR_GOLDENROD_CITY_STATE, 10, MahoganyTown_House1_EventScript_TeacherDuring
MahoganyTown_House1_EventScript_TeacherBeforeAfter::
	msgbox MahoganyRedGyaradosHouse_Text_Teacher, MSGBOX_NPC
	end

MahoganyTown_House1_EventScript_TeacherDuring::
	msgbox MahoganyRedGyaradosHouse_Text_Teacher_Rockets, MSGBOX_NPC
	end


MahoganyRedGyaradosHouse_Text_BlackBelt:
    .string "שמעתי שגרידוס אדום הופיע באגם.\p"
    .string "זה מוזר, כי אפילו גרידוס\n"
    .string "רגילים נדירים באגם ההוא…$"

MahoganyRedGyaradosHouse_Text_Teacher:
    .string "תוכנית הרדיו האהובה עליי? הייתי\n"
    .string "אומרת ”מוזיקת פוקימון”.$"

MahoganyRedGyaradosHouse_Text_Teacher_Rockets:
    .string "כבר כמה זמן אני שומעת צחוק\n"
    .string "ברדיו…\p"
    .string "זה מצמרר.$"
