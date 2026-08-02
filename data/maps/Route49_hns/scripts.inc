Route49_hns_MapScripts::
    map_script MAP_SCRIPT_ON_FRAME_TABLE, Route49_hns_OnFrame
	.byte 0

Route49_hns_OnFrame::
    map_script_2 VAR_SINJOH_STORYLINE, 3, Route49_EventScripts_KimonoGirl
	.2byte 0

Route49_EventScript_Skylar::
	goto_if_defeated TRAINER_SKYLAR_HNS, Route49_EventScript_SkylarAfter
	msgbox Route49_Text_SkylarBefore, MSGBOX_NPC
	goto_if_not_defeated TRAINER_SKYLAR_HNS, Route49_EventScript_TrySkylarBattle
	end
Route49_EventScript_TrySkylarBattle::
	goto_if_eq VAR_SINJOH_STORYLINE, 6, Route49_EventScript_SkylarBattle
	end
Route49_EventScript_SkylarBattle::
	lock
	msgbox Route49_Text_SkylarBeforeBattle, MSGBOX_AUTOCLOSE
	trainerbattle_no_intro TRAINER_SKYLAR_HNS, Route49_Text_SkylarDefeat
	giveitem ITEM_SKY_PLATE
	addvar VAR_PLATECOUNTER, 1
	msgbox Route49_Text_SkylarAfter, MSGBOX_AUTOCLOSE
	call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
    call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
    call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
    call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
    call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
    call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end
Route49_EventScript_SkylarAfter::
	msgbox Route49_Text_SkylarAfter, MSGBOX_NPC
	end

Route49_Text_SkylarDefeat:
	.string "OKAY, you can have the PLATE.$"

Route49_Text_SkylarAfter:
	.string "As cool as that PLATE is,\n"
	.string "you earned it fair and square.\p"
	.string "I'll just buy something at the gift\n"
	.string "shop instead.$"

Route49_Text_SkylarBeforeBattle:
	.string "What?\p"
	.string "You want the PLATE?\n"
	.string "It's an artifact imbued with an\l"
	.string "ancient power with a connection\l"
	.string "to the legendary POKéMON?!\p"
	.string "Well now I'm definitely keeping it.\p"
	.string "Fine.\p"
	.string "You'll just have to battle me for it.$"

Route49_Text_SkylarBefore:
	.string "When I was hitting the slopes, my\n"
	.string "skis snagged on something.\p"
	.string "It was this strange SKY-blue PLATE.\p"
	.string "I think I'll hold onto it as a\n"
	.string "souvenir!$"

Route49_EventScript_SkierM::
	msgbox Route49_Text_SkierM, MSGBOX_NPC
	end

Route49_Text_SkierM::
	.string "Hey, watch out for my board!\p"
	.string "What? You want to battle?\n"
	.string "No way, these slopes are too wicked!$"

Route49_EventScripts_KimonoGirl::
    delay 10
    lock
	playbgm MUS_HG_DANCE_THEATER, FALSE
	delay 10
	playse SE_PIN
	applymovement LOCALID_ROUTE49_KIMONOGIRL, Common_Movement_ExclamationMark
	waitmovement
	delay 20
	applymovement LOCALID_ROUTE49_KIMONOGIRL, Route49_KimonoGirl_Movement1
	waitmovement
	msgbox Route49_Text_KimonoGirl MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE49_KIMONOGIRL, Route49_KimonoGitl_Movement2
	waitmovement
	setflag FLAG_ROUTE_49_KIMONOGIRL
	setvar VAR_SINJOH_STORYLINE, 4
	removeobject LOCALID_ROUTE49_KIMONOGIRL
	fadedefaultbgm
	release
	end

Route49_KimonoGirl_Movement1:
    walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route49_KimonoGitl_Movement2:
    walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route49_Text_KimonoGirl:
    .string "You....\p"
	.string "You must be {PLAYER}, correct?\n"
    .string "I've heard all about you and\l"
	.string "your deeds from my cousins\l"
	.string "in Ecruteak City.\p"
	.string "My sisters wish to meet with you.\l"
	.string "If you find the time, please\n"
	.string "seek us out in the town\l"
	.string "up ahead.$"

Route49_EventScript_Item_StarDust::
    finditem ITEM_STARDUST
    end

Route49_EventScript_Item_Lure::
    finditem ITEM_LURE
    end

Route49_EventScript_Sign::
    msgbox Route49_Text_Sign, MSGBOX_SIGN
    end

