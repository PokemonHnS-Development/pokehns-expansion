AzaleaTown_Mart_hns_MapScripts::
	.byte 0

AzaleaTown_Mart_EventScriptCooltrainerM::
	lock
	faceplayer
	msgbox AzaleaMart_Text_CooltrainerM, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_Mart_EventScriptBugCatcher::
	lock
	faceplayer
	msgbox AzaleaMart_Text_BugCatcher, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaMart_Text_CooltrainerM:
	.string "אתה יכול לקנות כדור מעולה?\n"
	.string "אני יכול לקנות רק פוכדורים.\p"
	.string "שמעתי שאפשר לקנות יותר\n"
	.string "פריטים כשמרוויחים תגי מכון!\p"
	.string "הלוואי שקורט יכין לי כמה\n"
	.string "מהכדורים המיוחדים שלו.$"

AzaleaMart_Text_BugCatcher:
	.string "כדור מעולה טוב יותר לתפיסת\n"
	.string "פוקימונים מאשר פוכדור.\p"
	.string "אבל לפעמים הכדורים של קורט\n"
	.string "יכולים להיות טובים יותר.$"

