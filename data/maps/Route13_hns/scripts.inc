Route13_hns_MapScripts::
# 3 "data/maps/Route13_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route13_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION
# 4 "data/maps/Route13_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, Route13_hns_MapScripts_MAP_SCRIPT_ON_RESUME
# 2 "data/maps/Route13_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route13_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
# 5 "data/maps/Route13_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, Route13_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE
	.byte 0

Route13_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION:
# 3 "data/maps/Route13_hns/scripts.pory"
	call Route13_OnTransition
	return

Route13_hns_MapScripts_MAP_SCRIPT_ON_RESUME:
# 4 "data/maps/Route13_hns/scripts.pory"
	call SetTimeEncounters
	return

Route13_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
# 2 "data/maps/Route13_hns/scripts.pory"
	map_script_2 VAR_ALOLA_TRAVEL, 2, Route13_GetOffBoat
	.2byte 0

Route13_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE:
# 5 "data/maps/Route13_hns/scripts.pory"
	map_script_2 VAR_ALOLA_TRAVEL, 2, Route13_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0
	.2byte 0

Route13_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0:
# 6 "data/maps/Route13_hns/scripts.pory"
	applymovement Route13_Alola_Captain, Route13_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0
# 7 "data/maps/Route13_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Route13_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0
	return


# 11 "data/maps/Route13_hns/scripts.pory"

# 12 "data/maps/Route13_hns/scripts.pory"
Route13_OnTransition:
# 13 "data/maps/Route13_hns/scripts.pory"
	callnative SetTimeBasedEncounters
# 14 "data/maps/Route13_hns/scripts.pory"
	end
# 15 "data/maps/Route13_hns/scripts.pory"

# 16 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_Alex::
# 17 "data/maps/Route13_hns/scripts.pory"
	trainerbattle_single TRAINER_ALEX_HNS, Route13_Text_PokefanmAlexSeen, Route13_Text_PokefanmAlexBeaten, Route13_EventScript_RegisterAlex
# 18 "data/maps/Route13_hns/scripts.pory"
	specialvar VAR_RESULT, ShouldTryRematchBattle
# 19 "data/maps/Route13_hns/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route13_EventScript_RematchAlex
# 20 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_PokefanmAlexAfterBattle, MSGBOX_AUTOCLOSE
# 21 "data/maps/Route13_hns/scripts.pory"
	end
# 22 "data/maps/Route13_hns/scripts.pory"

# 23 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_RegisterAlex::
# 24 "data/maps/Route13_hns/scripts.pory"
	special PlayerFaceTrainerAfterBattle
# 25 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
# 26 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_AlexRegister, MSGBOX_DEFAULT
# 27 "data/maps/Route13_hns/scripts.pory"
	register_matchcall TRAINER_ALEX_HNS
# 28 "data/maps/Route13_hns/scripts.pory"
	release
# 29 "data/maps/Route13_hns/scripts.pory"
	end
# 30 "data/maps/Route13_hns/scripts.pory"

# 31 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_RematchAlex::
# 32 "data/maps/Route13_hns/scripts.pory"
	trainerbattle_rematch TRAINER_ALEX_HNS, Route13_Text_AlexRematchIntro, Route13_Text_AlexRematchDefeat
# 33 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_AlexPostRematch, MSGBOX_AUTOCLOSE
# 34 "data/maps/Route13_hns/scripts.pory"
	end
# 35 "data/maps/Route13_hns/scripts.pory"

# 36 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_Joshua::
# 37 "data/maps/Route13_hns/scripts.pory"
	trainerbattle_single TRAINER_JOSHUA_HNS, Route13_Text_PokefanmJoshuaSeen, Route13_Text_PokefanmJoshuaBeaten
# 38 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_PokefanmJoshuaAfterBattle, MSGBOX_AUTOCLOSE
# 39 "data/maps/Route13_hns/scripts.pory"
	end
# 40 "data/maps/Route13_hns/scripts.pory"

# 41 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_Perry::
# 42 "data/maps/Route13_hns/scripts.pory"
	trainerbattle_single TRAINER_PERRY_HNS, Route13_Text_BirdKeeperPerrySeen, Route13_Text_BirdKeeperPerryBeaten
