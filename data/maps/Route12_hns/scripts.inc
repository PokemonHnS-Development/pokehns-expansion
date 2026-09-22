Route12_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route12_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route12_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route12_EventScript_Martin::
	trainerbattle_single TRAINER_MARTIN_HNS, Route12_Text_FisherMartinSeen, Route12_Text_FisherMartinBeaten
	msgbox Route12_Text_FisherMartinAfterBattle, MSGBOX_AUTOCLOSE
	end

Route12_EventScript_Stephen::
	trainerbattle_single TRAINER_STEPHEN_HNS, Route12_Text_FisherStephenSeen, Route12_Text_FisherStephenBeaten
	msgbox Route12_Text_FisherStephenAfterBattle, MSGBOX_AUTOCLOSE
	end

Route12_EventScript_Barney::
	trainerbattle_single TRAINER_BARNEY_HNS, Route12_Text_FisherBarneySeen, Route12_Text_FisherBarneyBeaten
	msgbox Route12_Text_FisherBarneyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route12_EventScript_Kyle::
	trainerbattle_single TRAINER_KYLE_HNS, Route12_Text_FisherKyleSeen, Route12_Text_FisherKyleBeaten, Route12_EventScript_RegisterKyle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route12_EventScript_RematchKyle
	msgbox Route12_Text_FisherKyleAfterBattle, MSGBOX_AUTOCLOSE
	end

Route12_EventScript_RegisterKyle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route12_Text_KyleRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KYLE_HNS
	release
	end

Route12_EventScript_RematchKyle::
	trainerbattle_rematch TRAINER_KYLE_HNS, Route12_Text_KyleRematchIntro, Route12_Text_KyleRematchDefeat
	msgbox Route12_Text_KylePostRematch, MSGBOX_AUTOCLOSE
	goto_if_defeated TRAINER_KYLE_2_HNS, Route12_EventScript_RematchKyleTryGiveItem
	end

Route12_EventScript_RematchKyleTryGiveItem::
	checkitem ITEM_BLUE_SHARD
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NoOp
	giveitem ITEM_BLUE_SHARD
	closemessage
	end

Route12_EventScript_NewFisher::
	msgbox Route12_Text_NewFisher, MSGBOX_NPC
	end

Route12_EventScript_Elixir::
	finditem ITEM_ELIXIR
	end

Route12_EventScript_Calcium::
	finditem ITEM_CALCIUM
	end

Route12_EventScript_Magikarp::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MAGIKARP, CRY_MODE_NORMAL
	msgbox Route12_Text_Magikarp, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route12_EventScript_Tentacruel::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TENTACRUEL, CRY_MODE_NORMAL
	msgbox Route41_Text_Tentacruel, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route12_Text_Magikarp:
	.string "MAGIKARP: Kaaaarp.$"

Route12_Text_NewFisher:
	.string "Cuidado, algo feroz vive en\n"
	.string "estas aguas.$"

Route12_Text_FisherMartinSeen:
	.string "La paciencia es la clave para\n"
	.string "la pesca y los POKéMON.$"

Route12_Text_FisherMartinBeaten:
	.string "Gwaaah!$"

Route12_Text_FisherMartinAfterBattle:
	.string "Soy muy impaciente para pescar…$"

Route12_Text_FisherStephenSeen:
	.string "Me siento feliz pescando mientras\n"
	.string "escucho música en mi\l"
	.string "radio.$"

Route12_Text_FisherStephenBeaten:
	.string "¡Mi radio tonta me distrajo!$"

Route12_Text_FisherStephenAfterBattle:
	.string "¿Has escuchado la radio de KANTO?\n"
	.string "¿programas? Tenemos variedad\l"
	.string "para llegar aquí.$"

Route12_Text_FisherBarneySeen:
	.string "¿Qué es lo más importante en\n"
	.string "nuestra vida diaria?$"

Route12_Text_FisherBarneyBeaten:
	.string "¡La respuesta viene a continuación!$"

Route12_Text_FisherBarneyAfterBattle:
	.string "Creo que la electricidad es lo\n"
	.string "más importante en nuestra vida\l"
	.string "diaria.\p"
	.string "Si no, la gente no habría hecho\n"
	.string "tanto ruido cuando la CENTRAL\l"
	.string "ELÉCTRICA dejó de\l"
	.string "funcionar.$"

Route12_Text_KyleRegister:
	.string "Recordaré esto.\n"
	.string "¡Dame tu número!$"

Route12_Text_KyleRematchIntro:
	.string "¿Lo olvidaste?\n"
	.string "¡Veamos!$"

Route12_Text_KyleRematchDefeat:
	.string "Te acordaste.$"

Route12_Text_KylePostRematch:
	.string "La emoción de la batalla es casi\n"
	.string "¡tan buena como una gran pesca!$"

Route12_Text_FisherKyleSeen:
	.string "¿Te acuerdas?$"

Route12_Text_FisherKyleBeaten:
	.string "¿Entonces sí te acuerdas?$"

Route12_Text_FisherKyleAfterBattle:
	.string "El tirón que sientes en la CAÑA al\n"
	.string "atrapar un POKéMON...\p"
	.string "Es la mejor sensación para un\n"
	.string "pescador como yo.$"

Route12_EventScript_Sign::
	msgbox Route12_Text_Sign, MSGBOX_SIGN
	end

Route12_EventScript_FishingSign::
	msgbox Route12_Text_FishingSpotSign, MSGBOX_SIGN
	end

Route12_Text_Sign:
	.string "RUTA 12\p"
	.string "NORTE A PUEBLO LAVANDA$"

Route12_Text_FishingSpotSign:
	.string "FISHING SPOT$"

