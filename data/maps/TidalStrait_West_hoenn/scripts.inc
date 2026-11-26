@ Hoenn & Seek 2.0 (part 14): the Tidal Strait, Johto half (south of Route 41).
@ The great whirlpool (four whirlpool objects on FLAG_HOENN_STRAIT_OPEN) blocks the
@ channel through the rocks until you have Oak's TIDAL TICKET. The bottom channel's
@ last row warps to the Hoenn half: the halves use different tilesets, so they can't
@ share a map connection (data/hoenn/strait.json explains the layouts).

TidalStrait_West_hoenn_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TidalStrait_West_hoenn_OnTransition
	.byte 0

@ Oak sets the flag when he hands over the ticket; this covers a ticket received
@ before part 14 existed.
TidalStrait_West_hoenn_OnTransition:
	goto_if_set FLAG_HOENN_STRAIT_OPEN, TidalStrait_West_hoenn_OnTransitionEnd
	checkitem ITEM_TIDAL_TICKET
	goto_if_eq VAR_RESULT, FALSE, TidalStrait_West_hoenn_OnTransitionEnd
	setflag FLAG_HOENN_STRAIT_OPEN
TidalStrait_West_hoenn_OnTransitionEnd:
	end

TidalStrait_West_hoenn_EventScript_Whirlpool::
	msgbox TidalStrait_West_hoenn_Text_Whirlpool, MSGBOX_SIGN
	end

TidalStrait_West_hoenn_EventScript_ToHoenn::
	getplayerxy VAR_0x8004, VAR_0x8005
	warp MAP_TIDAL_STRAIT_EAST_HOENN, VAR_0x8004, 1
	waitstate
	end

TidalStrait_West_hoenn_Text_Whirlpool:
	.string "A huge whirlpool churns through the\n"
	.string "gap in the rocks.\p"
	.string "Even WHIRLPOOL couldn't calm water\n"
	.string "this wild. Not today, at least.$"
