AbandonedShip_Rooms2_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms2_1F_EventScript_Dan::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanIntro, AbandonedShip_Rooms2_1F_Text_DanDefeat, AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterDan
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms2_1F_EventScript_DanRematch
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterDan::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT  @ Kira speaks for both when registering KiraAndDan
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_DanRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanRematchIntro, AbandonedShip_Rooms2_1F_Text_DanRematchDefeat, AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Kira::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraIntro, AbandonedShip_Rooms2_1F_Text_KiraDefeat, AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterKira
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, AbandonedShip_Rooms2_1F_EventScript_KiraRematch
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterKira::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_KiraRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraRematchIntro, AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat, AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Jani::
	trainerbattle_single TRAINER_JANI, AbandonedShip_Rooms2_1F_Text_JaniIntro, AbandonedShip_Rooms2_1F_Text_JaniDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_JaniPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Garrison::
	trainerbattle_single TRAINER_GARRISON, AbandonedShip_Rooms2_1F_Text_GarrisonIntro, AbandonedShip_Rooms2_1F_Text_GarrisonDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_Text_DanIntro:
	.string "DAN: Buscando tesoros,\n"
	.string "¡encontramos a un ENTRENADOR!$"

AbandonedShip_Rooms2_1F_Text_DanDefeat:
	.string "DAN: No pudimos ganar aunque\n"
	.string "trabajamos juntos...$"

AbandonedShip_Rooms2_1F_Text_DanPostBattle:
	.string "DAN: No hallamos tesoros...\n"
	.string "¿Alguien se los habrá llevado?$"

AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons:
	.string "DAN: Ni siquiera tienes dos POKéMON.\n"
	.string "No esperes ganarnos así.$"

AbandonedShip_Rooms2_1F_Text_KiraIntro:
	.string "KIRA: ¿Oh?\n"
	.string "Buscábamos tesoros.\l"
	.string "¡Pero encontramos a un ENTRENADOR!$"

AbandonedShip_Rooms2_1F_Text_KiraDefeat:
	.string "KIRA: ¡Oh, qué fuerte!$"

AbandonedShip_Rooms2_1F_Text_KiraPostBattle:
	.string "KIRA: ¿Dónde estarán los tesoros?\p"
	.string "Ya decidí qué voy a comprar\n"
	.string "¡cuando hallemos los tesoros!$"

AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons:
	.string "KIRA: ¿No tienes dos POKéMON?\n"
	.string "¡Lucharemos en otro momento!$"

AbandonedShip_Rooms2_1F_Text_KiraRegister:
	.string "KIRA: ¡Ay, me haces enojar!\n"
	.string "¡Te lo voy a cobrar muy caro!$"

AbandonedShip_Rooms2_1F_Text_DanRematchIntro:
	.string "DAN: Hemos estado buscando\n"
	.string "tesoros todo este tiempo.\p"
	.string "Nuestros POKéMON también crecieron.\n"
	.string "¡Te lo demostraremos!$"

AbandonedShip_Rooms2_1F_Text_DanRematchDefeat:
	.string "DAN: ¡Eres fuerte, como siempre!$"

AbandonedShip_Rooms2_1F_Text_DanPostRematch:
	.string "DAN: No hallamos ningún tesoro,\n"
	.string "perdemos en POKéMON...\p"
	.string "Quiero ir a casa... Pero si lo digo,\n"
	.string "ella se enoja conmigo...$"

AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons:
	.string "DAN: Ni siquiera tienes dos POKéMON.\n"
	.string "No esperes ganarnos así.$"

AbandonedShip_Rooms2_1F_Text_KiraRematchIntro:
	.string "KIRA: ¿Oh? ¡Nos vemos otra vez!\p"
	.string "Como nosotros, tú no te rindes\n"
	.string "buscando tesoros, ¿verdad?\p"
	.string "¿Quieres que el perdedor tenga\n"
	.string "que dejar de buscar?$"

AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat:
	.string "KIRA: Oh, perdimos otra vez...$"

AbandonedShip_Rooms2_1F_Text_KiraPostRematch:
	.string "KIRA: No nos iremos hasta que\n"
	.string "entrenemos más a los POKéMON y\l"
	.string "hallemos los tesoros de aquí!$"

AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons:
	.string "KIRA: ¿No tienes dos POKéMON?\n"
	.string "¡Lucharemos en otro momento!$"

AbandonedShip_Rooms2_1F_Text_JaniIntro:
	.string "No soy buena nadando,\n"
	.string "¡pero soy buena en las batallas!$"

AbandonedShip_Rooms2_1F_Text_JaniDefeat:
	.string "Vaya.\n"
	.string "Eso no salió muy bien.$"

AbandonedShip_Rooms2_1F_Text_JaniPostBattle:
	.string "Caminar descalzo por este barco\n"
	.string "es algo asqueroso.$"

AbandonedShip_Rooms2_1F_Text_GarrisonIntro:
	.string "Fuerza y compasión...\n"
	.string "¡Esos son tesoros de ENTRENADOR!$"

AbandonedShip_Rooms2_1F_Text_GarrisonDefeat:
	.string "Ah, hay algo en ti\n"
	.string "que brilla.$"

AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle:
	.string "En algún camarote del barco,\n"
	.string "vi algo brillar.$"
