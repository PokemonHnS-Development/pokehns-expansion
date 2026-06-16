AlolaIslandMelemele_hns_MapScripts::
# 2 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION
# 5 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE
# 9 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION:
# 3 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setrespawn HEAL_LOCATION_ALOLA_ISLAND_MELEMELE_HNS
	return

AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE:
# 5 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	map_script_2 VAR_ALOLA_TRAVEL, 1, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0
	.2byte 0

AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0:
# 6 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Alola_Melemele_Captain, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0
# 7 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0
	return

AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
# 9 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	map_script_2 VAR_ALOLA_TRAVEL, 1, Alola_Melemele_GetOffBoat
	.2byte 0


Alola_Melemele_GetOffBoat::
# 13 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 14 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 15 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Alola_Melemele_Captain, Alola_Melemele_GetOffBoat_Movement_0
# 16 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_GetOffBoat_Movement_1
# 17 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 18 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_GetOffBoat_Text_0, MSGBOX_AUTOCLOSE
# 22 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_ALOLA_TRAVEL, 2
# 23 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_TravelToKanto::
# 28 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 29 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	faceplayer
# 30 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TravelToKanto_Text_0, MSGBOX_YESNO
# 34 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Alola_Melemele_TravelToKanto_1
# 72 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TravelToKanto_Text_2, MSGBOX_AUTOCLOSE
# 74 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_TravelToKanto_1:
# 35 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TravelToKanto_Text_1, MSGBOX_AUTOCLOSE
# 36 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
# 37 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_TEMP_1, 32
	goto_if_eq Alola_Melemele_TravelToKanto_5
# 41 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_TEMP_0, 23
	goto_if_eq Alola_Melemele_TravelToKanto_8
Alola_Melemele_TravelToKanto_7:
Alola_Melemele_TravelToKanto_4:
# 46 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Alola_Melemele_Captain, Alola_Melemele_TravelToKanto_Movement_2
# 47 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_TravelToKanto_Movement_2
# 48 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 49 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 50 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	hidefollower
# 51 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_EXIT
# 52 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	special SpawnCameraObject
# 53 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	hideobjectat LOCALID_PLAYER, MAP_ALOLA_ISLAND_MELEMELE_HNS
# 54 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	hideobjectat Alola_Melemele_Captain, MAP_ALOLA_ISLAND_MELEMELE_HNS
# 55 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement OBJ_EVENT_ID_CAMERA, Alola_Melemele_TravelToKanto_Movement_3
# 56 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 57 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 58 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 59 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 60 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_RG_SS_ANNE_HORN
# 61 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 62 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_M_SURF
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
# 38 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_TravelToKanto_Movement_0
# 39 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
	goto Alola_Melemele_TravelToKanto_4

Alola_Melemele_TravelToKanto_6:
# 42 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_TravelToKanto_Movement_1
# 43 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
	goto Alola_Melemele_TravelToKanto_4

Alola_Melemele_TravelToKanto_8:
# 41 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
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


Alola_Melemele_FindItem1::
# 142 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	finditem ITEM_RARE_CANDY, 1
	end


Alola_Melemele_SamsonOak_Trigger_Beginning::
# 147 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 148 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	addobject SamsonOakMelemeleIntro
# 149 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_0
# 150 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_PIN
# 151 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_0
# 152 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 153 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_1
# 154 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 155 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_1, MSGBOX_AUTOCLOSE
# 156 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_2
# 157 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 158 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_2, MSGBOX_AUTOCLOSE
# 162 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_3
# 163 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 164 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 15
# 165 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_3, MSGBOX_AUTOCLOSE
# 172 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playbgm MUS_HG_FOLLOW_ME_1, FALSE
# 173 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_4
# 174 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_5
# 175 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 176 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 177 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_2
# 178 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 179 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_4
# 186 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_6
# 187 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_LEDGE
# 188 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 189 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_LEDGE
# 190 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 191 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_5, MSGBOX_AUTOCLOSE
# 202 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_6
# 203 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_LEDGE
# 204 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 205 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_LEDGE
# 206 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitse
# 207 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOak_Trigger_Beginning_Text_6, MSGBOX_AUTOCLOSE
# 221 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement SamsonOakMelemeleIntro, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_7
# 222 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 223 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 224 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	fadedefaultbgm
# 225 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_ALOLA_STATE, 1
# 226 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject SamsonOakMelemeleIntro
# 227 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_NeedToTalkToSamsonOak::
# 232 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 233 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_NeedToTalkToSamsonOak_Text_0, MSGBOX_AUTOCLOSE
# 235 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Alola_Melemele_NeedToTalkToSamsonOak_Movement_0
# 236 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 237 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_TotemBattle_Trigger::
# 242 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_unset FLAG_TRIGGERED_MELEMELE_TOTEM, Alola_Melemele_TotemBattle_Trigger_1
	end

