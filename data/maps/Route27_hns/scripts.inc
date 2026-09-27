Route27_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route27_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route27_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route27_EventScript_BaobaCall::
	setspeaker Route27_Text_BaobaName
	pokenavcall BlackthornCity_Text_BaobaCall
	waitmessage
	delay 30
	setflag FLAG_SAFARI_ZONE_WEST_EXPANSION
    setvar VAR_ROUTE27_BAOBA_CALL, 1
	end

Route27_Text_BaobaName:
	.string "BAOBA$"

Route27_EventScript_FirstSteps::
    lock
    playse SE_PIN
    setflag FLAG_VISITED_KANTO
    applymovement2 LOCALID_ROUTE27_FATMAN, Common_Movement_ExclamationMark
    turnobject LOCALID_ROUTE27_FATMAN, DIR_WEST
    delay 30
    getplayerxy VAR_TEMP_0, VAR_TEMP_1
    call_if_eq VAR_TEMP_1, 24, Route27_EventScript_FirstStepsWalkTop
    call_if_eq VAR_TEMP_1, 25, Route27_EventScript_FirstStepsWalkBot

    msgbox Route27_Text_FisherHey, MSGBOX_DEFAULT
    msgbox Route27_Text_FisherMessage, MSGBOX_DEFAULT
    closemessage
    turnobject LOCALID_ROUTE27_FATMAN, DIR_SOUTH

    @integrated flagheap
    setflag FLAG_HIDE_VICTORY_ROAD_SILVER
    setflag FLAG_HIDE_INDIGO_PLATEAU_SILVER
    setflag FLAG_HIDE_INDIGO_PLATEAU_MARY_OAK
    
    clearflag FLAG_GOT_TM_SANDSTORM
    clearflag FLAG_INDIGOJUNCTION_HIDE_SILVER_GUARD
    clearflag FLAG_INDIGOJUNCTION_HIDE_KANTO_GUARD

    setvar VAR_ROUTE27_STATE, 1
    release
    end

Route27_EventScript_FirstStepsWalkTop::
    applymovement2 LOCALID_ROUTE27_FATMAN, Route27_Movement_WalkTop
    waitmovement 0
    return
Route27_EventScript_FirstStepsWalkBot::
    applymovement2 LOCALID_ROUTE27_FATMAN, Route27_Movement_WalkBot
    waitmovement 0
    return

Route27_Movement_WalkTop:
    face_left
    walk_left
    step_end

Route27_Movement_WalkBot:
    walk_down
    walk_left
    step_end

Route27_EventScript_Item_Moonstone::
    finditem ITEM_MOON_STONE
    end

Route27_EventScript_Item_RareCandy::
    finditem ITEM_RARE_CANDY
    end

Route27_EventScript_Item_DragonClaw::
    finditem ITEM_TM_DRAGON_CLAW
    end

Route27_EventScript_Item_Destiny_Knot::
    finditem ITEM_DESTINY_KNOT
    end

Route27_EventScript_Fatman::
    msgbox Route27_Text_FisherMessage, MSGBOX_NPC
    end

Route27_EventScript_Blake::
	trainerbattle_single TRAINER_BLAKE_HNS, Route27_Text_CooltrainermBlakeSeen, Route27_Text_CooltrainermBlakeBeaten
	msgbox Route27_Text_CooltrainermBlakeAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Brian::
	trainerbattle_single TRAINER_BRIAN_HNS, Route27_Text_CooltrainermBrianSeen, Route27_Text_CooltrainermBrianBeaten
	msgbox Route27_Text_CooltrainermBrianAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Reena::
	trainerbattle_single TRAINER_REENA_HNS, Route27_Text_CooltrainerfReenaSeen, Route27_Text_CooltrainerfReenaBeaten, Route27_EventScript_RegisterReena
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route27_EventScript_RematchReena
	msgbox Route27_Text_CooltrainerfReenaAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_RegisterReena::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route27_Text_ReenaRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_REENA_HNS
	release
	end

