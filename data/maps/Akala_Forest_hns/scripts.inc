Akala_Forest_hns_MapScripts::
	.byte 0


Alola_Akala_Forest_FindItem1::
	finditem ITEM_FULL_RESTORE, 1
	end


Alola_Akala_Forest_FindItem2::
	finditem ITEM_PP_UP, 1
	end


Alola_AkalaForest_TrainerBattleBugCatcher1::
	trainerbattle_single TRAINER_AKALA_FOREST_BUGCATCHER_1_HNS, Alola_AkalaForest_TrainerBattleBugCatcher1_Text_0, Alola_AkalaForest_TrainerBattleBugCatcher1_Text_1
	msgbox Alola_AkalaForest_TrainerBattleBugCatcher1_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_AkalaForest_TrainerBattleBugCatcher2::
	trainerbattle_single TRAINER_AKALA_FOREST_BUGCATCHER_2_HNS, Alola_AkalaForest_TrainerBattleBugCatcher2_Text_0, Alola_AkalaForest_TrainerBattleBugCatcher2_Text_1
	msgbox Alola_AkalaForest_TrainerBattleBugCatcher2_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_Akala_BattleRaichu::
	lock
	faceplayer
	setflag FLAG_BATTLED_RAICHU
	playmoncry SPECIES_RAICHU_ALOLA, 0
	msgbox Alola_Akala_BattleRaichu_Text_0, MSGBOX_AUTOCLOSE
	waitmoncry
	setwildbattle SPECIES_RAICHU_ALOLA, 60
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Akala_BattleRaichu_2
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Akala_BattleRaichu_3
	release
	end

	release
	end

Alola_Akala_BattleRaichu_2:
	setflag FLAG_HIDE_RAICHU_ALOLA
	removeobject LOCALID_AKALA_RAICHU
	release
	end

Alola_Akala_BattleRaichu_3:
	setflag FLAG_HIDE_RAICHU_ALOLA
	removeobject LOCALID_AKALA_RAICHU
	release
	end


Alola_AkalaForest_TrainerBattleBugCatcher1_Text_0:
	.string "תראה כמה חרקים מגניבים\n"
	.string "יש כאן באיים!$"

Alola_AkalaForest_TrainerBattleBugCatcher1_Text_1:
	.string "איי, זה עקץ!$"

Alola_AkalaForest_TrainerBattleBugCatcher1_Text_2:
	.string "האיים רחוקים מכל יבשה אחרת, אז\n"
	.string "פוקימוני החרק כאן בטח הסתגלו לסביבה.$"

Alola_AkalaForest_TrainerBattleBugCatcher2_Text_0:
	.string "תראה מה תפסתי!$"

Alola_AkalaForest_TrainerBattleBugCatcher2_Text_1:
	.string "אוף, איזו עקיצה!$"

Alola_AkalaForest_TrainerBattleBugCatcher2_Text_2:
	.string "האקלים באיי אלולה\n"
	.string "קצת שונה…\p"
	.string "אני בטוח שבגלל זה יש כאן כמה\n"
	.string "פוקימוני חרק ייחודיים.$"


Alola_Akala_BattleRaichu_Text_0:
	.string "גאאאה!$"

