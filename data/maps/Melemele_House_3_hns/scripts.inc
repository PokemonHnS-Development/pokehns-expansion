Melemele_House_3_hns_MapScripts::
	.byte 0


Melemele_House3_Woman::
	lock
	faceplayer
	msgbox Melemele_House3_Woman_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Melemele_House3_Man::
	lock
	faceplayer
	msgbox Melemele_House3_Man_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Melemele_House3_Woman_Text_0:
	.string "¡La vida aquí es muy tranquila!\p"
	.string "¡Y es genial que mis nietos estén\n"
	.string "cerca, en KANTO, en un bote!$"

Melemele_House3_Man_Text_0:
	.string "¡Malditos turistas!\p"
	.string "Mi agente dijo que este lugar era\n"
	.string "calmado... pero supongo que es más\l"
	.string "barato que viajar hasta ALOLA.$"
