@ Story step 3c: Goldenrod City to Route 37. Runs after `rungoto GoldenrodCity_EventScript_Trigger`
@ (the Route 34 first-visit trigger, GoldenrodCity_hns:4-47: VAR_GOLDENROD_CITY_STATE 1, town flags;
@ it also plays Elm's Togepi call, so it is run with A tapped).

@ Radio Tower 1F: the quiz and the radio card (RadioTower1F_EventScript_ReceptionGiveRadio:121-146)
	setflag FLAG_ENABLE_RADIO
	setflag FLAG_HIDE_GOLDENROD_BEAUTY
	setvar VAR_GOLDENROD_CITY_STATE, 2
@ Bike Shop: the free Bicycle (GoldenrodCity_BikeShop_EventScript_Clerk_BikeAgreed:15-21)
	additem ITEM_BICYCLE
	setflag FLAG_RECEIVED_BIKE
@ Goldenrod Gym: Whitney wins, cries, the gym trigger, then the badge
@ (GoldenrodCity_Gym_EventScript_Whitney:41-53, _Trigger:92-99, _WhitneyBadge:63-82)
	settrainerflag TRAINER_WHITNEY_1_HNS
	setvar VAR_GOLDENROD_CITY_STATE, 3
	setvar VAR_GOLDENROD_CITY_STATE, 4
	setflag FLAG_BADGE03_GET
	setflag FLAG_DEFEATED_GOLDENROD_CITY_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 3
	call Common_EventScript_SetGymTrainers_hns
	additem ITEM_TM_ATTRACT
	setvar VAR_GOLDENROD_CITY_STATE, 5
@ Flower shop: the Squirt Bottle (GoldenrodCity_FlowerShop_EventScript_GiveSquirtBottle:63-70)
	additem ITEM_SQUIRT_BOTTLE
	setflag FLAG_RECEIVED_SQUIRTBOTTLE
@ Route 36: Sudowoodo beaten, the Rock Smash HM (Route36_EventScript_Defeated_Sudowoodo:126-132,
@ Route36_EventScript_RockSmashGuy2:18-22)
	setflag FLAG_HIDE_SUDOWOODO
	additem ITEM_HM_ROCK_SMASH
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
	end
