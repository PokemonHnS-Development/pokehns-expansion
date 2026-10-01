BattleFrontier_Lounge2_hns_MapScripts::
	.byte 0

@ This NPC gives hints about a random facility or battle mode.
@ For battle modes he gives generic advice
@ For facilities, depending on how far the player has progressed he will say either
@    The name of the Frontier Brain there
@    The type and description of the 3 pokemon they use in their silver battle
@    The type and description of the 3 pokemon they use in their gold battle
BattleFrontier_Lounge2_EventScript_FrontierManiac_hns::
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_MANIAC, BattleFrontier_Lounge2_EventScript_AlreadyMetManiac_hns
	setflag FLAG_MET_BATTLE_FRONTIER_MANIAC
	msgbox BattleFrontier_Lounge2_Text_FrontierManiacIntro_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice_hns
	end

BattleFrontier_Lounge2_EventScript_AlreadyMetManiac_hns::
	msgbox BattleFrontier_Lounge2_Text_SwingByForTheLatestWord_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice_hns
	end

BattleFrontier_Lounge2_EventScript_GiveAdvice_hns::
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_SINGLES, BattleFrontier_Lounge2_EventScript_BufferSingle_hns
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_DOUBLES, BattleFrontier_Lounge2_EventScript_BufferDouble_hns
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_MULTIS, BattleFrontier_Lounge2_EventScript_BufferMulti_hns
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_LINK, BattleFrontier_Lounge2_EventScript_BufferMulti_hnsLink_hns
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_DOME, BattleFrontier_Lounge2_EventScript_BufferBattleDome_hns
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_FACTORY, BattleFrontier_Lounge2_EventScript_BufferBattleFactory_hns
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PALACE, BattleFrontier_Lounge2_EventScript_BufferBattlePalace_hns
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_ARENA, BattleFrontier_Lounge2_EventScript_BufferBattleArena_hns
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PIKE, BattleFrontier_Lounge2_EventScript_BufferBattlePike_hns
	call_if_eq VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_PYRAMID, BattleFrontier_Lounge2_EventScript_BufferBattlePyramid_hns
@ <= FRONTIER_MANIAC_TOWER_LINK is any Battle Tower mode
	call_if_le VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_TOWER_LINK, BattleFrontier_Lounge2_EventScript_BattleTowerNews_hns
@ >= FRONTIER_MANIAC_DOME is any facility other than Battle Tower
	call_if_ge VAR_FRONTIER_MANIAC_FACILITY, FRONTIER_MANIAC_DOME, BattleFrontier_Lounge2_EventScript_FacilityNews_hns
	special ShowFrontierManiacMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge2_EventScript_BattleTowerNews_hns::
	msgbox BattleFrontier_Lounge2_Text_BattleTowerIsHottest_hns, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_FacilityNews_hns::
	msgbox BattleFrontier_Lounge2_Text_FacilityIsHottest_hns, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_BufferSingle_hns::
	bufferstdstring STR_VAR_1, STDSTRING_SINGLE
	return

BattleFrontier_Lounge2_EventScript_BufferDouble_hns::
	bufferstdstring STR_VAR_1, STDSTRING_DOUBLE
	return

BattleFrontier_Lounge2_EventScript_BufferMulti_hns::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI
	return

BattleFrontier_Lounge2_EventScript_BufferMulti_hnsLink_hns::
	bufferstdstring STR_VAR_1, STDSTRING_MULTI_LINK
	return

BattleFrontier_Lounge2_EventScript_BufferBattleDome_hns::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_DOME
	return

BattleFrontier_Lounge2_EventScript_BufferBattleFactory_hns::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_FACTORY
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePalace_hns::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PALACE
	return

BattleFrontier_Lounge2_EventScript_BufferBattleArena_hns::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_ARENA
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePike_hns::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PIKE
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePyramid_hns::
	bufferstdstring STR_VAR_1, STDSTRING_BATTLE_PYRAMID
	return

BattleFrontier_Lounge2_EventScript_Maniac1_hns::
	lock
	msgbox BattleFrontier_Lounge2_Text_NewsGatheringPower_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac2_hns::
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowersOfObservation_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac3_hns::
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_TriathleteF_hns::
	msgbox BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe_hns, MSGBOX_NPC
	end

