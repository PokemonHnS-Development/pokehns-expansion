PokemonLeague_HallOfFame_hns_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PokemonLeague_HallOfFame_OnFrame
	.byte 0

PokemonLeague_HallOfFame_OnFrame::
	map_script_2 VAR_LEAGUE_STATE, 6, PokemonLeague_HallOfFame_EventScript_Cutscene
	.2byte 0

PokemonLeague_HallOfFame_EventScript_Cutscene::
	lock
	goto_if_set FLAG_IS_CHAMPION, PokemonLeague_HallOfFame_EventScript_CutsceneKantoChamp
	applymovement LOCALID_HALLOFFAME_LANCE, PokemonLeague_HallOfFame_Movement_LanceEnter
	applymovement OBJ_EVENT_ID_PLAYER, PokemonLeague_HallOfFame_Movement_PlayerEnter
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement LOCALID_HALLOFFAME_LANCE
	msgbox PokemonLeague_HallOfFame_LanceText, MSGBOX_DEFAULT
	closemessage
	special GivePartyMonChampionRibbon
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	dofieldeffect FLDEFF_HALL_OF_FAME_RECORD_FRLG
	waitfieldeffect FLDEFF_HALL_OF_FAME_RECORD_FRLG
	delay 40
	setvar VAR_TEMP_1, 1
	call PokemonLeague_HallOfFame_EventScript_SetFirstGameClearFlags
	setrespawn HEAL_LOCATION_NEW_BARK_TOWN_HNS
	fadescreenspeed FADE_TO_BLACK, 24
	special GameClear
	waitstate
	releaseall
	end

PokemonLeague_HallOfFame_EventScript_CutsceneKantoChamp::
	applymovement LOCALID_HALLOFFAME_LANCE, PokemonLeague_HallOfFame_Movement_LanceEnter
	applymovement OBJ_EVENT_ID_PLAYER, PokemonLeague_HallOfFame_Movement_PlayerEnter
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement LOCALID_HALLOFFAME_LANCE
	msgbox PokemonLeague_HallOfFame_Rematch_LanceText, MSGBOX_DEFAULT
	closemessage
	special GivePartyMonChampionRibbon
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	dofieldeffect FLDEFF_HALL_OF_FAME_RECORD_FRLG
	waitfieldeffect FLDEFF_HALL_OF_FAME_RECORD_FRLG
	delay 40
	setvar VAR_TEMP_1, 1
	call PokemonLeague_HallOfFame_EventScript_SetGameClearFlags
	setrespawn HEAL_LOCATION_NEW_BARK_TOWN_HNS
	fadescreenspeed FADE_TO_BLACK, 24
	special GameClear
	waitstate
	releaseall
	end

PokemonLeague_HallOfFame_EventScript_SetFirstGameClearFlags::
	setflag FLAG_HIDE_AZALEA_TOWN_SLOWPOKE
	setflag FLAG_HIDE_SLOWPOKE_WELL_TAILLESS_SLOWPOKES
	clearflag FLAG_HIDE_AZALEA_TOWN_TAILED_SLOWPOKES
	clearflag FLAG_HIDE_LEAGUE_BLACKBELT
	setflag FLAG_IS_CHAMPION
	setflag FLAG_HIDE_BATTLEFRONTIER_ENGINEER
	setvar VAR_LEAGUE_STATE, 1
	setvar VAR_NEWBARK_TOWN_STATE, 6
	setvar VAR_SSAQUA_STATE, 0
	return

PokemonLeague_HallOfFame_EventScript_SetGameClearFlags::
	setflag FLAG_HIDE_CERULEANCAVE_GUARD
	setflag FLAG_HIDE_AZALEA_TOWN_SLOWPOKE
	setflag FLAG_HIDE_SLOWPOKE_WELL_TAILLESS_SLOWPOKES
	clearflag FLAG_HIDE_AZALEA_TOWN_TAILED_SLOWPOKES
	clearflag FLAG_HIDE_LATIOS
	clearflag FLAG_HIDE_LATIAS
	clearflag FLAG_HIDE_RAYQUAZA
	clearflag FLAG_HIDE_GROUDON
	clearflag FLAG_HIDE_KYOGRE
	clearflag FLAG_HIDE_MEWTWO
	clearflag FLAG_HIDE_VERMILION_SNORLAX
	clearflag FLAG_HIDE_UNION_CAVE_LAPRAS
	clearflag FLAG_HIDE_SUDOWOODO
	clearflag FLAG_HIDE_ZAPDOS
	clearflag FLAG_HIDE_ARTICUNO
	clearflag FLAG_HIDE_MOLTRES
	clearflag FLAG_ITEM_GS_BALL
	setflag FLAG_HIDE_BATTLEFRONTIER_ENGINEER
	setflag FLAG_IS_KANTO_CHAMPION
	setvar VAR_COMPLETED_LUGIA, 4
	clearflag FLAG_HIDE_LUGIA
	setvar VAR_COMPLETED_HO_OH, 4
	clearflag FLAG_HIDE_HO_OH
	call PokemonLeague_HallOfFame_EventScript_SpawnRoamers
	call_if_ge VAR_SUICUNE_ENCOUNTERS, 8, PokemonLeague_HallOfFame_EventScript_SpawnSuicune
	call_if_set FLAG_CAUGHT_CELEBI, PokemonLeague_HallOfFame_EventScript_SpawnSecondCelebi
	call_if_ge VAR_VIRIDIAN_FOREST_PICHU, 4, PokemonLeague_HallOfFame_EventScript_SpawnPichu
	call_if_ge VAR_ALOLA_STATE, 4, PokemonLeague_HallOfFame_EventScript_SpawnAlolaMons
	call PokemonLeague_HallOfFame_EventScript_SpawnSinjohMons
	call_if_ge VAR_SINJOH_STORYLINE, 13 PokemonLeague_HallOfFame_EventScript_SpawnArceus
	clearflag FLAG_DEFEATED_MEW
	clearflag FLAG_CAUGHT_MEW
	clearflag FLAG_BATTLED_DEOXYS
	clearflag FLAG_DEFEATED_DEOXYS
	clearflag FLAG_SUMMONED_MTMOON_JIRACHI
	setvar VAR_LEAGUE_STATE, 1
	return

