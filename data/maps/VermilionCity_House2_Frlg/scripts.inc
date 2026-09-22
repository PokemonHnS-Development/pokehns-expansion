VermilionCity_House2_Frlg_MapScripts::
	.byte 0

VermilionCity_House2_EventScript_Elyssa::
	lock
	faceplayer
	setvar VAR_0x8008, INGAME_TRADE_FARFETCHD
	call EventScript_GetInGameTradeSpeciesInfo
	goto_if_set FLAG_DID_CH_DING_TRADE, VermilionCity_House2_EventScript_AlreadyTraded
	msgbox VermilionCity_House2_Text_DoYouHaveMonWantToTradeForMyMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VermilionCity_House2_EventScript_DeclineTrade
	call EventScript_ChooseMonForInGameTrade
	goto_if_ge VAR_0x8004, PARTY_SIZE, VermilionCity_House2_EventScript_DeclineTrade
	call EventScript_GetInGameTradeSpecies
	goto_if_ne VAR_RESULT, VAR_0x8009, VermilionCity_House2_EventScript_NotRequestedMon
	call EventScript_DoInGameTrade
	msgbox VermilionCity_House2_Text_ThankYou
	setflag FLAG_DID_CH_DING_TRADE
	release
	end

VermilionCity_House2_EventScript_DeclineTrade::
	msgbox VermilionCity_House2_Text_ThatsTooBad
	release
	end

VermilionCity_House2_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox VermilionCity_House2_Text_ThisIsNoMon
	release
	end

VermilionCity_House2_EventScript_AlreadyTraded::
	msgbox VermilionCity_House2_Text_HowIsMyOldMon
	release
	end

VermilionCity_House2_Text_DoYouHaveMonWantToTradeForMyMon::
	.string "Hi!\n"
	.string "¿Tienes un {STR_VAR_1}?\p"
	.string "¿Quieres cambiarlo por mi\n"
	.string "{STR_VAR_2}?$"

VermilionCity_House2_Text_ThatsTooBad::
	.string "Qué mal.$"

VermilionCity_House2_Text_ThisIsNoMon::
	.string "...Esto no es un {STR_VAR_1}.\p"
	.string "Si consigues uno, cámbialo\n"
	.string "¡a mí!$"

VermilionCity_House2_Text_ThankYou::
	.string "¡Gracias!$"

VermilionCity_House2_Text_HowIsMyOldMon::
	.string "¿Cómo está mi viejo {STR_VAR_2}?\p"
	.string "¡Mi {STR_VAR_1} está genial!$"
