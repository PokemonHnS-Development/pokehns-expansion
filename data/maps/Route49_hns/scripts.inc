Route49_hns_MapScripts::
    map_script MAP_SCRIPT_ON_FRAME_TABLE, Route49_hns_OnFrame
	.byte 0


Route49_hns_OnFrame::
    map_script_2 VAR_ROUTE49_HNS_KIMONOGIRL, 0, Route49_EventScripts_KimonoGirl
	.2byte 0

Route49_EventScripts_HideNoble_Trigger::
    goto_if_set FLAG_NOBLES_UNLOCKED, Route49_EventScript_AddNobles
    release
    end

Route49_EventScript_AddNobles::
    addobject LOCALID_NOBLE_ELECTRODE
    release
    end

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
	addvar VAR_ROUTE49_HNS_KIMONOGIRL, 1
	removeobject LOCALID_ROUTE49_KIMONOGIRL
	fadedefaultbgm
	release
	end


Route49_KimonoGirl_Movement1:
    walk_slow_left
	walk_slow_left
	walk_slow_left
	walk_slow_left
	walk_slow_left
	walk_slow_left
	step_end

Route49_KimonoGitl_Movement2:
    walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_slow_right
	walk_slow_right
	step_end

Route49_Text_KimonoGirl:
    .string "You....\p"
	.string "You must be {PLAYER}, correct?\n"
    .string "I've heard all about you and\l"
	.string "your deeds from my cousins\l"
	.string "in Ecruteak City.\p"
	.string "My older sister wishes to meet with you.\l"
	.string "If you find the time, please\n"
	.string "seek us out in the town\l"
	.string "up ahead.$"

Route49_EventScript_EngieNikolas::
    trainerbattle_single TRAINER_NIKOLAS_HNS, Route49_Text_EngieNikolas_Seen, Route49_Text_EngieNikolas_Beaten
    msgbox Route49_Text_EngieNikolas_After, MSGBOX_AUTOCLOSE
    end


Route49_Text_EngieNikolas_Seen:
    .string "I just put up this fence!\n"
    .string "What do you think?$"

Route49_Text_EngieNikolas_Beaten:
    .string "Woah!\n"
    .string "Your team is something else huh?$"

Route49_Text_EngieNikolas_After:
    .string "You think the fence is great?\n"
    .string "Why thank you!\p"
    .string "Now I just have to put up the rest.$"

Route49_EventScript_BeautyRebecca::
    trainerbattle_single TRAINER_REBECCA4_HNS, Route49_Text_BeautyRebecca_Seen, Route49_Text_BeautyRebecca_Beaten
    msgbox Route49_Text_BeautyRebecca_After, MSGBOX_AUTOCLOSE
    end


Route49_Text_BeautyRebecca_Seen:
    .string "Whitness my dazzling team!$"

Route49_Text_BeautyRebecca_Beaten:
    .string "Rest easy now everyone..\n"
    .string "Get your well earned beauty sleep..$"

Route49_Text_BeautyRebecca_After:
    .string "I can't believe how much your team\n"
    .string "sparkled as well!\p"
    .string "Let us both fill the world is beauty!$"

Route49_EventScript_JugglerJustin::
    trainerbattle_single TRAINER_JUSTIN4_HNS, Route49_Text_JugglerJustin_Seen, Route49_Text_JugglerJustin_Beaten
    msgbox Route49_Text_JugglerJustin_After, MSGBOX_AUTOCLOSE
    end


Route49_Text_JugglerJustin_Seen:
    .string "Here! Catch this!$"

Route49_Text_JugglerJustin_Beaten:
    .string "My balls!\n"
    .string "You were supposed to catch them!$"

Route49_Text_JugglerJustin_After:
    .string "Do you even know just how\n"
    .string "expensive those are?!\p"
    .string "You better help me find them!$"

Route49_EventScript_NinjaGenji::
    trainerbattle_single TRAINER_GENJI_HNS, Route49_Text_NinjaGenji_Seen, Route49_Text_NinjaGenji_Beaten
    msgbox Route49_Text_NinjaGenji_After, MSGBOX_AUTOCLOSE
    end


Route49_Text_NinjaGenji_Seen:
    .string "I'm training to be a ninja!$"

Route49_Text_NinjaGenji_Beaten:
    .string "Clearly I have more training to do..\n"
    .string "Thank you for this match!!$"

Route49_Text_NinjaGenji_After:
    .string "I'll keep practicing until\n"
	.string "Master Koga takes me on!$"

