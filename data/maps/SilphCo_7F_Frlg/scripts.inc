SilphCo_7F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SilphCo_7F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, SilphCo_7F_OnTransition
	.byte 0

SilphCo_7F_OnLoad::
	call_if_unset FLAG_SILPH_7F_DOOR_1, EventScript_Close7FDoor1
	call_if_unset FLAG_SILPH_7F_DOOR_2, EventScript_Close7FDoor2
	call_if_unset FLAG_SILPH_7F_DOOR_3, EventScript_Close7FDoor3
	end

SilphCo_7F_OnTransition::
	call_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_7F_EventScript_SetObjRocketsGone
	end

SilphCo_7F_EventScript_SetObjRocketsGone::
	setobjectmovementtype LOCALID_SILPH_CO_7F_WORKER_M2, MOVEMENT_TYPE_FACE_UP
	return

SilphCo_7F_EventScript_RivalTriggerTop::
	lockall
	setvar VAR_TEMP_1, 0
	goto SilphCo_7F_EventScript_RivalScene
	end

SilphCo_7F_EventScript_RivalTriggerBottom::
	lockall
	setvar VAR_TEMP_1, 1
	goto SilphCo_7F_EventScript_RivalScene
	end

SilphCo_7F_EventScript_RivalScene::
	textcolor NPC_TEXT_COLOR_MALE
	playbgm MUS_RG_ENCOUNTER_RIVAL, 0
	applymovement LOCALID_SILPH_CO_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_SILPH_CO_RIVAL, Common_Movement_Delay48
	waitmovement 0
	msgbox SilphCo_7F_Text_RivalWhatKeptYou
	call_if_eq VAR_TEMP_1, 0, SilphCo_7F_EventScript_RivalApproachTop
	call_if_eq VAR_TEMP_1, 1, SilphCo_7F_EventScript_RivalApproachBottom
	msgbox SilphCo_7F_Text_RivalIntro
	setvar VAR_LAST_TALKED, LOCALID_SILPH_CO_RIVAL
	call_if_eq VAR_STARTER_MON, 2, SilphCo_7F_EventScript_RivalSquirtle
	call_if_eq VAR_STARTER_MON, 1, SilphCo_7F_EventScript_RivalBulbasaur
	call_if_eq VAR_STARTER_MON, 0, SilphCo_7F_EventScript_RivalCharmander
	msgbox SilphCo_7F_Text_RivalPostBattle
	closemessage
	playbgm MUS_RG_RIVAL_EXIT, 0
	call_if_eq VAR_TEMP_1, 0, SilphCo_7F_EventScript_RivalExitTop
	call_if_eq VAR_TEMP_1, 1, SilphCo_7F_EventScript_RivalExitBottom
	playse SE_WARP_IN
	fadedefaultbgm
	removeobject LOCALID_SILPH_CO_RIVAL
	waitse
	setvar VAR_MAP_SCENE_SILPH_CO_7F, 1
	releaseall
	end

SilphCo_7F_EventScript_RivalApproachTop::
	closemessage
	applymovement LOCALID_SILPH_CO_RIVAL, SilphCo_7F_Movement_RivalApproachTop
	waitmovement 0
	return

SilphCo_7F_EventScript_RivalApproachBottom::
	return

SilphCo_7F_EventScript_RivalSquirtle::
	trainerbattle_no_intro TRAINER_RIVAL_SILPH_SQUIRTLE, SilphCo_7F_Text_RivalDefeat
	return

SilphCo_7F_EventScript_RivalBulbasaur::
	trainerbattle_no_intro TRAINER_RIVAL_SILPH_BULBASAUR, SilphCo_7F_Text_RivalDefeat
	return

SilphCo_7F_EventScript_RivalCharmander::
	trainerbattle_no_intro TRAINER_RIVAL_SILPH_CHARMANDER, SilphCo_7F_Text_RivalDefeat
	return

SilphCo_7F_EventScript_RivalExitTop::
	applymovement LOCALID_SILPH_CO_RIVAL, SilphCo_7F_Movement_RivalExitTop
	waitmovement 0
	return

SilphCo_7F_EventScript_RivalExitBottom::
	applymovement LOCALID_SILPH_CO_RIVAL, SilphCo_7F_Movement_RivalExitBottom
	waitmovement 0
	return

SilphCo_7F_Movement_RivalApproachTop::
	walk_up
	step_end

SilphCo_7F_Movement_RivalExitTop::
	walk_right
	walk_right
	walk_right
	walk_up
	delay_16
	step_end

SilphCo_7F_Movement_RivalExitBottom::
	walk_left
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	delay_16
	step_end

