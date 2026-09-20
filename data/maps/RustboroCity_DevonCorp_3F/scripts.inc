RustboroCity_DevonCorp_3F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_3F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, RustboroCity_DevonCorp_3F_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RustboroCity_DevonCorp_3F_OnFrame
	.byte 0

RustboroCity_DevonCorp_3F_OnTransition:
	call_if_eq VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_SetEmployeePos
	end

RustboroCity_DevonCorp_3F_EventScript_SetEmployeePos::
	setobjectxyperm LOCALID_DEVON_CORP_3F_EMPLOYEE, 3, 2
	setobjectmovementtype LOCALID_DEVON_CORP_3F_EMPLOYEE, MOVEMENT_TYPE_FACE_LEFT
	return

RustboroCity_DevonCorp_3F_OnWarp:
	map_script_2 VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_PlayerFaceEast
	.2byte 0

RustboroCity_DevonCorp_3F_EventScript_PlayerFaceEast::
	turnobject LOCALID_PLAYER, DIR_EAST
	end

RustboroCity_DevonCorp_3F_OnFrame:
	map_script_2 VAR_DEVON_CORP_3F_STATE, 0, RustboroCity_DevonCorp_3F_EventScript_MeetPresident
	.2byte 0

RustboroCity_DevonCorp_3F_EventScript_MeetPresident::
	lockall
	msgbox RustboroCity_DevonCorp_3F_Text_ThisIs3rdFloorWaitHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeWalkOffscreen
	waitmovement 0
	delay 80
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeReturnToPlayer
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_WordWithPresidentComeWithMe, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_FOLLOW_ME, FALSE
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_LeadPlayerToPresident
	applymovement LOCALID_PLAYER, RustboroCity_DevonCorp_3F_Movement_PlayerFollowToPresident
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_PleaseGoAhead, MSGBOX_DEFAULT
	closemessage
	fadedefaultbgm
	applymovement LOCALID_DEVON_CORP_3F_EMPLOYEE, RustboroCity_DevonCorp_3F_Movement_EmployeeFaceDesk
	applymovement LOCALID_PLAYER, RustboroCity_DevonCorp_3F_Movement_PlayerApproachDesk
	waitmovement 0
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneIHaveFavor, MSGBOX_DEFAULT
	giveitem ITEM_LETTER
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneWantYouToHaveThis, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_3F_Text_ReceivedPokenav
	waitfanfare
	setflag FLAG_SYS_POKENAV_GET
	setflag FLAG_RECEIVED_POKENAV
	setflag FLAG_HIDE_RUSTBORO_CITY_POKEMON_SCHOOL_SCOTT
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneExplainPokenavRestUp, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox RustboroCity_DevonCorp_3F_Text_MrStoneGoWithCautionAndCare, MSGBOX_DEFAULT
	setflag FLAG_HIDE_ROUTE_116_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_WANDAS_BOYFRIEND
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_WANDA
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	setvar VAR_BRINEY_LOCATION, 1
	clearflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
	setvar VAR_DEVON_CORP_3F_STATE, 1
	setvar VAR_RUSTBORO_CITY_STATE, 6
	releaseall
	end

RustboroCity_DevonCorp_3F_Movement_Unused:
	walk_up
	walk_up
	walk_up
	walk_in_place_faster_left
	step_end

RustboroCity_DevonCorp_3F_Movement_LeadPlayerToPresident:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_left
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeFaceDesk:
	delay_16
	walk_in_place_faster_down
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeWalkOffscreen:
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_EmployeeReturnToPlayer:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerFollowToPresident:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RustboroCity_DevonCorp_3F_Movement_PlayerApproachDesk:
	delay_16
	delay_16
	walk_down
	walk_down
	walk_in_place_faster_right
	step_end

RustboroCity_DevonCorp_3F_EventScript_MrStone::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_EXP_SHARE, RustboroCity_DevonCorp_3F_EventScript_MrStoneAfterFavor
	goto_if_set FLAG_DELIVERED_STEVEN_LETTER, RustboroCity_DevonCorp_3F_EventScript_GiveExpShare
	msgbox RustboroCity_DevonCorp_3F_Text_CountingOnYou, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_GiveExpShare::
	msgbox RustboroCity_DevonCorp_3F_Text_ThankYouForDeliveringLetter, MSGBOX_DEFAULT
	giveitem ITEM_EXP_SHARE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_EXP_SHARE
	msgbox RustboroCity_DevonCorp_3F_Text_ExplainExpShare, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_MrStoneAfterFavor::
	msgbox RustboroCity_DevonCorp_3F_Text_NotFamiliarWithTrends, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RustboroCity_DevonCorp_3F_EventScript_Employee::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_REPEAT_BALL, RustboroCity_DevonCorp_3F_EventScript_EmployeeBalls
	msgbox RustboroCity_DevonCorp_3F_Text_VisitCaptSternShipyard, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_EmployeeBalls::
	msgbox RustboroCity_DevonCorp_3F_Text_RepeatAndTimerHugelyPopular, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_3F_EventScript_RareRocksDisplay::
	msgbox RustboroCity_DevonCorp_3F_Text_RareRocksDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_3F_Text_MrStoneIHaveFavor:
	.string "Soy el SR. STONE, el PRESIDENTE de\n"
	.string "DEVON CORPORATION.\p"
	.string "¡Acabo de recibir noticias tuyas!\p"
	.string "Salvaste a nuestro personal no una,\n"
	.string "¡sino dos veces!\p"
	.string "Quiero pedirle un favor a alguien tan\n"
	.string "increíble como tú.\p"
	.string "Sé que vas a entregar un paquete\n"
	.string "al ASTILLERO de PORTALUCA.\p"
	.string "Bueno, ¿podrías pasar antes por\n"
	.string "PUEBLO JENGIBRE?\p"
	.string "Espero que puedas entregarle una\n"
	.string "CARTA a STEVEN en P. JENGIBRE.$"

