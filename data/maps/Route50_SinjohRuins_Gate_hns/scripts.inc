Route50_SinjohRuins_Gate_hns_MapScripts::
	.byte 0

Route50_Gate_EventScript_Officer::
    lock
	msgbox Route50_Gate_Officer_Text MSGBOX_DEFAULT
	release
	end

Route50_Gate_Officer_Text:
    .string "Normally gates like these\n"
	.string "don't require a guard, but\l"
	.string "the archeologists in the ruins\l"
	.string "asked me to keep a watch\l"
	.string "in case anyone tries to steal\l"
	.string "any artifacts or somethin'.$"

Route50_Gate_EventScript_Rex::
    lock
	faceplayer
    goto_if_set FLAG_ROUTE50GATE_BLACKBELTREX_FISTPLATE, Route50_Gate_AfterBattle
	msgbox Route50_Gate_Rex_Text MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Route50_Gate_EventScript_RexComeAgain
	msgbox Route50_Gate_REx__BattleBegin_Text
    trainerbattle_no_intro TRAINER_REX4_HNS, Route50_Gate_Rex_Beaten
    goto Route50_Gate_AfterBattle


Route50_Gate_AfterBattle::
    setflag FLAG_ROUTE50GATE_BLACKBELTREX_FISTPLATE
    msgbox Route50_Gate_Rex_GivesFistPlate MSGBOX_DEFAULT
    delay 8
    giveitem ITEM_FIST_PLATE, 1
	compare VAR_RESULT, 0
	goto_if_eq Route50_Gate_EventScript_BagIsFull
	addvar VAR_PLATECOUNTER, 1
	closemessage
	applymovement LOCALID_PLAYER, Route50_Gate_PlayerSteps_Asaide_Movement
	delay 30
	applymovement LOCALID_FIST_PLATE, Route50_Gate_RexLeaves_Movement
	applymovement LOCALID_HERACROSS, Route50_Gate_HeracrossLeaves_Movement
	waitmovement
	waitmovement
	waitmovement
	setflag FLAF_REMOVE_REX_AND_HERACROSS
	removeobject LOCALID_FIST_PLATE
	playse SE_WARP_OUT
	delay 30
	removeobject LOCALID_HERACROSS
	playse SE_WARP_OUT
	delay 10
	release
	end

Route50_Gate_PlayerSteps_Asaide_Movement:
    walk_left
	face_right
	step_end


Route50_Gate_RexLeaves_Movement:
    walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route50_Gate_HeracrossLeaves_Movement:
    walk_left
    walk_down
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route50_Gate_Rex_Text:
    .string "I've heard about you kid..\n"
	.string "You're our new champion huh?\p"
	.string "HAH!!\n"
	.string "You don't look that tough to me!\l"
	.string "I've been training all my life\l"
	.string "to take down and replace Bruno.\p"
	.string "And you just swoop in and\n"
	.string "defeat him like it's nothing?\p"
	.string "How's about we have a friendly\n"
	.string "sparing match?\l"
	.string "If you win, I'll give you\l"
	.string "something really special.\p"
	.string "What do you say?\n"
	.string "Shall we dance?$"

Route50_Gate_EventScript_RexComeAgain::
    msgbox Route50_RexNeedMoreTime_Text MSGBOX_DEFAULT
	release
	end


Route50_RexNeedMoreTime_Text:
    .string "What? You need to think about it?\p"
	.string "Well hurry up! Life is too short\n"
	.string "to be waiting and worrying!$"


Route50_Gate_REx__BattleBegin_Text:
    .string "That's the spirit!!$"

Route50_Gate_Rex_Beaten:
    .string "Woah... your power is in incredible!$"

Route50_Gate_Rex_GivesFistPlate:
    .string "Now i understand how you beat Bruno..\p"
	.string "At my current level, there's no\n"
	.string "way i could have beaten you.\p"
	.string "I am going to go deep into\n"
	.string "the mountains with my team\l"
	.string "to continue our training.\p"
	.string "But first, a promise is a promise.\n"
	.string "Take this Champion, you've earned it!$"

Route50_Gate_EventScript_BagIsFull::
    msgbox Route50_Rex_BagIsFull_Text MSGBOX_DEFAULT
	release
	end

Route50_Rex_BagIsFull_Text:
    .string "It seems you're already at\n"
	.string "your maximum carrying capacity!\p"
	.string "Why don't you make some space\n"
	.string "in your BAG and come back?\p"
	.string "I'll be waiting!$"


Route50_Gate_Scientist_Male::
    lock
	faceplayer
	msgbox Route50_Gate_Scientist_M_Text MSGBOX_DEFAULT
	release
	end

Route50_Gate_Scientist_M_Text:
    .string "It's crazy to think that this\n"
	.string "whole area was dozens of feet under\l"
	.string "the snow for hundreds of yerars!$"


Route50_Gate_Scientist_Female::
    lock
	msgbox Route50_Gate_Scientist_F_Text MSGBOX_DEFAULT
	release
	end

Route50_Gate_Scientist_F_Text:
    .string "We've made quite a lot\n"
	.string "progress in the last few months.\p"
	.string "I think that soon no\n"
	.string "secrects shall remain in the past.$"

Route50_Gate_EventScript_Machamp::
	lock
	faceplayer
	playmoncry SPECIES_MACHAMP, 0
	msgbox Route50_Gate_MachampCry MSGBOX_DEFAULT
	waitmoncry
        closemessage
	release
	end

Route50_Gate_MachampCry:
	.string "Cha Champ?$"


Route50_Gate_EventScript_Heracross::
	lock
	faceplayer
	playmoncry SPECIES_HERACROSS, 0
	msgbox Route50_Gate_HeracrossCry MSGBOX_DEFAULT
	waitmoncry
        closemessage
	release
	end

Route50_Gate_HeracrossCry:
	.string "Hera! Hera!$"