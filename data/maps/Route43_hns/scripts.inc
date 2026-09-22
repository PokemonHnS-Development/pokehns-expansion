Route43_hns_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route43_MapScript_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, SetTimeEncounters
	.byte 0

Route43_MapScript_OnTransition::
	call_if_set FLAG_HIDE_ROUTE42_SUICUNE, Route42_MapScript_HideTrigger
	callnative SetTimeBasedEncounters
	end

Route43_EventScript_Ben::
	trainerbattle_single TRAINER_BEN_HNS, Route43_Text_PokemaniacBenSeen, Route43_Text_PokemaniacBenBeaten
	msgbox Route43_Text_PokemaniacBenAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Brent::
	trainerbattle_single TRAINER_BRENT_HNS, Route43_Text_PokemaniacBrentSeen, Route43_Text_PokemaniacBrentBeaten, Route43_EventScript_RegisterBrent
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route43_EventScript_RematchBrent
	msgbox Route43_Text_PokemaniacBrentAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_RegisterBrent::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route43_Text_BrentRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_BRENT_HNS
	release
	end

Route43_EventScript_RematchBrent::
	trainerbattle_rematch TRAINER_BRENT_HNS, Route43_Text_BrentRematchIntro, Route43_Text_BrentRematchDefeat
	msgbox Route43_Text_BrentPostRematch, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Ron::
	trainerbattle_single TRAINER_RON_HNS, Route43_Text_PokemaniacRonSeen, Route43_Text_PokemaniacRonBeaten
	msgbox Route43_Text_PokemaniacRonAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Marvin::
	trainerbattle_single TRAINER_MARVIN_HNS, Route43_Text_FisherMarvinSeen, Route43_Text_FisherMarvinBeaten
	msgbox Route43_Text_FisherMarvinAfter, MSGBOX_AUTOCLOSE
	end
	
Route43_EventScript_Spencer::
	trainerbattle_single TRAINER_SPENCER_HNS, Route43_Text_CamperSpencerSeen, Route43_Text_CamperSpencerBeaten
	msgbox Route43_Text_CamperSpencerAfter, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Tiffany::
	trainerbattle_single TRAINER_TIFFANY_HNS, Route43_Text_PicnickerTiffanySeen, Route43_Text_PicnickerTiffanyBeaten, Route43_EventScript_RegisterTiffany
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route43_EventScript_RematchTiffany
	msgbox Route43_Text_PicnickerTiffanyWantsPicnic, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_RegisterTiffany::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route43_Text_TiffanyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_TIFFANY_HNS
	release
	end

Route43_EventScript_RematchTiffany::
	trainerbattle_rematch TRAINER_TIFFANY_HNS, Route43_Text_TiffanyRematchIntro, Route43_Text_TiffanyRematchDefeat
	msgbox Route43_Text_TiffanyPostRematch, MSGBOX_AUTOCLOSE
	end

Route43_EventScript_Sign1::
	msgbox Route43_Sign2, MSGBOX_SIGN
	end

Route43_EventScript_Sign2::
	msgbox Route43_TrainerTips, MSGBOX_SIGN
	end

Route43_EventScript_Item_Max_Ether::
	finditem ITEM_MAX_ETHER
	end

Route43_Text_PokemaniacBenSeen:
    .string "¡Amo a los POKéMON!\p"
    .string "¡Por eso empecé y por eso\n"
    .string "seguiré atrapando POKéMON!$"

Route43_Text_PokemaniacBenBeaten:
    .string "¿Cómo pudiste hacerme esto?$"

Route43_Text_PokemaniacBenAfter:
    .string "¿Qué más me gusta aparte de\n"
    .string "con los POKéMON?\p"
    .string "MARY en la radio? ¡Apuesto a que\n"
    .string "es linda!$"

Route43_Text_PokemaniacBrentSeen:
    .string "¡Oye! ¿Tienes algún POKéMON\n"
    .string "POKéMON?$"

Route43_Text_PokemaniacBrentBeaten:
    .string "Oh, my poor POKéMON! Darlings!$"

