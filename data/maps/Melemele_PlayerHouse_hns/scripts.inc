Melemele_PlayerHouse_hns_MapScripts::
# 2 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Melemele_PlayerHouse_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE
	.byte 0

Melemele_PlayerHouse_hns_MapScripts_MAP_SCRIPT_ON_FRAME_TABLE:
# 2 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	map_script_2 VAR_ALOLA_STATE, 1, Alola_Melemele_SamsonOakVillaIntro_Trigger
	.2byte 0


Alola_Melemele_SamsonOakVillaIntro_Trigger::
# 6 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	lock
# 7 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	playse SE_PIN
# 8 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_0
# 9 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 10 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_0
# 11 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_1
# 12 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 13 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_1, MSGBOX_AUTOCLOSE
# 22 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_2
# 23 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 24 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_2, MSGBOX_AUTOCLOSE
# 36 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	applymovement SamsonOakVilla, Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_3
# 37 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	waitmovement 0
# 38 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	setvar VAR_ALOLA_STATE, 2
# 39 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end


Alola_Melemele_SamsonOakVilla_Dialogue::
# 44 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	lock
# 45 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	faceplayer
# 46 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_0
# 53 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	dynmultichoice 20, 6, TRUE, 4, 0, DYN_MULTICHOICE_CB_NONE, Alola_Melemele_SamsonOakVilla_Dialogue_Text_1, Alola_Melemele_SamsonOakVilla_Dialogue_Text_2, Alola_Melemele_SamsonOakVilla_Dialogue_Text_3, Alola_Melemele_SamsonOakVilla_Dialogue_Text_4, Alola_Melemele_SamsonOakVilla_Dialogue_Text_5
# 54 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_1
# 58 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_2
# 62 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_3
# 66 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	compare VAR_RESULT, 3
	goto_if_eq Alola_Melemele_SamsonOakVilla_Dialogue_4
# 71 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	msgbox Alola_Melemele_SamsonOakVilla_Dialogue_Text_6, MSGBOX_AUTOCLOSE
# 75 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_1:
# 55 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_2:
# 59 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_3:
# 63 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end

Alola_Melemele_SamsonOakVilla_Dialogue_4:
# 67 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	release
	end


# 8 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_0:
# 8 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	emote_exclamation_mark
# 8 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	face_down
	step_end

# 11 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_1:
# 11 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	walk_down
# 11 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	walk_left
# 11 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	face_down
	step_end

# 22 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_2:
# 22 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	walk_in_place_down
# 22 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	walk_in_place_down
	step_end

# 36 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
Alola_Melemele_SamsonOakVillaIntro_Trigger_Movement_3:
# 36 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	walk_right
# 36 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	walk_up
# 36 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	face_right
	step_end

Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_0:
# 10 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Alola, {PLAYER}!$"

Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_1:
# 13 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "I'm glad you're here!\n"
	.string "Welcome to my Villa!\p"
	.string "I'm staying here while I research the\n"
	.string "Alola Isles for their similarity to\l"
	.string "the Alola Region.\p"
	.string "I'm particularly interested in the\n"
	.string "phenomenon of “Regional Variants”.$"

Alola_Melemele_SamsonOakVillaIntro_Trigger_Text_2:
# 24 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "You seem quite capable.\p"
	.string "You'd be perfect to help with my survey\n"
	.string "of the Alola Isles!\p"
	.string "Explore all the Isles have to offer,\n"
	.string "and if you find any familiar Pokémon\l"
	.string "that resemble those from Kanto…\l"
	.string "come back and show me your PokéDex!\p"
	.string "I'll be here patiently waiting to hear\n"
	.string "about your progress!$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_0:
# 46 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Hello again, {PLAYER}!\p"
	.string "How's your research on the Alola Isles\n"
	.string "coming along?\p"
	.string "Would you like to share your progress\n"
	.string "about a specific Isle with me?$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_1:
# 53 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Melemele Isle$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_2:
# 53 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Akala Isle$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_3:
# 53 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Ula'ula Isle$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_4:
# 53 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Poni Isle$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_5:
# 53 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "Not right now.$"

Alola_Melemele_SamsonOakVilla_Dialogue_Text_6:
# 71 "data/maps/Melemele_PlayerHouse_hns/scripts.pory"
	.string "No worries, {PLAYER}!\p"
	.string "Come back when you'd like to share your\n"
	.string "findings about the Alola Isles!$"
