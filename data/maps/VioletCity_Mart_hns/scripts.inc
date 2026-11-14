VioletCity_Mart_hns_MapScripts::
	.byte 0

VioletCity_Mart_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart 0
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

VioletCity_Mart_EventScript_Granny::
	lock
	faceplayer
	msgbox VioletCity_Mart_Text_Granny, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_Mart_EventScript_Rocker::
	lock
	faceplayer
	msgbox VioletCity_Mart_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end
	
VioletCity_Mart_Text_Granny:
	.string "כשתופסים פוקימון בפעם הראשונה,\n"
	.string "הוא עלול להיות חלש.\p"
	.string "אבל בסופו של דבר הוא יגדל ויתחזק.\p"
	.string "חשוב להתייחס לפוקימונים באהבה.$"

VioletCity_Mart_Text_CooltrainerM:
	.string "פוקימונים יכולים להחזיק פריטים כמו\n"
	.string "שיקוי ונוגדן.\p"
	.string "אבל נראה שהם לא יודעים איך\n"
	.string "להשתמש בפריטים מעשה ידי אדם.$"
