@ Hoenn & Seek 2.0 parts 26a/26b: the frozen chamber under Shoal Cave's ice
@ room (scripts in data/scripts/hoenn_hidden.inc): Glalie by day, the
@ Froslass's pillar chase by night.
ShoalCave_IceChamber_hoenn_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HoennSeek_EventScript_IceChamberOnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ShoalCave_IceChamber_hoenn_OnFrame
	.byte 0

ShoalCave_IceChamber_hoenn_OnFrame:
	map_script_2 VAR_TEMP_5, 1, HoennSeek_EventScript_IceFroslassIntro
	.2byte 0
