SafariZone_EventScript_OutOfBallsMidBattle::
#if IS_FRLG
	setvar VAR_MAP_SCENE_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 3
#elif IS_HNS
	setvar VAR_SAFARI_ZONE_STATE, 1
#else
	setvar VAR_SAFARI_ZONE_STATE, 1
#endif
	special ExitSafariMode
#if IS_FRLG
	setwarp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 4, 1
#elif IS_HNS
	goto_if_set FLAG_IN_KANTO_SAFARI_ZONE, SafariZone_EventScript_ExitKantoMidBattle
	setwarp MAP_SAFARI_ZONE_GATE_SAFARI_ZONE_ENTRANCE_HNS, 9, 3
#else
	setwarp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
#endif
	end

SafariZone_EventScript_ExitKantoMidBattle::
	clearflag FLAG_IN_KANTO_SAFARI_ZONE
	setwarp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE_HNS, 5, 6
	end

SafariZone_EventScript_Exit::
#if IS_FRLG
	setvar VAR_MAP_SCENE_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 1
#elif IS_HNS
	setvar VAR_SAFARI_ZONE_STATE, 1
#else
	setvar VAR_SAFARI_ZONE_STATE, 1
#endif
	special ExitSafariMode
#if IS_FRLG
	warp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE, 4, 1
#elif IS_HNS
	goto_if_set FLAG_IN_KANTO_SAFARI_ZONE, SafariZone_EventScript_ExitKanto
	warp MAP_SAFARI_ZONE_GATE_SAFARI_ZONE_ENTRANCE_HNS, 9, 3
#else
	warp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
#endif
	waitstate
	end

SafariZone_EventScript_ExitKanto::
	clearflag FLAG_IN_KANTO_SAFARI_ZONE
	warp MAP_FUCHSIA_CITY_SAFARI_ZONE_ENTRANCE_HNS, 5, 6
	waitstate
	end

SafariZone_EventScript_RetirePrompt::
	lockall
	msgbox SafariZone_Text_WouldYouLikeToExit, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_Retire
	releaseall
	end

SafariZone_EventScript_Retire::
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_TimesUp::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_TimesUp
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

SafariZone_EventScript_OutOfBalls::
	lockall
	playse SE_DING_DONG
	message SafariZone_Text_OutOfBalls
	waitmessage
	waitbuttonpress
	releaseall
	goto SafariZone_EventScript_Exit

EventScript_PokeBlockFeeder::
	lockall
	special GetPokeblockFeederInFront
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPresent
	msgbox SafariZone_Text_PlacePokeblockOnFeeder, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SafariZone_EventScript_ChoosePokeblock
	releaseall
	end

SafariZone_EventScript_ChoosePokeblock::
	fadescreen FADE_TO_BLACK
	special OpenPokeblockCaseOnFeeder
	waitstate
	goto_if_ne VAR_RESULT, 0xFFFF, SafariZone_EventScript_PokeblockPlaced
#ifdef BUGFIX
	releaseall  @ Only gets called from EventScript_PokeBlockFeeder which uses lockall.
#endif
	end

SafariZone_EventScript_PokeblockPlaced::
	message SafariZone_Text_PokeblockWasPlaced
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_EventScript_PokeblockPresent::
	message SafariZone_Text_PokeblockStillHere
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_EventScript_PokeblockGone::
	lockall
	message SafariZone_Text_PokeblockGone
	waitmessage
	waitbuttonpress
	releaseall
	end

SafariZone_Text_PokeblockGone:
	.string "¡El {STR_VAR_1} fue devorado\npor completo!$"

SafariZone_Text_WouldYouLikeToExit:
	.string "¿Quieres salir ahora de la\nZONA SAFARI?$"

SafariZone_Text_TimesUp:
	.string "¡Ding-dong! ¡Se acabó el tiempo!\n"
	.string "Tu juego SAFARI ha terminado.$"

SafariZone_Text_OutOfBalls:
	.string "Te quedaste sin BOLAS SAFARI.\nTu juego SAFARI ha terminado.$"

SafariZone_Text_PlacePokeblockOnFeeder:
	.string "¿Quieres poner un {POKEBLOCK}\nen el COMEDERO DE {POKEBLOCK}?$"

SafariZone_Text_PokeblockStillHere:
	.string "El {STR_VAR_1} que dejaste\nantes sigue aquí.$"

SafariZone_Text_PokeblockWasPlaced:
	.string "El {STR_VAR_1} se colocó\nen el COMEDERO DE {POKEBLOCK}.$"

