AlolaIslandMelemele_hns_MapScripts::
# 2 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION
# 6 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE
# 10 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION:
# 3 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setrespawn HEAL_LOCATION_ALOLA_ISLAND_MELEMELE_HNS
	end

AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE:
# 6 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	map_script_2 VAR_ALOLA_TRAVEL, 1, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0
	.2byte 0

AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0:
# 7 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Alola_Melemele_Captain, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0
# 8 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0
	return

AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
# 10 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	map_script_2 VAR_ALOLA_TRAVEL, 1, Alola_Melemele_GetOffBoat
	.2byte 0


Alola_Melemele_GetOffBoat::
# 14 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 15 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 16 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Alola_Melemele_Captain, Alola_Melemele_GetOffBoat_Movement_0
# 17 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_GetOffBoat_Movement_1
# 18 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 19 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_GetOffBoat_Text_0, MSGBOX_AUTOCLOSE
# 23 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_ALOLA_TRAVEL, 2
# 24 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_TravelToKanto::
# 29 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 30 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	faceplayer
# 31 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TravelToKanto_Text_0, MSGBOX_YESNO
# 35 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Alola_Melemele_TravelToKanto_1
# 72 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TravelToKanto_Text_2, MSGBOX_AUTOCLOSE
# 74 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_TravelToKanto_1:
# 36 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TravelToKanto_Text_1, MSGBOX_AUTOCLOSE
# 37 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
# 38 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_TEMP_1, 32
	goto_if_eq Alola_Melemele_TravelToKanto_5
# 42 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_TEMP_0, 23
	goto_if_eq Alola_Melemele_TravelToKanto_8
Alola_Melemele_TravelToKanto_7:
Alola_Melemele_TravelToKanto_4:
# 47 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Alola_Melemele_Captain, Alola_Melemele_TravelToKanto_Movement_2
# 48 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_TravelToKanto_Movement_2
# 49 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 50 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 51 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	hidefollower
# 52 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_EXIT
# 53 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	special SpawnCameraObject
# 54 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	hideobjectat LOCALID_PLAYER, MAP_ALOLA_ISLAND_MELEMELE_HNS
# 55 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	hideobjectat Alola_Melemele_Captain, MAP_ALOLA_ISLAND_MELEMELE_HNS
# 56 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement OBJ_EVENT_ID_CAMERA, Alola_Melemele_TravelToKanto_Movement_3
# 57 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 58 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 59 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 60 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 61 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_RG_SS_ANNE_HORN
# 62 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 63 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Alola_Melemele_Ship, Alola_Melemele_TravelToKanto_Movement_4
# 64 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 90
# 65 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 66 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	special RemoveCameraObject
# 67 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	warp MAP_ROUTE13_HNS, 37, 29
# 68 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitstate
	end

Alola_Melemele_TravelToKanto_5:
# 39 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_TravelToKanto_Movement_0
# 40 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
	goto Alola_Melemele_TravelToKanto_4

Alola_Melemele_TravelToKanto_6:
# 43 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_TravelToKanto_Movement_1
# 44 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
	goto Alola_Melemele_TravelToKanto_4

Alola_Melemele_TravelToKanto_8:
# 42 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_TEMP_1, 33
	goto_if_eq Alola_Melemele_TravelToKanto_6
	goto Alola_Melemele_TravelToKanto_7


Alola_Melemele_Mailbox::
# 80 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 81 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Mailbox_Text_0
# 82 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_Melemele_Sign::
# 87 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 88 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Melemele_Sign_Text_0
# 89 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_Pokecenter_Sign::
# 94 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 95 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Pokecenter_Sign_Text_0
# 101 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_MelemeleMart_Sign::
# 106 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 107 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_MelemeleMart_Sign_Text_0
# 108 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_BattleSandygast::
# 113 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 114 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	faceplayer
# 115 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_SANDYGAST, 0
# 116 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_BattleSandygast_Text_0, MSGBOX_AUTOCLOSE
# 117 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
# 118 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setwildbattle SPECIES_SANDYGAST, 45
# 119 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	dowildbattle
# 120 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 121 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Melemele_BattleSandygast_2
# 127 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Melemele_BattleSandygast_3
# 134 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

# 137 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleSandygast_2:
# 122 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_CAUGHT_SANDYGAST1
# 123 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject Alola_Melemele_Sandygast
# 124 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleSandygast_3:
# 128 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_CAUGHT_SANDYGAST1
# 129 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject Alola_Melemele_Sandygast
# 130 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


# 7 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0:
# 7 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	face_up
	step_end

# 16 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_GetOffBoat_Movement_0:
# 16 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	face_right
	step_end

# 17 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_GetOffBoat_Movement_1:
# 17 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	face_left
	step_end

# 39 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_TravelToKanto_Movement_0:
# 39 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_right
# 39 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
	step_end

# 43 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_TravelToKanto_Movement_1:
# 43 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 43 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_right
# 43 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_right
# 43 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
	step_end

# 47 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_TravelToKanto_Movement_2:
# 47 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	face_down
	step_end

# 56 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_TravelToKanto_Movement_3:
# 56 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
	step_end

# 63 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_TravelToKanto_Movement_4:
# 63 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 63 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 63 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 63 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 63 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 63 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 63 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 63 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 63 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 63 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 63 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
	step_end

Alola_Melemele_GetOffBoat_Text_0:
# 19 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Welcome back to the Alola Isles!\p"
	.string "Come back if you'd like to take a trip\n"
	.string "to mainland Kanto!$"

Alola_Melemele_TravelToKanto_Text_0:
# 31 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Ahoy!\p"
	.string "Would you like to travel to mainland\n"
	.string "Kanto?$"

Alola_Melemele_TravelToKanto_Text_1:
# 36 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Ahoy! Let's get you on board!$"

Alola_Melemele_TravelToKanto_Text_2:
# 72 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Ahoy!\n"
	.string "Come back when you'd like to set sail.$"

Alola_Melemele_Mailbox_Text_0:
# 81 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Samson Oak's Villa$"

Alola_Melemele_Melemele_Sign_Text_0:
# 88 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Welcome to Melemele Island!$"

Alola_Melemele_Pokecenter_Sign_Text_0:
# 95 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Welcome to the Melemele Island\n"
	.string "Pokémon Center!\p"
	.string "This is the only Pokémon Center on the\n"
	.string "Alola Isles, so be sure to take care of\l"
	.string "your Pokémon while you're here!$"

Alola_Melemele_MelemeleMart_Sign_Text_0:
# 107 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Melemele Island Mart$"

Alola_Melemele_BattleSandygast_Text_0:
# 116 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Gaaah!$"
