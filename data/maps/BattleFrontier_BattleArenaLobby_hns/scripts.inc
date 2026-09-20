BattleFrontier_BattleArenaLobby_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleArenaLobby_OnFrame_hns
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleArenaLobby_OnWarp_hns
	.byte 0

BattleFrontier_BattleArenaLobby_OnWarp_hns:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleArenaLobby_EventScript_TurnPlayerNorth_hns
	.2byte 0

BattleFrontier_BattleArenaLobby_EventScript_TurnPlayerNorth_hns::
	setvar VAR_TEMP_1, 1
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleArenaLobby_OnFrame_hns:
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, 0, BattleFrontier_BattleArenaLobby_EventScript_GetChallengeStatus_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING, BattleFrontier_BattleArenaLobby_EventScript_QuitWithoutSaving_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_PAUSED, BattleFrontier_BattleArenaLobby_EventScript_ResumeChallenge_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_WON, BattleFrontier_BattleArenaLobby_EventScript_WonChallenge_hns
	map_script_2 VAR_TEMP_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST, BattleFrontier_BattleArenaLobby_EventScript_LostChallenge_hns
	.2byte 0

BattleFrontier_BattleArenaLobby_EventScript_GetChallengeStatus_hns::
	frontier_getstatus
	end

BattleFrontier_BattleArenaLobby_EventScript_QuitWithoutSaving_hns::
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_DidntSaveBeforeShuttingDown_hns, MSGBOX_DEFAULT
	closemessage
	arena_set ARENA_DATA_WIN_STREAK, 0
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, FALSE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_WonChallenge_hns::
	lockall
	frontier_isbrain
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleArenaLobby_EventScript_DefeatedTycoon_hns
	msgbox BattleFrontier_BattleArenaLobby_Text_CongratsOnSevenWins_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_GiveBattlePoints_hns

BattleFrontier_BattleArenaLobby_EventScript_DefeatedTycoon_hns::
	msgbox BattleFrontier_BattleArenaLobby_Text_CongratsOnDefeatingTycoon_hns, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_GiveBattlePoints_hns::
	msgbox BattleFrontier_BattleArenaLobby_Text_PleaseAcceptBattlePoints_hns, MSGBOX_DEFAULT
	frontier_givepoints
	msgbox BattleFrontier_Text_ObtainedXBattlePoints, MSGBOX_GETPOINTS
	message BattleFrontier_BattleArenaLobby_Text_RecordAchievement_hns
	waitmessage
	call BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge_hns
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge_hns2_hns, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_LostChallenge_hns::
	lockall
	message BattleFrontier_BattleArenaLobby_Text_ThankYouWaitWhileSave_hns
	waitmessage
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, FALSE
	call BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge_hns
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge_hns2_hns, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_SaveAfterChallenge_hns::
	frontier_checkairshow
	special LoadPlayerParty
	special HealPlayerParty
	callnative UpdateFollowingPokemon
	arena_save 0
	playse SE_SAVE
	waitse
	call BattleFrontier_EventScript_GetCantRecordBattle
	goto_if_eq VAR_RESULT, TRUE, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge_hns
	message BattleFrontier_BattleArenaLobby_Text_RecordLastMatch_hns
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge_hns
	case 0, BattleFrontier_BattleArenaLobby_EventScript_RecordMatch_hns
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge_hns

BattleFrontier_BattleArenaLobby_EventScript_RecordMatch_hns::
	call BattleFrontier_EventScript_SaveBattle
BattleFrontier_BattleArenaLobby_EventScript_EndSaveAfterChallenge_hns::
	return

BattleFrontier_BattleArenaLobby_EventScript_ResumeChallenge_hns::
	lockall
	message BattleFrontier_BattleArenaLobby_Text_LookingForwardToArrivalSaveGame_hns
	waitmessage
	arena_save CHALLENGE_STATUS_SAVING
	playse SE_SAVE
	waitse
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto BattleFrontier_BattleArenaLobby_EventScript_EnterChallenge_hns

BattleFrontier_BattleArenaLobby_EventScript_Attendant_hns::
	lock
	faceplayer
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_ARENA
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	special SavePlayerParty
	msgbox BattleFrontier_BattleArenaLobby_Text_WelcomeToBattleArena_hns, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_AskTakeChallenge_hns::
	message BattleFrontier_BattleArenaLobby_Text_WishToTakeChallenge_hns
	waitmessage
	multichoice 17, 6, MULTI_CHALLENGEINFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_TryEnterChallenge_hns
	case 1, BattleFrontier_BattleArenaLobby_EventScript_ExplainChallenge_hns
	case 2, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge_hns

