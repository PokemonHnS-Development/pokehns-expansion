Gate_SaffronCity_Route6_hns_MapScripts::
	.byte 0

Gate_SaffronCity_Route6_EventScript_Guard::
	goto_if_eq VAR_TEMP_0, 1, Gate_SaffronCity_Route6_EventScript_Guard2
	msgbox Route6_Text_SaffronGuardWelcome, MSGBOX_NPC
	setvar VAR_TEMP_0, 1
	end
Gate_SaffronCity_Route6_EventScript_Guard2::
	msgbox Route6_Text_SaffronGuardMagnetTrain, MSGBOX_NPC
	end

Route6_Text_SaffronGuardWelcome:
	.string "Bienvenido a CIUDAD AZAFRÁN, hogar\n"
	.string "¡del TREN MAGNÉTICO!\p"
	.string "...Eso es lo que diría normalmente,\n"
	.string "pero el TREN MAGNÉTICO no está\l"
	.string "funcionando ahora.\p"
	.string "No está recibiendo electricidad\n"
	.string "porque algo anda mal con la\l"
	.string "CENTRAL ELÉCTRICA.$"

Route6_Text_SaffronGuardMagnetTrain:
	.string "El TREN MAGNÉTICO es lo más\n"
	.string "famoso de CIUDAD AZAFRÁN.$"
