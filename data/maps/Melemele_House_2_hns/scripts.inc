Melemele_House_2_hns_MapScripts::
	.byte 0


Alola_Pokemart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart Alola_Pokemart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end


	.align 2
Alola_Pokemart_Pokemart:
	.2byte ITEM_BIG_MALASADA
	.2byte ITEM_FRIEND_BALL
	.2byte ITEM_NET_BALL
	.2byte ITEM_WAVE_INCENSE
	.2byte ITEM_LEMONADE
	.2byte ITEM_NONE

Alola_Pokemart_Cook::
	lock
	faceplayer
	msgbox Alola_Pokemart_Cook_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Alola_Pokemart_BaldMan::
	lock
	faceplayer
	msgbox Alola_Pokemart_BaldMan_Text_0, MSGBOX_AUTOCLOSE
	release
	end


Alola_Pokemart_Cook_Text_0:
	.string "The Malasadas here are delicious.\n"
	.string "Just like the real ones in Alola!$"

Alola_Pokemart_BaldMan_Text_0:
	.string "I'm looking for some sunscreen!\p"
	.string "It's sunnier here on the Isles!$"
