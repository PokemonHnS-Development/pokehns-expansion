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
	.string "FIVE ISLAND\n"
	.string "Chrono Island: Where Time Goes$"

FiveIsland_Text_WeirdBuildingInMeadow::
	.string "Oh, qué asco. Quería jugar en\n"
	.string "la PRADERA.\p"
	.string "Pero pusieron un edificio raro\n"
	.string "on it, so I can't play there.$"

FiveIsland_Text_BeenGettingBusierAroundHere::
	.string "Se ha estado llenando más gente\n"
	.string "these parts lately.\p"
	.string "No he pescado muchos buenos\n"
	.string "fish lately, either.$"

