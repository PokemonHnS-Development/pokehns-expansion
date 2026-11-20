CeladonCity_Apartments_1F_hns_MapScripts::
	.byte 0

CeladonCity_Apartments_1F_EventScript_Manager::
	msgbox CeladonMansion_Text_Manager, MSGBOX_NPC
	end

CeladonCity_Apartments_1F_EventScript_Sign::
	msgbox CeladonMansion_Text_ManagersSuiteSign, MSGBOX_SIGN
	end

CeladonMansion_Text_Manager:
	.string "הפוקימונים היקרים שלי עושים לי חברה,\n"
	.string "אז אני אף פעם לא בודדה.\p"
	.string "מיאו אפילו מביא הביתה כסף.$"

CeladonMansion_Text_ManagersSuiteSign:
	.string "אחוזת סלדון\n"
	.string "סוויטת ההנהלה$"
