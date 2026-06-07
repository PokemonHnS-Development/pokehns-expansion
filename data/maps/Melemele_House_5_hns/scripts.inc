Melemele_House_5_hns_MapScripts::
	.byte 0


Melemele_House5_Mom::
# 4 "data/maps/Melemele_House_5_hns/scripts.pory"
	lock
# 5 "data/maps/Melemele_House_5_hns/scripts.pory"
	faceplayer
# 6 "data/maps/Melemele_House_5_hns/scripts.pory"
	msgbox Melemele_House5_Mom_Text_0, MSGBOX_AUTOCLOSE
# 11 "data/maps/Melemele_House_5_hns/scripts.pory"
	release
	end


Melemele_House5_Son::
# 16 "data/maps/Melemele_House_5_hns/scripts.pory"
	lockall
# 17 "data/maps/Melemele_House_5_hns/scripts.pory"
	faceplayer
# 18 "data/maps/Melemele_House_5_hns/scripts.pory"
	msgbox Melemele_House5_Son_Text_0
# 19 "data/maps/Melemele_House_5_hns/scripts.pory"
	playmoncry SPECIES_MEOWTH, 0
# 20 "data/maps/Melemele_House_5_hns/scripts.pory"
	waitmoncry
# 21 "data/maps/Melemele_House_5_hns/scripts.pory"
	msgbox Melemele_House5_Son_Text_1, MSGBOX_AUTOCLOSE
# 22 "data/maps/Melemele_House_5_hns/scripts.pory"
	releaseall
	end


Melemele_House5_Cat::
# 27 "data/maps/Melemele_House_5_hns/scripts.pory"
	lock
# 28 "data/maps/Melemele_House_5_hns/scripts.pory"
	faceplayer
# 29 "data/maps/Melemele_House_5_hns/scripts.pory"
	playmoncry SPECIES_MEOWTH, 0
# 30 "data/maps/Melemele_House_5_hns/scripts.pory"
	msgbox Melemele_House5_Cat_Text_0, MSGBOX_AUTOCLOSE
# 31 "data/maps/Melemele_House_5_hns/scripts.pory"
	waitmoncry
# 32 "data/maps/Melemele_House_5_hns/scripts.pory"
	release
	end


Melemele_House5_Mom_Text_0:
# 6 "data/maps/Melemele_House_5_hns/scripts.pory"
	.string "I'm thinking of moving to the Alola\n"
	.string "Region with my son, Elio.\p"
	.string "We're just getting a little taste here\n"
	.string "on the Isles!$"

Melemele_House5_Son_Text_0:
# 18 "data/maps/Melemele_House_5_hns/scripts.pory"
	.string "Hehe tag is so fun!$"

Melemele_House5_Son_Text_1:
# 21 "data/maps/Melemele_House_5_hns/scripts.pory"
	.string "Try to catch me meowth!$"

Melemele_House5_Cat_Text_0:
# 30 "data/maps/Melemele_House_5_hns/scripts.pory"
	.string "Mwaaawwwrrrrrrrr!!!$"
