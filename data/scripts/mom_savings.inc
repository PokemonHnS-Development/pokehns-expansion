EventScript_MomGiftCall_Item::
	lockall
	pokenavcall Mom_Text_GiftCall_Item
	waitmessage
	delay 30
	clearflag FLAG_MOM_HAS_GIFT
	releaseall
	end

EventScript_MomGiftCall_Berry::
	lockall
	pokenavcall Mom_Text_GiftCall_Berry
	waitmessage
	delay 30
	clearflag FLAG_MOM_HAS_GIFT
	releaseall
	end

EventScript_MomGiftCall_Decoration::
	lockall
	pokenavcall Mom_Text_GiftCall_Decoration
	waitmessage
	delay 30
	clearflag FLAG_MOM_HAS_GIFT
	releaseall
	end

Mom_Text_GiftCall_Item:
	.string "MAMÁ: ¡Hola, cariño!\p"
	.string "Compré algo lindo\n"
	.string "para ti con tus ahorros!\p"
	.string "Lo envié a tu PC.\n"
	.string "¡Cuídate!$"

Mom_Text_GiftCall_Berry:
	.string "MAMÁ: ¡Hola, cariño!\p"
	.string "¡Encontré unas BAYAS lindas\n"
	.string "en la tienda para ti!\p"
	.string "Las envié a tu PC.\n"
	.string "¡Cuídate!$"

Mom_Text_GiftCall_Decoration:
	.string "MAMÁ: ¡Hola, cariño!\p"
	.string "¡Compré un MUÑECO POKé lindo\n"
	.string "para tu cuarto!\p"
	.string "Mira tus DECORACIONES cuando\n"
	.string "vuelvas a casa. ¡Cuídate!$"
