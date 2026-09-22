MossdeepCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_OnTransition
	.byte 0

MossdeepCity_OnTransition:
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_1
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_2
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_3
	clearflag FLAG_MOSSDEEP_GYM_SWITCH_4
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	end

MossdeepCity_EventScript_PokefanF::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_PokefanFMagmaGone
	msgbox MossdeepCity_Text_SpaceCenterReceivedLetter, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_PokefanFMagmaGone::
	msgbox MossdeepCity_Text_SpaceCenterLaunchingRockets, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_Sailor::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_DIVE, MossdeepCity_EventScript_SailorMagmaGone
	msgbox MossdeepCity_Text_MossdeepTargetedByMagma, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_SailorMagmaGone::
	msgbox MossdeepCity_Text_FeelReliefOnLand, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_NinjaBoy::
	msgbox MossdeepCity_Text_WailmerWatching, MSGBOX_NPC
	end

MossdeepCity_EventScript_ExpertM::
	msgbox MossdeepCity_Text_LifeNeedsSeaToLive, MSGBOX_NPC
	end

MossdeepCity_EventScript_Girl::
	msgbox MossdeepCity_Text_NiceIfWorldCoveredByFlowers, MSGBOX_NPC
	end

MossdeepCity_EventScript_Woman::
	msgbox MossdeepCity_Text_SpecialSpaceCenterRock, MSGBOX_NPC
	end

MossdeepCity_EventScript_WhiteRock::
	msgbox MossdeepCity_Text_ItsAWhiteRock, MSGBOX_SIGN
	end

MossdeepCity_EventScript_GymSign::
	msgbox MossdeepCity_Text_GymSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_CitySign::
	msgbox MossdeepCity_Text_CitySign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_SpaceCenterSign::
	msgbox MossdeepCity_Text_SpaceCenterSign, MSGBOX_SIGN
	end

MossdeepCity_EventScript_VisitedMossdeep::
	setflag FLAG_VISITED_MOSSDEEP_CITY
	setvar VAR_TEMP_1, 1
	end

MossdeepCity_EventScript_TeamMagmaEnterSpaceCenter::
	lockall
	applymovement LOCALID_MOSSDEEP_MAXIE, MossdeepCity_Movement_MaxieGestureToSpaceCenter
	waitmovement 0
	applymovement LOCALID_MOSSDEEP_GRUNT_1, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_2, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_3, MossdeepCity_Movement_GruntFaceSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_4, MossdeepCity_Movement_GruntFaceSpaceCenter
	waitmovement 0
	applymovement LOCALID_MOSSDEEP_MAXIE, MossdeepCity_Movement_MaxieEnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_1, MossdeepCity_Movement_Grunt1EnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_2, MossdeepCity_Movement_Grunt2EnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_3, MossdeepCity_Movement_Grunt3EnterSpaceCenter
	applymovement LOCALID_MOSSDEEP_GRUNT_4, MossdeepCity_Movement_Grunt4EnterSpaceCenter
	waitmovement 0
	removeobject LOCALID_MOSSDEEP_MAXIE
	removeobject LOCALID_MOSSDEEP_GRUNT_1
	removeobject LOCALID_MOSSDEEP_GRUNT_2
	removeobject LOCALID_MOSSDEEP_GRUNT_3
	removeobject LOCALID_MOSSDEEP_GRUNT_4
	delay 30
	setvar VAR_MOSSDEEP_CITY_STATE, 2
	setflag FLAG_HIDE_MOSSDEEP_CITY_TEAM_MAGMA
	releaseall
	end

MossdeepCity_Movement_MaxieGestureToSpaceCenter:
	delay_16
	face_right
	delay_16
	delay_16
	delay_16
	delay_16
	face_left
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_GruntFaceSpaceCenter:
	face_right
	delay_16
	delay_16
	delay_16
	step_end

MossdeepCity_Movement_MaxieEnterSpaceCenter:
	walk_down
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt1EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt2EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt3EnterSpaceCenter:
	delay_16
	delay_8
	walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_Movement_Grunt4EnterSpaceCenter:
	delay_16
	delay_8
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MossdeepCity_EventScript_Man::
	lock
	faceplayer
	msgbox MossdeepCity_Text_SurfExhilarating, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

