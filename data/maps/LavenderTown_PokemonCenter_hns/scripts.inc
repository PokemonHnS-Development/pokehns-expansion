LavenderTown_PokemonCenter_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavenderTown_PokemonCenter_OnTransition
	.byte 0

LavenderTown_PokemonCenter_OnTransition::
	setrespawn HEAL_LOCATION_LAVENDER_TOWN_HNS
	end

LavenderTown_PokemonCenter_EventScript_Gent::
	msgbox LavenderTown_PokemonCenter1F_Text_Gentleman, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_EventScript_Teacher::
	msgbox LavenderTown_PokemonCenter1F_Text_Teacher, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_EventScript_Youngster::
	goto_if_set FLAG_RETURNED_MACHINE_PART, LavenderTown_PokemonCenter_EventScript_YoungsterReturnedMachinePart
	msgbox LavenderTown_PokemonCenter1F_Text_Youngster, MSGBOX_NPC
	end

LavenderTown_PokemonCenter_EventScript_YoungsterReturnedMachinePart::
	msgbox LavenderTown_PokemonCenter1F_Text_Youngster_ReturnedMachinePart, MSGBOX_NPC
	end

LavenderTown_PokemonCenter1F_Text_Gentleman:
	.string "Al norte de LAVENDER está el\n"
	.string "TÚNEL ROCA. Crúzalo para llegar\l"
	.string "a la CENTRAL ELÉCTRICA.$"

LavenderTown_PokemonCenter1F_Text_Teacher:
	.string "Hay un programa de radio que\n"
	.string "toca música de POKé FLUTE.\p"
	.string " ¿Oh? Tu radio necesita una\n"
	.string "MEJORA DE RADIO para oírlo.\p"
	.string "Tal vez la ESTACIÓN DE RADIO\n"
	.string "del pueblo pueda darte una?$"

LavenderTown_PokemonCenter1F_Text_Youngster:
	.string "Si la CENTRAL ELÉCTRICA no\n"
	.string "funciona, el TREN MAGNÉTICO\p"
	.string "tampoco... Y la ESTACIÓN DE RADIO\n"
	.string "no puede transmitir...$"

LavenderTown_PokemonCenter1F_Text_Youngster_ReturnedMachinePart:
	.string "El DIRECTOR de la ESTACIÓN DE RADIO\n"
	.string "estaba muy feliz.\p"
	.string "Dijo que ya están al aire\n"
	.string "porque la CENTRAL ELÉCTRICA ya\l"
	.string "funciona bien.$"
