Route4_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route4_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route4_OnTransition: 
	callnative SetTimeBasedEncounters
	end

Route4_EventScript_HpUp::
	finditem ITEM_HP_UP
	end

Route4_EventScript_UltraBall::
	finditem ITEM_ULTRA_BALL
	end

Route4_EventScript_Hank::
	trainerbattle_single TRAINER_HANK_HNS, Route4_Text_BirdKeeperHank_Seen, Route4_Text_BirdKeeperHank_Beaten
	msgbox Route4_Text_BirdKeeperHank_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route4_EventScript_Hope::
	trainerbattle_single TRAINER_HOPE_HNS, Route4_Text_PicnickerHope_Seen, Route4_Text_PicnickerHope_Beaten
	msgbox Route4_Text_PicnickerHope_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route4_EventScript_Sharon::
	trainerbattle_single TRAINER_SHARON_HNS, Route4_Text_PicnickerSharon_Seen, Route4_Text_PicnickerSharon_Beaten
	msgbox Route4_Text_PicnickerSharon_AfterBattle, MSGBOX_AUTOCLOSE
	end

Route4_EventScript_Sign::
	msgbox Route4_Text_MtMoonSquareSign, MSGBOX_SIGN
	end

Route4_Text_BirdKeeperHank_Seen:
	.string "אני מגדל את הפוקימונים שלי.\n"
	.string "רוצה להילחם איתי?$"

Route4_Text_BirdKeeperHank_Beaten:
	.string "אוף! את זה הפסדתי…$"

Route4_Text_BirdKeeperHank_AfterBattle:
	.string "אם יש פוקימון מסוים שרוצים לגדל,\n"
	.string "שולחים אותו ראשון ומחליפים אותו מיד.\p"
	.string "ככה עושים את זה.$"

Route4_Text_PicnickerHope_Seen:
	.string "יש לי הרגשה שאני יכולה לנצח.\p"
	.string "נראה אם אני צודקת!$"

Route4_Text_PicnickerHope_Beaten:
	.string "אוי, אתה חזק מדי.$"

Route4_Text_PicnickerHope_AfterBattle:
	.string "שמעתי שקלפרי מופיעים בהר הירח.\p"
	.string "אבל איפה הם יכולים להיות?$"

Route4_Text_PicnickerSharon_Seen:
	.string "אממ…\n"
	.string "אני…$"

Route4_Text_PicnickerSharon_Beaten:
	.string "…$"

Route4_Text_PicnickerSharon_AfterBattle:
	.string "……אלך להתאמן עוד קצת…$"

Route4_Text_MtMoonSquareSign:
	.string "כניסה חדשה להר הירח\n"
	.string "עקב מפולת\p"
	.string "היזהרו בצעדיכם$"

