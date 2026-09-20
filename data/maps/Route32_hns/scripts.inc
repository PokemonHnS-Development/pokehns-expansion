Route32_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route32_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route32_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route32_EventScript_FisherJustin::
	trainerbattle_single TRAINER_JUSTIN_HNS, Route32_Text_FisherJustin_Seen, Route32_Text_FisherJustin_Beaten
	msgbox Route32_Text_FisherJustin_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_FisherRalph::
	trainerbattle_single TRAINER_RALPH_HNS, Route32_Text_FisherRalph1_Seen, Route32_Text_FisherRalph1_Beaten, Route32_EventScript_RegisterRalph
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route32_EventScript_RematchRalph
	msgbox Route32_Text_FisherRalph1_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_RegisterRalph::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route32_Text_RalphRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_RALPH_HNS
	release
	end

Route32_EventScript_RematchRalph::
	trainerbattle_rematch TRAINER_RALPH_HNS, Route32_Text_RalphRematchIntro, Route32_Text_RalphRematchDefeat
	msgbox Route32_Text_RalphPostRematch, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_FisherHenry::
	trainerbattle_single TRAINER_HENRY_HNS, Route32_Text_FisherHenry_Seen, Route32_Text_FisherHenry_Beaten
	msgbox Route32_Text_FisherHenry_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_YoungsterAlbert::
	trainerbattle_single TRAINER_ALBERT_HNS, Route32_Text_YoungsterAlbert_Seen, Route32_Text_YoungsterAlbert_Beaten
	msgbox Route32_Text_YoungsterAlbert_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_YoungsterGordon::
	trainerbattle_single TRAINER_GORDON_HNS, Route32_Text_YoungsterGordon_Seen, Route32_Text_YoungsterGordon_Beaten
	msgbox Route32_Text_YoungsterGordon_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_CamperRoland::
	trainerbattle_single TRAINER_ROLAND_HNS, Route32_Text_CamperRoland_Seen, Route32_Text_CamperRoland_Beaten
	msgbox Route32_Text_CamperRoland_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_PicnickerLiz::
	trainerbattle_single TRAINER_LIZ_HNS, Route32_Text_PicnickerLiz1_Seen, Route32_Text_PicnickerLiz1_Beaten, Route32_EventScript_RegisterLiz
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route32_EventScript_RematchLiz
	msgbox Route32_Text_PicnickerLiz1_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_RegisterLiz::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route32_Text_LizRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_LIZ_HNS
	release
	end

Route32_EventScript_RematchLiz::
	trainerbattle_rematch TRAINER_LIZ_HNS, Route32_Text_LizRematchIntro, Route32_Text_LizRematchDefeat
	msgbox Route32_Text_LizPostRematch, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_BirdkeeperPeter::
	trainerbattle_single TRAINER_PETER_HNS, Route32_Text_BirdKeeperPeter_Seen, Route32_Text_BirdKeeperPeter_Beaten
	msgbox Route32_Text_BirdKeeperPeter_After, MSGBOX_AUTOCLOSE
	end

Route32_EventScript_Roar::
	lock
	faceplayer
	checkitem ITEM_TM_ROAR
	goto_if_eq VAR_RESULT, TRUE, Route32_EventScript_Roar2
	msgbox Route32_Text_RoarIntro, MSGBOX_DEFAULT
	giveitem ITEM_TM_ROAR
	msgbox Route32_Text_RoarOutro, MSGBOX_DEFAULT
	closemessage
	release
	end
Route32_EventScript_Roar2::
	msgbox Route32_Text_RoarOutro, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_EventScript_SlowpokeTail_TriggerLeft::
	lock
	turnobject LOCALID_SLOWPOKETAIL_MAN, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_PIN
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SLOWPOKETAIL_MAN
	applymovement LOCALID_SLOWPOKETAIL_MAN, Route32_Movement_SlowpokeLeft
	waitmovement 0
	goto Route32_EventScript_SlowpokeTail_Trigger

Route32_EventScript_SlowpokeTail_TriggerMid::
	lock
	turnobject LOCALID_SLOWPOKETAIL_MAN, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_PIN
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SLOWPOKETAIL_MAN
	applymovement LOCALID_SLOWPOKETAIL_MAN, Route32_Movement_SlowpokeMid
	waitmovement 0
	goto Route32_EventScript_SlowpokeTail_Trigger

