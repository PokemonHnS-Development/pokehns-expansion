@ Hoenn & Seek 2.0 part 23: the clifftop above Meteor Falls where the Altaria chorus sings (scripts in data/scripts/hoenn_hidden.inc).
MeteorFalls_Clifftop_hoenn_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HoennSeek_EventScript_ClifftopOnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MeteorFalls_Clifftop_hoenn_OnFrame
	.byte 0

MeteorFalls_Clifftop_hoenn_OnFrame:
	map_script_2 VAR_TEMP_1, 1, HoennSeek_EventScript_ChorusIntro
	.2byte 0
