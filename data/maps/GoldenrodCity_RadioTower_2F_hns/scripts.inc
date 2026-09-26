GoldenrodCity_RadioTower_2F_hns_MapScripts::
	.byte 0

GoldenrodRaidoTower2_EventScript_Grunt3::
	trainerbattle_single TRAINER_GRUNT_3_HNS, GoldenrodCity_RadioTower_2F_Text_GruntM4Seen, GoldenrodCity_RadioTower_2F_Text_GruntM4Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntM4After, MSGBOX_AUTOCLOSE
	end
GoldenrodRaidoTower2_EventScript_Grunt4::
	trainerbattle_single TRAINER_GRUNT_4_HNS, GoldenrodCity_RadioTower_2F_Text_GruntM5Seen, GoldenrodCity_RadioTower_2F_Text_GruntM5Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntM5After, MSGBOX_AUTOCLOSE
	end
GoldenrodRaidoTower2_EventScript_Grunt5::
	trainerbattle_single TRAINER_GRUNT_5_HNS, GoldenrodCity_RadioTower_2F_Text_GruntM6Seen, GoldenrodCity_RadioTower_2F_Text_GruntM6Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntM6After, MSGBOX_AUTOCLOSE
	end
GoldenrodRaidoTower2_EventScript_GruntF2::
	trainerbattle_single TRAINER_GRUNT_26_HNS, GoldenrodCity_RadioTower_2F_Text_GruntF2Seen, GoldenrodCity_RadioTower_2F_Text_GruntF2Beaten
	msgbox GoldenrodCity_RadioTower_2F_Text_GruntF2After, MSGBOX_AUTOCLOSE
	end

GoldenrodCity_RadioTower_2F_EventScript_Sign1::
	lock
	msgbox GoldenrodCity_RadioTower_2F_Text_SalesSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Sign2::
	lock
	msgbox GoldenrodCity_RadioTower_2F_Text_OakTalkSign, MSGBOX_SIGN
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Boy::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_2F_Text_SuperNerd, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Policeman::
	lock
	faceplayer
	msgbox GoldenrodCity_RadioTower_2F_Text_Policeman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Buena::
	lock
	faceplayer
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_RadioTower_2F_EventScript_BuenaRocket
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 7, GoldenrodCity_RadioTower_2F_EventScript_BuenaRocket
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 8, GoldenrodCity_RadioTower_2F_EventScript_BuenaRocket
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 9, GoldenrodCity_RadioTower_2F_EventScript_BuenaRocket
	goto_if_set FLAG_DAILY_BUENAS_PASSWORD_GUESSED, GoldenrodCity_RadioTower_2F_EventScript_BuenaAlreadyPlayed
	goto_if_unset FLAG_DAILY_BUENAS_PASSWORD, GoldenrodCity_RadioTower_2F_EventScript_BuenaNoShow
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaAskPassword, MSGBOX_DEFAULT
	special Special_BuenaPasswordShowMultichoice
	waitstate
	compare VAR_RESULT, 127
	goto_if_eq GoldenrodCity_RadioTower_2F_EventScript_BuenaCancelled
	special Special_BuenaCheckAnswer
	compare VAR_RESULT, TRUE
	goto_if_eq GoldenrodCity_RadioTower_2F_EventScript_BuenaCorrect
	setflag FLAG_DAILY_BUENAS_PASSWORD_GUESSED
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaWrong, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaCorrect::
	special Special_BuenaRollReward
	copyvar VAR_0x8004, VAR_RESULT
	checkitemspace VAR_0x8004, 1
	compare VAR_RESULT, FALSE
	goto_if_eq GoldenrodCity_RadioTower_2F_EventScript_BuenaBagFull
	giveitem VAR_0x8004, 1
	setflag FLAG_DAILY_BUENAS_PASSWORD_GUESSED
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaCorrect, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaBagFull::
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaBagFull, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaCancelled::
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaComeBack, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaAlreadyPlayed::
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaAlreadyPlayed, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaNoShow::
	msgbox GoldenrodCity_RadioTower_2F_Text_BuenaShowPromo, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_BuenaRocket::
	msgbox RadioTower2FBuenaPasswordIsHelpText, MSGBOX_DEFAULT
	closemessage
	release
	end


GoldenrodCity_RadioTower_2F_EventScript_Teacher::
	lock
	faceplayer
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 6, GoldenrodCity_RadioTower_2F_EventScript_Teacher2
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 7, GoldenrodCity_RadioTower_2F_EventScript_Teacher2 
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 8, GoldenrodCity_RadioTower_2F_EventScript_Teacher2 
	goto_if_eq VAR_GOLDENROD_CITY_STATE, 9, GoldenrodCity_RadioTower_2F_EventScript_Teacher2 
	msgbox GoldenrodCity_RadioTower_2F_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Teacher2::
	msgbox GoldenrodCity_RadioTower_2F_Text_TeacherRockets, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_RadioTower_2F_EventScript_Jigglypuff::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_JIGGLYPUFF, CRY_MODE_NORMAL
	msgbox GoldenrodCity_RadioTower_2F_Text_Jigglypuff, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RadioTower2FBuenaPasswordIsHelpText:
	.string "BUENA: ¿Eh? ¿La clave de hoy?\n"
	.string "¡AYUDA, por supuesto!$"

GoldenrodCity_RadioTower_2F_Text_SuperNerd:
	.string "Puedes escuchar la radio\n"
	.string "donde sea. ¡Sintonízala!$"

