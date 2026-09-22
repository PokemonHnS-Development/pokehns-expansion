AzaleaTown_KurtsHouse_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AzaleaTown_KurtsHouse_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, AzaleaTown_KurtsHouse_OnTransition
	.byte 0

AzaleaTown_KurtsHouse_OnTransition::
	goto_if_eq VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_ReturnFromWellSetup
	end

AzaleaTown_KurtsHouse_OnFrame::
	map_script_2 VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_ReturnFromWell
	.2byte 0

AzaleaTown_KurtsHouse_EventScript_KurtBefore::
	lock
	faceplayer
	msgbox KurtsHouse_Text_KurtMakingBallsMustWait, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_NORTH, AzaleaTown_KurtsHouse_EventScript_PlayerMove
	applymovement LOCALID_AZALEA_TOWN_KURT_BEFORE, AzaleaTown_KurtsHouse_Movement_KurtWalkDown
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_AZALEA_TOWN_KURT_BEFORE
	setflag FLAG_HIDE_KURT_1
	setflag FLAG_HIDE_AZALEA_TOWN_WELL_ROCKET
	setvar VAR_AZALEA_TOWN_STATE, 2
	release
	end

AzaleaTown_KurtsHouse_EventScript_PlayerMove::
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTown_KurtsHouse_Movement_Player
	waitmovement 0
	applymovement LOCALID_AZALEA_TOWN_KURT_BEFORE, AzaleaTown_KurtsHouse_Movement_KurtWalkDown
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_AZALEA_TOWN_KURT_BEFORE
	setflag FLAG_HIDE_KURT_1
	setflag FLAG_HIDE_AZALEA_TOWN_WELL_ROCKET
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl::
	lock
	faceplayer
	goto_if_unset FLAG_HIDE_KURT_2, AzaleaTown_KurtsHouse_EventScript_Girl2
	goto_if_set FLAG_HIDE_KURT_1, AzaleaTown_KurtsHouse_EventScript_Girl3
	msgbox KurtsHouse_Text_GranddaughterSlowpokeGone, MSGBOX_DEFAULT
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl2::
	goto_if_eq VAR_AZALEA_TOWN_STATE, 3, AzaleaTown_KurtsHouse_EventScript_Girl4
	goto_if_eq VAR_AZALEA_TOWN_STATE, 4, AzaleaTown_KurtsHouse_EventScript_Girl4
	goto_if_eq VAR_AZALEA_TOWN_STATE, 5, AzaleaTown_KurtsHouse_EventScript_Girl4
	goto_if_eq VAR_AZALEA_TOWN_STATE, 6, AzaleaTown_KurtsHouse_EventScript_Girl4
	goto_if_eq VAR_AZALEA_TOWN_STATE, 8, AzaleaTown_KurtsHouse_EventScript_Girl5
	goto_if_eq VAR_AZALEA_TOWN_STATE, 9, AzaleaTown_KurtsHouse_EventScript_Girl5

	msgbox KurtsHouse_Text_GranddaughterDad, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl3::
	msgbox KurtsHouse_Text_GranddaughterLonely, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_KurtsHouse_EventScript_Girl4::
	msgbox KurtsHouse_Text_GranddaughterSlowpokeBack, MSGBOX_DEFAULT
	closemessage
	release
	end	

AzaleaTown_KurtsHouse_EventScript_Girl5::
	msgbox KurtsHouse_Text_GranddaughterSound, MSGBOX_DEFAULT
	closemessage
	release
	end	

AzaleaTown_KurtsHouse_EventScript_ReturnFromWellSetup::
	setobjectmovementtype LOCALID_AZALEA_TOWN_KURT, MOVEMENT_TYPE_FACE_DOWN
	end

