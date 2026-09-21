PewterCity_Museum_1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RuinsOfAlph_Lab_OnTransition
	.byte 0

PewterCity_Museum_1F_EventScript_RootFossil::
	finditem ITEM_ROOT_FOSSIL
	setflag FLAG_HIDE_PEWTER_ROOT_FOSSIL
	removeobject LOCALID_MUSEUM_ROOTFOSSIL
	end

PewterCity_Museum_1F_EventScript_ClawFossil::
	finditem ITEM_CLAW_FOSSIL
	setflag FLAG_HIDE_PEWTER_CLAW_FOSSIL
	removeobject LOCALID_MUSEUM_CLAWFOSSIL
	end

PewterCity_Museum_1F_EventScript_Receptionist::
	msgbox PewterCity_Museum_1F_Text_Recptionist, MSGBOX_NPC
	end

PewterCity_Museum_1F_EventScript_FossilWoman::
	goto_if_set FLAG_HIDE_PEWTER_CLAW_FOSSIL, PewterCity_Museum_1F_EventScript_FossilWoman2
	goto_if_set FLAG_HIDE_PEWTER_ROOT_FOSSIL, PewterCity_Museum_1F_EventScript_FossilWoman2
	goto_if_ge VAR_TEMP_2, 1, PewterCity_Museum_1F_EventScript_FossilWoman2
	msgbox PewterCity_Museum_1F_Text_FossilWoman, MSGBOX_NPC
	setvar VAR_TEMP_2, 1
	end

PewterCity_Museum_1F_EventScript_FossilWoman2::
	msgbox PewterCity_Museum_1F_Text_FossilWomanAfter, MSGBOX_NPC
	end

PewterCity_Museum_1F_EventScript_Oldman::
	msgbox PewterCity_Museum_1F_Text_Oldman, MSGBOX_NPC
	end

PewterCity_Museum_1F_EventScript_Bones::
	msgbox PewterCity_Museum_1F_Text_Bones, MSGBOX_SIGN
	end

PewterCity_Museum_1F_Text_Recptionist:
	.string "¡Bienvenido!\p"
	.string "Solo para que sepas, todos los\n"
	.string "especímenes grandes fueron llevados\l"
	.string "a otros museos para exhibirlos.\p"
	.string "¡Así que por ahora la entrada es\n"
	.string "gratis!\p"
	.string "Por favor, adelante.$"

PewterCity_Museum_1F_Text_FossilWoman:
	.string "Debes ser un entrenador fuerte.\pNo les damos mucho uso a los\nfósiles del mostrador de allí.\pUn hombre raro de cabello plateado\ndejó un montón de ellos aquí.\pAdelante, tómalos si quieres.$"

PewterCity_Museum_1F_Text_FossilWomanAfter:
	.string "Solemos compartir investigaciones\n"
	.string "con los de RUINS OF ALPH.\p"
	.string "¡Incluso compartimos fósiles\n"
	.string "a través de la PC!$"

PewterCity_Museum_1F_Text_Oldman:
	.string "Debería estar agradecido por mi\n"
	.string "larga vida.\p"
	.string "¡Jamás pensé que vería los\n"
	.string "huesos de un dragón!$"

PewterCity_Museum_1F_Text_Bones:
	.string "Huesos de un dragón antiguo\n"
	.string "POKéMON.$"
