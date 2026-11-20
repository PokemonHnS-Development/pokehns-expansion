GoldenrodCity_FlowerShop_hns_MapScripts::
	.byte 0


GoldenrodCity_FlowerShop_EventScript_MintClerk::
	lock
	faceplayer
	goto_if_unset FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_MintClerkNotReady
	message gText_HowMayIServeYou
	waitmessage
	pokemart GoldenrodCity_FlowerShop_Mints
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_FlowerShop_EventScript_MintClerkNotReady::
	msgbox GoldenrodCity_FlowerShop_Text_MintClerkNotReady, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_Text_MintClerkNotReady:
	.string "כרגע אזל לנו המלאי.\p"
	.string "בבקשה לחזור מאוחר יותר.$"

	.align 2
GoldenrodCity_FlowerShop_Mints:
	.2byte ITEM_SERIOUS_MINT
	.2byte ITEM_ADAMANT_MINT
	.2byte ITEM_BOLD_MINT
	.2byte ITEM_BRAVE_MINT
	.2byte ITEM_CALM_MINT
	.2byte ITEM_CAREFUL_MINT
	.2byte ITEM_GENTLE_MINT
	.2byte ITEM_HASTY_MINT
	.2byte ITEM_IMPISH_MINT
	.2byte ITEM_JOLLY_MINT
	.2byte ITEM_LAX_MINT
	.2byte ITEM_LONELY_MINT
	.2byte ITEM_MILD_MINT
	.2byte ITEM_MODEST_MINT
	.2byte ITEM_NAIVE_MINT
	.2byte ITEM_NAUGHTY_MINT
	.2byte ITEM_QUIET_MINT
	.2byte ITEM_RASH_MINT
	.2byte ITEM_RELAXED_MINT
	.2byte ITEM_SASSY_MINT
	.2byte ITEM_TIMID_MINT
	pokemartlistend


GoldenrodCity_FlowerShop_EventScript_Owner::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SUDOWOODO, GoldenrodCity_FlowerShop_EventScript_Normal
	goto_if_set FLAG_RECEIVED_SQUIRTBOTTLE, GoldenrodCity_FlowerShop_EventScript_GotSquirtBottle
	goto_if_set FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_GiveSquirtBottle
	msgbox GoldenrodCity_FlowerShop_Text_Owner1, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_GiveSquirtBottle::
	lock
	faceplayer
	msgbox GoldenrodCity_FlowerShop_Text_Owner2, MSGBOX_DEFAULT
	giveitem ITEM_SQUIRT_BOTTLE
	setflag FLAG_RECEIVED_SQUIRTBOTTLE
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_GotSquirtBottle::
	lock
	faceplayer
	msgbox GoldenrodCity_FlowerShop_Text_Owner3, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_Normal::
	lock
	faceplayer
	msgbox GoldenrodCity_FlowerShop_Text_Owner4, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_Floria1::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SUDOWOODO, GoldenrodCity_FlowerShop_EventScript_Floria3
	goto_if_set FLAG_BADGE03_GET, GoldenrodCity_FlowerShop_EventScript_Floria2
	msgbox GoldenrodCity_FlowerShop_Text_Floria, MSGBOX_DEFAULT
	closemessage
	release
	end
	
GoldenrodCity_FlowerShop_EventScript_Floria2::
	msgbox GoldenrodCity_FlowerShop_Text_FloriaYouBeatWhitney, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_EventScript_Floria3::
	msgbox GoldenrodCity_FlowerShop_Text_FloriaItWasAMon, MSGBOX_DEFAULT
	closemessage
	release
	end

GoldenrodCity_FlowerShop_Text_Floria:
	.string "כשסיפרתי לאחותי על העץ המתנועע,\n"
	.string "היא אמרה שזה מסוכן.\p"
	.string "אם אנצח את ויטני, אולי אחותי\n"
	.string "תשאיל לי את בקבוק המים שלה…$"

GoldenrodCity_FlowerShop_Text_Owner1:
.string "מסתבר שיש עץ משונה בדרך 36.\p"
.string "אומרים שהוא רוקד כשמשקים אותו…\p"
.string "אה, בטח שלא!\p"
.string "זו חנות פרחים, אז יש לנו מזלפים…\p"
.string "אבל אני לא יכולה לתת לך אחד!\n"
.string "זה מסוכן מדי!\p"
.string "טוב, אולי אם תצליח לנצח את\n"
.string "מנהיגת המכון ויטני, זה יהיה בסדר.$"

GoldenrodCity_FlowerShop_Text_Owner2:
.string "מסתבר שיש עץ משונה בדרך 36.\p"
.string "אומרים שהוא רוקד כשמשקים אותו…\p"
.string "אה, זה תג מישור של מכון גולדנרוד!\p"
.string "ניצחת את ויטני?!\p"
.string "טוב, אז אין מה לדאוג, נכון?\p"
.string "אז אשאיל לך את בקבוק ההתזה\n"
.string "הזה לזמן מה.\p"
.string "…\n"
.string "אה, לא משנה. תשאיר אותו אצלך!$"

GoldenrodCity_FlowerShop_Text_Owner3:
.string "העץ המשונה נמצא בדרך 36.\n"
.string "תיזהר, בבקשה!$"

GoldenrodCity_FlowerShop_Text_Owner4:
    .string "לה-לה-לה, לה-לה-לה-לה. תשתו\n"
    .string "הרבה מים, יפים שלי!$"

GoldenrodCity_FlowerShop_Text_FloriaYouBeatWhitney:
    .string "וואו, ניצחת את ויטני? מגניב!$"

GoldenrodCity_FlowerShop_Text_FloriaItWasAMon:
    .string "אז זה באמת היה פוקימון!$"


GoldenrodCity_FlowerShop_EventScript_RandomBerryGirl::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_FLOWER_SHOP_RECEIVED_BERRY_HNS, GoldenrodCity_FlowerShop_EventScript_AlreadyReceivedBerry
	msgbox Route104_PrettyPetalFlowerShop_Text_ImGrowingFlowers, MSGBOX_DEFAULT
	random 8
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem VAR_RESULT
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_FLOWER_SHOP_RECEIVED_BERRY_HNS
	msgbox Route104_PrettyPetalFlowerShop_Text_MachineMixesBerries, MSGBOX_DEFAULT
	release
	end

GoldenrodCity_FlowerShop_EventScript_AlreadyReceivedBerry::
	msgbox Route104_PrettyPetalFlowerShop_Text_MachineMixesBerries, MSGBOX_DEFAULT
	release
	end

