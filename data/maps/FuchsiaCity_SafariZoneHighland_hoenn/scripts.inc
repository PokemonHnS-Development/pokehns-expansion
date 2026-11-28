@ Hoenn & Seek 2.0 part 30b: the Safari Zone's highland (composed map), above the
@ MOUNTAIN's east canyon (a map connection: the canyon runs on into this map's
@ bottom rows). Monday mornings the Tauros herd charges across it; the lead bull
@ waits in the nook of the north cliff. Scenes: data/scripts/hoenn_lane_b.inc
@ (Part 30b section, which includes this file); the herd's movement and the
@ knock-backs are src/hoenn_lane_b.c's stampede task.
FuchsiaCity_SafariZoneHighland_hoenn_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HoennSeek_EventScript_HighlandOnTransition
	map_script MAP_SCRIPT_ON_RESUME, HoennSeek_EventScript_HighlandOnResume
	.byte 0
