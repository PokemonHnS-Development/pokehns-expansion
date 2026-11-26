@ Hoenn & Seek 2.0 (part 14): the Tidal Strait, Hoenn half (west of Route 105).
@ The top channel's first row warps back to the Johto half (see its scripts.inc).

TidalStrait_East_hoenn_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TidalStrait_East_hoenn_OnTransition
	.byte 0

@ May's PokéGear call (src/hoenn_phone.c) rings once this is set.
TidalStrait_East_hoenn_OnTransition:
	setflag FLAG_HOENN_CROSSED_STRAIT
	end

TidalStrait_East_hoenn_EventScript_ToJohto::
	getplayerxy VAR_0x8004, VAR_0x8005
	warp MAP_TIDAL_STRAIT_WEST_HOENN, VAR_0x8004, 34
	waitstate
	end