# 43 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_BirdKeeperPerryAfterBattle, MSGBOX_AUTOCLOSE
# 44 "data/maps/Route13_hns/scripts.pory"
	end
# 45 "data/maps/Route13_hns/scripts.pory"

# 46 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_Bret::
# 47 "data/maps/Route13_hns/scripts.pory"
	trainerbattle_single TRAINER_BRET_HNS, Route13_Text_BirdKeeperBretSeen, Route13_Text_BirdKeeperBretBeaten
# 48 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_BirdKeeperBretAfterBattle, MSGBOX_AUTOCLOSE
# 49 "data/maps/Route13_hns/scripts.pory"
	end
# 50 "data/maps/Route13_hns/scripts.pory"

# 51 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_Kenny::
# 52 "data/maps/Route13_hns/scripts.pory"
	trainerbattle_single TRAINER_KENNY_HNS, Route13_Text_HikerKennySeen, Route13_Text_HikerKennyBeaten, Route13_EventScript_RegisterKenny
# 53 "data/maps/Route13_hns/scripts.pory"
	specialvar VAR_RESULT, ShouldTryRematchBattle
# 54 "data/maps/Route13_hns/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route13_EventScript_RematchKenny
# 55 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_HikerKennyAfterBattle, MSGBOX_AUTOCLOSE
# 56 "data/maps/Route13_hns/scripts.pory"
	end
# 57 "data/maps/Route13_hns/scripts.pory"

# 58 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_RegisterKenny::
# 59 "data/maps/Route13_hns/scripts.pory"
	special PlayerFaceTrainerAfterBattle
# 60 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
# 61 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_KennyRegister, MSGBOX_DEFAULT
# 62 "data/maps/Route13_hns/scripts.pory"
	register_matchcall TRAINER_KENNY_HNS
# 63 "data/maps/Route13_hns/scripts.pory"
	release
# 64 "data/maps/Route13_hns/scripts.pory"
	end
# 65 "data/maps/Route13_hns/scripts.pory"

# 66 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_RematchKenny::
# 67 "data/maps/Route13_hns/scripts.pory"
	trainerbattle_rematch TRAINER_KENNY_HNS, Route13_Text_KennyRematchIntro, Route13_Text_KennyRematchDefeat
# 68 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_KennyPostRematch, MSGBOX_AUTOCLOSE
# 69 "data/maps/Route13_hns/scripts.pory"
	end
# 70 "data/maps/Route13_hns/scripts.pory"

# 71 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_TrainerTips::
# 72 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_TrainerTips, MSGBOX_SIGN
# 73 "data/maps/Route13_hns/scripts.pory"
	end
# 74 "data/maps/Route13_hns/scripts.pory"

# 75 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_RouteSign::
# 76 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_Sign, MSGBOX_SIGN
# 77 "data/maps/Route13_hns/scripts.pory"
	end
# 78 "data/maps/Route13_hns/scripts.pory"

# 79 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_DirectionsSign::
# 80 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_DirectionsSign, MSGBOX_SIGN
# 81 "data/maps/Route13_hns/scripts.pory"
	end
# 82 "data/maps/Route13_hns/scripts.pory"

# 83 "data/maps/Route13_hns/scripts.pory"
Route13_Text_PokefanmAlexSeen:
# 84 "data/maps/Route13_hns/scripts.pory"
	.string "Bow down before my regal POKéMON!$"
# 85 "data/maps/Route13_hns/scripts.pory"

# 86 "data/maps/Route13_hns/scripts.pory"
Route13_Text_PokefanmAlexBeaten:
# 87 "data/maps/Route13_hns/scripts.pory"
	.string "How… How dare you mock royalty!$"
# 88 "data/maps/Route13_hns/scripts.pory"

# 89 "data/maps/Route13_hns/scripts.pory"
Route13_Text_PokefanmAlexAfterBattle:
# 90 "data/maps/Route13_hns/scripts.pory"
	.string "Doesn't everyone wish to someday\n"
