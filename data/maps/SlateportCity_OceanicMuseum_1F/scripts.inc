SlateportCity_OceanicMuseum_1F_MapScripts::
	.byte 0

SlateportCity_OceanicMuseum_1F_EventScript_EntranceAttendant::
	msgbox SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeLeft::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFeeRight::
	lockall
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee
	end

SlateportCity_OceanicMuseum_1F_EventScript_PayEntranceFee::
	showmoneybox 0, 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_WouldYouLikeToEnter, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, SlateportCity_OceanicMuseum_1F_EventScript_CheckMoneyForFee
	closemessage
	hidemoneybox
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_CheckMoneyForFee::
	checkmoney 50
	goto_if_eq VAR_RESULT, FALSE, SlateportCity_OceanicMuseum_1F_EventScript_NotEnoughMoney
	playse SE_SHOP
	removemoney 50
	updatemoneybox
	msgbox SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	hidemoneybox
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_NotEnoughMoney::
	goto_if_unset FLAG_DELIVERED_DEVON_GOODS, SlateportCity_OceanicMuseum_1F_EventScript_AllowEntranceAnyway
	msgbox SlateportCity_OceanicMuseum_1F_Text_NotEnoughMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter
	waitmovement 0
	releaseall
	end

SlateportCity_OceanicMuseum_1F_EventScript_AllowEntranceAnyway::
	msgbox SlateportCity_OceanicMuseum_1F_Text_CatchUpWithYourGroup, MSGBOX_DEFAULT
	setvar VAR_SLATEPORT_MUSEUM_1F_STATE, 1
	hidemoneybox
	releaseall
	end

SlateportCity_OceanicMuseum_1F_Movement_PushPlayerBackFromCounter:
	walk_down
	step_end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_AquaExistForGoodOfAll, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OurBossIsntHere, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WouldStuffHereMakeMeRich, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt4::
	msgbox SlateportCity_OceanicMuseum_1F_Text_CanLearnForNefariousDeeds, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt5::
	msgbox SlateportCity_OceanicMuseum_1F_Text_RustboroBungled, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumGrunt6::
	msgbox SlateportCity_OceanicMuseum_1F_Text_DidntHaveMoney, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_WhirlpoolExperiment::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WhirlpoolExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_WaterfallExperiment::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WaterfallExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanSoilDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanSoilDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_BeachSandDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_BeachSandDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_OceanicMinifact3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact3, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_FossilDisplay::
	msgbox SlateportCity_OceanicMuseum_1F_Text_FossilDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_DepthMeasuringMachine::
	msgbox SlateportCity_OceanicMuseum_1F_Text_DepthMeasuringMachine, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron1::
	msgbox SlateportCity_OceanicMuseum_1F_Text_LearnAboutSeaForBattling, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron2::
	msgbox SlateportCity_OceanicMuseum_1F_Text_SternIsRoleModel, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron3::
	msgbox SlateportCity_OceanicMuseum_1F_Text_MustBePokemonWeDontKnow, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_MuseumPatron4::
	msgbox SlateportCity_OceanicMuseum_1F_Text_WantSeaPokemon, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGrunt::
	lock
	faceplayer
	delay 8
	playse SE_PIN
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, Common_Movement_Delay48
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_THIEF
	goto_if_eq VAR_RESULT, 0, SlateportCity_OceanicMuseum_1F_EventScript_NoRoomForThief
	setflag FLAG_RECEIVED_TM_THIEF
	msgbox SlateportCity_OceanicMuseum_1F_Text_HopeINeverSeeYouAgain, MSGBOX_DEFAULT
	closemessage
	goto_if_eq VAR_FACING, DIR_NORTH, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitNorth
	goto_if_eq VAR_FACING, DIR_SOUTH, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitSouth
	goto_if_eq VAR_FACING, DIR_WEST, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast
	goto_if_eq VAR_FACING, DIR_EAST, SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitNorth::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitNorth
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExitNorth
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitSouth::
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExitWestEast::
	applymovement LOCALID_PLAYER, SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitWestEast
	applymovement LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT, SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit
	waitmovement 0
	goto SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited
	end

