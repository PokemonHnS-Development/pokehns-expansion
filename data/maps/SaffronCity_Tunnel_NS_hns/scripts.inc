SaffronCity_Tunnel_NS_hns_MapScripts::
	.byte 0

SaffronCity_Tunnel_NS_EventScript_BaldingMan::
	lock
	faceplayer
	goto_if_set FLAG_ITEM_UNDERGROUND_PATH_TM_EXPLOSION, SaffronCity_Tunnel_NS_EventScript_BaldingManAfter
	msgbox SaffronCity_Tunnel_NS_Text_BaldingManIntro, MSGBOX_DEFAULT
	checkitem ITEM_RAGE_CANDY_BAR
	goto_if_eq VAR_RESULT, TRUE, SaffronCity_Tunnel_NS_EventScript_BaldingManDetected
	closemessage
	release
	end

SaffronCity_Tunnel_NS_EventScript_BaldingManDetected::
	playse SE_PIN
	applymovement LOCALID_SAFFRONTUNNEL_UNCLE_RAGE, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SAFFRONTUNNEL_UNCLE_RAGE
	msgbox SaffronCity_Tunnel_NS_Text_BaldingManCandybarDetected, MSGBOX_DEFAULT
	removeitem ITEM_RAGE_CANDY_BAR
	msgbox SaffronCity_Tunnel_NS_Text_BaldingManGaveCandybar, MSGBOX_DEFAULT
	giveitem ITEM_TM_EXPLOSION
	setflag FLAG_ITEM_UNDERGROUND_PATH_TM_EXPLOSION
SaffronCity_Tunnel_NS_EventScript_BaldingManAfter::
	msgbox SaffronCity_Tunnel_NS_Text_BaldingManGaveTm, MSGBOX_DEFAULT
	closemessage
	release
	end

SaffronCity_Tunnel_NS_Text_BaldingManIntro:
	.string "Don't be afraid, I'm not a bad\n"
	.string "person.\p"
	.string "A place like this...\n"
	.string "attracts mean people.\p"
	.string "They would eventually cause\n"
	.string "trouble...\p"
	.string "It makes me mad just thinking about\n"
	.string "it.$"

SaffronCity_Tunnel_NS_Text_BaldingManCandybarDetected:
	.string "Aha!\n"
	.string "That's a RAGE CANDYBAR!\p"
	.string "Can I have it?\n"
	.string "Please!$"

SaffronCity_Tunnel_NS_Text_BaldingManGaveCandybar:
	.string "{PLAYER} Gave the RageCandyBar to the\n"
	.string "tipo del camino subterráneo.\p"
	.string "¡Ñam!\p"
	.string "¡Qué frustrante!\p"
	.string "¡Pero esto está riquísimo!\p"
	.string "¡Ñam ñam!\p"
	.string "¡Aargh! ¡Me pone furioso!\p"
	.string "¡Ñam ñam!\p"
	.string "Aargh...\p"
	.string "...................¡Uff!\p"
	.string "¡Ya me siento mucho mejor!\n"
	.string "¡Gracias por tu caramelo!\l"
	.string "¡Quiero que tengas esto!$"

SaffronCity_Tunnel_NS_Text_BaldingManGaveTm:
	.string "La MT 64 contiene........\p"
	.string "tic-\n"
	.string "            tock\l"
	.string "tic-\l"
	.string "            tock\l"
	.string "tic-\l"
	.string "            tock\l"
	.string "tic-\l"
	.string "            tock\l"
	.string "tick.....\l"
	.string "......................\l"
	.string "......................\l"
	.string "KA-BOOM!!!$"	

