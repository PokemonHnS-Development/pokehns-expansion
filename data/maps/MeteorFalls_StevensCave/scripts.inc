MeteorFalls_StevensCave_MapScripts::
	.byte 0

MeteorFalls_StevensCave_EventScript_Steven::
	lock
	goto_if_set FLAG_DEFEATED_METEOR_FALLS_STEVEN, MeteorFalls_StevensCave_EventScript_Defeated
	waitse
	playse SE_PIN
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN, MeteorFalls_StevensCave_Text_StevenDefeat
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_METEOR_FALLS_STEVEN
	release
	end

MeteorFalls_StevensCave_EventScript_Defeated::
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	release
	end

MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst:
	.string "STEVEN: Oh, vaya, {PLAYER}{KUN}.\n"
	.string "Me asombra que supieras dónde estaba.\p"
	.string "Dime, ¿acaso piensas que soy\n"
	.string "solo un loco por las rocas?\p"
	.string "No, eso no puede ser cierto.\p"
	.string "Luchamos juntos en el\n"
	.string "CENTRO ESPACIAL DE CALORÍA.\p"
	.string "Deberías tener una idea muy clara\n"
	.string "de lo fuerte que soy.\p"
	.string "Bien, {PLAYER}{KUN}, si buscas un\n"
	.string "reto serio, ¡espera lo peor!$"

MeteorFalls_StevensCave_Text_StevenDefeat:
	.string "Tú...\n"
	.string "No sabía que serías tan fuerte...$"

MeteorFalls_StevensCave_Text_MyPredictionCameTrue:
	.string "STEVEN: Ahora que lo pienso, desde\n"
	.string "que nos vimos en la CUEVA GRANITO\l"
	.string "de CIUDAD FENIA, lo presentía.\p"
	.string "Pensé que tarde o temprano\n"
	.string "te volverías el CAMPEÓN.\p"
	.string "Mis predicciones suelen cumplirse.\p"
	.string "¿Y a dónde irás ahora?\p"
	.string "... ... ... ... ... ...\n"
	.string "... ... ... ... ... ...\p"
	.string "Fufufu, ni yo mismo sabría decirte.$"

