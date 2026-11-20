SinjohRuins_ArceusRoom_hns_MapScripts::
	map_script 	MAP_SCRIPT_ON_TRANSITION, SinjohRuins_ArceusRoom_OnTransition
	.byte 0

SinjohRuins_ArceusRoom_OnTransition::
	call_if_ge VAR_SINJOH_STORYLINE, 11, SinjohRuins_ArceusRoom_MoveArceus
	end
	
SinjohRuins_ArceusRoom_MoveArceus::
	setobjectxyperm LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS, 18, 18
	return


SinjohRuins_ArceusRoom_TriggerRight::
	lock
	playse SE_M_DETECT
	dofieldeffectsparkle 19, 24, 0
	waitfieldeffect FLDEFF_SPARKLE
	goto SinjohRuins_ArceusRoom_TriggerScene
SinjohRuins_ArceusRoom_TriggerLeft::
	lock
	playse SE_M_DETECT
	dofieldeffectsparkle 17, 24, 0
	waitfieldeffect FLDEFF_SPARKLE
	goto SinjohRuins_ArceusRoom_TriggerScene
SinjohRuins_ArceusRoom_TriggerMid::
	lock
	playse SE_M_DETECT
	dofieldeffectsparkle 18, 24, 0
	waitfieldeffect FLDEFF_SPARKLE
	goto SinjohRuins_ArceusRoom_TriggerScene
SinjohRuins_ArceusRoom_TriggerScene::

	playse SE_PIN
    applymovement2 LOCALID_PLAYER, Common_Movement_ExclamationMark
    delay 55
    waitmovement LOCALID_PLAYER
    msgbox SinjohRuins_Lab_Text_PlayFlute, MSGBOX_YESNO
	closemessage
    goto_if_eq VAR_RESULT, FALSE, SinjohRuins_Lab_EventScript_NoOp

	playbgm MUS_DP_AZURE_FLUTE, FALSE
	applymovement2 LOCALID_PLAYER, SinjohRuins_ArceusRoom_Movement_WalkSlowUp
	waitmovement 0
	setvar VAR_RESULT, 3
	playse SE_ORB
	special DoOrbEffect

	delay 200
	applymovement2 LOCALID_PLAYER, SinjohRuins_ArceusRoom_Movement_Dance
	applymovement2 OBJ_EVENT_ID_FOLLOWER, SinjohRuins_ArceusRoom_Movement_Dance
	delay 400
	waitmovement 0
	waitmovement OBJ_EVENT_ID_FOLLOWER
	special FadeOutOrbEffect

	setweather WEATHER_SUNNY
	doweather
    playse SE_THUNDER
	delay 80
	setvar VAR_0x8004, 1  @ vertical pan
    setvar VAR_0x8005, 1  @ horizontal pan
    setvar VAR_0x8006, 15  @ num shakes
    setvar VAR_0x8007, 6  @ shake delay
    special ShakeCamera
    waitstate
	delay 80
	playse SE_THUNDER
	fadescreen FADE_TO_WHITE
	addobject LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS
	clearflag FLAG_HIDE_SINJOHRUINS_ARCEUSROOM_ARCEUS

	playse SE_THUNDER
	applymovement2 LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS, SinjohRuins_ArceusRoom_Movement_ArceusWalkDown
	playfanfare MUS_AWAKEN_LEGEND
	fadescreen FADE_FROM_WHITE
    playmoncry SPECIES_ARCEUS, 0
	delay 20
	waitmovement LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS
	setvar VAR_0x8004, 0  @ vertical pan
    setvar VAR_0x8005, 1  @ horizontal pan
    setvar VAR_0x8006, 6  @ num shakes
    setvar VAR_0x8007, 2  @ shake delay
    special ShakeCamera
    waitstate
	waitmoncry
	delay 8
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_PLAYER
	setweather WEATHER_NONE
	doweather
	applymovement2 LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS, SinjohRuins_ArceusRoom_Movement_ArceusLooksAround
	playmoncry SPECIES_ARCEUS, 0
	waitmovement 0
	playmoncry SPECIES_ARCEUS, 0
	waitmoncry
	fadedefaultbgm
	setobjectxyperm LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS, 18, 18
	setvar VAR_SINJOH_STORYLINE, 11
	release
	end

SinjohRuins_ArceusRoom_Movement_ArceusLooksAround:
	walk_in_place_down
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_left
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_right
	delay_16
	delay_16
	delay_16
	delay_16
	walk_in_place_down
	walk_in_place_fast_down
	step_end

SinjohRuins_ArceusRoom_Movement_Dance:
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_up
	step_end

SinjohRuins_ArceusRoom_Movement_ArceusWalkDown:
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	slide_down
	step_end

SinjohRuins_ArceusRoom_Movement_WalkSlowUp:
	walk_slow_up
	walk_slow_up
	walk_slow_up
	walk_slow_up
	step_end


