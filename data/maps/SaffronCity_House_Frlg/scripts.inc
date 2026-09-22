SaffronCity_House_Frlg_MapScripts::
	.byte 0

SaffronCity_House_EventScript_Lass::
	msgbox SaffronCity_House_Text_DontLookAtMyLetter, MSGBOX_NPC
	end

SaffronCity_House_EventScript_Youngster::
	msgbox SaffronCity_House_Text_GettingCopycatPokeDoll, MSGBOX_NPC
	end

SaffronCity_House_EventScript_Pidgey::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIDGEY, CRY_MODE_NORMAL
	msgbox SaffronCity_House_Text_Pidgey
	waitmoncry
	release
	end

SaffronCity_House_EventScript_Letter::
	msgbox SaffronCity_House_Text_ExplainPPUp, MSGBOX_SIGN
	end

SaffronCity_House_Text_DontLookAtMyLetter::
	.string "...Gracias por escribir.\n"
	.string "¡Espero verte pronto!\p"
	.string "...Hey!\n"
	.string "¡No mires mi carta!$"

SaffronCity_House_Text_Pidgey::
	.string "PIDGEY: Kurukkoo!$"

SaffronCity_House_Text_GettingCopycatPokeDoll::
	.string "¡La IMITADORA es linda!\n"
	.string "I'm getting her a POKé DOLL.$"

SaffronCity_House_Text_ExplainPPUp::
	.string "Me regalaron un PP UP.\p"
	.string "Sirve para aumentar los PP de\n"
	.string "un movimiento POKéMON.\p"
	.string "Debería usarlo en un movimiento\n"
	.string "poderoso con pocos PP.$"

