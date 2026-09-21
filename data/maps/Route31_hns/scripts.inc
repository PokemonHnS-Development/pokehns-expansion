Route31_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route31_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route31_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route31_EventScript_Bugcatcher_Wade::
	trainerbattle_single TRAINER_WADE_HNS, Route31_Text_BugCatcherWade1_Seen, Route31_Text_BugCatcherWade1_Beaten, Route31_EventScript_RegisterWade
	goto_if_set FLAG_WADE_HAS_ITEM_HNS, Route31_EventScript_WadeGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route31_EventScript_RematchWade
	msgbox Route31_Text_BugCatcherWade1_After, MSGBOX_AUTOCLOSE
	end

Route31_EventScript_RegisterWade::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route31_Text_WadeRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_WADE_HNS
	release
	end

Route31_EventScript_RematchWade::
	trainerbattle_rematch TRAINER_WADE_HNS, Route31_Text_WadeRematchIntro, Route31_Text_WadeRematchDefeat
	msgbox Route31_Text_WadePostRematch, MSGBOX_AUTOCLOSE
	end

Route31_EventScript_WadeGiveItem::
	msgbox Route31_Text_WadeHasItem, MSGBOX_DEFAULT
	giveitem VAR_WADE_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, Route31_EventScript_WadeNoRoom
	clearflag FLAG_WADE_HAS_ITEM_HNS
	msgbox Route31_Text_WadeGaveItem, MSGBOX_AUTOCLOSE
	end

Route31_EventScript_WadeNoRoom::
	msgbox Route31_Text_WadeNoRoom, MSGBOX_AUTOCLOSE
	end

Route31_EventScript_Youngster::
	lock
	faceplayer
	msgbox Route31_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_EventScript_SleepyMan::
	lock
	faceplayer
	goto_if_eq VAR_KENYA, 1, Route31_EventScript_SleepyMan_AskForKenya
	msgbox Route31_Text_SleepyMan, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_EventScript_SleepyMan_AskForKenya::
	msgbox Route31_Text_SleepyManGotMail, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route31_EventScript_SleepyMan_GiveKenya
	msgbox Route31_Text_SleepyManFail, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_EventScript_SleepyMan_GiveKenya::
	removenamedmon 1
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, Route31_EventScript_SleepyMan_Fail
	msgbox Route31_Text_HandOverMailMon, MSGBOX_DEFAULT
	delay 55
	callnative UpdateFollowingPokemon
	msgbox Route31_Text_ReadingMail, MSGBOX_DEFAULT
	giveitem ITEM_TM_REST
	msgbox Route31_Text_DescribeRest, MSGBOX_DEFAULT
	closemessage
	setvar VAR_KENYA, 2
	release
	end

Route31_EventScript_SleepyMan_Fail::
	msgbox Route31_Text_SleepyManFail, MSGBOX_DEFAULT
	release
	end


Route31_EventScript_Boy::
	lock
	faceplayer
	msgbox Route31_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Route31_EventScript_DarkCaveSign::
	lock
	msgbox Route31_Text_DarkCaveSign, MSGBOX_SIGN
	closemessage
	release
	end

Route31_EventScript_Sign::
	lock
	msgbox Route31_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route31_EventScript_ItemPokeBall::
	finditem ITEM_POKE_BALL
	end

Route31_EventScript_ItemAntidote::
	finditem ITEM_ANTIDOTE
	end

Route31_Text_CooltrainerM:
	.string "CUEVA OSCURA…\p"
	.string "Si un POKéMON pudiera iluminarla,\n"
	.string "la exploraría.$"

Route31_Text_BugCatcherWade1_Seen:
	.string "Atrapé varios POKéMON.\n"
	.string "¡Lucha conmigo!$"

Route31_Text_BugCatcherWade1_Beaten:
	.string "Awwwww…$"

