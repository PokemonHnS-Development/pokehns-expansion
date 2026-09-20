FuchsiaCity_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FuchsiaCity_EventScript_CityEnter
	.byte 0

FuchsiaCity_EventScript_CityEnter::
	setflag FLAG_VISITED_FUCHSIA_CITY
	end

FuchsiaCity_EventScript_BaobaCall::
	lock
	setspeaker FuchsiaCity_Text_BaobaName
	pokenavcall FuchsiaCity_Text_Baoba
	waitmessage
	delay 30
	setvar VAR_BAOBA_QUEST_STATE, 1
	setvar VAR_FUCHSIA_CITY_STATE, 1
	release
	end

FuchsiaCity_Text_BaobaName:
	.string "BAOBA$"

FuchsiaCity_Text_Baoba:
	.string "GUARDABAOBA: ¡{PLAYER}!\p"
	.string "Soy el GUARDABAOBA.\p"
	.string "¡Ha pasado algo terrible!\n"
	.string "Mi antigua SAFARI ZONE en CIUDAD\l"
	.string "FUCHSIA fue comprada y reabierta!\p"
	.string "¡Y al parecer tiene nuevos y\n"
	.string "exóticos POKéMON!\p"
	.string "¡Está afectando mi negocio!\p"
	.string "{PLAYER}, debes ir a la nueva\n"
	.string "SAFARI ZONE y capturar un POKéMON\l"
	.string "para enseñármelo. Debo saber sobre\l"
	.string "estos POKéMON exóticos.\p"
	.string "¡Por favor {PLAYER}, mi negocio\n"
	.string "depende de ti!$"

FuchsiaCity_EventScript_Dratini::
	lock
	showmonpic SPECIES_DRATINI, 10, 3
	delay 60
	hidemonpic
	release
	end
FuchsiaCity_EventScript_Kangaskhan::
	lock
	showmonpic SPECIES_KANGASKHAN, 10, 3
	delay 60
	hidemonpic
	release
	end
FuchsiaCity_EventScript_Cubone::
	lock
	showmonpic SPECIES_CUBONE, 10, 3
	delay 60
	hidemonpic
	release
	end
FuchsiaCity_EventScript_Omanyte::
	lock
	showmonpic SPECIES_OMANYTE, 10, 3
	delay 60
	hidemonpic
	release
	end
FuchsiaCity_EventScript_Kabuto::
	lock
	showmonpic SPECIES_KABUTO, 10, 3
	delay 60
	hidemonpic
	release
	end

FuchsiaCity_EventScript_Youngster::
	msgbox FuchsiaCity_Text_Youngster, MSGBOX_NPC
	end

FuchsiaCity_EventScript_PokefanM::
	msgbox FuchsiaCity_Text_PokefanM, MSGBOX_NPC
	end

FuchsiaCity_EventScript_Teacher::
	msgbox FuchsiaCity_Text_Teacher, MSGBOX_NPC
	end

FuchsiaCity_EventScript_CitySign::
	msgbox FuchsiaCity_Text_Sign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_GymSign::
	msgbox FuchsiaCity_Text_GymSign, MSGBOX_SIGN
	end

FuchsiaCity_EventScript_SafariZone::
	msgbox FuchsiaCity_Text_SafariZone, MSGBOX_NPC
	end

FuchsiaCity_Text_Youngster:
	.string "Uno del ALTO MANDO solía ser\n"
	.string "el LÍDER del GIMNASIO de FUCHSIA.$"

FuchsiaCity_Text_PokefanM:
	.string "La hija de KOGA lo sucedió como\n"
	.string "LÍDER del GIMNASIO tras unirse al\l"
	.string "ALTO MANDO.$"

FuchsiaCity_Text_Teacher:
	.string "La ZONA SAFARI tiene una nueva\n"
	.string "administración.\p"
	.string "¡Y tiene muchos POKéMON nuevos!$"

FuchsiaCity_Text_Sign:
	.string "CIUDAD FUCHSIA\p"
	.string "¡Mira! ¡Es Rosa Pasión!$"

FuchsiaCity_Text_GymSign:
	.string "GIMNASIO POKéMON CIUDAD FUCHSIA\n"
	.string "LÍDER: JANINE\p"
	.string "El Maestro Ninja Venenoso$"

FuchsiaCity_Text_SafariZoneOfficeSign:
	.string "Hay un aviso aquí…\p"
	.string "La OFICINA DE LA ZONA SAFARI\n"
	.string "está cerrada hasta nuevo aviso.$"

FuchsiaCity_Text_SafariZone:
	.string "ZONA SAFARI\n"
	.string "AHORA PROPIEDAD DE\l"
	.string "DEVON CORP.$"

FuchsiaCity_Text_SafariZoneClosedSign:
	.string "El GUARDABOSQUES viaja fuera.\p"
	.string "Por eso, la ZONA SAFARI está\n"
	.string "cerrada.$"

FuchsiaCity_Text_NoLitteringSign:
	.string "No tires basura.\p"
	.string "Lleva tus desperdicios contigo.$"

