RockTunnel_B1F_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RockTunnel_B1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	map_script MAP_SCRIPT_ON_LOAD, HoennSeek_EventScript_RockTunnelB1FOnLoad @ Hoenn & Seek 2.0 part 29
	map_script MAP_SCRIPT_ON_FRAME_TABLE, HoennSeek_EventScript_RockTunnelB1FOnFrame @ Hoenn & Seek 2.0 part 29
	.byte 0

RockTunnel_B1F_OnTransition: 
	callnative SetTimeBasedEncounters
	call HoennSeek_EventScript_RockTunnelB1FOnTransition @ Hoenn & Seek 2.0 part 29
	end

RockTunnel_B1F_EventScript_ItemFling::
	finditem ITEM_TM_FLING
	end

RockTunnel_B1F_EventScript_Elixir::
	finditem ITEM_ELIXIR
	end
