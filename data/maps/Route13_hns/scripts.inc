Route13_hns_MapScripts::
# 3 "data/maps/Route13_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route13_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION
# 4 "data/maps/Route13_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, Route13_hns_MapScripts_MAP_SCRIPT_ON_RESUME
# 2 "data/maps/Route13_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route13_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
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


# 7 "data/maps/Route13_hns/scripts.pory"

# 8 "data/maps/Route13_hns/scripts.pory"
Route13_OnTransition:
# 9 "data/maps/Route13_hns/scripts.pory"
	callnative SetTimeBasedEncounters
# 10 "data/maps/Route13_hns/scripts.pory"
	end
# 11 "data/maps/Route13_hns/scripts.pory"

# 12 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_Alex::
# 13 "data/maps/Route13_hns/scripts.pory"
	trainerbattle_single TRAINER_ALEX_HNS, Route13_Text_PokefanmAlexSeen, Route13_Text_PokefanmAlexBeaten, Route13_EventScript_RegisterAlex
# 14 "data/maps/Route13_hns/scripts.pory"
	specialvar VAR_RESULT, ShouldTryRematchBattle
# 15 "data/maps/Route13_hns/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route13_EventScript_RematchAlex
# 16 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_PokefanmAlexAfterBattle, MSGBOX_AUTOCLOSE
# 17 "data/maps/Route13_hns/scripts.pory"
	end
# 18 "data/maps/Route13_hns/scripts.pory"

# 19 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_RegisterAlex::
# 20 "data/maps/Route13_hns/scripts.pory"
	special PlayerFaceTrainerAfterBattle
# 21 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
# 22 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_AlexRegister, MSGBOX_DEFAULT
# 23 "data/maps/Route13_hns/scripts.pory"
	register_matchcall TRAINER_ALEX_HNS
# 24 "data/maps/Route13_hns/scripts.pory"
	release
# 25 "data/maps/Route13_hns/scripts.pory"
	end
# 26 "data/maps/Route13_hns/scripts.pory"

# 27 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_RematchAlex::
# 28 "data/maps/Route13_hns/scripts.pory"
	trainerbattle_rematch TRAINER_ALEX_HNS, Route13_Text_AlexRematchIntro, Route13_Text_AlexRematchDefeat
# 29 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_AlexPostRematch, MSGBOX_AUTOCLOSE
# 30 "data/maps/Route13_hns/scripts.pory"
	end
# 31 "data/maps/Route13_hns/scripts.pory"

# 32 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_Joshua::
# 33 "data/maps/Route13_hns/scripts.pory"
	trainerbattle_single TRAINER_JOSHUA_HNS, Route13_Text_PokefanmJoshuaSeen, Route13_Text_PokefanmJoshuaBeaten
# 34 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_PokefanmJoshuaAfterBattle, MSGBOX_AUTOCLOSE
# 35 "data/maps/Route13_hns/scripts.pory"
	end
# 36 "data/maps/Route13_hns/scripts.pory"

# 37 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_Perry::
# 38 "data/maps/Route13_hns/scripts.pory"
	trainerbattle_single TRAINER_PERRY_HNS, Route13_Text_BirdKeeperPerrySeen, Route13_Text_BirdKeeperPerryBeaten
# 39 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_BirdKeeperPerryAfterBattle, MSGBOX_AUTOCLOSE
# 40 "data/maps/Route13_hns/scripts.pory"
	end
# 41 "data/maps/Route13_hns/scripts.pory"

# 42 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_Bret::
# 43 "data/maps/Route13_hns/scripts.pory"
	trainerbattle_single TRAINER_BRET_HNS, Route13_Text_BirdKeeperBretSeen, Route13_Text_BirdKeeperBretBeaten
# 44 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_BirdKeeperBretAfterBattle, MSGBOX_AUTOCLOSE
# 45 "data/maps/Route13_hns/scripts.pory"
	end
# 46 "data/maps/Route13_hns/scripts.pory"

