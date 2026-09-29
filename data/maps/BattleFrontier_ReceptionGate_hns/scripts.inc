BattleFrontier_ReceptionGate_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_ReceptionGate_OnFrame_hns
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_ReceptionGate_OnTransition_hns
	.byte 0

BattleFrontier_ReceptionGate_OnTransition_hns:
	setflag FLAG_LANDMARK_BATTLE_FRONTIER
	end

BattleFrontier_ReceptionGate_OnFrame_hns:
	map_script_2 VAR_HAS_ENTERED_BATTLE_FRONTIER, 0, BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering_hns
	.2byte 0

BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering_hns::
	lockall
	setvar VAR_HAS_ENTERED_BATTLE_FRONTIER, 1
	playse SE_PIN
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_FRONTIER_RECEPTION_GREETER
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_Delay48
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter_hns
	waitmovement 0
	goto BattleFrontier_ReceptionGate_EventScript_ScottScene_hns
	end

BattleFrontier_ReceptionGate_EventScript_ScottScene_hns::
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier_hns, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IssueFrontierPass_hns, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass_hns
	waitfanfare
	waitmessage
	msgbox BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass_hns, MSGBOX_DEFAULT
	setflag FLAG_SYS_FRONTIER_PASS
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier_hns, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_ExclamationMark
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, Common_Movement_ExclamationMark
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_PLAYER
	msgbox BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, BattleFrontier_ReceptionGate_Movement_GreeterFaceScott_hns
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott_hns
	applymovement LOCALID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerFaceScott_hns
	applymovement LOCALID_FRONTIER_RECEPTION_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottEnter_hns
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottExit_hns
	waitmovement 0
	removeobject LOCALID_FRONTIER_RECEPTION_SCOTT
	releaseall
	end

BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter_hns:
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_PlayerFaceScott_hns:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

@ Unused
BattleFrontier_ReceptionGate_Movement_WalkDown_hns:
	walk_down
	walk_down
	step_end

BattleFrontier_ReceptionGate_Movement_ScottEnter_hns:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_ScottExit_hns:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_ReceptionGate_Movement_GreeterFaceScott_hns:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott_hns:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

BattleFrontier_ReceptionGate_EventScript_Greeter_hns::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier_hns, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FacilityGuide_hns::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFacilities_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich2_hns
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BF_RECEPTIONIST
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_BattleTower_hns
	case 1, BattleFrontier_ReceptionGate_EventScript_BattleDome_hns
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePalace_hns
	case 3, BattleFrontier_ReceptionGate_EventScript_BattleArena_hns
	case 4, BattleFrontier_ReceptionGate_EventScript_BattleFactory_hns
	case 5, BattleFrontier_ReceptionGate_EventScript_BattlePike_hns
	case 6, BattleFrontier_ReceptionGate_EventScript_BattlePyramid_hns
	case 7, BattleFrontier_ReceptionGate_EventScript_RankingHall_hns
	case 8, BattleFrontier_ReceptionGate_EventScript_ExchangeCorner_hns
	case 9, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide_hns
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide_hns
	end

BattleFrontier_ReceptionGate_EventScript_BattleTower_hns::
	msgbox BattleFrontier_ReceptionGate_Text_BattleTowerInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_BattleDome_hns::
	msgbox BattleFrontier_ReceptionGate_Text_BattleDomeInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_BattlePalace_hns::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePalaceInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_BattleArena_hns::
	msgbox BattleFrontier_ReceptionGate_Text_BattleArenaInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_BattleFactory_hns::
	msgbox BattleFrontier_ReceptionGate_Text_BattleFactoryInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_BattlePike_hns::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePikeInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_BattlePyramid_hns::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePyramidInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_RankingHall_hns::
	msgbox BattleFrontier_ReceptionGate_Text_RankingHallInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_ExchangeCorner_hns::
	msgbox BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide_hns::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_RulesGuide_hns::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToRules_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout_hns::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhat_hns
	waitmessage
	multichoice 15, 0, MULTI_FRONTIER_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_LevelMode_hns
	case 1, BattleFrontier_ReceptionGate_EventScript_Level50_hns
	case 2, BattleFrontier_ReceptionGate_EventScript_OpenLevel_hns
	case 3, BattleFrontier_ReceptionGate_EventScript_MonEntry_hns
	case 4, BattleFrontier_ReceptionGate_EventScript_HoldItems_hns
	case 5, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide_hns
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide_hns
	end

