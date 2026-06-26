NewSinjoh_House3_hns_MapScripts::
    map_script MAP_SCRIPT_ON_FRAME_TABLE, NewSinjoh_House3_hns_OnFrame
	map_script MAP_SCRIPT_ON_LOAD, NewSinjoh_House3_hns_OnLoad
    .byte 0

NewSinjoh_House3_hns_OnFrame::
    map_script_2 VAR_NEWSINJOH_HAUNTEDHOUSE_FRONTDOOR, 0,  NewSinjoh_House3_hns_SpookyBox
    .2byte 0

NewSinjoh_House3_hns_OnLoad::
    goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_STAIRS, NewSinjoh_House3_FogAndStairs
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_FROSLASS, NewSinjoh_House3_RemoveFroslass
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_FROSLASS_CAUGHT, NewSinjoh_House3_BoxPurge
    end

NewSinjoh_House3_FogAndStairs::
    call_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_STAIRS, NewSinjoh_House3_Stairs
    setweather WEATHER_FOG_HORIZONTAL
	doweather
	end

NewSinjoh_House3_RemoveFroslass::
    removeobject LOCALID_HAUNTED_HOUSE_FROSLASS
	end

NewSinjoh_House3_hns_SpookyBox::
    goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_FROSLASS_CAUGHT, NewSinjoh_House3_BoxPurge
    lock
	hidefollower
	applymovement LOCALID_PLAYER, NewSinjoh_House3_Movement_WALK_In
	waitmovement 0
	playse SE_CLICK
    waitse
	delay 10
	fadescreen FADE_TO_BLACK
	delay 15
	addobject LOCALID_NEWSINJOH_SPOOKY_BOX
	fadescreen FADE_FROM_BLACK
	delay 10
    playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	delay 20
    applymovement LOCALID_PLAYER, NewSinjoh_House3_Movement_AfterExclamation
    waitmovement 0
	msgbox Text_NewSinjoh_TheDoor_IsLocked
	setvar VAR_NEWSINJOH_HAUNTEDHOUSE_FRONTDOOR, 1
	setvar VAR_NEWSINJOH_HAUNTEDHOUSE_PUZZLE, 0
	setvar VAR_NEWSINJOH_HAUNTEDHOUSE_GRAVESTONES, 0
	release
	end

NewSinjoh_House3_hns_PlaceBox::
	addobject LOCALID_NEWSINJOH_SPOOKY_BOX
	setvar VAR_NEWSINJOH_HAUNTEDHOUSE_FRONTDOOR, 1
	release
	end

NewSinjoh_House3_Movement_WALK_In:
	walk_up
	walk_up
	step_end

NewSinjoh_House3_Movement_AfterExclamation:
	jump_in_place_up
	face_down
	walk_down
	step_end

Text_NewSinjoh_TheDoor_IsLocked:
	.string "The door is blocked.\l"
	.string "Better find a way outta here fast.$"

NewSinjoh_House3_EnterEnd::
	release
	end

NewSinjoh_House3_RedBook::
    lock
	msgbox Text_NewSinjoh_House3_YouFound_A_Book, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_House3_NotYet
	msgbox Text_Tale_Of_A_Broken_Heart
	goto_if_set FLAG_NEWSINJOH_hAUNTEDHOUSE_KEYSUNLOCKED, NewSinjoh_House3_RedBookEnd
	setflag FLAG_NEWSINJOH_hAUNTEDHOUSE_KEYSUNLOCKED
	release
	end

NewSinjoh_House3_RedBookEnd::
    release
	end

NewSinjoh_House3_Key1::
    lock
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_KEY1, NewSinjoh_House3_Destroyed_Object
    msgbox Text_NewSinjoh_House3_CorrectSpot, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_House3_NotYet
	playse SE_REPEL
	delay 60
	msgbox Text_NewSinjoh_House3_GhostlyPresence
		lock
	faceplayer
	waitse
	playmoncry SPECIES_DUSKULL, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_DUSKULL, 40
	dowildbattle
	setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_KEY1
	addvar  VAR_NEWSINJOH_HAUNTEDHOUSE_PUZZLE, 1
	release
	end

NewSinjoh_House3_Key1_Filter::
    lock
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_KEY1, NewSinjoh_House3_Destroyed_Object
    goto_if_set FLAG_NEWSINJOH_hAUNTEDHOUSE_KEYSUNLOCKED, NewSinjoh_House3_Key1
	msgbox Text_NewSinjoh_House3_What_A_Neat_Box
	release
	end

NewSinjoh_House3_Key2_Filter::
    lock
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_KEY2, NewSinjoh_House3_Destroyed_Object
    msgbox Text_NewSinjoh_House3_What_A_Nice_Plant
    goto_if_set FLAG_NEWSINJOH_hAUNTEDHOUSE_KEYSUNLOCKED, NewSinjoh_House3_Key2
	release
	end


