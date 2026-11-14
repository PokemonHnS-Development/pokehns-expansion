Gate_Route29_Route46_hns_MapScripts::
	.byte 0

Gate_Route29_Route46_EventScript_Officer::
	lock
	faceplayer
	msgbox Gate_Route29_Route46_Text_Officer, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route29_Route46_EventScript_Youngster::
	lock
	faceplayer
	msgbox Gate_Route29_Route46_Text_Youngster, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route29_Route46_Text_Officer:
	.string "אי אפשר לטפס על מדרגות סלע.\p"
	.string "אבל אפשר לקפוץ מהן למטה\n"
	.string "כדי לקצר את הדרך.$"

Gate_Route29_Route46_Text_Youngster:
	.string "מכאן והלאה מופיעים\n"
	.string "פוקימונים אחרים.\p"
	.string "אם רוצים לתפוס את כולם,\n"
	.string "צריך לחפש בכל מקום.$"
