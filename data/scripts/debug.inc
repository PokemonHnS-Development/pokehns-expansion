Debug_MessageEnd:
	waitmessage
	waitbuttonpress
	releaseall
	end

Debug_ShowFieldMessageStringVar4::
	special ShowFieldMessageStringVar4
	goto Debug_MessageEnd

Debug_CheatStart::
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_RESCUED_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH_ZIGZAGOON_BATTLE
	setflag FLAG_ADVENTURE_STARTED
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_BIRCH
	setflag FLAG_HIDE_ROUTE_101_BIRCH_STARTERS_BAG
	setvar VAR_BIRCH_LAB_STATE, 2
	setvar VAR_ROUTE101_STATE, 3
	givemon SPECIES_TREECKO, 20, ITEM_NONE
	givemon SPECIES_TORCHIC, 20, ITEM_NONE
	givemon SPECIES_MUDKIP, 20, ITEM_NONE
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
	setvar VAR_CABLE_CLUB_TUTORIAL_STATE, 2
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	setflag FLAG_RECEIVED_RUNNING_SHOES
	setflag FLAG_SYS_B_DASH
	setvar VAR_LITTLEROOT_TOWN_STATE, 4 @ 4: Received Running Shoes
	setvar VAR_LITTLEROOT_INTRO_STATE, 7 @ 7: Told to go meet rival
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 2 @ 2: Met Rival's Mom (and is corresponding gender)
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 2 @ 2: Met Rival's Mom (and is corresponding gender)
	setvar VAR_LITTLEROOT_RIVAL_STATE, 4 @ 4: Received Pokedex
	setflag FLAG_RECEIVED_BIKE
	additem ITEM_ACRO_BIKE
	setvar VAR_BRINEY_HOUSE_STATE, 1
	setvar VAR_ROUTE116_STATE, 2
	setflag FLAG_HIDE_ROUTE_116_MR_BRINEY
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setflag FLAG_BADGE03_GET
	setflag FLAG_BADGE04_GET
	setflag FLAG_BADGE05_GET
	setflag FLAG_BADGE06_GET
	setflag FLAG_BADGE07_GET
	setflag FLAG_BADGE08_GET
	setflag FLAG_VISITED_LITTLEROOT_TOWN
	setflag FLAG_VISITED_OLDALE_TOWN
	setflag FLAG_VISITED_DEWFORD_TOWN
	setflag FLAG_VISITED_LAVARIDGE_TOWN
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setflag FLAG_VISITED_VERDANTURF_TOWN
	setflag FLAG_VISITED_PACIFIDLOG_TOWN
	setflag FLAG_VISITED_PETALBURG_CITY
	setflag FLAG_VISITED_SLATEPORT_CITY
	setflag FLAG_VISITED_MAUVILLE_CITY
	setflag FLAG_VISITED_RUSTBORO_CITY
	setflag FLAG_VISITED_FORTREE_CITY
	setflag FLAG_VISITED_LILYCOVE_CITY
	setflag FLAG_VISITED_MOSSDEEP_CITY
	setflag FLAG_VISITED_SOOTOPOLIS_CITY
	setflag FLAG_VISITED_EVER_GRANDE_CITY
	setflag FLAG_LANDMARK_POKEMON_LEAGUE
	setflag FLAG_LANDMARK_BATTLE_FRONTIER
	clearflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
	clearflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
	release
	end

Debug_CheatStartFrlg::
	setflag FLAG_SYS_POKEMON_GET
	setflag FLAG_PALLET_LADY_NOT_BLOCKING_SIGN
	setflag FLAG_OPENED_START_MENU
	setflag FLAG_VISITED_OAKS_LAB
	setflag FLAG_BEAT_RIVAL_IN_OAKS_LAB
	givemon SPECIES_BULBASAUR, 20, ITEM_NONE
	givemon SPECIES_CHARMANDER, 20, ITEM_NONE
	givemon SPECIES_SQUIRTLE, 20, ITEM_NONE
	clearflag FLAG_HIDE_OAK_IN_HIS_LAB
	setflag FLAG_HIDE_RIVAL_IN_LAB
	setvar VAR_MAP_SCENE_PALLET_TOWN_OAK, 1 @ prevents Oak scene when trying to enter Route 1
	setflag FLAG_SYS_POKEDEX_GET
	special SetUnlockedPokedexFlags
	setvar VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 6 @ state after handing in parcel and getting pokedex
	setvar VAR_MAP_SCENE_VIRIDIAN_CITY_MART, 2
	setvar VAR_MAP_SCENE_VIRIDIAN_CITY_OLD_MAN, 1
	setvar VAR_MAP_SCENE_PALLET_TOWN_RIVALS_HOUSE, 1
	setvar VAR_MAP_SCENE_ROUTE22, 1
	setvar VAR_MAP_SCENE_POKEMON_CENTER_TEALA, 1 @ end
	setflag FLAG_SYS_NATIONAL_DEX
	special EnableNationalPokedex
	setflag FLAG_SYS_B_DASH
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setflag FLAG_BADGE03_GET
	setflag FLAG_BADGE04_GET
	setflag FLAG_BADGE05_GET
	setflag FLAG_BADGE06_GET
	setflag FLAG_BADGE07_GET
	setflag FLAG_BADGE08_GET
	setflag FLAG_GOT_BIKE_VOUCHER
	setflag FLAG_GOT_BICYCLE
	additem ITEM_BICYCLE
	setflag FLAG_WORLD_MAP_PALLET_TOWN
	setflag FLAG_WORLD_MAP_VIRIDIAN_CITY
	setflag FLAG_WORLD_MAP_PEWTER_CITY
	setflag FLAG_WORLD_MAP_ROUTE4_POKEMON_CENTER_1F
	setflag FLAG_WORLD_MAP_CERULEAN_CITY
	setflag FLAG_WORLD_MAP_VERMILION_CITY
	setflag FLAG_WORLD_MAP_ROUTE10_POKEMON_CENTER_1F
	setflag FLAG_WORLD_MAP_LAVENDER_TOWN
	setflag FLAG_WORLD_MAP_CELADON_CITY
	setflag FLAG_WORLD_MAP_FUCHSIA_CITY
	setflag FLAG_WORLD_MAP_SAFFRON_CITY
	setflag FLAG_WORLD_MAP_CINNABAR_ISLAND
	setflag FLAG_WORLD_MAP_INDIGO_PLATEAU_EXTERIOR
	setflag FLAG_WORLD_MAP_ONE_ISLAND
	setflag FLAG_WORLD_MAP_TWO_ISLAND
	setflag FLAG_WORLD_MAP_THREE_ISLAND
	setflag FLAG_WORLD_MAP_FOUR_ISLAND
	setflag FLAG_WORLD_MAP_FIVE_ISLAND
	setflag FLAG_WORLD_MAP_SIX_ISLAND
	setflag FLAG_WORLD_MAP_SEVEN_ISLAND
	release
	end