AzaleaTown_KurtsHouse_EventScript_ReturnFromWell::
	lock
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	msgbox KurtsHouse_Text_KurtHonoredToMakeBalls, MSGBOX_DEFAULT
	giveitem ITEM_FAST_BALL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox KurtsHouse_Text_KurtBallsFromApricorns, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	setvar VAR_AZALEA_TOWN_STATE, 4
	release
	end

AzaleaTown_KurtsHouse_EventScript_KurtCheckGSBall::
	checkitem ITEM_GS_BALL
	goto_if_eq VAR_RESULT, TRUE, AzaleaTown_KurtsHouse_EventScript_KurtGsBall
	return

AzaleaTown_KurtsHouse_EventScript_Kurt::
	lock
	faceplayer
	goto_if_eq VAR_AZALEA_TOWN_STATE, 8, AzaleaTown_KurtsHouse_EventScript_KurtGsBall2
	goto_if_eq VAR_AZALEA_TOWN_STATE, 9, AzaleaTown_KurtsHouse_EventScript_KurtGsBall3
	msgbox KurtsHouse_Text_KurtAskYouHaveAnApricorn, MSGBOX_DEFAULT
	closemessage
	call_if_unset FLAG_CAUGHT_CELEBI, AzaleaTown_KurtsHouse_EventScript_KurtCheckGSBall
AzaleaTown_KurtsHouse_EventScript_Kurt2::
	special CreateKurtBallShop
	waitstate
	goto_if_eq VAR_RESULT, FALSE, AzaleaTown_KurtsHouse_EventScript_KurtCancel
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	call_if_eq VAR_FACING, DIR_EAST, AzaleaTown_KurtsHouse_EventScript_TurnWest
	call_if_eq VAR_FACING, DIR_WEST, AzaleaTown_KurtsHouse_EventScript_TurnEast
	call_if_eq VAR_FACING, DIR_NORTH, AzaleaTown_KurtsHouse_EventScript_TurnSouth
	goto_if_eq VAR_0x8005, 1, AzaleaTown_KurtsHouse_EventScript_SingularBall
	bufferitemname STR_VAR_1, VAR_0x8004
	buffernumberstring STR_VAR_2, VAR_0x8005
	msgbox KurtsHouse_Text_KurtFinishedPlural, MSGBOX_DEFAULT
	message KurtsHouse_Text_KurtObtainedPlural
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	additem VAR_0x8004, VAR_0x8005
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end

AzaleaTown_KurtsHouse_EventScript_TurnSouth::
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_SOUTH
	return
AzaleaTown_KurtsHouse_EventScript_TurnWest::
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_WEST
	return
AzaleaTown_KurtsHouse_EventScript_TurnEast::
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_EAST
	return


AzaleaTown_KurtsHouse_EventScript_SingularBall::
	bufferitemname STR_VAR_1, VAR_0x8004
	msgbox KurtsHouse_Text_KurtFinishedSingular, MSGBOX_DEFAULT
	message KurtsHouse_Text_KurtObtainedSingular
	waitmessage
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	additem VAR_0x8004, VAR_0x8005
	msgbox KurtsHouse_Text_KurtTurnedOutGreat, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end

AzaleaTown_KurtsHouse_EventScript_KurtCancel::
	closemessage
	turnobject LOCALID_AZALEA_TOWN_KURT, DIR_NORTH
	release
	end

AzaleaTown_KurtsHouse_EventScript_KurtGsBall::
	msgbox KurtsHouse_Text_KurtWhatIsThat, MSGBOX_DEFAULT
	closemessage
	removeitem ITEM_GS_BALL
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	playse SE_BANG
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Making_Ball
	waitmovement 0
	faceplayer
	msgbox KurtsHouse_Text_KurtThisBallStartedToShake, MSGBOX_DEFAULT
	closemessage
	playse SE_M_PETAL_DANCE
	waitse
	playse SE_PIN
	applymovement LOCALID_AZALEA_TOWN_KURT, Common_Movement_ExclamationMark
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	waitse
	playse SE_M_PETAL_DANCE
	waitse
	applymovement LOCALID_AZALEA_TOWN_KURT, AzaleaTownKurt_Movement_Look_Around
	applymovement OBJ_EVENT_ID_PLAYER, AzaleaTownKurt_Movement_Look_Around
	waitmovement 0
	waitmovement 0
