Melemele_House_5_hns_MapScripts::
	.byte 0


Melemele_House5_Mom::
	lock
	faceplayer
	msgbox Melemele_House5_Mom_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Melemele_House5_Son::
	lock
	faceplayer
	msgbox Melemele_House5_Son_Text_0
	applymovement melemele_elio Melemele_House5_Son_Movement
	playse SE_LEDGE
	waitse
	playse SE_LEDGE
	waitse
	waitmovement
	msgbox Melemele_House5_Son_Text_1, MSGBOX_AUTOCLOSE
	playmoncry SPECIES_MEOWTH, 0
	waitmoncry
	release
	end


Melemele_House5_Cat::
	lock
	faceplayer
	playmoncry SPECIES_MEOWTH, 0
	msgbox Melemele_House5_Cat_Text_0, MSGBOX_AUTOCLOSE
	waitmoncry
	release
	end

Melemele_House5_Son_Movement:
	jump_in_place_down
	jump_in_place_down
	step_end

Melemele_House5_Mom_Text_0:
	.string "Pienso mudarme a la región de\n"
	.string "ALOLA con mi hijo, ELIO.\p"
	.string "¡Solo estamos probando un poco\n"
	.string "aquí en las ISLAS!$"

Melemele_House5_Son_Text_0:
	.string "Jeje... ¡las traes son geniales!$"

Melemele_House5_Son_Text_1:
	.string "¡Intenta atraparme, MEOWTH!$"

Melemele_House5_Cat_Text_0:
	.string "¡Mwaaawwwrrrrrrrr!$"