MossdeepCity_EventScript_KingsRockBoy::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_KINGS_ROCK, MossdeepCity_EventScript_ReceivedKingsRock
	msgbox MossdeepCity_Text_WantKingsRockStevenGaveMe, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MossdeepCity_EventScript_DeclineKingsRock
	msgbox MossdeepCity_Text_YouCanKeepIt, MSGBOX_DEFAULT
	giveitem ITEM_KINGS_ROCK
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_KINGS_ROCK
	release
	end

MossdeepCity_EventScript_ReceivedKingsRock::
	msgbox MossdeepCity_Text_StevensHouseOverThere, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_DeclineKingsRock::
	msgbox MossdeepCity_Text_WhatToDoWithWeirdRock, MSGBOX_DEFAULT
	release
	end

MossdeepCity_EventScript_BlackBelt::
	msgbox MossdeepCity_Text_SootopolisNewGymLeader, MSGBOX_NPC
	end

MossdeepCity_EventScript_Scott::
	lock
	faceplayer
	msgbox MossdeepCity_Text_ScottSomethingWrongWithTown, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, MossdeepCity_EventScript_ScottExitNorth
	call_if_eq VAR_FACING, DIR_EAST, MossdeepCity_EventScript_ScottExitEast
	addvar VAR_SCOTT_STATE, 1
	removeobject LOCALID_MOSSDEEP_SCOTT
	release
	end

MossdeepCity_EventScript_ScottExitNorth::
	applymovement LOCALID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_MOSSDEEP_SCOTT, MossdeepCity_Movement_ScottExitNorth
	waitmovement 0
	return

MossdeepCity_EventScript_ScottExitEast::
	applymovement LOCALID_PLAYER, MossdeepCity_Movement_PlayerWatchScottExit
	applymovement LOCALID_MOSSDEEP_SCOTT, MossdeepCity_Movement_ScottExitEast
	waitmovement 0
	return

MossdeepCity_Movement_PlayerWatchScottExit:
	delay_16
	delay_16
	walk_in_place_faster_left
	step_end

MossdeepCity_Movement_ScottExitNorth:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Movement_ScottExitEast:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

MossdeepCity_Text_WantKingsRockStevenGaveMe:
	.string "STEVEN me dio esto, pero no sé\n"
	.string "para qué sirve.\p"
	.string "Creo que se llama ROCA DEL REY.\n"
	.string "¿La quieres?$"

MossdeepCity_Text_YouCanKeepIt:
	.string "¿Por qué la querrías?\n"
	.string "Eres raro.\p"
	.string "Quédatela, pero que sea un secreto\n"
	.string "para STEVEN.$"

MossdeepCity_Text_StevensHouseOverThere:
	.string "¡La casa de STEVEN está justo ahí!$"

MossdeepCity_Text_WhatToDoWithWeirdRock:
	.string "¡Sí, tú también lo crees! ¿Qué se\n"
	.string "hace con una roca rara?$"

MossdeepCity_Text_WailmerWatching:
	.string "Cerca de FONDO MARIN, verás wild\n"
	.string "WAILMER.\p"
	.string "Se llama, eh...\n"
	.string "Cómo era...\p"
	.string "WAI, WAI, WAI...\p"
	.string "¡WAILMER observa!$"

MossdeepCity_Text_SpaceCenterReceivedLetter:
	.string "El CENTRO ESPACIAL de la isla ha\n"
	.string "lanzado cohetes enormes.\p"
	.string "Ha habido un gran alboroto por\n"
	.string "una carta que recibieron hace poco.$"

MossdeepCity_Text_SpaceCenterLaunchingRockets:
	.string "El CENTRO ESPACIAL de la isla ha\n"
	.string "lanzando cohetes enormes.$"

