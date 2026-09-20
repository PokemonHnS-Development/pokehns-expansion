BlackthornCity_House1_hns_MapScripts::
	.byte 0

BlackthornCity_House1EventScript_Granny::
	msgbox BlackthornCity_House1_Text_Granny, MSGBOX_NPC
	end

BlackthornCity_House1EventScript_Dratini::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DRATINI, CRY_MODE_NORMAL
	msgbox BlackthornCity_House1_Text_Dratini, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BlackthornCity_House1_Text_Granny:
	.string "Un clan de ENTRENADORES que pueden\n"
	.string "mandar dragones vive aquí mismo,\l"
	.string "en CIUDAD ENDRINO.\p"
	.string "Por eso, hay muchas leyendas\n"
	.string "sobre dragones en este pueblo.$"

BlackthornCity_House1_Text_Dratini:
	.string "DRATINI: Draa!$"
