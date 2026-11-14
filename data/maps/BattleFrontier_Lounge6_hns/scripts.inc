BattleFrontier_Lounge6_hns_MapScripts::
	.byte 0

BattleFrontier_Lounge6_EventScript_Trader_hns::
	lock
	faceplayer
	goto_if_set FLAG_BATTLE_FRONTIER_TRADE_DONE, BattleFrontier_Lounge6_EventScript_TradeCompleted_hns
	ingame_trade INGAME_TRADE_MEOWTH, BattleFrontier_Lounge6_Text_WouldYouLikeToTrade_hns, BattleFrontier_Lounge6_EventScript_DeclineTrade_hns, BattleFrontier_Lounge6_EventScript_NotRequestedMon_hns, BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt_hns
	setflag FLAG_BATTLE_FRONTIER_TRADE_DONE
	release
	end

BattleFrontier_Lounge6_EventScript_DeclineTrade_hns::
	msgbox BattleFrontier_Lounge6_Text_WellThatsFineToo_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_NotRequestedMon_hns::
	bufferspeciesname STR_VAR_1, VAR_0x8009
	msgbox BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_EventScript_TradeCompleted_hns::
	msgbox BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge6_Text_WouldYouLikeToTrade_hns:
	.string "הפוקימון שלי הוא {STR_VAR_2}.\n"
	.string "מכיר אותו?\p"
	.string "הוא ממש חמוד, וגם די נחמד.\n"
	.string "את הקטן הזה אני מציעה להחלפה בגאווה!\p"
	.string "תרצה לתת לי {STR_VAR_1}\n"
	.string "תמורת ה{STR_VAR_2} שלי?$"

BattleFrontier_Lounge6_Text_PromiseIllBeGoodToIt_hns:
	.string "אוי, הוא מקסים! תודה!\n"
	.string "אני מבטיחה שאהיה טובה אליו!\p"
	.string "אה! ואני מקווה שגם ל{STR_VAR_2}\n"
	.string "שלי יהיה טוב אצלך!$"

BattleFrontier_Lounge6_Text_DontTradeForAnythingButMon_hns:
	.string "אוי, סליחה! אני מוכנה להחליף\n"
	.string "רק תמורת {STR_VAR_1}.$"

BattleFrontier_Lounge6_Text_WellThatsFineToo_hns:
	.string "אה, לא? טוב, גם זה בסדר.\n"
	.string "נשמח לראות אותך שוב.$"

BattleFrontier_Lounge6_Text_SkittySoMuchCuterThanImagined_hns:
	.string "חי-חי! סקיטי הרבה יותר חמוד ממה\n"
	.string "שדמיינתי. אני כל כך שמחה!$"
