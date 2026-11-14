Gate_GoldenrodCity_Route35_hns_MapScripts::
	.byte 0

Gate_GoldenrodCity_Route35_EventScript_Randy::
	lock
	faceplayer
	goto_if_eq VAR_KENYA, 3, Gate_GoldenrodCity_Route35_EventScript_RandyPostKenya
	goto_if_eq VAR_KENYA, 2, Gate_GoldenrodCity_Route35_EventScript_RandyDeliveredKenya
	goto_if_eq VAR_KENYA, 1, Gate_GoldenrodCity_Route35_EventScript_RandyHaveKenya
	msgbox Route35GoldenrodGate_Text_RandyAskFavor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, Gate_GoldenrodCity_Route35_EventScript_RandyCancel
	closemessage

	msgbox Route35GoldenrodGate_Text_RandyThanks, MSGBOX_DEFAULT

	@HnS named gift pokemon setup
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_SPEAROW
	bufferspeciesname STR_VAR_1, SPECIES_SPEAROW
	givenamedmon 1
	call Common_EventScript_GiftMonNamed

	setvar VAR_KENYA, 1
	release
	end

Gate_GoldenrodCity_Route35_EventScript_RandyCancel::
	msgbox Route35GoldenrodGate_Text_RandyNeverMind, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_GoldenrodCity_Route35_EventScript_RandyHaveKenya::
	msgbox Route35GoldenrodGate_Text_RandyWeirdTree, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_GoldenrodCity_Route35_EventScript_RandyDeliveredKenya::
	msgbox Route35GoldenrodGate_Text_ThanksForDelivery, MSGBOX_DEFAULT
	closemessage
	giveitem ITEM_HP_UP
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox Route35GoldenrodGate_Text_RandyMyPalSnoozing, MSGBOX_DEFAULT
	closemessage
	setvar VAR_KENYA, 3
	release
	end

Gate_GoldenrodCity_Route35_EventScript_RandyPostKenya::
	msgbox Route35GoldenrodGate_Text_RandyMyPalSnoozing, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_GoldenrodCity_Route35_EventScript_Lady::
	lock
	faceplayer
	goto_if_set FLAG_HIDE_SUDOWOODO, Gate_GoldenrodCity_Route35_EventScript_Lady2
	msgbox Route35GoldenrodGate_Text_PokefanF_TreeBlocking, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_GoldenrodCity_Route35_EventScript_Lady2::
	msgbox Route35GoldenrodGate_Text_PokefanF_Lullaby, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_GoldenrodCity_Route35_EventScript_Fisher::
	lock
	faceplayer
	msgbox Route35GoldenrodGate_Text_Fisher, MSGBOX_DEFAULT
	closemessage
	release
	end

Route35GoldenrodGate_Text_RandyAskFavor:
	.string "סליחה, ילד! תוכל לעשות לי טובה?\p"
	.string "תוכל לקחת את הפוקימון הזה עם\n"
	.string "הדואר לחבר שלי?\p"
	.string "הוא נמצא בדרך 31.$"

Route35GoldenrodGate_Text_RandyThanks:
	.string "באמת? מושלם! תודה, ילד!\p"
	.string "החבר שלי הוא בחור שמנמן\n"
	.string "שמנמנם כל הזמן.\p"
	.string "תזהה אותו מיד!$"

Route35GoldenrodGate_Text_ReceivedMonWithMail:
	.string "{PLAYER} received a POKéMON with MAIL.$"

Route35GoldenrodGate_Text_RandyWeirdTree:
	.string "תדאג לשים אותו בראש הקבוצה שלך\n"
	.string "כשתמצא את החבר שלי!\p"
	.string "דרך 31!\p"
	.string "אה, נכון. היה שם עץ מוזר\n"
	.string "שחסם את הדרך.\p"
	.string "מעניין אם כבר פינו אותו?$"

Route35GoldenrodGate_Text_CantCarryMoreMon:
	.string "You can't carry another POKéMON…$"

Route35GoldenrodGate_Text_RandyNeverMind:
	.string "אה… טוב, לא חשוב…$"

Route35GoldenrodGate_Text_ThanksForDelivery:
	.string "תודה, ילד! מסרת את המשלוח\n"
	.string "בשבילי!\p"
	.string "הנה משהו על הטרחה!$"

Route35GoldenrodGate_Text_RandyMyPalSnoozing:
	.string "החבר שלי נמנם, נכון? חה,\n"
	.string "מה אמרתי לך?$"

Route35GoldenrodGate_Text_PokefanF_TreeBlocking:
	.string "עץ מוזר חוסם את הדרך.\p"
	.string "הוא מתפתל כשמדברים אליו.\p"
	.string "שמעתי שהוא השתולל כשמישהו\n"
	.string "השקה אותו בבקבוק התזה.$"

Route35GoldenrodGate_Text_PokefanF_Lullaby:
	.string "אני אוהבת את שיר הערש לפוקימונים\n"
	.string "שמשמיעים ברדיו.$"

Route35GoldenrodGate_Text_Fisher:
	.string "מעניין כמה מינים של פוקימונים\n"
	.string "יש בעולם.\p"
	.string "לפני שלוש שנים פרופ' אוק אמר\n"
	.string "שיש 150 מינים שונים.\p"
	.string "אבל לאחרונה שמעתי שיש\n"
	.string "יותר מ-400!$"
