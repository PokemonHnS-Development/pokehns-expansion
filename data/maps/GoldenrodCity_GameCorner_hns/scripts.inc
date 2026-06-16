GoldenrodCity_GameCorner_hns_MapScripts::
	.byte 0

GoldenrodCity_GameCorner_PrizeRoom_EventScript_PrizeClerkMons::
	lock
	faceplayer
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, MauvilleCity_GameCorner_EventScript_NeedCoinCase
	msgbox MauvilleCity_GameCorner_Text_ExchangeCoinsForPrizes, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChoosePrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChoosePrizeMon::
	@callnative DisableStaticRandomizer
	showcoinsbox 1, 1
	message MauvilleCity_GameCorner_Text_WhichPrize
	waitmessage
	multichoice 20, 0, MULTI_PRIZE_MONS, FALSE
	switch VAR_RESULT
	case 0, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Abra
	case 1, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Clefairy
	case 2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Munchlax
	case 3, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Dratini
	case 4, GoldenrodCity_GameCorner_PrizeRoom_EventScript_Porygon
	case 5, GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	case 127, GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange::
	hidecoinsbox 0, 0
	@callnative EnableStaticRandomizer
	closemessage
	release
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_Abra::
	setvar VAR_TEMP_1, SPECIES_ABRA
	setvar VAR_TEMP_2, 120
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_Clefairy::
	setvar VAR_TEMP_1, SPECIES_CLEFAIRY
	setvar VAR_TEMP_2, 500
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_Munchlax::
	setvar VAR_TEMP_1, SPECIES_MUNCHLAX
	setvar VAR_TEMP_2, 2800
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_Dratini::
	setvar VAR_TEMP_1, SPECIES_DRATINI
	setvar VAR_TEMP_2, 5500
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_Porygon::
	setvar VAR_TEMP_1, SPECIES_PORYGON
	setvar VAR_TEMP_2, 6500
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon::
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	msgbox GoldenrodCity_GameCorner_PrizeRoom_Text_YouWantPrize, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	checkcoins VAR_RESULT
	goto_if_lt VAR_RESULT, VAR_TEMP_2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoins
	switch VAR_TEMP_1
	updatecoinsbox 1, 1
	playse SE_SHOP
	case SPECIES_ABRA,     GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveAbra
	case SPECIES_CLEFAIRY, GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveClefairy
	case SPECIES_DRATINI,  GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveDratini
	case SPECIES_MUNCHLAX,  GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveMunchlax
	case SPECIES_PORYGON,  GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePorygon
	case SPECIES_PINSIR,   GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePinsir
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveAbra::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveClefairy::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveDratini::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GiveMunchlax::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePorygon::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_GivePinsir::
	givemon VAR_TEMP_1, 15
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon::
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonParty
	goto_if_eq VAR_RESULT, 1, GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonPC
	goto_if_eq VAR_RESULT, 2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_PartyFull
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_PartyFull::
	msgbox Route119_WeatherInstitute_2F_Text_NoRoomForPokemon
	hidecoinsbox 0, 0
	@callnative EnableStaticRandomizer
	closemessage
	release
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_NicknamePartyMon::
	getpartysize
	subvar VAR_RESULT, 1
	copyvar VAR_0x8004, VAR_RESULT
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonParty_Nickname_Nuzlocke::
	message GoldenrodGamecorner_Text_GiveNicknameToThisMon
	getpartysize
	subvar VAR_RESULT, 1
	copyvar VAR_0x8004, VAR_RESULT
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_NeedCoinCase::
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorNoCoinCase
	release
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoins::
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorNeedMoreCoins
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonParty::
	removecoins VAR_TEMP_2
	playse SE_SHOP
	updatecoinsbox 1, 1
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	playfanfare MUS_LEVEL_UP
	message GoldenrodCity_GameCorner_Text_PlayerObtainedTheMon
	waitmessage
	waitfanfare
	specialvar VAR_RESULT, IsNuzlockeNicknamingActive
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonParty_Nickname_Nuzlocke
	msgbox GoldenrodGamecorner_Text_GiveNicknameToThisMon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NicknamePartyMon
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReceivedMonPC::
	removecoins VAR_TEMP_2
	playse SE_SHOP
	updatecoinsbox 1, 1
	bufferspeciesname STR_VAR_1, VAR_TEMP_1
	playfanfare MUS_LEVEL_UP
	message GoldenrodCity_GameCorner_Text_PlayerObtainedTheMon
	waitmessage
	waitfanfare
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_TransferredToPC
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_TransferredToPC::
	call Common_EventScript_TransferredToPC
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_PartyMon::
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	end
	