BattleFrontier_Lounge2_Text_FrontierManiacIntro_hns::
	.string "¡Hola! Cuando se trata de noticias\n"
	.string "del FRENTE DE BATALLA, soy el n.º 1.\p"
	.string "Puedes verme como\n"
	.string "el MANÍACO DE LA FRONTIER.\p"
	.string "Solo confirmo, eres ENTRENADOR,\n"
	.string "¿no es cierto?\p"
	.string "Compartiré con gusto las noticias\n"
	.string "del FRENTE DE BATALLA que reuní.$"

BattleFrontier_Lounge2_Text_SwingByForTheLatestWord_hns::
	.string "¡Hola! ¿Vienes a preguntarme\n"
	.string "lo más reciente? ¡Está bien!$"

@ Unused
BattleFrontier_Lounge2_Text_MyInformationsBeenUsefulRight_hns::
	.string "¿Y bien? ¿Y bien? ¿Y bien?\p"
	.string "Seguro que mi información ha sido\n"
	.string "te será muy útil, ¿verdad?$"

BattleFrontier_Lounge2_Text_FacilityIsHottest_hns::
	.string "Veamos...\p"
	.string "Parece que {STR_VAR_1}\n"
	.string "es el lugar más popular.$"

BattleFrontier_Lounge2_Text_BattleTowerIsHottest_hns::
	.string "Veamos...\p"
	.string "Parece que la TORRE BATALLA\n"
	.string "{STR_VAR_1} es lo más popular.$"

BattleFrontier_Lounge2_Text_SalonMaidenIsThere_hns::
	.string "¡Apuesto a que no sabías esto!\p"
	.string "Uno de los mejores ENTRENADORES que\n"
	.string "SCOTT llama ASES DEL FRENTE está ahí.\p"
	.string "Es un ENTRENADOR misterioso llamado\n"
	.string "la DAMA DE LA TORRE,\nquien dirige el lugar.$"

BattleFrontier_Lounge2_Text_SalonMaidenSilverMons_hns::
	.string "¿Has luchado contra la\nDAMA DE LA TORRE?\p"
	.string "Cuando mide a su oponente,\n"
	.string "al parecer usa estos POKéMON:\p"
	.string "un POKéMON PSI tipo PSÍQUICO,\n"
	.string "un POKéMON VOLCÁN tipo FUEGO,\l"
	.string "y un POKéMON DURMIENTE tipo NORMAL.$"

BattleFrontier_Lounge2_Text_SalonMaidenGoldMons_hns::
	.string "¿Has luchado contra la\nDAMA DE LA TORRE\n"
	.string "cuando se pone seria?\p"
	.string "Cuando lucha con todo,\n"
	.string "al parecer usa estos POKéMON:\p"
	.string "un POKéMON EON DRAGÓN y PSÍQUICO,\n"
	.string "un POKéMON TRUENO tipo ELÉCTRICO,\l"
	.string "y un POKéMON DURMIENTE tipo NORMAL.$"

BattleFrontier_Lounge2_Text_DomeAceIsThere_hns::
	.string "¡Apuesto a que no sabías esto!\p"
	.string "Uno de los mejores ENTRENADORES que\n"
	.string "SCOTT llama ASES DEL FRENTE está ahí.\p"
	.string "Es ese ENTRENADOR llamativo\n"
	.string "el ASTRO DE LA CÚPULA quien manda.$"

BattleFrontier_Lounge2_Text_DomeAceSilverMons_hns::
	.string "¿Luchaste contra el\nASTRO DE LA CÚPULA?\p"
	.string "Cuando no se toma en serio\n"
	.string "al rival, usa estos tres POKéMON:\p"
	.string "Un POKéMON DRAGÓN y VOLADOR,\n"
	.string "un POKéMON AGUA y TIERRA,\l"
	.string "y un POKéMON FUEGO y VOLADOR.$"

BattleFrontier_Lounge2_Text_DomeAceGoldMons_hns::
	.string "¿Luchaste contra el\nASTRO DE LA CÚPULA\n"
	.string "cuando se puso serio?\p"
	.string "Para mostrar su estrategia,\n"
	.string "usa estos tres POKéMON:\p"
	.string "Un POKéMON DRAGÓN y VOLADOR,\n"
	.string "un POKéMON AGUA y TIERRA,\l"
	.string "y un POKéMON ACERO y PSÍQUICO\l"
	.string "POKéMON.$"

BattleFrontier_Lounge2_Text_FactoryHeadIsThere_hns::
	.string "¡Apuesto a que no sabías esto!\p"
	.string "Uno de los mejores ENTRENADORES que\n"
	.string "SCOTT llama ASES DEL FRENTE está ahí.\p"
	.string "Es un TRAINER muy raro llamado\n"
	.string "el JEFE DE LA FÁBRICA, quien manda.$"

