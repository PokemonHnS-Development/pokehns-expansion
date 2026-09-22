MauvilleCity_PokemonCenter_1F_EventScript_MauvilleOldMan::
	special Script_GetCurrentMauvilleMan
	switch VAR_RESULT
	case MAUVILLE_MAN_BARD, MauvilleCity_PokemonCenter_1F_EventScript_Bard
	case MAUVILLE_MAN_HIPSTER, MauvilleCity_PokemonCenter_1F_EventScript_Hipster
	case MAUVILLE_MAN_TRADER, MauvilleCity_PokemonCenter_1F_EventScript_Trader
	case MAUVILLE_MAN_STORYTELLER, MauvilleCity_PokemonCenter_1F_EventScript_Storyteller
	case MAUVILLE_MAN_GIDDY, MauvilleCity_PokemonCenter_1F_EventScript_Giddy
	end

@ Bard
MauvilleCity_PokemonCenter_1F_EventScript_Bard::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_PlaySong
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong
	end

MauvilleCity_PokemonCenter_1F_EventScript_PlaySong::
	setvar VAR_0x8004, FALSE  @ Play his current song
	special PlayBardSong
	delay 60
	special HasBardSongBeenChanged
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineSong::
	msgbox MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_AskToWriteLyrics::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	end

MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics::
	setvar VAR_0x8004, EASY_CHAT_TYPE_BARD_SONG
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou, MSGBOX_DEFAULT
	setvar VAR_0x8004, TRUE  @ Play the new song
	special PlayBardSong
	delay 60
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_WriteLyrics
	special SaveBardSongLyrics
	msgbox MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineWritingLyrics::
	msgbox MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2, MSGBOX_DEFAULT
	release
	end

@ Hipster
MauvilleCity_PokemonCenter_1F_EventScript_Hipster::
	lock
	faceplayer
	setflag FLAG_UNLOCKED_TRENDY_SAYINGS
	msgbox MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening, MSGBOX_DEFAULT
	special HasHipsterTaughtWord
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord
	msgbox MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTeachWord::
	special HipsterTryTeachWord
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_TeachWord
	msgbox MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TeachWord::
	msgbox MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfWord, MSGBOX_DEFAULT
	special SetHipsterTaughtWord
	release
	end

@ Trader
MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor:
	.string "Hola, soy el COMERCIANTE.\n"
	.string "¿Quieres cambiar adornos conmigo?$"

MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues:
	.string "Oh...\n"
	.string "Me has dejado muy triste...$"

MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded:
	.string "Pero si ya hemos intercambiado\n"
	.string "adornos, tú y yo.$"

MauvilleCity_PokemonCenter_1F_Text_PickADecorItem:
	.string "Si ves algún adorno mío que\n"
	.string "quieras, dímelo.$"

MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything:
	.string "¿No quieres nada?\n"
	.string "Me siento rechazado...$"

MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt:
	.string "Ese adorno perteneció alguna vez\n"
	.string "a {STR_VAR_1}.\p"
	.string "¿La quieres?$"

MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor:
	.string "Eh... Espera un segundo. No tienes un\n"
	.string "¡una sola pieza de decoración!$"

MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade:
	.string "Bien, elige la decoración que\n"
	.string "me vas a cambiar.$"

MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade:
	.string "¿No quieres cambiar conmigo?\n"
	.string "Me siento rechazado...$"

MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis:
	.string "Tienes todos los {STR_VAR_2} que\n"
	.string "caben. No tienes espacio para esto.$"

MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor:
	.string "Bien, cambiaré mi {STR_VAR_3}\n"
	.string "por tu {STR_VAR_2}.$"

MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse:
	.string "Esa decoración está en uso.\n"
	.string "No puedes cambiarla.$"

MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC:
	.string "¡Entonces hagamos el cambio!\n"
	.string "Enviaré mi decoración a tu PC.$"

MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne:
	.string "¡Ups! ¡Lo siento! Esa es una pieza\n"
	.string "de decoración muy rara.\l"
	.string "¡No puedo cambiar esa!\p"
	.string "¿Te interesa alguna otra cosa?$"

MauvilleCity_PokemonCenter_1F_EventScript_Trader::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_WantToTradeDecor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade
	special GetTraderTradedFlag
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded
	message MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineTrade::
	msgbox MauvilleCity_PokemonCenter_1F_Text_TraderFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_AlreadyTraded::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WeveAlreadyTraded, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive::
	special TraderMenuGetDecoration
	waitstate
	goto_if_eq VAR_0x8004, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor
	goto_if_eq VAR_0x8004, 0xFFFF, MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor
	msgbox MauvilleCity_PokemonCenter_1F_Text_OnceBelongedToPlayerDoYouWantIt, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor
	special DoesPlayerHaveNoDecorations
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

MauvilleCity_PokemonCenter_1F_EventScript_CancelPickDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontWantAnything, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_InvalidDecor::
	message MauvilleCity_PokemonCenter_1F_Text_CantTradeThatOne
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDifferentDecor::
	message MauvilleCity_PokemonCenter_1F_Text_PickADecorItem
	waitmessage
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToReceive
	end

MauvilleCity_PokemonCenter_1F_EventScript_DontHaveAnyDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontHaveAnyDecor, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive::
	msgbox MauvilleCity_PokemonCenter_1F_Text_PickTheDecorToTrade, MSGBOX_DEFAULT
	special TraderShowDecorationMenu
	waitstate
	goto_if_eq VAR_0x8006, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor
	goto_if_eq VAR_0x8006, 0xFFFF, MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse
	special IsDecorationCategoryFull
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor
	msgbox MauvilleCity_PokemonCenter_1F_Text_SoWellTradeTheseDecor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	special TraderDoDecorationTrade
	msgbox MauvilleCity_PokemonCenter_1F_Text_SendDecorToYourPC, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_CancelGiveDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDontWantToTrade, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DecorInUse::
	msgbox MauvilleCity_PokemonCenter_1F_Text_ThatDecorIsInUse, MSGBOX_DEFAULT
	goto MauvilleCity_PokemonCenter_1F_EventScript_PickDecorToGive
	end

MauvilleCity_PokemonCenter_1F_EventScript_NoRoomForDecor::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouveNoRoomForThis, MSGBOX_DEFAULT
	release
	end

@ Storyteller
MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale:
	.string "Soy el NARRADOR.\n"
	.string "Te contaré historias legendarias.\l"
	.string "con muchos ENTRENADORES.\p"
	.string "¿Quieres oír mi relato?$"

MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues:
	.string "Oh...\n"
	.string "Me has dejado muy triste...$"

MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell:
	.string "Conozco estas leyendas.\n"
	.string "¿Qué historia quieres que cuente?$"

MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales:
	.string "Pero no conozco ENTRENADORES\n"
	.string "legendarios. Así que no hay relatos.\p"
	.string "¿Dónde hallaría un ENTRENADOR digno\n"
	.string "¿de un cuento legendario?$"

MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes:
	.string "¡¿Qué es eso?!\n"
	.string "Tú... Tú...\p"
	.string "{STR_VAR_2}\n"
	.string "¡¿{STR_VAR_1} vez(es)?!\p"
	.string "¡Eso es realmente magnífico!\n"
	.string "¡Es el nacimiento de una leyenda!$"

MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends:
	.string "Me hace pensar, ¿podría haber\n"
	.string "otros ENTRENADORES con leyendas\l"
	.string "más impresionantes por hallar?$"

MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales:
	.string "¿Eres un ENTRENADOR?\p"
	.string "Dime, ¿tienes algún cuento que sea\n"
	.string "aunque sea remotamente legendario?$"

@ Unused
MauvilleCity_PokemonCenter_1F_Text_HearAnotherLegendaryTale:
	.string "Por cierto... ¿Te gustaría oír\n"
	.string "otro relato legendario?$"

MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend:
	.string "Hmm...\n"
	.string "No estoy satisfecho...\p"
	.string "Quisiera que me traigas noticias\n"
	.string "dignas de ser una leyenda.$"

MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested:
	.string "Quisiera que más gente se interesara\n"
	.string "al oír mis épicas historias de\l"
	.string "combate.$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameTitle::
	.string "The Save-Happy TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameAction::
	.string "Saved the game$"

MauvilleCity_PokemonCenter_1F_Text_SavedGameStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR guardó la partida\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "Un ENTRENADOR más cauteloso que\n"
	.string "{STR_VAR_3} ¡jamás encontrarás!$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedTitle::
	.string "The Trendsetter TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedAction::
	.string "Started trends$"

MauvilleCity_PokemonCenter_1F_Text_TrendsStartedStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR creó tendencias\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} marca tendencia en toda\n"
	.string "¡la región de HOENN!$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedTitle::
	.string "The BERRY-Planting TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedAction::
	.string "Planted BERRIES$"

MauvilleCity_PokemonCenter_1F_Text_BerriesPlantedStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR plantó BAYAS\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} es un amante legendario de\n"
	.string "¡BAYAS!$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesTitle::
	.string "The BIKE-Loving TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesAction::
	.string "Traded BIKES$"

MauvilleCity_PokemonCenter_1F_Text_BikeTradesStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR cambió BICICLETAS\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe amar las BICICLETAS\n"
	.string "¡con mucha pasión!$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsTitle::
	.string "The Interviewed TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsAction::
	.string "Got interviewed$"

MauvilleCity_PokemonCenter_1F_Text_InterviewsStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR fue entrevistado\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe ser un ENTRENADOR\n"
	.string "¡que atrae mucha atención!$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesTitle::
	.string "El ENTRENADOR amante de la lucha$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesAction::
	.string "Battled$"

MauvilleCity_PokemonCenter_1F_Text_TrainerBattlesStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR luchó {STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe ser un ENTRENADOR que\n"
	.string "¡jamás rechaza una batalla!$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtTitle::
	.string "The POKéMON-Catching TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtAction::
	.string "Caught POKéMON$"

MauvilleCity_PokemonCenter_1F_Text_PokemonCaughtStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR capturó\n"
	.string "{STR_VAR_1} POKéMON!\p"
	.string "{STR_VAR_3} es un capturador legendario de\n"
	.string "¡POKéMON salvajes!$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtTitle::
	.string "The Fishing TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtAction::
	.string "Caught POKéMON with a ROD$"

MauvilleCity_PokemonCenter_1F_Text_FishingPokemonCaughtStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "¡Este ENTRENADOR capturó\n"
	.string "¡{STR_VAR_1} POKéMON pescados!\p"
	.string "{STR_VAR_3} es un experto\n"
	.string "legendario de la pesca!$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedTitle::
	.string "The EGG-Warming TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedAction::
	.string "Hatched EGGS$"

MauvilleCity_PokemonCenter_1F_Text_EggsHatchedStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR eclosionó {STR_VAR_1}\n"
	.string "POKéMON de HUEVOS!\p"
	.string "{STR_VAR_3} es un experto\n"
	.string "en incubar HUEVOS!$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedTitle::
	.string "The Evolver TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedAction::
	.string "Evolved POKéMON$"

MauvilleCity_PokemonCenter_1F_Text_PokemonEvolvedStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR evolucionó {STR_VAR_1}\n"
	.string "¡evolucionar!\p"
	.string "{STR_VAR_3} es el maestro de la\n"
	.string "¡evolución POKéMON!$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterTitle::
	.string "The POKéMON CENTER-Loving TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterAction::
	.string "Used POKéMON CENTERS$"

MauvilleCity_PokemonCenter_1F_Text_UsedPokemonCenterStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR curó POKéMON\n"
	.string "{STR_VAR_1} veces en CENTROS POKéMON!\p"
	.string "No hay nadie que ame más los\n"
	.string "CENTROS POKéMON que {STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeTitle::
	.string "The Homebody TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeAction::
	.string "Rested POKéMON at home$"

MauvilleCity_PokemonCenter_1F_Text_RestedAtHomeStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR curó POKéMON\n"
	.string "¡{STR_VAR_1} veces en casa!\p"
	.string "No hay nadie más hogareño\n"
	.string "que {STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesTitle::
	.string "The SAFARI-Loving TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesAction::
	.string "Entered the SAFARI ZONE$"

MauvilleCity_PokemonCenter_1F_Text_SafariGamesStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR fue a la ZONA SAFARI\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} es un ENTRENADOR cuyo lado\n"
	.string "salvaje sale en la ZONA SAFARI!$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutTitle::
	.string "The CUT-Frenzy TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutAction::
	.string "Used CUT$"

