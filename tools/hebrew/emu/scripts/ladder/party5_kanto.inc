@ Ladder 5 additions: the Hall of Fame team from ladder 4 stays as it is (Lv 45-52, about right
@ for the first Kanto gyms). Two Kanto catches go to the PC; Kanto Pokedex marks are SYNTHETIC:
@ national 1-143 seen, every fourth caught.
	givemon SPECIES_ARCANINE, 45, ITEM_NONE, BALL_ULTRA
	givemon SPECIES_LAPRAS, 40, ITEM_NONE, BALL_ULTRA
	setvar VAR_0x8004, SPECIES_BULBASAUR
LadderParty5_Seen:
	setseenmon VAR_0x8004
	addvar VAR_0x8004, 1
	goto_if_le VAR_0x8004, SPECIES_SNORLAX, LadderParty5_Seen
	setvar VAR_0x8004, SPECIES_BULBASAUR
LadderParty5_Caught:
	setcaughtmon VAR_0x8004
	addvar VAR_0x8004, 4
	goto_if_le VAR_0x8004, SPECIES_SNORLAX, LadderParty5_Caught
	additem ITEM_HYPER_POTION, 6
	additem ITEM_FULL_RESTORE, 2
	additem ITEM_ULTRA_BALL, 10
	additem ITEM_MAX_REPEL, 3
	addmoney 21500
	end
