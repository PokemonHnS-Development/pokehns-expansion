Route45_hns_MapScripts::
	.byte 0

Route45_EventScript_Erik::
	trainerbattle_single TRAINER_ERIK_HNS, Route45_Text_HikerErikSeen, Route45_Text_HikerErikBeaten
	msgbox Route45_Text_HikerErikAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Michael::
	trainerbattle_single TRAINER_MICHAEL_HNS, Route45_Text_HikerMichaelSeen, Route45_Text_HikerMichaelBeaten
	msgbox Route45_Text_HikerMichaelAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Parry::
	trainerbattle_single TRAINER_PARRY_HNS, Route45_Text_HikerParrySeen, Route45_Text_HikerParryBeaten, Route45_EventScript_RegisterParry
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route45_EventScript_RematchParry
	msgbox Route45_Text_HikerParryAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_RegisterParry::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route45_Text_ParryRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_PARRY_HNS
	release
	end

Route45_EventScript_RematchParry::
	trainerbattle_rematch TRAINER_PARRY_HNS, Route45_Text_ParryRematchIntro, Route45_Text_ParryRematchDefeat
	msgbox Route45_Text_ParryPostRematch, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Timothy::
	trainerbattle_single TRAINER_TIMOTHY_HNS, Route45_Text_HikerTimothySeen, Route45_Text_HikerTimothyBeaten
	msgbox Route45_Text_HikerTimothyAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Kenji::
	trainerbattle_single TRAINER_KENJI_HNS, Route45_Text_BlackbeltKenjiSeen, Route45_Text_BlackbeltKenjiBeaten, Route45_EventScript_RegisterKenji
	goto_if_set FLAG_KENJI_HAS_ITEM_HNS, Route45_EventScript_KenjiGiveItem
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route45_EventScript_RematchKenji
	msgbox Route45_Text_BlackbeltKenjiAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_RegisterKenji::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route45_Text_KenjiRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KENJI_HNS
	release
	end

Route45_EventScript_RematchKenji::
	trainerbattle_rematch TRAINER_KENJI_HNS, Route45_Text_KenjiRematchIntro, Route45_Text_KenjiRematchDefeat
	msgbox Route45_Text_KenjiPostRematch, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_KenjiGiveItem::
	msgbox Route45_Text_KenjiHasItem, MSGBOX_DEFAULT
	giveitem VAR_KENJI_ITEM_HNS
	goto_if_eq VAR_RESULT, FALSE, Route45_EventScript_KenjiNoRoom
	clearflag FLAG_KENJI_HAS_ITEM_HNS
	msgbox Route45_Text_KenjiGaveItem, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_KenjiNoRoom::
	msgbox Route45_Text_KenjiNoRoom, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Ryan::
	trainerbattle_single TRAINER_RYAN_HNS, Route45_Text_CooltrainermRyanSeen, Route45_Text_CooltrainermRyanBeaten
	msgbox Route45_Text_CooltrainermRyanAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Kelly::
	trainerbattle_single TRAINER_KELLY_HNS, Route45_Text_CooltrainerfKellySeen, Route45_Text_CooltrainerfKellyBeaten
	msgbox Route45_Text_CooltrainerfKellyAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Quentin::
	trainerbattle_single TRAINER_QUENTIN_HNS, Route45_Text_CamperQuentinSeen, Route45_Text_CamperQuentinBeaten
	msgbox Route45_Text_CamperQuentinAfter, MSGBOX_AUTOCLOSE
	end

Route45_EventScript_Sign::
	msgbox Route45_Text_Sign, MSGBOX_SIGN
	end

Route45_EventScript_Item_Elixir::
	finditem ITEM_ELIXIR
	end

Route45_EventScript_Item_Max_Potion::
	finditem ITEM_MAX_POTION
	end

Route45_EventScript_Item_Full_Heal::
	finditem ITEM_FULL_HEAL
	end

Route45_EventScript_Item_Nugget::
	finditem ITEM_NUGGET
	end

Route45_Text_HikerErikSeen:
    .string "¡Prepárate para cualquier cosa!\p"
    .string "¡Veré si tus POKéMON han sido\n"
    .string "entrenados correctamente!$"

Route45_Text_HikerErikBeaten:
    .string "¡Oh, perdí esa!$"

Route45_Text_HikerErikAfter:
    .string "Volveré a la SENDA HELADA de\n"
    .string "CIUDAD ENDRINO para entrenar más.$"

Route45_Text_HikerMichaelSeen:
    .string "¡Oye! ¡Tienes agallas! Pero\n"
    .string "¿sabes qué?\p"
    .string "En cuanto a tener agallas,\n"
    .string "¡yo soy el mejor!$"

Route45_Text_HikerMichaelBeaten:
    .string "My POKéMON weren't spunky enough!$"

Route45_Text_HikerMichaelAfter:
    .string "¡Amo el VITUP! ¡Mmmm, qué rico!\p"
    .string "¡Sigo bebiendo por mis POKéMON!\p"
    .string "¡No puedo evitarlo!$"

Route45_Text_HikerParrySeen:
	.string "¡Mis POKéMON están llenos de poder!$"