Alola_Melemele_TotemBattle_Trigger_1:
# 244 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Melemele_TotemBattle_Trigger_7
Alola_Melemele_TotemBattle_Trigger_5:
	end

Alola_Melemele_TotemBattle_Trigger_4:
# 246 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 247 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 248 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_0x8004, 2
# 249 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_0x8005, 6
# 250 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_0x8006, 4
# 251 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_0x8007, 4
# 252 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	special ShakeCamera
# 253 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitstate
# 254 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 255 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 256 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_HIDE_MELEMELE_TOTEM
# 257 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	gettimeofday
# 258 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Melemele_TotemBattle_Trigger_14
# 258 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Melemele_TotemBattle_Trigger_14
# 267 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_RATICATE_ALOLA, 0
# 268 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( RATICATE_ALOLA )
# 269 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	addobject Melemele_Totem
# 270 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
Alola_Melemele_TotemBattle_Trigger_13:
# 272 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	special DrawWholeMapView
# 273 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 274 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 275 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay 30
# 276 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	gettimeofday
# 277 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Melemele_TotemBattle_Trigger_20
# 277 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Melemele_TotemBattle_Trigger_20
# 286 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_RATICATE_ALOLA, 0
# 287 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Melemele_Totem, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_2
# 288 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 289 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
Alola_Melemele_TotemBattle_Trigger_19:
# 291 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_TRIGGERED_MELEMELE_TOTEM
# 292 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_TotemBattle_Trigger_6:
# 244 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Melemele_TotemBattle_Trigger_10
	goto Alola_Melemele_TotemBattle_Trigger_5

Alola_Melemele_TotemBattle_Trigger_7:
# 244 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Melemele_TotemBattle_Trigger_6
	goto Alola_Melemele_TotemBattle_Trigger_5

Alola_Melemele_TotemBattle_Trigger_10:
# 244 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Melemele_TotemBattle_Trigger_4
	goto Alola_Melemele_TotemBattle_Trigger_5

Alola_Melemele_TotemBattle_Trigger_14:
# 260 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_GUMSHOOS, 0
# 261 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES ( GUMSHOOS )
# 262 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	addobject Melemele_Totem
# 263 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
	goto Alola_Melemele_TotemBattle_Trigger_13

Alola_Melemele_TotemBattle_Trigger_20:
# 279 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_GUMSHOOS, 0
# 280 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Melemele_Totem, Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_2
# 281 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 282 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
	goto Alola_Melemele_TotemBattle_Trigger_19


Alola_Melemele_TotemBattle::
# 307 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 308 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	faceplayer
# 309 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	gettimeofday
# 310 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_0x8000, TIME_MORNING
	goto_if_eq Alola_Melemele_TotemBattle_1
# 310 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_0x8000, TIME_DAY
	goto_if_eq Alola_Melemele_TotemBattle_1
# 345 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_RATICATE_ALOLA, 0
# 346 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
# 347 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
# 348 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setwildbattle SPECIES_RATTATA_ALOLA, 60, ITEM_NONE, SPECIES_RATICATE_ALOLA_TOTEM, 60, ITEM_PECHA_BERRY
# 349 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 0, 1, 0
# 350 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 351 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 352 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 353 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	dowildbattle
# 354 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 355 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Melemele_TotemBattle_9
	return