NewSinjoh_House3_Key3_Filter::
    lock
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_KEY3, NewSinjoh_House3_Destroyed_Object
    goto_if_set FLAG_NEWSINJOH_hAUNTEDHOUSE_KEYSUNLOCKED, NewSinjoh_House3_Key3
	msgbox Text_NewSinjoh_House3_What_A_Neat_Box
	release
	end

NewSinjoh_House3_FakePlant::
    lock
    msgbox Text_NewSinjoh_House3_What_A_Nice_Plant
	release
	end

NewSinjoh_House3_FakeBox::
    lock
    msgbox Text_NewSinjoh_House3_What_A_Neat_Box
	release
	end

Text_NewSinjoh_House3_What_A_Nice_Plant:
    .string "What a nice plant!\p"
	.string "Welp! Better get going.$"

Text_NewSinjoh_House3_What_A_Neat_Box:
    .string "This box is pretty dusty..\n"
	.string "It must be pretty old..\l"
	.string "Welp! Better keep moving.$"

NewSinjoh_House3_Key2::
    lock
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_KEY2, NewSinjoh_House3_Destroyed_Object
    msgbox Text_NewSinjoh_House3_CorrectSpot, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_House3_NotYet
	playse SE_REPEL
	delay 60
	msgbox Text_NewSinjoh_House3_GhostlyPresence
		lock
	faceplayer
	waitse
	playmoncry SPECIES_MISDREAVUS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_MISDREAVUS, 40
	dowildbattle
	setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_KEY2 
	addvar  VAR_NEWSINJOH_HAUNTEDHOUSE_PUZZLE, 1
	release
	end

NewSinjoh_House3_Key3::
    lock
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_KEY3, NewSinjoh_House3_Destroyed_Object
    msgbox Text_NewSinjoh_House3_CorrectSpot, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_House3_NotYet
	playse SE_REPEL
	delay 60
	msgbox Text_NewSinjoh_House3_GhostlyPresence
		lock
	faceplayer
	waitse
	playmoncry SPECIES_BANETTE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_BANETTE, 40
	dowildbattle
	setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_KEY3
	addvar  VAR_NEWSINJOH_HAUNTEDHOUSE_PUZZLE, 1
	release
	end

Text_NewSinjoh_House3_CorrectSpot:
	.string "You found a mysterious object!\l"
	.string "Destroy it?$"

NewSinjoh_House3_NotYet::
    msgbox Text_NewSinjoh_House3_Notyet
	release
	end

Text_NewSinjoh_House3_Notyet:
	.string "Maybe I better think this through\n"
	.string "first..$"

Text_NewSinjoh_House3_GhostlyPresence:
    .string "You feel a ghostly chill roll down\n"
	.string "your back!$"

Text_NewSinjoh_House3_YouFound_A_Book:
    .string "Something about this journal\n"
	.string "seems..off.\p"
	.string "Give it a read?$"

Text_Tale_Of_A_Broken_Heart:
    .string "This is a test for a lore book.$"

NewSinjoh_House3_Destroyed_Object::
    msgbox Text_NewSinjoh_House3_Already_Destroyed
	release
	end

Text_NewSinjoh_House3_Already_Destroyed:
    .string "You've already destroyed the object\n"
	.string "found here.\p"
	.string "Better keep searching for any\n"
	.string "others around here...$"

NewSinjoh_House3_Stove::
    lock
    compare VAR_NEWSINJOH_HAUNTEDHOUSE_PUZZLE, 3
	goto_if_lt NewSinjoh_House3_BetterKeepLooking
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_STAIRS, NewSinjoh_House3_AlreadyPurified
    msgbox Text_NewSinjoh_House3_Purify_Spirits, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_House3_NotYet
	closemessage
	playse SE_M_EMBER
	playse SE_REPEL
	delay 60
	setweather WEATHER_FOG_HORIZONTAL
	doweather
	msgbox Text_NewSinjoh_House3_Filled_WithFog
	closemessage
    setvar VAR_0x8004, 1  @ vertical pan
    setvar VAR_0x8005, 1  @ horizontal pan
    setvar VAR_0x8006, 20  @ num shakes
    setvar VAR_0x8007, 6  @ shake delay
    special ShakeCamera
    waitstate
	fadescreen FADE_TO_BLACK
	delay 15
	call_if_unset FLAG_NEWSINJOH_HAUNTEDHOUSE_STAIRS, NewSinjoh_House3_Stairs
	fadescreen FADE_FROM_BLACK
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	delay 30
	msgbox Text_NewSinjoh_House3_StairsAppears
	setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_STAIRS
	release
	end