# 47 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_Kenny::
# 48 "data/maps/Route13_hns/scripts.pory"
	trainerbattle_single TRAINER_KENNY_HNS, Route13_Text_HikerKennySeen, Route13_Text_HikerKennyBeaten, Route13_EventScript_RegisterKenny
# 49 "data/maps/Route13_hns/scripts.pory"
	specialvar VAR_RESULT, ShouldTryRematchBattle
# 50 "data/maps/Route13_hns/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route13_EventScript_RematchKenny
# 51 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_HikerKennyAfterBattle, MSGBOX_AUTOCLOSE
# 52 "data/maps/Route13_hns/scripts.pory"
	end
# 53 "data/maps/Route13_hns/scripts.pory"

# 54 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_RegisterKenny::
# 55 "data/maps/Route13_hns/scripts.pory"
	special PlayerFaceTrainerAfterBattle
# 56 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
# 57 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_KennyRegister, MSGBOX_DEFAULT
# 58 "data/maps/Route13_hns/scripts.pory"
	register_matchcall TRAINER_KENNY_HNS
# 59 "data/maps/Route13_hns/scripts.pory"
	release
# 60 "data/maps/Route13_hns/scripts.pory"
	end
# 61 "data/maps/Route13_hns/scripts.pory"

# 62 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_RematchKenny::
# 63 "data/maps/Route13_hns/scripts.pory"
	trainerbattle_rematch TRAINER_KENNY_HNS, Route13_Text_KennyRematchIntro, Route13_Text_KennyRematchDefeat
# 64 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_KennyPostRematch, MSGBOX_AUTOCLOSE
# 65 "data/maps/Route13_hns/scripts.pory"
	end
# 66 "data/maps/Route13_hns/scripts.pory"

# 67 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_TrainerTips::
# 68 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_TrainerTips, MSGBOX_SIGN
# 69 "data/maps/Route13_hns/scripts.pory"
	end
# 70 "data/maps/Route13_hns/scripts.pory"

# 71 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_RouteSign::
# 72 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_Sign, MSGBOX_SIGN
# 73 "data/maps/Route13_hns/scripts.pory"
	end
# 74 "data/maps/Route13_hns/scripts.pory"

# 75 "data/maps/Route13_hns/scripts.pory"
Route13_EventScript_DirectionsSign::
# 76 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_Text_DirectionsSign, MSGBOX_SIGN
# 77 "data/maps/Route13_hns/scripts.pory"
	end
# 78 "data/maps/Route13_hns/scripts.pory"

# 79 "data/maps/Route13_hns/scripts.pory"
Route13_Text_PokefanmAlexSeen:
# 80 "data/maps/Route13_hns/scripts.pory"
	.string "Bow down before my regal POKéMON!$"
# 81 "data/maps/Route13_hns/scripts.pory"

# 82 "data/maps/Route13_hns/scripts.pory"
Route13_Text_PokefanmAlexBeaten:
# 83 "data/maps/Route13_hns/scripts.pory"
	.string "How… How dare you mock royalty!$"
# 84 "data/maps/Route13_hns/scripts.pory"

# 85 "data/maps/Route13_hns/scripts.pory"
Route13_Text_PokefanmAlexAfterBattle:
# 86 "data/maps/Route13_hns/scripts.pory"
	.string "Doesn't everyone wish to someday\n"
# 87 "data/maps/Route13_hns/scripts.pory"
	.string "be a king?$"
# 88 "data/maps/Route13_hns/scripts.pory"

# 89 "data/maps/Route13_hns/scripts.pory"
Route13_Text_AlexRegister:
# 90 "data/maps/Route13_hns/scripts.pory"
	.string "You're not royalty but you're good.\n"
# 91 "data/maps/Route13_hns/scripts.pory"
	.string "Let me get your number.$"
# 92 "data/maps/Route13_hns/scripts.pory"

# 93 "data/maps/Route13_hns/scripts.pory"
Route13_Text_AlexRematchIntro:
# 94 "data/maps/Route13_hns/scripts.pory"
	.string "I've added knights to my court!\n"