Debug_FlagsNotSetOverworldConfigMessage::
	message Debug_FlagsNotSetOverworldConfigMessage_Text
	goto Debug_MessageEnd

Debug_FlagsNotSetOverworldConfigMessage_Text:
	.string "Feature unavailable!\n"
	.string "Please define a usable flag in:\l"
	.string "'include/config/overworld.h'!$"

Debug_FlagsNotSetBattleConfigMessage::
	message Debug_FlagsNotSetBattleConfigMessage_Text
	goto Debug_MessageEnd

Debug_FlagsNotSetBattleConfigMessage_Text:
	.string "Feature unavailable!\n"
	.string "Please define a usable flag in:\l"
	.string "'include/config/battle.h'!$"

Debug_VarsNotSetBattleConfigMessage::
	message Debug_VarsNotSetBattleConfigMessage_Text
	goto Debug_MessageEnd

Debug_VarsNotSetBattleConfigMessage_Text:
	.string "Feature unavailable!\n"
	.string "Please define a usable var in:\l"
	.string "'include/config/battle.h'!$"

Debug_BoxFilledMessage::
	message Debug_BoxFilledMessage_Text
	goto Debug_MessageEnd

Debug_BoxFilledMessage_Text:
	.string "Storage boxes filled!$"

Debug_EventScript_CheckEVs::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, Debug_NoPokemon
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_EventScript_CheckEVs_End
	callnative Script_GetChosenMonOffensiveEVs
	msgbox Debug_EventScript_Text_OffensiveEVs, MSGBOX_DEFAULT
	callnative Script_GetChosenMonDefensiveEVs
	msgbox Debug_EventScript_Text_DefensiveEVs, MSGBOX_DEFAULT
Debug_EventScript_CheckEVs_End::
	releaseall
	end

Debug_EventScript_Text_OffensiveEVs:
	.string "ATK EVs: {STR_VAR_1}, SPATK EVs: {STR_VAR_2}, SPEED EVs: {STR_VAR_3}$"

Debug_EventScript_Text_DefensiveEVs:
	.string "HP EVs: {STR_VAR_1}, DEF EVs: {STR_VAR_2}, SPDEF EVs: {STR_VAR_3}$"

Debug_EventScript_CheckIVs::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, Debug_NoPokemon
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_EventScript_CheckIVs_End
	callnative Script_GetChosenMonOffensiveIVs
	msgbox Debug_EventScript_Text_OffensiveIVs, MSGBOX_DEFAULT
	callnative Script_GetChosenMonDefensiveIVs
	msgbox Debug_EventScript_Text_DefensiveIVs, MSGBOX_DEFAULT
Debug_EventScript_CheckIVs_End::
	releaseall
	end

Debug_EventScript_Text_OffensiveIVs:
	.string "ATK IVs: {STR_VAR_1}, SPATK IVs: {STR_VAR_2}, SPEED IVs: {STR_VAR_3}$"

Debug_EventScript_Text_DefensiveIVs:
	.string "HP IVs: {STR_VAR_1}, DEF IVs: {STR_VAR_2}, SPDEF IVs: {STR_VAR_3}$"

Debug_EventScript_Script_1::
	@ Unlock all HMs
	setflag FLAG_BADGE01_GET
	setflag FLAG_BADGE02_GET
	setflag FLAG_BADGE03_GET
	setflag FLAG_BADGE04_GET
	setflag FLAG_BADGE05_GET
	setflag FLAG_BADGE06_GET
	setflag FLAG_BADGE07_GET
	setflag FLAG_BADGE08_GET
	setflag FLAG_RECEIVED_HM_CUT
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
	setflag FLAG_GET_HEADBUTT
	giveitem ITEM_HM01
	giveitem ITEM_HM02
	giveitem ITEM_HM03
	giveitem ITEM_HM04
	giveitem ITEM_HM05
	giveitem ITEM_HM06
	giveitem ITEM_HM07
	giveitem ITEM_HM08
	msgbox Debug_Text_HMsUnlocked, MSGBOX_DEFAULT
	release
	end

Debug_Text_HMsUnlocked:
	.string "All HM flags set!$"