Route32_EventScript_SlowpokeTail_TriggerRight::
	lock
	turnobject LOCALID_SLOWPOKETAIL_MAN, DIR_EAST
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	playse SE_PIN
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_SLOWPOKETAIL_MAN
	applymovement LOCALID_SLOWPOKETAIL_MAN, Route32_Movement_SlowpokeRight
	waitmovement 0
	goto Route32_EventScript_SlowpokeTail_Trigger

Route32_EventScript_SlowpokeTail_Trigger::
	msgbox Route32_Text_SlowpokeTailOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route32_EventScript_SlowpokeTail_Trigger2
	msgbox Route32_Text_RefusedSlowpokeTail, MSGBOX_DEFAULT
	closemessage
	setvar VAR_SLOWPOKE_TAIL, 1
	release
	end	
Route32_EventScript_SlowpokeTail_Trigger2::
	msgbox Route32_Text_ThoughtKidsLoaded, MSGBOX_DEFAULT
	closemessage
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_eq VAR_TEMP_0, 16, Route32_EventScript_Movement_Left
	call_if_eq VAR_TEMP_0, 17, 	Route32_EventScript_Movement_Right
	setvar VAR_SLOWPOKE_TAIL, 1
	release
	end

Route32_EventScript_Movement_Left::
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_WalkLeft1
	waitmovement 0
	turnobject LOCALID_SLOWPOKETAIL_MAN, DIR_EAST
	return 

Route32_EventScript_Movement_Right::
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_WalkLeft1
	waitmovement 0
	applymovement LOCALID_SLOWPOKETAIL_MAN, Common_Movement_WalkLeft1
	waitmovement 0
	turnobject LOCALID_SLOWPOKETAIL_MAN, DIR_EAST
	return 	

Route32_EventScript_SlowpokeTail::
	lock
	faceplayer
	msgbox Route32_Text_SlowpokeTailOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route32_EventScript_SlowpokeTail2
	msgbox Route32_Text_RefusedSlowpokeTail, MSGBOX_DEFAULT
	closemessage
	release
	end
Route32_EventScript_SlowpokeTail2::
	msgbox Route32_Text_ThoughtKidsLoaded, MSGBOX_DEFAULT
	closemessage
	release
	end


Route32_EventScript_Frieda::
	lock
	faceplayer
	goto_if_set FLAG_GOT_POISON_BARB, Route32_EventScript_FriedaCompleted
	msgbox Route32_Text_MeetFrieda, MSGBOX_DEFAULT
	closemessage
	multichoice 20, 0, MULTI_DAYS_OF_WEEK, FALSE
	switch VAR_RESULT
	case 0, Route32_EventScript_FriedaNope
	case 1, Route32_EventScript_FriedaNope
	case 2, Route32_EventScript_FriedaNope
	case 3, Route32_EventScript_FriedaNope
	case 4, Route32_EventScript_FriedaNope
	case 5, Route32_EventScript_FriedaYes
	case 6, Route32_EventScript_FriedaNope
	case 7, Route32_EventScript_FriedaCancel
	case MULTI_B_PRESSED, Route32_EventScript_FriedaCancel
	closemessage
	release
	end
Route32_EventScript_FriedaYes::
	msgbox Route32_Text_FriedaGivesGift, MSGBOX_DEFAULT
	giveitem ITEM_POISON_BARB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_GOT_POISON_BARB
	msgbox Route32_Text_FriedaGaveGift, MSGBOX_DEFAULT
	closemessage
	release
	end
Route32_EventScript_FriedaNope::
	msgbox Route32_Text_FriedaNope, MSGBOX_DEFAULT
	closemessage
	release
	end
Route32_EventScript_FriedaCancel::
	closemessage
	release
	end
Route32_EventScript_FriedaCompleted::
	msgbox Route32_Text_FriedaFriday, MSGBOX_DEFAULT
	closemessage
	release
	end

Route32_EventScript_BaldingMan::
	lock
	faceplayer
	msgbox Route32_Text_CooltrainerM_Experiences, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_ROUTE32_BALDINGMAN, DIR_EAST
	release
	end