Route27_EventScript_RematchReena::
	trainerbattle_rematch TRAINER_REENA_HNS, Route27_Text_ReenaRematchIntro, Route27_Text_ReenaRematchDefeat
	msgbox Route27_Text_ReenaPostRematch, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Megan::
	trainerbattle_single TRAINER_MEGAN_HNS, Route27_Text_CooltrainerfMeganSeen, Route27_Text_CooltrainerfMeganBeaten
	msgbox Route27_Text_CooltrainerfMeganAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Gilbert::
	trainerbattle_single TRAINER_GILBERT_HNS, Route27_Text_PsychicGilbertSeen, Route27_Text_PsychicGilbertBeaten
	msgbox Route27_Text_PsychicGilbertAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Jose::
	trainerbattle_single TRAINER_JOSE_HNS, Route27_Text_BirdKeeperJoseSeen, Route27_Text_BirdKeeperJoseBeaten, Route27_EventScript_RegisterJose
	goto_if_set FLAG_JOSE_HAS_ITEM_HNS, Route27_EventScript_JoseGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route27_EventScript_RematchJose
	msgbox Route27_Text_BirdKeeperJoseAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_RegisterJose::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route27_Text_JoseRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOSE_HNS
	release
	end

Route27_EventScript_RematchJose::
	trainerbattle_rematch TRAINER_JOSE_HNS, Route27_Text_JoseRematchIntro, Route27_Text_JoseRematchDefeat
	msgbox Route27_Text_JosePostRematch, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_JoseGiveItem::
	msgbox Route27_Text_JoseHasItem, MSGBOX_DEFAULT
	giveitem VAR_JOSE_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, Route27_EventScript_JoseNoRoom
	clearflag FLAG_JOSE_HAS_ITEM_HNS
	msgbox Route27_Text_JoseGaveItem, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_JoseNoRoom::
	msgbox Route27_Text_JoseNoRoom, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_Scott::
	trainerbattle_single TRAINER_SCOTT_HNS, Route27_Text_FisherScottSeen, Route27_Text_FisherScottBeaten
	msgbox Route27_Text_FisherScottAfter, MSGBOX_AUTOCLOSE
	end

Route27_EventScript_TohjoFallsSign::
    msgbox TohjoFalls_Text_Sign, MSGBOX_SIGN
    end

Route27_Text_FisherHey:
    .string "¡Oye!$"

Route27_Text_FisherMessage:
    .string "¿Sabes lo que acabas de hacer?\p"
    .string "Has dado tu primer paso en\n"
    .string "KANTO.\p"
    .string "Mira el MAPA del POKéGEAR.$"

Route27_Text_CooltrainermBlakeSeen:
    .string "Pareces bastante fuerte.\n"
    .string "¡Lucha contra mí!$"

Route27_Text_CooltrainermBlakeBeaten:
    .string "¡Au!$"

Route27_Text_CooltrainermBlakeAfter:
    .string "Si vences en este duro viaje,\n"
    .string "¡la verdad será revelada!\p"
    .string "Je, perdón, solo quería decir\n"
    .string "algo genial.$"

Route27_Text_CooltrainermBrianSeen:
    .string "¿Mmm? Eres bueno, ¿no?$"

Route27_Text_CooltrainermBrianBeaten:
    .string "¡Como lo pensaba!$"

Route27_Text_CooltrainermBrianAfter:
    .string "Un buen entrenador reconoce a\n"
    .string "otros buenos entrenadores.$"

Route27_Text_CooltrainerfReenaSeen:
    .string "No deberías subestimar a los\n"
    .string "POKéMON salvajes de esta zona.$"

Route27_Text_CooltrainerfReenaBeaten:
    .string "¡Oh! ¡Eres demasiado fuerte!$"

Route27_Text_CooltrainerfReenaAfter:
    .string "Solo eres un niño, pero tú\n"
    .string "tampoco debes subestimarse.$"