MauvilleCity_PokemonCenter_1F_Text_UsedCutStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR usó CORTE\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} es un ENTRENADOR que\n"
	.string "simplemente ama usar CORTE!$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashTitle::
	.string "The ROCK-SMASHING TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashAction::
	.string "Smashed rocks$"

MauvilleCity_PokemonCenter_1F_Text_UsedRockSmashStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este TRAINER usó ROMPEROCAS\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe ser un TRAINER que\n"
	.string "¡no deja piedra sin romper!$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesTitle::
	.string "El ENTRENADOR amante de movs.$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesAction::
	.string "Moved the SECRET BASE$"

MauvilleCity_PokemonCenter_1F_Text_MovedBasesStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este TRAINER movió la BASE SECRETA\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} es un TRAINER que ama\n"
	.string "¡mudarse de casa a menudo!$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashTitle::
	.string "The SPLASH-Happy TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashAction::
	.string "Used SPLASH$"

MauvilleCity_PokemonCenter_1F_Text_UsedSplashStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR usó SALPICADURA\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} es un ENTRENADOR que ama\n"
	.string "¡salpicar por todas partes!$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleTitle::
	.string "The Tenacious TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleAction::
	.string "Recorrió a usar DESESPERAR$"

MauvilleCity_PokemonCenter_1F_Text_UsedStruggleStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR dependió de ESFUERZO\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} es un ENTRENADOR tenaz\n"
	.string "¡que jamás se rinde ante nada!$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsTitle::
	.string "The SLOT Champ$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsAction::
	.string "Ganó el gran premio en las TRAGAPERRAS$"

MauvilleCity_PokemonCenter_1F_Text_SlotJackpotsStory::
	.string "Es la historia de un ENTRENADOR\nllamado {STR_VAR_3}.\pEste ENTRENADOR ganó el gran premio\nen las TRAGAPERRAS {STR_VAR_1} veces.\p{STR_VAR_3} es un ENTRENADOR\ncon suerte en las TRAGAPERRAS!$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsTitle::
	.string "The ROULETTE Champ$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsAction::
	.string "Tuvo una racha en la RULETA de$"

MauvilleCity_PokemonCenter_1F_Text_RouletteWinsStory::
	.string "Es la historia de un ENTRENADOR\nllamado {STR_VAR_3}.\pEste ENTRENADOR ganó en la RULETA\n{STR_VAR_1} veces seguidas.\p{STR_VAR_3} tuvo suerte cuando\nla bola cayó en la RULETA!$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesTitle::
	.string "El retador de la TORRE BATALLA$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesAction::
	.string "Aceptó el reto de la TORRE BATALLA$"

MauvilleCity_PokemonCenter_1F_Text_BattleTowerChallengesStory::
	.string "Es la historia de un ENTRENADOR\nllamado {STR_VAR_3}.\pEste ENTRENADOR aceptó el reto de la\nTORRE BATALLA {STR_VAR_1} veces!\p{STR_VAR_3} es un ENTRENADOR que busca\nla excelencia en la TORRE BATALLA!$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksTitle::
	.string "The Blend-Loving TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksAction::
	.string "Made {POKEBLOCK}S$"

