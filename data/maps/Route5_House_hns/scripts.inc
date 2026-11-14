Route5_House_hns_MapScripts::
	.byte 0

Route5_House_EventScript_Granny::
	goto_if_set FLAG_GOT_CLEANSE_TAG, Route5_House_EventScript_GrannyAfter
	msgbox Route5_House_Text_Granny1, MSGBOX_NPC
	giveitem ITEM_CLEANSE_TAG
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	setflag FLAG_GOT_CLEANSE_TAG
	release
	end

Route5_House_EventScript_GrannyAfter::
	msgbox Route5_House_Text_Granny2, MSGBOX_NPC
	end

Route5_House_EventScript_Woman::
	msgbox Route5_House_Text_Woman, MSGBOX_NPC
	end

Route5_House_Text_Granny1:
	.string "אייייאאה!\p"
	.string "אני חשה צל מרושע שמרחף מעליך.\n"
	.string "הנה, זה ירחיק אותו!$"

Route5_House_Text_Granny2:
	.string "היית בסכנת חיים, אבל\n"
	.string "עכשיו יש לך הגנה.$"

Route5_House_Text_Woman:
	.string "סבתא שלי מתעסקת בגירוש\n"
	.string "של מה שלדעתה הן רוחות רעות.\p"
	.string "אני מצטערת שהיא הבהילה אותך.$"
