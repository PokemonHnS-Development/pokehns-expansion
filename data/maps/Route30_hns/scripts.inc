Route30_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route30_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route30_OnFrame
	.byte 0

Route30_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route30_OnFrame::
	map_script_2 VAR_CHERRYGROVE_CITY_STATE, 2, Route30_EventScript_ElmCall_Trigger
	.2byte 0
	
Route30_EventScript_Boy::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, Route30_EventScript_Boy2
	msgbox Route30_Text_YoungsterDirectionsToMrPokemon, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Boy2::
	lock
	faceplayer
	msgbox Route30_Text_YoungsterEveryoneIsBattling, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Girl::
	lock
	faceplayer
	msgbox Route30_Text_CooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

Route30_EventScript_Youngster_Joey_Fighting::
	lock
	msgbox Route30_Text_UseTackle, 	MSGBOX_AUTOCLOSE
	waitmessage
	playse SE_PIN
	applymovement LOCALID_ROUTE_30_JOEY, Common_Movement_QuestionMark
	delay 55
	waitmovement LOCALID_ROUTE_30_JOEY
	faceplayer
	msgbox Route30_Text_ThisIsABigBattle, MSGBOX_AUTOCLOSE
	waitmessage
	turnobject LOCALID_ROUTE_30_JOEY DIR_NORTH
	release
	end


Route30_EventScript_Youngster_Joey::
	trainerbattle_single TRAINER_JOEY_HNS, Route30_Text_YoungsterJoey1Seen, Route30_Text_YoungsterJoey1Beaten, Route30_EventScript_RegisterJoey
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route30_EventScript_RematchJoey
	msgbox Route30_Text_YoungsterJoey1After, MSGBOX_AUTOCLOSE
	end

Route30_EventScript_RegisterJoey::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route30_Text_JoeyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOEY_HNS
	release
	end

Route30_EventScript_RematchJoey::
	trainerbattle_rematch TRAINER_JOEY_HNS, Route30_Text_JoeyRematchIntro, Route30_Text_JoeyRematchDefeat
	msgbox Route30_Text_JoeyPostRematch, MSGBOX_AUTOCLOSE
	end

Route30_EventScript_Youngster_Mikey::
	trainerbattle_single TRAINER_MIKEY_HNS, Route30_Text_YoungsterMikeySeen, Route30_Text_YoungsterMikeyBeaten
	msgbox Route30_Text_YoungsterMikeyAfter, MSGBOX_AUTOCLOSE
	end
	
Route30_EventScript_Bugcatcher_Don::
	trainerbattle_single TRAINER_DON_HNS, Route30_Text_BugCatcherDonSeen, Route30_Text_BugCatcherDonBeaten
	msgbox Route30_Text_BugCatcherDonAfter, MSGBOX_AUTOCLOSE
	end

Route30_EventScript_ElmCall_Trigger::
	lock
	setspeaker Route30_Text_ElmName
	pokenavcall Route30_Text_Elm_Disaster
	waitmessage
	delay 30
	setvar VAR_CHERRYGROVE_CITY_STATE, 3
	release
	end

Route30_EventScript_Sign::
	lock
	msgbox Route30_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route30_EventScript_TrainerTips::
	lock
	msgbox Route30_Text_TrainerTips, MSGBOX_SIGN
	closemessage
	release
	end	

Route30_EventScript_Poliwag::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_POLIWAG, CRY_MODE_NORMAL
	msgbox Route30_Text_Poliwag, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route30_EventScript_Mailbox::
	msgbox Route30_Text_Mailbox, MSGBOX_SIGN
	end

Route30_Text_Mailbox:
	.string "MR.POKéMON's House$"

Route30_Text_UseTackle:
	.string "¡Ve, RATTATA!\p"
	.string "¡PLACAGE!$"

Route30_Text_ThisIsABigBattle:
	.string "¡¿Qué?! ¡Esta es una gran batalla!\n"
	.string "¡Déjame en paz!$"

Route30_Text_YoungsterJoey1Seen:
	.string "Acabo de perder, así que intento\n"
	.string "buscar más POKéMON.\p"
	.string "¡Espera! ¡Te ves débil! Vamos,\n"
	.string "¡luchemos!$"

Route30_Text_YoungsterJoey1Beaten:
	.string "¡Ay! ¡Perdí otra vez!\n"
	.string "¡Maldita sea!$"

