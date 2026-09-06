Route50_hns_MapScripts::
	.byte 0

Route50_EventScript_BlackBelt1::
	msgbox Route50_Text_BlackBelt1, MSGBOX_NPC
	end

Route50_Text_BlackBelt1::
	.string "The body must be hardened\n"
    .string "and the mind strengthened\l"
    .string "in the harshest of conditions!$"

Route50_EventScript_BlackBelt2::
	msgbox Route50_Text_BlackBelt2, MSGBOX_NPC
	end

Route50_Text_BlackBelt2::
    .string "Phew!\p"
    .string "I'm not as hardcore as he is.\p"
	.string "There's really not much else\n"
    .string "to do here but train.$"
  

Route50_EventScript_Wessel::
	goto_if_defeated TRAINER_WESSEL_HNS, Route50_EventScript_WesselAfter
	msgbox Route50_Text_WesselBefore, MSGBOX_NPC
	goto_if_not_defeated TRAINER_WESSEL_HNS, Route50_EventScript_TryWesselBattle
	end
Route50_EventScript_TryWesselBattle::
	goto_if_eq VAR_SINJOH_STORYLINE, 6, Route50_EventScript_WesselBattle
	end
Route50_EventScript_WesselBattle::
	lock
	msgbox Route50_Text_WesselBeforeBattle, MSGBOX_AUTOCLOSE
	trainerbattle_no_intro TRAINER_WESSEL_HNS, Route50_Text_WesselDefeat
	giveitem ITEM_IRON_PLATE
	addvar VAR_PLATECOUNTER, 1
	msgbox Route50_Text_WesselAfter, MSGBOX_AUTOCLOSE
	call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end
Route50_EventScript_WesselAfter::
	msgbox Route50_Text_WesselAfter, MSGBOX_NPC
	end

Route50_Text_WesselBefore:
	.string "Incredible, A VOLTORB!\p"
    .string "But it appears to be made\n"
    .string "of... Wood?\p"
    .string "My hypothesis that this route\n"
    .string "would contain many STEEL TYPE\l"
    .string "POKéMON is disproven yet again.\p"
    .string "But why else would I have found\n"
    .string "this STEEL PLATE here?\p"
    .string "I must collect more data!$"

Route50_Text_WesselBeforeBattle:
	.string "You want this PLATE?\n"
	.string "But I haven't analyzed it yet!\p"
	.string "Fine, we will battle for it.$"

Route50_Text_WesselDefeat:
	.string "My hypothesis was wrong...$"

Route50_Text_WesselAfter:
	.string "Take the PLATE. I don't want to\n"
	.string "talk about it.$"

Route50_EventScript_Finley::
	goto_if_defeated TRAINER_FINLEY_HNS, Route50_EventScript_FinleyAfter
	msgbox Route50_Text_FinleyBefore, MSGBOX_NPC
	goto_if_not_defeated TRAINER_FINLEY_HNS, Route50_EventScript_TryFinleyBattle
	end
Route50_EventScript_TryFinleyBattle::
	goto_if_eq VAR_SINJOH_STORYLINE, 6, Route50_EventScript_FinleyBattle
	end
Route50_EventScript_FinleyBattle::
	lock
	msgbox Route50_Text_FinleyBeforeBattle, MSGBOX_AUTOCLOSE
	trainerbattle_no_intro TRAINER_FINLEY_HNS, Route50_Text_FinleyDefeat
	giveitem ITEM_DRACO_PLATE
	addvar VAR_PLATECOUNTER, 1
	msgbox Route50_Text_FinleyAfter, MSGBOX_AUTOCLOSE
	call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end
Route50_EventScript_FinleyAfter::
	msgbox Route50_Text_FinleyAfter, MSGBOX_NPC
	end

