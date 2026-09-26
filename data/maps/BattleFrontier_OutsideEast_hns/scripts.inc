BattleFrontier_OutsideEast_hns_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_OutsideEast_OnResume_hns
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideEast_OnTransition_hns
	.byte 0

BattleFrontier_OutsideEast_OnResume_hns:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo_hns
	end

BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo_hns::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

BattleFrontier_OutsideEast_OnTransition_hns:
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	call_if_unset FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_ShowSudowoodo_hns
	end

BattleFrontier_OutsideEast_EventScript_ShowSudowoodo_hns::
	clearflag FLAG_HIDE_BATTLE_FRONTIER_SUDOWOODO
	return

BattleFrontier_OutsideEast_EventScript_BattleTowerSign_hns::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerSign_hns, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign_hns::
	msgbox BattleFrontier_OutsideEast_Text_BattlePalaceSign_hns, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattleArenaSign_hns::
	msgbox BattleFrontier_OutsideEast_Text_BattleArenaSign_hns, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign_hns::
	msgbox BattleFrontier_OutsideEast_Text_BattlePyramidSign_hns, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_NinjaBoy_hns::
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man1_hns::
	msgbox BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Hiker_hns::
	msgbox BattleFrontier_OutsideEast_Text_PyramidTooHarsh_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_HexManiac_hns::
	msgbox BattleFrontier_OutsideEast_Text_ThriveInDarkness_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt1_hns::
	msgbox BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Cook_hns::
	lock
	msgbox BattleFrontier_OutsideEast_Text_BelieveInYouBuddy_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Zigzagoon_hns::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant_hns, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_OutsideEast_EventScript_RichBoy_hns::
	msgbox BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_ExpertF_hns::
	msgbox BattleFrontier_OutsideEast_Text_OnceBeatGymLeader_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_TriathleteF_hns::
	msgbox BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Twin_hns::
	msgbox BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man2_hns::
	lock
	msgbox BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_TriathleteM_hns::
	msgbox BattleFrontier_OutsideEast_Text_DidScottBringYouHere_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Sudowoodo_hns::
	lock
	faceplayer
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_FRONTIER_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake_hns
	waitmovement 0
	release
	end

BattleFrontier_OutsideEast_EventScript_WaterSudowoodo_hns::
	lock
	faceplayer
	special DoWateringBerryTreeAnim
	waitstate
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_FRONTIER_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake_hns
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
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo_hns
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo_hns
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo_hns
	setflag FLAG_DEFEATED_SUDOWOODO
	release
	end

BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo_hns::
	setflag FLAG_DEFEATED_SUDOWOODO
	goto Common_EventScript_RemoveStaticPokemon
	end

BattleFrontier_OutsideEast_Movement_SudowoodoShake_hns:
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

BattleFrontier_OutsideEast_EventScript_Maniac1_hns::
	msgbox BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Girl_hns::
	msgbox BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_PsychicM_hns::
	msgbox BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man3_hns::
	msgbox BattleFrontier_OutsideEast_Text_GotWipedOut_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman1_hns::
	msgbox BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman2_hns::
	msgbox BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt2_hns::
	msgbox BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Maniac2_hns::
	lock
	msgbox BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Woman3_hns::
	lock
	msgbox BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RankingHallSign_hns::
	msgbox BattleFrontier_OutsideEast_Text_RankingHallSign_hns, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_ExchangeCornerSign_hns::
	msgbox BattleFrontier_OutsideEast_Text_ExchangeCornerSign_hns, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_Gentleman_hns::
	msgbox BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_OldWoman_hns::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_OldWoman_hnsSudowoodoGone_hns
	msgbox BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_OldWoman_hnsSudowoodoGone_hns::
	msgbox BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere_hns, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Camper_hns::
	msgbox BattleFrontier_OutsideEast_Text_StickyMonWithLongTail_hns, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Text_BattleTowerSign_hns:
	.string "¡Esta es la TORRE DE COMBATE!\n"
	.string "¡Sé el más fuerte en racha!\l"
	.string "TRAINER!$"

