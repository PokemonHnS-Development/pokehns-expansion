SSAqua_RoomSW_hns_MapScripts::
	.byte 0

SSAqua_RoomSW_EventScript_Cassie::
	trainerbattle_single TRAINER_CASSIE_HNS, SSAqua_RoomSW_Text_BeautyCassieSeen, SSAqua_RoomSW_Text_BeautyCassieBeaten
	msgbox SSAqua_RoomSW_Text_BeautyCassieAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSW_EventScript_Clyde::
	trainerbattle_single TRAINER_CLYDE_HNS, SSAqua_RoomSW_Text_GuitaristClydeSeen, SSAqua_RoomSW_Text_GuitaristClydeBeaten
	msgbox SSAqua_RoomSW_Text_GuitaristClydeAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomSW_Text_BeautyCassieSeen:
    .string "אני מנסה לשכוח מהצרות שלי.\n"
    .string "קדימה, לקרב!$"

SSAqua_RoomSW_Text_BeautyCassieBeaten:
    .string "הלב שלי בוכה…$"

SSAqua_RoomSW_Text_BeautyCassieAfterBattle:
    .string "הפלגה היא הדרך הכי טובה\n"
    .string "להתגבר על לב שבור.\p"
    .string "אבל ההפלגה בספינה המהירה\n"
    .string "קצרה מדי בשביל להתאבל.$"

SSAqua_RoomSW_Text_GuitaristClydeSeen:
    .string "אני בדרך לאודישן עם השירים שלי\n"
    .string "בתחנת הרדיו של גולדנרוד.$"

SSAqua_RoomSW_Text_GuitaristClydeBeaten:
    .string "וואו! דיסטורשן מוחלט!$"

SSAqua_RoomSW_Text_GuitaristClydeAfterBattleMobile:
    .string "I was going to make my debut at\n"
    .string "the BATTLE TOWER…\p"
    .string "I should go back to VERMILION and\n"
    .string "redo my training…$"

SSAqua_RoomSW_Text_GuitaristClydeAfterBattle:
    .string "אם כבר מדברים על תחנת הרדיו,\n"
    .string "מה מספר המזל של השבוע?$"
