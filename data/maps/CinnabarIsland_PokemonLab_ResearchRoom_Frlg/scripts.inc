CinnabarIsland_PokemonLab_ResearchRoom_Frlg_MapScripts::
	.byte 0

CinnabarIsland_PokemonLab_ResearchRoom_EventScript_MetronomeTutor::
	goto EventScript_MetronomeTutor
	end

CinnabarIsland_PokemonLab_ResearchRoom_EventScript_Scientist::
	msgbox CinnabarIsland_PokemonLab_ResearchRoom_Text_EeveeCanEvolveIntroThreeMons, MSGBOX_NPC
	end

CinnabarIsland_PokemonLab_ResearchRoom_EventScript_Computer::
	msgbox CinnabarIsland_PokemonLab_ResearchRoom_Text_LegendaryBirdEmail, MSGBOX_SIGN
	end

CinnabarIsland_PokemonLab_ResearchRoom_EventScript_AmberPipe::
	msgbox CinnabarIsland_PokemonLab_ResearchRoom_Text_AnAmberPipe, MSGBOX_SIGN
	end

CinnabarIsland_PokemonLab_ResearchRoom_Text_EeveeCanEvolveIntroThreeMons::
	.string "prehistórico que evoluciona en\n"
	.string "kinds of POKéMON.$"

CinnabarIsland_PokemonLab_ResearchRoom_Text_LegendaryBirdEmail::
	.string "Hay un mensaje de correo.\p"
	.string "… … …\p"
	.string "Hay tres aves legendarias\n"
	.string "POKéMON planta.\p"
	.string "Son ARTICUNO, ZAPDOS y\n"
	.string "MOLTRES.\p"
	.string "Su paradero es desconocido.\p"
	.string "Planeamos explorar la caverna\n"
	.string "cercana a CELESTE.\p"
	.string "From: POKéMON RESEARCH TEAM…$"

CinnabarIsland_PokemonLab_ResearchRoom_Text_AnAmberPipe::
	.string "¡Un tubo de ámbar!$"