BattleFrontier_BattleArenaLobby_EventScript_TryEnterChallenge_hns::
	message BattleFrontier_BattleArenaLobby_Text_WhichLevelMode_hns
	waitmessage
	multichoice 17, 6, MULTI_LEVEL_MODE, FALSE
	switch VAR_RESULT
	case FRONTIER_LVL_TENT, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge_hns
	frontier_checkineligible
	goto_if_eq VAR_0x8004, TRUE, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons_hns
	frontier_set FRONTIER_DATA_LVL_MODE, VAR_RESULT
	msgbox BattleFrontier_BattleArenaLobby_Text_SelectThreeMons_hns, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	callnative RemoveFollowingPokemon
	call BattleFrontier_EventScript_GetLvlMode
	copyvar VAR_0x8004, VAR_RESULT
	setvar VAR_0x8005, FRONTIER_PARTY_SIZE
	special ChoosePartyForBattleFrontier
	waitstate
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge_hns
	msgbox BattleFrontier_BattleArenaLobby_Text_OkayToSave_hns, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge_hns
	case YES, BattleFrontier_BattleArenaLobby_EventScript_SaveBeforeChallenge_hns
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge_hns

BattleFrontier_BattleArenaLobby_EventScript_SaveBeforeChallenge_hns::
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	frontier_set FRONTIER_DATA_SELECTED_MON_ORDER
	arena_init
	arena_set ARENA_DATA_WIN_STREAK_ACTIVE, TRUE
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_SAVING
	frontier_set FRONTIER_DATA_PAUSED, FALSE
	special LoadPlayerParty
	closemessage
	delay 2
	call Common_EventScript_SaveGame
	setvar VAR_TEMP_CHALLENGE_STATUS, 255
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge_hnsSaveFailed_hns
BattleFrontier_BattleArenaLobby_EventScript_EnterChallenge_hns::
	special SavePlayerParty
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	msgbox BattleFrontier_BattleArenaLobby_Text_GuideYouToArena_hns, MSGBOX_DEFAULT
	closemessage
	frontier_get FRONTIER_DATA_LVL_MODE
	call_if_eq VAR_RESULT, FRONTIER_LVL_50, BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLv50_hns
	call_if_eq VAR_RESULT, FRONTIER_LVL_OPEN, BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLvOpen_hns
	warp MAP_BATTLE_FRONTIER_BATTLE_ARENA_CORRIDOR_HNS, 9, 13
	setvar VAR_TEMP_CHALLENGE_STATUS, 0
	waitstate
	end

BattleFrontier_BattleArenaLobby_EventScript_ExplainChallenge_hns::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainChallenge_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_AskTakeChallenge_hns

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons_hns::
	switch VAR_RESULT
	case FRONTIER_LVL_50, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons_hnsLv50_hns
	case FRONTIER_LVL_OPEN, BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons_hnsLvOpen_hns

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons_hnsLv50_hns::
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLv50_hns, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsEnd_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge_hns

BattleFrontier_BattleArenaLobby_EventScript_NotEnoughValidMons_hnsLvOpen_hns::
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLvOpen_hns, MSGBOX_DEFAULT
	call BattleFrontier_ShowCaughtBannedSpecies
	msgbox BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsEnd_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge_hns

BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge_hnsSaveFailed_hns::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	goto BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge_hns

BattleFrontier_BattleArenaLobby_EventScript_LoadPartyAndCancelChallenge_hns::
	special LoadPlayerParty
	callnative UpdateFollowingPokemon
BattleFrontier_BattleArenaLobby_EventScript_CancelChallenge_hns::
	msgbox BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge_hns, MSGBOX_DEFAULT
BattleFrontier_BattleArenaLobby_EventScript_EndCancelChallenge_hns::
	release
	end

BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLv50_hns::
	applymovement LOCALID_ARENA_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToLeftDoor_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToLeftDoor_hns
	waitmovement 0
	opendoor 2, 2
	waitdooranim
	applymovement LOCALID_ARENA_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor_hns
	waitmovement 0
	closedoor 2, 2
	waitdooranim
	return

BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToLeftDoor_hns:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor_hns:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToLeftDoor_hns:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor_hns:
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleArenaLobby_EventScript_WalkToDoorLvOpen_hns::
	applymovement LOCALID_ARENA_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToRightDoor_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToRightDoor_hns
	waitmovement 0
	opendoor 11, 2
	waitdooranim
	applymovement LOCALID_ARENA_ATTENDANT, BattleFrontier_BattleArenaLobby_Movement_AttendantEnterDoor_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattleArenaLobby_Movement_PlayerEnterDoor_hns
	waitmovement 0
	closedoor 11, 2
	waitdooranim
	return

BattleFrontier_BattleArenaLobby_Movement_AttendantWalkToRightDoor_hns:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	step_end

BattleFrontier_BattleArenaLobby_Movement_PlayerWalkToRightDoor_hns:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

BattleFrontier_BattleArenaLobby_EventScript_ShowResults_hns::
	lockall
	frontier_results FRONTIER_FACILITY_ARENA
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_BattleArenaLobby_EventScript_Youngster_hns::
	msgbox BattleFrontier_BattleArenaLobby_Text_BadIdeaToNotAttack_hns, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Man_hns::
	msgbox BattleFrontier_BattleArenaLobby_Text_LandingHitsWorked_hns, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Camper_hns::
	msgbox BattleFrontier_BattleArenaLobby_Text_MatchWasDeclaredDraw_hns, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_Woman_hns::
	msgbox BattleFrontier_BattleArenaLobby_Text_OrderOfMonsImportant_hns, MSGBOX_NPC
	end

BattleFrontier_BattleArenaLobby_EventScript_RulesBoard_hns::
	lockall
	msgbox BattleFrontier_BattleArenaLobby_Text_RulesAreListed_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard_hns::
	message BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading_hns
	waitmessage
	multichoice 17, 2, MULTI_BATTLE_ARENA_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_BattleArenaLobby_EventScript_BattleRules_hns
	case 1, BattleFrontier_BattleArenaLobby_EventScript_MindRules_hns
	case 2, BattleFrontier_BattleArenaLobby_EventScript_SkillRules_hns
	case 3, BattleFrontier_BattleArenaLobby_EventScript_BodyRules_hns
	case 4, BattleFrontier_BattleArenaLobby_EventScript_ExitRules_hns
	case MULTI_B_PRESSED, BattleFrontier_BattleArenaLobby_EventScript_ExitRules_hns
	end

BattleFrontier_BattleArenaLobby_EventScript_BattleRules_hns::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattleArenaLobby_EventScript_MindRules_hns::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainMindRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattleArenaLobby_EventScript_SkillRules_hns::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattleArenaLobby_EventScript_BodyRules_hns::
	msgbox BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_BattleArenaLobby_EventScript_ReadRulesBoard_hns
	end

BattleFrontier_BattleArenaLobby_EventScript_ExitRules_hns::
	releaseall
	end

BattleFrontier_BattleArenaLobby_Text_WelcomeToBattleArena_hns:
	.string "¡Donde el espíritu de lucha de los\n"
	.string "ENTRENADORES es puesto a prueba!\p"
	.string "¡Bienvenidos a la BATTLE ARENA!\p"
	.string "¡Soy tu guía del Torneo Set KO!$"

BattleFrontier_BattleArenaLobby_Text_WishToTakeChallenge_hns:
	.string "Ahora, ¿deseas aceptar el\n"
	.string "desafío de la BATTLE ARENA?$"

BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge_hns:
	.string "¡Esperaremos tu desafío en\n"
	.string "otra ocasión!$"

BattleFrontier_BattleArenaLobby_Text_ExplainChallenge_hns:
	.string "En la BATTLE ARENA, realizamos\n"
	.string "el Torneo Set KO.\p"
	.string "Todos entran con un equipo de\n"
	.string "tres POKéMON.\p"
	.string "Los tres POKéMON deben alinearse en\n"
	.string "el orden en que deben aparecer.\p"
	.string "En batalla, los POKéMON saldrán\n"
	.string "uno a uno en el orden establecido.\p"
	.string "Cuando un POKéMON entre en batalla,\n"
	.string "quédense fuera hasta que termine.\p"
	.string "Si el duelo no se decide en\n"
	.string "tres turnos, pasará al juzgado.\p"
	.string "Si quieres interrumpir el desafío,\n"
	.string "por favor, guarda la partida.\p"
	.string "Si no guardas, no podrás\n"
	.string "continuar con tu desafío.\p"
	.string "Si logras la hazaña de vencer a\n"
	.string "siete ENTRENADORES seguidos,\l"
	.string "te daremos Puntos de Batalla.$"