GoldenrodCity_GameCorner_PrizeRoom_EventScript_PcMon::
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_GameCorner_EventScript_SendMon
	call Common_EventScript_NameReceivedBoxMon
	goto GoldenrodCity_GameCorner_EventScript_SendMon
	closemessage
	hidecoinsbox 0, 0
	@callnative EnableStaticRandomizer
	release
	end

GoldenrodCity_GameCorner_EventScript_SendMon::
	call Common_EventScript_TransferredToPC
	closemessage
	hidecoinsbox 0, 0
	@callnative EnableStaticRandomizer
	release
	end

	.set TM_ICE_BEAM_COINS, 4000
	.set TM_FLAMETHROWER_COINS, 4000
	.set TM_REST_COINS, 2000
	.set TM_SWORDS_DANCE_COINS, 3000
	.set TM_SUBSTITUTE_COINS, 2000

GoldenrodCity_GameCorner_PrizeRoom_EventScript_PrizeClerkTMs::
	lock
	faceplayer
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NeedCoinCase
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorIntro, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChooseTMPrizeMessage
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChooseTMPrizeMessage::
	message GoldenrodCity_GameCorner_Text_PrizeVendorWhichPrize
	waitmessage
	setvar VAR_TEMP_1, 0
	showcoinsbox 1, 1
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChooseTMPrize

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize::
	message GoldenrodCity_GameCorner_Text_PrizeVendorWhichPrize
	waitmessage
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChooseTMPrize

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ChooseTMPrize::
	dynmultichoice 12, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, GoldenrodCity_GameCorner_PrizeRoom_Text_TM13, GoldenrodCity_GameCorner_PrizeRoom_Text_TM35, GoldenrodCity_GameCorner_PrizeRoom_Text_TM44, GoldenrodCity_GameCorner_PrizeRoom_Text_TM75, GoldenrodCity_GameCorner_PrizeRoom_Text_TM90, GoldenrodCity_GameCorner_PrizeRoom_Text_Cancel
	switch VAR_RESULT
	case 0, GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMIceBeam
	case 1, GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMFlamethrower
	case 2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMRest
	case 3, GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMSwordsDance
	case 4, GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMSubstitute
	case 5, GoldenrodCity_GameCorner_PrizeRoom_EventScript_CancelTMSelect
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_CancelTMSelect
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMIceBeam::
	setvar VAR_TEMP_1, 1
	bufferitemname STR_VAR_1, ITEM_TM_ICE_BEAM
	setvar VAR_0x8004, ITEM_TM_ICE_BEAM
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrize

GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMFlamethrower::
	setvar VAR_TEMP_1, 2
	bufferitemname STR_VAR_1, ITEM_TM_FLAMETHROWER
	setvar VAR_0x8004, ITEM_TM_FLAMETHROWER
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrize

GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMRest::
	setvar VAR_TEMP_1, 3
	bufferitemname STR_VAR_1, ITEM_TM_REST
	setvar VAR_0x8004, ITEM_TM_REST
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrize

GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMSwordsDance::
	setvar VAR_TEMP_1, 4
	bufferitemname STR_VAR_1, ITEM_TM75
	setvar VAR_0x8004, ITEM_TM75
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrize

