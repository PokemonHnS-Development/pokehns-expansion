SSAqua_RoomSW_hns_MapScripts::
	.byte 0

SSAqua_RoomSW_EventScript_Cassie::
	trainerbattle_single TRAINER_CASSIE_HNS, SSAqua_RoomSW_Text_BeautyCassieSeen, SSAqua_RoomSW_Text_BeautyCassieBeaten
	msgbox SSAqua_RoomSW_Text_BeautyCassieAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSW_EventScript_Clyde::
	trainerbattle_single TRAINER_CLYDE_HNS, SSAqua_RoomSW_Text_GuitaristClydeSeen, SSAqua_RoomSW_Text_GuitaristClydeBeaten
	msgbox SSAqua_RoomSW_Text_GuitaristClydeAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSW_Text_BeautyCassieSeen:
    .string "Trato de olvidar mis penas.\n"
    .string "¡A luchar!$"

SSAqua_RoomSW_Text_BeautyCassieBeaten:
    .string "Mi corazón llora...$"

SSAqua_RoomSW_Text_BeautyCassieAfterBattle:
    .string "Un viaje es lo mejor para sanar\n"
    .string "un corazón roto.\p"
    .string "Pero un viaje RÁPIDO es muy corto\n"
    .string "para el duelo.$"

SSAqua_RoomSW_Text_GuitaristClydeSeen:
    .string "Iré a hacer una audición con mis\n"
    .string "canciones en la RADIO de TRIGAL.$"

SSAqua_RoomSW_Text_GuitaristClydeBeaten:
    .string "¡Uala! ¡Distorsión total!$"

SSAqua_RoomSW_Text_GuitaristClydeAfterBattleMobile:
    .string "Iba a hacer mi debut en la\n"
    .string "BATTLE TOWER...\p"
    .string "Debería volver a VERMILION y\n"
    .string "repetir mi entrenamiento...$"

SSAqua_RoomSW_Text_GuitaristClydeAfterBattle:
    .string "Hablando de la ESTACIÓN DE RADIO,\n"
    .string "¿Cuál es el número suerte hoy?$"