BattleFrontier_Lounge2_Text_FactoryHeadSilverMons_hns::
	.string "¿Ya luchaste contra el\n"
	.string "JEFE DE LA FÁBRICA?\p"
	.string "Déjame pensar... Al luchar,\n"
	.string "usa tres POKéMON de alquiler.\p"
	.string "Lucha bajo condiciones casi\n"
	.string "iguales que las tuyas.$"

BattleFrontier_Lounge2_Text_FactoryHeadGoldMons_hns::
	.string "¿Ya luchaste contra el\n"
	.string "JEFE DE LA FÁBRICA\ncuando se puso serio?\p"
	.string "Cuando lucha en serio,\n"
	.string "también usa tres POKéMON de alquiler.\p"
	.string "Lucha bajo condiciones casi iguales\n"
	.string "iguales que las tuyas.$"

BattleFrontier_Lounge2_Text_PikeQueenIsThere_hns::
	.string "¡Apuesto a que no sabías esto!\p"
	.string "Uno de los mejores ENTRENADORES que\n"
	.string "SCOTT llama ASES DEL FRENTE está ahí.\p"
	.string "Es un TRAINER aterrador llamado\n"
	.string "la REINA DE LA SIERPE que manda aquí.$"

BattleFrontier_Lounge2_Text_PikeQueenSilverMons_hns::
	.string "¿Has luchado contra la\nREINA DE LA SIERPE\n"
	.string "antes?\p"
	.string "Dicen que cuando está de buen humor\n"
	.string "usa estos tres POKéMON:\p"
	.string "un FANG SNAKE de tipo VENENO,\n"
	.string "un MOLD de tipo BICHOS y ROCA,\l"
	.string "y un TENDER de tipo AGUA.$"

BattleFrontier_Lounge2_Text_PikeQueenGoldMons_hns::
	.string "¿Has luchado contra la\nREINA DE LA SIERPE\n"
	.string "cuando se pone seria?\p"
	.string "Si está muy molesta, dicen que usa\n"
	.string "usa estos tres POKéMON:\p"
	.string "un FANG SNAKE de tipo VENENO,\n"
	.string "un IRON SNAKE de ACERO y TIERRA,\l"
	.string "y un ATROCIOUS de AGUA y VOLADOR\l"
	.string "POKéMON.$"

BattleFrontier_Lounge2_Text_ArenaTycoonIsThere_hns::
	.string "¡Apuesto a que no sabías esto!\p"
	.string "Uno de los mejores ENTRENADORES que\n"
	.string "SCOTT llama ASES DEL FRENTE está ahí.\p"
	.string "Es una linda ENTRENADORA llamada\n"
	.string "la MAESTRA DEL DOJO que manda aquí.$"

BattleFrontier_Lounge2_Text_ArenaTycoonSilverMons_hns::
	.string "¿Has luchado contra la\nMAESTRA DEL DOJO?\n"
	.string "antes?\p"
	.string "Cuando evalúa la habilidad rival,\n"
	.string "se dice que usa estos POKéMON:\p"
	.string "un POKéMON Bicho y Lucha de cuerno,\n"
	.string "un POKéMON Siniestro de luz lunar,\l"
	.string "y un POKéMON Bicho y Fantasma.$"

BattleFrontier_Lounge2_Text_ArenaTycoonGoldMons_hns::
	.string "¿Has luchado contra la\nMAESTRA DEL DOJO?\n"
	.string "cuando se pone seria?\p"
	.string "Cuando lucha en serio,\n"
	.string "se dice que usa estos POKéMON:\p"
	.string "un POKéMON Siniestro de luz lunar,\n"
	.string "un POKéMON Fantasma y Veneno\l"
	.string "y un POKéMON Planta y Lucha\l"
	.string "tipo hongo.$"

BattleFrontier_Lounge2_Text_PalaceMavenIsThere_hns::
	.string "¡Apuesto a que no sabías esto!\p"
	.string "Uno de los mejores ENTRENADORES que\n"
	.string "SCOTT llama ASES DEL FRENTE está ahí.\p"
	.string "Es un ENTRENADOR siniestro llamado\n"
	.string "el AMO DEL PALACIO que manda.$"

BattleFrontier_Lounge2_Text_PalaceMavenSilverMons_hns::
	.string "¿Has luchado con el AMO DEL PALACIO\n"
	.string "antes?\p"
	.string "Cuando pone a prueba el\n"
	.string "espíritu, usa estos POKéMON:\p"
	.string "A POISON & FLYING-type BAT POKéMON,\n"
	.string "un POKéMON PEREZOSO tipo NORMAL y un\l"
	.string "POKéMON TRANSPORTE AGUA e HIELO.$"

