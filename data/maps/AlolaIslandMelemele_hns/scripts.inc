AlolaIslandMelemele_hns_MapScripts::
# 2 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION
# 16 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE
# 20 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION:
# 3 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setrespawn HEAL_LOCATION_ALOLA_ISLAND_MELEMELE_HNS
# 4 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	gettimeofday
# 5 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
# 5 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION_1
# 12 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( RATICATE_ALOLA )
# 13 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_MELEMELE_TOTEM_DAY
	return

AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION_1:
# 7 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( LEAFEON )
# 8 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_MELEMELE_TOTEM_DAY
	return

AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE:
# 16 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	map_script_2 VAR_ALOLA_TRAVEL, 1, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0
	.2byte 0

AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0:
# 17 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Alola_Melemele_Captain, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0
# 18 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0
	return

AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
# 20 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	map_script_2 VAR_ALOLA_TRAVEL, 1, Alola_Melemele_GetOffBoat
	.2byte 0


Alola_Melemele_GetOffBoat::
# 24 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 25 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 26 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Alola_Melemele_Captain, Alola_Melemele_GetOffBoat_Movement_0
# 27 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_GetOffBoat_Movement_1
# 28 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 29 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_GetOffBoat_Text_0, MSGBOX_AUTOCLOSE
# 33 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_ALOLA_TRAVEL, 2
# 34 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0
# 35 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 36 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_TravelToKanto::
# 41 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 42 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	faceplayer
# 43 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TravelToKanto_Text_0, MSGBOX_YESNO
# 47 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Alola_Melemele_TravelToKanto_1
# 85 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TravelToKanto_Text_2, MSGBOX_AUTOCLOSE
# 87 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_TravelToKanto_1:
# 48 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TravelToKanto_Text_1, MSGBOX_AUTOCLOSE
# 49 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
# 50 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_TEMP_1, 32
	goto_if_eq Alola_Melemele_TravelToKanto_5
# 54 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_TEMP_0, 23
	goto_if_eq Alola_Melemele_TravelToKanto_8
Alola_Melemele_TravelToKanto_7:
Alola_Melemele_TravelToKanto_4:
# 59 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Alola_Melemele_Captain, Alola_Melemele_TravelToKanto_Movement_2
# 60 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_TravelToKanto_Movement_2
# 61 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 62 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 63 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	hidefollower
# 64 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_EXIT
# 65 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	special SpawnCameraObject
# 66 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	hideobjectat LOCALID_PLAYER, MAP_ALOLA_ISLAND_MELEMELE_HNS
# 67 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	hideobjectat Alola_Melemele_Captain, MAP_ALOLA_ISLAND_MELEMELE_HNS
# 68 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement OBJ_EVENT_ID_CAMERA, Alola_Melemele_TravelToKanto_Movement_3
# 69 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 70 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 71 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 72 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 73 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_RG_SS_ANNE_HORN
# 74 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 75 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_M_SURF
# 76 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Alola_Melemele_Ship, Alola_Melemele_TravelToKanto_Movement_4
# 77 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 90
# 78 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 79 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	special RemoveCameraObject
# 80 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	warp MAP_ROUTE13_HNS, 37, 29
# 81 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitstate
	end

Alola_Melemele_TravelToKanto_5:
# 51 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_TravelToKanto_Movement_0
# 52 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
	goto Alola_Melemele_TravelToKanto_4

Alola_Melemele_TravelToKanto_6:
# 55 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_TravelToKanto_Movement_1
# 56 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
	goto Alola_Melemele_TravelToKanto_4

Alola_Melemele_TravelToKanto_8:
# 54 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_TEMP_1, 33
	goto_if_eq Alola_Melemele_TravelToKanto_6
	goto Alola_Melemele_TravelToKanto_7


Alola_Melemele_Mailbox::
# 93 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 94 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Mailbox_Text_0
# 95 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_Melemele_Sign::
# 100 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 101 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Melemele_Sign_Text_0
# 102 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_Pokecenter_Sign::
# 107 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 108 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Pokecenter_Sign_Text_0
# 114 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_MelemeleMart_Sign::
# 119 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 120 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_MelemeleMart_Sign_Text_0
# 121 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_BattleSandygast::
# 126 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 127 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	faceplayer
# 128 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_CORSOLA, 0
# 129 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_BattleSandygast_Text_0, MSGBOX_AUTOCLOSE
# 130 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
# 131 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setwildbattle SPECIES_CORSOLA, 45
# 132 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	dowildbattle
# 133 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 134 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Melemele_BattleSandygast_2
# 140 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Melemele_BattleSandygast_3
# 147 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

