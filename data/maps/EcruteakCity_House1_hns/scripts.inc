EcruteakCity_House1_hns_MapScripts::
	.byte 0

EcruteakCity_House1_EventScript_Gramps::
	lock
	faceplayer
	msgbox EcruteakLugiaSpeechHouse_Text_Gramps, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_House1_EventScript_Youngster::
	lock
	faceplayer
	msgbox EcruteakLugiaSpeechHouse_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakLugiaSpeechHouse_Text_Gramps:
	.string "זה קרה כשהייתי צעיר.\p"
	.string "השמיים החשיכו פתאום. פוקימון\n"
	.string "מעופף ענקי הסתיר את השמש.\p"
	.string "מעניין איזה פוקימון זה היה?\p"
	.string "הוא נראה כמו ציפור וגם כמו דרקון.$"

EcruteakLugiaSpeechHouse_Text_Youngster:
	.string "באמת יש פוקימון כל כך גדול?\p"
	.string "אם הוא קיים, הוא בטח חזק מאוד.$"