Route49_EventScript_CamperIssac::
    trainerbattle_single TRAINER_ISSAC4_HNS, Route49_Text_CamperIssac_Seen, Route49_Text_CamperIssac_Beaten
    msgbox Route49_Text_CamperIssac_After, MSGBOX_AUTOCLOSE
    end


Route49_Text_CamperIssac_Seen:
    .string "I've been exploring these woods\n"
    .string "for decades!$"

Route49_Text_CamperIssac_Beaten:
    .string "How old are you?!\n"
    .string "Your team is so experienced!$"

Route49_Text_CamperIssac_After:
    .string "I'm not trying to catch them all.\p"
	.string "I'm aiming for every scout badge!$"

Route49_EventScript_Mom::
    lock
    faceplayer
    msgbox Route49_Text_Mom MSGBOX_DEFAULT
    closemessage
    release
    end

Route49_Text_Mom:
    .string "Look at my adorable babies go!\p"
    .string "I'm so glad the town set up\n"
    .string "this ice rink so the\l"
    .string "little ones can play safely!$"

Route49_EventScript_Dad::
    lock
    faceplayer
    msgbox Route49_Text_Dad MSGBOX_DEFAULT
    closemessage
    release
    end

Route49_Text_Dad:
    .string "Hey kid, mind leaving me alone?\n"
    .string "I'm trying to focus on filming my kids.$"

Route49_EventScript_Sister::
    lock
    faceplayer
    msgbox Route49_Text_Sister MSGBOX_DEFAULT
    closemessage
    release
    end

Route49_Text_Sister:
    .string "Wheeeeee!!\p"
    .string "Look Mommy!\n"
    .string "No hands!$"

Route49_EventScript_Son::
    lock
    faceplayer
    msgbox Route49_Text_Son MSGBOX_DEFAULT
    closemessage
    release
    end

Route49_Text_Son:
    .string "Siiis!\p"
    .string "Slow down, You're going to crash!$"

Route49_EventScript_Item_MindPlate::
    finditem ITEM_MIND_PLATE
    addvar VAR_PLATECOUNTER, 1
    end

Route49_EventScript_Item_StarDust::
    finditem ITEM_STARDUST
    end

Route49_EventScript_Item_Lure::
    finditem ITEM_LURE
    end

Route49_EventScript_PetWyrdeer::
    lock
	faceplayer
	playmoncry SPECIES_WYRDEER, 0
	msgbox Route49_Text_Wyrdeer_Cry2, MSGBOX_DEFAULT
	waitmoncry
    closemessage
	release
	end

Route49_Text_Wyrdeer_Cry2:
    .string "Wyrrr!$"


Route49_EventScript_Electrode::
	lock
	faceplayer
	setwildbossbattle species=SPECIES_ELECTRODE_HISUI, level=80, item=ITEM_ZAP_PLATE, move1_1=MOVE_ELECTRO_BALL, move1_2=MOVE_ENERGY_BALL, move1_3=MOVE_STUN_SPORE move1_4=MOVE_CHARGE
	waitse
	playmoncry SPECIES_ELECTRODE, CRY_MODE_ENCOUNTER
	msgbox Route49_Text_Bzzzt MSGBOX_DEFAULT
	waitmessage
	waitmoncry
	delay 10
    setweather WEATHER_RAIN_THUNDERSTORM
    doweather
    delay 10
    playse SE_THUNDER
    fadescreen FADE_TO_WHITE
    fadescreen FADE_FROM_WHITE
	waitbuttonpress
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 0, 3, 2, 0, 0
	playbgm MUS_HG_VS_SUICUNE, 0
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route49_EventScript_DefeatedElectrode
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route49_EventScript_RanFromElectrode
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Route49_EventScript_RanFromElectrode
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NOBLE_ELECTRODE
    setweather WEATHER_SNOW
    doweather
	fadescreen FADE_FROM_BLACK
    DELAY 30
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox Route49_Text_ZapPlate
	giveitem ITEM_ZAP_PLATE, 1
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NOBLECOUNTER, 1
	release
	end

Route49_EventScript_DefeatedElectrode::
	setflag FLAG_FOUGHT_NOBLE_ELECTRODE
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NOBLE_ELECTRODE
    setweather WEATHER_SNOW
    doweather
	fadescreen FADE_FROM_BLACK
    delay 30
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox Route49_Text_ZapPlate
	giveitem ITEM_ZAP_PLATE, 1
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NOBLECOUNTER, 1
	end

Route49_EventScript_RanFromElectrode::
	setvar VAR_0x8004, SPECIES_ELECTRODE_HISUI
	end

Route49_Text_Bzzzt:
    .string "Bzzz Bzzzt!!$"

Route49_Text_ZapPlate:
    .string "It seems ELECTRODE left something behind..$"