MauvilleCity_PokemonCenter_1F_Text_MadePokeblocksStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR hizo {POKEBLOCK}S\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "¡Nadie usa mejor la MEZCLADORA de\n"
	.string "BAYAS que {STR_VAR_3}!$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsTitle::
	.string "The CONTEST-Loving TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsAction::
	.string "Entered CONTESTS$"

MauvilleCity_PokemonCenter_1F_Text_EnteredContestsStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR participó en\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "CONCURSOS. {STR_VAR_3} debe amar\n"
	.string "lucir sus POKéMON ante otros!$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsTitle::
	.string "The CONTEST Master$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsAction::
	.string "Won CONTESTS$"

MauvilleCity_PokemonCenter_1F_Text_WonContestsStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR ganó CONCURSOS\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe ser un increíble\n"
	.string "maestro de CONCURSOS!$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedTitle::
	.string "The Happy Shopper$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedAction::
	.string "Shopped$"

MauvilleCity_PokemonCenter_1F_Text_TimesShoppedStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR compró objetos\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe ser de esas\n"
	.string "personas que nacieron para comprar.$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderTitle::
	.string "El ENTRENADOR buscador de objetos$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderAction::
	.string "Used an ITEMFINDER$"

MauvilleCity_PokemonCenter_1F_Text_UsedItemFinderStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR usó un BUSCAOBJ.\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe disfrutar buscando\n"
	.string "objetos ocultos en el suelo!$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedTitle::
	.string "The Rain-Soaked TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedAction::
	.string "Got rained on$"

MauvilleCity_PokemonCenter_1F_Text_TimesRainedStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR se empapó con la\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "lluvia. ¡El carisma de {STR_VAR_3}\n"
	.string "hasta atrae la lluvia!$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexTitle::
	.string "The Avid POKéDEX Reader$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexAction::
	.string "Checked a POKéDEX$"

MauvilleCity_PokemonCenter_1F_Text_CheckedPokedexStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR consultó una\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "POKéDEX. {STR_VAR_3} debe amar\n"
	.string "¡POKéMON en una POKéDEX!$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsTitle::
	.string "The RIBBON Collector$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsAction::
	.string "Received RIBBONS$"

MauvilleCity_PokemonCenter_1F_Text_ReceivedRibbonsStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR recibió CINTAS\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe ser un TRAINER que\n"
	.string "¡ama coleccionar CINTAS!$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedTitle::
	.string "The Ledge-Jumping TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedAction::
	.string "Jumped down ledges$"

MauvilleCity_PokemonCenter_1F_Text_LedgesJumpedStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR saltó salientes\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "Si hay un saliente para saltar,\n"
	.string "¡{STR_VAR_3} no puede ignorarlo!$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedTitle::
	.string "The Legendary TV Viewer$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedAction::
	.string "Watched TV$"

MauvilleCity_PokemonCenter_1F_Text_TVWatchedStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR vio la TV\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "¡{STR_VAR_3} ama ver la TV!$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockTitle::
	.string "The Time-Conscious TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockAction::
	.string "Checked the time$"

MauvilleCity_PokemonCenter_1F_Text_CheckedClockStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR revisó la hora\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe ser un ENTRENADOR\n"
	.string "muy puntual con el tiempo.$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryTitle::
	.string "The POKéMON LOTTERY Wizard$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryAction::
	.string "Won POKéMON LOTTERIES$"

MauvilleCity_PokemonCenter_1F_Text_WonLotteryStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR ganó LOTERÍAS\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe tener muchos amigos\n"
	.string "para intercambiar POKéMON!$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareTitle::
	.string "El ENTRENADOR de la GUARDERÍA$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareAction::
	.string "Dejó POKéMON en la GUARDERÍA$"

