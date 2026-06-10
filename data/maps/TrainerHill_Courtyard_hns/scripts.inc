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
	.string "Wow, the TRAINER HILL is huge!\p"
	.string "There must be many kinds of\n"
	.string "POKéMON in there!$"

BattleTowerOutsideBeautyText:
	.string "In the BATTLE TENTS, you can\n"
	.string "use only three POKéMON.\p"
	.string "It's so hard to decide which\n"
	.string "three should go into battle…$"

BattleTowerOutsideSailorText:
	.string "Hehehe, I snuck out from work.\p"
	.string "I can't bail out until I've won!\p"
	.string "I have to win it all. That I must!$"

BattleTowerOutsideSignText:
	.string "{UP_ARROW} TRAINER HILL ENTRANCE\p"
	.string "“Scale the heights, you hot-blooded\n"
	.string "TRAINERS!”\p"
	.string "{RIGHT_ARROW} BATTLE TENTS.$"

BattleTower_Battle_Tent_Text_Factory:
	.string "BATTLE TENT: FACTORY\n"
	.string "“Find it! The ultimate POKéMON!”$"

BattleTower_Battle_Tent_Text_Palace:
	.string "BATTLE TENT: PALACE\n"
	.string "“Feast Your Eyes on Battles!”$"

BattleTower_Battle_Tent_Text_Arena:
	.string "BATTLE TENT: ARENA\n"
	.string "“May the Greatest Teams Gather!”$"

BattleTowerOutsideText_Closed:
	.string "The TRAINER HILL is currently\n"
	.string "closed for repairs.$"


TrainerHill_Courtyard_EventScript_LeftMoveTutor::
TrainerHill_Courtyard_EventScript_RightMoveTutor::
TrainerHill_Courtyard_EventScript_ElementalMoveTutor::
	lock
	faceplayer
	msgbox TrainerHill_Courtyard_Text_TutorStubbed, MSGBOX_DEFAULT
	release
	end

TrainerHill_Courtyard_Text_TutorStubbed:
	.string "…$"

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
	.string "Hi! If you are looking for the\n"
	.string "WONDERTRADE, they're now located in\l"
	.string "every POKéMON CENTER. Have fun!$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize:
	.string "Hello, this is the EXCHANGE SERVICE\n"
	.string "CORNER.\p"
	.string "We exchange the Battle Points you\n"
	.string "have collected for lovely prizes.\p"
	.string "Please choose a prize from this list.$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_WishIHadAllDolls:
	.string "Oh, they're so nice!\n"
	.string "I wish I had them!\l"
	.string "Cute cushions!\l"
	.string "Big plush DOLLS!\l"
	.string "Little plush DOLLS!\l"
	.string "I wish I had them all!$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_GetYouAnythingYouWant:
	.string "Leave it to your mommy!\p"
	.string "If it's anything you want, I'll go\n"
	.string "through anything to get it, honey!$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_ItemsWillGetMonTougher:
	.string "If I can get hold of the items here,\n"
	.string "my POKéMON will get tougher.\p"
	.string "You bet they will!\n"
	.string "No question about it!$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_GoGetYourOwnDoll:
	.string "Hah?\n"
	.string "What are you gawking at?\p"
	.string "I don't like you staring at my plush\n"
	.string "doll like that.\p"
	.string "If you want it, go get one yourself!\n"
	.string "Isn't that right, SMOOCHUM?$"

TrainerHill_Courtyard_ExchangeServiceCorner_Text_MoreBattlePointsForRecord:
	.string "Did you know?\p"
	.string "If you stretch your record at any of\n"
	.string "the BATTLE facilities, they start\l"
	.string "giving you more and more Battle Points.$"
