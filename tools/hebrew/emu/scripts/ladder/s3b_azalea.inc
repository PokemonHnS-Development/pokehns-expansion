@ Story step 3b: Azalea Town and Ilex Forest. Runs after `rungoto AzaleaTown_EventScript_Trigger`
@ (the Route 33 first-visit trigger, AzaleaTown_hns:19-50: VAR_AZALEA_TOWN_STATE 1, town flags).

@ Kurt's house: Kurt runs off to the well (AzaleaTown_KurtsHouse_EventScript_KurtBefore:14-28)
	setflag FLAG_HIDE_KURT_1
	setflag FLAG_HIDE_AZALEA_TOWN_WELL_ROCKET
	setvar VAR_AZALEA_TOWN_STATE, 2
@ Slowpoke Well B1F: the grunts and Proton (SlowpokeWell_B1F_hns:26-70)
	settrainerflag TRAINER_GRUNT_21_HNS
	settrainerflag TRAINER_GRUNT_22_HNS
	settrainerflag TRAINER_ETO_HNS
	settrainerflag TRAINER_PROTON_1_HNS
	setflag FLAG_HIDE_AZALEA_TOWN_ROCKETS
	setflag FLAG_HIDE_SLOWPOKE_WELL_KURT
	setflag FLAG_HIDE_KURT_1
	clearflag FLAG_HIDE_KURT_2
	clearflag FLAG_HIDE_AZALEA_TOWN_SLOWPOKE
	setvar VAR_AZALEA_TOWN_STATE, 3
@ Kurt's house: Kurt's thanks, a Fast Ball (AzaleaTown_KurtsHouse_EventScript_ReturnFromWell:86-97)
	additem ITEM_FAST_BALL
	setvar VAR_AZALEA_TOWN_STATE, 4
@ Azalea Gym: Bugsy (AzaleaTown_Gym_EventScript_Bugsy:525-549)
	settrainerflag TRAINER_BUGSY_1_HNS
	setflag FLAG_BADGE02_GET
	setflag FLAG_DEFEATED_AZALEA_TOWN_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 2
	call Common_EventScript_SetGymTrainers_hns
	additem ITEM_TM_U_TURN
	setvar VAR_AZALEA_TOWN_STATE, 5
	setflag FLAG_HIDE_AZALEA_TOWN_FARFETCHD
	setflag FLAG_GET_HEADBUTT
	clearflag FLAG_HIDE_ILEX_FOREST_APPRENTICE
	clearflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_1
@ Azalea Town: second rival battle at the gate. VAR_STARTER_MON 1 (Cyndaquil) -> the rival
@ has Totodile (AzaleaTown_EventScript_SilverTriggerTop:152-176, AzaleaTown_Silver_Battle_Totodile)
	settrainerflag TRAINER_RIVAL_TOTODILE_2_HNS
	setflag FLAG_HIDE_AZALEA_TOWN_SILVER
	setvar VAR_AZALEA_TOWN_STATE, 6
@ Ilex Forest: the Farfetch'd chase, the charcoal master's HM01 (IlexForest_EventScript_Farfetchd_Leave
@ :159-170, IlexForest_EventScript_Trigger:187-205)
	setvar VAR_ILEX_FOREST_FARFETCHD, 2
	clearflag FLAG_HIDE_ILEX_FOREST_KIMONO
	clearflag FLAG_HIDE_ILEX_FOREST_MASTER
	setflag FLAG_HIDE_AZALEA_TOWN_CUT_MASTER
	additem ITEM_HM_CUT
	setflag FLAG_RECEIVED_HM_CUT
	setflag FLAG_HIDE_ILEX_FOREST_MASTER
	setflag FLAG_HIDE_ILEX_FOREST_APPRENTICE
	setflag FLAG_HIDE_ILEX_FOREST_FARFETCHD_1
	setvar VAR_ILEX_FOREST_FARFETCHD, 3
	setvar VAR_AZALEA_TOWN_STATE, 7
	clearflag FLAG_HIDE_AZALEA_TOWN_FARFETCHD
	clearflag FLAG_HIDE_AZALEA_TOWN_CUT_MASTER
@ Ilex Forest: the second Kimono Girl (IlexForest_EventScript_Kimono:315-361)
	setvar VAR_ILEX_FOREST_FARFETCHD, 4
	setflag FLAG_HIDE_ILEX_FOREST_KIMONO
	end
