BattleFrontier_OutsideWest_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideWest_OnTransition_hns
	.byte 0

BattleFrontier_OutsideWest_OnTransition_hns:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	end

BattleFrontier_OutsideWest_EventScript_EventScript_Sailor_hns::
	lock
	faceplayer
	msgbox FarawayIsland_Entrance_Text_SailorReturn, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_OutsideWest_EventScript_AsYouLike_hns
	msgbox EventTicket_Text_SailHome, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 30
	clearflag FLAG_SAFE_FOLLOWER_MOVEMENT
	hideobjectat LOCALID_BATTLE_FRONTIER_SAILOR_HNS, MAP_BATTLE_FRONTIER_OUTSIDE_WEST_HNS
	setvar VAR_0x8004, LOCALID_FARAWAY_BATTLE_FRONTIER_HNS_SS_TIDAL
	call Common_EventScript_FerryDepartIsland
	warpsilent MAP_OLIVINE_CITY_PORT_INSIDE_HNS, 8, 16
	waitstate
	release
	end

BattleFrontier_OutsideWest_EventScript_AsYouLike_hns::
	msgbox EventTicket_Text_AsYouLike, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_BattleDomeSign_hns::
	msgbox BattleFrontier_OutsideWest_Text_BattleDomeSign_hns, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattleFactorySign_hns::
	msgbox BattleFrontier_OutsideWest_Text_BattleFactorySign_hns, MSGBOX_SIGN
	end

BattleFrontier_OutsideWest_EventScript_BattlePikeSign_hns::
	msgbox BattleFrontier_OutsideWest_Text_BattlePikeSign_hns, MSGBOX_SIGN
	end

@ Unused. Of note, Battle Tower is in the East section in the final release
BattleFrontier_OutsideWest_EventScript_UnusedNPC1_hns::
	msgbox BattleFrontier_OutsideWest_Text_ThisIsBattleTower_hns, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC2_hns::
	msgbox BattleFrontier_OutsideWest_Text_CantFindBattleTower_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Boy1_hns::
	msgbox BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Fisherman2_hns::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere_hns
	waitmessage
	applymovement LOCALID_FRONTIER_FISHERMAN_2, Common_Movement_FaceAwayPlayer
	waitmovement 0
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_Man1_hns::
	msgbox BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Maniac1_hns::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk_hns
	end

BattleFrontier_OutsideWest_EventScript_Maniac2_hns::
	lock
	goto BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk_hns
	end

BattleFrontier_OutsideWest_EventScript_FactoryChallengersTalk_hns::
	applymovement LOCALID_FRONTIER_MANIAC_1, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons_hns, MSGBOX_DEFAULT
	applymovement LOCALID_FRONTIER_MANIAC_2, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	msgbox BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons_hns, MSGBOX_DEFAULT
	closemessage
	delay 25
	applymovement LOCALID_FRONTIER_MANIAC_1, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_FRONTIER_MANIAC_2, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_Camper_hns::
	lock
	faceplayer
	delay 20
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_Camper_hnsFaceFactory_hns
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_Camper_hnsAlreadyFacingFactory_hns
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_Camper_hnsFaceFactory_hns
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_Camper_hnsFaceFactory_hns
	msgbox BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Camper_hnsFaceFactory_hns::
	applymovement LOCALID_FRONTIER_CAMPER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_Camper_hnsAlreadyFacingFactory_hns::
	return

BattleFrontier_OutsideWest_EventScript_Girl_hns::
	lock
	faceplayer
	message BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper_hns
	waitmessage
	call_if_eq VAR_FACING, DIR_NORTH, BattleFrontier_OutsideWest_EventScript_Girl_hnsShudderNorth_hns
	call_if_eq VAR_FACING, DIR_SOUTH, BattleFrontier_OutsideWest_EventScript_Girl_hnsShudderSouth_hns
	call_if_eq VAR_FACING, DIR_WEST, BattleFrontier_OutsideWest_EventScript_Girl_hnsShudderWest_hns
	call_if_eq VAR_FACING, DIR_EAST, BattleFrontier_OutsideWest_EventScript_Girl_hnsShudderEast_hns
	waitbuttonpress
	release
	end