BattleFrontier_BattleArenaLobby_Text_OkayToSave_hns:
	.string "Antes de ir a la ARENA DE BATALLA,\n"
	.string "debes guardar. ¿Está bien?$"

BattleFrontier_BattleArenaLobby_Text_WhichLevelMode_hns:
	.string "La ARENA DE BATALLA tiene dos\n"
	.string "niveles: Nivel 50 y Nivel Abierto.\l"
	.string "¿Cuál eliges?$"

BattleFrontier_BattleArenaLobby_Text_SelectThreeMons_hns:
	.string "Muy bien, ahora elige a tus\n"
	.string "tres POKéMON, por favor.$"

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLvOpen_hns:
	.string "¡Mi querido retador!\p"
	.string "No tienes los tres POKéMON\n"
	.string "necesarios para entrar.\p"
	.string "Para calificar, debes traer tres\n"
	.string "tipos distintos de POKéMON.\p"
	.string "Tampoco deben llevar el mismo\n"
	.string "tipo de objeto.\p"
	.string "HUEVOS{STR_VAR_1}.$"

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsEnd_hns:
	.string "Cuando estés preparado,\n"
	.string "por favor, regresa.$"

BattleFrontier_BattleArenaLobby_Text_NotEnoughValidMonsLv50_hns:
	.string "¡Mi querido retador!\p"
	.string "No tienes los tres POKéMON\n"
	.string "necesarios para entrar.\p"
	.string "Para calificar, debes traer tres\n"
	.string "tipos distintos de POKéMON.\p"
	.string "Los tres POKéMON distintos\n"
	.string "deben ser nivel 50 o inferior.\p"
	.string "Tampoco deben llevar el mismo\n"
	.string "tipo de objeto.\p"
	.string "HUEVOS{STR_VAR_1}.$"

BattleFrontier_BattleArenaLobby_Text_GuideYouToArena_hns:
	.string "Ahora te guiaré hacia\n"
	.string "la BATTLE ARENA.$"

BattleFrontier_BattleArenaLobby_Text_DidntSaveBeforeShuttingDown_hns:
	.string "¡Mi querido retador!\p"
	.string "No guardaste la partida antes\n"
	.string "¿Te rendiste, verdad?\p"
	.string "Es lamentable, pero eso ha\n"
	.string "causado tu descalificación\l"
	.string "de tu desafío.\p"
	.string "Puedes, por supuesto, iniciar un\n"
	.string "nuevo desafío.$"

BattleFrontier_BattleArenaLobby_Text_CongratsOnSevenWins_hns:
	.string "¡Te felicitamos por tu espléndida\n"
	.string "¡Racha de siete TRAINERS vencidos!$"

BattleFrontier_BattleArenaLobby_Text_RecordAchievement_hns:
	.string "Tu logro quedará registrado.\n"
	.string "Please wait while I save the game.$"

@ Unused
BattleFrontier_BattleArenaLobby_Text_PresentYouWithPrize_hns:
	.string "Para conmemorar tus 7 victorias,\n"
	.string "te entregamos este premio.$"

@ Unused
BattleFrontier_BattleArenaLobby_Text_ReceivedPrize_hns:
	.string "{PLAYER} recibió el premio\n"
	.string "{STR_VAR_1}.$"

@ Unused
BattleFrontier_BattleArenaLobby_Text_BagFullReturnForPrize_hns:
	.string "Oh?\n"
	.string "Tu MOCHILA parece estar llena.\p"
	.string "Te pido que hagas espacio y\n"
	.string "vuelvas por tu premio.$"

BattleFrontier_BattleArenaLobby_Text_ThankYouWaitWhileSave_hns:
	.string "¡Muchas gracias por participar!\p"
	.string "Please wait while I save the game.$"

BattleFrontier_BattleArenaLobby_Text_AwaitAnotherChallenge_hns2_hns:
	.string "¡Esperaremos tu desafío en\n"
	.string "otra ocasión!$"

BattleFrontier_BattleArenaLobby_Text_LookingForwardToArrivalSaveGame_hns:
	.string "Hemos estado esperando\n"
	.string "tu llegada.\p"
	.string "Antes de ir a la BATTLE ARENA,\n"
	.string "debo guardar la partida.\l"
	.string "Please wait.$"

BattleFrontier_BattleArenaLobby_Text_RecordLastMatch_hns:
	.string "¿Registro tu último combate de la\n"
	.string "BATTLE ARENA en tu FRONTIER PASS?$"

