BattleFrontier_BattlePyramidFloor_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattlePyramidFloor_OnResume
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePyramidFloor_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattlePyramidFloor_OnTransition
	.byte 0

BattleFrontier_BattlePyramidFloor_OnFrame:
	map_script_2 VAR_TEMP_D, 1, BattleFrontier_BattlePyramidFloor_EventScript_UpdateLight
	map_script_2 VAR_TEMP_PLAYING_PYRAMID_MUSIC, 0, BattleFrontier_BattlePyramidFloor_EventScript_PlayPyramidMusic
	map_script_2 VAR_TEMP_F, 1, BattleFrontier_BattlePyramidFloor_EventScript_ShowMapName
	.2byte 0

BattleFrontier_BattlePyramidFloor_EventScript_UpdateLight::
	lockall
	@ pyramid_updatelight, cant use macro because it straddles the loop
	setvar VAR_0x8004, BATTLE_PYRAMID_FUNC_UPDATE_LIGHT
	setvar VAR_0x8005, 4
	setvar VAR_0x8006, PYRAMID_LIGHT_INCR_RADIUS
	setvar VAR_0x8007, SE_SAVE
	setvar VAR_RESULT, 0
BattleFrontier_BattlePyramidFloor_EventScript_UpdateLightLoop::
	special CallBattlePyramidFunction
	delay 2
	goto_if_ne VAR_RESULT, 2, BattleFrontier_BattlePyramidFloor_EventScript_UpdateLightLoop
	setvar VAR_TEMP_D, 0
	releaseall
	end

BattleFrontier_BattlePyramidFloor_EventScript_ShowMapName::
	special ShowMapNamePopup
	setvar VAR_TEMP_F, 0
	end

BattleFrontier_BattlePyramidFloor_EventScript_PlayPyramidMusic::
	playbgm MUS_B_PYRAMID, FALSE
	setvar VAR_TEMP_PLAYING_PYRAMID_MUSIC, 1
	end

BattleFrontier_BattlePyramidFloor_OnResume:
	pyramid_setfloorpal
	frontier_getstatus
	switch VAR_TEMP_CHALLENGE_STATUS
	case 0, BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge
	case CHALLENGE_STATUS_SAVING, BattleFrontier_BattlePyramid_EventScript_WarpToLobby
	case CHALLENGE_STATUS_PAUSED, BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge
	frontier_get FRONTIER_DATA_BATTLE_OUTCOME
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, 0, BattleFrontier_BattlePyramidFloor_EventScript_ResetParty
	goto_if_eq VAR_RESULT, B_OUTCOME_LOST, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	goto_if_eq VAR_RESULT, B_OUTCOME_DREW, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	goto_if_eq VAR_RESULT, B_OUTCOME_FORFEITED, BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost
	frontier_isbattletype BATTLE_TYPE_TRAINER  @ VAR_RESULT seems to be ignored here
	setvar VAR_TEMP_D, 1
BattleFrontier_BattlePyramidFloor_EventScript_ResetParty::
	pyramid_resetparty
	end

BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST
	pyramid_set PYRAMID_DATA_TRAINER_FLAGS, 255
BattleFrontier_BattlePyramid_EventScript_WarpToLobby::
	pyramid_updatelight 0, PYRAMID_LIGHT_SET_RADIUS
	pyramid_clearhelditems
	special HealPlayerParty
	warpsilent MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_LOBBY, 7, 13
	waitstate
	end

BattleFrontier_BattlePyramidFloor_EventScript_ReadyChallenge::
	pyramid_save CHALLENGE_STATUS_SAVING
	special SavePlayerParty
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	pyramid_settrainers
	frontier_setpartyorder FRONTIER_PARTY_SIZE
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidFloor_OnTransition:
	call BattleFrontier_BattlePyramidFloor_EventScript_SetLightRadius
	setvar VAR_TEMP_F, 1
	end

BattleFrontier_BattlePyramidFloor_EventScript_SetLightRadius::
	pyramid_updatelight 32, PYRAMID_LIGHT_SET_RADIUS
	return

BattlePyramid_WarpToNextFloor::
	call BattleFrontier_EventScript_IncrementWinStreak
	frontier_get FRONTIER_DATA_BATTLE_NUM  @ Floor number
	addvar VAR_RESULT, 1
	frontier_set FRONTIER_DATA_BATTLE_NUM, VAR_RESULT
	goto_if_eq VAR_RESULT, 7, BattlePyramid_WarpToTop
	pyramid_seedfloor
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, 0
	setvar VAR_RESULT, 0
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_FLOOR, 1, 1
	waitstate
	end