BattleFrontier_OutsideWest_EventScript_Girl_hnsShudderNorth_hns::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderNorth_hns
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_Girl_hnsShudderSouth_hns::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderSouth_hns
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_Girl_hnsShudderWest_hns::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderWest_hns
	waitmovement 0
	return

BattleFrontier_OutsideWest_EventScript_Girl_hnsShudderEast_hns::
	applymovement LOCALID_FRONTIER_GIRL, BattleFrontier_OutsideWest_Movement_GirlShudderEast_hns
	waitmovement 0
	return

BattleFrontier_OutsideWest_Movement_GirlShudderNorth_hns:
	walk_in_place_faster_down
	walk_in_place_faster_down
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderSouth_hns:
	walk_in_place_faster_up
	walk_in_place_faster_up
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderWest_hns:
	walk_in_place_faster_right
	walk_in_place_faster_right
	step_end

BattleFrontier_OutsideWest_Movement_GirlShudderEast_hns:
	walk_in_place_faster_left
	walk_in_place_faster_left
	step_end

BattleFrontier_OutsideWest_EventScript_Woman2_hns::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors_hns, MSGBOX_DEFAULT
	random 2
	goto_if_eq VAR_RESULT, 1, BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors_hns
	goto BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors_hns
	end

BattleFrontier_OutsideWest_EventScript_WomanWonRockPaperScissors_hns::
	msgbox BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_WomanLostRockPaperScissors_hns::
	msgbox BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Fisherman1_hns::
	msgbox BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling_hns, MSGBOX_NPC
	end

@ Unused
BattleFrontier_OutsideWest_EventScript_UnusedNPC3_hns::
	msgbox BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Gentleman_hns::
	msgbox BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Lass_hns::
	msgbox BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_ExpertM_hns::
	msgbox BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man2_hns::
	msgbox BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman1_hns::
	msgbox BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan1_hns::
	msgbox BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_FatMan2_hns::
	msgbox BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Woman3_hns::
	lock
	msgbox BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_Boy2_hns::
	lock
	msgbox BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideWest_EventScript_OldMan_hns::
	msgbox BattleFrontier_OutsideWest_Text_DomeAceIsMine_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_EventScript_Man4_hns::
	lock
	faceplayer
	msgbox BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_MAN_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_OutsideWest_EventScript_PokefanF_hns::
	msgbox BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideWest_Text_BattleDomeSign_hns:
	.string "¡Este es el BATTLE DOME!\n"
	.string "¡Tu camino a ser una superestrella!$"

BattleFrontier_OutsideWest_Text_BattleFactorySign_hns:
	.string "¡Esta es la BATTLE FACTORY!\n"
	.string "¡Busca a los POKéMON más fuertes!$"

BattleFrontier_OutsideWest_Text_BattlePikeSign_hns:
	.string "¡Este es el BATTLE PIKE!\n"
	.string "¡Elige uno de los tres caminos!$"

BattleFrontier_OutsideWest_Text_ThisIsBattleTower_hns:
	.string "Esta es la BATTLE TOWER.\p"
	.string "Los ENTRENADORES traen a sus\n"
	.string "POKéMON para luchar por eliminación.$"

BattleFrontier_OutsideWest_Text_MayISeeYourTicket_hns:
	.string "Hola, ¿vienes por el ferry?\n"
	.string "¿Puedo ver tu TICKET?$"

BattleFrontier_OutsideWest_Text_MustHaveTicketToBoard_hns:
	.string "{PLAYER} no tiene el TICKET...\p"
	.string "Lo siento muchísimo.\p"
	.string "Necesitas un TICKET para subir\n"
	.string "al ferry.$"

BattleFrontier_OutsideWest_Text_WhereWouldYouLikeToGo_hns:
	.string "{PLAYER} mostró el TICKET.\p"
	.string "¡Perfecto! ¡Eso es todo!\p"
	.string "¿Y a dónde te gustaría ir?$"

