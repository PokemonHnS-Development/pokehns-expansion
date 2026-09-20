BattleFrontier_BattleTowerMultiPartnerRoom_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleTowerMultiPartnerRoom_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame
	.byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_OnResume:
	pyramid_resetparty
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition:
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_1
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_2
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_3
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_4
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_5
	clearflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_6
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_1
	setflag FLAG_HIDE_BATTLE_TOWER_MULTI_BATTLE_PARTNER_ALT_2
	tower_loadpartners
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_2, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_3, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_4, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_5, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_6, OBJ_EVENT_GFX_BOY_1
	setvar VAR_OBJ_GFX_ID_7, OBJ_EVENT_GFX_BOY_1
	setvar VAR_TEMP_1, 1
	setvar VAR_TEMP_3, 1
	setobjectxyperm LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, 10, 2
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp:
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom::
	lockall
	setvar VAR_TEMP_3, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom::
	lockall
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom
	waitmovement 0
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit
	waitmovement 0
	copyobjectxytoperm LOCALID_TOWER_PARTNER_ROOM_ATTENDANT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner, MSGBOX_DEFAULT
	special HealPlayerParty
	setvar VAR_TEMP_1, 1
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom:
	walk_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit:
	walk_left
	walk_in_place_faster_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Attendant::
	lock
	faceplayer
	message BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge::
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator::
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 10, 1
	waitdooranim
	call BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator
	closedoor 10, 1
	waitdooranim
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_ELEVATOR, 1, 6
	waitstate
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator::
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorEast:
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevatorWest:
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator:
	walk_up
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevatorEast:
	walk_right
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest:
	walk_left
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner1::
	lock
	faceplayer
	setvar VAR_TEMP_2, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner::
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_INTRO
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON1
	waitmessage
	waitbuttonpress
	tower_dopartnermsg PARTNER_MSGID_MON2_ASK
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner
	tower_dopartnermsg PARTNER_MSGID_ACCEPT
	waitmessage
	waitbuttonpress
	closemessage
	call_if_ne VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth
	removeobject VAR_LAST_TALKED
	setflag FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_TOWER_MULTI_PARTNER_ROOM, 10, 3
	waitstate
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner::
	tower_dopartnermsg PARTNER_MSGID_REJECT
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExitSouth::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExitSouth:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner2::
	lock
	faceplayer
	setvar VAR_TEMP_2, 1
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner3::
	lock
	faceplayer
	setvar VAR_TEMP_2, 2
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner4::
	lock
	faceplayer
	setvar VAR_TEMP_2, 3
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner5::
	lock
	faceplayer
	setvar VAR_TEMP_2, 4
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner6::
	lock
	faceplayer
	setvar VAR_TEMP_2, 5
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner7::
	lock
	faceplayer
	setvar VAR_TEMP_2, 6
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner8::
	lock
	faceplayer
	setvar VAR_TEMP_2, 7
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner:
	.string "Busca un compañero entre los\n"
	.string "ENTRENADORES reunidos aquí.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner:
	.string "{PLAYER}, no has encontrado un\n"
	.string "compañero para tu equipo.\p"
	.string "¿Quieres dejar de buscar y\n"
	.string "volver al mostrador de recepción?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner2:
	.string "Entonces, busca un compañero entre\n"
	.string "ENTRENADORES reunidos aquí.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner::
	.string "Gracias por elegir un compañero.\p"
	.string "Ahora te llevaré a tu\n"
	.string "SALA DE BATALLA MÚLTIPLE.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Intro::
	.string "Soy el aprendiz nro. {STR_VAR_2} de {STR_VAR_1}.\n"
	.string "¡Puedes llamarme {STR_VAR_3}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon1::
	.string "Por consejo de {STR_VAR_1}, traje\n"
	.string "un {STR_VAR_3} con {STR_VAR_2} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¡Por favor, hagamos un equipo doble!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Accept::
	.string "¡Gracias!\n"
	.string "Iré a registrarme ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Reject::
	.string "De verdad quería formar un equipo\n"
	.string "doble contigo, {PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Intro::
	.string "Soy el aprendiz nro. {STR_VAR_2} de {STR_VAR_1}.\n"
	.string "Mi nombre es {STR_VAR_3}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon1::
	.string "Seguí el consejo de {STR_VAR_1} y elegí\n"
	.string "un {STR_VAR_3} con {STR_VAR_2} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¡Por favor, hagamos un equipo doble!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Accept::
	.string "¡Muchas gracias!\n"
	.string "¡Terminaré el registro rápido!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Reject::
	.string "{PLAYER}, esperaba que pudiera\n"
	.string "ser tu compañero…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Intro::
	.string "Eh, me llamo {STR_VAR_3} y soy\n"
	.string "el aprendiz {STR_VAR_2} de {STR_VAR_1}.\p"
	.string "Snif…\p"
	.string "¡Lo siento!\n"
	.string "¡Tanta tensión me hace llorar…!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon1::
	.string "{STR_VAR_3} me aconsejó, así que tengo\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "Snif…\n"
	.string "¡Por favor, haz equipo conmigo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Accept::
	.string "¿Ah, sí? ¿Lo harás?\n"
	.string "¡Genial! ¡Increíble! ¡Awoooh!\p"
	.string "Oh... lo siento...\n"
	.string "Estoy tan feliz que lloro...\p"
	.string "Iré a registrarme ahora mismo.\n"
	.string "¡Por favor, no te vayas!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Reject::
	.string "Oh, p-pero...\n"
	.string "Snif... ¡Buaaaaaah!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Intro::
	.string "¡Hola! ¡Soy {STR_VAR_3}!\n"
	.string "¡Soy el aprendiz {STR_VAR_2} de {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon1::
	.string "{STR_VAR_3} recomendó a mi equipo.\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1},\n"
	.string "¡eso es lo que tengo! Genial, ¿no?\p"
	.string "¡Así que vamos!\n"
	.string "¡Hagamos un equipo doble!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Accept::
	.string "¡Súper! ¡Genial!\n"
	.string "Bien, iré a registrarme, ¿sí?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Reject::
	.string "Ay, ¿por qué?\n"
	.string "¡Quería ser tu pareja, {PLAYER}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Intro::
	.string "Soy {STR_VAR_3}, el aprendiz n.º {STR_VAR_2}\n"
	.string "¡del famoso {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon1::
	.string "Le pedí consejo a {STR_VAR_3}.\n"
	.string "One {STR_VAR_1}-using {STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon2Ask::
	.string "y un {STR_VAR_2} con {STR_VAR_1},\n"
	.string "esa es mi pareja.\p"
	.string "Por favor, ¿te unirías a mí en\n"
	.string "un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Accept::
	.string "¡Gracias!\n"
	.string "¡Me registraré ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Reject::
	.string "{PLAYER}, esperaba unirme a ti\n"
	.string "en un equipo doble…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Intro::
	.string "Eh… Me alegra sinceramente que\n"
	.string "te tomes el tiempo de hablarme.\p"
	.string "Soy {STR_VAR_3}.\n"
	.string "Soy el aprendiz nro. {STR_VAR_2} de {STR_VAR_1}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon1::
	.string "{STR_VAR_3} me dio un consejo.\n"
	.string "Estoy muy agradecido por ello.\p"
	.string "Tengo un equipo de un {STR_VAR_2}\n"
	.string "con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\n"
	.string "Sé que pido demasiado...\p"
	.string "No creo que quieras hacerlo,\n"
	.string "¡¿pero puedo ir contigo?!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Accept::
	.string "¡¿En serio?! ¡No lo puedo creer!\n"
	.string "¡No creo que me dejes acompañarte!\l"
	.string "¡Yo... no te fallaré!\p"
	.string "Eh... si está bien, iré a registrarme\n"
	.string "¡en este mismo instante!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Reject::
	.string "Oh…\n"
	.string "No creía ser lo suficiente...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Intro::
	.string "Hola, soy {STR_VAR_3}.\n"
	.string "¡Soy el aprendiz {STR_VAR_2} de {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon1::
	.string "{STR_VAR_3} me dijo que sería\n"
	.string "bueno para este equipo:\l"
	.string "un {STR_VAR_2} que use {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon2Ask::
	.string "y un {STR_VAR_2} que sepa\n"
	.string "usar {STR_VAR_1}.\p"
	.string "Nada mal, ¿eh?\n"
	.string "¿Quieres que me una a tu equipo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Accept::
	.string "¡Vale, me alegra acompañarte!\n"
	.string "¡Espero que no lo arruines todo!\l"
	.string "Me registraré ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Reject::
	.string "¿Eh? ¿Por qué me rechazaste?\n"
	.string "¡No sabes juzgar a la gente!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Intro::
	.string "Soy {STR_VAR_3} y soy TRIATLETA.\n"
	.string "Estoy ocupado todo el día trotando,\l"
	.string "entrenando y rapeando.\p"
	.string "I also happen to be {STR_VAR_1}'s\n"
	.string "no. {STR_VAR_2} apprentice.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon1::
	.string "Esto es lo que {STR_VAR_3} sugirió.\n"
	.string "One {STR_VAR_1}-using {STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon2Ask::
	.string "y un usuario de {STR_VAR_1}\n"
	.string "{STR_VAR_2}.\p"
	.string "Me esfuerzo mucho en criarlos,\n"
	.string "aunque esté muy ocupado.\p"
	.string "¡Hagamos un equipo doble\n"
	.string "y probemos suerte!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Accept::
	.string "¡Gracias, esa es la actitud!\n"
	.string "Espera mientras me registro, ¿sí?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Reject::
	.string "¡Saqué tiempo de mi agenda\n"
	.string "para venir! ¡Dame un respiro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Intro::
	.string "Hi!\n"
	.string "¿Cómo va todo?\p"
	.string "I'm {STR_VAR_3}, {STR_VAR_1}'s\n"
	.string "no. {STR_VAR_2} apprentice. Glad to meet you!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon1::
	.string "¡Oye, escucha! Tienes que saber\n"
	.string "del POKéMON que recomendó {STR_VAR_3}.\l"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\n"
	.string "¡Claro que los crié superbamente!\p"
	.string "Entonces, ¿quieres hacer equipo?\n"
	.string "¡Seguro que seremos un gran combo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Accept::
	.string "¡Súper, creo que será divertido!\n"
	.string "¡Iré a registrarme!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Reject::
	.string "¡Ay, qué malo eres!\n"
	.string "Vengo recomendado, ¿sabes?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Intro::
	.string "Permíteme presentarme.\n"
	.string "Soy {STR_VAR_3}.\p"
	.string "Sirvo como el {STR_VAR_1} de\n"
	.string "no. {STR_VAR_2} apprentice.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon1::
	.string "Busqué el sabio consejo de\n"
	.string "{STR_VAR_3} y crié a mi equipo\l"
	.string "de un {STR_VAR_2} con {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon2Ask::
	.string "y un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¡Acepta luchar en pareja conmigo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Accept::
	.string "¡Oh... estoy encantado!\n"
	.string "¡Prometo dar lo mejor de mí!\p"
	.string "¡Claro que nos registraré!\n"
	.string "¡Espera, por favor!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Reject::
	.string "Tenía esperanzas de unirme a ti,\n"
	.string "{PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Intro::
	.string "¡Ay! ¡Me hablaste!\n"
	.string "¡Estoy... estoy feliz!\p"
	.string "I'm {STR_VAR_3}! I'm {STR_VAR_1}'s\n"
	.string "no. {STR_VAR_2} apprentice!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon1::
	.string "Por consejo de {STR_VAR_3}, entrené\n"
	.string "un {STR_VAR_2} que use {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon2Ask::
	.string "y un usuario de {STR_VAR_1}\n"
	.string "{STR_VAR_2}.\p"
	.string "Por favor, ¿cumples mi deseo?\n"
	.string "¡Quiero ser tu pareja de combate!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Accept::
	.string "¡Ay! ¡Me... me siento mareada!\n"
	.string "¡Muchísimas gracias!\l"
	.string "¡Iré a registrarnos ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Reject::
	.string "¡Waaah! ¿No tienes piedad?\n"
	.string "Pero eso te hace más genial...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Intro::
	.string "¡Yeehaw! Soy el aprendiz de {STR_VAR_1}\n"
	.string "¡el aprendiz nro. {STR_VAR_2}!\p"
	.string "¡Me llamo {STR_VAR_3}, hola, hola!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon1::
	.string "Mi mentor {STR_VAR_3} recomendó\n"
	.string "un maestro {STR_VAR_2} de {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon2Ask::
	.string "y un maestro de {STR_VAR_1}\n"
	.string "{STR_VAR_2}.\p"
	.string "Cosas buenas, ¿eh?\n"
	.string "¿Serás mi compañero, verdad?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Accept::
	.string "¡Bien, excelente!\n"
	.string "¡Haré el registro rápidamente!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Reject::
	.string "¡Gwaaah!\n"
	.string "¡Eres muy calculador, {PLAYER}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Intro::
	.string "¡Oye! ¡Hay un gran problema! Es\n"
	.string "¡el último día de la BATTLE TOWER!\p"
	.string "… … … … … …\n"
	.string "¡Solo estoy bromeando!\p"
	.string "Me llaman {STR_VAR_3} ¡y yo también!\n"
	.string "¡Soy el aprendiz 1,000 de {STR_VAR_1}!\l"
	.string "¡En realidad, soy el no. {STR_VAR_2}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon1::
	.string "{STR_VAR_3} me dio un consejo.\n"
	.string "{STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon2Ask::
	.string "{STR_VAR_2} con {STR_VAR_1}.\n"
	.string "¡Tengo diez de cada tipo!\l"
	.string "¡En realidad, solo uno de cada!\p"
	.string "¿Qué te parece?\n"
	.string "¿Quieres batallas dobles conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Accept::
	.string "¡Súper!\n"
	.string "¡Te daré un POKéMON en agradecimiento!\p"
	.string "¡Es broma! Pero iré a hacer\n"
	.string "el registro, ¿está bien?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Reject::
	.string "¡Qué frío! ¡Tendré que arrasar\n"
	.string "la BATTLE TOWER por eso!\p"
	.string "¡Claro que no lo haré!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Intro::
	.string "¡Hola! ¡Llego con todo el ritmo!\n"
	.string "¡A mis POKéMON yo controlo!\p"
	.string "Soy {STR_VAR_3}, el MARINERO rapero.\n"
	.string "¡No me confundas con un llorón!\p"
	.string "Soy el aprendiz nro. {STR_VAR_2} de {STR_VAR_1}.\n"
	.string "¡No me subestimes tan rápido!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon1::
	.string "Con el consejo de {STR_VAR_3} yo\n"
	.string "seguí, ¡y mi equipo así surgió!\l"
	.string "One {STR_VAR_1}-using {STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon2Ask::
	.string "y un usuario de {STR_VAR_1}\n"
	.string "{STR_VAR_2}!\p"
	.string "Nuestro encuentro hay que anotar,\n"
	.string "¡con una victoria en pareja celebrar!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Accept::
	.string "¡Oye, oye, me gusta tu estilo!\n"
	.string "¡Yo mismo iré a registrarlos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Reject::
	.string "¡Oh, hola, {PLAYER}, eso fue frío!\n"
	.string "¡Si me permites ser tan audaz!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Intro::
	.string "¡Yippee-yahoo!\n"
	.string "¡No huyas! ¡Solo me divertía!\p"
	.string "¡Hola! ¡Soy {STR_VAR_3}!\n"
	.string "¡Soy el aprendiz {STR_VAR_2} de {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon1::
	.string "{STR_VAR_3} me dijo qué hacer.\n"
	.string "Así que un {STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon2Ask::
	.string "y un usuario de {STR_VAR_1}\n"
	.string "{STR_VAR_2}, es el que elegí.\p"
	.string "Entonces, ¿qué dices?\n"
	.string "¡Vamos, dame una alegría!\p"
	.string "¡Por favor, te lo ruego!\n"
	.string "¡Déjame ir, no me ignores!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Accept::
	.string "¡Siii! ¡La suerte está conmigo!\n"
	.string "¡Eso me hace muy feliz!\p"
	.string "Antes de ir a la batalla,\n"
	.string "¡iré a registrarme ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Reject::
	.string "¿Me estás rechazando?\n"
	.string "{PLAYER}, ¡me pones triste!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Intro::
	.string "¡Cof, cof!\p"
	.string "Oh, perdón, tengo un resfriado.\n"
	.string "Pero mis POKéMON están bien.\p"
	.string "Me llamo {STR_VAR_3}, soy de {STR_VAR_1}\n"
	.string "aprendiz de {STR_VAR_2}. ¡Cof!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon1::
	.string "Seguí el consejo de {STR_VAR_3}\n"
	.string "y armé mi equipo de\l"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "Los entrené cada día,\n"
	.string "incluso con viento y lluvia.\p"
	.string "Por eso tengo este resfriado,\n"
	.string "creo.\p"
	.string "Así soy yo.\n"
	.string "¿Quieres ser mi pareja de combate?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Accept::
	.string "¡Gracias, te lo agradezco!\n"
	.string "¡Cof, cof!\l"
	.string "Espera mientras voy a registrarme.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Reject::
	.string "Oh, ¿no quieres?\n"
	.string "{PLAYER}, creo que seríamos un gran par.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Intro::
	.string "¡Oh, hola!\n"
	.string "Esto pone los nervios de punta.\p"
	.string "Soy {STR_VAR_3}.\n"
	.string "Soy el aprendiz nro. {STR_VAR_2} de {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon1::
	.string "{STR_VAR_3} dijo que este equipo es bueno--\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "Me da un poco de vergüenza,\n"
	.string "¿pero me dejarías acompañarte?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Accept::
	.string "¡Oh, cielos, gracias!\n"
	.string "¡Me da pena, pero daré lo mejor!\p"
	.string "Iré a hacer el registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Reject::
	.string "¡Oh, por favor, no digas que no!\n"
	.string "Ya me siento bastante cohibido…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Intro::
	.string "Soy {STR_VAR_3}, y no es mentira.\n"
	.string "Soy el aprendiz nro. {STR_VAR_2} de {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon1::
	.string "{STR_VAR_3} recomendó a mi equipo.\p"
	.string "Como el consejo parecía sincero,\n"
	.string "decidí traer conmigo a\l"
	.string "mi {STR_VAR_2} de tipo {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon2Ask::
	.string "mi {STR_VAR_2} de tipo {STR_VAR_1}.\p"
	.string "Si es posible, me gustaría que me\n"
	.string "aceptes como tu pareja de equipo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Accept::
	.string "¿De verdad me aceptarás?\n"
	.string "De lo contrario sería terrible.\p"
	.string "Pero ya que aceptaste, está bien.\n"
	.string "Iré a registrarnos a los dos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Reject::
	.string "¿Hm? ¿Por qué rechazarías?\n"
	.string "¿Crees que esto es una broma?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassIntro::
	.string "I'm {STR_VAR_1}, and I'm a LASS!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon1::
	.string "Tengo un {STR_VAR_2}\n"
	.string "que usa {STR_VAR_1} y un$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon2Ask::
	.string "{STR_VAR_2} que usa {STR_VAR_1}.\n"
	.string "Eso es lo que traigo conmigo.\p"
	.string "¿Quieres ser mi compañero?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassAccept::
	.string "¡Gracias!\n"
	.string "¡Yo haré el registro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassReject::
	.string "¿No quieres ser mi compañero?\n"
	.string "¡Luego te arrepentirás!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterIntro::
	.string "¡Hola!\p"
	.string "¡Soy el JOVEN {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon1::
	.string "¿Quieres saber qué tengo?\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Serás mi compañero de equipo,\n"
	.string "¿verdad?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterAccept::
	.string "¡Súper!\n"
	.string "Iré a registrarme, ¿está bien?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterReject::
	.string "¡Ay! Si formaras un equipo con\n"
	.string "mis POKéMON, ¡seríamos invencibles!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerIntro::
	.string "¡Yahoo!\n"
	.string "¡Soy el EXCURSIONISTA {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon1::
	.string "¿Sabes qué traigo conmigo?\n"
	.string "¡Mi {STR_VAR_2} de tipo {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon2Ask::
	.string "mi {STR_VAR_2} de tipo {STR_VAR_1}!\p"
	.string "Suena bien, ¿no?\n"
	.string "¿Quieres formar un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerAccept::
	.string "¡Yahoo!\n"
	.string "Iré a hacer el registro entonces.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerReject::
	.string "Me hubiera gustado luchar contigo\n"
	.string "a mi lado.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyIntro::
	.string "¡Hola!\n"
	.string "¡Soy {STR_VAR_1} y soy una BEAUTY!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon1::
	.string "¿Sabes qué he estado criando?\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Qué te parece?\n"
	.string "¿Hacemos un equipo doble juntos?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyAccept::
	.string "¡Maravilloso!\n"
	.string "¡Haré el registro ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyReject::
	.string "¡Qué decepción!\p"
	.string "Nosotros dos juntos... habríamos\n"
	.string "¡sido los mejores!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanIntro::
	.string "Yo!\p"
	.string "¿Sabes quién soy?\n"
	.string "¡Soy el PESCADOR {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon1::
	.string "Tengo un equipo de un\n"
	.string "{STR_VAR_2} que usa {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon2Ask::
	.string "un {STR_VAR_2} que usa {STR_VAR_1}.\p"
	.string "Entonces, ¿qué dices?\n"
	.string "¿Lucharás a mi lado?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanAccept::
	.string "¡Bien, muy bien!\n"
	.string "¡Déjamelo a mí!\p"
	.string "Iré a registrarnos ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanReject::
	.string "We matched up perfectly, too…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyIntro::
	.string "Gusto en conocerte.\n"
	.string "Soy {STR_VAR_1}, una DAMA.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon1::
	.string "Me acompaña un equipo de\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "Espero contar con tu aprobación.\n"
	.string "Pues deseo que seas mi pareja.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyAccept::
	.string "Te lo agradezco sinceramente.\n"
	.string "Yo me encargo del registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyReject::
	.string "Seguro que te arrepentirás de no\n"
	.string "tenerme como tu pareja.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFIntro::
	.string "I'm TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon1::
	.string "Lo que tengo...\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\n"
	.string "¡Ese es mi compañero!\p"
	.string "¡Por favor!\n"
	.string "¿Quieres formar un equipo conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFAccept::
	.string "¡Vaya, gracias!\n"
	.string "Iré a registrarme al mostrador.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFReject::
	.string "Nosotros dos juntos, seguro que\n"
	.string "¡habríamos sido fuertes!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherIntro::
	.string "¡Hola!\n"
	.string "¡Soy el CAZABICHOS {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon1::
	.string "¡Mira lo que tengo!\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¡Oye, escucha!\n"
	.string "¿Quieres formar un equipo conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherAccept::
	.string "¡Te atrapé!\p"
	.string "Iré a hacer el registro\n"
	.string "en el mostrador.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherReject::
	.string "Ay, mis POKéMON son geniales.\n"
	.string "¡Espero que no te arrepientas!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMIntro::
	.string "¡Buen día!\n"
	.string "I'm SCHOOL KID {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon1::
	.string "He estado criando un\n"
	.string "{STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon2Ask::
	.string "y un {STR_VAR_2} que usa\n"
	.string "{STR_VAR_1}.\p"
	.string "No están mal, ¿verdad?\n"
	.string "¿Quieres formar un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMAccept::
	.string "¡Muchas gracias!\n"
	.string "Terminaré el registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMReject::
	.string "Qué mal...\p"
	.string "Esperaba poder aprender\n"
	.string "de ti como tu compañero...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyIntro::
	.string "¡Hola! ¡Déjame presentarme!\n"
	.string "¡Soy el RICO {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon1::
	.string "¡Adivina qué tengo!\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Estoy dispuesto a darte la chance\n"
	.string "de estar en un equipo doble conmigo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyAccept::
	.string "¡Buena decisión!\p"
	.string "Terminaré el registro\n"
	.string "¡Rápido, procesa!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyReject::
	.string "¿Me rechazarías a mí?\n"
	.string "¡Seguro que te arrepentirás de eso!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltIntro::
	.string "¡Hiyah!\n"
	.string "Soy el CINTURÓN NEGRO {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon1::
	.string "Como mis compañeros, tengo\n"
	.string "un {STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon2Ask::
	.string "y un {STR_VAR_2} que usa\n"
	.string "{STR_VAR_1}.\p"
	.string "¡Por favor, cumple mi deseo!\n"
	.string "¡Deja que sea tu pareja de combate!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltAccept::
	.string "¡Hiyah!\n"
	.string "¡Iré a registrarme ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltReject::
	.string "Ya veo... Espero tener una oportunidad\n"
	.string "la próxima vez que nos veamos…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFIntro::
	.string "¡Hola!\n"
	.string "¡Soy {STR_VAR_1}, soy un TUBER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon1::
	.string "Te diré lo que tengo.\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\n"
	.string "¿Puedo estar en tu equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFAccept::
	.string "¡Gracias!\n"
	.string "¡Iré a registrarnos ahora!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFReject::
	.string "Si hubiéramos sido compañeros,\n"
	.string "¡seríamos muy fuertes!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacIntro::
	.string "Saludos...\n"
	.string "Soy la BRUJA {STR_VAR_1}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon1::
	.string "Llevo conmigo un {STR_VAR_1}\n"
	.string "{STR_VAR_2} junto con uno$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon2Ask::
	.string "{STR_VAR_2} que usa {STR_VAR_1}…\p"
	.string "Te lo ruego...\n"
	.string "¡Únete a mi equipo doble!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacAccept::
	.string "Te lo agradezco...\n"
	.string "Nos inscribiré ahora mismo...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacReject::
	.string "I so longed to join you…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMIntro::
	.string "¿Cómo estás? Soy {STR_VAR_1},\n"
	.string "¡y soy CRIADOR POKéMON!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon1::
	.string "¡Estoy criando unos muy buenos!\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Qué te parece?\n"
	.string "¿Quieres formar un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMAccept::
	.string "¡Muchas gracias!\p"
	.string "Iré a encargarme del registro,\n"
	.string "¡así que espera justo aquí!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMReject::
	.string "Tenía muchas ganas de ser\n"
	.string "tu compañero…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFIntro::
	.string "¡Hola, qué tal!\n"
	.string "I'm TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon1::
	.string "¿Quieres ver qué POKéMON tengo?\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Y bien?\n"
	.string "¿Quieres hacer equipo conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFAccept::
	.string "¡Buen trabajo!\p"
	.string "¡Haré el registro rápido\n"
	.string "para terminar ya!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFReject::
	.string "Tú y yo habríamos sido los mejores.\n"
	.string "Es una lástima…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMIntro::
	.string "¡Hola! ¡Mi nombre es {STR_VAR_1}!\n"
	.string "¡Soy TRIATLETA!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon1::
	.string "Corro con mi equipo resistente--\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "No está mal, ¿eh?\n"
	.string "¡Deberíamos ser un equipo doble!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMAccept::
	.string "¡Muy bien!\n"
	.string "¡Me registraré en un instante!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMReject::
	.string "De verdad quería luchar como tu\n"
	.string "compañero de equipo doble…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlIntro::
	.string "I'm BATTLE GIRL {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon1::
	.string "He estado entrenando a mi\n"
	.string "{STR_VAR_2} que usa {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon2Ask::
	.string "{STR_VAR_2} usando {STR_VAR_1}!\p"
	.string "¿Te gusta esa combinación?\n"
	.string "¿Qué tal si nos unimos?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlAccept::
	.string "¡Vaya, gracias!\p"
	.string "Haré el registro\n"
	.string "¡ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlReject::
	.string "Pensé que contigo podríamos formar\n"
	.string "el mejor equipo doble…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMIntro::
	.string "I'm TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon1::
	.string "Tengo un {STR_VAR_2}\n"
	.string "que sabe usar {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon2Ask::
	.string "¡y un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Podríamos ser un equipo doble.\n"
	.string "¿No sería genial?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMAccept::
	.string "¡Gracias!\p"
	.string "Iré a registrarnos, y eso es\n"
	.string "¡ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMReject::
	.string "Vaya, qué mal. Habríamos sido\n"
	.string "¡el equipo doble más fuerte!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMIntro::
	.string "Me?\n"
	.string "¡Soy TUBER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon1::
	.string "¿Qué traigo conmigo?\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Hola?\n"
	.string "Te unirás a mi equipo, ¿verdad?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMAccept::
	.string "¡Está bien!\p"
	.string "¡Iré a registrarme!\n"
	.string "¡Seamos excelentes juntos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMReject::
	.string "Mis POKéMON son fuertes, seguro...\n"
	.string "Lástima que no quieras unirte.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristIntro::
	.string "¡Siii-hey!\n"
	.string "¡Llámame GUITARIST {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon1::
	.string "¡Mira mi séquito!\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¡Siii-hey! Bastante salvaje, ¿no?\n"
	.string "¡Haremos un dúo en equipo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristAccept::
	.string "¡Siii! ¡Exacto!\n"
	.string "¡Haré el registro ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristReject::
	.string "¡Mis POKéMON son fuertes!\n"
	.string "¡Te arrepentirás, te lo digo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanIntro::
	.string "Mucho gusto.\n"
	.string "Soy {STR_VAR_1}, un CABALLERO.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon1::
	.string "Me acompaña mi fiel\n"
	.string "{STR_VAR_2} que usa {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon2Ask::
	.string "un {STR_VAR_2} que usa {STR_VAR_1}.\p"
	.string "¿Me permitiría ser su pareja\n"
	.string "en un combate en equipo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanAccept::
	.string "Ah, gracias por su confianza.\n"
	.string "Terminaré con el registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanReject::
	.string "Eso es muy lamentable...\p"
	.string "Esperaré con ansias la próxima\n"
	.string "oportunidad...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMIntro::
	.string "Hola, soy {STR_VAR_1},\n"
	.string "¡y soy un POKéFAN!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon1::
	.string "Tengo conmigo un {STR_VAR_2}\n"
	.string "que sabe el movimiento {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿Te gusta lo que ves?\n"
	.string "¿Quieres ser mi pareja de equipo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMAccept::
	.string "¡Gracias!\n"
	.string "¡Yo me encargo del registro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMReject::
	.string "Mis POKéMON son de primer nivel...\n"
	.string "Lástima que no puedas apreciarlo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMIntro::
	.string "Hm!\n"
	.string "¡Soy {STR_VAR_1}, y soy un EXPERTO!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon1::
	.string "Los POKéMON que he entrenado son\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Qué dices de hacer equipo conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMAccept::
	.string "Hm!\n"
	.string "¡Nos registraré ahora mismo!\l"
	.string "¡Demos lo mejor de nosotros!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMReject::
	.string "Espero que tu elección sea\n"
	.string "realmente la correcta…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFIntro::
	.string "Hola, hola.\n"
	.string "Soy {STR_VAR_1}, y soy un EXPERTO.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon1::
	.string "He criado bien a mis POKéMON.\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}--\n"
	.string "eso es lo que tengo.\p"
	.string "¿No quieres hacer equipo conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFAccept::
	.string "Bien, bien.\n"
	.string "Haré el registro ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFReject::
	.string "Tal vez podamos formar un equipo la\n"
	.string "próxima vez que nos veamos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerIntro::
	.string "I'm DRAGON TAMER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon1::
	.string "El equipo que he estado entrenando es\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Qué te parece?\n"
	.string "¿Quieres ser mi compañero?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerAccept::
	.string "¡Está bien, daré lo mejor de mí!\n"
	.string "Iré a registrarme ahora, ¿vale?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerReject::
	.string "¡No hallarás a muchos compañeros más\n"
	.string "fuertes que yo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperIntro::
	.string "I'm BIRD KEEPER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon1::
	.string "¿Qué POKéMON tengo?\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿No crees que haríamos un buen\n"
	.string "equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperAccept::
	.string "¡Genial, gracias!\n"
	.string "¡Yo me encargo del registro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperReject::
	.string "Mis POKéMON y yo somos fuertes.\n"
	.string "Qué decepción.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyIntro::
	.string "I'm NINJA BOY {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon1::
	.string "Mi equipo POKéMON consiste en uno\n"
	.string "{STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¡Hagamos un equipo doble juntos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyAccept::
	.string "¡Súper!\n"
	.string "¡Déjame ir a registrarme!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyReject::
	.string "Lamentarás no tener a mis fuertes\n"
	.string "¡POKéMON a tu lado!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyIntro::
	.string "¡Hola!\n"
	.string "¡Soy la SEÑORA SOMBRILLA {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon1::
	.string "Me acompañan mis {STR_VAR_2},\n"
	.string "que usa {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon2Ask::
	.string "un {STR_VAR_2} que usa\n"
	.string "{STR_VAR_1}.\p"
	.string "¿No son lindos?\n"
	.string "¿Quieres unirte en un combate doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyAccept::
	.string "¡Muchas gracias!\p"
	.string "Iré a registrarme al mostrador.\n"
	.string "¡No nos decepcionemos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyReject::
	.string "Mis POKéMON son muy fuertes.\n"
	.string "Qué decepción...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacIntro::
	.string "Hola.\n"
	.string "¡Soy {STR_VAR_1}, un FANÁTICO BICHOS!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon1::
	.string "He hallado mis POKéMON, sí.\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}--\n"
	.string "son los que he encontrado.\p"
	.string "¿Te interesa formar parte?\n"
	.string "un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacAccept::
	.string "¡Está bien!\n"
	.string "¡Entendido!\p"
	.string "¡No tardaré con el registro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacReject::
	.string "Con los POKéMON que hallé, no\n"
	.string "habríamos perdido...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorIntro::
	.string "¡Hola, marinero!\n"
	.string "¡Soy el MARINERO {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon1::
	.string "¡Mira mi mayor orgullo y alegría!\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Claro que no me vas a rechazar,\n"
	.string "haremos equipo, ¿verdad?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorAccept::
	.string "¡No esperaba menos de ti!\n"
	.string "Iré a registrarme ahora.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorReject::
	.string "¡Habríamos arrasado con toda\n"
	.string "la oposición! ¡Qué mal!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorIntro::
	.string "Hola, soy {STR_VAR_1}.\n"
	.string "Soy COLECCIONISTA.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon1::
	.string "Las joyas de mi colección son\n"
	.string "mi {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Genial, ¿eh?\n"
	.string "Deberíamos estar en el mismo equipo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorAccept::
	.string "¡Oh, sí!\p"
	.string "Bueno, no perdamos tiempo.\n"
	.string "Iré a registrarnos los dos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorReject::
	.string "Vaya, eso es decepcionante.\n"
	.string "No valoras a mis POKéMON.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMIntro::
	.string "Hola, soy {STR_VAR_1}.\n"
	.string "Soy un POKéMON RANGER.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon1::
	.string "Me acompañan algunos\n"
	.string "{STR_VAR_2} que usa {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿No crees que haríamos un equipo\n"
	.string "equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMAccept::
	.string "¡Eso es genial!\n"
	.string "Me encargo del registro ahora.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMReject::
	.string "La próxima, elige a mis POKéMON,\n"
	.string "¿Lo harás?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFIntro::
	.string "Mi nombre es {STR_VAR_1}.\n"
	.string "¡Soy un POKéMON RANGER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon1::
	.string "Te hablaré de mi equipo. Tengo\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Te gustaría formar un equipo\n"
	.string "con mi pequeño grupo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFAccept::
	.string "¡Estaremos en nuestra mejor forma!\n"
	.string "¡Haré el registro rápido!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFReject::
	.string "Espero que elijas a mis POKéMON\n"
	.string "la próxima vez.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyIntro::
	.string "Mucho gusto. Soy {STR_VAR_1}.\n"
	.string "Me considero una AROMA LADY.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon1::
	.string "Viajo con un {STR_VAR_2}\n"
	.string "que usa {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon2Ask::
	.string "un {STR_VAR_2} que usa\n"
	.string "{STR_VAR_1}.\p"
	.string "Espero que te llamen la atención.\n"
	.string "¿Te gustaría ser mi compañero?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyAccept::
	.string "Me honra que hayas aceptado.\n"
	.string "Iré a registrarme ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyReject::
	.string "Sería maravilloso que pudiéramos\n"
	.string "ser un equipo la próxima vez.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacIntro::
	.string "¿Quieres saber quién soy?\n"
	.string "¡Soy {STR_VAR_1}, el FAN RUINAS!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon1::
	.string "Los POKéMON que traigo conmigo son\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Intrigantes, ¿eh?\n"
	.string "¿Qué tal si somos compañeros?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacAccept::
	.string "¡Es una decisión acertada!\n"
	.string "Iré a hacer el papeleo de registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacReject::
	.string "Hmm…\n"
	.string "Creo que mis POKéMON son fuertes…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMIntro::
	.string "I'm COOLTRAINER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon1::
	.string "Los POKéMON que tengo ahora son\n"
	.string "{STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\n"
	.string "geniales, ¿no?\p"
	.string "¿No crees que sería genial\n"
	.string "si formáramos un equipo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMAccept::
	.string "¡Genial!\n"
	.string "¡Haré el registro en un santiamén!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMReject::
	.string "Pensé que formaríamos\n"
	.string "el mejor equipo de la historia.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFIntro::
	.string "I'm COOLTRAINER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon1::
	.string "El equipo que he criado tiene uno\n"
	.string "{STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿Te parece bien?\n"
	.string "¿Y si somos pareja de combate?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFAccept::
	.string "¡Me parece genial!\n"
	.string "Mejor hago el registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFReject::
	.string "Pensaba en lo fuertes que\n"
	.string "seríamos como equipo…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacIntro::
	.string "¡Hola!\n"
	.string "¡Soy {STR_VAR_1}, el POKéMANÍACO!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon1::
	.string "¿Qué tiene alguien como yo?\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1},\n"
	.string "¡Pues esto!\p"
	.string "¡Hagámoslo!\n"
	.string "¡Daremos guerra en equipo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacAccept::
	.string "¡Buena idea!\n"
	.string "¡Nos registraré a los dos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacReject::
	.string "¡Mis POKéMON son brutales!\n"
	.string "¡No es mi culpa si te arrepientes!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerIntro::
	.string "¡Hola, tú!\n"
	.string "¡Soy KINDLER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon1::
	.string "¿Sabes qué logró mi entrenamiento?\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Y bien, ¿qué me dices?\n"
	.string "¿Quieres formar un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerAccept::
	.string "¡Muy bien!\n"
	.string "Seguiré con el registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerReject::
	.string "Promete que serás mi pareja\n"
	.string "la próxima vez que nos veamos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperIntro::
	.string "I'm {STR_VAR_1}, and I'm a CAMPER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon1::
	.string "He criado un {STR_VAR_1}-\n"
	.string "que usa {STR_VAR_2} y un$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon2Ask::
	.string "{STR_VAR_1}- que usa {STR_VAR_2}.\p"
	.string "¿Crees que sería divertido unirnos?\n"
	.string "¡Seguro que sí!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperAccept::
	.string "¡Sí!\n"
	.string "¡Me voy a registrar!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperReject::
	.string "La próxima vez, ¿vale?\n"
	.string "Quiero estar en tu equipo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerIntro::
	.string "¡Hola!\n"
	.string "¡Soy {STR_VAR_1}, soy CAMPISTA!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon1::
	.string "Los POKéMON que he estado criando\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿Te interesa unirte a mí\n"
	.string "en un combate doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerAccept::
	.string "¡Vaya, gracias!\n"
	.string "Haré el registro ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerReject::
	.string "Sería genial unirme a ti\n"
	.string "en otra ocasión.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMIntro::
	.string "I'm PSYCHIC {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon1::
	.string "La pareja que he criado es\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿Te gustaría formar un equipo\n"
	.string "conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMAccept::
	.string "¡Claro que sí!\n"
	.string "¡Yo me encargo del registro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMReject::
	.string "Si nos volvemos a ver, ahí es\n"
	.string "cuando quisiera unirnos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFIntro::
	.string "Soy {STR_VAR_1}.\n"
	.string "Soy un PSÍQUICO.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon1::
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}--\n"
	.string "ellos son mis discípulos.\p"
	.string "¿No te intriga la idea de formar\n"
	.string "una pareja de combate?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFAccept::
	.string "Gracias.\n"
	.string "Iré a encargarme del registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFReject::
	.string "Espero que haya otra oportunidad\n"
	.string "de forjar una alianza.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFIntro::
	.string "I'm SCHOOL KID {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon1::
	.string "One {STR_VAR_1}-using {STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon2Ask::
	.string "y un usuario de {STR_VAR_1}\n"
	.string "{STR_VAR_2} es mi pareja POKéMON.\p"
	.string "¿Puedo ser tu pareja en\n"
	.string "un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFAccept::
	.string "¡Oh, gracias!\n"
	.string "¡Me registraré en el mostrador!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFReject::
	.string "¡Por favor!\n"
	.string "¿Puedo unirme la próxima vez?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFIntro::
	.string "¡Hola! ¡Me llamo {STR_VAR_1}!\n"
	.string "¡Soy CRIADORA POKéMON!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon1::
	.string "Los POKéMON que crié son\n"
	.string "{STR_VAR_2} que usa {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon2Ask::
	.string "un {STR_VAR_2} que usa {STR_VAR_1}.\p"
	.string "¿Te parece interesante?\n"
	.string "¿Hacemos un equipo doble entonces?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFAccept::
	.string "¡Muy bien!\n"
	.string "¡Deja el registro en mis manos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFReject::
	.string "Tienes que ir conmigo la próxima,\n"
	.string "¿Todo bien?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFIntro::
	.string "Soy {STR_VAR_1}, y me enorgullece\n"
	.string "decir que soy un POKéFAN.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon1::
	.string "Los lindos POKéMON que crié son\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon2Ask::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿No son los más tiernos?\n"
	.string "¡Deberíamos hacer un equipo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFAccept::
	.string "¡Gracias, cielo!\n"
	.string "¡Me iré a registrar ahora!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFReject::
	.string "Mis lindos POKéMON son los mejores,\n"
	.string "te lo advierto. ¡Qué molesto!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFIntro::
	.string "Hi, I'm SWIMMER {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon1::
	.string "One {STR_VAR_1}-using {STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon2Ask::
	.string "y un usuario de {STR_VAR_1}\n"
	.string "{STR_VAR_2} es lo que he entrenado.\p"
	.string "Tú y yo, hagamos un equipo doble.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFAccept::
	.string "¡Qué genial!\n"
	.string "Nos registraré a los dos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFReject::
	.string "Si nos volvemos a ver, me debes\n"
	.string "¡un combate en pareja!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMIntro::
	.string "¿Qué está pasando?\n"
	.string "Soy {STR_VAR_1}, soy TRIATLETA.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon1::
	.string "Tengo unos POKéMON decentes.\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Sería genial formar un equipo\n"
	.string "juntos, ¿qué te parece?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMAccept::
	.string "¡Exacto!\n"
	.string "Espera mientras me registro, ¿ok?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMReject::
	.string "Espero que me dejes unirme\n"
	.string "¿Qué tal la próxima vez?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFIntro::
	.string "I'm the TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon1::
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon2Ask::
	.string "Otro {STR_VAR_2} que sabe\n"
	.string "usar {STR_VAR_1}. Es mi pareja.\p"
	.string "¿Qué te parece?\n"
	.string "Seríamos un buen equipo, diría yo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFAccept::
	.string "¡Me gusta esa respuesta!\n"
	.string "¡Terminaré el registro rápido!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFReject::
	.string "Me darás otra oportunidad de formar\n"
	.string "una alianza, ¿verdad?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMIntro::
	.string "¡Hola! ¡Hola!\n"
	.string "¡Soy {STR_VAR_1}, soy NADADOR!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon1::
	.string "¡Mira lo que he estado criando!\n"
	.string "One {STR_VAR_2} with {STR_VAR_1} and$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon2Ask::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Genial, ¿eh?\n"
	.string "¡Sería genial formar un equipo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMAccept::
	.string "¡Muy agradecido!\n"
	.string "¡Haré lo del registro ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMReject::
	.string "Si nos volvemos a ver, tienes que\n"
	.string "unirte a mí. Lo harás, ¿verdad?$"

