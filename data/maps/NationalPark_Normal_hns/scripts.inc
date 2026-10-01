NationalPark_Normal_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, NationalPark_Normal_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

NationalPark_Normal_OnTransition: 
	callnative SetTimeBasedEncounters
	end

NationalPark_Normal_EventScript_Lass::
	lock
	faceplayer
	msgbox NationalPark_Normal_Text_Lass, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_Normal_EventScript_Youngster1::
	lock
	faceplayer
	msgbox NationalPark_Normal_Text_Youngster1, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_Normal_EventScript_Youngster2::
	lock
	faceplayer
	msgbox NationalPark_Normal_Text_Youngster2, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_Normal_EventScript_Teacher2::
	lock
	faceplayer
	msgbox NationalPark_Normal_Text_Teacher2, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	release
	end

NationalPark_Normal_EventScript_TeacherQuickclaw::
	lock
	faceplayer
	goto_if_set FLAG_GOT_QUICK_CLAW, NationalPark_Normal_EventScript_TeacherQuickclaw2
	msgbox NationalPark_Normal_Text_Teacher1, MSGBOX_DEFAULT
	giveitem ITEM_QUICK_CLAW
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	setflag FLAG_GOT_QUICK_CLAW
NationalPark_Normal_EventScript_TeacherQuickclaw2::
	msgbox NationalPark_Normal_Text_Teacher1_QuickClaw, MSGBOX_DEFAULT
	closemessage
	release
	end

NationalPark_Normal_EventScript_Persian::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PERSIAN, CRY_MODE_NORMAL
	msgbox NationalPark_Normal_Text_Persian, MSGBOX_DEFAULT
	waitmoncry
	release
	end



NationalPark_Normal_Text_Lass:
	.string "¡Mira! ¡Mira mi bolso!\p"
	.string "Imprimí mis favoritos de mi\n"
	.string "POKéDEX y los pegué en mi bolso.$"

NationalPark_Normal_Text_PokefanF:
	.string "Es CORREO que recibí de mi hija.\n"
	.string "Me anima mucho.$"

NationalPark_Normal_Text_Teacher1:
	.string "¡Presta atención, por favor!\p"
	.string "...Vaya, debo dejar de pensar como\n"
	.string "maestro todo el tiempo.\p"
	.string "Debes ser un ENTRENADOR POKéMON.\p"
	.string "Como te esfuerzas tanto, quiero\n"
	.string "que te lleves esto.$"

NationalPark_Normal_Text_Teacher1_QuickClaw:
	.string "Que un POKéMON lleve GARRA RÁPIDA.\p"
	.string "A veces atacará primero\n"
	.string "durante la batalla.$"

NationalPark_Normal_Text_Youngster1:
	.string "Juego con calcomanías que imprimí\n"
	.string "de mi POKéDEX.$"

NationalPark_Normal_Text_Youngster2:
	.string "Obtengo la calcomanía del otro\n"
	.string "si gano.$"

NationalPark_Normal_Text_Teacher2:
	.string "Camino por el PARQUE, pero\n"
	.string "nunca entro en la hierba.\p"
	.string "Los Entrenadores siempre pelean...\p"
	.string "Debes haber tenido muchas batallas.\n"
	.string "Deja que cure a tus POKéMON.$"

NationalPark_Normal_Text_Persian:
	.string "PERSIAN: Fufushaa!$"

NationalPark_Normal_EventScript_Jack::
	trainerbattle_single TRAINER_JACK_HNS, NationalPark_Normal_Text_SchoolboyJack1_Seen, NationalPark_Normal_Text_SchoolboyJack1_Beaten, NationalPark_Normal_EventScript_RegisterJack
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, NationalPark_Normal_EventScript_RematchJack
	msgbox NationalPark_Normal_Text_SchoolboyJack_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_RegisterJack::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox NationalPark_Normal_Text_JackRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JACK_HNS
	release
	end

NationalPark_Normal_EventScript_RematchJack::
	trainerbattle_rematch TRAINER_JACK_HNS, NationalPark_Normal_Text_JackRematchIntro, NationalPark_Normal_Text_JackRematchDefeat
	msgbox NationalPark_Normal_Text_JackPostRematch, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_Beverly::
	trainerbattle_single TRAINER_BEVERLY_HNS, NationalPark_Normal_Text_PokefanFBeverly1_Seen, NationalPark_Normal_Text_PokefanFBeverly1_Beaten, NationalPark_Normal_EventScript_RegisterBeverly
	goto_if_set FLAG_BEVERLY_HAS_ITEM_HNS, NationalPark_Normal_EventScript_BeverlyGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, NationalPark_Normal_EventScript_RematchBeverly
	msgbox NationalPark_Normal_Text_PokefanFBeverly_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_RematchBeverly::
	trainerbattle_rematch TRAINER_BEVERLY_HNS, NationalPark_Normal_Text_PokefanFBeverly1_Seen, NationalPark_Normal_Text_PokefanFBeverly1_Beaten
	msgbox NationalPark_Normal_Text_PokefanFBeverly_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_RegisterBeverly::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox NationalPark_Normal_Text_BeverlyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_BEVERLY_HNS
	release
	end