Debug_EventScript_Script_2::
	setflag FLAG_HIDE_COPYCAT_CLEFAIRY_DOLL
	setflag FLAG_HIDE_CERULEAN_GYM_TRAINERS
	setflag FLAG_HIDE_CERULEAN_CAPE_ROCKET
	setflag FLAG_HIDE_CERULEAN_GYM_ROCKET
	setflag FLAG_HIDDEN_ITEM_MACHINE_PART
	setflag FLAG_HIDE_ROUTE25_MISTY
	setflag FLAG_HIDE_ROUTE25_EUSINE
	setflag FLAG_HIDE_ROUTE25_SUICUNE
	setflag FLAG_HIDE_CELADON_EUSINE
	setflag FLAG_HIDE_SEAFOAM_GYMGUY
	setflag FLAG_HIDE_VIRIDIAN_BLUE
	setflag FLAG_HIDE_ROUTE14_EUSINE
	setflag FLAG_HIDE_ROUTE14_SUICUNE
	setflag FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU
	setflag FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU1
	setflag FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU2
	setflag FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU3
	setflag FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU4
	setflag FLAG_HIDE_ROUTE13_BOAT
	
	clearflag FLAG_BADGE09_GET
	clearflag FLAG_BADGE10_GET
	clearflag FLAG_BADGE11_GET
	clearflag FLAG_BADGE12_GET
	clearflag FLAG_BADGE13_GET
	clearflag FLAG_BADGE14_GET
	clearflag FLAG_BADGE15_GET
	clearflag FLAG_BADGE16_GET
	clearflag FLAG_GOT_VERMILION_HP_UP
	clearflag FLAG_KANTO_RADIO_GOT
	clearflag FLAG_HIDE_VERMILION_SNORLAX
	clearflag FLAG_HIDE_FAN_CLUB_CLEFAIRY_DOLL
	clearflag FLAG_FOUND_BOTH_VERMILION_GYM_SWITCHES
	clearflag FLAG_RETURNED_MACHINE_PART
	clearflag FLAG_GOT_TM_PSYCHIC
	clearflag FLAG_GOT_HOENN_STARTER
	clearflag FLAG_GOT_UP_GRADE
	clearflag FLAG_GOT_CLEANSE_TAG
	clearflag FLAG_ROUTE25_GOT_NUGGET
	clearflag FLAG_HIDE_POWER_PLANT_ENGINEER
	clearflag FLAG_HIDE_ZAPDOS
	clearflag FLAG_HIDE_ARTICUNO
	clearflag FLAG_HIDE_MOLTRES
	clearflag FLAG_GOT_TM_SLEEP_TALK
	clearflag FLAG_GOT_SUPER_ROD
	clearflag FLAG_HIDE_CINNABAR_BLUE
	clearflag FLAG_GOT_ROUTE2_NUGGET
	clearflag FLAG_GOT_VIRIDIAN_TM_DREAM_EATER
	clearflag FLAG_GOT_ROUTE_14_AERIAL_ACE
	clearflag FLAG_HIDE_PEWTER_ROOT_FOSSIL
	clearflag FLAG_HIDE_PEWTER_CLAW_FOSSIL
	clearflag FLAG_HIDE_MTMOON_SILVER
	clearflag FLAG_GOT_TM_STEEL_WING
	clearflag FLAG_HIDE_CERULEANCAVE_GUARD
	clearflag FLAG_HIDE_MTSILVER_RED
	clearflag FLAG_HIDE_MEWTWO
	clearflag FLAG_HIDE_LATIAS
	clearflag FLAG_HIDE_LATIOS
	clearflag FLAG_HIDE_GROUDON
	clearflag FLAG_HIDE_KYOGRE
	clearflag FLAG_HIDE_RAYQUAZA
	clearflag FLAG_HIDE_SEAFOAM_BLAINE

	clearflag FLAG_HIDE_CELADON_FALKNER
	clearflag FLAG_HIDE_VIRIDIAN_BUGSY
	clearflag FLAG_HIDE_DEPTSTORE_WHITNEY
	clearflag FLAG_HIDE_BELLCHIME_MORTY
	clearflag FLAG_HIDE_CAFE_JASMINE
	clearflag FLAG_HIDE_LAKE_PRYCE
	clearflag FLAG_HIDE_DEN_CLAIR


	setvar VAR_KANTO_ROCKET_STORY_STATE, 0
	setvar VAR_BILLS_GRANDPA, 0
	setvar VAR_VERMILION_CITY_STEVEN, 0
	setvar VAR_OAK_MT_SILVER_CALL, 0
	setvar VAR_VIRIDIAN_FOREST_PICHU, 0


	setvar VAR_FAN_CLUB_CLEFAIRY, 0
	setvar VAR_FAN_CLUB_GUY, 0
	setvar VAR_CLEFAIRY_DOLL_STATE, 0
	setvar VAR_NUM_BADGES, 8
	setvar VAR_VERMILION_CITY_STATE, 1

	setvar VAR_KANTO_SAFARI_ZONE_PROGRESS, 0 
	clearflag FLAG_IN_KANTO_SAFARI_ZONE 
	clearflag FLAG_IS_KANTO_CHAMPION 
	setvar VAR_BAOBA_QUEST_STATE, 0 
	setvar VAR_CINNABAR_ISLAND_STATE, 0 
	setvar VAR_MT_SILVER_STATE, 0, 
	setvar VAR_PALLETTOWN_LABSTATE, 0 
	clearflag FLAG_HIDE_LEAGUE_BLACKBELT 
	
	setflag FLAG_HIDE_DOJO_FALKNER
	setflag FLAG_HIDE_DOJO_BUGSY
	setflag FLAG_HIDE_DOJO_WHITNEY
	setflag FLAG_HIDE_DOJO_MORTY
	setflag FLAG_HIDE_DOJO_CHUCK
	setflag FLAG_HIDE_DOJO_JASMINE
	setflag FLAG_HIDE_DOJO_PRYCE
	setflag FLAG_HIDE_DOJO_CLAIR
	setflag FLAG_HIDE_DOJO_BROCK
	setflag FLAG_HIDE_DOJO_MISTY
	setflag FLAG_HIDE_DOJO_SURGE
	setflag FLAG_HIDE_DOJO_ERIKA
	setflag FLAG_HIDE_DOJO_JANINE
	setflag FLAG_HIDE_DOJO_SABRINA
	setflag FLAG_HIDE_DOJO_BLAINE
	setflag FLAG_HIDE_DOJO_BLUE
	release
	end

Debug_EventScript_Script_3::
	additem ITEM_PASS
	setflag FLAG_RETURNED_MACHINE_PART
	release
	end

Debug_EventScript_Script_4::
	special InitRoamer
	givemon SPECIES_RATTATA_ALOLA 5
	givemon SPECIES_RATICATE_ALOLA 5
	givemon SPECIES_MEOWTH_ALOLA 5
	givemon SPECIES_PERSIAN_ALOLA 5
	givemon SPECIES_GEODUDE_ALOLA 5
	givemon SPECIES_GRAVELER_ALOLA 5
	givemon SPECIES_GOLEM_ALOLA 5
	givemon SPECIES_SANDSHREW_ALOLA 5
	givemon SPECIES_SANDSLASH_ALOLA 5
	givemon SPECIES_VULPIX_ALOLA 5
	givemon SPECIES_NINETALES_ALOLA 5
	givemon SPECIES_GRIMER_ALOLA 5
	givemon SPECIES_MUK_ALOLA 5
	givemon SPECIES_EXEGGUTOR_ALOLA 5
	givemon SPECIES_MAROWAK_ALOLA 5
	givemon SPECIES_DIGLETT_ALOLA 5
	givemon SPECIES_DUGTRIO_ALOLA 5
	release
	end

