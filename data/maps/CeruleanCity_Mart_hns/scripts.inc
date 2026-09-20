CeruleanCity_Mart_hns_MapScripts::
	.byte 0

CeruleanCity_Mart_EventScript_Juggler::
	msgbox CeruleanMart_Text_CooltrainerM, MSGBOX_NPC
	end

CeruleanCity_Mart_EventScript_CooltrainerF::
	msgbox CeruleanMart_Text_CooltrainerF, MSGBOX_NPC
	end

CeruleanMart_Text_CooltrainerM:
	.string "Te hallarás con muchos entrenadores\n"
	.string "camino al CABO de CERULEAN.\p"
	.string "Quieren ver cómo se comparan\n"
	.string "con otros entrenadores.$"

CeruleanMart_Text_CooltrainerF:
	.string "MISTY es casi la única persona en\n"
	.string "el pueblo que puede vencerlos.\l"
	.string "la CAPA de CIUDAD MALVA.$"
