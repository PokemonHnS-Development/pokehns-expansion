Route47_hns_MapScripts::
	.byte 0


Route47_EventScript_Hiker::
	trainerbattle_single TRAINER_DEVIN_HNS, Route47_Text_HikerSeen, Route47_Text_HikerBeaten
	msgbox Route47_Text_HikerAfter, MSGBOX_AUTOCLOSE
	end

Route47_Text_HikerSeen::
	.string "Anhelar a los demás es...\n"
	.string "lo que es.\p"
	.string "Pero las batallas son batallas,\n"
	.string "¡así que vamos!$"

Route47_Text_HikerBeaten::
	.string "Wahaha!$"

Route47_Text_HikerAfter::
	.string "Tras una batalla siempre debes irte\n"
	.string "con una risa de despedida!$"

Route47_EventScript_Camper::
	trainerbattle_single TRAINER_GRANT_HNS, Route47_Text_CamperSeen, Route47_Text_CamperBeaten
	msgbox Route47_Text_CamperAfter, MSGBOX_AUTOCLOSE
	end

Route47_Text_CamperSeen::
	.string "No me gustan las multitudes, así que\n"
	.string "estoy acampando aquí con mi\l"
	.string "POKéMON!$"

Route47_Text_CamperBeaten::
	.string "Supongo que debo ir más profundo en la\n"
	.string "montaña...$"

Route47_Text_CamperAfter::
	.string "See ya!$"

Route47_EventScript_Thom::
	trainerbattle_double TRAINER_THOM_AND_KAE_HNS, Route47_Text_Couple1Seen, Route47_Text_Couple1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route47_Text_Couple1After1, MSGBOX_AUTOCLOSE
	end

Route47_EventScript_Kae::
	trainerbattle_double TRAINER_THOM_AND_KAE_HNS, Route47_Text_Couple1Seen, Route47_Text_Couple1Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route47_Text_Couple1After2, MSGBOX_AUTOCLOSE
	end

Route47_Text_Couple1Seen::
	.string "THOM: Uno más uno son dos. Pero\nlos dos juntos somos mucho\lmás fuertes!\pKAE: Los dos no somos solo una\npareja aburrida!$"

Route47_Text_Couple1Beaten::
	.string "THOM: No esperaba eso.\lKAE: ¡Tú también eres peculiar!$"

Route47_Text_Couple1After1::
	.string "THOM: ¡Parece que tu poder\nes imposible de predecir!$"

Route47_Text_Couple1After2::
	.string "KAE: Pensé que eras un simple\nentrenador solitario. ¡Me equivoqué!$"

Route47_EventScript_Duff::
	trainerbattle_double TRAINER_DUFF_AND_EDA_HNS, Route47_Text_Couple2Seen, Route47_Text_Couple2Beaten, Route104_Text_GinaNotEnoughMons
	special GetPlayerBigGuyGirlString
	msgbox Route47_Text_Couple2After1, MSGBOX_AUTOCLOSE
	end

Route47_EventScript_Eda::
	trainerbattle_double TRAINER_DUFF_AND_EDA_HNS, Route47_Text_Couple2Seen, Route47_Text_Couple2Beaten, Route104_Text_GinaNotEnoughMons
	msgbox Route47_Text_Couple2After2, MSGBOX_AUTOCLOSE
	end

Route47_Text_Couple2Seen::
	.string "DUFF: Cuidar a mi novia\n¡hace que mi corazón se eleve!\pEDA: Los sentimientos de mi\ncorazón por mi novio son\l¡anchos y profundos como el mar!$"

Route47_Text_Couple2Beaten::
	.string "DUFF: No estuve a tu altura...\lEDA: Eres realmente increíble...$"

Route47_Text_Couple2After1::
	.string "DUFF: ¡Gracias por esta\nbatalla impresionante! ¡Adiós!$"

Route47_Text_Couple2After2::
	.string "EDA: ¡Tú también deberías\nbuscar una pareja increíble!$"

Route47_EventScript_Sage::
	lock
	faceplayer
	msgbox EmbeddedTower_Text_OldManIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

EmbeddedTower_Text_OldManIntro:
	.string "¡Hola, qué tal!\p"
	.string "Dicen que tras este hueco solía\n"
	.string "haber una torre que llegaba alto\l"
	.string "el cielo.\p"
	.string "Dicen que era una torre bastante\n"
	.string "extraña, con la mitad incrustada\l"
	.string "en el acantilado.\p"
	.string "No era solo una torre alta que\n"
	.string "llegaba hasta el cielo, ¡sino que\l"
	.string "bajaba hasta el subsuelo!\p"
	.string "¡Se rumorea que incluso llegaba\n"
	.string "hasta el fondo del océano!\p"
	.string "En resumen, las ruinas conectaban\n"
	.string "el cielo, la tierra y el mar\l"
	.string "entre sí...\p"
	.string "Casi toda la torre se derrumbó,\n"
	.string "y lo único que queda es\l"
	.string "la entrada y su interior, donde\l"
	.string "verás patrones extraños.$"

Route47_EventScript_Item_Pearl::
    finditem ITEM_PEARL
    end

Route47_EventScript_Item_Revive::
    finditem ITEM_REVIVE
    end

Route47_EventScript_Item_WhiteFlute::
    finditem ITEM_WHITE_FLUTE
    end

Route47_EventScript_Item_Stardust::
	finditem ITEM_STARDUST
	end

Route47_EventScript_Item_LuckyPunch::
	finditem ITEM_LUCKY_PUNCH
	end

Route47_EventScript_Chinchou::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CHINCHOU, CRY_MODE_NORMAL
	msgbox Route47_Text_Chinchou, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route47_Text_Chinchou:
	.string "CHINCHOU: Chou!$"
