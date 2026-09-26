CeruleanCity_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CeruleanCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

CeruleanCity_PokemonCenter_1F_OnTransition::
	setrespawn HEAL_LOCATION_CERULEAN_CITY
	end

CeruleanCity_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

CeruleanCity_PokemonCenter_1F_EventScript_Gentleman::
	msgbox CeruleanCity_PokemonCenter_1F_Text_EveryoneCallsBillPokemaniac, MSGBOX_NPC
	end

CeruleanCity_PokemonCenter_1F_EventScript_Rocker::
	msgbox CeruleanCity_PokemonCenter_1F_Text_BillDoesWhateverForRareMons, MSGBOX_NPC
	end

CeruleanCity_PokemonCenter_1F_EventScript_Youngster::
	lock
	faceplayer
	famechecker FAMECHECKER_BILL, 1
	msgbox CeruleanCity_PokemonCenter_1F_Text_BillCollectsRareMons
	release
	end

CeruleanCity_PokemonCenter_1F_EventScript_Lass::
	msgbox CeruleanCity_PokemonCenter_1F_Text_TryTradingUpstairs, MSGBOX_NPC
	end

CeruleanCity_PokemonCenter_1F_Text_BillDoesWhateverForRareMons::
	.string "¡Ese BILL!\p"
	.string "Me dijeron que hará lo que sea\n"
	.string "para conseguir POKéMON raros.\p"
	.string "No le detiene hacer todo tipo\n"
	.string "de cosas, según escuché.$"

CeruleanCity_PokemonCenter_1F_Text_EveryoneCallsBillPokemaniac::
	.string "¿Sabes algo de BILL?\p"
	.string "¡Todos lo llaman POKéMANÍACO!\p"
	.string "Creo que la gente solo tiene\n"
	.string "BILL, digo.\p"
	.string "¿Quién no querría presumir de\n"
	.string "sus POKéMON?$"

CeruleanCity_PokemonCenter_1F_Text_BillCollectsRareMons::
	.string "¡BILL tiene muchos POKéMON!\n"
	.string "¡También colecciona los raros!$"

CeruleanCity_PokemonCenter_1F_Text_TryTradingUpstairs::
	.string "¿Por qué no subes y pruebas?\n"
	.string "intercambiar POKéMON con amigos?\p"
	.string "Podrías tener más variedad\n"
	.string "intercambiando.\p"
	.string "Los POKéMON que cambias crecen\n"
	.string "rápido, también.$"