# 95 "data/maps/Route13_hns/scripts.pory"
	.string "Let's battle!$"
# 96 "data/maps/Route13_hns/scripts.pory"

# 97 "data/maps/Route13_hns/scripts.pory"
Route13_Text_AlexRematchDefeat:
# 98 "data/maps/Route13_hns/scripts.pory"
	.string "Dethroned again…$"
# 99 "data/maps/Route13_hns/scripts.pory"

# 100 "data/maps/Route13_hns/scripts.pory"
Route13_Text_AlexPostRematch:
# 101 "data/maps/Route13_hns/scripts.pory"
	.string "Maybe I'm just a pawn after all.$"
# 102 "data/maps/Route13_hns/scripts.pory"

# 103 "data/maps/Route13_hns/scripts.pory"
Route13_Text_PokefanmJoshuaSeen:
# 104 "data/maps/Route13_hns/scripts.pory"
	.string "Nihihi! Would you like to battle\n"
# 105 "data/maps/Route13_hns/scripts.pory"
	.string "my PIKACHU gang?$"
# 106 "data/maps/Route13_hns/scripts.pory"

# 107 "data/maps/Route13_hns/scripts.pory"
Route13_Text_PokefanmJoshuaBeaten:
# 108 "data/maps/Route13_hns/scripts.pory"
	.string "PI-PIKACHU!$"
# 109 "data/maps/Route13_hns/scripts.pory"

# 110 "data/maps/Route13_hns/scripts.pory"
Route13_Text_PokefanmJoshuaAfterBattle:
# 111 "data/maps/Route13_hns/scripts.pory"
	.string "You look like you have many\n"
# 112 "data/maps/Route13_hns/scripts.pory"
	.string "POKéMON, but PIKACHU\l"
# 113 "data/maps/Route13_hns/scripts.pory"
	.string "is still the best.$"
# 114 "data/maps/Route13_hns/scripts.pory"

# 115 "data/maps/Route13_hns/scripts.pory"
Route13_Text_BirdKeeperPerrySeen:
# 116 "data/maps/Route13_hns/scripts.pory"
	.string "Agility is the key attribute of\n"
# 117 "data/maps/Route13_hns/scripts.pory"
	.string "bird POKéMON.$"
# 118 "data/maps/Route13_hns/scripts.pory"

# 119 "data/maps/Route13_hns/scripts.pory"
Route13_Text_BirdKeeperPerryBeaten:
# 120 "data/maps/Route13_hns/scripts.pory"
	.string "You beat me with your speed…$"
# 121 "data/maps/Route13_hns/scripts.pory"

# 122 "data/maps/Route13_hns/scripts.pory"
Route13_Text_BirdKeeperPerryAfterBattle:
# 123 "data/maps/Route13_hns/scripts.pory"
	.string "Your POKéMON are remarkably well-\n"
# 124 "data/maps/Route13_hns/scripts.pory"
	.string "trained.$"
# 125 "data/maps/Route13_hns/scripts.pory"

# 126 "data/maps/Route13_hns/scripts.pory"
Route13_Text_BirdKeeperBretSeen:
# 127 "data/maps/Route13_hns/scripts.pory"
	.string "Check out my POKéMON. Just look\n"
# 128 "data/maps/Route13_hns/scripts.pory"
	.string "at their coloring and their\l"
# 129 "data/maps/Route13_hns/scripts.pory"
	.string "plumage.$"
# 130 "data/maps/Route13_hns/scripts.pory"

# 131 "data/maps/Route13_hns/scripts.pory"
Route13_Text_BirdKeeperBretBeaten:
# 132 "data/maps/Route13_hns/scripts.pory"
	.string "Shoot! Not good enough!$"
# 133 "data/maps/Route13_hns/scripts.pory"

# 134 "data/maps/Route13_hns/scripts.pory"
Route13_Text_BirdKeeperBretAfterBattle:
# 135 "data/maps/Route13_hns/scripts.pory"
	.string "If you groom them, POKéMON get\n"
