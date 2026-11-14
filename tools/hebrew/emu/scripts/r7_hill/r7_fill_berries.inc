@ Fill the Berries pocket: top up any GANLON BERRY stack to a full slot, then add full ORAN BERRY
@ slots until additem fails, so the roof prize (a Ganlon Berry at under 10 minutes on Expert)
@ finds no room (TrainerHill_Roof_hns_EventScript_NoRoomForPrize).
	additem ITEM_GANLON_BERRY, 999
	setvar VAR_0x8004, 0
R7Fill_Loop:
	additem ITEM_ORAN_BERRY, 999
	addvar VAR_0x8004, 1
	goto_if_lt VAR_0x8004, 80, R7Fill_Loop
	end
