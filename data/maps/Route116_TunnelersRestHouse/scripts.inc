Route116_TunnelersRestHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route116_TunnelersRestHouse_OnTransition
	.byte 0

Route116_TunnelersRestHouse_OnTransition:
	setflag FLAG_LANDMARK_TUNNELERS_REST_HOUSE
	end

Route116_TunnelersRestHouse_EventScript_Tunneler1::
	msgbox Route116_TunnelersRestHouse_Text_WeHadToStopBoring, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler2::
	msgbox Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler3::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, Route116_TunnelersRestHouse_EventScript_TunnelOpened
	msgbox Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_EventScript_TunnelOpened::
	msgbox Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_Text_WeHadToStopBoring:
	.string "Aquel TÚNEL RUSTURF...\p"
	.string "Al principio, un gran equipo excavaba\n"
	.string "la roca con maquinaria moderna.\l"
	.string "Pero tuvimos que parar.\p"
	.string "Resulta que habríamos causado\n"
	.string "un efecto negativo en los POKéMON\l"
	.string "salvajes de la zona.\p"
	.string "Así que no nos queda más que\n"
	.string "estar aquí sin hacer nada.$"

Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf:
	.string "Hay un hombre cavando hacia\n"
	.string "VERDANTURF él solo.\l"
	.string "Está desesperado por pasar.\p"
	.string "Dice que si cava poco a poco\n"
	.string "sin usar máquinas, no\l"
	.string "molestará a los POKéMON y evitará\l"
	.string "dañar el medio ambiente.\p"
	.string "Me pregunto si ya terminó.$"

Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel:
	.string "Para ir a VERDANTURF sin usar\n"
	.string "este TÚNEL, tendrías que cruzar el\l"
	.string "mar a DEWFORD, ir a SLATEPORT\l"
	.string "y luego pasar por MAUVILLE.$"

Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough:
	.string "¿Oíste? ¡El TÚNEL a VERDANTURF\n"
	.string "ya está terminado!\p"
	.string "A veces, si deseas algo con fuerza,\n"
	.string "Los sueños se hacen realidad.$"

