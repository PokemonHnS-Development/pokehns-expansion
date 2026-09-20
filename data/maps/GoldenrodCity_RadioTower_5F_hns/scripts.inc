GoldenrodCity_RadioTower_5F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GoldenrodCity_RadioTower_5F_OnLoad
	.byte 0

GoldenrodCity_RadioTower_5F_OnLoad::
	call_if_eq VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_RadioTower_5F_MapScript_HidePetrel
	end

GoldenrodCity_RadioTower_5F_MapScript_HidePetrel::
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	return


@=======[OFFICE]==============================================================================================================================

GoldenrodCity_RadioTower_5F_EventScript_Petrel::
	lock
	goto_if_ge VAR_GOLDENROD_CITY_STATE, 10, GoldenrodCity_RadioTower_5F_EventScript_Director
	goto_if_eq VAR_FACING, DIR_SOUTH, GoldenrodCity_RadioTower_5F_EventScript_PetrelNorth
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirector1, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DIRECTOR_OFFICE, GoldenrodCity_RadioTower_5F_Movement_Spin
	waitmovement 0
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	removeobject LOCALID_DIRECTOR_OFFICE
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	addobject LOCALID_PETREL_OFFICE
	applymovement LOCALID_PETREL_OFFICE, GoldenrodCity_RadioTower_5F_Movement_Spin2
	waitmovement 0
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirector2, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_PETREL_2_HNS, GoldenrodCity_RadioTower_5F_Text_FakeDirectorWin
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter, MSGBOX_DEFAULT
	giveitem ITEM_BASEMENT_KEY
	setvar VAR_GOLDENROD_CITY_STATE, 7
	clearflag FLAG_HIDE_GOLDENROD_UNDERGROUND_KIMONO
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_PetrelNorth::
	end

GoldenrodCity_RadioTower_5F_EventScript_Petrel2::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_Director::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_5F_Movement_Spin:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_4
	face_up
	delay_4
	face_left
	delay_4
	face_down
	delay_4
	face_right
	delay_2
	face_up
	delay_2
	face_left
	delay_2
	face_down
	step_end


GoldenrodCity_RadioTower_5F_Movement_Spin2:
	face_right
	delay_2
	face_up
	delay_2
	face_left
	delay_2
	face_down
	step_end


GoldenrodCity_RadioTower_5F_Text_FakeDirector1:
	.string "¡¿T-tú?! ¿Viniste a rescatarme?$"

GoldenrodCity_RadioTower_5F_Text_FakeDirector2:
	.string "¿Eso es lo que esperabas?\p"
	.string "¡Error! ¡Soy un impostor!\p"
	.string "Fingí ser el verdadero para\n"
	.string "preparar nuestra toma de control.\p"
	.string "¿Quieres saber dónde escondimos\n"
	.string "al DIRECTOR real?\p"
	.string "Claro, te lo diré. ¡Pero solo si\n"
	.string "puedes vencerme!$"

GoldenrodCity_RadioTower_5F_Text_FakeDirectorWin:
	.string "Está bien. Te diré dónde está.$"

GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter:
	.string "El jefe guardó al DIRECTOR en el\n"
	.string "ALMACÉN SUBTERRÁNEO.\p"
	.string "Está al final del SUBTERRÁ-\n"
	.string "NEO.\p"
	.string "Soy un buen tipo, te daré la\n"
	.string "LLAVE DEL SÓTANO para ir al\l"
	.string "ALMACÉN SUBTERRÁNEO.\p"
	.string "Pero dudo que llegues tan lejos.$"

GoldenrodCity_RadioTower_5F_Text_FakeDirectorAfter2:
	.string "El jefe guardó al DIRECTOR en el\n"
	.string "ALMACÉN SUBTERRÁNEO.\p"
	.string "Está al final del SUBTERRÁ-\n"
	.string "NEO.\p"
	.string "Usa la LLAVE DEL SÓTANO para ir\n"
	.string "al ALMACÉN SUBTERRÁNEO.\p"
	.string "Pero dudo que llegues tan lejos.$"

@=======[STUDIO]==============================================================================================================================

