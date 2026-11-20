@ Story step 5b: Kanto, three Kanto badges (Thunder, Marsh, Rainbow). Runs after the S.S. Aqua's
@ LeaveBoat flagheap (Kanto badges cleared, VAR_NUM_BADGES 8, VAR_VERMILION_CITY_STATE 1).

@ Vermilion City: first visit, Steven and the roaming Latios/Latias choice (VermilionCity_MapScript_
@ OnTransition:6-10, VermilionCity_EventScript_TriggerStevenLeft:420-430, _LatiChoice:481-489;
@ the multichoice's first entry, 0, is picked here)
	setflag FLAG_VISITED_VERMILION_CITY
	setvar VAR_0x8004, 0
	copyvar VAR_ROAMER_POKEMON_HNS, VAR_0x8004
	special InitKantoRoamers
	setflag FLAG_LATIOS_OR_LATIAS_ROAMING
	setvar VAR_VERMILION_CITY_STEVEN, 1
	setflag FLAG_HIDE_VERMILION_STEVEN
@ Vermilion Gym: Lt. Surge (VermilionCity_Gym_EventScript_Surge:...-270)
	settrainerflag TRAINER_LTSURGE_HNS
	setflag FLAG_BADGE11_GET
	setflag FLAG_DEFEATED_VERMILION_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 11
	call Common_EventScript_SetGymTrainers_hns
	additem ITEM_TM_SHOCK_WAVE
	clearflag FLAG_HIDE_PLANT_SURGE
@ Saffron City and Gym: Sabrina (SaffronCity_EventScript_CityEnter:6, SaffronCity_Gym_EventScript_Sabrina)
	setflag FLAG_VISITED_SAFFRON_CITY
	settrainerflag TRAINER_SABRINA_HNS
	additem ITEM_TM_SKILL_SWAP
	setflag FLAG_BADGE13_GET
	setflag FLAG_DEFEATED_SAFFRON_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 13
	call Common_EventScript_SetGymTrainers_hns
	clearflag FLAG_HIDE_OLIVINE_SABRINA
@ Celadon City and Gym: Erika (CeladonCity_EventScript_CityEnter:6, CeladonCity_Gym_EventScript_Erika:5-24)
	setflag FLAG_VISITED_CELADON_CITY
	settrainerflag TRAINER_ERIKA_HNS
	additem ITEM_TM_GIGA_DRAIN
	setflag FLAG_BADGE12_GET
	setflag FLAG_DEFEATED_CELADON_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 12
	call Common_EventScript_SetGymTrainers_hns
	clearflag FLAG_HIDE_FOUNTAIN_ERIKA
	setrespawn HEAL_LOCATION_CELADON_CITY_HNS
	end
