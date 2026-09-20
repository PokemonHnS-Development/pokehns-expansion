SaffronCity_PokemonCenter_hns_MapScripts::
map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_PokemonCenter_OnTransition
	.byte 0

SaffronCity_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_SAFFRON_CITY_HNS
	end

SaffronCity_PokemonCenter_EventScript_Teacher::
	msgbox SaffronCity_PokemonCenter1F_Text_Teacher, MSGBOX_NPC	
	end

SaffronCity_PokemonCenter_EventScript_Fisher::
	goto_if_set FLAG_RETURNED_MACHINE_PART, SaffronCity_PokemonCenter_EventScript_FisherReturnedMachinePart
	msgbox SaffronCity_PokemonCenter1F_Text_Fisher, MSGBOX_NPC	
	end
SaffronCity_PokemonCenter_EventScript_FisherReturnedMachinePart::
	msgbox SaffronCity_PokemonCenter1F_Text_Fisher_ReturnedPart, MSGBOX_NPC
	end

SaffronCity_PokemonCenter_EventScript_Youngster::
	msgbox SaffronCity_PokemonCenter1F_Text_Youngster, MSGBOX_NPC
	end

SaffronCity_PokemonCenter1F_Text_Teacher:
	.string "¿Cómo son los CENTROS POKéMON\n"
	.string "de JOHTO?\p"
	.string "...Ya veo. Entonces no son muy\n"
	.string "distintos a los de KANTO.\p"
	.string "¡Puedo ir a JOHTO sin\n"
	.string "preocuparme, entonces!$"

SaffronCity_PokemonCenter1F_Text_Fisher:
	.string "Casualmente pasé por el\n"
	.string "TÚNEL ROCK.\p"
	.string "Hubo cierto alboroto en la\n"
	.string "CENTRAL ELÉCTRICA.$"

SaffronCity_PokemonCenter1F_Text_Fisher_ReturnedPart:
	.string "Hay una cueva rara en CERULEAN.\p"
	.string "Como HIKER pro, debo explorarla,\n"
	.string "but that place scares even me.$"

SaffronCity_PokemonCenter1F_Text_Youngster:
	.string "SILPH CO.'s HEAD OFFICE and the\n"
	.string "MAGNET TRAIN STATION--they're the\l"
	.string "places to see in SAFFRON.$"
