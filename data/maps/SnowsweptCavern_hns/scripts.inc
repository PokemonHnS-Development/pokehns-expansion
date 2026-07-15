SnowsweptCavern_hns_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, SnowsweptCavern_hns_OnTransition
    .byte 0

SnowsweptCavern_hns_OnTransition::
    setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_DOORLOCK
    setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_GRAVELIGHT_N
    setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_GRAVELIGHT_W
    setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_GRAVELIGHT_E
    setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_GRAVELIGHT_S
    setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_FROSLASS
    setflag FLAG_FOUGHT_NOBLE_ELECTRODE
    setflag FLAG_FOUGHT_NOBLE_ARCANINE
    setflag FLAG_FOUGHT_NOBLE_SNEASLER
    setflag FLAG_FOUGHT_NOBLE_KLEAVOR
    setflag FLAG_FOUGHT_NOBLE_URSALUNA 
    setvar VAR_PLATECOUNTER, 0
    end


Snowswept_EventScript_GentlemanRubert::
    trainerbattle_single TRAINER_RUBERT_HNS, Snowswept_Text_GentlemanRubert_Seen, Snowswept_Text_GentlemanRubert_Beaten
    msgbox Snowswept_Text_GentlemanRubert_After, MSGBOX_AUTOCLOSE
    end


Snowswept_Text_GentlemanRubert_Seen:
    .string "Youngsters like you shouldn't\n"
    .string "be in fridged places like this!$"

Snowswept_Text_GentlemanRubert_Beaten:
    .string "ERk..You are clearly no ordinary\n"
    .string "kid...$"

Snowswept_Text_GentlemanRubert_After:
    .string "Up ahead is a massive hot spring!\n"
    .string "I came up here to cool off!$"

Snowswept_EventScript_HikerNicholas::
    trainerbattle_single TRAINER_NICHOLAS_HNS, Snowswept_Text_HikerNicholas_Seen, Snowswept_Text_HikerNicholas_Beaten
    msgbox Snowswept_Text_HikerNicholas_After, MSGBOX_AUTOCLOSE
    end


Snowswept_Text_HikerNicholas_Seen:
    .string "Now you look like a real\n"
    .string "challenge!$"

Snowswept_Text_HikerNicholas_Beaten:
    .string "Hah! Your resolve is as hard\n"
    .string "as my Pokemon!$"

Snowswept_Text_HikerNicholas_After:
    .string "That was an exceptional\n"
    .string "battle kid!$"

Snowswept_EventScript_SwimmerMakayla::
    trainerbattle_single TRAINER_MAKAYLA_HNS, Snowswept_Text_SwimmerMakayla_Seen, Snowswept_Text_SwimmerMakayla_Beaten
    msgbox Snowswept_Text_SwimmerMakayla_After, MSGBOX_AUTOCLOSE
    end


Snowswept_Text_SwimmerMakayla_Seen:
    .string "Hey!\n"
    .string "Watch where you're swimming!$"

Snowswept_Text_SwimmerMakayla_Beaten:
    .string "Wait, what do you mean\n"
    .string "this isn't the beach?$"

Snowswept_Text_SwimmerMakayla_After:
    .string "Huh..\n"
    .string "I was wondering why it was so cold\n"
    .string "and why the water was slippery.$"

Snowswept_EventScript_CoolNia::
    trainerbattle_single TRAINER_NIA_HNS, Snowswept_Text_CoolNia_Seen, Snowswept_Text_CoolNia_Beaten
    msgbox Snowswept_Text_CoolNia_After, MSGBOX_AUTOCLOSE
    end


Snowswept_Text_CoolNia_Seen:
    .string "I see you!\n"
    .string "Y'know what that means right?\l"
    .string "It's time to battle!$"

Snowswept_Text_CoolNia_Beaten:
    .string "Awww dang it!\n"
    .string "How are you this strong?!$"

Snowswept_Text_CoolNia_After:
    .string "Man you're strong!\n"
    .string "It's almost like you're a champion\l"
    .string "or something!\p"
    .string "Wait, you are?!$"

Snowswept_EventScript_CoolJohn::
    trainerbattle_single TRAINER_JOHN_1_HNS, Snowswept_Text_CoolJohn_Seen, Snowswept_Text_CoolJohn_Beaten
    msgbox Snowswept_Text_CoolJohn_After, MSGBOX_AUTOCLOSE
    end


Snowswept_Text_CoolJohn_Seen:
    .string "Yo! You look tough!\n"
    .string "Let's see who's stronger!$"

Snowswept_Text_CoolJohn_Beaten:
    .string "Now that is some impressive\n"
    .string "power you're packing there!$"

Snowswept_Text_CoolJohn_After:
    .string "Hey hey!\n"
    .string "You're incredibly powerful,\l"
    .string "Mind giving me a few tips?$"

Snowswept_EventScript_HikerSnape::
    trainerbattle_single TRAINER_SNAPE_HNS, Snowswept_Text_HikerSnape_Seen, Snowswept_Text_HikerSnape_Beaten
    msgbox Snowswept_Text_HikerSnape_After, MSGBOX_AUTOCLOSE
    end


Snowswept_Text_HikerSnape_Seen:
    .string "You'll make a great sssnack\n"
    .string "for my team!$"

Snowswept_Text_HikerSnape_Beaten:
    .string "Hey now!\n"
    .string "I was just joking y'know?$"

Snowswept_Text_HikerSnape_After:
    .string "How'd you like my team though?\n"
    .string "I found them all hiding under\l"
    .string "rocks as i climbed up this mountain!$"