Debug_EventScript_Script_5::
	special InitKantoRoamers
	givemon SPECIES_RAICHU_ALOLA 5
	release
	end

Debug_EventScript_Script_6_String_0:
	.string "Number of {STR_VAR_1} Pokemeon:  {STR_VAR_2}\n(not including cross gen evos)$"
	
Debug_EventScript_Script_6_String_Alolan:
	.string "Alolan$"

Debug_EventScript_Script_6_String_Galarian:
	.string "Galarian$"

Debug_EventScript_Script_6_String_Hisuian:
	.string "Hisuian$"

Debug_EventScript_Script_6_String_Paldean:
	.string "Paldean$"

Debug_EventScript_Script_6::
	lockall
	setvar VAR_FRONTIER_FACILITY, FRONTIER_FACILITY_TOWER
	setvar VAR_FRONTIER_BATTLE_MODE, FRONTIER_MODE_SINGLES
	frontier_settrainers
	setvar VAR_TRAINER_BATTLE_OPPONENT_A, FRONTIER_TRAINER_LEADER_BROCK_HNS
	special HealPlayerParty
	dofacilitytrainerbattle FACILITY_BATTLE_TOWER
	waitstate
	special HealPlayerParty
	releaseall
	end

Debug_EventScript_Script_7::
  specialvar VAR_RESULT, GetAlolaCatchProgress
	bufferstring STR_VAR_1, Debug_EventScript_Script_6_String_Alolan
	buffernumberstring STR_VAR_2, VAR_RESULT
	msgbox Debug_EventScript_Script_6_String_0, MSGBOX_DEFAULT

	specialvar VAR_RESULT, GetGalarCatchProgress
	bufferstring STR_VAR_1, Debug_EventScript_Script_6_String_Galarian
	buffernumberstring STR_VAR_2, VAR_RESULT
	msgbox Debug_EventScript_Script_6_String_0, MSGBOX_DEFAULT

	specialvar VAR_RESULT, GetHisuiCatchProgress
	bufferstring STR_VAR_1, Debug_EventScript_Script_6_String_Hisuian
	buffernumberstring STR_VAR_2, VAR_RESULT
	msgbox Debug_EventScript_Script_6_String_0, MSGBOX_DEFAULT

	specialvar VAR_RESULT, GetPaldeaCatchProgress
	bufferstring STR_VAR_1, Debug_EventScript_Script_6_String_Paldean
	buffernumberstring STR_VAR_2, VAR_RESULT
	msgbox Debug_EventScript_Script_6_String_0, MSGBOX_DEFAULT

	release
	end

Debug_EventScript_Script_8::
	helpwindow HELP_DEMO_WINDOW
	release
	end

Debug_EventScript_Lance_Multi::
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	waitstate
	goto_if_ne VAR_RESULT, 0, Debug_EventScript_DoLanceMultiBattle
	special LoadPlayerParty
	release
	end

Debug_EventScript_DoLanceMultiBattle::
	multi_2_vs_2 TRAINER_ARIANA_1_HNS, Debug_Text_ArianaDefeat, TRAINER_GRUNT_23_HNS, Debug_Text_Grunt23Defeat, PARTNER_LANCE_HNS
	switch VAR_RESULT
	case 1, Debug_EventScript_LanceMultiWin
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	waitstate

Debug_EventScript_LanceMultiWin::
	msgbox Debug_Text_LanceMultiVictory, MSGBOX_DEFAULT
	release
	end

Debug_Text_ArianaDefeat:
	.string "You haven't seen the last of me!$"

Debug_Text_Grunt23Defeat:
	.string "I won't accept this!$"

Debug_Text_LanceMultiVictory:
	.string "Lance multi battle complete!$"

Debug_EventScript_Silver_Multi::
	special SavePlayerParty
	fadescreen FADE_TO_BLACK
	special ChooseHalfPartyForBattle
	waitstate
	goto_if_ne VAR_RESULT, 0, Debug_EventScript_PickSilverPartner
	special LoadPlayerParty
	release
	end

Debug_EventScript_PickSilverPartner::
	switch VAR_STARTER_MON
	case 0, Debug_EventScript_DoSilverMulti_Typhlosion
	case 1, Debug_EventScript_DoSilverMulti_Feraligatr
	case 2, Debug_EventScript_DoSilverMulti_Meganium
	goto Debug_EventScript_DoSilverMulti_Typhlosion

Debug_EventScript_DoSilverMulti_Typhlosion::
	multi_2_vs_2 TRAINER_LANCE_3_HNS, Debug_Text_Lance3Defeat, TRAINER_CLAIR_3_HNS, Debug_Text_Clair3Defeat, PARTNER_SILVER_TYPHLOSION_HNS
	goto Debug_EventScript_SilverMultiResult

Debug_EventScript_DoSilverMulti_Feraligatr::
	multi_2_vs_2 TRAINER_LANCE_3_HNS, Debug_Text_Lance3Defeat, TRAINER_CLAIR_3_HNS, Debug_Text_Clair3Defeat, PARTNER_SILVER_FERALIGATR_HNS
	goto Debug_EventScript_SilverMultiResult

Debug_EventScript_DoSilverMulti_Meganium::
	multi_2_vs_2 TRAINER_LANCE_3_HNS, Debug_Text_Lance3Defeat, TRAINER_CLAIR_3_HNS, Debug_Text_Clair3Defeat, PARTNER_SILVER_MEGANIUM_HNS
	goto Debug_EventScript_SilverMultiResult

Debug_EventScript_SilverMultiResult::
	switch VAR_RESULT
	case 1, Debug_EventScript_SilverMultiWin
	fadescreen FADE_TO_BLACK
	special SetCB2WhiteOut
	waitstate

