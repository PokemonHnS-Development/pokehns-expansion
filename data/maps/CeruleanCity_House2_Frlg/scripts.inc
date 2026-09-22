CeruleanCity_House2_Frlg_MapScripts::
	.byte 0

CeruleanCity_House2_EventScript_Hiker::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM28_FROM_ROCKET, CeruleanCity_House2_EventScript_HikerGotTM28
	msgbox CeruleanCity_House2_Text_RocketsStoleTMForDig
	release
	end

CeruleanCity_House2_EventScript_HikerGotTM28::
	msgbox CeruleanCity_House2_Text_TeachDiglettDigWithoutTM
	release
	end

CeruleanCity_House2_EventScript_Lass::
	msgbox CeruleanCity_House2_Text_TeamRocketTryingToDigIntoNoGood, MSGBOX_NPC
	end

CeruleanCity_House2_EventScript_WallHole::
	msgbox CeruleanCity_House2_Text_TeamRocketLeftWayOut, MSGBOX_SIGN
	end

CeruleanCity_House2_Text_RocketsStoleTMForDig::
	.string "Those miserable ROCKETS!\p"
	.string "Mira lo que le han hecho a mi\n"
	.string "house!\p"
	.string "Robaron una MT que enseña\n"
	.string "POKéMON how to DIG holes!\p"
	.string "Iba a usarla en un\n"
	.string "MANKEY o un SANDSHREW…\p"
	.string "¡Eso me costó un dineral!$"

CeruleanCity_House2_Text_TeachDiglettDigWithoutTM::
	.string "Supongo que lo perdido,\p"
	.string "I decided to teach DIGLETT how to\n"
	.string "CAVAR sin una MT.$"

CeruleanCity_House2_Text_TeamRocketTryingToDigIntoNoGood::
	.string "¡EL EQUIPO ROCKET debe estar\n"
	.string "tratando de cavar algo malo!$"

CeruleanCity_House2_Text_TeamRocketLeftWayOut::
	.string "¡EL EQUIPO ROCKET dejó una salida!$"

