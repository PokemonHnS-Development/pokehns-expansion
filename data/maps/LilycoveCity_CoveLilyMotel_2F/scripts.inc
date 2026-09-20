LilycoveCity_CoveLilyMotel_2F_MapScripts::
	.byte 0

LilycoveCity_CoveLilyMotel_2F_EventScript_GameDesigner::
	lock
	faceplayer
	call_if_unset FLAG_TEMP_2, LilycoveCity_CoveLilyMotel_2F_EventScript_ShowMeCompletedDex
	call_if_set FLAG_TEMP_2, LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma
	specialvar VAR_RESULT, HasAllRegionalMons
	goto_if_eq VAR_RESULT, TRUE, LilycoveCity_CoveLilyMotel_2F_EventScript_AllHoennMonsFanfare
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_ShowMeCompletedDex::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ShowMeCompletedDex, MSGBOX_DEFAULT
	return

LilycoveCity_CoveLilyMotel_2F_EventScript_AllHoennMonsFanfare::
	setflag FLAG_TEMP_2
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	goto LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_ShowDiploma::
	message LilycoveCity_CoveLilyMotel_2F_Text_FilledPokedexGiveYouThis
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	specialvar VAR_RESULT, HasAllMons
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_CoveLilyMotel_2F_EventScript_TryGiveShinyCharm
	specialvar VAR_RESULT, HasAllRegionalMons
	call_if_eq VAR_RESULT, TRUE, LilycoveCity_CoveLilyMotel_2F_EventScript_TryGiveOvalCharm
	special Special_ShowDiploma
	waitstate

	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_TryGiveOvalCharm::
	checkitem ITEM_OVAL_CHARM
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_CoveLilyMotel_2F_EventScript_GiveOvalCharm
	return

LilycoveCity_CoveLilyMotel_2F_EventScript_GiveOvalCharm::
	giveitem ITEM_OVAL_CHARM
	return

LilycoveCity_CoveLilyMotel_2F_EventScript_TryGiveShinyCharm::
	checkitem ITEM_SHINY_CHARM
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_CoveLilyMotel_2F_EventScript_GiveShinyCharm
	checkitem ITEM_OVAL_CHARM
	call_if_eq VAR_RESULT, FALSE, LilycoveCity_CoveLilyMotel_2F_EventScript_GiveOvalCharm
	return

LilycoveCity_CoveLilyMotel_2F_EventScript_GiveShinyCharm::
	giveitem ITEM_SHINY_CHARM
	return

LilycoveCity_CoveLilyMotel_2F_EventScript_Programmer::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ImTheProgrammer, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_GraphicArtist::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ImTheGraphicArtist, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_FatMan::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_GirlsAreCute, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Woman::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_SeaBreezeTicklesHeart, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_GameBoyKid::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_NeverLeaveWithoutGameBoy, MSGBOX_NPC
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_Scott::
	lock
	faceplayer
	goto_if_set FLAG_MET_SCOTT_IN_LILYCOVE, LilycoveCity_CoveLilyMotel_2F_EventScript_MetScott
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_SnoozingPreferBattles, MSGBOX_DEFAULT
	addvar VAR_SCOTT_STATE, 1
	setflag FLAG_MET_SCOTT_IN_LILYCOVE
	release
	end

LilycoveCity_CoveLilyMotel_2F_EventScript_MetScott::
	msgbox LilycoveCity_CoveLilyMotel_2F_Text_ContestsDoTakeStrategy, MSGBOX_DEFAULT
	release
	end

LilycoveCity_CoveLilyMotel_2F_Text_ShowMeCompletedDex:
	.string "Soy el DISEÑADOR DE JUEGOS.\p"
	.string "Oh, ¿de verdad?\n"
	.string "¿Trabajas en una POKéDEX?\p"
	.string "Es difícil intentar completarla,\n"
	.string "pero no te rindas.\p"
	.string "Si lo logras, por favor ven y\n"
	.string "muéstramela.$"

LilycoveCity_CoveLilyMotel_2F_Text_FilledPokedexGiveYouThis:
	.string "¡Guau! ¡Eso es increíble!\n"
	.string "¡Sí, es totalmente increíble!\p"
	.string "¡Esta POKéDEX está completa!\n"
	.string "¡Debes amar a los POKéMON!\p"
	.string "¡Estoy muy impresionado!\p"
	.string "Déjame darte algo a cambio\n"
	.string "¡reconocimiento a tu hazaña!$"

LilycoveCity_CoveLilyMotel_2F_Text_ImTheProgrammer:
	.string "¿Yo? ¿Estás hablando conmigo?\n"
	.string "Soy el PROGRAMADOR.\p"
	.string "Me pregunto cómo serán las\n"
	.string "TRAGAPERRAS aquí.$"

LilycoveCity_CoveLilyMotel_2F_Text_ImTheGraphicArtist:
	.string "¡Soy el ARTISTA GRÁFICO! ¿No son\n"
	.string "interesantes los POKéMON de HOENN?$"

LilycoveCity_CoveLilyMotel_2F_Text_GirlsAreCute:
	.string "Las chicas TUBERS son lindas, ¿no?\n"
	.string "Luchar contra una linda TUBER...\p"
	.string "¡Uff, es genial!\p"
	.string "¡Y las GEMELAS! ¿No son lindas?\n"
	.string "Una batalla 2 contra 2 con GEMELAS...\p"
	.string "¡Uau, es increíblemente divertido!$"

LilycoveCity_CoveLilyMotel_2F_Text_SeaBreezeTicklesHeart:
	.string "La brisa marina me alegra el alma.\n"
	.string "¡Se siente maravilloso aquí!$"

LilycoveCity_CoveLilyMotel_2F_Text_NeverLeaveWithoutGameBoy:
	.string "Nunca sabes cuándo ni dónde\n"
	.string "la gente te desafiará.\p"
	.string "Por eso nunca salgo de casa sin\n"
	.string "mi GAME BOY ADVANCE.$"

LilycoveCity_CoveLilyMotel_2F_Text_SnoozingPreferBattles:
	.string "SCOTT: … … … … …\n"
	.string "… … … … … Zzz…\p"
	.string "… … … … … ¡¿Eh?!\n"
	.string "¡Oh, perdón! ¡Me quedé dormido!\p"
	.string "Vine a ver a este POKéMON\n"
	.string "Cosas de CONCURSOS.\p"
	.string "Debo admitir que parece bastante\n"
	.string "entretenido, pero...\p"
	.string "Soy un purista: prefiero las\n"
	.string "batallas y ENTRENADORES fuertes.\p"
	.string "Pero es solo mi opinión.\p"
	.string "{PLAYER}{KUN}, espero que disfrutes de\n"
	.string "GIMNASIOS, CONCURSOS, TIENDAS...\l"
	.string "¡de todo un poco!$"

LilycoveCity_CoveLilyMotel_2F_Text_ContestsDoTakeStrategy:
	.string "SCOTT: Creo que hace falta estrategia\n"
	.string "para ganar un CONCURSO.\p"
	.string "Crear estrategias de CONCURSO es una\n"
	.string "de ser un mejor ENTRENADOR, diría.$"