# 91 "data/maps/Route13_hns/scripts.pory"
	.string "be a king?$"
# 92 "data/maps/Route13_hns/scripts.pory"

# 93 "data/maps/Route13_hns/scripts.pory"
Route13_Text_AlexRegister:
# 94 "data/maps/Route13_hns/scripts.pory"
	.string "You're not royalty but you're good.\n"
# 95 "data/maps/Route13_hns/scripts.pory"
	.string "Let me get your number.$"
# 96 "data/maps/Route13_hns/scripts.pory"

# 97 "data/maps/Route13_hns/scripts.pory"
Route13_Text_AlexRematchIntro:
# 98 "data/maps/Route13_hns/scripts.pory"
	.string "I've added knights to my court!\n"
# 99 "data/maps/Route13_hns/scripts.pory"
	.string "Let's battle!$"
# 100 "data/maps/Route13_hns/scripts.pory"

# 101 "data/maps/Route13_hns/scripts.pory"
Route13_Text_AlexRematchDefeat:
# 102 "data/maps/Route13_hns/scripts.pory"
	.string "Dethroned again…$"
# 103 "data/maps/Route13_hns/scripts.pory"

# 104 "data/maps/Route13_hns/scripts.pory"
Route13_Text_AlexPostRematch:
# 105 "data/maps/Route13_hns/scripts.pory"
	.string "Maybe I'm just a pawn after all.$"
# 106 "data/maps/Route13_hns/scripts.pory"

# 107 "data/maps/Route13_hns/scripts.pory"
Route13_Text_PokefanmJoshuaSeen:
# 108 "data/maps/Route13_hns/scripts.pory"
	.string "Nihihi! Would you like to battle\n"
# 109 "data/maps/Route13_hns/scripts.pory"
	.string "my PIKACHU gang?$"
# 110 "data/maps/Route13_hns/scripts.pory"

# 111 "data/maps/Route13_hns/scripts.pory"
Route13_Text_PokefanmJoshuaBeaten:
# 112 "data/maps/Route13_hns/scripts.pory"
	.string "PI-PIKACHU!$"
# 113 "data/maps/Route13_hns/scripts.pory"

# 114 "data/maps/Route13_hns/scripts.pory"
Route13_Text_PokefanmJoshuaAfterBattle:
# 115 "data/maps/Route13_hns/scripts.pory"
	.string "You look like you have many\n"
# 116 "data/maps/Route13_hns/scripts.pory"
	.string "POKéMON, but PIKACHU\l"
# 117 "data/maps/Route13_hns/scripts.pory"
	.string "is still the best.$"
# 118 "data/maps/Route13_hns/scripts.pory"

# 119 "data/maps/Route13_hns/scripts.pory"
Route13_Text_BirdKeeperPerrySeen:
# 120 "data/maps/Route13_hns/scripts.pory"
	.string "Agility is the key attribute of\n"
# 121 "data/maps/Route13_hns/scripts.pory"
	.string "bird POKéMON.$"
# 122 "data/maps/Route13_hns/scripts.pory"

# 123 "data/maps/Route13_hns/scripts.pory"
Route13_Text_BirdKeeperPerryBeaten:
# 124 "data/maps/Route13_hns/scripts.pory"
	.string "You beat me with your speed…$"
# 125 "data/maps/Route13_hns/scripts.pory"

# 126 "data/maps/Route13_hns/scripts.pory"
Route13_Text_BirdKeeperPerryAfterBattle:
# 127 "data/maps/Route13_hns/scripts.pory"
	.string "Your POKéMON are remarkably well-\n"
# 128 "data/maps/Route13_hns/scripts.pory"
	.string "trained.$"
# 129 "data/maps/Route13_hns/scripts.pory"

# 130 "data/maps/Route13_hns/scripts.pory"
Route13_Text_BirdKeeperBretSeen:
# 131 "data/maps/Route13_hns/scripts.pory"
	.string "Check out my POKéMON. Just look\n"
# 132 "data/maps/Route13_hns/scripts.pory"
	.string "at their coloring and their\l"
# 133 "data/maps/Route13_hns/scripts.pory"
	.string "plumage.$"
