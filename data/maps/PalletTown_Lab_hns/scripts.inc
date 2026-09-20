PalletTown_Lab_hns_MapScripts::
	.byte 0

PalletTown_Lab_EventScript_Oak::
	lock
	faceplayer
	call_if_unset FLAG_SYS_NATIONAL_DEX, PalletTown_Lab_EventScript_OakGiveNatDex_ForPlaytesters
	goto_if_eq VAR_PALLETTOWN_LABSTATE, 1, PalletTown_Lab_EventScript_OakBadgeCheck
	goto_if_eq VAR_PALLETTOWN_LABSTATE, 2, PalletTown_Lab_EventScript_OakDex
	msgbox PalletTown_Lab_Text_OakWelcomeKanto, MSGBOX_DEFAULT
	msgbox PalletTown_Lab_Text_OakLabGoodbye, MSGBOX_DEFAULT
	setvar VAR_PALLETTOWN_LABSTATE, 1
	goto_if_ge VAR_NUM_BADGES, 16, PalletTown_Lab_EventScript_OakBadgeCheck
	closemessage
	release
	end

PalletTown_Lab_EventScript_OakGiveNatDex_ForPlaytesters::
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	return

PalletTown_Lab_EventScript_OakBadgeCheck::
	goto_if_ge VAR_NUM_BADGES, 16, PalletTown_Lab_EventScript_Oak16Badges
	goto_if_ge VAR_NUM_BADGES, 9, PalletTown_Lab_EventScript_Oak9Badges
	msgbox PalletTown_Lab_Text_OakNoKantoBadges, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_Lab_EventScript_Oak16Badges::
	msgbox PalletTown_Lab_Text_OakOpenMtSilver, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_INDIGOJUNCTION_HIDE_SILVER_GUARD
	setvar VAR_ROUTE28_SCIENTIST, 1
	setvar VAR_PALLETTOWN_LABSTATE, 2
	call_if_unset FLAG_IS_KANTO_CHAMPION, PalletTown_Lab_EventScript_OakKantoLeague
	release
	end

PalletTown_Lab_EventScript_OakKantoLeague::
	msgbox PalletTown_Lab_Text_OakOpenIndigoPlateau, MSGBOX_DEFAULT
	closemessage
	return

PalletTown_Lab_EventScript_Oak9Badges::
	msgbox PalletTown_Lab_Text_OakYesKantoBadges, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_Lab_EventScript_OakDex::
	msgbox PalletTown_Lab_Text_OakLabDexCheck, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_Lab_EventScript_Assistant1::
	msgbox PalletTown_Lab_Text_OaksAssistant1, MSGBOX_NPC
	end

PalletTown_Lab_EventScript_Assistant2::
	msgbox PalletTown_Lab_Text_OaksAssistant2, MSGBOX_NPC
	end

PalletTown_Lab_EventScript_Assistant3::
	msgbox PalletTown_Lab_Text_OaksAssistant3, MSGBOX_NPC
	end

PalletTown_Lab_EventScript_PC::
	msgbox PalletTown_Lab_Text_OaksLabPC, MSGBOX_SIGN
	end

PalletTown_Lab_Text_OakLabDexCheck:
	.string "How is your POKéDEX coming?$"

PalletTown_Lab_Text_OakWelcomeKanto:
	.string "OAK: ¡Ah, {PLAYER}!\n"
	.string "Es muy amable de tu parte venir\l"
	.string "hasta KANTO.\p"
	.string "¿Qué te parecen los entrenadores\n"
	.string "de aquí? Son fuertes, ¿eh?$"

PalletTown_Lab_Text_OakLabGoodbye:
	.string "Si estás por la zona, espero que\n"
	.string "vuelvas a visitarme.$"

PalletTown_Lab_Text_OakOpenMtSilver:
	.string "OAK: ¡Vaya! ¡Eso es excelente!\p"
	.string "Conseguiste las MEDALLAS de los\n"
	.string "GIMNASIOS de KANTO. ¡Bien hecho!\p"
	.string "Tenía razón en mi evaluación de\n"
	.string "vencerte.\p"
	.string "Escucha, {PLAYER}. Haré los\n"
	.string "arreglos necesarios para que\l"
	.string "vayas al MT.SILVER.\p"
	.string "El MT.SILVER es una montaña\n"
	.string "con muchos POKéMON salvajes.\p"
	.string "Es muy peligroso para un\n"
	.string "ENTRENADOR común, así que está\l"
	.string "prohibido. Pero haremos una\l"
	.string "excepción contigo, {PLAYER}.\p"
	.string "Ve a la MESETA AÑIL. Desde\n"
	.string "allí podrás llegar al MT.SILVER.$"

PalletTown_Lab_Text_OakOpenIndigoPlateau:
	.string "Ah, y hablando de la MESETA\n"
	.string "MESETA AÑIL, ahora que tienes\l"
	.string "16 medallas, la LIGA KANTO\l"
	.string "estará lista para aceptar\l"
	.string "tu desafío una vez más.\p"
	.string "Pero cuidado, LANCE y su\n"
	.string "ALTO MANDO no serán fáciles\l"
	.string "esta vez.\p"
	.string "¡Buena suerte, {PLAYER}!$"

PalletTown_Lab_Text_OakNoKantoBadges:
	.string "OAK: ¿Hmm? ¿No estás buscando\n"
	.string "las MEDALLAS de KANTO?\p"
	.string "Los LÍDERES de KANTO son tan\n"
	.string "fuertes como los de JOHTO.\p"
	.string "Te recomiendo que los desafíes.$"

PalletTown_Lab_Text_OakYesKantoBadges:
	.string "OAK: Ah, estás coleccionando las\n"
	.string "MEDALLAS de KANTO.\p"
	.string "Imagino que es difícil, pero la\n"
	.string "experiencia seguro te ayudará.\p"
	.string "Ven a verme cuando las tengas todas.\p"
	.string "Tendré un regalo para ti.\p"
	.string "¡Sigue esforzándote, {PLAYER}!$"

PalletTown_Lab_Text_OaksAssistant1:
	.string "El programa de radio POKéMON TALK\n"
	.string "del PROF. no se emite en KANTO.\p"
	.string "Es una pena, me gustaría oírlo.$"

PalletTown_Lab_Text_OaksAssistant2:
	.string "Gracias a tu trabajo con la POKéDEX,\n"
	.string "la investigación del PROF. avanza\l"
	.string "bien.$"

PalletTown_Lab_Text_OaksAssistant3:
	.string "No se lo digas a nadie, pero el\n"
	.string "POKéMON TALK no es en vivo.$"

PalletTown_Lab_Text_OaksLabPC:
	.string "Hay un correo en la PC.\p"
	.string "…\p"
	.string "PROF.OAK, ¿cómo va su investigación?\n"
	.string "las ISLAS ALOLA?\p"
	.string "Sigo trabajando duro en ella.\p"
	.string "Oí rumores de que {PLAYER} se\n"
	.string "está haciendo famoso.\p"
	.string "Me alegra mucho escuchar eso.\p"
	.string "ELM en PUEBLO PRIMAVERA 8-)$"
