VermilionCity_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VermilionCity_PokemonCenter_OnTransition
	.byte 0

VermilionCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_VERMILION_CITY_HNS
	end

VermilionPokeCenter_EventScript_FishingGuru::
	goto_if_set FLAG_HIDE_VERMILION_SNORLAX, VermilionPokeCenter_EventScript_FishingGuru2
	msgbox VermilionCity_PokemonCenter1F_Text_FishingGuru, MSGBOX_NPC
	end

VermilionPokeCenter_EventScript_FishingGuru2::
	msgbox VermilionCity_PokemonCenter1F_Text_FishingGuru_FoughtSnorlax, MSGBOX_NPC
	end

VermilionPokeCenter_EventScript_Sailor::
	msgbox VermilionCity_PokemonCenter1F_Text_Sailor, MSGBOX_NPC
	end

VermilionPokeCenter_EventScript_Bugcatcher::
	msgbox VermilionCity_PokemonCenter1F_Text_BugCatcher, MSGBOX_NPC
	end

VermilionCity_PokemonCenter1F_Text_FishingGuru:
	.string "Un POKéMON dormido está\n"
	.string "frente a la CUEVA DIGLETT.\p"
	.string "Es una gran oportunidad para\n"
	.string "atraparlo, ¿pero cómo lo despiertas?$"

VermilionCity_PokemonCenter1F_Text_FishingGuru_FoughtSnorlax:
	.string "Había un POKéMON dormido\n"
	.string "frente a la CUEVA DIGLETT.\l"
	.string "CUEVA DIGLETT.\p"
	.string "Pero parece que ha desaparecido.$"

VermilionCity_PokemonCenter1F_Text_Sailor:
	.string "El BARCO RÁPIDO es un gran lugar\n"
	.string "conoce y lucha con entrenadores.$"

VermilionCity_PokemonCenter1F_Text_BugCatcher:
	.string "¿Oh? Tienes algunas MEDALLAS que\n"
	.string "nunca había visto.\p"
	.string "Ah, ya entiendo. Los conseguiste en\n"
	.string "JOHTO.$"