Route45_Text_HikerParryBeaten:
    .string "¡Wahahah! ¡Soy el gran perdedor!$"

Route45_Text_HikerParryAfter:
    .string "No soy muy bueno pensando,\n"
    .string "¿ves?\p"
    .string "¡Así que avanzo con poder!$"

Route45_Text_ParryRegister:
    .string "No soy muy bueno pensando,\n"
    .string "¿ves?\p"
    .string "¡Así que avanzo con poder!$"

Route45_Text_ParryRematchIntro:
	.string "¡Mis POKéMON están llenos de poder!$"

Route45_Text_ParryRematchDefeat:
    .string "¡Wahahah! ¡Soy el gran perdedor!$"

Route45_Text_ParryPostRematch:
    .string "No soy muy bueno pensando,\n"
    .string "¿ves?\p"
    .string "¡Así que avanzo con poder!$"

Route45_Text_HikerTimothySeen:
    .string "¿Por qué subo montañas?\p"
    .string "Porque están ahí.\p"
    .string "¿Por qué entreno POKéMON?\p"
    .string "¡Porque están ahí!$"

Route45_Text_HikerTimothyBeaten:
    .string "Las derrotas... ¡También están ahí!$"

Route45_Text_HikerTimothyAfter:
    .string "Lo mejor que me ha pasado en la\n"
    .string "vida fue descubrir los POKéMON.$"

Route45_Text_HikerParryGivesIron:
    .string "¡No encuentro forma de ganar!\p"
    .string "¡Sigue así!\p"
    .string "Ah, y toma esto; es el regalo\n"
    .string "que no pudiste llevarte la\n"
    .string "última vez.$"

Route45_Text_BlackbeltKenjiSeen:
    .string "Entrenaba aquí yo solo.\p"
    .string "¡Mira los frutos de mi trabajo!$"

Route45_Text_BlackbeltKenjiBeaten:
    .string "Waaaargh!$"

Route45_Text_BlackbeltKenjiAfter:
    .string "Esto requiere medidas extremas.\p"
    .string "Iré a las colinas a entrenar\n"
    .string "en soledad.$"

Route45_Text_KenjiRegister:
    .string "Esto requiere medidas extremas.\p"
    .string "Iré a las colinas a entrenar\n"
    .string "en soledad.$"

Route45_Text_KenjiRematchIntro:
    .string "Entrenaba aquí yo solo.\p"
    .string "¡Mira los frutos de mi trabajo!$"

Route45_Text_KenjiRematchDefeat:
    .string "Waaaargh!$"

Route45_Text_KenjiPostRematch:
    .string "Esto requiere medidas extremas.\p"
    .string "Iré a las colinas a entrenar\n"
    .string "en soledad.$"

Route45_Text_KenjiHasItem:
    .string "¡Hola! Me estoy tomando un\n"
    .string "DRAGON entrenamos.\p"
    .string "Encontré algo bueno mientras\n"
    .string "estaba fuera. ¡Toma esto!$"

Route45_Text_KenjiGaveItem:
    .string "¡Úsalo bien!\p"
    .string "Debo volver a mi\n"
    .string "entrenamiento. ¡Oooooaaarrrgh!$"

Route45_Text_KenjiNoRoom:
    .string "Hmm, tu BOLSA está llena.\p"
    .string "Vuelve cuando tengas espacio.$"

Route45_Text_BlackbeltKenjiMorning:
    .string "Entrenaré un poco más\n"
    .string "antes del descanso para comer.$"

Route45_Text_BlackbeltKenjiNight:
    .string "Descansamos mucho al comer, así que\p"
    .string "¡ahora estamos listos para seguir!\p"
    .string "¡Vamos a entrenar otra vez!$"

Route45_Text_CooltrainermRyanSeen:
    .string "¿Qué opinas sobre\n"
    .string "criar POKéMON?$"

Route45_Text_CooltrainermRyanBeaten:
    .string "Has ganado mi respeto.$"

Route45_Text_CooltrainermRyanAfter:
    .string "Veo que crías a tus POKéMON\n"
    .string "con mucho cuidado.\p"
    .string "El vínculo que crees te salvará\n"
    .string "en situaciones difíciles.$"

Route45_Text_CooltrainerfKellySeen:
    .string "¿Cuál es tu estrategia de combate?\p"
    .string "Es necio usar movimientos fuertes\n"
    .string "sin discriminación.$"

Route45_Text_CooltrainerfKellyBeaten:
    .string "Fine. I lost.$"

Route45_Text_CooltrainerfKellyAfter:
    .string "No estoy a favor de los ataques\n"
    .string "demasiado poderosos.\p"
    .string "Quiero ganar, pero tampoco\n"
    .string "quiero dañar a los POKéMON.$"

Route45_Text_CamperQuentinSeen:
    .string "I'm really, really tough!$"

Route45_Text_CamperQuentinBeaten:
    .string "Era duro en la COLINA DEL ENTRENADOR...$"

Route45_Text_CamperQuentinAfter:
    .string "¿Has ido a la COLINA ENTRENADOR?\p"
    .string "Nunca pierdo allí, pero...$"

Route45_Text_Sign:
    .string "RUTA 45\n"
    .string "CAMINO DE MONTAÑA ADELANTE$"