Alola_Melemele_TotemBattle_1:
# 312 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_GUMSHOOS, 0
# 313 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
# 314 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
# 316 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setwildbattle SPECIES_YUNGOOS, 60, ITEM_NONE, SPECIES_GUMSHOOS_TOTEM, 60, ITEM_PECHA_BERRY
# 317 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 0, 1, 0
# 318 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 319 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 320 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 321 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	dowildbattle
# 322 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 323 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Melemele_TotemBattle_7
# 335 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Alola_Melemele_TotemBattle_11
	return

Alola_Melemele_TotemBattle_7:
# 324 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_HIDE_MELEMELE_TOTEM
# 325 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_DEFEATED_MELEMELE_TOTEM
# 326 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject Melemele_Totem
# 327 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TotemBattle_Text_1, MSGBOX_AUTOCLOSE
# 329 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 330 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 331 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 332 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_TotemBattle_9:
# 357 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_HIDE_MELEMELE_TOTEM
# 358 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_DEFEATED_MELEMELE_TOTEM
# 359 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject Melemele_Totem
# 360 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TotemBattle_Text_2, MSGBOX_AUTOCLOSE
# 362 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 363 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 364 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 365 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_TotemBattle_11:
# 336 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 337 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 338 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 339 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_Totem_sign::
# 373 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 374 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_FINI, Alola_Melemele_Totem_sign_5
Alola_Melemele_Totem_sign_3:
# 415 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Totem_sign_Text_6, MSGBOX_AUTOCLOSE
# 418 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_Totem_sign_2:
# 376 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Totem_sign_Text_0
# 381 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	dynmultichoice 20, 4, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, Alola_Melemele_Totem_sign_Text_1, Alola_Melemele_Totem_sign_Text_2, Alola_Melemele_Totem_sign_Text_3, Alola_Melemele_Totem_sign_Text_4, Alola_Melemele_Totem_sign_Text_5
# 382 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Alola_Melemele_Totem_sign_12
# 388 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_Totem_sign_15
# 394 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq Alola_Melemele_Totem_sign_18
# 400 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, 3
	goto_if_eq Alola_Melemele_Totem_sign_20
# 408 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_Totem_sign_4:
# 374 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_BULU, Alola_Melemele_Totem_sign_8
	goto Alola_Melemele_Totem_sign_3

Alola_Melemele_Totem_sign_5:
# 374 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_KOKO, Alola_Melemele_Totem_sign_4
	goto Alola_Melemele_Totem_sign_3

Alola_Melemele_Totem_sign_8:
# 374 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_BATTLED_TAPU_LELE, Alola_Melemele_Totem_sign_2
	goto Alola_Melemele_Totem_sign_3

Alola_Melemele_Totem_sign_12:
# 384 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_MELEMELE_HNS, 34, 26
# 385 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitstate
	end

Alola_Melemele_Totem_sign_15:
# 390 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_RIGHT_HNS, 9, 10
# 391 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitstate
	end

Alola_Melemele_Totem_sign_18:
# 396 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	warp MAP_ULA_ULA_FOREST_HNS, 16, 5
# 397 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitstate
	end

Alola_Melemele_Totem_sign_20:
# 402 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_HNS, 13, 8
# 403 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitstate
	end


Alola_MeleMele_TapuKoko_Flyover::
# 423 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	goto_if_set FLAG_FLYOVER_TAPU_KOKO, Alola_MeleMele_TapuKoko_Flyover_2
# 436 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_MeleMele_TapuKoko_Flyover_2:
# 425 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	addobject Melemele_Flyover_Tapu
# 426 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playse SE_M_FLY
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	applymovement Melemele_Flyover_Tapu, Alola_MeleMele_TapuKoko_Flyover_Movement_0
# 428 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 429 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject Melemele_Flyover_Tapu
# 430 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_FLYOVER_TAPU_KOKO
# 431 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	clearflag FLAG_HIDE_TAPU_KOKO
# 432 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_BattleVsTapuKoko::
# 441 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 442 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	faceplayer
# 443 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	playmoncry SPECIES_TAPU_KOKO, CRY_MODE_ENCOUNTER
# 444 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_BattleVsTapuKoko_Text_0
# 445 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmovement 0
# 446 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitmoncry
# 447 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	seteventmon SPECIES_TAPU_KOKO, 60
# 448 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	special BattleSetup_StartLegendaryBattle
# 449 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	waitstate
# 450 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 451 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Melemele_BattleVsTapuKoko_2
# 458 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Melemele_BattleVsTapuKoko_3
# 466 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

