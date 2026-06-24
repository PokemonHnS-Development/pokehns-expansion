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
	.string "I bought this place so that my son\n"
	.string "and I could explore the outdoors…\p"
	.string "All he wants to do is play on that\n"
	.string "Game Boy.$"

Melemele_House6_GameboyKid_Text_0:
	.string "I have a game on my Game Boy that lets\n"
	.string "me explore the Alola Region!\p"
	.string "It's just like the real thing.\p"
	.string "It's called Ultra Eclipse,\n"
	.string "by Phantonomy!\p"
	.string "Haha, look!\n"
	.string "I'm riding an Icy Noivern!$"
