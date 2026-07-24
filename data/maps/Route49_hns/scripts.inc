Route49_hns_MapScripts::
    map_script MAP_SCRIPT_ON_FRAME_TABLE, Route49_hns_OnFrame
	.byte 0


Route49_hns_OnFrame::
    map_script_2 VAR_SINJOH_STORYLINE, 3, Route49_EventScripts_KimonoGirl
	.2byte 0

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
	.string "your deeds from my sisters\l"
	.string "in Ecruteak City.\p"
	.string "My older sister wishes to meet with you.\l"
	.string "If you find the time, please\n"
	.string "seek us out in the town\l"
	.string "up ahead.$"

Route49_EventScript_Item_StarDust::
    finditem ITEM_STARDUST
    end

Route49_EventScript_Item_Lure::
    finditem ITEM_LURE
    end

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
	@removeobject LOCALID_NOBLE_ELECTRODE
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
	@removeobject LOCALID_NOBLE_ELECTRODE
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

Route49_EventScript_Sign::
    msgbox Route49_Text_Sign, MSGBOX_SIGN
    end

Route49_Text_Sign:
    .string "The sign is faded.\n"
    .string "ROUTE 49$"