GoldenrodCity_GameCorner_PrizeRoom_EventScript_TMSubstitute::
	setvar VAR_TEMP_1, 5
	bufferitemname STR_VAR_1, ITEM_TM90
	setvar VAR_0x8004, ITEM_TM90
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrize

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrize::
	special BufferTMHMMoveName
	msgbox GoldenrodCity_GameCorner_PrizeRoom_Text_SoYourChoiceIsTM, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, GoldenrodCity_GameCorner_PrizeRoom_EventScript_CancelTMSelect
	goto_if_unset FLAG_FINITE_TMS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrizeInfinite
	switch VAR_TEMP_1
	case 1, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMIceBeam
	case 2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMFlamethrower
	case 3, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMRest
	case 4, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMSwordsDance
	case 5, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMSubstitute
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_ConfirmTMPrizeInfinite::
	switch VAR_TEMP_1
	case 1, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMIceBeamInfinite
	case 2, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMFlamethrowerInfinite
	case 3, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMRestInfinite
	case 4, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMSwordsDanceInfinite
	case 5, GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMSubstituteInfinite
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMIceBeamInfinite::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_ICE_BEAM_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitem ITEM_TM_ICE_BEAM, 1
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_YouAlreadyHaveThis
	removecoins TM_ICE_BEAM_COINS
	additem ITEM_TM_ICE_BEAM
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMFlamethrowerInfinite::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_FLAMETHROWER_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitem ITEM_TM_FLAMETHROWER, 1
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_YouAlreadyHaveThis
	removecoins TM_FLAMETHROWER_COINS
	additem ITEM_TM_FLAMETHROWER
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMRestInfinite::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_REST_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitem ITEM_TM_REST, 1
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_YouAlreadyHaveThis
	removecoins TM_REST_COINS
	additem ITEM_TM_REST
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMSwordsDanceInfinite::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_SWORDS_DANCE_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitem ITEM_TM75, 1
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_YouAlreadyHaveThis
	removecoins TM_SWORDS_DANCE_COINS
	additem ITEM_TM75
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMSubstituteInfinite::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_SUBSTITUTE_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitem ITEM_TM90, 1
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_YouAlreadyHaveThis
	removecoins TM_SUBSTITUTE_COINS
	additem ITEM_TM90
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMIceBeam::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_ICE_BEAM_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_ICE_BEAM
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NoRoomForTM
	removecoins TM_ICE_BEAM_COINS
	additem ITEM_TM_ICE_BEAM
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMFlamethrower::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_FLAMETHROWER_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_FLAMETHROWER
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NoRoomForTM
	removecoins TM_FLAMETHROWER_COINS
	additem ITEM_TM_FLAMETHROWER
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMRest::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_REST_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM_REST
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NoRoomForTM
	removecoins TM_REST_COINS
	additem ITEM_TM_REST
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMSwordsDance::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_SWORDS_DANCE_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM75
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NoRoomForTM
	removecoins TM_SWORDS_DANCE_COINS
	additem ITEM_TM75
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_BuyTMSubstitute::
	checkcoins VAR_TEMP_2
	goto_if_lt VAR_TEMP_2, TM_SUBSTITUTE_COINS, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM
	checkitemspace ITEM_TM90
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_PrizeRoom_EventScript_NoRoomForTM
	removecoins TM_SUBSTITUTE_COINS
	additem ITEM_TM90
	updatecoinsbox 1, 1
	playse SE_SHOP
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoinsForTM::
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorNeedMoreCoins, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_NoRoomForTM::
	call Common_EventScript_BagIsFull
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_YouAlreadyHaveThis::
	msgbox GoldenrodCity_GameCorner_PrizeRoom_Text_YouAlreadyHaveThis, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_PrizeRoom_EventScript_ReturnToChooseTMPrize
	end

GoldenrodCity_GameCorner_PrizeRoom_EventScript_CancelTMSelect::
	msgbox GoldenrodCity_GameCorner_Text_PrizeVendorQuit, MSGBOX_DEFAULT
	hidecoinsbox 0, 0
	release
	end

GoldenrodCity_GameCorner_PrizeRoom_Text_TM13:
	.string "Ice Beam   4000$"

