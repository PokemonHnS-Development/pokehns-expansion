SixIsland_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SixIsland_OnTransition
	.byte 0

SixIsland_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_SIX_ISLAND
	end

SixIsland_EventScript_Hiker::
	msgbox SixIsland_Text_ThatWayToWaterPathRuinValley, MSGBOX_NPC
	end

SixIsland_EventScript_Boy::
	msgbox SixIsland_Text_SkyAtNightIsFantastic, MSGBOX_NPC
	end

SixIsland_EventScript_IslandSign::
	msgbox SixIsland_Text_IslandSign, MSGBOX_SIGN
	end

SixIsland_Text_IslandSign::
	.string "ISLA SEIS\n"
	.string "Isla Fortuna de la Sabiduría$"

SixIsland_Text_ThatWayToWaterPathRuinValley::
	.string "Sigue por aquí y llegarás\n"
	.string "al CAMINO DEL AGUA.\p"
	.string "Sigue por ahí y llegarás a\n"
	.string "el VALLE RUINA.$"

SixIsland_Text_SkyAtNightIsFantastic::
	.string "Cuando estás tan lejos de la\n"
	.string "ciudad, el cielo nocturno es fantástico.$"

