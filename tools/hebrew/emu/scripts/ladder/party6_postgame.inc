@ Ladder 6 party: a FRESH Lv 75-85 team. The Hall of Fame team from ladder 4 (Lv 45-52) cannot be
@ levelled from a script, so the party is wiped (ZeroPlayerPartyMons, src/pokemon.c:3189) and the
@ same species are given again; Hall of Fame records 2 and 3 hold this team, record 1 the old one.
@ Pokedex marks are SYNTHETIC: national 1-251 seen, every second one caught.
	callnative ZeroPlayerPartyMons
	special CalculatePlayerPartyCount
	givemon SPECIES_TYPHLOSION, 84, ITEM_CHARCOAL, BALL_POKE
	givemon SPECIES_PIDGEOT, 77, ITEM_NONE, BALL_POKE
	givemon SPECIES_AMPHAROS, 79, ITEM_NONE, BALL_GREAT
	givemon SPECIES_GOLEM, 78, ITEM_NONE, BALL_POKE
	givemon SPECIES_GENGAR, 80, ITEM_NONE, BALL_GREAT
	givemon SPECIES_TOGEKISS, 79, ITEM_NONE, BALL_POKE
	setvar VAR_0x8004, SPECIES_BULBASAUR
LadderParty6_Seen:
	setseenmon VAR_0x8004
	addvar VAR_0x8004, 1
	goto_if_le VAR_0x8004, SPECIES_CELEBI, LadderParty6_Seen
	setvar VAR_0x8004, SPECIES_BULBASAUR
LadderParty6_Caught:
	setcaughtmon VAR_0x8004
	addvar VAR_0x8004, 2
	goto_if_le VAR_0x8004, SPECIES_CELEBI, LadderParty6_Caught
	additem ITEM_FULL_RESTORE, 10
	additem ITEM_MAX_REVIVE, 4
	additem ITEM_MAX_ELIXIR, 3
	additem ITEM_ULTRA_BALL, 20
	addmoney 250000
	end