Route31_Text_BugCatcherWade1_After:
	.string "Puedes capturar POKéMON aunque\n"
	.string "ya lleves seis contigo.\p"
	.string "Si capturas uno, irá a tu\n"
	.string "BOX automáticamente.$"

Route31_Text_SleepyMan:
	.string "… Hnuurg… ¿Eh?\p"
	.string "Caminé demasiado hoy buscando\n"
	.string "POKéMON planta.\p"
	.string "Me duelen los pies y tengo sueño…\p"
	.string "Si fuera un POKéMON salvaje,\n"
	.string "sería fácil de atrapar...\p"
	.string "…Zzzz…$"

Route31_Text_SleepyManGotMail:
	.string "...Zzzz... ¿Eh?\p"
	.string "¿Qué es eso? Tienes CORREO\n"
	.string "por mí?$"

Route31_Text_SleepyManFail:
	.string "…Zzzz…$"

Route31_Text_HandOverMailMon:
	.string "{PLAYER} entregó al\n"
	.string "POKéMON que traía el CORREO.$"

Route31_Text_ReadingMail:
	.string "Veamos...\p
Gracias por traérmelo\n
a mí.\p
Mi amigo es buena persona, y\n
¡tú también eres genial!\p
¡También quiero hacer algo\n
bueno en agradecimiento!\p
¡Ya sé! Quiero que te\n
quedes con esto!$"

Route31_Text_DescribeRest:
	.string "...Zzz...\p
...Mmm... ¡Descanso!\p
La frase 'recuperarse rápido' se\n
acortó a 'Descanso', ¿ves?\p
Es un movimiento para dormir y\n
recuperar algo de PS.$"

Route31_Text_WrongMail:
	.string "Esta CARTA no es para mí.$"

Route31_Text_MissingMail:
	.string "¿Por qué este POKéMON es especial?\p"
	.string "No tiene ningún CORREO.$"

Route31_Text_DeclinedToHandOverMail:
	.string "¿Qué? ¿No quieres\n
nada?$"

Route31_Text_CantTakeLastMon:
	.string "Si te quito ese POKéMON,\n"
	.string "tú,\p"
	.string "¿qué usarás en?\n"
	.string "para luchar?$"

Route31_Text_Youngster:
	.string "Hallé un buen POKéMON en la\n"
	.string "CUEVA OSCURA.\p"
	.string "Lo entrenaré para luchar\n"
	.string "contra FALKNER.\p"
	.string "Él es el líder del GIMNASIO de\n"
	.string "CIUDAD MALVA.$"

Route31_Text_Sign:
	.string "RUTA 31\p"
	.string "CDAD. MALVA - CDAD. CEREZO$"

Route31_Text_WadeRegister:
	.string "¡Eres genial! ¡Me caes bien!\p"
	.string "Busco POKéMON aquí cada\n"
	.string "día.\p"
	.string "Cuando estoy en el pasto, hallo\n"
	.string "todo tipo de BAYAS.\p"
	.string "Si quieres, compartiré\n"
	.string "algunas.$"

Route31_Text_WadeRematchIntro:
	.string "Te estaba esperando.\n"
	.string "¡A luchar!$"

Route31_Text_WadeRematchDefeat:
	.string "Awwwww…$"

Route31_Text_WadePostRematch:
	.string "Te aviso en cuanto encuentre\n
algo que te pueda\l
gustar.$"

Route31_Text_WadeHasItem:
	.string "¡Oye! ¡Te he estado\n
buscando!\p
Encontré algo mientras\n
estaba en la hierba.\p
¡Toma, es para ti!$"

Route31_Text_WadeGaveItem:
	.string "¡Te aviso si encuentro\n
algo más!$"

Route31_Text_WadeNoRoom:
	.string "Hmm, parece que tu MOCHILA\n"
	.string "está llena.\p"
	.string "Vuelve cuando tengas espacio.\n"
	.string "cuarto del jefe!$"

Route31_Text_DarkCaveSign:
	.string "DARK CAVE$"
