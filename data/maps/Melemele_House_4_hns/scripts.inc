Melemele_House_4_hns_MapScripts::
	.byte 0


Melemele_House4_Man::
	lock
	faceplayer
	msgbox Melemele_House4_Man_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Melemele_House4_Woman::
	lock
	faceplayer
	msgbox Melemele_House4_Woman_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Melemele_House4_Man_Text_0:
	.string "¡Estamos de vacaciones en ALOLA!\p"
	.string "Es justo como la región de ALOLA,\n"
	.string "¡pero más cerca de KANTO!\p"
	.string "¡Ahorré mucho en los viajes!$"

Melemele_House4_Woman_Text_0:
	.string "Mi novio me dijo que iríamos a\n"
	.string "ALOLA…\p"
	.string "Supuse que sería la región de\n"
	.string "ALOLA, no las islas pequeñas de la\l"
	.string "costa de KANTO.$"
