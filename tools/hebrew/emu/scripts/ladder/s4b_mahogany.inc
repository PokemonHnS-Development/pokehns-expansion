@ Story step 4b: Lake of Rage, the Mahogany Rocket hideout, Pryce (badge 7), the Radio Tower
@ takeover call. Runs after `rungoto MahoganyTown_EventScript_TownTrigger` (the Route 42 first-visit
@ trigger, Mahoganytown_hns:33-90: VAR_MAHOGANY_TOWN_STATE 1, hideout and Blackthorn flags).

@ Lake of Rage: the red Gyarados (LakeOfRage_EventScript_Defeated_Gyarados:100-111), Lance
@ (LakeOfRage_EventScript_Lance:148), the end of the scene (LakeOfRage_EventScript_EndScene:160-166)
	setflag FLAG_VISITED_LAKE_OF_RAGE
	setflag FLAG_HIDE_LAKE_OF_RAGE_GYARADOS
	additem ITEM_RED_SCALE
	setflag FLAG_HIDE_LAKE_OF_RAGE_LANCE
	setvar VAR_MAHOGANY_TOWN_STATE, 4
@ Mahogany souvenir shop raid (MahoganyTown_Shop_EventScript_Raid:103-106)
	setflag FLAG_HIDE_MAHOGANY_TOWN_SHOP_NPCS
	setvar VAR_MAHOGANY_TOWN_STATE, 5
@ Rocket hideout B1F-B3F, end state after Petrel, Giovanni's double, Ariana and the Electrodes
@ (RocketHideout_B3F_EventScript_Giovanni:300-358, RocketHideout_B2F_EventScript_DefeatedAriana
@ :322-366, RocketHideout_B2F_EventScript_ElectrodeDone:500-522, which also gives HM Whirlpool)
	settrainerflag TRAINER_PETREL_1_HNS
	settrainerflag TRAINER_GRUNT_14_HNS
	settrainerflag TRAINER_GRUNT_15_HNS
	settrainerflag TRAINER_GRUNT_16_HNS
	settrainerflag TRAINER_GRUNT_29_HNS
	settrainerflag TRAINER_ETO_2_HNS
	settrainerflag TRAINER_MITCH_HNS
	settrainerflag TRAINER_ROSS_HNS
	setflag FLAG_HIDE_ROCKETHIDEOUT_ROCKETS
	setflag FLAG_HIDE_ROCKETHIDEOUT3_SILVER
	setflag FLAG_HIDE_ROCKETHIDEOUT3_PETREL
	setflag FLAG_HIDE_ROCKETHIDEOUT3_GIOVANNI
	setflag FLAG_HIDE_ROCKETHIDEOUT3_MURKROW
	setflag FLAG_HIDE_ROCKETHIDEOUT3_MURKROWSTAIRS
	setflag FLAG_HIDE_ROCKETHIDEOUT3_GATE
	setflag FLAG_HIDE_ROCKETHIDEOUT3_LANCE_DRAGONITE
	setflag FLAG_HIDE_ROCKETHIDEOUT2_MURKROWSTAIRS
	setflag FLAG_HIDE_ROCKETHIDEOUT2_MURKROWGATE
	setflag FLAG_HIDE_ROCKETHIDEOUT2_GATE
	setflag FLAG_HIDE_ROCKETHIDEOUT2_ARIANA_AND_GRUNT
	setflag FLAG_HIDE_ROCKETHIDEOUT2_LANCE_DRAGONITE
	setflag FLAG_HIDE_ROCKETHIDEOUT_ELECTRODE1
	setflag FLAG_HIDE_ROCKETHIDEOUT_ELECTRODE2
	setflag FLAG_HIDE_ROCKETHIDEOUT_ELECTRODE3
	setflag FLAG_GOT_PASSWORD_FROM_ETO
	setflag FLAG_GOT_PASSWORD_FROM_GRUNTF
	setvar VAR_ELECTRODES_FAINTED, 4
	setflag FLAG_HIDE_MAHOGANY_ROCKETS
	additem ITEM_HM_WHIRLPOOL
	clearflag FLAG_HIDE_MAHOGANY_COP
	setflag FLAG_HIDE_MAHOGANY_TOWN_FATMAN
	setvar VAR_MAHOGANY_TOWN_STATE, 14
@ Mahogany Gym: Pryce, badge 7 (MahoganyTown_Gym_EventScript_PryceVictory:75-90; battle variant 3,
@ Chuck and Jasmine already beaten). The 7th badge arms Elm's Radio Tower call.
	settrainerflag TRAINER_PRYCE_1_3_HNS
	setflag FLAG_BADGE07_GET
	setflag FLAG_DEFEATED_MAHOGANY_TOWN_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 7
	call Common_EventScript_SetGymTrainers_hns
	additem ITEM_TM_HAIL
	setvar VAR_MAHOGANY_TOWN_STATE, 15
	setvar VAR_TRIGGER_ELM_ROCKET_CALL, 1
@ Mahogany: Elm's call, Team Rocket takes over the Radio Tower (Mahoganytown_EventScript_RocketTrigger:19-31)
	setvar VAR_GOLDENROD_CITY_STATE, 6
	clearflag FLAG_HIDE_GOLDENROD_ROCKETS
	setflag FLAG_HIDE_GOLDENROD_ROCKET_SCOUT
	setflag FLAG_HIDE_GOLDENROD_NPCS
	clearflag FLAG_HIDE_ROCKET_GOLDENROD_RADIOTOWER_1
	setvar VAR_MAHOGANY_TOWN_STATE, 16
	setvar VAR_TRIGGER_ELM_ROCKET_CALL, 2
	end
