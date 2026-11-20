SSAqua_RoomNE_hns_MapScripts::
	.byte 0

SSAqua_RoomNE_EventScript_Noland::
	trainerbattle_single TRAINER_NOLAND_HNS, SSAqua_RoomNE_Text_HikerNolandSeen, SSAqua_RoomNE_Text_HikerNolandBeaten
	msgbox SSAqua_RoomNE_Text_HikerNolandAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNE_EventScript_Ethan::
	trainerbattle_single TRAINER_ETHAN_HNS, SSAqua_RoomNE_Text_PokemaniacEthanSeen, SSAqua_RoomNE_Text_PokemaniacEthanBeaten
	msgbox SSAqua_RoomNE_Text_PokemaniacEthanAfterBattle, MSGBOX_AUTOCLOSE
	end

SSAqua_RoomNE_Text_HikerNolandSeen:
    .string "אתה לבד?\n"
    .string "אז קדימה, לקרב!$"

SSAqua_RoomNE_Text_HikerNolandBeaten:
    .string "זה יותר מדי בשבילי!$"

SSAqua_RoomNE_Text_HikerNolandAfterBattle:
    .string "מעניין אם יש בקאנטו\n"
    .string "הרים ששווה לטפס עליהם?$"

SSAqua_RoomNE_Text_PokemaniacEthanSeen:
    .string "אתה מכיר את לילי?\n"
    .string "היא די-ג'יי לוהטת בקאנטו.$"

SSAqua_RoomNE_Text_PokemaniacEthanBeaten:
    .string "גיאאאאה!$"

SSAqua_RoomNE_Text_PokemaniacEthanAfterBattle:
    .string "לילי נחמדה, אבל\n"
    .string "מרי הכי טובה!\p"
    .string "אני רוצה לשמוע את\n"
    .string "תוכניות הרדיו של ג'וטו!$"
