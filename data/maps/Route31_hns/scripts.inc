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
	.string "POKéMON.\p"
	.string "Me duelen los pies y tengo sueño…\p"
	.string "If I were a wild POKéMON, I'd\n"
	.string "be easy to catch…\p"
	.string "…Zzzz…$"

Route31_Text_SleepyManGotMail:
	.string "…Zzzz… Huh?\p"
	.string "What's that? You have MAIL\n"
	.string "por mí?$"

Route31_Text_SleepyManFail:
	.string "…Zzzz…$"

Route31_Text_HandOverMailMon:
	.string "{PLAYER} handed over the\n"
	.string "POKéMON holding the MAIL.$"

Route31_Text_ReadingMail:
	.string "Veamos...\p"
	.string "Thanks for bringing this to\n"
	.string "me.\p"
	.string "My friend's a good guy, and\n"
	.string "you're swell too!\p"
	.string "I'd like to do something good\n"
	.string "in return too!\p"
	.string "I know! I want you to have\n"
	.string "this!$"

Route31_Text_DescribeRest:
	.string "...Zzz...\p"
	.string "...Umm... Rest!\p"
	.string "The phrase 'recover fast' became\n"
	.string "shortened to 'Rest,' you see?\p"
	.string "This is a move to sleep and recover\n"
	.string "some HP.$"

Route31_Text_WrongMail:
	.string "Esta CARTA no es para mí.$"

Route31_Text_MissingMail:
	.string "Why is this POKéMON so special?\p"
	.string "It doesn't have any MAIL.$"

Route31_Text_DeclinedToHandOverMail:
	.string "What? You don't want\n"
	.string "anything?$"

Route31_Text_CantTakeLastMon:
	.string "If I take that POKéMON from\n"
	.string "you,\p"
	.string "what are you going to use in\n"
	.string "battle?$"

Route31_Text_Youngster:
	.string "I found a good POKéMON in DARK\n"
	.string "CAVE.\p"
	.string "I'm going to raise it to take\n"
	.string "on FALKNER.\p"
	.string "He's the leader of VIOLET\n"
	.string "CITY's GYM.$"

Route31_Text_Sign:
	.string "ROUTE 31\p"
	.string "CDAD. MALVA - CDAD. CEREZO$"

Route31_Text_WadeRegister:
	.string "You're awesome! I like you!\p"
	.string "I look for POKéMON here every\n"
	.string "day.\p"
	.string "When I'm in the grass, I find\n"
	.string "all kinds of BERRIES.\p"
	.string "If you'd like, I'll share\n"
	.string "some.$"

Route31_Text_WadeRematchIntro:
	.string "I was waiting for you.\n"
	.string "¡A luchar!$"

Route31_Text_WadeRematchDefeat:
	.string "Awwwww…$"

Route31_Text_WadePostRematch:
	.string "You'll hear from me as soon\n"
	.string "as I find anything that you\l"
	.string "might like.$"

Route31_Text_WadeHasItem:
	.string "Hey! I've been looking for\n"
	.string "you!\p"
	.string "I found something while I\n"
	.string "estaba en la hierba.\p"
	.string "Here, you can have it!$"

Route31_Text_WadeGaveItem:
	.string "I'll let you know if I find\n"
	.string "anything else!$"

Route31_Text_WadeNoRoom:
	.string "Hmm, parece que tu MOCHILA\n"
	.string "está llena.\p"
	.string "Vuelve cuando tengas espacio.\n"
	.string "cuarto del jefe!$"

Route31_Text_DarkCaveSign:
	.string "DARK CAVE$"
