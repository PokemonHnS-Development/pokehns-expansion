NewSinjoh_House3_hns_MapScripts::
    map_script MAP_SCRIPT_ON_FRAME_TABLE, NewSinjoh_House3_hns_Enter
    .byte 0

NewSinjoh_House3_hns_OnFrame::
    map_script_2 VAR_NEWSINJOH_HAUNTEDHOUSE_FRONTDOOR, 0,  NewSinjoh_House3_hns_SpookyBox
    .2byte 0

NewSinjoh_House3_hns_Enter::
    setflag FLAG_NEWSINJOH_HAUNTEDHOUSE_DOORLOCK 
    end


NewSinjoh_House3_hns_SpookyBox::
    lock
	hidefollower
	applymovement LOCALID_PLAYER, NewSinjoh_House3_Movement_WALK_In
	waitmovement 0
	playfanfare SE_THUNDERSTORM
    waitfanfare
	delay 15
	fadescreen FADE_TO_BLACK
	delay 15
	addobject LOCALID_NEWSINJOH_SPOOKY_BOX
	fadescreen FADE_FROM_BLACK
	delay 10
    playse SE_PIN
    applymovement LOCALID_PLAYER, Movement_Exclamation
    waitmovement 0
	msgbox Text_NewSinjoh_TheDoor_IsLocked
	setvar VAR_NEWSINJOH_HAUNTEDHOUSE_FRONTDOOR, 1
	release
	end

NewSinjoh_House3_Movement_WALK_In:
	walk_up
	walk_up
	step_end

Movement_Exclamation:
	emote_exclamation_mark
	jump_in_place_up
	player_run_down
	player_run_down
	step_end

Text_NewSinjoh_TheDoor_IsLocked:
	.string "The door is blocked.\l"
	.string "Better find a way outta here fast.$"

NewSinjoh_House3_EnterEnd::
	release
	end
