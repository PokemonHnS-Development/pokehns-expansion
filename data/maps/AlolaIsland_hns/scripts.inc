AlolaIsland_hns_MapScripts::
	.byte 0


Alola_Poni_BattleExeggutor::
# 6 "data/maps/AlolaIsland_hns/scripts.pory"
	lock
# 7 "data/maps/AlolaIsland_hns/scripts.pory"
	faceplayer
# 8 "data/maps/AlolaIsland_hns/scripts.pory"
	setflag FLAG_BATTLED_EXEGGUTOR
# 9 "data/maps/AlolaIsland_hns/scripts.pory"
	playmoncry SPECIES_EXEGGUTOR_ALOLA, 0
# 10 "data/maps/AlolaIsland_hns/scripts.pory"
	msgbox Alola_Poni_BattleExeggutor_Text_0, MSGBOX_AUTOCLOSE
# 11 "data/maps/AlolaIsland_hns/scripts.pory"
	waitmoncry
# 12 "data/maps/AlolaIsland_hns/scripts.pory"
	setwildbattle SPECIES_EXEGGUTOR_ALOLA, 45
# 13 "data/maps/AlolaIsland_hns/scripts.pory"
	dowildbattle
# 14 "data/maps/AlolaIsland_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 15 "data/maps/AlolaIsland_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Poni_BattleExeggutor_2
# 21 "data/maps/AlolaIsland_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Poni_BattleExeggutor_3
# 28 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end

# 31 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end

Alola_Poni_BattleExeggutor_2:
# 16 "data/maps/AlolaIsland_hns/scripts.pory"
	setflag FLAG_CAUGHT_EXEGGUTOR_ALOLA
# 17 "data/maps/AlolaIsland_hns/scripts.pory"
	removeobject Alola_Poni_Exeggutor
# 18 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end

Alola_Poni_BattleExeggutor_3:
# 22 "data/maps/AlolaIsland_hns/scripts.pory"
	setflag FLAG_CAUGHT_EXEGGUTOR_ALOLA
# 23 "data/maps/AlolaIsland_hns/scripts.pory"
	removeobject Alola_Poni_Exeggutor
# 24 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end


Alola_Poni_Island_Sign::
# 36 "data/maps/AlolaIsland_hns/scripts.pory"
	lock
# 37 "data/maps/AlolaIsland_hns/scripts.pory"
	msgbox Alola_Poni_Island_Sign_Text_0
# 38 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end


Alola_Poni_TotemBattle_Trigger::
# 43 "data/maps/AlolaIsland_hns/scripts.pory"
	goto_if_unset FLAG_TRIGGERED_PONI_TOTEM, Alola_Poni_TotemBattle_Trigger_1
	end

Alola_Poni_TotemBattle_Trigger_1:
# 45 "data/maps/AlolaIsland_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_AKALA, Alola_Poni_TotemBattle_Trigger_7
Alola_Poni_TotemBattle_Trigger_5:
	end

Alola_Poni_TotemBattle_Trigger_4:
# 47 "data/maps/AlolaIsland_hns/scripts.pory"
	lock
# 48 "data/maps/AlolaIsland_hns/scripts.pory"
	delay 30
# 49 "data/maps/AlolaIsland_hns/scripts.pory"
	setvar VAR_0x8004, 2
# 50 "data/maps/AlolaIsland_hns/scripts.pory"
	setvar VAR_0x8005, 6
# 51 "data/maps/AlolaIsland_hns/scripts.pory"
	setvar VAR_0x8006, 4
# 52 "data/maps/AlolaIsland_hns/scripts.pory"
	setvar VAR_0x8007, 4
# 53 "data/maps/AlolaIsland_hns/scripts.pory"
	special ShakeCamera
# 54 "data/maps/AlolaIsland_hns/scripts.pory"
	waitstate
# 55 "data/maps/AlolaIsland_hns/scripts.pory"
	fadescreenswapbuffers FADE_TO_BLACK
# 56 "data/maps/AlolaIsland_hns/scripts.pory"
	delay 30
# 57 "data/maps/AlolaIsland_hns/scripts.pory"
	clearflag FLAG_HIDE_PONI_TOTEM
# 58 "data/maps/AlolaIsland_hns/scripts.pory"
	playmoncry SPECIES_KOMMO_O, 0
# 59 "data/maps/AlolaIsland_hns/scripts.pory"
	addobject Poni_Totem
# 60 "data/maps/AlolaIsland_hns/scripts.pory"
	waitmoncry
# 61 "data/maps/AlolaIsland_hns/scripts.pory"
	delay 30
# 62 "data/maps/AlolaIsland_hns/scripts.pory"
	fadescreenswapbuffers FADE_FROM_BLACK
