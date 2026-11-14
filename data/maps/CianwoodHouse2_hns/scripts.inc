CianwoodHouse2_hns_MapScripts::
	.byte 0

CianwoodHouse2_EventScript_Teacher::
	lock
	faceplayer
	msgbox CianwoodCity_Text_LugiaHouseTeacher, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse2_EventScript_Lass::
	lock
	faceplayer
	msgbox CianwoodCity_Text_LugiaHouseLass, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse2_EventScript_Twin::
	lock
	faceplayer
	msgbox CianwoodCity_Text_LugiaHouseTwin, MSGBOX_DEFAULT
	closemessage
	release
	end
	
CianwoodCity_Text_LugiaHouseTeacher:
	.string "באת מאוליבין?\p"
	.string "אתה זוכר את ארבעת האיים\n"
	.string "שבדרך?\p"
	.string "שמעתי שיצור ים אגדי\n"
	.string "מסתתר בהם.$"

CianwoodCity_Text_LugiaHouseLass:
	.string "שמעתי שאפשר לראות אותו\n"
	.string "רק אם יש לך נוצת כסף.\p"
	.string "כנראה הריח שלה זהה\n"
	.string "לריח של היצור.$"

CianwoodCity_Text_LugiaHouseTwin:
	.string "שמעתי שיצור הים הוא שגורם\n"
	.string "למערבולות מסביב לאיים.\p"
	.string "אולי צריך מהלך מיוחד\n"
	.string "כדי לעבור אותן.$"