# 136 "data/maps/Route13_hns/scripts.pory"
	.string "happy.$"
# 137 "data/maps/Route13_hns/scripts.pory"

# 138 "data/maps/Route13_hns/scripts.pory"
Route13_Text_HikerKennySeen:
# 139 "data/maps/Route13_hns/scripts.pory"
	.string "I should go to ROCK TUNNEL to get\n"
# 140 "data/maps/Route13_hns/scripts.pory"
	.string "myself an ONIX.$"
# 141 "data/maps/Route13_hns/scripts.pory"

# 142 "data/maps/Route13_hns/scripts.pory"
Route13_Text_HikerKennyBeaten:
# 143 "data/maps/Route13_hns/scripts.pory"
	.string "I lost…$"
# 144 "data/maps/Route13_hns/scripts.pory"

# 145 "data/maps/Route13_hns/scripts.pory"
Route13_Text_HikerKennyAfterBattle:
# 146 "data/maps/Route13_hns/scripts.pory"
	.string "Geological features don't appear\n"
# 147 "data/maps/Route13_hns/scripts.pory"
	.string "to change.\p"
# 148 "data/maps/Route13_hns/scripts.pory"
	.string "But they actually change, little\n"
# 149 "data/maps/Route13_hns/scripts.pory"
	.string "by little.$"
# 150 "data/maps/Route13_hns/scripts.pory"

# 151 "data/maps/Route13_hns/scripts.pory"
Route13_Text_KennyRegister:
# 152 "data/maps/Route13_hns/scripts.pory"
	.string "Maybe POKéMON change over time too.\n"
# 153 "data/maps/Route13_hns/scripts.pory"
	.string "Let's battle again sometime!$"
# 154 "data/maps/Route13_hns/scripts.pory"

# 155 "data/maps/Route13_hns/scripts.pory"
Route13_Text_KennyRematchIntro:
# 156 "data/maps/Route13_hns/scripts.pory"
	.string "I've learned from geology!\n"
# 157 "data/maps/Route13_hns/scripts.pory"
	.string "Let's go!$"
# 158 "data/maps/Route13_hns/scripts.pory"

# 159 "data/maps/Route13_hns/scripts.pory"
Route13_Text_KennyRematchDefeat:
# 160 "data/maps/Route13_hns/scripts.pory"
	.string "Still not enough…$"
# 161 "data/maps/Route13_hns/scripts.pory"

# 162 "data/maps/Route13_hns/scripts.pory"
Route13_Text_KennyPostRematch:
# 163 "data/maps/Route13_hns/scripts.pory"
	.string "The power of POKéMON is like\n"
# 164 "data/maps/Route13_hns/scripts.pory"
	.string "erosion. We will persevere!$"
# 165 "data/maps/Route13_hns/scripts.pory"

# 166 "data/maps/Route13_hns/scripts.pory"
Route13_Text_TrainerTips:
# 167 "data/maps/Route13_hns/scripts.pory"
	.string "TRAINER TIPS\p"
# 168 "data/maps/Route13_hns/scripts.pory"
	.string "Look! Right there, at the left\n"
# 169 "data/maps/Route13_hns/scripts.pory"
	.string "side of the post.$"
# 170 "data/maps/Route13_hns/scripts.pory"

# 171 "data/maps/Route13_hns/scripts.pory"
Route13_Text_Sign:
# 172 "data/maps/Route13_hns/scripts.pory"
	.string "ROUTE 13\p"
# 173 "data/maps/Route13_hns/scripts.pory"
	.string "NORTH TO SILENCE BRIDGE$"
# 174 "data/maps/Route13_hns/scripts.pory"

# 175 "data/maps/Route13_hns/scripts.pory"
Route13_Text_DirectionsSign:
# 176 "data/maps/Route13_hns/scripts.pory"
	.string "NORTH TO LAVENDER TOWN\p"
# 177 "data/maps/Route13_hns/scripts.pory"
	.string "WEST TO FUCHSIA CITY$"

