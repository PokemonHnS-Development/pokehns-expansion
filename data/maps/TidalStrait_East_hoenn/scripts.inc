@ Hoenn & Seek 2.0 (part 14): the Tidal Strait, Hoenn half (west of Route 105).
@ The top channel's first row warps back to the Johto half (see its scripts.inc).

TidalStrait_East_hoenn_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TidalStrait_East_hoenn_OnTransition
	.byte 0

@ May's PokéGear call (src/hoenn_phone.c) rings once this is set. If you
@ cross before Birch gives you her number, the call is marked done: by the
@ time you have the number the news is stale (part 17r).
TidalStrait_East_hoenn_OnTransition:
	goto_if_set FLAG_HOENN_CROSSED_STRAIT, TidalStrait_East_hoenn_OnTransitionEnd
	setflag FLAG_HOENN_CROSSED_STRAIT
	goto_if_set FLAG_HOENN_BM_PHONE, TidalStrait_East_hoenn_OnTransitionEnd
	setflag FLAG_HOENN_CALL_STRAIT
TidalStrait_East_hoenn_OnTransitionEnd:
	end

TidalStrait_East_hoenn_EventScript_ToJohto::
	getplayerxy VAR_0x8004, VAR_0x8005
	warp MAP_TIDAL_STRAIT_WEST_HOENN, VAR_0x8004, 34
	waitstate
	end
