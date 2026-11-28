@ Hoenn & Seek (2.0 part 13a): decoration clerks for Johto and Kanto secret bases.
@ Emerald's decorations are sold in Fortree and Lilycove only, so a base in Ilex Forest,
@ on Route 45, in Viridian Forest or in Mt. Moon had no shop on its side of the sea.
@ The new dolls (constants/hoenn_decorations.h) are only sold here.

@ Goldenrod Dept. Store 5F: Johto dolls.
HoennSeek_EventScript_DecorClerkJohto::
	lock
	faceplayer
	msgbox HoennSeek_Text_DecorClerkJohto, MSGBOX_DEFAULT
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration HoennSeek_DecorList_Johto
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
HoennSeek_DecorList_Johto:
	.2byte DECOR_SUDOWOODO_DOLL
	.2byte DECOR_SLOWPOKE_DOLL
	.2byte DECOR_MAREEP_DOLL
	.2byte DECOR_UNOWN_DOLL
	.2byte DECOR_PICHU_DOLL
	.2byte DECOR_MARILL_DOLL
	.2byte DECOR_TOGEPI_DOLL
	.2byte DECOR_CHIKORITA_DOLL
	.2byte DECOR_CYNDAQUIL_DOLL
	.2byte DECOR_TOTODILE_DOLL
	.2byte DECOR_SMOOCHUM_DOLL
	pokemartlistend

@ Celadon Dept. Store 4F: Kanto dolls.
HoennSeek_EventScript_DecorClerkKanto::
	lock
	faceplayer
	msgbox HoennSeek_Text_DecorClerkKanto, MSGBOX_DEFAULT
	message gText_HowMayIServeYou
	waitmessage
	pokemartdecoration HoennSeek_DecorList_Kanto
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
HoennSeek_DecorList_Kanto:
	.2byte DECOR_VULPIX_DOLL
	.2byte DECOR_EEVEE_DOLL
	.2byte DECOR_PIKACHU_DOLL
	.2byte DECOR_CLEFAIRY_DOLL
	.2byte DECOR_JIGGLYPUFF_DOLL
	.2byte DECOR_MEOWTH_DOLL
	.2byte DECOR_DITTO_DOLL
	.2byte DECOR_PIKA_CUSHION
	.2byte DECOR_PIKA_POSTER
	pokemartlistend

HoennSeek_Text_DecorClerkJohto:
	.string "We sell dolls for SECRET BASES!\n"
	.string "They're all the rage in HOENN.\p"
	.string "These ones are JOHTO's own. You\n"
	.string "won't find them over there!$"

HoennSeek_Text_DecorClerkKanto:
	.string "A HOENN fad has reached KANTO:\n"
	.string "SECRET BASES, full of dolls!\p"
	.string "Our VULPIX and EEVEE dolls are\n"
	.string "made right here in CELADON.$"
