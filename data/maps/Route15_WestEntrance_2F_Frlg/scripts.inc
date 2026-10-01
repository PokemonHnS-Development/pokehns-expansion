.equ REQUIRED_CAUGHT_MONS, 50

Route15_WestEntrance_2F_Frlg_MapScripts::
	.byte 0

Route15_WestEntrance_2F_EventScript_LeftBinoculars::
	lockall
	msgbox Route15_WestEntrance_2F_Text_LargeShiningBird
	showmonpic SPECIES_ARTICUNO, 10, 3
	delay 20
	waitbuttonpress
	hidemonpic
	setvar VAR_0x8004, SPECIES_ARTICUNO
	special SetSeenMon
	releaseall
	end

Route15_WestEntrance_2F_EventScript_RightBinoculars::
	msgbox Route15_WestEntrance_2F_Text_SmallIslandOnHorizon, MSGBOX_SIGN
	end

Route15_WestEntrance_2F_EventScript_Aide::
	lock
	faceplayer
	call Route15_WestEntrance_2F_EventScript_GetAideRequestInfo
	goto_if_set FLAG_GOT_EXP_SHARE_FROM_OAKS_AIDE, Route15_WestEntrance_2F_EventScript_AlreadyGotExpShare
	msgbox Route15_WestEntrance_2F_Text_GiveItemIfCaughtEnough, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Aide_EventScript_DeclineCheckMons
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetFrlgPokedexCount
	buffernumberstring STR_VAR_3, VAR_0x8006
	call Route15_WestEntrance_2F_EventScript_GetAideRequestInfo
	goto_if_lt VAR_0x8006, REQUIRED_CAUGHT_MONS, Aide_EventScript_HaventCaughtEnough
	msgbox Route15_WestEntrance_2F_Text_GreatHereYouGo
	checkitemspace ITEM_EXP_SHARE
	goto_if_eq VAR_RESULT, FALSE, Aide_EventScript_NoRoomForItem
	giveitem_msg Route15_WestEntrance_2F_Text_ReceivedItemFromAide, ITEM_EXP_SHARE
	setflag FLAG_GOT_EXP_SHARE_FROM_OAKS_AIDE
	msgbox Route15_WestEntrance_2F_Text_ExplainExpShare
	release
	end

Route15_WestEntrance_2F_EventScript_AlreadyGotExpShare::
	msgbox Route15_WestEntrance_2F_Text_ExplainExpShare
	release
	end

Route15_WestEntrance_2F_EventScript_GetAideRequestInfo::
	buffernumberstring STR_VAR_1, REQUIRED_CAUGHT_MONS
	bufferitemname STR_VAR_2, ITEM_EXP_SHARE
	return

Route15_WestEntrance_2F_Text_GiveItemIfCaughtEnough::
	.string "¡Hola! ¿Te acuerdas de mí?\n"
	.string "Soy AYUDANTE del PROF. OAK.\p"
	.string "Si tu POKéDEX tiene datos completos\n"
	.string "según la especie {STR_VAR_1}, se\l"
	.string "supone que te dé una recompensa.\p"
	.string "El PROF. OAK me encargó\n"
	.string "el {STR_VAR_2} para ti.\p"
	.string "Así que, {PLAYER}, déjame preguntarte.\p"
	.string "¿Ya reuniste datos de al menos\n"
	.string "¿{STR_VAR_1} tipos de POKéMON?$"

Route15_WestEntrance_2F_Text_GreatHereYouGo::
	.string "¡Genial! Has capturado o tenido\n"
	.string "{STR_VAR_3} tipos de POKéMON!\p"
	.string "¡Felicidades!\n"
	.string "¡Toma!$"

Route15_WestEntrance_2F_Text_ReceivedItemFromAide::
	.string "{PLAYER} recibió el {STR_VAR_2}\n"
	.string "del ayudante.$"

Route15_WestEntrance_2F_Text_ExplainExpShare::
	.string "El Reparto Exp. es un objeto que\n"
	.string "por un POKéMON.\p"
	.string "El POKéMON recibirá una parte\n"
	.string "se lleva y otorga Puntos de Exp.\l"
	.string "sin combatir.$"

Route15_WestEntrance_2F_Text_LargeShiningBird::
	.string "Veamos qué muestran los\n"
	.string "prismáticos...\p"
	.string "Un ave grande y brillante vuela\n"
	.string "hacia el mar.$"

Route15_WestEntrance_2F_Text_SmallIslandOnHorizon::
	.string "Veamos qué muestran los\n"
	.string "prismáticos...\p"
	.string "Parece una pequeña isla en\n"
	.string "¡el horizonte!$"

