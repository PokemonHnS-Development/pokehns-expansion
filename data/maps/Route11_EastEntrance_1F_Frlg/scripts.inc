Route11_EastEntrance_1F_Frlg_MapScripts::
	.byte 0

Route11_EastEntrance_1F_EventScript_TopGuard::
	msgbox Route11_EastEntrance_1F_Text_ManInLavenderRatesNames, MSGBOX_NPC
	end

Route11_EastEntrance_1F_EventScript_BottomGuard::
	msgbox Route11_EastEntrance_1F_Text_RockTunnelToReachLavender, MSGBOX_NPC
	end

@ Unclear where this is originally from
Route11_EastEntrance_1F_Text_BagIsFull::
	.string "{PLAYER}{KUN}: La BOLSA parece\n"
	.string "estar llena.$"

Route11_EastEntrance_1F_Text_ManInLavenderRatesNames::
	.string "¿No crees que es difícil\n"
	.string "poner buenos nombres a POKéMON?\p"
	.string "pensar en ello? Especialmente\n"
	.string "si atrapaste un montón?\p"
	.string "si atrapaste uno. En PUEBLO\n"
	.string "who rates POKéMON nicknames.\p"
	.string "Hasta puede ayudarte a cambiar el\n"
	.string "de los POKéMON.$"

Route11_EastEntrance_1F_Text_RockTunnelToReachLavender::
	.string "Si quieres llegar a CIUDAD\n"
	.string "LAVANDA, toma el TÚNEL ROCA.\p"
	.string "Puedes llegar al TÚNEL ROCA desde\n"
	.string "CIUDAD CELESTE.$"

