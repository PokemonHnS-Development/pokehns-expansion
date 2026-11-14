@ Story step 1: New Bark Town to the aide's Poke Balls (starter: Cyndaquil).
@ Each block mirrors the state ops of the ROM script named in its comment, in story order;
@ text, movement and sound are left out. Paths are pokehns-en/data/maps/<map>/scripts.inc.

@ Bedroom wall clock (NewBarkTown_PlayersHouse_2F_hns:19-35 -> data/scripts/players_house.inc:114
@ special StartWallClock; the clock screen ends in RtcInitLocalTimeOffset + InitTimeBasedEvents,
@ src/wallclock.c:853-857, src/clock.c:97-101). 10:00 is the clock screen's default.
	initclock 10, 0
	callnative InitTimeBasedEvents
	setvar VAR_NEWBARK_TOWN_STATE, 1
	setflag FLAG_SET_WALL_CLOCK

@ Mom: Pokegear and running shoes (NewBarkTown_PlayersHouse_1F_hns:215-268)
	setflag FLAG_SYS_POKENAV_GET
	setflag FLAG_HAS_MATCH_CALL
	setflag FLAG_RECEIVED_POKENAV
	setflag FLAG_ADDED_MATCH_CALL_TO_POKENAV
	setflag FLAG_REGISTER_RIVAL_POKENAV
	setflag FLAG_RECEIVED_RUNNING_SHOES
	setflag FLAG_SYS_B_DASH
	setvar VAR_NEWBARK_TOWN_STATE, 2
	setvar VAR_NEWBARKTOWN_LABSTATE, 0
	setflag FLAG_HIDE_LAB_POLICEMAN
	setflag FLAG_VISITED_NEWBARK_TOWN
@ New Bark Town on transition at state 2 shows the rival at the lab window (NewBarkTown_hns OnTransition)
	clearflag FLAG_HIDE_SILVER_NEWBARKTOWN

@ Elm's lab: the starter (NewBarkTown_Lab_hns ElmChoosePokemon, CyndaquilBall_Choice, ChoseStarter).
@ removeobject on the chosen ball sets its object flag (map.json: FLAG_HIDE_CYNDAQUILBALL).
	setvar VAR_NEWBARKTOWN_LABSTATE, 1
	setvar VAR_STARTER_MON, 1
	setflag FLAG_HIDE_CYNDAQUILBALL
	setflag FLAG_SYS_POKEMON_GET
@ Elm sends the player to Mr. Pokemon (NewBarkTown_Lab_EventScript_MrPokemon)
	setvar VAR_NEWBARKTOWN_LABSTATE, 2
	setvar VAR_NEWBARK_TOWN_STATE, 3
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
	clearflag FLAG_RECEIVED_FIRST_BALLS
	clearflag FLAG_RECEIVED_FIRST_POTION
@ The aide's Potion (NewBarkTown_Lab_EventScript_TriggerAideGivePotion)
	additem ITEM_POTION
	setflag FLAG_RECEIVED_FIRST_POTION
	setvar VAR_NEWBARKTOWN_LABSTATE, 3

@ Cherrygrove: the guide gent's tour (CherrygroveCity_hns TriggerGent_*, GentTour)
	setflag FLAG_VISITED_CHERRYGROVE_CITY
	clearflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
	setflag FLAG_HIDE_GUIDE_GENT_CHERRYGROVE
	setvar VAR_CHERRYGROVE_CITY_STATE, 1

@ Mr. Pokemon's house: the Mystery Egg, Oak gives the Pokedex (Route30_MrPokemonsHouse_hns:9-35).
@ Not randomized, so no National Dex here (MrPokemonHouse_EventScript_GiveNatDexRandomizer).
	additem ITEM_MYSTERY_EGG
	setflag FLAG_DELIVERED_EGG
	clearflag FLAG_HIDE_MRPOKEMON
	setvar VAR_NEWBARKTOWN_LABSTATE, 4
	setflag FLAG_HIDE_SILVER_NEWBARKTOWN
	setflag FLAG_SYS_POKEDEX_GET
	clearflag FLAG_HIDE_LAB_POLICEMAN
	setvar VAR_CHERRYGROVE_CITY_STATE, 2
	setrespawn HEAL_LOCATION_CHERRYGROVE_CITY_HNS
	clearflag FLAG_HIDE_SILVER_CHERRYGROVE
	setflag FLAG_HIDE_GUIDE_GENT_CHERRYGROVE
	clearflag FLAG_HIDE_CHERRYGROVE_GUIDE_GENT_HOUSE
@ Route 30: Elm's "disaster" call (Route30_hns OnFrame at CHERRYGROVE 2 -> 3)
	setvar VAR_CHERRYGROVE_CITY_STATE, 3
@ Cherrygrove: first rival battle (CherryGroveCity_Silver_AfterBattle)
	setflag FLAG_HIDE_SILVER_CHERRYGROVE
	setvar VAR_CHERRYGROVE_CITY_STATE, 4

@ Elm's lab: the police scene (NewBarkTown_Lab_EventScript_PoliceEpisode / PoliceYes). The rival
@ stole the ball that beats the player's starter: STARTER_MON 1 hides Totodile. The rival's name
@ stays the default SILVER (src/naming_screen.c:2268, src/new_game.c:308).
	setflag FLAG_HIDE_TOTODILEBALL
	setflag FLAG_HIDE_LAB_POLICEMAN
	setvar VAR_NEWBARKTOWN_LABSTATE, 5
	setvar VAR_NEWBARK_TOWN_STATE, 4
	setflag FLAG_HIDE_MOMS_FRIEND
	clearflag FLAG_HIDE_MOMS_FRIEND2
	setflag FLAG_ADVENTURE_STARTED
	setflag FLAG_START_NUZLOCKE
	setflag FLAG_EXP_SHARE_ENABLED
	removeitem ITEM_MYSTERY_EGG
@ The aide's five Poke Balls (NewBarkTown_Lab_EventScript_TriggerAideGiveBalls)
	additem ITEM_POKE_BALL, 5
	setflag FLAG_RECEIVED_FIRST_BALLS
	setvar VAR_NEWBARKTOWN_LABSTATE, 6
@ Mom's "good luck" (NewBarkTown_PlayersHouse_1F_MomEventScript_GoodLuck)
	setflag FLAG_MOM_VISITED
	clearflag FLAG_HIDE_ROUTE_30_NPCS
	setvar VAR_NEWBARK_TOWN_STATE, 5
	end
