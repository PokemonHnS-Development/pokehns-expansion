FuchsiaCity_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FuchsiaCity_OnTransition
	.byte 0

FuchsiaCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_FUCHSIA_CITY
	call_if_set FLAG_GOT_DOME_FOSSIL, FuchsiaCity_EventScript_SetOmanyteGfx
	call_if_unset FLAG_GOT_DOME_FOSSIL, FuchsiaCity_EventScript_SetKabutoGfx
	end

FuchsiaCity_EventScript_SetOmanyteGfx::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_OMANYTE
	return

FuchsiaCity_EventScript_SetKabutoGfx::
	setvar VAR_OBJ_GFX_ID_0, OBJ_EVENT_GFX_KABUTO
	return

FuchsiaCity_EventScript_LittleBoy::
	msgbox FuchsiaCity_Text_DidYouTrySafariGame, MSGBOX_NPC
	end

FuchsiaCity_EventScript_OldMan::
	msgbox FuchsiaCity_Text_SafariZoneZooInFront, MSGBOX_NPC
	end

FuchsiaCity_EventScript_Erik::
	msgbox FuchsiaCity_Text_WheresSara, MSGBOX_NPC
	end

FuchsiaCity_EventScript_Youngster::
	msgbox FuchsiaCity_Text_ItemBallInThere, MSGBOX_NPC
	end

FuchsiaCity_EventScript_Lass::
	lock
	faceplayer
	famechecker FAMECHECKER_KOGA, 3
	msgbox FuchsiaCity_Text_MyFatherIsGymLeader
	release
	end

FuchsiaCity_EventScript_CitySign::
	msgbox FuchsiaCity_Text_CitySign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_SafariZoneSign::
	msgbox FuchsiaCity_Text_SafariZoneSign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_SafariGameSign::
	msgbox FuchsiaCity_Text_SafariGameSign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_WardensHomeSign::
	msgbox FuchsiaCity_Text_WardensHomeSign, MSGBOX_SIGN
	end

@ Unused
FuchsiaCity_EventScript_SafariZoneOfficeSign::
	msgbox FuchsiaCity_Text_SafariZoneOfficeSign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_KOGA, 0
	msgbox FuchsiaCity_Text_GymSign
	releaseall
	end

FuchsiaCity_EventScript_ChanseySign::
	lockall
	setvar VAR_0x8004, SPECIES_CHANSEY
	special SetSeenMon
	showmonpic SPECIES_CHANSEY, 10, 3
	msgbox FuchsiaCity_Text_ChanseySign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_VoltorbSign::
	lockall
	setvar VAR_0x8004, SPECIES_VOLTORB
	special SetSeenMon
	showmonpic SPECIES_VOLTORB, 10, 3
	msgbox FuchsiaCity_Text_VoltorbSign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_KangaskhanSign::
	lockall
	setvar VAR_0x8004, SPECIES_KANGASKHAN
	special SetSeenMon
	showmonpic SPECIES_KANGASKHAN, 10, 3
	msgbox FuchsiaCity_Text_KangaskhanSign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_SlowpokeSign::
	lockall
	setvar VAR_0x8004, SPECIES_SLOWPOKE
	special SetSeenMon
	showmonpic SPECIES_SLOWPOKE, 10, 3
	msgbox FuchsiaCity_Text_SlowpokeSign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_LaprasSign::
	lockall
	setvar VAR_0x8004, SPECIES_LAPRAS
	special SetSeenMon
	showmonpic SPECIES_LAPRAS, 10, 3
	msgbox FuchsiaCity_Text_LaprasSign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_FossilMonSign::
	lockall
	goto_if_set FLAG_GOT_DOME_FOSSIL, FuchsiaCity_EventScript_OmanyteSign
	setvar VAR_0x8004, SPECIES_KABUTO
	special SetSeenMon
	showmonpic SPECIES_KABUTO, 10, 3
	msgbox FuchsiaCity_Text_KabutoSign
	hidemonpic
	releaseall
	end

FuchsiaCity_EventScript_OmanyteSign::
	setvar VAR_0x8004, SPECIES_OMANYTE
	special SetSeenMon
	showmonpic SPECIES_OMANYTE, 10, 3
	msgbox FuchsiaCity_Text_OmanyteSign
	hidemonpic
	releaseall
	end

FuchsiaCity_Text_DidYouTrySafariGame::
	.string "¿Probaste el JUEGO SAFARI?\p"
	.string "Hay algunos POKéMON raros que\n"
	.string "solo pueden capturarse allí.$"