AzaleaTown_KurtsHouse_EventScript_KurtGsBall2::
	msgbox KurtsHouse_Text_Kurt_Whatwasthat, MSGBOX_DEFAULT
	setvar VAR_AZALEA_TOWN_STATE, 8
	closemessage
	release
	end

AzaleaTown_KurtsHouse_EventScript_KurtGsBall3::
	msgbox KurtsHouse_Text_Forest, MSGBOX_DEFAULT
	closemessage
	delay 30
	msgbox KurtsHouse_Text_BallAnyway, MSGBOX_DEFAULT
	closemessage
	goto AzaleaTown_KurtsHouse_EventScript_Kurt2
	release
	end
KurtsHouse_Text_BallAnyway:
	.string "De todos modos, ¿te hago unas BALLS?$"

AzaleaTown_KurtsHouse_EventScript_OakPhoto::
	msgbox KurtsHouse_Text_OakPhoto, MSGBOX_SIGN
	closemessage
	end

AzaleaTown_KurtsHouse_EventScript_CelebiStatue::
	msgbox KurtsHouse_Text_CelebiStatue, MSGBOX_SIGN
	closemessage
	end

AzaleaTownKurt_Movement_Look_Around:
	face_left
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_down
	delay_8
	face_left
	step_end

AzaleaTownKurt_Movement_Making_Ball:
	face_up
	walk_in_place_fast_up
	delay_8
	walk_in_place_fast_up
	delay_8
	walk_in_place_fast_up
	step_end

AzaleaTown_KurtsHouse_Movement_Player:
	face_right
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

AzaleaTown_KurtsHouse_Movement_KurtWalkDown:
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	step_end

KurtsHouse_Text_KurtGetStarted:
	.string "KURT: I'll get started right now!$"

KurtsHouse_Text_KurtMakingBallsMustWait:
	.string "¿Hm? ¿Quién eres?\p"
	.string "{PLAYER}, ¿eh? Quieres que haga\n"
	.string "unas BALLS?\p"
	.string "Lo siento, eso tendrá que esperar.\p"
	.string "¿Conoces al TEAM ROCKET?\n"
	.string "Ah, no te preocupes.\p"
	.string "Te lo contaré de todos modos.\p"
	.string "El TEAM ROCKET es una banda malvada\n"
	.string "que usa POKéMON para sus fechorías.\p"
	.string "Se supone que se habían disuelto\n"
	.string "hace tres años.\p"
	.string "En fin, están en el POZO,\n"
	.string "¡cortando COLAS DE SLOWPOKE!\p"
	.string "¡Así que voy a darles una\n"
	.string "lección de dolor!\p"
	.string "¡Resiste, SLOWPOKE! El viejo KURT\n"
	.string "¡ya va en camino!$"

KurtsHouse_Text_KurtHonoredToMakeBalls:
	.string "KURT: ¡Hola, {PLAYER}!\p"
	.string "Te manejaste como un\n"
	.string "héroe real en el POZO.\p"
	.string "¡Me gusta tu estilo!\p"
	.string "Sería un honor fabricar\n"
	.string "BALLS para un entrenador como tú.\p"
	.string "Esto es todo lo que tengo ahora, \n"
	.string "pero tómalo.$"

KurtsHouse_Text_KurtBallsFromApricorns:
	.string "KURT: Hago BALLS con BAYAS.\p"
	.string "Recógelas de los árboles y tráelas\n"
	.string "para mí.\p"
	.string "Haré POKé BALLS con ellas.$"

