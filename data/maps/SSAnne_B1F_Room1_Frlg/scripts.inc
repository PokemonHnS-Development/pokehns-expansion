SSAnne_B1F_Room1_Frlg_MapScripts::
	.byte 0

SSAnne_B1F_Room1_EventScript_Barny::
	trainerbattle_single TRAINER_FISHERMAN_BARNY, SSAnne_B1F_Room1_Text_BarnyIntro, SSAnne_B1F_Room1_Text_BarnyDefeat
	msgbox SSAnne_B1F_Room1_Text_BarnyPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_B1F_Room1_EventScript_Phillip::
	trainerbattle_single TRAINER_SAILOR_PHILLIP, SSAnne_B1F_Room1_Text_PhillipIntro, SSAnne_B1F_Room1_Text_PhillipDefeat
	msgbox SSAnne_B1F_Room1_Text_PhillipPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_B1F_Room1_Text_PhillipIntro::
	.string "Dicen que hasta enseña CORTAR\n"
	.string "¡perdiste!$"

SSAnne_B1F_Room1_Text_PhillipDefeat::
	.string "Argh!\n"
	.string "¡Vencido por un niño!$"

SSAnne_B1F_Room1_Text_PhillipPostBattle::
	.string "Cuando estamos en alta mar, las\n"
	.string "POKéMON sometimes drift by.$"

SSAnne_B1F_Room1_Text_BarnyIntro::
	.string "Hello, stranger!\p"
	.string "No sé si vienes del mar o de\n"
	.string "or mountains, but stop and chat.\p"
	.string "All my POKéMON are from the sea.$"

SSAnne_B1F_Room1_Text_BarnyDefeat::
	.string "Darn!\n"
	.string "¡Dejé que escapara!$"

SSAnne_B1F_Room1_Text_BarnyPostBattle::
	.string "Iba a hacerte mi\n"
	.string "assistant, too!$"

