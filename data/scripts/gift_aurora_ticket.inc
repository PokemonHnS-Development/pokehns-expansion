MysteryGiftScript_AuroraTicket::
	setvaddress MysteryGiftScript_AuroraTicket
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_AURORA_TICKET, AuroraTicket_Obtained
	vgoto_if_set FLAG_BATTLED_DEOXYS, AuroraTicket_Obtained
	checkitem ITEM_AURORA_TICKET
	vgoto_if_eq VAR_RESULT, TRUE, AuroraTicket_Obtained
	vmessage sText_AuroraTicketForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_AURORA_TICKET
	vgoto_if_eq VAR_RESULT, FALSE, AuroraTicket_NoBagSpace
	giveitem ITEM_AURORA_TICKET
	setflag FLAG_ENABLE_SHIP_BIRTH_ISLAND
	setflag FLAG_RECEIVED_AURORA_TICKET
	vmessage sText_AuroraTicketUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

AuroraTicket_NoBagSpace:
	vmessage sText_AuroraTicketBagFull
	waitmessage
	waitbuttonpress
	release
	end

AuroraTicket_Obtained:
	vmessage sText_AuroraTicketThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_AuroraTicketForYou:
	.string "Gracias por usar el SISTEMA\n
de REGALO MISTERIOSO.\p
Debes ser {PLAYER}.\n
Hay un boleto aquí para ti.$"

sText_AuroraTicketUseAtPort:
	.string "Parece que es para usarlo en el\n
puerto de CIUDAD CALAGUA.\p
¿Por qué no probarlo y ver de qué\n
se trata?$"

sText_AuroraTicketThankYou:
	.string "Gracias por usar el SISTEMA\n
de REGALO MISTERIOSO.$"

sText_AuroraTicketBagFull:
	.string "Ay, lo siento, {PLAYER}.\n
Tu BOLSILLO de OBJ. CLAVE está lleno.\p
Por favor, guarda algo en tu PC,\n
y vuelve luego por esto.$"
