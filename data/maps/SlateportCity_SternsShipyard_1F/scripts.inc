SlateportCity_SternsShipyard_1F_MapScripts::
	.byte 0

SlateportCity_SternsShipyard_1F_EventScript_Dock::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_SternsShipyard_1F_EventScript_FerryReady
	goto_if_set FLAG_BADGE07_GET, SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined
	goto_if_set FLAG_DELIVERED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_GoFindStern
	msgbox SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails, MSGBOX_DEFAULT
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_DOCK_REJECTED_DEVON_GOODS
	setflag FLAG_HIDE_SLATEPORT_CITY_TEAM_AQUA
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_FerryReady::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_FerryIsReady, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_GoFindStern::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist1::
	msgbox SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist2::
	msgbox SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Briney::
	msgbox SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails:
	.string "Umm... Si esto va aquí, y aquello\n"
	.string "va por allá...\p"
	.string "Entonces, ¿dónde va esta cosa?\n"
	.string "¿Y qué pasa con ese aparatito?\p"
	.string "¡Aaargh! ¡No entiendo nada\n"
	.string "de esto!$"

SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern:
	.string "Hm?\n"
	.string "Hola, soy DOCK.\p"
	.string "El CAPT. STERN me encargó\n"
	.string "diseñar un ferry.\p"
	.string "¡Oh! Eso de ahí...\n"
	.string "¿Son PRODUCTOS DEVON?\p"
	.string "Pero, hmm...\n"
	.string "Esto no servirá...\p"
	.string "El CAPT. STERN se fue a algún lado.\n"
	.string "Dijo que tenía trabajo que hacer.\p"
	.string "¿Podrías ir a buscar al CAPT.\n"
	.string "STERN y entregarle esto?$"

SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern:
	.string "MUELLE: ¿A dónde habrá ido el\n"
	.string "CAPT. STERN?\p"
	.string "¿Podrías buscar al CAPT. STERN y\n"
	.string "entregarle ese paquete?$"

SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran:
	.string "MUELLE: Construir barcos es un arte.\p"
	.string "Hay cosas que no se resuelven\n"
	.string "solo con cálculos.\p"
	.string "Me vendría bien el consejo de un\n"
	.string "veterano que conozca los mares…$"

SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs:
	.string "DOCK: ¡Hola! El SR. BRINEY se ha\n"
	.string "unido para ayudarnos.\p"
	.string "Gracias al veterano marinero, el\n"
	.string "ferry se está terminando.$"

SlateportCity_SternsShipyard_1F_Text_FerryIsReady:
	.string "DOCK: ¡El ferry ya está listo!\p"
	.string "¡El nuevo S.S. TIDAL es una verdadera\n"
	.string "maravilla tecnológica!\p"
	.string "Pero siento que podemos crear\n"
	.string "algo todavía mejor.\p"
	.string "Ya sabes, nunca se deja de\n"
	.string "el avance tecnológico.$"

SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock:
	.string "SR. BRINEY: ¡Ah, {PLAYER}{KUN}!\n"
	.string "¡Ha pasado mucho tiempo!\p"
	.string "¡Sí, desde que te vi, este viejo\n"
	.string "lobo de mar se siente activo!\p"
	.string "Así que decidí ayudar a DOCK a\n"
	.string "hacer un ferry.\p"
	.string "Sí, después de todo, un ferry\n"
	.string "podría llevar a mucha gente.\p"
	.string "Pero, ya sabes, ese DOCK es\n"
	.string "realmente especial.\p"
	.string "Con su talento para la tecnología y\n"
	.string "por mi experiencia, estoy seguro\l"
	.string "de que haremos un gran barco!$"

SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing:
	.string "Las estaciones, el clima, donde\n"
	.string "está la luna en el cielo...\p"
	.string "Estas y otras condiciones hacen\n"
	.string "que el mar cambie su expresión.\p"
	.string "¡Así es!\n"
	.string "¡El mar es como un ser vivo!$"

SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily:
	.string "Me mareo muy fácilmente.\n"
	.string "Así que ayudo por aquí en su lugar.$"

