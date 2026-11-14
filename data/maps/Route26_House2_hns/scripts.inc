Route26_House2_hns_MapScripts::
	.byte 0

Route26_House2_EventScript_Book::
	lock
	msgbox DayOfWeekSiblingsHouse_Text_Pokedex1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE,Route26_House2_EventScript_BookRead
	closemessage
	release
	end

Route26_House2_EventScript_BookRead::
	msgbox DayOfWeekSiblingsHouse_Text_Pokedex2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, Route26_House2_EventScript_BookRead2
	closemessage
	release
	end
	
Route26_House2_EventScript_BookRead2::
	msgbox DayOfWeekSiblingsHouse_Text_Pokedex3, MSGBOX_DEFAULT
	closemessage
	release
	end

DayOfWeekSiblingsHouse_Text_Pokedex1:
    .string "משהו כתוב כאן.\p"
    .string "לקרוא?$"

DayOfWeekSiblingsHouse_Text_Pokedex2:
    .string "לאחיי ולאחיותיי:\p"
    .string "אנחנו גאים לשרת מאמני פוקימונים.\p"
    .string "כשמאמנים מדברים איתכם,\n"
    .string "תנו להם משהו מועיל.\p"
    .string "באהבה,\n"
    .string "מוניקה\p"
    .string "להמשיך לקרוא?$"

DayOfWeekSiblingsHouse_Text_Pokedex3:
    .string "יום שני, מוניקה\n"
    .string "דרך 40\p"
    .string "יום שלישי, טוסקני\n"
    .string "דרך 29\p"
    .string "יום רביעי, ווסלי\n"
    .string "אגם הזעם\p"
    .string "יום חמישי, ארתור\n"
    .string "דרך 36\p"
    .string "יום שישי, פרידה\n"
    .string "דרך 32\p"
    .string "שבת, סנטוס\n"
    .string "העיר בלקתורן\p"
    .string "יום ראשון, סאני\n"
    .string "דרך 37$"
