SilphCo_8F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_8F_OnLoad
	.byte 0

SilphCo_8F_OnLoad::
	call_if_unset FLAG_SILPH_8F_DOOR, EventScript_Close8FDoor
	end

SilphCo_8F_EventScript_WorkerM::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_8F_EventScript_WorkerMRocketsGone
	msgbox SilphCo_8F_Text_WonderIfSilphIsFinished
	release
	end

SilphCo_8F_EventScript_WorkerMRocketsGone::
	msgbox SilphCo_8F_Text_ThanksForSavingUs
	release
	end

SilphCo_8F_EventScript_FloorSign::
	msgbox SilphCo_8F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_8F_EventScript_Parker::
	trainerbattle_single TRAINER_SCIENTIST_PARKER, SilphCo_8F_Text_ParkerIntro, SilphCo_8F_Text_ParkerDefeat
	msgbox SilphCo_8F_Text_ParkerPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_8F_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_32, SilphCo_8F_Text_Grunt1Intro, SilphCo_8F_Text_Grunt1Defeat
	msgbox SilphCo_8F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_8F_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_36, SilphCo_8F_Text_Grunt2Intro, SilphCo_8F_Text_Grunt2Defeat
	msgbox SilphCo_8F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_8F_Text_WonderIfSilphIsFinished::
	.string "Me pregunto si SILPH ya terminó…$"

SilphCo_8F_Text_ThanksForSavingUs::
	.string "¡Gracias por salvarnos!$"

SilphCo_8F_Text_Grunt1Intro::
	.string "¡Hasta aquí llegaste!$"

SilphCo_8F_Text_Grunt1Defeat::
	.string "¡No tienes agallas!$"

SilphCo_8F_Text_Grunt1PostBattle::
	.string "Si no te das la vuelta…\n"
	.string "¡Llamaré a refuerzos!$"

SilphCo_8F_Text_ParkerIntro::
	.string "¡Nos estás causando problemas!$"

SilphCo_8F_Text_ParkerDefeat::
	.string "¿Eh?\n"
	.string "¿Perdí?$"

SilphCo_8F_Text_ParkerPostBattle::
	.string "¿Qué te parece SILPH?\n"
	.string "BUILDING's maze?$"

SilphCo_8F_Text_Grunt2Intro::
	.string "Soy uno de los cuatro ROCKET\n"
	.string "BROTHERS!$"

SilphCo_8F_Text_Grunt2Defeat::
	.string "Whoo!\n"
	.string "Oh, Brothers!$"

SilphCo_8F_Text_Grunt2PostBattle::
	.string "Te dejo en manos de mis hermanos.$"

SilphCo_8F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "8F$"

SilphCo_8F_Text_ToRocketBossMonsAreTools::
	.string "El JEFE del TEAM ROCKET es terrible\n"
	.string "cruel!\p"
	.string "Para él, los POKéMON son solo\n"
	.string "de ser usado.\p"
	.string "¿Qué pasará si ese tirano\n"
	.string "toma el control de nuestra empresa…$"
