SSTidalRooms_MapScripts::
	.byte 0

SSTidalRooms_EventScript_SnatchGiver::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM_SNATCH, SSTidalRooms_EventScript_ExplainSnatch
	msgbox SSTidalRooms_Text_NotSuspiciousTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM_SNATCH
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_SNATCH
	msgbox SSTidalRooms_Text_ExplainSnatch, MSGBOX_DEFAULT
	release
	end

SSTidalRooms_EventScript_ExplainSnatch::
	msgbox SSTidalRooms_Text_ExplainSnatch, MSGBOX_DEFAULT
	release
	end

SSTidalRooms_EventScript_Bed::
	lockall
	msgbox SSTidalRooms_Text_TakeRestOnBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	call SSTidalRooms_EventScript_ProgessCruiseAfterBed
	releaseall
	end

SSTidalRooms_EventScript_Colton::
	trainerbattle_single TRAINER_COLTON, SSTidalRooms_Text_ColtonIntro, SSTidalRooms_Text_ColtonDefeat
	msgbox SSTidalRooms_Text_ColtonPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Micah::
	trainerbattle_single TRAINER_MICAH, SSTidalRooms_Text_MicahIntro, SSTidalRooms_Text_MicahDefeat
	msgbox SSTidalRooms_Text_MicahPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Thomas::
	trainerbattle_single TRAINER_THOMAS, SSTidalRooms_Text_ThomasIntro, SSTidalRooms_Text_ThomasDefeat
	msgbox SSTidalRooms_Text_ThomasPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Jed::
	trainerbattle_double TRAINER_LEA_AND_JED, SSTidalRooms_Text_JedIntro, SSTidalRooms_Text_JedDefeat, SSTidalRooms_Text_JedNotEnoughMons
	msgbox SSTidalRooms_Text_JedPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Lea::
	trainerbattle_double TRAINER_LEA_AND_JED, SSTidalRooms_Text_LeaIntro, SSTidalRooms_Text_LeaDefeat, SSTidalRooms_Text_LeaNotEnoughMons
	msgbox SSTidalRooms_Text_LeaPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Garret::
	trainerbattle_single TRAINER_GARRET, SSTidalRooms_Text_GarretIntro, SSTidalRooms_Text_GarretDefeat
	msgbox SSTidalRooms_Text_GarretPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Naomi::
	trainerbattle_single TRAINER_NAOMI, SSTidalRooms_Text_NaomiIntro, SSTidalRooms_Text_NaomiDefeat
	msgbox SSTidalRooms_Text_NaomiPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_Text_TakeRestOnBed:
	.string "Hay una cama…\n"
	.string "Descansemos un poco.$"

SSTidalRooms_Text_ColtonIntro:
	.string "Suelo navegar hacia CIUDAD FONDOMAR.\p"
	.string "Me gusta asistir a los CONCURSOS,\n"
	.string "ya ves.$"

SSTidalRooms_Text_ColtonDefeat:
	.string "¡Fue un combate muy divertido!$"

SSTidalRooms_Text_ColtonPostBattle:
	.string "Me emociona imaginar qué tipos\n"
	.string "de POKéMON veré en el próximo\l"
	.string "CONCURSO. ¡La espera es emocionante!$"

SSTidalRooms_Text_MicahIntro:
	.string "¿Tus amigos son fuertes?$"

SSTidalRooms_Text_MicahDefeat:
	.string "Tus amigos sí que son fuertes.$"

SSTidalRooms_Text_MicahPostBattle:
	.string "Los amigos no tienen que ser humanos.\n"
	.string "¡Para mí, los POKéMON son tesoros!$"

SSTidalRooms_Text_ThomasIntro:
	.string "Niño...\n"
	.string "¿Tocaste a la puerta?$"

SSTidalRooms_Text_ThomasDefeat:
	.string "Una derrota se acepta sin prisas\n"
	.string "ni pánico.$"

SSTidalRooms_Text_ThomasPostBattle:
	.string "No alterarse en ninguna situación es\n"
	.string "el código del GENTLEMAN.$"

SSTidalRooms_Text_JedIntro:
	.string "JED: Me da un poco de pena, pero...\n"
	.string "¡Te mostraremos nuestro poder amoroso!$"

SSTidalRooms_Text_JedDefeat:
	.string "JED: Sigh…$"

SSTidalRooms_Text_JedPostBattle:
	.string "JED: ¡Es la primera vez que nuestro\n"
	.string "poder amoroso no prevalece!\l"
	.string "¡Debes ser un gran ENTRENADOR!$"

SSTidalRooms_Text_JedNotEnoughMons:
	.string "JED: ¿Solo tienes un POKéMON?\n"
	.string "¿No es eso demasiado solitario?$"

SSTidalRooms_Text_LeaIntro:
	.string "LEA: Me siento un poco tonta, pero…\n"
	.string "¡Te mostraremos nuestro poder amoroso!$"

SSTidalRooms_Text_LeaDefeat:
	.string "LEA: Oh, boo!$"

SSTidalRooms_Text_LeaPostBattle:
	.string "LEA: ¡No puedo creerlo!\n"
	.string "Nuestro poder del amor falló…\l"
	.string "¡Debes ser un gran ENTRENADOR!$"

SSTidalRooms_Text_LeaNotEnoughMons:
	.string "LEA: Quería luchar…\n"
	.string "Pero ni siquiera tienes dos POKéMON…$"

SSTidalRooms_Text_GarretIntro:
	.string "Ah, llegaste justo a tiempo.\p"
	.string "Estoy aburrida, ya ves.\n"
	.string "Puedes entretenerme.$"

SSTidalRooms_Text_GarretDefeat:
	.string "…Con eso basta.$"

SSTidalRooms_Text_GarretPostBattle:
	.string "Tal vez haga que mi padre consiga\n"
	.string "un yate para mí.\l"
	.string "¡Un yate para mí y mis POKéMON!$"

SSTidalRooms_Text_NaomiIntro:
	.string "Oh, eres un ENTRENADOR adorable.\n"
	.string "¿Te gustaría tomar el té?\l"
	.string "¿O prefieres luchar?$"

SSTidalRooms_Text_NaomiDefeat:
	.string "Ya veo.\n"
	.string "Eres del tipo activo.$"

SSTidalRooms_Text_NaomiPostBattle:
	.string "Un crucero mundial en un barco de lujo\n"
	.string "tiene su encanto, debo decir...\p"
	.string "Pero admito que tiene su atractivo\n"
	.string "recorrer HOENN en ferry.$"

SSTidalRooms_Text_NotSuspiciousTakeThis:
	.string "¡Eh... Hola! ¡No actúo raro!\n"
	.string "¡Eh... ¡Toma esto! ¡Es gratis!\p"
	.string "Es que... ¡Sinceramente, no se lo\n"
	.string "ROBÉ a nadie! ¡Jamás haría eso!\l"
	.string "¡Está limpio! ¡Puedes usarlo!$"

SSTidalRooms_Text_ExplainSnatch:
	.string "ROBO quita los efectos positivos\n"
	.string "de ciertos movimientos antes de que\l"
	.string "un aliado o rival los use.$"

