MagmaHideout_3F_2R_MapScripts::
	.byte 0

MagmaHideout_3F_2R_EventScript_Grunt10::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_10, MagmaHideout_3F_2R_Text_Grunt10Intro, MagmaHideout_3F_2R_Text_Grunt10Defeat
	msgbox MagmaHideout_3F_2R_Text_Grunt10PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_2R_Text_Grunt10Intro:
	.string "Entiendo todo lo que nuestro líder\n"
	.string "dice. Pero, ¿sabes qué?\p"
	.string "Hacer cosas como despertar a un\n"
	.string "POKéMON antiguo y robarle el\l"
	.string "METEORITO a alguien...\p"
	.string "Creo que estamos yendo muy lejos.\n"
	.string "¿Tú qué opinas?$"

MagmaHideout_3F_2R_Text_Grunt10Defeat:
	.string "Sí, creo que estamos haciendo\n"
	.string "algo mal de alguna forma.$"

MagmaHideout_3F_2R_Text_Grunt10PostBattle:
	.string "Perder contra ti me aclaró la mente.\p"
	.string "La próxima vez que vea al líder,\n"
	.string "le preguntaré sobre lo que hacemos.$"

