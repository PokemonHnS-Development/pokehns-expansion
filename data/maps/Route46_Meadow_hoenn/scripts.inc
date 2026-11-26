@ Hoenn & Seek 2.0 part 15a: the hidden meadow behind Route 46's cave
@ (layout from data/hoenn/composed_maps.json). The Chikorita scene's scripts
@ are in data/scripts/hoenn_starters.inc.
Route46_Meadow_hoenn_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route46_Meadow_hoenn_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route46_Meadow_hoenn_OnTransition:
	callnative SetTimeBasedEncounters
	goto HoennSeek_EventScript_MeadowOnTransition
