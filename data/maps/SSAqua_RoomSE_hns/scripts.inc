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
    .string "¡Hola! ¿Quieres luchar?\n"
    .string "conmigo?$"

SSAqua_RoomSE_Text_PokefanmColinBeaten:
    .string "You're strong!$"

SSAqua_RoomSE_Text_PokefanmColinAfter:
    .string "¿Viajas tú solo?\n"
    .string "¿No está preocupada tu mamá?$"

SSAqua_RoomSE_Text_TwinsMegandpeg1Seen:
    .string "¿Crees que soy un bebé?\n"
    .string "¡Eso no es justo!$"

SSAqua_RoomSE_Text_TwinsMegandpeg1Beaten:
    .string "Oh! We lost!$"

SSAqua_RoomSE_Text_TwinsMegandpeg1After:
    .string "¡Llamarnos bebés es muy grosero\n"
    .string "para nosotras!$"

SSAqua_RoomSE_Text_TwinsMegandpeg2Seen:
    .string "¡No soy un bebé!\n"
    .string "¡No es amable decirle eso a una dama!$"

SSAqua_RoomSE_Text_TwinsMegandpeg2Beaten:
    .string "Oh! We lost!$"

SSAqua_RoomSE_Text_TwinsMegandpeg2After:
    .string "¡A veces los niños son más listos\n"
    .string "que los adultos!$"
