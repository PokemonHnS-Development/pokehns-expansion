BattleFrontier_Lounge3_hns_MapScripts::
	.byte 0

	.set BET_AMOUNT_5,  5
	.set BET_AMOUNT_10, 10
	.set BET_AMOUNT_15, 15

BattleFrontier_Lounge3_EventScript_Gambler_hns::
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_GAMBLER, BattleFrontier_Lounge3_EventScript_AlreadyMetGambler_hns
	call BattleFrontier_Lounge3_EventScript_CountSilverSymbols_hns
	goto_if_le VAR_0x8004, 2, BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols_hns
	setflag FLAG_MET_BATTLE_FRONTIER_GAMBLER
	msgbox BattleFrontier_Lounge3_Text_YouLookToughExplainGambling_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge_hns
	end

BattleFrontier_Lounge3_EventScript_AskToEnterChallenge_hns::
	special ShowFrontierGamblerLookingMessage
	waitmessage
	waitbuttonpress
	msgbox BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe_hns, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_DeclineChallenge_hns
	msgbox BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints_hns, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, BattleFrontier_Lounge3_EventScript_DeclineChallenge_hns
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot_hns
	waitmessage
	special ShowBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount_hns
	end

BattleFrontier_Lounge3_EventScript_ChooseBetAmount_hns::
	multichoice 20, 4, MULTI_FRONTIER_GAMBLER_BET, FALSE
	copyvar VAR_FRONTIER_GAMBLER_AMOUNT_BET, VAR_RESULT
	switch VAR_RESULT
	case FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_Bet5_hns
	case FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_Bet10_hns
	case FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_Bet15_hns
	case FRONTIER_GAMBLER_BET_CANCEL, BattleFrontier_Lounge3_EventScript_CancelBet_hns
	case MULTI_B_PRESSED, BattleFrontier_Lounge3_EventScript_CancelBet_hns
	end

BattleFrontier_Lounge3_EventScript_Bet5_hns::
	setvar VAR_0x8008, BET_AMOUNT_5
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet_hns
	end

BattleFrontier_Lounge3_EventScript_Bet10_hns::
	setvar VAR_0x8008, BET_AMOUNT_10
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet_hns
	end

BattleFrontier_Lounge3_EventScript_Bet15_hns::
	setvar VAR_0x8008, BET_AMOUNT_15
	goto BattleFrontier_Lounge3_EventScript_TryPlaceBet_hns
	end

BattleFrontier_Lounge3_EventScript_TryPlaceBet_hns::
	specialvar VAR_TEMP_1, GetFrontierBattlePoints
	goto_if_ge VAR_TEMP_1, VAR_0x8008, BattleFrontier_Lounge3_EventScript_PlaceBet_hns
	msgbox BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints_hns, MSGBOX_DEFAULT
	message BattleFrontier_Lounge3_Text_HowMuchCanYouSpot_hns
	waitmessage
	goto BattleFrontier_Lounge3_EventScript_ChooseBetAmount_hns
	end

BattleFrontier_Lounge3_EventScript_PlaceBet_hns::
	copyvar VAR_0x8004, VAR_0x8008
	special TakeFrontierBattlePoints
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET
	special UpdateBattlePointsWindow
	playse SE_SHOP
	msgbox BattleFrontier_Lounge3_Text_ThanksOffYouGo_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FinishBet_hns
	end

BattleFrontier_Lounge3_EventScript_FinishBet_hns::
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	special CloseBattlePointsWindow
	release
	end

BattleFrontier_Lounge3_EventScript_CountSilverSymbols_hns::
	setvar VAR_0x8004, 0
	call_if_set FLAG_SYS_TOWER_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount_hns
	call_if_set FLAG_SYS_DOME_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount_hns
	call_if_set FLAG_SYS_PALACE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount_hns
	call_if_set FLAG_SYS_ARENA_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount_hns
	call_if_set FLAG_SYS_FACTORY_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount_hns
	call_if_set FLAG_SYS_PIKE_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount_hns
	call_if_set FLAG_SYS_PYRAMID_SILVER, BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount_hns
	return

