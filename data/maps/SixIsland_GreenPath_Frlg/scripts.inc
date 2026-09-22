SixIsland_GreenPath_Frlg_MapScripts::
	.byte 0

SixIsland_GreenPath_EventScript_RightRouteSign::
	msgbox SixIsland_GreenPath_Text_LeftRouteSign, MSGBOX_SIGN
	end

SixIsland_GreenPath_EventScript_LeftRouteSign::
	msgbox SixIsland_GreenPath_Text_RightRouteSign, MSGBOX_SIGN
	end

SixIsland_GreenPath_Text_JaclynIntro::
	.string "…¿Eh?\p"
	.string "Me imaginaba mi casa, pero\n"
	.string "¿aquí es donde TELETRANSPORTO?$"

SixIsland_GreenPath_Text_JaclynDefeat::
	.string "Big boo-boo!$"

SixIsland_GreenPath_Text_JaclynPostBattle::
	.string "I am so scatterbrained!\p"
	.string "Debo concentrarme para poder\n"
	.string "teletransportarme bien a mi casa!$"

SixIsland_GreenPath_Text_LeftRouteSign::
	.string "GREEN PATH\n"
	.string "PATTERN BUSH AHEAD$"

SixIsland_GreenPath_Text_RightRouteSign::
	.string "GREEN PATH\n"
	.string "Think Green, Keep Nature Clean!$"

