CinnabarIsland_PokemonLab_Entrance_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, CinnabarIsland_PokemonLab_Entrance_OnTransition
	.byte 0

CinnabarIsland_PokemonLab_Entrance_OnTransition::
	call_if_eq VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_REVIVE_STATE, 1, CinnabarIsland_PokemonLab_Entrance_EventScript_ReadyFossil
	end

CinnabarIsland_PokemonLab_Entrance_EventScript_ReadyFossil::
	setvar VAR_MAP_SCENE_CINNABAR_ISLAND_POKEMON_LAB_EXPERIMENT_ROOM_REVIVE_STATE, 2
	return

CinnabarIsland_PokemonLab_Entrance_EventScript_Scientist::
	msgbox CinnabarIsland_PokemonLab_Entrance_Text_StudyMonsExtensively, MSGBOX_NPC
	end

CinnabarIsland_PokemonLab_Entrance_EventScript_DrFujiPhoto::
	msgbox CinnabarIsland_PokemonLab_Entrance_Text_PhotoOfLabFounderDrFuji, MSGBOX_SIGN
	end

CinnabarIsland_PokemonLab_Entrance_EventScript_MeetingRoomSign::
	msgbox CinnabarIsland_PokemonLab_Entrance_Text_MeetingRoomSign, MSGBOX_SIGN
	end

CinnabarIsland_PokemonLab_Entrance_EventScript_RAndDRoomSign::
	msgbox CinnabarIsland_PokemonLab_Entrance_Text_RAndDRoomSign, MSGBOX_SIGN
	end

CinnabarIsland_PokemonLab_Entrance_EventScript_TestingRoomSign::
	msgbox CinnabarIsland_PokemonLab_Entrance_Text_TestingRoomSign, MSGBOX_SIGN
	end

CinnabarIsland_Gym_Text_PhotoOfBlaineAndFuji::
	.string "Es una foto de BLAINE y\n"
	.string "SR. FUJI.\p"
	.string "Están hombro con hombro\n"
	.string "con grandes sonrisas.$"

CinnabarIsland_PokemonLab_Entrance_Text_StudyMonsExtensively::
	.string "Estudiamos POKéMON a fondo\n"
	.string "todos los días.\p"
	.string "A menudo nos traen POKéMON raros\n"
	.string "para examinarla.$"

CinnabarIsland_PokemonLab_Entrance_Text_PhotoOfLabFounderDrFuji::
	.string "Una foto del fundador del LAB...\n"
	.string "DR. FUJI?!$"

CinnabarIsland_PokemonLab_Entrance_Text_MeetingRoomSign::
	.string "POKéMON LAB\n"
	.string "Sala de reuniones$"

CinnabarIsland_PokemonLab_Entrance_Text_RAndDRoomSign::
	.string "POKéMON LAB\n"
	.string "Sala de investigación$"

CinnabarIsland_PokemonLab_Entrance_Text_TestingRoomSign::
	.string "POKéMON LAB\n"
	.string "Sala de pruebas$"