SinjohRuins_ArceusRoom_EventScript_Arceus::
	lock
	faceplayer
	goto_if_ge VAR_SINJOH_STORYLINE, 12, SinjohRuins_ArceusRoom_EventScript_ArceusPhase2
	playmoncry SPECIES_ARCEUS, CRY_MODE_ENCOUNTER
	msgbox SinjohRuins_ArceusRoom_Text_CryArceus, MSGBOX_AUTOCLOSE
	delay 40
	waitmoncry
	setflag FLAG_NO_WILD_CATCHING
	setflag FLAG_NO_WILD_RUNNING
	setflag FLAG_SMART_WILD_AI
	setflag FLAG_NO_SHINY
	setwildbossbattle species=SPECIES_ARCEUS_STEEL, level=100, item=ITEM_IRON_PLATE, move1_1=MOVE_JUDGMENT, move1_2=MOVE_HYDRO_PUMP, move1_3=MOVE_RECOVER move1_4=MOVE_DAZZLING_GLEAM
	settotemboost B_POSITION_OPPONENT_LEFT, 2, 2, 0, 2, 2, 2
	special BattleSetup_StartLegendaryBattle
	playbgm MUS_HG_VS_ARCEUS, 0
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_ArceusRoom_EventScript_ArceusRan
	setvar VAR_SINJOH_STORYLINE, 12
	clearflag FLAG_NO_WILD_CATCHING
	clearflag FLAG_NO_WILD_RUNNING
	clearflag FLAG_SMART_WILD_AI
	clearflag FLAG_NO_SHINY
SinjohRuins_ArceusRoom_EventScript_ArceusPhase2::
	playmoncry SPECIES_ARCEUS, CRY_MODE_ENCOUNTER
	msgbox SinjohRuins_ArceusRoom_Text_CryArceus2, MSGBOX_AUTOCLOSE
	delay 40
	waitmoncry
	setwildbossbattle species=SPECIES_ARCEUS, level=80, item=ITEM_NONE, move1_1=MOVE_EXTREME_SPEED, move1_2=MOVE_EARTH_POWER, move1_3=MOVE_RECOVER move1_4=MOVE_HYPER_BEAM
	@settotemboost B_POSITION_OPPONENT_LEFT, 1, 0, 2, 0, 0, 0
	special BattleSetup_StartLegendaryBattle
	playbgm MUS_HG_VS_ARCEUS, 0
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_ArceusRoom_EventScript_ArceusRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_SINJOHRUINS_ARCEUSROOM_ARCEUS
	setflag FLAG_HIDE_SINJOHRUINS_ARCEUSROOM_ARCEUS
	special GivePartyMonSkyRibbon
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

SinjohRuins_ArceusRoom_EventScript_ArceusRan::
	release
	end

SinjohRuins_ArceusRoom_Text_CryArceus:
    .string "ארקיאוס: דודוגיווון!$"

SinjohRuins_ArceusRoom_Text_CryArceus2:
	.string "ארקיאוס: דודוגיווון!\p"
	.string "ארקיאוס נחלש…\n"
	.string "אפשר לתפוס אותו?$"

SinjohRuins_ArceusRoom_TriggerSteven::
	lock
	addobject LOCALID_SINJOHRUINS_ARCEUSROOM_STEVEN
	applymovement2 LOCALID_SINJOHRUINS_ARCEUSROOM_STEVEN, SinjohRuins_ArceusRoom_Movement_StevenWalkUp
	waitmovement 0
	msgbox SinjohRuins_ArceusRoom_Text_StevenCongrats, MSGBOX_AUTOCLOSE
	applymovement2 LOCALID_SINJOHRUINS_ARCEUSROOM_STEVEN, SinjohRuins_ArceusRoom_Movement_StevenWalkDown
	waitmovement 0
	removeobject LOCALID_SINJOHRUINS_ARCEUSROOM_STEVEN
	playse SE_EXIT
	setflag FLAG_HIDE_SINJOHRUINS_STEVEN
	clearflag FLAG_HIDE_NEWSINJOH_STEVEN
	setvar VAR_SINJOH_STORYLINE, 13	
	release
	end

SinjohRuins_ArceusRoom_Movement_StevenWalkUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SinjohRuins_ArceusRoom_Movement_StevenWalkDown:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_in_place_down
	step_end

SinjohRuins_ArceusRoom_Text_StevenCongrats:
    .string "סטיבן: הצלחת, {PLAYER}!\p"
    .string "הקרב הזה היה עוצר נשימה.\p"
    .string "כשראיתי את הכוח שלך, הבנתי.\p"
    .string "נערות הקימונו לא שלחו אותך\n"
    .string "כדי לעזור למחקר שלנו.\p"
    .string "אני חושב שהן שלחו אותך כי רק אתה\n"
    .string "היית ראוי לאלף את הפוקימון האגדי.\p"
    .string "הן לא סמכו עליי ועל הצוות שלי\n"
    .string "שנתמודד עם זה.\p"
    .string "ואחרי מה שראיתי עכשיו…\p"
    .string "אני חושב שהן צדקו.\p"
    .string "משכתי לעיירה הזאת\n"
    .string "הרבה תשומת לב לא רצויה.\p"
    .string "אני חושב שאבלה קצת זמן עם המקומיים.\p"
    .string "אחרי כל זה, מגיעה לך\n"
    .string "ולפוקימונים שלך קצת מנוחה.\p"
    .string "אהיה בכפר אם תצטרך אותי.\p"
    .string "פופופו, מה כבר תצטרך ממני?$"
