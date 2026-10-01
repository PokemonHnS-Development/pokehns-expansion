CliffEdgeCave_hns_MapScripts::
	.byte 0

CliffEdgeCave_EventScript_BaldMan::
	lock
	faceplayer
	msgbox CliffEdgeCave_Text_Baldman, MSGBOX_DEFAULT
	closemessage
	release
	end

CliffEdgeCave_Text_Baldman:
	.string "Si ves un camino que se divide\n"
	.string "dentro de una cueva, lo más probable\l"
	.string "es que una vía sea la correcta y la\l"
	.string "otra lleve a un callejón sin salida.\p"
	.string "Pero todos quieren probar ambos.$"
