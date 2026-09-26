SilphCo_10F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_10F_OnLoad
	.byte 0

SilphCo_10F_OnLoad::
	call_if_unset FLAG_SILPH_10F_DOOR, EventScript_Close10FDoor
	end

SilphCo_10F_EventScript_WorkerF::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_10F_EventScript_WorkerFRocketsGone
	msgbox SilphCo_10F_Text_WaaaImScared
	release
	end

SilphCo_10F_EventScript_WorkerFRocketsGone::
	msgbox SilphCo_10F_Text_KeepMeCryingASecret
	release
	end

SilphCo_10F_EventScript_FloorSign::
	msgbox SilphCo_10F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_10F_EventScript_Travis::
	trainerbattle_single TRAINER_SCIENTIST_TRAVIS, SilphCo_10F_Text_TravisIntro, SilphCo_10F_Text_TravisDefeat
	msgbox SilphCo_10F_Text_TravisPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_10F_EventScript_Grunt::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_39, SilphCo_10F_Text_GruntIntro, SilphCo_10F_Text_GruntDefeat
	msgbox SilphCo_10F_Text_GruntPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_10F_Text_GruntIntro::
	.string "¡Bienvenidos al piso 10!\n"
	.string "¡Qué bueno que vinieron!$"

SilphCo_10F_Text_GruntDefeat::
	.string "¡Estoy pasmado!$"

SilphCo_10F_Text_GruntPostBattle::
	.string "Buen intento, pero la sala de juntas\n"
	.string "una planta más arriba.$"

SilphCo_10F_Text_TravisIntro::
	.string "¡Basta de tus juegos tontos!$"

SilphCo_10F_Text_TravisDefeat::
	.string "¡No quedan continues!$"

SilphCo_10F_Text_TravisPostBattle::
	.string "¿Estás satisfecho con vencerme?\n"
	.string "¡Entonces vete a casa!$"

SilphCo_10F_Text_WaaaImScared::
	.string "Waaaaa!\n"
	.string "¡Tengo miedo!$"

SilphCo_10F_Text_KeepMeCryingASecret::
	.string "Sobre que yo llorara...\n"
	.string "Guárdalo en secreto, por favor.$"

SilphCo_10F_Text_FloorSign::
	.string "SEDE DE SILPH CO.\n"
	.string "10F$"