SlateportCity_OceanicMuseum_1F_EventScript_FamiliarGruntExited::
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_FAMILIAR_AQUA_GRUNT
	playse SE_EXIT
	removeobject LOCALID_OCEANIC_MUSEUM_FAMILIAR_GRUNT
	release
	end

SlateportCity_OceanicMuseum_1F_EventScript_NoRoomForThief::
	msgbox SlateportCity_OceanicMuseum_1F_Text_YouHaveToTakeThis, MSGBOX_DEFAULT
	release
	end

SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitNorth:
	delay_16
	delay_8
	delay_4
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_1F_Movement_PlayerWatchGruntExitWestEast:
	delay_16
	walk_in_place_faster_down
	step_end

SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExit:
	face_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

SlateportCity_OceanicMuseum_1F_Movement_FamiliarGruntExitNorth:
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

SlateportCity_OceanicMuseum_1F_Text_WouldYouLikeToEnter:
	.string "Bienvenido al MUSEO OCEÁNICO.\p"
	.string "La entrada cuesta ¥50.\n"
	.string "¿Te gustaría entrar?$"

SlateportCity_OceanicMuseum_1F_Text_PleaseEnjoyYourself:
	.string "Please enjoy yourself.$"

SlateportCity_OceanicMuseum_1F_Text_NotEnoughMoney:
	.string "¿Oh? Lo siento, pero parece que no\n"
	.string "tienes suficiente dinero.$"

SlateportCity_OceanicMuseum_1F_Text_CatchUpWithYourGroup:
	.string "¿Oh? ¿Estás con el grupo que\n"
	.string "entró hace un momento?\p"
	.string "Eres el único que llega tarde.\n"
	.string "¡Mejor ve a alcanzarlos!$"

SlateportCity_OceanicMuseum_1F_Text_AquaExistForGoodOfAll:
	.string "¡Nosotros, el TEAM AQUA, existimos\n"
	.string "por el bien de todos!$"

SlateportCity_OceanicMuseum_1F_Text_OurBossIsntHere:
	.string "Nos dijeron que nos reuniéramos\n"
	.string "aquí, así que lo hicimos, pero...\p"
	.string "Nuestro JEFE, el líder, no está.$"

SlateportCity_OceanicMuseum_1F_Text_WouldStuffHereMakeMeRich:
	.string "Si robara las cosas de aquí,\n"
	.string "¿me haría rico?$"

SlateportCity_OceanicMuseum_1F_Text_CanLearnForNefariousDeeds:
	.string "Lo que aprenda aquí, podré usarlo\n"
	.string "en actos nefarios...$"

SlateportCity_OceanicMuseum_1F_Text_RustboroBungled:
	.string "¡Si nuestros secuaces no hubieran\n"
	.string "¡en RUSTBORO, no estaríamos aquí!$"

SlateportCity_OceanicMuseum_1F_Text_DidntHaveMoney:
	.string "No tenía ¥50, así que tardé mucho\n"
	.string "en pasar por la recepción.$"

SlateportCity_OceanicMuseum_1F_Text_LearnAboutSeaForBattling:
	.string "Quiero aprender sobre el mar y\n"
	.string "usa ese saber para combatir.$"

SlateportCity_OceanicMuseum_1F_Text_SternIsRoleModel:
	.string "Me pongo muy feliz y emocionado\n"
	.string "¡cuando veo el mar!\p"
	.string "Para mí, el CAPT. STERN es el\n"
	.string "mejor ejemplo a seguir!$"

SlateportCity_OceanicMuseum_1F_Text_MustBePokemonWeDontKnow:
	.string "El mar es vasto y sin final, y\n"
	.string "está infinitamente profundo…\p"
	.string "Debe haber muchos POKéMON que\n"
	.string "aún no conocemos.$"

SlateportCity_OceanicMuseum_1F_Text_WantSeaPokemon:
	.string "Quiero un POKéMON marino.\p"
	.string "Creo que se sentiría genial y lindo\n"
	.string "al abrazarlo.$"