NewSinjoh_House3_BetterKeepLooking::
    msgbox Text_NewSinjoh_House3_BetterKeepLooking
	release
	end


NewSinjoh_House3_Stairs::
	setmetatile 38, 13, 0x015, TRUE
	setmetatile 38, 14, 0x005, TRUE
	setmetatile 38, 15, 0x00D, TRUE
	setmetatile 39, 14, 0x006, TRUE
	setmetatile 39, 15, 0x00E, TRUE
	setmetatile 40, 14, 0x007, FALSE
	setmetatile 40, 15, 0x00F, FALSE
	return

Text_NewSinjoh_House3_BetterKeepLooking:
    .string "You still feel a chill in the air.\n"
	.string "Better keep looking around.$"


Text_NewSinjoh_House3_Purify_Spirits:
    .string "Would you like to burn some incense?$"


Text_NewSinjoh_House3_Filled_WithFog:
    .string "The building filled with\n"
	.string "smoke from the incense!$"
	

Text_NewSinjoh_House3_StairsAppears:
    .string "You hear a loud crash to\n"
	.string "the south..$"
	
NewSinjoh_House3_AlreadyPurified::
    msgbox Text_NewSinjoh_House3_Already_Purified
	release
	end


Text_NewSinjoh_House3_Already_Purified:
    .string "You've already purified the\n"
	.string "spirits here.\p"
	.string "Better keep exploring...$"

NewSinjoh_House3_hns_Gravestone_North::
    lock
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_FROSLASS_CAUGHT, NewSinjoh_House3_Gastly_Gone
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_GRAVELIGHT_NORTH, NewSinjoh_House3_Already_Shining
	playse SE_THUNDER
	fadescreen FADE_TO_WHITE
	delay 15
	addobject LOCALID_NEWSINJOH_NORTHLIGHT
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_GASTLY, 0
	delay 20
	msgbox Text_NewSinjoh_House3_Stone_Light
	addvar VAR_NEWSINJOH_HAUNTEDHOUSE_GRAVESTONES, 1
	setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_GRAVELIGHT_NORTH
	release
	end

NewSinjoh_House3_hns_Gravestone_West::
    lock
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_FROSLASS_CAUGHT, NewSinjoh_House3_Gastly_Gone
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_GRAVELIGHT_WEST, NewSinjoh_House3_Already_Shining
	playse SE_THUNDER
	fadescreen FADE_TO_WHITE
	delay 15
	addobject LOCALID_NEWSINJOH_WESTLIGHT
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_GASTLY, 0
	delay 20
	msgbox Text_NewSinjoh_House3_Stone_Light
	addvar VAR_NEWSINJOH_HAUNTEDHOUSE_GRAVESTONES, 1
	setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_GRAVELIGHT_WEST
	release
	end

NewSinjoh_House3_hns_Gravestone_East::
    lock
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_FROSLASS_CAUGHT, NewSinjoh_House3_Gastly_Gone
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_GRAVELIGHT_EAST, NewSinjoh_House3_Already_Shining
	playse SE_THUNDER
	fadescreen FADE_TO_WHITE
	delay 15
	addobject LOCALID_NEWSINJOH_EASTLIGHT
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_GASTLY, 0
	delay 20
	msgbox Text_NewSinjoh_House3_Stone_Light
	addvar VAR_NEWSINJOH_HAUNTEDHOUSE_GRAVESTONES, 1
	setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_GRAVELIGHT_EAST
	release
	end

NewSinjoh_House3_hns_Gravestone_South::
    lock
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_FROSLASS_CAUGHT, NewSinjoh_House3_Gastly_Gone
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_GRAVELIGHT_SOUTH, NewSinjoh_House3_Already_Shining
	playse SE_THUNDER
	fadescreen FADE_TO_WHITE
	delay 15
	addobject LOCALID_NEWSINJOH_SOUTHLIGHT
	fadescreen FADE_FROM_WHITE
	playmoncry SPECIES_GASTLY, 0
	delay 20
	msgbox Text_NewSinjoh_House3_Stone_Light
	addvar VAR_NEWSINJOH_HAUNTEDHOUSE_GRAVESTONES, 1
	setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_GRAVELIGHT_SOUTH
	release
	end

NewSinjoh_House3_Already_Shining::
    msgbox Text_NewSinjoh_House3_Already_Shining
	release
	end

Text_NewSinjoh_House3_Already_Shining:
    .string "Gastly is ready to help you!\p"
	.string "Better not keep it waiting...$"

Text_NewSinjoh_House3_Stone_Light:
    .string "A wild GASTLY came out from\n"
	.string "the grave to help!\p"
	.string "Better keep moving..$"

