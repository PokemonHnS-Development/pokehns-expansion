GoldenrodCity_BikeShop_hns_MapScripts::
	.byte 0

GoldenrodCity_BikeShop_EventScript_Clerk::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_BIKE, GoldenrodCity_BikeShop_EventScript_Clerk_BikeReceived
	msgbox GoldenrodCity_BikeShop_Text_ClerkIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, GoldenrodCity_BikeShop_EventScript_Clerk_BikeAgreed
	msgbox GoldenrodCity_BikeShop_Text_Refused, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Clerk_BikeAgreed::
	msgbox GoldenrodCity_BikeShop_Text_ClerkAgreed, MSGBOX_DEFAULT
	giveitem ITEM_BICYCLE
	setflag FLAG_RECEIVED_BIKE
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Clerk_BikeReceived::
	msgbox GoldenrodCity_BikeShop_Text_Mainshop, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Clerk2::
	lock
	faceplayer
	msgbox GoldenrodCity_BikeShop_Text_Clerk2, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_EventScript_Bike::
	lock
	msgbox GoldenrodCity_BikeShop_Text_Bicycle, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_BikeShop_Text_Clerk2:
	.string "אם רושמים את האופניים מהתיק,\n"
	.string "רכיבה עליהם היא בלחיצת כפתור!\p"
	.string "אם רוצים לנסוע מהר יותר,\n"
	.string "קודם צריך לעצור!\p"
	.string "זו אולי נשמעת עצה מוזרה, אבל\n"
	.string "אפשר להחליף הילוכים רק בעמידה.\p"
	.string "לחץ על R בעמידה, ובדיווש הבא\n"
	.string "תגיע למהירות גבוהה יותר!$"

GoldenrodCity_BikeShop_Text_ClerkIntro:
    .string "…אנחה… עברתי לכאן, אבל אני לא\n"
    .string "מצליח למכור את האופניים שלי. למה?\p"
    .string "תוכל לרכוב על אופניים ולעשות\n"
    .string "לי פרסומת?$"

GoldenrodCity_BikeShop_Text_ClerkAgreed:
    .string "באמת? מצוין!\p"
    .string "תן לי את השם ומספר הטלפון שלך,\n"
    .string "ואשאיל לך אופניים.$"

GoldenrodCity_BikeShop_Text_BorrowedBicycle:
    .string "{PLAYER} borrowed a BICYCLE.$"

GoldenrodCity_BikeShop_Text_Mainshop:
	.string "העסק לא הולך מאז שעברנו מקאנטו.\n"
	.string "אנחנו מעריכים את העזרה שלך!\p"
	.string "תוכל להקפיד להשוויץ בפטנט\n"
	.string "שלנו להחלפת הילוכים?\p"
	.string "זה פשוט כמו ללחוץ על R כשאתה\n"
	.string "עומד במקום על האופניים.\p"
	.string "זהירות! אז תיסע מהר יותר!$"

GoldenrodCity_BikeShop_Text_Refused:
    .string "…אנחה… איפה טוב הלב של האנשים…$"

GoldenrodCity_BikeShop_Text_JustReleasedCompact:
    .string "Just released!\p"
    .string "First-rate compact BICYCLES!$"

GoldenrodCity_BikeShop_Text_Bicycle:
    .string "אלה אופניים חדשים ונוצצים!$"
