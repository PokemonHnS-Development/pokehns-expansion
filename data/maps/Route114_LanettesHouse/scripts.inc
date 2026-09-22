Route114_LanettesHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_LanettesHouse_OnTransition
	.byte 0

Route114_LanettesHouse_OnTransition:
	setflag FLAG_LANDMARK_LANETTES_HOUSE
	end

Route114_LanettesHouse_EventScript_Lanette::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_DOLL_LANETTE, Route114_LanettesHouse_EventScript_OfferAdvice
	setflag FLAG_SYS_PC_LANETTE
	msgbox Route114_LanettesHouse_Text_EverythingClutteredKeepThis, MSGBOX_DEFAULT
	givedecoration DECOR_LOTAD_DOLL
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowNoRoomForDecor
	setflag FLAG_RECEIVED_DOLL_LANETTE
	release
	end

Route114_LanettesHouse_EventScript_OfferAdvice::
	msgbox Route114_LanettesHouse_Text_OrganizeYourBoxes, MSGBOX_DEFAULT
	release
	end

Route114_LanettesHouse_EventScript_Notebook::
	lockall
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage2
	msgbox Route114_LanettesHouse_Text_ClosedTheNotebook, MSGBOX_DEFAULT
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage2::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage2, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, Route114_LanettesHouse_EventScript_NotebookPage3
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage3::
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage3, MSGBOX_DEFAULT
	return

Route114_LanettesHouse_EventScript_PC::
	msgbox Route114_LanettesHouse_Text_EmailFromBill, MSGBOX_SIGN
	end

Route114_LanettesHouse_Text_EverythingClutteredKeepThis:
	.string "LANETTE: ¡Oh! ¡{PLAYER}{KUN}!\p"
	.string "Siento que todo esté tan desordenado…\n"
	.string "Cuando me concentro en investigar,\l"
	.string "las cosas terminan así...\p"
	.string "Qué vergüenza... Por favor, guarda\n"
	.string "el secreto a cambio de esto.$"

Route114_LanettesHouse_Text_OrganizeYourBoxes:
	.string "¿Te doy un consejo sobre mi sistema\n"
	.string "de almacenamiento de POKéMON?\p"
	.string "Organiza tus BOXES para saber qué\n"
	.string "POKéMON hay en cada una.$"

Route114_LanettesHouse_Text_ResearchNotesPage1:
	.string "Son las notas de LANETTE.\n"
	.string "Hay información sobre las BOXES.\p"
	.string "Crea BOXES para 30 POKéMON cada una.\p"
	.string "Cada ENTRENADOR debe poder guardar\n"
	.string "420 POKéMON en el sistema PC.\p"
	.string "¿Seguir leyendo?$"

Route114_LanettesHouse_Text_ResearchNotesPage2:
	.string "Añade un sistema de marcas para\n"
	.string "organizar mejor a los POKéMON.\p"
	.string "El nombre y fondo de cada BOX\n"
	.string "serán cambiables para agradar a\l"
	.string "los POKéMON guardados.\p"
	.string "¿Seguir leyendo?$"

Route114_LanettesHouse_Text_ResearchNotesPage3:
	.string "Al guardar un POKéMON, debe ir a\n"
	.string "la última BOX revisada.\p"
	.string "Si esa BOX está llena, el POKéMON\n"
	.string "se guardará en la siguiente BOX.\p"
	.string "En otras palabras, al examinar una\n"
	.string "BOX, esta se selecciona como la BOX\l"
	.string "a la que se envían los POKéMON.$"

Route114_LanettesHouse_Text_ClosedTheNotebook:
	.string "{PLAYER} cerró el cuaderno.$"

Route114_LanettesHouse_Text_EmailFromBill:
	.string "Hay un correo de alguien en la\n"
	.string "PC.\p"
	.string "“… … … … … … …\p"
	.string "“Tu Sistema de Almacenamiento es más\n"
	.string "conveniente que el mío.\p"
	.string "“Tiene funciones muy fáciles de usar\n"
	.string "que lo hacen divertido y útil.\p"
	.string "“Me enorgullece haber formado\n"
	.string "de su desarrollo.”\p"
	.string "“Espero que continúes con tu\n"
	.string "estudio de los Sistemas de Almacén.\p"
	.string "“De BILL\n"
	.string "… … … … … … … …”$"

