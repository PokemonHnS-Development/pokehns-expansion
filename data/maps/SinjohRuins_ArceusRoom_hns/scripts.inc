SinjohRuins_ArceusRoom_hns_MapScripts::
    map_script MAP_SCRIPT_ON_FRAME_TABLE, SinjohRuins_ArceusRoom_OnFrame
	map_script MAP_SCRIPT_ON_TRANSITION, SinjohRuins_ArceusRoom_OnTransition
	.byte 0

SinjohRuins_ArceusRoom_OnTransition::
    setflag FLAG_SINJOHRUINS_ARCEUS
    end

SinjohRuins_ArceusRoom_OnFrame::
    map_script_2 VAR_STEVENSTONE_PART1, 0, SinjohRuins_ArceusRoom_EventScript_StevenStone_PreFight
	.2byte 0

SinjohRuins_ArceusRoom_EventScript_StevenStone_PreFight::
    lock
	removeobject LOCALID_ARCEUS
	msgbox StevenTalksAboutTheRoom_Text MSGBOX_AUTOCLOSE
	applymovement LOCALID_STEVENSTONEBATTLE, StevenWalksUpLedge_Movement
	applymovement LOCALID_PLAYER, PLayerFollowsSteven_Movement
	waitmovement 0
	waitmovement 0
	delay 10
	msgbox StevenGets_Serious_Text MSGBOX_DEFAULT
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox StevenChallengesPlayer_Text MSGBOX_DEFAULT
    setflag FLAG_SINJOHRUINS_STEVENSTONE_PART2
	trainerbattle_no_intro TRAINER_STEVENSTONE_HNS, SinjohRuins_ArceusRoom_Steven_Beaten
	playbgm MUS_VS_CHAMPION, 0
    goto SinjohRuins_ArceusRoom_Steven_AfterBattle


SinjohRuins_Arceus_EventScript_BattleStevenStone::
    lock
	faceplayer
	goto_if_set FLAG_SINJOHRUINS_ARCEUS_APPEARS, SinjohRuins_EventScript_StevenWishesPlayerLuck
	goto_if_set FLAG_SINJOHRUINS_STEVENSTONE_PART2, SinjohRuins_EventScript_StevenBeforeArceus
	release
	end


SinjohRuins_ArceusRoom_Steven_AfterBattle::
    fadedefaultbgm
    addvar VAR_STEVENSTONE_PART1, 1
    msgbox SinjohRuins_StevenGivesIronPlate_Text MSGBOX_DEFAULT
	delay 8
    giveitem ITEM_IRON_PLATE, 1
	compare VAR_RESULT, 0
	goto_if_eq SinjohRuins_EventScript_BagIsFull
	addvar VAR_PLATECOUNTER, 1
	msgbox SinjohRuins_Arceus_StevenAndPlayer_Text MSGBOX_DEFAULT
	goto SinjohRuins_EventScript_StevenBeforeArceus


SinjohRuins_EventScript_StevenBeforeArceus::
    msgbox SinjohRuins_StevenAsksAboutFlute MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_EventScript_StevenWaits
	msgbox StevenTellsYouTooGoAhead_Text MSGBOX_AUTOCLOSE
	applymovement LOCALID_STEVENSTONEBATTLE, StevenStepsAside_Movement
	setobjectxyperm LOCALID_STEVENSTONEBATTLE, 16, 22
	applymovement LOCALID_PLAYER, PlayerWalksUPAndPlaysFlute_MOvement
	waitmovement 0
	waitmovement 0
	playse SE_M_DETECT
	dofieldeffectsparkle 18, 21, 0
	waitfieldeffect FLDEFF_SPARKLE
	msgbox PlayerPulledOutTheAzureFlute_Text MSGBOX_AUTOCLOSE
	delay 8
    playse SE_THUNDER
	delay 40
	setvar VAR_0x8004, 1  @ vertical pan
    setvar VAR_0x8005, 1  @ horizontal pan
    setvar VAR_0x8006, 15  @ num shakes
    setvar VAR_0x8007, 6  @ shake delay
    special ShakeCamera
    waitstate
	delay 60
	playse SE_THUNDER
	fadescreen FADE_TO_WHITE
	addobject LOCALID_ARCEUS
	playse SE_THUNDER
	fadescreen FADE_FROM_WHITE
    playmoncry SPECIES_ARCEUS, 0
	delay 20
	msgbox SinjohRuins_Text_CryArceus, MSGBOX_DEFAULT
	setvar VAR_0x8004, 0  @ vertical pan
    setvar VAR_0x8005, 1  @ horizontal pan
    setvar VAR_0x8006, 6  @ num shakes
    setvar VAR_0x8007, 2  @ shake delay
    special ShakeCamera
    waitstate
	waitmoncry
	delay 8
	playse SE_PIN
	applymovement LOCALID_STEVENSTONEBATTLE, Common_Movement_ExclamationMark
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
    waitmovement 0
	setflag FLAG_SINJOHRUINS_ARCEUS_APPEARS
    release
	end