Debug_EventScript_SilverMultiWin::
	msgbox Debug_Text_SilverMultiVictory, MSGBOX_DEFAULT
	release
	end

Debug_Text_SilverMultiVictory:
	.string "Silver multi battle complete!$"

Debug_Text_Lance3Defeat:
	.string "You haven't seen the last of me!$"

Debug_Text_Clair3Defeat:
	.string "I won't accept this!$"

Debug_CheckSaveBlock::
	callnative CheckSaveBlock1Size
	msgbox Debug_SaveBlock1Size, MSGBOX_DEFAULT
	callnative CheckSaveBlock2Size
	msgbox Debug_SaveBlock2Size, MSGBOX_DEFAULT
	callnative CheckSaveBlock3Size
	msgbox Debug_SaveBlock3Size, MSGBOX_DEFAULT
	callnative CheckPokemonStorageSize
	msgbox Debug_PokemonStorageSize, MSGBOX_DEFAULT
	release
	end

Debug_SaveBlock1Size::
	.string "SaveBlock1 size: {STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Free space: {STR_VAR_3}b.$"

Debug_SaveBlock2Size::
	.string "SaveBlock2 size: {STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Free space: {STR_VAR_3}b.$"

Debug_SaveBlock3Size::
	.string "SaveBlock3 size: {STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Free space: {STR_VAR_3}b.$"

Debug_PokemonStorageSize::
	.string "{PKMN}Storage size: {STR_VAR_1}b/{STR_VAR_2}b.\n"
	.string "Free space: {STR_VAR_3}b.$"

Debug_CheckROMSpace::
	callnative CheckROMSize
	msgbox Debug_ROMSize, MSGBOX_DEFAULT
	release
	end

Debug_ROMSize::
	.string "ROM size: {STR_VAR_1}MB/32MB.\n"
	.string "Free space: {STR_VAR_2}MB.$"

Debug_HatchAnEgg::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, Debug_NoPokemon
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_HatchAnEgg_End
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_ne VAR_RESULT, SPECIES_EGG, DebugScript_HatchAnEgg_CantForceHatch
	special EggHatch
	waitstate
Debug_HatchAnEgg_End::
	releaseall
	end

Debug_NoPokemon::
	msgbox DebugScript_Text_EmptyParty, MSGBOX_DEFAULT
	releaseall
	end

DebugScript_HatchAnEgg_CantForceHatch::
	msgbox DebugScript_HatchAnEgg_Text_NotAnEgg, MSGBOX_DEFAULT
	releaseall
	end

DebugScript_Text_EmptyParty::
	.string "You have no Pokémon nor Eggs.$"

DebugScript_HatchAnEgg_Text_NotAnEgg::
	.string "That's not a Pokémon Egg.$"

DebugScript_ZeroDaycareMons::
	msgbox DebugText_DaycareNoPokemon, MSGBOX_DEFAULT
	releaseall
	end

DebugScript_OneDaycareMons::
	msgbox DebugText_DaycareOnePokemon, MSGBOX_DEFAULT
	releaseall
	end

DebugScript_DaycareMonsNotCompatible::
	msgbox DebugText_DaycarePokemonNotCompatible, MSGBOX_DEFAULT
	releaseall
	end

DebugText_DaycareNoPokemon:
	.string "You have no Pokémon at Daycare.$"

DebugText_DaycareOnePokemon:
	.string "You have only one Pokémon at Daycare.$"

DebugText_DaycarePokemonNotCompatible:
	.string "Your Pokémon at Daycare can't\nhave babies together!$"

Debug_ShowExpansionVersion::
	callnative BufferExpansionVersion
	msgbox Debug_ExpansionVersion, MSGBOX_DEFAULT
	release
	end

Debug_ExpansionVersion:
	.string "pokeemerald-expansion {STR_VAR_1}$"

Debug_Follower_NPC_Not_Enabled::
	msgbox Debug_Enable_To_Use_Follower_NPCs, MSGBOX_DEFAULT
	release
	end

Debug_Enable_To_Use_Follower_NPCs:
	.string "Feature unavailable.\nSet FNPC_ENABLE_NPC_FOLLOWERS to\lTRUE in 'include/config/follower_npc.h'.$"

Debug_Follower_NPC_Event_Script::
	lock
	facefollowernpc
	msgbox Debug_Follower_NPC_Test_Message, MSGBOX_DEFAULT
	releaseall
	end

Debug_Follower_NPC_Test_Message:
	.string "This is a Follower NPC test.$"

Debug_EventScript_Steven_Multi::
	call MossdeepCity_SpaceCenter_2F_EventScript_ChoosePartyForMultiBattle
	release
	end

Debug_EventScript_WallyTutorial::
	special SavePlayerParty
	special LoadWallyZigzagoon
	special StartWallyTutorialBattle
	waitstate
	special LoadPlayerParty
	release
	end

Debug_BerryPestsDisabled::
	msgbox DebugText_BerryPestsDisabled, MSGBOX_DEFAULT
	release
	end

DebugText_BerryPestsDisabled:
	.string "OW_BERRY_PESTS is disabled.\n"
	.string "Unable to force pests onto berry trees.$"

Debug_BerryWeedsDisabled::
	msgbox DebugText_BerryWeedsDisabled, MSGBOX_DEFAULT
	release
	end

DebugText_BerryWeedsDisabled:
	.string "OW_BERRY_WEEDS is disabled.\n"
	.string "Unable to force weeds onto berry trees.$"

Debug_EventScript_InflictStatus1::
	lockall
	getpartysize
	goto_if_eq VAR_RESULT, 0, Debug_NoPokemon
	dynmultipush Debug_EventScript_InflictStatus1_Text_Single, 0
	dynmultipush Debug_EventScript_InflictStatus1_Text_PartyWide, 1
	dynmultipush Debug_EventScript_InflictStatus1_Text_Close, 2
	dynmultistack 0, 0, FALSE, 3 FALSE, 0, NULL
	switch VAR_RESULT
	case 0, Debug_EventScript_InflictStatus1_Single
	case 1, Debug_EventScript_InflictStatus1_Party
	case 2, Debug_EventScript_InflictStatus1_Close
Debug_EventScript_InflictStatus1_Close:
	releaseall
	end

