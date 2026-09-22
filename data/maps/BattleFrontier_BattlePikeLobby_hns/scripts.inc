BattleFrontier_BattlePikeLobby_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePikeLobby_OnFrame_hns
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePikeLobby_OnWarp_hns
	.byte 0

BattleFrontier_BattlePikeLobby_OnFrame_hns:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattlePikeLobby_EventScript_GetChallengeStatus_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePikeLobby_EventScript_QuitWithoutSaving_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattlePikeLobby_EventScript_WonChallenge_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattlePikeLobby_EventScript_LostChallenge_hns
	.2byte 0

BattleFrontier_BattlePikeLobby_OnWarp_hns:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattlePikeLobby_EventScript_TurnPlayerNorth_hns
	.2byte 0

BattleFrontier_BattlePikeLobby_EventScript_TurnPlayerNorth_hns::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattlePikeLobby_EventScript_GetChallengeStatus_hns::
	frontier_getstatus
	end

BattleFrontier_BattlePikeLobby_EventScript_QuitWithoutSaving_hns::
	special HealPlayerParty
	pike_resethelditems
	lockall
	msgbox BattleFrontier_BattlePikeLobby_Text_FailedToSaveBeforeQuitting_hns, MSGBOX_DEFAULT
	closemessage
	pike_set PIKE_DATA_WIN_STREAK, 0
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_WonChallenge_hns::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattlePikeLobby_EventScript_DefeatedQueen_hns
	msgbox BattleFrontier_BattlePikeLobby_Text_PossessLuckInAbundance_hns, MSGBOX_DEFAULT
	waitmessage
	goto BattleFrontier_BattlePikeLobby_EventScript_GiveBattlePoints_hns

BattleFrontier_BattlePikeLobby_EventScript_DefeatedQueen_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_SnatchedVictoryFromQueen_hns, MSGBOX_DEFAULT
	waitmessage
BattleFrontier_BattlePikeLobby_EventScript_GiveBattlePoints_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints_hns, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	frontier_checkairshow
	pike_get PIKE_DATA_TOTAL_STREAKS
	addvar VAR_RESULT, 1
	pike_set PIKE_DATA_TOTAL_STREAKS, VAR_RESULT
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	pike_resethelditems
	message BattleFrontier_BattlePikeLobby_Text_ShallRecordResults_hns
	waitmessage
	pike_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou_hns, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_LostChallenge_hns::
	lockall
	message BattleFrontier_BattlePikeLobby_Text_ChallengeEndedRecordResults_hns
	waitmessage
	frontier_checkairshow
	frontier_set FRONTIER_DATA_BATTLE_NUM, 0
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, FALSE
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	pike_resethelditems
	pike_save 0
	playse SE_SAVE
	waitse
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou_hns, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_Attendant_hns::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_PIKE
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattlePikeLobby_Text_WelcomeToBattlePike_hns, MSGBOX_DEFAULT
BattleFrontier_BattlePikeLobby_EventScript_AskTakeChallenge_hns::
	message BattleFrontier_BattlePikeLobby_Text_TakeChallenge_hns
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeLobby_EventScript_TryEnterChallenge_hns
	case 1, BattleFrontier_BattlePikeLobby_EventScript_ExplainChallenge_hns
	case 2, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge_hns

BattleFrontier_BattlePikeLobby_EventScript_TryEnterChallenge_hns::
	message BattleFrontier_BattlePikeLobby_Text_WhichChallengeMode_hns
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge_hns
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons_hns
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattlePikeLobby_Text_PleaseChooseThreeMons_hns, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge_hns
	msgbox BattleFrontier_BattlePikeLobby_Text_SaveBeforeChallenge_hns, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge_hns
	case YES, BattleFrontier_BattlePikeLobby_EventScript_SaveBeforeChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge_hns

BattleFrontier_BattlePikeLobby_EventScript_SaveBeforeChallenge_hns::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_1, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	pike_init
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	pike_set PIKE_DATA_WIN_STREAK_ACTIVE, TRUE
	pike_savehelditems
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	pike_savehelditems
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge_hnsSaveFailed_hns
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattlePikeLobby_Text_StepThisWay_hns, MSGBOX_DEFAULT
	closemessage
	frontier_settrainers
	call BattleFrontier_BattlePikeLobby_EventScript_WalkToCorridor_hns
	special HealPlayerParty
	call BattleFrontier_BattlePike_EventScript_CloseCurtain_hns
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PIKE_CORRIDOR_HNS, 6, 7
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattlePikeLobby_EventScript_ExplainChallenge_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainBattlePike_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_AskTakeChallenge_hns

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons_hns::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons_hnsLv50_hns
	case FRONTIER_LVL_OPEN, BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons_hnsLvOpen_hns

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons_hnsLv50_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLv50_hns, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsEnd_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge_hns

BattleFrontier_BattlePikeLobby_EventScript_NotEnoughValidMons_hnsLvOpen_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLvOpen_hns, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsEnd_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge_hns

BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge_hnsSaveFailed_hns::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge_hns