GoldenrodCity_GameCorner_PrizeRoom_Text_TM35:
	.string "Flamethrower 4000$"

GoldenrodCity_GameCorner_PrizeRoom_Text_TM44:
	.string "Rest       2000$"

GoldenrodCity_GameCorner_PrizeRoom_Text_TM75:
	.string "Swords Dance 3000$"

GoldenrodCity_GameCorner_PrizeRoom_Text_TM90:
	.string "Substitute 2000$"

GoldenrodCity_GameCorner_PrizeRoom_Text_Cancel:
	.string "Cancel$"

GoldenrodCity_GameCorner_PrizeRoom_Text_SoYourChoiceIsTM:
	.string "So your choice is\n"
	.string "the {STR_VAR_1} {STR_VAR_2}?$"

GoldenrodCity_GameCorner_PrizeRoom_Text_YouAlreadyHaveThis:
	.string "You already have that item.$"

GoldenrodCity_GameCorner_EventScript_PokefanM::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_PokefanM1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_EventScript_Hiker::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_MoveTutorInside, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_EventScript_Woman::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_Woman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_EventScript_Gentleman::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_Gentleman, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_EventScript_PokefanF::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_PokefanF, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_EventScript_PokefanM2::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_PokefanM2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_EventScript_CooltrainerM::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_EventScript_Pharmacist::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_Pharmacist, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_GameCorner_PrizeRoom_Text_YouWantPrize:
	.string "{STR_VAR_1} is what you want?$"

GoldenrodCity_GameCorner_Text_PlayerObtainedTheMon:
	.string "{PLAYER} got {STR_VAR_1}!$"

GoldenrodGamecorner_Text_GiveNicknameToThisMon:
	.string "Nickname {STR_VAR_1}?$"

GoldenrodCity_GameCorner_Text_PrizeVendorIntro:
    .string "Welcome!\p"
    .string "We exchange your game coins for\n"
    .string "fabulous prizes!$"

GoldenrodCity_GameCorner_Text_PrizeVendorWhichPrize:
    .string "Which prize would you like?$"

GoldenrodCity_GameCorner_Text_PrizeVendorHereYouGo:
    .string "Here you go!$"

GoldenrodCity_GameCorner_Text_PrizeVendorNeedMoreCoins:
    .string "Sorry! You need more coins.$"

GoldenrodCity_GameCorner_Text_PrizeVendorNoMoreRoom:
    .string "Sorry. You can't carry any more.$"

GoldenrodCity_GameCorner_Text_PrizeVendorQuit:
    .string "OK. Please save your coins and come\n"
    .string "again!$"

GoldenrodCity_GameCorner_Text_PrizeVendorNoCoinCase:
    .string "Oh? You don't have a COIN CASE.$"

GoldenrodCity_GameCorner_Text_Pharmacist:
    .string "I always play this slot machine.\n"
    .string "It pays out more than others,\l"
    .string "I think.$"

GoldenrodCity_GameCorner_Text_Woman:
    .string "I can't stop winning!$"

GoldenrodCity_GameCorner_Text_PokefanM1:
    .string "I just love this new slot machine.\p"
    .string "It's more of a challenge than the\n"
    .string "ones in CELADON.$"

GoldenrodCity_GameCorner_Text_CooltrainerM:
    .string "Life is a gamble. I'm going to pull\n"
    .string "till I drop!$"

GoldenrodCity_GameCorner_Text_PokefanF:
    .string "Roulette…\p"
    .string "I prefer it over the slots because\n"
    .string "it's easier to figure the odds.\p"
    .string "But the payout is much lower.$"

GoldenrodCity_GameCorner_Text_CooltrainerF:
    .string "I won't quit until I win!$"

GoldenrodCity_GameCorner_Text_Gentleman:
    .string "I taught ICE BEAM to my POKéMON.\p"
    .string "It was hard to get enough coins for\n"
    .string "it, but it was worth it.$"

