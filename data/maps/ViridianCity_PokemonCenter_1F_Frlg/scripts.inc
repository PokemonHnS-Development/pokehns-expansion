ViridianCity_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ViridianCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

ViridianCity_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_VIRIDIAN_CITY
	end

ViridianCity_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

ViridianCity_PokemonCenter_1F_EventScript_Boy::
	msgbox ViridianCity_PokemonCenter_1F_Text_PokeCenterInEveryTown, MSGBOX_NPC
	end

ViridianCity_PokemonCenter_1F_EventScript_Gentleman::
	msgbox ViridianCity_PokemonCenter_1F_Text_FeelFreeToUsePC, MSGBOX_NPC
	end

ViridianCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox ViridianCity_PokemonCenter_1F_Text_PokeCentersHealMons, MSGBOX_NPC
	end

ViridianCity_PokemonCenter_1F_Text_FeelFreeToUsePC::
	.string "Puedes usar esa PC de la\n"
	.string "esquina con toda confianza.\p"
	.string "Me lo dijo la recepcionista.\n"
	.string "¡Qué amable de su parte!$"

ViridianCity_PokemonCenter_1F_Text_PokeCenterInEveryTown::
	.string "Hay un CENTRO POKéMON en cada\n"
	.string "pueblo.\p"
	.string "No cobran nada, así que no\n"
	.string "te dé pena curar POKéMON.$"

ViridianCity_PokemonCenter_1F_Text_PokeCentersHealMons::
	.string "Los CENTROS POKéMON curan a tus\n"
	.string "POKéMON heridos o debilitados.\p"
	.string "Dejan a todos los POKéMON\n"
	.string "sanos del todo.$"

