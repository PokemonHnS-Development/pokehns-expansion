MahoganyTown_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MahoganyTown_PokemonCenter_OnTransition
	.byte 0

MahoganyTown_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_MAHOGANY_TOWN_HNS
	end

MahoganyTown_PokemonCenter_EventScript_Hiker::
	msgbox MahoganyTown_PokemonCenter_Text_PokefanM, MSGBOX_NPC
	end
	
MahoganyTown_PokemonCenter_EventScript_Boy::
	msgbox MahoganyTown_PokemonCenter_Text_Youngster, MSGBOX_NPC
	end

MahoganyTown_PokemonCenter_EventScript_Girl::
	msgbox MahoganyTown_PokemonCenter_Text_CooltrainerF, MSGBOX_NPC
	end

MahoganyTown_PokemonCenter_Text_PokefanM:
    .string "¿Qué es esto? ¿El TEAM ROCKET ha\n"
    .string "vuelto?\p"
    .string "Vi hombres de negro en el LAGO de la\n"
    .string "Furia…$"

MahoganyTown_PokemonCenter_Text_Youngster:
    .string "Evito que mis POKéMON evolucionen\n"
    .string "muy pronto.\p"
    .string "Hago que aprendan ciertos movimientos\n"
    .string "antes de que evolucionen.$"

MahoganyTown_PokemonCenter_Text_CooltrainerF:
    .string "Los POKéMON se hacen más fuertes al\n"
    .string "evolucionar,\p"
    .string "pero también aprenden movimientos\n"
    .string "más lento.$"