FuchsiaCity_Text_SafariZoneZooInFront::
	.string "La ZONA SAFARI tiene un zoológico\n"
	.string "frente a la entrada.\p"
	.string "Al fondo está el JUEGO SAFARI\n"
	.string "catching POKéMON.$"

FuchsiaCity_Text_WheresSara::
	.string "ERIK: ¿Dónde está SARA?\n"
	.string "Dije que la vería aquí.$"

FuchsiaCity_Text_ItemBallInThere::
	.string "Esa ball de objeto ahí...\n"
	.string "¿La querías?\p"
	.string "¡Yo también!\n"
	.string "...¿Eh? ¡¿Eso es un POKéMON?$"

FuchsiaCity_Text_CitySign::
	.string "CIUDAD FUCSIA\n"
	.string "¡Mira! ¡Es Rosa Pasión!$"

FuchsiaCity_Text_SafariZoneSign::
	.string "POKéMON PARADISE\n"
	.string "ZONA SAFARI$"

FuchsiaCity_Text_SafariGameSign::
	.string "JUEGO SAFARI\n"
	.string "POKéMON-U-CATCH!$"

FuchsiaCity_Text_WardensHomeSign::
	.string "ZONA SAFARI\n"
	.string "CASA DEL GUARDA$"

FuchsiaCity_Text_SafariZoneOfficeSign::
	.string "POKéMON PARADISE!\n"
	.string "¡Bienvenido a la ZONA SAFARI!\l"
	.string "OFICINA DEL SAFARI$"

FuchsiaCity_Text_GymSign::
	.string "GIMNASIO POKéMON CIUDAD FUCSIA\n"
	.string "CIUDAD FUXIA: KOGA\l"
	.string "El Maestro Ninja Venenoso$"

FuchsiaCity_Text_ChanseySign::
	.string "Nombre: CHANSEY\n"
	.string "Atraparlo es puro azar.$"

FuchsiaCity_Text_VoltorbSign::
	.string "Nombre: VOLTORB\n"
	.string "La viva imagen de una POKé BALL.$"

FuchsiaCity_Text_KangaskhanSign::
	.string "Nombre: KANGASKHAN\p"
	.string "Un POKéMON maternal que cría a su\n"
	.string "joven en una bolsa en su vientre.$"

FuchsiaCity_Text_SlowpokeSign::
	.string "Nombre: SLOWPOKE\n"
	.string "Amigable y muy lento.$"

FuchsiaCity_Text_LaprasSign::
	.string "Nombre: LAPRAS\n"
	.string "El rey de los mares.$"

FuchsiaCity_Text_OmanyteSign::
	.string "Nombre: OMANYTE\n"
	.string "Un POKéMON rarísimo que fue\l"
	.string "regenerado de un fósil.$"

FuchsiaCity_Text_KabutoSign::
	.string "Nombre: KABUTO\n"
	.string "Un POKéMON rarísimo que fue\l"
	.string "regenerado de un fósil.$"

@ Unused. May have been meant to be the placeholder text for the zoo mons, similar to RB's "!" text
FuchsiaCity_Text_Ellipsis::
	.string "......$"

Text_SubstituteTeach::
	.string "Ojalá fuera un KANGASKHAN\n"
	.string "bebé.\p"
	.string "Me encantaría ser suplente de los\n"
	.string "bebé...\p"
	.string "Y acurrucarse en la madre\n"
	.string "de la madre KANGASKHAN.\p"
	.string "Pero solo los POKéMON pueden\n"
	.string "usar la técnica SUSTITUTO...\p"
	.string "¿Quieres que le enseñe SUSTITUTO a\n"
	.string "uno de tus POKéMON?$"

Text_SubstituteDeclined::
	.string "¿Ah, de verdad?\n"
	.string "SUSTITUTO parece muy divertido...$"

Text_SubstituteWhichMon::
	.string "¿Qué POKéMON quiere aprender\n"
	.string "SUSTITUTO?$"

Text_SubstituteTaught::
	.string "Ojalá pudiera meterme en la\n"
	.string "bolsa de un KANGASKHAN...$"

FuchsiaCity_Text_MyFatherIsGymLeader::
	.string "Mi padre es el LÍDER de GIMNASIO\n"
	.string "de este pueblo.\p"
	.string "Entreno para usar POKéMON TIPO\n"
	.string "VENENO, igual que mi padre.$"

