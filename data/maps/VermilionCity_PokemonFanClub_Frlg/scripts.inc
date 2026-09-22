.set SPOKE_TO_WOMAN_LAST,   FLAG_TEMP_2
.set SPOKE_TO_FAT_MAN_LAST, FLAG_TEMP_3

VermilionCity_PokemonFanClub_Frlg_MapScripts::
	.byte 0

VermilionCity_PokemonFanClub_EventScript_Chairman::
	lock
	faceplayer
	goto_if_set FLAG_GOT_BIKE_VOUCHER, VermilionCity_PokemonFanClub_EventScript_AlreadyHeardStory
	msgbox VermilionCity_PokemonFanClub_Text_DidYouComeToHearAboutMyMons, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, VermilionCity_PokemonFanClub_EventScript_ChairmanStory
	msgbox VermilionCity_PokemonFanClub_Text_ComeBackToHearStory
	release
	end

VermilionCity_PokemonFanClub_EventScript_AlreadyHeardStory::
	msgbox VermilionCity_PokemonFanClub_Text_DidntComeToSeeAboutMonsAgain
	release
	end

VermilionCity_PokemonFanClub_EventScript_ChairmanStory::
	msgbox VermilionCity_PokemonFanClub_Text_ChairmansStory
	checkitemspace ITEM_BIKE_VOUCHER
	goto_if_eq VAR_RESULT, FALSE, VermilionCity_PokemonFanClub_EventScript_NoRoomForBikeVoucher
	setflag FLAG_GOT_BIKE_VOUCHER
	giveitem_msg VermilionCity_PokemonFanClub_Text_ReceivedBikeVoucherFromChairman, ITEM_BIKE_VOUCHER, 1, MUS_RG_OBTAIN_KEY_ITEM
	msgbox VermilionCity_PokemonFanClub_Text_ExplainBikeVoucher
	release
	end

VermilionCity_PokemonFanClub_EventScript_NoRoomForBikeVoucher::
	msgbox VermilionCity_PokemonFanClub_Text_MakeRoomForThis
	release
	end

VermilionCity_PokemonFanClub_EventScript_WorkerF::
	lock
	faceplayer
	goto_if_set FLAG_SYS_GAME_CLEAR, VermilionCity_PokemonFanClub_EventScript_WorkerFGameClear
	msgbox VermilionCity_PokemonFanClub_Text_ChairmanVeryVocalAboutPokemon
	release
	end

VermilionCity_PokemonFanClub_EventScript_WorkerFGameClear::
	famechecker FAMECHECKER_DAISY, 1
	msgbox VermilionCity_PokemonFanClub_Text_ChairmanReallyAdoresHisMons
	release
	end

VermilionCity_PokemonFanClub_EventScript_Woman::
	lock
	faceplayer
	goto_if_set SPOKE_TO_FAT_MAN_LAST, VermilionCity_PokemonFanClub_EventScript_WomanSpokeToFatMan
	msgbox VermilionCity_PokemonFanClub_Text_AdoreMySeel
	closemessage
	applymovement LOCALID_POKEMON_FAN_CLUB_WOMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag SPOKE_TO_WOMAN_LAST
	release
	end

VermilionCity_PokemonFanClub_EventScript_WomanSpokeToFatMan::
	msgbox VermilionCity_PokemonFanClub_Text_SeelFarMoreAttractive
	closemessage
	applymovement LOCALID_POKEMON_FAN_CLUB_WOMAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	clearflag SPOKE_TO_FAT_MAN_LAST
	release
	end

VermilionCity_PokemonFanClub_EventScript_FatMan::
	lock
	faceplayer
	goto_if_set SPOKE_TO_WOMAN_LAST, VermilionCity_PokemonFanClub_EventScript_FatManSpokeToWoman
	msgbox VermilionCity_PokemonFanClub_Text_AdmirePikachusTail
	closemessage
	applymovement LOCALID_POKEMON_FAN_CLUB_FAT_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag SPOKE_TO_FAT_MAN_LAST
	release
	end

VermilionCity_PokemonFanClub_EventScript_FatManSpokeToWoman::
	msgbox VermilionCity_PokemonFanClub_Text_PikachuTwiceAsCute
	closemessage
	applymovement LOCALID_POKEMON_FAN_CLUB_FAT_MAN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	clearflag SPOKE_TO_WOMAN_LAST
	release
	end

VermilionCity_PokemonFanClub_EventScript_Pikachu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, CRY_MODE_NORMAL
	msgbox VermilionCity_PokemonFanClub_Text_Pikachu
	waitmoncry
	release
	end

VermilionCity_PokemonFanClub_EventScript_Seel::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SEEL, CRY_MODE_NORMAL
	msgbox VermilionCity_PokemonFanClub_Text_Seel
	waitmoncry
	release
	end

