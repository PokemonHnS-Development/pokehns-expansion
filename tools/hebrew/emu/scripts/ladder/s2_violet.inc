@ Story step 2: Violet City after the gate trigger (rungoto VioletCity_EventScript_Trigger runs
@ first: VIOLET_CITY_STATE 1, Sprout Tower rival shown, town flags).

@ Sprout Tower 3F: the rival leaves, Sage Li gives HM05 (SproutTower_3F_hns TriggerSceneLeft, SageLi)
	setflag FLAG_HIDE_SPROUT_TOWER_SILVER
	setvar VAR_SPROUT_TOWER, 1
	additem ITEM_HM_FLASH
	setflag FLAG_RECEIVED_HM_FLASH
	settrainerflag TRAINER_LI_HNS

@ Violet Gym: Falkner (VioletCity_Gym_EventScript_Falkner)
	settrainerflag TRAINER_FALKNER_1_HNS
	setflag FLAG_BADGE01_GET
	setflag FLAG_DEFEATED_VIOLET_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 1
	call Common_EventScript_SetGymTrainers_hns
	additem ITEM_TM_ROOST
	setvar VAR_VIOLET_CITY_STATE, 3
	setrespawn HEAL_LOCATION_VIOLET_CITY_HNS

@ Violet City: Elm calls about the aide (VioletCity_EventScript_ElmCall_Trigger, state 3 -> 4).
@ The aide now waits in the Violet Pokemon Center with the Togepi Egg (not taken yet).
	clearflag FLAG_HIDE_VIOLET_CITY_AIDE
	setflag FLAG_HIDE_NEWBARKTOWN_LAB_AIDE
	setvar VAR_VIOLET_CITY_STATE, 4
	end
