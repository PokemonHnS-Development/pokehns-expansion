BattleFrontier_ReceptionGate_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_ReceptionGate_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_ReceptionGate_OnTransition
	.byte 0

BattleFrontier_ReceptionGate_OnTransition:
	setflag FLAG_LANDMARK_BATTLE_FRONTIER
	end

BattleFrontier_ReceptionGate_OnFrame:
	map_script_2 VAR_HAS_ENTERED_BATTLE_FRONTIER, 0, BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering
	.2byte 0

BattleFrontier_ReceptionGate_EventScript_FirstTimeEntering::
	lockall
	setvar VAR_HAS_ENTERED_BATTLE_FRONTIER, 1
	playse SE_PIN
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_Delay48
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter
	waitmovement 0
	goto BattleFrontier_ReceptionGate_EventScript_ScottScene
	end

BattleFrontier_ReceptionGate_EventScript_ScottScene::
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IssueFrontierPass, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass
	waitfanfare
	waitmessage
	msgbox BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass, MSGBOX_DEFAULT
	setflag FLAG_SYS_FRONTIER_PASS
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, Common_Movement_ExclamationMark
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, Common_Movement_ExclamationMark
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_GREETER, BattleFrontier_ReceptionGate_Movement_GreeterFaceScott
	applymovement LOCALID_FRONTIER_RECEPTION_GUIDE, BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott
	applymovement LOCALID_PLAYER, BattleFrontier_ReceptionGate_Movement_PlayerFaceScott
	applymovement LOCALID_FRONTIER_RECEPTION_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottEnter
	waitmovement 0
	msgbox BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_FRONTIER_RECEPTION_SCOTT, BattleFrontier_ReceptionGate_Movement_ScottExit
	waitmovement 0
	removeobject LOCALID_FRONTIER_RECEPTION_SCOTT
	releaseall
	end

BattleFrontier_ReceptionGate_Movement_PlayerApproachCounter:
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_PlayerFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

@ Unused
BattleFrontier_ReceptionGate_Movement_WalkDown:
	walk_down
	walk_down
	step_end

BattleFrontier_ReceptionGate_Movement_ScottEnter:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	step_end

BattleFrontier_ReceptionGate_Movement_ScottExit:
	walk_right
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

BattleFrontier_ReceptionGate_Movement_GreeterFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_right
	step_end

BattleFrontier_ReceptionGate_Movement_FacilityGuideFaceScott:
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_faster_left
	step_end

BattleFrontier_ReceptionGate_EventScript_Greeter::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier, MSGBOX_DEFAULT
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FacilityGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFacilities, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich2
	waitmessage
	setvar VAR_0x8004, SCROLL_MULTI_BF_RECEPTIONIST
	special ShowScrollableMultichoice
	waitstate
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_BattleTower
	case 1, BattleFrontier_ReceptionGate_EventScript_BattleDome
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePalace
	case 3, BattleFrontier_ReceptionGate_EventScript_BattleArena
	case 4, BattleFrontier_ReceptionGate_EventScript_BattleFactory
	case 5, BattleFrontier_ReceptionGate_EventScript_BattlePike
	case 6, BattleFrontier_ReceptionGate_EventScript_BattlePyramid
	case 7, BattleFrontier_ReceptionGate_EventScript_RankingHall
	case 8, BattleFrontier_ReceptionGate_EventScript_ExchangeCorner
	case 9, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide
	end

BattleFrontier_ReceptionGate_EventScript_BattleTower::
	msgbox BattleFrontier_ReceptionGate_Text_BattleTowerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleDome::
	msgbox BattleFrontier_ReceptionGate_Text_BattleDomeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePalace::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePalaceInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleArena::
	msgbox BattleFrontier_ReceptionGate_Text_BattleArenaInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattleFactory::
	msgbox BattleFrontier_ReceptionGate_Text_BattleFactoryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePike::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePikeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePyramid::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePyramidInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RankingHall::
	msgbox BattleFrontier_ReceptionGate_Text_RankingHallInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExchangeCorner::
	msgbox BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFacilityToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFacilityGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_RulesGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToRules, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhat
	waitmessage
	multichoice 15, 0, MULTI_FRONTIER_RULES, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_LevelMode
	case 1, BattleFrontier_ReceptionGate_EventScript_Level50
	case 2, BattleFrontier_ReceptionGate_EventScript_OpenLevel
	case 3, BattleFrontier_ReceptionGate_EventScript_MonEntry
	case 4, BattleFrontier_ReceptionGate_EventScript_HoldItems
	case 5, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide
	end

