MagmaHideout_3F_1R_MapScripts::
	.byte 0

MagmaHideout_3F_1R_EventScript_Grunt9::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_9, MagmaHideout_3F_1R_Text_Grunt9Intro, MagmaHideout_3F_1R_Text_Grunt9Defeat
	msgbox MagmaHideout_3F_1R_Text_Grunt9PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_1R_EventScript_Grunt16::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_16, MagmaHideout_3F_1R_Text_Grunt16Intro, MagmaHideout_3F_1R_Text_Grunt16Defeat
	msgbox MagmaHideout_3F_1R_Text_Grunt16PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_3F_1R_Text_Grunt9Intro:
	.string "¿Qué hice para merecer este puesto\n"
	.string "de guardia?\p"
	.string "¡Me arde la oreja izquierda!$"

MagmaHideout_3F_1R_Text_Grunt9Defeat:
	.string "I'm getting heat exhaustion…$"

MagmaHideout_3F_1R_Text_Grunt9PostBattle:
	.string "¿No crees que es raro usar capuchas\n"
	.string "en este volcán lleno de magma?$"

MagmaHideout_3F_1R_Text_Grunt16Intro:
	.string "Nos unimos para ayudar a nuestro\n"
	.string "líder a lograr su gran visión.\p"
	.string "No me importa si eres del TEAM AQUA\n"
	.string "o si solo eres un niño que pasa.\p"
	.string "¡Nadie nos interfiere y sale\n"
	.string "impune de esto!$"

MagmaHideout_3F_1R_Text_Grunt16Defeat:
	.string "Oh, no!\n"
	.string "¡No se puede confiar en ti!$"

MagmaHideout_3F_1R_Text_Grunt16PostBattle:
	.string "Escúchame.\n"
	.string "¡El TEAM MAGMA tiene razón!\p"
	.string "No escuches al TEAM AQUA.\n"
	.string "¡No creas sus mentiras!$"

