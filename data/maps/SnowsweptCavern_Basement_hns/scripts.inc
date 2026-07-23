SnowsweptCavern_Basement_hns_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, SnowsweptCaverns_Basement_hns_OnTransition
	.byte 0

SnowsweptCaverns_Basement_hns_OnTransition::
    goto_if_unset FLAG_NOBLES_UNLOCKED, SnosweptCaverns_Basement_Hide_Noble
    end

SnosweptCaverns_Basement_Hide_Noble::
    removeobject LOCALID_NOBLE_ARCANINE
    end

SnowsweptB_EventScript_PsychicRaphael::
    @trainerbattle_single TRAINER_RAPHAEL_HNS, SnowsweptB_Text_PsychicRaphael_Seen, SnowsweptB_Text_PsychicRaphael_Beaten
    msgbox SnowsweptB_Text_PsychicRaphael_After, MSGBOX_AUTOCLOSE
    end


SnowsweptB_Text_PsychicRaphael_Seen:
    .string "I foresaw our encounter\n"
    .string "eons ago.\l"
    .string "You're fate is sealed.$"

SnowsweptB_Text_PsychicRaphael_Beaten:
    .string "How?!\n"
    .string "Are you able to bend fate itself?$"

SnowsweptB_Text_PsychicRaphael_After:
    .string "I can't belive my visions\n"
    .string "were wrong...$"

SnowsweptB_EventScript_SwimmerMaura::
    @trainerbattle_single TRAINER_MAURA_HNS, SnowsweptB_Text_SwimmerMaura_Seen, SnowsweptB_Text_SwimmerMaura_Beaten
    msgbox SnowsweptB_Text_SwimmerMaura_After, MSGBOX_AUTOCLOSE
    end


SnowsweptB_Text_SwimmerMaura_Seen:
    .string "Hey! Get out of the way!\n"
    .string "I'm swimin' here!$"

SnowsweptB_Text_SwimmerMaura_Beaten:
    .string "Alright, alright.\n"
    .string "I'll watch where I'm goin' geeze..$"

SnowsweptB_Text_SwimmerMaura_After:
    .string "I came all the way here from Unova\n"
    .string "to train and enjoy the local eats.$"

SnowsweptB_EventScript_SwimmerMasoto::
    @trainerbattle_single TRAINER_MASOTO_HNS, SnowsweptB_Text_SwimmerMasoto_Seen, SnowsweptB_Text_SwimmerMasoto_Beaten
    msgbox SnowsweptB_Text_SwimmerMasoto_After, MSGBOX_AUTOCLOSE
    end


SnowsweptB_Text_SwimmerMasoto_Seen:
    .string "This hotspring makes an\n"
    .string "exceptional place to train!\p"
    .string "Let's train together!$"

SnowsweptB_Text_SwimmerMasoto_Beaten:
    .string "Your teamwork is awe inspiring!\n"
    .string "Have you ever thought about\l"
    .string "becoming a couch before?$"

SnowsweptB_Text_SwimmerMasoto_After:
    .string "Make sure to take proper breaks inbetween\n"
    .string "training seasions!$"

SnowsweptB_EventScript_TriatheleteJoshua::
    faceplayer
    @trainerbattle_single TRAINER_JOSHUA2_HNS, SnowsweptB_Text_TriatheleteJoshua_Seen, SnowsweptB_Text_TriatheleteJoshua_Beaten
    msgbox SnowsweptB_Text_TriatheleteJoshua_After, MSGBOX_AUTOCLOSE
    end


SnowsweptB_Text_TriatheleteJoshua_Seen:
    .string "Yeah!\p"
    .string "Let's get pumped up!!$"

SnowsweptB_Text_TriatheleteJoshua_Beaten:
    .string "Maybe I got a little\n"
    .string "too pumped there..$"
  
SnowsweptB_Text_TriatheleteJoshua_After:
    .string "Maybe I need to drink\n"
    .string "some more nitro fuel..$"