BattleFrontier_Lounge3_EventScript_AddSilverSymbolCount_hns::
	addvar VAR_0x8004, 1
	return

BattleFrontier_Lounge3_EventScript_NotEnoughSilverSymbols_hns::
	msgbox BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection_hns
	end

BattleFrontier_Lounge3_EventScript_AlreadyMetGambler_hns::
	msgbox BattleFrontier_Lounge3_Text_Oh_hns, MSGBOX_DEFAULT
	goto_if_ge VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET, BattleFrontier_Lounge3_EventScript_CheckBetResults_hns
	goto BattleFrontier_Lounge3_EventScript_AskToEnterChallenge_hns
	end

BattleFrontier_Lounge3_EventScript_CheckBetResults_hns::
	goto_if_eq VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_PLACED_BET, BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted_hns
	goto_if_eq VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WON, BattleFrontier_Lounge3_EventScript_WonChallenge_hns
	goto BattleFrontier_Lounge3_EventScript_LostChallenge_hns
	end

BattleFrontier_Lounge3_EventScript_WonChallenge_hns::
	msgbox BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints_hns, MSGBOX_DEFAULT
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_5, BattleFrontier_Lounge3_EventScript_RewardBet5_hns
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_10, BattleFrontier_Lounge3_EventScript_RewardBet10_hns
	call_if_eq VAR_FRONTIER_GAMBLER_AMOUNT_BET, FRONTIER_GAMBLER_BET_15, BattleFrontier_Lounge3_EventScript_RewardBet15_hns
	msgbox BattleFrontier_Lounge3_Text_ObtainedBattlePoints_hns, MSGBOX_GETPOINTS
	special GiveFrontierBattlePoints
	msgbox BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge_hns, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_LostChallenge_hns::
	msgbox BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints_hns, MSGBOX_DEFAULT
	setvar VAR_FRONTIER_GAMBLER_STATE, FRONTIER_GAMBLER_WAITING
	release
	end

BattleFrontier_Lounge3_EventScript_RewardBet5_hns::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_5 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_5 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet10_hns::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_10 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_10 * 2)
	return

BattleFrontier_Lounge3_EventScript_RewardBet15_hns::
	buffernumberstring STR_VAR_1, (BET_AMOUNT_15 * 2)
	setvar VAR_0x8004, (BET_AMOUNT_15 * 2)
	return

BattleFrontier_Lounge3_EventScript_ChallengeNotAttempted_hns::
	special ShowFrontierGamblerGoMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge3_EventScript_DeclineChallenge_hns::
	msgbox BattleFrontier_Lounge3_Text_NotInterested_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge3_EventScript_CancelBet_hns::
	special CloseBattlePointsWindow
	goto BattleFrontier_Lounge3_EventScript_DeclineChallenge_hns
	end

BattleFrontier_Lounge3_EventScript_Man_hns::
	msgbox BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges_hns, MSGBOX_NPC
	end

BattleFrontier_Lounge3_EventScript_Woman_hns::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_BackedWrongTrainer_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection_hns
	end

BattleFrontier_Lounge3_EventScript_PokefanF_hns::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection_hns
	end

BattleFrontier_Lounge3_EventScript_FatMan_hns::
	lock
	faceplayer
	msgbox BattleFrontier_Lounge3_Text_TrainerGoodButRattled_hns, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge3_EventScript_FaceOriginalDirection_hns
	end

BattleFrontier_Lounge3_EventScript_FaceOriginalDirection_hns::
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

BattleFrontier_Lounge3_Text_CantYouSeeWereBusyHere_hns::
	.string "...¿Qué es lo que quieres?\p"
	.string "¿No ves que estamos algo ocupados?\n"
	.string "¿No puede esperar tu asunto?$"

