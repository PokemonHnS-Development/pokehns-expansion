VictoryRoad_3F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, VictoryRoad_3F_OnLoad
	.byte 0

VictoryRoad_3F_OnLoad::
	call_if_ne VAR_MAP_SCENE_VICTORY_ROAD_3F, 100, VictoryRoad_3F_EventScript_SetRockBarrier
	end

VictoryRoad_3F_EventScript_SetRockBarrier::
	setmetatile 12, 12, METATILE_Cave_RockBarrier_Top, 1
	setmetatile 12, 13, METATILE_Cave_RockBarrier_Bottom, 1
	return

VictoryRoad_3F_EventScript_FloorSwitch::
	lockall
	goto_if_eq VAR_MAP_SCENE_VICTORY_ROAD_3F, 100, VictoryRoad_3F_EventScript_FloorSwitchAlreadyPressed
	setmetatile 12, 12, METATILE_Cave_Floor_Ledge_Top, 0
	setmetatile 12, 13, METATILE_Cave_Floor_Ledge_Bottom, 0
	playse SE_ICE_BREAK
	special DrawWholeMapView
	waitse
	copyobjectxytoperm LOCALID_VICTORY_ROAD_3F_BOULDER1
	copyobjectxytoperm LOCALID_VICTORY_ROAD_3F_BOULDER2
	setvar VAR_MAP_SCENE_VICTORY_ROAD_3F, 100
	releaseall
	end

VictoryRoad_3F_EventScript_FloorSwitchAlreadyPressed::
	releaseall
	end

VictoryRoad_3F_EventScript_George::
	trainerbattle_single TRAINER_COOLTRAINER_GEORGE, VictoryRoad_3F_Text_GeorgeIntro, VictoryRoad_3F_Text_GeorgeDefeat
	msgbox VictoryRoad_3F_Text_GeorgePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_3F_EventScript_Colby::
	trainerbattle_single TRAINER_COOLTRAINER_COLBY, VictoryRoad_3F_Text_ColbyIntro, VictoryRoad_3F_Text_ColbyDefeat
	msgbox VictoryRoad_3F_Text_ColbyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_3F_EventScript_Caroline::
	trainerbattle_single TRAINER_COOLTRAINER_CAROLINE, VictoryRoad_3F_Text_CarolineIntro, VictoryRoad_3F_Text_CarolineDefeat
	msgbox VictoryRoad_3F_Text_CarolinePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_3F_EventScript_Alexa::
	trainerbattle_single TRAINER_COOLTRAINER_ALEXA, VictoryRoad_3F_Text_AlexaIntro, VictoryRoad_3F_Text_AlexaDefeat
	msgbox VictoryRoad_3F_Text_AlexaPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_3F_EventScript_Ray::
	trainerbattle_double TRAINER_COOL_COUPLE_RAY_TYRA, VictoryRoad_3F_Text_RayIntro, VictoryRoad_3F_Text_RayDefeat, VictoryRoad_3F_Text_RayNotEnoughMons
	msgbox VictoryRoad_3F_Text_RayPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_3F_EventScript_Tyra::
	trainerbattle_double TRAINER_COOL_COUPLE_RAY_TYRA, VictoryRoad_3F_Text_TyraIntro, VictoryRoad_3F_Text_TyraDefeat, VictoryRoad_3F_Text_TyraNotEnoughMons
	msgbox VictoryRoad_3F_Text_TyraPostBattle, MSGBOX_AUTOCLOSE
	end

Text_DoubleEdgeTeach::
	.string "Debes estar orgulloso de ti,\n"
	.string "por haber luchado hasta llegar\l"
	.string "a la CALLE VICTORIA con valor.\p"
	.string "En reconocimiento a tu hazaña,\n"
	.string "te enseñaré DOBLE FILO.\p"
	.string "¿Quieres que te enseñe ese\n"
	.string "movimiento?$"

Text_DoubleEdgeDeclined::
	.string "Te enseñaré la técnica\n"
	.string "en cualquier momento.$"

Text_DoubleEdgeWhichMon::
	.string "¿A qué POKéMON le enseño\n"
	.string "CABEZA DE HIERRO?$"

Text_DoubleEdgeTaught::
	.string "Sigue con ese ánimo para\n"
	.string "la LIGA POKéMON!\p"
	.string "Corre hacia ellos y derribalos\n"
	.string "¡a todos!$"

VictoryRoad_3F_Text_GeorgeIntro::
	.string "Oí rumores de un niño prodigio.$"

VictoryRoad_3F_Text_GeorgeDefeat::
	.string "¡Los rumores eran ciertos!$"

VictoryRoad_3F_Text_GeorgePostBattle::
	.string "Así que fuiste tú quien venció a\n"
	.string "GIOVANNI del TEAM ROCKET?$"

VictoryRoad_3F_Text_AlexaIntro::
	.string "Los ENTRENADORES viven buscando\n"
	.string "opponents.$"

VictoryRoad_3F_Text_AlexaDefeat::
	.string "Oh!\n"
	.string "So strong!$"

VictoryRoad_3F_Text_AlexaPostBattle::
	.string "Al librar batallas duras, te vuelves\n"
	.string "más fuerte.$"

VictoryRoad_3F_Text_CarolineIntro::
	.string "Te mostraré lo bueno que\n"
	.string "eres. ¡Ni loco!$"

VictoryRoad_3F_Text_CarolineDefeat::
	.string "¡Estoy furioso!$"

VictoryRoad_3F_Text_CarolinePostBattle::
	.string "Me mostraste lo bueno que\n"
	.string "era yo...$"

VictoryRoad_3F_Text_ColbyIntro::
	.string "¡Solo los elegidos pueden pasar!$"

VictoryRoad_3F_Text_ColbyDefeat::
	.string "¡No lo puedo creer!$"

VictoryRoad_3F_Text_ColbyPostBattle::
	.string "Todos los ENTRENADORES van hacia\n"
	.string "a la LIGA POKéMON.\p"
	.string "No bajes la guardia.$"

VictoryRoad_3F_Text_RayIntro::
	.string "RAY: Juntos, los dos estamos\n"
	.string "destinados a la grandeza!$"

VictoryRoad_3F_Text_RayDefeat::
	.string "RAY: Ludicrous!\n"
	.string "¡No puede ser!$"

VictoryRoad_3F_Text_RayPostBattle::
	.string "RAY: Nos has vencido.\n"
	.string "La grandeza sigue esquiva...$"

VictoryRoad_3F_Text_RayNotEnoughMons::
	.string "RAY: Juntos, los dos estamos\n"
	.string "hacia la cima.\p"
	.string "Necesitamos que traigas dos POKéMON\n"
	.string "a la batalla con nosotros.$"

VictoryRoad_3F_Text_TyraIntro::
	.string "TYRA: Intentamos convertirnos\n"
	.string "en campeones juntos.$"

VictoryRoad_3F_Text_TyraDefeat::
	.string "TYRA: Oh, pero...$"

VictoryRoad_3F_Text_TyraPostBattle::
	.string "TYRA: Me enseñaste que el poder\n"
	.string "puede ser infinito en forma y tipo.$"

VictoryRoad_3F_Text_TyraNotEnoughMons::
	.string "TYRA: No pueden batallar con noso-\n"
	.string "solo tienes un POKéMON.$"

