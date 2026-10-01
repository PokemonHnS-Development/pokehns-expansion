LilycoveCity_House3_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_House3_OnTransition
	.byte 0

LilycoveCity_House3_OnTransition:
	random 4
	copyvar VAR_TEMP_1, VAR_RESULT
	end

LilycoveCity_House3_EventScript_PokefanF::
	lock
	faceplayer
	msgbox LilycoveCity_House3_Text_LearnFromMasterOfPokeblocks, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LilycoveCity_House3_EventScript_DeclinePokeblockLearn
	msgbox LilycoveCity_House3_Text_ExplainPokeblocks, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_DeclinePokeblockLearn::
	msgbox LilycoveCity_House3_Text_OhAreYouSure, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_Man::
	lock
	faceplayer
	msgbox LilycoveCity_House3_Text_HappyToHaveQuadruplets, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_House3_EventScript_GameBoyKid1::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid2::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid3::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_GameBoyKid4::
	lock
	faceplayer
	switch VAR_TEMP_1
	case 0, LilycoveCity_House3_EventScript_WereDoingMultiBattle
	case 1, LilycoveCity_House3_EventScript_WereMixingRecords
	case 2, LilycoveCity_House3_EventScript_WereBlendingBerries
	case 3, LilycoveCity_House3_EventScript_WereDoingContest
	end

LilycoveCity_House3_EventScript_WereDoingMultiBattle::
	msgbox LilycoveCity_House3_Text_GoingToWinMultiBattles, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereMixingRecords::
	msgbox LilycoveCity_House3_Text_LikeMixingAtRecordCorner, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereBlendingBerries::
	msgbox LilycoveCity_House3_Text_MakePokeblocksWithBerryBlender, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_EventScript_WereDoingContest::
	msgbox LilycoveCity_House3_Text_GoingToEnterContest, MSGBOX_DEFAULT
	release
	end

LilycoveCity_House3_Text_LearnFromMasterOfPokeblocks:
	.string "¡Vaya, vaya! ¿Viajas solo?\n"
	.string "¡Eres muy joven! ¡Qué bien!\p"
	.string "Seguro que mis hijos podrían\n"
	.string "aprender algo de ti!\p"
	.string "¿Yo? Soy maestra de {POKEBLOCK}S.\p"
	.string "Si me pongo seria un poquito,\n"
	.string "puedo crear grandes {POKEBLOCK}S.\p"
	.string "¿Quieres aprender de mí,\n"
	.string "una maestra de {POKEBLOCK}S?$"

LilycoveCity_House3_Text_OhAreYouSure:
	.string "¿Oh? ¿Estás seguro?\p"
	.string "¡No intentes hacer siempre\n"
	.string "todo por tu cuenta, cielo!$"

LilycoveCity_House3_Text_ExplainPokeblocks:
	.string "¡Oh, bien! ¡Eres muy inteligente!\n"
	.string "¡Esto es largo, así que escucha!\p"
	.string "¿Estás listo?\p"
	.string "Si miras los {POKEBLOCK}S, verás\n"
	.string "que se califican por su tacto.\p"
	.string "Cuanto menor sea la calificación,\n"
	.string "mejor será. ¡No lo olvides!\p"
	.string "Un buen {POKEBLOCK} tiene un tacto\n"
	.string "bajo y un nivel alto.\p"
	.string "Un POKéMON puede comer más\n"
	.string "{POKEBLOCK}S buenos que los comunes.\p"
	.string "Y esto es muy importante.\p"
	.string "Si quieres {POKEBLOCK}S suaves,\n"
	.string "usa varios tipos de BAYAS.\p"
	.string "No seas tacaño; los tipos de BAYAS\n"
	.string "afectan la suavidad de {POKEBLOCK}S.\p"
	.string "Y otra cosa más.\p"
	.string "Cuanta más gente mezcle las BAYAS,\n"
	.string "más suaves serán los {POKEBLOCK}S.\p"
	.string "Por eso debes hablar con otros\n"
	.string "y hacer {POKEBLOCK}S juntos.\p"
	.string "Eso es todo lo que necesitas saber\n"
	.string "para hacer buenos {POKEBLOCK}S.\p"
	.string "Si todos tuvieran POKéMON amados,\n"
	.string "{POKEBLOCK}S suaves y una familia unida,\l"
	.string "el mundo sería un lugar más feliz.\p"
	.string "¡No te rindas, cariño!$"

LilycoveCity_House3_Text_HappyToHaveQuadruplets:
	.string "Cuando mi esposa tuvo cuatrillizos,\n"
	.string "estaba muy impactado.\p"
	.string "Pero ahora, al verlos jugar juntos,\n"
	.string "me hace muy feliz.$"

LilycoveCity_House3_Text_GoingToWinMultiBattles:
	.string "Hacemos BATALLAS MÚLTIPLES, pero sé\n"
	.string "que voy a ganar.$"

LilycoveCity_House3_Text_LikeMixingAtRecordCorner:
	.string "Nos gusta mezclar cosas en\n"
	.string "el RINCÓN DEL DISCO.\p"
	.string "Pero, ¿qué es lo que se mezcla?$"

LilycoveCity_House3_Text_MakePokeblocksWithBerryBlender:
	.string "Haremos super {POKEBLOCK}S\n"
	.string "¡con una BATIDORA DE BAYAS!$"

LilycoveCity_House3_Text_GoingToEnterContest:
	.string "Quiero presumir de lo fuerte que\n"
	.string "es mi POKéMON, así que iremos a\l"
	.string "un CONCURSO juntos.$"

