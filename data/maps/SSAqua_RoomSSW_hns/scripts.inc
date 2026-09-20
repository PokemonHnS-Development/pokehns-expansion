SSAqua_RoomSSW_hns_MapScripts::
	.byte 0

SSAqua_RoomSSW_EventScript_Lyle::
	trainerbattle_single TRAINER_LYLE_HNS, SSAqua_RoomSSW_Text_FirebreatherLyleSeen, SSAqua_RoomSSW_Text_FirebreatherLyleBeaten
	msgbox SSAqua_RoomSSW_Text_FirebreatherLyleAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSSW_EventScript_Ken::
	trainerbattle_single TRAINER_KEN_HNS, SSAqua_RoomSSW_Text_BugCatcherKenSeen, SSAqua_RoomSSW_Text_BugCatcherKenBeaten
	msgbox SSAqua_RoomSSW_Text_BugCatcherKenAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSSW_Text_FirebreatherLyleSeen:
    .string "Voy a KANTO para dar\n"
    .string "¡shows de fuego!$"

SSAqua_RoomSSW_Text_FirebreatherLyleBeaten:
    .string "Fizzle… The flame's tiny…$"

SSAqua_RoomSSW_Text_FirebreatherLyleAfterBattle:
    .string "El fuego es débil en el mar.\n"
    .string "¿No importa? ¿En serio?$"

SSAqua_RoomSSW_Text_BugCatcherKenSeen:
    .string "Visitaré a mi abuela para\n"
    .string "¡atrapar algunos bichos!$"

SSAqua_RoomSSW_Text_BugCatcherKenBeaten:
    .string "Ooh, wow. You're tough!$"

SSAqua_RoomSSW_Text_BugCatcherKenAfterBattle:
    .string "¡Hay muchos POKéMON\n"
    .string "en los árboles de JOHTO!$"