Route13_GetOffBoat::
# 182 "data/maps/Route13_hns/scripts.pory"
	lock
# 183 "data/maps/Route13_hns/scripts.pory"
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
# 184 "data/maps/Route13_hns/scripts.pory"
	compare VAR_TEMP_0, 37
	goto_if_ne Route13_GetOffBoat_2
# 184 "data/maps/Route13_hns/scripts.pory"
	compare VAR_TEMP_1, 29
	goto_if_ne Route13_GetOffBoat_2
# 189 "data/maps/Route13_hns/scripts.pory"
	delay 30
# 190 "data/maps/Route13_hns/scripts.pory"
	applymovement Route13_Alola_Captain, Route13_GetOffBoat_Movement_0
# 191 "data/maps/Route13_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Route13_GetOffBoat_Movement_1
# 192 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
# 193 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_GetOffBoat_Text_0, MSGBOX_AUTOCLOSE
# 197 "data/maps/Route13_hns/scripts.pory"
	setvar VAR_ALOLA_TRAVEL, 0
# 198 "data/maps/Route13_hns/scripts.pory"
	release
	end

Route13_GetOffBoat_2:
# 185 "data/maps/Route13_hns/scripts.pory"
	setvar VAR_ALOLA_TRAVEL, 0
# 186 "data/maps/Route13_hns/scripts.pory"
	release
	end


Route13_TravelToAlola::
# 203 "data/maps/Route13_hns/scripts.pory"
	lock
# 204 "data/maps/Route13_hns/scripts.pory"
	faceplayer
	checkitem ITEM_STRANGE_SOUVENIR
# 0 "data/maps/Route13_hns/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_ne Route13_TravelToAlola_1
# 312 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_TravelToAlola_Text_4, MSGBOX_AUTOCLOSE
# 320 "data/maps/Route13_hns/scripts.pory"
	release
	end

Route13_TravelToAlola_1:
# 206 "data/maps/Route13_hns/scripts.pory"
	goto_if_unset FLAG_PREVIOUSLY_TRAVELED_TO_ALOLA, Route13_TravelToAlola_4
# 268 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_TravelToAlola_Text_3, MSGBOX_YESNO
# 270 "data/maps/Route13_hns/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Route13_TravelToAlola_10
# 304 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_TravelToAlola_Text_2, MSGBOX_AUTOCLOSE
# 306 "data/maps/Route13_hns/scripts.pory"
	release
	end

Route13_TravelToAlola_4:
# 207 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_TravelToAlola_Text_0, MSGBOX_YESNO
# 214 "data/maps/Route13_hns/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq Route13_TravelToAlola_7
# 261 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_TravelToAlola_Text_2, MSGBOX_AUTOCLOSE
# 263 "data/maps/Route13_hns/scripts.pory"
	release
	end

Route13_TravelToAlola_7:
# 215 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_TravelToAlola_Text_1, MSGBOX_AUTOCLOSE
# 216 "data/maps/Route13_hns/scripts.pory"
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
# 217 "data/maps/Route13_hns/scripts.pory"
	compare VAR_TEMP_1, 28
	goto_if_eq Route13_TravelToAlola_14
Route13_TravelToAlola_13:
# 221 "data/maps/Route13_hns/scripts.pory"
	applymovement Route13_Alola_Captain, Route13_TravelToAlola_Movement_1
# 222 "data/maps/Route13_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Route13_TravelToAlola_Movement_1
# 223 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
# 224 "data/maps/Route13_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 225 "data/maps/Route13_hns/scripts.pory"
	hidefollower
# 226 "data/maps/Route13_hns/scripts.pory"
	playse SE_EXIT
# 227 "data/maps/Route13_hns/scripts.pory"
	special SpawnCameraObject
# 228 "data/maps/Route13_hns/scripts.pory"
	hideobjectat LOCALID_PLAYER, MAP_ROUTE13_HNS
