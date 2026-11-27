@ Hoenn & Seek 2.0 part 29: the Dunsparce burrow under Dark Cave (composed map).
@ Every burrow hole in Dark Cave's south side drops you into the room (warp 0,
@ an arrival point); the ladder (warp 1) climbs back out. The passage up to the
@ chamber is choked with rubble (HoennDrawBurrowRubble); each time of day's
@ Dunsparce digs one row out, once. Scenes: data/scripts/hoenn_lane_b.inc.
DarkCave_Burrow_hoenn_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, DarkCave_Burrow_hoenn_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, DarkCave_Burrow_hoenn_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, DarkCave_Burrow_hoenn_OnFrame
	.byte 0

DarkCave_Burrow_hoenn_OnLoad:
	special HoennDrawBurrowRubble
	end

@ Shows this time of day's digger (below the lowest row of rubble) if it
@ hasn't dug yet, and the Dudunsparce once the passage is open.
DarkCave_Burrow_hoenn_OnTransition:
	specialvar VAR_RESULT, HoennBurrowPrepare
	goto_if_eq VAR_RESULT, FALSE, DarkCave_Burrow_hoenn_OnTransitionEnd
	setobjectxyperm LOCALID_HOENN_BURROW_DIGGER, VAR_0x8008, VAR_0x8009
	setvar VAR_TEMP_1, 1
DarkCave_Burrow_hoenn_OnTransitionEnd:
	end

DarkCave_Burrow_hoenn_OnFrame:
	map_script_2 VAR_TEMP_1, 1, HoennSeek_EventScript_BurrowDig
	.2byte 0
