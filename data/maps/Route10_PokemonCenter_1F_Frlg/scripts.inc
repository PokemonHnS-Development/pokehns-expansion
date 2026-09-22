.equ REQUIRED_OWNED_MONS, 20

Route10_PokemonCenter_1F_Frlg_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route10_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

Route10_PokemonCenter_1F_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_ROUTE10_POKEMON_CENTER_1F
	setrespawn HEAL_LOCATION_ROUTE10
	end

Route10_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse_Frlg
	release
	end

Route10_PokemonCenter_1F_EventScript_FatMan::
	msgbox Route10_PokemonCenter_1F_Text_NuggetUselessSoldFor5000, MSGBOX_NPC
	end

Route10_PokemonCenter_1F_EventScript_Gentleman::
	msgbox Route10_PokemonCenter_1F_Text_EveryTypeStrongerThanOthers, MSGBOX_NPC
	end

Route10_PokemonCenter_1F_EventScript_Youngster::
	msgbox Route10_PokemonCenter_1F_Text_HeardGhostsHauntLavender, MSGBOX_NPC
	end

Route10_PokemonCenter_1F_EventScript_Aide::
	lock
	faceplayer
	call Route10_PokemonCenter_1F_EventScript_GetAideRequestInfo
	goto_if_set FLAG_GOT_EVERSTONE_FROM_OAKS_AIDE, Route10_PokemonCenter_1F_EventScript_AlreadyGotEverstone
	msgbox Route10_PokemonCenter_1F_Text_GiveEverstoneIfCaught20Mons, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Aide_EventScript_DeclineCheckMons
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetFrlgPokedexCount
	buffernumberstring STR_VAR_3, VAR_0x8006
	call Route10_PokemonCenter_1F_EventScript_GetAideRequestInfo
	goto_if_lt VAR_0x8006, REQUIRED_OWNED_MONS, Aide_EventScript_HaventCaughtEnough
	msgbox Route10_PokemonCenter_1F_Text_GreatHereYouGo
	checkitemspace ITEM_EVERSTONE
	goto_if_eq VAR_RESULT, FALSE, Aide_EventScript_NoRoomForItem
	giveitem_msg Route10_PokemonCenter_1F_Text_ReceivedEverstoneFromAide, ITEM_EVERSTONE
	setflag FLAG_GOT_EVERSTONE_FROM_OAKS_AIDE
	msgbox Route10_PokemonCenter_1F_Text_ExplainEverstone
	release
	end

Route10_PokemonCenter_1F_EventScript_AlreadyGotEverstone::
	msgbox Route10_PokemonCenter_1F_Text_ExplainEverstone
	release
	end

Route10_PokemonCenter_1F_EventScript_GetAideRequestInfo::
	buffernumberstring STR_VAR_1, REQUIRED_OWNED_MONS
	bufferitemname STR_VAR_2, ITEM_EVERSTONE
	return

Route10_PokemonCenter_1F_Text_EveryTypeStrongerThanOthers::
	.string "The types of POKéMON match up\n"
	.string "diferente entre sí.\p"
	.string "Cada tipo es más fuerte que\n"
	.string "algunos y más débil que otros.$"

Route10_PokemonCenter_1F_Text_NuggetUselessSoldFor5000::
	.string "Una PEPITA es totalmente\n"
	.string "Así que lo vendí por ¥5000.$"

Route10_PokemonCenter_1F_Text_HeardGhostsHauntLavender::
	.string "Escuché que hay fantasmas que\n"
	.string "LAVENDER TOWN.$"

Route10_PokemonCenter_1F_Text_GiveEverstoneIfCaught20Mons::
	.string "Oh… {PLAYER}!\n"
	.string "¡Te estaba buscando!\p"
	.string "Soy yo, uno de los siempre\n"
	.string "presentes AYUDANTES del PROF. OAK.\p"
	.string "If your POKéDEX has complete data\n"
	.string "en veinte especies, se supone que debo\l"
	.string "darte una recompensa del PROF. OAK.\p"
	.string "Me encargó esto\n"
	.string "EVERSTONE.\p"
	.string "Bueno, {PLAYER}, déjame preguntarte.\p"
	.string "¿Has reunido datos de al menos\n"
	.string "twenty kinds of POKéMON?$"

Route10_PokemonCenter_1F_Text_GreatHereYouGo::
	.string "¡Genial! Has capturado o tenido\n"
	.string "{STR_VAR_3} tipos de POKéMON!\p"
	.string "¡Felicidades!\n"
	.string "¡Toma!$"

Route10_PokemonCenter_1F_Text_ReceivedEverstoneFromAide::
	.string "{PLAYER} recibió la PIEDRAEterna\n"
	.string "del AYUDANTE.$"

Route10_PokemonCenter_1F_Text_ExplainEverstone::
	.string "Making POKéMON evolve certainly\n"
	.string "can add to the POKéDEX.\p"
	.string "Sin embargo, a veces puede que\n"
	.string "want a certain POKéMON to evolve.\p"
	.string "En ese caso, dale la PIEDRAEterna\n"
	.string "to that POKéMON.\p"
	.string "Evitará la evolución según\n"
	.string "lo que diga el PROFESOR.$"

