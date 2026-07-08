NewSinjoh_KimonoHideout_hns_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION NewSinjoh_KimonoHideout_OnTransition
	.byte 0

NewSinjoh_KimonoHideout_OnTransition::
    setvar VAR_NEWSINOH_KIMONO_TRACKER, 0
	end

NewSinjoh_Kimono_EventScript_Miharu::
    lock
	faceplayer
	goto_if_set FLAG_NEWSINJOH_KIMONOGIRLGRASS, NewSinjoh_Kimono_EventScript_Miharu2
	msgbox NewSinjoh_KimonoHideout_Miharu_Text MSGBOX_DEFAULT
	applymovement LOCALID_MIHARU, NewSinjoh_Kimono_Dance_Movement
	waitmovement
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 2,1, 0, 2, 3, 0
    trainerbattle_no_intro TRAINER_MIHARU_HNS, NewSinjoh_KimonoHideout_Miharu_Beaten
    goto NewSinjoh_Kimono_Miharu_AfterBattle


NewSinjoh_Kimono_Miharu_AfterBattle::
    msgbox NewSinjoh_Kimono_Hideout_MiharuGivesMeadowPlate
	delay 8
    giveitem ITEM_MEADOW_PLATE, 1
	compare VAR_RESULT, 0
	goto_if_eq NewSinjoh_KimonoHideout_EventScript_BagIsFull
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NEWSINOH_KIMONO_TRACKER, 1
	setflag FLAG_NEWSINJOH_KIMONOGIRLGRASS
	release
	end

NewSinjoh_KimonoHideout_Miharu_Text:
    .string "Good day to you {PLAYER}.\p"
	.string "I see you followed my\n"
	.string "younger sister's instructions..\p"
	.string "We are fully aware of the flute\n"
	.string "you're carrying..but while\l"
	.string "our cousins deemed you worthy\l"
	.string "of calming their idol.\p"
	.string "We follow the true god of\n"
	.string "this world!\p"
	.string "Now! whitness a taste of their\n"
	.string "almighty power!!$"


NewSinjoh_KimonoHideout_Miharu_Beaten:
    .string "Perhaps you are worthy after all..$"


NewSinjoh_Kimono_Hideout_MiharuGivesMeadowPlate:
    .string "Here {PLAYER}, take this..\n"
	.string "I belive you should take this\l"
	.string "and keep moving forward\l"
	.string "and discover the truth.$"


NewSinjoh_Kimono_EventScript_Miharu2::
    msgbox NewSinjoh_Kimono_Text_Miharu2 MSGBOX_DEFAULT
	release
	end


NewSinjoh_Kimono_Text_Miharu2:
    .string "Good luck in your travels {PLAYER}..$"

TEST_TEXT:
    .string "This is a test.$"

NewSinjoh_Kimono_EventScript_Youko::
    lock
	faceplayer
	goto_if_set FLAG_NEWSINJOH_KIMONOGIRLICE, NewSinjoh_Kimono_EventScript_Youko2
	msgbox NewSinjoh_KimonoHideout_Youko_Text MSGBOX_DEFAULT
	applymovement LOCALID_YOUKO, NewSinjoh_Kimono_Dance_Movement
	waitmovement
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 2,0, 1, 2, 3, 0
    trainerbattle_no_intro TRAINER_YOUKO_HNS, NewSinjoh_KimonoHideout_Youko_Beaten
    goto NewSinjoh_Kimono_Youko_AfterBattle


NewSinjoh_Kimono_Youko_AfterBattle::
    msgbox NewSinjoh_Kimono_Hideout_YoukoGivesIciclePlate MSGBOX_DEFAULT
	delay 8
    giveitem ITEM_ICICLE_PLATE, 1
	compare VAR_RESULT, 0
	goto_if_eq NewSinjoh_KimonoHideout_EventScript_BagIsFull
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NEWSINOH_KIMONO_TRACKER, 1
	setflag FLAG_NEWSINJOH_KIMONOGIRLICE
	release
	end

NewSinjoh_Kimono_EventScript_Youko2::
    msgbox NewSinjoh_Kimono_Text_Youko2 MSGBOX_DEFAULT
	release
	end

NewSinjoh_KimonoHideout_Youko_Text:
    .string "Ah {PLAYER}, thank you for coming..\p"
	.string "Did you find your way from\n"
	.string "Route 49 okay..?\p"
	.string "You did? Good.\n"
	.string "Let's keep this short then...!$"

NewSinjoh_KimonoHideout_Youko_Beaten:
    .string "That was a good battle..!$"

NewSinjoh_Kimono_Hideout_YoukoGivesIciclePlate:
    .string "I see why our cousins trust you.\p"
	.string "Here, take this..\n"
	.string "My eldest sister is waiting..$"

NewSinjoh_Kimono_Text_Youko2:
    .string "I wish you good luck on\n"
	.string "your adventures and in life..$"

