BattleFrontier_BattleTowerMultiPartnerRoom_hns_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattleTowerMultiPartnerRoom_OnResume_hns
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition_hns
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp_hns
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame_hns
	.byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_OnResume_hns:
	pyramid_resetparty
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnTransition_hns:
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner_hns
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

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ChosePartner_hns::
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

BattleFrontier_BattleTowerMultiPartnerRoom_OnWarp_hns:
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth_hns
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TurnPlayerNorth_hns::
	turnobject LOCALID_PLAYER, DIR_NORTH
	end

BattleFrontier_BattleTowerMultiPartnerRoom_OnFrame_hns:
	map_script_2 VAR_TEMP_1, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom_hns
	map_script_2 VAR_TEMP_3, 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom_hns
	.2byte 0

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_ExitRoom_hns::
	lockall
	setvar VAR_TEMP_3, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator_hns
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterRoom_hns::
	lockall
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom_hns
	waitmovement 0
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit_hns
	waitmovement 0
	copyobjectxytoperm LOCALID_TOWER_PARTNER_ROOM_ATTENDANT
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner_hns, MSGBOX_DEFAULT
	special HealPlayerParty
	setvar VAR_TEMP_1, 1
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterRoom_hns:
	walk_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantBlockExit_hns:
	walk_left
	walk_in_place_faster_down
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Attendant_hns::
	lock
	faceplayer
	message BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner_hns
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge_hns
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner_hns2_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_QuitChallenge_hns::
	frontier_set FRONTIER_DATA_RECORD_DISABLED, TRUE
	goto BattleFrontier_BattleTower_EventScript_WarpToLobbyLost_hns
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_EnterElevator_hns::
	msgbox BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor 10, 1
	waitdooranim
	call BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator_hns
	closedoor 10, 1
	waitdooranim
	warp MAP_BATTLE_FRONTIER_BATTLE_TOWER_ELEVATOR_HNS, 1, 6
	waitstate
	releaseall
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator_hns::
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator_hns
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator_hnsEast_hns:
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator_hnsEast_hns
	waitmovement 0
	return

@ Unused
BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_MoveToElevator_hnsWest_hns:
	applymovement LOCALID_TOWER_PARTNER_ROOM_ATTENDANT, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator_hns
	applymovement LOCALID_PLAYER, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest_hns
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator_hns:
	walk_up
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEnterElevator_hnsEast_hns:
	walk_right
	walk_up
	set_invisible
	step_end

@ Functionally unused
BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PlayerEneterElevatorWest_hns:
	walk_left
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_AttendantEnterElevator_hns:
	walk_up
	set_invisible
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner1_hns::
	lock
	faceplayer
	setvar VAR_TEMP_2, 0
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner_hns
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner_hns::
	goto_if_set FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner_hns
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
	case 1, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner_hns
	case MULTI_B_PRESSED, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner_hns
	tower_dopartnermsg PARTNER_MSGID_ACCEPT
	waitmessage
	waitbuttonpress
	closemessage
	call_if_ne VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit_hns
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit_hnsSouth_hns
	removeobject VAR_LAST_TALKED
	setflag FLAG_CHOSEN_MULTI_BATTLE_NPC_PARTNER
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_TOWER_MULTI_PARTNER_ROOM_HNS, 10, 3
	waitstate
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_RejectPartner_hns::
	tower_dopartnermsg PARTNER_MSGID_REJECT
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit_hns::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit_hns
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_PartnerExit_hnsSouth_hns::
	applymovement VAR_LAST_TALKED, BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit_hnsSouth_hns
	waitmovement 0
	return

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit_hns:
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_Movement_PartnerExit_hnsSouth_hns:
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner2_hns::
	lock
	faceplayer
	setvar VAR_TEMP_2, 1
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner_hns
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner3_hns::
	lock
	faceplayer
	setvar VAR_TEMP_2, 2
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner_hns
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner4_hns::
	lock
	faceplayer
	setvar VAR_TEMP_2, 3
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner_hns
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner5_hns::
	lock
	faceplayer
	setvar VAR_TEMP_2, 4
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner_hns
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner6_hns::
	lock
	faceplayer
	setvar VAR_TEMP_2, 5
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner_hns
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner7_hns::
	lock
	faceplayer
	setvar VAR_TEMP_2, 6
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner_hns
	end

BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_Partner8_hns::
	lock
	faceplayer
	setvar VAR_TEMP_2, 7
	goto BattleFrontier_BattleTowerMultiPartnerRoom_EventScript_TalkToPotentialPartner_hns
	end

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner_hns:
	.string "Busca un compañero entre los\n"
	.string "ENTRENADORES reunidos aquí.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_QuitLookingForPartner_hns:
	.string "{PLAYER}, no has encontrado un\n"
	.string "compañero para tu equipo.\p"
	.string "¿Quieres dejar de buscar y\n"
	.string "volver al mostrador de recepción?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PleaseFindPartner_hns2_hns:
	.string "Entonces, busca un compañero entre\n"
	.string "ENTRENADORES reunidos aquí.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ThankYouForChoosingPartner_hns::
	.string "Gracias por elegir un compañero.\p"
	.string "Ahora te llevaré a tu\n"
	.string "SALA DE BATALLA MÚLTIPLE.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Intro_hns::
	.string "Soy el aprendiz nro. {STR_VAR_2} de {STR_VAR_1}.\n"
	.string "¡Puedes llamarme {STR_VAR_3}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon1_hns::
	.string "Por consejo de {STR_VAR_1}, traje\n"
	.string "un {STR_VAR_3} con {STR_VAR_2} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Mon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¡Por favor, hagamos un equipo doble!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Accept_hns::
	.string "¡Gracias!\n"
	.string "Iré a registrarme ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice1Reject_hns::
	.string "De verdad quería formar un equipo\n"
	.string "doble contigo, {PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Intro_hns::
	.string "Soy el aprendiz nro. {STR_VAR_2} de {STR_VAR_1}.\n"
	.string "Mi nombre es {STR_VAR_3}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon1_hns::
	.string "Seguí el consejo de {STR_VAR_1} y elegí\n"
	.string "un {STR_VAR_3} con {STR_VAR_2} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Mon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¡Por favor, hagamos un equipo doble!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Accept_hns::
	.string "¡Muchas gracias!\n"
	.string "¡Terminaré el registro rápido!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_UnusedApprentice2Reject_hns::
	.string "{PLAYER}, esperaba que pudiera\n"
	.string "ser tu compañero…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Intro_hns::
	.string "Eh, me llamo {STR_VAR_3} y soy\n"
	.string "el aprendiz {STR_VAR_2} de {STR_VAR_1}.\p"
	.string "Snif…\p"
	.string "¡Lo siento!\n"
	.string "¡Tanta tensión me hace llorar…!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon1_hns::
	.string "{STR_VAR_3} me aconsejó, así que tengo\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Mon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "Snif…\n"
	.string "¡Por favor, haz equipo conmigo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Accept_hns::
	.string "¿Ah, sí? ¿Lo harás?\n"
	.string "¡Genial! ¡Increíble! ¡Awoooh!\p"
	.string "Oh... lo siento...\n"
	.string "Estoy tan feliz que lloro...\p"
	.string "Iré a registrarme ahora mismo.\n"
	.string "¡Por favor, no te vayas!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice1Reject_hns::
	.string "Oh, p-pero...\n"
	.string "Snif... ¡Buaaaaaah!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Intro_hns::
	.string "¡Hola! ¡Soy {STR_VAR_3}!\n"
	.string "¡Soy el aprendiz {STR_VAR_2} de {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon1_hns::
	.string "{STR_VAR_3} recomendó a mi equipo.\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Mon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1},\n"
	.string "¡eso es lo que tengo! Genial, ¿no?\p"
	.string "¡Así que vamos!\n"
	.string "¡Hagamos un equipo doble!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Accept_hns::
	.string "¡Súper! ¡Genial!\n"
	.string "Bien, iré a registrarme, ¿sí?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice2Reject_hns::
	.string "Ay, ¿por qué?\n"
	.string "¡Quería ser tu pareja, {PLAYER}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Intro_hns::
	.string "Soy {STR_VAR_3}, el aprendiz n.º {STR_VAR_2}\n"
	.string "¡del famoso {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon1_hns::
	.string "Le pedí consejo a {STR_VAR_3}.\n"
	.string "One {STR_VAR_1}-using {STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Mon2Ask_hns::
	.string "y un {STR_VAR_2} con {STR_VAR_1},\n"
	.string "esa es mi pareja.\p"
	.string "Por favor, ¿te unirías a mí en\n"
	.string "un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Accept_hns::
	.string "¡Gracias!\n"
	.string "¡Me registraré ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice3Reject_hns::
	.string "{PLAYER}, esperaba unirme a ti\n"
	.string "en un equipo doble…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Intro_hns::
	.string "Eh… Me alegra sinceramente que\n"
	.string "te tomes el tiempo de hablarme.\p"
	.string "Soy {STR_VAR_3}.\n"
	.string "Soy el aprendiz nro. {STR_VAR_2} de {STR_VAR_1}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon1_hns::
	.string "{STR_VAR_3} me dio un consejo.\n"
	.string "Estoy muy agradecido por ello.\p"
	.string "Tengo un equipo de un {STR_VAR_2}\n"
	.string "con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Mon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\n"
	.string "Sé que pido demasiado...\p"
	.string "No creo que quieras hacerlo,\n"
	.string "¡¿pero puedo ir contigo?!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Accept_hns::
	.string "¡¿En serio?! ¡No lo puedo creer!\n"
	.string "¡No creo que me dejes acompañarte!\l"
	.string "¡Yo... no te fallaré!\p"
	.string "Eh... si está bien, iré a registrarme\n"
	.string "¡en este mismo instante!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice4Reject_hns::
	.string "Oh…\n"
	.string "No creía ser lo suficiente...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Intro_hns::
	.string "Hola, soy {STR_VAR_3}.\n"
	.string "¡Soy el aprendiz {STR_VAR_2} de {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon1_hns::
	.string "{STR_VAR_3} me dijo que sería\n"
	.string "bueno para este equipo:\l"
	.string "un {STR_VAR_2} que use {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Mon2Ask_hns::
	.string "y un {STR_VAR_2} que sepa\n"
	.string "usar {STR_VAR_1}.\p"
	.string "Nada mal, ¿eh?\n"
	.string "¿Quieres que me una a tu equipo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Accept_hns::
	.string "¡Vale, me alegra acompañarte!\n"
	.string "¡Espero que no lo arruines todo!\l"
	.string "Me registraré ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice5Reject_hns::
	.string "¿Eh? ¿Por qué me rechazaste?\n"
	.string "¡No sabes juzgar a la gente!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Intro_hns::
	.string "Soy {STR_VAR_3} y soy TRIATLETA.\n"
	.string "Estoy ocupado todo el día trotando,\l"
	.string "entrenando y rapeando.\p"
	.string "I also happen to be {STR_VAR_1}'s\n"
	.string "no. {STR_VAR_2} apprentice.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon1_hns::
	.string "Esto es lo que {STR_VAR_3} sugirió.\n"
	.string "One {STR_VAR_1}-using {STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Mon2Ask_hns::
	.string "y un usuario de {STR_VAR_1}\n"
	.string "{STR_VAR_2}.\p"
	.string "Me esfuerzo mucho en criarlos,\n"
	.string "aunque esté muy ocupado.\p"
	.string "¡Hagamos un equipo doble\n"
	.string "y probemos suerte!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Accept_hns::
	.string "¡Gracias, esa es la actitud!\n"
	.string "Espera mientras me registro, ¿sí?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice6Reject_hns::
	.string "¡Saqué tiempo de mi agenda\n"
	.string "para venir! ¡Dame un respiro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Intro_hns::
	.string "Hi!\n"
	.string "¿Cómo va todo?\p"
	.string "I'm {STR_VAR_3}, {STR_VAR_1}'s\n"
	.string "no. {STR_VAR_2} apprentice. Glad to meet you!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon1_hns::
	.string "¡Oye, escucha! Tienes que saber\n"
	.string "del POKéMON que recomendó {STR_VAR_3}.\l"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Mon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\n"
	.string "¡Claro que los crié superbamente!\p"
	.string "Entonces, ¿quieres hacer equipo?\n"
	.string "¡Seguro que seremos un gran combo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Accept_hns::
	.string "¡Súper, creo que será divertido!\n"
	.string "¡Iré a registrarme!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice7Reject_hns::
	.string "¡Ay, qué malo eres!\n"
	.string "Vengo recomendado, ¿sabes?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Intro_hns::
	.string "Permíteme presentarme.\n"
	.string "Soy {STR_VAR_3}.\p"
	.string "Sirvo como el {STR_VAR_1} de\n"
	.string "no. {STR_VAR_2} apprentice.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon1_hns::
	.string "Busqué el sabio consejo de\n"
	.string "{STR_VAR_3} y crié a mi equipo\l"
	.string "de un {STR_VAR_2} con {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Mon2Ask_hns::
	.string "y un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¡Acepta luchar en pareja conmigo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Accept_hns::
	.string "¡Oh... estoy encantado!\n"
	.string "¡Prometo dar lo mejor de mí!\p"
	.string "¡Claro que nos registraré!\n"
	.string "¡Espera, por favor!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice8Reject_hns::
	.string "Tenía esperanzas de unirme a ti,\n"
	.string "{PLAYER}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Intro_hns::
	.string "¡Ay! ¡Me hablaste!\n"
	.string "¡Estoy... estoy feliz!\p"
	.string "I'm {STR_VAR_3}! I'm {STR_VAR_1}'s\n"
	.string "no. {STR_VAR_2} apprentice!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon1_hns::
	.string "Por consejo de {STR_VAR_3}, entrené\n"
	.string "un {STR_VAR_2} que use {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Mon2Ask_hns::
	.string "y un usuario de {STR_VAR_1}\n"
	.string "{STR_VAR_2}.\p"
	.string "Por favor, ¿cumples mi deseo?\n"
	.string "¡Quiero ser tu pareja de combate!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Accept_hns::
	.string "¡Ay! ¡Me... me siento mareada!\n"
	.string "¡Muchísimas gracias!\l"
	.string "¡Iré a registrarnos ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice9Reject_hns::
	.string "¡Waaah! ¿No tienes piedad?\n"
	.string "Pero eso te hace más genial...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Intro_hns::
	.string "¡Yeehaw! Soy el aprendiz de {STR_VAR_1}\n"
	.string "¡el aprendiz nro. {STR_VAR_2}!\p"
	.string "¡Me llamo {STR_VAR_3}, hola, hola!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon1_hns::
	.string "Mi mentor {STR_VAR_3} recomendó\n"
	.string "un maestro {STR_VAR_2} de {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Mon2Ask_hns::
	.string "y un maestro de {STR_VAR_1}\n"
	.string "{STR_VAR_2}.\p"
	.string "Cosas buenas, ¿eh?\n"
	.string "¿Serás mi compañero, verdad?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Accept_hns::
	.string "¡Bien, excelente!\n"
	.string "¡Haré el registro rápidamente!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice10Reject_hns::
	.string "¡Gwaaah!\n"
	.string "¡Eres muy calculador, {PLAYER}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Intro_hns::
	.string "¡Oye! ¡Hay un gran problema! Es\n"
	.string "¡el último día de la BATTLE TOWER!\p"
	.string "… … … … … …\n"
	.string "¡Solo estoy bromeando!\p"
	.string "Me llaman {STR_VAR_3} ¡y yo también!\n"
	.string "¡Soy el aprendiz 1,000 de {STR_VAR_1}!\l"
	.string "¡En realidad, soy el no. {STR_VAR_2}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon1_hns::
	.string "{STR_VAR_3} me dio un consejo.\n"
	.string "{STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Mon2Ask_hns::
	.string "{STR_VAR_2} con {STR_VAR_1}.\n"
	.string "¡Tengo diez de cada tipo!\l"
	.string "¡En realidad, solo uno de cada!\p"
	.string "¿Qué te parece?\n"
	.string "¿Quieres batallas dobles conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Accept_hns::
	.string "¡Súper!\n"
	.string "¡Te daré un POKéMON en agradecimiento!\p"
	.string "¡Es broma! Pero iré a hacer\n"
	.string "el registro, ¿está bien?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice11Reject_hns::
	.string "¡Qué frío! ¡Tendré que arrasar\n"
	.string "la BATTLE TOWER por eso!\p"
	.string "¡Claro que no lo haré!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Intro_hns::
	.string "¡Hola! ¡Llego con todo el ritmo!\n"
	.string "¡A mis POKéMON yo controlo!\p"
	.string "Soy {STR_VAR_3}, el MARINERO rapero.\n"
	.string "¡No me confundas con un llorón!\p"
	.string "Soy el aprendiz nro. {STR_VAR_2} de {STR_VAR_1}.\n"
	.string "¡No me subestimes tan rápido!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon1_hns::
	.string "Con el consejo de {STR_VAR_3} yo\n"
	.string "seguí, ¡y mi equipo así surgió!\l"
	.string "One {STR_VAR_1}-using {STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Mon2Ask_hns::
	.string "y un usuario de {STR_VAR_1}\n"
	.string "{STR_VAR_2}!\p"
	.string "Nuestro encuentro hay que anotar,\n"
	.string "¡con una victoria en pareja celebrar!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Accept_hns::
	.string "¡Oye, oye, me gusta tu estilo!\n"
	.string "¡Yo mismo iré a registrarlos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice12Reject_hns::
	.string "¡Oh, hola, {PLAYER}, eso fue frío!\n"
	.string "¡Si me permites ser tan audaz!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Intro_hns::
	.string "¡Yippee-yahoo!\n"
	.string "¡No huyas! ¡Solo me divertía!\p"
	.string "¡Hola! ¡Soy {STR_VAR_3}!\n"
	.string "¡Soy el aprendiz {STR_VAR_2} de {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon1_hns::
	.string "{STR_VAR_3} me dijo qué hacer.\n"
	.string "Así que un {STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Mon2Ask_hns::
	.string "y un usuario de {STR_VAR_1}\n"
	.string "{STR_VAR_2}, es el que elegí.\p"
	.string "Entonces, ¿qué dices?\n"
	.string "¡Vamos, dame una alegría!\p"
	.string "¡Por favor, te lo ruego!\n"
	.string "¡Déjame ir, no me ignores!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Accept_hns::
	.string "¡Siii! ¡La suerte está conmigo!\n"
	.string "¡Eso me hace muy feliz!\p"
	.string "Antes de ir a la batalla,\n"
	.string "¡iré a registrarme ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice13Reject_hns::
	.string "¿Me estás rechazando?\n"
	.string "{PLAYER}, ¡me pones triste!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Intro_hns::
	.string "¡Cof, cof!\p"
	.string "Oh, perdón, tengo un resfriado.\n"
	.string "Pero mis POKéMON están bien.\p"
	.string "Me llamo {STR_VAR_3}, soy de {STR_VAR_1}\n"
	.string "aprendiz de {STR_VAR_2}. ¡Cof!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon1_hns::
	.string "Seguí el consejo de {STR_VAR_3}\n"
	.string "y armé mi equipo de\l"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Mon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "Los entrené cada día,\n"
	.string "incluso con viento y lluvia.\p"
	.string "Por eso tengo este resfriado,\n"
	.string "creo.\p"
	.string "Así soy yo.\n"
	.string "¿Quieres ser mi pareja de combate?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Accept_hns::
	.string "¡Gracias, te lo agradezco!\n"
	.string "¡Cof, cof!\l"
	.string "Espera mientras voy a registrarme.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice14Reject_hns::
	.string "Oh, ¿no quieres?\n"
	.string "{PLAYER}, creo que seríamos un gran par.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Intro_hns::
	.string "¡Oh, hola!\n"
	.string "Esto pone los nervios de punta.\p"
	.string "Soy {STR_VAR_3}.\n"
	.string "Soy el aprendiz nro. {STR_VAR_2} de {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon1_hns::
	.string "{STR_VAR_3} dijo que este equipo es bueno--\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Mon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "Me da un poco de vergüenza,\n"
	.string "¿pero me dejarías acompañarte?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Accept_hns::
	.string "¡Oh, cielos, gracias!\n"
	.string "¡Me da pena, pero daré lo mejor!\p"
	.string "Iré a hacer el registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice15Reject_hns::
	.string "¡Oh, por favor, no digas que no!\n"
	.string "Ya me siento bastante cohibido…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Intro_hns::
	.string "Soy {STR_VAR_3}, y no es mentira.\n"
	.string "Soy el aprendiz nro. {STR_VAR_2} de {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon1_hns::
	.string "{STR_VAR_3} recomendó a mi equipo.\p"
	.string "Como el consejo parecía sincero,\n"
	.string "decidí traer conmigo a\l"
	.string "mi {STR_VAR_2} de tipo {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Mon2Ask_hns::
	.string "mi {STR_VAR_2} de tipo {STR_VAR_1}.\p"
	.string "Si es posible, me gustaría que me\n"
	.string "aceptes como tu pareja de equipo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Accept_hns::
	.string "¿De verdad me aceptarás?\n"
	.string "De lo contrario sería terrible.\p"
	.string "Pero ya que aceptaste, está bien.\n"
	.string "Iré a registrarnos a los dos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_Apprentice16Reject_hns::
	.string "¿Hm? ¿Por qué rechazarías?\n"
	.string "¿Crees que esto es una broma?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassIntro_hns::
	.string "I'm {STR_VAR_1}, and I'm a LASS!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon1_hns::
	.string "Tengo un {STR_VAR_2}\n"
	.string "que usa {STR_VAR_1} y un$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassMon2Ask_hns::
	.string "{STR_VAR_2} que usa {STR_VAR_1}.\n"
	.string "Eso es lo que traigo conmigo.\p"
	.string "¿Quieres ser mi compañero?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassAccept_hns::
	.string "¡Gracias!\n"
	.string "¡Yo haré el registro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LassReject_hns::
	.string "¿No quieres ser mi compañero?\n"
	.string "¡Luego te arrepentirás!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterIntro_hns::
	.string "¡Hola!\p"
	.string "¡Soy el JOVEN {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon1_hns::
	.string "¿Quieres saber qué tengo?\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Serás mi compañero de equipo,\n"
	.string "¿verdad?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterAccept_hns::
	.string "¡Súper!\n"
	.string "Iré a registrarme, ¿está bien?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_YoungsterReject_hns::
	.string "¡Ay! Si formaras un equipo con\n"
	.string "mis POKéMON, ¡seríamos invencibles!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerIntro_hns::
	.string "¡Yahoo!\n"
	.string "¡Soy el EXCURSIONISTA {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon1_hns::
	.string "¿Sabes qué traigo conmigo?\n"
	.string "¡Mi {STR_VAR_2} de tipo {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerMon2Ask_hns::
	.string "mi {STR_VAR_2} de tipo {STR_VAR_1}!\p"
	.string "Suena bien, ¿no?\n"
	.string "¿Quieres formar un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerAccept_hns::
	.string "¡Yahoo!\n"
	.string "Iré a hacer el registro entonces.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HikerReject_hns::
	.string "Me hubiera gustado luchar contigo\n"
	.string "a mi lado.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyIntro_hns::
	.string "¡Hola!\n"
	.string "¡Soy {STR_VAR_1} y soy una BEAUTY!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon1_hns::
	.string "¿Sabes qué he estado criando?\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Qué te parece?\n"
	.string "¿Hacemos un equipo doble juntos?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyAccept_hns::
	.string "¡Maravilloso!\n"
	.string "¡Haré el registro ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BeautyReject_hns::
	.string "¡Qué decepción!\p"
	.string "Nosotros dos juntos... habríamos\n"
	.string "¡sido los mejores!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanIntro_hns::
	.string "Yo!\p"
	.string "¿Sabes quién soy?\n"
	.string "¡Soy el PESCADOR {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon1_hns::
	.string "Tengo un equipo de un\n"
	.string "{STR_VAR_2} que usa {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanMon2Ask_hns::
	.string "un {STR_VAR_2} que usa {STR_VAR_1}.\p"
	.string "Entonces, ¿qué dices?\n"
	.string "¿Lucharás a mi lado?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanAccept_hns::
	.string "¡Bien, muy bien!\n"
	.string "¡Déjamelo a mí!\p"
	.string "Iré a registrarnos ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_FishermanReject_hns::
	.string "We matched up perfectly, too…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyIntro_hns::
	.string "Gusto en conocerte.\n"
	.string "Soy {STR_VAR_1}, una DAMA.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon1_hns::
	.string "Me acompaña un equipo de\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyMon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "Espero contar con tu aprobación.\n"
	.string "Pues deseo que seas mi pareja.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyAccept_hns::
	.string "Te lo agradezco sinceramente.\n"
	.string "Yo me encargo del registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_LadyReject_hns::
	.string "Seguro que te arrepentirás de no\n"
	.string "tenerme como tu pareja.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFIntro_hns::
	.string "I'm TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon1_hns::
	.string "Lo que tengo...\nUn {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\n"
	.string "¡Ese es mi compañero!\p"
	.string "¡Por favor!\n"
	.string "¿Quieres formar un equipo conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFAccept_hns::
	.string "¡Vaya, gracias!\n"
	.string "Iré a registrarme al mostrador.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteFReject_hns::
	.string "Nosotros dos juntos, seguro que\n"
	.string "¡habríamos sido fuertes!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherIntro_hns::
	.string "¡Hola!\n"
	.string "¡Soy el CAZABICHOS {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon1_hns::
	.string "¡Mira lo que tengo!\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¡Oye, escucha!\n"
	.string "¿Quieres formar un equipo conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherAccept_hns::
	.string "¡Te atrapé!\p"
	.string "Iré a hacer el registro\n"
	.string "en el mostrador.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugCatcherReject_hns::
	.string "Ay, mis POKéMON son geniales.\n"
	.string "¡Espero que no te arrepientas!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMIntro_hns::
	.string "¡Buen día!\n"
	.string "I'm SCHOOL KID {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon1_hns::
	.string "He estado criando un\n"
	.string "{STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMMon2Ask_hns::
	.string "y un {STR_VAR_2} que usa\n"
	.string "{STR_VAR_1}.\p"
	.string "No están mal, ¿verdad?\n"
	.string "¿Quieres formar un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMAccept_hns::
	.string "¡Muchas gracias!\n"
	.string "Terminaré el registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidMReject_hns::
	.string "Qué mal...\p"
	.string "Esperaba poder aprender\n"
	.string "de ti como tu compañero...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyIntro_hns::
	.string "¡Hola! ¡Déjame presentarme!\n"
	.string "¡Soy el RICO {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon1_hns::
	.string "¡Adivina qué tengo!\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Estoy dispuesto a darte la chance\n"
	.string "de estar en un equipo doble conmigo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyAccept_hns::
	.string "¡Buena decisión!\p"
	.string "Terminaré el registro\n"
	.string "¡Rápido, procesa!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RichBoyReject_hns::
	.string "¿Me rechazarías a mí?\n"
	.string "¡Seguro que te arrepentirás de eso!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltIntro_hns::
	.string "¡Hiyah!\n"
	.string "Soy el CINTURÓN NEGRO {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon1_hns::
	.string "Como mis compañeros, tengo\n"
	.string "un {STR_VAR_2} que usa {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltMon2Ask_hns::
	.string "y un {STR_VAR_2} que usa\n"
	.string "{STR_VAR_1}.\p"
	.string "¡Por favor, cumple mi deseo!\n"
	.string "¡Deja que sea tu pareja de combate!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltAccept_hns::
	.string "¡Hiyah!\n"
	.string "¡Iré a registrarme ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BlackBeltReject_hns::
	.string "Ya veo... Espero tener una oportunidad\n"
	.string "la próxima vez que nos veamos…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFIntro_hns::
	.string "¡Hola!\n"
	.string "¡Soy {STR_VAR_1}, soy un TUBER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon1_hns::
	.string "Te diré lo que tengo.\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\n"
	.string "¿Puedo estar en tu equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFAccept_hns::
	.string "¡Gracias!\n"
	.string "¡Iré a registrarnos ahora!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberFReject_hns::
	.string "Si hubiéramos sido compañeros,\n"
	.string "¡seríamos muy fuertes!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacIntro_hns::
	.string "Saludos...\n"
	.string "Soy la BRUJA {STR_VAR_1}…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon1_hns::
	.string "Llevo conmigo un {STR_VAR_1}\n"
	.string "{STR_VAR_2} junto con uno$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacMon2Ask_hns::
	.string "{STR_VAR_2} que usa {STR_VAR_1}…\p"
	.string "Te lo ruego...\n"
	.string "¡Únete a mi equipo doble!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacAccept_hns::
	.string "Te lo agradezco...\n"
	.string "Nos inscribiré ahora mismo...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_HexManiacReject_hns::
	.string "I so longed to join you…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMIntro_hns::
	.string "¿Cómo estás? Soy {STR_VAR_1},\n"
	.string "¡y soy CRIADOR POKéMON!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon1_hns::
	.string "¡Estoy criando unos muy buenos!\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Qué te parece?\n"
	.string "¿Quieres formar un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMAccept_hns::
	.string "¡Muchas gracias!\p"
	.string "Iré a encargarme del registro,\n"
	.string "¡así que espera justo aquí!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederMReject_hns::
	.string "Tenía muchas ganas de ser\n"
	.string "tu compañero…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFIntro_hns::
	.string "¡Hola, qué tal!\n"
	.string "I'm TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon1_hns::
	.string "¿Quieres ver qué POKéMON tengo?\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Y bien?\n"
	.string "¿Quieres hacer equipo conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFAccept_hns::
	.string "¡Buen trabajo!\p"
	.string "¡Haré el registro rápido\n"
	.string "para terminar ya!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteFReject_hns::
	.string "Tú y yo habríamos sido los mejores.\n"
	.string "Es una lástima…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMIntro_hns::
	.string "¡Hola! ¡Mi nombre es {STR_VAR_1}!\n"
	.string "¡Soy TRIATLETA!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon1_hns::
	.string "Corro con mi equipo resistente--\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "No está mal, ¿eh?\n"
	.string "¡Deberíamos ser un equipo doble!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMAccept_hns::
	.string "¡Muy bien!\n"
	.string "¡Me registraré en un instante!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RunningTriathleteMReject_hns::
	.string "De verdad quería luchar como tu\n"
	.string "compañero de equipo doble…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlIntro_hns::
	.string "I'm BATTLE GIRL {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon1_hns::
	.string "He estado entrenando a mi\n"
	.string "{STR_VAR_2} que usa {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlMon2Ask_hns::
	.string "{STR_VAR_2} usando {STR_VAR_1}!\p"
	.string "¿Te gusta esa combinación?\n"
	.string "¿Qué tal si nos unimos?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlAccept_hns::
	.string "¡Vaya, gracias!\p"
	.string "Haré el registro\n"
	.string "¡ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BattleGirlReject_hns::
	.string "Pensé que contigo podríamos formar\n"
	.string "el mejor equipo doble…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMIntro_hns::
	.string "I'm TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon1_hns::
	.string "Tengo un {STR_VAR_2}\n"
	.string "que sabe usar {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMMon2Ask_hns::
	.string "¡y un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Podríamos ser un equipo doble.\n"
	.string "¿No sería genial?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMAccept_hns::
	.string "¡Gracias!\p"
	.string "Iré a registrarnos, y eso es\n"
	.string "¡ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CyclingTriathleteMReject_hns::
	.string "Vaya, qué mal. Habríamos sido\n"
	.string "¡el equipo doble más fuerte!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMIntro_hns::
	.string "Me?\n"
	.string "¡Soy TUBER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon1_hns::
	.string "¿Qué traigo conmigo?\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Hola?\n"
	.string "Te unirás a mi equipo, ¿verdad?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMAccept_hns::
	.string "¡Está bien!\p"
	.string "¡Iré a registrarme!\n"
	.string "¡Seamos excelentes juntos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_TuberMReject_hns::
	.string "Mis POKéMON son fuertes, seguro...\n"
	.string "Lástima que no quieras unirte.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristIntro_hns::
	.string "¡Siii-hey!\n"
	.string "¡Llámame GUITARIST {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon1_hns::
	.string "¡Mira mi séquito!\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¡Siii-hey! Bastante salvaje, ¿no?\n"
	.string "¡Haremos un dúo en equipo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristAccept_hns::
	.string "¡Siii! ¡Exacto!\n"
	.string "¡Haré el registro ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GuitaristReject_hns::
	.string "¡Mis POKéMON son fuertes!\n"
	.string "¡Te arrepentirás, te lo digo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanIntro_hns::
	.string "Mucho gusto.\n"
	.string "Soy {STR_VAR_1}, un CABALLERO.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon1_hns::
	.string "Me acompaña mi fiel\n"
	.string "{STR_VAR_2} que usa {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanMon2Ask_hns::
	.string "un {STR_VAR_2} que usa {STR_VAR_1}.\p"
	.string "¿Me permitiría ser su pareja\n"
	.string "en un combate en equipo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanAccept_hns::
	.string "Ah, gracias por su confianza.\n"
	.string "Terminaré con el registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_GentlemanReject_hns::
	.string "Eso es muy lamentable...\p"
	.string "Esperaré con ansias la próxima\n"
	.string "oportunidad...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMIntro_hns::
	.string "Hola, soy {STR_VAR_1},\n"
	.string "¡y soy un POKéFAN!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon1_hns::
	.string "Tengo conmigo un {STR_VAR_2}\n"
	.string "que sabe el movimiento {STR_VAR_1}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMMon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿Te gusta lo que ves?\n"
	.string "¿Quieres ser mi pareja de equipo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMAccept_hns::
	.string "¡Gracias!\n"
	.string "¡Yo me encargo del registro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanMReject_hns::
	.string "Mis POKéMON son de primer nivel...\n"
	.string "Lástima que no puedas apreciarlo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMIntro_hns::
	.string "Hm!\n"
	.string "¡Soy {STR_VAR_1}, y soy un EXPERTO!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon1_hns::
	.string "Los POKéMON que he entrenado son\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Qué dices de hacer equipo conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMAccept_hns::
	.string "Hm!\n"
	.string "¡Nos registraré ahora mismo!\l"
	.string "¡Demos lo mejor de nosotros!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertMReject_hns::
	.string "Espero que tu elección sea\n"
	.string "realmente la correcta…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFIntro_hns::
	.string "Hola, hola.\n"
	.string "Soy {STR_VAR_1}, y soy un EXPERTO.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon1_hns::
	.string "He criado bien a mis POKéMON.\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFMon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}--\n"
	.string "eso es lo que tengo.\p"
	.string "¿No quieres hacer equipo conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFAccept_hns::
	.string "Bien, bien.\n"
	.string "Haré el registro ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ExpertFReject_hns::
	.string "Tal vez podamos formar un equipo la\n"
	.string "próxima vez que nos veamos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerIntro_hns::
	.string "I'm DRAGON TAMER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon1_hns::
	.string "El equipo que he estado entrenando es\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Qué te parece?\n"
	.string "¿Quieres ser mi compañero?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerAccept_hns::
	.string "¡Está bien, daré lo mejor de mí!\n"
	.string "Iré a registrarme ahora, ¿vale?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_DragonTamerReject_hns::
	.string "¡No hallarás a muchos compañeros más\n"
	.string "fuertes que yo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperIntro_hns::
	.string "I'm BIRD KEEPER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon1_hns::
	.string "¿Qué POKéMON tengo?\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperMon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿No crees que haríamos un buen\n"
	.string "equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperAccept_hns::
	.string "¡Genial, gracias!\n"
	.string "¡Yo me encargo del registro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BirdKeeperReject_hns::
	.string "Mis POKéMON y yo somos fuertes.\n"
	.string "Qué decepción.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyIntro_hns::
	.string "I'm NINJA BOY {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon1_hns::
	.string "Mi equipo POKéMON consiste en uno\n"
	.string "{STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¡Hagamos un equipo doble juntos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyAccept_hns::
	.string "¡Súper!\n"
	.string "¡Déjame ir a registrarme!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_NinjaBoyReject_hns::
	.string "Lamentarás no tener a mis fuertes\n"
	.string "¡POKéMON a tu lado!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyIntro_hns::
	.string "¡Hola!\n"
	.string "¡Soy la SEÑORA SOMBRILLA {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon1_hns::
	.string "Me acompañan mis {STR_VAR_2},\n"
	.string "que usa {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyMon2Ask_hns::
	.string "un {STR_VAR_2} que usa\n"
	.string "{STR_VAR_1}.\p"
	.string "¿No son lindos?\n"
	.string "¿Quieres unirte en un combate doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyAccept_hns::
	.string "¡Muchas gracias!\p"
	.string "Iré a registrarme al mostrador.\n"
	.string "¡No nos decepcionemos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_ParasolLadyReject_hns::
	.string "Mis POKéMON son muy fuertes.\n"
	.string "Qué decepción...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacIntro_hns::
	.string "Hola.\n"
	.string "¡Soy {STR_VAR_1}, un FANÁTICO BICHOS!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon1_hns::
	.string "He hallado mis POKéMON, sí.\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacMon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}--\n"
	.string "son los que he encontrado.\p"
	.string "¿Te interesa formar parte?\n"
	.string "un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacAccept_hns::
	.string "¡Está bien!\n"
	.string "¡Entendido!\p"
	.string "¡No tardaré con el registro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_BugManiacReject_hns::
	.string "Con los POKéMON que hallé, no\n"
	.string "habríamos perdido...$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorIntro_hns::
	.string "¡Hola, marinero!\n"
	.string "¡Soy el MARINERO {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon1_hns::
	.string "¡Mira mi mayor orgullo y alegría!\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Claro que no me vas a rechazar,\n"
	.string "haremos equipo, ¿verdad?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorAccept_hns::
	.string "¡No esperaba menos de ti!\n"
	.string "Iré a registrarme ahora.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SailorReject_hns::
	.string "¡Habríamos arrasado con toda\n"
	.string "la oposición! ¡Qué mal!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorIntro_hns::
	.string "Hola, soy {STR_VAR_1}.\n"
	.string "Soy COLECCIONISTA.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon1_hns::
	.string "Las joyas de mi colección son\n"
	.string "mi {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Genial, ¿eh?\n"
	.string "Deberíamos estar en el mismo equipo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorAccept_hns::
	.string "¡Oh, sí!\p"
	.string "Bueno, no perdamos tiempo.\n"
	.string "Iré a registrarnos los dos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CollectorReject_hns::
	.string "Vaya, eso es decepcionante.\n"
	.string "No valoras a mis POKéMON.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMIntro_hns::
	.string "Hola, soy {STR_VAR_1}.\n"
	.string "Soy un POKéMON RANGER.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon1_hns::
	.string "Me acompañan algunos\n"
	.string "{STR_VAR_2} que usa {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿No crees que haríamos un equipo\n"
	.string "equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMAccept_hns::
	.string "¡Eso es genial!\n"
	.string "Me encargo del registro ahora.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerMReject_hns::
	.string "La próxima, elige a mis POKéMON,\n"
	.string "¿Lo harás?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFIntro_hns::
	.string "Mi nombre es {STR_VAR_1}.\n"
	.string "¡Soy un POKéMON RANGER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon1_hns::
	.string "Te hablaré de mi equipo. Tengo\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "¿Te gustaría formar un equipo\n"
	.string "con mi pequeño grupo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFAccept_hns::
	.string "¡Estaremos en nuestra mejor forma!\n"
	.string "¡Haré el registro rápido!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnRangerFReject_hns::
	.string "Espero que elijas a mis POKéMON\n"
	.string "la próxima vez.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyIntro_hns::
	.string "Mucho gusto. Soy {STR_VAR_1}.\n"
	.string "Me considero una AROMA LADY.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon1_hns::
	.string "Viajo con un {STR_VAR_2}\n"
	.string "que usa {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyMon2Ask_hns::
	.string "un {STR_VAR_2} que usa\n"
	.string "{STR_VAR_1}.\p"
	.string "Espero que te llamen la atención.\n"
	.string "¿Te gustaría ser mi compañero?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyAccept_hns::
	.string "Me honra que hayas aceptado.\n"
	.string "Iré a registrarme ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_AromaLadyReject_hns::
	.string "Sería maravilloso que pudiéramos\n"
	.string "ser un equipo la próxima vez.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacIntro_hns::
	.string "¿Quieres saber quién soy?\n"
	.string "¡Soy {STR_VAR_1}, el FAN RUINAS!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon1_hns::
	.string "Los POKéMON que traigo conmigo son\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Intrigantes, ¿eh?\n"
	.string "¿Qué tal si somos compañeros?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacAccept_hns::
	.string "¡Es una decisión acertada!\n"
	.string "Iré a hacer el papeleo de registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_RuinManiacReject_hns::
	.string "Hmm…\n"
	.string "Creo que mis POKéMON son fuertes…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMIntro_hns::
	.string "I'm COOLTRAINER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon1_hns::
	.string "Los POKéMON que tengo ahora son\n"
	.string "{STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMMon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\n"
	.string "geniales, ¿no?\p"
	.string "¿No crees que sería genial\n"
	.string "si formáramos un equipo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMAccept_hns::
	.string "¡Genial!\n"
	.string "¡Haré el registro en un santiamén!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerMReject_hns::
	.string "Pensé que formaríamos\n"
	.string "el mejor equipo de la historia.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFIntro_hns::
	.string "I'm COOLTRAINER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon1_hns::
	.string "El equipo que he criado tiene uno\n"
	.string "{STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFMon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿Te parece bien?\n"
	.string "¿Y si somos pareja de combate?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFAccept_hns::
	.string "¡Me parece genial!\n"
	.string "Mejor hago el registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CoolTrainerFReject_hns::
	.string "Pensaba en lo fuertes que\n"
	.string "seríamos como equipo…$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacIntro_hns::
	.string "¡Hola!\n"
	.string "¡Soy {STR_VAR_1}, el POKéMANÍACO!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon1_hns::
	.string "¿Qué tiene alguien como yo?\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacMon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1},\n"
	.string "¡Pues esto!\p"
	.string "¡Hagámoslo!\n"
	.string "¡Daremos guerra en equipo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacAccept_hns::
	.string "¡Buena idea!\n"
	.string "¡Nos registraré a los dos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokemaniacReject_hns::
	.string "¡Mis POKéMON son brutales!\n"
	.string "¡No es mi culpa si te arrepientes!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerIntro_hns::
	.string "¡Hola, tú!\n"
	.string "¡Soy KINDLER {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon1_hns::
	.string "¿Sabes qué logró mi entrenamiento?\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Y bien, ¿qué me dices?\n"
	.string "¿Quieres formar un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerAccept_hns::
	.string "¡Muy bien!\n"
	.string "Seguiré con el registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_KindlerReject_hns::
	.string "Promete que serás mi pareja\n"
	.string "la próxima vez que nos veamos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperIntro_hns::
	.string "I'm {STR_VAR_1}, and I'm a CAMPER!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon1_hns::
	.string "He criado un {STR_VAR_1}-\n"
	.string "que usa {STR_VAR_2} y un$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperMon2Ask_hns::
	.string "{STR_VAR_1}- que usa {STR_VAR_2}.\p"
	.string "¿Crees que sería divertido unirnos?\n"
	.string "¡Seguro que sí!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperAccept_hns::
	.string "¡Sí!\n"
	.string "¡Me voy a registrar!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_CamperReject_hns::
	.string "La próxima vez, ¿vale?\n"
	.string "Quiero estar en tu equipo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerIntro_hns::
	.string "¡Hola!\n"
	.string "¡Soy {STR_VAR_1}, soy CAMPISTA!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon1_hns::
	.string "Los POKéMON que he estado criando\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerMon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿Te interesa unirte a mí\n"
	.string "en un combate doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerAccept_hns::
	.string "¡Vaya, gracias!\n"
	.string "Haré el registro ahora mismo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PicnickerReject_hns::
	.string "Sería genial unirme a ti\n"
	.string "en otra ocasión.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMIntro_hns::
	.string "I'm PSYCHIC {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon1_hns::
	.string "La pareja que he criado es\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMMon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿Te gustaría formar un equipo\n"
	.string "conmigo?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMAccept_hns::
	.string "¡Claro que sí!\n"
	.string "¡Yo me encargo del registro!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicMReject_hns::
	.string "Si nos volvemos a ver, ahí es\n"
	.string "cuando quisiera unirnos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFIntro_hns::
	.string "Soy {STR_VAR_1}.\n"
	.string "Soy un PSÍQUICO.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon1_hns::
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFMon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}--\n"
	.string "ellos son mis discípulos.\p"
	.string "¿No te intriga la idea de formar\n"
	.string "una pareja de combate?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFAccept_hns::
	.string "Gracias.\n"
	.string "Iré a encargarme del registro.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PsychicFReject_hns::
	.string "Espero que haya otra oportunidad\n"
	.string "de forjar una alianza.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFIntro_hns::
	.string "I'm SCHOOL KID {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon1_hns::
	.string "One {STR_VAR_1}-using {STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFMon2Ask_hns::
	.string "y un usuario de {STR_VAR_1}\n"
	.string "{STR_VAR_2} es mi pareja POKéMON.\p"
	.string "¿Puedo ser tu pareja en\n"
	.string "un equipo doble?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFAccept_hns::
	.string "¡Oh, gracias!\n"
	.string "¡Me registraré en el mostrador!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SchoolKidFReject_hns::
	.string "¡Por favor!\n"
	.string "¿Puedo unirme la próxima vez?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFIntro_hns::
	.string "¡Hola! ¡Me llamo {STR_VAR_1}!\n"
	.string "¡Soy CRIADORA POKéMON!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon1_hns::
	.string "Los POKéMON que crié son\n"
	.string "{STR_VAR_2} que usa {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFMon2Ask_hns::
	.string "un {STR_VAR_2} que usa {STR_VAR_1}.\p"
	.string "¿Te parece interesante?\n"
	.string "¿Hacemos un equipo doble entonces?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFAccept_hns::
	.string "¡Muy bien!\n"
	.string "¡Deja el registro en mis manos!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PkmnBreederFReject_hns::
	.string "Tienes que ir conmigo la próxima,\n"
	.string "¿Todo bien?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFIntro_hns::
	.string "Soy {STR_VAR_1}, y me enorgullece\n"
	.string "decir que soy un POKéFAN.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon1_hns::
	.string "Los lindos POKéMON que crié son\n"
	.string "un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFMon2Ask_hns::
	.string "un {STR_VAR_2} con {STR_VAR_1}.\p"
	.string "¿No son los más tiernos?\n"
	.string "¡Deberíamos hacer un equipo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFAccept_hns::
	.string "¡Gracias, cielo!\n"
	.string "¡Me iré a registrar ahora!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_PokefanFReject_hns::
	.string "Mis lindos POKéMON son los mejores,\n"
	.string "te lo advierto. ¡Qué molesto!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFIntro_hns::
	.string "Hi, I'm SWIMMER {STR_VAR_1}.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon1_hns::
	.string "One {STR_VAR_1}-using {STR_VAR_2}$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFMon2Ask_hns::
	.string "y un usuario de {STR_VAR_1}\n"
	.string "{STR_VAR_2} es lo que he entrenado.\p"
	.string "Tú y yo, hagamos un equipo doble.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFAccept_hns::
	.string "¡Qué genial!\n"
	.string "Nos registraré a los dos.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerFReject_hns::
	.string "Si nos volvemos a ver, me debes\n"
	.string "¡un combate en pareja!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMIntro_hns::
	.string "¿Qué está pasando?\n"
	.string "Soy {STR_VAR_1}, soy TRIATLETA.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon1_hns::
	.string "Tengo unos POKéMON decentes.\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Sería genial formar un equipo\n"
	.string "juntos, ¿qué te parece?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMAccept_hns::
	.string "¡Exacto!\n"
	.string "Espera mientras me registro, ¿ok?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteMReject_hns::
	.string "Espero que me dejes unirme\n"
	.string "¿Qué tal la próxima vez?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFIntro_hns::
	.string "I'm the TRIATHLETE {STR_VAR_1}!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon1_hns::
	.string "Un {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFMon2Ask_hns::
	.string "Otro {STR_VAR_2} que sabe\n"
	.string "usar {STR_VAR_1}. Es mi pareja.\p"
	.string "¿Qué te parece?\n"
	.string "Seríamos un buen equipo, diría yo.$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFAccept_hns::
	.string "¡Me gusta esa respuesta!\n"
	.string "¡Terminaré el registro rápido!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmingTriathleteFReject_hns::
	.string "Me darás otra oportunidad de formar\n"
	.string "una alianza, ¿verdad?$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMIntro_hns::
	.string "¡Hola! ¡Hola!\n"
	.string "¡Soy {STR_VAR_1}, soy NADADOR!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon1_hns::
	.string "¡Mira lo que he estado criando!\n"
	.string "Uno {STR_VAR_2} con {STR_VAR_1} y$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMMon2Ask_hns::
	.string "¡un {STR_VAR_2} con {STR_VAR_1}!\p"
	.string "Genial, ¿eh?\n"
	.string "¡Sería genial formar un equipo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMAccept_hns::
	.string "¡Muy agradecido!\n"
	.string "¡Haré lo del registro ahora mismo!$"

BattleFrontier_BattleTowerMultiPartnerRoom_Text_SwimmerMReject_hns::
	.string "Si nos volvemos a ver, tienes que\n"
	.string "unirte a mí. Lo harás, ¿verdad?$"