BattlePyramid_WarpToTop::
	warp MAP_BATTLE_FRONTIER_BATTLE_PYRAMID_TOP, 17, 17
	waitstate
	end

@ TRAINER_PHILLIP is used as a placeholder
BattlePyramid_TrainerBattle::
	facilitytrainerbattle FACILITY_BATTLE_PYRAMID
	pyramid_showhint
	waitmessage
	waitbuttonpress
	closemessage
	releaseall
	end

BattlePyramid_FindItemBall::
	pyramid_setitem
	callstd STD_FIND_ITEM
	goto_if_eq VAR_0x8007, 0, BattlePyramid_FindItemBallEnd
	pyramid_hideitem
BattlePyramid_FindItemBallEnd::
	end

BattlePyramid_Retire::
	goto BattleFrontier_BattlePyramid_EventScript_WarpToLobbyLost

@ Also used by Trainer Hill
BattleFacility_TrainerBattle_PlaceholderText:
	.string "This is a sample message.$"

gText_BattlePyramidConfirmRest::
	.string "Tu reto de la PIRÁMIDE BATALLA\n"
	.string "se guardará para que puedas salir.\l"
	.string "Is that okay?$"

gText_BattlePyramidConfirmRetire::
	.string "¿Estás seguro de que quieres dejar\n"
	.string "tu reto de la PIRÁMIDE?$"

BattlePyramid_Text_ExitHintUp1::
	.string "La salida de este piso está en\n"
	.string "esa dirección: {UP_ARROW}$"

BattlePyramid_Text_ExitHintLeft1::
	.string "La salida de este piso está en\n"
	.string "esa dirección: {LEFT_ARROW}$"

BattlePyramid_Text_ExitHintRight1::
	.string "La salida de este piso está en\n"
	.string "esa dirección: {RIGHT_ARROW}$"

BattlePyramid_Text_ExitHintDown1::
	.string "La salida de este piso está en\n"
	.string "esa dirección: {DOWN_ARROW}$"

BattlePyramid_Text_ExitHintUp2::
	.string "La salida de este piso está en\n"
	.string "la dirección {UP_ARROW}.$"

BattlePyramid_Text_ExitHintLeft2::
	.string "La salida de este piso está en\n"
	.string "la dirección {LEFT_ARROW}.$"

BattlePyramid_Text_ExitHintRight2::
	.string "La salida de este piso está en\n"
	.string "la dirección {RIGHT_ARROW}.$"

BattlePyramid_Text_ExitHintDown2::
	.string "La salida de este piso está en\n"
	.string "la dirección {DOWN_ARROW}.$"

BattlePyramid_Text_ExitHintUp3::
	.string "La salida está por\n"
	.string "aquél camino {UP_ARROW}.$"

BattlePyramid_Text_ExitHintLeft3::
	.string "La salida está por\n"
	.string "aquél camino {LEFT_ARROW}.$"

BattlePyramid_Text_ExitHintRight3::
	.string "La salida está por\n"
	.string "aquél camino {RIGHT_ARROW}.$"

BattlePyramid_Text_ExitHintDown3::
	.string "La salida está por\n"
	.string "aquél camino {DOWN_ARROW}.$"

BattlePyramid_Text_ExitHintUp4::
	.string "En este piso, la salida está\n"
	.string "hacia el {UP_ARROW}.$"

BattlePyramid_Text_ExitHintLeft4::
	.string "En este piso, la salida está\n"
	.string "hacia el {LEFT_ARROW}.$"

BattlePyramid_Text_ExitHintRight4::
	.string "En este piso, la salida está\n"
	.string "hacia el {RIGHT_ARROW}.$"

BattlePyramid_Text_ExitHintDown4::
	.string "En este piso, la salida está\n"
	.string "en dirección {DOWN_ARROW}.$"

BattlePyramid_Text_ExitHintUp5::
	.string "¿La salida?\n"
	.string "Es por allá {UP_ARROW}.$"

BattlePyramid_Text_ExitHintLeft5::
	.string "¿La salida?\n"
	.string "Es por allá {LEFT_ARROW}.$"