Route49_Text_Sign:
    .string "The sign is faded.\n"
    .string "ROUTE 49$"

Route49_EventScript_ActivateOverqwil::
    lock
    setobjectxyperm LOCALID_ROUTE49_NOBLE_OVERQWIL, 48, 42
    playse SE_M_DETECT
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	dofieldeffectsparkle VAR_TEMP_1, VAR_TEMP_2, 0
	waitfieldeffect FLDEFF_SPARKLE
    playse SE_PIN
    applymovement2 LOCALID_PLAYER, Common_Movement_ExclamationMark
    delay 60
    msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
    goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
    playbgm MUS_DP_AZURE_FLUTE, FALSE
    delay 200
    fadedefaultbgm
    addobject LOCALID_ROUTE49_NOBLE_OVERQWIL
    clearflag FLAG_HIDE_ROUTE49_NOBLE_OVERQWIL
    applymovement2 LOCALID_ROUTE49_NOBLE_OVERQWIL, Route49_Movement_OverqwilEntrance1
    delay 10
    playmoncry SPECIES_OVERQWIL, CRY_MODE_NORMAL
    waitmoncry
    playmoncry SPECIES_OVERQWIL, CRY_MODE_NORMAL
    waitmoncry
    waitmovement 0
    applymovement2 LOCALID_ROUTE49_NOBLE_OVERQWIL, Route49_Movement_OverqwilEntrance2
    delay 10
    playse SE_LEDGE
    delay 20
	waitmovement LOCALID_ROUTE49_NOBLE_OVERQWIL
    setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 5  @ num shakes
	setvar VAR_0x8007, 2  @ shake delay
	special ShakeCamera
    setobjectxyperm LOCALID_ROUTE49_NOBLE_OVERQWIL, 48, 44
    setvar VAR_NOBLE_OVERQWIL, 2
    release
    end

Route49_Movement_OverqwilEntrance1:
    walk_in_place_fast_down
    jump_in_place_down
    jump_in_place_down
    jump_in_place_down
    jump_in_place_down
	step_end

Route49_Movement_OverqwilEntrance2:
	walk_slow_down
	walk_slow_down
    walk_in_place_slow_down
	walk_in_place_slow_down
	jump_in_place_down
	step_end


Route49_EventScript_Overqwil::
	lock
	faceplayer
	playmoncry SPECIES_OVERQWIL, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbossbattle species=SPECIES_OVERQWIL, level=80, item=ITEM_BLACK_SLUDGE, move1_1=MOVE_BARB_BARRAGE, move1_2=MOVE_LIQUIDATION, move1_3=MOVE_TOXIC_SPIKES move1_4=MOVE_CURSE
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 2, 0, 0, 3, 0
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	setflag FLAG_NO_SHINY
    dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route49_EventScript_OverqwilRan
    bufferspeciesname STR_VAR_1, SPECIES_OVERQWIL
    msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
    giveitem ITEM_DREAD_PLATE
    addvar VAR_PLATECOUNTER, 1
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ROUTE49_NOBLE_OVERQWIL
	setflag FLAG_HIDE_ROUTE49_NOBLE_OVERQWIL
	fadescreenswapbuffers FADE_FROM_BLACK
    call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
    call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
    call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
    call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
    call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
    call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag FLAG_NO_SHINY
	release
	end

Route49_EventScript_OverqwilRan::
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag FLAG_NO_SHINY
	release
	end


Route49_Movement_PlayerWyrdeerRight:
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	step_end

Route49_Movement_PlayerWyrdeerLeft:
	walk_right
	walk_up
	walk_right
	walk_up
	walk_up
	step_end

