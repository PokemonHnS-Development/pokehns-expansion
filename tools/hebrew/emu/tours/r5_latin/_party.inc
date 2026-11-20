@ r5 Latin-leftover tours: a fresh party in RAM (nicknames = species names in the language of the ROM
@ that runs it). 0 Typhlosion, 1 Rhyhorn (Brock's trade), 2 Dugtrio (Lorenzo's trade), 3 an Egg
@ (Daisy's egg line), 4 Magikarp (Jasmine's trade, any Pokemon); slot 5 stays free for Kirk's Shuckie.
	callnative ZeroPlayerPartyMons
	special CalculatePlayerPartyCount
	givemon SPECIES_TYPHLOSION, 50
	givemon SPECIES_RHYHORN, 30
	givemon SPECIES_DUGTRIO, 30
	giveegg SPECIES_TOGEPI
	givemon SPECIES_MAGIKARP, 20
	end
