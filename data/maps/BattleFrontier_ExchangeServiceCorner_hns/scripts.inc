BattleFrontier_ExchangeServiceCorner_hns_MapScripts::
	.byte 0

BattleFrontier_ExchangeServiceCorner_EventScript_DecorClerk1_hns::
	lock
	faceplayer
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize_hns, MSGBOX_DEFAULT
	special CreateBPDecorShop1
	waitstate
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_DecorClerk2_hns::
	lock
	faceplayer
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize_hns, MSGBOX_DEFAULT
	special CreateBPDecorShop2
	waitstate
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_VitaminClerk_hns::
	lock
	faceplayer
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize_hns, MSGBOX_DEFAULT
	special CreateBPVitaminShop
	waitstate
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_HoldItemClerk_hns::
	lock
	faceplayer
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize_hns, MSGBOX_DEFAULT
	special CreateBPHoldItemShop
	waitstate
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_PokeBallClerk_hns::
	lock
	faceplayer
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize_hns, MSGBOX_DEFAULT
	special CreateBPPokeBallShop
	waitstate
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_HoldItemClerk2_hns::
	lock
	faceplayer
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize_hns, MSGBOX_DEFAULT
	special CreateBPHoldItemShop2
	waitstate
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_PowerClerk_hns::
	lock
	faceplayer
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize_hns, MSGBOX_DEFAULT
	special CreateBPPowerShop
	waitstate
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Man_hns::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_GoGetYourOwnDoll_hns, MSGBOX_NPC
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Sailor_hns::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_ItemsWillGetMonTougher_hns, MSGBOX_NPC
	end

BattleFrontier_ExchangeServiceCorner_EventScript_PokefanF_hns::
	lock
	msgbox BattleFrontier_ExchangeServiceCorner_Text_GetYouAnythingYouWant_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_ExchangeServiceCorner_EventScript_RichBoy_hns::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_WishIHadAllDolls_hns, MSGBOX_NPC
	end

BattleFrontier_ExchangeServiceCorner_EventScript_Girl_hns::
	msgbox BattleFrontier_ExchangeServiceCorner_Text_MoreBattlePointsForRecord_hns, MSGBOX_NPC
	end

BattleFrontier_ExchangeServiceCorner_Text_WelcomePleaseChoosePrize_hns:
	.string "שלום, כאן פינת שירות\n"
	.string "ההמרה.\p"
	.string "אנחנו ממירים את נקודות הקרב\n"
	.string "שצברת בפרסים נהדרים.\p"
	.string "אפשר לבחור פרס מהרשימה הזאת.$"

BattleFrontier_ExchangeServiceCorner_Text_WishIHadAllDolls_hns:
	.string "וואו, הם כל כך יפים!\n"
	.string "הלוואי שהיו לי!\p"
	.string "כריות חמודות!\n"
	.string "בובות פרווה גדולות!\p"
	.string "בובות פרווה קטנות!\n"
	.string "הלוואי שכולם היו שלי!$"

BattleFrontier_ExchangeServiceCorner_Text_GetYouAnythingYouWant_hns:
	.string "תסמוך על אמא!\p"
	.string "כל מה שתרצה, אעשה הכול\n"
	.string "כדי להשיג לך אותו, מתוק!$"

BattleFrontier_ExchangeServiceCorner_Text_ItemsWillGetMonTougher_hns:
	.string "אם אשיג את הפריטים שיש כאן,\n"
	.string "הפוקימונים שלי יתחזקו.\p"
	.string "בטח שהם יתחזקו!\n"
	.string "אין בכלל ספק!$"

BattleFrontier_ExchangeServiceCorner_Text_GoGetYourOwnDoll_hns:
	.string "האא?\n"
	.string "מה אתה בוהה?\p"
	.string "אני לא אוהב שאתה נועץ ככה עיניים\n"
	.string "בבובת הפרווה שלי.\p"
	.string "אם אתה רוצה כזאת, לך תשיג לעצמך!\n"
	.string "נכון, סמוצ'ום?$"

BattleFrontier_ExchangeServiceCorner_Text_MoreBattlePointsForRecord_hns:
	.string "ידעת?\p"
	.string "אם מאריכים את רצף הניצחונות באחד\n"
	.string "ממתקני הקרב, מתחילים לקבל\p"
	.string "יותר ויותר נקודות קרב.$"