Route32_EventScript_BaldingManTriggerLeft::
	lock
	playse SE_PIN
	applymovement LOCALID_ROUTE32_BALDINGMAN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ROUTE32_BALDINGMAN
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	goto Route32_EventScript_BaldingManCheck
	end
Route32_EventScript_BaldingManTriggerMid::
	lock
	playse SE_PIN
	applymovement LOCALID_ROUTE32_BALDINGMAN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ROUTE32_BALDINGMAN
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Movement_StartMid
	waitmovement 0
	goto Route32_EventScript_BaldingManCheck
	end
Route32_EventScript_BaldingManTriggerRight::
	lock
	playse SE_PIN
	applymovement LOCALID_ROUTE32_BALDINGMAN, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_ROUTE32_BALDINGMAN
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Movment_StartRight
	waitmovement 0
	goto Route32_EventScript_BaldingManCheck
	end
Route32_EventScript_BaldingManCheck::
	goto_if_unset FLAG_HIDE_SPROUT_TOWER_SILVER, Route32_EventScript_BaldingManTower
	goto_if_unset FLAG_DEFEATED_VIOLET_GYM, Route32_EventScript_BaldingManGym
	goto_if_unset FLAG_RECEIVED_TOGEPI_EGG, Route32_EventScript_BaldingManEgg
	msgbox Route32_Text_CooltrainerM_HaveThisSeed, MSGBOX_DEFAULT
	giveitem ITEM_MIRACLE_SEED
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	closemessage
	setvar VAR_VIOLET_CITY_STATE, 5
	release
	end
Route32_EventScript_BaldingManTower::
	msgbox Route32_Text_CooltrainerM_WhatsTheHurry, MSGBOX_DEFAULT
	msgbox Route32_Text_CooltrainerM_SproutTower, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Movement_Turnback
	waitmovement 0
	release
	end
Route32_EventScript_BaldingManGym::
	msgbox Route32_Text_CooltrainerM_WhatsTheHurry, MSGBOX_DEFAULT
	msgbox Route32_Text_CooltrainerM_VioletGym, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Movement_Turnback
	waitmovement 0
	release
	end
Route32_EventScript_BaldingManEgg::
	msgbox Route32_Text_CooltrainerM_WhatsTheHurry, MSGBOX_DEFAULT
	msgbox Route32_Text_CooltrainerM_AideIsWaiting, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Movement_Turnback
	waitmovement 0
	release
	end

Route32_EventScript_Item_Bullet_Seed::
    finditem ITEM_TM_BULLET_SEED
    end
	
Route32_EventScript_GreatBall::
	finditem ITEM_GREAT_BALL
	end
Route32_EventScript_GreatBallII::
	finditem ITEM_GREAT_BALL
	end
Route32_EventScript_SuperPotion::
	finditem ITEM_SUPER_POTION
	end

Route32_EventScript_Sign1::
	lock
	msgbox Route32_Text_Sign1, MSGBOX_SIGN
	closemessage
	release
	end

Route32_EventScript_Sign2::
	lock
	msgbox Route32_Text_Sign2, MSGBOX_SIGN
	closemessage
	release
	end

Route32_EventScript_Sign3::
	lock
	msgbox Route32_Text_Sign3, MSGBOX_SIGN
	closemessage
	release
	end

Route32_Movement_Turnback:
	walk_up
	step_end

Route32_Movement_StartMid:
	walk_left
	step_end

Route32_Movment_StartRight:
	walk_left
	walk_left
	step_end

Route32_Movement_SlowpokeLeft::
	step_end

Route32_Movement_SlowpokeMid::
	walk_right
	step_end

Route32_Movement_SlowpokeRight::
	walk_right
	walk_right
	step_end

Route32_Text_CooltrainerM_WhatsTheHurry:
	.string "Wait up!\n"
	.string "What's the hurry?$"

Route32_Text_CooltrainerM_AideIsWaiting:
	.string "{PLAYER}, right?\n"
	.string "Some guy wearing glasses\p"
	.string "was looking for you.\p"
	.string "See for yourself. He's waiting for\n"
	.string "you at the POKéMON CENTER.$"

Route32_Text_CooltrainerM_SproutTower:
	.string "Have you gone to SPROUT TOWER?\n"
	.string "If you ever visit VIOLET CITY,\p"
	.string "they'll expect you to train there.\n"
	.string "That's basic for trainers.\p"
	.string "Go to SPROUT TOWER!$"

