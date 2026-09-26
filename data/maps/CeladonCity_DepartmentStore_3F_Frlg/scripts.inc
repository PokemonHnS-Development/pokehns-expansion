CeladonCity_DepartmentStore_3F_Frlg_MapScripts::
	.byte 0

CeladonCity_DepartmentStore_3F_EventScript_CounterTutor::
	goto EventScript_CounterTutor
	end

CeladonCity_DepartmentStore_3F_EventScript_GBAKid1::
	msgbox CeladonCity_DepartmentStore_3F_Text_OTStandsForOriginalTrainer, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_3F_EventScript_GBAKid2::
	msgbox CeladonCity_DepartmentStore_3F_Text_BuddyTradingKangaskhanForHaunter, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_3F_EventScript_GBAKid3::
	msgbox CeladonCity_DepartmentStore_3F_Text_HaunterEvolvedOnTrade, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_3F_EventScript_LittleGirl::
	msgbox CeladonCity_DepartmentStore_3F_Text_CanIdentifyTradeMonsByID, MSGBOX_NPC
	end

CeladonCity_DepartmentStore_3F_EventScript_SuperNES::
	msgbox CeladonCity_DepartmentStore_3F_Text_ItsSuperNES, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_3F_EventScript_TV1::
	msgbox CeladonCity_DepartmentStore_3F_Text_AnRPG, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_3F_EventScript_TV2::
	msgbox CeladonCity_DepartmentStore_3F_Text_SportsGame, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_3F_EventScript_TV3::
	msgbox CeladonCity_DepartmentStore_3F_Text_PuzzleGame, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_3F_EventScript_TV4::
	msgbox CeladonCity_DepartmentStore_3F_Text_FightingGame, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_3F_EventScript_FloorSign::
	msgbox CeladonCity_DepartmentStore_3F_Text_TVGameShop, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_3F_EventScript_Poster::
	msgbox CeladonCity_DepartmentStore_3F_Text_RedGreenBothArePokemon, MSGBOX_SIGN
	end

CeladonCity_DepartmentStore_3F_Text_OTStandsForOriginalTrainer::
	.string "Los POKéMON capturados se registran\n"
	.string "con un No. de ID y el OE.\p"
	.string "OT significa “Entrenador Original” -\n"
	.string "el ENTRENADOR que lo atrapó primero.$"

CeladonCity_DepartmentStore_3F_Text_BuddyTradingKangaskhanForHaunter::
	.string "¡De acuerdo!\p"
	.string "Mi amigo me va a intercambiar su\n"
	.string "KANGASKHAN por mi HAUNTER!$"

CeladonCity_DepartmentStore_3F_Text_HaunterEvolvedOnTrade::
	.string "¡Vamos, HAUNTER!\p"
	.string "¡Me encanta HAUNTER!\n"
	.string "¡Los colecciono!\p"
	.string "¿Eh?\p"
	.string "HAUNTER se transformó en otro\n"
	.string "¡POKéMON al ser intercambiado!$"

CeladonCity_DepartmentStore_3F_Text_CanIdentifyTradeMonsByID::
	.string "Puedes identificar los POKéMON que\n"
	.string "en los intercambios por su número de ID.$"

CeladonCity_DepartmentStore_3F_Text_ItsSuperNES::
	.string "Es un Super Nintendo.$"

CeladonCity_DepartmentStore_3F_Text_AnRPG::
	.string "¡Un RPG!\n"
	.string "¡No hay tiempo para eso!$"

CeladonCity_DepartmentStore_3F_Text_SportsGame::
	.string "¡Un juego de deportes!\n"
	.string "¡A papá le gustará eso!$"

CeladonCity_DepartmentStore_3F_Text_PuzzleGame::
	.string "¡Un juego de rompecabezas!\n"
	.string "¡Parece adictivo!$"

CeladonCity_DepartmentStore_3F_Text_FightingGame::
	.string "¡Un juego de lucha!\n"
	.string "¡Parece difícil!$"

CeladonCity_DepartmentStore_3F_Text_TVGameShop::
	.string "3F: TIENDA DE VIDEOJUEGOS$"

CeladonCity_DepartmentStore_3F_Text_RedGreenBothArePokemon::
	.string "¡Rojo y Verde!\n"
	.string "¡Ambos son POKéMON!$"

Text_CounterTeach::
	.string "¡Oh, hola!\n"
	.string "¡Por fin terminé POKéMON!\p"
	.string "¿Aún no terminas? ¿Qué tal si te enseño\n"
	.string "¿Quieres aprender un buen movimiento?\p"
	.string "El movimiento que tengo en mente es\n"
	.string "CONTRAATAQUE.\p"
	.string "No como el que me apoyo,\n"
	.string "¡Ojo!$"

Text_CounterDeclined::
	.string "¿No te interesa? Ven a ver\n"
	.string "me si cambias de opinión.$"

Text_CounterWhichMon::
	.string "¿A qué POKéMON le enseño\n"
	.string "Contraataque a...?$"

Text_CounterTaught::
	.string "¿Estás usando ese movimiento CONTRAATAQUE\n"
	.string "¿Le enseñé a tu POKéMON?$"
