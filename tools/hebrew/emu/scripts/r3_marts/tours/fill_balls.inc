@ Fill the Poke Ball pocket with Poke Balls until AddBagItem fails (src/item.c:376), 999 at a time,
@ then 100, 10, 1, so no slot has room left for one more Poke Ball.
r3m_fill999:
	additem ITEM_POKE_BALL, 999
	goto_if_eq VAR_RESULT, TRUE, r3m_fill999
r3m_fill100:
	additem ITEM_POKE_BALL, 100
	goto_if_eq VAR_RESULT, TRUE, r3m_fill100
r3m_fill10:
	additem ITEM_POKE_BALL, 10
	goto_if_eq VAR_RESULT, TRUE, r3m_fill10
r3m_fill1:
	additem ITEM_POKE_BALL, 1
	goto_if_eq VAR_RESULT, TRUE, r3m_fill1
	end
