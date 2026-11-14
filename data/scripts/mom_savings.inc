EventScript_MomGiftCall_Item::
	lockall
	pokenavcall Mom_Text_GiftCall_Item
	waitmessage
	delay 30
	clearflag FLAG_MOM_HAS_GIFT
	releaseall
	end

EventScript_MomGiftCall_Berry::
	lockall
	pokenavcall Mom_Text_GiftCall_Berry
	waitmessage
	delay 30
	clearflag FLAG_MOM_HAS_GIFT
	releaseall
	end

EventScript_MomGiftCall_Decoration::
	lockall
	pokenavcall Mom_Text_GiftCall_Decoration
	waitmessage
	delay 30
	clearflag FLAG_MOM_HAS_GIFT
	releaseall
	end

Mom_Text_GiftCall_Item:
	.string "אמא: היי, מותק!\p"
	.string "קניתי לך משהו נחמד\n"
	.string "מהחיסכון שלך!\p"
	.string "שלחתי אותו למחשב שלך.\n"
	.string "תשמור על עצמך!$"

Mom_Text_GiftCall_Berry:
	.string "אמא: היי, מותק!\p"
	.string "מצאתי לך בחנות\n"
	.string "כמה פירות נחמדים!\p"
	.string "שלחתי אותם למחשב שלך.\n"
	.string "תשמור על עצמך!$"

Mom_Text_GiftCall_Decoration:
	.string "אמא: היי, מותק!\p"
	.string "קניתי בובת פוקימון\n"
	.string "חמודה לחדר שלך!\p"
	.string "כשתחזור הביתה, תבדוק את\n"
	.string "הקישוטים שלך. תשמור על עצמך!$"
