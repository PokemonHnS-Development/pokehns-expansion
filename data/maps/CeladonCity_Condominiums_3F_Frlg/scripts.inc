CeladonCity_Condominiums_3F_Frlg_MapScripts::
	.byte 0

CeladonCity_Condominiums_3F_EventScript_Programmer::
	msgbox CeladonCity_Condominiums_3F_Text_ImTheProgrammer, MSGBOX_NPC
	end

CeladonCity_Condominiums_3F_EventScript_GraphicArtist::
	msgbox CeladonCity_Condominiums_3F_Text_ImTheGraphicArtist, MSGBOX_NPC
	end

CeladonCity_Condominiums_3F_EventScript_Writer::
	msgbox CeladonCity_Condominiums_3F_Text_IWroteTheStory, MSGBOX_NPC
	end

CeladonCity_Condominiums_3F_EventScript_Designer::
	lock
	faceplayer
	specialvar VAR_RESULT, HasAllKantoMons
	goto_if_eq VAR_RESULT, TRUE, CeladonCity_Condominiums_3F_EventScript_CompletedPokedex
	msgbox CeladonCity_Condominiums_3F_Text_ImGameDesignerShowMeFinishedPokedex
	release
	end

CeladonCity_Condominiums_3F_EventScript_CompletedPokedex::
	goto CeladonCity_Condominiums_3F_EventScript_ShowDiploma
	end

CeladonCity_Condominiums_3F_EventScript_ShowDiploma::
	message CeladonCity_Condominiums_3F_Text_CompletedPokedexCongratulations
	waitmessage
	delay 60
	special Special_ShowDiploma
	waitstate
	release
	end

CeladonCity_Condominiums_3F_EventScript_DevelopmentRoomSign::
	msgbox CeladonCity_Condominiums_3F_Text_GameFreakDevelopmentRoom, MSGBOX_SIGN
	end

CeladonCity_Condominiums_3F_EventScript_Computer1::
	msgbox CeladonCity_Condominiums_3F_Text_ItsTheGameProgram, MSGBOX_SIGN
	end

CeladonCity_Condominiums_3F_EventScript_Computer2::
	msgbox CeladonCity_Condominiums_3F_Text_SomeonesPlayingGame, MSGBOX_SIGN
	end

CeladonCity_Condominiums_3F_EventScript_Computer3::
	msgbox CeladonCity_Condominiums_3F_Text_ItsScriptBetterNotLookAtEnding, MSGBOX_SIGN
	end

CeladonCity_Condominiums_3F_Text_ImTheProgrammer::
	.string "¿Yo?\n"
	.string "¡Soy el programador!$"

CeladonCity_Condominiums_3F_Text_ImTheGraphicArtist::
	.string "¡Soy el artista gráfico!\n"
	.string "¡Yo te dibujé!$"

CeladonCity_Condominiums_3F_Text_IWroteTheStory::
	.string "¡Escribí la historia!\n"
	.string "Isn't ERIKA cute?\p"
	.string "¡Misty también me cae muy bien!\n"
	.string "Oh, y SABRINA, ¡me gusta!$"

CeladonCity_Condominiums_3F_Text_ImGameDesignerShowMeFinishedPokedex::
	.string "¿De verdad?\p"
	.string "¡Soy el diseñador del juego!\p"
	.string "Llenar la POKéDEX es difícil,\n"
	.string "but don't quit!\p"
	.string "Cuando termines, ven a decírmelo!$"

CeladonCity_Condominiums_3F_Text_CompletedPokedexCongratulations::
	.string "Wow! Excellent!\n"
	.string "You completed your POKéDEX!\l"
	.string "¡Felicidades!\l"
	.string "...$"

CeladonCity_Condominiums_3F_Text_ItsTheGameProgram::
	.string "¡Es el programa del juego! Manipulando\n"
	.string "¡podría dañar el juego!"

CeladonCity_Condominiums_3F_Text_SomeonesPlayingGame::
	.string "Alguien está jugando un juego en lugar de\n"
	.string "working!$"

CeladonCity_Condominiums_3F_Text_ItsScriptBetterNotLookAtEnding::
	.string "¡Es el guion!\n"
	.string "Mejor no mires el final!$"

CeladonCity_Condominiums_3F_Text_GameFreakDevelopmentRoom::
	.string "GAME FREAK Development Room$"