SilphCo_7F_EventScript_LaprasGuy::
	lock
	faceplayer
	goto_if_set FLAG_GOT_LAPRAS_FROM_SILPH, SilphCo_7F_EventScript_AlreadyGotLapras
	msgbox SilphCo_7F_Text_HaveMonForSavingUs
	setvar VAR_TEMP_1, SPECIES_LAPRAS
	givemon SPECIES_LAPRAS, 25
	goto_if_eq VAR_RESULT, 0, SilphCo_7F_EventScript_ReceiveLaprasParty
	goto_if_eq VAR_RESULT, 1, SilphCo_7F_EventScript_ReceiveLaprasPC
	goto_if_eq VAR_RESULT, 2, Common_EventScript_NoMoreRoomForPokemon
	release
	end

SilphCo_7F_EventScript_ReceiveLaprasParty::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	playfanfare MUS_LEVEL_UP
	message SilphCo_7F_Text_ObtainedLaprasFromEmployee
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_LAPRAS
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SilphCo_7F_EventScript_EndReceiveLapras
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto SilphCo_7F_EventScript_EndReceiveLapras
	end

SilphCo_7F_EventScript_ReceiveLaprasPC::
	textcolor NPC_TEXT_COLOR_NEUTRAL
	playfanfare MUS_LEVEL_UP
	message SilphCo_7F_Text_ObtainedLaprasFromEmployee
	waitmessage
	waitfanfare
	bufferspeciesname STR_VAR_1, SPECIES_LAPRAS
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SilphCo_7F_EventScript_LaprasTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto SilphCo_7F_EventScript_LaprasTransferredToPC
	end

SilphCo_7F_EventScript_LaprasTransferredToPC::
	call Common_EventScript_TransferredToPC
	goto SilphCo_7F_EventScript_EndReceiveLapras
	end

SilphCo_7F_EventScript_EndReceiveLapras::
	textcolor NPC_TEXT_COLOR_MALE
	msgbox SilphCo_7F_Text_ExplainLapras
	setflag FLAG_GOT_LAPRAS_FROM_SILPH
	release
	end

SilphCo_7F_EventScript_AlreadyGotLapras::
	msgbox SilphCo_7F_Text_RocketBossWentToBoardroom
	release
	end

SilphCo_7F_EventScript_WorkerM1::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_7F_EventScript_WorkerM1RocketsGone
	msgbox SilphCo_7F_Text_RocketsAfterMasterBall
	release
	end

SilphCo_7F_EventScript_WorkerM1RocketsGone::
	msgbox SilphCo_7F_Text_CanceledMasterBallProject
	release
	end

SilphCo_7F_EventScript_WorkerM2::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_7F_EventScript_WorkerM2RocketsGone
	msgbox SilphCo_7F_Text_BadIfTeamRocketTookOver
	release
	end

SilphCo_7F_EventScript_WorkerM2RocketsGone::
	msgbox SilphCo_7F_Text_WowYouChasedOffTeamRocket
	release
	end

SilphCo_7F_EventScript_WorkerF::
	lock
	faceplayer
	goto_if_ge VAR_MAP_SCENE_SILPH_CO_11F, 1, SilphCo_7F_EventScript_WorkerFRocketsGone
	msgbox SilphCo_7F_Text_ReallyDangerousHere
	release
	end

SilphCo_7F_EventScript_WorkerFRocketsGone::
	msgbox SilphCo_7F_Text_ThankYouSoMuch
	release
	end

SilphCo_7F_EventScript_FloorSign::
	msgbox SilphCo_7F_Text_FloorSign, MSGBOX_SIGN
	end

SilphCo_7F_EventScript_Joshua::
	trainerbattle_single TRAINER_SCIENTIST_JOSHUA, SilphCo_7F_Text_JoshuaIntro, SilphCo_7F_Text_JoshuaDefeat
	msgbox SilphCo_7F_Text_JoshuaPostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_7F_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_33, SilphCo_7F_Text_Grunt1Intro, SilphCo_7F_Text_Grunt1Defeat
	msgbox SilphCo_7F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_7F_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_34, SilphCo_7F_Text_Grunt2Intro, SilphCo_7F_Text_Grunt2Defeat
	msgbox SilphCo_7F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_7F_EventScript_Grunt3::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_35, SilphCo_7F_Text_Grunt3Intro, SilphCo_7F_Text_Grunt3Defeat
	msgbox SilphCo_7F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

SilphCo_7F_Text_HaveMonForSavingUs::
	.string "¡Oh! ¡Hola! ¡No eres un ROCKET!\n"
	.string "¿Viniste a salvarnos?\l"
	.string "¡Oh, gracias!\p"
	.string "Quiero que te lleves este POKéMON\n"
	.string "por salvarnos.$"

SilphCo_7F_Text_ObtainedLaprasFromEmployee::
	.string "{PLAYER} obtuvo un LAPRAS de\n"
	.string "¡un empleado de SILPH!$"

SilphCo_7F_Text_ExplainLapras::
	.string "Es un LAPRAS.\n"
	.string "Es un POKéMON muy inteligente.\p"
	.string "Lo mantuvimos en nuestro laboratorio,\n"
	.string "pero estará mejor contigo.\p"
	.string "Creo que serás un buen\n"
	.string "ENTRENADOR para LAPRAS!\p"
	.string "Es un buen nadador.\n"
	.string "¡Te llevará por el agua!$"