SnowsweptB_EventScript_CamperDennis::
    @trainerbattle_single TRAINER_DENNIS2_HNS, SnowsweptB_Text_CamperDennis_Seen, SnowsweptB_Text_CamperDennis_Beaten
    msgbox SnowsweptB_Text_CamperDennis_After, MSGBOX_AUTOCLOSE
    end


SnowsweptB_Text_CamperDennis_Seen:
    .string "Yeah!\p"
    .string "Let's get pumped up!!$"

SnowsweptB_Text_CamperDennis_Beaten:
    .string "Maybe I got a little\n"
    .string "too pumped there..$"
  
SnowsweptB_Text_CamperDennis_After:
    .string "Maybe I need to drink\n"
    .string "some more nitro fuel..$"

Snowswept_EventScript_Item_SPLASHPLATE::
    finditem ITEM_SPLASH_PLATE
    addvar VAR_PLATECOUNTER, 1
    end

Snowswept_EventScript_Item_MaxRevive::
    finditem ITEM_MAX_REVIVE
    end

Snowswept_EventScript_Item_LavaCookie::
    finditem ITEM_LAVA_COOKIE
    end

SnowsweptB_EventScript_Sign::
    lock
    msgbox Snowswept_Text_TrainerTips
    release
    end

Snowswept_Text_TrainerTips:
    .string "Trainer Tips!\p"
    .string "Always fully explore\n"
    .string "your surroundings!\l"
    .string "You'll never know what\l"
    .string "you might find out there!$"

Snowswept_Caverns_Noble_Arcanine_Left::
    goto_if_set FLAG_NOBLES_UNLOCKED, Snowswept_Encounter_Noble_Arcanine_Left
    end

Snowswept_Caverns_Noble_Arcanine_Right::
    goto_if_set FLAG_NOBLES_UNLOCKED, Snowswept_Encounter_Noble_Arcanine_Right
    end

Snowswept_Encounter_Noble_Arcanine_Left::
    lock
    setvar VAR_0x8004, 1  @ vertical pan
    setvar VAR_0x8005, 1  @ horizontal pan
    setvar VAR_0x8006, 20  @ num shakes
    setvar VAR_0x8007, 6  @ shake delay
    special ShakeCamera
    waitstate
    playse SE_PIN
    applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
    playmoncry SPECIES_ARCANINE, CRY_MODE_ENCOUNTER
    delay 40
    waitmoncry
    addobject LOCALID_NOBLE_ARCANINE
    applymovement LOCALID_NOBLE_ARCANINE, Snowswept_Caverns_Arcanijne_Movement_Left
    applymovement LOCALID_PLAYER, Snowswept_Caverns_Player_Movement_Left
    waitmovement
    waitmovement
    delay 30
    setwildbossbattle species=SPECIES_ARCANINE_HISUI, level=80, item=ITEM_LOADED_DICE, move1_1=MOVE_ROCK_BLAST, move1_2=MOVE_WILD_CHARGE, move1_3=MOVE_RAGING_FURY move1_4=MOVE_PROTECT
	waitse
	playmoncry SPECIES_ARCANINE, CRY_MODE_ENCOUNTER
	msgbox Text_Grrwowl MSGBOX_DEFAULT
	waitmessage
	waitmoncry
	delay 10
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 0, 2, 0, 0, 0
	playbgm MUS_HG_VS_SUICUNE, 0
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SinjohRuins_Cave_EventScript_DefeatedArcanine
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_Cave_EventScript_RanFromArcanine
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SinjohRuins_Cave_EventScript_RanFromArcanine
	setflag FLAG_FOUGHT_NOBLE_ARCANINE
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NOBLE_ARCANINE
	fadescreen FADE_FROM_BLACK
    delay 30
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox Snowswept_Cavern_Text_FlamePlate MSGBOX_DEFAULT
	giveitem ITEM_FLAME_PLATE, 1
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NOBLECOUNTER, 1
    addvar VAR_NOBLE_ARCANINE_TRIGGER, 1
    closemessage
	release
	end

