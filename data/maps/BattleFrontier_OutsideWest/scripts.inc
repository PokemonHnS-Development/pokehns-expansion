BattleFrontier_OutsideWest_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideWest_OnTransition
	.byte 0

BattleFrontier_OutsideWest_OnTransition:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	end

BattleFrontier_OutsideWest_EventScript_FerryAttendant::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_MayISeeYourTicket, MSGBOX_DEFAULT
	checkitem ITEM_SS_TICKET
	goto_if_eq VAR_RESULT, FALSE, BattleFrontier_OutsideWest_EventScript_NoSSTicket
	message BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination::
	multichoicedefault 18, 6, MULTI_SSTIDAL_BATTLE_FRONTIER, 2, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_OutsideWest_EventScript_FerryToSlateport
	case 1, BattleFrontier_OutsideWest_EventScript_FerryToLilycove
	case 2, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	case MULTI_B_PRESSED, BattleFrontier_OutsideWest_EventScript_CancelFerrySelect
	end

BattleFrontier_OutsideWest_EventScript_NoSSTicket::
	msgbox BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToSlateport::
	msgbox BattleFrontier_OutsideWest_Text_SlateportItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_SLATEPORT_CITY_HARBOR, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_FerryToLilycove::
	msgbox BattleFrontier_OutsideWest_Text_LilycoveItIs, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination
	msgbox BattleFrontier_OutsideWest_Text_PleaseBoardFerry, MSGBOX_DEFAULT
	call BattleFrontier_OutsideWest_EventScript_BoardFerry
	warp MAP_LILYCOVE_CITY_HARBOR, 8, 11
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_ChooseNewFerryDestination::
	message BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo
	waitmessage
	goto BattleFrontier_OutsideWest_EventScript_ChooseFerryDestination
	end

BattleFrontier_OutsideWest_EventScript_BoardFerry::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	hideobjectat LOCALID_FRONTIER_FERRY_ATTENDANT, MAP_BATTLE_FRONTIER_OUTSIDE_WEST
	setvar VAR_0x8004, LOCALID_FRONTIER_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	return

BattleFrontier_OutsideWest_EventScript_CancelFerrySelect::
	msgbox BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_BattleDomeSign::
	msgbox BattleFrontier_OutsideWest_Text_BattleDomeSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattleFactorySign::
	msgbox BattleFrontier_OutsideWest_Text_BattleFactorySign, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattlePikeSign::
	msgbox BattleFrontier_OutsideWest_Text_BattlePikeSign, MSGBOX_SIGN
	end

@ Unused. Of note, Battle Tower is in the East section in the final release
BattleFrontier_OutsideWest_EventScript_UnusedNPC1::
	msgbox BattleFrontier_OutsideWest_Text_ThisIsBattleTower, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC2::
	msgbox BattleFrontier_OutsideWest_Text_CantFindBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Boy1::
	msgbox BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Fisherman2::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere
	waitmessage
	applymovement LOCALID_FRONTIER_FISHERMAN_2, Common_Movement_FaceAwayPlayer
	waitmovement 0
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_Man1::
	msgbox BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Maniac1::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_Maniac2::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk
	end

BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk::
	applymovement LOCALID_FRONTIER_MANIAC_1, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons, MSGBOX_DEFAULT
	applymovement LOCALID_FRONTIER_MANIAC_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons, MSGBOX_DEFAULT
	closemessage
	delay 25
	applymovement LOCALID_FRONTIER_MANIAC_1, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_FRONTIER_MANIAC_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_Camper::
	lock
	faceplayer
	delay 20
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_CamperFaceFactory
	msgbox BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_CamperFaceFactory::
	applymovement LOCALID_FRONTIER_CAMPER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_CamperAlreadyFacingFactory::
	return

BattleFrontier_OutsideWest_EventScript_Girl::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper
	waitmessage
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_GirlShudderNorth
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_GirlShudderSouth
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_GirlShudderWest
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_GirlShudderEast
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_GirlShudderNorth::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderNorth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderSouth::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderSouth
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderWest::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderWest
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_GirlShudderEast::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderEast
	waitmovement 0
	return

BattleFrontier_OutsideWest_Movement_GirlShudderNorth:
	walk_in_place_faster_down
	walk_in_place_faster_down
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderSouth:
	walk_in_place_faster_up
	walk_in_place_faster_up
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderWest:
	walk_in_place_faster_right
	walk_in_place_faster_right
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderEast:
	walk_in_place_faster_left
	walk_in_place_faster_left
	step_end

BattleFrontier_OutsideWest_EventScript_Woman2::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors, MSGBOX_DEFAULT
	random 2
	goto_if_eq VAR_RESULT, 1, BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors
	goto BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors
	end

BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors::
	msgbox BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors::
	msgbox BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Fisherman1::
	msgbox BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC3::
	msgbox BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Lass::
	msgbox BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_ExpertM::
	msgbox BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man2::
	msgbox BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman1::
	msgbox BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan1::
	msgbox BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan2::
	msgbox BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Boy2::
	lock
	msgbox BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_OldMan::
	msgbox BattleFrontier_OutsideWest_Text_DomeAceIsMine, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man4::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_MAN_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_PokefanF::
	msgbox BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Text_BattleDomeSign:
	.string "¡Este es el BATTLE DOME!\n"
	.string "¡Tu camino a ser una superestrella!$"

BattleFrontier_OutsideWest_Text_BattleFactorySign:
	.string "¡Esta es la BATTLE FACTORY!\n"
	.string "¡Busca a los POKéMON más fuertes!$"

BattleFrontier_OutsideWest_Text_BattlePikeSign:
	.string "¡Este es el BATTLE PIKE!\n"
	.string "¡Elige uno de los tres caminos!$"

BattleFrontier_OutsideWest_Text_ThisIsBattleTower:
	.string "Esta es la BATTLE TOWER.\p"
	.string "Los ENTRENADORES traen a sus\n"
	.string "POKéMON para luchar por eliminación.$"

BattleFrontier_OutsideWest_Text_MayISeeYourTicket:
	.string "Hola, ¿vienes por el ferry?\n"
	.string "¿Puedo ver tu TICKET?$"

BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard:
	.string "{PLAYER} no tiene el TICKET...\p"
	.string "Lo siento muchísimo.\p"
	.string "Necesitas un TICKET para subir\n"
	.string "al ferry.$"

BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo:
	.string "{PLAYER} mostró el TICKET.\p"
	.string "¡Perfecto! ¡Eso es todo!\p"
	.string "¿Y a dónde te gustaría ir?$"

BattleFrontier_OutsideWest_Text_SlateportItIs:
	.string "¡Entonces, a CIUDAD PORTUAL!$"

BattleFrontier_OutsideWest_Text_LilycoveItIs:
	.string "¡Ciudad Calagua, entonces!$"

BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime:
	.string "¡Navega con nosotros en otra ocasión!$"

BattleFrontier_OutsideWest_Text_PleaseBoardFerry:
	.string "Sube al ferry y espera la\n"
	.string "salida.$"

BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo:
	.string "Entonces, ¿adónde quieres ir?$"

BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends:
	.string "Soy el mejor de todos mis amigos.\n"
	.string "Pero aquí...\l"
	.string "¡He sido un inútil!$"

BattleFrontier_OutsideWest_Text_CantFindBattleTower:
	.string "Quiero ir a la BATTLE TOWER,\n"
	.string "pero no la encuentro aunque tengo\l"
	.string "un mapa de la BATTLE FRONTIER.\p"
	.string "¡Este lugar es demasiado grande!$"

BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere:
	.string "Quería aceptar un desafío en cuanto\n"
	.string "llegué aquí.\p"
	.string "Pero en el camino, me mareé...\n"
	.string "Urrrrp...$"

BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere:
	.string "No es como si cualquiera pudiera venir\n"
	.string "aquí, ¿sabes?\p"
	.string "Solo los ENTRENADORES que han sido\n"
	.string "reconocidos como fuertes vienen aquí.\p"
	.string "Por eso muchos ENTRENADORES ni\n"
	.string "saben del BATTLE FRONTIER.$"

BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons:
	.string "Oye, hermano...\p"
	.string "¿Seguro que podemos hacer retos\n"
	.string "sin tener ningún POKéMON?$"

BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons:
	.string "Uh…\n"
	.string "Seguro que todo saldrá bien.\p"
	.string "Creo que...\p"
	.string "¿Recuerdas al tipo grande y aterrador?\n"
	.string "Dijo: ¡Les prestaré POKéMON!$"

BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons:
	.string "Esa es la FÁBRICA DE COMBATE.\n"
	.string "Puedes alquilar POKéMON fuertes.\p"
	.string "Pero me pregunto algo.\n"
	.string "¿Quién cría esos POKéMON de alquiler?$"

BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper:
	.string "Me da miedo entrar al CAMINO DE\n"
	.string "COMBATE por culpa de SEVIPER...\p"
	.string "P-pero vine hasta aquí, ¡así que\n"
	.string "intentaré conquistarlo todo!\l"
	.string "...Tiemblo...$"

BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors:
	.string "¡Juguemos piedra, papel o tijera!\n"
	.string "¡Uno, dos, tres!\p"
	.string "… … … … … …$"

BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge:
	.string "¡Sii! ¡Gané!\n"
	.string "¡Aceptaré el reto de la LANZA!$"

BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge:
	.string "Oh, no…\n"
	.string "Perdí.\p"
	.string "Creo que hoy no tengo suerte.\n"
	.string "Dejaré mi reto de la LANZA\l"
	.string "para mañana.$"

BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling:
	.string "Creo que soy la única persona aquí,\n"
	.string "por alguna razón, preferiría\l"
	.string "pescar que luchar.\p"
	.string "¿Eh? ¿No puedes pescar nada aquí?\n"
	.string "Qué decepción...$"

BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol:
	.string "Hoy seguiré luchando, pase lo que\n"
	.string "pase, hasta conseguir un Símbolo.$"

BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome:
	.string "¿Oh? ¿Vas a desafiar\n"
	.string "el BATTLE DOME?\p"
	.string "Te deseo mucha suerte.\n"
	.string "Ganemos ambos para encontrarnos\l"
	.string "en los desafíos.$"

BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa:
	.string "¡Abuelo, por aquí!\n"
	.string "¡El BATTLE DOME está aquí!\l"
	.string "¡Ve por ellos, abuelo!$"

BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe:
	.string "Ah, ¿así que esto es el BATTLE DOME?\n"
	.string "¡No dejaré que los GENTLEMEN ganen!\p"
	.string "Pero, ¿dónde está la entrada?$"

BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo:
	.string "Antes no había nada aquí, pero ahora\n"
	.string "hace tanto tiempo.\p"
	.string "¡Pero mira este lugar! ¡Increíble!\n"
	.string "Traeré a mi madre para que lo vea.$"

BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier:
	.string "¡Al fin llegué a la\n"
	.string "BATTLE FRONTIER!\p"
	.string "¡Seguro llamaré la atención con\n"
	.string "mi aspecto y habilidad!$"

BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople:
	.string "Munch, munch...\p"
	.string "Parece que esta plaza está llena\n"
	.string "de gente fuerte.\p"
	.string "Munch, munch…$"

BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike:
	.string "Crunch, munch...\p"
	.string "Hace poco conocí a una chica mayor\n"
	.string "en el BATTLE PIKE.\p"
	.string "Tenía unos ojos que daban miedo\n"
	.string "de una forma muy malhumorada.\p"
	.string "Crunch, munch...\p"
	.string "Se puso furiosa: “¿Vas a dejar de\n"
	.string "¡comiendo!”. Luego me dio una paliza.\p"
	.string "Fue una experiencia aterradora\n"
	.string "y espeluznante, la verdad.\p"
	.string "Crunch, munch…$"

BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet:
	.string "¿Eh? ¿Te escuchas a ti mismo?\n"
	.string "¡Eso no es nada!\p"
	.string "¡La última vez que lo animé,\n"
	.string "nuestras miradas se cruzaron!$"

BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering:
	.string "¡¿Quééééé?!\n"
	.string "¡Pfft!\p"
	.string "Eso solo pasó porque\n"
	.string "¡estaba sentado junto a ti!\p"
	.string "El AS DEL DOMO solo nos miró\n"
	.string "¡porque grité muy fuerte!$"

BattleFrontier_OutsideWest_Text_DomeAceIsMine:
	.string "¡Ay, cállate!\n"
	.string "¡Deja de hacer tanto ruido!\p"
	.string "Fans así deberían limitarse a\n"
	.string "¡animar a algún LÍDER de GIMNASIO!\p"
	.string "¡El AS DEL DOMO es mío!\n"
	.string "¡Es mi único ídolo!$"

BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers:
	.string "Esa gente que discute allá...\p"
	.string "Cuesta creerlo, pero alguna vez\n"
	.string "fueron ENTRENADORES muy buenos.\p"
	.string "Solían ser increíblemente fuertes\n"
	.string "y también eran muy famosos.\p"
	.string "Pero fueron aniquilados por un\n"
	.string "cierto ENTRENADOR en un torneo.\p"
	.string "Les dieron tal paliza que\n"
	.string "quedaron prendados del ENTRENADOR.\p"
	.string "Ahora solo son fans del ENTRENADOR.\n"
	.string "Van a animar a su ídolo al\l"
	.string "CÚPULA DE BATALLA cada día.$"

BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier:
	.string "Oí un rumor de que alguien vio\n"
	.string "un POKéMON con una cola muy larga\l"
	.string "en algún lugar de BATTLE FRONTIER.\p"
	.string "Debe ser adorable. Estoy segura…\p"
	.string "Oh, los retos pueden esperar. ¡Siento\n"
	.string "que debo hallar a esa criatura!$"

