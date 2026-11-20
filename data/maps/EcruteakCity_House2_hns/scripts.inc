EcruteakCity_House2_hns_MapScripts::
	.byte 0

Ecruteak_Text_ItemfinderAdventure:
	.string "אה. אתה בהרפתקה עם\n"
	.string "הפוקימונים שלך?\p"
	.string "נו, מה זו הרפתקה בלי\n"
	.string "ציד אוצרות?\p"
	.string "אני צודק, או שאני צודק?$"

Ecruteak_Text_ItemfinderTrueSpirit:
	.string "יופי! אתה מבין את רוח\n"
	.string "ההרפתקה האמיתית.\p"
	.string "זה מוצא חן בעיניי! הנה, זה בשבילך.$"

Ecruteak_Text_ItemfinderExplanation:
	.string "יש הרבה פריטים מפוזרים\n"
	.string "שלא רואים אותם בקלות.\p"
	.string "בעזרת גלאי פריטים אפשר לבדוק\n"
	.string "אם יש פריט על הקרקע בסביבה.\p"
	.string "הוא לא מראה את המקום המדויק,\n"
	.string "אז צריך לחפש בעצמך.\p"
	.string "אה, נכון - שמעתי שיש פריטים\n"
	.string "במגדל השרוף של אקרוטיק.$"

Ecruteak_Text_ItemfinderToEachHisOwn:
	.string "אה… כל אחד והטעם שלו, אני מניח…$"

EcruteakCity_House2_EventScript_ItemFinderMan::
	lock
	faceplayer
	checkitem ITEM_DOWSING_MACHINE
	goto_if_eq VAR_RESULT, TRUE, EcruteakCity_House2_EventScript_AlreadyGotItemfinder
	msgbox Ecruteak_Text_ItemfinderAdventure, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, EcruteakCity_House2_EventScript_GiveItemFinder
	msgbox Ecruteak_Text_ItemfinderToEachHisOwn, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_House2_EventScript_GiveItemFinder::
	msgbox Ecruteak_Text_ItemfinderTrueSpirit, MSGBOX_DEFAULT
	giveitem ITEM_DOWSING_MACHINE
EcruteakCity_House2_EventScript_AlreadyGotItemfinder::
	msgbox Ecruteak_Text_ItemfinderExplanation, MSGBOX_DEFAULT
	closemessage
	release
	end


EcruteakCity_House2_EventScript_Book::
	lock
	msgbox Ecruteak_Text_HistoryBook, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, EcruteakCity_House2_EventScript_Book2
	closemessage
	release
	end

EcruteakCity_House2_EventScript_Book2::
	msgbox Ecruteak_Text_TwoTowers, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, EcruteakCity_House2_EventScript_Book3
	release
	end

EcruteakCity_House2_EventScript_Book3::
	msgbox Ecruteak_Text_ThreeMon, MSGBOX_DEFAULT
	closemessage
	release
	end

Ecruteak_Text_ItemFinderMan::
	.string "ECRUTEAK is a very old city.\n"
	.string "Many generations passed down\l"
	.string "their history in books like these.$"

Ecruteak_Text_HistoryBook:
	.string "תולדות אקרוטיק\p"
	.string "לקרוא את הספר?$"

Ecruteak_Text_TwoTowers:
	.string "באקרוטיק היו שני מגדלים.\p"
	.string "כל מגדל היה משכנו של\n"
	.string "פוקימון מעופף ועוצמתי.\p"
	.string "אבל אחד המגדלים נשרף\n"
	.string "עד היסוד.\p"
	.string "את שני הפוקימונים לא ראו\n"
	.string "מאז…\p"
	.string "להמשיך לקרוא?$"

Ecruteak_Text_ThreeMon:
	.string "באקרוטיק חיו גם שלושה\n"
	.string "פוקימונים שדהרו ברחבי העיר.\p"
	.string "אומרים שהם נולדו\n"
	.string "ממים, מברק ומאש.\p"
	.string "אבל הם לא הצליחו לרסן את\n"
	.string "כוחם העצום.\p"
	.string "ולכן, אומרים, השלושה דהרו כמו\n"
	.string "הרוח אל הערבות.$"
