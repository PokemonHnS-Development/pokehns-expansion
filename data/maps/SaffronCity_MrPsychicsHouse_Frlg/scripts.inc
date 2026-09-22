SaffronCity_MrPsychicsHouse_Frlg_MapScripts::
	.byte 0

SaffronCity_MrPsychicsHouse_EventScript_MrPsychic::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM29_FROM_MR_PSYCHIC, SaffronCity_MrPsychicsHouse_EventScript_AlreadyGotTM29
	msgbox SaffronCity_MrPsychicsHouse_Text_YouWantedThis
	checkitemspace ITEM_TM29
	goto_if_eq VAR_RESULT, FALSE, SaffronCity_MrPsychicsHouse_EventScript_NoRoomForTM29
	giveitem_msg SaffronCity_MrPsychicsHouse_Text_ReceivedTM29FromMrPsychic, ITEM_TM29
	msgbox SaffronCity_MrPsychicsHouse_Text_ExplainTM29
	setflag FLAG_GOT_TM29_FROM_MR_PSYCHIC
	release
	end

SaffronCity_MrPsychicsHouse_EventScript_NoRoomForTM29::
	msgbox SaffronCity_MrPsychicsHouse_Text_YouveNoRoom
	release
	end

SaffronCity_MrPsychicsHouse_EventScript_AlreadyGotTM29::
	msgbox SaffronCity_MrPsychicsHouse_Text_ExplainTM29
	release
	end

SaffronCity_MrPsychicsHouse_Text_YouWantedThis::
	.string "¡Espera! ¡No digas nada!\p"
	.string "¡Querías esto!$"

SaffronCity_MrPsychicsHouse_Text_ReceivedTM29FromMrPsychic::
	.string "{PLAYER} received TM29\n"
	.string "del SR. PSÍQUICO.$"

SaffronCity_MrPsychicsHouse_Text_ExplainTM29::
	.string "Ya lo sabes, ¿verdad?\n"
	.string "La MT29 es PSÍQUICO.\p"
	.string "Es un ataque que también puede\n"
	.string "the target's special stats.$"

SaffronCity_MrPsychicsHouse_Text_YouveNoRoom::
	.string "¿Dónde piensas poner esto?\n"
	.string "No tienes espacio.$"