NewSinjoh_House3_Summoning_Circle::
    lock
	msgbox Text_NewSinjoh_Summoning_Circle
    compare VAR_NEWSINJOH_HAUNTEDHOUSE_GRAVESTONES, 4
	goto_if_lt NewSinjoh_House3_BetterKeepLooking
	goto_if_set FLAG_NEWSINJOH_HAUNTEDHOUSE_FROSLASS_CAUGHT, NewSinjoh_House3_Already_Caught
    msgbox Text_NewSinjoh_House3_Activate_Circle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_House3_NotYet
	closemessage
	playse MUS_HG_DANCE_THEATER
	applymovement LOCALID_NEWSINJOH_NORTHLIGHT, NewSinjoh_House3_Gastly_Movement_North
	waitmovement 20
	delay 90
	applymovement LOCALID_NEWSINJOH_WESTLIGHT, NewSinjoh_House3_Gastly_Movement_West
	waitmovement 20
	delay 90
	applymovement LOCALID_NEWSINJOH_EASTLIGHT, NewSinjoh_House3_Gastly_Movement_East
	waitmovement 20
	delay 90
	applymovement LOCALID_NEWSINJOH_SOUTHLIGHT, NewSinjoh_House3_Gastly_Movement_South
	waitmovement 20
	delay 90
	fadescreen FADE_TO_WHITE
	playse SE_THUNDER
	removeobject LOCALID_NEWSINJOH_NORTHLIGHT
	removeobject LOCALID_NEWSINJOH_WESTLIGHT
	removeobject LOCALID_NEWSINJOH_EASTLIGHT
	removeobject LOCALID_NEWSINJOH_SOUTHLIGHT
	delay 20
	playse SE_THUNDER
    waitse
	delay 10
	addobject LOCALID_HAUNTED_HOUSE_FROSLASS
	fadescreen FADE_FROM_WHITE
	msgbox Text_NewSinjoh_House3_FroslassCry, MSGBOX_DEFAULT
	waitse
	playmoncry SPECIES_FROSLASS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattleshiny SPECIES_FROSLASS, 70
	dowildbattle
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_HAUNTED_HOUSE_FROSLASS
	fadescreen FADE_FROM_BLACK
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, NewSinjoh_EventScript_Defeated_Froslass
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, NewSinjoh_EventScript_Ran_Froslass
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, NewSinjoh_EventScript_Ran_Froslass
NewSinjoh_EventScript_Defeated_Froslass::
	setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_FROSLASS
	clearflag FLAG_TEMP_1
	setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_FROSLASS_CAUGHT
	subvar VAR_NEWSINJOH_HAUNTEDHOUSE_FRONTDOOR, 1
	subvar VAR_NEWSINJOH_HAUNTEDHOUSE_STAIRS, 1
	removeobject LOCALID_NEWSINJOH_SPOOKY_BOX
	msgbox Text_NewSinjoh_House3_Sprits_Gone
	release
	end

NewSinjoh_EventScript_Ran_Froslass::
	setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_FROSLASS_CAUGHT
	msgbox Text_NewSinjoh_House3_Sprits_Gone
	release
	end

NewSinjoh_House3_Already_Caught::
    msgbox Text_NewSinjoh_AlreadyBattled
	release
	end

Text_NewSinjoh_Summoning_Circle:
    .string "{PLAYER} found a summoning circle..$"

Text_NewSinjoh_House3_Activate_Circle:
    .string "Would you like to activate it?$"

Text_NewSinjoh_House3_FroslassCry:
    .string "BWAASHAA!$"

Text_NewSinjoh_AlreadyBattled:
    .string "You remember the battle fought here...\p"
    .string "Better to keep moving forwards.$"

Text_NewSinjoh_House3_Sprits_Gone:
    .string "It seems like the spirits trapped here\n"
	.string "are now gone..\l"
	.string "Perhaps it's now possible to leave?$"

NewSinjoh_House3_BoxPurge::
    removeobject LOCALID_NEWSINJOH_SPOOKY_BOX
	subvar VAR_NEWSINJOH_HAUNTEDHOUSE_FRONTDOOR, 1
	end

NewSinjoh_House3_Gastly_Movement_North:
    walk_down
	walk_down
	walk_left
	walk_down
	step_end

NewSinjoh_House3_Gastly_Movement_West:
    walk_right
	walk_right
	walk_down
	walk_right
	walk_right
	step_end

NewSinjoh_House3_Gastly_Movement_East:
	walk_left
	walk_left
	walk_up
	face_down
	face_right
	face_left
	walk_left
	walk_left
	step_end

NewSinjoh_House3_Gastly_Movement_South:
    walk_up
	walk_up
	walk_right
	walk_up
	step_end

NewSinjoh_House3_Gastly_Gone::
    msgbox Text_GastlyGone
	release
	end

Text_GastlyGone:
    .string "The Gastly that helped you\n"
	.string "is no longer here...$"