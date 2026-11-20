SSAqua_RoomSE_hns_MapScripts::
	.byte 0

SSAqua_RoomSE_EventScript_Colin::
	trainerbattle_single TRAINER_COLIN_HNS, SSAqua_RoomSE_Text_PokefanmColinSeen, SSAqua_RoomSE_Text_PokefanmColinBeaten
	msgbox SSAqua_RoomSE_Text_PokefanmColinAfter, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSE_EventScript_Meg::
	trainerbattle_double TRAINER_MEG_AND_PEG_HNS, SSAqua_RoomSE_Text_TwinsMegandpeg1Seen, SSAqua_RoomSE_Text_TwinsMegandpeg1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox SSAqua_RoomSE_Text_TwinsMegandpeg1After, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSE_EventScript_Peg::
	trainerbattle_double TRAINER_MEG_AND_PEG_HNS, SSAqua_RoomSE_Text_TwinsMegandpeg2Seen, SSAqua_RoomSE_Text_TwinsMegandpeg2Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox SSAqua_RoomSE_Text_TwinsMegandpeg2After, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSE_Text_PokefanmColinSeen:
    .string "היי, ילד! רוצה להילחם\n"
    .string "איתי?$"

SSAqua_RoomSE_Text_PokefanmColinBeaten:
    .string "אתה חזק!$"

SSAqua_RoomSE_Text_PokefanmColinAfter:
    .string "אתה מטייל לגמרי לבד?\n"
    .string "אמא שלך לא דואגת?$"

SSAqua_RoomSE_Text_TwinsMegandpeg1Seen:
    .string "אתה חושב שאני תינוקת?\n"
    .string "זה לא הוגן!$"

SSAqua_RoomSE_Text_TwinsMegandpeg1Beaten:
    .string "אוי! הפסדנו!$"

SSAqua_RoomSE_Text_TwinsMegandpeg1After:
    .string "זה לא מנומס לקרוא\n"
    .string "לבנות כמונו תינוקות!$"

SSAqua_RoomSE_Text_TwinsMegandpeg2Seen:
    .string "אני לא תינוקת!\n"
    .string "לא יפה להגיד את זה לגברת!$"

SSAqua_RoomSE_Text_TwinsMegandpeg2Beaten:
    .string "אוי! הפסדנו!$"

SSAqua_RoomSE_Text_TwinsMegandpeg2After:
    .string "לפעמים ילדים חכמים\n"
    .string "יותר ממבוגרים!$"
