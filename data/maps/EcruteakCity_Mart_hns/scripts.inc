EcruteakCity_Mart_hns_MapScripts::
	.byte 0

EcruteakCity_Mart_EventScript_Nerd::
	lock
	faceplayer
	msgbox EcruteakMart_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_Mart_EventScript_Granny::
	lock
	faceplayer
	msgbox EcruteakMart_Text_Granny, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakMart_Text_SuperNerd:
	.string "האיווי שלי התפתח לאספיאון.\p"
	.string "אבל האיווי של החבר שלי הפך\n"
	.string "לאמבריאון.\p"
	.string "למה, בעצם? שנינו גידלנו את\n"
	.string "האיווי שלנו באותה דרך…$"

EcruteakMart_Text_Granny:
	.string "עם החייאה, פוקימון שהתעלף\n"
	.string "מתעורר מיד.$"
