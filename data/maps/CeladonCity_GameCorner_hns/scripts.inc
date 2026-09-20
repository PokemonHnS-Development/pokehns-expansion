CeladonCity_GameCorner_hns_MapScripts::
	.byte 0

CeladonGameCorner_EventScript_PokefanM::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_PokefanM, MSGBOX_NPC
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceLeft
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_Teacher::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_Teacher, MSGBOX_NPC
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceRight
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_FishingGuru::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_FishingGuru, MSGBOX_NPC
	closemessage
	release
	end

CeladonGameCorner_EventScript_Fisher1::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_Fisher1, MSGBOX_NPC
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceLeft
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_Fisher2::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_Fisher2, MSGBOX_NPC
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceLeft
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_GymGuide::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_GymGuide, MSGBOX_NPC
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceRight
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_Gramps::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_Gramps, MSGBOX_NPC
	closemessage
	release
	end

CeladonGameCorner_EventScript_PokefanF::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_PokefanF, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceRight
	waitmovement 0
	release
	end

CeladonGameCorner_EventScript_Woman::
	lock
	faceplayer
	msgbox CeladonGameCorner_Text_Woman, MSGBOX_DEFAULT
	closemessage
	release
	end

CeladonGameCorner_Text_PokefanM:
	.string "Las máquinas tragamonedas son lo\n"
	.string "último en tecnología.$"

CeladonGameCorner_Text_Teacher:
	.string "Quiero usar esta máquina.\p"
	.string "Ayer me dejó sin nada, así que\n"
	.string "hoy debería dar el premio.$"

CeladonGameCorner_Text_FishingGuru:
	.string "Creo que esta máquina me dará\n"
	.string "el premio...\p"
	.string "Las probabilidades varían.$"

CeladonGameCorner_Text_Fisher1:
	.string "¡Gajajaja!\p"
	.string "¡Las monedas no dejan de llegar!\p"
	.string "¿Eh? ¿Qué, niño? ¿Quieres jugar?\p"
	.string "¡Compartiré mi suerte contigo!$"

CeladonGameCorner_Text_Fisher2:
	.string "¡Gajajaja!\p"
	.string "Me hace sentir bien hacer cosas\n"
	.string "buenas por los demás!$"

CeladonGameCorner_Text_GymGuide:
	.string "¡Hola! ¡Futuro CAMPEÓN!\p"
	.string "¿Tú también juegas a las tragamonedas?\p"
	.string "Intento conseguir monedas para\n"
	.string "un POKéMON de premio.\p"
	.string "Pero aún no tengo suficientes...$"

CeladonGameCorner_Text_PokefanF:
	.string "La ruleta...\p"
	.string "La prefiero a las tragamonedas\n"
	.string "porque es más fácil calcularla.\p"
	.string "Pero el premio es mucho menor.$"

CeladonGameCorner_Text_Gramps:
	.string "Hmmm... Las probabilidades son\n"
	.string "mejor apostarlo todo al azul,\l"
	.string "pero... ¿qué hacer?$"

CeladonGameCorner_Text_Woman:
	.string "I can't stop winning!$"
