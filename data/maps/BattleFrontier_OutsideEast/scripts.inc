BattleFrontier_OutsideEast_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_OutsideEast_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideEast_OnTransition
	.byte 0

BattleFrontier_OutsideEast_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

BattleFrontier_OutsideEast_OnTransition:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	call_if_unset FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_ShowSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_ShowSudowoodo::
	clearflag FLAG_HIDE_BATTLE_FRONTIER_SUDOWOODO
	return

BattleFrontier_OutsideEast_EventScript_BattleTowerSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign::
	msgbox BattleFrontier_OutsideEast_Text_BattlePalaceSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattleArenaSign::
	msgbox BattleFrontier_OutsideEast_Text_BattleArenaSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign::
	msgbox BattleFrontier_OutsideEast_Text_BattlePyramidSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_NinjaBoy::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man1::
	msgbox BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Hiker::
	msgbox BattleFrontier_OutsideEast_Text_PyramidTooHarsh, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_HexManiac::
	msgbox BattleFrontier_OutsideEast_Text_ThriveInDarkness, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt1::
	msgbox BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Cook::
	lock
	msgbox BattleFrontier_OutsideEast_Text_BelieveInYouBuddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_OutsideEast_EventScript_RichBoy::
	msgbox BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_ExpertF::
	msgbox BattleFrontier_OutsideEast_Text_OnceBeatGymLeader, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_TriathleteF::
	msgbox BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Twin::
	msgbox BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_TriathleteM::
	msgbox BattleFrontier_OutsideEast_Text_DidScottBringYouHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Sudowoodo::
	lock
	faceplayer
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_FRONTIER_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	release
	end

BattleFrontier_OutsideEast_EventScript_WaterSudowoodo::
	lock
	faceplayer
	special DoWateringBerryTreeAnim
	waitstate
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_FRONTIER_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	msgbox gText_Sudowoodo_Attacked, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SUDOWOODO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_FRONTIER_SUDOWOODO
	setwildbattle SPECIES_SUDOWOODO, 40
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	setflag FLAG_DEFEATED_SUDOWOODO
	release
	end

BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo::
	setflag FLAG_DEFEATED_SUDOWOODO
	goto Common_EventScript_RemoveStaticPokemon
	end

BattleFrontier_OutsideEast_Movement_SudowoodoShake:
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	step_end

BattleFrontier_OutsideEast_EventScript_Maniac1::
	msgbox BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Girl::
	msgbox BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_PsychicM::
	msgbox BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man3::
	msgbox BattleFrontier_OutsideEast_Text_GotWipedOut, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman1::
	msgbox BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman2::
	msgbox BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt2::
	msgbox BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Maniac2::
	lock
	msgbox BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Woman3::
	lock
	msgbox BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RankingHallSign::
	msgbox BattleFrontier_OutsideEast_Text_RankingHallSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_ExchangeCornerSign::
	msgbox BattleFrontier_OutsideEast_Text_ExchangeCornerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_Gentleman::
	msgbox BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_OldWoman::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone
	msgbox BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone::
	msgbox BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Camper::
	msgbox BattleFrontier_OutsideEast_Text_StickyMonWithLongTail, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Text_BattleTowerSign:
	.string "¡Esta es la TORRE DE COMBATE!\n"
	.string "¡Sé el más fuerte en racha!\l"
	.string "TRAINER!$"

BattleFrontier_OutsideEast_Text_BattlePalaceSign:
	.string "¡Este es el PALACIO DE COMBATE!\n"
	.string "¡Enfócate en las batallas POKéMON!$"

BattleFrontier_OutsideEast_Text_BattleArenaSign:
	.string "¡Esta es la ARENA DE COMBATE!\n"
	.string "¡Que se reúnan los mejores equipos!$"

BattleFrontier_OutsideEast_Text_BattlePyramidSign:
	.string "¡Esta es la PIRÁMIDE DE COMBATE!\n"
	.string "¡Avanza en la Misión de Combate!$"

