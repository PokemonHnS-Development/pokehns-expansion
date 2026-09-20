CeladonCity_Apartments_3F_hns_MapScripts::
	.byte 0

CeladonCity_Apartments_3F_EventScript_Sign::
	msgbox CeladonMansion3F_Text_DevRoomSign, MSGBOX_SIGN
	end

CeladonCity_Apartments_3F_EventScript_Programmer::
	msgbox GameFreak_Text_Programmer, MSGBOX_NPC
	end

CeladonCity_Apartments_3F_EventScript_GraphicArtist::
	msgbox GameFreak_Text_GraphicArtist, MSGBOX_NPC
	end

CeladonCity_Apartments_3F_EventScript_Program::
	msgbox CeladonMansion3F_Text_GameProgram, MSGBOX_SIGN
	end

CeladonCity_Apartments_3F_EventScript_Picture::
	msgbox CeladonMansion3F_Text_Drawing, MSGBOX_SIGN
	end

CeladonCity_Apartments_3F_EventScript_CharacterDesigner::
	msgbox GameFreak_Text_CharacterDesigner, MSGBOX_NPC
	end

GameFreak_Text_GameDesigner:
	.string "¿De verdad?\p"
	.string "¡Soy el DISEÑADOR!\p"
	.string "Llenar la POKéDEX es difícil,\n"
	.string "¡pero no te rindas!$"

GameFreak_Text_GameDesignerCompletedPokedex:
	.string "¡Guau! ¡Excelente! Completaste\n"
	.string "¡tu POKéDEX!\p"
	.string "¡Felicidades!$"

GameFreak_Text_GraphicArtist:
	.string "Soy el ARTISTA GRÁFICO.\p"
	.string "¡Yo te dibujé!$"

GameFreak_Text_GraphicArtistPrintDiploma:
	.string "Soy el ARTISTA GRÁFICO.\p"
	.string "¿Oh, completaste tu POKéDEX?\p"
	.string "¿Quieres que imprima tu\n"
	.string "DIPLOMA?$"

GameFreak_Text_GraphicArtistRefused:
	.string "Avísame si quieres tu\n"
	.string "DIPLOMA impreso.$"

GameFreak_Text_GraphicArtistError:
	.string "Algo va mal. Tendré que\n"
	.string "cancelar la impresión.$"

GameFreak_Text_Programmer:
	.string "¿Quién, yo? Soy el PROGRAMADOR.\p"
	.string "¡Juega en las tragaperras!$"

GameFreak_Text_CharacterDesigner:
	.string "¿No son adorables los GEMELOS?\p"
	.string "JASMINE también es linda.\p"
	.string "¡Oh, me encantan!$"

CeladonMansion3F_Text_DevRoomSign:
	.string "GAME FREAK DEVELOPMENT ROOM$"

CeladonMansion3F_Text_Drawing:
	.string "Es el dibujo detallado de una\n"
	.string "chica linda.$"

CeladonMansion3F_Text_GameProgram:
	.string "Es el programa del juego. Tocar\n"
	.string "con eso podría causar un error en el\n"
	.string "juego!$"

CeladonMansion3F_Text_ReferenceMaterial:
	.string "Está lleno de materiales de\n"
	.string "referencia. ¡Incluso hay un\n"
	.string "MUÑECO POKéMON!$"