Route43_Text_PokemaniacBrentAfter:
    .string "Sería feliz solo con tener un\n"
    .string "POKéMON raros.$"

Route43_Text_BrentRegister:
    .string "Sería feliz solo con tener un\n"
    .string "POKéMON raros.$"

Route43_Text_BrentRematchIntro:
    .string "¡Oye! ¿Tienes algún POKéMON\n"
    .string "POKéMON?$"

Route43_Text_BrentRematchDefeat:
    .string "Oh, my poor POKéMON! Darlings!$"

Route43_Text_BrentPostRematch:
    .string "Sería feliz solo con tener un\n"
    .string "POKéMON raros.$"

Route43_Text_PokemaniacRonSeen:
    .string "¿Podrías conseguir esto?\p"
    .string "Un tal {RIVAL} se burló de mi\n"
    .string "exóticos POKéMON!\p"
    .string "¡Rayos! ¡Mi POKéMON es genial!$"

Route43_Text_PokemaniacRonBeaten:
    .string "¡Mi NIDOKING lo hizo muy bien!$"

Route43_Text_PokemaniacRonAfter:
    .string "Está bien que a la gente le guste\n"
    .string "distintos tipos de POKéMON.\p"
    .string "POKéMON no es solo tener al\n"
    .string "más poderoso.$"

Route43_Text_FisherMarvinSeen:
    .string "Estoy en una mala racha.\p"
    .string "Quizás es el equipo que uso.\p"
    .string "¡Luchemos para cambiar el ritmo!$"

Route43_Text_FisherMarvinBeaten:
    .string "I lost, but I feel better anyway.$"

Route43_Text_FisherMarvinAfter:
    .string "La LURE BALL de KURT es la mejor\n"
    .string "para capturar POKéMON pescados.\p"
    .string "Es mucho más efectiva que una\n"
    .string "ULTRA BALL.$"

Route43_Text_CamperSpencerSeen:
    .string "Puedo hacer mucho con mis\n"
    .string "POKéMON... ¡es superdivertido!$"

Route43_Text_CamperSpencerBeaten:
    .string "Perder no es nada divertido...$"

Route43_Text_CamperSpencerAfter:
    .string "¿Qué pasa en el LAGO DE la FURIA?\p"
    .string "Planeábamos acampar allí.$"

Route43_Text_PicnickerTiffanySeen:
    .string "¿Tú también vas al LAGO DE la FURIA?\p"
    .string "¡Juguemos un rato!$"

Route43_Text_PicnickerTiffanyBeaten:
    .string "¡Jugué demasiado!$"

Route43_Text_PicnickerTiffanyWantsPicnic:
    .string "Hago un picnic con POKéMON.\p"
    .string "¿No quieres unirte?$"

Route43_Text_TiffanyRegister:
    .string "Hago un picnic con POKéMON.\p"
    .string "¿No quieres unirte?$"

Route43_Text_TiffanyRematchIntro:
    .string "¿Tú también vas al LAGO DE la FURIA?\p"
    .string "¡Juguemos un rato!$"

Route43_Text_TiffanyRematchDefeat:
    .string "¡Jugué demasiado!$"

Route43_Text_TiffanyPostRematch:
    .string "Hago un picnic con POKéMON.\p"
    .string "¿No quieres unirte?$"

Route43_Sign1:
    .string "RUTA 43\p"
    .string "LAGO DE LA FURIA - PUEBLO CAOBA$"

Route43_Sign2:
    .string "RUTA 43\p"
    .string "LAGO DE LA FURIA - PUEBLO CAOBA$"

Route43_TrainerTips:
    .string "CONSEJOS DE ENTRENADOR\p"
    .string "Todo POKéMON tiene pros y contras\n"
    .string "según sus tipos.\p"
    .string "Si los tipos difieren, un POKéMON\n"
    .string "de nivel alto puede perder.\p"
    .string "Aprende qué tipos son fuertes y\n"
    .string "débiles ante el tipo de tu POKéMON.$"