# 229 "data/maps/Route13_hns/scripts.pory"
	hideobjectat Route13_Alola_Captain, MAP_ROUTE13_HNS
# 230 "data/maps/Route13_hns/scripts.pory"
	applymovement OBJ_EVENT_ID_CAMERA, Route13_TravelToAlola_Movement_1
# 231 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
# 232 "data/maps/Route13_hns/scripts.pory"
	waitse
# 233 "data/maps/Route13_hns/scripts.pory"
	delay 30
# 234 "data/maps/Route13_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 235 "data/maps/Route13_hns/scripts.pory"
	playse SE_RG_SS_ANNE_HORN
# 236 "data/maps/Route13_hns/scripts.pory"
	waitse
# 237 "data/maps/Route13_hns/scripts.pory"
	playse SE_M_SURF
# 238 "data/maps/Route13_hns/scripts.pory"
	applymovement Route13_Alola_Ship, Route13_TravelToAlola_Movement_2
# 239 "data/maps/Route13_hns/scripts.pory"
	setvar VAR_ALOLA_TRAVEL, 1
# 240 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_PREVIOUSLY_TRAVELED_TO_ALOLA
# 241 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_MELEMELE_TOTEM
# 242 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_AKALA_TOTEM
# 243 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_ULAULA_TOTEM
# 244 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_PONI_TOTEM
# 245 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_SAMSONOAK_INTRO
# 246 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_KOKO
# 247 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_LELE
# 248 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_BULU
# 249 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_FINI
# 250 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_FLYOVER
# 251 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_PHANT_OUTSIDE
# 252 "data/maps/Route13_hns/scripts.pory"
	setflag FLAG_HIDE_PHANT_INSIDE
# 253 "data/maps/Route13_hns/scripts.pory"
	delay 90
# 254 "data/maps/Route13_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 255 "data/maps/Route13_hns/scripts.pory"
	special RemoveCameraObject
# 256 "data/maps/Route13_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_MELEMELE_HNS, 25, 33
# 257 "data/maps/Route13_hns/scripts.pory"
	waitstate
	end

Route13_TravelToAlola_10:
# 271 "data/maps/Route13_hns/scripts.pory"
	msgbox Route13_TravelToAlola_Text_1, MSGBOX_AUTOCLOSE
# 272 "data/maps/Route13_hns/scripts.pory"
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
# 273 "data/maps/Route13_hns/scripts.pory"
	compare VAR_TEMP_1, 28
	goto_if_eq Route13_TravelToAlola_17
Route13_TravelToAlola_16:
# 277 "data/maps/Route13_hns/scripts.pory"
	applymovement Route13_Alola_Captain, Route13_TravelToAlola_Movement_1
# 278 "data/maps/Route13_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Route13_TravelToAlola_Movement_1
# 279 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
# 280 "data/maps/Route13_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 281 "data/maps/Route13_hns/scripts.pory"
	hidefollower
# 282 "data/maps/Route13_hns/scripts.pory"
	playse SE_EXIT
# 283 "data/maps/Route13_hns/scripts.pory"
	special SpawnCameraObject
# 284 "data/maps/Route13_hns/scripts.pory"
	hideobjectat LOCALID_PLAYER, MAP_ROUTE13_HNS
# 285 "data/maps/Route13_hns/scripts.pory"
	hideobjectat Route13_Alola_Captain, MAP_ROUTE13_HNS
# 286 "data/maps/Route13_hns/scripts.pory"
	applymovement OBJ_EVENT_ID_CAMERA, Route13_TravelToAlola_Movement_1
# 287 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
# 288 "data/maps/Route13_hns/scripts.pory"
	waitse
# 289 "data/maps/Route13_hns/scripts.pory"
	delay 30
# 290 "data/maps/Route13_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 291 "data/maps/Route13_hns/scripts.pory"
	playse SE_RG_SS_ANNE_HORN
# 292 "data/maps/Route13_hns/scripts.pory"
	waitse
# 293 "data/maps/Route13_hns/scripts.pory"
	playse SE_M_SURF
