@ Hoenn & Seek 2.0 part 31b: the moon hollow above Route 45, where the Ursaring
@ mother leads you (scripts in data/scripts/hoenn_lane_b.inc, which includes this file).
Route45_MoonHollow_hoenn_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HoennSeek_EventScript_MoonHollowOnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route45_MoonHollow_hoenn_OnFrame
	.byte 0

Route45_MoonHollow_hoenn_OnFrame:
	map_script_2 VAR_TEMP_1, 1, HoennSeek_EventScript_MoonHollowArrival
	.2byte 0