GoldenrodCity_GameCorner_Text_PokefanM2:
    .string "I couldn't win at the slots, and I\n"
    .string "blew it on roulette.\p"
    .string "I got so furious, I tossed out my\n"
    .string "COIN CASE in the UNDERGROUND.$"

GoldenrodCity_GameCorner_Text_MoveTutorInside:
    .string "Wahahah! The coins keep rolling in!$"

GoldenrodCity_GameCorner_Text_LeftTheirDrink:
    .string "Someone left their drink.\p"
    .string "It smells sweet.$"

@ ========================================
@ VOLTORB FLIP GAME IMPLEMENTATION
@ ========================================

GoldenrodCity_GameCorner_EventScript_VoltorbFlip::
	lockall
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, GoldenrodCity_GameCorner_EventScript_VF_NoCoinCase
	message GoldenrodCity_GameCorner_Text_VF_Welcome
	waitmessage
	playbgm MUS_RG_OAK, FALSE
	setvar VAR_TEMP_4, 0

GoldenrodCity_GameCorner_EventScript_VF_CheckCoinCap::
	checkcoins VAR_RESULT
	goto_if_lt VAR_RESULT, MAX_COINS, GoldenrodCity_GameCorner_EventScript_VF_ShowMenu
	msgbox GoldenrodCity_GameCorner_Text_VF_CoinCap, MSGBOX_DEFAULT
	setvar VAR_TEMP_4, 0
	setvar VAR_TEMP_7, 0
	hidecoinsbox 0, 5
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

GoldenrodCity_GameCorner_EventScript_VF_ShowMenu::
	showcoinsbox 1, 1
	copyvar VAR_TEMP_A, VAR_TEMP_4
	addvar VAR_TEMP_A, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_A
	message GoldenrodCity_GameCorner_Text_VF_PlayLevel
	waitmessage
	dynmultichoice 19, 6, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, GoldenrodCity_GameCorner_Text_VF_OptPlay, GoldenrodCity_GameCorner_Text_VF_OptGameInfo, GoldenrodCity_GameCorner_Text_VF_OptQuit
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_GameCorner_EventScript_VF_Play
	goto_if_eq VAR_RESULT, 1, GoldenrodCity_GameCorner_EventScript_VF_GameInfo
	@ Quit or B-press
	setvar VAR_TEMP_4, 0
	setvar VAR_TEMP_7, 0
	closemessage
	hidecoinsbox 0, 5
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

GoldenrodCity_GameCorner_EventScript_VF_GameInfo::
	message GoldenrodCity_GameCorner_Text_VF_WhichInfo
	waitmessage
	dynmultichoice 19, 4, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, GoldenrodCity_GameCorner_Text_VF_OptHowToPlay, GoldenrodCity_GameCorner_Text_VF_OptHint, GoldenrodCity_GameCorner_Text_VF_OptAboutNotes, GoldenrodCity_GameCorner_Text_VF_OptReturn
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_GameCorner_EventScript_VF_HowToPlay
	goto_if_eq VAR_RESULT, 1, GoldenrodCity_GameCorner_EventScript_VF_Hint
	goto_if_eq VAR_RESULT, 2, GoldenrodCity_GameCorner_EventScript_VF_AboutNotes
	goto GoldenrodCity_GameCorner_EventScript_VF_ShowMenu

GoldenrodCity_GameCorner_EventScript_VF_HowToPlay::
	msgbox GoldenrodCity_GameCorner_Text_VF_HowToPlay, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_GameInfo

GoldenrodCity_GameCorner_EventScript_VF_Hint::
	msgbox GoldenrodCity_GameCorner_Text_VF_HintText, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_GameInfo

GoldenrodCity_GameCorner_EventScript_VF_AboutNotes::
	msgbox GoldenrodCity_GameCorner_Text_VF_AboutNotes, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_GameInfo