Route50_Text_FinleyBefore:
	.string "How are the villagers treating\n"
    .string "you?\p"
    .string "They can be very unwelcoming to\n"
    .string "strangers.\p"
    .string "But meeting new people is one\n"
    .string "of life's greatest joys.\p"
    .string "One day, I hope to meet CHAMPION\n"
    .string "LANCE.\p"
    .string "He is a legendary dragon tamer,\n"
    .string "much like myself.\l"
    .string "Who am I?\p"
    .string "Well, I am FINLEY, keeper of the\n"
    .string "DRACO PLATE.$"

Route50_Text_FinleyBeforeBattle:
	.string "I know the KIMONO's have sent you\n"
	.string "to collect these PLATES.\p"
	.string "They say you are worthy...\n"
	.string "But can you conquer my dragons?$"

Route50_Text_FinleyDefeat:
	.string "My dragons fought well.$"

Route50_Text_FinleyAfter:
	.string "Perhaps you are even strong enough\n"
	.string "to beat LANCE...$"

Route50_EventScript_Item_ULtraBall::
    finditem ITEM_ULTRA_BALL
    end

Route50_EventScript_Item_Big_Nugget::
    finditem ITEM_BIG_NUGGET
    end

Route50_EventScript_ActivateKleavor::
    lock
    setobjectxyperm LOCALID_ROUTE50_NOBLE_KLEAVOR, 75, 12
    playse SE_M_DETECT
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	dofieldeffectsparkle VAR_TEMP_1, VAR_TEMP_2, 0
	waitfieldeffect FLDEFF_SPARKLE
    playse SE_PIN
    applymovement2 LOCALID_PLAYER, Common_Movement_ExclamationMark
    delay 55
    waitmovement LOCALID_PLAYER
    msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
    goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
    playbgm MUS_DP_AZURE_FLUTE, FALSE
    delay 200
    fadedefaultbgm
    addobject LOCALID_ROUTE50_NOBLE_KLEAVOR
    clearflag FLAG_HIDE_ROUTE50_NOBLE_KLEAVOR
    applymovement2 LOCALID_ROUTE50_NOBLE_KLEAVOR, Route50_Movement_KleavorEntrance1
    delay 10
    playmoncry SPECIES_KLEAVOR, CRY_MODE_NORMAL
    waitmoncry
    playmoncry SPECIES_KLEAVOR, CRY_MODE_NORMAL
    waitmoncry
    waitmovement 0
    applymovement2 LOCALID_ROUTE50_NOBLE_KLEAVOR, Route50_Movement_KleavorEntrance2
    delay 10
    playse SE_LEDGE
    delay 20
	waitmovement LOCALID_ROUTE50_NOBLE_KLEAVOR
    setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 5  @ num shakes
	setvar VAR_0x8007, 2  @ shake delay
	special ShakeCamera
    setobjectxyperm LOCALID_ROUTE50_NOBLE_KLEAVOR, 75, 14
    setvar VAR_NOBLE_KLEAVOR, 2
    release
    end

Route50_Movement_KleavorEntrance1:
    jump_in_place_down
    walk_in_place_fast_down
    walk_in_place_fast_down
	step_end

Route50_Movement_KleavorEntrance2:
	jump_2_down
    walk_in_place_slow_down
	walk_in_place_slow_down
	jump_in_place_down
	step_end

Route50_EventScript_Kleavor::
	lock
	faceplayer
	playmoncry SPECIES_KLEAVOR, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbossbattle species=SPECIES_KLEAVOR, level=80, item=ITEM_SCOPE_LENS, move1_1=MOVE_STONE_AXE, move1_2=MOVE_CROSS_POISON, move1_3=MOVE_LUNGE move1_4=MOVE_FOCUS_ENERGY
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 2, 0, 0, 2, 0
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	setflag FLAG_NO_SHINY
    dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route50_EventScript_KleavorRan
    bufferspeciesname STR_VAR_1, SPECIES_KLEAVOR
    msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
    giveitem ITEM_INSECT_PLATE
    addvar VAR_PLATECOUNTER, 1
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ROUTE50_NOBLE_KLEAVOR
	setflag FLAG_HIDE_ROUTE50_NOBLE_KLEAVOR
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

