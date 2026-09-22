MauvilleCity_House2_MapScripts::
	.byte 0

MauvilleCity_House2_EventScript_Woman::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_COIN_CASE, MauvilleCity_House2_EventScript_ReceivedCoinCase
	msgbox MauvilleCity_House2_Text_BuyHarborMailAtSlateport, MSGBOX_DEFAULT
	checkitem ITEM_HARBOR_MAIL
	goto_if_eq VAR_RESULT, TRUE, MauvilleCity_House2_EventScript_AskToTradeForHarborMail
	release
	end

MauvilleCity_House2_EventScript_AskToTradeForHarborMail::
	playse SE_PIN
	applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_LAST_TALKED, Common_Movement_Delay48
	waitmovement 0
	msgbox MauvilleCity_House2_Text_TradeHarborMailForCoinCase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, MauvilleCity_House2_EventScript_AcceptTrade
	goto_if_eq VAR_RESULT, NO, MauvilleCity_House2_EventScript_DeclineTrade
	end

MauvilleCity_House2_EventScript_AcceptTrade::
	msgbox MauvilleCity_House2_Text_IllTradeYouCoinCase, MSGBOX_DEFAULT
	giveitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	removeitem ITEM_HARBOR_MAIL
	setflag FLAG_RECEIVED_COIN_CASE
	goto MauvilleCity_House2_EventScript_ReceivedCoinCase
	end

MauvilleCity_House2_EventScript_ReceivedCoinCase::
	msgbox MauvilleCity_House2_Text_UseCoinCaseAtGameCorner, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_EventScript_DeclineTrade::
	msgbox MauvilleCity_House2_Text_ThatsDisappointing, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House2_Text_BuyHarborMailAtSlateport:
	.string "Si tuviera una BICI, sería fácil ir\n"
	.string "a PORTALUANA de compras.\p"
	.string "Podría comprar CORREO DEL PUERTO en\n"
	.string "la TIENDA POKéMON de PORTALUANA...$"

MauvilleCity_House2_Text_TradeHarborMailForCoinCase:
	.string "¡Oh! ¿Tienes CORREO DEL PUERTO?\n"
	.string "¿Lo cambias por un ESTUCHE MONEDAS?$"

MauvilleCity_House2_Text_IllTradeYouCoinCase:
	.string "¡Oh, estoy muy feliz!\n"
	.string "¡Vale, te daré un ESTUCHE MONEDAS!$"

MauvilleCity_House2_Text_UseCoinCaseAtGameCorner:
	.string "Ese ESTUCHE MONEDAS se usa\n"
	.string "en el CASINO.$"

MauvilleCity_House2_Text_ThatsDisappointing:
	.string "Oh, qué decepción.\p"
	.string "Se necesita un ESTUCHE MONEDAS para\n"
	.string "CASINO POKéMON.$"

