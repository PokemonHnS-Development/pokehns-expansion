FuchsiaCity_House2_Frlg_MapScripts::
	.byte 0

FuchsiaCity_House2_EventScript_FishingGurusBrother::
	lock
	faceplayer
	goto_if_set FLAG_GOT_GOOD_ROD, FuchsiaCity_House2_EventScript_AlreadyGotGoodRod
	msgbox FuchsiaCity_House2_Text_DoYouLikeToFish, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, FuchsiaCity_House2_EventScript_GiveGoodRod
	msgbox FuchsiaCity_House2_Text_OhThatsDisappointing
	release
	end

FuchsiaCity_House2_EventScript_AlreadyGotGoodRod::
	msgbox FuchsiaCity_House2_Text_HowAreTheFishBiting
	release
	end

FuchsiaCity_House2_EventScript_GiveGoodRod::
	msgbox FuchsiaCity_House2_Text_LikeYourStyleTakeThis
	checkitemspace ITEM_GOOD_ROD
	goto_if_eq VAR_RESULT, FALSE, FuchsiaCity_House2_EventScript_NoRoomForGoodRod
	giveitem_msg FuchsiaCity_House2_Text_ReceivedGoodRod, ITEM_GOOD_ROD
	msgbox FuchsiaCity_House2_Text_GoodRodCanCatchBetterMons
	setflag FLAG_GOT_GOOD_ROD
	release
	end

FuchsiaCity_House2_EventScript_NoRoomForGoodRod::
	msgbox FuchsiaCity_House2_Text_YouHaveNoRoomForGift
	release
	end

FuchsiaCity_House2_Text_DoYouLikeToFish::
	.string "Soy el hermano mayor del GURÚ\n"
	.string "EXPERTO EN PESCA.\p"
	.string "I simply looove fishing!\n"
	.string "No puedo soportar ir sin él.\p"
	.string "Dime, te gusta pescar?$"

FuchsiaCity_House2_Text_LikeYourStyleTakeThis::
	.string "¡Genial! Me gusta tu estilo.\n"
	.string "Creo que podemos ser amigos.\p"
	.string "¡Toma esto y pesca, joven amigo!$"

FuchsiaCity_House2_Text_ReceivedGoodRod::
	.string "{PLAYER} recibió una CAÑA BUENA\n"
	.string "el hermano del GURÚ DE LA PESCA.$"

FuchsiaCity_House2_Text_GoodRodCanCatchBetterMons::
	.string "¡La pesca es un estilo de vida!\n"
	.string "Es como la mejor poesía.\p"
	.string "Una VIEJA CAÑA mala solo\n"
	.string "atrapaba MAGIKARP, ¿verdad?\p"
	.string "Pero con una CAÑA BUENA puedes\n"
	.string "catch much better POKéMON.$"

FuchsiaCity_House2_Text_OhThatsDisappointing::
	.string "Oh…\n"
	.string "Qué decepción…$"

FuchsiaCity_House2_Text_HowAreTheFishBiting::
	.string "¡Hola, {PLAYER}!\p"
	.string "¿Cómo pican los peces?$"

FuchsiaCity_House2_Text_YouHaveNoRoomForGift::
	.string "¡Oh, no!\p"
	.string "Tenía un regalo para ti, pero\n"
	.string "¡no hay espacio!$"

