Akala_Cave_hns_MapScripts::
	.byte 0


Alola_Melemele_BattleMarowak::
	lock
	faceplayer
	setflag FLAG_BATTLED_MAROWAK
	playmoncry SPECIES_MAROWAK_ALOLA, 0
	msgbox Alola_Melemele_BattleMarowak_Text_0, MSGBOX_AUTOCLOSE
	waitmoncry
	setwildbattle SPECIES_MAROWAK_ALOLA, 60
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Melemele_BattleMarowak_2
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Melemele_BattleMarowak_3
	release
	end

	release
	end

Alola_Melemele_BattleMarowak_2:
	setflag FLAG_HIDE_MAROWAK_ALOLA
	removeobject Alola_Melemele_Marowak
	release
	end

Alola_Melemele_BattleMarowak_3:
	setflag FLAG_HIDE_MAROWAK_ALOLA
	removeobject Alola_Melemele_Marowak
	release
	end


Alola_Melemele_BattleDugtrio::
	lock
	faceplayer
	setflag FLAG_BATTLED_DUGTRIO
	playmoncry SPECIES_DUGTRIO_ALOLA, 0
	msgbox Alola_Melemele_BattleDugtrio_Text_0, MSGBOX_AUTOCLOSE
	waitmoncry
	setwildbattle SPECIES_DUGTRIO_ALOLA, 60
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_eq Alola_Melemele_BattleDugtrio_2
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq Alola_Melemele_BattleDugtrio_3
	release
	end

	release
	end

Alola_Melemele_BattleDugtrio_2:
	setflag FLAG_HIDE_DUGTRIO_ALOLA
	removeobject Alola_Melemele_Dugtrio
	release
	end

Alola_Melemele_BattleDugtrio_3:
	setflag FLAG_HIDE_DUGTRIO_ALOLA
	removeobject Alola_Melemele_Dugtrio
	release
	end


Alola_Akala_Cave_FindItem1::
	finditem ITEM_CARBOS, 1
	end


Alola_Akala_Cave_FindItem2::
	finditem ITEM_HP_UP, 1
	end


Alola_AkalaCave_TrainerBattleHiker::
	trainerbattle_single TRAINER_AKALA_CAVE_HIKER_HNS, Alola_AkalaCave_TrainerBattleHiker_Text_0, Alola_AkalaCave_TrainerBattleHiker_Text_1
	msgbox Alola_AkalaCave_TrainerBattleHiker_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_AkalaCave_TrainerBattlePicnicker::
	trainerbattle_single TRAINER_AKALA_CAVE_PICNICKER_HNS, Alola_AkalaCave_TrainerBattlePicnicker_Text_0, Alola_AkalaCave_TrainerBattlePicnicker_Text_1
	msgbox Alola_AkalaCave_TrainerBattlePicnicker_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_AkalaCave_TrainerBattleCamper::
	trainerbattle_single TRAINER_AKALA_CAVE_CAMPER_HNS, Alola_AkalaCave_TrainerBattleCamper_Text_0, Alola_AkalaCave_TrainerBattleCamper_Text_1
	msgbox Alola_AkalaCave_TrainerBattleCamper_Text_2, MSGBOX_AUTOCLOSE
	release
	end


Alola_Melemele_BattleMarowak_Text_0:
	.string "ראאה!$"

Alola_Melemele_BattleDugtrio_Text_0:
	.string "צ'ה-צ'ה!$"

Alola_AkalaCave_TrainerBattleHiker_Text_0:
	.string "אתה בטח קשוח אם הצלחת לטפס\n"
	.string "עד לכאן!$"

Alola_AkalaCave_TrainerBattleHiker_Text_1:
	.string "קשוח יותר ממני!$"

Alola_AkalaCave_TrainerBattleHiker_Text_2:
	.string "נאלצתי להפסיק לטפס כי\n"
	.string "נהיה חם מדי.\p"
	.string "זה כאילו מישהו הדליק מדורה\n"
	.string "למעלה על הפסגה…$"

Alola_AkalaCave_TrainerBattlePicnicker_Text_0:
	.string "אני עייפה מכל ההליכה הזאת,\n"
	.string "בוא נילחם!$"

Alola_AkalaCave_TrainerBattlePicnicker_Text_1:
	.string "טוב, זה היה מרענן!$"

Alola_AkalaCave_TrainerBattlePicnicker_Text_2:
	.string "בדרך כלל אני לא כל כך עייפה,\n"
	.string "אבל החום במערה הזאת מתיש!$"

Alola_AkalaCave_TrainerBattleCamper_Text_0:
	.string "תסתכל עליי!\n"
	.string "תפסתי כמה פוקימונים חזקים!$"

Alola_AkalaCave_TrainerBattleCamper_Text_1:
	.string "לא רע,\n"
	.string "אבל לא מספיק טוב!$"

Alola_AkalaCave_TrainerBattleCamper_Text_2:
	.string "חם פה, או שרק לי חם?$"