# 134 "data/maps/Route13_hns/scripts.pory"

# 135 "data/maps/Route13_hns/scripts.pory"
Route13_Text_BirdKeeperBretBeaten:
# 136 "data/maps/Route13_hns/scripts.pory"
	.string "Shoot! Not good enough!$"
# 137 "data/maps/Route13_hns/scripts.pory"

# 138 "data/maps/Route13_hns/scripts.pory"
Route13_Text_BirdKeeperBretAfterBattle:
# 139 "data/maps/Route13_hns/scripts.pory"
	.string "If you groom them, POKéMON get\n"
# 140 "data/maps/Route13_hns/scripts.pory"
	.string "happy.$"
# 141 "data/maps/Route13_hns/scripts.pory"

# 142 "data/maps/Route13_hns/scripts.pory"
Route13_Text_HikerKennySeen:
# 143 "data/maps/Route13_hns/scripts.pory"
	.string "I should go to ROCK TUNNEL to get\n"
# 144 "data/maps/Route13_hns/scripts.pory"
	.string "myself an ONIX.$"
# 145 "data/maps/Route13_hns/scripts.pory"

# 146 "data/maps/Route13_hns/scripts.pory"
Route13_Text_HikerKennyBeaten:
# 147 "data/maps/Route13_hns/scripts.pory"
	.string "I lost…$"
# 148 "data/maps/Route13_hns/scripts.pory"

# 149 "data/maps/Route13_hns/scripts.pory"
Route13_Text_HikerKennyAfterBattle:
# 150 "data/maps/Route13_hns/scripts.pory"
	.string "Geological features don't appear\n"
# 151 "data/maps/Route13_hns/scripts.pory"
	.string "to change.\p"
# 152 "data/maps/Route13_hns/scripts.pory"
	.string "But they actually change, little\n"
# 153 "data/maps/Route13_hns/scripts.pory"
	.string "by little.$"
# 154 "data/maps/Route13_hns/scripts.pory"

# 155 "data/maps/Route13_hns/scripts.pory"
Route13_Text_KennyRegister:
# 156 "data/maps/Route13_hns/scripts.pory"
	.string "Maybe POKéMON change over time too.\n"
# 157 "data/maps/Route13_hns/scripts.pory"
	.string "Let's battle again sometime!$"
# 158 "data/maps/Route13_hns/scripts.pory"

# 159 "data/maps/Route13_hns/scripts.pory"
Route13_Text_KennyRematchIntro:
# 160 "data/maps/Route13_hns/scripts.pory"
	.string "I've learned from geology!\n"
# 161 "data/maps/Route13_hns/scripts.pory"
	.string "Let's go!$"
# 162 "data/maps/Route13_hns/scripts.pory"

# 163 "data/maps/Route13_hns/scripts.pory"
Route13_Text_KennyRematchDefeat:
# 164 "data/maps/Route13_hns/scripts.pory"
	.string "Still not enough…$"
# 165 "data/maps/Route13_hns/scripts.pory"

# 166 "data/maps/Route13_hns/scripts.pory"
Route13_Text_KennyPostRematch:
# 167 "data/maps/Route13_hns/scripts.pory"
	.string "The power of POKéMON is like\n"
# 168 "data/maps/Route13_hns/scripts.pory"
	.string "erosion. We will persevere!$"
# 169 "data/maps/Route13_hns/scripts.pory"

# 170 "data/maps/Route13_hns/scripts.pory"
Route13_Text_TrainerTips:
# 171 "data/maps/Route13_hns/scripts.pory"
	.string "TRAINER TIPS\p"
# 172 "data/maps/Route13_hns/scripts.pory"
	.string "Look! Right there, at the left\n"
# 173 "data/maps/Route13_hns/scripts.pory"
	.string "side of the post.$"
# 174 "data/maps/Route13_hns/scripts.pory"

# 175 "data/maps/Route13_hns/scripts.pory"
Route13_Text_Sign:
# 176 "data/maps/Route13_hns/scripts.pory"
	.string "ROUTE 13\p"
