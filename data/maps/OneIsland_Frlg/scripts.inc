OneIsland_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OneIsland_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, OneIsland_OnFrame
	.byte 0

OneIsland_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_ONE_ISLAND
	end

OneIsland_OnFrame::
	map_script_2 VAR_MAP_SCENE_ONE_ISLAND_HARBOR, 2, OneIsland_EventScript_EnterOneIslandFirstTime
	.2byte 0

OneIsland_EventScript_EnterOneIslandFirstTime::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_PLAYER, OneIsland_Movement_PlayerExitHarbor
	waitmovement 0
	msgbox OneIsland_Text_BillLetsGoSeeCelio
	closemessage
	applymovement LOCALID_ONE_ISLAND_BILL, OneIsland_Movement_BillWalkToPokeCenter
	applymovement LOCALID_PLAYER, OneIsland_Movement_PlayerWalkToPokeCenter
	waitmovement 0
	opendoor 14, 5
	waitdooranim
	applymovement LOCALID_ONE_ISLAND_BILL, OneIsland_Movement_BillEnterPokeCenter
	applymovement LOCALID_PLAYER, OneIsland_Movement_PlayerEnterPokeCenter
	waitmovement 0
	closedoor 14, 5
	waitdooranim
	removeobject LOCALID_ONE_ISLAND_BILL
	setvar VAR_MAP_SCENE_ONE_ISLAND_HARBOR, 3
	warp MAP_ONE_ISLAND_POKEMON_CENTER_1F, 9, 9
	waitstate
	releaseall
	end

	.macro walk_to_pokecenter
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	.endm

OneIsland_Movement_PlayerWalkToPokeCenter::
	walk_up
	walk_to_pokecenter
	step_end

OneIsland_Movement_PlayerEnterPokeCenter::
	walk_up
	walk_up
	set_invisible
	step_end

OneIsland_Movement_PlayerExitHarbor::
	walk_up
	step_end

OneIsland_Movement_BillWalkToPokeCenter::
	walk_to_pokecenter
	walk_up
	step_end

OneIsland_Movement_BillEnterPokeCenter::
	walk_up
	set_invisible
	step_end

OneIsland_EventScript_OldMan::
	lock
	faceplayer
	goto_if_set FLAG_IS_CHAMPION, OneIsland_EventScript_OldManLinkHoenn
	goto_if_set FLAG_SEVII_DETOUR_FINISHED, OneIsland_EventScript_OldManLinkKanto
	msgbox OneIsland_Text_LuckyToHaveCelioHere
	release
	end

OneIsland_EventScript_OldManLinkKanto::
	msgbox OneIsland_Text_HavePCLinkageWithKanto
	release
	end

OneIsland_EventScript_OldManLinkHoenn::
	msgbox OneIsland_Text_HavePCLinkageWithHoenn
	release
	end

OneIsland_EventScript_BaldingMan::
	msgbox OneIsland_Text_IsntWarmClimateHereGreat, MSGBOX_NPC
	end

OneIsland_EventScript_IslandSign::
	msgbox OneIsland_Text_IslandSign, MSGBOX_SIGN
	end

OneIsland_EventScript_PokemonNetCenterSign::
	msgbox OneIsland_Text_PokemonNetCenterSign, MSGBOX_SIGN
	end

OneIsland_Text_BillLetsGoSeeCelio::
	.string "BILL: ¡Aquí estamos!\n"
	.string "Esta es la ISLA UNO.\p"
	.string "Hay varias islas por aquí\n"
	.string "alrededor, y esta es una de ellas.\p"
	.string "Mi amigo CELIO envió el bote\n"
	.string "para buscarme.\p"
	.string "Él se encarga de la PC de la isla\n"
	.string "la red por su cuenta.\p"
	.string "...¿Por qué te cuento esto ahora?\n"
	.string "¡Vamos a ver a CELIO!$"

Text_WhereDoYouWantToSail::
	.string "¡Hola, marinero!\n"
	.string "¿A dónde quieres navegar?$"

OneIsland_Text_LuckyToHaveCelioHere::
	.string "Aquí estamos en una isla en pleno\n"
	.string "en medio de la nada.\p"
	.string "Somos afortunados de tener\n"
	.string "un joven íntegro como CELIO.\p"
	.string "Mi nieta estaba muy agitada\n"
	.string "over CELIO's friend.\p"
	.string "Algo sobre un famoso\n"
	.string "POKéMANIAC?\p"
	.string "No sé qué significa eso, pero\n"
	.string "¡CELIO es todo un hombre!$"

OneIsland_Text_HavePCLinkageWithKanto::
	.string "Mi nieta estaba muy agitada\n"
	.string "por un nuevo avance.\p"
	.string "Dijo que ahora tenemos conexión\n"
	.string "con gente de KANTO.\p"
	.string "No sé qué significa eso, pero\n"
	.string "¡CELIO es todo un hombre!$"

OneIsland_Text_HavePCLinkageWithHoenn::
	.string "Mi nieta estaba muy agitada\n"
	.string "por un nuevo avance.\p"
	.string "Dijo que por fin tenemos enlace\n"
	.string "de PC con gente de HOENN.\p"
	.string "No sé qué significa eso, pero\n"
	.string "CELIO es todo un hombre.\p"
	.string "Sería un buen esposo para\n"
	.string "¡mi nieta!$"

OneIsland_Text_IslandSign::
	.string "ONE ISLAND\n"
	.string "Friends Gather at Knot Island$"

OneIsland_Text_PokemonNetCenterSign::
	.string "Expanding the POKéMON World!\n"
	.string "POKéMON NET CENTER$"

@ Unused
OneIsland_Text_ReturnToCinnabar::
	.string "グレンタウンに　もどりますか？$"

OneIsland_Text_IsntWarmClimateHereGreat::
	.string "Hola, ¿turisteando, verdad?\n"
	.string "Isn't the warm climate here great?$"

