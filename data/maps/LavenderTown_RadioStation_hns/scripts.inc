LavenderTown_RadioStation_hns_MapScripts::
	.byte 0

LavenderTown_RadioStation_EventScript_Officer::
	msgbox LavenderTown_RadioStation_Text_Officer, MSGBOX_NPC
	end

LavenderTown_RadioStation_EventScript_Receptionist::
	msgbox LavenderTown_RadioStation_Text_Receptionist, MSGBOX_NPC
	end

LavenderTown_RadioStation_EventScript_SuperNerd::
	msgbox LavenderTown_RadioStation_Text_SuperNerd1, MSGBOX_NPC
	end

LavenderTown_RadioStation_EventScript_Director::
	lock
	faceplayer
	goto_if_set FLAG_KANTO_RADIO_GOT, LavenderTown_RadioStation_EventScript_DirectorGotRadio
	goto_if_set FLAG_RETURNED_MACHINE_PART, LavenderTown_RadioStation_EventScript_DirectorReturnedMachinePart
	msgbox LavenderTown_RadioStation_Text_Gentleman, MSGBOX_NPC
	end
LavenderTown_RadioStation_EventScript_DirectorReturnedMachinePart::
	msgbox LavenderTown_RadioStation_Text_Gentleman_ReturnedMachinePart, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	msgbox LavendertownRadioStation_Text_Upgraded_Radio, MSGBOX_DEFAULT
	waitfanfare
	msgbox LavenderTown_RadioStation_Text_Gentleman_GotExpnCard, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_KANTO_RADIO_GOT
	release
	end
LavenderTown_RadioStation_EventScript_DirectorGotRadio::	
	msgbox LavenderTown_RadioStation_Text_Gentleman_GotExpnCard, MSGBOX_NPC
	end

LavenderTown_RadioStation_EventScript_Host::
	goto_if_set FLAG_KANTO_RADIO_GOT, LavenderTown_RadioStation_EventScript_Host2
	msgbox LavenderTown_RadioStation_Text_SuperNerd2, MSGBOX_NPC
	end
LavenderTown_RadioStation_EventScript_Host2::
	msgbox LavenderTown_RadioStation_Text_SuperNerd2_GotExpnCard, MSGBOX_NPC
	end

LavenderTown_RadioStation_EventScript_Directory::
	msgbox LavenderTown_RadioStation_Text_Directory, MSGBOX_SIGN
	end
LavenderTown_RadioStation_EventScript_Sign::
	msgbox LavenderTown_RadioStation_Text_PokeFluteSign, MSGBOX_SIGN
	end
LavenderTown_RadioStation_EventScript_Library::
	msgbox LavenderTown_RadioStation_Text_ReferenceLibrary, MSGBOX_SIGN
	end

LavenderTown_RadioStation_Text_Receptionist:
	.string "¡Bienvenido! Siéntete libre de\n"
	.string "mirar por todo este piso.$"

LavenderTown_RadioStation_Text_Officer:
	.string "Lo siento, pero solo puedes\n"
	.string "recorrer la planta baja.\p"
	.string "Desde que la RADIO TOWER de\n"
	.string "JOHTO fue tomada por criminales,\l"
	.string "hemos tenido que reforzar la\l"
	.string "seguridad.$"

LavenderTown_RadioStation_Text_SuperNerd1:
	.string "Mucha gente trabaja duro aquí\n"
	.string "en la RADIO TOWER.\p"
	.string "Deben estar dando lo mejor de sí\n"
	.string "para dar buenos shows.$"

LavenderTown_RadioStation_Text_Gentleman:
	.string "¡Oh, no, no, no!\p"
	.string "Hemos estado fuera del aire desde\n"
	.string "que cerró la CENTRAL ELÉCTRICA.\p"
	.string "Todo mi esfuerzo por iniciar esta\n"
	.string "estación sería en vano si no puedo\l"
	.string "transmitir.\p"
	.string "¡Estaré arruinado!$"

LavenderTown_RadioStation_Text_Gentleman_ReturnedMachinePart:
	.string "¡Ah! ¿Así que tú eres {PLAYER}, quien\n"
	.string "resolvió lo de la CENTRAL ELÉCTRICA?\p"
	.string "Gracias a ti, no perdí mi\n"
	.string "empleo.\p"
	.string "¡Te lo digo, eres un verdadero\n"
	.string "salvavidas!\p"
	.string "Toma esto como mi agradecimiento.$"

LavendertownRadioStation_Text_Upgraded_Radio:
	.string "{PLAYER} recibió la\n"
	.string "¡MEJORA DE RADIO!$"

LavenderTown_RadioStation_Text_Gentleman_GotExpnCard:
	.string "Con eso podrás sintonizar los\n"
	.string "programas de radio de KANTO.\p"
	.string "¡Gajajajaja!$"

LavenderTown_RadioStation_Text_SuperNerd2:
	.string "¡Hola!\p"
	.string "¡Soy el súper DIRECTOR MUSICAL!\p"
	.string "¡¿Eh?! Tu RADIO no sintoniza\n" @POKéGEAR
	.string "mi música. ¡Qué mala suerte!\p"
	.string "Si consigues la MEJORA DE RADIO,\n"
	.string "podrás oírme. Mejor consíguela\l"
	.string "¡uno!$"

LavenderTown_RadioStation_Text_SuperNerd2_GotExpnCard:
	.string "¡Hola!\p"
	.string "¡Soy el súper DIRECTOR MUSICAL!\p"
	.string "Soy responsable de las bellas\n"
	.string "melodías que salen al aire.\p"
	.string "No seas aburrido. ¡Sintoniza tu\n"
	.string "música ahora!$"

LavenderTown_RadioStation_Text_Directory:
	.string "1F RECEPCIÓN 2F VENTAS\p"
	.string "3F PERSONAL 4F PRODUCCIÓN\p"
	.string "OFICINA DIRECTOR 5F$"

LavenderTown_RadioStation_Text_PokeFluteSign:
	.string "Anima a tu POKéMON con los\n"
	.string "sonidos de la POKé FLUTE en el\l"
	.string "CANAL 20$"

LavenderTown_RadioStation_Text_ReferenceLibrary:
	.string "¡Vaya! Un estante lleno de CDs y\n"
	.string "videos de POKéMON.\p"
	.string "Esta debe ser la biblioteca\n"
	.string "de referencia.$"

