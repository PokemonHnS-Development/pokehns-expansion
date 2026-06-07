Melemele_House_hns_MapScripts::
# 2 "data/maps/Melemele_House_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Melemele_House_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION
	.byte 0

Melemele_House_hns_MapScripts_MAP_SCRIPT_ON_TRANSITION:
# 3 "data/maps/Melemele_House_hns/scripts.pory"
	setrespawn HEAL_LOCATION_ALOLA_ISLAND_MELEMELE_HNS
	end


Alola_Melemele_Pokecenter_AceTrainer::
# 9 "data/maps/Melemele_House_hns/scripts.pory"
	lock
# 10 "data/maps/Melemele_House_hns/scripts.pory"
	faceplayer
# 11 "data/maps/Melemele_House_hns/scripts.pory"
	msgbox Alola_Melemele_Pokecenter_AceTrainer_Text_0, MSGBOX_AUTOCLOSE
# 13 "data/maps/Melemele_House_hns/scripts.pory"
	release
	end


Alola_Melemele_Pokecenter_BugCatcher::
# 18 "data/maps/Melemele_House_hns/scripts.pory"
	lock
# 19 "data/maps/Melemele_House_hns/scripts.pory"
	faceplayer
# 20 "data/maps/Melemele_House_hns/scripts.pory"
	msgbox Alola_Melemele_Pokecenter_BugCatcher_Text_0, MSGBOX_AUTOCLOSE
# 24 "data/maps/Melemele_House_hns/scripts.pory"
	playse SE_PIN
# 25 "data/maps/Melemele_House_hns/scripts.pory"
	applymovement Melemele_PokecenterGrubbin, Alola_Melemele_Pokecenter_BugCatcher_Movement_0
# 26 "data/maps/Melemele_House_hns/scripts.pory"
	waitmovement 0
# 27 "data/maps/Melemele_House_hns/scripts.pory"
	waitse
# 28 "data/maps/Melemele_House_hns/scripts.pory"
	playmoncry SPECIES_GRUBBIN, 0
# 29 "data/maps/Melemele_House_hns/scripts.pory"
	waitmoncry
# 30 "data/maps/Melemele_House_hns/scripts.pory"
	release
	end


Alola_Melemele_Pokecenter_Grubbin::
# 35 "data/maps/Melemele_House_hns/scripts.pory"
	lock
# 36 "data/maps/Melemele_House_hns/scripts.pory"
	faceplayer
# 37 "data/maps/Melemele_House_hns/scripts.pory"
	playmoncry SPECIES_GRUBBIN, 0
# 38 "data/maps/Melemele_House_hns/scripts.pory"
	msgbox Alola_Melemele_Pokecenter_Grubbin_Text_0, MSGBOX_AUTOCLOSE
# 39 "data/maps/Melemele_House_hns/scripts.pory"
	waitmoncry
# 40 "data/maps/Melemele_House_hns/scripts.pory"
	release
	end


# 25 "data/maps/Melemele_House_hns/scripts.pory"
Alola_Melemele_Pokecenter_BugCatcher_Movement_0:
# 25 "data/maps/Melemele_House_hns/scripts.pory"
	face_up
# 25 "data/maps/Melemele_House_hns/scripts.pory"
	emote_exclamation_mark
	step_end

Alola_Melemele_Pokecenter_AceTrainer_Text_0:
# 11 "data/maps/Melemele_House_hns/scripts.pory"
	.string "There are so many unique Pokémon here!\n"
	.string "I'm gonna catch 'em all!$"

Alola_Melemele_Pokecenter_BugCatcher_Text_0:
# 20 "data/maps/Melemele_House_hns/scripts.pory"
	.string "I found some brand new bug Pokémon\n"
	.string "here on the Isles!\p"
	.string "Like my new friend Grubbin here!$"

Alola_Melemele_Pokecenter_Grubbin_Text_0:
# 38 "data/maps/Melemele_House_hns/scripts.pory"
	.string "Grub!$"
