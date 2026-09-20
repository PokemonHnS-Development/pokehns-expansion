@ All the LOCALID constants used in this file are essentially redundant.
@ They're all used to have the NPC the player talked to turn back so they're facing
@ their original direction (because they're watching/participating in the contests).
@ They could all be substituted for VAR_LAST_TALKED.
LilycoveCity_ContestHall_MapScripts::
	.byte 0

LilycoveCity_ContestHall_EventScript_Boy1::
	msgbox LilycoveCity_ContestHall_Text_TodayWonSmartnessContest, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Boy2::
	msgbox LilycoveCity_ContestHall_Text_EnteredBunchOfContests, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Girl::
	msgbox LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Sailor::
	msgbox LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_SmartContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EnteredWrongContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_RaisedMonToBeSmart, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience1::
	msgbox LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_StillLoveSmartnessContests, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_OverdidGrooming, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestMC::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_InTheMiddleOfContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestJudge::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant1::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyAzurillWasDistracted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_NeverWonBattleButContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PetalDanceIsMarvel, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant4::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience1::
	lockall
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_ContestHall_Text_MyChildIsInContest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	delay 25
	msgbox LilycoveCity_ContestHall_Text_ComeOnDear, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience2::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience3::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyStageSign::
	msgbox LilycoveCity_ContestHall_Text_BeautyContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_CuteStageSign::
	msgbox LilycoveCity_ContestHall_Text_CuteContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartStageSign::
	msgbox LilycoveCity_ContestHall_Text_SmartContestStage, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_Text_TodayWonSmartnessContest:
	.string "Este POKéMON ganó el CONCURSO BELLEZA\n"
	.string "aquí antes.\p"
	.string "Bueno, ¿sabes qué? Hoy logré que\n"
	.string "¡ganara un CONCURSO INTELIGENCIA!\p"
	.string "Mis habilidades me asustan hasta a mí…$"

LilycoveCity_ContestHall_Text_EnteredBunchOfContests:
	.string "He entrado en varios CONCURSOS,\n"
	.string "así que veo cómo funcionan las cosas.\p"
	.string "Si estás en un CONCURSO GENIALIDAD,\n"
	.string "Los buenos movimientos son atractivos.\p"
	.string "Pero los inteligentes y lindos\n"
	.string "no funcionan tan bien, por ejemplo.$"

LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks:
	.string "Aquel joven que ganó hace poco tenía\n"
	.string "muchos {POKEBLOCK} diferentes.\p"
	.string "¿Podrías ganar si tuvieras tantos\n"
	.string "de esos objetos?$"

LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous:
	.string "¡Vaya, este lugar es enorme!\p"
	.string "La tensión en el aire... No es\n"
	.string "como un CONTEST de pueblo.$"

LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal:
	.string "MC: ¡Bien, POKéMON inteligentes y\n"
	.string "sus ENTRENADORES, están listos?!\p"
	.string "¡Den su mejor espectáculo!\n"
	.string "¡A lucirse!$"

LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest:
	.string "JUEZ: ¿Disfrutan este CONTEST?\p"
	.string "Vuelve con tres amigos y\n"
	.string "¡Todos pueden entrar a un CONCURSO!$"

LilycoveCity_ContestHall_Text_EnteredWrongContest:
	.string "Ayayayay...\n"
	.string "Entré al CONCURSO equivocado.\p"
	.string "Metí a este POKéMON rudo en\n"
	.string "el CONCURSO de INTELIGENCIA...\p"
	.string "¡Vamos, impresiónalos con un\n"
	.string "ROMPE ROCAS inteligente!$"

LilycoveCity_ContestHall_Text_RaisedMonToBeSmart:
	.string "Pasé muchos años y toda mi\n"
	.string "sabiduría criando a este POKéMON\l"
	.string "para que sea inteligente.\p"
	.string "No será vencido fácilmente por el\n"
	.string "POKéMON de un novato.\p"
	.string "Querida esposa, ¿estás viendo esto?$"

LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext:
	.string "¡Ahí está!\p"
	.string "Si mi POKéMON hace un movimiento\n"
	.string "astuto, ¡el público se emocionará!$"

LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife:
	.string "¡Oh, cielos, no!\p"
	.string "¡El VIDA DRENAJE de mi lindo ZUBAT\n"
	.string "es tan tierno que no dejé de usarlo!\p"
	.string "¡Pero esta gente malvada no lo\n"
	.string "aprecia para nada!$"

LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa:
	.string "Kiyaaah! You're beautiful, Grandpa!$"

LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves:
	.string "Incluso cuando los ENTRENADORES usan\n"
	.string "el mismo tipo de POKéMON, todos usan\l"
	.string "distintos movimientos para lucirse.\p"
	.string "Es justo como ocurre cuando la gente\n"
	.string "tiene estilos de combate distintos.$"

LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers:
	.string "Creo que los POKéMON se ven más\n"
	.string "listos que sus ENTRENADORES. Mucho.$"

LilycoveCity_ContestHall_Text_StillLoveSmartnessContests:
	.string "Al final, sigo amando los\n"
	.string "CONCURSOS DE INTELIGENCIA.\p"
	.string "Ese color verde intelectual...\n"
	.string "Es tan... tan... genial.$"

LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest:
	.string "MC: ¿También entrarás al CONCURSO\n"
	.string "DE BELLEZA? ¡Buena suerte!$"

LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty:
	.string "JUEZ: Ah, cada POKéMON aquí es\n"
	.string "¡un modelo de belleza pura!\p"
	.string "¡Vaya, casi olvido calificarlos!$"

LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty:
	.string "Un POKéMON tan hermoso...\n"
	.string "No hay otro igual.\p"
	.string "Todos mirarán fijamente\n"
	.string "mi belleza.$"

LilycoveCity_ContestHall_Text_OverdidGrooming:
	.string "¡Buaaaa!\p"
	.string "Cepillé y arreglé a mi POKéMON\n"
	.string "con cuidado para este CONCURSO...\p"
	.string "Pero me excedí...\n"
	.string "¡El pelaje quedó todo erizado!\p"
	.string "¿Qué debo hacer?$"

LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam:
	.string "Este RAYO AURORA es deslumbrante,\n"
	.string "el JUEZ no podrá verlo.\p"
	.string "Eh, espera un segundo...\n"
	.string "¡Entonces no tendrá sentido!$"

LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe:
	.string "Este lindo POKéMON se parece\n"
	.string "a mí cuando era joven.\p"
	.string "Justo al decir eso, mi esposo\n"
	.string "escupió el café que bebía.\p"
	.string "¿Dije algo gracioso?$"

LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy:
	.string "Sabes, si gano un CONCURSO\n"
	.string "de BELLEZA, claro que me\l"
	.string "hace feliz. Más de lo normal.$"

LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon:
	.string "¡Jajajajaja!\p"
	.string "¡Mira todos esos hermosos\n"
	.string "POKéMON!\l"
	.string "¡Me encanta este tipo de brillo!$"

LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone:
	.string "No siempre se gana solo con la\n"
	.string "belleza.\p"
	.string "Debes cuidar a tu POKéMON para que\n"
	.string "brille tanto como el mío.$"

LilycoveCity_ContestHall_Text_InTheMiddleOfContest:
	.string "MC: ¡Oh! ¡Hola!\n"
	.string "¡Estamos en medio de un CONCURSO!\p"
	.string "Por favor, regístrate en el mostrador\n"
	.string "y luego vuelve, ¿está bien?$"

LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals:
	.string "JUEZ: Oh, qué encantadores y lindos\n"
	.string "¡atractivos!\p"
	.string "¡Cielos! ¡Qué atractivo de\n"
	.string "DEPORTES ACUÁTICOS tan adorable!$"

LilycoveCity_ContestHall_Text_MyAzurillWasDistracted:
	.string "Oh, no... Mi dulce AZURILL se\n"
	.string "distrajo con otro POKéMON.$"

LilycoveCity_ContestHall_Text_NeverWonBattleButContest:
	.string "Mi POKéMON nunca ganó una batalla,\n"
	.string "¡pero en un CONCURSO, cuidado!$"

LilycoveCity_ContestHall_Text_PetalDanceIsMarvel:
	.string "El DANZA PÉTALO de mi POKéMON es\n"
	.string "una maravilla de elegancia.\p"
	.string "No dejaré que nadie interrumpa su\n"
	.string "actuación.$"

LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter:
	.string "Los POKéMON de todos son muy lindos.\p"
	.string "Pero si mi POKéMON hiciera\n"
	.string "una pose linda...\p"
	.string "estoy segura de que sería\n"
	.string "mucho más linda que las demás.$"

LilycoveCity_ContestHall_Text_MyChildIsInContest:
	.string "Mi hijo está en este CONCURSO.$"

LilycoveCity_ContestHall_Text_ComeOnDear:
	.string "¡Vamos, cariño! ¡Tú puedes!\n"
	.string "¡Tu POKéMON es el mejor!$"

LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest:
	.string "Creo que esa chica de allá es\n"
	.string "la más linda de todas.\p"
	.string "¿Qué dices? ¿Juzgan a los\n"
	.string "POKéMON por su apariencia?$"

LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn:
	.string "Oh, al ver tantos POKéMON lindos,\n"
	.string "¡Dan ganas de tener uno propio!\p"
	.string "¡Iré a capturar algunos!$"

LilycoveCity_ContestHall_Text_BeautyContestStage:
	.string "ESCENARIO DE BELLEZA\n"
	.string "¡Déjate llevar por su belleza!$"

LilycoveCity_ContestHall_Text_CuteContestStage:
	.string "ESCENARIO DE LINURA\n"
	.string "¡Déjate cautivar por su dulzura!$"

LilycoveCity_ContestHall_Text_SmartContestStage:
	.string "ESCENARIO DE INTELIGENCIA\n"
	.string "¡Impresionate con su ingenio!$"