SlateportCity_OceanicMuseum_1F_Text_RememberMeTakeThis:
	.string "¡Aiyeeeh!\n"
	.string "¿Qué haces aquí?\p"
	.string "¿Yo? Soy el miembro del TEAM AQUA\n"
	.string "al que venciste, ¿recuerdas?\l"
	.string "¿En el TÚNEL RUSTURF?\p"
	.string "¡Toma, ten esto!\n"
	.string "¡Tienes que perdonarme!$"

SlateportCity_OceanicMuseum_1F_Text_HopeINeverSeeYouAgain:
	.string "Esa MT te queda mejor a ti que\n"
	.string "a mí.\p"
	.string "¡Espero no verte nunca más!\n"
	.string "¡Jajajaja!$"

SlateportCity_OceanicMuseum_1F_Text_YouHaveToTakeThis:
	.string "¡Ay, vamos!\n"
	.string "¡Toma esto y déjame ir!$"

SlateportCity_OceanicMuseum_1F_Text_WhirlpoolExperiment:
	.string "Un fluido azul gira dentro de\n"
	.string "un recipiente de vidrio.\p"
	.string "“Es un experimento para crear un\n"
	.string "REMOLINO artificial usando viento.”$"

SlateportCity_OceanicMuseum_1F_Text_WaterfallExperiment:
	.string "Una bola roja sube y baja\n"
	.string "dentro de un recipiente de vidrio.\p"
	.string "“Es un experimento que simula una\n"
	.string "CASCADA usando la flotabilidad.”$"

SlateportCity_OceanicMuseum_1F_Text_OceanSoilDisplay:
	.string "Es una muestra de suelo del fondo\n"
	.string "del océano.\p"
	.string "“Tras muchos años, los restos de\n"
	.string "seres vivos caen al fondo del mar,\l"
	.string "creando capas sedimentarias.\p"
	.string "“Al analizar estas capas, el\n"
	.string "el pasado antiguo se revela.”$"

SlateportCity_OceanicMuseum_1F_Text_BeachSandDisplay:
	.string "Es una muestra de arena de playa.\p"
	.string "“Piedras de montañas son arrastradas\n"
	.string "por ríos donde son\l"
	.string "desgastadas y trituradas.\p"
	.string "“Se reducen a granos y terminan\n"
	.string "como arena en las playas.”$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact1:
	.string "“DATO OCEÁNICO 1\n"
	.string "¿Por qué el mar es azul?\p"
	.string "“La luz tiene muchos colores.\p"
	.string "“Cuando la luz pasa por el agua,\n"
	.string "la mayoría de luces pierden color.\p"
	.string "“Sin embargo, la luz azul mantiene\n"
	.string "su color, haciendo el mar azul.”$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact2:
	.string "“DATO OCEÁNICO 2\n"
	.string "¿Por qué el mar es salado?\p"
	.string "“El agua de mar tiene sal disuelta\n"
	.string "como iones de sodio y cloro.\p"
	.string "“Estos iones salen de las rocas\n"
	.string "y la lluvia los lleva hacia el mar.\p"
	.string "“La concentración de sal disuelta\n"
	.string "hace que el mar sea salado.”$"

SlateportCity_OceanicMuseum_1F_Text_OceanicMinifact3:
	.string "“DATO OCEÁNICO 3\n"
	.string "¿Qué es más grande? ¿Mar o tierra?\p"
	.string "“El mar cubre cerca del 70% del\n"
	.string "planeta, y el resto es tierra.\p"
	.string "“Por eso, el mar es más del doble\n"
	.string "del tamaño de la tierra.”$"

SlateportCity_OceanicMuseum_1F_Text_FossilDisplay:
	.string "Es un fósil con crestas onduladas.\p"
	.string "“El suelo del fondo marino es\n"
	.string "lavado por la marea.\p"
	.string "“El agua marca el suelo con\n"
	.string "pequeñas crestas y valles.\p"
	.string "“Si este suelo se fosiliza, se\n"
	.string "llama marca de rizo.”$"

SlateportCity_OceanicMuseum_1F_Text_DepthMeasuringMachine:
	.string "Una máquina gira debajo\n"
	.string "una cúpula de vidrio.\p"
	.string "Tal vez sea para medir la profundidad\n"
	.string "de algo...$"

