NewSinjoh_hns_MapScripts::
map_script MAP_SCRIPT_ON_TRANSITION, NewSinjoh_On_Transition
	.byte 0

NewSinjoh_On_Transition:
    setflag FLAG_VISITED_NEWSINJOH
	end

NewSinjoh_EventScript_PetStantler::
    lock
	faceplayer
	playmoncry SPECIES_STANTLER, 0
	msgbox NewSinjoh_Text_Stantler_Cry, MSGBOX_DEFAULT
	waitmoncry
    closemessage
	release
	end

NewSinjoh_Text_Stantler_Cry:
    .string "Lerrrrr!$"

NewSinjoh_MilkMan_EventScript_Seller::
	lock
	faceplayer
	checkitem ITEM_MOOMOO_MILK, 99
	goto_if_eq VAR_RESULT, 1, MilkMan_EventScript_Battle
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
    release
    end

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

NewSinjoh_EventScript_Josh::
	msgbox NewSinjoh_Text_Josh, MSGBOX_NPC
	end

NewSinjoh_Text_Josh:
	.string "This place is sick!\p"
	.string "Hiding these hot springs\n"
	.string "from the world is a travesty.\p"
	.string "I'm gonna tell all my friends!$"

NewSinjoh_EventScript_Janice::
	msgbox NewSinjoh_Text_Janice, MSGBOX_NPC
	end

NewSinjoh_Text_Janice:
	.string "These springs are magical,\n"
	.string "but I feel like the locals\l"
	.string "are giving us dirty looks.$"

NewSinjoh_EventScript_CreepyMan::
	msgbox NewSinjoh_Text_CreepyMan, MSGBOX_NPC
	end

NewSinjoh_Text_CreepyMan:
	.string "Ouughh...\p"
	.string "This water feels magical on my back.\p"
	.string "If you have back pain too,\n"
	.string "you should stay here with me..$"

NewSinjoh_EventScript_OldLady1::
	msgbox NewSinjoh_Text_OldLady1, MSGBOX_NPC
	end

NewSinjoh_Text_OldLady1:
	.string "There's nothing like a nice\n"
	.string "view to invigorate\l"
	.string "this old soul.$"

NewSinjoh_EventScript_OldLady2::
	msgbox NewSinjoh_Text_OldLady2, MSGBOX_NPC
	end

NewSinjoh_Text_OldLady2:
	.string "Great, now these tourists\n"
	.string "are hogging our hot springs!\p"
	.string "It's been one bad thing after\n"
	.string "another lately!$"

NewSinjoh_EventScript_OldLady3::
	msgbox NewSinjoh_Text_OldLady3, MSGBOX_NPC
	end

NewSinjoh_Text_OldLady3:
	.string "How can that woman\n"
	.string "be so rude to our guests?\p"
	.string "She needs to take a dip\n"
	.string "in the springs.$"


NewSinjoh_EventScript_SpringsSage::
	msgbox NewSinjoh_Text_SpringsSage, MSGBOX_NPC
	end

NewSinjoh_Text_SpringsSage:
	.string "There has been much division\n"
	.string "and strife in our community\l"
	.string "since the newcomers arrived.\p"
	.string "Regardless of your perspective,\n"
	.string "it is clear that the balance has\l"
	.string "been disturbed.\p"
	.string "Please be kind to locals and\n"
	.string "tourists alike.$"

NewSinjoh_EventScript_Sage2::
	msgbox NewSinjoh_Text_Sage2, MSGBOX_NPC
	end

NewSinjoh_Text_Sage2:
	.string "Times change, but the stantler\n"
	.string "still gather. For that, we can\l"
	.string "be thankful.$"

NewSinjoh_EventScript_Daughter::
	msgbox NewSinjoh_Text_Daughter, MSGBOX_NPC
	end

NewSinjoh_Text_Daughter:
    .string "Wheeeeee!!\p"
    .string "Look Mommy!\n"
    .string "No hands!\p"
	.string "Just like the snowboarders!$"

NewSinjoh_EventScript_Mother::
	lock
	faceplayer
	msgbox NewSinjoh_Text_Mother, MSGBOX_AUTOCLOSE
	turnobject LOCALID_NEWSINJOH_MOTHER, DIR_EAST
	release
	end

NewSinjoh_Text_Mother:
    .string "Look at my adorable baby go!\p"
    .string "This rink has been here\n"
	.string "for generations, but the children\l"
	.string "never used it until the newcomers\l"
	.string "arrived.$"


NewSinjoh_EventScript_Welcome_Sign::
	msgbox NewSinjoh_Text_Welcome_Sign, MSGBOX_SIGN
	end

NewSinjoh_Text_Welcome_Sign:
	.string "New Sinjoh$"

NewSinjoh_EventScript_Resturant_Sign::
	msgbox NewSinjoh_Text_Resturant_Sign, MSGBOX_SIGN
	end

NewSinjoh_Text_Resturant_Sign:
	.string "FAMILY CAFE$"

NewSinjoh_EventScript_Hiker::
	msgbox NewSinjoh_Text_Hiker, MSGBOX_NPC
	end

NewSinjoh_Text_Hiker:
	.string "Business is booming!\n"
	.string "But prices have gone up since\l"
	.string "the city folk became interested\l"
	.string "in our little town.$"

NewSinjoh_EventScript_OldLady4::
	msgbox NewSinjoh_Text_OldLady4, MSGBOX_NPC
	end

NewSinjoh_Text_OldLady4:
	.string "I only sell to locals!$"

NewSinjoh_EventScript_Item_DuskBall::
	finditem ITEM_DUSK_BALL
    end


