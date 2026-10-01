MagmaHideout_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MagmaHideout_1F_OnTransition
	.byte 0

MagmaHideout_1F_OnTransition:
	setvar VAR_JAGGED_PASS_ASH_WEATHER, 0
	end

MagmaHideout_1F_EventScript_Grunt1::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_1, MagmaHideout_1F_Text_Grunt1Intro, MagmaHideout_1F_Text_Grunt1Defeat
	msgbox MagmaHideout_1F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_EventScript_Grunt2::
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_2, MagmaHideout_1F_Text_Grunt2Intro, MagmaHideout_1F_Text_Grunt2Defeat
	msgbox MagmaHideout_1F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_1F_Text_Grunt1Intro:
	.string "Cuando el TEAM MAGMA pasa lista,\n"
	.string "nos dan tareas de guardia según\l"
	.string "el orden en que nos formamos.\p"
	.string "Por eso estoy aquí en el rincón.\n"
	.string "¡Siempre llego tarde al pase!$"

MagmaHideout_1F_Text_Grunt1Defeat:
	.string "¡También llego tarde a los\n"
	.string "entrenamientos!\p"
	.string "Odio admitirlo, pero soy un miedoso...$"

MagmaHideout_1F_Text_Grunt1PostBattle:
	.string "Está bien, me esforzaré un poco\n"
	.string "más de ahora en adelante...$"

MagmaHideout_1F_Text_Grunt2Intro:
	.string "Nuestro líder nos dijo que caváramos\n"
	.string "en el MT. CHIMNEY, y cavamos mucho.\p"
	.string "Y mientras excavábamos, nos\n"
	.string "topamos con algo increíble!\p"
	.string "¿Qué fue lo que encontraron?\p"
	.string "¡Fuhahaha!\n"
	.string "¡Te lo diré si me vences!$"

MagmaHideout_1F_Text_Grunt2Defeat:
	.string "¡Arrgh!\n"
	.string "¡Me derrotaron!$"

MagmaHideout_1F_Text_Grunt2PostBattle:
	.string "Al final no te lo diré.\n"
	.string "¡Lo descubrirás al llegar!\p"
	.string "Es mejor dejar las sorpresas\n"
	.string "para el final, ¿no crees?$"