# 177 "data/maps/Route13_hns/scripts.pory"
	.string "NORTH TO SILENCE BRIDGE$"
# 178 "data/maps/Route13_hns/scripts.pory"

# 179 "data/maps/Route13_hns/scripts.pory"
Route13_Text_DirectionsSign:
# 180 "data/maps/Route13_hns/scripts.pory"
	.string "NORTH TO LAVENDER TOWN\p"
# 181 "data/maps/Route13_hns/scripts.pory"
	.string "WEST TO FUCHSIA CITY$"

Route13_GetOffBoat::
# 186 "data/maps/Route13_hns/scripts.pory"
	lock
# 187 "data/maps/Route13_hns/scripts.pory"
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
# 188 "data/maps/Route13_hns/scripts.pory"
	compare VAR_TEMP_0, 37
	goto_if_ne Route13_GetOffBoat_2
# 188 "data/maps/Route13_hns/scripts.pory"
	compare VAR_TEMP_1, 29
	goto_if_ne Route13_GetOffBoat_2
# 193 "data/maps/Route13_hns/scripts.pory"
	delay 30
# 194 "data/maps/Route13_hns/scripts.pory"
	applymovement Route13_Alola_Captain, Route13_GetOffBoat_Movement_0
# 195 "data/maps/Route13_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Route13_GetOffBoat_Movement_1
# 196 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
# 197 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_GetOffBoat_Text_0, MSGBOX_AUTOCLOSE
# 201 "data/maps/Route13_hns/scripts.pory"
	setvar VAR_ALOLA_TRAVEL, 0
# 202 "data/maps/Route13_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Route13_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0
# 203 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
# 204 "data/maps/Route13_hns/scripts.pory"
	release
	end

Route13_GetOffBoat_2:
# 189 "data/maps/Route13_hns/scripts.pory"
	setvar VAR_ALOLA_TRAVEL, 0
# 190 "data/maps/Route13_hns/scripts.pory"
	release
	end


Route13_TravelToAlola::
# 209 "data/maps/Route13_hns/scripts.pory"
	lock
# 210 "data/maps/Route13_hns/scripts.pory"
	faceplayer
	checkitem ITEM_STRANGE_SOUVENIR
# 0 "data/maps/Route13_hns/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_ne Route13_TravelToAlola_1
# 318 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_TravelToAlola_Text_4, MSGBOX_AUTOCLOSE
# 326 "data/maps/Route13_hns/scripts.pory"
	release
	end

Route13_TravelToAlola_1:
# 212 "data/maps/Route13_hns/scripts.pory"
	goto_if_unset FLAG_PREVIOUSLY_TRAVELED_TO_ALOLA, Route13_TravelToAlola_4
# 274 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_TravelToAlola_Text_3, MSGBOX_YESNO
# 276 "data/maps/Route13_hns/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Route13_TravelToAlola_10
# 310 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_TravelToAlola_Text_2, MSGBOX_AUTOCLOSE
# 312 "data/maps/Route13_hns/scripts.pory"
	release
	end

Route13_TravelToAlola_4:
# 213 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_TravelToAlola_Text_0, MSGBOX_YESNO
# 220 "data/maps/Route13_hns/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Route13_TravelToAlola_7
# 267 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_TravelToAlola_Text_2, MSGBOX_AUTOCLOSE
# 269 "data/maps/Route13_hns/scripts.pory"
	release
	end

Route13_TravelToAlola_7:
# 221 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_TravelToAlola_Text_1, MSGBOX_AUTOCLOSE
# 222 "data/maps/Route13_hns/scripts.pory"
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
# 223 "data/maps/Route13_hns/scripts.pory"
	compare VAR_TEMP_1, 28
	goto_if_eq Route13_TravelToAlola_14
Route13_TravelToAlola_13:
# 227 "data/maps/Route13_hns/scripts.pory"
	applymovement Route13_Alola_Captain, Route13_TravelToAlola_Movement_1
# 228 "data/maps/Route13_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Route13_TravelToAlola_Movement_1
# 229 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
# 230 "data/maps/Route13_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 231 "data/maps/Route13_hns/scripts.pory"
	hidefollower