Debug_EventScript_InflictStatus1_Single:
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_EventScript_InflictStatus1_Close
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, Debug_EventScript_InflictStatus1_Close
	dynmultipush Debug_EventScript_InflictStatus1_Text_Poison, 0
	dynmultipush Debug_EventScript_InflictStatus1_Text_Paralysis, 1
	dynmultipush Debug_EventScript_InflictStatus1_Text_Sleep, 2
	dynmultipush Debug_EventScript_InflictStatus1_Text_Burn, 3
	dynmultipush Debug_EventScript_InflictStatus1_Text_Freeze, 4
	dynmultipush Debug_EventScript_InflictStatus1_Text_Frostbite, 5
	dynmultipush Debug_EventScript_InflictStatus1_Text_Close, 6
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	switch VAR_RESULT
	case 0, Debug_EventScript_InflictStatus1_Single_Poison
	case 1, Debug_EventScript_InflictStatus1_Single_Paralysis
	case 2, Debug_EventScript_InflictStatus1_Single_Sleep
	case 3, Debug_EventScript_InflictStatus1_Single_Burn
	case 4, Debug_EventScript_InflictStatus1_Single_Freeze
	case 5, Debug_EventScript_InflictStatus1_Single_Frostbite
	case 6, Debug_EventScript_InflictStatus1_Close
	case MULTI_B_PRESSED, Debug_EventScript_InflictStatus1_Close
	releaseall
	end

Debug_EventScript_KoPokemon::
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_EventScript_InflictStatus1_Close
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, Debug_EventScript_InflictStatus1_Close
	setko VAR_0x8004
	releaseall
	end

Debug_EventScript_SetHiddenNature::
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Debug_EventScript_InflictStatus1_Close
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, Debug_EventScript_InflictStatus1_Close
	dynmultipush Debug_EventScript_ChangeNature_Text_Hardy, 0
	dynmultipush Debug_EventScript_ChangeNature_Text_Lonely, 1
	dynmultipush Debug_EventScript_ChangeNature_Text_Brave, 2
	dynmultipush Debug_EventScript_ChangeNature_Text_Adamant, 3
	dynmultipush Debug_EventScript_ChangeNature_Text_Naughty, 4
	dynmultipush Debug_EventScript_ChangeNature_Text_Bold, 5
	dynmultipush Debug_EventScript_ChangeNature_Text_Docile, 6
	dynmultipush Debug_EventScript_ChangeNature_Text_Relaxed, 7
	dynmultipush Debug_EventScript_ChangeNature_Text_Impish, 8
	dynmultipush Debug_EventScript_ChangeNature_Text_Lax, 9
	dynmultipush Debug_EventScript_ChangeNature_Text_Timid, 10
	dynmultipush Debug_EventScript_ChangeNature_Text_Hasty, 11
	dynmultipush Debug_EventScript_ChangeNature_Text_Serious, 12
	dynmultipush Debug_EventScript_ChangeNature_Text_Jolly, 13
	dynmultipush Debug_EventScript_ChangeNature_Text_Naive, 14
	dynmultipush Debug_EventScript_ChangeNature_Text_Modest, 15
	dynmultipush Debug_EventScript_ChangeNature_Text_Mild, 16
	dynmultipush Debug_EventScript_ChangeNature_Text_Quiet, 17
	dynmultipush Debug_EventScript_ChangeNature_Text_Bashful, 18
	dynmultipush Debug_EventScript_ChangeNature_Text_Rash, 19
	dynmultipush Debug_EventScript_ChangeNature_Text_Calm, 20
	dynmultipush Debug_EventScript_ChangeNature_Text_Gentle, 21
	dynmultipush Debug_EventScript_ChangeNature_Text_Sassy, 22
	dynmultipush Debug_EventScript_ChangeNature_Text_Careful, 23
	dynmultipush Debug_EventScript_ChangeNature_Text_Quirky, 24
	dynmultistack 0, 0, TRUE, 7, FALSE, 0, NULL
	switch VAR_RESULT
	case MULTI_B_PRESSED, Debug_EventScript_InflictStatus1_Close
	special SetHiddenNature
	releaseall
	end

Debug_EventScript_SetAbility::
	special ChoosePartyMon
	waitstate
	callnative DebugNative_GetAbilityNames
	dynmultipush gStringVar1, 0
	dynmultipush gStringVar2, 1
	dynmultipush gStringVar3, 2
	dynmultistack 0, 0, FALSE, 3 FALSE, 0, NULL
	switch VAR_RESULT
	case MULTI_B_PRESSED, Debug_EventScript_SetAbilityClose
	special SetAbility
Debug_EventScript_SetAbilityClose:
	releaseall
	end

Debug_EventScript_SetFriendship::
	special ChoosePartyMon
	waitstate
	callnative DebugNative_Party_SetFriendship
	releaseall
	end

Debug_EventScript_GivePokerus::
	special ChoosePartyMon
	waitstate
	callnative DebugNative_Party_SetPokerus
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Poison:
	setstatus1 STATUS1_POISON, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Paralysis:
	setstatus1 STATUS1_PARALYSIS, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Sleep:
	setstatus1 STATUS1_SLEEP, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Burn:
	setstatus1 STATUS1_BURN, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Freeze:
	setstatus1 STATUS1_FREEZE, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Single_Frostbite:
	setstatus1 STATUS1_FROSTBITE, VAR_0x8004
	releaseall
	end

