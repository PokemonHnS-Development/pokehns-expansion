@ Story step 4a: Route 38/39, Olivine City, Cianwood City (badges 5 and 6). Runs after
@ `rungoto OlivineCity_EventScript_CityTrigger` (the Route 39 first-visit trigger, OlivineCity_hns:44-67:
@ VAR_OLIVINE_CITY_STATE 1, Cianwood's Suicune set up).
@ From here on the files give the END state of each event chain (the last value each script
@ writes), not every intermediate write; each line still names the script it comes from.

@ Route 39: the legendary shadow; this run picks GOLD = Ho-Oh, and meets Baoba
@ (Route39_EventScript_LegendaryTriggerGold:113-115, Route39_EventScript_BaobaIntro)
	setflag FLAG_HIDE_ROUTE39_SHADOW
	setvar VAR_LUGIA_OR_HOOH, 2
	setflag FLAG_ENABLE_BAOBA_MATCH_CALL
@ Olivine City: the rival walks out of the Pokemon Center (OlivineCity_EventScript_SilverTrigger:68-93)
	setvar VAR_OLIVINE_CITY_STATE, 2
	setflag FLAG_HIDE_OLIVINE_SILVER
@ Olivine Cafe: HM04 Strength (OlivineCity_Cafe_hns OlivineCity_EventScript_SailorA:31-36)
	additem ITEM_HM_STRENGTH
	setflag FLAG_RECEIVED_HM_STRENGTH
@ Lighthouse: Jasmine asks for medicine (OlivineLighthouse_EventScript_Jasmine, VAR 3)
	setvar VAR_OLIVINE_CITY_STATE, 3
@ Cianwood: Eusine and Suicune (CianwoodCity_EventScript_SuicuneTrigger:194-217)
	settrainerflag TRAINER_EUSINE_HNS
	setflag FLAG_HIDE_CIANWOOD_EUSINE
	setflag FLAG_HIDE_CIANWOOD_SUICUNE
	setvar VAR_SUICUNE_ENCOUNTERS, 2
	setvar VAR_CIANWOOD_CITY_STATE, 2
	setflag FLAG_VISITED_CIANWOOD_CITY
@ Cianwood Gym: Chuck, badge 5; his wife gives HM02 Fly (CianwoodGym_EventScript_ChuckVictory,
@ CianwoodCity_EventScript_Flytrigger:28-46)
	settrainerflag TRAINER_CHUCK_1_HNS
	setflag FLAG_BADGE05_GET
	setflag FLAG_DEFEATED_CIANWOOD_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 5
	call Common_EventScript_SetGymTrainers_hns
	additem ITEM_TM_FOCUS_PUNCH
	additem ITEM_HM_FLY
	setvar VAR_GETFLY, 2
@ Cianwood pharmacy: the Secret Potion, handed to Jasmine at once (CianwoodCity_EventScript_Pharmacist,
@ OlivineLighthouse_EventScript_JasmineDeliverPotion: removeitem, Amphy healed, VAR 5)
	setflag FLAG_HIDE_LIGHTHOUSE_JASMINE
	setvar VAR_SAFARI_ZONE_GATE_STATE, 1
	setvar VAR_OLIVINE_CITY_STATE, 5
	setflag FLAG_AMPHAROS_HEALED
	clearflag FLAG_HIDE_OLIVINE_CITY_GYM_JASMINE
@ Olivine: Baoba's call, the Safari Zone is open (OlivineCity_EventScript_BaobaCall)
	setvar VAR_SAFARI_ZONE_GATE_STATE, 2
@ Olivine Gym: Jasmine, badge 6 (OlivineCity_Gym_EventScript_JasmineVictory; battle variant 2,
@ Chuck already beaten)
	settrainerflag TRAINER_JASMINE_1_2_HNS
	setflag FLAG_BADGE06_GET
	setflag FLAG_DEFEATED_OLIVINE_CITY_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 6
	call Common_EventScript_SetGymTrainers_hns
	additem ITEM_TM_IRON_TAIL
	setvar VAR_OLIVINE_CITY_STATE, 8
	end
