@ Storage-system test setup on the post-game ladder save (party of 6, box 1 holds Ho-Oh, Arcanine,
@ Lapras, Arceus in slots 0-3, no other boxes used; read with boxprobe). The party is full, so every
@ givemon goes to the PC (box 1 slots 4-29, in order). Pidgeot (party slot 1) is given SURF: no other
@ party or box Pokemon knows it (boxprobe), so releasing it runs the "came back" sequence
@ (src/pokemon_storage_system.c:6745-6766). The ITEMS pocket is then filled by the debug menu
@ (pcs_00_setup.txt): every slot used, so an ITEMS-pocket item cannot go back to the bag
@ (CheckBagHasSpace counts empty slots, src/item.c:276-300); MEDICINE items still can.
	setmonmove 1, 0, MOVE_SURF
	givemon SPECIES_MEOWTH, 30, ITEM_ORANGE_MAIL
	givemon SPECIES_SNORLAX, 50, ITEM_LEFTOVERS
	givemon SPECIES_CHANSEY, 40, ITEM_LUCKY_EGG
	giveegg SPECIES_TOGEPI
	givemon SPECIES_MEOWSCARADA, 50
	givemon SPECIES_STARAPTOR, 40, ITEM_FOCUS_SASH
	givemon SPECIES_BRAMBLEGHAST, 40, ITEM_POWER_LENS
	givemon SPECIES_SANDSLASH_ALOLA, 40, ITEM_BERRY_JUICE
	givemon SPECIES_EXEGGUTOR_ALOLA, 40, ITEM_HYPER_POTION
	givemon SPECIES_MAROWAK, 40, ITEM_THICK_CLUB
	givemon SPECIES_ELECTRODE_HISUI, 40
	givemon SPECIES_CRABOMINABLE, 40
	givemon SPECIES_DUDUNSPARCE, 40
	givemon SPECIES_PIKACHU, 20
	givemon SPECIES_BULBASAUR, 10
	givemon SPECIES_CHIKORITA, 10
	givemon SPECIES_TOTODILE, 10
	givemon SPECIES_MAREEP, 10
	givemon SPECIES_SUDOWOODO, 20
	givemon SPECIES_HERACROSS, 30
	givemon SPECIES_SCYTHER, 30
	givemon SPECIES_EEVEE, 10
	givemon SPECIES_UMBREON, 30
	givemon SPECIES_ESPEON, 30
	givemon SPECIES_TYRANITAR, 55
	givemon SPECIES_DRAGONITE, 55
	end
