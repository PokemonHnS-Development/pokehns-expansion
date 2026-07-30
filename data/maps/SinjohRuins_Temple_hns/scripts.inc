SinjohRuins_Temple_hns_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, SinjohRuins_Temple_OnLoad
	.byte 0


SinjohRuins_Temple_OnLoad::
	call_if_eq VAR_REGIS_SCANNED, 5, SinjohRuins_Temple_OpenDoor
	end

SinjohRuins_Temple_OpenDoor::
	setmetatile 18, 7, 0x308, FALSE
	return
