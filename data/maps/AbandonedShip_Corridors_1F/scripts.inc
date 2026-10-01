AbandonedShip_Corridors_1F_MapScripts::
	.byte 0

AbandonedShip_Corridors_1F_EventScript_Youngster::
	msgbox AbandonedShip_Corridors_1F_Text_IsntItFunHere, MSGBOX_NPC
	end

AbandonedShip_Corridors_1F_EventScript_Charlie::
	trainerbattle_single TRAINER_CHARLIE, AbandonedShip_Corridors_1F_Text_CharlieIntro, AbandonedShip_Corridors_1F_Text_CharlieDefeat
	msgbox AbandonedShip_Corridors_1F_Text_CharliePostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Corridors_1F_Text_CharlieIntro:
	.string "¿Qué tiene de gracioso tener mi\n"
	.string "flotador en el barco?$"

AbandonedShip_Corridors_1F_Text_CharlieDefeat:
	.string "¡Vaya, me superaste!$"

AbandonedShip_Corridors_1F_Text_CharliePostBattle:
	.string "¡No es fácil lanzar POKé BALLS\n"
	.string "mientras usas un flotador!$"

AbandonedShip_Corridors_1F_Text_IsntItFunHere:
	.string "¿No es divertido este lugar?\n"
	.string "¡Me emociona solo estar aquí!$"
