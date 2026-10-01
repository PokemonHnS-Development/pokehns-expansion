GraniteCave_1F_MapScripts::
	.byte 0

GraniteCave_1F_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_1F_EventScript_ReceivedFlash
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
	giveitem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_EventScript_ReceivedFlash::
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
	release
	end

GraniteCave_1F_Text_GetsDarkAheadHereYouGo:
	.string "Oye, tú.\n"
	.string "Se pone muy oscuro más adelante.\l"
	.string "Será difícil intentar explorar.\p"
	.string "Aquel chico que pasó hace poco...\n"
	.string "STEVEN, creo que se llamaba.\p"
	.string "Él sabía usar FLASH, así que\n"
	.string "debería estar bien, pero...\p"
	.string "Bueno, los EXCURSIONISTAS ayudamos\n"
	.string "ayudar a quien encontremos es el lema.\p"
	.string "Toma, te daré esto.$"

GraniteCave_1F_Text_ExplainFlash:
	.string "Enseña el movimiento oculto FLASH a\n"
	.string "un POKéMON y úsalo.\p"
	.string "Ilumina incluso la oscuridad total\n"
	.string "de las cuevas.\p"
	.string "Pero para usarla, necesitas la MEDALLA\n"
	.string "del GIMNASIO POKéMON de ROCÍO.$"

