@ Story step 3d: Ecruteak City up to the Fog Badge. Runs after `rungoto EcruteakCity_EventScript_Trigger`
@ (the Route 37 first-visit trigger, EcruteakCity_hns:19-59: VAR_ECRUTEAK_CITY_STATE 1, theater 0,
@ town and legendary flags).

@ Ecruteak Pokemon Center: Bill goes home to Goldenrod, his PC is now "BILL's PC"
@ (EcruteakCity_PokemonCenter_EventScript_Bill:9-26)
	setflag FLAG_HIDE_ECRUTEAK_BILL
	setflag FLAG_SYS_PC_BILL
	clearflag FLAG_HIDE_GOLDENROD_BILL
@ Burned Tower 1F: Eusine (BurnedTower_1F_EventScript_MeetEusine:24-38)
	setvar VAR_ECRUTEAK_CITY_STATE, 2
@ Burned Tower 1F: third rival battle, the floor gives way (BurnedTower_1F_EventScript_Silver:101-139;
@ VAR_STARTER_MON 1 -> BurnedTower_1F_Silver_Battle_Totodile)
	settrainerflag TRAINER_RIVAL_TOTODILE_3_HNS
	setvar VAR_ECRUTEAK_CITY_STATE, 3
@ Burned Tower B1F: the three beasts flee and start roaming (BurnedTower_B1F_EventScript_ReleaseBeasts:15-123)
	setflag FLAG_HIDE_BURNED_TOWER_BEASTS
	setflag FLAG_HIDE_BURNED_TOWER_B1F_EUSINE
	setflag FLAG_HIDE_BURNED_TOWER_NPCS
	setflag FLAG_HIDE_ECRUTEAK_CITY_SAGE
	special InitRoamer
	setflag FLAG_RELEASED_BEASTS
	setvar VAR_ECRUTEAK_CITY_STATE, 4
@ Dance Theater: the Rocket scene, the grunt, the Surf HM
@ (EcruteakCity_Theater_EventScript_RocketEventTrigger:24-52, _Rocket:129-148, _TriggerSurfGuy:283-298)
	setvar VAR_ECRUTEAK_CITY_THEATER, 1
	settrainerflag TRAINER_GRUNT_33_HNS
	setflag FLAG_HIDE_ECRUTEAK_ROCKET
	setvar VAR_ECRUTEAK_CITY_THEATER, 2
	additem ITEM_HM_SURF
	setflag FLAG_RECEIVED_HM_SURF
	setvar VAR_ECRUTEAK_CITY_THEATER, 3
@ Ecruteak Gym: Morty (EcruteakCity_Gym_EventScript_Morty:37-57)
	settrainerflag TRAINER_MORTY_1_HNS
	setflag FLAG_BADGE04_GET
	setflag FLAG_DEFEATED_ECRUTEAK_CITY_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 4
	call Common_EventScript_SetGymTrainers_hns
	additem ITEM_TM_SHADOW_BALL
	setvar VAR_ECRUTEAK_CITY_STATE, 4
	setrespawn HEAL_LOCATION_ECRUTEAK_CITY_HNS
	end
