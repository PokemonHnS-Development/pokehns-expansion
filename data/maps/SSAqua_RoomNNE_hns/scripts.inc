SSAqua_RoomNNE_hns_MapScripts::
	.byte 0

SSAqua_RoomNNE_EventScript_Sean::
	trainerbattle_single TRAINER_SEAN_HNS, SSAqua_RoomNNE_Text_CooltrainermSeanSeen, SSAqua_RoomNNE_Text_CooltrainermSeanBeaten
	msgbox SSAqua_RoomNNE_Text_CooltrainermSeanAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNNE_EventScript_Carol::
	trainerbattle_single TRAINER_CAROL_HNS, SSAqua_RoomNNE_Text_CooltrainerfCarolSeen, SSAqua_RoomNNE_Text_CooltrainerfCarolBeaten
	msgbox SSAqua_RoomNNE_Text_CooltrainerfCarolAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNNE_Text_CooltrainermSeanSeen:
    .string "Iré a KANTO\n"
    .string "para probar mi nivel.$"

SSAqua_RoomNNE_Text_CooltrainermSeanBeaten:
    .string "I wanted to win!$"

SSAqua_RoomNNE_Text_CooltrainermSeanAfterBattle:
    .string "Los ENTRENADORES de JOHTO\n"
    .string "pueden luchar contra los\l"
    .string "LÍDERES de GIMNASIO de KANTO.$"

SSAqua_RoomNNE_Text_CooltrainerfCarolSeen:
    .string "Entreno para\n"
    .string "¡ser el CAMPEÓN!$"

SSAqua_RoomNNE_Text_CooltrainerfCarolBeaten:
    .string "¿Qué es lo que nos\n"
    .string "hace tan diferentes?$"

SSAqua_RoomNNE_Text_CooltrainerfCarolAfterBattle:
    .string "¡Algún día\n"
    .string "te derrotaré!$"