BattlePyramid_Text_ExitHintRight5::
	.string "¿La salida?\n"
	.string "Es por allá {RIGHT_ARROW}.$"

BattlePyramid_Text_ExitHintDown5::
	.string "¿La salida?\n"
	.string "Es por allá {DOWN_ARROW}.$"

BattlePyramid_Text_ExitHintUp6::
	.string "La salida se encuentra en\n"
	.string "la dirección {UP_ARROW}.$"

BattlePyramid_Text_ExitHintLeft6::
	.string "La salida se encuentra en\n"
	.string "la dirección {LEFT_ARROW}.$"

BattlePyramid_Text_ExitHintRight6::
	.string "La salida se encuentra en\n"
	.string "la dirección {RIGHT_ARROW}.$"

BattlePyramid_Text_ExitHintDown6::
	.string "La salida se encuentra en\n"
	.string "la dirección {DOWN_ARROW}.$"

BattlePyramid_Text_EightItemsRemaining1::
	.string "¿Buscas objetos?\p"
	.string "Quedan ocho objetos por\n"
	.string "encontrar.$"

BattlePyramid_Text_SevenItemsRemaining1::
	.string "¿Buscas objetos?\p"
	.string "Quedan siete objetos por\n"
	.string "encontrar.$"

BattlePyramid_Text_SixItemsRemaining1::
	.string "¿Buscas objetos?\p"
	.string "Quedan seis objetos por\n"
	.string "encontrar.$"

BattlePyramid_Text_FiveItemsRemaining1::
	.string "¿Buscas objetos?\p"
	.string "Quedan cinco objetos por\n"
	.string "encontrar.$"

BattlePyramid_Text_FourItemsRemaining1::
	.string "¿Buscas objetos?\p"
	.string "Quedan cuatro objetos por\n"
	.string "encontrar.$"

BattlePyramid_Text_ThreeItemsRemaining1::
	.string "¿Buscas objetos?\p"
	.string "Quedan tres objetos por\n"
	.string "encontrar.$"

BattlePyramid_Text_TwoItemsRemaining1::
	.string "¿Buscas objetos?\p"
	.string "Quedan dos objetos por\n"
	.string "encontrar.$"

BattlePyramid_Text_OneItemRemaining1::
	.string "¿Buscas objetos?\p"
	.string "Queda un objeto por\n"
	.string "encontrar.$"

BattlePyramid_Text_ZeroItemsRemaining1::
	.string "¿Buscas objetos?\p"
	.string "Ya no queda nada por\n"
	.string "¡encontrar!$"

BattlePyramid_Text_EightItemsRemaining2::
	.string "Como ganaste, te diré\n"
	.string "¡un pequeño secreto!\p"
	.string "Hay ocho objetos\n"
	.string "esparcidos por aquí.$"

BattlePyramid_Text_SevenItemsRemaining2::
	.string "Como ganaste, te diré\n"
	.string "¡un pequeño secreto!\p"
	.string "Quedan siete objetos\n"
	.string "esparcidos por aquí.$"

BattlePyramid_Text_SixItemsRemaining2::
	.string "Como ganaste, te diré\n"
	.string "¡un pequeño secreto!\p"
	.string "Quedan seis objetos\n"
	.string "esparcidos por aquí.$"

BattlePyramid_Text_FiveItemsRemaining2::
	.string "Como ganaste, te diré\n"
	.string "¡un pequeño secreto!\p"
	.string "Quedan cinco objetos\n"
	.string "esparcidos por aquí.$"

BattlePyramid_Text_FourItemsRemaining2::
	.string "Como ganaste, te diré\n"
	.string "¡un pequeño secreto!\p"
	.string "Quedan cuatro objetos\n"
	.string "esparcidos por aquí.$"

BattlePyramid_Text_ThreeItemsRemaining2::
	.string "Como ganaste, te diré\n"
	.string "¡un pequeño secreto!\p"
	.string "Quedan tres objetos\n"
	.string "esparcidos por aquí.$"

BattlePyramid_Text_TwoItemsRemaining2::
	.string "Como ganaste, te diré\n"
	.string "¡un pequeño secreto!\p"
	.string "Quedan dos objetos\n"
	.string "esparcidos por aquí.$"

BattlePyramid_Text_OneItemRemaining2::
	.string "Como ganaste, te diré\n"
	.string "¡un pequeño secreto!\p"
	.string "Solo queda un objeto\n"
	.string "esparcidos por aquí.$"