GoldenrodCity_GameCorner_EventScript_VF_Play::
	closemessage
	copyvar VAR_TEMP_6, VAR_TEMP_4
	setvar VAR_TEMP_5, 0
	hidecoinsbox 0, 5
	special Special_ViewVoltorbFlip
	waitstate
	goto_if_eq VAR_RESULT, 0, GoldenrodCity_GameCorner_EventScript_VF_HandleLoss
	goto_if_eq VAR_RESULT, 1, GoldenrodCity_GameCorner_EventScript_VF_HandleWin
	goto GoldenrodCity_GameCorner_EventScript_VF_HandleQuit
	end

GoldenrodCity_GameCorner_EventScript_VF_HandleWin::
	msgbox GoldenrodCity_GameCorner_Text_VF_GameClear, MSGBOX_DEFAULT
	copyvar VAR_TEMP_1, VAR_TEMP_5
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_1
	msgbox GoldenrodCity_GameCorner_Text_VF_ReceivedCoins, MSGBOX_DEFAULT
	addcoins VAR_TEMP_5
	setvar VAR_TEMP_5, 0
	updatecoinsbox 1, 1
	goto_if_le VAR_TEMP_4, VAR_TEMP_6, GoldenrodCity_GameCorner_EventScript_VF_CheckCoinCap
	copyvar VAR_TEMP_A, VAR_TEMP_4
	addvar VAR_TEMP_A, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_A
	msgbox GoldenrodCity_GameCorner_Text_VF_Advanced, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_CheckCoinCap

GoldenrodCity_GameCorner_EventScript_VF_HandleLoss::
	msgbox GoldenrodCity_GameCorner_Text_VF_OhNo, MSGBOX_DEFAULT
	goto_if_ge VAR_TEMP_4, VAR_TEMP_6, GoldenrodCity_GameCorner_EventScript_VF_ShowMenu
	copyvar VAR_TEMP_A, VAR_TEMP_4
	addvar VAR_TEMP_A, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_A
	msgbox GoldenrodCity_GameCorner_Text_VF_Dropped, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_ShowMenu

GoldenrodCity_GameCorner_EventScript_VF_HandleQuit::
	goto_if_eq VAR_TEMP_5, 0, GoldenrodCity_GameCorner_EventScript_VF_QuitNoCoins
	copyvar VAR_TEMP_1, VAR_TEMP_5
	showcoinsbox 1, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_1
	msgbox GoldenrodCity_GameCorner_Text_VF_ReceivedCoins, MSGBOX_DEFAULT
	addcoins VAR_TEMP_5
	setvar VAR_TEMP_5, 0
	updatecoinsbox 1, 1

GoldenrodCity_GameCorner_EventScript_VF_QuitNoCoins::
	goto_if_ge VAR_TEMP_4, VAR_TEMP_6, GoldenrodCity_GameCorner_EventScript_VF_CheckCoinCap
	copyvar VAR_TEMP_A, VAR_TEMP_4
	addvar VAR_TEMP_A, 1
	buffernumberstring STR_VAR_1, VAR_TEMP_A
	msgbox GoldenrodCity_GameCorner_Text_VF_Dropped, MSGBOX_DEFAULT
	goto GoldenrodCity_GameCorner_EventScript_VF_CheckCoinCap

GoldenrodCity_GameCorner_EventScript_VF_NoCoinCase::
	msgbox GoldenrodCity_GameCorner_Text_VF_NeedCoinCase, MSGBOX_DEFAULT
	releaseall
	end

GoldenrodCity_GameCorner_EventScript_VFAttendant1::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_VFAttendant1, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceDown
	waitmovement 0
	release
	end

GoldenrodCity_GameCorner_EventScript_VFAttendant2::
	lock
	faceplayer
	msgbox GoldenrodCity_GameCorner_Text_VFAttendant2, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceDown
	waitmovement 0
	release
	end

@ Voltorb Flip Menu Option Strings
GoldenrodCity_GameCorner_Text_VF_OptPlay:
	.string "PLAY$"

GoldenrodCity_GameCorner_Text_VF_OptGameInfo:
	.string "GAME INFO$"