Route32_Text_CooltrainerM_VioletGym:
	.string "¿Fuiste al GIMNASIO POKéMON?\n"
	.string "Allí puedes poner a prueba a tus\p"
	.string "POKéMON y a ti mismo.\n"
	.string "¡Es un rito de iniciación para\p"
	.string "todo ENTRENADOR!$"

Route32_Text_CooltrainerM_HaveThisSeed:
	.string "Tienes buenos POKéMON contigo.\n"
	.string "Debe ser por el entrenamiento que\p"
	.string "les diste en CIUDAD MALVA.\n"
	.string "El entrenamiento en el GIMNASIO\p"
	.string "debió ayudar mucho. Como recuerdo\n"
	.string "de CIUDAD MALVA, toma esto.\p"
	.string "Aumenta el poder de los ataques\n"
	.string "movimientos tipo DRAGÓN.$"

Route32_Text_CooltrainerM_Experiences:
	.string "Tus vivencias en CIUDAD MALVA\n"
	.string "serán útiles en tu viaje.$"

Route32_Text_SlowpokeTailOffer:
	.string "¿Te gustaría tener esta\n"
	.string "rica y nutritiva COLA SLOWPOKÉ?\p"
	.string "Para ti ahora mismo, solo\n"
	.string "¥1,000,000!\p"
	.string "¡Querrás esto!$"

Route32_Text_ThoughtKidsLoaded:
	.string "¡Tch! Pensé que los niños\n"
	.string "de hoy tenían dinero...$"

Route32_Text_RefusedSlowpokeTail:
	.string "¿No lo quieres?\n"
	.string "Entonces lárgate. ¡Fuera!$"

Route32_Text_FisherJustin_Seen:
	.string "¡Vaya!\p"
	.string "¡Hiciste que perdiera ese pez!$"

Route32_Text_FisherJustin_Beaten:
	.string "Sploosh!$"

Route32_Text_FisherJustin_After:
	.string "Calma, serenidad... La esencia de\n"
	.string "la pesca y POKéMON es la misma.$"

Route32_Text_FisherRalph1_Seen:
	.string "Soy muy bueno tanto en la\n"
	.string "pesca como en POKéMON.\p"
	.string "¡No pienso perder contra un niño!$"

Route32_Text_FisherRalph1_Beaten:
	.string "¡Tch! Intenté apresurar\n"
	.string "las cosas...$"

Route32_Text_FisherRalph1_After:
	.string "La pesca es una pasión\n"
	.string "para toda la vida.\p"
	.string "¡Los POKéMON son amigos eternos!$"

Route32_Text_RalphRegister:
	.string "La pesca es una pasión\n"
	.string "para toda la vida.\p"
	.string "¡Los POKéMON son amigos eternos!$"

Route32_Text_RalphRematchIntro:
	.string "Soy muy bueno tanto en la\n"
	.string "pesca como en POKéMON.\p"
	.string "¡No pienso perder contra un niño!$"

Route32_Text_RalphRematchDefeat:
	.string "¡Tch! Intenté apresurar\n"
	.string "las cosas...$"

Route32_Text_RalphPostRematch:
	.string "La pesca es una pasión\n"
	.string "para toda la vida.\p"
	.string "¡Los POKéMON son amigos eternos!$"

Route32_Text_FisherHenry_Seen:
	.string "My POKéMON? Freshly caught!$"

Route32_Text_FisherHenry_Beaten:
	.string "SPLASH?$"

Route32_Text_FisherHenry_After:
	.string "Los POKéMON recién capturados\n"
	.string "no valen nada ante los entrenados.$"

Route32_Text_YoungsterAlbert_Seen:
	.string "No te había visto por aquí.\n"
	.string "¿Así que crees que eres fuerte?$"

Route32_Text_YoungsterAlbert_Beaten:
	.string "You're strong!$"

Route32_Text_YoungsterAlbert_After:
	.string "Intentaré ser el mejor\n"
	.string "con mis favoritos.\p"
	.string "No usaré los mismos POKéMON\n"
	.string "fuertes que todos los demás.$"

