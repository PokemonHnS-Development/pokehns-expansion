SinjohRuins_House1_hns_MapScripts::
    map_script MAP_SCRIPT_ON_FRAME_TABLE, SinjohRuins_House1_hns_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, SinjohRuins_House1_hns_OnTransition
	.byte 0

SinjohRuins_House1_hns_OnTransition::
	end

SinjohRuins_House1_hns_OnFrame::
    map_script_2 VAR_STEVEN_GROUP_INTRODUCTION, 0, SinjohRuins_House1_EventScripts_Steven_Intro_Yapping
	.2byte 0

SinjohRuins_EventScript_AddingSteven::
    setobjectxyperm LOCALID_HOUSE1_STEVENSTONE2, 15, 25
	end

SinjohRuins_House1_EventScripts_Steven_Intro_Yapping::
    lock
	applymovement LOCALID_HOUSE1_STEVENSTONE, SinjohRuins_Steven_Movement_FinishesWalk
	applymovement LOCALID_PLAYER, SinjohRuins_Player_Movement_FinishesWalk
	waitmovement 0
	waitmovement 0
	delay 10
	msgbox SinjohRuins_House1_Text_StevenTalksAboutRecentEvents MSGBOX_DEFAULT
	closemessage
	playse SE_PIN
	applymovement LOCALID_WISEOLDLADY, Common_Movement_ExclamationMark
	waitmovement 0
	delay 10
	applymovement LOCALID_WISEOLDLADY, SinjohRuins_House1_Movement_WiseOldLady_MovesDown
	waitmovement 0
	delay 8
	msgbox SinjohRuins_House1_Text_OldLady_TalksAboutForms MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_HOUSE1_STEVENSTONE, SinjohRuins_House1_Movement_StevenWaddles
	waitmovement 0
	msgbox SinjohRuins_Text_StevenFinishesTalking MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_House1_StevenAsksAgain
	msgbox SinjohRuins_House1_Text_StevenSends_PlayerOff MSGBOX_DEFAULT
	addvar VAR_STEVEN_GROUP_INTRODUCTION, 1
	setflag FLAG_SINJOHRUINS_HOUSE1_STEVENSTONE_INTRO_YAPPINGDONE
	release
	end

SinjohRuins_Steven_Movement_FinishesWalk:
    walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right 
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	face_right
	step_end

SinjohRuins_Player_Movement_FinishesWalk:
    walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
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
	walk_down
	walk_down
	walk_down
	face_left
	step_end

SinjohRuins_House1_Movement_WiseOldLady_MovesDown:
    walk_slow_left
	walk_slow_left
	walk_slow_down
	walk_slow_left
	walk_slow_left
	step_end

SinjohRuins_House1_Movement_StevenWaddles:
    walk_in_place_right
	walk_in_place_right
	step_end

SinjohRuins_House1_Text_StevenTalksAboutRecentEvents:
    .string "See! Isn't this place much\n"
	.string "better for conversation?\l"
	.string "Now, onto the topic at hand.\l"
	.string "Recently these ruins were discovered\l"
	.string "deep under the snow, until the\l"
	.string "team here dug it up!\p"
	.string "The chamber inside the main\n"
	.string "structure shares a lot of resemblance\l"
	.string "to ruins spotted in both\l"
	.string "the Sinnoh and Hoenn reigons.\p"
	.string "So they asked for my assistance\n"
	.string "on getting to the bottom of this.$"

SinjohRuins_House1_Text_OldLady_TalksAboutForms:
    .string "Yes, my dearest husband did...\n"
	.string "You see.. after my husband and\l"
	.string "his team tried opening any of\l"
	.string "the lesser chambers..\p"
	.string "A strange energy blasted out\n"
	.string "from the very earth itself!\p"
	.string "Since then, several strange POKEMON\n"
	.string "have appeared nearby and well..\p"
	.string "They seem to resemble POKEMON\n"
	.string "from a time long long ago..$"

SinjohRuins_Text_StevenFinishesTalking:
    .string "Thank you Rosalyne,\n"
	.string "but I can take it from here.\p"
	.string "These anicent POKEMON are from\n"
	.string "a land called Hisui.\p"
	.string "Although, nowadays that reigon\n"
	.string "is actually called Sinnoh!\p"
	.string "So our task is this,\n"
	.string "we must catch these ancient POKEMON,\l"
	.string "go deeper into the ruins and\l"
	.string "uncover the source of that\l"
	.string "mysterious light!\p"
	.string "Are you in?$"


