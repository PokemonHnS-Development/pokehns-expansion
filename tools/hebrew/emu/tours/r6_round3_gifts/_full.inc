@ r6 round-3 gift tours: a full party of six (slots 1-5 Lv 5 Rattata), so a gift finds no party slot.
	callnative ZeroPlayerPartyMons
	special CalculatePlayerPartyCount
	createmon 0, 0, SPECIES_MEWTWO, 50, move1=MOVE_PSYCHIC, move2=MOVE_ICE_BEAM, move3=MOVE_RECOVER, move4=MOVE_FLY
	createmon 0, 1, SPECIES_RATTATA, 5
	createmon 0, 2, SPECIES_RATTATA, 5
	createmon 0, 3, SPECIES_RATTATA, 5
	createmon 0, 4, SPECIES_RATTATA, 5
	createmon 0, 5, SPECIES_RATTATA, 5
	special CalculatePlayerPartyCount
	end
