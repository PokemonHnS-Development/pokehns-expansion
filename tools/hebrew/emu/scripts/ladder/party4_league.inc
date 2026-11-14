@ Ladder 4 party, bag, money and Pokedex: the team that enters the Hall of Fame (8 badges,
@ levels like a normal first clear). The party is full, so the Ho-Oh caught at Tin Tower goes to
@ the PC (givemon sends it to the first free box slot).
@ The Pokedex marks are SYNTHETIC: Johto natives SPECIES_CHIKORITA..SPECIES_SUICUNE (national
@ 152-245) seen, every third of them caught, plus a list of Kanto species found in Johto.
	givemon SPECIES_TYPHLOSION, 52, ITEM_CHARCOAL, BALL_POKE
	givemon SPECIES_PIDGEOT, 47, ITEM_NONE, BALL_POKE
	givemon SPECIES_AMPHAROS, 48, ITEM_NONE, BALL_GREAT
	givemon SPECIES_GOLEM, 46, ITEM_NONE, BALL_POKE
	givemon SPECIES_GENGAR, 47, ITEM_NONE, BALL_GREAT
	givemon SPECIES_TOGETIC, 45, ITEM_NONE, BALL_POKE
	givemon SPECIES_HO_OH, 45, ITEM_NONE, BALL_MASTER
	removeitem ITEM_MASTER_BALL
	setvar VAR_0x8004, SPECIES_CHIKORITA
LadderParty4_Seen:
	setseenmon VAR_0x8004
	addvar VAR_0x8004, 1
	goto_if_le VAR_0x8004, SPECIES_SUICUNE, LadderParty4_Seen
	setvar VAR_0x8004, SPECIES_CHIKORITA
LadderParty4_Caught:
	setcaughtmon VAR_0x8004
	addvar VAR_0x8004, 3
	goto_if_le VAR_0x8004, SPECIES_SNEASEL, LadderParty4_Caught
	setcaughtmon SPECIES_BELLSPROUT
	setcaughtmon SPECIES_ZUBAT
	setcaughtmon SPECIES_GYARADOS
	setcaughtmon SPECIES_MAGIKARP
	setcaughtmon SPECIES_GEODUDE
	setcaughtmon SPECIES_GASTLY
	setcaughtmon SPECIES_PIDGEY
	setseenmon SPECIES_RATTATA
	setseenmon SPECIES_RATICATE
	setseenmon SPECIES_SPEAROW
	setseenmon SPECIES_FEAROW
	setseenmon SPECIES_EKANS
	setseenmon SPECIES_ARBOK
	setseenmon SPECIES_PIKACHU
	setseenmon SPECIES_SANDSHREW
	setseenmon SPECIES_NIDORAN_F
	setseenmon SPECIES_NIDORAN_M
	setseenmon SPECIES_CLEFAIRY
	setseenmon SPECIES_VULPIX
	setseenmon SPECIES_JIGGLYPUFF
	setseenmon SPECIES_GOLBAT
	setseenmon SPECIES_ODDISH
	setseenmon SPECIES_GLOOM
	setseenmon SPECIES_PARAS
	setseenmon SPECIES_VENONAT
	setseenmon SPECIES_DIGLETT
	setseenmon SPECIES_MEOWTH
	setseenmon SPECIES_PSYDUCK
	setseenmon SPECIES_MANKEY
	setseenmon SPECIES_GROWLITHE
	setseenmon SPECIES_POLIWAG
	setseenmon SPECIES_POLIWHIRL
	setseenmon SPECIES_ABRA
	setseenmon SPECIES_MACHOP
	setseenmon SPECIES_MACHOKE
	setseenmon SPECIES_WEEPINBELL
	setseenmon SPECIES_TENTACOOL
	setseenmon SPECIES_TENTACRUEL
	setseenmon SPECIES_GRAVELER
	setseenmon SPECIES_PONYTA
	setseenmon SPECIES_SLOWPOKE
	setseenmon SPECIES_SLOWBRO
	setseenmon SPECIES_MAGNEMITE
	setseenmon SPECIES_MAGNETON
	setseenmon SPECIES_DODUO
	setseenmon SPECIES_SEEL
	setseenmon SPECIES_GRIMER
	setseenmon SPECIES_SHELLDER
	setseenmon SPECIES_HAUNTER
	setseenmon SPECIES_ONIX
	setseenmon SPECIES_DROWZEE
	setseenmon SPECIES_KRABBY
	setseenmon SPECIES_VOLTORB
	setseenmon SPECIES_ELECTRODE
	setseenmon SPECIES_EXEGGCUTE
	setseenmon SPECIES_CUBONE
	setseenmon SPECIES_KOFFING
	setseenmon SPECIES_WEEZING
	setseenmon SPECIES_RHYHORN
	setseenmon SPECIES_TANGELA
	setseenmon SPECIES_HORSEA
	setseenmon SPECIES_GOLDEEN
	setseenmon SPECIES_STARYU
	setseenmon SPECIES_SCYTHER
	setseenmon SPECIES_JYNX
	setseenmon SPECIES_ELECTABUZZ
	setseenmon SPECIES_MAGMAR
	setseenmon SPECIES_PINSIR
	setseenmon SPECIES_TAUROS
	setseenmon SPECIES_LAPRAS
	setseenmon SPECIES_DITTO
	setseenmon SPECIES_EEVEE
	setseenmon SPECIES_DRATINI
	setseenmon SPECIES_DRAGONAIR
	setseenmon SPECIES_DRAGONITE
	setseenmon SPECIES_AERODACTYL
	setseenmon SPECIES_GENGAR
	setseenmon SPECIES_MUK
	setseenmon SPECIES_ARCANINE
	setseenmon SPECIES_EXEGGUTOR
	setseenmon SPECIES_CHARIZARD
	setseenmon SPECIES_HYPNO
	setseenmon SPECIES_MACHAMP
	setseenmon SPECIES_HITMONLEE
	setseenmon SPECIES_HITMONCHAN
	setseenmon SPECIES_STEELIX
	setseenmon SPECIES_TYRANITAR
	additem ITEM_HYPER_POTION, 8
	additem ITEM_SUPER_POTION, 4
	additem ITEM_FULL_RESTORE, 3
	additem ITEM_MAX_POTION, 2
	additem ITEM_REVIVE, 6
	additem ITEM_MAX_REVIVE, 1
	additem ITEM_FULL_HEAL, 4
	additem ITEM_ANTIDOTE, 2
	additem ITEM_PARALYZE_HEAL, 2
	additem ITEM_ICE_HEAL, 1
	additem ITEM_BURN_HEAL, 1
	additem ITEM_MAX_ELIXIR, 1
	additem ITEM_RARE_CANDY, 2
	additem ITEM_ESCAPE_ROPE, 3
	additem ITEM_MAX_REPEL, 4
	additem ITEM_POKE_BALL, 5
	additem ITEM_GREAT_BALL, 8
	additem ITEM_ULTRA_BALL, 12
	additem ITEM_NUGGET, 1
	additem ITEM_SITRUS_BERRY, 3
	addmoney 76800
	end