Route121_SafariZoneEntrance_Text_WelcomeToSafariZone:
	.string "¡Bienvenido a la ZONA SAFARI!\p"
	.string "Aquí podrás ver muchas clases de\n"
	.string "POKéMON raros en esta región.\p"
	.string "Y los verás en su estado salvaje,\n"
	.string "en sus hábitats naturales.\p"
	.string "Además, hemos abierto las puertas\n"
	.string "a los ENTRENADORES POKéMON.\p"
	.string "¡Te animamos a capturar POKéMON\n"
	.string "para siempre!\p"
	.string "¡Entra y disfruta de la ZONA SAFARI!$"

Route121_SafariZoneEntrance_Text_WelcomeFirstTime:
	.string "¡Bienvenido a la ZONA SAFARI!\n¿Es tu primera vez aquí?$"

Route121_SafariZoneEntrance_Text_ComeInAndEnjoy:
	.string "¡Entra y disfruta de la ZONA SAFARI!$"

Route121_SafariZoneEntrance_Text_FirstTimeInfo:
	.string "Al entrar en la ZONA SAFARI, tú\n"
	.string "empiezas con 30 BOLAS SAFARI para\l"
	.string "atrapar POKéMON.\p"
	.string "El juego SAFARI termina al gastar\n"
	.string "tus BOLAS SAFARI, o al caminar\l"
	.string "500 pasos.\p"
	.string "¡Entra y disfruta de la ZONA SAFARI!$"

Route121_SafariZoneEntrance_Text_WouldYouLikeToPlay:
	.string "¡Bienvenido a la ZONA SAFARI!\p¡Puedes atrapar todo por solo ¥500!\n¿Quieres jugar una partida SAFARI?$"

Route121_SafariZoneEntrance_Text_PlayAnotherTime:
	.string "Está bien.\n"
	.string "¡Vuelve a jugar otro día!$"

Route121_SafariZoneEntrance_Text_NotEnoughMoney:
	.string "No tienes suficiente dinero.\n"
	.string "Lo siento.$"

Route121_SafariZoneEntrance_Text_ThatWillBe500Please:
	.string "Son ¥500, por favor.$"

Route121_SafariZoneEntrance_Text_HereAreYourSafariBalls:
	.string "Aquí tienes tus BOLAS SAFARI.$"

Route121_SafariZoneEntrance_Text_Received30SafariBalls:
	.string "¡{PLAYER} recibió 30 BOLAS SAFARI!$"

Route121_SafariZoneEntrance_Text_PleaseEnjoyYourself:
	.string "Te avisaremos cuando tu partida\nhaya terminado.\pMientras tanto, ¡diviértete!\n¡Disfruta tu excursión salvaje!$"

Route121_SafariZoneEntrance_Text_PCIsFull:
	.string "¡Disculpa!\n"
	.string "Tu PC BOX está llena.$"

Route121_SafariZoneEntrance_Text_YouNeedPokeblockCase:
	.string "¡Disculpa!\n"
	.string "Parece que no tienes un ESTUCHE {POKEBLOCK}.\p"
	.string "Tu juego de SAFARI será mucho más\n"
	.string "útil si usas {POKEBLOCK}S.\p"
	.string "Vuelve con un ESTUCHE {POKEBLOCK}.\p"
	.string "Puedes obtener un ESTUCHE {POKEBLOCK} de\n"
#if IS_HNS
	.string "aquel chico de allá.$"
#else
	.string "el SALÓN DE CONCURSOS DE VERA GUÍA.$"
#endif

SafariZone_South_Text_StillHaveTimeExit:
	.string "Aún te queda tiempo. ¿Quieres\nsalir de la ZONA SAFARI ahora?$"

SafariZone_South_Text_EnjoyTheRestOfYourAdventure:
	.string "¡Disfruta el resto de tu\naventura salvaje!$"

SafariZone_South_Text_ExitEarlyThankYouForPlaying:
	.string "Está bien.\p"
	.string "Recuperaré tus BOLAS SAFARI\n"
	.string "restantes.\p"
	.string "Gracias por jugar.\n"
	.string "Esperamos verte de nuevo.$"

SafariZone_South_Text_GoodLuck:
	.string "¡Buena suerte!\pSi necesitas algo, no dudes\nen decírmelo, ¡por favor!$"

SafariZone_South_Text_Boy:
	.string "¿Sabías esto?\p"
	.string "Si pones un {POKEBLOCK} en la caja,\n"
	.string "los POKéMON se reunirán.$"

