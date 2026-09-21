AzaleaTown_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AzaleaTown_Pokecenter_OnTransition
	.byte 0

AzaleaTown_Pokecenter_OnTransition::
	setrespawn HEAL_LOCATION_AZALEA_TOWN_HNS
	end

AzaleaPokeCenter_EventScript_Gentleman::
	lock
	faceplayer
	msgbox AzaleaPokecenter_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaPokeCenter_EventScript_Fisher::
	lock
	faceplayer
	msgbox AzaleaPokecenter_Text_FishingGuru, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaPokeCenter_EventScript_PokefanF::
	lock
	faceplayer
	msgbox AzaleaPokecenter_Text_PokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaPokecenter_Text_Gentleman:
	.string "¿Tus POKéMON saben MO?\p"
	.string "Esos movimientos se pueden usar\n"
	.string "aunque tu POKéMON se haya debilitado.$"

AzaleaPokecenter_Text_UnusedPCExplanation:
	.string "Este tal BILL creó el sistema\n"
	.string "para guardar POKéMON en la PC.\p"
	.string "La PC de BILL guarda hasta 30\n"
	.string "POKéMON por BOX.$"

AzaleaPokecenter_Text_FishingGuru:
	.string "La PC de BILL guarda hasta 30\n"
	.string "POKéMON por BOX.$"

AzaleaPokecenter_Text_PokefanF:
	.string "¿Sabes qué son las BAYAS?\p"
	.string "Ábrela, vacíala y ponle\n"
	.string "un dispositivo especial.\p"
	.string "Así podrás capturar POKéMON.\p"
	.string "Antes de que existieran las POKé BALL,\n"
	.string "todos usaban BAYAS.$"
