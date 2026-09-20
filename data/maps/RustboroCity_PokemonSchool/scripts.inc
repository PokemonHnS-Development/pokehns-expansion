RustboroCity_PokemonSchool_MapScripts::
	.byte 0

RustboroCity_PokemonSchool_EventScript_Blackboard::
	lockall
	msgbox RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic::
	message RustboroCity_PokemonSchool_Text_ReadWhichTopic
	waitmessage
	multichoicegrid 8, 1, MULTI_STATUS_INFO, 3, FALSE
	switch VAR_RESULT
	case 0, RustboroCity_PokemonSchool_EventScript_Poison
	case 1, RustboroCity_PokemonSchool_EventScript_Paralysis
	case 2, RustboroCity_PokemonSchool_EventScript_Sleep
	case 3, RustboroCity_PokemonSchool_EventScript_Burn
	case 4, RustboroCity_PokemonSchool_EventScript_Freeze
	case 5, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
	case MULTI_B_PRESSED, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
	end

RustboroCity_PokemonSchool_EventScript_Poison::
	msgbox RustboroCity_PokemonSchool_Text_ExplainPoison, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Paralysis::
	msgbox RustboroCity_PokemonSchool_Text_ExplainParalysis, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Sleep::
	msgbox RustboroCity_PokemonSchool_Text_ExplainSleep, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Burn::
	msgbox RustboroCity_PokemonSchool_Text_ExplainBurn, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_Freeze::
	msgbox RustboroCity_PokemonSchool_Text_ExplainFreeze, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
	end

RustboroCity_PokemonSchool_EventScript_ExitTopicSelect::
	releaseall
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid1::
	msgbox RustboroCity_PokemonSchool_Text_TradingRightNow, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_GameboyKid2::
	msgbox RustboroCity_PokemonSchool_Text_AlwaysWantedSeedot, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_RichBoy::
	msgbox RustboroCity_PokemonSchool_Text_PokemontCantUseManMadeItems, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_Lass::
	msgbox RustboroCity_PokemonSchool_Text_ConfusedPokemonAttacksItself, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_SchoolKidM::
	msgbox RustboroCity_PokemonSchool_Text_PokemonHealItselfWithBerry, MSGBOX_NPC
	end

RustboroCity_PokemonSchool_EventScript_StudentNotebook::
	msgbox RustboroCity_PokemonSchool_Text_StudentsNotes, MSGBOX_SIGN
	end

RustboroCity_PokemonSchool_EventScript_Teacher::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_QUICK_CLAW, RustboroCity_PokemonSchool_EventScript_GaveQuickClaw
	call_if_eq VAR_FACING, DIR_EAST, RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast
	call_if_eq VAR_FACING, DIR_WEST, RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest
	msgbox RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw, MSGBOX_DEFAULT
	giveitem ITEM_QUICK_CLAW
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	setflag FLAG_RECEIVED_QUICK_CLAW
	release
	end

RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast::
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast
	waitmovement 0
	return

RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest::
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest
	waitmovement 0
	return

RustboroCity_PokemonSchool_EventScript_GaveQuickClaw::
	msgbox RustboroCity_PokemonSchool_Text_ExplainQuickClaw, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	release
	end

RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest:
	walk_left
	walk_down
	walk_down
	walk_right
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_faster_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	walk_right
	step_end

RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast:
	walk_right
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_in_place_faster_down
	delay_16
	delay_16
	delay_16
	walk_down
	walk_in_place_faster_left
	delay_16
	delay_16
	walk_right
	delay_16
	delay_16
	delay_8
	walk_up
	walk_right
	walk_up
	walk_up
	walk_left
	walk_left
	step_end

RustboroCity_PokemonSchool_EventScript_Scott::
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE, RustboroCity_PokemonSchool_EventScript_ScottWatchStudents
	goto_if_set FLAG_MET_SCOTT_RUSTBORO, RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_RUSTBORO
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready::
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge::
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge::
	msgbox RustboroCity_PokemonSchool_Text_ScottStoneBadge, MSGBOX_DEFAULT
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
	end

RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge::
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE
	release
	end

RustboroCity_PokemonSchool_EventScript_ScottWatchStudents::
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
	release
	end

RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges:
	.string "El pizarrón muestra los cambios\n"
	.string "de estado en batalla.$"

RustboroCity_PokemonSchool_Text_ReadWhichTopic:
	.string "¿Qué tema quieres leer?$"

RustboroCity_PokemonSchool_Text_ExplainPoison:
	.string "Si un POKéMON se envenena, sus\n"
	.string "PS bajarán gradualmente.\p"
	.string "El efecto del veneno sigue tras\n"
	.string "la batalla.\p"
	.string "Los PS de un POKéMON envenenado\n"
	.string "bajarán mientras camines.\p"
	.string "Cura el veneno con un ANTÍDOTO.$"

RustboroCity_PokemonSchool_Text_ExplainParalysis:
	.string "Si un POKéMON se paraliza,\n"
	.string "su VELOCIDAD bajará.\p"
	.string "También puede que no se mueva\n"
	.string "durante la batalla.\p"
	.string "La parálisis sigue tras la batalla.\n"
	.string "Cúrala con una CURA PARÁLISIS.$"

RustboroCity_PokemonSchool_Text_ExplainSleep:
	.string "Si un POKéMON se duerme, no podrá\n"
	.string "lanzar ataques.\p"
	.string "Puede despertar por su cuenta,\n"
	.string "pero si la batalla termina y sigue\l"
	.string "dormido, seguirá así.\p"
	.string "Despiértalo con un DESPERTAR.$"

