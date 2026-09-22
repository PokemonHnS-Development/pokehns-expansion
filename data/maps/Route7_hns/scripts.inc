Route7_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route7_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route7_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route7_EventScript_Sign::
	msgbox Route7_Text_UndergroundPathSign, MSGBOX_SIGN
	end

Route7_EventScript_Door::
	msgbox Route7_Text_LockedDoor, MSGBOX_SIGN
	end

Route7_Text_UndergroundPathSign:
	.string "¿Qué es este volante?\p"
	.string "... Entrenadores rudos han\n"
	.string "estado luchando en el\l"
	.string "CAMINO SUBTERRÁNEO.\p"
	.string "Por las quejas de los\n"
	.string "vecinos, el CAMINO SUBTERRÁNEO\l"
	.string "está sellado indefinidamente.\p"
	.string "POLICÍA DE CELADON$"

Route7_Text_LockedDoor:
	.string "Está cerrado con llave...$"

