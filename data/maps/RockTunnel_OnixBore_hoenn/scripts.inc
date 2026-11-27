@ Hoenn & Seek 2.0 part 29: the Onix's bore under Rock Tunnel B1F (composed map).
@ Tonight's hole in B1F drops you at the bottom (warp 0, an arrival point); the
@ bottom row (7-8, 21) takes you back below today's hole. Scenes are in
@ data/scripts/hoenn_lane_b.inc (Part 29 section), which includes this file.
RockTunnel_OnixBore_hoenn_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RockTunnel_OnixBore_hoenn_OnTransition
	.byte 0

@ The Onix rests here at night until it's caught or knocked out tonight.
RockTunnel_OnixBore_hoenn_OnTransition:
	setflag FLAG_HOENN_HIDE_ONIX
	goto_if_set FLAG_HOENN_ONIX_CAUGHT, RockTunnel_OnixBore_hoenn_OnTransitionEnd
	goto_if_set FLAG_HOENN_DAILY_ONIX_GONE, RockTunnel_OnixBore_hoenn_OnTransitionEnd
	gettimeofday
	goto_if_ne VAR_0x8000, HOENN_TIME_NIGHT, RockTunnel_OnixBore_hoenn_OnTransitionEnd
	clearflag FLAG_HOENN_HIDE_ONIX
RockTunnel_OnixBore_hoenn_OnTransitionEnd:
	end