# 469 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleVsTapuKoko_2:
# 452 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_KOKO
# 453 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_KOKO
# 454 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject Melemele_Tapu
# 455 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end

Alola_Melemele_BattleVsTapuKoko_3:
# 459 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_KOKO
# 460 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_KOKO
# 461 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	removeobject Melemele_Tapu
# 462 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_TrainerBattleSwimmer::
# 474 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	trainerbattle_single TRAINER_MELEMELE_SWIMMER_1_HNS, Alola_Melemele_TrainerBattleSwimmer_Text_0, Alola_Melemele_TrainerBattleSwimmer_Text_1
# 475 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_TrainerBattleSwimmer_Text_2, MSGBOX_AUTOCLOSE
# 477 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_Bugcatcher::
# 482 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 483 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	faceplayer
# 484 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Bugcatcher_Text_0, MSGBOX_AUTOCLOSE
# 486 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_camper::
# 492 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 493 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	faceplayer
# 494 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_camper_Text_0, MSGBOX_AUTOCLOSE
# 496 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


Alola_Melemele_Picnicker::
# 502 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	lock
# 503 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	faceplayer
# 504 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	msgbox Alola_Melemele_Picnicker_Text_0, MSGBOX_AUTOCLOSE
# 509 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	release
	end


# 6 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
AlolaIslandMelemele_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0:
# 6 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	face_up
	step_end

# 15 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_GetOffBoat_Movement_0:
# 15 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	face_right
	step_end

# 16 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_GetOffBoat_Movement_1:
# 16 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	face_left
	step_end

# 38 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_TravelToKanto_Movement_0:
# 38 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_right
# 38 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
	step_end

# 42 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_TravelToKanto_Movement_1:
# 42 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 42 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_right
# 42 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_right
# 42 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
	step_end

# 46 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_TravelToKanto_Movement_2:
# 46 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	face_down
	step_end

# 55 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_TravelToKanto_Movement_3:
# 55 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
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

# 151 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_0:
# 151 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	emote_exclamation_mark
# 151 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	face_up
	step_end

# 153 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_1:
# 153 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
# 153 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
# 153 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
# 153 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
# 153 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_down
	step_end

# 156 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_2:
# 156 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_in_place_down
# 156 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_in_place_down
	step_end

# 162 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_3:
# 162 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_in_place_up
# 162 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_in_place_up
	step_end

# 173 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_4:
# 173 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	delay_16
# 173 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 173 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 173 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 173 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
# 173 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
	step_end

# 174 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_5:
# 174 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
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

# 186 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_6:
# 186 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	jump_in_place_down
# 186 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	jump_in_place_down
	step_end

# 221 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_SamsonOak_Trigger_Beginning_Movement_7:
# 221 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 221 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 221 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 221 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 221 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 221 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 221 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
# 221 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_left
	step_end

# 235 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_Melemele_NeedToTalkToSamsonOak_Movement_0:
# 235 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_up
	step_end

# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
Alola_MeleMele_TapuKoko_Flyover_Movement_0:
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
# 427 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	walk_faster_left
	step_end

Alola_Melemele_GetOffBoat_Text_0:
# 18 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Welcome back to the Isles!\p"
	.string "Come back if you'd like to take a trip\n"
	.string "to mainland Kanto!$"

Alola_Melemele_TravelToKanto_Text_0:
# 30 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Ahoy!\p"
	.string "Would you like to travel to mainland\n"
	.string "Kanto?$"

Alola_Melemele_TravelToKanto_Text_1:
# 35 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
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
	.string "Welcome to Melemele Isle!$"

