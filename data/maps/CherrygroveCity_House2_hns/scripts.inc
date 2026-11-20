CherrygroveCity_House2_hns_MapScripts::
	.byte 0

CherrygroveCity_House2_EventScript_GuideGent::
	lock
	faceplayer
	msgbox CherrygroveCity_GuideHouse_Text_GuideGent, MSGBOX_DEFAULT
	closemessage
	release
	end

CherrygroveCity_GuideHouse_Text_GuideGent:
	.string "כשהייתי זאטוט, הייתי מאמן\n"
	.string "מהשורה הראשונה!\p"
	.string "הנה עצה קטנה:\n"
	.string "לתפוס הרבה פוקימונים!\p"
	.string "ולהתייחס לכולם בטוב לב!$"
