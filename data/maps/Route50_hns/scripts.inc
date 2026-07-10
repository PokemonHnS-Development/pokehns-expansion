Route50_hns_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Route50_hns_OnTransition
	.byte 0

Route50_hns_OnTransition::
    goto_if_unset FLAG_NOBLES_UNLOCKED, Route50_Hide_Noble
	end

Route50_Hide_Noble::
    removeobject LOCALID_NOBLE_KLEAVOR
	removeobject LOCALID_NOBLE_SNEASLER
	release
	end


Route50_EventScript_Noble_Kleavor_Trigger::
    goto_if_set FLAG_NOBLES_UNLOCKED, Route50_EventScript_Kleavor
	end

Route50_EventScript_Noble_Sneasler_Trigger::
    goto_if_set FLAG_NOBLES_UNLOCKED, Route50_EventScript_Sneasler
	end



Route50_EventScript_Kleavor::
	lock
	addobject LOCALID_NOBLE_KLEAVOR
	applymovement LOCALID_NOBLE_KLEAVOR, Route50_Kleavor_Movement
	delay 110
	playse SE_BIKE_HOP
	waitmovement
	setwildbossbattle species=SPECIES_KLEAVOR, level=80, item=ITEM_SCOPE_LENS, move1_1=MOVE_STONE_AXE, move1_2=MOVE_CROSS_POISON, move1_3=MOVE_LUNGE move1_4=MOVE_FOCUS_ENERGY
	waitse
	playmoncry SPECIES_KLEAVOR, CRY_MODE_ENCOUNTER
	msgbox Route50_Text_KleavorCry MSGBOX_DEFAULT
	waitmessage
	waitmoncry
	delay 10
	waitbuttonpress
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 2, 0, 0, 2, 0
	playbgm MUS_HG_VS_SUICUNE, 0
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route50_EventScript_DefeatedKleavor
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route50_EventScript_RanFromKleavor
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Route50_EventScript_RanFromKleavor
	setflag FLAG_FOUGHT_NOBLE_KLEAVOR
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NOBLE_KLEAVOR
	fadescreen FADE_FROM_BLACK
    DELAY 30
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox Route50_Text_InsectPlate MSGBOX_DEFAULT
	giveitem ITEM_INSECT_PLATE, 1
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NOBLECOUNTER, 1
	addvar VAR_NOBLE_KLEAVOR_TRIGGER, 1
	closemessage
	release
	end

Route50_EventScript_DefeatedKleavor::
	setflag FLAG_FOUGHT_NOBLE_KLEAVOR
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NOBLE_KLEAVOR
	fadescreen FADE_FROM_BLACK
    delay 30
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox Route50_Text_InsectPlate MSGBOX_DEFAULT
	giveitem ITEM_INSECT_PLATE, 1
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NOBLECOUNTER, 1
	addvar VAR_NOBLE_KLEAVOR_TRIGGER, 1
	closemessage
	release
	end

Route50_EventScript_RanFromKleavor::
	setvar VAR_0x8004, SPECIES_KLEAVOR
	end

Route50_Text_KleavorCry:
    .string "Scrraahh!!$"

Route50_Text_InsectPlate:
    .string "It seems KLEAVOR left something behind..$"

Route50_Kleavor_Movement:
    walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_down
	walk_left
	jump_down
	face_down
	step_end

Route50_EventScript_Sneasler::
	lock
	addobject LOCALID_NOBLE_SNEASLER
	applymovement LOCALID_NOBLE_SNEASLER, Route50_Sneasler_Movement
	delay 60
	playse SE_BIKE_HOP
	waitmovement
	setwildbossbattle species=SPECIES_SNEASLER, level=80, item=ITEM_RAZOR_CLAW, move1_1=MOVE_DIRE_CLAW, move1_2=MOVE_ROCK_SLIDE, move1_3=MOVE_BRICK_BREAK move1_4=MOVE_LASH_OUT
	waitse
	playmoncry SPECIES_SNEASLER, CRY_MODE_ENCOUNTER
	msgbox Route50_Text_SneaslerCry MSGBOX_DEFAULT
	waitmessage
	waitmoncry
	delay 10
	waitbuttonpress
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 0, 2, 0, 0, 0
	playbgm MUS_HG_VS_SUICUNE, 0
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route50_EventScript_DefeatedSneasler
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route50_EventScript_RanFromSneasler
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Route50_EventScript_RanFromSneasler
	setflag FLAG_FOUGHT_NOBLE_SNEASLER
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NOBLE_SNEASLER
	fadescreen FADE_FROM_BLACK
    DELAY 30
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox Route50_Text_ToxicPlate MSGBOX_DEFAULT
	giveitem ITEM_TOXIC_PLATE, 1
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NOBLECOUNTER, 1
	addvar VAR_NOBLE_SNEASLER_TRIGGER, 1
	closemessage
	release
	end

