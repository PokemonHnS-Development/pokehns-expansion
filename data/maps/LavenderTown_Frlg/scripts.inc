LavenderTown_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LavenderTown_OnTransition
	.byte 0

LavenderTown_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_LAVENDER_TOWN
	setvar VAR_MAP_SCENE_S_S_ANNE_2F_CORRIDOR, 1
	setflag FLAG_HIDE_SS_ANNE_RIVAL
	end

LavenderTown_EventScript_LittleGirl::
	lock
	faceplayer
	msgbox LavenderTown_Text_DoYouBelieveInGhosts, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LavenderTown_EventScript_LittleGirlBelieve
	msgbox LavenderTown_Text_JustImaginingWhiteHand
	release
	end

LavenderTown_EventScript_LittleGirlBelieve::
	msgbox LavenderTown_Text_SoThereAreBelievers
	release
	end

LavenderTown_EventScript_WorkerM::
	msgbox LavenderTown_Text_TownKnownAsMonGraveSite, MSGBOX_NPC
	end

LavenderTown_EventScript_Boy::
	msgbox LavenderTown_Text_GhostsAppearedInTower, MSGBOX_NPC
	end

LavenderTown_EventScript_TownSign::
	msgbox LavenderTown_Text_TownSign, MSGBOX_SIGN
	end

LavenderTown_EventScript_SilphScopeNotice::
	msgbox LavenderTown_Text_SilphScopeNotice, MSGBOX_SIGN
	end

LavenderTown_EventScript_VolunteerHouseSign::
	msgbox LavenderTown_Text_VolunteerPokemonHouse, MSGBOX_SIGN
	end

LavenderTown_EventScript_PokemonTowerSign::
	msgbox LavenderTown_Text_PokemonTowerSign, MSGBOX_SIGN
	end

LavenderTown_Text_DoYouBelieveInGhosts::
	.string "¿Crees en fantasmas?$"

LavenderTown_Text_SoThereAreBelievers::
	.string "¿De verdad?\n"
	.string "Así que hay creyentes...$"

LavenderTown_Text_JustImaginingWhiteHand::
	.string "Jajaja, supongo que no.\p"
	.string "Esa mano blanca en tu hombro...\n"
	.string "Solo me lo estoy imaginando.$"

LavenderTown_Text_TownKnownAsMonGraveSite::
	.string "Este pueblo es conocido como la tumba\n"
	.string "de POKéMON.\p"
	.string "Se realizan servicios conmemorativos\n"
	.string "POKéMON TOWER.$"

LavenderTown_Text_GhostsAppearedInTower::
	.string "Aparecieron fantasmas en la TORRE POKéMON.\p"
	.string "Creo que son los espíritus de\n"
	.string "POKéMON que los ROCKET mataron.$"

LavenderTown_Text_TownSign::
	.string "PUEBLO LAVANDA\n"
	.string "El Noble Pueblo Púrpura$"

LavenderTown_Text_SilphScopeNotice::
	.string "¡Nuevo SILPH SCOPE!\n"
	.string "¡Haz visible lo invisible!\p"
	.string "SILPH CO.$"

LavenderTown_Text_VolunteerPokemonHouse::
	.string "VOLUNTARIOS DE LAVANDA\n"
	.string "CASA POKéMON$"

LavenderTown_Text_PokemonTowerSign::
	.string "TORRE POKéMON\n"
	.string "Calma los espíritus de los POKéMON$"

