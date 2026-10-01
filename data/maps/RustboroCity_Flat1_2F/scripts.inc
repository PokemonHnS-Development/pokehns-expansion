RustboroCity_Flat1_2F_MapScripts::
	.byte 0

RustboroCity_Flat1_2F_EventScript_WaldasDad::
	lock
	faceplayer
	specialvar VAR_RESULT, TryBufferWaldaPhrase
	goto_if_eq VAR_RESULT, FALSE, RustboroCity_Flat1_2F_EventScript_WaldasDadFirstPhrase
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Flat1_2F_EventScript_WaldasDadNewPhrase

RustboroCity_Flat1_2F_EventScript_GivePhrase::
	special DoWaldaNamingScreen
	waitstate
	goto_if_eq VAR_0x8004, 1, RustboroCity_Flat1_2F_EventScript_CancelGivePhrase
	goto_if_eq VAR_0x8004, 2, RustboroCity_Flat1_2F_EventScript_CancelGiveFirstPhrase
	specialvar VAR_RESULT, TryGetWallpaperWithWaldaPhrase
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Flat1_2F_EventScript_WaldaLikesPhrase
	goto_if_eq VAR_RESULT, FALSE, RustboroCity_Flat1_2F_EventScript_WaldaDoesntLikePhrase
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFirstPhrase::
	msgbox RustboroCity_Flat1_2F_Text_HelloDoYouKnowFunnyPhrase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_GivePhrase

RustboroCity_Flat1_2F_EventScript_WaldasDadNewPhrase::
	msgbox RustboroCity_Flat1_2F_Text_BeenSayingXDoYouKnowBetterPhrase, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase
	msgbox RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion, MSGBOX_DEFAULT
	goto RustboroCity_Flat1_2F_EventScript_GivePhrase

RustboroCity_Flat1_2F_EventScript_DeclineGivePhrase::
	msgbox RustboroCity_Flat1_2F_Text_OhIsThatRight, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_CancelGivePhrase::
	msgbox RustboroCity_Flat1_2F_Text_OhYouDontKnowAny, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_CancelGiveFirstPhrase::
	msgbox RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldaLikesPhrase::
	msgbox RustboroCity_Flat1_2F_Text_LetsGiveItATry2, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_OhShesLaughing, MSGBOX_DEFAULT
	applymovement LOCALID_WALDAS_DAD, Common_Movement_FacePlayer
	waitmovement 0
	msgbox RustboroCity_Flat1_2F_Text_ThankYouIllGiveYouWallpaper, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldaDoesntLikePhrase::
	msgbox RustboroCity_Flat1_2F_Text_LetsGiveItATry, MSGBOX_DEFAULT
	call RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda
	msgbox RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll, MSGBOX_DEFAULT
	release
	end

RustboroCity_Flat1_2F_EventScript_WaldasDadFaceWalda::
	turnobject LOCALID_WALDAS_DAD, DIR_EAST
	return

RustboroCity_Flat1_2F_EventScript_WaldasMom::
	msgbox RustboroCity_Flat1_2F_Text_ComingUpWithMealsIsHard, MSGBOX_NPC
	end

RustboroCity_Flat1_2F_EventScript_PokeDoll::
	msgbox RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll, MSGBOX_SIGN
	end

RustboroCity_Flat1_2F_Text_ComingUpWithMealsIsHard:
	.string "Ay, qué difícil es todos los días...\p¿Qué es difícil?\n¿Hace falta preguntar?\pEs pensar qué hacer de comer\ntodos los días.\pLa verdad es que no es fácil\npensar en la comida diaria.$"

RustboroCity_Flat1_2F_Text_HelloDoYouKnowFunnyPhrase:
	.string "¡Oh, hola!\n"
	.string "Bienvenidos a casa de PEPPER.\p"
	.string "Tengo una pregunta para ti.\n"
	.string "¿Has cuidado niños alguna vez?\p"
	.string "Soy padre primerizo, así que criar\n"
	.string "a un niño es nuevo para mí.\p"
	.string "Y tengo un problema. Mi hija\n"
	.string "WALDA no se ríe lo suficiente.\p"
	.string "Creo que se reiría si le dijera\n"
	.string "algo divertido.\p"
	.string "¿Conoces alguna palabra o frase\n"
	.string "divertida que me puedas decir?$"

RustboroCity_Flat1_2F_Text_BeenSayingXDoYouKnowBetterPhrase:
	.string "Últimamente le digo “{STR_VAR_1}”\npara divertirla.\p¿Se te ocurre alguna palabra o\nfrase que funcione mejor?$"

RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion:
	.string "Oh, qué bien.\nA ver, dime tu sugerencia.$"

RustboroCity_Flat1_2F_Text_OhIsThatRight:
	.string "Oh, ¿de verdad?\p"
	.string "Bueno, si se te ocurre una buena\n"
	.string "sugerencia, soy todo oídos.$"

RustboroCity_Flat1_2F_Text_LetsGiveItATry2:
	.string "Ah, ya veo.\nBueno, vamos a probarlo, ¿sí?$"

RustboroCity_Flat1_2F_Text_OhShesLaughing:
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "¡Oh, sí! ¡Se está riendo!\n"
	.string "¡Oh, estoy tan feliz como ella!$"

RustboroCity_Flat1_2F_Text_LetsGiveItATry:
	.string "Ah, ya veo.\nBueno, vamos a probarlo, ¿sí?$"

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll:
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "Hmmm... No está sonriendo nada.\n"
	.string "Quizá WALDA sea una niña seria...$"

RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase:
	.string "Ah, no sabes ninguna palabra.\nEntonces, mejor pienso yo solo.\pMmm...\n¿Qué tal “{STR_VAR_1}”?\lA ver si funciona.$"

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2:
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "Hmmm... No está sonriendo nada.\n"
	.string "Quizá WALDA sea una niña seria...$"

RustboroCity_Flat1_2F_Text_OhYouDontKnowAny:
	.string "Ah, no sabes ninguna palabra.\nEntonces trataré de divertirla con\llo que le decía antes.\pEn fin, si se te ocurre algo bueno,\nno dudes en decírmelo, ¿sí?$"

RustboroCity_Flat1_2F_Text_ThankYouIllGiveYouWallpaper:
	.string "¡Gracias!\p"
	.string "¡Gracias a ti, mi querida WALDA\n"
	.string "se ha reído!\p"
	.string "En realidad, puede que no me vea\n"
	.string "tan especial, pero soy uno de los\l"
	.string "mejores investigadores de DEVON\p"
	.string "CORPORATION. Así que, ¿qué tal si\n"
	.string "hago algo a cambio por ti?\p"
	.string "Ya sé, pondré un papel tapiz nuevo\n"
	.string "diseños para las CAJAS de la PC\l"
	.string "Sistema de Almacenamiento POKéMON.\p"
	.string "En el menú de diseños de fondo,\n"
	.string "select “FRIENDS.”\p"
	.string "Eso te dará acceso a los nuevos\n"
	.string "diseños de fondo.$"

RustboroCity_Flat1_2F_Text_ItsAPokemonPlushDoll:
	.string "¡Es un PELUCHE de POKéMON!$"