SinjohRuins_Cave_EventScript_DefeatedArcanine::
	setflag FLAG_FOUGHT_NOBLE_ARCANINE
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NOBLE_ARCANINE
	fadescreen FADE_FROM_BLACK
    delay 30
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox Snowswept_Cavern_Text_FlamePlate MSGBOX_DEFAULT
	giveitem ITEM_FLAME_PLATE, 1
    closemessage
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NOBLECOUNTER, 1
    addvar VAR_NOBLE_ARCANINE_TRIGGER, 1
	end

SinjohRuins_Cave_EventScript_RanFromArcanine::
	setvar VAR_0x8004, SPECIES_ARCANINE_HISUI
	end

Text_Grrwowl:
    .string "Grrrowh owhh!!$"

Snowswept_Cavern_Text_FlamePlate:
    .string "It seems ARCANINE left something behind..$"

Snowswept_Encounter_Noble_Arcanine_Right::
    lock
    setvar VAR_0x8004, 1  @ vertical pan
    setvar VAR_0x8005, 1  @ horizontal pan
    setvar VAR_0x8006, 20  @ num shakes
    setvar VAR_0x8007, 6  @ shake delay
    special ShakeCamera
    waitstate
    playse SE_PIN
    applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
    playmoncry SPECIES_ARCANINE, CRY_MODE_ENCOUNTER
    delay 40
    waitmoncry
    addobject LOCALID_NOBLE_ARCANINE
    applymovement LOCALID_NOBLE_ARCANINE, Snowswept_Caverns_Arcanijne_Movement_Right
    applymovement LOCALID_PLAYER, Snowswept_Caverns_Player_Movement_Right
    waitmovement
    waitmovement
    delay 30
    setwildbossbattle species=SPECIES_ARCANINE_HISUI, level=80, item=ITEM_LOADED_DICE, move1_1=MOVE_ROCK_BLAST, move1_2=MOVE_WILD_CHARGE, move1_3=MOVE_RAGING_FURY move1_4=MOVE_PROTECT
	waitse
	playmoncry SPECIES_ARCANINE, CRY_MODE_ENCOUNTER
	msgbox Text_Grrwowl MSGBOX_DEFAULT
	waitmessage
	waitmoncry
	delay 10
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 0, 2, 0, 0, 0
	playbgm MUS_HG_VS_SUICUNE, 0
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SinjohRuins_Cave_EventScript_DefeatedArcanine
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_Cave_EventScript_RanFromArcanine
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SinjohRuins_Cave_EventScript_RanFromArcanine
	setflag FLAG_FOUGHT_NOBLE_ARCANINE
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NOBLE_ARCANINE
	fadescreen FADE_FROM_BLACK
    delay 30
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox Snowswept_Cavern_Text_FlamePlate MSGBOX_DEFAULT
	giveitem ITEM_FLAME_PLATE, 1
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NOBLECOUNTER, 1
    addvar VAR_NOBLE_ARCANINE_TRIGGER, 1
    closemessage
	release
	end

Snowswept_Caverns_Arcanijne_Movement_Left::
    walk_down
    walk_down
    walk_down
    walk_down
    jump_right
    walk_right
    face_down
    step_end

Snowswept_Caverns_Arcanijne_Movement_Right::
    walk_down
    walk_down
    walk_down
    walk_down
    jump_right
    walk_right
    face_down
    step_end

Snowswept_Caverns_Player_Movement_Left::
    face_left
    face_left
    face_left
    face_left
    face_up
    step_end

Snowswept_Caverns_Player_Movement_Right::
    face_left
    face_left
    face_left
    face_left
    face_left
    face_up
    step_end