BattleFrontier_ReceptionGate_EventScript_LevelMode::
	msgbox BattleFrontier_ReceptionGate_Text_LevelModeInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_Level50::
	msgbox BattleFrontier_ReceptionGate_Text_Level50Info, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_OpenLevel::
	msgbox BattleFrontier_ReceptionGate_Text_OpenLevelInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_MonEntry::
	msgbox BattleFrontier_ReceptionGate_Text_MonEntryInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_HoldItems::
	msgbox BattleFrontier_ReceptionGate_Text_HoldItemsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseRuleToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitRulesGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_EventScript_FrontierPassGuide::
	lock
	faceplayer
	msgbox BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout::
	message BattleFrontier_ReceptionGate_Text_LearnAboutWhich1
	waitmessage
	multichoice 16, 4, MULTI_FRONTIER_PASS_INFO, FALSE
	switch VAR_RESULT
	case 0, BattleFrontier_ReceptionGate_EventScript_Symbols
	case 1, BattleFrontier_ReceptionGate_EventScript_RecordBattle
	case 2, BattleFrontier_ReceptionGate_EventScript_BattlePoints
	case 3, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	case MULTI_B_PRESSED, BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide
	end

BattleFrontier_ReceptionGate_EventScript_Symbols::
	msgbox BattleFrontier_ReceptionGate_Text_SymbolsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_RecordBattle::
	msgbox BattleFrontier_ReceptionGate_Text_RecordedBattleInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_BattlePoints::
	msgbox BattleFrontier_ReceptionGate_Text_BattlePointsInfo, MSGBOX_DEFAULT
	goto BattleFrontier_ReceptionGate_EventScript_ChooseFrontierPassInfoToLearnAbout
	end

BattleFrontier_ReceptionGate_EventScript_ExitFrontierPassGuide::
	msgbox BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ReceptionGate_Text_FirstTimeHereThisWay:
	.string "¿Es tu primera vez aquí?\n"
	.string "¡Por aquí, por favor!$"

BattleFrontier_ReceptionGate_Text_WelcomeToBattleFrontier:
	.string "¡La vanguardia de las batallas\n"
	.string "¡Bienvenido a la BATTLE FRONTIER!$"

BattleFrontier_ReceptionGate_Text_IssueFrontierPass:
	.string "A los visitantes primerizos les\n"
	.string "damos el FRONTIER PASS.\p"
	.string "Sirve para todas las instalaciones.\n"
	.string "en la BATTLE FRONTIER.\p"
	.string "¡Aquí tienes!$"

BattleFrontier_ReceptionGate_Text_ObtainedFrontierPass:
	.string "{PLAYER} obtuvo\n"
	.string "el FRONTIER PASS.$"

BattleFrontier_ReceptionGate_Text_PlacedTrainerCardInFrontierPass:
	.string "{PLAYER} puso su TRAINER CARD\n"
	.string "en el FRONTIER PASS.$"

BattleFrontier_ReceptionGate_Text_EnjoyBattleFrontier:
	.string "Esperamos que disfrutes todo lo que\n"
	.string "¡lo que FRONTIER ofrece!$"

BattleFrontier_ReceptionGate_Text_IfItIsntPlayerYouCame:
	.string "???: ¡Vaya, pero si es {PLAYER}{KUN}!\n"
	.string "¡Así que viniste!$"

BattleFrontier_ReceptionGate_Text_OhMrScottGoodDay:
	.string "GUÍA: ¡Oh! ¡Sr. SCOTT, señor!\n"
	.string "¡Buen día tenga, señor!$"