BattleFrontier_BattleArenaLobby_Text_BadIdeaToNotAttack_hns:
	.string "Perdí por decisión del ÁRBITRO...\p"
	.string "No creo que fuera buena idea solo\n"
	.string "usar defensa y no atacar...$"

BattleFrontier_BattleArenaLobby_Text_LandingHitsWorked_hns:
	.string "¡Gané por decisión!\p"
	.string "¡Golpear constantemente al\n"
	.string "POKéMON rival funcionó!$"

BattleFrontier_BattleArenaLobby_Text_MatchWasDeclaredDraw_hns:
	.string "El combate terminó en empate.\p"
	.string "Al acabarse el tiempo, mi\n"
	.string "POKéMON y el del rival tenían\l"
	.string "casi los mismos PS.$"

BattleFrontier_BattleArenaLobby_Text_OrderOfMonsImportant_hns:
	.string "En la ARENA DE COMBATE, el orden\n"
	.string "de los POKéMON es muy importante.\p"
	.string "Por ejemplo, si tu primer POKéMON\n"
	.string "tiene desventajas de tipo,\l"
	.string "intenta que tu segundo POKéMON\l"
	.string "tenga movimientos súper eficaces\l"
	.string "contra el primero.\p"
	.string "Creo que esa es la mejor forma de\n"
	.string "armar un equipo efectivo.$"

BattleFrontier_BattleArenaLobby_Text_RulesAreListed_hns:
	.string "Reglas del Torneo Set KO.$"

BattleFrontier_BattleArenaLobby_Text_ReadWhichHeading_hns:
	.string "¿Qué título quieres leer?$"

BattleFrontier_BattleArenaLobby_Text_ExplainBattleRules_hns:
	.string "El Torneo KO tiene reglas especiales,\n"
	.string "a diferencia de las batallas comunes.\p"
	.string "Primero, una batalla dura solo\n"
	.string "tres turnos.\p"
	.string "Si no hay un resultado después de\n"
	.string "tres turnos, pasará al juzgado.\p"
	.string "el REFEREE elegirá al ganador\n"
	.string "según cómo lucharon los POKéMON.\p"
	.string "Además, no puedes cambiar a un\n"
	.string "POKéMON hasta que termine el duelo.$"

BattleFrontier_BattleArenaLobby_Text_ExplainMindRules_hns:
	.string "El primer factor es la “Mente.”\nEste factor evalúa qué tan\lagresivos\nfueron los luchadores.\pSe juzga según\ncuántas veces\nlos ENTRENADORES ordenaron\nusar\lmovimientos ofensivos.$"

BattleFrontier_BattleArenaLobby_Text_ExplainSkillRules_hns:
	.string "The second judging factor is “Skill.”\n"
	.string "Este factor evalúa qué tan bien\l"
	.string "se usaron los movimientos POKéMON.\p"
	.string "Si un movimiento tuvo éxito,\n"
	.string "la Habilidad sube.\p"
	.string "Si el movimiento falló, la\n"
	.string "Habilidad baja.\p"
	.string "Si fue un ataque, la Habilidad\n"
	.string "Sube si el movimiento fue “muy\l"
	.string "efectivo” y baja si fue\l"
	.string "“not very effective.”\p"
	.string "La Habilidad no subirá si\n"
	.string "movimientos como PROTECT y DETECT.\p"
	.string "Si el rival usó PROTECCIÓN o\n"
	.string "DETECCIÓN, y tu POKéMON falló el\l"
	.string "ataque, su nivel de Habilidad no\l"
	.string "bajará.$"

BattleFrontier_BattleArenaLobby_Text_ExplainBodyRules_hns:
	.string "El tercer factor es “Cuerpo”.\n"
	.string "Se basa en cuántos PS quedaron\l"
	.string "al final de una batalla.\p"
	.string "La calificación considera cuántos\n"
	.string "PS tenía el POKéMON al inicio y\l"
	.string "cuántos quedaron al final.$"

BattleFrontier_BattleArenaLobby_Text_CongratsOnDefeatingTycoon_hns:
	.string "Una victoria lograda en la ARENA\n"
	.string "¡TYCOON, y venciste a 7 ENTRENADORES!\p"
	.string "¡Te felicitamos por tu desafío\n"
	.string "más espléndido!$"

BattleFrontier_BattleArenaLobby_Text_PleaseAcceptBattlePoints_hns:
	.string "Querido retador, en reconocimiento a\n"
	.string "tu espíritu incansable, acepta\l"
	.string "estos Puntos de Batalla.$"
