Gate_Route43_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Gate_Route43_Rocket_OnFrame
	.byte 0

Gate_Route43_Rocket_OnFrame::
	map_script_2 VAR_TEMP_0, 0, Gate_Route43_RocketChecker
	.2byte 0

Gate_Route43_RocketChecker::
	setvar VAR_TEMP_0, 1
	goto_if_eq VAR_MAHOGANY_TOWN_STATE, 1, Gate_Route43_Rocket_EventScript_Shakedown
	goto_if_eq VAR_MAHOGANY_TOWN_STATE, 2, Gate_Route43_Rocket_EventScript_Shakedown
	goto_if_eq VAR_MAHOGANY_TOWN_STATE, 3, Gate_Route43_Rocket_EventScript_Shakedown
	goto_if_eq VAR_MAHOGANY_TOWN_STATE, 4, Gate_Route43_Rocket_EventScript_Shakedown
	goto_if_eq VAR_MAHOGANY_TOWN_STATE, 5, Gate_Route43_Rocket_EventScript_Shakedown
	end

Gate_Route43_Rocket_EventScript_Shakedown::
	lock
	showmoneybox 0, 0
	msgbox Gate_Route43_Rocket_Text_TollFee, MSGBOX_DEFAULT
	checkmoney 500
	goto_if_eq VAR_RESULT, FALSE, Gate_Route43_Rocket_EventScript_ShakedownBroke
	removemoney 500
	playse SE_SHOP
	updatemoneybox
	msgbox Gate_Route43_Rocket_Text_ThankYou, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Gate_Route43_Rocket_EventScript_ShakedownBroke::
	checkmoney 1
	goto_if_eq VAR_RESULT, FALSE, Gate_Route43_Rocket_EventScript_KickOut
	msgbox Gate_Route43_Rocket_Text_AllYouGot, MSGBOX_DEFAULT
	removemoney 500
	playse SE_SHOP
	updatemoneybox
	msgbox Gate_Route43_Rocket_Text_ThankYou, MSGBOX_DEFAULT
	hidemoneybox
	release
	end

Gate_Route43_Rocket_EventScript_KickOut::
	msgbox Gate_Route43_Rocket_Text_KickOut, MSGBOX_DEFAULT
	closemessage
	hidemoneybox
	release
	end

Gate_Route43_Rocket_EventScript_Policeman::
	lock
	faceplayer
	goto_if_set FLAG_GOT_TM_FROM_MAHOGANY_COP, Gate_Route43_Rocket_EventScript_PolicemanAfter
	msgbox Route43Gate_Text_OfficerFoundTM, MSGBOX_DEFAULT
	giveitem ITEM_TM_SLUDGE_BOMB
	setflag FLAG_GOT_TM_FROM_MAHOGANY_COP
	closemessage
	release
	end

Gate_Route43_Rocket_EventScript_PolicemanAfter::
	msgbox Gate_Route43_Text_OfficerAvoidGrass, MSGBOX_DEFAULT
	closemessage
	release
	end

Gate_Route43_Rocket_EventScript_Rockets::
	msgbox Gate_Route43_Rocket_Text_MakingABundle, MSGBOX_NPC
	end

Gate_Route43_Rocket_Text_TollFee:
    .string "עצור, ילדון!\p"
    .string "המעבר כאן עולה ¥500.$"

Gate_Route43_Rocket_Text_ThankYou:
    .string "תודה רבה!$"

Gate_Route43_Rocket_Text_AllYouGot:
    .string "אז תשלם כמה שיש לך, בבקשה.$"

Gate_Route43_Rocket_Text_KickOut:
	.string "וואו!\p"
	.string "אתה מרושש לגמרי!\p"
	.string "אני כמעט מרחם עליך.\p"
	.string "טוב, אתה יכול לעבור…\p"
	.string "רק אל תספר לשומר השני,\n"
	.string "בסדר?$"

Gate_Route43_Rocket_Text_MakingABundle:
    .string "חה-חה-חה. אנחנו עושים הון.\p"
    .string "כולם רוצים לראות מה קורה\n"
    .string "למעלה באגם הזעם.$"

Route43Gate_Text_OfficerFoundTM:
    .string "הבריונים האלה בשחור גירשו\n"
    .string "אותי מהעמדה שלי.\p"
    .string "הם השאירו את זה פה.\p"
    .string "לא נוח לי עם זה. תוכל לקחת\n"
    .string "את זה מכאן?$"

Gate_Route43_Text_ReceivedTM30:
    .string "{PLAYER} received TM36.$"

Gate_Route43_Text_OfficerAvoidGrass:
    .string "אפשר לעבור דרך השער הזה\n"
    .string "כדי לא ללכת בעשב.$"
