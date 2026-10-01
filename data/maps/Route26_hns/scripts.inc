Route26_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route26_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route26_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route26_EventScript_Jake::
	trainerbattle_single TRAINER_JAKE_HNS, Route26_Text_CooltrainermJakeSeen, Route26_Text_CooltrainermJakeBeaten
	msgbox Route26_Text_CooltrainermJakeAfter, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_Gaven::
	trainerbattle_single TRAINER_GAVEN_HNS, Route26_Text_CooltrainermGavenSeen, Route26_Text_CooltrainermGavenBeaten, Route26_EventScript_RegisterGaven
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route26_EventScript_RematchGaven
	msgbox Route26_Text_CooltrainermGavenAfter, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_RegisterGaven::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route26_Text_GavenRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_GAVEN_HNS
	release
	end

Route26_EventScript_RematchGaven::
	trainerbattle_rematch TRAINER_GAVEN_HNS, Route26_Text_GavenRematchIntro, Route26_Text_GavenRematchDefeat
	msgbox Route26_Text_GavenPostRematch, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_Joyce::
	trainerbattle_single TRAINER_JOYCE_HNS, Route26_Text_CooltrainerfJoyceSeen, Route26_Text_CooltrainerfJoyceBeaten
	msgbox Route26_Text_CooltrainerfJoyceAfter, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_Beth::
	trainerbattle_single TRAINER_BETH_HNS, Route26_Text_CooltrainerfBethSeen, Route26_Text_CooltrainerfBethBeaten, Route26_EventScript_RegisterBeth
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route26_EventScript_RematchBeth
	msgbox Route26_Text_CooltrainerfBethAfter, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_RegisterBeth::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route26_Text_BethRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_BETH_HNS
	release
	end

Route26_EventScript_RematchBeth::
	trainerbattle_rematch TRAINER_BETH_HNS, Route26_Text_BethRematchIntro, Route26_Text_BethRematchDefeat
	msgbox Route26_Text_BethPostRematch, MSGBOX_AUTOCLOSE
	end

Route26_EventScript_Richard::
	trainerbattle_single TRAINER_RICHARD_HNS, Route26_Text_PsychicRichardSeen, Route26_Text_PsychicRichardBeaten
	msgbox Route26_Text_PsychicRichardAfter, MSGBOX_AUTOCLOSE
	end

Route26_Text_CooltrainermJakeSeen:
    .string "Hago mis preparativos finales\n"
    .string "para la LIGA POKéMON.$"

Route26_Text_CooltrainermJakeBeaten:
    .string "¡Lo arruiné!$"

Route26_Text_CooltrainermJakeAfter:
    .string "Será difícil ganar en la\n"
    .string "LIGA.\p"
    .string "Debo entrenar un poco más.\p"
    .string "Oigo que el ALTO MANDO de la LIGA\n"
    .string "es más fuerte que los LÍDERES.$"

Route26_Text_CooltrainermGavenSeen:
    .string "Al vivir batallas difíciles,\n"
    .string "ganas poder.$"

Route26_Text_CooltrainermGavenBeaten:
    .string "¡Ah! ¡La vida es aún más dura!$"

Route26_Text_CooltrainermGavenAfter:
    .string "Para ir a la LIGA POKéMON, debes\n"
    .string "para cruzar la VIA TRIUNFO.\p"
    .string "Pero la VIA TRIUNFO es dura.\p"
    .string "¡Casi nadie va por ahí!$"

Route26_Text_GavenRegister:
    .string "Para ir a la LIGA POKéMON, debes\n"
    .string "para cruzar la VIA TRIUNFO.\p"
    .string "Pero la VIA TRIUNFO es dura.\p"
    .string "¡Casi nadie va por ahí!$"

Route26_Text_GavenRematchIntro:
    .string "Al vivir batallas difíciles,\n"
    .string "ganas poder.$"

Route26_Text_GavenRematchDefeat:
    .string "¡Ah! ¡La vida es aún más dura!$"

Route26_Text_GavenPostRematch:
    .string "Para ir a la LIGA POKéMON, debes\n"
    .string "para cruzar la VIA TRIUNFO.\p"
    .string "Pero la VIA TRIUNFO es dura.\p"
    .string "¡Casi nadie va por ahí!$"

Route26_Text_CooltrainerfJoyceSeen:
    .string "Ya que has llegado tan lejos,\n"
    .string "debes ser muy bueno.\p"
    .string "¡Voy a darlo todo en esta\n"
    .string "batalla!$"

Route26_Text_CooltrainerfJoyceBeaten:
    .string "¡No! ¡No puedo creerlo!$"

Route26_Text_CooltrainerfJoyceAfter:
    .string "Vencí a ocho LÍDERES de GIMNASIO,\n"
    .string "así que me sentía confiado.\p"
    .string "Debo esforzarme más la próxima vez.$"

Route26_Text_CooltrainerfBethSeen:
    .string "Perdí contra {RIVAL}.\p"
    .string "Era muy fuerte, pero...\p"
    .string "Era como si tuviera que ganar\n"
    .string "a cualquier precio.\p"
    .string "Sentí pena por sus POKéMON.$"

Route26_Text_CooltrainerfBethBeaten:
    .string "POKéMON aren't tools of war.$"

Route26_Text_CooltrainerfBethAfter:
    .string "Los POKéMON son compañeros\n"
    .string "invaluables de por vida.$"

Route26_Text_BethRegister:
    .string "Los POKéMON son invaluables,\n"
    .string "invaluables de por vida.$"

Route26_Text_BethRematchIntro:
    .string "Perdí contra {RIVAL}.\p"
    .string "¡Pero no perderé contra ti!$"

Route26_Text_BethRematchDefeat:
    .string "POKéMON aren't tools of war.$"

Route26_Text_BethPostRematch:
    .string "Los POKéMON son invaluables,\n"
    .string "invaluables de por vida.$"

Route26_Text_PsychicRichardSeen:
    .string "¡Vaya, mira todas esas MEDALLAS!\n"
    .string "Estoy impresionado.\p"
    .string "Pero no te basta con eso\n"
    .string "los coleccionas, ¿verdad?$"

Route26_Text_PsychicRichardBeaten:
    .string "Good battle!$"

Route26_Text_PsychicRichardAfter:
    .string "La gente y los POKéMON crecen con\n"
    .string "sus experiencias.\p"
    .string "No te vuelvas flojo ni confiado.$"

Route26_Text_Sign:
    .string "RUTA 26\p"
    .string "LIGA POKéMON\n"
    .string "PUERTA DE ACCESO$"

