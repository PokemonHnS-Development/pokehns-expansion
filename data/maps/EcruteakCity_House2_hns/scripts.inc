EcruteakCity_House2_hns_MapScripts::
	.byte 0

Ecruteak_Text_ItemfinderAdventure:
	.string "Ah. ¿Estás en una aventura con\n"
	.string "tus POKéMON?\p"
	.string "Bueno, ¿qué es una aventura sin\n"
	.string "buscar tesoros?\p"
	.string "¿Tengo razón o no?$"

Ecruteak_Text_ItemfinderTrueSpirit:
	.string "¡Bien! Entiendes el verdadero\n"
	.string "espíritu de la aventura.\p"
	.string "¡Me gusta! Toma esto.$"

Ecruteak_Text_ItemfinderExplanation:
	.string "Hay muchos objetos por ahí\n"
	.string "que no se ven a simple vista.\p"
	.string "Usa DOWSING MACHINE para ver si hay\n"
	.string "un objeto en el suelo cerca de ti.\p"
	.string "No muestra el lugar exacto,\n"
	.string "así que tendrás que buscarlo.\p"
	.string "Ah, sí... oí que hay objetos\n"
	.string "en la TORRE QUEMADA de CIUDAD IRIS.$"

Ecruteak_Text_ItemfinderToEachHisOwn:
	.string "Oh… To each his own, I suppose…$"

EcruteakCity_House2_EventScript_ItemFinderMan::
	lock
	faceplayer
	checkitem ITEM_DOWSING_MACHINE
	goto_if_eq VAR_RESULT, TRUE, EcruteakCity_House2_EventScript_AlreadyGotItemfinder
	msgbox Ecruteak_Text_ItemfinderAdventure, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, EcruteakCity_House2_EventScript_GiveItemFinder
	msgbox Ecruteak_Text_ItemfinderToEachHisOwn, MSGBOX_DEFAULT
	closemessage
	release
	end

EcruteakCity_House2_EventScript_GiveItemFinder::
	msgbox Ecruteak_Text_ItemfinderTrueSpirit, MSGBOX_DEFAULT
	giveitem ITEM_DOWSING_MACHINE
EcruteakCity_House2_EventScript_AlreadyGotItemfinder::
	msgbox Ecruteak_Text_ItemfinderExplanation, MSGBOX_DEFAULT
	closemessage
	release
	end


EcruteakCity_House2_EventScript_Book::
	lock
	msgbox Ecruteak_Text_HistoryBook, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, EcruteakCity_House2_EventScript_Book2
	closemessage
	release
	end

EcruteakCity_House2_EventScript_Book2::
	msgbox Ecruteak_Text_TwoTowers, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, TRUE, EcruteakCity_House2_EventScript_Book3
	release
	end

EcruteakCity_House2_EventScript_Book3::
	msgbox Ecruteak_Text_ThreeMon, MSGBOX_DEFAULT
	closemessage
	release
	end

Ecruteak_Text_ItemFinderMan::
	.string "CIUDAD IRIS es una ciudad muy vieja.\n"
	.string "Muchas generaciones pasaron\l"
	.string "su historia en libros como estos.$"

Ecruteak_Text_HistoryBook:
	.string "HISTORIA DE CIUDAD IRIS\p"
	.string "¿Quieres leerlo?$"

Ecruteak_Text_TwoTowers:
	.string "En CIUDAD IRIS, había dos torres.\p"
	.string "Cada torre era el nido de\n"
	.string "poderosos POKéMON voladores.\p"
	.string "Pero una de las torres ardió\n"
	.string "hasta los cimientos.\p"
	.string "No se ha visto a esos dos POKéMON\n"
	.string "desde entonces...\p"
	.string "¿Seguir leyendo?$"

Ecruteak_Text_ThreeMon:
	.string "CIUDAD IRIS también albergó a tres\n"
	.string "POKéMON que corrían por el pueblo.\p"
	.string "Se decía que habían nacido\n"
	.string "del agua, el rayo y el fuego.\p"
	.string "Pero no pudieron contener su\n"
	.string "excesivo poder.\p"
	.string "Dicen que los tres corrieron como el\n"
	.string "viento hacia la pradera.$"