BattlePyramid_Text_ZeroItemsRemaining2::
	.string "Como ganaste, te diré\n"
	.string "¡un pequeño secreto!\p"
	.string "Ya no queda nada\n"
	.string "esparcidos por aquí.$"

BattlePyramid_Text_EightItemsRemaining3::
	.string "¿Cómo va tu reserva de objetos?\p"
	.string "Creo que quedan ocho objetos\n"
	.string "por encontrar en este piso.$"

BattlePyramid_Text_SevenItemsRemaining3::
	.string "¿Cómo va tu reserva de objetos?\p"
	.string "Creo que quedan siete objetos\n"
	.string "por encontrar en este piso.$"

BattlePyramid_Text_SixItemsRemaining3::
	.string "¿Cómo va tu reserva de objetos?\p"
	.string "Creo que quedan seis objetos\n"
	.string "por encontrar en este piso.$"

BattlePyramid_Text_FiveItemsRemaining3::
	.string "¿Cómo va tu reserva de objetos?\p"
	.string "Creo que quedan cinco objetos\n"
	.string "por encontrar en este piso.$"

BattlePyramid_Text_FourItemsRemaining3::
	.string "¿Cómo va tu reserva de objetos?\p"
	.string "Creo que quedan cuatro objetos\n"
	.string "por encontrar en este piso.$"

BattlePyramid_Text_ThreeItemsRemaining3::
	.string "¿Cómo va tu reserva de objetos?\p"
	.string "Creo que quedan tres objetos\n"
	.string "por encontrar en este piso.$"

BattlePyramid_Text_TwoItemsRemaining3::
	.string "¿Cómo va tu reserva de objetos?\p"
	.string "Creo que quedan dos objetos\n"
	.string "por encontrar en este piso.$"

BattlePyramid_Text_OneItemRemaining3::
	.string "¿Cómo va tu reserva de objetos?\p"
	.string "Creo que solo queda un objeto\n"
	.string "por encontrar en este piso.$"

BattlePyramid_Text_ZeroItemsRemaining3::
	.string "¿Cómo va tu reserva de objetos?\p"
	.string "Creo que ya no quedan objetos\n"
	.string "por encontrar en este piso.\l"
	.string "¡Cuídate mucho!$"

BattlePyramid_Text_EightItemsRemaining4::
	.string "Eres fuerte, así que te has\n"
	.string "ganado una pista!\p"
	.string "Parece que hay ocho objetos\n"
	.string "más en el suelo.$"

BattlePyramid_Text_SevenItemsRemaining4::
	.string "Eres fuerte, así que te has\n"
	.string "ganado una pista!\p"
	.string "Parece que quedan siete\n"
	.string "más en el suelo.$"

BattlePyramid_Text_SixItemsRemaining4::
	.string "Eres fuerte, así que te has\n"
	.string "ganado una pista!\p"
	.string "Parece que quedan seis\n"
	.string "más en el suelo.$"

BattlePyramid_Text_FiveItemsRemaining4::
	.string "Eres fuerte, así que te has\n"
	.string "ganado una pista!\p"
	.string "Parece que quedan cinco\n"
	.string "más en el suelo.$"

BattlePyramid_Text_FourItemsRemaining4::
	.string "Eres fuerte, así que te has\n"
	.string "ganado una pista!\p"
	.string "Parece que quedan cuatro\n"
	.string "más en el suelo.$"

BattlePyramid_Text_ThreeItemsRemaining4::
	.string "Eres fuerte, así que te has\n"
	.string "ganado una pista!\p"
	.string "Parece que quedan tres\n"
	.string "más en el suelo.$"

BattlePyramid_Text_TwoItemsRemaining4::
	.string "Eres fuerte, así que te has\n"
	.string "ganado una pista!\p"
	.string "Parece que quedan dos\n"
	.string "más en el suelo.$"

BattlePyramid_Text_OneItemRemaining4::
	.string "Eres fuerte, así que te has\n"
	.string "ganado una pista!\p"
	.string "Parece que solo queda uno\n"
	.string "objeto en el suelo.$"

BattlePyramid_Text_ZeroItemsRemaining4::
	.string "Eres fuerte, así que te has\n"
	.string "ganado una pista!\p"
	.string "Parece que ya no quedan\n"
	.string "más en el suelo.$"

