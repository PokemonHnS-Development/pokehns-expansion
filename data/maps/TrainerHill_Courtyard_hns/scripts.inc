TrainerHill_Courtyard_hns_MapScripts::
map_script MAP_SCRIPT_ON_TRANSITION, TrainerHill_Courtyard_OnTransition
	.byte 0

TrainerHill_Courtyard_OnTransition::
	setvar VAR_TRAINER_HILL_IS_ACTIVE, 0
	end

TrainerHill_Courtyard_EventScript_BattleTowerSign::
	lock
	msgbox BattleTowerOutsideSignText, MSGBOX_SIGN	
	closemessage	
	release
	end

TrainerHill_Courtyard_EventScript_Tent_Factory::
	lock
	msgbox BattleTower_Battle_Tent_Text_Factory, MSGBOX_SIGN	
	closemessage	
	release
	end

TrainerHill_Courtyard_EventScript_Tent_Palace::
	lock
	msgbox BattleTower_Battle_Tent_Text_Palace, MSGBOX_SIGN	
	closemessage	
	release
	end

TrainerHill_Courtyard_EventScript_Tent_Arena::
	lock
	msgbox BattleTower_Battle_Tent_Text_Arena, MSGBOX_SIGN	
	closemessage	
	release
	end
	
TrainerHill_Courtyard_EventScript_Engineer::
	lock
	faceplayer
	msgbox BattleTowerOutsideText_Closed, MSGBOX_DEFAULT
	closemessage
	release
	end

TrainerHill_Courtyard_EventScript_Youngster::
	lock
	faceplayer
	msgbox BattleTowerOutsideYoungsterText, MSGBOX_DEFAULT
	closemessage
	release
	end

TrainerHill_Courtyard_EventScript_Beauty::
	lock
	faceplayer
	msgbox BattleTowerOutsideBeautyText, MSGBOX_DEFAULT
	closemessage
	release
	end

TrainerHill_Courtyard_EventScript_Sailor::
	lock
	faceplayer
	msgbox BattleTowerOutsideSailorText, MSGBOX_DEFAULT
	closemessage
	release
	end

BattleTowerOutsideYoungsterText:
	.string "¡Vaya, la COLINA ENTRENADOR es enorme!\p"
	.string "¡Debe haber muchos tipos de\n"
	.string "POKéMON allí!$"

BattleTowerOutsideBeautyText:
	.string "En las CARPAS DE BATALLA, solo\n"
	.string "puedes usar tres POKéMON.\p"
	.string "Es muy difícil decidir qué\n"
	.string "tres irán a la batalla…$"

BattleTowerOutsideSailorText:
	.string "Jejeje, me escapé del trabajo.\p
¡No puedo rendirme hasta ganar!\p
Tengo que ganarlo todo. ¡Debo hacerlo!$"

BattleTowerOutsideSignText:
	.string "{UP_ARROW} ENTRADA COLINA ENTRENADOR\p"
	.string "¡Lleguen a la cima, ENTRENADORES\n"
	.string "¡ENTRENADORES!\p"
	.string "{RIGHT_ARROW} CARPAS DE BATALLA.$"

BattleTower_Battle_Tent_Text_Factory:
	.string "CARPA BATALLA: FÁBRICA\n"
	.string "“¡Búscalo! ¡El POKéMON definitivo!”$"

BattleTower_Battle_Tent_Text_Palace:
	.string "CARPA BATALLA: PALACIO\n"
	.string "¡Mira estas batallas!$"

BattleTower_Battle_Tent_Text_Arena:
	.string "TIENDA BATALLA: ARENA\n"
	.string "¡Que se reúnan los mejores equipos!$"

BattleTowerOutsideText_Closed:
	.string "La COLINA ENTRENADOR está actualmente\n
cerrada por reparaciones.$"


TrainerHill_Courtyard_EventScript_LeftMoveTutor::
	goto BattleFrontier_Lounge7_EventScript_LeftMoveTutor_hns
	end

TrainerHill_Courtyard_EventScript_RightMoveTutor::
	goto BattleFrontier_Lounge7_EventScript_RightMoveTutor_hns
	end

TrainerHill_Courtyard_EventScript_ElementalMoveTutor::
	goto BattleFrontier_Lounge7_EventScript_ElementalMoveTutor
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_DecorClerk1::
	lock
	faceplayer
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize, MSGBOX_DEFAULT
	special CreateBPDecorShop1
	waitstate
	release
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_DecorClerk2::
	lock
	faceplayer
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize, MSGBOX_DEFAULT
	special CreateBPDecorShop2
	waitstate
	release
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_VitaminClerk::
	lock
	faceplayer
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize, MSGBOX_DEFAULT
	special CreateBPVitaminShop
	waitstate
	release
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_HoldItemClerk::
	lock
	faceplayer
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize, MSGBOX_DEFAULT
	special CreateBPHoldItemShop
	waitstate
	release
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_HoldItemClerk2::
	lock
	faceplayer
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize, MSGBOX_DEFAULT
	special CreateBPHoldItemShop2
	waitstate
	release
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_PowerClerk::
	lock
	faceplayer
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize, MSGBOX_DEFAULT
	special CreateBPPowerShop
	waitstate
	release
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Man::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_GoGetYourOwnDoll, MSGBOX_NPC
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Sailor::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_ItemsWillGetMonTougher, MSGBOX_NPC
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_PokefanF::
	lock
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_GetYouAnythingYouWant, MSGBOX_DEFAULT
	release
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_RichBoy::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_WishIHadAllDolls, MSGBOX_NPC
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_Girl::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_Text_MoreBattlePointsForRecord, MSGBOX_NPC
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_OldWTMan::
	msgbox TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_OldWTMan_Text, MSGBOX_NPC
	end

TrainerHill_Courtyard_ExchangeServiceCorner_EventScript_OldWTMan_Text:
	.string "¡Hola! Si buscas el\n"
	.string "WONDERTRADE, ahora están en\l"
	.string "cada CENTRO POKéMON. ¡Diviértete!$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize:
	.string "Hola, este es el SERVICIO DE\n"
	.string "CANJE.\p"
	.string "Canjeamos tus Puntos de Batalla\n"
	.string "por premios fantásticos.\p"
	.string "Elige un premio de la lista.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_WishIHadAllDolls:
	.string "¡Oh, son tan lindos!\n"
	.string "¡Desearía tenerlos!\l"
	.string "¡Qué lindos cojines!\l"
	.string "¡Muñecos de peluche grandes!\l"
	.string "¡Muñecos de peluche chicos!\l"
	.string "¡Quisiera tenerlos todos!$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_GetYouAnythingYouWant:
	.string "¡Déjaselo a tu mami!\p"
	.string "Si es algo que quieras, iré\n"
	.string "¡haré lo que sea por ello, cielo!$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ItemsWillGetMonTougher:
	.string "Si consigo los objetos de aquí,\n"
	.string "mis POKéMON serán más fuertes.\p"
	.string "¡Seguro que lo serán!\n"
	.string "¡No hay duda de ello!$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_GoGetYourOwnDoll:
	.string "¿Eh?\n"
	.string "¿Qué estás mirando?\p"
	.string "No me gusta que mi peluche\n"
	.string "lo mires de esa forma.\p"
	.string "¡Si lo quieres, ve a buscar uno!\n"
	.string "¿A que sí, SMOOCHUM?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_MoreBattlePointsForRecord:
	.string "¿Sabías esto?\p"
	.string "Si extiendes tu récord en cualquier\n"
	.string "las instalaciones de BATALLA,\l"
	.string "te dan cada vez más Puntos de Batalla.$"
