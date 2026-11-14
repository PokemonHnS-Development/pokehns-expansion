SSAqua_RoomNNE_hns_MapScripts::
	.byte 0

SSAqua_RoomNNE_EventScript_Sean::
	trainerbattle_single TRAINER_SEAN_HNS, SSAqua_RoomNNE_Text_CooltrainermSeanSeen, SSAqua_RoomNNE_Text_CooltrainermSeanBeaten
	msgbox SSAqua_RoomNNE_Text_CooltrainermSeanAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNNE_EventScript_Carol::
	trainerbattle_single TRAINER_CAROL_HNS, SSAqua_RoomNNE_Text_CooltrainerfCarolSeen, SSAqua_RoomNNE_Text_CooltrainerfCarolBeaten
	msgbox SSAqua_RoomNNE_Text_CooltrainerfCarolAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNNE_Text_CooltrainermSeanSeen:
    .string "אני נוסע לקאנטו\n"
    .string "לבחון את הכישורים שלי.$"

SSAqua_RoomNNE_Text_CooltrainermSeanBeaten:
    .string "רציתי לנצח!$"

SSAqua_RoomNNE_Text_CooltrainermSeanAfterBattle:
    .string "מאמנים מג'וטו יכולים להילחם\n"
    .string "במנהיגי המכונים של קאנטו.$"

SSAqua_RoomNNE_Text_CooltrainerfCarolSeen:
    .string "אני מתאמנת כדי\n"
    .string "להיות האלופה!$"

SSAqua_RoomNNE_Text_CooltrainerfCarolBeaten:
    .string "מה כל כך שונה\n"
    .string "בינינו?$"

SSAqua_RoomNNE_Text_CooltrainerfCarolAfterBattle:
    .string "יום אחד אני\n"
    .string "עוד אנצח אותך!$"