MossdeepCity_Text_MossdeepTargetedByMagma:
	.string "Un amigo MARINERO me contó que\n"
	.string "el EQUIPO AQUA llegó a LILYCOVE.\p"
	.string "También oí que alguien llegó\n"
	.string "¡y los dejó en ridículo!\p"
	.string "Pero MOSSDEEP ha sido el blanco\n"
	.string "del TEAM MAGMA.\p"
	.string "Si quieres saber qué planean,\n"
	.string "ve al CENTRO ESPACIAL.$"

MossdeepCity_Text_FeelReliefOnLand:
	.string "Soy MARINERO, así que el mar es\n"
	.string "obviamente más importante para mí.\p"
	.string "Pero ¿sabes? Al volver a tierra\n"
	.string "tras un viaje, ¡siento alivio!$"

MossdeepCity_Text_NiceIfWorldCoveredByFlowers:
	.string "¿No sería genial?\p"
	.string "Si todo el mundo estuviera cubierto\n"
	.string "¿plantas y flores como esta isla?$"

MossdeepCity_Text_LifeNeedsSeaToLive:
	.string "Toda vida necesita el mar para vivir,\n"
	.string "aunque haga su hogar en la tierra.\p"
	.string "La vida, al terminar su curso, se\n"
	.string "vuelve suelo y vuelve a la tierra.\p"
	.string "Y el mar siempre está conectado a\n"
	.string "la tierra.\p"
	.string "Sí, como la misma costa de aquí.$"

MossdeepCity_Text_SurfExhilarating:
	.string "Viajar en barco está bien.\p"
	.string "Pero cruzar el mar con POKéMON\n"
	.string "usando SURF...\p"
	.string "¡Eso sí que es un viaje emocionante!\n"
	.string "¿No estás de acuerdo, joven?$"

MossdeepCity_Text_SpecialSpaceCenterRock:
	.string "Esta roca tiene un significado\n"
	.string "la gente del CENTRO ESPACIAL.\p"
	.string "La pusieron aquí como un deseo\n"
	.string "para que sus cohetes vuelen seguros.\p"
	.string "¿Qué usas tú para pedir un deseo?\n"
	.string "¿Le pides un deseo a una estrella?\p"
	.string "Yo uso una etiqueta de deseos\n"
	.string "para que se cumpla.$"

MossdeepCity_Text_ItsAWhiteRock:
	.string "Es una roca blanca.$"

MossdeepCity_Text_GymSign:
	.string "GIMNASIO POKéMON CIUDAD FONDO MAR\n"
	.string "LÍDERES: LIZA Y TATE\p"
	.string "¡La combinación mística!$"

MossdeepCity_Text_CitySign:
	.string "CIUDAD FONDO MARINO\n"
	.string "“Lema: ¡Amen a los POKéMON!”$"

MossdeepCity_Text_SpaceCenterSign:
	.string "CENTRO ESPACIAL FONDO MARINO\n"
	.string "“El lugar más cercano al espacio.”$"

MossdeepCity_Text_ScottSomethingWrongWithTown:
	.string "SCOTT: {PLAYER}{KUN}, ¿todo bien?\n"
	.string "¡Me va genial!\p"
	.string "Oí que el LÍDER del GIMNASIO de\n"
	.string "FONDO MARINO es muy fuerte, así que\l"
	.string "vine a verlo por mí mismo.\p"
	.string "Pero algo no me cuadra\n"
	.string "de este pueblo.\p"
	.string "La gente habla de una advertencia\n"
	.string "carta y el CENTRO ESPACIAL…\p"
	.string "No creo que tenga algo que ver\n"
	.string "conmigo, en realidad.$"

MossdeepCity_Text_SootopolisNewGymLeader:
	.string "Ahh… Se siente genial dejar que las\n"
	.string "olas bañen mis pies…\p"
	.string "Hablando de olas, ¿conoces esa\n"
	.string "ciudad isla, CALORÍS?\p"
	.string "Creo que el GIMNASIO de allá tiene\n"
	.string "un nuevo LÍDER.\p"
	.string "Dicen que ese nuevo LÍDER alguna vez\n"
	.string "fue mentor de WALLACE.$"