BattleFrontier_OutsideEast_Text_RankingHallSign:
	.string "SALÓN DE RÁNKINGS DE LA FRONTERA\n"
	.string "¡Busca romper nuevos récords!$"

BattleFrontier_OutsideEast_Text_ExchangeCornerSign:
	.string "CANJE DE PUNTOS DE COMBATE\n"
	.string "¡Canjea tus Puntos de Combate!$"

BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial:
	.string "¡Guau!\n"
	.string "¡Es enorme!\p"
	.string "La BATTLE TOWER es especial.\n"
	.string "Es distinta a las demás.$"

BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier:
	.string "Mi gran ambición es conquistar\n"
	.string "la BATTLE FRONTIER y la LIGA\l"
	.string "POKéMON planta.\p"
	.string "Y si mi sueño se hace realidad...\p"
	.string "le preguntaré a MIMI, la vecina,\n"
	.string "¡si quiere ser mi amiga!$"

BattleFrontier_OutsideEast_Text_PyramidTooHarsh:
	.string "¡La BATTLE PYRAMID es muy dura!\n"
	.string "¡No logro llegar a la cima!\p"
	.string "Como no tengo opciones, tal vez\n"
	.string "pueda escalar por fuera...$"

BattleFrontier_OutsideEast_Text_ThriveInDarkness:
	.string "Prospero en la oscuridad...\n"
	.string "Sí... ¿Qué es digno de mí?\l"
	.string "Nada menos que la PIRÁMIDE BATALLA...\p"
	.string "¿Qué dices de vagar en la oscuridad\n"
	.string "y en total y absoluta desesperación?$"

BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam:
	.string "No dormí por una semana, ¡pero\n"
	.string "armé el equipo definitivo!\p"
	.string "No me veo perdiendo, en serio.\n"
	.string "¡Asaltaremos la ARENA BATALLA!$"

BattleFrontier_OutsideEast_Text_DidScottBringYouHere:
	.string "¿SCOTT también te trajo aquí?\n"
	.string "¿Qué pasa con ese tipo?\p"
	.string "Parece que realmente sabe\n"
	.string "cómo hallar TRAINERS con talento,\p"
	.string "pero nunca lo he visto luchar\n"
	.string "en persona.$"

BattleFrontier_OutsideEast_Text_BelieveInYouBuddy:
	.string "¡ZIGG!\n"
	.string "¡Confío en ti, amiguito!\p"
	.string "¡Le daré a mi ZIGG sus premios\n"
	.string "favoritos si ganas!$"

BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant:
	.string "ZIGZAGOON looks vacant…$"

BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody:
	.string "Dicen que soy un entrometido,\n"
	.string "pero no puedo evitarlo.\p"
	.string "¡Tienes el sombrero torcido!\n"
	.string "¡Oh, no, basura en el suelo!\l"
	.string "¡Uy, ya casi es hora de cenar!\p"
	.string "No sé si pueda soportar solo\n"
	.string "mirar en el BATTLE PALACE…$"

BattleFrontier_OutsideEast_Text_OnceBeatGymLeader:
	.string "Quizá no luzca muy impresionante,\n"
	.string "pero una vez vencí a un LÍDER de GYM.\p"
	.string "Quién sabe, tal vez debería intentar\n"
	.string "buscar la gloria otra vez.$"

BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles:
	.string "Soy rápido en mi BIKE, y eso aplica\n"
	.string "también a mi forma de luchar.\p"
	.string "Gano los combates en un abrir y\n"
	.string "¡un ojo!$"

BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon:
	.string "Soy mejor que mi papá\n"
	.string "con los POKéMON.$"

BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy:
	.string "¡Dale, mi dulce bebé!\n"
	.string "¡Consigue victorias para papá!\p"
	.string "Eres igual que tu madre,\n"
	.string "¡así que dominarás!$"

BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena:
	.string "No fue fácil llegar aquí,\n"
	.string "pero oí de una chica preciosa\l"
	.string "en la BATTLE ARENA.\p"
	.string "En vez de ella, ¿sabes qué\n"
	.string "¿Encontré?\p"
	.string "¡Una multitud de artistas marciales\n"
	.string "sudorosos, apestosos y primitivos!$"

BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere:
	.string "A veces veo entrar ahí a un anciano\n"
	.string "que parece ser muy importante.\p"
	.string "Tiene unos POKéMON increíbles.\n"
	.string "Aunque parece ser muy amable.$"

BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid:
	.string "¿Lo conoces?\n"
	.string "¿La leyenda de la PIRÁMIDE BATALLA?\p"
	.string "Cuando un TRAINER confiado\n"
	.string "alcanza la cima dorada,\l"
	.string "aparecerá un hombre entre hombres.\p"
	.string "¿No conoces esa leyenda?\n"
	.string "¡Bueno, claro que no!\l"
	.string "¡Me lo acabo de inventar!\p"
	.string "¿Qué se supone que significa?\n"
	.string "¡Eso, amigo, no lo puedo decir!$"

BattleFrontier_OutsideEast_Text_GotWipedOut:
	.string "¡Cielos! ¡No puede ser!\n"
	.string "¡Nunca había perdido antes!\p"
	.string "¡Pero me barrieron sin ninguna\n"
	.string "piedad!\p"
	.string "¡¿Y luego me dicen que no tengo\n"
	.string "talento?! ¡No puede ser!$"

BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower:
	.string "Este tipo se topó con un\n"
	.string "ENTRENADOR muy duro en el reto de\l"
	.string "la TORRE DE COMBATE.\p"
	.string "Míralo ahora...\p"
	.string "Debes tener cuidado si alguna vez\n"
	.string "vas a la TORRE DE COMBATE.$"

BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll:
	.string "¡Sí!\n"
	.string "¡Ya tengo suficientes Puntos Batalla!\p"
	.string "¡Canjearé otros puntos por un\n"
	.string "MUÑECO gigante!$"

BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere:
	.string "¡Ah, sí, está bien!\n"
	.string "¡Así que este es el SALÓN DE RANKING!\p"
	.string "Quiero pasar a la historia como\n"
	.string "un súper campeón y que mi nombre\l"
	.string "quede registrado aquí para siempre.$"

BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou:
	.string "Contigo a mi lado, todo es posible.$"

BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome:
	.string "¡Ay, cariño, eres maravilloso!\p"
	.string "¡Ay, ya no puedo esperar más!\p"
	.string "¡Vamos a una MULTI BATTLE ROOM\n"
	.string "en este mismo instante!\p"
	.string "Si nos unimos en el BATTLE SALON,\n"
	.string "el poder de nuestro amor vencerá\l"
	.string "a todo el que encontremos.\p"
	.string "¡Ante nosotros, cariño, todo\n"
	.string "caerá como fichas de dominó!$"

BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers:
	.string "El BATTLE FRONTIER no es solo\n"
	.string "para ENTRENADORES rudos.\p"
	.string "Parece que han invitado a mucha\n"
	.string "gente con habilidades especiales.\p"
	.string "Ese hombre, SCOTT...\p"
	.string "Quizás construyó este lugar para\n"
	.string "un objetivo más grande...$"

BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle:
	.string "Disculpa, jovencito.\n"
	.string "¿Tienes buena vista?\p"
	.string "Hay un árbol raro más adelante y,\n"
	.string "según yo, parece moverse.$"

BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere:
	.string "Disculpa, jovencito.\n"
	.string "¿Tienes buena memoria?\p"
	.string "Tengo la sensación de que antes\n"
	.string "había un árbol raro por aquí.$"

BattleFrontier_OutsideEast_Text_StickyMonWithLongTail:
	.string "I…\n"
	.string "¡Lo vi!\p"
	.string "Había un POKéMON pegajoso\n"
	.string "con una cola larga más adelante!\p"
	.string "Se escondía bajo una roca y\n"
	.string "¡no dejaba de mirarme!$"
