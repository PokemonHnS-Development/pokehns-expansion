Melemele_House_5_hns_MapScripts::
	.byte 0


Melemele_House5_Mom::
	lock
	faceplayer
	msgbox Melemele_House5_Mom_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Melemele_House5_Son::
	lockall
	faceplayer
	msgbox Melemele_House5_Son_Text_0
	playmoncry SPECIES_MEOWTH, 0
	waitmoncry
	msgbox Melemele_House5_Son_Text_1, MSGBOX_AUTOCLOSE
	releaseall
	end


Melemele_House5_Cat::
	lock
	faceplayer
	playmoncry SPECIES_MEOWTH, 0
	msgbox Melemele_House5_Cat_Text_0, MSGBOX_AUTOCLOSE
	waitmoncry
	release
	end


Melemele_House5_Mom_Text_0:
	.string "I'm thinking of moving to the Alola\n"
	.string "Region with my son, Elio.\p"
	.string "We're just getting a little taste here\n"
	.string "on the Isles!$"

Melemele_House5_Son_Text_0:
	.string "Hehe tag is so fun!$"

Melemele_House5_Son_Text_1:
	.string "Try to catch me meowth!$"

Melemele_House5_Cat_Text_0:
	.string "Mwaaawwwrrrrrrrr!!!$"
