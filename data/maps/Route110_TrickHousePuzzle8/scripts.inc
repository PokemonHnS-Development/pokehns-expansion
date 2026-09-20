Route110_TrickHousePuzzle8_MapScripts::
	.byte 0

Route110_TrickHousePuzzle8_EventScript_Scroll::
	lockall
	goto_if_eq VAR_TRICK_HOUSE_PUZZLE_8_STATE, 0, Route110_TrickHousePuzzle8_EventScript_FoundScroll
	goto Route110_TrickHousePuzzle_EventScript_ReadScrollAgain
	end

Route110_TrickHousePuzzle8_EventScript_FoundScroll::
	setvar VAR_TRICK_HOUSE_PUZZLE_8_STATE, 1
	goto Route110_TrickHousePuzzle_EventScript_FoundScroll
	end

Route110_TrickHousePuzzle8_EventScript_Vincent::
	trainerbattle_single TRAINER_VINCENT, Route110_TrickHousePuzzle8_Text_VincentIntro, Route110_TrickHousePuzzle8_Text_VincentDefeat
	msgbox Route110_TrickHousePuzzle8_Text_VincentPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_Keira::
	trainerbattle_single TRAINER_KEIRA, Route110_TrickHousePuzzle8_Text_KeiraIntro, Route110_TrickHousePuzzle8_Text_KeiraDefeat
	msgbox Route110_TrickHousePuzzle8_Text_KeiraPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_EventScript_Leroy::
	trainerbattle_single TRAINER_LEROY, Route110_TrickHousePuzzle8_Text_LeroyIntro, Route110_TrickHousePuzzle8_Text_LeroyDefeat
	msgbox Route110_TrickHousePuzzle8_Text_LeroyPostBattle, MSGBOX_AUTOCLOSE
	end

Route110_TrickHousePuzzle8_Text_WroteSecretCodeLockOpened::
	.string "{PLAYER} anotó el código secreto\n"
	.string "en la puerta.\p"
	.string "“AMO SER UN MAESTRO DEL TRUCO”.\n"
	.string "… … … … … … … …\p"
	.string "¡La cerradura se abrió!$"

Route110_TrickHousePuzzle8_Text_VincentIntro:
	.string "No muchos ENTRENADORES han\n"
	.string "llegado tan lejos.$"

Route110_TrickHousePuzzle8_Text_VincentDefeat:
	.string "That must mean you're tough, too…$"

Route110_TrickHousePuzzle8_Text_VincentPostBattle:
	.string "¿Has vencido al CAMPEÓN de la\n"
	.string "LIGA POKéMON? ¡Es demasiado!$"

Route110_TrickHousePuzzle8_Text_KeiraIntro:
	.string "¡Siéntete afortunado de\n"
	.string "luchar contra mí!$"

Route110_TrickHousePuzzle8_Text_KeiraDefeat:
	.string "¡Esto no puede ser!\n"
	.string "¡No puedo perder!$"

Route110_TrickHousePuzzle8_Text_KeiraPostBattle:
	.string "Es un milagro que me vencieras.\n"
	.string "Puedes presumir de ello.$"

Route110_TrickHousePuzzle8_Text_LeroyIntro:
	.string "Tú también has superado el reto de\n"
	.string "la CASA DE TRUCOS.$"

Route110_TrickHousePuzzle8_Text_LeroyDefeat:
	.string "Ya veo...\n"
	.string "Tienes un estilo extraordinario.$"

Route110_TrickHousePuzzle8_Text_LeroyPostBattle:
	.string "Ver a alguien como tú debería\n"
	.string "gustarle al MAESTRO DE TRUCOS.$"

