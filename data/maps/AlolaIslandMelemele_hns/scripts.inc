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
# 73 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TravelToKanto_Text_2, MSGBOX_AUTOCLOSE
# 75 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
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
	playse SE_M_SURF
# 64 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Alola_Melemele_Ship, Alola_Melemele_TravelToKanto_Movement_4
# 65 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 90
# 66 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 67 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	special RemoveCameraObject
# 68 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	warp MAP_ROUTE13_HNS, 37, 29
# 69 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
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
# 81 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 82 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Mailbox_Text_0
# 83 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_Melemele_Sign::
# 88 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 89 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Melemele_Sign_Text_0
# 90 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_Pokecenter_Sign::
# 95 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 96 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Pokecenter_Sign_Text_0
# 102 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_MelemeleMart_Sign::
# 107 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 108 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_MelemeleMart_Sign_Text_0
# 109 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_BattleSandygast::
# 114 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 115 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	faceplayer
# 116 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_SANDYGAST, 0
# 117 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_BattleSandygast_Text_0, MSGBOX_AUTOCLOSE
# 118 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
# 119 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setwildbattle SPECIES_SANDYGAST, 45
# 120 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	dowildbattle
# 121 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 122 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Melemele_BattleSandygast_2
# 128 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Melemele_BattleSandygast_3
# 135 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

# 138 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleSandygast_2:
# 123 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_CAUGHT_SANDYGAST1
# 124 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject Alola_Melemele_Sandygast
# 125 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleSandygast_3:
# 129 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_CAUGHT_SANDYGAST1
# 130 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject Alola_Melemele_Sandygast
# 131 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_FindItem1::
# 143 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	finditem ITEM_POTION, 1
	end


Alola_Melemele_SamsonOak_Trigger_Beginning::
# 148 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 149 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	addobject SamsonOakMelemeleIntro
# 150 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_0
# 151 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_PIN
# 152 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_0
# 153 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 154 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_1
# 155 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 156 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_1, MSGBOX_AUTOCLOSE
# 157 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_2
# 158 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 159 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_2, MSGBOX_AUTOCLOSE
# 163 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_3
# 164 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 165 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 15
# 166 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_3, MSGBOX_AUTOCLOSE
# 173 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playbgm MUS_HG_FOLLOW_ME_1, FALSE
# 174 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_4
# 175 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_5
# 176 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 177 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 178 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_2
# 179 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 180 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_4
# 187 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_6
# 188 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_LEDGE
# 189 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 190 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_LEDGE
# 191 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 192 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_5, MSGBOX_AUTOCLOSE
# 203 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_6
# 204 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_LEDGE
# 205 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 206 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_LEDGE
# 207 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 208 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_6, MSGBOX_AUTOCLOSE
# 222 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_7
# 223 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 224 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 225 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	fadedefaultbgm
# 226 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_ALOLA_STATE, 1
# 227 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject SamsonOakMelemeleIntro
# 228 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_NeedToTalkToSamsonOak::
# 233 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 234 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_NeedToTalkToSamsonOak_Text_0, MSGBOX_AUTOCLOSE
# 236 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_NeedToTalkToSamsonOak_Movement_0
# 237 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 238 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
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

# 64 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_TravelToKanto_Movement_4:
# 64 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 64 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 64 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 64 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 64 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 64 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 64 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 64 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 64 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 64 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 64 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
	step_end

# 152 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_0:
# 152 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	emote_exclamation_mark
# 152 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	face_up
	step_end

# 154 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_1:
# 154 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
# 154 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
# 154 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
# 154 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
# 154 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
	step_end

# 157 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_2:
# 157 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_in_place_down
# 157 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_in_place_down
	step_end

# 163 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_3:
# 163 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_in_place_up
# 163 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_in_place_up
	step_end

# 174 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_4:
# 174 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay_16
# 174 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 174 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 174 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 174 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 174 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
	step_end

# 175 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_5:
# 175 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 175 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 175 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 175 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 175 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 175 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
	step_end

# 187 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_6:
# 187 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	jump_in_place_down
# 187 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	jump_in_place_down
	step_end

# 222 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_7:
# 222 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 222 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 222 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 222 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 222 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 222 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 222 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 222 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
	step_end

# 236 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_NeedToTalkToSamsonOak_Movement_0:
# 236 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
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
# 73 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Ahoy!\n"
	.string "Come back when you'd like to set sail.$"

Alola_Melemele_Mailbox_Text_0:
# 82 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Samson Oak's Villa$"

Alola_Melemele_Melemele_Sign_Text_0:
# 89 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Welcome to Melemele Isle!$"

Alola_Melemele_Pokecenter_Sign_Text_0:
# 96 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Welcome to the Melemele Isle\n"
	.string "Pokémon Center!\p"
	.string "This is the only Pokémon Center on the\n"
	.string "Alola Isles, so be sure to take care of\l"
	.string "your Pokémon while you're here!$"

Alola_Melemele_MelemeleMart_Sign_Text_0:
# 108 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Melemele Isle Mart$"

Alola_Melemele_BattleSandygast_Text_0:
# 117 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Gaaah!$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_0:
# 150 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "ALOLA!$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_1:
# 156 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Welcome to the Alola Isles!$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_2:
# 159 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "My name is Samson Oak!\n"
	.string "I'm a Pokémon Professor.\p"
	.string "What's your name?$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_3:
# 166 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Ah, {PLAYER}.\n"
	.string "A fine name!\p"
	.string "You may know my cousin, Professor Oak,\n"
	.string "from the Kanto region.\p"
	.string "Let me show you to town!$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_4:
# 180 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "This is the main town on these Islands.\p"
	.string "It's eerily similar to Hau'oli City in\n"
	.string "Alola… {PAUSE 30}And when I think about it…\p"
	.string "This whole island reminds me of Melemele\n"
	.string "Island…$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_5:
# 192 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Well, anyways!\p"
	.string "I research variations of Pokémon that \n"
	.string "can be found in different regions!\p"
	.string "On my way back from the Alola region,\n"
	.string "I stumbled across these isles…\p"
	.string "Surprisingly, many of the Pokémon I saw\n"
	.string "in Alola were here as well, so I've called\l"
	.string "this place… {PAUSE 30}the Alola Isles!$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_6:
# 208 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Now I haven't completely explored the\n"
	.string "Isles yet… {PAUSE 30}I just landed here myself.\p"
	.string "I'd like to know if all of the variants\n"
	.string "native to Alola are here.\p"
	.string "If you happen to come across any,\n"
	.string "please come by my villa on the east side\l"
	.string "of the Isle and show them to me!\p"
	.string "Oh. And feel free to explore the Isle\n"
	.string "while on your way!\p"
	.string "See you there!$"

Alola_Melemele_NeedToTalkToSamsonOak_Text_0:
# 234 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Samson is waiting for you at his villa…\n"
	.string "{PAUSE 30}best not make him wait too long!$"