SinjohRuins_EventScript_StevenWishesPlayerLuck::
    msgbox StevenWishesPlayerGoodLuck_Text
    release
    end

SinjohRuins_EventScript_StevenWaits::
    msgbox SinjohRuins_TakeYourTime_Text MSGBOX_DEFAULT
	release 
	end

SinjohRuins_EventScript_Arceus::
    lock
	faceplayer
	setwildbossbattle species=SPECIES_ARCEUS_STEEL, level=100, item=ITEM_IRON_PLATE, move1_1=MOVE_JUDGMENT, move1_2=MOVE_HYDRO_PUMP, move1_3=MOVE_RECOVER move1_4=MOVE_DAZZLING_GLEAM
	waitse
	playmoncry SPECIES_ARCEUS, CRY_MODE_ENCOUNTER
	msgbox SinjohRuins_Text_CryArceus MSGBOX_DEFAULT
	waitmessage
	waitmoncry
	msgbox SinjohRuins_WarningArceus_Text MSGBOX_DEFAULT
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	settotemboost B_POSITION_OPPONENT_LEFT, 2, 2, 2, 2, 2, 0, 0
	playbgm MUS_HG_VS_ARCEUS, 0
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SinjohRuins_EventScript_DefeatedArceus
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_EventScript_RanFromArceus
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SinjohRuins_EventScript_RanFromArceus
	fadedefaultbgm
	release
	end

SinjohRuins_EventScript_DefeatedArceus::
    fadedefaultbgm
    playbgm MUS_HG_RADIO_UNOWN, 0
    msgbox SinjohRuins_ShowEmYouPower_Text MSGBOX_AUTOCLOSE
	setwildbossbattle species=SPECIES_ARCEUS, level=80, item=ITEM_NONE, move1_1=MOVE_EXTREME_SPEED, move1_2=MOVE_EARTH_POWER, move1_3=MOVE_RECOVER move1_4=MOVE_HYPER_BEAM
	waitse
	playmoncry SPECIES_ARCEUS, CRY_MODE_ENCOUNTER
	msgbox SinjohRuins_Text_CryArceus MSGBOX_DEFAULT
	waitmessage
	waitmoncry
	waitbuttonpress
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	playbgm MUS_HG_VS_ARCEUS, 0
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SinjohRuins_EventScript_DefeatedArceus2
	end

SinjohRuins_EventScript_RanFromArceus::
	setvar VAR_0x8004, SPECIES_ARCEUS_STEEL
	end

SinjohRuins_EventScript_DefeatedArceus2::
    setflag FLAG_SINJOHRUINS_ARCEUS_DEFEATED
	addvar VAR_SNOWSWEPT_FINALBRIDGE, 1
    fadedefaultbgm
    fadescreen FADE_TO_BLACK
	removeobject LOCALID_ARCEUS
	fadescreen FADE_FROM_BLACK
	applymovement LOCALID_STEVENSTONEBATTLE, SinjohRuins_StevenCongratsPlayer_Movement
	applymovement LOCALID_PLAYER, PlayerFacesSteven_Movement
	waitmovement 0
	waitmovement 0
	special SpawnCameraObject
	msgbox SinjohRuins_StevenCongratsPlayer_Text MSGBOX_DEFAULT
	applymovement LOCALID_STEVENSTONEBATTLE, SinjohRuins_StevenLeaves_Movement
	applymovement LOCALID_PLAYER, SinjohRuins_PlayerLeaves_Movement
	waitmovement 0
    waitmovement 0
	setrespawn HEAL_LOCATION_NEW_BARK_TOWN_HNS
	fadescreenspeed FADE_TO_BLACK, 24
	special GameClear
	waitstate
	releaseall
	end

