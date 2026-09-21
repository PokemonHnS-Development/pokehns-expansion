MysteryGiftScript_BattleCard::
	setvaddress MysteryGiftScript_BattleCard
	vgoto_if_set FLAG_MYSTERY_GIFT_DONE, MysteryGiftScript_BattleCardInfo
	setorcopyvar VAR_RESULT, GET_CARD_BATTLES_WON
	specialvar VAR_0x8008, GetMysteryGiftCardStat
	vgoto_if_ne VAR_0x8008, REQUIRED_CARD_BATTLES, MysteryGiftScript_BattleCardInfo
	lock
	faceplayer
	vmessage sText_MysteryGiftBattleCountCard_WonPrize
	waitmessage
	waitbuttonpress
	giveitem ITEM_POTION
	release
	setflag FLAG_MYSTERY_GIFT_DONE
	end

MysteryGiftScript_BattleCardInfo:
	lock
	faceplayer
	vmessage sText_MysteryGiftBattleCountCard
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftBattleCountCard:
	.string "Gracias por usar el sistema\nde REGALO MISTERIOSO.\pTu TARJETA DE COMBATES guarda\ntu registro de combates contra\lENTRENADORES con la misma TARJETA.\pBusca y reta a ENTRENADORES\nque tengan la misma TARJETA.\pPuedes consultar la clasificación\nleyendo las NOTICIAS.\p¡Anímate a probarlo!$"

sText_MysteryGiftBattleCountCard_WonPrize:
	.string "Gracias por usar el sistema de\n"
	.string "REGALO MISTERIOSO.\p"
	.string "¡Felicidades!\p"
	.string "¡Ganaste un premio por ganar\n"
	.string "tres batallas!\p"
	.string "Esperamos que te inspires para\n"
	.string "luchar un poco más.$"