KurtsHouse_Text_KurtAskYouHaveAnApricorn:
	.string "KURT: ¿Tienes BAYAS para mí?\p"
	.string "¡Bien! Las convertiré en POKé BALLS.$"

KurtsHouse_Text_KurtThatsALetdown:
	.string "KURT: ¡No veo ninguna {STR_VAR_1}!$"

KurtsHouse_Text_KurtFinishedPlural:
	.string "KURT: ¡{PLAYER}!\n"
	.string "Tus {STR_VAR_1} están listas. ¡Toma!$"

KurtsHouse_Text_KurtObtainedPlural:
	.string "{PLAYER} obtuvo\n"
	.string "{STR_VAR_2} {STR_VAR_1}!$"

KurtsHouse_Text_KurtFinishedSingular:
	.string "KURT: ¡{PLAYER}!\n"
	.string "Tu {STR_VAR_1} está lista. ¡Toma!$"

KurtsHouse_Text_KurtObtainedSingular:
	.string "{PLAYER} obtuvo\n"
	.string "¡la {STR_VAR_1}!$"

KurtsHouse_Text_KurtTurnedOutGreat:
	.string "KURT: Quedó genial.\p"
	.string "Intenta capturar POKéMON con ella.$"

KurtsHouse_Text_KurtWhatIsThat:
	.string "¿Qu-qué es eso?\p"
	.string "Nunca había visto una así.\p"
	.string "Parece una POKé BALL, pero\n"
	.string "parece ser algo distinto.\p"
	.string "Déjame revisarla por ti.$"

KurtsHouse_Text_KurtImCheckingItNow:
	.string "Lo reviso ahora.$"

KurtsHouse_Text_KurtAhHaISee:
	.string "¡Ajá! ¡Ya veo! Así que...$"

KurtsHouse_Text_KurtThisBallStartedToShake:
	.string "¡{PLAYER}!\p"
	.string "Esta BALL empezó a agitarse\n"
	.string "mientras la revisaba.\p"
	.string "¡Debe haber algo en esto!$"

KurtsHouse_Text_Kurt_Whatwasthat:
	.string "¡¿Qué fue ese sonido?!\p"
	.string "¡Vamos afuera a investigar!$"

KurtsHouse_Text_GranddaughterSlowpokeGone:
	.string "Los SLOWPOKE se han ido... \n"
	.string "¿Se los llevaron personas malas?$"

KurtsHouse_Text_GranddaughterLonely:
	.string "El abuelo se fue... Qué soledad...$"

KurtsHouse_Text_GranddaughterSlowpokeBack:
	.string "¡Volvió el SLOWPOKE que me dio papá!\p"
	.string "¡Su COLA también está creciendo!$"

KurtsHouse_Text_GranddaughterDad:
	.string "Mi papá trabaja en SILPH, donde\n"
	.string "estudia las POKé BALLS.\p"
	.string "Tengo que quedarme en casa\n"
	.string "con el abuelo y SLOWPOKE.$"

KurtsHouse_Text_GranddaughterHelp:
	.string "¡Ahora ayudo al abuelo!\p"
	.string "Haremos buenas BALLS\n"
	.string "para ti, ¡así que espera!$"

KurtsHouse_Text_GranddaughterFun:
	.string "¡Es divertido hacer PELOTAS!$"

KurtsHouse_Text_GranddaughterSound:
	.string "¿Ese sonido vino del\n"
	.string "BOSQUE VERDE????$"

KurtsHouse_Text_Forest:
	.string "¿Ya revisaste el BOSQUE VERDE?\n"
	.string "Suena muy inquieto.$"

KurtsHouse_Text_Slowpoke:
	.string "SLOWPOKE: ... Yawn?$"

KurtsHouse_Text_OakPhoto:
	.string "...A young PROF. OAK?$"

KurtsHouse_Text_CelebiStatue:
	.string "Es una estatua del protector\n"
	.string "del bosque.$"
