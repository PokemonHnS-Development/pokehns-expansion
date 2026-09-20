VictoryRoad_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, VictoryRoad_1F_OnTransition
	.byte 0

VictoryRoad_1F_OnTransition:
	call_if_eq VAR_VICTORY_ROAD_1F_STATE, 1, VictoryRoad_1F_EventScript_SetEntranceWallyPos1
	call_if_eq VAR_VICTORY_ROAD_1F_STATE, 2, VictoryRoad_1F_EventScript_SetEntranceWallyPos2
	end

VictoryRoad_1F_EventScript_SetEntranceWallyPos1::
	setobjectxyperm LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, 2, 24
	setobjectmovementtype LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_SetEntranceWallyPos2::
	setobjectxyperm LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, 3, 24
	setobjectmovementtype LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, MOVEMENT_TYPE_FACE_DOWN
	return

VictoryRoad_1F_EventScript_WallyBattleTrigger1::
	lockall
	setvar VAR_0x8008, 1
	addobject LOCALID_VICTORY_ROAD_ENTRANCE_WALLY
	applymovement LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, VictoryRoad_1F_Movement_WallyApproachPlayer1
	waitmovement 0
	goto VictoryRoad_1F_EventScript_WallyEntranceBattle
	end

VictoryRoad_1F_EventScript_WallyBattleTrigger2::
	lockall
	setvar VAR_0x8008, 2
	addobject LOCALID_VICTORY_ROAD_ENTRANCE_WALLY
	applymovement LOCALID_VICTORY_ROAD_ENTRANCE_WALLY, VictoryRoad_1F_Movement_WallyApproachPlayer2
	waitmovement 0
	goto VictoryRoad_1F_EventScript_WallyEntranceBattle
	end

VictoryRoad_1F_EventScript_WallyEntranceBattle::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLY_VR_1, VictoryRoad_1F_Text_WallyEntranceDefeat
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_DEFAULT
	clearflag FLAG_HIDE_VICTORY_ROAD_ENTRANCE_WALLY
	copyobjectxytoperm LOCALID_VICTORY_ROAD_ENTRANCE_WALLY
	setflag FLAG_DEFEATED_WALLY_VICTORY_ROAD
	copyvar VAR_VICTORY_ROAD_1F_STATE, VAR_0x8008
	releaseall
	end

VictoryRoad_1F_Movement_WallyApproachPlayer1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

VictoryRoad_1F_Movement_WallyApproachPlayer2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

@ This Wally appears near the entrance once his battle is triggered and remains there until the Hall of Fame is entered
VictoryRoad_1F_EventScript_EntranceWally::
	msgbox VictoryRoad_1F_Text_WallyPostEntranceBattle, MSGBOX_NPC
	end

@ This Wally appears and remains at the exit after the Hall of Fame is entered
VictoryRoad_1F_EventScript_ExitWally::
	trainerbattle_single TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, VictoryRoad_1F_EventScript_RematchWally
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_RematchWally::
	trainerbattle_rematch TRAINER_WALLY_VR_2, VictoryRoad_1F_Text_WallyIntro, VictoryRoad_1F_Text_WallyDefeat
	msgbox VictoryRoad_1F_Text_WallyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Edgar::
	trainerbattle_single TRAINER_EDGAR, VictoryRoad_1F_Text_EdgarIntro, VictoryRoad_1F_Text_EdgarDefeat
	msgbox VictoryRoad_1F_Text_EdgarPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Albert::
	trainerbattle_single TRAINER_ALBERT, VictoryRoad_1F_Text_AlbertIntro, VictoryRoad_1F_Text_AlbertDefeat
	msgbox VictoryRoad_1F_Text_AlbertPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Hope::
	trainerbattle_single TRAINER_HOPE, VictoryRoad_1F_Text_HopeIntro, VictoryRoad_1F_Text_HopeDefeat
	msgbox VictoryRoad_1F_Text_HopePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Quincy::
	trainerbattle_single TRAINER_QUINCY, VictoryRoad_1F_Text_QuincyIntro, VictoryRoad_1F_Text_QuincyDefeat
	msgbox VictoryRoad_1F_Text_QuincyPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_EventScript_Katelynn::
	trainerbattle_single TRAINER_KATELYNN, VictoryRoad_1F_Text_KatelynnIntro, VictoryRoad_1F_Text_KatelynnDefeat
	msgbox VictoryRoad_1F_Text_KatelynnPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_1F_Text_WallyNotGoingToLoseAnymore:
	.string "WALLY: ¡Hola, {PLAYER}!\p"
	.string "¡Seguro que te sorprende verme!\p"
	.string "Llegué hasta aquí, y todo es\n"
	.string "gracias a ti!\p"
	.string "{PLAYER}, perder contra ti aquella vez\n"
	.string "¡me hizo más fuerte!\p"
	.string "¡Pero ya no voy a perder!\p"
	.string "¡Voy a ganar! ¡Por los POKéMON que\n"
	.string "me dieron valor y fuerza!\p"
	.string "Bien... ¡Aquí voy!$"