MauvilleCity_PokemonCenter_1F_Text_UsedDaycareStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR dejó POKéMON en el\n"
	.string "DAY CARE {STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe ser alguien muy\n"
	.string "activo criando sus POKéMON!$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarTitle::
	.string "The CABLE CAR-Loving TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarAction::
	.string "Rode the CABLE CAR$"

MauvilleCity_PokemonCenter_1F_Text_RodeCableCarStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR usó el TELEFÉRICO\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "{STR_VAR_3} debe ser un ENTRENADOR\n"
	.string "que viaja todo el tiempo!$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsTitle::
	.string "The Hot Spring-Loving TRAINER$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsAction::
	.string "Bathed in hot springs$"

MauvilleCity_PokemonCenter_1F_Text_HotSpringsStory::
	.string "Es la historia de un ENTRENADOR\n"
	.string "llamado {STR_VAR_3}.\p"
	.string "Este ENTRENADOR se bañó en\n"
	.string "¡{STR_VAR_1} veces!\p"
	.string "aguas termales. {STR_VAR_3} debe\n"
	.string "¡tener una piel muy suave!$"


MauvilleCity_PokemonCenter_1F_EventScript_Storyteller::
	lock
	faceplayer
	setvar VAR_0x8008, 0
	setvar VAR_0x8009, 0
	setvar VAR_0x800A, 0
	setvar VAR_0x800B, 0
	msgbox MauvilleCity_PokemonCenter_1F_Text_WillYouHearMyTale, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar VAR_RESULT, StorytellerGetFreeStorySlot
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales
	message MauvilleCity_PokemonCenter_1F_Text_WhichTaleToTell
	waitmessage
	special StorytellerStoryListMenu
	waitstate
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection
	setvar VAR_0x8008, 1
	special Script_StorytellerDisplayStory
	waitmessage
	waitbuttonpress
	specialvar VAR_RESULT, StorytellerUpdateStat
	goto_if_eq VAR_RESULT, 0, MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales
	goto MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale

MauvilleCity_PokemonCenter_1F_EventScript_CancelStorySelection::
	goto MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	end

MauvilleCity_PokemonCenter_1F_EventScript_AreThereOtherTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_CouldThereBeOtherLegends, MSGBOX_DEFAULT
	specialvar VAR_RESULT, HasStorytellerAlreadyRecorded
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd
	goto MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales

MauvilleCity_PokemonCenter_1F_EventScript_KnowNoTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_IKnowNoTales, MSGBOX_DEFAULT
MauvilleCity_PokemonCenter_1F_EventScript_DoYouHaveAnyTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_HaveYouAnyLegendaryTales, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller
	specialvar VAR_RESULT, Script_StorytellerInitializeRandomStat
	goto_if_eq VAR_RESULT, 1, MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale
	msgbox MauvilleCity_PokemonCenter_1F_Text_NotWorthyOfLegend, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_TellPlayersTale::
	msgbox MauvilleCity_PokemonCenter_1F_Text_YouDidStatXTimes, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineStoryteller::
	msgbox MauvilleCity_PokemonCenter_1F_Text_StorytellerFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

@ Unused
MauvilleCity_PokemonCenter_1F_EventScript_WaitingForRecordMix::
	msgbox MauvilleCity_PokemonCenter_1F_Text_IWishMorePeopleWereInterested, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_StorytellerEnd::
	release
	end

@ Giddy
MauvilleCity_PokemonCenter_1F_Text_HearMyStory:
	.string "¡Estoy EMOCIONADO!\n"
	.string "¡Tengo una historia genial para ti!\p"
	.string "¿Quieres escuchar mi historia?$"

MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues:
	.string "Oh...\n"
	.string "Me has dejado muy triste...$"

MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking:
	.string "Also, I was thinking...$"

MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain:
	.string "Eso es todo, creo...\p"
	.string "¡Deberíamos charlar otra vez!\n"
	.string "¡Adiós!$"