Alola_Melemele_Pokecenter_Sign_Text_0:
# 95 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Welcome to the Melemele Isle\n"
	.string "Pokémon Center!\p"
	.string "This is the only Pokémon Center on the\n"
	.string "Alola Isles but you can rest on benches\l"
	.string "around the Isles.$"

Alola_Melemele_MelemeleMart_Sign_Text_0:
# 107 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Melemele Isle Mart$"

Alola_Melemele_BattleSandygast_Text_0:
# 116 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Gaaah!$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_0:
# 149 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "ALOLA!$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_1:
# 155 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Welcome to the Alola Isles!$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_2:
# 158 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "My name is Samson Oak!\n"
	.string "I'm a Pokémon Professor.\p"
	.string "What's your name?$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_3:
# 165 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Ah, {PLAYER}.\n"
	.string "A fine name!\p"
	.string "You may know my cousin, Professor Oak,\n"
	.string "from the Kanto region.\p"
	.string "Let me show you to town!$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_4:
# 179 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "This is the main town on these Islands.\p"
	.string "It's eerily similar to Hau'oli City in\n"
	.string "Alola… {PAUSE 30}And when I think about it…\p"
	.string "This whole island reminds me of Melemele\n"
	.string "Island…$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_5:
# 191 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Well, anyways!\p"
	.string "I research variations of Pokémon that \n"
	.string "can be found in different regions!\p"
	.string "On my way back from the Alola region,\n"
	.string "I stumbled across these isles…\p"
	.string "Surprisingly, many of the Pokémon I saw\n"
	.string "in Alola were here as well, so I've called\l"
	.string "this place… {PAUSE 30}the Alola Isles!$"

Alola_Melemele_SamsonOak_Trigger_Beginning_Text_6:
# 207 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
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
# 233 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Samson is waiting for you at his villa…\n"
	.string "{PAUSE 30}best not make him wait too long!$"

Alola_Melemele_TotemBattle_Text_0:
# 313 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Thhhh!$"

Alola_Melemele_TotemBattle_Text_1:
# 327 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Totem Gumshoos was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Melemele_TotemBattle_Text_2:
# 360 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Totem Raticate was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Melemele_Totem_sign_Text_0:
# 376 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "The totem is emanating a strong\n"
	.string "energy…\p"
	.string "Touch the totem to teleport to another\n"
	.string "Isle?$"

Alola_Melemele_Totem_sign_Text_1:
# 381 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Melemele Isle$"

Alola_Melemele_Totem_sign_Text_2:
# 381 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Akala Isle$"

Alola_Melemele_Totem_sign_Text_3:
# 381 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Ula'ula Isle$"

Alola_Melemele_Totem_sign_Text_4:
# 381 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Poni Isle$"

Alola_Melemele_Totem_sign_Text_5:
# 381 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Cancel$"

Alola_Melemele_Totem_sign_Text_6:
# 415 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "A strange totem stands here,\n"
	.string "power is emanating from it…$"

Alola_Melemele_BattleVsTapuKoko_Text_0:
# 444 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Ko-Ko-Kooo!$"

Alola_Melemele_TrainerBattleSwimmer_Text_0:
# 474 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "The waters are warm here by the Isles!$"

Alola_Melemele_TrainerBattleSwimmer_Text_1:
# 474 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "Maybe I should dry off on land for\na bit…$"

Alola_Melemele_TrainerBattleSwimmer_Text_2:
# 475 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "There are plenty of neat Pokémon in\n"
	.string "the water, try all your fishing rods!$"

Alola_Melemele_Bugcatcher_Text_0:
# 484 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "The bug Pokémon on the Alola Isles\n"
	.string "are much bigger than those in Kanto!$"

Alola_Melemele_camper_Text_0:
# 494 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "I traveled all the way from Kanto to see\n"
	.string "my favorite bird Pokémon, Pikipek!$"

Alola_Melemele_Picnicker_Text_0:
# 504 "data/maps/AlolaIslandMelemele_hns/scripts.pory"
	.string "These Isles are chock full of unique\n"
	.string "Pokémon!\p"
	.string "I need to stock up on Poké Balls so I\n"
	.string "can catch them all!$"
