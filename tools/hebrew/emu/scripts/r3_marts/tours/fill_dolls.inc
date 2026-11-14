@ Fill the doll inventory (gSaveBlock1Ptr->decorationDolls[40], the only H&S decoration category,
@ src/decoration_inventory.c:16) until DecorationAdd fails.
r3m_doll:
	adddecoration DECOR_PICHU_DOLL
	goto_if_eq VAR_RESULT, TRUE, r3m_doll
	end