VictoryRoad_1F_Text_WallyEntranceDefeat:
	.string "¡Guau!\n"
	.string "{PLAYER}, ¡eres muy fuerte!$"

VictoryRoad_1F_Text_WallyPostEntranceBattle:
	.string "WALLY: No pude vencerte hoy,\n"
	.string "{PLAYER}, ¡pero algún día lo haré!\l"
	.string "¡alcanzarte!$"

VictoryRoad_1F_Text_WallyIntro:
	.string "WALLY: ¡Hola, {PLAYER}!\p"
	.string "Me he vuelto más fuerte desde la\n"
	.string "última vez! ¡Quería mostrarlo, {PLAYER}!\p"
	.string "Bien... ¡Aquí voy!$"

VictoryRoad_1F_Text_WallyDefeat:
	.string "¡Guau!\n"
	.string "{PLAYER}, ¡eres muy fuerte!$"

VictoryRoad_1F_Text_WallyPostBattle:
	.string "WALLY: No pude ganarte esta vez\n"
	.string "tampoco... Pero algún día, {PLAYER},\l"
	.string "voy a alcanzarte...\p"
	.string "¡Y desafiaré la LIGA POKéMON!$"

VictoryRoad_1F_Text_EdgarIntro:
	.string "He llegado hasta aquí un par de veces,\n"
	.string "pero el tramo final es muy largo...$"

VictoryRoad_1F_Text_EdgarDefeat:
	.string "My dream ends here again…$"

VictoryRoad_1F_Text_EdgarPostBattle:
	.string "Tú has llegado hasta aquí. Sigue\n"
	.string "así y conviértete en el\l"
	.string "¡CAMPEÓN! ¡Si alguien puede, eres tú!$"

VictoryRoad_1F_Text_AlbertIntro:
	.string "No vine hasta aquí para perder ahora.\n"
	.string "¡Esa posibilidad no existe!$"

VictoryRoad_1F_Text_AlbertDefeat:
	.string "Imposible...\n"
	.string "¿Perdí?$"

VictoryRoad_1F_Text_AlbertPostBattle:
	.string "Perdí aquí...\p"
	.string "Eso significa que no estoy calificado\n"
	.string "para ser el CAMPEÓN...$"

VictoryRoad_1F_Text_HopeIntro:
	.string "Este camino duro y casi infinito\n"
	.string "hace honor a su nombre de VICTORIA.$"

VictoryRoad_1F_Text_HopeDefeat:
	.string "Tu estilo de combate es fantástico…$"

VictoryRoad_1F_Text_HopePostBattle:
	.string "Pareces tener el potencial para\n"
	.string "convertirse en el CAMPEÓN.$"

VictoryRoad_1F_Text_QuincyIntro:
	.string "¿Qué es la VÍA TRIUNFO?\n"
	.string "¡Te lo diré si ganas!$"

VictoryRoad_1F_Text_QuincyDefeat:
	.string "¡Está bien!\n"
	.string "¡Bien hecho!$"

VictoryRoad_1F_Text_QuincyPostBattle:
	.string "Pasar por aquí a salvo es la\n"
	.string "the final test for any TRAINER aiming\l"
	.string "ser el CAMPEÓN POKéMON.\p"
	.string "Por eso se llama la VÍA\n"
	.string "TRIUNFO.$"

VictoryRoad_1F_Text_KatelynnIntro:
	.string "No tengo nada que decir a quien\n"
	.string "ha llegado tan lejos. ¡Ven!$"

VictoryRoad_1F_Text_KatelynnDefeat:
	.string "Esto es una vergüenza…$"

VictoryRoad_1F_Text_KatelynnPostBattle:
	.string "Hmph, sigue adelante.\n"
	.string "Como si me importara.$"