Route27_Text_ReenaRegister:
    .string "Solo eres un niño, pero tú\n"
    .string "tampoco debes subestimarse.$"

Route27_Text_ReenaRematchIntro:
    .string "No deberías subestimar a los\n"
    .string "POKéMON salvajes de esta zona.$"

Route27_Text_ReenaRematchDefeat:
    .string "¡Oh! ¡Eres demasiado fuerte!$"

Route27_Text_ReenaPostRematch:
    .string "Solo eres un niño, pero tú\n"
    .string "tampoco debes subestimarse.$"

Route27_Text_CooltrainerfMeganSeen:
    .string "Es raro ver a alguien por aquí.\p"
    .string "¿Entrenas por tu cuenta?$"

Route27_Text_CooltrainerfMeganBeaten:
    .string "¡Oh! ¡Eres realmente fuerte!$"

Route27_Text_CooltrainerfMeganAfter:
    .string "Estoy revisando el antes y el\n"
    .string "POKéMON evolución.\p"
    .string "La evolución realmente hace\n"
    .string "POKéMON más fuertes.\p"
    .string "Pero las formas evolucionadas\n"
    .string "aprenden ataques más tarde.$"

Route27_Text_PsychicGilbertSeen:
    .string "¡No digas nada!\p"
    .string "Déjame adivinar qué piensas.\p"
    .string "Mmmmmmm...\p"
    .string "¡Lo tengo! ¡Estás en el reto de\n"
    .string "la LIGA POKéMON!$"

Route27_Text_PsychicGilbertBeaten:
    .string "¡Eres demasiado!$"

Route27_Text_PsychicGilbertAfter:
    .string "Con tu habilidad, te irá bien en\n"
    .string "LIGA.\p"
    .string "Eso es lo que dice mi premonición.$"

Route27_Text_BirdKeeperJoseSeen:
    .string "¡Pío! ¡Pío! ¡Piopío!$"

Route27_Text_BirdKeeperJoseBeaten:
    .string "¡Pío!$"

Route27_Text_BirdKeeperJoseAfter:
    .string "Los CUIDADORES de aves como yo\n"
    .string "imitan silbidos para mandar.$"

Route27_Text_JoseRegister:
    .string "Los CUIDADORES de aves como yo\n"
    .string "imitan silbidos para mandar.$"

Route27_Text_JoseRematchIntro:
    .string "¡Pío! ¡Pío! ¡Piopío!$"

Route27_Text_JoseRematchDefeat:
    .string "¡Pío!$"

Route27_Text_JosePostRematch:
    .string "Los CUIDADORES de aves como yo\n"
    .string "imitan silbidos para mandar.$"

Route27_Text_JoseHasItem:
    .string "¡Oye! Encontré algo brillante\n"
    .string "mientras observaba aves.\p"
    .string "¡Toma, puedes quedártelo!$"

Route27_Text_JoseGaveItem:
    .string "Encuentro todo tipo de cosas\n"
    .string "aquí en la RUTA 27.\p"
    .string "¡Te avisaré si encuentro\n"
    .string "algo más!$"

Route27_Text_JoseNoRoom:
    .string "Hmm, tu BOLSA está llena.\p"
    .string "Vuelve cuando tengas espacio.$"

TohjoFalls_Text_Sign:
    .string "CASCADAS TOHJO\p"
    .string "EL VÍNCULO ENTRE KANTO Y JOHTO$"

Route27_Text_FisherScottSeen:
    .string "¡Me siento genial hoy!\p"
    .string "Siento que podría vencer hasta al\n"
    .string "¡CAMPEÓN DE LA LIGA!$"

Route27_Text_FisherScottBeaten:
    .string "¡No! ¡No en esta batalla!$"

Route27_Text_FisherScottAfter:
    .string "Como al pescar, todo acaba en\n"
    .string "POKéMON si te rindes.$"
