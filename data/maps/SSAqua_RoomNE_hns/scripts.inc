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
    .string "¿Estás solo?\n"
    .string "¡Entonces luchemos!$"

SSAqua_RoomNE_Text_HikerNolandBeaten:
    .string "That's too much to handle!$"

SSAqua_RoomNE_Text_HikerNolandAfterBattle:
    .string "Me pregunto si habrá\n"
    .string "¿montañas que escalar en KANTO?$"

SSAqua_RoomNE_Text_PokemaniacEthanSeen:
    .string "¿Conoces a LILY?\n"
    .string "Es una DJ genial en KANTO.$"

SSAqua_RoomNE_Text_PokemaniacEthanBeaten:
    .string "Gyaaaah!$"

SSAqua_RoomNE_Text_PokemaniacEthanAfterBattle:
    .string "LILY es agradable, pero\n"
    .string "¡MARY es la mejor!\n"
    .string "Quiero escuchar\n"
    .string "la radio de JOHTO\n"
    .string "¡programas!$"
