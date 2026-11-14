@ Baoba's requests (src/scrcmd.c ScrCmd_baobacheckmon: 1 Beldum, 2 Castform, 3 Medicham, 4 Bagon):
@ 0 Typhlosion (wrong), 1 Beldum, 2 Castform, 3 Medicham, 4 Bagon, 5 an Egg (wrong: eggs are refused).
	callnative ZeroPlayerPartyMons
	special CalculatePlayerPartyCount
	givemon SPECIES_TYPHLOSION, 50
	givemon SPECIES_BELDUM, 20
	givemon SPECIES_CASTFORM, 20
	givemon SPECIES_MEDICHAM, 30
	givemon SPECIES_BAGON, 20
	giveegg SPECIES_TOGEPI
	end
