MysteryGiftScript_MysticTicket::
	setvaddress MysteryGiftScript_MysticTicket
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_MYSTIC_TICKET, MysticTicket_Obtained
	vgoto_if_set FLAG_CAUGHT_LUGIA, MysticTicket_Obtained
	vgoto_if_set FLAG_CAUGHT_HO_OH, MysticTicket_Obtained
	checkitem ITEM_MYSTIC_TICKET
	vgoto_if_eq VAR_RESULT, TRUE, MysticTicket_Obtained
	vmessage sText_MysticTicketForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_MYSTIC_TICKET
	vgoto_if_eq VAR_RESULT, FALSE, MysticTicket_NoBagSpace
	giveitem ITEM_MYSTIC_TICKET
	setflag FLAG_ENABLE_SHIP_NAVEL_ROCK
	setflag FLAG_RECEIVED_MYSTIC_TICKET
	vmessage sText_MysticTicketUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

MysticTicket_NoBagSpace:
	vmessage sText_MysticTicketBagFull
	waitmessage
	waitbuttonpress
	release
	end

MysticTicket_Obtained:
	vmessage sText_MysticTicketThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_MysticTicketForYou:
	.string "Gracias por usar el REGALO\nMISTERIOSO.\pDebes ser {PLAYER}.\nHay un boleto aquí para ti.$"

sText_MysticTicketUseAtPort:
	.string "Parece que es para usar en el\npuerto de CIUDAD CALAGUA.\p¿Por qué no probarlo y ver de qué\nse trata?$"

sText_MysticTicketThankYou:
	.string "Gracias por usar el REGALO\nMISTERIOSO.$"

sText_MysticTicketBagFull:
	.string "Ay, lo siento, {PLAYER}.\nEl bolsillo OBJETOS CLAVE está lleno.\pGuarda algo en tu PC,\ny luego vuelve por esto.$"
