NewSinjoh_HotSprings_hns_MapScripts::
	.byte 0

NewSinjoh_HotSprings_EventScript_Item_MaxRevive::
    finditem ITEM_MAX_REVIVE
    end

NewSinjoh_HotSprings_EventScript_Item_LavaCookie::
    finditem ITEM_LAVA_COOKIE
    end

NewSinjoh_HotSprings_EventScript_Mualani::
	goto_if_defeated TRAINER_MUALANI_HNS, NewSinjoh_HotSprings_EventScript_MualaniAfter
	msgbox NewSinjoh_HotSprings_Text_MualaniBefore, MSGBOX_NPC
	goto_if_not_defeated TRAINER_MUALANI_HNS, NewSinjoh_HotSprings_EventScript_TryMualaniBattle
	end
NewSinjoh_HotSprings_EventScript_TryMualaniBattle::
	goto_if_eq VAR_SINJOH_STORYLINE, 6, NewSinjoh_HotSprings_EventScript_MualaniBattle
	end
NewSinjoh_HotSprings_EventScript_MualaniBattle::
	lock
	msgbox NewSinjoh_HotSprings_Text_MualaniBeforeBattle, MSGBOX_AUTOCLOSE
	trainerbattle_no_intro TRAINER_MUALANI_HNS, NewSinjoh_HotSprings_Text_MualaniDefeat
	giveitem ITEM_SPLASH_PLATE
	addvar VAR_PLATECOUNTER, 1
	msgbox NewSinjoh_HotSprings_Text_MualaniAfter, MSGBOX_AUTOCLOSE
	call_if_eq VAR_PLATECOUNTER, 3, SinjohRuins_Lab_EventScript_3Plates
	call_if_eq VAR_PLATECOUNTER, 6, SinjohRuins_Lab_EventScript_6Plates
	call_if_eq VAR_PLATECOUNTER, 9, SinjohRuins_Lab_EventScript_9Plates
	call_if_eq VAR_PLATECOUNTER, 12, SinjohRuins_Lab_EventScript_12Plates
	call_if_eq VAR_PLATECOUNTER, 15, SinjohRuins_Lab_EventScript_15Plates
	call_if_eq VAR_PLATECOUNTER, 16, SinjohRuins_Lab_EventScript_16Plates
	release
	end
NewSinjoh_HotSprings_EventScript_MualaniAfter::
	msgbox NewSinjoh_HotSprings_Text_MualaniAfter, MSGBOX_NPC
	end

NewSinjoh_HotSprings_Text_MualaniBefore:
	.string "Am I a local or a visitor?\n"
    .string "What a rude question!\p"
    .string "If you must know, I'm a local.\p"
    .string "My family was among the first to\n"
    .string "enjoy these springs.\p"
    .string "See, I even have this SPLASH PLATE\n"
    .string "to prove it.$"

NewSinjoh_HotSprings_Text_MualaniBeforeBattle:
	.string "Wait...\p"
	.string "You need the SPLASH PLATE\n"
	.string "to tame the legendary POKéMON?\p"
	.string "If the KIMONO GIRLS think you\n"
	.string "are worthy, then so do I.\p"
	.string "But you'll still need to earn\n"
	.string "it.$"

NewSinjoh_HotSprings_Text_MualaniDefeat:
	.string "Well earned.$"

NewSinjoh_HotSprings_Text_MualaniAfter:
	.string "It is hard for me to let that\n"
	.string "plate go.\p"
	.string "But when the situation changes,\n"
	.string "it is important for us to change\l"
	.string "too.\p"
	.string "The plate is yours.$"


NewSinjoh_HotSprings_EventScript_Sign1::
    msgbox NewSinjoh_HotSprings_Text_Sign1, MSGBOX_SIGN
    end

NewSinjoh_HotSprings_Text_Sign1:
    .string "NEW SINJOH\n"
    .string "HOT SPRINGS$"

NewSinjoh_HotSprings_EventScript_Sign2::
    msgbox NewSinjoh_HotSprings_Text_Sign2, MSGBOX_SIGN
    end

NewSinjoh_HotSprings_Text_Sign2:
    .string "DANGER\n"
    .string "WILD HIBERNATION DEN$"

