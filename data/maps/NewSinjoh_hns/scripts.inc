NewSinjoh_hns_MapScripts::
map_script MAP_SCRIPT_ON_TRANSITION, NewSinjoh_On_Transition
	.byte 0

NewSinjoh_On_Transition:
    setflag FLAG_VISITED_NEWSINJOH
	end

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
	.string "This world is perfect.\p"
	.string "isn't it?$"

NewSinjoh_Script_TravelMart::
	lock
	faceplayer
	message NewSinjoh_Text_TravelShopGreeting
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
	setflag FLAG_NEWSINJOH_NPC_TRADE_COMPLETED
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
	.string "Yo, how's my GALLADE doing?$"

NewSinjoh_Text_PokefanM:
	.string "A POKéMON you get in a trade\n"
	.string "grows quickly.\p"
	.string "But if you don't have the right\n"
	.string "GYM BADGE, they may disobey you.$"

NewSinjoh_EventScript_Josh::
	lock
	faceplayer
	msgbox NewSinjoh_Text_Josh, MSGBOX_DEFAULT
	closemessage
	release
	end

	NewSinjoh_Text_Josh:
	.string "We're relaxing after\n"
	.string "helping dig up that old ruin.\p"
	.string "Our pure brawn let's us\n"
	.string "move that rubble real easy!$"

NewSinjoh_EventScript_FatMan::
	lock
	faceplayer
	msgbox NewSinjoh_Text_FatMan, MSGBOX_DEFAULT
	closemessage
	release
	end

	NewSinjoh_Text_FatMan:
	.string "Ouughh...\p"
	.string "This water feels magical on my back.\p"
	.string "If you have back pain too,\n"
	.string "you should stay here with me..$"

NewSinjoh_EventScript_OldLady::
	lock
	faceplayer
	msgbox NewSinjoh_Text_OldLady, MSGBOX_DEFAULT
	closemessage
	release
	end

	NewSinjoh_Text_OldLady:
	.string "There's nothing like a nice\n"
	.string "view to invigorate\p"
	.string "this old soul.$"

NewSinjoh_EventScript_Girl1::
	lock
	faceplayer
	msgbox NewSinjoh_Text_Girl1, MSGBOX_DEFAULT
	closemessage
	release
	end

	NewSinjoh_Text_Girl1:
	.string "I'm here on vacation with\n"
	.string "my girfliend!\p"
	.string "She really like to explore\n"
	.string "old ruins, so she begged me\l"
	.string "if we could visit Sinjoh.\p"
	.string "And I just couldn't say no to her!$"

NewSinjoh_EventScript_Girl2::
	lock
	faceplayer
	msgbox NewSinjoh_Text_Girl2, MSGBOX_DEFAULT
	closemessage
	release
	end

	NewSinjoh_Text_Girl2:
	.string "I'm so happy she agreed to\n"
	.string "bring me here!\p"
	.string "We came all the way from\n"
	.string "Alola to check out Sinjoh!$"

Script_NewSinjoh_Welcome_Sign::
	lock
	faceplayer
	msgbox Text_Welcome_Sign, MSGBOX_DEFAULT
	release
	end

Text_Welcome_Sign:
	.string "New Sinjoh\n"
	.string "A town of new endings.$"

Script_NewSinjoh_HotSprings_Mailbox::
	lock
	faceplayer
	msgbox Text_HotSprings_Sign, MSGBOX_DEFAULT
	release
	end

Text_HotSprings_Sign:
	.string "A Comforting retreat\n"
	.string "in the harsh north.\p"
	.string "-Edward's Hotsprings-.$"

Script_NewSinjoh_Abandoned_House_Mailbox::
	lock
	faceplayer
	msgbox Text_Abandoned_MailBox, MSGBOX_DEFAULT
	release
	end

Text_Abandoned_MailBox:
	.string "DO NOT ENTER.\p"
	.string "This home is forclosed.$"

Script_NewSinjoh_Resturant_Sign::
	lock
	faceplayer
	msgbox Text_Resturant_Sign, MSGBOX_DEFAULT
	release
	end

Text_Resturant_Sign:
	.string "Welcome to Serana's Cafe!\n"
	.string "A cozy joint hidden in the brush.$"

Script_NewSinjoh_LockedDoor::
	lock
	faceplayer
	msgbox Text_NewSinjoh_LockedDoor, MSGBOX_DEFAULT
	release
	end

Text_NewSinjoh_LockedDoor:
	.string "This is the hotsprings'\n"
	.string "changing room...\l"
	.string"No reason to go in there!$"

Script_NewSinoh_OldLady_Gift::
	lock
	faceplayer
	goto_if_set FLAG_NEWSINJOH_HEATROCK_GOT, NewSinjoh_EventScript_HeatRock_Got
	msgbox Text_ItemGiveaway, MSGBOX_DEFAULT
	checkitem ITEM_HEAT_ROCK, 1
	compare VAR_RESULT, 1
	goto_if_ge Script_HasHeatRockAlready
	msgbox Text_GivingRock, MSGBOX_DEFAULT
	giveitem ITEM_HEAT_ROCK, 1
	compare VAR_RESULT, 0
	goto_if_eq Script_BagIsFull
	setflag FLAG_NEWSINJOH_HEATROCK_GOT
	release
	end

Script_HasHeatRockAlready::
	msgbox Text_HasHeatRockAlready, MSGBOX_DEFAULT
	release
	end

Script_BagIsFull::
	msgbox Text_BagIsFull, MSGBOX_DEFAULT
	release
	end

Text_ItemGiveaway:
	.string "Oh dear... The trip up\n"
	.string "here must have been so cold.\l"
	.string "Why don't i give you something.$"

Text_GivingRock:
	.string "Here you go deary..\n"
    .string "Take this.$"

Text_HasHeatRockAlready:
	.string "Oh you already have one?\n"
	.string "I'll hold onto this for now then..$"

Text_BagIsFull:
	.string "Your BAG is full hun.\n"
	.string "why don't you make space and come back hm?$"

NewSinjoh_EventScript_HeatRock_Got::
    msgbox Text_ItemGiveaway, MSGBOX_DEFAULT 
	msgbox Text_HasHeatRockAlready, MSGBOX_DEFAULT
	release
	end

NewSinjoh_EventScript_Hiker::
	lock
	faceplayer
	msgbox NewSinjoh_Text_Hiker, MSGBOX_DEFAULT
	closemessage
	release
	end

	NewSinjoh_Text_Hiker:
	.string "It's so cold here!\p"
	.string "I think after i finish exploring\n"
	.string "I'll go somewhere tropical!$"

Script_NewSinjoh_GroundItem_1::
	lock
	giveitem ITEM_DUSK_BALL, 1
	compare VAR_RESULT, 0
	goto_if_eq Script_Bag1sFull
	release
	end

Script_Bag1sFull::
	msgbox Text_Bag1sFull, MSGBOX_DEFAULT
	release
	end

Text_Bag1sFull:
	.string "Your BAG is full.$"