BattleFrontier_OutsideEast_Text_BattlePalaceSign_hns:
	.string "¡Este es el PALACIO DE COMBATE!\n"
	.string "¡Enfócate en las batallas POKéMON!$"

BattleFrontier_OutsideEast_Text_BattleArenaSign_hns:
	.string "¡Esta es la ARENA DE COMBATE!\n"
	.string "¡Que se reúnan los mejores equipos!$"

BattleFrontier_OutsideEast_Text_BattlePyramidSign_hns:
	.string "¡Esta es la PIRÁMIDE DE COMBATE!\n"
	.string "¡Avanza en la Misión de Combate!$"

BattleFrontier_OutsideEast_Text_RankingHallSign_hns:
	.string "SALÓN DE RÁNKINGS DE LA FRONTERA\n"
	.string "¡Busca romper nuevos récords!$"

BattleFrontier_OutsideEast_Text_ExchangeCornerSign_hns:
	.string "CANJE DE PUNTOS DE COMBATE\n"
	.string "¡Canjea tus Puntos de Combate!$"

BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial_hns:
	.string "¡Guau!\n"
	.string "¡Es enorme!\p"
	.string "La BATTLE TOWER es especial.\n"
	.string "Es distinta a las demás.$"

BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier_hns:
	.string "Mi gran ambición es conquistar\n"
	.string "la BATTLE FRONTIER y la LIGA\l"
	.string "POKéMON planta.\p"
	.string "Y si mi sueño se hace realidad...\p"
	.string "le preguntaré a MIMI, la vecina,\n"
	.string "¡si quiere ser mi amiga!$"

BattleFrontier_OutsideEast_Text_PyramidTooHarsh_hns:
	.string "¡La BATTLE PYRAMID es muy dura!\n"
	.string "¡No logro llegar a la cima!\p"
	.string "Como no tengo opciones, tal vez\n"
	.string "pueda escalar por fuera...$"

BattleFrontier_OutsideEast_Text_ThriveInDarkness_hns:
	.string "Prospero en la oscuridad...\n"
	.string "Sí... ¿Qué es digno de mí?\l"
	.string "Nada menos que la PIRÁMIDE BATALLA...\p"
	.string "¿Qué dices de vagar en la oscuridad\n"
	.string "y en total y absoluta desesperación?$"

BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam_hns:
	.string "No dormí por una semana, ¡pero\n"
	.string "armé el equipo definitivo!\p"
	.string "No creo que pueda perder, en serio.\n"
	.string "¡Asaltaremos la ARENA BATALLA!$"

BattleFrontier_OutsideEast_Text_DidScottBringYouHere_hns:
	.string "¿SCOTT también te trajo aquí?\n"
	.string "¿Qué pasa con ese tipo?\p"
	.string "Parece que realmente sabe\n"
	.string "cómo hallar TRAINERS con talento,\p"
	.string "pero nunca lo he visto pelear\n"
	.string "en persona.$"

BattleFrontier_OutsideEast_Text_BelieveInYouBuddy_hns:
	.string "¡ZIGG!\n"
	.string "¡Confío en ti, amiguito!\p"
	.string "¡Le daré a mi ZIGG sus premios\n"
	.string "favoritos si ganas!$"

BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant_hns:
	.string "ZIGZAGOON parece distraído...$"

BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody_hns:
	.string "Dicen que soy un entrometido,\n"
	.string "pero no puedo evitarlo.\p"
	.string "¡Tienes el sombrero torcido!\n"
	.string "¡Oh, no, basura en el suelo!\l"
	.string "¡Uy, ya casi es hora de cenar!\p"
	.string "No sé si pueda soportar solo\n"
	.string "mirar en el BATTLE PALACE...$"

BattleFrontier_OutsideEast_Text_OnceBeatGymLeader_hns:
	.string "Quizá no luzca muy impresionante,\n"
	.string "pero una vez vencí a un LÍDER de GYM.\p"
	.string "Quién sabe, tal vez debería intentar\n"
	.string "buscar la gloria otra vez.$"

BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles_hns:
	.string "Soy rápido en mi BIKE, y eso aplica\n"
	.string "también a mi forma de luchar.\p"
	.string "Gano los combates en un abrir y\n"
	.string "¡un ojo!$"

BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon_hns:
	.string "Soy mejor que mi papá\n"
	.string "con los POKéMON.$"

BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy_hns:
	.string "¡Dale, mi dulce bebé!\n"
	.string "¡Consigue victorias para papá!\p"
	.string "Eres igual que tu madre,\n"
	.string "¡así que dominarás!$"

BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena_hns:
	.string "No fue fácil llegar aquí,\n"
	.string "pero oí de una chica preciosa\l"
	.string "en la BATTLE ARENA.\p"
	.string "En vez de ella, ¿sabes qué\n"
	.string "¿Encontré?\p"
	.string "¡Una multitud de artistas marciales\n"
	.string "sudorosos, apestosos y primitivos!$"

BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere_hns:
	.string "A veces veo entrar ahí a un anciano\n"
	.string "que parece ser muy importante.\p"
	.string "Tiene unos POKéMON increíbles.\n"
	.string "Aunque parece ser muy amable.$"

BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid_hns:
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

BattleFrontier_OutsideEast_Text_GotWipedOut_hns:
	.string "¡Cielos! ¡No puede ser!\n"
	.string "¡Nunca había perdido antes!\p"
	.string "¡Pero me barrieron sin ninguna\n"
	.string "piedad!\p"
	.string "¡¿Y luego me dicen que no tengo\n"
	.string "talento?! ¡No puede ser!$"

BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower_hns:
	.string "Este tipo se topó con un\n"
	.string "ENTRENADOR muy duro en el reto de\l"
	.string "la TORRE DE COMBATE.\p"
	.string "Míralo ahora...\p"
	.string "Debes tener cuidado si alguna vez\n"
	.string "vas a la TORRE DE COMBATE.$"

BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll_hns:
	.string "¡Sí!\n"
	.string "¡Ya tengo suficientes Puntos Batalla!\p"
	.string "¡Canjearé otros puntos por un\n"
	.string "MUÑECO gigante!$"

BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere_hns:
	.string "¡Ah, sí, está bien!\n"
	.string "¡Así que este es el SALÓN DE RANKING!\p"
	.string "Quiero pasar a la historia como\n"
	.string "un súper campeón y que mi nombre\l"
	.string "quede registrado aquí para siempre.$"

BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou_hns:
	.string "Contigo a mi lado, lo puedo todo.$"

BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome_hns:
	.string "¡Ay, cariño, eres maravilloso!\p"
	.string "¡Ay, ya no puedo esperar más!\p"
	.string "¡Vamos a una SALA MULTI\n"
	.string "en este mismo instante!\p"
	.string "Si nos unimos en el BATTLE SALON,\n"
	.string "el poder de nuestro amor vencerá\l"
	.string "a todo el que encontremos.\p"
	.string "¡Ante nosotros, cariño, todo\n"
	.string "caerá como fichas de dominó!$"

BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers_hns:
	.string "El BATTLE FRONTIER no es solo\n"
	.string "para ENTRENADORES rudos.\p"
	.string "Parece que han invitado a mucha\n"
	.string "gente con habilidades especiales.\p"
	.string "Ese hombre, SCOTT...\p"
	.string "Quizás construyó este lugar para\n"
	.string "un objetivo más grande...$"

BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle_hns:
	.string "Disculpa, jovencito.\n"
	.string "¿Tienes buena vista?\p"
	.string "Hay un árbol raro más adelante y,\n"
	.string "según yo, parece moverse.$"

BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere_hns:
	.string "Disculpa, jovencito.\n"
	.string "¿Tienes buena memoria?\p"
	.string "Tengo la sensación de que antes\n"
	.string "había un árbol raro por aquí.$"

BattleFrontier_OutsideEast_Text_StickyMonWithLongTail_hns:
	.string "I...\n"
	.string "¡Lo vi!\p"
	.string "Había un POKéMON pegajoso\n"
	.string "con una cola larga más adelante!\p"
	.string "Se escondía bajo una roca y\n"
	.string "¡no dejaba de mirarme!$"