SilphCo_7F_Text_RocketBossWentToBoardroom::
	.string "El JEFE del EQUIPO ROCKET fue al\n"
	.string "¡sala de juntas!\p"
	.string "¿Está bien nuestro PRESIDENTE?\n"
	.string "Estoy preocupado.$"

SilphCo_7F_Text_RocketsAfterMasterBall::
	.string "El EQUIPO ROCKET buscaba al\nMAESTRO"
	.string "BALL, que atrapa cualquier POKéMON.$"

SilphCo_7F_Text_CanceledMasterBallProject::
	.string "Cancelamos el proyecto de la\nMASTER BALL"
	.string "por culpa del EQUIPO ROCKET.$"

SilphCo_7F_Text_BadIfTeamRocketTookOver::
	.string "Sería malo si el EQUIPO ROCKET\n"
	.string "se apoderara de SILPH o de nuestros POKéMON.$"

SilphCo_7F_Text_WowYouChasedOffTeamRocket::
	.string "¡Guau!\p"
	.string "Ahuyentaste al EQUIPO ROCKET tú\n"
	.string "solo?$"

SilphCo_7F_Text_ReallyDangerousHere::
	.string "¡Tú!\n"
	.string "¡Aquí es muy peligroso!\p"
	.string "¿Viniste a rescatarme?\n"
	.string "¡No puedes!$"

SilphCo_7F_Text_ThankYouSoMuch::
	.string "¡Muchas gracias!$"

SilphCo_7F_Text_Grunt3Intro::
	.string "Uh-oh!\n"
	.string "¡Huelo a un ratoncito!$"

SilphCo_7F_Text_Grunt3Defeat::
	.string "¡Luces fuera!$"

SilphCo_7F_Text_Grunt3PostBattle::
	.string "No encontrarás a mi JEFE solo\n"
	.string "¡correteando!$"

SilphCo_7F_Text_JoshuaIntro::
	.string "Heheh!\p"
	.string "¿Me confundiste con un empleado de SILPH?$"

SilphCo_7F_Text_JoshuaDefeat::
	.string "¡Estoy acabado!$"

SilphCo_7F_Text_JoshuaPostBattle::
	.string "A pesar de tu edad, eres un\n"
	.string "¡ENTRENADOR hábil!$"

SilphCo_7F_Text_Grunt1Intro::
	.string "Soy uno de los cuatro ROCKET\n"
	.string "BROTHERS!$"

SilphCo_7F_Text_Grunt1Defeat::
	.string "Aack!\n"
	.string "¡Hermanos, perdí!$"

SilphCo_7F_Text_Grunt1PostBattle::
	.string "No importa.\n"
	.string "¡Mis hermanos pagarán el favor!$"

SilphCo_7F_Text_Grunt2Intro::
	.string "¿Un niño intruso?\n"
	.string "¡Debes ser tú!$"

SilphCo_7F_Text_Grunt2Defeat::
	.string "¡Bien!\n"
	.string "¡Perdí!$"

SilphCo_7F_Text_Grunt2PostBattle::
	.string "Vete a casa antes de que mi JEFE\n"
	.string "¡se enfade!$"

SilphCo_7F_Text_RivalWhatKeptYou::
	.string "{RIVAL}: ¿Qué te retrasó, {PLAYER}?$"

SilphCo_7F_Text_RivalIntro::
	.string "{RIVAL}: ¡Jaja! Sabía que\n"
	.string "¡que aparecería si esperaba aquí!\p"
	.string "¡Supongo que el EQUIPO ROCKET te\n"
	.string "retrasó! ¡No es que me importe!\p"
	.string "Te vi en AZULONA, así que decidí\n"
	.string "ver si habías mejorado!$"

SilphCo_7F_Text_RivalDefeat::
	.string "¡Oh, hermano!\n"
	.string "Así que ya estás listo para el\l"
	.string "ROCKET!$"

SilphCo_7F_Text_RivalPostBattle::
	.string "Bueno, {PLAYER}!\n"
	.string "¡Voy subiendo y avanzando!\p"
	.string "Al revisar mi POKéDEX,\n"
	.string "empiezo a ver qué es fuerte y\l"
	.string "¡cómo evolucionan!\p"
	.string "¿Soy un genio o qué?\p"
	.string "Voy a la LIGA POKéMON para\n"
	.string "vencer al ALTO MANDO.\p"
	.string "Seré el más fuerte del mundo\n"
	.string "¡un ENTRENADOR poderoso!\p"
	.string "{PLAYER}, ¡buena suerte!\n"
	.string "¡No te preocupes!\l"
	.string "¡Hasta luego!$"

SilphCo_7F_Text_FloorSign::
	.string "SILPH CO. HEAD OFFICE\n"
	.string "7F$"