# 150 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleSandygast_2:
# 135 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_CAUGHT_SANDYGAST1
# 136 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject Alola_Melemele_Sandygast
# 137 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleSandygast_3:
# 141 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_CAUGHT_SANDYGAST1
# 142 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject Alola_Melemele_Sandygast
# 143 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_FindItem1::
# 155 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	finditem ITEM_RARE_CANDY, 1
	end


Alola_Melemele_SamsonOak_Trigger_Beginning::
# 160 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 161 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	addobject SamsonOakMelemeleIntro
# 162 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_0
# 163 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_PIN
# 164 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_0
# 165 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 166 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_1
# 167 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 168 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_1, MSGBOX_AUTOCLOSE
# 169 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_2
# 170 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 171 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_2, MSGBOX_AUTOCLOSE
# 175 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_3
# 176 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 177 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 15
# 178 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_3, MSGBOX_AUTOCLOSE
# 185 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playbgm MUS_HG_FOLLOW_ME_1, FALSE
# 186 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_4
# 187 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_5
# 188 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 189 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 190 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_2
# 191 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 192 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_4
# 199 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_6
# 200 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_LEDGE
# 201 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 202 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_LEDGE
# 203 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 204 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_5, MSGBOX_AUTOCLOSE
# 215 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_6
# 216 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_LEDGE
# 217 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 218 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_LEDGE
# 219 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 220 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_6, MSGBOX_AUTOCLOSE
# 234 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_7
# 235 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 236 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 237 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	fadedefaultbgm
# 238 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_ALOLA_STATE, 1
# 239 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject SamsonOakMelemeleIntro
# 240 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_NeedToTalkToSamsonOak::
# 245 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 246 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_NeedToTalkToSamsonOak_Text_0, MSGBOX_AUTOCLOSE
# 248 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_NeedToTalkToSamsonOak_Movement_0
# 249 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 250 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_TotemBattle_Trigger::
# 255 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_unset FLAG_TRIGGERED_MELEMELE_TOTEM, Alola_Melemele_TotemBattle_Trigger_1
	end

Alola_Melemele_TotemBattle_Trigger_1:
# 257 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_TotemBattle_Trigger_7
Alola_Melemele_TotemBattle_Trigger_5:
	end

Alola_Melemele_TotemBattle_Trigger_4:
# 259 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 260 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 261 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_0x8004, 2
# 262 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_0x8005, 6
# 263 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_0x8006, 4
# 264 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_0x8007, 4
# 265 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	special ShakeCamera
# 266 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitstate
# 267 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 268 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 269 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_HIDE_MELEMELE_TOTEM
# 270 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	gettimeofday
# 271 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Melemele_TotemBattle_Trigger_14
# 271 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Melemele_TotemBattle_Trigger_14
# 281 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_RATICATE_ALOLA, 0
# 282 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( RATICATE_ALOLA )
# 283 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_MELEMELE_TOTEM_DAY
# 284 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	addobject Melemele_Totem
# 285 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
Alola_Melemele_TotemBattle_Trigger_13:
# 287 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	special DrawWholeMapView
# 288 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 289 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 290 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 291 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	gettimeofday
# 292 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Melemele_TotemBattle_Trigger_20
# 292 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Melemele_TotemBattle_Trigger_20
# 301 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_RATICATE_ALOLA, 0
# 302 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Melemele_Totem, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_2
# 303 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 304 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
Alola_Melemele_TotemBattle_Trigger_19:
# 306 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_TRIGGERED_MELEMELE_TOTEM
# 307 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_TotemBattle_Trigger_6:
# 257 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_TotemBattle_Trigger_10
	goto Alola_Melemele_TotemBattle_Trigger_5

Alola_Melemele_TotemBattle_Trigger_7:
# 257 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_TotemBattle_Trigger_6
	goto Alola_Melemele_TotemBattle_Trigger_5

Alola_Melemele_TotemBattle_Trigger_10:
# 257 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_TotemBattle_Trigger_4
	goto Alola_Melemele_TotemBattle_Trigger_5

Alola_Melemele_TotemBattle_Trigger_14:
# 273 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_LEAFEON, 0
# 274 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( LEAFEON )
# 275 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_MELEMELE_TOTEM_DAY
# 276 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	addobject Melemele_Totem
# 277 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
	goto Alola_Melemele_TotemBattle_Trigger_13