BattleFrontier_ReceptionGate_Text_ScottGreatToSeeYouHere:
	.string "SCOTT: Es genial verte aquí,\n"
	.string "¡de verdad lo es!\p"
	.string "Espero que te tomes tu tiempo y\n"
	.string "explores cada rincón.\p"
	.string "Naturalmente, espero que vivas\n"
	.string "la pura esencia de las batallas.\p"
	.string "Tengo mis cuartos aquí, así que\n"
	.string "visítalo si tienes tiempo.$"

BattleFrontier_ReceptionGate_Text_YourGuideToFacilities:
	.string "Soy tu guía de las instalaciones\n"
	.string "de la BATTLE FRONTIER.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich2:
	.string "¿Sobre qué te gustaría saber?$"

BattleFrontier_ReceptionGate_Text_BattleTowerInfo:
	.string "Es la torre gigante considerada\n"
	.string "el símbolo de la BATTLE FRONTIER.\p"
	.string "Hay cuatro tipos de BATTLE ROOMS\n"
	.string "para COMBATES INDIVIDUAL, DOBLE,\l"
	.string "MULTI y LINK MULTI.$"

BattleFrontier_ReceptionGate_Text_BattleDomeInfo:
	.string "El BATTLE DOME es el edificio\n"
	.string "con forma de huevo gigante.\p"
	.string "Se hacen eventos llamados Torneos\n"
	.string "en estas instalaciones.\p"
	.string "Los Torneos de Batalla se ofrecen en\n"
	.string "dos modalidades: COMBATES INDIV.\l"
	.string "y DOBLES.$"

BattleFrontier_ReceptionGate_Text_BattlePalaceInfo:
	.string "El PALACIO DE COMBATE es el edificio\n"
	.string "rojo a la derecha de la FRONTERA.\p"
	.string "Hay dos tipos de SALAS DE COMBATE\n"
	.string "para COMBATES INDIV. y DOBLES.$"

BattleFrontier_ReceptionGate_Text_BattleArenaInfo:
	.string "La ARENA DE COMBATE es el edificio\n"
	.string "tipo dojo en el centro-derecha de\l"
	.string "la FRONTERA DE BATALLA.\p"
	.string "Un evento llamado Torneo de KO Fijo\n"
	.string "es en la ARENA DE BATALLA.$"

BattleFrontier_ReceptionGate_Text_BattleFactoryInfo:
	.string "La FÁBRICA DE BATALLA es el gran\n"
	.string "el edificio más cercano a nosotros.\p"
	.string "Allí se realiza un evento llamado\n"
	.string "se lleva a cabo allí.\p"
	.string "El Intercambio de Batalla ofrece\n"
	.string "dos cursos: INDIVIDUAL y DOBLE\l"
	.string "y DOBLES.$"

BattleFrontier_ReceptionGate_Text_BattlePikeInfo:
	.string "La LANZA DE BATALLA es el edificio\n"
	.string "como un POKéMON al centro-izquierda\l"
	.string "la FRONTERA DE BATALLA.\p"
	.string "Allí se realiza un evento llamado\n"
	.string "Elección de Batalla.$"

BattleFrontier_ReceptionGate_Text_BattlePyramidInfo:
	.string "La PIRÁMIDE DE BATALLA es la enorme\n"
	.string "pirámide.\p"
	.string "Un evento llamado Battle Quest\n"
	.string "Elección de Batalla.$"

BattleFrontier_ReceptionGate_Text_RankingHallInfo:
	.string "El RANKING HALL está ubicado cerca\n"
	.string "de la BATTLE TOWER.\p"
	.string "Allí verás los récords más increíbles\n"
	.string "dejados por los ENTRENADORES que\l"
	.string "superaron los retos de la\l"
	.string "BATTLE FRONTIER.$"

BattleFrontier_ReceptionGate_Text_ExchangeCornerInfo:
	.string "El EXCHANGE SERVICE CORNER está cerca\n"
	.string "de la BATTLE TOWER.\p"
	.string "Los Battle Points que ganaste en la\n"
	.string "BATTLE FRONTIER pueden canjearse\l"
	.string "por premios fabulosos allí.$"

BattleFrontier_ReceptionGate_Text_YourGuideToRules:
	.string "Soy tu guía sobre las reglas básicas\n"
	.string "que son comunes en todos los retos\l"
	.string "de las instalaciones de la BATTLE\l"
	.string "FRONTIER.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhat:
	.string "¿Sobre qué te gustaría saber?$"

