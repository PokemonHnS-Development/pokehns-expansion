SafariZone_SecretHouse_Frlg_MapScripts::
	.byte 0

SafariZone_SecretHouse_EventScript_Attendant::
	lock
	faceplayer
	goto_if_set FLAG_GOT_HM03, SafariZone_SecretHouse_EventScript_ExplainSurf
	msgbox SafariZone_SecretHouse_Text_CongratsYouveWon
	checkitemspace ITEM_HM03
	goto_if_eq VAR_RESULT, FALSE, SafariZone_SecretHouse_EventScript_NoRoomForHM03
	giveitem_msg SafariZone_SecretHouse_Text_ReceivedHM03FromAttendant, ITEM_HM03
	msgbox SafariZone_SecretHouse_Text_ExplainSurf
	setflag FLAG_GOT_HM03
	release
	end

SafariZone_SecretHouse_EventScript_NoRoomForHM03::
	msgbox SafariZone_SecretHouse_Text_DontHaveRoomForPrize
	release
	end

SafariZone_SecretHouse_EventScript_ExplainSurf::
	msgbox SafariZone_SecretHouse_Text_ExplainSurf
	release
	end

SafariZone_SecretHouse_Text_CongratsYouveWon::
	.string "Ah! Finally!\p"
	.string "¡Eres la primera persona en\nllegar a"
	.string "la CASA SECRETA!\p"
	.string "Aunque hice una campaña\npara nuestra"
	.string "gran inauguración,\p"
	.string "Me preocupaba que nadie\n"
	.string "ganara nuestro premio.\p"
	.string "¡Felicidades!\n"
	.string "¡Has ganado!$"

SafariZone_SecretHouse_Text_ReceivedHM03FromAttendant::
	.string "{PLAYER} received HM03\n"
	.string "del encargado!$"

SafariZone_SecretHouse_Text_ExplainSurf::
	.string "MO03 es SURF.\p"
	.string "POKéMON will be able to ferry you\n"
	.string "sobre el agua usándolo.\p"
	.string "Y esta MO no es desechable, así\n"
	.string "que puedes usarla una y otra vez.\p"
	.string "Tienes mucha suerte por ganar esto\n"
	.string "fabulous prize!$"

SafariZone_SecretHouse_Text_DontHaveRoomForPrize::
	.string "No tienes espacio para esto\n"
	.string "fabulous prize!$"