Alola_Melemele_TotemBattle_Trigger_20:
# 294 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_LEAFEON, 0
# 295 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Melemele_Totem, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_2
# 296 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 297 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
	goto Alola_Melemele_TotemBattle_Trigger_19


Alola_Melemele_TotemBattle::
# 322 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 323 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	faceplayer
# 324 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_MELEMELE_TOTEM_DAY, Alola_Melemele_TotemBattle_1
# 359 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_RATICATE_ALOLA, 0
# 360 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TotemBattle_Text_2, MSGBOX_AUTOCLOSE
# 361 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
# 362 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setwildbattle SPECIES_RATTATA_ALOLA, 60, ITEM_NONE, SPECIES_RATICATE_ALOLA_TOTEM, 60, ITEM_PECHA_BERRY
# 363 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 0, 1, 0
# 364 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 365 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 366 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 367 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	dowildbattle
# 368 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 369 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Melemele_TotemBattle_7
	return

Alola_Melemele_TotemBattle_1:
# 326 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_LEAFEON, 0
# 327 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
# 328 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
# 330 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setwildbattle SPECIES_EEVEE, 60, ITEM_NONE, SPECIES_LEAFEON, 60, ITEM_PECHA_BERRY
# 331 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 1, 1, 1, 1, 1, 1
# 332 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 333 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 334 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 335 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	dowildbattle
# 336 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 337 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Melemele_TotemBattle_5
# 349 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Alola_Melemele_TotemBattle_9
	return

Alola_Melemele_TotemBattle_5:
# 338 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_HIDE_MELEMELE_TOTEM
# 339 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_DEFEATED_MELEMELE_TOTEM
# 340 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject Melemele_Totem
# 341 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TotemBattle_Text_1, MSGBOX_AUTOCLOSE
# 343 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 344 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 345 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 346 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_TotemBattle_7:
# 371 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_HIDE_MELEMELE_TOTEM
# 372 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_DEFEATED_MELEMELE_TOTEM
# 373 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject Melemele_Totem
# 374 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TotemBattle_Text_3, MSGBOX_AUTOCLOSE
# 376 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 377 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 378 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 379 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_TotemBattle_9:
# 350 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 351 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 352 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 353 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_Totem_sign::
# 387 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 388 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_FINI, Alola_Melemele_Totem_sign_5
Alola_Melemele_Totem_sign_3:
# 429 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Totem_sign_Text_6, MSGBOX_AUTOCLOSE
# 432 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_Totem_sign_2:
# 390 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Totem_sign_Text_0
# 395 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	dynmultichoice 20, 4, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, Alola_Melemele_Totem_sign_Text_1, Alola_Melemele_Totem_sign_Text_2, Alola_Melemele_Totem_sign_Text_3, Alola_Melemele_Totem_sign_Text_4, Alola_Melemele_Totem_sign_Text_5
# 396 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Alola_Melemele_Totem_sign_12
# 402 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_Totem_sign_15
# 408 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq Alola_Melemele_Totem_sign_18
# 414 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, 3
	goto_if_eq Alola_Melemele_Totem_sign_20
# 422 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_Totem_sign_4:
# 388 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_BULU, Alola_Melemele_Totem_sign_8
	goto Alola_Melemele_Totem_sign_3

Alola_Melemele_Totem_sign_5:
# 388 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_KOKO, Alola_Melemele_Totem_sign_4
	goto Alola_Melemele_Totem_sign_3

Alola_Melemele_Totem_sign_8:
# 388 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_LELE, Alola_Melemele_Totem_sign_2
	goto Alola_Melemele_Totem_sign_3

Alola_Melemele_Totem_sign_12:
# 398 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_MELEMELE_HNS, 34, 26
# 399 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitstate
	end

Alola_Melemele_Totem_sign_15:
# 404 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_RIGHT_HNS, 9, 10
# 405 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitstate
	end

Alola_Melemele_Totem_sign_18:
# 410 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	warp MAP_ULA_ULA_FOREST_HNS, 16, 5
# 411 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitstate
	end

Alola_Melemele_Totem_sign_20:
# 416 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_HNS, 13, 8
# 417 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitstate
	end


