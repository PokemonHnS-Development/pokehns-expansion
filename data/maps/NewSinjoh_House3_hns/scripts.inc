NewSinjoh_House3_hns_MapScripts::
    map_script MAP_SCRIPT_ON_FRAME_TABLE, NewSinjoh_House3_OnFrame
    .byte 0


NewSinjoh_House3_OnFrame:
    map_script_2 VAR_TEMP_0, 0, NewSinjoh_HauntedHouse_EventScript_Enter
	.2byte 0


NewSinjoh_HauntedHouse_EventScript_Enter::
    setvar VAR_TEMP_0, 1
	goto_if_lt VAR_SINJOH_STORYLINE, 6, NewSinjoh_HauntedHouse_EventScript_EnterTooEarly
    goto_if_eq VAR_SINJOH_STORYLINE, 6, NewSinjoh_HauntedHouse_EventScript_TryStartScary
    end

NewSinjoh_HauntedHouse_EventScript_EnterTooEarly::
    lock
    msgbox NewSinjoh_HauntedHouse_Text_TooEarlyNoReaction, MSGBOX_AUTOCLOSE
    release
    end

NewSinjoh_HauntedHouse_Text_TooEarlyNoReaction:
    .string "You sense an odd presence...\p"
    .string "But there is no reaction.$"

NewSinjoh_HauntedHouse_EventScript_TryStartScary::
    lock
    msgbox NewSinjoh_HauntedHouse_Text_StartScary, MSGBOX_AUTOCLOSE
    release
    end

NewSinjoh_HauntedHouse_Text_StartScary:
    .string "You sense an odd presence...\p"
    .string "Are you being watched?$"