NationalPark_Normal_EventScript_BeverlyGiveItem::
	msgbox NationalPark_Normal_Text_BeverlyHasItem, MSGBOX_DEFAULT
	giveitem VAR_BEVERLY_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, NationalPark_Normal_EventScript_BeverlyNoRoom
	clearflag FLAG_BEVERLY_HAS_ITEM_HNS
	msgbox NationalPark_Normal_Text_BeverlyGaveItem, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_BeverlyNoRoom::
	msgbox NationalPark_Normal_Text_BeverlyNoRoom, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_William::
	trainerbattle_single TRAINER_WILLIAM_HNS, NationalPark_Normal_Text_PokefanmWilliam_Seen, NationalPark_Normal_Text_PokefanmWilliam_Beaten
	msgbox NationalPark_Normal_Text_PokefanmWilliam_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_Krise::
	trainerbattle_single TRAINER_KRISE_HNS, NationalPark_Normal_Text_LassKrise_Seen, NationalPark_Normal_Text_LassKrise_Beaten
	msgbox NationalPark_Normal_Text_LassKrise_After, MSGBOX_AUTOCLOSE
	end

NationalPark_Normal_EventScript_TM_Dig::
	finditem ITEM_TM_DIG
	end

NationalPark_Normal_EventScript_Item_Soothe_Bell::
	finditem ITEM_SOOTHE_BELL
	end

NationalPark_Normal_Text_SchoolboyJack1_Seen:
	.string "El mundo POKéMON es profundo.\p"
	.string "Aún hay muchas cosas que\n"
	.string "no sabemos.\p"
	.string "¡Pero yo sé más que tú!$"

NationalPark_Normal_Text_SchoolboyJack1_Beaten:
	.string "¿Qué-qué-qué?$"

NationalPark_Normal_Text_SchoolboyJack_After:
	.string "Hay mucho que aprender.\p"
	.string "Por ejemplo...\p"
	.string "Hay 92 tipos de MT.\p"
	.string "Los POKéMON cambiados suben rápido.$"

NationalPark_Normal_Text_JackRegister:
	.string "Hay mucho que aprender.\p"
	.string "Por ejemplo...\p"
	.string "Hay 92 tipos de MT.\p"
	.string "Los POKéMON cambiados suben rápido.$"

NationalPark_Normal_Text_JackRematchIntro:
	.string "¡He aprendido mucho desde\n"
	.string "nuestra última batalla! ¡Vamos!$"

NationalPark_Normal_Text_JackRematchDefeat:
	.string "¿Qué-qué-qué?$"

NationalPark_Normal_Text_JackPostRematch:
	.string "Hay mucho que aprender.\p"
	.string "Por ejemplo...\p"
	.string "Hay 92 tipos de MT.\p"
	.string "Los POKéMON cambiados suben rápido.$"

NationalPark_Normal_Text_PokefanFBeverly1_Seen:
	.string "Mis POKéMON son adorables.\p"
	.string "Déjame decirte lo orgulloso que\n"
	.string "me hacen adorables.$"

NationalPark_Normal_Text_PokefanFBeverly1_Beaten:
	.string "Puedo superarte en orgullo, pero...$"

NationalPark_Normal_Text_PokefanFBeverly_After:
	.string "debo decir que tus POKéMON son muy\n"
	.string "lindos también.$"

NationalPark_Normal_Text_PokefanmWilliam_Seen:
	.string "Adoramos a nuestros POKéMON, aunque\n"
	.string "no nos quieran.\p"
	.string "¡De eso se trata ser un FAN!$"

NationalPark_Normal_Text_PokefanmWilliam_Beaten:
	.string "¡M-mi POKéMON!$"

NationalPark_Normal_Text_PokefanmWilliam_After:
	.string "Perdí la batalla, pero mis POKéMON\n"
	.string "ganan el premio a los más bellos.$"

NationalPark_Normal_Text_LassKrise_Seen:
	.string "¿Hola? ¿Por qué me miras así?\p"
	.string "Oh, ¿una batalla?$"

NationalPark_Normal_Text_LassKrise_Beaten:
	.string "...Hmmm...$"

NationalPark_Normal_Text_LassKrise_After:
	.string "¡Pensé que me mirabas\n"
	.string "porque soy linda!$"

NationalPark_Normal_Text_Sign_RelaxationSquare:
	.string "PLAZA DE RELAJACIÓN\n"
	.string "PARQUE NACIONAL$"

NationalPark_Normal_Text_Sign_BattleNotice:
	.string "¿Qué dice este aviso?\p"
	.string "Lucha solo en la hierba, por favor.\p"
	.string "OFICINA DEL GUARDAPARQUE$"

NationalPark_Normal_Text_TrainerTips:
	.string "CONSEJOS DE ENTRENADOR\p"
	.string "Imprime el CORREO abriéndolo y\n"
	.string "luego pulsando START.$"

NationalPark_Normal_Text_BeverlyRegister:
	.string "debo decir que tus POKéMON son muy\n"
	.string "lindos también.$"

NationalPark_Normal_Text_BeverlyHasItem:
	.string "¡Hola! Tengo algo para ti.\n"
	.string "estábamos guardando.\p"
	.string "¡Tómalo como muestra de\n"
	.string "mi agradecimiento!$"

NationalPark_Normal_Text_BeverlyGaveItem:
	.string "¡Mi querido POKéMON y yo\n"
	.string "estaremos animándote!$"

NationalPark_Normal_Text_BeverlyNoRoom:
	.string "Hmm, tu BOLSA está llena.\p"
	.string "Vuelve cuando tengas espacio.$"