Alola_MeleMele_TapuKoko_Flyover::
# 437 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_FLYOVER_TAPU_KOKO, Alola_MeleMele_TapuKoko_Flyover_2
# 450 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_MeleMele_TapuKoko_Flyover_2:
# 439 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	addobject Melemele_Flyover_Tapu
# 440 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_M_FLY
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Melemele_Flyover_Tapu, Alola_MeleMele_TapuKoko_Flyover_Movement_0
# 442 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 443 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject Melemele_Flyover_Tapu
# 444 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_FLYOVER_TAPU_KOKO
# 445 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_HIDE_TAPU_KOKO
# 446 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_BattleVsTapuKoko::
# 455 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 456 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	faceplayer
# 457 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_TAPU_KOKO, CRY_MODE_ENCOUNTER
# 458 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_BattleVsTapuKoko_Text_0
# 459 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 460 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
# 461 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	seteventmon SPECIES_TAPU_KOKO, 60
# 462 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	special BattleSetup_StartLegendaryBattle
# 463 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitstate
# 464 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 465 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Melemele_BattleVsTapuKoko_2
# 472 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Melemele_BattleVsTapuKoko_3
# 480 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

# 483 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleVsTapuKoko_2:
# 466 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_KOKO
# 467 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_KOKO
# 468 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject Melemele_Tapu
# 469 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleVsTapuKoko_3:
# 473 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_KOKO
# 474 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_KOKO
# 475 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject Melemele_Tapu
# 476 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_TrainerBattleSwimmer::
# 488 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	trainerbattle_single TRAINER_MELEMELE_SWIMMER_1_HNS, Alola_Melemele_TrainerBattleSwimmer_Text_0, Alola_Melemele_TrainerBattleSwimmer_Text_1
# 489 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TrainerBattleSwimmer_Text_2, MSGBOX_AUTOCLOSE
# 491 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_Bugcatcher::
# 496 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 497 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	faceplayer
# 498 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Bugcatcher_Text_0, MSGBOX_AUTOCLOSE
# 500 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_camper::
# 506 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 507 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	faceplayer
# 508 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_camper_Text_0, MSGBOX_AUTOCLOSE
# 510 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_Picnicker::
# 516 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 517 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	faceplayer
# 518 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Picnicker_Text_0, MSGBOX_AUTOCLOSE
# 523 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


# 17 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0:
# 17 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	face_up
	step_end

# 26 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_GetOffBoat_Movement_0:
# 26 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	face_right
	step_end

# 27 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_GetOffBoat_Movement_1:
# 27 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	face_left
	step_end

# 51 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_TravelToKanto_Movement_0:
# 51 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_right
# 51 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
	step_end

# 55 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_TravelToKanto_Movement_1:
# 55 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 55 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_right
# 55 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_right
# 55 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
	step_end

# 59 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_TravelToKanto_Movement_2:
# 59 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	face_down
	step_end

# 68 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_TravelToKanto_Movement_3:
# 68 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
	step_end

# 76 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_TravelToKanto_Movement_4:
# 76 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 76 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 76 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 76 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 76 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 76 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 76 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 76 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 76 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 76 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 76 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
	step_end

# 164 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_0:
# 164 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	emote_exclamation_mark
# 164 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	face_up
	step_end

# 166 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_1:
# 166 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
# 166 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
# 166 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
# 166 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
# 166 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
	step_end

# 169 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_2:
# 169 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_in_place_down
# 169 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_in_place_down
	step_end

# 175 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_3:
# 175 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_in_place_up
# 175 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_in_place_up
	step_end

# 186 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_4:
# 186 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay_16
# 186 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 186 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 186 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 186 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 186 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
	step_end

# 187 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_5:
# 187 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 187 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 187 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 187 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 187 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 187 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
	step_end

# 199 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_6:
# 199 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	jump_in_place_down
# 199 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	jump_in_place_down
	step_end

# 234 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_7:
# 234 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 234 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 234 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 234 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 234 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 234 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 234 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 234 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
	step_end

# 248 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_NeedToTalkToSamsonOak_Movement_0:
# 248 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
	step_end

# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_MeleMele_TapuKoko_Flyover_Movement_0:
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
	step_end

Alola_Melemele_GetOffBoat_Text_0:
# 29 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Welcome back to the Isles!\p"
	.string "Come back if you'd like to take a trip\n"
	.string "to mainland Kanto!$"

Alola_Melemele_TravelToKanto_Text_0:
# 43 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Ahoy!\p"
	.string "Would you like to travel to mainland\n"
	.string "Kanto?$"

Alola_Melemele_TravelToKanto_Text_1:
# 48 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Ahoy! Let's get you on board!$"

