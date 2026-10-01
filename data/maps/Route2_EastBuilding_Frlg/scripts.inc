.equ REQUIRED_SEEN_MONS, 10

Route2_EastBuilding_Frlg_MapScripts::
	.byte 0

Route2_EastBuilding_EventScript_Aide::
	lock
	faceplayer
	call Route2_EastBuilding_EventScript_GetAideRequestInfo
	goto_if_set FLAG_GOT_HM05, Route2_EastBuilding_EventScript_AlreadyGotHM05
	msgbox Route2_EastBuilding_Text_GiveHM05IfSeen10Mons, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Aide_EventScript_DeclineCheckMons
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetFrlgPokedexCount
	buffernumberstring STR_VAR_3, VAR_0x8006
	call Route2_EastBuilding_EventScript_GetAideRequestInfo
	goto_if_lt VAR_0x8006, REQUIRED_SEEN_MONS, Aide_EventScript_HaventCaughtEnough
	msgbox Route2_EastBuilding_Text_GreatHereYouGo
	checkitemspace ITEM_HM05
	goto_if_eq VAR_RESULT, FALSE, Aide_EventScript_NoRoomForItem
	giveitem_msg Route2_EastBuilding_Text_ReceivedHM05FromAide, ITEM_HM05
	setflag FLAG_GOT_HM05
	msgbox Route2_EastBuilding_Text_ExplainHM05
	release
	end

Route2_EastBuilding_EventScript_AlreadyGotHM05::
	msgbox Route2_EastBuilding_Text_ExplainHM05
	release
	end

Route2_EastBuilding_EventScript_GetAideRequestInfo::
	buffernumberstring STR_VAR_1, REQUIRED_SEEN_MONS
	bufferitemname STR_VAR_2, ITEM_HM05
	return

Route2_EastBuilding_EventScript_Rocker::
	msgbox Route2_EastBuilding_Text_CanGetThroughRockTunnel, MSGBOX_NPC
	end

Route2_EastBuilding_Text_GiveHM05IfSeen10Mons::
	.string "¡Hola! ¿Me recuerdas?\n"
	.string "Soy un AYUDANTE del PROF. OAK.\p"
	.string "If your POKéDEX has complete data\n"
	.string "de diez especies, debería\l"
	.string "darte una recompensa.\p"
	.string "El PROF. OAK me encargó\n"
	.string "entregarte la MO05.\p"
	.string "Así que, {PLAYER}, dime.\p"
	.string "¿Ya reuniste datos sobre al menos\n"
	.string "ten kinds of POKéMON?$"

Route2_EastBuilding_Text_GreatHereYouGo::
	.string "¡Genial! Has capturado o tenido\n"
	.string "{STR_VAR_3} tipos de POKéMON!\p"
	.string "¡Felicidades!\n"
	.string "¡Toma!$"

Route2_EastBuilding_Text_ReceivedHM05FromAide::
	.string "{PLAYER} received HM05\n"
	.string "de la AYUDA.$"

Route2_EastBuilding_Text_ExplainHM05::
	.string "MO05 contiene el movimiento oculto\n"
	.string "FLASH.\p"
	.string "FLASH ilumina hasta las cuevas\n"
	.string "más oscuras y mazmorras.$"

Route2_EastBuilding_Text_CanGetThroughRockTunnel::
	.string "Once a POKéMON learns FLASH, you\n"
	.string "puede atravesar TÚNEL ROCA.$"