# 232 "data/maps/Route13_hns/scripts.pory"
	playse SE_EXIT
# 233 "data/maps/Route13_hns/scripts.pory"
	special SpawnCameraObject
# 234 "data/maps/Route13_hns/scripts.pory"
	hideobjectat LOCALID_PLAYER, MAP_ROUTE13_HNS
# 235 "data/maps/Route13_hns/scripts.pory"
	hideobjectat Route13_Alola_Captain, MAP_ROUTE13_HNS
# 236 "data/maps/Route13_hns/scripts.pory"
	applymovement OBJ_EVENT_ID_CAMERA, Route13_TravelToAlola_Movement_1
# 237 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
# 238 "data/maps/Route13_hns/scripts.pory"
	waitse
# 239 "data/maps/Route13_hns/scripts.pory"
	delay 30
# 240 "data/maps/Route13_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 241 "data/maps/Route13_hns/scripts.pory"
	playse SE_RG_SS_ANNE_HORN
# 242 "data/maps/Route13_hns/scripts.pory"
	waitse
# 243 "data/maps/Route13_hns/scripts.pory"
	playse SE_M_SURF
# 244 "data/maps/Route13_hns/scripts.pory"
	applymovement Route13_Alola_Ship, Route13_TravelToAlola_Movement_2
# 245 "data/maps/Route13_hns/scripts.pory"
	setvar VAR_ALOLA_TRAVEL, 1
# 246 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_PREVIOUSLY_TRAVELED_TO_ALOLA
# 247 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_MELEMELE_TOTEM
# 248 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_AKALA_TOTEM
# 249 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_ULAULA_TOTEM
# 250 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_PONI_TOTEM
# 251 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_SAMSONOAK_INTRO
# 252 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_KOKO
# 253 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_LELE
# 254 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_BULU
# 255 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_FINI
# 256 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_FLYOVER
# 257 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_PHANT_OUTSIDE
# 258 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_PHANT_INSIDE
# 259 "data/maps/Route13_hns/scripts.pory"
	delay 90
# 260 "data/maps/Route13_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 261 "data/maps/Route13_hns/scripts.pory"
	special RemoveCameraObject
# 262 "data/maps/Route13_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_MELEMELE_HNS, 25, 33
# 263 "data/maps/Route13_hns/scripts.pory"
	waitstate
	end

Route13_TravelToAlola_10:
# 277 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_TravelToAlola_Text_1, MSGBOX_AUTOCLOSE
# 278 "data/maps/Route13_hns/scripts.pory"
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
# 279 "data/maps/Route13_hns/scripts.pory"
	compare VAR_TEMP_1, 28
	goto_if_eq Route13_TravelToAlola_17
Route13_TravelToAlola_16:
# 283 "data/maps/Route13_hns/scripts.pory"
	applymovement Route13_Alola_Captain, Route13_TravelToAlola_Movement_1
# 284 "data/maps/Route13_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Route13_TravelToAlola_Movement_1
# 285 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
# 286 "data/maps/Route13_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 287 "data/maps/Route13_hns/scripts.pory"
	hidefollower
# 288 "data/maps/Route13_hns/scripts.pory"
	playse SE_EXIT
# 289 "data/maps/Route13_hns/scripts.pory"
	special SpawnCameraObject
# 290 "data/maps/Route13_hns/scripts.pory"
	hideobjectat LOCALID_PLAYER, MAP_ROUTE13_HNS
# 291 "data/maps/Route13_hns/scripts.pory"
	hideobjectat Route13_Alola_Captain, MAP_ROUTE13_HNS
# 292 "data/maps/Route13_hns/scripts.pory"
	applymovement OBJ_EVENT_ID_CAMERA, Route13_TravelToAlola_Movement_1
# 293 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
# 294 "data/maps/Route13_hns/scripts.pory"
	waitse
# 295 "data/maps/Route13_hns/scripts.pory"
	delay 30
# 296 "data/maps/Route13_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 297 "data/maps/Route13_hns/scripts.pory"
	playse SE_RG_SS_ANNE_HORN
