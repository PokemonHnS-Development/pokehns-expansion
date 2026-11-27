IcePath_B2F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, IcePath_B2F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

IcePath_B2F_OnTransition: 
	call HoennSeek_EventScript_SneaselArm @ Hoenn & Seek 2.0 part 31a: the Sneasel thief
	callnative SetTimeBasedEncounters
	end

IcePath_B2F_EventScript_Item_FullHeal::
	finditem ITEM_FULL_HEAL
	end

IcePath_B2F_EventScript_Item_MaxPotion::
	finditem ITEM_MAX_POTION
	end

IcePath_B2F_EventScript_Item_Carbos::
	finditem ITEM_CARBOS
	end
