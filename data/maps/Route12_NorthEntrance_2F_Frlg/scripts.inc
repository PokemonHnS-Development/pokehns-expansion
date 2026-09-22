Route12_NorthEntrance_2F_Frlg_MapScripts::
	.byte 0

Route12_NorthEntrance_2F_EventScript_LeftBinoculars::
	msgbox Route12_NorthEntrance_2F_Text_TheresManFishing, MSGBOX_SIGN
	end

Route12_NorthEntrance_2F_EventScript_RightBinoculars::
	msgbox Route12_NorthEntrance_2F_Text_ItsPokemonTower, MSGBOX_SIGN
	end

Route12_NorthEntrance_2F_EventScript_Lass::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM27, Route12_NorthEntrance_2F_EventScript_ExplainTM27
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Route12_NorthEntrance_2F_EventScript_TakeTMMale
	call_if_eq VAR_RESULT, FEMALE, Route12_NorthEntrance_2F_EventScript_TakeTMFemale
	checkitemspace ITEM_TM27
	goto_if_eq VAR_RESULT, FALSE, Route12_NorthEntrance_2F_EventScript_NoRoomForTM27
	giveitem_msg Route12_NorthEntrance_2F_Text_ReceivedTM27FromLittleGirl, ITEM_TM27
	msgbox Route12_NorthEntrance_2F_Text_ExplainTM27
	setflag FLAG_GOT_TM27
	release
	end

Route12_NorthEntrance_2F_EventScript_TakeTMMale::
	msgbox Route12_NorthEntrance_2F_Text_TakeTMDontNeedAnymoreMale
	return

Route12_NorthEntrance_2F_EventScript_TakeTMFemale::
	msgbox Route12_NorthEntrance_2F_Text_TakeTMDontNeedAnymoreFemale
	return

Route12_NorthEntrance_2F_EventScript_NoRoomForTM27::
	msgbox Route12_NorthEntrance_2F_Text_DontHaveRoomForThis
	release
	end

Route12_NorthEntrance_2F_EventScript_ExplainTM27::
	msgbox Route12_NorthEntrance_2F_Text_ExplainTM27
	release
	end

@ Male and female text identical, differ (presumably) in JP
Route12_NorthEntrance_2F_Text_TakeTMDontNeedAnymoreMale::
	.string "My POKéMON's ashes are stored in\n"
	.string "POKéMON TOWER.\p"
	.string "Puedes quedarte esta MT.\n"
	.string "Ya no la necesito...$"

Route12_NorthEntrance_2F_Text_TakeTMDontNeedAnymoreFemale::
	.string "My POKéMON's ashes are stored in\n"
	.string "POKéMON TOWER.\p"
	.string "Puedes quedarte esta MT.\n"
	.string "Ya no la necesito...$"

Route12_NorthEntrance_2F_Text_ReceivedTM27FromLittleGirl::
	.string "{PLAYER} received TM27\n"
	.string "de la niña.$"

Route12_NorthEntrance_2F_Text_ExplainTM27::
	.string "La MT27 es el movimiento RETRO...\p"
	.string "If you treat your POKéMON good,\n"
	.string "devolverá tu cariño esforzándose\l"
	.string "al máximo en combate.$"

Route12_NorthEntrance_2F_Text_DontHaveRoomForThis::
	.string "No tienes espacio para esto.$"

Route12_NorthEntrance_2F_Text_TheresManFishing::
	.string "Veamos qué tienen los prismáticos\n"
	.string "para mostrar...\p"
	.string "¡Hay un hombre pescando!$"

Route12_NorthEntrance_2F_Text_ItsPokemonTower::
	.string "Veamos qué tienen los prismáticos\n"
	.string "para mostrar...\p"
	.string "It's POKéMON TOWER!$"

