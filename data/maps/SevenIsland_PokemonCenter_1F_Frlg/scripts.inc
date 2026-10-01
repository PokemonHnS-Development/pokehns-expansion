SevenIsland_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SevenIsland_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

SevenIsland_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_SEVEN_ISLAND
	end

SevenIsland_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

SevenIsland_PokemonCenter_1F_EventScript_OldMan::
	msgbox SevenIsland_PokemonCenter_1F_Text_EventsDependingOnConnections, MSGBOX_NPC
	end

SevenIsland_PokemonCenter_1F_EventScript_Sailor::
	msgbox SevenIsland_PokemonCenter_1F_Text_DidYouRideSeagallopHere, MSGBOX_NPC
	end

SevenIsland_PokemonCenter_1F_EventScript_Beauty::
	msgbox SevenIsland_PokemonCenter_1F_Text_CheckOutTrainerTower, MSGBOX_NPC
	end

SevenIsland_PokemonCenter_1F_Text_EventsDependingOnConnections::
	.string "En esta isla ocurren distintos\n"
	.string "eventos según las conexiones.\p"
	.string "¿Cuáles son esas conexiones?\p"
	.string "Eso lo descubrirás por\n"
	.string "ti mismo.$"

SevenIsland_PokemonCenter_1F_Text_DidYouRideSeagallopHere::
	.string "¿Montaste en un ferry SEAGALLOP?\n"
	.string "para llegar acá?\p"
	.string "Hay al menos diez de esos\n"
	.string "barcos de alta velocidad.\p"
	.string "No sé a dónde van todos,\n"
	.string "su voz.$"

SevenIsland_PokemonCenter_1F_Text_CheckOutTrainerTower::
	.string "Si estás seguro, deberías\n"
	.string "visitar la TORRE ENTRENADORES.$"