NewSinjoh_Kimono_EventScript_Shizuko1::
    lock 
	goto_if_eq VAR_NEWSINOH_KIMONO_TRACKER, 2, NewSinjoh_Kimono_EventScript_Shizuko2
	applymovement LOCALID_YOUKO, NewSinjoh_Youko1_Movement
	waitmovement
	msgbox NewSinjoh_Kimomo_BattleUsFirst_Text MSGBOX_DEFAULT
	applymovement LOCALID_YOUKO, NewSinjoh_Youko2_Movement
	waitmovement
	release
	end

NewSinjoh_Kimono_EventScript_Shizuko2::
	faceplayer
	goto_if_set FLAG_NEWSINJOH_KIMONOGIRLFAIRY, NewSinjoh_Kimono_EventScript_Shizuko3
	playse SE_PIN
	applymovement LOCALID_SHIZUKO, Common_Movement_ExclamationMark
	applymovement LOCALID_SHIZUKO, NewSinjoh_Shizuko_JumpInPlace_Movement
	waitmovement
	waitmovement
	msgbox NewSinjoh_KimonoHideout_Shizuko_Text MSGBOX_DEFAULT
	applymovement LOCALID_SHIZUKO, NewSinjoh_Kimono_Dance_Movement
	waitmovement
	settotemboost B_POSITION_OPPONENT_LEFT, 2, 2,0, 0, 2, 2, 0
    trainerbattle_no_intro TRAINER_SHIZUKO_HNS, NewSinjoh_KimonoHideout_Shizuko_Beaten
    goto NewSinjoh_Kimono_Shizuko_AfterBattle


NewSinjoh_Kimono_Shizuko_AfterBattle::
    msgbox NewSinjoh_Kimono_Hideout_ShizukoGivesPixiePlate MSGBOX_DEFAULT
	delay 8
    giveitem ITEM_PIXIE_PLATE, 1
	compare VAR_RESULT, 0
	goto_if_eq NewSinjoh_KimonoHideout_EventScript_BagIsFull
	addvar VAR_PLATECOUNTER, 1
	setflag FLAG_NEWSINJOH_KIMONOGIRLFAIRY
	msgbox NewSinjoh_Shizuko_Final_Text MSGBOX_DEFAULT
	release
	end

NewSinjoh_Kimono_EventScript_Shizuko3::
    msgbox NewSinjoh_Kimono_Text_Shizuko3 MSGBOX_DEFAULT
	release
	end

NewSinjoh_Youko1_Movement:
    face_left
	walk_in_place_slow_left
	walk_in_place_slow_left
	step_end

NewSinjoh_Youko2_Movement:
    face_down
	step_end


NewSinjoh_Kimomo_BattleUsFirst_Text:
    .string "I'm sorry {PLAYER}...\n"
	.string "My big sister is very picky..\l"
	.string "She won't talk to anyone\l"
	.string "she doesn't think is worthy enough..\p"
	.string "Please try to defeat us first\n"
	.string "then she might talk to you..$"


NewSinjoh_Shizuko_JumpInPlace_Movement:
    jump_in_place_left_right
	face_player
	step_end

NewSinjoh_KimonoHideout_Shizuko_Text:
    .string "ALRIGHT!!!!\p"
	.string "Those battles got me all fired up!!\n"
	.string "{PLAYER}! You better not\l"
	.string "hold back because I Won't!$"


NewSinjoh_KimonoHideout_Shizuko_Beaten:
    .string "I can't believe how strong you are!$"


NewSinjoh_Kimono_Hideout_ShizukoGivesPixiePlate:
    .string "That battle was fantastic!\n"
	.string "You really are the best there is huh?\p"
	.string "Here, take this!$"

NewSinjoh_Shizuko_Final_Text:
    .string "There's 18 of those plates total\n"
	.string "in the world.\p"
	.string "If you manage to collect all of them\n"
	.string "Our Lord might finally reveal\l"
	.string "themselves again!$"

NewSinjoh_Kimono_Text_Shizuko3:
    .string "Yo! Good luck out there alright?\n"
	.string "Just know that we're rootin'\l"
	.string "for you and wishing you the best!$"


NewSinjoh_KimonoHideout_EventScript_BagIsFull::
	msgbox NewSinjoh_Kimono_Text_BagIsFull, MSGBOX_DEFAULT
	release
	end

NewSinjoh_Kimono_Dance_Movement:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_up
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_up
	delay_8
	face_player
	step_end

NewSinjoh_Kimono_Text_BagIsFull:
    .string "Your BAG is full..\n"
	.string "Please make space and\l"
	.string "return to me again.$"

NewSinjoh_KimonoHideout_EventScript_OldMan::
    lock
	faceplayer
	msgbox NewSinjoh_Kimono_OldMan_Text MSGBOX_DEFAULT
	release
	end

NewSinjoh_Kimono_OldMan_Text:
    .string "Aren't my daughters beautiful?\p"
	.string "They've prayed to the true lord\n"
	.string "for as long as i can remember..\p"
	.string "Because of that, he has blessed\n"
	.string "them with powers beyond that\l"
	.string "of any normal trainer!\p"
	.string "That is to say, be prepared\n"
	.string "before fighting them young one.$"