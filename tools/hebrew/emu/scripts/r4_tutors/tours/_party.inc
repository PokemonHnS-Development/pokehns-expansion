@ Move tutor party (every tour starts from it). Party: 0 Typhlosion (4 moves, learns every
@ tutor move here), 1 Golem (2 moves; learns Headbutt, Fury Cutter, Rollout, Metronome, Dynamic
@ Punch, Swagger, Mimic, Substitute, Body Slam, Seismic Toss), 2 Snorlax (knows Headbutt),
@ 3 Magikarp (learns none of them), 4 an Egg, 5 Ampharos (2 moves; Wild Charge for Ula'ula).
@ Two more go to the PC box: Feraligatr (4 moves; Headbutt, Fury Cutter, Wave Crash for New
@ Sinjoh) and Raichu (2 moves).
	callnative ZeroPlayerPartyMons
	special CalculatePlayerPartyCount
	givemon SPECIES_TYPHLOSION, 50, move1=MOVE_TACKLE, move2=MOVE_LEER, move3=MOVE_EMBER, move4=MOVE_SMOKESCREEN
	givemon SPECIES_GOLEM, 50, move1=MOVE_TACKLE, move2=MOVE_DEFENSE_CURL, move3=MOVE_NONE, move4=MOVE_NONE
	givemon SPECIES_SNORLAX, 50, move1=MOVE_HEADBUTT, move2=MOVE_REST, move3=MOVE_NONE, move4=MOVE_NONE
	givemon SPECIES_MAGIKARP, 20
	giveegg SPECIES_TOGEPI
	givemon SPECIES_AMPHAROS, 50, move1=MOVE_THUNDER_SHOCK, move2=MOVE_GROWL, move3=MOVE_NONE, move4=MOVE_NONE
	givemon SPECIES_FERALIGATR, 50, move1=MOVE_SCRATCH, move2=MOVE_LEER, move3=MOVE_WATER_GUN, move4=MOVE_BITE
	givemon SPECIES_RAICHU, 40, move1=MOVE_THUNDER_SHOCK, move2=MOVE_TAIL_WHIP, move3=MOVE_NONE, move4=MOVE_NONE
	end