Route50_EventScript_DefeatedSneasler::
	setflag FLAG_FOUGHT_NOBLE_SNEASLER
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NOBLE_SNEASLER
	fadescreen FADE_FROM_BLACK
    delay 30
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox Route50_Text_ToxicPlate MSGBOX_DEFAULT
	giveitem ITEM_TOXIC_PLATE, 1
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NOBLECOUNTER, 1
	addvar VAR_NOBLE_SNEASLER_TRIGGER, 1
	closemessage
	end

Route50_EventScript_RanFromSneasler::
	setvar VAR_0x8004, SPECIES_SNEASLER
	end

Route50_Text_SneaslerCry:
    .string "Wrrhehe!!$"

Route50_Text_ToxicPlate:
    .string "It seems SNEASLER left something behind..$"

Route50_Sneasler_Movement:
    walk_down
	walk_down
	walk_down
	walk_down
	jump_down
	face_down
	step_end


Route50_EventScript_Channeler_Youmu::
    lock
	faceplayer
	goto_if_set FLAG_DEFEATED_CHANNELERYOUMU, Route50_EventScript_Youmu_AfterBattle
	msgbox Route50_Youmu_Encounter_Text MSGBOX_DEFAULT
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 6, 0, 0, 6, 3, 0
    trainerbattle_no_intro TRAINER_YOUMU_HNS, Route50_Youmu_Defeat_Text
    goto Route50_EventScript_Youmu_AfterBattle


Route50_EventScript_Youmu_AfterBattle::
    setflag FLAG_DEFEATED_CHANNELERYOUMU
    msgbox Route50_Youmu_GivesDreadPlate_Text MSGBOX_DEFAULT
	delay 8
    giveitem ITEM_DREAD_PLATE, 1
	compare VAR_RESULT, 0
	goto_if_eq Route50_EventScript_Youmu_BagIsFull
	addvar VAR_PLATECOUNTER, 1
	closemessage
	delay 30
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_YOUMU
	removeobject LOCALID_YOUMU_ABSOL
	setflag FLAG_ROUTE50_CHANNELER_YOUMU
	fadescreen FADE_FROM_BLACK
	delay 10
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	applymovement LOCALID_PLAYER, Route50_PlayerJumps_Movement
	waitse
	waitmovement
	waitmovement
	msgbox Route50_TheyreGone_Text MSGBOX_DEFAULT
	release
	end

Route50_Youmu_Encounter_Text:
    .string "You..You must be the one.\n"
	.string "The one my partner warned me about.\p"
	.string "I don't know who you are,\n"
	.string "but I'll stop you before it's\l"
	.string "to late!!$"

Route50_Youmu_Defeat_Text:
    .string "Those bonds...no being capable\n"
	.string "of true destrucion could have\l"
	.string "friendships like those..!$"

Route50_Youmu_GivesDreadPlate_Text:
    .string "Perhaps you aren't the danger\n"
	.string "they speak of..but the one to stop it?\p"
	.string "That must be the case..!\n"
	.string "If that is the case then please...\l"
	.string "take this..and be careful..$"

Route50_EventScript_Youmu_BagIsFull::
    msgbox Route50_YourBagIsFull_Text MSGBOX_DEFAULT
	release
	end

Route50_YourBagIsFull_Text:
    .string "You seem to already be\n"
	.string "at your limits...\p"
	.string "Please make space in that BAG\n"
	.string "of yours and return to me..$"

Route50_PlayerJumps_Movement:
    jump_in_place_up
	step_end

Route50_TheyreGone_Text:
   .string "They disappeared..?!$"

Route50_EventScript_Absol::
	lock
	faceplayer
	playmoncry SPECIES_ABSOL, 0
	msgbox Route50_Text_CryAbsol, MSGBOX_DEFAULT
	waitmoncry
        closemessage
	release
	end

Route50_Text_CryAbsol:
	.string "Grrr!$"

Route50_EventScript_PsychicRonan::
    trainerbattle_single TRAINER_RONAN_HNS, Route50_Text_PsychicRonan_Seen, Route50_Text_PsychicRonan_Beaten
    msgbox Route50_Text_PsychicRonan_After, MSGBOX_AUTOCLOSE
    end


Route50_Text_PsychicRonan_Seen:
    .string "Your fate is sealed!\n"
    .string "For I have forseen your fall!!$"

Route50_Text_PsychicRonan_Beaten:
    .string "Was my prediction wrong?!$"

Route50_Text_PsychicRonan_After:
    .string "Perhaps the future isn't set\p"
	.string "in stone afterall...$"


Route50_EventScript_NerdMaxwell::
    trainerbattle_single TRAINER_MAXWELL2_HNS, Route50_Text_NerdMaxwell_Seen, Route50_Text_NerdMaxwell_Beaten
    msgbox Route50_Text_NerdMaxell_After, MSGBOX_AUTOCLOSE
    end


Route50_Text_NerdMaxwell_Seen:
    .string "The power of technology is incredible..\n"
    .string "Allow me to show you real power..$"

Route50_Text_NerdMaxwell_Beaten:
    .string "My teams all out of batteries!$"