Route50_EventScript_KleavorRan::
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag FLAG_NO_SHINY
	release
	end


Route50_EventScript_ActivateElectrode::
    lock
    setobjectxyperm LOCALID_ROUTE50_NOBLE_ELECTRODE, 18, 26
    playse SE_M_DETECT
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	dofieldeffectsparkle VAR_TEMP_1, VAR_TEMP_2, 0
	waitfieldeffect FLDEFF_SPARKLE
    playse SE_PIN
    applymovement2 LOCALID_PLAYER, Common_Movement_ExclamationMark
    delay 55
    waitmovement LOCALID_PLAYER
    msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
    goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
    playbgm MUS_DP_AZURE_FLUTE, FALSE
    delay 200
    fadedefaultbgm
    addobject LOCALID_ROUTE50_NOBLE_ELECTRODE
    clearflag FLAG_HIDE_ROUTE50_NOBLE_ELECTRODE
    applymovement2 LOCALID_ROUTE50_NOBLE_ELECTRODE, Route50_Movement_ElectrodeEntrance1
    delay 10
    playmoncry SPECIES_ELECTRODE_HISUI, CRY_MODE_NORMAL
    waitmoncry
    playmoncry SPECIES_ELECTRODE_HISUI, CRY_MODE_NORMAL
    waitmoncry
    waitmovement 0
    applymovement2 LOCALID_ROUTE50_NOBLE_ELECTRODE, Route50_Movement_ElectrodeEntrance2
    delay 10
    playse SE_LEDGE
    delay 20
	waitmovement 0
    setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 5  @ num shakes
	setvar VAR_0x8007, 2  @ shake delay
	special ShakeCamera
	applymovement2 LOCALID_ROUTE50_NOBLE_ELECTRODE, Route50_Movement_ElectrodeEntrance3
	waitmovement LOCALID_ROUTE50_NOBLE_ELECTRODE
	removeobject LOCALID_ROUTE50_NOBLE_ELECTRODE
	delay 20
	setobjectxyperm LOCALID_ROUTE50_NOBLE_ELECTRODE, 14, 31
	addobject LOCALID_ROUTE50_NOBLE_ELECTRODE
	clearflag FLAG_HIDE_ROUTE50_NOBLE_ELECTRODE
    setvar VAR_NOBLE_ELECTRODE, 2
    release
    end

Route50_Movement_ElectrodeEntrance1:
	walk_right
    jump_in_place_right
    walk_in_place_fast_right
    walk_in_place_fast_right
	step_end

Route50_Movement_ElectrodeEntrance2:
	jump_2_right
    walk_in_place_slow_up
	walk_in_place_slow_up
	jump_in_place_down
	step_end

Route50_Movement_ElectrodeEntrance3:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route50_EventScript_Electrode::
	lock
	faceplayer
	playmoncry SPECIES_ELECTRODE_HISUI, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbossbattle species=SPECIES_ELECTRODE_HISUI, level=80, item=ITEM_BRIGHT_POWDER, move1_1=MOVE_FOUL_PLAY, move1_2=MOVE_ELECTRO_BALL, move1_3=MOVE_ENERGY_BALL move1_4=MOVE_CHLOROBLAST
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 3, 1, 0, 3, 0
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	setflag FLAG_NO_SHINY
    dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route50_EventScript_ElectrodeRan
    bufferspeciesname STR_VAR_1, SPECIES_ELECTRODE_HISUI
    msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
    giveitem ITEM_ZAP_PLATE
    addvar VAR_PLATECOUNTER, 1
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_ROUTE50_NOBLE_ELECTRODE
	setflag FLAG_HIDE_ROUTE50_NOBLE_ELECTRODE
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

Route50_EventScript_ElectrodeRan::
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag FLAG_NO_SHINY
	release
	end
