BlackthornCity_House1_hns_MapScripts::
	.byte 0

BlackthornCity_House1EventScript_Granny::
	msgbox BlackthornCity_House1_Text_Granny, MSGBOX_NPC
	end

BlackthornCity_House1EventScript_Dratini::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DRATINI, CRY_MODE_NORMAL
	msgbox BlackthornCity_House1_Text_Dratini, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BlackthornCity_House1_Text_Granny:
	.string "שבט מאמנים שיכולים לפקד בחופשיות\n"
	.string "על דרקונים גר ממש כאן, בבלקתורן.\p"
	.string "לכן יש בעיר הזאת\n"
	.string "הרבה אגדות על דרקונים.$"

BlackthornCity_House1_Text_Dratini:
	.string "דרטיני: דראה!$"