RustboroCity_DevonCorp_3F_Text_MrStoneWantYouToHaveThis:
	.string "SR. STONE: Debes saber que\n"
	.string "soy un gran PRESIDENTE.\p"
	.string "Así que jamás sería tan tacaño\n"
	.string "como pedir un favor sin dar nada.\p"
	.string "¡Por eso quiero que tengas esto!$"

RustboroCity_DevonCorp_3F_Text_ReceivedPokenav:
	.string "{PLAYER} received a POKéNAV.$"

RustboroCity_DevonCorp_3F_Text_MrStoneExplainPokenavRestUp:
	.string "SR. STONE: Ese dispositivo...\p"
	.string "Es un NAVEGADOR POKéMON, o POKéNAV\n"
	.string "para abreviar.\p"
	.string "Es una herramienta indispensable\n"
	.string "para cualquier ENTRENADOR.\p"
	.string "Tiene un mapa de la región de HOENN.\p"
	.string "Puedes ver la ubicación de\n"
	.string "¡DEWFORD y SLATEPORT fácilmente!\p"
	.string "Por cierto, oí que unos criminales\n"
	.string "sinuosos, MAGMA y AQUA, creo,\l"
	.string "están causando problemas por doquier.\p"
	.string "Creo que sería mejor que descanses\n"
	.string "antes de seguir tu camino.$"

RustboroCity_DevonCorp_3F_Text_MrStoneGoWithCautionAndCare:
	.string "SR. STONE: Bien, entonces, {PLAYER}{KUN},\n"
	.string "¡ve con mucha precaución!$"

RustboroCity_DevonCorp_3F_Text_CountingOnYou:
	.string "MR. STONE: I'm counting on you!$"

RustboroCity_DevonCorp_3F_Text_ThankYouForDeliveringLetter:
	.string "SR. STONE: ¿Entregaste mi CARTA?\n"
	.string "¡Muchas gracias!\p"
	.string "Esta es mi forma de agradecerte.\n"
	.string "Te servirá, ENTRENADOR.$"

RustboroCity_DevonCorp_3F_Text_ExplainExpShare:
	.string "SR. STONE: Un POKéMON que lleve el\n"
	.string "REPARTIR EXP recibirá parte de los\l"
	.string "puntos de EXP del combate.\p"
	.string "Ganará puntos de EXP aunque no haya\n"
	.string "combatido realmente.\p"
	.string "Diría que el REPARTIR EXP es muy útil\n"
	.string "para subir POKéMON débiles.$"

RustboroCity_DevonCorp_3F_Text_NotFamiliarWithTrends:
	.string "SR. STONE: Desde joven, me he\n"
	.string "dedicado solo al trabajo.\p"
	.string "Por eso, no estoy al tanto de las\n"
	.string "modas y cosas así.\p"
	.string "¿Pero todos los jóvenes quieren ser\n"
	.string "ENTRENADORES de la LIGA POKéMON?$"

RustboroCity_DevonCorp_3F_Text_ThisIs3rdFloorWaitHere:
	.string "Este es el tercer piso de la\n"
	.string "DEVON CORPORATION.\p"
	.string "La OFICINA DEL PRESIDENTE está\n"
	.string "en este piso.\p"
	.string "En fin, no puedo expresar cuánto\n"
	.string "agradezco lo que has hecho.\p"
	.string "Eh... Por cierto, ese paquete\n"
	.string "que recuperaste para nosotros...\p"
	.string "¿Podrías entregarlo en el\n"
	.string "ASTILLERO de PORTALAGUNA?\p"
	.string "Sería terrible que esos ladrones\n"
	.string "intentaran robárselo otra vez.\p"
	.string "Eh... Jejeje, entonces, ¿podría\n"
	.string "contar contigo para hacer eso?\p"
	.string "Ah, es cierto.\n"
	.string "¿Podrías esperar aquí un segundo?$"

RustboroCity_DevonCorp_3F_Text_WordWithPresidentComeWithMe:
	.string "Nuestro PRESIDENTE quiere\n"
	.string "decirte unas palabras.\p"
	.string "Por favor, ven conmigo.$"

RustboroCity_DevonCorp_3F_Text_PleaseGoAhead:
	.string "Please, go ahead.$"

RustboroCity_DevonCorp_3F_Text_VisitCaptSternShipyard:
	.string "Si visitas el ASTILLERO de PORTALEN,\n"
	.string "Deberías ir a ver al CAPT. STERN.$"

RustboroCity_DevonCorp_3F_Text_RepeatAndTimerHugelyPopular:
	.string "DEVON's new products, the REPEAT BALL\n"
	.string "y la TIMER BALL, se han vuelto muy\l"
	.string "populares entre los ENTRENADORES.$"

RustboroCity_DevonCorp_3F_Text_RareRocksDisplay:
	.string "Es una colección de rocas y\n"
	.string "piedras reunidas por el PRESIDENTE.$"