# 63 "data/maps/AlolaIsland_hns/scripts.pory"
	delay 30
# 64 "data/maps/AlolaIsland_hns/scripts.pory"
	playmoncry SPECIES_KOMMO_O, 0
# 65 "data/maps/AlolaIsland_hns/scripts.pory"
	applymovement Poni_Totem, Alola_Poni_TotemBattle_Trigger_Movement_0
# 66 "data/maps/AlolaIsland_hns/scripts.pory"
	waitmovement 0
# 67 "data/maps/AlolaIsland_hns/scripts.pory"
	waitmoncry
# 68 "data/maps/AlolaIsland_hns/scripts.pory"
	setflag FLAG_TRIGGERED_PONI_TOTEM
# 69 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end

Alola_Poni_TotemBattle_Trigger_6:
# 45 "data/maps/AlolaIsland_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_PONI, Alola_Poni_TotemBattle_Trigger_10
	goto Alola_Poni_TotemBattle_Trigger_5

Alola_Poni_TotemBattle_Trigger_7:
# 45 "data/maps/AlolaIsland_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_ULAULA, Alola_Poni_TotemBattle_Trigger_6
	goto Alola_Poni_TotemBattle_Trigger_5

Alola_Poni_TotemBattle_Trigger_10:
# 45 "data/maps/AlolaIsland_hns/scripts.pory"
	goto_if_set FLAG_CAUGHT_ALL_MELEMELE, Alola_Poni_TotemBattle_Trigger_4
	goto Alola_Poni_TotemBattle_Trigger_5


Alola_Poni_TotemBattle::
# 84 "data/maps/AlolaIsland_hns/scripts.pory"
	lock
# 85 "data/maps/AlolaIsland_hns/scripts.pory"
	faceplayer
# 86 "data/maps/AlolaIsland_hns/scripts.pory"
	playmoncry SPECIES_KOMMO_O, 0
# 87 "data/maps/AlolaIsland_hns/scripts.pory"
	msgbox Alola_Poni_TotemBattle_Text_0, MSGBOX_AUTOCLOSE
# 88 "data/maps/AlolaIsland_hns/scripts.pory"
	waitmoncry
# 90 "data/maps/AlolaIsland_hns/scripts.pory"
	setwildbattle SPECIES_NOIVERN, 60, ITEM_NONE, SPECIES_KOMMO_O_TOTEM, 60, ITEM_OCCA_BERRY
# 91 "data/maps/AlolaIsland_hns/scripts.pory"
	settotemboost B_POSITION_OPPONENT_RIGHT, 1, 1, 1, 1, 1, 1
# 92 "data/maps/AlolaIsland_hns/scripts.pory"
	setflag FLAG_NO_WILD_CATCHING
# 93 "data/maps/AlolaIsland_hns/scripts.pory"
	setflag FLAG_NO_WILD_RUNNING
# 94 "data/maps/AlolaIsland_hns/scripts.pory"
	setflag FLAG_SMART_WILD_AI
# 95 "data/maps/AlolaIsland_hns/scripts.pory"
	dowildbattle
# 96 "data/maps/AlolaIsland_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 97 "data/maps/AlolaIsland_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Poni_TotemBattle_2
# 109 "data/maps/AlolaIsland_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_LOST
	goto_if_eq Alola_Poni_TotemBattle_4
	return

Alola_Poni_TotemBattle_2:
# 98 "data/maps/AlolaIsland_hns/scripts.pory"
	setflag FLAG_HIDE_PONI_TOTEM
# 99 "data/maps/AlolaIsland_hns/scripts.pory"
	setflag FLAG_DEFEATED_PONI_TOTEM
# 100 "data/maps/AlolaIsland_hns/scripts.pory"
	removeobject Poni_Totem
# 101 "data/maps/AlolaIsland_hns/scripts.pory"
	msgbox Alola_Poni_TotemBattle_Text_1, MSGBOX_AUTOCLOSE
# 103 "data/maps/AlolaIsland_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 104 "data/maps/AlolaIsland_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 105 "data/maps/AlolaIsland_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 106 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end

Alola_Poni_TotemBattle_4:
# 110 "data/maps/AlolaIsland_hns/scripts.pory"
	clearflag FLAG_NO_WILD_CATCHING
# 111 "data/maps/AlolaIsland_hns/scripts.pory"
	clearflag FLAG_NO_WILD_RUNNING
# 112 "data/maps/AlolaIsland_hns/scripts.pory"
	clearflag FLAG_SMART_WILD_AI
# 113 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end


Alola_Poni_Totem_sign::
# 119 "data/maps/AlolaIsland_hns/scripts.pory"
	lock