BattleFrontier_ReceptionGate_EventScript_LevelMode_hns::
	msgbox BattleFrontier_ReceptionGate_Text_LevelModeInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_Level50_hns::
	msgbox BattleFrontier_ReceptionGate_Text_Level50Info_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_OpenLevel_hns::
	msgbox BattleFrontier_ReceptionGate_Text_OpenLevelInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_MonEntry_hns::
	msgbox BattleFrontier_ReceptionGate_Text_MonEntryInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_HoldItems_hns::
	msgbox BattleFrontier_ReceptionGate_Text_HoldItemsInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide_hns::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FrontierPassGuide_hns::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout_hns::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich1_hns
	waitmessage
	multichoice 16, 4, MULTI_FRONTIER_PASS_INFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_Symbols_hns
	case 1, BattleFrontier_ReceptionGate_EventScript_RecordBattle_hns
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePoints_hns
	case 3, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide_hns
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide_hns
	end

BattleFrontier_ReceptionGate_EventScript_Symbols_hns::
	msgbox BattleFrontier_ReceptionGate_Text_SymbolsInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_RecordBattle_hns::
	msgbox BattleFrontier_ReceptionGate_Text_RecordedBattleInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_BattlePoints_hns::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePointsInfo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout_hns
	end

BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide_hns::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay_hns:
	.string "¿Es tu primera vez aquí?\n"
	.string "¡Por aquí, por favor!$"

BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier_hns:
	.string "¡La vanguardia de las batallas\n"
	.string "¡Bienvenido al FRENTE DE BATALLA!$"

BattleFrontier_ReceptionGate_Text_IssueFrontierPass_hns:
	.string "A los visitantes primerizos les\n"
	.string "damos el PASE DEL FRENTE.\p"
	.string "Sirve para todas las instalaciones.\n"
	.string "en el FRENTE\nDE BATALLA.\p"
	.string "¡Aquí tienes!$"

BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass_hns:
	.string "{PLAYER} obtuvo\n"
	.string "el PASE DEL FRENTE.$"

BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass_hns:
	.string "{PLAYER} puso su\nFICHA DE ENTRENADOR\n"
	.string "en el PASE DEL FRENTE.$"

BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier_hns:
	.string "Esperamos que disfrutes todo lo que\n"
	.string "¡lo que FRONTIER ofrece!$"

BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame_hns:
	.string "???: ¡Vaya, pero si es {PLAYER}{KUN}!\n"
	.string "¡Así que viniste!$"

BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay_hns:
	.string "GUÍA: ¡Oh! ¡Sr. SCOTT, señor!\n"
	.string "¡Buen día tenga, señor!$"

BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere_hns:
	.string "SCOTT: Es genial verte aquí,\n"
	.string "¡de verdad lo es!\p"
	.string "Espero que te tomes tu tiempo y\n"
	.string "explores cada rincón.\p"
	.string "Naturalmente, espero que vivas\n"
	.string "la pura esencia de las batallas.\p"
	.string "Tengo mis cuartos aquí, así que\n"
	.string "visítalo si tienes tiempo.$"

BattleFrontier_ReceptionGate_Text_YourGuideToFacilities_hns:
	.string "Soy tu guía de las instalaciones\n"
	.string "del FRENTE DE BATALLA.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich2_hns:
	.string "¿Sobre cuál te gustaría aprender?$"