BattlePyramid_Text_EightItemsRemaining5::
	.string "En este piso de la PIRÁMIDE,\n"
	.string "oigo que hay ocho objetos…$"

BattlePyramid_Text_SevenItemsRemaining5::
	.string "En este piso de la PIRÁMIDE,\n"
	.string "oigo que hay siete objetos…$"

BattlePyramid_Text_SixItemsRemaining5::
	.string "En este piso de la PIRÁMIDE,\n"
	.string "Oigo que hay seis objetos…$"

BattlePyramid_Text_FiveItemsRemaining5::
	.string "En este piso de la PIRÁMIDE,\n"
	.string "Oigo que hay cinco objetos…$"

BattlePyramid_Text_FourItemsRemaining5::
	.string "En este piso de la PIRÁMIDE,\n"
	.string "Oigo que hay cuatro objetos…$"

BattlePyramid_Text_ThreeItemsRemaining5::
	.string "En este piso de la PIRÁMIDE,\n"
	.string "Oigo que hay tres objetos…$"

BattlePyramid_Text_TwoItemsRemaining5::
	.string "En este piso de la PIRÁMIDE,\n"
	.string "Oigo que hay dos objetos…$"

BattlePyramid_Text_OneItemRemaining5::
	.string "En este piso de la PIRÁMIDE,\n"
	.string "Oigo que hay un objeto…$"

BattlePyramid_Text_ZeroItemsRemaining5::
	.string "En este piso de la PIRÁMIDE,\n"
	.string "Oigo que no hay objetos…$"

BattlePyramid_Text_EightItemsRemaining6::
	.string "¿Has recogido algún objeto?\p"
	.string "Creo que quedan ocho objetos\n"
	.string "más en este piso.$"

BattlePyramid_Text_SevenItemsRemaining6::
	.string "¿Has recogido algún objeto?\p"
	.string "Creo que quedan siete objetos\n"
	.string "más en este piso.$"

BattlePyramid_Text_SixItemsRemaining6::
	.string "¿Has recogido algún objeto?\p"
	.string "Creo que quedan seis objetos\n"
	.string "más en este piso.$"

BattlePyramid_Text_FiveItemsRemaining6::
	.string "¿Has recogido algún objeto?\p"
	.string "Creo que quedan cinco\n"
	.string "más en este piso.$"

BattlePyramid_Text_FourItemsRemaining6::
	.string "¿Has recogido algún objeto?\p"
	.string "Creo que quedan cuatro\n"
	.string "más en este piso.$"

BattlePyramid_Text_ThreeItemsRemaining6::
	.string "¿Has recogido algún objeto?\p"
	.string "Creo que quedan tres\n"
	.string "más en este piso.$"

BattlePyramid_Text_TwoItemsRemaining6::
	.string "¿Has recogido algún objeto?\p"
	.string "Creo que quedan dos\n"
	.string "más en este piso.$"

BattlePyramid_Text_OneItemRemaining6::
	.string "¿Has recogido algún objeto?\p"
	.string "Creo que queda uno\n"
	.string "objeto en este piso.$"

BattlePyramid_Text_ZeroItemsRemaining6::
	.string "¿Has recogido algún objeto?\p"
	.string "Creo que ya no quedan más\n"
	.string "más en este piso.$"

BattlePyramid_Text_SevenTrainersRemaining1::
	.string "¡Fuiste realmente increíble!\p"
	.string "¡Pero aún quedan siete\n"
	.string "ENTRENADORES fuertes aparte de mí!$"

BattlePyramid_Text_SixTrainersRemaining1::
	.string "¡Fuiste realmente increíble!\p"
	.string "¡Pero aún quedan seis\n"
	.string "ENTRENADORES fuertes aparte de mí!$"

BattlePyramid_Text_FiveTrainersRemaining1::
	.string "¡Fuiste realmente increíble!\p"
	.string "¡Pero aún quedan cinco\n"
	.string "ENTRENADORES fuertes aparte de mí!$"

BattlePyramid_Text_FourTrainersRemaining1::
	.string "¡Fuiste realmente increíble!\p"
	.string "Pero aún quedan cuatro\n"
	.string "ENTRENADORES fuertes aparte de mí!$"

BattlePyramid_Text_ThreeTrainersRemaining1::
	.string "¡Fuiste realmente increíble!\p"
	.string "Pero aún quedan tres\n"
	.string "ENTRENADORES fuertes aparte de mí!$"

