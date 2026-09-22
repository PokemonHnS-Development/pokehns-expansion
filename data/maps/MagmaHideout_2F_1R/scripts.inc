MagmaHideout_2F_1R_MapScripts::
	.byte 0

MagmaHideout_2F_1R_EventScript_Grunt14::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_14, MagmaHideout_2F_1R_Text_Grunt14Intro, MagmaHideout_2F_1R_Text_Grunt14Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt14PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_3, MagmaHideout_2F_1R_Text_Grunt3Intro, MagmaHideout_2F_1R_Text_Grunt3Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_4, MagmaHideout_2F_1R_Text_Grunt4Intro, MagmaHideout_2F_1R_Text_Grunt4Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_5, MagmaHideout_2F_1R_Text_Grunt5Intro, MagmaHideout_2F_1R_Text_Grunt5Defeat
	msgbox MagmaHideout_2F_1R_Text_Grunt5PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_1R_Text_Grunt14Intro:
	.string "¿Qué, qué, qué?\p"
	.string "Solo los miembros del TEAM MAGMA\n"
	.string "deberían estar aquí!\p"
	.string "Pero no llevas puesto el uniforme\n"
	.string "del TEAM MAGMA...\p"
	.string "¡Me resultas sospechoso!\n"
	.string "¡Lucha contra mí!$"

MagmaHideout_2F_1R_Text_Grunt14Defeat:
	.string "Aiyiyi...\n"
	.string "My pride as a TEAM MAGMA member...$"

MagmaHideout_2F_1R_Text_Grunt14PostBattle:
	.string "Si tienes escalofríos, deberías\n"
	.string "unirte al TEAM MAGMA.$"

MagmaHideout_2F_1R_Text_Grunt3Intro:
	.string "¡Detente justo ahí!\p"
	.string "No esperas que yo guarde\n"
	.string "¿Dejar que pases así de fácil?$"

MagmaHideout_2F_1R_Text_Grunt3Defeat:
	.string "¡Oh, vaya!\n"
	.string "¡Me rindo!$"

MagmaHideout_2F_1R_Text_Grunt3PostBattle:
	.string "Quizás hubiera sido mejor si\n"
	.string "te hubiera dejado pasar...$"

MagmaHideout_2F_1R_Text_Grunt4Intro:
	.string "¡Ajaja!\n"
	.string "¡Un intruso!$"

MagmaHideout_2F_1R_Text_Grunt4Defeat:
	.string "Graaah!$"

MagmaHideout_2F_1R_Text_Grunt4PostBattle:
	.string "Ya he perdido.\p"
	.string "¿De verdad tengo que seguir corriendo\n"
	.string "en círculos?$"

MagmaHideout_2F_1R_Text_Grunt5Intro:
	.string "Oh, oh!\n"
	.string "¡Un intruso!$"

MagmaHideout_2F_1R_Text_Grunt5Defeat:
	.string "Mutter...$"

MagmaHideout_2F_1R_Text_Grunt5PostBattle:
	.string "Actually, I'm no expert at battling...$"