Route32_Text_YoungsterGordon_Seen:
	.string "¡Encontré buenos POKéMON\n"
	.string "en la hierba!\p"
	.string "¡Creo que lo harán por mí!$"

Route32_Text_YoungsterGordon_Beaten:
	.string "Darn. I thought I could win.$"

Route32_Text_YoungsterGordon_After:
	.string "La hierba está llena de\n"
	.string "cosas pegajosas.$"

Route32_Text_CamperRoland_Seen:
	.string "That glance… It's intriguing.$"

Route32_Text_CamperRoland_Beaten:
	.string "Hmmm. This is disappointing.$"

Route32_Text_CamperRoland_After:
	.string "Si no quieres luchar,\n"
	.string "solo evita el contacto visual.$"

Route32_Text_PicnickerLiz1_Seen:
	.string "Ajá. Sí, y ya sabes...\p"
	.string "¿Perdón? ¿Luchar? Estoy al teléfono.\n"
	.string "Oh, está bien. Pero que sea rápido.$"

Route32_Text_PicnickerLiz1_Beaten:
	.string "¡Oh! Tengo que aliviar\n"
	.string "¡mi furia!$"

Route32_Text_PicnickerLiz1_After:
	.string "I was having a nice chat too.$"

Route32_Text_LizRegister:
	.string "I was having a nice chat too.$"

Route32_Text_LizRematchIntro:
	.string "Ajá. Sí, y ya sabes...\p"
	.string "¿Perdón? ¿Luchar? Estoy al teléfono.\n"
	.string "Oh, está bien. Pero que sea rápido.$"

Route32_Text_LizRematchDefeat:
	.string "¡Oh! Tengo que aliviar\n"
	.string "¡mi furia!$"

Route32_Text_LizPostRematch:
	.string "I was having a nice chat too.$"

Route32_Text_BirdKeeperPeter_Seen:
	.string "¡Esa MEDALLA! ¡Es de CIUDAD MALVA!\n"
	.string "¿Venciste a FALKNER?$"

Route32_Text_BirdKeeperPeter_Beaten:
	.string "I know what my weaknesses are.$"

Route32_Text_BirdKeeperPeter_After:
	.string "Debo entrenar otra vez en el\n"
	.string "GIMNASIO de CIUDAD MALVA.$"

Route32_Text_RoarIntro:
	.string "¡GRRRRR! ¡LA GENTE HUYE CUANDO\n"
	.string "RUJO! ¡PERO TÚ VINISTE A BUSCARME!\p"
	.string "¡ESO ME GUSTA! ¡AHORA RECIBE ESTO!$"

Route32_Text_RoarOutro:
	.string "¡GRRRRR! ¡ES UN RUJIDO!\p"
	.string "HASTA LOS POKéMON HUYEN DE UN BUEN\n"
	.string "¡ROAAR!$"

Route32_Text_MeetFrieda:
	.string "FRIEDA: ¡Yahoo!\p"
	.string "¡Soy FRIEDA de la FAMILIA DÍA!\n"
	.string "¡Mucho gusto!\p"
	.string "Si adivinas mi día favorito,\n"
	.string "te daré una recompensa.$"

Route32_Text_FriedaGivesGift:
	.string "Here's a POISON BARB for you!$"

Route32_Text_FriedaGaveGift:
	.string "FRIEDA: Dáselo a un POKéMON\n"
	.string "que use ataques tipo VENENO.\p"
	.string "Oh!\p"
	.string "¡Es increíble!\p"
	.string "Te sorprenderá lo mucho que\n"
	.string "potencia los ataques veneno!$"

Route32_Text_FriedaFriday:
	.string "FRIEDA: ¡Hola! ¿Cuál es tu\n"
	.string "día favorito?\p"
	.string "Amo los viernes. No hay duda,\n"
	.string "it!\p"
	.string "¿no crees que es genial?$"

Route32_Text_FriedaNope:
	.string "FRIEDA: Not that one!$"

Route32_Text_Sign1:
	.string "RUTA 32\p"
	.string "CIUDAD MALVA - PUEBLO AZALEA$"

Route32_Text_Sign2:
	.string "RUINAS ALFA\n"
	.string "ENTRADA ESTE$"

Route32_Text_Sign3:
	.string "CUEVA UNIÓN\n"
	.string "ADELANTE$"
