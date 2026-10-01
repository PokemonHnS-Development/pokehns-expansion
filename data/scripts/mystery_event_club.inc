.equ GAVE_PROFILE,  VAR_TEMP_1

MysteryEventClub_EventScript_Woman::
	lock
	faceplayer
	goto_if_eq GAVE_PROFILE, TRUE, EventScript_AlreadyGaveProfile
	goto_if_set FLAG_SYS_SET_TRAINER_CARD_PROFILE, EventScript_GivenProfileBefore
	msgbox Text_IdLoveToHearYourProfile
	goto EventScript_AskForProfile
	end

EventScript_AlreadyGaveProfile:
	msgbox Text_TellMoreNextTime
	release
	end

EventScript_AskForProfile:
	message Text_TellMeWhatsYourProfile
	waitmessage
	multichoice 18, 6, MULTI_YESNOINFO_2, FALSE
	switch VAR_RESULT
	case 0, EventScript_AcceptGiveProfile
	case 1, EventScript_DeclineGiveProfile
	case 2, EventScript_ProfileInfo
	case MULTI_B_PRESSED, EventScript_DeclineGiveProfile
	end

EventScript_ProfileInfo:
	msgbox Text_ExplainProfile
	goto EventScript_AskForProfile
	end

EventScript_AcceptGiveProfile:
	msgbox Text_WhatsYourProfile
	closemessage
	goto EventScript_GiveProfile
	end

EventScript_CancelGiveProfile:
	msgbox Text_DecidedNotTo
	release
	end

EventScript_GaveProfile:
	setvar GAVE_PROFILE, TRUE
	setvar VAR_0x8004, 0
	special ShowEasyChatProfile
	waitmessage
	delay 80
	msgbox Text_ProfileSaysSomethingAboutYou
	release
	end

EventScript_DeclineGiveProfile:
	msgbox Text_DontBeLikeThat
	release
	end

EventScript_GivenProfileBefore:
	msgbox Text_HiWeMeetAgain
	goto EventScript_AskForNewProfile
	end

EventScript_AskForNewProfile:
	message Text_ChangeYourProfile
	waitmessage
	multichoice 18, 6, MULTI_YESNOINFO_2, FALSE
	switch VAR_RESULT
	case 0, EventScript_AcceptGiveNewProfile
	case 1, EventScript_DeclineGiveNewProfile
	case 2, EventScript_ProfileInfo2
	@case MULTI_B_PRESSED, EventScript_DeclineGiveNewProfile
	end

EventScript_ProfileInfo2:
	msgbox Text_ExplainProfile
	goto EventScript_AskForNewProfile
	end

EventScript_AcceptGiveNewProfile:
	msgbox Text_WhatAreYouLikeNow
	closemessage
	goto EventScript_GiveProfile
	end

EventScript_DeclineGiveNewProfile:
	msgbox Text_LikeProfileWayItIs
	release
	end

EventScript_GaveSpecialProfile:
	setvar GAVE_PROFILE, TRUE
	setvar VAR_0x8004, 0
	special ShowEasyChatProfile
	waitmessage
	delay 80
	msgbox Text_HeardThatBefore
	release
	end

EventScript_GiveProfile:
	setvar VAR_0x8004, EASY_CHAT_TYPE_PROFILE
	call Common_ShowEasyChatScreen
	lock
	faceplayer
	goto_if_eq VAR_0x8004, 0, EventScript_GaveSpecialProfile
	goto_if_eq VAR_RESULT, FALSE, EventScript_CancelGiveProfile
	goto_if_eq VAR_RESULT, TRUE, EventScript_GaveProfile
	end

Text_IdLoveToHearYourProfile:
	.string "¡Hola, gusto en conocerte!\p"
	.string "...Qué antipático eres.\n"
	.string "¿Por qué no me saludas tú?\p"
	.string "Anda, cuéntame algo sobre\n"
	.string "ti.\p"
	.string "¡Me encantaría ver tu perfil!$"

Text_TellMeWhatsYourProfile:
	.string "Dime algo bueno sobre\n"
	.string "ti. ¿Cómo es tu perfil?$"

Text_ExplainProfile:
	.string "Un perfil se escribe usando cuatro\n"
	.string "palabras o frases.\p"
	.string "Hay muchísimas palabras para\n"
	.string "elegir para tu perfil.\p"
	.string "Las palabras y frases están\n"
	.string "en varios grupos convenientes.\p"
	.string "Primero elige un grupo y luego\n"
	.string "una palabra o frase.\p"
	.string "...Es más fácil de lo que parece.\n"
	.string "¿Por qué no lo intentas?$"

Text_WhatsYourProfile:
	.string "¿Cuál es tu perfil?$"

Text_DontBeLikeThat:
	.string "Aww... No seas así.\n"
	.string "Puedes decirme tu perfil.$"

Text_DecidedNotTo:
	.string "Oh, ¿decidiste no hacerlo?\n"
	.string "Eres muy indeciso, ¿verdad?$"

Text_HiWeMeetAgain:
	.string "Hi!\n"
	.string "¡Nos volvemos a ver!$"

Text_ChangeYourProfile:
	.string "¿Quieres cambiar tu\n"
	.string "perfil?$"

Text_WhatAreYouLikeNow:
	.string "¿Cómo eres ahora?\n"
	.string "¡Tengo muchas ganas de saberlo!$"

Text_LikeProfileWayItIs:
	.string "Está bien, te gusta tu perfil\n"
	.string "tal como está.\p"
	.string "Yo también lo creo.$"

Text_ProfileSaysSomethingAboutYou:
	.string "Hmhm...\p"
	.string "Tu perfil dice mucho\n"
	.string "sobre quién eres.\p"
	.string "¡Ahora que te conozco mejor,\n"
	.string "seremos mejores amigos que nunca!$"

Text_HeardThatBefore:
	.string "Oh, ya he oído eso antes...\p"
	.string "Mi primo, que vive muy lejos,\n"
	.string "siempre decía eso, creo.$"

Text_TellMoreNextTime:
	.string "¡Cuéntame más sobre ti\n"
	.string "la próxima vez!$"
