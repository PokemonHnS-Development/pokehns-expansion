SSAnne_2F_Room2_Frlg_MapScripts::
	.byte 0

SSAnne_2F_Room2_EventScript_Dale::
	trainerbattle_single TRAINER_FISHERMAN_DALE, SSAnne_2F_Room2_Text_DaleIntro, SSAnne_2F_Room2_Text_DaleDefeat
	msgbox SSAnne_2F_Room2_Text_DalePostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_2F_Room2_EventScript_Brooks::
	trainerbattle_single TRAINER_GENTLEMAN_BROOKS, SSAnne_2F_Room2_Text_BrooksIntro, SSAnne_2F_Room2_Text_BrooksDefeat
	msgbox SSAnne_2F_Room2_Text_BrooksPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_2F_Room2_Text_BrooksIntro::
	.string "Competir con los jóvenes me\n"
	.string "mantiene joven.$"

SSAnne_2F_Room2_Text_BrooksDefeat::
	.string "¡Buen combate!\n"
	.string "Ah, me siento joven otra vez!$"

SSAnne_2F_Room2_Text_BrooksPostBattle::
	.string "Hace quince años, yo\n"
	.string "¡ha ganado!$"

SSAnne_2F_Room2_Text_DaleIntro::
	.string "¡Mira lo que pesqué!$"

SSAnne_2F_Room2_Text_DaleDefeat::
	.string "¡Me quedé sin nada!$"

SSAnne_2F_Room2_Text_DalePostBattle::
	.string "Party?\p"
	.string "La fiesta del crucero debería\n"
	.string "terminó ya.$"