NewSinjoh_HotSprings_EventScript_SkierF::
    msgbox NewSinjoh_HotSprings_Text_SkierF, MSGBOX_NPC
    end

NewSinjoh_HotSprings_Text_SkierF:
	.string "I hate the cold!\p"
    .string "I'm just here for the hot springs!$"

NewSinjoh_HotSprings_EventScript_SkierM::
    msgbox NewSinjoh_HotSprings_Text_SkierM, MSGBOX_NPC
    end

NewSinjoh_HotSprings_Text_SkierM:
	.string "I came here to snowboard\n"
    .string "but all my girlfriend wants to do\l"
    .string "is sit in the springs all day!$"


NewSinjoh_HotSprings_EventScript_OldLady::
    msgbox NewSinjoh_HotSprings_Text_OldLady, MSGBOX_NPC
    end

NewSinjoh_HotSprings_Text_OldLady:
	.string "Ignore my husband.\p"
    .string "Let your worries melt away.$"

NewSinjoh_HotSprings_EventScript_CreepyMan::
	msgbox NewSinjoh_HotSprings_Text_CreepyMan, MSGBOX_NPC
	end

NewSinjoh_HotSprings_Text_CreepyMan:
	.string "Ouughh...\p"
	.string "This water feels magical on my back.\p"
	.string "If you have back pain too,\n"
	.string "you should stay here with me...$"

NewSinjoh_HotSprings_EventScript_PLATutor::
	lock
	faceplayer
	msgbox NewSinjoh_HotSprings_Text_PLATutorIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, NewSinjoh_HotSprings_EventScript_PLATutorDecline
	message NewSinjoh_HotSprings_Text_PLATutorChoose
	waitmessage
	dynmultichoice 0, 0, FALSE, 6, 0, DYN_MULTICHOICE_CB_NONE, NewSinjoh_HotSprings_Text_PLAMove_PowerShift, NewSinjoh_HotSprings_Text_PLAMove_SpringtideStorm, NewSinjoh_HotSprings_Text_PLAMove_MysticalPower, NewSinjoh_HotSprings_Text_PLAMove_WaveCrash, NewSinjoh_HotSprings_Text_PLAMove_MountainGale, NewSinjoh_HotSprings_Text_PLAMove_VictoryDance, NewSinjoh_HotSprings_Text_PLAMove_EsperWing, NewSinjoh_HotSprings_Text_PLAMove_BitterMalice, NewSinjoh_HotSprings_Text_PLAMove_Shelter, NewSinjoh_HotSprings_Text_PLAMove_BleakwindStorm, NewSinjoh_HotSprings_Text_PLAMove_WildboltStorm, NewSinjoh_HotSprings_Text_PLAMove_SandsearStorm, NewSinjoh_HotSprings_Text_PLAMove_LunarBlessing, NewSinjoh_HotSprings_Text_PLAMove_TakeHeart, NewSinjoh_HotSprings_Text_PLAMove_Cancel
	switch VAR_RESULT
	case 0, NewSinjoh_HotSprings_EventScript_PLATeach_PowerShift
	case 1, NewSinjoh_HotSprings_EventScript_PLATeach_SpringtideStorm
	case 2, NewSinjoh_HotSprings_EventScript_PLATeach_MysticalPower
	case 3, NewSinjoh_HotSprings_EventScript_PLATeach_WaveCrash
	case 4, NewSinjoh_HotSprings_EventScript_PLATeach_MountainGale
	case 5, NewSinjoh_HotSprings_EventScript_PLATeach_VictoryDance
	case 6, NewSinjoh_HotSprings_EventScript_PLATeach_EsperWing
	case 7, NewSinjoh_HotSprings_EventScript_PLATeach_BitterMalice
	case 8, NewSinjoh_HotSprings_EventScript_PLATeach_Shelter
	case 9, NewSinjoh_HotSprings_EventScript_PLATeach_BleakwindStorm
	case 10, NewSinjoh_HotSprings_EventScript_PLATeach_WildboltStorm
	case 11, NewSinjoh_HotSprings_EventScript_PLATeach_SandsearStorm
	case 12, NewSinjoh_HotSprings_EventScript_PLATeach_LunarBlessing
	case 13, NewSinjoh_HotSprings_EventScript_PLATeach_TakeHeart
	case 14, NewSinjoh_HotSprings_EventScript_PLATutorDecline
	case MULTI_B_PRESSED, NewSinjoh_HotSprings_EventScript_PLATutorDecline
	end

