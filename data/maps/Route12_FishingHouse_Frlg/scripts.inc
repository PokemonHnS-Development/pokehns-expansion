Route12_FishingHouse_Frlg_MapScripts::
	.byte 0

Route12_FishingHouse_EventScript_FishingGuruBrother::
	lock
	faceplayer
	goto_if_set FLAG_GOT_SUPER_ROD, Route12_FishingHouse_EventScript_CheckMagikarpRecord
	msgbox Route12_FishingHouse_Text_DoYouLikeToFish, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route12_FishingHouse_EventScript_GiveSuperRod
	msgbox Route12_FishingHouse_Text_OhThatsDisappointing
	release
	end

Route12_FishingHouse_EventScript_GiveSuperRod::
	checkitemspace ITEM_SUPER_ROD
	goto_if_eq VAR_RESULT, FALSE, Route12_FishingHouse_EventScript_NoRoomForSuperRod
	additem ITEM_SUPER_ROD
	msgbox Route12_FishingHouse_Text_TakeThisAndFish
	msgreceiveditem Route12_FishingHouse_Text_ReceivedSuperRod, ITEM_SUPER_ROD
	setflag FLAG_GOT_SUPER_ROD
	msgbox Route12_FishingHouse_Text_IfYouCatchBigMagikarpShowMe
	release
	end

Route12_FishingHouse_EventScript_NoRoomForSuperRod::
	msgbox Route12_FishingHouse_Text_NoRoomForGift
	release
	end

Route12_FishingHouse_EventScript_CheckMagikarpRecord::
	setvar VAR_0x8004, SPECIES_MAGIKARP
	specialvar VAR_RESULT, DoesPlayerPartyContainSpecies
	goto_if_eq VAR_RESULT, FALSE, Route12_FishingHouse_EventScript_NoMagikarpInParty
	special GetMagikarpSizeRecordInfo
	msgbox Route12_FishingHouse_Text_OhMagikarpAllowMeToSee
	special ChoosePartyMon
	waitstate
	copyvar VAR_RESULT, VAR_0x8004
	goto_if_ge VAR_RESULT, PARTY_SIZE, Route12_FishingHouse_EventScript_CancelShowMon
	special CompareMagikarpSize
	goto_if_eq VAR_RESULT, 1, Route12_FishingHouse_EventScript_NotMagikarp
	goto_if_eq VAR_RESULT, 2, Route12_FishingHouse_EventScript_NotRecordMagikarp
	goto_if_eq VAR_RESULT, 3, Route12_FishingHouse_EventScript_NewRecordMagikarp
	goto_if_eq VAR_RESULT, 4, Route12_FishingHouse_EventScript_TieRecordMagikarp
	release
	end

Route12_FishingHouse_EventScript_NoMagikarpInParty::
	msgbox Route12_FishingHouse_Text_TryFishingBringMeMagikarp
	release
	end

Route12_FishingHouse_EventScript_CancelShowMon::
	release
	end

Route12_FishingHouse_EventScript_NotMagikarp::
	msgbox Route12_FishingHouse_Text_DoesntLookLikeMagikarp
	release
	end

Route12_FishingHouse_EventScript_NotRecordMagikarp::
	goto_if_unset FLAG_GOT_RECORD_SETTING_MAGIKARP, Route12_FishingHouse_EventScript_NewRecordMagikarp
	msgbox Route12_FishingHouse_Text_HmmXInchesDoesntMeasureUp
	release
	end

Route12_FishingHouse_EventScript_TieRecordMagikarp::
	goto_if_unset FLAG_GOT_RECORD_SETTING_MAGIKARP, Route12_FishingHouse_EventScript_NewRecordMagikarp
	msgbox Route12_FishingHouse_Text_HuhXInchesSameSizeAsLast
	release
	end

Route12_FishingHouse_EventScript_NewRecordMagikarp::
	setflag FLAG_GOT_RECORD_SETTING_MAGIKARP
	msgbox Route12_FishingHouse_Text_WhoaXInchesTakeThis
	giveitem ITEM_NET_BALL
	goto_if_eq VAR_RESULT, FALSE, Route12_FishingHouse_EventScript_NoRoomForNetBall
	msgbox Route12_FishingHouse_Text_LookForwardToGreaterRecords
	release
	end

Route12_FishingHouse_EventScript_NoRoomForNetBall::
	msgbox Route12_FishingHouse_Text_NoRoomForGift
	release
	end

