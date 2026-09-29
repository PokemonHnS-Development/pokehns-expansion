PewterCity_Museum_2F_hns_MapScripts::
	.byte 0


PewterCity_Museum_2F_EventScript_Nerd::
	msgbox PewterCity_Museum_2F_Text_Nerd, MSGBOX_NPC
	end

PewterCity_Museum_2F_EventScript_Daughter::
	lock
	msgbox PewterCity_Museum_2F_Text_AskedDaddyToCatchPikachu, MSGBOX_DEFAULT
	release
	end

PewterCity_Museum_2F_EventScript_Dad::
	lock
	msgbox PewterCity_Museum_2F_Text_PikachuSoonIPromise, MSGBOX_DEFAULT
	release
	end

PewterCity_Museum_2F_EventScript_Meteor::
	msgbox PewterCity_Museum_2F_Text_MeteoriteThatFellOnMtMoon, MSGBOX_SIGN
	end

PewterCity_Museum_2F_Text_Nerd:
	.string "Dicen que meteoritos cayeron en\n"
	.string "ISLA ORIGEN.\p"
	.string "Nos encantaría exhibirlos aquí\n"
	.string "en nuestro museo, pero...\p"
	.string "Dicen que estos meteoritos emiten\n"
	.string "una energía extraña y no pueden\l"
	.string "ser trasladados...$"

PewterCity_Museum_2F_Text_AskedDaddyToCatchPikachu::
    .string "¡Quiero un PIKACHU!\n"
    .string "¡Es tan lindo!\p"
    .string "¡Le pedí a mi papi que atrape uno!$"

PewterCity_Museum_2F_Text_PikachuSoonIPromise::
    .string "Yeah, a PIKACHU soon, I promise!$"

PewterCity_Museum_2F_Text_SpaceShuttle::
    .string "Space Shuttle$"

PewterCity_Museum_2F_Text_MeteoriteThatFellOnMtMoon::
	.string "Un meteorito caído en MONTE LUNA.\n"
    .string "Se cree que es una MOON STONE.$"
