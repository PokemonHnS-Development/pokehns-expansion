VioletCity_TrainerSchool_hns_MapScripts::
	.byte 0

VioletCity_TrainerSchool_EventScript_Earl::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_EarlIntro, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Teacher::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_Teacher, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Boy1::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_GameboyKid1, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Boy2::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_GameboyKid2, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Kid::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_Youngster1, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Girl::
	lock
	faceplayer
	msgbox VioletCity_TrainerSchool_Text_Youngster2, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_EventScript_Twin::
	msgbox VioletCity_TrainerSchool_Text_Twin, MSGBOX_NPC
	end

VioletCity_TrainerSchool_EventScript_BlackBoard::
	lock
	msgbox VioletCity_TrainerSchool_Text_Blackboard, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_TrainerSchool_Text_Twin:
	.string "I'm not a GBA kid, but I love\n"
	.string "playing POKéMON games!\p"
	.string "In the old games, you had to battle\n"
	.string "a lot of wild POKéMON to get enough\l"
	.string "EXP.\p"
	.string "But in newer games, the EXP. SHARE\n"
	.string "makes your POKéMON level up too fast.\p"
	.string "In this game, the EXP. SHARE is\n"
	.string "balanced to put your POKéMON at just\l"
	.string "the right level. Or slightly higher,\l"
	.string "depending on how many battles you do.\p"
	.string "If you want a traditional GEN 1-4\n"
	.string "experiencia, desactiva EXP. SHARE.\l"
	.string "Si quieres una experiencia moderna,\l"
	.string "activa EXP. SHARE.\p"
	.string "¡Tú eliges cómo quieres jugar!$"

VioletCity_TrainerSchool_Text_EarlIntro:
	.string "¡EARL, soy yo!\p"
	.string "¡Maravillosos son los POKéMON!\p"
	.string "¡Te enseñaré a ser un mejor\n"
	.string "ENTRENADOR!$"

VioletCity_TrainerSchool_Text_Teacher:
	.string "Ciertos POKéMON empiezan débiles y\n"
	.string "requieren más EXP para ser\l"
	.string "fuertes que otros.\p"
	.string "Por ejemplo, LARVITAR es muy débil\n"
	.string "pero al final será un\l"
	.string "poderoso TYRANITAR, a costa de\l"
	.string "mucha EXP.\p"
	.string "Solo los ENTRENADORES más\n"
	.string "dedicados deben intentar criar\l"
	.string "POKéMON.$"

VioletCity_TrainerSchool_Text_TeachHowToWin:
	.string "¡Bien! ¡Enseñarte, yo voy!\p"
	.string "En batalla, el POKéMON arriba\n"
	.string "¡sale primero!\p"
	.string "Cambiar el orden puede hacer\n"
	.string "la batalla más fácil, ¡quizás!\p"
	.string "¿Más de mí quieres oír?$"

VioletCity_TrainerSchool_Text_TeachMore:
	.string "Entonces, ¿quieres saber cómo\n"
	.string "¿Tu POKéMON está bien?$"

VioletCity_TrainerSchool_Text_TeachRaiseWell:
	.string "¡Bien! ¡Te enseñaré!\p"
	.string "Si un POKéMON sale en batalla,\n"
	.string "aunque sea un momento,\p"
	.string "ganará algunos puntos de EXP.\n"
	.string "Pon los POKéMON débiles arriba\p"
	.string "¡Para cambiarlos rápido!\n"
	.string "Así, los débiles serán fuertes.\p"
	.string "hemos crecido!$"

VioletCity_TrainerSchool_Text_NoMoreToTeach:
	.string "¡Oh! ¡Qué alumno tan listo!\n"
	.string "¡No tengo nada más que enseñar!\p"
	.string "Si quieres más, ¡habla con\n"
	.string "los alumnos!$"

VioletCity_TrainerSchool_Text_Youngster1:
	.string "POKéMON que antes se creía que\n"
	.string "solo evolucionaban al cambiar\p"
	.string "pueden evolucionar por nivel.\n"
	.string "MACHOKE y GRAVELER evolucionan\p"
	.string "al NIV 38, mientras KADABRA y\n"
	.string "GASTLY evolucionan al NIV 42.\p"
	.string "Ciertos objetos, como la\n"
	.string "COPA METAL, también hacen que\p"
	.string "algunos POKéMON evolucionen\n"
	.string "al subir de nivel llevándolo.$"

VioletCity_TrainerSchool_Text_GameboyKid1:
	.string "¡POKéMON notables de la zona\n"
	.string "se pueden ver en el mapa!\p"
	.string "Pero asegúrate de revisar rutas\n"
	.string "¡de DÍA y de NOCHE!$"

VioletCity_TrainerSchool_Text_GameboyKid2:
	.string "Las BAYAS de la región de JOHTO\n"
	.string "curan y sirven para hacer BALLS.\p"
	.string "Las BAYAS de KANTO sirven para\n"
	.string "bajar los stats de un POKéMON.\p"
	.string "El DOJO de KANTO ayuda a que los\n"
	.string "POKéMON tengan stats perfectos.$"

VioletCity_TrainerSchool_Text_Youngster2:
	.string "Ten en cuenta que tus rivales\n"
	.string "usan equipos con mejor cobertura\l"
	.string "de tipos, así que espera un\l"
	.string "viaje mucho más difícil ahora.$"

VioletCity_TrainerSchool_Text_Blackboard:
	.string "El pizarrón describe\n"
	.string "movimientos MO de POKéMON.\p"
	.string "Las MO, una vez desbloqueadas,\n"
	.string "no necesitan ser enseñadas.$"

VioletCity_TrainerSchool_Text_Notebook:
	.string "Es el cuaderno de este chico...\p"
	.string "Atrapa POKéMON con POKé BALLS.\p"
	.string "Puedes llevar hasta seis contigo.\p"
	.string "¿Seguir leyendo?$"

VioletCity_TrainerSchool_Text_Notebook1:
	.string "Antes de lanzar una POKé BALL,\n"
	.string "debilita primero al objetivo.\p"
	.string "Un POKéMON envenenado o quemado\n"
	.string "es más fácil de atrapar.\p"
	.string "¿Seguir leyendo?$"

VioletCity_TrainerSchool_Text_Notebook2:
	.string "Algunos movimientos confunden.\p"
	.string "La confusión puede hacer que un\n"
	.string "POKéMON se ataque a sí mismo.\p"
	.string "Salir de la batalla elimina la\n"
	.string "confusión.\p"
	.string "¿Seguir leyendo?$"

VioletCity_TrainerSchool_Text_Notebook3:
	.string "Quienes capturan y usan\n"
	.string "POKéMON en batalla son ENTRENADORES\n"
	.string "ENTRENADORES POKéMON.\p"
	.string "Se espera que visiten los\n"
	.string "GIMNASIOS y venzan a otros.\n"
	.string "ENTRENADORES POKéMON.\p"
	.string "¡La siguiente página está... vacía!\p"
	.string "Niño: Je, je, je...\p"
	.string "No he escrito nada más...$"

VioletCity_TrainerSchool_Text_StickerMachine:
	.string "Esta supermáquina imprime datos\n"
	.string "¡salieron como calcomanías!$"