Route12_FishingHouse_EventScript_MagikarpRecordSign::
	lockall
	goto_if_set FLAG_GOT_RECORD_SETTING_MAGIKARP, Route12_FishingHouse_EventScript_MagikarpRecordSignRecordSet
	msgbox Route12_FishingHouse_Text_BlankChartOfSomeSort
	releaseall
	end

Route12_FishingHouse_EventScript_MagikarpRecordSignRecordSet::
	special GetMagikarpSizeRecordInfo
	msgbox Route12_FishingHouse_Text_MostGiganticMagikarpXInches
	releaseall
	end

Route12_FishingHouse_Text_DoYouLikeToFish::
	.string "Soy el hermano menor del\n"
	.string "EXPERTO EN PESCA.\p"
	.string "I simply looove fishing!\n"
	.string "No soporto ir sin él.\p"
	.string "Dime, ¿te gusta pescar?$"

Route12_FishingHouse_Text_TakeThisAndFish::
	.string "¡Genial! Me gusta tu estilo.\n"
	.string "Creo que podemos ser amigos.\p"
	.string "¡Toma esto y pesca, joven amigo!$"

Route12_FishingHouse_Text_ReceivedSuperRod::
	.string "{PLAYER} recibió una CAÑA SÚPER de\n"
	.string "el hermano del MAESTRO PESCADOR.$"

Route12_FishingHouse_Text_IfYouCatchBigMagikarpShowMe::
	.string "¡Pescar es un modo de vida!\n"
	.string "Es como la mejor poesía.\p"
	.string "De los mares a los ríos, sal\n"
	.string "y pesques uno grande, amigo.\p"
	.string "Ahora, tengo una petición.\p"
	.string "Si pescas un MAGIKARP grande \n"
	.string "con esa CAÑA, quiero verlo.\p"
	.string "Por más que me encanta pescar,\n"
	.string "love seeing gigantic MAGIKARP.$"

Route12_FishingHouse_Text_OhThatsDisappointing::
	.string "Oh...\n"
	.string "Qué decepción...$"

Route12_FishingHouse_Text_TryFishingBringMeMagikarp::
	.string "¡Hola, {PLAYER}!\n"
	.string "¿Has estado pescando?\p"
	.string "Prueba a pescar con la\n"
	.string "CAÑA SÚPER en cualquier agua.\p"
	.string "You'll find different POKéMON in\n"
	.string "otros lugares.\p"
	.string "Ah, y no olvides traerme\n"
	.string "gigantic MAGIKARP.$"

Route12_FishingHouse_Text_OhMagikarpAllowMeToSee::
	.string "Oh? {PLAYER}?\n"
	.string "¡Vaya, si es un MAGIKARP!\p"
	.string "¡Déjame verlo, rápido!$"

Route12_FishingHouse_Text_WhoaXInchesTakeThis::
	.string "... ... ...Whoa!\n"
	.string "{STR_VAR_2} inches!\p"
	.string "Tienes un aprecio poco común\n"
	.string "por lo poético de la pesca!\p"
	.string "Debes llevarte esto.\n"
	.string "I insist!$"

Route12_FishingHouse_Text_LookForwardToGreaterRecords::
	.string "¡Espero ver mejores\n"
	.string "marcas tuyas!$"

Route12_FishingHouse_Text_HuhXInchesSameSizeAsLast::
	.string "¿Eh?\n"
	.string "{STR_VAR_2} inches?\p"
	.string "Es del mismo tamaño que el\n"
	.string "I saw before.$"

Route12_FishingHouse_Text_HmmXInchesDoesntMeasureUp::
	.string "Hmm...\n"
	.string "Este mide {STR_VAR_2} pulgadas.\p"
	.string "No llega a medir lo\n"
	.string "{STR_VAR_3}-inch one you brought before.$"

Route12_FishingHouse_Text_DoesntLookLikeMagikarp::
	.string "Eh... Eso no parece muy\n"
	.string "un MAGIKARP.$"

Route12_FishingHouse_Text_NoRoomForGift::
	.string "¡Oh, no!\p"
	.string "Tenía un regalo para ti, pero no\n"
	.string "tienes espacio para él.$"

Route12_FishingHouse_Text_MostGiganticMagikarpXInches::
	.string "El MAGIKARP más gigantesco\n"
	.string "que he visto jamás...\p"
	.string "{STR_VAR_3} inches!$"

Route12_FishingHouse_Text_BlankChartOfSomeSort::
	.string "Es una tabla en blanco.\p"
	.string "Tiene espacios para escribir en\n"
	.string "algún tipo de registro.$"

