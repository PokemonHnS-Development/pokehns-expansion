PewterCity_Museum_2F_hns_MapScripts::
	.byte 0


PewterCity_Museum_2F_EventScript_Nerd::
	msgbox PewterCity_Museum_2F_Text_Nerd, MSGBOX_NPC
	end

PewterCity_Museum_2F_EventScript_Daughter::
	lock
	msgbox PewterCity_Museum_2F_Text_AskedDaddyToCatchPikachu, MSGBOX_DEFAULT
	release
	end

PewterCity_Museum_2F_EventScript_Dad::
	lock
	msgbox PewterCity_Museum_2F_Text_PikachuSoonIPromise, MSGBOX_DEFAULT
	release
	end

PewterCity_Museum_2F_EventScript_Meteor::
	msgbox PewterCity_Museum_2F_Text_MeteoriteThatFellOnMtMoon, MSGBOX_SIGN
	end

PewterCity_Museum_2F_Text_Nerd:
	.string "אומרים שמטאוריטים פגעו\n"
	.string "באי הלידה.\p"
	.string "היינו שמחים להציג אותם כאן\n"
	.string "במוזיאון שלנו, אבל…\p"
	.string "אומרים שהם פולטים אנרגיה מוזרה,\n"
	.string "ושאי אפשר להזיז אותם…$"

PewterCity_Museum_2F_Text_AskedDaddyToCatchPikachu::
    .string "אני רוצה פיקאצ'ו!\n"
    .string "הוא כל כך חמוד!\p"
    .string "ביקשתי מאבא שלי שיתפוס לי אחד!$"

PewterCity_Museum_2F_Text_PikachuSoonIPromise::
    .string "כן, פיקאצ'ו בקרוב, אני מבטיח!$"

PewterCity_Museum_2F_Text_SpaceShuttle::
    .string "Space Shuttle$"

PewterCity_Museum_2F_Text_MeteoriteThatFellOnMtMoon::
    .string "מטאוריט שנפל על הר הירח.\n"
    .string "משערים שזו אבן ירח.$"
