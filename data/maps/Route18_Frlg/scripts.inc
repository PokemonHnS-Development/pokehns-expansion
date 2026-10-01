Route18_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route18_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route18_OnWarp
	.byte 0

Route18_OnTransition::
	call_if_eq VAR_MAP_SCENE_ROUTE16, 1, Route18_OnTransitionCyclingRoad
	end

Route18_OnTransitionCyclingRoad::
	setflag FLAG_SYS_ON_CYCLING_ROAD
	return

Route18_OnWarp::
	map_script_2 VAR_MAP_SCENE_ROUTE16, 1, Route18_OnWarpCyclingRoad
	.2byte 0

Route18_OnWarpCyclingRoad::
	special ForcePlayerOntoBike
	end

Route18_EventScript_RouteSign::
	msgbox Route18_Text_RouteSign, MSGBOX_SIGN
	end

Route18_EventScript_CyclingRoadSign::
	msgbox Route18_Text_CyclingRoadSign, MSGBOX_SIGN
	end

Route18_Text_WiltonIntro::
	.string "Siempre reviso cada zona de hierba\n"
	.string "por POKéMON nuevos.$"

Route18_Text_WiltonDefeat::
	.string "¡Tsk!$"

Route18_Text_WiltonPostBattle::
	.string "¡Ojalá tuviera una BICI!$"

Route18_Text_RamiroIntro::
	.string "Kurukkoo!\n"
	.string "¿Qué tal mi canto de pájaro?$"

Route18_Text_RamiroDefeat::
	.string "¡Tenía que molestarte!$"

Route18_Text_RamiroPostBattle::
	.string "Colecciono POKéMON marinos los fines\n"
	.string "porque el mar está tan cerca.$"

Route18_Text_JacobIntro::
	.string "¡Este es mi territorio!\n"
	.string "¡Fuera de aquí!$"

Route18_Text_JacobDefeat::
	.string "¡Rayos!$"

Route18_Text_JacobPostBattle::
	.string "Este es mi lugar favorito para\n"
	.string "POKéMON.$"

Route18_Text_RouteSign::
	.string "RUTA 18\n"
	.string "CIUDAD CELADON - CIUDAD FUXIA$"

Route18_Text_CyclingRoadSign::
	.string "CICLOVÍA\n"
	.string "¡Prohibido el paso a peatones!$"