Snowswept_EventScript_BlackBelt_Terry::
    lock
    faceplayer
	goto_if_eq VAR_SNOWSWEPT_TERRY_BOULDER, 1, Snowswept_Terry_PostHelp
    msgbox Snowswept_Text_Terry_Challenge, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, FALSE, Snowswept_Text_Terry_NotYet
    trainerbattle_no_intro TRAINER_TERRY_HNS, Snowswept_Text_BlackBelt_Terry_Beaten
    goto Snowswept_Terry_AfterBattle

Snowswept_Terry_AfterBattle::
    applymovement LOCALID_TERRY, Snowswept_Terry_Movement
    waitmovement
    msgbox Snowswept_Text_TerryMachamp_Command
    delay 25
    applymovement LOCALID_TERRY_MACHAMP, Snowswept_Machamp_Movement
    waitmovement
    playmoncry SPECIES_MACHAMP, 0
    msgbox Snowswept_Text_Machamp_Cry MSGBOX_DEFAULT
    waitmoncry
    closemessage
        setvar VAR_0x8004, 1  @ vertical pan
    setvar VAR_0x8005, 1  @ horizontal pan
    setvar VAR_0x8006, 10  @ num shakes
    setvar VAR_0x8007, 4  @ shake delay
    special ShakeCamera
    waitstate
    applymovement LOCALID_BOULDER, Snowswept_Boulder_Movement
    waitmovement
    delay 10
    faceplayer
    msgbox Snowswept_Text_Terry_GoodToGo MSGBOX_DEFAULT
    setvar VAR_SNOWSWEPT_TERRY_BOULDER, 1
    setobjectxyperm LOCALID_BOULDER, 52, 56
    release
    end

Snowswept_Terry_PostHelp::
    msgbox Snowswept_Text_Terry_HelloAgain
    release
    end

Snowswept_Text_Terry_Challenge:
    .string "I saw you slippin' and sliding\n"
    .string "from up here!\l"
    .string "Also saw those battles you\l"
    .string "did as well.\p"
    .string "How about this, you beat\n"
    .string "me and my MACHAMP here\l"
    .string "and we'll help you across.\l"
    .string "Sound like a deal?$"

Snowswept_Text_Terry_NotYet:
    .string "Need some time to think\n"
    .string "about it huh?\p"
    .string "Fine by me.$"

Snowswept_Text_BlackBelt_Terry_Seen:
    .string "Alright\n"
    .string "That's what I'm talking about!\l"
    .string "Let's do this MACHAMP!$"

Snowswept_Text_BlackBelt_Terry_Beaten:
    .string "That battle was spectacular!$"

Snowswept_Terry_Movement:
    jump_in_place_right
    walk_in_place_right
    step_end

Snowswept_Text_TerryMachamp_Command:
    .string "Alright MACHAMP, use\n"
    .string "Cross Chop to knock that\l"
    .string "boulder down the hill!$"

Snowswept_Text_Machamp_Cry:
    .string "Mahh!!$"

Snowswept_Machamp_Movement:
    jump_in_place_up
    walk_in_place_fast_up
    walk_in_place_fast_up
    step_end

Snowswept_Boulder_Movement:
    walk_fast_down
    walk_fast_down
    walk_fast_down
    walk_fast_down
    walk_fast_down
    walk_fast_down
    step_end

Snowswept_Text_Terry_GoodToGo:
    .string "You should be able to cross\n"
    .string "safely now!\p"
    .string "Don't be a stranger you hear?!$"

Snowswept_Text_Terry_HelloAgain:
    .string "It's nice to see you again {PLAYER}!\p"
    .string "How have you been?$"

Snowswept_EventScript_BattleGirl::
    lock
    faceplayer
    msgbox Snowswept_Text_BattleGirl, MSGBOX_DEFAULT
    release
    end

Snowswept_Text_BattleGirl:
    .string "This cave is perfect\n"
    .string "for endurance training!\p"
    .string "The cold keeps me from sweating\n"
    .string "and there's plenty of rocks\l"
    .string "to lift and smash!!$"

Snowswept_EventScript_BoulderPlacer::
    goto_if_eq VAR_SNOWSWEPT_TERRY_BOULDER, 1, Snowswept_EventScript_Boulder
    end

Snowswept_EventScript_Boulder:;
    setobjectxyperm LOCALID_BOULDER, 52, 56
    end

Snowswept_EventScript_Camper::
    lock
    faceplayer
    msgbox Snowswept_Text_Camper
    closemessage
    face_right
    release
    end

Snowswept_Text_Camper:
    .string "SHH!!\p"
    .string "I'm trying to watch the wild\n"
    .string "POKEMON train over there!$"

Snowswept_EventScript_Sign::
    lock
    msgbox Snowswept_Text_Sign
    release
    end

Snowswept_Text_Sign:
    .string "CAUTION!\p"
    .string "Slippery surfaces ahead!\n"
    .string "Please put your POKEMON away\l"
    .string "in their ball for both\l"
    .string "their safetly and yours.$"

Snowswept_EventScript_VibingMachamp::
    lock
	faceplayer
	playmoncry SPECIES_MACHAMP, 0
	msgbox Snowswept_Text_Machamp_Cry2, MSGBOX_DEFAULT
	waitmoncry
    closemessage
	release
	end

Snowswept_Text_Machamp_Cry2:
    .string "Mahh!!$"

Snowswept_EventScript_Item_NeverMeltIce::
    finditem ITEM_NEVER_MELT_ICE
    end

Snowswept_EventScript_Item_UltraBall::
    finditem ITEM_ULTRA_BALL
    end

