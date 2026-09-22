PalletTown_RedsHouse_1F_hns_MapScripts::
	.byte 0

PalletTown_RedsHouse_1F_EventScript_Mom::
	lock
	faceplayer
	goto_if_ge VAR_TEMP_0, 1, PalletTown_RedsHouse_1F_EventScript_MomAfter
	msgbox RedsHouse_Text_Mom1, MSGBOX_DEFAULT
	closemessage
	setvar VAR_TEMP_0, 1
	release
	end

PalletTown_RedsHouse_1F_EventScript_MomAfter::
	msgbox RedsHouse_Text_Mom2, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_RedsHouse_1F_EventScript_TV::
	msgbox RedsHouse_Text_TV, MSGBOX_SIGN
	end

RedsHouse_Text_Mom1:
	.string "Hi!\p"
	.string "RED se fue hace mucho tiempo.\p"
	.string "Tampoco ha llamado, así que no\n"
	.string "tengo idea de dónde está ni de\l"
	.string "qué ha estado haciendo.\p"
	.string "Dicen que el silencio es prueba de\n"
	.string "que está bien, pero me preocupa\l"
	.string "mucho.$"

RedsHouse_Text_Mom2:
	.string "Temo que RED se lastime o enferme,\n"
	.string "pero es un chico.\p"
	.string "Me enorgullece que haga lo\n"
	.string "él desea hacer.$"

RedsHouse_Text_TV:
	.string "Tienen programas que no son\n"
	.string "vistos en JOHTO...$"
