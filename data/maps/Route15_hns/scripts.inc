Route15_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route15_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route15_OnTransition:
	callnative SetTimeBasedEncounters
	end

Route15_EventScript_Colette::
	trainerbattle_single TRAINER_COLETTE_HNS, Route15_Text_TeacherColetteSeen, Route15_Text_TeacherColetteBeaten
	msgbox Route15_Text_TeacherColetteAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_Hillary::
	trainerbattle_single TRAINER_HILLARY_HNS, Route15_Text_TeacherHillarySeen, Route15_Text_TeacherHillaryBeaten, Route15_EventScript_RegisterHillary
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route15_EventScript_RematchHillary
	msgbox Route15_Text_TeacherHillaryAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_RegisterHillary::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route15_Text_HillaryRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_HILLARY_HNS
	release
	end

Route15_EventScript_RematchHillary::
	trainerbattle_rematch TRAINER_HILLARY_HNS, Route15_Text_HillaryRematchIntro, Route15_Text_HillaryRematchDefeat
	msgbox Route15_Text_HillaryPostRematch, MSGBOX_AUTOCLOSE
	goto_if_defeated TRAINER_HILLARY_2_HNS, Route15_EventScript_RematchHillaryTryGiveItem
	end

Route15_EventScript_RematchHillaryTryGiveItem::
	checkitem ITEM_TM_ENERGY_BALL
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NoOp
	giveitem ITEM_TM_ENERGY_BALL
	closemessage
	end

Route15_EventScript_Kipp::
	trainerbattle_single TRAINER_KIPP_HNS, Route15_Text_SchoolboyKippSeen, Route15_Text_SchoolboyKippBeaten
	msgbox Route15_Text_SchoolboyKippAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_Tommy::
	trainerbattle_single TRAINER_TOMMY_HNS, Route15_Text_SchoolboyTommySeen, Route15_Text_SchoolboyTommyBeaten
	msgbox Route15_Text_SchoolboyTommyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_Johnny::
	trainerbattle_single TRAINER_JOHNNY_HNS, Route15_Text_SchoolboyJohnnySeen, Route15_Text_SchoolboyJohnnyBeaten
	msgbox Route15_Text_SchoolboyJohnnyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_Billy::
	trainerbattle_single TRAINER_BILLY_HNS, Route15_Text_SchoolboyBillySeen, Route15_Text_SchoolboyBillyBeaten, Route15_EventScript_RegisterBilly
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route15_EventScript_RematchBilly
	msgbox Route15_Text_SchoolboyBillyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route15_EventScript_RegisterBilly::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route15_Text_BillyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_BILLY_HNS
	release
	end

Route15_EventScript_RematchBilly::
	trainerbattle_rematch TRAINER_BILLY_HNS, Route15_Text_BillyRematchIntro, Route15_Text_BillyRematchDefeat
	msgbox Route15_Text_BillyPostRematch, MSGBOX_AUTOCLOSE
	goto_if_defeated TRAINER_BILLY_2_HNS, Route15_EventScript_RematchBillyTryGiveItem
	end

Route15_EventScript_RematchBillyTryGiveItem::
	checkitem ITEM_TM_FACADE
	goto_if_eq VAR_RESULT, TRUE, Common_EventScript_NoOp
	giveitem ITEM_TM_FACADE
	closemessage
	end

Route15_EventScript_Sign::
	msgbox Route15_Text_Sign, MSGBOX_SIGN
	end

Route15_EventScript_PPup::
	finditem ITEM_PP_UP
	end

Route15_Text_TeacherColetteSeen:
	.string "¿Has olvidado algo?$"

Route15_Text_TeacherColetteBeaten:
	.string "Kyaaah!$"

Route15_Text_TeacherColetteAfterBattle:
	.string "Antes de ser maestra, solía\n"
	.string "olvidar muchas cosas.$"

Route15_Text_TeacherHillarySeen:
	.string "En días soleados, creo que los\n"
	.string "niños prefieren jugar en el patio\l"
	.string "que estudiar en clase.$"

Route15_Text_TeacherHillaryBeaten:
	.string "No quería perder…$"

Route15_Text_TeacherHillaryAfterBattle:
	.string "Estudiar es importante, pero el\n"
	.string "ejercicio es igual de vital.$"

Route15_Text_HillaryRegister:
	.string "¡Me has dado una lección!\n"
	.string "¿Me das tu número?$"

Route15_Text_HillaryRematchIntro:
	.string "¡Esta vez te daré una lección!$"

Route15_Text_HillaryRematchDefeat:
	.string "Toca empezar de cero...$"

Route15_Text_HillaryPostRematch:
	.string "Entrenar POKéMON es justo como\n"
	.string "educar niños. ¡Paciencia!$"

Route15_Text_SchoolboyKippSeen:
	.string "Espera. Tengo que llamar a mi mamá.$"

Route15_Text_SchoolboyKippBeaten:
	.string "¡Perdón, mamá! ¡Me vencieron!$"

Route15_Text_SchoolboyKippAfterBattle:
	.string "Mi mamá se preocupa tanto que\n"
	.string "debo llamarla a cada rato.$"

Route15_Text_SchoolboyTommySeen:
	.string "¡Batallamos! ¡No perderé!$"

Route15_Text_SchoolboyTommyBeaten:
	.string "¡Olvidé hacer mi tarea!$"

Route15_Text_SchoolboyTommyAfterBattle:
	.string "¡Sayonara! Lo acabo de aprender en\n"
	.string "mi clase de japonés.$"

Route15_Text_SchoolboyJohnnySeen:
	.string "Estamos de excursión a la TORRE\n"
	.string "RADIO de LAVANDA por estudios.$"

Route15_Text_SchoolboyJohnnyBeaten:
	.string "¡Eres durísimo!$"

Route15_Text_SchoolboyJohnnyAfterBattle:
	.string "Estoy cansado de caminar. Necesito\n"
	.string "tomar un descanso.$"

Route15_Text_SchoolboyBillySeen:
	.string "My favorite class is Gym!$"

Route15_Text_SchoolboyBillyBeaten:
	.string "¡Oh, no! ¿Cómo pude perder?$"

Route15_Text_SchoolboyBillyAfterBattle:
	.string "Si los POKéMON fueran una materia\n"
	.string "escolar, ¡sería el mejor!$"

Route15_Text_BillyRegister:
	.string "Debí prestar más atención en clase.\n"
	.string "¿Me das tu número?$"

Route15_Text_BillyRematchIntro:
	.string "¡He estado estudiando duro!\n"
	.string "¡Déjame mostrarte lo que aprendí!$"

Route15_Text_BillyRematchDefeat:
	.string "Debo estudiar más…$"

Route15_Text_BillyPostRematch:
	.string "Saber libros no lo es todo.\n"
	.string "¡Necesito experiencia en combate!$"

Route15_Text_Sign:
	.string "RUTA 15\p"
	.string "CIUDAD FUXIA - PUEBLO LAVANDA$"