BattleFrontier_OutsideWest_Text_SlateportItIs_hns:
	.string "¡Entonces, a CIUDAD PORTUAL!$"

BattleFrontier_OutsideWest_Text_LilycoveItIs_hns:
	.string "¡Ciudad Calagua, entonces!$"

BattleFrontier_OutsideWest_Text_SailWithUsAnotherTime_hns:
	.string "¡Navega con nosotros en otra ocasión!$"

BattleFrontier_OutsideWest_Text_PleaseBoardFerry_hns:
	.string "Sube al ferry y espera la\n"
	.string "salida.$"

BattleFrontier_OutsideWest_Text_ThenWhereWouldYouLikeToGo_hns:
	.string "Entonces, ¿adónde quieres ir?$"

BattleFrontier_OutsideWest_Text_BestOutOfAllMyFriends_hns:
	.string "Soy el mejor de todos mis amigos.\n"
	.string "Pero aquí...\l"
	.string "¡He sido un inútil!$"

BattleFrontier_OutsideWest_Text_CantFindBattleTower_hns:
	.string "Quiero ir a la BATTLE TOWER,\n"
	.string "pero no la encuentro aunque tengo\l"
	.string "un mapa de la BATTLE FRONTIER.\p"
	.string "¡Este lugar es demasiado grande!$"

BattleFrontier_OutsideWest_Text_GotSeasickOnWayHere_hns:
	.string "Quería aceptar un desafío en cuanto\n"
	.string "llegué aquí.\p"
	.string "Pero en el camino, me mareé...\n"
	.string "Urrrrp...$"

BattleFrontier_OutsideWest_Text_OnlyToughTrainersBroughtHere_hns:
	.string "No es como si cualquiera pudiera venir\n"
	.string "aquí, ¿sabes?\p"
	.string "Solo los ENTRENADORES que han sido\n"
	.string "reconocidos como fuertes vienen aquí.\p"
	.string "Por eso muchos ENTRENADORES ni\n"
	.string "saben del BATTLE FRONTIER.$"

BattleFrontier_OutsideWest_Text_SureWeCanChallengeWithNoMons_hns:
	.string "Oye, hermano...\p"
	.string "¿Seguro que podemos hacer retos\n"
	.string "sin tener ningún POKéMON?$"

BattleFrontier_OutsideWest_Text_BigGuySaidIllLendYouMons_hns:
	.string "Uh…\n"
	.string "Seguro que todo saldrá bien.\p"
	.string "Creo que...\p"
	.string "¿Recuerdas al tipo grande y aterrador?\n"
	.string "Dijo: ¡Les prestaré POKéMON!$"

BattleFrontier_OutsideWest_Text_WhosRaisingThoseRentalMons_hns:
	.string "Esa es la FÁBRICA DE COMBATE.\n"
	.string "Puedes alquilar POKéMON fuertes.\p"
	.string "Pero me pregunto algo.\n"
	.string "¿Quién cría esos POKéMON de alquiler?$"

BattleFrontier_OutsideWest_Text_ScaredOfPikeBecauseSeviper_hns:
	.string "Me da miedo entrar al CAMINO DE\n"
	.string "COMBATE por culpa de SEVIPER...\p"
	.string "P-pero vine hasta aquí, ¡así que\n"
	.string "intentaré conquistarlo todo!\l"
	.string "...Tiemblo...$"

BattleFrontier_OutsideWest_Text_LetsPlayRockPaperScissors_hns:
	.string "¡Juguemos piedra, papel o tijera!\n"
	.string "¡Uno, dos, tres!\p"
	.string "… … … … … …$"

BattleFrontier_OutsideWest_Text_WonIllTakePikeChallenge_hns:
	.string "¡Sii! ¡Gané!\n"
	.string "¡Aceptaré el reto de la LANZA!$"

BattleFrontier_OutsideWest_Text_LostIllPutOffPikeChallenge_hns:
	.string "Oh, no…\n"
	.string "Perdí.\p"
	.string "Creo que hoy no tengo suerte.\n"
	.string "Dejaré mi reto de la LANZA\l"
	.string "para mañana.$"

