SilphCo_6F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_6F_OnLoad
	.byte 0

SilphCo_6F_OnLoad::
	call_if_unset FLAG_SILPH_6F_DOOR, EventScript_Close6FDoor
	end

SilphCo_6F_EventScript_WorkerM2::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_6F_EventScript_WorkerM2RocketsGone
	msgbox SilphCo_6F_Text_TargetedSilphForOurMonProducts
	release
	end

SilphCo_6F_EventScript_WorkerM2RocketsGone::
	msgbox SilphCo_6F_Text_ComeWorkForSilphWhenYoureOlder
	release
	end

SilphCo_6F_EventScript_WorkerM3::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_6F_EventScript_WorkerM3RocketsGone
	msgbox SilphCo_6F_Text_RocketsTookOverBuilding
	release
	end

SilphCo_6F_EventScript_WorkerM3RocketsGone::
	msgbox SilphCo_6F_Text_BetterGetBackToWork
	release
	end

SilphCo_6F_EventScript_WorkerM1::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_6F_EventScript_WorkerM1RocketsGone
	msgbox SilphCo_6F_Text_HelpMePlease
	release
	end

SilphCo_6F_EventScript_WorkerM1RocketsGone::
	msgbox SilphCo_6F_Text_WeGotEngaged
	release
	end

SilphCo_6F_EventScript_WorkerF1::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_6F_EventScript_WorkerF1RocketsGone
	msgbox SilphCo_6F_Text_ThatManIsSuchACoward
	release
	end

SilphCo_6F_EventScript_WorkerF1RocketsGone::
	msgbox SilphCo_6F_Text_NeedsMeToLookAfterHim
	release
	end

SilphCo_6F_EventScript_WorkerF2::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_6F_EventScript_WorkerF2RocketsGone
	msgbox SilphCo_6F_Text_RocketsTryingToConquerWorld
	release
	end

SilphCo_6F_EventScript_WorkerF2RocketsGone::
	msgbox SilphCo_6F_Text_RocketsRanAwayBecauseOfYou
	release
	end

SilphCo_6F_EventScript_FloorSign::
	msgbox SilphCo_6F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_6F_EventScript_Taylor::
	trainerbattle_single TRAINER_SCIENTIST_TAYLOR, SilphCo_6F_Text_TaylorIntro, SilphCo_6F_Text_TaylorDefeat
	msgbox SilphCo_6F_Text_TaylorPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_6F_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_30, SilphCo_6F_Text_Grunt1Intro, SilphCo_6F_Text_Grunt1Defeat
	msgbox SilphCo_6F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_6F_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_31, SilphCo_6F_Text_Grunt2Intro, SilphCo_6F_Text_Grunt2Defeat
	msgbox SilphCo_6F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_6F_Text_RocketsTookOverBuilding::
	.string "Los COHETES vinieron y tomaron\n"
	.string "¡el edificio!$"

SilphCo_6F_Text_BetterGetBackToWork::
	.string "Bueno, mejor vuelvo al trabajo.$"

SilphCo_6F_Text_HelpMePlease::
	.string "Oh dear, oh dear.\n"
	.string "¡Ayúdenme, por favor!$"

SilphCo_6F_Text_WeGotEngaged::
	.string "Nos comprometimos.\n"
	.string "Heheh!$"

SilphCo_6F_Text_ThatManIsSuchACoward::
	.string "Ese hombre a mi lado...\n"
	.string "¡Es un cobarde!$"

SilphCo_6F_Text_NeedsMeToLookAfterHim::
	.string "Es tan inútil que necesitó\n"
	.string "a alguien como yo para cuidarlo.$"

SilphCo_6F_Text_RocketsTryingToConquerWorld::
	.string "El EQUIPO ROCKET intenta conquistar\n"
	.string "the world with POKéMON.$"

SilphCo_6F_Text_RocketsRanAwayBecauseOfYou::
	.string "El EQUIPO ROCKET huyó, y todo\n"
	.string "¡por tu culpa!$"

SilphCo_6F_Text_TargetedSilphForOurMonProducts::
	.string "Debieron atacar a SILPH por\n"
	.string "our POKéMON products.$"

SilphCo_6F_Text_ComeWorkForSilphWhenYoureOlder::
	.string "Ven a trabajar para SILPH\n"
	.string "cuando seas mayor.$"

SilphCo_6F_Text_Grunt1Intro::
	.string "Soy uno de los cuatro del\n"
	.string "BROTHERS!$"

SilphCo_6F_Text_Grunt1Defeat::
	.string "Flame out!$"

SilphCo_6F_Text_Grunt1PostBattle::
	.string "¡No importa!\n"
	.string "¡Mis hermanos me vengarán!$"

SilphCo_6F_Text_TaylorIntro::
	.string "¡Ese PRESIDENTE podrido!\p"
	.string "Bien tiene por enviarme\n"
	.string "a la SUCURSAL TIKSI!\p"
	.string "That's why TEAM ROCKET came after\n"
	.string "¡Estoy seguro!$"

SilphCo_6F_Text_TaylorDefeat::
	.string "Shoot!$"

SilphCo_6F_Text_TaylorPostBattle::
	.string "TIKSI BRANCH?\n"
	.string "¡Está en tierra de nadie rusa!$"

SilphCo_6F_Text_Grunt2Intro::
	.string "You dare betray TEAM ROCKET?$"

SilphCo_6F_Text_Grunt2Defeat::
	.string "¡Traidor!$"

SilphCo_6F_Text_Grunt2PostBattle::
	.string "Si defiendes la justicia,\n"
	.string "¡Los villanos nos traicionan!$"

SilphCo_6F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "6F$"