BattleFrontier_ReceptionGate_Text_LevelModeInfo:
	.string "Los retos de la BATTLE FRONTIER\n"
	.string "se dividen en dos categorías:\l"
	.string "Nivel 50 y Nivel Abierto.$"

BattleFrontier_ReceptionGate_Text_Level50Info:
	.string "El curso Nivel 50 es para POKéMON\n"
	.string "de Nivel 50 o inferior.\p"
	.string "Ten en cuenta, sin embargo, que\n"
	.string "ningún ENTRENADOR tendrá\l"
	.string "POKéMON por debajo del Nivel 50.\p"
	.string "Este curso es el nivel básico para\n"
	.string "luchar en la BATTLE FRONTIER.\p"
	.string "Para empezar, esperamos que aceptes\n"
	.string "este desafío.$"

BattleFrontier_ReceptionGate_Text_OpenLevelInfo:
	.string "El Nivel Abierto no pone límites\n"
	.string "a los niveles de los POKéMON que\l"
	.string "participen.\p"
	.string "Los niveles de tus rivales se\n"
	.string "ajustarán para coincidir con los\l"
	.string "de tus POKéMON.\p"
	.string "Aun así, ningún ENTRENADOR tendrá\n"
	.string "POKéMON por debajo del Nivel 60.$"

BattleFrontier_ReceptionGate_Text_MonEntryInfo:
	.string "Casi cualquier POKéMON puede\n"
	.string "en los retos de todas las sedes.\p"
	.string "HUEVOS y ciertos POKéMON,\n"
	.string "sin embargo, no están permitidos.\p"
	.string "El número de POKéMON requeridos\n"
	.string "dependerá de cada instalación.\p"
	.string "En todas, no se permiten dos o más\n"
	.string "POKéMON de la misma especie\l"
	.string "en el equipo.$"

BattleFrontier_ReceptionGate_Text_HoldItemsInfo:
	.string "Al entrar a un reto de la BATTLE\n"
	.string "FRONTIER, los POKéMON no pueden\l"
	.string "llevar el mismo objeto.\p"
	.string "Asegúrate de que todos los POKéMON\n"
	.string "que entren al desafío lleven\l"
	.string "objetos diferentes.$"

BattleFrontier_ReceptionGate_Text_YourGuideToFrontierPass:
	.string "Soy tu guía del PASE FRONTERA.$"

BattleFrontier_ReceptionGate_Text_LearnAboutWhich1:
	.string "¿Sobre qué te gustaría saber?$"

BattleFrontier_ReceptionGate_Text_SymbolsInfo:
	.string "Hay siete instalaciones en el\n"
	.string "la FRONTERA DE BATALLA.\p"
	.string "ENTRENADORES que demuestren su\n"
	.string "habilidad podrán ganar\l"
	.string "símbolos de cada instalación.\p"
	.string "Para ganar un símbolo, debes\n"
	.string "vencer ENTRENADORES seguidos\l"
	.string "o ganar eventos repetidamente.\p"
	.string "No es nada fácil ganar símbolos.\n"
	.string "¡Te deseo mucha suerte!$"

BattleFrontier_ReceptionGate_Text_RecordedBattleInfo:
	.string "Es posible grabar una batalla\n"
	.string "en tu FRONTIER PASS.\p"
	.string "Puedes grabar una batalla que hayas\n"
	.string "tenido con amigos.\p"
	.string "O puedes grabar una batalla hecha\n"
	.string "en la BATTLE FRONTIER, excepto\l"
	.string "combates en la BATTLE PIKE o\l"
	.string "en la BATTLE PYRAMID.\p"
	.string "Puedes elegir grabar tu combate\n"
	.string "al final de la batalla.$"

BattleFrontier_ReceptionGate_Text_BattlePointsInfo:
	.string "Los Battle Points son premios que\n"
	.string "ENTRENADORES que lucharon muy bien\l"
	.string "en la FRONTERA DE BATALLA.\p"
	.string "Puedes canjear tus Puntos de Batalla\n"
	.string "por premios en el SERVICIO DE\l"
	.string "CANJE.$"