GoldenrodCity_GameCorner_Text_VF_OptQuit:
	.string "QUIT$"

GoldenrodCity_GameCorner_Text_VF_OptHowToPlay:
	.string "HOW TO PLAY$"

GoldenrodCity_GameCorner_Text_VF_OptHint:
	.string "HINT$"

GoldenrodCity_GameCorner_Text_VF_OptAboutNotes:
	.string "ABOUT NOTES$"

GoldenrodCity_GameCorner_Text_VF_OptReturn:
	.string "RETURN$"

@ Voltorb Flip Dialogue Strings
GoldenrodCity_GameCorner_Text_VF_Welcome:
	.string "Welcome to VOLTORB FLIP!\p$"

GoldenrodCity_GameCorner_Text_VF_PlayLevel:
	.string "Play VOLTORB Flip Lv. {STR_VAR_1}?$"

GoldenrodCity_GameCorner_Text_VF_GameClear:
	.string "Game clear!\p"
	.string "You've found all the hidden\n"
	.string "x2 and x3 cards!$"

GoldenrodCity_GameCorner_Text_VF_ReceivedCoins:
	.string "You have received\n"
	.string "{STR_VAR_1} Coin(s)!$"

GoldenrodCity_GameCorner_Text_VF_Advanced:
	.string "Advanced to Game Lv. {STR_VAR_1}!$"

GoldenrodCity_GameCorner_Text_VF_OhNo:
	.string "Oh no! You get 0 Coins!$"

GoldenrodCity_GameCorner_Text_VF_Dropped:
	.string "Dropped to Game Lv. {STR_VAR_1}.$"

GoldenrodCity_GameCorner_Text_VF_CoinCap:
	.string "You've gathered 9,999 COINS.\n"
	.string "You cannot gather any more.$"

GoldenrodCity_GameCorner_Text_VF_WhichInfo:
	.string "Which set of info?$"

GoldenrodCity_GameCorner_Text_VF_HowToPlay:
	.string "VOLTORB FLIP is a game in which you flip\n"
	.string "cards to find numbers hidden beneath.\p"
	.string "The cards hide the numbers 1 through 3,\n"
	.string "and VOLTORB as well.\p"
	.string "The first number you flip gives\n"
	.string "you that many Coins.\p"
	.string "Each new number multiplies your total.\n"
	.string "A 2 by x2 and a 3 by x3.\p"
	.string "But if you flip a VOLTORB, it's game over.\n"
	.string "You lose all Coins collected that round!\p"
	.string "QUIT the game at any time to keep\n"
	.string "the Coins you've found so far.\p"
	.string "Find all hidden x2 and x3 cards to clear\n"
	.string "the game and advance to the next level!$"

GoldenrodCity_GameCorner_Text_VF_HintText:
	.string "The numbers on the sides of the board\n"
	.string "are hints about the numbers…\p"
	.string "hidden in that row or column.\p"
	.string "The larger the number, the more high-\n"
	.string "value cards are in that row or column.\p"
	.string "The VOLTORB count tells you how\n"
	.string "many VOLTORBs lurk there.\p"
	.string "Use both totals to figure out\n"
	.string "which cards are safe to flip!$"

GoldenrodCity_GameCorner_Text_VF_AboutNotes:
	.string "Use the notes mode ({L_BUTTON} & {R_BUTTON}) to mark\n"
	.string "cards with numbers 1-3 or a VOLTORB.\p"
	.string "Mark a card you think you know,\n"
	.string "then flip it when you're sure.\p"
	.string "Apply a note again to remove it.$"

GoldenrodCity_GameCorner_Text_VF_NeedCoinCase:
	.string "Oh? You don't have a COIN CASE.$"

GoldenrodCity_GameCorner_Text_VFAttendant1:
	.string "You want to play VOLTORB FLIP?\p"
	.string "You need to be on the other\n"
	.string "side of the table.$"

GoldenrodCity_GameCorner_Text_VFAttendant2:
	.string "Try the other side of\n"
	.string "the table, pal.$"
