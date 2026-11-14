AzaleaTown_House1_hns_MapScripts::
	.byte 0

AzaleaTown_House1_EventScript_Boss::
	lock
	faceplayer
	goto_if_eq VAR_AZALEA_TOWN_STATE, 5, AzaleaTown_House1_EventScript_Boss3
	goto_if_eq VAR_AZALEA_TOWN_STATE, 6, AzaleaTown_House1_EventScript_Boss3
	goto_if_eq VAR_AZALEA_TOWN_STATE, 7, AzaleaTown_House1_EventScript_Boss4
	goto_if_set FLAG_HIDE_AZALEA_TOWN_ROCKETS, AzaleaTown_House1_EventScript_Boss2
	msgbox CharcoalKiln_Text_Boss1, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Boss2::
	msgbox CharcoalKiln_Text_Boss2, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Boss3::
	msgbox CharcoalKiln_Text_Boss3, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Boss4::
	msgbox CharcoalKiln_Text_Boss4, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Apprentice::
	lock
	faceplayer
	goto_if_ge VAR_AZALEA_TOWN_STATE, 7, AzaleaTown_House1_EventScript_Apprentice3
	goto_if_set FLAG_HIDE_AZALEA_TOWN_ROCKETS, AzaleaTown_House1_EventScript_Apprentice2
	msgbox CharcoalKiln_Text_Apprentice1, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Apprentice2::
	msgbox CharcoalKiln_Text_Apprentice2, MSGBOX_DEFAULT
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Apprentice3::
	goto_if_set FLAG_GOT_CHARCOAL, AzaleaTown_House1_EventScript_Apprentice4
	msgbox CharcoalKiln_Text_Apprentice3, MSGBOX_DEFAULT
	giveitem ITEM_CHARCOAL 
	setflag FLAG_GOT_CHARCOAL
	closemessage
	release
	end

AzaleaTown_House1_EventScript_Apprentice4::
	msgbox CharcoalKiln_Text_Apprentice4, MSGBOX_DEFAULT
	closemessage
	release
	end


AzaleaTown_House1_EventScript_Farfetchd::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_FARFETCHD, CRY_MODE_NORMAL
	msgbox CharcoalKiln_Text_Farfetchd, MSGBOX_DEFAULT
	waitmoncry
	release
	end
	


CharcoalKiln_Text_Boss1:
	.string "כל הסלופוק נעלמו מהעיירה.\p"
	.string "אולי מגן היער כועס עלינו…\p"
	.string "אולי זה סימן רע. כדאי שנישאר בבית.$"

CharcoalKiln_Text_Boss2:
	.string "הסלופוק חזרו…$"

CharcoalKiln_Text_Boss3:
	.string "הסלופוק חזרו…\p"
	.string "אבל השוליה שלי עוד לא חזר מיער אילקס.\p"
	.string "איפה בכלל מסתובב הבטלן הזה?$"

CharcoalKiln_Text_Boss4:
	.string "גירשת את צוות רוקט\n"
	.string "והלכת לבד ליער אילקס?\p"
	.string "לזה צריך אומץ! אני אוהב את זה.\n"
	.string "בוא להתאמן איתנו.$"

CharcoalKiln_Text_Apprentice1:
	.string "לאן נעלמו כל הסלופוק?\p"
	.string "אולי הם משחקים איפשהו בחוץ?$"

CharcoalKiln_Text_Apprentice2:
	.string "הסלופוק חזרו!$"

CharcoalKiln_Text_Apprentice3:
	.string "סליחה, שכחתי להודות לך.\p"
	.string "זה פחם שהכנתי.\p"
	.string "פוקימונים מסוג אש ישמחו להחזיק אותו.$"

CharcoalKiln_Text_Apprentice4:
	.string "הסלופוק חזרו, ואפילו מצאת את פארפג'ד.\p"
	.string "אתה הכי מגניב, אחי!$"

CharcoalKiln_Text_Farfetchd:
	.string "פארפג'ד: קוואה!$"
