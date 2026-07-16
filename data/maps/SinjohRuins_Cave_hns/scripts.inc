SinjohRuins_Cave_hns_MapScripts::
	.byte 0

SinjohRuins_Cave_EventScript_Ursaluna::
	lock
	faceplayer
	setwildbossbattle species=SPECIES_URSALUNA, level=80, item=ITEM_EARTH_PLATE, move1_1=MOVE_EARTHQUAKE, move1_2=MOVE_AVALANCHE, move1_3=MOVE_BULK_UP move1_4=MOVE_GIGA_IMPACT
	waitse
	playmoncry SPECIES_URSALUNA, CRY_MODE_ENCOUNTER
	msgbox SinjohRuins_Cave_Text_Grrwowl MSGBOX_DEFAULT
	waitmessage
	waitmoncry
	delay 10
	waitbuttonpress
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	settotemboost B_POSITION_OPPONENT_LEFT, 0, 0, 0, 0, 2, 0, 0
	playbgm MUS_HG_VS_SUICUNE, 0
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SinjohRuins_Cave_EventScript_DefeatedUrsaluna
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SinjohRuins_Cave_EventScript_RanFromUrsaluna
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SinjohRuins_Cave_EventScript_RanFromUrsaluna
	setflag FLAG_FOUGHT_NOBLE_URSALUNA
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NOBLE_URSALUNA
	fadescreen FADE_FROM_BLACK
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox SinjohRuins_Cave_Text_EarthPlate
	giveitem ITEM_EARTH_PLATE, 1
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NOBLECOUNTER, 1
	release
	end

SinjohRuins_Cave_EventScript_DefeatedUrsaluna::
	setflag FLAG_FOUGHT_NOBLE_URSALUNA
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_NOBLE_URSALUNA
	fadescreen FADE_FROM_BLACK
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_QuestionMark
	msgbox SinjohRuins_Cave_Text_EarthPlate MSGBOX_DEFAULT
	giveitem ITEM_EARTH_PLATE, 1
	addvar VAR_PLATECOUNTER, 1
	addvar VAR_NOBLECOUNTER, 1
	end

SinjohRuins_Cave_EventScript_RanFromUrsaluna::
	setvar VAR_0x8004, SPECIES_URSALUNA
	end

SinjohRuins_Cave_Text_Grrwowl:
    .string "GRRRR!!$"

SinjohRuins_Cave_Text_EarthPlate:
    .string "It seems URSALUNA left something behind..$"

