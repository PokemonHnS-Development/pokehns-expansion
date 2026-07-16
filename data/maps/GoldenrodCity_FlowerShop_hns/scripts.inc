GoldenrodCity_FlowerShop_hns_MapScripts::
	.byte 0


GoldenrodCity_FlowerShop_EventScript_MintClerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart GoldenrodCity_FlowerShop_Mints
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
GoldenrodCity_FlowerShop_Mints:
	.2byte ITEM_SERIOUS_MINT
	.2byte ITEM_ADAMANT_MINT
	.2byte ITEM_BOLD_MINT
	.2byte ITEM_BRAVE_MINT
	.2byte ITEM_CALM_MINT
	.2byte ITEM_CAREFUL_MINT
	.2byte ITEM_GENTLE_MINT
	.2byte ITEM_HASTY_MINT
	.2byte ITEM_IMPISH_MINT
	.2byte ITEM_JOLLY_MINT
	.2byte ITEM_LAX_MINT
	.2byte ITEM_LONELY_MINT
	.2byte ITEM_MILD_MINT
	.2byte ITEM_MODEST_MINT
	.2byte ITEM_NAIVE_MINT
	.2byte ITEM_NAUGHTY_MINT
	.2byte ITEM_QUIET_MINT
	.2byte ITEM_RASH_MINT
	.2byte ITEM_RELAXED_MINT
	.2byte ITEM_SASSY_MINT
	.2byte ITEM_TIMID_MINT
	pokemartlistend


GoldenrodCity_FlowerShop_EventScript_Owner::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SUDOWOODO, GoldenrodCity_FlowerShop_EventScript_Normal
	goto_if_set FLAG_RECEIVED_SQUIRTBOTTLE, GoldenrodCity_FlowerShop_EventScript_GotSquirtBottle
	goto_if_set FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_GiveSquirtBottle
	msgbox GoldenrodCity_FlowerShop_Text_Owner1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_GiveSquirtBottle::
	lock
	faceplayer
	msgbox GoldenrodCity_FlowerShop_Text_Owner2, MSGBOX_DEFAULT
	giveitem ITEM_SQUIRT_BOTTLE
	setflag FLAG_RECEIVED_SQUIRTBOTTLE
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_GotSquirtBottle::
	lock
	faceplayer
	msgbox GoldenrodCity_FlowerShop_Text_Owner3, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_Normal::
	lock
	faceplayer
	msgbox GoldenrodCity_FlowerShop_Text_Owner4, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_Floria1::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SUDOWOODO, GoldenrodCity_FlowerShop_EventScript_Floria3
	goto_if_set FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_Floria2
	msgbox GoldenrodCity_FlowerShop_Text_Floria, MSGBOX_DEFAULT
	closemessage
	release
	end
	
GoldenrodCity_FlowerShop_EventScript_Floria2::
	msgbox GoldenrodCity_FlowerShop_Text_FloriaYouBeatWhitney, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_Floria3::
	msgbox GoldenrodCity_FlowerShop_Text_FloriaItWasAMon, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_Text_Floria:
	.string "When I told my sis about the jiggly\n"
	.string "tree, she said it's dangerous.\p"
	.string "If I beat WHITNEY, I wonder if\n"
	.string "she'll lend me her water bottle…$"

GoldenrodCity_FlowerShop_Text_Owner1:
.string "Apparently, there is an odd tree\n"
.string "on ROUTE 36.\p"
.string "They say it dances when you water\n"
.string "it...\p"
.string "Oh, of course not!\p"
.string "This is a flower shop, so we do\n"
.string "have watering cans...\p"
.string "But I cannot let you have one!\n"
.string "It's too dangerous!\p"
.string "Well, maybe if you manage to\n"
.string "defeat gym leader WHITNEY, it\l"
.string "might be okay.$"

GoldenrodCity_FlowerShop_Text_Owner2:
.string "Apparently, there is an odd tree\n"
.string "on ROUTE 36.\p"
.string "They say it dances when you water\n"
.string "it...\p"
.string "Oh, that's a PLAINBADGE from\n"
.string "The GOLDENROD GYM!\p"
.string "Did you defeat WHITNEY?!\p"
.string "Well, then there's nothing to worry\n"
.string "about, is there?\p"
.string "I'll let you use this SQUIRTBOTTLE\n"
.string "for a while then.\l"
.string "...\p"
.string "Oh, never mind. Keep it!$"

GoldenrodCity_FlowerShop_Text_Owner3:
.string "The odd tree is on ROUTE 36.\n"
.string "Please be careful!$"

GoldenrodCity_FlowerShop_Text_Owner4:
    .string "Lalala lalalala. Have plenty of\n"
    .string "water, my lovely!$"

GoldenrodCity_FlowerShop_Text_FloriaYouBeatWhitney:
    .string "Wow, you beat WHITNEY? Cool!$"

GoldenrodCity_FlowerShop_Text_FloriaItWasAMon:
    .string "So it really was a POKéMON!$"
