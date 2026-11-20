Route46_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route29_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route46_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route46_EventScript_Bailey::
	trainerbattle_single TRAINER_BAILEY_HNS, Route46_Text_HikerBaileySeen, Route46_Text_HikerBaileyBeaten
	msgbox Route46_Text_HikerBaileyAfterBattle, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_Ted::
	trainerbattle_single TRAINER_TED_HNS, Route46_Text_CamperTedSeen, Route46_Text_CamperTedBeaten
	msgbox Route46_Text_CamperTedAfterBattle, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_Erin::
	trainerbattle_single TRAINER_ERIN_HNS, Route46_Text_PicnickerErinSeen, Route46_Text_PicnickerErinBeaten, Route46_EventScript_RegisterErin
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route46_EventScript_RematchErin
	msgbox Route46_Text_PicnickerErinAfterBattle, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_RegisterErin::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route46_Text_ErinRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ERIN_HNS
	release
	end

Route46_EventScript_RematchErin::
	trainerbattle_rematch TRAINER_ERIN_HNS, Route46_Text_ErinRematchIntro, Route46_Text_ErinRematchDefeat
	msgbox Route46_Text_ErinPostRematch, MSGBOX_AUTOCLOSE
	end

Route46_EventScript_Sign::
	lock
	msgbox Route46_Text_Sign, MSGBOX_SIGN
	closemessage
	release
	end

Route46_EventScript_Item_Revive::
	finditem ITEM_REVIVE
	end

Route46_Text_HikerBaileySeen:
	.string "קדימה! אראה לך את\n"
	.string "הכוח של פוקימוני ההרים!$"

Route46_Text_HikerBaileyBeaten:
	.string "רחם עליי!\n"
	.string "הראית לי את הכוח שלך!$"

Route46_Text_HikerBaileyAfterBattle:
	.string "נגמר. לא אכפת לי.\n"
	.string "ככה זה אצלנו, המטיילים.$"

Route46_Text_CamperTedSeen:
	.string "גם אני מגדל פוקימונים!\p"
	.string "תילחם איתי?$"

Route46_Text_CamperTedBeaten:
	.string "מה…?$"

Route46_Text_CamperTedAfterBattle:
	.string "עשיתי כמיטב יכולתי,\n"
	.string "אבל זה לא הספיק.\p"
	.string "בלי תירוצים -\n"
	.string "אני מודה שהפסדתי.$"

Route46_Text_PicnickerErinSeen:
	.string "גם אני מגדלת פוקימונים!\p"
	.string "תילחם איתי?$"

Route46_Text_PicnickerErinBeaten:
	.string "אוף, חבל!$"

Route46_Text_PicnickerErinAfterBattle:
	.string "הייתי בהרבה מכונים,\n"
	.string "אבל המכון בגולדנרוד הכי אהוב עליי.\p"
	.string "הוא מלא בפרחים יפים!$"

Route46_Text_ErinRegister:
	.string "הייתי בהרבה מכונים,\n"
	.string "אבל המכון בגולדנרוד הכי אהוב עליי.\p"
	.string "הוא מלא בפרחים יפים!$"

Route46_Text_ErinRematchIntro:
	.string "גם אני מגדלת פוקימונים!\p"
	.string "תילחם איתי?$"

Route46_Text_ErinRematchDefeat:
	.string "אוף, חבל!$"

Route46_Text_ErinPostRematch:
	.string "הייתי בהרבה מכונים,\n"
	.string "אבל המכון בגולדנרוד הכי אהוב עליי.\p"
	.string "הוא מלא בפרחים יפים!$"

Route46_Text_PicnickerErin2Beaten:
	.string "Aww… I keep losing all the time!\p"
	.string "I'll just have to try harder!\n"
	.string "Anyway, thanks for battling\n"
	.string "me again and again.\p"
	.string "Here's that present from the\n"
	.string "other time.$"

Route46_Text_Sign:
	.string "דרך 46\n"
	.string "בהמשך: דרך הררית$"
