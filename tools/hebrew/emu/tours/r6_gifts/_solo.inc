@ r6 gift tours: a party of one (the Lv 100 Mewtwo of _base.txt, no Surf), so every gift goes to
@ the party.
	callnative ZeroPlayerPartyMons
	special CalculatePlayerPartyCount
	createmon 0, 0, SPECIES_MEWTWO, 100, move1=MOVE_PSYSTRIKE, move2=MOVE_ICE_BEAM, move3=MOVE_RECOVER, move4=MOVE_AURA_SPHERE
	special CalculatePlayerPartyCount
	end
