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
	.string "Ay, es tan difícil cada día…\p"
	.string "¿Qué es lo difícil?\n"
	.string "¿En serio lo preguntas?\p"
	.string "Pensar en qué cocinar\n"
	.string "para las comidas cada día.\p"
	.string "No es nada fácil pensar en\n"
	.string "el menú de cada día.$"

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
	.string "He estado diciendo “{STR_VAR_1}”\n"
	.string "para divertirla últimamente.\p"
	.string "¿Conoces alguna palabra o frase\n"
	.string "mejor que pueda funcionar?$"

RustboroCity_Flat1_2F_Text_WonderfulLetsHearSuggestion:
	.string "Oh, eso es maravilloso.\n"
	.string "Bien, dime tu sugerencia.$"

RustboroCity_Flat1_2F_Text_OhIsThatRight:
	.string "Oh, ¿de verdad?\p"
	.string "Bueno, si se te ocurre una buena\n"
	.string "sugerencia, soy todo oídos.$"

RustboroCity_Flat1_2F_Text_LetsGiveItATry2:
	.string "Ah, ya veo.\n"
	.string "Bueno, intentémoslo, ¿te parece?$"

RustboroCity_Flat1_2F_Text_OhShesLaughing:
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "¡Oh, sí! ¡Se está riendo!\n"
	.string "¡Oh, estoy tan feliz como ella!$"

RustboroCity_Flat1_2F_Text_LetsGiveItATry:
	.string "Ah, ya veo.\n"
	.string "Bueno, intentémoslo, ¿te parece?$"

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll:
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "Hmmm... No está sonriendo nada.\n"
	.string "Quizá WALDA sea una niña seria...$"

RustboroCity_Flat1_2F_Text_ThinkOfMyOwnPhrase:
	.string "Oh, así que no sabes palabras.\nMejor pienso algo yo misma,\nentonces.\pHmm…\n¿Qué tal "{STR_VAR_1}"?\lVeamos si eso funciona.$"

RustboroCity_Flat1_2F_Text_ShesNotSmilingAtAll2:
	.string "{STR_VAR_1}.\n"
	.string "{STR_VAR_1}.\p"
	.string "Hmmm... No está sonriendo nada.\n"
	.string "Quizá WALDA sea una niña seria...$"

RustboroCity_Flat1_2F_Text_OhYouDontKnowAny:
	.string "Oh, así que no sabes palabras.\n"
	.string "Creo que intentaré divertirla con\l"
	.string "el dicho que usé antes.\p"
	.string "En fin, si tienes alguna sugerencia,\n"
	.string "no dudes en decírmelo, ¿vale?$"

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
	.string "It's a POKéMON plush DOLL!$"