Debug_EventScript_InflictStatus1_Party:
	dynmultipush Debug_EventScript_InflictStatus1_Text_Poison, 0
	dynmultipush Debug_EventScript_InflictStatus1_Text_Paralysis, 1
	dynmultipush Debug_EventScript_InflictStatus1_Text_Sleep, 2
	dynmultipush Debug_EventScript_InflictStatus1_Text_Burn, 3
	dynmultipush Debug_EventScript_InflictStatus1_Text_Freeze, 4
	dynmultipush Debug_EventScript_InflictStatus1_Text_Frostbite, 5
	dynmultipush Debug_EventScript_InflictStatus1_Text_Close, 6
	dynmultistack 0, 0, FALSE, 7, FALSE, 0, NULL
	switch VAR_RESULT
	case 0, Debug_EventScript_InflictStatus1_Party_Poison
	case 1, Debug_EventScript_InflictStatus1_Party_Paralysis
	case 2, Debug_EventScript_InflictStatus1_Party_Sleep
	case 3, Debug_EventScript_InflictStatus1_Party_Burn
	case 4, Debug_EventScript_InflictStatus1_Party_Freeze
	case 5, Debug_EventScript_InflictStatus1_Party_Frostbite
	case 6, Debug_EventScript_InflictStatus1_Close
	case MULTI_B_PRESSED, Debug_EventScript_InflictStatus1_Close
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Poison:
	setstatus1 STATUS1_POISON, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Paralysis:
	setstatus1 STATUS1_PARALYSIS, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Sleep:
	setstatus1 STATUS1_SLEEP, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Burn:
	setstatus1 STATUS1_BURN, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Freeze:
	setstatus1 STATUS1_FREEZE, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Party_Frostbite:
	setstatus1 STATUS1_FROSTBITE, PARTY_SIZE
	releaseall
	end

Debug_EventScript_InflictStatus1_Text_Single:
	.string "Single$"

Debug_EventScript_InflictStatus1_Text_PartyWide:
	.string "Party-wide$"

Debug_EventScript_InflictStatus1_Text_Close:
	.string "Close$"

Debug_EventScript_InflictStatus1_Text_Poison:
	.string "Poison$"

Debug_EventScript_InflictStatus1_Text_Paralysis:
	.string "Paralysis$"

Debug_EventScript_InflictStatus1_Text_Sleep:
	.string "Sleep$"

Debug_EventScript_InflictStatus1_Text_Burn:
	.string "Burn$"

Debug_EventScript_InflictStatus1_Text_Freeze:
	.string "Freeze$"

Debug_EventScript_InflictStatus1_Text_Frostbite:
	.string "Frostbite$"

Debug_EventScript_InflictStatus1_Text_KO:
	.string "KO$"

Debug_EventScript_ChangeNature_Text_Hardy:
	.string "Hardy$"
Debug_EventScript_ChangeNature_Text_Lonely:
	.string "Lonely$"
Debug_EventScript_ChangeNature_Text_Brave:
	.string "Brave$"
Debug_EventScript_ChangeNature_Text_Adamant:
	.string "Adamant$"
Debug_EventScript_ChangeNature_Text_Naughty:
	.string "Naughty$"
Debug_EventScript_ChangeNature_Text_Bold:
	.string "Bold$"
Debug_EventScript_ChangeNature_Text_Docile:
	.string "Docile$"
Debug_EventScript_ChangeNature_Text_Relaxed:
	.string "Relaxed$"
Debug_EventScript_ChangeNature_Text_Impish:
	.string "Impish$"
Debug_EventScript_ChangeNature_Text_Lax:
	.string "Lax$"
Debug_EventScript_ChangeNature_Text_Timid:
	.string "Timid$"
Debug_EventScript_ChangeNature_Text_Hasty:
	.string "Hasty$"
Debug_EventScript_ChangeNature_Text_Serious:
	.string "Serious$"
Debug_EventScript_ChangeNature_Text_Jolly:
	.string "Jolly$"
Debug_EventScript_ChangeNature_Text_Naive:
	.string "Naive$"
Debug_EventScript_ChangeNature_Text_Modest:
	.string "Modest$"
Debug_EventScript_ChangeNature_Text_Mild:
	.string "Mild$"
Debug_EventScript_ChangeNature_Text_Quiet:
	.string "Quiet$"
Debug_EventScript_ChangeNature_Text_Bashful:
	.string "Bashful$"
Debug_EventScript_ChangeNature_Text_Rash:
	.string "Rash$"
Debug_EventScript_ChangeNature_Text_Calm:
	.string "Calm$"
Debug_EventScript_ChangeNature_Text_Gentle:
	.string "Gentle$"
Debug_EventScript_ChangeNature_Text_Sassy:
	.string "Sassy$"
Debug_EventScript_ChangeNature_Text_Careful:
	.string "Careful$"
Debug_EventScript_ChangeNature_Text_Quirky:
	.string "Quirky$"

Debug_EventScript_EWRAMCounters::
	callnative CheckEWRAMCounters
	msgbox Debug_EventScript_EWRAMCounters_Text, MSGBOX_DEFAULT
	release
	end

Debug_EventScript_EWRAMCounters_Text::
	.string "Follower Steps: {STR_VAR_1}.\n"
	.string "Fishing Chain: {STR_VAR_2}.$"

Debug_EventScript_FontTest_Text_1::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Angel Adept Blind Bodice Clique\n"
	.string "Coast Dunce Docile Enact Eosin\l"
	.string "Furlong Focal Gnome Gondola Human\l"
	.string "Hoist Inlet Iodine Justin Jocose\l"
	.string "Knoll Koala Linden Loads Milliner\l"
	.string "Modal Number Nodule Onset Oddball\l"
	.string "Pneumo Poncho Quanta Qophs Rhone\l"
	.string "Roman Snout Sodium Tundra Tocsin\l"
	.string "Uncle Udder Vulcan Vocal Whale\l"
	.string "Woman Xmas Xenon Yunnan Young\l"
	.string "Zloty Zodiac.$"

Debug_EventScript_FontTest_Text_2::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Angel angel adept for the nuance loads\n"
	.string "of the arena cocoa and quaalude. Blind\l"
	.string "blind bodice for the submit oboe of the\l"
	.string "club snob and abbot. Clique clique\l"
	.string "coast for the pouch loco of the franc\l"
	.string "assoc and accede. Dunce dunce docile\l"
	.string "for the loudness mastodon of the\l"
	.string "loud statehood and huddle.$"

Debug_EventScript_FontTest_Text_3::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Enact enact eosin for the quench coed\n"
	.string "of the pique canoe and bleep. Furlong\l"
	.string "furlong focal for the genuflect\l"
	.string "profound of the motif aloof and offers.\l"
	.string "Gnome gnome gondola for the impugn\l"
	.string "logos of the unplug analog and smuggle.\l"
	.string "Human human hoist for the buddhist\l"
	.string "alcohol of the riyadh caliph and\l"
	.string "bathhouse.$"