BattlePyramid_Text_TwoTrainersRemaining1::
	.string "¡Fuiste realmente increíble!\p"
	.string "Pero aún quedan dos\n"
	.string "ENTRENADORES fuertes aparte de mí!$"

BattlePyramid_Text_OneTrainersRemaining1::
	.string "¡Fuiste realmente increíble!\p"
	.string "Pero aún queda un\n"
	.string "¡ENTRENADOR fuerte aparte de mí!$"

BattlePyramid_Text_ZeroTrainersRemaining1::
	.string "¡Fuiste realmente increíble!\p"
	.string "¡Ya no queda nadie que\n"
	.string "pueda vencerte!$"

BattlePyramid_Text_SevenTrainersRemaining2::
	.string "¡Esto es muy frustrante!\p"
	.string "¡Pero quedan siete ENTRENADORES!\n"
	.string "¡Alguien te pondrá en tu lugar!$"

BattlePyramid_Text_SixTrainersRemaining2::
	.string "¡Esto es muy frustrante!\p"
	.string "¡Pero quedan seis ENTRENADORES!\n"
	.string "¡Alguien te pondrá en tu lugar!$"

BattlePyramid_Text_FiveTrainersRemaining2::
	.string "¡Esto es muy frustrante!\p"
	.string "¡Pero quedan cinco ENTRENADORES!\n"
	.string "¡Alguien te pondrá en tu lugar!$"

BattlePyramid_Text_FourTrainersRemaining2::
	.string "¡Esto es muy frustrante!\p"
	.string "¡Pero quedan cuatro ENTRENADORES!\n"
	.string "¡Alguien te pondrá en tu lugar!$"

BattlePyramid_Text_ThreeTrainersRemaining2::
	.string "¡Esto es muy frustrante!\p"
	.string "¡Pero quedan tres ENTRENADORES!\n"
	.string "¡Alguien te pondrá en tu lugar!$"

BattlePyramid_Text_TwoTrainersRemaining2::
	.string "¡Esto es muy frustrante!\p"
	.string "¡Pero quedan dos ENTRENADORES!\n"
	.string "¡Alguien te pondrá en tu lugar!$"

BattlePyramid_Text_OneTrainersRemaining2::
	.string "¡Esto es muy frustrante!\p"
	.string "¡Pero queda un ENTRENADOR!\n"
	.string "¡Seguro que te darán una lección!$"

BattlePyramid_Text_ZeroTrainersRemaining2::
	.string "¡Esto es muy frustrante!\p"
	.string "Pero ya no quedan más ENTRENADORES\n"
	.string "que puedan enfrentarse a ti!$"

BattlePyramid_Text_SevenTrainersRemaining3::
	.string "¡Eso es muy impresionante!\p"
	.string "Pero hay siete ENTRENADORES más\n"
	.string "en este piso. ¿Podrás vencerlos?$"

BattlePyramid_Text_SixTrainersRemaining3::
	.string "¡Eso es muy impresionante!\p"
	.string "Pero hay seis ENTRENADORES más\n"
	.string "en este piso. ¿Podrás vencerlos?$"

BattlePyramid_Text_FiveTrainersRemaining3::
	.string "¡Eso es muy impresionante!\p"
	.string "Pero hay cinco ENTRENADORES más\n"
	.string "en este piso. ¿Podrás vencerlos?$"

BattlePyramid_Text_FourTrainersRemaining3::
	.string "¡Eso es muy impresionante!\p"
	.string "Pero quedan cuatro ENTRENADORES\n"
	.string "en este piso. ¿Podrás vencerlos?$"

BattlePyramid_Text_ThreeTrainersRemaining3::
	.string "¡Eso es muy impresionante!\p"
	.string "Pero quedan tres ENTRENADORES\n"
	.string "en este piso. ¿Podrás vencerlos?$"

BattlePyramid_Text_TwoTrainersRemaining3::
	.string "¡Eso es muy impresionante!\p"
	.string "Pero quedan dos ENTRENADORES\n"
	.string "en este piso. ¿Vencerás a ambos?$"

BattlePyramid_Text_OneTrainersRemaining3::
	.string "¡Eso es muy impresionante!\p"
	.string "Pero aún queda un ENTRENADOR\n"
	.string "en este piso. ¿Podrás ganar?$"

