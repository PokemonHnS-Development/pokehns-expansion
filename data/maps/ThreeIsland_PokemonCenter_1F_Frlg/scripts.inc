ThreeIsland_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ThreeIsland_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

ThreeIsland_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_THREE_ISLAND
	end

ThreeIsland_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

ThreeIsland_PokemonCenter_1F_EventScript_Sailor::
	msgbox ThreeIsland_PokemonCenter_1F_Text_ImpossibleToSurfBetweenIslands, MSGBOX_NPC
	end

ThreeIsland_PokemonCenter_1F_EventScript_Lass::
	msgbox ThreeIsland_PokemonCenter_1F_Text_AlwaysBerriesInBerryForest, MSGBOX_NPC
	end

ThreeIsland_PokemonCenter_1F_EventScript_Rocker::
	msgbox ThreeIsland_PokemonCenter_1F_Text_PCNetworkCanLinkWithKanto, MSGBOX_NPC
	end

ThreeIsland_PokemonCenter_1F_Text_PCNetworkCanLinkWithKanto::
	.string "Oye, ¿escuchaste la noticia?\p"
	.string "La red de PC de aquí ya puede\n"
	.string "conectarse con PCs de KANTO.\p"
	.string "No sé cómo ocurrió eso,\n"
	.string "¡pero es fantástico!$"

ThreeIsland_PokemonCenter_1F_Text_ImpossibleToSurfBetweenIslands::
	.string "Es imposible hacer SURF entre el\n"
	.string "islands around these parts.\p"
	.string "Las mareas son muy rápidas\n"
	.string "treacherous.$"

ThreeIsland_PokemonCenter_1F_Text_AlwaysBerriesInBerryForest::
	.string "¡Aplastemos BAYAS!\n"
	.string "…That'd be wasting BERRIES?\p"
	.string "Siempre puedes encontrar BAYAS\n"
	.string "en el suelo del BOSQUE BAYA.$"