BattleFrontier_BattlePikeLobby_EventScript_LoadPartyAndCancelChallenge_hns::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattlePikeLobby_EventScript_CancelChallenge_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou_hns, MSGBOX_DEFAULT
BattleFrontier_BattlePikeLobby_EventScript_EndCancelChallenge_hns::
	release
	end

BattleFrontier_BattlePikeLobby_EventScript_ShowResults_hns::
	lockall
	frontier_results FRONTIER_FACILITY_PIKE
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattlePikeLobby_EventScript_WalkToCorridor_hns::
	applymovement LOCALID_PIKE_LOBBY_ATTENDANT, BattleFrontier_BattlePikeLobby_Movement_AttendantWalkToCorridor_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePikeLobby_Movement_PlayerWalkToCorridor_hns
	waitmovement 0
	return

BattleFrontier_BattlePikeLobby_Movement_PlayerWalkToCorridor_hns:
	walk_up
BattleFrontier_BattlePikeLobby_Movement_AttendantWalkToCorridor_hns:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePikeLobby_EventScript_Hiker_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_OneRoomAwayFromGoal_hns, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_Twin_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_NeverHadToBattleTrainer_hns, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_Beauty_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_ThinkAbilitiesUsefulHere_hns, MSGBOX_NPC
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesBoard_hns::
	lockall
	msgbox BattleFrontier_BattlePikeLobby_Text_RulesAreListed_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard_hns::
	message BattleFrontier_BattlePikeLobby_Text_ReadWhichHeading_hns
	waitmessage
	multichoice 16, 4, MULTI_BATTLE_PIKE_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeLobby_EventScript_RulesPokenavBag_hns
	case 1, BattleFrontier_BattlePikeLobby_EventScript_RulesHeldItems_hns
	case 2, BattleFrontier_BattlePikeLobby_EventScript_RulesMonOrder_hns
	case 3, BattleFrontier_BattlePikeLobby_EventScript_ExitRules_hns
	case MULTI_B_PRESSED, BattleFrontier_BattlePikeLobby_EventScript_ExitRules_hns
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesPokenavBag_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainPokenavBagRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesHeldItems_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainHeldItemRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePikeLobby_EventScript_RulesMonOrder_hns::
	msgbox BattleFrontier_BattlePikeLobby_Text_ExplainMonOrderRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattlePikeLobby_EventScript_ExitRules_hns::
	releaseall
	end

BattleFrontier_BattlePike_EventScript_CloseCurtain_hns::
	playse SE_PIKE_CURTAIN_CLOSE
	special CloseBattlePikeCurtain
	waitstate
	waitse
	return

BattleFrontier_BattlePikeLobby_Text_WelcomeToBattlePike_hns:
	.string "Donde la suerte de los ENTRENADORES\n"
	.string "se pone a prueba...\p"
	.string "Bienvenido al BATTLE PIKE...\p"
	.string "Soy tu guía del BATTLE PIKE...$"

BattleFrontier_BattlePikeLobby_Text_TakeChallenge_hns:
	.string "¿Te gustaría aceptar el desafío\n"
	.string "¿Reto de elección?$"

BattleFrontier_BattlePikeLobby_Text_ExplainBattlePike_hns:
	.string "Aquí hacemos un evento llamado\n"
	.string "la Elección de Batalla.\p"
	.string "Las reglas de la Elección de Batalla\n"
	.string "son muy simples...\p"
	.string "Elige uno de tres caminos y llega\n"
	.string "a la sala final al terminar el\l"
	.string "BATTLE PIKE. Así de simple.\p"
	.string "Pero lo que pase en el camino\n"
	.string "elegido dependerá totalmente de\l"
	.string "la suerte del retador…\p"
	.string "Si llegas a la meta, recibirás\n"
	.string "Puntos de Batalla como premio.\p"
	.string "Si quieres interrumpir tu\n"
	.string "Para el reto, habla con nuestro\l"
	.string "personal en las salas del camino.\p"
	.string "Si no guardas antes de interrumpir,\n"
	.string "quedarás descalificado.$"

BattleFrontier_BattlePikeLobby_Text_LookForwardToSeeingYou_hns:
	.string "Esperamos verte por aquí\n"
	.string "en otra ocasión…$"

BattleFrontier_BattlePikeLobby_Text_WhichChallengeMode_hns:
	.string "Puedes elegir entre dos rutas,\n"
	.string "Nivel 50 y Nivel Abierto.\l"
	.string "¿Cuál quieres retar?$"

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLv50_hns:
	.string "Perdona, pero…\p"
	.string "No tienes tres POKéMON aptos\n"
	.string "para el evento Battle Choice.\p"
	.string "Debes tener tres POKéMON distintos\n"
	.string "de nivel 50 o menos para entrar.\p"
	.string "También deben llevar objetos\n"
	.string "tipo de objeto.\p"
	.string "HUEVOS{STR_VAR_1}.$"

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsEnd_hns:
	.string "Vuelve a verme cuando\n"
	.string "estés listo…$"