BattleFrontier_Lounge2_Text_PalaceMavenGoldMons_hns::
	.string "¿Has luchado con el AMO DEL PALACIO\n"
	.string "cuando se puso serio?\p"
	.string "Cuando pone todo su poder en la\n"
	.string "batalla, usa estos POKéMON:\p"
	.string "Un POKéMON LEGENDARIO tipo FUEGO,\n"
	.string "un POKéMON PEREZOSO tipo NORMAL,\l"
	.string "y un POKéMON AURORA tipo AGUA.$"

BattleFrontier_Lounge2_Text_PyramidKingIsThere_hns::
	.string "¡Apuesto a que no sabías esto!\p"
	.string "Uno de los mejores ENTRENADORES que\n"
	.string "SCOTT llama ASES DEL FRENTE está ahí.\p"
	.string "Es un ENTRENADOR ardiente llamado\n"
	.string "el REY DE LA PIRÁMIDE,\nquien manda allí.$"

BattleFrontier_Lounge2_Text_PyramidKingSilverMons_hns::
	.string "¿Has luchado contra el\nREY DE LA PIRÁMIDE?\n"
	.string "antes?\p"
	.string "Cuando mide el poder del rival,\n"
	.string "al parecer usa estos POKéMON:\p"
	.string "Un POKéMON ROCA PEAK tipo ROCA,\n"
	.string "un POKéMON ICEBERG tipo HIELO,\l"
	.string "y un POKéMON IRON tipo ACERO.$"

BattleFrontier_Lounge2_Text_PyramidKingGoldMons_hns::
	.string "¿Has luchado contra el\nREY DE LA PIRÁMIDE?\n"
	.string "cuando se puso serio?\p"
	.string "Cuando se llena de poder ardiente,\n"
	.string "al parecer usa estos POKéMON:\p"
	.string "un POKéMON FREEZE HIELO y VOLADOR,\n"
	.string "POKéMON ELÉCTRICOS Y VOLADORES,\l"
	.string "y un FLAME tipo FUEGO y VOLADOR\l"
	.string "POKéMON.$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice1_hns::
	.string "Claro, hay varios lugares donde\n"
	.string "puedes tener COMBATES DOBLES.\p"
	.string "Pero las SALAS BATALLA DOBLE de\n"
	.string "la TORRE BATALLA son básicas.\p"
	.string "Ahí es donde debes aprender cómo\n"
	.string "se juegan los COMBATES DOBLES aquí\l"
	.string "en el FRENTE DE BATALLA.$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice2_hns::
	.string "Ten cuidado en los combates aquí.\p"
	.string "Oigo que hay ENTRENADORES con\n"
	.string "estrategias creadas solo para\l"
	.string "COMBATES DOBLES.$"

BattleFrontier_Lounge2_Text_DoubleBattleAdvice3_hns::
	.string "Cuando tengas confianza y te sientas\n"
	.string "cómodo con los DOBLES COMBATES,\l"
	.string "deberías pensar en desafiar otros\l"
	.string "lugares de DOBLES COMBATES.$"

BattleFrontier_Lounge2_Text_MultiBattleAdvice_hns::
	.string "Todo tipo de ENTRENADORES se reúnen\n"
	.string "en el SALÓN BATALLA.\p"
	.string "¡Piensa que podrías encontrarte con\n"
	.string "tus amigos o seguidores!\l"
	.string "¡Mira con atención!$"

BattleFrontier_Lounge2_Text_LinkMultiBattleAdvice_hns::
	.string "Si estás con un amigo, ve a la\n"
	.string "SALA BATALLA MULTI-VÍNCULO.\p"
	.string "Si juegas con un amigo fuerte,\n"
	.string "¡Verás rivales muy fuertes!$"

BattleFrontier_Lounge2_Text_NewsGatheringPower_hns::
	.string "¡Qué gran poder para obtener noticias!\n"
	.string "¡Mi mentor es único en su clase!$"

BattleFrontier_Lounge2_Text_AmazingPowersOfObservation_hns::
	.string "¡Qué increíble poder de observación!\n"
	.string "¡Mi mentor es único en su clase!$"

BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion_hns::
	.string "¡Qué increíble poder de persuasión!\n"
	.string "¡Mi mentor es único en su clase!$"

BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe_hns::
	.string "...¿Qué es este lugar?\n"
	.string "Me da miedo...$"

