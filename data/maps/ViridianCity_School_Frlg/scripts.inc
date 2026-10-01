ViridianCity_School_Frlg_MapScripts::
	.byte 0

ViridianCity_School_EventScript_Lass::
	lock
	faceplayer
	msgbox ViridianCity_School_Text_TryingToMemorizeNotes
	closemessage
	applymovement LOCALID_SCHOOL_LASS, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

ViridianCity_School_EventScript_Woman::
	lock
	faceplayer
	msgbox ViridianCity_School_Text_ReadBlackboardCarefully
	closemessage
	applymovement LOCALID_SCHOOL_WOMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

ViridianCity_School_EventScript_Notebook::
	lockall
	msgbox ViridianCity_School_Text_NotebookFirstPage
	msgbox ViridianCity_School_Text_TurnThePage, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ViridianCity_School_EventScript_StopReadingNotebook
	msgbox ViridianCity_School_Text_NotebookSecondPage
	msgbox ViridianCity_School_Text_TurnThePage, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ViridianCity_School_EventScript_StopReadingNotebook
	msgbox ViridianCity_School_Text_NotebookThirdPage
	msgbox ViridianCity_School_Text_TurnThePage, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ViridianCity_School_EventScript_StopReadingNotebook
	msgbox ViridianCity_School_Text_NotebookFourthPage
	applymovement LOCALID_SCHOOL_LASS, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox ViridianCity_School_Text_HeyDontLookAtMyNotes
	releaseall
	end

ViridianCity_School_EventScript_StopReadingNotebook::
	releaseall
	end

ViridianCity_School_EventScript_Blackboard::
	lockall
	msgbox ViridianCity_School_Text_BlackboardListsStatusProblems
	goto ViridianCity_School_EventScript_ChooseBlackboardTopic
	end

ViridianCity_School_EventScript_ChooseBlackboardTopic::
	message ViridianCity_School_Text_ReadWhichTopic
	waitmessage
	multichoicegrid 7, 1, MULTI_STATUS_INFO, 3, FALSE
	switch VAR_RESULT
	case 0, ViridianCity_School_EventScript_ReadSleep
	case 1, ViridianCity_School_EventScript_ReadPoison
	case 2, ViridianCity_School_EventScript_ReadParalysis
	case 3, ViridianCity_School_EventScript_ReadBurn
	case 4, ViridianCity_School_EventScript_ReadFreeze
	case 5, ViridianCity_School_EventScript_ExitBlackboard
	case 127, ViridianCity_School_EventScript_ExitBlackboard
	end

ViridianCity_School_EventScript_ReadSleep::
	msgbox ViridianCity_School_Text_ExplainSleep
	goto ViridianCity_School_EventScript_ChooseBlackboardTopic
	end

ViridianCity_School_EventScript_ReadBurn::
	msgbox ViridianCity_School_Text_ExplainBurn
	goto ViridianCity_School_EventScript_ChooseBlackboardTopic
	end

ViridianCity_School_EventScript_ReadPoison::
	msgbox ViridianCity_School_Text_ExplainPoison
	goto ViridianCity_School_EventScript_ChooseBlackboardTopic
	end

ViridianCity_School_EventScript_ReadFreeze::
	msgbox ViridianCity_School_Text_ExplainFreeze
	goto ViridianCity_School_EventScript_ChooseBlackboardTopic
	end

ViridianCity_School_EventScript_ReadParalysis::
	msgbox ViridianCity_School_Text_ExplainParalysis
	goto ViridianCity_School_EventScript_ChooseBlackboardTopic
	end

ViridianCity_School_EventScript_ExitBlackboard::
	releaseall
	end

ViridianCity_School_Text_TryingToMemorizeNotes::
	.string "¡Uf! Intento memorizar todo\n"
	.string "mis apuntes.$"

ViridianCity_School_Text_ReadBlackboardCarefully::
	.string "¡Está bien!\p"
	.string "Asegúrate de leer lo que hay\n"
	.string "¡en la pizarra con cuidado!$"

ViridianCity_School_Text_NotebookFirstPage::
	.string "Veamos el cuaderno.\p"
	.string "Primera página...\p"
	.string "Las POKé BALL sirven para atrapar\n"
	.string "POKéMON.\p"
	.string "Puedes llevar hasta seis POKéMON\n"
	.string "en tu equipo.\p"
	.string "Personas que crían y combaten\n"
	.string "con POKéMON se llaman ENTRENADORES.$"

ViridianCity_School_Text_NotebookSecondPage::
	.string "Segunda página...\p"
	.string "Un POKéMON sano puede ser difícil\n"
	.string "de atrapar, así que debilítalo.\p"
	.string "Envenénalo, quémalo o causa otro\n"
	.string "estado para debilitarlo.$"

ViridianCity_School_Text_NotebookThirdPage::
	.string "Tercera página...\p"
	.string "Los ENTRENADORES POKéMON buscan\n"
	.string "rivales con quienes combatir.\p"
	.string "Para los ENTRENADORES, el sabor\nde la victoria"
	.string "es dulce, en verdad.\p"
	.string "Se libran batallas constantes\n"
	.string "en los GIMNASIOS POKéMON.$"

ViridianCity_School_Text_NotebookFourthPage::
	.string "Cuarta página...\p"
	.string "La meta final de todos los\n"
	.string "ENTRENADORES es simple.\p"
	.string "Es vencer a los ocho mejores\n"
	.string "LÍDERES DE GIMNASIO POKéMON.\p"
	.string "Hazlo para ganar el derecho a...\p"
	.string "¡Al ALTO MANDO de la LIGA\n"
	.string "POKéMON!$"

ViridianCity_School_Text_TurnThePage::
	.string "¿Pasar la página?$"

ViridianCity_School_Text_HeyDontLookAtMyNotes::
	.string "CHICA: ¡Oye!\n"
	.string "¡No mires mis notas!$"

ViridianCity_School_Text_BlackboardListsStatusProblems::
	.string "La pizarra lista los problemas de\n"
	.string "ESTADO de los POKéMON en combate.$"

ViridianCity_School_Text_ReadWhichTopic::
	.string "¿Qué tema quieres leer?$"

ViridianCity_School_Text_ExplainSleep::
	.string "Un POKéMON no puede atacar si\n"
	.string "está dormido.\p"
	.string "Un POKéMON sigue dormido incluso\n"
	.string "después de los combates.\p"
	.string "Usa DESPERTAR para despertar\n"
	.string "del sueño.$"

ViridianCity_School_Text_ExplainBurn::
	.string "Una quemadura reduce el ATAQUE.\n"
	.string "También causa pérdida de PS\p"
	.string "La quemadura sigue tras el combate.\n"
	.string "¡Usa CURA QUEMADURA para curarla!$"

ViridianCity_School_Text_ExplainPoison::
	.string "Envenenado, la salud de un POKéMON\n"
	.string "baja poco a poco.\p"
	.string "El veneno sigue tras los combates.\n"
	.string "¡Usa un ANTÍDOTO para curarlo!$"

ViridianCity_School_Text_ExplainFreeze::
	.string "Un POKéMON congelado queda\n"
	.string "totalmente inmóvil.\p"
	.string "Sigue congelado incluso cuando\n"
	.string "termina el combate.\p"
	.string "Usa CURA HIELO para descongelar\n"
	.string "al POKéMON que sufre.$"

ViridianCity_School_Text_ExplainParalysis::
	.string "La parálisis reduce VELOCIDAD y\n"
	.string "impide que el POKéMON se mueva.\p"
	.string "La parálisis sigue tras los combates.\n"
	.string "Usa CURA PARALISIS para tratar.$"