SinjohRuins_House1_StevenAsksAgain::
    msgbox SinjohRuins_House1_Text_StevenAsksAgain MSGBOX_DEFAULT
	waitmessage
	msgbox SinjohRuins_House1_Text_StevenSends_PlayerOff2 MSGBOX_DEFAULT
	closemessage
	addvar VAR_STEVEN_GROUP_INTRODUCTION, 1
	setflag FLAG_SINJOHRUINS_HOUSE1_STEVENSTONE_INTRO_YAPPINGDONE
	release
	end

SinjohRuins_House1_Text_StevenAsksAgain:
    .string "I see you're trying to be\n"
	.string "careful with your choice,\l"
	.string "but time is of the essance.$"

SinjohRuins_House1_Text_StevenSends_PlayerOff:
    .string "Alright!\n"
	.string "That's the answer I was looking for!\p"
	.string "Now, there is some work\n"
	.string "I must do here, but I will\l"
	.string "catch up once I finish.$"

SinjohRuins_House1_Text_StevenSends_PlayerOff2:
	.string "Now, there is some work\n"
	.string "I must do here, but I will\l"
	.string "catch up once I finish.\p"
	.string "Please feel free to head\n"
	.string "into the main structure\l"
	.string "or search around for the\l"
	.string "Hisuian forms.$"

SinjohRuins_House1_StevenFaceRight:
    face_right
	step_end


SinjohRuins_House1_Scientist_Male1::
    lock
	faceplayer
	msgbox SinjohRuins_House1_Text_MS1 MSGBOX_DEFAULT
	closemessage
	release
	end

SinjohRuins_House1_Text_MS1:
    .string "I'm currently working on mapping\n"
	.string "the ruins with GPR and my partner!\l"
	.string "So far we've discovered\n"
	.string "6 subterrainian chambers!$"

SinjohRuins_House1_Scientist_Female1::
    lock
	faceplayer
    msgbox SinjohRuins_House1_Text_FS1 MSGBOX_DEFAULT
	closemessage
	release
	end

SinjohRuins_House1_Text_FS1:
    .string "Ugh....\n"
	.string "There's so many gliphs\l"
	.string "to translate..\p"
	.string "But it'll be worth it in the\n"
	.string "end if something amazing happens!$"

SinjohRuins_House1_Scientist_Female2::
    lock
	faceplayer
    msgbox SinjohRuins_House1_Text_FS2 MSGBOX_DEFAULT
	closemessage
	release
	end

SinjohRuins_House1_Text_FS2:
    .string "That flute you're carrying...\n"
	.string "It's known as the Azure Flute.\p"
	.string "There is a legend that states when\n"
	.string "it is played with all 18 plates\l"
	.string "nearby, a stairway that pierces\l"
	.string "the sky shall appear.\p"
	.string "If you have such a thing...\n"
	.string "maybe it was a good thing boss\l"
	.string "sent that request for help\l"
	.string "from Mr.Steven Stone.$"

SinjohRuins_House1_Growlithe_Hisui::
    lock
	faceplayer
	playmoncry SPECIES_GROWLITHE, 0
	msgbox Snowswept_Text_Growlithe_Cry, MSGBOX_DEFAULT
	waitmoncry
    closemessage
	release
	end

Snowswept_Text_Growlithe_Cry:
    .string "Growh owh!!$"

SinjohRuins_EventScript_GrowlithePokeball::
    lock
    msgbox SinjohRuins_House1_Text_GrowlitheBall MSGBOX_DEFAULT
	closemessage
	release
	end

SinjohRuins_House1_Text_GrowlitheBall:
    .string "This appears to be Growlithe's ball..\n"
	.string "I better leave it alone.$"

SinjohRuins_House1_Scientist_Male2::
    lock
	faceplayer
	msgbox SinjohRuins_House1_Text_MS2 MSGBOX_DEFAULT
	release
	end

SinjohRuins_House1_Text_MS2:
    .string "Look at this wonderful specimen!\n"
	.string "Isn't he just the goodest boy?$"

SinjohRuins_House1_Rosalyne::
    lock
	faceplayer
	msgbox SinjohRuins_Text_Rosalyne_BeforeCompletion MSGBOX_DEFAULT
	closemessage
	release
	end

SinjohRuins_Text_Rosalyne_BeforeCompletion:
    .string "Hello there {PLAYER}...\n"
	.string "How are you doing today?\p"
	.string "Please make sure to take\n"
	.string "breaks while helping my husband..$"