BattleFrontier_BattlePikeLobby_Text_NotEnoughValidMonsLvOpen_hns:
	.string "Perdona, pero…\p"
	.string "No tienes tres POKéMON aptos\n"
	.string "para el evento Battle Choice.\p"
	.string "Debes tener tres POKéMON\n"
	.string "distintos para entrar.\p"
	.string "También deben llevar objetos\n"
	.string "tipo de objeto.\p"
	.string "HUEVOS{STR_VAR_1}.$"

BattleFrontier_BattlePikeLobby_Text_PleaseChooseThreeMons_hns:
	.string "Elige los tres POKéMON que\n"
	.string "quieras usar en el desafío…$"

BattleFrontier_BattlePikeLobby_Text_SaveBeforeChallenge_hns:
	.string "Antes de iniciar el desafío\n"
	.string "Battle Choice, debo guardar.\l"
	.string "¿Te parece bien?$"

BattleFrontier_BattlePikeLobby_Text_StepThisWay_hns:
	.string "Pase por aquí, por favor…$"

BattleFrontier_BattlePikeLobby_Text_ChallengeEndedRecordResults_hns:
	.string "Tu desafío ha terminado…\p"
	.string "Registraré tus resultados.\n"
	.string "Espera, por favor…$"

BattleFrontier_BattlePikeLobby_Text_PossessLuckInAbundance_hns:
	.string "Completaste el desafío…\p"
	.string "Debo decir que pareces tener mucha\n"
	.string "suerte…$"

BattleFrontier_BattlePikeLobby_Text_ShallRecordResults_hns:
	.string "Registraré tus resultados.\n"
	.string "Espera, por favor…$"

@ Unused
BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints_hns2_hns:
	.string "Para conmemorar que completaste el\n"
	.string "desafío de Elección de Batalla,\l"
	.string "te damos estos Puntos de Batalla…$"

@ Unused
BattleFrontier_BattlePikeLobby_Text_ReachedBattlePointLimit_hns:
	.string "Parece que has alcanzado el límite\n"
	.string "de Puntos de Batalla…\p"
	.string "Por favor, canjea algunos puntos\n"
	.string "por premios, luego vuelve…$"

BattleFrontier_BattlePikeLobby_Text_FailedToSaveBeforeQuitting_hns:
	.string "Perdona, pero…\p"
	.string "No guardaste antes de salir\n"
	.string "tu desafío la última vez.\p"
	.string "Por eso, tu progreso hasta ahora\n"
	.string "ha sido descalificado. Lo siento…$"

BattleFrontier_BattlePikeLobby_Text_SnatchedVictoryFromQueen_hns:
	.string "Felicidades…\p"
	.string "Le has robado la victoria a la\n"
	.string "REINA CARPA y ganaste el evento…$"

BattleFrontier_BattlePikeLobby_Text_AwardYouTheseBattlePoints_hns:
	.string "Por tu increíble suerte,\n"
	.string "te damos estos Puntos de Batalla…$"

BattleFrontier_BattlePikeLobby_Text_OneRoomAwayFromGoal_hns:
	.string "¡Arggh! ¡Perdí mi oportunidad!\n"
	.string "¡Estaba a una sala de la meta!\p"
	.string "En este lugar, mejor ten cuidado\n"
	.string "con el veneno, congelación y más.$"

BattleFrontier_BattlePikeLobby_Text_NeverHadToBattleTrainer_hns:
	.string "He completado el reto 10 veces\n"
	.string "ya, pero nunca tuve que luchar\l"
	.string "contra un ENTRENADOR.$"

BattleFrontier_BattlePikeLobby_Text_ThinkAbilitiesUsefulHere_hns:
	.string "¡Escucha! ¡Escucha!\p"
	.string "¿No crees que las habilidades\n"
	.string "especiales de los POKéMON serán\l"
	.string "útiles aquí?$"

@ Unused
BattleFrontier_BattlePikeLobby_Text_TrainersWhicheverPathIChoose_hns:
	.string "¿Qué es este lugar tan raro?\n"
	.string "¡No logro entenderlo!\p"
	.string "He hecho el reto muchas veces,\n"
	.string "pero siempre me topo con\l"
	.string "ENTRENADORES en cualquier ruta.$"

BattleFrontier_BattlePikeLobby_Text_RulesAreListed_hns:
	.string "Las reglas de Battle Choice se listan.$"

BattleFrontier_BattlePikeLobby_Text_ReadWhichHeading_hns:
	.string "¿Qué título quieres leer?$"

BattleFrontier_BattlePikeLobby_Text_ExplainPokenavBagRules_hns:
	.string "No se pueden usar la MOCHILA ni el\n"
	.string "POKéNAV en un reto Battle Choice.$"

BattleFrontier_BattlePikeLobby_Text_ExplainHeldItemRules_hns:
	.string "En un reto de Battle Choice,\n"
	.string "cualquier BAYA o hierba que lleve\l"
	.string "el POKéMON solo servirá una vez.$"

BattleFrontier_BattlePikeLobby_Text_ExplainMonOrderRules_hns:
	.string "En un reto de Battle Choice,\n"
	.string "El orden de los POKéMON no puede\l"
	.string "cambiarse.\p"
	.string "El orden debe fijarse antes de\n"
	.string "empezar el reto.$"

