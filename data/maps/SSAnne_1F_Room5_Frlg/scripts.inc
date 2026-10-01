SSAnne_1F_Room5_Frlg_MapScripts::
	.byte 0

SSAnne_1F_Room5_EventScript_Arthur::
	trainerbattle_single TRAINER_GENTLEMAN_ARTHUR, SSAnne_1F_Room5_Text_ArthurIntro, SSAnne_1F_Room5_Text_ArthurDefeat
	msgbox SSAnne_1F_Room5_Text_ArthurPostBattle, MSGBOX_AUTOCLOSE
	end

SSAnne_1F_Room5_Text_ArthurIntro::
	.string "¡Cachorro insolente!\n"
	.string "¡¿Cómo te atreves a entrar así!$"

SSAnne_1F_Room5_Text_ArthurDefeat::
	.string "¡Humph! ¡Niño grosero!\n"
	.string "¡No tienes modales!$"

SSAnne_1F_Room5_Text_ArthurPostBattle::
	.string "¡Quiero estar solo!\n"
	.string "¡Fuera!$"