# 298 "data/maps/Route13_hns/scripts.pory"
	waitse
# 299 "data/maps/Route13_hns/scripts.pory"
	playse SE_M_SURF
# 300 "data/maps/Route13_hns/scripts.pory"
	applymovement Route13_Alola_Ship, Route13_TravelToAlola_Movement_2
# 301 "data/maps/Route13_hns/scripts.pory"
	setvar VAR_ALOLA_TRAVEL, 1
# 302 "data/maps/Route13_hns/scripts.pory"
	delay 90
# 303 "data/maps/Route13_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 304 "data/maps/Route13_hns/scripts.pory"
	special RemoveCameraObject
# 305 "data/maps/Route13_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_MELEMELE_HNS, 25, 33
# 306 "data/maps/Route13_hns/scripts.pory"
	waitstate
	end

Route13_TravelToAlola_14:
# 224 "data/maps/Route13_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Route13_TravelToAlola_Movement_0
# 225 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
	goto Route13_TravelToAlola_13

Route13_TravelToAlola_17:
# 280 "data/maps/Route13_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Route13_TravelToAlola_Movement_0
# 281 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
	goto Route13_TravelToAlola_16


# 6 "data/maps/Route13_hns/scripts.pory"
Route13_hns_MapScripts_MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE_0_Movement_0:
# 6 "data/maps/Route13_hns/scripts.pory"
	face_up
	step_end

# 194 "data/maps/Route13_hns/scripts.pory"
Route13_GetOffBoat_Movement_0:
# 194 "data/maps/Route13_hns/scripts.pory"
	face_left
	step_end

# 195 "data/maps/Route13_hns/scripts.pory"
Route13_GetOffBoat_Movement_1:
# 195 "data/maps/Route13_hns/scripts.pory"
	face_right
	step_end

# 224 "data/maps/Route13_hns/scripts.pory"
Route13_TravelToAlola_Movement_0:
# 224 "data/maps/Route13_hns/scripts.pory"
	walk_left
# 224 "data/maps/Route13_hns/scripts.pory"
	walk_down
	step_end

# 227 "data/maps/Route13_hns/scripts.pory"
Route13_TravelToAlola_Movement_1:
# 227 "data/maps/Route13_hns/scripts.pory"
	walk_down
	step_end

# 244 "data/maps/Route13_hns/scripts.pory"
Route13_TravelToAlola_Movement_2:
# 244 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 244 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 244 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 244 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 244 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 244 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 244 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 244 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 244 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 244 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 244 "data/maps/Route13_hns/scripts.pory"
	walk_right
	step_end

Route13_GetOffBoat_Text_0:
# 197 "data/maps/Route13_hns/scripts.pory"
	.string "Welcome back to mainland Kanto!\p"
	.string "Come back if you'd like to take a trip\n"
	.string "to the Alola Isles!$"

Route13_TravelToAlola_Text_0:
# 213 "data/maps/Route13_hns/scripts.pory"
	.string "Ahoy there!\p"
	.string "That's one strange souvenir.\n"
	.string "You must be from the Isles!\p"
	.string "Would you like to take the next ship?\n"
	.string "It departs shortly!$"

Route13_TravelToAlola_Text_1:
# 221 "data/maps/Route13_hns/scripts.pory"
	.string "Ahoy! Let's get you on board!$"

Route13_TravelToAlola_Text_2:
# 267 "data/maps/Route13_hns/scripts.pory"
	.string "Ahoy!\n"
	.string "Come back when you'd like to set sail.$"

Route13_TravelToAlola_Text_3:
# 274 "data/maps/Route13_hns/scripts.pory"
	.string "Ah, its you again!\n"
	.string "Do you want to go to the Alola Isles?$"

Route13_TravelToAlola_Text_4:
# 318 "data/maps/Route13_hns/scripts.pory"
	.string "Ahoy!\n"
	.string "This ship is for residents only.\p"
	.string "All of the residents of these Isles\n"
	.string "carry some… {PAUSE 30}strange souvenirs.\p"
	.string "It makes them so easy to identify,\n"
	.string "I don't even need to check tickets!$"