SafariZone_South_Text_Man:
	.string "Quiero ir más profundo, pero yo\n"
	.string "olvidé traer la BICICLETA.\p"
	.string "Algo me dice que esos POKéMON\n"
	.string "viven en las zonas alejadas.$"

SafariZone_Southwest_Text_Woman:
	.string "A veces, si lanzo un {POKEBLOCK} a un\n"
	.string "POKéMON, me ignora.\p"
	.string "¿Tienen los POKéMON gustos y\n"
	.string "disgustos con lo que comen?$"

SafariZone_Northwest_Text_Man:
	.string "Jadeo... Jadeo...\n"
	.string "Logré... llegar hasta aquí... pero...\p"
	.string "estoy agotado... No tengo la\n"
	.string "energía para capturar POKéMON...$"

SafariZone_North_Text_Fisherman:
	.string "Busco POKéMON de tipo AGUA\n"
	.string "no se ven en HOENN.\p"
	.string "¿Sabes dónde queda el lago?$"

SafariZone_North_Text_Man:
	.string "Atraparé muchos POKéMON raros\n"
	.string "aquí y los cambiaré con mis amigos!$"

SafariZone_South_Text_Youngster:
	.string "He puesto un {POKEBLOCK} en el COMEDERO de {POKEBLOCK}S.\n"
	.string "Pero parece que ha desaparecido.\p"
	.string "Creo que un POKéMON se lo comió\n"
	.string "sin que me diera cuenta.$"

Route121_SafariZoneEntrance_Text_TrainerTip:
	.string "¡CONSEJO DE SAFARI ZONE!\p"
	.string "Lanza {POKEBLOCK}S a los POKéMON\n"
	.string "para que no huyan tan fácil.$"

SafariZone_Southwest_Text_RestHouseSign:
	.string "Descansa tus pies cansados.\n"
	.string "CASA DE DESCANSO$"

SafariZone_RestHouse_Text_Youngster:
	.string "No tengo {POKEBLOCK}S, pero atrapé\n"
	.string "bastantes POKéMON.\p"
	.string "Puedes mejorar tus chances de captura\n"
	.string "acercándote más a ellos\l"
	.string "antes de lanzar una BOLA SAFARI.$"

SafariZone_RestHouse_Text_PsychicM:
	.string "Si usas {POKEBLOCK}S, los POKéMON\n"
	.string "no huirán tan rápido.\p"
	.string "No sirve dar {POKEBLOCK}S a POKéMON\n"
	.string "que no huyen fácilmente.$"

SafariZone_RestHouse_Text_FatMan:
	.string "Si pones un {POKEBLOCK} en el COMEDERO,\n"
	.string "los POKéMON se sentirán atraídos.\p"
	.string "Creo que los POKéMON con la misma\n"
	.string "naturaleza buscan un {POKEBLOCK}.$"

SafariZone_South_Text_AreaOffLimits1:
	.string "Esta área aún está en construcción.\nEstá prohibido el paso, ¡lo siento!$"

SafariZone_Southeast_Text_ExpansionIsFinished:
	.string "El proyecto de ampliación de\nla ZONA SAFARI ya terminó.\pEsperamos que disfrutes la zona.$"

SafariZone_South_Text_AreaOffLimits2:
	.string "Esta zona aún está en construcción.\nEstá prohibido el paso, ¡perdón!$"

SafariZone_Southeast_Text_LittleGirl:
	.string "¡Guau! ¡Genial! ¡No había visto\n"
	.string "estos POKéMON antes!$"

SafariZone_Southeast_Text_FatMan:
	.string "Los POKéMON de esta zona son todos\n"
	.string "nuevos para mí.\p"
	.string "Y puedo capturar estos raros\n"
	.string "¡POKéMON! ¡Qué genial!$"

SafariZone_Southeast_Text_RichBoy:
	.string "Los POKéMON de por aquí parecen\n"
	.string "venir de fuera de HOENN.$"

SafariZone_Northeast_Text_Boy:
	.string "Solo me quedan un par de BOLAS SAFARI.\pMe cuesta mucho decidir\nqué debería atrapar.$"

SafariZone_Northeast_Text_Woman:
	.string "Oí que aquí se puede ver a PIKACHU.\n¿Dónde podría haber uno?$"

SafariZone_Northeast_Text_Girl:
	.string "¡Ay, qué mal!\n"
	.string "¡Parece que no capturo nada!\p"
	.string "¡Desperdiciaré el precio de la\n"
	.string "entrada si no capturo algo!$"
