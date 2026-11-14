UnionCave_B2F_hns_MapScripts::
	.byte 0

UnionCave_B2F_EventScript_CooltrainerNick::
	trainerbattle_single TRAINER_NICK_HNS, UnionCave_B2F_Text_CooltrainermNickSeen, UnionCave_B2F_Text_CooltrainermNickBeaten
	msgbox UnionCave_B2F_Text_CooltrainermNickAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B2F_EventScript_CooltrainerfGwen::
	trainerbattle_single TRAINER_GWEN_HNS, UnionCave_B2F_Text_CooltrainerfGwenSeen, UnionCave_B2F_Text_CooltrainerfGwenBeaten
	msgbox UnionCave_B2F_Text_CooltrainerfGwenAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B2F_EventScript_CooltrainerfEmma::
	trainerbattle_single TRAINER_EMMA_HNS, UnionCave_B2F_Text_CooltrainerfEmmaSeen, UnionCave_B2F_Text_CooltrainerfEmmaBeaten
	msgbox UnionCave_B2F_Text_CooltrainerfEmmaAfter, MSGBOX_AUTOCLOSE
	end

UnionCave_B2F_EventScript_Lapras::
	lock
	faceplayer
	playmoncry SPECIES_LAPRAS, CRY_MODE_ENCOUNTER
	waitmoncry
	setwildbattle SPECIES_LAPRAS, 20
	dowildbattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, UnionCave_B2F_EventScript_LaprasRan
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_UNION_CAVE_LAPRAS
	setflag FLAG_HIDE_UNION_CAVE_LAPRAS
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

UnionCave_B2F_EventScript_LaprasRan::
	release
	end


UnionCave_B2F_EventScript_Item_Ether::
	finditem ITEM_ETHER
	end

UnionCave_B2F_EventScript_Item_HyperPotion::
	finditem ITEM_HYPER_POTION
	end

UnionCave_B2F_EventScript_Item_MaxRevive::
	finditem ITEM_MAX_REVIVE
	end

UnionCave_B2F_Text_CooltrainermNickSeen:
	.string "יש שני סוגים של אנשים.\p"
	.string "אלה שיש להם סטייל, ואלה\n"
	.string "שאין להם.\p"
	.string "לאיזה סוג אתה שייך?$"

UnionCave_B2F_Text_CooltrainermNickBeaten:
	.string "יש לך סטייל מסנוור!$"

UnionCave_B2F_Text_CooltrainermNickAfter:
	.string "הסטייל שלך עם פוקימונים מהמם\n"
	.string "וצבעוני, אני מודה.\p"
	.string "אתה רק תמשיך להשתפר!$"

UnionCave_B2F_Text_CooltrainerfGwenSeen:
	.string "אני באימונים. מתחשק לך סיבוב?$"

UnionCave_B2F_Text_CooltrainerfGwenBeaten:
	.string "אוף, לא! אתה טוב מדי בשבילי.$"

UnionCave_B2F_Text_CooltrainerfGwenAfter:
	.string "אני אתאמן לבד עד שאשתפר.$"

UnionCave_B2F_Text_CooltrainerfEmmaSeen:
	.string "הייתי הולכת לכל מקום\n"
	.string "שיש בו פוקימון שאני אוהבת.\p"
	.string "ככה עושה מאמן אמיתי.$"

UnionCave_B2F_Text_CooltrainerfEmmaBeaten:
	.string "הייתי מעדיפה ללטף את המתוקים שלי\n"
	.string "במקום זה!$"

UnionCave_B2F_Text_CooltrainerfEmmaAfter:
	.string "רק פעם בשבוע, פוקימון אחד מגיע\n"
	.string "לשפת המים.\p"
	.string "רציתי לראות את הפוקימון הזה…$"