MauvilleCity_PokemonCenter_1F_EventScript_Giddy::
	lock
	faceplayer
	msgbox MauvilleCity_PokemonCenter_1F_Text_HearMyStory, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTellTale::
	special GiddyShouldTellAnotherTale
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale::
	special GiddyShouldTellAnotherTale
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales
	end

MauvilleCity_PokemonCenter_1F_EventScript_GiddyStartNewTale::
	msgbox MauvilleCity_PokemonCenter_1F_Text_AlsoIWasThinking, MSGBOX_DEFAULT
	goto MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale
	end

@ Giddy will continue to tell stories regardless of whether yes or no is selected below.
@ Each story there is a 10% chance it will be his last. Otherwise he will stop at 10 stories.
MauvilleCity_PokemonCenter_1F_EventScript_GiddyTellTale::
	special GenerateGiddyLine
	special ShowFieldMessageStringVar4
	waitmessage
	yesnobox 20, 8
	goto_if_eq VAR_RESULT, YES, MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	goto_if_eq VAR_RESULT, NO, MauvilleCity_PokemonCenter_1F_EventScript_TryTellNewTale
	end

MauvilleCity_PokemonCenter_1F_EventScript_DeclineGiddy::
	msgbox MauvilleCity_PokemonCenter_1F_Text_GiddyFeelingTheBlues, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_ToldEnoughTales::
	msgbox MauvilleCity_PokemonCenter_1F_Text_WeShouldChatAgain, MSGBOX_DEFAULT
	release
	end

MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToHearMySong:
	.string "Hola, soy el BARDO.\n"
	.string "¿Quieres escuchar mi canción?$"

MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues1:
	.string "Oh...\n"
	.string "Me has dejado muy triste...$"

MauvilleCity_PokemonCenter_1F_Text_WishICouldPlaySongForOthers:
	.string "Oh, qué canción tan emotiva...\n"
	.string "Desearía tocarla para otros...$"

MauvilleCity_PokemonCenter_1F_Text_WouldYouLikeToWriteSomeLyrics:
	.string "So?\n"
	.string "¿Qué te parece mi canción?\p"
	.string "Pero no estoy muy feliz con\n"
	.string "la letra.\p"
	.string "¿Te gustaría escribirme una\n"
	.string "letra nueva?$"

MauvilleCity_PokemonCenter_1F_Text_BardFeelingTheBlues2:
	.string "Oh...\n"
	.string "Me has dejado muy triste...$"

MauvilleCity_PokemonCenter_1F_Text_LetMeSingItForYou:
	.string "¡Muchas gracias!\n"
	.string "Déjame cantarla para ti.$"

MauvilleCity_PokemonCenter_1F_Text_ThatHowYouWantedSongToGo:
	.string "¿Así es como querías tu canción?\n"
	.string "to go?$"

MauvilleCity_PokemonCenter_1F_Text_IllSingThisSongForAWhile:
	.string "¡Bien! Entonces quedó así.\n"
	.string "Cantaré esta canción un tiempo.$"

MauvilleCity_PokemonCenter_1F_Text_TeachWhatsHipAndHappening:
	.string "¡Hey, yo! Me llaman el HIPSTER.\n"
	.string "¡Te enseñaré lo que está de moda!$"

MauvilleCity_PokemonCenter_1F_Text_IAlreadyTaughtYou:
	.string "Pero, oye, ya te enseñé lo que\n"
	.string "está de moda.\p"
	.string "Quisiera contarle estas cosas a\n"
	.string "otras personas.$"

MauvilleCity_PokemonCenter_1F_Text_IveGotNothingNewToTeach:
	.string "Pero ya sabes mucho sobre lo que\n"
	.string "está de moda.\p"
	.string "¡No tengo nada nuevo que enseñarte!$"

MauvilleCity_PokemonCenter_1F_Text_HaveYouHeardOfWord:
	.string "Oye, ¿has oído hablar de...?\n"
	.string "“{STR_VAR_1}”?\p"
	.string "¿Qué significa? Bueno...\n"
	.string "Pregúntale a tu papá o mamá, ¿sí?$"
