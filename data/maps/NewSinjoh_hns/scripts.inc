NewSinjoh_hns_MapScripts::
	.byte 0

NewSinjoh_MilkMan_EventScript_Seller::
	lock
	faceplayer
	checkitem ITEM_MOOMOO_MILK, 99
	compare VAR_RESULT, 1
	goto_if_eq MilkMan_EventScript_Battle
	showmoneybox 0, 0
	msgbox NewSinjoh_MilkMan_text_BuyMilk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, NewSinjoh_EventScript_MilkMan_BuyMilk
	msgbox NewSinjoh_MilkMan_NoSale, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	end

NewSinjoh_EventScript_MilkMan_BuyMilk::
	checkmoney 500, 0
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_MilkMan_NotEnough
	additem ITEM_MOOMOO_MILK
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_MilkMan_BagFull
	removemoney 500
	updatemoneybox 0
	msgbox NewSinjoh_MilkMan_Text_WouldYouLikeAnother, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, NewSinjoh_EventScript_MilkMan_BuyMilk

	
	msgbox NewSinjoh_MilkMan_GotMilk, MSGBOX_DEFAULT
	closemessage
	playse MUS_OBTAIN_ITEM
	msgbox NewSinjoh_Text_GotMilk, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end


NewSinjoh_MilkMan_BagFull::
	msgbox NewSinjoh_MilkMan_NoRoom, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

NewSinjoh_MilkMan_NotEnough::
	msgbox NewSinjoh_MilkMan_NoMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

    NewSinjoh_MilkMan_text_BuyMilk:
	.string "I am the Milkman.\p"
	.string "My milk is delicious.\p"
	.string "If you would like some today, it'll be\n"
	.string "¥500.$"

NewSinjoh_MilkMan_GotMilk:
	.string "Here ya go!\n"
	.string "It's fortified with what the world wants.$"

NewSinjoh_MilkMan_NoMoney:
	.string "Sorry.\n"
	.string "Get some cash, then you will get a sale!$"

NewSinjoh_MilkMan_NoRoom:
	.string "Look's like your PACK's full.$"

NewSinjoh_MilkMan_NoSale:
	.string "Don't you want it?\n"
	.string "It gots what the world deserves.$"

NewSinjoh_MilkMan_Text_WouldYouLikeAnother:
	.string "How bout another?$"

NewSinjoh_Text_GotMilk:
	.string "{PLAYER} got MOOMOO MILK.$"

MilkMan_EventScript_Battle:: 
msgbox MilkMan_Battle_text
Trainerbattle_no_intro TRAINER_MILKMAN_HNS, NewSinjoh_MilkMan_text_Lose
end
release


MilkMan_Battle_text:
	.string "I am the MilkMan,\p"
	.string "My milk is delicious.\p"
	.string "Special delivery today!$"

NewSinjoh_MilkMan_text_Lose:
	.string "This world is perfect,\p"
	.string "isn't it?$"

NewSinjoh_Script_TravelMart::
	lock
	faceplayer
	message Text_TravelShopGreeting
	waitmessage
	pokemart NewSinjoh_Pokemart_TravelShop
	msgbox NewSinjoh_Text_TravelShopEnd, MSGBOX_DEFAULT
	release
	end

	.align 2
NewSinjoh_Pokemart_TravelShop:
	.2byte ITEM_ENERGY_ROOT
	.2byte ITEM_REVIVAL_HERB
	.2byte ITEM_HEAL_POWDER
	.2byte ITEM_ELIXER
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_MAX_LURE
	.2byte ITEM_MAX_MUSHROOMS
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_NONE
	release
	end

NewSinjoh_Text_TravelShopGreeting:
	.string "Welcome to My little Supply Shop.\n"
	.string "How can I help you?$"

NewSinjoh_Text_TravelShopEnd:
	.string "Do come back.$"

Script_NewSinjoh_Traveler_Brother::
	lock
	faceplayer
	msgbox NewSinjoh_Text_TravelBrother_Greeting
	release
	end

NewSinjoh_Text_TravelBrother_Greeting:
    .string "All our goods are homemade\n"
	.string "and grown locally!\p"
	.string "My big Sister opened up this shop,\n"
	.string "because the PokeMart company\l"
	.string "won't open a location\l"
	.string "this far out from a major town.$"

NewSinjoh_EventScript_Kyle::
	lock
	faceplayer
	msgbox NewSinjoh_Text_PokefanM, MSGBOX_DEFAULT
	closemessage
	release
	end

NewSinjoh_EventScript_Jessica::
	lock
	faceplayer
	goto_if_set FLAG_NEWSINJOH_NPC_TRADE_COMPLETED, NewSinjoh_EventScript_TradeCompleted
	setvar VAR_0x8008, INGAME_TRADE_GALLADE
	copyvar VAR_0x8004, VAR_0x8008
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
	copyvar VAR_0x8009, VAR_RESULT
	msgbox NewSinjoh_Text_YouWillTradeWontYou, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, NewSinjoh_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x800A, VAR_0x8004
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, NewSinjoh_EventScript_DeclineTrade
	copyvar VAR_0x8005, VAR_0x800A
	specialvar VAR_RESULT, GetTradeSpecies
	copyvar VAR_0x800B, VAR_RESULT
	goto_if_ne VAR_RESULT, VAR_0x8009, NewSinjoh_EventScript_NotRequestedMon
	copyvar VAR_0x8004, VAR_0x8008
	copyvar VAR_0x8005, VAR_0x800A
	special CreateInGameTradePokemon
	special DoInGameTradeScene
	waitstate
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox NewSinjoh_Text_MonYouTakeCare, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_NewSinjoh_NPC_TRADE_COMPLETED
	release
	end

NewSinjoh_EventScript_DeclineTrade::
	msgbox NewSinjoh_Text_YouWontTradeMe, MSGBOX_DEFAULT
	release
	end

NewSinjoh_EventScript_NotRequestedMon::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox NewSinjoh_Text_ThisIsntAMon, MSGBOX_DEFAULT
	release
	end

NewSinjoh_EventScript_TradeCompleted::
	msgbox NewSinjoh_Text_After, MSGBOX_DEFAULT
	release
	end

NewSinjoh_Text_YouWillTradeWontYou:
	.string "I collect POKéMON!\n"
	.string "Do you have a {STR_VAR_1}?\p"
	.string "Want to trade it for my\n"
	.string "{STR_VAR_2}?$"

NewSinjoh_Text_MonYouTakeCare:
	.string "Yay! I got myself {STR_VAR_1}!\p"
	.string "{STR_VAR_2}, you take care!$"

NewSinjoh_Text_ThisIsntAMon:
	.string "Uh, no, I don't think so.\n"
	.string "That isn't a {STR_VAR_1}.$"

NewSinjoh_Text_YouWontTradeMe:
	.string "You don't want to trade? Aww...$"

NewSinjoh_Text_After:
	.string "Hi, how's my old ONIX doing?$"

NewSinjoh_Text_PokefanM:
	.string "A POKéMON you get in a trade\n"
	.string "grows quickly.\p"
	.string "But if you don't have the right\n"
	.string "GYM BADGE, they may disobey you.$"
