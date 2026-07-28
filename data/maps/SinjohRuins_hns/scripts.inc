SinjohRuins_hns_MapScripts::
    map_script 	MAP_SCRIPT_ON_TRANSITION, SinjohRuins_hns_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, SinjohRuins_hns_OnLoad
	.byte 0

SinjohRuins_hns_OnTransition::
	end

SinjohRuins_hns_OnLoad::
    @call_if_set FLAG_SINJOHRUINS_ARCEUS_STAIRS, SinjohRuins_Arceus_Stairs
    end

