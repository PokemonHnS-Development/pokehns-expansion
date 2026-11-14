@ r5 field-move party: 0 Typhlosion (CUT, ROCK SMASH, STRENGTH, HEADBUTT; the lead, so it is the
@ follower and the field-move user), 1 Gyarados (SURF, WATERFALL, WHIRLPOOL, DEFOG). The ladder 6
@ party is wiped first, so no other Pokemon knows a field move. The HM flags and HM04 that the
@ field-move scripts check (data/scripts/field_move_scripts_hns.inc:4,72,112,328) are set
@ although ladder 6 should already have them.
	callnative ZeroPlayerPartyMons
	special CalculatePlayerPartyCount
	givemon SPECIES_TYPHLOSION, 60, move1=MOVE_CUT, move2=MOVE_ROCK_SMASH, move3=MOVE_STRENGTH, move4=MOVE_HEADBUTT
	givemon SPECIES_GYARADOS, 60, move1=MOVE_SURF, move2=MOVE_WATERFALL, move3=MOVE_WHIRLPOOL, move4=MOVE_DEFOG
	setflag FLAG_RECEIVED_HM_CUT
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
	setflag FLAG_RECEIVED_HM_STRENGTH
	setflag FLAG_GET_HEADBUTT
	checkitem ITEM_HM_STRENGTH
	goto_if_eq VAR_RESULT, TRUE, FmParty_HaveHM04
	additem ITEM_HM_STRENGTH
FmParty_HaveHM04:
	end
