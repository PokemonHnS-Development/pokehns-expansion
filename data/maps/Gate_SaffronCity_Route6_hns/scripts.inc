Gate_SaffronCity_Route6_hns_MapScripts::
	.byte 0

Gate_SaffronCity_Route6_EventScript_Guard::
	goto_if_eq VAR_TEMP_0, 1, Gate_SaffronCity_Route6_EventScript_Guard2
	msgbox Route6_Text_SaffronGuardWelcome, MSGBOX_NPC
	setvar VAR_TEMP_0, 1
	end
Gate_SaffronCity_Route6_EventScript_Guard2::
	msgbox Route6_Text_SaffronGuardMagnetTrain, MSGBOX_NPC
	end

Route6_Text_SaffronGuardWelcome:
	.string "ברוכים הבאים לעיר סאפרון,\n"
	.string "ביתה של הרכבת המגנטית!\p"
	.string "…זה מה שהייתי אומר בדרך כלל, אבל\n"
	.string "הרכבת המגנטית לא פועלת עכשיו.\p"
	.string "היא לא מקבלת חשמל, כי משהו\n"
	.string "לא בסדר במפעל החשמל.$"

Route6_Text_SaffronGuardMagnetTrain:
	.string "הרכבת המגנטית היא הדבר\n"
	.string "הכי מפורסם בסאפרון.$"