Route30_Text_YoungsterJoey1After:
	.string "¡¿Tengo que tener más POKéMON?!\n"
	.string "¿para luchar mejor?\p"
	.string "¡No! Me quedo con este,\n"
	.string "¡pase lo que pase!$"

Route30_Text_YoungsterMikeySeen:
	.string "Eres un entrenador POKéMON,\n"
	.string "¿Verdad?\p"
	.string "¡entonces tienes que luchar!$"

Route30_Text_YoungsterMikeyBeaten:
	.string "Qué extraño.\n"
	.string "Ya gané antes.$"

Route30_Text_YoungsterMikeyAfter:
	.string "Ser un buen entrenador es\n"
	.string "muy difícil.\p"
	.string "Lucharé contra otras\n"
	.string "personas para mejorar.$"

Route30_Text_BugCatcherDonSeen:
	.string "En vez de un POKéMON bicho,\n"
	.string "¡Encontré un entrenador!$"

Route30_Text_BugCatcherDonBeaten:
	.string "¡Ah! ¡Eres muy fuerte!$"

Route30_Text_BugCatcherDonAfter:
	.string "Me quedé sin POKé BALLS mientras\n"
	.string "capturaba POKéMON.\p"
	.string "Debí haber comprado más...$"

Route30_Text_YoungsterDirectionsToMrPokemon:
	.string "¿La casa del SR. POKéMON?\n"
	.string "Está un poco más adelante.$"

Route30_Text_YoungsterEveryoneIsBattling:
	.string "Todos se divierten\n"
	.string "¡combatiendo!\p"
	.string "¡Tú también deberías!$"

Route30_Text_CooltrainerF:
	.string "No soy un entrenador.\p"
	.string "Pero si buscas a uno en la\n"
	.string "ojos, ¡prepárate para luchar!$"

Route30_Text_Sign:
	.string "RUTA 30\p"
	.string "CDAD. MALVA - CDAD. CEREZO$"

Route30_Text_MrPokemonsHouseDirectionsSign:
	.string "CASA DEL SR. POKéMON\n"
	.string "¡SIGUE TODO RECTO!$"

Route30_Text_MrPokemonsHouseSign:
	.string "MR. POKéMON'S HOUSE$"

Route30_Text_TrainerTips:
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "No robes las POKé BALLS\n"
	.string "exóticos POKéMON!\p"
	.string "de los demás. ¡Lánzalas\n"
	.string "solo a POKéMON salvajes!$"

Route30_Text_JoeyRegister:
	.string "¡Eres bastante bueno!\p"
	.string "Mi RATTATA está ansioso,\n"
	.string "como siempre.\p"
	.string "Es el único que tengo.\n"
	.string "¡Me convertiré en un gran\l"
	.string "ENTRENADOR con él!\p"
	.string "¡Luchemos otra vez algún día!$"

Route30_Text_JoeyRematchIntro:
	.string "¡Prometí que las cosas\n"
	.string "serían diferentes! ¡Luchamos!$"

Route30_Text_JoeyRematchDefeat:
	.string "¡Ay! ¡Perdí otra vez!\n"
	.string "¡Maldita sea!$"

Route30_Text_JoeyPostRematch:
	.string "Estoy revisando los movimientos\n"
	.string "de mi RATTATA y planeando\l"
	.string "unas estrategias.\p"
	.string "Cuando se me ocurra una buena,\n"
	.string "¡lucharemos!$"

Route30_Text_YoungsterJoeyGiveHPUp:
	.string "Perdí otra vez...\n"
	.string "¡Vaya, eres fuerte!\p"
	.string "Ah, sí, casi olvido eso\n"
	.string "Tenía que darte esto.\p"
	.string "Úsalo para hacerte más fuerte,\n"
	.string "OK?\p"
	.string "yo también me haré más fuerte.$"

Route30_Text_ElmName:
	.string "PROF.ELM$"

Route30_Text_Elm_Disaster:
	.string "PROF.ELM: ¿H-hola? ¿{PLAYER}? ¡Es\n"
	.string "un desastre!\p"
	.string "¡Eh, esto es terrible!\p"
	.string "¿Qué debo hacer? Es que...\n"
	.string "Oh, no...\p"
	.string "¡Por favor, vuelve ahora mismo!$"


Route30_Text_Poliwag:
	.string "POLIWAG: Wag waag!$"