NewSinjoh_HotSprings_EventScript_PLATeach_PowerShift::
	setvar VAR_0x8005, MOVE_POWER_SHIFT
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_SpringtideStorm::
	setvar VAR_0x8005, MOVE_SPRINGTIDE_STORM
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_MysticalPower::
	setvar VAR_0x8005, MOVE_MYSTICAL_POWER
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_WaveCrash::
	setvar VAR_0x8005, MOVE_WAVE_CRASH
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_MountainGale::
	setvar VAR_0x8005, MOVE_MOUNTAIN_GALE
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_VictoryDance::
	setvar VAR_0x8005, MOVE_VICTORY_DANCE
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_EsperWing::
	setvar VAR_0x8005, MOVE_ESPER_WING
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_BitterMalice::
	setvar VAR_0x8005, MOVE_BITTER_MALICE
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_Shelter::
	setvar VAR_0x8005, MOVE_SHELTER
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_BleakwindStorm::
	setvar VAR_0x8005, MOVE_BLEAKWIND_STORM
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_WildboltStorm::
	setvar VAR_0x8005, MOVE_WILDBOLT_STORM
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_SandsearStorm::
	setvar VAR_0x8005, MOVE_SANDSEAR_STORM
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_LunarBlessing::
	setvar VAR_0x8005, MOVE_LUNAR_BLESSING
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeach_TakeHeart::
	setvar VAR_0x8005, MOVE_TAKE_HEART
	goto NewSinjoh_HotSprings_EventScript_PLATeachMove
	end

NewSinjoh_HotSprings_EventScript_PLATeachMove::
	buffermovename STR_VAR_1, VAR_0x8005
	msgbox NewSinjoh_HotSprings_Text_PLATutorConfirm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, NewSinjoh_HotSprings_EventScript_PLATutor
	msgbox NewSinjoh_HotSprings_Text_PLATutorWhichMon, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	chooseboxmon SELECT_PC_MON_PLA_TUTOR
	waitstate
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_HotSprings_EventScript_PLATutorCancelMon
	msgbox NewSinjoh_HotSprings_Text_PLATutorDone, MSGBOX_DEFAULT
	release
	end

NewSinjoh_HotSprings_EventScript_PLATutorCancelMon::
	msgbox NewSinjoh_HotSprings_Text_PLATutorComeBack, MSGBOX_DEFAULT
	release
	end

NewSinjoh_HotSprings_EventScript_PLATutorDecline::
	msgbox NewSinjoh_HotSprings_Text_PLATutorComeBack, MSGBOX_DEFAULT
	release
	end

NewSinjoh_HotSprings_Text_PLATutorIntro:
	.string "The ancient power flows\n"
	.string "through these springs.\p"
	.string "I can teach your POKeMON moves\n"
	.string "from a forgotten age.\p"
	.string "Interested?$"

NewSinjoh_HotSprings_Text_PLATutorChoose:
	.string "Which move would you like?$"

NewSinjoh_HotSprings_Text_PLATutorConfirm:
	.string "You'd like to learn {STR_VAR_1}?$"

NewSinjoh_HotSprings_Text_PLATutorWhichMon:
	.string "Which POKeMON should learn it?$"

NewSinjoh_HotSprings_Text_PLATutorDone:
	.string "Done! Your POKeMON has mastered\n"
	.string "the ancient technique.$"

NewSinjoh_HotSprings_Text_PLATutorComeBack:
	.string "Come back anytime.$"

NewSinjoh_HotSprings_Text_PLAMove_VictoryDance:
	.string "VICTORY DANCE$"

NewSinjoh_HotSprings_Text_PLAMove_MountainGale:
	.string "MOUNTAIN GALE$"

NewSinjoh_HotSprings_Text_PLAMove_BitterMalice:
	.string "BITTER MALICE$"

