@ r5 remaining in-game trades: a fresh party in RAM (nicknames = species names in the language of the
@ ROM that runs it). 0 Typhlosion, 1 Bellsprout (Rudy), 2 Krabby (Tim), 3 Xatu (Mondo), 4 Dodrio (Emy),
@ 5 Forretress (Steven); the seventh, a second Krabby, goes to the PC box (the box pane of the trade box).
@ Trade flags cleared, the Eon Ticket in the bag (Steven trades only with it), the Safari Zone met.
	callnative ZeroPlayerPartyMons
	special CalculatePlayerPartyCount
	givemon SPECIES_TYPHLOSION, 50
	givemon SPECIES_BELLSPROUT, 20
	givemon SPECIES_KRABBY, 20
	givemon SPECIES_XATU, 30
	givemon SPECIES_DODRIO, 30
	givemon SPECIES_FORRETRESS, 30
	givemon SPECIES_KRABBY, 21
	clearflag FLAG_VIOLET_NPC_TRADE_COMPLETED
	clearflag FLAG_OLIVINE_NPC_TRADE_COMPLETED
	clearflag FLAG_PEWTER_NPC_TRADE_COMPLETED
	clearflag FLAG_BLACKTHORN_NPC_TRADE_COMPLETED
	clearflag FLAG_FUCHSIA_SAFARI_NPC_TRADE_COMPLETED
	clearflag FLAG_COMPLETED_TAUROS_TRADE
	setvar VAR_KANTO_SAFARI_ZONE_PROGRESS, 1
	removeitem ITEM_EON_TICKET
	additem ITEM_EON_TICKET
	end