BattleFrontier_Lounge3_Text_YouLookToughExplainGambling_hns::
	.string "...¿Eh?\n"
	.string "Pareces un ENTRENADOR fuerte.\p"
	.string "Jeje...\n"
	.string "Escucha, tengo una propuesta.\p"
	.string "Tenemos un pequeño grupo aquí,\n"
	.string "y jugamos un juego sobre lo que\l"
	.string "pasa en la BATTLE FRONTIER.\p"
	.string "Las reglas son muy simples.\p"
	.string "Primero, elegimos una instalación\n"
	.string "en la BATTLE FRONTIER.\p"
	.string "Luego, cada uno elige un TRAINER\n"
	.string "que esté haciendo el desafío,\l"
	.string "y apostamos Battle Points.\p"
	.string "Quien apueste por el TRAINER con\n"
	.string "el mejor récord se lleva todos los\l"
	.string "Battle Points del pozo.\p"
	.string "Suena simple, ¿no?\n"
	.string "En fin...$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerSingle_hns::
	.string "Busco a un TRAINER que vaya a\n"
	.string "desafiar las SALAS DE COMBATE\l"
	.string "INDIVIDUAL de la BATTLE TOWER.\p"
	.string "Pero hasta ahora, no he visto a un\n"
	.string "ENTRENADOR con esa chispa.$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerDouble_hns::
	.string "Busco a un TRAINER que vaya a\n"
	.string "desafiar las SALAS DE COMBATE\l"
	.string "SALAS DOBLES de la TORRE.\p"
	.string "Pero hasta ahora, no he visto a un\n"
	.string "ENTRENADOR con esa chispa.$"

BattleFrontier_Lounge3_Text_ChallengeBattleTowerMulti_hns::
	.string "Busco a un TRAINER que vaya a\n"
	.string "desafiar las SALAS DE COMBATE\l"
	.string "SALAS MULTI de la TORRE.\p"
	.string "Pero hasta ahora, no he visto a un\n"
	.string "ENTRENADOR con esa chispa.$"

BattleFrontier_Lounge3_Text_ChallengeBattleDomeSingle_hns::
	.string "Busco a un TRAINER que vaya a\n"
	.string "va a entrar al torneo de\l"
	.string "BATALLA INDIVIDUAL del DOME.\p"
	.string "Pero hasta ahora, no he visto a un\n"
	.string "ENTRENADOR con esa chispa.$"

BattleFrontier_Lounge3_Text_ChallengeBattleDomeDouble_hns::
	.string "Busco a un TRAINER que vaya a\n"
	.string "va a entrar al torneo de\l"
	.string "BATALLA DOBLE del DOME.\p"
	.string "Pero hasta ahora, no he visto a un\n"
	.string "ENTRENADOR con esa chispa.$"

BattleFrontier_Lounge3_Text_ChallengeBattleFactorySingle_hns::
	.string "Busco a un TRAINER que vaya a\n"
	.string "va a entrar al torneo de\l"
	.string "Intercambio Individual de FACTORY.\p"
	.string "Pero hasta ahora, no he visto a un\n"
	.string "ENTRENADOR con esa chispa.$"

BattleFrontier_Lounge3_Text_ChallengeBattleFactoryDouble_hns::
	.string "Busco a un TRAINER que vaya a\n"
	.string "va a entrar al torneo de\l"
	.string "Intercambio Doble de FACTORY.\p"
	.string "Pero hasta ahora, no he visto a un\n"
	.string "ENTRENADOR con esa chispa.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceSingle_hns::
	.string "Busco a un TRAINER que vaya a\n"
	.string "desafiar las SALAS DE COMBATE\l"
	.string "SALAS INDIVIDUALES del PALACIO.\p"
	.string "Pero hasta ahora, no he visto a un\n"
	.string "ENTRENADOR con esa chispa.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePalaceDouble_hns::
	.string "Busco a un TRAINER que vaya a\n"
	.string "desafiar las SALAS DE COMBATE\l"
	.string "SALAS DOBLES del PALACIO.\p"
	.string "Pero hasta ahora, no he visto a un\n"
	.string "ENTRENADOR con esa chispa.$"