BattleFrontier_OutsideWest_Text_ChooseFishingOverBattling_hns:
	.string "Creo que soy la única persona aquí,\n"
	.string "por alguna razón, preferiría\l"
	.string "pescar que luchar.\p"
	.string "¿Eh? ¿No puedes pescar nada aquí?\n"
	.string "Qué decepción...$"

BattleFrontier_OutsideWest_Text_KeepBattlingUntilIGetSymbol_hns:
	.string "Hoy seguiré luchando, pase lo que\n"
	.string "pase, hasta conseguir un Símbolo.$"

BattleFrontier_OutsideWest_Text_YoureOffToChallengeDome_hns:
	.string "¿Oh? ¿Vas a desafiar\n"
	.string "el BATTLE DOME?\p"
	.string "Te deseo mucha suerte.\n"
	.string "Ganemos ambos para encontrarnos\l"
	.string "en los desafíos.$"

BattleFrontier_OutsideWest_Text_DomeIsHereGrandpa_hns:
	.string "¡Abuelo, por aquí!\n"
	.string "¡El BATTLE DOME está aquí!\l"
	.string "¡Ve por ellos, abuelo!$"

BattleFrontier_OutsideWest_Text_WontLetGentlemenBeatMe_hns:
	.string "Ah, ¿así que esto es el BATTLE DOME?\n"
	.string "¡No dejaré que los GENTLEMEN ganen!\p"
	.string "Pero, ¿dónde está la entrada?$"

BattleFrontier_OutsideWest_Text_NothingHereNotLongAgo_hns:
	.string "Antes no había nada aquí, pero ahora\n"
	.string "hace tanto tiempo.\p"
	.string "¡Pero mira este lugar! ¡Increíble!\n"
	.string "Traeré a mi madre para que lo vea.$"

BattleFrontier_OutsideWest_Text_FinallyArrivedAtFrontier_hns:
	.string "¡Al fin llegué a la\n"
	.string "BATTLE FRONTIER!\p"
	.string "¡Seguro llamaré la atención con\n"
	.string "mi aspecto y habilidad!$"

BattleFrontier_OutsideWest_Text_SquareFilledWithToughPeople_hns:
	.string "Munch, munch...\p"
	.string "Parece que esta plaza está llena\n"
	.string "de gente fuerte.\p"
	.string "Munch, munch…$"

BattleFrontier_OutsideWest_Text_MetOlderGirlAtPike_hns:
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

BattleFrontier_OutsideWest_Text_LastTimeOurEyesMet_hns:
	.string "¿Eh? ¿Te escuchas a ti mismo?\n"
	.string "¡Eso no es nada!\p"
	.string "¡La última vez que lo animé,\n"
	.string "nuestras miradas se cruzaron!$"

BattleFrontier_OutsideWest_Text_DomeAceLookedBecauseOfMyCheering_hns:
	.string "¡¿Quééééé?!\n"
	.string "¡Pfft!\p"
	.string "Eso solo pasó porque\n"
	.string "¡estaba sentado junto a ti!\p"
	.string "El AS DEL DOMO solo nos miró\n"
	.string "¡porque grité muy fuerte!$"

BattleFrontier_OutsideWest_Text_DomeAceIsMine_hns:
	.string "¡Ay, cállate!\n"
	.string "¡Deja de hacer tanto ruido!\p"
	.string "Fans así deberían limitarse a\n"
	.string "¡animar a algún LÍDER de GIMNASIO!\p"
	.string "¡El AS DEL DOMO es mío!\n"
	.string "¡Es mi único ídolo!$"

BattleFrontier_OutsideWest_Text_FansOverThereUsedToBeTrainers_hns:
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

BattleFrontier_OutsideWest_Text_MonWithLongTailInFrontier_hns:
	.string "Oí un rumor de que alguien vio\n"
	.string "un POKéMON con una cola muy larga\l"
	.string "en algún lugar de BATTLE FRONTIER.\p"
	.string "Debe ser adorable. Estoy segura…\p"
	.string "Oh, los retos pueden esperar. ¡Siento\n"
	.string "que debo hallar a esa criatura!$"

