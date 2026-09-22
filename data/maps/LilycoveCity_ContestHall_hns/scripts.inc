@ All the LOCALID constants used in this file are essentially redundant.
@ They're all used to have the NPC the player talked to turn back so they're facing
@ their original direction (because they're watching/participating in the contests).
@ They could all be substituted for VAR_LAST_TALKED.
LilycoveCity_ContestHall_hns_MapScripts::
	.byte 0

LilycoveCity_ContestHall_EventScript_Boy1_hns::
	msgbox LilycoveCity_ContestHall_Text_TodayWonSmartnessContest_hns, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Boy2_hns::
	msgbox LilycoveCity_ContestHall_Text_EnteredBunchOfContests_hns, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Girl_hns::
	msgbox LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks_hns, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_Sailor_hns::
	msgbox LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous_hns, MSGBOX_NPC
	end

LilycoveCity_ContestHall_EventScript_SmartContestMC_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestJudge_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant1_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EnteredWrongContest_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant2_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_RaisedMonToBeSmart_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant3_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestant4_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience1_hns::
	msgbox LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa_hns, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience2_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience3_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_SmartContestAudience4_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_StillLoveSmartnessContests_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SMART_AUDIENCE_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestMC_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestJudge_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant1_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant2_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_OverdidGrooming_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant3_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestant4_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience1_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience2_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyContestAudience3_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BEAUTY_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestMC_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_InTheMiddleOfContest_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_MC, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestJudge_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_JUDGE, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant1_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyAzurillWasDistracted_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant2_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_NeverWonBattleButContest_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant3_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_PetalDanceIsMarvel_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestant4_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_CONTESTANT_4, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience1_hns::
	lockall
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_ContestHall_Text_MyChildIsInContest_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_1, Common_Movement_FaceOriginalDirection
	waitmovement 0
	delay 25
	msgbox LilycoveCity_ContestHall_Text_ComeOnDear_hns, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience2_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_CuteContestAudience3_hns::
	lock
	faceplayer
	msgbox LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest_hns, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_CUTE_AUDIENCE_3, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_ContestHall_EventScript_BeautyStageSign_hns::
	msgbox LilycoveCity_ContestHall_Text_BeautyContestStage_hns, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_CuteStageSign_hns::
	msgbox LilycoveCity_ContestHall_Text_CuteContestStage_hns, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_EventScript_SmartStageSign_hns::
	msgbox LilycoveCity_ContestHall_Text_SmartContestStage_hns, MSGBOX_SIGN
	end

LilycoveCity_ContestHall_Text_TodayWonSmartnessContest_hns:
	.string "Este POKéMON ganó el CONCURSO BELLEZA\n"
	.string "aquí antes.\p"
	.string "Bueno, ¿sabes qué? Hoy logré que\n"
	.string "¡ganara un CONCURSO INTELIGENCIA!\p"
	.string "Mis habilidades me asustan hasta a mí...$"

LilycoveCity_ContestHall_Text_EnteredBunchOfContests_hns:
	.string "He entrado en varios\n"
	.string "así que veo cómo funcionan las cosas.\p"
	.string "Si estás en un CONCURSO GENIALIDAD,\n"
	.string "Los buenos movimientos son atractivos.\p"
	.string "Pero los inteligentes y lindos\n"
	.string "no funcionan tan bien, por ejemplo.$"

LilycoveCity_ContestHall_Text_ManWhoWonEarlierHadPokeblocks_hns:
	.string "Aquel joven que ganó hace poco tenía\n"
	.string "muchos {POKEBLOCK} diferentes.\p"
	.string "¿Podrías ganar si tuvieras tantos\n"
	.string "de esos objetos?$"

LilycoveCity_ContestHall_Text_IsntThisPlaceHumongous_hns:
	.string "¡Vaya, este lugar es enorme!\p"
	.string "La tensión en el aire... No es\n"
	.string "como un CONTEST de pueblo.$"

LilycoveCity_ContestHall_Text_GiveItBestSmartAppeal_hns:
	.string "MC: ¡Bien, POKéMON inteligentes y\n"
	.string "sus ENTRENADORES, están listos?!\p"
	.string "¡Den su mejor espectáculo!\n"
	.string "¡A lucirse!$"

LilycoveCity_ContestHall_Text_AreYouEnjoyingThisContest_hns:
	.string "JUEZ: ¿Disfrutan este CONTEST?\p"
	.string "Vuelve con tres amigos y\n"
	.string "¡Todos pueden entrar a un CONCURSO!$"

LilycoveCity_ContestHall_Text_EnteredWrongContest_hns:
	.string "Ayayayay...\n"
	.string "Entré al CONCURSO equivocado.\p"
	.string "Metí a este POKéMON rudo en\n"
	.string "el CONCURSO de INTELIGENCIA...\p"
	.string "¡Vamos, impresiónalos con un\n"
	.string "ROMPE ROCAS inteligente!$"

LilycoveCity_ContestHall_Text_RaisedMonToBeSmart_hns:
	.string "Pasé muchos años y toda mi\n"
	.string "sabiduría criando a este POKéMON\l"
	.string "para que sea inteligente.\p"
	.string "No será vencido fácilmente por el\n"
	.string "POKéMON de un novato.\p"
	.string "Querida esposa, ¿estás viendo esto?$"

LilycoveCity_ContestHall_Text_IfMonPullsSmartMoveNext_hns:
	.string "¡Ahí está!\p"
	.string "Si mi POKéMON hace un movimiento\n"
	.string "astuto, ¡el público se emocionará!$"

LilycoveCity_ContestHall_Text_DontAppreciateCuteLeechLife_hns:
	.string "¡Oh, cielos, no!\p"
	.string "¡El VIDA DRENAJE de mi lindo ZUBAT\n"
	.string "es tan tierno que no dejé de usarlo!\p"
	.string "¡Pero esta gente malvada no lo\n"
	.string "aprecia para nada!$"

LilycoveCity_ContestHall_Text_YoureBeautifulGrandpa_hns:
	.string "¡Kiyaaah! ¡Qué bello, abuelo!$"

LilycoveCity_ContestHall_Text_AllSeemToUseDifferentMoves_hns:
	.string "Incluso cuando los ENTRENADORES usan\n"
	.string "el mismo tipo de POKéMON, todos usan\l"
	.string "distintos movimientos para lucirse.\p"
	.string "Es justo como ocurre cuando la gente\n"
	.string "tiene estilos de combate distintos.$"

LilycoveCity_ContestHall_Text_PokemonSmarterThanTrainers_hns:
	.string "Creo que los POKéMON se ven más\n"
	.string "listos que sus ENTRENADORES. Mucho.$"

LilycoveCity_ContestHall_Text_StillLoveSmartnessContests_hns:
	.string "Al final, sigo amando los\n"
	.string "CONCURSOS DE INTELIGENCIA.\p"
	.string "Ese color verde intelectual...\n"
	.string "Es tan... tan... genial.$"

LilycoveCity_ContestHall_Text_AreYouEnteringBeautyContest_hns:
	.string "MC: ¿También entrarás al CONCURSO\n"
	.string "DE BELLEZA? ¡Buena suerte!$"

LilycoveCity_ContestHall_Text_EveryPokemonPristineBeauty_hns:
	.string "JUEZ: Ah, cada POKéMON aquí es\n"
	.string "¡un modelo de belleza pura!\p"
	.string "¡Vaya, casi olvido calificarlos!$"

LilycoveCity_ContestHall_Text_EyesWillBeGluedToMyBeauty_hns:
	.string "Un POKéMON tan hermoso...\n"
	.string "No hay otro igual.\p"
	.string "Todos mirarán fijamente\n"
	.string "mi belleza.$"

LilycoveCity_ContestHall_Text_OverdidGrooming_hns:
	.string "¡Buaaaa!\p"
	.string "Cepillé y arreglé a mi POKéMON\n"
	.string "con cuidado para este CONCURSO...\p"
	.string "Pero me excedí...\n"
	.string "¡El pelaje quedó todo erizado!\p"
	.string "¿Qué debo hacer?$"

LilycoveCity_ContestHall_Text_JudgeWontSeeAuroraBeam_hns:
	.string "Este RAYO AURORA es deslumbrante,\n"
	.string "el JUEZ no podrá verlo.\p"
	.string "Eh, espera un segundo...\n"
	.string "¡Entonces no tendrá sentido!$"

LilycoveCity_ContestHall_Text_PokemonLooksLikeYoungerMe_hns:
	.string "Este lindo POKéMON se parece\n"
	.string "a mí cuando era joven.\p"
	.string "Justo al decir eso, mi esposo\n"
	.string "escupió el café que bebía.\p"
	.string "¿Dije algo gracioso?$"

LilycoveCity_ContestHall_Text_WinBeautyContestMakesMeHappy_hns:
	.string "Sabes, si gano un CONCURSO\n"
	.string "de BELLEZA, claro que me\l"
	.string "hace feliz. Más de lo normal.$"

LilycoveCity_ContestHall_Text_GanderAtAllThosePrettyPokemon_hns:
	.string "¡Jajajajaja!\p"
	.string "¡Mira todos esos hermosos\n"
	.string "POKéMON!\l"
	.string "¡Me encanta este tipo de brillo!$"

LilycoveCity_ContestHall_Text_CantWinOnBeautyAlone_hns:
	.string "No siempre se gana solo con la\n"
	.string "belleza.\p"
	.string "Debes cuidar a tu POKéMON para que\n"
	.string "brille tanto como el mío.$"

LilycoveCity_ContestHall_Text_InTheMiddleOfContest_hns:
	.string "MC: ¡Oh! ¡Hola!\n"
	.string "¡Estamos en medio de un CONCURSO!\p"
	.string "Por favor, regístrate en el mostrador\n"
	.string "y luego vuelve, ¿está bien?$"

LilycoveCity_ContestHall_Text_SuchCharmingCuteAppeals_hns:
	.string "JUEZ: Oh, qué encantadores y lindos\n"
	.string "¡atractivos!\p"
	.string "¡Cielos! ¡Qué atractivo de\n"
	.string "DEPORTES ACUÁTICOS tan adorable!$"

LilycoveCity_ContestHall_Text_MyAzurillWasDistracted_hns:
	.string "Oh, no... Mi dulce AZURILL se\n"
	.string "distrajo con otro POKéMON.$"

LilycoveCity_ContestHall_Text_NeverWonBattleButContest_hns:
	.string "Mi POKéMON nunca ganó una batalla,\n"
	.string "¡pero en un CONCURSO, cuidado!$"

LilycoveCity_ContestHall_Text_PetalDanceIsMarvel_hns:
	.string "El DANZA PÉTALO de mi POKéMON es\n"
	.string "una maravilla de elegancia.\p"
	.string "No dejaré que nadie interrumpa su\n"
	.string "actuación.$"

LilycoveCity_ContestHall_Text_MyMonAppealSoMuchCuter_hns:
	.string "Los POKéMON de todos son muy lindos.\p"
	.string "Pero si mi POKéMON hiciera\n"
	.string "una pose linda...\p"
	.string "estoy segura de que sería\n"
	.string "mucho más linda que las demás.$"

LilycoveCity_ContestHall_Text_MyChildIsInContest_hns:
	.string "Mi hijo está en este CONCURSO.$"

LilycoveCity_ContestHall_Text_ComeOnDear_hns:
	.string "¡Vamos, cariño! ¡Tú puedes!\n"
	.string "¡Tu POKéMON es el mejor!$"

LilycoveCity_ContestHall_Text_ThatGirlThereIsCutest_hns:
	.string "Creo que esa chica de allá es\n"
	.string "la más linda de todas.\p"
	.string "¿Qué dices? ¿Juzgan a los\n"
	.string "POKéMON por su apariencia?$"

LilycoveCity_ContestHall_Text_WantCuteMonOfMyOwn_hns:
	.string "Oh, al ver tantos POKéMON lindos,\n"
	.string "¡Dan ganas de tener uno propio!\p"
	.string "¡Iré a capturar algunos!$"

LilycoveCity_ContestHall_Text_BeautyContestStage_hns:
	.string "ESCENARIO DE BELLEZA\n"
	.string "¡Déjate llevar por su belleza!$"

LilycoveCity_ContestHall_Text_CuteContestStage_hns:
	.string "ESCENARIO DE LINURA\n"
	.string "¡Déjate cautivar por su dulzura!$"

LilycoveCity_ContestHall_Text_SmartContestStage_hns:
	.string "ESCENARIO DE INTELIGENCIA\n"
	.string "¡Impresionate con su ingenio!$"