GoldenrodCity_RadioTower_5F_EventScript_Ben::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_Ben, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodRaidoTower4_EventScript_ARIANA::
	trainerbattle_single TRAINER_ARIANA_2_HNS GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Seen, GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Beaten
	msgbox GoldenrodCity_RadioTower_5F_Text_ExecutiveF1After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_RadioTower_5F_EventScript_Archer::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_5F_Text_RocketBossSeen, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ARCHER_HNS, GoldenrodCity_RadioTower_5F_Text_RocketBossBeaten
	msgbox GoldenrodCity_RadioTower_5F_Text_RocketBossAfter, MSGBOX_DEFAULT
	delay 55
	closemessage
	fadescreen FADE_TO_BLACK
	setflag FLAG_HIDE_GOLDENROD_ROCKETS
	playse SE_EXIT
	setvar VAR_GOLDENROD_CITY_STATE, 10
	removeobject LOCALID_GOLDENROD_ARCHER
	removeobject LOCALID_GOLDENROD_ARIANA
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	removeobject LOCALID_PETREL_OFFICE
	addobject LOCALID_DIRECTOR_STUDIO
	playbgm MUS_HG_GOLDENROD, TRUE
	delay 120
	fadescreen FADE_FROM_BLACK
	goto_if_eq VAR_FACING, DIR_SOUTH, GoldenrodCity_RadioTower_5F_EventScript_WingTop
	goto_if_eq VAR_FACING, DIR_WEST, GoldenrodCity_RadioTower_5F_EventScript_WingMid
	goto_if_eq VAR_FACING, DIR_NORTH, GoldenrodCity_RadioTower_5F_EventScript_WingBot
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_WingTop::
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerTop
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorThanks, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_LUGIA_OR_HOOH, 1,  GoldenrodCity_RadioTower_5F_EventScript_GiveTidalWing
	call_if_eq VAR_LUGIA_OR_HOOH, 2, GoldenrodCity_RadioTower_5F_EventScript_GiveClearWing
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_LeaveTop
	waitmovement 0
	goto GoldenrodCity_RadioTower_5F_Fakeout
	end

GoldenrodCity_RadioTower_5F_EventScript_WingMid::
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerMid
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorThanks, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_LUGIA_OR_HOOH, 1,  GoldenrodCity_RadioTower_5F_EventScript_GiveTidalWing
	call_if_eq VAR_LUGIA_OR_HOOH, 2, GoldenrodCity_RadioTower_5F_EventScript_GiveClearWing
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_LeaveMid
	waitmovement 0
	goto GoldenrodCity_RadioTower_5F_Fakeout
	end

GoldenrodCity_RadioTower_5F_EventScript_WingBot::
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerBot
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorThanks, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_LUGIA_OR_HOOH, 1,  GoldenrodCity_RadioTower_5F_EventScript_GiveTidalWing
	call_if_eq VAR_LUGIA_OR_HOOH, 2, GoldenrodCity_RadioTower_5F_EventScript_GiveClearWing
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_LeaveBot
	waitmovement 0
	goto GoldenrodCity_RadioTower_5F_Fakeout
	end

GoldenrodCity_RadioTower_5F_EventScript_GiveTidalWing::
	giveitem ITEM_SILVER_WING
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorTidalWingExplanation, MSGBOX_DEFAULT
	closemessage
	release
	return

GoldenrodCity_RadioTower_5F_EventScript_GiveClearWing::
	giveitem ITEM_RAINBOW_WING
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorClearWingExplanation, MSGBOX_DEFAULT
	closemessage
	release
	return

GoldenrodCity_RadioTower_5F_Fakeout::
	playse SE_PIN
	applymovement LOCALID_DIRECTOR_STUDIO, Common_Movement_ExclamationMark
	delay 60
	turnobject LOCALID_DIRECTOR_STUDIO, DIR_WEST
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorLegendary, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_Leave1
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_DIRECTOR_STUDIO, Common_Movement_ExclamationMark
	delay 60
	turnobject LOCALID_DIRECTOR_STUDIO, DIR_SOUTH
	msgbox GoldenrodCity_RadioTower_5F_Text_DirectorFakeout, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DIRECTOR_STUDIO, GoldenrodCity_RadioTower_5F_Movement_Leave2
	waitmovement 0
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR_2
	removeobject LOCALID_DIRECTOR_STUDIO
	setvar VAR_MAHOGANY_TOWN_STATE, 17
	release
	end

GoldenrodCity_RadioTower_5F_EventScript_Trigger_NPCS::
	clearflag FLAG_HIDE_GOLDENROD_NPCS
	setvar VAR_GOLDENROD_CITY_STATE, 11
	end

GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerTop:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_RadioTower_5F_Movement_LeaveTop:
	walk_right
	walk_right
	walk_right
	step_end

GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerMid:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	step_end


GoldenrodCity_RadioTower_5F_Movement_LeaveMid:
	walk_right
	walk_right
	step_end

GoldenrodCity_RadioTower_5F_Movement_WalkToPlayerBot:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	step_end

GoldenrodCity_RadioTower_5F_Movement_LeaveBot:
	walk_right
	walk_right
	walk_right
	step_end

GoldenrodCity_RadioTower_5F_Movement_Leave1:
	walk_up
	walk_up
	step_end

GoldenrodCity_RadioTower_5F_Movement_Leave2:
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Seen:
	.string "¿Me recuerdas de la GUARIDA en\n"
	.string "PUEBLO CAOBA?\p"
	.string "Mi jefe me regañó, pero soy fuerte.\p"
	.string "Perdí entonces, ¡pero ahora no!$"

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1Beaten:
	.string "¡Esto no puede estar pasando!\p"
	.string "Luché duro, pero perdí...\p"
	.string "Lo siento mucho, GIOVANNI...$"