NewSinjoh_HotSprings_Text_PLAMove_SpringtideStorm:
	.string "SPRINGTIDE STORM$"

NewSinjoh_HotSprings_Text_PLAMove_LunarBlessing:
	.string "LUNAR BLESSING$"

NewSinjoh_HotSprings_Text_PLAMove_BleakwindStorm:
	.string "BLEAKWIND STORM$"

NewSinjoh_HotSprings_Text_PLAMove_WildboltStorm:
	.string "WILDBOLT STORM$"

NewSinjoh_HotSprings_Text_PLAMove_SandsearStorm:
	.string "SANDSEAR STORM$"

NewSinjoh_HotSprings_Text_PLAMove_Shelter:
	.string "SHELTER$"

NewSinjoh_HotSprings_Text_PLAMove_EsperWing:
	.string "ESPER WING$"

NewSinjoh_HotSprings_Text_PLAMove_TakeHeart:
	.string "TAKE HEART$"

NewSinjoh_HotSprings_Text_PLAMove_MysticalPower:
	.string "MYSTICAL POWER$"

NewSinjoh_HotSprings_Text_PLAMove_WaveCrash:
	.string "WAVE CRASH$"

NewSinjoh_HotSprings_Text_PLAMove_PowerShift:
	.string "POWER SHIFT$"

NewSinjoh_HotSprings_Text_PLAMove_Cancel:
	.string "CANCEL$"


NewSinjoh_HotSprings_EventScript_ActivateArcanine::
    lock
    setobjectxyperm LOCALID_HOTSPRINGS_NOBLE_ARCANINE, 16, 4
    playse SE_M_DETECT
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	dofieldeffectsparkle VAR_TEMP_1, VAR_TEMP_2, 0
	waitfieldeffect FLDEFF_SPARKLE
    playse SE_PIN
    applymovement2 LOCALID_PLAYER, Common_Movement_ExclamationMark
    delay 60
    msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
    goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
    playbgm MUS_DP_AZURE_FLUTE, FALSE
    delay 200
    fadedefaultbgm
    addobject LOCALID_HOTSPRINGS_NOBLE_ARCANINE
    clearflag FLAG_HIDE_HOTSPRINGS_NOBLE_ARCANINE
    applymovement2 LOCALID_HOTSPRINGS_NOBLE_ARCANINE, NewSinjoh_HotSprings_Movement_ArcanineEntrance1
    delay 10
	playse SE_LEDGE
    playmoncry SPECIES_ARCANINE_HISUI, CRY_MODE_NORMAL
    waitmoncry
    waitmovement 0
    applymovement2 LOCALID_HOTSPRINGS_NOBLE_ARCANINE, NewSinjoh_HotSprings_Movement_ArcanineEntrance2
    delay 10
	playmoncry SPECIES_ARCANINE_HISUI, CRY_MODE_NORMAL
    waitmoncry
    playse SE_LEDGE
    delay 20
	waitmovement LOCALID_HOTSPRINGS_NOBLE_ARCANINE
    setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 5  @ num shakes
	setvar VAR_0x8007, 2  @ shake delay
	special ShakeCamera
    setobjectxyperm LOCALID_HOTSPRINGS_NOBLE_ARCANINE, 16, 8
    setvar VAR_NOBLE_ARCANINE, 2
    release
    end

NewSinjoh_HotSprings_Movement_ArcanineEntrance1:
    slide_down
	slide_down
	slide_down
	slide_down
	step_end

NewSinjoh_HotSprings_Movement_ArcanineEntrance2:
    walk_in_place_slow_down
	walk_in_place_slow_down
	jump_in_place_down
	step_end


NewSinjoh_HotSprings_EventScript_Arcanine::
	lock
	faceplayer
	playmoncry SPECIES_ARCANINE_HISUI, CRY_MODE_ENCOUNTER
	waitmoncry
    setwildbossbattle species=SPECIES_ARCANINE_HISUI, level=80, item=ITEM_LOADED_DICE, move1_1=MOVE_ROCK_BLAST, move1_2=MOVE_WILD_CHARGE, move1_3=MOVE_RAGING_FURY move1_4=MOVE_PROTECT
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 0, 2, 0, 0, 0
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	setflag FLAG_NO_SHINY
    dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NewSinjoh_HotSprings_EventScript_ArcanineRan
    bufferspeciesname STR_VAR_1, SPECIES_ARCANINE_HISUI
    msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
    giveitem ITEM_FLAME_PLATE
    addvar VAR_PLATECOUNTER, 1
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_HOTSPRINGS_NOBLE_ARCANINE
	setflag FLAG_HIDE_HOTSPRINGS_NOBLE_ARCANINE
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

