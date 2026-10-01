SaffronCity_CopycatsHouse_2F_Frlg_MapScripts::
	.byte 0

SaffronCity_CopycatsHouse_2F_EventScript_Doduo::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DODUO, CRY_MODE_NORMAL
	msgbox SaffronCity_CopycatsHouse_2F_Text_Doduo
	waitmoncry
	release
	end

SaffronCity_CopycatsHouse_2F_EventScript_Doll::
	lock
	msgbox SaffronCity_CopycatsHouse_2F_Text_RareMonOnlyDoll
	release
	end

SaffronCity_CopycatsHouse_2F_EventScript_Copycat::
	lock
	faceplayer
	checkitem ITEM_POKE_DOLL
	goto_if_eq VAR_RESULT, TRUE, EventScript_MimicTutor
	checkplayergender
	call_if_eq VAR_RESULT, MALE, SaffronCity_CopycatsHouse_2F_EventScript_MimicPlayerMale
	call_if_eq VAR_RESULT, FEMALE, SaffronCity_CopycatsHouse_2F_EventScript_MimicPlayerFemale
	release
	end

SaffronCity_CopycatsHouse_2F_EventScript_MimicPlayerMale::
	msgbox SaffronCity_CopycatsHouse_2F_Text_MimickingFavoriteHobbyMale
	return

SaffronCity_CopycatsHouse_2F_EventScript_MimicPlayerFemale::
	msgbox SaffronCity_CopycatsHouse_2F_Text_MimickingFavoriteHobbyFemale
	return

SaffronCity_CopycatsHouse_2F_EventScript_Computer::
	msgbox SaffronCity_CopycatsHouse_2F_Text_MySecrets, MSGBOX_SIGN
	end

SaffronCity_CopycatsHouse_2F_EventScript_Game::
	msgbox SaffronCity_CopycatsHouse_2F_Text_MarioWearingABucket, MSGBOX_SIGN
	end

SaffronCity_CopycatsHouse_2F_Text_MimickingFavoriteHobbyMale::
	.string "{PLAYER}: ¡Hola!\n"
	.string "¿Te gustan los POKéMON?\p"
	.string "{PLAYER}: Eh, no, solo te preguntaba.\p"
	.string "{PLAYER}: ¿Eh?\n"
	.string "¡Qué raro eres!\p"
	.string "IMITADORA: ¿Mmm? ¿Dejar de imitar?\n"
	.string "¡Pero ese es mi pasatiempo favorito!$"

SaffronCity_CopycatsHouse_2F_Text_MimickingFavoriteHobbyFemale::
	.string "{PLAYER}: Hola.\n"
	.string "Debes de querer a los POKéMON.\p"
	.string "{PLAYER}: No, yo no.\n"
	.string "Te pregunté a ti.\p"
	.string "{PLAYER}: ¿Perdón?\n"
	.string "¡Qué raro eres!\l"
	.string " \l"
	.string "IMITADORA: ¿Mmm? ¿Dejar de imitar?\l"
	.string "¡Pero si es mi pasatiempo favorito!$"

Text_MimicTeach::
	.string "¡Oh, vaya!\n"
	.string "¡Un POKé MUÑECO!\p"
	.string "¿Para mí?\n"
	.string "¡Gracias!\p"
	.string "¿Sabes qué?\n"
	.string "Puedo enseñarle MIMÉTICO.$"

Text_MimicDeclined::
	.string "¿No te gusta MIMÉTICO?$"

Text_MimicWhichMon::
	.string "¡Me encanta MIMÉTICO!\n"
	.string "¿Quién lo aprenderá?$"

Text_MimicTaughtMale::
	.string "{PLAYER}: ¡Hola!\n"
	.string "¡Gracias por lo de antes!\p"
	.string "{PLAYER}: ¿Perdón?\p"
	.string "{PLAYER}: ¿Es tan divertido imitar\n"
	.string "cada movimiento mío?\p"
	.string "IMITADORA: ¡Claro que sí!\n"
	.string "¡Es divertidísimo!$"

Text_MimicTaughtFemale::
	.string "{PLAYER}: ¡Hola!\n"
	.string "Gracias por lo que hiciste por mí.\p"
	.string "{PLAYER}: ¿Perdón?\p"
	.string "{PLAYER}: ¿De verdad es tan\n"
	.string "¿divertido copiarme?\p"
	.string "IMITADORA: ¡Claro que sí!\n"
	.string "¡Es divertidísimo!$"

SaffronCity_CopycatsHouse_2F_Text_Doduo::
	.string "DODUO: Giiih!\p"
	.string "ESPEJO HERMOSO MÍRAME,\n"
	.string "¿VES LO LINDA QUE SOY?$"

SaffronCity_CopycatsHouse_2F_Text_RareMonOnlyDoll::
	.string "¡Este es un POKéMON raro!\n"
	.string "¿Eh? ¡Es solo una muñeca!$"

SaffronCity_CopycatsHouse_2F_Text_MarioWearingABucket::
	.string "Un juego con MARIO con un balde\n"
	.string "en la cabeza!$"

SaffronCity_CopycatsHouse_2F_Text_MySecrets::
	.string "...\p"
	.string "Mis secretos!\p"
	.string "¡Habilidad: imitación!\n"
	.string "Afición: coleccionar muñecos!\l"
	.string "POKéMON favorito: ¡CLEFAIRY!$"

