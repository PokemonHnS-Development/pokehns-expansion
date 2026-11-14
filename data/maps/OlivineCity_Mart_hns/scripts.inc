OlivineCity_Mart_hns_MapScripts::
	.byte 0

OlivineCity_EventScript_Trainer1::
	lock
	faceplayer
	msgbox OlivineCity_Text_MartCooltrainerF, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_EventScript_Lass::
	lock
	faceplayer
	msgbox OlivineCity_Text_MartLass, MSGBOX_DEFAULT
	closemessage
	release
	end

OlivineCity_Text_MartCooltrainerF:
	.string "הפוקימונים שלך כבר יודעים את\n"
	.string "המהלך שמסיע אנשים על פני המים?$"

OlivineCity_Text_MartLass:
	.string "את הבטרפרי שלי קיבלתי\n"
	.string "מהחבר שלי שמעבר לים.\p"
	.string "הבטרפרי הביא איתו דואר ממנו.\p"
	.string "רוצה לדעת מה כתוב שם?\p"
	.string "בוא נראה… לא! זה סוד!$"