Route50_Text_NerdMaxell_After:
    .string "Hmpph.\p"
	.string "You only won because extreme cold\n"
	.string "is bad for technology!$"


Route50_EventScript_FireBreather_Edwin::
    trainerbattle_double TRAINER_EDWIN2_HNS, Route50_Text_FireBreather_Edwin_Seen, Route50_Text_FireBreather_Edwin_Beaten, Route50_Text_FireBreather_Edwin_NotEnoughMons
	special GetPlayerBigGuyGirlString
    msgbox Route50_Text_FireBreather_Edwin_After, MSGBOX_AUTOCLOSE
    end


Route50_Text_FireBreather_Edwin_Seen:
    .string "Let's light this party up!$"

Route50_Text_FireBreather_Edwin_Beaten:
    .string "I'm all burnt up!$"

Route50_Text_FireBreather_Edwin_After:
    .string "Your flame burns way brighter\n"
	.string "than my own!$"

Route50_Text_FireBreather_Edwin_NotEnoughMons:
    .string "You don't seem to have enough\n"
	.string "fuel for your fire there partner!\p"
	.string "Why don't we party after you fill\n"
	.string "out your PARTY some more eh?$"

Route50_EventScript_BikerBram::
    trainerbattle_single TRAINER_BRAM_HNS, Route50_Text_BikerBram_Seen, Route50_Text_BikerBram_Beaten
    msgbox Route50_Text_BikerBram_After, MSGBOX_AUTOCLOSE
    end


Route50_Text_BikerBram_Seen:
    .string "Oi oi!!\n"
    .string "Get out of the way!!$"

Route50_Text_BikerBram_Beaten:
    .string "Woah woah!! Calm down now,\n"
    .string "I wasn't being serious!$"

Route50_Text_BikerBram_After:
    .string "Alright kid, you're good.\p"
	.string "I can respect pure strength.$"


Route50_EventScript_BikerKyle::
    trainerbattle_single TRAINER_KYLE9_HNS, Route50_Text_BikerKyle_Seen, Route50_Text_BikerKyle_Beaten
    msgbox Route50_Text_BikerKyle_After, MSGBOX_AUTOCLOSE
    end


Route50_Text_BikerKyle_Seen:
    .string "Whatcha doin' getting in my way?!\n"
    .string "Are you cruisin' for a brusin'?$"

Route50_Text_BikerKyle_Beaten:
    .string "Woah woah!! Calm down now,\n"
    .string "I wasn't being serious!$"

Route50_Text_BikerKyle_After:
    .string "Alright kid, you're good.\p"
	.string "I can respect your strength.$"


Route50_EventScript_AnnoyingFisherman::
    lock
	faceplayer
	msgbox Route50_Fisherman_ImStandingHereToAnnoyThePlayer_Text MSGBOX_DEFAULT
	release
	end

Route50_Fisherman_ImStandingHereToAnnoyThePlayer_Text:
    .string "Isn't this view amazing?\p"
	.string "This is such a convinent spot\n"
	.string "to stand to take in the views!$"

Route50_EventScript_PicknickerDawn::
    trainerbattle_single TRAINER_DAWN9_HNS, Route50_Text_PicknickerDawn_Seen, Route50_Text_PicknickerDawn_Beaten
    msgbox Route50_Text_PicknickerDawn_After, MSGBOX_AUTOCLOSE
    end


Route50_Text_PicknickerDawn_Seen:
    .string "I'm so glad my parents\n"
	.string "let me come here!\p"
	.string "Isn't this place perfect for a battle?$"

Route50_Text_PicknickerDawn_Beaten:
    .string "See? I told you this is the\n"
	.string "perfect spot for a battle!$"

Route50_Text_PicknickerDawn_After:
    .string "If we ever meet again..\n"
	.string "Let's have a rematch 'kay?$"


Route50_EventScript_Bibarel::
	lock
	faceplayer
	playmoncry SPECIES_BIBAREL, 0
	msgbox Route50_Text_CryBibarel, MSGBOX_DEFAULT
	waitmoncry
        closemessage
	release
	end

Route50_Text_CryBibarel:
	.string "Dgg Dgg!$"

Route50_Script_Walrein::
	lock
	faceplayer
	playmoncry SPECIES_WALREIN, 0
	msgbox Route50_Text_CryWalrein, MSGBOX_DEFAULT
	waitmoncry
        closemessage
	release
	end

Route50_Text_CryWalrein:
	.string "Wrruhh?$"


Route50_EventScript_Juggler::
    lock
	faceplayer
	msgbox Route50_Juggler_Text MSGBOX_DEFAULT
	release
	end

Route50_Juggler_Text:
    .string "Bet you thought I was a trainer huh?\p"
	.string "Nah, I'm just waiting for my\n"
	.string "big bro to come down from\l"
	.string "that hill over there.$"


Route50_EventScript_Item_ULtraBall::
    finditem ITEM_ULTRA_BALL
    end

Route50_EventScript_Item_Big_Nugget::
    finditem ITEM_BIG_NUGGET
    end