Alola_Melemele_TravelToKanto_Text_2:
# 85 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Ahoy!\n"
	.string "Come back when you'd like to set sail.$"

Alola_Melemele_Mailbox_Text_0:
# 94 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Samson Oak's Villa$"

Alola_Melemele_Melemele_Sign_Text_0:
# 101 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Welcome to Melemele Isle!$"

Alola_Melemele_Pokecenter_Sign_Text_0:
# 108 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Welcome to the Melemele Isle\n"
	.string "Pokémon Center!\p"
	.string "This is the only Pokémon Center on the\n"
	.string "Alola Isles but you can rest on benches\l"
	.string "around the Isles.$"

Alola_Melemele_MelemeleMart_Sign_Text_0:
# 120 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Melemele Isle Mart$"

Alola_Melemele_BattleSandygast_Text_0:
# 129 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Coorr!$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_0:
# 162 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "ALOLA!$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_1:
# 168 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Welcome to the Alola Isles!$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_2:
# 171 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "My name is Samson Oak!\n"
	.string "I'm a Pokémon Professor.\p"
	.string "What's your name?$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_3:
# 178 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Ah, {PLAYER}.\n"
	.string "A fine name!\p"
	.string "You may know my cousin, Professor Oak,\n"
	.string "from the Kanto region.\p"
	.string "Let me show you to town!$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_4:
# 192 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "This is the main town on these Islands.\p"
	.string "It's eerily similar to Hau'oli City in\n"
	.string "Alola… {PAUSE 30}And when I think about it…\p"
	.string "This whole island reminds me of Melemele\n"
	.string "Island…$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_5:
# 204 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Well, anyways!\p"
	.string "I research variations of Pokémon that \n"
	.string "can be found in different regions!\p"
	.string "On my way back from the Alola region,\n"
	.string "I stumbled across these isles…\p"
	.string "Surprisingly, many of the Pokémon I saw\n"
	.string "in Alola were here as well, so I've called\l"
	.string "this place… {PAUSE 30}the Alola Isles!$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_6:
# 220 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
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
# 246 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Samson is waiting for you at his villa…\n"
	.string "{PAUSE 30}best not make him wait too long!$"

Alola_Melemele_TotemBattle_Text_0:
# 327 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Leee!$"

Alola_Melemele_TotemBattle_Text_1:
# 341 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Totem Leafeon was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Melemele_TotemBattle_Text_2:
# 360 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Thhhh!$"

Alola_Melemele_TotemBattle_Text_3:
# 374 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Totem Raticate was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Melemele_Totem_sign_Text_0:
# 390 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "The totem is emanating a strong\n"
	.string "energy…\p"
	.string "Touch the totem to teleport to another\n"
	.string "Isle?$"

Alola_Melemele_Totem_sign_Text_1:
# 395 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Melemele Isle$"

Alola_Melemele_Totem_sign_Text_2:
# 395 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Akala Isle$"

Alola_Melemele_Totem_sign_Text_3:
# 395 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Ula'ula Isle$"

Alola_Melemele_Totem_sign_Text_4:
# 395 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Poni Isle$"

Alola_Melemele_Totem_sign_Text_5:
# 395 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Cancel$"

Alola_Melemele_Totem_sign_Text_6:
# 429 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "A strange totem stands here,\n"
	.string "power is emanating from it…$"

Alola_Melemele_BattleVsTapuKoko_Text_0:
# 458 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Ko-Ko-Kooo!$"

Alola_Melemele_TrainerBattleSwimmer_Text_0:
# 488 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "The waters are warm here by the Isles!$"

Alola_Melemele_TrainerBattleSwimmer_Text_1:
# 488 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Maybe I should dry off on land for\na bit…$"

Alola_Melemele_TrainerBattleSwimmer_Text_2:
# 489 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "There are plenty of neat Pokémon in\n"
	.string "the water, try all your fishing rods!$"

Alola_Melemele_Bugcatcher_Text_0:
# 498 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "The bug Pokémon on the Alola Isles\n"
	.string "are much bigger than those in Kanto!$"

Alola_Melemele_camper_Text_0:
# 508 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "I traveled all the way from Kanto to see\n"
	.string "my favorite bird Pokémon, Chatot!$"

Alola_Melemele_Picnicker_Text_0:
# 518 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "These Isles are chock full of unique\n"
	.string "Pokémon!\p"
	.string "I need to stock up on Poké Balls so I\n"
	.string "can catch them all!$"
