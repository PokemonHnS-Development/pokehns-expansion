SSAnne_2F_Room4_Frlg_MapScripts::
	.byte 0

SSAnne_2F_Room4_EventScript_Lamar::
	trainerbattle_single TRAINER_GENTLEMAN_LAMAR, SSAnne_2F_Room4_Text_LamarIntro, SSAnne_2F_Room4_Text_LamarDefeat
	msgbox SSAnne_2F_Room4_Text_LamarPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_2F_Room4_EventScript_Dawn::
	trainerbattle_single TRAINER_LASS_DAWN, SSAnne_2F_Room4_Text_DawnIntro, SSAnne_2F_Room4_Text_DawnDefeat
	msgbox SSAnne_2F_Room4_Text_DawnPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_2F_Room4_Text_LamarIntro::
	.string "¿Cuál te parece más digno,\n"
	.string "a strong or a rare POKéMON?$"

SSAnne_2F_Room4_Text_LamarDefeat::
	.string "¡Debo saludarte!$"

SSAnne_2F_Room4_Text_LamarPostBattle::
	.string "Personalmente, prefiero a los\n"
	.string "POKéMON raros.$"

SSAnne_2F_Room4_Text_DawnIntro::
	.string "No creo haberte visto por ahí.\n"
	.string "party?$"

SSAnne_2F_Room4_Text_DawnDefeat::
	.string "¡Tómalo con calma!$"

SSAnne_2F_Room4_Text_DawnPostBattle::
	.string "Oh, I adore your strong POKéMON!\n"
	.string "¡Oh, cómo los envidio!$"

