PalletTown_House2_hns_MapScripts::
	.byte 0

PalletTown_House2_EventScript_Daisy::
	lock
	faceplayer
	goto_if_unset FLAG_HIDE_CINNABAR_BLUE, PalletTown_House2_EventScript_Blue
	goto_if_unset FLAG_DAILY_DAISY_GROOMED, PalletTown_House2_EventScript_DaisyGrooming
	msgbox PalletTown_House2_Text_AlreadyGroomed, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_House2_EventScript_Blue::
	msgbox PalletTown_House2_Text_Hello, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_House2_EventScript_DaisyDeclineGrooming::
	msgbox PalletTown_House2_Text_Refused, MSGBOX_DEFAULT
	closemessage
	release
	end
PalletTown_House2_EventScript_Egg::
	msgbox PalletTown_House2_Text_CantGroomEgg, MSGBOX_DEFAULT
	closemessage
	release
	end

PalletTown_House2_EventScript_DaisyGrooming::
	msgbox PalletTown_House2_Text_OfferGrooming, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, PalletTown_House2_EventScript_DaisyDeclineGrooming
	msgbox PalletTown_House2_Text_WhichMon, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	lock
	faceplayer
	bufferpartymonnick STR_VAR_1, VAR_0x8004
	goto_if_ge VAR_0x8004, PARTY_SIZE, PalletTown_House2_EventScript_DaisyDeclineGrooming
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	goto_if_eq VAR_RESULT, SPECIES_EGG, PalletTown_House2_EventScript_Egg
	goto_if_eq VAR_RESULT, FALSE, PalletTown_House2_EventScript_DaisyDeclineGrooming
	
	msgbox PalletTown_House2_Text_Alright
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HaircutBrother1
	fadescreen FADE_FROM_BLACK
	special BufferMonNickname
	msgbox PalletTown_House2_Text_AllDone
	setflag FLAG_DAILY_DAISY_GROOMED
	release
	end

PalletTown_House2_Text_Hello:
	.string "DAISY: ¡Hola! Mi hermano menor es el\n"
	.string "LÍDER del GIMNASIO de CIUDAD VERIDIAN.\p"
	.string "Pero sale tanto de la ciudad que\n"
	.string "les causa problemas a los\l"
	.string "ENTRENADORES.$"

PalletTown_House2_Text_OfferGrooming:
	.string "DAISY: ¡Hola! Llegas justo a tiempo.\n"
	.string "Voy a tomar un té.\p"
	.string "¿Te gustaría acompañarme?\p"
	.string "Tus POKéMON están algo sucios.\p"
	.string "¿Quieres que limpie a alguno?$"

PalletTown_House2_Text_WhichMon:
	.string "DAISY: ¿A cuál debo arreglar?$"

PalletTown_House2_Text_Alright:
	.string "DAISY: Bien, lo dejaré impecable\n"
	.string "bien en un abrir y cerrar de ojos.$"

PalletTown_House2_Text_AllDone:
	.string "DAISY: ¡Listo! Ya terminé.\p"
	.string "¿Ves? ¿No se ve bien {STR_VAR_1}?\n"
	.string "¿Lindo?\p"
	.string "Es un POKéMON muy lindo.$"

PalletTown_House2_Text_AlreadyGroomed:
	.string "DAISY: Siempre tomo el té a\n"
	.string "esta hora. Acompáñame.$"

PalletTown_House2_Text_Refused:
	.string "DAISY: ¿No quieres que\n"
	.string "lo arregle?\p"
	.string "Está bien, solo tomaremos té.$"

PalletTown_House2_Text_CantGroomEgg:
	.string "DAISY: Oh, lo siento. No puedo\n"
	.string "arreglar un HUEVO.$"