BattleFrontier_Lounge3_Text_ChallengeBattleArena_hns::
	.string "Busco a un TRAINER que vaya a\n"
	.string "va a entrar al torneo de\l"
	.string "Torneo Set KO de la ARENA.\p"
	.string "Pero hasta ahora, no he visto a un\n"
	.string "ENTRENADOR con esa chispa.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePike_hns::
	.string "Busco a un TRAINER que vaya a\n"
	.string "entrar en la Selección de Batalla\l"
	.string "del BATTLE PIKE.\p"
	.string "Pero hasta ahora, no he visto a un\n"
	.string "ENTRENADOR con esa chispa.$"

BattleFrontier_Lounge3_Text_ChallengeBattlePyramid_hns::
	.string "Busco a un TRAINER que vaya a\n"
	.string "va a entrar al torneo de\l"
	.string "la Búsqueda de Batalla de la PYRAMID.\p"
	.string "Pero hasta ahora, no he visto a un\n"
	.string "ENTRENADOR con esa chispa.$"

BattleFrontier_Lounge3_Text_HowAboutEnteringEventForMe_hns::
	.string "Haré que tú también te beneficies.\n"
	.string "¿Qué te parece?\l"
	.string "¿Entrarías en ese evento por mí?$"

BattleFrontier_Lounge3_Text_SpotMeSomeBattlePoints_hns::
	.string "Muy bien, es perfecto.\n"
	.string "Entonces, eh... ¿Podrías darme\l"
	.string "algunos de tus Puntos de Batalla?\p"
	.string "Confía en mí, te lo agradeceré\n"
	.string "después.$"

BattleFrontier_Lounge3_Text_HowMuchCanYouSpot_hns::
	.string "¡Genial, genial!\n"
	.string "Entonces, ¿cuánto me prestarás?$"

BattleFrontier_Lounge3_Text_YouDontHaveEnoughPoints_hns::
	.string "Oh, no, no, no!\n"
	.string "¡No tienes suficientes Puntos de!\p"
	.string "¡Ojalá dejaras de jugar y no\n"
	.string "perdieras el tiempo de todos!$"

BattleFrontier_Lounge3_Text_ThanksOffYouGo_hns::
	.string "¡Jeje! ¡Muchas gracias!\n"
	.string "¡Ahora, vete ya!$"

BattleFrontier_Lounge3_Text_GetToBattleTowerSingle_hns::
	.string "¡Ve a las SALAS DE BATALLA\n"
	.string "¡SALAS DE BATALLA INDIVIDUAL pronto!\p"
	.string "¡Es una situación de ganar o morir!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestros futuros dependen de ti!$"

BattleFrontier_Lounge3_Text_GetToBattleTowerDouble_hns::
	.string "¡Ve a las SALAS DE BATALLA\n"
	.string "¡SALAS DE BATALLA DOBLE pronto!\p"
	.string "¡Es una situación de ganar o morir!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestros futuros dependen de ti!$"

BattleFrontier_Lounge3_Text_GetToBattleTowerMulti_hns::
	.string "¡Ve a las SALAS DE BATALLA\n"
	.string "¡SALA MULTI BATALLA pronto!\p"
	.string "¡Es una situación de ganar o morir!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestros futuros dependen de ti!$"

BattleFrontier_Lounge3_Text_GetToBattleDomeSingle_hns::
	.string "Ve al BATTLE DOME,\n"
	.string "¡Torneo BATALLA INDIVIDUAL pronto!\p"
	.string "¡Es una situación de ganar o morir!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestros futuros dependen de ti!$"

BattleFrontier_Lounge3_Text_GetToBattleDomeDouble_hns::
	.string "Ve al BATTLE DOME,\n"
	.string "¡Torneo BATALLA DOBLE pronto!\p"
	.string "¡Es una situación de ganar o morir!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestros futuros dependen de ti!$"

BattleFrontier_Lounge3_Text_GetToBattleFactorySingle_hns::
	.string "Ve al BATTLE FACTORY,\n"
	.string "¡Torneo Intercambio Individual!\p"
	.string "¡Es una situación de ganar o morir!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestros futuros dependen de ti!$"