# 120 "data/maps/AlolaIsland_hns/scripts.pory"
	msgbox Alola_Poni_Totem_sign_Text_0, MSGBOX_AUTOCLOSE
# 122 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end


Alola_Poni_TapuFini_Flyover::
# 127 "data/maps/AlolaIsland_hns/scripts.pory"
	goto_if_set FLAG_FLYOVER_TAPU_FINI, Alola_Poni_TapuFini_Flyover_2
# 140 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end

Alola_Poni_TapuFini_Flyover_2:
# 129 "data/maps/AlolaIsland_hns/scripts.pory"
	addobject Poni_Flyover_Tapu
# 130 "data/maps/AlolaIsland_hns/scripts.pory"
	playse SE_M_FLY
# 131 "data/maps/AlolaIsland_hns/scripts.pory"
	applymovement Poni_Flyover_Tapu, Alola_Poni_TapuFini_Flyover_Movement_0
# 132 "data/maps/AlolaIsland_hns/scripts.pory"
	waitmovement 0
# 133 "data/maps/AlolaIsland_hns/scripts.pory"
	removeobject Poni_Flyover_Tapu
# 134 "data/maps/AlolaIsland_hns/scripts.pory"
	clearflag FLAG_FLYOVER_TAPU_FINI
# 135 "data/maps/AlolaIsland_hns/scripts.pory"
	clearflag FLAG_HIDE_TAPU_FINI
# 136 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end


Alola_Poni_BattleVsTapuFini::
# 145 "data/maps/AlolaIsland_hns/scripts.pory"
	lock
# 146 "data/maps/AlolaIsland_hns/scripts.pory"
	faceplayer
# 147 "data/maps/AlolaIsland_hns/scripts.pory"
	playmoncry SPECIES_TAPU_FINI, 0
# 148 "data/maps/AlolaIsland_hns/scripts.pory"
	applymovement Poni_Tapu, Alola_Poni_TotemBattle_Trigger_Movement_0
# 149 "data/maps/AlolaIsland_hns/scripts.pory"
	msgbox Alola_Poni_BattleVsTapuFini_Text_0
# 150 "data/maps/AlolaIsland_hns/scripts.pory"
	waitmovement 0
# 151 "data/maps/AlolaIsland_hns/scripts.pory"
	waitmoncry
# 152 "data/maps/AlolaIsland_hns/scripts.pory"
	setwildbattle SPECIES_TAPU_FINI, 60
# 153 "data/maps/AlolaIsland_hns/scripts.pory"
	dowildbattle
# 154 "data/maps/AlolaIsland_hns/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 155 "data/maps/AlolaIsland_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Poni_BattleVsTapuFini_2
# 162 "data/maps/AlolaIsland_hns/scripts.pory"
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Poni_BattleVsTapuFini_3
# 170 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end

# 173 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end

Alola_Poni_BattleVsTapuFini_2:
# 156 "data/maps/AlolaIsland_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_FINI
# 157 "data/maps/AlolaIsland_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_FINI
# 158 "data/maps/AlolaIsland_hns/scripts.pory"
	removeobject Poni_Tapu
# 159 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end

Alola_Poni_BattleVsTapuFini_3:
# 163 "data/maps/AlolaIsland_hns/scripts.pory"
	setflag FLAG_HIDE_TAPU_FINI
# 164 "data/maps/AlolaIsland_hns/scripts.pory"
	setflag FLAG_BATTLED_TAPU_FINI
# 165 "data/maps/AlolaIsland_hns/scripts.pory"
	removeobject Poni_Tapu
# 166 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end


Alola_Poni_TrainerBattleSwimmer1::
# 178 "data/maps/AlolaIsland_hns/scripts.pory"
	trainerbattle_single TRAINER_PONI_SWIMMER_1_HNS, Alola_Poni_TrainerBattleSwimmer1_Text_0, Alola_Poni_TrainerBattleSwimmer1_Text_1
# 179 "data/maps/AlolaIsland_hns/scripts.pory"
	msgbox Alola_Poni_TrainerBattleSwimmer1_Text_2, MSGBOX_AUTOCLOSE
# 181 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end


Alola_Poni_TrainerBattleSwimmer2::
# 186 "data/maps/AlolaIsland_hns/scripts.pory"
	trainerbattle_single TRAINER_PONI_SWIMMER_2_HNS, Alola_Poni_TrainerBattleSwimmer2_Text_0, Alola_Poni_TrainerBattleSwimmer2_Text_1
# 187 "data/maps/AlolaIsland_hns/scripts.pory"
	msgbox Alola_Poni_TrainerBattleSwimmer2_Text_2, MSGBOX_AUTOCLOSE
# 189 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end


Alola_Poni_NPC_girl::
# 194 "data/maps/AlolaIsland_hns/scripts.pory"
	lock
