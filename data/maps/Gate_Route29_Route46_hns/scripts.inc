Gate_Route29_Route46_hns_MapScripts::
	.byte 0

Gate_Route29_Route46_EventScript_Officer::
	lock
	faceplayer
	msgbox Gate_Route29_Route46_Text_Officer, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route29_Route46_EventScript_Youngster::
	lock
	faceplayer
	msgbox Gate_Route29_Route46_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route29_Route46_Text_Officer:
	.string "No puedes subir los salientes.\p"
	.string "Pero puedes saltar desde\n"
	.string "ellos para ir más rápido.$"

Gate_Route29_Route46_Text_Youngster:
	.string "Aparecen distintos tipos de\n"
	.string "POKéMON más allá de aquí.\p"
	.string "Si quieres atraparlos a todos,\n"
	.string "debes buscar por todas partes.$"
