Melemele_House_6_hns_MapScripts::
	.byte 0


Melemele_House6_Hiker::
	lock
	faceplayer
	msgbox Melemele_House6_Hiker_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Melemele_House6_GameboyKid::
	lock
	faceplayer
	msgbox Melemele_House6_GameboyKid_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Melemele_House6_Hiker_Text_0:
	.string "Compré este lugar para que mi hijo\n"
	.string "y yo exploráramos el exterior...\p"
	.string "Pero él solo quiere jugar con su\n"
	.string "Game Boy Advance.$"

Melemele_House6_GameboyKid_Text_0:
	.string "Tengo un juego en mi Game Boy Advance\n"
	.string "¡que me deja explorar ALOLA!\p"
	.string "Es igual que en la vida real.\p"
	.string "Se llama ULTRA ECLIPSE,\n"
	.string "¡de PHANTONOMY!\p"
	.string "¡Ja, ja, mira!\n"
	.string "¡Voy montado en un NOIVERN de hielo!$"
