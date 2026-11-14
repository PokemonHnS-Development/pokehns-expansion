Route39_FarmHouse_hns_MapScripts::
	.byte 0


Route39House_EventScript_FarmerF::
	lock
	faceplayer
	goto_if_eq VAR_ROUTE39_BARN, 5, Route39House_EventScript_FarmerFAfter
	msgbox Route39_Text_FarmerFInTrouble, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39House_EventScript_FarmerFAfter::
	goto_if_set FLAG_GOT_TM_SNATCH, Route39House_EventScript_FarmerFAfterTM
	msgbox Route39_Text_FarmerFHealedMiltank, MSGBOX_DEFAULT
	giveitem ITEM_TM_SNATCH
	msgbox Route39_Text_FarmerFSnatchSpeech, MSGBOX_DEFAULT
	closemessage 
	setflag FLAG_GOT_TM_SNATCH
	release
	end

Route39House_EventScript_FarmerFAfterTM::
	msgbox Route39_Text_FarmerFSnatchSpeech, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39_FarmHouse_EventScript_FarmerM::
	lock
	faceplayer
	goto_if_lt VAR_ROUTE39_BARN, 5, Route39_FarmHouse_EventScript_FarmerM_Sick
	showmoneybox 0, 0
	msgbox Route39_Text_FarmerMBuyMilk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route39_FarmHouse_EventScript_FarmerMBuyMilk
	msgbox Route39_Text_FarmerMNoSale, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	end

Route39_FarmHouse_EventScript_FarmerMBuyMilk::
	checkmoney 500, 0
	goto_if_eq VAR_RESULT, FALSE, Route39_FarmHouse_EventScript_FarmerM_NotEnough
	additem ITEM_MOOMOO_MILK
	goto_if_eq VAR_RESULT, FALSE, Route39_FarmHouse_EventScript_FarmerM_BagFull
	removemoney 500
	updatemoneybox 0
	msgbox Route39FarmHouse_Text_WouldYouLikeAnother, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route39_FarmHouse_EventScript_FarmerMBuyMilk

	
	msgbox Route39_Text_FarmerMGotMilk, MSGBOX_DEFAULT
	closemessage
	playse MUS_OBTAIN_ITEM
	msgbox Route39_Text_GotMilk, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

Route39_FarmHouse_EventScript_FarmerM_Sick::
	msgbox Route39_Text_FarmerMSickCow, MSGBOX_DEFAULT
	closemessage
	release
	end

Route39_FarmHouse_EventScript_FarmerM_BagFull::
	msgbox Route39_Text_FarmerMNoRoom, MSGBOX_DEFAULT
	hidemoneybox
	closemessage
	release
	end

Route39_FarmHouse_EventScript_FarmerM_NotEnough::
	msgbox Route39_Text_FarmerMNoMoney, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

Route39_Text_FarmerMSickCow:
	.string "המילטנק שלי כבר לא נותן לי חלב.\p"
	.string "לחווה הזאת פה יש חלב מפורסם.\p"
	.string "כמעט כולם רוצים לשתות ממנו.\p"
	.string "אם אאכיל אותו בהמון פירות,\n"
	.string "הוא ייתן לי המון חלב, נראה לי.$"

Route39_Text_FarmerMBuyMilk:
	.string "רוצה קצת מחלב המומו שלי?\p"
	.string "הוא הגאווה והתפארת שלי, כן.\p"
	.string "תן אותו לפוקימונים כדי להחזיר להם נ”ח!\p"
	.string "אתן לך אותו תמורת ¥500 בלבד.$"

Route39_Text_FarmerMGotMilk:
	.string "הנה לך! תשתה ותיהנה!$"

Route39_Text_FarmerMNoMoney:
	.string "סליחה, חבר. אין כסף, אין עסקה!$"

Route39_Text_FarmerMNoRoom:
	.string "נראה לי שהתיק שלך מלא.$"

Route39_Text_FarmerMNoSale:
	.string "לא רוצה? תבוא שוב, טוב?$"

Route39FarmHouse_Text_WouldYouLikeAnother:
	.string "מה דעתך על עוד בקבוק?$"

Route39_Text_GotMilk:
	.string "{PLAYER} קיבל חלב מומו.$"

Route39_Text_FarmerMMilking:
	.string "I best go do my milkin'.$"

Route39_Text_FarmerFInTrouble:
	.string "החלב שלנו נשלח אפילו לקאנטו.\p"
	.string "אז אם המילטנק שלנו\n"
	.string "לא ייתן לנו חלב, אנחנו בצרות.$"

Route39_Text_FarmerFHealedMiltank:
	.string "ריפאת את המילטנק שלנו, מותק.\n"
	.string "עכשיו הוא שוב נותן חלב מומו.\p"
	.string "הנה משהו על הטרחה.$"

Route39_Text_FarmerFSnatchSpeech:
	.string "זה המהלך חטיפה.\p"
	.string "זה מהלך ערמומי שמאפשר לפוקימון\n"
	.string "לגנוב מהלך של יריב רגע לפני השימוש בו.\p"
	.string "אם כמה פוקימונים משתמשים בחטיפה,\n"
	.string "רק האיטי מביניהם יגנוב בסוף את המהלך.\p"
	.string "תשתמש בו בחוכמה, מותק.\n"
	.string "התזמון הוא הכול.$"
