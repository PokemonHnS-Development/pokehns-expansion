.equ REQUIRED_CAUGHT_MONS, 40

Route16_NorthEntrance_2F_Frlg_MapScripts::
	.byte 0

Route16_NorthEntrance_2F_EventScript_LittleBoy::
	msgbox Route16_NorthEntrance_2F_Text_OnBikeRideWithGirlfriend, MSGBOX_NPC
	end

Route16_NorthEntrance_2F_EventScript_LittleGirl::
	msgbox Route16_NorthEntrance_2F_Text_RidingTogetherOnNewBikes, MSGBOX_NPC
	end

Route16_NorthEntrance_2F_EventScript_LeftBinoculars::
	msgbox Route16_NorthEntrance_2F_Text_ItsCeladonDeptStore, MSGBOX_SIGN
	end

Route16_NorthEntrance_2F_EventScript_RightBinoculars::
	msgbox Route16_NorthEntrance_2F_Text_LongPathOverWater, MSGBOX_SIGN
	end

Route16_NorthEntrance_2F_EventScript_Aide::
	lock
	faceplayer
	call Route16_NorthEntrance_2F_EventScript_GetAideRequestInfo
	goto_if_set FLAG_GOT_AMULET_COIN_FROM_OAKS_AIDE, Route16_NorthEntrance_2F_EventScript_AlreadyGotAmuletCoin
	msgbox Route16_NorthEntrance_2F_Text_GiveAmuletCoinIfCaught40, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Aide_EventScript_DeclineCheckMons
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetFrlgPokedexCount
	buffernumberstring STR_VAR_3, VAR_0x8006
	call Route16_NorthEntrance_2F_EventScript_GetAideRequestInfo
	goto_if_lt VAR_0x8006, REQUIRED_CAUGHT_MONS, Aide_EventScript_HaventCaughtEnough
	msgbox Route16_NorthEntrance_2F_Text_GreatHereYouGo
	checkitemspace ITEM_AMULET_COIN
	goto_if_eq VAR_RESULT, FALSE, Aide_EventScript_NoRoomForItem
	giveitem_msg Route16_NorthEntrance_2F_Text_ReceivedAmuletCoinFromAide, ITEM_AMULET_COIN
	setflag FLAG_GOT_AMULET_COIN_FROM_OAKS_AIDE
	msgbox Route16_NorthEntrance_2F_Text_ExplainAmuletCoin
	release
	end

Route16_NorthEntrance_2F_EventScript_AlreadyGotAmuletCoin::
	msgbox Route16_NorthEntrance_2F_Text_ExplainAmuletCoin
	release
	end

Route16_NorthEntrance_2F_EventScript_GetAideRequestInfo::
	buffernumberstring STR_VAR_1, REQUIRED_CAUGHT_MONS
	bufferitemname STR_VAR_2, ITEM_AMULET_COIN
	return

Route16_NorthEntrance_2F_Text_OnBikeRideWithGirlfriend::
	.string "Estoy en un paseo relajante\n"
	.string "en mi bici nueva con mi novia.$"

Route16_NorthEntrance_2F_Text_RidingTogetherOnNewBikes::
	.string "Vamos a pasear juntos en\n"
	.string "new bikes.$"

Route16_NorthEntrance_2F_Text_ItsCeladonDeptStore::
	.string "Veamos qué tienen los prismáticos\n"
	.string "para mostrar…\p"
	.string "¡Es el ALMACÉN DE AZALEA!$"

Route16_NorthEntrance_2F_Text_LongPathOverWater::
	.string "Veamos qué tienen los prismáticos\n"
	.string "para mostrar…\p"
	.string "Hay un largo camino sobre el agua\n"
	.string "lejano.$"

Route16_NorthEntrance_2F_Text_GiveAmuletCoinIfCaught40::
	.string "¡Hola! ¿Me recuerdas?\n"
	.string "I'm one of PROF. OAK's AIDES.\p"
	.string "If your POKéDEX has complete data\n"
	.string "con 40 especies, se supone que\l"
	.string "te daré una recompensa.\p"
	.string "El PROF. OAK me encargó un\n"
	.string "AMULETO para ti.\p"
	.string "Así que, {PLAYER}, te pregunto.\p"
	.string "¿Ya reuniste datos de al menos\n"
	.string "40 kinds of POKéMON?$"

Route16_NorthEntrance_2F_Text_GreatHereYouGo::
	.string "¡Genial! Has capturado o tenido\n"
	.string "{STR_VAR_3} tipos de POKéMON!\p"
	.string "¡Felicidades!\n"
	.string "¡Toma!$"

Route16_NorthEntrance_2F_Text_ReceivedAmuletCoinFromAide::
	.string "{PLAYER} recibió la MONEDA\n"
	.string "AMULETO del AYUDANTE.$"

Route16_NorthEntrance_2F_Text_ExplainAmuletCoin::
	.string "La MONEDA AMULETO es un objeto\n"
	.string "held by a POKéMON.\p"
	.string "If the POKéMON appears in a winning\n"
	.string "que da más dinero al batallar.$"

