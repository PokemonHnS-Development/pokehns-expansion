Route49_hns_MapScripts::
    map_script MAP_SCRIPT_ON_FRAME_TABLE, Route49_hns_OnFrame
	.byte 0


Route49_hns_OnFrame::
    map_script_2 VAR_ROUTE49_HNS_KIMONOGIRL, 0, Route49_EventScripts_KimonoGirl
	.2byte 0

Route49_EventScripts_KimonoGirl::
    delay 15
    lock
	playse MUS_HG_DANCE_THEATER
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
	playse MUS_HG_SINJOU_RUINS
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