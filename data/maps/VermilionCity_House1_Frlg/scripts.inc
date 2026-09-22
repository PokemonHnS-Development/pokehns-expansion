VermilionCity_House1_Frlg_MapScripts::
	.byte 0

VermilionCity_House1_EventScript_FishingGuru::
	lock
	faceplayer
	goto_if_set FLAG_GOT_OLD_ROD, VermilionCity_House1_EventScript_AlreadyGotOldRod
	msgbox VermilionCity_House1_Text_ImFishingGuruDoYouLikeToFish, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, VermilionCity_House1_EventScript_GiveOldRod
	msgbox VermilionCity_House1_Text_OhThatsSoDisappointing
	release
	end

VermilionCity_House1_EventScript_AlreadyGotOldRod::
	msgbox VermilionCity_House1_Text_HowAreTheFishBiting
	release
	end

VermilionCity_House1_EventScript_GiveOldRod::
	checkitemspace ITEM_OLD_ROD
	goto_if_eq VAR_RESULT, FALSE, VermilionCity_House1_EventScript_NoRoomForOldRod
	additem ITEM_OLD_ROD
	msgbox VermilionCity_House1_Text_TakeThisAndFish
	msgreceiveditem VermilionCity_House1_Text_ReceivedOldRodFromFishingGuru, ITEM_OLD_ROD
	setflag FLAG_GOT_OLD_ROD
	msgbox VermilionCity_House1_Text_FishingIsAWayOfLife
	release
	end

VermilionCity_House1_EventScript_NoRoomForOldRod::
	msgbox VermilionCity_House1_Text_NoRoomForNiceGift
	release
	end

VermilionCity_House1_Text_ImFishingGuruDoYouLikeToFish::
	.string "¡Soy el GURÚ DE LA PESCA!\p"
	.string "I simply looove fishing!\n"
	.string "No soporto salir sin él.\p"
	.string "Dime, ¿te gusta pescar?$"

VermilionCity_House1_Text_TakeThisAndFish::
	.string "¡Genial! Me gusta tu estilo.\n"
	.string "Creo que podemos ser amigos.\p"
	.string "Take this and fish, young friend!$"

VermilionCity_House1_Text_ReceivedOldRodFromFishingGuru::
	.string "{PLAYER} recibió una CAÑA\n"
	.string "VIEJA del GURÚ PESCADOR.$"

VermilionCity_House1_Text_FishingIsAWayOfLife::
	.string "¡Pescar es un modo de vida!\n"
	.string "Es como la mejor poesía.\p"
	.string "De los mares a los ríos, sal\n"
	.string "a pescar el grande, amigo.$"

VermilionCity_House1_Text_OhThatsSoDisappointing::
	.string "Oh...\n"
	.string "Qué decepción...$"

VermilionCity_House1_Text_HowAreTheFishBiting::
	.string "¡Hola, {PLAYER}!\p"
	.string "¿Cómo pican los peces?$"

VermilionCity_House1_Text_NoRoomForNiceGift::
	.string "¡Oh, no!\p"
	.string "Tenía un buen regalo para ti, pero\n"
	.string "¡no tienes espacio para él!$"