# 294 "data/maps/Route13_hns/scripts.pory"
	applymovement Route13_Alola_Ship, Route13_TravelToAlola_Movement_2
# 295 "data/maps/Route13_hns/scripts.pory"
	setvar VAR_ALOLA_TRAVEL, 1
# 296 "data/maps/Route13_hns/scripts.pory"
	delay 90
# 297 "data/maps/Route13_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 298 "data/maps/Route13_hns/scripts.pory"
	special RemoveCameraObject
# 299 "data/maps/Route13_hns/scripts.pory"
	warp MAP_ALOLA_ISLAND_MELEMELE_HNS, 25, 33
# 300 "data/maps/Route13_hns/scripts.pory"
	waitstate
	end

Route13_TravelToAlola_14:
# 218 "data/maps/Route13_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Route13_TravelToAlola_Movement_0
# 219 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
	goto Route13_TravelToAlola_13

Route13_TravelToAlola_17:
# 274 "data/maps/Route13_hns/scripts.pory"
	applymovement LOCALID_PLAYER, Route13_TravelToAlola_Movement_0
# 275 "data/maps/Route13_hns/scripts.pory"
	waitmovement 0
	goto Route13_TravelToAlola_16


# 190 "data/maps/Route13_hns/scripts.pory"
Route13_GetOffBoat_Movement_0:
# 190 "data/maps/Route13_hns/scripts.pory"
	face_left
	step_end

# 191 "data/maps/Route13_hns/scripts.pory"
Route13_GetOffBoat_Movement_1:
# 191 "data/maps/Route13_hns/scripts.pory"
	face_right
	step_end

# 218 "data/maps/Route13_hns/scripts.pory"
Route13_TravelToAlola_Movement_0:
# 218 "data/maps/Route13_hns/scripts.pory"
	walk_left
# 218 "data/maps/Route13_hns/scripts.pory"
	walk_down
	step_end

# 221 "data/maps/Route13_hns/scripts.pory"
Route13_TravelToAlola_Movement_1:
# 221 "data/maps/Route13_hns/scripts.pory"
	walk_down
	step_end

# 238 "data/maps/Route13_hns/scripts.pory"
Route13_TravelToAlola_Movement_2:
# 238 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 238 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 238 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 238 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 238 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 238 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 238 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 238 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 238 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 238 "data/maps/Route13_hns/scripts.pory"
	walk_right
# 238 "data/maps/Route13_hns/scripts.pory"
	walk_right
	step_end

Route13_GetOffBoat_Text_0:
# 193 "data/maps/Route13_hns/scripts.pory"
	.string "Welcome back to mainland Kanto!\p"
	.string "Come back if you'd like to take a trip\n"
	.string "to the Alola Isles!$"

Route13_TravelToAlola_Text_0:
# 207 "data/maps/Route13_hns/scripts.pory"
	.string "Ahoy there!\p"
	.string "That's one strange souvenir.\n"
	.string "You must be from the Isles!\p"
	.string "Would you like to take the next ship?\n"
	.string "It departs shortly!$"

Route13_TravelToAlola_Text_1:
# 215 "data/maps/Route13_hns/scripts.pory"
	.string "Ahoy! Let's get you on board!$"

Route13_TravelToAlola_Text_2:
# 261 "data/maps/Route13_hns/scripts.pory"
	.string "Ahoy!\n"
	.string "Come back when you'd like to set sail.$"

Route13_TravelToAlola_Text_3:
# 268 "data/maps/Route13_hns/scripts.pory"
	.string "Ah, its you again!\n"
	.string "Do you want to go to the Alola Isles?$"

Route13_TravelToAlola_Text_4:
# 312 "data/maps/Route13_hns/scripts.pory"
	.string "Ahoy!\n"
	.string "This ship is for residents only.\p"
	.string "All of the residents of these Isles\n"
	.string "carry some… {PAUSE 30}strange souvenirs.\p"
	.string "It makes them so easy to identify,\n"
	.string "I don't even need to check tickets!$"