Debug_EventScript_FontTest_Text_4::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Inlet inlet iodine for the quince\n"
	.string "champion of the ennui scampi and shiite.\l"
	.string "Justin justin jocose for the djibouti\l"
	.string "sojourn of the oranj raj and hajjis.\l"
	.string "Knoll knoll koala for the banknote\l"
	.string "lookout of the dybbuk outlook and\l"
	.string "trekked. Linden linden loads for the\l"
	.string "ulna monolog of the consul menthol and\l"
	.string "shallot.$"

Debug_EventScript_FontTest_Text_5::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Milliner milliner modal for the alumna\n"
	.string "solomon of the album custom and summon.\l"
	.string "Number number nodule for the unmade\l"
	.string "economic of the shotgun bison and\l"
	.string "tunnel. Onset onset oddball for the\l"
	.string "abandon podium of the antiquo tempo\l"
	.string "and moonlit. Pneumo pneumo poncho for\l"
	.string "the dauphin opossum of the holdup\l"
	.string "bishop and supplies.$"

Debug_EventScript_FontTest_Text_6::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Quanta quanta qophs for the inquest\n"
	.string "sheqel of the cinq coq and suqqu. Rhone\l"
	.string "rhone roman for the burnt porous of the\l"
	.string "lemur clamor and carrot. Snout snout\l"
	.string "sodium for the ensnare bosom of the\l"
	.string "genus pathos and missing. Tundra\l"
	.string "tundra tocsin for the nutmeg isotope\l"
	.string "of the peasant ingot and ottoman.$"

Debug_EventScript_FontTest_Text_7::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Uncle uncle udder for the dunes cloud\n"
	.string "of the hindu thou and continuum. Vulcan\l"
	.string "vulcan vocal for the alluvial ovoid of\l"
	.string "the yugoslav chekhov and revved. Whale\l"
	.string "whale woman for the meanwhile blowout\l"
	.string "of the forepaw meadow and glowworm.\l"
	.string "Xmas xmas xenon for the bauxite\l"
	.string "doxology of the tableaux equinox and\l"
	.string "exxon.$"

Debug_EventScript_FontTest_Text_8::
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "Yunnan yunnan young for the dynamo\n"
	.string "coyote of the obloquy employ and\l"
	.string "sayyid. Zloty zloty zodiac for the gizmo\l"
	.string "ozone of the franz laissez and buzzing.$"


Debug_EventScript_FontTest_Text_9::                 @ Special thanks to Nintendo for this nice pangram to test other glyphs
	.string "{FONT_SMALL_NARROWER}"                 @ Edit this to test your font
	.string "42 × 138 = 5796.\n"
	.string "Mr Jock, TV quiz PhD: bags 20% fewer\l"
	.string "lynx at a café; voilà, they're “worth”\l"
	.string "♂1/♀1 = ¥1. That's 10 + 9 - 8 = 11\l"
	.string "Nintendo GBA can connect to a Nintendo\l"
	.string "GameCube console! He claimed-though I don't\l"
	.string "believe him-to have done so in an eyes-shut\l"
	.string "state…?$"

Debug_PrintFontTest::
	msgbox Debug_EventScript_FontTest_Text_1, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_2, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_3, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_4, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_5, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_6, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_7, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_8, MSGBOX_DEFAULT
	msgbox Debug_EventScript_FontTest_Text_9, MSGBOX_DEFAULT
	releaseall
	end

Debug_EventScript_FontTest::
	lockall
	goto Debug_PrintFontTest
@	goto_if_eq VAR_RESULT, 0, Debug_NoPokemon
@	dynmultipush Debug_EventScript_InflictStatus1_Text_Single, 0
@	dynmultipush Debug_EventScript_InflictStatus1_Text_PartyWide, 1
@	dynmultipush Debug_EventScript_InflictStatus1_Text_Close, 2
@	dynmultistack 0, 0, FALSE, 3 FALSE, 0, NULL
@	switch VAR_RESULT
@	case 0, Debug_EventScript_InflictStatus1_Single
@	case 1, Debug_EventScript_InflictStatus1_Party
@	case 2, Debug_EventScript_InflictStatus1_Close
@Debug_EventScript_InflictStatus1_Close:
@	releaseall
@	end

Debug_EventScript_TellTheTime::
	callnative DebugMenu_CalculateTime
	msgbox Debug_EventScript_TellTheTime_Text_0, MSGBOX_DEFAULT
	waitmessage
	closemessage
	end

Debug_EventScript_PrintTimeOfDay::
	callnative DebugMenu_CalculateTimeOfDay
	msgbox DebugEventScript_PrintWeekday_Text_0, MSGBOX_DEFAULT
	waitmessage
	closemessage
	end

Debug_EventScript_FakeRTCNotEnabled::
	msgbox Debug_EventScript_FakeRTCNotEnabled_Text_0, MSGBOX_DEFAULT
	waitmessage
	closemessage
	return

Debug_EventScript_FakeRTCNotEnabled_Text_0:
	.string "You currently do not have Fake RTC\nenabled. Please enable it in include/\lconfig/overworld.h$"


Debug_EventScript_TellTheTime_Text_0:
	.string "Time and date:\n"
	.string "{STR_VAR_1}, {STR_VAR_2}:{STR_VAR_3}$"

DebugEventScript_PrintWeekday_Text_0:
	.string "Time of day: {STR_VAR_1}$"

@ Mom Savings debug: enables saving + force-deposits 50000
Debug_MomSavings_BigDeposit::
	lockall
	special Special_MomEnsureInitialized
	special Special_MomEnableSaving
	setvar VAR_0x8000, 50000
	special Special_MomDeposit
	special Special_MomGetBalance
	msgbox Debug_MomSavings_Text_Deposited, MSGBOX_DEFAULT
	releaseall
	end

Debug_MomSavings_Text_Deposited:
	.string "Mom savings enabled.\n"
	.string "Deposited ¥50000.\p"
	.string "Balance: {STR_VAR_2}\n"
	.string "Walk outside for gift call.$"