GoldenrodCity_RadioTower_2F_Text_Policeman:
	.string "Acceso restringido más allá de\n"
	.string "este punto.$"

GoldenrodCity_RadioTower_2F_Text_Teacher:
	.string "Las canciones de cuna en la radio\n"
	.string "duermen a los POKéMON.$"

GoldenrodCity_RadioTower_2F_Text_TeacherRockets:
	.string "¿Por qué querrían apoderarse de\n"
	.string "la TORRE RADIO?$"

GoldenrodCity_RadioTower_2F_Text_Jigglypuff:
	.string "JIGGLYPUFF: Jiggly...$"

GoldenrodCity_RadioTower_2F_Text_BlackBelt1:
	.string "Lo siento. Solo personal\n"
	.string "autorizado más allá de aquí.\p"
	.string "Antes no era así.\p"
	.string "Algo anda mal con el\n"
	.string "DIRECTOR...$"

GoldenrodCity_RadioTower_2F_Text_BlackBelt2:
	.string "Siéntete libre de mirar todo.\p"
	.string "El DIRECTOR volvió a ser amable,\n"
	.string "como era antes.$"

GoldenrodCity_RadioTower_2F_Text_GruntM4Seen:
	.string "Hace tres años, el TEAM ROCKET\n"
	.string "fue obligado a disolverse.\p"
	.string "¡Pero regresaremos con fuerza!$"

GoldenrodCity_RadioTower_2F_Text_GruntM4Beaten:
	.string "¡Gwah! ¡No seas tierno!$"

GoldenrodCity_RadioTower_2F_Text_GruntM4After:
	.string "¡No dejaremos que arruines los\n"
	.string "planes de nuestro regreso!$"

GoldenrodCity_RadioTower_2F_Text_GruntM5Seen:
	.string "Somos el TEAM ROCKET, los que usan\n"
	.string "a los POKéMON!\p"
	.string "¡Amamos ser malos! ¿Tienes miedo?$"

GoldenrodCity_RadioTower_2F_Text_GruntM5Beaten:
	.string "¿Te crees un héroe?$"

GoldenrodCity_RadioTower_2F_Text_GruntM5After:
	.string "No siempre somos malos. Solo hacemos\n"
	.string "lo que nos da la gana.$"

GoldenrodCity_RadioTower_2F_Text_GruntM6Seen:
	.string "¡Oye, oye! ¡Apártense!$"

GoldenrodCity_RadioTower_2F_Text_GruntM6Beaten:
	.string "Arggh. Me rindo.$"

GoldenrodCity_RadioTower_2F_Text_GruntM6After:
	.string "Nuestros EJECUTIVOS intentan tomar\n"
	.string "el control de este lugar.\p"
	.string "Tienen un gran plan. Me pregunto\n"
	.string "¿cuál será?$"

GoldenrodCity_RadioTower_2F_Text_GruntF2Seen:
	.string "¡Jajaja!\p"
	.string "Qué aburrido. Fue demasiado fácil\n"
	.string "¡apoderarme de este lugar!\p"
	.string "¡Vamos, diviérteme más!$"

GoldenrodCity_RadioTower_2F_Text_GruntF2Beaten:
	.string "¿Qui-quién eres?$"

GoldenrodCity_RadioTower_2F_Text_GruntF2After:
	.string "Me venciste, y no lo olvidaré.\n"
	.string "it!$"

GoldenrodCity_RadioTower_2F_Text_BuenaShowPromo:
	.string "BUENA: Sintoniza mi PROGRAMA\n"
	.string "¡DE CLAVES!\p"
	.string "¡Escucha para saber la clave\n"
	.string "de hoy!$"

GoldenrodCity_RadioTower_2F_Text_BuenaAskPassword:
	.string "BUENA: ¡Hola!\p"
	.string "Y bien, ¿sabes la clave de hoy?\n"
	.string "¿Contraseña?\p"
	.string "¡Bien! ¿Cuál es?$"

GoldenrodCity_RadioTower_2F_Text_BuenaCorrect:
	.string "BUENA: ¡Acertaste!\p"
	.string "¡Toma este {STR_VAR_1}\n"
	.string "como premio!$"

GoldenrodCity_RadioTower_2F_Text_BuenaWrong:
	.string "BUENA: ¡Bzzt! ¡Qué mal!\p"
	.string "¡Inténtalo mañana!$"

GoldenrodCity_RadioTower_2F_Text_BuenaComeBack:
	.string "BUENA: ¿No adivinas?\n"
	.string "¡Vuelve cuando estés listo!$"

GoldenrodCity_RadioTower_2F_Text_BuenaAlreadyPlayed:
	.string "BUENA: Ya adivinaste\n"
	.string "la contraseña de hoy!\p"
	.string "¡Sintoniza mañana otra vez!$"

GoldenrodCity_RadioTower_2F_Text_BuenaBagFull:
	.string "BUENA: Acertaste, pero\n"
	.string "¡tu MOCHILA está llena!\p"
	.string "¡Haz espacio y vuelve a\n"
	.string "hablar conmigo!$"

GoldenrodCity_RadioTower_2F_Text_SalesSign:
	.string "2F SALES$"

GoldenrodCity_RadioTower_2F_Text_OakTalkSign:
	.string "CHARLA POKéMON DEL PROF.OAK\p"
	.string "¡El show más popular del aire!$"

GoldenrodCity_RadioTower_2F_Text_PokemonRadioSign:
	.string "Anywhere, Anytime POKéMON Radio$"