PokemonLeague_HallOfFame_EventScript_SpawnAlolaMons::
	clearflag FLAG_HIDE_TAPU_BULU
	clearflag FLAG_HIDE_TAPU_FINI
	clearflag FLAG_HIDE_TAPU_KOKO
	clearflag FLAG_HIDE_TAPU_LELE
	clearflag FLAG_HIDE_DUGTRIO_ALOLA
	clearflag FLAG_HIDE_MAROWAK_ALOLA
	clearflag FLAG_HIDE_EXEGGUTOR_ALOLA
	clearflag FLAG_HIDE_SANDSLASH_ALOLA
	clearflag FLAG_HIDE_NINETALES_ALOLA
	clearflag FLAG_HIDE_MUK_ALOLA
	clearflag FLAG_HIDE_RAICHU_ALOLA
	clearflag FLAG_HIDE_GOLEM_ALOLA
	return

PokemonLeague_HallOfFame_EventScript_SpawnSinjohMons::
	clearflag FLAG_HIDE_SINJOHRUINS_REGIROCK
	clearflag FLAG_HIDE_SINJOHRUINS_REGICE
	clearflag FLAG_HIDE_SINJOHRUINS_REGISTEEL
	clearflag FLAG_HIDE_SINJOHRUINS_REGIELEKI
	clearflag FLAG_HIDE_SINJOHRUINS_REGIDRAGO
	clearflag FLAG_HIDE_SINJOHRUINS_REGIGIGAS
	return

PokemonLeague_HallOfFame_EventScript_SpawnArceus::
	clearflag FLAG_HIDE_SINJOHRUINS_ARCEUSROOM_ARCEUS
	return

PokemonLeague_HallOfFame_EventScript_SpawnPichu::
	clearflag FLAG_HIDE_VIRIDIAN_FOREST_SPIKY_EARED_PICHU
	return

PokemonLeague_HallOfFame_EventScript_SpawnRoamers::
	clearflag FLAG_CAUGHT_ENTEI
	clearflag FLAG_CAUGHT_RAIKOU
	special InitRoamer
	copyvar VAR_0x8004, VAR_ROAMER_POKEMON_HNS
	special InitKantoRoamers
	setflag FLAG_LATIOS_OR_LATIAS_ROAMING
	return

PokemonLeague_HallOfFame_EventScript_SpawnSuicune::
	clearflag FLAG_HIDE_ROUTE25_SUICUNE
	return

PokemonLeague_HallOfFame_EventScript_SpawnSecondCelebi::
	clearflag FLAG_HIDE_ILEX_FOREST_SECOND_CELEBI
	return

PokemonLeague_HallOfFame_Movement_LanceEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	face_left
	step_end

PokemonLeague_HallOfFame_Movement_PlayerEnter:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_right
	step_end

PokemonLeague_HallOfFame_LanceText:
    .string "לאנס: עבר הרבה זמן מאז\n"
    .string "שהייתי כאן בפעם האחרונה.\p"
    .string "כאן אנחנו מכבדים את אלופי הליגה\n"
    .string "לנצח נצחים.\p"
    .string "גם הפוקימונים האמיצים שלהם\n"
    .string "מונצחים כאן.\p"
    .string "היום היינו עדים לעלייתו\n"
    .string "של אלוף ליגה חדש -\p"
    .string "מאמן שמרגיש חמלה ואמון\n"
    .string "כלפי כל הפוקימונים.\p"
    .string "מאמן שהצליח בזכות התמדה ונחישות.\p"
    .string "אלוף הליגה החדש,\n"
    .string "שיש בו את כל הסימנים לגדולה!\p"
    .string "{PLAYER}, הרשה לי לרשום אותך\n"
    .string "ואת השותפים שלך כאלופים!$"

PokemonLeague_HallOfFame_Rematch_LanceText:
    .string "לאנס: אני זוכר,\n"
    .string "לא מזמן עמדתי כאן וקיבלתי את פניך\p"
    .string "כאלוף ג'וטו.\p"
    .string "ועכשיו אנחנו שוב כאן,\n"
    .string "במקום הקדוש הזה שבו אנחנו מכבדים את\p"
    .string "המאמנים הטובים ביותר\n"
    .string "ואת הפוקימונים שלהם.\p"
    .string "היום הוכחת את עצמך לא רק בג'וטו,\n"
    .string "אלא גם בקאנטו,\p"
    .string "וגברת אפילו על הקבוצה\n"
    .string "החזקה ביותר שלי.\p"
    .string "הפגנת חמלה ואמון נדירים בפוקימונים שלך,\n"
    .string "קשר שהוביל אותך לניצחון שוב ושוב.\p"
    .string "המסע שלך, רצוף התמדה ונחישות עיקשת,\n"
    .string "מעיד על רוחך האמיתית כמאמן.\p"
    .string "יש בך את כל מה שדרוש כדי להיות\n"
    .string "גדול באמת, ואולי אפילו הגדול מכולם.\p"
    .string "{PLAYER}, זה כבוד לי לרשום שוב אותך\n"
    .string "ואת השותפים הנאמנים שלך כאלופים.$"

