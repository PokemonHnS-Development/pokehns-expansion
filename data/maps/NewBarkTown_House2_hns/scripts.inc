NewBarkTown_House2_hns_MapScripts::
	.byte 0


NewBarkTown_House2_EventScript_ElmsWife::
	lock
	faceplayer
	msgbox NewBarkTown_House2_Text_ElmsWife, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_House2_EventScript_ElmsSon::
	lock
	faceplayer
	msgbox NewBarkTown_House2_Text_ElmsSon, MSGBOX_DEFAULT
	closemessage
	release
	end

NewBarkTown_House2_Text_ElmsWife:
	.string "היי, {PLAYER}! בעלי תמיד\n"
	.string "כל כך עסוק - אני מקווה שהוא בסדר.\p"
	.string "כשהוא שקוע במחקר הפוקימונים שלו,\n"
	.string "הוא אפילו שוכח לאכול.$"

NewBarkTown_House2_Text_ElmsSon:
	.string "כשאהיה גדול, אני אעזור\n"
	.string "לאבא שלי!\p"
	.string "אני אהיה פרופסור\n"
	.string "פוקימונים גדול!$"
