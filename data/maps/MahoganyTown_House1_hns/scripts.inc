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
    .string "Oí que apareció un GYARADOS rojo\n"
    .string "en el LAGO.\p"
    .string "Es raro, ya que incluso los\n"
    .string "GYARADOS comunes son raros ahí…$"

MahoganyRedGyaradosHouse_Text_Teacher:
    .string "¿Mi programa favorito? Diría que\n"
    .string "es POKéMON MUSIC.$"

MahoganyRedGyaradosHouse_Text_Teacher_Rockets:
    .string "He estado oyendo risas en la\n"
    .string "radio…\p"
    .string "Da miedo.$"