# 195 "data/maps/AlolaIsland_hns/scripts.pory"
	faceplayer
# 196 "data/maps/AlolaIsland_hns/scripts.pory"
	msgbox Alola_Poni_NPC_girl_Text_0, MSGBOX_AUTOCLOSE
# 198 "data/maps/AlolaIsland_hns/scripts.pory"
	release
	end


# 65 "data/maps/AlolaIsland_hns/scripts.pory"
Alola_Poni_TotemBattle_Trigger_Movement_0:
# 65 "data/maps/AlolaIsland_hns/scripts.pory"
	walk_in_place_down
# 65 "data/maps/AlolaIsland_hns/scripts.pory"
	walk_in_place_down
	step_end

# 131 "data/maps/AlolaIsland_hns/scripts.pory"
Alola_Poni_TapuFini_Flyover_Movement_0:
# 131 "data/maps/AlolaIsland_hns/scripts.pory"
	walk_faster_up
# 131 "data/maps/AlolaIsland_hns/scripts.pory"
	walk_faster_up
# 131 "data/maps/AlolaIsland_hns/scripts.pory"
	walk_faster_up
# 131 "data/maps/AlolaIsland_hns/scripts.pory"
	walk_faster_up
# 131 "data/maps/AlolaIsland_hns/scripts.pory"
	walk_faster_up
# 131 "data/maps/AlolaIsland_hns/scripts.pory"
	walk_faster_up
# 131 "data/maps/AlolaIsland_hns/scripts.pory"
	walk_faster_up
# 131 "data/maps/AlolaIsland_hns/scripts.pory"
	walk_faster_up
# 131 "data/maps/AlolaIsland_hns/scripts.pory"
	walk_faster_up
# 131 "data/maps/AlolaIsland_hns/scripts.pory"
	walk_faster_up
# 131 "data/maps/AlolaIsland_hns/scripts.pory"
	walk_faster_up
# 131 "data/maps/AlolaIsland_hns/scripts.pory"
	walk_faster_up
# 131 "data/maps/AlolaIsland_hns/scripts.pory"
	walk_faster_up
	step_end

Alola_Poni_BattleExeggutor_Text_0:
# 10 "data/maps/AlolaIsland_hns/scripts.pory"
	.string "Gaah-aah!$"

Alola_Poni_Island_Sign_Text_0:
# 37 "data/maps/AlolaIsland_hns/scripts.pory"
	.string "Poni Isle$"

Alola_Poni_TotemBattle_Text_0:
# 87 "data/maps/AlolaIsland_hns/scripts.pory"
	.string "Thhhh!$"

Alola_Poni_TotemBattle_Text_1:
# 101 "data/maps/AlolaIsland_hns/scripts.pory"
	.string "Totem Kommo-o was defeated!\n"
	.string "It scampered off somewhere…$"

Alola_Poni_Totem_sign_Text_0:
# 120 "data/maps/AlolaIsland_hns/scripts.pory"
	.string "A strange totem stands here,\n"
	.string "power is emanating from it…$"

Alola_Poni_BattleVsTapuFini_Text_0:
# 149 "data/maps/AlolaIsland_hns/scripts.pory"
	.string "Fiiin!$"

Alola_Poni_TrainerBattleSwimmer1_Text_0:
# 178 "data/maps/AlolaIsland_hns/scripts.pory"
	.string "Warmer water, no problem!$"

Alola_Poni_TrainerBattleSwimmer1_Text_1:
# 178 "data/maps/AlolaIsland_hns/scripts.pory"
	.string "Gah, I forgot my sunscreen…$"

Alola_Poni_TrainerBattleSwimmer1_Text_2:
# 179 "data/maps/AlolaIsland_hns/scripts.pory"
	.string "I've swam into so many cool Pokémon!\n"
	.string "It must be something in the water.$"

Alola_Poni_TrainerBattleSwimmer2_Text_0:
# 186 "data/maps/AlolaIsland_hns/scripts.pory"
	.string "Hey, don't block my current!$"

Alola_Poni_TrainerBattleSwimmer2_Text_1:
# 186 "data/maps/AlolaIsland_hns/scripts.pory"
	.string "Ugh, fine,\njust let me swim…$"

Alola_Poni_TrainerBattleSwimmer2_Text_2:
# 187 "data/maps/AlolaIsland_hns/scripts.pory"
	.string "The current is great for tubing.\n"
	.string "I don't think I'll tube anywhere else!$"

Alola_Poni_NPC_girl_Text_0:
# 196 "data/maps/AlolaIsland_hns/scripts.pory"
	.string "Poni Isle is my favorite.\n"
	.string "The wilderness just speaks for itself!$"
