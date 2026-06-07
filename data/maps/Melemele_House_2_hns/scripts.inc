Melemele_House_2_hns_MapScripts::
	.byte 0


Alola_Pokemart_EventScript_Clerk::
# 4 "data/maps/Melemele_House_2_hns/scripts.pory"
	lock
# 5 "data/maps/Melemele_House_2_hns/scripts.pory"
	faceplayer
# 6 "data/maps/Melemele_House_2_hns/scripts.pory"
	message gText_HowMayIServeYou
# 7 "data/maps/Melemele_House_2_hns/scripts.pory"
	waitmessage
# 8 "data/maps/Melemele_House_2_hns/scripts.pory"
	pokemart Alola_Pokemart_Pokemart
# 9 "data/maps/Melemele_House_2_hns/scripts.pory"
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
# 10 "data/maps/Melemele_House_2_hns/scripts.pory"
	release
	end


	.align 2
# 14 "data/maps/Melemele_House_2_hns/scripts.pory"
Alola_Pokemart_Pokemart:
# 15 "data/maps/Melemele_House_2_hns/scripts.pory"
	.2byte ITEM_BIG_MALASADA
# 16 "data/maps/Melemele_House_2_hns/scripts.pory"
	.2byte ITEM_FRIEND_BALL
# 17 "data/maps/Melemele_House_2_hns/scripts.pory"
	.2byte ITEM_NET_BALL
# 18 "data/maps/Melemele_House_2_hns/scripts.pory"
	.2byte ITEM_WAVE_INCENSE
# 19 "data/maps/Melemele_House_2_hns/scripts.pory"
	.2byte ITEM_LEMONADE
	.2byte ITEM_NONE

Alola_Pokemart_Cook::
# 23 "data/maps/Melemele_House_2_hns/scripts.pory"
	lock
# 24 "data/maps/Melemele_House_2_hns/scripts.pory"
	faceplayer
# 25 "data/maps/Melemele_House_2_hns/scripts.pory"
	msgbox Alola_Pokemart_Cook_Text_0, MSGBOX_AUTOCLOSE
# 27 "data/maps/Melemele_House_2_hns/scripts.pory"
	release
	end


Alola_Pokemart_BaldMan::
# 32 "data/maps/Melemele_House_2_hns/scripts.pory"
	lock
# 33 "data/maps/Melemele_House_2_hns/scripts.pory"
	faceplayer
# 34 "data/maps/Melemele_House_2_hns/scripts.pory"
	msgbox Alola_Pokemart_BaldMan_Text_0, MSGBOX_AUTOCLOSE
# 37 "data/maps/Melemele_House_2_hns/scripts.pory"
	release
	end


Alola_Pokemart_Cook_Text_0:
# 25 "data/maps/Melemele_House_2_hns/scripts.pory"
	.string "The Malasadas here are delicious.\n"
	.string "Just like the real ones in Alola!$"

Alola_Pokemart_BaldMan_Text_0:
# 34 "data/maps/Melemele_House_2_hns/scripts.pory"
	.string "I'm looking for some sunscreen!\p"
	.string "It's a sunnier here on the Isles!$"