BattlePyramid_Text_ZeroTrainersRemaining3::
	.string "¡Eso es muy impresionante!\p"
	.string "Ya derrotaste a todos los\n"
	.string "ENTRENADORES de este piso.$"

BattlePyramid_Text_SevenTrainersRemaining4::
	.string "Tal vez podrías derrotar a\n"
	.string "los siete ENTRENADORES que quedan.$"

BattlePyramid_Text_SixTrainersRemaining4::
	.string "Tal vez podrías derrotar a\n"
	.string "los seis ENTRENADORES que quedan.$"

BattlePyramid_Text_FiveTrainersRemaining4::
	.string "Tal vez podrías derrotar a\n"
	.string "los cinco ENTRENADORES que quedan.$"

BattlePyramid_Text_FourTrainersRemaining4::
	.string "Tal vez podrías derrotar a\n"
	.string "los cuatro ENTRENADORES que quedan.$"

BattlePyramid_Text_ThreeTrainersRemaining4::
	.string "Tal vez podrías derrotar a\n"
	.string "los tres ENTRENADORES que quedan.$"

BattlePyramid_Text_TwoTrainersRemaining4::
	.string "Tal vez podrías derrotar a\n"
	.string "los dos ENTRENADORES que quedan.$"

BattlePyramid_Text_OneTrainersRemaining4::
	.string "Tal vez podrías completar tu racha\n"
	.string "con el ENTRENADOR que queda aquí.$"

BattlePyramid_Text_ZeroTrainersRemaining4::
	.string "Ya no queda ni una sola persona que\n"
	.string "pueda derrotarte ahora…$"

BattlePyramid_Text_SevenTrainersRemaining5::
	.string "Puede que tengas lo necesario para\n"
	.string "the seven expert TRAINERS who remain.$"

BattlePyramid_Text_SixTrainersRemaining5::
	.string "Puede que tengas lo necesario para\n"
	.string "vencer a los seis expertos que quedan.$"

BattlePyramid_Text_FiveTrainersRemaining5::
	.string "Puede que tengas lo necesario para\n"
	.string "the five expert TRAINERS who remain.$"

BattlePyramid_Text_FourTrainersRemaining5::
	.string "Puede que tengas lo necesario para\n"
	.string "the four expert TRAINERS who remain.$"

BattlePyramid_Text_ThreeTrainersRemaining5::
	.string "Puede que tengas lo necesario para\n"
	.string "los tres EXPERTOS que quedan.$"

BattlePyramid_Text_TwoTrainersRemaining5::
	.string "Puede que tengas lo necesario para\n"
	.string "los dos EXPERTOS que quedan.$"

BattlePyramid_Text_OneTrainersRemaining5::
	.string "Puede que tengas lo necesario para\n"
	.string "el único ENTRENADOR experto restante.$"

BattlePyramid_Text_ZeroTrainersRemaining5::
	.string "Tus habilidades son impecables.\p"
	.string "Ya no quedan ENTRENADORES aquí\n"
	.string "que tengan chance de vencerte.$"

BattlePyramid_Text_SevenTrainersRemaining6::
	.string "¿Podrás seguir ganando a\n"
	.string "los siete ENTRENADORES restantes?$"

BattlePyramid_Text_SixTrainersRemaining6::
	.string "¿Podrás seguir ganando a\n"
	.string "los seis ENTRENADORES restantes?$"

BattlePyramid_Text_FiveTrainersRemaining6::
	.string "¿Podrás seguir ganando a\n"
	.string "los cinco ENTRENADORES restantes?$"

BattlePyramid_Text_FourTrainersRemaining6::
	.string "¿Podrás seguir ganando a\n"
	.string "los cuatro ENTRENADORES restantes?$"

BattlePyramid_Text_ThreeTrainersRemaining6::
	.string "¿Podrás seguir ganando a\n"
	.string "los tres ENTRENADORES restantes?$"

BattlePyramid_Text_TwoTrainersRemaining6::
	.string "¿Podrás seguir ganando a\n"
	.string "¿a los dos ENTRENADORES restantes?$"

BattlePyramid_Text_OneTrainersRemaining6::
	.string "¿Podrás seguir ganando a\n"
	.string "¿al último ENTRENADOR restante?$"

BattlePyramid_Text_ZeroTrainersRemaining6::
	.string "No quedan ENTRENADORES que\n"
	.string "puedan luchar contra ti ahora…$"
