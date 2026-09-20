BlackthornCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BlackthornCity_PokemonCenter_OnTransition
	.byte 0

BlackthornCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_BLACKTHORN_CITY_HNS
	end

BlackthornCity_PokemonCenter_EventScript_Gent::
	msgbox BlackthornCity_PokemonCenter1FGentlemanText, MSGBOX_NPC
	end

BlackthornCity_PokemonCenter_EventScript_Twin::
	msgbox BlackthornCity_PokemonCenter1FTwinText, MSGBOX_NPC
	end

BlackthornCity_PokemonCenter1FGentlemanText:
	.string "En lo profundo de la lejana\n"
	.string "MESETA AÑIL está la LIGA POKéMON.\p"
	.string "Oigo que los mejores entrenadores\n"
	.string "del país se reúnen allí.$"

BlackthornCity_PokemonCenter1FTwinText:
	.string "Había un movimiento que debía\n"
	.string "enseñarle a mi POKéMON.\p"
	.string "Así que usé el BORRADOR DE MOV.\n"
	.string "para que olvidara un MO.$"
