@ Story step 6a: the rest of Kanto on top of ladder 5 (badges 9, 10, 14, 15, 16; the Power Plant /
@ Machine Part chain; Snorlax; Oak's Mt. Silver permission). End states, each line naming its script.

@ Power Plant -> Cerulean Gym grunt -> Route 24 -> Machine Part -> Power Plant manager
@ (Route10_PowerPlantEntrance_Trigger_Cop:84-85, CeruleanCity_Gym_EventScript_RocketGrunt:36-40,
@ Route24_EventScript_Grunt:92-95, CeruleanCity_Gym_EventScript_MachinePartItem:69-70,
@ Route10_PowerPlantBackRoom_EventScript_ManagerCheckPart:43-48)
	setflag FLAG_VISITED_ROUTE10
	setflag FLAG_VISITED_CERULEAN_CITY
	setflag FLAG_HIDE_CERULEAN_GYM_ROCKET
	settrainerflag TRAINER_GRUNT_31_HNS
	setflag FLAG_HIDE_CERULEAN_CAPE_ROCKET
	setflag FLAG_HIDDEN_ITEM_MACHINE_PART
	setflag FLAG_RETURNED_MACHINE_PART
	clearflag FLAG_HIDE_ROUTE25_MISTY
	setvar VAR_CERULEAN_CITY_STATE, 2
	setflag FLAG_HIDE_POWER_PLANT_ENGINEER
	setvar VAR_KANTO_ROCKET_STORY_STATE, 7
	setvar VAR_VERMILION_CITY_SAMSON, 1
@ Route 25: Misty's date interrupted, back to her gym (Route25_EventScript_Misty:126-134)
	setflag FLAG_HIDE_ROUTE25_MISTY
	clearflag FLAG_HIDE_CERULEAN_GYM_TRAINERS
	setflag FLAG_HIDE_CERULEAN_GYM_POKEMON
	setvar VAR_CERULEAN_CITY_STATE, 3
@ Cerulean Gym: Misty (CeruleanCity_Gym_EventScript_Misty:185-200)
	settrainerflag TRAINER_MISTY_HNS
	setflag FLAG_BADGE10_GET
	setflag FLAG_DEFEATED_CERULEAN_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 10
	call Common_EventScript_SetGymTrainers_hns
	clearflag FLAG_HIDE_CAPE_MISTY
@ Lavender Radio Tower: the Kanto radio expansion (LavenderTown_RadioStation_EventScript_
@ DirectorReturnedMachinePart:20-31); Vermilion: Snorlax woken and beaten
@ (VermilionCity_EventScript_SnorlaxWakeUp:190-210)
	setflag FLAG_VISITED_LAVENDER_TOWN
	setflag FLAG_KANTO_RADIO_GOT
	setflag FLAG_HIDE_VERMILION_SNORLAX
	setflag FLAG_INDIGOJUNCTION_HIDE_KANTO_GUARD
@ Copycat's doll and the Magnet Train pass (VermilionCity_FanClub_EventScript_ClefairyGiveDoll:54-59,
@ SaffronCity_CopyCatsHouse_2F_EventScript_CopycatReturnDoll:147-154)
	setvar VAR_FAN_CLUB_GUY, 1
	setflag FLAG_HIDE_FAN_CLUB_CLEFAIRY_DOLL
	clearflag FLAG_HIDE_COPYCAT_CLEFAIRY_DOLL
	setvar VAR_FAN_CLUB_CLEFAIRY, 3
	additem ITEM_PASS
@ Mt. Moon: the rival (MtMoon_Cave_EventScript_SilverAfterBattle:56-61; VAR_STARTER_MON 1 -> Totodile)
	settrainerflag TRAINER_RIVAL_TOTODILE_6_HNS
	setflag FLAG_HIDE_MTMOON_SILVER
	clearflag FLAG_HIDE_INDIGO_PLATEAU_SILVER
	setvar VAR_PEWTER_CITY_STATE, 2
