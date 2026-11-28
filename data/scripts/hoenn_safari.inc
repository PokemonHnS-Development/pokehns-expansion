@ Hoenn & Seek (part 17): the Hoenn Safari Zone (Route 121) on HnS's Safari engine.
@ HnS runs two Safari Zones already (Johto's gate and Fuchsia's, told apart by
@ FLAG_IN_KANTO_SAFARI_ZONE); Route 121's entrance sets FLAG_HOENN_IN_SAFARI_ZONE,
@ and the shared exits in data/scripts/safari_zone.inc send you back here.

HoennSeek_EventScript_SafariExit::
	clearflag FLAG_HOENN_IN_SAFARI_ZONE
	warp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
	waitstate
	end

HoennSeek_EventScript_SafariExitMidBattle::
	clearflag FLAG_HOENN_IN_SAFARI_ZONE
	setwarp MAP_ROUTE121_SAFARI_ZONE_ENTRANCE, 2, 5
	end