BattleFrontier_ReceptionGate_Text_BattleTowerInfo_hns:
	.string "Es la torre gigante considerada\n"
	.string "el símbolo del FRENTE DE BATALLA.\p"
	.string "Hay cuatro tipos de SALAS BATALLA\n"
	.string "para COMBATES INDIVIDUAL, DOBLE,\l"
	.string "MULTI y LINK MULTI.$"

BattleFrontier_ReceptionGate_Text_BattleDomeInfo_hns:
	.string "La CÚPULA BATALLA es el edificio\n"
	.string "con forma de huevo gigante.\p"
	.string "Se hacen eventos llamados Torneos\n"
	.string "en estas instalaciones.\p"
	.string "Los Torneos de Batalla se ofrecen en\n"
	.string "dos modalidades: COMBATES INDIV.\l"
	.string "y DOBLES.$"

BattleFrontier_ReceptionGate_Text_BattlePalaceInfo_hns:
	.string "El PALACIO BATALLA es el edificio\n"
	.string "rojo al este del FRENTE DE BATALLA.\p"
	.string "Hay dos tipos de SALAS BATALLA\n"
	.string "para COMBATES INDIV. y DOBLES.$"

BattleFrontier_ReceptionGate_Text_BattleArenaInfo_hns:
	.string "El DOJO BATALLA es el edificio\n"
	.string "tipo dojo en el centro-derecha de\l"
	.string "el FRENTE DE BATALLA.\p"
	.string "Un evento llamado Torneo de KO Fijo\n"
	.string "es en el DOJO BATALLA.$"

BattleFrontier_ReceptionGate_Text_BattleFactoryInfo_hns:
	.string "La FÁBRICA BATALLA es el gran\n"
	.string "el edificio más cercano a nosotros.\p"
	.string "Allí se realiza un evento llamado\n"
	.string "se lleva a cabo allí.\p"
	.string "El Intercambio de Batalla ofrece\n"
	.string "dos cursos: INDIVIDUAL y DOBLE\l"
	.string "y DOBLES.$"

BattleFrontier_ReceptionGate_Text_BattlePikeInfo_hns:
	.string "La LANZA DE BATALLA es el edificio\n"
	.string "como un POKéMON al centro-izquierda\l"
	.string "el FRENTE DE BATALLA.\p"
	.string "Allí se realiza un evento llamado\n"
	.string "Elección de Batalla.$"

BattleFrontier_ReceptionGate_Text_BattlePyramidInfo_hns:
	.string "La PIRÁMIDE BATALLA es la enorme\n"
	.string "pirámide.\p"
	.string "Un evento llamado Búsqueda de Batalla\n"
	.string "se lleva a cabo allí.$"

BattleFrontier_ReceptionGate_Text_RankingHallInfo_hns:
	.string "El HALL DE LAS\nCLASIFICACIONES está cerca\n"
	.string "de la TORRE BATALLA.\p"
	.string "Allí verás los récords más increíbles\n"
	.string "dejados por los ENTRENADORES que\l"
	.string "superaron los retos de la\l"
	.string "FRENTE DE BATALLA.$"

BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo_hns:
	.string "El CENTRO DEL\nSERVICIO DE CANJE está cerca\n"
	.string "de la TORRE BATALLA.\p"
	.string "Los Puntos de Batalla ganados en la\n"
	.string "FRENTE DE BATALLA pueden canjearse\l"
	.string "por premios fabulosos allí.$"

BattleFrontier_ReceptionGate_Text_YourGuideToRules_hns:
	.string "Soy tu guía sobre las reglas básicas\n"
	.string "que son comunes en todos los retos\l"
	.string "de las instalaciones de la BATTLE\l"
	.string "FRONTIER.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhat_hns:
	.string "¿Sobre qué te gustaría aprender?$"

BattleFrontier_ReceptionGate_Text_LevelModeInfo_hns:
	.string "Los retos del FRENTE DE BATALLA\n"
	.string "se dividen en dos categorías:\l"
	.string "Nivel 50 y Nivel Abierto.$"