RustboroCity_PokemonSchool_Text_ExplainBurn:
	.string "La quemadura baja el ATAQUE y\n"
	.string "reduce los PS poco a poco.\p"
	.string "La quemadura sigue tras la batalla.\n"
	.string "Cúrala usando una CURAQUEMADURAS.$"

RustboroCity_PokemonSchool_Text_ExplainFreeze:
	.string "Si un POKéMON se congela, queda\n"
	.string "completamente indefenso.\p"
	.string "Seguirá congelado tras la batalla.\n"
	.string "Descongélalo con una CURA HIELO.$"

RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw:
	.string "Los alumnos que no estudian prueban\n"
	.string "mi GARRA RÁPIDA.\p"
	.string "Si eres un buen alumno o no, se\n"
	.string "notará por cómo uses\l"
	.string "este objeto.$"

RustboroCity_PokemonSchool_Text_ExplainQuickClaw:
	.string "Un POKéMON con la GARRA RÁPIDA\n"
	.string "a veces aceleran y logran moverse\l"
	.string "antes que su oponente.\p"
	.string "Hay muchos otros objetos que\n"
	.string "están hechos para que los lleven\p"
	.string "los POKéMON. ¡Solo eso te dará\n"
	.string "muchos temas que estudiar!$"

RustboroCity_PokemonSchool_Text_TradingRightNow:
	.string "Intercambio POKéMON con mi amigo.\n"
	.string "en este momento.$"

RustboroCity_PokemonSchool_Text_AlwaysWantedSeedot:
	.string "¡Siempre quise un SEEDOT y por\n"
	.string "fin voy a tener uno!$"

RustboroCity_PokemonSchool_Text_PokemontCantUseManMadeItems:
	.string "Los POKéMON pueden llevar objetos,\n"
	.string "pero no saben qué hacer con cosas\l"
	.string "como POCIÓN o ANTÍDOTO.$"

RustboroCity_PokemonSchool_Text_ConfusedPokemonAttacksItself:
	.string "Sabes que algunos movimientos de\n"
	.string "POKéMON pueden confundirlos?\p"
	.string "Un POKéMON confundido a veces se\n"
	.string "atacará a sí mismo sin querer.\p"
	.string "Pero al salir de la batalla,\n"
	.string "volverá a la normalidad.$"

RustboroCity_PokemonSchool_Text_PokemonHealItselfWithBerry:
	.string "Un POKéMON con una BAYA se\n"
	.string "curará solo...\p"
	.string "Hay muchos tipos de objetos que\n"
	.string "los POKéMON pueden llevar...\p"
	.string "Vaya, es muy difícil tomar\n"
	.string "notas...$"

RustboroCity_PokemonSchool_Text_StudentsNotes:
	.string "Es el cuaderno de un estudiante…\p"
	.string "Los POKéMON se capturan usando\n"
	.string "POKé BALLS.\p"
	.string "Hasta seis POKéMON pueden acompañar\n"
	.string "a un ENTRENADOR.\p"
	.string "Un ENTRENADOR es quien captura\n"
	.string "POKéMON, los cría y batalla\l"
	.string "con ellos.\p"
	.string "La misión es derrotar a los\n"
	.string "fuertes ENTRENADORES que esperan\l"
	.string "en los GIMNASIOS POKéMON.$"

RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut:
	.string "¿Hola? ¿No nos conocíamos?\n"
	.string "Pienso en CIUDAD PETALBURG.\p"
	.string "Permíteme presentarme.\n"
	.string "Mi nombre es SCOTT.\p"
	.string "He viajado por todas partes en\n"
	.string "busca de grandes ENTRENADORES.\p"
	.string "Más específicamente, busco a\n"
	.string "expertos en batallas POKéMON.\p"
	.string "¿Qué te trae a esta ESCUELA?\n"
	.string "¿Tú también eres ENTRENADOR?\p"
	.string "Lo primero que debes hacer es que\n"
	.string "que un POKéMON aprenda CORTE.\p"
	.string "Si mal no recuerdo, alguien en\n"
	.string "este pueblo tiene CORTE.$"

RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown:
	.string "SCOTT: Hmm...\p"
	.string "El nivel de talento de los alumnos\n"
	.string "es desconocido. Hay potencial.$"

RustboroCity_PokemonSchool_Text_ScottStoneBadge:
	.string "SCOTT: Oh, ¿qué es eso?\p"
	.string "Es una INSIGNIA ROCA, ¿verdad?\n"
	.string "Eso es muy impresionante, diría yo.\p"
	.string "Pero, sabes, me hubiera encantado\n"
	.string "verte en batalla.\p"
	.string "Es difícil saber cómo eres de\n"
	.string "ENTRENADOR solo por una INSIGNIA.$"

RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge:
	.string "¿Hola? ¿No nos conocíamos?\n"
	.string "Pienso en CIUDAD PETALBURG.\p"
	.string "Permíteme presentarme.\n"
	.string "Mi nombre es SCOTT.\p"
	.string "He viajado por todas partes en\n"
	.string "busca de grandes ENTRENADORES.\p"
	.string "Más específicamente, busco a\n"
	.string "expertos en batallas POKéMON.\p"
	.string "Oh, ¿qué es eso?\n"
	.string "Es una INSIGNIA ROCA, ¿verdad?\p"
	.string "Diría que es impresionante para\n"
	.string "un ENTRENADOR novato como tú.\p"
	.string "Pero, sabes, me hubiera encantado\n"
	.string "verte en batalla.\p"
	.string "Es difícil saber cómo eres de\n"
	.string "ENTRENADOR solo por una INSIGNIA.$"