StevenTalksAboutTheRoom_Text:
    .string "This has been quite the adventure\n"
	.string "hasn't it {PLAYER}?\p"
	.string "What we are about to face up ahead\n"
	.string "is something much powerful than\l"
	.string "anything you've ever faced.\p"
	.string "If my research is correct,\n"
	.string "we will be facing the most powerful\l"
	.string "POKEMON in the universe...$"

StevenWalksUpLedge_Movement:
    walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
    face_down
	step_end


PLayerFollowsSteven_Movement:
    walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

StevenGets_Serious_Text:
    .string "That is why {PLAYER}....\p"
    .string "Why you must understand...$"

StevenChallengesPlayer_Text:
    .string "Why it is my duty as the\n"
	.string "POKEMON League chamption of Hoenn\l"
	.string "to make sure you're strong enough!\p"
	.string "Now, show me everything you've learned!$"

SinjohRuins_ArceusRoom_Steven_Beaten:
    .string "You've bested me {PLAYER}!\p"
	.string "You truely are a wonderful trainer!$"

StevenChallengesPlayer_Text2: 
    .string "Are you ready to try again?\p"
	.string "I hope you know I'll never hold back!$"

SinjohRuins_StevenGivesIronPlate_Text:
    .string "The bonds you have formed with\n"
	.string "your POKEMON, they remind me of a\l"
	.string "trainer I met 3 years ago.\p"
	.string "To think another trainer would\n"
	.string "defeat me like this!\p"
	.string "Take this, it's the final plate you\n"
	.string "need to awaken the full potentail\l"
	.string "of the Azure Flute.$"

SinjohRuins_Arceus_StevenAndPlayer_Text:
    .string "{PLAYER}, what happens here today\n"
	.string "will change histroy for all of Johto,\l"
	.string "no... for the entire world! I'm sure of it!$"


SinjohRuins_StevenAsksAboutFlute:
    .string "That is why I must ask this of you first.\p"
	.string "Are you ready to face what lies up ahead?$"

SinjohRuins_TakeYourTime_Text:
    .string "Alright... head back down and\n"
	.string "get some rest.\p"
	.string "I will remain\n"
	.string "here and wait for you.$"

StevenTellsYouTooGoAhead_Text:
    .string "I believe in you {PLAYER},\n"
	.string "with your POKEMON, you'll be able to\l"
	.string "overcome all odds! I know it!$"

StevenStepsAside_Movement:
    walk_left
	walk_left
	face_up
	step_end

PlayerWalksUPAndPlaysFlute_MOvement:
    walk_up
	walk_up
	step_end

PlayerPulledOutTheAzureFlute_Text:
    .string "You began to play the Azure FLute\n"
	.string "one final time.$"

SinjohRuins_Text_CryArceus:
    .string "Dodogyuuun!$"

SinjohRuins_Steven_ItsArceus_Text:
    .string "I can't believe it...\n"
	.string "it really is ACREUS!$"

StevenWishesPlayerGoodLuck_Text:
    .string "Good luck {PLAYER}, I believe in you!$"

SinjohRuins_WarningArceus_Text:
    .string "ARCEUS unleashed it's full power!$"

SinjohRuins_ShowEmYouPower_Text:
    .string "Now's your chance!\n"
	.string "Show ARCEUS your power!$"

SinjohRuins_StevenCongratsPlayer_Movement:
    walk_up
	walk_up
    walk_right
	step_end

PlayerFacesSteven_Movement:
    face_left
	step_end

SinjohRuins_StevenCongratsPlayer_Text:
    .string "You did it {PLAYER}!\p"
	.string "That battle was breathtaking,\n"
	.string "I knew from the moment we met\l"
	.string "that your sparkle would outshine\l"
	.string "my expectations!\p"
	.string "I think after all of this, you\n"
	.string "and your POKEMON deserve some rest.\l"
	.string "Come now, it's time to return.$"

SinjohRuins_StevenLeaves_Movement:
    walk_down
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

SinjohRuins_PlayerLeaves_Movement:
    delay_8
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

SinjohRuins_EventScript_BagIsFull:
    msgbox PleaseMakeRoom_Text MSGBOX_DEFAULT
	release
	end

PleaseMakeRoom_Text:
    .string "Ah! Your BAG seems to be full.\p"
	.string "Please make some space so\n"
	.string "I can give this to you.$"