BattleFrontier_Lounge3_Text_GetToBattleFactoryDouble_hns::
	.string "Ve al BATTLE FACTORY,\n"
	.string "¡Torneo Intercambio Doble!\p"
	.string "¡Es una situación de ganar o morir!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestros futuros dependen de ti!$"

BattleFrontier_Lounge3_Text_GetToBattlePalaceSingle_hns::
	.string "Ve al BATTLE PALACE,\n"
	.string "¡SALA BATALLA INDIVIDUAL pronto!\p"
	.string "¡Es una situación de ganar o morir!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestros futuros dependen de ti!$"

BattleFrontier_Lounge3_Text_GetToBattlePalaceDouble_hns::
	.string "Ve al BATTLE PALACE,\n"
	.string "¡SALA BATALLA DOBLE pronto!\p"
	.string "¡Es una situación de ganar o morir!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestros futuros dependen de ti!$"

BattleFrontier_Lounge3_Text_GetToBattleArena_hns::
	.string "Ve al BATTLE ARENA,\n"
	.string "¡Torneo Set KO pronto!\p"
	.string "¡Es una situación de ganar o morir!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestros futuros dependen de ti!$"

BattleFrontier_Lounge3_Text_GetToBattlePike_hns::
	.string "Ve al BATTLE PIKE\n"
	.string "¡Battle Choice pronto!\p"
	.string "¡Es una situación de ganar o morir!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestros futuros dependen de ti!$"

BattleFrontier_Lounge3_Text_GetToBattlePyramid_hns::
	.string "Ve al BATTLE PYRAMID\n"
	.string "¡Battle Quest pronto!\p"
	.string "¡Es una situación de ganar o morir!\n"
	.string "¡No desperdicies tu oportunidad!\l"
	.string "¡Nuestros futuros dependen de ti!$"

BattleFrontier_Lounge3_Text_NiceTryCantReturnPoints_hns::
	.string "Oh, eres tú...\n"
	.string "Buen intento...\p"
	.string "Siento decirte que no puedo\n"
	.string "devolverte tus Battle Points...\p"
	.string "¡Que esto nos motive a esforzarnos\n"
	.string "más la próxima vez!$"

BattleFrontier_Lounge3_Text_HelloChampHeresYourPoints_hns::
	.string "¡Oh, sí!\n"
	.string "¡Hola, campeón!\p"
	.string "¡Sabía que podías!\n"
	.string "¡Sabía que lo harías!\l"
	.string "¡Ambos somos grandes ganadores!\p"
	.string "Te devolveré tus Puntos de Batalla\n"
	.string "¡y, claro, un extra de mi parte!$"

BattleFrontier_Lounge3_Text_ObtainedBattlePoints_hns::
	.string "{PLAYER} obtuvo\n"
	.string "{STR_VAR_1} Puntos de Batalla.$"

BattleFrontier_Lounge3_Text_ThinkOfMeForAnotherChallenge_hns::
	.string "Si quieres otro desafío,\n"
	.string "¡por favor, piensa en mí!$"

BattleFrontier_Lounge3_Text_NotInterested_hns::
	.string "¡¿No te interesa?! No deberías\n"
	.string "tener miedo de arriesgarte!$"

BattleFrontier_Lounge3_Text_Oh_hns::
	.string "Oh...$"

BattleFrontier_Lounge3_Text_BackedWrongTrainer_hns::
	.string "¡Aposté por el ENTRENADOR errado!\p"
	.string "Tal vez debería luchar normal\n"
	.string "como todos los demás...$"

BattleFrontier_Lounge3_Text_TrainerGoodButRattled_hns::
	.string "Ese ENTRENADOR...\p"
	.string "Es bueno, pero se pone nervioso\n"
	.string "sobrevivir fácil al BATTLE DOME...$"

BattleFrontier_Lounge3_Text_KnowWinnerWhenISeeOne_hns::
	.string "¡Jeje!\n"
	.string "¡Reconozco a un ganador al verlo!$"

BattleFrontier_Lounge3_Text_ShouldBeTakingChallenges_hns::
	.string "Esos ENTRENADORES...\n"
	.string "¿Qué están haciendo?\l"
	.string "Deberían aceptar los desafíos.$"
