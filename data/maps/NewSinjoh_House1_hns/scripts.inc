NewSinjoh_House1_hns_MapScripts::
	.byte 0


NewSinjoh__House1_EventScripts_Elizabeth::
    lock
	faceplayer
	goto_if_set FLAG_NEWSINJOH_HOUSE1_ELIZABETH_GAVEWOOPER, NewSinjoh_House1_EventScript_Elizabeth_AfterGift
    msgbox NewSinjoh_House1_Text_Looking4Celebi MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, NewSinjoh_House1_EventScript_Decline
    checkspecies SPECIES_CELEBI
    goto_if_eq VAR_RESULT, TRUE, NewSinjoh_House1_EventScript_GiveWooperPaldea
	msgbox NewSinjoh_House1_Text_NicePokemonButNotCelebi, MSGBOX_DEFAULT
    release
    end

NewSinjoh_House1_EventScript_Decline::
	msgbox NewSinjoh_House1_Text_Decline, MSGBOX_DEFAULT
	closemessage
	release
	end

NewSinjoh_House1_EventScript_GiveWooperPaldea::
	playse SE_PIN
    applymovement LOCALID_NEWSINJOH_HOUSE1_ELIZABETH, Common_Movement_ExclamationMark
	delay 55
	waitmovement LOCALID_NEWSINJOH_HOUSE1_ELIZABETH
    msgbox NewSinjoh_House1_OffersWooper MSGBOX_DEFAULT
    setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_WOOPER_PALDEA
    bufferspeciesname STR_VAR_1, SPECIES_WOOPER_PALDEA
    givemon SPECIES_WOOPER_PALDEA, 5
	call Common_EventScript_GiftMon
	setflag FLAG_NEWSINJOH_HOUSE1_ELIZABETH_GAVEWOOPER
	closemessage
    release
    end

NewSinjoh_House1_Text_Looking4Celebi:
    .string "¡Hola, Entrenador!\p"
	.string "Viniste desde muy lejos,\n"
	.string "¿De PUEBLO PRIMAVERA?\p"
	.string "tengo un pedido para alguien tan\n"
	.string "viajero como tú.\l"
	.string "Mira, mi POKéMON favorito de todo\l"
	.string "el mundo resulta ser\l"
	.string "el mítico POKéMON CELEBI.\p"
	.string "Si tienes uno, ¿te importaría\n"
	.string "mostrármelo?$"

NewSinjoh_House1_Text_NicePokemonButNotCelebi:
    .string "Es un POKéMON maravilloso\n"
	.string "el que tienes, pero no es\l"
	.string "exactamente lo que buscaba..$"

NewSinjoh_House1_OffersWooper:
    .string "¡Eso es! ¡Es un CELEBI vivo!\p"
	.string "Muchas gracias por traerlo\n"
	.string "desde tan al norte para que lo vea.\p"
    .string "Toma, a mi novia le pasó que\n"
	.string "atrapó demasiados de estos durante\l"
	.string "su viaje a una región lejana...\p"
    .string "Toma este WOOPER especial como\n"
	.string "agradecimiento, {PLAYER}.$"

NewSinjoh_House1_Text_Decline:
	.string "Qué mal. De verdad quería\n"
	.string "ver uno.$"

NewSinjoh_House1_Text_TakeCareOfWooper:
    .string "Cuida muy bien a ese WOOPER\n"
	.string "por mí, ¿está bien?$"

NewSinjoh_House1_EventScript_Elizabeth_AfterGift::
	msgbox NewSinjoh_House1_Text_GoodToSeeYouAgain MSGBOX_DEFAULT
	release
	end

NewSinjoh_House1_Text_GoodToSeeYouAgain:
    .string "Qué bueno verte de nuevo,\n"
	.string "{PLAYER}.\p"
	.string "¿Cómo has estado tratando a\n"
	.string "ese WOOPER?$"

NewSinjoh_House1_Bookshelf::
    lock
	msgbox NewSinjoh_House1_Bookshelf_Text MSGBOX_DEFAULT
	release
	end

NewSinjoh_House1_Bookshelf_Text:
    .string "¡Es un estante lleno de\n"
	.string "videojuegos y novelas gráficas!$"

NewSinjoh_House1_Eevee::
    lock
	faceplayer
	playmoncry SPECIES_EEVEE, 0
	msgbox NewSinjoh_House1_Text_Eevee_Cry, MSGBOX_DEFAULT
	waitmoncry
    closemessage
	release
	end

NewSinjoh_House1_Text_Eevee_Cry:
    .string "¿Vee Vee?$"
