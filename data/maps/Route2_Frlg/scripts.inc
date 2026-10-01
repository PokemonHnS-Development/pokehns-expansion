Route2_Frlg_MapScripts::
	.byte 0

Route2_EventScript_RouteSign::
	msgbox Route2_Text_RouteSign, MSGBOX_SIGN
	end

Route2_EventScript_DiglettsCaveSign::
	msgbox Route2_Text_DiglettsCave, MSGBOX_SIGN
	end

Route2_Text_RouteSign::
	.string "RUTA 2\n"
	.string "CIUDAD VERIDIAN - CIUDAD PLATEADA$"

Route2_Text_DiglettsCave::
	.string "CUEVA DIGLETT$"

