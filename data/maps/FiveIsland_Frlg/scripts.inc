FiveIsland_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FiveIsland_OnTransition
	.byte 0

FiveIsland_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_FIVE_ISLAND
	end

FiveIsland_EventScript_IslandSign::
	msgbox FiveIsland_Text_IslandSign, MSGBOX_SIGN
	end

FiveIsland_EventScript_BugCatcher::
	msgbox FiveIsland_Text_WeirdBuildingInMeadow, MSGBOX_NPC
	end

FiveIsland_EventScript_Fisher::
	msgbox FiveIsland_Text_BeenGettingBusierAroundHere, MSGBOX_NPC
	end

FiveIsland_Text_IslandSign::
	.string "ISLA CINCO\n"
	.string "Isla del Tiempo: Donde el tiempo pasa$"

FiveIsland_Text_WeirdBuildingInMeadow::
	.string "Oh, qué asco. Quería jugar en\n"
	.string "la PRADERA.\p"
	.string "Pero pusieron un edificio raro\n"
	.string "encima, así que no puedo jugar ahí.$"

FiveIsland_Text_BeenGettingBusierAroundHere::
	.string "Se ha estado llenando más gente\n"
	.string "estas partes últimamente.\p"
	.string "No he pescado muchos buenos\n"
	.string "peces últimamente, tampoco.$"

