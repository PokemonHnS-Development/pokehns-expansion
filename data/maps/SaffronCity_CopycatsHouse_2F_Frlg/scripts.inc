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
	.string "{PLAYER}: Hi!\n"
	.string "Do you like POKéMON?\p"
	.string "{PLAYER}: Eh, no, solo te preguntaba.\p"
	.string "{PLAYER}: Huh?\n"
	.string "¡Qué raro eres!\p"
	.string "COPYCAT: Hmm? Quit mimicking?\n"
	.string "¡Pero ese es mi pasatiempo favorito!$"

SaffronCity_CopycatsHouse_2F_Text_MimickingFavoriteHobbyFemale::
	.string "{PLAYER}: Hi.\n"
	.string "You must like POKéMON.\p"
	.string "{PLAYER}: No, yo no.\n"
	.string "Te pregunté a ti.\p"
	.string "{PLAYER}: Pardon?\n"
	.string "¡Qué raro eres!\l"
	.string " \l"
	.string "COPYCAT: Hmm? Quit mimicking?\l"
	.string "¡Pero si es mi pasatiempo favorito!$"

Text_MimicTeach::
	.string "Oh wow!\n"
	.string "A POKé DOLL!\p"
	.string "¿Para mí?\n"
	.string "¡Gracias!\p"
	.string "¿Sabes qué?\n"
	.string "I can teach the move MIMIC.$"

Text_MimicDeclined::
	.string "¿No te gusta MIMÉTICO?$"

Text_MimicWhichMon::
	.string "I really love MIMIC!\n"
	.string "¿Quién lo aprenderá?$"

Text_MimicTaughtMale::
	.string "{PLAYER}: Hi!\n"
	.string "¡Gracias por lo de antes!\p"
	.string "{PLAYER}: ¿Perdón?\p"
	.string "{PLAYER}: ¿Es tan divertido imitar\nmi forma de hablar?"
	.string "every move?\p"
	.string "IMITADOR: ¡Claro que sí!\n"
	.string "¡Es divertidísimo!$"

Text_MimicTaughtFemale::
	.string "{PLAYER}: Hi!\n"
	.string "Thanks for what you did for us.\p"
	.string "{PLAYER}: ¿Perdón?\p"
	.string "{PLAYER}: ¿De verdad es tan\n"
	.string "copy what I say and do?\p"
	.string "IMITADOR: ¡Claro que sí!\n"
	.string "¡Es divertidísimo!$"

SaffronCity_CopycatsHouse_2F_Text_Doduo::
	.string "DODUO: Giiih!\p"
	.string "ESPEJO HERMOSO MÍRAME,\n"
	.string "¿VES LO LINDA QUE SOY?$"

SaffronCity_CopycatsHouse_2F_Text_RareMonOnlyDoll::
	.string "This is a rare POKéMON!\n"
	.string "¿Eh? ¡Es solo una muñeca!$"

SaffronCity_CopycatsHouse_2F_Text_MarioWearingABucket::
	.string "Un juego con MARIO con un balde\n"
	.string "en la cabeza!$"

SaffronCity_CopycatsHouse_2F_Text_MySecrets::
	.string "...\p"
	.string "Mis secretos!\p"
	.string "Skill: Mimicry!\n"
	.string "Hobby: Collecting dolls!\l"
	.string "Favorite POKéMON: CLEFAIRY!$"