NewSinjoh_HotSprings_EventScript_ArcanineRan::
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag FLAG_NO_SHINY
	release
	end






NewSinjoh_HotSprings_EventScript_ActivateUrsaluna::
    lock
    setobjectxyperm LOCALID_HOTSPRINGS_NOBLE_URSALUNA, 52, 26
    playse SE_M_DETECT
	getplayerxy VAR_TEMP_1, VAR_TEMP_2
	dofieldeffectsparkle VAR_TEMP_1, VAR_TEMP_2, 0
	waitfieldeffect FLDEFF_SPARKLE
    playse SE_PIN
    applymovement2 LOCALID_PLAYER, Common_Movement_ExclamationMark
    delay 60
    msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
    goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp
    playbgm MUS_DP_AZURE_FLUTE, FALSE
    delay 200
    fadedefaultbgm
    addobject LOCALID_HOTSPRINGS_NOBLE_URSALUNA
    clearflag FLAG_HIDE_HOTSPRINGS_NOBLE_URSALUNA
    applymovement2 LOCALID_HOTSPRINGS_NOBLE_URSALUNA, NewSinjoh_HotSprings_Movement_UrsalunaEntrance1
    delay 10
	playse SE_LEDGE
    playmoncry SPECIES_URSALUNA, CRY_MODE_NORMAL
    waitmoncry
    waitmovement 0
    applymovement2 LOCALID_HOTSPRINGS_NOBLE_URSALUNA, NewSinjoh_HotSprings_Movement_UrsalunaEntrance2
    delay 10
	playmoncry SPECIES_URSALUNA, CRY_MODE_NORMAL
    waitmoncry
    playse SE_LEDGE
    delay 20
	waitmovement LOCALID_HOTSPRINGS_NOBLE_URSALUNA
    setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 5  @ num shakes
	setvar VAR_0x8007, 2  @ shake delay
	special ShakeCamera
    setobjectxyperm LOCALID_HOTSPRINGS_NOBLE_URSALUNA, 52, 28
    setvar VAR_NOBLE_URSALUNA, 2
    release
    end

NewSinjoh_HotSprings_Movement_UrsalunaEntrance1:
    jump_in_place_down
    walk_in_place_fast_down
    walk_in_place_fast_down
	step_end

NewSinjoh_HotSprings_Movement_UrsalunaEntrance2:
	jump_2_down
    walk_in_place_slow_down
	walk_in_place_slow_down
	jump_in_place_down
	step_end


NewSinjoh_HotSprings_EventScript_Ursaluna::
	lock
	faceplayer
	playmoncry SPECIES_URSALUNA, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbossbattle species=SPECIES_URSALUNA, level=80, item=ITEM_EARTH_PLATE, move1_1=MOVE_EARTHQUAKE, move1_2=MOVE_AVALANCHE, move1_3=MOVE_BULK_UP move1_4=MOVE_GIGA_IMPACT
	settotemboost B_POSITION_OPPONENT_LEFT, 1, 0, 2, 0, 0, 0
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	setflag FLAG_NO_SHINY
    dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NewSinjoh_HotSprings_EventScript_UrsalunaRan
    bufferspeciesname STR_VAR_1, SPECIES_URSALUNA
    msgbox SinjohRuins_Lab_Text_DropedItem, MSGBOX_DEFAULT
    giveitem ITEM_EARTH_PLATE
    addvar VAR_PLATECOUNTER, 1
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_HOTSPRINGS_NOBLE_URSALUNA
	setflag FLAG_HIDE_HOTSPRINGS_NOBLE_URSALUNA
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

NewSinjoh_HotSprings_EventScript_UrsalunaRan::
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag FLAG_NO_SHINY
	release
	end