GoldenrodCity_RadioTower_5F_Text_ExecutiveF1After:
	.string "{PLAYER}, ¿verdad?\p"
	.string "Un mocoso como tú no apreciará\n"
	.string "la magnificencia del TEAM ROCKET.\p"
	.string "Qué mal. Realmente admiro\n"
	.string "tu poder.$"

GoldenrodCity_RadioTower_5F_Text_RocketBossSeen:
	.string "¿Oh? ¿Lograste llegar hasta aquí?\p"
	.string "Debes ser un gran entrenador.\p"
	.string "Tomaremos esta ESTACIÓN DE RADIO\n"
	.string "para anunciar nuestro regreso.\p"
	.string "Eso atraerá a nuestro jefe GIOVANNI\n"
	.string "vuelve de su entrenamiento solo.\p"
	.string "Recuperaremos nuestra antigua\n"
	.string "gloria...\p"
	.string "¡No permitiré que interfieras con\n"
	.string "nuestros meticulosos planes!$"

GoldenrodCity_RadioTower_5F_Text_RocketBossBeaten:
	.string "No! Forgive me, GIOVANNI!$"

GoldenrodCity_RadioTower_5F_Text_RocketBossAfter:
	.string "¿Cómo puede ser esto?\p"
	.string "Nuestros sueños se han esfumado.\p"
	.string "No estuve a la altura del reto.\p"
	.string "Como hizo GIOVANNI antes que yo,\n"
	.string "disolveré el TEAM ROCKET hoy mismo.\p"
	.string "Adiós.$"

GoldenrodCity_RadioTower_5F_Text_DirectorThanks:
	.string "DIRECTOR: {PLAYER}, ¡gracias!\p"
	.string "Tus valientes acciones salvaron\n"
	.string "POKéMON en todo el país.\p"
	.string "Sé que no es mucho, pero por favor\n"
	.string "toma esto.$"

GoldenrodCity_RadioTower_5F_Text_DirectorClearWingExplanation:
	.string "Había una torre justo aquí\n"
	.string "en CIUDAD TRIGAL.\p"
	.string "Pero era vieja y crujía.\p"
	.string "Así que pusimos nuestra TORRE\n"
	.string "RADIO.\p"
	.string "Desenterramos ese ala durante\n"
	.string "la construcción.\p"
	.string "Oí que todo tipo de POKéMON\n"
	.string "vivió en CIUDAD TRIGAL antes.\p"
	.string "Tal vez...\p"
	.string "Esa ala tiene alguna conexión con la\n"
	.string "TORRE BELL en CIUDAD IRIS...\p"
	.string "Bien, mejor voy a mi OFICINA.$"

GoldenrodCity_RadioTower_5F_Text_DirectorTidalWingExplanation:
	.string "Había una torre justo aquí\n"
	.string "en CIUDAD TRIGAL.\p"
	.string "Pero era vieja y crujía.\p"
	.string "Así que pusimos nuestra TORRE\n"
	.string "RADIO.\p"
	.string "Desenterramos ese ala durante\n"
	.string "la construcción.\p"
	.string "Oí que todo tipo de POKéMON\n"
	.string "vivió en CIUDAD TRIGAL antes.\p"
	.string "Tal vez...\p"
	.string "Esa ala tiene alguna conexión con la\n"
	.string "ISLAS REMOLINO cerca de C. ORQUIDEA...\p"
	.string "Bien, mejor voy a mi OFICINA.$"

GoldenrodCity_RadioTower_5F_Text_DirectorLegendary:
	.string "Ah!\p"
	.string "Eso me recuerda...\p"
	.string "Esa ala que te di... creo que\n"
	.string "está ligada al LEGENDARIO\l"
	.string "POKéMON planta.\p"
	.string "¡Pero el POKéMON LEGENDARIO no\n"
	.string "aparecerá solo con esa ala...\p"
	.string "Al parecer hay algo más\n"
	.string "necesitas... o algo así.\p"
	.string "Me pregunto qué sería...\p"
	.string "No puedo recordarlo.$"

GoldenrodCity_RadioTower_5F_Text_DirectorFakeout:
	.string "¿Estás esperando algo?\n"
	.string "A esto lo llaman SORPRESA.\p"
	.string "Debo volver a mi OFICINA\n"
	.string "esta vez. ¡Nos vemos!$"

GoldenrodCity_RadioTower_5F_Text_DirectorIntro:
	.string "DIRECTOR: ¡Hola, {PLAYER}!\p"
	.string "Sabes, amo a los POKéMON.\p"
	.string "Hice esta TORRE RADIO para\n"
	.string "expresar mi amor por POKéMON.\p"
	.string "Sería lindo que la gente disfrutara\n"
	.string "nuestros programas.$"

GoldenrodCity_RadioTower_5F_Text_Ben:
	.string "BEN: ¿Escuchas nuestra música?$"

GoldenrodCity_RadioTower_5F_Text_DirectorOfficeSign:
	.string "5F DIRECTOR'S   OFFICE$"

GoldenrodCity_RadioTower_5F_Text_Studio1Sign:
	.string "5F STUDIO 1$"
