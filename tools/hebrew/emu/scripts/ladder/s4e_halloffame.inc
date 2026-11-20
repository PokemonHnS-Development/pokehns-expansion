@ Hand over to the ROM's own Hall of Fame. This is the tail of
@ PokemonLeague_WillsRoom_EventScript_LanceOnDefeatJohto (PokemonLeague_ChampionsRoom_hns:72-138):
@ VAR_LEAGUE_STATE 6 and the silent warp into the Hall of Fame. There the map's ON_FRAME script
@ (PokemonLeague_HallOfFame_EventScript_Cutscene) runs Lance's speech, the champion ribbons, the
@ record, SetFirstGameClearFlags, respawn in New Bark Town and special GameClear, which sets
@ FLAG_SYS_GAME_CLEAR, saves the Hall of Fame and the game, and rolls the credits.
	setvar VAR_LEAGUE_STATE, 6
	warpsilent MAP_POKEMON_LEAGUE_HALL_OF_FAME_HNS, 0
	waitstate
	end
