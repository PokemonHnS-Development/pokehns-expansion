RocketHideout_B3F_Frlg_MapScripts::
	.byte 0

RocketHideout_B3F_EventScript_Grunt1::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_14, RocketHideout_B3F_Text_Grunt1Intro, RocketHideout_B3F_Text_Grunt1Defeat
	msgbox RocketHideout_B3F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

RocketHideout_B3F_EventScript_Grunt2::
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_15, RocketHideout_B3F_Text_Grunt2Intro, RocketHideout_B3F_Text_Grunt2Defeat
	msgbox RocketHideout_B3F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

RocketHideout_B3F_Text_Grunt1Intro::
	.string "Deja de entrometerte en el\n"
	.string "asuntos, ¡o si no!$"

RocketHideout_B3F_Text_Grunt1Defeat::
	.string "¡Uf!\n"
	.string "¡Me derrotaron!$"

RocketHideout_B3F_Text_Grunt1PostBattle::
	.string "SILPH SCOPE?\n"
	.string "Ah, esa máquina que robó el\p"
	.string "JEFE. Está aquí en algún lado.$"

RocketHideout_B3F_Text_Grunt2Intro::
	.string "Nos avisaron desde arriba de que\n"
	.string "venías!$"

RocketHideout_B3F_Text_Grunt2Defeat::
	.string "¿Qué?\n"
	.string "¿Perdí? ¡No!$"

RocketHideout_B3F_Text_Grunt2PostBattle::
	.string "¡Adelante, sigue!\p"
	.string "Pero no puedes usar el ascensor\n"
	.string "sin la LLAVE DEL ASCENSOR.$"