BattleFrontier_ReceptionGate_Text_Level50Info_hns:
	.string "El curso Nivel 50 es para POKéMON\n"
	.string "de Nivel 50 o inferior.\p"
	.string "Ten en cuenta, sin embargo, que\n"
	.string "ningún ENTRENADOR tendrá\l"
	.string "POKéMON por debajo del Nivel 50.\p"
	.string "Este curso es el nivel básico para\n"
	.string "luchar en el FRENTE DE BATALLA.\p"
	.string "Para empezar, esperamos que aceptes\n"
	.string "este desafío.$"

BattleFrontier_ReceptionGate_Text_OpenLevelInfo_hns:
	.string "El Nivel Abierto no pone límites\n"
	.string "a los niveles de los POKéMON que\l"
	.string "participen.\p"
	.string "Los niveles de tus rivales se\n"
	.string "ajustarán para coincidir con los\l"
	.string "de tus POKéMON.\p"
	.string "Aun así, ningún ENTRENADOR tendrá\n"
	.string "POKéMON por debajo del Nivel 60.$"

BattleFrontier_ReceptionGate_Text_MonEntryInfo_hns:
	.string "Casi cualquier POKéMON puede\n"
	.string "en los retos de todas las sedes.\p"
	.string "HUEVOS y ciertos POKéMON,\n"
	.string "sin embargo, no están permitidos.\p"
	.string "El número de POKéMON requeridos\n"
	.string "dependerá de cada instalación.\p"
	.string "En todas, no se permiten dos o más\n"
	.string "POKéMON de la misma especie\l"
	.string "en el equipo.$"

BattleFrontier_ReceptionGate_Text_HoldItemsInfo_hns:
	.string "Al entrar a un reto de la BATTLE\n"
	.string "FRONTIER, los POKéMON no pueden\l"
	.string "llevar el mismo objeto.\p"
	.string "Asegúrate de que todos los POKéMON\n"
	.string "que entren al desafío lleven\l"
	.string "objetos diferentes.$"

BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass_hns:
	.string "Soy tu guía para el PASE DEL FRENTE.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich1_hns:
	.string "¿Sobre cuál te gustaría aprender?$"

BattleFrontier_ReceptionGate_Text_SymbolsInfo_hns:
	.string "Hay siete instalaciones en el\n"
	.string "el FRENTE DE BATALLA.\p"
	.string "ENTRENADORES que demuestren su\n"
	.string "habilidad podrán ganar\l"
	.string "símbolos de cada instalación.\p"
	.string "Para ganar un símbolo, debes\n"
	.string "vencer ENTRENADORES seguidos\l"
	.string "o ganar eventos repetidamente.\p"
	.string "No es nada fácil ganar símbolos.\n"
	.string "¡Te deseo mucha suerte!$"

BattleFrontier_ReceptionGate_Text_RecordedBattleInfo_hns:
	.string "Es posible grabar una batalla\n"
	.string "en tu PASE DEL FRENTE.\p"
	.string "Puedes grabar una batalla que hayas\n"
	.string "tenido con amigos.\p"
	.string "O puedes grabar una batalla hecha\n"
	.string "en el FRENTE DE BATALLA, excepto\l"
	.string "combates en la SIERPE\nBATALLA o\l"
	.string "en la PIRÁMIDE BATALLA.\p"
	.string "Puedes elegir grabar tu combate\n"
	.string "al final de la batalla.$"

BattleFrontier_ReceptionGate_Text_BattlePointsInfo_hns:
	.string "Los Puntos de Batalla son premios para\n"
	.string "ENTRENADORES que lucharon muy bien\l"
	.string "en el FRENTE DE BATALLA.\p"
	.string "Puedes canjear tus Puntos de Batalla\n"
	.string "por premios en el SERVICIO DE\l"
	.string "CANJE.$"

