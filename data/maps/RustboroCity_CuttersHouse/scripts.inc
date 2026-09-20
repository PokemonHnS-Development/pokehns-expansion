RustboroCity_CuttersHouse_MapScripts::
	.byte 0

RustboroCity_CuttersHouse_EventScript_Cutter::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_CUT, RustboroCity_CuttersHouse_EventScript_ExplainCut
	msgbox RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse, MSGBOX_DEFAULT
	giveitem ITEM_HM_CUT
	setflag FLAG_RECEIVED_HM_CUT
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_ExplainCut::
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
	release
	end

RustboroCity_CuttersHouse_EventScript_Lass::
	msgbox RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees, MSGBOX_NPC
	end

RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse:
	.string "Esa expresión decidida…\n"
	.string "Esa forma tan ágil de moverte…\l"
	.string "Y tus POKéMON tan entrenados…\p"
	.string "¡Eres un TRAINER muy hábil!\p"
	.string "No, espera, no digas nada.\n"
	.string "Lo noto solo con mirarte.\p"
	.string "Estoy seguro de que darás\n"
	.string "buen uso a esta MO.\p"
	.string "No hace falta ser modesto.\n"
	.string "¡Anda, tómala!$"

RustboroCity_CuttersHouse_Text_ExplainCut:
	.string "Esa MO, o HIDDEN MACHINE\n"
	.string "para abreviar, es CORTE.\p"
	.string "Un movimiento MO es aquel que puede\n"
	.string "usar un POKéMON fuera de combate.\p"
	.string "Cualquier POKéMON que sepa CORTE\n"
	.string "podrá talar árboles si el ENTRENADOR\l"
	.string "tiene la MEDALLA ROCA.\p"
	.string "Y, a diferencia de una MT, una MO\n"
	.string "se puede usar más de una vez.$"

RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees:
	.string "Cuando expandían la ciudad de\n"
	.string "RUSTBORO, mi papá ayudó.\p"
	.string "Hizo que sus POKéMON usaran CORTE\n"
	.string "para limpiar los árboles del lugar.$"

