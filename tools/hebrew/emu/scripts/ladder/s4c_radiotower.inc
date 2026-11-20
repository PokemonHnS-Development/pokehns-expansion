@ Story step 4c: the Goldenrod Radio Tower takeover, end state (VAR_GOLDENROD_CITY_STATE 11).
@ Sources: GoldenrodCity_RadioTower_1F_hns RadioTower1F_EventScript_Grunt:4-20,
@ GoldenrodCity_RadioTower_5F_hns _Petrel:20-40, _Archer:150-166, _WingBot:202-206 (Ho-Oh run ->
@ Rainbow Wing), _Fakeout:240-249, _Trigger_NPCS:251-256, GoldenrodCity_UndergroundTunnel_hns
@ KimonoTrigger:25-35, OpenDoor:291, GoldenrodCity_UndergroundSwitches_hns SilverTriggerBot:379-410
@ (VAR_STARTER_MON 1 -> TRAINER_RIVAL_TOTODILE_4_HNS), GoldenrodCity_UndergroundStorage_hns:11 (Card Key),
@ GoldenrodCity_RadioTower_3F_hns OpenGate:114.
	settrainerflag TRAINER_GRUNT_2_HNS
	setflag FLAG_HIDE_ROCKET_GOLDENROD_RADIOTOWER_1
	settrainerflag TRAINER_PETREL_2_HNS
	additem ITEM_BASEMENT_KEY
	setflag FLAG_HIDE_GOLDENROD_UNDERGROUND_KIMONO
	setflag FLAG_UNLOCKED_GOLDENROD_UNDERGROUND_DOOR
	settrainerflag TRAINER_RIVAL_TOTODILE_4_HNS
	setflag FLAG_HIDE_GOLDENROD_UNDERGROUND_SILVER
	setflag FLAG_COMPLETED_SWITCHES
	additem ITEM_CARD_KEY
	setflag FLAG_HIDE_RADIOTOWER_GATE
	settrainerflag TRAINER_ARIANA_2_HNS
	settrainerflag TRAINER_ARCHER_HNS
	setflag FLAG_HIDE_GOLDENROD_ROCKETS
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_PETREL
	clearflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR
	additem ITEM_RAINBOW_WING
	setflag FLAG_HIDE_GOLDENROD_RADIOTOWER_DIRECTOR_2
	setvar VAR_MAHOGANY_TOWN_STATE, 17
	clearflag FLAG_HIDE_GOLDENROD_NPCS
	setvar VAR_GOLDENROD_CITY_STATE, 11
	end