Route49_EventScript_ActivateWyrdeerLeft::
    lock
    setobjectxyperm LOCALID_ROUTE49_NOBLE_WYRDEER, 59, 2
    playse SE_M_DETECT
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	dofieldeffectsparkle VAR_TEMP_1, VAR_TEMP_2, 0
	waitfieldeffect FLDEFF_SPARKLE
    playse SE_PIN
    applymovement2 LOCALID_PLAYER, Common_Movement_ExclamationMark
    delay 60
    msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
    goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
    playbgm MUS_DP_AZURE_FLUTE, FALSE
	applymovement2 LOCALID_PLAYER, Route49_Movement_PlayerWyrdeerLeft
    delay 200
	waitmovement 0
    fadedefaultbgm
    addobject LOCALID_ROUTE49_NOBLE_WYRDEER
    clearflag FLAG_HIDE_ROUTE49_NOBLE_WYRDEER
    applymovement2 LOCALID_ROUTE49_NOBLE_WYRDEER, Route49_Movement_WyrdeerEntrance1
    delay 10
    playmoncry SPECIES_WYRDEER, CRY_MODE_NORMAL
    waitmoncry
    playmoncry SPECIES_WYRDEER, CRY_MODE_NORMAL
    waitmoncry
    waitmovement 0
    applymovement2 LOCALID_ROUTE49_NOBLE_WYRDEER, Route49_Movement_WyrdeerEntrance2
    delay 10
    playse SE_LEDGE
    delay 20
	waitmovement LOCALID_ROUTE49_NOBLE_WYRDEER
    setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 5  @ num shakes
	setvar VAR_0x8007, 2  @ shake delay
	special ShakeCamera
    setobjectxyperm LOCALID_ROUTE49_NOBLE_WYRDEER, 59, 7
    setvar VAR_NOBLE_WYRDEER, 2
    release
    end
Route49_EventScript_ActivateWyrdeerRight::
    lock
    setobjectxyperm LOCALID_ROUTE49_NOBLE_WYRDEER, 59, 2
    playse SE_M_DETECT
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	dofieldeffectsparkle VAR_TEMP_1, VAR_TEMP_2, 0
	waitfieldeffect FLDEFF_SPARKLE
    playse SE_PIN
    applymovement2 LOCALID_PLAYER, Common_Movement_ExclamationMark
    delay 60
    msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
    goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
	applymovement2 LOCALID_PLAYER, Route49_Movement_PlayerWyrdeerRight
    delay 200
	waitmovement 0
    fadedefaultbgm
    addobject LOCALID_ROUTE49_NOBLE_WYRDEER
    clearflag FLAG_HIDE_ROUTE49_NOBLE_WYRDEER
    applymovement2 LOCALID_ROUTE49_NOBLE_WYRDEER, Route49_Movement_WyrdeerEntrance1
    delay 10
    playmoncry SPECIES_WYRDEER, CRY_MODE_NORMAL
    waitmoncry
    playmoncry SPECIES_WYRDEER, CRY_MODE_NORMAL
    waitmoncry
    waitmovement 0
    applymovement2 LOCALID_ROUTE49_NOBLE_WYRDEER, Route49_Movement_WyrdeerEntrance2
    delay 10
    playse SE_LEDGE
    delay 20
	waitmovement LOCALID_ROUTE49_NOBLE_WYRDEER
    setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 5  @ num shakes
	setvar VAR_0x8007, 2  @ shake delay
	special ShakeCamera
    setobjectxyperm LOCALID_ROUTE49_NOBLE_WYRDEER, 59, 7
    setvar VAR_NOBLE_WYRDEER, 2
    release
    end

Route49_Movement_WyrdeerEntrance1:
	walk_down
    walk_in_place_fast_down
    jump_in_place_down
    jump_in_place_down
    jump_in_place_down
    jump_in_place_down
	step_end

Route49_Movement_WyrdeerEntrance2:
	walk_slow_down
	walk_slow_down
	jump_2_down
    walk_in_place_slow_down
	walk_in_place_slow_down
	jump_in_place_down
	step_end


Route49_EventScript_Wyrdeer::
	lock
	faceplayer
	playmoncry SPECIES_WYRDEER, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbossbattle species=SPECIES_WYRDEER, level=80, item=ITEM_CLEAR_AMULET, move1_1=MOVE_PSYSHIELD_BASH, move1_2=MOVE_LUNGE, move1_3=MOVE_CALM_MIND move1_4=MOVE_THUNDERBOLT
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 1, 2, 0, 1, 0
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	setflag FLAG_NO_SHINY
    dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route49_EventScript_WyrdeerRan
    bufferspeciesname STR_VAR_1, SPECIES_WYRDEER
    msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
    giveitem ITEM_MIND_PLATE
    addvar VAR_PLATECOUNTER, 1
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ROUTE49_NOBLE_WYRDEER
	setflag FLAG_HIDE_ROUTE49_NOBLE_WYRDEER
	fadescreenswapbuffers FADE_FROM_BLACK
    call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
    call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
    call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
    call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
    call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
    call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag FLAG_NO_SHINY
	release
	end

Route49_EventScript_WyrdeerRan::
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag FLAG_NO_SHINY
	release
	end