VermilionCity_PokemonFanClub_EventScript_RulesSign1::
	msgbox VermilionCity_PokemonFanClub_Text_ListenPolitelyToOtherTrainers, MSGBOX_SIGN
	end

VermilionCity_PokemonFanClub_EventScript_RulesSign2::
	msgbox VermilionCity_PokemonFanClub_Text_SomeoneBragsBragBack, MSGBOX_SIGN
	end

VermilionCity_PokemonFanClub_Text_AdmirePikachusTail::
	.string "¿No admiras a mi PIKACHU?\n"
	.string "adorable tail?$"

VermilionCity_PokemonFanClub_Text_PikachuTwiceAsCute::
	.string "¡Hmph!\p"
	.string "Mi PIKACHU es el doble de lindo\n"
	.string "que ese!$"

VermilionCity_PokemonFanClub_Text_AdoreMySeel::
	.string "¡Amo a mi SEEL!\n"
	.string "¡Es tan adorable!\p"
	.string "Chilla “Kyuuuh“ cuando\n"
	.string "¡abrázalo!$"

VermilionCity_PokemonFanClub_Text_SeelFarMoreAttractive::
	.string "¡Cielos!\p"
	.string "Mi SEEL es mucho más atractivo.\n"
	.string "¡El doble, diría yo!$"

VermilionCity_PokemonFanClub_Text_Pikachu::
	.string "PIKACHU: Chu! Pikachu!$"

VermilionCity_PokemonFanClub_Text_Seel::
	.string "SEEL: Kyuoo!$"

VermilionCity_PokemonFanClub_Text_DidYouComeToHearAboutMyMons::
	.string "I chair the POKéMON Fan Club!\p"
	.string "Crío más de un centenar\n"
	.string "exóticos POKéMON!\p"
	.string "Soy muy exigente en cuanto a\n"
	.string "POKéMON! I surely am!\p"
	.string "So…\p"
	.string "¿Vienes a escuchar sobre mí?\n"
	.string "de mis POKéMON?$"

VermilionCity_PokemonFanClub_Text_ChairmansStory::
	.string "¡Bien!\n"
	.string "Then listen up!\p"
	.string "Mi RAPIDASH favorito…\p"
	.string "Es…lindo…hermoso…listo…\n"
	.string "además…increíble…¿no crees?…\l"
	.string "oh sí…es…deslumbrante…\l"
	.string "amablemente…¡me encanta!\p"
	.string "Abrázalo…cuando…duerme…cálido\n"
	.string "y acogedor…espectacular…\l"
	.string "ravishing…\l"
	.string "…¡Ups! ¡Mira la hora!\l"
	.string "¡Te he retenido demasiado!\p"
	.string "¡Gracias por escucharme!\n"
	.string "¡Quiero que tengas esto!$"

VermilionCity_PokemonFanClub_Text_ReceivedBikeVoucherFromChairman::
	.string "{PLAYER} recibió un BONO DE\n"
	.string "BICICLETA del PRESIDENTE.$"

VermilionCity_PokemonFanClub_Text_ExplainBikeVoucher::
	.string "Lleva ese BONO DE BICICLETA\n"
	.string "BIKE SHOP in CERULEAN CITY.\p"
	.string "Cámbialo por una BICICLETA\n"
	.string "¡gratis!\p"
	.string "No te preocupes, mi SPEAROW\n"
	.string "will FLY me anywhere I need to go.\p"
	.string "quiera ir.\p"
	.string "¡Espero que te guste el ciclismo!$"

VermilionCity_PokemonFanClub_Text_ComeBackToHearStory::
	.string "Oh. Vuelve cuando quieras\n"
	.string "escuchar mi historia!$"

VermilionCity_PokemonFanClub_Text_DidntComeToSeeAboutMonsAgain::
	.string "¡Hola, {PLAYER}!\p"
	.string "¿Vienes a verme por mi\n"
	.string "POKéMON otra vez?\p"
	.string "¿No?\n"
	.string "¡Qué mal!$"

VermilionCity_PokemonFanClub_Text_MakeRoomForThis::
	.string "¡Abre espacio para esto!$"

VermilionCity_PokemonFanClub_Text_ChairmanVeryVocalAboutPokemon::
	.string "Nuestro PRESIDENTE es muy\n"
	.string "POKéMON.$"

VermilionCity_PokemonFanClub_Text_ListenPolitelyToOtherTrainers::
	.string "Escuchemos con cortesía a los\n"
	.string "¡ENTRENADORES!$"

VermilionCity_PokemonFanClub_Text_SomeoneBragsBragBack::
	.string "If someone brags, brag right back!$"

VermilionCity_PokemonFanClub_Text_ChairmanReallyAdoresHisMons::
	.string "A nuestro PRESIDENTE le encanta\n"
	.string "POKéMON planta.\p"
	.string "Pero quien más aprecio recibe\n"
	.string "POKéMON es DAISY, creo.$"