@ Pewter Gym: Brock (PewterCity_Gym_EventScript_Brock:17-29)
	setflag FLAG_VISITED_PEWTER_CITY
	settrainerflag TRAINER_BROCK_HNS
	setflag FLAG_BADGE09_GET
	setflag FLAG_DEFEATED_PEWTER_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 9
	call Common_EventScript_SetGymTrainers_hns
	clearflag FLAG_HIDE_DIGLETT_BROCK
@ Fuchsia: Baoba's call, Janine (FuchsiaCity_EventScript_BaobaCall:15-16, FuchsiaCity_Gym_EventScript_Janine:50-78)
	setflag FLAG_VISITED_FUCHSIA_CITY
	setvar VAR_BAOBA_QUEST_STATE, 1
	setvar VAR_FUCHSIA_CITY_STATE, 1
	settrainerflag TRAINER_JANINE_HNS
	setflag FLAG_BADGE14_GET
	setflag FLAG_DEFEATED_FUCHSIA_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 14
	call Common_EventScript_SetGymTrainers_hns
	clearflag FLAG_HIDE_ROUTE22_JANINE
@ Cinnabar: Blaine moved to the Seafoam gym, Blue (CinnabarIsland_EventScript_Blaine:14-21,
@ CinnabarIsland_EventScript_BlueActive:40-47, SeafoamIslands_Gym_EventScript_Blaine:15-26)
	setflag FLAG_VISITED_CINNABAR_ISLAND
	setflag FLAG_HIDE_CINNABAR_BLAINE
	clearflag FLAG_HIDE_DOJO_BLAINE
	setflag FLAG_HIDE_CINNABAR_BLUE
	clearflag FLAG_HIDE_VIRIDIAN_BLUE
	settrainerflag TRAINER_BLAINE_HNS
	setflag FLAG_BADGE15_GET
	setflag FLAG_DEFEATED_CINNABAR_ISLAND_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 15
	call Common_EventScript_SetGymTrainers_hns
	clearflag FLAG_HIDE_SEAFOAM_GYMGUY
@ Pallet Town (PalletTown_EventScript_CityEnter:6, PalletTown_Lab_EventScript_Oak:12)
	setflag FLAG_VISITED_PALLET_TOWN
	setflag FLAG_VISITED_OAKS_LAB
	setvar VAR_PALLETTOWN_LABSTATE, 1
@ Viridian Gym: Blue, badge 16; Oak's call (ViridianCity_Gym_EventScript_Blue:4-30,
@ ViridianCity_EventScript_OakCall:15-21)
	setflag FLAG_VISITED_VIRIDIAN_CITY
	settrainerflag TRAINER_BLUE_HNS
	additem ITEM_TM_TRICK_ROOM
	setflag FLAG_BADGE16_GET
	setflag FLAG_DEFEATED_VIRIDIAN_GYM
	addvar VAR_NUM_BADGES, 1
	setvar VAR_0x8008, 16
	call Common_EventScript_SetGymTrainers_hns
	setflag FLAG_HIDE_LEAGUE_BLACKBELT
	setvar VAR_OAK_MT_SILVER_CALL, 2
@ Oak's lab with 16 badges: Mt. Silver opens (PalletTown_Lab_EventScript_Oak16Badges:31-39)
	setflag FLAG_INDIGOJUNCTION_HIDE_SILVER_GUARD
	setvar VAR_ROUTE28_SCIENTIST, 1
	setvar VAR_PALLETTOWN_LABSTATE, 2
@ The League rematch as Kanto champion: Elite Four and Lance beaten again (the rematch trainers,
@ PokemonLeague_*Room_EventScript_*RematchStandard). The Hall of Fame is run by the ROM.
	setflag FLAG_VISITED_INDIGO_PLATEAU
	settrainerflag TRAINER_WILL_2_HNS
	settrainerflag TRAINER_KOGA_2_HNS
	settrainerflag TRAINER_BRUNO_2_HNS
	settrainerflag TRAINER_KAREN_2_HNS
	settrainerflag TRAINER_LANCE_2_HNS
	end
