Route12_House_hns_MapScripts::
	.byte 0

Route12_House_EventScript_SuperRod::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SUPER_ROD, Route12_House_EventScript_SuperRodGot
	msgbox Route12_House_Text_OfferSuperRod, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Route12_House_EventScript_SuperRodRefused
	msgbox Route12_House_Text_GiveSuperRod, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_ROD
	msgbox Route12_House_Text_GaveSuperRod, MSGBOX_DEFAULT
	setflag FLAG_GOT_SUPER_ROD
	closemessage
	release
	end

Route12_House_EventScript_SuperRodRefused::
	msgbox Route12_House_Text_DontWantSuperRod, MSGBOX_DEFAULT
	closemessage
	release
	end

Route12_House_EventScript_SuperRodGot::
	msgbox Route12_House_Text_GaveSuperRod, MSGBOX_NPC
	release
	end

Route12_House_Text_OfferSuperRod:
	.string "Soy el hermano menor del\n"
	.string "EXPERTO EN PESCA.\p"
	.string "Veo que te gusta pescar.\p"
	.string "¡No me cabe la menor duda\n"
	.string "al respecto!\p"
	.string "¿Y bien? Sé que tengo razón.$"

Route12_House_Text_GiveSuperRod:
	.string "¡Sí, sí. ¡Tal como pensaba!\p"
	.string "¡Toma esto, fan de la pesca!\n"
	.string "¡Es una SUPERCAÑA!$"

Route12_House_Text_GaveSuperRod:
	.string "Intenta pescar en cualquier lugar\n"
	.string "donde haya agua.\p"
	.string "Recuerda que puedes capturar\n"
	.string "POKéMON usando distintas CAÑAS.$"

Route12_House_Text_DontWantSuperRod:
	.string "¿Eh? ¿Mis ojos me engañaron?$"

